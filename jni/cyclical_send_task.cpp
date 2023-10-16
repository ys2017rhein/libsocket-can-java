#include <string>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cstddef>
#include <cerrno>
#include <syslog.h>

#include <sstream>
#include <string.h>
#include <stdio.h>

#include <vector>
#include <climits>
#include <memory>

extern "C" {
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
}

#include "cansocket.hpp"

#define MAX_CAN_FRAMES_TO_STORE					90
#define MAX_CAN_FRAMES_SIZE						 8
#define HARDCODED_100MS             		100000
#define TIME_BETWEEN_FRAMES           		  1100

typedef struct _CanFrameStorage {
	jint fd;
	jint if_idx;
	jint canid;
	jint len;
	jbyte data[MAX_CAN_FRAMES_SIZE];
	jint cycleTime;  //in ms
} CanFrameStorage;

typedef struct _CanAutoincrement{
	jint canid;
	jint bytePos;
	jbyte value;
} CanAutoincrement;


CanFrameStorage canStorage[MAX_CAN_FRAMES_TO_STORE];
CanAutoincrement canAutoIncrement[MAX_CAN_FRAMES_TO_STORE];

static int storageIdx = -1;
static int autoIncrementIdx = -1;

static int syncAdjust = 0; //basic "simulation" of a thread synchronisation //TODO replace with pthread sync
static int theOneCycleTime = HARDCODED_100MS;
static int statsErrorCntrCyclicalSend = 0;
static int statsFramesSendPerCycle = 0;


void* worker(void *t);
void sendFrame(CanFrameStorage *frameToSend);

void initThread(void) {
	pthread_t t;

	//init storage
	memset(canStorage, 0, sizeof(CanFrameStorage) * MAX_CAN_FRAMES_TO_STORE);
	storageIdx = 0;

	//init autoincrement
	memset(canAutoIncrement, 0, sizeof(CanAutoincrement) * MAX_CAN_FRAMES_TO_STORE);
	autoIncrementIdx = 0;

	//spawn extra thread
	int rc = pthread_create(&t, NULL, worker, (void*) NULL);
	if (rc) {
		perror("[FATAL] Failed spawn the thread..\n");
		exit(-1);
	}
}

int cyclicalAutoIncrementAddFunctionality( jint canid, jint autoIncrementBytePos ) {
	if(autoIncrementIdx >= MAX_CAN_FRAMES_TO_STORE){
		return -1;
	}
	canAutoIncrement[autoIncrementIdx].canid = canid;
	canAutoIncrement[autoIncrementIdx].bytePos = autoIncrementBytePos;
	canAutoIncrement[autoIncrementIdx].value = 0;
	autoIncrementIdx++;
	
	return 0;
}

/* check for special low level autocounter behavior.
 * If found, set the data for the autocounter byte position to the internally handled value 
 */ 
void ignoreAutoIncrementPos(jint canid, jbyte *tmpData) {
	for (int j = 0; j < autoIncrementIdx; j++) {
		if (canAutoIncrement[j].canid == canid) {
			if( canAutoIncrement[j].bytePos >= 0 && canAutoIncrement[j].bytePos < MAX_CAN_FRAMES_SIZE){
				//found an autoincrement frame, setting the relevant data byte back to low level autocounter value
				tmpData[canAutoIncrement[j].bytePos] = canAutoIncrement[j].value;
			}
		}
	}
}

/* check for special low level autocounter behavior.
 * If found, increment the data value at the given autocounter byte position  
 */ 
void modifyAutocounters(CanFrameStorage *frameToSend) {
	for (int j = 0; j < autoIncrementIdx; j++) {
		if (frameToSend->canid == canAutoIncrement[j].canid) {
			if( canAutoIncrement[j].bytePos >= 0 && canAutoIncrement[j].bytePos < MAX_CAN_FRAMES_SIZE){
				//found an autoincrement frame, auto incrementing the relevant data byte within the data 
				canAutoIncrement[j].value += 1;
				frameToSend->data[canAutoIncrement[j].bytePos] = canAutoIncrement[j].value;
			}
		}
	}
}

int cyclicalTaskAddCanFrame(jint fd, jint if_idx, jint canid, jint len,
		jbyte *buffer, jint _cylceTime) {
	if (storageIdx == -1) {
		initThread();
		//Note only the first given cycle time is used 
		theOneCycleTime = _cylceTime * 1000;
	}
	for (int i = 0; i < storageIdx; i++) {
		if (canStorage[i].canid == canid) {
			return 1;   //CAN identifier is already existing
		}

		//TODO we could also use the canStorage space someone has removed with cyclicalTaskRemoveCanFrame()
	}
	if (storageIdx >= MAX_CAN_FRAMES_TO_STORE) {
		return 2;  //storage size to low
	}

	canStorage[storageIdx].fd = fd;
	canStorage[storageIdx].if_idx = if_idx;
	canStorage[storageIdx].cycleTime = _cylceTime;
	canStorage[storageIdx].len = len;
	memcpy(canStorage[storageIdx].data, buffer, MAX_CAN_FRAMES_SIZE);
	//should be the last
	canStorage[storageIdx].canid = canid;
	storageIdx++;
	return 0;
}

int cyclicalTaskRemoveCanFrame(jint canid) {

	for (int i = 0; i < storageIdx; i++) {
		if (canStorage[i].canid == canid) {
			memset(&(canStorage[i]), 0, sizeof(CanFrameStorage));
			return 0;   //CAN identifier removed
		}
	}
	return 1;   //CAN identifier is not existing
}

int cyclicalTaskRemoveAll(void) {
	//init storage
	memset(canStorage, 0, sizeof(CanFrameStorage) * MAX_CAN_FRAMES_TO_STORE);
	storageIdx = 0;

	return 0;
}

int cyclicalTaskAdoptCanFrame(jint canid, jint len, jbyte *buffer) {
	jbyte tmpData[MAX_CAN_FRAMES_SIZE];
	
	for (int i = 0; i < storageIdx; i++) {
		if (canStorage[i].canid == canid) {
			memcpy(tmpData, buffer, MAX_CAN_FRAMES_SIZE);
			ignoreAutoIncrementPos(canid, tmpData);
			syncAdjust = 1;
			memcpy(&(canStorage[i].data), tmpData, MAX_CAN_FRAMES_SIZE);
			syncAdjust = 0;
			return 0;   //CAN identifier adopted
		}
	}
	return 1;
}

void* worker(void *t) {
	CanFrameStorage frameToSend;
	int framesCnt;

	//TODO remove hardcoded 100ms cycle time and implement using of cycleTime
	while (1) {
		framesCnt = 0;
		for (int i = 0; i < storageIdx; i++) {
			if (canStorage[i].canid != 0) {
				while (syncAdjust == 1) {
					usleep(10);
				}
				memcpy((void*) &frameToSend, (void*) &(canStorage[i]),
						sizeof(CanFrameStorage));
				modifyAutocounters(&frameToSend);
				sendFrame(&frameToSend);
				framesCnt++;
			}
		}
		statsFramesSendPerCycle = framesCnt;
		if (framesCnt * TIME_BETWEEN_FRAMES >= theOneCycleTime) {
			continue;
		}
		if (framesCnt == 0) {
			usleep(theOneCycleTime);
		} else {
			usleep(theOneCycleTime - framesCnt * TIME_BETWEEN_FRAMES);
		}
	}   //while
	return NULL;
}

void sendFrame(CanFrameStorage *frameToSend) {
	const int flags = 0;
	ssize_t nbytes;

	struct sockaddr_can addr;
	struct can_frame frame;
	memset(&addr, 0, sizeof(addr));
	memset(&frame, 0, sizeof(frame));
	addr.can_family = AF_CAN;
	addr.can_ifindex = frameToSend->if_idx;
	frame.can_id = frameToSend->canid;
	frame.can_dlc = static_cast<__u8 >(frameToSend->len);
	memcpy(&(frame.data), frameToSend->data, MAX_CAN_FRAMES_SIZE);
	nbytes = sendto(frameToSend->fd, &frame, sizeof(frame), flags,
			reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));

	if (nbytes == -1) {
		statsErrorCntrCyclicalSend++;
//		perror("[FATAL] CAN: (cyclically Thread) Unable to send CAN frames\n");
	} else if (nbytes != sizeof(frame)) {
		statsErrorCntrCyclicalSend++;
		std::string s; //for logging purposes
		perror("[FATAL] CAN: (cyclically Thread) send partial CAN frame\n");
	}
}

int statsGetCanFrameErrorCntrCyclicalSend() {
	return statsErrorCntrCyclicalSend;
}

int statsGetCanFrameFramesSendPerCycle(){ 
	return statsFramesSendPerCycle;
}




/*
 * cansocket.h
 *
 *  Created on: 12.09.2022
 *      Author: C.Lehne
 */

#ifndef JNI_CANSOCKET_HPP_
#define JNI_CANSOCKET_HPP_


//#ifdef (ANDROID) || defined(__ANDROID__)
//#include "jni.h"
//#else
#include "io_openems_edge_socketcan_driver_CanSocket.h"
//#endif


void logthis(std::string msg);

void throwException(JNIEnv *env, const std::string& exception_name, const std::string& msg);
void throwIOExceptionMsg(JNIEnv *env, const std::string& msg);
void throwIOExceptionErrno(JNIEnv *env, const int exc_errno);
void throwIllegalArgumentException(JNIEnv *env, const std::string& message);
void throwOutOfMemoryError(JNIEnv *env, const std::string& message);

void cyclicalInitLowLevelThread(void);
int cyclicalTaskAddCanFrame(jint fd, jint if_idx, jint canid, jint len, jbyte *buffer, jint cylceTime);
int cyclicalTaskRemoveCanFrame(jint canid);
int cyclicalTaskAdoptCanFrame(jint canid, jint len, jbyte *buffer);
int cyclicalTaskRemoveAll(void);
int cyclicalAutoIncrementAddFunctionality( jint canid, jint autoIncrementBytePos );
int statsGetCanFrameErrorCntrCyclicalSend();
int statsGetCanFrameFramesSendPerCycle();

#endif /* JNI_CANSOCKET_HPP_ */

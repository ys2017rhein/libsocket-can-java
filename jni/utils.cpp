#include <string>
#include <algorithm>
#include <utility>

#include <cstring>
#include <cstddef>
#include <cerrno>
#include <syslog.h>

#include <sstream>
#include <string.h>

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

}

#include "cansocket.hpp"


static const int ERRNO_BUFFER_LEN = 1024;

typedef unsigned char BYTE;


void logthis(std::string msg) {
	openlog("libsocket-can-java native library ", LOG_CONS, LOG_USER);
	std::stringstream strs;
	strs << msg;
	std::string temp_str = strs.str();
	char* char_type = (char*) temp_str.c_str();
	syslog(LOG_INFO, char_type);

}

void throwException(JNIEnv *env, const std::string& exception_name,
		const std::string& msg) {
	const jclass exception = env->FindClass(exception_name.c_str());
	if (exception == NULL) {
		return;
	}
	env->ThrowNew(exception, msg.c_str());
}

void throwIOExceptionMsg(JNIEnv *env, const std::string& msg) {
	throwException(env, "java/io/IOException", msg);
}

void throwIOExceptionErrno(JNIEnv *env, const int exc_errno) {
	char message[ERRNO_BUFFER_LEN];
	const char * const msg = (char *) strerror_r(exc_errno, message,
			ERRNO_BUFFER_LEN);
	if (((long) msg) == 0) {
		// POSIX strerror_r, success
		throwIOExceptionMsg(env, std::string(message));
	} else if (((long) msg) == -1) {
		// POSIX strerror_r, failure
		// (Strictly, POSIX only guarantees a value other than 0. The safest
		// way to implement this function is to use C++ and overload on the
		// type of strerror_r to accurately distinguish GNU from POSIX. But
		// realistic implementations will always return -1.)
		snprintf(message, ERRNO_BUFFER_LEN, "errno %d", exc_errno);
		throwIOExceptionMsg(env, std::string(message));
	} else {
		// glibc strerror_r returning a string
		throwIOExceptionMsg(env, std::string(msg));
	}
}

void throwIllegalArgumentException(JNIEnv *env,
		const std::string& message) {
	throwException(env, "java/lang/IllegalArgumentException", message);
}

void throwOutOfMemoryError(JNIEnv *env, const std::string& message) {
	throwException(env, "java/lang/OutOfMemoryError", message);
}





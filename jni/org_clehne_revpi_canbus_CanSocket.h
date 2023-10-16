/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_clehne_revpi_canbus_CanSocket */

#ifndef _Included_org_clehne_revpi_canbus_CanSocket
#define _Included_org_clehne_revpi_canbus_CanSocket
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _getCANID_SFF
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1getCANID_1SFF
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _getCANID_EFF
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1getCANID_1EFF
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _getCANID_ERR
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1getCANID_1ERR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _isSetEFFSFF
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_clehne_revpi_canbus_CanSocket__1isSetEFFSFF
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _isSetRTR
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_clehne_revpi_canbus_CanSocket__1isSetRTR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _isSetERR
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_clehne_revpi_canbus_CanSocket__1isSetERR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setEFFSFF
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setEFFSFF
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setRTR
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setRTR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setERR
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setERR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _clearEFFSFF
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1clearEFFSFF
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _clearRTR
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1clearRTR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _clearERR
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1clearERR
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _openSocketRAW
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1openSocketRAW
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _openSocketBCM
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1openSocketBCM
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _close
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1close
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetchInterfaceMtu
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetchInterfaceMtu
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_MTU
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1MTU
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_FD_MTU
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1FD_1MTU
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _discoverInterfaceIndex
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1discoverInterfaceIndex
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _discoverInterfaceName
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_clehne_revpi_canbus_CanSocket__1discoverInterfaceName
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _bindToSocket
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1bindToSocket
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _recvFrame
 * Signature: (I)Lorg/clehne/revpi/canbus/CanSocket/CanFrame;
 */
JNIEXPORT jobject JNICALL Java_org_clehne_revpi_canbus_CanSocket__1recvFrame
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _sendFrame
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1sendFrame
  (JNIEnv *, jclass, jint, jint, jint, jbyteArray);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _sendCyclicallyAdd
 * Signature: (III[BI)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1sendCyclicallyAdd
  (JNIEnv *, jclass, jint, jint, jint, jbyteArray, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _sendCyclicallyRemove
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1sendCyclicallyRemove
  (JNIEnv *, jclass, jint, jint, jint, jbyteArray);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _removeCyclicalAll
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1removeCyclicalAll
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _sendCyclicallyAdopt
 * Signature: (III[B)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1sendCyclicallyAdopt
  (JNIEnv *, jclass, jint, jint, jint, jbyteArray);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _enableCyclicallyAutoIncrement
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1enableCyclicallyAutoIncrement
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _statsGetCanFrameErrorCntrCyclicalSend
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1statsGetCanFrameErrorCntrCyclicalSend
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _statsGetCanFrameErrorCntrSend
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1statsGetCanFrameErrorCntrSend
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _statsGetCanFrameErrorCntrReceive
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1statsGetCanFrameErrorCntrReceive
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _statsGetCanFrameFramesSendPerCycle
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1statsGetCanFrameFramesSendPerCycle
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_RAW_FILTER
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1RAW_1FILTER
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_RAW_ERR_FILTER
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1RAW_1ERR_1FILTER
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_RAW_LOOPBACK
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1RAW_1LOOPBACK
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_RAW_RECV_OWN_MSGS
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1RAW_1RECV_1OWN_1MSGS
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _fetch_CAN_RAW_FD_FRAMES
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1fetch_1CAN_1RAW_1FD_1FRAMES
  (JNIEnv *, jclass);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setFilters
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setFilters
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _getFilters
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_clehne_revpi_canbus_CanSocket__1getFilters
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setsockopt
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setsockopt
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _getsockopt
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_clehne_revpi_canbus_CanSocket__1getsockopt
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     org_clehne_revpi_canbus_CanSocket
 * Method:    _setreceivetimeout
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_org_clehne_revpi_canbus_CanSocket__1setreceivetimeout
  (JNIEnv *, jclass, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif

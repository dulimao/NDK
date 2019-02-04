
#include "jni.h"


#ifndef _Included_jni_JNIMain
#define _Included_jni_JNIMain
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jni_JNIMain
 * Method:    getStringFromC
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jni_JNIMain_getStringFromC
  (JNIEnv *, jclass);




JNIEXPORT jstring JNICALL Java_jni_JNIMain_accessField
  (JNIEnv *, jobject);


#ifdef __cplusplus
}
#endif
#endif

//
// Created by ZhangWei on 2016/12/19.
//

#ifndef ANDROIDJNI_ANDROID_JNI_H
#define ANDROIDJNI_ANDROID_JNI_H

#endif //ANDROIDJNI_ANDROID_JNI_H

#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOG_TAG    "android-jni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// extern "C"不然会报错
extern "C" {

jstring Java_com_excellence_androidjni_MainActivity_stringFromJNI(
        JNIEnv *,
        jobject);

JNIEXPORT jobjectArray JNICALL
        Java_com_excellence_androidjni_MainActivity_infoArrayFromJNI(JNIEnv *, jobject,
                                                                     jint);
JNIEXPORT jobject JNICALL
        Java_com_excellence_androidjni_MainActivity_infoListFromJNI(JNIEnv *, jobject,
                                                                    jint);
char *intToStr(int num);

}
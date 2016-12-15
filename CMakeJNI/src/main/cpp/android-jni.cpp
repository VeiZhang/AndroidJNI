#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOG_TAG    "android-jni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

char * newString(int num);

extern "C"
jstring
Java_com_excellence_androidjni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// C/C++不能返回局部创建变量,可以返回地址
char * newString(int num) {
    int count = 1;
    int index = num;
    while (index > 0) {
        index /= 10;
        count++;
    }

    char *str = NULL;
    str = (char *) malloc(sizeof(int) * count);

    int n = sprintf(str, "%d", num);
    LOGE("%d转换为字符串的长度是:%d", num, n);

    // n == strlen(str) true
    for (int i = 0; i < strlen(str); ++i) {
        LOGD("%d的第%d个字符:%c", num, i, str[i]);
    }
    // \0结束符 str[n] = '\0';

    return str;
}

// extern "C"不然会报错
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_excellence_androidjni_MainActivity_infoFromJNI(JNIEnv *env, jobject instance, jint num) {

    // TODO
    LOGE("######### %d", num);
    jclass classINFO = env->FindClass("com/excellence/androidjni/Info");
    jobjectArray infos = env->NewObjectArray(num, classINFO, 0);
    jmethodID consID = env->GetMethodID(classINFO, "<init>", "()V");
    jfieldID name = env->GetFieldID(classINFO, "name", "Ljava/lang/String;");
    jfieldID id = env->GetFieldID(classINFO, "id", "I");
    for (int i = 0; i < num; i++) {
        LOGD("************ %d", i);
        jobject obj = env->NewObject(classINFO, consID);
        LOGE("%d的占用空间:%d 转化为字符串:%s", i, sizeof(i), newString(i));
        env->SetObjectField(obj, name, env->NewStringUTF(newString(i)));
        env->SetIntField(obj, id, i);
        env->SetObjectArrayElement(infos, i, obj);
    }
    return infos;
}
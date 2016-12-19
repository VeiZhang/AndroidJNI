#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOG_TAG    "android-jni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

char *intToStr(int num);

extern "C"
jstring
Java_com_excellence_androidjni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// extern "C"不然会报错
extern "C"
//返回Java数组
JNIEXPORT jobjectArray JNICALL
Java_com_excellence_androidjni_MainActivity_infoArrayFromJNI(JNIEnv *env, jobject instance,
                                                             jint num) {

    // TODO
    LOGE("%s ######### %d", __FUNCTION__, num);
    jclass classINFO = env->FindClass("com/excellence/androidjni/Info");
    jobjectArray infos = env->NewObjectArray(num, classINFO, 0);
    jmethodID consID = env->GetMethodID(classINFO, "<init>", "()V");
    jfieldID name = env->GetFieldID(classINFO, "name", "Ljava/lang/String;");
    jfieldID id = env->GetFieldID(classINFO, "id", "I");
    for (int i = 0; i < num; i++) {
        LOGD("************ %d", i);
        jobject obj = env->NewObject(classINFO, consID);
        jstring stringName = env->NewStringUTF(intToStr(i));
        env->SetObjectField(obj, name, stringName);
        env->SetIntField(obj, id, i);
        env->SetObjectArrayElement(infos, i, obj);

        //释放object引用
        env->DeleteLocalRef(obj);
        env->DeleteLocalRef(stringName);
    }

    //释放object引用
    env->DeleteLocalRef(classINFO);

    return infos;
}

// extern "C"不然会报错
extern "C"
//返回List
JNIEXPORT jobject JNICALL
Java_com_excellence_androidjni_MainActivity_infoListFromJNI(JNIEnv *env, jobject instance,
                                                            jint num) {

    // TODO
    LOGE("%s ########## %d", __FUNCTION__, num);
    //获得ArrayList类引用
    jclass listCls = env->FindClass("java/util/ArrayList");
    //获得得带参数构造函数Id
    jmethodID costruct = env->GetMethodID(listCls, "<init>", "()V");
    //创建一个Arraylist集合对象
    jobject listObj = env->NewObject(listCls, costruct);
    //获得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    jmethodID listAdd = env->GetMethodID(listCls, "add", "(Ljava/lang/Object;)Z");

    //获取类引用
    jclass infoCls = env->FindClass("com/excellence/androidjni/Info");
    jmethodID consID = env->GetMethodID(infoCls, "<init>", "(Ljava/lang/String;I)V");
    for (int i = 0; i < num; i++) {
        LOGD("************ %d", i);
        jstring stringName = env->NewStringUTF(intToStr(i));
        //初始化带参数的构造方法
        jobject infoObj = env->NewObject(infoCls, consID, stringName, i);
        env->CallBooleanMethod(listObj, listAdd, infoObj);

        env->DeleteLocalRef(infoObj);
        env->DeleteLocalRef(stringName);
    }
    env->DeleteLocalRef(infoCls);
    env->DeleteLocalRef(listCls);
    return listObj;
}

// C/C++不能返回局部创建变量,可以返回地址
char *intToStr(int num) {
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
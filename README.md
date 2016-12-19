# AndroidJNI
 [Android JNI示例](https://github.com/VeiZhang/AndroidJNI/blob/master/CMakeJNI/src/main/cpp/android-jni.cpp)

#### 1.Native层返回String给Java层
    jstring Java_com_excellence_androidjni_MainActivity_stringFromJNI(
            JNIEnv *,
            jobject);

#### 2.Native层返回Array数组给Java层
    JNIEXPORT jobjectArray JNICALL
            Java_com_excellence_androidjni_MainActivity_infoArrayFromJNI(JNIEnv *, jobject,
                                                                         jint);

#### 3.Native层返回List对象给java层
    JNIEXPORT jobject JNICALL
            Java_com_excellence_androidjni_MainActivity_infoListFromJNI(JNIEnv *, jobject,
                                                                        jint);

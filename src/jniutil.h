#pragma once

inline jstring GetPackageName(JNIEnv *env, jobject jActivity)
{
    jmethodID method = env->GetMethodID(env->GetObjectClass(jActivity), OBFUSCATE("getPackageName"), OBFUSCATE("()Ljava/lang/String;"));
    return (jstring)env->CallObjectMethod(jActivity, method);
}

inline jobject GetGlobalActivity(JNIEnv *env)
{
    jclass activityThread = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, OBFUSCATE("currentActivityThread"), OBFUSCATE("()Landroid/app/ActivityThread;"));
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    jmethodID getApplication = env->GetMethodID(activityThread, OBFUSCATE("getApplication"), OBFUSCATE("()Landroid/app/Application;"));
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}

inline void toasty(const char* txt, int msDuration = 3500)
{
    jclass ToastClass = mEnv->FindClass(OBFUSCATE("android/widget/Toast"));
    jmethodID makeTextMethodID = mEnv->GetStaticMethodID(ToastClass, OBFUSCATE("makeText"), OBFUSCATE("(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    jmethodID showMethodID = mEnv->GetMethodID(ToastClass, OBFUSCATE("show"), OBFUSCATE("()V"));

    jstring message = mEnv->NewStringUTF(txt);
    jint duration = msDuration;

    jobject toast = mEnv->CallStaticObjectMethod(ToastClass, makeTextMethodID, GetGlobalActivity(mEnv), message, duration);
    mEnv->CallVoidMethod(toast, showMethodID);
    
    mEnv->DeleteLocalRef(message);
}
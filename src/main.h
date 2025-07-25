#pragma once 

#include <jni.h>
#include <android/log.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "ARMHook.h"
#include "str_obfuscate.hpp"
//#include "../dependencies/Dobby/include/dobby.h"

extern uintptr_t g_libGTAVC;
#define GTA(a) (g_libGTAVC + (a))

extern char const* g_pStorage;
extern const char* g_pAPKPackage;
extern JavaVM *mVm;
extern JNIEnv *mEnv;

uint32_t GetTickCount();
void SetFunc(uintptr_t addr, uintptr_t *orig);

#define AndroidLog(a) __android_log_write(ANDROID_LOG_INFO, "VCMP", a);
#define LOG_TAG "VCMP"
#define LOGI(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
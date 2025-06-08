//
// Created by weikton on 08.06.2025.
//
#pragma once
#include <string>
#include <android/log.h>

void Log(const char *fmt, ...);

#define LOG_TAG "VICEMP"
#define LOGI(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
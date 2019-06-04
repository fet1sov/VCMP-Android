#pragma once

#include <android/log.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

extern uintptr_t g_libGTAVC;
extern char const* g_pStorage;

void InitNetwork();
uint32_t GetTickCount();

#define LOG_TAG "VICEMP"
#define LOGI(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

/* ============ */
#include "game/game.h"
#include "game/camera.h"
#include "game/scripting.h"
#include "game/patches.h"

#include "util/address.h"
#include "util/util.h"
#include "util/memory.h"
/* ============ */
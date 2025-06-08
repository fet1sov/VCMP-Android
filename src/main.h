#pragma once

#include <android/log.h>
#include "log.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

extern uintptr_t g_libGTAVC;
extern char const* g_pStorage;

void InitNetwork();
uint32_t GetTickCount();


/* ============ */
#include "game/game.h"
#include "game/camera.h"
#include "game/scripting.h"
#include "game/patches.h"

#include "util/address.h"
#include "util/util.h"
#include "util/memory.h"
/* ============ */
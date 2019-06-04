#include "main.h"
#include <jni.h>

uintptr_t g_libGTAVC = 0;
char const* g_pStorage = nullptr;

bool bNetworkInited = false;

CGame *pGame = 0;

void *Init(void *p)
{
	pGame = new CGame();

	while (true)
	{
		if (*(uintptr_t*)(g_libGTAVC+ADDR_GAMESTATE) == 9)
		{
			LOGI("libGTAVC.so: Game start sended!");
			pGame->InitGame();
			break;
		} else {
			usleep(5000);
		}
	}

	pthread_exit(0);
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) 
{
	LOGI("VC:MP has inited!");

	g_libGTAVC = findLibrary("libGTAVC.so");
	if (!g_libGTAVC)
	{
		LOGI("ERROR: libGTAVC.so not found!");
	}
	LOGI("libGTAVC.so: 0x%X", g_libGTAVC);

	g_pStorage = "/storage/emulated/0/Android/data/com.rockstargames.gtavc/files/";
	if(!g_pStorage)
	{
		return LOGI("Error: Storage path not found!");
	}
	LOGI("Storage path: %s", g_pStorage);

	/* Hooks */
	InitHooks();
	/* ========== */

	pthread_t thread;
	pthread_create(&thread, 0, Init, 0);

    return JNI_VERSION_1_6;
}

uint32_t GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000+tv.tv_usec/1000);
}
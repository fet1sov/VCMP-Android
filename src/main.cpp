#include "main.h"
#include "jniutil.h"
#include "CHooks.h"
#define LOGI(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
uintptr_t g_libGTAVC = 0; // libGTAVC
const char* g_pAPKPackage;
char const* g_pStorage = nullptr;
bool bNetworkInited = false;
#include "dependencies/Dobby/include/dobby.h"
#include "game/game.h"

jobject appContext;
JavaVM *mVm;
JNIEnv *mEnv;
#ifdef IS_ARM64
#define ADDR_GAMESTATE 0x57AED0
#elif defined(IS_ARM32)
#define ADDR_GAMESTATE 0x7152BC
#endif
CGame *pGame = 0;

void (*TouchEvent)(int, int, int posX, int posY);

void TouchEvent_hook(int type, int num, int posX, int posY) {
    return TouchEvent(type, num, posX, posY);
}

void WNGTA() 
{
#ifdef IS_ARM64

    DobbyHook((void *)GTA(0x45D4E8), (void *)TouchEvent_hook, (void **)&TouchEvent);
#elif defined(IS_ARM32)
    DobbyHook((void *)GTA(0x3199EC), (void *)TouchEvent_hook, (void **)&TouchEvent);

#endif
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("VC:MP initializing...");
    
	g_libGTAVC = ARMHook::getLibraryAddress("libGTAVC.so");
	if(g_libGTAVC)
	{
        WNGTA();
        CHooks::InitHooksKuzia();
	pGame->InitGame();
	}
    else
    {
        LOGE("ERROR: libGTAVC.so not found!");
        return JNI_ERR;
    }

    g_pStorage = "/storage/emulated/0/Android/data/com.rockstargames.gtavc/files/";

	return JNI_VERSION_1_6;
}

uint32_t GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

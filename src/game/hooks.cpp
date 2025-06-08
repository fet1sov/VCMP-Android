#include "../main.h"

void (*TouchEvent)(int, int, int posX, int posY);
void TouchEvent_hook(int type, int num, int posX, int posY)
{
	bool bRet;

	if(bRet) 
		return TouchEvent(type, num, posX, posY);
}

/**
  * "/storage/emulated/0/Android/data/com.rockstargames.gtavc/files/"
  * "/storage/emulated/0/VCMP/"
*/
void (*NvUtilInit)();
void NvUtilInit_hook()
{
    NvUtilInit();

	// .. vc
    UnFuck(g_libGTAVC + NV_STORAGE);
    strcpy((char*)(g_libGTAVC + NV_STORAGE), "/storage/emulated/0/Android/data/com.rockstargames.gtavc/files/");

	// .. client
    g_pStorage = (char*)(g_libGTAVC + NV_STORAGE);
    Log("> Custom Storage: %s", g_pStorage);
}

void InstallHooks()
{
    LOGI("> Inject hooks...");
	InstallHook(g_libGTAVC+HOOK_NVINIT, (uintptr_t)NvUtilInit_hook, (uintptr_t*)NvUtilInit);
	InstallHook(g_libGTAVC+HOOK_TOUCHEVENT, (uintptr_t)TouchEvent_hook, (uintptr_t*)&TouchEvent);
}
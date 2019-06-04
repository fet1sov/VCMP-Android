#include "../main.h"

void (*TouchEvent)(int, int, int posX, int posY);
void TouchEvent_hook(int type, int num, int posX, int posY)
{
	bool bRet;

	if(bRet) 
		return TouchEvent(type, num, posX, posY);
}

void InstallHooks()
{
	InstallHook(g_libGTAVC+HOOK_TOUCHEVENT, (uintptr_t)TouchEvent_hook, (uintptr_t*)&TouchEvent);
}
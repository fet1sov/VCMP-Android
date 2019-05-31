#include "../main.h"
#include "patches.h"

void ApplyPatches()
{
	LOGI("libGTAVC.so: Patching the game...");

	WriteMemory(g_libGTAVC+CLOCK_DATA, "VC:MP", 6);
}
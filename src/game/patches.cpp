#include "../main.h"
#include "patches.h"

void ApplyPatches()
{
	LOGI("libGTAVC.so: Patching the game...");

	WriteMemory(g_libGTAVC+CLOCK_DATA, "VC:MP", 6);

	// .. That is a mini stupid thing to get log for my plugin
    UnFuck(g_libGTAVC + CUSTOMTAG_OSWR);
    strcpy((char*)(g_libGTAVC + CUSTOMTAG_OSWR), "WeiktonWrapper?");
    UnFuck(g_libGTAVC + CUSTOMTAG_NVE);
    strcpy((char*)(g_libGTAVC + CUSTOMTAG_NVE), "WeiktonNVEvent?");
}

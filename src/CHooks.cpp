#include "main.h"
#include "CHooks.h"
#include <iostream>


void (*CMenuManager_ProcessButtonPresses)(uintptr_t);
void CMenuManager_ProcessButtonPresses_hook(uintptr_t thiz)
{
    //LOGI("libGTAVC.so: Patching the game...");


    CMenuManager_ProcessButtonPresses(thiz);

}
void (*CMenuManager_DrawLoadingScreen)(uintptr_t);
void CMenuManager_DrawLoadingScreen_hook(uintptr_t thiz)
{
    LOGI("CMenuManager: Открытие логин скрин....");

    CMenuManager_DrawLoadingScreen(thiz);

}


int (*OS_ServiceOpenLink)(const char* url);
int OS_ServiceOpenLink_hook(const char* url) {
    const char* newUrl = "https://t.me/kuzia15/";

    if (strstr(url, "http://www.rockstarwarehouse.com/")) {
        return OS_ServiceOpenLink(newUrl);
    }

    return OS_ServiceOpenLink(url);
}

void (*LoadingScreen)(const char *, const char *, const char *);
void LoadingScreen_hook(const char *text, const char *text1, const char *text2)
{
    LOGI("LoadingScreen: Открытие логин скрин....");
    LOGI("text %s", text);
    LOGI("text %s", text1);
    LOGI("text %s", text);
    //CallFunction<void>(g_libGTAVC+0x152070+1);

    LoadingScreen(text, text1, text2);

}
void (*CHud_Draw)(uintptr_t);
void CHud_Draw_hook(uintptr_t thiz)
{
    //LOGI("libGTAVC.so: Patching the game...");
    return;

}
#include "dependencies/Dobby/include/dobby.h"
void CHooks::InitHooksKuzia() {

#ifdef IS_ARM64

    DobbyHook((void *)GTA(0x206490), (void *)CMenuManager_ProcessButtonPresses_hook, (void **)&CMenuManager_ProcessButtonPresses);
    DobbyHook((void *)GTA(0x201F00), (void *)CMenuManager_DrawLoadingScreen_hook, (void **)&CMenuManager_DrawLoadingScreen);
    DobbyHook((void *)GTA(0x1F8CC8), (void *)LoadingScreen_hook, (void **)&LoadingScreen);
    DobbyHook((void *)GTA(0x2C317C), (void *)CHud_Draw_hook, (void **)&CHud_Draw);

DobbyHook((void *)GTA(0x4609CC), (void *)OS_ServiceOpenLink_hook, (void **)&OS_ServiceOpenLink);

#elif defined(IS_ARM32)

    DobbyHook((void *)GTA(0x155848), (void *)CMenuManager_ProcessButtonPresses_hook, (void **)&CMenuManager_ProcessButtonPresses);
    DobbyHook((void *)GTA(0x152070), (void *)CMenuManager_DrawLoadingScreen_hook, (void **)&CMenuManager_DrawLoadingScreen);
    DobbyHook((void *)GTA(0x14E164), (void *)LoadingScreen_hook, (void **)&LoadingScreen);
    DobbyHook((void *)GTA(0x1E8278), (void *)CHud_Draw_hook, (void **)&CHud_Draw);

    DobbyHook((void *)GTA(0x322D18), (void *)OS_ServiceOpenLink_hook, (void **)&OS_ServiceOpenLink);
#endif
}
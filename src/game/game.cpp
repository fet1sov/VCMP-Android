#include "../main.h"
#include "game.h"

void InitScripting();
void InstallHooks();

CGame::CGame()
{
	m_pGameCamera = new CCamera();
}

void CGame::InitGame()
{
	LOGI("libGTAVC.so: Game has been inited!");

	ApplyPatches();
	InitScripting();
	
	InstallHooks();
}
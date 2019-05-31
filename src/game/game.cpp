#include "../main.h"
#include "game.h"

void InitScripting();

CGame::CGame()
{
	m_pGameCamera = new CCamera();
}

void CGame::InitGame()
{
	LOGI("libGTAVC.so: Game has been inited!");
	ApplyPatches();
	InitScripting();
}
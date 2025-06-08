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
	LOGI("> Inject game...");

	ApplyPatches();
	InitScripting();
	
	InstallHooks();
}
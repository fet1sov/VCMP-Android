#pragma once

#include "camera.h"

class CGame
{
public:
	CGame();
	~CGame() {};

	void InitGame();
	void StartGame();
private:
	CCamera* m_pGameCamera;
};
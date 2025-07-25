#pragma once

#include "camera.h"

class CGame
{
public:
    CGame();
    ~CGame() {};

    void InitGame();
private:
    CCamera* m_pGameCamera;
};
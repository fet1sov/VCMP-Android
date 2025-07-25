#include "../main.h"
#include "camera.h"
#include "scripting.h"

void CCamera::SetBehindPlayer()
{
	ScriptCommand(&set_camera_behind_player);
}
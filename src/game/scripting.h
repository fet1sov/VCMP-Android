#pragma once

#define MAX_SCRIPT_VARS 16
#define MAX_SCRIPT_SIZE	255

struct GAME_SCRIPT_THREAD
{
	uint8_t Pad1[20];			// +00
	uintptr_t dwScriptIP;		// +20
	uint8_t Pad2[36];			// +24
	uint32_t dwLocalVar[32];	// +60
	uint32_t dwTimers[2];		// +188
	uint8_t Pad3[33];			// +196
	uint8_t condResult;			// +229
	uint8_t Pad4[10];			// +230
	uint16_t logicalOp;			// +240
	uint8_t notFlag;			// +242
	uint8_t Pad5[13];			// +243
};

struct SCRIPT_COMMAND
{
	uint32_t OpCode;
	char Params[MAX_SCRIPT_VARS];
};

int ScriptCommand(const SCRIPT_COMMAND* ScriptCommand, ...);

const SCRIPT_COMMAND set_camera_behind_player	= { 0x0373, "" };
const SCRIPT_COMMAND toggle_player_controllable = { 0x01B4, "ii" };
const SCRIPT_COMMAND set_camera					= { 0x03CB, "fff" };
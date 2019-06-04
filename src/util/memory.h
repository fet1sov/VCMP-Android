#pragma once

void UnFuck(uintptr_t target);
void NOP(uintptr_t dest, size_t size);
void WriteMemory(uintptr_t dest, const char* src, size_t size);
void ReadMemory(uintptr_t dest, uintptr_t src, size_t size);
void InitHooks();
void JMPCode(uintptr_t func, uintptr_t addr);
void WriteHookProc(uintptr_t addr, uintptr_t func);
void InstallHook(uintptr_t addr, uintptr_t func, uintptr_t *orig);
void InstallMethodHook(uintptr_t addr, uintptr_t func);
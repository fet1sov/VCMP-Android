#include "../main.h"
#include "memory.h"
#include <sys/mman.h>

#define HOOK_PROC   "\x01\xB4\x01\xB4\x01\x48\x01\x90\x01\xBD\x00\xBF\x00\x00\x00\x00"

uintptr_t mmap_start = 0,
    mmap_end = 0,
    memlib_start = 0,
    memlib_end = 0;

void UnFuck(uintptr_t target)
{
    mprotect((void*)(target & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void NOP(uintptr_t dest, size_t size)
{
    for(uint32_t ptr = dest; ptr != (dest + size*2); ptr+=2)
    {
        *(char*)ptr = 0x00;
        *(char*)(ptr+1) = 0x46;
    }
    __builtin___clear_cache((char*)dest, (char*)(dest+size*2));
}

void WriteMemory(uintptr_t dest, const char* src, size_t size)
{
    mprotect((void*)(dest & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy((void*)dest, (void*)src, size);
    __builtin___clear_cache((char*)dest, (char*)(dest+size));
}

void ReadMemory(uintptr_t dest, uintptr_t src, size_t size)
{
    mprotect((void*)(src & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy((void*)dest, (void*)src, size);
}

void InitHooks()
{
	LOGI("Hooks: Init hook system...");
    memlib_start = g_libGTAVC+MEM_START; // gzprintf
    memlib_end = memlib_start+0x100;

    mmap_start = (uintptr_t)mmap(0, PAGE_SIZE, PROT_WRITE | PROT_READ | PROT_EXEC,
      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        mprotect((void*)(mmap_start & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    mmap_end = (mmap_start + PAGE_SIZE);
    LOGI("Hooks: Hook system inited!");
}

void JMPCode(uintptr_t func, uintptr_t addr)
{
    uint32_t code = ((addr-func-4) >> 12) & 0x7FF | 0xF000 | ((((addr-func-4) >> 1) & 0x7FF | 0xB800) << 16);
    WriteMemory(func, (const char*)&code, 4);
}

void WriteHookProc(uintptr_t addr, uintptr_t func)
{
    char code[16];
    memcpy(code, HOOK_PROC, 16);
    *(uint32_t*)&code[12] = (func | 1);
    WriteMemory(addr, (const char*)code, 16);
}

void InstallHook(uintptr_t addr, uintptr_t func, uintptr_t *orig)
{
	LOGI("Install Hook: ADDR 0x%X FUNC 0x%X", addr, func);
    if(memlib_end < (memlib_start + 0x10) || mmap_end < (mmap_start + 0x20))
    {
        LOGI("Hooks: Space Limit!");
        exit(1);
    }

    ReadMemory(mmap_start, addr, 4);
    WriteHookProc(mmap_start+4, addr+4);
    *orig = mmap_start+1;
    mmap_start += 32;
    JMPCode(addr, memlib_start);
    WriteHookProc(memlib_start, func);
    memlib_start += 16;
}

void InstallMethodHook(uintptr_t addr, uintptr_t func)
{
    UnFuck(addr);
    *(uintptr_t*)addr = func;
}
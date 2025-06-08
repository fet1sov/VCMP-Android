//
// Created by weikton on 08.06.2025.
//

#include "../main.h"
#include "memory.h"
#include <sys/mman.h>

#if defined(__arm__)
#define HOOK_PROC "\x01\xB4\x01\xB4\x01\x48\x01\x90\x01\xBD\x00\xBF\x00\x00\x00\x00"
#elif defined(__aarch64__)
#define HOOK_PROC "\xD6\x5F\x03\xE0\xD6\x5F\x03\xE0\xD6\x5F\x03\xE0\xD6\x5F\x03\xE0"
#endif

uintptr_t mmap_start = 0,
    mmap_end = 0,
    memlib_start = 0,
    memlib_end = 0;

void UnFuck(uintptr_t target)
{
    mprotect((void*)(target & ~(PAGE_SIZE - 1)), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void NOP(uintptr_t dest, size_t size)
{
    memset((void *)dest, 0xBF, size);
    __builtin___clear_cache((char*)dest, (char*)(dest+size));
}

void WriteMemory(uintptr_t dest, const char* src, size_t size)
{
    mprotect((void*)(dest & ~(PAGE_SIZE - 1)), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy((void*)dest, (void*)src, size);
    __builtin___clear_cache((char*)dest, (char*)(dest+size));
}

void ReadMemory(uintptr_t dest, uintptr_t src, size_t size)
{
    mprotect((void*)(src & ~(PAGE_SIZE - 1)), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy((void*)dest, (void*)src, size);
}

void InitHooks()
{
    LOGI("Hooks: Init hook system...");
    memlib_start = g_libGTAVC + MEM_START; // gzprintf
    memlib_end = memlib_start + 0x100;

    mmap_start = (uintptr_t)mmap(NULL, PAGE_SIZE, PROT_WRITE | PROT_READ | PROT_EXEC,
                                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    mprotect((void*)(mmap_start & ~(PAGE_SIZE - 1)), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    mmap_end = (mmap_start + PAGE_SIZE);
    LOGI("Hooks: Hook system initialized!");
}

#if defined(__arm__)
void JMPCode(uintptr_t func, uintptr_t addr)
{
    uint32_t code = ((addr - func - 4) >> 12) & 0x7FF |
                    0xF000 | (((((addr - func - 4) >> 1) & 0x7FF) | 0xB800) << 16);
    WriteMemory(func, (const char *)&code, 4);
}
#elif defined(__aarch64__)
void JMPCode(uintptr_t func, uintptr_t addr)
{
    uint64_t code = ((addr - func) & ~3) | 0x58000000;
    WriteMemory(func, (const char *)&code, sizeof(uint64_t));
}
#endif

void WriteHookProc(uintptr_t addr, uintptr_t func)
{
    char code[16];
    memcpy(code, HOOK_PROC, 16);
#if defined(__arm__)
    *(uint32_t *)&code[12] = (func | 1);
#else
    *(uint64_t *)&code[8] = (func | 1);
#endif
    WriteMemory(addr, (const char *)code, 16);
}

void InstallHook(uintptr_t addr, uintptr_t func, uintptr_t *orig)
{
    LOGI("Install Hook: ADDR 0x%X FUNC 0x%X", addr, func);
    if (memlib_end < (memlib_start + 0x10) || mmap_end < (mmap_start + 0x20)) {
        LOGI("Hooks: Space Limit!");
        exit(1);
    }

    ReadMemory(mmap_start, addr, 4);
    WriteHookProc(mmap_start + 4, addr + 4);
    *orig = mmap_start + 1;
    mmap_start += 32;
    JMPCode(addr, memlib_start);
    WriteHookProc(memlib_start, func);
    memlib_start += 16;
}

void InstallMethodHook(uintptr_t addr, uintptr_t func)
{
    UnFuck(addr);
#if defined(__arm__)
    *(uintptr_t *)addr = func;
#else
    *(uint64_t *)addr = func;
#endif
}
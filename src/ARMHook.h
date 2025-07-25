#pragma once
#include "main.h"
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <ctype.h>
#include <link.h>
#include <sys/cachectl.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <cstddef>
#include <sys/cdefs.h>

#if defined(__aarch64__) 
#define IS_ARM64
#else
#define IS_ARM32
#endif

#define SET_TO(__a1, __a2) *(void**)&(__a1) = (void*)(__a2)

class ARMHook
{
public:
	static uintptr_t getLibraryAddress(const char* library);
	static void InitialiseTrampolines(uintptr_t dest, uintptr_t size);
	static void unprotect(uintptr_t ptr);
	static void writeMem(uintptr_t dest, uintptr_t src, size_t size);
	static void readMem(uintptr_t dest, uintptr_t src, size_t size);
	static void makeNOP(uintptr_t addr, unsigned int count);
	static void writeMemHookProc(uintptr_t addr, uintptr_t func);
	static void JMPCode(uintptr_t func, uintptr_t addr);
	static void installHook(uintptr_t addr, uintptr_t func, uintptr_t *orig);
	static void installMethodHook(uintptr_t addr, uintptr_t func);
	static void makeRet(uintptr_t dest);
	static void putCode(uintptr_t addr, uintptr_t point, uintptr_t func);
	static void injectCode(uintptr_t addr, uintptr_t func, int reg);

	static void UnFuck(uintptr_t ptr, uint64_t len = PAGE_SIZE) 
	{
		#ifdef IS_ARM32
				if(mprotect((void*)(ptr & 0xFFFFF000), len, PROT_READ | PROT_WRITE | PROT_EXEC) == 0)
					return;
		
				mprotect((void*)(ptr & 0xFFFFF000), len, PROT_READ | PROT_WRITE);
		#else
				if(mprotect((void*)(ptr & 0xFFFFFFFFFFFFF000), len, PROT_READ | PROT_WRITE | PROT_EXEC) == 0)
					return;
		
				mprotect((void*)(ptr & 0xFFFFFFFFFFFFF000), len, PROT_READ | PROT_WRITE);
		#endif
	}

	template<typename Addr>
    static void NOP(Addr adr, size_t count)
    {
        // fully check
        auto addr = (uintptr_t)(adr);
#ifdef IS_ARM32
        int bytesCount = 2 * count;
        uintptr_t endAddr = addr + bytesCount;
        UnFuck(addr, bytesCount);
        for (uintptr_t p = addr; p != endAddr; p += 2)
        {
            (*(char*)(p + 0)) = 0x00;
            (*(char*)(p + 1)) = 0xBF;
        }
        cacheflush(addr, endAddr, 0);

#else
        if(count > 1)
            count /= 2;

        int bytesCount = 4 * count;
        uintptr_t endAddr = addr + bytesCount;
        UnFuck(addr, bytesCount);
        for (uintptr_t p = addr; p != endAddr; p += 4)
        {
            (*(char*)(p + 0)) = 0x1F;
            (*(char*)(p + 1)) = 0x20;
            (*(char*)(p + 2)) = 0x03;
            (*(char*)(p + 3)) = 0xD5;
        }
        // cacheflush(addr, endAddr, 0);
		__builtin___clear_cache((char*)(addr), (char*)(endAddr));
#endif
    }
};
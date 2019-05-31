#include "../main.h"
#include "memory.h"
#include <sys/mman.h>

void WriteMemory(uintptr_t dest, const char* src, size_t size)
{
    mprotect((void*)(dest & 0xFFFFF000), PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC);
    memcpy((void*)dest, (void*)src, size);
    __builtin___clear_cache((char*)dest, (char*)(dest+size));
}
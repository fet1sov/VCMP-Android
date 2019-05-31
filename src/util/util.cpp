#include "../main.h"
#include "util.h"

uintptr_t findLibrary(const char *library)
{
    char filename[0xFF] = {0},
    buffer[2048] = {0};
    FILE *fp = 0;
    uintptr_t address = 0;

    sprintf(filename, "/proc/%d/maps", getpid());

    fp = fopen(filename, "rt");
    if(fp == 0)
    {
        LOGI("can't open file %s", filename);
        goto done;
    }

    while(fgets(buffer, sizeof(buffer), fp))
    {
        if(strstr(buffer, library))
        {
            address = (uintptr_t)strtoul( buffer, 0, 16 );
            break;
        }
    }

    done:

    if(fp)
      fclose(fp);

    return address;
}
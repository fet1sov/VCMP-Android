//
// Created by vadim on 07.06.2025.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uintptr_t FindLibrary(const char* library)
{
    char filename[0xFF] = {0},
            buffer[2048] = {0};
    FILE *fp = 0;
    uintptr_t address = 0;

    sprintf( filename, "/proc/%d/maps", getpid() );

    fp = fopen( filename, "rt" );
    if(fp == 0)
    {
        goto done;
    }

    while(fgets(buffer, sizeof(buffer), fp))
    {
        if( strstr( buffer, library ) )
        {
            address = (uintptr_t)strtoul( buffer, 0, 16 );
            break;
        }
    }

    done:

    if(fp) {
        fclose(fp);
    }

    return address;
}
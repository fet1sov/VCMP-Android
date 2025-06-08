//
// Created by weikton on 08.06.2025.
//
#include "log.h"
#include "main.h"

void Log(const char *fmt, ...)
{
	static char buffer[512] {};
	memset(buffer, 0, sizeof(buffer));

	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, arg);
	va_end(arg);

	static FILE* flLog = nullptr;

	if(flLog == nullptr && g_pStorage != nullptr)
	{
		sprintf(buffer, "%svcmp.log", g_pStorage);
		flLog = fopen(buffer, "ab");
	}

	if(flLog == nullptr) 
		return;
	fprintf(flLog, "%s\n", buffer);
	fflush(flLog);
}
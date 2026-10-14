#pragma once

#include <Windows.h>

#include <cstdint>

enum BnLogCommand
{
	BNLOG_COMMAND_REOPEN = 1,
	BNLOG_COMMAND_INDENT = 2,
};

void __fastcall BNLOG_SetUnused(int32_t nValue);
int __cdecl BNLOG_Command(int nCommand, int nValue);
void __cdecl BNLOG_Printf(const char* szFormat, ...);

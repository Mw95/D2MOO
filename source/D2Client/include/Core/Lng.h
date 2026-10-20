#pragma once

#include <D2Client.h>


//D2Client.0x6FB9A710
extern HACCEL ghLNGAccelerators;
//D2Client.0x6FB9A718
extern char gszLNGFile[MAX_PATH];
//D2Client.0x6FB9A81C
extern HMODULE sghLNGInstance;


//D2Client.0x6FAA11E0
int32_t __fastcall LNG_RegisterCommandLineArgument();
//D2Client.0x6FAA1210
BOOL __fastcall LNG_Initialize();
//D2Client.0x6FAA1300
void __fastcall LNG_Shutdown();
//D2Client.0x6FAA1330
BOOL __stdcall LNG_GetErrorString(DWORD dwMessageId, char* szBuffer, unsigned int nBufferSize);

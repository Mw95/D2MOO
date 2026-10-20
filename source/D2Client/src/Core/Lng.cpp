#include "Core/Lng.h"

#define XFAULT_IMPL
#define XFAULT_MODULE_NAME "D2Client.dll"
#include <Fault.h>


//D2Client.0x6FB9A710
HACCEL ghLNGAccelerators;
//D2Client.0x6FB9A718
char gszLNGFile[MAX_PATH];
//D2Client.0x6FB9A81C
HMODULE sghLNGInstance;


//D2Client.0x6FAA11E0
int32_t __fastcall LNG_RegisterCommandLineArgument()
{
	SCmdRegisterArgument(0x20000, -1, (char*)"lng", (int)gszLNGFile, sizeof(gszLNGFile), 0, 0, 0);
	return TRUE;
}

//D2Client.0x6FAA1210
BOOL __fastcall LNG_Initialize()
{
	if (gszLNGFile[0])
	{
		sghLNGInstance = LoadLibraryExA(gszLNGFile, nullptr, LOAD_LIBRARY_AS_DATAFILE);
		SRegSaveString("Diablo II", "LNG File", 0, gszLNGFile);
	}

	if (!sghLNGInstance)
	{
		if (SRegLoadString("Diablo II", "LNG File", 0, gszLNGFile, sizeof(gszLNGFile)))
		{
			sghLNGInstance = LoadLibraryExA(gszLNGFile, nullptr, LOAD_LIBRARY_AS_DATAFILE);
		}

		if (!sghLNGInstance)
		{
			sghLNGInstance = LoadLibraryExA("D2.LNG", nullptr, LOAD_LIBRARY_AS_DATAFILE);
			if (!sghLNGInstance)
			{
				if (!XFaultMessage("Unable to start LNG manager."))
				{
					return FALSE;
				}

				__debugbreak();
				return FALSE;
			}
		}
	}

	ghLNGAccelerators = LoadAcceleratorsA(sghLNGInstance, MAKEINTRESOURCEA(100));
	SErrRegisterMessageSource(0xFFF, (int)sghLNGInstance, 0);
	FaultRegisterMessageSource(LNG_GetErrorString);
	return TRUE;
}

//D2Client.0x6FAA1300
void __fastcall LNG_Shutdown()
{
	if (sghLNGInstance)
	{
		FreeLibrary(sghLNGInstance);
	}

	sghLNGInstance = nullptr;
	ghLNGAccelerators = nullptr;
}

//D2Client.0x6FAA1330
BOOL __stdcall LNG_GetErrorString(DWORD dwMessageId, char* szBuffer, unsigned int nBufferSize)
{
	D2_ASSERT(sghLNGInstance);

	if (!SErrGetErrorStr(dwMessageId, szBuffer, nBufferSize))
	{
		lstrcpynA(szBuffer, "Stupid Lng.cpp error.", nBufferSize);
		return FALSE;
	}

	return TRUE;
}

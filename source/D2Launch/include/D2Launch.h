#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Config.h>

#ifdef D2_VERSION_110F
constexpr int D2LaunchImageBase = 0x6FA10000;
#endif

#pragma pack(push, 1)
// Returned by QueryInterface, used by Game.exe to run the launcher
struct D2LaunchInterfaceStrc
{
	int32_t(__fastcall* pfRun)(D2ConfigStrc* pConfig);	//0x00 Returns the next module to be run by the game (see D2_MODULES in Game.exe)
};
#pragma pack(pop)

extern HINSTANCE ghD2LaunchInstance;

//D2Launch.0x6FA17740 (#1)
extern "C" D2LAUNCH_DLL_DECL D2LaunchInterfaceStrc* __cdecl QueryInterface();

#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2BasicTypes.h>
#include <D2Config.h>

//1.10f Image Base: 0x6F9A0000

#ifdef D2_VERSION_110F
constexpr int D2MultiImageBase = 0x6F9A0000;
#endif

// Interface returned by QueryInterface, used by Game.exe to run the module
struct D2MultiInterfaceStrc
{
	int32_t(__fastcall* pfRunModule)(D2ConfigStrc* pConfig);	//0x00 Returns the next module to run
};

//D2Multi.0x6F9AF3B0 (#1)
extern "C" D2MULTI_DLL_DECL D2MultiInterfaceStrc* __cdecl QueryInterface();

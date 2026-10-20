#pragma once

#include <D2Dll.h>
#include <cstdint>

//1.10f Image Base: 0x6F980000

#ifdef D2_VERSION_110F
constexpr int D2SoundImageBase = 0x6F980000;
#endif

#if D2_VERSION_MAJOR >= 1 && D2_VERSION_MINOR >= 13
D2FUNC_DLL(D2SOUND, OpenSoundSystem, void, __fastcall, (BOOL bExpansion, BOOL bSoundBackground), 0x0000/*TODO*/)	//D2Sound.#10002
#else
D2FUNC_DLL(D2SOUND, OpenSoundSystem, void, __fastcall, (BOOL bExpansion), 0x10E0)					//D2Sound.#10000
#endif
D2FUNC_DLL(D2SOUND, CloseSoundSystem, void, __fastcall, (), 0x21C0)									//D2Sound.#10001
D2FUNC_DLL(D2SOUND, 10034, void, __fastcall, (int), 0x4D60)											//D2Sound.#10034
D2FUNC_DLL(D2SOUND, 10039, void, __fastcall, (const char*), 0x2800)									//D2Sound.#10039
D2FUNC_DLL(D2SOUND, 10048, void*, __fastcall, (), 0x2B30)											//D2Sound.#10048
D2FUNC_DLL(D2SOUND, 10049, void, __fastcall, (void*), 0x2B40)										//D2Sound.#10049
D2FUNC_DLL(D2SOUND, 10065, void, __fastcall, (), 0x49D0)											//D2Sound.#10065
D2FUNC_DLL(D2SOUND, 10066, int, __fastcall, (), 0x2990)												//D2Sound.#10066
D2FUNC_DLL(D2SOUND, 10069, int, __fastcall, (), 0x2BC0)												//D2Sound.#10069
D2FUNC_DLL(D2SOUND, 10070, void, __fastcall, (int), 0x2BD0)											//D2Sound.#10070

// Used by D2Client, signatures inferred from D2Client call sites
D2FUNC_DLL(D2SOUND, 10002, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10002
D2FUNC_DLL(D2SOUND, 10003, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10003
D2FUNC_DLL(D2SOUND, 10004, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10004
D2FUNC_DLL(D2SOUND, 10006, void, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10006
D2FUNC_DLL(D2SOUND, 10007, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10007
D2FUNC_DLL(D2SOUND, 10008, void, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10008
D2FUNC_DLL(D2SOUND, 10009, void, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10009
D2FUNC_DLL(D2SOUND, 10010, int32_t, __fastcall, (int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10010
D2FUNC_DLL(D2SOUND, 10011, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10011
D2FUNC_DLL(D2SOUND, 10012, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10012
D2FUNC_DLL(D2SOUND, 10013, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10013
D2FUNC_DLL(D2SOUND, 10014, int32_t, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10014
D2FUNC_DLL(D2SOUND, 10016, void, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10016
D2FUNC_DLL(D2SOUND, 10017, void, __fastcall, (int32_t, int32_t, int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10017
D2FUNC_DLL(D2SOUND, 10018, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10018
D2FUNC_DLL(D2SOUND, 10019, void, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10019
D2FUNC_DLL(D2SOUND, 10020, void, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10020
D2FUNC_DLL(D2SOUND, 10021, void, __fastcall, (int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10021
D2FUNC_DLL(D2SOUND, 10022, int32_t, __fastcall, (int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10022
D2FUNC_DLL(D2SOUND, 10023, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10023
D2FUNC_DLL(D2SOUND, 10025, int32_t, __fastcall, (int32_t, int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10025
D2FUNC_DLL(D2SOUND, 10027, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10027
D2FUNC_DLL(D2SOUND, 10029, void, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10029
D2FUNC_DLL(D2SOUND, 10031, void, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10031
D2FUNC_DLL(D2SOUND, 10032, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10032
D2FUNC_DLL(D2SOUND, 10044, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10044
D2FUNC_DLL(D2SOUND, 10045, void, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10045
D2FUNC_DLL(D2SOUND, 10046, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10046
D2FUNC_DLL(D2SOUND, 10047, void, __fastcall, (int32_t nVolume), 0x0000/*TODO*/)	//D2Sound.#10047
D2FUNC_DLL(D2SOUND, 10050, int32_t, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10050
D2FUNC_DLL(D2SOUND, 10051, void, __fastcall, (int32_t nVolume), 0x0000/*TODO*/)	//D2Sound.#10051
D2FUNC_DLL(D2SOUND, 10052, int32_t, __stdcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10052
D2FUNC_DLL(D2SOUND, 10053, void, __fastcall, (int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10053
D2FUNC_DLL(D2SOUND, 10056, int32_t, __fastcall, (int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10056
D2FUNC_DLL(D2SOUND, 10057, void, __fastcall, (int32_t, int32_t, int32_t, int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10057
D2FUNC_DLL(D2SOUND, 10058, int32_t, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10058
D2FUNC_DLL(D2SOUND, 10059, void, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10059
D2FUNC_DLL(D2SOUND, 10060, int32_t, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10060
D2FUNC_DLL(D2SOUND, 10062, int32_t, __fastcall, (int32_t), 0x0000/*TODO*/)	//D2Sound.#10062
D2FUNC_DLL(D2SOUND, 10063, int32_t, __fastcall, (int32_t, int32_t), 0x0000/*TODO*/)	//D2Sound.#10063
D2FUNC_DLL(D2SOUND, 10064, void, __stdcall, (), 0x0000/*TODO*/)	//D2Sound.#10064

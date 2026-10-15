#pragma once

#include <D2BasicTypes.h>
#include <D2BuildInformation.h>
#include <Windows.h>
#include <cstdint>

#include "D2SoundFast.h"
#include "D2SoundSettings.h"
#include "D2SoundSmp.h"
#include "D2SoundStrm.h"
#include "D2SoundUtil.h"

//1.10f Image Base: 0x6F980000

#ifdef D2_VERSION_110F
constexpr int D2SoundImageBase = 0x6F980000;
#endif

struct IDirectSound;

#pragma pack(push, 1)
// Mirrors the EAX 2.0 listener properties (see DSPROPERTY_EAXLISTENER_*)
struct D2SoundEnvironmentStrc
{
	uint32_t dwEnvironment;					//0x00
	float flEnvironmentSize;				//0x04
	float flEnvironmentDiffusion;			//0x08
	int32_t lRoom;							//0x0C
	int32_t lRoomHF;						//0x10
	float flDecayTime;						//0x14
	float flDecayHFRatio;					//0x18
	int32_t lReflections;					//0x1C
	float flReflectionsDelay;				//0x20
	int32_t lReverb;						//0x24
	float flReverbDelay;					//0x28
	float flRoomRolloffFactor;				//0x2C
	float flAirAbsorptionHF;				//0x30
};
#pragma pack(pop)


//D2Sound.0x6F9810E0 (#10000)
#if D2_VERSION_MAJOR >= 1 && D2_VERSION_MINOR >= 13
// 1.13+ is #10002 and takes an extra parameter, which is currently ignored by this implementation.
D2SOUND_DLL_DECL void __fastcall D2SOUND_OpenSoundSystem(BOOL bExpansion, BOOL bSoundBackground);
#else
D2SOUND_DLL_DECL void __fastcall D2SOUND_OpenSoundSystem(BOOL bExpansion);
#endif
//D2Sound.0x6F9821C0 (#10001)
D2SOUND_DLL_DECL void __fastcall D2SOUND_CloseSoundSystem();
//D2Sound.0x6F9822B0 (#10002)
D2SOUND_DLL_DECL IDirectSound* __fastcall D2SOUND_GetDirectSound();
//D2Sound.0x6F9822C0 (#10003)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_Is3DEnabled();
//D2Sound.0x6F9822D0 (#10004)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsEAXEnabled();
//D2Sound.0x6F9822E0 (#10005)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_10005();
//D2Sound.0x6F9823C0 (#10006)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetEnvironment(const D2SoundEnvironmentStrc* pEnvironment);
//D2Sound.0x6F9848E0 (#10067)
D2SOUND_DLL_DECL void __fastcall D2SOUND_10067();
//D2Sound.0x6F9848E0 (#10068)
D2SOUND_DLL_DECL void __fastcall D2SOUND_10068();


// Internal functions (not exported)

//D2Sound.0x6F9810D0
BOOL __fastcall SOUND_IsExpansion();
//D2Sound.0x6F9822F0
int32_t __fastcall SOUND_GetEAXVersion();
//D2Sound.0x6F982300
BOOL __fastcall SOUND_IsReverbOff();
//D2Sound.0x6F982310
BOOL __fastcall SOUND_CanReuseSampleBuffers();
//Inlined
void __fastcall SOUND_EnterCriticalSection();
//Inlined
void __fastcall SOUND_LeaveCriticalSection();

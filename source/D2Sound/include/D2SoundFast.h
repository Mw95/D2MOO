#pragma once

#include <D2BasicTypes.h>
#include <Windows.h>
#include <cstdint>

#pragma pack(push, 1)
// Cached .wav file for sounds that must play without delay (UI sounds)
struct D2SoundFastSoundStrc
{
	char szFileName[80];					//0x00
	void* pFileData;						//0x50
	uint32_t dwFileSize;					//0x54
	BOOL bStereo;							//0x58
	D2SoundFastSoundStrc* pNext;			//0x5C
};
#pragma pack(pop)


//D2Sound.0x6F982630 (#10036)
D2SOUND_DLL_DECL void __fastcall D2SOUND_InitFastSounds();
//D2Sound.0x6F9826A0 (#10037)
D2SOUND_DLL_DECL void __fastcall D2SOUND_ShutdownFastSounds();
//D2Sound.0x6F982750 (#10038)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LoadFastSound(const char* szFileName);
//D2Sound.0x6F982800 (#10039)
D2SOUND_DLL_DECL void __fastcall D2SOUND_PlayFastSound(const char* szFileName);
//D2Sound.0x6F9828F0 (#10040)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsAnyFastSoundPlaying();
//D2Sound.0x6F982920 (#10041)
D2SOUND_DLL_DECL void __fastcall D2SOUND_StopFastSounds();
//D2Sound.0x6F982950 (#10042)
D2SOUND_DLL_DECL void __fastcall D2SOUND_FadeOutFastSounds();
//D2Sound.0x6F982990 (#10066)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_AreFastSoundsInitialized();

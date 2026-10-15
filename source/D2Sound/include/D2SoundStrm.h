#pragma once

#include <D2BasicTypes.h>
#include <Windows.h>
#include <cstdint>

#pragma pack(push, 1)
struct D2SoundStreamTrackStrc
{
	const char* szFileName;					//0x00
	BOOL bPlayed;							//0x04
};
#pragma pack(pop)


//D2Sound.0x6F984930 (#10030)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_PlayMusic(const char* szFileName, BOOL bLoop);
//D2Sound.0x6F9849A0 (#10031)
D2SOUND_DLL_DECL void __fastcall D2SOUND_StopMusic();
//D2Sound.0x6F9849D0 (#10065)
D2SOUND_DLL_DECL void __fastcall D2SOUND_FadeOutMusic();
//D2Sound.0x6F984A00 (#10032)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsMusicPlaying();
//D2Sound.0x6F984A20 (#10033)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_PlayNextRandomTrack();
//D2Sound.0x6F984D60 (#10034)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetRandomMusic(BOOL bEnable);
//D2Sound.0x6F984E20 (#10035)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsRandomMusicEnabled();


// Internal functions (not exported)

//D2Sound.0x6F9848F0
void __fastcall STREAM_Initialize();
//D2Sound.0x6F984910
void __fastcall STREAM_Shutdown();

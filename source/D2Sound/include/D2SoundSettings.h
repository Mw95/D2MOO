#pragma once

#include <D2BasicTypes.h>
#include <Windows.h>
#include <cstdint>

// Sound options, stored in the registry under "Diablo II"

//D2Sound.0x6F9829A0 (#10043)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LoadSettings();
//D2Sound.0x6F982AD0 (#10044)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetSoundMixerSetting();
//D2Sound.0x6F982AE0 (#10045)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetSoundMixerSetting(int32_t nValue);
//D2Sound.0x6F982B00 (#10046)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetMasterVolumeSetting();
//D2Sound.0x6F982B10 (#10047)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetMasterVolumeSetting(int32_t nValue);
//D2Sound.0x6F982B30 (#10048)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetMusicVolumeSetting();
//D2Sound.0x6F982B40 (#10049)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetMusicVolumeSetting(int32_t nValue);
//D2Sound.0x6F982B60 (#10050)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetPositionalBiasSetting();
//D2Sound.0x6F982B70 (#10051)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetPositionalBiasSetting(int32_t nValue);
//D2Sound.0x6F982B90 (#10052)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetNPCSpeechSetting();
//D2Sound.0x6F982BA0 (#10053)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetNPCSpeechSetting(int32_t nValue);
//D2Sound.0x6F982BC0 (#10069)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetOptionsMusicSetting();
//D2Sound.0x6F982BD0 (#10070)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_SetOptionsMusicSetting(int32_t nValue);

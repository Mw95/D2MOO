#include "D2SoundSettings.h"

#include <Storm.h>


static const char* const gszRegistryKey = "Diablo II";

int32_t gnSoundMixerSetting;							//D2Sound.0x6F992D30
int32_t gnMasterVolumeSetting;							//D2Sound.0x6F992D34
int32_t gnMusicVolumeSetting;							//D2Sound.0x6F992D38
int32_t gnPositionalBiasSetting;						//D2Sound.0x6F992D3C
int32_t gnNPCSpeechSetting;								//D2Sound.0x6F992D40
int32_t gnOptionsMusicSetting;							//D2Sound.0x6F992D44


// Inlined
static void SETTINGS_LoadValue(const char* szValueName, int32_t* pSetting, uint32_t nMaxValue)
{
	DWORD dwValue;
	if (SRegLoadValue(gszRegistryKey, szValueName, 0, &dwValue) && dwValue <= nMaxValue)
	{
		*pSetting = dwValue;
	}
}

// Inlined
static int32_t SETTINGS_SaveValue(const char* szValueName, int32_t* pSetting, int32_t nValue)
{
	SRegSaveValue(gszRegistryKey, szValueName, 0, nValue);
	*pSetting = nValue;
	return nValue;
}

//D2Sound.0x6F9829A0 (#10043)
void __fastcall D2SOUND_LoadSettings()
{
	gnSoundMixerSetting = 0;
	gnMusicVolumeSetting = 50;
	gnPositionalBiasSetting = 50;
	gnMasterVolumeSetting = 100;
	gnNPCSpeechSetting = 2;
	gnOptionsMusicSetting = 1;

	SETTINGS_LoadValue("Sound Mixer", &gnSoundMixerSetting, 2);
	SETTINGS_LoadValue("Master Volume", &gnMasterVolumeSetting, 100);
	SETTINGS_LoadValue("Music Volume", &gnMusicVolumeSetting, 100);
	SETTINGS_LoadValue("Positional Bias", &gnPositionalBiasSetting, 100);
	SETTINGS_LoadValue("NPC Speech", &gnNPCSpeechSetting, 2);
	SETTINGS_LoadValue("Options Music", &gnOptionsMusicSetting, 1);
}

//D2Sound.0x6F982AD0 (#10044)
int32_t __fastcall D2SOUND_GetSoundMixerSetting()
{
	return gnSoundMixerSetting;
}

//D2Sound.0x6F982AE0 (#10045)
int32_t __fastcall D2SOUND_SetSoundMixerSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("Sound Mixer", &gnSoundMixerSetting, nValue);
}

//D2Sound.0x6F982B00 (#10046)
int32_t __fastcall D2SOUND_GetMasterVolumeSetting()
{
	return gnMasterVolumeSetting;
}

//D2Sound.0x6F982B10 (#10047)
int32_t __fastcall D2SOUND_SetMasterVolumeSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("Master Volume", &gnMasterVolumeSetting, nValue);
}

//D2Sound.0x6F982B30 (#10048)
int32_t __fastcall D2SOUND_GetMusicVolumeSetting()
{
	return gnMusicVolumeSetting;
}

//D2Sound.0x6F982B40 (#10049)
int32_t __fastcall D2SOUND_SetMusicVolumeSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("Music Volume", &gnMusicVolumeSetting, nValue);
}

//D2Sound.0x6F982B60 (#10050)
int32_t __fastcall D2SOUND_GetPositionalBiasSetting()
{
	return gnPositionalBiasSetting;
}

//D2Sound.0x6F982B70 (#10051)
int32_t __fastcall D2SOUND_SetPositionalBiasSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("Positional Bias", &gnPositionalBiasSetting, nValue);
}

//D2Sound.0x6F982B90 (#10052)
int32_t __fastcall D2SOUND_GetNPCSpeechSetting()
{
	return gnNPCSpeechSetting;
}

//D2Sound.0x6F982BA0 (#10053)
int32_t __fastcall D2SOUND_SetNPCSpeechSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("NPC Speech", &gnNPCSpeechSetting, nValue);
}

//D2Sound.0x6F982BC0 (#10069)
int32_t __fastcall D2SOUND_GetOptionsMusicSetting()
{
	return gnOptionsMusicSetting;
}

//D2Sound.0x6F982BD0 (#10070)
int32_t __fastcall D2SOUND_SetOptionsMusicSetting(int32_t nValue)
{
	return SETTINGS_SaveValue("Options Music", &gnOptionsMusicSetting, nValue);
}

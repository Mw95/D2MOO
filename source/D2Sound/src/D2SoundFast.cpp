#include <cstring>

#include <Windows.h>
#include <mmsystem.h>

#include "D2SoundFast.h"

#include <Archive.h>
#include <Fog.h>

#include "D2Sound.h"


constexpr int32_t NUM_FAST_SAMPLES = 8;
constexpr int32_t NUM_FAST_STEREO_SAMPLES = 4;

D2SoundSampleStrc* gpFastSamples[NUM_FAST_SAMPLES];		//D2Sound.0x6F992CF0
CRITICAL_SECTION gFastSoundsCriticalSection;			//D2Sound.0x6F992D10
BOOL gbFastSoundsInitialized;							//D2Sound.0x6F992D28
D2SoundFastSoundStrc* gpFastSoundsList;					//D2Sound.0x6F992D2C


//D2Sound.0x6F982630 (#10036)
void __fastcall D2SOUND_InitFastSounds()
{
	if (!D2SOUND_GetDirectSound() || gbFastSoundsInitialized)
	{
		return;
	}

	InitializeCriticalSection(&gFastSoundsCriticalSection);
	EnterCriticalSection(&gFastSoundsCriticalSection);

	D2SOUND_SetMasterVolume(255);

	for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
	{
		gpFastSamples[i] = D2SOUND_CreateSample(i < NUM_FAST_STEREO_SAMPLES ? (uint32_t)SAMPLEFLAG_STEREO : 0);
	}

	gbFastSoundsInitialized = TRUE;
	LeaveCriticalSection(&gFastSoundsCriticalSection);
}

//D2Sound.0x6F9826A0 (#10037)
void __fastcall D2SOUND_ShutdownFastSounds()
{
	if (!gbFastSoundsInitialized)
	{
		return;
	}

	EnterCriticalSection(&gFastSoundsCriticalSection);

	if (gbFastSoundsInitialized)
	{
		for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
		{
			D2SOUND_StopSample(gpFastSamples[i]);
		}
	}

	for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
	{
		D2SOUND_DestroySample(gpFastSamples[i]);
		gpFastSamples[i] = nullptr;
	}

	while (gpFastSoundsList)
	{
		D2SoundFastSoundStrc* pNext = gpFastSoundsList->pNext;
		if (gpFastSoundsList->pFileData)
		{
			D2_FREE(gpFastSoundsList->pFileData);
		}
		D2_FREE(gpFastSoundsList);
		gpFastSoundsList = pNext;
	}

	gbFastSoundsInitialized = FALSE;
	// Note: The critical section is deleted while still being owned, as in the original game.
	DeleteCriticalSection(&gFastSoundsCriticalSection);
}

//D2Sound.0x6F982750 (#10038)
void __fastcall D2SOUND_LoadFastSound(const char* szFileName)
{
	if (!gbFastSoundsInitialized)
	{
		return;
	}

	size_t nFileSize = 0;
	void* pFileData = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(nullptr, szFileName, &nFileSize);
	if (!pFileData)
	{
		return;
	}

	uint32_t dwDataSize = nFileSize;
	WAVEFORMATEX tWaveFormat = {};
	D2SOUND_ParseWave(pFileData, &dwDataSize, &tWaveFormat);
	if (tWaveFormat.nSamplesPerSec != 22050)
	{
		// Note: pFileData is leaked, as in the original game.
		return;
	}

	D2SoundFastSoundStrc* pFastSound = D2_ALLOC_STRC(D2SoundFastSoundStrc);
	pFastSound->pNext = gpFastSoundsList;
	gpFastSoundsList = pFastSound;
	pFastSound->pFileData = pFileData;
	pFastSound->dwFileSize = nFileSize;
	pFastSound->bStereo = tWaveFormat.nChannels == 2;
	strcpy(pFastSound->szFileName, szFileName);
}

//D2Sound.0x6F982800 (#10039)
void __fastcall D2SOUND_PlayFastSound(const char* szFileName)
{
	if (!gbFastSoundsInitialized)
	{
		return;
	}

	EnterCriticalSection(&gFastSoundsCriticalSection);

	D2SoundFastSoundStrc* pFastSound = gpFastSoundsList;
	while (pFastSound && strcmp(pFastSound->szFileName, szFileName))
	{
		pFastSound = pFastSound->pNext;
	}

	if (!pFastSound)
	{
		LeaveCriticalSection(&gFastSoundsCriticalSection);
		return;
	}

	for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
	{
		D2SoundSampleStrc* ptSample = gpFastSamples[i];
		if ((BOOL)ptSample->dwFlags == pFastSound->bStereo && !D2SOUND_IsSamplePlaying(ptSample))
		{
			D2SOUND_ResetSample(ptSample);
			D2SOUND_SetSampleData(ptSample, pFastSound->pFileData, pFastSound->dwFileSize);
			D2SOUND_SetSampleVolume(ptSample, 255);
			D2SOUND_PlaySample(ptSample);
			break;
		}
	}

	LeaveCriticalSection(&gFastSoundsCriticalSection);
}

//D2Sound.0x6F9828F0 (#10040)
BOOL __fastcall D2SOUND_IsAnyFastSoundPlaying()
{
	if (gbFastSoundsInitialized)
	{
		for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
		{
			if (D2SOUND_IsSamplePlaying(gpFastSamples[i]))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

//D2Sound.0x6F982920 (#10041)
void __fastcall D2SOUND_StopFastSounds()
{
	if (gbFastSoundsInitialized)
	{
		for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
		{
			D2SOUND_StopSample(gpFastSamples[i]);
		}
	}
}

//D2Sound.0x6F982950 (#10042)
void __fastcall D2SOUND_FadeOutFastSounds()
{
	if (gbFastSoundsInitialized)
	{
		for (int32_t i = 0; i < NUM_FAST_SAMPLES; ++i)
		{
			if (D2SOUND_IsSamplePlaying(gpFastSamples[i]))
			{
				D2SOUND_FadeSample(gpFastSamples[i], 0, 200);
			}
		}
	}
}

//D2Sound.0x6F982990 (#10066)
BOOL __fastcall D2SOUND_AreFastSoundsInitialized()
{
	return gbFastSoundsInitialized;
}

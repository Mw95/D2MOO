#include <cstdlib>

#include <Windows.h>

#include "D2SoundStrm.h"

#include <Fog.h>
#include <Storm.h>

#include "D2Sound.h"


constexpr int32_t MUSIC_VOLUME = 110;

//D2Sound.0x6F98F808
D2SoundStreamTrackStrc gaStreamTracks[] =
{
	{ "data\\global\\music\\common\\options.wav", FALSE },
	{ "data\\global\\music\\act1\\caves.wav", FALSE },
	{ "data\\global\\music\\act1\\monastery.wav", FALSE },
	{ "data\\global\\music\\act1\\crypt.wav", FALSE },
	{ "data\\global\\music\\act2\\harem.wav", FALSE },
	{ "data\\global\\music\\act2\\tombs.wav", FALSE },
	{ "data\\global\\music\\act3\\spider.wav", FALSE },
	{ "data\\global\\music\\act3\\kurastsewer.wav", FALSE },
};
int32_t sgnStreamTrackCount = ARRAY_SIZE(gaStreamTracks);	//D2Sound.0x6F98F848

//D2Sound.0x6F98F850
D2SoundStreamTrackStrc gaStreamTracksEx[] =
{
	{ "data\\global\\music\\introedit.wav", FALSE },
	{ "data\\global\\music\\act5\\icecaves.wav", FALSE },
	{ "data\\global\\music\\act5\\xtemple.wav", FALSE },
	{ "data\\global\\music\\act2\\desert.wav", FALSE },
	{ "data\\global\\music\\act2\\sewer.wav", FALSE },
	{ "data\\global\\music\\act3\\kurast.wav", FALSE },
	{ "data\\global\\music\\act3\\kurastsewer.wav", FALSE },
	{ "data\\global\\music\\act4\\diablo.wav", FALSE },
};
int32_t sgnStreamTrackCountEx = ARRAY_SIZE(gaStreamTracksEx);	//D2Sound.0x6F98F890

D2SoundSampleStrc* gpMusicSample;						//D2Sound.0x6F992D58
BOOL gbRandomMusicEnabled;								//D2Sound.0x6F992D5C
BOOL gbPlayFirstTrack;									//D2Sound.0x6F992D60
BOOL gbStreamTracksExpansionChecked;					//D2Sound.0x6F992D64
BOOL gbStreamTracksExpansion;							//D2Sound.0x6F992D68


// Inlined
static D2SoundStreamTrackStrc* STREAM_GetTrack(int32_t nIndex)
{
	if (!gbStreamTracksExpansionChecked)
	{
		gbStreamTracksExpansionChecked = TRUE;
		gbStreamTracksExpansion = SOUND_IsExpansion();
	}

	D2_ASSERT(sgnStreamTrackCount == sgnStreamTrackCountEx);
	D2_ASSERT(nIndex < sgnStreamTrackCount);

	if (gbStreamTracksExpansion)
	{
		return &gaStreamTracksEx[nIndex];
	}

	return &gaStreamTracks[nIndex];
}

//D2Sound.0x6F9848F0
void __fastcall STREAM_Initialize()
{
	SFileDdaInitialize(D2SOUND_GetDirectSound());
	gpMusicSample = D2SOUND_CreateSample(SAMPLEFLAG_STEREO);
}

//D2Sound.0x6F984910
void __fastcall STREAM_Shutdown()
{
	if (gpMusicSample)
	{
		D2SOUND_DestroySample(gpMusicSample);
		gpMusicSample = nullptr;
	}

	SFileDdaDestroy();
}

//D2Sound.0x6F984930 (#10030)
BOOL __fastcall D2SOUND_PlayMusic(const char* szFileName, BOOL bLoop)
{
	if (gpMusicSample && D2SOUND_GetMasterVolume() && !D2SOUND_IsSampleStreaming(gpMusicSample) && szFileName)
	{
		D2SOUND_ResetSample(gpMusicSample);
		D2SOUND_SetSampleVolume(gpMusicSample, MUSIC_VOLUME);
		if (D2SOUND_OpenSampleStream(gpMusicSample, szFileName, 0, bLoop))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//D2Sound.0x6F9849A0 (#10031)
void __fastcall D2SOUND_StopMusic()
{
	if (gpMusicSample)
	{
		gbRandomMusicEnabled = FALSE;
		if (D2SOUND_IsSampleStreaming(gpMusicSample))
		{
			D2SOUND_StopSample(gpMusicSample);
		}
	}
}

//D2Sound.0x6F9849D0 (#10065)
void __fastcall D2SOUND_FadeOutMusic()
{
	if (gpMusicSample)
	{
		gbRandomMusicEnabled = FALSE;
		if (D2SOUND_IsSampleStreaming(gpMusicSample))
		{
			D2SOUND_FadeSample(gpMusicSample, 0, 200);
		}
	}
}

//D2Sound.0x6F984A00 (#10032)
BOOL __fastcall D2SOUND_IsMusicPlaying()
{
	return gpMusicSample && D2SOUND_IsSampleStreaming(gpMusicSample);
}

//D2Sound.0x6F984A20 (#10033)
BOOL __fastcall D2SOUND_PlayNextRandomTrack()
{
	SOUND_EnterCriticalSection();

	if (!gpMusicSample || !D2SOUND_GetMasterVolume() || D2SOUND_IsMusicPlaying())
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	BOOL bTracksReset = FALSE;
	while (true)
	{
		BOOL bHasUnplayedTrack = FALSE;
		for (int32_t i = 0; i < sgnStreamTrackCount; ++i)
		{
			if (!STREAM_GetTrack(i)->bPlayed)
			{
				bHasUnplayedTrack = TRUE;
				break;
			}
		}

		if (!bHasUnplayedTrack)
		{
			if (bTracksReset)
			{
				// No track could be played
				gbRandomMusicEnabled = FALSE;
				SOUND_LeaveCriticalSection();
				return FALSE;
			}

			for (int32_t i = 0; i < sgnStreamTrackCount; ++i)
			{
				STREAM_GetTrack(i)->bPlayed = FALSE;
			}

			bTracksReset = TRUE;
		}

		D2SoundStreamTrackStrc* pTrack = nullptr;
		if (gbPlayFirstTrack)
		{
			pTrack = STREAM_GetTrack(0);
			gbPlayFirstTrack = FALSE;
		}
		else
		{
			int32_t nIndex = rand() % sgnStreamTrackCount;
			while (STREAM_GetTrack(nIndex)->bPlayed)
			{
				++nIndex;
				if (nIndex >= sgnStreamTrackCount)
				{
					nIndex = 0;
				}
			}
			pTrack = STREAM_GetTrack(nIndex);
		}

		pTrack->bPlayed = TRUE;

		if (D2SOUND_PlayMusic(pTrack->szFileName, FALSE))
		{
			SOUND_LeaveCriticalSection();
			return TRUE;
		}
	}
}

//D2Sound.0x6F984D60 (#10034)
void __fastcall D2SOUND_SetRandomMusic(BOOL bEnable)
{
	if (bEnable && !gbRandomMusicEnabled)
	{
		for (int32_t i = 0; i < sgnStreamTrackCount; ++i)
		{
			STREAM_GetTrack(i)->bPlayed = FALSE;
		}

		gbPlayFirstTrack = TRUE;
	}

	gbRandomMusicEnabled = bEnable;
}

//D2Sound.0x6F984E20 (#10035)
BOOL __fastcall D2SOUND_IsRandomMusicEnabled()
{
	return gbRandomMusicEnabled;
}

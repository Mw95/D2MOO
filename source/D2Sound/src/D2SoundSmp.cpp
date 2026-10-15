#include <cstring>

#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>

#include "D2SoundSmp.h"

#include <Fog.h>
#include <Storm.h>
#include <Window.h>

#include "D2Sound.h"
#include "D2SoundEAX.h"


constexpr int32_t MIN_VOLUME = 0;
constexpr int32_t MAX_VOLUME = 255;

D2SoundListStrc* gpSampleList;							//D2Sound.0x6F992D48
HANDLE ghMixerThreadEvent;								//D2Sound.0x6F992D4C
HANDLE sghThreadHandle;									//D2Sound.0x6F992D50
BOOL gbIsIconic;										//D2Sound.0x6F992D54
int32_t gnMasterVolume = MAX_VOLUME;					//D2Sound.0x6F98F64C


//D2Sound.0x6F9832F0
static BOOL __fastcall SAMPLE_WriteData(D2SoundSampleStrc* ptSample, uint32_t dwRawOffset, uint32_t dwBufferOffset, uint32_t dwWriteLength)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer && ptSample->pbRawData && dwWriteLength);

	SOUND_EnterCriticalSection();

	void* pLockedBuffer = nullptr;
	DWORD dwLockedSize = dwWriteLength;
	if (FAILED(ptSample->ptSoundBuffer->Lock(dwBufferOffset, dwWriteLength, &pLockedBuffer, &dwLockedSize, nullptr, nullptr, 0)))
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	uint8_t* pWrite = (uint8_t*)pLockedBuffer;
	do
	{
		if (dwRawOffset >= ptSample->dwRawSize)
		{
			dwRawOffset = (dwRawOffset - ptSample->dwLoopBlockStart) % (ptSample->dwRawSize - ptSample->dwLoopBlockStart) + ptSample->dwLoopBlockStart;
		}

		int32_t nCopySize = ptSample->dwRawSize - dwRawOffset;
		if ((int32_t)dwWriteLength < nCopySize)
		{
			nCopySize = dwWriteLength;
		}

		memcpy(pWrite, &ptSample->pbRawData[dwRawOffset], nCopySize);
		dwRawOffset += nCopySize;
		ptSample->dwWritePosition += nCopySize;
		pWrite += nCopySize;
		dwWriteLength -= nCopySize;
		dwBufferOffset += nCopySize;
	}
	while (ptSample->bLoop && dwWriteLength);

	if (!ptSample->bLoop && dwWriteLength)
	{
		BOOL bFillSilence = TRUE;
		if (ptSample->dwDataEndOffset != (uint32_t)-1)
		{
			if (dwBufferOffset >= ptSample->dwDataEndOffset)
			{
				bFillSilence = FALSE;
			}
			else
			{
				dwWriteLength = ptSample->dwDataEndOffset - dwBufferOffset;
			}
		}

		if (bFillSilence && dwWriteLength)
		{
			memset(pWrite, 0, dwWriteLength);
		}
	}

	ptSample->ptSoundBuffer->Unlock(pLockedBuffer, dwLockedSize, nullptr, 0);

	if (!ptSample->bLoop && ptSample->dwWritePosition >= ptSample->dwRawSize)
	{
		ptSample->bWriteComplete = TRUE;
	}

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F9834A0
static BOOL __fastcall SAMPLE_RestoreLostBuffer(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample->ptSoundBuffer);

	SOUND_EnterCriticalSection();

	DWORD dwStatus;
	if (FAILED(ptSample->ptSoundBuffer->GetStatus(&dwStatus)))
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	if (dwStatus & DSBSTATUS_BUFFERLOST)
	{
		while (true)
		{
			const HRESULT hResult = ptSample->ptSoundBuffer->Restore();
			if (hResult == DSERR_BUFFERLOST)
			{
				Sleep(10);
			}
			else if (SUCCEEDED(hResult))
			{
				break;
			}
		}

		D2SOUND_StopSample(ptSample);
	}

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F982C50
static DWORD __stdcall SAMPLE_MixerThreadProc(void* pParameter)
{
	D2_MAYBE_UNUSED(pParameter);

	while (WaitForSingleObject(ghMixerThreadEvent, 50) == WAIT_TIMEOUT)
	{
		SOUND_EnterCriticalSection();

		const BOOL bWasIconic = gbIsIconic;
		gbIsIconic = IsIconic(WINDOW_GetWindow());

		if (D2SOUND_IsRandomMusicEnabled() && !D2SOUND_IsMusicPlaying())
		{
			D2SOUND_PlayNextRandomTrack();
		}

		for (D2SoundListStrc* pNode = gpSampleList; pNode; pNode = pNode->pNext)
		{
			D2SoundSampleStrc* ptSample = (D2SoundSampleStrc*)pNode->pData;

			SAMPLE_RestoreLostBuffer(ptSample);

			if (gbIsIconic != bWasIconic)
			{
				D2SOUND_SetSampleVolume(ptSample, ptSample->nVolume);
			}

			if (ptSample->bFading)
			{
				const int32_t nTickCount = GetTickCount();
				if (nTickCount >= ptSample->nFadeStartTick && nTickCount <= ptSample->nFadeEndTick)
				{
					const int32_t nVolume = ptSample->nFadeStartVolume + (ptSample->nFadeEndVolume - ptSample->nFadeStartVolume) * (nTickCount - ptSample->nFadeStartTick) / (ptSample->nFadeEndTick - ptSample->nFadeStartTick);
					D2SOUND_SetSampleVolume(ptSample, nVolume);
				}
				else
				{
					D2SOUND_SetSampleVolume(ptSample, ptSample->nFadeEndVolume);
					if (!ptSample->nFadeEndVolume)
					{
						D2SOUND_StopSample(ptSample);
					}
					ptSample->bFading = FALSE;
				}
			}

			if (ptSample->hStreamFile)
			{
				uint32_t dwPosition;
				uint32_t dwMaxPosition;
				if (!SFileDdaGetPos(ptSample->hStreamFile, &dwPosition, &dwMaxPosition))
				{
					D2SOUND_StopSample(ptSample);
				}
			}
			else if (ptSample->bPlaying)
			{
				DWORD dwPlayCursor;
				DWORD dwWriteCursor;
				if (SUCCEEDED(ptSample->ptSoundBuffer->GetCurrentPosition(&dwPlayCursor, &dwWriteCursor)))
				{
					const uint32_t dwMask = ptSample->dwBufferSize - 1;
					const uint32_t dwPreviousCursor = ptSample->dwPlayPosition & dwMask;
					uint32_t dwPlayPosition = ptSample->dwPlayPosition - dwPreviousCursor;
					if (dwPlayCursor < dwPreviousCursor)
					{
						// The play cursor wrapped around the buffer
						dwPlayPosition += ptSample->dwBufferSize;
					}
					ptSample->dwPlayPosition = dwPlayPosition + dwPlayCursor;

					if (!ptSample->bWriteComplete)
					{
						if (ptSample->dwWritePosition - ptSample->dwPlayPosition < ptSample->dwHalfBufferSize || ptSample->dwPlayPosition > ptSample->dwWritePosition)
						{
							const uint32_t dwBufferOffset = ptSample->dwWritePosition & dwMask;
							SAMPLE_WriteData(ptSample, ptSample->dwWritePosition, dwBufferOffset, ptSample->dwHalfBufferSize);
							ptSample->nCurrentHalf = dwBufferOffset != 0;
							ptSample->dwDataEndOffset = (uint32_t)-1;
						}
					}
					else if (!ptSample->bLoop)
					{
						// Everything has been written, fill the half that was just played with silence
						if (dwPlayCursor < ptSample->dwHalfBufferSize && ptSample->nCurrentHalf == 0)
						{
							SAMPLE_ClearBuffer(ptSample->ptSoundBuffer, ptSample->dwHalfBufferSize, ptSample->dwHalfBufferSize);
							ptSample->nCurrentHalf = 1;
						}

						if (dwPlayCursor >= ptSample->dwHalfBufferSize && ptSample->nCurrentHalf == 1)
						{
							SAMPLE_ClearBuffer(ptSample->ptSoundBuffer, 0, ptSample->dwHalfBufferSize);
							ptSample->nCurrentHalf = 0;
						}

						if (ptSample->dwPlayPosition > ptSample->dwRawSize)
						{
							ptSample->ptSoundBuffer->Stop();
							ptSample->bPlaying = FALSE;
						}
					}
				}
			}
		}

		SOUND_LeaveCriticalSection();
	}

	return 0;
}

//D2Sound.0x6F982BF0
void __fastcall SAMPLE_StartMixerThread()
{
	D2_ASSERT(!sghThreadHandle);

	ghMixerThreadEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);

	DWORD dwThreadId;
	sghThreadHandle = CreateThread(nullptr, 0, SAMPLE_MixerThreadProc, nullptr, 0, &dwThreadId);
}

//D2Sound.0x6F983290
void __fastcall SAMPLE_StopMixerThread()
{
	if (sghThreadHandle && ghMixerThreadEvent)
	{
		SetEvent(ghMixerThreadEvent);
		WaitForSingleObject(sghThreadHandle, INFINITE);
		CloseHandle(ghMixerThreadEvent);
		CloseHandle(sghThreadHandle);
		ghMixerThreadEvent = nullptr;
		sghThreadHandle = nullptr;
	}
}

//D2Sound.0x6F9835F0
BOOL __fastcall SAMPLE_ClearBuffer(IDirectSoundBuffer* ptSoundBuffer, uint32_t dwOffset, uint32_t dwSize)
{
	D2_ASSERT(ptSoundBuffer);

	SOUND_EnterCriticalSection();

	void* pLockedBuffer = nullptr;
	DWORD dwLockedSize = dwSize;
	if (FAILED(ptSoundBuffer->Lock(dwOffset, dwSize, &pLockedBuffer, &dwLockedSize, nullptr, nullptr, 0)))
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	memset(pLockedBuffer, 0, dwLockedSize);
	ptSoundBuffer->Unlock(pLockedBuffer, dwLockedSize, nullptr, 0);

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F983750
static BOOL __fastcall SAMPLE_CreateBuffer(D2SoundSampleStrc* ptSample, uint32_t dwFlags)
{
	WAVEFORMATEX tWaveFormat;
	UTIL_InitWaveFormat(&tWaveFormat, (dwFlags & SAMPLEFLAG_STEREO) ? 2 : 1);

	const uint32_t dwBufferSize = (dwFlags & SAMPLEFLAG_STEREO) ? 0x40000 : 0x20000;
	const BOOL b3D = (dwFlags & SAMPLEFLAG_3D) != 0;

	DSBUFFERDESC1 tBufferDesc = {};
	tBufferDesc.dwSize = sizeof(tBufferDesc);
	tBufferDesc.dwFlags = b3D ? (DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRL3D | DSBCAPS_LOCHARDWARE) : (DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY);
	tBufferDesc.dwBufferBytes = dwBufferSize;
	tBufferDesc.dwReserved = 0;
	tBufferDesc.lpwfxFormat = &tWaveFormat;

	IDirectSound* pDirectSound = D2SOUND_GetDirectSound();
	if (FAILED(pDirectSound->CreateSoundBuffer((LPCDSBUFFERDESC)&tBufferDesc, &ptSample->ptSoundBuffer, nullptr)))
	{
		return FALSE;
	}

	if (b3D)
	{
		if (FAILED(ptSample->ptSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, (void**)&ptSample->pt3DBuffer)))
		{
			ptSample->ptSoundBuffer->Release();
			return FALSE;
		}

		if (D2SOUND_IsEAXEnabled())
		{
			if (FAILED(ptSample->pt3DBuffer->QueryInterface(IID_IKsPropertySet, (void**)&ptSample->ptPropertySet)))
			{
				ptSample->ptSoundBuffer->Release();
				return FALSE;
			}

			ULONG nSupport = 0;
			HRESULT hResult;
			if (SOUND_GetEAXVersion() == 1)
			{
				hResult = ptSample->ptPropertySet->QuerySupport(DSPROPSETID_EAXBUFFER_ReverbProperties, DSPROPERTY_EAXBUFFER_REVERBMIX, &nSupport);
			}
			else
			{
				hResult = ptSample->ptPropertySet->QuerySupport(DSPROPSETID_EAX20_BufferProperties, DSPROPERTY_EAXBUFFER_ALLPARAMETERS, &nSupport);
			}

			if (FAILED(hResult) || (nSupport & (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET)) != (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET))
			{
				ptSample->ptPropertySet->Release();
				ptSample->ptSoundBuffer->Release();
				return FALSE;
			}
		}
	}

	ptSample->dwBufferSize = dwBufferSize;
	ptSample->dwFlags = dwFlags;
	ptSample->dwHalfBufferSize = dwBufferSize >> 1;
	ptSample->dwDataEndOffset = (uint32_t)-1;
	return TRUE;
}

//D2Sound.0x6F9836B0 (#10007)
D2SoundSampleStrc* __fastcall D2SOUND_CreateSample(uint32_t dwFlags)
{
	if ((dwFlags & SAMPLEFLAG_3D) && !D2SOUND_Is3DEnabled())
	{
		return nullptr;
	}

	if ((dwFlags & SAMPLEFLAG_3D) && (dwFlags & SAMPLEFLAG_STEREO))
	{
		return nullptr;
	}

	D2SoundSampleStrc* ptSample = D2_ALLOC_STRC(D2SoundSampleStrc);
	memset(ptSample, 0x00, sizeof(D2SoundSampleStrc));

	if (!SAMPLE_CreateBuffer(ptSample, dwFlags))
	{
		D2_FREE(ptSample);
		return nullptr;
	}

	SOUND_EnterCriticalSection();
	D2SOUND_LIST_AddHead(&gpSampleList, ptSample);
	SOUND_LeaveCriticalSection();
	return ptSample;
}

// Inlined
static void SAMPLE_ReleaseBuffers(D2SoundSampleStrc* ptSample)
{
	if (ptSample->ptPropertySet)
	{
		ptSample->ptPropertySet->Release();
		ptSample->ptPropertySet = nullptr;
	}

	if (ptSample->pt3DBuffer)
	{
		ptSample->pt3DBuffer->Release();
		ptSample->pt3DBuffer = nullptr;
	}

	if (ptSample->ptSoundBuffer)
	{
		ptSample->ptSoundBuffer->Release();
		ptSample->ptSoundBuffer = nullptr;
	}
}

//D2Sound.0x6F9838F0 (#10008)
void __fastcall D2SOUND_DestroySample(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample);

	SOUND_EnterCriticalSection();

	D2SOUND_StopSample(ptSample);
	SAMPLE_ReleaseBuffers(ptSample);
	memset(ptSample, 0x00, sizeof(D2SoundSampleStrc));
	D2SOUND_LIST_Remove(&gpSampleList, ptSample);

	SOUND_LeaveCriticalSection();

	D2_FREE(ptSample);
}

//D2Sound.0x6F983A30 (#10009)
void __fastcall D2SOUND_ResetSample(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);
	D2_ASSERT(!ptSample->hStreamFile);

	SOUND_EnterCriticalSection();

	if (SOUND_CanReuseSampleBuffers())
	{
		ptSample->pbRawData = nullptr;
		ptSample->dwRawSize = 0;
		ptSample->dwPlayPosition = 0;
		ptSample->dwWritePosition = 0;
		ptSample->bWriteComplete = FALSE;
		ptSample->bLoop = FALSE;
		ptSample->dwLoopBlockStart = 0;
	}
	else
	{
		// Some drivers do not behave well when reusing buffers, recreate them
		const uint32_t dwFlags = ptSample->dwFlags;
		D2SOUND_StopSample(ptSample);
		SAMPLE_ReleaseBuffers(ptSample);
		memset(ptSample, 0x00, sizeof(D2SoundSampleStrc));
		SAMPLE_CreateBuffer(ptSample, dwFlags);
	}

	ptSample->ptSoundBuffer->SetCurrentPosition(0);

	if (ptSample->pt3DBuffer)
	{
		ptSample->pt3DBuffer->SetMaxDistance(100.0f, DS3D_IMMEDIATE);
		ptSample->pt3DBuffer->SetMinDistance(2.0f, DS3D_IMMEDIATE);
	}

	if (ptSample->dwFlags & SAMPLEFLAG_3D)
	{
		D2SOUND_SetSamplePosition(ptSample, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		ptSample->ptSoundBuffer->SetPan(0);
	}

	ptSample->fObstruction = 0.0f;

	if (ptSample->ptPropertySet && SOUND_GetEAXVersion() == 2)
	{
		int32_t nObstruction = (int32_t)D2SOUND_LinearToDecibels(0.0f, 1.0f, 1.0f);
		ptSample->ptPropertySet->Set(DSPROPSETID_EAX20_BufferProperties, DSPROPERTY_EAXBUFFER_OBSTRUCTION, nullptr, 0, &nObstruction, sizeof(nObstruction));
	}

	D2SOUND_SetSampleVolume(ptSample, MAX_VOLUME);

	SOUND_LeaveCriticalSection();
}

//D2Sound.0x6F983CB0 (#10010)
BOOL __fastcall D2SOUND_SetSampleData(D2SoundSampleStrc* ptSample, const void* pbWaveData, uint32_t dwWaveSize)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer && pbWaveData && dwWaveSize);

	SOUND_EnterCriticalSection();

	uint32_t dwRawSize = dwWaveSize;
	WAVEFORMATEX tWaveFormat;
	const uint8_t* pbRawData = (const uint8_t*)D2SOUND_ParseWave(pbWaveData, &dwRawSize, &tWaveFormat);

	D2_ASSERT(ptSample->dwLoopBlockStart < dwRawSize);

	ptSample->dwRawSize = dwRawSize;
	ptSample->pbRawData = pbRawData;
	SAMPLE_WriteData(ptSample, 0, 0, ptSample->dwBufferSize);
	ptSample->nCurrentHalf = 1;

	if (!ptSample->bLoop && ptSample->dwRawSize < ptSample->dwBufferSize)
	{
		ptSample->dwDataEndOffset = ptSample->dwRawSize;
	}
	else
	{
		ptSample->dwDataEndOffset = (uint32_t)-1;
	}

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F983DA0 (#10011)
BOOL __fastcall D2SOUND_PlaySample(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample);

	SOUND_EnterCriticalSection();

	if (FAILED(ptSample->ptSoundBuffer->Play(0, 0, DSBPLAY_LOOPING)))
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	ptSample->bPlaying = TRUE;

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F983E10 (#10012)
void __fastcall D2SOUND_StopSample(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	SOUND_EnterCriticalSection();

	if (ptSample->hStreamFile)
	{
		D2SOUND_CloseSampleStream(ptSample);
	}

	ptSample->ptSoundBuffer->Stop();
	ptSample->bPlaying = FALSE;

	SOUND_LeaveCriticalSection();
}

//D2Sound.0x6F983EE0 (#10013)
BOOL __fastcall D2SOUND_IsSamplePlaying(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	return ptSample->bPlaying;
}

//D2Sound.0x6F983F10 (#10064)
BOOL __fastcall D2SOUND_IsSampleBufferPlaying(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	SOUND_EnterCriticalSection();

	DWORD dwStatus;
	if (FAILED(ptSample->ptSoundBuffer->GetStatus(&dwStatus)))
	{
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	SOUND_LeaveCriticalSection();
	return dwStatus & DSBSTATUS_PLAYING;
}

//D2Sound.0x6F983F80 (#10014)
void __fastcall D2SOUND_SetSampleVolume(D2SoundSampleStrc* ptSample, int32_t nVolume)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	ptSample->nVolume = nVolume;

	int32_t nScaledVolume = gnMasterVolume * nVolume / MAX_VOLUME;
	if (!(ptSample->dwFlags & SAMPLEFLAG_EAX_OBSTRUCTION) || SOUND_GetEAXVersion() != 2)
	{
		nScaledVolume = (int32_t)((1.0 - ptSample->fObstruction) * nScaledVolume);
	}

	ptSample->ptSoundBuffer->SetVolume((LONG)D2SOUND_LinearToDecibels(0.0f, 255.0f, (float)nScaledVolume));
}

//D2Sound.0x6F984020 (#10015)
int32_t __fastcall D2SOUND_GetSampleVolume(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample);

	return ptSample->nVolume;
}

//D2Sound.0x6F984050 (#10016)
void __fastcall D2SOUND_SetSamplePan(D2SoundSampleStrc* ptSample, int32_t nPan)
{
	D2_ASSERT(ptSample);

	// nPan: 0 = left, 128 = center, 255 = right
	if (nPan > 128)
	{
		ptSample->ptSoundBuffer->SetPan((LONG)-D2SOUND_LinearToDecibels(0.0f, 127.0f, (float)(255 - nPan)));
	}
	else if (nPan < 128)
	{
		ptSample->ptSoundBuffer->SetPan((LONG)D2SOUND_LinearToDecibels(0.0f, 127.0f, (float)nPan));
	}
	else
	{
		ptSample->ptSoundBuffer->SetPan(0);
	}
}

//D2Sound.0x6F9840F0 (#10017)
void __fastcall D2SOUND_SetSamplePosition(D2SoundSampleStrc* ptSample, float fX, float fY, float fZ)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	if (ptSample->dwFlags & SAMPLEFLAG_3D)
	{
		ptSample->pt3DBuffer->SetPosition(fX, fY, fZ, DS3D_IMMEDIATE);
	}
}

//D2Sound.0x6F984140 (#10018)
uint32_t __fastcall D2SOUND_GetSampleStreamPosition(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample);

	SOUND_EnterCriticalSection();

	if (ptSample->hStreamFile)
	{
		uint32_t dwPosition;
		uint32_t dwMaxPosition;
		if (SFileDdaGetPos(ptSample->hStreamFile, &dwPosition, &dwMaxPosition))
		{
			SOUND_LeaveCriticalSection();
			// 16 bits stereo samples
			return dwPosition >> 2;
		}
	}

	SOUND_LeaveCriticalSection();
	return 0;
}

//D2Sound.0x6F9841C0 (#10019)
void __fastcall D2SOUND_SetSampleLoop(D2SoundSampleStrc* ptSample, BOOL bLoop)
{
	D2_ASSERT(ptSample);

	ptSample->bLoop = bLoop;
}

//D2Sound.0x6F9841F0 (#10020)
void __fastcall D2SOUND_SetSampleLoopBlockStart(D2SoundSampleStrc* ptSample, uint32_t dwLoopBlockStart)
{
	D2_ASSERT(ptSample);

	ptSample->dwLoopBlockStart = dwLoopBlockStart;
}

//D2Sound.0x6F984220 (#10021)
void __fastcall D2SOUND_SetSampleObstruction(D2SoundSampleStrc* ptSample, float fObstruction)
{
	D2_ASSERT(ptSample);

	ptSample->fObstruction = fObstruction;

	if (!ptSample->ptPropertySet || SOUND_GetEAXVersion() != 2)
	{
		return;
	}

	if ((ptSample->dwFlags & SAMPLEFLAG_EAX_OBSTRUCTION) || fObstruction == 0.0f)
	{
		int32_t nObstruction = (int32_t)D2SOUND_LinearToDecibels(0.0f, 1.0f, 1.0f - fObstruction);
		ptSample->ptPropertySet->Set(DSPROPSETID_EAX20_BufferProperties, DSPROPERTY_EAXBUFFER_OBSTRUCTION, nullptr, 0, &nObstruction, sizeof(nObstruction));
	}
}

//D2Sound.0x6F9842C0 (#10022)
void __fastcall D2SOUND_SetSampleReverb(D2SoundSampleStrc* ptSample, float fReverb)
{
	D2_ASSERT(ptSample);

	if (SOUND_IsReverbOff())
	{
		fReverb = 0.0f;
	}

	if (!ptSample->ptPropertySet)
	{
		return;
	}

	if (SOUND_GetEAXVersion() == 1)
	{
		if (fReverb == 0.0f)
		{
			fReverb = EAX_REVERBMIX_USEDISTANCE;
		}

		ptSample->ptPropertySet->Set(DSPROPSETID_EAXBUFFER_ReverbProperties, DSPROPERTY_EAXBUFFER_REVERBMIX, nullptr, 0, &fReverb, sizeof(fReverb));
	}
	else
	{
		int32_t nRoom = (int32_t)D2SOUND_LinearToDecibels(0.0f, 1.0f, fReverb);
		ptSample->ptPropertySet->Set(DSPROPSETID_EAX20_BufferProperties, DSPROPERTY_EAXBUFFER_ROOMHF, nullptr, 0, &nRoom, sizeof(nRoom));
		ptSample->ptPropertySet->Set(DSPROPSETID_EAX20_BufferProperties, DSPROPERTY_EAXBUFFER_ROOM, nullptr, 0, &nRoom, sizeof(nRoom));
	}
}

//D2Sound.0x6F9843A0 (#10023)
BOOL __fastcall D2SOUND_IsSampleStreaming(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample);

	return ptSample->hStreamFile != nullptr;
}

//D2Sound.0x6F9845B0 (#10024)
void __fastcall D2SOUND_FadeSample(D2SoundSampleStrc* ptSample, int32_t nVolume, int32_t nDuration)
{
	D2_ASSERT(ptSample);

	if (!D2SOUND_GetDirectSound())
	{
		return;
	}

	SOUND_EnterCriticalSection();

	ptSample->bFading = TRUE;
	ptSample->nFadeStartVolume = ptSample->nVolume;
	ptSample->nFadeEndVolume = nVolume;
	ptSample->nFadeStartTick = GetTickCount();
	ptSample->nFadeEndTick = ptSample->nFadeStartTick + nDuration;

	SOUND_LeaveCriticalSection();
}

//D2Sound.0x6F9847A0 (#10025)
BOOL __fastcall D2SOUND_OpenSampleStream(D2SoundSampleStrc* ptSample, const char* szFileName, uint32_t dwStartSample, BOOL bLoop)
{
	D2_ASSERT(ptSample);

	HSFILE hFile;
	if (!FOG_FOpenFile(szFileName, &hFile))
	{
		return FALSE;
	}

	SOUND_EnterCriticalSection();

	// Samples are 16 bits stereo
	if (!SFileDdaBeginEx(hFile, ptSample->dwBufferSize, bLoop ? SFILE_DDA_LOOP : 0, 4 * dwStartSample, INT32_MAX, INT32_MAX, ptSample->ptSoundBuffer))
	{
		FOG_FCloseFile(hFile);
		SOUND_LeaveCriticalSection();
		return FALSE;
	}

	ptSample->hStreamFile = hFile;
	ptSample->bPlaying = TRUE;
	ptSample->dwDataEndOffset = (uint32_t)-1;

	SOUND_LeaveCriticalSection();
	return TRUE;
}

//D2Sound.0x6F984870 (#10026)
void __fastcall D2SOUND_CloseSampleStream(D2SoundSampleStrc* ptSample)
{
	D2_ASSERT(ptSample && ptSample->ptSoundBuffer);

	SOUND_EnterCriticalSection();

	if (ptSample->hStreamFile)
	{
		SFileDdaEnd(ptSample->hStreamFile);
		ptSample->ptSoundBuffer->Stop();
		FOG_FCloseFile(ptSample->hStreamFile);
		ptSample->hStreamFile = nullptr;
		ptSample->bPlaying = FALSE;
	}

	SOUND_LeaveCriticalSection();
}

//D2Sound.0x6F984630 (#10027)
void __fastcall D2SOUND_SetMasterVolume(int32_t nVolume)
{
	if (!D2SOUND_GetDirectSound() || nVolume == gnMasterVolume)
	{
		return;
	}

	D2_ASSERT(nVolume >= MIN_VOLUME && nVolume <= MAX_VOLUME);

	SOUND_EnterCriticalSection();

	gnMasterVolume = nVolume;
	for (D2SoundListStrc* pNode = gpSampleList; pNode; pNode = pNode->pNext)
	{
		D2SoundSampleStrc* ptSample = (D2SoundSampleStrc*)pNode->pData;
		D2SOUND_SetSampleVolume(ptSample, D2SOUND_GetSampleVolume(ptSample));
	}

	SOUND_LeaveCriticalSection();
}

//D2Sound.0x6F984780 (#10028)
int32_t __fastcall D2SOUND_GetMasterVolume()
{
	return D2SOUND_GetDirectSound() ? gnMasterVolume : 0;
}

//D2Sound.0x6F9843D0 (#10029)
void __fastcall D2SOUND_FadeOutMasterVolume(int32_t nDuration)
{
	if (!D2SOUND_GetDirectSound())
	{
		return;
	}

	D2_ASSERT(nDuration > 0);

	constexpr uint32_t nStepDuration = 20;
	uint32_t nVolume = D2SOUND_GetMasterVolume();
	const uint32_t nVolumeStep = nVolume / ((uint32_t)nDuration / nStepDuration);

	while (nVolume)
	{
		Sleep(nStepDuration);

		if (nVolume > nVolumeStep)
		{
			nVolume -= nVolumeStep;
		}
		else
		{
			nVolume = 0;
		}

		D2SOUND_SetMasterVolume(nVolume);
	}
}

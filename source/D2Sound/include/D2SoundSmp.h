#pragma once

#include <D2BasicTypes.h>
#include <StormHandles.h>
#include <Windows.h>
#include <cstdint>

struct IDirectSoundBuffer;
struct IDirectSound3DBuffer;
struct IKsPropertySet;

enum D2SoundSampleFlags : uint32_t
{
	SAMPLEFLAG_STEREO = 0x01,
	SAMPLEFLAG_3D = 0x02,
	// Obstruction is applied through EAX 2.0 instead of the sample volume
	SAMPLEFLAG_EAX_OBSTRUCTION = 0x04,
};

#pragma pack(push, 1)
struct D2SoundSampleStrc
{
	IDirectSoundBuffer* ptSoundBuffer;		//0x00
	uint32_t dwBufferSize;					//0x04 Power of 2
	uint32_t dwHalfBufferSize;				//0x08
	IDirectSound3DBuffer* pt3DBuffer;		//0x0C
	IKsPropertySet* ptPropertySet;			//0x10
	const uint8_t* pbRawData;				//0x14
	uint32_t dwRawSize;						//0x18
	BOOL bPlaying;							//0x1C
	uint32_t dwPlayPosition;				//0x20 Total amount of bytes played
	uint32_t dwWritePosition;				//0x24 Total amount of bytes written to the buffer
	int32_t nCurrentHalf;					//0x28
	BOOL bWriteComplete;					//0x2C
	uint32_t dwDataEndOffset;				//0x30 Buffer offset after which the buffer is filled with silence, or -1
	uint32_t dwFlags;						//0x34 D2SoundSampleFlags
	int32_t nVolume;						//0x38 [0, 255]
	float fObstruction;						//0x3C [0, 1]
	BOOL bLoop;								//0x40
	uint32_t dwLoopBlockStart;				//0x44
	HSFILE hStreamFile;						//0x48
	BOOL bFading;							//0x4C
	int32_t nFadeStartVolume;				//0x50
	int32_t nFadeEndVolume;					//0x54
	int32_t nFadeStartTick;					//0x58
	int32_t nFadeEndTick;					//0x5C
};
#pragma pack(pop)


//D2Sound.0x6F9836B0 (#10007)
D2SOUND_DLL_DECL D2SoundSampleStrc* __fastcall D2SOUND_CreateSample(uint32_t dwFlags);
//D2Sound.0x6F9838F0 (#10008)
D2SOUND_DLL_DECL void __fastcall D2SOUND_DestroySample(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983A30 (#10009)
D2SOUND_DLL_DECL void __fastcall D2SOUND_ResetSample(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983CB0 (#10010)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_SetSampleData(D2SoundSampleStrc* ptSample, const void* pbWaveData, uint32_t dwWaveSize);
//D2Sound.0x6F983DA0 (#10011)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_PlaySample(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983E10 (#10012)
D2SOUND_DLL_DECL void __fastcall D2SOUND_StopSample(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983EE0 (#10013)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsSamplePlaying(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983F10 (#10064)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsSampleBufferPlaying(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F983F80 (#10014)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSampleVolume(D2SoundSampleStrc* ptSample, int32_t nVolume);
//D2Sound.0x6F984020 (#10015)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetSampleVolume(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F984050 (#10016)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSamplePan(D2SoundSampleStrc* ptSample, int32_t nPan);
//D2Sound.0x6F9840F0 (#10017)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSamplePosition(D2SoundSampleStrc* ptSample, float fX, float fY, float fZ);
//D2Sound.0x6F984140 (#10018)
D2SOUND_DLL_DECL uint32_t __fastcall D2SOUND_GetSampleStreamPosition(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F9841C0 (#10019)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSampleLoop(D2SoundSampleStrc* ptSample, BOOL bLoop);
//D2Sound.0x6F9841F0 (#10020)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSampleLoopBlockStart(D2SoundSampleStrc* ptSample, uint32_t dwLoopBlockStart);
//D2Sound.0x6F984220 (#10021)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSampleObstruction(D2SoundSampleStrc* ptSample, float fObstruction);
//D2Sound.0x6F9842C0 (#10022)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetSampleReverb(D2SoundSampleStrc* ptSample, float fReverb);
//D2Sound.0x6F9843A0 (#10023)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_IsSampleStreaming(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F9845B0 (#10024)
D2SOUND_DLL_DECL void __fastcall D2SOUND_FadeSample(D2SoundSampleStrc* ptSample, int32_t nVolume, int32_t nDuration);
//D2Sound.0x6F9847A0 (#10025)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_OpenSampleStream(D2SoundSampleStrc* ptSample, const char* szFileName, uint32_t dwStartSample, BOOL bLoop);
//D2Sound.0x6F984870 (#10026)
D2SOUND_DLL_DECL void __fastcall D2SOUND_CloseSampleStream(D2SoundSampleStrc* ptSample);
//D2Sound.0x6F984630 (#10027)
D2SOUND_DLL_DECL void __fastcall D2SOUND_SetMasterVolume(int32_t nVolume);
//D2Sound.0x6F984780 (#10028)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_GetMasterVolume();
//D2Sound.0x6F9843D0 (#10029)
D2SOUND_DLL_DECL void __fastcall D2SOUND_FadeOutMasterVolume(int32_t nDuration);


// Internal functions (not exported)

//D2Sound.0x6F982BF0
void __fastcall SAMPLE_StartMixerThread();
//D2Sound.0x6F983290
void __fastcall SAMPLE_StopMixerThread();
//D2Sound.0x6F9835F0
BOOL __fastcall SAMPLE_ClearBuffer(IDirectSoundBuffer* ptSoundBuffer, uint32_t dwOffset, uint32_t dwSize);

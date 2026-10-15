#pragma once

#include <D2BasicTypes.h>
#include <Windows.h>
#include <cstdint>

struct tWAVEFORMATEX;

#pragma pack(push, 1)
struct D2SoundListStrc
{
	void* pData;							//0x00
	D2SoundListStrc* pNext;					//0x04
};
#pragma pack(pop)


//D2Sound.0x6F984E30 (#10054)
// Converts fValue (in [fMin, fMax]) to an attenuation in hundredths of decibels ([-10000, 0])
D2SOUND_DLL_DECL float __fastcall D2SOUND_LinearToDecibels(float fMin, float fMax, float fValue);
//D2Sound.0x6F984EB0 (#10055)
// Converts an attenuation in hundredths of decibels to a gain in [0, 1]
D2SOUND_DLL_DECL float __fastcall D2SOUND_DecibelsToLinear(float fValue);
//D2Sound.0x6F984F60 (#10056)
// Returns a pointer to the 'data' chunk of a .wav file (and its size in pdwSize), or nullptr if the file is invalid
D2SOUND_DLL_DECL void* __fastcall D2SOUND_ParseWave(const void* pWave, uint32_t* pdwSize, tWAVEFORMATEX* pWaveFormat);
//D2Sound.0x6F985050 (#10057)
D2SOUND_DLL_DECL void __fastcall D2SOUND_GetVolumeAndPanFromPosition(int32_t* pVolume, int32_t* pPan, float fX, float fY, float fZ);
//D2Sound.0x6F985140 (#10058)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LIST_AddHead(D2SoundListStrc** ppList, void* pData);
//D2Sound.0x6F985180 (#10059)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LIST_Remove(D2SoundListStrc** ppList, void* pData);
//D2Sound.0x6F9851D0 (#10060)
D2SOUND_DLL_DECL BOOL __fastcall D2SOUND_LIST_Contains(D2SoundListStrc* pList, void* pData);
//D2Sound.0x6F9851F0 (#10061)
D2SOUND_DLL_DECL int32_t __fastcall D2SOUND_LIST_GetCount(D2SoundListStrc* pList);
//D2Sound.0x6F985200 (#10062)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LIST_Clear(D2SoundListStrc** ppList);
//D2Sound.0x6F985250 (#10063)
D2SOUND_DLL_DECL void __fastcall D2SOUND_LIST_AddTail(D2SoundListStrc** ppList, void* pData);


// Internal functions (not exported)

//D2Sound.0x6F984F10
void __fastcall UTIL_InitWaveFormat(tWAVEFORMATEX* pWaveFormat, uint16_t nChannels);
//D2Sound.0x6F985450
BOOL __fastcall UTIL_GetVxdVersion(const char* szPath, uint32_t* pMajor, uint32_t* pMinor, uint32_t* pBuild);

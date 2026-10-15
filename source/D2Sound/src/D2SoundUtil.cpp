#include <cmath>
#include <cstring>

#include <Windows.h>
#include <mmsystem.h>

#include "D2SoundUtil.h"

#include <Fog.h>


constexpr float DECIBELS_EPSILON = 0.0001f;
constexpr float MIN_DECIBELS = -10000.0f;
constexpr float MAX_DECIBELS = 0.0f;


//D2Sound.0x6F984E30 (#10054)
float __fastcall D2SOUND_LinearToDecibels(float fMin, float fMax, float fValue)
{
	if (!(fMin + DECIBELS_EPSILON < fValue))
	{
		return MIN_DECIBELS;
	}

	if (!(fMax - DECIBELS_EPSILON > fValue))
	{
		return MAX_DECIBELS;
	}

	const double fLinear = (fValue == 0.0) ? fMax : fValue;
	return (float)(-2000.0 * log10((fMin + fMax) / fLinear));
}

//D2Sound.0x6F984EB0 (#10055)
float __fastcall D2SOUND_DecibelsToLinear(float fValue)
{
	if (fValue + DECIBELS_EPSILON > MAX_DECIBELS)
	{
		return 1.0f;
	}

	if (fValue - DECIBELS_EPSILON < MIN_DECIBELS)
	{
		return 0.0f;
	}

	return (float)pow(10.0, fValue * 0.0005f);
}

//D2Sound.0x6F984F10
void __fastcall UTIL_InitWaveFormat(WAVEFORMATEX* pWaveFormat, uint16_t nChannels)
{
	memset(pWaveFormat, 0x00, sizeof(WAVEFORMATEX));
	pWaveFormat->nBlockAlign = 2 * nChannels;
	pWaveFormat->nChannels = nChannels;
	pWaveFormat->wFormatTag = WAVE_FORMAT_PCM;
	pWaveFormat->nSamplesPerSec = 22050;
	pWaveFormat->wBitsPerSample = 16;
	pWaveFormat->nAvgBytesPerSec = 22050 * pWaveFormat->nBlockAlign;
}

//D2Sound.0x6F984F60 (#10056)
void* __fastcall D2SOUND_ParseWave(const void* pWave, uint32_t* pdwSize, WAVEFORMATEX* pWaveFormat)
{
	struct D2RiffChunkHeaderStrc
	{
		uint32_t dwId;
		uint32_t dwSize;
	};

	constexpr uint32_t RIFF_ID = 0x46464952; // "RIFF"
	constexpr uint32_t WAVE_ID = 0x45564157; // "WAVE"
	constexpr uint32_t FMT_ID = 0x20746D66; // "fmt "
	constexpr uint32_t DATA_ID = 0x61746164; // "data"

	if (*pdwSize < 32)
	{
		return nullptr;
	}

	*pdwSize -= 12;

	const uint32_t* pRiffHeader = (const uint32_t*)pWave;
	if (pRiffHeader[0] != RIFF_ID || pRiffHeader[2] != WAVE_ID)
	{
		return nullptr;
	}

	const uint8_t* pCurrent = (const uint8_t*)pWave + 12;

	const D2RiffChunkHeaderStrc* pChunk = nullptr;
	while (true)
	{
		if (*pdwSize < sizeof(D2RiffChunkHeaderStrc))
		{
			return nullptr;
		}

		pChunk = (const D2RiffChunkHeaderStrc*)pCurrent;
		*pdwSize -= sizeof(D2RiffChunkHeaderStrc);
		pCurrent += sizeof(D2RiffChunkHeaderStrc);

		if (pChunk->dwId == FMT_ID)
		{
			break;
		}

		if (*pdwSize < pChunk->dwSize)
		{
			return nullptr;
		}

		pCurrent += pChunk->dwSize;
		*pdwSize -= pChunk->dwSize;
	}

	if (!pCurrent || pChunk->dwSize < 16 || *pdwSize < pChunk->dwSize)
	{
		return nullptr;
	}

	*pdwSize -= pChunk->dwSize;

	const PCMWAVEFORMAT* pFormat = (const PCMWAVEFORMAT*)pCurrent;
	pWaveFormat->wFormatTag = pFormat->wf.wFormatTag;
	pWaveFormat->nChannels = pFormat->wf.nChannels;
	pWaveFormat->nSamplesPerSec = pFormat->wf.nSamplesPerSec;
	pWaveFormat->nAvgBytesPerSec = pFormat->wf.nAvgBytesPerSec;
	pWaveFormat->nBlockAlign = pFormat->wf.nBlockAlign;
	pWaveFormat->wBitsPerSample = pFormat->wBitsPerSample;
	pWaveFormat->cbSize = 0;

	pCurrent += pChunk->dwSize;

	while (true)
	{
		if (*pdwSize < sizeof(D2RiffChunkHeaderStrc))
		{
			return nullptr;
		}

		pChunk = (const D2RiffChunkHeaderStrc*)pCurrent;
		*pdwSize -= sizeof(D2RiffChunkHeaderStrc);
		pCurrent += sizeof(D2RiffChunkHeaderStrc);

		if (pChunk->dwId == DATA_ID)
		{
			break;
		}

		if (*pdwSize < pChunk->dwSize)
		{
			return nullptr;
		}

		pCurrent += pChunk->dwSize;
		*pdwSize -= pChunk->dwSize;
	}

	if (!pCurrent || *pdwSize < pChunk->dwSize)
	{
		return nullptr;
	}

	*pdwSize = pChunk->dwSize;
	return (void*)pCurrent;
}

//D2Sound.0x6F985050 (#10057)
void __fastcall D2SOUND_GetVolumeAndPanFromPosition(int32_t* pVolume, int32_t* pPan, float fX, float fY, float fZ)
{
	constexpr float fMinDistance = 2.0f;
	constexpr float fMaxDistance = 100.0f;

	float fDistance = sqrtf(fX * fX + fY * fY + fZ * fZ);
	if (fDistance > fMaxDistance)
	{
		fDistance = fMaxDistance;
	}

	float fAttenuation = 0.0f;
	if (fDistance >= fMinDistance)
	{
		// -6dB each time the distance is doubled
		fAttenuation = (float)(log(fDistance * 0.5f) * 1.4426950408889634 * 6.0f);
	}

	int32_t nVolume = (int32_t)(255.0 / pow(10.0, fAttenuation * 0.05f));
	if (nVolume <= 0)
	{
		nVolume = 0;
	}
	else if (nVolume >= 255)
	{
		nVolume = 255;
	}

	int32_t nPan = (int32_t)(fX * 127.0f * 0.8f + 128.0f);
	if (nPan <= 0)
	{
		nPan = 0;
	}
	else if (nPan >= 255)
	{
		nPan = 255;
	}

	*pVolume = nVolume;
	*pPan = nPan;
}

//D2Sound.0x6F985140 (#10058)
void __fastcall D2SOUND_LIST_AddHead(D2SoundListStrc** ppList, void* pData)
{
	D2SoundListStrc* pNode = D2_ALLOC_STRC(D2SoundListStrc);
	pNode->pData = nullptr;
	pNode->pNext = nullptr;

	pNode->pNext = *ppList;
	pNode->pData = pData;
	*ppList = pNode;
}

//D2Sound.0x6F985180 (#10059)
void __fastcall D2SOUND_LIST_Remove(D2SoundListStrc** ppList, void* pData)
{
	D2SoundListStrc* pPrevious = nullptr;
	D2SoundListStrc* pNode = *ppList;
	while (pNode && pNode->pData != pData)
	{
		pPrevious = pNode;
		pNode = pNode->pNext;
	}

	if (!pNode)
	{
		return;
	}

	if (*ppList == pNode)
	{
		*ppList = pNode->pNext;
	}

	if (pPrevious)
	{
		pPrevious->pNext = pNode->pNext;
	}

	D2_FREE(pNode);
}

//D2Sound.0x6F9851D0 (#10060)
BOOL __fastcall D2SOUND_LIST_Contains(D2SoundListStrc* pList, void* pData)
{
	for (D2SoundListStrc* pNode = pList; pNode; pNode = pNode->pNext)
	{
		if (pNode->pData == pData)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//D2Sound.0x6F9851F0 (#10061)
int32_t __fastcall D2SOUND_LIST_GetCount(D2SoundListStrc* pList)
{
	int32_t nCount = 0;
	for (D2SoundListStrc* pNode = pList; pNode; pNode = pNode->pNext)
	{
		++nCount;
	}

	return nCount;
}

//D2Sound.0x6F985200 (#10062)
void __fastcall D2SOUND_LIST_Clear(D2SoundListStrc** ppList)
{
	while (*ppList)
	{
		D2SOUND_LIST_Remove(ppList, (*ppList)->pData);
	}
}

//D2Sound.0x6F985250 (#10063)
void __fastcall D2SOUND_LIST_AddTail(D2SoundListStrc** ppList, void* pData)
{
	D2SoundListStrc* pNode = D2_ALLOC_STRC(D2SoundListStrc);
	pNode->pData = nullptr;
	pNode->pNext = nullptr;

	pNode->pData = pData;

	D2SoundListStrc* pLast = *ppList;
	if (!pLast)
	{
		*ppList = pNode;
		return;
	}

	while (pLast->pNext)
	{
		pLast = pLast->pNext;
	}

	pLast->pNext = pNode;
}

//D2Sound.0x6F9852A0
// Reads the version resource of a Windows 9x virtual device driver (LE executable)
static BOOL __fastcall UTIL_ReadVxdVersionResource(const char* szPath, uint32_t* pdwSize, void* pBuffer)
{
	constexpr uint16_t IMAGE_LE_SIGNATURE = 0x454C; // "LE"
	constexpr uint32_t LE_HEADER_VERSION_RESOURCE_OFFSET = 0xB8;
	constexpr uint32_t LE_HEADER_VERSION_RESOURCE_SIZE = 0xBC;
	// Size of the 16-bit resource header (type, name, flags and size) preceding the resource data
	constexpr uint32_t VXD_RESOURCE_HEADER_SIZE = 0x0C;
	constexpr uint32_t VXD_RESOURCE_HEADER_DATA_SIZE = 0x08;

	BOOL bResult = FALSE;
	HANDLE hMapping = nullptr;
	void* pView = nullptr;

	HANDLE hFile = CreateFileA(szPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		hMapping = CreateFileMappingA(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
		if (hMapping)
		{
			pView = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
			if (pView)
			{
				const IMAGE_DOS_HEADER* pDosHeader = (const IMAGE_DOS_HEADER*)pView;
				if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
				{
					SetLastError(ERROR_BAD_FORMAT);
				}
				else
				{
					const uint8_t* pLEHeader = (const uint8_t*)pView + pDosHeader->e_lfanew;
					if (*(const uint32_t*)pLEHeader != IMAGE_LE_SIGNATURE)
					{
						SetLastError(ERROR_BAD_FORMAT);
					}
					else if (*(const uint32_t*)(pLEHeader + LE_HEADER_VERSION_RESOURCE_SIZE) == 0)
					{
						*pdwSize = 0;
						SetLastError(ERROR_RESOURCE_DATA_NOT_FOUND);
					}
					else
					{
						const uint8_t* pResource = (const uint8_t*)pView + *(const uint32_t*)(pLEHeader + LE_HEADER_VERSION_RESOURCE_OFFSET);
						const uint32_t dwResourceSize = *(const uint32_t*)(pResource + VXD_RESOURCE_HEADER_DATA_SIZE);
						if (pBuffer && *pdwSize >= dwResourceSize)
						{
							memset(pBuffer, 0x00, *pdwSize);
							memcpy(pBuffer, pResource + VXD_RESOURCE_HEADER_SIZE, dwResourceSize);
							*pdwSize = dwResourceSize;
							SetLastError(ERROR_SUCCESS);
							bResult = TRUE;
						}
						else
						{
							*pdwSize = dwResourceSize;
							SetLastError(ERROR_INSUFFICIENT_BUFFER);
						}
					}
				}
			}
		}
	}

	// Originally a __finally block
	const DWORD dwLastError = GetLastError();
	if (pView)
	{
		UnmapViewOfFile(pView);
	}

	if (hMapping)
	{
		CloseHandle(hMapping);
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	SetLastError(dwLastError);
	return bResult;
}

//D2Sound.0x6F985450
BOOL __fastcall UTIL_GetVxdVersion(const char* szPath, uint32_t* pMajor, uint32_t* pMinor, uint32_t* pBuild)
{
	uint32_t dwSize = 0;
	if (UTIL_ReadVxdVersionResource(szPath, &dwSize, nullptr) || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		return FALSE;
	}

	SetLastError(ERROR_SUCCESS);

	const uint32_t dwBufferSize = dwSize;
	if (!dwBufferSize)
	{
		return FALSE;
	}

	void* pBuffer = D2_ALLOC(dwBufferSize);
	dwSize = dwBufferSize;
	if (!UTIL_ReadVxdVersionResource(szPath, &dwSize, pBuffer))
	{
		D2_FREE(pBuffer);
		return FALSE;
	}

	VS_FIXEDFILEINFO* pFileInfo;
	UINT nFileInfoSize;
	if (!VerQueryValueA(pBuffer, "\\", (void**)&pFileInfo, &nFileInfoSize))
	{
		D2_FREE(pBuffer);
		return FALSE;
	}

	*pMajor = HIWORD(pFileInfo->dwFileVersionMS);
	*pMinor = LOWORD(pFileInfo->dwFileVersionMS);
	*pBuild = LOWORD(pFileInfo->dwFileVersionLS);
	// Note: pBuffer is leaked, as in the original game.
	return TRUE;
}

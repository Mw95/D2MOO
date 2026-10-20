#include "Core/MemoryPartitions.h"

#include "Engine/Gfx.h"
#include "Sound/SoundHdr.h"


//D2Client.0x6FAA13A0
void __fastcall MEMORY_InitializePartitions(void* pMemPool, BOOL bAllocateTileCache)
{
	D2SystemInfoStrc* pSystemInfo = (D2SystemInfoStrc*)FOG_GetSystemInfo();
	D2_ASSERT(pSystemInfo);

	uint32_t nPhysicalMemory = pSystemInfo->dwTotalPhysicalMemory;
	if (nPhysicalMemory < 0x167D000)
	{
		FOG_Trace("This machine doesn't have enough physical memory (> %.2f MB) for minimal performance!", (double)((float)nPhysicalMemory * (1.0f / (1024.0f * 1024.0f))));
		exit(-1);
	}

	nPhysicalMemory -= 0xB00000;

	uint32_t nSoundCacheSize = (nPhysicalMemory * 10) / 100;
	if (nSoundCacheSize <= 0x300000)
	{
		nSoundCacheSize = 0x300000;
	}
	else if (nSoundCacheSize >= 0x500000)
	{
		nSoundCacheSize = 0x500000;
	}
	sub_6FB553A0(nSoundCacheSize);

	uint32_t nRemainingMemory = nPhysicalMemory - nSoundCacheSize;
	if (bAllocateTileCache)
	{
		nRemainingMemory -= 0x600000;
		D2CMP_10089(pMemPool, 0x600000);
	}

	uint32_t nSpriteCacheSize = (nRemainingMemory - 0x200000) / 3;
	if (nSpriteCacheSize <= 0x1800000)
	{
		nSpriteCacheSize = 0x1800000;
	}
	else if (nSpriteCacheSize >= 0x4000000)
	{
		nSpriteCacheSize = 0x4000000;
	}

	FOG_Trace("Sound Cache Size: %dMB", nSoundCacheSize >> 20);
	FOG_Trace("Tile Cache Size: %dMB", 6);
	FOG_Trace("Sprite Cache Size: %dMB", nSpriteCacheSize >> 20);
	D2CMP_InitSpriteCache(pMemPool, nSpriteCacheSize, 0x7D000, nPhysicalMemory);
	sub_6FB590B0(0x200000);
}

//D2Client.0x6FAA14E0
void __fastcall MEMORY_FreePartitions(void* pMemPool)
{
	D2CMP_10090(pMemPool);
	D2CMP_FlushSpriteCache((BOOL)pMemPool);
	sub_6FB59140();
}

//D2Client.0x6FAA1500
void __fastcall MEMORY_Nop()
{
}

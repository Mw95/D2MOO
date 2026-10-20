#pragma once

#include <D2Client.h>


#pragma pack(push, 1)
// Returned by FOG_GetSystemInfo
struct D2SystemInfoStrc
{
	uint32_t unk0x00[3];					//0x00
	uint32_t dwTotalPhysicalMemory;			//0x0C
};
#pragma pack(pop)


//D2Client.0x6FAA13A0
void __fastcall MEMORY_InitializePartitions(void* pMemPool, BOOL bAllocateTileCache);
//D2Client.0x6FAA14E0
void __fastcall MEMORY_FreePartitions(void* pMemPool);
//D2Client.0x6FAA1500
void __fastcall MEMORY_Nop();

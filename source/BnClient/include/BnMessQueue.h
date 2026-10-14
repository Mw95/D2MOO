#pragma once

#include <Windows.h>

#include <cstdint>

#include <BnClient.h>

#pragma pack(push, 1)
struct BnMessQueueEntry
{
	int32_t nType;						//0x000
	char szText[0x120];					//0x004
	uint32_t dwBytes;					//0x124
	BnMessQueueEntry* pNext;			//0x128
};
#pragma pack(pop)

BOOL __stdcall BNMESSQUEUE_Initialize();
BOOL __stdcall BNMESSQUEUE_Shutdown();
BOOL __fastcall BNMESSQUEUE_PushData(int32_t nType, const void* pData, uint32_t nSize);
BOOL __fastcall BNMESSQUEUE_PushString(int32_t nType, const char* szText);
uint32_t __fastcall BNMESSQUEUE_Read(int32_t* pType, void* pBuffer);
BOOL __stdcall BNMESSQUEUE_Clear();
BOOL __fastcall BNMESSQUEUE_SetErrorIfNone(int32_t nError);
BOOL __fastcall BNMESSQUEUE_SetError(int32_t nError);
BOOL __fastcall BNMESSQUEUE_SetErrorText(char* szErrorText);
BOOL __fastcall BNMESSQUEUE_GetLastError(BnMessQueueErrorInfo* errInfo);
BOOL __fastcall BNMESSQUEUE_PeekLastError(BnMessQueueErrorInfo* errInfo);

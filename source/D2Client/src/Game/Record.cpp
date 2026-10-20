#include "Game/Record.h"

#include "Draw/DFloor.h"
#include "Game/Game.h"

//D2Client.0x6FB76048
uint8_t* gpuint8_t_6FB76048 = (uint8_t*)&byte_6FBA9A38;
//D2Client.0x6FBA9A20
uint32_t dword_6FBA9A20;
//D2Client.0x6FBA9A24
int32_t dword_6FBA9A24;
//D2Client.0x6FBA9A28
int32_t dword_6FBA9A28;
//D2Client.0x6FBA9A2C
int32_t dword_6FBA9A2C;
//D2Client.0x6FBA9A30
int32_t dword_6FBA9A30;
//D2Client.0x6FBA9A34
uint32_t dword_6FBA9A34;
//D2Client.0x6FBA9A38
uint8_t byte_6FBA9A38;
//D2Client.0x6FBAB978
int32_t dword_6FBAB978;
//D2Client.0x6FBAB980
uint8_t* ptr_6FBAB980;
//D2Client.0x6FBAB984
uint32_t dword_6FBAB984;
//D2Client.0x6FBAB988
int32_t dword_6FBAB988;
//D2Client.0x6FBAB98C
uint32_t dword_6FBAB98C;
//D2Client.0x6FBAB990
uint32_t dword_6FBAB990;

//D2Client.0x6FAAE5B0
void __fastcall RECORD_ProcessWindowMessage(UINT a1, WPARAM a2, LPARAM a3)
{
	uint8_t* puVar1;
	uint32_t uVar2;
	uint32_t* puVar3;

	if (dword_6FBAB988 != 0)
	{
		if (0x111 < a1)
		{
			switch (a1)
			{
			case 0x200:
			case 0x201:
			case 0x202:
			case 0x204:
			case 0x205:
				goto switchD_6faae5ee_caseD_10;
			default:
				goto switchD_6faae5ee_caseD_11;
			}
		}
		if (a1 != 0x111)
		{
			switch (a1)
			{
			case 0x10:
			case 0x101:
			case 0x102:
				break;
			default:
				goto switchD_6faae5ee_caseD_11;
			case 0x100:
				if (499 < *(int*)(gpuint8_t_6FB76048 + 8000))
				{
					puVar1 = (uint8_t*)D2_ALLOC(0x1f4c);
					*(uint32_t*)(puVar1 + 8000) = 0;
					*(uint32_t*)(puVar1 + 0x1f44) = 0;
					*(uint8_t**)(gpuint8_t_6FB76048 + 0x1f48) = puVar1;
					*(uint32_t*)(puVar1 + 0x1f48) = 0;
					gpuint8_t_6FB76048 = puVar1;
				}
				puVar3 = (uint32_t*)(gpuint8_t_6FB76048 + *(int*)(gpuint8_t_6FB76048 + 8000) * 0x10);
				*(int*)(gpuint8_t_6FB76048 + 8000) = *(int*)(gpuint8_t_6FB76048 + 8000) + 1;
				uVar2 = sub_6FAABF80();
				*puVar3 = uVar2;
				puVar3[3] = a3;
				puVar3[1] = a1;
				puVar3[2] = a2;
				return;
			}
		}
	switchD_6faae5ee_caseD_10:
		if (499 < *(int*)(gpuint8_t_6FB76048 + 8000))
		{
			puVar1 = (uint8_t*)D2_ALLOC(0x1f4c);
			*(uint32_t*)(puVar1 + 0x1f44) = 0;
			*(uint32_t*)(puVar1 + 8000) = 0;
			*(uint8_t**)(gpuint8_t_6FB76048 + 0x1f48) = puVar1;
			*(uint32_t*)(puVar1 + 0x1f48) = 0;
			gpuint8_t_6FB76048 = puVar1;
		}
		puVar3 = (uint32_t*)(gpuint8_t_6FB76048 + *(int*)(gpuint8_t_6FB76048 + 8000) * 0x10);
		*(int*)(gpuint8_t_6FB76048 + 8000) = *(int*)(gpuint8_t_6FB76048 + 8000) + 1;
		uVar2 = sub_6FAABF80();
		*puVar3 = uVar2;
		puVar3[3] = a3;
		puVar3[1] = a1;
		puVar3[2] = a2;
	}
switchD_6faae5ee_caseD_11:
}

//D2Client.0x6FAAE810
void __cdecl sub_6FAAE810()
{
	HANDLE hFile;
	int iVar1;
	uint8_t* puVar2;
	void** ppvVar3;
	DWORD aDStack_1c[5];
	uint32_t uStack_8;
	int iStack_4;

	hFile = CreateFileA("Record.dr1", 0x40000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 2, 0x80,
	    (HANDLE)0x0);
	iVar1 = 1;
	puVar2 = &byte_6FBA9A38;
	aDStack_1c[2] = 1;
	aDStack_1c[3] = 1;
	if (ptr_6FBAB980 != nullptr)
	{
		ppvVar3 = (void**)(&ptr_6FBAB980);
		do
		{
			iVar1 = iVar1 + 1;
			puVar2 = (uint8_t*)*ppvVar3;
			ppvVar3 = (void**)(puVar2 + 0x1f48);
			aDStack_1c[3] = iVar1;
		} while (*(int*)(puVar2 + 0x1f48) != 0);
	}
	aDStack_1c[4] = *(int*)(puVar2 + 8000) + -500 + aDStack_1c[3] * 500;
	uStack_8 = sub_6FAABF80();
	iStack_4 = DUNGEON_GetInitSeedFromAct(ghAct);
	aDStack_1c[1] = 0x14;
	WriteFile(hFile, aDStack_1c + 1, 4, aDStack_1c, (LPOVERLAPPED)0x0);
	WriteFile(hFile, aDStack_1c + 2, 0x14, aDStack_1c, (LPOVERLAPPED)0x0);
	puVar2 = &byte_6FBA9A38;
	do
	{
		WriteFile(hFile, puVar2, *(int*)(puVar2 + 8000) << 4, aDStack_1c, (LPOVERLAPPED)0x0);
		puVar2 = *(uint8_t**)(puVar2 + 0x1f48);
	} while (puVar2 != nullptr);
	CloseHandle(hFile);
}

//D2Client.0x6FAAE910
void __cdecl sub_6FAAE910()
{
	void* pvVar1;
	void* pFree;

	pFree = ptr_6FBAB980;
	if (ptr_6FBAB980 != nullptr)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree + 0x1f48);
			D2_FREE(pFree);
			pFree = pvVar1;
		} while (pvVar1 != nullptr);
	}
}

//D2Client.0x6FAAE940
void __fastcall sub_6FAAE940()
{
	HANDLE hFile;
	uint8_t* puVar1;
	int iVar2;
	DWORD DStack_8;
	uint32_t auStack_4;

	if (dword_6FBAB984 != 0)
	{
		dword_6FBAB984 = 0;
		return;
	}
	dword_6FBAB98C = 1;
	hFile = CreateFileA("Record.dr1", 0x80000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 3, 0x80,
	    (HANDLE)0x0);
	ReadFile(hFile, (LPVOID)(auStack_4), 4, &DStack_8, (LPOVERLAPPED)0x0);
	ReadFile(hFile, &dword_6FBA9A20, 0x14, &DStack_8, (LPOVERLAPPED)0x0);
	if (dword_6FBA9A20 == 1)
	{
		iVar2 = 0;
		if (0 < dword_6FBA9A24)
		{
			do
			{
				if (iVar2 != 0)
				{
					puVar1 = (uint8_t*)D2_ALLOC(0x1f4c);
					*(uint32_t*)(puVar1 + 8000) = 0;
					*(uint32_t*)(puVar1 + 0x1f44) = 0;
					*(uint8_t**)(gpuint8_t_6FB76048 + 0x1f48) = puVar1;
					*(uint32_t*)(puVar1 + 0x1f48) = 0;
					gpuint8_t_6FB76048 = puVar1;
				}
				if (dword_6FBA9A28 < 0x1f5)
				{
					dword_6FBAB978 = dword_6FBA9A28;
					D2_ASSERT(iVar2 + 1 == dword_6FBA9A24);
				}
				else
				{
					dword_6FBAB978 = 500;
				}
				ReadFile(hFile, gpuint8_t_6FB76048, dword_6FBAB978 << 4, &DStack_8, (LPOVERLAPPED)0x0);
				iVar2 = iVar2 + 1;
			} while (iVar2 < dword_6FBA9A24);
		}
		gpuint8_t_6FB76048 = &byte_6FBA9A38;
	}
	else
	{
		dword_6FBAB98C = 0;
		dword_6FBAB990 = 0;
	}
	CloseHandle(hFile);
	GAME_SetInitSeed(dword_6FBA9A30);
}

//D2Client.0x6FAAEAA0
uint32_t __cdecl sub_6FAAEAA0()
{
	return dword_6FBAB984;
}

//D2Client.0x6FAAEAB0
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAAEAB0(uint32_t a1, uint32_t a2, uint32_t a3)
{
	sub_6FAAE810();
	if (dword_6FBA9A34 != 0)
	{
		// TODO: Ghidra: Could not recover jumptable
		// TODO: Ghidra: Treating indirect jump
		(*(code*)dword_6FBA9A34)();
		return;
	}
}

//D2Client.0x6FAAEAD0
void __cdecl sub_6FAAEAD0()
{
	dword_6FBAB988 = 1;
	dword_6FBA9A34 = (uint32_t)(FaultSetAssertHandler((FaultAssertHandler)(sub_6FAAEAB0)));
}

//D2Client.0x6FAAEAF0
void __cdecl sub_6FAAEAF0()
{
	dword_6FBAB990 = 1;
}

//D2Client.0x6FAAEB00
uint32_t __cdecl sub_6FAAEB00()
{
	return dword_6FBAB98C;
}

//D2Client.0x6FAAEB10
BOOL __fastcall RECORD_IsPlaying()
{
	return dword_6FBAB990;
}

//D2Client.0x6FAAEB20
void __fastcall sub_6FAAEB20()
{
	if (dword_6FBAB98C != 0)
	{
		dword_6FBAB98C = 0;
		return;
	}
	dword_6FBAB984 = 1;
}

//D2Client.0x6FAAEB40
void __cdecl sub_6FAAEB40()
{
	int iVar1;
	int iVar2;
	HWND__* hWnd;
	int* piVar3;
	uint32_t messageID;
	uint32_t wParam;
	int* bUseResult;
	int* pResult;
	int local_8[2];

	if ((dword_6FBAB990 != 0) && (gpuint8_t_6FB76048 != nullptr))
	{
		iVar1 = sub_6FAABF80();
		if (iVar1 < dword_6FBA9A2C)
		{
			iVar2 = *(int*)(gpuint8_t_6FB76048 + 0x1f44);
			D2_ASSERT(499 >= iVar2);
			if (((*(int*)(gpuint8_t_6FB76048 + 0x1f48) != 0) ||
			        (*(int*)(gpuint8_t_6FB76048 + 8000) != iVar2)) &&
			    (piVar3 = (int*)(gpuint8_t_6FB76048 + iVar2 * 0x10), *piVar3 <= iVar1))
			{
				while (true)
				{
					local_8[1] = 0;
					local_8[0] = 0;
					iVar2 = sub_6FAABF80();
					D2_ASSERT(*piVar3 == iVar2);
					iVar2 = piVar3[3];
					pResult = local_8;
					bUseResult = local_8 + 1;
					wParam = piVar3[2];
					messageID = piVar3[1];
					hWnd = WINDOW_GetWindow();
					SMsgDispatchMessage(hWnd, messageID, wParam, iVar2, bUseResult, (LRESULT*)(pResult));
					*(int*)(gpuint8_t_6FB76048 + 0x1f44) = *(int*)(gpuint8_t_6FB76048 + 0x1f44) + 1;
					if ((*(uint8_t**)(gpuint8_t_6FB76048 + 0x1f48) == nullptr) &&
					    (*(int*)(gpuint8_t_6FB76048 + 8000) == *(int*)(gpuint8_t_6FB76048 + 0x1f44)))
						break;
					if (499 < *(int*)(gpuint8_t_6FB76048 + 0x1f44))
					{
						gpuint8_t_6FB76048 = *(uint8_t**)(gpuint8_t_6FB76048 + 0x1f48);
					}
					if (gpuint8_t_6FB76048 == nullptr)
					{
						return;
					}
					piVar3 = (int*)(gpuint8_t_6FB76048 + *(int*)(gpuint8_t_6FB76048 + 0x1f44) * 0x10);
					if (iVar1 < *piVar3)
					{
						return;
					}
				}
			}
		}
		else
		{
			dword_6FBAB990 = 0;
		}
	}
}

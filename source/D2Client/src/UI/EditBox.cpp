#include "UI/EditBox.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "UI/CmdTbl.h"
#include "UI/Hireables.h"
#include "UI/Inv.h"
#include "UI/Panel.h"
#include "UI/Trade.h"
#include "UI/UI.h"

//D2Client.0x6FB6EF30
uint8_t* gpuint8_t_6FB6EF30 = (uint8_t*)sub_6FAD7730;
//D2Client.0x6FB6EF80
uint8_t* gpuint8_t_6FB6EF80 = (uint8_t*)sub_6FAD8030;
//D2Client.0x6FB78C6B
uint32_t dword_6FB78C6B = 0x6C65486F;
//D2Client.0x6FB79088
uint32_t dword_6FB79088 = 0xFFFFFFFF;
//D2Client.0x6FBB3650
D2CellFileStrc* gpCellFile_6FBB3650;
//D2Client.0x6FBB3654
D2CellFileStrc* gpCellFile_6FBB3654;
//D2Client.0x6FBB3658
D2CellFileStrc* gpCellFile_6FBB3658;
//D2Client.0x6FBB365C
uint8_t byte_6FBB365C;
//D2Client.0x6FBB3660
int32_t dword_6FBB3660;
//D2Client.0x6FBB3664
int32_t dword_6FBB3664;
//D2Client.0x6FBB3668
uint32_t dword_6FBB3668;
//D2Client.0x6FBB366C
int32_t dword_6FBB366C;

//D2Client.0x6FAD7540
void* __fastcall sub_6FAD7540(void* a1, uint32_t a2, int a3, int a4, int a5, int a6, uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10)
{
	D2CellFileStrc* pDVar1;
	void* pvVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t* puVar6;
	Unicode* pThis;
	char acStack_138[4];
	char acStack_134[4];
	char acStack_130[2];
	char cStack_12e;
	void* local_12c;
	Unicode aUStack_128[12];
	char local_110[260];
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*(uint8_t***)a1 = &gpuint8_t_6FB6EF30;
	local_12c = a1;
	sprintf(local_110, "%s\\ui\\menu\\textslid", "DATA\\GLOBAL");
	pDVar1 = CLIENT_LoadCellFile(local_110, 0);
	*(D2CellFileStrc**)((int)a1 + 0x52) = pDVar1;
	uVar4 = (uint32_t)(uint16_t)a8 * 2 + 2;
	*(int*)((int)a1 + 8) = a3;
	*(int*)((int)a1 + 0xc) = a4;
	*(uint32_t*)((int)a1 + 0x3e) = 0;
	*(uint32_t*)((int)a1 + 0x42) = a9;
	*(uint32_t*)((int)a1 + 0x46) = 0;
	pvVar2 = D2_ALLOC(uVar4);
	*(void**)((int)a1 + 0x28) = pvVar2;
	pvVar2 = D2_ALLOC(uVar4);
	*(void**)((int)a1 + 0x2c) = pvVar2;
	puVar6 = *(uint32_t**)((int)a1 + 0x28);
	for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*(uint8_t*)puVar6 = 0;
		puVar6 = (uint32_t*)((int)puVar6 + 1);
	}
	puVar6 = *(uint32_t**)((int)a1 + 0x2c);
	for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
	{
		*(uint8_t*)puVar6 = 0;
		puVar6 = (uint32_t*)((int)puVar6 + 1);
	}
	*(uint32_t*)((int)a1 + 0x36) = 0;
	*(uint32_t*)((int)a1 + 0x3a) = 0;
	*(uint16_t*)((int)a1 + 0x34) = (uint16_t)a8;
	*(uint32_t*)((int)a1 + 0x30) = a7;
	*(uint32_t*)((int)a1 + 0x4e) = a10;
	*(int*)((int)a1 + 0x14) = a4;
	*(int*)((int)a1 + 0x10) = a3 + 1;
	*(uint32_t*)((int)a1 + 0x20) = 1;
	*(uint32_t*)((int)a1 + 0x4a) = 1;
	acStack_138[0] = "0000000000"[0];
	acStack_138[1] = "0000000000"[1];
	acStack_138[2] = "0000000000"[2];
	acStack_138[3] = "0000000000"[3];
	acStack_134[0] = "0000000000"[4];
	acStack_134[1] = "0000000000"[5];
	acStack_134[2] = "0000000000"[6];
	acStack_134[3] = "0000000000"[7];
	acStack_130[0] = "0000000000"[8];
	acStack_130[1] = "0000000000"[9];
	cStack_12e = "0000000000"[10];
	D2Win_10127_SetFont(*(Font*)((int)a1 + 0x4e));
	Unicode::win2Unicode(aUStack_128, acStack_138, 0xb);
	if (a5 < 1)
	{
		iVar5 = D2Win_10121_GetTextWidth(aUStack_128);
		*(uint32_t*)((int)a1 + 0x18) = (iVar5 / 10) * ((uint16_t)a8 + 2);
	}
	else
	{
		*(int*)((int)a1 + 0x18) = a5;
	}
	if (a6 < 1)
	{
		a6 = 1;
		*(uint32_t*)((int)a1 + 0x56) = 1;
	}
	else
	{
		*(uint32_t*)((int)a1 + 0x56) = 0;
	}
	*(int*)((int)a1 + 0x1c) = a6;
	*(uint32_t*)((int)a1 + 0x24) = 0;
	*(uint32_t*)((int)a1 + 4) = 0;
	return a1;
}

//D2Client.0x6FAD7730
void* __fastcall sub_6FAD7730(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAD7760((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAD7760
void __fastcall sub_6FAD7760(uint32_t* a1)
{
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6EF30);
	local_4 = 0;
	if ((void*)a1[10] != nullptr)
	{
		D2_FREE((void*)a1[10]);
		a1[10] = 0;
	}
	if ((void*)a1[0xb] != nullptr)
	{
		D2_FREE((void*)a1[0xb]);
		a1[0xb] = 0;
	}
	CLIENT_FreeCellFile(*(D2CellFileStrc**)((int)a1 + 0x52));
	local_4 = 0xffffffff;
	sub_6FAEFD30(a1);
}

//D2Client.0x6FAD77F0
void __fastcall sub_6FAD77F0(void* a1, uint32_t a2, uint32_t a3)
{
	*(uint32_t*)((int)a1 + 0x20) = a3;
}

//D2Client.0x6FAD7800
void __fastcall sub_6FAD7800(int a1)
{
	int iVar1;
	D2SplittedTextStrc* pFree;
	int iVar2;
	int iVar3;
	Unicode* pUVar4;
	int iVar5;
	int bCentered;
	Unicode aUStack_1ac[3];
	char acStack_1a6[2];
	int iStack_1a4;
	int iStack_1a0;
	int iStack_19c;
	D2SplittedTextStrc* pDStack_198;
	int iStack_194;
	Unicode aUStack_190[200];

	iVar3 = 0;
	*(int*)(a1 + 0x46) = *(int*)(a1 + 0x46) + 1;
	if (*(int*)(a1 + 0x56) != 0)
	{
		sub_6FB5B0F0(*(int*)(a1 + 0x10) + -10, *(int*)(a1 + 0x14) + -0x10,
		    *(int*)(a1 + 0x18), 0x12, 0, (DrawMode)(2));
	}
	D2Win_10127_SetFont(*(Font*)(a1 + 0x4e));
	acStack_1a6[1] = 0;
	acStack_1a6[0] = '_';
	Unicode::win2Unicode(aUStack_1ac, acStack_1a6, 2);
	iVar2 = *(int*)(a1 + 0x4a);
	if (iVar2 == 0)
	{
	LAB_6fad78a1:
		if (*(uint32_t*)(a1 + 0x46) % 10 != 0)
			goto LAB_6fad78bb;
	}
	else if (*(uint32_t*)(a1 + 0x46) % 0x14 != 0)
	{
		if (iVar2 != 0)
			goto LAB_6fad78bb;
		goto LAB_6fad78a1;
	}
	*(uint32_t*)(a1 + 0x4a) = (uint32_t)(iVar2 == 0);
LAB_6fad78bb:
	if (*(int*)(a1 + 0x1c) == 1)
	{
		iVar2 = 0;
		iVar3 = D2Win_10121_GetTextWidth(*(Unicode**)(a1 + 0x28));
		if ((*(int*)(a1 + 0x18) < iVar3) &&
		    (iVar3 = Unicode::strlen(*(Unicode**)(a1 + 0x28)), 0 < iVar3))
		{
			do
			{
				iVar1 = D2Win_10121_GetTextWidth((Unicode*)(*(int*)(a1 + 0x28) + iVar2 * 2));
				if (iVar1 <= *(int*)(a1 + 0x18))
					break;
				iVar2 = iVar2 + 1;
			} while (iVar2 < iVar3);
		}
		D2Win_10117_DrawText((Unicode*)(*(int*)(a1 + 0x28) + iVar2 * 2), *(int*)(a1 + 0x10),
		    *(int*)(a1 + 0x14), 0, 0);
		if ((int)(uint32_t) * (uint16_t*)(a1 + 0x34) <= *(int*)(a1 + 0x36))
		{
			return;
		}
		if (*(int*)(a1 + 0x4a) == 0)
		{
			return;
		}
		if (*(int*)(a1 + 0x3a) < *(int*)(a1 + 0x36))
		{
			return;
		}
		iVar3 = Unicode::strlen((Unicode*)(*(int*)(a1 + 0x28) + iVar2 * 2));
		if (iVar3 != 0)
		{
			Unicode::strcpy(*(Unicode**)(a1 + 0x2c), *(Unicode**)(a1 + 0x28));
			iVar5 = 0;
			iVar1 = 0;
			*(uint16_t*)(*(int*)(a1 + 0x2c) + *(int*)(a1 + 0x36) * 2) = 0;
			iVar3 = *(int*)(a1 + 0x14);
			iVar2 = D2Win_10121_GetTextWidth(*(Unicode**)(a1 + 0x2c));
			D2Win_10117_DrawText(aUStack_1ac, iVar2 + *(int*)(a1 + 0x10), iVar3, iVar1, iVar5);
			return;
		}
		iVar3 = *(int*)(a1 + 0x14);
	}
	else
	{
		pFree = D2Win_10199(*(Unicode**)(a1 + 0x28), &iStack_194, *(int*)(a1 + 0x18));
		iVar2 = 0;
		iStack_1a4 = 0;
		iStack_1a0 = 0;
		if (pFree != nullptr)
		{
			do
			{
				D2Win_10117_DrawText(pFree->wszLine, *(int*)(a1 + 0x10), *(int*)(a1 + 0x14) + iVar3, 0, 0);
				iVar1 = Unicode::strlen(pFree->wszLine);
				pDStack_198 = pFree->pNextLine;
				iStack_19c = iVar2 + iVar1;
				iStack_1a4 = iStack_1a4 + 1;
				iVar2 = *(int*)(a1 + 0x36);
				iVar3 = iVar3 + 0x14;
				if ((((iVar2 < (int)(uint32_t) * (uint16_t*)(a1 + 0x34)) && (*(int*)(a1 + 0x4a) != 0)) && (iVar2 <= iStack_19c)) && (iStack_1a0 == 0))
				{
					iStack_1a0 = 1;
					iVar1 = (iVar2 - iStack_19c) + iVar1;
					if (iVar1 < 0)
					{
						iVar1 = 0;
					}
					iVar2 = Unicode::strlen(pFree->wszLine);
					if (iVar2 == 0)
					{
						bCentered = 0;
						iVar5 = 0;
						iVar2 = *(int*)(a1 + 0x14) + -0x14 + iVar3;
						iVar1 = *(int*)(a1 + 0x10);
					}
					else
					{
						iVar2 = Unicode::strlen(pFree->wszLine);
						if (199 < iVar2)
						{
							return;
						}
						Unicode::strcpy(aUStack_190, pFree->wszLine);
						iVar2 = *(int*)(a1 + 0x14);
						bCentered = 0;
						iVar5 = 0;
						aUStack_190[iVar1].ch = 0;
						iVar2 = iVar2 + -0x14 + iVar3;
						iVar1 = D2Win_10121_GetTextWidth(aUStack_190);
						iVar1 = iVar1 + *(int*)(a1 + 0x10);
					}
					D2Win_10117_DrawText(aUStack_1ac, iVar1, iVar2, iVar5, bCentered);
				}
				iVar2 = iStack_19c;
				D2_FREE(pFree->wszLine);
				D2_FREE(pFree);
				pFree = pDStack_198;
			} while (pDStack_198 != nullptr);
			if (iStack_1a4 != 0)
			{
				return;
			}
		}
		if (*(int*)(a1 + 0x4a) == 0)
		{
			return;
		}
		iVar3 = *(int*)(a1 + 0x14);
	}
	D2Win_10117_DrawText(aUStack_1ac, *(int*)(a1 + 0x10), iVar3, 0, 0);
}

//D2Client.0x6FAD7B00
// TODO: decompilation needs review (stack0x)
void __fastcall sub_6FAD7B00(int a1, uint32_t a2, uint32_t a32)
{
	uint8_t stack0xffffffeb[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	char cVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t a3;
	char* pcVar4;
	char local_14[20];

	sprintf(local_14, "%d", a32);
	uVar3 = 0xffffffff;
	pcVar4 = local_14;
	do
	{
		if (uVar3 == 0)
			break;
		uVar3 = uVar3 - 1;
		cVar1 = *pcVar4;
		pcVar4 = pcVar4 + 1;
	} while (cVar1 != '\0');
	a3 = (uint32_t) * (uint16_t*)(a1 + 0x34);
	if (a3 < ~uVar3 - 1)
	{
		(stack0xffffffeb)[a3] = 0;
	}
	Unicode::win2Unicode(*(Unicode**)(a1 + 0x28), local_14, a3);
	iVar2 = Unicode::strlen(*(Unicode**)(a1 + 0x28));
	*(int*)(a1 + 0x36) = iVar2;
	*(int*)(a1 + 0x3a) = iVar2;
}

//D2Client.0x6FAD7B60
void __fastcall sub_6FAD7B60(void* a1, char* a2, char* a3)
{
	int iVar1;

	Unicode::win2Unicode(*(Unicode**)((int)a1 + 0x28), a3, (uint32_t) * (uint16_t*)((int)a1 + 0x34));
	iVar1 = Unicode::strlen(*(Unicode**)((int)a1 + 0x28));
	*(int*)((int)a1 + 0x36) = iVar1;
	*(int*)((int)a1 + 0x3a) = iVar1;
}

//D2Client.0x6FAD7B90
uint32_t __fastcall sub_6FAD7B90(int a1)
{
	int iVar1;
	uint32_t uVar2;
	char acStack_64[100];

	iVar1 = Unicode::strlen(*(Unicode**)(a1 + 0x28));
	if (iVar1 == 0)
	{
		return 0;
	}
	Unicode::toUtf(acStack_64, *(Unicode**)(a1 + 0x28), (uint32_t) * (uint16_t*)(a1 + 0x34));
	uVar2 = atoi(acStack_64);
	return uVar2 & (*(int*)(a1 + 0x30) < (int)uVar2) - 1;
}

//D2Client.0x6FAD7BE0
void __fastcall sub_6FAD7BE0(void* a1, char* a2, char* a3)
{
	Unicode::toUtf(a3, *(Unicode**)((int)a1 + 0x28), (uint32_t) * (uint16_t*)((int)a1 + 0x34));
}

//D2Client.0x6FAD7C00
uint32_t __cdecl sub_6FAD7C00()
{
	return 0;
}

//D2Client.0x6FAD7C10
uint32_t __fastcall sub_6FAD7C10(int a1, uint32_t a2, uint32_t a3)
{
	*(uint32_t*)(a1 + 0x3e) = 1;
	return 0;
}

//D2Client.0x6FAD7C20
uint32_t __fastcall sub_6FAD7C20(int a1, uint32_t a2, uint32_t a3)
{
	if (*(int*)(a1 + 0x3e) != 0)
	{
		*(uint32_t*)(a1 + 0x46) = 0;
		*(uint32_t*)(a1 + 0x3e) = 0;
	}
	return 0;
}

//D2Client.0x6FAD7C40
uint32_t __fastcall sub_6FAD7C40(void* a12, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS2)
{
	int iVar1;
	uint32_t uVar2;
	D2SplittedTextStrc* pDVar3;
	uint32_t uVar4;
	D2SplittedTextStrc* pFree;
	uint32_t uVar5;
	int iVar6;
	uint8_t a1;
	uint32_t* puVar7;
	int iStack_804;
	char acStack_800[2048];

	if ((*(int*)((int)a12 + 0x24) == 0) && ((pSMSGHANDLER_PARAMS2->lParam & 0x40000000U) != 0))
	{
		return 1;
	}
	if (pSMSGHANDLER_PARAMS2->wParam < 0x80)
	{
		a1 = (uint8_t)pSMSGHANDLER_PARAMS2->wParam;
		if (*(code**)((int)a12 + 4) == nullptr)
		{
			if (*(int*)((int)a12 + 0x20) == 0)
			{
				uVar4 = D2Win_10128(a1);
				if ((a1 == 0xd) || (a1 == 0x1b))
				{
					(**(code**)((int)a12 + 0x42))();
					goto LAB_6fad7f30;
				}
			}
			else
			{
				uVar4 = isdigit((int)(char)a1);
			}
		}
		else
		{
			uVar4 = (**(code**)((int)a12 + 4))();
		}
		if (a1 == 8)
		{
			if (0 < *(int*)((int)a12 + 0x3a))
			{
				iVar6 = *(int*)((int)a12 + 0x36);
				if ((iVar6 != *(int*)((int)a12 + 0x3a)) && (iVar6 != 0))
				{
					iVar6 = iVar6 + -1;
					while (true)
					{
						uVar4 = (uint32_t) * (uint16_t*)((int)a12 + 0x34);
						if ((int)*(uint32_t*)((int)a12 + 0x3a) < (int)(uint32_t) * (uint16_t*)((int)a12 + 0x34))
						{
							uVar4 = *(uint32_t*)((int)a12 + 0x3a);
						}
						if ((int)(uVar4 - 1) <= iVar6)
							break;
						iVar6 = iVar6 + 1;
						*(uint16_t*)(*(int*)((int)a12 + 0x28) + -2 + iVar6 * 2) =
						    *(uint16_t*)(*(int*)((int)a12 + 0x28) + iVar6 * 2);
					}
				}
				*(uint16_t*)(*(int*)((int)a12 + 0x28) + -2 + *(int*)((int)a12 + 0x3a) * 2) = 0;
				*(int*)((int)a12 + 0x3a) = *(int*)((int)a12 + 0x3a) + -1;
			}
			if (*(int*)((int)a12 + 0x36) != 0)
			{
				*(int*)((int)a12 + 0x36) = *(int*)((int)a12 + 0x36) + -1;
			}
		}
		else if (a1 == 0x2e)
		{
			if ((0 < *(int*)((int)a12 + 0x3a)) &&
			    (iVar6 = *(int*)((int)a12 + 0x36), iVar6 != *(int*)((int)a12 + 0x3a)))
			{
				while (true)
				{
					uVar4 = (uint32_t) * (uint16_t*)((int)a12 + 0x34);
					if ((int)*(uint32_t*)((int)a12 + 0x3a) < (int)(uint32_t) * (uint16_t*)((int)a12 + 0x34))
					{
						uVar4 = *(uint32_t*)((int)a12 + 0x3a);
					}
					if ((int)uVar4 <= iVar6)
						break;
					iVar6 = iVar6 + 1;
					*(uint16_t*)(*(int*)((int)a12 + 0x28) + -2 + iVar6 * 2) =
					    *(uint16_t*)(*(int*)((int)a12 + 0x28) + iVar6 * 2);
				}
				*(uint16_t*)(*(int*)((int)a12 + 0x28) + -2 + *(int*)((int)a12 + 0x3a) * 2) = 0;
				*(int*)((int)a12 + 0x3a) = *(int*)((int)a12 + 0x3a) + -1;
			}
		}
		else if (uVar4 == 0)
		{
			if (((a1 == 0x20) || (a1 == 0x1b)) || (a1 == 0xd))
			{
				return 0;
			}
		}
		else
		{
			uVar4 = *(uint32_t*)((int)a12 + 0x3a);
			uVar5 = (uint32_t) * (uint16_t*)((int)a12 + 0x34);
			if ((int)uVar4 < (int)(uVar5 - 1))
			{
				uVar2 = *(uint32_t*)((int)a12 + 0x36);
				if (uVar2 == uVar4)
				{
					*(short*)(*(int*)((int)a12 + 0x28) + uVar2 * 2) = (short)(char)a1;
					iVar6 = *(int*)((int)a12 + 0x36) + 1;
					*(int*)((int)a12 + 0x36) = iVar6;
					*(uint16_t*)(*(int*)((int)a12 + 0x28) + iVar6 * 2) = 0;
					*(int*)((int)a12 + 0x3a) = *(int*)((int)a12 + 0x3a) + 1;
				}
				else
				{
					if ((int)uVar4 < (int)uVar5)
					{
						uVar5 = uVar4;
					}
					if ((int)uVar2 <= (int)uVar5)
					{
						do
						{
							iVar1 = uVar5 * 2;
							iVar6 = uVar5 * 2;
							uVar5 = uVar5 - 1;
							*(uint16_t*)(*(int*)((int)a12 + 0x28) + iVar6) =
							    *(uint16_t*)(*(int*)((int)a12 + 0x28) + -2 + iVar1);
						} while (*(int*)((int)a12 + 0x36) <= (int)uVar5);
					}
					if (*(int*)((int)a12 + 0x3a) < (int)(uint32_t) * (uint16_t*)((int)a12 + 0x34))
					{
						*(int*)((int)a12 + 0x3a) = *(int*)((int)a12 + 0x3a) + 1;
					}
					*(uint16_t*)(*(int*)((int)a12 + 0x28) + *(int*)((int)a12 + 0x3a) * 2) = 0;
					*(short*)(*(int*)((int)a12 + 0x28) + *(int*)((int)a12 + 0x36) * 2) =
					    (short)(char)a1;
				}
			}
			if (*(int*)((int)a12 + 0x3a) != 0)
			{
				D2Win_10127_SetFont(*(Font*)((int)a12 + 0x4e));
				pFree = D2Win_10199(*(Unicode**)((int)a12 + 0x28), &iStack_804,
				    *(int*)((int)a12 + 0x18));
				while (pFree != nullptr)
				{
					pDVar3 = pFree->pNextLine;
					D2_FREE(pFree->wszLine);
					D2_FREE(pFree);
					pFree = pDVar3;
				}
				if (*(int*)((int)a12 + 0x1c) < iStack_804)
				{
					iVar6 = *(int*)((int)a12 + 0x3a) + -1;
					*(int*)((int)a12 + 0x36) = *(int*)((int)a12 + 0x36) + -1;
					*(int*)((int)a12 + 0x3a) = iVar6;
					*(uint16_t*)(*(int*)((int)a12 + 0x28) + iVar6 * 2) = 0;
				}
			}
			if ((*(int*)((int)a12 + 4) == 0) &&
			    (iVar6 = Unicode::strlen(*(Unicode**)((int)a12 + 0x28)), iVar6 != 0))
			{
				if (*(int*)((int)a12 + 0x20) == 0)
				{
					iVar6 = Unicode::strlen(*(Unicode**)((int)a12 + 0x28));
					*(int*)((int)a12 + 0x3a) = iVar6;
				}
				else
				{
					Unicode::toUtf(acStack_800, *(Unicode**)((int)a12 + 0x28),
					    (uint32_t) * (uint16_t*)((int)a12 + 0x34));
					uVar4 = *(uint32_t*)((int)a12 + 0x30);
					uVar5 = atoi(acStack_800);
					if (uVar4 < uVar5)
					{
						sprintf(acStack_800, "%d", uVar4);
						uVar4 = (uint32_t) * (uint16_t*)((int)a12 + 0x34) * 2;
						puVar7 = *(uint32_t**)((int)a12 + 0x28);
						for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
						{
							*puVar7 = 0;
							puVar7 = puVar7 + 1;
						}
						for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
						{
							*(uint8_t*)puVar7 = 0;
							puVar7 = (uint32_t*)((int)puVar7 + 1);
						}
						Unicode::win2Unicode(*(Unicode**)((int)a12 + 0x28), acStack_800,
						    (uint32_t) * (uint16_t*)((int)a12 + 0x34));
						iVar6 = Unicode::strlen(*(Unicode**)((int)a12 + 0x28));
						*(int*)((int)a12 + 0x3a) = iVar6;
						*(int*)((int)a12 + 0x36) = iVar6;
					}
				}
			}
		}
	}
LAB_6fad7f30:
	pSMSGHANDLER_PARAMS2->lResult = 0;
	pSMSGHANDLER_PARAMS2->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS2);
	return 1;
}

//D2Client.0x6FAD7F60
uint32_t __cdecl sub_6FAD7F60(uint32_t a1)
{
	return 0;
}

//D2Client.0x6FAD7F70
void __fastcall sub_6FAD7F70(void* a1, uint32_t a2, uint32_t a3)
{
	*(uint32_t*)((int)a1 + 0x18) = a3;
}

//D2Client.0x6FAD7F80
void __fastcall sub_6FAD7F80(void* a1, uint32_t a2, uint32_t a3)
{
	*(uint32_t*)((int)a1 + 0x24) = a3;
}

//D2Client.0x6FAD7F90
uint32_t __fastcall sub_6FAD7F90(int a1, uint32_t a2, uint32_t a3)
{
	if (*(int*)(a1 + 0x36) < *(int*)(a1 + 0x3a))
	{
		*(int*)(a1 + 0x36) = *(int*)(a1 + 0x36) + 1;
	}
	return 1;
}

//D2Client.0x6FAD7FB0
uint32_t __fastcall sub_6FAD7FB0(int a1, uint32_t a2, uint32_t a3)
{
	if (0 < *(int*)(a1 + 0x36))
	{
		*(int*)(a1 + 0x36) = *(int*)(a1 + 0x36) + -1;
	}
	return 1;
}

//D2Client.0x6FAD7FD0
void __fastcall sub_6FAD7FD0(uint32_t* a1)
{
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6EF80);
	local_4 = 0;
	if ((uint32_t*)a1[2] != nullptr)
	{
		(*(code*)**(uint32_t**)a1[2])(1);
	}
	local_4 = 0xffffffff;
	sub_6FAEFD30(a1);
}

//D2Client.0x6FAD8030
void* __fastcall sub_6FAD8030(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAD7FD0((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAD8060
void* __fastcall sub_6FAD8060(void* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10)
{
	void* pvVar1;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*(uint8_t***)a1 = &gpuint8_t_6FB6EF80;
	pvVar1 = SMemAlloc(0x5a, "new", -1, 0);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	if (pvVar1 == nullptr)
	{
		pvVar1 = nullptr;
	}
	else
	{
		pvVar1 = sub_6FAD7540(pvVar1, a3, a3, a4, a5, a6, a7, a8, a9,
		    a10);
	}
	*(void**)((int)a1 + 8) = pvVar1;
	return a1;
}

//D2Client.0x6FAD8100
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8100(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x10))();
}

//D2Client.0x6FAD8110
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8110(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x14))();
}

//D2Client.0x6FAD8120
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8120(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x18))();
}

//D2Client.0x6FAD8130
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8130(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x20))();
}

//D2Client.0x6FAD8140
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8140(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x1c))();
}

//D2Client.0x6FAD8150
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8150(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x24))();
}

//D2Client.0x6FAD8160
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8160(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x28))();
}

//D2Client.0x6FAD8170
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8170(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x2c))();
}

//D2Client.0x6FAD8180
void __fastcall sub_6FAD8180(int a1, uint32_t a2, uint32_t a3)
{
	(**(code**)(**(int**)(a1 + 8) + 0x34))();
}

//D2Client.0x6FAD8190
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD8190(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x3c))();
}

//D2Client.0x6FAD81A0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD81A0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x38))();
}

//D2Client.0x6FAD81B0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD81B0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x30))();
}

//D2Client.0x6FAD81C0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD81C0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x40))();
}

//D2Client.0x6FAD81D0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD81D0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x44))();
}

//D2Client.0x6FAD81E0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD81E0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x48))();
}

//D2Client.0x6FAD81F0
void __cdecl sub_6FAD81F0()
{
	D2GameResolutionMode DVar1;
	char* pcVar2;

	DVar1 = D2GFX_GetResolutionMode();
	if (DVar1 == NUM_GAME_RESOLUTIONS)
	{
		if (gpCellFile_6FBB3650 == nullptr)
		{
			pcVar2 = "Menu\\800helpborder";
			goto LAB_6fad8236;
		}
		CLIENT_FreeCellFile(gpCellFile_6FBB3650);
		pcVar2 = "Menu\\800helpborder";
	}
	else
	{
		if (gpCellFile_6FBB3650 == nullptr)
		{
			pcVar2 = "Menu\\helpborder";
			goto LAB_6fad8236;
		}
		CLIENT_FreeCellFile(gpCellFile_6FBB3650);
		pcVar2 = "Menu\\helpborder";
	}
	gpCellFile_6FBB3650 = nullptr;
LAB_6fad8236:
	gpCellFile_6FBB3650 = sub_6FB20100(pcVar2);
	if (gpCellFile_6FBB3654 == nullptr)
	{
		gpCellFile_6FBB3654 = sub_6FB20100("Menu\\helpwhitebullet");
	}
	if (gpCellFile_6FBB3658 == nullptr)
	{
		gpCellFile_6FBB3658 = sub_6FB20100("Menu\\helpyellowbullet");
	}
}

//D2Client.0x6FAD8280
int __fastcall sub_6FAD8280(uint32_t a1, int a2)
{
	Unicode* pUVar1;
	int iVar2;
	Unicode local_c8[100];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a1));
	Unicode::strcpy(local_c8, pUVar1);
	iVar2 = D2Win_10121_GetTextWidth(local_c8);
	return a2 - iVar2 / 2;
}

//D2Client.0x6FAD82E0
void __cdecl sub_6FAD82E0()
{
	uint32_t uVar1;

	uVar1 = sub_6FB01C50();
	sub_6FB5B0F0(0, 0, gnScreenWidth, gnScreenHeight + -0x31, CONCAT31((int32_t)((uint32_t)uVar1 >> 8), byte_6FBB365C), (DrawMode)(1));
}

//D2Client.0x6FAD8310
void __cdecl sub_6FAD8310()
{
	int iVar1;
	D2GameResolutionMode DVar2;
	int nYPos;
	D2GfxDataStrc* pDVar3;
	D2GfxDataStrc DStack_48;

	iVar1 = sub_6FB23230(0x15);
	if (iVar1 == 0)
	{
		sub_6FB23260(0x15, 0, 0);
		dword_6FBB3664 = 1;
	}
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		pDVar3 = &DStack_48;
		for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			pDVar3->pCurrentCell = nullptr;
			pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
		}
		DStack_48.pCellFile = gpCellFile_6FBB3650;
		DStack_48.nDirection = 0;
		DStack_48.nFrame = 0;
		TEXTURE_CelDraw(&DStack_48, 0, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 1;
		TEXTURE_CelDraw(&DStack_48, 0, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 2;
		TEXTURE_CelDraw(&DStack_48, 0x42, 0x14, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 3;
		TEXTURE_CelDraw(&DStack_48, 0x142, 0x14, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 4;
		TEXTURE_CelDraw(&DStack_48, 0x217, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 5;
		TEXTURE_CelDraw(&DStack_48, 0x30c, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		DStack_48.nFrame = 6;
		TEXTURE_CelDraw(&DStack_48, 0x30c, 0x200, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		pDVar3 = &DStack_48;
		for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			pDVar3->pCurrentCell = nullptr;
			pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
		}
		DStack_48.pCellFile = sub_6FB24110();
		DStack_48.nDirection = 0;
		DStack_48.nFrame = (dword_6FBB3660 != 0) + 10;
		DVar2 = D2GFX_GetResolutionMode();
		if (DVar2 == NUM_GAME_RESOLUTIONS)
		{
			iVar1 = 0x2ad;
		}
		else
		{
			iVar1 = 0x20d;
		}
		TEXTURE_CelDraw(&DStack_48, iVar1, 0x38, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		pDVar3 = &DStack_48;
		for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			pDVar3->pCurrentCell = nullptr;
			pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
		}
		DStack_48.pCellFile = gpCellFile_6FBB3658;
		DStack_48.nDirection = 0;
		DStack_48.nFrame = 0;
		nYPos = 0x49;
		iVar1 = 8;
		do
		{
			TEXTURE_CelDraw(&DStack_48, 0x68, nYPos, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			nYPos = nYPos + 0x14;
			iVar1 = iVar1 + -1;
		} while (iVar1 != 0);
		pDVar3 = &DStack_48;
		for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			pDVar3->pCurrentCell = nullptr;
			pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
		}
		DStack_48.pCellFile = gpCellFile_6FBB3654;
		DStack_48.nDirection = 0;
		DStack_48.nFrame = 0;
		TEXTURE_CelDraw(&DStack_48, 0x37, 0x217, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x3a, 0x1e6, 0x3a, 0x214, 0xff, 0xff);
		D2GFX_DrawLine(0x3b, 0x1e6, 0x3b, 0x214, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x82, 0x234, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x85, 0x1bd, 0x85, 0x231, 0xff, 0xff);
		D2GFX_DrawLine(0x86, 0x1bd, 0x86, 0x231, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0xd9, 0x23f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0xdc, 0x177, 0xdc, 0x23c, 0xff, 0xff);
		D2GFX_DrawLine(0xdd, 0x177, 0xdd, 0x23c, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x104, 0x249, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x107, 0x20e, 0x107, 0x246, 0xff, 0xff);
		D2GFX_DrawLine(0x108, 0x20e, 0x108, 0x246, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x136, 0x249, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x139, 0x1e6, 0x139, 0x246, 0xff, 0xff);
		D2GFX_DrawLine(0x13a, 0x1e6, 0x13a, 0x246, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x16d, 0x235, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x170, 0x20d, 0x170, 0x232, 0xff, 0xff);
		D2GFX_DrawLine(0x171, 0x20d, 0x171, 0x232, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x1bd, 0x21c, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x1c0, 0x1c3, 0x1c0, 0x219, 0xff, 0xff);
		D2GFX_DrawLine(0x1c1, 0x1c3, 0x1c1, 0x219, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x212, 0x239, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x215, 0x20d, 0x215, 0x236, 0xff, 0xff);
		D2GFX_DrawLine(0x216, 0x20d, 0x216, 0x236, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x23c, 0x23f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x23f, 0x177, 0x23f, 0x23c, 0xff, 0xff);
		D2GFX_DrawLine(0x240, 0x177, 0x240, 0x23c, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x29e, 0x234, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x2a1, 0x1bd, 0x2a1, 0x231, 0xff, 0xff);
		D2GFX_DrawLine(0x2a2, 0x1bd, 0x2a2, 0x231, 0xff, 0xff);
		TEXTURE_CelDraw(&DStack_48, 0x2e4, 0x217, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		D2GFX_DrawLine(0x2e7, 0x1e6, 0x2e7, 0x214, 0xff, 0xff);
		D2GFX_DrawLine(0x2e8, 0x1e6, 0x2e8, 0x214, 0xff, 0xff);
		sub_6FAD8E50();
		return;
	}
	sub_6FAD8920();
	sub_6FADA0D0();
	sub_6FAD8A70();
	sub_6FAD8AD0();
	sub_6FAD97D0();
}

//D2Client.0x6FAD8920
void __cdecl sub_6FAD8920()
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc local_48;

	pDVar1 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar1->pCurrentCell = 0;
		pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
	}
	local_48.pCellFile = gpCellFile_6FBB3650;
	local_48.nDirection = 0;
	local_48.nFrame = 0;
	TEXTURE_CelDraw(&local_48, 0, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 1;
	TEXTURE_CelDraw(&local_48, 0x100, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 2;
	TEXTURE_CelDraw(&local_48, 0, gnScreenHeight + -0x30, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 3;
	TEXTURE_CelDraw(&local_48, 0x100, gnScreenHeight + -0x30, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 4;
	TEXTURE_CelDraw(&local_48, 0x140, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 5;
	TEXTURE_CelDraw(&local_48, 0x240, 0x100, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 6;
	TEXTURE_CelDraw(&local_48, 0x140, gnScreenHeight + -0x30, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 7;
	TEXTURE_CelDraw(&local_48, 0x240, gnScreenHeight + -0x30, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FAD8A70
void __cdecl sub_6FAD8A70()
{
	int iVar1;
	int nYPos;
	D2GfxDataStrc* pDVar2;
	D2GfxDataStrc local_48;

	nYPos = 0x49;
	pDVar2 = &local_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar2->pCurrentCell = nullptr;
		pDVar2 = (D2GfxDataStrc*)&pDVar2->pCellFile;
	}
	local_48.nDirection = 0;
	local_48.pCellFile = gpCellFile_6FBB3658;
	local_48.nFrame = 0;
	iVar1 = 8;
	do
	{
		TEXTURE_CelDraw(&local_48, 0x68, nYPos, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		nYPos = nYPos + 0x14;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD8AD0
void __cdecl sub_6FAD8AD0()
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc local_48;

	pDVar1 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar1->pCurrentCell = 0;
		pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
	}
	local_48.pCellFile = gpCellFile_6FBB3654;
	local_48.nDirection = 0;
	local_48.nFrame = 0;
	TEXTURE_CelDraw(&local_48, 0x33, 0x19e, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x36, 0x16d, 0x36, 0x19b, 0xff, 0xff);
	D2GFX_DrawLine(0x37, 0x16d, 0x37, 0x19b, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x7f, 0x1bc, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x82, 0x145, 0x82, 0x1b9, 0xff, 0xff);
	D2GFX_DrawLine(0x83, 0x145, 0x83, 0x1b9, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0xb2, 0x1d0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0xb5, 0x195, 0xb5, 0x1cd, 0xff, 0xff);
	D2GFX_DrawLine(0xb6, 0x195, 0xb6, 0x1cd, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0xe3, 0x1d0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0xe6, 0x16d, 0xe6, 0x1cd, 0xff, 0xff);
	D2GFX_DrawLine(0xe7, 0x16d, 0xe7, 0x1cd, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x11c, 0x1bd, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x11f, 0x195, 0x11f, 0x1ba, 0xff, 0xff);
	D2GFX_DrawLine(0x120, 0x195, 0x120, 0x1ba, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x15e, 0x19f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x161, 0x145, 0x161, 0x19b, 0xff, 0xff);
	D2GFX_DrawLine(0x162, 0x145, 0x162, 0x19b, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x1bd, 0x1c2, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x1c0, 0x195, 0x1c0, 0x1be, 0xff, 0xff);
	D2GFX_DrawLine(0x1c1, 0x195, 0x1c1, 0x1be, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x1f7, 0x1bd, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x1fa, 0x145, 0x1fa, 0x1b9, 0xff, 0xff);
	D2GFX_DrawLine(0x1fb, 0x145, 0x1fb, 0x1b9, 0xff, 0xff);
	TEXTURE_CelDraw(&local_48, 0x246, 0x19f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2GFX_DrawLine(0x249, 0x16d, 0x249, 0x19b, 0xff, 0xff);
	D2GFX_DrawLine(0x24a, 0x16d, 0x24a, 0x19b, 0xff, 0xff);
}

//D2Client.0x6FAD8E50
void __cdecl sub_6FAD8E50()
{
	Unicode* pUVar1;
	Font nFontSize;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	Unicode local_4b0[100];
	Unicode aUStack_3e8[100];
	Unicode aUStack_320[100];
	Unicode aUStack_258[100];
	Unicode aUStack_190[100];
	Unicode aUStack_c8[100];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1066));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x11;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1066));
	D2Win_10117_DrawText(pUVar1, 0x17c - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x49;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
	D2Win_10117_DrawText(pUVar1, 0x2bd - iVar3 / 2, iVar4, iVar5, iVar6);
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL12);
	pUVar1 = sub_6FAD4F50(0x22, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1067));
	Unicode::sprintf(100, aUStack_190, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_190, 0x75, 0x4e, 0, 0);
	pUVar1 = sub_6FAD4F50(0x25, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1068));
	Unicode::sprintf(100, aUStack_3e8, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_3e8, 0x75, 0x62, 0, 0);
	pUVar1 = sub_6FAD4F50(0x24, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1069));
	Unicode::sprintf(100, aUStack_320, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_320, 0x75, 0x76, 0, 0);
	pUVar1 = sub_6FAD4F50(7, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106a));
	Unicode::sprintf(100, aUStack_258, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_258, 0x75, 0x8a, 0, 0);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0x9e;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106b));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0xb2;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106c));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0xc6;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106d));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	pUVar1 = sub_6FAD4F50(6, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106e));
	Unicode::sprintf(100, aUStack_c8, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_c8, 0x75, 0xda, 0, 0);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106f));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1e1;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106f));
	D2Win_10117_DrawText(pUVar1, 0x3b - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1070));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x19a;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1070));
	D2Win_10117_DrawText(pUVar1, 0x86 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1a9;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	D2Win_10117_DrawText(pUVar1, 0x86 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1b8;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	D2Win_10117_DrawText(pUVar1, 0x86 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x177;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
	D2Win_10117_DrawText(pUVar1, 0xde - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1074));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1fa;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1074));
	D2Win_10117_DrawText(pUVar1, 0x108 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1075));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x209;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1075));
	D2Win_10117_DrawText(pUVar1, 0x108 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1076));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1e1;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1076));
	D2Win_10117_DrawText(pUVar1, 0x13a - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1077));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1f9;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1077));
	D2Win_10117_DrawText(pUVar1, 0x171 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1078));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x208;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1078));
	D2Win_10117_DrawText(pUVar1, 0x171 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1079));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x191;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1079));
	D2Win_10117_DrawText(pUVar1, 0x1c1 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107a));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1a0;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107a));
	D2Win_10117_DrawText(pUVar1, 0x1c1 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107b));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1af;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107b));
	D2Win_10117_DrawText(pUVar1, 0x1c1 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107c));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1be;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107c));
	D2Win_10117_DrawText(pUVar1, 0x1c1 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107d));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x208;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107d));
	D2Win_10117_DrawText(pUVar1, 0x216 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x177;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
	D2Win_10117_DrawText(pUVar1, 0x23c - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1073));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x19a;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1073));
	D2Win_10117_DrawText(pUVar1, 0x2a2 - iVar3 / 2, iVar4, iVar5, iVar6);
	iVar3 = sub_6FAD8280(0x1071, 0x2a2);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1a9;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar4, iVar5, iVar6);
	iVar3 = sub_6FAD8280(0x1072, 0x2a2);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1b8;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar4, iVar5, iVar6);
	iVar3 = sub_6FAD8280(0x107e, 0x2e8);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x1e1;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107e));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar4, iVar5, iVar6);
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FAD97D0
void __cdecl sub_6FAD97D0()
{
	Unicode* pUVar1;
	Font nFontSize;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	Unicode local_4b0[100];
	Unicode aUStack_3e8[100];
	Unicode aUStack_320[100];
	Unicode aUStack_258[100];
	Unicode aUStack_190[100];
	Unicode aUStack_c8[100];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1066));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x11;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1066));
	D2Win_10117_DrawText(pUVar1, 0x131 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x49;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
	D2Win_10117_DrawText(pUVar1, 0x21d - iVar3 / 2, iVar4, iVar5, iVar6);
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL12);
	pUVar1 = sub_6FAD4F50(0x22, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1067));
	Unicode::sprintf(100, aUStack_190, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_190, 0x75, 0x4e, 0, 0);
	pUVar1 = sub_6FAD4F50(0x25, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1068));
	Unicode::sprintf(100, aUStack_3e8, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_3e8, 0x75, 0x62, 0, 0);
	pUVar1 = sub_6FAD4F50(0x24, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1069));
	Unicode::sprintf(100, aUStack_320, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_320, 0x75, 0x76, 0, 0);
	pUVar1 = sub_6FAD4F50(7, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106a));
	Unicode::sprintf(100, aUStack_258, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_258, 0x75, 0x8a, 0, 0);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0x9e;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106b));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0xb2;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106c));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	iVar5 = 0;
	iVar4 = 0;
	iVar3 = 0xc6;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106d));
	D2Win_10117_DrawText(pUVar1, 0x75, iVar3, iVar4, iVar5);
	pUVar1 = sub_6FAD4F50(6, 1);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106e));
	Unicode::sprintf(100, aUStack_c8, pUVar2, pUVar1);
	D2Win_10117_DrawText(aUStack_c8, 0x75, 0xda, 0, 0);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106f));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x168;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x106f));
	D2Win_10117_DrawText(pUVar1, 0x37 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1070));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x122;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1070));
	D2Win_10117_DrawText(pUVar1, 0x83 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x131;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	D2Win_10117_DrawText(pUVar1, 0x83 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x140;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	D2Win_10117_DrawText(pUVar1, 0x83 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1074));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x181;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1074));
	D2Win_10117_DrawText(pUVar1, 0xb6 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1075));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 400;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1075));
	D2Win_10117_DrawText(pUVar1, 0xb6 - iVar3 / 2, iVar4, iVar5, iVar6);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1076));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x168;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1076));
	D2Win_10117_DrawText(pUVar1, 0xe7 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1077));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x181;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1077));
	D2Win_10117_DrawText(pUVar1, 0x120 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1078));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 400;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1078));
	D2Win_10117_DrawText(pUVar1, 0x120 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1079));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x113;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1079));
	D2Win_10117_DrawText(pUVar1, 0x162 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107a));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x122;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107a));
	D2Win_10117_DrawText(pUVar1, 0x162 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107b));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x131;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107b));
	D2Win_10117_DrawText(pUVar1, 0x162 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107c));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x140;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107c));
	D2Win_10117_DrawText(pUVar1, 0x162 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107d));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 400;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107d));
	D2Win_10117_DrawText(pUVar1, 0x1c1 - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1073));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x122;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1073));
	D2Win_10117_DrawText(pUVar1, 0x1fb - iVar3 / 2, iVar4, iVar5, iVar6);
	memset(local_4b0, 0, 2 * (100));
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	Unicode::strcpy(local_4b0, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_4b0);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x131;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1071));
	D2Win_10117_DrawText(pUVar1, 0x1fb - iVar3 / 2, iVar4, iVar5, iVar6);
	iVar3 = sub_6FAD8280(0x1072, 0x1fb);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x140;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1072));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar4, iVar5, iVar6);
	iVar3 = sub_6FAD8280(0x107e, 0x24a);
	iVar6 = 0;
	iVar5 = 0;
	iVar4 = 0x168;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x107e));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar4, iVar5, iVar6);
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FADA0D0
void __cdecl sub_6FADA0D0()
{
	D2GfxDataStrc* pDVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	D2GfxDataStrc local_48;

	pDVar1 = &local_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar1->pCurrentCell = 0;
		pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
	}
	local_48.pCellFile = sub_6FB24110();
	local_48.nDirection = 0;
	local_48.nFrame = (dword_6FBB3660 != 0) + 10;
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		TEXTURE_CelDraw(&local_48, 0x2ad, 0x38, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		return;
	}
	TEXTURE_CelDraw(&local_48, 0x20d, 0x38, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FADA140
void __cdecl sub_6FADA140()
{
	if (gpCellFile_6FBB3650 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB3650);
		gpCellFile_6FBB3650 = nullptr;
	}
	if (gpCellFile_6FBB3654 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB3654);
		gpCellFile_6FBB3654 = nullptr;
	}
	if (gpCellFile_6FBB3658 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB3658);
		gpCellFile_6FBB3658 = nullptr;
	}
}

//D2Client.0x6FADA190
void __cdecl sub_6FADA190(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	uint16_t uVar2;
	int iVar3;
	D2GameResolutionMode DVar4;
	uint32_t uVar5;
	bool bVar6;
	bool bVar7;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t)uVar1;
	uVar2 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	DVar4 = D2GFX_GetResolutionMode();
	if (DVar4 == NUM_GAME_RESOLUTIONS)
	{
		if (uVar1 < 0x2ad)
			goto LAB_6fada1f7;
		bVar7 = SBORROW4(uVar5, 0x2cd);
		iVar3 = -0x2cd;
		bVar6 = uVar5 == 0x2cd;
	}
	else
	{
		if (uVar1 < 0x20d)
			goto LAB_6fada1f7;
		bVar7 = SBORROW4(uVar5, 0x22d);
		iVar3 = -0x22d;
		bVar6 = uVar5 == 0x22d;
	}
	if (((bVar6 || bVar7 != (int)(uVar5 + iVar3) < 0) && (0x17 < uVar2)) && (uVar2 < 0x39))
	{
		dword_6FBB3660 = 1;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
LAB_6fada1f7:
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADA220
void __cdecl sub_6FADA220(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	uint16_t uVar2;
	int iVar3;
	D2GameResolutionMode DVar4;
	uint32_t uVar5;
	bool bVar6;
	bool bVar7;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t)uVar1;
	uVar2 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if (dword_6FBB3660 != 0)
	{
		DVar4 = D2GFX_GetResolutionMode();
		if (DVar4 == NUM_GAME_RESOLUTIONS)
		{
			if (0x2ac < uVar1)
			{
				bVar7 = SBORROW4(uVar5, 0x2cd);
				iVar3 = -0x2cd;
				bVar6 = uVar5 == 0x2cd;
			LAB_6fada267:
				if (((bVar6 || bVar7 != (int)(uVar5 + iVar3) < 0) && (0x17 < uVar2)) && (uVar2 < 0x39))
				{
					sub_6FB23260(0x21, 2, 0);
					if (dword_6FBB3664 != 0)
					{
						sub_6FB23260(0x15, 1, 0);
						dword_6FBB3664 = 0;
					}
					goto LAB_6fada2ae;
				}
			}
		}
		else if (0x20c < uVar1)
		{
			bVar7 = SBORROW4(uVar5, 0x22d);
			iVar3 = -0x22d;
			bVar6 = uVar5 == 0x22d;
			goto LAB_6fada267;
		}
	}
	dword_6FBB3660 = 0;
	sub_6FAABF60();
LAB_6fada2ae:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADA2D0
void __cdecl sub_6FADA2D0(uint32_t a1)
{
	sub_6FB23260(0x21, 1, 0);
	if (dword_6FBB3664 != 0)
	{
		sub_6FB23260(0x15, 1, 0);
		dword_6FBB3664 = 0;
	}
}

//D2Client.0x6FADA310
void __cdecl sub_6FADA310(uint32_t a1)
{
	return;
}

//D2Client.0x6FADA320
void __cdecl sub_6FADA320()
{
	if (dword_6FBB3664 != 0)
	{
		sub_6FB23260(0x15, 1, 0);
		dword_6FBB3664 = 0;
	}
}

//D2Client.0x6FADA350
void __cdecl sub_6FADA350()
{
	int iVar1;
	Unicode* pUVar2;
	uint32_t uVar3;
	Unicode* pUVar4;
	D2GfxDataStrc* pDVar5;
	Unicode aUStack_214[30];
	D2GfxDataStrc local_1d8;
	Unicode aUStack_190[200];

	iVar1 = sub_6FB23230(4);
	if (iVar1 == 0)
	{
		iVar1 = sub_6FB23230(3);
		if (iVar1 == 0)
		{
			iVar1 = sub_6FB23230(1);
			if (iVar1 == 0)
			{
				iVar1 = sub_6FB23230(0xc);
				if (iVar1 == 0)
				{
					iVar1 = sub_6FB23230(0x17);
					if (iVar1 == 0)
					{
						iVar1 = sub_6FB23230(0x19);
						if (iVar1 == 0)
						{
							dword_6FBB366C = 0;
							if (dword_6FB79088 == -1)
							{
								dword_6FB79088 = 0;
								SRegLoadValue("Diablo II", (const char*)(dword_6FB78C6B + 1), 1, (DWORD*)((uint32_t*)&dword_6FB79088));
							}
							if (dword_6FB79088 == 0)
							{
								pDVar5 = &local_1d8;
								for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
								{
									pDVar5->pCurrentCell = nullptr;
									pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
								}
								pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1051));
								Unicode::strcpy(aUStack_190, pUVar2);
								uVar3 = sub_6FAD4B60(6, 1);
								if ((short)uVar3 != -1)
								{
									pUVar2 = aUStack_214;
									for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1)
									{
										*(uint32_t*)pUVar2 = 0;
										pUVar2 = pUVar2 + 2;
									}
									pUVar2 = sub_6FAD56B0(6, 1);
									pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
									Unicode::sprintf(0x1e, aUStack_214, pUVar4, pUVar2);
									Unicode::strcat(aUStack_190, aUStack_214);
								}
								uVar3 = sub_6FAD4B60(6, 0);
								if ((short)uVar3 != -1)
								{
									pUVar2 = aUStack_214;
									for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1)
									{
										*(uint32_t*)pUVar2 = 0;
										pUVar2 = pUVar2 + 2;
									}
									pUVar2 = sub_6FAD56B0(6, 0);
									pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
									Unicode::sprintf(0x1e, aUStack_214, pUVar4, pUVar2);
									Unicode::strcat(aUStack_190, aUStack_214);
								}
								iVar1 = D2Win_10121_GetTextWidth(aUStack_190);
								D2Win_10117_DrawText(aUStack_190, (gnScreenWidth - iVar1 / 2) + -0x3a, gnScreenHeight + -0xc5, 0, 0);
								local_1d8.pCellFile = gpCellFile_6FBB5BB8;
								local_1d8.nDirection = 0;
								local_1d8.nFrame = 0;
								TEXTURE_CelDraw(&local_1d8, gnScreenWidth + -0x4b, gnScreenHeight + -0xa0, 0xffffffff,
								    DRAWMODE_NORMAL, nullptr);
								local_1d8.pCellFile = gpCellFile_6FBB5BB4;
								local_1d8.nFrame = (uint32_t)(dword_6FBB3668 != 0);
								TEXTURE_CelDraw(&local_1d8, gnScreenWidth + -0x48, gnScreenHeight + -0xa4, 0xffffffff,
								    DRAWMODE_NORMAL, nullptr);
								return;
							}
							sub_6FB23260(0x22, 1, 0);
							return;
						}
					}
				}
			}
		}
	}
	dword_6FBB366C = 1;
}

//D2Client.0x6FADA5F0
void __cdecl sub_6FADA5F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar4 = gnScreenHeight;
	iVar3 = gnScreenWidth;
	if (dword_6FBB366C == 0)
	{
		iVar2 = gnScreenHeight + -0xa0;
		iVar1 = gnScreenWidth + -0x4b;
		iVar5 = sub_6FB57BC0();
		iVar6 = sub_6FB57BD0();
		if ((((iVar1 <= iVar5) && (iVar5 <= iVar3 + -0x28)) && (iVar4 + -0xc4 <= iVar6)) &&
		    (iVar6 <= iVar2))
		{
			dword_6FBB3668 = 1;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
}

//D2Client.0x6FADA660
void __cdecl sub_6FADA660(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar4 = gnScreenHeight;
	iVar3 = gnScreenWidth;
	if (dword_6FBB366C == 0)
	{
		iVar2 = gnScreenHeight + -0xa0;
		iVar1 = gnScreenWidth + -0x4b;
		iVar5 = sub_6FB57BC0();
		iVar6 = sub_6FB57BD0();
		if ((((iVar1 <= iVar5) && (iVar5 <= iVar3 + -0x28)) && (iVar4 + -0xc4 <= iVar6)) &&
		    (iVar6 <= iVar2))
		{
			sub_6FB23260(0x22, 1, 0);
			sub_6FB23260(0x21, 2, 0);
			dword_6FB79088 = 1;
			SRegSaveValue("Diablo II", (const char*)(dword_6FB78C6B + 1), 1, 1);
			dword_6FBB3668 = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
}

//D2Client.0x6FADA710
bool __cdecl sub_6FADA710()
{
	return dword_6FBB3690 != 2;
}

#include "Game/PalShift.h"

#include "Game/Game.h"
#include "Unit/CUnit.h"

//D2Client.0x6FBA7C10
int32_t dword_6FBA7C10;
//D2Client.0x6FBA7C14
int32_t* gpint32_t_6FBA7C14;
//D2Client.0x6FBA7C18
uint8_t byte_6FBA7C18[7680];
//D2Client.0x6FBA9A18
int32_t dword_6FBA9A18;
//D2Client.0x6FBA9A1C
uint8_t* ptr_6FBA9A1C;

//D2Client.0x6FAADEA0
void __cdecl sub_6FAADEA0()
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t* puVar4;
	HSFILE__* pHStack_8;
	HSFILE__* pHStack_4;

	uVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) << 3;
	dword_6FBA7C10 = (int)D2_ALLOC(uVar3);
	puVar4 = (uint32_t*)dword_6FBA7C10;
	for (uVar3 = uVar3 >> 2; uVar3 != 0; uVar3 = uVar3 - 1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*(uint8_t*)puVar4 = 0;
		puVar4 = (uint32_t*)((int)puVar4 + 1);
	}
	iVar1 = 0;
	iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80);
	if (0 < iVar2)
	{
		do
		{
			*(int*)(dword_6FBA7C10 + iVar1 * 8) = iVar1;
			iVar1 = iVar1 + 1;
		} while (iVar1 < iVar2);
	}
	gpint32_t_6FBA7C14 = nullptr;
	iVar2 = ARCHIVE_OpenFile(0, "Data\\Global\\Monsters\\RandTransforms.dat", &pHStack_8, 1);
	if (iVar2 != 0)
	{
		ARCHIVE_ReadFileToBuffer(nullptr, pHStack_8, (D2CellFileStrc*)byte_6FBA7C18, 0x1e00);
		ARCHIVE_CloseFile(0, pHStack_8);
		dword_6FBA9A18 = 1;
	}
	iVar2 = ARCHIVE_OpenFile(0, "Data\\Global\\Monsters\\GreenBlood.dat", &pHStack_4, 1);
	if (iVar2 != 0)
	{
		ptr_6FBA9A1C = (uint8_t*)(D2_ALLOC(0x100));
		puVar4 = (uint32_t*)ptr_6FBA9A1C;
		for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		ARCHIVE_ReadFileToBuffer(nullptr, pHStack_4, (D2CellFileStrc*)ptr_6FBA9A1C, 0x100);
		ARCHIVE_CloseFile(0, pHStack_4);
	}
}

//D2Client.0x6FAADFB0
void __cdecl sub_6FAADFB0()
{
	int* piVar1;

	if (gpint32_t_6FBA7C14 != nullptr)
	{
		do
		{
			piVar1 = (int*)gpint32_t_6FBA7C14[0x401];
			D2_FREE(gpint32_t_6FBA7C14);
			gpint32_t_6FBA7C14 = piVar1;
		} while (piVar1 != nullptr);
		gpint32_t_6FBA7C14 = nullptr;
	}
	if (dword_6FBA7C10 != 0)
	{
		D2_FREE((void*)dword_6FBA7C10);
		dword_6FBA7C10 = 0;
	}
	if (ptr_6FBA9A1C != nullptr)
	{
		D2_FREE(ptr_6FBA9A1C);
		ptr_6FBA9A1C = nullptr;
	}
}

//D2Client.0x6FAAE030
void __fastcall sub_6FAAE030(int a1)
{
	char cVar1;
	int* piVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t uVar5;
	char* pcVar6;
	char* pcVar7;
	char* pcVar8;
	char* local_130;
	char* local_12c;
	HSFILE__* local_118;
	int* local_114;
	char local_110[260];
	int local_c;
	int local_8;

	local_c = sub_6FAAE570(a1);
	if ((local_c != 0) && (piVar2 = sub_6FAAE2E0(a1), piVar2 == nullptr))
	{
		if (*(char*)(local_c + 0x10) == ' ')
		{
			local_110[0] = '\0';
		}
		else
		{
			local_110[0] = *(char*)(local_c + 0x10);
		}
		if (*(char*)(local_c + 0x11) == ' ')
		{
			local_110[1] = 0;
		}
		else
		{
			local_110[1] = *(uint8_t*)(local_c + 0x11);
		}
		local_110[3] = 0;
		local_110[2] = 0;
		local_12c = "Data\\Global\\Monsters\\";
		local_130 = local_110 + 4;
		do
		{
			cVar1 = *local_12c;
			*local_130 = cVar1;
			local_12c = local_12c + 1;
			local_130 = local_130 + 1;
		} while (cVar1 != '\0');
		uVar3 = 0xffffffff;
		pcVar6 = local_110;
		do
		{
			pcVar8 = pcVar6;
			if (uVar3 == 0)
				break;
			uVar3 = uVar3 - 1;
			pcVar8 = pcVar6 + 1;
			cVar1 = *pcVar6;
			pcVar6 = pcVar8;
		} while (cVar1 != '\0');
		uVar3 = ~uVar3;
		iVar4 = -1;
		pcVar6 = local_110 + 4;
		do
		{
			pcVar7 = pcVar6;
			if (iVar4 == 0)
				break;
			iVar4 = iVar4 + -1;
			pcVar7 = pcVar6 + 1;
			cVar1 = *pcVar6;
			pcVar6 = pcVar7;
		} while (cVar1 != '\0');
		pcVar6 = pcVar8 + -uVar3;
		pcVar8 = pcVar7 + -1;
		for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
		{
			*(uint32_t*)pcVar8 = *(uint32_t*)pcVar6;
			pcVar6 = pcVar6 + 4;
			pcVar8 = pcVar8 + 4;
		}
		for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1)
		{
			*pcVar8 = *pcVar6;
			pcVar6 = pcVar6 + 1;
			pcVar8 = pcVar8 + 1;
		}
		iVar4 = -1;
		pcVar6 = local_110 + 4;
		do
		{
			pcVar8 = pcVar6;
			if (iVar4 == 0)
				break;
			iVar4 = iVar4 + -1;
			pcVar8 = pcVar6 + 1;
			cVar1 = *pcVar6;
			pcVar6 = pcVar8;
		} while (cVar1 != '\0');
		*(uint32_t*)(pcVar8 + -1) = (*(uint32_t*)((uint8_t*)&"\\Cof\\palshift.dat" + 0));
		*(uint32_t*)(pcVar8 + 3) = (*(uint32_t*)((uint8_t*)&"\\Cof\\palshift.dat" + 4));
		*(uint32_t*)(pcVar8 + 7) = (*(uint32_t*)((uint8_t*)&"\\Cof\\palshift.dat" + 8));
		*(uint32_t*)(pcVar8 + 0xb) = (*(uint32_t*)((uint8_t*)&"\\Cof\\palshift.dat" + 12));
		*(uint16_t*)(pcVar8 + 0xf) = (*(uint16_t*)((uint8_t*)&"\\Cof\\palshift.dat" + 16));
		iVar4 = ARCHIVE_OpenFile(0, local_110 + 4, &local_118, 1);
		if (iVar4 != 0)
		{
			local_114 = (int*)D2_ALLOC(0x1008);
			piVar2 = local_114;
			for (iVar4 = 0x402; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*piVar2 = 0;
				piVar2 = piVar2 + 1;
			}
			ARCHIVE_ReadFileToBuffer(nullptr, local_118, (D2CellFileStrc*)(local_114 + 1), 0x800);
			ARCHIVE_CloseFile(0, local_118);
			sub_6FAAE300(a1, (int)local_114);
			*local_114 = a1;
			local_114[0x401] = (int)gpint32_t_6FBA7C14;
			gpint32_t_6FBA7C14 = local_114;
			local_8 = 0;
			while (iVar4 = sub_6FAAE5A0(), local_8 < iVar4)
			{
				if (*local_114 == local_8)
				{
					*(int**)(dword_6FBA7C10 + 4 + local_8 * 8) = local_114;
				}
				local_8 = local_8 + 1;
			}
		}
	}
}

//D2Client.0x6FAAE2E0
int* __fastcall sub_6FAAE2E0(int a1)
{
	int* piVar1;

	piVar1 = gpint32_t_6FBA7C14;
	if (gpint32_t_6FBA7C14 != nullptr)
	{
		do
		{
			if (*piVar1 == a1)
			{
				return piVar1;
			}
			piVar1 = (int*)piVar1[0x401];
		} while (piVar1 != nullptr);
	}
	return nullptr;
}

//D2Client.0x6FAAE300
void __fastcall sub_6FAAE300(int a1, int a2)
{
	void* pvVar1;
	int iVar2;
	int iVar3;
	char* pcVar4;
	char* pcVar5;
	uint32_t* puVar6;
	uint32_t local_4;

	if ((((-1 < a1) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), a1 < *(int*)(iVar3 + 0xa80))) && (iVar2 = (int)*(short*)(*(int*)(iVar3 + 0xa78) + 0x18 + a1 * 0x1a8), -1 < iVar2)) &&
	    (((iVar2 < *(int*)(iVar3 + 0xa98) &&
	          (iVar3 = *(int*)(iVar3 + 0xa90) + iVar2 * 0x134, iVar3 != 0)) &&
	        (*(char*)(iVar3 + 0x11c) == '\x02'))))
	{
		pcVar5 = (char*)(a2 + 0x804);
		puVar6 = (uint32_t*)(a2 + 4);
		pcVar4 = pcVar5;
		for (iVar3 = 0x200; pvVar1 = ptr_6FBA9A1C, iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*(uint32_t*)pcVar4 = *puVar6;
			puVar6 = puVar6 + 1;
			pcVar4 = pcVar4 + 4;
		}
		iVar3 = 8;
		do
		{
			iVar2 = 0x100;
			pcVar4 = pcVar5;
			do
			{
				local_4 = (uint32_t)(uint8_t)pcVar4[-0x800];
				if (*(char*)(local_4 + (int)pvVar1) != '\0')
				{
					*pcVar4 = *(char*)(local_4 + (int)pvVar1);
				}
				pcVar4 = pcVar4 + 1;
				iVar2 = iVar2 + -1;
			} while (iVar2 != 0);
			pcVar5 = pcVar5 + 0x100;
			iVar3 = iVar3 + -1;
		} while (iVar3 != 0);
	}
}

//D2Client.0x6FAAE3C0
uint8_t* __fastcall sub_6FAAE3C0(int* a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	if (((a1 == nullptr) || (*a1 != 1)) ||
	    (iVar1 = *(int*)(dword_6FBA7C10 + 4 + a1[1] * 8), iVar1 == 0))
	{
		return nullptr;
	}
	iVar3 = sub_6FB284A0((int)a1);
	switch (iVar3)
	{
	case 0:
	case 1:
		if ((uint32_t)a1[1] < 0x16b)
		{
			return nullptr;
		}
		if (0x16c < (uint32_t)a1[1])
		{
			return nullptr;
		}
		break;
	default:
		if (dword_6FBA9A18 != 0)
		{
			iVar3 = iVar3 + -8;
			if ((-1 < iVar3) && (iVar3 < 0x1e))
			{
				return byte_6FBA7C18 + iVar3 * 0x100;
			}
			FOG_DisplayAssert("eTransform >= 0 && eTransform < NUM_RANDTABLES",
			    __FILE__, __LINE__);
			exit(-1);
		}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		iVar4 = sub_6FAAC020();
		if ((((iVar4 != 0) && (iVar4 = a1[1], -1 < iVar4)) &&
		        ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar4 < *(int*)(iVar2 + 0xa80) &&
		                                                          (((iVar4 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar4 * 0x1a8), -1 < iVar4 &&
		                                                                                                                                        (iVar4 < *(int*)(iVar2 + 0xa98))) &&
		                                                              (iVar4 = *(int*)(iVar2 + 0xa90) + iVar4 * 0x134, iVar4 != 0)))))) &&
		    (*(char*)(iVar4 + 0x11c) == '\x02'))
		{
			return (uint8_t*)(iVar3 * 0x100 + 0x804 + iVar1);
		}
	}
	return (uint8_t*)(iVar3 * 0x100 + 4 + iVar1);
}

//D2Client.0x6FAAE510
// TODO: decompilation needs review (in_reg)
int __fastcall sub_6FAAE510(int a1)
{
	D2SeedStrc* pSeed;
	uint64_t DVar1;
	uint32_t in_EDX;

	if (a1 == 0)
	{
		return 9;
	}
	pSeed = (D2SeedStrc*)(a1 + 0x20);
	SEED_InitLowSeed(pSeed, (in_EDX & 0xffff) + *(int*)(a1 + 4));
	DVar1 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t) * (uint32_t*)(a1 + 0x24));
	*(uint64_t*)pSeed = DVar1;
	return (int)(((uint64_t)DVar1 & 0xffffffff) % 0x1e) + 9;
}

//D2Client.0x6FAAE560
void* __cdecl sub_6FAAE560()
{
	return ptr_6FBA9A1C;
}

//D2Client.0x6FAAE570
int __fastcall sub_6FAAE570(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + a1 * 0x1a8;
	}
	return 0;
}

//D2Client.0x6FAAE5A0
uint32_t __cdecl sub_6FAAE5A0()
{
	return *(uint32_t*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80);
}

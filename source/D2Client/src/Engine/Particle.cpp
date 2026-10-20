#include "Engine/Particle.h"

#include "Engine/Gfx.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB5FB10
void __cdecl sub_6FB5FB10(int a1)
{
	uint32_t* puVar1;
	int iVar2;
	uint32_t* puVar3;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 == nullptr)
	{
		puVar1 = (uint32_t*)D2_ALLOC(0x4c);
		D2_ASSERT(puVar1 != nullptr);
	}
	puVar3 = puVar1;
	for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	sub_6FB5BA50(a1, (uint32_t)(puVar1));
}

//D2Client.0x6FB5FB70
void __cdecl sub_6FB5FB70(int a1)
{
	void* pFree;

	pFree = (void*)sub_6FB5BA40(a1);
	if (pFree != nullptr)
	{
		D2_FREE(pFree);
		sub_6FB5BA50(a1, 0);
	}
}

//D2Client.0x6FB5FBA0
uint32_t __cdecl sub_6FB5FBA0(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0x34);
	}
	return 0;
}

//D2Client.0x6FB5FBC0
uint32_t __cdecl sub_6FB5FBC0(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0x38);
	}
	return 0;
}

//D2Client.0x6FB5FBE0
uint32_t __cdecl sub_6FB5FBE0(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0x3c);
	}
	return 0;
}

//D2Client.0x6FB5FC00
int __cdecl sub_6FB5FC00(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(int*)(iVar1 + 4) >> 0xb;
	}
	return 0;
}

//D2Client.0x6FB5FC20
int __cdecl sub_6FB5FC20(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(int*)(iVar1 + 8) >> 0xb;
	}
	return 0;
}

//D2Client.0x6FB5FC40
int __cdecl sub_6FB5FC40(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(int*)(iVar1 + 0xc) >> 0xb;
	}
	return 0;
}

//D2Client.0x6FB5FC60
uint32_t __cdecl sub_6FB5FC60(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0xc);
	}
	return 0;
}

//D2Client.0x6FB5FC80
void __cdecl sub_6FB5FC80(int a1, int a2, int a3, int a4)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		*(int*)(iVar1 + 4) = a2 << 0xb;
		*(int*)(iVar1 + 8) = a3 << 0xb;
		*(int*)(iVar1 + 0xc) = a4 << 0xb;
	}
}

//D2Client.0x6FB5FCB0
void __cdecl sub_6FB5FCB0(int a1, int a2, int a3, int a4, int a5)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		if (a5 != 0)
		{
			*(int*)(iVar1 + 0x10) = a2 << 0xb;
			*(int*)(iVar1 + 0x14) = a3 << 0xb;
			*(int*)(iVar1 + 0x18) = a4 << 0xb;
			return;
		}
		*(int*)(iVar1 + 0x10) = a2;
		*(int*)(iVar1 + 0x14) = a3;
		*(int*)(iVar1 + 0x18) = a4;
	}
}

//D2Client.0x6FB5FD00
void __cdecl sub_6FB5FD00(int a1, int a2, int a3, int a4, int a5)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		if (a5 != 0)
		{
			*(int*)(iVar1 + 0x1c) = a2 << 0xb;
			*(int*)(iVar1 + 0x20) = a3 << 0xb;
			*(int*)(iVar1 + 0x24) = a4 << 0xb;
			return;
		}
		*(int*)(iVar1 + 0x1c) = a2;
		*(int*)(iVar1 + 0x20) = a3;
		*(int*)(iVar1 + 0x24) = a4;
	}
}

//D2Client.0x6FB5FD50
void __cdecl sub_6FB5FD50(int a1, int a2, int a3, int a4, int a5)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		if (a5 != 0)
		{
			*(int*)(iVar1 + 0x28) = a2 << 0xb;
			*(int*)(iVar1 + 0x2c) = a3 << 0xb;
			*(int*)(iVar1 + 0x30) = a4 << 0xb;
			return;
		}
		*(int*)(iVar1 + 0x28) = a2;
		*(int*)(iVar1 + 0x2c) = a3;
		*(int*)(iVar1 + 0x30) = a4;
	}
}

//D2Client.0x6FB5FDA0
void __cdecl sub_6FB5FDA0(int a1, uint32_t a2, uint32_t a3)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		puVar1[0x11] = a3;
		*puVar1 = *puVar1 | 4;
		puVar1[0x10] = a2;
	}
}

//D2Client.0x6FB5FDD0
uint32_t __cdecl sub_6FB5FDD0(int a1)
{
	int iVar1;

	iVar1 = sub_6FB5BA40(a1);
	if (iVar1 != 0)
	{
		return *(uint32_t*)(iVar1 + 0x40);
	}
	return 0;
}

//D2Client.0x6FB5FDF0
void __fastcall sub_6FB5FDF0(int a1)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		*puVar1 = *puVar1 & 0xfffffffd;
	}
}

//D2Client.0x6FB5FE00
void __cdecl sub_6FB5FE00(int* a1)
{
	uint32_t* pX;
	uint32_t* pY;
	uint32_t uVar1;
	uint32_t* puVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	uint32_t local_8;
	uint32_t local_4;

	puVar2 = (uint32_t*)sub_6FB5BA40((int)a1);
	if (puVar2 == nullptr)
	{
		return;
	}
	uVar1 = *puVar2;
	if ((uVar1 & 1) != 0)
	{
		return;
	}
	pX = puVar2 + 1;
	*pX = puVar2[1] + puVar2[4];
	pY = puVar2 + 2;
	puVar2[4] = puVar2[7] + puVar2[4];
	*pY = *pY + puVar2[5];
	puVar2[5] = puVar2[8] + puVar2[5];
	puVar2[3] = puVar2[3] + puVar2[6];
	uVar8 = puVar2[9] + puVar2[6];
	puVar2[6] = uVar8;
	if ((uVar1 & 2) != 0)
	{
		if (puVar2[0x12] == 0)
		{
			*pX = 0;
			*puVar2 = uVar1 | 1;
			*pY = 0;
		}
		else
		{
			puVar2[0x12] = puVar2[0x12] - 1;
		}
	}
	uVar1 = *puVar2;
	if ((uVar1 & 4) == 0)
	{
		if ((uVar1 & 0x10) != 0)
		{
			pDVar3 = sub_6FB26AD0((int)a1);
			if (pDVar3 == nullptr)
				goto LAB_6fb60041;
			local_8 = 0;
			local_4 = 0;
			iVar6 = 8;
			if (a1 == nullptr)
			{
				iVar4 = 6;
			}
			else
			{
				iVar4 = *a1;
			}
			if (iVar4 == 1)
			{
			LAB_6fb5ff42:
				iVar6 = 0xe;
			}
			else if (iVar4 == 3)
			{
				if (pDVar3->dwUnitType != 1)
				{
					FOG_DisplayWarning("UnitGetType (hSourceUnit) == UNIT_MONSTER",
					    __FILE__, __LINE__);
				}
				if (pDVar3->dwAnimMode == 0)
				{
					return;
				}
				if (pDVar3->dwAnimMode == 0xc)
				{
					return;
				}
				goto LAB_6fb5ff42;
			}
			sub_6FB5C3C0(pDVar3, iVar6, (int*)(&local_8), (int*)(&local_4));
			puVar2[0xd] = local_8;
			puVar2[0xf] = local_4;
			if ((a1 != nullptr) && (*a1 == 3))
			{
				puVar2[0xf] = local_4 + 10;
			}
			iVar6 = sub_6FB5BA40((int)pDVar3);
			if (iVar6 == 0)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = *(int*)(iVar6 + 0x34);
			}
			puVar2[0xd] = puVar2[0xd] + iVar6;
			iVar6 = sub_6FB5BA40((int)pDVar3);
			if (iVar6 == 0)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = *(int*)(iVar6 + 0x3c);
			}
			puVar2[0xf] = puVar2[0xf] + iVar6;
			*pX = puVar2[0xd];
			*pY = puVar2[0xe];
			DUNGEON_ClientToGameSubtileCoords((int*)pX, (int*)pY);
			puVar2[3] = puVar2[0xf] * -0x800;
			goto LAB_6fb60041;
		}
		if ((((((uVar1 & 0x20) != 0) || (uVar8 = puVar2[10], (int)uVar8 < (int)*pX >> 0xb)) ||
		         (uVar5 = puVar2[0xb], (int)uVar5 < (int)*pY >> 0xb)) ||
		        (uVar7 = puVar2[0xc], (int)uVar7 < (int)puVar2[3] >> 0xb)) &&
		    ((((uVar1 & 0x20) == 0 || (uVar8 = puVar2[10], (int)*pX >> 0xb < (int)uVar8)) ||
		        ((uVar5 = puVar2[0xb], (int)puVar2[2] >> 0xb < (int)uVar5 ||
		                                   (uVar7 = puVar2[0xc], (int)puVar2[3] >> 0xb < (int)uVar7))))))
			goto LAB_6fb60041;
		*pX = uVar8 << 0xb;
		puVar2[2] = uVar5 << 0xb;
		puVar2[3] = uVar7 << 0xb;
	}
	else
	{
		if ((int)puVar2[0xc] < (int)puVar2[3] >> 0xb)
			goto LAB_6fb60041;
		iVar6 = (int)((uint64_t)((int64_t)(int)(puVar2[0x11] * uVar8) * -0x51eb851f) >> 0x20);
		puVar2[3] = puVar2[0xc];
		puVar2[6] = (iVar6 >> 5) - (iVar6 >> 0x1f);
		if (puVar2[0x10] != 0)
		{
			puVar2[0x10] = puVar2[0x10] - 1;
			goto LAB_6fb60041;
		}
	}
	*puVar2 = uVar1 | 1;
LAB_6fb60041:
	if ((*puVar2 & 0x10) == 0)
	{
		puVar2[0xd] = (int)*pX >> 0xb;
		puVar2[0xe] = (int)puVar2[2] >> 0xb;
		DUNGEON_GameToClientCoords((int*)(puVar2 + 0xd), (int*)(puVar2 + 0xe));
		puVar2[0xf] = -((int)puVar2[3] >> 0xb);
	}
}

//D2Client.0x6FB60080
void __fastcall sub_6FB60080(int a1, int a2, uint32_t a3)
{
	uint32_t uVar1;
	uint32_t* puVar2;

	puVar2 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar2 != nullptr)
	{
		*puVar2 = *puVar2 | 2;
		puVar2[0x12] = a3;
		if ((int)a3 < 1)
		{
			puVar2[0x12] = 1;
		}
		puVar2[1] = 0;
		puVar2[2] = 0;
		puVar2[3] = a2 * 0x800;
		if (puVar2[9] == 0)
		{
			puVar2[9] = 0xfffff000;
		}
		uVar1 = puVar2[0x12];
		puVar2[4] = 0;
		puVar2[5] = 0;
		puVar2[6] = (a2 * -0x800 - (int)(puVar2[9] * uVar1 * uVar1) / 2) / (int)uVar1;
	}
}

//D2Client.0x6FB600F0
void __fastcall sub_6FB600F0(int a1, int a2)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		if (a2 != 0)
		{
			*puVar1 = *puVar1 | 0x10;
			return;
		}
		*puVar1 = *puVar1 & 0xffffffef;
	}
}

//D2Client.0x6FB60110
void __cdecl sub_6FB60110(int a1)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		*puVar1 = *puVar1 | 1;
	}
}

//D2Client.0x6FB60130
void __cdecl sub_6FB60130(int a1)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		*puVar1 = *puVar1 & 0xfffffffe | 8;
	}
}

//D2Client.0x6FB60150
uint32_t __cdecl sub_6FB60150(int a1)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (((puVar1 != nullptr) && ((*puVar1 & 1) != 0)) && ((*puVar1 & 8) == 0))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FB60180
void __fastcall sub_6FB60180(int a1, int a2)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)sub_6FB5BA40(a1);
	if (puVar1 != nullptr)
	{
		if (a2 != 0)
		{
			*puVar1 = *puVar1 | 0x20;
			return;
		}
		*puVar1 = *puVar1 & 0xffffffdf;
	}
}

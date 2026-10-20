#include "Game/RosterPets.h"

#include "Game/Roster.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/PlayerList.h"

//D2Client.0x6FBAB9A0
int32_t dword_6FBAB9A0;

//D2Client.0x6FAB14C0
void __cdecl sub_6FAB14C0()
{
	void* pvVar1;
	void* pFree;

	pFree = (void*)dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree + 0x30);
			D2_FREE(pFree);
			pFree = pvVar1;
		} while (pvVar1 != nullptr);
	}
	dword_6FBAB9A0 = 0;
}

//D2Client.0x6FAB14F0
void __fastcall sub_6FAB14F0(int a1, int a2, int a3, int a4)
{
	int* piVar1;
	int* pFree;
	int iVar2;
	int* piVar3;
	int* piVar4;

	piVar4 = (int*)dword_6FBAB9A0;
	if (a3 == 7)
	{
		piVar1 = (int*)dword_6FBAB9A0;
		piVar3 = nullptr;
		if (dword_6FBAB9A0 == 0)
			goto LAB_6fab155b;
		do
		{
			pFree = piVar1;
			if ((*pFree == 7) && (pFree[2] != a1))
			{
				if (piVar3 == nullptr)
				{
					dword_6FBAB9A0 = pFree[0xc];
				}
				else
				{
					piVar3[0xc] = pFree[0xc];
				}
				D2_FREE(pFree);
				piVar4 = (int*)dword_6FBAB9A0;
				break;
			}
			piVar1 = (int*)pFree[0xc];
			piVar3 = pFree;
		} while ((int*)pFree[0xc] != nullptr);
	}
	for (; piVar4 != nullptr; piVar4 = (int*)piVar4[0xc])
	{
		if (piVar4[2] == a1)
		{
			piVar4[1] = a3;
			piVar4[3] = a2;
			*piVar4 = a4;
			piVar4[8] = 0;
			return;
		}
	}
LAB_6fab155b:
	piVar1 = (int*)D2_ALLOC(0x34);
	piVar4 = piVar1;
	for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*piVar4 = 0;
		piVar4 = piVar4 + 1;
	}
	piVar1[2] = a1;
	piVar1[3] = a2;
	piVar1[1] = a3;
	*piVar1 = a4;
	piVar1[7] = 100;
	piVar1[0xc] = dword_6FBAB9A0;
	dword_6FBAB9A0 = (int)piVar1;
}

//D2Client.0x6FAB15D0
void __fastcall sub_6FAB15D0(uint32_t a1, int a2, int a3, int a4, int* a5)
{
	int* piVar1;
	D2UnitStrc* pUnit;
	int* pFree;
	int iVar2;
	int* piVar3;
	int* piVar4;
	uint16_t auStack_10[2];
	int iStack_c;

	iVar2 = dword_6FBAB9A0;
	if ((a3 == 7) && (piVar1 = (int*)dword_6FBAB9A0, piVar3 = nullptr, dword_6FBAB9A0 != 0))
	{
		do
		{
			piVar4 = piVar1;
			if ((*piVar4 == 7) && (piVar4[2] != a1))
			{
				if (piVar3 == nullptr)
				{
					dword_6FBAB9A0 = piVar4[0xc];
				}
				else
				{
					piVar3[0xc] = piVar4[0xc];
				}
				D2_FREE(piVar4);
				iVar2 = dword_6FBAB9A0;
				break;
			}
			piVar1 = (int*)piVar4[0xc];
			piVar3 = piVar4;
		} while ((int*)piVar4[0xc] != nullptr);
	}
	for (; (iVar2 != 0 && (*(uint32_t*)(iVar2 + 8) != a1)); iVar2 = *(int*)(iVar2 + 0x30))
	{
	}
	piVar1 = (int*)dword_6FBAB9A0;
	if (a3 == 7)
	{
		piVar3 = (int*)dword_6FBAB9A0;
		piVar4 = nullptr;
		if (dword_6FBAB9A0 == 0)
		{
		LAB_6fab169a:
			piVar1 = (int*)D2_ALLOC(0x34);
			piVar3 = piVar1;
			for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*piVar3 = 0;
				piVar3 = piVar3 + 1;
			}
			piVar1[2] = a1;
			piVar1[3] = a2;
			piVar1[1] = a3;
			*piVar1 = a4;
			piVar1[7] = 100;
			piVar1[0xc] = dword_6FBAB9A0;
			dword_6FBAB9A0 = (int)piVar1;
		joined_r0x6fab16e2:
			while (true)
			{
				D2_ASSERT(piVar1 != nullptr);
				if (piVar1[2] == a1)
					break;
				piVar1 = (int*)piVar1[0xc];
			}
			piVar1[2] = a1;
			piVar1[3] = a2;
			piVar1[1] = a3;
			piVar1[9] = *a5;
			piVar1[10] = a5[1];
			piVar1[0xb] = a5[2];
			if (a3 == 7)
			{
				iStack_c = *a5;
				auStack_10[0] = (uint16_t)a5[1];
				pUnit = sub_6FB269F0(a1, 1);
				if (pUnit != nullptr)
				{
					sub_6FB446B0(pUnit, auStack_10);
					sub_6FB294B0((int*)pUnit);
					sub_6FB40B50(pUnit);
					UNITS_ChangeAnimMode(pUnit, 1);
				}
			}
			return;
		}
		do
		{
			pFree = piVar3;
			if ((*pFree == 7) && (pFree[2] != a1))
			{
				if (piVar4 == nullptr)
				{
					dword_6FBAB9A0 = pFree[0xc];
				}
				else
				{
					piVar4[0xc] = pFree[0xc];
				}
				D2_FREE(pFree);
				piVar1 = (int*)dword_6FBAB9A0;
				break;
			}
			piVar3 = (int*)pFree[0xc];
			piVar4 = pFree;
		} while ((int*)pFree[0xc] != nullptr);
	}
	do
	{
		if (piVar1 == nullptr)
			goto LAB_6fab169a;
		if (piVar1[2] == a1)
		{
			piVar1[3] = a2;
			piVar1[1] = a3;
			*piVar1 = a4;
			piVar1[8] = 0;
			piVar1 = (int*)dword_6FBAB9A0;
			goto joined_r0x6fab16e2;
		}
		piVar1 = (int*)piVar1[0xc];
	} while (true);
}

//D2Client.0x6FAB17A0
void __fastcall sub_6FAB17A0(int a1)
{
	void* pvVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	void* pFree;
	void* pvVar4;

	pvVar1 = (void*)dword_6FBAB9A0;
	pvVar4 = nullptr;
	if (dword_6FBAB9A0 != 0)
	{
		while (pFree = pvVar1, *(int*)((int)pFree + 8) != a1)
		{
			pvVar1 = *(void**)((int)pFree + 0x30);
			pvVar4 = pFree;
			if (*(void**)((int)pFree + 0x30) == nullptr)
			{
				return;
			}
		}
		if (*(int*)((int)pFree + 4) == 7)
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 == nullptr)
			{
				uVar3 = 0xffffffff;
			}
			else
			{
				uVar3 = pDVar2->dwUnitId;
			}
			if (*(uint32_t*)((int)pFree + 0xc) == uVar3)
			{
				*(uint32_t*)((int)pFree + 0x20) = 1;
				return;
			}
		}
		if (pvVar4 == nullptr)
		{
			dword_6FBAB9A0 = *(int*)((int)pFree + 0x30);
		}
		else
		{
			*(uint32_t*)((int)pvVar4 + 0x30) = *(uint32_t*)((int)pFree + 0x30);
		}
		D2_FREE(pFree);
	}
}

//D2Client.0x6FAB1810
uint32_t __fastcall sub_6FAB1810(int a1)
{
	short sVar1;
	short sVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;

	iVar5 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar5 + 8) == a1)
			{
				iVar3 = *(int*)(iVar5 + 4);
				if (((iVar3 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0) <= iVar3)) ||
				    (iVar3 = iVar3 * 0xe0 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbe8), iVar3 == 0))
				{
					return 3;
				}
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar3 + 4)) == 0)
				{
					return 3;
				}
				pDVar4 = CUNIT_GetPlayer();
				if (pDVar4 == nullptr)
				{
					uVar6 = 0xffffffff;
				}
				else
				{
					uVar6 = pDVar4->dwUnitId;
				}
				if (*(uint32_t*)(iVar5 + 0xc) != uVar6)
				{
					iVar3 = sub_6FAAFD60(uVar6);
					sVar1 = sub_6FAAFDA0(iVar3);
					if (sVar1 == -1)
					{
						return 0;
					}
					iVar5 = sub_6FAAFD60(*(int*)(iVar5 + 0xc));
					sVar2 = sub_6FAAFDA0(iVar5);
					if (sVar1 != sVar2)
					{
						return 0;
					}
					return 2;
				}
				return 1;
			}
			iVar5 = *(int*)(iVar5 + 0x30);
		} while (iVar5 != 0);
	}
	return 0;
}

//D2Client.0x6FAB18D0
int __fastcall sub_6FAB18D0(int a1)
{
	int iVar1;

	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 8) == a1)
			{
				return iVar1 + 0x24;
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	return 0;
}

//D2Client.0x6FAB18F0
int __fastcall sub_6FAB18F0(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if (a1 == 0)
	{
		iVar2 = -1;
	}
	else
	{
		iVar2 = *(int*)(a1 + 0xc);
	}
	iVar1 = 0;
	iVar3 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if ((*(int*)(iVar3 + 4) == a2) && (*(int*)(iVar3 + 0xc) == iVar2))
			{
				iVar1 = iVar1 + 1;
			}
			iVar3 = *(int*)(iVar3 + 0x30);
		} while (iVar3 != 0);
	}
	return iVar1;
}

//D2Client.0x6FAB1920
uint32_t __fastcall sub_6FAB1920(int a1, int a2, int a3)
{
	int* piVar1;
	int iVar2;

	if ((a1 != 0) && (iVar2 = dword_6FBAB9A0, dword_6FBAB9A0 != 0))
	{
		do
		{
			if (((*(int*)(iVar2 + 4) == a2) && (*(int*)(iVar2 + 0xc) == *(int*)(a1 + 0xc))) && ((a3 != 0 || (*(int*)(iVar2 + 0x20) == 0))))
			{
				return *(uint32_t*)(iVar2 + 8);
			}
			piVar1 = (int*)(iVar2 + 0x30);
			iVar2 = *piVar1;
		} while (*piVar1 != 0);
	}
	return 0xffffffff;
}

//D2Client.0x6FAB1970
uint32_t __fastcall sub_6FAB1970(int a1)
{
	int iVar1;
	int iVar2;

	if (a1 == 0)
	{
		iVar2 = -1;
	}
	else
	{
		iVar2 = *(int*)(a1 + 0xc);
	}
	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 0xc) == iVar2)
			{
				return 1;
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	return 0;
}

//D2Client.0x6FAB19A0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAB19A0()
{
	bool bVar1;
	D2UnitStrc* pUnit1;
	D2UnitStrc* pUnit2;
	int iVar2;
	uint32_t extraout_var;
	int iVar3;
	uint32_t uVar4;

	iVar3 = dword_6FBAB9A0;
	pUnit1 = CUNIT_GetPlayer();
	if (iVar3 != 0)
	{
		do
		{
			if ((*(int*)(iVar3 + 4) == 4) &&
			    (pUnit2 = sub_6FB269F0(*(uint32_t*)(iVar3 + 8), 1), pUnit2 != nullptr))
			{
				for (iVar2 = dword_6FBAB9A0; iVar2 != 0; iVar2 = *(int*)(iVar2 + 0x30))
				{
					if (*(uint32_t*)(iVar2 + 8) == pUnit2->dwUnitId)
						goto LAB_6fab19e8;
				}
				iVar2 = 0;
			LAB_6fab19e8:
				if (pUnit1 == nullptr)
				{
				LAB_6fab1a3c:
					uVar4 = 0;
				}
				else
				{
					if (iVar2 == 0)
					{
						if (((pUnit1->dwUnitType != 1) || (pUnit2->dwUnitType != 1)) ||
						    (iVar2 = STATLIST_AreUnitsAligned(pUnit1, pUnit2), iVar2 == 0))
							goto LAB_6fab1a3c;
					}
					else if ((*(uint32_t*)(iVar2 + 0xc) != pUnit1->dwUnitId) &&
					         (bVar1 = sub_6FAB07D0(pUnit1->dwUnitId, *(uint32_t*)(iVar2 + 0xc)),
					             D2C_ZEXT(bVar1) != 0))
						goto LAB_6fab1a3c;
					uVar4 = 1;
				}
				sub_6FB28410((int)pUnit2, uVar4);
				sub_6FB28470((int)pUnit2, uVar4);
			}
			iVar3 = *(int*)(iVar3 + 0x30);
		} while (iVar3 != 0);
	}
}

//D2Client.0x6FAB1A40
void __fastcall sub_6FAB1A40(uint32_t a1, int a2, uint32_t a3)
{
	D2UnitStrc* pUnit;
	int iVar1;
	uint16_t nLayer;

	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		while (*(uint32_t*)(iVar1 + 8) != a1)
		{
			iVar1 = *(int*)(iVar1 + 0x30);
			if (iVar1 == 0)
			{
				return;
			}
		}
		*(int*)(iVar1 + 0x1c) = a2;
		*(uint32_t*)(iVar1 + 0x10) = a3 & 0xffff;
		if (*(int*)(iVar1 + 4) == 7)
		{
			pUnit = sub_6FB269F0(a1, 1);
			if (pUnit != nullptr)
			{
				nLayer = 0;
				iVar1 = STATLIST_GetMaxLifeFromUnit(pUnit);
				STATLIST_SetUnitStat(pUnit, 6, (iVar1 * a2) / 100, nLayer);
			}
		}
	}
}

//D2Client.0x6FAB1AC0
uint32_t __fastcall sub_6FAB1AC0(int a1)
{
	int iVar1;

	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 8) == a1)
			{
				return *(uint32_t*)(iVar1 + 0x1c);
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	return 0;
}

//D2Client.0x6FAB1AE0
uint32_t __fastcall sub_6FAB1AE0(int a1)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (puVar1[2] == a1)
			{
				return *puVar1;
			}
			puVar1 = (uint32_t*)puVar1[0xc];
		} while (puVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FAB1B00
uint32_t __fastcall sub_6FAB1B00(int a1)
{
	int iVar1;

	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 8) == a1)
			{
				return *(uint32_t*)(iVar1 + 0xc);
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	return 0xffffffff;
}

//D2Client.0x6FAB1B20
uint32_t __fastcall sub_6FAB1B20(int a1)
{
	int iVar1;

	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 8) == a1)
			{
				return *(uint32_t*)(iVar1 + 4);
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	return 0;
}

//D2Client.0x6FAB1B40
uint32_t __fastcall sub_6FAB1B40(int a1)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;

	if (a1 == 0)
	{
		iVar4 = -1;
	}
	else
	{
		iVar4 = *(int*)(a1 + 0xc);
	}
	iVar1 = dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if (*(int*)(iVar1 + 8) == iVar4)
			{
				iVar4 = *(int*)(iVar1 + 0xc);
				goto LAB_6fab1b65;
			}
			iVar1 = *(int*)(iVar1 + 0x30);
		} while (iVar1 != 0);
	}
	iVar4 = -1;
LAB_6fab1b65:
	pDVar2 = CUNIT_GetPlayer();
	if ((pDVar2 != nullptr) && (pDVar2->dwUnitId != 0xffffffff))
	{
		if (iVar4 != -1)
		{
			uVar3 = sub_6FB4B900(iVar4, pDVar2->dwUnitId, 8);
			return uVar3;
		}
		return 1;
	}
	FOG_DisplayAssert("dwControlId != INVALID_PLAYER_ID",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAB1BB0
void __fastcall sub_6FAB1BB0(int a1)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int* piVar5;
	int iVar6;
	uint32_t uVar7;

	piVar5 = (int*)dword_6FBAB9A0;
	if (dword_6FBAB9A0 != 0)
	{
		do
		{
			if ((((piVar5[3] == a1) && (0x16a < *piVar5)) && (*piVar5 < 0x16d)) &&
			    (pDVar1 = sub_6FB269F0(piVar5[2], 1), pDVar1 != nullptr))
			{
				iVar2 = sub_6FB284A0((int)pDVar1);
				for (iVar6 = dword_6FBAB9A0; iVar6 != 0; iVar6 = *(int*)(iVar6 + 0x30))
				{
					if (*(uint32_t*)(iVar6 + 8) == pDVar1->dwUnitId)
					{
						iVar6 = *(int*)(iVar6 + 0xc);
						goto LAB_6fab1c26;
					}
				}
				iVar6 = -1;
			LAB_6fab1c26:
				pDVar3 = CUNIT_GetPlayer();
				D2_ASSERT(!((pDVar3 == nullptr) || (pDVar3->dwUnitId == 0xffffffff)));
				if ((iVar6 == -1) || (uVar4 = sub_6FB4B900(iVar6, pDVar3->dwUnitId, 8), uVar4 != 0))
				{
					uVar7 = 0;
				}
				else
				{
					uVar7 = 1;
				}
				iVar6 = sub_6FB28440((int)pDVar1);
				if (iVar2 == iVar6)
				{
					sub_6FB28470((int)pDVar1, uVar7);
				}
				sub_6FB28410((int)pDVar1, uVar7);
			}
			piVar5 = (int*)piVar5[0xc];
		} while (piVar5 != nullptr);
	}
}

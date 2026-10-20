#include "Sound/SoundInst.h"

#include "Game/Env.h"
#include "Game/Game.h"
#include "Sound/SoundChan.h"
#include "Sound/SoundHdr.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FBBD4D0
uint32_t dword_6FBBD4D0;
//D2Client.0x6FBC1A57
uint8_t tbl_6FBC1A57[1];
//D2Client.0x6FBC1A58
int32_t* gpint32_t_6FBC1A58;
//D2Client.0x6FBC1A5C
int32_t dword_6FBC1A5C;
//D2Client.0x6FBC1A60
int32_t dword_6FBC1A60;
//D2Client.0x6FBC1A64
uint32_t dword_6FBC1A64;
//D2Client.0x6FBC1A68
uint32_t dword_6FBC1A68;
//D2Client.0x6FBC1A6C
uint32_t dword_6FBC1A6C;
//D2Client.0x6FBC1A70
uint8_t byte_6FBC1A70;
//D2Client.0x6FBC1A74
int32_t dword_6FBC1A74;
//D2Client.0x6FBC1A78
int32_t dword_6FBC1A78;
//D2Client.0x6FBC1A7C
uint32_t dword_6FBC1A7C;
//D2Client.0x6FBC1A80
int32_t dword_6FBC1A80;
//D2Client.0x6FBC1A84
int32_t dword_6FBC1A84;
//D2Client.0x6FBC1A88
uint32_t dword_6FBC1A88;
//D2Client.0x6FBC1A8C
int32_t dword_6FBC1A8C;
//D2Client.0x6FBC1A90
int32_t dword_6FBC1A90;
//D2Client.0x6FBC1A94
int32_t dword_6FBC1A94;
//D2Client.0x6FBC1A98
int32_t dword_6FBC1A98;
//D2Client.0x6FBC1A9C
int32_t dword_6FBC1A9C;
//D2Client.0x6FBC1AA0
int32_t dword_6FBC1AA0;

//D2Client.0x6FB555C0
void __fastcall sub_6FB555C0(int a1, int a2, int a3)
{
	int iVar1;
	int* piVar2;
	bool bVar3;
	int iVar4;

	D2_ASSERT(!((a1 == 0) || (a2 == 0)));
	sub_6FB4F960(a2);
	piVar2 = gpint32_t_6FBC1A58;
	while (true)
	{
		if (piVar2 == nullptr)
		{
			return;
		}
		iVar1 = *piVar2;
		if (*(int*)(iVar1 + 8) == a1)
			break;
		piVar2 = (int*)piVar2[1];
	}
	iVar4 = sub_6FB53C00(*(int*)(iVar1 + 4));
	D2SOUND_10059(iVar1 + 0x28, a2);
	if ((*(char*)(iVar4 + 0x3e) == '\0') ||
	    ((*(int*)(iVar1 + 0x45) != 0 && (*(int*)(iVar1 + 0x4d) == 0))))
	{
		bVar3 = true;
	}
	else
	{
		bVar3 = false;
	}
	if (*(int*)(iVar1 + 0x28) != 0)
	{
		return;
	}
	if ((a3 == 0) && (bVar3))
	{
		return;
	}
	iVar4 = sub_6FB53C00(*(int*)(iVar1 + 4));
	*(uint32_t*)(iVar1 + 0x3d) = 1;
	if (*(uint8_t*)(iVar4 + 0x40) == 0)
	{
		return;
	}
	if (*(int*)(iVar1 + 0x30) != 1)
	{
		return;
	}
	sub_6FB55BF0(*(int*)(iVar1 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar4 + 0x40));
}

//D2Client.0x6FB556A0
void __fastcall sub_6FB556A0(int a1)
{
	int iVar1;
	int* piVar2;
	int iVar3;

	if ((a1 != 0) && (piVar2 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		while (iVar1 = *piVar2, *(int*)(iVar1 + 8) != a1)
		{
			piVar2 = (int*)piVar2[1];
			if (piVar2 == nullptr)
			{
				return;
			}
		}
		iVar3 = sub_6FB53C00(*(int*)(iVar1 + 4));
		*(uint32_t*)(iVar1 + 0x3d) = 1;
		if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar1 + 0x30) == 1))
		{
			sub_6FB55BF0(*(int*)(iVar1 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
		}
	}
}

//D2Client.0x6FB556F0
uint32_t __fastcall sub_6FB556F0(int a1)
{
	int* piVar1;

	piVar1 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			if (*(int*)(*piVar1 + 4) == a1)
			{
				return *(uint32_t*)(*piVar1 + 8);
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB55710
void __fastcall sub_6FB55710(int a1, int a2, float a3, float a4)
{
	int iVar1;
	float fVar2;
	int* piVar3;
	double fVar4;

	if ((a1 != 0) && (piVar3 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		while (iVar1 = *piVar3, *(int*)(iVar1 + 8) != a1)
		{
			piVar3 = (int*)piVar3[1];
			if (piVar3 == nullptr)
			{
				return;
			}
		}
		fVar2 = (float)a2;
		a3 = (float)(int)a3;
		*(float*)(iVar1 + 0xc) = fVar2;
		*(float*)(iVar1 + 0x10) = a3;
		*(float*)(iVar1 + 0x14) = (float)(int)a4 + 640.0;
		if (fVar2 <= -2000.0)
		{
			a4 = -2000.0;
		}
		else
		{
			a4 = fVar2;
			if (2000.0 <= fVar2)
			{
				a4 = 2000.0;
			}
		}
		if (a3 <= -2000.0)
		{
			a3 = -2000.0;
		}
		else if (2000.0 <= a3)
		{
			a3 = 2000.0;
		}
		fVar4 = sub_6FB572B0(a4, a3);
		*(float*)(iVar1 + 0x18) = (float)fVar4;
	}
}

//D2Client.0x6FB55820
// TODO: decompilation needs review (extraout)
int __fastcall sub_6FB55820(int a1, D2UnitStrc* pUnit, float a3, float a4, int a5)
{
	uint8_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t extraout_var;
	D2UnitStrc* pDVar6;
	int* a2;
	int* piVar7;
	bool bVar8;
	double fVar9;
	float fStack_c;
	float fStack_8;
	int iStack_4;

	if (dword_6FBC1A5C == 0)
	{
		return 0;
	}
	if (a1 < 1)
	{
		return 0;
	}
	iVar2 = sub_6FB53C00(a1);
	iVar3 = sub_6FB54C50();
	if (*(char*)(iVar2 + 0x3c) == '\0')
	{
		return 0;
	}
	if (*(short*)(iVar2 + 0x45) != 0)
	{
		iVar4 = sub_6FB53C00(a1);
		for (piVar7 = gpint32_t_6FBC1A58; piVar7 != nullptr; piVar7 = (int*)piVar7[1])
		{
			a2 = (int*)*piVar7;
			iVar5 = sub_6FB53C30(a2[1]);
			if (((iVar5 == *(int*)(iVar4 + 0x60)) && (*(int*)((int)a2 + 0x3d) == 0)) &&
			    ((*(short*)(iVar4 + 0x45) < 0 ||
			        (iVar5 = sub_6FB54C50(), (uint32_t)(iVar5 - a2[0xd]) <= (uint32_t)(int)*(short*)(iVar4 + 0x45)))))
				goto LAB_6fb55aae;
		}
	}
	a2 = (int*)(&dword_6FBBD4D0);
	while (*a2 != 0)
	{
		a2 = (int*)((int)a2 + 0x59);
		if ((int)&tbl_6FBC1A57 < (int)a2)
		{
			return 0;
		}
	}
	piVar7 = a2;
	for (iVar4 = 0x16; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*piVar7 = 0;
		piVar7 = piVar7 + 1;
	}
	*(uint8_t*)piVar7 = 0;
	*a2 = 1;
	D2SOUND_10058((int)&gpint32_t_6FBC1A58, (int)a2);
	dword_6FBC1A60 = dword_6FBC1A60 + 1;
	a2[2] = dword_6FBC1A60;
	a2[0xe] = (int)a4;
	a2[1] = a1;
	a2[0xd] = iVar3 + (int)a3;
	a2[9] = a5;
	a2[7] = 0xff;
	*(uint8_t*)(a2 + 0xf) = *(uint8_t*)(iVar2 + 0x4e);
	if (pUnit == nullptr)
	{
		fStack_c = 0.0;
		fStack_8 = 0.0;
		iStack_4 = 0x43a00000;
		a2[3] = 0;
		a2[4] = 0;
		a2[5] = 0x43a00000;
		fVar9 = sub_6FB572B0(0.0, 0.0);
		a2[6] = (int)(float)fVar9;
		goto LAB_6fb55aae;
	}
	sub_6FB55AE0(pUnit, a1, &fStack_c);
	a2[3] = (int)fStack_c;
	a2[4] = (int)fStack_8;
	a2[5] = iStack_4;
	if (fStack_c <= -2000.0)
	{
		a3 = -2000.0;
	}
	else if (2000.0 <= fStack_c)
	{
		a3 = 2000.0;
	}
	else
	{
		a3 = fStack_c;
	}
	if (fStack_8 <= -2000.0)
	{
		a4 = -2000.0;
	}
	else if (2000.0 <= fStack_8)
	{
		a4 = 2000.0;
	}
	else
	{
		a4 = fStack_8;
	}
	fVar9 = sub_6FB572B0(a3, a4);
	a2[6] = (int)(float)fVar9;
	iVar2 = sub_6FB53C00(a1);
	if (iVar2 == 0)
	{
	LAB_6fb55a4b:
		pDVar6 = CUNIT_GetPlayer();
		iVar2 = UNITS_TestCollisionWithUnit(pDVar6, pUnit, 2);
		bVar8 = iVar2 == 0;
	LAB_6fb55a5b:
		if (!bVar8)
		{
			a2[8] = 0x3f000000;
			goto LAB_6fb55aae;
		}
	}
	else if (*(int*)(iVar2 + 0x47) != 4)
	{
		if (*(int*)(iVar2 + 0x60) != 0xca)
			goto LAB_6fb55a4b;
		uVar1 = sub_6FB53CF0();
		iVar2 = sub_6FB53D30(D2C_ZEXT(uVar1));
		if (iVar2 == 0)
			goto LAB_6fb55a68;
		bVar8 = *(char*)(iVar2 + 0x18) == '\0';
		goto LAB_6fb55a5b;
	}
LAB_6fb55a68:
	a2[8] = 0;
LAB_6fb55aae:
	pDVar6 = CUNIT_GetPlayer();
	if (pUnit == pDVar6)
	{
		*(char*)(a2 + 0xf) = (char)a2[0xf] + 'P';
	}
	if (pUnit != nullptr)
	{
		D2SOUND_10058((int)(a2 + 10), (int)pUnit);
		sub_6FB4F930((int)pUnit);
	}
	return a2[2];
}

//D2Client.0x6FB55AE0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB55AE0(D2UnitStrc* pUnit2, int a2, float* a3)
{
	D2UnitStrc* pUnit;
	double fVar1;
	double extraout_ST0;
	double extraout_ST1;
	int64_t lVar2;
	int64_t lVar3;
	D2CoordStrc DStack_10;
	D2CoordStrc local_8;

	pUnit = CUNIT_GetPlayer();
	UNITS_GetClientCoords(pUnit, &local_8);
	UNITS_GetClientCoords(pUnit2, &DStack_10);
	if (a2 == 0xa27)
	{
		fVar1 = (double)local_8.nX * (double)-2.0;
		lVar2 = (int64_t)((((fVar1 - (double)DStack_10.nX * (double)0.5) + (double)local_8.nY) -
		                      (double)DStack_10.nY) *
		                  (double)-0.4);
		lVar3 = (int64_t)((extraout_ST1 - extraout_ST0 * (double)-2.0) + fVar1);
		DStack_10.nY = (int)lVar3;
		DStack_10.nX = (int)lVar2;
	}
	a3[2] = 640.0;
	*a3 = (float)(DStack_10.nX - local_8.nX);
	a3[1] = (float)(DStack_10.nY - local_8.nY) + (float)(DStack_10.nY - local_8.nY);
}

//D2Client.0x6FB55B90
uint32_t __fastcall sub_6FB55B90(int a1)
{
	int* piVar1;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar1 + 8) == a1)
			{
				return *(uint32_t*)(*piVar1 + 0x1c);
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB55BC0
int32_t __fastcall sub_6FB55BC0(int a1, uint32_t a2)
{
	int* piVar1;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		while (*(int*)(*piVar1 + 8) != a1)
		{
			piVar1 = (int*)piVar1[1];
			if (piVar1 == nullptr)
			{
				return 0;
			}
		}
		*(uint32_t*)(*piVar1 + 0x1c) = a2;
	}
	return 0;
}

//D2Client.0x6FB55BF0
void __fastcall sub_6FB55BF0(int a1, int a2, int a3, uint32_t a4)
{
	uint8_t bVar1;
	int iVar2;
	int* piVar3;
	int iVar4;
	int* piVar5;

	if (a1 == 0)
	{
		return;
	}
	piVar5 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 == nullptr)
	{
		return;
	}
	while (iVar2 = *piVar5, piVar3 = gpint32_t_6FBC1A58, *(int*)(iVar2 + 8) != a1)
	{
		piVar5 = (int*)piVar5[1];
		if (piVar5 == nullptr)
		{
			return;
		}
	}
	do
	{
		if (*(int*)(*piVar3 + 8) == a1)
		{
			iVar4 = *(int*)(*piVar3 + 0x28);
			if ((iVar4 != 0) && (*(int*)(iVar4 + 4) != 0))
			{
				return;
			}
			break;
		}
		piVar5 = piVar3 + 1;
		piVar3 = (int*)*piVar5;
	} while ((int*)*piVar5 != nullptr);
	iVar4 = sub_6FB53C00(*(int*)(iVar2 + 4));
	if (a2 == 0xff)
	{
		bVar1 = *(uint8_t*)(iVar4 + 0x3f);
	LAB_6fb55c81:
		if (a4 < bVar1)
		{
			a4 = (uint32_t)bVar1;
		}
	}
	else if (a2 == 0)
	{
		bVar1 = *(uint8_t*)(iVar4 + 0x40);
		goto LAB_6fb55c81;
	}
	if (*(int*)(iVar2 + 0x45) == 0)
	{
	LAB_6fb55cc4:
		if (a2 != 0)
			goto LAB_6fb55ccf;
	}
	else
	{
		if ((a2 == *(int*)(iVar2 + 0x4d)) &&
		    (iVar4 = sub_6FB54C50(), *(uint32_t*)(iVar2 + 0x55) <= iVar4 + a3 + a4))
		{
			return;
		}
		if (*(int*)(iVar2 + 0x4d) != 0)
			goto LAB_6fb55cc4;
		if (a2 != 0)
		{
			return;
		}
	}
	*(uint32_t*)(iVar2 + 0x3d) = 1;
LAB_6fb55ccf:
	if (a4 == 0)
	{
		D2_ASSERT(!a3);
		piVar5 = gpint32_t_6FBC1A58;
		if (gpint32_t_6FBC1A58 != nullptr)
		{
			do
			{
				if (*(int*)(*piVar5 + 8) == a1)
				{
					*(int*)(*piVar5 + 0x1c) = a2;
					return;
				}
				piVar5 = (int*)piVar5[1];
			} while (piVar5 != nullptr);
			return;
		}
	}
	else
	{
		iVar4 = sub_6FB54C50();
		*(uint32_t*)(iVar2 + 0x49) = *(uint32_t*)(iVar2 + 0x1c);
		*(int*)(iVar2 + 0x51) = iVar4 + a3;
		*(int*)(iVar2 + 0x4d) = a2;
		*(uint32_t*)(iVar2 + 0x55) = iVar4 + a3 + a4;
		*(uint32_t*)(iVar2 + 0x45) = 1;
	}
}

//D2Client.0x6FB55D60
uint32_t __fastcall sub_6FB55D60(int a1)
{
	int iVar1;
	int* piVar2;

	if ((a1 != 0) && (piVar2 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar2 + 8) == a1)
			{
				iVar1 = *(int*)(*piVar2 + 0x28);
				if (iVar1 == 0)
				{
					return 0;
				}
				if (*(int*)(iVar1 + 4) == 0)
				{
					return 0;
				}
				return 1;
			}
			piVar2 = (int*)piVar2[1];
		} while (piVar2 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB55DA0
void __fastcall sub_6FB55DA0(int a1)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	piVar4 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar4;
			if (*(int*)(iVar2 + 4) == a1)
			{
				iVar3 = sub_6FB53C00(*(int*)(iVar2 + 4));
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
				}
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB55DF0
void __cdecl sub_6FB55DF0()
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int* piVar5;

	piVar5 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar5;
			iVar3 = sub_6FB53D60();
			iVar4 = *(int*)(iVar2 + 4);
			if ((iVar3 <= iVar4) && (iVar3 = sub_6FB53D70(), iVar4 <= iVar3))
			{
				iVar4 = sub_6FB53C00(iVar4);
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar4 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar4 + 0x40));
				}
			}
			piVar1 = piVar5 + 1;
			piVar5 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB55E60
void __fastcall sub_6FB55E60(int a1, int a2)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	piVar4 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar4;
			iVar3 = sub_6FB53C30(*(int*)(iVar2 + 4));
			if ((((iVar3 != a1) && (iVar3 = sub_6FB53C30(*(int*)(iVar2 + 4)), iVar3 != a2)) &&
			        (iVar3 = *(int*)(iVar2 + 4), 0x33 < iVar3)) &&
			    (iVar3 < 0x48))
			{
				iVar3 = sub_6FB53C00(iVar3);
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
				}
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB55EE0
void __fastcall sub_6FB55EE0(int a1, int a2)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	piVar4 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar4;
			iVar3 = sub_6FB53C30(*(int*)(iVar2 + 4));
			if ((((iVar3 != a1) && (iVar3 = sub_6FB53C30(*(int*)(iVar2 + 4)), iVar3 != a2)) &&
			        (iVar3 = *(int*)(iVar2 + 4), 0x47 < iVar3)) &&
			    (iVar3 < 0xca))
			{
				iVar3 = sub_6FB53C00(iVar3);
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
				}
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB55F60
void __cdecl sub_6FB55F60()
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	piVar4 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar4;
			iVar3 = *(int*)(iVar2 + 4);
			if ((0xb75 < iVar3) && (iVar3 < 0x1231))
			{
				iVar3 = sub_6FB53C00(iVar3);
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
				}
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB55FC0
void __cdecl sub_6FB55FC0()
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	piVar4 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar4;
			iVar3 = sub_6FB53C00(*(int*)(iVar2 + 4));
			*(uint32_t*)(iVar2 + 0x3d) = 1;
			if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
			{
				sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB56010
uint32_t __cdecl sub_6FB56010()
{
	int* piVar1;
	int iVar2;
	int* piVar3;

	piVar3 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			if (((*(int*)(*piVar3 + 0x30) != 2) && (iVar2 = *(int*)(*piVar3 + 4), 0xb75 < iVar2)) &&
			    (iVar2 < 0x1231))
			{
				return 1;
			}
			piVar1 = piVar3 + 1;
			piVar3 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB56050
uint32_t __cdecl sub_6FB56050()
{
	int* piVar1;
	int iVar2;
	int* piVar3;

	piVar3 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			if (((*(int*)(*piVar3 + 0x30) != 2) && (iVar2 = *(int*)(*piVar3 + 4), 0x1230 < iVar2)) &&
			    (iVar2 < 0x125b))
			{
				return 1;
			}
			piVar1 = piVar3 + 1;
			piVar3 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB56090
uint32_t __fastcall sub_6FB56090(int a1)
{
	int* piVar1;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar1 + 8) == a1)
			{
				return *(uint32_t*)(*piVar1 + 4);
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB560C0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB560C0(uint32_t a1)
{
	uint32_t* puVar1;
	D2UnitStrc* pUnit2;
	float* pfVar2;
	uint32_t uVar3;
	uint32_t* a2;
	int* piVar4;
	uint32_t* puVar5;
	float fVar6;
	bool bVar7;
	float fVar8;
	uint8_t uVar9;
	uint32_t uVar10;
	int iVar11;
	void* pvVar12;
	uint32_t extraout_var;
	D2UnitStrc* pUnit1;
	uint32_t* puVar13;
	int iVar14;
	uint32_t uVar15;
	uint32_t uVar16;
	bool bVar17;
	double fVar18;
	int iStack_50;
	uint32_t* local_4c;
	uint32_t local_48;
	uint32_t* puStack_44;
	float fStack_44;
	float fStack_40;
	float fStack_3c;
	uint32_t uStack_38;
	D2UnitStrc* pDStack_34;
	float fStack_30;
	float fStack_2c;
	float fStack_28;
	uint32_t* puStack_24;
	uint32_t uStack_20;
	uint32_t local_1c;
	float fStack_18;
	float fStack_14;
	uint32_t uStack_10;
	float fStack_c;
	float fStack_8;
	uint32_t uStack_4;

	if (dword_6FBC1A5C == 0)
	{
		return;
	}
	local_4c = nullptr;
	local_48 = a1;
	if ((dword_6FBC1A68 != 0) && (uVar10 = sub_6FB54C50(), uVar10 % 3 == 0))
	{
		iVar11 = sub_6FB571B0(0xb76, 0x1230);
		sub_6FB55820(iVar11, nullptr, 0.0, 0.0, 0);
	}
	do
	{
		bVar17 = true;
		puVar13 = (uint32_t*)gpint32_t_6FBC1A58;
		piVar4 = gpint32_t_6FBC1A58;
		if (gpint32_t_6FBC1A58 == nullptr)
			break;
		do
		{
			puVar1 = (uint32_t*)puVar13[1];
			if (puVar1 != nullptr)
			{
				uVar10 = *puVar13;
				uVar16 = *puVar1;
				if ((*(uint8_t*)(uVar10 + 0x3c) < *(uint8_t*)(uVar16 + 0x3c)) ||
				    ((*(uint8_t*)(uVar10 + 0x3c) <= *(uint8_t*)(uVar16 + 0x3c) &&
				        ((*(float*)(uVar16 + 0x18) < *(float*)(uVar10 + 0x18) ||
				            ((*(float*)(uVar16 + 0x18) <= *(float*)(uVar10 + 0x18) &&
				                ((*(uint32_t*)(uVar10 + 0x34) < *(uint32_t*)(uVar16 + 0x34) ||
				                    ((*(uint32_t*)(uVar10 + 0x34) <= *(uint32_t*)(uVar16 + 0x34) &&
				                        (local_1c = (uint32_t)(uVar10 < uVar16), local_1c != 0))))))))))))
				{
					*puVar13 = uVar16;
					*puVar1 = uVar10;
					bVar17 = false;
				}
			}
			puVar13 = (uint32_t*)puVar13[1];
		} while (puVar13 != nullptr);
		piVar4 = gpint32_t_6FBC1A58;
	} while (!bVar17);
	for (; piVar4 != nullptr; piVar4 = (int*)piVar4[1])
	{
		iVar11 = *piVar4;
		if ((*(int*)(iVar11 + 0x3d) != 0) &&
		    ((*(int*)(iVar11 + 0x45) == 0 || (*(int*)(iVar11 + 0x4d) != 0))))
		{
			if (*(int*)(iVar11 + 0x30) == 0)
			{
				*(uint32_t*)(iVar11 + 0x30) = 2;
			}
			if ((*(int*)(iVar11 + 0x30) == 1) &&
			    (sub_6FB528F0(*(int**)(iVar11 + 0x2c)), *(int*)(iVar11 + 0x2c) != 0))
			{
				FOG_DisplayAssert("!ptInst->hChannel", __FILE__, __LINE__);
				exit(-1);
			}
		}
	}
	iVar11 = D2SOUND_10046();
	uStack_20 = (uint32_t)(0 < iVar11);
	for (puStack_24 = (uint32_t*)gpint32_t_6FBC1A58; puStack_24 != nullptr;
	     puStack_24 = (uint32_t*)puStack_24[1])
	{
		uVar10 = *puStack_24;
		iStack_50 = sub_6FB53C00(*(int*)(uVar10 + 4));
		uStack_38 = uStack_20;
		iVar11 = sub_6FB53D60();
		if (((iVar11 <= *(int*)(uVar10 + 4)) &&
		        (iVar11 = sub_6FB53D70(), *(int*)(uVar10 + 4) <= iVar11)) &&
		    (pvVar12 = D2SOUND_10048(), pvVar12 == nullptr))
		{
			uStack_38 = 0;
		}
		if (*(int*)(uVar10 + 0x30) == 2)
		{
			D2_ASSERT(!(*(int*)(uVar10 + 0x2c)));
			if (((*(char*)(iStack_50 + 0x3e) == '\0') || (*(short*)(iStack_50 + 0x43) != 0)) ||
			    (*(int*)(uVar10 + 0x3d) != 0))
			{
				D2SOUND_10058((int)&local_4c, uVar10);
			}
			else
			{
				if (*(int*)(uVar10 + 0x45) != 0)
				{
					*(uint32_t*)(uVar10 + 0x45) = 0;
					*(uint32_t*)(uVar10 + 0x1c) = *(uint32_t*)(uVar10 + 0x4d);
				}
				*(uint32_t*)(uVar10 + 0x30) = 0;
			}
		}
		else
		{
			if (((dword_6FBA796C != 0) && (*(char*)(iStack_50 + 0x51) != '\0')) &&
			    (*(uint32_t**)(uVar10 + 0x28) != nullptr))
			{
				fStack_c = 0.0;
				fStack_8 = 0.0;
				uStack_4 = 0;
				fStack_18 = 0.0;
				fStack_14 = 0.0;
				uStack_10 = 0;
				pDStack_34 = nullptr;
				fStack_30 = -1.0;
				fStack_3c = 0.0;
				fStack_40 = 0.0;
				for (puStack_44 = *(uint32_t**)(uVar10 + 0x28); puStack_44 != nullptr;
				     puStack_44 = (uint32_t*)puStack_44[1])
				{
					pUnit2 = (D2UnitStrc*)*puStack_44;
					D2_ASSERT(pUnit2 != nullptr);
					sub_6FB55AE0(pUnit2, *(int*)(uVar10 + 4), &fStack_c);
					fVar8 = fStack_8;
					fVar6 = fStack_c;
					fVar18 = sub_6FB572B0(fStack_c, fStack_8);
					if ((pDStack_34 == nullptr) || (fVar18 < (double)fStack_30))
					{
						fStack_18 = fVar6;
						fStack_30 = (float)fVar18;
						fStack_14 = fVar8;
						uStack_10 = uStack_4;
						pDStack_34 = pUnit2;
					}
					iVar11 = sub_6FB53C00(*(int*)(uVar10 + 4));
					if (iVar11 == 0)
					{
					LAB_6fb563a0:
						pUnit1 = CUNIT_GetPlayer();
						iVar11 = UNITS_TestCollisionWithUnit(pUnit1, pUnit2, 2);
						bVar17 = iVar11 == 0;
					LAB_6fb563b0:
						if (bVar17)
							goto LAB_6fb563ba;
						fVar6 = 0.5;
					}
					else
					{
						if (*(int*)(iVar11 + 0x47) != 4)
						{
							if (*(int*)(iVar11 + 0x60) != 0xca)
								goto LAB_6fb563a0;
							uVar9 = sub_6FB53CF0();
							iVar11 = sub_6FB53D30(D2C_ZEXT(uVar9));
							if (iVar11 == 0)
								goto LAB_6fb563ba;
							bVar17 = *(char*)(iVar11 + 0x18) == '\0';
							goto LAB_6fb563b0;
						}
					LAB_6fb563ba:
						fVar6 = 0.0;
					}
					fStack_3c = fVar6 + fStack_3c;
					fStack_40 = (float)((int)fStack_40 + 1);
				}
				*(float*)(uVar10 + 0xc) = fStack_18;
				*(float*)(uVar10 + 0x10) = fStack_14;
				*(uint32_t*)(uVar10 + 0x14) = uStack_10;
				if (fStack_18 <= -2000.0)
				{
					fStack_28 = -2000.0;
				}
				else
				{
					fStack_28 = fStack_18;
					if (2000.0 <= fStack_18)
					{
						fStack_28 = 2000.0;
					}
				}
				if (fStack_14 <= -2000.0)
				{
					fStack_2c = -2000.0;
				}
				else
				{
					fStack_2c = fStack_14;
					if (2000.0 <= fStack_14)
					{
						fStack_2c = 2000.0;
					}
				}
				fVar18 = sub_6FB572B0(fStack_28, fStack_2c);
				*(float*)(uVar10 + 0x18) = (float)fVar18;
				fStack_44 = fStack_3c / (float)(int)fStack_40;
				if (fStack_44 <= *(float*)(uVar10 + 0x20))
				{
					fVar6 = *(float*)(uVar10 + 0x20) - 0.05;
					if (fVar6 <= fStack_44)
						goto LAB_6fb564d7;
				}
				else
				{
					fVar6 = *(float*)(uVar10 + 0x20) + 0.05;
					if (fStack_44 <= fVar6)
					{
					LAB_6fb564d7:
						fVar6 = fStack_44;
					}
				}
				*(float*)(uVar10 + 0x20) = fVar6;
			}
			uVar16 = local_48;
			if (*(int*)(uVar10 + 0x45) != 0)
			{
				if (*(uint32_t*)(uVar10 + 0x55) < local_48)
				{
					*(uint32_t*)(uVar10 + 0x45) = 0;
					*(uint32_t*)(uVar10 + 0x1c) = *(uint32_t*)(uVar10 + 0x4d);
				}
				else
				{
					uVar3 = *(uint32_t*)(uVar10 + 0x51);
					if (local_48 < uVar3)
					{
						*(uint32_t*)(uVar10 + 0x1c) = *(uint32_t*)(uVar10 + 0x49);
					}
					else
					{
						*(int*)(uVar10 + 0x1c) =
						    (int)((*(int*)(uVar10 + 0x4d) - *(int*)(uVar10 + 0x49)) * (local_48 - uVar3)) /
						        (int)(*(uint32_t*)(uVar10 + 0x55) - uVar3) +
						    *(int*)(uVar10 + 0x49);
					}
				}
			}
			fVar18 = sub_6FB552A0(*(int*)(uVar10 + 4));
			fStack_40 = (float)(fVar18 * fVar18);
			if (((*(int*)(uVar10 + 0x30) == 0) && (*(uint32_t*)(uVar10 + 0x34) <= uVar16)) &&
			    (*(int*)(uVar10 + 0x1c) != 0))
			{
				if ((uStack_38 != 0) &&
				    (*(float*)(uVar10 + 0x18) < fStack_40 != (*(float*)(uVar10 + 0x18) == fStack_40)))
				{
					D2_ASSERT(!(*(int*)(uVar10 + 0x2c)));
					pfVar2 = *(float**)(uVar10 + 0x28);
					puStack_44 = nullptr;
					if ((pfVar2 != nullptr) && (pfVar2[1] == 0.0))
					{
						puStack_44 = *(uint32_t**)pfVar2;
					}
					uVar16 = 0;
					if (((*(float*)(uVar10 + 0xc) != 0.0) || (*(float*)(uVar10 + 0x10) != 0.0)) ||
					    (pDStack_34 = nullptr, *(float*)(uVar10 + 0x14) != 0.0))
					{
						pDStack_34 = (D2UnitStrc*)0x1;
					}
					if ((*(char*)(iStack_50 + 0x41) != '\0') || (*(char*)(iStack_50 + 0x42) != '\0'))
					{
						uVar16 = 0;
						local_1c = *(uint32_t*)(iStack_50 + 0x60);
						for (puVar13 = (uint32_t*)gpint32_t_6FBC1A58; puVar13 != nullptr;
						     puVar13 = (uint32_t*)puVar13[1])
						{
							uVar3 = *puVar13;
							iVar11 = sub_6FB53C00(*(int*)(uVar3 + 4));
							if ((((*(uint32_t*)(iVar11 + 0x60) == local_1c) && (uVar3 != uVar10)) &&
							        ((*(int*)(uVar3 + 0x30) == 1 &&
							            ((puStack_44 == nullptr ||
							                (iVar11 = D2SOUND_10060(*(int*)(uVar3 + 0x28), (int)puStack_44), iVar11 != 0)))))) &&
							    ((uVar16 == 0 || (*(uint32_t*)(uVar3 + 0x34) < *(uint32_t*)(uVar16 + 0x34)))))
							{
								uVar16 = uVar3;
							}
						}
					}
					puVar5 = puStack_44;
					if (((puStack_44 != nullptr) && (0xb75 < *(int*)(uVar10 + 4))) &&
					    (puVar13 = (uint32_t*)gpint32_t_6FBC1A58, *(int*)(uVar10 + 4) < 0x1231))
					{
						for (; puVar13 != nullptr; puVar13 = (uint32_t*)puVar13[1])
						{
							uVar16 = *puVar13;
							if (((uVar16 != uVar10) && (*(int*)(uVar16 + 0x30) == 1)) &&
							    ((iVar11 = D2SOUND_10060(*(int*)(uVar16 + 0x28), (int)puVar5), iVar11 != 0 &&
							                                                                       ((0xb75 < *(int*)(uVar16 + 4) && (*(int*)(uVar16 + 4) < 0x1231))))))
								goto LAB_6fb566b4;
						}
						uVar16 = 0;
					}
				LAB_6fb566b4:
					if ((((*(char*)(iStack_50 + 0x41) == '\0') || (*(int*)(uVar10 + 0x28) != 0)) ||
					        (pDStack_34 == nullptr)) &&
					    (uVar16 != 0))
					{
						if (*(char*)(iStack_50 + 0x42) == '\0')
						{
							*(uint32_t*)(uVar10 + 0x3d) = 1;
							D2SOUND_10058((int)&local_4c, uVar10);
							goto LAB_6fb56855;
						}
						*(uint32_t*)(uVar16 + 0x3d) = 1;
						D2SOUND_10058((int)&local_4c, uVar16);
					}
					iVar11 = *(int*)(uVar10 + 0x41);
					if (iVar11 != 0)
					{
						*(int*)(uVar10 + 0x24) = iVar11;
						*(uint32_t*)(uVar10 + 0x41) = 0;
					}
					uVar15 = 0;
					uVar16 = 0;
					if (iVar11 == 0)
					{
						if (((*(uint8_t*)(iStack_50 + 0x3f) != 0) && (*(int*)(uVar10 + 0x45) == 0)) &&
						    ((*(uint8_t*)(uVar10 + 0x38) & 2) == 0))
						{
							uVar16 = (uint32_t) * (uint8_t*)(iStack_50 + 0x3f);
							goto LAB_6fb56744;
						}
					}
					else
					{
						uVar16 = 3;
					LAB_6fb56744:
						uVar15 = *(uint32_t*)(uVar10 + 0x1c);
						*(uint32_t*)(uVar10 + 0x1c) = 0;
					}
					puVar13 = sub_6FB524A0(uVar10);
					*(uint32_t**)(uVar10 + 0x2c) = puVar13;
					if ((puVar13 != nullptr) && (*(uint32_t*)(uVar10 + 0x30) = 1, uVar16 != 0))
					{
						*(uint32_t*)(uVar10 + 0x49) = *(uint32_t*)(uVar10 + 0x1c);
						*(uint32_t*)(uVar10 + 0x4d) = uVar15;
						*(uint32_t*)(uVar10 + 0x51) = local_48;
						*(uint32_t*)(uVar10 + 0x55) = uVar16 + local_48;
						*(uint32_t*)(uVar10 + 0x45) = 1;
					}
					iStack_50 = sub_6FB53C00(*(int*)(uVar10 + 4));
				}
				if (((*(int*)(uVar10 + 0x2c) == 0) && (*(char*)(iStack_50 + 0x3e) == '\0')) &&
				    ((*(char*)(iStack_50 + 0x4d) == '\0' || (*(int*)(iStack_50 + 0x86) != 1))))
				{
					D2SOUND_10058((int)&local_4c, uVar10);
				}
			}
			if (*(int*)(uVar10 + 0x30) == 1)
			{
				piVar4 = *(int**)(uVar10 + 0x2c);
				D2_ASSERT(piVar4 != nullptr);
				if ((*(uint16_t*)(iStack_50 + 0x43) == 0) ||
				    (local_48 - *(int*)(uVar10 + 0x34) <= (uint32_t) * (uint16_t*)(iStack_50 + 0x43)))
				{
					if ((uStack_38 == 0) || (fStack_40 < *(float*)(uVar10 + 0x18)))
					{
						sub_6FB528F0(piVar4);
						D2_ASSERT(!(*(int*)(uVar10 + 0x2c)));
					}
					else
					{
						sub_6FB529B0(piVar4);
						if (*(int*)(iStack_50 + 0x86) == 2)
						{
							sub_6FB554D0(*(int*)(uVar10 + 4));
						}
					}
				}
				else
				{
					sub_6FB528F0(piVar4);
					D2_ASSERT(!(*(int*)(uVar10 + 0x2c)));
				}
			}
		}
	LAB_6fb56855:
	}
	puStack_24 = nullptr;
	for (puVar5 = local_4c; puVar5 != nullptr; puVar5 = (uint32_t*)puVar5[1])
	{
		a2 = (uint32_t*)*puVar5;
		if (a2 != nullptr)
		{
			D2SOUND_10059((int)&gpint32_t_6FBC1A58, (int)a2);
			for (piVar4 = (int*)a2[10]; piVar4 != nullptr; piVar4 = (int*)piVar4[1])
			{
				sub_6FB4F960(*piVar4);
			}
			D2SOUND_10062((int)(a2 + 10));
			if (a2[0xc] == 1)
			{
				sub_6FB528F0((int*)a2[0xb]);
			}
			D2_ASSERT(!a2[0xb]);
			*a2 = 0;
		}
	}
	D2SOUND_10062((int)&local_4c);
	iVar11 = sub_6FAABFF0();
	if (((iVar11 == 0) || (iVar11 = sub_6FAABFF0(), iVar11 == 1)) &&
	    ((iVar11 = sub_6FB23860(9), iVar11 != 0 || (iVar11 = sub_6FB23860(0xb), iVar11 != 0))))
	{
		bVar17 = true;
	}
	else
	{
		bVar17 = false;
	}
	bVar7 = false;
	piVar4 = gpint32_t_6FBC1A58;
	do
	{
		if (piVar4 == nullptr)
		{
		LAB_6fb56a06:
			uVar10 = dword_6FB96A94;
			if (dword_6FBC1A64 < local_48)
			{
				if (bVar17)
				{
					dword_6FB96A94 = ((int)(dword_6FB96A94 - 5) < 0) - 1 & dword_6FB96A94 - 5;
				}
				else
				{
					dword_6FB96A94 = 100;
					if ((int)(uVar10 + 5) < 0x65)
					{
						dword_6FB96A94 = uVar10 + 5;
					}
				}
				if (bVar7)
				{
					dword_6FB96A98 = dword_6FB96A98 + -2;
					if (dword_6FB96A98 < 0x46)
					{
						dword_6FBC1A64 = local_48;
						dword_6FB96A98 = 0x46;
						return;
					}
				}
				else
				{
					dword_6FB96A98 = dword_6FB96A98 + 2;
					if (100 < dword_6FB96A98)
					{
						dword_6FB96A98 = 100;
						dword_6FBC1A64 = local_48;
						return;
					}
				}
			}
			dword_6FBC1A64 = local_48;
			return;
		}
		iVar11 = *piVar4;
		iVar14 = sub_6FB53C00(*(int*)(iVar11 + 4));
		if ((*(char*)(iVar14 + 0x52) != '\0') &&
		    ((*(int*)(iVar11 + 0x45) == 0 || (*(int*)(iVar11 + 0x4d) != 0))))
		{
			bVar7 = true;
			goto LAB_6fb56a06;
		}
		piVar4 = (int*)piVar4[1];
	} while (true);
}

//D2Client.0x6FB56AA0
void __cdecl sub_6FB56AA0()
{
	dword_6FBC1A5C = 1;
	dword_6FBC1A60 = 0;
	sub_6FB53800();
}

//D2Client.0x6FB56AC0
void __cdecl sub_6FB56AC0()
{
	uint32_t* a2;
	int* piVar1;

	sub_6FB53800();
	piVar1 = gpint32_t_6FBC1A58;
	while (true)
	{
		do
		{
			if (piVar1 == nullptr)
			{
				dword_6FBC1A5C = 1;
				return;
			}
			a2 = (uint32_t*)*piVar1;
		} while (a2 == nullptr);
		D2SOUND_10059((int)&gpint32_t_6FBC1A58, (int)a2);
		for (piVar1 = (int*)a2[10]; piVar1 != nullptr; piVar1 = (int*)piVar1[1])
		{
			sub_6FB4F960(*piVar1);
		}
		D2SOUND_10062((int)(a2 + 10));
		if (a2[0xc] == 1)
		{
			sub_6FB528F0((int*)a2[0xb]);
		}
		if (a2[0xb] != 0)
			break;
		*a2 = 0;
		piVar1 = gpint32_t_6FBC1A58;
	}
	FOG_DisplayAssert("!ptInst->hChannel", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB56B60
uint32_t __fastcall sub_6FB56B60(int a1)
{
	int* piVar1;
	uint32_t uVar2;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar1 + 8) == a1)
			{
				D2_ASSERT(*(int*)(*piVar1 + 0x2c));
				uVar2 = sub_6FB52DA0();
				return uVar2;
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return 0;
}

//D2Client.0x6FB56BB0
bool __fastcall sub_6FB56BB0(uint32_t a1, uint32_t a2, int a3, int a4)
{
	if (*(uint8_t*)(a2 + 0x3c) < *(uint8_t*)(a1 + 0x3c))
	{
		return true;
	}
	if (*(uint8_t*)(a1 + 0x3c) < *(uint8_t*)(a2 + 0x3c))
	{
		return false;
	}
	if (a3 != 0)
	{
		if (*(float*)(a1 + 0x18) < *(float*)(a2 + 0x18))
		{
			return true;
		}
		if (*(float*)(a2 + 0x18) < *(float*)(a1 + 0x18))
		{
			return false;
		}
	}
	if (a4 != 0)
	{
		if (*(uint32_t*)(a2 + 0x34) < *(uint32_t*)(a1 + 0x34))
		{
			return true;
		}
		if (*(uint32_t*)(a1 + 0x34) < *(uint32_t*)(a2 + 0x34))
		{
			return false;
		}
	}
	return a2 < a1;
}

//D2Client.0x6FB56C30
uint32_t __fastcall sub_6FB56C30(D2UnitStrc* pUnit)
{
	double fVar1;
	float local_c;
	float local_8;

	sub_6FB55AE0(pUnit, 0, &local_c);
	fVar1 = sub_6FB572B0(local_c, local_8);
	if (fVar1 < (double)490000.0 != (fVar1 == (double)490000.0))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB56C70
bool __fastcall sub_6FB56C70(int a1)
{
	int iVar1;
	int iVar2;
	int* piVar3;

	piVar3 = gpint32_t_6FBC1A58;
	if (gpint32_t_6FBC1A58 != nullptr)
	{
		do
		{
			iVar2 = *piVar3;
			if ((iVar2 != 0) && (*(int*)(iVar2 + 0x30) == 1))
			{
				if (a1 != 0)
				{
					iVar1 = D2SOUND_10060(*(int*)(iVar2 + 0x28), a1);
					if (iVar1 == 0)
						goto LAB_6fb56cae;
				}
				if ((0xb75 < *(int*)(iVar2 + 4)) && (*(int*)(iVar2 + 4) < 0x1231))
					goto LAB_6fb56cb7;
			}
		LAB_6fb56cae:
			piVar3 = (int*)piVar3[1];
		} while (piVar3 != nullptr);
	}
	iVar2 = 0;
LAB_6fb56cb7:
	return iVar2 != 0;
}

//D2Client.0x6FB56CD0
void __cdecl sub_6FB56CD0()
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int* piVar4;

	dword_6FBC1A68 = (uint32_t)(dword_6FBC1A68 == 0);
	if ((dword_6FBC1A68 == 0) && (piVar4 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			iVar2 = *piVar4;
			iVar3 = *(int*)(iVar2 + 4);
			if ((0xb75 < iVar3) && (iVar3 < 0x1231))
			{
				iVar3 = sub_6FB53C00(iVar3);
				*(uint32_t*)(iVar2 + 0x3d) = 1;
				if ((*(uint8_t*)(iVar3 + 0x40) != 0) && (*(int*)(iVar2 + 0x30) == 1))
				{
					sub_6FB55BF0(*(int*)(iVar2 + 8), 0, 0, (uint32_t) * (uint8_t*)(iVar3 + 0x40));
				}
			}
			piVar1 = piVar4 + 1;
			piVar4 = (int*)*piVar1;
		} while ((int*)*piVar1 != nullptr);
	}
}

//D2Client.0x6FB56D40
void __fastcall sub_6FB56D40()
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uVar4;

	dword_6FBC1A6C = 0;
	byte_6FBC1A70 = 0;
	dword_6FBC1A74 = 0;
	dword_6FBC1A78 = 0;
	dword_6FBC1A7C = 0;
	dword_6FBC1A80 = 0;
	dword_6FBC1AA0 = 0;
	iVar1 = sub_6FB53D60();
	iVar2 = sub_6FB53D70();
	puVar3 = (uint32_t*)sub_6FB53D80();
	for (uVar4 = (1 - iVar1) + iVar2 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*(uint8_t*)puVar3 = 0;
		puVar3 = (uint32_t*)((int)puVar3 + 1);
	}
}

//D2Client.0x6FB56DA0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB56DA0(uint32_t a1)
{
	uint8_t uVar1;
	bool bVar2;
	int iVar3;
	uint32_t extraout_var;
	int* piVar4;
	int iVar5;
	void* pvVar6;
	uint32_t uVar7;
	D2UnitStrc* pDVar8;
	uint32_t extraout_var_00;
	int iVar9;
	float fVar10;

	iVar3 = sub_6FB53CD0();
	if (iVar3 != 0)
	{
		if (iVar3 != dword_6FBC1A78)
		{
			dword_6FBC1A6C = a1;
			dword_6FBC1A78 = iVar3;
		}
		iVar3 = 0;
		uVar1 = sub_6FB53CF0();
		piVar4 = (int*)sub_6FB53D30(D2C_ZEXT(uVar1));
		if (((piVar4 != nullptr) && (iVar3 = *piVar4, iVar3 != 0)) &&
		    ((iVar5 = sub_6FB53D60(), iVar3 < iVar5 || (iVar5 = sub_6FB53D70(), iVar5 < iVar3))))
		{
			iVar3 = 0;
		}
		iVar5 = D2SOUND_10046();
		if ((iVar5 == 0) || (pvVar6 = D2SOUND_10048(), pvVar6 == nullptr))
		{
			bVar2 = false;
		}
		else
		{
			bVar2 = true;
		}
		if ((dword_6FBC1A74 != iVar3) && (0x4a < a1 - dword_6FBC1A6C || (!bVar2 || dword_6FBC1A74 == 0)))
		{
			dword_6FBC1A74 = iVar3;
			dword_6FBC1A7C = a1;
		}
		if (!bVar2)
		{
			sub_6FB55DF0();
		}
		if (dword_6FBC1A74 == 0)
		{
			sub_6FB55DF0();
		}
		if (dword_6FBC1A80 != 0)
		{
			if ((dword_6FBC1A8C != 0) && (uVar7 = sub_6FAABF80(), dword_6FBC1A88 <= uVar7))
			{
				sub_6FB55820(dword_6FBC1A84, nullptr, 0.0, 0.0, 0);
				dword_6FBC1A8C = 0;
			}
			if ((dword_6FBC1A98 != 0) && (uVar7 = sub_6FAABF80(), (uint32_t)dword_6FBC1A94 <= uVar7))
			{
				pDVar8 = CUNIT_GetPlayer();
				iVar3 = sub_6FB29550((int*)pDVar8);
				if (iVar3 == 0)
				{
					sub_6FB55820(dword_6FBC1A90, pDVar8, 0.0, 0.0, 0);
				}
				dword_6FBC1A98 = 0;
			}
			uVar7 = sub_6FAABF80();
			if (uVar7 < (uint32_t)dword_6FBC1A9C)
			{
				return;
			}
			dword_6FBC1A80 = 0;
			if (bVar2)
			{
				sub_6FB55DA0(dword_6FBC1A84);
			}
		}
		if (((dword_6FBC1A74 != 0) && (bVar2)) && (iVar3 = sub_6FB556F0(dword_6FBC1A74), iVar3 == 0))
		{
			iVar3 = sub_6FB53D60();
			iVar3 = dword_6FBC1A74 - iVar3;
			iVar5 = (int)(sub_6FB53D80());
			iVar3 = *(int*)(iVar5 + iVar3 * 4);
			iVar5 = sub_6FB56050();
			if ((iVar5 == 0) && (iVar3 == 0))
			{
				fVar10 = 2.8026e-45;
			}
			else
			{
				fVar10 = 0.0;
			}
			sub_6FB55DF0();
			sub_6FB55820(dword_6FBC1A74, nullptr, 0.0, fVar10, iVar3);
			byte_6FBC1A70 = a1;
		}
		if ((dword_6FBC1A78 != dword_6FBC1AA0) && (0x3d < a1 - dword_6FBC1A6C))
		{
			sub_6FB520A0();
			dword_6FBC1AA0 = dword_6FBC1A78;
		}
		if ((dword_6FBC1A74 != 0) && (dword_6FBC1A7C + 0x7d < a1))
		{
			iVar3 = sub_6FB53C00(dword_6FBC1A74);
			iVar5 = sub_6FB556F0(dword_6FBC1A74);
			if ((iVar5 != 0) && (bVar2 = sub_6FB55520(iVar5), D2C_ZEXT(bVar2) != 0))
			{
				iVar9 = sub_6FB56B60(iVar5);
				iVar5 = 0;
				if ((-1 < iVar9) && (iVar9 < *(int*)(iVar3 + 0x54)))
				{
					iVar5 = *(int*)(iVar3 + 0x54);
				}
				if ((*(int*)(iVar3 + 0x54) <= iVar9) && (iVar9 < *(int*)(iVar3 + 0x58)))
				{
					iVar5 = *(int*)(iVar3 + 0x58);
				}
				if ((*(int*)(iVar3 + 0x58) <= iVar9) && (iVar9 < *(int*)(iVar3 + 0x5c)))
				{
					iVar5 = *(int*)(iVar3 + 0x5c);
				}
				iVar3 = sub_6FB53D60();
				iVar3 = dword_6FBC1A74 - iVar3;
				iVar9 = (int)(sub_6FB53D80());
				*(int*)(iVar9 + iVar3 * 4) = iVar5;
				dword_6FBC1A7C = a1;
			}
		}
	}
}

//D2Client.0x6FB57030
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB57030(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	bool bVar1;
	int iVar2;
	int iVar3;
	uint32_t extraout_var;
	uint32_t uVar4;

	if (dword_6FBC1A74 != 0)
	{
		iVar2 = sub_6FB53C00(dword_6FBC1A74);
		iVar3 = sub_6FB556F0(dword_6FBC1A74);
		if (iVar3 != 0)
		{
			bVar1 = sub_6FB55520(iVar3);
			if (D2C_ZEXT(bVar1) != 0)
			{
				if (a4 == 0)
				{
					uVar4 = 0;
				}
				else
				{
					uVar4 = *(uint32_t*)(iVar2 + 0x50 + a4 * 4);
				}
				iVar2 = sub_6FB53D60();
				iVar2 = dword_6FBC1A74 - iVar2;
				iVar3 = (int)(sub_6FB53D80());
				*(uint32_t*)(iVar3 + iVar2 * 4) = uVar4;
				dword_6FBC1A7C = sub_6FB54C50();
			}
		}
	}
	sub_6FB55DF0();
	dword_6FBC1A80 = 1;
	dword_6FBC1A84 = a1;
	iVar2 = sub_6FAABF80();
	dword_6FBC1A88 = iVar2 + a2;
	dword_6FBC1A8C = 1;
	dword_6FBC1A90 = a5;
	iVar2 = sub_6FAABF80();
	dword_6FBC1A94 = iVar2 + a6;
	dword_6FBC1A98 = a7;
	iVar2 = sub_6FAABF80();
	dword_6FBC1A9C = iVar2 + a3;
}

//D2Client.0x6FB57100
void __fastcall sub_6FB57100(int a1, int a2)
{
	int iVar1;

	if (dword_6FBC1A80 != 0)
	{
		if (a2 != 0)
		{
			iVar1 = sub_6FAABF80();
			dword_6FBC1A98 = a2;
			dword_6FBC1A94 = iVar1 + a1;
			dword_6FBC1A9C = iVar1 + a1 + 0x32;
			return;
		}
		dword_6FBC1A9C = dword_6FBC1A94 + 0x32;
		dword_6FBC1A98 = 0;
	}
}

//D2Client.0x6FB57150
uint32_t __fastcall sub_6FB57150(uint32_t a1)
{
	uint64_t DVar1;
	uint64_t uVar2;
	D2UnitStrc* pDVar3;
	D2SeedStrc* pDVar4;

	pDVar3 = CUNIT_GetPlayer();
	pDVar4 = &pDVar3->pSeed;
	if ((int)a1 < 1)
	{
		return 0;
	}
	uVar2 = (uint64_t)(pDVar3->pSeed).nHighSeed;
	if ((a1 & a1 - 1) != 0)
	{
		DVar1 = (uint64_t)((uint64_t)pDVar4->nLowSeed * 0x6ac690c5 + uVar2);
		*(uint64_t*)pDVar4 = DVar1;
		return (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)a1);
	}
	DVar1 = (uint64_t)((uint64_t)pDVar4->nLowSeed * 0x6ac690c5 + uVar2);
	*(uint64_t*)pDVar4 = DVar1;
	return a1 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
}

//D2Client.0x6FB571B0
int __fastcall sub_6FB571B0(int a1, int a2)
{
	uint64_t DVar1;
	uint64_t uVar2;
	D2UnitStrc* pDVar3;
	D2SeedStrc* pDVar4;
	uint32_t uVar5;
	uint32_t uVar6;

	uVar5 = a2 - a1;
	uVar6 = uVar5 + 1;
	pDVar3 = CUNIT_GetPlayer();
	pDVar4 = &pDVar3->pSeed;
	if ((int)uVar6 < 1)
	{
		return a1;
	}
	uVar2 = (uint64_t)(pDVar3->pSeed).nHighSeed;
	if ((uVar6 & uVar5) != 0)
	{
		DVar1 = (uint64_t)((uint64_t)pDVar4->nLowSeed * 0x6ac690c5 + uVar2);
		*(uint64_t*)pDVar4 = DVar1;
		return (int)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar6) + a1;
	}
	DVar1 = (uint64_t)((uint64_t)pDVar4->nLowSeed * 0x6ac690c5 + uVar2);
	*(uint64_t*)pDVar4 = DVar1;
	return (uVar5 & (*(uint32_t*)((uint8_t*)&DVar1 + 0))) + a1;
}

//D2Client.0x6FB57220
int __fastcall sub_6FB57220(int a1)
{
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	D2SeedStrc* pDVar6;

	uVar4 = a1 * 2;
	uVar1 = uVar4 + 1;
	pDVar5 = CUNIT_GetPlayer();
	pDVar6 = &pDVar5->pSeed;
	if ((int)uVar1 < 1)
	{
		return -a1;
	}
	uVar3 = (uint64_t)(pDVar5->pSeed).nHighSeed;
	if ((uVar1 & uVar4) != 0)
	{
		DVar2 = (uint64_t)((uint64_t)pDVar6->nLowSeed * 0x6ac690c5 + uVar3);
		*(uint64_t*)pDVar6 = DVar2;
		return (int)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar1) - a1;
	}
	DVar2 = (uint64_t)((uint64_t)pDVar6->nLowSeed * 0x6ac690c5 + uVar3);
	*(uint64_t*)pDVar6 = DVar2;
	return (uVar4 & (*(uint32_t*)((uint8_t*)&DVar2 + 0))) - a1;
}

//D2Client.0x6FB57290
double __cdecl sub_6FB57290(float a1, float a2)
{
	return sqrt((double)a2 * (double)a2 + (double)a1 * (double)a1);
}

//D2Client.0x6FB572B0
double __cdecl sub_6FB572B0(float a1, float a2)
{
	return (double)a2 * (double)a2 + (double)a1 * (double)a1;
}

//D2Client.0x6FB572D0
int __fastcall sub_6FB572D0(uint32_t a1, uint32_t a2, uint32_t a3)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;

	uVar2 = a3 - 1;
	if ((a3 & uVar2) == 0)
	{
		uVar5 = uVar2 & a1;
		uVar2 = uVar2 & a2;
	}
	else
	{
		uVar5 = (int)a1 % (int)a3;
		uVar2 = (int)a2 % (int)a3;
	}
	iVar1 = uVar2 - uVar5;
	iVar4 = iVar1;
	if (iVar1 < 0)
	{
		iVar4 = -iVar1;
	}
	iVar1 = iVar1 - a3;
	if (iVar1 < 0)
	{
		iVar1 = -iVar1;
	}
	iVar6 = (uVar5 - uVar2) - a3;
	if (iVar6 < 0)
	{
		iVar6 = -iVar6;
	}
	iVar3 = iVar4;
	if (iVar1 <= iVar4)
	{
		iVar3 = iVar1;
	}
	if ((iVar3 < iVar6) && (iVar6 = iVar4, iVar1 <= iVar4))
	{
		iVar6 = iVar1;
	}
	return iVar6;
}

#include "Sound/SoundChan.h"

#include "Draw/DFloor.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB70F58
uint8_t byte_6FB70F58 = 0xFF;
//D2Client.0x6FB9661C
int32_t dword_6FB9661C = -1;
//D2Client.0x6FB96A94
uint32_t dword_6FB96A94 = 0x64;
//D2Client.0x6FB96A98
int32_t dword_6FB96A98 = 100;
//D2Client.0x6FBBD268
uint32_t dword_6FBBD268;
//D2Client.0x6FBBD26C
uint32_t dword_6FBBD26C;
//D2Client.0x6FBBD270
uint32_t dword_6FBBD270;
//D2Client.0x6FBBD2EC
uint32_t tbl_6FBBD2EC[95];
//D2Client.0x6FBBD468
uint32_t dword_6FBBD468;
//D2Client.0x6FBBD46B
uint8_t tbl_6FBBD46B[1];
//D2Client.0x6FBBD46C
int32_t dword_6FBBD46C;
//D2Client.0x6FBBD46F
uint8_t tbl_6FBBD46F[1];
//D2Client.0x6FBBD474
int32_t dword_6FBBD474;
//D2Client.0x6FBBD478
int32_t dword_6FBBD478;
//D2Client.0x6FBBD47C
int32_t dword_6FBBD47C;
//D2Client.0x6FBBD480
int32_t dword_6FBBD480;
//D2Client.0x6FBBD484
uint32_t dword_6FBBD484;
//D2Client.0x6FBBD488
int32_t dword_6FBBD488;
//D2Client.0x6FBBD48C
uint32_t dword_6FBBD48C;
//D2Client.0x6FBBD490
int32_t dword_6FBBD490;
//D2Client.0x6FBBD494
uint32_t* gpuint32_t_6FBBD494;
//D2Client.0x6FBBD4B8
int32_t dword_6FBBD4B8;

//D2Client.0x6FB52330
uint32_t __fastcall sub_6FB52330(int a1)
{
	int iVar1;
	uint32_t local_18;
	uint16_t local_14;
	short sStack_12;
	int iStack_10;
	short sStack_6;

	D2_ASSERT(*(int*)(a1 + 0x86) == 2);
	local_18 = *(uint32_t*)(a1 + 0x70);
	iVar1 = D2SOUND_10056(*(int*)(a1 + 0x6c), (int)&local_18, (int)local_14);
	if (((iVar1 != 0) && (sStack_6 == 0x10)) && (iStack_10 == 0x5622))
	{
		*(int*)(a1 + 0x74) = iVar1;
		*(uint32_t*)(a1 + 0x78) = local_18;
		*(bool*)(a1 + 0x50) = sStack_12 == 2;
		return 1;
	}
	*(uint8_t*)(a1 + 0x81) = 1;
	return 0;
}

//D2Client.0x6FB523C0
void __fastcall sub_6FB523C0(int a1)
{
	int iVar1;
	int iVar2;

	iVar1 = dword_6FB9661C;
	if (a1 != dword_6FB9661C)
	{
		sub_6FB53D30(a1);
		iVar1 = D2SOUND_10044();
		if (((iVar1 == 2) || (iVar1 = a1, a1 == 0)) &&
		    (iVar2 = D2SOUND_10004(), iVar1 = a1, iVar2 != 0))
		{
			D2SOUND_10006();
			iVar1 = a1;
		}
	}
	dword_6FB9661C = iVar1;
}

//D2Client.0x6FB524A0
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FB524A0(uint32_t a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t uVar4;
	int* piVar5;
	uint32_t* puVar6;
	int* piVar7;
	uint32_t* puVar8;
	bool bVar9;
	int local_58;
	char acStack_50[80];

	iVar1 = sub_6FB53C00(*(int*)(a1 + 4));
	if ((*(uint8_t*)(a1 + 0x38) & 1) == 0)
	{
		iVar2 = sub_6FB55310(*(int*)(a1 + 4));
		*(int*)(a1 + 4) = iVar2;
	}
	iVar2 = *(int*)(a1 + 4);
	if (dword_6FBBD46C != 0)
	{
		piVar7 = nullptr;
		piVar5 = (int*)(&dword_6FBBD270);
		do
		{
			iVar3 = D2SOUND_10013(piVar5[-2]);
			if ((((iVar3 != 0) && (iVar3 = *piVar5, iVar3 != 0)) && (*(int*)(iVar3 + 4) == iVar2)) &&
			    ((piVar7 == nullptr || (*(uint32_t*)(iVar3 + 0x34) < *(uint32_t*)(piVar7[2] + 0x34)))))
			{
				piVar7 = piVar5 + -2;
			}
			piVar5 = piVar5 + 8;
		} while ((int)piVar5 < (int)&dword_6FBBD470);
		if (((piVar7 != nullptr) && (iVar2 = piVar7[2], *(int*)(iVar2 + 0x3d) == 0)) &&
		    (((uint32_t)(*(int*)(a1 + 0x34) - *(int*)(iVar2 + 0x34)) < 2 &&
		        (*(uint8_t*)(a1 + 0x3c) <= *(uint8_t*)(iVar2 + 0x3c)))))
		{
			return nullptr;
		}
	}
	iVar2 = sub_6FB53C00(*(int*)(a1 + 4));
	*(uint32_t*)(iVar1 + 0x68) = *(uint32_t*)(iVar1 + 100);
	*(uint32_t*)(iVar1 + 100) = *(uint32_t*)(a1 + 4);
	sub_6FB527A0();
	if (((*(char*)(iVar2 + 0x4f) == '\0') && (*(int*)(iVar2 + 0x86) != 2)) &&
	    (sub_6FB54D90(*(int*)(a1 + 4), (uint32_t)(*(char*)(iVar2 + 0x4d) == '\0'), 0),
	        *(int*)(iVar2 + 0x86) != 2))
	{
		return nullptr;
	}
	if (*(char*)(iVar2 + 0x81) != '\0')
	{
		return nullptr;
	}
	bVar9 = *(char*)(iVar2 + 0x50) != '\0';
	uVar4 = (uint32_t)bVar9;
	if (!bVar9)
	{
		iVar1 = D2SOUND_10044();
		if (iVar1 == 1)
		{
			uVar4 = uVar4 | 2;
		}
		iVar1 = D2SOUND_10044();
		if (iVar1 == 2)
		{
			uVar4 = uVar4 | 6;
		}
	}
	puVar6 = &dword_6FBBD268;
	do
	{
		if (((puVar6[2] == 0) && (puVar6[1] == uVar4)) && (iVar1 = D2SOUND_10013(*puVar6), iVar1 == 0))
			goto LAB_6fb5269a;
		puVar6 = puVar6 + 8;
	} while ((int)puVar6 < (int)&dword_6FBBD468);
	puVar6 = nullptr;
	puVar8 = &dword_6FBBD270;
	do
	{
		if (((puVar8[-1] == uVar4) && (*puVar8 != 0)) &&
		    ((puVar6 == nullptr ||
		        (bVar9 = sub_6FB56BB0(puVar6[2], *puVar8, 1, 1), D2C_ZEXT(bVar9) != 0))))
		{
			puVar6 = puVar8 + -2;
		}
		puVar8 = puVar8 + 8;
	} while ((int)puVar8 < (int)&dword_6FBBD470);
	if ((puVar6 != nullptr) &&
	    (bVar9 = sub_6FB56BB0(a1, puVar6[2], 0, 0), D2C_ZEXT(bVar9) != 0))
	{
		if (*puVar6 != 0)
		{
			if (puVar6[2] != 0)
			{
				iVar1 = D2SOUND_10018();
				*(int*)(puVar6[2] + 0x41) = iVar1;
			}
			D2SOUND_10012(*puVar6);
		}
		if (puVar6[2] != 0)
		{
			*(uint32_t*)(puVar6[2] + 0x30) = 2;
			*(uint32_t*)(puVar6[2] + 0x2c) = 0;
			puVar6[2] = 0;
		}
	LAB_6fb5269a:
		if (puVar6 != nullptr)
		{
			D2SOUND_10009(*puVar6);
			if (*(char*)(iVar2 + 0x4f) == '\0')
			{
				D2SOUND_10019(*puVar6, (uint32_t) * (uint8_t*)(iVar2 + 0x3e));
				if (*(char*)(iVar2 + 0x80) == '\x01')
				{
					D2SOUND_10020(*puVar6, *(int*)(iVar2 + 0x54) * 2);
				}
				iVar1 = D2SOUND_10010(*puVar6, *(int*)(iVar2 + 0x6c), *(int*)(iVar2 + 0x70));
				if (iVar1 == 0)
				{
					return nullptr;
				}
			}
			puVar6[2] = a1;
			if ((uVar4 & 4) != 0)
			{
				local_58 = 0x3f800000;
				if (*(char*)(iVar2 + 0x4b) == '\0')
				{
					local_58 = 0;
				}
				D2SOUND_10022(*puVar6, local_58, local_58);
			}
			puVar6[6] = 0xffffffff;
			puVar6[7] = 0;
			puVar6[3] = 0;
			puVar6[4] = 0;
			puVar6[5] = 0;
			sub_6FB529B0((int*)puVar6);
			if (*(char*)(iVar2 + 0x4f) == '\0')
			{
				iVar1 = D2SOUND_10011(*puVar6);
				if (iVar1 == 0)
				{
					puVar6[2] = 0;
					return nullptr;
				}
			}
			else
			{
				sub_6FB553B0(*(int*)(a1 + 4), acStack_50);
				iVar1 = D2SOUND_10025(*puVar6, (int)acStack_50, *(int*)(a1 + 0x24),
				    (uint32_t) * (uint8_t*)(iVar2 + 0x3e));
				if (iVar1 == 0)
				{
					puVar6[2] = 0;
					return nullptr;
				}
			}
			return puVar6;
		}
	}
	return nullptr;
}

//D2Client.0x6FB527A0
void __cdecl sub_6FB527A0()
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t* puVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	void* local_14;
	uint32_t uStack_10;
	uint8_t* puStack_c;
	uint32_t local_8;

	puStack_c = &byte_6FB70F58;
	uStack_10 = 0x6fb61938;
	if ((dword_6FBBD470 & 0x4000) != 0)
	{
		dword_6FBBD470 = 0;
		if ((gnGameType == 2) || (gnGameType == 3))
		{
			local_8 = 0;
			puVar4 = (uint32_t*)D2NET_10039();
			uVar1 = *puVar4;
			puVar4 = (uint32_t*)D2NET_10040();
			uVar2 = *puVar4;
			local_8 = 1;
			puVar4 = (uint32_t*)D2Win_10206();
			uVar3 = *puVar4;
			puVar4 = (uint32_t*)D2Win_10207();
			local_8 = 0xffffffff;
			uVar5 = *puVar4 & 0xffff;
			uVar6 = uVar3 & 0xffff;
			uVar7 = uVar2 & 0xffff;
			uVar8 = uVar1 & 0xffff;
			sub_6FAADAA0(D2C_ZEXT(0x65), (uVar1 >> 0x10 ^ uVar8) << 0x10 | uVar8,
			    (uVar2 >> 0x10 ^ uVar7) << 0x10 | uVar7, (uVar3 >> 0x10 ^ uVar6) << 0x10 | uVar6,
			    (*puVar4 >> 0x10 ^ uVar5) << 0x10 | uVar5);
		}
	}
}

//D2Client.0x6FB528D0
void __fastcall sub_6FB528D0(int a1)
{
	if (*(int*)(a1 + 8) != 0)
	{
		*(uint32_t*)(*(int*)(a1 + 8) + 0x30) = 2;
		*(uint32_t*)(*(int*)(a1 + 8) + 0x2c) = 0;
		*(uint32_t*)(a1 + 8) = 0;
	}
}

//D2Client.0x6FB528F0
void __fastcall sub_6FB528F0(int* a1)
{
	int iVar1;

	if (*a1 != 0)
	{
		if (a1[2] != 0)
		{
			iVar1 = D2SOUND_10018();
			*(int*)(a1[2] + 0x41) = iVar1;
		}
		D2SOUND_10012(*a1);
	}
	if (a1[2] != 0)
	{
		*(uint32_t*)(a1[2] + 0x30) = 2;
		*(uint32_t*)(a1[2] + 0x2c) = 0;
		a1[2] = 0;
	}
}

//D2Client.0x6FB52940
void __cdecl sub_6FB52940()
{
	int iVar1;
	int* piVar2;

	iVar1 = D2SOUND_10002();
	if (iVar1 != 0)
	{
		D2SOUND_10027(0);
		piVar2 = (int*)(&dword_6FBBD270);
		do
		{
			if (piVar2[-2] != 0)
			{
				if (*piVar2 != 0)
				{
					iVar1 = D2SOUND_10018();
					*(int*)(*piVar2 + 0x41) = iVar1;
				}
				D2SOUND_10012(piVar2[-2]);
			}
			if (*piVar2 != 0)
			{
				*(uint32_t*)(*piVar2 + 0x30) = 2;
				*(uint32_t*)(*piVar2 + 0x2c) = 0;
				*piVar2 = 0;
			}
			piVar2 = piVar2 + 8;
		} while ((int)piVar2 < (int)&dword_6FBBD470);
		D2SOUND_10027(0xff);
		return;
	}
}

//D2Client.0x6FB529B0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB529B0(int* a1)
{
	uint8_t* pbVar1;
	float a3;
	int iVar2;
	int iVar3;
	void* pvVar4;
	int iVar5;
	int extraout_EDX;
	int iVar6;
	int* piVar7;
	int* piVar8;
	bool bVar9;
	double fVar10;
	int64_t lVar11;
	int iStack_14;
	int local_10;
	float local_c;
	float local_8;
	float local_4;

	iVar5 = a1[2];
	local_10 = iVar5;
	if (iVar5 == 0)
	{
		FOG_DisplayAssert("ptChannel->ptInst", __FILE__, __LINE__);
		exit(-1);
	}
	iVar3 = sub_6FB53C00(*(int*)(iVar5 + 4));
	local_4 = (float)iVar3;
	fVar10 = sub_6FB55230(*(int*)(iVar5 + 4));
	local_8 = (float)fVar10;
	fVar10 = sub_6FB552A0(*(int*)(iVar5 + 4));
	iVar6 = *(int*)(iVar5 + 0x1c);
	local_c = (float)fVar10;
	if (*(char*)(iVar3 + 0x53) != '\0')
	{
		pvVar4 = D2SOUND_10048();
		iVar6 = ((int)pvVar4 * iVar6) / 100;
	}
	iVar3 = D2SOUND_10046();
	iStack_14 = (iVar3 * iVar6) / 100;
	if ((((dword_6FB96A94 != 100) &&
	         ((iVar6 = *(int*)(iVar5 + 4), iVar6 < 0x1231 || (0x125a < iVar6)))) &&
	        ((iVar6 < 0x34 || (0x47 < iVar6)))) &&
	    ((iVar6 < 1 || (0xf < iVar6))))
	{
		iStack_14 = (int)(dword_6FB96A94 * iStack_14) / 100;
	}
	if ((dword_6FB96A98 != 100) && (*(char*)((int)local_4 + 0x52) == '\0'))
	{
		iStack_14 = (dword_6FB96A98 * iStack_14) / 100;
	}
	iVar6 = iStack_14;
	if ((dword_6FBBD46C != 0) &&
	    (((iVar3 = D2SOUND_10044(), iVar3 == 1 || (iVar3 == 2)) &&
	        (iVar3 = D2SOUND_10050(), iVar3 != 0x32))))
	{
		iVar3 = D2SOUND_10050();
		iVar3 = (iVar3 * 2 + -100) / 3;
		if ((*a1 != 0) && (0 < iVar3))
		{
			iVar6 = ((0xff - (iVar3 * 0xff) / 0x32) * iVar6) / 0xff;
			iStack_14 = iVar6;
		}
		if (((*(uint8_t*)(a1 + 1) & 2) != 0) && (iVar3 < 0))
		{
			iVar6 = (((iVar3 * 0xff) / 0x32 + 0xff) * iVar6) / 0xff;
			iStack_14 = iVar6;
		}
	}
	if ((iVar6 == a1[6]) && (*(float*)(iVar5 + 0x20) == (float)a1[7]))
	{
		iVar5 = 3;
		bVar9 = true;
		piVar7 = (int*)(local_10 + 0xc);
		piVar8 = a1 + 3;
		do
		{
			if (iVar5 == 0)
				break;
			iVar5 = iVar5 + -1;
			bVar9 = *piVar7 == *piVar8;
			piVar7 = piVar7 + 1;
			piVar8 = piVar8 + 1;
		} while (bVar9);
		iVar5 = local_10;
		if (bVar9)
		{
			return;
		}
	}
	fVar10 = sub_6FB57290(*(float*)(iVar5 + 0xc), *(float*)(iVar5 + 0x10));
	iVar3 = iVar6;
	if ((double)local_8 < fVar10)
	{
		lVar11 = (int64_t)((((double)local_c - fVar10) * (double)iStack_14) /
		                   ((double)local_c - (double)local_8));
		iVar3 = (int)lVar11;
	}
	pbVar1 = (uint8_t*)((int)local_4 + 0x3c);
	a3 = *(float*)(iVar5 + 0xc) * 0.003125;
	local_8 = *(float*)(iVar5 + 0x10) * 0.003125;
	local_4 = *(float*)(iVar5 + 0x14) * 0.003125;
	iVar5 = (int)((uint32_t)*pbVar1 * iVar3) / 0xff;
	local_c = a3;
	if (a1[1] == 0)
	{
		D2SOUND_10057((int)&iStack_14, (int)&local_c, (int)a3, (int)local_8, (int)local_4);
		D2SOUND_10016(*a1, (int)local_c);
		iVar5 = (iStack_14 * iVar5) / 0xff;
	}
	iVar3 = iVar5;
	if ((*(uint8_t*)(a1 + 1) & 2) != 0)
	{
		D2SOUND_10017(*a1, (int)local_4, (int)a3, (int)local_8, (int)local_4);
		iVar3 = extraout_EDX;
	}
	iVar2 = local_10;
	D2SOUND_10021(*a1, iVar3, *(int*)(local_10 + 0x20));
	D2SOUND_10014(*a1, iVar5);
	a1[3] = *(int*)(iVar2 + 0xc);
	a1[4] = *(int*)(iVar2 + 0x10);
	iVar5 = *(int*)(iVar2 + 0x14);
	a1[6] = iVar6;
	a1[5] = iVar5;
	a1[7] = *(int*)(iVar2 + 0x20);
}

//D2Client.0x6FB52CF0
int __cdecl sub_6FB52CF0()
{
	return dword_6FBBD46C;
}

//D2Client.0x6FB52D00
int __cdecl sub_6FB52D00()
{
	return dword_6FBBD46C;
}

//D2Client.0x6FB52D10
void __cdecl sub_6FB52D10()
{
	int iVar1;
	int* piVar2;

	piVar2 = (int*)(&dword_6FBBD270);
	do
	{
		if (*piVar2 != 0)
		{
			iVar1 = sub_6FB53C00(*(int*)(*piVar2 + 4));
			if (*(char*)(iVar1 + 0x3e) == '\0')
			{
				iVar1 = D2SOUND_10013(piVar2[-2]);
				if (iVar1 == 0)
				{
					iVar1 = D2SOUND_10023(piVar2[-2]);
					if (iVar1 == 0)
					{
						if (*piVar2 != 0)
						{
							*(uint32_t*)(*piVar2 + 0x30) = 2;
							*(uint32_t*)(*piVar2 + 0x2c) = 0;
							goto LAB_6fb52d85;
						}
					}
					else
					{
						if (piVar2[-2] != 0)
						{
							if (*piVar2 != 0)
							{
								iVar1 = D2SOUND_10018();
								*(int*)(*piVar2 + 0x41) = iVar1;
							}
							D2SOUND_10012(piVar2[-2]);
						}
						if (*piVar2 != 0)
						{
							*(uint32_t*)(*piVar2 + 0x30) = 2;
							*(uint32_t*)(*piVar2 + 0x2c) = 0;
						LAB_6fb52d85:
							*piVar2 = 0;
						}
					}
				}
			}
		}
		piVar2 = piVar2 + 8;
		if ((int)&tbl_6FBBD46F < (int)piVar2)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB52DA0
int32_t __cdecl sub_6FB52DA0()
{
	return D2SOUND_10018();
}

//D2Client.0x6FB52DB0
void __cdecl sub_6FB52DB0()
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	int* piVar4;
	uint32_t* puVar5;

	iVar1 = D2SOUND_10044();
	if (iVar1 == 1)
	{
		iVar2 = D2SOUND_10003();
	joined_r0x6fb52e97:
		if (iVar2 == 0)
			goto LAB_6fb52dd2;
	}
	else if (iVar1 == 2)
	{
		iVar2 = D2SOUND_10004();
		goto joined_r0x6fb52e97;
	}
	if (dword_6FBBD46C != 0)
	{
		iVar2 = D2SOUND_10002();
		if (iVar2 != 0)
		{
			D2SOUND_10027(0);
			piVar4 = (int*)(&dword_6FBBD268);
			do
			{
				if (*piVar4 != 0)
				{
					if (piVar4[2] != 0)
					{
						iVar2 = D2SOUND_10018();
						*(int*)(piVar4[2] + 0x41) = iVar2;
					}
					D2SOUND_10012(*piVar4);
				}
				sub_6FB528D0((int)piVar4);
				piVar4 = piVar4 + 8;
			} while ((int)piVar4 < (int)&dword_6FBBD468);
			D2SOUND_10027(0xff);
		}
		piVar4 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar4);
			*piVar4 = 0;
			piVar4 = piVar4 + 8;
		} while ((int)piVar4 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
	iVar2 = sub_6FB53030(iVar1);
	if (iVar2 != 0)
	{
		iVar2 = D2SOUND_10044();
		if (iVar2 != iVar1)
		{
			D2SOUND_10045(iVar1);
			return;
		}
		return;
	}
LAB_6fb52dd2:
	if (dword_6FBBD46C != 0)
	{
		iVar1 = D2SOUND_10002();
		if (iVar1 != 0)
		{
			D2SOUND_10027(0);
			piVar4 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar4[-2] != 0)
				{
					if (*piVar4 != 0)
					{
						iVar1 = D2SOUND_10018();
						*(int*)(*piVar4 + 0x41) = iVar1;
					}
					D2SOUND_10012(piVar4[-2]);
				}
				if (*piVar4 != 0)
				{
					*(uint32_t*)(*piVar4 + 0x30) = 2;
					*(uint32_t*)(*piVar4 + 0x2c) = 0;
					*piVar4 = 0;
				}
				piVar4 = piVar4 + 8;
			} while ((int)piVar4 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar4 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar4);
			*piVar4 = 0;
			piVar4 = piVar4 + 8;
		} while ((int)piVar4 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
	iVar1 = D2SOUND_10002();
	if (iVar1 != 0)
	{
		D2_ASSERT(!dword_6FBBD46C);
		puVar5 = &dword_6FBBD26C;
		do
		{
			*puVar5 = 0;
			*puVar5 = (uint32_t)((int)puVar5 < (int)&tbl_6FBBD2EC);
			uVar3 = D2SOUND_10007((uint32_t)((int)puVar5 < (int)&tbl_6FBBD2EC));
			puVar5[-1] = uVar3;
			if (uVar3 == 0)
			{
				sub_6FB52F90();
				return;
			}
			puVar5 = puVar5 + 8;
		} while ((int)puVar5 < (int)&dword_6FBBD46C);
		sub_6FB523C0(0);
		dword_6FBBD46C = 1;
		iVar1 = D2SOUND_10044();
		if (iVar1 != 0)
		{
			D2SOUND_10045(0);
			return;
		}
	}
}

//D2Client.0x6FB52F90
void __cdecl sub_6FB52F90()
{
	int iVar1;
	int* piVar2;

	if (dword_6FBBD46C != 0)
	{
		iVar1 = D2SOUND_10002();
		if (iVar1 != 0)
		{
			D2SOUND_10027(0);
			piVar2 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar2[-2] != 0)
				{
					if (*piVar2 != 0)
					{
						iVar1 = D2SOUND_10018();
						*(int*)(*piVar2 + 0x41) = iVar1;
					}
					D2SOUND_10012(piVar2[-2]);
				}
				if (*piVar2 != 0)
				{
					*(uint32_t*)(*piVar2 + 0x30) = 2;
					*(uint32_t*)(*piVar2 + 0x2c) = 0;
					*piVar2 = 0;
				}
				piVar2 = piVar2 + 8;
			} while ((int)piVar2 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar2 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar2);
			*piVar2 = 0;
			piVar2 = piVar2 + 8;
		} while ((int)piVar2 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
}

//D2Client.0x6FB53030
uint32_t __fastcall sub_6FB53030(int a1)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t* puVar3;
	int* piVar4;

	iVar1 = D2SOUND_10002();
	if (iVar1 == 0)
	{
		return 0;
	}
	D2_ASSERT(!dword_6FBBD46C);
	puVar3 = &dword_6FBBD26C;
	while (true)
	{
		*puVar3 = 0;
		if ((int)puVar3 < (int)&tbl_6FBBD2EC)
		{
			*puVar3 = 1;
		}
		else if (a1 == 1)
		{
			*puVar3 = 2;
		}
		else
		{
			*puVar3 = (a1 != 2) - 1 & 6;
		}
		uVar2 = D2SOUND_10007(*puVar3);
		puVar3[-1] = uVar2;
		if (uVar2 == 0)
			break;
		puVar3 = puVar3 + 8;
		if ((int)&tbl_6FBBD46B < (int)puVar3)
		{
			sub_6FB523C0(0);
			dword_6FBBD46C = 1;
			return 1;
		}
	}
	if (dword_6FBBD46C != 0)
	{
		iVar1 = D2SOUND_10002();
		if (iVar1 != 0)
		{
			D2SOUND_10027(0);
			piVar4 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar4[-2] != 0)
				{
					if (*piVar4 != 0)
					{
						iVar1 = D2SOUND_10018();
						*(int*)(*piVar4 + 0x41) = iVar1;
					}
					D2SOUND_10012(piVar4[-2]);
				}
				if (*piVar4 != 0)
				{
					*(uint32_t*)(*piVar4 + 0x30) = 2;
					*(uint32_t*)(*piVar4 + 0x2c) = 0;
					*piVar4 = 0;
				}
				piVar4 = piVar4 + 8;
			} while ((int)piVar4 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar4 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar4);
			*piVar4 = 0;
			piVar4 = piVar4 + 8;
		} while ((int)piVar4 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
	return 0;
}

//D2Client.0x6FB53170
void __cdecl sub_6FB53170()
{
	int iVar1;
	int* piVar2;

	if (dword_6FBBD46C != 0)
	{
		iVar1 = D2SOUND_10002();
		if (iVar1 != 0)
		{
			D2SOUND_10027(0);
			piVar2 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar2[-2] != 0)
				{
					if (*piVar2 != 0)
					{
						iVar1 = D2SOUND_10018();
						*(int*)(*piVar2 + 0x41) = iVar1;
					}
					D2SOUND_10012(piVar2[-2]);
				}
				if (*piVar2 != 0)
				{
					*(uint32_t*)(*piVar2 + 0x30) = 2;
					*(uint32_t*)(*piVar2 + 0x2c) = 0;
					*piVar2 = 0;
				}
				piVar2 = piVar2 + 8;
			} while ((int)piVar2 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar2 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar2);
			*piVar2 = 0;
			piVar2 = piVar2 + 8;
		} while ((int)piVar2 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
}

//D2Client.0x6FB53210
uint32_t __cdecl sub_6FB53210()
{
	int iVar1;

	if (dword_6FBBD46C == 0)
	{
		return 0;
	}
	iVar1 = D2SOUND_10003();
	return iVar1;
}

//D2Client.0x6FB53230
uint32_t __cdecl sub_6FB53230()
{
	int iVar1;

	if (dword_6FBBD46C == 0)
	{
		return 0;
	}
	iVar1 = D2SOUND_10004();
	return iVar1;
}

//D2Client.0x6FB53250
uint32_t __cdecl sub_6FB53250()
{
	int iVar1;

	if (dword_6FBBD46C == 0)
	{
		return 0;
	}
	iVar1 = D2SOUND_10044();
	if ((iVar1 != 1) && (iVar1 != 2))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FB53280
bool __cdecl sub_6FB53280()
{
	int iVar1;

	if (dword_6FBBD46C == 0)
	{
		return false;
	}
	iVar1 = D2SOUND_10044();
	return iVar1 == 2;
}

//D2Client.0x6FB532A0
uint32_t __cdecl sub_6FB532A0()
{
	int a1;
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int* piVar5;
	uint32_t* puVar6;

	uVar4 = 0;
	if ((dword_6FBBD46C == 0) || (dword_6FBBD468 != 0))
	{
		return 0;
	}
	InterlockedIncrement(&dword_6FBBD468);
	a1 = D2SOUND_10044();
	uVar3 = (uint32_t)(a1 == 0);
	D2SOUND_10029(0xb4);
	if (uVar3 == 1)
	{
		iVar1 = D2SOUND_10003();
		if (iVar1 != 0)
			goto LAB_6fb53313;
	}
	else
	{
		if (uVar3 == 2)
		{
			iVar1 = D2SOUND_10004();
			if (iVar1 == 0)
				goto LAB_6fb532f2;
		}
	LAB_6fb53313:
		if (dword_6FBBD46C != 0)
		{
			iVar1 = D2SOUND_10002();
			if (iVar1 != 0)
			{
				D2SOUND_10027(0);
				piVar5 = (int*)(&dword_6FBBD268);
				do
				{
					if (*piVar5 != 0)
					{
						if (piVar5[2] != 0)
						{
							iVar1 = D2SOUND_10018();
							*(int*)(piVar5[2] + 0x41) = iVar1;
						}
						D2SOUND_10012(*piVar5);
					}
					sub_6FB528D0((int)piVar5);
					piVar5 = piVar5 + 8;
				} while ((int)piVar5 < (int)&dword_6FBBD468);
				D2SOUND_10027(0xff);
			}
			piVar5 = (int*)(&dword_6FBBD268);
			do
			{
				D2SOUND_10008(*piVar5);
				*piVar5 = 0;
				piVar5 = piVar5 + 8;
			} while ((int)piVar5 < (int)&dword_6FBBD468);
			dword_6FBBD46C = 0;
		}
		iVar1 = sub_6FB53030(uVar3);
		if (iVar1 != 0)
		{
			uVar2 = D2SOUND_10044();
			if (uVar2 != uVar3)
			{
				D2SOUND_10045(uVar3);
			}
			uVar4 = 1;
			goto LAB_6fb534e4;
		}
	}
LAB_6fb532f2:
	if (a1 == 1)
	{
		iVar1 = D2SOUND_10003();
	LAB_6fb533bb:
		if (iVar1 == 0)
			goto LAB_6fb534e4;
	}
	else if (a1 == 2)
	{
		iVar1 = D2SOUND_10004();
		goto LAB_6fb533bb;
	}
	if (dword_6FBBD46C != 0)
	{
		iVar1 = D2SOUND_10002();
		if (iVar1 != 0)
		{
			D2SOUND_10027(0);
			piVar5 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar5[-2] != 0)
				{
					if (*piVar5 != 0)
					{
						iVar1 = D2SOUND_10018();
						*(int*)(*piVar5 + 0x41) = iVar1;
					}
					D2SOUND_10012(piVar5[-2]);
				}
				if (*piVar5 != 0)
				{
					*(uint32_t*)(*piVar5 + 0x30) = 2;
					*(uint32_t*)(*piVar5 + 0x2c) = 0;
					*piVar5 = 0;
				}
				piVar5 = piVar5 + 8;
			} while ((int)piVar5 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar5 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar5);
			*piVar5 = 0;
			piVar5 = piVar5 + 8;
		} while ((int)piVar5 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
	iVar1 = D2SOUND_10002();
	if (iVar1 != 0)
	{
		D2_ASSERT(!dword_6FBBD46C);
		puVar6 = &dword_6FBBD26C;
		do
		{
			*puVar6 = 0;
			if ((int)puVar6 < (int)&tbl_6FBBD2EC)
			{
				*puVar6 = 1;
			}
			else if (a1 == 1)
			{
				*puVar6 = 2;
			}
			else
			{
				*puVar6 = (a1 != 2) - 1 & 6;
			}
			uVar3 = D2SOUND_10007(*puVar6);
			puVar6[-1] = uVar3;
			if (uVar3 == 0)
			{
				sub_6FB52F90();
				goto LAB_6fb534e4;
			}
			puVar6 = puVar6 + 8;
		} while ((int)puVar6 < (int)&dword_6FBBD46C);
		sub_6FB523C0(0);
		dword_6FBBD46C = 1;
		iVar1 = D2SOUND_10044();
		if (iVar1 != a1)
		{
			D2SOUND_10045(a1);
		}
	}
LAB_6fb534e4:
	D2SOUND_10027(0xff);
	InterlockedDecrement(&dword_6FBBD468);
	return uVar4;
}

//D2Client.0x6FB53510
uint32_t __cdecl sub_6FB53510()
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int* piVar6;
	uint32_t* puVar7;

	uVar5 = 0;
	if ((dword_6FBBD46C == 0) || (dword_6FBBD468 != 0))
	{
		return 0;
	}
	InterlockedIncrement(&dword_6FBBD468);
	iVar1 = D2SOUND_10044();
	iVar2 = (iVar1 != 2) + 1;
	D2SOUND_10029(0xb4);
	if (iVar2 == 1)
	{
		iVar3 = D2SOUND_10003();
		if (iVar3 != 0)
			goto LAB_6fb53585;
	}
	else
	{
		if (iVar2 == 2)
		{
			iVar3 = D2SOUND_10004();
			if (iVar3 == 0)
				goto LAB_6fb53564;
		}
	LAB_6fb53585:
		if (dword_6FBBD46C != 0)
		{
			iVar3 = D2SOUND_10002();
			if (iVar3 != 0)
			{
				D2SOUND_10027(0);
				piVar6 = (int*)(&dword_6FBBD268);
				do
				{
					if (*piVar6 != 0)
					{
						if (piVar6[2] != 0)
						{
							iVar3 = D2SOUND_10018();
							*(int*)(piVar6[2] + 0x41) = iVar3;
						}
						D2SOUND_10012(*piVar6);
					}
					sub_6FB528D0((int)piVar6);
					piVar6 = piVar6 + 8;
				} while ((int)piVar6 < (int)&dword_6FBBD468);
				D2SOUND_10027(0xff);
			}
			piVar6 = (int*)(&dword_6FBBD268);
			do
			{
				D2SOUND_10008(*piVar6);
				*piVar6 = 0;
				piVar6 = piVar6 + 8;
			} while ((int)piVar6 < (int)&dword_6FBBD468);
			dword_6FBBD46C = 0;
		}
		iVar3 = sub_6FB53030(iVar2);
		if (iVar3 != 0)
		{
			iVar1 = D2SOUND_10044();
			if (iVar1 != iVar2)
			{
				D2SOUND_10045(iVar2);
			}
			uVar5 = 1;
			goto LAB_6fb53756;
		}
	}
LAB_6fb53564:
	if (iVar1 == 1)
	{
		iVar2 = D2SOUND_10003();
	LAB_6fb5362d:
		if (iVar2 == 0)
			goto LAB_6fb53756;
	}
	else if (iVar1 == 2)
	{
		iVar2 = D2SOUND_10004();
		goto LAB_6fb5362d;
	}
	if (dword_6FBBD46C != 0)
	{
		iVar2 = D2SOUND_10002();
		if (iVar2 != 0)
		{
			D2SOUND_10027(0);
			piVar6 = (int*)(&dword_6FBBD270);
			do
			{
				if (piVar6[-2] != 0)
				{
					if (*piVar6 != 0)
					{
						iVar2 = D2SOUND_10018();
						*(int*)(*piVar6 + 0x41) = iVar2;
					}
					D2SOUND_10012(piVar6[-2]);
				}
				if (*piVar6 != 0)
				{
					*(uint32_t*)(*piVar6 + 0x30) = 2;
					*(uint32_t*)(*piVar6 + 0x2c) = 0;
					*piVar6 = 0;
				}
				piVar6 = piVar6 + 8;
			} while ((int)piVar6 < (int)&dword_6FBBD470);
			D2SOUND_10027(0xff);
		}
		piVar6 = (int*)(&dword_6FBBD268);
		do
		{
			D2SOUND_10008(*piVar6);
			*piVar6 = 0;
			piVar6 = piVar6 + 8;
		} while ((int)piVar6 < (int)&dword_6FBBD468);
		dword_6FBBD46C = 0;
	}
	iVar2 = D2SOUND_10002();
	if (iVar2 != 0)
	{
		D2_ASSERT(!dword_6FBBD46C);
		puVar7 = &dword_6FBBD26C;
		do
		{
			*puVar7 = 0;
			if ((int)puVar7 < (int)&tbl_6FBBD2EC)
			{
				*puVar7 = 1;
			}
			else if (iVar1 == 1)
			{
				*puVar7 = 2;
			}
			else
			{
				*puVar7 = (iVar1 != 2) - 1 & 6;
			}
			uVar4 = D2SOUND_10007(*puVar7);
			puVar7[-1] = uVar4;
			if (uVar4 == 0)
			{
				sub_6FB52F90();
				goto LAB_6fb53756;
			}
			puVar7 = puVar7 + 8;
		} while ((int)puVar7 < (int)&dword_6FBBD46C);
		sub_6FB523C0(0);
		dword_6FBBD46C = 1;
		iVar2 = D2SOUND_10044();
		if (iVar2 != iVar1)
		{
			D2SOUND_10045(iVar1);
		}
	}
LAB_6fb53756:
	D2SOUND_10027(0xff);
	InterlockedDecrement(&dword_6FBBD468);
	return uVar5;
}

//D2Client.0x6FB53780
int* __fastcall sub_6FB53780(int a1)
{
	int iVar1;
	int* piVar2;
	int* piVar3;

	if (dword_6FBBD46C == 0)
	{
		return nullptr;
	}
	piVar3 = nullptr;
	piVar2 = (int*)(&dword_6FBBD270);
	do
	{
		iVar1 = D2SOUND_10013(piVar2[-2]);
		if ((((iVar1 != 0) && (iVar1 = *piVar2, iVar1 != 0)) && (*(int*)(iVar1 + 4) == a1)) &&
		    ((piVar3 == nullptr || (*(uint32_t*)(iVar1 + 0x34) < *(uint32_t*)(piVar3[2] + 0x34)))))
		{
			piVar3 = piVar2 + -2;
		}
		piVar2 = piVar2 + 8;
	} while ((int)piVar2 < (int)&dword_6FBBD470);
	return piVar3;
}

//D2Client.0x6FB53790
// TODO: decompilation needs review (unaff_)
int* __cdecl sub_6FB53790()
{
	int iVar1;
	int unaff_EBP;
	int* piVar2;
	int* piVar3;

	piVar3 = nullptr;
	piVar2 = (int*)(&dword_6FBBD270);
	do
	{
		iVar1 = D2SOUND_10013(piVar2[-2]);
		if ((((iVar1 != 0) && (iVar1 = *piVar2, iVar1 != 0)) && (*(int*)(iVar1 + 4) == unaff_EBP)) &&
		    ((piVar3 == nullptr || (*(uint32_t*)(iVar1 + 0x34) < *(uint32_t*)(piVar3[2] + 0x34)))))
		{
			piVar3 = piVar2 + -2;
		}
		piVar2 = piVar2 + 8;
	} while ((int)piVar2 < (int)&dword_6FBBD470);
	return piVar3;
}

//D2Client.0x6FB537E0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB537E0(int* a1)
{
	uint32_t extraout_EAX;

	if ((a1 != nullptr) && (*a1 != 0))
	{
		D2SOUND_10064();
		return extraout_EAX;
	}
	return 0;
}

//D2Client.0x6FB53800
void __cdecl sub_6FB53800()
{
	dword_6FBBD474 = 0;
	dword_6FBBD488 = 0;
	dword_6FBBD48C = 0;
	dword_6FBBD490 = 0;
	if (dword_6FBBD478 != 0)
	{
		sub_6FB556A0(dword_6FBBD478);
		dword_6FBBD478 = 0;
	}
	dword_6FBBD480 = 0;
	if (dword_6FBBD47C != 0)
	{
		sub_6FB556A0(dword_6FBBD47C);
		dword_6FBBD47C = 0;
	}
	dword_6FBBD484 = 0;
}

//D2Client.0x6FB53860
// TODO: decompilation needs review (extraout, in_reg)
void __cdecl sub_6FB53860()
{
	uint8_t uVar1;
	bool bVar2;
	int iVar3;
	int iVar4;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	int iVar5;
	float fVar6;
	int in_ECX;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	double fVar10;
	int64_t lVar11;
	int local_10;

	iVar3 = sub_6FB52CF0();
	if (iVar3 == 0)
	{
		return;
	}
	iVar3 = sub_6FB53CD0();
	bVar2 = false;
	if (iVar3 == 0)
	{
		return;
	}
	iVar9 = 0;
	local_10 = 0;
	iVar4 = ENVIRONMENT_GetCycleIndexFromAct(ghAct);
	if ((iVar4 < 1) || (3 < iVar4))
	{
		bVar2 = true;
	}
	uVar1 = sub_6FB53CF0();
	iVar4 = sub_6FB53D30(D2C_ZEXT(uVar1));
	if (iVar4 != 0)
	{
		if (bVar2)
		{
			local_10 = *(int*)(iVar4 + 0x10);
			iVar9 = *(int*)(iVar4 + 8);
		}
		else
		{
			local_10 = *(int*)(iVar4 + 0xc);
			iVar9 = *(int*)(iVar4 + 4);
		}
	}
	bVar2 = sub_6FAA8870();
	uVar7 = -(uint32_t)(D2C_ZEXT(bVar2) != 0) & 0x40;
	bVar2 = sub_6FAA8870();
	lVar11 = 0;
	if (D2C_ZEXT(bVar2) != 0)
	{
		fVar10 = sub_6FAA88B0();
		lVar11 = 0;
		if (fVar10 != (double)0.0)
		{
			bVar2 = sub_6FAA8870();
			if (D2C_ZEXT(bVar2) == 0)
			{
				fVar10 = (double)0.0;
			}
			else
			{
				fVar10 = sub_6FAA88B0();
			}
			lVar11 = (int64_t)(fVar10 * (double)255.0);
		}
	}
	iVar8 = (int)lVar11;
	iVar5 = dword_6FBBD480;
	if (iVar9 != dword_6FBBD480)
	{
		bVar2 = false;
		if ((iVar9 == *(int*)(iVar4 + 4)) && (dword_6FBBD480 == *(int*)(iVar4 + 8)))
		{
			bVar2 = true;
		}
		if ((iVar9 == *(int*)(iVar4 + 8)) && (dword_6FBBD480 == *(int*)(iVar4 + 4)))
		{
			bVar2 = true;
		LAB_6fb53962:
			sub_6FB55BF0(dword_6FBBD478, 0, 0, 0xfa);
		}
		else
		{
			if (bVar2)
				goto LAB_6fb53962;
			sub_6FB55E60(iVar9, uVar7);
			sub_6FB55EE0(local_10, 0);
		}
		iVar5 = dword_6FBBD480;
		if (iVar9 != dword_6FBBD480)
		{
			if (iVar9 == 0)
			{
				dword_6FBBD478 = 0;
				dword_6FBBD480 = 0;
				iVar5 = dword_6FBBD480;
			}
			else
			{
				dword_6FBBD478 = sub_6FB55820(iVar9, nullptr, 0.0, 0.0, 0);
				iVar5 = iVar9;
				if (bVar2)
				{
					sub_6FB55BC0(dword_6FBBD478, 0);
					sub_6FB55BF0(dword_6FBBD478, 0xff, 0, 0xfa);
				}
			}
		}
	}
	dword_6FBBD480 = iVar5;
	if (uVar7 == 0)
	{
		sub_6FB556A0(dword_6FBBD47C);
		dword_6FBBD47C = 0;
		dword_6FBBD484 = 0;
		uVar7 = dword_6FBBD484;
		goto LAB_6fb53a89;
	}
	if (iVar8 == 0)
	{
	LAB_6fb53a1f:
		if (dword_6FBBD47C == 0)
			goto LAB_6fb53a89;
	}
	else if (dword_6FBBD47C == 0)
	{
		dword_6FBBD47C = sub_6FB55820(dword_6FBBD484, nullptr, 0.0, 0.0, 0);
		if (dword_6FBBD47C == 0)
			goto LAB_6fb53a89;
		sub_6FB55BC0(dword_6FBBD47C, iVar8);
		goto LAB_6fb53a1f;
	}
	iVar9 = sub_6FB55B90(dword_6FBBD47C);
	if (iVar9 < iVar8)
	{
		iVar5 = iVar9 + 6;
		if (iVar8 < iVar9 + 6)
		{
		LAB_6fb53a42:
			iVar5 = iVar8;
		}
	}
	else
	{
		iVar5 = iVar9 + -6;
		if (iVar5 < iVar8)
			goto LAB_6fb53a42;
	}
	if (iVar5 == 0)
	{
		sub_6FB556A0(dword_6FBBD47C);
		dword_6FBBD47C = 0;
	}
	else
	{
		sub_6FB55BC0(dword_6FBBD47C, iVar5);
	}
LAB_6fb53a89:
	dword_6FBBD484 = uVar7;
	sub_6FB523C0(D2C_ZEXT(uVar1));
	if (local_10 != 0)
	{
		if (local_10 != dword_6FBBD488)
		{
			iVar9 = sub_6FB57220(*(uint32_t*)(iVar4 + 0x14) / 3);
			dword_6FBBD48C = iVar9 + *(int*)(iVar4 + 0x14);
			uVar7 = sub_6FB57150(dword_6FBBD48C);
			dword_6FBBD488 = local_10;
			dword_6FBBD490 = in_ECX - uVar7;
		}
		if ((dword_6FBBD48C <= (uint32_t)(in_ECX - dword_6FBBD490)) &&
		    (iVar9 = sub_6FB55820(dword_6FBBD488, nullptr, 0.0, 0.0, 0), iVar9 != 0))
		{
			uVar7 = sub_6FB57150(2);
			iVar5 = sub_6FB571B0(0x1c2, 0x2ee);
			fVar6 = (float)sub_6FB57220(100);
			sub_6FB55710(iVar9, ((-(uint32_t)(uVar7 != 0) & 2) - 1) * iVar5, fVar6, 0.0);
			dword_6FBBD490 = in_ECX;
			iVar9 = sub_6FB57220(*(uint32_t*)(iVar4 + 0x14) / 3);
			dword_6FBBD48C = iVar9 + *(int*)(iVar4 + 0x14);
		}
	}
	iVar9 = dword_6FBBD474;
	if (iVar3 != dword_6FBBD474)
	{
		iVar9 = *(int*)(iVar4 + 0x1c);
		iVar4 = *(int*)(iVar4 + 0x20);
		iVar5 = 0xaa0;
		do
		{
			sub_6FB54A90(iVar5);
			iVar5 = iVar5 + 4;
		} while (iVar5 < 0xb3d);
		if (iVar9 != 0)
		{
			iVar9 = iVar9 * 4 + 0xa9c;
			iVar5 = 3;
			do
			{
				sub_6FB549C0(iVar9, 1);
				sub_6FB549C0(iVar9 + 0x18, 1);
				iVar9 = iVar9 + 0x30;
				iVar5 = iVar5 + -1;
			} while (iVar5 != 0);
		}
		iVar9 = iVar3;
		if (iVar4 != 0)
		{
			iVar3 = iVar4 * 4 + 0xa9c;
			iVar4 = 3;
			do
			{
				sub_6FB549C0(iVar3, 1);
				sub_6FB549C0(iVar3 + 0x18, 1);
				iVar3 = iVar3 + 0x30;
				iVar4 = iVar4 + -1;
			} while (iVar4 != 0);
		}
	}
	dword_6FBBD474 = iVar9;
}

//D2Client.0x6FB53C00
int __fastcall sub_6FB53C00(int a1)
{
	if (((dword_6FBBD498 != 0) && (-1 < a1)) && (a1 < dword_6FBBD49C))
	{
		return dword_6FBBD498 + a1 * 0x8e;
	}
	return 0;
}

//D2Client.0x6FB53C30
uint32_t __fastcall sub_6FB53C30(int a1)
{
	if (dword_6FBBD498 == 0)
	{
		return 0;
	}
	if ((-1 < a1) && (a1 < dword_6FBBD49C))
	{
		return *(uint32_t*)(dword_6FBBD498 + a1 * 0x8e + 0x60);
	}
	return (*(uint32_t*)0x60);
}

//D2Client.0x6FB53C60
uint32_t __fastcall sub_6FB53C60(int a1)
{
	int iVar1;

	if (dword_6FBBD498 == 0)
	{
		return 0;
	}
	if ((-1 < a1) && (a1 < dword_6FBBD49C))
	{
		iVar1 = dword_6FBBD498 + a1 * 0x8e;
		return CONCAT31((int32_t)((uint32_t)iVar1 >> 8), *(uint8_t*)(iVar1 + 0x3d));
	}
	return (uint32_t)(*(uint8_t*)0x3D);
}

//D2Client.0x6FB53C90
uint8_t __fastcall sub_6FB53C90(int a1)
{
	if (dword_6FBBD498 == 0)
	{
		return 0;
	}
	if ((-1 < a1) && (a1 < dword_6FBBD49C))
	{
		return *(uint8_t*)(dword_6FBBD498 + 0x3e + a1 * 0x8e);
	}
	return (*(uint32_t*)0x3E);
}

//D2Client.0x6FB53CD0
int32_t __cdecl sub_6FB53CD0()
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;

	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		return 0;
	}
	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom == nullptr)
	{
		return 0;
	}
	return DUNGEON_GetLevelIdFromRoom(pRoom);
}

//D2Client.0x6FB53CF0
uint8_t __cdecl sub_6FB53CF0()
{
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int nLevelId;
	D2LevelsTxt* pDVar1;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
			if (nLevelId != 0)
			{
				pDVar1 = DATATBLS_GetLevelsTxtRecord(nLevelId);
				return (char)pDVar1->dwSoundEnv;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB53D30
int __fastcall sub_6FB53D30(int a1)
{
	if (((ptr_6FBBD4A0 != nullptr) && (-1 < a1)) && (a1 < dword_6FBBD4A4))
	{
		return (int)(void*)((int)ptr_6FBBD4A0 + a1 * 0x58);
	}
	return 0;
}

//D2Client.0x6FB53D60
uint32_t __cdecl sub_6FB53D60()
{
	return dword_6FBBD4A8;
}

//D2Client.0x6FB53D70
uint32_t __cdecl sub_6FB53D70()
{
	return dword_6FBBD4AC;
}

//D2Client.0x6FB53D80
uint32_t* __cdecl sub_6FB53D80()
{
	return gpuint32_t_6FBBD494;
}

//D2Client.0x6FB53D90
void __cdecl sub_6FB53D90()
{
	int iVar1;

	iVar1 = D2SOUND_10002();
	if (iVar1 != 0)
	{
		sub_6FB53DE0();
		sub_6FB52DB0();
		sub_6FB56AA0();
		sub_6FB56D40();
		sub_6FB4F4A0();
		D2SOUND_10027(0xff);
		dword_6FBBD4B4 = 0;
		dword_6FBBD4B8 = 0;
		byte_6FBBD4BC = 0;
		dword_6FBBD4C0 = 0;
	}
}

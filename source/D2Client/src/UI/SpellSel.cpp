#include "UI/SpellSel.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "UI/Inv.h"
#include "UI/SkillDesc.h"
#include "UI/SkillsTree.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB6FBAC
uint8_t* gpuint8_t_6FB6FBAC = (uint8_t*)sub_6FB1A340;
//D2Client.0x6FB6FBE0
uint8_t* gpuint8_t_6FB6FBE0 = (uint8_t*)sub_6FB1A6D0;
//D2Client.0x6FBB9858
uint32_t dword_6FBB9858;
//D2Client.0x6FBB9988
uint32_t dword_6FBB9988;
//D2Client.0x6FBB9A78
uint32_t dword_6FBB9A78;
//D2Client.0x6FBB9C5C
uint32_t dword_6FBB9C5C;
//D2Client.0x6FBB9C60
uint8_t byte_6FBB9C60;
//D2Client.0x6FBB9C64
uint8_t byte_6FBB9C64;
//D2Client.0x6FBB9C68
uint8_t byte_6FBB9C68;
//D2Client.0x6FBB9C6C
uint8_t byte_6FBB9C6C;
//D2Client.0x6FBB9CE8
int32_t dword_6FBB9CE8;
//D2Client.0x6FBB9CF0
uint32_t dword_6FBB9CF0;
//D2Client.0x6FBB9D30
uint32_t dword_6FBB9D30;

//D2Client.0x6FB19720
void __fastcall sub_6FB19720(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5)
{
	short sVar1;
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	char* pcVar10;
	int local_130;
	int local_12c;
	int local_128;
	int iStack_124;
	int iStack_118;
	int local_114;
	uint32_t uStack_110;
	int local_10c;
	D2SkillStrc* pDStack_108;
	int local_104;
	char local_100[256];

	local_130 = gnScreenHeight + -0x56;
	local_104 = (-(uint32_t)(a3 != 0) & 0x60) - 0x30;
	local_114 = 0;
	local_128 = 0;
	pcVar10 = local_100;
	for (iVar9 = 0x40; local_10c = a2, iVar9 != 0; iVar9 = iVar9 + -1)
	{
		pcVar10[0] = '\0';
		pcVar10[1] = '\0';
		pcVar10[2] = '\0';
		pcVar10[3] = '\0';
		pcVar10 = pcVar10 + 4;
	}
	do
	{
		local_12c = local_10c;
		pSkill = UNITS_GetStartSkill(pUnit);
		if (pSkill != nullptr)
		{
			iStack_124 = local_130 + -0x30;
			do
			{
				iVar9 = 0;
				pDStack_108 = SKILLS_GetNextSkill(pSkill);
				pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
				if (((((pDVar2 != nullptr) && (iVar3 = (int)pDVar2->nSkillId, -1 < iVar3)) &&
				         (iVar5 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar5 + 0xba0))) &&
				        (((iVar3 = *(int*)(iVar5 + 0xb98) + iVar3 * 0x23c, iVar3 != 0 &&
				                                                               (iVar3 = (int)*(short*)(iVar3 + 0x194), -1 < iVar3)) &&
				            ((iVar3 < *(int*)(iVar5 + 0xb94) &&
				                (iVar3 = iVar3 * 0x120 + *(int*)(iVar5 + 0xb8c), iVar3 != 0)))))) &&
				    (((a3 == 0 ||
				          (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & *(uint8_t*)((int)pDVar2->dwFlags + 3)) != 0)) &&
				        ((((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & (uint8_t)pDVar2->dwFlags[0]) == 0 &&
				            (uVar4 = SKILLS_GetFlags(pSkill), (uVar4 & 8) == 0))))))
				{
					uStack_110 = 0xffffffff;
					iStack_118 = 0;
					iVar5 = SKILLS_GetSkillInfo(pSkill, &uStack_110, nullptr, nullptr, &iStack_118);
					if ((((a3 == 0) && (iVar5 == 0)) && (iVar9 = SKILLS_GetQuantity(pSkill), 0 < iVar9)) && (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & (uint8_t)pDVar2->dwFlags[1]) != 0))
					{
						iVar5 = 1;
					}
					if (local_128 < 4)
					{
						if ((iVar5 == 0) && (local_128 == *(char*)(iVar3 + 5)))
						{
						LAB_6fb198ce:
							iVar6 = sub_6FB4DA80(pUnit, pSkill);
							iVar5 = iStack_118;
							if (iVar6 == 0)
							{
								iVar6 = 0;
							}
							else
							{
								iVar6 = (-(uint32_t)(iVar6 != 6) & 0xfffffffd) + 4;
							}
							if (local_114 < local_128)
							{
								local_130 = local_130 + -0x30;
								local_114 = local_128;
								iStack_124 = iStack_124 + -0x30;
							}
							if ((*(uint8_t*)(iVar3 + 6) != 0) && (uVar4 = (uint32_t) * (uint8_t*)(iVar3 + 6), uVar4 < 0x100))
							{
								if (local_100[uVar4] != '\0')
									goto switchD_6fb19ae7_default;
								local_100[uVar4] = '\x01';
							}
							if (a4 == 0)
							{
								if (a5 == 0)
								{
									sub_6FB19430(pDVar2, uStack_110, iStack_118, iVar6, local_12c, local_130, a3);
								}
								(&dword_6FBB9898)[dword_6FBB9C58 & 0xff] = local_12c;
								(&dword_6FBB9988)[dword_6FBB9C58 & 0xff] = local_130;
								iVar9 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
								(&dword_6FBB9A78)[dword_6FBB9C58 & 0xff] = iVar9;
								SKILLS_GetSkillInfo(pSkill, &dword_6FBB9B68 + (dword_6FBB9C58 & 0xff), nullptr,
								    nullptr, nullptr);
								dword_6FBB9C5C = (uint8_t)((uint32_t)iVar6 >> 0x18);
								dword_6FBB9C58 = CONCAT31((int32_t)iVar6, (char)dword_6FBB9C58 + '\x01');
								iVar9 = local_12c + -0x30;
								if (a3 != 0)
								{
									iVar9 = local_12c + 0x30;
								}
							}
							else
							{
								if (iVar9 == 0)
								{
									iVar9 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
									iVar3 = sub_6FB57BC0();
									iVar7 = sub_6FB57BD0();
									if ((((iVar3 < local_12c) || (local_12c + 0x30 < iVar3)) || (iVar7 < iStack_124)) || (local_130 < iVar7))
									{
										uVar4 = 1;
									}
									else
									{
										uVar4 = (uint32_t)(iVar6 == 1);
									}
									iVar3 = sub_6FB57BC0();
									iVar6 = sub_6FB57BD0();
									if (((local_12c <= iVar3) && (iVar3 <= local_12c + 0x30)) &&
									    ((iStack_124 <= iVar6 && (iVar6 <= local_130))))
									{
										sVar1 = pDVar2->nSkillId;
										iVar3 = local_12c;
										iVar6 = local_130;
										pDVar8 = CUNIT_GetPlayer();
										sub_6FB15850(pDVar8, (int)sVar1, iVar9, iVar5, uVar4, iVar3, iVar6);
									}
								}
								else
								{
									sub_6FB18790(&pDVar2->nSkillId, iVar6, iVar9, local_12c, local_130);
								}
								iVar9 = local_12c + local_104;
							}
							local_12c = iVar9;
							switch (local_128)
							{
							case 1:
								byte_6FBB9C60 = local_130;
								break;
							case 2:
								byte_6FBB9C64 = local_130;
								break;
							case 3:
								byte_6FBB9C68 = local_130;
								break;
							case 4:
								byte_6FBB9C6C = local_130;
							}
						}
					}
					else if (iVar5 != 0)
						goto LAB_6fb198ce;
				}
			switchD_6fb19ae7_default:
				pSkill = pDStack_108;
			} while (pDStack_108 != nullptr);
		}
		local_128 = local_128 + 1;
		if (4 < local_128)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB19B60
uint32_t __fastcall sub_6FB19B60(D2UnitStrc* pUnit, int a2)
{
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar1;
	int iVar2;

	if (pUnit != nullptr)
	{
		pSkill = UNITS_GetStartSkill(pUnit);
		while ((pSkill != nullptr &&
		        (((pDVar1 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill), pDVar1 == nullptr ||
		                                                                    (iVar2 = SKILLS_GetQuantity(pSkill), iVar2 < 1)) ||
		            (pDVar1->nSkillId != a2)))))
		{
			pSkill = SKILLS_GetNextSkill(pSkill);
		}
	}
	return 0;
}

//D2Client.0x6FB19BB0
void __cdecl sub_6FB19BB0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	bool bVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	D2SkillStrc* pSkill;
	uint32_t uVar6;
	uint32_t* puVar7;
	int iStack_8;
	int local_4;

	pDVar3 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar3 != nullptr);
	local_4 = sub_6FB57BD0();
	bVar2 = false;
	puVar7 = &dword_6FBB9B68;
	do
	{
		uVar6 = puVar7[-0x78];
		uVar1 = puVar7[-0xb4];
		iVar4 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		if (((((int)uVar1 <= iVar4) && (iVar4 <= (int)(uVar1 + 0x30))) && ((int)(uVar6 - 0x30) <= iVar5)) && (iVar5 <= (int)uVar6))
		{
			uVar6 = *puVar7;
			pDVar3 = CUNIT_GetPlayer();
			pSkill = SKILLS_GetSkillById(pDVar3, puVar7[-0x3c], uVar6);
			uVar6 = SKILLS_GetOwnerGUIDFromSkill(pSkill);
			if (uVar6 != 0xffffffff)
			{
				iVar4 = SKILLS_GetSkillInfo(pSkill, nullptr, nullptr, nullptr, &iStack_8);
				if ((iVar4 != 0) && (iStack_8 < 1))
					goto LAB_6fb19ce3;
			}
			sub_6FAADA40(CONCAT31((int32_t)(puVar7[-0x3c] >> 8), 0x3c),
			    (-(uint32_t)(dword_6FBB9D78 != 0) & 0x80000000) + puVar7[-0x3c], *puVar7);
			sub_6FB23260(3, 1, 0);
			dword_6FBB9D78 = 0;
			bVar2 = true;
			sub_6FAABF30();
		}
		puVar7 = puVar7 + 1;
	} while ((int)puVar7 < (int)&dword_6FBB9C58);
	if ((local_4 <= gnScreenHeight + -0x31) && (!bVar2))
	{
	LAB_6fb19ce3:
		iVar4 = sub_6FB23230(3);
		if (iVar4 != 0)
		{
			sub_6FB23260(3, 1, 0);
		}
	}
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB19D30
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB19D30(int a1)
{
	int* piVar1;
	uint32_t* puVar2;
	bool bVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;
	D2SkillStrc* pDVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int local_c;
	int local_8;
	int iStack_4;

	bVar3 = sub_6FB283E0();
	if (D2C_ZEXT(bVar3) == 0)
	{
		bVar3 = a1 == 0;
		local_c = a1;
		if (a1 < 0)
		{
			local_c = -a1;
			bVar3 = local_c == 0;
		}
		if (!bVar3)
		{
			local_8 = -1;
			iVar8 = 0;
			iVar9 = dword_6FBB9CE8;
			do
			{
				iVar9 = iVar9 + D2C_ZEXT(0 < a1) * 2 + -1;
				if (iVar9 < 0)
				{
					iVar9 = 0xf;
				}
				else if (0xf < iVar9)
				{
					iVar9 = 0;
				}
			} while ((((((&dword_6FBB9CF0)[iVar9] == -1) || ((&dword_6FBB9858)[iVar9] != 0)) ||
			              (pDVar4 = CUNIT_GetPlayer(), pDVar4 == nullptr)) ||
			             ((pDVar5 = SKILLS_GetSkillById(pDVar4, (&dword_6FBB9CF0)[iVar9], (&dword_6FBB9D30)[iVar9]),
			                 pDVar5 == nullptr ||
			                     ((((uVar6 = SKILLS_GetOwnerGUIDFromSkill(pDVar5), uVar6 != 0xffffffff &&
			                                                                           (iVar7 = SKILLS_GetSkillInfo(pDVar5, nullptr, nullptr, nullptr, &iStack_4),
			                                                                               iVar7 != 0)) &&
			                           (iStack_4 < 1)) ||
			                         (local_c = local_c + -1, local_8 = iVar9, local_c != 0)))))) &&
			         (iVar8 = iVar8 + 1, iVar8 < 0x10));
			if (((local_8 != -1) && (piVar1 = (int*)(&dword_6FBB9CF0 + local_8), (&dword_6FBB9CF0)[local_8] != -1)) &&
			    (pDVar4 = CUNIT_GetPlayer(), pDVar4 != nullptr))
			{
				puVar2 = &dword_6FBB9D30 + local_8;
				pDVar5 = SKILLS_GetSkillById(pDVar4, *piVar1, (&dword_6FBB9D30)[local_8]);
				if (pDVar5 != nullptr)
				{
					uVar6 = SKILLS_GetOwnerGUIDFromSkill(pDVar5);
					if (((uVar6 != 0xffffffff) &&
					        (iVar9 = SKILLS_GetSkillInfo(pDVar5, nullptr, nullptr, nullptr, &iStack_4),
					            iVar9 != 0)) &&
					    (iStack_4 < 1))
					{
						return;
					}
					pDVar4 = CUNIT_GetPlayer();
					dword_6FBB9CE8 = local_8;
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)*piVar1 >> 8), 0x3c),
					    (-(uint32_t)((&dword_6FBB9858)[local_8] != 0) & 0x80000000) + *piVar1, *puVar2);
					if ((&dword_6FBB9858)[local_8] != 0)
					{
						SKILLS_SetLeftActiveSkill(pDVar4, *piVar1, *puVar2);
						return;
					}
					SKILLS_SetRightActiveSkill(pDVar4, *piVar1, *puVar2);
				}
			}
		}
	}
}

//D2Client.0x6FB19EF0
void __cdecl sub_6FB19EF0()
{
	int iVar1;
	D2UnitStrc* pUnit;
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar2;
	int iVar3;
	int* piVar4;
	int iVar5;
	int iVar6;

	pUnit = CUNIT_GetPlayer();
	pSkill = UNITS_GetStartSkill(pUnit);
	if (pSkill != nullptr)
	{
		do
		{
			pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
			if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & (uint8_t)pDVar2->dwFlags[1]) != 0)
			{
				iVar3 = SKILLS_GetQuantity(pSkill);
				piVar4 = (int*)(&dword_6FBB9A78);
				do
				{
					if (*piVar4 == (int)pDVar2->nSkillId)
					{
						iVar6 = 0xffff;
						iVar5 = 0;
						do
						{
							iVar1 = *piVar4;
							if ((*(int*)((int)&dword_6FBB9CF0 + iVar5) == iVar1) && (iVar3 < 1))
							{
								*(uint32_t*)((int)&dword_6FBB9CF0 + iVar5) = 0xffffffff;
								*(uint32_t*)((int)&dword_6FBB9858 + iVar5) = 0xffffffff;
								*(uint32_t*)((int)&dword_6FBB9D30 + iVar5) = 0xffffffff;
								sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar1 >> 8), 0x51), iVar6, 0xffffffff);
							}
							iVar6 = iVar6 + 0x10000;
							iVar5 = iVar5 + 4;
						} while (iVar6 < 0x10ffff);
					}
					piVar4 = piVar4 + 1;
				} while ((int)piVar4 < (int)&dword_6FBB9B68);
			}
			pSkill = SKILLS_GetNextSkill(pSkill);
		} while (pSkill != nullptr);
		return;
	}
	FOG_DisplayAssert("hSkill", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB19FE0
void __fastcall sub_6FB19FE0(int a1)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	bool bVar6;
	int* local_4;

	local_4 = (int*)(&dword_6FBB9898);
	do
	{
		iVar5 = local_4[0x3c];
		iVar4 = *local_4;
		iVar1 = sub_6FB57BC0();
		iVar2 = sub_6FB57BD0();
		if ((((iVar4 <= iVar1) && (iVar1 <= iVar4 + 0x30)) && (iVar4 = iVar5 + -0x30, iVar4 <= iVar2)) && (iVar2 <= iVar5))
		{
			if ((&dword_6FBB9CF0)[a1] != -1)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar4 >> 8), 0x51), a1 * 0x10000 + 0xffff, 0xffffffff);
			}
			iVar4 = 0;
			iVar5 = local_4[0x78];
			bVar6 = dword_6FBB9D78 == 0;
			(&dword_6FBB9CF0)[a1] = iVar5;
			if (bVar6)
			{
				(&dword_6FBB9858)[a1] = 0;
			}
			else
			{
				(&dword_6FBB9858)[a1] = 1;
			}
			iVar1 = local_4[0xb4];
			(&dword_6FBB9D30)[a1] = iVar1;
			uVar3 = -(uint32_t)((&dword_6FBB9858)[a1] != 0) & 0x8000;
			sub_6FAADA40(D2C_ZEXT(0x51), a1 * 0x10000 + iVar5 + uVar3, iVar1);
			iVar5 = 0xffff;
			do
			{
				if ((((&dword_6FBB9CF0)[a1] == (&dword_6FBB9CF0)[iVar4]) &&
				        (iVar1 = (&dword_6FBB9D30)[iVar4], (&dword_6FBB9D30)[a1] == iVar1)) &&
				    (a1 != iVar4))
				{
					(&dword_6FBB9CF0)[iVar4] = 0xffffffff;
					(&dword_6FBB9858)[iVar4] = 0xffffffff;
					(&dword_6FBB9D30)[iVar4] = 0xffffffff;
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar1 >> 8), 0x51), iVar5, 0xffffffff);
				}
				iVar5 = iVar5 + 0x10000;
				iVar4 = iVar4 + 1;
			} while (iVar5 < 0x10ffff);
		}
		local_4 = local_4 + 1;
	} while ((int)local_4 < (int)&dword_6FBB9988);
}

//D2Client.0x6FB1A130
void __fastcall sub_6FB1A130(int a1)
{
	int* piVar1;
	uint32_t* puVar2;
	D2UnitStrc* pDVar3;
	D2SkillStrc* pSkill;
	uint32_t uVar4;
	int iVar5;
	int iStack_4;

	piVar1 = (int*)(&dword_6FBB9CF0 + a1);
	if (((&dword_6FBB9CF0)[a1] != -1) &&
	    (iStack_4 = a1, pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr))
	{
		puVar2 = &dword_6FBB9D30 + a1;
		pSkill = SKILLS_GetSkillById(pDVar3, *piVar1, (&dword_6FBB9D30)[a1]);
		if (pSkill != nullptr)
		{
			uVar4 = SKILLS_GetOwnerGUIDFromSkill(pSkill);
			if (((uVar4 != 0xffffffff) &&
			        (iVar5 = SKILLS_GetSkillInfo(pSkill, nullptr, nullptr, nullptr, &iStack_4),
			            iVar5 != 0)) &&
			    (iStack_4 < 1))
			{
				return;
			}
			pDVar3 = CUNIT_GetPlayer();
			dword_6FBB9CE8 = a1;
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)*piVar1 >> 8), 0x3c),
			    (-(uint32_t)((&dword_6FBB9858)[a1] != 0) & 0x80000000) + *piVar1, *puVar2);
			if ((&dword_6FBB9858)[a1] != 0)
			{
				SKILLS_SetLeftActiveSkill(pDVar3, *piVar1, *puVar2);
				return;
			}
			SKILLS_SetRightActiveSkill(pDVar3, *piVar1, *puVar2);
		}
	}
}

//D2Client.0x6FB1A200
void __fastcall sub_6FB1A200(int a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
	(&dword_6FBB9CF0)[a1] = a2;
	(&dword_6FBB9858)[a1] = a3;
	(&dword_6FBB9D30)[a1] = a4;
}

//D2Client.0x6FB1A220
void* __fastcall sub_6FB1A220(void* a1, uint32_t a2, int a3, int a4, uint32_t a5, uint32_t a6)
{
	D2CellFileStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc* pDVar3;
	D2GfxDataStrc local_158;
	char local_110[260];
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*(uint8_t***)a1 = &gpuint8_t_6FB6FBAC;
	sprintf(local_110, "%s\\ui\\menu\\spinner", "DATA\\GLOBAL");
	pDVar1 = CLIENT_LoadCellFile(local_110, 0);
	*(int*)((int)a1 + 8) = a3;
	*(uint32_t*)((int)a1 + 0x3c) = a6;
	*(uint32_t*)((int)a1 + 0x2c) = a5;
	*(D2CellFileStrc**)((int)a1 + 0x50) = pDVar1;
	pDVar3 = &local_158;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	*(int*)((int)a1 + 0xc) = a4;
	*(uint32_t*)((int)a1 + 0x34) = 0;
	*(uint32_t*)((int)a1 + 0x38) = 0;
	*(uint32_t*)((int)a1 + 0x30) = 0;
	*(uint32_t*)((int)a1 + 0x4c) = 0;
	*(uint32_t*)((int)a1 + 0x40) = 0;
	local_158.nDirection = 0;
	local_158.nFrame = 0;
	local_158.pCellFile = pDVar1;
	pDVar1 = D2CMP_CelGetHandle(&local_158);
	iVar2 = D2CMP_CelGetHeight(pDVar1);
	*(int*)((int)a1 + 0x24) = iVar2;
	iVar2 = D2CMP_CelGetWidth(pDVar1);
	*(int*)((int)a1 + 0x28) = iVar2;
	*(int*)((int)a1 + 0x14) = a4;
	if (*(int*)((int)a1 + 0x2c) == 0)
	{
		iVar2 = a3 + 1;
		*(int*)((int)a1 + 0x10) = iVar2;
		*(int*)((int)a1 + 0x1c) = *(int*)((int)a1 + 0x24) + 1 + a4;
	}
	else
	{
		*(int*)((int)a1 + 0x1c) = a4;
		iVar2 = iVar2 + a3;
		*(int*)((int)a1 + 0x10) = a3 + 1;
	}
	*(int*)((int)a1 + 0x18) = iVar2;
	return a1;
}

//D2Client.0x6FB1A340
void* __fastcall sub_6FB1A340(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FB1A370((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FB1A370
void __fastcall sub_6FB1A370(uint32_t* a1)
{
	void* local_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6FBAC);
	local_4 = 0;
	CLIENT_FreeCellFile((D2CellFileStrc*)a1[0x14]);
	local_4 = 0xffffffff;
	sub_6FAEFD30(a1);
}

//D2Client.0x6FB1A3D0
void __fastcall sub_6FB1A3D0(int a1)
{
	int nYPos;
	int iVar1;
	D2GfxDataStrc* pDVar2;
	D2GfxDataStrc local_48;

	if ((*(int*)(a1 + 0x38) != 0) || (*(int*)(a1 + 0x34) != 0))
	{
		*(int*)(a1 + 0x40) = *(int*)(a1 + 0x40) + 1;
		(**(code**)(a1 + 0x3c))();
	}
	nYPos = *(int*)(a1 + 0x14);
	pDVar2 = &local_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar2->pCurrentCell = nullptr;
		pDVar2 = (D2GfxDataStrc*)&pDVar2->pCellFile;
	}
	local_48.pCellFile = *(D2CellFileStrc**)(a1 + 0x50);
	local_48.nFrame = *(int*)(a1 + 0x34) * 2;
	local_48.nDirection = 0;
	TEXTURE_CelDraw(&local_48, *(int*)(a1 + 0x10), nYPos, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = *(int*)(a1 + 0x38) * 2 + 1;
	TEXTURE_CelDraw(&local_48, *(int*)(a1 + 0x18), *(int*)(a1 + 0x1c), 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB1A460
uint8_t __fastcall sub_6FB1A460(int a1)
{
	if (*(int*)(a1 + 0x34) != 0)
	{
		return 1;
	}
	return -(*(int*)(a1 + 0x38) != 0) & 2;
}

//D2Client.0x6FB1A480
uint32_t __fastcall sub_6FB1A480(int a1)
{
	DWORD DVar1;
	uint32_t uVar2;

	if ((*(int*)(a1 + 0x34) == 0) && (*(int*)(a1 + 0x38) == 0))
	{
		return 0;
	}
	if (*(int*)(a1 + 0x20) == 0)
	{
		DVar1 = GetTickCount();
		if (*(int*)(a1 + 0x4c) != 0)
		{
			*(DWORD*)(a1 + 0x48) = DVar1;
			return 1;
		}
		uVar2 = DVar1 - *(int*)(a1 + 0x44);
		if (DVar1 - *(int*)(a1 + 0x48) < 0x46)
		{
			return 0;
		}
		*(DWORD*)(a1 + 0x48) = DVar1;
		if (0x1000 < uVar2)
		{
			return *(int*)(a1 + 0x40) * (uVar2 >> 0xb);
		}
		if (3000 < uVar2)
		{
			return *(uint32_t*)(a1 + 0x40) >> 2;
		}
		if (2000 < uVar2)
		{
			return *(uint32_t*)(a1 + 0x40) >> 4;
		}
		if (1000 < uVar2)
		{
			return *(uint32_t*)(a1 + 0x40) >> 5;
		}
	}
	else
	{
		*(uint32_t*)(a1 + 0x34) = 0;
		*(uint32_t*)(a1 + 0x38) = 0;
		*(uint32_t*)(a1 + 0x20) = 0;
	}
	return 1;
}

//D2Client.0x6FB1A530
uint32_t __fastcall sub_6FB1A530(void* a1, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS2)
{
	short sVar1;

	sVar1 = *(short*)((int)&pSMSGHANDLER_PARAMS2->wParam + 2);
	if (sVar1 < 1)
	{
		if (-1 < sVar1)
			goto LAB_6fb1a55e;
		*(uint32_t*)((int)a1 + 0x34) = 0;
		*(uint32_t*)((int)a1 + 0x38) = 1;
	}
	else
	{
		*(uint32_t*)((int)a1 + 0x34) = 1;
		*(uint32_t*)((int)a1 + 0x38) = 0;
	}
	*(uint32_t*)((int)a1 + 0x20) = 1;
LAB_6fb1a55e:
	pSMSGHANDLER_PARAMS2->bUseResult = 1;
	pSMSGHANDLER_PARAMS2->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS2);
	return 1;
}

//D2Client.0x6FB1A580
uint32_t __fastcall sub_6FB1A580(void* a1, int a2, int a3)
{
	uint32_t uVar1;
	DWORD DVar2;
	uint32_t uVar3;

	*(uint32_t*)((int)a1 + 0x30) = 1;
	uVar1 = (uint32_t) * (uint16_t*)(a3 + 0xc);
	uVar3 = (uint32_t) * (uint16_t*)(a3 + 0xe);
	if ((((*(int*)((int)a1 + 0x10) < (int)uVar1) &&
	         ((int)uVar1 < *(int*)((int)a1 + 0x28) + *(int*)((int)a1 + 0x10))) &&
	        (*(int*)((int)a1 + 0x14) - *(int*)((int)a1 + 0x24) < (int)uVar3)) &&
	    ((int)uVar3 <= *(int*)((int)a1 + 0x14)))
	{
		DVar2 = GetTickCount();
		*(DWORD*)((int)a1 + 0x44) = DVar2;
		*(uint32_t*)((int)a1 + 0x34) = 1;
		*(uint32_t*)((int)a1 + 0x4c) = 1;
		(**(code**)((int)a1 + 0x3c))();
		*(uint32_t*)((int)a1 + 0x4c) = 0;
		return 1;
	}
	if (((*(int*)((int)a1 + 0x18) < (int)uVar1) &&
	        ((int)uVar1 < *(int*)((int)a1 + 0x28) + *(int*)((int)a1 + 0x18))) &&
	    ((*(int*)((int)a1 + 0x1c) - *(int*)((int)a1 + 0x24) < (int)uVar3 &&
	        ((int)uVar3 < *(int*)((int)a1 + 0x1c)))))
	{
		DVar2 = GetTickCount();
		*(DWORD*)((int)a1 + 0x44) = DVar2;
		*(uint32_t*)((int)a1 + 0x38) = 1;
		*(uint32_t*)((int)a1 + 0x4c) = 1;
		(**(code**)((int)a1 + 0x3c))();
		*(uint32_t*)((int)a1 + 0x4c) = 0;
		return 1;
	}
	return 0;
}

//D2Client.0x6FB1A630
uint32_t __fastcall sub_6FB1A630(int a1, uint32_t a2, uint32_t a3)
{
	if (*(int*)(a1 + 0x30) != 0)
	{
		*(uint32_t*)(a1 + 0x40) = 0;
		*(uint32_t*)(a1 + 0x30) = 0;
		if (*(int*)(a1 + 0x34) == 1)
		{
			*(uint32_t*)(a1 + 0x34) = 0;
			return 1;
		}
		if (*(int*)(a1 + 0x38) == 1)
		{
			*(uint32_t*)(a1 + 0x38) = 0;
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB1A670
void __fastcall sub_6FB1A670(uint32_t* a1)
{
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6FBE0);
	local_4 = 0;
	if ((uint32_t*)a1[2] != nullptr)
	{
		(*(code*)**(uint32_t**)a1[2])(1);
	}
	local_4 = 0xffffffff;
	sub_6FAEFD30(a1);
}

//D2Client.0x6FB1A6D0
void* __fastcall sub_6FB1A6D0(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FB1A670((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FB1A700
uint32_t* __fastcall sub_6FB1A700(uint32_t* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6)
{
	void* pvVar1;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*a1 = (uint32_t)(&gpuint8_t_6FB6FBE0);
	pvVar1 = SMemAlloc(0x54, "new", -1, 0);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	if (pvVar1 == nullptr)
	{
		pvVar1 = nullptr;
	}
	else
	{
		pvVar1 = sub_6FB1A220(pvVar1, a3, a3, a4, a5, a6);
	}
	a1[2] = (uint32_t)(pvVar1);
	return a1;
}

//D2Client.0x6FB1A780
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FB1A780(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0xc))();
}

//D2Client.0x6FB1A790
void __fastcall sub_6FB1A790(int a1, uint32_t a2, uint32_t a3)
{
	(**(code**)(**(int**)(a1 + 8) + 0x30))();
}

//D2Client.0x6FB1A7A0
void __cdecl sub_6FB1A7A0()
{
	dword_6FBB9F54 = (gnScreenWidth + -0x145) / 2;
}

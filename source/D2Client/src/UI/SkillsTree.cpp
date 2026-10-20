#include "UI/SkillsTree.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Inv.h"
#include "UI/Panel.h"
#include "UI/ShowItems.h"
#include "UI/SkillDesc.h"
#include "UI/SpellSel.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB8CF00
int32_t dword_6FB8CF00 = 1;
//D2Client.0x6FB8CF08
uint8_t byte_6FB8CF08[4];
//D2Client.0x6FB8CF0C
char str_6FB8CF0C[236] = {83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 97, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 115, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 110, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 112, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 98, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 100, 95, 98, 97, 99, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 112, 101, 108, 108, 115, 92, 115, 107, 108, 116, 114, 101, 101, 95, 105, 95, 98, 97, 99, 107};
//D2Client.0x6FB8CFF8
int32_t dword_6FB8CFF8 = 1;
//D2Client.0x6FB8CFFC
uint8_t byte_6FB8CFFC[88] = {0, 0, 0, 0, 0x6B, 0xFF, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0x24, 0xFF, 0xFF, 0xFF, 0x6B, 0xFF, 0xFF, 0xFF, 0xCF, 0xFE, 0xFF, 0xFF};
//D2Client.0x6FB8D0C8
uint32_t dword_6FB8D0C8;
//D2Client.0x6FB8D0CC
char str_6FB8D0CC[30] = "Spells\\AmSkillicon";
//D2Client.0x6FB8D1B6
uint8_t tbl_6FB8D1B6[2];
//D2Client.0x6FBA7894
uint8_t byte_6FBA7894;
//D2Client.0x6FBB9438
uint32_t dword_6FBB9438[128];
//D2Client.0x6FBB9638
uint32_t dword_6FBB9638[128];
//D2Client.0x6FBB9838
int32_t dword_6FBB9838;
//D2Client.0x6FBB983C
int32_t dword_6FBB983C;
//D2Client.0x6FBB9840
uint8_t byte_6FBB9840;
//D2Client.0x6FBB9844
int32_t dword_6FBB9844;
//D2Client.0x6FBB984C
int32_t dword_6FBB984C;
//D2Client.0x6FBB9850
uint8_t byte_6FBB9850;
//D2Client.0x6FBB985C
int32_t dword_6FBB985C;
//D2Client.0x6FBB9860
int32_t dword_6FBB9860;
//D2Client.0x6FBB9864
int32_t dword_6FBB9864;
//D2Client.0x6FBB9868
int32_t dword_6FBB9868;
//D2Client.0x6FBB986C
int32_t dword_6FBB986C;
//D2Client.0x6FBB9870
int32_t dword_6FBB9870;
//D2Client.0x6FBB9874
int32_t dword_6FBB9874;
//D2Client.0x6FBB9878
int32_t dword_6FBB9878;
//D2Client.0x6FBB987C
int32_t dword_6FBB987C;
//D2Client.0x6FBB9880
int32_t dword_6FBB9880;
//D2Client.0x6FBB9884
int32_t dword_6FBB9884;
//D2Client.0x6FBB9888
int32_t dword_6FBB9888;
//D2Client.0x6FBB988C
int32_t dword_6FBB988C;
//D2Client.0x6FBB9890
int32_t dword_6FBB9890;
//D2Client.0x6FBB9894
int32_t dword_6FBB9894;
//D2Client.0x6FBB9898
uint32_t dword_6FBB9898;
//D2Client.0x6FBB9B68
uint32_t dword_6FBB9B68;
//D2Client.0x6FBB9C58
uint32_t dword_6FBB9C58;
//D2Client.0x6FBB9C78
uint32_t dword_6FBB9C78;
//D2Client.0x6FBB9CB8
uint8_t byte_6FBB9CB8;
//D2Client.0x6FBB9CBC
uint8_t byte_6FBB9CBC;
//D2Client.0x6FBB9CC0
uint8_t byte_6FBB9CC0;
//D2Client.0x6FBB9CC4
uint8_t byte_6FBB9CC4;
//D2Client.0x6FBB9CC8
uint8_t byte_6FBB9CC8[2];
//D2Client.0x6FBB9CF4
int32_t dword_6FBB9CF4;
//D2Client.0x6FBB9CF8
int32_t dword_6FBB9CF8;
//D2Client.0x6FBB9CFC
int32_t dword_6FBB9CFC;
//D2Client.0x6FBB9D00
int32_t dword_6FBB9D00;
//D2Client.0x6FBB9D04
int32_t dword_6FBB9D04;
//D2Client.0x6FBB9D08
int32_t dword_6FBB9D08;
//D2Client.0x6FBB9D0C
int32_t dword_6FBB9D0C;
//D2Client.0x6FBB9D10
int32_t dword_6FBB9D10;
//D2Client.0x6FBB9D14
int32_t dword_6FBB9D14;
//D2Client.0x6FBB9D18
int32_t dword_6FBB9D18;
//D2Client.0x6FBB9D1C
int32_t dword_6FBB9D1C;
//D2Client.0x6FBB9D20
int32_t dword_6FBB9D20;
//D2Client.0x6FBB9D24
int32_t dword_6FBB9D24;
//D2Client.0x6FBB9D28
int32_t dword_6FBB9D28;
//D2Client.0x6FBB9D2C
int32_t dword_6FBB9D2C;
//D2Client.0x6FBB9D34
int32_t dword_6FBB9D34;
//D2Client.0x6FBB9D38
int32_t dword_6FBB9D38;
//D2Client.0x6FBB9D3C
int32_t dword_6FBB9D3C;
//D2Client.0x6FBB9D40
int32_t dword_6FBB9D40;
//D2Client.0x6FBB9D44
int32_t dword_6FBB9D44;
//D2Client.0x6FBB9D48
int32_t dword_6FBB9D48;
//D2Client.0x6FBB9D4C
int32_t dword_6FBB9D4C;
//D2Client.0x6FBB9D50
int32_t dword_6FBB9D50;
//D2Client.0x6FBB9D54
int32_t dword_6FBB9D54;
//D2Client.0x6FBB9D58
int32_t dword_6FBB9D58;
//D2Client.0x6FBB9D5C
int32_t dword_6FBB9D5C;
//D2Client.0x6FBB9D60
int32_t dword_6FBB9D60;
//D2Client.0x6FBB9D64
int32_t dword_6FBB9D64;
//D2Client.0x6FBB9D68
int32_t dword_6FBB9D68;
//D2Client.0x6FBB9D6C
int32_t dword_6FBB9D6C;
//D2Client.0x6FBB9D70
uint8_t byte_6FBB9D70;
//D2Client.0x6FBB9D74
D2CellFileStrc* gpCellFile_6FBB9D74;
//D2Client.0x6FBB9D78
int32_t dword_6FBB9D78;

//D2Client.0x6FB16310
void __cdecl sub_6FB16310()
{
	D2CellFileStrc* pDVar1;

	D2_ASSERT(str_6FB8CF0C + (uint32_t)byte_6FBA7894 * 0x22 != nullptr);
	pDVar1 = sub_6FB20100(str_6FB8CF0C + (uint32_t)byte_6FBA7894 * 0x22);
	*(D2CellFileStrc**)(byte_6FB8CF08 + (uint32_t)byte_6FBA7894 * 0x22) = pDVar1;
}

//D2Client.0x6FB16370
void __cdecl sub_6FB16370()
{
	if (*(D2CellFileStrc**)(byte_6FB8CF08 + (uint32_t)byte_6FBA7894 * 0x22) != nullptr)
	{
		CLIENT_FreeCellFile(*(D2CellFileStrc**)(byte_6FB8CF08 + (uint32_t)byte_6FBA7894 * 0x22));
		*(uint32_t*)(byte_6FB8CF08 + (uint32_t)byte_6FBA7894 * 0x22) = 0;
	}
}

//D2Client.0x6FB163B0
void __cdecl sub_6FB163B0()
{
	short* psVar1;
	int nClassId;
	D2UnitStrc* pUnit;
	D2UnitStrc* pUnit_00;
	int iVar2;
	int iVar3;
	int iVar4;
	D2SkillStrc* pDVar5;
	int iVar6;
	int iVar7;
	Unicode* pThis;
	int iVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	int iStack_30;
	CHAR aCStack_20[12];
	Unicode local_14[10];

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		nClassId = pUnit->dwClassId;
		iVar8 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
		wsprintfA(aCStack_20, "%i", iVar8);
		Unicode::toUnicode(local_14, aCStack_20, 9);
		pUnit_00 = CUNIT_GetPlayer();
		if (((pUnit_00 == nullptr) || (iVar8 = STATES_CheckState(pUnit_00, 0x36), iVar8 == 0)) && (dword_6FBB983C == 0))
		{
			iVar8 = 0;
		}
		else
		{
			iVar8 = 1;
		}
		D2Win_10117_DrawText(local_14, (gnScreenWidth - dword_6FBBA748) + -0x34, dword_6FBBA74C + -400 + gnScreenHeight,
		    iVar8, 0);
		iVar8 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
		iStack_30 = 0;
		iVar2 = SKILLS_GetPlayerSkillCount(nClassId);
		if (0 < iVar2)
		{
			do
			{
				iVar2 = SKILLS_GetClassSkillId(nClassId, iStack_30);
				if (((((-1 < iVar2) &&
				          (iVar4 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar4 + 0xba0))) &&
				         ((psVar1 = (short*)(*(int*)(iVar4 + 0xb98) + iVar2 * 0x23c), psVar1 != nullptr && ((iVar3 = (int)psVar1[0xca], -1 < iVar3 && (iVar3 < *(int*)(iVar4 + 0xb94))))))) &&
				        (iVar4 = iVar3 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar4 != 0)) &&
				    (dword_6FB8CF00 == *(char*)(iVar4 + 2)))
				{
					iVar4 = SKILLS_CheckRequiredSkills(pUnit, iVar2);
					if (iVar4 == 0)
					{
						dword_6FBB9638[iStack_30] = 0xffffffff;
						dword_6FBB9438[iStack_30] = 5;
						pDVar5 = SKILLS_GetSkillById(pUnit, (int)*psVar1, 0xffffffff);
						if ((pDVar5 == nullptr) ||
						    (iVar4 = SKILLS_GetSkillLevel(pUnit, pDVar5, 1), iVar4 == 0))
						{
							uVar10 = dword_6FBB9438[iStack_30];
							uVar9 = dword_6FBB9638[iStack_30];
							iVar4 = 0;
						}
						else
						{
							uVar10 = dword_6FBB9438[iStack_30];
							uVar9 = dword_6FBB9638[iStack_30];
						}
						sub_6FB166C0(iVar2, (int)(psVar1), iVar4, uVar9, uVar10);
					}
					else
					{
						iVar4 = 0;
						pDVar5 = SKILLS_GetSkillById(pUnit, iVar2, 0xffffffff);
						if (pDVar5 != nullptr)
						{
							iVar4 = SKILLS_GetSkillLevel(pUnit, pDVar5, 0);
						}
						iVar3 = (int)*psVar1;
						if (((iVar3 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar3)) ||
						    (iVar3 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 +
						                            iVar3 * 0x23c),
						        iVar3 < 1))
						{
							iVar3 = 0x14;
						}
						iVar6 = SKILLS_CheckRequiredAttributes(pUnit, iVar2);
						iVar7 = 1;
						if (*(uint32_t*)(psVar1 + 0xb8) != 0xffffffff)
						{
							iVar7 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(psVar1 + 0xb8), iVar2, iVar4);
						}
						if ((iVar8 < iVar7) || (iVar6 == 0 || iVar3 <= iVar4))
						{
							dword_6FBB9638[iStack_30] = 0xffffffff;
							dword_6FBB9438[iStack_30] = 5;
						}
						else if (dword_6FBB9638[iStack_30] != 1)
						{
							dword_6FBB9638[iStack_30] = 0;
							dword_6FBB9438[iStack_30] = 0;
						}
						iVar4 = 0;
						if (pDVar5 != nullptr)
						{
							iVar4 = SKILLS_GetSkillLevel(pUnit, pDVar5, 1);
						}
						sub_6FB166C0(iVar2, (int)(psVar1), iVar4, dword_6FBB9638[iStack_30],
						    dword_6FBB9438[iStack_30]);
					}
				}
				iStack_30 = iStack_30 + 1;
				iVar2 = SKILLS_GetPlayerSkillCount(nClassId);
			} while (iStack_30 < iVar2);
		}
	}
}

//D2Client.0x6FB166C0
void __fastcall sub_6FB166C0(int a1, int a2, int a3, int a4, int a5)
{
	char cVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	D2CellFileStrc* pDVar5;
	D2UnitStrc* pDVar6;
	D2SkillStrc* pSkill;
	int iVar7;
	int iVar8;
	Unicode* pUVar9;
	int nXPos;
	D2GfxDataStrc* pDVar10;
	uint32_t uVar11;
	uint32_t uStack_874;
	CHAR aCStack_868[12];
	Unicode aUStack_85c[10];
	D2GfxDataStrc DStack_848;
	Unicode local_800[1024];

	if (((((-1 < a1) && (iVar8 = *(int*)((uint8_t*)&sgptDataTables), a1 < *(int*)(iVar8 + 0xba0))) && (iVar2 = *(int*)(iVar8 + 0xb98) + a1 * 0x23c, iVar2 != 0)) &&
	        ((iVar2 = (int)*(short*)(iVar2 + 0x194), -1 < iVar2 && (iVar2 < *(int*)(iVar8 + 0xb94))))) &&
	    (iVar8 = iVar2 * 0x120 + *(int*)(iVar8 + 0xb8c), iVar8 != 0))
	{
		cVar1 = *(char*)(iVar8 + 3);
		if (cVar1 == '\x01')
		{
			iVar2 = dword_6FBBA74C + -0x1a2 + gnScreenHeight;
		}
		else if (cVar1 == '\x02')
		{
			iVar2 = dword_6FBBA74C + -0x15e + gnScreenHeight;
		}
		else if (cVar1 == '\x03')
		{
			iVar2 = dword_6FBBA74C + -0x11a + gnScreenHeight;
		}
		else if (cVar1 == '\x04')
		{
			iVar2 = dword_6FBBA74C + -0xd6 + gnScreenHeight;
		}
		else if (cVar1 == '\x05')
		{
			iVar2 = dword_6FBBA74C + -0x91 + gnScreenHeight;
		}
		else if (cVar1 == '\x06')
		{
			iVar2 = dword_6FBBA74C + -0x4d + gnScreenHeight;
		}
		else
		{
			iVar2 = 0;
		}
		cVar1 = *(char*)(iVar8 + 4);
		if (cVar1 == '\x01')
		{
			nXPos = (gnScreenWidth - dword_6FBBA748) + -0x131;
		}
		else if (cVar1 == '\x02')
		{
			nXPos = (gnScreenWidth - dword_6FBBA748) + -0xec;
		}
		else if (cVar1 == '\x03')
		{
			nXPos = (gnScreenWidth - dword_6FBBA748) + -0xa7;
		}
		else
		{
			nXPos = 0;
		}
		iVar3 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		pDVar5 = sub_6FB18700(nullptr);
		uStack_874 = (uint32_t) * (uint8_t*)(iVar8 + 7);
		if (a4 == 1)
		{
			uStack_874 = uStack_874 + 1;
		}
		if (((nXPos < iVar3) && (iVar3 < nXPos + 0x30)) && ((iVar2 + -0x30 < iVar4 && (iVar4 < iVar2))))
		{
			a5 = 3;
		}
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(a2 + 5)) == 0)
		{
			a5 = 1;
		}
		pDVar6 = CUNIT_GetPlayer();
		iVar8 = 0;
		pSkill = SKILLS_GetSkillById(pDVar6, a1, 0xffffffff);
		iVar8 = SKILLS_GetSkillLevel(pDVar6, pSkill, iVar8);
		iVar7 = SKILLS_GetBonusSkillLevelFromSkillId(pDVar6, a1);
		if (((iVar8 == 0) && (iVar7 != 0)) && (a4 != -1))
		{
			a5 = 3;
		}
		pDVar10 = &DStack_848;
		for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			pDVar10->pCurrentCell = nullptr;
			pDVar10 = (D2GfxDataStrc*)&pDVar10->pCellFile;
		}
		DStack_848.nDirection = 0;
		DStack_848.nFrame = uStack_874;
		DStack_848.pCellFile = pDVar5;
		TEXTURE_CelDrawColor(&DStack_848, nXPos, iVar2, 0xffffffff, DRAWMODE_NORMAL, a5);
		if (((nXPos < iVar3) && (iVar3 < nXPos + 0x30)) && ((iVar2 + -0x30 < iVar4 && (iVar4 < iVar2))))
		{
			uVar11 = 0;
			if (a4 == -1)
			{
				iVar3 = a3;
				iVar4 = nXPos;
				iVar7 = iVar2;
				pDVar6 = CUNIT_GetPlayer();
				sub_6FB15220(pDVar6, a1, iVar3, uVar11, iVar4, iVar7);
			}
			else
			{
				iVar3 = a3;
				iVar4 = nXPos;
				iVar7 = iVar2;
				CUNIT_GetPlayer();
				sub_6FB14C00(iVar3, uVar11, iVar4, iVar7);
			}
		}
		if ((iVar8 != 0) || (a3 != 0))
		{
			wsprintfA(aCStack_868, "%d", a3);
			Unicode::toUnicode(aUStack_85c, aCStack_868, 9);
			if (a3 < 10)
			{
				D2Win_10127_SetFont(D2FONT_FONT16);
			}
			else
			{
				D2Win_10127_SetFont(D2FONT_FONTFORMAL10);
				nXPos = nXPos + -4;
			}
			pDVar6 = CUNIT_GetPlayer();
			iVar3 = 0;
			iVar8 = SKILLS_GetBonusSkillLevelFromSkillId(pDVar6, a1);
			if (iVar8 < 1)
			{
				if (iVar8 < 0)
				{
					iVar3 = 1;
				}
			}
			else
			{
				iVar3 = 3;
			}
			D2Win_10117_DrawText(aUStack_85c, nXPos + 0x30, iVar2 + 0xc, iVar3, 0);
		}
	}
}

//D2Client.0x6FB16A50
void __cdecl sub_6FB16A50()
{
	int iVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	int iVar3;
	int iVar4;
	D2SkillStrc* pSkill;
	Unicode* pThis;
	int iVar5;
	CHAR aCStack_20[12];
	Unicode local_14[10];

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		if (dword_6FBB9844 == 0)
		{
			wsprintfA(aCStack_20, "%d", 0);
			Unicode::toUnicode(local_14, aCStack_20, 9);
			sub_6FACFCD0((gnScreenWidth - dword_6FBBA748) + -0x41, dword_6FBBA74C + -400 + gnScreenHeight,
			    (gnScreenWidth - dword_6FBBA748) + -0x19, local_14, nullptr);
		}
		iVar5 = 0;
		while (true)
		{
			iVar2 = SKILLS_GetPlayerSkillCount(pUnit->dwClassId);
			if (iVar2 <= iVar5)
				break;
			iVar2 = SKILLS_GetClassSkillId(pUnit->dwClassId, iVar5);
			if ((-1 < iVar2) && (iVar4 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar4 + 0xba0)))
			{
				iVar1 = *(int*)(iVar4 + 0xb98) + iVar2 * 0x23c;
				if (((iVar1 != 0) &&
				        (((iVar3 = (int)*(short*)(iVar1 + 0x194), -1 < iVar3 &&
				                                                      (iVar3 < *(int*)(iVar4 + 0xb94))) &&
				            (iVar4 = iVar3 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar4 != 0)))) &&
				    (dword_6FB8CF00 == *(char*)(iVar4 + 2)))
				{
					dword_6FBB9638[iVar5] = 0xffffffff;
					dword_6FBB9438[iVar5] = 5;
					iVar4 = 0;
					pSkill = SKILLS_GetSkillById(pUnit, iVar2, 0xffffffff);
					if (pSkill != nullptr)
					{
						iVar4 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
						if (0 < iVar4)
						{
							dword_6FBB9638[iVar5] = 0;
							dword_6FBB9438[iVar5] = 0;
						}
					}
					sub_6FB166C0(iVar2, iVar1, iVar4, dword_6FBB9638[iVar5], dword_6FBB9438[iVar5]);
				}
			}
			iVar5 = iVar5 + 1;
		}
	}
}

//D2Client.0x6FB16BE0
void __cdecl sub_6FB16BE0()
{
	byte_6FBB9850 = D2Win_10034_MixRGB(0, 0, 0);
}

//D2Client.0x6FB16C00
void __cdecl sub_6FB16C00()
{
	D2UnitStrc* pUnit;
	int iVar1;
	Unicode* wszText;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	D2GfxDataStrc* pDVar6;
	D2GfxDataStrc DStack_48;

	pUnit = CUNIT_GetPlayer();
	D2Win_10127_SetFont(D2FONT_FONT16);
	iVar1 = dword_6FB8CF00;
	pDVar6 = &DStack_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	DStack_48.pCellFile = *(D2CellFileStrc**)(byte_6FB8CF08 + (uint32_t)byte_6FBA7894 * 0x22);
	dword_6FBB984C = 1;
	DStack_48.nDirection = 0;
	DStack_48.nFrame = 0;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = 1;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = 2;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = 3;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	uVar4 = iVar1 * 4;
	DStack_48.nFrame = uVar4;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = uVar4 + 1;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = uVar4 + 2;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	DStack_48.nFrame = uVar4 + 3;
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	sub_6FB17080();
	iVar1 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
	if (iVar1 < 1)
	{
		byte_6FBB9840 = 0;
		dword_6FBB9844 = 0;
		sub_6FB16A50();
	}
	else
	{
		byte_6FBB9840 = 1;
		dword_6FBB9844 = 1;
		sub_6FB163B0();
	}
	iVar1 = *(int*)(byte_6FB8CFFC + (dword_6FB8CF00 + (uint32_t)byte_6FBA7894 * 3) * 4);
	if (iVar1 == -0x95)
	{
		dword_6FB8CFF8 = 1;
	}
	else if (iVar1 == -0xdc)
	{
		dword_6FB8CFF8 = 2;
	}
	else if (iVar1 == -0x131)
	{
		dword_6FB8CFF8 = 3;
	}
	iVar2 = gnScreenWidth - dword_6FBBA748;
	pDVar6 = &DStack_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	DStack_48.pCellFile = sub_6FB24110();
	DStack_48.nFrame = (dword_6FBB9838 != 0) + 10;
	DStack_48.nDirection = 0;
	TEXTURE_CelDraw(&DStack_48, iVar1 + iVar2, dword_6FBBA74C + -0x3f + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	if (dword_6FB8CFF8 == 1)
	{
		iVar5 = gnScreenWidth - dword_6FBBA748;
		iVar1 = dword_6FBBA74C + -0x3f + gnScreenHeight;
		iVar2 = sub_6FB57BC0();
		iVar3 = sub_6FB57BD0();
		if ((((iVar2 < iVar5 + -0x95) || (iVar5 + -0x73 < iVar2)) || (iVar3 < iVar1 + -0x22)) ||
		    (iVar1 < iVar3))
			goto LAB_6fb17068;
		iVar1 = dword_6FBBA74C + -0x62 + gnScreenHeight;
		iVar2 = (gnScreenWidth - dword_6FBBA748) + -0x86;
	}
	else if (dword_6FB8CFF8 == 2)
	{
		iVar1 = sub_6FB17A30((gnScreenWidth - dword_6FBBA748) + -0xdc, dword_6FBBA74C + -0x3f + gnScreenHeight,
		    0x22, 0x22);
		if (iVar1 == 0)
			goto LAB_6fb17068;
		iVar1 = dword_6FBBA74C + -0x62 + gnScreenHeight;
		iVar2 = (gnScreenWidth - dword_6FBBA748) + -0xcd;
	}
	else
	{
		if (dword_6FB8CFF8 != 3)
			goto LAB_6fb17068;
		iVar1 = sub_6FB17A30((gnScreenWidth - dword_6FBBA748) + -0x131, dword_6FBBA74C + -0x3f + gnScreenHeight,
		    0x22, 0x22);
		if (iVar1 == 0)
			goto LAB_6fb17068;
		iVar1 = dword_6FBBA74C + -0x62 + gnScreenHeight;
		iVar2 = (gnScreenWidth - dword_6FBBA748) + -0x122;
	}
	iVar5 = 1;
	iVar3 = 0;
	wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
	D2Win_10129_DrawFramedText(wszText, iVar2, iVar1, iVar3, iVar5);
LAB_6fb17068:
	sub_6FB17800();
}

//D2Client.0x6FB17080
void __cdecl sub_6FB17080()
{
	Unicode* pUVar1;

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1083));
	sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x1c7 + gnScreenHeight,
	    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1084));
	sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x1bb + gnScreenHeight,
	    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1085));
	sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x1af + gnScreenHeight,
	    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
	if (byte_6FBA7894 == 0)
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1088));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x14a + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1089));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x13e + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1086));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x132 + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108a));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xde + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108b));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xd2 + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1086));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xc6 + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108c));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x79 + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108d));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x6d + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1086));
		sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x61 + gnScreenHeight,
		    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
	}
	else
	{
		if (byte_6FBA7894 == 3)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108e));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x144 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108f));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x138 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1090));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xd8 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x108f));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xcc + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1091));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x6e + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1086));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x62 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			return;
		}
		if (byte_6FBA7894 == 2)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1092));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x144 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1087));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x138 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1093));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xde + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1094));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xd2 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1087));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xc6 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1095));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x68 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			return;
		}
		if (byte_6FBA7894 == 4)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1096));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0x13e + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1097));
			sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + -0xd8 + gnScreenHeight,
			    gnViewWidth - dword_6FBBA748, pUVar1, nullptr);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1098));
			sub_6FB177C0(pUVar1, 0x114);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1097));
			sub_6FB177C0(pUVar1, 0x172);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1086));
			sub_6FB177C0(pUVar1, 0x17e);
			return;
		}
		if (byte_6FBA7894 == 1)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1099));
			sub_6FB177C0(pUVar1, 0x9c);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1087));
			sub_6FB177C0(pUVar1, 0xa8);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109a));
			sub_6FB177C0(pUVar1, 0x108);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1087));
			sub_6FB177C0(pUVar1, 0x114);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109b));
			sub_6FB177C0(pUVar1, 0x172);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1087));
			sub_6FB177C0(pUVar1, 0x17e);
			return;
		}
		if (byte_6FBA7894 == 6)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f4));
			sub_6FB177C0(pUVar1, 0x96);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f5));
			sub_6FB177C0(pUVar1, 0xa2);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f2));
			sub_6FB177C0(pUVar1, 0x108);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f3));
			sub_6FB177C0(pUVar1, 0x114);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f1));
			sub_6FB177C0(pUVar1, 0x172);
			return;
		}
		if (byte_6FBA7894 == 5)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57f0));
			sub_6FB177C0(pUVar1, 0xa2);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57ee));
			sub_6FB177C0(pUVar1, 0x108);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57ef));
			sub_6FB177C0(pUVar1, 0x114);
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x57ed));
			sub_6FB177C0(pUVar1, 0x172);
			return;
		}
	}
}

//D2Client.0x6FB177C0
void __fastcall sub_6FB177C0(Unicode* pUnicode, int a2)
{
	sub_6FACFCD0((gnViewWidth - dword_6FBBA748) + -0x5a, dword_6FBBA74C + gnScreenHeight + -0x1e0 + a2,
	    gnViewWidth - dword_6FBBA748, pUnicode, nullptr);
}

//D2Client.0x6FB17800
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB17800()
{
	bool bVar1;
	bool bVar2;
	bool bVar3;
	bool bVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	Unicode* pUVar8;
	int in_ECX;
	int iVar9;
	D2SkillsTxt* pDVar10;
	Unicode local_64[50];

	iVar5 = sub_6FB57BC0();
	iVar6 = sub_6FB57BD0();
	iVar9 = 0;
	bVar1 = false;
	bVar2 = false;
	bVar3 = false;
	bVar4 = false;
	byte_6FBB9850 = D2Win_10034_MixRGB(0, 0, 0);
	if ((iVar5 < (gnScreenWidth - dword_6FBBA748) + -0x59) || ((gnScreenWidth - dword_6FBBA748) + 1 < iVar5))
		goto LAB_6fb17958;
	if (in_ECX == 1)
	{
		if ((iVar6 <= dword_6FBBA74C + -0x9c + gnScreenHeight) &&
		    (iVar7 = dword_6FBBA74C + -0x108 + gnScreenHeight, iVar7 <= iVar6))
		{
		LAB_6fb17947:
			bVar3 = true;
			bVar1 = true;
			iVar9 = iVar7;
			goto LAB_6fb17958;
		}
		if ((dword_6FBBA74C + -0x108 + gnScreenHeight < iVar6) ||
		    (iVar5 = dword_6FBBA74C + -0x174 + gnScreenHeight, iVar6 < iVar5))
			goto LAB_6fb17958;
	LAB_6fb178c1:
		bVar4 = true;
		bVar1 = true;
		iVar9 = iVar5;
	}
	else
	{
		if (in_ECX == 2)
		{
			if ((iVar6 <= dword_6FBBA74C + -0x108 + gnScreenHeight) &&
			    (iVar5 = dword_6FBBA74C + -0x174 + gnScreenHeight, iVar5 <= iVar6))
				goto LAB_6fb178c1;
			if (dword_6FBBA74C + -0x30 + gnScreenHeight < iVar6)
				goto LAB_6fb17958;
			iVar5 = dword_6FBBA74C + -0x9c + gnScreenHeight;
		}
		else
		{
			if (in_ECX != 3)
				goto LAB_6fb17958;
			iVar5 = dword_6FBBA74C + -0x9c + gnScreenHeight;
			if ((iVar6 <= iVar5) && (iVar7 = dword_6FBBA74C + -0x108 + gnScreenHeight, iVar7 <= iVar6))
				goto LAB_6fb17947;
			if (dword_6FBBA74C + -0x30 + gnScreenHeight < iVar6)
				goto LAB_6fb17958;
		}
		if (iVar5 <= iVar6)
		{
			bVar2 = true;
			bVar1 = true;
			iVar9 = iVar5;
		}
	}
LAB_6fb17958:
	D2Win_10127_SetFont(D2FONT_FONT16);
	if (bVar1)
	{
		sub_6FB5B0F0((gnScreenWidth - dword_6FBBA748) + -0x59, iVar9 + 5, 0x5a, 0x14, (uint32_t)byte_6FBB9850, (DrawMode)(6));
		if (bVar2)
		{
			pDVar10 = nullptr;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1082));
			sub_6FACFCD0((gnScreenWidth - dword_6FBBA748) + -0x59, iVar9 + 0x14, 0x5a, pUVar8, pDVar10);
		}
		if (bVar3)
		{
			pDVar10 = nullptr;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1081));
			sub_6FACFCD0((gnScreenWidth - dword_6FBBA748) + -0x59, iVar9 + 0x14, 0x5a, pUVar8, pDVar10);
		}
		if (bVar4)
		{
			pDVar10 = nullptr;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1080));
			sub_6FACFCD0((gnScreenWidth - dword_6FBBA748) + -0x59, iVar9 + 0x14, 0x5a, pUVar8, pDVar10);
		}
	}
}

//D2Client.0x6FB17A30
uint32_t __fastcall sub_6FB17A30(int a1, int a2, int a3, int a4)
{
	int iVar1;
	int iVar2;

	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	if ((((a1 <= iVar1) && (iVar1 <= a1 + a3)) && (a2 - a4 <= iVar2)) &&
	    (iVar2 <= a2))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB17A80
void __cdecl sub_6FB17A80(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short* psVar1;
	char cVar2;
	uint16_t uVar3;
	uint32_t uVar4;
	int iVar5;
	D2UnitStrc* pUnit;
	int iVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	int iVar10;

	uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar3 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	uVar9 = (uint32_t)uVar3;
	iVar5 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar5 != 0)
	{
		return;
	}
	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		return;
	}
	iVar5 = pUnit->dwClassId;
	if (gnScreenHeight + -0x30 < (int)uVar9)
	{
		return;
	}
	if (dword_6FBB984C == 0)
	{
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if ((((gnScreenWidth - dword_6FBBA748) + -0x140 < (int)uVar4) &&
	        ((int)uVar4 < (gnScreenWidth - dword_6FBBA748) + -0x58)) &&
	    (iVar6 = STATLIST_GetUnitBaseStat(pUnit, 5, 0), iVar6 < 1))
	{
		iVar10 = 0;
		iVar6 = SKILLS_GetPlayerSkillCount(iVar5);
		if (0 < iVar6)
		{
			do
			{
				iVar6 = SKILLS_GetClassSkillId(iVar5, iVar10);
				if ((((-1 < iVar6) &&
				         (iVar7 = *(int*)((uint8_t*)&sgptDataTables), iVar6 < *(int*)(iVar7 + 0xba0))) &&
				        ((psVar1 = (short*)(*(int*)(iVar7 + 0xb98) + iVar6 * 0x23c), psVar1 != nullptr &&
				                                                                         ((iVar6 = (int)psVar1[0xca], -1 < iVar6 && (iVar6 < *(int*)(iVar7 + 0xb94))))))) &&
				    (iVar6 = iVar6 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar6 != 0))
				{
					if (dword_6FB8CF00 == *(char*)(iVar6 + 2))
					{
						cVar2 = *(char*)(iVar6 + 3);
						if (cVar2 == '\x01')
						{
							iVar7 = dword_6FBBA74C + -0x1a2 + gnScreenHeight;
						}
						else if (cVar2 == '\x02')
						{
							iVar7 = dword_6FBBA74C + -0x15e + gnScreenHeight;
						}
						else if (cVar2 == '\x03')
						{
							iVar7 = dword_6FBBA74C + -0x11a + gnScreenHeight;
						}
						else if (cVar2 == '\x04')
						{
							iVar7 = dword_6FBBA74C + -0xd6 + gnScreenHeight;
						}
						else if (cVar2 == '\x05')
						{
							iVar7 = dword_6FBBA74C + -0x91 + gnScreenHeight;
						}
						else if (cVar2 == '\x06')
						{
							iVar7 = dword_6FBBA74C + -0x4d + gnScreenHeight;
						}
						else
						{
							iVar7 = 0;
						}
						if ((iVar7 + -0x30 < (int)uVar9) && ((int)uVar9 < iVar7))
						{
							cVar2 = *(char*)(iVar6 + 4);
							if (cVar2 == '\x01')
							{
								iVar6 = (gnScreenWidth - dword_6FBBA748) + -0x131;
							}
							else if (cVar2 == '\x02')
							{
								iVar6 = (gnScreenWidth - dword_6FBBA748) + -0xec;
							}
							else if (cVar2 == '\x03')
							{
								iVar6 = (gnScreenWidth - dword_6FBBA748) + -0xa7;
							}
							else
							{
								iVar6 = 0;
							}
							if ((((iVar6 < (int)uVar4) && ((int)uVar4 < iVar6 + 0x30)) &&
							        (dword_6FBB9638[iVar10] == 0)) &&
							    (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(psVar1 + 2)) == 0))
							{
								sub_6FAADA40(CONCAT31((uint32_t)(uint8_t)(uVar3 >> 8), 0x3c), (int)*psVar1, 0xffffffff);
								sub_6FB23260(4, 1, 0);
								goto LAB_6fb17d2a;
							}
						}
					}
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				}
			LAB_6fb17d2a:
				iVar10 = iVar10 + 1;
				iVar6 = SKILLS_GetPlayerSkillCount(iVar5);
			} while (iVar10 < iVar6);
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
	iVar6 = dword_6FB8CF00;
	if ((gnScreenWidth - dword_6FBBA748) + -0x58 <= (int)uVar4)
	{
		if ((int)uVar4 <= gnScreenWidth - dword_6FBBA748)
		{
			if ((dword_6FBBA74C + -0x174 + gnScreenHeight < (int)uVar9) &&
			    ((int)uVar9 < dword_6FBBA74C + -0x109 + gnScreenHeight))
			{
				dword_6FB8CF00 = 3;
			}
			if ((dword_6FBBA74C + -0x108 + gnScreenHeight < (int)uVar9) &&
			    ((int)uVar9 < dword_6FBBA74C + -0x9d + gnScreenHeight))
			{
				dword_6FB8CF00 = 2;
			}
			if ((dword_6FBBA74C + -0x9c + gnScreenHeight < (int)uVar9) && ((int)uVar9 < gnScreenHeight + -0x31))
			{
				dword_6FB8CF00 = 1;
			}
			if (dword_6FB8CF00 != iVar6)
			{
				sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
			}
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
	if (dword_6FB8CFF8 == 1)
	{
		iVar6 = (gnScreenWidth - dword_6FBBA748) + -0x95;
	}
	else if (dword_6FB8CFF8 == 2)
	{
		iVar6 = (gnScreenWidth - dword_6FBBA748) + -0xdc;
	}
	else
	{
		if (dword_6FB8CFF8 != 3)
			goto LAB_6fb17ea6;
		iVar6 = (gnScreenWidth - dword_6FBBA748) + -0x131;
	}
	iVar10 = dword_6FBBA74C + -0x3f + gnScreenHeight;
	iVar7 = sub_6FB57BC0();
	iVar8 = sub_6FB57BD0();
	if ((((iVar6 <= iVar7) && (iVar7 <= iVar6 + 0x22)) && (iVar10 + -0x22 <= iVar8)) &&
	    (iVar8 <= iVar10))
	{
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		dword_6FBB9838 = 1;
	}
LAB_6fb17ea6:
	if (((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0x140) ||
	    ((gnScreenWidth - dword_6FBBA748) + -0x58 <= (int)uVar4))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	iVar6 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
	if (0 < iVar6)
	{
		iVar10 = 0;
		iVar6 = SKILLS_GetPlayerSkillCount(iVar5);
		if (0 < iVar6)
		{
			do
			{
				iVar6 = SKILLS_GetClassSkillId(iVar5, iVar10);
				if ((((-1 < iVar6) &&
				         (iVar7 = *(int*)((uint8_t*)&sgptDataTables), iVar6 < *(int*)(iVar7 + 0xba0))) &&
				        ((iVar6 = *(int*)(iVar7 + 0xb98) + iVar6 * 0x23c, iVar6 != 0 &&
				                                                              (((iVar6 = (int)*(short*)(iVar6 + 0x194), -1 < iVar6 &&
				                                                                                                            (iVar6 < *(int*)(iVar7 + 0xb94))) &&
				                                                                  (iVar6 = iVar6 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar6 != 0)))))) &&
				    (dword_6FB8CF00 == *(char*)(iVar6 + 2)))
				{
					cVar2 = *(char*)(iVar6 + 3);
					if (cVar2 == '\x01')
					{
						iVar7 = dword_6FBBA74C + -0x1a2 + gnScreenHeight;
					}
					else if (cVar2 == '\x02')
					{
						iVar7 = dword_6FBBA74C + -0x15e + gnScreenHeight;
					}
					else if (cVar2 == '\x03')
					{
						iVar7 = dword_6FBBA74C + -0x11a + gnScreenHeight;
					}
					else if (cVar2 == '\x04')
					{
						iVar7 = dword_6FBBA74C + -0xd6 + gnScreenHeight;
					}
					else if (cVar2 == '\x05')
					{
						iVar7 = dword_6FBBA74C + -0x91 + gnScreenHeight;
					}
					else if (cVar2 == '\x06')
					{
						iVar7 = dword_6FBBA74C + -0x4d + gnScreenHeight;
					}
					else
					{
						iVar7 = 0;
					}
					if ((iVar7 + -0x30 < (int)uVar9) && ((int)uVar9 < iVar7))
					{
						cVar2 = *(char*)(iVar6 + 4);
						if (cVar2 == '\x01')
						{
							iVar6 = (gnScreenWidth - dword_6FBBA748) + -0x131;
						}
						else if (cVar2 == '\x02')
						{
							iVar6 = (gnScreenWidth - dword_6FBBA748) + -0xec;
						}
						else if (cVar2 == '\x03')
						{
							iVar6 = (gnScreenWidth - dword_6FBBA748) + -0xa7;
						}
						else
						{
							iVar6 = 0;
						}
						if (((iVar6 < (int)uVar4) && ((int)uVar4 < iVar6 + 0x30)) &&
						    (dword_6FBB9638[iVar10] == 0))
						{
							dword_6FBB9638[iVar10] = 1;
							dword_6FBB9438[iVar10] = 3;
							sub_6FB57480((int)pSMSGHANDLER_PARAMS);
							pSMSGHANDLER_PARAMS->bUseResult = 1;
							pSMSGHANDLER_PARAMS->lResult = 0;
							sub_6FB55820(5, nullptr, 0.0, 0.0, 0);
							SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
							return;
						}
					}
				}
				iVar10 = iVar10 + 1;
				iVar6 = SKILLS_GetPlayerSkillCount(iVar5);
			} while (iVar10 < iVar6);
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB18100
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB18100(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short* psVar1;
	char cVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	D2SkillStrc* pDVar8;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar9;
	int iVar10;
	int iVar11;
	uint32_t uVar12;
	int iStack_14;

	uVar12 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar3 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	pDVar4 = CUNIT_GetPlayer();
	if (pDVar4 == nullptr)
	{
		return;
	}
	iVar11 = pDVar4->dwClassId;
	sub_6FB57500((int)pSMSGHANDLER_PARAMS);
	iVar5 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar5 != 0)
	{
		return;
	}
	if (dword_6FBB984C == 0)
	{
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if (dword_6FBB9838 == 0)
	{
		if ((int)uVar12 <= gnScreenWidth / 2)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 0;
			return;
		}
		iVar5 = STATLIST_GetUnitBaseStat(pDVar4, 5, 0);
		if (0 < iVar5)
		{
			iStack_14 = 0;
			iVar6 = SKILLS_GetPlayerSkillCount(iVar11);
			if (0 < iVar6)
			{
				do
				{
					iVar6 = SKILLS_GetClassSkillId(iVar11, iStack_14);
					if ((((-1 < iVar6) &&
					         (iVar10 = *(int*)((uint8_t*)&sgptDataTables), iVar6 < *(int*)(iVar10 + 0xba0))) &&
					        (psVar1 = (short*)(*(int*)(iVar10 + 0xb98) + iVar6 * 0x23c), psVar1 != nullptr)) &&
					    (((iVar7 = (int)psVar1[0xca], -1 < iVar7 && (iVar7 < *(int*)(iVar10 + 0xb94))) && (iVar10 = iVar7 * 0x120 + *(int*)(iVar10 + 0xb8c), iVar10 != 0))))
					{
						if (dword_6FB8CF00 == *(char*)(iVar10 + 2))
						{
							cVar2 = *(char*)(iVar10 + 3);
							if (cVar2 == '\x01')
							{
								iVar7 = dword_6FBBA74C + -0x1a2 + gnScreenHeight;
							}
							else if (cVar2 == '\x02')
							{
								iVar7 = dword_6FBBA74C + -0x15e + gnScreenHeight;
							}
							else if (cVar2 == '\x03')
							{
								iVar7 = dword_6FBBA74C + -0x11a + gnScreenHeight;
							}
							else if (cVar2 == '\x04')
							{
								iVar7 = dword_6FBBA74C + -0xd6 + gnScreenHeight;
							}
							else if (cVar2 == '\x05')
							{
								iVar7 = dword_6FBBA74C + -0x91 + gnScreenHeight;
							}
							else if (cVar2 == '\x06')
							{
								iVar7 = dword_6FBBA74C + -0x4d + gnScreenHeight;
							}
							else
							{
								iVar7 = 0;
							}
							if ((iVar7 + -0x30 < (int)uVar3) && ((int)uVar3 < iVar7))
							{
								cVar2 = *(char*)(iVar10 + 4);
								if (cVar2 == '\x01')
								{
									iVar10 = (gnScreenWidth - dword_6FBBA748) + -0x131;
								}
								else if (cVar2 == '\x02')
								{
									iVar10 = (gnScreenWidth - dword_6FBBA748) + -0xec;
								}
								else if (cVar2 == '\x03')
								{
									iVar10 = (gnScreenWidth - dword_6FBBA748) + -0xa7;
								}
								else
								{
									iVar10 = 0;
								}
								if (((iVar10 < (int)uVar12) && ((int)uVar12 < iVar10 + 0x30)) &&
								    (dword_6FBB9638[iStack_14] == 1))
								{
									if (*(int*)(psVar1 + 0xb8) != -1)
									{
										iVar11 = 0;
										pDVar8 = SKILLS_GetSkillById(pDVar4, iVar6, 0xffffffff);
										if (pDVar8 != nullptr)
										{
											iVar11 = SKILLS_GetSkillLevel(pDVar4, pDVar8, 0);
										}
										iVar11 = SKILLS_EvaluateSkillFormula(pDVar4, *(uint32_t*)(psVar1 + 0xb8), iVar6, iVar11);
										if (iVar5 < iVar11)
											goto LAB_6fb18538;
									}
									iVar11 = 0;
									pDVar8 = SKILLS_GetSkillById(pDVar4, iVar6, 0xffffffff);
									if (pDVar8 != nullptr)
									{
										iVar11 = SKILLS_GetSkillLevel(pDVar4, pDVar8, 0);
									}
									iVar5 = (int)*psVar1;
									if (((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar5)) ||
									    (iVar5 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 +
									                            iVar5 * 0x23c),
									        iVar5 < 1))
									{
										iVar5 = 0x14;
									}
									if (((iVar11 <= iVar5) &&
									        ((pDVar4 = CUNIT_GetPlayer(), uVar9 = extraout_ECX, pDVar4 == nullptr || (iVar11 = STATES_CheckState(pDVar4, 0x36), uVar9 = extraout_ECX_00, iVar11 == 0)))) &&
									    (dword_6FBB983C == 0))
									{
										sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar9 >> 8), 0x3b), (short)iVar6);
										dword_6FBB983C = 0;
									}
								LAB_6fb18538:
									dword_6FBB9638[iStack_14] = 0;
									dword_6FBB9438[iStack_14] = 0;
									pSMSGHANDLER_PARAMS->bUseResult = 1;
									pSMSGHANDLER_PARAMS->lResult = 0;
									SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
									return;
								}
							}
						}
						if (dword_6FBB9638[iStack_14] != -1)
						{
							dword_6FBB9638[iStack_14] = 0;
							dword_6FBB9438[iStack_14] = 0;
						}
					}
					iStack_14 = iStack_14 + 1;
					iVar6 = SKILLS_GetPlayerSkillCount(iVar11);
				} while (iStack_14 < iVar6);
			}
		}
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	dword_6FBB9838 = 0;
	if (dword_6FB8CFF8 == 1)
	{
		iVar11 = (gnScreenWidth - dword_6FBBA748) + -0x95;
	}
	else if (dword_6FB8CFF8 == 2)
	{
		iVar11 = (gnScreenWidth - dword_6FBBA748) + -0xdc;
	}
	else
	{
		if (dword_6FB8CFF8 != 3)
			goto LAB_6fb1822f;
		iVar11 = (gnScreenWidth - dword_6FBBA748) + -0x131;
	}
	iVar10 = dword_6FBBA74C + -0x3f + gnScreenHeight;
	iVar5 = sub_6FB57BC0();
	iVar6 = sub_6FB57BD0();
	if ((((iVar11 <= iVar5) && (iVar5 <= iVar11 + 0x22)) && (iVar10 + -0x22 <= iVar6)) &&
	    (iVar6 <= iVar10))
	{
		sub_6FB23260(4, 2, 0);
	}
LAB_6fb1822f:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB18580
void __cdecl sub_6FB18580()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;

	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		iVar3 = 0;
		while (true)
		{
			iVar2 = SKILLS_GetPlayerSkillCount(pDVar1->dwClassId);
			if (iVar2 <= iVar3)
				break;
			if (dword_6FBB9638[iVar3] == 1)
			{
				dword_6FBB9638[iVar3] = 0;
			}
			iVar3 = iVar3 + 1;
		}
	}
}

//D2Client.0x6FB185C0
void __cdecl sub_6FB185C0()
{
	D2CellFileStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;

	gpCellFile_6FBB9D74 = sub_6FB20100("Spells\\Skillicon");
	pDVar1 = sub_6FB20100(str_6FB8D0CC + (uint32_t)byte_6FBA7894 * 0x22);
	*(D2CellFileStrc**)((int)&dword_6FB8D0C8 + (uint32_t)byte_6FBA7894 * 0x22) = pDVar1;
	puVar3 = &dword_6FBB9C78;
	for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBB9D30;
	for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBB9858;
	for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBB9CF0;
	for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	puVar3 = &dword_6FBB9898;
	for (iVar2 = 0xf1; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint8_t*)puVar3 = 0;
	puVar3 = &dword_6FBB9B68;
	for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	byte_6FBB9CB8 = 0;
	byte_6FBB9CBC = 0;
	byte_6FBB9CC0 = 0;
	byte_6FBB9CC4 = 0;
}

//D2Client.0x6FB18680
void __cdecl sub_6FB18680()
{
	D2CellFileStrc* pDVar1;
	uint32_t* puVar2;

	if (gpCellFile_6FBB9D74 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB9D74);
		gpCellFile_6FBB9D74 = nullptr;
	}
	pDVar1 = *(D2CellFileStrc**)((int)&dword_6FB8D0C8 + (uint32_t)byte_6FBA7894 * 0x22);
	if (pDVar1 != nullptr)
	{
		CLIENT_FreeCellFile(pDVar1);
		*(uint32_t*)((int)&dword_6FB8D0C8 + (uint32_t)byte_6FBA7894 * 0x22) = 0;
	}
	puVar2 = &dword_6FB8D0C8;
	do
	{
		if ((D2CellFileStrc*)*puVar2 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar2);
			*puVar2 = 0;
		}
		puVar2 = (uint32_t*)((int)puVar2 + 0x22);
	} while ((int)puVar2 < (int)&tbl_6FB8D1B6);
}

//D2Client.0x6FB18700
D2CellFileStrc* __fastcall sub_6FB18700(short* a1)
{
	int iVar1;
	int iVar2;
	D2CellFileStrc* pDVar3;

	if (a1 == nullptr)
	{
		return *(D2CellFileStrc**)((int)&dword_6FB8D0C8 + (uint32_t)byte_6FBA7894 * 0x22);
	}
	iVar2 = SKILLS_GetClassIdFromSkillId((int)*a1);
	if ((-1 < iVar2) && (iVar2 < 7))
	{
		iVar1 = iVar2 * 0x22;
		if (*(int*)((int)&dword_6FB8D0C8 + iVar2 * 0x22) == 0)
		{
			pDVar3 = sub_6FB20100(str_6FB8D0CC + iVar1);
			*(D2CellFileStrc**)((int)&dword_6FB8D0C8 + iVar1) = pDVar3;
		}
		return *(D2CellFileStrc**)((int)&dword_6FB8D0C8 + iVar1);
	}
	return gpCellFile_6FBB9D74;
}

//D2Client.0x6FB18760
void __fastcall sub_6FB18760(int a1)
{
	dword_6FBB9D78 = a1;
}

//D2Client.0x6FB18770
int __fastcall sub_6FB18770(D2UnitStrc* pUnit, D2SkillStrc* pSkill)
{
	int iVar1;

	iVar1 = sub_6FB4DA80(pUnit, pSkill);
	if (iVar1 != 0)
	{
		return (-(uint32_t)(iVar1 != 6) & 0xfffffffd) + 4;
	}
	return 0;
}

//D2Client.0x6FB18790
void __fastcall sub_6FB18790(short* a1, int a22, int a3, int a4, int a5)
{
	short index;
	short index_00;
	int iVar1;
	int iVar2;
	Unicode* a2;
	Unicode* pUVar3;
	int local_228;
	CHAR aCStack_220[12];
	Unicode aUStack_214[10];
	Unicode aUStack_200[256];

	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	if ((((iVar1 < a4) || (a4 + 0x30 < iVar1)) || (iVar2 < a5 + -0x30)) ||
	    (a5 < iVar2))
	{
		local_228 = 1;
	}
	else
	{
		local_228 = a22;
		if (a22 != 1)
		{
			local_228 = 0;
		}
	}
	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	if (((a4 <= iVar1) && (iVar1 <= a4 + 0x30)) &&
	    ((a5 + -0x30 <= iVar2 && (iVar2 <= a5))))
	{
		a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		index = sub_6FB0A440((int)*a1, 0);
		index_00 = sub_6FB0A440((int)*a1, 1);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index_00));
		Unicode::strcpy(aUStack_200, pUVar3);
		Unicode::strcat(aUStack_200, a2);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x105c));
		Unicode::strcat(aUStack_200, pUVar3);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat(aUStack_200, pUVar3);
		wsprintfA(aCStack_220, "%i", a3);
		Unicode::toUnicode(aUStack_214, aCStack_220, 9);
		Unicode::strcat(aUStack_200, aUStack_214);
		Unicode::strcat(aUStack_200, a2);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		Unicode::strcat(aUStack_200, pUVar3);
		D2Win_10129_DrawFramedText(aUStack_200, a4, a5 + -0x32, local_228, 1);
	}
}

//D2Client.0x6FB18940
void __fastcall sub_6FB18940(short* a1, int a2, uint32_t a3, uint32_t a4, int a5, int a6)
{
	short sVar1;
	int iVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;

	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	if ((((iVar2 < a5) || (a5 + 0x30 < iVar2)) || (iVar3 < a6 + -0x30)) ||
	    (a6 < iVar3))
	{
		uVar5 = 1;
	}
	else
	{
		uVar5 = (uint32_t)(a2 == 1);
	}
	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	if (((a5 <= iVar2) && (iVar2 <= a5 + 0x30)) &&
	    ((a6 + -0x30 <= iVar3 && (iVar3 <= a6))))
	{
		sVar1 = *a1;
		pDVar4 = CUNIT_GetPlayer();
		sub_6FB15850(pDVar4, (int)sVar1, a3, a4, uVar5, a5, a6);
	}
}

//D2Client.0x6FB189E0
void __fastcall sub_6FB189E0(void* a1, int a2, int a3, int a4)
{
	uint32_t uVar1;
	uint8_t* puVar2;
	uint16_t* puVar3;
	int iVar4;

	uVar1 = sub_6FAD4B60((int)a1, 1);
	if ((short)uVar1 != -1)
	{
		if ((byte_6FBB9D70 & 1) == 0)
		{
			byte_6FBB9D70 = byte_6FBB9D70 | 1;
			puVar2 = byte_6FBB9CC8;
			iVar4 = 0x10;
			do
			{
				memset((Unicode*)puVar2, 0, sizeof(Unicode));
				puVar2 = (uint8_t*)((int)puVar2 + 2);
				iVar4 = iVar4 + -1;
			} while (iVar4 != 0);
			atexit(sub_6FB18AB0);
		}
		puVar2 = (uint8_t*)sub_6FAD56B0((int)a1, 1);
		iVar4 = D2Win_10121_GetTextWidth((Unicode*)puVar2);
		if (0x28 < iVar4)
		{
			Unicode::strncpy((Unicode*)byte_6FBB9CC8, (Unicode*)puVar2, 0x10);
			puVar2 = byte_6FBB9CC8;
			iVar4 = Unicode::strlen((Unicode*)byte_6FBB9CC8);
			puVar3 = (uint16_t*)(byte_6FBB9CC8 + iVar4 * 2);
			do
			{
				puVar3 = puVar3 + -1;
				*puVar3 = 0;
				iVar4 = D2Win_10121_GetTextWidth((Unicode*)byte_6FBB9CC8);
			} while (0x28 < iVar4);
		}
		if (0xd < iVar4)
		{
			a2 = a2 + (0xd - iVar4);
		}
		D2Win_10117_DrawText((Unicode*)puVar2, a2, a3, a4, 0);
	}
}

//D2Client.0x6FB18AB0
void __cdecl sub_6FB18AB0()
{
	return;
}

//D2Client.0x6FB18AC0
void __fastcall sub_6FB18AC0(D2CellFileStrc* pCellFile2, short* a22, int a3, int a4, int a5, char* a6, int a7, int a8)
{
	uint8_t bVar1;
	D2InventoryStrc* pInventory;
	int iVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	D2UnitStrc* pDVar6;
	uint32_t uVar7;
	char* a2;
	Unicode* pUVar8;
	D2GfxDataStrc* pDVar9;
	char acStack_78[16];
	Unicode aUStack_68[16];
	D2GfxDataStrc local_48;

	iVar2 = (int)*a22;
	if ((((-1 < iVar2) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar3 + 0xba0))) &&
	        (iVar2 = *(int*)(iVar3 + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
	    (((iVar2 = (int)*(short*)(iVar2 + 0x194), -1 < iVar2 && (iVar2 < *(int*)(iVar3 + 0xb94))) &&
	        (iVar2 = iVar2 * 0x120 + *(int*)(iVar3 + 0xb8c), iVar2 != 0))))
	{
		bVar1 = *(uint8_t*)(iVar2 + 7);
		iVar2 = sub_6FB57BC0();
		iVar3 = sub_6FB57BD0();
		if ((((int)a6 <= iVar2) && (iVar2 <= (int)(a6 + 0x30))) &&
		    ((a7 + -0x30 <= iVar3 && (iVar3 <= a7))))
		{
			if (a5 == 0)
			{
				a5 = 0;
			}
			else if (a5 != 1)
			{
				a5 = (-(uint32_t)(a5 != 4) & 0xfffffffd) + 4;
			}
		}
		pDVar9 = &local_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar9->pCurrentCell = nullptr;
			pDVar9 = (D2GfxDataStrc*)&pDVar9->pCellFile;
		}
		local_48.nDirection = 0;
		local_48.pCellFile = pCellFile2;
		local_48.nFrame = (uint32_t)bVar1;
		TEXTURE_CelDrawColor(&local_48, (int)a6, a7, 0xffffffff, DRAWMODE_NORMAL, a5);
		if (a8 == 0)
		{
			sub_6FB190C0(a22, a3, (int)(a6), a7);
		}
		else
		{
			sub_6FB18D50(a22, a3, (int)(a6), a7);
		}
		pDVar4 = CUNIT_GetPlayer();
		if ((pDVar4 != nullptr) &&
		    (pInventory = pDVar4->pInventory, pInventory != nullptr))
		{
			if (*a22 == 2)
			{
				pDVar4 = INVENTORY_GetLeftHandWeapon(pInventory);
				if (((pDVar4 != nullptr) && (iVar2 = ITEMS_CheckIfThrowable(pDVar4), iVar2 != 0)) && (uVar7 = ITEMS_CheckIfStackable(pDVar4), uVar7 != 0))
				{
					a4 = STATLIST_UnitGetStatValue(pDVar4, 0x46, 0);
				}
			}
			else if (*a22 == 4)
			{
				pDVar5 = INVENTORY_GetLeftHandWeapon(pInventory);
				pDVar4 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
				pDVar6 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
				if (pDVar5 == pDVar4)
				{
					pDVar4 = pDVar6;
				}
				if ((((pDVar4 != nullptr) &&
				         (iVar2 = ITEMS_CheckItemTypeId(pDVar4, 0x2d), iVar2 != 0)) &&
				        (iVar2 = ITEMS_CheckIfThrowable(pDVar4), iVar2 != 0)) &&
				    (uVar7 = ITEMS_CheckIfStackable(pDVar4), uVar7 != 0))
				{
					a4 = STATLIST_UnitGetStatValue(pDVar4, 0x46, 0);
				}
			}
		}
		if (0 < a4)
		{
			iVar2 = 0x10;
			a2 = _itoa(a4, acStack_78, 10);
			Unicode::toUnicode(aUStack_68, a2, iVar2);
			iVar2 = Unicode::strlen(aUStack_68);
			iVar3 = D2Win_10121_GetTextWidth(aUStack_68);
			if (0x28 < iVar3)
			{
				pUVar8 = aUStack_68 + iVar2;
				do
				{
					pUVar8->ch = 0;
					pUVar8 = pUVar8 + -1;
					iVar2 = D2Win_10121_GetTextWidth(aUStack_68);
				} while (0x28 < iVar2);
			}
			D2Win_10121_GetTextWidth(aUStack_68);
			D2Win_10117_DrawText(aUStack_68, (int)(a6 + 4), a7 + -1, 3, 0);
		}
	}
}

//D2Client.0x6FB18D50
void __fastcall sub_6FB18D50(short* a1, int a2, int a3, int a4)
{
	if ((((dword_6FBB9CF0 == *a1) && (dword_6FBB9D30 == a2)) && (dword_6FBB9CF0 != -1)) &&
	    (dword_6FBB9858 == 1))
	{
		sub_6FB189E0((void*)0xe, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9CF4 == *a1) && (dword_6FBB9D34 == a2)) &&
	    ((dword_6FBB9CF4 != -1 && (dword_6FBB985C == 1))))
	{
		sub_6FB189E0((void*)0xf, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9CF8 == *a1) && (dword_6FBB9D38 == a2)) &&
	    ((dword_6FBB9CF8 != -1 && (dword_6FBB9860 == 1))))
	{
		sub_6FB189E0((void*)0x10, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9CFC == *a1) && (dword_6FBB9D3C == a2)) && (dword_6FBB9CFC != -1)) &&
	    (dword_6FBB9864 == 1))
	{
		sub_6FB189E0((void*)0x11, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D00 == *a1) && (dword_6FBB9D40 == a2)) &&
	    ((dword_6FBB9D00 != -1 && (dword_6FBB9868 == 1))))
	{
		sub_6FB189E0((void*)0x12, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D04 == *a1) && (dword_6FBB9D44 == a2)) &&
	    ((dword_6FBB9D04 != -1 && (dword_6FBB986C == 1))))
	{
		sub_6FB189E0((void*)0x13, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D08 == *a1) && (dword_6FBB9D48 == a2)) && (dword_6FBB9D08 != -1)) &&
	    (dword_6FBB9870 == 1))
	{
		sub_6FB189E0((void*)0x14, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D0C == *a1) && (dword_6FBB9D4C == a2)) &&
	    ((dword_6FBB9D0C != -1 && (dword_6FBB9874 == 1))))
	{
		sub_6FB189E0((void*)0x15, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D10 == *a1) && (dword_6FBB9D50 == a2)) &&
	    ((dword_6FBB9D10 != -1 && (dword_6FBB9878 == 1))))
	{
		sub_6FB189E0((void*)0x2e, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D14 == *a1) && (dword_6FBB9D54 == a2)) && (dword_6FBB9D14 != -1)) &&
	    (dword_6FBB987C == 1))
	{
		sub_6FB189E0((void*)0x2f, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D18 == *a1) && (dword_6FBB9D58 == a2)) &&
	    ((dword_6FBB9D18 != -1 && (dword_6FBB9880 == 1))))
	{
		sub_6FB189E0((void*)0x30, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D1C == *a1) && (dword_6FBB9D5C == a2)) &&
	    ((dword_6FBB9D1C != -1 && (dword_6FBB9884 == 1))))
	{
		sub_6FB189E0((void*)0x31, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D20 == *a1) && (dword_6FBB9D60 == a2)) && (dword_6FBB9D20 != -1)) &&
	    (dword_6FBB9888 == 1))
	{
		sub_6FB189E0((void*)0x32, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D24 == *a1) && (dword_6FBB9D64 == a2)) &&
	    ((dword_6FBB9D24 != -1 && (dword_6FBB988C == 1))))
	{
		sub_6FB189E0((void*)0x33, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D28 == *a1) && (dword_6FBB9D68 == a2)) &&
	    ((dword_6FBB9D28 != -1 && (dword_6FBB9890 == 1))))
	{
		sub_6FB189E0((void*)0x34, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D2C == *a1) && (dword_6FBB9D6C == a2)) && (dword_6FBB9D2C != -1)) &&
	    (dword_6FBB9894 == 1))
	{
		sub_6FB189E0((void*)0x35, a3 + 0x22, a4 + -0x23, 4);
	}
}

//D2Client.0x6FB190C0
void __fastcall sub_6FB190C0(short* a1, int a2, int a3, int a4)
{
	if ((((dword_6FBB9CF0 == *a1) && (dword_6FBB9D30 == a2)) && (dword_6FBB9CF0 != -1)) &&
	    (dword_6FBB9858 == 0))
	{
		sub_6FB189E0((void*)0xe, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9CF4 == *a1) && (dword_6FBB9D34 == a2)) &&
	    ((dword_6FBB9CF4 != -1 && (dword_6FBB985C == 0))))
	{
		sub_6FB189E0((void*)0xf, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9CF8 == *a1) && (dword_6FBB9D38 == a2)) &&
	    ((dword_6FBB9CF8 != -1 && (dword_6FBB9860 == 0))))
	{
		sub_6FB189E0((void*)0x10, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9CFC == *a1) && (dword_6FBB9D3C == a2)) && (dword_6FBB9CFC != -1)) &&
	    (dword_6FBB9864 == 0))
	{
		sub_6FB189E0((void*)0x11, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D00 == *a1) && (dword_6FBB9D40 == a2)) &&
	    ((dword_6FBB9D00 != -1 && (dword_6FBB9868 == 0))))
	{
		sub_6FB189E0((void*)0x12, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D04 == *a1) && (dword_6FBB9D44 == a2)) &&
	    ((dword_6FBB9D04 != -1 && (dword_6FBB986C == 0))))
	{
		sub_6FB189E0((void*)0x13, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D08 == *a1) && (dword_6FBB9D48 == a2)) && (dword_6FBB9D08 != -1)) &&
	    (dword_6FBB9870 == 0))
	{
		sub_6FB189E0((void*)0x14, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D0C == *a1) && (dword_6FBB9D4C == a2)) &&
	    ((dword_6FBB9D0C != -1 && (dword_6FBB9874 == 0))))
	{
		sub_6FB189E0((void*)0x15, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D10 == *a1) && (dword_6FBB9D50 == a2)) &&
	    ((dword_6FBB9D10 != -1 && (dword_6FBB9878 == 0))))
	{
		sub_6FB189E0((void*)0x2e, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D14 == *a1) && (dword_6FBB9D54 == a2)) && (dword_6FBB9D14 != -1)) &&
	    (dword_6FBB987C == 0))
	{
		sub_6FB189E0((void*)0x2f, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D18 == *a1) && (dword_6FBB9D58 == a2)) &&
	    ((dword_6FBB9D18 != -1 && (dword_6FBB9880 == 0))))
	{
		sub_6FB189E0((void*)0x30, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D1C == *a1) && (dword_6FBB9D5C == a2)) &&
	    ((dword_6FBB9D1C != -1 && (dword_6FBB9884 == 0))))
	{
		sub_6FB189E0((void*)0x31, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D20 == *a1) && (dword_6FBB9D60 == a2)) && (dword_6FBB9D20 != -1)) &&
	    (dword_6FBB9888 == 0))
	{
		sub_6FB189E0((void*)0x32, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D24 == *a1) && (dword_6FBB9D64 == a2)) &&
	    ((dword_6FBB9D24 != -1 && (dword_6FBB988C == 0))))
	{
		sub_6FB189E0((void*)0x33, a3 + 0x22, a4 + -0x23, 4);
	}
	if (((dword_6FBB9D28 == *a1) && (dword_6FBB9D68 == a2)) &&
	    ((dword_6FBB9D28 != -1 && (dword_6FBB9890 == 0))))
	{
		sub_6FB189E0((void*)0x34, a3 + 0x22, a4 + -0x23, 4);
	}
	if ((((dword_6FBB9D2C == *a1) && (dword_6FBB9D6C == a2)) && (dword_6FBB9D2C != -1)) &&
	    (dword_6FBB9894 == 0))
	{
		sub_6FB189E0((void*)0x35, a3 + 0x22, a4 + -0x23, 4);
	}
}

//D2Client.0x6FB19430
void __fastcall sub_6FB19430(D2SkillsTxt* pSkillsTxtRecord, int a22, int a3, int a4, int a5, int a6, int a7)
{
	uint8_t bVar1;
	int iVar2;
	D2CellFileStrc* pDVar3;
	int iVar4;
	char* a2;
	Unicode* pUVar5;
	D2GfxDataStrc* pDVar6;
	D2CellFileStrc* pDStack_80;
	Unicode aUStack_78[16];
	D2GfxDataStrc DStack_58;
	char acStack_10[16];

	iVar2 = SKILLS_GetClassIdFromSkillId((int)pSkillsTxtRecord->nSkillId);
	if ((iVar2 < 0) || (6 < iVar2))
	{
		pDStack_80 = gpCellFile_6FBB9D74;
	}
	else
	{
		iVar4 = iVar2 * 0x22;
		if (*(int*)((int)&dword_6FB8D0C8 + iVar2 * 0x22) == 0)
		{
			pDVar3 = sub_6FB20100(str_6FB8D0CC + iVar4);
			*(D2CellFileStrc**)((int)&dword_6FB8D0C8 + iVar4) = pDVar3;
		}
		pDStack_80 = *(D2CellFileStrc**)((int)&dword_6FB8D0C8 + iVar4);
	}
	iVar2 = (int)pSkillsTxtRecord->nSkillId;
	if (((((-1 < iVar2) && (iVar4 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar4 + 0xba0))) &&
	         (iVar2 = *(int*)(iVar4 + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
	        ((iVar2 = (int)*(short*)(iVar2 + 0x194), -1 < iVar2 && (iVar2 < *(int*)(iVar4 + 0xb94))))) &&
	    (iVar2 = iVar2 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar2 != 0))
	{
		bVar1 = *(uint8_t*)(iVar2 + 7);
		iVar2 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		if (((a5 <= iVar2) && (iVar2 <= a5 + 0x30)) &&
		    ((a6 + -0x30 <= iVar4 && (iVar4 <= a6))))
		{
			if (a4 == 0)
			{
				a4 = 0;
			}
			else if (a4 != 1)
			{
				a4 = (-(uint32_t)(a4 != 4) & 0xfffffffd) + 4;
			}
		}
		pDVar6 = &DStack_58;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar6->pCurrentCell = nullptr;
			pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
		}
		DStack_58.pCellFile = pDStack_80;
		DStack_58.nDirection = 0;
		DStack_58.nFrame = (uint32_t)bVar1;
		TEXTURE_CelDrawColor(&DStack_58, a5, a6, 0xffffffff, DRAWMODE_NORMAL, a4);
		if (a7 == 0)
		{
			sub_6FB190C0(&pSkillsTxtRecord->nSkillId, a22, a5, a6);
		}
		else
		{
			sub_6FB18D50(&pSkillsTxtRecord->nSkillId, a22, a5, a6);
		}
		if (0 < a3)
		{
			iVar2 = 0x10;
			a2 = _itoa(a3, acStack_10, 10);
			Unicode::toUnicode(aUStack_78, a2, iVar2);
			iVar2 = Unicode::strlen(aUStack_78);
			iVar4 = D2Win_10121_GetTextWidth(aUStack_78);
			if (0x28 < iVar4)
			{
				pUVar5 = aUStack_78 + iVar2;
				do
				{
					pUVar5->ch = 0;
					pUVar5 = pUVar5 + -1;
					iVar2 = D2Win_10121_GetTextWidth(aUStack_78);
				} while (0x28 < iVar2);
			}
			D2Win_10121_GetTextWidth(aUStack_78);
			D2Win_10117_DrawText(aUStack_78, a5 + 4, a6 + -1, 3, 0);
		}
	}
}

//D2Client.0x6FB19660
void __cdecl sub_6FB19660()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	puVar3 = &dword_6FBB9898;
	for (iVar2 = 0xf1; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint8_t*)puVar3 = 0;
	puVar3 = &dword_6FBB9B68;
	for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0xffffffff;
		puVar3 = puVar3 + 1;
	}
	if (dword_6FBB9D78 == 0)
	{
	LAB_6fb196b0:
		iVar6 = 0;
		iVar5 = 0;
		iVar4 = 0;
		(*(uint8_t*)((uint8_t*)&dword_6FBB9C58 + 0)) = 0;
		iVar2 = gnScreenWidth + -0x80;
		pDVar1 = CUNIT_GetPlayer();
		sub_6FB19720(pDVar1, iVar2, iVar4, iVar5, iVar6);
		if (dword_6FBB9D78 == 0)
			goto LAB_6fb196fc;
	}
	else
	{
		iVar5 = 0;
		iVar4 = 0;
		iVar2 = 1;
		(*(uint8_t*)((uint8_t*)&dword_6FBB9C58 + 0)) = 0;
		pDVar1 = CUNIT_GetPlayer();
		sub_6FB19720(pDVar1, 0x50, iVar2, iVar4, iVar5);
		if (dword_6FBB9D78 == 0)
			goto LAB_6fb196b0;
	}
	iVar5 = 0;
	iVar4 = 1;
	iVar2 = 1;
	pDVar1 = CUNIT_GetPlayer();
	sub_6FB19720(pDVar1, 0x50, iVar2, iVar4, iVar5);
	if (dword_6FBB9D78 != 0)
	{
		return;
	}
LAB_6fb196fc:
	iVar6 = 0;
	iVar5 = 1;
	iVar4 = 0;
	iVar2 = gnScreenWidth + -0x80;
	pDVar1 = CUNIT_GetPlayer();
	sub_6FB19720(pDVar1, iVar2, iVar4, iVar5, iVar6);
}

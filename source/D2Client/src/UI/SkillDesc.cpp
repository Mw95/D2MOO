#include "UI/SkillDesc.h"

#include "Core/WinMain.h"
#include "Game/Game.h"
#include "Game/PalShift.h"
#include "UI/Automap.h"
#include "UI/Inv.h"
#include "UI/ShowItems.h"
#include "UI/SkillsTree.h"
#include "UI/SpellSel.h"
#include "UI/Trade.h"
#include "Unit/CUnit.h"
#include "Unit/PlrSkills.h"

//D2Client.0x6FB8CD00
uint8_t byte_6FB8CD00[144] = {0, 0, 0, 0, 0x70, 0xC2, 0xB0, 0x6F, 0x40, 0xCD, 0xB0, 0x6F, 0x30, 0xD3, 0xB0, 0x6F, 0x20, 0xD9, 0xB0, 0x6F, 0xC0, 0xDE, 0xB0, 0x6F, 0xE0, 0xAC, 0xB0, 0x6F, 0xC0, 0xBE, 0xB0, 0x6F, 0, 0xE8, 0xB0, 0x6F, 0xB0, 0xEA, 0xB0, 0x6F, 0x40, 0xED, 0xB0, 0x6F, 0x80, 0xF0, 0xB0, 0x6F, 0, 0xF7, 0xB0, 0x6F, 0xB0, 0xE7, 0xB0, 0x6F, 0x50, 0xFA, 0xB0, 0x6F, 0x60, 0xFC, 0xB0, 0x6F, 0x10, 0, 0xB1, 0x6F, 0x40, 5, 0xB1, 0x6F, 0xF0, 8, 0xB1, 0x6F, 0x60, 0xCA, 0xB0, 0x6F, 0x30, 0xC9, 0xB0, 0x6F, 0x90, 0xCE, 0xB0, 0x6F, 0xB0, 0xDA, 0xB0, 0x6F, 0x40, 0xE4, 0xB0, 0x6F, 0x80, 0xE1, 0xB0, 0x6F};
//D2Client.0x6FB8CD90
uint8_t byte_6FB8CD90[72] = {0, 0, 0, 0, 0xA0, 0xA4, 0xB0, 0x6F, 0x30, 0xA7, 0xB0, 0x6F, 0xB0, 0xAA, 0xB0, 0x6F, 0xC0, 0xAB, 0xB0, 0x6F, 0x10, 0xA6, 0xB0, 0x6F};
//D2Client.0x6FB8CDD8
uint8_t byte_6FB8CDD8[4] = {0xA2};
//D2Client.0x6FB8CDDC
int32_t dword_6FB8CDDC = 93;
//D2Client.0x6FB8CDE0
uint8_t byte_6FB8CDE0[68] = {2, 1, 0, 0, 0xA2, 0, 0, 0, 0x65, 0, 0, 0, 2, 1, 0, 0, 7, 1, 0, 0, 0x62, 0, 0, 0, 0x33, 1, 0, 0, 0xA2, 0, 0, 0, 0xA0, 0, 0, 0, 0xE, 1, 0, 0, 0xA2, 0, 0, 0, 0xA3, 0, 0, 0, 0xE, 1, 0, 0, 0xE, 1, 0, 0, 0xA0, 0, 0, 0, 0x36, 1, 0, 0, 0xA2};
//D2Client.0x6FB8CE24
int32_t dword_6FB8CE24 = 117;
//D2Client.0x6FBB9430
int32_t dword_6FBB9430;
//D2Client.0x6FBB9434
char byte_6FBB9434;

//D2Client.0x6FB0BEC0
void __fastcall sub_6FB0BEC0(D2UnitStrc* pUnit, D2SkillStrc* pSkill, short* a3, int a4, int a5, int a6, int a7)
{
	uint8_t bVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	Unicode* pThis;
	uint32_t uVar5;
	uint64_t uVar6;
	int iVar7;
	uint32_t local_7c;
	uint32_t local_78;
	D2SkillsTxt* local_74;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	D2SkillsTxt* pDStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if (pSkill == nullptr)
	{
		return;
	}
	if (a3 == nullptr)
	{
		return;
	}
	iVar3 = (int)*a3;
	if (iVar3 < 0)
	{
		return;
	}
	iVar7 = *(int*)((uint8_t*)&sgptDataTables);
	if (*(int*)(iVar7 + 0xba0) <= iVar3)
	{
		return;
	}
	iVar3 = *(int*)(iVar7 + 0xb98) + iVar3 * 0x23c;
	if (iVar3 == 0)
	{
		return;
	}
	iVar3 = (int)*(short*)(iVar3 + 0x194);
	if (iVar3 < 0)
	{
		return;
	}
	if (*(int*)(iVar7 + 0xb94) <= iVar3)
	{
		return;
	}
	iVar3 = iVar3 * 0x120 + *(int*)(iVar7 + 0xb8c);
	if (iVar3 == 0)
	{
		return;
	}
	local_7c = 0;
	local_78 = 0;
	local_74 = nullptr;
	iVar7 = a4;
	iVar4 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	iStack_6c = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar3 + 0x18), iVar4, iVar7);
	iVar7 = a4;
	iVar4 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	iVar3 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar3 + 0x1c), iVar4, iVar7);
	sub_6FB0B2C0(pUnit, (uint32_t)&local_7c, (int*)(&local_78), (uint32_t*)(&local_74), iStack_6c, iVar3, pSkill, 0x80, 0, 0);
	sub_6FB0B6F0(pUnit, (int*)&local_7c, (int*)&local_78, (uint32_t*)(&local_74), nullptr, pSkill);
	bVar1 = *(uint8_t*)((int)a3 + 0x1a5);
	if (bVar1 == 0x80)
		goto LAB_6fb0c0da;
	uVar5 = (uint32_t)bVar1;
	if ((int)local_7c < 0x100001)
	{
		if (uVar5 < 0x10001)
		{
			local_7c = (int)(uVar5 * local_7c + ((int)(uVar5 * local_7c) >> 0x1f & 0x7fU)) >> 7;
		}
		else
		{
			if ((bVar1 & 0xf0) < 0x800)
				goto LAB_6fb0c038;
			local_7c = ((int)uVar5 >> 7) * local_7c;
		}
	}
	else if ((int)(local_7c & 0xfffffff0) < 0x800)
	{
	LAB_6fb0c038:
		uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)local_7c),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)local_7c) >> 0x20),
		    0x80, 0);
		local_7c = (uint32_t)uVar6;
	}
	else
	{
		local_7c = ((int)(local_7c + ((int)local_7c >> 0x1f & 0x7fU)) >> 7) * uVar5;
	}
	if ((int)local_78 < 0x100001)
	{
		if (uVar5 < 0x10001)
		{
			local_78 = (int)(uVar5 * local_78 + ((int)(uVar5 * local_78) >> 0x1f & 0x7fU)) >> 7;
			goto LAB_6fb0c0da;
		}
		if (0x7ff < (bVar1 & 0xf0))
		{
			local_78 = ((int)uVar5 >> 7) * local_78;
			goto LAB_6fb0c0da;
		}
	}
	else if (0x7ff < (int)(local_78 & 0xfffffff0))
	{
		local_78 = ((int)(local_78 + ((int)local_78 >> 0x1f & 0x7fU)) >> 7) * uVar5;
		goto LAB_6fb0c0da;
	}
	uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)local_78),
	    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)local_78) >> 0x20), 0x80,
	    0);
	local_78 = (uint32_t)uVar6;
LAB_6fb0c0da:
	iVar3 = SKILLS_GetMinPhysDamage(pUnit, (int)*a3, a4, 0);
	local_7c = local_7c + (iVar3 >> 8);
	iVar3 = SKILLS_GetMaxPhysDamage(pUnit, (int)*a3, a4, 0);
	local_78 = local_78 + (iVar3 >> 8);
	iVar3 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
	local_7c = local_7c + (iVar3 >> 8);
	iVar3 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, a4, 1);
	uVar2 = local_7c;
	pDStack_64 = local_74;
	local_78 = local_78 + (iVar3 >> 8);
	uVar5 = local_78;
	if ((int)local_78 <= (int)local_7c)
	{
		uVar5 = local_7c + 1;
	}
	if (uVar2 == uVar5)
	{
		wsprintfA(aCStack_60, "%d", uVar2);
		Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
	}
	else
	{
		sub_6FB0B140((Unicode*)aUStack_40, uVar2, uVar5, 0, 1);
	}
	iStack_70 = 0;
	iStack_68 = 0;
	D2Win_10131_GetTextDimensions(aUStack_40, &iStack_70, &iStack_68);
	iStack_70 = (iStack_70 * 0xb) / 7;
	if (a7 - a5 < iStack_70)
	{
		D2Win_10127_SetFont(D2FONT_FONT6);
		a6 = a6 + -1;
	}
	else
	{
		D2Win_10127_SetFont(D2FONT_FONT16);
	}
	sub_6FACFCD0(dword_6FBBA748 + a5, gnScreenHeight + -0x1e0 + a6 + dword_6FBBA74C,
	    dword_6FBBA748 + a7, aUStack_40, pDStack_64);
}

//D2Client.0x6FB0C270
void __fastcall sub_6FB0C270(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int nSkillId;
	int* piVar3;

	if (((((pSkill != nullptr) && (a3 != nullptr)) &&
	         (iVar1 = (int)(short)*a3, -1 < iVar1)) &&
	        ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar1 < *(int*)(iVar2 + 0xba0) &&
	                                                          (iVar1 = *(int*)(iVar2 + 0xb98) + iVar1 * 0x23c, iVar1 != 0)))) &&
	    ((iVar1 = (int)*(short*)(iVar1 + 0x194), -1 < iVar1 &&
	                                                 ((iVar1 < *(int*)(iVar2 + 0xb94) &&
	                                                     (iVar1 = iVar1 * 0x120 + *(int*)(iVar2 + 0xb8c), iVar1 != 0))))))
	{
		iVar2 = UNITS_CanDualWield(pUnit);
		if (iVar2 != 0)
		{
			piVar3 = a4;
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iVar2 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x18), iVar2, (int)piVar3);
			piVar3 = a4;
			nSkillId = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iVar1 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x1c), nSkillId, (int)piVar3);
			sub_6FB0C400(pUnit, pSkill, (short*)a3, a4, 0x6fb0c3a0, iVar2, iVar1, a5, a6,
			    a7, 1);
			return;
		}
		sub_6FB0BEC0(pUnit, pSkill, (short*)a3, (int)a4, a5, a6, a7);
	}
}

//D2Client.0x6FB0C3A0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB0C3A0(int* a1, uint32_t* a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, D2UnitStrc* pUnit)
{
	D2UnitStrc* in_ECX;
	int* in_EDX;

	sub_6FB0B2C0(in_ECX, (uint32_t)in_EDX, a1, a2, a3, a4, (D2SkillStrc*)(a5), a6, pUnit, 0);
	sub_6FB0B6F0(in_ECX, in_EDX, a1, a2, pUnit, (D2SkillStrc*)(a5));
}

//D2Client.0x6FB0C400
void __fastcall sub_6FB0C400(D2UnitStrc* pUnit, D2SkillStrc* pSkill, short* a3, int* a4, int a5, uint32_t a6, int a7, int a8, int a9, int a10, int a11)
{
	D2SkillsTxt* pDVar1;
	uint32_t uVar2;
	int iVar3;
	Unicode* pUVar4;
	int iVar5;
	int iVar6;
	int iStack_f0;
	int local_ec;
	D2SkillsTxt* local_e8;
	int local_e4;
	int local_e0;
	D2SkillsTxt* local_dc;
	int local_d8;
	int local_d4;
	D2SkillsTxt* local_d0;
	int local_cc;
	int local_c8;
	D2SkillsTxt* local_c4;
	Unicode local_c0[32];
	Unicode aUStack_80[32];
	Unicode local_40[32];

	if (((pSkill == nullptr) || (a3 == nullptr)) || (a5 == 0))
	{
		return;
	}
	local_cc = 0;
	local_d4 = 0;
	local_e8 = nullptr;
	local_dc = nullptr;
	if (a11 != 0)
	{
		sub_6FB0C840(pUnit, a3, a4, &local_cc, &local_d4, (uint32_t*)(&local_e8));
	}
	local_dc = local_e8;
	uVar2 = (uint32_t) * (uint8_t*)((int)a3 + 0x1a5);
	local_e0 = 0;
	local_e4 = 0;
	local_d8 = 0;
	local_ec = 0;
	sub_6FB0A7D0(pUnit, (uint8_t*)&local_e0, (uint32_t*)(&local_e4), (uint32_t)(&local_e8), (uint32_t*)(&local_d8), (uint32_t*)(&local_ec), (uint32_t)(&local_dc),
	    pSkill, (code*)(a5), a6, a7);
	if ((local_e0 != 0) && (local_e4 != 0))
	{
		local_e0 = local_cc + ((int)(local_e0 * uVar2 + ((int)(local_e0 * uVar2) >> 0x1f & 0x7fU)) >> 7);
		local_e4 = ((int)(local_e4 * uVar2 + ((int)(local_e4 * uVar2) >> 0x1f & 0x7fU)) >> 7) + local_d4;
	}
	iVar6 = local_e0;
	if ((local_d8 != 0) && (local_ec != 0))
	{
		local_d8 = local_cc + ((int)(local_d8 * uVar2 + ((int)(local_d8 * uVar2) >> 0x1f & 0x7fU)) >> 7);
		local_ec = ((int)(local_ec * uVar2 + ((int)(local_ec * uVar2) >> 0x1f & 0x7fU)) >> 7) + local_d4;
	}
	iVar5 = local_d8;
	if ((local_e0 == 0) && (local_e4 == 0))
	{
		local_c8 = a9;
		local_d0 = local_dc;
		iVar6 = local_ec;
		if (local_ec <= local_d8)
		{
			iVar6 = local_d8 + 1;
		}
		if (iVar5 == iVar6)
		{
			sub_6FB0B0F0((Unicode*)local_c0, iVar5, 0);
		}
		else
		{
			sub_6FB0B140((Unicode*)local_c0, iVar5, iVar6, 0, 1);
		}
		iStack_f0 = 0;
		local_c4 = nullptr;
		D2Win_10131_GetTextDimensions(local_c0, &iStack_f0, (int*)&local_c4);
		iStack_f0 = (iStack_f0 * 0xb) / 7;
		if (a10 - a8 < iStack_f0)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			pDVar1 = local_d0;
			iVar6 = a9 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar1 = local_d0;
			iVar6 = local_c8;
		}
	}
	else
	{
		if ((local_d8 != 0) || (local_ec != 0))
		{
			if (local_e0 == local_e4)
			{
				wsprintfA((LPSTR)local_c0, "%d", local_e0);
				Unicode::toUnicode(local_40, (char*)local_c0, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)local_40, local_e0, local_e4, 0, 1);
			}
			if (local_d8 == local_ec)
			{
				wsprintfA((LPSTR)local_c0, "%d", local_d8);
				Unicode::toUnicode(aUStack_80, (char*)local_c0, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_80, local_d8, local_ec, 0, 1);
			}
			sub_6FB0AC10((uint32_t)(local_40), (uint32_t)(aUStack_80), a8, a9, a10, local_e8, local_dc);
			return;
		}
		local_c8 = a9;
		local_c4 = local_e8;
		iVar5 = local_e4;
		if (local_e4 <= local_e0)
		{
			iVar5 = local_e0 + 1;
		}
		sub_6FB0B250((Unicode*)local_c0, iVar6, iVar5, 0);
		iStack_f0 = 0;
		local_d0 = nullptr;
		D2Win_10131_GetTextDimensions(local_c0, &iStack_f0, (int*)&local_d0);
		iStack_f0 = (iStack_f0 * 0xb) / 7;
		if (a10 - a8 < iStack_f0)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			pDVar1 = local_c4;
			iVar6 = a9 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar1 = local_c4;
			iVar6 = local_c8;
		}
	}
	sub_6FACFCD0(dword_6FBBA748 + a8, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar6,
	    dword_6FBBA748 + a10, local_c0, pDVar1);
}

//D2Client.0x6FB0C840
void __fastcall sub_6FB0C840(D2UnitStrc* pUnit, short* a2, int* a3, int* a4, int* a5, uint32_t* a6)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;

	if ((char)a2[0xee] == '\x05')
	{
		iVar1 = SKILLS_GetElementalLength(pUnit, (int)*a2, (int)a3, 1);
		*a6 = 2;
		iVar2 = SKILLS_GetMinElemDamage(pUnit, (int)*a2, (int)a3, 1);
		iVar2 = iVar1 * iVar2;
		iVar3 = SKILLS_GetMaxElemDamage(pUnit, (int)*a2, (int)a3, 1);
		iVar3 = iVar3 * iVar1;
	}
	else
	{
		iVar2 = SKILLS_GetMinElemDamage(pUnit, (int)*a2, (int)a3, 1);
		iVar3 = SKILLS_GetMaxElemDamage(pUnit, (int)*a2, (int)a3, 1);
	}
	if (a6 != nullptr)
	{
		switch ((char)a2[0xee])
		{
		case '\x01':
			uVar4 = 1;
			break;
		case '\x02':
			uVar4 = 9;
			break;
		case '\x03':
		case '\x04':
			uVar4 = 3;
			break;
		case '\x05':
			uVar4 = 2;
			break;
		default:
			goto switchD_6fb0c8cf_default;
		}
		*a6 = uVar4;
	}
switchD_6fb0c8cf_default:
	*a4 = *a4 + (iVar2 >> 8);
	*a5 = *a5 + (iVar3 >> 8);
}

//D2Client.0x6FB0C930
void __fastcall sub_6FB0C930(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int nSkillId;
	int* piVar3;

	if (((((pSkill != nullptr) && (a3 != nullptr)) &&
	         (iVar1 = (int)(short)*a3, -1 < iVar1)) &&
	        ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar1 < *(int*)(iVar2 + 0xba0) &&
	                                                          (iVar1 = *(int*)(iVar2 + 0xb98) + iVar1 * 0x23c, iVar1 != 0)))) &&
	    ((iVar1 = (int)*(short*)(iVar1 + 0x194), -1 < iVar1 &&
	                                                 ((iVar1 < *(int*)(iVar2 + 0xb94) &&
	                                                     (iVar1 = iVar1 * 0x120 + *(int*)(iVar2 + 0xb8c), iVar1 != 0))))))
	{
		iVar2 = UNITS_CanDualWield(pUnit);
		if (iVar2 != 0)
		{
			piVar3 = a4;
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iVar2 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x18), iVar2, (int)piVar3);
			piVar3 = a4;
			nSkillId = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iVar1 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x1c), nSkillId, (int)piVar3);
			sub_6FB0C400(pUnit, pSkill, (short*)a3, a4, 0x6fb0c3a0, iVar2, iVar1, a5, a6,
			    a7, 0);
			return;
		}
		sub_6FB0BEC0(pUnit, pSkill, (short*)a3, (int)a4, a5, a6, a7);
	}
}

//D2Client.0x6FB0CA60
void __fastcall sub_6FB0CA60(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	Unicode* pThis;
	int* piVar3;
	D2SkillsTxt* pDStack_7c;
	int iStack_78;
	int iStack_74;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	D2SkillsTxt* pDStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if (((((pSkill != nullptr) && (a3 != nullptr)) &&
	         (iVar1 = (int)(short)*a3, -1 < iVar1)) &&
	        ((iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar1 < *(int*)(iVar2 + 0xba0) &&
	                                                          (iVar1 = *(int*)(iVar2 + 0xb98) + iVar1 * 0x23c, iVar1 != 0)))) &&
	    ((iVar1 = (int)*(short*)(iVar1 + 0x194), -1 < iVar1 &&
	                                                 ((iVar1 < *(int*)(iVar2 + 0xb94) &&
	                                                     (iVar1 = iVar1 * 0x120 + *(int*)(iVar2 + 0xb8c), iVar1 != 0))))))
	{
		iVar2 = UNITS_CanDualWield(pUnit);
		if (iVar2 != 0)
		{
			piVar3 = a4;
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iStack_6c = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x18), iVar2, (int)piVar3);
			piVar3 = a4;
			iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
			iVar1 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x1c), iVar2, (int)piVar3);
			sub_6FB0C400(pUnit, pSkill, (short*)a3, a4, 0x6fb0c3a0, iStack_6c, iVar1, a5,
			    a6, a7, 1);
			return;
		}
		iStack_74 = 0;
		iStack_78 = 0;
		pDStack_7c = nullptr;
		piVar3 = a4;
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iStack_6c = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x18), iVar2, (int)piVar3);
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iVar1 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar1 + 0x1c), iVar2, (int)a4);
		sub_6FB0B2C0(pUnit, (uint32_t)&iStack_74, &iStack_78, (uint32_t*)(&pDStack_7c), iStack_6c, iVar1, pSkill, 0, 0, 0);
		sub_6FB0B6F0(pUnit, &iStack_74, &iStack_78, (uint32_t*)(&pDStack_7c), nullptr, pSkill);
		iVar2 = iStack_74;
		pDStack_64 = pDStack_7c;
		iVar1 = iStack_78;
		if (iStack_78 <= iStack_74)
		{
			iVar1 = iStack_74 + 1;
		}
		if (iVar2 == iVar1)
		{
			wsprintfA(aCStack_60, "%d", iVar2);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar2, iVar1, 0, 1);
		}
		iStack_70 = 0;
		iStack_68 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &iStack_70, &iStack_68);
		iStack_70 = (iStack_70 * 0xb) / 7;
		if (a7 - a5 < iStack_70)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			a6 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + a6,
		    dword_6FBBA748 + a7, aUStack_40, pDStack_64);
	}
}

//D2Client.0x6FB0CD40
void __fastcall sub_6FB0CD40(D2UnitStrc* pUnit, int a2, int a3, uint32_t a4, int a5, int a6, int a7)
{
	char cVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	Unicode* pThis;
	int iStack_68;
	int iStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if ((a2 != 0) && (a3 != 0))
	{
		cVar1 = *(char*)(a3 + 0x1a4);
		iVar4 = *(int*)(a3 + 0x1a8);
		iVar2 = STATLIST_UnitGetItemStatOrSkillStatValue(pUnit, 0x89, 0);
		iVar2 = (iVar4 << (cVar1 - 8U & 0x1f)) + iVar2;
		pThis = aUStack_40;
		iVar4 = 0x20;
		iStack_64 = a6;
		do
		{
			pThis = pThis + 1;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
		if (iVar2 == iVar2 + 1)
		{
			wsprintfA(aCStack_60, "%d", iVar2);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar2, iVar2 + 1, 0, 1);
		}
		a3 = 0;
		iStack_68 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &a3, &iStack_68);
		iVar2 = a7;
		iVar4 = a5;
		a3 = (a3 * 0xb) / 7;
		if (a7 - a5 < a3)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar3 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar3 = iStack_64;
		}
		sub_6FACFCD0(dword_6FBBA748 + iVar4, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar3,
		    dword_6FBBA748 + iVar2, aUStack_40, nullptr);
	}
}

//D2Client.0x6FB0CE90
void __fastcall sub_6FB0CE90(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int a3, int* a4, int a5, D2UnitStrc* pUnit2, int a7)
{
	short sVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	Unicode* pThis;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	D2UnitStrc* pDVar10;
	uint64_t uVar11;
	D2UnitStrc* pDStack_54;
	D2UnitStrc* local_50;
	D2SkillsTxt* local_4c;
	D2SkillStrc* local_48;
	D2UnitStrc* pDStack_44;
	Unicode aUStack_40[32];

	iVar7 = 0;
	if (pSkill == nullptr)
	{
		return;
	}
	if (a3 == 0)
	{
		return;
	}
	local_4c = nullptr;
	if (pUnit->pInventory == nullptr)
	{
		return;
	}
	local_50 = pUnit;
	local_48 = pSkill;
	pDVar2 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory);
	if (pDVar2 == nullptr)
	{
		return;
	}
	pDStack_44 = pDVar2;
	iVar3 = ITEMS_CheckIfThrowable(pDVar2);
	if (iVar3 == 0)
	{
		return;
	}
	sVar1 = ITEMS_GetStrengthBonus(pDVar2);
	if (sVar1 != 0)
	{
		iVar7 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
		iVar7 = (iVar7 * sVar1) / 100;
	}
	sVar1 = ITEMS_GetDexBonus(pDVar2);
	if (sVar1 != 0)
	{
		iVar3 = STATLIST_UnitGetStatValue(pUnit, 2, 0);
		iVar7 = iVar7 + (iVar3 * sVar1) / 100;
	}
	iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x9f, 0);
	iVar4 = STATLIST_UnitGetStatValue(pUnit, 0xa0, 0);
	iVar5 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
	iVar7 = iVar7 + iVar5;
	iVar5 = STATLIST_UnitGetStatValue(pUnit, 0x12, 0);
	pDStack_54 = (D2UnitStrc*)STATLIST_UnitGetStatValue(local_50, 0x11, 0);
	pDVar2 = local_50;
	if (iVar7 < -0x59)
	{
		iVar7 = -0x5a;
	}
	uVar9 = iVar3 + ((iVar7 + iVar5) * iVar3) / 100;
	uVar8 = 0;
	uVar6 = iVar4 + ((int)(pDStack_54->unk0x19 + iVar7 + -0x19) * iVar4) / 100;
	iVar7 = STATES_CheckState(local_50, 0x4e);
	if (iVar7 != 0)
	{
		uVar8 = SKILLS_GetWeaponMasteryBonus(pDVar2, pDStack_44, local_48, 1);
	}
	if ((int)uVar9 < 0x100001)
	{
		if ((int)uVar8 < 0x10001)
		{
			iVar7 = (int)(uVar8 * uVar9) / 100;
		}
		else if ((int)(uVar8 & 0xfffffff0) < 0x640)
		{
			uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar9),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar9) >> 0x20), 100, 0);
			iVar7 = (int)uVar11;
		}
		else
		{
			iVar7 = ((int)uVar8 / 100) * uVar9;
		}
	}
	else if ((int)(uVar9 & 0xfffffff0) < 0x640)
	{
		uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar9),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar9) >> 0x20), 100, 0);
		iVar7 = (int)uVar11;
	}
	else
	{
		iVar7 = ((int)uVar9 / 100) * uVar8;
	}
	local_50 = (D2UnitStrc*)(uVar9 + iVar7);
	if ((int)uVar6 < 0x100001)
	{
		if ((int)uVar8 < 0x10001)
		{
			iVar7 = (int)(uVar8 * uVar6) / 100;
		}
		else if ((int)(uVar8 & 0xfffffff0) < 0x640)
		{
			uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar6),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar6) >> 0x20), 100, 0);
			iVar7 = (int)uVar11;
		}
		else
		{
			iVar7 = ((int)uVar8 / 100) * uVar6;
		}
	}
	else if ((int)(uVar6 & 0xfffffff0) < 0x640)
	{
		uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar6),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)uVar6) >> 0x20), 100, 0);
		iVar7 = (int)uVar11;
	}
	else
	{
		iVar7 = ((int)uVar6 / 100) * uVar8;
	}
	iVar3 = a3;
	pDStack_54 = (D2UnitStrc*)(uVar6 + iVar7);
	sub_6FB0BD60(pDVar2, (int*)&local_50, (int*)(&pDStack_54), *(uint8_t*)(a3 + 0x1dc));
	pDVar10 = pDStack_54;
	if ((int)pDStack_54 < (int)local_50)
	{
		pDVar10 = local_50;
	}
	uVar8 = (uint32_t) * (uint8_t*)(iVar3 + 0x1a5);
	if ((int)local_50 < 0x100001)
	{
		if (uVar8 < 0x10001)
		{
			local_50 = (D2UnitStrc*)((int)(uVar8 * (int)local_50 + ((int)(uVar8 * (int)local_50) >> 0x1f & 0x7fU)) >> 7);
		}
		else
		{
			if ((uVar8 & 0xfffffff0) < 0x800)
				goto LAB_6fb0d18e;
			local_50 = (D2UnitStrc*)(((int)uVar8 >> 7) * (int)local_50);
		}
	}
	else if ((int)((uint32_t)local_50 & 0xfffffff0) < 0x800)
	{
	LAB_6fb0d18e:
		uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)local_50),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)local_50) >> 0x20),
		    0x80, 0);
		local_50 = (D2UnitStrc*)uVar11;
	}
	else
	{
		local_50 = (D2UnitStrc*)(((int)(local_50->unk0x19 + (((int)local_50 >> 0x1f & 0x7fU) - 0x19)) >> 7) * uVar8);
	}
	if ((int)pDVar10 < 0x100001)
	{
		if (uVar8 < 0x10001)
		{
			pDStack_54 = (D2UnitStrc*)((int)(uVar8 * (int)pDVar10 + ((int)(uVar8 * (int)pDVar10) >> 0x1f & 0x7fU)) >> 7);
			goto LAB_6fb0d228;
		}
		if (0x7ff < (uVar8 & 0xfffffff0))
		{
			pDStack_54 = (D2UnitStrc*)(((int)uVar8 >> 7) * (int)pDVar10);
			goto LAB_6fb0d228;
		}
	}
	else if (0x7ff < (int)((uint32_t)pDVar10 & 0xfffffff0))
	{
		pDStack_54 = (D2UnitStrc*)(((int)(pDVar10->unk0x19 + (((int)pDVar10 >> 0x1f & 0x7fU) - 0x19)) >> 7) * uVar8);
		goto LAB_6fb0d228;
	}
	uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar8 * (int64_t)(int)pDVar10),
	    (uint32_t)((uint64_t)((int64_t)(int)uVar8 * (int64_t)(int)pDVar10) >> 0x20), 0x80,
	    0);
	pDStack_54 = (D2UnitStrc*)uVar11;
LAB_6fb0d228:
	sub_6FB0C840(pDVar2, (short*)iVar3, a4, (int*)(&local_50), (int*)(&pDStack_54), (uint32_t*)(&local_4c));
	pDVar10 = local_50;
	pDStack_44 = pUnit2;
	pDVar2 = pDStack_54;
	if ((int)pDStack_54 <= (int)local_50)
	{
		pDVar2 = (D2UnitStrc*)((int)&local_50->dwUnitType + 1);
	}
	sub_6FB0B250((Unicode*)aUStack_40, (int)pDVar10, (int)pDVar2, 0);
	a3 = 0;
	a4 = nullptr;
	D2Win_10131_GetTextDimensions(aUStack_40, &a3, (int*)&a4);
	iVar3 = a7;
	iVar7 = a5;
	a3 = (a3 * 0xb) / 7;
	if (a7 - a5 < a3)
	{
		D2Win_10127_SetFont(D2FONT_FONT6);
		pDVar2 = (D2UnitStrc*)((int)&pUnit2[-1].pMsgLast + 3);
	}
	else
	{
		D2Win_10127_SetFont(D2FONT_FONT16);
		pDVar2 = pDStack_44;
	}
	sub_6FACFCD0(dword_6FBBA748 + iVar7, (int)pDVar2 + gnScreenHeight + dword_6FBBA74C + -0x1e0,
	    dword_6FBBA748 + iVar3, aUStack_40, local_4c);
}

//D2Client.0x6FB0D330
void __fastcall sub_6FB0D330(D2UnitStrc* pUnit, int a2, short* a3, int* a4, int a5, int a6, int a7)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	Unicode* pThis;
	int iVar4;
	D2SkillsTxt* local_7c;
	int local_78;
	int local_74;
	int local_70;
	int local_6c;
	int local_68;
	D2SkillsTxt* local_64;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if ((a2 != 0) && (a3 != nullptr))
	{
		bVar1 = *(uint8_t*)((int)a3 + 0x1a5);
		local_7c = nullptr;
		sub_6FB0D4F0(pUnit, (uint32_t*)(&local_70), (uint32_t*)(&local_6c), (uint32_t*)(&local_7c), 0, 0, (D2SkillStrc*)(a2), 0, 0);
		local_70 = local_70 * (uint32_t)bVar1;
		local_74 = (int)(local_70 + (local_70 >> 0x1f & 0x7fU)) >> 7;
		local_6c = local_6c * (uint32_t)bVar1;
		local_78 = (int)(local_6c + (local_6c >> 0x1f & 0x7fU)) >> 7;
		sub_6FB0C840(pUnit, a3, a4, &local_74, &local_78, (uint32_t*)(&local_7c));
		iVar2 = local_74;
		local_68 = a6;
		local_64 = local_7c;
		iVar3 = local_78;
		if (local_78 <= local_74)
		{
			iVar3 = local_74 + 1;
		}
		if (iVar2 == iVar3)
		{
			wsprintfA(aCStack_60, "%d", iVar2);
			Unicode::toUnicode(local_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)local_40, iVar2, iVar3, 0, 1);
		}
		local_78 = 0;
		local_74 = 0;
		D2Win_10131_GetTextDimensions(local_40, &local_78, &local_74);
		local_78 = (local_78 * 0xb) / 7;
		if (a7 - a5 < local_78)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar3 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar3 = local_68;
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar3,
		    dword_6FBBA748 + a7, local_40, local_64);
	}
}

//D2Client.0x6FB0D4F0
void __fastcall sub_6FB0D4F0(D2UnitStrc* pUnit, uint32_t* a2, uint32_t* a3, uint32_t* a4, uint32_t a5, uint32_t a6, D2SkillStrc* pSkill, uint32_t a8, D2UnitStrc* pUnit2)
{
	uint32_t uVar1;
	uint8_t bVar2;
	short sVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint64_t uVar8;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	*a2 = 0;
	*a3 = 0;
	if ((pSkill == nullptr) ||
	    (((pUnit2 == nullptr &&
	          ((pUnit->pInventory == nullptr ||
	              (pUnit2 = INVENTORY_GetLeftHandWeapon(pUnit->pInventory), pUnit2 == nullptr)))) ||
	        (iVar4 = ITEMS_CheckIfThrowable(pUnit2), iVar4 == 0))))
	{
		return;
	}
	iVar4 = ITEMS_CheckItemTypeId(pUnit2, 0x26);
	if (iVar4 == 0)
	{
		iVar4 = 0;
		sVar3 = ITEMS_GetStrengthBonus(pUnit2);
		if (sVar3 != 0)
		{
			iVar4 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
			iVar4 = (iVar4 * sVar3) / 100;
		}
		sVar3 = ITEMS_GetDexBonus(pUnit2);
		if (sVar3 != 0)
		{
			iVar6 = STATLIST_UnitGetStatValue(pUnit, 2, 0);
			iVar4 = iVar4 + (iVar6 * sVar3) / 100;
		}
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x9f, 0);
		*a2 = iVar6;
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0xa0, 0);
		*a3 = iVar6;
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
		iVar4 = iVar4 + iVar6;
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x12, 0);
		iStack_4 = STATLIST_UnitGetStatValue(pUnit, 0x11, 0);
		if (iVar4 < -0x59)
		{
			iVar4 = -0x5a;
		}
		*a2 = ((iVar4 + iVar6) * *a2) / 100 + *a2;
		*a3 = ((iStack_4 + iVar4) * *a3) / 100 + *a3;
		iVar4 = STATES_CheckState(pUnit, 0x4e);
		if (iVar4 != 0)
		{
			iVar4 = SKILLS_GetWeaponMasteryBonus(pUnit, pUnit2, pSkill, 1);
			a5 = iVar4 + a5;
		}
		uVar1 = *a2;
		if ((int)uVar1 < 0x100001)
		{
			if ((int)a5 < 0x10001)
			{
				iVar4 = (int)(uVar1 * a5) / 100;
			}
			else if ((int)(a5 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)a5),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)a5) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)a5 / 100) * uVar1;
			}
		}
		else if ((int)(uVar1 & 0xfffffff0) < 0x640)
		{
			uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)a5),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)a5) >> 0x20),
			    100, 0);
			iVar4 = (int)uVar8;
		}
		else
		{
			iVar4 = ((int)uVar1 / 100) * a5;
		}
		*a2 = uVar1 + iVar4;
		uVar1 = *a3;
		if ((int)uVar1 < 0x100001)
		{
			if ((int)a5 < 0x10001)
			{
				iVar4 = (int)(uVar1 * a5) / 100;
			}
			else if ((int)(a5 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)a5),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)a5) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar8;
			}
			else
			{
				iVar4 = ((int)a5 / 100) * uVar1;
			}
		}
		else if ((int)(uVar1 & 0xfffffff0) < 0x640)
		{
			uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)a5),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)a5) >> 0x20),
			    100, 0);
			iVar4 = (int)uVar8;
		}
		else
		{
			iVar4 = ((int)uVar1 / 100) * a5;
		}
		iVar6 = *a3;
		*a3 = iVar6 + iVar4;
		if (iVar6 + iVar4 < (int)*a2)
		{
			*a3 = *a2;
		}
		iStack_8 = 0;
		iStack_c = 0;
		sub_6FB0B6F0(pUnit, &iStack_8, &iStack_c, a4, pUnit2, pSkill);
		if (iStack_c < iStack_8)
		{
			iStack_c = iStack_8;
		}
		*a2 = *a2 + iStack_8;
		*a3 = *a3 + iStack_c;
		return;
	}
	iVar4 = ITEMS_GetMissileType(pUnit2);
	*a4 = 0;
	iVar5 = MISSILE_GetMinElemDamage(nullptr, pUnit, iVar4, 1);
	iVar6 = MISSILE_GetMinDamage(nullptr, pUnit, iVar4, 1);
	iVar5 = iVar5 + iVar6;
	iVar7 = MISSILE_GetMaxElemDamage(nullptr, pUnit, iVar4, 1);
	iVar6 = MISSILE_GetMaxDamage(nullptr, pUnit, iVar4, 1);
	iVar7 = iVar7 + iVar6;
	bVar2 = MISSILE_GetElemTypeFromMissileId(iVar4);
	switch (bVar2)
	{
	case 1:
		*a4 = 1;
		break;
	case 2:
		*a4 = 4;
		break;
	case 4:
		*a4 = 3;
		break;
	case 5:
		*a4 = 2;
		iVar4 = MISSILE_GetElementalLength(0, pUnit, iVar4, 1);
		iVar4 = iVar4 / 0x19;
		if (iVar4 < 1)
		{
			iVar4 = 1;
		}
		iVar5 = iVar5 / iVar4;
		iVar7 = iVar7 / iVar4;
		goto LAB_6fb0d62a;
	}
LAB_6fb0d62a:
	iVar5 = iVar5 >> 8;
	iVar4 = iVar7 >> 8;
	if (iVar7 >> 8 <= iVar5)
	{
		iVar4 = iVar5;
	}
	*a2 = iVar5;
	*a3 = iVar4;
}

//D2Client.0x6FB0D920
void __fastcall sub_6FB0D920(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int iVar3;
	Unicode* pThis;
	int local_74;
	D2SkillsTxt* local_70;
	int local_6c;
	int local_68;
	D2SkillsTxt* local_64;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if ((a2 != 0) && (a3 != 0))
	{
		local_6c = 0;
		local_74 = 0;
		local_70 = nullptr;
		iVar2 = sub_6FB0A950(pUnit);
		if (iVar2 != 0)
		{
			sub_6FB0D4F0(pUnit, (uint32_t*)(&local_6c), (uint32_t*)(&local_74), (uint32_t*)(&local_70), 0, 0, (D2SkillStrc*)(a2), 0, (D2UnitStrc*)(iVar2));
			sub_6FB0AA00(pUnit);
			iVar1 = local_6c;
			local_64 = local_70;
			local_68 = a6;
			iVar2 = local_74;
			if (local_74 <= local_6c)
			{
				iVar2 = local_6c + 1;
			}
			if (iVar1 == iVar2)
			{
				wsprintfA(aCStack_60, "%d", iVar1);
				Unicode::toUnicode(local_40, aCStack_60, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)local_40, iVar1, iVar2, 0, 1);
			}
			local_74 = 0;
			local_6c = 0;
			D2Win_10131_GetTextDimensions(local_40, &local_74, &local_6c);
			local_74 = (local_74 * 0xb) / 7;
			if (a7 - a5 < local_74)
			{
				D2Win_10127_SetFont(D2FONT_FONT6);
				iVar2 = a6 + -1;
			}
			else
			{
				D2Win_10127_SetFont(D2FONT_FONT16);
				iVar2 = local_68;
			}
			sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar2,
			    dword_6FBBA748 + a7, local_40, local_64);
		}
	}
}

//D2Client.0x6FB0DAB0
void __fastcall sub_6FB0DAB0(uint32_t* a1, int a2, short* a3, int* a4, int a5, int a6, int a7)
{
	uint8_t bVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	Unicode* pUVar5;
	int iVar6;
	uint64_t uVar7;
	uint32_t local_98;
	D2SkillsTxt* local_94;
	D2SkillsTxt* local_90;
	int local_8c;
	D2SkillsTxt* local_88;
	int local_84;
	Unicode local_80[32];
	Unicode aUStack_40[32];

	if (a2 == 0)
	{
		return;
	}
	if (a3 == nullptr)
	{
		return;
	}
	bVar1 = *(uint8_t*)((int)a3 + 0x1a5);
	uVar2 = (uint32_t)bVar1;
	local_94 = nullptr;
	local_98 = 0;
	local_88 = nullptr;
	local_90 = (D2SkillsTxt*)a1;
	sub_6FB0D4F0((D2UnitStrc*)a1, (uint32_t*)(&local_94), &local_98, (uint32_t*)(&local_88), 0, 0, (D2SkillStrc*)(a2), 0, 0);
	if ((int)local_94 < 0x100001)
	{
		if (uVar2 < 0x10001)
		{
			iVar6 = (int)(uVar2 * (int)local_94 + ((int)(uVar2 * (int)local_94) >> 0x1f & 0x7fU)) >> 7;
		}
		else
		{
			if ((bVar1 & 0xfffffff0) < 0x800)
				goto LAB_6fb0db4d;
			iVar6 = ((int)uVar2 >> 7) * (int)local_94;
		}
	}
	else if ((int)((uint32_t)local_94 & 0xfffffff0) < 0x800)
	{
	LAB_6fb0db4d:
		uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar2 * (int64_t)(int)local_94),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar2 * (int64_t)(int)local_94) >> 0x20),
		    0x80, 0);
		iVar6 = (int)uVar7;
	}
	else
	{
		iVar6 = ((int)((int)local_94->dwFlags + (((int)local_94 >> 0x1f & 0x7fU) - 4)) >> 7) * uVar2;
	}
	if ((int)local_98 < 0x100001)
	{
		if (uVar2 < 0x10001)
		{
			iVar3 = (int)(uVar2 * local_98 + ((int)(uVar2 * local_98) >> 0x1f & 0x7fU)) >> 7;
			goto LAB_6fb0dbf3;
		}
		if (0x7ff < (bVar1 & 0xfffffff0))
		{
			iVar3 = ((int)uVar2 >> 7) * local_98;
			goto LAB_6fb0dbf3;
		}
	}
	else if (0x7ff < (int)(local_98 & 0xfffffff0))
	{
		iVar3 = ((int)(local_98 + ((int)local_98 >> 0x1f & 0x7fU)) >> 7) * uVar2;
		goto LAB_6fb0dbf3;
	}
	uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar2 * (int64_t)(int)local_98),
	    (uint32_t)((uint64_t)((int64_t)(int)uVar2 * (int64_t)(int)local_98) >> 0x20), 0x80,
	    0);
	iVar3 = (int)uVar7;
LAB_6fb0dbf3:
	local_98 = 0;
	local_8c = 0;
	local_94 = nullptr;
	sub_6FB0C840((D2UnitStrc*)local_90, a3, a4, (int*)(&local_98), &local_8c, (uint32_t*)(&local_94));
	uVar2 = local_98;
	if ((iVar6 == 0) && (iVar3 == 0))
	{
		local_84 = a6;
		iVar6 = local_8c;
		if (local_8c <= (int)local_98)
		{
			iVar6 = local_98 + 1;
		}
		sub_6FB0B250((Unicode*)local_80, uVar2, iVar6, 0);
		local_98 = 0;
		local_90 = nullptr;
		D2Win_10131_GetTextDimensions(local_80, (int*)&local_98, (int*)&local_90);
		local_98 = (int)(local_98 * 0xb) / 7;
		if (a7 - a5 < (int)local_98)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar6 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar6 = local_84;
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar6,
		    dword_6FBBA748 + a7, local_80, local_94);
		return;
	}
	if ((local_98 == 0) && (local_8c == 0))
	{
		local_90 = local_88;
		if (iVar3 <= iVar6)
		{
			iVar3 = iVar6 + 1;
		}
		memset(local_80, 0, 2 * (0x20));
		sub_6FB0B250((Unicode*)local_80, iVar6, iVar3, 0);
		local_98 = 0;
		local_84 = 0;
		D2Win_10131_GetTextDimensions(local_80, (int*)&local_98, &local_84);
		local_98 = (int)(local_98 * 0xb) / 7;
		if (a7 - a5 < (int)local_98)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			a6 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, gnScreenHeight + -0x1e0 + a6 + dword_6FBBA74C,
		    dword_6FBBA748 + a7, local_80, local_90);
		return;
	}
	if (iVar6 == iVar3)
	{
		sub_6FB0B0F0((Unicode*)local_80, iVar6, 0);
	}
	else
	{
		sub_6FB0B140((Unicode*)local_80, iVar6, iVar3, 0, 1);
	}
	sub_6FB0B250((Unicode*)aUStack_40, local_98, local_8c, 0);
	sub_6FB0AC10((uint32_t)(local_80), (uint32_t)(aUStack_40), a5, a6, a7, local_88, local_94);
}

//D2Client.0x6FB0DEC0
void __fastcall sub_6FB0DEC0(D2UnitStrc* pUnit, int a2, short* a3, int a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	Unicode* pThis;
	int iVar6;
	D2SkillsTxt* local_74;
	int local_70;
	D2SkillsTxt* local_6c;
	int local_68;
	uint32_t local_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if ((a2 != 0) && (a3 != nullptr))
	{
		iVar5 = 0;
		iVar6 = 0;
		local_64 = (uint32_t) * (uint8_t*)((int)a3 + 0x1a5);
		switch ((char)a3[0xee])
		{
		case '\x01':
			local_6c = (D2SkillsTxt*)0x1;
			break;
		case '\x02':
			local_6c = (D2SkillsTxt*)0x9;
			break;
		case '\x03':
		case '\x04':
			local_6c = (D2SkillsTxt*)0x3;
			break;
		case '\x05':
			local_6c = (D2SkillsTxt*)0x2;
			break;
		default:
			local_6c = nullptr;
		}
		local_68 = a2;
		if (local_64 != 0)
		{
			local_74 = nullptr;
			local_70 = 0;
			sub_6FB0B2C0(pUnit, (uint32_t)&local_74, &local_70, (uint32_t*)(&local_6c), 0, 0, (D2SkillStrc*)(a2), 0x80, 0, 0);
			sub_6FB0B6F0(pUnit, (int*)&local_74, &local_70, (uint32_t*)(&local_6c), nullptr, (D2SkillStrc*)(local_68));
			iVar5 = (int)((int)local_74 * local_64 + ((int)((int)local_74 * local_64) >> 0x1f & 0x7fU)) >>
			        7;
			iVar6 = (int)(local_70 * local_64 + ((int)(local_70 * local_64) >> 0x1f & 0x7fU)) >> 7;
		}
		iVar1 = SKILLS_GetMinPhysDamage(pUnit, (int)*a3, a4, 0);
		iVar2 = SKILLS_GetMaxPhysDamage(pUnit, (int)*a3, a4, 0);
		if ((char)a3[0xee] == '\x05')
		{
			local_70 = SKILLS_GetElementalLength(pUnit, (int)*a3, a4, 1);
			iVar3 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
			iVar3 = iVar3 * local_70;
			iVar4 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, a4, 1);
			iVar4 = iVar4 * local_70;
		}
		else
		{
			iVar3 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
			iVar4 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, a4, 1);
		}
		iVar1 = iVar5 + (iVar1 >> 8) + (iVar3 >> 8);
		iVar5 = iVar6 + (iVar2 >> 8) + (iVar4 >> 8);
		local_68 = a6;
		local_74 = local_6c;
		if (iVar5 <= iVar1)
		{
			iVar5 = iVar1 + 1;
		}
		if (iVar1 == iVar5)
		{
			wsprintfA(aCStack_60, "%d", iVar1);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar1, iVar5, 0, 1);
		}
		local_70 = 0;
		local_64 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &local_70, (int*)&local_64);
		local_70 = (local_70 * 0xb) / 7;
		if (a7 - a5 < local_70)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar5 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar5 = local_68;
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar5,
		    dword_6FBBA748 + a7, aUStack_40, local_74);
	}
}

//D2Client.0x6FB0E180
void __fastcall sub_6FB0E180(D2UnitStrc* pUnit, int a2, short* a3, int a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	Unicode* pThis;
	D2SkillsTxt* pDStack_74;
	int iStack_70;
	D2SkillsTxt* local_6c;
	int local_68;
	uint32_t local_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if ((a2 != 0) && (a3 != nullptr))
	{
		local_64 = (uint32_t) * (uint8_t*)((int)a3 + 0x1a5);
		switch ((char)a3[0xee])
		{
		case '\x01':
			local_6c = (D2SkillsTxt*)0x1;
			break;
		case '\x02':
			local_6c = (D2SkillsTxt*)0x9;
			break;
		case '\x03':
		case '\x04':
			local_6c = (D2SkillsTxt*)0x3;
			break;
		case '\x05':
			local_6c = (D2SkillsTxt*)0x2;
			break;
		default:
			local_6c = nullptr;
		}
		local_68 = a2;
		iVar1 = SKILLS_GetMinPhysDamage(pUnit, (int)*a3, a4, 0);
		iVar1 = iVar1 >> 8;
		iVar2 = SKILLS_GetMaxPhysDamage(pUnit, (int)*a3, a4, 0);
		iVar2 = iVar2 >> 8;
		if (local_64 != 0)
		{
			pDStack_74 = nullptr;
			iStack_70 = 0;
			sub_6FB0B2C0(pUnit, (uint32_t)&pDStack_74, &iStack_70, (uint32_t*)(&local_6c), 0, 0, (D2SkillStrc*)(local_68), 0x80, 0, 0);
			sub_6FB0B6F0(pUnit, (int*)&pDStack_74, &iStack_70, (uint32_t*)(&local_6c), nullptr, (D2SkillStrc*)(local_68));
			iVar1 = iVar1 + ((int)((int)pDStack_74 * local_64 +
			                       ((int)((int)pDStack_74 * local_64) >> 0x1f & 0x7fU)) >>
			                    7);
			iVar2 = iVar2 + ((int)(iStack_70 * local_64 + ((int)(iStack_70 * local_64) >> 0x1f & 0x7fU)) >> 7);
		}
		if ((char)a3[0xee] == '\x05')
		{
			local_64 = SKILLS_GetElementalLength(pUnit, (int)*a3, a4, 1);
			iVar3 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
			iVar3 = iVar3 * local_64;
			iVar4 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, a4, 1);
			iVar4 = iVar4 * local_64;
		}
		else
		{
			iVar3 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
			iVar4 = SKILLS_GetMaxElemDamage(pUnit, (int)*a3, a4, 1);
		}
		iVar1 = iVar1 + (iVar3 >> 8);
		iVar2 = iVar2 + (iVar4 >> 8);
		local_68 = a6;
		pDStack_74 = local_6c;
		if (iVar2 <= iVar1)
		{
			iVar2 = iVar1 + 1;
		}
		if (iVar1 == iVar2)
		{
			wsprintfA(aCStack_60, "%d", iVar1);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar1, iVar2, 0, 1);
		}
		iStack_70 = 0;
		local_64 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &iStack_70, (int*)&local_64);
		iStack_70 = (iStack_70 * 0xb) / 7;
		if (a7 - a5 < iStack_70)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar2 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar2 = local_68;
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar2,
		    dword_6FBBA748 + a7, aUStack_40, pDStack_74);
	}
}

//D2Client.0x6FB0E440
void __fastcall sub_6FB0E440(D2UnitStrc* pUnit, int a2, short* a3, int* a4, int a5, D2SkillsTxt* pSkillsTxtRecord, int a7)
{
	D2SkillsTxt* pDVar1;
	D2SkillsTxt* pDVar2;
	int iVar3;
	int iVar4;
	Unicode* pUVar5;
	int iVar6;
	D2SkillsTxt* local_dc;
	D2SkillsTxt* local_d8;
	D2SkillsTxt* local_d4;
	D2SkillsTxt* local_d0;
	int local_cc;
	int local_c8;
	D2SkillsTxt* local_c4;
	Unicode local_c0[32];
	Unicode aUStack_80[32];
	Unicode local_40[32];

	if ((a2 == 0) || (a3 == nullptr))
	{
		return;
	}
	local_cc = 0;
	local_c8 = 0;
	local_d0 = nullptr;
	sub_6FB0B2C0(pUnit, (uint32_t)&local_cc, &local_c8, (uint32_t*)(&local_d0), 0, 0, (D2SkillStrc*)(a2), 0x80, 0, 0);
	sub_6FB0B6F0(pUnit, &local_cc, &local_c8, (uint32_t*)(&local_d0), nullptr, (D2SkillStrc*)(a2));
	local_d8 = nullptr;
	local_dc = nullptr;
	local_d4 = nullptr;
	sub_6FB0C840(pUnit, a3, a4, (int*)(&local_d8), (int*)(&local_dc), (uint32_t*)(&local_d4));
	iVar3 = local_cc;
	pDVar2 = local_d8;
	if ((local_cc == 0) && (local_c8 == 0))
	{
		local_c4 = pSkillsTxtRecord;
		pDVar1 = local_dc;
		if ((int)local_dc <= (int)local_d8)
		{
			pDVar1 = (D2SkillsTxt*)((int)&local_d8->nSkillId + 1);
		}
		sub_6FB0B250((Unicode*)local_c0, (int)pDVar2, (int)pDVar1, 0);
		local_dc = nullptr;
		local_d8 = nullptr;
		D2Win_10131_GetTextDimensions(local_c0, (int*)&local_dc, (int*)&local_d8);
		local_dc = (D2SkillsTxt*)(((int)local_dc * 0xb) / 7);
		if (a7 - a5 < (int)local_dc)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			pDVar2 = (D2SkillsTxt*)((int)&pSkillsTxtRecord[-1].nCostAdd + 3);
			pDVar1 = local_d4;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar1 = local_d4;
			pDVar2 = local_c4;
		}
	}
	else
	{
		if ((local_d8 != nullptr) || (local_dc != nullptr))
		{
			if (local_cc == local_c8)
			{
				wsprintfA((LPSTR)local_c0, "%d", local_cc);
				Unicode::toUnicode(local_40, (char*)local_c0, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)local_40, local_cc, local_c8, 0, 1);
			}
			if (local_d8 == local_dc)
			{
				wsprintfA((LPSTR)local_c0, "%d", local_d8);
				Unicode::toUnicode(aUStack_80, (char*)local_c0, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_80, (int)local_d8, (int)local_dc, 0, 1);
			}
			sub_6FB0AC10((uint32_t)(local_40), (uint32_t)(aUStack_80), a5, (int)pSkillsTxtRecord, a7, local_d0, local_d4);
			return;
		}
		local_d4 = pSkillsTxtRecord;
		local_d8 = local_d0;
		iVar6 = local_c8;
		if (local_c8 <= local_cc)
		{
			iVar6 = local_cc + 1;
		}
		sub_6FB0B250((Unicode*)local_c0, iVar3, iVar6, 0);
		local_dc = nullptr;
		local_c4 = nullptr;
		D2Win_10131_GetTextDimensions(local_c0, (int*)&local_dc, (int*)&local_c4);
		local_dc = (D2SkillsTxt*)(((int)local_dc * 0xb) / 7);
		if (a7 - a5 < (int)local_dc)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			pDVar1 = local_d8;
			pDVar2 = (D2SkillsTxt*)((int)&pSkillsTxtRecord[-1].nCostAdd + 3);
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar1 = local_d8;
			pDVar2 = local_d4;
		}
	}
	sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + (int)pDVar2,
	    dword_6FBBA748 + a7, local_c0, pDVar1);
}

//D2Client.0x6FB0E7B0
void __fastcall sub_6FB0E7B0(D2UnitStrc* pUnit, int a2, short* a3, int* a4, int a5, int a6, int a7)
{
	int iVar1;

	iVar1 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(a3 + 0x9c), (int)*a3, (int)a4);
	sub_6FB0C400(pUnit, (D2SkillStrc*)a2, a3, a4, 0x6fb0d4f0, iVar1, 0, a5, a6,
	    a7, 1);
}

//D2Client.0x6FB0E800
void __fastcall sub_6FB0E800(D2UnitStrc* pUnit, D2SkillStrc* pSkill, D2SkillsTxt* pSkillsTxtRecord, int a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	Unicode* pThis;
	int iStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	iVar2 = a4;
	if (((((pSkill != nullptr) && (pSkillsTxtRecord != nullptr)) &&
	         (iVar1 = (int)pSkillsTxtRecord->nSkillId, -1 < iVar1)) &&
	        ((iVar4 = *(int*)((uint8_t*)&sgptDataTables), iVar1 < *(int*)(iVar4 + 0xba0) &&
	                                                          (iVar3 = *(int*)(iVar4 + 0xb98) + iVar1 * 0x23c, iVar3 != 0)))) &&
	    ((iVar3 = (int)*(short*)(iVar3 + 0x194), -1 < iVar3 &&
	                                                 ((iVar3 < *(int*)(iVar4 + 0xb94) &&
	                                                     (iVar4 = iVar3 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar4 != 0))))))
	{
		a4 = SKILLS_GetMinElemDamage(pUnit, iVar1, a4, 1);
		iStack_64 = SKILLS_GetMaxElemDamage(pUnit, (int)pSkillsTxtRecord->nSkillId, iVar2, 1);
		switch (pSkillsTxtRecord->nEType)
		{
		case 1:
			pSkillsTxtRecord = (D2SkillsTxt*)0x1;
			break;
		case 2:
			pSkillsTxtRecord = (D2SkillsTxt*)0x9;
			break;
		case 3:
		case 4:
			pSkillsTxtRecord = (D2SkillsTxt*)0x3;
			break;
		case 5:
			pSkillsTxtRecord = (D2SkillsTxt*)0x2;
			break;
		default:
			pSkillsTxtRecord = nullptr;
		}
		iVar1 = iVar2;
		iVar3 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iVar1 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar4 + 0x18), iVar3, iVar1);
		if (iVar1 == 0)
		{
			iVar1 = 1;
		}
		iVar3 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iVar4 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar4 + 0x1c), iVar3, iVar2);
		iVar2 = a6;
		if (iVar4 == 0)
		{
			iVar4 = 1;
		}
		iVar3 = (iVar1 * a4 * 0x19) / iVar4 >> 8;
		iVar1 = (iVar1 * iStack_64 * 0x19) / iVar4 >> 8;
		if (iVar1 <= iVar3)
		{
			iVar1 = iVar3 + 1;
		}
		if (iVar3 == iVar1)
		{
			wsprintfA(aCStack_60, "%d", iVar3);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar3, iVar1, 0, 1);
		}
		a4 = 0;
		iStack_64 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &a4, &iStack_64);
		iVar4 = a7;
		iVar1 = a5;
		a4 = (a4 * 0xb) / 7;
		if (a7 - a5 < a4)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar2 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
		}
		sub_6FACFCD0(dword_6FBBA748 + iVar1, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar2,
		    dword_6FBBA748 + iVar4, aUStack_40, pSkillsTxtRecord);
	}
}

//D2Client.0x6FB0EAB0
void __fastcall sub_6FB0EAB0(D2UnitStrc* pUnit, int a2, short* a3, int a4, int a5, int a6, int a7)
{
	uint8_t bVar1;
	short* psVar2;
	D2SkillsTxt* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	Unicode* pThis;
	int iVar9;
	D2SkillsTxt* pDStack_68;
	int local_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	iVar7 = a4;
	psVar2 = a3;
	if ((a2 != 0) && (a3 != nullptr))
	{
		iVar8 = *(int*)(a3 + 0xd6);
		bVar1 = *(uint8_t*)(a3 + 0xd2);
		iVar9 = *(int*)(a3 + 0xd4);
		local_64 = a2;
		iVar4 = SKILLS_GetMinElemDamage(pUnit, (int)*a3, a4, 1);
		iVar5 = SKILLS_GetMaxElemDamage(pUnit, (int)*psVar2, iVar7, 1);
		iVar7 = local_64;
		uVar6 = (uint32_t) * (uint8_t*)((int)psVar2 + 0x1a5);
		switch ((char)psVar2[0xee])
		{
		case '\x01':
			pDStack_68 = (D2SkillsTxt*)0x1;
			break;
		case '\x02':
			pDStack_68 = (D2SkillsTxt*)0x9;
			break;
		case '\x03':
		case '\x04':
			pDStack_68 = (D2SkillsTxt*)0x3;
			break;
		case '\x05':
			pDStack_68 = (D2SkillsTxt*)0x2;
			break;
		default:
			pDStack_68 = nullptr;
		}
		iVar9 = ((iVar9 << (bVar1 & 0x1f)) + iVar4) * 0x4b >> 8;
		iVar8 = ((iVar8 << (bVar1 & 0x1f)) + iVar5) * 0x4b >> 8;
		if (uVar6 != 0)
		{
			a3 = nullptr;
			a4 = 0;
			sub_6FB0B2C0(pUnit, (uint32_t)&a3, &a4, (uint32_t*)(&pDStack_68), 0, 0, (D2SkillStrc*)(local_64), 0x80, 0, 0);
			sub_6FB0B6F0(pUnit, (int*)&a3, &a4, (uint32_t*)(&pDStack_68), nullptr, (D2SkillStrc*)(iVar7));
			iVar9 = iVar9 + ((int)((int)a3 * uVar6 + ((int)((int)a3 * uVar6) >> 0x1f & 0x7fU)) >> 7);
			iVar8 = iVar8 + ((int)(a4 * uVar6 + ((int)(a4 * uVar6) >> 0x1f & 0x7fU)) >> 7);
		}
		pDVar3 = pDStack_68;
		local_64 = a6;
		if (iVar8 <= iVar9)
		{
			iVar8 = iVar9 + 1;
		}
		if (iVar9 == iVar8)
		{
			wsprintfA(aCStack_60, "%d", iVar9);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar9, iVar8, 0, 1);
		}
		a3 = nullptr;
		a4 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, (int*)&a3, &a4);
		iVar8 = a7;
		iVar7 = a5;
		a3 = (short*)(((int)a3 * 0xb) / 7);
		if (a7 - a5 < (int)a3)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar9 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar9 = local_64;
		}
		sub_6FACFCD0(dword_6FBBA748 + iVar7, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar9,
		    dword_6FBBA748 + iVar8, aUStack_40, pDVar3);
	}
}

//D2Client.0x6FB0ED40
void __fastcall sub_6FB0ED40(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5, int a6, int a7)
{
	short sVar1;
	int iVar2;
	D2ItemsTxt* pDVar3;
	D2SkillStrc* pSkill;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	Unicode* pThis;
	D2UnitStrc* local_6c;
	D2SkillsTxt* pDStack_68;
	int iStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if ((a2 != 0) && (a3 != 0))
	{
		iVar2 = INVENTORY_GetEquippedShield(pUnit->pInventory, &local_6c);
		if (iVar2 != 0)
		{
			if (local_6c == nullptr)
			{
				iVar2 = -1;
			}
			else
			{
				iVar2 = local_6c->dwClassId;
			}
			pDVar3 = DATATBLS_GetItemsTxtRecord(iVar2);
			uVar7 = (uint32_t)pDVar3->nMaxDam;
			uVar5 = (uint32_t)pDVar3->nMinDam;
			pSkill = SKILLS_GetSkillById(pUnit, 0x75, 0xffffffff);
			if (pSkill != nullptr)
			{
				iVar2 = STATES_CheckState(pUnit, 0x65);
				if (iVar2 != 0)
				{
					iVar2 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
					iVar4 = SKILLS_GetMinPhysDamage(pUnit, 0x75, iVar2, 1);
					uVar5 = uVar5 + (iVar4 >> 8);
					iVar2 = SKILLS_GetMaxPhysDamage(pUnit, 0x75, iVar2, 1);
					uVar7 = uVar7 + (iVar2 >> 8);
				}
			}
			iVar4 = 0;
			pDStack_68 = nullptr;
			iVar2 = (int)*(short*)a3;
			if ((((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
			        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
			    (0 < a4))
			{
				iVar4 = *(int*)(iVar2 + 0x154) * (a4 + -1) + *(int*)(iVar2 + 0x150);
			}
			sVar1 = ITEMS_GetStrengthBonus(local_6c);
			a3 = (int)sVar1;
			if (a3 != 0)
			{
				iVar2 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
				iVar4 = iVar4 + (iVar2 * a3) / 100;
			}
			sVar1 = ITEMS_GetDexBonus(local_6c);
			a3 = (int)sVar1;
			if (a3 != 0)
			{
				iVar2 = STATLIST_UnitGetStatValue(pUnit, 2, 0);
				iVar4 = iVar4 + (iVar2 * a3) / 100;
			}
			iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
			iVar4 = iVar4 + iVar2;
			a3 = STATLIST_UnitGetStatValue(pUnit, 0x12, 0);
			a4 = STATLIST_UnitGetStatValue(pUnit, 0x11, 0);
			iVar2 = STATES_CheckStateMaskDamBlueOnUnit(pUnit);
			if (iVar2 != 0)
			{
				pDStack_68 = (D2SkillsTxt*)0x3;
			}
			iVar2 = STATES_CheckStateMaskDamRedOnUnit(pUnit);
			if (iVar2 != 0)
			{
				pDStack_68 = (D2SkillsTxt*)0x1;
			}
			if (iVar4 < -0x59)
			{
				iVar4 = -0x5a;
			}
			iVar6 = uVar5 + (int)(iVar4 * uVar5 + a3) / 100;
			iStack_64 = a6;
			iVar2 = (int)(iVar4 * uVar7 + a4) / 100 + uVar7;
			if (iVar2 <= iVar6)
			{
				iVar2 = iVar6 + 1;
			}
			if (iVar6 == iVar2)
			{
				wsprintfA(aCStack_60, "%d", iVar6);
				Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_40, iVar6, iVar2, 0, 1);
			}
			a3 = 0;
			a4 = 0;
			D2Win_10131_GetTextDimensions(aUStack_40, &a3, &a4);
			iVar4 = a7;
			iVar2 = a5;
			a3 = (a3 * 0xb) / 7;
			if (a7 - a5 < a3)
			{
				D2Win_10127_SetFont(D2FONT_FONT6);
				iVar6 = a6 + -1;
			}
			else
			{
				D2Win_10127_SetFont(D2FONT_FONT16);
				iVar6 = iStack_64;
			}
			sub_6FACFCD0(dword_6FBBA748 + iVar2, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar6,
			    dword_6FBBA748 + iVar4, aUStack_40, pDStack_68);
		}
	}
}

//D2Client.0x6FB0F080
void __fastcall sub_6FB0F080(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5, int a6, uint32_t a7)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	uint8_t* pbVar8;
	int iVar9;
	D2UnitStrc* pDVar10;
	uint64_t uVar11;
	int local_10;
	uint8_t* local_c;
	D2SkillsTxt* local_8;
	int local_4;

	if ((a2 != 0) && (a3 != 0))
	{
		uVar3 = (uint32_t) * (uint8_t*)(a3 + 0x1a5);
		local_10 = 0;
		local_c = nullptr;
		switch (*(uint8_t*)(a3 + 0x1dc))
		{
		case 1:
			local_8 = (D2SkillsTxt*)0x1;
			break;
		case 2:
			local_8 = (D2SkillsTxt*)0x9;
			break;
		case 3:
		case 4:
			local_8 = (D2SkillsTxt*)0x3;
			break;
		case 5:
			local_8 = (D2SkillsTxt*)0x2;
			break;
		default:
			local_8 = nullptr;
		}
		if (uVar3 != 0)
		{
			local_c = nullptr;
			local_4 = 0;
			sub_6FB0B2C0(pUnit, (uint32_t)&local_c, &local_4, (uint32_t*)(&local_8), 0, 0, (D2SkillStrc*)(a2), 0x80, 0, 0);
			sub_6FB0B6F0(pUnit, (int*)&local_c, &local_4, (uint32_t*)(&local_8), nullptr, (D2SkillStrc*)(a2));
			local_10 = (int)((int)local_c * uVar3 + ((int)((int)local_c * uVar3) >> 0x1f & 0x7fU)) >> 7;
			local_c = (uint8_t*)((int)(local_4 * uVar3 + ((int)(local_4 * uVar3) >> 0x1f & 0x7fU)) >> 7);
		}
		pDVar1 = D2Common_10434(pUnit, 1);
		if ((pDVar1 == nullptr) ||
		    (iVar2 = INVENTORY_GetWieldType(pUnit, pUnit->pInventory), iVar2 != 2))
		{
			uVar3 = STATLIST_UnitGetStatValue(pUnit, 0x15, 0);
			iVar2 = 0x16;
		}
		else
		{
			uVar3 = STATLIST_UnitGetStatValue(pUnit, 0x17, 0);
			iVar2 = 0x18;
		}
		uVar4 = STATLIST_UnitGetStatValue(pUnit, iVar2, 0);
		if ((int)uVar3 < 2)
		{
			uVar3 = 1;
		}
		if ((int)uVar4 < 3)
		{
			uVar4 = 2;
		}
		if ((int)uVar4 < (int)uVar3)
		{
			uVar4 = uVar3;
		}
		local_4 = (int)*(short*)a3;
		uVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(a3 + 0x138), local_4, a4);
		if ((uVar5 != 0) && (uVar6 = STATLIST_UnitGetStatValue(pUnit, 0x149, 0), uVar6 != 0))
		{
			if ((int)uVar5 < 0x100001)
			{
				if ((int)uVar6 < 0x10001)
				{
					iVar2 = (int)(uVar6 * uVar5) / 100;
				}
				else if ((int)(uVar6 & 0xfffffff0) < 0x640)
				{
					uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5) >> 0x20), 100, 0);
					iVar2 = (int)uVar11;
				}
				else
				{
					iVar2 = ((int)uVar6 / 100) * uVar5;
				}
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5) >> 0x20),
				    100, 0);
				iVar2 = (int)uVar11;
			}
			else
			{
				iVar2 = ((int)uVar5 / 100) * uVar6;
			}
			uVar5 = uVar5 + iVar2;
		}
		if ((int)uVar3 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar2 = (int)(uVar5 * uVar3) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3) >> 0x20),
				    100, 0);
				iVar2 = (int)uVar11;
			}
			else
			{
				iVar2 = ((int)uVar5 / 100) * uVar3;
			}
		}
		else if ((int)(uVar3 & 0xfffffff0) < 0x640)
		{
			uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3) >> 0x20), 100, 0);
			iVar2 = (int)uVar11;
		}
		else
		{
			iVar2 = ((int)uVar3 / 100) * uVar5;
		}
		if ((int)uVar4 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar7 = (int)(uVar5 * uVar4) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar4),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar4) >> 0x20),
				    100, 0);
				iVar7 = (int)uVar11;
			}
			else
			{
				iVar7 = ((int)uVar5 / 100) * uVar4;
			}
		}
		else if ((int)(uVar4 & 0xfffffff0) < 0x640)
		{
			uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar4),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar4) >> 0x20), 100, 0);
			iVar7 = (int)uVar11;
		}
		else
		{
			iVar7 = ((int)uVar4 / 100) * uVar5;
		}
		local_c = local_c + iVar7;
		uVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(a3 + 0x13c), local_4, a4);
		if ((uVar5 != 0) && (uVar6 = STATLIST_UnitGetStatValue(pUnit, 0x14b, 0), uVar6 != 0))
		{
			if ((int)uVar5 < 0x100001)
			{
				if ((int)uVar6 < 0x10001)
				{
					iVar7 = (int)(uVar6 * uVar5) / 100;
				}
				else if ((int)(uVar6 & 0xfffffff0) < 0x640)
				{
					uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5) >> 0x20), 100, 0);
					iVar7 = (int)uVar11;
				}
				else
				{
					iVar7 = ((int)uVar6 / 100) * uVar5;
				}
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar6 * (int64_t)(int)uVar5) >> 0x20),
				    100, 0);
				iVar7 = (int)uVar11;
			}
			else
			{
				iVar7 = ((int)uVar5 / 100) * uVar6;
			}
			uVar5 = uVar5 + iVar7;
		}
		if ((int)uVar3 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar7 = (int)(uVar5 * uVar3) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3) >> 0x20),
				    100, 0);
				iVar7 = (int)uVar11;
			}
			else
			{
				iVar7 = ((int)uVar5 / 100) * uVar3;
			}
		}
		else if ((int)(uVar3 & 0xfffffff0) < 0x640)
		{
			uVar11 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar3) >> 0x20), 100, 0);
			iVar7 = (int)uVar11;
		}
		else
		{
			iVar7 = ((int)uVar3 / 100) * uVar5;
		}
		pDVar1 = sub_6FAE5BD0(uVar4, uVar5, 100);
		local_c = pDVar1->unk0x19 + (int)(local_c + -0x19);
		pbVar8 = (uint8_t*)SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(a3 + 0x140), local_4, a4);
		if ((pbVar8 != nullptr) && (iVar9 = STATLIST_UnitGetStatValue(pUnit, 0x14a, 0), iVar9 != 0))
		{
			pDVar1 = sub_6FAE5BD0((int)pbVar8, iVar9, 100);
			pbVar8 = pDVar1->unk0x19 + (int)(pbVar8 + -0x19);
		}
		pDVar1 = sub_6FAE5BD0(uVar3, (int)pbVar8, 100);
		pDVar10 = sub_6FAE5BD0(uVar4, (int)pbVar8, 100);
		if (local_8 == nullptr)
		{
			local_8 = (D2SkillsTxt*)0x3;
		}
		sub_6FB0F5E0(pUnit, (int)(pDVar1->unk0x19 + local_10 + iVar2 + iVar7 + -0x19),
		    (int)(pDVar10->unk0x19 + (int)(local_c + -0x19)), local_8, a5, a6, a7);
	}
}

//D2Client.0x6FB0F5E0
void __fastcall sub_6FB0F5E0(D2UnitStrc* pUnit, int a2, int a3, D2SkillsTxt* pSkillsTxtRecord, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	Unicode* pThis;
	int iStack_64;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	iVar2 = a3;
	if (a3 <= a2)
	{
		iVar2 = a2 + 1;
	}
	if (a2 == iVar2)
	{
		wsprintfA(aCStack_60, "%d", a2);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
	}
	else
	{
		sub_6FB0B140((Unicode*)local_40, a2, iVar2, 0, 1);
	}
	a3 = 0;
	iStack_64 = 0;
	D2Win_10131_GetTextDimensions(local_40, &a3, &iStack_64);
	iVar1 = a7;
	iVar2 = a5;
	a3 = (a3 * 0xb) / 7;
	if (a7 - a5 < a3)
	{
		D2Win_10127_SetFont(D2FONT_FONT6);
		a6 = a6 + -1;
	}
	else
	{
		D2Win_10127_SetFont(D2FONT_FONT16);
	}
	sub_6FACFCD0(dword_6FBBA748 + iVar2, dword_6FBBA74C + gnScreenHeight + -0x1e0 + a6,
	    dword_6FBBA748 + iVar1, local_40, pSkillsTxtRecord);
}

//D2Client.0x6FB0F700
void __fastcall sub_6FB0F700(D2UnitStrc* pUnit, int a2, int* a3, int* a4, int a5, D2SkillsTxt* pSkillsTxtRecord, int a7)
{
	int* piVar1;
	int iVar2;
	D2SkillsTxt* pDVar3;
	D2SkillsTxt* pDVar4;
	Unicode* pUVar5;
	int iVar6;
	D2SkillsTxt* local_6c;
	D2SkillsTxt* local_68;
	D2SkillsTxt* pDStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	piVar1 = a3;
	if ((a2 != 0) && (a3 != nullptr))
	{
		iVar2 = sub_6FAAC080();
		local_68 = nullptr;
		local_6c = nullptr;
		a3 = nullptr;
		if (iVar2 == 0)
		{
			sub_6FB0C840(pUnit, (short*)piVar1, a4, (int*)(&a3), (int*)(&local_68), (uint32_t*)(&local_6c));
			iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
			if (iVar2 < -0x59)
			{
				iVar2 = -0x5a;
			}
			iVar6 = (int)a3 + (iVar2 * (int)a3) / 100;
			iVar2 = (int)local_68->dwFlags + (iVar2 * (int)local_68) / 100 + -4;
			local_68 = pSkillsTxtRecord;
			if (iVar2 <= iVar6)
			{
				iVar2 = iVar6 + 1;
			}
			pUVar5 = aUStack_40;
			a3 = (int*)0x20;
			do
			{
				pUVar5 = pUVar5 + 1;
				a3 = (int*)((int)a3 + -1);
			} while (a3 != nullptr);
			if (iVar6 == iVar2)
			{
				wsprintfA(aCStack_60, "%d", iVar6);
				Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_40, iVar6, iVar2, 0, 1);
			}
			a4 = nullptr;
			pDStack_64 = nullptr;
			D2Win_10131_GetTextDimensions(aUStack_40, (int*)&a4, (int*)&pDStack_64);
			iVar6 = a7;
			iVar2 = a5;
			a4 = (int*)(((int)a4 * 0xb) / 7);
			if (a7 - a5 < (int)a4)
			{
				D2Win_10127_SetFont(D2FONT_FONT6);
				pDVar4 = (D2SkillsTxt*)((int)&pSkillsTxtRecord[-1].nCostAdd + 3);
				pDVar3 = local_6c;
			}
			else
			{
				D2Win_10127_SetFont(D2FONT_FONT16);
				pDVar3 = local_6c;
				pDVar4 = local_68;
			}
		}
		else
		{
			sub_6FB0C840(pUnit, (short*)piVar1, a4, (int*)(&a3), (int*)(&local_6c), (uint32_t*)(&local_68));
			iVar2 = SKILLS_GetConcentrationDamageBonus(pUnit, (int)(short)*piVar1);
			iVar6 = (int)a3 + (iVar2 * (int)a3) / 100;
			iVar2 = (int)local_6c->dwFlags + (iVar2 * (int)local_6c) / 100 + -4;
			pDStack_64 = pSkillsTxtRecord;
			if (iVar2 <= iVar6)
			{
				iVar2 = iVar6 + 1;
			}
			pUVar5 = aUStack_40;
			a3 = (int*)0x20;
			do
			{
				pUVar5 = pUVar5 + 1;
				a3 = (int*)((int)a3 + -1);
			} while (a3 != nullptr);
			if (iVar6 == iVar2)
			{
				wsprintfA(aCStack_60, "%d", iVar6);
				Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_40, iVar6, iVar2, 0, 1);
			}
			a4 = nullptr;
			local_6c = nullptr;
			D2Win_10131_GetTextDimensions(aUStack_40, (int*)&a4, (int*)&local_6c);
			iVar6 = a7;
			iVar2 = a5;
			a4 = (int*)(((int)a4 * 0xb) / 7);
			if (a7 - a5 < (int)a4)
			{
				D2Win_10127_SetFont(D2FONT_FONT6);
				pDVar3 = local_68;
				pDVar4 = (D2SkillsTxt*)((int)&pSkillsTxtRecord[-1].nCostAdd + 3);
			}
			else
			{
				D2Win_10127_SetFont(D2FONT_FONT16);
				pDVar3 = local_68;
				pDVar4 = pDStack_64;
			}
		}
		sub_6FACFCD0(dword_6FBBA748 + iVar2, dword_6FBBA74C + gnScreenHeight + -0x1e0 + (int)pDVar4,
		    dword_6FBBA748 + iVar6, aUStack_40, pDVar3);
	}
}

//D2Client.0x6FB0FA50
void __fastcall sub_6FB0FA50(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int a3, uint32_t a4, int a5, int a6, int a7)
{
	int iVar1;
	int iVar2;
	Unicode* pThis;
	int local_7c;
	int local_78;
	D2SkillsTxt* local_74;
	int iStack_70;
	int iStack_6c;
	int iStack_68;
	D2SkillsTxt* pDStack_64;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	if ((pSkill != nullptr) && (a3 != 0))
	{
		local_78 = 0;
		local_7c = 0;
		local_74 = nullptr;
		sub_6FB0B2C0(pUnit, (uint32_t)&local_78, &local_7c, (uint32_t*)(&local_74), 0, 0, pSkill, 0, 0, 0);
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		if ((iVar2 < 0) ||
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar2 ||
		        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar2 == 0))))
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = *(int*)(iVar2 + 0x158);
		}
		local_78 = local_78 + (iVar2 * local_78) / 100;
		local_7c = local_7c + (iVar2 * local_7c) / 100;
		sub_6FB0B6F0(pUnit, &local_78, &local_7c, (uint32_t*)(&local_74), nullptr, pSkill);
		iVar1 = local_78;
		pDStack_64 = local_74;
		iVar2 = local_7c;
		if (local_7c <= local_78)
		{
			iVar2 = local_78 + 1;
		}
		if (iVar1 == iVar2)
		{
			wsprintfA(aCStack_60, "%d", iVar1);
			Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
		}
		else
		{
			sub_6FB0B140((Unicode*)aUStack_40, iVar1, iVar2, 0, 1);
		}
		iStack_70 = 0;
		iStack_68 = 0;
		D2Win_10131_GetTextDimensions(aUStack_40, &iStack_70, &iStack_68);
		iStack_70 = (iStack_70 * 0xb) / 7;
		if (a7 - a5 < iStack_70)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			a6 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
		}
		sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + a6,
		    dword_6FBBA748 + a7, aUStack_40, pDStack_64);
	}
}

//D2Client.0x6FB0FC60
void __fastcall sub_6FB0FC60(D2UnitStrc* pUnit, int a2, short* a3, uint32_t a4, int a5, int a6, uint32_t a7)
{
	short* psVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int iVar8;
	uint64_t uVar9;
	uint32_t uStack_14;
	uint32_t uStack_10;
	D2SkillsTxt* local_c;
	D2UnitStrc* local_8;
	int iStack_4;

	uVar7 = a4;
	if ((a2 != 0) && (a3 != nullptr))
	{
		iVar8 = (int)*a3;
		local_c = nullptr;
		local_8 = pUnit;
		iVar4 = SKILLS_GetMinPhysDamage(pUnit, iVar8, a4, 1);
		uStack_10 = iVar4 >> 8;
		iVar4 = SKILLS_GetMaxPhysDamage(pUnit, iVar8, uVar7, 1);
		uVar6 = iVar4 >> 8;
		iVar4 = sub_6FB0B580();
		uVar2 = uStack_10;
		if ((iVar8 < 0) ||
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar8 ||
		        (iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar8 * 0x23c, iVar8 == 0))))
		{
			iVar8 = 0;
		}
		else if ((int)uVar7 < 1)
		{
			iVar8 = 0;
		}
		else
		{
			iVar8 = *(int*)(iVar8 + 0x14c) * (uVar7 - 1) + *(int*)(iVar8 + 0x148);
		}
		uVar7 = iVar4 + iVar8;
		if (uVar7 != 0)
		{
			local_c = (D2SkillsTxt*)0x3;
		}
		if ((int)uStack_10 < 0x100001)
		{
			if ((int)uVar7 < 0x10001)
			{
				iVar4 = (int)(uVar7 * uStack_10) / 100;
			}
			else if ((int)(uVar7 & 0xfffffff0) < 0x640)
			{
				uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)uStack_10),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)uStack_10) >> 0x20), 100, 0);
				iVar4 = (int)uVar9;
			}
			else
			{
				iVar4 = ((int)uVar7 / 100) * uStack_10;
			}
		}
		else if ((int)(uStack_10 & 0xfffffff0) < 0x640)
		{
			uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)uStack_10),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)uStack_10) >> 0x20),
			    100, 0);
			iVar4 = (int)uVar9;
		}
		else
		{
			iVar4 = ((int)uStack_10 / 100) * uVar7;
		}
		uStack_10 = uVar2 + iVar4;
		if ((int)uVar6 < 0x100001)
		{
			if ((int)uVar7 < 0x10001)
			{
				iVar4 = (int)(uVar7 * uVar6) / 100;
			}
			else if ((int)(uVar7 & 0xfffffff0) < 0x640)
			{
				uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)uVar6),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)uVar6) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar9;
			}
			else
			{
				iVar4 = ((int)uVar7 / 100) * uVar6;
			}
		}
		else if ((int)(uVar6 & 0xfffffff0) < 0x640)
		{
			uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)uVar6),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)uVar6) >> 0x20), 100,
			    0);
			iVar4 = (int)uVar9;
		}
		else
		{
			iVar4 = ((int)uVar6 / 100) * uVar7;
		}
		a3 = nullptr;
		a4 = 0;
		uStack_14 = uVar7;
		SKILLS_CalculateKickDamage(local_8, (int*)&a3, (int*)&a4, (int*)&uStack_14);
		uVar7 = uStack_14;
		psVar1 = a3;
		if ((int)a3 < 0x100001)
		{
			if ((int)uStack_14 < 0x10001)
			{
				iVar8 = (int)(uStack_14 * (int)a3) / 100;
			}
			else if ((int)(uStack_14 & 0xfffffff0) < 0x640)
			{
				uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uStack_14 * (int64_t)(int)a3),
				    (uint32_t)((uint64_t)((int64_t)(int)uStack_14 * (int64_t)(int)a3) >>
				               0x20),
				    100, 0);
				iVar8 = (int)uVar9;
			}
			else
			{
				iVar8 = ((int)uStack_14 / 100) * (int)a3;
			}
		}
		else if ((int)((uint32_t)a3 & 0xfffffff0) < 0x640)
		{
			uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uStack_14 * (int64_t)(int)a3),
			    (uint32_t)((uint64_t)((int64_t)(int)uStack_14 * (int64_t)(int)a3) >> 0x20), 100, 0);
			iVar8 = (int)uVar9;
		}
		else
		{
			iVar8 = ((int)a3 / 100) * uStack_14;
		}
		uVar2 = a4;
		if ((int)a4 < 0x100001)
		{
			if ((int)uVar7 < 0x10001)
			{
				iVar5 = (int)(uVar7 * a4) / 100;
			}
			else if ((int)(uVar7 & 0xfffffff0) < 0x640)
			{
				uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)a4),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)a4) >> 0x20),
				    100, 0);
				iVar5 = (int)uVar9;
			}
			else
			{
				iVar5 = ((int)uVar7 / 100) * a4;
			}
		}
		else if ((int)(a4 & 0xfffffff0) < 0x640)
		{
			uVar9 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)a4),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)a4) >> 0x20),
			    100, 0);
			iVar5 = (int)uVar9;
		}
		else
		{
			iVar5 = ((int)a4 / 100) * uVar7;
		}
		pDVar3 = local_8;
		uVar7 = uStack_10;
		a4 = uVar2 + iVar5 + uVar6 + iVar4;
		uStack_10 = 0;
		iStack_4 = 0;
		a3 = (short*)((int)psVar1 + uVar7 + iVar8);
		sub_6FB0BB10(local_8, (int*)&uStack_10, (uint32_t*)(&iStack_4), (uint32_t*)(&local_c));
		a4 = a4 + iStack_4;
		a3 = (short*)((int)a3 + uStack_10);
		sub_6FB0F5E0(pDVar3, (int)a3, a4, local_c, a5, a6, a7);
	}
}

//D2Client.0x6FB10010
void __fastcall sub_6FB10010(D2UnitStrc* pUnit, int a2, short* a3, uint32_t a4, int a5, int a6, int a7)
{
	D2InventoryStrc* pInventory;
	uint8_t* pbVar1;
	D2SkillsTxt* pDVar2;
	D2UnitStrc* pTarget;
	uint8_t bVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	D2UnitStrc* pDVar8;
	uint32_t uVar9;
	int iVar10;
	uint32_t uVar11;
	D2UnitStrc* pItem;
	uint8_t* pbVar12;
	uint64_t uVar13;
	uint8_t* pbStack_5c;
	uint8_t* pbStack_58;
	uint32_t uStack_54;
	D2SkillsTxt* local_50;
	int local_4c;
	D2UnitStrc* local_48;
	int local_44;
	Unicode aUStack_40[32];

	uVar5 = a4;
	if ((a2 != 0) && (a3 != nullptr))
	{
		iVar10 = (int)*a3;
		switch ((char)a3[0xee])
		{
		case '\x01':
			local_50 = (D2SkillsTxt*)0x1;
			break;
		case '\x02':
			local_50 = (D2SkillsTxt*)0x9;
			break;
		case '\x03':
		case '\x04':
			local_50 = (D2SkillsTxt*)0x3;
			break;
		case '\x05':
			local_50 = (D2SkillsTxt*)0x2;
			break;
		default:
			local_50 = nullptr;
		}
		local_4c = iVar10;
		local_48 = pUnit;
		local_44 = a2;
		iVar4 = SKILLS_GetMinPhysDamage(pUnit, iVar10, a4, 0);
		uVar9 = iVar4 >> 8;
		iVar10 = SKILLS_GetMaxPhysDamage(pUnit, iVar10, uVar5, 0);
		uVar11 = iVar10 >> 8;
		uVar5 = sub_6FB0B580();
		if ((int)uVar9 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar10 = (int)(uVar5 * uVar9) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar9),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar9) >> 0x20),
				    100, 0);
				iVar10 = (int)uVar13;
			}
			else
			{
				iVar10 = ((int)uVar5 / 100) * uVar9;
			}
		}
		else if ((int)(uVar9 & 0xfffffff0) < 0x640)
		{
			uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar9),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar9) >> 0x20), 100, 0);
			iVar10 = (int)uVar13;
		}
		else
		{
			iVar10 = ((int)uVar9 / 100) * uVar5;
		}
		if ((int)uVar11 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar4 = (int)(uVar5 * uVar11) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar11),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar11) >> 0x20),
				    100, 0);
				iVar4 = (int)uVar13;
			}
			else
			{
				iVar4 = ((int)uVar5 / 100) * uVar11;
			}
		}
		else if ((int)(uVar11 & 0xfffffff0) < 0x640)
		{
			uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar11),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar11) >> 0x20),
			    100, 0);
			iVar4 = (int)uVar13;
		}
		else
		{
			iVar4 = ((int)uVar11 / 100) * uVar5;
		}
		pbStack_5c = nullptr;
		pbStack_58 = nullptr;
		uStack_54 = uVar5;
		SKILLS_CalculateKickDamage(pUnit, (int*)&pbStack_5c, (int*)&pbStack_58, (int*)&uStack_54);
		uVar5 = uStack_54;
		pbVar12 = pbStack_5c;
		if ((int)pbStack_5c < 0x100001)
		{
			if ((int)uStack_54 < 0x10001)
			{
				iVar6 = (int)(uStack_54 * (int)pbStack_5c) / 100;
			}
			else if ((int)(uStack_54 & 0xfffffff0) < 0x640)
			{
				uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uStack_54 * (int64_t)(int)pbStack_5c),
				    (uint32_t)((uint64_t)((int64_t)(int)uStack_54 * (int64_t)(int)pbStack_5c) >> 0x20), 100, 0);
				iVar6 = (int)uVar13;
			}
			else
			{
				iVar6 = ((int)uStack_54 / 100) * (int)pbStack_5c;
			}
		}
		else if ((int)((uint32_t)pbStack_5c & 0xfffffff0) < 0x640)
		{
			uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uStack_54 * (int64_t)(int)pbStack_5c),
			    (uint32_t)((uint64_t)((int64_t)(int)uStack_54 * (int64_t)(int)pbStack_5c) >>
			               0x20),
			    100, 0);
			iVar6 = (int)uVar13;
		}
		else
		{
			iVar6 = ((int)pbStack_5c / 100) * uStack_54;
		}
		pbVar1 = pbStack_58;
		pbStack_5c = pbVar12 + iVar6;
		if ((int)pbStack_58 < 0x100001)
		{
			if ((int)uVar5 < 0x10001)
			{
				iVar6 = (int)(uVar5 * (int)pbStack_58) / 100;
			}
			else if ((int)(uVar5 & 0xfffffff0) < 0x640)
			{
				uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)pbStack_58),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)pbStack_58) >>
				               0x20),
				    100, 0);
				iVar6 = (int)uVar13;
			}
			else
			{
				iVar6 = ((int)uVar5 / 100) * (int)pbStack_58;
			}
		}
		else if ((int)((uint32_t)pbStack_58 & 0xfffffff0) < 0x640)
		{
			uVar13 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)pbStack_58),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)pbStack_58) >> 0x20), 100, 0);
			iVar6 = (int)uVar13;
		}
		else
		{
			iVar6 = ((int)pbStack_58 / 100) * uVar5;
		}
		pTarget = local_48;
		pbStack_5c = pbStack_5c + uVar9 + iVar10;
		pbStack_58 = pbVar1 + iVar6 + uVar11 + iVar4;
		iVar10 = SKILLS_EvaluateSkillFormula(local_48, *(uint32_t*)(a3 + 0x9c), local_4c, a4);
		pDVar7 = sub_6FAE5BD0((int)pbStack_5c, iVar10, 100);
		pbStack_5c = pDVar7->unk0x19 + (int)(pbStack_5c + -0x19);
		pDVar7 = sub_6FAE5BD0((int)pbStack_58, iVar10, 100);
		pInventory = pTarget->pInventory;
		pbStack_58 = pDVar7->unk0x19 + (int)(pbStack_58 + -0x19);
		if (pInventory != nullptr)
		{
			pDVar7 = INVENTORY_GetLeftHandWeapon(pInventory);
			pItem = nullptr;
			if (pDVar7 != nullptr)
			{
				bVar3 = ITEMS_GetBodyLocation(pDVar7);
				pItem = INVENTORY_GetItemFromBodyLoc(pInventory, (bVar3 == 4) + 4);
			}
			iVar10 = ITEMS_CheckItemTypeId(pDVar7, 0x2d);
			if (((iVar10 == 0) || (iVar10 = ITEMS_CanBeEquipped(pDVar7), iVar10 == 0)) ||
			    (pDVar8 = STATLIST_GetOwner(pDVar7, nullptr), pDVar8 == nullptr))
			{
				pDVar7 = nullptr;
			}
			else
			{
				STATLIST_MergeStatLists(pTarget, pDVar7, 0);
			}
			if (((pItem != nullptr) && (pItem != pDVar7)) &&
			    ((iVar10 = ITEMS_CheckItemTypeId(pItem, 0x2d), iVar10 != 0 &&
			                                                       ((iVar10 = ITEMS_CanBeEquipped(pItem), iVar10 != 0 &&
			                                                                                                  (pDVar8 = STATLIST_GetOwner(pItem, nullptr), pDVar8 != nullptr))))))
			{
				STATLIST_MergeStatLists(pTarget, pItem, 0);
			}
			sub_6FB0B6F0(pTarget, (int*)&pbStack_5c, (int*)&pbStack_58, (uint32_t*)(&local_50), nullptr,
			    (D2SkillStrc*)(local_44));
			if (pDVar7 != nullptr)
			{
				STATLIST_MergeStatLists(pTarget, pDVar7, 1);
			}
		}
		pDVar2 = local_50;
		pbVar1 = pbStack_5c;
		iVar10 = a6;
		pbVar12 = pbStack_58;
		if ((int)pbStack_58 <= (int)pbStack_5c)
		{
			pbVar12 = pbStack_5c + 1;
		}
		memset(aUStack_40, 0, 2 * (0x20));
		sub_6FB0B250((Unicode*)aUStack_40, (int)pbVar1, (int)pbVar12, 0);
		a4 = 0;
		a3 = nullptr;
		D2Win_10131_GetTextDimensions(aUStack_40, (int*)&a4, (int*)&a3);
		iVar6 = a7;
		iVar4 = a5;
		a4 = (int)(a4 * 0xb) / 7;
		if (a7 - a5 < (int)a4)
		{
			D2Win_10127_SetFont(D2FONT_FONT6);
			iVar10 = a6 + -1;
		}
		else
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
		}
		sub_6FACFCD0(dword_6FBBA748 + iVar4, iVar10 + dword_6FBBA74C + -0x1e0 + gnScreenHeight,
		    dword_6FBBA748 + iVar6, aUStack_40, pDVar2);
	}
}

//D2Client.0x6FB10540
void __fastcall sub_6FB10540(D2UnitStrc* pUnit, D2SkillsTxt* pSkillsTxtRecord, short* a3, int* a4, int a5, int a6, int a7)
{
	D2SkillsTxt* pDVar1;
	int iVar2;
	Unicode* pUVar3;
	int iVar4;
	int iVar5;
	int iStack_a0;
	int iStack_9c;
	D2SkillsTxt* local_98;
	int local_94;
	D2SkillsTxt* local_90;
	int local_8c;
	int iStack_88;
	int iStack_84;
	Unicode aUStack_80[32];
	Unicode aUStack_40[32];

	if (((((pSkillsTxtRecord == nullptr) || (a3 == nullptr)) ||
	         (iVar2 = (int)*a3, iVar2 < 0)) ||
	        ((iVar5 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar5 + 0xba0) <= iVar2 ||
	                                                          (iVar4 = *(int*)(iVar5 + 0xb98) + iVar2 * 0x23c, iVar4 == 0)))) ||
	    ((iVar4 = (int)*(short*)(iVar4 + 0x194), iVar4 < 0 ||
	                                                 ((*(int*)(iVar5 + 0xb94) <= iVar4 ||
	                                                     (iVar5 = iVar4 * 0x120 + *(int*)(iVar5 + 0xb8c), iVar5 == 0))))))
	{
		return;
	}
	local_94 = 0;
	local_8c = 0;
	local_90 = nullptr;
	local_98 = pSkillsTxtRecord;
	iStack_a0 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar5 + 0x18), iVar2, (int)a4);
	iVar2 = SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(iVar5 + 0x1c), iVar2, (int)a4);
	pDVar1 = local_98;
	sub_6FB0B2C0(pUnit, (uint32_t)&local_94, &local_8c, (uint32_t*)(&local_90), iStack_a0, iVar2, (D2SkillStrc*)(local_98), 0x80, 0, 0);
	sub_6FB0B6F0(pUnit, &local_94, &local_8c, (uint32_t*)(&local_90), nullptr, (D2SkillStrc*)(pDVar1));
	iStack_a0 = 0;
	iStack_9c = 0;
	local_98 = nullptr;
	sub_6FB0C840(pUnit, a3, a4, &iStack_a0, &iStack_9c, (uint32_t*)(&local_98));
	iVar5 = local_94;
	iVar2 = iStack_a0;
	if ((local_94 == 0) && (local_8c == 0))
	{
		iStack_84 = a6;
		iVar5 = iStack_9c;
		if (iStack_9c <= iStack_a0)
		{
			iVar5 = iStack_a0 + 1;
		}
		sub_6FB0B250((Unicode*)aUStack_80, iVar2, iVar5, 0);
		iStack_9c = 0;
		iStack_88 = 0;
		D2Win_10131_GetTextDimensions(aUStack_80, &iStack_9c, &iStack_88);
		iStack_9c = (iStack_9c * 0xb) / 7;
		if (iStack_9c <= a7 - a5)
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar2 = iStack_84;
			goto LAB_6fb1072f;
		}
	}
	else
	{
		if ((iStack_a0 != 0) || (iStack_9c != 0))
		{
			if (local_94 == local_8c)
			{
				sub_6FB0B0F0((Unicode*)aUStack_40, local_94, 0);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_40, local_94, local_8c, 0, 1);
			}
			if (iVar2 == iStack_9c)
			{
				sub_6FB0B0F0((Unicode*)aUStack_80, iVar2, 0);
			}
			else
			{
				sub_6FB0B140((Unicode*)aUStack_80, iVar2, iStack_9c, 0, 1);
			}
			sub_6FB0AC10((uint32_t)(aUStack_40), (uint32_t)(aUStack_80), a5, a6, a7, local_90, local_98);
			return;
		}
		iStack_88 = a6;
		local_98 = local_90;
		iVar2 = local_8c;
		if (local_8c <= local_94)
		{
			iVar2 = local_94 + 1;
		}
		sub_6FB0B250((Unicode*)aUStack_80, iVar5, iVar2, 0);
		iStack_a0 = 0;
		iStack_84 = 0;
		D2Win_10131_GetTextDimensions(aUStack_80, &iStack_a0, &iStack_84);
		iStack_a0 = (iStack_a0 * 0xb) / 7;
		if (iStack_a0 <= a7 - a5)
		{
			D2Win_10127_SetFont(D2FONT_FONT16);
			iVar2 = iStack_88;
			goto LAB_6fb1072f;
		}
	}
	D2Win_10127_SetFont(D2FONT_FONT6);
	iVar2 = a6 + -1;
LAB_6fb1072f:
	sub_6FACFCD0(dword_6FBBA748 + a5, dword_6FBBA74C + gnScreenHeight + -0x1e0 + iVar2,
	    dword_6FBBA748 + a7, aUStack_80, local_98);
}

//D2Client.0x6FB108F0
void __fastcall sub_6FB108F0(D2UnitStrc* pUnit, D2SkillStrc* pSkill, short* a3, int a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
	int iVar1;
	int iVar2;

	if (((((pSkill != nullptr) && (a3 != nullptr)) &&
	         (iVar2 = (int)*a3, -1 < iVar2)) &&
	        ((iVar1 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar1 + 0xba0) &&
	                                                          (iVar2 = *(int*)(iVar1 + 0xb98) + iVar2 * 0x23c, iVar2 != 0)))) &&
	    ((iVar2 = (int)*(short*)(iVar2 + 0x194), -1 < iVar2 &&
	                                                 ((iVar2 < *(int*)(iVar1 + 0xb94) && (iVar2 * 0x120 + *(int*)(iVar1 + 0xb8c) != 0))))))
	{
		sub_6FB0BEC0(pUnit, pSkill, a3, a4, a5, a6, a7);
	}
}

//D2Client.0x6FB10970
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB10970(D2UnitStrc* pUnit, char* a2, int a32, int a4, int* a5, int a6, int a7, uint32_t a8)
{
	uint8_t bVar1;
	int iVar2;
	uint8_t* pbVar3;
	uint32_t uVar4;
	int iVar5;
	D2DifficultyLevelsTxt* pDVar6;
	D2UnitStrc* pDVar7;
	Unicode* a3;
	int iVar8;
	uint32_t uVar9;
	Unicode* pUVar10;
	short sVar11;
	short sVar12;
	uint16_t extraout_var;
	char cVar13;
	D2MonStatsInitStrc* pDVar14;
	uint32_t* puVar15;
	code* pcVar16;
	uint32_t uVar17;
	int iVar18;
	uint8_t* pbVar19;
	uint8_t* pbStack_31c;
	short* psStack_318;
	uint8_t* pbStack_314;
	short* psStack_310;
	uint8_t* local_30c;
	D2MonStatsInitStrc DStack_308;
	Unicode aUStack_2c8[100];
	Unicode aUStack_200[256];

	if (a32 == 0)
	{
		return 0;
	}
	if (a4 < 0)
	{
		return 0;
	}
	iVar18 = *(int*)((uint8_t*)&sgptDataTables);
	if (*(int*)(iVar18 + 0xba0) <= a4)
	{
		return 0;
	}
	iVar2 = *(int*)(iVar18 + 0xb98) + a4 * 0x23c;
	if (iVar2 == 0)
	{
		return 0;
	}
	iVar2 = (int)*(short*)(iVar2 + 0x194);
	if (iVar2 < 0)
	{
		return 0;
	}
	if (*(int*)(iVar18 + 0xb94) <= iVar2)
	{
		return 0;
	}
	local_30c = (uint8_t*)(iVar2 * 0x120 + *(int*)(iVar18 + 0xb8c));
	if (local_30c == nullptr)
	{
		return 0;
	}
	pbVar3 = (uint8_t*)SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(local_30c + a7 * 4 + 0x98), a4, (int)a5);
	pbStack_314 = (uint8_t*)SKILLS_EvaluateSkillDescFormula(pUnit, *(uint32_t*)(local_30c + a7 * 4 + 0xdc), a4,
	    (int)a5);
	sVar11 = *(short*)(local_30c + a7 * 2 + 0x54);
	iVar18 = CONCAT22((short)((uint32_t)a7 >> 0x10), sVar11);
	sVar12 = *(short*)(local_30c + a7 * 2 + 0x76);
	pbStack_31c = (uint8_t*)CONCAT22((*(uint16_t*)((uint8_t*)&pbStack_31c + 2)), sVar12);
	cVar13 = (char)pbVar3;
	switch (local_30c[a7 + 0x42])
	{
	case 1:
		if ((*(short*)(a32 + 0x18a) == 0) && (*(short*)(a32 + 0x18c) == 0))
		{
			return 1;
		}
		if (a6 != 0)
		{
			sub_6FB13E70((Unicode*)(a2), a6);
			return 1;
		}
		iVar18 = sub_6FB14AE0(a4);
		if (iVar18 == 0)
		{
			return 1;
		}
		iVar18 = (int)*(short*)(iVar18 + 0x194);
		if (iVar18 < 0)
		{
			return 1;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb94) <= iVar18)
		{
			return 1;
		}
		iVar18 = iVar18 * 0x120 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb8c);
		if (iVar18 == 0)
		{
			return 1;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		sVar11 = *(short*)(iVar18 + 0x10);
		psStack_318 = (short*)CONCAT22((*(uint16_t*)((uint8_t*)&psStack_318 + 2)), sVar11);
		sVar12 = *(short*)(a32 + 0x188);
		psStack_310 = (short*)D2C_ZEXT(sVar12);
		uVar17 = ((int)a5 + -1) * (int)*(short*)(a32 + 0x18c) +
		             (int)*(short*)(a32 + 0x18a)
		         << ((uint8_t)sVar12 & 0x1f);
		uVar4 = *(short*)(a32 + 0x186) * 0x100;
		if ((int)uVar17 < (int)uVar4)
		{
			uVar17 = uVar4;
		}
		if (((sVar12 != 8) && ((int)*(short*)(a32 + 0x18c) << ((uint8_t)sVar12 & 0x1f) < 0x101)) &&
		    ((int)uVar17 < 0x1901))
		{
			if (10 < (int)pbVar3)
			{
				sub_6FB13790((Unicode*)(a2), sVar11, 0x1506, uVar17, (int)pbVar3, 0);
				return 1;
			}
			uVar4 = uVar17 & 0x800000ff;
			if ((int)uVar4 < 0)
			{
				uVar4 = (uVar4 - 1 | 0xffffff00) + 1;
			}
			sub_6FB138E0((Unicode*)(a2), (int)psStack_318, (int)(uVar17 + ((int)uVar17 >> 0x1f & 0xffU)) >> 8,
			    (int)(uVar4 * 10 + ((int)(uVar4 * 10) >> 0x1f & 0xffU)) >> 8, 0);
			return 1;
		}
		sub_6FB136E0((Unicode*)(a2), (int)psStack_318, (int)uVar17 >> 8, 0);
		return 1;
	case 2:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 1);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 3:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 4:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 1);
		goto LAB_6fb125be;
	case 5:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 0);
		goto LAB_6fb125be;
	case 6:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		iVar18 = 1;
		goto LAB_6fb10dc8;
	case 7:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		iVar18 = 0;
	LAB_6fb10dc8:
		psStack_318 = nullptr;
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, iVar18);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
	LAB_6fb12d39:
		(*pcVar16)();
		sVar12 = sVar11;
	LAB_6fb12d3f:
		D2LANG_GetStringFromTblIndex(sVar12);
		(*pcVar16)();
	LAB_6fb12d4a:
		D2LANG_GetStringFromTblIndex(0xf9e);
		(*pcVar16)();
		return 1;
	case 8:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetToHitFactor(pUnit, a4, (int)a5);
		if (iVar18 == 0)
		{
			return 1;
		}
		sub_6FB13B50((Unicode*)(a2), 0x10a6, 0x10b3, iVar18, 1);
		return 1;
	case 9:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		sub_6FB14240(pUnit, a2, a4, a32, (int)(a5), (uint32_t)(pbVar3), (int)(pbStack_314));
		return 1;
	case 10:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetMinElemDamage(pUnit, a4, (int)a5, 1);
		iVar2 = SKILLS_GetMaxElemDamage(pUnit, a4, (int)a5, 1);
		if ((iVar18 == 0) && (iVar2 == 0))
		{
			return 1;
		}
		sub_6FB13FA0((Unicode*)(a2), iVar18 >> 8, iVar2 >> 8, (uint32_t) * (uint8_t*)(a32 + 0x1dc), 0);
		return 1;
	case 0xb:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetElementalLength(pUnit, a4, (int)a5, 0);
		if (iVar18 == 0)
		{
			return 1;
		}
		if (*(char*)(a32 + 0x1dc) == '\x04')
		{
			sub_6FB13410((Unicode*)(a2), 0x10a9, iVar18, 0);
			return 1;
		}
		if (*(char*)(a32 + 0x1dc) != '\x05')
		{
			return 1;
		}
		sub_6FB13410((Unicode*)(a2), 0x10aa, iVar18, 0);
		return 1;
	case 0xc:
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		sub_6FB13410((Unicode*)(a2), iVar18, (int)pbVar3, 0);
		return 1;
	case 0xd:
		iVar18 = (int)*(short*)(a32 + 0xbc);
		if (iVar18 < 0)
		{
			return 1;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar18)
		{
			return 1;
		}
		psStack_310 = (short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar18 * 0x1a8);
		if (psStack_310 == nullptr)
		{
			return 1;
		}
		bVar1 = sub_6FAAC090();
		uVar17 = (uint32_t)bVar1;
		pDVar14 = &DStack_308;
		for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar14->nMinHP = 0;
			pDVar14 = (D2MonStatsInitStrc*)&pDVar14->nMaxHP;
		}
		pDVar14 = &DStack_308;
		sVar11 = 1;
		iVar8 = (int)psStack_310[uVar17 + 0x55];
		iVar2 = sub_6FAAC060();
		iVar18 = DATATBLS_CalculateMonsterStatsByLevel(iVar18, iVar2, uVar17, iVar8, sVar11, pDVar14);
		if (iVar18 == 0)
		{
			return 1;
		}
		iVar18 = (DStack_308.nMaxHP + DStack_308.nMinHP) / 2;
		if (pbStack_314 + iVar18 + (iVar18 * (int)pbVar3) / 100 == nullptr)
		{
			return 1;
		}
		sub_6FB136E0((Unicode*)(a2), 0x10c6, (int)(pbStack_314 + iVar18 + (iVar18 * (int)pbVar3) / 100), 0);
		return 1;
	case 0xe:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetElementalLength(pUnit, a4, (int)a5, 0);
		psStack_310 = (short*)SKILLS_GetMinElemDamage(pUnit, a4, (int)a5, 1);
		iVar2 = SKILLS_GetMaxElemDamage(pUnit, a4, (int)a5, 1);
		sub_6FB13410((Unicode*)(a2), 0x2b0e, iVar18, 0);
		sub_6FB13FA0((Unicode*)(a2), (int)psStack_310 * iVar18 >> 8, iVar2 * iVar18 >> 8,
		    (uint32_t) * (uint8_t*)(a32 + 0x1dc), 0);
		return 1;
	case 0xf:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 0x10:
		pDVar14 = &DStack_308;
		iVar18 = 0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			iVar18 = iVar18 + -1;
		} while (iVar18 != 0);
		iVar8 = (int)pbVar3 / 0x19;
		iVar18 = (((int)pbVar3 % 0x19) * 10) / 0x19;
		iVar5 = (int)pbStack_314 / 0x19;
		iVar2 = (((int)pbStack_314 % 0x19) * 10) / 0x19;
		if (iVar8 == 0)
		{
			if (iVar18 != 0)
				goto LAB_6fb112b8;
			if (iVar5 == 0)
			{
				return 1;
			}
		LAB_6fb112a4:
			if (iVar2 != 0)
				goto LAB_6fb112b8;
			sub_6FB0B140((Unicode*)&DStack_308, iVar8, iVar5, 0, 0);
		}
		else
		{
			if (iVar18 == 0)
				goto LAB_6fb112a4;
		LAB_6fb112b8:
			sub_6FB133C0((Unicode*)&DStack_308, iVar8, iVar18, iVar5, iVar2, 0);
		}
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10b0));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(0x10ac);
		break;
	case 0x11:
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (pbVar3 == pbStack_314)
		{
			sub_6FB13B50((Unicode*)(a2), iVar18, 0x10be, (int)pbVar3, 0);
			return 1;
		}
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		sub_6FB0B140((Unicode*)&DStack_308, (int)pbVar3, (int)pbStack_314, 0, 0);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		(*pcVar16)();
		D2LANG_GetStringFromTblIndex(0x10be);
		break;
	case 0x12:
		pUVar10 = aUStack_200;
		psStack_318 = (short*)0x100;
		do
		{
			pUVar10 = pUVar10 + 1;
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::strcpy(aUStack_200, pUVar10);
		if (0 < (int)pbVar3)
		{
			sub_6FB20430((short*)aUStack_200, cVar13);
		}
		Unicode::strcat((Unicode*)a2, aUStack_200);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcpy(aUStack_200, pUVar10);
		sub_6FB20430((short*)aUStack_200, (char)a8);
		Unicode::strcat((Unicode*)a2, aUStack_200);
		return 1;
	case 0x13:
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		iVar18 = ((int)pbVar3 * 0x14) / 3;
		iVar2 = iVar18 / 10;
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		sub_6FB13320((Unicode*)&DStack_308, iVar2, iVar18 % 10, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		sVar11 = 0x10c0;
		if (iVar2 != 1)
		{
			sVar11 = 0x10b6;
		}
		D2LANG_GetStringFromTblIndex(sVar11);
		break;
	case 0x14:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 1);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10b3));
		Unicode::strcat((Unicode*)a2, pUVar10);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 0x15:
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10b3));
		Unicode::strcat((Unicode*)a2, pUVar10);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 0x16:
		iVar2 = (int)*(short*)(local_30c + 0x3c);
		iVar18 = MISSILE_GetMinElemDamage(nullptr, pUnit, iVar2, (int)a5);
		pbStack_314 = (uint8_t*)(iVar18 * 0x4b);
		iVar18 = MISSILE_GetMaxElemDamage(nullptr, pUnit, iVar2, (int)a5);
		local_30c = (uint8_t*)(iVar18 * 0x4b);
		sub_6FB12F80(a32, (uint32_t*)&pbStack_314, (uint32_t*)(&local_30c));
		sub_6FB13120(a32, (uint32_t*)&pbStack_314, (uint32_t*)(&local_30c));
		pbStack_314 = (uint8_t*)((int)pbStack_314 >> 8);
		local_30c = (uint8_t*)((int)local_30c >> 8);
		bVar1 = MISSILE_GetElemTypeFromMissileId(iVar2);
		switch (bVar1)
		{
		default:
			uVar9 = 0x10a1;
			break;
		case 2:
			uVar9 = 0x10a3;
			break;
		case 3:
			uVar9 = 0x10c3;
			break;
		case 4:
			uVar9 = 0x10a2;
			break;
		case 5:
			uVar9 = 0x10a4;
			break;
		case 6:
			uVar9 = 0xdc4;
		}
		sub_6FB14530((Unicode*)(a2), (int)pbStack_314, (int)local_30c, uVar9);
		return 1;
	case 0x17:
		iVar2 = (int)*(short*)(local_30c + 0x3c);
		if (iVar2 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)
		{
			return 0;
		}
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4;
		goto LAB_6fb11c02;
	case 0x18:
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetMinElemDamage(pUnit, a4, (int)a5, 1);
		iVar2 = SKILLS_GetMaxElemDamage(pUnit, a4, (int)a5, 1);
		if ((iVar18 == 0) && (iVar2 == 0))
		{
			return 1;
		}
		sub_6FB13FA0((Unicode*)(a2), iVar18 >> 8, iVar2 >> 8, (uint32_t) * (uint8_t*)(a32 + 0x1dc), sVar11);
		return 1;
	case 0x19:
		pUVar10 = aUStack_200;
		psStack_318 = (short*)0x100;
		do
		{
			pUVar10 = pUVar10 + 1;
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::strcpy(aUStack_200, pUVar10);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat(aUStack_200, pUVar10);
		}
		if (0 < (int)pbVar3)
		{
			sub_6FB20430((short*)aUStack_200, cVar13);
		}
		Unicode::strcat((Unicode*)a2, aUStack_200);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcpy(aUStack_200, pUVar10);
		goto LAB_6fb12541;
	case 0x1a:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetMinElemDamage(pUnit, a4, (int)a5, 1);
		psStack_310 = (short*)(iVar18 * 0x19 >> 8);
		iVar18 = SKILLS_GetMaxElemDamage(pUnit, a4, (int)a5, 1);
		iVar18 = iVar18 * 0x19 >> 8;
		switch (*(uint8_t*)(a32 + 0x1dc))
		{
		default:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0x10a1);
			return 1;
		case 2:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0x10a3);
			return 1;
		case 3:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0x10c3);
			return 1;
		case 4:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0x10a2);
			return 1;
		case 5:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0x10a4);
			return 1;
		case 6:
			sub_6FB14530((Unicode*)(a2), (int)psStack_310, iVar18, 0xdc4);
			return 1;
		}
	case 0x1b:
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		iVar18 = SKILLS_GetMinElemDamage(pUnit, a4, (int)a5, 1);
		iVar2 = SKILLS_GetMaxElemDamage(pUnit, a4, (int)a5, 1);
		sub_6FB14530((Unicode*)(a2), iVar18 * 0x4b >> 8, iVar2 * 0x4b >> 8, 0x10a1);
		return 1;
	case 0x1c:
		iVar18 = (int)*(short*)(local_30c + 0x3c);
		if (iVar18 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar18)
		{
			return 0;
		}
		iVar18 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar18 * 0x1a4;
		if (iVar18 == 0)
		{
			return 0;
		}
		iVar18 = *(int*)(iVar18 + 0x38);
		pDVar14 = &DStack_308;
		iVar2 = 0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		iVar18 = (iVar18 * 0x14) / 3;
		iVar2 = iVar18 / 10;
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		sub_6FB13320((Unicode*)&DStack_308, iVar2, iVar18 % 10, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10ae));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		sVar12 = 0x10c0;
		if (iVar2 != 1)
		{
			sVar12 = 0x10b6;
		}
		goto LAB_6fb12d3f;
	case 0x1d:
		iVar18 = (int)*(short*)(local_30c + 0x3c);
		if (iVar18 < 0)
		{
			return 0;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar18)
		{
			return 0;
		}
		iVar18 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar18 * 0x1a4;
		if (iVar18 == 0)
		{
			return 0;
		}
		pDVar14 = &DStack_308;
		iVar2 = 0x20;
		iVar18 = (((int)*(short*)(iVar18 + 0x98) * ((int)a5 + -1) + (int)*(short*)(iVar18 + 0x96)) * 2) / 3;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		if (iVar18 == 0)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, iVar18, 0);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(0x10b6);
		break;
	case 0x1e:
		iVar2 = (int)*(short*)(local_30c + 0x3c);
		if (iVar2 < 0)
		{
			return 0;
		}
		iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c);
		if (iVar8 <= iVar2)
		{
			return 0;
		}
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64);
		iVar2 = iVar5 + iVar2 * 0x1a4;
		if (iVar2 == 0)
		{
			return 0;
		}
		iVar2 = (int)*(short*)(iVar2 + 0x18);
		if (iVar2 < 0)
		{
			return 0;
		}
		if (iVar8 <= iVar2)
		{
			return 0;
		}
		iVar5 = iVar5 + iVar2 * 0x1a4;
	LAB_6fb11c02:
		if (iVar5 != 0)
		{
			sub_6FB13410((Unicode*)(a2), iVar18,
			    (int)*(short*)(iVar5 + 0x98) * (int)a5 + (int)*(short*)(iVar5 + 0x96), 0);
			return 1;
		}
	switchD_6fb10a7b_default:
		return 0;
	case 0x1f:
		bVar1 = sub_6FAAC090();
		pDVar6 = DATATBLS_GetDifficultyLevelsTxtRecord((uint32_t)bVar1);
		if (0 < (int)pDVar6->dwAiCurseDiv)
		{
			pbVar3 = (uint8_t*)((int)pbVar3 / (int)pDVar6->dwAiCurseDiv);
		}
		sub_6FB13410((Unicode*)(a2), iVar18, (int)pbVar3, 0);
		return 1;
	case 0x20:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pDVar14 = &DStack_308;
		psStack_318 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 1);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(0x10b3);
		break;
	case 0x21:
		if ((int)a5 < 2)
		{
			return 1;
		}
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 0x22:
		iVar18 = (int)*(short*)(a32 + 0xbc);
		if (iVar18 < 0)
		{
			return 1;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar18)
		{
			return 1;
		}
		iVar18 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar18 * 0x1a8;
		if (iVar18 == 0)
		{
			return 1;
		}
		pDVar14 = &DStack_308;
		for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar14->nMinHP = 0;
			pDVar14 = (D2MonStatsInitStrc*)&pDVar14->nMaxHP;
		}
		pDVar14 = &DStack_308;
		sVar11 = 8;
		bVar1 = sub_6FAAC090();
		iVar2 = (int)*(short*)(iVar18 + 0xaa + (uint32_t)bVar1 * 2);
		bVar1 = sub_6FAAC090();
		uVar17 = (uint32_t)bVar1;
		iVar18 = sub_6FAAC060();
		DATATBLS_CalculateMonsterStatsByLevel((int)*(short*)(a32 + 0xbc), iVar18, uVar17, iVar2, sVar11, pDVar14);
		puVar15 = (uint32_t*)(a32 + 0x68);
		psStack_318 = (short*)(a32 + 0x54);
		pbStack_31c = (uint8_t*)DStack_308.nA1MinD;
		pbStack_314 = (uint8_t*)DStack_308.nA1MaxD;
		local_30c = nullptr;
		psStack_310 = (short*)0x6;
		do
		{
			if (*psStack_318 == 0x19)
			{
				iVar18 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				local_30c = local_30c + iVar18;
			}
			if (*psStack_318 == 0x6f)
			{
				iVar18 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				pbStack_31c = pbStack_31c + iVar18;
				pbStack_314 = pbStack_314 + iVar18;
			}
			psStack_318 = psStack_318 + 1;
			puVar15 = puVar15 + 1;
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		psStack_310 = (short*)0x5;
		puVar15 = (uint32_t*)(a32 + 0xa4);
		psStack_318 = (short*)(a32 + 0x98);
		do
		{
			if (*psStack_318 == 0x19)
			{
				iVar18 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				local_30c = local_30c + iVar18;
			}
			if (*psStack_318 == 0x6f)
			{
				iVar18 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				pbStack_31c = pbStack_31c + iVar18;
				pbStack_314 = pbStack_314 + iVar18;
			}
			psStack_318 = psStack_318 + 1;
			puVar15 = puVar15 + 1;
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		if (local_30c != nullptr)
		{
			if ((int)local_30c < -0x59)
			{
				local_30c = (uint8_t*)0xffffffa6;
			}
			pbVar19 = local_30c;
			pDVar7 = sub_6FAE5BD0((int)pbStack_31c, (int)local_30c, 100);
			pbVar3 = pbStack_314;
			pbStack_31c = pDVar7->unk0x19 + (int)(pbStack_31c + -0x19);
			pDVar7 = sub_6FAE5BD0((int)pbStack_314, (int)pbVar19, 100);
			pbStack_314 = pDVar7->unk0x19 + (int)(pbVar3 + -0x19);
		}
		sub_6FB13FA0((Unicode*)(a2), (int)pbStack_31c, (int)pbStack_314, 0, 0x10a0);
		return 1;
	case 0x23:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pDVar14 = &DStack_308;
		psStack_310 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		sub_6FB0B140((Unicode*)&DStack_308, (int)pbVar3, (int)pbStack_314, 0, 0);
		break;
	case 0x24:
		pDVar14 = &DStack_308;
		psStack_310 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		if (pbVar3 == nullptr)
		{
			return 1;
		}
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, 0);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		if (pbVar3 != (uint8_t*)0x1)
		{
			sVar11 = sVar12;
		}
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)a2, pUVar10);
		return 1;
	case 0x25:
		pDVar14 = &DStack_308;
		psStack_310 = (short*)0x20;
		do
		{
			memset((Unicode*)pDVar14, 0, sizeof(Unicode));
			pDVar14 = (D2MonStatsInitStrc*)((int)&pDVar14->nMinHP + 2);
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		iVar18 = ((int)pbVar3 * 10) / 3;
		iVar2 = iVar18 / 10;
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		sub_6FB13320((Unicode*)&DStack_308, iVar2, iVar18 % 10, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		sVar11 = 0x10c0;
		if (iVar2 != 1)
		{
			sVar11 = 0x10b6;
		}
		D2LANG_GetStringFromTblIndex(sVar11);
		break;
	case 0x26:
		if (pbVar3 == pbStack_314)
		{
		LAB_6fb1286c:
			sub_6FB13B50((Unicode*)(a2), iVar18, (int)pbStack_31c, (int)pbVar3, 0);
			return 1;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		iVar18 = 0;
		goto LAB_6fb120d6;
	case 0x27:
		iVar18 = sub_6FAAE570((int)*(short*)(a32 + 0xbc));
		if (iVar18 == 0)
		{
			return 1;
		}
		pDVar14 = &DStack_308;
		for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar14->nMinHP = 0;
			pDVar14 = (D2MonStatsInitStrc*)&pDVar14->nMaxHP;
		}
		pDVar14 = &DStack_308;
		sVar11 = 8;
		bVar1 = sub_6FAAC090();
		iVar2 = (int)*(short*)(iVar18 + 0xaa + (uint32_t)bVar1 * 2);
		bVar1 = sub_6FAAC090();
		uVar17 = (uint32_t)bVar1;
		iVar18 = sub_6FAAC060();
		DATATBLS_CalculateMonsterStatsByLevel((int)*(short*)(a32 + 0xbc), iVar18, uVar17, iVar2, sVar11, pDVar14);
		iVar18 = 0;
		puVar15 = (uint32_t*)(a32 + 0x68);
		psStack_318 = (short*)(a32 + 0x54);
		pbStack_314 = (uint8_t*)DStack_308.nA1MinD;
		local_30c = (uint8_t*)DStack_308.nA1MaxD;
		psStack_310 = (short*)0x6;
		do
		{
			if (*psStack_318 == 0x19)
			{
				iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				iVar18 = iVar18 + iVar2;
			}
			psStack_318 = psStack_318 + 1;
			puVar15 = puVar15 + 1;
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		psStack_318 = (short*)0x5;
		puVar15 = (uint32_t*)(a32 + 0xa4);
		psStack_310 = (short*)(a32 + 0x98);
		do
		{
			if (*psStack_310 == 0x19)
			{
				iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *puVar15, a4, (int)a5);
				iVar18 = iVar18 + iVar2;
			}
			pbVar3 = pbStack_314;
			psStack_310 = psStack_310 + 1;
			puVar15 = puVar15 + 1;
			psStack_318 = (short*)((int)psStack_318 + -1);
		} while (psStack_318 != nullptr);
		if (iVar18 != 0)
		{
			if (iVar18 < -0x59)
			{
				iVar18 = -0x5a;
			}
			pDVar7 = sub_6FAE5BD0((int)pbStack_314, iVar18, 100);
			pbVar19 = local_30c;
			pbStack_314 = pDVar7->unk0x19 + (int)(pbVar3 + -0x19);
			pDVar7 = sub_6FAE5BD0((int)local_30c, iVar18, 100);
			local_30c = pDVar7->unk0x19 + (int)(pbVar19 + -0x19);
		}
		sub_6FB13FA0((Unicode*)(a2), (int)pbStack_314, (int)local_30c, 0, 0x10a0);
		return 1;
	case 0x28:
		if (sVar11 == 0x1506)
		{
			return 0;
		}
		pUVar10 = aUStack_200;
		psStack_310 = (short*)0x100;
		do
		{
			pUVar10 = pUVar10 + 1;
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
		psStack_310 = nullptr;
		goto LAB_6fb124dd;
	case 0x29:
		iVar18 = sub_6FAAE570((int)*(short*)(a32 + 0xbc));
		if (iVar18 == 0)
		{
			return 1;
		}
		bVar1 = sub_6FAAC090();
		uVar17 = (uint32_t)bVar1;
		pDVar14 = &DStack_308;
		for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar14->nMinHP = 0;
			pDVar14 = (D2MonStatsInitStrc*)&pDVar14->nMaxHP;
		}
		iVar8 = (int)*(short*)(iVar18 + 0xaa + uVar17 * 2);
		pDVar14 = &DStack_308;
		sVar11 = 8;
		iVar18 = sub_6FAAC060();
		iVar2 = sub_6FB14AC0(0x124);
		DATATBLS_CalculateMonsterStatsByLevel(iVar2, iVar18, uVar17, iVar8, sVar11, pDVar14);
		sub_6FB13FA0((Unicode*)(a2), (int)(DStack_308.nA1MinD + (int)pbVar3),
		    (int)(DStack_308.nA1MaxD + (int)pbStack_314), (uint32_t) * (uint8_t*)(a32 + 0x1dc), 0);
		return 1;
	case 0x2a:
		if (sVar11 == 0x1506)
		{
			return 1;
		}
		if ((pbVar3 == nullptr) && (pbStack_314 == nullptr))
		{
			return 1;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		sub_6FB132C0((Unicode*)&DStack_308, (int)pbVar3, (uint32_t)(pbStack_314), 1);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		D2LANG_GetStringFromTblIndex(sVar12);
		break;
	case 0x2b:
		sub_6FB13550((Unicode*)(a2), sVar11, sVar12, (uint32_t)pbVar3, (uint32_t)pbStack_314, 10);
		return 1;
	case 0x2c:
		sub_6FB13550((Unicode*)(a2), sVar11, sVar12, (uint32_t)pbVar3, (uint32_t)pbStack_314, 100);
		return 1;
	case 0x2d:
		if ((int)a5 < 2)
		{
			return 1;
		}
		uVar9 = 0;
		iVar18 = sub_6FB14BB0(a4, (int)a5 + -1);
		sub_6FB139E0((Unicode*)(a2), 0x10d5, iVar18, uVar9);
		D2LANG_GetStringFromTblIndex(0x110d);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		break;
	case 0x2e:
		if (pbStack_314 == nullptr)
		{
			return 0;
		}
		if (sVar11 == 0x1506)
		{
			return 0;
		}
		pUVar10 = aUStack_200;
		psStack_310 = (short*)0x100;
		do
		{
			pUVar10 = pUVar10 + 1;
			psStack_310 = (short*)((int)psStack_310 + -1);
		} while (psStack_310 != nullptr);
	LAB_6fb124dd:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
		a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::sprintf(0x100, aUStack_200, a3, pUVar10);
		if (0 < (int)pbVar3)
		{
			sub_6FB20430((short*)aUStack_200, cVar13);
		}
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, aUStack_200);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcpy(aUStack_200, pUVar10);
	LAB_6fb12541:
		sub_6FB20430((short*)aUStack_200, (char)a8);
		(*pcVar16)();
		return 1;
	case 0x2f:
		if (pbVar3 == pbStack_314)
		{
			sub_6FB136E0((Unicode*)(a2), iVar18, (int)pbVar3, 0);
			return 1;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		sub_6FB0B140((Unicode*)&DStack_308, (int)pbVar3, (int)pbStack_314, 0, 0);
	LAB_6fb125be:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		break;
	case 0x30:
		iVar18 = sub_6FAAC080();
		if (iVar18 == 0)
		{
			psStack_318 = nullptr;
			psStack_310 = nullptr;
			sub_6FB0C840(pUnit, (short*)a32, a5, (int*)(&psStack_318), (int*)(&psStack_310), (uint32_t*)(&local_30c));
			sub_6FB13D30((Unicode*)(a2), 0x10a0, (int)psStack_318, (int)psStack_310, 0, 0);
			return 1;
		}
		sub_6FB13F40(pUnit, (uint32_t)(a2), a4, a32, (int)(a5));
		sub_6FB140B0(pUnit, a2, a4, a32, (int)(a5), 0);
		sub_6FB14240(pUnit, a2, a4, a32, (int)(a5), 0, 0);
		sub_6FB14470(pUnit, (Unicode*)(a2), a4, a32, (int)(a5));
		return 1;
	case 0x31:
		iVar2 = SKILLS_GetMinPhysDamage(pUnit, a4, (int)a5, 1);
		iVar2 = iVar2 >> 8;
		iVar8 = SKILLS_GetMaxPhysDamage(pUnit, a4, (int)a5, 1);
		if (iVar2 == iVar8 >> 8)
		{
			sub_6FB136E0((Unicode*)(a2), iVar18, iVar2, 1);
			return 1;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		sub_6FB0B140((Unicode*)&DStack_308, iVar2, iVar8 >> 8, 1, 0);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		break;
	case 0x32:
		psStack_310 = (short*)(int)*(short*)(local_30c + 0x3c);
		iVar2 = MISSILE_GetMinElemDamage(nullptr, pUnit, (int)psStack_310, (int)a5);
		iVar8 = MISSILE_GetMaxElemDamage(nullptr, pUnit, (int)psStack_310, (int)a5);
		if ((iVar2 >> 8 == 0) && (iVar8 >> 8 == 0))
		{
			return 1;
		}
		bVar1 = MISSILE_GetElemTypeFromMissileId((int)psStack_310);
		sub_6FB13FA0((Unicode*)(a2), iVar2 >> 8, iVar8 >> 8, (uint32_t)bVar1, (short)iVar18);
		return 1;
	case 0x33:
		memset(aUStack_200, 0, 2 * (0x100));
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::sprintf(0x100, aUStack_200, pUVar10, pbVar3);
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			Unicode::strcat(aUStack_200, pUVar10);
			Unicode::strcat((Unicode*)a2, aUStack_200);
			return 1;
		}
		sub_6FB136B0();
		return 1;
	case 0x34:
		if (pbVar3 == pbStack_314)
			goto LAB_6fb1286c;
		memset(&DStack_308, 0, 2 * (0x20));
		iVar18 = 1;
	LAB_6fb120d6:
		sub_6FB0B140((Unicode*)&DStack_308, (int)pbVar3, (int)pbStack_314, iVar18, 0);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		if (sVar11 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		if (sVar12 == 0x1506)
			goto LAB_6fb12d4a;
		goto LAB_6fb12d3f;
	case 0x35:
		uVar9 = sub_6FB19B60(pUnit, a4);
		memset(aUStack_2c8, 0, 2 * (100));
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1058));
		Unicode::sprintf(100, aUStack_2c8, pUVar10, uVar9);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_2c8, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::strcat(aUStack_2c8, pUVar10);
		D2Win_10129_DrawFramedText(aUStack_2c8, gnScreenWidth + -0x80, gnScreenHeight + -0x34, 0, 1);
		return 1;
	case 0x36:
		uVar9 = sub_6FB19B60(pUnit, a4);
		sub_6FB14B10(uVar9);
		return 1;
	case 0x37:
		uVar9 = sub_6FB19B60(pUnit, a4);
		sub_6FB14B10(uVar9);
		return 1;
	case 0x38:
		uVar9 = sub_6FB19B60(pUnit, a4);
		sub_6FB14B10(uVar9);
		return 1;
	case 0x39:
		sub_6FB13410((Unicode*)(a2), iVar18, (int)pbVar3, 1);
		return 1;
	case 0x3a:
		sub_6FB13C10((Unicode*)(a2), iVar18, (int)pbStack_31c, (int)pbVar3, (int)pbStack_314, 1);
		return 1;
	case 0x3b:
		if (sVar12 != 0x1506)
		{
			pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
			Unicode::strcat((Unicode*)a2, pUVar10);
		}
		sub_6FB13FA0((Unicode*)(a2), (int)pbVar3, (int)pbStack_314, (uint32_t) * (uint8_t*)(a32 + 0x1dc), sVar11);
		return 1;
	case 0x3c:
		if (pbStack_314 == nullptr)
		{
			pbStack_314 = (uint8_t*)0xa;
		}
		sub_6FB13790((Unicode*)(a2), sVar11, sVar12, (uint32_t)pbVar3, (int)pbStack_314, 1);
		return 1;
	case 0x3d:
		if (pbStack_314 == nullptr)
		{
			pbStack_314 = (uint8_t*)0xa;
		}
		sub_6FB13790((Unicode*)(a2), sVar11, sVar12, (uint32_t)pbVar3, (int)pbStack_314, 0);
		return 1;
	case 0x3e:
		sub_6FB13C10((Unicode*)(a2), iVar18, (int)pbStack_31c, (int)pbVar3, (int)pbStack_314, 0);
		return 1;
	case 0x3f:
		sub_6FB14600((Unicode*)(a2), sVar11, (uint32_t)(pbStack_31c), (int)pbVar3, 1, 1);
		return 1;
	case 0x40:
		sub_6FB14710((Unicode*)(a2), sVar11, (uint32_t)(pbStack_31c), (int)pbVar3, (int)pbStack_314, 1);
		return 1;
	case 0x41:
		sub_6FB14860((Unicode*)(a2), sVar11, sVar12);
		return 1;
	case 0x42:
		sub_6FB14A30((Unicode*)(a2), sVar11, (uint32_t)(pbVar3));
		return 1;
	case 0x43:
		sub_6FB14600((Unicode*)(a2), sVar11, (uint32_t)(pbStack_31c), (int)pbVar3, 1, 0);
		return 1;
	case 0x44:
		sub_6FB13A90((Unicode*)(a2), iVar18, (int)pbStack_31c, (int)pbVar3, 0);
		return 1;
	case 0x45:
		sub_6FB14910((Unicode*)(a2), sVar11, (uint32_t)(pbStack_31c), (int)pbVar3, 0, 0);
		return 1;
	case 0x46:
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::strcat((Unicode*)a2, pUVar10);
		sub_6FB136E0((Unicode*)(a2), (int)pbStack_31c, (int)pbVar3, 1);
		return 1;
	case 0x47:
		if (sVar11 == 0x1506)
		{
			return 0;
		}
		if (sVar12 == 0x1506)
		{
			return 0;
		}
		memset(aUStack_2c8, 0, 2 * (100));
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar12));
		Unicode::sprintf(100, aUStack_2c8, pUVar10, pbVar3);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat((Unicode*)a2, pUVar10);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat((Unicode*)a2, pUVar10);
		break;
	case 0x48:
		if (pbVar3 == nullptr)
		{
			return 0;
		}
		if ((int)pbStack_314 < 1)
		{
			return 0;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		iVar18 = 1;
		goto LAB_6fb12ced;
	case 0x49:
		if (pbVar3 == nullptr)
		{
			return 0;
		}
		if ((int)pbStack_314 < 1)
		{
			return 0;
		}
		memset(&DStack_308, 0, 2 * (0x20));
		iVar18 = 0;
	LAB_6fb12ced:
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbVar3, iVar18);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(4000));
		Unicode::strcat((Unicode*)a2, pUVar10);
		sub_6FB0B0F0((Unicode*)&DStack_308, (int)pbStack_314, 0);
		Unicode::strcat((Unicode*)a2, (Unicode*)&DStack_308);
		D2LANG_GetStringFromTblIndex(0xf9b);
		goto LAB_6fb12d39;
	case 0x4a:
		if (sVar11 == 0x1506)
		{
			return 0;
		}
		memset(aUStack_2c8, 0, 2 * (100));
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::sprintf(100, aUStack_2c8, pUVar10, pbVar3);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		break;
	case 0x4b:
		if (sVar11 == 0x1506)
		{
			return 0;
		}
		memset(aUStack_2c8, 0, 2 * (100));
		pbVar19 = pbStack_314;
		pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar11));
		Unicode::sprintf(100, aUStack_2c8, pUVar10, pbVar3, pbVar19);
		pcVar16 = (code*)(((uint8_t*)&Unicode::strcat));
		break;
	default:
		goto switchD_6fb10a7b_default;
	}
	(*pcVar16)();
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar16)();
	return 1;
}

//D2Client.0x6FB12F80
void __fastcall sub_6FB12F80(int a1, uint32_t* a2, uint32_t* a3)
{
	uint32_t uVar1;
	D2UnitStrc* pUnit;
	uint32_t uVar2;
	int iVar3;
	uint64_t uVar4;

	pUnit = CUNIT_GetPlayer();
	if ((a1 != 0) && (*(char*)(a1 + 0x1dc) == '\x01'))
	{
		uVar2 = STATLIST_UnitGetStatValue(pUnit, 0x149, 0);
		if (uVar2 != 0)
		{
			uVar1 = *a2;
			if ((int)uVar1 < 0x100001)
			{
				if ((int)uVar2 < 0x10001)
				{
					iVar3 = (int)(uVar1 * uVar2) / 100;
				}
				else if ((int)(uVar2 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar3 = (int)uVar4;
				}
				else
				{
					iVar3 = ((int)uVar2 / 100) * uVar1;
				}
			}
			else if ((int)(uVar1 & 0xfffffff0) < 0x640)
			{
				uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar3 = (int)uVar4;
			}
			else
			{
				iVar3 = ((int)uVar1 / 100) * uVar2;
			}
			*a2 = uVar1 + iVar3;
			uVar1 = *a3;
			if (0x100000 < (int)uVar1)
			{
				if ((int)(uVar1 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					*a3 = uVar1 + (int)uVar4;
					return;
				}
				*a3 = uVar1 + ((int)uVar1 / 100) * uVar2;
				return;
			}
			if (0x10000 < (int)uVar2)
			{
				if ((int)(uVar2 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					*a3 = uVar1 + (int)uVar4;
					return;
				}
				*a3 = uVar1 + ((int)uVar2 / 100) * uVar1;
				return;
			}
			*a3 = uVar1 + (int)(uVar1 * uVar2) / 100;
		}
	}
}

//D2Client.0x6FB13120
void __fastcall sub_6FB13120(int a1, uint32_t* a2, uint32_t* a3)
{
	uint32_t uVar1;
	D2UnitStrc* pUnit;
	uint32_t uVar2;
	int iVar3;
	uint64_t uVar4;

	pUnit = CUNIT_GetPlayer();
	if ((a1 != 0) && (*(char*)(a1 + 0x1dc) == '\x02'))
	{
		uVar2 = STATLIST_UnitGetStatValue(pUnit, 0x14a, 0);
		if (uVar2 != 0)
		{
			uVar1 = *a2;
			if ((int)uVar1 < 0x100001)
			{
				if ((int)uVar2 < 0x10001)
				{
					iVar3 = (int)(uVar1 * uVar2) / 100;
				}
				else if ((int)(uVar2 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar3 = (int)uVar4;
				}
				else
				{
					iVar3 = ((int)uVar2 / 100) * uVar1;
				}
			}
			else if ((int)(uVar1 & 0xfffffff0) < 0x640)
			{
				uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar3 = (int)uVar4;
			}
			else
			{
				iVar3 = ((int)uVar1 / 100) * uVar2;
			}
			*a2 = uVar1 + iVar3;
			uVar1 = *a3;
			if (0x100000 < (int)uVar1)
			{
				if ((int)(uVar1 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					*a3 = uVar1 + (int)uVar4;
					return;
				}
				*a3 = uVar1 + ((int)uVar1 / 100) * uVar2;
				return;
			}
			if (0x10000 < (int)uVar2)
			{
				if ((int)(uVar2 & 0xfffffff0) < 0x640)
				{
					uVar4 = D2C_alldiv((uint32_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar1 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					*a3 = uVar1 + (int)uVar4;
					return;
				}
				*a3 = uVar1 + ((int)uVar2 / 100) * uVar1;
				return;
			}
			*a3 = uVar1 + (int)(uVar1 * uVar2) / 100;
		}
	}
}

//D2Client.0x6FB132C0
uint32_t __fastcall sub_6FB132C0(Unicode* pUnicode, int a2, uint32_t a3, int a4)
{
	char* pcVar1;
	CHAR local_20[32];

	if ((a4 == 0) || (a2 < 0))
	{
		pcVar1 = "%d.%d";
	}
	else
	{
		pcVar1 = "+%d.%d";
	}
	wsprintfA(local_20, pcVar1, a2, a3);
	Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
	return 1;
}

//D2Client.0x6FB13320
int __fastcall sub_6FB13320(Unicode* pUnicode, int a2, int a3, int a4)
{
	LPCSTR pCVar1;
	CHAR local_20[32];

	if (a2 == 0)
	{
		if (a3 == 0)
		{
			return a3;
		}
	}
	else if (a3 == 0)
	{
		if ((a4 == 0) || (a2 < 0))
		{
			pCVar1 = "%d";
		}
		else
		{
			pCVar1 = "+%d";
		}
		wsprintfA(local_20, pCVar1, a2);
		goto LAB_6fb133a4;
	}
	if ((a4 == 0) || (a2 < 0))
	{
		wsprintfA(local_20, "%d.%d", a2, a3);
	}
	else
	{
		wsprintfA(local_20, "+%d.%d", a2, a3);
	}
LAB_6fb133a4:
	Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
	return 1;
}

//D2Client.0x6FB133C0
void __fastcall sub_6FB133C0(Unicode* pUnicode, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, int a6)
{
	char* pcVar1;
	CHAR local_20[32];

	if (a6 == 0)
	{
		pcVar1 = "%d.%d-%d.%d";
	}
	else
	{
		pcVar1 = "+%d.%d-%d.%d";
	}
	wsprintfA(local_20, pcVar1, a2, a3, a4, a5);
	Unicode::toUnicode((Unicode*)pUnicode, local_20, 0x20);
}

//D2Client.0x6FB13410
uint32_t __fastcall sub_6FB13410(Unicode* pUnicode, int a2, int a3, int a4)
{
	int iVar1;
	Unicode* pUVar2;
	short index;
	int iVar3;
	LPCSTR pCVar4;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	iVar1 = a3 / 0x19;
	iVar3 = ((a3 % 0x19) * 10) / 0x19;
	if (iVar1 == 0)
	{
		if (iVar3 == 0)
		{
			return 0;
		}
	}
	else if (iVar3 == 0)
	{
		if ((a4 == 0) || (iVar1 < 0))
		{
			pCVar4 = "%d";
		}
		else
		{
			pCVar4 = "+%d";
		}
		wsprintfA(aCStack_60, pCVar4, iVar1);
		goto LAB_6fb134d9;
	}
	if ((a4 == 0) || (iVar1 < 0))
	{
		wsprintfA(aCStack_60, "%d.%d", iVar1, iVar3);
	}
	else
	{
		wsprintfA(aCStack_60, "+%d.%d", iVar1, iVar3);
	}
LAB_6fb134d9:
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar2);
	Unicode::strcat(pUnicode, local_40);
	if ((iVar1 != 1) || (index = 0x10ab, iVar3 != 0))
	{
		index = 0x10ac;
	}
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	Unicode::strcat(pUnicode, pUVar2);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar2);
	return 1;
}

//D2Client.0x6FB13550
uint32_t __fastcall sub_6FB13550(Unicode* pUnicode, short a2, short a3, uint32_t a4, uint32_t a5, int a6)
{
	uint32_t uVar1;
	int iVar2;
	Unicode* pUVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	iVar5 = (int)(a4 + ((int)a4 >> 0x1f & 0xffU)) >> 8;
	uVar1 = a4 & 0x800000ff;
	if ((int)uVar1 < 0)
	{
		uVar1 = (uVar1 - 1 | 0xffffff00) + 1;
	}
	iVar4 = (int)(uVar1 * a6 + ((int)(uVar1 * a6) >> 0x1f & 0xffU)) >> 8;
	iVar6 = (int)(a5 + ((int)a5 >> 0x1f & 0xffU)) >> 8;
	uVar1 = a5 & 0x800000ff;
	if ((int)uVar1 < 0)
	{
		uVar1 = (uVar1 - 1 | 0xffffff00) + 1;
	}
	iVar2 = (int)(uVar1 * a6 + ((int)(uVar1 * a6) >> 0x1f & 0xffU)) >> 8;
	if ((iVar5 == 0) && (iVar6 == 0))
	{
		if ((iVar4 == 0) && (iVar2 == 0))
		{
			return 0;
		}
	}
	else if ((iVar4 == 0) && (iVar2 == 0))
	{
		sub_6FB0B140((Unicode*)local_40, iVar5, iVar6, 0, 0);
		goto LAB_6fb13641;
	}
	wsprintfA(aCStack_60, "%d.%d-%d.%d", iVar5, iVar4, iVar6, iVar2);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
LAB_6fb13641:
	if (a2 != 0x1506)
	{
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcat(pUnicode, pUVar3);
	}
	Unicode::strcat(pUnicode, local_40);
	if (a3 != 0x1506)
	{
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(a3));
		Unicode::strcat(pUnicode, pUVar3);
	}
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar3);
	return 1;
}

//D2Client.0x6FB136B0
// TODO: decompilation needs review (in_reg)
uint32_t __fastcall sub_6FB136B0()
{
	Unicode* pUVar1;
	Unicode* in_ECX;
	short in_DX;

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(in_DX));
	Unicode::strcat(in_ECX, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(in_ECX, pUVar1);
	return 1;
}

//D2Client.0x6FB136E0
int __fastcall sub_6FB136E0(Unicode* pUnicode, int a2, int a3, int a4)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a3 == 0)
	{
		return a3;
	}
	if ((a4 == 0) || (a3 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a3);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB13790
uint32_t __fastcall sub_6FB13790(Unicode* pUnicode, short a2, short a3, uint32_t a4, int a5, int a6)
{
	uint32_t uVar1;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	LPCSTR pCVar5;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a4 == 0)
	{
		return 0;
	}
	uVar1 = a4 & 0x800000ff;
	if ((int)uVar1 < 0)
	{
		uVar1 = (uVar1 - 1 | 0xffffff00) + 1;
	}
	iVar3 = (int)(uVar1 * a5 + ((int)(uVar1 * a5) >> 0x1f & 0xffU)) >> 8;
	iVar4 = (int)(a4 + ((int)a4 >> 0x1f & 0xffU)) >> 8;
	if (iVar4 == 0)
	{
		if (iVar3 == 0)
			goto LAB_6fb13884;
	LAB_6fb13807:
		if ((a6 == 0) || (iVar4 < 0))
		{
			wsprintfA(aCStack_60, "%d.%d", iVar4, iVar3);
		}
		else
		{
			wsprintfA(aCStack_60, "+%d.%d", iVar4, iVar3);
		}
	}
	else
	{
		if (iVar3 != 0)
			goto LAB_6fb13807;
		if ((a6 == 0) || (iVar4 < 0))
		{
			pCVar5 = "%d";
		}
		else
		{
			pCVar5 = "+%d";
		}
		wsprintfA(aCStack_60, pCVar5, iVar4);
	}
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
LAB_6fb13884:
	if (a2 != 0x1506)
	{
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcat(pUnicode, pUVar2);
	}
	Unicode::strcat(pUnicode, local_40);
	if (a3 != 0x1506)
	{
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(a3));
		Unicode::strcat(pUnicode, pUVar2);
	}
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar2);
	return 1;
}

//D2Client.0x6FB138E0
int __fastcall sub_6FB138E0(Unicode* pUnicode, int a2, int a3, int a4, int a5)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a3 == 0)
	{
		if (a4 < 1)
		{
			return a3;
		}
	}
	else if (a4 == 0)
	{
		if ((a5 == 0) || (a3 < 0))
		{
			pCVar3 = "%d";
		}
		else
		{
			pCVar3 = "+%d";
		}
		wsprintfA(aCStack_60, pCVar3, a3);
		goto LAB_6fb13987;
	}
	if ((a5 == 0) || (a3 < 0))
	{
		wsprintfA(aCStack_60, "%d.%d", a3, a4);
	}
	else
	{
		wsprintfA(aCStack_60, "+%d.%d", a3, a4);
	}
LAB_6fb13987:
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB139E0
int __fastcall sub_6FB139E0(Unicode* pUnicode, int a2, int a3, int a4)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a3 == 0)
	{
		return a3;
	}
	if ((a4 == 0) || (a3 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a3);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB13A90
int __fastcall sub_6FB13A90(Unicode* pUnicode, uint32_t a2, int a3, int a4, int a5)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a4 == 0)
	{
		return a4;
	}
	if ((a5 == 0) || (a4 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a4);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB13B50
int __fastcall sub_6FB13B50(Unicode* pUnicode, uint32_t a2, int a3, int a4, int a5)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a4 == 0)
	{
		return a4;
	}
	if ((a5 == 0) || (a4 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a4);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB13C10
uint32_t __fastcall sub_6FB13C10(Unicode* pUnicode, uint32_t a2, int a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	int iVar2;
	code* pcVar3;
	CHAR aCStack_a0[32];
	Unicode local_80[32];
	Unicode local_40[32];

	iVar2 = 0x20;
	if (a4 == a5)
	{
		pUVar1 = local_80;
		do
		{
			pUVar1 = pUVar1 + 1;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		if (a4 == 0)
		{
			return 0;
		}
		wsprintfA(aCStack_a0, "%d", a4);
		Unicode::toUnicode(local_80, aCStack_a0, 0x20);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
		pcVar3 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(pUnicode, pUVar1);
		Unicode::strcat(pUnicode, local_80);
		D2LANG_GetStringFromTblIndex((short)a3);
	}
	else
	{
		pUVar1 = local_40;
		do
		{
			pUVar1 = pUVar1 + 1;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		sub_6FB0B140((Unicode*)local_40, a4, a5, a6, 0);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
		pcVar3 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
		Unicode::strcat(pUnicode, pUVar1);
	}
	(*pcVar3)();
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar3)();
	return 1;
}

//D2Client.0x6FB13D30
uint32_t __fastcall sub_6FB13D30(Unicode* pUnicode, int a2, int a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	int iVar2;
	code* pcVar3;
	LPCSTR pCVar4;
	CHAR aCStack_a0[32];
	Unicode local_80[32];
	Unicode local_40[32];

	iVar2 = 0x20;
	if (a3 == a4)
	{
		pUVar1 = local_80;
		do
		{
			pUVar1 = pUVar1 + 1;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		if (a3 == 0)
		{
			return 0;
		}
		if ((a5 == 0) || (a3 < 0))
		{
			pCVar4 = "%d";
		}
		else
		{
			pCVar4 = "+%d";
		}
		wsprintfA(aCStack_a0, pCVar4, a3);
		Unicode::toUnicode(local_80, aCStack_a0, 0x20);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
		pcVar3 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(pUnicode, pUVar1);
	}
	else
	{
		pUVar1 = local_40;
		do
		{
			pUVar1 = pUVar1 + 1;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		sub_6FB0B140((Unicode*)local_40, a3, a4, a5, 0);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a2));
		pcVar3 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(pUnicode, pUVar1);
		if (a6 != 0)
		{
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			Unicode::strcat(pUnicode, pUVar1);
		}
	}
	(*pcVar3)();
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar3)();
	return 1;
}

//D2Client.0x6FB13E70
uint32_t __fastcall sub_6FB13E70(Unicode* pUnicode, uint32_t a22)
{
	Unicode* a2;
	Unicode* a2_00;
	Unicode* a2_01;
	Unicode* a2_02;
	Unicode* pUVar1;
	int iVar2;
	Unicode aUStack_40[16];
	CHAR aCStack_20[32];

	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5300));
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5304));
	a2_01 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5305));
	a2_02 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	wsprintfA(aCStack_20, "%d", a22);
	Unicode::toUnicode(aUStack_40, aCStack_20, 0x20);
	Unicode::strcat(pUnicode, a2_00);
	Unicode::strcat(pUnicode, aUStack_40);
	Unicode::strcat(pUnicode, a2_02);
	Unicode::strcat(pUnicode, a2);
	Unicode::strcat(pUnicode, a2_01);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB13F40
uint32_t __fastcall sub_6FB13F40(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, int a5)
{
	int iVar1;
	uint32_t uVar2;

	iVar1 = SKILLS_GetElementalLength(pUnit, a3, a5, 0);
	if (iVar1 != 0)
	{
		if (*(char*)(a4 + 0x1dc) == '\x04')
		{
			uVar2 = sub_6FB13410((Unicode*)(a2), 0x10a9, iVar1, 0);
			return uVar2;
		}
		if (*(char*)(a4 + 0x1dc) == '\x05')
		{
			uVar2 = sub_6FB13410((Unicode*)(a2), 0x10aa, iVar1, 0);
			return uVar2;
		}
	}
	return 0;
}

//D2Client.0x6FB13FA0
uint32_t __fastcall sub_6FB13FA0(Unicode* pUnicode, int a2, int a3, uint32_t a4, short a5)
{
	Unicode* pUVar1;
	int iVar2;
	bool bVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a5 == 0)
	{
		switch (a4)
		{
		case 1:
			a5 = 0x10a1;
			break;
		case 2:
			a5 = 0x10a3;
			break;
		case 3:
			a5 = 0x10c3;
			break;
		case 4:
			a5 = 0x10a2;
			break;
		case 5:
			a5 = 0x10a4;
			break;
		case 6:
			a5 = 0xdc4;
			break;
		default:
			return 0;
		}
	}
	if (a2 == 0)
	{
		bVar3 = a3 == 0;
	}
	else
	{
		bVar3 = a2 == a3;
	}
	if (bVar3)
	{
		wsprintfA(aCStack_60, "%d", a2);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
	}
	else
	{
		sub_6FB0B140((Unicode*)local_40, a2, a3, 0, 0);
	}
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a5));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB140B0
uint32_t __fastcall sub_6FB140B0(D2UnitStrc* pUnit, char* a2, int a3, int a4, int a5, uint32_t a6)
{
	uint8_t uVar1;
	int iVar2;
	int iVar3;
	Unicode* pUVar4;
	int iVar5;
	bool bVar6;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	iVar2 = SKILLS_GetMinElemDamage(pUnit, a3, a5, 1);
	iVar3 = SKILLS_GetMaxElemDamage(pUnit, a3, a5, 1);
	if ((iVar2 == 0) && (iVar3 == 0))
	{
	switchD_6fb14141_default:
		return 0;
	}
	iVar2 = iVar2 >> 8;
	iVar3 = iVar3 >> 8;
	(*(uint16_t*)((uint8_t*)&a5 + 0)) = (short)a6;
	uVar1 = *(uint8_t*)(a4 + 0x1dc);
	if ((short)a6 == 0)
	{
		switch (uVar1)
		{
		case 1:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0x10a1;
			break;
		case 2:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0x10a3;
			break;
		case 3:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0x10c3;
			break;
		case 4:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0x10a2;
			break;
		case 5:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0x10a4;
			break;
		case 6:
			(*(uint16_t*)((uint8_t*)&a5 + 0)) = 0xdc4;
			break;
		default:
			goto switchD_6fb14141_default;
		}
	}
	if (iVar2 == 0)
	{
		bVar6 = iVar3 == 0;
	}
	else
	{
		bVar6 = iVar2 == iVar3;
	}
	if (bVar6)
	{
		wsprintfA(aCStack_60, "%d", iVar2);
		Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
	}
	else
	{
		sub_6FB0B140((Unicode*)aUStack_40, iVar2, iVar3, 0, 0);
	}
	pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a5));
	Unicode::strcat((Unicode*)a2, pUVar4);
	Unicode::strcat((Unicode*)a2, aUStack_40);
	pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat((Unicode*)a2, pUVar4);
	return 1;
}

//D2Client.0x6FB14240
// TODO: decompilation needs review (extraout)
uint64_t __fastcall sub_6FB14240(D2UnitStrc* pUnit, char* a2, int a3, uint32_t a4, int a5, uint32_t a6, int a7)
{
	Unicode* pUVar1;
	uint32_t extraout_EDX;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	uint64_t uVar6;
	uint64_t uVar7;
	LPCSTR pCVar8;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	iVar2 = SKILLS_GetMinPhysDamage(pUnit, a3, a5, 0);
	uVar3 = iVar2 >> 8;
	iVar2 = SKILLS_GetMaxPhysDamage(pUnit, a3, a5, 0);
	uVar4 = iVar2 >> 8;
	if ((int)uVar3 < 0x100001)
	{
		if ((int)a6 < 0x10001)
		{
			iVar2 = (int)(uVar3 * a6) / 100;
		}
		else if ((int)(a6 & 0xfffffff0) < 0x640)
		{
			uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)a6),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)a6) >> 0x20),
			    100, 0);
			iVar2 = (int)uVar6;
		}
		else
		{
			iVar2 = ((int)a6 / 100) * uVar3;
		}
	}
	else if ((int)(uVar3 & 0xfffffff0) < 0x640)
	{
		uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)a6),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)a6) >> 0x20), 100,
		    0);
		iVar2 = (int)uVar6;
	}
	else
	{
		iVar2 = ((int)uVar3 / 100) * a6;
	}
	iVar2 = uVar3 + iVar2 + a7;
	if ((int)uVar4 < 0x100001)
	{
		if ((int)a6 < 0x10001)
		{
			uVar7 = CONCAT44(-((int)(uVar4 * a6) >> 0x1f), (int)(uVar4 * a6) / 100);
		}
		else if ((int)(a6 & 0xfffffff0) < 0x640)
		{
			uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar4 * (int64_t)(int)a6),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar4 * (int64_t)(int)a6) >> 0x20),
			    100, 0);
		}
		else
		{
			uVar7 = CONCAT44((int)((uint64_t)((int64_t)(int)a6 * 0x51eb851f) >> 0x20),
			    ((int)a6 / 100) * uVar4);
		}
	}
	else if ((int)(uVar4 & 0xfffffff0) < 0x640)
	{
		uVar7 = D2C_alldiv((uint32_t)((int64_t)(int)uVar4 * (int64_t)(int)a6),
		    (uint32_t)((uint64_t)((int64_t)(int)uVar4 * (int64_t)(int)a6) >> 0x20), 100,
		    0);
	}
	else
	{
		uVar7 = CONCAT44((int)((uint64_t)((int64_t)(int)uVar4 * 0x51eb851f) >> 0x20),
		    ((int)uVar4 / 100) * a6);
	}
	iVar5 = uVar4 + (int)uVar7 + a7;
	if (iVar2 == 0)
	{
		if (iVar5 == 0)
		{
			return uVar7 & 0xffffffff00000000;
		}
	}
	else if (iVar2 == iVar5)
	{
		if (iVar2 < 0)
		{
			pCVar8 = "%d";
		}
		else
		{
			pCVar8 = "+%d";
		}
		wsprintfA(aCStack_60, pCVar8, iVar2);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
		goto LAB_6fb14425;
	}
	sub_6FB0B140((Unicode*)local_40, iVar2, iVar5, 0, 0);
LAB_6fb14425:
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10a0));
	Unicode::strcat((Unicode*)a2, pUVar1);
	Unicode::strcat((Unicode*)a2, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat((Unicode*)a2, pUVar1);
	return CONCAT44(extraout_EDX, 1);
}

//D2Client.0x6FB14470
uint32_t __fastcall sub_6FB14470(D2UnitStrc* pUnit, Unicode* pUnicode, int a3, uint32_t a4, int a5)
{
	int iVar1;
	Unicode* pUVar2;
	int iVar3;
	LPCSTR pCVar4;
	CHAR aCStack_60[32];
	Unicode aUStack_40[32];

	iVar1 = SKILLS_GetToHitFactor(pUnit, a3, a5);
	if (iVar1 == 0)
	{
		return 0;
	}
	if (iVar1 < 0)
	{
		pCVar4 = "%d";
	}
	else
	{
		pCVar4 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar4, iVar1);
	Unicode::toUnicode(aUStack_40, aCStack_60, 0x20);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10a6));
	Unicode::strcat(pUnicode, pUVar2);
	Unicode::strcat(pUnicode, aUStack_40);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10b3));
	Unicode::strcat(pUnicode, pUVar2);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar2);
	return 1;
}

//D2Client.0x6FB14530
int __fastcall sub_6FB14530(Unicode* pUnicode, int a2, int a3, uint32_t a4)
{
	Unicode* pUVar1;
	int iVar2;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a2 == 0)
	{
		if (a3 == 0)
		{
			return a3;
		}
	}
	else if (a2 == a3)
	{
		wsprintfA(aCStack_60, "%d", a2);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
		goto LAB_6fb145a2;
	}
	sub_6FB0B140((Unicode*)local_40, a2, a3, 0, 0);
LAB_6fb145a2:
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10e2));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a4));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10be));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB14600
uint32_t __fastcall sub_6FB14600(Unicode* pUnicode, short a2, uint32_t a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a4 == 0)
	{
		return 0;
	}
	if ((a5 == 0) || (a4 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a4);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	if (a2 != 0x1506)
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(pUnicode, pUVar1);
	}
	Unicode::strcat(pUnicode, local_40);
	if (a6 != 0)
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa1));
		Unicode::strcat(pUnicode, pUVar1);
	}
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB14710
uint32_t __fastcall sub_6FB14710(Unicode* pUnicode, short a2, uint32_t a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (((a2 != 0x1506) && (a4 != 0)) && (0 < a5))
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(pUnicode, pUVar1);
		if ((a6 == 0) || (a4 < 0))
		{
			pCVar3 = "%d";
		}
		else
		{
			pCVar3 = "+%d";
		}
		wsprintfA(aCStack_60, pCVar3, a4);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
		Unicode::strcat(pUnicode, local_40);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(4000));
		Unicode::strcat(pUnicode, pUVar1);
		wsprintfA(aCStack_60, "%d", a5);
		Unicode::toUnicode(local_40, aCStack_60, 0x20);
		Unicode::strcat(pUnicode, local_40);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(pUnicode, pUVar1);
		return 1;
	}
	return 0;
}

//D2Client.0x6FB14860
uint32_t __fastcall sub_6FB14860(Unicode* pUnicode, short a2, short a3)
{
	Unicode* pUVar1;
	int iVar2;
	Unicode local_40[32];

	if ((a2 != 0x1506) && (a3 != 0x1506))
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a3));
		Unicode::strcat(pUnicode, pUVar1);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(pUnicode, pUVar1);
		return 1;
	}
	return 0;
}

//D2Client.0x6FB14910
uint32_t __fastcall sub_6FB14910(Unicode* pUnicode, short a2, uint32_t a3, int a4, int a5, int a6)
{
	Unicode* pUVar1;
	int iVar2;
	LPCSTR pCVar3;
	CHAR aCStack_60[32];
	Unicode local_40[32];

	if (a2 == 0x1506)
	{
		return 0;
	}
	if (a4 == 0)
	{
		return 0;
	}
	if ((a5 == 0) || (a4 < 0))
	{
		pCVar3 = "%d";
	}
	else
	{
		pCVar3 = "+%d";
	}
	wsprintfA(aCStack_60, pCVar3, a4);
	Unicode::toUnicode(local_40, aCStack_60, 0x20);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a3));
	Unicode::strcat(pUnicode, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_40);
	if (a6 != 0)
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfa1));
		Unicode::strcat(pUnicode, pUVar1);
	}
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB14A30
uint32_t __fastcall sub_6FB14A30(Unicode* pUnicode, short a2, uint32_t a3)
{
	Unicode* pUVar1;
	int iVar2;
	Unicode local_200[256];

	if (a2 == 0x1506)
	{
		return 0;
	}
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
	Unicode::sprintf(0x100, local_200, pUVar1, a3);
	Unicode::strcat(pUnicode, local_200);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(pUnicode, pUVar1);
	return 1;
}

//D2Client.0x6FB14AC0
int __fastcall sub_6FB14AC0(int a1)
{
	if ((a1 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= a1))
	{
		a1 = -1;
	}
	return a1;
}

//D2Client.0x6FB14AE0
int __fastcall sub_6FB14AE0(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a1 * 0x23c;
	}
	return 0;
}

//D2Client.0x6FB14B10
void __fastcall sub_6FB14B10(uint32_t a1)
{
	Unicode* pUVar1;
	short in_DX;
	int iVar2;
	Unicode local_c8[100];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1058));
	Unicode::sprintf(100, local_c8, pUVar1, a1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(local_c8, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(in_DX));
	Unicode::strcat(local_c8, pUVar1);
	D2Win_10129_DrawFramedText(local_c8, gnScreenWidth + -0x80, gnScreenHeight + -0x34, 0, 1);
}

//D2Client.0x6FB14BB0
int __fastcall sub_6FB14BB0(int a1, int a2)
{
	int iVar1;

	if (((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a1 * 0x23c, iVar1 != 0))
	{
		if (a2 < 1)
		{
			return 0;
		}
		return *(int*)(iVar1 + 0x14c) * (a2 + -1) + *(int*)(iVar1 + 0x148);
	}
	return 0;
}

//D2Client.0x6FB14C00
// TODO: decompilation needs review (in_stack, stack0x)
void __cdecl sub_6FB14C00(uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
	uint8_t stack0x00000018[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000001c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000020[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000040[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000080[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000880[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	bool bVar1;
	bool bVar2;
	short sVar3;
	D2SkillStrc* pDVar4;
	int iVar5;
	Unicode* pUVar6;
	int iVar7;
	int iVar8;
	D2UnitStrc* pUnit;
	int iVar9;
	int nSkillId;
	int iVar10;
	code* pcVar11;
	int iStack00000014;
	int in_stack_00000018;
	int in_stack_00001084;
	uint32_t in_stack_00001088;
	int in_stack_0000108c;
	int in_stack_00001090;

	if (pUnit == nullptr)
	{
		return;
	}
	if (nSkillId < 0)
	{
		return;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= nSkillId)
	{
		return;
	}
	iVar9 = nSkillId * 0x23c;
	iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar9;
	if (iVar10 == 0)
	{
		return;
	}
	pDVar4 = SKILLS_GetSkillById(pUnit, nSkillId, 0xffffffff);
	if ((pDVar4 == nullptr) || (iVar5 = SKILLS_GetSkillLevel(pUnit, pDVar4, 1), iVar5 == 0))
	{
	LAB_6fb14c89:
		bVar2 = false;
	}
	else
	{
		iVar5 = SKILLS_GetSkillLevel(pUnit, pDVar4, 0);
		bVar2 = true;
		if (iVar5 != 0)
			goto LAB_6fb14c89;
	}
	pUVar6 = (Unicode*)stack0x00000080;
	iVar5 = 0x400;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar5 = iVar5 + -1;
	} while (iVar5 != 0);
	pUVar6 = (Unicode*)stack0x00000040;
	iVar5 = 0x20;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar5 = iVar5 + -1;
	} while (iVar5 != 0);
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109c));
	Unicode::strcpy((Unicode*)stack0x00000080, pUVar6);
	pDVar4 = SKILLS_GetSkillById(pUnit, nSkillId, 0xffffffff);
	if (pDVar4 != nullptr)
	{
		if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= nSkillId) ||
		    (iVar5 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 + iVar9),
		        iVar5 < 1))
		{
			iVar5 = 0x14;
		}
		iVar7 = SKILLS_GetSkillLevel(pUnit, pDVar4, 0);
		bVar1 = true;
		if (iVar5 <= iVar7)
			goto LAB_6fb14d38;
	}
	bVar1 = false;
LAB_6fb14d38:
	iVar5 = in_stack_00001084 + 1;
	iStack00000014 = 0;
	iVar7 = 0x10;
	do
	{
		iVar8 = sub_6FB10970(pUnit, (char*)(stack0x00000080), iVar10, nSkillId, (int*)(iVar5), in_stack_00001088, iVar7, 0);
		if (iVar8 != 0)
		{
			iStack00000014 = 1;
		}
		iVar7 = iVar7 + -1;
	} while (9 < iVar7);
	if (iStack00000014 != 0)
	{
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	}
	if (!bVar1)
	{
		iVar7 = 0;
		bVar1 = false;
		do
		{
			iVar8 = sub_6FB10970(pUnit, (char*)(stack0x00000080), iVar10, nSkillId, (int*)(iVar5), in_stack_00001088, iVar7, 0);
			if (iVar8 != 0)
			{
				bVar1 = true;
			}
			iVar7 = iVar7 + 1;
		} while (iVar7 < 6);
		if (bVar1)
		{
			if (in_stack_00001084 == 0)
			{
				pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x10ad));
				Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
				pcVar11 = (code*)(((uint8_t*)&Unicode::strcat));
			}
			else
			{
				pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109d));
				pcVar11 = (code*)(((uint8_t*)&Unicode::strcat));
				Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
			}
			D2LANG_GetStringFromTblIndex(0xf9e);
			(*pcVar11)();
			D2LANG_GetStringFromTblIndex(0xf9e);
			(*pcVar11)();
		}
	}
	if (0 < in_stack_00001084)
	{
		iVar7 = 0;
		bVar1 = false;
		do
		{
			iVar8 = sub_6FB10970(pUnit, (char*)(stack0x00000080), iVar10, nSkillId, (int*)(in_stack_00001084),
			    in_stack_00001088, iVar7, 0);
			if (iVar8 != 0)
			{
				bVar1 = true;
			}
			iVar7 = iVar7 + 1;
		} while (iVar7 < 6);
		if (bVar1)
		{
			wsprintfA((LPSTR)(stack0x00000020), "%d");
			Unicode::toUnicode((Unicode*)stack0x00000040, (const char*)(stack0x00000020), 0x20);
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109e));
			Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
			Unicode::strcat((Unicode*)stack0x00000080, (Unicode*)stack0x00000040);
			if (bVar2)
			{
				pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1112));
				Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
			}
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
		}
	}
	bVar1 = false;
	iVar7 = 6;
	do
	{
		iVar8 = sub_6FB10970(pUnit, (char*)(stack0x00000080), iVar10, nSkillId, (int*)(iVar5), in_stack_00001088, iVar7, 0);
		if (iVar8 != 0)
		{
			bVar1 = true;
		}
		iVar7 = iVar7 + 1;
	} while (iVar7 < 10);
	if (bVar1)
	{
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	}
	iVar10 = *(int*)((uint8_t*)&sgptDataTables);
	if ((((nSkillId < *(int*)(iVar10 + 0xba0)) &&
	         (iVar5 = *(int*)(iVar10 + 0xb98) + iVar9, iVar5 != 0)) &&
	        (iVar5 = (int)*(short*)(iVar5 + 0x194), -1 < iVar5)) &&
	    ((iVar5 < *(int*)(iVar10 + 0xb94) &&
	        (iVar10 = iVar5 * 0x120 + *(int*)(iVar10 + 0xb8c), iVar10 != 0))))
	{
		sVar3 = *(short*)(iVar10 + 0xc);
	}
	else
	{
		sVar3 = 0x1506;
	}
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar3));
	Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	pUVar6 = (Unicode*)stack0x00000880;
	iVar10 = 0x400;
	do
	{
		pUVar6 = pUVar6 + 1;
		iVar10 = iVar10 + -1;
	} while (iVar10 != 0);
	iVar10 = *(int*)((uint8_t*)&sgptDataTables);
	if (((nSkillId < *(int*)(iVar10 + 0xba0)) &&
	        (iVar9 = *(int*)(iVar10 + 0xb98) + iVar9, iVar9 != 0)) &&
	    ((iVar9 = (int)*(short*)(iVar9 + 0x194), -1 < iVar9 &&
	                                                 ((iVar9 < *(int*)(iVar10 + 0xb94) &&
	                                                     (iVar9 = iVar9 * 0x120 + *(int*)(iVar10 + 0xb8c), iVar9 != 0))))))
	{
		sVar3 = *(short*)(iVar9 + 8);
	}
	else
	{
		sVar3 = 0x1506;
	}
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar3));
	Unicode::strcpy((Unicode*)stack0x00000880, pUVar6);
	sub_6FB20430((short*)stack0x00000880, '\x02');
	Unicode::strcat((Unicode*)stack0x00000080, (Unicode*)stack0x00000880);
	if (bVar2)
	{
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1113));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	}
	if (dword_6FBB9430 == 0)
	{
		iVar5 = 0;
		iVar9 = *(int*)((uint8_t*)&sgptDataTables);
		iVar10 = *(int*)(iVar9 + 0xba0);
		if (0 < iVar10)
		{
			iVar7 = 0;
			do
			{
				if (((((-1 < iVar7) && (iVar5 < iVar10)) &&
				         (iVar9 = *(int*)(iVar9 + 0xb98) + iVar7, iVar9 != 0)) &&
				        ((*(char*)(iVar9 + 0xc) == (char)pUnit->dwClassId &&
				            (pDVar4 = SKILLS_GetSkillById(pUnit, iVar5, 0xffffffff), pDVar4 != nullptr)))) &&
				    (iVar9 = SKILLS_GetSkillLevel(pUnit, pDVar4, 0), iVar9 != 0))
				{
					dword_6FBB9430 = 1;
					goto LAB_6fb151c4;
				}
				iVar5 = iVar5 + 1;
				iVar7 = iVar7 + 0x23c;
				iVar9 = *(int*)((uint8_t*)&sgptDataTables);
				iVar10 = *(int*)(iVar9 + 0xba0);
			} while (iVar5 < iVar10);
		}
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1114));
		Unicode::strcat((Unicode*)stack0x00000080, pUVar6);
	}
LAB_6fb151c4:
	D2Win_10131_GetTextDimensions((Unicode*)stack0x00000080, (int*)stack0x0000001c, (int*)(stack0x00000018));
	D2Win_10129_DrawFramedText((Unicode*)stack0x00000080, in_stack_0000108c + -0x18,
	    in_stack_00000018 + 3 + in_stack_00001090, 0, 0);
}

//D2Client.0x6FB15220
void __fastcall sub_6FB15220(D2UnitStrc* pUnit, int a2, int a3, uint32_t a4, int a5, int a6)
{
	bool bVar1;
	bool bVar2;
	short sVar3;
	int iVar4;
	D2SkillStrc* pDVar5;
	D2SkillStrc* pSkill;
	int iVar6;
	Unicode* pUVar7;
	int iVar8;
	int iVar9;
	code* pcVar10;
	int iStack_aa8;
	int iStack_aa4;
	CHAR aCStack_aa0[32];
	Unicode aUStack_a80[32];
	Unicode aUStack_a40[32];
	Unicode aUStack_a00[1024];
	Unicode aUStack_200[256];

	bVar1 = false;
	if (pUnit == nullptr)
	{
		return;
	}
	if (a2 < 0)
	{
		return;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2)
	{
		return;
	}
	iVar9 = a2 * 0x23c;
	iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar9;
	if (iVar4 == 0)
	{
		return;
	}
	pDVar5 = SKILLS_GetSkillById(pUnit, a2, 0xffffffff);
	pSkill = SKILLS_GetSkillById(pUnit, a2, 0xffffffff);
	if ((pSkill == nullptr) || (iVar6 = SKILLS_GetSkillLevel(pUnit, pSkill, 1), iVar6 == 0))
	{
	LAB_6fb152bc:
		bVar2 = false;
	}
	else
	{
		iVar6 = SKILLS_GetSkillLevel(pUnit, pSkill, 0);
		bVar2 = true;
		if (iVar6 != 0)
			goto LAB_6fb152bc;
	}
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109c));
	Unicode::strcpy(aUStack_a00, pUVar7);
	iVar6 = 0x10;
	do
	{
		iVar8 = sub_6FB10970(pUnit, (char*)(aUStack_a00), iVar4, a2, (int*)(a3 + 1), a4, iVar6, 1);
		if (iVar8 != 0)
		{
			bVar1 = true;
		}
		iVar6 = iVar6 + -1;
	} while (9 < iVar6);
	if (bVar1)
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
	}
	bVar1 = false;
	iVar6 = 0;
	do
	{
		iVar8 = a3;
		if (a3 < 1)
		{
			iVar8 = 1;
		}
		iVar8 = sub_6FB10970(pUnit, (char*)(aUStack_a00), iVar4, a2, (int*)(iVar8), a4, iVar6, 1);
		if (iVar8 != 0)
		{
			bVar1 = true;
		}
		iVar6 = iVar6 + 1;
	} while (iVar6 < 6);
	if (bVar1)
	{
		if (a3 < 1)
		{
			D2LANG_GetStringFromTblIndex(0x10ad);
			pcVar10 = (code*)(((uint8_t*)&Unicode::strcat));
		}
		else
		{
			wsprintfA(aCStack_aa0, "%d", a3);
			Unicode::toUnicode(aUStack_a80, aCStack_aa0, 0x20);
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109e));
			pcVar10 = (code*)(((uint8_t*)&Unicode::strcat));
			Unicode::strcat(aUStack_a00, pUVar7);
		}
		(*pcVar10)();
		if (bVar2)
		{
			D2LANG_GetStringFromTblIndex(0x1112);
			(*pcVar10)();
		}
		D2LANG_GetStringFromTblIndex(0xf9e);
		(*pcVar10)();
		D2LANG_GetStringFromTblIndex(0xf9e);
		(*pcVar10)();
	}
	bVar1 = false;
	iVar6 = 6;
	do
	{
		iVar8 = a3;
		if (a3 < 1)
		{
			iVar8 = 1;
		}
		iVar8 = sub_6FB10970(pUnit, (char*)(aUStack_a00), iVar4, a2, (int*)(iVar8), a4, iVar6, 1);
		if (iVar8 != 0)
		{
			bVar1 = true;
		}
		iVar6 = iVar6 + 1;
	} while (iVar6 < 10);
	if (bVar1)
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
	}
	if (pDVar5 == nullptr)
	{
	LAB_6fb15531:
		pUVar7 = aUStack_a40;
		iVar6 = 0x20;
		iVar4 = *(short*)(iVar4 + 0x174) + a3;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar6 = iVar6 + -1;
		} while (iVar6 != 0);
		if (iVar4 == 0)
			goto LAB_6fb155ca;
		wsprintfA(aCStack_aa0, "%d", iVar4);
		Unicode::toUnicode(aUStack_a40, aCStack_aa0, 0x20);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x105b));
		pcVar10 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(aUStack_a00, pUVar7);
	}
	else
	{
		if ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= a2) ||
		    (iVar6 = (int)*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + 300 + iVar9),
		        iVar6 < 1))
		{
			iVar6 = 0x14;
		}
		iVar8 = SKILLS_GetSkillLevel(pUnit, pDVar5, 0);
		if (iVar8 < iVar6)
			goto LAB_6fb15531;
		D2LANG_GetStringFromTblIndex(0x1111);
		pcVar10 = (code*)(((uint8_t*)&Unicode::strcat));
	}
	(*pcVar10)();
	D2LANG_GetStringFromTblIndex(0xf9e);
	(*pcVar10)();
LAB_6fb155ca:
	iVar4 = *(int*)((uint8_t*)&sgptDataTables);
	if ((((a2 < *(int*)(iVar4 + 0xba0)) && (iVar6 = *(int*)(iVar4 + 0xb98) + iVar9, iVar6 != 0)) && (iVar6 = (int)*(short*)(iVar6 + 0x194), -1 < iVar6)) &&
	    ((iVar6 < *(int*)(iVar4 + 0xb94) &&
	        (iVar4 = iVar6 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar4 != 0))))
	{
		sVar3 = *(short*)(iVar4 + 0xc);
	}
	else
	{
		sVar3 = 0x1506;
	}
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar3));
	Unicode::strcat(aUStack_a00, pUVar7);
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcat(aUStack_a00, pUVar7);
	iVar4 = *(int*)((uint8_t*)&sgptDataTables);
	if (((a2 < *(int*)(iVar4 + 0xba0)) && (iVar9 = *(int*)(iVar4 + 0xb98) + iVar9, iVar9 != 0)) && ((iVar9 = (int)*(short*)(iVar9 + 0x194), -1 < iVar9 &&
	                                                                                                                                            ((iVar9 < *(int*)(iVar4 + 0xb94) &&
	                                                                                                                                                (iVar4 = iVar9 * 0x120 + *(int*)(iVar4 + 0xb8c), iVar4 != 0))))))
	{
		sVar3 = *(short*)(iVar4 + 8);
	}
	else
	{
		sVar3 = 0x1506;
	}
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar3));
	Unicode::strcpy(aUStack_200, pUVar7);
	sub_6FB20430((short*)aUStack_200, '\x02');
	Unicode::strcat(aUStack_a00, aUStack_200);
	if (bVar2)
	{
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1113));
		Unicode::strcat(aUStack_a00, pUVar7);
	}
	if (dword_6FBB9430 == 0)
	{
		iVar6 = 0;
		iVar4 = *(int*)((uint8_t*)&sgptDataTables);
		iVar9 = *(int*)(iVar4 + 0xba0);
		if (0 < iVar9)
		{
			iVar8 = 0;
			do
			{
				if (((((-1 < iVar8) && (iVar6 < iVar9)) &&
				         (iVar4 = *(int*)(iVar4 + 0xb98) + iVar8, iVar4 != 0)) &&
				        ((*(char*)(iVar4 + 0xc) == (char)pUnit->dwClassId &&
				            (pDVar5 = SKILLS_GetSkillById(pUnit, iVar6, 0xffffffff), pDVar5 != nullptr)))) &&
				    (iVar4 = SKILLS_GetSkillLevel(pUnit, pDVar5, 0), iVar4 != 0))
				{
					dword_6FBB9430 = 1;
					goto LAB_6fb157ee;
				}
				iVar6 = iVar6 + 1;
				iVar8 = iVar8 + 0x23c;
				iVar4 = *(int*)((uint8_t*)&sgptDataTables);
				iVar9 = *(int*)(iVar4 + 0xba0);
			} while (iVar6 < iVar9);
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		Unicode::strcat(aUStack_a00, pUVar7);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1114));
		Unicode::strcat(aUStack_a00, pUVar7);
	}
LAB_6fb157ee:
	D2Win_10131_GetTextDimensions(aUStack_a00, &iStack_aa4, &iStack_aa8);
	D2Win_10129_DrawFramedText(aUStack_a00, a5, iStack_aa8 + 3 + a6, 1, 0);
}

//D2Client.0x6FB15850
void __fastcall sub_6FB15850(D2UnitStrc* pUnit, int a2, uint32_t a3, uint32_t a4, int a5, int a6, int a7)
{
	bool bVar1;
	short sVar2;
	int iVar3;
	Unicode* pUVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iStack_868;
	int iStack_864;
	CHAR aCStack_860[32];
	Unicode aUStack_840[32];
	Unicode local_800[1024];

	if (((pUnit != nullptr) && (-1 < a2)) &&
	    (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)))
	{
		iVar3 = a2 * 0x23c;
		iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3;
		if (iVar7 != 0)
		{
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109c));
			Unicode::strcpy(local_800, pUVar4);
			iVar6 = 0;
			bVar1 = false;
			do
			{
				iVar5 = sub_6FB10970(pUnit, (char*)(local_800), iVar7, a2, (int*)(a3), a4, iVar6, a5);
				if (iVar5 != 0)
				{
					bVar1 = true;
				}
				iVar6 = iVar6 + 1;
			} while (iVar6 < 10);
			if (bVar1)
			{
				wsprintfA(aCStack_860, "%d", a3);
				Unicode::toUnicode(aUStack_840, aCStack_860, 0x20);
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x109e));
				Unicode::strcat(local_800, pUVar4);
				Unicode::strcat(local_800, aUStack_840);
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				Unicode::strcat(local_800, pUVar4);
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				Unicode::strcat(local_800, pUVar4);
			}
			if (((a2 == 0) && (pUnit->dwUnitType == 0)) && (pUnit->dwClassId == 6))
			{
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5722));
				Unicode::strcat(local_800, pUVar4);
			}
			iVar7 = *(int*)((uint8_t*)&sgptDataTables);
			if (((a2 < *(int*)(iVar7 + 0xba0)) &&
			        (iVar6 = *(int*)(iVar7 + 0xb98) + iVar3, iVar6 != 0)) &&
			    ((iVar6 = (int)*(short*)(iVar6 + 0x194), -1 < iVar6 &&
			                                                 ((iVar6 < *(int*)(iVar7 + 0xb94) &&
			                                                     (iVar7 = iVar6 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar7 != 0))))))
			{
				sVar2 = *(short*)(iVar7 + 10);
			}
			else
			{
				sVar2 = 0x1506;
			}
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::strcat(local_800, pUVar4);
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			Unicode::strcat(local_800, pUVar4);
			iVar7 = *(int*)((uint8_t*)&sgptDataTables);
			if ((((a2 < *(int*)(iVar7 + 0xba0)) &&
			         (iVar3 = *(int*)(iVar7 + 0xb98) + iVar3, iVar3 != 0)) &&
			        (iVar3 = (int)*(short*)(iVar3 + 0x194), -1 < iVar3)) &&
			    ((iVar3 < *(int*)(iVar7 + 0xb94) &&
			        (iVar3 = iVar3 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar3 != 0))))
			{
				sVar2 = *(short*)(iVar3 + 8);
			}
			else
			{
				sVar2 = 0x1506;
			}
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar2));
			Unicode::strcat(local_800, pUVar4);
			D2Win_10131_GetTextDimensions(local_800, &iStack_864, &iStack_868);
			D2Win_10129_DrawFramedText(local_800, a6, iStack_868 + 3 + a7, a5, 0);
		}
	}
}

//D2Client.0x6FB15B00
// TODO: decompilation needs review (stack0x, unaff_)
void __fastcall sub_6FB15B00(D2UnitStrc* pUnit, D2SkillStrc* pSkill, int a3)
{
	uint8_t stack0xfffffd50[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	bool bVar1;
	short index;
	D2SkillsTxt* pDVar2;
	int iVar3;
	int iVar4;
	Unicode* pUVar5;
	D2C_Language DVar6;
	int iVar7;
	int unaff_ESI;
	int unaff_EDI;
	int iVar8;
	uint32_t* puVar9;
	uint32_t* puVar10;
	D2SkillsTxt* pDVar11;
	uint32_t uStack_290;
	D2SkillsTxt* pDStack_28c;
	int iStack_288;
	int iStack_284;
	uint32_t uStack_280;
	int iStack_27c;
	D2UnitStrc* local_278;
	uint32_t auStack_274[3];
	uint32_t auStack_268[6];
	Unicode aUStack_250[20];
	Unicode aUStack_228[32];
	Unicode aUStack_1e8[32];
	Unicode aUStack_1a8[12];
	Unicode aUStack_190[187];
	uint16_t uStack_1a;

	local_278 = pUnit;
	pDVar2 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
	if (pDVar2 == nullptr)
	{
		return;
	}
	iStack_288 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
	iVar3 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
	if (iVar3 < 0)
	{
		return;
	}
	iVar7 = *(int*)((uint8_t*)&sgptDataTables);
	if (*(int*)(iVar7 + 0xba0) <= iVar3)
	{
		return;
	}
	iVar4 = *(int*)(iVar7 + 0xb98) + iVar3 * 0x23c;
	if (iVar4 == 0)
	{
		return;
	}
	iVar4 = (int)*(short*)(iVar4 + 0x194);
	if (iVar4 < 0)
	{
		return;
	}
	if (*(int*)(iVar7 + 0xb94) <= iVar4)
	{
		return;
	}
	iStack_27c = iVar4 * 0x120 + *(int*)(iVar7 + 0xb8c);
	if (iStack_27c == 0)
	{
		return;
	}
	D2Win_10127_SetFont(D2FONT_FONT6);
	iVar7 = *(int*)((uint8_t*)&sgptDataTables);
	if ((((iVar3 < *(int*)(iVar7 + 0xba0)) &&
	         (iVar3 = *(int*)(iVar7 + 0xb98) + iVar3 * 0x23c, iVar3 != 0)) &&
	        (iVar3 = (int)*(short*)(iVar3 + 0x194), -1 < iVar3)) &&
	    ((iVar3 < *(int*)(iVar7 + 0xb94) &&
	        (iVar3 = iVar3 * 0x120 + *(int*)(iVar7 + 0xb8c), iVar3 != 0))))
	{
		index = *(short*)(iVar3 + 0xe);
	}
	else
	{
		index = 0x1506;
	}
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	Unicode::strcpy(aUStack_250, pUVar5);
	sub_6FB203F0((int)aUStack_250);
	sub_6FACFCD0(*(int*)(byte_6FB8CDD8 + a3 * 0xc) + dword_6FBBA748,
	    (&dword_6FB8CDDC)[a3 * 3] + dword_6FBBA74C + -0x1e0 + gnScreenHeight,
	    *(int*)(byte_6FB8CDE0 + a3 * 0xc) + dword_6FBBA748, aUStack_250,
	    nullptr);
	bVar1 = false;
	iStack_284 = 0;
	iVar3 = sub_6FB4DA80(local_278, pSkill);
	switch (iVar3)
	{
	case 0:
	case 1:
	case 6:
	case 8:
		bVar1 = true;
		iStack_284 = 1;
	}
	if ((0x8f < *(uint16_t*)(iStack_27c + 0x12)) ||
	    (*(int*)(byte_6FB8CD00 + (uint32_t) * (uint16_t*)(iStack_27c + 0x12) * 4) == 0))
	{
		bVar1 = false;
	}
	if ((0x47 < *(uint16_t*)(iStack_27c + 0x14)) ||
	    (*(int*)(byte_6FB8CD90 + (uint32_t) * (uint16_t*)(iStack_27c + 0x14) * 4) == 0))
	{
		iStack_284 = 0;
	}
	if (bVar1)
	{
		pDVar11 = nullptr;
		iVar3 = (a3 + 1) * 0xc;
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfdd));
		sub_6FACFCD0(*(int*)(byte_6FB8CDD8 + iVar3) + dword_6FBBA748,
		    (&dword_6FB8CDDC)[(a3 + 1) * 3] + dword_6FBBA74C + -0x1e0 + gnScreenHeight,
		    *(int*)(byte_6FB8CDE0 + iVar3) + dword_6FBBA748, pUVar5, pDVar11);
	}
	if (bVar1)
	{
		(**(code**)(byte_6FB8CD00 + (uint32_t) * (uint16_t*)(iStack_27c + 0x12) * 4))(pDVar2, iStack_288, *(uint32_t*)(byte_6FB8CDD8 + (a3 + 2) * 0xc));
	}
	if (iStack_284 == 0)
	{
		return;
	}
	pDStack_28c = nullptr;
	uStack_290 = 0;
	uStack_280 = 0;
	auStack_274[0] = 0;
	puVar10 = auStack_274;
	puVar9 = &uStack_290;
	(**(code**)(byte_6FB8CD90 + (uint32_t) * (uint16_t*)(iStack_27c + 0x14) * 4))(pDVar2, iStack_288, &pDStack_28c, &uStack_280);
	iVar3 = a3 + 3;
	if ((unaff_ESI != 0) || (unaff_EDI != 0))
	{
		D2Win_10127_SetFont(D2FONT_FONT6);
		if (puVar10 == nullptr)
		{
			puVar10 = auStack_268;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfe1));
		}
		else
		{
			puVar10 = auStack_268;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfdf));
		}
		Unicode::sprintf(200, aUStack_1a8, pUVar5, puVar10);
		uStack_1a = 0;
		iVar7 = sub_6FACFD10((short*)aUStack_1a8, (uint32_t*)stack0xfffffd50);
		if (iVar7 == 0)
		{
			puVar9 = auStack_268;
			iVar4 = *(int*)(byte_6FB8CDE0 + iVar3 * 0xc) + dword_6FBBA748;
			iVar7 = (&dword_6FB8CDDC)[iVar3 * 3] + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
			iVar3 = *(int*)(byte_6FB8CDD8 + iVar3 * 0xc) + dword_6FBBA748;
		}
		else
		{
			iVar8 = iVar3 * 0xc;
			sub_6FACFCD0(*(int*)(byte_6FB8CDD8 + iVar8) + dword_6FBBA748,
			    (&dword_6FB8CDDC)[iVar3 * 3] + dword_6FBBA74C + -0x1e4 + gnScreenHeight,
			    *(int*)(byte_6FB8CDE0 + iVar8) + dword_6FBBA748, aUStack_1a8, nullptr);
			iVar4 = *(int*)(byte_6FB8CDE0 + iVar8) + dword_6FBBA748;
			iVar7 = (&dword_6FB8CDDC)[iVar3 * 3] + dword_6FBBA74C + -0x1dc + gnScreenHeight;
			iVar3 = *(int*)(byte_6FB8CDD8 + iVar8) + dword_6FBBA748;
		}
		sub_6FACFCD0(iVar3, iVar7, iVar4, (Unicode*)(puVar9), nullptr);
	}
	iVar3 = a3 + 5;
	if (unaff_EDI == 0)
	{
		if (unaff_ESI == 0)
		{
			return;
		}
		iVar7 = *(int*)(byte_6FB8CDE0 + iVar3 * 0xc);
		iVar4 = (&dword_6FB8CDDC)[iVar3 * 3];
		iVar3 = *(int*)(byte_6FB8CDD8 + iVar3 * 0xc);
		wsprintfA((LPSTR)&iStack_288, "%d", unaff_ESI);
		Unicode::toUnicode(aUStack_228, (char*)&iStack_288, 0x20);
		D2Win_10127_SetFont((Font)((uint32_t)(unaff_ESI < 1000)));
		sub_6FACFCD0(iVar3 + dword_6FBBA748, gnScreenHeight + -0x1e0 + iVar4 + dword_6FBBA74C,
		    iVar7 + dword_6FBBA748, aUStack_228, pDVar2);
		return;
	}
	wsprintfA((LPSTR)&iStack_288, "%d", unaff_ESI);
	Unicode::toUnicode(aUStack_1e8, (char*)&iStack_288, 0x20);
	wsprintfA((LPSTR)&iStack_288, "%d", unaff_EDI);
	Unicode::toUnicode(aUStack_228, (char*)&iStack_288, 0x20);
	pDVar11 = pDStack_28c;
	iVar7 = *(int*)(byte_6FB8CDE0 + iVar3 * 0xc);
	iVar4 = (&dword_6FB8CDDC)[iVar3 * 3];
	iVar3 = *(int*)(byte_6FB8CDD8 + iVar3 * 0xc);
	D2Win_10127_SetFont(D2FONT_FONT6);
	if (byte_6FBB942C != '\0')
		goto LAB_6fb1602c;
	DVar6 = STRTABLE_GetLanguage();
	if ((int)DVar6 < 6)
	{
	LAB_6fb1601b:
		dword_6FB8CCF4 = -6;
	}
	else
	{
		DVar6 = STRTABLE_GetLanguage();
		dword_6FB8CCF4 = -7;
		if (9 < (int)DVar6)
			goto LAB_6fb1601b;
	}
	byte_6FBB942C = '\x01';
LAB_6fb1602c:
	sub_6FACFCD0(dword_6FBBA748 + iVar3, iVar4 + dword_6FB8CCF4 + dword_6FBBA74C + -0x1e0 + gnScreenHeight,
	    iVar7 + dword_6FBBA748, aUStack_1e8, pDVar2);
	sub_6FACFCD0(dword_6FBBA748 + iVar3, iVar4 + dword_6FB8CCF8 + dword_6FBBA74C + -0x1e0 + gnScreenHeight,
	    iVar7 + dword_6FBBA748, aUStack_228, pDVar11);
}

//D2Client.0x6FB16190
void __fastcall sub_6FB16190(D2UnitStrc* pUnit)
{
	D2C_Language DVar1;
	D2SkillStrc* pDVar2;

	if (byte_6FBB9434 == '\0')
	{
		DVar1 = STRTABLE_GetLanguage();
		if (5 < (int)DVar1)
		{
			DVar1 = STRTABLE_GetLanguage();
			if ((int)DVar1 < 10)
			{
				dword_6FB8CDDC = dword_6FB8CDDC + -1;
				dword_6FB8CE24 = dword_6FB8CE24 + -1;
			}
		}
		byte_6FBB9434 = '\x01';
	}
	if (pUnit != nullptr)
	{
		pDVar2 = UNITS_GetLeftSkill(pUnit);
		sub_6FB15B00(pUnit, pDVar2, 0);
		pDVar2 = UNITS_GetRightSkill(pUnit);
		sub_6FB15B00(pUnit, pDVar2, 6);
	}
}

//D2Client.0x6FB16200
uint32_t __fastcall sub_6FB16200(D2UnitStrc* pUnit, int a2)
{
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar1;
	int iVar2;
	int iVar3;
	uint32_t uStack_10;
	uint32_t uStack_c;
	uint32_t auStack_8;
	uint8_t auStack_4[4];

	if (pUnit == nullptr)
	{
		return 0;
	}
	if (a2 == 0)
	{
		pSkill = UNITS_GetRightSkill(pUnit);
	}
	else
	{
		pSkill = UNITS_GetLeftSkill(pUnit);
	}
	pDVar1 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
	if (pDVar1 == nullptr)
	{
		return 0;
	}
	iVar2 = (int)pDVar1->nSkillId;
	if (((((-1 < iVar2) && (iVar3 = *(int*)((uint8_t*)&sgptDataTables), iVar2 < *(int*)(iVar3 + 0xba0))) &&
	         (iVar2 = *(int*)(iVar3 + 0xb98) + iVar2 * 0x23c, iVar2 != 0)) &&
	        ((iVar2 = (int)*(short*)(iVar2 + 0x194), -1 < iVar2 && (iVar2 < *(int*)(iVar3 + 0xb94))))) &&
	    (iVar2 = iVar2 * 0x120 + *(int*)(iVar3 + 0xb8c), iVar2 != 0))
	{
		uStack_10 = 0;
		uStack_c = 0;
		if ((*(uint16_t*)(iVar2 + 0x14) < 0x48) &&
		    (*(int*)(byte_6FB8CD90 + (uint32_t) * (uint16_t*)(iVar2 + 0x14) * 4) != 0))
		{
			iVar3 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			(**(code**)(byte_6FB8CD90 + (uint32_t) * (uint16_t*)(iVar2 + 0x14) * 4))(pDVar1, iVar3, &uStack_10, auStack_4, &uStack_c, auStack_8);
		}
		return uStack_10;
	}
	return 0;
}

//D2Client.0x6FB16300
void __cdecl sub_6FB16300()
{
	dword_6FBB983C = 0;
}

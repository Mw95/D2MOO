#include "UI/Char.h"

#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/Scroll.h"
#include "Sound/SoundInst.h"
#include "UI/Chat.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/Panel.h"
#include "UI/SkillDesc.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB6EF00
uint32_t dword_6FB6EF00 = 0x9A;
//D2Client.0x6FB6EF04
uint32_t dword_6FB6EF04 = 0x73;
//D2Client.0x6FB6EF08
uint32_t dword_6FB6EF08 = 0x9F;
//D2Client.0x6FB6EF0C
uint32_t dword_6FB6EF0C = 0x80;
//D2Client.0x6FB6EF10
uint32_t dword_6FB6EF10 = 0x9F;
//D2Client.0x6FB6EF14
uint32_t dword_6FB6EF14 = 0x8C;
//D2Client.0x6FB78010
uint32_t dword_6FB78010 = 0xB;
//D2Client.0x6FB7801C
uint16_t word_6FB7801C = 0xFD9;
//D2Client.0x6FB7801E
uint32_t dword_6FB7801E[4] = {6, 0x41, 0x2C, 0xB4};
//D2Client.0x6FB78120
uint8_t byte_6FB78120[4] = {0xD};
//D2Client.0x6FB78124
uint8_t byte_6FB78124[4] = {0x3B};
//D2Client.0x6FB78128
uint8_t byte_6FB78128[4] = {0x35};
//D2Client.0x6FB7812C
uint32_t dword_6FB7812C = 0xC;
//D2Client.0x6FB78248
uint32_t dword_6FB78248;
//D2Client.0x6FB7824C
uint8_t byte_6FB7824C[2];
//D2Client.0x6FBB1A44
uint8_t byte_6FBB1A44;
//D2Client.0x6FBB1A4C
uint32_t dword_6FBB1A4C;
//D2Client.0x6FBB1A50
uint8_t byte_6FBB1A50;
//D2Client.0x6FBB1C60
uint8_t byte_6FBB1C60;
//D2Client.0x6FBB2CB8
uint8_t byte_6FBB2CB8;
//D2Client.0x6FBB2CF6
uint8_t byte_6FBB2CF6;

//D2Client.0x6FACFD60
void __cdecl sub_6FACFD60()
{
	Unicode UVar1;
	bool bVar2;
	bool bVar3;
	uint8_t bVar4;
	char cVar5;
	D2UnitStrc* pUnit;
	int iVar6;
	Unicode* pUVar7;
	D2UnitStrc* pDVar8;
	Unicode* pUVar9;
	char* a1;
	D2C_Language DVar10;
	int iVar11;
	Font FVar12;
	uint32_t uVar13;
	D2DifficultyLevelsTxt* pDVar14;
	uint32_t* puVar15;
	uint32_t uVar16;
	int* piVar17;
	D2GfxDataStrc* pDVar18;
	int iVar19;
	int iVar20;
	D2MonStatsInitStrc* pDVar21;
	D2MonStatsInitStrc* pDVar22;
	char* pcVar23;
	short sVar24;
	int iVar25;
	int iVar26;
	int iVar27;
	uint32_t local_3b0;
	uint32_t uStack_3a8;
	int iStack_3a0;
	D2DifficultyLevelsTxt* pDStack_39c;
	int iStack_398;
	int iStack_394;
	D2DifficultyLevelsTxt* pDStack_390;
	D2UnitStrc* pDStack_38c;
	D2GfxDataStrc local_388;
	int iStack_340;
	Unicode aUStack_33c[10];
	CHAR aCStack_328[12];
	D2MonStatsInitStrc DStack_31c;
	CHAR aCStack_2e4[128];
	uint32_t uStack_264;
	uint16_t uStack_19e;
	Unicode aUStack_164[127];
	uint16_t uStack_66;
	Unicode aUStack_64[50];

	pUnit = CUNIT_GetPlayer();
	pDVar18 = &local_388;
	for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1)
	{
		pDVar18->pCurrentCell = nullptr;
		pDVar18 = (D2GfxDataStrc*)&pDVar18->pCellFile;
	}
	local_388.pCellFile = gpCellFile_6FBB5E24;
	local_388.nDirection = 0;
	local_388.nFrame = 0;
	TEXTURE_CelDraw(&local_388, dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_388.nFrame = 1;
	TEXTURE_CelDraw(&local_388, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_388.nFrame = 2;
	TEXTURE_CelDraw(&local_388, dword_6FBBA748, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_388.nFrame = 3;
	TEXTURE_CelDraw(&local_388, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	iVar11 = sub_6FB57BC0();
	iVar6 = sub_6FB57BD0();
	if ((((dword_6FBBA748 + 0x80 <= iVar11) && (iVar11 <= dword_6FBBA748 + 0xa0)) &&
	        (dword_6FBBA74C + -0x5c + gnScreenHeight <= iVar6)) &&
	    (iVar6 <= dword_6FBBA74C + -0x3c + gnScreenHeight))
	{
		iVar26 = 1;
		iVar20 = dword_6FBBA74C + -0x5f + gnScreenHeight;
		iVar25 = 0;
		iVar19 = dword_6FBBA748 + 0x8f;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
		D2Win_10129_DrawFramedText(pUVar7, iVar19, iVar20, iVar25, iVar26);
	}
	iVar19 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
	if (iVar19 != 0)
	{
		local_388.pCellFile = gpCellFile_6FBB5E50;
		local_388.nFrame = 0;
		TEXTURE_CelDraw(&local_388, dword_6FBBA748 + 3, dword_6FBBA74C + -0x74 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		D2Win_10127_SetFont(D2FONT_FONT6);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfeb));
		iVar20 = dword_6FBBA74C + -0x7d + gnScreenHeight;
		iVar19 = dword_6FBBA748 + 0xb;
		iVar25 = (dword_6FBBA748 - iVar19) + 0x59;
		iVar26 = D2Win_10121_GetTextWidth(pUVar7);
		if (iVar26 < iVar25)
		{
			iVar19 = iVar19 + (iVar25 - iVar26 >> 1);
		}
		D2Win_10117_DrawText(pUVar7, iVar19, iVar20, 1, 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfec));
		iVar20 = dword_6FBBA74C + -0x75 + gnScreenHeight;
		iVar19 = dword_6FBBA748 + 0xb;
		iVar25 = (dword_6FBBA748 - iVar19) + 0x59;
		iVar26 = D2Win_10121_GetTextWidth(pUVar7);
		if (iVar26 < iVar25)
		{
			iVar19 = iVar19 + (iVar25 - iVar26 >> 1);
		}
		D2Win_10117_DrawText(pUVar7, iVar19, iVar20, 1, 0);
		iVar19 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
		wsprintfA(aCStack_328, "%i", iVar19);
		D2Win_10127_SetFont(D2FONT_FONT16);
		Unicode::win2Unicode(aUStack_33c, aCStack_328, 9);
		iVar20 = dword_6FBBA74C + -0x78 + gnScreenHeight;
		iVar19 = dword_6FBBA748 + 0x5c;
		iVar25 = (dword_6FBBA748 - iVar19) + 0x80;
		iVar26 = D2Win_10121_GetTextWidth(aUStack_33c);
		if (iVar26 < iVar25)
		{
			iVar19 = iVar19 + (iVar25 - iVar26 >> 1);
		}
		D2Win_10117_DrawText(aUStack_33c, iVar19, iVar20, 0, 0);
	}
	iVar19 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
	if (iVar19 != 0)
	{
		piVar17 = (int*)("i");
		do
		{
			local_388.pCellFile = gpCellFile_6FBB5BB8;
			iVar19 = *piVar17 + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
			iVar20 = piVar17[-1] + dword_6FBBA748;
			local_388.nFrame = 0;
			TEXTURE_CelDraw(&local_388, iVar20 + 5, iVar19 + 5, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			local_388.nFrame = (uint32_t)(piVar17[1] != 0);
			local_388.pCellFile = gpCellFile_6FBB5BB4;
			TEXTURE_CelDraw(&local_388, iVar20 + 8, iVar19 + 1, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			piVar17 = (int*)((int)piVar17 + 0xe);
		} while ((int)piVar17 < (int)"nDifficultyLevel < NUM_DIFFICULTY_LEVELS");
	}
	D2Win_10127_SetFont(D2FONT_FONT6);
	uVar13 = 0;
	do
	{
		pUVar7 = (Unicode*)&uStack_264;
		iVar19 = 100;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar19 = iVar19 + -1;
		} while (iVar19 != 0);
		iVar19 = 99;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)&word_6FB7801C + uVar13)));
		Unicode::strncpy((Unicode*)&uStack_264, pUVar7, iVar19);
		iVar25 = *(int*)((int)&dword_6FB78010 + uVar13) + dword_6FBBA748;
		iVar26 = *(int*)((int)"4" + uVar13) + dword_6FBBA748;
		uStack_19e = 0;
		puVar15 = &uStack_264;
		iStack_398 = *(int*)((int)"," + uVar13) + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
		iVar20 = Unicode::strlen((Unicode*)&uStack_264);
		iVar19 = 0;
		uVar16 = uStack_264;
		UVar1.ch = (*(uint16_t*)((uint8_t*)&uStack_264 + 0));
		while (UVar1.ch != 0)
		{
			if ((short)uVar16 == 10)
			{
				*(uint16_t*)((int)&uStack_264 + iVar19 * 2) = 0;
				if (iVar19 < iVar20)
				{
					pUVar7 = (Unicode*)((int)puVar15 + 2);
					iVar26 = (iVar26 - iVar25) + 1;
					iVar20 = D2Win_10121_GetTextWidth((Unicode*)&uStack_264);
					iVar19 = iVar25;
					if (iVar20 < iVar26)
					{
						iVar19 = (iVar26 - iVar20 >> 1) + iVar25;
					}
					D2Win_10117_DrawText((Unicode*)&uStack_264, iVar19, iStack_398 + -4, 0, 0);
					iVar19 = D2Win_10121_GetTextWidth(pUVar7);
					if (iVar19 < iVar26)
					{
						iVar25 = (iVar26 - iVar19 >> 1) + iVar25;
					}
					iVar19 = iStack_398 + 4;
					goto LAB_6fad01f5;
				}
				break;
			}
			UVar1.ch = *(uint16_t*)((int)puVar15 + 2);
			uVar16 = (uint32_t)UVar1.ch;
			puVar15 = (uint32_t*)((int)puVar15 + 2);
			iVar19 = iVar19 + 1;
		}
		iVar20 = (iVar26 - iVar25) + 1;
		iVar19 = D2Win_10121_GetTextWidth((Unicode*)&uStack_264);
		if (iVar19 < iVar20)
		{
			iVar25 = (iVar20 - iVar19 >> 1) + iVar25;
		}
		pUVar7 = (Unicode*)&uStack_264;
		iVar19 = iStack_398;
	LAB_6fad01f5:
		D2Win_10117_DrawText(pUVar7, iVar25, iVar19, 0, 0);
		uVar13 = uVar13 + 0x12;
	} while (uVar13 < 0x10e);
	sub_6FB16190(pUnit);
	D2Win_10127_SetFont(D2FONT_FONT8);
	iVar19 = sub_6FB16200(pUnit, 1);
	pDStack_390 = sub_6FAD10D0(iVar19);
	iVar19 = sub_6FB16200(pUnit, 0);
	pDStack_39c = sub_6FAD10D0(iVar19);
	pDVar8 = CUNIT_GetPlayer();
	iStack_398 = 100;
	pDStack_38c = pDVar8;
	iVar20 = UNITS_GetDefense(pDVar8);
	iVar19 = STATLIST_UnitGetStatValue(pDVar8, 0x21, 0);
	iVar20 = iVar20 + iVar19;
	bVar4 = sub_6FAAC090();
	uVar13 = (uint32_t)bVar4;
	D2_ASSERT(2 >= uVar13);
	iVar19 = sub_6FAB5A80();
	if (((iVar19 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar19)) ||
	    (iVar25 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar19 * 0x1a8, iVar25 == 0))
	{
		iStack_3a0 = 0;
	}
	else
	{
		pDVar22 = &DStack_31c;
		pDVar21 = &DStack_31c;
		for (iVar26 = 0xe; iVar26 != 0; iVar26 = iVar26 + -1)
		{
			pDVar21->nMinHP = 0;
			pDVar21 = (D2MonStatsInitStrc*)&pDVar21->nMaxHP;
		}
		iVar26 = (int)*(short*)(iVar25 + 0xaa + uVar13 * 2);
		sVar24 = 8;
		uVar16 = uVar13;
		iVar27 = sub_6FAAC060();
		DATATBLS_CalculateMonsterStatsByLevel(iVar19, iVar27, uVar16, iVar26, sVar24, pDVar22);
		iVar26 = DStack_31c.nTH;
		if (DStack_31c.nTH == 0)
		{
			pDVar22 = &DStack_31c;
			for (iVar26 = 0xe; iVar26 != 0; iVar26 = iVar26 + -1)
			{
				pDVar22->nMinHP = 0;
				pDVar22 = (D2MonStatsInitStrc*)&pDVar22->nMaxHP;
			}
			iVar27 = (int)*(short*)(iVar25 + 0xaa + uVar13 * 2);
			pDVar22 = &DStack_31c;
			sVar24 = 0x10;
			uVar16 = uVar13;
			iVar26 = sub_6FAAC060();
			DATATBLS_CalculateMonsterStatsByLevel(iVar19, iVar26, uVar16, iVar27, sVar24, pDVar22);
			iVar26 = DStack_31c.nTH;
			if (DStack_31c.nTH == 0)
			{
				pDVar22 = &DStack_31c;
				for (iVar26 = 0xe; iVar26 != 0; iVar26 = iVar26 + -1)
				{
					pDVar22->nMinHP = 0;
					pDVar22 = (D2MonStatsInitStrc*)&pDVar22->nMaxHP;
				}
				iVar27 = (int)*(short*)(iVar25 + 0xaa + uVar13 * 2);
				pDVar22 = &DStack_31c;
				sVar24 = 0x20;
				uVar16 = uVar13;
				iVar26 = sub_6FAAC060();
				DATATBLS_CalculateMonsterStatsByLevel(iVar19, iVar26, uVar16, iVar27, sVar24, pDVar22);
				iVar26 = DStack_31c.nTH;
			}
		}
		if (((*(char*)(iVar25 + 0x4c) != '\x01') && (iVar19 = sub_6FAAC080(), iVar19 == 0)) &&
		    (cVar5 = sub_6FAAC090(), cVar5 != '\0'))
		{
			iVar26 = (iVar26 * 10) / 0xf;
		}
		if (iVar20 < 0)
		{
			iVar26 = iVar26 - iVar20;
			iVar20 = 0;
		}
		if (iVar26 < 0)
		{
			iVar20 = iVar20 - iVar26;
			iVar26 = 0;
		LAB_6fad0456:
			iVar19 = iStack_398;
			if (iVar20 != 0)
				goto LAB_6fad045a;
		}
		else
		{
			if (iVar26 == 0)
				goto LAB_6fad0456;
		LAB_6fad045a:
			iVar19 = (iVar26 * 100) / (iVar26 + iVar20);
		}
		iVar25 = (int)*(short*)(iVar25 + 0xaa + uVar13 * 2);
		iVar20 = STATLIST_UnitGetStatValue(pDStack_38c, 0xc, 0);
		iStack_3a0 = (iVar25 * iVar19 * 2) / (iVar20 + iVar25);
	}
	pUVar7 = (Unicode*)&uStack_264;
	iVar19 = 0x80;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar19 = iVar19 + -1;
	} while (iVar19 != 0);
	sub_6FB01C50();
	bVar2 = false;
	bVar3 = false;
	if ((((iVar11 < dword_6FBBA748 + 0xa2) || (dword_6FBBA748 + 0x140 < iVar11)) ||
	        (iVar6 < dword_6FBBA74C + -0x14e + gnScreenHeight)) ||
	    (dword_6FBBA74C + -0x13b + gnScreenHeight < iVar6))
	{
		if (((dword_6FBBA748 + 0xa2 <= iVar11) && (iVar11 <= dword_6FBBA748 + 0x140)) &&
		    ((dword_6FBBA74C + -0x134 + gnScreenHeight <= iVar6 &&
		        (iVar6 <= dword_6FBBA74C + -0x121 + gnScreenHeight))))
		{
			bVar3 = true;
		}
	}
	else
	{
		bVar2 = true;
	}
	if (pDStack_390 == nullptr)
	{
		bVar2 = false;
	}
	if (pDStack_39c == nullptr)
	{
		bVar3 = false;
	}
	if (bVar2)
	{
		iVar19 = 0;
		pDVar14 = pDStack_390;
	}
	else
	{
		if (!bVar3)
			goto LAB_6fad06a8;
		iVar19 = 1;
		pDVar14 = pDStack_39c;
	}
	if ((int)pDVar14 < 5)
	{
		pDVar14 = (D2DifficultyLevelsTxt*)0x5;
	}
	else if (0x5f < (int)pDVar14)
	{
		pDVar14 = (D2DifficultyLevelsTxt*)0x5f;
	}
	iVar19 = iVar19 * 0x18;
	sub_6FB5B0F0(*(int*)(dword_6FB6EF00 + iVar19) + dword_6FBBA748,
	    *(int*)(dword_6FB6EF04 + iVar19) + dword_6FBBA74C + -0x1e0 + gnScreenHeight, 0x9b, 0x1e,
	    byte_6FBB1A50 & 0xff, (DrawMode)(2));
	iVar25 = *(int*)(dword_6FB6EF08 + iVar19) + dword_6FBBA748;
	iVar27 = 0;
	iVar26 = 0;
	iVar20 = *(int*)(dword_6FB6EF0C + iVar19) + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x103f));
	D2Win_10117_DrawText(pUVar7, iVar25, iVar20, iVar26, iVar27);
	iVar20 = sub_6FAB5A70();
	if (((iVar20 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar20)) ||
	    (iVar20 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar20 * 0x1a8, iVar20 == 0))
	{
		FOG_DisplayAssert("ptStats", __FILE__, __LINE__);
		exit(-1);
	}
	pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar20 + 6)));
	pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2777));
	Unicode::sprintf(0x80, (Unicode*)&uStack_264, pUVar9, pUVar7, pDVar14);
	D2Win_10117_DrawText((Unicode*)&uStack_264, *(int*)(dword_6FB6EF10 + iVar19) + dword_6FBBA748,
	    *(int*)(dword_6FB6EF14 + iVar19) + dword_6FBBA74C + -0x1e0 + gnScreenHeight, 0, 0);
LAB_6fad06a8:
	if (iStack_3a0 < 5)
	{
		iStack_3a0 = 5;
	}
	else if (0x5f < iStack_3a0)
	{
		iStack_3a0 = 0x5f;
	}
	pUVar7 = (Unicode*)&uStack_264;
	iVar19 = 0x80;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar19 = iVar19 + -1;
	} while (iVar19 != 0);
	if ((((dword_6FBBA748 + 0xad <= iVar11) && (iVar11 <= dword_6FBBA748 + 0x137)) &&
	        (dword_6FBBA74C + -0x11e + gnScreenHeight <= iVar6)) &&
	    (iVar6 <= dword_6FBBA74C + -0x10b + gnScreenHeight))
	{
		pDVar8 = CUNIT_GetPlayer();
		iVar11 = sub_6FAAC080();
		iVar11 = UNITS_GetBlockRate(pDVar8, iVar11);
		if (((iVar11 < 1) && (iVar11 = sub_6FAD1010(pDVar8), 0 < iVar11)) &&
		    (COMPOSIT_GetWeaponClassId(pDVar8, pDVar8->pInventory, (int*)&pDStack_39c, -1, 1),
		        pDStack_39c != (D2DifficultyLevelsTxt*)0xd))
		{
			iVar11 = 0;
		}
		iVar6 = sub_6FAB5A80();
		if (((iVar6 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar6)) ||
		    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar6 * 0x1a8, iVar6 == 0))
		{
			FOG_DisplayAssert("ptStats", __FILE__, __LINE__);
			exit(-1);
		}
		iVar19 = iStack_3a0;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar6 + 6)));
		if (iVar11 == 0)
		{
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2778));
			Unicode::sprintf(0x80, (Unicode*)&uStack_264, pUVar9, pUVar7, iVar19);
		}
		else
		{
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2779));
			Unicode::sprintf(0x80, (Unicode*)&uStack_264, pUVar7, iVar11, iStack_3a0);
		}
		D2Win_10132((Unicode*)&uStack_264, dword_6FBBA748 + 0x8b, dword_6FBBA74C + -0x13b + gnScreenHeight,
		    byte_6FBB1A50 & 0xff, DRAWMODE_TRANS75, 0);
	}
	D2Win_10127_SetFont(D2FONT_FONT16);
	local_388.pCellFile = sub_6FB24110();
	local_388.nFrame = (dword_6FBB1A4C != 0) + 10;
	TEXTURE_CelDraw(&local_388, dword_6FBBA748 + 0x80, dword_6FBBA74C + -0x3c + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	if ((pUnit != nullptr) && (pUnit->dwUnitType == 0))
	{
		iVar11 = pUnit->dwClassId;
		if ((iVar11 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= iVar11))
		{
			pUVar7 = nullptr;
		}
		else
		{
			pUVar7 = (Unicode*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar11 * 0xc4);
		}
		iVar11 = dword_6FBBA748 + 0xc1;
		iVar6 = dword_6FBBA74C + -0x1c7 + gnScreenHeight;
		iVar19 = (dword_6FBBA748 - iVar11) + 0x137;
		iVar20 = D2Win_10121_GetTextWidth(pUVar7);
		if (iVar20 < iVar19)
		{
			iVar11 = iVar11 + (iVar19 - iVar20 >> 1);
		}
		D2Win_10117_DrawText(pUVar7, iVar11, iVar6, 0, 0);
		a1 = (char*)sub_6FAB0C00(pUnit);
		uVar13 = 0xffffffff;
		pcVar23 = a1;
		do
		{
			if (uVar13 == 0)
				break;
			uVar13 = uVar13 - 1;
			cVar5 = *pcVar23;
			pcVar23 = pcVar23 + 1;
		} while (cVar5 != '\0');
		uVar13 = Unicode::unicodenwidth(a1, ~uVar13 - 1);
		if (0xb < uVar13 + 1)
		{
			if (uVar13 + 1 < 0xe)
			{
				FVar12 = D2FONT_FONT8;
			}
			else
			{
				FVar12 = D2FONT_FONT6;
			}
			D2Win_10127_SetFont(FVar12);
		}
		Unicode::win2Unicode(aUStack_164, a1, 0x80);
		iVar6 = dword_6FBBA74C + -0x1c7 + gnScreenHeight;
		iVar11 = dword_6FBBA748 + 0xd;
		iVar19 = (dword_6FBBA748 - iVar11) + 0xa1;
		iVar20 = D2Win_10121_GetTextWidth(aUStack_164);
		if (iVar20 < iVar19)
		{
			iVar11 = iVar11 + (iVar19 - iVar20 >> 1);
		}
		D2Win_10117_DrawText(aUStack_164, iVar11, iVar6, 0, 0);
		D2Win_10127_SetFont(D2FONT_FONT16);
	}
	uStack_3a8 = 0;
	do
	{
		local_3b0 = 0;
		iVar6 = uStack_3a8 * 0x10;
		bVar2 = false;
		uVar13 = STATLIST_UnitGetStatValue(pUnit, (&dword_6FB7812C)[uStack_3a8 * 4], 0);
		iVar11 = STATLIST_GetUnitBaseStat(pUnit, (&dword_6FB7812C)[uStack_3a8 * 4], 0);
		if (0x27 < (&dword_6FB7812C)[uStack_3a8 * 4] - 6)
		{
		switchD_6fad0a33_caseD_ffffffff:
			uVar16 = uVar13;
			if (iVar11 < (int)uVar13)
			{
				local_3b0 = 3;
			}
			else if ((int)uVar13 < iVar11)
			{
				local_3b0 = 1;
			}
		LAB_6fad0e8c:
			bVar2 = false;
			wsprintfA(aCStack_2e4, "%ld", uVar16);
			goto LAB_6fad0e95;
		}
		uVar16 = (int)uVar13 >> 8;
		switch ((&dword_6FB7812C)[uStack_3a8 * 4])
		{
		case 6:
			pDVar8 = CUNIT_GetPlayer();
			if (((pDVar8 != nullptr) && (pDVar8->dwUnitType == 0)) &&
			    ((pDVar8->dwAnimMode != 0x11 && ((-1 < (int)uVar16 && ((int)uVar16 < 2))))))
			{
				uVar16 = 1;
			}
			goto LAB_6fad0b3e;
		case 7:
			if (iVar11 < (int)uVar13)
			{
				local_3b0 = 3;
				wsprintfA(aCStack_2e4, "%ld", uVar16);
				bVar2 = true;
			}
			else
			{
				local_3b0 = (uint32_t)((int)uVar13 < iVar11);
				wsprintfA(aCStack_2e4, "%ld", uVar16);
				bVar2 = true;
			}
			break;
		case 8:
			wsprintfA(aCStack_2e4, "%ld", uVar16);
			bVar2 = true;
			break;
		case 9:
			if (iVar11 < (int)uVar13)
			{
				local_3b0 = 3;
			}
			else if ((int)uVar13 < iVar11)
			{
				local_3b0 = 1;
			}
		case 10:
			wsprintfA(aCStack_2e4, "%ld", uVar16);
			bVar2 = true;
			break;
		case 0xb:
			if (iVar11 < (int)uVar13)
			{
				local_3b0 = 3;
			}
			else if ((int)uVar13 < iVar11)
			{
				local_3b0 = 1;
			}
		LAB_6fad0b3e:
			wsprintfA(aCStack_2e4, "%ld", uVar16);
			bVar2 = true;
			break;
		default:
			goto switchD_6fad0a33_caseD_ffffffff;
		case 0xd:
			STR_GroupUintDigits(aUStack_164, uVar13, 0x80);
			iVar19 = *(int*)(byte_6FB78124 + iVar6) + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
			iVar20 = *(int*)(byte_6FB78120 + iVar6) + dword_6FBBA748;
			iVar11 = (*(int*)(byte_6FB78128 + iVar6) - iVar20) + 1 + dword_6FBBA748;
			goto LAB_6fad0e30;
		case 0x1e:
			pDStack_39c = (D2DifficultyLevelsTxt*)STATLIST_GetUnitBaseStat(pUnit, 0xc, 0);
			if (pUnit == nullptr)
			{
				iVar11 = -1;
			}
			else
			{
				iVar11 = pUnit->dwClassId;
			}
			pDVar14 = (D2DifficultyLevelsTxt*)DATATBLS_GetMaxLevel(iVar11);
			if (pDStack_39c != pDVar14)
			{
				uVar13 = DATATBLS_GetLevelThreshold(iVar11, (uint32_t)pDStack_39c);
			}
			STR_GroupUintDigits(aUStack_164, uVar13, 0x80);
			iVar19 = *(int*)(byte_6FB78124 + iVar6) + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
			iVar20 = *(int*)(byte_6FB78120 + iVar6) + dword_6FBBA748;
			iVar11 = (*(int*)(byte_6FB78128 + iVar6) - iVar20) + 1 + dword_6FBBA748;
		LAB_6fad0e30:
			iVar6 = D2Win_10121_GetTextWidth(aUStack_164);
			if (iVar6 < iVar11)
			{
				iVar20 = iVar20 + (iVar11 - iVar6 >> 1);
			}
			D2Win_10117_DrawText(aUStack_164, iVar20, iVar19, 0, 0);
			goto LAB_6fad0f74;
		case 0x1f:
			uVar16 = UNITS_GetDefense(pUnit);
			iVar11 = STATES_CheckStateMaskArmBlueOnUnit(pUnit);
			if (iVar11 != 0)
			{
				local_3b0 = 3;
			}
			if (((pUnit->pInventory != nullptr) &&
			        (iVar11 = INVENTORY_GetEquippedShield(pUnit->pInventory, nullptr), iVar11 != 0)) &&
			    (iVar11 = STATES_CheckState(pUnit, 0x65), iVar11 != 0))
			{
				local_3b0 = 3;
			}
			iVar11 = STATES_CheckStateMaskArmRedOnUnit(pUnit);
			if (iVar11 != 0)
			{
				local_3b0 = 1;
			}
			wsprintfA(aCStack_2e4, "%ld", uVar16);
			if ((999 < (int)uVar16) || (DVar10 = STRTABLE_GetLanguage(), DVar10 == LANGUAGE_JAPANESE))
			{
				bVar2 = true;
			}
			break;
		case 0x25:
		case 0x27:
		case 0x29:
		case 0x2b:
		case 0x2d:
			bVar4 = sub_6FAAC090();
			pDStack_39c = DATATBLS_GetDifficultyLevelsTxtRecord((uint32_t)bVar4);
			iVar11 = 0;
			switch ((&dword_6FB7812C)[uStack_3a8 * 4])
			{
			case 0x25:
				iVar11 = 0x26;
				break;
			default:
				goto switchD_6fad0b84_caseD_26;
			case 0x27:
				iVar11 = STATES_CheckStateMaskRFBlueOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 3;
				}
				iVar11 = STATES_CheckStateMaskRFRedOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 1;
				}
				iVar11 = 0x28;
				break;
			case 0x29:
				iVar11 = STATES_CheckStateMaskRLBlueOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 3;
				}
				iVar11 = STATES_CheckStateMaskRLRedOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 1;
				}
				iVar11 = 0x2a;
				break;
			case 0x2b:
				iVar11 = STATES_CheckStateMaskRCBlueOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 3;
				}
				iVar11 = STATES_CheckStateMaskRCRedOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 1;
				}
				iVar11 = 0x2c;
				break;
			case 0x2d:
				iVar11 = STATES_CheckStateMaskRPBlueOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 3;
				}
				iVar11 = STATES_CheckStateMaskRPRedOnUnit(pUnit);
				if (iVar11 != 0)
				{
					local_3b0 = 1;
				}
				iVar11 = 0x2e;
			}
			iVar11 = STATLIST_UnitGetStatValue(pUnit, iVar11, 0);
		switchD_6fad0b84_caseD_26:
			iVar19 = sub_6FAAC080();
			if (iVar19 == 0)
			{
				cVar5 = sub_6FAAC090();
				if (cVar5 == '\x01')
				{
					uVar13 = uVar13 - 0x14;
				}
				else if (cVar5 == '\x02')
				{
					uVar13 = uVar13 - 0x32;
				}
			}
			else
			{
				uVar13 = uVar13 + pDStack_39c->dwResistPenalty;
			}
			uVar16 = iVar11 + 0x4b;
			if (0x5e < (int)uVar16)
			{
				uVar16 = 0x5f;
			}
			if ((int)uVar13 < -99)
			{
				uVar13 = 0xffffff9c;
			}
			if (((int)uVar13 < (int)uVar16) || (uVar13 = uVar16, local_3b0 == 3))
			{
				uVar16 = uVar13;
				if ((int)uVar13 < 0)
				{
					local_3b0 = 1;
				}
			}
			else
			{
				local_3b0 = 4;
			}
			goto LAB_6fad0e8c;
		}
	LAB_6fad0e95:
		Unicode::win2Unicode(aUStack_164, aCStack_2e4, 0x80);
		uStack_66 = 0;
		FVar12 = NUM_FONTS;
		if ((bVar2) &&
		    ((999 < (int)uVar16 ||
		        (D2Win_10131_GetTextDimensions(aUStack_164, &iStack_394, &iStack_340),
		            *(int*)(byte_6FB78128 + iVar6) - *(int*)(byte_6FB78120 + iVar6) <= iStack_394))))
		{
			FVar12 = D2Win_10127_SetFont(D2FONT_FONT8);
		}
		iVar19 = *(int*)(byte_6FB78124 + iVar6) + dword_6FBBA74C + -0x1e0 + gnScreenHeight;
		iVar20 = *(int*)(byte_6FB78120 + iVar6) + dword_6FBBA748;
		iVar11 = (*(int*)(byte_6FB78128 + iVar6) - iVar20) + 1 + dword_6FBBA748;
		iVar6 = D2Win_10121_GetTextWidth(aUStack_164);
		if (iVar6 < iVar11)
		{
			iVar20 = iVar20 + (iVar11 - iVar6 >> 1);
		}
		D2Win_10117_DrawText(aUStack_164, iVar20, iVar19, local_3b0, 0);
		if (FVar12 != NUM_FONTS)
		{
			D2Win_10127_SetFont(FVar12);
		}
	LAB_6fad0f74:
		uStack_3a8 = uStack_3a8 + 1;
		if (0x11 < uStack_3a8)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FAD1010
int __fastcall sub_6FAD1010(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t nItemType;
	D2UnitStrc* local_10c;
	D2UnitStrc* local_108;
	D2StatStrc local_100[32];

	iVar4 = 0;
	if (pUnit == nullptr)
	{
		return 0;
	}
	pInventory = pUnit->pInventory;
	local_10c = nullptr;
	local_108 = nullptr;
	if (pInventory != nullptr)
	{
		local_10c = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
		local_108 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	}
	iVar2 = STATLIST_CopyStats(pUnit, 0x15c, local_100, 0x20);
	iVar5 = 0;
	if (0 < iVar2)
	{
		do
		{
			iVar1 = local_100[iVar5].nValue;
			nItemType = (uint32_t) * (uint16_t*)(local_100 + iVar5);
			if (nItemType == 0)
			{
			LAB_6fad10a9:
				iVar4 = iVar1;
			}
			else if (local_108 == nullptr)
			{
			LAB_6fad1092:
				if (local_10c != nullptr)
				{
					iVar3 = ITEMS_CheckItemTypeId(local_10c, nItemType);
					if (iVar3 != 0)
						goto LAB_6fad10a5;
				}
			}
			else
			{
				iVar3 = ITEMS_CheckItemTypeId(local_108, nItemType);
				if (iVar3 == 0)
					goto LAB_6fad1092;
			LAB_6fad10a5:
				if (iVar4 < iVar1)
					goto LAB_6fad10a9;
			}
			iVar5 = iVar5 + 1;
		} while (iVar5 < iVar2);
	}
	return iVar4;
}

//D2Client.0x6FAD10D0
D2DifficultyLevelsTxt* __fastcall sub_6FAD10D0(int a1)
{
	int iVar1;
	uint8_t bVar2;
	char cVar3;
	D2UnitStrc* pUnit;
	int iVar5;
	D2DifficultyLevelsTxt* pDVar6;
	int iVar7;
	int nLevel;
	D2MonStatsInitStrc* pDVar8;
	uint32_t nDifficulty;
	short nFlags;
	D2MonStatsInitStrc local_38;
	uint32_t uVar4;

	if (a1 == 0)
	{
		return nullptr;
	}
	pUnit = CUNIT_GetPlayer();
	bVar2 = sub_6FAAC090();
	uVar4 = (uint32_t)bVar2;
	D2_ASSERT(2 >= uVar4);
	iVar5 = sub_6FAB5A70();
	if (((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar5)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar5 * 0x1a8, iVar1 == 0))
	{
		FOG_DisplayAssert("ptStats", __FILE__, __LINE__);
		exit(-1);
	}
	pDVar8 = &local_38;
	for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar8->nMinHP = 0;
		pDVar8 = (D2MonStatsInitStrc*)&pDVar8->nMaxHP;
	}
	pDVar8 = &local_38;
	nFlags = 2;
	nLevel = (int)*(short*)(iVar1 + 0xaa + uVar4 * 2);
	nDifficulty = uVar4;
	iVar7 = sub_6FAAC060();
	DATATBLS_CalculateMonsterStatsByLevel(iVar5, iVar7, nDifficulty, nLevel, nFlags, pDVar8);
	if (*(char*)(iVar1 + 0x4c) != '\x01')
	{
		iVar5 = sub_6FAAC080();
		if (iVar5 == 0)
		{
			cVar3 = sub_6FAAC090();
			if (cVar3 != '\0')
			{
				local_38.nAC = (local_38.nAC * 10) / 0xc;
			}
		}
	}
	if (((pUnit != nullptr) && (pUnit->dwUnitType == 0)) &&
	    ((iVar5 = pUnit->dwClassId, -1 < iVar5 &&
	                                    ((iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) &&
	                                        (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar5 * 0xc4, iVar5 != 0))))))
	{
		a1 = *(int*)(iVar5 + 0x3c) + a1;
	}
	if (local_38.nAC < 0)
	{
		a1 = a1 - local_38.nAC;
		local_38.nAC = 0;
	}
	if (a1 < 0)
	{
		local_38.nAC = local_38.nAC - a1;
		a1 = 0;
	LAB_6fad1231:
		if (local_38.nAC == 0)
		{
			iVar5 = 100;
			goto LAB_6fad124b;
		}
	}
	else if (a1 == 0)
		goto LAB_6fad1231;
	iVar5 = (a1 * 100) / (local_38.nAC + a1);
LAB_6fad124b:
	iVar7 = STATLIST_UnitGetStatValue(pUnit, 0xc, 0);
	pDVar6 = (D2DifficultyLevelsTxt*)((iVar7 * iVar5 * 2) / (*(short*)(iVar1 + 0xaa + uVar4 * 2) + iVar7));
	if ((int)pDVar6 < 5)
	{
		return (D2DifficultyLevelsTxt*)0x5;
	}
	if (0x5f < (int)pDVar6)
	{
		pDVar6 = (D2DifficultyLevelsTxt*)0x5f;
	}
	return pDVar6;
}

//D2Client.0x6FAD1290
void __cdecl sub_6FAD1290(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pUnit;
	int iVar1;
	int* piVar2;
	D2GameResolutionMode DVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;

	uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if ((((dword_6FBBA748 + 0x80 <= (int)uVar5) && ((int)uVar5 <= dword_6FBBA748 + 0xa0)) &&
	        (dword_6FBBA74C + -0x5c + gnScreenHeight <= (int)uVar6)) &&
	    ((int)uVar6 <= dword_6FBBA74C + -0x3c + gnScreenHeight))
	{
		dword_6FBB1A4C = 1;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if (((dword_6FBBA748 <= (int)uVar5) && ((int)uVar5 <= gnScreenWidth / 2 + -1)) &&
	    ((dword_6FBBA74C <= (int)uVar6 && ((int)uVar6 <= dword_6FBBA74C + -0x31 + gnScreenHeight))))
	{
		pUnit = CUNIT_GetPlayer();
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
		if (iVar1 != 0)
		{
			iVar1 = 0;
			piVar2 = (int*)("u");
			do
			{
				iVar4 = piVar2[1] + dword_6FBBA74C + gnScreenHeight;
				if ((((iVar4 + -0x1f6 < (int)uVar6) && ((int)uVar6 < iVar4 + -0x1e0)) &&
				        (*piVar2 + dword_6FBBA748 < (int)uVar5)) &&
				    ((int)uVar5 < *piVar2 + dword_6FBBA748 + 0x28))
				{
					*(uint32_t*)((int)&dword_6FB78248 + iVar1 * 0xe) = 1;
					sub_6FB57480((int)pSMSGHANDLER_PARAMS);
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					sub_6FB55820(5, nullptr, 0.0, 0.0, 0);
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
				piVar2 = (int*)((int)piVar2 + 0xe);
				iVar1 = iVar1 + 1;
			} while ((int)piVar2 < (int)"%ld");
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	DVar3 = D2GFX_GetResolutionMode();
	if (DVar3 == NUM_GAME_RESOLUTIONS)
	{
		iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
		if (((iVar1 == 0) && ((int)(uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam <= gnScreenWidth / 2)) &&
		    ((int)(uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2) < gnScreenHeight + -0x2f))
		{
			iVar1 = sub_6FB57CC0();
			if (iVar1 == 6)
			{
				sub_6FB23A40();
			}
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAD1470
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD1470(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	SHORT SVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	int* piVar3;
	int iVar4;
	D2GameResolutionMode DVar5;
	int iVar6;
	int extraout_ECX;
	uint32_t uVar7;
	uint32_t uVar8;
	int iStack_8;

	uVar8 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar7 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	sub_6FB57500((int)pSMSGHANDLER_PARAMS);
	dword_6FBB1A4C = 0;
	if ((((dword_6FBBA748 + 0x80 <= (int)uVar8) && ((int)uVar8 <= dword_6FBBA748 + 0xa0)) &&
	        (dword_6FBBA74C + -0x5c + gnScreenHeight <= (int)uVar7)) &&
	    ((int)uVar7 <= dword_6FBBA74C + -0x3c + gnScreenHeight))
	{
		sub_6FB23260(2, 1, 0);
		return;
	}
	if ((((int)uVar8 < dword_6FBBA748) || (gnScreenWidth / 2 + -1 < (int)uVar8)) ||
	    (((int)uVar7 < dword_6FBBA74C || (dword_6FBBA74C + -0x31 + gnScreenHeight < (int)uVar7))))
	{
		DVar5 = D2GFX_GetResolutionMode();
		if (((DVar5 == NUM_GAME_RESOLUTIONS) && (iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS), iVar4 == 0)) &&
		    (((int)(uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam <= gnScreenWidth / 2 &&
		        ((int)(uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2) < gnScreenHeight + -0x2f))))
		{
			iVar4 = sub_6FB57CC0();
			if (iVar4 == 6)
			{
				sub_6FB23A40();
			}
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	pUnit = CUNIT_GetPlayer();
	iVar2 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
	iVar6 = dword_6FBBA74C;
	iVar4 = gnScreenHeight;
	if (iVar2 != 0)
	{
		iStack_8 = 0;
		piVar3 = (int*)("i");
		do
		{
			iVar2 = iVar6 + iVar4 + *piVar3;
			piVar3[1] = 0;
			if ((((iVar2 + -0x1f6 < (int)uVar7) && ((int)uVar7 < iVar2 + -0x1e0)) &&
			        (piVar3[-1] + dword_6FBBA748 < (int)uVar8)) &&
			    ((int)uVar8 < piVar3[-1] + dword_6FBBA748 + 0x28))
			{
				iVar4 = STATLIST_UnitGetStatValue(pUnit, 4, 0);
				SVar1 = GetKeyState(0x10);
				if (SVar1 < 0)
				{
					if (iVar4 == 0)
						goto LAB_6fad1619;
				}
				else
				{
					iVar4 = 1;
				}
				iVar6 = iStack_8 * 7;
				do
				{
					iVar2 = iVar4;
					if (0x1f < iVar4)
					{
						iVar2 = 0x20;
					}
					iVar4 = iVar4 - iVar2;
					sub_6FAAD990(CONCAT31((int32_t)((uint32_t)iVar6 >> 8), 0x3a),
					    ((short)iVar2 + -1) * 0x100 | *(uint16_t*)(byte_6FB7824C + iStack_8 * 0xe));
					iVar6 = extraout_ECX;
				} while (iVar4 != 0);
			LAB_6fad1619:
				sub_6FAABF60();
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			piVar3 = (int*)((int)piVar3 + 0xe);
			iStack_8 = iStack_8 + 1;
		} while ((int)piVar3 < (int)"nDifficultyLevel < NUM_DIFFICULTY_LEVELS");
	}
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD16C0
void __cdecl sub_6FAD16C0()
{
	byte_6FBB1A44 = 0;
}

//D2Client.0x6FAD16D0
void __cdecl sub_6FAD16D0()
{
	byte_6FBB1A44 = 1;
}

//D2Client.0x6FAD16E0
void __cdecl sub_6FAD16E0()
{
	Unicode* a1;
	int iVar1;
	uint32_t uVar2;

	uVar2 = 0;
	do
	{
		a1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)&word_6FB7801C + uVar2)));
		iVar1 = Unicode::strlen(a1);
		*(int*)((int)dword_6FB7801E + uVar2) = iVar1;
		uVar2 = uVar2 + 0x12;
	} while (uVar2 < 0x10e);
}

//D2Client.0x6FAD1710
void __cdecl sub_6FAD1710()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&word_6FBB1A58;
	iVar1 = 0x101;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD1730
void __cdecl sub_6FAD1730()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&dword_6FBB1CA8;
	iVar1 = 0x808;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD1750
void __cdecl sub_6FAD1750()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB2CB8;
	iVar1 = 0x20;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD1770
void __cdecl sub_6FAD1770()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB1C60;
	iVar1 = 0x20;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD1790
void __cdecl sub_6FAD1790(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	HWND__* pHVar1;
	HIMC pHVar2;
	DWORD dwBufLen;
	int iVar3;
	int iVar4;
	BOOL BVar5;
	uint32_t dwBufLen_00;
	LONG LVar6;
	int iVar7;
	Unicode* pUVar8;
	CHAR* pCVar9;
	Unicode aUStack_108[31];
	uint16_t uStack_ca;
	CHAR local_c8[199];
	uint8_t uStack_1;

	pCVar9 = local_c8;
	for (iVar7 = 0x32; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pCVar9[0] = '\0';
		pCVar9[1] = '\0';
		pCVar9[2] = '\0';
		pCVar9[3] = '\0';
		pCVar9 = pCVar9 + 4;
	}
	pHVar1 = WINDOW_GetWindow();
	pHVar2 = ImmGetContext((HWND)pHVar1);
	if (pHVar2 != (HIMC)0x0)
	{
		if ((pSMSGHANDLER_PARAMS->lParam & 0x800U) != 0)
		{
			dwBufLen = ImmGetCompositionStringA(pHVar2, 0x800, (LPVOID)0x0, 0);
			if (199 < dwBufLen)
			{
				dwBufLen = 199;
			}
			ImmGetCompositionStringA(pHVar2, 0x800, local_c8, dwBufLen);
			uStack_1 = 0;
			MultiByteToWideChar(0, 1, local_c8, -1, (LPWSTR)aUStack_108, 0x20);
			uStack_ca = 0;
			iVar7 = Unicode::strlen(aUStack_108);
			iVar3 = Unicode::strlen((Unicode*)&byte_6FBB1C60);
			iVar4 = Unicode::strlen((Unicode*)&word_6FBB1A58);
			if (iVar3 + iVar4 < 0x7f)
			{
				Unicode::strcat((Unicode*)&word_6FBB1A58, (Unicode*)&byte_6FBB1C60);
				iVar3 = Unicode::strlen((Unicode*)&byte_6FBB1C60);
				dword_6FBB2D04 = dword_6FBB2D04 + iVar3;
			}
			iVar3 = Unicode::strlen((Unicode*)&word_6FBB1A58);
			if (iVar3 + iVar7 < 0x7f)
			{
				Unicode::strcat((Unicode*)&word_6FBB1A58, aUStack_108);
				dword_6FBB2D04 = dword_6FBB2D04 + iVar7;
			}
			byte_6FBB1C60 = 0;
			byte_6FBB2CB8 = 0;
		}
		if ((pSMSGHANDLER_PARAMS->lParam & 8) != 0)
		{
			BVar5 = ImmGetOpenStatus(pHVar2);
			if (BVar5 != 0)
			{
				dwBufLen_00 = ImmGetCompositionStringA(pHVar2, 8, (LPVOID)0x0, 0);
				if (dwBufLen_00 != 0)
				{
					pCVar9 = local_c8;
					for (iVar7 = 0x32; iVar7 != 0; iVar7 = iVar7 + -1)
					{
						pCVar9[0] = '\0';
						pCVar9[1] = '\0';
						pCVar9[2] = '\0';
						pCVar9[3] = '\0';
						pCVar9 = pCVar9 + 4;
					}
					pUVar8 = aUStack_108;
					for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1)
					{
						*(uint32_t*)pUVar8 = 0;
						pUVar8 = pUVar8 + 2;
					}
					if (199 < dwBufLen_00)
					{
						dwBufLen_00 = 199;
					}
					LVar6 = ImmGetCompositionStringA(pHVar2, 8, local_c8, dwBufLen_00);
					if (0 < LVar6)
					{
						uStack_1 = 0;
						MultiByteToWideChar(0, 1, local_c8, -1, (LPWSTR)aUStack_108, 0x20);
						iVar7 = Unicode::strlen(aUStack_108);
						if (iVar7 < 0x1f)
						{
							aUStack_108[iVar7].ch = 0;
						}
						else
						{
							uStack_ca = 0;
						}
						if (iVar7 < 0x20)
						{
							Unicode::strcpy((Unicode*)&byte_6FBB2CB8, aUStack_108);
						}
						else
						{
							Unicode::strncpy((Unicode*)&byte_6FBB2CB8, aUStack_108, 0x1f);
							byte_6FBB2CF6 = 0;
							sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
						}
					}
				}
			}
		}
		pHVar1 = WINDOW_GetWindow();
		ImmReleaseContext((HWND)pHVar1, pHVar2);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD19B0
void __cdecl sub_6FAD19B0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	byte_6FBB2CF8 = 1;
	byte_6FBB2CB8 = 0;
	byte_6FBB1C60 = 0;
	if (byte_6FBB2CFC == 9)
	{
		dword_6FBB2D0C = 4;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if (byte_6FBB2CFC == 8)
	{
		dword_6FBB2D0C = 5;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD1A20
void __cdecl sub_6FAD1A20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	byte_6FBB2CB8 = 0;
	byte_6FBB1C60 = 0;
	dword_6FBB2D08 = -2;
	if (byte_6FBB2CFC == 6)
	{
		byte_6FBB2CF8 = 0;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

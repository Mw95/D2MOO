#include "UI/Party.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/Roster.h"
#include "UI/Automap.h"
#include "UI/Inv.h"
#include "UI/QuestLog.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/PlayerList.h"

//D2Client.0x6FB7CFE8
uint8_t byte_6FB7CFE8[8] = {0x83, 0x27, 0x7F, 0x27, 0x81, 0x27, 0x7E, 0x27};
//D2Client.0x6FB7CFF0
uint8_t byte_6FB7CFF0[8] = {0x83, 0x27, 0x80, 0x27, 0x82, 0x27, 0x7E, 0x27};
//D2Client.0x6FB7CFF8
uint8_t byte_6FB7CFF8[8] = {0x89, 0x27, 0x87, 0x27, 0x85, 0x27, 0x84, 0x27};
//D2Client.0x6FB7D000
uint8_t byte_6FB7D000[7] = {0x89, 0x27, 0x88, 0x27, 0x86, 0x27, 0x84};
//D2Client.0x6FB7D007
uint32_t dword_6FB7D007 = 0x5C3A4327;
//D2Client.0x6FB7D044
uint32_t dword_6FB7D044 = 0x2E2E2E;
//D2Client.0x6FB7D048
uint32_t dword_6FB7D048 = 0x2E2E2E2E;
//D2Client.0x6FB7D04C
uint8_t byte_6FB7D04C;
//D2Client.0x6FB7D0F0
uint8_t byte_6FB7D0F0[4];
//D2Client.0x6FB7D0F4
int32_t dword_6FB7D0F4;
//D2Client.0x6FB7D0F8
uint8_t byte_6FB7D0F8;
//D2Client.0x6FB7D0FC
int32_t dword_6FB7D0FC;
//D2Client.0x6FB7D100
uint8_t byte_6FB7D100;
//D2Client.0x6FB7D104
uint8_t byte_6FB7D104;
//D2Client.0x6FB7D108
uint8_t byte_6FB7D108;
//D2Client.0x6FB7D10C
uint8_t byte_6FB7D10C;
//D2Client.0x6FB7D110
uint8_t byte_6FB7D110;
//D2Client.0x6FB7D114
uint8_t byte_6FB7D114;
//D2Client.0x6FB7D118
uint8_t byte_6FB7D118;
//D2Client.0x6FB7D11C
uint8_t byte_6FB7D11C;
//D2Client.0x6FB7D120
uint8_t byte_6FB7D120;
//D2Client.0x6FB7D124
uint8_t byte_6FB7D124;
//D2Client.0x6FB7D128
uint8_t byte_6FB7D128;
//D2Client.0x6FB7D12C
uint8_t byte_6FB7D12C;
//D2Client.0x6FBB5EF8
uint32_t dword_6FBB5EF8;
//D2Client.0x6FBB5F14
uint32_t tbl_6FBB5F14[1];
//D2Client.0x6FBB5F18
int32_t dword_6FBB5F18;
//D2Client.0x6FBB5F1C
D2CellFileStrc* gpCellFile_6FBB5F1C;
//D2Client.0x6FBB5F20
D2CellFileStrc* gpCellFile_6FBB5F20;
//D2Client.0x6FBB5F24
D2CellFileStrc* gpCellFile_6FBB5F24;
//D2Client.0x6FBB5F28
D2CellFileStrc* gpCellFile_6FBB5F28;
//D2Client.0x6FBB5F2C
D2CellFileStrc* gpCellFile_6FBB5F2C;
//D2Client.0x6FBB5F34
uint32_t dword_6FBB5F34;
//D2Client.0x6FBB5F38
uint8_t byte_6FBB5F38;
//D2Client.0x6FBB5F3C
int32_t dword_6FBB5F3C;
//D2Client.0x6FBB5F81
uint8_t byte_6FBB5F81;
//D2Client.0x6FBB5F85
uint8_t byte_6FBB5F85;
//D2Client.0x6FBB5F89
uint8_t byte_6FBB5F89;
//D2Client.0x6FBB5F8D
uint8_t byte_6FBB5F8D;
//D2Client.0x6FBB6070
uint8_t tbl_6FBB6070[602];

//D2Client.0x6FB01C70
void __cdecl sub_6FB01C70()
{
	void* pvVar1;
	void* pFree;

	pFree = (void*)dword_6FBB5F18;
	if (dword_6FBB5F18 != 0)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree + 0xcd);
			FOG_Free(pFree, (const char*)(dword_6FB7D007 + 1), 0x108, 0);
			pFree = pvVar1;
		} while (pvVar1 != nullptr);
	}
	dword_6FBB5F18 = 0;
}

//D2Client.0x6FB01CB0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB01CB0()
{
	char cVar1;
	void* pvVar2;
	int iVar3;
	int iVar4;
	D2CellFileStrc* pDVar5;
	uint16_t uVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	char* pcVar11;
	uint16_t extraout_var;
	void* pFree;
	int iVar12;
	uint32_t* puVar13;
	char* pcVar14;
	int local_c;
	int iStack_4;

	pFree = (void*)dword_6FBB5F18;
	if (dword_6FBB5F18 != 0)
	{
		do
		{
			pvVar2 = *(void**)((int)pFree + 0xcd);
			FOG_Free(pFree, (const char*)(dword_6FB7D007 + 1), 0x108, 0);
			pFree = pvVar2;
		} while (pvVar2 != nullptr);
	}
	dword_6FBB5F18 = 0;
	local_c = 0x5a;
	iVar7 = sub_6FAAF5B0(0);
	iVar7 = sub_6FAAF5B0(iVar7);
	for (iStack_4 = 0; (iVar4 = dword_6FBB5F18, iVar7 != 0 || (8 < iStack_4)); iStack_4 = iStack_4 + 1)
	{
		puVar8 = (uint32_t*)FOG_Alloc(0xd1, (const char*)(dword_6FB7D007 + 1), 0x14d, 0);
		puVar13 = puVar8;
		for (iVar12 = 0x34; iVar12 != 0; iVar12 = iVar12 + -1)
		{
			*puVar13 = 0;
			puVar13 = puVar13 + 1;
		}
		*(uint8_t*)puVar13 = 0;
		*(int*)((int)puVar8 + 0xc9) = local_c + 0xd;
		uVar9 = sub_6FAAFF30(iVar7);
		puVar8[3] = (uint32_t)(gpCellFile_6FBB5F20);
		*puVar8 = 1;
		puVar8[1] = 0xbe;
		puVar8[2] = local_c;
		puVar8[4] = 0;
		puVar8[5] = 0;
		puVar8[6] = uVar9;
		iVar12 = sub_6FAAFEF0(iVar7);
		pDVar5 = gpCellFile_6FBB5F24;
		puVar8[8] = 0;
		puVar8[0xb] = (uint32_t)(pDVar5);
		puVar8[9] = 0xe;
		puVar8[10] = local_c + 7;
		puVar8[0xc] = (-(uint32_t)(iVar12 != 0) & 2) + 4;
		puVar8[0xd] = 1;
		puVar8[0xe] = 0;
		uVar10 = sub_6FAAFE30(iVar7);
		puVar8[0x13] = (uint32_t)(gpCellFile_6FBB5F24);
		puVar8[0x10] = 0;
		puVar8[0x11] = 0xf5;
		puVar8[0x12] = local_c;
		puVar8[0x14] = (-(uint32_t)(uVar10 != 0) & 2) + 0xc;
		puVar8[0x15] = 2;
		puVar8[0x16] = 0;
		uVar10 = sub_6FAAFE70(iVar7);
		pDVar5 = gpCellFile_6FBB5F24;
		puVar8[0x18] = 0;
		puVar8[0x1b] = (uint32_t)(pDVar5);
		puVar8[0x19] = 0x10a;
		puVar8[0x1a] = local_c;
		puVar8[0x1c] = -(uint32_t)(uVar10 != 0) & 2;
		puVar8[0x1d] = 3;
		puVar8[0x1e] = 0;
		uVar10 = sub_6FAAFEB0(iVar7);
		pDVar5 = gpCellFile_6FBB5F24;
		puVar8[0x20] = 0;
		puVar8[0x21] = 0x11f;
		puVar8[0x22] = local_c;
		puVar8[0x23] = (uint32_t)(pDVar5);
		puVar8[0x24] = (-(uint32_t)(uVar10 != 0) & 2) + 8;
		puVar8[0x25] = 4;
		puVar8[0x26] = 0;
		uVar9 = sub_6FAB0870(iVar7);
		*(uint32_t*)((int)puVar8 + 0xc5) = uVar9;
		pcVar11 = (char*)sub_6FAAF5D0(iVar7);
		pcVar14 = (char*)(puVar8 + 0x28);
		do
		{
			cVar1 = *pcVar11;
			pcVar11 = pcVar11 + 1;
			*pcVar14 = cVar1;
			pcVar14 = pcVar14 + 1;
		} while (cVar1 != '\0');
		uVar9 = sub_6FAAFD50(iVar7);
		*(uint32_t*)((int)puVar8 + 0xb9) = uVar9;
		uVar6 = sub_6FAAFD40(iVar7);
		*(uint32_t*)((int)puVar8 + 0xbd) = D2C_ZEXT(uVar6);
		uVar9 = sub_6FAB0BB0(iVar7);
		*(uint32_t*)((int)puVar8 + 0xc1) = uVar9;
		if (iVar4 != 0)
		{
			iVar12 = *(int*)(iVar4 + 0xcd);
			while (iVar3 = iVar12, iVar3 != 0)
			{
				iVar4 = iVar3;
				iVar12 = *(int*)(iVar3 + 0xcd);
			}
			*(uint32_t**)(iVar4 + 0xcd) = puVar8;
			puVar8 = (uint32_t*)dword_6FBB5F18;
		}
		dword_6FBB5F18 = (int)puVar8;
		local_c = local_c + 0x26;
		iVar7 = sub_6FAAF5B0(iVar7);
	}
}

//D2Client.0x6FB01F10
void __cdecl sub_6FB01F10()
{
	char cVar1;
	bool bVar2;
	short sVar3;
	short sVar4;
	short sVar5;
	D2UnitStrc* pDVar6;
	char* a1;
	Unicode* pUVar7;
	int iVar8;
	int iVar9;
	int iVar10;
	uint32_t uVar11;
	Font nFontSize;
	int iVar12;
	char* pcVar13;
	uint32_t uVar14;
	D2GfxDataStrc* pDVar15;
	D2SkillsTxt* pDVar16;
	int iStack_68;
	uint8_t auStack_5c[20];
	D2GfxDataStrc local_48;

	pDVar15 = &local_48;
	for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
	{
		pDVar15->pCurrentCell = nullptr;
		pDVar15 = (D2GfxDataStrc*)&pDVar15->pCellFile;
	}
	local_48.pCellFile = gpCellFile_6FBB5F1C;
	local_48.nDirection = 0;
	local_48.nFrame = 0;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748, gnScreenHeight + -0xe0 + dword_6FBBA74C, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 1;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, gnScreenHeight + -0xe0 + dword_6FBBA74C, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 2;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748, gnScreenHeight + -0x30 + dword_6FBBA74C, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 3;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, gnScreenHeight + -0x30 + dword_6FBBA74C, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	pDVar6 = CUNIT_GetPlayer();
	if ((pDVar6 != nullptr) && (a1 = (char*)sub_6FAB0C00(pDVar6), a1 != nullptr))
	{
		uVar11 = 0xffffffff;
		pcVar13 = a1;
		do
		{
			if (uVar11 == 0)
				break;
			uVar11 = uVar11 - 1;
			cVar1 = *pcVar13;
			pcVar13 = pcVar13 + 1;
		} while (cVar1 != '\0');
		uVar11 = Unicode::unicodenwidth(a1, ~uVar11 - 1);
		uVar11 = uVar11 + 1;
		if (0xb < uVar11)
		{
			if (uVar11 < 0xe)
			{
				nFontSize = D2FONT_FONT8;
			}
			else
			{
				nFontSize = D2FONT_FONT6;
			}
			D2Win_10127_SetFont(nFontSize);
		}
		pUVar7 = (Unicode*)
		    FOG_Alloc(uVar11 * 2, (const char*)(dword_6FB7D007 + 1), 0x211, 0);
		Unicode::toUnicode(pUVar7, a1, uVar11);
		sub_6FACFCD0(dword_6FBBA748 + 0x14, 0x1f - dword_6FBBA74C, dword_6FBBA748 + 0xbe, pUVar7,
		    nullptr);
		D2Win_10127_SetFont(D2FONT_FONT8);
		FOG_Free(pUVar7, (const char*)(dword_6FB7D007 + 1), 0x21a, 0);
	}
	iVar10 = dword_6FBB5F18;
	iVar12 = 0x5a;
	memset(auStack_5c, 0, 2 * (10));
	iVar8 = sub_6FAAF5B0(0);
	sVar3 = sub_6FAAFDA0(iVar8);
	iVar8 = sub_6FAAF5B0(iVar8);
	for (iStack_68 = 0; ((iVar10 != 0 && (uVar14 = 0, iVar8 != 0)) && (iStack_68 < 8));
	     iStack_68 = iStack_68 + 1)
	{
		bVar2 = false;
		sVar4 = sub_6FAAFDA0(iVar8);
		sVar5 = sub_6FAAFDA0(iVar8);
		if (sVar5 != -1)
		{
			if (sVar3 == sVar4)
			{
				uVar14 = 2;
				bVar2 = true;
			}
			else
			{
				uVar14 = 8;
			}
		}
		iVar9 = sub_6FAB1340(iVar8);
		if (iVar9 != 0)
		{
			uVar14 = 1;
		}
		D2Win_10127_SetFont(D2FONT_FONT8);
		sub_6FB02480((char*)(iVar10 + 0xa0), iVar12, uVar14, (uint32_t)(sVar4 != -1));
		sub_6FB025B0(*(uint32_t*)(iVar10 + 0xb9), iVar12 + 0xc, uVar14);
		sub_6FB02390(*(uint32_t*)(iVar10 + 0xbd), iVar12 + 0xc, uVar14);
		if ((bVar2) && (*(int*)(iVar10 + 0xc1) != 0))
		{
			sub_6FB028A0(iVar10, iVar12, uVar14);
		}
		sub_6FB02700(iVar10);
		sub_6FB02640(iVar8, *(uint32_t*)(iVar10 + 0x18), iVar12, (uint32_t)(sVar3 == sVar4), sVar4);
		iVar10 = *(int*)(iVar10 + 0xcd);
		iVar12 = iVar12 + 0x26;
		iVar8 = sub_6FAAF5B0(iVar8);
		D2Win_10127_SetFont(D2FONT_FONT16);
	}
	iVar10 = sub_6FAAF5B0(0);
	D2Win_10127_SetFont(D2FONT_FONT8);
	sVar3 = sub_6FAAFDA0(iVar10);
	if (sVar3 != -1)
	{
		sub_6FB02330(gpCellFile_6FBB5F20, 0xe3, 0x23, 0);
		pDVar16 = (D2SkillsTxt*)0x2;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1038));
		sub_6FACFCD0(dword_6FBBA748 + 0xe3, 0x21 - dword_6FBBA74C, dword_6FBBA748 + 0x118, pUVar7, pDVar16);
	}
	D2Win_10127_SetFont(D2FONT_FONT16);
	pDVar15 = &local_48;
	for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
	{
		pDVar15->pCurrentCell = nullptr;
		pDVar15 = (D2GfxDataStrc*)&pDVar15->pCellFile;
	}
	local_48.pCellFile = sub_6FB24110();
	local_48.nFrame = (dword_6FBB5F34 != 0) + 10;
	local_48.nDirection = 0;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x116, 0x1a5 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL,
	    nullptr);
	sub_6FB02B20();
	sub_6FB03110();
	sub_6FB029D0();
	iVar10 = sub_6FB02AC0(0x116, 0x1a5, 0x20, 0x20);
	if (iVar10 != 0)
	{
		iVar9 = 1;
		iVar12 = 0x182 - dword_6FBBA74C;
		iVar8 = 0;
		iVar10 = dword_6FBBA748 + 0x125;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x102f));
		D2Win_10129_DrawFramedText(pUVar7, iVar10, iVar12, iVar8, iVar9);
	}
}

//D2Client.0x6FB02330
void __fastcall sub_6FB02330(D2CellFileStrc* pCellFile2, int a2, int a3, uint32_t a4)
{
	int iVar1;
	D2GfxDataStrc* pDVar2;
	D2GfxDataStrc local_48;

	pDVar2 = &local_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar2->pCurrentCell = nullptr;
		pDVar2 = (D2GfxDataStrc*)&pDVar2->pCellFile;
	}
	local_48.nDirection = 0;
	local_48.nFrame = a4;
	local_48.pCellFile = pCellFile2;
	TEXTURE_CelDraw(&local_48, dword_6FBBA748 + a2, a3 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB02390
void __fastcall sub_6FB02390(uint32_t a1, int a2, int a3)
{
	Unicode* pUVar1;
	int iVar2;
	Unicode aUStack_140[10];
	Unicode local_12c[100];
	CHAR aCStack_64[100];

	iVar2 = 0x14;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd28));
	Unicode::strncpy(local_12c, pUVar1, iVar2);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
	Unicode::strcat(local_12c, pUVar1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	Unicode::strcat(local_12c, pUVar1);
	wsprintfA(aCStack_64, "%2u", a1);
	Unicode::win2Unicode(aUStack_140, aCStack_64, 9);
	Unicode::strcat(local_12c, aUStack_140);
	D2Win_10117_DrawText(local_12c, dword_6FBBA748 + 0x10a, a2 - dword_6FBBA74C, a3, 0);
}

//D2Client.0x6FB02480
void __fastcall sub_6FB02480(char* a1, int a2, int a3, int a4)
{
	Unicode* pUVar1;
	uint16_t* puVar2;
	int iVar3;
	uint32_t uStack_e0;
	uint8_t uStack_dc;
	Unicode aUStack_d8[6];
	int local_cc;
	Unicode local_c8[98];
	uint16_t auStack_4[2];

	pUVar1 = local_c8;
	iVar3 = 100;
	local_cc = a2;
	do
	{
		pUVar1 = pUVar1 + 1;
		iVar3 = iVar3 + -1;
	} while (iVar3 != 0);
	Unicode::toUnicode(local_c8, a1, 100);
	puVar2 = auStack_4 + 1;
	uStack_e0 = dword_6FB7D044;
	uStack_dc = 0;
	if (a4 == 0)
	{
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		if (iVar3 < 0x88)
			goto LAB_6fb02570;
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		while (0x87 < iVar3)
		{
			puVar2 = puVar2 + -1;
			*puVar2 = 0;
			iVar3 = D2Win_10121_GetTextWidth(local_c8);
		}
	}
	else
	{
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		if (iVar3 < 0x60)
			goto LAB_6fb02570;
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		while (0x5f < iVar3)
		{
			puVar2 = puVar2 + -1;
			*puVar2 = 0;
			iVar3 = D2Win_10121_GetTextWidth(local_c8);
		}
	}
	Unicode::toUnicode(aUStack_d8, (char*)&uStack_e0, 5);
	Unicode::strcat(local_c8, aUStack_d8);
LAB_6fb02570:
	D2Win_10117_DrawText(local_c8, dword_6FBBA748 + 0x24, (local_cc - dword_6FBBA74C) + -2, a3, 0);
}

//D2Client.0x6FB025B0
void __fastcall sub_6FB025B0(uint32_t a1, int a2, int a3)
{
	int nX;
	Unicode* wszText;
	short index;
	int nY;
	int bCentered;

	switch (a1)
	{
	case 0:
		index = 0x103a;
		break;
	case 1:
		index = 0x103b;
		break;
	case 2:
		index = 0x103d;
		break;
	case 3:
		index = 0x103e;
		break;
	case 4:
		index = 0x103c;
		break;
	case 5:
		index = 0x2771;
		break;
	case 6:
		index = 0x2772;
		break;
	default:
		goto switchD_6fb025b5_default;
	}
	bCentered = 0;
	nY = a2 - dword_6FBBA74C;
	nX = dword_6FBBA748 + 0x24;
	wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	D2Win_10117_DrawText(wszText, nX, nY, a3, bCentered);
switchD_6fb025b5_default:
}

//D2Client.0x6FB02640
void __fastcall sub_6FB02640(uint32_t a1, uint32_t a2, int a3, int a4, short a5)
{
	D2SkillsTxt* pDVar1;
	Unicode* pUVar2;
	short index;
	int iVar3;

	pDVar1 = nullptr;
	iVar3 = 0xbe;
	switch (a2)
	{
	case 0:
		index = 0x1036;
		break;
	case 1:
		if (a5 == -1)
		{
			return;
		}
		if (a4 == 0)
		{
			index = 0x1035;
			pDVar1 = (D2SkillsTxt*)0x8;
			iVar3 = 0xaf;
		}
		else
		{
			index = 0x1034;
			pDVar1 = (D2SkillsTxt*)0x2;
			iVar3 = 0x9b;
		}
		break;
	case 2:
		index = 0x1037;
		break;
	case 3:
		index = 0x1038;
		break;
	case 4:
		index = 0x13ef;
		break;
	default:
		D2Win_10127_SetFont(D2FONT_FONT8);
		return;
	}
	iVar3 = iVar3 + dword_6FBBA748;
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	sub_6FACFCD0(iVar3, (a3 - dword_6FBBA74C) + -2, iVar3 + 0x35, pUVar2, pDVar1);
}

//D2Client.0x6FB02700
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB02700(int a1)
{
	bool bVar1;
	uint8_t bVar2;
	uint16_t uVar3;
	D2UnitStrc* pUnit;
	uint32_t extraout_var;
	D2ActiveRoomStrc* pRoom;
	uint16_t extraout_var_01;
	uint32_t extraout_var_00;
	int iVar4;
	uint32_t uVar5;
	int* piVar6;
	D2GfxDataStrc* pDVar7;
	int local_50;
	D2GfxDataStrc local_48;

	pUnit = CUNIT_GetPlayer();
	pDVar7 = &local_48;
	for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	local_48.nDirection = 0;
	piVar6 = (int*)(a1 + 8);
	local_50 = 5;
	do
	{
		if ((piVar6[3] != 0) || (piVar6[4] != 1))
		{
			local_48.pCellFile = (D2CellFileStrc*)piVar6[1];
			local_48.nFrame = piVar6[2];
			switch (piVar6[3])
			{
			case 1:
				if ((local_48.nFrame < 4) || (7 < local_48.nFrame))
				{
					local_48.nFrame = 4;
				}
				break;
			case 2:
				if ((local_48.nFrame < 0xc) || (0xf < local_48.nFrame))
				{
					local_48.nFrame = 0xc;
				}
				bVar2 = CLIENT_IsHardcore();
				if (D2C_ZEXT(bVar2) == 0)
					goto LAB_6fb027d3;
				break;
			case 3:
				if (3 < local_48.nFrame)
				{
					local_48.nFrame = 0;
				}
				break;
			case 4:
				if ((local_48.nFrame < 8) || (0xb < local_48.nFrame))
				{
					local_48.nFrame = 8;
				}
			}
			TEXTURE_CelDraw(&local_48, piVar6[-1] + dword_6FBBA748, *piVar6 - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
		}
	LAB_6fb027d3:
		if (piVar6[3] == 1)
		{
			bVar1 = false;
			pRoom = UNITS_GetRoom(pUnit);
			if ((pRoom == nullptr) || (iVar4 = DUNGEON_IsRoomInTown(pRoom), iVar4 == 0))
			{
				bVar1 = true;
			}
			if (*(int*)(a1 + 0xbd) < 9)
			{
				if (pUnit == nullptr)
				{
					uVar5 = 0xffffffff;
				}
				else
				{
					uVar5 = pUnit->dwUnitId;
				}
				uVar5 = sub_6FB4B900(uVar5, *(int*)(a1 + 0xc5), 8);
				if (uVar5 == 0)
				{
					bVar1 = true;
				}
			}
			iVar4 = sub_6FAAF5B0(0);
			uVar3 = sub_6FAAFD40(iVar4);
			if ((D2C_ZEXT(uVar3) < 9) || (bVar1))
			{
				byte_6FBB5F38 = D2Win_10034_MixRGB(0xff, 0, 0);
				sub_6FB5B0F0(piVar6[-1] + dword_6FBBA748, (*piVar6 - dword_6FBBA74C) + -0x13, 0x14, 0x14,
				    D2C_ZEXT(byte_6FBB5F38), (DrawMode)(1));
			}
		}
		piVar6 = piVar6 + 8;
		local_50 = local_50 + -1;
		if (local_50 == 0)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB028A0
void __fastcall sub_6FB028A0(int a1, int a2, int a3)
{
	uint16_t uVar1;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	uint16_t* puVar5;
	uint32_t uStack_218;
	uint8_t uStack_214;
	Unicode aUStack_210[3];
	uint16_t uStack_20a;
	int local_204;
	Unicode local_200[253];
	uint16_t auStack_6[3];

	pUVar2 = local_200;
	iVar4 = 0xff;
	local_204 = a2;
	do
	{
		pUVar2 = pUVar2 + 1;
		iVar4 = iVar4 + -1;
	} while (iVar4 != 0);
	pUVar2 = sub_6FB239F0(*(int*)(a1 + 0xc1));
	Unicode::strcpy(local_200, pUVar2);
	puVar5 = auStack_6 + 1;
	iVar4 = D2Win_10121_GetTextWidth(local_200);
	if (0x8c < iVar4)
	{
		iVar4 = Unicode::strlen(local_200);
		uVar1 = local_200[iVar4 + -1].ch;
		uStack_218 = dword_6FB7D048;
		uStack_214 = byte_6FB7D04C;
		Unicode::toUnicode(aUStack_210, (char*)&uStack_218, 5);
		uStack_20a = uVar1;
		iVar4 = D2Win_10121_GetTextWidth(aUStack_210);
		iVar3 = D2Win_10121_GetTextWidth(local_200);
		while (0x8b - iVar4 < iVar3)
		{
			puVar5 = puVar5 + -1;
			*puVar5 = 0;
			iVar3 = D2Win_10121_GetTextWidth(local_200);
		}
		Unicode::strcat(local_200, aUStack_210);
		a2 = local_204;
	}
	D2Win_10117_DrawText(local_200, dword_6FBBA748 + 0x7e, (a2 - dword_6FBBA74C) + 0xc, a3, 0);
}

//D2Client.0x6FB029D0
void __cdecl sub_6FB029D0()
{
	uint16_t uVar1;
	int iVar2;
	int iVar3;
	int* piVar4;
	uint32_t* puVar5;
	uint32_t* puVar6;
	D2GfxDataStrc* pDVar7;
	D2GfxDataStrc local_48;

	iVar2 = sub_6FAAF5B0(0);
	puVar5 = &dword_6FBB5EF8;
	for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar5 = 0xffff;
		puVar5 = puVar5 + 1;
	}
	if (iVar2 != 0)
	{
		puVar6 = &dword_6FBB5EF8;
		do
		{
			uVar1 = sub_6FAAFDA0(iVar2);
			*puVar6 = (uint32_t)uVar1;
			iVar2 = sub_6FAAF5B0(iVar2);
			puVar6 = puVar6 + 1;
		} while (iVar2 != 0);
	}
	iVar2 = 0x43;
	piVar4 = (int*)(&dword_6FBB5EF8);
	do
	{
		if ((piVar4[1] != *piVar4) && (*piVar4 != 0xffff))
		{
			pDVar7 = &local_48;
			for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				pDVar7->pCurrentCell = nullptr;
				pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
			}
			local_48.pCellFile = gpCellFile_6FBB5F2C;
			local_48.nDirection = 0;
			local_48.nFrame = 0;
			TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0xc, iVar2 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL,
			    nullptr);
			local_48.nFrame = 1;
			TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x10b, iVar2 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		piVar4 = piVar4 + 1;
		iVar2 = iVar2 + 0x26;
	} while ((int)piVar4 < (int)&tbl_6FBB5F14);
}

//D2Client.0x6FB02AC0
uint32_t __fastcall sub_6FB02AC0(int a1, int a2, int a3, int a4)
{
	int iVar1;
	int iVar2;

	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	if ((((dword_6FBBA748 + a1 <= iVar1) && (iVar1 <= dword_6FBBA748 + a1 + a3)) &&
	        ((a2 - dword_6FBBA74C) - a4 <= iVar2)) &&
	    (iVar2 <= a2 - dword_6FBBA74C))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB02B20
void __cdecl sub_6FB02B20()
{
	short sVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	Unicode* pUVar5;
	int iVar6;
	int nColor;
	int bCentered;
	int local_4b8;
	int iStack_4b4;
	Unicode aUStack_4b0[100];
	Unicode aUStack_3e8[100];
	Unicode aUStack_320[100];
	Unicode aUStack_258[100];
	Unicode aUStack_190[100];
	Unicode aUStack_c8[100];

	iVar6 = dword_6FBB5F18;
	local_4b8 = dword_6FBB5F18;
	iVar2 = sub_6FAAF5B0(0);
	byte_6FBB5F38 = D2Win_10034_MixRGB(0, 0, 0);
	sVar1 = sub_6FAAFDA0(iVar2);
	if (sVar1 != -1)
	{
		iVar3 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		if ((((dword_6FBBA748 + 0xe3 <= iVar3) && (iVar3 <= dword_6FBBA748 + 0x118)) &&
		        (0x18 - dword_6FBBA74C <= iVar4)) &&
		    (iVar4 <= 0x23 - dword_6FBBA74C))
		{
			sub_6FB03010(0x1018, 0, 0xd5, 0);
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1018));
			Unicode::strcpy(aUStack_4b0, pUVar5);
			iVar3 = D2Win_10121_GetTextWidth(aUStack_4b0);
			bCentered = 0;
			iVar4 = 0x37 - dword_6FBBA74C;
			nColor = 0;
			iVar3 = dword_6FBBA748 + (0xd5 - iVar3 / 2);
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1018));
			D2Win_10117_DrawText(pUVar5, iVar3, iVar4, nColor, bCentered);
		}
	}
	iStack_4b4 = sub_6FAAF5B0(iVar2);
	if (iVar6 != 0)
	{
		do
		{
			iVar2 = *(int*)(local_4b8 + 8);
			iVar6 = *(int*)(local_4b8 + 4);
			iVar3 = sub_6FB57BC0();
			iVar4 = sub_6FB57BD0();
			iVar6 = dword_6FBBA748 + iVar6;
			if (((iVar6 <= iVar3) && (iVar3 <= iVar6 + 0x35)) &&
			    ((iVar2 = iVar2 - dword_6FBBA74C, iVar2 + -0x14 <= iVar4 &&
			                                          ((iVar4 <= iVar2 && (*(int*)(local_4b8 + 0x14) == 0))))))
			{
				iVar6 = *(int*)(local_4b8 + 0x18);
				if (iVar6 == 0)
				{
					sub_6FB03010(0x1004, 0x1005, 0xda, 1);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1004));
					Unicode::strcpy(aUStack_4b0, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_4b0);
					iVar4 = 0;
					iVar2 = 0x32 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1004));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1005));
					Unicode::strcpy(aUStack_3e8, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_3e8);
					iVar4 = 0;
					iVar2 = 0x41 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1005));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
				}
				else if (iVar6 == 2)
				{
					sub_6FB03010(0x1006, 0x1007, 0xda, 1);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1006));
					Unicode::strcpy(aUStack_190, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_190);
					iVar4 = 0;
					iVar2 = 0x32 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1006));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1007));
					Unicode::strcpy(aUStack_320, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_320);
					iVar4 = 0;
					iVar2 = 0x41 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1007));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
				}
				else if (iVar6 == 4)
				{
					sub_6FB03010(0x1008, 0x1009, 0xda, 1);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1008));
					Unicode::strcpy(aUStack_258, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_258);
					iVar4 = 0;
					iVar2 = 0x32 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1008));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1009));
					Unicode::strcpy(aUStack_c8, pUVar5);
					iVar6 = D2Win_10121_GetTextWidth(aUStack_c8);
					iVar4 = 0;
					iVar2 = 0x41 - dword_6FBBA74C;
					iVar3 = 0;
					iVar6 = dword_6FBBA748 + (0xda - iVar6 / 2);
					pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1009));
					D2Win_10117_DrawText(pUVar5, iVar6, iVar2, iVar3, iVar4);
				}
			}
			local_4b8 = *(int*)(local_4b8 + 0xcd);
			if (iStack_4b4 != 0)
			{
				iStack_4b4 = sub_6FAAF5B0(iStack_4b4);
			}
		} while (local_4b8 != 0);
	}
}

//D2Client.0x6FB03010
void __fastcall sub_6FB03010(uint32_t a1, short a2, int a3, int a4)
{
	Unicode* pUVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	Unicode local_190[100];
	Unicode aUStack_c8[100];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)a1));
	Unicode::strcpy(local_190, pUVar1);
	iVar2 = D2Win_10121_GetTextWidth(local_190);
	iVar6 = 0;
	if (a2 != 0)
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
		Unicode::strcpy(aUStack_c8, pUVar1);
		iVar6 = D2Win_10121_GetTextWidth(aUStack_c8);
	}
	iVar5 = 0x23;
	iVar4 = 0x1e;
	if (a4 == 0)
	{
		iVar5 = 0x2a;
		iVar4 = 0xf;
	}
	if (iVar6 < iVar2)
	{
		uVar3 = (uint32_t)((uint32_t)iVar6 >> 8);
		iVar6 = iVar2;
	}
	else
	{
		uVar3 = (uint32_t)((uint32_t)a4 >> 8);
	}
	sub_6FB5B0F0((dword_6FBBA748 - iVar6 / 2) + -5 + a3, iVar5 - dword_6FBBA74C, iVar6 + 10, iVar4,
	    CONCAT31(uVar3, byte_6FBB5F38), (DrawMode)(2));
}

//D2Client.0x6FB03110
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB03110()
{
	int iVar1;
	char cVar2;
	bool bVar3;
	uint8_t bVar4;
	uint16_t uVar5;
	int iVar6;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar7;
	char* a2;
	int iVar8;
	int iVar9;
	Unicode* pUVar10;
	uint32_t extraout_var;
	Unicode* pUVar11;
	uint32_t extraout_var_00;
	uint32_t uVar12;
	uint16_t extraout_var_01;
	short sVar13;
	int iVar14;
	uint32_t extraout_ECX;
	uint32_t uVar15;
	int* piVar16;
	int iStack_398;
	int iStack_394;
	int local_390;
	int iStack_38c;
	int iStack_388;
	Unicode aUStack_380[128];
	Unicode aUStack_280[128];
	Unicode aUStack_180[128];
	char acStack_80[128];

	iVar14 = dword_6FBB5F18;
	local_390 = dword_6FBB5F18;
	iVar6 = sub_6FAAF5B0(0);
	pUnit = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pUnit);
	bVar3 = false;
	iStack_398 = sub_6FAAF5B0(iVar6);
	byte_6FBB5F38 = D2Win_10034_MixRGB(0, 0, 0);
	if ((pRoom != nullptr) && (iVar6 = DUNGEON_IsRoomInTown(pRoom), iVar6 != 0))
	{
		bVar3 = true;
	}
	if (iVar14 == 0)
	{
		return;
	}
	do
	{
		iVar14 = *(int*)(local_390 + 0xc9);
		iVar6 = sub_6FB57BC0();
		iVar7 = sub_6FB57BD0();
		if ((((iVar6 < dword_6FBBA748 + 0x24) || (dword_6FBBA748 + 0x8c < iVar6)) ||
		        (iVar14 = iVar14 - dword_6FBBA74C, iVar7 < iVar14 + -0x1a)) ||
		    (iVar14 < iVar7))
		{
			iStack_394 = 1;
			piVar16 = (int*)(local_390 + 0x34);
			do
			{
				iVar14 = piVar16[-3];
				iVar6 = piVar16[-4];
				iVar7 = sub_6FB57BC0();
				iVar8 = sub_6FB57BD0();
				if (((dword_6FBBA748 + iVar6 <= iVar7) && (iVar7 <= dword_6FBBA748 + iVar6 + 0x14)) &&
				    (((iVar14 - dword_6FBBA74C) + -0x14 <= iVar8 && (iVar8 <= iVar14 - dword_6FBBA74C))))
				{
					iVar14 = *piVar16;
					if (iVar14 == 1)
					{
						iVar14 = sub_6FAAF5B0(0);
						uVar5 = sub_6FAAFD40(iVar14);
						if ((D2C_ZEXT(uVar5) < 9) || (*(int*)(local_390 + 0xbd) < 9))
						{
							sub_6FB036C0(0x101a, 0x101b, 0xa0, 0, 0x32, 0x41, nullptr);
							return;
						}
						if (!bVar3)
						{
							sub_6FB036C0(0x1019, 0, 0x6e, 0, 0x37, 0, (char*)0x1);
							return;
						}
						iVar14 = sub_6FAAFEF0(iStack_398);
						if (iVar14 != 0)
						{
							sub_6FB036C0(0x100c, 0x100d, 0x6e, 0, 0x32, 0x41, nullptr);
							return;
						}
						sub_6FB036C0(0x100a, 0x100b, 0x6e, 0, 0x32, 0x41, nullptr);
						return;
					}
					if (iVar14 == 2)
					{
						bVar4 = CLIENT_IsHardcore();
						if (D2C_ZEXT(bVar4) != 0)
						{
							uVar12 = sub_6FAAFE30(iStack_398);
							if (uVar12 != 0)
							{
								sub_6FB036C0(0x1010, 0x1011, 0xff, 0, 0x32, 0x41, nullptr);
								return;
							}
							sub_6FB036C0(0x100e, 0x100f, 0xff, 0, 0x32, 0x41, nullptr);
							return;
						}
					}
					else
					{
						if (iVar14 == 3)
						{
							uVar12 = sub_6FAAFE70(iStack_398);
							if (uVar12 != 0)
							{
								sub_6FB036C0(0x1012, 0x1013, 0x114, 0, 0x32, 0x41, nullptr);
								return;
							}
							sub_6FB036C0(0x1014, 0x1015, 0x114, 0, 0x32, 0x41, nullptr);
							return;
						}
						if (iVar14 == 4)
						{
							uVar12 = sub_6FAAFEB0(iStack_398);
							uVar15 = 0x1017;
							if (uVar12 == 0)
							{
								uVar15 = 0x1016;
							}
							sub_6FB036C0(uVar15, 0, 0x128, 0, 0x37, 0, nullptr);
							return;
						}
					}
				}
				piVar16 = piVar16 + 8;
				iStack_394 = iStack_394 + 1;
			} while (iStack_394 < 5);
		}
		else
		{
			pUVar10 = aUStack_380;
			iStack_388 = 0;
			iStack_38c = 0;
			iVar14 = 0x80;
			do
			{
				pUVar10 = pUVar10 + 1;
				iVar14 = iVar14 + -1;
			} while (iVar14 != 0);
			iStack_394 = 0x10;
			a2 = (char*)sub_6FAAF5D0(iStack_398);
			if (a2 == nullptr)
			{
				iVar14 = 0;
				do
				{
					cVar2 = "ERROR PLAYER NAME"[iVar14];
					acStack_80[iVar14] = cVar2;
					iVar14 = iVar14 + 1;
				} while (cVar2 != '\0');
				a2 = acStack_80;
			}
			Unicode::toUnicode(aUStack_180, a2, 0x80);
			iVar14 = sub_6FAB1370(iStack_398);
			iVar6 = sub_6FAB13D0(iStack_398);
			iVar7 = sub_6FAB1340(iStack_398);
			iVar8 = sub_6FAB13A0(iStack_398);
			iVar9 = sub_6FAB1400(iStack_398);
			if (iVar14 == iVar7)
			{
				if (iVar9 == 0)
				{
					sVar13 = *(short*)(byte_6FB7CFF0 + (iVar7 + iVar14 * 2) * 2);
				}
				else
				{
					sVar13 = *(short*)(byte_6FB7CFE8 + (iVar7 + iVar14 * 2) * 2);
				}
				pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar13));
				Unicode::strcpy(aUStack_380, pUVar10);
			}
			else
			{
				pUVar10 = aUStack_180;
				iVar1 = iVar7 + iVar14 * 2;
				if (iVar9 == 0)
				{
					sVar13 = *(short*)(byte_6FB7CFF0 + iVar1 * 2);
				}
				else
				{
					sVar13 = *(short*)(byte_6FB7CFE8 + iVar1 * 2);
				}
				pUVar11 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar13));
				Unicode::sprintf(0x80, aUStack_380, pUVar11, pUVar10);
			}
			bVar4 = CLIENT_IsHardcore();
			if (D2C_ZEXT(bVar4) != 0)
			{
				iStack_394 = 0x1e;
				iVar9 = sub_6FAB1400(iStack_398);
				if (iVar6 == iVar8)
				{
					if (iVar9 == 0)
					{
						sVar13 = *(short*)(byte_6FB7D000 + (iVar8 + iVar6 * 2) * 2);
					}
					else
					{
						sVar13 = *(short*)(byte_6FB7CFF8 + (iVar8 + iVar6 * 2) * 2);
					}
					pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar13));
					Unicode::strcpy(aUStack_280, pUVar10);
				}
				else
				{
					pUVar10 = aUStack_180;
					iVar1 = iVar8 + iVar6 * 2;
					if (iVar9 == 0)
					{
						sVar13 = *(short*)(byte_6FB7D000 + iVar1 * 2);
					}
					else
					{
						sVar13 = *(short*)(byte_6FB7CFF8 + iVar1 * 2);
					}
					pUVar11 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar13));
					Unicode::sprintf(0x80, aUStack_280, pUVar11, pUVar10);
				}
			}
			if (iVar14 != 0)
			{
				iStack_388 = 8;
			}
			if (iVar7 != 0)
			{
				iStack_388 = 1;
			}
			if (iVar6 != 0)
			{
				iStack_38c = 9;
			}
			if (iVar8 != 0)
			{
				iStack_38c = 4;
			}
			iVar6 = D2Win_10121_GetTextWidth(aUStack_380);
			iVar7 = D2Win_10121_GetTextWidth(aUStack_280);
			iVar14 = iVar7 + 10;
			if (iVar7 + 10 < iVar6 + 10)
			{
				iVar14 = iVar6 + 10;
			}
			sub_6FB5B0F0(dword_6FBBA748 + 0x24, 0x23 - dword_6FBBA74C, iVar14, iStack_394,
			    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5F38), (DrawMode)(2));
			D2Win_10117_DrawText(aUStack_380, dword_6FBBA748 + 0x29, 0x32 - dword_6FBBA74C, iStack_388, 0);
			D2Win_10117_DrawText(aUStack_280, dword_6FBBA748 + 0x29, 0x41 - dword_6FBBA74C, iStack_38c, 0);
		}
		local_390 = *(int*)(local_390 + 0xcd);
		if (iStack_398 != 0)
		{
			iStack_398 = sub_6FAAF5B0(iStack_398);
		}
		if (local_390 == 0)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB036C0
void __fastcall sub_6FB036C0(uint32_t a1, short a2, int a3, uint32_t a4, int a5, int a6, char* a7)
{
	Unicode* pUVar1;
	short index;
	int iVar2;
	int iVar3;
	char* nColor;
	int iVar4;
	int local_cc;
	Unicode local_c8[100];

	index = (short)a1;
	if (a2 == 0)
	{
		sub_6FB03010(a1, 0, a3, 0);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		Unicode::strcpy(local_c8, pUVar1);
		iVar3 = D2Win_10121_GetTextWidth(local_c8);
		iVar4 = 0;
		iVar2 = a5 - dword_6FBBA74C;
		iVar3 = dword_6FBBA748 + (a3 - iVar3 / 2);
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		D2Win_10117_DrawText(pUVar1, iVar3, iVar2, (int)a7, iVar4);
		return;
	}
	sub_6FB03010(a1, a2, a3, 1);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	Unicode::strcpy(local_c8, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_c8);
	iVar4 = 0;
	iVar2 = a5 - dword_6FBBA74C;
	iVar3 = dword_6FBBA748 + (a3 - iVar3 / 2);
	nColor = a7;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar2, (int)nColor, iVar4);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
	Unicode::strcpy(local_c8, pUVar1);
	iVar3 = D2Win_10121_GetTextWidth(local_c8);
	iVar4 = 0;
	iVar2 = a6 - dword_6FBBA74C;
	iVar3 = dword_6FBBA748 + (a3 - iVar3 / 2);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(a2));
	D2Win_10117_DrawText(pUVar1, iVar3, iVar2, (int)a7, iVar4);
}

//D2Client.0x6FB03870
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB03870(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	D2UnitStrc* pUnit;
	int iVar5;
	int iVar6;
	int iVar7;
	uint16_t extraout_var;
	D2ActiveRoomStrc* pRoom;
	int* piVar8;
	int local_c;

	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FAAF5B0(0);
	iVar4 = sub_6FAAF5B0(iVar3);
	iVar3 = dword_6FBB5F18;
	pUnit = CUNIT_GetPlayer();
	iVar5 = sub_6FB57BC0();
	iVar6 = sub_6FB57BD0();
	if ((((iVar5 < dword_6FBBA748 + 0x116) || (dword_6FBBA748 + 0x136 < iVar5)) ||
	        (iVar6 < 0x185 - dword_6FBBA74C)) ||
	    (0x1a5 - dword_6FBBA74C < iVar6))
	{
		if (gnScreenWidth / 2 <= iVar2)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 0;
			return;
		}
		while (iVar3 != 0)
		{
			local_c = 0;
			piVar8 = (int*)(iVar3 + 0x14);
			do
			{
				iVar2 = piVar8[-4];
				iVar5 = piVar8[-3];
				if (piVar8[-5] == 0)
				{
					iVar6 = sub_6FB57BC0();
					iVar7 = sub_6FB57BD0();
					iVar2 = dword_6FBBA748 + iVar2;
					if (((iVar2 <= iVar6) && (iVar6 <= iVar2 + 0x14)) &&
					    ((iVar5 = iVar5 - dword_6FBBA74C, iVar5 + -0x14 <= iVar7 && (iVar7 <= iVar5))))
					{
						if (*piVar8 == 1)
						{
							iVar2 = sub_6FAAF5B0(0);
							uVar1 = sub_6FAAFD40(iVar2);
							if (D2C_ZEXT(uVar1) < 9)
								goto LAB_6fb039df;
							if ((*piVar8 == 1) &&
							    ((pRoom = UNITS_GetRoom(pUnit), pRoom == nullptr ||
							                                        (iVar2 = DUNGEON_IsRoomInTown(pRoom), iVar2 == 0))))
								goto LAB_6fb03a35;
						}
						if (piVar8[2] == 0)
						{
							iVar3 = local_c * 0x20 + iVar3;
							*(int*)(iVar3 + 0x10) = piVar8[-1] + 1;
							*(uint32_t*)(iVar3 + 0x1c) = 1;
							dword_6FBB5F3C = 1;
							goto LAB_6fb039df;
						}
					}
				}
				else
				{
					iVar6 = sub_6FB57BC0();
					iVar7 = sub_6FB57BD0();
					iVar2 = dword_6FBBA748 + iVar2;
					if (((iVar2 <= iVar6) && (iVar6 <= iVar2 + 0x35)) &&
					    ((iVar5 = iVar5 - dword_6FBBA74C, iVar5 + -0x14 <= iVar7 && (iVar7 <= iVar5))))
					{
						iVar3 = local_c * 0x20 + iVar3;
						if (*(int*)(iVar3 + 0x18) != 1)
						{
							*(uint32_t*)(iVar3 + 0x10) = 1;
						}
						*(uint32_t*)(iVar3 + 0x1c) = 1;
						dword_6FBB5F3C = 1;
						pSMSGHANDLER_PARAMS->bUseResult = 1;
						goto LAB_6fb039ea;
					}
				}
			LAB_6fb03a35:
				piVar8 = piVar8 + 8;
				local_c = local_c + 1;
			} while (local_c < 5);
			iVar3 = *(int*)(iVar3 + 0xcd);
			if (iVar4 != 0)
			{
				iVar4 = sub_6FAAF5B0(iVar4);
			}
		}
	LAB_6fb039df:
		pSMSGHANDLER_PARAMS->bUseResult = 1;
	}
	else
	{
		dword_6FBB5F34 = 1;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
	}
LAB_6fb039ea:
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB03AC0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB03AC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	char cVar1;
	int iVar2;
	uint8_t bVar3;
	short sVar4;
	uint16_t uVar5;
	int iVar6;
	int iVar7;
	D2UnitStrc* pUnit;
	int iVar8;
	int iVar9;
	int iVar10;
	uint16_t extraout_var_00;
	D2ActiveRoomStrc* pRoom;
	uint32_t extraout_var;
	char* pcVar11;
	uint32_t uVar12;
	uint32_t uVar13;
	uint32_t uVar14;
	uint32_t uVar15;
	int* piVar16;
	char* pcVar17;
	char* pcVar18;
	int local_210;
	char acStack_200[512];

	iVar6 = sub_6FB57BC0();
	iVar7 = sub_6FAAF5B0(0);
	iVar2 = dword_6FBB5F18;
	dword_6FBB5F34 = 0;
	pUnit = CUNIT_GetPlayer();
	if (gnScreenWidth / 2 <= iVar6)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	iVar6 = sub_6FB57BC0();
	iVar8 = sub_6FB57BD0();
	if ((((dword_6FBBA748 + 0x116 <= iVar6) && (iVar6 <= dword_6FBBA748 + 0x136)) &&
	        (0x185 - dword_6FBBA74C <= iVar8)) &&
	    (iVar8 <= 0x1a5 - dword_6FBBA74C))
	{
		sub_6FB23260(0x16, 1, 0);
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	iVar6 = sub_6FB57BC0();
	iVar8 = sub_6FB57BD0();
	if (((dword_6FBBA748 + 0xe3 <= iVar6) && (iVar6 <= dword_6FBBA748 + 0x118)) &&
	    ((0x18 - dword_6FBBA74C <= iVar8 &&
	        ((iVar8 <= 0x23 - dword_6FBBA74C && (sVar4 = sub_6FAAFDA0(iVar7), sVar4 != -1))))))
	{
		sub_6FAB0330();
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if (dword_6FBB5F3C == 0)
	{
		dword_6FBB5F3C = 0;
		for (; iVar2 != 0; iVar2 = *(int*)(iVar2 + 0xcd))
		{
			piVar16 = (int*)(iVar2 + 0x1c);
			iVar6 = 5;
			do
			{
				if (*piVar16 != 0)
				{
					*piVar16 = 0;
					piVar16[-3] = piVar16[-3] + -1;
				}
				piVar16 = piVar16 + 8;
				iVar6 = iVar6 + -1;
			} while (iVar6 != 0);
		}
	}
	else
	{
		iVar6 = sub_6FAAF5B0(iVar7);
		while ((iVar6 != 0 && (iVar2 != 0)))
		{
			local_210 = 0;
			piVar16 = (int*)(iVar2 + 0x10);
			do
			{
				iVar7 = piVar16[-3];
				iVar8 = piVar16[-2];
				if (piVar16[-4] == 0)
				{
					iVar9 = sub_6FB57BC0();
					iVar10 = sub_6FB57BD0();
					iVar7 = dword_6FBBA748 + iVar7;
					if (((iVar7 <= iVar9) && (iVar9 <= iVar7 + 0x14)) &&
					    ((iVar8 = iVar8 - dword_6FBBA74C, iVar8 + -0x14 <= iVar10 && (iVar10 <= iVar8))))
					{
						if (piVar16[1] == 1)
						{
							iVar7 = sub_6FAAF5B0(0);
							uVar5 = sub_6FAAFD40(iVar7);
							if (D2C_ZEXT(uVar5) < 9)
							{
								pSMSGHANDLER_PARAMS->bUseResult = 1;
								pSMSGHANDLER_PARAMS->lResult = 0;
								SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
								return;
							}
							if ((piVar16[1] == 1) &&
							    ((pRoom = UNITS_GetRoom(pUnit), pRoom == nullptr ||
							                                        (iVar7 = DUNGEON_IsRoomInTown(pRoom), iVar7 == 0))))
								goto LAB_6fb03e09;
						}
						uVar15 = 0;
						switch (piVar16[1])
						{
						case 1:
							sub_6FAB0540(iVar6);
							uVar15 = sub_6FAAFEF0(iVar6);
							break;
						case 2:
							bVar3 = CLIENT_IsHardcore();
							if (D2C_ZEXT(bVar3) != 0)
							{
								sub_6FAAFF40(iVar6);
								uVar15 = sub_6FAAFE30(iVar6);
							}
							break;
						case 3:
							sub_6FAAFFB0(iVar6);
							uVar15 = sub_6FAAFE70(iVar6);
							break;
						case 4:
							sub_6FAB0020(iVar6);
							uVar15 = sub_6FAAFEB0(iVar6);
							iVar7 = (int)(CLIENT_GetComInterface());
							if (iVar7 != 0)
							{
								iVar8 = 0;
								if (uVar15 == 0)
								{
									do
									{
										cVar1 = "/unsquelch "[iVar8];
										acStack_200[iVar8] = cVar1;
										iVar8 = iVar8 + 1;
									} while (cVar1 != '\0');
								}
								else
								{
									do
									{
										cVar1 = "/squelch "[iVar8];
										acStack_200[iVar8] = cVar1;
										iVar8 = iVar8 + 1;
									} while (cVar1 != '\0');
								}
								pcVar11 = (char*)sub_6FAAF5D0(iVar6);
								uVar13 = 0xffffffff;
								do
								{
									pcVar18 = pcVar11;
									if (uVar13 == 0)
										break;
									uVar13 = uVar13 - 1;
									pcVar18 = pcVar11 + 1;
									cVar1 = *pcVar11;
									pcVar11 = pcVar18;
								} while (cVar1 != '\0');
								uVar13 = ~uVar13;
								iVar8 = -1;
								pcVar11 = acStack_200;
								do
								{
									pcVar17 = pcVar11;
									if (iVar8 == 0)
										break;
									iVar8 = iVar8 + -1;
									pcVar17 = pcVar11 + 1;
									cVar1 = *pcVar11;
									pcVar11 = pcVar17;
								} while (cVar1 != '\0');
								pcVar11 = pcVar18 + -uVar13;
								pcVar18 = pcVar17 + -1;
								for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1)
								{
									*(uint32_t*)pcVar18 = *(uint32_t*)pcVar11;
									pcVar11 = pcVar11 + 4;
									pcVar18 = pcVar18 + 4;
								}
								for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1)
								{
									*pcVar18 = *pcVar11;
									pcVar11 = pcVar11 + 1;
									pcVar18 = pcVar18 + 1;
								}
								(**(code**)(iVar7 + 0x14))();
							}
						}
						if (uVar15 != 0)
						{
							*piVar16 = *piVar16 + 2;
						}
					}
				}
				else
				{
					iVar9 = sub_6FB57BC0();
					iVar10 = sub_6FB57BD0();
					iVar7 = dword_6FBBA748 + iVar7;
					if ((((iVar7 <= iVar9) && (iVar9 <= iVar7 + 0x35)) &&
					        (iVar8 = iVar8 - dword_6FBBA74C, iVar8 + -0x14 <= iVar10)) &&
					    (iVar10 <= iVar8))
					{
						if (*(int*)(local_210 * 0x20 + 0x18 + iVar2) != 1)
						{
							iVar2 = *(int*)(iVar2 + 0xc5);
							sub_6FAB0090(iVar6);
							uVar12 = sub_6FAAFF30(iVar6);
							iVar6 = dword_6FBB5F18;
							while (true)
							{
								D2_ASSERT(iVar6);
								if (*(int*)(iVar6 + 0xc5) == iVar2)
									break;
								iVar6 = *(int*)(iVar6 + 0xcd);
							}
							*(uint32_t*)(local_210 * 0x20 + 0x18 + iVar6) = uVar12;
						}
						sub_6FAABF60();
						pSMSGHANDLER_PARAMS->bUseResult = 1;
						pSMSGHANDLER_PARAMS->lResult = 0;
						SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
						return;
					}
				}
			LAB_6fb03e09:
				piVar16 = piVar16 + 8;
				local_210 = local_210 + 1;
			} while (local_210 < 5);
			iVar2 = *(int*)(iVar2 + 0xcd);
			iVar6 = sub_6FAAF5B0(iVar6);
		}
		dword_6FBB5F3C = 0;
	}
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB03FA0
void __cdecl sub_6FB03FA0()
{
	gpCellFile_6FBB5F1C = sub_6FB20100("Menu\\party");
	gpCellFile_6FBB5F20 = sub_6FB20100("Menu\\partybuttons");
	gpCellFile_6FBB5F24 = sub_6FB20100("Menu\\partyboxes");
	gpCellFile_6FBB5F28 = sub_6FB20100("Panel\\inv_goldbtn");
	gpCellFile_6FBB5F2C = sub_6FB20100("Menu\\partybar");
}

//D2Client.0x6FB03FF0
void __cdecl sub_6FB03FF0()
{
	if (gpCellFile_6FBB5F1C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F1C);
		gpCellFile_6FBB5F1C = nullptr;
	}
	if (gpCellFile_6FBB5F20 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F20);
		gpCellFile_6FBB5F20 = nullptr;
	}
	if (gpCellFile_6FBB5F24 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F24);
		gpCellFile_6FBB5F24 = nullptr;
	}
	if (gpCellFile_6FBB5F28 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F28);
		gpCellFile_6FBB5F28 = nullptr;
	}
	if (gpCellFile_6FBB5F2C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5F2C);
		gpCellFile_6FBB5F2C = nullptr;
	}
}

//D2Client.0x6FB04060
void __cdecl sub_6FB04060()
{
	*(uint32_t*)byte_6FB7D0EC = (uint32_t)(gnScreenHeight + -0x69);
	*(uint32_t*)byte_6FB7D100 = (uint32_t)(gnScreenHeight + -0x69);
	*(uint32_t*)byte_6FB7D0E8 = (uint32_t)(gnScreenHeight + -0x8c);
	dword_6FB7D0FC = gnScreenHeight + -0x8c;
	dword_6FB7D0F4 = gnScreenWidth / 2 + 0x28;
	byte_6FB7D114 = gnScreenHeight + -0xa0;
	byte_6FB7D128 = gnScreenHeight + -0xa0;
	byte_6FB7D0F8 = gnScreenWidth / 2 + 0x4b;
	byte_6FB7D110 = gnScreenHeight + -0xc3;
	byte_6FB7D124 = gnScreenHeight + -0xc3;
	*(uint32_t*)byte_6FB7D0F0 = (uint32_t)(gnScreenHeight + -0x8f);
	*(uint32_t*)byte_6FB7D104 = (uint32_t)(gnScreenHeight + -0x8f);
	byte_6FB7D108 = 0x28;
	byte_6FB7D10C = 0x4b;
	byte_6FB7D118 = gnScreenHeight + -0xc6;
	byte_6FB7D11C = dword_6FB7D0F4;
	byte_6FB7D120 = byte_6FB7D0F8;
	byte_6FB7D12C = gnScreenHeight + -0xc6;
}

//D2Client.0x6FB04110
void __cdecl sub_6FB04110()
{
	int iVar1;
	int iVar2;

	iVar1 = (int)&tbl_6FBB6070;
	iVar2 = 6;
	do
	{
		memset((void*)(iVar1), 0, 2 * (300));
		iVar1 = iVar1 + 0x26a;
		iVar2 = iVar2 + -1;
	} while (iVar2 != 0);
}

//D2Client.0x6FB04140
void __cdecl sub_6FB04140()
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;

	SRegSaveValue("Diablo II", "GAMEOVER", 0, 0);
	iVar1 = 0;
	dword_6FBB5F58 = 0;
	gpCellFile_6FBB5F95 = nullptr;
	gpCellFile_6FBB5F99 = nullptr;
	gpCellFile_6FBB5F91 = nullptr;
	gpCellFile_6FBB5F9D = nullptr;
	gpCellFile_6FBB6011 = nullptr;
	gpCellFile_6FBB600D = nullptr;
	puVar3 = &dword_6FBB5FA1;
	for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	dword_6FBB5F64 = 0;
	dword_6FBB5F6C = 0;
	byte_6FBB6F19 = 0;
	do
	{
		(&byte_6FBB6016)[iVar1] = 0;
		(&byte_6FBB6040)[iVar1] = 0;
		iVar1 = iVar1 + 1;
	} while (iVar1 < 0x29);
	byte_6FBB5F71 = 0;
	*(uint32_t*)byte_6FBB5F7D = (uint32_t)0xffffffff;
	byte_6FBB5F72 = '\0';
	byte_6FBB5F81 = 0xffffffff;
	byte_6FBB5F70 = 0;
	byte_6FBB5F85 = 0xffffffff;
	byte_6FBB5F74 = '\0';
	byte_6FBB5F89 = 0xffffffff;
	byte_6FBB6F1D = 0;
	byte_6FBB6F1E = 0;
	byte_6FBB6F1F = 0;
	byte_6FBB6F20 = 0;
	byte_6FBB5F73 = '\0';
	dword_6FBB5F75 = 0xffffffff;
	byte_6FBB5F8D = 0xffffffff;
}

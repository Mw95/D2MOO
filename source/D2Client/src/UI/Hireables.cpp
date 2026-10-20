#include "UI/Hireables.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Cursor.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Select.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Inv.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB791E8
uint32_t tbl_6FB791E8[12] = {0, 0x201, (uint32_t)sub_6FADC550, 0, 0x202, (uint32_t)sub_6FADC5F0, 3, 0x1B, (uint32_t)sub_6FADC6D0, 3, 0xD, (uint32_t)sub_6FADC690};
//D2Client.0x6FB79218
uint8_t tbl_6FB79218[47] = {0, 0, 0, 0, 1, 2, 0, 0, 0xC0, 0xCC, 0xAD, 0x6F, 0, 0, 0, 0, 2, 2, 0, 0, 0xB0, 0xCD, 0xAD, 0x6F, 3, 0, 0, 0, 0x1B, 0, 0, 0, 0xF0, 0xCE, 0xAD, 0x6F, 3, 0, 0, 0, 0xD, 0, 0, 0, 0xB0, 0xCE, 0xAD};
//D2Client.0x6FB79247
uint32_t dword_6FB79247 = 0x7461446F;
//D2Client.0x6FBB3670
uint8_t* ptr_6FBB3670;
//D2Client.0x6FBB3674
uint32_t dword_6FBB3674;
//D2Client.0x6FBB3678
D2CellFileStrc* gpCellFile_6FBB3678;
//D2Client.0x6FBB367C
D2CellFileStrc* gpCellFile_6FBB367C;
//D2Client.0x6FBB3680
D2CellFileStrc* gpCellFile_6FBB3680;
//D2Client.0x6FBB3684
D2CellFileStrc* gpCellFile_6FBB3684;
//D2Client.0x6FBB3688
D2CellFileStrc* gpCellFile_6FBB3688;
//D2Client.0x6FBB368C
D2CellFileStrc* gpCellFile_6FBB368C;
//D2Client.0x6FBB3690
int32_t dword_6FBB3690;
//D2Client.0x6FBB3694
uint8_t byte_6FBB3694;
//D2Client.0x6FBB3695
uint8_t byte_6FBB3695;
//D2Client.0x6FBB3696
uint8_t byte_6FBB3696;
//D2Client.0x6FBB3697
char byte_6FBB3697;
//D2Client.0x6FBB3698
int32_t dword_6FBB3698;
//D2Client.0x6FBB369C
int32_t dword_6FBB369C;
//D2Client.0x6FBB36A0
uint32_t dword_6FBB36A0;
//D2Client.0x6FBB36A4
uint32_t dword_6FBB36A4;
//D2Client.0x6FBB36A8
char byte_6FBB36A8;
//D2Client.0x6FBB36AC
uint32_t dword_6FBB36AC;
//D2Client.0x6FBB36B0
int32_t dword_6FBB36B0;
//D2Client.0x6FBB36B4
D2CellFileStrc* gpCellFile_6FBB36B4;
//D2Client.0x6FBB36B8
D2CellFileStrc* gpCellFile_6FBB36B8;
//D2Client.0x6FBB36BC
D2CellFileStrc* gpCellFile_6FBB36BC;
//D2Client.0x6FBB36C0
uint32_t dword_6FBB36C0;
//D2Client.0x6FBB36C4
uint32_t dword_6FBB36C4;
//D2Client.0x6FBB36C8
uint32_t dword_6FBB36C8;
//D2Client.0x6FBB36CC
uint32_t dword_6FBB36CC;
//D2Client.0x6FBB36D0
uint32_t dword_6FBB36D0;
//D2Client.0x6FBB36D4
uint32_t dword_6FBB36D4;
//D2Client.0x6FBB377A
uint8_t byte_6FBB377A;
//D2Client.0x6FBB377B
uint8_t byte_6FBB377B;
//D2Client.0x6FBB377C
uint8_t byte_6FBB377C;

//D2Client.0x6FADA720
void __cdecl sub_6FADA720()
{
	char cVar1;
	D2CellFileStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t* puVar6;
	int iVar7;
	char* pcVar8;
	char* pcVar9;
	char local_180[21];
	uint32_t local_16b;
	uint32_t local_167;
	uint16_t local_163;
	uint8_t local_161;
	uint32_t local_160[6];
	uint32_t local_148;
	uint32_t local_144;
	uint32_t local_140[6];
	uint32_t local_128;
	uint32_t local_124;
	uint32_t local_120[5];
	uint32_t local_10a;
	uint32_t local_106;
	uint16_t local_102;
	uint32_t local_100[6];
	uint32_t local_e6;
	uint16_t local_e2;
	char local_e0[2];
	char acStack_de[21];
	uint32_t local_c9;
	uint32_t local_c5;
	uint8_t local_c1;
	uint32_t local_c0[5];
	uint32_t local_ac;
	uint32_t local_a8;
	uint32_t local_a4;
	uint32_t local_a0[40];

	pcVar8 = "Hireables\\AmazonIcon";
	pcVar9 = local_180;
	for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*(uint32_t*)pcVar9 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		pcVar9 = pcVar9 + 4;
	}
	*pcVar9 = *pcVar8;
	local_16b = 0;
	local_167 = 0;
	local_163 = 0;
	local_161 = 0;
	iVar5 = 5;
	pcVar8 = "Hireables\\SorceressIcon";
	puVar6 = local_160;
	for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		puVar6 = puVar6 + 1;
	}
	local_148 = 0;
	local_144 = 0;
	pcVar8 = "Hireables\\BarbarianIcon";
	puVar6 = local_140;
	for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		puVar6 = puVar6 + 1;
	}
	local_128 = 0;
	local_124 = 0;
	pcVar8 = "Hireables\\PaladinIcon";
	puVar6 = local_120;
	for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		puVar6 = puVar6 + 1;
	}
	*(uint16_t*)puVar6 = *(uint16_t*)pcVar8;
	local_10a = 0;
	local_106 = 0;
	local_102 = 0;
	pcVar8 = "Hireables\\NecromancerIcon";
	puVar6 = local_100;
	for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		puVar6 = puVar6 + 1;
	}
	*(uint16_t*)puVar6 = *(uint16_t*)pcVar8;
	local_e6 = 0;
	local_e2 = 0;
	pcVar8 = "Hireables\\AssassinIcon";
	pcVar9 = local_e0;
	for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*(uint32_t*)pcVar9 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		pcVar9 = pcVar9 + 4;
	}
	*(uint16_t*)pcVar9 = *(uint16_t*)pcVar8;
	pcVar9[2] = pcVar8[2];
	local_c9 = 0;
	local_c5 = 0;
	local_c1 = 0;
	pcVar8 = "Hireables\\DruidIcon";
	puVar6 = local_c0;
	for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = *(uint32_t*)pcVar8;
		pcVar8 = pcVar8 + 4;
		puVar6 = puVar6 + 1;
	}
	local_ac = 0;
	local_a8 = 0;
	local_a4 = 0;
	iVar7 = 0;
	puVar6 = local_a0;
	for (iVar3 = 0x28; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	puVar6 = &dword_6FBB3674;
	for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	pcVar8 = local_180;
	do
	{
		pDVar2 = sub_6FB20100(pcVar8);
		(&dword_6FBB3674)[iVar7] = (uint32_t)(pDVar2);
		pcVar8 = pcVar8 + 0x20;
		iVar7 = iVar7 + 1;
		iVar5 = iVar5 + -1;
	} while (iVar5 != 0);
	iVar3 = FOG_IsExpansion();
	if (iVar3 != 0)
	{
		puVar6 = &dword_6FBB3674 + iVar7;
		iVar3 = 0;
		pcVar8 = local_e0;
		do
		{
			iVar5 = -1;
			pcVar9 = pcVar8;
			do
			{
				if (iVar5 == 0)
					break;
				iVar5 = iVar5 + -1;
				cVar1 = *pcVar9;
				pcVar9 = pcVar9 + 1;
			} while (cVar1 != '\0');
			if (iVar5 == -2)
				break;
			pDVar2 = sub_6FB20100(pcVar8);
			*puVar6 = (uint32_t)(pDVar2);
			iVar3 = iVar3 + 1;
			pcVar8 = pcVar8 + 0x20;
			puVar6 = puVar6 + 1;
		} while (iVar3 < 7);
	}
	iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0);
	ptr_6FBB3670 = (uint8_t*)(D2_ALLOC_POOL(nullptr, iVar3 * 0x14));
	puVar6 = (uint32_t*)ptr_6FBB3670;
	for (uVar4 = iVar3 * 5 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*(uint8_t*)puVar6 = 0;
		puVar6 = (uint32_t*)((int)puVar6 + 1);
	}
}

//D2Client.0x6FADA8F0
void __cdecl sub_6FADA8F0()
{
	D2CellFileStrc* pDVar1;
	int iVar2;
	void* pFree;
	uint32_t* puVar3;
	int iVar4;

	puVar3 = &dword_6FBB3674;
	do
	{
		if ((D2CellFileStrc*)*puVar3 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar3);
			*puVar3 = 0;
		}
		puVar3 = puVar3 + 1;
	} while ((int)puVar3 < (int)&dword_6FBB3690);
	if (ptr_6FBB3670 != nullptr)
	{
		iVar4 = 0;
		iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0) * 5;
		pFree = ptr_6FBB3670;
		if (0 < iVar2)
		{
			do
			{
				pDVar1 = *(D2CellFileStrc**)((int)pFree + iVar4 * 4);
				if (pDVar1 != nullptr)
				{
					CLIENT_FreeCellFile(pDVar1);
					pFree = ptr_6FBB3670;
				}
				iVar4 = iVar4 + 1;
			} while (iVar4 < iVar2);
		}
		D2_FREE_POOL(nullptr, pFree);
		ptr_6FBB3670 = nullptr;
	}
}

//D2Client.0x6FADA970
void __fastcall sub_6FADA970(int a1)
{
	if (a1 == 0)
	{
		if (byte_6FBB3697 != '\0')
		{
			return;
		}
		byte_6FBB3697 = '\x01';
	}
	byte_6FBB3694 = D2Win_10034_MixRGB(0, 0x80, 0);
	byte_6FBB3695 = D2Win_10034_MixRGB(0xc0, 0xc0, 0);
	byte_6FBB3696 = D2Win_10034_MixRGB(0xff, 0, 0);
}

//D2Client.0x6FADA9D0
void __cdecl sub_6FADA9D0()
{
	byte_6FBB3697 = '\0';
}

//D2Client.0x6FADA9E0
D2CellFileStrc* __fastcall sub_6FADA9E0(int a1, int a2, int* a3, uint32_t* a4)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	D2CellFileStrc* pDVar4;
	uint16_t* puVar5;
	char* pcVar6;
	int iVar7;
	char local_100[256];

	if (((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0) <= a2)) ||
	    (iVar7 = a2 * 0xe0 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbe8), iVar7 == 0))
	{
		return nullptr;
	}
	if (a4 != nullptr)
	{
		*a4 = (uint32_t) * (uint8_t*)(iVar7 + 4) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x14);
	}
	iVar1 = sub_6FAB1920(a1, a2, 0);
	*a3 = iVar1;
	if (iVar1 == -1)
	{
		return nullptr;
	}
	uVar2 = sub_6FAB1AE0(iVar1);
	iVar1 = 1;
	pcVar6 = (char*)(iVar7 + 0x2f);
	puVar5 = (uint16_t*)(iVar7 + 0xb2);
	do
	{
		if ((uVar2 == *puVar5) && (iVar3 = iVar1, *pcVar6 != '\0'))
			break;
		iVar1 = iVar1 + 1;
		puVar5 = puVar5 + 1;
		pcVar6 = pcVar6 + 0x20;
		iVar3 = 0;
	} while (iVar1 < 5);
	iVar1 = iVar3 + a2 * 5;
	if (*(int*)((int)ptr_6FBB3670 + iVar1 * 4) == 0)
	{
		sprintf(local_100, "hireables\\%s", iVar3 * 0x20 + 0xf + iVar7);
		pDVar4 = sub_6FB20100(local_100);
		*(D2CellFileStrc**)((int)ptr_6FBB3670 + iVar1 * 4) = pDVar4;
	}
	return *(D2CellFileStrc**)((int)ptr_6FBB3670 + iVar1 * 4);
}

//D2Client.0x6FADAB00
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FADAB00()
{
	char cVar1;
	bool bVar2;
	int iVar3;
	short sVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint16_t extraout_var;
	uint32_t uVar7;
	uint32_t uVar8;
	char* a2;
	uint32_t uVar9;
	D2CellFileStrc* pDVar10;
	DWORD DVar11;
	Unicode* pUVar12;
	Unicode* a3;
	Unicode* a2_00;
	Unicode* pUVar13;
	int iVar14;
	void* pvVar15;
	D2GfxDataStrc* pDVar16;
	DrawMode eDrawMode;
	int local_2b4;
	D2CellFileStrc* local_2b0;
	int local_2ac;
	uint32_t local_2a8;
	uint32_t local_2a4[2];
	D2UnitStrc* local_29c;
	int iStack_298;
	int iStack_294;
	D2GfxDataStrc local_290;
	D2GfxDataStrc DStack_248;
	Unicode aUStack_200[256];

	pDVar5 = CUNIT_GetPlayer();
	local_2ac = 0x48;
	local_2a4[1] = 0;
	local_2b4 = 0xf;
	local_29c = pDVar5;
	iVar6 = sub_6FAB5750();
	if ((((iVar6 == 3) || (iVar6 == 2)) || (iVar6 = sub_6FB23230(9), iVar6 != 0)) ||
	    ((iVar6 = sub_6FB23230(0xb), iVar6 != 0 || (dword_6FBB3690 == 2))))
	{
		dword_6FBB36A0 = 0;
		dword_6FBB36A4 = 0;
		return;
	}
	iVar6 = sub_6FAAC080();
	if (((iVar6 != 0) && (iVar6 = sub_6FB23230(0x23), iVar6 == 0)) &&
	    ((dword_6FBB3690 != 2 && (iVar6 = sub_6FAB1920((int)pDVar5, 7, 0), iVar6 != -1))))
	{
		sub_6FB23260(0x23, 0, 0);
	}
	bVar2 = false;
	sVar4 = sub_6FB2A6E0((int*)pDVar5);
	uVar9 = D2C_ZEXT(sVar4);
	if (pDVar5 == nullptr)
	{
		local_2a4[0] = 0xffffffff;
	}
	else
	{
		local_2a4[0] = pDVar5->dwUnitId;
	}
	local_2a8 = uVar9;
	if (((sVar4 == -1) || (dword_6FBB3690 != 0)) || (iVar6 = sub_6FAAF5B0(0), iVar6 == 0))
	{
	LAB_6fadad53:
		uVar9 = 0;
	}
	else
	{
		do
		{
			sVar4 = sub_6FAAFDA0(iVar6);
			if (((short)uVar9 == sVar4) &&
			    (uVar7 = sub_6FAB0870(iVar6), pDVar5 = local_29c, uVar7 != local_2a4[0]))
			{
				uVar8 = sub_6FAAFD50(iVar6);
				pDVar5 = local_29c;
				switch (uVar8)
				{
				case 0:
					local_2b0 = (D2CellFileStrc*)(dword_6FBB3674);
					break;
				case 1:
					local_2b0 = gpCellFile_6FBB3678;
					break;
				case 2:
					local_2b0 = gpCellFile_6FBB3684;
					break;
				case 3:
					local_2b0 = gpCellFile_6FBB3680;
					break;
				case 4:
					local_2b0 = gpCellFile_6FBB367C;
					break;
				case 5:
					local_2b0 = gpCellFile_6FBB368C;
					break;
				case 6:
					local_2b0 = gpCellFile_6FBB3688;
					break;
				default:
					goto switchD_6fadac35_default;
				}
				if (local_2b0 != nullptr)
				{
					sub_6FADB180(uVar7, local_2b4, 0);
					iVar3 = local_2ac;
					iVar14 = local_2b4;
					a2 = (char*)sub_6FAAF5D0(iVar6);
					memset(&local_290, 0, 2 * (0x20));
					Unicode::toUnicode((Unicode*)&local_290, a2, 0x20);
					sub_6FADB280((Unicode*)&local_290, iVar14, iVar3, 0);
					sub_6FADB5C0(&local_2ac, (int*)(local_2a4 + 1));
					pDVar16 = &DStack_248;
					for (iVar14 = 0x12; iVar14 != 0; iVar14 = iVar14 + -1)
					{
						pDVar16->pCurrentCell = nullptr;
						pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
					}
					DStack_248.pCellFile = local_2b0;
					TEXTURE_CelDraw(&DStack_248, local_2b4, 0x3c, 0xffffffff, DRAWMODE_TRANS50, nullptr);
					bVar2 = true;
					local_2b4 = local_2b4 + 0x38;
					uVar9 = local_2a8;
					pDVar5 = local_29c;
				}
			}
		switchD_6fadac35_default:
			iVar6 = sub_6FAAF5B0(iVar6);
		} while (iVar6 != 0);
		if (!bVar2)
			goto LAB_6fadad53;
		uVar9 = 1;
	}
	pDVar16 = &local_290;
	for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		pDVar16->pCurrentCell = nullptr;
		pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
	}
	pDVar10 = sub_6FADA9E0((int)pDVar5, 7, (int*)&local_2a8, nullptr);
	uVar7 = local_2a8;
	local_290.pCellFile = pDVar10;
	if (pDVar10 == nullptr)
		goto LAB_6fadae44;
	sub_6FADB180(local_2a8, local_2b4, 7);
	iVar6 = local_2ac;
	pDVar5 = sub_6FB269F0(uVar7, 1);
	sub_6FADB300(pDVar5, local_2b4, iVar6);
	sub_6FADB5C0(&local_2ac, (int*)(local_2a4 + 1));
	dword_6FBB3698 = local_2b4;
	dword_6FBB369C = local_2ac;
	if (((dword_6FBB36A4 == 0) || (dword_6FBB36AC == 0)) ||
	    (DVar11 = GetTickCount(), DVar11 - dword_6FBB36AC < 700))
	{
		if (dword_6FBB36A0 != 0)
			goto LAB_6fadae09;
		eDrawMode = DRAWMODE_TRANS50;
	}
	else
	{
		dword_6FBB36A0 = 1;
	LAB_6fadae09:
		eDrawMode = DRAWMODE_HIGHLIGHT;
	}
	TEXTURE_CelDraw(&local_290, local_2b4, 0x3c, 0xffffffff, eDrawMode, nullptr);
	local_2b4 = local_2b4 + 0x38;
	pDVar10 = (D2CellFileStrc*)0x1;
LAB_6fadae44:
	local_2b0 = (D2CellFileStrc*)(uVar9 | (uint32_t)pDVar10);
	pvVar15 = nullptr;
	iVar6 = *(int*)((uint8_t*)&sgptDataTables);
	iVar14 = *(int*)(iVar6 + 0xbf0);
	if (0 < iVar14)
	{
		local_2a8 = 0;
		do
		{
			pDVar5 = local_29c;
			uVar9 = local_2a8;
			if (((-1 < (int)local_2a8) && ((int)pvVar15 < iVar14)) &&
			    (iVar6 = *(int*)(iVar6 + 0xbe8) + local_2a8, iVar6 != 0))
			{
				cVar1 = *(char*)(iVar6 + 0xe);
				if (cVar1 == '\x01')
				{
					pDVar16 = &local_290;
					for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
					{
						pDVar16->pCurrentCell = nullptr;
						pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
					}
					pDVar10 = sub_6FADA9E0((int)local_29c, (int)pvVar15, &iStack_298, nullptr);
					local_290.pCellFile = pDVar10;
					if (pDVar10 != nullptr)
					{
						sub_6FADB180(iStack_298, local_2b4, (int)pvVar15);
						sub_6FADB3D0(pvVar15, local_2b4, local_2ac);
						sub_6FADB5C0(&local_2ac, (int*)(local_2a4 + 1));
						TEXTURE_CelDraw(&local_290, local_2b4, 0x3c, 0xffffffff, DRAWMODE_TRANS50, nullptr);
						local_2b4 = local_2b4 + 0x38;
						pDVar10 = (D2CellFileStrc*)0x1;
					}
				}
				else if (cVar1 == '\x02')
				{
					iVar6 = sub_6FAB18F0((int)local_29c, (int)pvVar15);
					pDVar10 = nullptr;
					uVar9 = local_2a8;
					if (iVar6 != 0)
					{
						pDVar16 = &DStack_248;
						for (iVar14 = 0x12; iVar14 != 0; iVar14 = iVar14 + -1)
						{
							pDVar16->pCurrentCell = nullptr;
							pDVar16 = (D2GfxDataStrc*)&pDVar16->pCellFile;
						}
						local_2a4[0] = 0;
						DStack_248.pCellFile = sub_6FADA9E0((int)pDVar5, (int)pvVar15, &iStack_294, local_2a4);
						if (DStack_248.pCellFile == nullptr)
						{
							pDVar10 = nullptr;
							uVar9 = local_2a8;
						}
						else
						{
							if ((iVar6 == 1) && (local_2a4[0] != 0))
							{
								iVar6 = sub_6FAB1920((int)pDVar5, (int)pvVar15, 0);
								sub_6FADB180(iVar6, local_2b4, (int)pvVar15);
							}
							sub_6FADB4D0();
							sub_6FADB3D0(pvVar15, local_2b4, local_2ac);
							sub_6FADB5C0(&local_2ac, (int*)(local_2a4 + 1));
							TEXTURE_CelDraw(&DStack_248, local_2b4, 0x3c, 0xffffffff, DRAWMODE_TRANS50, nullptr);
							local_2b4 = local_2b4 + 0x38;
							pDVar10 = (D2CellFileStrc*)0x1;
							uVar9 = local_2a8;
						}
					}
				}
				else
				{
					if (cVar1 != '\x03')
						goto LAB_6fadb002;
					pDVar10 = sub_6FADB5F0((int)local_29c, (int)pvVar15, &local_2b4, &local_2ac,
					    (int*)(local_2a4 + 1));
				}
				local_2b0 = (D2CellFileStrc*)((uint32_t)local_2b0 | (uint32_t)pDVar10);
			}
		LAB_6fadb002:
			pvVar15 = (void*)((int)pvVar15 + 1);
			local_2a8 = uVar9 + 0xe0;
			iVar6 = *(int*)((uint8_t*)&sgptDataTables);
			iVar14 = *(int*)(iVar6 + 0xbf0);
		} while ((int)pvVar15 < iVar14);
	}
	if (local_2b0 == nullptr)
	{
		sub_6FB23260(0x13, 1, 0);
	}
	if (((byte_6FBB36A8 != '\0') && (iVar6 = sub_6FB23230(0x24), iVar6 == 0)) &&
	    (iVar6 = sub_6FB23260(0x24, 0, 0), iVar6 != 0))
	{
		SRegSaveValue("Diablo II", "PopupHireling", 0, 1);
		byte_6FBB36A8 = '\0';
	}
	if ((dword_6FBB36A4 != 0) && (dword_6FBB36A0 != 0))
	{
		aUStack_200[0].ch = 0;
		pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58a2));
		a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58a3));
		a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		pUVar13 = sub_6FAD56B0(0x36, 1);
		Unicode::sprintf(0x100, aUStack_200, a3, pUVar13);
		Unicode::strcat(aUStack_200, a2_00);
		Unicode::strcat(aUStack_200, pUVar12);
		D2Win_10129_DrawFramedText(aUStack_200, dword_6FBB3698, dword_6FBB369C + 0x24, 0, 0);
		return;
	}
}

//D2Client.0x6FADB180
void __fastcall sub_6FADB180(int a1, int a2, int a3)
{
	uint8_t bVar1;
	int iVar2;
	int nXEnd;

	if (a3 == 0)
	{
		iVar2 = sub_6FAB0AE0(a1);
	}
	else
	{
		iVar2 = sub_6FAB1AC0(a1);
	}
	if (iVar2 != 0)
	{
		if (iVar2 < 1)
		{
			iVar2 = 0;
		}
		else if (99 < iVar2)
		{
			iVar2 = 100;
		}
		nXEnd = (iVar2 * 0x2e) / 100 + a2;
		if (byte_6FBB3697 == '\0')
		{
			byte_6FBB3697 = '\x01';
			byte_6FBB3694 = D2Win_10034_MixRGB(0, 0x80, 0);
			byte_6FBB3695 = D2Win_10034_MixRGB(0xc0, 0xc0, 0);
			byte_6FBB3696 = D2Win_10034_MixRGB(0xff, 0, 0);
		}
		bVar1 = byte_6FBB3694;
		if (iVar2 < 0x32)
		{
			bVar1 = byte_6FBB3695;
		}
		if (iVar2 < 0x19)
		{
			bVar1 = byte_6FBB3696;
		}
		a3 = CONCAT31((*(uint8_t*)((uint8_t*)&a3 + 1)), bVar1);
		D2GFX_DrawBox(a2, 0xe, nXEnd, 0x13, a3, DRAWMODE_NORMAL);
		D2GFX_DrawBox(nXEnd, 0xe, a2 + 0x2e, 0x13, 0, DRAWMODE_NORMAL);
	}
}

//D2Client.0x6FADB280
void __fastcall sub_6FADB280(Unicode* pUnicode, int a2, int a3, int a4)
{
	Font nFontSize;
	int iVar1;
	Unicode* pUVar2;

	nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
	pUVar2 = pUnicode + 0x1f;
	iVar1 = D2Win_10121_GetTextWidth(pUnicode);
	while (0x42 < iVar1)
	{
		pUVar2 = pUVar2 + -1;
		pUVar2->ch = 0;
		iVar1 = D2Win_10121_GetTextWidth(pUnicode);
	}
	iVar1 = D2Win_10121_GetTextWidth(pUnicode);
	iVar1 = a2 + (0x16 - iVar1 / 2);
	if (iVar1 < 0)
	{
		iVar1 = 0;
	}
	D2Win_10117_DrawText(pUnicode, iVar1, a3, a4, 0);
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FADB300
void __fastcall sub_6FADB300(D2UnitStrc* pUnit, int a2, int a32)
{
	Unicode* pUVar1;
	Font nFontSize;
	uint16_t* puVar2;
	int iVar3;
	int a3;
	Unicode local_40[30];
	uint16_t auStack_4[2];

	if (pUnit != nullptr)
	{
		a3 = 0x20;
		pUVar1 = local_40;
		for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*(uint32_t*)pUVar1 = 0;
			pUVar1 = pUVar1 + 2;
		}
		pUVar1 = sub_6FB297F0(pUnit);
		Unicode::strncpy(local_40, pUVar1, a3);
		auStack_4[1] = 0;
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		puVar2 = auStack_4 + 1;
		iVar3 = D2Win_10121_GetTextWidth(local_40);
		while (0x42 < iVar3)
		{
			puVar2 = puVar2 + -1;
			*puVar2 = 0;
			iVar3 = D2Win_10121_GetTextWidth(local_40);
		}
		iVar3 = D2Win_10121_GetTextWidth(local_40);
		iVar3 = (a2 - iVar3 / 2) + 0x16;
		if (iVar3 < 0)
		{
			iVar3 = 0;
		}
		D2Win_10117_DrawText(local_40, iVar3, a32, 0, 0);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FADB3D0
void __fastcall sub_6FADB3D0(void* a1, int a2, int a3)
{
	Unicode* pUVar1;
	Font nFontSize;
	int iVar2;
	int iVar3;
	uint16_t* puVar4;
	Unicode local_40[30];
	uint16_t auStack_4[2];

	if ((((-1 < (int)a1) && ((int)a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0))) &&
	        (iVar3 = (int)a1 * 0xe0 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbe8), iVar3 != 0)) &&
	    ((*(short*)(iVar3 + 0xc) != 0 && (*(short*)(iVar3 + 0xc) != 0x1506))))
	{
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar3 + 0xc)));
		Unicode::strcpy(local_40, pUVar1);
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		puVar4 = auStack_4 + 1;
		iVar3 = D2Win_10121_GetTextWidth(local_40);
		while (0x42 < iVar3)
		{
			puVar4 = puVar4 + -1;
			*puVar4 = 0;
			iVar3 = D2Win_10121_GetTextWidth(local_40);
		}
		iVar3 = D2Win_10121_GetTextWidth(local_40);
		iVar3 = (a2 - iVar3 / 2) + 0x16;
		if (iVar3 < 0)
		{
			iVar3 = 0;
		}
		D2Win_10117_DrawText(local_40, iVar3, a3, 0, 0);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FADB4D0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FADB4D0()
{
	Font nFontSize;
	int in_EDX;
	Unicode* pUVar1;
	int iVar2;
	Unicode aUStack_a0[31];
	uint16_t uStack_62;
	char acStack_60[32];
	Unicode local_40[32];

	sprintf(acStack_60, "%d");
	pUVar1 = aUStack_a0;
	for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*(uint32_t*)pUVar1 = 0;
		pUVar1 = pUVar1 + 2;
	}
	Unicode::toUnicode(local_40, acStack_60, 0x20);
	Unicode::strncpy(aUStack_a0, local_40, 0x20);
	uStack_62 = 0;
	iVar2 = Unicode::strlen(aUStack_a0);
	pUVar1 = aUStack_a0 + iVar2;
	iVar2 = D2Win_10121_GetTextWidth(aUStack_a0);
	while (0x2e < iVar2)
	{
		pUVar1 = pUVar1 + -1;
		pUVar1->ch = 0;
		iVar2 = D2Win_10121_GetTextWidth(aUStack_a0);
	}
	nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
	D2Win_10117_DrawText(aUStack_a0, in_EDX + 8, 0x37, 0, 0);
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FADB5C0
void __fastcall sub_6FADB5C0(int* a1, int* a2)
{
	if (*a2 != 0)
	{
		*a1 = *a1 - *a2;
		*a2 = 0;
		return;
	}
	*a2 = 10;
	*a1 = *a1 + 10;
}

//D2Client.0x6FADB5F0
D2CellFileStrc* __fastcall sub_6FADB5F0(int a1, int a2, int* a3, int* a4, int* a5)
{
	uint8_t bVar1;
	int iVar2;
	Unicode* pUVar3;
	Font nFontSize;
	int iVar4;
	int nXEnd;
	uint16_t* puVar5;
	D2GfxDataStrc* pDVar6;
	uint32_t local_94;
	int local_90;
	int local_8c;
	Unicode aUStack_88[30];
	uint16_t auStack_4c[2];
	D2GfxDataStrc local_48;

	pDVar6 = &local_48;
	for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	local_8c = a2;
	local_48.pCellFile = sub_6FADA9E0(a1, a2, (int*)&local_94, nullptr);
	if (local_48.pCellFile == nullptr)
	{
		return nullptr;
	}
	iVar4 = *a3;
	if (a2 == 0)
	{
		iVar2 = sub_6FAB0AE0(local_94);
	}
	else
	{
		iVar2 = sub_6FAB1AC0(local_94);
	}
	if (iVar2 != 0)
	{
		local_90 = iVar4 + 0x2e;
		if (iVar2 < 1)
		{
			iVar2 = 0;
		}
		else if (99 < iVar2)
		{
			iVar2 = 100;
		}
		nXEnd = (iVar2 * 0x2e) / 100 + iVar4;
		if (byte_6FBB3697 == '\0')
		{
			byte_6FBB3697 = '\x01';
			byte_6FBB3694 = D2Win_10034_MixRGB(0, 0x80, 0);
			byte_6FBB3695 = D2Win_10034_MixRGB(0xc0, 0xc0, 0);
			byte_6FBB3696 = D2Win_10034_MixRGB(0xff, 0, 0);
			a2 = local_8c;
		}
		bVar1 = byte_6FBB3694;
		if (iVar2 < 0x32)
		{
			bVar1 = byte_6FBB3695;
		}
		if (iVar2 < 0x19)
		{
			bVar1 = byte_6FBB3696;
		}
		local_94 = CONCAT31((*(uint8_t*)((uint8_t*)&local_94 + 1)), bVar1);
		D2GFX_DrawBox(iVar4, 0xe, nXEnd, 0x13, local_94, DRAWMODE_NORMAL);
		D2GFX_DrawBox(nXEnd, 0xe, local_90, 0x13, 0, DRAWMODE_NORMAL);
	}
	local_90 = *a3;
	local_8c = *a4;
	if ((((-1 < a2) && (a2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbf0))) &&
	        (iVar4 = a2 * 0xe0 + *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbe8), iVar4 != 0)) &&
	    ((*(short*)(iVar4 + 0xc) != 0 && (*(short*)(iVar4 + 0xc) != 0x1506))))
	{
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar4 + 0xc)));
		Unicode::strcpy(aUStack_88, pUVar3);
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		puVar5 = auStack_4c + 1;
		iVar4 = D2Win_10121_GetTextWidth(aUStack_88);
		while (0x42 < iVar4)
		{
			puVar5 = puVar5 + -1;
			*puVar5 = 0;
			iVar4 = D2Win_10121_GetTextWidth(aUStack_88);
		}
		iVar4 = D2Win_10121_GetTextWidth(aUStack_88);
		iVar4 = (local_90 - iVar4 / 2) + 0x16;
		if (iVar4 < 0)
		{
			iVar4 = 0;
		}
		D2Win_10117_DrawText(aUStack_88, iVar4, local_8c, 0, 0);
		D2Win_10127_SetFont(nFontSize);
	}
	if (*a5 == 0)
	{
		*a5 = 10;
		*a4 = *a4 + 10;
	}
	else
	{
		*a4 = *a4 - *a5;
		*a5 = 0;
	}
	TEXTURE_CelDraw(&local_48, *a3, 0x3c, 0xffffffff, DRAWMODE_TRANS50, nullptr);
	*a3 = *a3 + 0x38;
	return (D2CellFileStrc*)0x1;
}

//D2Client.0x6FADB890
void __cdecl sub_6FADB890()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;

	if (dword_6FBB3690 == 2)
	{
		dword_6FBB36AC = 0;
		dword_6FBB36A4 = 0;
		dword_6FBB36A0 = 0;
		return;
	}
	pDVar1 = CUNIT_GetPlayer();
	iVar2 = sub_6FAB1970((int)pDVar1);
	iVar3 = sub_6FAB0D30((int*)pDVar1);
	if (((iVar3 == 0) || (dword_6FBB3690 == 1)) && (iVar2 == 0))
	{
		dword_6FBB36AC = 0;
		dword_6FBB36A4 = 0;
		dword_6FBB36A0 = 0;
		iVar2 = sub_6FB23230(0x13);
		if (iVar2 != 0)
		{
			sub_6FB23260(0x13, 1, 0);
		}
	}
	else
	{
		uVar4 = sub_6FAB1920((int)pDVar1, 7, 0);
		if ((uVar4 == 0xffffffff) ||
		    ((pDVar1 = sub_6FB269F0(uVar4, 1), pDVar1 != nullptr &&
		                                           (iVar2 = sub_6FB29550((int*)pDVar1), iVar2 != 0))))
		{
			dword_6FBB36AC = 0;
			dword_6FBB36A4 = 0;
			dword_6FBB36A0 = 0;
		}
		iVar2 = sub_6FB23230(0x13);
		if (iVar2 == 0)
		{
			sub_6FB23260(0x13, 0, 0);
			return;
		}
	}
}

//D2Client.0x6FADB980
void __cdecl sub_6FADB980(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;

	if (dword_6FBB3690 == 2)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
	pDVar1 = CUNIT_GetPlayer();
	iVar2 = sub_6FAB1920((int)pDVar1, 7, 0);
	if (iVar2 != -1)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	pDVar3 = sub_6FB269F0(0xffffffff, 1);
	if (pDVar3 == nullptr)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	sub_6FAB6430((int)pDVar1, (int)pDVar3, 1);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADBA00
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FADBA00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t extraout_ECX;

	iVar2 = sub_6FAAC080();
	if (iVar2 != 0)
	{
		uVar3 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
		uVar1 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		if ((((dword_6FBB3690 == 2) || ((int)uVar3 < dword_6FBB3698)) || (dword_6FBB3698 + 0x2e < (int)uVar3)) || ((uVar1 < 0x18 || (0x3c < uVar1))))
		{
			dword_6FBB36AC = 0;
			return;
		}
		iVar2 = sub_6FADBA90(1);
		if (iVar2 != 0)
		{
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x61), 0);
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FADBA90
// TODO: decompilation needs review (extraout)
int __fastcall sub_6FADBA90(int a1)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	uint32_t extraout_EDX_02;
	uint32_t extraout_EDX_03;
	uint32_t extraout_EDX_04;
	uint32_t extraout_EDX_05;
	uint32_t extraout_EDX_06;
	uint32_t extraout_EDX_07;
	uint32_t extraout_EDX_08;
	uint32_t extraout_EDX_09;
	uint32_t uVar7;

	iVar1 = sub_6FAAC080();
	if (iVar1 == 0)
	{
		return 0;
	}
	iVar1 = 0;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		return 0;
	}
	pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
	if (pDVar3 == nullptr)
	{
		return 0;
	}
	uVar4 = sub_6FAB1920((int)pDVar2, 7, 0);
	if (uVar4 == 0xffffffff)
	{
		return 0;
	}
	iVar5 = ITEMS_CheckItemFlag(pDVar3, 0x10, __LINE__, __FILE__);
	uVar7 = extraout_EDX;
	if ((iVar5 == 0) ||
	    (iVar5 = ITEMS_CheckItemFlag(pDVar3, 0x100, __LINE__, __FILE__),
	        uVar7 = extraout_EDX_00, iVar5 != 0))
	{
		if (a1 == 0)
		{
			return 0;
		}
		sub_6FB51920(uVar4, CONCAT31((int32_t)((uint32_t)uVar7 >> 8), 1), 0x56);
		return 0;
	}
	iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x4c);
	uVar7 = extraout_EDX_01;
	if (((iVar5 != 0) ||
	        (iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x50), uVar7 = extraout_EDX_02, iVar5 != 0)) ||
	    (iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x51), uVar7 = extraout_EDX_03, iVar5 != 0))
	{
		if (a1 != 0)
		{
			sub_6FB51920(uVar4, CONCAT31((int32_t)((uint32_t)uVar7 >> 8), 1), 0x54);
		}
		return 1;
	}
	iVar5 = ITEMS_CheckItemTypeId(pDVar3, 3);
	if ((iVar5 != 0) || (iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x25), iVar5 != 0))
	{
		iVar1 = 1;
	}
	pDVar2 = sub_6FB269F0(uVar4, 1);
	if (pDVar2 == nullptr)
	{
		return 0;
	}
	iVar5 = sub_6FAB1AE0(uVar4);
	uVar7 = extraout_EDX_04;
	if (iVar5 < 0x168)
	{
		if (iVar5 == 0x167)
		{
			iVar5 = ITEMS_CheckItemTypeId(pDVar3, 2);
			if (iVar5 != 0)
			{
				iVar1 = 1;
			}
			iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x1e);
			uVar7 = extraout_EDX_05;
			if (iVar5 != 0)
			{
				uVar6 = ITEMS_CheckWeaponIfTwoHanded(pDVar3);
				uVar7 = extraout_EDX_06;
			joined_r0x6fadbc34:
				if (uVar6 == 0)
					goto LAB_6fadbbe6;
			}
		}
		else
		{
			if (iVar5 == 0x10f)
			{
				iVar5 = 0x1b;
			}
			else
			{
				if (iVar5 != 0x152)
					goto LAB_6fadbc36;
				iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x21);
				if (iVar5 != 0)
					goto LAB_6fadbbe6;
				iVar5 = 0x22;
			}
		LAB_6fadbc14:
			iVar5 = ITEMS_CheckItemTypeId(pDVar3, iVar5);
			uVar7 = extraout_EDX_07;
			if (iVar5 != 0)
			{
			LAB_6fadbbe6:
				iVar1 = 1;
				goto LAB_6fadbbeb;
			}
		}
	}
	else if (iVar5 == 0x230)
	{
		iVar5 = ITEMS_CheckItemTypeId(pDVar3, 0x1c);
		uVar7 = extraout_EDX_08;
		if (iVar5 != 0)
		{
			uVar6 = ITEMS_CheckWeaponIfTwoHanded(pDVar3);
			uVar7 = extraout_EDX_09;
			goto joined_r0x6fadbc34;
		}
	}
	else if (iVar5 == 0x231)
	{
		iVar5 = 0x1e;
		goto LAB_6fadbc14;
	}
LAB_6fadbc36:
	if (iVar1 == 0)
	{
		if (a1 == 0)
		{
			return 0;
		}
		sub_6FB51920(uVar4, CONCAT31((int32_t)((uint32_t)uVar7 >> 8), 1), 0x55);
		return 0;
	}
LAB_6fadbbeb:
	iVar5 = ITEMS_CheckRequirements(pDVar3, pDVar2, 0, nullptr, nullptr, nullptr);
	if (iVar5 == 0)
	{
		iVar1 = 0;
	}
	return iVar1;
}

//D2Client.0x6FADBC90
void __cdecl sub_6FADBC90(int a1)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	DWORD DVar3;

	iVar1 = sub_6FAAC080();
	if (iVar1 == 0)
	{
		return;
	}
	*(uint32_t*)(a1 + 0x18) = 0;
	dword_6FBB36A4 = 0;
	if ((((dword_6FBB3690 != 2) && (dword_6FBB3698 <= (int)(uint32_t) * (uint16_t*)(a1 + 0xc))) &&
	        ((int)(uint32_t) * (uint16_t*)(a1 + 0xc) <= dword_6FBB3698 + 0x2e)) &&
	    ((0x17 < *(uint16_t*)(a1 + 0xe) && (*(uint16_t*)(a1 + 0xe) < 0x3d))))
	{
		if (dword_6FBB36AC == 0)
		{
			dword_6FBB36AC = GetTickCount();
		}
		pDVar2 = CUNIT_GetPlayer();
		if ((pDVar2 == nullptr) ||
		    (pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory), pDVar2 == nullptr))
		{
			iVar1 = 0;
			pDVar2 = CUNIT_GetPlayer();
			iVar1 = sub_6FAB1920((int)pDVar2, 7, iVar1);
			if (iVar1 != -1)
			{
				dword_6FBB36A4 = 1;
				DVar3 = GetTickCount();
				if (699 < DVar3 - dword_6FBB36AC)
				{
					dword_6FBB36A0 = 1;
				}
			}
		}
		iVar1 = sub_6FADBA90(0);
		if (iVar1 != 0)
		{
			dword_6FBB36A0 = 1;
		}
		return;
	}
	dword_6FBB36A0 = 0;
	dword_6FBB36AC = 0;
}

//D2Client.0x6FADBD70
void __cdecl sub_6FADBD70()
{
	int iVar1;

	if (dword_6FBB3690 == 0)
	{
		iVar1 = sub_6FAABFF0();
		if (iVar1 == 0)
		{
			dword_6FBB3690 = 2;
			dword_6FBB36AC = 0;
			sub_6FB23260(0x23, 1, 0);
			return;
		}
		dword_6FBB3690 = 1;
		sub_6FB23260(0x23, 0, 0);
		return;
	}
	if (dword_6FBB3690 != 1)
	{
		dword_6FBB3690 = 0;
		sub_6FB23260(0x23, 0, 0);
		return;
	}
	iVar1 = sub_6FAABFF0();
	if (iVar1 == 0)
	{
		dword_6FBB3690 = 0;
		sub_6FB23260(0x23, 0, 0);
		return;
	}
	dword_6FBB3690 = 2;
	dword_6FBB36AC = 0;
	sub_6FB23260(0x23, 1, 0);
}

//D2Client.0x6FADBE20
void __cdecl sub_6FADBE20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	int iVar2;
	uint32_t uVar3;
	DWORD DVar4;
	D2UnitStrc* pDVar5;

	iVar2 = sub_6FAAC080();
	if (iVar2 == 0)
	{
		return;
	}
	uVar3 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar1 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	pSMSGHANDLER_PARAMS->bUseResult = 0;
	if ((((dword_6FBB3690 != 2) && (dword_6FBB3698 <= (int)uVar3)) && ((int)uVar3 <= dword_6FBB3698 + 0x2e)) && ((0x17 < uVar1 && (uVar1 < 0x3d))))
	{
		if (dword_6FBB36AC == 0)
		{
			dword_6FBB36AC = GetTickCount();
		}
		DVar4 = GetTickCount();
		if (699 < DVar4 - dword_6FBB36AC)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			iVar2 = sub_6FB23230(0x23);
			if (iVar2 == 0)
			{
				return;
			}
			iVar2 = sub_6FB23230(0x24);
			if (iVar2 != 0)
			{
				return;
			}
			iVar2 = 0;
			pDVar5 = CUNIT_GetPlayer();
			iVar2 = sub_6FAB1920((int)pDVar5, 7, iVar2);
			if (iVar2 == -1)
			{
				return;
			}
			sub_6FB23260(0x24, 0, 0);
		}
	}
	dword_6FBB36AC = 0;
}

//D2Client.0x6FADBF00
void __cdecl sub_6FADBF00()
{
	uint32_t local_4;

	dword_6FBB3690 = 0;
	sub_6FB23260(0x23, 0, 0);
	local_4 = 0;
	SRegLoadValue("Diablo II", "PopupHireling", 0, (DWORD*)(&local_4));
	if (local_4 == 0)
	{
		byte_6FBB36A8 = '\x01';
	}
}

//D2Client.0x6FADBF50
bool __cdecl sub_6FADBF50(uint32_t a1)
{
	int iVar1;
	Font FVar2;
	Unicode* pUVar3;
	D2GfxDataStrc* pDVar4;
	D2SkillsTxt* pDVar5;
	D2GfxDataStrc DStack_48;

	sub_6FAAD3B0();
	iVar1 = WINDOW_GetState();
	if (iVar1 == 0)
	{
		iVar1 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar1 != 0)
		{
			D2GFX_ClearScreen(0);
			D2Win_10179();
			pDVar4 = &DStack_48;
			for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				pDVar4->pCurrentCell = 0;
				pDVar4 = (D2GfxDataStrc*)((int)pDVar4 + 4);
			}
			DStack_48.pCellFile = gpCellFile_6FBB36B4;
			DStack_48.nDirection = 0;
			DStack_48.nFrame = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xbc, 0x148 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = 1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x1bc, 0x148 - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar5 = nullptr;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1430));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xbe - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar3, pDVar5);
			iVar1 = FOG_IsExpansion();
			pDVar5 = nullptr;
			if (iVar1 == 0)
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1431));
			}
			else
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5578));
			}
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xcd - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar3, pDVar5);
			D2Win_10127_SetFont(FVar2);
			pDVar4 = &DStack_48;
			for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				pDVar4->pCurrentCell = nullptr;
				pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
			}
			DStack_48.nDirection = 0;
			DStack_48.pCellFile = gpCellFile_6FBB36B8;
			DStack_48.nFrame = dword_6FBB36C4;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x110, 0x13e - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar5 = nullptr;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
			sub_6FACFCD0(dword_6FBBA748 + 0x110, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x170, pUVar3, pDVar5);
			D2Win_10127_SetFont(FVar2);
			sub_6FB57AC0();
			D2GFX_EndScene();
		}
	}
	sub_6FB54C60();
	return dword_6FBB36CC != 0;
}

//D2Client.0x6FADC180
void __cdecl sub_6FADC180()
{
	int iVar1;
	Font FVar2;
	Unicode* pUVar3;
	D2GfxDataStrc* pDVar4;
	D2SkillsTxt* pDVar5;
	D2GfxDataStrc DStack_48;

	iVar1 = WINDOW_GetState();
	if (iVar1 == 0)
	{
		iVar1 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar1 != 0)
		{
			D2GFX_ClearScreen(0);
			D2Win_10179();
			pDVar4 = &DStack_48;
			for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				pDVar4->pCurrentCell = 0;
				pDVar4 = (D2GfxDataStrc*)((int)pDVar4 + 4);
			}
			DStack_48.pCellFile = gpCellFile_6FBB36B4;
			DStack_48.nDirection = 0;
			DStack_48.nFrame = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xbc, 0x148 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = 1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x1bc, 0x148 - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar5 = nullptr;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1430));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xbe - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar3, pDVar5);
			iVar1 = FOG_IsExpansion();
			pDVar5 = nullptr;
			if (iVar1 == 0)
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1431));
			}
			else
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x5578));
			}
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xcd - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar3, pDVar5);
			D2Win_10127_SetFont(FVar2);
			pDVar4 = &DStack_48;
			for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				pDVar4->pCurrentCell = nullptr;
				pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
			}
			DStack_48.nDirection = 0;
			DStack_48.pCellFile = gpCellFile_6FBB36B8;
			DStack_48.nFrame = dword_6FBB36C4;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x110, 0x13e - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar5 = nullptr;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
			sub_6FACFCD0(dword_6FBBA748 + 0x110, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x170, pUVar3, pDVar5);
			D2Win_10127_SetFont(FVar2);
			sub_6FB57AC0();
			D2GFX_EndScene();
			return;
		}
	}
}

//D2Client.0x6FADC390
BOOL __stdcall sub_6FADC390()
{
	HWND__* pHVar1;
	uint32_t uVar2;

	dword_6FBB36CC = 0;
	D2Win_10176(0);
	gpCellFile_6FBB36B4 = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36BC = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36B8 = CLIENT_LoadCellFile((const char*)(dword_6FB79247 + 1), 0);
	D2Win_10177(0);
	sub_6FAA9620(1);
	uVar2 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB791E8), uVar2);
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FADBF50));
	uVar2 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB791E8), uVar2);
	sub_6FAA9620(0);
	if (gpCellFile_6FBB36B4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B4);
		gpCellFile_6FBB36B4 = nullptr;
	}
	if (gpCellFile_6FBB36BC != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36BC);
		gpCellFile_6FBB36BC = nullptr;
	}
	if (gpCellFile_6FBB36B8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B8);
		gpCellFile_6FBB36B8 = nullptr;
	}
	sub_6FB24150();
	return 1;
}

//D2Client.0x6FADC470
BOOL __stdcall sub_6FADC470()
{
	HWND__* pHVar1;
	uint32_t uVar2;

	dword_6FBB36CC = 0;
	D2Win_10176(0);
	gpCellFile_6FBB36B4 = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36BC = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36B8 = CLIENT_LoadCellFile((const char*)(dword_6FB79247 + 1), 0);
	D2Win_10177(0);
	sub_6FAA9620(1);
	uVar2 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB791E8), uVar2);
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FADBF50));
	uVar2 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB791E8), uVar2);
	sub_6FAA9620(0);
	if (gpCellFile_6FBB36B4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B4);
		gpCellFile_6FBB36B4 = nullptr;
	}
	if (gpCellFile_6FBB36BC != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36BC);
		gpCellFile_6FBB36BC = nullptr;
	}
	if (gpCellFile_6FBB36B8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B8);
		gpCellFile_6FBB36B8 = nullptr;
	}
	sub_6FB24150();
	return 1;
}

//D2Client.0x6FADC550
void __cdecl sub_6FADC550(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar3 = dword_6FBBA748;
	iVar2 = -dword_6FBBA74C;
	iVar1 = dword_6FBBA748 + 0x110;
	iVar4 = sub_6FB57BC0();
	iVar5 = sub_6FB57BD0();
	if ((((iVar1 <= iVar4) && (iVar4 <= iVar3 + 0x170)) && (iVar2 + 0x116 <= iVar5)) &&
	    (iVar5 <= iVar2 + 0x136))
	{
		dword_6FBB36C4 = 1;
		dword_6FBB36C0 = 1;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADC5F0
void __cdecl sub_6FADC5F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;

	iVar3 = dword_6FBBA748;
	dword_6FBB36C4 = 0;
	if (dword_6FBB36C0 != 0)
	{
		iVar2 = -dword_6FBBA74C;
		iVar1 = dword_6FBBA748 + 0x110;
		iVar4 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		if ((((iVar1 <= iVar4) && (iVar4 <= iVar3 + 0x170)) && (iVar2 + 0x116 <= iVar5)) &&
		    (iVar5 <= iVar2 + 0x136))
		{
			dword_6FBB36CC = 1;
			dword_6FBB36C0 = 0;
			pSMSGHANDLER_PARAMS->lResult = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADC690
void __cdecl sub_6FADC690(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	dword_6FBB36CC = 1;
	dword_6FBB36C0 = 0;
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADC6D0
void __cdecl sub_6FADC6D0(uint32_t a1)
{
	dword_6FBB36CC = 0;
}

//D2Client.0x6FADC6E0
uint32_t __cdecl sub_6FADC6E0(uint32_t a1)
{
	uint32_t uVar1;
	int iVar2;
	Font FVar3;
	Unicode* pUVar4;
	short index;
	D2GfxDataStrc* pDVar5;
	D2SkillsTxt* pDVar6;
	D2GfxDataStrc DStack_48;

	sub_6FAAD3B0();
	iVar2 = WINDOW_GetState();
	if (iVar2 == 0)
	{
		iVar2 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar2 != 0)
		{
			D2GFX_ClearScreen(0);
			D2Win_10179();
			pDVar5 = &DStack_48;
			for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				pDVar5->pCurrentCell = 0;
				pDVar5 = (D2GfxDataStrc*)((int)pDVar5 + 4);
			}
			DStack_48.pCellFile = gpCellFile_6FBB36BC;
			DStack_48.nDirection = 0;
			DStack_48.nFrame = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xbc, 0x148 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = 1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x1bc, 0x148 - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar3 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1430));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xbe - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar4, pDVar6);
			index = 0x1432;
			if (dword_6FBB36B0 != 0)
			{
				index = 0x5578;
			}
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xcd - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar4, pDVar6);
			D2Win_10127_SetFont(FVar3);
			uVar1 = dword_6FBB36C8;
			pDVar5 = &DStack_48;
			for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				pDVar5->pCurrentCell = nullptr;
				pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
			}
			DStack_48.pCellFile = gpCellFile_6FBB36B8;
			DStack_48.nFrame = dword_6FBB36C4;
			DStack_48.nDirection = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xce, 0x13e - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = uVar1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x152, 0x13e - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar3 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
			sub_6FACFCD0(dword_6FBBA748 + 0xce, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x12e, pUVar4, pDVar6);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ef));
			sub_6FACFCD0(dword_6FBBA748 + 0x152, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x1b2, pUVar4, pDVar6);
			D2Win_10127_SetFont(FVar3);
			sub_6FB57AC0();
			D2GFX_EndScene();
		}
	}
	sub_6FB54C60();
	if ((dword_6FBB36D0 == 0) && (dword_6FBB36D4 == 0))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FADC970
void __cdecl sub_6FADC970()
{
	uint32_t uVar1;
	int iVar2;
	Font FVar3;
	Unicode* pUVar4;
	short index;
	D2GfxDataStrc* pDVar5;
	D2SkillsTxt* pDVar6;
	D2GfxDataStrc DStack_48;

	iVar2 = WINDOW_GetState();
	if (iVar2 == 0)
	{
		iVar2 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar2 != 0)
		{
			D2GFX_ClearScreen(0);
			D2Win_10179();
			pDVar5 = &DStack_48;
			for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				pDVar5->pCurrentCell = 0;
				pDVar5 = (D2GfxDataStrc*)((int)pDVar5 + 4);
			}
			DStack_48.pCellFile = gpCellFile_6FBB36BC;
			DStack_48.nDirection = 0;
			DStack_48.nFrame = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xbc, 0x148 - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = 1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x1bc, 0x148 - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar3 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1430));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xbe - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar4, pDVar6);
			index = 0x1432;
			if (dword_6FBB36B0 != 0)
			{
				index = 0x5578;
			}
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
			sub_6FACFCD0(gnScreenWidth / 2 + -0x84, 0xcd - dword_6FBBA74C, dword_6FBBA748 + 0x1c4, pUVar4, pDVar6);
			D2Win_10127_SetFont(FVar3);
			uVar1 = dword_6FBB36C8;
			pDVar5 = &DStack_48;
			for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				pDVar5->pCurrentCell = nullptr;
				pDVar5 = (D2GfxDataStrc*)&pDVar5->pCellFile;
			}
			DStack_48.pCellFile = gpCellFile_6FBB36B8;
			DStack_48.nFrame = dword_6FBB36C4;
			DStack_48.nDirection = 0;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0xce, 0x13e - dword_6FBBA74C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			DStack_48.nFrame = uVar1;
			TEXTURE_CelDraw(&DStack_48, dword_6FBBA748 + 0x152, 0x13e - dword_6FBBA74C, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			FVar3 = D2Win_10127_SetFont(D2FONT_FONT16);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ee));
			sub_6FACFCD0(dword_6FBBA748 + 0xce, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x12e, pUVar4, pDVar6);
			pDVar6 = nullptr;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13ef));
			sub_6FACFCD0(dword_6FBBA748 + 0x152, 0x136 - dword_6FBBA74C, dword_6FBBA748 + 0x1b2, pUVar4, pDVar6);
			D2Win_10127_SetFont(FVar3);
			sub_6FB57AC0();
			D2GFX_EndScene();
			return;
		}
	}
}

//D2Client.0x6FADCBD0
BOOL __stdcall sub_6FADCBD0()
{
	HWND__* pHVar1;
	bool bVar2;
	uint32_t uVar3;

	dword_6FBB36D4 = 0;
	dword_6FBB36D0 = 0;
	D2Win_10176(0);
	gpCellFile_6FBB36B4 = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36BC = CLIENT_LoadCellFile("Data\\Global\\UI\\Bigmenu\\popupok", 0);
	gpCellFile_6FBB36B8 = CLIENT_LoadCellFile((const char*)(dword_6FB79247 + 1), 0);
	D2Win_10177(0);
	sub_6FAA9620(2);
	uVar3 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB79218), uVar3);
	CLIENT_RunMessageLoop((CLIENT_IdleCallback)(sub_6FADC6E0));
	bVar2 = dword_6FBB36D4 == 0;
	uVar3 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB79218), uVar3);
	sub_6FAA9620(0);
	if (gpCellFile_6FBB36B4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B4);
		gpCellFile_6FBB36B4 = nullptr;
	}
	if (gpCellFile_6FBB36BC != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36BC);
		gpCellFile_6FBB36BC = nullptr;
	}
	if (gpCellFile_6FBB36B8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB36B8);
		gpCellFile_6FBB36B8 = nullptr;
	}
	sub_6FB24150();
	return bVar2;
}

//D2Client.0x6FADCCC0
void __cdecl sub_6FADCCC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar6 = dword_6FBBA748;
	iVar2 = -dword_6FBBA74C;
	iVar1 = dword_6FBBA748 + 0xce;
	iVar4 = sub_6FB57BC0();
	iVar5 = sub_6FB57BD0();
	iVar3 = dword_6FBBA748;
	if ((((iVar4 < iVar1) || (iVar6 + 0x12e < iVar4)) || (iVar5 < iVar2 + 0x116)) ||
	    (iVar2 + 0x136 < iVar5))
	{
		iVar2 = -dword_6FBBA74C;
		iVar1 = dword_6FBBA748 + 0x152;
		iVar6 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		if (((iVar6 < iVar1) || (iVar3 + 0x1b2 < iVar6)) ||
		    ((iVar4 < iVar2 + 0x116 || (iVar2 + 0x136 < iVar4))))
		{
			sub_6FAABF60();
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		dword_6FBB36C8 = 1;
	}
	else
	{
		dword_6FBB36C4 = 1;
	}
	dword_6FBB36C0 = 1;
	sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADCDB0
void __cdecl sub_6FADCDB0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar2 = dword_6FBBA748;
	dword_6FBB36C4 = 0;
	dword_6FBB36C8 = 0;
	if (dword_6FBB36C0 != 0)
	{
		iVar6 = -dword_6FBBA74C;
		iVar1 = dword_6FBBA748 + 0xce;
		iVar4 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		iVar3 = dword_6FBBA748;
		if ((((iVar1 <= iVar4) && (iVar4 <= iVar2 + 0x12e)) && (iVar6 + 0x116 <= iVar5)) &&
		    (iVar5 <= iVar6 + 0x136))
		{
			dword_6FBB36D0 = 1;
			dword_6FBB36C0 = 0;
		}
		iVar1 = -dword_6FBBA74C;
		iVar2 = dword_6FBBA748 + 0x152;
		iVar6 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		if (((iVar2 <= iVar6) && (iVar6 <= iVar3 + 0x1b2)) &&
		    ((iVar1 + 0x116 <= iVar4 && (iVar4 <= iVar1 + 0x136))))
		{
			dword_6FBB36D4 = 1;
			dword_6FBB36C0 = 0;
		}
		pSMSGHANDLER_PARAMS->lResult = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADCEB0
void __cdecl sub_6FADCEB0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	dword_6FBB36D0 = 1;
	dword_6FBB36C0 = 0;
	sub_6FAABF60();
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FADCEF0
void __cdecl sub_6FADCEF0(uint32_t a1)
{
	dword_6FBB36D4 = 1;
}

//D2Client.0x6FADCF00
void __fastcall sub_6FADCF00(BOOL a1)
{
	dword_6FBB36B0 = a1;
}

//D2Client.0x6FADCF10
void __fastcall sub_6FADCF10(short* a1, int a2, Unicode* pUnicode)
{
	short* psVar1;
	Unicode* pThis;
	int iVar2;
	int iVar3;
	Unicode local_320[400];

	iVar3 = Unicode::strlen((Unicode*)a1);
	iVar2 = 0;
	if (0 < iVar3 + -1)
	{
		psVar1 = a1;
		while ((*psVar1 != 0x25 || ((uint32_t)(uint16_t)psVar1[1] != a2 + 0x30U)))
		{
			*(short*)(((int)local_320 - (int)a1) + (int)psVar1) = *psVar1;
			iVar2 = iVar2 + 1;
			psVar1 = psVar1 + 1;
			if (iVar3 + -1 <= iVar2)
			{
				return;
			}
		}
		Unicode::strcat(local_320, pUnicode);
		iVar3 = Unicode::strlen(local_320);
		if ((local_320[iVar3 + -1].ch != 0x20) || (iVar3 = iVar2 + 3, a1[iVar2 + 2] != 0x20))
		{
			iVar3 = iVar2 + 2;
		}
		Unicode::strcat(local_320, (Unicode*)(a1 + iVar3));
		Unicode::strcpy((Unicode*)a1, local_320);
	}
}

//D2Client.0x6FADCFE0
// TODO: decompilation needs review (in_stack, stack0x, unaff_)
void __cdecl sub_6FADCFE0(Unicode* pUnicode, char* a22, Unicode* pUnicode2, Unicode* pUnicode3, uint16_t a5)
{
	uint8_t stack0x0000001c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000000e4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000000ec[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000000f0[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000109c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffff4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	Unicode* pUVar1;
	uint16_t a2;
	uint32_t unaff_EBX;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint8_t* puVar6;
	int unaff_retaddr;
	Unicode* in_stack_00001088;
	Unicode* in_stack_00001098;
	Unicode* in_stack_0000109c;
	Unicode* pUVar7;

	if (in_stack_00001098 == nullptr)
	{
		return;
	}
	pUVar2 = (Unicode*)stack0x000000f0;
	iVar5 = 2000;
	do
	{
		pUVar2 = pUVar2 + 1;
		iVar5 = iVar5 + -1;
	} while (iVar5 != 0);
	pUVar2 = nullptr;
	pUnicode2 = nullptr;
	if (in_stack_0000109c != nullptr)
	{
		puVar6 = stack0x0000109c;
		pUVar1 = (Unicode*)stack0x000000f0;
		do
		{
			pUVar2 = (Unicode*)((int)&pUVar2->ch + 1);
			Unicode::strcpy(pUVar1, in_stack_0000109c);
			in_stack_0000109c = *(Unicode**)(puVar6 + 4);
			puVar6 = puVar6 + 4;
			pUVar1 = pUVar1 + 200;
		} while (in_stack_0000109c != nullptr);
		in_stack_0000109c = nullptr;
		pUnicode2 = pUVar2;
	}
	a22 = (char*)CONCAT22((*(uint16_t*)((uint8_t*)&a22 + 2)), 0x3a);
	pUVar2 = Unicode::strchr(in_stack_00001098, (uint16_t)in_stack_0000109c);
	pUnicode = pUVar2;
	if (pUVar2 != nullptr)
	{
		pUVar7 = (Unicode*)CONCAT22((short)((uint32_t)unaff_EBX >> 0x10), 0x61);
		pUnicode2 = (Unicode*)0x6d005b;
		pUnicode3 = (Unicode*)0x5d0073;
		a5 = 0;
		iVar5 = -1;
		pUVar1 = Unicode::strchr(in_stack_00001098, a2);
		if ((pUVar1 != nullptr) && (pUVar1 < pUVar2))
		{
			iVar5 = pUVar1[1].ch - 0x30;
		}
		iVar4 = -1;
		pUVar2 = Unicode::strchr(in_stack_00001098, 0x6e);
		if ((pUVar2 != nullptr) && (pUVar2 < pUVar7))
		{
			iVar4 = pUVar2[1].ch - 0x30;
		}
		if (iVar5 == -1)
		{
			if (iVar4 != -1)
			{
				Unicode::strcpy((Unicode*)(stack0x000000e4 + iVar4 * 400),
				    (Unicode*)(stack0x000000ec + iVar4 * 400));
			}
		}
		else if (iVar4 == -1)
		{
			pUVar2 = (Unicode*)stack0x0000001c;
			iVar4 = 100;
			do
			{
				pUVar2 = pUVar2 + 1;
				iVar4 = iVar4 + -1;
			} while (iVar4 != 0);
			pUVar2 = Unicode::strstr((Unicode*)(stack0x000000e4 + iVar5 * 400), (Unicode*)&pUnicode);
			if (pUVar2 != nullptr)
			{
				pUVar2 = pUVar2 + 4;
				iVar4 = Unicode::strlen(pUVar2);
				pUVar1 = Unicode::strstr(pUVar2, (Unicode*)stack0xfffffff4);
				iVar3 = Unicode::strlen(pUVar1);
				Unicode::strncpy((Unicode*)stack0x0000001c, pUVar2, iVar4 - iVar3);
				Unicode::strcpy((Unicode*)(stack0x000000e4 + iVar5 * 400), (Unicode*)stack0x0000001c);
				in_stack_00001098 = pUVar7 + 1;
				goto LAB_6fadd2a2;
			}
		}
		else
		{
			pUVar2 = (Unicode*)&pUnicode3;
			iVar3 = 5;
			do
			{
				pUVar2 = pUVar2 + 1;
				iVar3 = iVar3 + -1;
			} while (iVar3 != 0);
			pUVar2 = (Unicode*)&pUnicode3;
			iVar4 = iVar4 * 400;
			if (*(short*)(stack0x000000e4 + iVar4) == 0x5b)
			{
				Unicode::strncpy(pUVar2, (Unicode*)(stack0x000000e4 + iVar4), 4);
				pUVar1 = (Unicode*)(stack0x000000ec + iVar4);
				pUVar2 = (Unicode*)(stack0x000000e4 + iVar4);
			}
			else
			{
				pUVar1 = (Unicode*)&pUnicode;
			}
			Unicode::strcpy(pUVar2, pUVar1);
			if (*(short*)(stack0x000000e4 + iVar5 * 400) == 0x5b)
			{
				pUVar2 = (Unicode*)stack0x0000001c;
				iVar4 = 100;
				do
				{
					pUVar2 = pUVar2 + 1;
					iVar4 = iVar4 + -1;
				} while (iVar4 != 0);
				pUVar2 = Unicode::strstr((Unicode*)(stack0x000000e4 + iVar5 * 400), (Unicode*)&pUnicode3);
				if (pUVar2 != nullptr)
				{
					pUVar2 = pUVar2 + 4;
					iVar4 = Unicode::strlen(pUVar2);
					pUVar1 = Unicode::strstr(pUVar2, (Unicode*)stack0xfffffff4);
					iVar3 = Unicode::strlen(pUVar1);
					Unicode::strncpy((Unicode*)stack0x0000001c, pUVar2, iVar4 - iVar3);
					Unicode::strcpy((Unicode*)(stack0x000000e4 + iVar5 * 400), (Unicode*)stack0x0000001c);
					in_stack_00001098 = pUVar7 + 1;
					goto LAB_6fadd2a2;
				}
			}
		}
		in_stack_00001098 = pUVar7 + 1;
	}
LAB_6fadd2a2:
	Unicode::strcpy(in_stack_00001088, in_stack_00001098);
	iVar5 = 0;
	if (0 < unaff_retaddr)
	{
		puVar6 = stack0x000000e4;
		do
		{
			sub_6FADCF10((short*)in_stack_00001088, iVar5, (Unicode*)(puVar6));
			iVar5 = iVar5 + 1;
			puVar6 = puVar6 + 400;
		} while (iVar5 < unaff_retaddr);
	}
}

//D2Client.0x6FADD2F0
void __cdecl sub_6FADD2F0()
{
	byte_6FBB3778 = D2Win_10034_MixRGB(0x80, 0, 0);
	byte_6FBB3779 = D2Win_10034_MixRGB(0, 0x80, 0);
	byte_6FBB377A = D2Win_10034_MixRGB(0, 0, 0x80);
	byte_6FBB377B = D2Win_10034_MixRGB(0x80, 0x80, 0);
	byte_6FBB377C = D2Win_10034_MixRGB(0x80, 0x40, 0x40);
}

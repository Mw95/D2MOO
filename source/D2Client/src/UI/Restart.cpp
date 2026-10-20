#include "UI/Restart.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Panel.h"
#include "UI/QuestLog.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"

//D2Client.0x6FB7DE68
uint32_t dword_6FB7DE68;
//D2Client.0x6FB7DE6C
uint32_t dword_6FB7DE6C;
//D2Client.0x6FB7DF6C
int32_t dword_6FB7DF6C;
//D2Client.0x6FB7E030
uint32_t dword_6FB7E030 = 3;
//D2Client.0x6FB7E048
uint8_t byte_6FB7E048;
//D2Client.0x6FB7F038
uint32_t dword_6FB7F038 = 5;
//D2Client.0x6FB7F050
uint8_t byte_6FB7F050;
//D2Client.0x6FB80AE0
uint32_t dword_6FB80AE0 = 8;
//D2Client.0x6FB80AF8
uint8_t byte_6FB80AF8 = 0xFF;
//D2Client.0x6FB83578
uint32_t dword_6FB83578 = 7;
//D2Client.0x6FB83590
uint8_t byte_6FB83590 = 0xFF;
//D2Client.0x6FB85AC0
uint32_t dword_6FB85AC0 = 8;
//D2Client.0x6FB85AD8
uint8_t byte_6FB85AD8 = 0xFF;
//D2Client.0x6FB88558
uint32_t dword_6FB88558 = 6;
//D2Client.0x6FB88570
uint8_t byte_6FB88570 = 0xFF;
//D2Client.0x6FB8A550
uint32_t dword_6FB8A550 = 7;
//D2Client.0x6FB8A568
uint8_t byte_6FB8A568 = 0xFF;
//D2Client.0x6FBB6F38
uint32_t dword_6FBB6F38;
//D2Client.0x6FBB6F58
uint32_t dword_6FBB6F58;
//D2Client.0x6FBB6F78
uint32_t dword_6FBB6F78;
//D2Client.0x6FBB6F98
uint32_t dword_6FBB6F98;
//D2Client.0x6FBB6FB8
uint32_t dword_6FBB6FB8;
//D2Client.0x6FBB6FDC
int32_t* sgptMenuInfo;
//D2Client.0x6FBB6FE4
uint32_t dword_6FBB6FE4;
//D2Client.0x6FBB6FF0
D2CellFileStrc* gpCellFile_6FBB6FF0;
//D2Client.0x6FBB6FF4
D2CellFileStrc* gpCellFile_6FBB6FF4;
//D2Client.0x6FBB6FF8
D2CellFileStrc* gpCellFile_6FBB6FF8;
//D2Client.0x6FBB6FFC
int32_t dword_6FBB6FFC;
//D2Client.0x6FBB7000
int32_t dword_6FBB7000;
//D2Client.0x6FBB7004
int32_t dword_6FBB7004;
//D2Client.0x6FBB7008
D2CellFileStrc* gpCellFile_6FBB7008;
//D2Client.0x6FBB700C
D2CellFileStrc* gpCellFile_6FBB700C;
//D2Client.0x6FBB7010
int32_t dword_6FBB7010;
//D2Client.0x6FBB7014
int32_t dword_6FBB7014;
//D2Client.0x6FBB7018
int32_t dword_6FBB7018;
//D2Client.0x6FBB701C
uint8_t byte_6FBB701C;
//D2Client.0x6FBB7020
int32_t dword_6FBB7020;
//D2Client.0x6FBB7024
uint32_t dword_6FBB7024;
//D2Client.0x6FBB703C
uint16_t word_6FBB703C[128];

//D2Client.0x6FB081D0
void __fastcall sub_6FB081D0(int* ptMenuInfo, int ptMenuItem)
{
	uint32_t uVar1;
	int iVar2;
	D2CellFileStrc* pDVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	uint32_t* puVar8;
	char local_114[4];
	int iStack_110;
	int local_10c;
	int* local_108;
	char local_104;
	uint32_t local_103;

	local_10c = ptMenuItem;
	local_108 = ptMenuInfo;
	D2_ASSERT(ptMenuInfo != nullptr);
	D2_ASSERT(ptMenuItem);
	local_104 = byte_6FB9A828;
	local_114[0] = byte_6FB9A828;
	puVar7 = &local_103;
	for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar7 = 0;
		puVar7 = puVar7 + 1;
	}
	*(uint16_t*)puVar7 = 0;
	*(uint8_t*)((int)puVar7 + 2) = 0;
	local_114[1] = '\0';
	local_114[2] = '\0';
	local_114[3] = 0;
	D2LANG_10006((char*)((int)local_114), 0);
	iStack_110 = 0;
	if (0 < *ptMenuInfo)
	{
		iVar4 = 0x150;
		puVar5 = (uint32_t*)(ptMenuItem + 0x120);
		do
		{
			if (puVar5[-0x47] == 0)
			{
			LAB_6fb08297:
				if ((char)puVar5[-0x45] != '\0')
				{
					sprintf(&local_104, "%s\\UI\\%s\\%s", "DATA\\LOCAL", local_114, puVar5 + -0x45);
					pDVar3 = CLIENT_LoadCellFile(&local_104, 0);
					puVar5[0x107] = (uint32_t)pDVar3;
					if (puVar5[-0x48] == 1)
					{
						uVar1 = *puVar5;
						D2_ASSERT(!((uVar1 == 0) || (4 < uVar1)));
						uVar6 = 0;
						if (uVar1 != 0)
						{
							puVar8 = puVar5 + 3;
							do
							{
								D2_ASSERT((char)*puVar8 != '\0');
								sprintf(&local_104, "%s\\UI\\%s\\%s", "DATA\\LOCAL", local_114, puVar8);
								pDVar3 = CLIENT_LoadCellFile(&local_104, 0);
								iVar2 = uVar6 + iVar4;
								uVar6 = uVar6 + 1;
								puVar8 = puVar8 + 0x41;
								*(D2CellFileStrc**)(local_10c + iVar2 * 4) = pDVar3;
							} while (uVar6 < *puVar5);
						}
					}
				}
				if ((code*)puVar5[-2] != nullptr)
				{
					(*(code*)puVar5[-2])();
				}
			}
			else
			{
				iVar2 = FOG_IsExpansion();
				if (iVar2 != 0)
					goto LAB_6fb08297;
			}
			iStack_110 = iStack_110 + 1;
			iVar4 = iVar4 + 0x154;
			puVar5 = puVar5 + 0x154;
		} while (iStack_110 < *local_108);
	}
}

//D2Client.0x6FB083C0
void __cdecl sub_6FB083C0()
{
	int iVar1;
	uint32_t uVar2;
	D2CellFileStrc* pCelFile;
	int iVar3;
	int* piVar4;
	uint8_t* puVar5;
	uint32_t* puVar6;
	D2GfxDataStrc* pDVar7;
	D2GfxDataStrc DStack_14c;
	char cStack_104;
	uint32_t uStack_103;

	sub_6FB081D0((int*)(&dword_6FB7E030), (int)&byte_6FB7E048);
	sub_6FB081D0((int*)(&dword_6FB7F038), (int)&byte_6FB7F050);
	sub_6FB081D0((int*)(&dword_6FB80AE0), (int)&byte_6FB80AF8);
	iVar1 = FOG_IsExpansion();
	if (iVar1 == 0)
	{
		sub_6FB081D0((int*)(&dword_6FB83578), (int)&byte_6FB83590);
		puVar5 = &byte_6FB88570;
		piVar4 = (int*)(&dword_6FB88558);
	}
	else
	{
		sub_6FB081D0((int*)(&dword_6FB85AC0), (int)&byte_6FB85AD8);
		puVar5 = &byte_6FB8A568;
		piVar4 = (int*)(&dword_6FB8A550);
	}
	sub_6FB081D0(piVar4, (int)puVar5);
	cStack_104 = byte_6FB9A828;
	puVar6 = &uStack_103;
	for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	*(uint16_t*)puVar6 = 0;
	sgptMenuInfo = (int32_t*)(&dword_6FB7E030);
	dword_6FBB6FE0 = (int)&byte_6FB7E048;
	*(uint8_t*)((int)puVar6 + 2) = 0;
	sprintf(&cStack_104, "%s\\UI\\Widgets\\OptBar", "DATA\\GLOBAL");
	gpCellFile_6FBB6FF0 = CLIENT_LoadCellFile(&cStack_104, 0);
	sprintf(&cStack_104, "%s\\UI\\Widgets\\OptBarC", "DATA\\GLOBAL");
	gpCellFile_6FBB6FF4 = CLIENT_LoadCellFile(&cStack_104, 0);
	sprintf(&cStack_104, "%s\\UI\\Widgets\\OptSkull", "DATA\\GLOBAL");
	gpCellFile_6FBB6FF8 = CLIENT_LoadCellFile(&cStack_104, 0);
	pDVar7 = &DStack_14c;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	DStack_14c.pCellFile = sub_6FB23870();
	uVar2 = D2CMP_CelFileGetCelsPerDirection(DStack_14c.pCellFile);
	iVar1 = 0;
	DStack_14c.nFrame = 0;
	if (uVar2 != 0)
	{
		do
		{
			pCelFile = D2CMP_CelGetHandle(&DStack_14c);
			iVar3 = D2CMP_CelGetWidth(pCelFile);
			if (iVar1 <= iVar3)
			{
				iVar1 = iVar3;
			}
			DStack_14c.nFrame = DStack_14c.nFrame + 1;
		} while (DStack_14c.nFrame < uVar2);
	}
	dword_6FBB6FFC = iVar1;
}

//D2Client.0x6FB08540
void __fastcall sub_6FB08540(int* ptMenuInfo, int a2)
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint32_t* puVar3;
	uint32_t* puVar4;
	int local_8;

	D2_ASSERT(ptMenuInfo != nullptr);
	if (a2 != 0)
	{
		local_8 = 0;
		if (0 < *ptMenuInfo)
		{
			puVar4 = (uint32_t*)(a2 + 0x120);
			do
			{
				if ((D2CellFileStrc*)puVar4[0x107] != nullptr)
				{
					CLIENT_FreeCellFile((D2CellFileStrc*)puVar4[0x107]);
					puVar4[0x107] = 0;
				}
				if (puVar4[-0x48] == 1)
				{
					uVar1 = *puVar4;
					D2_ASSERT(!((uVar1 == 0) || (4 < uVar1)));
					uVar2 = 0;
					if (uVar1 != 0)
					{
						puVar3 = puVar4 + 0x108;
						do
						{
							if ((D2CellFileStrc*)*puVar3 != nullptr)
							{
								CLIENT_FreeCellFile((D2CellFileStrc*)*puVar3);
								*puVar3 = 0;
							}
							uVar2 = uVar2 + 1;
							puVar3 = puVar3 + 1;
						} while (uVar2 < *puVar4);
					}
				}
				local_8 = local_8 + 1;
				puVar4 = puVar4 + 0x154;
			} while (local_8 < *ptMenuInfo);
		}
		return;
	}
	FOG_DisplayAssert("ptMenuItem", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB08640
void __cdecl sub_6FB08640()
{
	int iVar1;
	int* piVar2;
	uint8_t* puVar3;

	sgptMenuInfo = nullptr;
	dword_6FBB6FE0 = 0;
	sub_6FB08540((int*)(&dword_6FB80AE0), (int)&byte_6FB80AF8);
	sub_6FB08540((int*)(&dword_6FB7F038), (int)&byte_6FB7F050);
	sub_6FB08540((int*)(&dword_6FB7E030), (int)&byte_6FB7E048);
	iVar1 = FOG_IsExpansion();
	if (iVar1 == 0)
	{
		sub_6FB08540((int*)(&dword_6FB83578), (int)&byte_6FB83590);
		puVar3 = &byte_6FB88570;
		piVar2 = (int*)(&dword_6FB88558);
	}
	else
	{
		sub_6FB08540((int*)(&dword_6FB85AC0), (int)&byte_6FB85AD8);
		puVar3 = &byte_6FB8A568;
		piVar2 = (int*)(&dword_6FB8A550);
	}
	sub_6FB08540(piVar2, (int)puVar3);
	if (gpCellFile_6FBB6FF0 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB6FF0);
		gpCellFile_6FBB6FF0 = nullptr;
	}
	if (gpCellFile_6FBB6FF4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB6FF4);
		gpCellFile_6FBB6FF4 = nullptr;
	}
	if (gpCellFile_6FBB6FF8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB6FF8);
		gpCellFile_6FBB6FF8 = nullptr;
	}
}

//D2Client.0x6FB08700
void __fastcall sub_6FB08700(int a1, int a2)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	if (a1 != 0)
	{
		uVar4 = 0;
		uVar3 = 0;
		do
		{
			*(uint32_t*)((int)&dword_6FB7DE70 + uVar3) = 0;
			if (*(int*)((int)&dword_6FB7DE68 + uVar3) != 0)
			{
				if (*(int*)((int)&dword_6FB7DE6C + uVar3) != 0)
				{
					uVar1 = sub_6FB23230(uVar4);
					*(uint32_t*)((int)&dword_6FB7DE70 + uVar3) = uVar1;
				}
				iVar2 = sub_6FB23230(uVar4);
				if (iVar2 != 0)
				{
					sub_6FB23260(uVar4, 1, 0);
				}
			}
			uVar3 = uVar3 + 0xc;
			uVar4 = uVar4 + 1;
		} while (uVar3 < 0x1c8);
	}
	sub_6FB23260(9, 0, 0);
	switch (a2)
	{
	case 0:
		sgptMenuInfo = (int32_t*)(&dword_6FB7E030);
		dword_6FBB6FE0 = (int)&byte_6FB7E048;
		break;
	case 1:
		sgptMenuInfo = (int32_t*)(&dword_6FB7F038);
		dword_6FBB6FE0 = (int)&byte_6FB7F050;
		break;
	case 2:
		sgptMenuInfo = (int32_t*)(&dword_6FB80AE0);
		dword_6FBB6FE0 = (int)&byte_6FB80AF8;
		break;
	case 3:
		iVar2 = FOG_IsExpansion();
		if (iVar2 == 0)
		{
			sgptMenuInfo = (int32_t*)(&dword_6FB83578);
			dword_6FBB6FE0 = (int)&byte_6FB83590;
		}
		else
		{
			sgptMenuInfo = (int32_t*)(&dword_6FB85AC0);
			dword_6FBB6FE0 = (int)&byte_6FB85AD8;
		}
		break;
	case 4:
		iVar2 = FOG_IsExpansion();
		if (iVar2 == 0)
		{
			sgptMenuInfo = (int32_t*)(&dword_6FB88558);
			dword_6FBB6FE0 = (int)&byte_6FB88570;
		}
		else
		{
			sgptMenuInfo = (int32_t*)(&dword_6FB8A550);
			dword_6FBB6FE0 = (int)&byte_6FB8A568;
		}
	}
	dword_6FBB6FD8 = *sgptMenuInfo + -1;
	if (a2 == 5)
	{
		dword_6FBB6FD8 = 1;
	}
}

//D2Client.0x6FB08860
void __fastcall sub_6FB08860(int a1)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	iVar1 = sub_6FB23230(9);
	if (iVar1 != 0)
	{
		sub_6FB23260(9, 1, 0);
	}
	if (a1 != 0)
	{
		uVar3 = 0;
		uVar2 = 0;
		do
		{
			if (*(int*)((int)&dword_6FB7DE70 + uVar2) != 0)
			{
				sub_6FB23260(uVar3, 0, 0);
			}
			uVar2 = uVar2 + 0xc;
			uVar3 = uVar3 + 1;
		} while (uVar2 < 0x1c8);
	}
}

//D2Client.0x6FB088B0
void __cdecl sub_6FB088B0()
{
	DrawMode eDrawMode;
	int iVar1;
	code* pcVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	D2CellFileStrc* pDVar9;
	int iVar10;
	int nXPos;
	int iVar11;
	D2GfxDataStrc* pDVar12;
	bool bVar13;
	int64_t lVar14;
	int local_c0;
	int local_b8;
	int local_b4;
	D2GfxDataStrc local_90;
	D2GfxDataStrc DStack_48;

	D2_ASSERT(sgptMenuInfo != nullptr);
	if (dword_6FBB6FE0 != 0)
	{
		iVar4 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		iVar10 = sgptMenuInfo[1];
		iVar1 = *sgptMenuInfo;
		iVar6 = gnScreenHeight + -0x50;
		if ((dword_6FBB7004 != iVar5) || (dword_6FBB7000 != iVar4))
		{
			dword_6FBB7000 = iVar4;
			dword_6FBB7004 = iVar5;
			if (dword_6FBB6FE8 == 0)
			{
				iVar4 = sub_6FB07AA0(iVar5);
				if (iVar4 != -1)
				{
					dword_6FBB6FD8 = iVar4;
				}
			}
			else
			{
				sub_6FB07B30(iVar4, iVar5);
			}
		}
		local_c0 = 0;
		local_b4 = 0;
		if (0 < *sgptMenuInfo)
		{
			iVar4 = 0;
			local_b8 = 0;
			do
			{
				*(uint32_t*)(iVar4 + 8 + dword_6FBB6FE0) = 0;
				if ((*(int*)(iVar4 + 4 + dword_6FBB6FE0) == 0) || (iVar5 = FOG_IsExpansion(), iVar5 != 0))
				{
					pcVar2 = *(code**)(iVar4 + 0x110 + dword_6FBB6FE0);
					if ((pcVar2 == nullptr) || (iVar5 = (*pcVar2)(), iVar5 != 0))
					{
						iVar5 = 1;
					}
					eDrawMode = (DrawMode)((uint32_t)(iVar5 != 0) * 4 + DRAWMODE_TRANS50);
					pcVar2 = *(code**)(iVar4 + dword_6FBB6FE0 + 0x11c);
					if (pcVar2 != nullptr)
					{
						(*pcVar2)();
					}
					iVar11 = sgptMenuInfo[1] * local_c0 + (iVar6 / 2 - (iVar10 * iVar1) / 2);
					iVar5 = sgptMenuInfo[2];
					*(int*)(iVar4 + 8 + dword_6FBB6FE0) = iVar11;
					iVar5 = iVar5 + iVar11;
					switch (*(uint32_t*)(iVar4 + dword_6FBB6FE0))
					{
					case 1:
						D2Win_10134_DrawCellFile(*(D2CellFileStrc**)(iVar4 + 0x53c + dword_6FBB6FE0), gnScreenWidth / 2 + -0xe6,
						    iVar5, 0, eDrawMode, -1);
						D2Win_10134_DrawCellFile(*(D2CellFileStrc**)(dword_6FBB6FE0 + 0x540 +
						                                             (*(int*)(iVar4 + 0x124 + dword_6FBB6FE0) + local_b8) * 4),
						    gnScreenWidth / 2 + 0xe6, iVar5, 2, eDrawMode, -1);
						break;
					case 2:
						pDVar9 = *(D2CellFileStrc**)(iVar4 + 0x53c + dword_6FBB6FE0);
						if (pDVar9 != nullptr)
						{
							D2Win_10134_DrawCellFile(pDVar9, gnScreenWidth / 2 + -0xe6, iVar5, 0, eDrawMode, -1);
						}
						iVar5 = iVar4 + dword_6FBB6FE0;
						bVar13 = *(int*)(iVar4 + 0x53c + dword_6FBB6FE0) == 0;
						iVar11 = sgptMenuInfo[4] + iVar11;
						iVar7 = gnScreenWidth / 2;
						if (bVar13)
						{
							iVar8 = iVar7 + -0x91;
						}
						else
						{
							iVar8 = iVar7 + -0x3c;
						}
						lVar14 = (int64_t)(((double)-265.0 / (double)(*(int*)(iVar5 + 0x120) - 1)) *
						                   (double)*(int*)(iVar5 + 0x124));
						nXPos = iVar8 - (int)lVar14;
						iVar3 = *(int*)(iVar5 + 0x128);
						iVar8 = (nXPos - iVar8) + 0xc;
						if (bVar13)
						{
							iVar7 = iVar7 + -0x90;
						}
						else
						{
							iVar7 = iVar7 + -0x3b;
						}
						sub_6FB5B0F0(iVar7, iVar11 + -0x1e, iVar8, 0x1e, 0, (DrawMode)(2 - (uint32_t)(iVar3 != 0)));
						sub_6FB5B0F0(iVar7 + iVar8, iVar11 + -0x1e, 0x121 - iVar8, 0x1e, 0,
						    (DrawMode)((uint32_t)(*(int*)(iVar5 + 0x128) != 0)));
						iVar8 = 2;
						iVar7 = gnScreenWidth / 2 + 0xe6;
						if (bVar13)
						{
							iVar8 = 1;
							iVar7 = gnScreenWidth / 2;
						}
						pDVar9 = gpCellFile_6FBB6FF4;
						if (*(int*)(iVar5 + 0x128) == 0)
						{
							pDVar9 = gpCellFile_6FBB6FF0;
						}
						D2Win_10134_DrawCellFile(pDVar9, iVar7, iVar11, iVar8, eDrawMode, -1);
						pDVar12 = &DStack_48;
						for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
						{
							pDVar12->pCurrentCell = nullptr;
							pDVar12 = (D2GfxDataStrc*)&pDVar12->pCellFile;
						}
						DStack_48.pCellFile = gpCellFile_6FBB6FF8;
						TEXTURE_CelDraw(&DStack_48, nXPos, (iVar11 - (uint32_t)(iVar3 == 0)) + -1, 0xffffffff, eDrawMode, nullptr);
						break;
					case 0xffffffff:
					case 0:
						D2Win_10134_DrawCellFile(*(D2CellFileStrc**)(iVar4 + 0x53c + dword_6FBB6FE0), gnScreenWidth / 2, iVar5, 1,
						    eDrawMode, -1);
					}
					local_c0 = local_c0 + 1;
				}
				local_b4 = local_b4 + 1;
				local_b8 = local_b8 + 0x154;
				iVar4 = iVar4 + 0x550;
			} while (local_b4 < *sgptMenuInfo);
		}
		pDVar12 = &local_90;
		for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			pDVar12->pCurrentCell = nullptr;
			pDVar12 = (D2GfxDataStrc*)&pDVar12->pCellFile;
		}
		local_90.pCellFile = sub_6FB23870();
		if (dword_6FBB6FE4 == 0)
		{
			local_90.nFrame = 0;
		}
		else
		{
			local_90.nFrame = 8 - dword_6FBB6FE4;
		}
		iVar10 = *(int*)(dword_6FBB6FD8 * 0x550 + 8 + dword_6FBB6FE0) + sgptMenuInfo[3];
		TEXTURE_CelDraw(&local_90, (gnScreenWidth / 2 - dword_6FBB6FFC) + -0xf9, iVar10, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		local_90.nFrame = dword_6FBB6FE4;
		TEXTURE_CelDraw(&local_90, gnScreenWidth / 2 + 0xf9, iVar10, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		iVar10 = sub_6FB24660();
		if ((iVar10 != 0) && (dword_6FBB6FE4 = dword_6FBB6FE4 + 1 & 0x80000007, (int)dword_6FBB6FE4 < 0))
		{
			dword_6FBB6FE4 = (dword_6FBB6FE4 - 1 | 0xfffffff8) + 1;
		}
		return;
	}
	FOG_DisplayAssert("sgptMenuItem", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB08D90
void __cdecl sub_6FB08D90()
{
	uint32_t local_4;

	local_4 = 0;
	SRegLoadValue("Diablo II", "Always Run", 0, (DWORD*)(&local_4));
	sub_6FAA8B20(local_4);
}

//D2Client.0x6FB08DC0
void __cdecl sub_6FB08DC0()
{
	uint32_t result;

	result = sub_6FAA8B30();
	SRegSaveValue("Diablo II", "Always Run", 0, result);
}

//D2Client.0x6FB08DE0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB08DE0()
{
	bool bVar1;
	bool bVar2;
	bool bVar3;
	int iVar4;
	uint32_t extraout_var;
	int iVar5;
	int iVar6;
	D2GfxDataStrc* pDVar7;
	uint32_t uVar8;
	D2GfxDataStrc local_48;

	bVar1 = false;
	iVar4 = sub_6FB23230(0x17);
	if (iVar4 == 0)
	{
		iVar4 = sub_6FB23230(0x19);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x1a);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0xc);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x1c);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x1d);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x18);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(3);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x10);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x16);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x24);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(2);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0xf);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x14);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		iVar4 = sub_6FB23230(0x1b);
		if (iVar4 != 0)
			goto LAB_6fb08ee2;
		dword_6FBB7014 = 0;
	}
	else
	{
	LAB_6fb08ee2:
		bVar1 = true;
		dword_6FBB7014 = 1;
	}
	iVar4 = sub_6FB23230(0x24);
	if (iVar4 != 0)
	{
		bVar1 = true;
		dword_6FBB7014 = 1;
	}
	bVar2 = false;
	iVar4 = sub_6FB23230(0x17);
	if (iVar4 == 0)
	{
		iVar4 = sub_6FB23230(0x19);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(0x1c);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(0x1a);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(0xc);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(0x18);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(0x1b);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
		iVar4 = sub_6FB23230(3);
		if (iVar4 != 0)
			goto LAB_6fb08f72;
	}
	else
	{
	LAB_6fb08f72:
		bVar2 = true;
		dword_6FBB7010 = 1;
	}
	iVar4 = sub_6FB23230(0x1f);
	if (iVar4 == 0)
	{
		bVar3 = sub_6FAFE9E0();
		if (D2C_ZEXT(bVar3) != 0)
			goto LAB_6fb08f91;
	}
	else
	{
	LAB_6fb08f91:
		iVar4 = sub_6FAFE9F0();
		if (1 < iVar4)
		{
			bVar2 = true;
			dword_6FBB7010 = 1;
		}
	}
	iVar4 = sub_6FB23230(1);
	if (iVar4 == 0)
	{
		iVar4 = sub_6FB23230(4);
		if (iVar4 == 0)
		{
			dword_6FBB7010 = 0;
			goto LAB_6fb08fcb;
		}
	}
	bVar2 = true;
	dword_6FBB7010 = 1;
LAB_6fb08fcb:
	if (!bVar1)
	{
		if (!bVar2)
		{
			pDVar7 = &local_48;
			for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				pDVar7->pCurrentCell = nullptr;
				pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
			}
			local_48.pCellFile = gpCellFile_6FBB7008;
			if (dword_6FBB7020 == 0)
			{
				iVar4 = gnScreenWidth / 2 + -0x54;
			}
			else
			{
				iVar4 = gnScreenWidth / 2 + -0x4a;
			}
			TEXTURE_CelDraw(&local_48, iVar4 + -3, gnScreenHeight + -0x2f, 0xffffffff, DRAWMODE_NORMAL,
			    nullptr);
			sub_6FB092B0(2);
			sub_6FB09390(1);
			sub_6FB09460(2);
			dword_6FBB7018 = 0;
			return;
		}
		sub_6FB09180(1);
		sub_6FB092B0(1);
		sub_6FB09390(1);
		sub_6FB09460(1);
		dword_6FBB7018 = 0;
		return;
	}
	if (!bVar2)
	{
		pDVar7 = &local_48;
		for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			pDVar7->pCurrentCell = nullptr;
			pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
		}
		local_48.pCellFile = gpCellFile_6FBB7008;
		if (dword_6FBB7020 == 0)
		{
			iVar4 = gnScreenWidth / 2 + 0x23;
		}
		else
		{
			iVar4 = gnScreenWidth / 2 + 0x38;
		}
		TEXTURE_CelDraw(&local_48, iVar4 + -2, gnScreenHeight + -0x2f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		sub_6FB092B0(3);
		iVar4 = 8;
		if (dword_6FBB7020 != 0)
		{
			iVar4 = 7;
		}
		iVar6 = 0;
		if (iVar4 != 0)
		{
			do
			{
				if ((&dword_6FBB6F98)[iVar6] == 1)
				{
					uVar8 = (&dword_6FBB6F58)[iVar6];
					iVar5 = (&dword_6FBB6FB8)[iVar6] + 1;
				}
				else
				{
					uVar8 = (&dword_6FBB6F58)[iVar6];
					iVar5 = (&dword_6FBB6FB8)[iVar6];
				}
				sub_6FB09270(iVar5, (&dword_6FBB6F38)[iVar6], uVar8, 1);
				iVar6 = iVar6 + 1;
			} while (iVar6 < iVar4);
		}
		sub_6FB09460(3);
		dword_6FBB7018 = 0;
		return;
	}
	sub_6FB09180(0);
	sub_6FB092B0(0);
	sub_6FB09390(0);
	sub_6FB09460(0);
	dword_6FBB7018 = 1;
}

//D2Client.0x6FB09180
void __fastcall sub_6FB09180(int a1)
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc local_48;

	if (a1 != 0)
	{
		pDVar1 = &local_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar1->pCurrentCell = 0;
			pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
		}
		local_48.pCellFile = gpCellFile_6FBB7008;
		if (a1 == 1)
		{
			TEXTURE_CelDraw(&local_48, gnScreenWidth / 2 + -0xcd, gnScreenHeight + -0x2f, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
		}
		else
		{
			if (a1 == 2)
			{
				if (dword_6FBB7020 == 0)
				{
					iVar2 = gnScreenWidth / 2 + -0x54;
				}
				else
				{
					iVar2 = gnScreenWidth / 2 + -0x4a;
				}
				TEXTURE_CelDraw(&local_48, iVar2 + -3, gnScreenHeight + -0x2f, 0xffffffff, DRAWMODE_NORMAL,
				    nullptr);
				return;
			}
			if (a1 == 3)
			{
				if (dword_6FBB7020 == 0)
				{
					iVar2 = gnScreenWidth / 2 + 0x23;
				}
				else
				{
					iVar2 = gnScreenWidth / 2 + 0x38;
				}
				TEXTURE_CelDraw(&local_48, iVar2 + -2, gnScreenHeight + -0x2f, 0xffffffff, DRAWMODE_NORMAL,
				    nullptr);
				return;
			}
		}
	}
}

//D2Client.0x6FB09270
void __fastcall sub_6FB09270(uint32_t a1, int a2, int a3, uint32_t a4)
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
	local_48.pCellFile = gpCellFile_6FBB700C;
	local_48.nFrame = a1;
	TEXTURE_CelDraw(&local_48, a2, a3, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB092B0
void __fastcall sub_6FB092B0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	int local_4;

	iVar1 = dword_6FBB7020;
	iVar5 = 0;
	uVar7 = 8;
	if (dword_6FBB7020 != 0)
	{
		uVar7 = 7;
	}
	local_4 = 0;
	if (a1 != 0)
	{
		iVar2 = gnScreenWidth / 2;
		iVar4 = iVar2 + -0x54;
		if (dword_6FBB7020 != 0)
		{
			iVar4 = iVar2 + -0x4a;
		}
		iVar6 = gnScreenHeight + -0x32;
		if (a1 == 1)
		{
			iVar4 = iVar2 + -0xca;
		}
		else if ((a1 == 3) && (iVar4 = iVar2 + 0x39, dword_6FBB7020 == 0))
		{
			iVar4 = iVar2 + 0x23;
		}
		dword_6FBB6F78 = 0;
		dword_6FBB6FB8 = 0;
		iVar2 = 1;
		dword_6FBB6F38 = iVar4;
		dword_6FBB6F58 = iVar6;
		if (1 < uVar7)
		{
			do
			{
				iVar4 = iVar4 + 0x15;
				(&dword_6FBB6F38)[iVar2] = iVar4;
				(&dword_6FBB6F58)[iVar2] = iVar6;
				if (iVar1 == 0)
				{
					(&dword_6FBB6F78)[iVar2] = iVar2;
					iVar3 = iVar2 * 2;
				}
				else
				{
					if (iVar2 == 3)
					{
						iVar5 = iVar5 + 2;
						local_4 = local_4 + 1;
					}
					(&dword_6FBB6F78)[iVar2] = local_4 + iVar2;
					iVar3 = iVar5 + iVar2 * 2;
				}
				(&dword_6FBB6FB8)[iVar2] = iVar3;
				iVar2 = iVar2 + 1;
			} while (iVar2 < (int)uVar7);
		}
	}
}

//D2Client.0x6FB09390
void __fastcall sub_6FB09390(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	D2GfxDataStrc* pDVar4;
	int nYPos;
	D2GfxDataStrc local_90;
	D2GfxDataStrc DStack_48;

	iVar2 = 8;
	if (a1 != 0)
	{
		if (dword_6FBB7020 != 0)
		{
			iVar2 = 7;
		}
		iVar3 = 0;
		if (iVar2 != 0)
		{
			do
			{
				iVar1 = 0x12;
				if ((&dword_6FBB6F98)[iVar3] == 1)
				{
					nYPos = (&dword_6FBB6F58)[iVar3];
					pDVar4 = &local_90;
					for (; iVar1 != 0; iVar1 = iVar1 + -1)
					{
						pDVar4->pCurrentCell = nullptr;
						pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
					}
					local_90.nFrame = (&dword_6FBB6FB8)[iVar3] + 1;
					local_90.pCellFile = gpCellFile_6FBB700C;
					iVar1 = (&dword_6FBB6F38)[iVar3];
					pDVar4 = &local_90;
				}
				else
				{
					pDVar4 = &DStack_48;
					for (; iVar1 != 0; iVar1 = iVar1 + -1)
					{
						pDVar4->pCurrentCell = nullptr;
						pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
					}
					DStack_48.nFrame = (&dword_6FBB6FB8)[iVar3];
					nYPos = (&dword_6FBB6F58)[iVar3];
					DStack_48.pCellFile = gpCellFile_6FBB700C;
					iVar1 = (&dword_6FBB6F38)[iVar3];
					pDVar4 = &DStack_48;
				}
				TEXTURE_CelDraw(pDVar4, iVar1, nYPos, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				iVar3 = iVar3 + 1;
			} while (iVar3 < iVar2);
		}
	}
}

//D2Client.0x6FB09460
void __fastcall sub_6FB09460(int a1)
{
	bool bVar1;
	int iVar2;
	int iVar3;
	Unicode* pUVar4;
	uint32_t uVar5;
	Unicode* pUVar6;
	int iVar7;
	short index;
	int iVar8;
	int iVar9;
	int local_1e4;
	int local_1e0;
	int local_1dc;
	Unicode aUStack_1cc[30];
	Unicode local_190[200];

	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	iVar7 = 0;
	local_1e4 = 8;
	if (dword_6FBB7020 != 0)
	{
		local_1e4 = 7;
	}
	if (a1 != 0)
	{
		if (a1 == 1)
		{
			iVar7 = -0x76;
		}
		else if (a1 == 3)
		{
			iVar7 = 0x77;
		}
		iVar7 = gnScreenWidth / 2 + iVar7;
		if ((((iVar7 + -0x54 < iVar2) && (iVar2 < iVar7 + 0x59)) && (gnScreenHeight + -0x45 < iVar3)) &&
		    ((iVar3 < gnScreenHeight + -0x2f && (local_1dc = 0, local_1e4 != 0))))
		{
			do
			{
				iVar3 = (&dword_6FBB6F38)[local_1dc];
				if ((iVar3 < iVar2) && (iVar2 < iVar3 + 0x14))
				{
					iVar7 = (&dword_6FBB6F58)[local_1dc];
					bVar1 = false;
					iVar9 = 0x39;
					switch ((&dword_6FBB6F78)[local_1dc])
					{
					case 0:
						index = 0x1049;
						bVar1 = true;
						iVar9 = 0;
						break;
					case 1:
						bVar1 = true;
						index = 0x104a;
						iVar9 = 1;
						break;
					case 2:
						index = 0x104b;
						bVar1 = true;
						iVar9 = 0xc;
						break;
					case 3:
						index = 0x104c;
						bVar1 = true;
						iVar9 = 2;
						break;
					case 4:
						index = 0x104d;
						bVar1 = true;
						iVar9 = 7;
						break;
					case 5:
						index = 0x104e;
						bVar1 = true;
						iVar9 = 3;
						break;
					case 6:
						index = 0x104f;
						bVar1 = true;
						iVar9 = 4;
						break;
					case 7:
						index = 0x1050;
						break;
					default:
						goto switchD_6fb09546_default;
					}
					pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
					Unicode::strcpy(local_190, pUVar4);
					if ((bVar1) && (iVar9 != 0x39))
					{
						uVar5 = sub_6FAD4B60(iVar9, 1);
						if ((short)uVar5 != -1)
						{
							pUVar4 = aUStack_1cc;
							for (iVar8 = 0xf; iVar8 != 0; iVar8 = iVar8 + -1)
							{
								*(uint32_t*)pUVar4 = 0;
								pUVar4 = pUVar4 + 2;
							}
							pUVar4 = sub_6FAD4F50(iVar9, 1);
							pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
							Unicode::sprintf(0x1e, aUStack_1cc, pUVar6, pUVar4);
							Unicode::strcat(local_190, aUStack_1cc);
						}
						uVar5 = sub_6FAD4B60(iVar9, 0);
						if ((short)uVar5 != -1)
						{
							pUVar4 = aUStack_1cc;
							for (iVar8 = 0xf; iVar8 != 0; iVar8 = iVar8 + -1)
							{
								*(uint32_t*)pUVar4 = 0;
								pUVar4 = pUVar4 + 2;
							}
							pUVar4 = sub_6FAD4F50(iVar9, 0);
							pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1052));
							Unicode::sprintf(0x1e, aUStack_1cc, pUVar6, pUVar4);
							Unicode::strcat(local_190, aUStack_1cc);
						}
					}
					D2Win_10129_DrawFramedText(local_190, iVar3 + -3, iVar7 + -0x1a, 0, 1);
				}
			switchD_6fb09546_default:
				local_1dc = local_1dc + 1;
			} while (local_1dc < local_1e4);
		}
	}
}

//D2Client.0x6FB09730
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB09730(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	int iVar8;
	int iStack_8;

	pDVar2 = CUNIT_GetPlayer();
	iVar5 = 0;
	if ((((dword_6FBB7024 != 0) && (dword_6FBB7024 = 0, pDVar2 != nullptr)) &&
	        (pDVar2->pInventory != nullptr)) &&
	    (pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory), pDVar2 == nullptr))
	{
		iVar3 = sub_6FB57CC0();
		if (iVar3 != 7)
		{
			sub_6FB575B0(nullptr);
		}
		iVar3 = 8;
		iStack_8 = 8;
		if (dword_6FBB7020 != 0)
		{
			iStack_8 = 7;
			iVar3 = 7;
		}
		if (dword_6FBB7018 == 0)
		{
			pDVar2 = CUNIT_GetPlayer();
			uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
			uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
			iVar8 = iVar3;
			if (iVar3 != 0)
			{
				puVar7 = &dword_6FBB6F98;
				for (; iVar8 = iStack_8, iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
			}
			bVar1 = sub_6FAFE9E0();
			if ((D2C_ZEXT(bVar1) != 0) && (iVar3 = sub_6FAFE9F0(), 1 < iVar3))
			{
				iVar5 = -0x76;
			}
			if (dword_6FBB7010 != 0)
			{
				iVar5 = iVar5 + -0x76;
			}
			if (dword_6FBB7014 != 0)
			{
				iVar5 = iVar5 + 0x77;
			}
			iVar5 = iVar5 + gnScreenWidth / 2;
			if (((iVar5 + -0x54 < (int)uVar4) && ((int)uVar4 < iVar5 + 0x59)) &&
			    ((gnScreenHeight + -0x45 < (int)uVar6 && ((int)uVar6 < gnScreenHeight + -0x2f))))
			{
				iVar5 = 0;
				if (iVar8 != 0)
				{
					do
					{
						if ((((int)(&dword_6FBB6F38)[iVar5] < (int)uVar4) &&
						        ((int)uVar4 < (&dword_6FBB6F38)[iVar5] + 0x14)) &&
						    (((&dword_6FBB6F78)[iVar5] == 7 ||
						        (((pDVar2 != nullptr && (pDVar2->dwUnitType == 0)) &&
						            (pDVar2->dwAnimMode != 0x11))))))
						{
							sub_6FB098D0((&dword_6FBB6F78)[iVar5]);
						}
						iVar5 = iVar5 + 1;
					} while (iVar5 < iVar8);
				}
				sub_6FAABF30();
				sub_6FAABF60();
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			pSMSGHANDLER_PARAMS->bUseResult = 0;
		}
		byte_6FBB701C = 0;
	}
}

//D2Client.0x6FB098D0
void __fastcall sub_6FB098D0(uint32_t a1)
{
	int iVar1;
	uint32_t uVar2;

	switch (a1)
	{
	case 0:
		iVar1 = sub_6FB23230(2);
		uVar2 = 2;
		break;
	case 1:
		iVar1 = sub_6FB23230(1);
		uVar2 = 1;
		break;
	case 2:
		iVar1 = sub_6FB23230(4);
		uVar2 = 4;
		break;
	case 3:
		iVar1 = sub_6FAABFF0();
		if (iVar1 == 0)
		{
			return;
		}
		iVar1 = sub_6FB23230(0x16);
		uVar2 = 0x16;
		break;
	case 4:
		iVar1 = sub_6FB23230(10);
		uVar2 = 10;
		break;
	case 5:
		iVar1 = sub_6FB23230(0x1f);
		if (iVar1 != 0)
		{
			sub_6FB23260(0x1f, 1, 0);
		}
		iVar1 = sub_6FB23230(0x18);
		uVar2 = 0x18;
		break;
	case 6:
		OutputDebugStringA("Panel quest log toggle\n");
		sub_6FB06120(0);
		return;
	case 7:
		sub_6FB23800(0, 0);
		sub_6FB23890();
		sub_6FB08700(1, 0);
		sub_6FB238A0();
		sub_6FB238B0();
		return;
	default:
		goto switchD_6fb098d5_default;
	}
	if (iVar1 == 0)
	{
		sub_6FB23260(uVar2, 2, 0);
		return;
	}
	sub_6FB23260(uVar2, 1, 0);
switchD_6fb098d5_default:
}

//D2Client.0x6FB099F0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB099F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_var;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int local_8;

	local_8 = 8;
	if (dword_6FBB7020 != 0)
	{
		local_8 = 7;
	}
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		return;
	}
	if (pDVar2->pInventory == nullptr)
	{
		return;
	}
	pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	if (pDVar2 != nullptr)
	{
		return;
	}
	if (dword_6FBB7018 != 0)
	{
		return;
	}
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		return;
	}
	uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar4 = 0;
	bVar1 = sub_6FAFE9E0();
	if ((D2C_ZEXT(bVar1) != 0) && (iVar3 = sub_6FAFE9F0(), 1 < iVar3))
	{
		iVar4 = -0x76;
	}
	if (dword_6FBB7010 != 0)
	{
		iVar4 = iVar4 + -0x76;
	}
	if (dword_6FBB7014 != 0)
	{
		iVar4 = iVar4 + 0x77;
	}
	iVar4 = gnScreenWidth / 2 + iVar4;
	if ((int)uVar6 <= iVar4 + -0x54)
	{
		return;
	}
	if (iVar4 + 0x59 <= (int)uVar6)
	{
		return;
	}
	if ((int)uVar5 <= gnScreenHeight + -0x45)
	{
		return;
	}
	if (gnScreenHeight + -0x2f <= (int)uVar5)
	{
		return;
	}
	iVar4 = 0;
	if (local_8 == 0)
	{
		return;
	}
	while (((int)uVar6 <= (int)(&dword_6FBB6F38)[iVar4] || ((&dword_6FBB6F38)[iVar4] + 0x14 <= (int)uVar6)))
	{
		iVar4 = iVar4 + 1;
		if (local_8 <= iVar4)
		{
			return;
		}
	}
	if ((&dword_6FBB6F78)[iVar4] != 7)
	{
		if ((pDVar2->dwUnitType != 0) || (pDVar2->dwAnimMode == 0x11))
			goto LAB_6fb09b47;
		iVar3 = sub_6FB23230(9);
		if (iVar3 != 0)
		{
			iVar3 = sub_6FAABFF0();
			if (iVar3 == 0)
			{
				bVar1 = SBORROW4(iVar4, 4);
				iVar3 = -4;
			}
			else
			{
				bVar1 = SBORROW4(iVar4, 5);
				iVar3 = -5;
			}
			if (bVar1 != iVar4 + iVar3 < 0)
				goto LAB_6fb09b47;
		}
	}
	(&dword_6FBB6F98)[iVar4] = 1;
LAB_6fb09b47:
	sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
	dword_6FBB7024 = 1;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FB09B80
void __cdecl sub_6FB09B80()
{
	int iVar1;
	uint32_t* puVar2;

	iVar1 = sub_6FAABFF0();
	if (iVar1 == 0)
	{
		gpCellFile_6FBB7008 = sub_6FB20100("Panel\\minipanel_s");
	}
	else
	{
		gpCellFile_6FBB7008 = sub_6FB20100("Panel\\minipanel");
	}
	dword_6FBB7020 = (int)(iVar1 == 0);
	gpCellFile_6FBB700C = sub_6FB20100("Panel\\minipanelbtn");
	iVar1 = 8;
	if (dword_6FBB7020 != 0)
	{
		iVar1 = 7;
	}
	if (iVar1 != 0)
	{
		puVar2 = &dword_6FBB6F98;
		for (; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar2 = 0;
			puVar2 = puVar2 + 1;
		}
	}
}

//D2Client.0x6FB09BF0
void __cdecl sub_6FB09BF0()
{
	SRegSaveValue("Diablo II", "Mini Panel", 1, (uint32_t)(dword_6FB7DF6C == 0));
	if (gpCellFile_6FBB7008 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB7008);
		gpCellFile_6FBB7008 = nullptr;
	}
	if (gpCellFile_6FBB700C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB700C);
		gpCellFile_6FBB700C = nullptr;
	}
}

//D2Client.0x6FB09C50
uint32_t __fastcall sub_6FB09C50(int a1, int a2)
{
	if ((((gnScreenWidth / 2 + -0x4a < a1) && (a1 < gnScreenWidth / 2 + 0x47)) &&
	        (a2 < gnScreenHeight + -0x32)) &&
	    (gnScreenHeight + -0x45 < a2))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB09C90
void __cdecl sub_6FB09C90()
{
	int iVar1;
	uint32_t local_4;

	SRegLoadValue("Diablo II", "Resolution", 0, (DWORD*)(&local_4));
	iVar1 = 0;
	if (local_4 == 1)
	{
		iVar1 = 2;
	}
	CLIENT_SetResolution(iVar1);
}

//D2Client.0x6FB09CC0
uint32_t __cdecl sub_6FB09CC0()
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = sub_6FB57BC0();
	iVar2 = sub_6FB57BD0();
	iVar3 = sub_6FB23230(0x14);
	if (iVar3 != 0)
	{
		iVar3 = sub_6FB23230(0x15);
		if (iVar3 != 0)
		{
			if (dword_6FBB7020 == 0)
			{
				iVar3 = gnScreenWidth / 2 + 0x23;
			}
			else
			{
				iVar3 = gnScreenWidth / 2 + 0x38;
			}
			iVar4 = 8;
			if (dword_6FBB7020 != 0)
			{
				iVar4 = 7;
			}
			if ((((iVar3 < iVar1) && (iVar1 < iVar3 + iVar4 * 0x14)) && (gnScreenHeight + -0x4c < iVar2)) &&
			    (iVar2 < gnScreenHeight + -0x32))
			{
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB09D50
void __cdecl sub_6FB09D50()
{
	uint16_t* puVar1;
	int iVar2;

	puVar1 = word_6FBB703C;
	iVar2 = 0x20;
	do
	{
		memset(puVar1, 0, 2 * (0x80));
		puVar1 = puVar1 + 0x90;
		iVar2 = iVar2 + -1;
	} while (iVar2 != 0);
}

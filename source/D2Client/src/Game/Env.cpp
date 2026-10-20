#include "Game/Env.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Draw/DWall.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "Game/Select.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Player.h"

//D2Client.0x6FB6E189
uint8_t byte_6FB6E189[7] = {0xC8, 0x40, 0xA0, 0x20, 0x50, 0x40, 0xA0};
//D2Client.0x6FB6E190
uint8_t byte_6FB6E190[4];
//D2Client.0x6FB6E194
uint8_t byte_6FB6E194[4];
//D2Client.0x6FB6E198
uint8_t byte_6FB6E198[4];
//D2Client.0x6FB6E19C
uint8_t byte_6FB6E19C[4] = {1};
//D2Client.0x6FB6E1A0
uint8_t byte_6FB6E1A0[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB6E1A4
uint8_t byte_6FB6E1A4[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB6E1A8
uint8_t byte_6FB6E1A8[4];
//D2Client.0x6FB6E1AC
uint8_t byte_6FB6E1AC[116] = {0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 2, 0, 0, 0, 1, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 2, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 2};
//D2Client.0x6FB751C0
int32_t dword_6FB751C0 = 1;
//D2Client.0x6FB7580C
uint32_t dword_6FB7580C = 0x10;
//D2Client.0x6FB75810
uint32_t dword_6FB75810 = 0x10;
//D2Client.0x6FB75814
int32_t dword_6FB75814 = 1;
//D2Client.0x6FBA762C
uint8_t byte_6FBA762C[12];
//D2Client.0x6FBA7638
int32_t dword_6FBA7638;
//D2Client.0x6FBA763C
uint8_t byte_6FBA763C;
//D2Client.0x6FBA7640
int32_t dword_6FBA7640;
//D2Client.0x6FBA7644
int32_t dword_6FBA7644;
//D2Client.0x6FBA7648
uint32_t dword_6FBA7648;
//D2Client.0x6FBA764C
uint32_t dword_6FBA764C;
//D2Client.0x6FBA7650
uint8_t byte_6FBA7650;
//D2Client.0x6FBA7654
uint8_t byte_6FBA7654;
//D2Client.0x6FBA7658
int32_t dword_6FBA7658;
//D2Client.0x6FBA765C
int32_t dword_6FBA765C;
//D2Client.0x6FBA7660
uint32_t dword_6FBA7660;
//D2Client.0x6FBA7664
uint8_t byte_6FBA7664;
//D2Client.0x6FBA7668
uint8_t byte_6FBA7668;
//D2Client.0x6FBA766C
uint8_t byte_6FBA766C;
//D2Client.0x6FBA7670
uint8_t byte_6FBA7670[12];
//D2Client.0x6FBA767C
uint8_t byte_6FBA767C[12];
//D2Client.0x6FBA7688
uint32_t dword_6FBA7688;
//D2Client.0x6FBA768C
uint8_t byte_6FBA768C[12];
//D2Client.0x6FBA7698
uint32_t dword_6FBA7698[4];
//D2Client.0x6FBA76A8
int32_t dword_6FBA76A8;
//D2Client.0x6FBA76AC
uint32_t dword_6FBA76AC;
//D2Client.0x6FBA76B0
int32_t dword_6FBA76B0;
//D2Client.0x6FBA76B8
uint32_t dword_6FBA76B8;
//D2Client.0x6FBA76BC
uint32_t dword_6FBA76BC;
//D2Client.0x6FBA76C0
uint8_t byte_6FBA76C0;
//D2Client.0x6FBA76C4
uint8_t byte_6FBA76C4;
//D2Client.0x6FBA76C8
uint8_t byte_6FBA76C8[12];
//D2Client.0x6FBA76D4
uint32_t dword_6FBA76D4[4];
//D2Client.0x6FBA76E4
uint32_t dword_6FBA76E4;
//D2Client.0x6FBA76E8
uint8_t byte_6FBA76E8;
//D2Client.0x6FBA76EC
int32_t dword_6FBA76EC;
//D2Client.0x6FBA76F0
uint8_t byte_6FBA76F0;
//D2Client.0x6FBA76F4
uint32_t dword_6FBA76F4;
//D2Client.0x6FBA76FC
int32_t dword_6FBA76FC;
//D2Client.0x6FBA7700
int32_t dword_6FBA7700;
//D2Client.0x6FBA7704
int32_t dword_6FBA7704;
//D2Client.0x6FBA7708
int32_t dword_6FBA7708;
//D2Client.0x6FBA7710
uint8_t byte_6FBA7710;
//D2Client.0x6FBA7714
int32_t dword_6FBA7714;
//D2Client.0x6FBA7718
int32_t dword_6FBA7718;
//D2Client.0x6FBA771C
int32_t dword_6FBA771C;
//D2Client.0x6FBA7720
D2UnitStrc* gpUnit_6FBA7720;
//D2Client.0x6FBA7724
int32_t dword_6FBA7724;
//D2Client.0x6FBA7728
int32_t dword_6FBA7728;
//D2Client.0x6FBA772C
int32_t dword_6FBA772C;
//D2Client.0x6FBA7730
uint32_t dword_6FBA7730;
//D2Client.0x6FBA7734
uint32_t dword_6FBA7734;
//D2Client.0x6FBA7738
uint32_t dword_6FBA7738;
//D2Client.0x6FBA773C
uint32_t dword_6FBA773C;
//D2Client.0x6FBA7828
uint8_t byte_6FBA7828;
//D2Client.0x6FBA796C
int32_t dword_6FBA796C;
//D2Client.0x6FBA79B0
uint32_t dword_6FBA79B0;
//D2Client.0x6FBA79B4
int32_t dword_6FBA79B4;
//D2Client.0x6FBA79B8
int32_t dword_6FBA79B8;
//D2Client.0x6FBA79BC
int32_t dword_6FBA79BC;
//D2Client.0x6FBA79CC
uint32_t dword_6FBA79CC;
//D2Client.0x6FBA79D0
char byte_6FBA79D0;
//D2Client.0x6FBA79D4
uint32_t dword_6FBA79D4;
//D2Client.0x6FBA79D8
int32_t dword_6FBA79D8;
//D2Client.0x6FBA79DC
int32_t dword_6FBA79DC;

//D2Client.0x6FAA6AE0
int __fastcall sub_6FAA6AE0(int a1)
{
	uint64_t uVar1;
	uint64_t DVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pRoom;
	int iVar4;
	D2SeedStrc* pDVar5;

	if ((-1 < a1) && (a1 < 4))
	{
		if (((gpUnit_6FBA7720 == nullptr) || (pDVar3 = gpUnit_6FBA7720, a1 == 0)) &&
		    ((dword_6FBA771C == 0 || (pDVar3 = (D2UnitStrc*)dword_6FBA771C, a1 == 2))))
		{
			dword_6FBA7724 = a1;
			pDVar3 = CUNIT_GetPlayer();
			D2_ASSERT(pDVar3 != nullptr);
			switch (a1)
			{
			case 0:
				dword_6FBA7658 = 0;
				return (int)pDVar3;
			case 1:
				sub_6FAA6D40();
				DVar2 = (uint64_t)((uint64_t)(pDVar3->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pDVar3->pSeed).nHighSeed);
				(*(uint64_t*)&pDVar3->pSeed) = DVar2;
				uVar1 = (uint64_t)DVar2 & 0xffffffff;
				dword_6FBA76A8 = (int)(uVar1 % 0xe0) + 0x20;
				return (int)(uVar1 / 0xe0);
			case 2:
				pRoom = CUNIT_GetPlayerRoom();
				iVar4 = DUNGEON_GetLevelIdFromRoom(pRoom);
				pDVar3 = CUNIT_GetPlayer();
				pDVar5 = &pDVar3->pSeed;
				switch (iVar4)
				{
				case 0x6d:
				case 0x6e:
				case 0x6f:
				case 0x70:
					byte_6FBA76B4 = 0x2a;
					dword_6FBA76B0 = 0x2a;
					byte_6FBA76F8 = 0xaa;
					dword_6FBA76F4 = 0xaa;
					DVar2 = (uint64_t)((uint64_t)pDVar5->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar3->pSeed).nHighSeed);
					*(uint64_t*)pDVar5 = DVar2;
					pDVar3 = (D2UnitStrc*)((int)(((uint64_t)DVar2 & 0xffffffff) % 0x38) + 0x20);
					dword_6FBA7658 = (int)pDVar3;
					dword_6FBA76A8 = (int)pDVar3;
					break;
				default:
					dword_6FBA7658 = dword_6FBA76A8;
					if (dword_6FBA7714 != 0)
					{
						dword_6FBA7708 = 0;
						return dword_6FBA7714;
					}
					*(uint64_t*)pDVar5 = (uint64_t)((uint64_t)pDVar5->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar3->pSeed).nHighSeed);
					dword_6FBA7708 = 0;
					return 0;
				case 0x75:
					dword_6FBA76B0 = 0xaa;
					dword_6FBA76F4 = 0x38;
					byte_6FBA76B4 = 0x1c;
					byte_6FBA76F8 = 0x38;
					DVar2 = (uint64_t)((uint64_t)pDVar5->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar3->pSeed).nHighSeed);
					*(uint64_t*)pDVar5 = DVar2;
					dword_6FBA76A8 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x70) + 0x20;
					dword_6FBA7658 = dword_6FBA76A8;
					return dword_6FBA76A8;
				case 0x78:
				case 0x79:
					dword_6FBA76B0 = 0x1c;
					dword_6FBA76F4 = 0x1c;
					byte_6FBA76B4 = 0x1c;
					byte_6FBA76F8 = 0x1c;
					dword_6FBA7638 = 0x1c;
					dword_6FBA7644 = 0x1c;
					dword_6FBA76A8 = 0x100;
					dword_6FBA7658 = 0x100;
					return 0x100;
				}
				break;
			case 3:
				dword_6FBA7708 = 0;
				return (int)pDVar3;
			}
		}
		return (int)pDVar3;
	}
	FOG_DisplayAssert("eState >= 0 && eState < NUMBER_OF_RAIN_STATES",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAA6D40
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FAA6D40()
{
	D2SeedStrc* pDVar1;
	uint64_t DVar2;
	uint8_t bVar3;
	D2UnitStrc* pDVar4;
	D2ActiveRoomStrc* pRoom;
	int nLevelId;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	int in_ECX;
	int iVar7;

	pDVar4 = CUNIT_GetPlayer();
	if ((pDVar4 != nullptr) && (pRoom = CUNIT_GetPlayerRoom(), pRoom != nullptr))
	{
		nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
		bVar3 = DRLG_GetActNoFromLevelId(nLevelId);
		if (bVar3 != 4)
		{
			if (dword_6FBA771C != 0)
			{
				dword_6FBA771C = 0;
			}
			D2_ASSERT(!((dword_6FBA7714 != 0) && (FOG_10063(dword_6FBA7704), *(int*)(dword_6FBA7704 + 0x114) != 0)));
			dword_6FBA7714 = 0;
			pDVar4 = CUNIT_GetPlayer();
			if (pDVar4 != nullptr)
			{
				pDVar1 = &pDVar4->pSeed;
				uVar5 = sub_6FAA88F0((uint64_t*)pDVar1, 0x177);
				dword_6FBA765C = uVar5 + 0x7d;
				uVar5 = sub_6FAA88F0((uint64_t*)pDVar1, 0x5dc);
				dword_6FBA7640 = uVar5 + 500;
				uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
				dword_6FBA7644 = uVar5 % 0x47 + 0x5c;
				dword_6FBA7638 = dword_6FBA7644;
				return 0;
			}
			FOG_Trace("Env problem with latency at line %d of file %s", __LINE__, __FILE__);
			dword_6FBA7644 = 0x7f;
			dword_6FBA7638 = 0x7f;
			dword_6FBA765C = 0x138;
			dword_6FBA7640 = 0x4e2;
			return 0;
		}
		pDVar6 = CUNIT_GetPlayer();
		if (pDVar6 == nullptr)
		{
			FOG_Trace("Env problem with latency at line %d of file %s", __LINE__, __FILE__);
			dword_6FBA765C = 0x138;
			dword_6FBA7640 = 0x4e2;
			dword_6FBA7638 = 0x7f;
		}
		else
		{
			pDVar1 = &pDVar6->pSeed;
			uVar5 = sub_6FAA88F0((uint64_t*)pDVar1, 0x177);
			dword_6FBA765C = uVar5 + 0x7d;
			uVar5 = sub_6FAA88F0((uint64_t*)pDVar1, 0x5dc);
			dword_6FBA7640 = uVar5 + 500;
			uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
			dword_6FBA7638 = uVar5 % 0x47 + 0x5c;
		}
		iVar7 = 0;
		uVar5 = 0;
		switch (nLevelId)
		{
		case 0x6d:
		case 0x6e:
		case 0x6f:
		case 0x70:
			dword_6FBA7718 = 0;
			uVar5 = 0x19;
			break;
		case 0x78:
		case 0x79:
			iVar7 = 1;
		case 0x75:
			dword_6FBA7718 = 1;
			uVar5 = 0;
		}
		DVar2 = (uint64_t)((uint64_t)(pDVar4->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar4->pSeed).nHighSeed);
		dword_6FBA7644 = dword_6FBA7638;
		(*(uint64_t*)&pDVar4->pSeed) = DVar2;
		if (((uint32_t)(((uint64_t)DVar2 & 0xffffffff) % 100) < uVar5) && (in_ECX == 0))
		{
			if (dword_6FBA771C != 0)
			{
				dword_6FBA771C = 0;
			}
			D2_ASSERT(!((dword_6FBA7714 != 0) && (FOG_10063(dword_6FBA7704), *(int*)(dword_6FBA7704 + 0x114) != 0)));
			dword_6FBA7714 = 0;
			return 0;
		}
		dword_6FBA771C = iVar7;
		if (iVar7 != 0)
		{
			sub_6FAA6AE0(2);
		}
		if (dword_6FBA7708 != 0)
		{
			dword_6FBA7708 = 0;
		}
		if (((dword_6FBA7714 != 1) || (in_ECX != 0)) &&
		    (FOG_10063(dword_6FBA7704), *(int*)(dword_6FBA7704 + 0x114) != 0))
		{
			FOG_DisplayAssert("spParticleData->nTotalCount == 0",
			    __FILE__, __LINE__);
			exit(-1);
		}
		dword_6FBA7714 = 1;
	}
	return 0;
}

//D2Client.0x6FAA7050
void __fastcall sub_6FAA7050(int a1)
{
	uint64_t DVar1;
	char cVar2;
	uint8_t bVar3;
	D2UnitStrc* pDVar4;
	char cVar5;
	uint8_t nRed;
	int iVar6;
	int iVar7;
	int iStack_110;
	int local_10c;
	int iStack_108;
	CHAR aCStack_104[260];

	local_10c = a1;
	sub_6FAA6D40();
	if (dword_6FBA7728 == 0)
	{
		pDVar4 = CUNIT_GetPlayer();
		if (pDVar4 == nullptr)
		{
			FOG_Trace("Env problem with latency at line %d of file %s", __LINE__, __FILE__);
			dword_6FBA765C = 0x138;
			dword_6FBA7640 = 0x4e2;
			dword_6FBA7638 = 0x7f;
		}
		else
		{
			DVar1 = (uint64_t)((uint64_t)(pDVar4->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar4->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar4->pSeed) = DVar1;
			dword_6FBA765C = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x177) + 0x7d;
			DVar1 = (uint64_t)((uint64_t)(pDVar4->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar4->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar4->pSeed) = DVar1;
			dword_6FBA7640 = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x5dc) + 500;
			DVar1 = (uint64_t)((uint64_t)(pDVar4->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar4->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar4->pSeed) = DVar1;
			dword_6FBA7638 = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x47) + 0x5c;
		}
		dword_6FBA7728 = 1;
		dword_6FBA7644 = dword_6FBA7638;
	}
	dword_6FBA76E4 = 0x1d4c;
	byte_6FBA76E8 = 0xfa;
	dword_6FBA76EC = 3000;
	byte_6FBA76F0 = 0x7d;
	bVar3 = DRLG_GetActNoFromLevelId(a1);
	if (bVar3 == 2)
	{
		dword_6FBA76EC = dword_6FBA76EC * 3;
	}
	bVar3 = DRLG_GetActNoFromLevelId(local_10c);
	if (bVar3 == 4)
	{
		dword_6FBA76EC = dword_6FBA76EC * 3;
	}
	byte_6FBA7664 = 0xfa;
	iVar7 = 0;
	byte_6FBA7668 = 3000;
	dword_6FBA7660 = 0x1d4c;
	byte_6FBA766C = 0x32;
	iVar6 = 0;
	local_10c = 0;
	iStack_108 = 0;
	do
	{
		cVar5 = (char)(local_10c / 0xc);
		bVar3 = -cVar5 + 0x62;
		bVar3 = D2Win_10034_MixRGB(bVar3, -cVar5 + 0x7b, bVar3);
		byte_6FBA7670[iVar6] = bVar3;
		cVar2 = -(((char)(iVar7 / 0xc) + (char)(iVar7 >> 0x1f)) -
		          (char)((int64_t)iVar7 * 0x2aaaaaab >> 0x3f));
		bVar3 = cVar2 + 0x2d;
		bVar3 = D2Win_10034_MixRGB(bVar3, cVar2 + 0x37, bVar3);
		byte_6FBA762C[iVar6] = bVar3;
		cVar2 = -(((char)(iStack_108 / 0xc) + (char)(iStack_108 >> 0x1f)) -
		          (char)((int64_t)iStack_108 * 0x2aaaaaab >> 0x3f));
		bVar3 = cVar2 + 0x19;
		bVar3 = D2Win_10034_MixRGB(bVar3, cVar2 + 0x1e, bVar3);
		byte_6FBA768C[iVar6] = bVar3;
		bVar3 = cVar5 + 0x78;
		bVar3 = D2Win_10034_MixRGB(bVar3, bVar3, bVar3);
		nRed = cVar5 + 0xaa;
		byte_6FBA767C[iVar6] = bVar3;
		bVar3 = D2Win_10034_MixRGB(nRed, nRed, nRed);
		byte_6FBA76C8[iVar6] = bVar3;
		iVar7 = iVar7 + 0x28;
		iVar6 = iVar6 + 1;
		iStack_108 = iStack_108 + 0x18;
		local_10c = local_10c + 0x50;
	} while (iVar7 < 0x1e0);
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\Rain1", "DATA\\GLOBAL");
	dword_6FBA76B8 = (uint32_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\Rain2", "DATA\\GLOBAL");
	dword_6FBA76BC = (uint32_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\Rain3", "DATA\\GLOBAL");
	byte_6FBA76C0 = (uint8_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\Rain4", "DATA\\GLOBAL");
	byte_6FBA76C4 = (uint8_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	iVar6 = 0;
	do
	{
		iVar7 = D2CMP_CelFileGetCelsPerDirection(*(D2CellFileStrc**)((int)&dword_6FBA76B8 + iVar6));
		*(int*)((int)dword_6FBA7698 + iVar6) = iVar7;
		iVar6 = iVar6 + 4;
	} while (iVar6 < 0x10);
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\bubble1", "DATA\\GLOBAL");
	dword_6FBA7648 = (uint32_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\bubble2", "DATA\\GLOBAL");
	dword_6FBA764C = (uint32_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\bubble3", "DATA\\GLOBAL");
	byte_6FBA7650 = (uint8_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	wsprintfA(aCStack_104, "%s\\UncompOverlays\\bubble4", "DATA\\GLOBAL");
	byte_6FBA7654 = (uint8_t)(CLIENT_LoadCellFileWithFileSize(aCStack_104, (size_t*)(&iStack_110), 0));
	iVar6 = 0;
	do
	{
		iVar7 = D2CMP_CelFileGetCelsPerDirection(*(D2CellFileStrc**)((int)&dword_6FBA7648 + iVar6));
		*(int*)((int)dword_6FBA76D4 + iVar6) = iVar7;
		iVar6 = iVar6 + 4;
	} while (iVar6 < 0x10);
	byte_6FBA763C = 0;
}

//D2Client.0x6FAA7440
void __cdecl sub_6FAA7440()
{
	uint32_t* puVar1;

	puVar1 = &dword_6FBA76B8;
	do
	{
		if ((D2CellFileStrc*)*puVar1 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar1);
			*puVar1 = 0;
		}
		puVar1 = puVar1 + 1;
	} while ((int)puVar1 < (int)&byte_6FBA76C8);
	puVar1 = &dword_6FBA7648;
	do
	{
		if ((D2CellFileStrc*)*puVar1 != nullptr)
		{
			CLIENT_FreeCellFile((D2CellFileStrc*)*puVar1);
			*puVar1 = 0;
		}
		puVar1 = puVar1 + 1;
	} while ((int)puVar1 < (int)&dword_6FBA7658);
}

//D2Client.0x6FAA7490
void __fastcall sub_6FAA7490(int a1)
{
	FOG_10063(dword_6FBA76FC);
	FOG_10063(dword_6FBA7700);
	if (a1 != 0)
	{
		sub_6FAA6D40();
		return;
	}
}

//D2Client.0x6FAA74C0
void __fastcall sub_6FAA74C0(int a1)
{
	if (dword_6FBA7708 == 0)
	{
		dword_6FBA76AC = 0;
		dword_6FBA7708 = 1;
		dword_6FBA7688 = 1;
		dword_6FB751C0 = a1;
	}
}

//D2Client.0x6FAA74F0
void __cdecl sub_6FAA74F0()
{
	int iVar1;
	int iVar2;
	short* psVar3;
	int iVar4;

	iVar2 = D2GFX_CheckPerspective();
	iVar4 = 0;
	psVar3 = *(short**)(dword_6FBA7700 + 0x11c);
	if (-1 < *(int*)(dword_6FBA7700 + 0x110))
	{
		do
		{
			if (*psVar3 != 0)
			{
				if (iVar2 == 0)
				{
					*(int*)(psVar3 + 2) = *(int*)(psVar3 + 2) - dword_6FBA79D8;
					*(int*)(psVar3 + 4) = *(int*)(psVar3 + 4) - dword_6FBA79DC;
				}
				iVar1 = *(int*)(psVar3 + 10);
				*(int*)(psVar3 + 10) = iVar1 + -1;
				if (iVar1 + -1 < 1)
				{
					iVar1 = *(int*)(psVar3 + 8);
					psVar3[10] = 2;
					psVar3[0xb] = 0;
					*(int*)(psVar3 + 8) = iVar1 + 1;
					if ((int)dword_6FBA76D4[*(int*)(psVar3 + 6)] <= iVar1 + 1)
					{
						FOG_10065(dword_6FBA7700, iVar4 << 0x10);
					}
				}
			}
			iVar4 = iVar4 + 1;
			psVar3 = psVar3 + 0xc;
		} while (iVar4 <= *(int*)(dword_6FBA7700 + 0x110));
	}
}

//D2Client.0x6FAA7590
void __fastcall sub_6FAA7590(int a1, int a2, int a3, int a4)
{
	uint64_t DVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;

	pDVar2 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar2 != nullptr);
	iVar3 = FOG_10064(dword_6FBA76FC);
	if (iVar3 != -1)
	{
		iVar3 = *(int*)(dword_6FBA76FC + 0x11c) + (short)((uint32_t)iVar3 >> 0x10) * 0x18;
		iVar4 = D2GFX_CheckPerspective();
		uVar5 = (pDVar2->pSeed).nLowSeed;
		if (iVar4 == 0)
		{
			DVar1 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + (uint64_t)(pDVar2->pSeed).nHighSeed);
			iVar6 = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x50);
			(*(uint64_t*)&pDVar2->pSeed) = DVar1;
			iVar4 = iVar6 + -0x28;
			if (iVar4 < 0)
			{
				iVar4 = -iVar4;
			}
			iVar4 = iVar4 * -2 + 0x50;
			uVar5 = iVar4 * 2;
			if ((int)uVar5 < 1)
			{
				uVar5 = 0;
			}
			else if ((uVar5 & uVar5 - 1) == 0)
			{
				DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar1 + 4)));
				(*(uint64_t*)&pDVar2->pSeed) = DVar1;
				uVar5 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
			}
			else
			{
				DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar1 + 4)));
				(*(uint64_t*)&pDVar2->pSeed) = DVar1;
				uVar5 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar5);
			}
			*(uint32_t*)(iVar3 + 4) = (uVar5 - iVar4) + a1;
			*(int*)(iVar3 + 8) = iVar6 + a2;
		}
		else
		{
			DVar1 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + (uint64_t)(pDVar2->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar2->pSeed) = DVar1;
			*(int*)(iVar3 + 4) = (int)(((uint64_t)DVar1 & 0xffffffff) % 5) * 0x10000 + a3;
			DVar1 = (uint64_t)((uint64_t)(pDVar2->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar2->pSeed).nHighSeed);
			(*(uint64_t*)&pDVar2->pSeed) = DVar1;
			*(int*)(iVar3 + 8) = (int)(((uint64_t)DVar1 & 0xffffffff) % 5) * 0x10000 + a4;
		}
		DVar1 = (uint64_t)((uint64_t)(pDVar2->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar2->pSeed).nHighSeed);
		(*(uint64_t*)&pDVar2->pSeed) = DVar1;
		uVar5 = ((*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 1) + 2;
		*(uint32_t*)(iVar3 + 0xc) = uVar5;
		D2_ASSERT(3 >= uVar5);
		*(uint32_t*)(iVar3 + 0x10) = 0;
		*(uint32_t*)(iVar3 + 0x14) = 2;
	}
}

//D2Client.0x6FAA7760
void __fastcall sub_6FAA7760(int a1, int a2, int a3, int a4)
{
	uint64_t DVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		iVar3 = FOG_10064(dword_6FBA7700);
		if (iVar3 != -1)
		{
			iVar3 = *(int*)(dword_6FBA7700 + 0x11c) + (short)((uint32_t)iVar3 >> 0x10) * 0x18;
			iVar4 = D2GFX_CheckPerspective();
			uVar6 = (pDVar2->pSeed).nLowSeed;
			if (iVar4 == 0)
			{
				DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pDVar2->pSeed).nHighSeed);
				iVar5 = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x50);
				(*(uint64_t*)&pDVar2->pSeed) = DVar1;
				iVar4 = iVar5 + -0x28;
				if (iVar4 < 0)
				{
					iVar4 = -iVar4;
				}
				iVar4 = iVar4 * -2 + 0x50;
				uVar6 = iVar4 * 2;
				if ((int)uVar6 < 1)
				{
					uVar6 = 0;
				}
				else if ((uVar6 & uVar6 - 1) == 0)
				{
					DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar1 + 4)));
					(*(uint64_t*)&pDVar2->pSeed) = DVar1;
					uVar6 = uVar6 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar1 + 4)));
					(*(uint64_t*)&pDVar2->pSeed) = DVar1;
					uVar6 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar6);
				}
				*(uint32_t*)(iVar3 + 4) = (uVar6 - iVar4) + a1;
				*(int*)(iVar3 + 8) = iVar5 + -0x1e + a2;
			}
			else
			{
				DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pDVar2->pSeed).nHighSeed);
				(*(uint64_t*)&pDVar2->pSeed) = DVar1;
				*(int*)(iVar3 + 4) = ((int)(((uint64_t)DVar1 & 0xffffffff) % 5) + -2) * 0x10000 + a3;
				DVar1 = (uint64_t)((uint64_t)(pDVar2->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pDVar2->pSeed).nHighSeed);
				(*(uint64_t*)&pDVar2->pSeed) = DVar1;
				*(int*)(iVar3 + 8) = ((int)(((uint64_t)DVar1 & 0xffffffff) % 5) + -2) * 0x10000 + a4;
			}
			*(uint32_t*)(iVar3 + 0x10) = 0;
			*(uint32_t*)(iVar3 + 0xc) = 2;
			*(uint32_t*)(iVar3 + 0x14) = 2;
		}
		return;
	}
	FOG_DisplayAssert("hCtrlUnit", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAA7900
BOOL __fastcall sub_6FAA7900()
{
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int nLevelId;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
		DATATBLS_GetRainFromLevelsTxt(nLevelId);
		bVar1 = DATATBLS_GetMudFromLevelsTxt(nLevelId);
		return bVar1 != 0;
	}
	return false;
}

//D2Client.0x6FAA7940
void __cdecl sub_6FAA7940()
{
	D2SeedStrc* pDVar1;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	D2ActiveRoomStrc* pRoom;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	short* psVar8;
	uint32_t uVar9;
	int64_t lVar10;
	int64_t lVar11;
	float fVar12;
	float fStack_10;
	uint32_t local_8;

	pDVar3 = CUNIT_GetPlayer();
	iVar7 = 0;
	uVar9 = 0;
	local_8 = 0;
	if (pDVar3 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar3);
		iVar4 = DUNGEON_GetLevelIdFromRoom(pRoom);
		bVar2 = DATATBLS_GetRainFromLevelsTxt(iVar4);
		uVar9 = (uint32_t)(bVar2 != 0);
		bVar2 = DATATBLS_GetMudFromLevelsTxt(iVar4);
		local_8 = (uint32_t)(bVar2 != 0);
		if (uVar9 != 0)
			goto LAB_6faa79b6;
	}
	if (dword_6FBA7738 != 0)
	{
		if (*(int*)(dword_6FBA7704 + 0x114) != 0)
		{
			FOG_10063(dword_6FBA7704);
		}
		if (*(int*)(dword_6FBA76FC + 0x114) != 0)
		{
			FOG_10063(dword_6FBA76FC);
		}
	}
LAB_6faa79b6:
	if (((local_8 == 0) && (dword_6FBA773C != 0)) && (*(int*)(dword_6FBA7700 + 0x114) != 0))
	{
		FOG_10063(dword_6FBA7700);
	}
	dword_6FBA773C = local_8;
	dword_6FBA7738 = uVar9;
	uVar5 = sub_6FAABF80();
	pDVar3 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar3 != nullptr);
	pDVar1 = &pDVar3->pSeed;
	if (dword_6FBA770C < uVar5)
	{
		dword_6FBA770C = uVar5;
		if (uVar9 == 0)
		{
			byte_6FBA763C = 0.0;
		}
		else
		{
			if (*(int*)(dword_6FBA7704 + 0x114) != 0)
			{
				if (dword_6FBA7714 == 0)
				{
					fStack_10 = byte_6FBA763C * 0.15 + 0.85;
				}
				else
				{
					fStack_10 = FOG_10083_Cos_LUT((short)dword_6FBA7644);
					fStack_10 = fabs(fStack_10);
					if (fStack_10 < 0.25)
					{
						fStack_10 = 0.25;
					}
				}
				psVar8 = *(short**)(dword_6FBA7704 + 0x11c);
				if (-1 < *(int*)(dword_6FBA7704 + 0x110))
				{
					do
					{
						if (*psVar8 != 0)
						{
							lVar10 = (int64_t)((double)*(int*)(psVar8 + 10) * (double)fStack_10);
							fVar12 = FOG_10083_Cos_LUT((short)dword_6FBA7644);
							lVar11 = (int64_t)((double)fVar12 * (double)(int)lVar10);
							iVar4 = (int)lVar11;
							fVar12 = FOG_10084_Sin_LUT((short)dword_6FBA7644);
							lVar10 = (int64_t)((double)fVar12 * (double)(int)lVar10);
							iVar6 = *(int*)(psVar8 + 4) + ((int)lVar10 - dword_6FBA79DC);
							*(int*)(psVar8 + 4) = iVar6;
							if (*(int*)(psVar8 + 6) < iVar6)
							{
								psVar8[0xe] = 1;
								psVar8[0xf] = 0;
							}
							if (*(int*)(psVar8 + 0xe) != 0)
							{
								if (*(int*)(psVar8 + 0x10) == 0)
								{
									FOG_10065(dword_6FBA7704, iVar7 << 0x10);
									if (*(int*)(dword_6FBA7704 + 0x114) < dword_6FBA7658)
									{
										sub_6FAA7D70((uint64_t*)pDVar1);
									}
								}
								else
								{
									iVar4 = 0;
									psVar8[10] = 0;
									psVar8[0xb] = 0;
									*(int*)(psVar8 + 0x10) = *(int*)(psVar8 + 0x10) + -1;
								}
							}
							if (*psVar8 != 0)
							{
								if ((dword_6FBA7714 != 0) && (*(int*)(psVar8 + 0xe) == 0))
								{
									fVar12 = FOG_10084_Sin_LUT((short)((uint32_t)(dword_6FBA772C << 9) / 0x19) +
									                               (short)*(uint32_t*)(psVar8 + 0xc) &
									                           0x1ff);
									lVar10 = (int64_t)((double)fVar12 + (double)fVar12);
									iVar4 = iVar4 + (int)lVar10;
								}
								iVar4 = (*(int*)(psVar8 + 2) - dword_6FBA79D8) + iVar4;
								*(int*)(psVar8 + 2) = iVar4;
								if (gnScreenWidth <= iVar4)
								{
									*(int*)(psVar8 + 2) = iVar4 - gnScreenWidth;
								}
								if (*(int*)(psVar8 + 2) < 0)
								{
									*(int*)(psVar8 + 2) = *(int*)(psVar8 + 2) + gnScreenWidth;
								}
							}
						}
						iVar7 = iVar7 + 1;
						psVar8 = psVar8 + 0x14;
					} while (iVar7 <= *(int*)(dword_6FBA7704 + 0x110));
				}
				dword_6FBA772C = dword_6FBA772C + 1;
			}
			iVar7 = D2GFX_CheckPerspective();
			iVar4 = 0;
			psVar8 = *(short**)(dword_6FBA76FC + 0x11c);
			if (-1 < *(int*)(dword_6FBA76FC + 0x110))
			{
				do
				{
					if (*psVar8 != 0)
					{
						if (iVar7 == 0)
						{
							*(int*)(psVar8 + 2) = *(int*)(psVar8 + 2) - dword_6FBA79D8;
							*(int*)(psVar8 + 4) = *(int*)(psVar8 + 4) - dword_6FBA79DC;
						}
						iVar6 = *(int*)(psVar8 + 10);
						*(int*)(psVar8 + 10) = iVar6 + -1;
						if (iVar6 + -1 < 1)
						{
							iVar6 = *(int*)(psVar8 + 8);
							psVar8[10] = 2;
							psVar8[0xb] = 0;
							*(int*)(psVar8 + 8) = iVar6 + 1;
							if ((int)dword_6FBA7698[*(int*)(psVar8 + 6)] <= iVar6 + 1)
							{
								FOG_10065(dword_6FBA76FC, iVar4 << 0x10);
							}
						}
					}
					iVar4 = iVar4 + 1;
					psVar8 = psVar8 + 0xc;
				} while (iVar4 <= *(int*)(dword_6FBA76FC + 0x110));
			}
			if ((dword_6FBA771C == 0) || (dword_6FBA7724 == 2))
			{
				iVar7 = dword_6FBA7724;
				if (dword_6FBA7730 == 0)
				{
					iVar7 = dword_6FBA7724 + 1;
					if (iVar7 == 4)
					{
						iVar7 = 0;
					}
					iVar4 = (&dword_6FBA76E4)[iVar7];
					uVar9 = sub_6FAA88F0((uint64_t*)pDVar1, (&dword_6FBA7660)[iVar7]);
					dword_6FBA7730 = uVar9 + iVar4;
					dword_6FBA7734 = dword_6FBA7730;
					sub_6FAA6AE0(iVar7);
				}
				dword_6FBA7730 = dword_6FBA7730 - 1;
				if (iVar7 == 1)
				{
					dword_6FBA7658 = (int)(((int64_t)(int)(dword_6FBA7734 - dword_6FBA7730) *
					                               (int64_t)dword_6FBA76A8 &
					                           0xffffffffU) /
					                       (uint64_t)dword_6FBA7734);
				}
				else if (iVar7 == 3)
				{
					dword_6FBA7658 = (dword_6FBA76A8 * dword_6FBA7730) / dword_6FBA7734;
				}
				byte_6FBA763C = (float)dword_6FBA7658 * 0.00390625;
				sub_6FAA80C0((uint64_t*)pDVar1);
			}
			else
			{
				sub_6FAA6AE0(2);
				sub_6FAA80C0((uint64_t*)pDVar1);
			}
		}
		if (local_8 != 0)
		{
			sub_6FAA74F0();
			return;
		}
	}
}

//D2Client.0x6FAA7D70
void __fastcall sub_6FAA7D70(uint64_t* a1)
{
	uint8_t* puVar1;
	uint8_t uVar2;
	uint64_t uVar3;
	float fVar4;
	bool bVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	DisplayType DVar10;
	D2ActiveRoomStrc* pRoom;
	int iVar11;
	uint8_t* puVar12;
	int64_t lVar13;

	iVar6 = FOG_10064(dword_6FBA7704);
	if (iVar6 == -1)
	{
		return;
	}
	iVar6 = *(int*)(dword_6FBA7704 + 0x11c) + (short)((uint32_t)iVar6 >> 0x10) * 0x28;
	uVar7 = 0;
	*(uint32_t*)(iVar6 + 0x1c) = 0;
	iVar9 = gnScreenWidth;
	if (0 < gnScreenWidth)
	{
		if ((gnScreenWidth & gnScreenWidth - 1U) == 0)
		{
			uVar7 = sub_6FAA88D0((uint32_t*)a1);
			uVar7 = uVar7 & iVar9 - 1U;
		}
		else
		{
			uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
			*a1 = uVar3;
			uVar7 = (uint32_t)((uVar3 & 0xffffffff) % (uint64_t)(uint32_t)iVar9);
		}
	}
	*(uint32_t*)(iVar6 + 4) = uVar7;
	iVar9 = gnScreenHeight;
	uVar7 = gnScreenHeight - 0x57;
	if ((int)uVar7 < 1)
	{
		uVar7 = 0;
	}
	else if ((uVar7 & gnScreenHeight - 0x58U) == 0)
	{
		uVar7 = sub_6FAA88D0((uint32_t*)a1);
		uVar7 = uVar7 & iVar9 - 0x58U;
	}
	else
	{
		uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
		*a1 = uVar3;
		uVar7 = (uint32_t)((uVar3 & 0xffffffff) % (uint64_t)uVar7);
	}
	*(uint32_t*)(iVar6 + 0xc) = uVar7 + 0x28;
	uVar8 = uVar7 + 0x3c;
	if ((int)uVar8 < 1)
	{
		uVar8 = 0;
	}
	else if ((uVar8 & uVar7 + 0x3b) == 0)
	{
		uVar8 = sub_6FAA88D0((uint32_t*)a1);
		uVar8 = uVar8 & uVar7 + 0x3b;
	}
	else
	{
		uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
		*a1 = uVar3;
		uVar8 = (uint32_t)((uVar3 & 0xffffffff) % (uint64_t)uVar8);
	}
	*(uint32_t*)(iVar6 + 8) = uVar8 - 0x14;
	uVar7 = sub_6FAA88D0((uint32_t*)a1);
	*(uint32_t*)(iVar6 + 0x18) = uVar7 & 0x1ff;
	fVar4 = (float)(*(int*)(iVar6 + 0xc) + -0x28) / (float)(gnScreenHeight + -0x57);
	if (dword_6FBA7714 == 0)
	{
		uVar7 = sub_6FAA88F0(a1, 0xc);
		iVar9 = ENVIRONMENT_GetPeriodOfDayFromAct(ghAct, nullptr);
		switch (iVar9)
		{
		case 0:
			uVar2 = byte_6FBA7670[uVar7];
			*(uint8_t*)(iVar6 + 0x25) = 0x7f;
			*(uint8_t*)(iVar6 + 0x24) = uVar2;
			break;
		case 1:
		case 3:
			uVar2 = byte_6FBA762C[uVar7];
			*(uint8_t*)(iVar6 + 0x25) = 0xff;
			*(uint8_t*)(iVar6 + 0x24) = uVar2;
			break;
		case 2:
			uVar2 = byte_6FBA768C[uVar7];
			*(uint8_t*)(iVar6 + 0x25) = 0xff;
			*(uint8_t*)(iVar6 + 0x24) = uVar2;
		}
		lVar13 = (int64_t)((double)fVar4 * (double)-8.0);
		*(int*)(iVar6 + 0x10) = 4 - (int)lVar13;
		lVar13 = (int64_t)((double)fVar4 * (double)-15.0);
		*(uint32_t*)(iVar6 + 0x20) = 3;
		*(int*)(iVar6 + 0x14) = 0xf - (int)lVar13;
		return;
	}
	puVar1 = (uint8_t*)(iVar6 + 0x25);
	*puVar1 = 0xff;
	*a1 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
	bVar5 = true;
	*(uint32_t*)(iVar6 + 0x20) = 1;
	lVar13 = (int64_t)((double)fVar4 * (double)-28.0);
	*(int*)(iVar6 + 0x14) = 8 - (int)lVar13;
	iVar9 = ((*(int*)(iVar6 + 0xc) + -0x28) * 7) / (gnScreenHeight + -0x57);
	*(int*)(iVar6 + 0x10) = iVar9;
	if (dword_6FBA7718 != 0)
	{
		*(int*)(iVar6 + 0x10) = iVar9 + 1;
	}
	iVar9 = *(int*)(iVar6 + 0x10);
	D2_ASSERT(!((7 < iVar9) || (iVar9 < 0)));
	puVar12 = (uint8_t*)(iVar6 + 0x24);
	DVar10 = D2GFX_GetDisplayType();
	if ((0 < (int)DVar10) && (((int)DVar10 < 4 || (DVar10 == DISPLAYTYPE_DIRECT3D))))
	{
		bVar5 = false;
	}
	pRoom = CUNIT_GetPlayerRoom();
	DUNGEON_GetLevelIdFromRoom(pRoom);
	iVar6 = ENVIRONMENT_GetPeriodOfDayFromAct(ghAct, nullptr);
	D2_ASSERT(!((iVar6 < 0) || (3 < iVar6)));
	if (puVar1 != nullptr)
	{
		*puVar1 = byte_6FB6E189[iVar6 * 2];
	}
	if (puVar12 == nullptr)
	{
		return;
	}
	iVar9 = iVar9 * 0xc + (iVar9 * 0xc >> 0x1f & 7U);
	iVar11 = iVar9 >> 3;
	if (bVar5)
	{
		*puVar12 = byte_6FBA76C8[iVar11];
		return;
	}
	uVar7 = iVar9 >> 0x1f;
	if (iVar6 != 1)
	{
		if (iVar6 == 2)
		{
			*puVar12 = byte_6FBA767C[(int)(iVar11 + (uVar7 & 3)) >> 2];
			return;
		}
		if (iVar6 != 3)
			goto LAB_6faa7fb4;
	}
	iVar11 = (int)(iVar11 - uVar7) >> 1;
LAB_6faa7fb4:
	*puVar12 = byte_6FBA767C[iVar11];
}

//D2Client.0x6FAA80C0
void __fastcall sub_6FAA80C0(uint64_t* a1)
{
	uint32_t uVar1;
	int64_t lVar2;
	uint64_t uVar3;
	int iVar4;

	if (*(int*)(dword_6FBA7704 + 0x114) < dword_6FBA7658)
	{
		do
		{
			sub_6FAA7D70(a1);
		} while (*(int*)(dword_6FBA7704 + 0x114) < dword_6FBA7658);
	}
	iVar4 = 2 - (uint32_t)(dword_6FBA7714 != 0);
	if (dword_6FBA7638 < dword_6FBA7644)
	{
		dword_6FBA7644 = dword_6FBA7644 - iVar4;
		if (dword_6FBA7644 < dword_6FBA7638)
		{
			dword_6FBA7644 = dword_6FBA7638;
		}
	}
	else if (dword_6FBA7644 < dword_6FBA7638)
	{
		iVar4 = iVar4 + dword_6FBA7644;
		dword_6FBA7644 = dword_6FBA7638;
		if (iVar4 <= dword_6FBA7638)
		{
			dword_6FBA7644 = iVar4;
		}
	}
	dword_6FBA765C = dword_6FBA765C + -1;
	if (dword_6FBA765C == 0)
	{
		lVar2 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5;
		if (dword_6FBA7714 == 0)
		{
			uVar3 = lVar2 + (uint64_t) * (uint32_t*)((int)a1 + 4);
			*a1 = uVar3;
			dword_6FBA765C = (int)((uVar3 & 0xffffffff) % 0x177) + 0x7d;
			uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
			*a1 = uVar3;
			dword_6FBA7638 = (int)((uVar3 & 0xffffffff) % 0x47) + 0x5c;
		}
		else
		{
			uVar3 = lVar2 + (uint64_t) * (uint32_t*)((int)a1 + 4);
			*a1 = uVar3;
			uVar1 = dword_6FBA76F4;
			iVar4 = dword_6FBA76B0;
			dword_6FBA765C = (int)((uVar3 & 0xffffffff) % 0x36b) + 0xfa;
			dword_6FBA7638 = dword_6FBA76B0;
			if (0 < (int)dword_6FBA76F4)
			{
				if ((dword_6FBA76F4 & dword_6FBA76F4 - 1) == 0)
				{
					uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
					uVar1 = dword_6FBA76F4 - 1;
					*a1 = uVar3;
					dword_6FBA7638 = (uVar1 & (uint32_t)uVar3) + iVar4;
				}
				else
				{
					uVar3 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5 + (uint64_t) * (uint32_t*)((int)a1 + 4);
					*a1 = uVar3;
					dword_6FBA7638 = (int)((uVar3 & 0xffffffff) % (uint64_t)uVar1) + iVar4;
				}
			}
		}
	}
	if ((dword_6FBA7708 != 0) && (dword_6FBA7640 = dword_6FBA7640 + -1, dword_6FBA7640 == 0))
	{
		dword_6FBA7688 = 1;
	}
}

//D2Client.0x6FAA8240
void __cdecl sub_6FAA8240()
{
	D2SeedStrc* pDVar1;
	uint64_t DVar2;
	uint8_t bVar3;
	D2UnitStrc* pDVar4;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	int nYEnd;
	int iVar10;
	int iVar11;
	short* psVar12;
	bool bVar13;
	int64_t lVar14;
	uint64_t uVar15;
	float fVar16;
	uint8_t nColor;
	int local_4;

	pDVar4 = CUNIT_GetPlayer();
	bVar13 = false;
	if (pDVar4 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar4);
		iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom);
		bVar3 = DATATBLS_GetRainFromLevelsTxt(iVar5);
		bVar13 = bVar3 != 0;
		DATATBLS_GetMudFromLevelsTxt(iVar5);
	}
	pDVar4 = CUNIT_GetPlayer();
	D2_ASSERT(pDVar4 != nullptr);
	pDVar1 = &pDVar4->pSeed;
	if ((dword_6FBA7708 != 0) && (dword_6FBA7688 != 0))
	{
		dword_6FBA7688 = dword_6FBA7688 + -1;
		if (dword_6FBA7688 == 0)
		{
			if (dword_6FBA76AC == 0)
			{
				dword_6FBA7640 = 3;
				dword_6FBA76AC = 1;
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar4->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar2;
				dword_6FBA76AC = 0;
				dword_6FBA7640 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x5dc) + 500;
				if (dword_6FB751C0 == 0)
				{
					dword_6FB751C0 = 1;
				}
				else
				{
					DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar4->pSeed).nHighSeed);
					*(uint64_t*)pDVar1 = DVar2;
					iVar5 = sub_6FB55820(0xca, nullptr,
					    (float)((int)(((uint64_t)DVar2 & 0xffffffff) % 0x32) + 0x19), 0.0, 0);
					if (iVar5 != 0)
					{
						uVar15 = (uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pDVar4->pSeed).nHighSeed;
						pDVar1->nLowSeed = (uint32_t)uVar15;
						DVar2 = (uint64_t)((uVar15 & 0xffffffff) * 0x6ac690c5 + (uVar15 >> 0x20));
						*(uint64_t*)pDVar1 = DVar2;
						sub_6FB55710(iVar5, (int)(((uint64_t)DVar2 & 0xffffffff) % 400) + -200,
						    (float)((int)((uVar15 & 0xffffffff) % 400) + -200), 0.0);
					}
				}
			}
		}
		iVar5 = gnScreenWidth;
		if (9 < gnFramesPerSecond)
		{
			iVar11 = 0;
			iVar7 = gnScreenHeight + -0x2f;
			iVar6 = sub_6FAB5750();
			if (iVar6 == 1)
			{
				iVar5 = iVar5 + ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2) * -2;
			}
			else if (iVar6 == 2)
			{
				iVar11 = ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2) * 2;
			}
			D2GFX_DrawBox(iVar11, 0, iVar5, iVar7, 0xff, DRAWMODE_NORMAL);
			return;
		}
	}
	if ((!bVar13) || (*(int*)(dword_6FBA7704 + 0x114) == 0))
	{
		return;
	}
	iVar7 = D2GFX_CheckLowQuality();
	iVar5 = gnScreenWidth;
	if (iVar7 == 0)
	{
		iVar7 = gnScreenHeight + -0x2f;
		iVar11 = 0;
		iVar6 = sub_6FAB5750();
		if (iVar6 == 1)
		{
			iVar5 = iVar5 + ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2) * -2;
		}
		else if (iVar6 == 2)
		{
			iVar11 = ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2) * 2;
		}
		local_4 = 0;
		psVar12 = *(short**)(dword_6FBA7704 + 0x11c);
		if (-1 < *(int*)(dword_6FBA7704 + 0x110))
		{
			do
			{
				if (*psVar12 != 0)
				{
					if (dword_6FBA7714 == 0)
					{
						if (*(int*)(psVar12 + 0xe) == 0)
						{
							fVar16 = FOG_10083_Cos_LUT((short)dword_6FBA7644);
							lVar14 = (int64_t)((double)fVar16 * (double)*(int*)(psVar12 + 8));
							iVar10 = (int)lVar14;
							fVar16 = FOG_10084_Sin_LUT((short)dword_6FBA7644);
							uVar15 = (int64_t)((double)fVar16 * (double)*(int*)(psVar12 + 8));
							iVar6 = *(int*)(psVar12 + 4);
							uVar9 = *(int*)(psVar12 + 6) - iVar6;
							if ((int)uVar9 < (int)uVar15)
							{
								iVar10 = (int)(uVar9 * iVar10) / (int)uVar15;
								uVar15 = (uint64_t)uVar9;
							}
							iVar8 = *(int*)(psVar12 + 2);
							iVar10 = iVar10 + iVar8;
							nYEnd = (int)uVar15 + iVar6;
							if (((((iVar11 <= iVar8) && (iVar8 < iVar5)) && (-1 < iVar6)) && (iVar6 < iVar7)) ||
							    (((iVar11 <= iVar10 && (iVar10 < iVar5)) && ((-1 < nYEnd && (nYEnd < iVar7))))))
							{
								bVar3 = *(uint8_t*)((int)psVar12 + 0x25);
								nColor = *(uint8_t*)(psVar12 + 0x12);
								goto LAB_6faa8658;
							}
						}
						else
						{
							iVar8 = *(int*)(psVar12 + 2);
							if (((iVar11 <= iVar8) && (iVar8 < iVar5)) &&
							    ((iVar6 = *(int*)(psVar12 + 4), -1 < iVar6 && (iVar6 < iVar7))))
							{
								bVar3 = *(uint8_t*)((int)psVar12 + 0x25);
								nColor = *(uint8_t*)(psVar12 + 0x12);
								iVar10 = iVar8;
								nYEnd = iVar6;
							LAB_6faa8658:
								D2GFX_DrawLine(iVar8, iVar6, iVar10, nYEnd, nColor, bVar3);
							}
						}
					}
					else
					{
						iVar6 = *(int*)(psVar12 + 2);
						if (((((iVar11 <= iVar6) && (iVar6 < iVar5)) &&
						         (iVar10 = *(int*)(psVar12 + 4), -1 < iVar10)) &&
						        ((iVar10 < iVar7 && (iVar8 = *(int*)(psVar12 + 8), iVar8 < 8)))) &&
						    (-1 < iVar8))
						{
							iVar8 = iVar8 * 0x10;
							D2GFX_DrawLine(*(int*)(byte_6FB6E190 + iVar8) + iVar6,
							    *(int*)(byte_6FB6E194 + iVar8) + iVar10,
							    *(int*)(byte_6FB6E198 + iVar8) + iVar6,
							    *(int*)(byte_6FB6E19C + iVar8) + iVar10, *(uint8_t*)(psVar12 + 0x12),
							    *(uint8_t*)((int)psVar12 + 0x25));
							bVar3 = *(uint8_t*)((int)psVar12 + 0x25);
							nColor = *(uint8_t*)(psVar12 + 0x12);
							iVar8 = *(int*)(psVar12 + 8) * 0x10;
							nYEnd = *(int*)(byte_6FB6E1AC + iVar8) + *(int*)(psVar12 + 4);
							iVar10 = *(int*)(byte_6FB6E1A8 + iVar8) + *(int*)(psVar12 + 2);
							iVar6 = *(int*)(byte_6FB6E1A4 + iVar8) + *(int*)(psVar12 + 4);
							iVar8 = *(int*)(byte_6FB6E1A0 + iVar8) + *(int*)(psVar12 + 2);
							goto LAB_6faa8658;
						}
					}
				}
				local_4 = local_4 + 1;
				psVar12 = psVar12 + 0x14;
			} while (local_4 <= *(int*)(dword_6FBA7704 + 0x110));
		}
	}
}

//D2Client.0x6FAA8690
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAA8690(int a12, int a2)
{
	int a1;
	int iVar1;
	int extraout_EAX;
	int nXPos;
	int iVar2;
	short* psVar3;
	D2GfxDataStrc* pDVar4;
	int iStack_64;
	int iStack_60;
	int iStack_5c;
	int local_58;
	int iStack_54;
	int iStack_50;
	int iStack_4c;
	D2GfxDataStrc DStack_48;

	local_58 = a12;
	iStack_50 = D2GFX_CheckPerspective();
	iStack_60 = gnScreenWidth;
	iVar2 = 0;
	iStack_54 = gnScreenHeight + -0x2f;
	iStack_64 = 0;
	iVar1 = sub_6FAB5750();
	a1 = local_58;
	if (iVar1 == 1)
	{
		iVar1 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		iVar2 = -iVar1;
		iStack_60 = iStack_60 + iVar1 * -2;
	}
	else if (iVar1 == 2)
	{
		iVar2 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
		iStack_64 = iVar2 * 2;
	}
	psVar3 = *(short**)(a12 + 0x11c);
	pDVar4 = &DStack_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar4->pCurrentCell = nullptr;
		pDVar4 = (D2GfxDataStrc*)&pDVar4->pCellFile;
	}
	iStack_5c = 0;
	if (-1 < *(int*)(local_58 + 0x110))
	{
		do
		{
			if (*psVar3 != 0)
			{
				if (iStack_50 == 0)
				{
					iVar1 = *(int*)(psVar3 + 4);
					nXPos = *(int*)(psVar3 + 2) + iVar2;
					if ((((iStack_64 <= nXPos) && (nXPos < iStack_60)) && (-1 < iVar1)) && (iVar1 < iStack_54))
					{
						DStack_48.pCellFile = *(D2CellFileStrc**)(a2 + *(int*)(psVar3 + 6) * 4);
						DStack_48.nFrame = *(uint32_t*)(psVar3 + 8);
						TEXTURE_CelDraw(&DStack_48, nXPos, iVar1, 0xffffffff, DRAWMODE_MODULATE, nullptr);
					}
				}
				else
				{
					iVar1 = SCALE_CheckPerspectivePosition(*(int*)(psVar3 + 2), *(int*)(psVar3 + 4));
					if (iVar1 != 0)
					{
						SCALE_AdjustPerspectivePosition(*(int*)(psVar3 + 2), *(int*)(psVar3 + 4), 0, &local_58, &iStack_4c);
						local_58 = local_58 + iVar2;
						if (((iStack_64 <= local_58) && (local_58 < iStack_60)) &&
						    ((-1 < iStack_4c && (iStack_4c < iStack_54))))
						{
							DStack_48.pCellFile = *(D2CellFileStrc**)(a2 + *(int*)(psVar3 + 6) * 4);
							DStack_48.nFrame = *(uint32_t*)(psVar3 + 8);
							TEXTURE_CelDraw(&DStack_48, local_58, iStack_4c, 0xffffffff, DRAWMODE_MODULATE, nullptr);
							if (extraout_EAX != 0)
								goto LAB_6faa880e;
						}
					}
					FOG_10065(a1, iStack_5c << 0x10);
				}
			}
		LAB_6faa880e:
			iStack_5c = iStack_5c + 1;
			psVar3 = psVar3 + 0xc;
		} while (iStack_5c <= *(int*)(a1 + 0x110));
	}
}

//D2Client.0x6FAA8830
void __cdecl sub_6FAA8830()
{
	if (*(int*)(dword_6FBA76FC + 0x114) != 0)
	{
		sub_6FAA8690(dword_6FBA76FC, (int)&dword_6FBA76B8);
	}
	if (*(int*)(dword_6FBA7700 + 0x114) != 0)
	{
		sub_6FAA8690(dword_6FBA7700, (int)&dword_6FBA7648);
		return;
	}
}

//D2Client.0x6FAA8870
bool __cdecl sub_6FAA8870()
{
	uint8_t bVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int nLevelId;
	bool bVar2;

	if (dword_6FBA7714 != 0)
	{
		return false;
	}
	pUnit = CUNIT_GetPlayer();
	bVar2 = false;
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		nLevelId = DUNGEON_GetLevelIdFromRoom(pRoom);
		bVar1 = DATATBLS_GetRainFromLevelsTxt(nLevelId);
		bVar2 = bVar1 != 0;
		DATATBLS_GetMudFromLevelsTxt(nLevelId);
	}
	return bVar2;
}

//D2Client.0x6FAA88B0
double __fastcall sub_6FAA88B0()
{
	return (double)byte_6FBA763C;
}

//D2Client.0x6FAA88C0
void __fastcall sub_6FAA88C0(uint32_t a1)
{
	byte_6FBA7710 = a1;
}

//D2Client.0x6FAA88D0
int32_t __fastcall sub_6FAA88D0(uint32_t* a1)
{
	*(uint64_t*)a1 = (uint64_t)*a1 * 0x6ac690c5 + (uint64_t)a1[1];
	return 0;
}

//D2Client.0x6FAA88F0
uint32_t __fastcall sub_6FAA88F0(uint64_t* a1, uint32_t a2)
{
	int64_t lVar1;
	uint64_t uVar2;

	if ((int)a2 < 1)
	{
		return 0;
	}
	lVar1 = (uint64_t)(uint32_t)*a1 * 0x6ac690c5;
	if ((a2 & a2 - 1) != 0)
	{
		uVar2 = lVar1 + (uint64_t) * (uint32_t*)((int)a1 + 4);
		*a1 = uVar2;
		return (uint32_t)((uVar2 & 0xffffffff) % (uint64_t)a2);
	}
	uVar2 = lVar1 + (uint64_t) * (uint32_t*)((int)a1 + 4);
	*a1 = uVar2;
	return a2 - 1 & (uint32_t)uVar2;
}

//D2Client.0x6FAA8940
void __cdecl sub_6FAA8940()
{
	sub_6FAAC320((uint32_t*)&byte_6FBA7828);
	atexit(sub_6FAA8960);
}

//D2Client.0x6FAA8960
void __cdecl sub_6FAA8960()
{
	sub_6FAA8970((uint32_t*)&byte_6FBA7828);
}

//D2Client.0x6FAA8970
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAA8970(uint32_t* a1)
{
	void* pvVar1;
	int iVar2;
	int* piVar3;
	int* piVar4;
	int extraout_EDX;
	int extraout_EDX_00;
	int extraout_EDX_01;
	int extraout_EDX_02;
	int extraout_EDX_03;
	int extraout_EDX_04;
	int iVar5;
	int extraout_EDX_05;
	uint32_t uVar6;
	int iVar7;
	void* pvStack_c;
	code* pcStack_8;
	int iStack_4;

	iStack_4 = 0xffffffff;
	DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 0x14));
	*a1 = (uint32_t)(&gpuint8_t_6FB6E24C);
	iStack_4 = 2;
	iVar5 = extraout_EDX;
	while (pvVar1 = (void*)a1[0x10], 0 < (int)pvVar1)
	{
		sub_6FAACEE0((int)pvVar1);
		SMemFree(pvVar1, str_6FB75B40, -2, 0);
		iVar5 = extraout_EDX_00;
	}
	while (pvVar1 = (void*)a1[0xc], 0 < (int)pvVar1)
	{
		sub_6FAAC7B0(pvVar1, iVar5, 0);
		SMemFree(pvVar1, str_6FB75B28, -2, 0);
		iVar5 = extraout_EDX_01;
	}
	(*(uint8_t*)((uint8_t*)&iStack_4 + 0)) = 3;
	piVar4 = (int*)(a1 + 0xf);
	while (0 < (int)a1[0x10])
	{
		sub_6FAAD010((int*)(a1[0xe] + a1[0x10]));
		iVar5 = extraout_EDX_02;
	}
	(*(uint8_t*)((uint8_t*)&iStack_4 + 0)) = 1;
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, iVar5, 0xffffffff);
		*piVar3 = *piVar4;
		iVar5 = *piVar4;
		*(uint32_t*)(iVar5 + 4) = a1[0x10];
		*piVar4 = 0;
		a1[0x10] = 0;
	}
	(*(uint8_t*)((uint8_t*)&iStack_4 + 0)) = 4;
	piVar4 = (int*)(a1 + 0xb);
	while (0 < (int)a1[0xc])
	{
		sub_6FAAD010((int*)(a1[10] + a1[0xc]));
		iVar5 = extraout_EDX_03;
	}
	iStack_4 = (uint32_t)(*(uint8_t*)((uint8_t*)&iStack_4 + 1)) << 8;
	if (*piVar4 != 0)
	{
		piVar3 = (int*)sub_6FAACE10(piVar4, iVar5, 0xffffffff);
		*piVar3 = *piVar4;
		*(uint32_t*)(*piVar4 + 4) = a1[0xc];
		*piVar4 = 0;
		a1[0xc] = 0;
	}
	*a1 = (uint32_t)(&gpuint8_t_6FB6E23C);
	a1[4] = 0;
	iStack_4 = 6;
	sub_6FAACE60((int*)(a1 + 1));
	uVar6 = 0;
	if (a1[6] != 0)
	{
		iVar7 = 0;
		iVar5 = extraout_EDX_04;
		do
		{
			while (true)
			{
				iVar2 = *(int*)(a1[7] + iVar7 + 8);
				if (iVar2 < 1)
					break;
				piVar4 = (int*)sub_6FAACE40((void*)(a1[7] + iVar7), iVar5, iVar2);
				sub_6FAAD010(piVar4);
				iVar5 = extraout_EDX_05;
			}
			uVar6 = uVar6 + 1;
			iVar7 = iVar7 + 0xc;
		} while (uVar6 < (uint32_t)a1[6]);
	}
	iStack_4 = CONCAT31((*(uint8_t*)((uint8_t*)&iStack_4 + 1)), 5);
	sub_6FAACBC0((int)(a1 + 5));
	iStack_4 = 7;
	sub_6FAACE60((int*)(a1 + 1));
	iStack_4 = 0xffffffff;
	sub_6FAAD010((int*)(a1 + 2));
}

//D2Client.0x6FAA8B10
void __fastcall sub_6FAA8B10(int a1)
{
	dword_6FBA79B4 = a1;
}

//D2Client.0x6FAA8B20
void __fastcall sub_6FAA8B20(int a1)
{
	dword_6FBA79B8 = a1;
}

//D2Client.0x6FAA8B30
int __cdecl sub_6FAA8B30()
{
	return dword_6FBA79B8;
}

//D2Client.0x6FAA8B40
void __fastcall sub_6FAA8B40(int a1)
{
	dword_6FBA79BC = a1;
}

//D2Client.0x6FAA8B50
uint32_t __cdecl sub_6FAA8B50()
{
	uint32_t uVar1;

	uVar1 = 0;
	if (dword_6FBA79B4 != 0)
	{
		uVar1 = 8;
	}
	if (dword_6FBA79B8 != 0)
	{
		uVar1 = 8;
	}
	if (dword_6FBA79BC != 0)
	{
		uVar1 = uVar1 | 4;
	}
	return uVar1;
}

//D2Client.0x6FAA8B80
void __cdecl sub_6FAA8B80()
{
	dword_6FBA79B0 = 1;
}

//D2Client.0x6FAA8B90
uint32_t __cdecl sub_6FAA8B90()
{
	return dword_6FB7580C;
}

//D2Client.0x6FAA8BA0
uint32_t __cdecl sub_6FAA8BA0()
{
	return dword_6FB75810;
}

//D2Client.0x6FAA8BB0
uint32_t __cdecl sub_6FAA8BB0()
{
	return dword_6FBA79A8;
}

//D2Client.0x6FAA8BC0
void __fastcall sub_6FAA8BC0(uint32_t a1, int a2, int a3)
{
	dword_6FBA79B4 = 0;
	if (dword_6FBA7970 != 0)
	{
		sub_6FB23960();
		sub_6FAB6A50();
		*(uint32_t*)(a3 + 0x18) = 0;
		return;
	}
	sub_6FAAD420((uint32_t)a1);
	dword_6FBA79D4 = 1;
	*(uint32_t*)(a3 + 0x18) = 1;
	*(uint32_t*)(a3 + 0x1c) = 0;
}

//D2Client.0x6FAA8C10
void __cdecl sub_6FAA8C10(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	uint8_t bVar2;

	dword_6FB7580C = 4;
	dword_6FBA79B0 = 0;
	sub_6FAB5D50();
	if (dword_6FBA796C != 0)
	{
		dword_6FBA79A8 = 1;
		pDVar1 = CUNIT_GetPlayer();
		bVar2 = 0;
		if (dword_6FBA79B4 != 0)
		{
			bVar2 = 8;
		}
		if (dword_6FBA79B8 != 0)
		{
			bVar2 = 8;
		}
		if (dword_6FBA79BC != 0)
		{
			bVar2 = bVar2 | 4;
		}
		if ((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0))
		{
			dword_6FBA79A8 = sub_6FB49920(0, (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam,
			    (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2), bVar2);
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAA8CB0
bool __cdecl sub_6FAA8CB0()
{
	return dword_6FBA79C4 != 0;
}

//D2Client.0x6FAA8CC0
void __cdecl sub_6FAA8CC0(uint32_t a1)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	uint8_t bVar4;

	dword_6FB7580C = 0x10;
	dword_6FBA79A8 = 0;
	dword_6FBA79C4 = 0;
	dword_6FBA79B0 = 0;
	sub_6FAB5D50();
	if (dword_6FBA796C != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if ((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0))
		{
			bVar4 = 0;
			if (dword_6FBA79B4 != 0)
			{
				bVar4 = 8;
			}
			if (dword_6FBA79B8 != 0)
			{
				bVar4 = 8;
			}
			if (dword_6FBA79BC != 0)
			{
				bVar4 = bVar4 | 4;
			}
			iVar2 = sub_6FB57BD0();
			iVar3 = sub_6FB57BC0();
			sub_6FB49920(2, iVar3, iVar2, bVar4);
		}
	}
}

//D2Client.0x6FAA8D50
void __cdecl sub_6FAA8D50(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	bool bVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint8_t bVar5;
	uint32_t uVar6;
	uint32_t uVar7;

	bVar1 = false;
	dword_6FB75810 = 4;
	dword_6FBA79B0 = 0;
	sub_6FAB5D50();
	if (dword_6FBA796C != 0)
	{
		iVar3 = sub_6FAB5750();
		if (iVar3 != 3)
		{
			uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
			uVar7 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
			bVar2 = false;
			iVar3 = sub_6FAB5750();
			if ((((iVar3 == 2) && (uVar6 != 0)) && ((int)uVar6 < gnScreenWidth / 2)) &&
			    ((uVar7 != 0 && ((int)uVar7 < gnScreenHeight + -0x2f))))
			{
				bVar2 = true;
			}
			iVar3 = sub_6FAB5750();
			if (((iVar3 == 1) && (gnScreenWidth / 2 < (int)uVar6)) &&
			    (((int)uVar6 < gnScreenWidth && ((uVar7 != 0 && ((int)uVar7 < gnViewHeight))))))
			{
				bVar1 = true;
			}
			if ((!bVar2) && (!bVar1))
			{
				dword_6FBA79AC = 1;
				pDVar4 = CUNIT_GetPlayer();
				bVar5 = 0;
				if (dword_6FBA79B4 != 0)
				{
					bVar5 = 8;
				}
				if (dword_6FBA79B8 != 0)
				{
					bVar5 = 8;
				}
				if (dword_6FBA79BC != 0)
				{
					bVar5 = bVar5 | 4;
				}
				if ((pDVar4 != nullptr) && (pDVar4->dwUnitType == 0))
				{
					dword_6FBA79AC = sub_6FB49920(3, (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam,
					    (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2), bVar5);
				}
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			pSMSGHANDLER_PARAMS->bUseResult = 0;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FAA8E90
void __cdecl sub_6FAA8E90(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;

	dword_6FB75810 = 0x10;
	dword_6FBA79AC = 0;
	byte_6FBA79C8 = 1;
	dword_6FBA79B0 = 0;
	sub_6FAB5D50();
	if (dword_6FBA796C != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if ((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0))
		{
			dword_6FBA79AC = sub_6FB49920(5, (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam,
			    (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2),
			    (uint8_t)(short)pSMSGHANDLER_PARAMS->wParam);
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAA8F20
void __cdecl sub_6FAA8F20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if (dword_6FBA796C != 0)
	{
		dword_6FBA79CC = dword_6FBA79CC + (int)*(short*)((int)&pSMSGHANDLER_PARAMS->wParam + 2);
		if (0x77 < (int)((dword_6FBA79CC ^ (int)dword_6FBA79CC >> 0x1f) - ((int)dword_6FBA79CC >> 0x1f)))
		{
			sub_6FAD4160((int)dword_6FBA79CC / 0x78);
			dword_6FBA79CC = 0;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAA8F90
void __cdecl sub_6FAA8F90(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if (dword_6FBA796C != 0)
	{
		sub_6FAD4020();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
}

//D2Client.0x6FAA8FC0
void __cdecl sub_6FAA8FC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if (dword_6FBA796C != 0)
	{
		sub_6FAD3FE0();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
}

//D2Client.0x6FAA8FF0
void __cdecl sub_6FAA8FF0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short sVar1;

	if (dword_6FBA796C != 0)
	{
		sVar1 = *(short*)((int)&pSMSGHANDLER_PARAMS->wParam + 2);
		if (sVar1 == 1)
		{
			sub_6FAD4060();
		}
		else if (sVar1 == 2)
		{
			sub_6FAD40E0();
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAA9040
void __cdecl sub_6FAA9040(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short sVar1;

	if (dword_6FBA796C != 0)
	{
		sVar1 = *(short*)((int)&pSMSGHANDLER_PARAMS->wParam + 2);
		if (sVar1 == 1)
		{
			sub_6FAD40A0();
		}
		else if (sVar1 == 2)
		{
			sub_6FAD4120();
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAA9090
void __cdecl sub_6FAA9090(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	int iVar2;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->wParam & 0xfff0;
	if ((uVar1 != 0xf130) && (uVar1 != 0xf100))
	{
		if (uVar1 != 0xf010)
		{
			return;
		}
		iVar2 = WINDOW_IsFullScreen();
		if (iVar2 == 0)
		{
			return;
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAA90E0
void __cdecl sub_6FAA90E0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAA9100
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAA9100(int a1)
{
	bool bVar1;
	SHORT SVar2;
	uint32_t extraout_var;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	uint8_t bVar7;

	gbIsAppActive = *(uint32_t*)(a1 + 8);
	if (*(int*)(a1 + 8) != 0)
	{
		sub_6FB23260(0xd, 1, 0);
		dword_6FBA79BC = 0;
		sub_6FAB5D40();
		D2Win_10176(0);
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	bVar1 = sub_6FAD4F00(0x22, 1);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar3 = sub_6FAD4B60(0x22, 1);
		SVar2 = GetAsyncKeyState(uVar3 & 0xffff);
		if (-1 < SVar2)
		{
			dword_6FBA79B4 = 0;
		}
	}
	if (dword_6FB7580C != 0x10)
	{
		dword_6FB7580C = 0x10;
		dword_6FBA79A8 = 0;
		dword_6FBA79C4 = 0;
		dword_6FBA79B0 = 0;
		sub_6FAB5D50();
		if (dword_6FBA796C != 0)
		{
			pDVar4 = CUNIT_GetPlayer();
			if ((pDVar4 != nullptr) && (pDVar4->dwUnitType == 0))
			{
				bVar7 = 0;
				if (dword_6FBA79B4 != 0)
				{
					bVar7 = 8;
				}
				if (dword_6FBA79B8 != 0)
				{
					bVar7 = 8;
				}
				if (dword_6FBA79BC != 0)
				{
					bVar7 = bVar7 | 4;
				}
				iVar5 = sub_6FB57BD0();
				iVar6 = sub_6FB57BC0();
				sub_6FB49920(2, iVar6, iVar5, bVar7);
			}
		}
	}
	if (dword_6FB75810 != 0x10)
	{
		dword_6FB75810 = 0x10;
		dword_6FBA79AC = 0;
		byte_6FBA79C8 = 1;
		dword_6FBA79B0 = 0;
		sub_6FAB5D50();
	}
	*(uint32_t*)(a1 + 0x18) = 0;
}

//D2Client.0x6FAA9230
void __cdecl sub_6FAA9230()
{
	int iVar1;

	if (dword_6FBA796C != 0)
	{
		iVar1 = sub_6FB23800(0, 1);
		if (iVar1 == 0)
		{
			sub_6FACB6E0(0);
			sub_6FB23800(1, 0);
			return;
		}
	}
}

//D2Client.0x6FAA9260
void __cdecl sub_6FAA9260()
{
	D2ActiveRoomStrc* pRoom;
	int nIndex;
	int nTicks;
	int bEclipse;

	if (ghAct != nullptr)
	{
		bEclipse = 1;
		nTicks = 0;
		nIndex = 5;
		pRoom = CUNIT_GetPlayerRoom();
		ENVIRONMENT_InitializeEnvironment(ghAct, pRoom, nIndex, nTicks, bEclipse);
		return;
	}
	byte_6FBA79D0 = '\x01';
}

//D2Client.0x6FAA9290
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAA9290(uint32_t a1, uint32_t a2, uint32_t a3, int a4)
{
	void* pvVar1;
	bool bVar2;
	uint32_t extraout_var;
	D2ActiveRoomStrc* pRoom;
	DWORD DVar3;
	uint32_t extraout_ECX;
	uint8_t nActNo;
	int iVar4;
	int iVar5;
	int bEclipse;
	uint32_t auStack_6c;
	char local_68;
	uint32_t uStack_67;
	char acStack_64[40];
	char acStack_3c[60];

	nActNo = (uint8_t)a1;
	(*(uint32_t*)&local_68) = CONCAT31(uStack_67, nActNo + 1);
	iVar5 = 0;
	do
	{
		bVar2 = DATATBLS_CheckActInLevelTypesTxt(iVar5, (uint8_t)(*(uint32_t*)&local_68));
		if (D2C_ZEXT(bVar2) != 0)
		{
			iVar4 = 0;
			do
			{
				DATATBLS_GetFileNameFromLevelTypeAndFileId(iVar5, iVar4, acStack_3c);
				if ((acStack_3c[0] != '0') && (acStack_3c[0] != '\0'))
				{
					D2CMP_10095((int)auStack_6c, (int)acStack_3c);
				}
				iVar4 = iVar4 + 1;
			} while (iVar4 < 0x20);
		}
		iVar5 = iVar5 + 1;
	} while (iVar5 < 0x24);
	D2CMP_10095((int)auStack_6c, (int)"data\\global\\tiles\\act1\\barracks\\warp.dt1");
	D2CMP_10095((int)auStack_6c, (int)"data\\global\\tiles\\act1\\outdoors\\blank.dt1");
	if (ghAct != nullptr)
	{
		DUNGEON_FreeAct(ghAct);
	}
	ghAct = DUNGEON_AllocAct(nActNo, a2, 1, nullptr, byte_6FBA795C, nullptr,
	    a4, (AUTOMAPFN)(sub_6FACD660), (TOWNAUTOMAPFN)(sub_6FACD840));
	if (((byte_6FBA79D0 != '\0') && (nActNo == 1)) && (ghAct != nullptr))
	{
		bEclipse = 1;
		iVar4 = 0;
		iVar5 = 5;
		pRoom = CUNIT_GetPlayerRoom();
		ENVIRONMENT_InitializeEnvironment(ghAct, pRoom, iVar5, iVar4, bEclipse);
	}
	byte_6FBA79D0 = '\0';
	sub_6FB245B0(a1 & 0xff);
	sub_6FB242E0(1);
	pvVar1 = ptr_6FBA7988;
	*(uint32_t*)ptr_6FBA7988 = 0;
	*(uint32_t*)((int)pvVar1 + 4) = 0;
	*(uint32_t*)ptr_6FBA7988 = a2;
	*(uint32_t*)((int)ptr_6FBA7988 + 4) = a3;
	sub_6FACF730();
	sub_6FAA4A30();
	sub_6FB203C0();
	dword_6FBA798C = a4;
	sub_6FB5CB60();
	sub_6FB5C9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), nActNo));
	sprintf(acStack_64, "Seed: %d", a2);
	FOG_Trace(acStack_64);
	dword_6FB75814 = 1;
	DVar3 = GetTickCount();
	if (dword_6FBA778C < DVar3 + 10000)
	{
		dword_6FBA778C = DVar3 + 10000;
	}
}

//D2Client.0x6FAA9420
void __cdecl sub_6FAA9420(uint32_t a1, uint32_t a2, uint32_t a3)
{
	WINDOW_Destroy();
	D2GFX_Release();
}

//D2Client.0x6FAA9430
void __fastcall sub_6FAA9430(uint32_t a1)
{
	dword_6FBA79D4 = a1;
}

//D2Client.0x6FAA9440
uint32_t __cdecl sub_6FAA9440()
{
	return dword_6FBA79D4;
}

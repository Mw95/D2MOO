#include "Unit/CUnit.h"

#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/PalShift.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Quest/QuestsFX.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/Inv.h"
#include "UI/SkillDesc.h"
#include "UI/SkillsTree.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "Unit/CUnitEvent.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"
#include "Unit/Object.h"
#include "Unit/Player.h"
#include "Unit/PlayerList.h"
#include "Unit/UnitGfx.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB70148
uint32_t dword_6FB70148 = 1;
//D2Client.0x6FB908FC
uint32_t dword_6FB908FC = 1;
//D2Client.0x6FB90900
uint8_t byte_6FB90900[28] = {0, 0, 0, 0, 0xD0, 0x85, 0xB2, 0x6F, 0xE0, 0x85, 0xB2, 0x6F, 0xF0, 0x85, 0xB2, 0x6F, 0x80, 0x86, 0xB2, 0x6F, 0xA0, 0x86, 0xB2, 0x6F, 0x90, 0x86, 0xB2, 0x6F};
//D2Client.0x6FB9091C
int32_t dword_6FB9091C = 7;
//D2Client.0x6FBBAA00
uint32_t dword_6FBBAA00;
//D2Client.0x6FBBAC00
uint32_t dword_6FBBAC00;
//D2Client.0x6FBBAE00
uint32_t dword_6FBBAE00;
//D2Client.0x6FBBB000
uint32_t dword_6FBBB000;
//D2Client.0x6FBBB200
uint32_t dword_6FBBB200;
//D2Client.0x6FBBB400
uint32_t tbl_6FBBB400[128];
//D2Client.0x6FBBB600
uint32_t dword_6FBBB600;
//D2Client.0x6FBBB800
uint32_t dword_6FBBB800;
//D2Client.0x6FBBBA00
uint32_t dword_6FBBBA00;
//D2Client.0x6FBBBC00
uint32_t dword_6FBBBC00;
//D2Client.0x6FBBBE00
uint32_t tbl_6FBBBE00[256];
//D2Client.0x6FBBC200
D2UnitStrc* gpUnit_6FBBC200;
//D2Client.0x6FBBC204
int32_t dword_6FBBC204;

//D2Client.0x6FB269F0
D2UnitStrc* __fastcall sub_6FB269F0(uint32_t a1, int a2)
{
	D2UnitStrc* pDVar1;

	pDVar1 = (D2UnitStrc*)(&dword_6FBBAA00)[(a1 & 0x7f) + a2 * 0x80];
	do
	{
		if (pDVar1 == nullptr)
		{
			return nullptr;
		}
		if (pDVar1->dwUnitId == a1)
		{
			if (pDVar1->dwUnitType == a2)
			{
				return pDVar1;
			}
			FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar1->dwUnitType, a2);
			D2_ASSERT(pDVar1->dwUnitType == a2);
		}
		pDVar1 = pDVar1->pListNext;
	} while (true);
}

//D2Client.0x6FB26A60
D2UnitStrc* __fastcall sub_6FB26A60(uint32_t a1, int a2)
{
	D2UnitStrc* pDVar1;

	pDVar1 = (D2UnitStrc*)(&dword_6FBBB600)[(a1 & 0x7f) + a2 * 0x80];
	do
	{
		if (pDVar1 == nullptr)
		{
			return nullptr;
		}
		if (pDVar1->dwUnitId == a1)
		{
			if (pDVar1->dwUnitType == a2)
			{
				return pDVar1;
			}
			FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar1->dwUnitType, a2);
			D2_ASSERT(pDVar1->dwUnitType == a2);
		}
		pDVar1 = pDVar1->pListNext;
	} while (true);
}

//D2Client.0x6FB26AD0
D2UnitStrc* __fastcall sub_6FB26AD0(int ptUnit)
{
	uint32_t uVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;

	D2_ASSERT(ptUnit);
	if ((*(uint32_t*)(ptUnit + 200) >> 10 & 1) != 0)
	{
		uVar1 = *(uint32_t*)(ptUnit + 0x94);
		if (uVar1 == 3)
		{
			uVar1 = *(uint32_t*)(ptUnit + 0x98);
			for (pDVar3 = (D2UnitStrc*)(&dword_6FBBBC00)[uVar1 & 0x7f]; pDVar3 != nullptr;
			     pDVar3 = pDVar3->pListNext)
			{
				if (pDVar3->dwUnitId == uVar1)
				{
					if (pDVar3->dwUnitType == 3)
					{
						return pDVar3;
					}
					FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar3->dwUnitType, 3);
					if (pDVar3->dwUnitType != 3)
					{
					LAB_6fb26baf:
						FOG_DisplayAssert("ptUnit->eType == eTOU",
						    __FILE__, __LINE__);
						exit(-1);
					}
				}
			}
		}
		else
		{
			uVar2 = *(uint32_t*)(ptUnit + 0x98);
			pDVar3 = (D2UnitStrc*)(&dword_6FBBAA00)[(uVar2 & 0x7f) + uVar1 * 0x80];
			if (pDVar3 != nullptr)
			{
				do
				{
					if (pDVar3->dwUnitId == uVar2)
					{
						if (pDVar3->dwUnitType == uVar1)
						{
							return pDVar3;
						}
						FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar3->dwUnitType, uVar1);
						if (pDVar3->dwUnitType != uVar1)
							goto LAB_6fb26baf;
					}
					pDVar3 = pDVar3->pListNext;
					if (pDVar3 == nullptr)
					{
						return nullptr;
					}
				} while (true);
			}
		}
	}
	return nullptr;
}

//D2Client.0x6FB26BE0
int32_t __fastcall sub_6FB26BE0(uint32_t a1, uint32_t a2)
{
	return sub_6FB26C00((int)(&dword_6FBBAA00 + a2 * 0x80), a1 & 0x7f, a1, a2);
}

//D2Client.0x6FB26C00
int32_t __fastcall sub_6FB26C00(int a1, int a2, uint32_t a3, uint32_t a4)
{
	D2UnitStrc** ppDVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;

	pDVar3 = *(D2UnitStrc**)(a1 + a2 * 4);
	pDVar2 = nullptr;
	if (pDVar3 != nullptr)
	{
		while ((pDVar3->dwUnitId != a3 || (pDVar3->dwUnitType != a4)))
		{
			ppDVar1 = &pDVar3->pListNext;
			pDVar2 = pDVar3;
			pDVar3 = *ppDVar1;
			if (*ppDVar1 == nullptr)
			{
				return 0;
			}
		}
		if (pDVar2 == nullptr)
		{
			*(D2UnitStrc**)(a1 + a2 * 4) = pDVar3->pListNext;
		}
		else
		{
			pDVar2->pListNext = pDVar3->pListNext;
		}
		if (pDVar3->dwUnitType == 4)
		{
			sub_6FAE8F50(pDVar3);
		}
		sub_6FB27ED0(pDVar3);
	}
	return 0;
}

//D2Client.0x6FB26C70
int32_t __fastcall sub_6FB26C70(uint32_t a1, uint32_t a2)
{
	return sub_6FB26C00((int)(&dword_6FBBB600 + a2 * 0x80), a1 & 0x7f, a1, a2);
}

//D2Client.0x6FB26C90
D2ActiveRoomStrc* __fastcall sub_6FB26C90(int a1, int a2)
{
	int iVar1;
	D2ActiveRoomStrc* pDVar2;
	uint32_t uVar3;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar4;
	D2ActiveRoomStrc** ppDStack_20c;
	uint32_t uStack_208;
	D2UnitStrc* local_204;
	char acStack_200[512];

	pDVar4 = gpUnit_6FBBC200;
	pRoom = nullptr;
	local_204 = gpUnit_6FBBC200;
	if ((a1 == 0) && (a2 == 0))
	{
		pDVar2 = nullptr;
	}
	else
	{
		if ((gpUnit_6FBBC200 != nullptr) &&
		    (pRoom = UNITS_GetRoom(gpUnit_6FBBC200), pRoom != nullptr))
		{
			iVar1 = (pRoom->tCoords).nSubtileX;
			if ((((a1 < iVar1) || ((pRoom->tCoords).nSubtileWidth + iVar1 <= a1)) ||
			        (iVar1 = (pRoom->tCoords).nSubtileY, a2 < iVar1)) ||
			    (pDVar2 = pRoom, (pRoom->tCoords).nSubtileHeight + iVar1 <= a2))
			{
				ppDStack_20c = nullptr;
				uStack_208 = 0;
				DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_20c, (int*)&uStack_208);
				uVar3 = 0;
				if (uStack_208 != 0)
				{
					do
					{
						pDVar2 = ppDStack_20c[uVar3];
						if (((pDVar2 != nullptr) &&
						        (iVar1 = (pDVar2->tCoords).nSubtileX, iVar1 <= a1)) &&
						    ((a1 < (pDVar2->tCoords).nSubtileWidth + iVar1 &&
						        ((iVar1 = (pDVar2->tCoords).nSubtileY, iVar1 <= a2 &&
						                                                   (a2 < (pDVar2->tCoords).nSubtileHeight + iVar1))))))
						{
							pDVar2 = ppDStack_20c[uVar3];
							goto LAB_6fb26d5a;
						}
						uVar3 = uVar3 + 1;
						pDVar4 = local_204;
					} while (uVar3 < uStack_208);
				}
			}
			else
			{
			LAB_6fb26d5a:
				pDVar4 = local_204;
				if (pDVar2 != nullptr)
				{
					return pDVar2;
				}
			}
		}
		pDVar2 = DUNGEON_FindRoomBySubtileCoordinates(ghAct, a1, a2);
		if (pDVar2 == nullptr)
		{
			SStrPrintf(acStack_200, 0x200, "Unable to find room for unit...  hControlUnit:%8x  hUnitRoom:%8x  ghAct:%8x  nX:%d  nY:%d", pDVar4, pRoom,
			    ghAct, a1, a2);
			FOG_DisplayWarning(acStack_200, __FILE__, __LINE__);
			FOG_DisplayAssert("hFindRoom", __FILE__, __LINE__);
			exit(-1);
		}
	}
	return pDVar2;
}

//D2Client.0x6FB26DD0
void __fastcall sub_6FB26DD0(D2UnitStrc* pUnit, char* a2, char* a3, int a4)
{
	uint32_t uVar1;
	uint8_t bVar2;
	D2ActiveRoomStrc* pDVar3;
	D2ActiveRoomStrc* pRoom;
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar4;
	int iVar5;
	D2LevelsTxt* pDVar6;
	D2LevelsTxt* pDVar7;
	D2CoordStrc local_10;
	D2DynamicPathStrc* local_8;
	D2UnitStrc* local_4;

	local_4 = gpUnit_6FBBC200;
	local_10.nX = (int)a2;
	if (pUnit == gpUnit_6FBBC200)
	{
		sub_6FAB5D40();
	}
	pDVar3 = sub_6FB26C90((int)a2, (int)a3);
	local_8 = pUnit->pDynamicPath;
	D2_ASSERT(local_8 != nullptr);
	if (((a2 != nullptr) && (a3 != nullptr)) && (pDVar3 == nullptr))
	{
		FOG_DisplayAssert("Tried to warp to a room we didn't know about",
		    __FILE__, __LINE__);
		exit(-1);
	}
	if ((pUnit->dwFlags & 0x10000) == 0)
	{
		uVar1 = pUnit->dwAnimMode;
		if (pUnit->dwUnitType == 0)
		{
			if (uVar1 == 0)
			{
				return;
			}
			if (uVar1 == 0x11)
			{
				return;
			}
		}
		else if (pUnit->dwUnitType == 1)
		{
			if (uVar1 == 0)
			{
				return;
			}
			if (uVar1 == 0xc)
			{
				return;
			}
		}
		if (pUnit == local_4)
		{
			pRoom = UNITS_GetRoom(pUnit);
			if (pRoom != nullptr)
			{
				pSkill = UNITS_GetUsedSkill(pUnit);
				if (((pSkill == nullptr) ||
				        (pDVar4 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill), pDVar4 == nullptr)) ||
				    (((uint8_t)((uint8_t*)&gdwBitMasks)[0x18] & (uint8_t)pDVar4->dwFlags[1]) == 0))
				{
					if (a4 != 0)
					{
						D2_ASSERT(!pUnit->dwUnitType);
						sub_6FAA61F0();
					}
				}
				else
				{
					a4 = 0;
				}
			}
			if (pDVar3 != nullptr)
			{
				DUNGEON_UpdatePops(pDVar3, (int)a2, (int)a3, (uint32_t)(pRoom != pDVar3));
				iVar5 = DUNGEON_GetLevelIdFromRoom(pDVar3);
				bVar2 = DATATBLS_GetNoPerFromLevelsTxt(iVar5);
				D2GFX_SetUnitPerspective((uint32_t)(bVar2 == 0));
				a2 = (char*)local_10.nX;
				if (pRoom != nullptr)
				{
					iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom);
					pDVar6 = DATATBLS_GetLevelsTxtRecord(iVar5);
					iVar5 = DUNGEON_GetLevelIdFromRoom(pDVar3);
					pDVar7 = DATATBLS_GetLevelsTxtRecord(iVar5);
					a2 = (char*)local_10.nX;
					if (pDVar6->nPal != pDVar7->nPal)
					{
						D2Win_10177(pDVar7->nPal);
						D2CMP_10097((uint32_t)pDVar7->nPal);
						a2 = (char*)local_10.nX;
					}
				}
			}
		}
		iVar5 = D2Common_10229(local_8, pUnit, pDVar3, (uint32_t)a2, (uint32_t)a3);
		if (iVar5 == 0)
		{
			local_10.nY = (int)a3;
			local_10.nX = (int)a2;
			iVar5 = UNITS_GetUnitSizeX(pUnit);
			COLLISION_GetFreeCoordinates(pDVar3, &local_10, iVar5, 0x1c09, 1);
			iVar5 = D2Common_10231(local_8, pUnit, pDVar3, (uint16_t)local_10.nX, (uint16_t)local_10.nY);
			D2_ASSERT(iVar5);
		}
		sub_6FACD650();
		if (pUnit == local_4)
		{
			sub_6FAA7490(a4);
		}
		if (pUnit->dwUnitType == 0)
		{
			uVar1 = pUnit->dwAnimMode;
			pDVar3 = UNITS_GetRoom(pUnit);
			if ((pDVar3 != nullptr) && ((uVar1 == 1 || (uVar1 == 5))))
			{
				sub_6FB49090(7, pUnit, 0, 1);
			}
		}
	}
}

//D2Client.0x6FB27040
D2UnitStrc* __fastcall sub_6FB27040(uint32_t a1, uint32_t a2, float a3, int a4, uint32_t a5, int a6)
{
	D2UnitStrc* pDVar1;

	pDVar1 = UNITS_AllocUnit(nullptr, a5);
	if (pDVar1 == nullptr)
	{
		return nullptr;
	}
	pDVar1 = sub_6FB27080(pDVar1, a1, a2, a3, a4, a5, a6, 0);
	return pDVar1;
}

//D2Client.0x6FB27080
D2UnitStrc* __fastcall sub_6FB27080(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, float a4, int a5, uint32_t a6, int a7, uint32_t a8)
{
	uint64_t DVar1;
	uint8_t bVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	D2ActiveRoomStrc* pRoom;

	iVar3 = sub_6FAAC080();
	pRoom = nullptr;
	if (pUnit != nullptr)
	{
		if (iVar3 == 0)
		{
			uVar4 = pUnit->dwFlagEx & 0xfdffffff;
		}
		else
		{
			uVar4 = pUnit->dwFlagEx | 0x2000000;
		}
		pUnit->dwFlagEx = uVar4;
	}
	pUnit->dwUnitId = a2;
	pUnit->dwUnitType = a6;
	pUnit->dwClassId = a3;
	pUnit->dwTickCount = 0;
	pUnit->pMemoryPool = nullptr;
	if ((a4 != 0.0) || (a5 != 0))
	{
		pRoom = sub_6FB26C90((int)a4, a5);
		iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom);
		bVar2 = DRLG_GetActNoFromLevelId(iVar3);
		pUnit->nAct = bVar2;
		pUnit->pDrlgAct = ghAct;
	}
	SEED_InitSeed(&pUnit->pSeed);
	if (a6 == 4)
	{
		ITEMS_AllocItemData(nullptr, pUnit);
		ITEMS_InitItemSeed(pUnit);
	}
	if (pRoom != nullptr)
	{
		DVar1 = (uint64_t)((uint64_t)(pRoom->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pRoom->pSeed).nHighSeed);
		uVar4 = (*(uint32_t*)((uint8_t*)&DVar1 + 0));
		(*(uint64_t*)&pRoom->pSeed) = DVar1;
		pUnit->dwInitSeed = uVar4;
		SEED_InitLowSeed(&pUnit->pSeed, uVar4);
	}
	switch (a6)
	{
	case 0:
		sub_6FB488A0(pUnit, pRoom, a4, a5);
		break;
	case 1:
		FOG_DisplayAssert("eTOU != UNIT_MONSTER", __FILE__, __LINE__);
		exit(-1);
	case 2:
		UNITS_AllocStaticPath(pUnit);
		sub_6FB469D0(pUnit, pRoom, a4, a5, a3, a8);
		break;
	case 3:
		sub_6FB39750(pUnit, pRoom, a4, a5, a3);
		break;
	case 4:
		UNITS_AllocStaticPath(pUnit);
		sub_6FB2A8E0(pUnit, pRoom, a4, a5, a7, 1);
		break;
	case 5:
		UNITS_AllocStaticPath(pUnit);
		pUnit->dwFlags = pUnit->dwFlags | 0x22;
		UNITS_InitializeStaticPath(pUnit, pRoom, (int)a4, a5);
		UNITS_BlockCollisionPath(pUnit, pRoom, (int)a4, a5);
		UNITROOM_AddUnitToRoom(pUnit, pRoom);
		goto LAB_6fb2723d;
	}
	sub_6FB4DAC0(pUnit);
	if ((a6 == 0) || (a6 == 1))
	{
		UNITS_UpdateAnimRateAndVelocity(pUnit, __FILE__, __LINE__);
	}
LAB_6fb2723d:
	pDVar5 = sub_6FB27280(pUnit);
	if ((pDVar5 != nullptr) && (a6 == 2))
	{
		sub_6FB46BA0(pDVar5);
	}
	return pDVar5;
}

//D2Client.0x6FB27280
D2UnitStrc* __fastcall sub_6FB27280(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t* puVar4;

	iVar2 = sub_6FB27390(pUnit);
	if (iVar2 == 0)
	{
		pDVar3 = sub_6FB27320((int)(&dword_6FBBAA00 + pUnit->dwUnitType * 0x80), pUnit->dwUnitId & 0x7f, pUnit->dwUnitId, pUnit->dwUnitType);
		D2_ASSERT(pDVar3 != pUnit);
		if (pDVar3 != nullptr)
		{
			uVar1 = pDVar3->dwUnitType;
			if ((pDVar3->dwFlags >> 0x15 & 1) == 0)
			{
				puVar4 = &dword_6FBBAA00 + uVar1 * 0x80;
			}
			else
			{
				puVar4 = &dword_6FBBB600 + uVar1 * 0x80;
			}
			sub_6FB26C00((int)puVar4, pDVar3->dwUnitId & 0x7f, pDVar3->dwUnitId, uVar1);
			iVar2 = sub_6FB27390(pUnit);
			if (iVar2 != 0)
			{
				return pUnit;
			}
		}
		sub_6FB27ED0(pUnit);
		pUnit = nullptr;
	}
	return pUnit;
}

//D2Client.0x6FB27320
D2UnitStrc* __fastcall sub_6FB27320(int a1, int a2, int a3, int a4)
{
	D2UnitStrc* pDVar1;

	pDVar1 = *(D2UnitStrc**)(a1 + a2 * 4);
	do
	{
		if (pDVar1 == nullptr)
		{
			return nullptr;
		}
		if (pDVar1->dwUnitId == a3)
		{
			if (pDVar1->dwUnitType == a4)
			{
				return pDVar1;
			}
			FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar1->dwUnitType, a4);
			D2_ASSERT(pDVar1->dwUnitType == a4);
		}
		pDVar1 = pDVar1->pListNext;
	} while (true);
}

//D2Client.0x6FB27390
uint32_t __fastcall sub_6FB27390(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint32_t* puVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t* puVar6;
	uint32_t uVar7;

	if ((pUnit == nullptr) || ((pUnit->dwFlags >> 0x15 & 1) != 1))
	{
		uVar7 = pUnit->dwUnitType;
		uVar1 = pUnit->dwUnitId;
		for (puVar2 = (uint32_t*)(&dword_6FBBAA00)[(uVar1 & 0x7f) + uVar7 * 0x80]; puVar2 != nullptr;
		     puVar2 = (uint32_t*)puVar2[0x39])
		{
			if (puVar2[3] == uVar1)
			{
				if (*puVar2 == uVar7)
				{
					return 0;
				}
				FOG_Trace("current unit is %d, table is supposed to be %d\n", *puVar2, uVar7);
				D2_ASSERT(*puVar2 == uVar7);
			}
		}
		uVar7 = pUnit->dwUnitType;
		uVar1 = pUnit->dwUnitId;
		for (puVar2 = (uint32_t*)(&dword_6FBBAA00)[(uVar1 & 0x7f) + uVar7 * 0x80]; puVar2 != nullptr;
		     puVar2 = (uint32_t*)puVar2[0x39])
		{
			if (puVar2[3] == uVar1)
			{
				D2_ASSERT(*puVar2 != uVar7);
				FOG_Trace("current unit is %d, table is supposed to be %d\n", *puVar2, uVar7);
				D2_ASSERT(*puVar2 == uVar7);
			}
		}
	}
	else
	{
		pDVar5 = sub_6FB27320((int)(&dword_6FBBB600 + pUnit->dwUnitType * 0x80), pUnit->dwUnitId & 0x7f, pUnit->dwUnitId, pUnit->dwUnitType);
		if (pDVar5 != nullptr)
		{
			return 0;
		}
		pDVar5 = sub_6FB27320((int)(&dword_6FBBB600 + pUnit->dwUnitType * 0x80), pUnit->dwUnitId & 0x7f, pUnit->dwUnitId, pUnit->dwUnitType);
		D2_ASSERT(pDVar5 == nullptr);
	}
	sub_6FB51F00(pUnit, 1);
	uVar7 = pUnit->dwUnitId & 0x7f;
	if ((pUnit->dwFlags >> 0x15 & 1) == 1)
	{
		puVar6 = &dword_6FBBB600 + pUnit->dwUnitType * 0x80;
	}
	else
	{
		puVar6 = &dword_6FBBAA00 + pUnit->dwUnitType * 0x80;
	}
	pDVar4 = (D2UnitStrc*)puVar6[uVar7];
	pDVar5 = nullptr;
	while ((pDVar3 = pDVar4, pDVar3 != nullptr && (pUnit->dwUnitId < pDVar3->dwUnitId)))
	{
		pDVar5 = pDVar3;
		pDVar4 = pDVar3->pListNext;
	}
	pUnit->pListNext = pDVar3;
	if (pDVar5 != nullptr)
	{
		pDVar5->pListNext = pUnit;
		return 1;
	}
	puVar6[uVar7] = (uint32_t)(pUnit);
	return 1;
}

//D2Client.0x6FB27570
uint32_t* __fastcall sub_6FB27570(uint32_t a1, uint32_t a2, float a3, int a4, char* a5)
{
	D2UnitStrc* pDVar1;

	pDVar1 = UNITS_AllocUnit(nullptr, 0);
	if (pDVar1 == nullptr)
	{
		return nullptr;
	}
	pDVar1 = sub_6FB27080(pDVar1, a1, a2, a3, a4, 0, 0, 0);
	if (pDVar1 != nullptr)
	{
		UNITS_SetNameInPlayerData(pDVar1, a5);
	}
	return &pDVar1->dwUnitType;
}

//D2Client.0x6FB275C0
uint32_t* __fastcall sub_6FB275C0(uint32_t a1, uint32_t a2, float a3, int a4, uint32_t a5, int a6, uint32_t a7, uint32_t a8)
{
	D2UnitStrc* pDVar1;
	int iVar2;

	pDVar1 = UNITS_AllocUnit(nullptr, a5);
	if (pDVar1 == nullptr)
	{
		return nullptr;
	}
	pDVar1 = sub_6FB27080(pDVar1, a1, a2, a3, a4, a5, a6, a7);
	if (pDVar1 != nullptr)
	{
		pDVar1->pPlayerData->szName[4] = (char)a8;
		iVar2 = UNITS_IsShrine(pDVar1);
		if (iVar2 != 0)
		{
			sub_6FB475D0(pDVar1);
		}
	}
	return &pDVar1->dwUnitType;
}

//D2Client.0x6FB27630
// TODO: decompilation needs review (extraout)
D2UnitStrc* __fastcall sub_6FB27630(void* a1, uint32_t* a2, int a3, uint32_t a4, uint32_t a5, int a6)
{
	int iVar1;
	D2PlayerDataStrc* pDVar2;
	int64_t lVar3;
	uint64_t DVar4;
	bool bVar5;
	uint8_t bVar6;
	short sVar7;
	uint32_t uVar8;
	int iVar9;
	int iVar10;
	D2UnitStrc* pDVar11;
	D2ActiveRoomStrc* pDVar12;
	uint32_t extraout_var;
	Unicode* wszName;
	uint8_t* puVar13;
	uint32_t extraout_var_00;
	int iVar14;
	uint32_t extraout_var_01;
	D2SuperUniquesTxt* pDVar15;
	D2UnitStrc* pDVar16;
	uint32_t* puVar17;
	int iVar18;
	int iVar19;
	int iVar20;
	uint32_t uVar21;
	uint16_t auStack_10[2];
	uint32_t uStack_c;

	uVar21 = *(uint32_t*)(a1);
	uVar8 = sub_6FAB1920((int)gpUnit_6FBBC200, 7, 1);
	if (uVar21 == uVar8)
	{
		for (pDVar11 = (D2UnitStrc*)(&dword_6FBBAC00)[uVar21 & 0x7f]; pDVar11 != nullptr;
		     pDVar11 = pDVar11->pListNext)
		{
			if (pDVar11->dwUnitId == uVar21)
			{
				if (pDVar11->dwUnitType == 1)
				{
					if (pDVar11 != nullptr)
					{
						sub_6FB59320((int)pDVar11);
						sub_6FB4DAC0(pDVar11);
						UNITS_ChangeAnimMode(pDVar11, *(int*)((int)a1 + 0x18));
						return pDVar11;
					}
					break;
				}
				FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar11->dwUnitType, 1);
				D2_ASSERT(pDVar11->dwUnitType == 1);
			}
		}
	}
	iVar14 = *(int*)((int)a1 + 4);
	if ((iVar14 < 0) || (iVar20 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar20 + 0xa80) <= iVar14))
	{
		return nullptr;
	}
	iVar9 = iVar14 * 0x1a8;
	iVar18 = *(int*)(iVar20 + 0xa78) + iVar9;
	iVar10 = (int)*(short*)(iVar18 + 0x18);
	if (iVar10 < 0)
	{
		return nullptr;
	}
	if (*(int*)(iVar20 + 0xa98) <= iVar10)
	{
		return nullptr;
	}
	iVar20 = *(int*)(iVar20 + 0xa90) + iVar10 * 0x134;
	if (iVar20 == 0)
	{
		return nullptr;
	}
	if (iVar18 == 0)
	{
		return nullptr;
	}
	pDVar11 = UNITS_AllocUnit(nullptr, 1);
	if ((a6 != 0) && (pDVar11 != nullptr))
	{
		pDVar11->dwFlags = pDVar11->dwFlags | 0x600000;
	}
	iVar10 = *(int*)((int)a1 + 8);
	iVar1 = *(int*)((int)a1 + 0xc);
	pDVar11->dwUnitType = 1;
	pDVar11->dwClassId = *(int*)((int)a1 + 4);
	pDVar11->dwUnitId = *(uint32_t*)(a1);
	pDVar11->pMemoryPool = nullptr;
	pDVar11->dwTickCount = 0;
	pDVar12 = sub_6FB26C90(iVar10, iVar1);
	SEED_InitSeed(&pDVar11->pSeed);
	if (pDVar12 != nullptr)
	{
		lVar3 = (uint64_t)(pDVar12->pSeed).nLowSeed * 0x6ac690c5;
		uStack_c = (uint32_t)((uint64_t)lVar3 >> 0x20);
		DVar4 = (uint64_t)(lVar3 + (uint64_t)(pDVar12->pSeed).nHighSeed);
		(*(uint64_t*)&pDVar12->pSeed) = DVar4;
		pDVar11->dwInitSeed = (*(uint32_t*)((uint8_t*)&DVar4 + 0));
	}
	SEED_InitLowSeed(&pDVar11->pSeed, pDVar11->dwInitSeed);
	sub_6FB40A80((int*)pDVar11, 0);
	sub_6FB44A00((int*)pDVar11, *(uint16_t*)((int)a1 + 0x10), 1);
	bVar5 = sub_6FB449D0((int*)pDVar11, 2);
	if (D2C_ZEXT(bVar5) != 0)
	{
		sub_6FB44990((int*)pDVar11, (uint16_t)a5);
	}
	sub_6FB40B10((int*)pDVar11, *(uint32_t*)((int)a1 + 0x14));
	wszName = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar18 + 6)));
	MONSTERS_SetMonsterNameInMonsterData(pDVar11, wszName);
	if (a3 != 0)
	{
		sub_6FB44970((int*)pDVar11, (uint16_t)a4);
		puVar13 = (uint8_t*)sub_6FB44950((int*)pDVar11);
		iVar19 = 9;
		do
		{
			*puVar13 = *(uint8_t*)a3;
			puVar13 = puVar13 + 1;
			a3 = a3 + 1;
			iVar19 = iVar19 + -1;
		} while (iVar19 != 0);
	}
	if ((((a2 != nullptr) && (pDVar11->dwUnitType == 1)) &&
	        (pDVar2 = pDVar11->pPlayerData, pDVar2 != nullptr)) &&
	    (pDVar2->szName + 4 != nullptr))
	{
		*(uint32_t*)(pDVar2->szName + 4) = *a2;
		*(uint32_t*)(pDVar2->szName + 8) = a2[1];
		*(uint32_t*)(pDVar2->szName + 0xc) = a2[2];
		pDVar2->pQuestData[0] = (D2BitBufferStrc*)a2[3];
	}
	sub_6FB40D60(pDVar11, pDVar12, iVar10, iVar1, iVar14, *(uint32_t*)((int)a1 + 0x18));
	PATH_SetStepNum(pDVar11->pDynamicPath, *(uint8_t*)(iVar20 + 0xe));
	sub_6FB4DAC0(pDVar11);
	if (iVar14 < 0x158)
	{
		if (iVar14 == 0x157)
		{
			sub_6FB5FB10((int)pDVar11);
			sub_6FB5FC80((int)pDVar11, 0x20, -0x20, 0);
			goto switchD_6fb278f3_caseD_f3;
		}
		switch (iVar14)
		{
		case 0xf2:
			iVar20 = 0x7a;
			goto LAB_6fb27a0c;
		case 0x14d:
			uVar21 = 0;
			uVar8 = 2;
			iVar20 = 0xba;
			goto LAB_6fb27a18;
		case 0x154:
			sub_6FB5FB10((int)pDVar11);
			sub_6FB5FC80((int)pDVar11, -0x20, -0x20, 0);
			break;
		case 0x155:
			sub_6FB5FB10((int)pDVar11);
			sub_6FB5FC80((int)pDVar11, -0x20, 0x20, 0);
			break;
		case 0x156:
			sub_6FB5FB10((int)pDVar11);
			sub_6FB5FC80((int)pDVar11, 0x20, 0x20, 0);
		}
		goto switchD_6fb278f3_caseD_f3;
	}
	switch (iVar14)
	{
	case 0x15f:
	case 0x160:
	case 0x161:
		iVar20 = pDVar11->dwClassId + -0xb3;
		uVar21 = pDVar11->dwClassId - 0xb0;
		uVar8 = 4;
		break;
	default:
		goto switchD_6fb278f3_caseD_f3;
	case 0x196:
		sub_6FB5FB10((int)pDVar11);
		sub_6FB5FC80((int)pDVar11, 0, 0, -0x37);
		sub_6FB5FCB0((int)pDVar11, 0, 0, 1, 1);
		sub_6FB5FD50((int)pDVar11, 0, 0, 0x32, 0);
		sub_6FB60180((int)pDVar11, 1);
		goto switchD_6fb278f3_caseD_f3;
	case 0x1a1:
	case 0x1a2:
		uVar21 = 0;
		uVar8 = 2;
		iVar20 = 0x10e;
		break;
	case 0x209:
		sub_6FAB9F10(pDVar11);
		goto switchD_6fb278f3_caseD_f3;
	case 0x21f:
		iVar20 = 0x113;
	LAB_6fb27a0c:
		uVar21 = 0;
		uVar8 = 3;
	}
LAB_6fb27a18:
	sub_6FB5BA70(pDVar11, iVar20, uVar8, 0, uVar21, 0, 0, 0);
switchD_6fb278f3_caseD_f3:
	uVar21 = 2;
	if (*(uint8_t*)(iVar18 + 0x4d) < 8)
	{
		uVar21 = *(uint8_t*)(iVar18 + 0x4d) + 2;
	}
	bVar5 = sub_6FB40D00((int*)pDVar11);
	if ((D2C_ZEXT(bVar5) != 0) &&
	    (((iVar20 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar20 + 0xa80) <= iVar14 ||
	                                                        (iVar10 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar9), iVar10 < 0)) ||
	        ((*(int*)(iVar20 + 0xa98) <= iVar10 ||
	            ((iVar20 = *(int*)(iVar20 + 0xa90) + iVar10 * 0x134, iVar20 == 0 ||
	                                                                     (((uint32_t) * (uint8_t*)(iVar20 + 5) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x1c)) == 0))))))))
	{
		uVar21 = sub_6FAAE510((int)pDVar11);
	}
	iVar20 = *(int*)((uint8_t*)&sgptDataTables);
	if ((((iVar14 < *(int*)(iVar20 + 0xa80)) &&
	         (iVar14 = (int)*(short*)(*(int*)(iVar20 + 0xa78) + 0x18 + iVar9), -1 < iVar14)) &&
	        (iVar14 < *(int*)(iVar20 + 0xa98))) &&
	    ((iVar14 = *(int*)(iVar20 + 0xa90) + iVar14 * 0x134, iVar14 != 0 &&
	                                                             (bVar6 = sub_6FAAC090(), *(char*)(bVar6 + 0x122 + iVar14) != '\0'))))
	{
		bVar6 = sub_6FAAC090();
		uVar21 = (uint32_t) * (uint8_t*)(bVar6 + 0x122 + iVar14);
		if (uVar21 == 0xff)
		{
			uVar21 = sub_6FAB1B40((int)pDVar11);
			uVar21 = (uint32_t)(uVar21 == 0);
		}
	}
	bVar5 = sub_6FB449D0((int*)pDVar11, 2);
	if (D2C_ZEXT(bVar5) != 0)
	{
		sVar7 = sub_6FB449B0((int*)pDVar11);
		pDVar15 = DATATBLS_GetSuperUniquesTxtRecord((int)sVar7);
		bVar6 = sub_6FAAC090();
		if (pDVar15->nUtrans[bVar6] != 0)
		{
			bVar6 = sub_6FAAC090();
			uVar21 = (uint32_t)pDVar15->nUtrans[bVar6];
		}
	}
	if (0x1d < (int)uVar21)
	{
		uVar21 = 2;
	}
	sub_6FB5BFC0((int)pDVar11->pGfxData, uVar21);
	sub_6FB5C020((int)pDVar11->pGfxData, uVar21);
	pDVar16 = sub_6FB27280(pDVar11);
	iVar14 = sub_6FAB1B20(pDVar16->dwUnitId);
	if ((iVar14 == 7) &&
	    (puVar17 = (uint32_t*)sub_6FAB18D0(pDVar16->dwUnitId), puVar17 != nullptr))
	{
		uStack_c = *puVar17;
		auStack_10[0] = *(uint16_t*)(puVar17 + 1);
		sub_6FB446B0(pDVar11, auStack_10);
	}
	iVar14 = MONSTERS_GetHirelingTypeId(pDVar11);
	if (iVar14 != 0)
	{
		INVENTORY_AllocInventory(nullptr, pDVar11);
	}
	sub_6FB52190(pDVar11);
	return pDVar11;
}

//D2Client.0x6FB27D50
D2UnitStrc* __fastcall sub_6FB27D50(uint32_t a1, float a2, int a3, uint32_t a4, int a5)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_1c[2];
	float local_14;
	int local_10;
	uint32_t local_4;

	dword_6FB908FC = dword_6FB908FC + 1;
	if (dword_6FB908FC == 0xffffffff)
	{
		dword_6FB908FC = 0;
	}
	if (a4 == 1)
	{
		puVar3 = local_1c;
		for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_10 = a3;
		local_4 = 1;
		local_1c[0] = dword_6FB908FC;
		local_1c[1] = a1;
		local_14 = a2;
		pDVar1 = sub_6FB27630(local_1c, 0, 0, 0, 0, 1);
		return pDVar1;
	}
	pDVar1 = UNITS_AllocUnit(nullptr, a4);
	if (pDVar1 == nullptr)
	{
		return nullptr;
	}
	pDVar1->dwFlags = pDVar1->dwFlags | 0x600000;
	pDVar1 = sub_6FB27080(pDVar1, dword_6FB908FC, a1, a2, a3, a4, a5, 0);
	return pDVar1;
}

//D2Client.0x6FB27E10
void __fastcall sub_6FB27E10(D2UnitStrc* pUnit, char a2, char a3)
{
	D2ActiveRoomStrc* pRoom;

	if (((pUnit != nullptr) && (pUnit->dwUnitType == 1)) && (a2 != a3))
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			if (a3 == '\x02')
			{
				DUNGEON_IncreaseAlliedCountOfRoom(pRoom);
				D2Common_10214(pUnit);
				return;
			}
			if (a2 == '\x02')
			{
				DUNGEON_DecreaseAlliedCountOfRoom(pRoom);
			}
			D2Common_10214(pUnit);
		}
	}
}

//D2Client.0x6FB27E70
void __fastcall sub_6FB27E70(D2ActiveRoomStrc* pActiveRoom)
{
	D2PresetUnitStrc* pDVar1;
	D2DrlgCoordsStrc DStack_20;

	for (pDVar1 = DUNGEON_GetPresetUnitsFromRoom(pActiveRoom); pDVar1 != nullptr;
	     pDVar1 = pDVar1->pNext)
	{
		if ((pDVar1->bSpawned & 1) != 0)
		{
			DUNGEON_GetRoomCoordinates(pActiveRoom, &DStack_20);
			sub_6FB27D50(pDVar1->nIndex, (float)(pDVar1->nXpos + DStack_20.nSubtileX),
			    pDVar1->nYpos + DStack_20.nSubtileY, pDVar1->nUnitType, pDVar1->nMode);
		}
	}
}

//D2Client.0x6FB27ED0
void __fastcall sub_6FB27ED0(D2UnitStrc* pUnit)
{
	void* pvVar1;

	if (pUnit->dwInteractGUID != 0)
	{
		sub_6FAA44D0(pUnit->dwInteractGUID);
		pUnit->dwInteractGUID = 0;
	}
	pvVar1 = D2Common_10958(pUnit, nullptr);
	if (pvVar1 != nullptr)
	{
		sub_6FAA44D0((int)pvVar1);
	}
	sub_6FB5FB70((int)pUnit);
	sub_6FB4FA40((int)pUnit, 0);
	sub_6FB51F00(pUnit, -1);
	switch (pUnit->dwUnitType)
	{
	case 0:
		if (pUnit->pHoverText != nullptr)
		{
			sub_6FB1E0B0(pUnit->pHoverText);
			pUnit->pHoverText = nullptr;
		}
		sub_6FB48A60(pUnit);
		sub_6FB4FA40((int)pUnit, 1);
		break;
	case 1:
		if (pUnit->pHoverText != nullptr)
		{
			sub_6FB1E0B0(pUnit->pHoverText);
			pUnit->pHoverText = nullptr;
		}
		sub_6FB41860(pUnit);
		sub_6FB4FA40((int)pUnit, 1);
		break;
	case 2:
		if (pUnit->pHoverText != nullptr)
		{
			sub_6FB1E0B0(pUnit->pHoverText);
			pUnit->pHoverText = nullptr;
		}
		sub_6FB46D10(pUnit);
		UNITS_FreeStaticPath(pUnit);
		sub_6FB4FA40((int)pUnit, 1);
		break;
	case 3:
		sub_6FB39830(pUnit);
		break;
	case 4:
		sub_6FB2ABD0(pUnit);
		ITEMS_FreeItemData(nullptr, pUnit);
		goto LAB_6fb27fd0;
	case 5:
		if (ghAct != nullptr)
		{
			UNITROOM_RemoveUnitFromRoom(pUnit);
		}
	LAB_6fb27fd0:
		UNITS_FreeStaticPath(pUnit);
	}
	sub_6FB2A700((int)pUnit);
	sub_6FAB55C0((int)pUnit);
	if (pUnit == gpUnit_6FBBC200)
	{
		if (gpUnit_6FBBC200 != nullptr)
		{
			sub_6FB23960();
		}
		gpUnit_6FBBC200 = nullptr;
	}
	UNITS_FreeUnit(pUnit);
}

//D2Client.0x6FB28020
void __cdecl sub_6FB28020()
{
	int iVar1;
	uint32_t* puVar2;

	puVar2 = &dword_6FBBAA00;
	for (iVar1 = 0x300; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	puVar2 = &dword_6FBBB600;
	for (iVar1 = 0x300; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
}

//D2Client.0x6FB28040
void __cdecl sub_6FB28040()
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int* piVar4;
	int iVar5;

	piVar4 = (int*)(&dword_6FB70148);
	do
	{
		iVar5 = 0;
		iVar3 = *piVar4 << 7;
		do
		{
			pDVar2 = (D2UnitStrc*)(&dword_6FBBAA00)[iVar3 + iVar5];
			while (pDVar2 != nullptr)
			{
				pDVar1 = pDVar2->pListNext;
				sub_6FB27ED0(pDVar2);
				iVar3 = *piVar4 * 0x80;
				(&dword_6FBBAA00)[iVar3 + iVar5] = (uint32_t)(pDVar1);
				pDVar2 = pDVar1;
			}
			iVar5 = iVar5 + 1;
		} while (iVar5 < 0x80);
		piVar4 = piVar4 + 1;
	} while ((int)piVar4 < (int)&byte_6FB70160);
	piVar4 = (int*)(&dword_6FB70148);
	do
	{
		iVar5 = 0;
		iVar3 = *piVar4 << 7;
		do
		{
			pDVar2 = (D2UnitStrc*)(&dword_6FBBB600)[iVar3 + iVar5];
			while (pDVar2 != nullptr)
			{
				pDVar1 = pDVar2->pListNext;
				sub_6FB27ED0(pDVar2);
				iVar3 = *piVar4 * 0x80;
				(&dword_6FBBB600)[iVar3 + iVar5] = (uint32_t)(pDVar1);
				pDVar2 = pDVar1;
			}
			iVar5 = iVar5 + 1;
		} while (iVar5 < 0x80);
		piVar4 = piVar4 + 1;
	} while ((int)piVar4 < (int)&byte_6FB70160);
}

//D2Client.0x6FB280F0
void __cdecl sub_6FB280F0()
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t* puVar6;

	puVar6 = &dword_6FBBB000;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			sub_6FB4E6A0(pDVar4);
			pDVar4 = pDVar1;
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBB200);
	puVar6 = &dword_6FBBBC00;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			uVar2 = pDVar4->dwUnitId;
			uVar3 = pDVar4->dwUnitType;
			sub_6FB4E6A0(pDVar4);
			pDVar5 = sub_6FB26A60(uVar2, uVar3);
			pDVar4 = pDVar1;
			if (pDVar5 != nullptr)
			{
				if (pDVar5->dwUnitType == 1)
				{
					sub_6FB3F350(pDVar5);
				}
				else if (pDVar5->dwUnitType == 2)
				{
					sub_6FB48430(pDVar5);
				}
			}
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&tbl_6FBBBE00);
	puVar6 = &dword_6FBBBA00;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			uVar2 = pDVar4->dwUnitId;
			uVar3 = pDVar4->dwUnitType;
			sub_6FB4E6A0(pDVar4);
			pDVar5 = sub_6FB26A60(uVar2, uVar3);
			pDVar4 = pDVar1;
			if (pDVar5 != nullptr)
			{
				if (pDVar5->dwUnitType == 1)
				{
					sub_6FB3F350(pDVar5);
				}
				else if (pDVar5->dwUnitType == 2)
				{
					sub_6FB48430(pDVar5);
				}
			}
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBBC00);
	puVar6 = &dword_6FBBAA00;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			sub_6FB4E6A0(pDVar4);
			pDVar4 = pDVar1;
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBAC00);
	puVar6 = &dword_6FBBAC00;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			sub_6FB4E6A0(pDVar4);
			pDVar4 = pDVar1;
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBAE00);
	puVar6 = &dword_6FBBAE00;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			sub_6FB4E6A0(pDVar4);
			pDVar4 = pDVar1;
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBB000);
	puVar6 = &dword_6FBBB200;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			sub_6FB4E6A0(pDVar4);
			pDVar4 = pDVar1;
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&tbl_6FBBB400);
	puVar6 = &dword_6FBBB800;
	do
	{
		pDVar4 = (D2UnitStrc*)*puVar6;
		while (pDVar4 != nullptr)
		{
			pDVar1 = pDVar4->pListNext;
			uVar2 = pDVar4->dwUnitId;
			uVar3 = pDVar4->dwUnitType;
			sub_6FB4E6A0(pDVar4);
			pDVar5 = sub_6FB26A60(uVar2, uVar3);
			pDVar4 = pDVar1;
			if (pDVar5 != nullptr)
			{
				if (pDVar5->dwUnitType == 1)
				{
					sub_6FB3F350(pDVar5);
				}
				else if (pDVar5->dwUnitType == 2)
				{
					sub_6FB48430(pDVar5);
				}
			}
		}
		puVar6 = puVar6 + 1;
	} while ((int)puVar6 < (int)&dword_6FBBBA00);
	sub_6FB28350((int)&dword_6FBBB800, (uint8_t*)(sub_6FAABE90));
	sub_6FB28350((int)&dword_6FBBB200, (uint8_t*)(sub_6FAABE90));
	sub_6FB28350((int)&dword_6FBBAA00, (uint8_t*)(sub_6FAABE90));
	sub_6FB28350((int)&dword_6FBBAC00, (uint8_t*)(sub_6FAABE90));
	sub_6FB28350((int)&dword_6FBBB800, (uint8_t*)(sub_6FB28380));
	sub_6FB28350((int)&dword_6FBBB200, (uint8_t*)(sub_6FB28380));
	sub_6FB28350((int)&dword_6FBBAA00, (uint8_t*)(sub_6FB28380));
	if (gnGameType == 0)
	{
		sub_6FB28350((int)&dword_6FBBAA00, (uint8_t*)(sub_6FB2A2D0));
		sub_6FB28350((int)&dword_6FBBAC00, (uint8_t*)(sub_6FB2A2D0));
		return;
	}
}

//D2Client.0x6FB28350
void __fastcall sub_6FB28350(int a1, uint8_t* a2)
{
	int iVar1;
	int iVar2;

	iVar2 = 0;
	do
	{
		iVar1 = *(int*)(a1 + iVar2 * 4);
		while (iVar1 != 0)
		{
			iVar1 = *(int*)(iVar1 + 0xe4);
			(*(code*)a2)();
		}
		iVar2 = iVar2 + 1;
	} while (iVar2 < 0x80);
}

//D2Client.0x6FB28380
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB28380()
{
	D2UnitStrc* in_ECX;

	STATLIST_FreeModStats(in_ECX);
}

//D2Client.0x6FB28390
void __fastcall sub_6FB28390(D2UnitStrc* pUnit)
{
	if (gpUnit_6FBBC200 != nullptr)
	{
		sub_6FB23960();
	}
	if (pUnit != nullptr)
	{
		PATH_SetDirection(pUnit->pDynamicPath, 0);
		byte_6FBA7894 = (uint8_t)pUnit->dwClassId;
		sub_6FAA8B40(0);
		sub_6FB23910();
	}
	gpUnit_6FBBC200 = pUnit;
}

//D2Client.0x6FB283D0
D2UnitStrc* __fastcall CUNIT_GetPlayer()
{
	return gpUnit_6FBBC200;
}

//D2Client.0x6FB283E0
bool __cdecl sub_6FB283E0()
{
	if (gpUnit_6FBBC200 == nullptr)
	{
		return true;
	}
	return gpUnit_6FBBC200->dwAnimMode == 0x11;
}

//D2Client.0x6FB28400
uint32_t __fastcall sub_6FB28400(int a1)
{
	if (a1 == 0)
	{
		return 0;
	}
	return *(uint32_t*)(a1 + 0x54);
}

//D2Client.0x6FB28410
void __fastcall sub_6FB28410(int hUnit, uint32_t a2)
{
	D2_ASSERT(hUnit);
	sub_6FB5BFC0(*(int*)(hUnit + 0x54), a2);
}

//D2Client.0x6FB28440
int32_t __fastcall sub_6FB28440(int hUnit)
{
	D2_ASSERT(hUnit);
	return sub_6FB5BFF0(*(int*)(hUnit + 0x54));
}

//D2Client.0x6FB28470
void __fastcall sub_6FB28470(int hUnit, uint32_t a2)
{
	D2_ASSERT(hUnit);
	sub_6FB5C020(*(int*)(hUnit + 0x54), a2);
}

//D2Client.0x6FB284A0
int32_t __fastcall sub_6FB284A0(int hUnit)
{
	D2_ASSERT(hUnit);
	return sub_6FB5C050(*(int*)(hUnit + 0x54));
}

//D2Client.0x6FB284D0
uint32_t __fastcall sub_6FB284D0(D2UnitStrc* pUnit, int a2, int a3)
{
	uint32_t uVar1;
	D2ActiveRoomStrc* pRoom;
	D2LvlWarpTxt* pDVar2;
	int iVar3;
	int iStack_8;
	int32_t DStack_4;

	D2_ASSERT(pUnit->dwUnitType == 5);
	pRoom = UNITS_GetRoom(pUnit);
	pDVar2 = DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit(pRoom, pUnit);
	if (pDVar2 != nullptr)
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_8 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_8 = 0;
		}
		else
		{
			iStack_8 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_4 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_4 + 2)) = 0;
		}
		else
		{
			DStack_4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DUNGEON_GameSubtileToClientCoords(&iStack_8, (int*)&DStack_4);
		iStack_8 = pDVar2->dwSelectX + iStack_8;
		iVar3 = pDVar2->dwSelectY + (int)DStack_4;
		if ((((iStack_8 <= a2) && (iVar3 <= a3)) &&
		        (a2 <= (int)(pDVar2->dwSelectDX + iStack_8))) &&
		    (a3 <= (int)(pDVar2->dwSelectDY + iVar3)))
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB285D0
void __fastcall sub_6FB285D0(uint32_t a1, D2UnitStrc* pUnit)
{
	D2COMMON_11021(pUnit);
}

//D2Client.0x6FB285E0
void __fastcall sub_6FB285E0(uint32_t a1, D2UnitStrc* pUnit)
{
	D2COMMON_11017_CheckUnitIfConsumeable(pUnit, 0);
}

//D2Client.0x6FB285F0
uint32_t __fastcall sub_6FB285F0(uint32_t a1, D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;

	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar2 = D2COMMON_11017_CheckUnitIfConsumeable(pUnit, 0);
	if (iVar2 == 0)
	{
		return 0;
	}
	iVar2 = sub_6FB44820((int*)pUnit);
	if (iVar2 == 0)
	{
		return 0;
	}
	if (pUnit->dwUnitType != 1)
	{
		return 0;
	}
	iVar2 = pUnit->dwClassId;
	if (-1 < iVar2)
	{
		if ((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)) &&
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar2 * 0x1a8, iVar1 != 0))
		{
			iVar2 = (int)*(short*)(iVar1 + 2);
		}
		if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
		    (iVar2 == 0x4e))
		{
			return 0;
		}
	}
	return 1;
}

//D2Client.0x6FB28680
void __fastcall sub_6FB28680(uint32_t a1, D2UnitStrc* pUnit)
{
	D2COMMON_11018(pUnit);
}

//D2Client.0x6FB28690
void __fastcall sub_6FB28690(uint32_t a1, D2UnitStrc* pUnit)
{
	D2Common_11020(pUnit);
}

//D2Client.0x6FB286A0
void __fastcall sub_6FB286A0(uint32_t a1, D2UnitStrc* pUnit)
{
	D2COMMON_11019(pUnit);
}

//D2Client.0x6FB286B0
bool __fastcall sub_6FB286B0(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;
	D2ObjectsTxt* pDVar2;

	pDVar1 = sub_6FAB5A20();
	if ((pDVar1 != nullptr) && (pDVar1->dwUnitType == 2))
	{
		pDVar2 = DATATBLS_GetObjectsTxtRecord(pDVar1->dwClassId);
		if ((char)pDVar2->nSubClass < '\0')
		{
			return false;
		}
	}
	pDVar1 = sub_6FAB5A20();
	return pDVar1 == pUnit;
}

//D2Client.0x6FB286F0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB286F0(D2UnitStrc* pUnit2, uint32_t a2, int a3, int a4)
{
	uint32_t uVar1;
	POINT pt;
	D2UnitStrc* pUnit;
	bool bVar2;
	uint8_t bVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	D2SkillStrc* pDVar7;
	int iVar8;
	int iVar9;
	BOOL BVar10;
	uint32_t extraout_var_01;
	D2ObjectsTxt* pDVar11;
	char* pcVar12;
	int iStack_38;
	uint32_t uStack_34;
	uint32_t uStack_30;
	int32_t local_2c;
	int iStack_28;
	int iStack_24;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	RECT RStack_10;

	iVar4 = sub_6FB57BC0();
	iVar5 = sub_6FAB5750();
	pUnit = gpUnit_6FBBC200;
	if (iVar5 == 1)
	{
		if (gnScreenWidth / 2 <= iVar4)
		{
			return 0;
		}
	}
	else if (iVar5 == 2)
	{
		if (iVar4 < gnScreenWidth / 2)
		{
			return 0;
		}
	}
	else if (iVar5 == 3)
	{
		return 0;
	}
	if ((pUnit2 != nullptr) &&
	    (local_2c = (int32_t)(pUnit2->dwFlags >> 0x15 & 1), local_2c != (int32_t)0x0))
	{
		return 0;
	}
	uVar6 = sub_6FB29D80(gpUnit_6FBBC200, pUnit2);
	if (((uVar6 == 0) &&
	        (bVar2 = sub_6FB2A0C0(pUnit, (int*)pUnit2), D2C_ZEXT(bVar2) == 0)) &&
	    (bVar2 = sub_6FB2A1C0(pUnit, (int*)pUnit2), D2C_ZEXT(bVar2) == 0))
	{
		return 0;
	}
	bVar2 = false;
	if (pUnit2 == nullptr)
	{
		return 0;
	}
	if (pUnit2->dwUnitType == 1)
	{
		iVar4 = 0x688;
		pcVar12 = __FILE__;
		pDVar7 = UNITS_GetLeftSkill(pUnit);
		iVar4 = SKILLS_GetSkillIdFromSkill(pDVar7, pcVar12, iVar4);
		iVar4 = sub_6FB14AE0(iVar4);
		if (((iVar4 == 0) || (bVar3 = *(uint8_t*)(iVar4 + 0x15), bVar3 == 0)) ||
		    ((dword_6FB9091C <= (int)(uint32_t)bVar3 ||
		        (iVar4 = (**(code**)(byte_6FB90900 + (uint32_t)bVar3 * 4))(), iVar4 == 0))))
		{
			iVar4 = 0x68c;
			pcVar12 = __FILE__;
			pDVar7 = UNITS_GetRightSkill(pUnit);
			iVar4 = SKILLS_GetSkillIdFromSkill(pDVar7, pcVar12, iVar4);
			iVar4 = sub_6FB28F20(iVar4);
			if (iVar4 == 0)
				goto LAB_6fb28858;
		}
		uVar6 = pUnit2->dwFlags;
		if ((uVar6 >> 1 & 1) != 0)
			goto LAB_6fb28869;
		if ((pUnit2->dwUnitType == 1) &&
		    ((((uVar6 & 0x10000) != 0 || (pUnit2->dwAnimMode == 0)) || (pUnit2->dwAnimMode == 0xc))))
		{
			uVar6 = uVar6 >> 2;
			goto LAB_6fb28860;
		}
	}
	else
	{
	LAB_6fb28858:
		uVar6 = pUnit2->dwFlags >> 1;
	LAB_6fb28860:
		if ((uVar6 & 1) != 0)
		{
		LAB_6fb28869:
			bVar2 = true;
		}
	}
	local_2c = (int32_t)(pUnit2->dwFlagEx >> 7 & 1);
	if (local_2c == (int32_t)0x0)
	{
		return 0;
	}
	if (!bVar2)
	{
		return 0;
	}
	if (a4 == 0)
	{
		return 1;
	}
	uStack_30 = UNITS_GetAnimOrSeqMode(pUnit2);
	iStack_38 = pUnit2->dwClassId;
	uStack_34 = pUnit2->dwUnitType;
	D2COMMON_11013_ConvertMode(pUnit2, (int*)&uStack_34, &iStack_38, (int*)&uStack_30,
	    __FILE__, __LINE__);
	pDVar11 = nullptr;
	iVar4 = UNITS_GetClientCoordX(pUnit2);
	iVar5 = UNITS_GetClientCoordY(pUnit2);
	switch (uStack_34)
	{
	case 0:
		goto LAB_6fb289ca;
	case 1:
		if ((((iStack_38 < 0) ||
		         (iVar9 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar9 + 0xa80) <= iStack_38)) ||
		        (iVar8 = (int)*(short*)(*(int*)(iVar9 + 0xa78) + 0x18 + iStack_38 * 0x1a8), iVar8 < 0)) ||
		    (*(int*)(iVar9 + 0xa98) <= iVar8))
		{
			iVar9 = 0;
		}
		else
		{
			iVar9 = *(int*)(iVar9 + 0xa90) + iVar8 * 0x134;
		}
		if (((uint8_t) * ((uint8_t*)&gdwBitMasks) & *(uint8_t*)(iVar9 + 4)) != 0)
		{
			RStack_10.left = *(short*)(iVar9 + 0x110) + iVar4;
			RStack_10.top = *(short*)(iVar9 + 0x10e) + iVar5;
			RStack_10.right = *(short*)(iVar9 + 0x112) + RStack_10.left;
			RStack_10.bottom = *(short*)(iVar9 + 0x114) + RStack_10.top;
			pt.y = a3;
			pt.x = a2;
			BVar10 = PtInRect(&RStack_10, pt);
			return (uint32_t)(BVar10 != 0);
		}
	LAB_6fb289ca:
		iVar4 = sub_6FB5C600(pUnit2, iVar4, iVar5, a2, a3);
		bVar2 = iVar4 == 0;
	LAB_6fb289d6:
		if (bVar2)
		{
			return 0;
		}
		break;
	case 2:
		pDVar11 = DATATBLS_GetObjectsTxtRecord(iStack_38);
		iVar4 = sub_6FB5C600(pUnit2, iVar4, iVar5, a2, a3);
		if ((iVar4 != 0) || (pDVar11->nIsDoor != 0))
			break;
		bVar2 = pDVar11->nCollisionSubst == 0;
		goto LAB_6fb289d6;
	case 4:
		if (pUnit2->dwAnimMode != 3)
		{
			return 0;
		}
		iVar4 = sub_6FB23230(0xd);
		if (iVar4 != 0)
		{
			return 0;
		}
		break;
	case 5:
		uVar6 = sub_6FB284D0(pUnit2, a2, a3);
		return uVar6;
	}
	uVar6 = 0;
	a4 = 0;
	if (uStack_34 == 0)
	{
	LAB_6fb28c63:
		a4 = 1;
	}
	else if (uStack_34 == 1)
	{
		if (((-1 < iStack_38) &&
		        (iVar4 = *(int*)((uint8_t*)&sgptDataTables), iStack_38 < *(int*)(iVar4 + 0xa80))) &&
		    ((iVar5 = (int)*(short*)(*(int*)(iVar4 + 0xa78) + 0x18 + iStack_38 * 0x1a8), -1 < iVar5 &&
		                                                                                     ((iVar5 < *(int*)(iVar4 + 0xa98) &&
		                                                                                         (iVar4 = *(int*)(iVar4 + 0xa90) + iVar5 * 0x134, iVar4 != 0))))))
		{
			bVar3 = *(uint8_t*)(iVar4 + 0xec);
		LAB_6fb28c61:
			if (1 < bVar3)
				goto LAB_6fb28c63;
		}
	}
	else if (uStack_34 == 2)
	{
		D2_ASSERT(pDVar11 != nullptr);
		if (pDVar11->nIsDoor == 0)
		{
			if (pDVar11->nCollisionSubst == 0)
				goto LAB_6fb28c02;
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				a4 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				a4 = 0;
			}
			else
			{
				a4 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				local_2c = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&local_2c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&local_2c + 2)) = 0;
			}
			else
			{
				local_2c = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
		}
		else
		{
			uVar1 = pUnit2->dwAnimMode;
			if (((uVar1 != 2) && (uVar1 != 4)) && (uVar1 != 5))
			{
			LAB_6fb28c02:
				bVar3 = pDVar11->nTotalPieces;
				goto LAB_6fb28c61;
			}
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				a4 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				a4 = 0;
			}
			else
			{
				a4 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				local_2c = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&local_2c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&local_2c + 2)) = 0;
			}
			else
			{
				local_2c = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
		}
		DUNGEON_GameSubtileToClientCoords(&a4, (int*)&local_2c);
		iVar4 = pDVar11->dwLeft + a4;
		iStack_1c = pDVar11->dwTop + (int)local_2c;
		if ((int)a2 < iVar4)
		{
			return 0;
		}
		if (a3 < iStack_1c)
		{
			return 0;
		}
		if ((int)(pDVar11->dwWidth + iVar4) < (int)a2)
		{
			return 0;
		}
		iStack_1c = pDVar11->dwHeight + iStack_1c;
		goto LAB_6fb28d5e;
	}
	UNITS_GetShiftedFrameMetrics(pUnit2, &iStack_28, &iStack_24);
	iStack_20 = 0;
	iStack_1c = 0;
	iStack_18 = 0;
	iStack_14 = 0;
	if (((pUnit2->dwUnitType == 0) && (pUnit2->dwClassId == 4)) && (pUnit2->dwAnimMode == 0x12))
	{
		return 1;
	}
	if (a4 != 0)
	{
		while (((iVar4 = sub_6FB28D90(pUnit2, uStack_30, uVar6, (D2CellFileStrc*)(iStack_28), &iStack_20, a4), iVar4 == 0 || (bVar3 = sub_6FB5F7F0(pUnit2, uVar6), D2C_ZEXT(bVar3) == 0)) ||
		        (((int)a2 < iStack_20 ||
		            (((iStack_18 < (int)a2 || (a3 < iStack_14)) || (iStack_1c < a3)))))))
		{
			uVar6 = uVar6 + 1;
			if (0xf < uVar6)
			{
				return 0;
			}
		}
		return 1;
	}
	iVar4 = sub_6FB28D90(pUnit2, uStack_30, 1, (D2CellFileStrc*)(iStack_28), &iStack_20, 0);
	if (iVar4 == 0)
	{
		return 0;
	}
	if ((int)a2 < iStack_20)
	{
		return 0;
	}
	if (iStack_18 < (int)a2)
	{
		return 0;
	}
	if (a3 < iStack_14)
	{
		return 0;
	}
LAB_6fb28d5e:
	if (a3 <= iStack_1c)
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB28D90
uint32_t __fastcall sub_6FB28D90(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, D2CellFileStrc* pCellFile, int* a5, uint32_t a6)
{
	uint8_t bVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	D2CellFileStrc** ppDVar5;
	D2CellFileStrc* pDVar6;
	D2InventoryStrc** ppDVar7;
	D2InventoryStrc* pDVar8;
	D2InventoryStrc* local_4c;
	D2CellFileStrc* local_48[5];
	D2CellFileStrc* pDStack_34;

	iVar2 = sub_6FB5E200(pUnit, a3);
	if (iVar2 != 0)
	{
		pDVar8 = (D2InventoryStrc*)0xffffffff;
		ppDVar5 = local_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*ppDVar5 = nullptr;
			ppDVar5 = ppDVar5 + 1;
		}
		ppDVar7 = &local_4c;
		pDVar6 = pCellFile;
		bVar1 = UNITS_GetDirection(pUnit);
		iVar2 = sub_6FB5EC80((int)local_48, pUnit, 0, (D2CellFileStrc*)(uint32_t)bVar1, pDVar6, ppDVar7,
		    (char)a3, pDVar8);
		if (iVar2 != 0)
		{
			iVar2 = D2CMP_10055((int)local_48, 0, 1);
			if ((iVar2 != 0) && (local_48[0] != nullptr))
			{
				D2_ASSERT(pDStack_34 >= pCellFile);
				iVar2 = D2CMP_CelGetOffsetX(local_48[0]);
				iVar3 = UNITS_GetClientCoordX(pUnit);
				*a5 = iVar2 + -0xc + iVar3;
				iVar2 = D2CMP_CelGetWidth(local_48[0]);
				a5[2] = iVar2 + 0x18 + *a5;
				iVar3 = D2CMP_CelGetOffsetY(local_48[0]);
				iVar2 = UNITS_GetClientCoordY(pUnit);
				iVar3 = iVar2 + 0xc + iVar3;
				a5[1] = iVar3;
				iVar2 = D2CMP_CelGetHeight(local_48[0]);
				iVar2 = (iVar3 - iVar2) + -0x18;
				iVar4 = a5[2] - *a5;
				a5[3] = iVar2;
				if (iVar4 < 0x20)
				{
					iVar4 = 0x20 - iVar4 >> 1;
					a5[2] = iVar4 + a5[2];
					*a5 = *a5 - iVar4;
				}
				iVar2 = iVar3 - iVar2;
				if (iVar2 < 0x20)
				{
					iVar2 = 0x20 - iVar2 >> 1;
					a5[3] = a5[3] - iVar2;
					a5[1] = iVar2 + iVar3;
				}
				iVar2 = sub_6FB5FBA0((int)pUnit);
				iVar3 = sub_6FB5FBC0((int)pUnit);
				iVar4 = sub_6FB5FBE0((int)pUnit);
				*a5 = *a5 + iVar2;
				a5[2] = a5[2] + iVar2;
				a5[1] = a5[1] + iVar3 + iVar4;
				a5[3] = a5[3] + iVar3 + iVar4;
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB28F20
uint32_t __cdecl sub_6FB28F20(int a1)
{
	uint8_t bVar1;
	int iVar2;

	if ((((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a1 * 0x23c, iVar2 != 0)) &&
	    ((bVar1 = *(uint8_t*)(iVar2 + 0x15), bVar1 != 0 && ((int)(uint32_t)bVar1 < dword_6FB9091C))))
	{
		iVar2 = (**(code**)(byte_6FB90900 + (uint32_t)bVar1 * 4))();
		if (iVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB28F90
void __fastcall sub_6FB28F90(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	D2UnitStrc* pTargetUnit;

	for (pTargetUnit = (D2UnitStrc*)(&dword_6FBBAA00)[a2 * 0x80 + (a3 & 0x7f)];
	     pTargetUnit != nullptr; pTargetUnit = pTargetUnit->pListNext)
	{
		if (pTargetUnit->dwUnitId == a3)
		{
			if (pTargetUnit->dwUnitType == a2)
				goto LAB_6fb28fdf;
			FOG_Trace("current unit is %d, table is supposed to be %d\n", pTargetUnit->dwUnitType, a2);
			D2_ASSERT(pTargetUnit->dwUnitType == a2);
		}
	}
	pTargetUnit = nullptr;
LAB_6fb28fdf:
	UNITS_SetTargetUnitForDynamicUnit(pUnit, pTargetUnit);
}

//D2Client.0x6FB29010
void __fastcall sub_6FB29010(D2UnitStrc* pUnit, int a2)
{
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int32_t nY;
	int nX;

	sub_6FB4DEC0((int)pUnit);
	D2_ASSERT(pUnit->pDynamicPath != nullptr);
	pDVar2 = PATH_GetTargetUnit(pUnit->pDynamicPath);
	if ((pDVar2 != nullptr) && (pDVar2 != pUnit))
	{
		pDynamicPath = pUnit->pDynamicPath;
		D2_ASSERT(pDynamicPath != nullptr);
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
		{
			if (pDVar2->pDynamicPath != nullptr)
			{
				nX = PATH_GetXPosition(pDVar2->pDynamicPath);
				D2Common_10216(pDynamicPath, nX, (int)nY, a2);
				return;
			}
			D2Common_10216(pDynamicPath, 0, (int)nY, a2);
			return;
		}
		D2Common_10216(pDynamicPath, pDVar2->pDynamicPath->dwClientCoordY, (int)nY, a2);
	}
}

//D2Client.0x6FB29100
void __fastcall sub_6FB29100(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int32_t nY;
	int nX;

	pDVar2 = gpUnit_6FBBC200;
	pDynamicPath = pUnit->pDynamicPath;
	D2_ASSERT(pDynamicPath != nullptr);
	UNITS_ChangeAnimMode(pUnit, 1);
	uVar1 = pDVar2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		nY = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
	}
	else if (pDVar2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
	}
	else
	{
		nY = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
	}
	uVar1 = pDVar2->dwUnitType;
	if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
	{
		if (pDVar2->pDynamicPath != nullptr)
		{
			nX = PATH_GetXPosition(pDVar2->pDynamicPath);
			D2Common_10216(pDynamicPath, nX, (int)nY, 0);
			return;
		}
		D2Common_10216(pDynamicPath, 0, (int)nY, 0);
		return;
	}
	D2Common_10216(pDynamicPath, pDVar2->pDynamicPath->dwClientCoordY, (int)nY, 0);
}

//D2Client.0x6FB291C0
void __fastcall sub_6FB291C0(int* a1)
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	int iVar2;

	if ((gpUnit_6FBBC200 != nullptr) &&
	    ((gpUnit_6FBBC200->dwAnimMode == 1 || (gpUnit_6FBBC200->dwAnimMode == 5))))
	{
		pDynamicPath = gpUnit_6FBBC200->pDynamicPath;
		D2_ASSERT(pDynamicPath != nullptr);
		iVar1 = *a1;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
		{
			iVar1 = *(int*)(a1[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
		{
			iVar1 = 0;
		}
		else
		{
			iVar1 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
		}
		iVar2 = *a1;
		if ((iVar2 != 2) && ((iVar2 < 4 || (5 < iVar2))))
		{
			if ((D2DynamicPathStrc*)a1[0xb] != nullptr)
			{
				iVar2 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
				D2Common_10216(pDynamicPath, iVar2, iVar1, 0);
				return;
			}
			D2Common_10216(pDynamicPath, 0, iVar1, 0);
			return;
		}
		D2Common_10216(pDynamicPath, *(int*)(a1[0xb] + 0xc), iVar1, 0);
	}
}

//D2Client.0x6FB29290
bool __fastcall sub_6FB29290(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	D2SkillStrc* pSkill;
	D2SkillsTxt* pDVar4;

	pDVar3 = INVENTORY_GetCursorItem(pUnit->pInventory);
	if (pDVar3 != nullptr)
	{
		return false;
	}
	if (pUnit->dwUnitType != 0)
	{
		return false;
	}
	switch (pUnit->dwAnimMode)
	{
	case 0:
	case 4:
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xc:
	case 0x11:
	case 0x13:
		return false;
	case 0xd:
		if (pUnit->dwClassId == 3)
		{
			return false;
		}
		break;
	case 0xe:
		if (pUnit->dwClassId == 6)
		{
			return false;
		}
		break;
	case 0xf:
	case 0x10:
		iVar2 = pUnit->dwClassId;
		if (((iVar2 == 4) || (iVar2 == 6)) || (iVar2 == 5))
		{
			return false;
		}
		break;
	case 0x12:
		pSkill = UNITS_GetUsedSkill(pUnit);
		if (pSkill != nullptr)
		{
			pDVar4 = SKILLS_GetSkillsTxtRecordFromSkill(pSkill);
			if (pDVar4 == nullptr)
			{
				return false;
			}
			if (pDVar4->nAnim == 0x12)
			{
				bVar1 = pDVar4->nSeqInput;
				if (bVar1 == 0)
				{
					return false;
				}
				if (bVar1 == 0xff)
				{
					return false;
				}
				return (int)(uint32_t)bVar1 <= pUnit->dwSeqFrame >> 8;
			}
		}
	}
	return true;
}

//D2Client.0x6FB29370
D2ActiveRoomStrc* __fastcall CUNIT_GetPlayerRoom()
{
	D2ActiveRoomStrc* pDVar1;

	if (gpUnit_6FBBC200 != nullptr)
	{
		pDVar1 = UNITS_GetRoom(gpUnit_6FBBC200);
		return pDVar1;
	}
	return nullptr;
}

//D2Client.0x6FB29390
void __cdecl sub_6FB29390()
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t* puVar4;

	iVar3 = ENVIRONMENT_GetPeriodOfDayFromAct(ghAct, nullptr);
	if (iVar3 != dword_6FBBC204)
	{
		puVar4 = &dword_6FBBAE00;
		dword_6FBBC204 = iVar3;
		do
		{
			pDVar2 = (D2UnitStrc*)*puVar4;
			while (pDVar2 != nullptr)
			{
				pDVar1 = pDVar2->pListNext;
				D2_ASSERT(pDVar2->dwUnitType == 2);
				sub_6FB467E0(pDVar2, 0);
				pDVar2 = pDVar1;
			}
			puVar4 = puVar4 + 1;
		} while ((int)puVar4 < (int)&dword_6FBBB000);
		puVar4 = &dword_6FBBBA00;
		do
		{
			pDVar2 = (D2UnitStrc*)*puVar4;
			while (pDVar2 != nullptr)
			{
				pDVar1 = pDVar2->pListNext;
				D2_ASSERT(pDVar2->dwUnitType == 2);
				sub_6FB467E0(pDVar2, 0);
				pDVar2 = pDVar1;
			}
			puVar4 = puVar4 + 1;
		} while ((int)puVar4 < (int)&dword_6FBBBC00);
	}
}

//D2Client.0x6FB29450
uint32_t __fastcall sub_6FB29450(int ptUnit)
{
	D2_ASSERT(ptUnit);
	return *(uint32_t*)(ptUnit + 0xd8);
}

//D2Client.0x6FB29480
void __fastcall sub_6FB29480(int ptUnit, uint32_t a2)
{
	D2_ASSERT(ptUnit);
	*(uint32_t*)(ptUnit + 0xd8) = a2;
}

//D2Client.0x6FB294B0
void __fastcall sub_6FB294B0(int* a1)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;

	uVar1 = a1[0x31];
	a1[0x31] = uVar1 & 0xfffeffff;
	if ((*a1 != 1) ||
	    ((((iVar3 = a1[1], -1 < iVar3 &&
	                           (iVar2 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar2 + 0xa80))) &&
	          (iVar3 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar3 * 0x1a8), -1 < iVar3)) &&
	        (((iVar3 < *(int*)(iVar2 + 0xa98) &&
	              (iVar3 = *(int*)(iVar2 + 0xa90) + iVar3 * 0x134, iVar3 != 0)) &&
	            (((uint32_t) * (uint8_t*)(iVar3 + 5) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) != 0))))))
	{
		a1[0x31] = uVar1 & 0xfffeffff | 4;
	}
}

//D2Client.0x6FB29540
void __fastcall sub_6FB29540(int a1)
{
	if (a1 != 0)
	{
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | 0x10000;
	}
}

//D2Client.0x6FB29550
uint32_t __fastcall sub_6FB29550(int* a1)
{
	int iVar1;

	if ((a1[0x31] & 0x10000U) == 0)
	{
		iVar1 = a1[4];
		if (*a1 == 0)
		{
			if ((iVar1 != 0) && (iVar1 != 0x11))
			{
				return 0;
			}
		}
		else if ((*a1 != 1) || ((iVar1 != 0 && (iVar1 != 0xc))))
		{
			return 0;
		}
	}
	return 1;
}

//D2Client.0x6FB29590
bool __fastcall sub_6FB29590(uint32_t* a1)
{
	int iVar1;
	int iVar2;
	D2ObjectsTxt* pDVar3;
	int iVar4;

	if (a1 != nullptr)
	{
		iVar1 = a1[4];
		switch (*a1)
		{
		case 0:
			if (iVar1 == 0x11)
			{
				return true;
			}
			break;
		case 1:
			iVar4 = a1[1];
			if (((((iVar4 < 0) || (iVar2 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar2 + 0xa80) <= iVar4)) || (iVar4 = (int)*(short*)(*(int*)(iVar2 + 0xa78) + 0x18 + iVar4 * 0x1a8), iVar4 < 0)) ||
			        (((*(int*)(iVar2 + 0xa98) <= iVar4 ||
			              (iVar4 = *(int*)(iVar2 + 0xa90) + iVar4 * 0x134, iVar4 == 0)) ||
			            (((uint32_t) * (uint8_t*)(iVar4 + 6) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x10)) == 0)))) &&
			    (iVar1 == 0xc))
			{
				return true;
			}
			break;
		case 2:
			pDVar3 = DATATBLS_GetObjectsTxtRecord(a1[1]);
			if ((pDVar3->nDrawUnder & 2) != 0)
			{
				return true;
			}
			if ((iVar1 == 2) && ((pDVar3->nDrawUnder & 1) != 0))
			{
				return true;
			}
			break;
		case 3:
			if ((a1[0x31] & 0x10000) != 0)
			{
				return true;
			}
			break;
		case 4:
			return iVar1 == 3;
		}
	}
	return false;
}

//D2Client.0x6FB296A0
D2UnitStrc* __fastcall sub_6FB296A0(int a1)
{
	D2UnitStrc* pDVar1;

	sub_6FB4DEC0(a1);
	D2_ASSERT(*(D2DynamicPathStrc**)(a1 + 0x2c) != nullptr);
	pDVar1 = PATH_GetTargetUnit(*(D2DynamicPathStrc**)(a1 + 0x2c));
	return pDVar1;
}

//D2Client.0x6FB296E0
int32_t __fastcall sub_6FB296E0(int a1)
{
	if (*(int*)(a1 + 100) != 0)
	{
		sub_6FAA44D0(*(int*)(a1 + 100));
		*(uint32_t*)(a1 + 100) = 0;
	}
	return 0;
}

//D2Client.0x6FB29700
void __fastcall sub_6FB29700(uint8_t* a1)
{
	int iVar1;
	int* piVar2;

	if (a1 != nullptr)
	{
		piVar2 = (int*)(&dword_6FBBAA00);
		do
		{
			iVar1 = *piVar2;
			while (iVar1 != 0)
			{
				iVar1 = *(int*)(iVar1 + 0xe4);
				(*(code*)a1)();
			}
			piVar2 = piVar2 + 1;
		} while ((int)piVar2 < (int)&dword_6FBBAC00);
		return;
	}
	FOG_DisplayAssert("pfnUnitFunction", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB29750
void __fastcall sub_6FB29750(uint8_t* a1)
{
	int iVar1;
	int* piVar2;

	if (a1 != nullptr)
	{
		piVar2 = (int*)(&dword_6FBBAC00);
		do
		{
			iVar1 = *piVar2;
			while (iVar1 != 0)
			{
				iVar1 = *(int*)(iVar1 + 0xe4);
				(*(code*)a1)();
			}
			piVar2 = piVar2 + 1;
		} while ((int)piVar2 < (int)&dword_6FBBAE00);
		return;
	}
	FOG_DisplayAssert("pfnUnitFunction", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB297A0
void __fastcall sub_6FB297A0(uint8_t* a1)
{
	int iVar1;
	int* piVar2;

	if (a1 != nullptr)
	{
		piVar2 = (int*)(&dword_6FBBAE00);
		do
		{
			iVar1 = *piVar2;
			while (iVar1 != 0)
			{
				iVar1 = *(int*)(iVar1 + 0xe4);
				(*(code*)a1)();
			}
			piVar2 = piVar2 + 1;
		} while ((int)piVar2 < (int)&dword_6FBBB000);
		return;
	}
	FOG_DisplayAssert("pfnUnitFunction", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB297F0
Unicode* __fastcall sub_6FB297F0(D2UnitStrc* ptUnit)
{
	D2UnitStrc* pDVar1;
	D2PlayerDataStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	D2LevelsTxt* pDVar3;
	int iVar4;
	D2ItemsTxt* pDVar5;
	Unicode* pUVar6;
	short index;
	uint32_t uVar7;
	uint32_t uStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	D2_ASSERT(ptUnit != nullptr);
	switch (ptUnit->dwUnitType)
	{
	default:
		return nullptr;
	case 1:
		if (ptUnit->pPlayerData == nullptr)
		{
			pUVar6 = nullptr;
		}
		else
		{
			pUVar6 = (Unicode*)ptUnit->pPlayerData->nPortalFlags;
		}
		iVar4 = Unicode::strlen(pUVar6);
		if (iVar4 == 0)
		{
			iVar4 = ptUnit->dwClassId;
			if ((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)))
			{
				pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + 6 +
				                                                           iVar4 * 0x1a8)));
				return pUVar6;
			}
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex((*(int16_t*)0x6)));
			return pUVar6;
		}
		return pUVar6;
	case 2:
		break;
	case 4:
		pDVar5 = DATATBLS_GetItemsTxtRecord(ptUnit->dwClassId);
		pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar5->wNameStr));
		return pUVar6;
	}
	if ((*(char*)(*(int*)ptUnit->pPlayerData->szName + 0x1b8) != '\0') &&
	    (ptUnit->dwAnimMode == 2))
	{
		pRoom = UNITS_GetRoom(ptUnit);
		for (pDVar1 = pRoom->pUnitFirst; pDVar1 != nullptr; pDVar1 = pDVar1->pRoomNext)
		{
			if (pDVar1->dwUnitType == 5)
			{
				iVar4 = pDVar1->dwClassId;
			LAB_6fb298ae:
				iVar4 = DUNGEON_GetWarpDestinationLevel(pRoom, iVar4);
				if (iVar4 == 0)
				{
					return nullptr;
				}
				pDVar3 = DATATBLS_GetLevelsTxtRecord(iVar4);
				return pDVar3->wszLevelWarp;
			}
		}
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_4, (int*)&uStack_8);
		uVar7 = 0;
		if (uStack_8 != 0)
		{
			do
			{
				if (ppDStack_4[uVar7] != pRoom)
				{
					for (pDVar1 = ppDStack_4[uVar7]->pUnitFirst; pDVar1 != nullptr;
					     pDVar1 = pDVar1->pRoomNext)
					{
						if (pDVar1->dwUnitType == 5)
						{
							iVar4 = pDVar1->dwClassId;
							pRoom = ppDStack_4[uVar7];
							goto LAB_6fb298ae;
						}
					}
				}
				uVar7 = uVar7 + 1;
			} while (uVar7 < uStack_8);
		}
	}
	if (*(char*)(*(int*)ptUnit->pPlayerData->szName + 0x13a) == '\0')
	{
		iVar4 = UNITS_IsShrine(ptUnit);
		pDVar2 = ptUnit->pPlayerData;
		if (iVar4 != 0)
		{
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex((uint8_t)pDVar2->szName[4] + 0x2a39));
			return pUVar6;
		}
		if ((*(char*)(*(int*)pDVar2->szName + 0x171) != '\0') && (pDVar2->szName[4] < '\0'))
		{
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xcbe));
			return pUVar6;
		}
		return (Unicode*)(*(int*)pDVar2->szName + 0x40);
	}
	uVar7 = ptUnit->dwAnimMode;
	index = 0xc9b;
	if ((uVar7 == 5) || (uVar7 == 4))
	{
		index = 0xc9c;
	}
	else
	{
		if (uVar7 == 0)
		{
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xc99));
			return pUVar6;
		}
		if (uVar7 == 6)
		{
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xc9d));
			return pUVar6;
		}
	}
	pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	return pUVar6;
}

//D2Client.0x6FB29A40
uint32_t __fastcall sub_6FB29A40(D2UnitStrc* ptUnit)
{
	D2GfxDataStrc* pDVar1;
	int iVar2;

	D2_ASSERT(ptUnit != nullptr);
	pDVar1 = ptUnit->pGfxDataCopy;
	if (pDVar1 == nullptr)
	{
		return (uint32_t)pDVar1;
	}
	ptUnit->pGfxDataCopy = (D2GfxDataStrc*)((int)&pDVar1[-1].pName + 3);
	iVar2 = STATES_CheckState(ptUnit, 0x8f);
	return (uint32_t)(iVar2 == 0);
}

//D2Client.0x6FB29A80
void __fastcall sub_6FB29A80(int ptUnit)
{
	D2_ASSERT(ptUnit);
	*(uint32_t*)(ptUnit + 0x58) = 3;
}

//D2Client.0x6FB29AB0
void __fastcall sub_6FB29AB0(int ptUnit, uint32_t a2)
{
	D2_ASSERT(ptUnit);
	*(uint32_t*)(ptUnit + 0x68) = a2;
}

//D2Client.0x6FB29AE0
void __fastcall sub_6FB29AE0(D2UnitStrc* hUnit, int a2)
{
	D2InventoryStrc* pInventory;
	bool bVar1;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	D2UnitStrc* pItem_00;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint32_t* puStack_18;
	int iStack_14;

	D2_ASSERT(hUnit != nullptr);
	pInventory = hUnit->pInventory;
	if (pInventory == nullptr)
	{
		return;
	}
	pItem = INVENTORY_GetFirstItem(pInventory);
	do
	{
		if (pItem == nullptr)
		{
			return;
		}
		pDVar2 = INVENTORY_GetNextItem(pItem);
		uVar3 = INVENTORY_GetItemGUID(pItem);
		for (pDVar5 = (D2UnitStrc*)(&dword_6FBBB200)[uVar3 & 0x7f]; pItem = pDVar2,
		    pDVar5 != nullptr;
		     pDVar5 = pDVar5->pListNext)
		{
			if (pDVar5->dwUnitId == uVar3)
			{
				if (pDVar5->dwUnitType == 4)
				{
					if (pDVar5 != nullptr)
					{
						if (a2 == 0)
							goto LAB_6fb29c2a;
						puStack_18 = &dword_6FBBAA00;
						iStack_14 = 0;
						do
						{
							iVar6 = 0;
							do
							{
								for (pDVar2 = (D2UnitStrc*)puStack_18[iVar6]; pDVar2 != nullptr;
								     pDVar2 = pDVar2->pListNext)
								{
									if ((hUnit != pDVar2) && (pDVar2->pInventory != nullptr))
									{
										for (pItem_00 = INVENTORY_GetFirstItem(pDVar2->pInventory);
										     pItem_00 != nullptr; pItem_00 = INVENTORY_GetNextItem(pItem_00))
										{
											pDVar4 = INVENTORY_UnitIsItem(pItem_00);
											D2_ASSERT(pDVar4 != nullptr);
											if (pDVar4 == pDVar5)
											{
												bVar1 = true;
												goto LAB_6fb29c1d;
											}
										}
									}
								}
								iVar6 = iVar6 + 1;
							} while (iVar6 < 0x80);
							puStack_18 = &dword_6FBBAC00;
							iStack_14 = iStack_14 + 1;
						} while (iStack_14 < 2);
						bVar1 = false;
					LAB_6fb29c1d:
						if (bVar1)
						{
							pDVar5 = INVENTORY_RemoveItemFromInventory(pInventory, pDVar5);
							D2_ASSERT(pDVar5 != nullptr);
						}
						else
						{
						LAB_6fb29c2a:
							sub_6FB2A880(pDVar5, hUnit, 0, 0);
							pDVar2 = INVENTORY_RemoveItemFromInventory(pInventory, pDVar5);
							D2_ASSERT(pDVar2 != nullptr);
							sub_6FB26C00((int)(&dword_6FBBAA00 + pDVar5->dwUnitType * 0x80), pDVar5->dwUnitId & 0x7f,
							    pDVar5->dwUnitId, pDVar5->dwUnitType);
						}
					}
					break;
				}
				FOG_Trace("current unit is %d, table is supposed to be %d\n", pDVar5->dwUnitType, 4);
				D2_ASSERT(pDVar5->dwUnitType == 4);
			}
		}
	} while (true);
}

//D2Client.0x6FB29D10
void __fastcall sub_6FB29D10(D2UnitStrc* pUnit, int a2, uint32_t a3)
{
	uint32_t uVar1;

	if (pUnit != nullptr)
	{
		if ((int)a3 < 1)
		{
			a3 = 0;
			uVar1 = 2;
		}
		else
		{
			uVar1 = 1;
		}
		sub_6FB5BA70(pUnit, a2, uVar1, 0, a3, 0, 0, 0);
		if (a2 == 0x97)
		{
			sub_6FB55820(0x18c, pUnit, 0.0, 0.0, 0);
		}
		else if (a2 == 0x98)
		{
			sub_6FB55820(0x18d, pUnit, 0.0, 0.0, 0);
			return;
		}
	}
}

//D2Client.0x6FB29D80
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB29D80(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	int iVar1;
	bool bVar2;
	D2ActiveRoomStrc* pRoom;
	int iVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t local_14;
	uint32_t local_10;
	uint32_t local_c;

	if (pUnit == nullptr)
	{
		local_10 = 6;
		local_14 = 0xffffffff;
	}
	else
	{
		local_10 = pUnit->dwUnitType;
		local_14 = pUnit->dwUnitId;
	}
	if (pUnit2 == nullptr)
	{
		local_c = 6;
		uVar6 = 0xffffffff;
	}
	else
	{
		local_c = pUnit2->dwUnitType;
		uVar6 = pUnit2->dwUnitId;
	}
	pRoom = UNITS_GetRoom(pUnit);
	iVar3 = DUNGEON_IsRoomInTown(pRoom);
	if (iVar3 == 0)
	{
		if (local_10 == 1)
		{
			uVar4 = sub_6FAB1B00(local_14);
			if (uVar4 != 0xffffffff)
			{
				local_10 = 0;
				local_14 = uVar4;
			}
			if (((pUnit != nullptr) && ((pUnit->dwFlagEx >> 10 & 1) != 0)) &&
			    (pUnit2->dwOwnerType == 0))
			{
				local_14 = pUnit->dwOwnerGUID;
				local_10 = 0;
			}
		}
		if (local_c == 1)
		{
			uVar4 = sub_6FAB1B00(uVar6);
			if (uVar4 != 0xffffffff)
			{
				local_c = 0;
				uVar6 = uVar4;
			}
			if (((pUnit2 != nullptr) && ((pUnit2->dwFlagEx >> 10 & 1) != 0)) &&
			    (pUnit2->dwOwnerType == 0))
			{
				uVar6 = pUnit2->dwOwnerGUID;
				local_c = 0;
			}
		}
		if ((local_10 == local_c) && (local_14 == uVar6))
		{
			return 0;
		}
		if ((local_10 == 0) && (local_c == 0))
		{
			if (((pUnit2 != nullptr) && (pUnit2->dwUnitType == 0)) &&
			    (((((pUnit2->dwFlags & 0x10000) != 0 || (pUnit2->dwAnimMode == 0)) ||
			          (pUnit2->dwAnimMode == 0x11)) &&
			        (iVar3 = sub_6FAB1200(local_14, pUnit2->dwUnitId), iVar3 != 0))))
			{
				return 1;
			}
			uVar6 = sub_6FB4B900(local_14, uVar6, 8);
			return uVar6;
		}
		if (((local_c == 1) && (pUnit2 != nullptr)) &&
		    (iVar3 = pUnit2->dwClassId, -1 < iVar3))
		{
			iVar1 = *(int*)((uint8_t*)&sgptDataTables);
			if (((iVar3 < *(int*)(iVar1 + 0xa80)) &&
			        (iVar5 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar3 * 0x1a8), -1 < iVar5)) &&
			    ((iVar5 < *(int*)(iVar1 + 0xa98) &&
			        ((iVar1 = *(int*)(iVar1 + 0xa90) + iVar5 * 0x134, iVar1 != 0 &&
			                                                              (((uint32_t) * (uint8_t*)(iVar1 + 4) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x10)) != 0))))))
			{
				return 1;
			}
			if (((((-1 < iVar3) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), iVar3 < *(int*)(iVar1 + 0xa80))) && (iVar3 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + iVar3 * 0x1a8),
			                                                                                                            -1 < iVar3)) &&
			        ((iVar3 < *(int*)(iVar1 + 0xa98) &&
			            (iVar3 = *(int*)(iVar1 + 0xa90) + iVar3 * 0x134, iVar3 != 0)))) &&
			    (((uint32_t) * (uint8_t*)(iVar3 + 4) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x14)) != 0))
			{
				return 0;
			}
		}
		if ((local_10 != 0) || ((local_c != 4 && (local_c != 2))))
		{
			iVar3 = STATLIST_AreUnitsAligned(pUnit, pUnit2);
			return (uint32_t)(iVar3 == 0);
		}
	}
	else
	{
		if ((((pUnit2 != nullptr) && (pUnit2->dwUnitType == 0)) &&
		        (((pUnit2->dwFlags & 0x10000) != 0 ||
		            ((pUnit2->dwAnimMode == 0 || (pUnit2->dwAnimMode == 0x11)))))) &&
		    (iVar3 = sub_6FAB1200(local_14, pUnit2->dwUnitId), iVar3 == 0))
		{
			return 0;
		}
		if (((((pUnit != nullptr) && (pUnit->dwUnitType == 0)) &&
		         (pUnit2 != nullptr)) &&
		        ((pUnit2->dwUnitType == 1 && (iVar3 = sub_6FAB1B00(pUnit2->dwUnitId), iVar3 != -1)))) &&
		    (bVar2 = sub_6FB2A0C0(pUnit, (int*)pUnit2), D2C_ZEXT(bVar2) == 0))
		{
			return 0;
		}
	}
	return 1;
}

//D2Client.0x6FB2A0C0
bool __fastcall sub_6FB2A0C0(D2UnitStrc* pUnit, int* a2)
{
	bool bVar1;
	D2SkillStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;

	bVar1 = false;
	if (((pUnit != nullptr) && (a2 != nullptr)) &&
	    ((pUnit->dwUnitType == 0 || (*a2 == 1))))
	{
		pDVar2 = UNITS_GetLeftSkill(pUnit);
		if (pDVar2 != nullptr)
		{
			iVar3 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__);
			if ((((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
			        (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0)) &&
			    (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar3 + 7)) != 0))
			{
				bVar1 = true;
			}
		}
		pDVar2 = UNITS_GetRightSkill(pUnit);
		if (pDVar2 != nullptr)
		{
			iVar3 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__);
			if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
			    ((iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0 &&
			                                                                                       (((uint8_t)((uint8_t*)&gdwBitMasks)[4] & *(uint8_t*)(iVar3 + 7)) != 0))))
				goto LAB_6fb2a193;
		}
		if (bVar1)
		{
		LAB_6fb2a193:
			uVar4 = sub_6FAB1B00(a2[3]);
			return uVar4 == pUnit->dwUnitId;
		}
	}
	return false;
}

//D2Client.0x6FB2A1C0
bool __fastcall sub_6FB2A1C0(D2UnitStrc* pUnit, int* a2)
{
	bool bVar1;
	D2SkillStrc* pDVar2;
	int iVar3;

	bVar1 = false;
	if (pUnit == nullptr)
	{
		return false;
	}
	if (a2 == nullptr)
	{
		return false;
	}
	if (((pUnit->dwUnitType != 0) && (*a2 != 0)) && (*a2 != 1))
	{
		return false;
	}
	pDVar2 = UNITS_GetLeftSkill(pUnit);
	if (((pDVar2 != nullptr) &&
	        (iVar3 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__),
	            -1 < iVar3)) &&
	    ((iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) &&
	        ((iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0 &&
	                                                                                           (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar3 + 7)) != 0))))))
	{
		bVar1 = true;
	}
	pDVar2 = UNITS_GetRightSkill(pUnit);
	if (((((pDVar2 == nullptr) ||
	          (iVar3 = SKILLS_GetSkillIdFromSkill(pDVar2, __FILE__, __LINE__), iVar3 < 0)) ||
	         (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar3)) ||
	        ((iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 == 0 ||
	                                                                                           (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar3 + 7)) == 0)))) &&
	    (!bVar1))
	{
		return false;
	}
	iVar3 = a2[3];
	if ((*a2 == 1) && (iVar3 = sub_6FAB1B00(iVar3), iVar3 == -1))
	{
		return false;
	}
	iVar3 = sub_6FAB1260(pUnit->dwUnitId, iVar3);
	return iVar3 != 0;
}

//D2Client.0x6FB2A2D0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB2A2D0()
{
	uint16_t nX;
	uint16_t nY;
	D2DynamicPathStrc* pDynamicPath;
	D2DynamicPathStrc* pDynamicPath_00;
	D2UnitStrc* pUnit;
	uint32_t uVar1;
	D2ActiveRoomStrc* pDVar2;
	D2SkillStrc* pSkill;
	D2SkillStrc* pSkill_00;
	D2UnitStrc* in_ECX;
	uint32_t uVar3;
	int iVar4;
	D2PathPointStrc* pDVar5;
	D2PathPointStrc* pDVar6;
	uint32_t uStack_14;
	D2ActiveRoomStrc** ppDStack_10;
	uint32_t uStack_c;
	D2ActiveRoomStrc* pDStack_8;
	D2UnitStrc* pDStack_4;

	D2_ASSERT(!gnGameType);
	if (in_ECX == nullptr)
	{
		uVar3 = 6;
		uVar1 = 0xffffffff;
	}
	else
	{
		uVar3 = in_ECX->dwUnitType;
		uVar1 = in_ECX->dwUnitId;
	}
	pDStack_4 = DEBUG_GetUnitFromTypeAndGUID(uVar3, uVar1);
	if (pDStack_4 == nullptr)
	{
		return;
	}
	pDynamicPath = pDStack_4->pDynamicPath;
	pDynamicPath_00 = in_ECX->pDynamicPath;
	pDVar2 = UNITS_GetRoom(in_ECX);
	if (pDVar2 == nullptr)
	{
		return;
	}
	nX = *(uint16_t*)((uint8_t*)pDynamicPath + 0x2);
	uVar3 = (uint32_t)nX;
	nY = *(uint16_t*)((uint8_t*)pDynamicPath + 0x6);
	uVar1 = (uint32_t)nY;
	pDStack_8 = pDVar2;
	if ((uVar3 != *(uint16_t*)((uint8_t*)pDynamicPath_00 + 0x2)) ||
	    (uVar1 != *(uint16_t*)((uint8_t*)pDynamicPath_00 + 0x6)))
	{
		iVar4 = (pDVar2->tCoords).nSubtileX;
		if (((int)uVar3 < iVar4) ||
		    ((((pDVar2->tCoords).nSubtileWidth + iVar4 <= (int)uVar3 ||
		          (iVar4 = (pDVar2->tCoords).nSubtileY, (int)uVar1 < iVar4)) ||
		        ((pDVar2->tCoords).nSubtileHeight + iVar4 <= (int)uVar1))))
		{
			ppDStack_10 = nullptr;
			uStack_14 = 0;
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar2, &ppDStack_10, (int*)&uStack_14);
			uStack_c = 0;
			if (uStack_14 == 0)
			{
				return;
			}
			while (((pDVar2 = ppDStack_10[uStack_c], pDVar2 == nullptr ||
			                                             (iVar4 = (pDVar2->tCoords).nSubtileX, (int)uVar3 < iVar4)) ||
			        (((pDVar2->tCoords).nSubtileWidth + iVar4 <= (int)uVar3 ||
			            ((iVar4 = (pDVar2->tCoords).nSubtileY, (int)uVar1 < iVar4 ||
			                                                       ((pDVar2->tCoords).nSubtileHeight + iVar4 <= (int)uVar1)))))))
			{
				uStack_c = uStack_c + 1;
				if (uStack_14 <= uStack_c)
				{
					return;
				}
			}
			pDVar2 = ppDStack_10[uStack_c];
		}
		if (pDVar2 == nullptr)
		{
			return;
		}
		D2Common_10231(pDynamicPath_00, in_ECX, pDStack_8, nX, nY);
	}
	*(uint32_t*)pDynamicPath_00 = *(uint32_t*)pDynamicPath;
	*(uint32_t*)((uint8_t*)pDynamicPath_00 + 0x4) = *(uint32_t*)((uint8_t*)pDynamicPath + 0x4);
	pDynamicPath_00->dwClientCoordX = pDynamicPath->dwClientCoordX;
	pDynamicPath_00->dwClientCoordY = pDynamicPath->dwClientCoordY;
	pDynamicPath_00->dwCurrentPointIdx = pDynamicPath->dwCurrentPointIdx;
	pDynamicPath_00->dwPathPoints = pDynamicPath->dwPathPoints;
	pDynamicPath_00->unk0x38 = pDynamicPath->unk0x38;
	(*(int32_t*)&pDynamicPath_00->tTargetCoord) = (*(int32_t*)&pDynamicPath->tTargetCoord);
	pDynamicPath_00->tPrevTargetCoord = pDynamicPath->tPrevTargetCoord;
	pDynamicPath_00->tFinalTargetCoord = pDynamicPath->tFinalTargetCoord;
	pDynamicPath_00->dwTargetType = pDynamicPath->dwTargetType;
	pDynamicPath_00->dwTargetId = pDynamicPath->dwTargetId;
	pDynamicPath_00->unk0x67 = pDynamicPath->unk0x67;
	pDynamicPath_00->dwSpeed = pDynamicPath->dwSpeed;
	pDynamicPath_00->dwVelocity = pDynamicPath->dwVelocity;
	pDynamicPath_00->nPreviousVelocity = pDynamicPath->nPreviousVelocity;
	pDynamicPath_00->dwMaxVelocity = pDynamicPath->dwMaxVelocity;
	pDynamicPath_00->dwAcceleration = pDynamicPath->dwAcceleration;
	pDynamicPath_00->dwAccelerationsCounter = pDynamicPath->dwAccelerationsCounter;
	pDynamicPath_00->nDistMax = pDynamicPath->nDistMax;
	pDynamicPath_00->nIDAStarInitFScore = pDynamicPath->nIDAStarInitFScore;
	pDynamicPath_00->nStepNum = pDynamicPath->nStepNum;
	pDynamicPath_00->nDistance = pDynamicPath->nDistance;
	pDynamicPath_00->nDirOffset = pDynamicPath->nDirOffset;
	(pDynamicPath_00->tDirectionVector).nX = (pDynamicPath->tDirectionVector).nX;
	(pDynamicPath_00->tDirectionVector).nY = (pDynamicPath->tDirectionVector).nY;
	iVar4 = pDynamicPath->dwPathPoints;
	if (iVar4 != 0)
	{
		pDVar5 = pDynamicPath->PathPoints;
		pDVar6 = pDynamicPath_00->PathPoints;
		for (; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*pDVar6 = *pDVar5;
			pDVar5 = pDVar5 + 1;
			pDVar6 = pDVar6 + 1;
		}
	}
	iVar4 = pDynamicPath->nSavedStepsCount;
	if (iVar4 != 0)
	{
		pDVar5 = pDynamicPath->SavedSteps;
		pDVar6 = pDynamicPath_00->SavedSteps;
		for (; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*pDVar6 = *pDVar5;
			pDVar5 = pDVar5 + 1;
			pDVar6 = pDVar6 + 1;
		}
	}
	pDynamicPath_00->nSavedStepsCount = pDynamicPath->nSavedStepsCount;
	uVar3 = pDynamicPath->dwPathType;
	if ((uVar3 != 8) && (uVar3 != 0xb))
	{
		pDynamicPath_00->dwPathType = uVar3;
	}
	uVar3 = pDynamicPath->dwPrevPathType;
	if ((uVar3 != 8) && (uVar3 != 0xb))
	{
		pDynamicPath_00->dwPrevPathType = uVar3;
	}
	pDynamicPath_00->dwPrevPathType = pDynamicPath->dwPrevPathType;
	pDynamicPath_00->dwUnitSize = pDynamicPath->dwUnitSize;
	iVar4 = D2COMMON_10209_PathCheckPathingFlag(pDynamicPath);
	D2COMMON_10208_PathSetPathingFlag(pDynamicPath_00, iVar4);
	pUnit = pDStack_4;
	uVar3 = in_ECX->dwAnimMode;
	uVar1 = pDStack_4->dwAnimMode;
	if (uVar3 == uVar1)
		goto switchD_6fb2a5de_caseD_12;
	if (in_ECX->dwUnitType == 0)
	{
		switch (uVar1)
		{
		case 1:
		case 5:
			if ((uVar3 < 2) || ((3 < uVar3 && (uVar3 != 6))))
				goto switchD_6fb2a5de_caseD_12;
			pDVar2 = UNITS_GetRoom(in_ECX);
			iVar4 = DUNGEON_IsRoomInTown(pDVar2);
			if (iVar4 == 0)
				goto LAB_6fb2a5c7;
			uVar1 = 5;
			break;
		case 2:
		case 6:
			if ((uVar3 != 1) && (uVar3 != 5))
				goto switchD_6fb2a5de_caseD_12;
			pDVar2 = UNITS_GetRoom(in_ECX);
			iVar4 = DUNGEON_IsRoomInTown(pDVar2);
			if (iVar4 == 0)
				goto LAB_6fb2a5b2;
			uVar1 = 6;
			break;
		case 3:
			if (((uVar3 != 1) && (uVar3 != 3)) && (uVar3 != 5))
				goto switchD_6fb2a5de_caseD_12;
			uVar1 = 3;
			break;
		default:
			if (uVar3 != 0x13)
			{
				pSkill = UNITS_GetUsedSkill(in_ECX);
				pSkill_00 = UNITS_GetUsedSkill(pUnit);
				if ((pSkill != nullptr) &&
				    ((((pSkill_00 == nullptr ||
				           (uVar3 = SKILLS_GetFlags(pSkill_00), (uVar3 & 1) == 0)) ||
				          (uVar3 = SKILLS_GetFlags(pSkill_00), (uVar3 & 2) != 0)) &&
				        (uVar3 = SKILLS_GetFlags(pSkill), (uVar3 & 1) != 0))))
				{
					SKILLS_SetFlags(pSkill, uVar3 | 2);
					D2COMMON_10212_PATH_SetMoveFlags(in_ECX, 0);
					return;
				}
				goto switchD_6fb2a5de_caseD_12;
			}
			break;
		case 0x12:
			goto switchD_6fb2a5de_caseD_12;
		}
	}
	else
	{
		if (in_ECX->dwUnitType != 1)
			goto switchD_6fb2a5de_caseD_12;
		if (uVar1 == 1)
		{
			if ((uVar3 != 2) && (uVar3 != 0xf))
				goto switchD_6fb2a5de_caseD_12;
		LAB_6fb2a5c7:
			uVar1 = 1;
		}
		else if (uVar1 == 2)
		{
			if (uVar3 != 1)
				goto switchD_6fb2a5de_caseD_12;
		LAB_6fb2a5b2:
			uVar1 = 2;
		}
		else
		{
			if ((uVar1 != 0xf) || (uVar3 != 1))
				goto switchD_6fb2a5de_caseD_12;
			uVar1 = 0xf;
		}
	}
	UNITS_ChangeAnimMode(in_ECX, uVar1);
switchD_6fb2a5de_caseD_12:
	D2COMMON_10212_PATH_SetMoveFlags(in_ECX, 0);
}

//D2Client.0x6FB2A6E0
uint16_t __fastcall sub_6FB2A6E0(int* a1)
{
	uint16_t uVar1;

	if ((a1 != nullptr) && (*a1 == 0))
	{
		uVar1 = sub_6FAAFDE0((int)a1);
		return uVar1;
	}
	return 0xffff;
}

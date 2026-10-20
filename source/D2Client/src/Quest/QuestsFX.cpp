#include "Quest/QuestsFX.h"
#include "Quest/Quests.h"

#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Game.h"
#include "Skills/Skills.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/Monster.h"

//D2Client.0x6FB773A8
uint32_t dword_6FB773A8 = 0xFFFFFFFF;
//D2Client.0x6FB773AC
int32_t dword_6FB773AC = -1;
//D2Client.0x6FB773B0
uint32_t dword_6FB773B0 = 0xFFFFFFFF;
//D2Client.0x6FB773B8
uint8_t* ptr_6FB773B8 = (uint8_t*)sub_6FAB9140;
//D2Client.0x6FB77407
uint32_t dword_6FB77407 = 0x61466E6F;
//D2Client.0x6FBAF948
uint32_t dword_6FBAF948;
//D2Client.0x6FBAF94C
uint32_t dword_6FBAF94C;
//D2Client.0x6FBAF950
uint8_t byte_6FBAF950;
//D2Client.0x6FBAF951
uint8_t byte_6FBAF951;
//D2Client.0x6FBAF952
uint8_t byte_6FBAF952;
//D2Client.0x6FBAF954
int32_t dword_6FBAF954;
//D2Client.0x6FBAF958
int32_t dword_6FBAF958;
//D2Client.0x6FBAF95C
uint8_t byte_6FBAF95C;
//D2Client.0x6FBAF960
int32_t dword_6FBAF960;
//D2Client.0x6FBAF964
int32_t dword_6FBAF964;
//D2Client.0x6FBAF968
int32_t dword_6FBAF968;
//D2Client.0x6FBAF96C
uint32_t dword_6FBAF96C;
//D2Client.0x6FBAF970
int32_t dword_6FBAF970;
//D2Client.0x6FBAF974
uint32_t dword_6FBAF974;
//D2Client.0x6FBAF978
int32_t dword_6FBAF978;
//D2Client.0x6FBAF97C
int32_t dword_6FBAF97C;
//D2Client.0x6FBAF980
int32_t dword_6FBAF980;
//D2Client.0x6FBAF984
int32_t dword_6FBAF984;
//D2Client.0x6FBAF988
int32_t dword_6FBAF988;
//D2Client.0x6FBAF98C
uint32_t dword_6FBAF98C;

//D2Client.0x6FAB8F70
void __fastcall sub_6FAB8F70(int a1, int a2, int a3, uint32_t a4, int a5)
{
	int iVar1;
	uint32_t* puVar2;

	if ((dword_6FBAF970 == 0) || (a5 != 0))
	{
		puVar2 = &dword_6FBAF948;
		for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar2 = 0;
			puVar2 = puVar2 + 1;
		}
		dword_6FBAF948 = 1;
		D2_ASSERT(a1);
		if (a3 == 0)
		{
			a3 = 0x19;
		}
		dword_6FBAF960 = a1 + a2 + a3;
		dword_6FBAF96C = a4;
		dword_6FBAF954 = a1;
		dword_6FBAF958 = a3;
		byte_6FBAF95C = a2;
	}
}

//D2Client.0x6FAB9000
void __cdecl sub_6FAB9000()
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;
	int iVar6;
	uint32_t* puVar7;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x11);
			if (pDVar3 != nullptr)
			{
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
				sub_6FB3EAF0((int)pUnit, 0x120, iVar4, (D2UnitStrc**)DVar5, 0, 1);
				if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) < 0x121)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + 0x1d880;
				}
				iVar2 = *(int*)(iVar4 + 0x38);
				iVar6 = (int)*(short*)(iVar4 + 0x96) + iVar2 * -2;
				puVar7 = &dword_6FBAF948;
				for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				dword_6FBAF948 = 1;
				D2_ASSERT(iVar2);
				dword_6FBAF958 = iVar2;
				if (iVar2 == 0)
				{
					dword_6FBAF958 = 0x19;
				}
				dword_6FBAF960 = iVar2 + dword_6FBAF958 + iVar6;
				dword_6FBAF96C = 4;
				dword_6FBAF954 = iVar2;
				byte_6FBAF95C = iVar6;
			}
		}
	}
}

//D2Client.0x6FAB9140
void __cdecl sub_6FAB9140()
{
	dword_6FB773A8 = 0;
}

//D2Client.0x6FAB9150
void __cdecl sub_6FAB9150()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar2);
		if (pRoom != nullptr)
		{
			pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x98);
			if (pDVar3 != nullptr)
			{
				sub_6FB57030(0x1252, 0, 0x2d5, 1, 0, 0, 0);
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
				pDVar2 = sub_6FB3EAF0((int)pDVar2, 0x152, iVar4, (D2UnitStrc**)DVar5, 0, 1);
				if (pDVar2 != nullptr)
				{
					sub_6FB5FC80((int)pDVar2, 0, 0, 0x28);
					sub_6FB5FCB0((int)pDVar2, 0, 0, 0x200, 0);
					sub_6FB5FD50((int)pDVar2, 0, 0, 0x46, 0);
					sub_6FB60180((int)pDVar2, 1);
				}
				sub_6FB5BA70(pDVar3, 0xb5, 2, 0, 0, 0, 0, 0);
				sub_6FB5CC40(0xd3, 1);
				return;
			}
		}
	}
}

//D2Client.0x6FAB9280
void __cdecl sub_6FAB9280()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int iVar5;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar2);
		pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x95);
		if (pDVar3 != nullptr)
		{
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar4 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iVar5 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iVar5 = 0;
			}
			else
			{
				iVar5 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			pDVar2 = sub_6FB3EAF0((int)pDVar2, 0x15e, iVar5, (D2UnitStrc**)DVar4, 0, 1);
			if (pDVar2 != nullptr)
			{
				MISSILE_SetTargetY(pDVar2, pDVar3->dwUnitId);
			}
		}
	}
}

//D2Client.0x6FAB9330
void __cdecl sub_6FAB9330()
{
	uint32_t uVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar2;
	int32_t DVar3;

	dword_6FBAF97C = 1;
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pRoom);
			if (iVar2 == 0x6c)
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar2 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar2 = 0;
				}
				else
				{
					iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
				}
				else
				{
					DVar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				sub_6FB3EAF0((int)pUnit, 0x174, iVar2, (D2UnitStrc**)DVar3, 0, 1);
				sub_6FB5CC40(0xf3, 1);
				return;
			}
		}
	}
}

//D2Client.0x6FAB93E0
void __cdecl sub_6FAB93E0()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar2);
		if (pRoom != nullptr)
		{
			pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x178);
			if (pDVar3 != nullptr)
			{
				sub_6FB57030(0x1251, 0, 0x15e, 0, 0, 0, 0);
				sub_6FB55820(0x23, pDVar3, 0.0, 0.0, 0);
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
				pDVar2 = sub_6FB3EAF0((int)pDVar2, 0x175, iVar4, (D2UnitStrc**)DVar5, 0, 1);
				if (pDVar2 != nullptr)
				{
					MISSILE_SetTargetX(pDVar2, pDVar3->dwUnitId);
					MISSILE_SetTargetY(pDVar2, 0);
				}
			}
		}
	}
}

//D2Client.0x6FAB94D0
void __cdecl sub_6FAB94D0()
{
	int iVar1;

	iVar1 = FOG_10055_GetSyncTime();
	dword_6FB773AC = 0;
	dword_6FBAF980 = iVar1 + 0x5a;
}

//D2Client.0x6FAB94F0
void __fastcall sub_6FAB94F0(int* a1)
{
	D2UnitStrc** ppDVar1;
	int iVar2;
	D2UnitStrc* pMissile;

	if (a1 != nullptr)
	{
		iVar2 = *a1;
		if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
		{
			ppDVar1 = *(D2UnitStrc***)(a1[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
		{
			ppDVar1 = nullptr;
		}
		else
		{
			ppDVar1 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
		}
		iVar2 = *a1;
		if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
		{
			iVar2 = *(int*)(a1[0xb] + 0xc);
		}
		else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
		}
		pMissile = sub_6FB3EAF0((int)a1, 0x25a, iVar2, ppDVar1, 0, 1);
		if (pMissile != nullptr)
		{
			MISSILE_SetTargetX(pMissile, 0x19);
		}
	}
}

//D2Client.0x6FAB9570
void __cdecl sub_6FAB9570()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int32_t DVar4;
	int iVar5;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pRoom = UNITS_GetRoom(pDVar2);
		if (pRoom != nullptr)
		{
			pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x1cc);
			if (pDVar3 != nullptr)
			{
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar4 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
				}
				else
				{
					DVar4 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar5 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar5 = 0;
				}
				else
				{
					iVar5 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				pDVar2 = sub_6FB3EAF0((int)pDVar2, 0x210, iVar5, (D2UnitStrc**)DVar4, 0, 1);
				if (pDVar2 != nullptr)
				{
					MISSILE_SetTargetX(pDVar2, 0x19);
				}
			}
		}
	}
}

//D2Client.0x6FAB9620
void __cdecl sub_6FAB9620()
{
	uint32_t uVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar2;
	int iVar3;
	int32_t DVar4;

	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 1, 0x20e);
			if (pDVar2 != nullptr)
			{
				uVar1 = pDVar2->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar3 = pDVar2->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar2->pDynamicPath == nullptr)
				{
					iVar3 = 0;
				}
				else
				{
					iVar3 = PATH_GetXPosition(pDVar2->pDynamicPath);
				}
				uVar1 = pDVar2->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar4 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
				}
				else if (pDVar2->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
				}
				else
				{
					DVar4 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
				}
				sub_6FB3EAF0((int)pUnit, 0x25e, iVar3, (D2UnitStrc**)DVar4, 0, 1);
				sub_6FB3EAF0((int)pUnit, 0x25b, iVar3, (D2UnitStrc**)DVar4, 0, 1);
				pDVar2->dwFlagEx = pDVar2->dwFlagEx | 0x40000;
			}
		}
	}
}

//D2Client.0x6FAB96F0
void __cdecl sub_6FAB96F0()
{
	dword_6FBAF984 = 1;
}

//D2Client.0x6FAB9700
void __fastcall sub_6FAB9700(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pMissile;
	uint32_t* puVar4;
	int nUnitType;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	uint32_t uStack_2c;

	if (pUnit != nullptr)
	{
		iVar2 = pUnit->dwClassId;
		if (iVar2 == 0x21c)
		{
			iVar2 = 0x1db;
		}
		else if (iVar2 == 0x21d)
		{
			iVar2 = 0x1dc;
		}
		else
		{
			if (iVar2 != 0x21e)
			{
				return;
			}
			iVar2 = 0x1da;
		}
		nUnitType = 2;
		pRoom = UNITS_GetRoom(pUnit);
		pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, nUnitType, iVar2);
		if (pDVar3 != nullptr)
		{
			puVar4 = &uStack_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			uStack_5c = 0x420;
			uStack_4c = 0x21d;
			uVar1 = pDVar3->dwUnitType;
			pDStack_58 = pUnit;
			pDStack_54 = pUnit;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iStack_40 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iStack_40 = 0;
			}
			else
			{
				iStack_40 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar1 = pDVar3->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DStack_3c = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
			}
			else
			{
				DStack_3c = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			uStack_2c = 1;
			pMissile = sub_6FB3E070(&uStack_5c);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, pDVar3->dwUnitId);
			}
		}
	}
}

//D2Client.0x6FAB9800
void __fastcall sub_6FAB9800(int a1)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;
	int iVar6;
	uint32_t* puVar7;

	D2_ASSERT(0x1f >= a1);
	D2_ASSERT(0x13 >= a1);
	dword_6FBAF974 = dword_6FBAF974 | 1 << ((uint8_t)a1 & 0x1f);
	if ((&ptr_6FB773B8)[a1] == nullptr)
	{
		return;
	}
	/* WARNING (jumptable): Sanity check requires truncation of jumptable */
	switch (a1)
	{
	case 0:
		dword_6FB773A8 = 0;
		return;
	}
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		pRoom = UNITS_GetRoom(pUnit);
		if (pRoom != nullptr)
		{
			pDVar3 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, 2, 0x11);
			if (pDVar3 != nullptr)
			{
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
				}
				uVar1 = pDVar3->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
				}
				else if (pDVar3->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
				}
				sub_6FB3EAF0((int)pUnit, 0x120, iVar4, (D2UnitStrc**)DVar5, 0, 1);
				if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) < 0x121)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + 0x1d880;
				}
				iVar2 = *(int*)(iVar4 + 0x38);
				iVar6 = (int)*(short*)(iVar4 + 0x96) + iVar2 * -2;
				puVar7 = &dword_6FBAF948;
				for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				dword_6FBAF948 = 1;
				D2_ASSERT(iVar2);
				dword_6FBAF958 = iVar2;
				if (iVar2 == 0)
				{
					dword_6FBAF958 = 0x19;
				}
				dword_6FBAF960 = iVar2 + dword_6FBAF958 + iVar6;
				dword_6FBAF96C = 4;
				dword_6FBAF954 = iVar2;
				byte_6FBAF95C = iVar6;
			}
		}
	}
}

//D2Client.0x6FAB9870
void __cdecl sub_6FAB9870()
{
	D2UnitStrc* pMissile;
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_5c[4];
	uint32_t local_4c;
	uint32_t local_2c;

	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_4c = 0x11c;
	local_2c = 1;
	pMissile = sub_6FB3E070(local_5c);
	if (pMissile != nullptr)
	{
		MISSILE_SetTargetX(pMissile, 0x32);
	}
	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_4c = 0x128;
	local_2c = 1;
	sub_6FB3E070(local_5c);
	local_4c = 0x125;
	sub_6FB3E070(local_5c);
}

//D2Client.0x6FAB9900
void __fastcall sub_6FAB9900(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar2;
	int32_t DVar3;
	int32_t DVar4;
	uint32_t* puVar5;
	int iVar6;
	int iVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	uint32_t uStack_2c;

	iVar7 = 0x173;
	iVar6 = 2;
	pRoom = UNITS_GetRoom(pUnit);
	pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, iVar6, iVar7);
	if (pDVar2 == nullptr)
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iVar6 = iVar6 + -0xf;
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
		}
		else
		{
			DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DVar3 = (int32_t)((int)DVar4 + -0xf);
	}
	else
	{
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar6 = pDVar2->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar3 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
		}
		else
		{
			DVar3 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
	}
	puVar5 = &uStack_5c;
	for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	uStack_5c = 0x420;
	uStack_4c = 0x123;
	uStack_2c = 1;
	pDStack_58 = pUnit;
	pDStack_54 = pUnit;
	iStack_40 = iVar6;
	DStack_3c = DVar3;
	sub_6FB3E070(&uStack_5c);
	pDVar2 = sub_6FB3EAF0((int)pUnit, 0x14c, iVar6, (D2UnitStrc**)DVar3, 0, 1);
	if (pDVar2 != nullptr)
	{
		MISSILE_SetTargetY(pDVar2, 0);
	}
}

//D2Client.0x6FAB9A40
void __fastcall sub_6FAB9A40(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar2;
	int32_t DVar3;
	int32_t DVar4;
	D2UnitStrc* pMissile;
	uint32_t* puVar5;
	int iVar6;
	int iVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	uint32_t uStack_2c;

	iVar7 = 0x182;
	iVar6 = 2;
	pRoom = UNITS_GetRoom(pUnit);
	pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, iVar6, iVar7);
	if (pDVar2 == nullptr)
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iVar6 = iVar6 + -0xf;
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
		}
		else
		{
			DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DVar3 = (int32_t)((int)DVar4 + -0xf);
	}
	else
	{
		sub_6FB57030(0x124f, 0, 0x15e, 0, 0, 0, 0);
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar6 = pDVar2->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar3 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
		}
		else
		{
			DVar3 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
	}
	puVar5 = &uStack_5c;
	for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
	uStack_5c = 0x420;
	uStack_4c = 0x170;
	uStack_2c = 1;
	pDStack_58 = pUnit;
	pDStack_54 = pUnit;
	iStack_40 = iVar6;
	DStack_3c = DVar3;
	pMissile = sub_6FB3E070(&uStack_5c);
	if ((pMissile != nullptr) && (pDVar2 != nullptr))
	{
		MISSILE_SetTargetX(pMissile, pDVar2->dwUnitId);
	}
}

//D2Client.0x6FAB9B90
void __cdecl sub_6FAB9B90()
{
	D2UnitStrc* pMissile;
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_5c[4];
	uint32_t local_4c;
	uint32_t local_2c;

	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_4c = 299;
	local_2c = 1;
	pMissile = sub_6FB3E070(local_5c);
	if (pMissile != nullptr)
	{
		MISSILE_SetTargetX(pMissile, 0x4b);
		MISSILE_SetTargetY(pMissile, 0x4b);
	}
	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_2c = 1;
	local_4c = 0x166;
	sub_6FB3E070(local_5c);
	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_4c = 0x132;
	local_2c = 1;
	sub_6FB3E070(local_5c);
}

//D2Client.0x6FAB9C40
void __cdecl sub_6FAB9C40()
{
	uint32_t* puVar1;
	int iVar2;
	uint32_t local_5c[4];
	uint32_t local_4c;
	uint32_t local_2c;

	puVar1 = local_5c;
	for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar1 = 0;
		puVar1 = puVar1 + 1;
	}
	local_4c = 0x133;
	local_2c = 1;
	sub_6FB3E070(local_5c);
}

//D2Client.0x6FAB9C80
void __fastcall sub_6FAB9C80(int* a1)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc** ppDVar2;
	int iVar3;

	pDVar1 = CUNIT_GetPlayer();
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		ppDVar2 = *(D2UnitStrc***)(a1[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		ppDVar2 = nullptr;
	}
	else
	{
		ppDVar2 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		iVar3 = *(int*)(a1[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	sub_6FB3EAF0((int)pDVar1, 0x15b, iVar3, ppDVar2, 0, 1);
}

//D2Client.0x6FAB9D00
void __fastcall sub_6FAB9D00(int* a1)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc** ppDVar2;
	int iVar3;

	pDVar1 = CUNIT_GetPlayer();
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		ppDVar2 = *(D2UnitStrc***)(a1[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		ppDVar2 = nullptr;
	}
	else
	{
		ppDVar2 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		iVar3 = *(int*)(a1[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	sub_6FB3EAF0((int)pDVar1, 0x161, iVar3, ppDVar2, 0, 1);
}

//D2Client.0x6FAB9D80
void __fastcall sub_6FAB9D80(int* a1)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc** ppDVar2;
	int iVar3;

	pDVar1 = CUNIT_GetPlayer();
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		ppDVar2 = *(D2UnitStrc***)(a1[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		ppDVar2 = nullptr;
	}
	else
	{
		ppDVar2 = (D2UnitStrc**)PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	iVar3 = *a1;
	if ((iVar3 == 2) || ((3 < iVar3 && (iVar3 < 6))))
	{
		iVar3 = *(int*)(a1[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
	}
	sub_6FB3EAF0((int)pDVar1, 0x16b, iVar3, ppDVar2, 0, 1);
}

//D2Client.0x6FAB9E00
void __cdecl sub_6FAB9E00()
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t local_5c[4];
	uint32_t local_4c;
	uint32_t local_2c;

	sub_6FB57030(0x1253, 0, 0xfa, 0, 0, 0, 0);
	puVar2 = local_5c;
	for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	local_4c = 0x17b;
	local_2c = 1;
	sub_6FB3E070(local_5c);
}

//D2Client.0x6FAB9E60
void __fastcall sub_6FAB9E60(int a1)
{
	if (a1 == 0)
	{
		dword_6FB773B0 = 0xffffffff;
		return;
	}
	dword_6FB773B0 = *(uint32_t*)(a1 + 0xc);
}

//D2Client.0x6FAB9E80
void __cdecl sub_6FAB9E80()
{
	uint32_t uVar1;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pDVar2;
	int32_t DVar3;
	int iVar4;
	int nClassId;

	pUnit = CUNIT_GetPlayer();
	nClassId = 0x220;
	iVar4 = 1;
	pRoom = UNITS_GetRoom(pUnit);
	pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, iVar4, nClassId);
	if (pDVar2 != nullptr)
	{
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar3 = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
		}
		else
		{
			DVar3 = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pDVar2->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pDVar2->pDynamicPath);
		}
		sub_6FB3EAF0((int)pUnit, 0x271, iVar4, (D2UnitStrc**)DVar3, 0, 1);
	}
}

//D2Client.0x6FAB9F10
void __fastcall sub_6FAB9F10(D2UnitStrc* pUnit)
{
	D2ActiveRoomStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int nClassId;

	nClassId = 0x271;
	iVar3 = 3;
	pDVar1 = UNITS_GetRoom(pUnit);
	pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pDVar1, iVar3, nClassId);
	if (pDVar2 != nullptr)
	{
		sub_6FB5FB10((int)pUnit);
		sub_6FB5FC80((int)pUnit, 0, 0, 300);
		sub_6FB5FCB0((int)pUnit, 0, 0, -2, 1);
		sub_6FB5FD50((int)pUnit, 0, 0, 5, 0);
		sub_6FB60180((int)pUnit, 0);
		MISSILE_SetTargetY(pDVar2, 1);
		pDVar1 = CUNIT_GetPlayerRoom();
		if (pDVar1 != nullptr)
		{
			iVar3 = DUNGEON_GetLevelIdFromRoom(pDVar1);
			if ((iVar3 < 0x83) || (0x84 < iVar3))
			{
				dword_6FBAF988 = 0;
			}
			else if ((dword_6FBAF988 == 0) && (dword_6FBAF984 != 0))
			{
				pDVar2 = CUNIT_GetPlayer();
				if (pDVar2 != nullptr)
				{
					sub_6FABABC0(pDVar2, 0x27f, 0, 1);
					dword_6FBAF988 = 1;
					return;
				}
			}
		}
	}
}

//D2Client.0x6FAB9FE0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAB9FE0(D2ActiveRoomStrc* pActiveRoom, uint8_t* a2, uint8_t* a3, uint8_t* a4)
{
	uint8_t uVar1;
	int iVar2;
	uint32_t extraout_var;
	int64_t lVar3;
	float fVar4;

	iVar2 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
	if (iVar2 == 8)
	{
		if (dword_6FBAF978 == 0)
		{
			uVar1 = D2Client_10002(0, 1);
			if (D2C_ZEXT(uVar1) != 0)
			{
				*a2 = 0xff;
				*a3 = 0x40;
				*a4 = 0x30;
				if (dword_6FB773A8 == -1)
				{
					return 0x50;
				}
				fVar4 = FOG_10083_Cos_LUT((short)((dword_6FB773A8 * 0x80) / 0x1e));
				lVar3 = (int64_t)((double)fVar4 * (double)80.0);
				return (int)lVar3;
			}
		}
	}
	else
	{
		if ((iVar2 < 0x6b) || (0x6c < iVar2))
		{
			*a2 = byte_6FBAF950;
			*a3 = byte_6FBAF951;
			*a4 = byte_6FBAF952;
			return dword_6FBAF94C;
		}
		if ((dword_6FBAF97C != 0) && (dword_6FB773AC == -1))
		{
			*a2 = 0xff;
			*a3 = 0x40;
			*a4 = 0x30;
			return 0xa0;
		}
	}
	return 0;
}

//D2Client.0x6FABA0D0
void __fastcall sub_6FABA0D0(D2ActiveRoomStrc* hRoom)
{
	int iVar1;

	D2_ASSERT(hRoom != nullptr);
	iVar1 = DUNGEON_GetLevelIdFromRoom(hRoom);
	if ((iVar1 == 8) && (dword_6FBAF978 != 0))
	{
		sub_6FABA120(hRoom);
		return;
	}
}

//D2Client.0x6FABA120
void __fastcall sub_6FABA120(D2ActiveRoomStrc* pActiveRoom)
{
	uint64_t DVar1;
	uint64_t uVar2;
	uint16_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	int iStack_88;
	int iStack_84;
	D2DrlgCoordsStrc local_7c;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	uint32_t local_4c;
	int iStack_48;
	int iStack_44;
	uint32_t local_30;
	uint32_t local_2c;

	pDVar4 = CUNIT_GetPlayer();
	if (pDVar4 != nullptr)
	{
		puVar7 = &local_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		local_5c = 0x2003;
		local_30 = 0;
		local_2c = 1;
		local_4c = 0x11f;
		local_58 = pDVar4;
		DUNGEON_GetRoomCoordinates(pActiveRoom, &local_7c);
		iStack_88 = 0;
		iStack_84 = 0;
		do
		{
			if (0x18 < iStack_84)
			{
				return;
			}
			if (local_7c.nSubtileWidth < 1)
			{
				uVar6 = 0;
			}
			else
			{
				uVar6 = (pDVar4->pSeed).nLowSeed;
				uVar2 = (uint64_t)(pDVar4->pSeed).nHighSeed;
				if ((local_7c.nSubtileWidth & local_7c.nSubtileWidth - 1U) == 0)
				{
					DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pDVar4->pSeed) = DVar1;
					uVar6 = local_7c.nSubtileWidth - 1U & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pDVar4->pSeed) = DVar1;
					uVar6 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)(uint32_t)local_7c.nSubtileWidth);
				}
			}
			iStack_48 = uVar6 + local_7c.nSubtileX;
			if (local_7c.nSubtileHeight < 1)
			{
				uVar6 = 0;
			}
			else
			{
				uVar6 = (pDVar4->pSeed).nLowSeed;
				uVar2 = (uint64_t)(pDVar4->pSeed).nHighSeed;
				if ((local_7c.nSubtileHeight & local_7c.nSubtileHeight - 1U) == 0)
				{
					DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pDVar4->pSeed) = DVar1;
					uVar6 = local_7c.nSubtileHeight - 1U & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar2);
					(*(uint64_t*)&pDVar4->pSeed) = DVar1;
					uVar6 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)(uint32_t)local_7c.nSubtileHeight);
				}
			}
			iStack_44 = local_7c.nSubtileY + uVar6;
			uVar3 = COLLISION_CheckMask(pActiveRoom, iStack_48, iStack_44, 5);
			if (uVar3 == 0)
			{
				sub_6FB3E070(&local_5c);
			}
			else
			{
				iStack_88 = iStack_88 + -1;
			}
			iStack_88 = iStack_88 + 1;
			iStack_84 = iStack_84 + 1;
		} while (iStack_88 < 3);
	}
}

//D2Client.0x6FABA270
void __cdecl sub_6FABA270()
{
	D2ActiveRoomStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	int64_t lVar4;
	float fVar5;
	uint8_t* puVar6;
	uint8_t* puVar7;
	uint8_t* puVar8;
	uint32_t uVar9;
	uint32_t local_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	if (dword_6FBAF948 != 0)
	{
		uVar9 = 0;
		puVar8 = &byte_6FBAF952;
		puVar7 = &byte_6FBAF951;
		puVar6 = &byte_6FBAF950;
		local_c = 0;
		pDVar1 = CUNIT_GetPlayerRoom();
		sub_6FAA45C0(pDVar1, &local_c, puVar6, puVar7, puVar8, uVar9);
		if (dword_6FBAF964 < dword_6FBAF954)
		{
			fVar5 = FOG_10083_Cos_LUT((short)dword_6FBAF968);
			uStack_4 = 0;
			uStack_8 = local_c;
			lVar4 = (int64_t)((double)fVar5 * (double)(int)local_c);
			dword_6FBAF94C = (uint32_t)lVar4;
			dword_6FBAF968 = (dword_6FBAF964 << 7) / dword_6FBAF954;
		}
		else if (dword_6FBAF964 < dword_6FBAF960 - dword_6FBAF958)
		{
			dword_6FBAF94C = 0;
		}
		else
		{
			fVar5 = FOG_10083_Cos_LUT((short)dword_6FBAF968);
			uStack_4 = 0;
			uStack_8 = local_c;
			lVar4 = (int64_t)((double)fVar5 * (double)(int)local_c);
			dword_6FBAF94C = (uint32_t)lVar4;
			iVar2 = dword_6FBAF958 - dword_6FBAF960;
			if (dword_6FBAF958 == 0)
			{
				dword_6FBAF958 = 0x19;
			}
			dword_6FBAF968 = 0x80 - ((iVar2 + dword_6FBAF964) * 0x80) / dword_6FBAF958;
		}
		dword_6FBAF964 = dword_6FBAF964 + 1;
		pDVar1 = CUNIT_GetPlayerRoom();
		iVar2 = 0;
		if (pDVar1 != nullptr)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pDVar1);
		}
		if ((dword_6FBAF960 < dword_6FBAF964) || (iVar2 != dword_6FBAF96C))
		{
			puVar3 = &dword_6FBAF948;
			for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar3 = 0;
				puVar3 = puVar3 + 1;
			}
		}
	}
	if (((dword_6FBAF978 == 0) && (dword_6FB773A8 != -1)) &&
	    (dword_6FB773A8 = dword_6FB773A8 + 1, 0x1d < dword_6FB773A8))
	{
		dword_6FBAF978 = 1;
		for (pDVar1 = DUNGEON_GetRoomFromAct(ghAct); pDVar1 != nullptr;
		     pDVar1 = pDVar1->pRoomNext)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pDVar1);
			if (iVar2 == 8)
			{
				sub_6FABA120(pDVar1);
			}
		}
	}
	if (((dword_6FBAF97C != 0) && (dword_6FB773AC != -1)) &&
	    (dword_6FB773AC = dword_6FB773AC + 1, 0x1d < dword_6FB773AC))
	{
		dword_6FBAF97C = 0;
		dword_6FB773AC = -1;
	}
}

//D2Client.0x6FABA440
void __fastcall sub_6FABA440(D2ActiveRoomStrc* pActiveRoom)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	if (pActiveRoom != nullptr)
	{
		iVar1 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
		if ((iVar1 < 0x83) || (0x84 < iVar1))
		{
			dword_6FBAF988 = 0;
		}
		else if ((dword_6FBAF988 == 0) && (dword_6FBAF984 != 0))
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				sub_6FABABC0(pDVar2, 0x27f, 0, 1);
				dword_6FBAF988 = 1;
				return;
			}
		}
	}
}

//D2Client.0x6FABA4A0
void __cdecl sub_6FABA4A0()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	Unicode* pUVar3;
	Font nFontSize;
	int iVar4;
	Unicode aUStack_200[256];

	iVar1 = FOG_10055_GetSyncTime();
	if ((dword_6FBAF980 != 0) && (iVar1 < dword_6FBAF980))
	{
		pDVar2 = sub_6FB269F0(dword_6FB773B0, 1);
		if ((pDVar2 == nullptr) ||
		    ((pDVar2->dwAnimMode == 0xc || (dword_6FBAF980 + -0x46 <= iVar1))))
		{
			iVar1 = dword_6FBAF980 - iVar1;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13e9));
			Unicode::sprintf(0x100, aUStack_200, pUVar3, iVar1);
			nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
			iVar1 = D2Win_10121_GetTextWidth(aUStack_200);
			D2Win_10117_DrawText(aUStack_200, gnScreenWidth / 2 - iVar1 / 2, 0x177, 9, 1);
			D2Win_10127_SetFont(nFontSize);
		}
	}
}

//D2Client.0x6FABA580
void __cdecl sub_6FABA580()
{
	int iVar1;
	uint32_t* puVar2;

	dword_6FB773A8 = 0xffffffff;
	dword_6FB773B0 = 0xffffffff;
	dword_6FBAF978 = 0;
	puVar2 = &dword_6FBAF948;
	for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	dword_6FBAF97C = 0;
	dword_6FBAF980 = 0;
	dword_6FBAF984 = 0;
}

//D2Client.0x6FABA5C0
void __fastcall sub_6FABA5C0(int a1)
{
	int iVar1;

	if ((0 < a1) && (dword_6FBAF980 == 0))
	{
		iVar1 = FOG_10055_GetSyncTime();
		dword_6FBAF980 = iVar1 + a1;
	}
}

//D2Client.0x6FABA5E0
uint32_t __fastcall sub_6FABA5E0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t uVar1;

	uVar1 = sub_6FAABF80();
	if (dword_6FBAF98C < uVar1)
	{
		dword_6FBAF98C = uVar1 + 5;
		sub_6FB42A70(pUnit, 1, 0);
	}
	return 1;
}

//D2Client.0x6FABA610
uint32_t __fastcall sub_6FABA610(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, D2UnitStrc* pUnit2, int a5, int a6, uint32_t a7)
{
	int iVar1;
	short sVar2;
	uint32_t uVar3;
	bool bVar4;
	D2UnitStrc* pTargetUnit;
	int nX;
	int nY;
	int iVar5;
	uint32_t uVar6;

	if ((((int)a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= (int)a2)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + a2 * 0x23c, iVar1 == 0))
	{
		return 0;
	}
	pTargetUnit = sub_6FB296A0((int)pUnit);
	nX = D2COMMON_10175_PathGetFirstPointX(pUnit->pDynamicPath);
	nY = D2COMMON_10176_PathGetFirstPointY(pUnit->pDynamicPath);
	uVar3 = pUnit->dwFlags;
	if (pUnit2 == nullptr)
	{
		D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, a5, a6);
	}
	else
	{
		UNITS_SetTargetUnitForDynamicUnit(pUnit, pUnit2);
	}
	if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar1 + 8)) != 0)
	{
		bVar4 = false;
		if (((pUnit2 != nullptr) && (iVar5 = sub_6FB29550((int*)pUnit2), iVar5 != 0)) &&
		    (iVar5 = STATES_CheckState(pUnit2, 0x76), iVar5 != 0))
		{
			bVar4 = true;
			STATES_ToggleState(pUnit2, 0x76, 0);
		}
		iVar5 = sub_6FABBEB0(pUnit, a2, a3, (int*)0xffffffff);
		if (iVar5 == 0)
		{
			uVar6 = 0;
			goto LAB_6faba794;
		}
		if (bVar4)
		{
			STATES_ToggleState(pUnit2, 0x76, 1);
		}
	}
	if (-1 < *(short*)(iVar1 + 0x122))
	{
		sub_6FB55820((int)*(short*)(iVar1 + 0x122), pUnit, 0.0, 0.0, 0);
	}
	sVar2 = *(short*)(iVar1 + 0x124);
	if ((-1 < sVar2) && ((int)sVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc0)))
	{
		sub_6FB5BA70(pUnit, (int)sVar2, 2, 0, 0, 0, 0, 0);
	}
	uVar6 = sub_6FABC6B0(pUnit, a2, a3, a7 & 0xffff);
LAB_6faba794:
	if (pTargetUnit == nullptr)
	{
		D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, nX, nY);
	}
	else
	{
		UNITS_SetTargetUnitForDynamicUnit(pUnit, pTargetUnit);
	}
	if ((uVar3 >> 6 & 1) == 0)
	{
		pUnit->dwFlags = pUnit->dwFlags & 0xffffffbf;
		return uVar6;
	}
	pUnit->dwFlags = pUnit->dwFlags | 0x40;
	return uVar6;
}

//D2Client.0x6FABA7F0
uint32_t __fastcall sub_6FABA7F0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int a4, uint32_t a5)
{
	uint32_t uVar1;

	if ((pUnit != nullptr) && (a4 != 0))
	{
		uVar1 = sub_6FABA610(pUnit, a2, a3, (D2UnitStrc*)(a4), 0, 0, a5);
		return uVar1;
	}
	return 0;
}

//D2Client.0x6FABA820
uint32_t __fastcall sub_6FABA820(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, int a4, int a5, uint32_t a6)
{
	uint32_t uVar1;

	if (((pUnit != nullptr) && (a4 != 0)) && (a5 != 0))
	{
		uVar1 = sub_6FABA610(pUnit, a2, a3, 0, a4, a5, a6);
		return uVar1;
	}
	return 0;
}

//D2Client.0x6FABA860
void __fastcall sub_6FABA860(D2UnitStrc* pUnit, int* a2, int* a3)
{
	uint32_t uVar1;
	uint8_t bVar2;
	int iVar3;
	int32_t DVar4;
	int aiStack_40[16];

	bVar2 = UNITS_GetDirection(pUnit);
	aiStack_40[5] = 1;
	aiStack_40[7] = 1;
	aiStack_40[9] = 1;
	aiStack_40[0xf] = 1;
	uVar1 = pUnit->dwUnitType;
	aiStack_40[0] = 0;
	aiStack_40[1] = 0xffffffff;
	aiStack_40[2] = 0xfffffffe;
	aiStack_40[3] = 0xffffffff;
	aiStack_40[4] = 0;
	aiStack_40[6] = 2;
	aiStack_40[8] = 2;
	aiStack_40[10] = 0;
	aiStack_40[0xb] = 0xffffffff;
	aiStack_40[0xc] = 0xfffffffe;
	aiStack_40[0xd] = 0xffffffff;
	aiStack_40[0xe] = 0;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar3 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	*a2 = aiStack_40[bVar2 >> 3] + iVar3;
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	}
	else
	{
		DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	*a3 = aiStack_40[(bVar2 >> 3) + 8] + (int)DVar4;
}

//D2Client.0x6FABA950
uint32_t __fastcall sub_6FABA950(D2UnitStrc* pUnit, int* a2, int* a3)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	int aiStack_40[16];

	pDVar3 = sub_6FB296A0((int)pUnit);
	if (pDVar3 == nullptr)
	{
		pDynamicPath = pUnit->pDynamicPath;
		iVar4 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		*a2 = iVar4;
		iVar4 = D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
		*a3 = iVar4;
	}
	else
	{
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
		}
		*a2 = iVar4;
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			*a3 = (int)(*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			*a3 = 0;
		}
		else
		{
			iVar4 = PATH_GetYPosition(pDVar3->pDynamicPath);
			*a3 = iVar4;
		}
	}
	if ((*a2 != 0) && (*a3 != 0))
	{
		return 1;
	}
	bVar2 = UNITS_GetDirection(pUnit);
	uVar5 = (uint32_t)(bVar2 >> 3);
	aiStack_40[1] = 0xffffffff;
	aiStack_40[3] = 0xffffffff;
	aiStack_40[0xb] = 0xffffffff;
	aiStack_40[0xd] = 0xffffffff;
	uVar1 = pUnit->dwUnitType;
	aiStack_40[0] = 0;
	aiStack_40[4] = 0;
	aiStack_40[2] = 0xfffffffe;
	aiStack_40[5] = 1;
	aiStack_40[6] = 2;
	aiStack_40[7] = 1;
	aiStack_40[8] = 2;
	aiStack_40[9] = 1;
	aiStack_40[10] = 0;
	aiStack_40[0xc] = 0xfffffffe;
	aiStack_40[0xe] = 0;
	aiStack_40[0xf] = 1;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar4 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar4 = 0;
	}
	else
	{
		iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	*a2 = aiStack_40[uVar5] + iVar4;
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
	{
		if (pUnit->pDynamicPath != nullptr)
		{
			iVar4 = PATH_GetYPosition(pUnit->pDynamicPath);
			*a3 = aiStack_40[uVar5 + 8] + iVar4;
			return 1;
		}
		*a3 = aiStack_40[uVar5 + 8];
		return 1;
	}
	*a3 = aiStack_40[uVar5 + 8] + (int)(*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	return 1;
}

//D2Client.0x6FABAB20
void __fastcall sub_6FABAB20(int* a1, int* a2)
{
	int iVar1;
	int iVar2;

	iVar2 = *a1;
	iVar1 = *a2 * *a2 + iVar2 * iVar2;
	if (iVar1 < 4)
	{
		*a1 = iVar2 * 4;
		iVar1 = *a2 * 4;
		*a2 = iVar1;
		iVar2 = *a1;
		iVar1 = iVar1 * iVar1 + iVar2 * iVar2;
	}
	if (iVar1 < 0x10)
	{
		*a1 = iVar2 * 2;
		*a2 = *a2 * 2;
	}
}

//D2Client.0x6FABAB70
void __fastcall sub_6FABAB70(int* a1, int* a2)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar2 = *a2;
	iVar3 = -*a1;
	iVar1 = iVar3 * iVar3 + iVar2 * iVar2;
	while (3 < iVar1)
	{
		iVar2 = iVar2 / 2;
		iVar3 = iVar3 / 2;
		iVar1 = iVar3 * iVar3 + iVar2 * iVar2;
	}
	*a1 = iVar2;
	*a2 = iVar3;
}

//D2Client.0x6FABABC0
D2UnitStrc* __fastcall sub_6FABABC0(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;
	int32_t DVar6;
	int aiStack_40[16];

	pDVar3 = sub_6FB296A0((int)pUnit);
	if (pDVar3 == nullptr)
	{
		pDynamicPath = pUnit->pDynamicPath;
		iVar4 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		DVar5 = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
	}
	else
	{
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
		}
		uVar1 = pDVar3->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
		}
		else if (pDVar3->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
		}
		else
		{
			DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
		}
	}
	if ((iVar4 == 0) || (DVar5 == (int32_t)0x0))
	{
		bVar2 = UNITS_GetDirection(pUnit);
		aiStack_40[5] = 1;
		aiStack_40[7] = 1;
		aiStack_40[9] = 1;
		aiStack_40[0xf] = 1;
		uVar1 = pUnit->dwUnitType;
		aiStack_40[0] = 0;
		aiStack_40[1] = 0xffffffff;
		aiStack_40[2] = 0xfffffffe;
		aiStack_40[3] = 0xffffffff;
		aiStack_40[4] = 0;
		aiStack_40[6] = 2;
		aiStack_40[8] = 2;
		aiStack_40[10] = 0;
		aiStack_40[0xb] = 0xffffffff;
		aiStack_40[0xc] = 0xfffffffe;
		aiStack_40[0xd] = 0xffffffff;
		aiStack_40[0xe] = 0;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iVar4 = aiStack_40[bVar2 >> 3] + iVar4;
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
		}
		else
		{
			DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DVar5 = (int32_t)(aiStack_40[(bVar2 >> 3) + 8] + (int)DVar6);
	}
	if ((iVar4 != 0) && (DVar5 != (int32_t)0x0))
	{
		pDVar3 = sub_6FB3EB50(pUnit, a2, iVar4, (D2UnitStrc*)DVar5, a3, a4);
		return pDVar3;
	}
	return nullptr;
}

//D2Client.0x6FABAD50
D2UnitStrc* __fastcall sub_6FABAD50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	int32_t nY2;
	D2UnitStrc* pDVar2;
	int nX2;
	int32_t nY1;
	int iVar3;
	int32_t DStack_c;
	int local_8;
	uint32_t local_4;

	local_4 = a2;
	pDVar2 = sub_6FB296A0((int)pUnit);
	if (pDVar2 == nullptr)
	{
		pDynamicPath = pUnit->pDynamicPath;
		nX2 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		local_8 = nX2;
		DStack_c = (int32_t)D2COMMON_10176_PathGetFirstPointY(pDynamicPath);
	}
	else
	{
		uVar1 = pDVar2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nX2 = pDVar2->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			nX2 = 0;
		}
		else
		{
			nX2 = PATH_GetXPosition(pDVar2->pDynamicPath);
		}
		uVar1 = pDVar2->dwUnitType;
		local_8 = nX2;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_c = (*(int32_t*)&pDVar2->pDynamicPath->tTargetCoord);
		}
		else if (pDVar2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_c + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_c + 2)) = 0;
		}
		else
		{
			DStack_c = (int32_t)PATH_GetYPosition(pDVar2->pDynamicPath);
		}
	}
	if ((nX2 == 0) || (DStack_c == (int32_t)0x0))
	{
		sub_6FABA860(pUnit, &local_8, &DStack_c);
		nX2 = local_8;
	}
	nY2 = DStack_c;
	if ((nX2 != 0) && (DStack_c != (int32_t)0x0))
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY1 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY1 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY1 + 2)) = 0;
		}
		else
		{
			nY1 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iVar3 = PATH_ComputeSquaredDistance(iVar3, (int)nY1, nX2, (int)nY2);
		if (iVar3 < 0x2711)
		{
			pDVar2 = sub_6FB3EAF0((int)pUnit, local_4, nX2, (D2UnitStrc**)nY2, a3, a4);
			return pDVar2;
		}
	}
	return nullptr;
}

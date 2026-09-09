#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/SUnitInactive.h>


BEGIN_VISIT(D2MinionListStrc)
	//FIELD(dwMinionGUID)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2InactiveItemNodeStrc)
	//POINTER(pNext)
	//FIELD(nFrame)
	//FIELD(nOwnerId)
	//FIELD(nBitstreamSize)
	//FIELD(pBitstream)
END_VISIT()

BEGIN_VISIT(D2InactiveMonsterNodeStrc)
	//FIELD(nX)
	//FIELD(nY)
	//FIELD(nClassId)
	//FIELD(nUnitId)
	//FIELD(nUnitFlags)
	//FIELD(nUnitFlagsEx)
	//FIELD(nTypeFlags)
	//FIELD(unk0x1C)
	//POINTER(pMinionList)
	//POINTER(pMapAI)
	//OBJECT(nAiSpecialState)
	//FIELD(nLevelId)
	//FIELD(nNameSeed)
	//ARRAY(nMonUMods)
	//FIELD(unk0x3B)
	//FIELD(nBossHcIdx)
	//FIELD(unk0x3E)
	//FIELD(nExperience)
	//FIELD(nMaxHitpoints)
	//FIELD(nHitpoints)
	//FIELD(nCmdParam1)
	//FIELD(nCmdParam2)
	//FIELD(nGameFrame)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2InactiveUnitNodeStrc)
	//FIELD(nX)
	//FIELD(nY)
	//FIELD(nUnitType)
	//FIELD(nClassId)
	//FIELD(nAnimMode)
	//FIELD(nGameFrame)
	//FIELD(nUnitFlags)
	//FIELD(nUnitFlagsEx)
	//FIELD(nUnitId)
	//FIELD(nFrame)
	//FIELD(nInteractType)
	//FIELD(unk0x29)
	//FIELD(unk0x2A)
	//FIELD(nDropItemCode)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2InactiveUnitListStrc)
	//FIELD(nX)
	//FIELD(nY)
	//POINTER(pInactiveItems)
	//POINTER(pInactiveMonsters)
	//POINTER(pInactiveUnits)
	//POINTER(pNext)
END_VISIT()

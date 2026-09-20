#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <MONSTER/MonsterRegion.h>


BEGIN_VISIT(D2MonRegDataStrc)
	//FIELD(nMonHcIdx)
	//FIELD(nRarity)
	//FIELD(nComponentVariantsMax)
	//ARRAY(nComponentVariants)
END_VISIT()

BEGIN_VISIT(D2MonsterRegionStrc)
	//FIELD(nAct)
	//ARRAY(unk0x01)
	//FIELD(unk0x04)
	//FIELD(unk0x08)
	//FIELD(unk0x0C)
	//FIELD(nMonCount)
	//FIELD(nTotalRarity)
	//FIELD(nSpawnCount)
	//FIELD(unk0x13)
	//ARRAY(pMonData)
	//FIELD(dwMonDen)
	//FIELD(nBossMin)
	//FIELD(nBossMax)
	//FIELD(nMonWander)
	//FIELD(unk0x2BF)
	//FIELD(dwlevel)
	//FIELD(unk0x2C4)
	//FIELD(dwUniqueCount)
	//FIELD(dwMonSpawnCount)
	//FIELD(dwMonKillCount)
	//FIELD(unk0x2D4)
	//FIELD(nQuest)
	//ARRAY(unk0x2D9)
	//FIELD(dwDungeonLevel)
	//FIELD(dwDungeonLevelEx)
END_VISIT()

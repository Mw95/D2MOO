#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <MONSTER/MonsterSpawn.h>


BEGIN_VISIT(D2UnkMonCreateStrc)
	//POINTER(pGame)
	//POINTER(pRoom)
	//POINTER(pRoomCoordList)
	//FIELD(nMonsterId)
	//FIELD(nAnimMode)
	//FIELD(nUnitGUID)
	//FIELD(nX)
	//FIELD(nY)
	//FIELD(field_20)
	//FIELD(nFlags)
END_VISIT()

BEGIN_VISIT(D2UnkMonCreateStrc3)
	//FIELD(nXOffset)
	//FIELD(nYOffset)
	//FIELD(nSpawnType)
END_VISIT()

BEGIN_VISIT(D2UnkMonCreateStrc2)
	//FIELD(nRecordCount)
	//FIELD(unk0x04)
	//FIELD(unk0x08)
	//ARRAY(pad0x09)
	//ARRAY(records)
END_VISIT()

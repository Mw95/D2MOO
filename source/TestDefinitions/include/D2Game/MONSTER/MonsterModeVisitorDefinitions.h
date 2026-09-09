#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <MONSTER/MonsterMode.h>


BEGIN_VISIT(D2ModeChangeStrc)
	//FIELD(nMode)
	//POINTER(pUnit)
	//POINTER(pTargetUnit)
	//FIELD(nX)
	//FIELD(nY)
	//ARRAY(unk0x14)
	//FIELD(unk0x18)
	//FIELD(unk0x1C)
	//ARRAY(unk0x1D)
END_VISIT()

BEGIN_VISIT(D2MonModeCallbackTableStrc)
	//OBJECT(unk0x00)
	//OBJECT(unk0x04)
	//OBJECT(unk0x08)
	//FIELD(unk0x0C)
END_VISIT()

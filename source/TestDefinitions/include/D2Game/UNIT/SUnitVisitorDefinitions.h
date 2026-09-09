#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/SUnit.h>


BEGIN_VISIT(D2UnitInfoStrc)
	//FIELD(nUnitType)
	//FIELD(nClassId)
	//FIELD(nUnitGUID)
	//FIELD(nAnimMode)
	//FIELD(nX)
	//FIELD(nY)
	//FIELD(nOwnerType)
	//FIELD(nOwnerGUID)
	//FIELD(unk0x20)
	//ARRAY(szDescription)
END_VISIT()

BEGIN_VISIT(D2UnitDescriptionListStrc)
	//FIELD(nClassId)
	//FIELD(nCount)
	//FIELD(nDefaultCount)
	//ARRAY(szDescription)
	//POINTER(pNext)
END_VISIT()

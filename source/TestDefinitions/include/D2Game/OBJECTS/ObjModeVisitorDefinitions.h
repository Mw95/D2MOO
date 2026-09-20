#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <OBJECTS/ObjMode.h>


BEGIN_VISIT(D2ObeliskPowerUpStrc)
	//OBJECT(pPowerUpCallback)
	//FIELD(nChance)
	//FIELD(nValue)
END_VISIT()

BEGIN_VISIT(D2ObjOperateFnStrc)
	//POINTER(pGame)
	//POINTER(pObject)
	//POINTER(pPlayer)
	//POINTER(pObjectregion)
	//FIELD(nObjectIdx)
END_VISIT()

BEGIN_VISIT(D2ShrineTableStrc)
	//OBJECT(pfShrineCallback)
	//FIELD(unk0x04)
	//FIELD(unk0x08)
END_VISIT()

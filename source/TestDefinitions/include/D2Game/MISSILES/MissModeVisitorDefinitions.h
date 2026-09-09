#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <MISSILES/MissMode.h>


BEGIN_VISIT(D2MissileUnitFindArgStrc)
	//POINTER(pGame)
	//POINTER(pMissile)
	//POINTER(pOwner)
	//POINTER(pMissilesTxtRecord)
END_VISIT()

BEGIN_VISIT(D2MissileUnitFindTableStrc)
	//OBJECT(pfUnitFindCallback)
	//FIELD(nCollisionMask)
END_VISIT()

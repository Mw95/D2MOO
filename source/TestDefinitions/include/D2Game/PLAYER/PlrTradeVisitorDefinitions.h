#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <PLAYER/PlrTrade.h>


BEGIN_VISIT(D2CubeItemStrc)
	//POINTER(pItem)
	//FIELD(nClassId)
	//FIELD(nItemLevel)
END_VISIT()

BEGIN_VISIT(D2CubeTableStrc)
	//OBJECT(pFunc)
END_VISIT()

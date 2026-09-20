#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2ItemMods.h>


BEGIN_VISIT(D2PropertyAssignStrc)
	//OBJECT(pfAssign)
	//FIELD(nStatId)
END_VISIT()

BEGIN_VISIT(D2ItemCalcStrc)
	//POINTER(pUnit)
	//POINTER(pItem)
END_VISIT()

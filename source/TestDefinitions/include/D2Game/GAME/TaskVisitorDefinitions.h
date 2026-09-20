#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <GAME/Task.h>


BEGIN_VISIT(D2LinkStrc)
	//POINTER(pPrev)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2TaskStrc)
	//FIELD(nTaskQ)
	//FIELD(nType)
	//OBJECT(pTaskBalanceLink)
	//OBJECT(pTaskQueueLink)
END_VISIT()

BEGIN_VISIT(CRITICAL_SECTION_WRAPPER)
	//OBJECT(cs)
END_VISIT()

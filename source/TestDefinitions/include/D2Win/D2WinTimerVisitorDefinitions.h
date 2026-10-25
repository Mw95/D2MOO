#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinTimer.h>


BEGIN_VISIT(D2WinTimerStrc)
	OBJECT(controlHeader)
	FIELD(nTimeout)
	//FIELD(dwTickCount) // Result of GetTickCount(), may differ between both calls
END_VISIT()

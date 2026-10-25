#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinAnimImage.h>


BEGIN_VISIT(D2AnimatedImageDescriptor)
	FIELD(ppCellFile1)
	FIELD(ppCellFile2)
	FIELD(eDrawMode)
	FIELD(nAnimSpeed)
END_VISIT()

BEGIN_VISIT(D2WinAnimImageStrc)
	OBJECT(controlHeader)
	POINTER(pAnimatedImageDescriptor)
	FIELD(nAnimSpeed)
	//FIELD(dwStartTickCount) // Result of GetTickCount(), may differ between both calls
	FIELD(nFrame)
	FIELD(nAnimType)
	FIELD(eDrawMode)
	FIELD(pfOnHoverChanged)
	FIELD(bIsRunning)
END_VISIT()

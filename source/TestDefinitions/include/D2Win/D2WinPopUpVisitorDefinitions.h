#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinPopUp.h>


BEGIN_VISIT(D2WinPopUpLineStrc)
	ARRAY(wszText)
	FIELD(pfHandleMouseInput)
END_VISIT()

BEGIN_VISIT(D2WinPopUpStrc)
	OBJECT(controlHeader)
	FIELD(nLines)
	ARRAY(lines)
	FIELD(nCurrentLine)
END_VISIT()

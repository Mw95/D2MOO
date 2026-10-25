#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "D2WinTextBoxVisitorDefinitions.h"

#include <D2WinScrollBar.h>


BEGIN_VISIT(D2WinScrollBarStrc)
	OBJECT(controlHeader)
	FIELD(bIsUpperArrowPressed)
	FIELD(bIsLowerArrowPressed)
	FIELD(nMaxSteps)
	FIELD(nCurrentStep)
	FIELD(nPageSize)
	POINTER(pTextBox)
	FIELD(bIsStepIndicatorDragged)
	FIELD(pfOnScroll)
END_VISIT()

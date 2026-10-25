#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinImage.h>


BEGIN_VISIT(D2WinImageClickRectStrc)
	FIELD(nX)
	FIELD(nY)
	FIELD(nWidth)
	FIELD(nHeight)
	FIELD(pCallback)
END_VISIT()

BEGIN_VISIT(D2WinImageStrc)
	OBJECT(controlHeader)
	FIELD(nFrame)
	FIELD(eDrawMode)
	POINTER(pClickRect)
	FIELD(nBorderWidth)
	FIELD(nBorderHeight)
END_VISIT()

BEGIN_VISIT(D2WinImage2Strc)
	OBJECT(controlHeader)
	FIELD(nFrame)
	FIELD(eDrawMode)
	POINTER(pClickRect)
END_VISIT()

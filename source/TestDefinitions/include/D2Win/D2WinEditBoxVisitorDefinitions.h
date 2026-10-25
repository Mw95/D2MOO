#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinEditBox.h>


BEGIN_VISIT(D2WinEditBoxStrc)
	OBJECT(controlHeader)
	FIELD(nTextOffsetX)
	FIELD(nTextOffsetY)
	FIELD(nMaxLength)
	FIELD(nFirstVisibleChar)
	FIELD(nLastVisibleChar)
	FIELD(nSelectionStart)
	FIELD(nSelectionEnd)
	ARRAY(wszText)
	FIELD(nCursorPosition)
	FIELD(dwEditBoxFlags)
	FIELD(pfOnReturn)
	FIELD(pfCharFilter)
	FIELD(pfOnTextChanged)
	FIELD(eFont)
	FIELD(nTextColor)
	POINTER(pNext)
	POINTER(pPrevious)
	FIELD(bMouseSelecting)
END_VISIT()

BEGIN_VISIT(D2WinEditBoxFontStrc)
	FIELD(eFont)
	FIELD(nTextColor)
END_VISIT()

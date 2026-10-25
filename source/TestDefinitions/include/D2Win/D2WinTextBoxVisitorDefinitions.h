#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinTextBox.h>


// NOTE: pColumns point to strings, but ARRAY() only compares their first character (and whether they are null).
// Compare the strings separately when needed.
BEGIN_VISIT(D2WinTextBoxLineStrc)
	ARRAY(pColumns)
	FIELD(nColor)
	FIELD(bContinued)
	//ARRAY(pad0x19)
	POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2WinTextBoxStrc)
	OBJECT(controlHeader)
	FIELD(nTextOffsetX)
	FIELD(nTextOffsetY)
	POINTER(pFirstLine)
	POINTER(pLastLine)
	POINTER(pCurrentLine)
	FIELD(nNumLines)
	FIELD(nLine)
	FIELD(dwTextBoxFlags)
	FIELD(nCurrentLine)
	FIELD(nNumColumns)
	ARRAY(nColumnOffsets)
	ARRAY(nColumnFlags)
	POINTER(pScrollBar)
	FIELD(eFont)
	FIELD(nTextColor)
	FIELD(nScrollOffset)
	FIELD(nContinuedLineSpacing)
	FIELD(nLineSpacing)
	FIELD(nExtraLineSpacing)
END_VISIT()

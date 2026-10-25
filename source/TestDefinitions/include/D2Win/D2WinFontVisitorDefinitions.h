#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinFont.h>


BEGIN_VISIT(D2CharStrc)
	FIELD(wChar)
	FIELD(nReserved0x02)
	FIELD(nWidth)
	FIELD(nHeight)
	FIELD(nReserved0x05)
	FIELD(wReserved0x06)
	FIELD(nImageIndex)
	FIELD(dwReserved0x0A)
END_VISIT()

BEGIN_VISIT(D2FontStrc)
	FIELD(dwHeader)
	FIELD(wVersion)
	FIELD(wReserved0x06)
	FIELD(wNumChars)
	FIELD(nHeight)
	FIELD(nWidth)
	ARRAY(pChars)
END_VISIT()

BEGIN_VISIT(D2FontCacheStrc)
	FIELD(pCellFile)
	ARRAY(pFontInfo)
	POINTER(pCharInfo)
	//FIELD(dwShiftedTickCount) // Derived from GetTickCount(), may differ between both calls
END_VISIT()

// NOTE: wszLine points to a string, but POINTER() would only compare its first character. Compare the strings separately.
BEGIN_VISIT(D2SplittedTextStrc)
	//POINTER(wszLine)
	POINTER(pNextLine)
END_VISIT()

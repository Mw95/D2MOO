#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinAccountList.h>


BEGIN_VISIT(D2WinAccountListDataStrc)
	ARRAY(szText)
	//ARRAY(pad0x32)
	POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2WinAccountListStrc)
	OBJECT(controlHeader)
	POINTER(pDataList)
	POINTER(pSelectedDataEntry)
	FIELD(nFirstVisibleEntry)
	FIELD(nUnused)
	FIELD(eFont)
	FIELD(nTextColor)
END_VISIT()

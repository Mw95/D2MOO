#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinList.h>


BEGIN_VISIT(D2WinListDataStrc)
	ARRAY(wszText)
	FIELD(nTextWidth)
	FIELD(pfOnSelect)
	FIELD(nLeft)
	FIELD(nRight)
	FIELD(nTop)
	FIELD(nBottom)
	FIELD(nHotkeyChar)
	//ARRAY(pad0x219)
	FIELD(nHotkeyVirtualKey)
	POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2WinListItemInitStrc)
	FIELD(nStringId)
	FIELD(nHotkeyChar)
	//ARRAY(pad0x05)
	FIELD(nHotkeyVirtualKey)
	FIELD(pfOnSelect)
END_VISIT()

BEGIN_VISIT(D2WinListStrc)
	OBJECT(controlHeader)
	FIELD(eFont)
	FIELD(nLineHeight)
	FIELD(nLinePadding)
	FIELD(nFirstVisibleItem)
	FIELD(nItemCount)
	FIELD(nSelectedIndex)
	FIELD(nMaxVisibleItemIndex)
	FIELD(nPentspinFrame)
	FIELD(nMaxItemWidth)
	POINTER(pDataList)
	POINTER(pSelectedDataEntry)
END_VISIT()

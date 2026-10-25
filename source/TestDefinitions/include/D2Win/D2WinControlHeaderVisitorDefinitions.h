#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2WinControlHeader.h>


// NOTE: hWindow is the control handling the message, which is a different object in both implementations
BEGIN_VISIT(SMSGHANDLER_PARAMS)
	OMIT(hWindow)
	FIELD(nMessage)
	FIELD(wParam)
	FIELD(lParam)
	FIELD(nNotifyCode)
	OMIT(pExtra)
	FIELD(bUseResult)
	FIELD(lResult)
END_VISIT()

// NOTE: The callbacks which get set to internal functions of the respective implementation (pfDraw, pfInitialize, ...)
// differ between D2MOO and the original .dll, so they are omitted. Only pfCallback is always provided by the caller.
BEGIN_VISIT(D2WinControlStrc)
	FIELD(nType)
	FIELD(pCellFile)
	FIELD(dwFlags)
	FIELD(nImageX)
	FIELD(nImageY)
	FIELD(nWidth)
	FIELD(nHeight)
	OMIT(pfDraw)
	OMIT(pfInitialize)
	OMIT(pfHandleMouseDown)
	OMIT(pfHandleMouseUp)
	OMIT(pfHandleCharInput)
	OMIT(pfHandleVirtualKeyInput)
	FIELD(pfCallback)
	OMIT(pfShouldMouseInputBeHandled)
	POINTER(pNext)
END_VISIT()

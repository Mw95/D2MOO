#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"
#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinButton.h>


BEGIN_VISIT(D2WinButtonStrc)
	OBJECT(controlHeader)
	FIELD(dwButtonFlags)
	FIELD(bIsPressed)
	FIELD(bIsCallbackPending)
	FIELD(nActivationCounter)
	FIELD(nActivationVirtualKey)
	FIELD(nIsPressedFrameOffset)
	FIELD(nDisabledFrameOffset)
	FIELD(nBaseFrame)
	FIELD(eFont)
	ARRAY(wszText)
	FIELD(nTextColor)
	FIELD(pfUpdateHoverState)
	FIELD(isButtonHovered)
	FIELD(nStringId)
	//FIELD(pad0x272)
END_VISIT()

#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinProgressBar.h>


BEGIN_VISIT(D2WinProgressBarStrc)
	OBJECT(controlHeader)
	FIELD(fProgress)
END_VISIT()

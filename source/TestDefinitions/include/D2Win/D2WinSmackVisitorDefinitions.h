#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "D2WinControlHeaderVisitorDefinitions.h"

#include <D2WinSmack.h>


BEGIN_VISIT(D2WinSmackerContextStrc)
	//ARRAY(pRendererData) // Filled by the renderer
	FIELD(nX)
	FIELD(nY)
END_VISIT()

BEGIN_VISIT(D2WinSmackStrc)
	OBJECT(controlHeader)
	ARRAY(szFileName)
	OBJECT(smackerContext)
END_VISIT()

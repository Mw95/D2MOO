#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <GAME/Arena.h>


BEGIN_VISIT(D2ArenaStrc)
	//FIELD(nAlternateStartTown)
	//FIELD(nType)
	//FIELD(fFlags)
	//FIELD(nTemplate)
END_VISIT()

BEGIN_VISIT(D2ArenaUnitStrc)
	//FIELD(nScore)
	//FIELD(bUpdateScore)
END_VISIT()

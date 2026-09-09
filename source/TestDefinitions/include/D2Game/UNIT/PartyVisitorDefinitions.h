#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/Party.h>


BEGIN_VISIT(D2PartyNodeStrc)
	//FIELD(nUnitGUID)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2PartyStrc)
	//FIELD(nPartyId)
	//FIELD(field_2)
	//POINTER(pPartyNodes)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2PartyControlStrc)
	//FIELD(field_0)
	//FIELD(field_2)
	//POINTER(pParties)
END_VISIT()

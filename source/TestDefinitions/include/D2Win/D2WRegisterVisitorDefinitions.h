#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2WRegister.h>


BEGIN_VISIT(D2WinCommandRegisterStrc)
	FIELD(nType)
	FIELD(nId)
	FIELD(pCallback)
END_VISIT()

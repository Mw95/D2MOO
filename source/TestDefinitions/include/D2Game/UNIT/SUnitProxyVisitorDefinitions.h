#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/SUnitProxy.h>


BEGIN_VISIT(D2ItemCacheStrc)
	//FIELD(nMin)
	//FIELD(nMax)
	//FIELD(nMagicMin)
	//FIELD(nMagicMax)
	//FIELD(dwCode)
	//FIELD(nMagicLevel)
END_VISIT()

BEGIN_VISIT(D2UnitProxyStrc)
	//POINTER(pItemCache)
	//FIELD(nItems)
	//POINTER(pPermCache)
	//FIELD(nPerms)
END_VISIT()

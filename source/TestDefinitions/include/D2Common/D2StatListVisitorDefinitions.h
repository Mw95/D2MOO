#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2StatList.h>


BEGIN_VISIT(D2SLayerStatIdStrc)
	//OBJECT(int32_t)
	//BEGIN_UNION()
		//FIELD(nLayer)
		//FIELD(nStat)
		//OBJECT(nPackedValue)
	//END_UNION()
	//OBJECT(ls)
	//OBJECT(nPackedValue)
	//OBJECT(ls)
END_VISIT()

BEGIN_VISIT(D2StatsArrayStrc)
	//POINTER(pStat)
	//FIELD(nStatCount)
	//FIELD(nCapacity)
END_VISIT()

BEGIN_VISIT(D2ModStatsArrayStrc)
	//POINTER(pStat)
	//FIELD(nStatCount)
	//FIELD(nCapacity)
END_VISIT()

BEGIN_VISIT(D2StatListStrc)
	//OMIT(pMemPool)
	//POINTER(pUnit)
	//FIELD(dwOwnerType)
	//FIELD(dwOwnerId)
	//FIELD(dwFlags)
	//FIELD(dwStateNo)
	//FIELD(dwExpireFrame)
	//FIELD(dwSkillNo)
	//FIELD(dwSLvl)
	//OBJECT(Stats)
	//POINTER(pPrevLink)
	//POINTER(pNextLink)
	//POINTER(pParent)
	//OBJECT(fpStatRemove)
END_VISIT()

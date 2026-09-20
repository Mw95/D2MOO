#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2StatList.h>


BEGIN_VISIT(D2SLayerStatIdStrc)
	FIELD(nLayer)
	FIELD(nStat)
END_VISIT()

BEGIN_VISIT(D2StatStrc)
	FIELD(nLayer)
	FIELD(nStat)
	FIELD(nValue)
END_VISIT()

BEGIN_VISIT(D2StatsArrayStrc)
	POINTER(pStat)
	FIELD(nStatCount)
	FIELD(nCapacity)
END_VISIT()

BEGIN_VISIT(D2ModStatsArrayStrc)
	POINTER(pStat)
	FIELD(nStatCount)
	FIELD(nCapacity)
END_VISIT()

BEGIN_VISIT(D2StatListStrc)
	OMIT(pMemPool)
	POINTER(pUnit)
	FIELD(dwOwnerType)
	FIELD(dwOwnerId)
	FIELD(dwFlags)
	FIELD(dwStateNo)
	FIELD(dwExpireFrame)
	FIELD(dwSkillNo)
	FIELD(dwSLvl)
	OBJECT(Stats)
	POINTER(pPrevLink)
	POINTER(pNextLink)
	POINTER(pParent)
	FIELD(fpStatRemove)
END_VISIT()

BEGIN_VISIT(D2StatListExStrc)
	OMIT(pMemPool)
	POINTER(pUnit)
	FIELD(dwOwnerType)
	FIELD(dwOwnerId)
	FIELD(dwFlags)
	FIELD(dwStateNo)
	FIELD(dwExpireFrame)
	FIELD(dwSkillNo)
	FIELD(dwSLvl)
	OBJECT(Stats)
	POINTER(pPrevLink)
	POINTER(pNextLink)
	POINTER(pParent)
	FIELD(fpStatRemove)
	POINTER(pMyLastList)
	POINTER(pMyStats)
	POINTER(pOwner)
	OBJECT(FullStats)
	OBJECT(ModStats)
	//DYNAMIC_ARRAY(StatFlags)
	FIELD(pfOnValueChanged)
	//OMIT(pGame)
END_VISIT()

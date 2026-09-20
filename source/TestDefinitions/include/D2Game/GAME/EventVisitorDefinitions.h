#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <GAME/Event.h>


BEGIN_VISIT(D2TimerArg2Strc)
	//FIELD(nUnitGUID)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2TimerArgStrc)
	//POINTER(unk0x00)
	//FIELD(dwUnitId)
END_VISIT()

BEGIN_VISIT(D2EventTimerStrc)
	//OBJECT(nEventType)
	//FIELD(padding0x01)
	//FIELD(nFlags)
	//FIELD(nExpireFrame)
	//POINTER(pUnit)
	//FIELD(nUnitGUID)
	//FIELD(nUnitType)
	//FIELD(dwEventCustomId)
	//FIELD(dwEventCustomParam)
	//POINTER(pNextFreeEventTimer)
	//POINTER(unk0x20)
	//POINTER(pNext)
	//POINTER(pPrevious)
	//OBJECT(pCallback)
END_VISIT()

BEGIN_VISIT(D2EventTimerSlabListStrc)
	//ARRAY(tEventTimersStorage)
	//POINTER(pFreeEventTimerListHead)
	//POINTER(pNextSlab)
END_VISIT()

BEGIN_VISIT(D2EventTimerQueueStrc)
	//FIELD(nArrayIndex)
	//ARRAY(pHead)
	//ARRAY(pTail)
	//ARRAY(pInfinite)
	//POINTER(pCurrent)
	//POINTER(pSlabListHead)
END_VISIT()

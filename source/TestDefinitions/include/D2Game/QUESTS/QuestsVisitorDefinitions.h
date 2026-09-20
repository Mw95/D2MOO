#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <QUESTS/Quests.h>


BEGIN_VISIT(D2QuestArgStrc)
	//POINTER(pGame)
	//FIELD(nEvent)
	//POINTER(pTarget)
	//POINTER(pPlayer)
	//FIELD(unk0x10)
	//BEGIN_UNION()
		//POINTER(pTextControl)
		//FIELD(dw18)
		//FIELD(nNPCNo)
		//FIELD(unk0x16)
		//FIELD(nMessageIndex)
		//FIELD(unk0x1A)
		//FIELD(nOldLevel)
		//FIELD(nNewLevel)
	//END_UNION()
END_VISIT()

BEGIN_VISIT(D2QuestChainStrc)
	//POINTER(pQuestData)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2QuestGUIDStrc)
	//ARRAY(nPlayerGUIDs)
	//FIELD(nPlayerCount)
	//ARRAY(pad0x82)
END_VISIT()

BEGIN_VISIT(D2NPCMessageStrc)
	//FIELD(nNPCNo)
	//FIELD(nStringIndex)
	//FIELD(nPad)
	//FIELD(nMenu)
END_VISIT()

BEGIN_VISIT(D2NPCMessageTableStrc)
	//ARRAY(pMessages)
	//FIELD(nMessages)
END_VISIT()

BEGIN_VISIT(D2QuestDataStrc)
	//FIELD(nQuestNo)
	//POINTER(pGame)
	//FIELD(nActNo)
	//FIELD(bNotIntro)
	//FIELD(bActive)
	//FIELD(fLastState)
	//FIELD(fState)
	//FIELD(nInitNo)
	//FIELD(dw0E)
	//FIELD(nSeqId)
	//FIELD(dwFlags)
	//OMIT(pQuestDataEx)
	//OBJECT(tPlayerGUIDs)
	//ARRAY(pfCallback)
	//POINTER(pNPCMessages)
	//FIELD(nQuestFilter)
	//OBJECT(pfStatusFilter)
	//OBJECT(pfActiveFilter)
	//OBJECT(pfSeqFilter)
	//POINTER(pPrev)
END_VISIT()

BEGIN_VISIT(D2QuestInitTableStrc)
	//OBJECT(pfInit)
	//FIELD(nAct)
	//ARRAY(pad0x05)
	//FIELD(nVersion)
	//FIELD(bNoSetState)
	//ARRAY(pad0x0D)
	//FIELD(nChainNo)
	//FIELD(nQuestNo)
END_VISIT()

BEGIN_VISIT(D2QuestIntroTableStrc)
	//OBJECT(pfInit)
	//FIELD(nAct)
	//ARRAY(pad0x05)
END_VISIT()

BEGIN_VISIT(D2QuestTimerStrc)
	//OBJECT(pfUpdate)
	//POINTER(pQuest)
	//FIELD(dwTicks)
	//FIELD(dwTimeout)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2QuestInfoStrc)
	//POINTER(pLastQuest)
	//FIELD(bExecuting)
	//FIELD(bPickedSet)
	//POINTER(pQuestFlags)
	//POINTER(pTimer)
	//FIELD(dwTick)
	//OBJECT(pSeed)
	//FIELD(unk0x20)
	//ARRAY(unk0x21)
END_VISIT()

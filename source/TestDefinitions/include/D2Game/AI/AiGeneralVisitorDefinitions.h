#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <AI/AiGeneral.h>


BEGIN_VISIT(D2AiCmdStrc)
	//POINTER(pNextCmd)
	//POINTER(pPrevCmd)
	//ARRAY(nCmdParam)
END_VISIT()

BEGIN_VISIT(D2AiTickParamStrc)
	//POINTER(pAiControl)
	//FIELD(unk0x04)
	//POINTER(pTarget)
	//ARRAY(unk0x0C)
	//FIELD(nTargetDistance)
	//FIELD(bCombat)
	//POINTER(pMonstatsTxt)
	//POINTER(pMonstats2Txt)
END_VISIT()

BEGIN_VISIT(D2AiControlStrc)
	//OBJECT(nAiSpecialState)
	//OBJECT(pAiParamFn)
	//FIELD(nAiFlags)
	//ARRAY(unk0x0A)
	//FIELD(dwOwnerGUID)
	//FIELD(dwOwnerType)
	//ARRAY(dwAiParam)
	//POINTER(pCurrentCmd)
	//POINTER(pLastCmd)
	//POINTER(pGame)
	//FIELD(dwOwnerGUIDEx)
	//FIELD(dwOwnerTypeEx)
	//POINTER(pMinionList)
	//POINTER(pMapAi)
	//FIELD(nMinionSpawnClassId)
END_VISIT()

BEGIN_VISIT(D2AiParamStrc)
	//FIELD(unk0x00)
	//FIELD(unk0x01)
	//FIELD(unk0x02)
	//FIELD(unk0x03)
	//POINTER(pTarget)
	//FIELD(unk0x08)
	//FIELD(unk0x0C)
	//FIELD(unk0x10)
	//FIELD(unk0x14)
	//FIELD(unk0x18)
	//FIELD(nVelocity)
	//FIELD(unk0x20)
	//FIELD(unk0x21)
	//FIELD(unk0x22)
	//FIELD(unk0x23)
END_VISIT()

BEGIN_VISIT(D2AiTableStrc)
	//FIELD(unk0x00)
	//OBJECT(unk0x04)
	//OBJECT(pAiParamFn)
	//OBJECT(unk0x0C)
END_VISIT()

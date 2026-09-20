#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <AI/AiUtil.h>


BEGIN_VISIT(D2BaalThroneAiCallbackArgStrc)
	//POINTER(pTarget)
	//FIELD(nDistance)
	//FIELD(unk0x08)
	//FIELD(nMaxDistance)
END_VISIT()

BEGIN_VISIT(D2UnkAiCallbackArgStrc)
	//POINTER(pTarget)
	//FIELD(nDistance)
	//FIELD(unk0x08)
	//FIELD(nMaxDistance)
	//FIELD(unk0x10)
	//POINTER(pAlternativeTarget)
	//FIELD(nAlternativeDistance)
END_VISIT()

BEGIN_VISIT(D2UnkAiCallbackArgStrc2)
	//POINTER(pTarget)
	//FIELD(nDistance)
	//POINTER(pAlternativeTarget)
	//FIELD(nAlternativeDistance)
END_VISIT()

BEGIN_VISIT(D2AiCallback7ArgStrc)
	//POINTER(pTarget)
	//FIELD(nDistance)
	//POINTER(unk0x08)
END_VISIT()

BEGIN_VISIT(D2AiCallback11ArgStrc)
	//POINTER(pTarget)
	//FIELD(nDistance)
	//POINTER(unk0x08)
END_VISIT()

BEGIN_VISIT(D2DoorObjectAiCallbackArgStrc)
	//POINTER(pDoor)
	//FIELD(nDistance)
END_VISIT()

BEGIN_VISIT(D2FallenShamanAiCallbackArgStrc)
	//POINTER(pTarget)
	//FIELD(nCounter)
	//FIELD(nDistance)
	//FIELD(nMaxDistance)
END_VISIT()

BEGIN_VISIT(D2VileMotherAiCallbackArgStrc)
	//FIELD(nLastInClass)
	//FIELD(nMaxDistance)
	//FIELD(nCounter)
END_VISIT()

BEGIN_VISIT(UnkAiStrc5)
	//FIELD(nMaxDistance)
END_VISIT()

#ifdef D2_VERSION_HAS_UBERS

BEGIN_VISIT(D2UbersAiCallbackArgStrc)
	//FIELD(nUberMephisto)
	//FIELD(nUberDiablo)
	//FIELD(nUberBaal)
	//FIELD(nDistance)
	//FIELD(nOtherMonsters)
	//FIELD(nDiabloSpawner)
	//FIELD(nBaalMinions)
	//FIELD(nDiabloMinions)
END_VISIT()

#endif

#ifdef D2_VERSION_HAS_UBERS

#endif

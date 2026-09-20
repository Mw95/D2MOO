#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <SKILLS/Skills.h>


BEGIN_VISIT(D2AuraCallbackStrc)
	//POINTER(pGame)
	//POINTER(pOwner)
	//FIELD(nCounter)
	//OMIT(pArgs)
END_VISIT()

BEGIN_VISIT(D2StaticFieldCallbackArgStrc)
	//FIELD(nMinDamage)
	//FIELD(nDamagePct)
	//FIELD(nStaticFieldMin)
	//FIELD(nElementalLength)
	//FIELD(nElementalType)
END_VISIT()

BEGIN_VISIT(D2UnkNecSkillStrc)
	//POINTER(pGame)
	//POINTER(pUnit)
	//FIELD(unk0x08)
	//FIELD(bUpdateAnimRate)
	//FIELD(nSkillId)
	//FIELD(nSkillLevel)
	//FIELD(nDuration)
	//ARRAY(nAuraStat)
	//ARRAY(nAuraStatCalc)
	//FIELD(nAuraTargetState)
	//ARRAY(nAuraEvent)
	//ARRAY(nAuraEventFunc)
END_VISIT()

BEGIN_VISIT(D2_6FD106F0_Strc)
	//POINTER(pUnit)
	//FIELD(nDistance)
	//FIELD(nX)
	//FIELD(nY)
END_VISIT()

BEGIN_VISIT(D2_6FD10880_Strc)
	//POINTER(unk0x00)
	//FIELD(unk0x04)
	//POINTER(unk0x08)
	//FIELD(unk0x0C)
	//FIELD(unk0x10)
	//FIELD(unk0x14)
END_VISIT()

BEGIN_VISIT(D2EffectStrc)
	//FIELD(nFlags)
	//POINTER(pUnit)
	//FIELD(nSkillId)
	//FIELD(nX)
	//FIELD(nY)
	//FIELD(nParam)
	//FIELD(nSkillLevel)
	//FIELD(unk0x1C)
	//OMIT(pfAreaEffect)
END_VISIT()

BEGIN_VISIT(D2MonSkillInfoStrc)
	//FIELD(nMinDamage)
	//FIELD(nMaxDamage)
	//FIELD(nToHit)
END_VISIT()

BEGIN_VISIT(D2CurseStrc)
	//POINTER(pUnit)
	//POINTER(pTarget)
	//FIELD(nSkill)
	//FIELD(nSkillLevel)
	//FIELD(nDuration)
	//FIELD(nStat)
	//FIELD(nStatValue)
	//FIELD(nState)
	//OBJECT(pStateRemoveCallback)
END_VISIT()

BEGIN_VISIT(D2SummonArgStrc)
	//FIELD(dwFlags)
	//POINTER(pOwner)
	//FIELD(nHcIdx)
	//OBJECT(nAiSpecialState)
	//FIELD(nMonMode)
	//OBJECT(pPosition)
	//FIELD(nPetType)
	//FIELD(nPetMax)
END_VISIT()

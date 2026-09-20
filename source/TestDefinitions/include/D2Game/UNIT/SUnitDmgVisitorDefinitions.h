#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/SUnitDmg.h>


BEGIN_VISIT(D2DamageStrc)
	//FIELD(dwHitFlags)
	//FIELD(wResultFlags)
	//FIELD(wExtra)
	//FIELD(dwPhysDamage)
	//FIELD(dwEnDmgPct)
	//FIELD(dwFireDamage)
	//FIELD(dwBurnDamage)
	//FIELD(dwBurnLen)
	//FIELD(dwLtngDamage)
	//FIELD(dwMagDamage)
	//FIELD(dwColdDamage)
	//FIELD(dwPoisDamage)
	//FIELD(dwPoisLen)
	//FIELD(dwColdLen)
	//FIELD(dwFrzLen)
	//FIELD(dwLifeLeech)
	//FIELD(dwManaLeech)
	//FIELD(dwStamLeech)
	//FIELD(dwStunLen)
	//FIELD(dwAbsLife)
	//FIELD(dwDmgTotal)
	//FIELD(unk0x50)
	//FIELD(dwPiercePct)
	//FIELD(dwDamageRate)
	//FIELD(unk0x5C)
	//FIELD(dwHitClass)
	//FIELD(nHitClassActiveSet)
	//FIELD(nConvType)
	//ARRAY(unk0x66)
	//FIELD(dwConvPct)
	//FIELD(nOverlay)
END_VISIT()

BEGIN_VISIT(D2CombatStrc)
	//POINTER(pGame)
	//FIELD(dwAttackerType)
	//FIELD(dwAttackerId)
	//FIELD(dwDefenderType)
	//FIELD(dwDefenderId)
	//OBJECT(tDamage)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2DamageInfoStrc)
	//POINTER(pGame)
	//POINTER(pDifficultyLevelsTxt)
	//POINTER(pAttacker)
	//POINTER(pDefender)
	//FIELD(bAttackerIsMonster)
	//FIELD(bDefenderIsMonster)
	//POINTER(pDamage)
	//ARRAY(nDamageReduction)
END_VISIT()

BEGIN_VISIT(D2DamageStatTableStrc)
	//FIELD(nOffsetInDamageStrc)
	//FIELD(nResStatId)
	//FIELD(nMaxResStatId)
	//FIELD(nPierceStatId)
	//FIELD(nAbsorbPctStatId)
	//FIELD(nAbsorbStatId)
	//OBJECT(nDamageReductionType)
	//FIELD(unk0x1C)
	//FIELD(unk0x20)
	//POINTER(szName)
	//FIELD(unk0x28)
	//FIELD(pad0x29)
	//FIELD(pad0x2A)
	//FIELD(pad0x2B)
END_VISIT()

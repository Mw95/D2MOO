#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <ITEMS/ItemMode.h>


BEGIN_VISIT(D2UnkItemModeStrc)
	//FIELD(nHitpoints)
	//FIELD(nMana)
	//FIELD(nStamina)
	//FIELD(nRightSkillId)
	//FIELD(nLeftSkillId)
	//FIELD(nRightSkillOwnerGUID)
	//FIELD(nLeftSkillOwnerGUID)
END_VISIT()

BEGIN_VISIT(D2UnkItemModeStrc2)
	//FIELD(nBodyLoc)
	//POINTER(pItem)
	//FIELD(nSwitchBodyLoc)
	//FIELD(nSocketArg)
END_VISIT()

BEGIN_VISIT(D2ItemModeArgStrc)
	//FIELD(bIsBow)
	//FIELD(bIsCrossBow)
	//FIELD(bIsBowQuiver)
	//FIELD(bIsCrossBowQuiver)
	//FIELD(bIsShield)
	//FIELD(bIsWeapon)
	//FIELD(bIsTwoHanded)
	//FIELD(bCanUse2Weapons)
	//FIELD(bIsThrowable)
	//FIELD(bIsRing)
END_VISIT()

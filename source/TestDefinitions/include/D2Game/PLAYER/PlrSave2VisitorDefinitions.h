#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <PLAYER/PlrSave2.h>


BEGIN_VISIT(D2MercSaveDataStrc)
	//FIELD(nFlags)
	//FIELD(nSeed)
	//FIELD(wName)
	//FIELD(nHirelingId)
	//FIELD(nExperience)
	//ARRAY(unk0x10)
END_VISIT()

BEGIN_VISIT(D2SaveSkillKeyStrc)
	//FIELD(nSkill)
	//BEGIN_UNION()
		//FIELD(nKey)
		//FIELD(nKeyEx)
		//FIELD(nItemSlot)
	//END_UNION()
END_VISIT()

BEGIN_VISIT(D2SaveHeaderStrc)
	//FIELD(dwHeaderMagic)
	//FIELD(dwVersion)
	//FIELD(dwSize)
	//FIELD(dwChecksum)
	//FIELD(dwWeaponSwitch)
	//ARRAY(szName)
	//BEGIN_UNION()
		//FIELD(dwSaveFlags)
		//OBJECT(tPackedSaveFlags)
		//FIELD(nUnk)
	//END_UNION()
	//FIELD(nClass)
	//FIELD(nStats)
	//FIELD(nSkills)
	//FIELD(nLevel)
	//FIELD(dwCreateTime)
	//FIELD(dwLasTime)
	//FIELD(dwPlayTime)
	//ARRAY(SkillKeys)
	//FIELD(nLeftSkillId)
	//FIELD(nLeftSkillItemIndex)
	//FIELD(nRightSkillId)
	//FIELD(nRightSkillItemIndex)
	//FIELD(nSwitchLeftSkillId)
	//FIELD(nSwitchLeftSkillItemIndex)
	//FIELD(nSwitchRightSkillId)
	//FIELD(nSwitchRightSkillItemIndex)
	//ARRAY(nComponent)
	//ARRAY(nCompColor)
	//ARRAY(nTown)
	//FIELD(dwMapSeed)
	//OBJECT(MercSaveData)
	//FIELD(nGuildEmblemBgColor)
	//FIELD(dwLastLevel)
	//FIELD(dwLastTown)
	//FIELD(nLastDifficulty)
	//ARRAY(unk0xD9)
END_VISIT()

#if PLRSAVE2_CHECK_LADDER_TIMESTAMP

#else

#endif

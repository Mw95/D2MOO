#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <QUESTS/ACT5/A5Q3.h>


BEGIN_VISIT(D2PrisonOfIceRewardStrc)
	//POINTER(dwItemCodes)
	//FIELD(nItemCount)
END_VISIT()

BEGIN_VISIT(D2Act5Quest3Strc)
	//OBJECT(tPlayerGUIDs)
	//FIELD(unk0x84)
	//FIELD(unk0x88)
	//FIELD(nTimerInvocations)
	//FIELD(bDrehyaIcedMonsterSpawned)
	//FIELD(bDrehyaMonsterInTownSpawned)
	//FIELD(bNilathakOutsideTownSpawned)
	//FIELD(bNihlathakMonsterInTownSpawned)
	//FIELD(nDrehyaMonsterInTownGUID)
	//FIELD(nDrehyaIcedMonsterGUID)
	//FIELD(NihlathakMonsterInTownGUID)
	//FIELD(nNihlathakOutsideTownGUID)
	//FIELD(bFrozenAnyaObjectSpawned)
	//ARRAY(pad0xA5)
	//FIELD(nFrozenDrehyaObjectGUID)
	//FIELD(bMalahIntroActivated)
	//FIELD(bChangeToSpecialObjectModeOutsideTown)
	//FIELD(bChangeToSpecialObjectModeInTown)
	//FIELD(pad0xAF)
	//FIELD(unused0xB0)
	//FIELD(bDrehyaPortalOutsideTownSpawned)
	//FIELD(bDrehyaPortalInTownSpawned)
	//FIELD(unused0xB3)
	//FIELD(nDrehyaPortalInTownGUID)
	//ARRAY(unused0xB8)
	//FIELD(nDrehyaPortalOutsideTownGUID)
	//OBJECT(pDrehyaPortalCoords)
	//ARRAY(unused0xCC)
	//FIELD(nDefrostPotionsInGame)
	//FIELD(nObjectUpdateInvocations)
	//FIELD(bDrehyaPortalCoordsInitialized)
	//FIELD(bDrehyaInTownInitialized)
	//FIELD(bDefrostPotionAcquired)
	//FIELD(bDrehyaIcedRemoved)
	//FIELD(nDrehyaObjectInTownGUID)
	//OBJECT(pDrehyaObjectInTownCoords)
	//OBJECT(pDrehyaObjectOutsideTownCoords)
	//FIELD(nDrehyaObjectOutsideTownGUID)
	//FIELD(nFrozenAnyaObjectGUID)
	//FIELD(bTimerActive)
	//FIELD(bMalahActivated)
	//FIELD(bRewarded)
	//FIELD(pad0x103)
	//POINTER(pDrehyaMapAI)
	//POINTER(pNilathakMapAI)
	//FIELD(bDrehyaMapAIChanged)
	//FIELD(bNilathakMapAIChanged)
	//ARRAY(pad0x10E)
	//FIELD(nNihlathakObjectInTownGUID)
END_VISIT()

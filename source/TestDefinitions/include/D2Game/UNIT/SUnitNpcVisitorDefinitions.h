#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <UNIT/SUnitNpc.h>


BEGIN_VISIT(D2NpcTradeStrc)
	//OBJECT(bVendorInit)
	//FIELD(bHireInit)
	//FIELD(nAct)
	//FIELD(bTrader)
	//FIELD(bLevelRefresh)
	//FIELD(bInited)
	//FIELD(bForceVendor)
	//FIELD(bRefreshInventory)
	//FIELD(dwTicks)
	//OBJECT(pProxy)
	//FIELD(dwUnk)
	//FIELD(dwNPCGUID)
END_VISIT()

BEGIN_VISIT(D2NpcControlStrc)
	//FIELD(nArraySize)
	//POINTER(pFirstRecord)
	//OBJECT(pSeed)
	//FIELD(unk0x10)
END_VISIT()

BEGIN_VISIT(D2NpcGambleStrc)
	//POINTER(pInventory)
	//FIELD(dwGUID)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2NPCMessageListStrc)
	//ARRAY(nMessageIndexes)
END_VISIT()

BEGIN_VISIT(D2NpcVendorChainStrc)
	//FIELD(dwGUID)
	//FIELD(field_4)
	//ARRAY(unk0x05)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2NpcEventStrc)
	//POINTER(pUnit)
	//FIELD(field_4)
	//FIELD(field_8)
	//FIELD(field_C)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2MercDataStrc)
	//FIELD(nMercName)
	//FIELD(nPad)
	//FIELD(dwSeed)
	//FIELD(bHired)
	//FIELD(bAvailable)
END_VISIT()

BEGIN_VISIT(D2NpcRecordStrc)
	//FIELD(nNPC)
	//POINTER(pInventory)
	//POINTER(pGamble)
	//FIELD(bGambleInit)
	//POINTER(pMercData)
	//POINTER(pEvent)
	//POINTER(pVendorChain)
	//FIELD(bTrading)
	//OBJECT(npcTrade)
END_VISIT()

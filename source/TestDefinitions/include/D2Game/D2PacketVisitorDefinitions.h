#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2Packet.h>


BEGIN_VISIT(D2PacketDataStrc)
	//FIELD(nPacketSize)
	//ARRAY(packetData)
	//POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2PacketListStrc)
	//FIELD(nTotal)
	//FIELD(nUsed)
	//FIELD(unk0x08)
	//OMIT(unk0x0C)
END_VISIT()

BEGIN_VISIT(D2PacketTableStrc)
	//OMIT(pCallback1)
	//FIELD(nSize)
	//OMIT(pCallback2)
END_VISIT()

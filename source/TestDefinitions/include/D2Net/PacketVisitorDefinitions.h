#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <Packet.h>


BEGIN_VISIT(D2NetQueuedPacketStrc)
	ARRAY(data)
	FIELD(nPacketSize)
	FIELD(dwReceiveTick)
	POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2NetReceiveBufferStrc)
	ARRAY(data)
	FIELD(nUsedBytes)
END_VISIT()

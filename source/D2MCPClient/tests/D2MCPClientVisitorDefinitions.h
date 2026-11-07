#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <EqualityMacros.h>


#include <D2MCPClient.h>


BEGIN_VISIT(D2MCPGameInfoStrc)
	FIELD(bMoreData)
	FIELD(nRequestId)
	FIELD(pad0x06)
	FIELD(dwIndex)
	FIELD(dwUptime)
	FIELD(nUnk0x10)
	FIELD(nUnk0x11)
	FIELD(nMaxPlayers)
	FIELD(pad0x13)
	FIELD(nPlayers)
	FIELD(nStatus)
	ARRAY(szGameName)
	ARRAY(szGameDescription)
	ARRAY(nPlayerClass)
	ARRAY(nPlayerLevel)
	ARRAY(szPlayerName)
END_VISIT()

BEGIN_VISIT(D2MCPCharListStrc)
	FIELD(nMessageId)
	FIELD(count)
	FIELD(firstChar)
	FIELD(totalChars)
	FIELD(maxCharsAllowed)
END_VISIT()

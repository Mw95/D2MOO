#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <GAME/Game.h>


BEGIN_VISIT(D2ServerCallbackFunctions)
	//OBJECT(pfCloseGame)
	//OBJECT(pfLeaveGame)
	//OBJECT(pfGetDatabaseCharacter)
	//OBJECT(pfSaveDatabaseCharacter)
	//OBJECT(pfServerLogMessage)
	//OBJECT(pfEnterGame)
	//OBJECT(pfFindPlayerToken)
	//OBJECT(pfSaveDatabaseGuild)
	//OBJECT(pfUnlockDatabaseCharacter)
	//OBJECT(unk0x24)
	//OBJECT(pfUpdateCharacterLadder)
	//OBJECT(pfUpdateGameInformation)
	//OBJECT(pfHandlePacket)
	//OBJECT(pfSetGameData)
	//OBJECT(pfRelockDatabaseCharacter)
	//OBJECT(pfLoadComplete)
END_VISIT()

BEGIN_VISIT(D2GameInfoStrc)
	//FIELD(nGameId)
	//FIELD(nInitSeed)
	//FIELD(nClients)
	//FIELD(nPlayers)
	//FIELD(nMonsters)
	//FIELD(nObjects)
	//FIELD(nItems)
	//FIELD(nMissiles)
	//FIELD(nUniqueItems)
	//FIELD(nNPCs)
	//ARRAY(dwLastUsedUnitGUID)
	//FIELD(nPathTowardPct)
	//FIELD(nPathClockPct)
	//FIELD(nPathCounterPct)
	//FIELD(nPathAStarPct)
	//FIELD(nPathFoWallPct)
	//FIELD(nPathTotalCalls)
	//FIELD(nFrames)
	//FIELD(nTime)
	//FIELD(nFrameRate)
	//ARRAY(szGameName)
	//ARRAY(szGamePassword)
	//ARRAY(szGameDescription)
	//FIELD(nArenaTemplate)
	//FIELD(nMaxLevelDifference)
	//FIELD(nMaxPlayers)
	//FIELD(padding0xA7)
	//FIELD(nArenaFlags)
	//OMIT(pMemoryPool)
END_VISIT()

BEGIN_VISIT(D2TargetNodeStrc)
	//POINTER(pUnit)
	//FIELD(unk0x04)
	//POINTER(pNext)
	//POINTER(unk0x0C)
END_VISIT()

#if D2_VERSION_MAJOR <= 1 && D2_VERSION_MINOR <= 10

#else

#endif

BEGIN_VISIT(D2GameDataTableStrc)
	//OBJECT(tHashTable)
END_VISIT()

BEGIN_VISIT(D2GameStatisticsStrc)
	//FIELD(nGamesCount)
	//FIELD(nActiveMonsters)
	//FIELD(nInactiveMonsters)
	//FIELD(nPlayersCount)
END_VISIT()

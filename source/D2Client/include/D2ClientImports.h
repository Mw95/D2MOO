#pragma once

#include <cstdint>
#include <D2BasicTypes.h>

// D2Game exports used by D2Client (single player / open battle.net local server).
// They are declared here instead of including the D2Game headers, which pull in the server-side game structures.

struct D2UnitStrc;
struct D2GameDataTableStrc;

#ifndef D2GAME_DLL_DECL
#define D2GAME_DLL_DECL
#endif

D2GAME_DLL_DECL D2UnitStrc* __stdcall DEBUG_GetUnitFromTypeAndGUID(int32_t nUnitType, int32_t nUnitGUID);	//D2Game.#10025
D2GAME_DLL_DECL int32_t __stdcall GAME_UpdateGamesProgress(int32_t a1);										//D2Game.#10004
D2GAME_DLL_DECL void __stdcall GAME_CloseAllGames();														//D2Game.#10006
D2GAME_DLL_DECL void __stdcall GAME_UpdateClients(int32_t a1, int32_t a2);									//D2Game.#10005
D2GAME_DLL_DECL void __fastcall D2GAME_10036_PLRSAVE_EnableSaveFileWriting(int32_t bWriteSaveFile);		//D2Game.#10036
D2GAME_DLL_DECL void __fastcall GAME_ProcessNetworkMessages();												//D2Game.#10003
D2GAME_DLL_DECL int32_t __stdcall GAME_GetPlayerUnitsCount(uint16_t nGameId);								//D2Game.#10016
D2GAME_DLL_DECL int32_t __stdcall D2Game_10046();															//D2Game.#10046
D2GAME_DLL_DECL void __stdcall GAME_SetGlobalAct(int32_t nAct);												//D2Game.#10009
D2GAME_DLL_DECL void __stdcall GAME_SetInitSeed(int32_t nInitSeed);											//D2Game.#10010
D2GAME_DLL_DECL void __fastcall PLAYER_SetVirtualPlayerCount(int32_t nPlayers);							//D2Game.#10059
D2GAME_DLL_DECL int32_t __stdcall D2Game_10050();															//D2Game.#10050
D2GAME_DLL_DECL void __stdcall GAME_InitGameDataTable(D2GameDataTableStrc* pGameDataTbl, void* pGameList);	//D2Game.#10002

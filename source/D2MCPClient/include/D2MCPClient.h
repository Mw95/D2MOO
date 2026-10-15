#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Dll.h>

// Signatures recovered from the call sites in D2Multi.dll (1.10f).
// Names are kept as ordinals until their exact purpose is known.

D2FUNC_DLL(D2MCPCLIENT, 10000, BOOL, __stdcall, (void* pRealmLogonInfo), 0x0000/*TODO*/)							//D2MCPClient.#10000 Connects to the MCP server with the realm logon info
D2MCPCLIENT_DLL_DECL void __cdecl D2MCPClientCloseMCP();																	//D2MCPClient.#10001
D2FUNC_DLL(D2MCPCLIENT, 10002, BOOL, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10002 Returns TRUE if connected to the MCP
D2FUNC_DLL(D2MCPCLIENT, 10003, BOOL, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10003 Processes the incoming MCP messages
D2FUNC_DLL(D2MCPCLIENT, 10004, void, __fastcall, (void* pCreateGameInfo, uint16_t nRequestId), 0x0000/*TODO*/)		//D2MCPClient.#10004 MCP_CREATEGAME
D2FUNC_DLL(D2MCPCLIENT, 10005, void, __fastcall, (const char* szGameName, const char* szGamePassword, uint16_t nRequestId), 0x0000/*TODO*/)	//D2MCPClient.#10005 MCP_JOINGAME
D2FUNC_DLL(D2MCPCLIENT, 10006, void, __fastcall, (void* pGameListFilter, uint16_t nRequestId), 0x0000/*TODO*/)		//D2MCPClient.#10006 MCP_GAMELIST
D2FUNC_DLL(D2MCPCLIENT, 10007, void, __fastcall, (const char* szGameName, uint16_t nRequestId), 0x0000/*TODO*/)		//D2MCPClient.#10007 MCP_GAMEINFO
D2FUNC_DLL(D2MCPCLIENT, 10009, void, __stdcall, (const char* szCharacterName), 0x0000/*TODO*/)						//D2MCPClient.#10009 MCP_CHARLOGON
D2FUNC_DLL(D2MCPCLIENT, 10012, void, __fastcall, (void(__fastcall* pfLadderDataCallback)(int32_t, int32_t, int32_t, uint8_t, void*), void(__stdcall* pfLadderDoneCallback)()), 0x0000/*TODO*/)	//D2MCPClient.#10012 Sets the ladder callbacks
D2FUNC_DLL(D2MCPCLIENT, 10015, const char*, __fastcall, (), 0x0000/*TODO*/)											//D2MCPClient.#10015 Returns the game server IP of the last joined game
D2FUNC_DLL(D2MCPCLIENT, 10016, uint16_t, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10016 Returns the request id of the last game response
D2FUNC_DLL(D2MCPCLIENT, 10017, uint16_t, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10017 Returns the game token of the last joined game
D2FUNC_DLL(D2MCPCLIENT, 10018, uint32_t, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10018 Returns the join token of the last joined game
D2FUNC_DLL(D2MCPCLIENT, 10019, void*, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10019 Returns the current game list/info message
D2FUNC_DLL(D2MCPCLIENT, 10020, void, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10020 Pops the current game list/info message
D2FUNC_DLL(D2MCPCLIENT, 10027, void, __fastcall, (uint8_t nLadderType, int32_t nStart), 0x0000/*TODO*/)				//D2MCPClient.#10027 MCP_REQUESTLADDERDATA
D2FUNC_DLL(D2MCPCLIENT, 10030, void, __stdcall, (int32_t a1), 0x0000/*TODO*/)											//D2MCPClient.#10030
D2FUNC_DLL(D2MCPCLIENT, 10031, BOOL, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10031
D2FUNC_DLL(D2MCPCLIENT, 10046, int32_t, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10046 Returns the status of the last MCP request
D2FUNC_DLL(D2MCPCLIENT, 10048, void, __fastcall, (void(__fastcall* pfMotdCallback)(int32_t, int32_t, const char*)), 0x0000/*TODO*/)	//D2MCPClient.#10048 Sets the MOTD callback
D2FUNC_DLL(D2MCPCLIENT, 10049, void, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10049 MCP_MOTD
D2FUNC_DLL(D2MCPCLIENT, 10050, int32_t, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10050
D2FUNC_DLL(D2MCPCLIENT, 10052, BOOL, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10052 Returns TRUE if the game creation queue is active
D2FUNC_DLL(D2MCPCLIENT, 10053, void, __stdcall, (BOOL bEnable), 0x0000/*TODO*/)										//D2MCPClient.#10053
D2FUNC_DLL(D2MCPCLIENT, 10054, void, __fastcall, (), 0x0000/*TODO*/)													//D2MCPClient.#10054 Cancels the game creation queue
D2FUNC_DLL(D2MCPCLIENT, 10055, HANDLE, __fastcall, (), 0x0000/*TODO*/)												//D2MCPClient.#10055 Returns the connection event handle
D2FUNC_DLL(D2MCPCLIENT, 10059, void, __fastcall, (const char* szCharacterName, BOOL bHardcore, BOOL bExpansion), 0x0000/*TODO*/)	//D2MCPClient.#10059 MCP_CHARLADDERREQUEST

#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Dll.h>

//D2MCPClient.#10001
D2MCPCLIENT_DLL_DECL void __cdecl D2MCPClientCloseMCP();

// Functions not implemented yet, only used by D2Launch.dll for now.
// Note: the names reflect their observed usage, the actual behaviour has not been reimplemented.
D2FUNC_DLL(D2MCPCLIENT, 10000, BOOL, __stdcall, (void* pRealmLogonPacket), 0x0)						//D2MCPClient.#10000 Starts the realm (MCP) logon with the packet returned by BnClientInterface::LogonRealm
D2FUNC_DLL(D2MCPCLIENT, 10002, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10002 Is connected to the realm
D2FUNC_DLL(D2MCPCLIENT, 10003, void, __stdcall, (), 0x0)											//D2MCPClient.#10003 Processes the pending packets
D2FUNC_DLL(D2MCPCLIENT, 10008, void, __stdcall, (const char* szName, int32_t nClass, uint16_t nSaveFlags), 0x0)	//D2MCPClient.#10008 Sends a character creation request
D2FUNC_DLL(D2MCPCLIENT, 10009, void, __stdcall, (const char* szName), 0x0)							//D2MCPClient.#10009 Sends a character logon request
D2FUNC_DLL(D2MCPCLIENT, 10021, void, __fastcall, (const char* szName, int32_t nUnused), 0x0)		//D2MCPClient.#10021 Sends a character deletion request
D2FUNC_DLL(D2MCPCLIENT, 10028, void, __stdcall, (int32_t nUnused), 0x0)							//D2MCPClient.#10028 Ends the character creation request
D2FUNC_DLL(D2MCPCLIENT, 10029, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10029 Is the character creation request done
D2FUNC_DLL(D2MCPCLIENT, 10030, void, __stdcall, (int32_t nUnused), 0x0)							//D2MCPClient.#10030 Ends the character logon request
D2FUNC_DLL(D2MCPCLIENT, 10031, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10031 Is the character logon request done
D2FUNC_DLL(D2MCPCLIENT, 10032, void, __stdcall, (int32_t nUnused), 0x0)							//D2MCPClient.#10032 Ends the character deletion request
D2FUNC_DLL(D2MCPCLIENT, 10033, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10033 Is the character deletion request done
D2FUNC_DLL(D2MCPCLIENT, 10046, int32_t, __stdcall, (), 0x0)										//D2MCPClient.#10046 Returns the last error
D2FUNC_DLL(D2MCPCLIENT, 10055, HANDLE, __stdcall, (), 0x0)										//D2MCPClient.#10055 Returns the event signaled when the realm logon is done
D2FUNC_DLL(D2MCPCLIENT, 10056, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10056 Is the character list request pending
D2FUNC_DLL(D2MCPCLIENT, 10057, uint8_t*, __stdcall, (), 0x0)										//D2MCPClient.#10057 Returns the character list packet
D2FUNC_DLL(D2MCPCLIENT, 10058, void, __stdcall, (int32_t nUnused1, int32_t nUnused2), 0x0)		//D2MCPClient.#10058 Sends a character list request
D2FUNC_DLL(D2MCPCLIENT, 10060, void, __stdcall, (int32_t nUnused), 0x0)							//D2MCPClient.#10060 Ends the character upgrade request
D2FUNC_DLL(D2MCPCLIENT, 10061, BOOL, __stdcall, (), 0x0)											//D2MCPClient.#10061 Is the character upgrade request done
D2FUNC_DLL(D2MCPCLIENT, 10062, void, __fastcall, (const char* szName), 0x0)						//D2MCPClient.#10062 Sends a character upgrade (to expansion) request

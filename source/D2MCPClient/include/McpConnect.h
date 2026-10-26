#pragma once


#include <cstdint>

#include <Windows.h>

#include "D2MCPClient.h"


struct FClientConnection;

// Max size of a message, both sent and received
constexpr uint32_t MCP_MESSAGE_BUFFER_SIZE = 0x400;

// Connection to the realm server, nullptr when closed
//D2MCPClient.0x6FA02E58
extern FClientConnection* gpMCPConnection;
// Request id of the last request sent with one, answers with another request id are ignored
//D2MCPClient.0x6FA02CD0
extern uint16_t gnMCPPendingRequestId;
//D2MCPClient.0x6FA02CCC
extern uint32_t gdwMCPGameToken;


// Handles a message polled by D2MCPClientProcessMessages
//D2MCPClient.0x6F9F16F0
BOOL __fastcall MCP_DispatchMessage(const uint8_t* pMessage, uint32_t nMessageSize);
// Fog connection callback, called from the network thread for each received message.
// Only handles MCP_STARTUP, other messages are left in the queue (returns FALSE) for D2MCPClientProcessMessages.
//D2MCPClient.0x6F9F1730
BOOL __fastcall MCP_DispatchConnectionMessage(const uint8_t* pMessage, uint32_t nMessageSize, void* pUserData);

// Sends MCP_STARTUP, the first message after selecting the protocol
//D2MCPClient.0x6F9F1F20
BOOL __fastcall TOMCP_Startup(const D2MCPConnectInfoStrc* pConnectInfo);

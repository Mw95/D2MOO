#pragma once

// Private declarations shared between the Storm source files.
// Everything that is exported lives in Storm.h, this header only contains what the
// different modules of Storm.dll share internally.

#include <Windows.h>
#include <cstdint>
#include <cstddef>
#include <new>
#include <typeinfo>

#include <Storm.h>

// Storm 1.08b (shipped with Diablo II 1.10f)
#define STORM_VERSION_STRING "1.08b"

// Storm error codes (see the message table of Storm.dll)
enum StormError : uint32_t
{
	STORM_ERROR_ASSERTION                = 0x85100000,
	STORM_ERROR_BAD_ARGUMENT             = 0x85100065,
	STORM_ERROR_GAME_ALREADY_STARTED     = 0x85100066,
	STORM_ERROR_GAME_FULL                = 0x85100067,
	STORM_ERROR_GAME_NOT_FOUND           = 0x85100068,
	STORM_ERROR_GAME_TERMINATED          = 0x85100069,
	STORM_ERROR_INVALID_PLAYER           = 0x8510006A,
	STORM_ERROR_NO_MESSAGES_WAITING      = 0x8510006B,
	STORM_ERROR_NOT_ARCHIVE              = 0x8510006C,
	STORM_ERROR_NOT_ENOUGH_ARGUMENTS     = 0x8510006D,
	STORM_ERROR_NOT_IMPLEMENTED          = 0x8510006E,
	STORM_ERROR_NOT_IN_ARCHIVE           = 0x8510006F,
	STORM_ERROR_NOT_IN_GAME              = 0x85100070,
	STORM_ERROR_NOT_INITIALIZED          = 0x85100071,
	STORM_ERROR_NOT_PLAYING              = 0x85100072,
	STORM_ERROR_NOT_REGISTERED           = 0x85100073,
	STORM_ERROR_REQUIRES_CODEC1          = 0x85100074,
	STORM_ERROR_REQUIRES_CODEC2          = 0x85100075,
	STORM_ERROR_REQUIRES_CODEC3          = 0x85100076,
	STORM_ERROR_REQUIRES_UPGRADE         = 0x85100077,
	STORM_ERROR_STILL_ACTIVE             = 0x85100078,
	STORM_ERROR_VERSION_MISMATCH         = 0x85100079,
	STORM_ERROR_MEMORY_ALREADY_FREED     = 0x8510007A,
	STORM_ERROR_MEMORY_CORRUPT           = 0x8510007B,
	STORM_ERROR_MEMORY_INVALID_BLOCK     = 0x8510007C,
	STORM_ERROR_MEMORY_MANAGER_INACTIVE  = 0x8510007D,
	STORM_ERROR_MEMORY_NEVER_RELEASED    = 0x8510007E,
	STORM_ERROR_HANDLE_NEVER_RELEASED    = 0x8510007F,
	STORM_ERROR_ACCESS_OUT_OF_BOUNDS     = 0x85100080,
	STORM_ERROR_MEMORY_NULL_POINTER      = 0x85100081,
	STORM_ERROR_CDKEY_MISMATCH           = 0x85100082,
	STORM_ERROR_FILE_CORRUPTED           = 0x85100083,
	STORM_ERROR_FATAL                    = 0x85100084,
	STORM_ERROR_GAMETYPE_UNAVAILABLE     = 0x85100085,
};

// Validates arguments the same way Storm does: sets ERROR_INVALID_PARAMETER and returns.
#define STORM_VALIDATE_BEGIN { bool __stormValid = true;
#define STORM_VALIDATE_ARG(x) __stormValid = __stormValid && (x);
#define STORM_VALIDATE_END(...) if (!__stormValid) { SErrSetLastError(ERROR_INVALID_PARAMETER); return __VA_ARGS__; } }
#define STORM_VALIDATE_END_VOID if (!__stormValid) { SErrSetLastError(ERROR_INVALID_PARAMETER); return; } }

#define STORM_ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))

// The original binary aborts through SErrDisplayError with the "Object:" (-2) or "Handle:" (-3) line marker.
#define SERR_LINECODE_FUNCTION  (-1)
#define SERR_LINECODE_OBJECT    (-2)
#define SERR_LINECODE_HANDLE    (-3)
#define SERR_LINECODE_FILE      (-4)

//////////////////////////////////////////////////////////////////////////////
// Storm.cpp
//////////////////////////////////////////////////////////////////////////////

// Values controlled by StormSetOption
extern uint32_t gStormOptionReportMemoryLeaksToDebugger;  // Option 3
extern uint32_t gStormOptionReportHandleLeaksToDebugger;  // Option 1
extern uint32_t gStormOptionDdaBufferSize;                // Option 2
extern uint32_t gStormOptionSFileOption4;                 // Option 4
extern uint32_t gStormOptionWriteLogsToDebugger;          // Option 5

void StormProcessAttach(HINSTANCE hInstance, BOOL bDynamicLoad);
void StormProcessDetach();

// Module destruction functions called by StormDestroy
BOOL SDlgDestroy();
BOOL SGdiDestroy();
BOOL SRgnDestroy();
BOOL SMsgDestroy();
BOOL SEvtDestroy();
BOOL SBltDestroy();
BOOL SCodeDestroy();
BOOL SCmdDestroy();
BOOL SStrDestroy();
BOOL STransDestroy();

//////////////////////////////////////////////////////////////////////////////
// SErr.cpp
//////////////////////////////////////////////////////////////////////////////

void SErrInitialize();
void SErrDestroy();
// Storm.0x6FFC1FD0 / Storm.0x6FFC2010
void SErrEnterCriticalSection();
void SErrLeaveCriticalSection();

//////////////////////////////////////////////////////////////////////////////
// SMem.cpp
//////////////////////////////////////////////////////////////////////////////

void SMemInitialize();
BOOL SMemDestroy();

// Storm.0x6FFCBD30
void SMemReportError(uint32_t errorCode, const char* filename, int32_t linenumber);

//////////////////////////////////////////////////////////////////////////////
// SStr.cpp
//////////////////////////////////////////////////////////////////////////////

void SStrInitialize();

//////////////////////////////////////////////////////////////////////////////
// SLog.cpp
//////////////////////////////////////////////////////////////////////////////

void SLogInitialize();
void SLogDestroy();

//////////////////////////////////////////////////////////////////////////////
// SBlt.cpp
//////////////////////////////////////////////////////////////////////////////

void SBltInitialize();

//////////////////////////////////////////////////////////////////////////////
// SFile.cpp
//////////////////////////////////////////////////////////////////////////////

void SFileInitializeCryptTable();

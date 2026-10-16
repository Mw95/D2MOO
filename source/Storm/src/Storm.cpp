#include "StormInternal.h"

// Storm.dll initializes its logs and memory manager before running the C++ static initializers,
// and destroys them after the static destructors. Reproduce this with a library level initializer.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4073) // initializers put in library initialization area
#pragma init_seg(lib)
#pragma warning(pop)
#define STORM_INIT_PRIORITY
#elif defined(__GNUC__)
#define STORM_INIT_PRIORITY __attribute__((init_priority(101)))
#else
#define STORM_INIT_PRIORITY
#endif

// Storm.0x6FFECF50
uint32_t gStormOptionReportMemoryLeaksToDebugger;
// Storm.0x6FFECF54
uint32_t gStormOptionReportHandleLeaksToDebugger;
// Storm.0x6FFECF58
uint32_t gStormOptionDdaBufferSize;
// Storm.0x6FFECF5C
uint32_t gStormOptionSFileOption4;
// Storm.0x6FFECF64
uint32_t gStormOptionWriteLogsToDebugger;

// Storm.0x6FFECF68
static HMODULE sghStormInstance;
// Storm.0x6FFECF6C
static LPTOP_LEVEL_EXCEPTION_FILTER sgpfnPreviousExceptionFilter;

struct StormRuntime
{
	// Storm.0x6FFD9E80
	StormRuntime()
	{
		SLogInitialize();
		SMemInitialize();
	}

	// Storm.0x6FFD9E10
	~StormRuntime()
	{
		SMemDestroy();
		SErrDestroy();
		SLogDestroy();
	}
};

static StormRuntime sgStormRuntime STORM_INIT_PRIORITY;


// Storm.0x6FFDB2C0
static LONG WINAPI StormUnhandledExceptionFilter(EXCEPTION_POINTERS* pExceptionInfo)
{
	SErrSuppressErrors(TRUE);
	SLogFlushAll();
	if (sgpfnPreviousExceptionFilter)
	{
		return sgpfnPreviousExceptionFilter(pExceptionInfo);
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

// Storm.0x6FFDB2F0
static void StormInitializeModules()
{
	SBltInitialize();
	SStrInitialize();
}

// Storm.0x6FFDB260
void StormProcessAttach(HINSTANCE hInstance, BOOL bDynamicLoad)
{
	sghStormInstance = hInstance;
	sgpfnPreviousExceptionFilter = SetUnhandledExceptionFilter(StormUnhandledExceptionFilter);
	StormInitializeModules();
	if (bDynamicLoad)
	{
		SFileInitializeCryptTable();
	}
}

// Storm.0x6FFDB260
void StormProcessDetach()
{
	SetUnhandledExceptionFilter(sgpfnPreviousExceptionFilter);
	StormDestroy();
}

// Storm.#301
BOOL __cdecl StormDestroy()
{
	SDlgDestroy();
	SGdiDestroy();
	SVidDestroy();
	SDrawDestroy();
	SRgnDestroy();
	SMsgDestroy();
	SNetDestroy();
	SEvtDestroy();
	SBltDestroy();
	SCodeDestroy();
	SCmdDestroy();
	SFileDestroy();
	SStrDestroy();
	STransDestroy();
	return TRUE;
}

// Storm.#302
HMODULE __cdecl StormGetInstance()
{
	return sghStormInstance;
}

// Storm.#303
BOOL __stdcall StormGetOption(uint32_t type, void* optval, uint32_t* optlen)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(optval);
	STORM_VALIDATE_ARG(optlen);
	STORM_VALIDATE_END(FALSE);

	SErrSetLastError(ERROR_INVALID_PARAMETER);

	uint32_t nValue;
	switch (type)
	{
	case STORM_OPTION_REPORT_HANDLE_LEAKS_TO_DEBUGGER:
		nValue = gStormOptionReportHandleLeaksToDebugger;
		break;
	case STORM_OPTION_DDA_BUFFER_SIZE:
		nValue = gStormOptionDdaBufferSize;
		break;
	case STORM_OPTION_REPORT_MEMORY_LEAKS_TO_DEBUGGER:
		nValue = gStormOptionReportMemoryLeaksToDebugger;
		break;
	case STORM_OPTION_SFILE_OPTION4:
		nValue = gStormOptionSFileOption4;
		break;
	case STORM_OPTION_WRITE_LOGS_TO_DEBUGGER:
		nValue = gStormOptionWriteLogsToDebugger;
		break;
	default:
		SErrSetLastError(ERROR_SUCCESS);
		return TRUE;
	}

	if (*optlen < sizeof(uint32_t))
	{
		return FALSE;
	}

	*(uint32_t*)optval = nValue;
	*optlen = sizeof(uint32_t);
	SErrSetLastError(ERROR_SUCCESS);
	return TRUE;
}

// Storm.#304
BOOL __stdcall StormSetOption(uint32_t type, const void* optval, uint32_t optlen)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(optval);
	STORM_VALIDATE_END(FALSE);

	SErrSetLastError(ERROR_INVALID_PARAMETER);

	uint32_t* pOption;
	switch (type)
	{
	case STORM_OPTION_REPORT_HANDLE_LEAKS_TO_DEBUGGER:
		pOption = &gStormOptionReportHandleLeaksToDebugger;
		break;
	case STORM_OPTION_DDA_BUFFER_SIZE:
		pOption = &gStormOptionDdaBufferSize;
		break;
	case STORM_OPTION_REPORT_MEMORY_LEAKS_TO_DEBUGGER:
		pOption = &gStormOptionReportMemoryLeaksToDebugger;
		break;
	case STORM_OPTION_SFILE_OPTION4:
		pOption = &gStormOptionSFileOption4;
		break;
	case STORM_OPTION_WRITE_LOGS_TO_DEBUGGER:
		pOption = &gStormOptionWriteLogsToDebugger;
		break;
	default:
		SErrSetLastError(ERROR_SUCCESS);
		return TRUE;
	}

	if (optlen != sizeof(uint32_t))
	{
		return FALSE;
	}

	const uint32_t nValue = *(const uint32_t*)optval;
	if (type == STORM_OPTION_DDA_BUFFER_SIZE)
	{
		// Must be a power of 2
		if (!nValue || ((nValue - 1) ^ nValue) != nValue * 2 - 1)
		{
			return FALSE;
		}
	}

	*pOption = nValue;
	SErrSetLastError(ERROR_SUCCESS);
	return TRUE;
}

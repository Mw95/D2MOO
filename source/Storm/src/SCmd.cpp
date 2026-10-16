#include "StormInternal.h"

#include <cstdlib>
#include <cstring>
#include <storm/List.hpp>

// Command line parsing

#define SCMD_FILENAME "C:\\projects\\D2\\head\\Diablo2\\3rdParty\\STORM\\SOURCE\\SCMD.CPP"
#define SCMD_MAX_NAME 16

// Storm.0x6FFE5A34 / Storm.0x6FFE5A48
static const char sgszTokenDelimiters[] = " ,;\"\t\n\r\x1A";

struct CMDDEF : TSLinkedNode<CMDDEF>
{
	uint32_t dwFlags;                   // 0x08
	uint32_t dwId;                      // 0x0C
	char szName[SCMD_MAX_NAME];         // 0x10
	int32_t nNameLength;                // 0x20
	uint32_t dwSetValue;                // 0x24
	uint32_t dwSetMask;                 // 0x28
	void* pVariable;                    // 0x2C
	uint32_t nVariableSize;             // 0x30
	SCMDCALLBACK pfnCallback;           // 0x34
	BOOL bFound;                        // 0x38
	union                               // 0x3C
	{
		uint32_t dwValue;
		char* szValue;
	};
};

// State of a switch that is waiting for its value
struct SCMDPARSESTATE
{
	CMDDEF* pPendingDef;                // 0x00
	char szName[SCMD_MAX_NAME];         // 0x04
	int32_t nNameLength;                // 0x14
};

// Storm.0x6FFE9B94 : arguments without name, in order
static STORM_LIST(CMDDEF) sgPositionalList;
// Storm.0x6FFE9BA0 : switches
static STORM_LIST(CMDDEF) sgSwitchList;
// Storm.0x6FFE9BAC
static BOOL sgbHasOptionalPositional;
// Storm.0x6FFE9BB0
static const char sgszEmpty[2] = "";


static inline STORM_LIST(CMDDEF)* SCmdGetList(int32_t nList)
{
	return nList ? &sgSwitchList : &sgPositionalList;
}

static CMDDEF* SCmdFindById(uint32_t dwId)
{
	for (int32_t nList = 0; nList <= 1; ++nList)
	{
		for (CMDDEF* pDef = SCmdGetList(nList)->Head(); pDef; pDef = pDef->Next())
		{
			if (pDef->dwId == dwId)
			{
				return pDef;
			}
		}
	}
	return nullptr;
}

// Storm.0x6FFB8270
static void SCmdReportError(SCMDERRORCALLBACK pfnErrorCallback, uint32_t dwErrorCode, const char* szItem)
{
	uint32_t nString;
	if (dwErrorCode == ERROR_OPEN_FAILED)
	{
		nString = 2;
	}
	else if (dwErrorCode == STORM_ERROR_BAD_ARGUMENT)
	{
		nString = 0;
	}
	else if (dwErrorCode == STORM_ERROR_NOT_ENOUGH_ARGUMENTS)
	{
		nString = 1;
	}
	else
	{
		return;
	}

	// Storm.0x6FFE16B8
	static const char* const szDefaultStrings[] =
	{
		"Invalid argument: %s",
		"The syntax of the command is incorrect.",
		"Unable to open response file: %s",
	};

	char szFormat[256];
	szFormat[0] = '\0';
	LoadStringA(StormGetInstance(), 0x5201 + nString, szFormat, sizeof(szFormat));
	if (!szFormat[0])
	{
		SStrCopy(szFormat, szDefaultStrings[nString], sizeof(szFormat));
	}

	char szMessage[256];
	if (strstr(szFormat, "%s"))
	{
		wsprintfA(szMessage, szFormat, szItem);
	}
	else
	{
		SStrCopy(szMessage, szFormat, sizeof(szMessage));
	}

	if (szMessage[0])
	{
		SStrNCat(szMessage, "\n", sizeof(szMessage));
	}

	SErrSetLastError(dwErrorCode);

	SCMDERROR error;
	error.dwErrorCode = dwErrorCode;
	error.szItem = szItem;
	error.szErrorString = szMessage;
	pfnErrorCallback(&error);
}

// Storm.0x6FFB8860
// Finds the switch with the longest name matching the beginning of szName, starting at pDef
static CMDDEF* SCmdFindBestSwitch(const char* szName, CMDDEF* pDef, int32_t nMinLength)
{
	const int32_t nLength = SStrLen(szName);
	int32_t nBestLength = nMinLength - 1;
	CMDDEF* pBest = nullptr;
	for (; pDef; pDef = pDef->Next())
	{
		if (pDef->nNameLength > nBestLength && pDef->nNameLength <= nLength)
		{
			const int nCompare = (pDef->dwFlags & SCMD_CASESENSITIVE)
				? strncmp(pDef->szName, szName, pDef->nNameLength)
				: _strnicmp(pDef->szName, szName, pDef->nNameLength);
			if (!nCompare)
			{
				nBestLength = pDef->nNameLength;
				pBest = pDef;
			}
		}
	}
	return pBest;
}

// Storm.0x6FFB8680
static void SCmdSetBool(CMDDEF* pDef, const char* szText, uint32_t* pConsumed)
{
	BOOL bSet;
	if (*szText == '-')
	{
		bSet = FALSE;
		*pConsumed = 1;
	}
	else if (*szText == '+')
	{
		bSet = TRUE;
		*pConsumed = 1;
	}
	else
	{
		bSet = !(pDef->dwFlags & SCMD_BOOL_CLEAR);
	}

	const uint32_t dwKeepMask = ~pDef->dwSetMask;
	pDef->dwValue &= dwKeepMask;
	if (bSet)
	{
		pDef->dwValue |= pDef->dwSetValue;
	}

	if (uint32_t* pVariable = (uint32_t*)pDef->pVariable)
	{
		*pVariable &= dwKeepMask;
		if (bSet)
		{
			*pVariable |= pDef->dwSetValue;
		}
	}
}

// Storm.0x6FFB86F0
static void SCmdSetNumber(CMDDEF* pDef, const char* szText, uint32_t* pConsumed)
{
	char* pEnd = nullptr;
	if ((pDef->dwFlags & SCMD_NUM_SIGNED) == SCMD_NUM_SIGNED)
	{
		pDef->dwValue = strtol(szText, &pEnd, 0);
	}
	else
	{
		pDef->dwValue = strtoul(szText, &pEnd, 0);
	}

	if (pEnd)
	{
		*pConsumed = pEnd - szText;
	}
	else
	{
		*pConsumed = SStrLen(szText);
	}

	if (pDef->pVariable)
	{
		SMemCopy(pDef->pVariable, &pDef->dwValue, pDef->nVariableSize > sizeof(uint32_t) ? sizeof(uint32_t) : pDef->nVariableSize);
	}
}

// Storm.0x6FFB8770
static void SCmdSetString(CMDDEF* pDef, const char* szText, uint32_t* pConsumed)
{
	*pConsumed = SStrLen(szText);
	if (pDef->szValue)
	{
		SMemFree(pDef->szValue, SCMD_FILENAME, 139, 0);
	}
	pDef->szValue = (char*)SMemAlloc(SStrLen(szText) + 1, SCMD_FILENAME, 140, 0);
	SStrCopy(pDef->szValue, szText, STORM_MAX_STR);

	if (pDef->pVariable)
	{
		SStrCopy((char*)pDef->pVariable, szText, pDef->nVariableSize);
	}
}

// Storm.0x6FFB8510
static BOOL SCmdSetValue(CMDDEF* pDef, const char* szText, uint32_t* pConsumed)
{
	*pConsumed = 0;
	switch (pDef->dwFlags & SCMD_TYPE_MASK)
	{
	case SCMD_TYPE_BOOL:
		SCmdSetBool(pDef, szText, pConsumed);
		break;
	case SCMD_TYPE_NUMBER:
		SCmdSetNumber(pDef, szText, pConsumed);
		break;
	case SCMD_TYPE_STRING:
		SCmdSetString(pDef, szText, pConsumed);
		break;
	default:
		return FALSE;
	}

	pDef->bFound = TRUE;
	if (pDef->pfnCallback)
	{
		SCMDCALLBACKDATA data;
		data.dwFlags = pDef->dwFlags;
		data.dwId = pDef->dwId;
		data.szName = pDef->szName;
		data.pVariable = pDef->pVariable;
		data.dwSetValue = pDef->dwSetValue;
		data.dwSetMask = pDef->dwSetMask;
		data.dwValue = pDef->dwValue;
		if (!pDef->pfnCallback(&data, szText))
		{
			return FALSE;
		}
	}

	// Propagate the value to the other definitions sharing the same identifier
	for (int32_t nList = 0; nList <= 1; ++nList)
	{
		for (CMDDEF* pOther = SCmdGetList(nList)->Head(); pOther; pOther = pOther->Next())
		{
			const uint32_t dwType = pOther->dwFlags & SCMD_TYPE_MASK;
			if (pOther->dwId != pDef->dwId || dwType != (pDef->dwFlags & SCMD_TYPE_MASK) || pOther == pDef)
			{
				continue;
			}

			pOther->bFound = TRUE;
			if (dwType == SCMD_TYPE_STRING)
			{
				if (pOther->szValue)
				{
					SMemFree(pOther->szValue, SCMD_FILENAME, 288, 0);
				}
				pOther->szValue = (char*)SMemAlloc(SStrLen(pDef->szValue) + 1, SCMD_FILENAME, 289, 0);
				SStrCopy(pOther->szValue, pDef->szValue, STORM_MAX_STR);
			}
			else
			{
				pOther->dwValue = pDef->dwValue;
			}
		}
	}
	return TRUE;
}

// Storm.0x6FFB87E0
// Applies a value to the pending switch, and every other switch with the same name
static BOOL SCmdApplySwitchValue(const char* szText, SCMDPARSESTATE* pState, uint32_t* pConsumed)
{
	*pConsumed = 0;
	CMDDEF* pDef = pState->pPendingDef;
	pState->pPendingDef = nullptr;
	while (pDef)
	{
		uint32_t nConsumed;
		if (!SCmdSetValue(pDef, szText, &nConsumed))
		{
			return FALSE;
		}

		if ((int32_t)*pConsumed <= (int32_t)nConsumed)
		{
			*pConsumed = nConsumed;
		}
		pDef = SCmdFindBestSwitch(pState->szName, pDef->Next(), pState->nNameLength);
	}
	return TRUE;
}

// Storm.0x6FFB89A0
// Parses the switches following a '-' or '/'. Several switches can be grouped (ex: -abc).
static BOOL SCmdProcessSwitches(const char* szText, SCMDPARSESTATE* pState, SCMDERRORCALLBACK pfnErrorCallback)
{
	char szName[256];
	szName[0] = '\0';
	while (*szText)
	{
		const int32_t nTextLength = SStrLen(szText);

		// Try to find a switch, reusing the beginning of the previous switch name
		int32_t nPrefixLength = SStrLen(szName) < 1 ? 1 : SStrLen(szName);
		CMDDEF* pDef = nullptr;
		while (nPrefixLength)
		{
			--nPrefixLength;
			if (nTextLength + nPrefixLength < (int32_t)sizeof(szName))
			{
				SStrCopy(&szName[nPrefixLength], szText, sizeof(szName));
				pDef = SCmdFindBestSwitch(szName, sgSwitchList.Head(), 0);
				if (pDef)
				{
					nPrefixLength = pDef->nNameLength;
					szName[nPrefixLength] = '\0';
					break;
				}
			}
		}

		if (!pDef)
		{
			if (pfnErrorCallback)
			{
				SCmdReportError(pfnErrorCallback, STORM_ERROR_BAD_ARGUMENT, szText);
			}
			return FALSE;
		}

		const char* pValue = &szText[nPrefixLength];
		if (SStrChr("=:", *pValue))
		{
			do
			{
				++pValue;
			}
			while (SStrChr("=:", *pValue));
		}

		pState->pPendingDef = pDef;
		pState->nNameLength = nPrefixLength;
		SStrCopy(pState->szName, szName, STORM_MAX_STR);

		// The value of the switch is the next token
		if (!*pValue && (pDef->dwFlags & SCMD_TYPE_MASK))
		{
			return TRUE;
		}

		uint32_t nConsumed;
		if (!SCmdApplySwitchValue(pValue, pState, &nConsumed))
		{
			return FALSE;
		}

		szText = pValue + nConsumed;
	}
	return TRUE;
}

static BOOL SCmdProcessTokens(const char** pszCommandLine, SCMDPARSESTATE* pState, CMDDEF** ppPositional, SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback);

// Storm.0x6FFB88D0
static BOOL SCmdProcessResponseFile(const char* szFilename, SCMDPARSESTATE* pState, CMDDEF** ppPositional, SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback)
{
	HANDLE hFile = CreateFileA(szFilename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		if (pfnErrorCallback)
		{
			SCmdReportError(pfnErrorCallback, ERROR_OPEN_FAILED, szFilename);
		}
		return FALSE;
	}

	const DWORD dwFileSize = GetFileSize(hFile, nullptr);
	char* pBuffer = (char*)SMemAlloc(dwFileSize + 1, SCMD_FILENAME, 339, 0);
	DWORD dwRead;
	ReadFile(hFile, pBuffer, dwFileSize, &dwRead, nullptr);
	CloseHandle(hFile);
	pBuffer[dwRead] = '\0';

	const char* szCommandLine = pBuffer;
	const BOOL bResult = SCmdProcessTokens(&szCommandLine, pState, ppPositional, pfnExtraCallback, pfnErrorCallback);
	SMemFree(pBuffer, SCMD_FILENAME, 356, 0);
	return bResult;
}

// Storm.0x6FFB8430
static BOOL SCmdProcessToken(const char* szToken, BOOL bQuoted, SCMDPARSESTATE* pState, CMDDEF** ppPositional, SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback)
{
	if (*szToken == '@' && !bQuoted)
	{
		return SCmdProcessResponseFile(szToken + 1, pState, ppPositional, pfnExtraCallback, pfnErrorCallback);
	}

	if (SStrChr("-/", *szToken) && !bQuoted)
	{
		pState->pPendingDef = nullptr;
		return SCmdProcessSwitches(szToken + 1, pState, pfnErrorCallback);
	}

	uint32_t nConsumed;
	if (pState->pPendingDef)
	{
		return SCmdApplySwitchValue(szToken, pState, &nConsumed);
	}

	if (*ppPositional)
	{
		if (!SCmdSetValue(*ppPositional, szToken, &nConsumed))
		{
			return FALSE;
		}
		*ppPositional = (*ppPositional)->Next();
		return TRUE;
	}

	if (pfnExtraCallback)
	{
		return pfnExtraCallback(szToken);
	}

	if (pfnErrorCallback)
	{
		SCmdReportError(pfnErrorCallback, STORM_ERROR_BAD_ARGUMENT, szToken);
	}
	return FALSE;
}

// Storm.0x6FFB8390
static BOOL SCmdProcessTokens(const char** pszCommandLine, SCMDPARSESTATE* pState, CMDDEF** ppPositional, SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback)
{
	while (**pszCommandLine)
	{
		const char* szNext = *pszCommandLine;
		BOOL bQuoted = FALSE;
		char szToken[256];
		SStrTokenize(&szNext, szToken, sizeof(szToken), sgszTokenDelimiters, &bQuoted);
		if (szToken[0] && !SCmdProcessToken(szToken, bQuoted, pState, ppPositional, pfnExtraCallback, pfnErrorCallback))
		{
			break;
		}
		*pszCommandLine = szNext;
	}
	return !**pszCommandLine;
}

// Storm.0x6FFB7FD0
BOOL SCmdDestroy()
{
	for (int32_t nList = 0; nList <= 1; ++nList)
	{
		for (CMDDEF* pDef = SCmdGetList(nList)->Head(); pDef; pDef = pDef->Next())
		{
			if ((pDef->dwFlags & SCMD_TYPE_MASK) == SCMD_TYPE_STRING && pDef->szValue)
			{
				SMemFree(pDef->szValue, SCMD_FILENAME, 530, 0);
				pDef->szValue = nullptr;
			}
		}
	}

	for (int32_t nList = 0; nList <= 1; ++nList)
	{
		while (CMDDEF* pDef = SCmdGetList(nList)->Head())
		{
			SCmdGetList(nList)->UnlinkNode(pDef);
			SMemFree(pDef, typeid(CMDDEF).name(), SERR_LINECODE_OBJECT, 0);
		}
	}

	sgbHasOptionalPositional = FALSE;
	return TRUE;
}

// Storm.#472
BOOL __stdcall SCmdGetBool(uint32_t dwId)
{
	return SCmdGetNum(dwId) != 0;
}

// Storm.#473
uint32_t __stdcall SCmdGetNum(uint32_t dwId)
{
	CMDDEF* pDef = SCmdFindById(dwId);
	return pDef ? pDef->dwValue : 0;
}

// Storm.#474
BOOL __stdcall SCmdGetString(uint32_t dwId, char* buffer, size_t bufferchars)
{
	if (buffer)
	{
		*buffer = '\0';
	}

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(buffer);
	STORM_VALIDATE_ARG(bufferchars);
	STORM_VALIDATE_END(FALSE);

	CMDDEF* pDef = SCmdFindById(dwId);
	if (!pDef)
	{
		return FALSE;
	}

	if (pDef->szValue)
	{
		SStrCopy(buffer, pDef->szValue, bufferchars);
	}
	return TRUE;
}

// Storm.#475
BOOL __stdcall SCmdProcess(const char* szCommandLine, BOOL bSkipFirstToken, SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(szCommandLine);
	STORM_VALIDATE_END(FALSE);

	if (bSkipFirstToken)
	{
		SStrTokenize(&szCommandLine, nullptr, 0, sgszTokenDelimiters, nullptr);
	}

	SCMDPARSESTATE state;
	SMemZero(&state, sizeof(state));
	CMDDEF* pPositional = sgPositionalList.Head();
	if (!SCmdProcessTokens(&szCommandLine, &state, &pPositional, pfnExtraCallback, pfnErrorCallback))
	{
		return FALSE;
	}

	// Check that every required argument was provided
	BOOL bResult = TRUE;
	for (CMDDEF* pDef = pPositional; pDef && bResult; pDef = pDef->Next())
	{
		if ((pDef->dwFlags & SCMD_ARG_MASK) == SCMD_ARG_REQUIRED)
		{
			bResult = FALSE;
		}
	}

	if (pfnErrorCallback && !bResult)
	{
		SCmdReportError(pfnErrorCallback, STORM_ERROR_NOT_ENOUGH_ARGUMENTS, sgszEmpty);
	}
	return bResult;
}

// Storm.#476
BOOL __stdcall SCmdRegisterArgList(const SCMDARGDEF* pArgList, uint32_t nCount)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pArgList);
	STORM_VALIDATE_END(FALSE);

	for (uint32_t i = 0; i < nCount; ++i)
	{
		const SCMDARGDEF* pArg = &pArgList[i];
		if (!SCmdRegisterArgument(pArg->dwFlags, pArg->dwId, pArg->szName, nullptr, 0, TRUE, 0xFFFFFFFF, pArg->pfnCallback))
		{
			return FALSE;
		}
	}
	return TRUE;
}

// Storm.#477
BOOL __stdcall SCmdRegisterArgument(uint32_t dwFlags, uint32_t dwId, const char* szName, void* pVariable, uint32_t nVariableSize, uint32_t dwSetValue, uint32_t dwSetMask, SCMDCALLBACK pfnCallback)
{
	if (!szName)
	{
		szName = &sgszEmpty[1];
	}

	const int32_t nNameLength = SStrLen(szName);
	const uint32_t dwArgType = dwFlags & SCMD_ARG_MASK;

	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(nNameLength < SCMD_MAX_NAME);
	STORM_VALIDATE_ARG(!nVariableSize || pVariable);
	STORM_VALIDATE_ARG(dwArgType != SCMD_ARG_REQUIRED || !sgbHasOptionalPositional);
	STORM_VALIDATE_ARG(dwArgType != SCMD_ARG_SWITCH || nNameLength > 0);
	STORM_VALIDATE_ARG((dwFlags & SCMD_TYPE_MASK) != SCMD_TYPE_BOOL || !pVariable || nVariableSize == sizeof(uint32_t));
	STORM_VALIDATE_END(FALSE);

	STORM_LIST(CMDDEF)* pList = dwArgType == SCMD_ARG_SWITCH ? &sgSwitchList : &sgPositionalList;
	CMDDEF* pDef = pList->NewNode(0, 0, 0);
	pList->LinkToTail(pDef);

	SStrCopy(pDef->szName, szName, SCMD_MAX_NAME);
	pDef->dwId = dwId;
	pDef->pVariable = pVariable;
	pDef->nVariableSize = nVariableSize;
	pDef->nNameLength = nNameLength;
	pDef->dwSetMask = dwSetMask;
	pDef->dwFlags = dwFlags;
	pDef->dwSetValue = dwSetValue;
	pDef->pfnCallback = pfnCallback;
	if (!(dwFlags & SCMD_TYPE_MASK) && (dwFlags & SCMD_BOOL_CLEAR) == SCMD_BOOL_CLEAR)
	{
		pDef->dwValue = dwSetValue;
	}
	else
	{
		pDef->dwValue = 0;
	}

	if (dwArgType == SCMD_ARG_OPTIONAL)
	{
		sgbHasOptionalPositional = TRUE;
	}
	return TRUE;
}

// Storm.#478
BOOL __stdcall SCmdStringExists(uint32_t dwId)
{
	CMDDEF* pDef = SCmdFindById(dwId);
	return pDef ? pDef->bFound : FALSE;
}

// Storm.#479
BOOL __stdcall SCmdProcessCommandLine(SCMDEXTRACALLBACK pfnExtraCallback, SCMDERRORCALLBACK pfnErrorCallback)
{
	return SCmdProcess(GetCommandLineA(), TRUE, pfnExtraCallback, pfnErrorCallback);
}

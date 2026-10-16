#include "StormInternal.h"

#include <cstdlib>

// Registry access

// Storm.0x6FFEC870
static uint32_t sgdwEmptyData;

#define SREG_KEY_READ  0x20019 // KEY_READ
#define SREG_KEY_WRITE 0x20006 // KEY_WRITE

static void SRegBuildKeyPath(char* szPath, const char* keyname, uint32_t flags)
{
	szPath[0] = '\0';
	if (!(flags & SREG_ABSOLUTE))
	{
		SRegGetBaseKey(flags, szPath, MAX_PATH);
	}
	SStrNCat(szPath, keyname, MAX_PATH);
}

// Storm.0x6FFD56B0
static BOOL SRegDeleteValueInternal(const char* keyname, const char* valuename, uint32_t flags)
{
	char szPath[MAX_PATH];
	SRegBuildKeyPath(szPath, keyname, flags);

	BOOL bResult = FALSE;
	const uint32_t dwHives = flags & (SREG_EXCLUDE_LOCAL_MACHINE | SREG_EXCLUDE_CURRENT_USER);

	LONG nUserError = ERROR_SUCCESS;
	if (dwHives != SREG_EXCLUDE_CURRENT_USER)
	{
		HKEY hKey;
		LONG nError = RegOpenKeyExA(HKEY_CURRENT_USER, szPath, 0, SREG_KEY_READ, &hKey);
		if (nError == ERROR_SUCCESS)
		{
			const LONG nDeleteError = RegDeleteValueA(hKey, valuename);
			if (nDeleteError)
			{
				nUserError = nDeleteError;
			}
			nError = RegCloseKey(hKey);
		}
		if (nError)
		{
			nUserError = nError;
		}
		if (!nUserError)
		{
			bResult = TRUE;
		}
	}

	LONG nMachineError = ERROR_SUCCESS;
	if (dwHives != SREG_EXCLUDE_LOCAL_MACHINE)
	{
		HKEY hKey;
		LONG nError = RegOpenKeyExA(HKEY_LOCAL_MACHINE, szPath, 0, SREG_KEY_READ, &hKey);
		if (nError == ERROR_SUCCESS)
		{
			const LONG nDeleteError = RegDeleteValueA(hKey, valuename);
			if (nDeleteError)
			{
				nMachineError = nDeleteError;
			}
			nError = RegCloseKey(hKey);
		}
		if (nError)
		{
			nMachineError = nError;
		}
		if (!nMachineError)
		{
			return TRUE;
		}
	}

	if (bResult)
	{
		return bResult;
	}

	SetLastError(nUserError ? nUserError : nMachineError);
	return bResult;
}

// Storm.0x6FFD58B0
static BOOL SRegLoadDataInternal(const char* keyname, const char* valuename, uint32_t flags, DWORD* pType, void* buffer, uint32_t buffersize, DWORD* pBytesRead)
{
	*pBytesRead = 0;

	char szPath[MAX_PATH];
	SRegBuildKeyPath(szPath, keyname, flags);

	HKEY hKey = nullptr;
	LONG nError = ERROR_CANTOPEN;
	if (!(flags & SREG_EXCLUDE_CURRENT_USER))
	{
		nError = RegOpenKeyExA(HKEY_CURRENT_USER, szPath, 0, SREG_KEY_READ, &hKey);
		if (nError == ERROR_SUCCESS)
		{
			*pBytesRead = buffersize;
			nError = RegQueryValueExA(hKey, valuename, nullptr, pType, (LPBYTE)buffer, pBytesRead);
			RegCloseKey(hKey);
			if (nError == ERROR_SUCCESS)
			{
				return TRUE;
			}
		}
	}

	if (!(flags & SREG_EXCLUDE_LOCAL_MACHINE))
	{
		nError = RegOpenKeyExA(HKEY_LOCAL_MACHINE, szPath, 0, SREG_KEY_READ, &hKey);
		if (nError)
		{
			SetLastError(nError);
			return FALSE;
		}
		*pBytesRead = buffersize;
		nError = RegQueryValueExA(hKey, valuename, nullptr, pType, (LPBYTE)buffer, pBytesRead);
		RegCloseKey(hKey);
	}

	if (nError)
	{
		SetLastError(nError);
		return FALSE;
	}
	return TRUE;
}

// Storm.0x6FFD5C10
static BOOL SRegSaveDataInternal(const char* keyname, const char* valuename, uint32_t flags, DWORD dwType, const void* data, uint32_t datasize)
{
	char szPath[MAX_PATH];
	SRegBuildKeyPath(szPath, keyname, flags);

	// When saving, SREG_EXCLUDE_CURRENT_USER means "save to HKEY_LOCAL_MACHINE"
	HKEY hRootKey = (flags & SREG_EXCLUDE_CURRENT_USER) ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER;
	HKEY hKey;
	DWORD dwDisposition;
	LONG nError = RegCreateKeyExA(hRootKey, szPath, 0, nullptr, REG_OPTION_NON_VOLATILE, SREG_KEY_WRITE, nullptr, &hKey, &dwDisposition);
	if (nError == ERROR_SUCCESS)
	{
		nError = RegSetValueExA(hKey, valuename, 0, dwType, (const BYTE*)data, datasize);
		if (nError == ERROR_SUCCESS && (!(flags & SREG_FLUSH) || (nError = RegFlushKey(hKey)) == ERROR_SUCCESS))
		{
			nError = RegCloseKey(hKey);
			if (nError == ERROR_SUCCESS)
			{
				return TRUE;
			}
		}
		RegCloseKey(hKey);
	}

	SetLastError(nError);
	return FALSE;
}

// Storm.#421
BOOL __stdcall SRegLoadData(const char* keyname, const char* valuename, uint32_t flags, void* buffer, uint32_t buffersize, uint32_t* bytesread)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_END(FALSE);

	DWORD dwBytesRead;
	DWORD dwType;
	const BOOL bResult = SRegLoadDataInternal(keyname, valuename, flags, &dwType, buffer, buffersize, &dwBytesRead);
	if (bytesread)
	{
		*bytesread = dwBytesRead;
	}
	return bResult;
}

// Storm.#422
BOOL __stdcall SRegLoadString(const char* keyname, const char* valuename, uint32_t flags, char* buffer, size_t buffersize)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_ARG(buffer);
	STORM_VALIDATE_ARG(buffersize);
	STORM_VALIDATE_END(FALSE);

	DWORD dwType;
	DWORD dwBytesRead;
	if (!SRegLoadDataInternal(keyname, valuename, flags, &dwType, buffer, buffersize, &dwBytesRead))
	{
		return FALSE;
	}

	if (dwType == REG_SZ)
	{
		uint32_t nEnd = buffersize - 1;
		if (nEnd >= dwBytesRead)
		{
			nEnd = dwBytesRead;
		}
		buffer[nEnd] = '\0';
	}
	else if (dwType == REG_DWORD)
	{
		wsprintfA(buffer, "%u", *(DWORD*)buffer);
	}
	return TRUE;
}

// Storm.#423
BOOL __stdcall SRegLoadValue(const char* keyname, const char* valuename, uint32_t flags, DWORD* value)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_ARG(value);
	STORM_VALIDATE_END(FALSE);

	union
	{
		DWORD dwValue;
		char szValue[256];
	} buffer;
	buffer.dwValue = 0;

	DWORD dwType;
	DWORD dwBytesRead;
	if (!SRegLoadDataInternal(keyname, valuename, flags, &dwType, &buffer, sizeof(buffer), &dwBytesRead))
	{
		return FALSE;
	}

	if (dwType == REG_SZ)
	{
		*value = strtoul(buffer.szValue, nullptr, 0);
	}
	else if (dwType == REG_DWORD)
	{
		*value = buffer.dwValue;
	}
	return TRUE;
}

// Storm.#424
BOOL __stdcall SRegSaveData(const char* keyname, const char* valuename, uint32_t flags, const void* data, uint32_t datasize)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_END(FALSE);

	if (!data)
	{
		data = &sgdwEmptyData;
	}

	const DWORD dwType = ((flags & SREG_MULTI_SZ) | 0x60) >> 5; // REG_BINARY or REG_MULTI_SZ
	return SRegSaveDataInternal(keyname, valuename, flags, dwType, data, datasize);
}

// Storm.#425
BOOL __stdcall SRegSaveString(const char* keyname, const char* valuename, uint32_t flags, const char* string)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_ARG(string);
	STORM_VALIDATE_END(FALSE);

	return SRegSaveDataInternal(keyname, valuename, flags, REG_SZ, string, SStrLen(string) + 1);
}

// Storm.#426
BOOL __stdcall SRegSaveValue(const char* keyname, const char* valuename, uint32_t flags, DWORD value)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_END(FALSE);

	return SRegSaveDataInternal(keyname, valuename, flags, REG_DWORD, &value, sizeof(value));
}

// Storm.#427
BOOL __stdcall SRegGetBaseKey(uint32_t flags, char* buffer, size_t bufferchars)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(buffer);
	STORM_VALIDATE_ARG(bufferchars);
	STORM_VALIDATE_END(FALSE);

	if (flags & SREG_BATTLE_NET)
	{
		SStrCopy(buffer, "Software\\Battle.net\\", bufferchars);
	}
	else
	{
		SStrCopy(buffer, "Software\\Blizzard Entertainment\\", bufferchars);
	}
	return TRUE;
}

// Storm.#428
BOOL __stdcall SRegDeleteValue(const char* keyname, const char* valuename, uint32_t flags)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(keyname);
	STORM_VALIDATE_ARG(*keyname);
	STORM_VALIDATE_ARG(valuename);
	STORM_VALIDATE_ARG(*valuename);
	STORM_VALIDATE_END(FALSE);

	return SRegDeleteValueInternal(keyname, valuename, flags);
}

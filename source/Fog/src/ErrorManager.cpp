#include <Fog.h>
#include <Storm.h>

#include <cstdarg>
#include <cstdio>

// Fog.0x6FFA0274
static size_t gnSourceRootPathLength;

// 1.10f: 0x6FF5DD90 (#10018)
// sprintf returning the destination buffer
const char* __cdecl FOG_csprintf(char* szDest, const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	vsprintf(szDest, szFormat, args);
	va_end(args);
	return szDest;
}

// 1.10f: 0x6FF5F2B0 (#10231)
// Removes the root directory of the source tree from a source file path (such as __FILE__).
// The root directory length is deduced from the path of this file.
const char* __fastcall FOG_GetShortSourceFilePath(const char* szFilePath)
{
	if (!gnSourceRootPathLength)
	{
		const int nRootLength = (int)SStrLen(__FILE__) - (int)SStrLen("Fog\\src\\ErrorManager.cpp");
		gnSourceRootPathLength = nRootLength > 0 ? nRootLength : 0;
	}

	if (SStrLen(szFilePath) > gnSourceRootPathLength)
	{
		return szFilePath + gnSourceRootPathLength;
	}
	return szFilePath;
}

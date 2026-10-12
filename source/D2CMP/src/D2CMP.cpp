#include <D2CMP.h>

#include <cstdio>
#include <cstring>

#include <Storm.h>

#include "SpriteCache.h"


BOOL gbCompressedData = TRUE;	//D2CMP.0x6FE0F058

//D2CMP.0x6FDFB930 (#10051)
const char* __stdcall D2CMP_GetGfxFileExtension(BOOL bAllowCompressed)
{
	if (bAllowCompressed && gbCompressedData)
	{
		return ".dcc";
	}

	return ".dc6";
}

//D2CMP.0x6FDFB950 (#10050)
void __stdcall D2CMP_BuildFileName(char* szFileName, const char* szFormat, va_list args, BOOL bAllowCompressed)
{
	vsprintf(szFileName, szFormat, args);
	strcat(szFileName, D2CMP_GetGfxFileExtension(bAllowCompressed));
}

//D2CMP.0x6FDFB9C0 (#10054)
void __stdcall D2CMP_SetNoCompress(BOOL bAllowCompressed)
{
	SRegLoadValue("Diablo II", "CompressedData", 1, (DWORD*)&gbCompressedData);
	if (!bAllowCompressed)
	{
		gbCompressedData = FALSE;
	}
}

//D2CMP.0x6FDF3ED0 (#10103)
void __stdcall D2CMP_10103()
{
}

//D2CMP.0x6FDF3ED0 (#10104)
void __stdcall D2CMP_10104()
{
}

//D2CMP.0x6FDF3ED0 (#10106)
void __stdcall D2CMP_10106()
{
}

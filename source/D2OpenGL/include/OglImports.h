#pragma once

#include <cstdint>

#include <Windows.h>


struct D2GfxCellStrc;
struct D2GfxDataStrc;
struct D2TileLibraryEntryStrc;


// Functions of the other game modules used by the renderer.
// They are resolved at runtime (by ordinal or by name) because they are either not implemented by D2MOO yet,
// or their D2MOO prototypes are not precise enough. They are the same functions the original D2Gdi.dll / D2DDraw.dll import,
// and their signatures were deduced from the calls made by those drivers.

#pragma pack(push, 1)
// Partial layout of the BINK structure of binkw32.dll
struct D2BinkStrc
{
    uint32_t nWidth;                            //0x00
    uint32_t nHeight;                           //0x04
    uint32_t nFrames;                           //0x08
    uint32_t nFrameNum;                         //0x0C
};

// Partial layout of the Smack structure of smackw32.dll
struct D2SmackStrc
{
    uint32_t nVersion;                          //0x00
    uint32_t nWidth;                            //0x04
    uint32_t nHeight;                           //0x08
    uint32_t nFrames;                           //0x0C
    uint32_t unk0x10[22];                       //0x10
    uint32_t bNewPalette;                       //0x68
    uint8_t pPalette[772];                      //0x6C
    uint32_t nPaletteType;                      //0x370
    uint32_t nFrameNum;                         //0x374
};
#pragma pack(pop)

// Old bink surface types, D2Glide.dll uses BINKSURFACE32 to write to its 8888 linear frame buffer
constexpr uint32_t BINKSURFACE32 = 2;

// Bink open flags
constexpr uint32_t BINKFILEHANDLE = 0x00800000;


// D2CMP.#10004
extern int32_t(__stdcall* D2CMP_GetNearestPaletteIndex)(PALETTEENTRY* pPalette, int32_t nPaletteSize, int32_t nRed, int32_t nGreen, int32_t nBlue);
// D2CMP.#10033 Draws a cel to an 8 bits buffer. pLightPalette, pBlendTable and pRemapPalette are optional.
extern void(__stdcall* D2CMP_CelDraw)(D2GfxDataStrc* pData, int32_t nX, int32_t nY, int32_t nClipLeft, int32_t nClipRight, uint8_t* pBuffer, int32_t nBufferHeight, int32_t nBufferPitch, uint8_t* pLightPalette, uint8_t* pBlendTable, uint8_t* pRemapPalette);
// D2CMP.#10034 Same as D2CMP_CelDraw, but skips the nSkipLines bottom lines and only draws nDrawLines lines
extern void(__stdcall* D2CMP_CelDrawEx)(D2GfxDataStrc* pData, int32_t nX, int32_t nY, int32_t nClipLeft, int32_t nClipRight, uint8_t* pBuffer, int32_t nBufferHeight, int32_t nBufferPitch, uint8_t* pLightPalette, uint8_t* pBlendTable, int32_t nSkipLines, int32_t nDrawLines, uint8_t* pRemapPalette);
// D2CMP.#10035 Draws the (skewed) shadow of a cel
extern void(__stdcall* D2CMP_CelDrawShadow)(D2GfxDataStrc* pData, int32_t nX, int32_t nY, int32_t nClipLeft, int32_t nClipRight, uint8_t* pBuffer, int32_t nBufferHeight, int32_t nBufferPitch, uint8_t* pBlendTable, int32_t nUnused);
// D2CMP.#10037
extern int32_t(__stdcall* D2CMP_CelGetWidth)(D2GfxCellStrc* pCell);
// D2CMP.#10038
extern int32_t(__stdcall* D2CMP_CelGetHeight)(D2GfxCellStrc* pCell);
// D2CMP.#10039
extern int32_t(__stdcall* D2CMP_CelGetOffsetX)(D2GfxCellStrc* pCell);
// D2CMP.#10040
extern int32_t(__stdcall* D2CMP_CelGetOffsetY)(D2GfxCellStrc* pCell);
// D2CMP.#10048 Debug function filling the back buffer at the given position
extern void(__stdcall* D2CMP_DebugFillBuffer)(uint8_t* pBuffer, int32_t nBufferPitch);
// D2CMP.#10055 Makes sure the current cell of pData is loaded, returns FALSE if it can not be drawn
extern BOOL(__stdcall* D2CMP_SpriteValidate)(D2GfxDataStrc* pData, int32_t nUnused, BOOL bLoad);
// D2CMP.#10091 Makes sure the blocks of the tile are loaded, returns FALSE if it can not be drawn
extern BOOL(__stdcall* D2CMP_TileValidate)(D2TileLibraryEntryStrc* pTile, BOOL bLoad, int32_t nUnused);

// D2Sound.#10027 Called with 0 before closing a bink cutscene, and 255 after
extern void(__fastcall* D2SOUND_10027)(int32_t nValue);

// Fog.#10198 Builds a gamma ramp of nEntries entries of nEntrySize bytes each, with values in [0, nMaxValue]
extern void(__fastcall* FOG_BuildGammaRamp)(int32_t nGamma, void* pTable, double dContrast, int32_t nEntrySize, int32_t nEntries, int32_t nMaxValue);

// Storm.#268
extern BOOL(__stdcall* STORM_SFileOpenFileEx)(HANDLE hArchive, const char* szFileName, uint32_t dwSearchScope, HANDLE* phFile);
// Storm.#281
extern BOOL(__stdcall* STORM_SFileLoadFileEx)(HANDLE hArchive, const char* szFileName, void** ppBuffer, uint32_t* pnSize, uint32_t nExtraSize, uint32_t dwSearchScope, void* pOverlapped);
// Storm.#321
extern BOOL(__stdcall* STORM_SBmpDecodeImage)(uint32_t nImageType, void* pSrc, uint32_t nSrcSize, PALETTEENTRY* pPalette, void* pDst, uint32_t nDstSize, uint32_t* pWidth, uint32_t* pHeight, uint32_t* pBitsPerPixel);
// Storm.#403
extern BOOL(__stdcall* STORM_SMemFree)(void* pMemory, const char* szFile, int32_t nLine, uint32_t dwFlags);

// binkw32.dll
extern void* gpfBinkOpenDirectSound;
extern int32_t(__stdcall* BINK_SetSoundSystem)(void* pfOpen, uint32_t nParam);
extern D2BinkStrc* (__stdcall* BINK_Open)(const char* szName, uint32_t dwFlags);
extern void(__stdcall* BINK_Close)(D2BinkStrc* pBink);
extern int32_t(__stdcall* BINK_Wait)(D2BinkStrc* pBink);
extern int32_t(__stdcall* BINK_DoFrame)(D2BinkStrc* pBink);
extern void(__stdcall* BINK_NextFrame)(D2BinkStrc* pBink);
extern int32_t(__stdcall* BINK_CopyToBuffer)(D2BinkStrc* pBink, void* pDst, int32_t nDstPitch, uint32_t nDstHeight, uint32_t nDstX, uint32_t nDstY, uint32_t dwFlags);

// smackw32.dll
extern D2SmackStrc* (__stdcall* SMACK_Open)(const char* szName, uint32_t dwFlags, uint32_t nExtraBuffers);
extern void(__stdcall* SMACK_Close)(D2SmackStrc* pSmack);
extern uint32_t(__stdcall* SMACK_Wait)(D2SmackStrc* pSmack);
extern uint32_t(__stdcall* SMACK_DoFrame)(D2SmackStrc* pSmack);
extern void(__stdcall* SMACK_NextFrame)(D2SmackStrc* pSmack);
extern void(__stdcall* SMACK_ToBuffer)(D2SmackStrc* pSmack, uint32_t nLeft, uint32_t nTop, uint32_t nPitch, uint32_t nDstHeight, void* pBuffer, uint32_t dwFlags);


// Resolves all the imports. Returns FALSE if a function required to draw the game is missing.
BOOL __fastcall IMPORTS_Load();
// Releases the modules loaded by IMPORTS_Load
void __fastcall IMPORTS_Unload();
// Returns TRUE if the bink functions were found
BOOL __fastcall IMPORTS_HasBink();
// Returns TRUE if the smacker functions were found
BOOL __fastcall IMPORTS_HasSmack();

#include "OglImports.h"

#include <Fog.h>


int32_t(__stdcall* D2CMP_GetNearestPaletteIndex)(PALETTEENTRY*, int32_t, int32_t, int32_t, int32_t);
void(__stdcall* D2CMP_CelDraw)(D2GfxDataStrc*, int32_t, int32_t, int32_t, int32_t, uint8_t*, int32_t, int32_t, uint8_t*, uint8_t*, uint8_t*);
void(__stdcall* D2CMP_CelDrawEx)(D2GfxDataStrc*, int32_t, int32_t, int32_t, int32_t, uint8_t*, int32_t, int32_t, uint8_t*, uint8_t*, int32_t, int32_t, uint8_t*);
void(__stdcall* D2CMP_CelDrawShadow)(D2GfxDataStrc*, int32_t, int32_t, int32_t, int32_t, uint8_t*, int32_t, int32_t, uint8_t*, int32_t);
int32_t(__stdcall* D2CMP_CelGetWidth)(D2GfxCellStrc*);
int32_t(__stdcall* D2CMP_CelGetHeight)(D2GfxCellStrc*);
int32_t(__stdcall* D2CMP_CelGetOffsetX)(D2GfxCellStrc*);
int32_t(__stdcall* D2CMP_CelGetOffsetY)(D2GfxCellStrc*);
void(__stdcall* D2CMP_DebugFillBuffer)(uint8_t*, int32_t);
BOOL(__stdcall* D2CMP_SpriteValidate)(D2GfxDataStrc*, int32_t, BOOL);
BOOL(__stdcall* D2CMP_TileValidate)(D2TileLibraryEntryStrc*, BOOL, int32_t);

void(__fastcall* D2SOUND_10027)(int32_t);

void(__fastcall* FOG_BuildGammaRamp)(int32_t, void*, double, int32_t, int32_t, int32_t);

BOOL(__stdcall* STORM_SFileOpenFileEx)(HANDLE, const char*, uint32_t, HANDLE*);
BOOL(__stdcall* STORM_SFileLoadFileEx)(HANDLE, const char*, void**, uint32_t*, uint32_t, uint32_t, void*);
BOOL(__stdcall* STORM_SBmpDecodeImage)(uint32_t, void*, uint32_t, PALETTEENTRY*, void*, uint32_t, uint32_t*, uint32_t*, uint32_t*);
BOOL(__stdcall* STORM_SMemFree)(void*, const char*, int32_t, uint32_t);

void* gpfBinkOpenDirectSound;
int32_t(__stdcall* BINK_SetSoundSystem)(void*, uint32_t);
D2BinkStrc* (__stdcall* BINK_Open)(const char*, uint32_t);
void(__stdcall* BINK_Close)(D2BinkStrc*);
int32_t(__stdcall* BINK_Wait)(D2BinkStrc*);
int32_t(__stdcall* BINK_DoFrame)(D2BinkStrc*);
void(__stdcall* BINK_NextFrame)(D2BinkStrc*);
int32_t(__stdcall* BINK_CopyToBuffer)(D2BinkStrc*, void*, int32_t, uint32_t, uint32_t, uint32_t, uint32_t);

D2SmackStrc* (__stdcall* SMACK_Open)(const char*, uint32_t, uint32_t);
void(__stdcall* SMACK_Close)(D2SmackStrc*);
uint32_t(__stdcall* SMACK_Wait)(D2SmackStrc*);
uint32_t(__stdcall* SMACK_DoFrame)(D2SmackStrc*);
void(__stdcall* SMACK_NextFrame)(D2SmackStrc*);
void(__stdcall* SMACK_ToBuffer)(D2SmackStrc*, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t);


struct D2OglModuleStrc
{
    const char* szName;
    HMODULE hModule;
    BOOL bLoaded; // TRUE if we called LoadLibrary and need to call FreeLibrary
    BOOL bLoadAttempted;
};

enum D2OglModules
{
    OGLMODULE_D2CMP,
    OGLMODULE_D2SOUND,
    OGLMODULE_FOG,
    OGLMODULE_STORM,
    OGLMODULE_BINK,
    OGLMODULE_SMACK,
    NUM_OGLMODULES
};

static D2OglModuleStrc gImportModules[NUM_OGLMODULES] =
{
    { "D2CMP.dll", nullptr, FALSE, FALSE },
    { "D2Sound.dll", nullptr, FALSE, FALSE },
    { "Fog.dll", nullptr, FALSE, FALSE },
    { "Storm.dll", nullptr, FALSE, FALSE },
    { "binkw32.dll", nullptr, FALSE, FALSE },
    { "smackw32.dll", nullptr, FALSE, FALSE },
};

static BOOL gbHasBink;
static BOOL gbHasSmack;


static HMODULE IMPORTS_GetModule(D2OglModules eModule)
{
    D2OglModuleStrc* pModule = &gImportModules[eModule];
    if (!pModule->hModule && !pModule->bLoadAttempted)
    {
        pModule->bLoadAttempted = TRUE;

        // The game modules are already loaded by the game, only load them if they are not
        pModule->hModule = GetModuleHandleA(pModule->szName);
        if (!pModule->hModule)
        {
            pModule->hModule = LoadLibraryA(pModule->szName);
            pModule->bLoaded = pModule->hModule != nullptr;
        }

        if (!pModule->hModule)
        {
            FOG_Trace("D2OpenGL: Unable to load %s", pModule->szName);
        }
    }

    return pModule->hModule;
}

template<typename T>
static BOOL IMPORTS_Resolve(T& pfFunction, D2OglModules eModule, const char* szProcName)
{
    pfFunction = nullptr;

    if (HMODULE hModule = IMPORTS_GetModule(eModule))
    {
        pfFunction = (T)GetProcAddress(hModule, szProcName);
    }

    return pfFunction != nullptr;
}

template<typename T>
static BOOL IMPORTS_Resolve(T& pfFunction, D2OglModules eModule, int32_t nOrdinal)
{
    if (!IMPORTS_Resolve(pfFunction, eModule, (const char*)MAKEINTRESOURCEA(nOrdinal)))
    {
        FOG_Trace("D2OpenGL: Unable to find %s ordinal #%d", gImportModules[eModule].szName, nOrdinal);
        return FALSE;
    }

    return TRUE;
}

BOOL __fastcall IMPORTS_Load()
{
    BOOL bResult = TRUE;
    bResult &= IMPORTS_Resolve(D2CMP_GetNearestPaletteIndex, OGLMODULE_D2CMP, 10004);
    bResult &= IMPORTS_Resolve(D2CMP_CelDraw, OGLMODULE_D2CMP, 10033);
    bResult &= IMPORTS_Resolve(D2CMP_CelDrawEx, OGLMODULE_D2CMP, 10034);
    bResult &= IMPORTS_Resolve(D2CMP_CelDrawShadow, OGLMODULE_D2CMP, 10035);
    bResult &= IMPORTS_Resolve(D2CMP_CelGetWidth, OGLMODULE_D2CMP, 10037);
    bResult &= IMPORTS_Resolve(D2CMP_CelGetHeight, OGLMODULE_D2CMP, 10038);
    bResult &= IMPORTS_Resolve(D2CMP_CelGetOffsetX, OGLMODULE_D2CMP, 10039);
    bResult &= IMPORTS_Resolve(D2CMP_CelGetOffsetY, OGLMODULE_D2CMP, 10040);
    bResult &= IMPORTS_Resolve(D2CMP_DebugFillBuffer, OGLMODULE_D2CMP, 10048);
    bResult &= IMPORTS_Resolve(D2CMP_SpriteValidate, OGLMODULE_D2CMP, 10055);
    bResult &= IMPORTS_Resolve(D2CMP_TileValidate, OGLMODULE_D2CMP, 10091);

    bResult &= IMPORTS_Resolve(STORM_SFileOpenFileEx, OGLMODULE_STORM, 268);
    bResult &= IMPORTS_Resolve(STORM_SFileLoadFileEx, OGLMODULE_STORM, 281);
    bResult &= IMPORTS_Resolve(STORM_SBmpDecodeImage, OGLMODULE_STORM, 321);
    bResult &= IMPORTS_Resolve(STORM_SMemFree, OGLMODULE_STORM, 403);

    // Optional functions, we can live without them
    IMPORTS_Resolve(D2SOUND_10027, OGLMODULE_D2SOUND, 10027);
    IMPORTS_Resolve(FOG_BuildGammaRamp, OGLMODULE_FOG, 10198);

    gbHasBink = TRUE;
    gbHasBink &= IMPORTS_Resolve(gpfBinkOpenDirectSound, OGLMODULE_BINK, "_BinkOpenDirectSound@4");
    gbHasBink &= IMPORTS_Resolve(BINK_SetSoundSystem, OGLMODULE_BINK, "_BinkSetSoundSystem@8");
    gbHasBink &= IMPORTS_Resolve(BINK_Open, OGLMODULE_BINK, "_BinkOpen@8");
    gbHasBink &= IMPORTS_Resolve(BINK_Close, OGLMODULE_BINK, "_BinkClose@4");
    gbHasBink &= IMPORTS_Resolve(BINK_Wait, OGLMODULE_BINK, "_BinkWait@4");
    gbHasBink &= IMPORTS_Resolve(BINK_DoFrame, OGLMODULE_BINK, "_BinkDoFrame@4");
    gbHasBink &= IMPORTS_Resolve(BINK_NextFrame, OGLMODULE_BINK, "_BinkNextFrame@4");
    gbHasBink &= IMPORTS_Resolve(BINK_CopyToBuffer, OGLMODULE_BINK, "_BinkCopyToBuffer@28");
    if (!gbHasBink)
    {
        FOG_Trace("D2OpenGL: binkw32.dll is unavailable, cutscenes will not be played.");
    }

    gbHasSmack = TRUE;
    gbHasSmack &= IMPORTS_Resolve(SMACK_Open, OGLMODULE_SMACK, "_SmackOpen@12");
    gbHasSmack &= IMPORTS_Resolve(SMACK_Close, OGLMODULE_SMACK, "_SmackClose@4");
    gbHasSmack &= IMPORTS_Resolve(SMACK_Wait, OGLMODULE_SMACK, "_SmackWait@4");
    gbHasSmack &= IMPORTS_Resolve(SMACK_DoFrame, OGLMODULE_SMACK, "_SmackDoFrame@4");
    gbHasSmack &= IMPORTS_Resolve(SMACK_NextFrame, OGLMODULE_SMACK, "_SmackNextFrame@4");
    gbHasSmack &= IMPORTS_Resolve(SMACK_ToBuffer, OGLMODULE_SMACK, "_SmackToBuffer@28");
    if (!gbHasSmack)
    {
        FOG_Trace("D2OpenGL: smackw32.dll is unavailable, smacker banners will not be played.");
    }

    return bResult;
}

void __fastcall IMPORTS_Unload()
{
    for (D2OglModuleStrc& module : gImportModules)
    {
        if (module.bLoaded)
        {
            FreeLibrary(module.hModule);
        }

        module.hModule = nullptr;
        module.bLoaded = FALSE;
        module.bLoadAttempted = FALSE;
    }

    gbHasBink = FALSE;
    gbHasSmack = FALSE;
}

BOOL __fastcall IMPORTS_HasBink()
{
    return gbHasBink;
}

BOOL __fastcall IMPORTS_HasSmack()
{
    return gbHasSmack;
}

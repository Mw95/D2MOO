#include "OglBink.h"

#include <cstring>

#include <Windows.h>

#include <Fog.h>

#include "OglCore.h"
#include "OglDevice.h"
#include "OglImports.h"


// Minimum duration of a cutscene before it can end
constexpr uint32_t CUTSCENE_MIN_DURATION = 500;


static int32_t gbPlayingCutscene;
static D2BinkStrc* gpBink;


// Returns the bink open flags matching the copy mode of the game
static uint32_t BINK_GetOpenFlags(int32_t nCopyMode)
{
    switch (nCopyMode)
    {
    case 1:
        return BINKFILEHANDLE | 0x30000000;

    case 2:
        return BINKFILEHANDLE | 0x10000000;

    case 3:
        return BINKFILEHANDLE | 0x40000000;

    default:
        return BINKFILEHANDLE;
    }
}

// Port of D2DDraw.0x6F881020
static void BINK_PlayFile(const char* szFile, int32_t nCopyMode, void(__cdecl* pfFrame)())
{
    if (gpBink || gbPaused || !IMPORTS_HasBink())
    {
        return;
    }

    BINK_SetSoundSystem(gpfBinkOpenDirectSound, 0);

    HANDLE hFile = nullptr;
    STORM_SFileOpenFileEx(nullptr, szFile, FOG_UseDirect() ? 5 : 4, &hFile);
    if (!hFile)
    {
        FOG_Trace("OpenGLPlayBinkFile: *** Couldn't load Bink movie '%s'.", szFile);
        return;
    }

    gpBink = BINK_Open((const char*)hFile, BINK_GetOpenFlags(nCopyMode));
    if (!gpBink)
    {
        FOG_Trace("BinkOpen failed on '%s'.", szFile);
        CloseHandle(hFile);
        return;
    }

    // Center the movie, horizontally aligned on 4 pixels
    // Note: the original dll does not handle movies larger than the screen
    int32_t nOffsetX = ((int32_t)gnBufferWidth - (int32_t)gpBink->nWidth) / 2;
    int32_t nOffsetY = ((int32_t)gnBufferHeight - (int32_t)gpBink->nHeight) / 2;
    if (nOffsetX & 3)
    {
        nOffsetX = (nOffsetX | 3) + 1;
    }
    nOffsetX = nOffsetX < 0 ? 0 : nOffsetX;
    nOffsetY = nOffsetY < 0 ? 0 : nOffsetY;

    const uint32_t dwMinEndTickCount = GetTickCount() + CUTSCENE_MIN_DURATION;
    BOOL bSkipped = FALSE;
    BOOL bDone = FALSE;
    BOOL bQuit = FALSE;

    while ((!bDone || GetTickCount() < dwMinEndTickCount) && !gbPaused)
    {
        if (pfFrame)
        {
            pfFrame();
        }

        if (bSkipped)
        {
            break;
        }

        MSG msg = {};
        if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_CHAR:
                bSkipped = TRUE;
                break;

            case WM_QUIT:
                bDone = TRUE;
                bQuit = TRUE;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessageA(&msg);
            continue;
        }

        if (BINK_Wait(gpBink))
        {
            Sleep(1);
            continue;
        }

        if (!ghWnd)
        {
            continue;
        }

        BINK_DoFrame(gpBink);

        D2_ASSERT(gpcsPause);
        EnterCriticalSection(gpcsPause);
        if (uint32_t* pFrame = DEVICE_GetFrameBuffer())
        {
            BINK_CopyToBuffer(gpBink, pFrame, gnBufferWidth * sizeof(uint32_t), gnBufferHeight, nOffsetX, nOffsetY, BINKSURFACE32);
            DEVICE_Present();
        }
        LeaveCriticalSection(gpcsPause);

        if (gpBink->nFrameNum == gpBink->nFrames)
        {
            bDone = TRUE;
        }
        else
        {
            BINK_NextFrame(gpBink);
        }
    }

    if (D2SOUND_10027)
    {
        D2SOUND_10027(0);
    }

    BINK_Close(gpBink);
    CloseHandle(hFile);

    if (D2SOUND_10027)
    {
        D2SOUND_10027(255);
    }

    gpBink = nullptr;

    if (bQuit)
    {
        exit(-1);
    }
}

//pfOpenSmackCutscene
// Port of D2DDraw.0x6F881DA0. Despite its name, the second parameter is the copy mode of the movie.
void __fastcall OGL_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolutionMode, void* pfFrame)
{
    if (gbPaused)
    {
        return;
    }

    gbPlayingCutscene = TRUE;

    // Start from a black screen
    if (uint32_t* pFrame = DEVICE_GetFrameBuffer())
    {
        memset(pFrame, 0, sizeof(uint32_t) * gnBufferWidth * gnBufferHeight);
        DEVICE_Present();
    }

    BINK_PlayFile(szFile, nResolutionMode, (void(__cdecl*)())pfFrame);

    gbPlayingCutscene = FALSE;
}

//pfCheckCutScene
BOOL __fastcall OGL_CheckCutScene()
{
    return gbPlayingCutscene;
}

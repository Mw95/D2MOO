#include "Core/WndProc.h"

#include <D2Gfx.h>
#include <Window.h>

#include "Core/MemoryPartitions.h"
#include "Draw/DFloor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"


//D2Client.0x6FB74970
int32_t gnDisplayType = DISPLAYTYPE_DDRAW;
//D2Client.0x6FB9A968
uint8_t gbWindowed;
//D2Client.0x6FB9A96C
int32_t gnFramesPerSecond;
//D2Client.0x6FB9A970
static DWORD gdwLastFpsTick;
//D2Client.0x6FB9A974
static int32_t gnFramesThisSecond;
//D2Client.0x6FB9A978
static int32_t gnFramesSinceDebugStart;
//D2Client.0x6FB9A97C
static DWORD gdwDebugStartTick;
//D2Client.0x6FB9A980
static BOOL gbShowDebugInfo;
//D2Client.0x6FB9A988
static BOOL gbHideCacheStats;
//D2Client.0x6FB9A990
D2FloorDrawContextStrc gFloorDrawContext;


//D2Client.0x6FAA26C0
void __fastcall WNDPROC_RegisterMessageHandlers(HWND hWnd, const D2WindowMessageHandlerStrc* pHandlers, uint32_t nHandlers)
{
	D2_ASSERT(hWnd);

	for (uint32_t i = 0; i < nHandlers; ++i)
	{
		const D2WindowMessageHandlerStrc* pHandler = &pHandlers[i];
		switch (pHandler->nType)
		{
		case WINDOW_MESSAGE_HANDLER_MESSAGE:
			D2_ASSERT(pHandler->nId != WM_COMMAND);
			SMsgRegisterMessage(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_COMMAND:
			SMsgRegisterCommand(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_KEYUP:
			SMsgRegisterKeyUp(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_KEYDOWN:
			SMsgRegisterKeyDown(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		}
	}
}

//D2Client.0x6FAA2780
void __fastcall WNDPROC_UnregisterMessageHandlers(HWND hWnd, const D2WindowMessageHandlerStrc* pHandlers, uint32_t nHandlers)
{
	D2_ASSERT(hWnd);

	for (uint32_t i = 0; i < nHandlers; ++i)
	{
		const D2WindowMessageHandlerStrc* pHandler = &pHandlers[i];
		switch (pHandler->nType)
		{
		case WINDOW_MESSAGE_HANDLER_MESSAGE:
			D2_ASSERT(pHandler->nId != WM_COMMAND);
			SMsgUnregisterMessage(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_COMMAND:
			SMsgUnregisterCommand(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_KEYUP:
			SMsgUnregisterKeyUp(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		case WINDOW_MESSAGE_HANDLER_KEYDOWN:
			SMsgUnregisterKeyDown(hWnd, pHandler->nId, pHandler->pHandler);
			break;
		}
	}
}

//D2Client.0x6FAA2840
void __fastcall WNDPROC_PushRegisterState()
{
	SMsgPushRegisterState((int)WINDOW_GetWindow());
}

//D2Client.0x6FAA2850
void __fastcall WNDPROC_PopRegisterState()
{
	SMsgPopRegisterState((int)WINDOW_GetWindow());
}

//D2Client.0x6FAA2860
void __fastcall WNDPROC_SetGamma(uint32_t nGamma)
{
	D2GFX_SetGamma(nGamma);
}

//D2Client.0x6FAA2870
void __fastcall WNDPROC_SetDisplayTypeGDI()
{
	gnDisplayType = DISPLAYTYPE_GDI;
	gbWindowed = TRUE;
}

//D2Client.0x6FAA2880
void __fastcall WNDPROC_SetDisplayTypeGlide()
{
	gnDisplayType = DISPLAYTYPE_GLIDE;
}

//D2Client.0x6FAA2890
void __fastcall WNDPROC_SetDisplayTypeOpenGL()
{
	gnDisplayType = DISPLAYTYPE_OPENGL;
}

//D2Client.0x6FAA28A0
void __fastcall WNDPROC_SetDisplayTypeDirect3D()
{
	gnDisplayType = DISPLAYTYPE_DIRECT3D;
}

//D2Client.0x6FAA28B0
void __fastcall WNDPROC_SetDisplayTypeRave()
{
	gnDisplayType = DISPLAYTYPE_RAVE;
}

//D2Client.0x6FAA28C0
int32_t __fastcall WNDPROC_GetDisplayType()
{
	return gnDisplayType;
}

//D2Client.0x6FAA28D0
BOOL __fastcall WNDPROC_IsHardwareAccelerated()
{
	return gnDisplayType > DISPLAYTYPE_DDRAW;
}

//D2Client.0x6FAA28E0
void __fastcall WNDPROC_DrawDebugInfo()
{
	const DWORD dwTickCount = GetTickCount();

	if (gbShowDebugInfo && !gdwDebugStartTick)
	{
		gdwDebugStartTick = dwTickCount;
		gnFramesSinceDebugStart = 0;
	}

	if (dwTickCount - gdwLastFpsTick > 1000)
	{
		gnFramesPerSecond = gnFramesThisSecond;
		gnFramesThisSecond = 0;
		gdwLastFpsTick = dwTickCount;
	}
	else
	{
		++gnFramesThisSecond;
		++gnFramesSinceDebugStart;
	}

	if (!gbShowDebugInfo)
	{
		gdwDebugStartTick = 0;
		return;
	}

	D2GFX_OutputString(10, 2, "%d FPS  %d Skip", gnFramesPerSecond, sub_6FAABFD0());
	D2GFX_OutputString(160, 2, "Ping: %d", sub_6FAA9AD0());

	MEMORYSTATUS memoryStatus;
	memoryStatus.dwLength = sizeof(memoryStatus);
	GlobalMemoryStatus(&memoryStatus);
	D2GFX_OutputString(10, 16, "Phys:%d/%dm", ((memoryStatus.dwTotalPhys - memoryStatus.dwAvailPhys) >> 20) + 1, (memoryStatus.dwTotalPhys >> 20) + 1);
	D2GFX_OutputString(160, 16, "Page:%d/%dm", ((memoryStatus.dwTotalPageFile - memoryStatus.dwAvailPageFile) >> 20) + 1, (memoryStatus.dwTotalPageFile >> 20) + 1);

	const char* szDisplayType = nullptr;
	switch (D2GFX_GetDisplayType())
	{
	case DISPLAYTYPE_GDI:
		szDisplayType = "Software";
		break;
	case DISPLAYTYPE_SOFTWARE:
		szDisplayType = "Software";
		break;
	case DISPLAYTYPE_DDRAW:
		szDisplayType = "DirectDraw";
		break;
	case DISPLAYTYPE_GLIDE:
		szDisplayType = "Glide";
		break;
	case DISPLAYTYPE_OPENGL:
		szDisplayType = "OpenGL";
		break;
	case DISPLAYTYPE_DIRECT3D:
		szDisplayType = "Direct3D";
		break;
	case DISPLAYTYPE_RAVE:
		szDisplayType = "RAVE";
		break;
	default:
		szDisplayType = "Unknown";
		break;
	}

	char szVideo[16];
	sprintf(szVideo, szDisplayType);
	D2GFX_OutputString(500, 2, "Video: %s", szVideo);

	if (gbHideCacheStats)
	{
		return;
	}

	D2GFX_OutputString(10, 120, "GFX Memory->%i", sub_6FB5DA70());
	D2GFX_OutputString(10, 132, "COF Memory->%i of %i", sub_6FB5DA80(), sub_6FB5DA90());
	D2GFX_OutputString(10, 144, "Sprite Cache Memory->%i of %i", D2CMP_10060(D2CMP_10061()));
	D2GFX_OutputString(10, 156, "Async Files->%i", FOG_10098());
	D2GFX_OutputString(10, 168, "CelData Cache Memory->%i of %i", D2CMP_10063(D2CMP_10064()));
	MEMORY_Nop();

	int32_t nAccesses = 0;
	int32_t nMisses = 0;
	int32_t nSize = 0;
	int32_t nUtilization = 0;
	D2CMP_10092(&nSize, &nMisses, &nAccesses, &nUtilization);

	char szBuffer[1024];
	if (nAccesses > 0)
	{
		sprintf(szBuffer, "Tile Cache: (%.2fK) %3.2f%%, Misses: %d, %d percent utilized\n", (double)nSize * (1.0 / 1024.0), (double)((float)nMisses * 100.0f / (float)nAccesses), nMisses, nUtilization);
		D2GFX_OutputString(10, 48, szBuffer);
	}

	uint32_t* pCacheResults = D2GFX_GetCacheResults();
	if (!pCacheResults)
	{
		return;
	}

	if (pCacheResults[0])
	{
		sprintf(szBuffer, "Floor Cache: (%.2fK) Misses: %d\n", (double)((float)pCacheResults[0] * (1.0f / 1024.0f)), pCacheResults[2]);
		D2GFX_OutputString(10, 60, szBuffer);
	}

	if (pCacheResults[3])
	{
		sprintf(szBuffer, "Subtile Cache: (%.2fK) Misses: %d\n", (double)((float)pCacheResults[3] * (1.0f / 1024.0f)), pCacheResults[5]);
		D2GFX_OutputString(10, 72, szBuffer);
	}

	for (int32_t i = 0; i < 3; ++i)
	{
		if (pCacheResults[6 + i])
		{
			sprintf(szBuffer, "Sprite Cache %d: (%.2fK) Misses: %d, Accesses Per Frame: %d\n", i + 1, (double)((float)pCacheResults[6 + i] * (1.0f / 1024.0f)), pCacheResults[12 + i], pCacheResults[18 + i]);
			D2GFX_OutputString(10, 84 + 12 * i, szBuffer);
		}
	}
}

//D2Client.0x6FAA2D30 (inlined)
static void WNDPROC_ResetCacheStats()
{
	if (uint32_t* pCacheResults = D2GFX_GetCacheResults())
	{
		pCacheResults[1] = 0;
		pCacheResults[2] = 0;
		pCacheResults[4] = 0;
		pCacheResults[5] = 0;
		pCacheResults[9] = 0;
		pCacheResults[10] = 0;
		pCacheResults[11] = 0;
		pCacheResults[12] = 0;
		pCacheResults[13] = 0;
		pCacheResults[14] = 0;
		pCacheResults[18] = 0;
		pCacheResults[19] = 0;
		pCacheResults[20] = 0;
		pCacheResults[24] = 0;
		pCacheResults[25] = 0;
		pCacheResults[26] = 0;
	}

	D2CMP_10093();
}

//D2Client.0x6FAA2D30
void __fastcall WNDPROC_ToggleDebugInfo()
{
	gbHideCacheStats = FALSE;
	gbShowDebugInfo = !gbShowDebugInfo;
	if (gbShowDebugInfo)
	{
		WNDPROC_ResetCacheStats();
	}
}

//D2Client.0x6FAA2DA0
void __fastcall WNDPROC_ToggleDebugInfoNoCacheStats()
{
	if (gbHideCacheStats || !gbShowDebugInfo)
	{
		gbShowDebugInfo = !gbShowDebugInfo;
		gbHideCacheStats = FALSE;
		if (gbShowDebugInfo)
		{
			WNDPROC_ResetCacheStats();
		}
	}

	gbHideCacheStats = TRUE;
}

//D2Client.0x6FAA2E30
void __fastcall WNDPROC_InitializeFloorDrawContext()
{
	gFloorDrawContext.dwLastFloorParticleTick = 0;
	gFloorDrawContext.dwLastFloorSplashTick = 0;
	atexit(WNDPROC_DestroyFloorDrawContext);
}

//D2Client.0x6FAA2E50
void __cdecl WNDPROC_DestroyFloorDrawContext()
{
}

//D2Client.0x6FAA2E60
void __fastcall WNDPROC_DrawFloor(D2GameViewStrc* pView, int32_t nUnused)
{
	DFLOOR_DrawFloor(&gFloorDrawContext, nUnused, pView);
}

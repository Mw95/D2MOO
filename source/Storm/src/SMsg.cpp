#include "StormInternal.h"

#include <storm/List.hpp>

// Window messages dispatching, built on top of SEvt.
// The window handle is used as the event subtype.

#define SMSG_TYPE_MESSAGE  'SMSG' // id is the message
#define SMSG_TYPE_COMMAND  'SMSH' // id is the command identifier
#define SMSG_TYPE_KEYDOWN  'SMSI' // id is the virtual key code
#define SMSG_TYPE_KEYUP    'SMSJ' // id is the virtual key code

struct WNDREC : TSLinkedNode<WNDREC>
{
	HWND hWnd;
};

// Storm.0x6FFEC4C4
static STORM_LIST(WNDREC) sgWindowList;
// Storm.0x6FFEC4D0
static HWND sghDefaultWindow;


// Storm.0x6FFCD1D0
static WNDREC* SMsgFindWindow(HWND hWnd)
{
	for (WNDREC* pWindow = sgWindowList.Head(); pWindow; pWindow = pWindow->Next())
	{
		if (pWindow->hWnd == hWnd)
		{
			return pWindow;
		}
	}
	return nullptr;
}

// Storm.0x6FFCD530
static WNDREC* SMsgAddWindow(HWND hWnd)
{
	WNDREC* pWindow = sgWindowList.NewNode(0, 0, 0);
	sgWindowList.LinkToTail(pWindow);
	pWindow->hWnd = hWnd;
	return pWindow;
}

// Storm.0x6FFCD140
static void SMsgRemoveWindow(HWND hWnd)
{
	if (hWnd == sghDefaultWindow)
	{
		sghDefaultWindow = nullptr;
	}

	WNDREC* pWindow = SMsgFindWindow(hWnd);
	if (!pWindow)
	{
		return;
	}

	SEvtUnregisterType(SMSG_TYPE_MESSAGE, (uint32_t)(uintptr_t)hWnd);
	SEvtUnregisterType(SMSG_TYPE_COMMAND, (uint32_t)(uintptr_t)hWnd);
	SEvtUnregisterType(SMSG_TYPE_KEYUP, (uint32_t)(uintptr_t)hWnd);
	SEvtUnregisterType(SMSG_TYPE_KEYDOWN, (uint32_t)(uintptr_t)hWnd);

	sgWindowList.UnlinkNode(pWindow);
	SMemFree(pWindow, typeid(WNDREC).name(), SERR_LINECODE_OBJECT, 0);
}

// Storm.0x6FFCD120
BOOL SMsgDestroy()
{
	while (WNDREC* pWindow = sgWindowList.Head())
	{
		SMsgRemoveWindow(pWindow->hWnd);
	}
	return TRUE;
}

// Storm.0x6FFCD4E0
static BOOL SMsgRegister(uint32_t dwType, HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(pHandler);
	STORM_VALIDATE_END(FALSE);

	if (!SMsgFindWindow(hWnd))
	{
		SMsgAddWindow(hWnd);
	}
	return SEvtRegisterHandler(dwType, (uint32_t)(uintptr_t)hWnd, nId, 0, (SEVTHANDLER)pHandler);
}

// Storm.0x6FFCD650
static BOOL SMsgUnregister(uint32_t dwType, HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	if (!SMsgFindWindow(hWnd))
	{
		SMsgAddWindow(hWnd);
	}
	return SEvtUnregisterHandler(dwType, (uint32_t)(uintptr_t)hWnd, nId, (SEVTHANDLER)pHandler);
}

// Storm.0x6FFCD3D0
static LRESULT CALLBACK SMsgWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bUseResult = FALSE;
	LRESULT lResult = 0;
	if (SMsgDispatchMessage(hWnd, uMsg, wParam, lParam, &bUseResult, &lResult) && bUseResult)
	{
		return lResult;
	}
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

// Storm.#412
BOOL __stdcall SMsgDispatchMessage(HWND hWnd, DWORD messageID, WPARAM wParam, LPARAM lParam, BOOL* bUseResult, LRESULT* pResult)
{
	if (bUseResult)
	{
		*bUseResult = FALSE;
	}
	if (pResult)
	{
		*pResult = 0;
	}

	SMSGHANDLER_PARAMS params;
	params.hWindow = hWnd;
	params.nMessage = messageID;
	params.wParam = wParam;
	params.lParam = lParam;
	params.nNotifyCode = messageID == WM_COMMAND ? HIWORD(wParam) : 0;
	params.pExtra = nullptr;
	params.bUseResult = FALSE;
	params.lResult = 0;

	// Handlers registered for the default window also receive the messages of the windows without handle
	HWND hTarget = hWnd;
	while (true)
	{
		SEvtDispatch(SMSG_TYPE_MESSAGE, (uint32_t)(uintptr_t)hTarget, messageID, &params);
		if (messageID == WM_COMMAND)
		{
			SEvtDispatch(SMSG_TYPE_COMMAND, (uint32_t)(uintptr_t)hTarget, LOWORD(wParam), &params);
		}
		else if (messageID == WM_KEYDOWN)
		{
			SEvtDispatch(SMSG_TYPE_KEYDOWN, (uint32_t)(uintptr_t)hTarget, wParam, &params);
		}
		else if (messageID == WM_KEYUP)
		{
			SEvtDispatch(SMSG_TYPE_KEYUP, (uint32_t)(uintptr_t)hTarget, wParam, &params);
		}

		if (!hTarget || hTarget != sghDefaultWindow)
		{
			break;
		}
		hTarget = nullptr;
	}

	if (messageID == WM_NCDESTROY)
	{
		SMsgRemoveWindow(hWnd);
	}

	if (bUseResult)
	{
		*bUseResult = params.bUseResult;
	}
	if (pResult)
	{
		*pResult = params.lResult;
	}
	return TRUE;
}

// Storm.#413
WPARAM __stdcall SMsgDoMessageLoop(SMSGIDLEPROC pIdleProc, BOOL bCleanUponQuit)
{
	MSG msg;
	uint32_t nIdleCount = 0;
	while (true)
	{
		while (!PeekMessageA(&msg, nullptr, 0, 0, PM_NOREMOVE) && pIdleProc && pIdleProc(nIdleCount++))
		{
		}
		nIdleCount = 0;

		if (!GetMessageA(&msg, nullptr, 0, 0))
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	if (bCleanUponQuit)
	{
		StormDestroy();
	}
	return msg.wParam;
}

// Storm.#414
BOOL __stdcall SMsgRegisterCommand(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgRegister(SMSG_TYPE_COMMAND, hWnd, nId, pHandler);
}

// Storm.#415
BOOL __stdcall SMsgRegisterKeyDown(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgRegister(SMSG_TYPE_KEYDOWN, hWnd, nId, pHandler);
}

// Storm.#416
BOOL __stdcall SMsgRegisterKeyUp(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgRegister(SMSG_TYPE_KEYUP, hWnd, nId, pHandler);
}

// Storm.#417
BOOL __stdcall SMsgRegisterMessage(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgRegister(SMSG_TYPE_MESSAGE, hWnd, nId, pHandler);
}

// Storm.#418
BOOL __stdcall SMsgPopRegisterState(HWND hWnd)
{
	SEvtPopState(SMSG_TYPE_COMMAND, (uint32_t)(uintptr_t)hWnd);
	SEvtPopState(SMSG_TYPE_KEYDOWN, (uint32_t)(uintptr_t)hWnd);
	SEvtPopState(SMSG_TYPE_KEYUP, (uint32_t)(uintptr_t)hWnd);
	SEvtPopState(SMSG_TYPE_MESSAGE, (uint32_t)(uintptr_t)hWnd);
	return TRUE;
}

// Storm.#419
BOOL __stdcall SMsgPushRegisterState(HWND hWnd)
{
	SEvtPushState(SMSG_TYPE_COMMAND, (uint32_t)(uintptr_t)hWnd);
	SEvtPushState(SMSG_TYPE_KEYDOWN, (uint32_t)(uintptr_t)hWnd);
	SEvtPushState(SMSG_TYPE_KEYUP, (uint32_t)(uintptr_t)hWnd);
	SEvtPushState(SMSG_TYPE_MESSAGE, (uint32_t)(uintptr_t)hWnd);
	return TRUE;
}

// Storm.#511
BOOL __stdcall SMsgBreakHandlerChain(SMSGHANDLER_PARAMS* pData)
{
	return SEvtBreakHandlerChain(pData);
}

// Storm.#512
BOOL __stdcall SMsgUnregisterCommand(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgUnregister(SMSG_TYPE_COMMAND, hWnd, nId, pHandler);
}

// Storm.#513
BOOL __stdcall SMsgUnregisterKeyDown(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgUnregister(SMSG_TYPE_KEYDOWN, hWnd, nId, pHandler);
}

// Storm.#514
BOOL __stdcall SMsgUnregisterKeyUp(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgUnregister(SMSG_TYPE_KEYUP, hWnd, nId, pHandler);
}

// Storm.#515
BOOL __stdcall SMsgUnregisterMessage(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
{
	return SMsgUnregister(SMSG_TYPE_MESSAGE, hWnd, nId, pHandler);
}

// Storm.#516
WNDPROC __stdcall SMsgGetDispatcher(uint32_t dwReserved)
{
	STORM_VALIDATE_BEGIN;
	STORM_VALIDATE_ARG(!dwReserved);
	STORM_VALIDATE_END(nullptr);

	return SMsgWindowProc;
}

// Storm.#517
BOOL __stdcall SMsgSetDefaultWindow(HWND hWnd)
{
	sghDefaultWindow = hWnd;
	return TRUE;
}

// Storm.#518
HWND __cdecl SMsgGetDefaultWindow()
{
	return sghDefaultWindow;
}

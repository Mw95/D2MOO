#pragma once

#include <D2Client.h>


enum D2C_WindowMessageHandlerType
{
	WINDOW_MESSAGE_HANDLER_MESSAGE = 0,
	WINDOW_MESSAGE_HANDLER_COMMAND = 1,
	WINDOW_MESSAGE_HANDLER_KEYUP = 2,
	WINDOW_MESSAGE_HANDLER_KEYDOWN = 3,
};

#pragma pack(push, 1)
struct D2WindowMessageHandlerStrc
{
	int32_t nType;							//0x00 D2C_WindowMessageHandlerType
	uint32_t nId;							//0x04
	SMSGHANDLER pHandler;					//0x08
};

#pragma pack(pop)


//D2Client.0x6FB74970
extern int32_t gnDisplayType;
//D2Client.0x6FB9A968
extern uint8_t gbWindowed;
//D2Client.0x6FB9A96C
extern int32_t gnFramesPerSecond;
//D2Client.0x6FB9A990
extern D2FloorDrawContextStrc gFloorDrawContext;


//D2Client.0x6FAA26C0
void __fastcall WNDPROC_RegisterMessageHandlers(HWND hWnd, const D2WindowMessageHandlerStrc* pHandlers, uint32_t nHandlers);
//D2Client.0x6FAA2780
void __fastcall WNDPROC_UnregisterMessageHandlers(HWND hWnd, const D2WindowMessageHandlerStrc* pHandlers, uint32_t nHandlers);
//D2Client.0x6FAA2840
void __fastcall WNDPROC_PushRegisterState();
//D2Client.0x6FAA2850
void __fastcall WNDPROC_PopRegisterState();
//D2Client.0x6FAA2860
void __fastcall WNDPROC_SetGamma(uint32_t nGamma);
//D2Client.0x6FAA2870
void __fastcall WNDPROC_SetDisplayTypeGDI();
//D2Client.0x6FAA2880
void __fastcall WNDPROC_SetDisplayTypeGlide();
//D2Client.0x6FAA2890
void __fastcall WNDPROC_SetDisplayTypeOpenGL();
//D2Client.0x6FAA28A0
void __fastcall WNDPROC_SetDisplayTypeDirect3D();
//D2Client.0x6FAA28B0
void __fastcall WNDPROC_SetDisplayTypeRave();
//D2Client.0x6FAA28C0
int32_t __fastcall WNDPROC_GetDisplayType();
//D2Client.0x6FAA28D0
BOOL __fastcall WNDPROC_IsHardwareAccelerated();
//D2Client.0x6FAA28E0
void __fastcall WNDPROC_DrawDebugInfo();
//D2Client.0x6FAA2D30
void __fastcall WNDPROC_ToggleDebugInfo();
//D2Client.0x6FAA2DA0
void __fastcall WNDPROC_ToggleDebugInfoNoCacheStats();
//D2Client.0x6FAA2E30
void __fastcall WNDPROC_InitializeFloorDrawContext();
//D2Client.0x6FAA2E50
void __cdecl WNDPROC_DestroyFloorDrawContext();
//D2Client.0x6FAA2E60
void __fastcall WNDPROC_DrawFloor(D2GameViewStrc* pView, int32_t nUnused);

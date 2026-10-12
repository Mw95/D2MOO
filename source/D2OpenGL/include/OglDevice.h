#pragma once

#include <cstdint>

#include <Windows.h>


// OpenGL presentation of the frames.
// Frames are written as 32 bits BGRA pixels into the frame buffer returned by DEVICE_GetFrameBuffer,
// then uploaded to a texture drawn over the whole client area of the window by DEVICE_Present.
// Only OpenGL 1.1 functions are used so that any implementation works, extensions are optional.

// Creates the OpenGL context of the window. The window class must have the CS_OWNDC style.
BOOL __fastcall DEVICE_Create(HWND hWnd);
// Destroys the OpenGL context and all the resources
void __fastcall DEVICE_Destroy();
// Returns TRUE if the OpenGL context exists
BOOL __fastcall DEVICE_IsCreated();
// (Re)creates the texture and frame buffer for frames of the given size
BOOL __fastcall DEVICE_SetFrameSize(int32_t nWidth, int32_t nHeight);
// Returns the nWidth * nHeight BGRA frame buffer, the pitch is nWidth * 4
uint32_t* __fastcall DEVICE_GetFrameBuffer();
// Uploads the frame buffer and presents it
void __fastcall DEVICE_Present();
// Enables or disables vertical synchronization, if supported
void __fastcall DEVICE_SetVSync(BOOL bVSync);
// Changes the resolution of the screen for fullscreen mode
BOOL __fastcall DEVICE_SetDisplayMode(int32_t nWidth, int32_t nHeight);
// Restores the resolution of the desktop
void __fastcall DEVICE_RestoreDisplayMode();

#pragma once

#include <cstdint>

#include <Windows.h>


// OpenGL 3.3 core presentation of the frames.
// Game frames are uploaded as 8 bits indices and converted with the palette by a shader into an offscreen frame
// (DEVICE_PresentIndexed). Cutscenes are written as 32 bits BGRA pixels into the frame buffer returned by
// DEVICE_GetFrameBuffer and uploaded directly to the offscreen frame (DEVICE_PresentFrameBuffer).
// The offscreen frame is then scaled to the whole client area of the window with glBlitFramebuffer.

// Creates the OpenGL 3.3 core context of the window. The window class must have the CS_OWNDC style.
BOOL __fastcall DEVICE_Create(HWND hWnd);
// Destroys the OpenGL context and all the resources
void __fastcall DEVICE_Destroy();
// Returns TRUE if the OpenGL context exists
BOOL __fastcall DEVICE_IsCreated();
// (Re)creates the textures and frame buffer for frames of the given size
BOOL __fastcall DEVICE_SetFrameSize(int32_t nWidth, int32_t nHeight);
// Converts the nWidth * nHeight 8 bits indices with the 256 colors palette (0xAARRGGBB) and presents them
void __fastcall DEVICE_PresentIndexed(const uint8_t* pIndices, const uint32_t* pPalette);
// Returns the nWidth * nHeight BGRA frame buffer, the pitch is nWidth * 4
uint32_t* __fastcall DEVICE_GetFrameBuffer();
// Uploads the frame buffer and presents it
void __fastcall DEVICE_PresentFrameBuffer();
// Enables or disables vertical synchronization, if supported
void __fastcall DEVICE_SetVSync(BOOL bVSync);
// Changes the resolution of the screen for fullscreen mode
BOOL __fastcall DEVICE_SetDisplayMode(int32_t nWidth, int32_t nHeight);
// Restores the resolution of the desktop
void __fastcall DEVICE_RestoreDisplayMode();

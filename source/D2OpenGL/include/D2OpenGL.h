#pragma once

#include <D2Gfx.h>


// OpenGL renderer for D2Gfx (DISPLAYTYPE_OPENGL), loaded by D2Gfx.dll like D2Gdi.dll, D2DDraw.dll, D2Glide.dll and D2Direct3D.dll.
// The original game does not ship this renderer.

//D2OpenGL (#10000)
D2OPENGL_DLL_DECL D2GraphicsInterfaceStrc* __fastcall D2OpenGL_GetGraphicsInterface();

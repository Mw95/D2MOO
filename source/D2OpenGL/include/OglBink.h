#pragma once

#include <cstdint>

#include <Windows.h>

#include <D2Constants.h>


// Bink cutscenes, ported from D2DDraw.dll (ddBink.cpp). Frames are decoded to 32 bits and presented with OpenGL.

//pfOpenSmackCutscene
void __fastcall OGL_OpenSmackCutscene(const char* szFile, D2GameResolutionMode nResolutionMode, void* pfFrame);
//pfCheckCutScene
BOOL __fastcall OGL_CheckCutScene();

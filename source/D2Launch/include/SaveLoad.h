#pragma once

#include <Windows.h>
#include <cstdint>

#include <D2Config.h>

//D2Launch.0x6FA279F0
void __fastcall SAVE_CreateCharacter(const char* szName, uint8_t nClass, D2CharacterPreviewInfoStrc* pPreviewInfo, uint16_t nSaveFlags);
//D2Launch.0x6FA27B50
void __fastcall SAVE_SetRealmCharacter(BOOL bRealm);
//D2Launch.0x6FA27B60
BOOL __fastcall SAVE_WriteCharacterFile(const char* szName);
//D2Launch.0x6FA27C00
void __fastcall SAVE_DeleteCharacter(const char* pszFileName, const char* szSubDirectory);
//D2Launch.0x6FA27D50
void __fastcall SAVE_InitializeHashes();
//D2Launch.0x6FA27D80
BOOL __fastcall SAVE_ReadCharacterPreview(const char* pszFileName, uint8_t* pPreviewInfo);
//D2Launch.0x6FA27F80
BOOL __fastcall SAVE_ConvertCharacterToExpansion(const char* szName);

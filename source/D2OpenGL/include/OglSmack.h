#pragma once

#include <cstdint>


// Smacker and PCX banners (468x60) drawn into the 8 bits back buffer, ported from D2Gdi.dll (gdiSmack.cpp)

#pragma pack(push, 1)
// Context passed by D2Win to pfDecodeSmacker, pfPlaySmacker and pfCloseSmacker
struct D2GfxSmackContextStrc
{
    void* pHandle;                              //0x00 D2SmackStrc* for SMACKTYPE_SMACKER
    uint8_t nType;                              //0x04 D2GfxSmackType
    uint8_t pad0x05[3];                         //0x05
    int32_t nX;                                 //0x08
    int32_t nY;                                 //0x0C Bottom of the banner
};
#pragma pack(pop)

enum D2GfxSmackType : uint8_t
{
    SMACKTYPE_NONE = 0,
    SMACKTYPE_PCX = 'p',
    SMACKTYPE_SMACKER = 's',
};


//pfDecodeSmacker
void __fastcall OGL_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion);
//pfPlaySmacker
void __fastcall OGL_PlaySmacker(void* pContext);
//pfCloseSmacker
void __fastcall OGL_CloseSmacker(void* pContext);

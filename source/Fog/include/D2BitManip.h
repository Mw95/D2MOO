#pragma once

#include <D2BasicTypes.h>

#include <Fog.h>

#pragma pack(1)


extern "C" FOG_DLL_DECL const uint32_t gdwBitMasks[];
extern "C" FOG_DLL_DECL const uint32_t gdwInvBitMasks[];


struct D2BitBufferStrc
{
	uint8_t* pBuffer;							//0x00
	int32_t nBits;								//0x04
	int32_t nPos;								//0x08
	int32_t nPosBits;							//0x0C
	BOOL bFull;									//0x10
};

struct D2BitCodeStrc
{
	uint32_t dwValue;							//0x00
	uint32_t dwBits;							//0x04
};

// Packs strings using only nPackedBits per character
struct FOGStringPack							// sizeof 0x204
{
	int32_t nPackedBits;						//0x000
	// Index of each character is stored at [character], the character of each index at [0xFF + index]
	uint8_t pTable[512];						//0x004
};

#pragma pack()

/*
Function:		BITMANIP_Initialize
Address:		Fog.#10126
Notes:
*/
FOG_DLL_DECL void __stdcall BITMANIP_Initialize(D2BitBufferStrc* pBuffer, uint8_t* pBitStream, size_t nSize);

/*
Function:		BITMANIP_GetSize
Address:		Fog.#10127
Notes:
*/
FOG_DLL_DECL size_t __stdcall BITMANIP_GetSize(D2BitBufferStrc* pBuffer);

/*
Function:		BITMANIP_Write
Address:		Fog.#10128
Notes:
*/
FOG_DLL_DECL void __stdcall BITMANIP_Write(D2BitBufferStrc* pBuffer, uint32_t dwValue, uint32_t dwBits);

/*
Function:		BITMANIP_ReadSigned
Address:		Fog.#10129
Notes:
*/
FOG_DLL_DECL int __stdcall BITMANIP_ReadSigned(D2BitBufferStrc* pBuffer, int nBits);

/*
Function:		BITMANIP_Read
Address:		Fog.#10130
Notes:
*/
FOG_DLL_DECL uint32_t __stdcall BITMANIP_Read(D2BitBufferStrc* pBuffer, int nBits);

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10131
Notes:
*/
FOG_DLL_DECL void __stdcall BITMANIP_GoToNextByte(D2BitBufferStrc* pBuffer);




/*
Function:		BITMANIP_SetBitState
Address:		Fog.#10118
Notes:
*/
FOG_DLL_DECL void __stdcall BITMANIP_SetBitState(uint8_t* pBitStream, int nBit);

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10119
Notes:
*/
FOG_DLL_DECL int __stdcall BITMANIP_GetBitState(uint8_t* pBitStream, int nBit);

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10120
Notes:
*/
FOG_DLL_DECL void __stdcall BITMANIP_MaskBitstate(uint8_t* pBitStream, int nBit);

// 1.10f: 0x6FF53390 (#10121)
FOG_DLL_DECL void __stdcall BITMANIP_ToggleBitState(uint8_t* pBitStream, int nBit);
// 1.10f: 0x6FF533B0 (#10122)
FOG_DLL_DECL void __stdcall BITMANIP_And(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits);
// 1.10f: 0x6FF53460 (#10123)
FOG_DLL_DECL void __stdcall BITMANIP_Or(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits);
// 1.10f: 0x6FF53510 (#10124)
FOG_DLL_DECL void __stdcall BITMANIP_Not(const uint8_t* pBitStream, uint8_t* pDest, int nBits);
// 1.10f: 0x6FF535A0 (#10125)
FOG_DLL_DECL void __stdcall BITMANIP_Xor(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits);
// 1.10f: 0x6FF538C0 (#10132)
FOG_DLL_DECL void __stdcall BITMANIP_WriteCode(D2BitBufferStrc* pBuffer, const D2BitCodeStrc* pCodes, int nCode);
// 1.10f: 0x6FF538E0 (#10133)
FOG_DLL_DECL int __stdcall BITMANIP_ReadTreeValue(D2BitBufferStrc* pBuffer, const int* pTree);

// 1.10f: 0x6FF53A10 (#10134)
FOG_DLL_DECL void __stdcall STRPACK_Initialize(FOGStringPack* pStrPack, int nMaxBits, const char* szCharacters);
// 1.10f: 0x6FF53B80 (#10135)
FOG_DLL_DECL void __stdcall STRPACK_PackString(FOGStringPack* pStrPack, const char* szString, uint8_t* pbBuffer, int nBufferSize, BOOL bForceTerminator);
// 1.10f: 0x6FF53CA0 (#10136)
FOG_DLL_DECL void __stdcall STRPACK_UnpackString(FOGStringPack* pStrPack, char* szString, uint8_t* pbBuffer, int nBufferSize, int nStringSize);


// Sets bits of the mask to newBitValue, and returns wether the value changed
template<typename T>
bool BITMANIP_SetBitsValueForMask(T& var, uint64_t mask, bool newBitValue)
{
	T previousValue = var;
	if (newBitValue)
	{
		var |= mask;
	}
	else
	{
		var &= ~mask;
	}
	return previousValue != var;
}

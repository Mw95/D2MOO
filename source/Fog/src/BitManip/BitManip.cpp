#include "D2BitManip.h"


// Fog.6FF71308
extern "C" const uint32_t gdwBitMasks[] =
{
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000,
};

// Fog.6FF71388
extern "C" const uint32_t gdwInvBitMasks[] =
{
	0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7, 0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
	0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF, 0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
	0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF, 0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
	0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF, 0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF,
};

//Fog.0x6FF71408
uint32_t gdw_6FF71408[] =
{
	0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF
};

//Fog.0x6FF7142C
uint8_t gn_6FF7142C[] =
{
	0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00
};


/*
Function:		BITMANIP_Initialize
Address:		Fog.#10126
Notes:			
*/
void __stdcall BITMANIP_Initialize(D2BitBufferStrc* pBuffer, uint8_t* pBitStream, size_t nSize)
{
	if (!pBuffer)
	{
		return;
	}

	pBuffer->nPos = 0;
	pBuffer->pBuffer = pBitStream;
	pBuffer->nBits = 8 * nSize;
	pBuffer->nPosBits = 0;
	pBuffer->bFull = FALSE;
}

/*
Function:		BITMANIP_GetSize
Address:		Fog.#10127
Notes:
*/
size_t __stdcall BITMANIP_GetSize(D2BitBufferStrc* pBuffer)
{
	return (pBuffer->nPosBits) ? (pBuffer->nPos + 1) : pBuffer->nPos;
}

/*
Function:		BITMANIP_Write
Address:		Fog.#10128
Notes:
*/
void __stdcall BITMANIP_Write(D2BitBufferStrc* pBuffer, uint32_t dwValue, uint32_t dwBits)
{
	uint32_t dwBitsLeft = dwBits;
	uint32_t dwValueEx = dwValue;

	if ((signed int)(dwBits + pBuffer->nPosBits + 8 * pBuffer->nPos) <= (signed int)pBuffer->nBits)
	{
		if (!pBuffer->nPosBits)
		{
			*pBuffer->pBuffer = 0;
		}

		if (dwBits > 0)
		{
			do
			{
				size_t n = 8 - pBuffer->nPosBits;
				if (n > dwBitsLeft)
				{
					n = dwBitsLeft;
				}

				*pBuffer->pBuffer |= ((uint8_t)dwValueEx & gdw_6FF71408[n]) << pBuffer->nPosBits;

				pBuffer->nPosBits += n;
				if (pBuffer->nPosBits != 8)
				{
					break;
				}

				pBuffer->pBuffer = pBuffer->pBuffer + 1;
				++pBuffer->nPos;
				pBuffer->nPosBits = 0;

				if ((signed int)(8 * pBuffer->nPos) < (signed int)pBuffer->nBits)
				{
					*pBuffer->pBuffer = 0;
				}

				dwBitsLeft -= n;
				dwValueEx >>= n;
			}
			while (dwBitsLeft > 0);
		}
	}
	else
	{
		pBuffer->bFull = TRUE;
		pBuffer->nPosBits = 0;
		pBuffer->nPos = pBuffer->nBits / 8;
	}
}

/*
Function:		BITMANIP_ReadSigned
Address:		Fog.#10129
Notes:
*/
int __stdcall BITMANIP_ReadSigned(D2BitBufferStrc* pBuffer, int nBits)
{
	int nResult = BITMANIP_Read(pBuffer, nBits);

	if (nBits < 32)
	{
		if ((1 << (nBits - 1)) & nResult)
		{
			nResult |= ~((1 << nBits) - 1);
		}
	}

	return nResult;
}

/*
Function:		BITMANIP_Read
Address:		Fog.#10130
Notes:
*/
uint32_t __stdcall BITMANIP_Read(D2BitBufferStrc* pBuffer, int nBits)
{
	int n = pBuffer->nPosBits + nBits + 8 * pBuffer->nPos - pBuffer->nBits;

	if ((signed int)n < 0)
	{
		n = 0;
	}

	uint32_t dwBitsLeft = nBits - n;
	if (n)
	{
		pBuffer->bFull = TRUE;
	}

	uint32_t dwValue = 0;
	uint32_t dw = 0;

	if (dwBitsLeft > 0)
	{
		do
		{
			size_t i = 8 - pBuffer->nPosBits;
			if (i > dwBitsLeft)
			{
				i = dwBitsLeft;
			}

			dwBitsLeft -= i;
			dwValue += (gdw_6FF71408[i] & ((uint8_t)(*pBuffer->pBuffer & gn_6FF7142C[pBuffer->nPosBits]) >> pBuffer->nPosBits)) << dw;
			dw += i;
			pBuffer->nPosBits += i;

			if (pBuffer->nPosBits == 8)
			{
				++pBuffer->nPos;
				pBuffer->pBuffer = pBuffer->pBuffer + 1;
				pBuffer->nPosBits = 0;
			}
		}
		while (dwBitsLeft > 0);
	}

	return dwValue;
}

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10131
Notes:
*/
void __stdcall BITMANIP_GoToNextByte(D2BitBufferStrc* pBuffer)
{
	if (pBuffer->nPosBits)
	{
		++pBuffer->nPos;
		pBuffer->pBuffer = pBuffer->pBuffer + 1;
		pBuffer->nPosBits = 0;

		if ((signed int)(8 * pBuffer->nPos) < (signed int)pBuffer->nBits)
		{
			*pBuffer->pBuffer = 0;
		}
	}
}



/*
Function:		BITMANIP_SetBitState
Address:		Fog.#10118
Notes:
*/
void __stdcall BITMANIP_SetBitState(uint8_t* pBitStream, int nBit)
{
	pBitStream[nBit >> 3] |= (uint8_t)gdwBitMasks[nBit & 7];
}

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10119
Notes:
*/
int __stdcall BITMANIP_GetBitState(uint8_t* pBitStream, int nBit)
{
	return pBitStream[nBit >> 3] & (uint8_t)gdwBitMasks[nBit & 7];
}

/*
Function:		BITMANIP_GoToNextByte
Address:		Fog.#10120
Notes:
*/
void __stdcall BITMANIP_MaskBitstate(uint8_t* pBitStream, int nBit)
{
	pBitStream[nBit >> 3] &= (uint8_t)gdwInvBitMasks[nBit & 7];
}

/*
Function:		FOG_ComputeChecksum
Address:		Fog.#10229
Notes:			Rotates the checksum left by one bit and adds each byte.
*/
uint32_t __stdcall FOG_ComputeChecksum(void* pData, size_t dwSize)
{
	const uint8_t* pBytes = (const uint8_t*)pData;
	uint32_t nChecksum = 0;
	for (int i = 0; i < (int)dwSize; ++i)
	{
		nChecksum = (nChecksum << 1) + pBytes[i] + (nChecksum >> 31);
	}
	return nChecksum;
}

/*
Function:		FOG_PopCount
Address:		Fog.#10230
Notes:			Returns the number of bits set in the buffer.
*/
uint32_t __stdcall FOG_PopCount(void* pData, size_t dwSize)
{
	const uint8_t* pBytes = (const uint8_t*)pData;
	uint32_t nCount = 0;
	for (const uint8_t* pByte = pBytes; pByte < pBytes + dwSize; ++pByte)
	{
		for (uint8_t nByte = *pByte; nByte; nByte &= nByte - 1)
		{
			++nCount;
		}
	}
	return nCount;
}

/*
Function:		FOG_LeadingZeroesCount
Address:		Fog.#10252
Notes:			Despite its name, returns the index of the lowest bit set (number of trailing zeroes), or -1 if nValue is 0.
*/
uint32_t __stdcall FOG_LeadingZeroesCount(uint32_t nValue)
{
	if (!nValue)
	{
		return (uint32_t)-1;
	}

	uint32_t nBit = 0;
	while (!(nValue & 1))
	{
		nValue >>= 1;
		++nBit;
	}
	return nBit;
}

/*
Function:		BITMANIP_ToggleBitState
Address:		Fog.#10121
Notes:
*/
void __stdcall BITMANIP_ToggleBitState(uint8_t* pBitStream, int nBit)
{
	pBitStream[nBit >> 3] ^= (uint8_t)gdwBitMasks[nBit & 7];
}

static int BITMANIP_GetByteCount(int nBits)
{
	return (nBits + 7) / 8;
}

/*
Function:		BITMANIP_And
Address:		Fog.#10122
Notes:			pDest = pBitStream1 & pBitStream2
*/
void __stdcall BITMANIP_And(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits)
{
	const int nBytes = BITMANIP_GetByteCount(nBits);
	for (int i = 0; i < nBytes; ++i)
	{
		pDest[i] = pBitStream1[i] & pBitStream2[i];
	}
}

/*
Function:		BITMANIP_Or
Address:		Fog.#10123
Notes:			pDest = pBitStream1 | pBitStream2
*/
void __stdcall BITMANIP_Or(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits)
{
	const int nBytes = BITMANIP_GetByteCount(nBits);
	for (int i = 0; i < nBytes; ++i)
	{
		pDest[i] = pBitStream1[i] | pBitStream2[i];
	}
}

/*
Function:		BITMANIP_Not
Address:		Fog.#10124
Notes:			pDest = ~pBitStream
*/
void __stdcall BITMANIP_Not(const uint8_t* pBitStream, uint8_t* pDest, int nBits)
{
	const int nBytes = BITMANIP_GetByteCount(nBits);
	for (int i = 0; i < nBytes; ++i)
	{
		pDest[i] = ~pBitStream[i];
	}
}

/*
Function:		BITMANIP_Xor
Address:		Fog.#10125
Notes:			pDest = pBitStream1 ^ pBitStream2
*/
void __stdcall BITMANIP_Xor(const uint8_t* pBitStream1, const uint8_t* pBitStream2, uint8_t* pDest, int nBits)
{
	const int nBytes = BITMANIP_GetByteCount(nBits);
	for (int i = 0; i < nBytes; ++i)
	{
		pDest[i] = pBitStream1[i] ^ pBitStream2[i];
	}
}

/*
Function:		BITMANIP_WriteCode
Address:		Fog.#10132
Notes:			Writes the code of index nCode from the table
*/
void __stdcall BITMANIP_WriteCode(D2BitBufferStrc* pBuffer, const D2BitCodeStrc* pCodes, int nCode)
{
	BITMANIP_Write(pBuffer, pCodes[nCode].dwValue, pCodes[nCode].dwBits);
}

/*
Function:		BITMANIP_ReadTreeValue
Address:		Fog.#10133
Notes:			Walks a binary tree stored as an array, one bit at a time.
				Negative entries are inner nodes, whose children are at index 2*i+2 and 2*i+3.
				Does not check for the end of the buffer.
*/
int __stdcall BITMANIP_ReadTreeValue(D2BitBufferStrc* pBuffer, const int* pTree)
{
	int nNode = 0;
	while (true)
	{
		const int nBit = (*pBuffer->pBuffer & gdwBitMasks[pBuffer->nPosBits]) >> pBuffer->nPosBits;
		++pBuffer->nPosBits;
		if (pBuffer->nPosBits == 8)
		{
			++pBuffer->pBuffer;
			pBuffer->nPosBits = 0;
			++pBuffer->nPos;
		}

		const int nIndex = nNode + nBit;
		if (pTree[nIndex] >= 0)
		{
			return pTree[nIndex];
		}
		nNode = 2 * nIndex + 2;
	}
}

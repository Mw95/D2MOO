#include "Raw.h"

#include <cstring>

#include <Fog.h>

#include "CelCmp.h"


//D2CMP.0x6FDFB7B0
void __fastcall RAW_CreateCels(D2CelCompressListStrc* pList, D2CellFileStrc* pCelFile)
{
	const uint32_t nFramesPerDirection = pList->nImages / pList->dwNumDirections;
	uint32_t nImage = 0;
	for (D2CelCompressImageStrc* pImage = pList->pFirstImage; pImage; pImage = pImage->pNext)
	{
		const uint32_t dwSize = 3 * pImage->dwWidth * pImage->dwHeight;
		D2GfxCellStrc* pCel = (D2GfxCellStrc*)D2_ALLOC(dwSize + offsetof(D2GfxCellStrc, pPixels) + 3);
		pCel->dwFlags = pImage->dwFlags;
		pCel->dwWidth = pImage->dwWidth;
		pCel->dwHeight = pImage->dwHeight;
		pCel->nXOffset = pImage->nXOffset;
		pCel->nYOffset = pImage->nYOffset;
		pCel->dwHardwareDataSize = 0;
		pCel->pCellNode = nullptr;
		pCel->dwLength = dwSize;
		memcpy(pCel->pPixels, pImage->pData, dwSize);

		const uint32_t nDirections = pList->dwNumDirections;
		int nGameDirection = 1;
		if (nDirections > 1)
		{
			nGameDirection = ((nImage / nFramesPerDirection) << 6) / nDirections;
		}

		const int nFileDirection = D2CMP_CelGameDirToFileDir(nGameDirection, nDirections);
		pCelFile->pGfxCells[nImage % nFramesPerDirection + nFileDirection * nFramesPerDirection] = pCel;
		++nImage;
	}
}

//D2CMP.0x6FDFB8B0
void __fastcall RAW_IteratePixels(D2GfxCellStrc* pCel, D2CMPPixelCallback pfnCallback, uint32_t dwTransparentColor)
{
	const uint32_t dwTransparent = dwTransparentColor & 0xFFFFFF;
	const uint8_t* pPixel = pCel->pPixels;
	for (uint32_t i = 0; i < pCel->dwWidth * pCel->dwHeight; ++i)
	{
		const uint32_t dwColor = (pPixel[2] << 16) | (pPixel[1] << 8) | pPixel[0];
		pPixel += 3;
		if (dwColor != dwTransparent)
		{
			pfnCallback(dwColor);
		}
	}
}

#include "FastCmp.h"

#include <cstring>

#include <Fog.h>

#include "CelCmp.h"
#include "Count.h"


static BOOL gbCelDrawMode;							//D2CMP.0x6FE94BF0
static int gaLensEffectStart[80];					//D2CMP.0x6FE8E570
static int gaLensEffectEnd[80];						//D2CMP.0x6FE8E6B0
static int gaLensEffectOffsets[80][80];				//D2CMP.0x6FE8E7F0


//D2CMP.0x6FDF5C00
static BOOL __fastcall FASTCMP_ReturnTrue(void* pUnused1, void* pUnused2, int nUnused3, int nUnused4, int nUnused5)
{
	return TRUE;
}

// Inlined helper: places a cel in a cel file, given its index in the cel list
static void FASTCMP_SetCel(D2CellFileStrc* pCelFile, uint32_t nNumDirections, uint32_t nFramesPerDirection, uint32_t nImage, D2GfxCellStrc* pCel)
{
	int nGameDirection = 1;
	if (nNumDirections > 1)
	{
		nGameDirection = ((nImage / nFramesPerDirection) << 6) / nNumDirections;
	}

	const int nFileDirection = D2CMP_CelGameDirToFileDir(nGameDirection, nNumDirections);
	pCelFile->pGfxCells[nImage % nFramesPerDirection + nFileDirection * nFramesPerDirection] = pCel;
}

//D2CMP.0x6FDF5C10
void __fastcall FASTCMP_EncodeCelList(D2CelCompressListStrc* pList, D2CellFileStrc* pCelFile)
{
	D2_ASSERT(!( pList->dwFlags & CELFILE_24BIT ));

	const uint32_t nFramesPerDirection = pList->nImages / pList->dwNumDirections;
	uint32_t nImage = 0;
	for (D2CelCompressImageStrc* pImage = pList->pFirstImage; pImage; pImage = pImage->pNext)
	{
		uint8_t* pData = nullptr;
		uint32_t nSize = 0;
		FASTCMP_EncodeImage(pImage->pData, pImage->dwWidth, pImage->dwHeight, pImage->dwFlags, &pData, &nSize);

		D2GfxCellStrc* pCel = (D2GfxCellStrc*)D2_ALLOC(nSize + offsetof(D2GfxCellStrc, pPixels) + 3);
		pCel->dwFlags = pImage->dwFlags;
		pCel->dwWidth = pImage->dwWidth;
		pCel->dwHeight = pImage->dwHeight;
		pCel->nXOffset = pImage->nXOffset;
		pCel->nYOffset = pImage->nYOffset;
		pCel->dwHardwareDataSize = 0;
		pCel->pCellNode = nullptr;
		pCel->dwLength = nSize;
		memcpy(pCel->pPixels, pData, nSize);
		D2_FREE(pData);

		FASTCMP_SetCel(pCelFile, pList->dwNumDirections, nFramesPerDirection, nImage, pCel);
		++nImage;
	}
}

//D2CMP.0x6FDF5D60
void __fastcall FASTCMP_EncodeImage(const uint8_t* pPixels, uint32_t nWidth, uint32_t nHeight, uint32_t dwFlags, uint8_t** ppData, uint32_t* pSize)
{
	uint8_t* pBuffer = (uint8_t*)D2_ALLOC((2 * nWidth + 1) * nHeight);
	uint8_t* pDest = pBuffer;

	// Images are stored bottom-up unless the cel is flagged as top-down
	int nStride = nWidth;
	const uint8_t* pSrc = pPixels;
	if (!(dwFlags & GFXCELL_FLAG_TOPDOWN))
	{
		pSrc += (nHeight - 1) * nWidth;
		nStride = -(int)nWidth;
	}

	const uint8_t* pNextRow = pSrc + nStride;
	const uint8_t* pRowEnd = pSrc + nWidth;
	uint32_t nRow = 0;
	while (nRow < nHeight)
	{
		BOOL bCountEqualsDist = FALSE;
		BOOL bIsRemainingSame = FALSE;
		bool bEndOfRow = false;
		if (*pSrc == 0)
		{
			const int nSkip = CountConsecutiveFirst(pSrc, pRowEnd, DC6_MAX_RUN, &bCountEqualsDist, &bIsRemainingSame);
			if (bIsRemainingSame || bCountEqualsDist)
			{
				bEndOfRow = true;
			}
			else
			{
				*pDest++ = (uint8_t)nSkip | DC6_SKIP_FLAG;
				pSrc += nSkip;
			}
		}
		else
		{
			const int nCopy = CountConsecutiveDiff(pSrc, pRowEnd, 0, DC6_MAX_RUN, &bCountEqualsDist, &bIsRemainingSame);
			*pDest++ = (uint8_t)nCopy;
			for (int i = 0; i < nCopy; ++i)
			{
				*pDest++ = *pSrc++;
			}

			if (bCountEqualsDist)
			{
				bEndOfRow = true;
			}
		}

		if (bEndOfRow)
		{
			*pDest++ = DC6_END_OF_LINE;
			pSrc = pNextRow;
			pNextRow += nStride;
			pRowEnd += nStride;
			++nRow;
		}
	}

	*ppData = pBuffer;
	*pSize = pDest - pBuffer;
}

//D2CMP.0x6FDF5E60
void __fastcall FASTCMP_TransformCel(D2GfxCellStrc* pCel, const uint8_t* pTransform)
{
	uint32_t nLines = pCel->dwHeight;
	uint8_t* pData = pCel->pPixels;
	while (true)
	{
		const int8_t nCode = (int8_t)*pData++;
		if (nCode < 0)
		{
			if (!(nCode & 0x7F))
			{
				--nLines;
				if (!nLines)
				{
					return;
				}
			}
			continue;
		}

		for (int i = 0; i < nCode; ++i)
		{
			*pData = pTransform[*pData];
			++pData;
		}
	}
}

//D2CMP.0x6FDF5EA0
void __fastcall FASTCMP_ConvertCelFile24To8(D2CellFileStrc* pSrc, D2CellFileStrc* pDest, uint32_t dwTransparentColor, D2CMPColorConvertCallback pfnConvert)
{
	D2_ASSERT(pSrc->dwFlags & CELFILE_24BIT);

	const uint8_t* pTransparentColor = (const uint8_t*)&dwTransparentColor;
	for (int nCel = 0; nCel < pSrc->nDirections * pSrc->nFrames; ++nCel)
	{
		const D2GfxCellStrc* pSrcCel = pSrc->pGfxCells[nCel];
		const uint32_t nPixels = pSrcCel->dwWidth * pSrcCel->dwHeight;
		uint8_t* pPixels = (uint8_t*)D2_ALLOC(nPixels);

		const uint8_t* pSrcPixel = pSrcCel->pPixels;
		for (uint32_t i = 0; i < nPixels; ++i)
		{
			if (pSrcPixel[0] == pTransparentColor[0] && pSrcPixel[1] == pTransparentColor[1] && pSrcPixel[2] == pTransparentColor[2])
			{
				pPixels[i] = 0;
			}
			else
			{
				const uint8_t bTemp = pfnConvert(pSrcPixel[0], pSrcPixel[1], pSrcPixel[2]);
				D2_ASSERT(bTemp);
				pPixels[i] = bTemp;
			}
			pSrcPixel += 3;
		}

		uint8_t* pData = nullptr;
		uint32_t nSize = 0;
		FASTCMP_EncodeImage(pPixels, pSrcCel->dwWidth, pSrcCel->dwHeight, pSrcCel->dwFlags, &pData, &nSize);
		D2_FREE(pPixels);

		D2GfxCellStrc* pCel = (D2GfxCellStrc*)D2_ALLOC(nSize + offsetof(D2GfxCellStrc, pPixels) + 3);
		pCel->dwFlags = pSrcCel->dwFlags;
		pCel->dwWidth = pSrcCel->dwWidth;
		pCel->dwHeight = pSrcCel->dwHeight;
		pCel->nXOffset = pSrcCel->nXOffset;
		pCel->nYOffset = pSrcCel->nYOffset;
		pCel->dwHardwareDataSize = 0;
		pCel->pCellNode = nullptr;
		pCel->dwLength = nSize;
		memcpy(pCel->pPixels, pData, nSize);
		D2_FREE(pData);

		pDest->pGfxCells[nCel] = pCel;
	}
}

// Pixel operations used by the cel drawing functions
struct FASTCMP_CopyOp
{
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return nSrc; }
};

struct FASTCMP_PaletteOp
{
	const uint8_t* pPalette;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pPalette[nSrc]; }
};

struct FASTCMP_PaletteBlendOp
{
	const uint8_t* pPalette;
	const uint8_t* pBlendTable;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pBlendTable[(nDest << 8) + pPalette[nSrc]]; }
};

struct FASTCMP_PaletteShiftOp
{
	const uint8_t* pPalette;
	const uint8_t* pPalShift;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pPalette[pPalShift[nSrc]]; }
};

struct FASTCMP_ShiftOp
{
	const uint8_t* pPalShift;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pPalShift[nSrc]; }
};

struct FASTCMP_ShiftBlendOp
{
	const uint8_t* pPalShift;
	const uint8_t* pBlendTable;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pBlendTable[(nDest << 8) + pPalShift[nSrc]]; }
};

struct FASTCMP_BlendOp
{
	const uint8_t* pBlendTable;
	uint8_t operator()(uint8_t nSrc, uint8_t nDest) const { return pBlendTable[(nDest << 8) + nSrc]; }
};

// Draws nLines rows of DC6 control data, starting at pSrc (after the skipped lines)
template<bool bClip, typename PixelOp>
static void FASTCMP_DrawLines(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const PixelOp& tOp)
{
	uint8_t* pNextRow = pDest + nStride;
	int nCurrentX = nX;
	while (true)
	{
		const int8_t nCode = (int8_t)*pSrc++;
		if (nCode < 0)
		{
			const int nSkip = nCode & 0x7F;
			if (!nSkip)
			{
				--nLines;
				if (!nLines)
				{
					return;
				}
				pDest = pNextRow;
				pNextRow += nStride;
				nCurrentX = nX;
			}
			else
			{
				nCurrentX += nSkip;
				pDest += nSkip;
			}
			continue;
		}

		const int nCount = nCode;
		int nStart = 0;
		int nEnd = nCount;
		if (bClip && (nClipLeft || nClipRight))
		{
			nStart = nClipLeft - nCurrentX;
			if (nStart < 0)
			{
				nStart = 0;
			}

			nEnd = nClipRight - nCurrentX;
			if (nEnd > nCount)
			{
				nEnd = nCount;
			}
		}

		for (int i = nStart; i < nEnd; ++i)
		{
			pDest[i] = tOp(pSrc[i], pDest[i]);
		}

		nCurrentX += nCount;
		pSrc += nCount;
		pDest += nCount;
	}
}

//D2CMP.0x6FDF6080
static void __fastcall FASTCMP_DrawCopyClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_CopyOp{});
}

//D2CMP.0x6FDF6130
static void __fastcall FASTCMP_DrawPaletteBlend(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pPalette, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_PaletteBlendOp{ pPalette, pBlendTable });
}

//D2CMP.0x6FDF6390
static void __fastcall FASTCMP_DrawPaletteBlendClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pPalette, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteBlendOp{ pPalette, pBlendTable });
}

//D2CMP.0x6FDF6690
static void __fastcall FASTCMP_DrawPaletteShift(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pPalette, const uint8_t* pPalShift)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_PaletteShiftOp{ pPalette, pPalShift });
}

//D2CMP.0x6FDF6830
static void __fastcall FASTCMP_DrawPaletteShiftClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pPalette, const uint8_t* pPalShift)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteShiftOp{ pPalette, pPalShift });
}

//D2CMP.0x6FDF6A60
static void __fastcall FASTCMP_DrawPalette(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pPalette)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_PaletteOp{ pPalette });
}

//D2CMP.0x6FDF6BA0
static void __fastcall FASTCMP_DrawPaletteClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pPalette)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteOp{ pPalette });
}

//D2CMP.0x6FDF6D70
static void __fastcall FASTCMP_DrawShiftBlend(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pPalShift, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_ShiftBlendOp{ pPalShift, pBlendTable });
}

//D2CMP.0x6FDF6FD0
static void __fastcall FASTCMP_DrawShiftBlendClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pPalShift, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_ShiftBlendOp{ pPalShift, pBlendTable });
}

//D2CMP.0x6FDF72D0
static void __fastcall FASTCMP_DrawShift(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pPalShift)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_ShiftOp{ pPalShift });
}

//D2CMP.0x6FDF7410
static void __fastcall FASTCMP_DrawShiftClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pPalShift)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_ShiftOp{ pPalShift });
}

//D2CMP.0x6FDF75E0
static void __fastcall FASTCMP_DrawBlend(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<false>(pSrc, pDest, nLines, nStride, 0, 0, 0, FASTCMP_BlendOp{ pBlendTable });
}

//D2CMP.0x6FDF77E0
static void __fastcall FASTCMP_DrawBlendClipped(const uint8_t* pSrc, uint8_t* pDest, int nLines, int nStride, int nX, int nClipLeft, int nClipRight, const uint8_t* pBlendTable)
{
	FASTCMP_DrawLines<true>(pSrc, pDest, nLines, nStride, nX, nClipLeft, nClipRight, FASTCMP_BlendOp{ pBlendTable });
}

//D2CMP.0x6FDF7A80 (#10049)
void __stdcall D2CMP_ToggleCelDrawMode()
{
	gbCelDrawMode = !gbCelDrawMode;
}

//D2CMP.0x6FDF7AA0
void __fastcall FASTCMP_DrawCel(D2GfxCellStrc* pCel, uint8_t* pDest, int nX, int nClipLeft, int nClipRight, int nStride, int nLinesToSkip, int nLinesToDraw, const uint8_t* pPalette, const uint8_t* pBlendTable, const uint8_t* pPalShift)
{
	D2_ASSERT((uint32_t)nStride >= pCel->dwWidth); // dwStride >= pCel->dwWidth
	D2_ASSERT(nLinesToSkip + nLinesToDraw <= (int)pCel->dwHeight);

	const uint8_t* pSrc = pCel->pPixels;
	for (int nLine = nLinesToSkip; nLine; )
	{
		const int8_t nCode = (int8_t)*pSrc++;
		if (nCode >= 0)
		{
			pSrc += nCode;
		}
		else if (!(nCode & 0x7F))
		{
			--nLine;
		}
	}

	if (!(pCel->dwFlags & GFXCELL_FLAG_TOPDOWN))
	{
		nStride = -nStride;
	}

	if (gbCelDrawMode)
	{
		if (pPalette)
		{
			if (pBlendTable)
			{
				FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteBlendOp{ pPalette, pBlendTable });
			}
			else if (pPalShift)
			{
				FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteShiftOp{ pPalette, pPalShift });
			}
			else
			{
				FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_PaletteOp{ pPalette });
			}
		}
		else if (pPalShift)
		{
			if (pBlendTable)
			{
				FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_ShiftBlendOp{ pPalShift, pBlendTable });
			}
			else
			{
				FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_ShiftOp{ pPalShift });
			}
		}
		else if (pBlendTable)
		{
			FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_BlendOp{ pBlendTable });
		}
		else
		{
			FASTCMP_DrawLines<true>(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, FASTCMP_CopyOp{});
		}
		return;
	}

	// When clipping is not needed, use the faster functions
	const bool bNoClip = (!nClipLeft && !nClipRight) || (nX >= nClipLeft && nX + (int)pCel->dwWidth < nClipRight);

	if (pPalette)
	{
		if (pBlendTable)
		{
			if (bNoClip)
			{
				FASTCMP_DrawPaletteBlend(pSrc, pDest, nLinesToDraw, nStride, pPalette, pBlendTable);
			}
			else
			{
				FASTCMP_DrawPaletteBlendClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pPalette, pBlendTable);
			}
		}
		else if (pPalShift)
		{
			if (bNoClip)
			{
				FASTCMP_DrawPaletteShift(pSrc, pDest, nLinesToDraw, nStride, pPalette, pPalShift);
			}
			else
			{
				FASTCMP_DrawPaletteShiftClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pPalette, pPalShift);
			}
		}
		else
		{
			if (bNoClip)
			{
				FASTCMP_DrawPalette(pSrc, pDest, nLinesToDraw, nStride, pPalette);
			}
			else
			{
				FASTCMP_DrawPaletteClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pPalette);
			}
		}
	}
	else if (pPalShift)
	{
		if (pBlendTable)
		{
			if (bNoClip)
			{
				FASTCMP_DrawShiftBlend(pSrc, pDest, nLinesToDraw, nStride, pPalShift, pBlendTable);
			}
			else
			{
				FASTCMP_DrawShiftBlendClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pPalShift, pBlendTable);
			}
		}
		else
		{
			if (bNoClip)
			{
				FASTCMP_DrawShift(pSrc, pDest, nLinesToDraw, nStride, pPalShift);
			}
			else
			{
				FASTCMP_DrawShiftClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pPalShift);
			}
		}
	}
	else if (pBlendTable)
	{
		if (bNoClip)
		{
			FASTCMP_DrawBlend(pSrc, pDest, nLinesToDraw, nStride, pBlendTable);
		}
		else
		{
			FASTCMP_DrawBlendClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight, pBlendTable);
		}
	}
	else
	{
		if (bNoClip)
		{
			FASTCMP_DrawLines<false>(pSrc, pDest, nLinesToDraw, nStride, 0, 0, 0, FASTCMP_CopyOp{});
		}
		else
		{
			FASTCMP_DrawCopyClipped(pSrc, pDest, nLinesToDraw, nStride, nX, nClipLeft, nClipRight);
		}
	}
}

//D2CMP.0x6FDF7FB0 (#10048)
void __stdcall D2CMP_CmpDoLensEffect(uint8_t* pDest, int nStride)
{
	constexpr int nLensSize = 80;
	constexpr int nLensHalfSize = nLensSize / 2;

	// Top half
	uint8_t* pRow = pDest;
	for (int nY = 0; nY < nLensHalfSize; ++nY)
	{
		const int nStart = gaLensEffectStart[nY];
		const int nEnd = gaLensEffectEnd[nY];

		const int nLeftEnd = nEnd < nLensHalfSize + 1 ? nEnd : nLensHalfSize + 1;
		for (int nX = nStart; nX < nLeftEnd; ++nX)
		{
			pRow[nX] = pRow[nX + gaLensEffectOffsets[nY][nX]];
		}

		const int nRightEnd = nStart >= nLensHalfSize ? nStart : nLensHalfSize;
		for (int nX = nEnd; nX > nRightEnd; --nX)
		{
			pRow[nX] = pRow[nX + gaLensEffectOffsets[nY][nX]];
		}

		pRow += nStride;
	}

	// Bottom half, drawn from the bottom
	pRow = pDest + (nLensSize - 1) * nStride;
	for (int nY = nLensSize - 1; nY >= nLensHalfSize; --nY)
	{
		const int nStart = gaLensEffectStart[nY];
		const int nEnd = gaLensEffectEnd[nY];

		const int nLeftEnd = nEnd < nLensHalfSize + 1 ? nEnd : nLensHalfSize + 1;
		for (int nX = nStart; nX < nLeftEnd; ++nX)
		{
			pRow[nX] = pRow[nX + gaLensEffectOffsets[nY][nX]];
		}

		const int nRightEnd = nStart >= nLensHalfSize ? nStart : nLensHalfSize;
		for (int nX = nEnd; nX > nRightEnd; --nX)
		{
			pRow[nX] = pRow[nX + gaLensEffectOffsets[nY][nX]];
		}

		pRow -= nStride;
	}
}

//D2CMP.0x6FDF8100
void __fastcall FASTCMP_DrawCelShadow(D2GfxCellStrc* pCel, uint8_t* pDest, int nX, int nClipLeft, int nClipRight, int nStride, int nLinesToSkip, int nLinesToDraw, const uint8_t* pBlendTable, uint8_t nShadowColor)
{
	D2_ASSERT((uint32_t)nStride >= pCel->dwWidth); // dwStride >= pCel->dwWidth

	// Shadows only use one line out of two
	const uint8_t* pSrc = pCel->pPixels;
	for (int nLine = 2 * nLinesToSkip; nLine; )
	{
		const int8_t nCode = (int8_t)*pSrc++;
		if (nCode >= 0)
		{
			pSrc += nCode;
		}
		else if (!(nCode & 0x7F))
		{
			--nLine;
		}
	}

	nStride = -nStride;
	uint8_t* pNextRow = pDest + nStride;
	int nLineX = nX;
	int nCurrentX = nX;
	while (true)
	{
		const int8_t nCode = (int8_t)*pSrc++;
		if (nCode < 0)
		{
			const int nSkip = nCode & 0x7F;
			if (nSkip)
			{
				nCurrentX += nSkip;
				pDest += nSkip;
				continue;
			}

			// The shadow is skewed by one pixel to the left each line
			pDest = pNextRow - 1;
			pNextRow = pNextRow + nStride - 1;
			--nLineX;
			nCurrentX = nLineX;
			--nLinesToDraw;
			if (!nLinesToDraw)
			{
				return;
			}

			// Skip the next line
			while (true)
			{
				const int8_t nSkippedCode = (int8_t)*pSrc++;
				if (nSkippedCode > 0)
				{
					pSrc += nSkippedCode;
				}
				else if (!(nSkippedCode & 0x7F))
				{
					break;
				}
			}
			continue;
		}

		const int nCount = nCode;
		uint8_t* pNextDest = pDest + nCount;
		int nDrawCount = nCount;
		if (nClipLeft || nClipRight)
		{
			int nStart = nClipLeft - nCurrentX;
			if (nStart <= 0)
			{
				nStart = 0;
			}

			int nEnd = nClipRight - nCurrentX;
			if (nEnd <= 0)
			{
				nEnd = 0;
			}

			if (nEnd > nCount)
			{
				nEnd = nCount;
			}

			nDrawCount = nEnd - nStart;
			if (nDrawCount <= 0)
			{
				nDrawCount = 0;
			}
			else
			{
				pDest += nStart;
			}
		}

		if (nDrawCount)
		{
			if (pBlendTable)
			{
				for (int i = 0; i < nDrawCount; ++i)
				{
					pDest[i] = pBlendTable[(pDest[i] << 8) + nShadowColor];
				}
			}
			else
			{
				memset(pDest, nShadowColor, nDrawCount);
			}
		}

		nCurrentX += nCount;
		pDest = pNextDest;
		pSrc += nCount;
	}
}

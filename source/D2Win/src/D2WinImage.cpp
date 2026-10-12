#include "D2WinImage.h"

#include <algorithm>

#include <D2Math.h>

#include <D2CMP.h>

#include <D2Gfx.h>
#include <Texture.h>

#include <Fog.h>
#include <D2BitManip.h>

#include "D2WinMain.h"


#pragma pack(push, 1)
struct D2CropRectStrc
{
	int32_t unk0x00;
	int32_t unk0x04;
	int32_t unk0x08;
	int32_t unk0x0C;
};
#pragma pack(pop)


//D2Win.0x6F8ABA90 (#10084)
D2WinImage2Strc* __fastcall IMAGE2_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, D2CellFileStrc* pCellFile, int32_t(__stdcall* pfOnClick)(SMSGHANDLER_PARAMS*), D2WinImageClickRectStrc* pClickRect, int32_t(__stdcall* pfHandleVirtualKeyInput)(SMSGHANDLER_PARAMS*))
{
	D2WinImage2Strc* pImage = D2_CALLOC_STRC(D2WinImage2Strc);

	pImage->controlHeader.nType = D2WIN_IMAGE;
	pImage->controlHeader.dwFlags |= gdwBitMasks[0] | gdwBitMasks[2];
	pImage->controlHeader.pCellFile = pCellFile;
	pImage->controlHeader.nImageX = nX;
	pImage->controlHeader.nImageY = nY;
	pImage->controlHeader.nWidth = nWidth;
	pImage->controlHeader.nHeight = nHeight;
	pImage->controlHeader.pfDraw = IMAGE2_Draw;
	pImage->controlHeader.pfHandleMouseDown = IMAGE2_HandleMouseDown;
	pImage->controlHeader.pfHandleVirtualKeyInput = pfHandleVirtualKeyInput;
	pImage->controlHeader.pfCallback = pfOnClick;
	pImage->eDrawMode = DRAWMODE_NORMAL;
	pImage->pClickRect = pClickRect;

	CONTROL_AppendToList(&pImage->controlHeader);

	return pImage;
}

//D2Win.0x6F8B1BF0 (#10085)
int32_t __fastcall IMAGE_Destroy(D2WinControlStrc* pControl)
{
	return CONTROL_RemoveFromList(pControl);
}

//D2Win.0x6F8ABB40
D2WinImageStrc* __fastcall IMAGE_Create(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight, D2CellFileStrc* pCellFile, int32_t nBorderWidth, int32_t nBorderHeight)
{
	D2WinImageStrc* pImage = D2_CALLOC_STRC(D2WinImageStrc);

	pImage->controlHeader.nType = D2WIN_IMAGE;
	pImage->controlHeader.dwFlags |= gdwBitMasks[0] | gdwBitMasks[2];
	pImage->controlHeader.pCellFile = pCellFile;
	pImage->controlHeader.nImageX = nX;
	pImage->controlHeader.nImageY = nY;
	pImage->controlHeader.nWidth = nWidth;
	pImage->controlHeader.nHeight = nHeight;
	pImage->controlHeader.pfDraw = IMAGE_Draw;
	pImage->controlHeader.pfHandleMouseDown = IMAGE2_HandleMouseDown;
	pImage->eDrawMode = DRAWMODE_NORMAL;
	pImage->nBorderWidth = nBorderWidth;
	pImage->nBorderHeight = nBorderHeight;

	CONTROL_AppendToList(&pImage->controlHeader);

	return pImage;
}

//D2Win.0x6F8ABC00 (#10086)
int32_t __stdcall IMAGE_SetCellFile(D2WinImageStrc* pImage, D2CellFileStrc* pCellFile, D2WinImageClickRectStrc* pClickRect)
{
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	pImage->controlHeader.pCellFile = pCellFile;
	pImage->pClickRect = pClickRect;
	return 1;
}

//D2Win.0x6F8ABC40 (#10087)
int32_t __stdcall IMAGE_SetCoordinates(D2WinImageStrc* pImage, int32_t nX, int32_t nY)
{
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	pImage->controlHeader.nImageX = nX;
	pImage->controlHeader.nImageY = nY;
	return 1;
}

//D2Win.0x6F8ABC80 (#10088)
int32_t __stdcall IMAGE_SetFrame(D2WinImageStrc* pImage, int32_t nFrame)
{
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	const int32_t nMaxFrames = D2CMP_CelFileGetCelsPerDirection(pImage->controlHeader.pCellFile) - 1;
	pImage->nFrame = D2Clamp(nFrame, 0, nMaxFrames);
	return 1;
}

//D2Win.0x6F8ABCD0 (#10089)
int32_t __stdcall IMAGE_ForceNormalDrawMode(D2WinImageStrc* pImage, int32_t nUnused)
{
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	pImage->eDrawMode = DRAWMODE_NORMAL;
	return 1;
}

//D2Win.0x6F8ABD10 (#10090)
int32_t __stdcall IMAGE_GetFrameCount(D2WinImageStrc* pImage)
{
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	return D2CMP_CelFileGetCelsPerDirection(pImage->controlHeader.pCellFile);
}

//D2Win.0x6F8ABD50
int32_t __fastcall IMAGE2_Draw(D2WinControlStrc* pControl)
{
	D2WinImageStrc* pImage = (D2WinImageStrc*)pControl;

	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	if (!(pImage->controlHeader.dwFlags & gdwBitMasks[2]) || !(pImage->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	if (!pImage->controlHeader.pCellFile)
	{
		return 1;
	}

	const int32_t nBaseY = pImage->controlHeader.nImageY - pImage->controlHeader.nHeight + 1;
	const int32_t nColumns = (pImage->controlHeader.nWidth + 255) >> 8;
	const int32_t nRows = ((pImage->controlHeader.nHeight + 255) >> 8) - 1;

	D2GfxDataStrc gfxData = {};

	gfxData.pCellFile = pImage->controlHeader.pCellFile;
	gfxData.nDirection = 0;
	gfxData.nFrame = pImage->nFrame;

	for (int32_t i = 0; i < nRows; ++i)
	{
		for (int32_t j = 0; j < nColumns; ++j)
		{
			TEXTURE_CelDraw(&gfxData, pImage->controlHeader.nImageX + 256 * j, nBaseY + 256 * (i + 1), -1, pImage->eDrawMode, 0);
			++gfxData.nFrame;
		}
	}

	if (nRows >= 0)
	{
		for (int32_t i = 0; i < nColumns; ++i)
		{
			TEXTURE_CelDraw(&gfxData, pImage->controlHeader.nImageX + 256 * i, pImage->controlHeader.nImageY, -1, pImage->eDrawMode, 0);
			++gfxData.nFrame;
		}
	}

	return 1;
}

//D2Win.0x6F8ABEA0
int32_t __fastcall IMAGE_Draw(D2WinControlStrc* pControl)
{
	D2WinImageStrc* pImage = (D2WinImageStrc*)pControl;

	// Draws the 256x256 cell as a 9-slice: the corners keep their size, the edges and the center are tiled
	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	D2GfxDataStrc gfxData = {};
	gfxData.pCellFile = pImage->controlHeader.pCellFile;
	gfxData.nDirection = 0;
	gfxData.nFrame = 0;

	const int32_t nDestY[4] =
	{ 
		pImage->controlHeader.nImageY - pImage->controlHeader.nHeight,
		pImage->controlHeader.nImageY - pImage->controlHeader.nHeight + pImage->nBorderHeight,
		pImage->controlHeader.nImageY - pImage->nBorderHeight,
		pImage->controlHeader.nImageY
	};

	const int32_t nDestX[4] =
	{
		pImage->controlHeader.nImageX,
		pImage->controlHeader.nImageX + pImage->nBorderWidth,
		pImage->controlHeader.nImageX + pImage->controlHeader.nWidth - pImage->nBorderWidth,
		pImage->controlHeader.nImageX + pImage->controlHeader.nWidth
	};

	const int32_t nSrcX[4] =
	{
		0,
		pImage->nBorderWidth,
		256 - pImage->nBorderWidth,
		256
	};

	const int32_t nSrcY[4] =
	{
		0,
		pImage->nBorderHeight,
		256 - pImage->nBorderHeight,
		256
	};

	D2CropRectStrc destRect = {};
	D2CropRectStrc clipRect = {};

	for (int32_t nRow = 0; nRow < 3; ++nRow)
	{
		const int32_t nDestBottom = nDestY[nRow + 1];
		const int32_t nDestTop = nDestY[nRow];
		const int32_t nSrcTop = nSrcY[nRow];
		const int32_t nSrcBottom = nSrcY[nRow + 1];
		const int32_t nSrcHeight = nSrcBottom - nSrcTop;

		for (int32_t nColumn = 0; nColumn < 3; ++nColumn)
		{
			int32_t nClipLeft = nDestX[nColumn];
			int32_t nClipTop = nDestTop;
			const int32_t nSrcLeft = nSrcX[nColumn];
			const int32_t nSrcWidth = nSrcX[nColumn + 1] - nSrcLeft;
			destRect.unk0x04 = nDestX[nColumn + 1];
			const int32_t nDestWidth = destRect.unk0x04 - nClipLeft;
			const int32_t nDestHeight = nDestBottom - nDestTop;
			destRect.unk0x00 = nClipLeft;
			destRect.unk0x08 = nDestTop;
			destRect.unk0x0C = nDestBottom;

			if (nSrcWidth == nDestWidth && nSrcHeight == nDestHeight)
			{
				TEXTURE_CelDrawClipped(&gfxData, nClipLeft - nSrcLeft, nDestBottom - nSrcBottom + 256, &destRect, DRAWMODE_NORMAL);
			}
			else
			{
				const int32_t nTilesX = (nDestWidth + nSrcWidth - 1) / nSrcWidth;
				int32_t nTileY = nDestTop - nSrcTop + 256;
				const int32_t nTilesY = (nDestHeight + nSrcHeight - 1) / nSrcHeight;
				int32_t nTileTop = nSrcTop + nTileY - 256;
				for (int32_t nTileRow = 0; nTileRow < nTilesY; ++nTileRow)
				{
					int32_t nTileX = nClipLeft - nSrcLeft;
					int32_t nTileLeft = nClipLeft;
					for (int32_t nTileColumn = 0; nTileColumn < nTilesX; ++nTileColumn)
					{
						if (nClipLeft <= nTileLeft)
						{
							nClipLeft = nTileLeft;
						}

						clipRect.unk0x00 = nClipLeft;
						clipRect.unk0x04 = std::min(destRect.unk0x04, nClipLeft + nSrcWidth);
						clipRect.unk0x08 = std::max(nClipTop, nTileTop);
						clipRect.unk0x0C = std::min(destRect.unk0x0C, nSrcHeight + clipRect.unk0x08);

						TEXTURE_CelDrawClipped(&gfxData, nTileX, nTileY, &clipRect, DRAWMODE_NORMAL);

						nClipTop = destRect.unk0x08;
						nTileX += nSrcWidth;
						nTileLeft += nSrcWidth;
						nClipLeft = destRect.unk0x00;
					}

					nTileY += nSrcHeight;
					nTileTop += nSrcHeight;
				}
			}
		}
	}

	return 1;
}

//D2Win.0x6F8AC170
int32_t __stdcall IMAGE2_HandleMouseDown(SMSGHANDLER_PARAMS* pMsg)
{
	const D2WinImage2Strc* pImage = (const D2WinImage2Strc*)pMsg->hWindow;

	D2_ASSERT(pImage->controlHeader.nType == D2WIN_IMAGE);

	if (!(pImage->controlHeader.dwFlags & gdwBitMasks[2]) || !(pImage->controlHeader.dwFlags & gdwBitMasks[0]))
	{
		return 0;
	}

	const int32_t nX = gMousePosition_6F8FE234.x - pImage->controlHeader.nImageX;
	const int32_t nY = gMousePosition_6F8FE234.y + pImage->controlHeader.nHeight - pImage->controlHeader.nImageY;

	const D2WinImageClickRectStrc* pClickRect = pImage->pClickRect;
	while (pClickRect && pClickRect->pCallback)
	{
		if (nX >= pClickRect->nX && nY >= pClickRect->nY - pClickRect->nHeight && nX < pClickRect->nX + pClickRect->nWidth && nY < pClickRect->nY)
		{
			return pClickRect->pCallback(pMsg);
		}

		++pClickRect;
	}

	if (pImage->controlHeader.pfCallback)
	{
		return pImage->controlHeader.pfCallback(pMsg);
	}

	return 0;
}

#pragma once


#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

#include <D2CMP.h>
#include <D2Gfx.h>
#include <D2Lang.h>
#include <D2Sound.h>
#include <D2Unicode.h>
#include <Storm.h>
#include <Texture.h>
#include <Window.h>

#include <D2WinControlHeader.h>
#include <D2WinEditBox.h>
#include <D2WinFont.h>
#include <D2WinMain.h>
#include <D2WinPalette.h>

#include <Fixtures/D2Lang/D2LangStringTblFixture.h>
#include <IatHook.h>


// Globals of the D2MOO implementation that are not declared in the D2Win headers
extern D2WinControlStrc* gpControlList_6F8FE24C;
extern D2WinControlStrc* dword_6F8FE250;
extern D2WinEditBoxStrc* gpEditBox_6F8FE258;
extern D2WinEditBoxStrc* dword_6F8FE25C;
extern void* dword_6F8FE260;
extern D2WinControlStrc* dword_6F8FE264;
extern int32_t dword_6F8FE278;
extern D2FontCacheStrc stru_6F8FD8C0[14];
extern D2CellFileStrc* ghCellfileFontMonsterIndicators_6F8FD9EC;
extern Unicode gszFramedText_Buffer_6F8FD9F0[1024];
extern Font gnFontSize_6F8BDB24;
extern int dword_6F8BDB28;
extern int dword_6F8BDB2C;
extern int dword_6F8BDB30;
extern Unicode gMonsterIndicatorCodeUnicodeChar_6F8FE204[2];
extern Unicode gColorCodeUnicodeChar_6F8FE208[2];
extern D2CharStrc* (__fastcall* dword_6F8FE20C)(Unicode);
extern DWORD gdwLastShiftedTickCount_6F8FE214;
extern BYTE byte_6F8FE218;
extern bool byte_6F8FE21A;
extern PALETTEENTRY gRGBAPalette_6F9622C0[256];


// Image base of the original D2Win.dll. The addresses in the comments of the D2Win sources are relative to it.
constexpr uintptr_t D2WIN_IMAGE_BASE = 0x6F8A0000;

inline HMODULE get_original_d2win()
{
	static const HMODULE original_d2win = LoadLibraryA((std::filesystem::current_path() / "D2Win.dll").string().c_str());
	if (original_d2win == nullptr)
	{
		throw std::runtime_error("Cannot load original D2Win.dll");
	}

	return original_d2win;
}

// Returns the global of the original D2Win.dll at the given address (e.g. 0x6F8FE24C)
template<typename T>
T& original_d2win_global(uintptr_t nAddress)
{
	return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(get_original_d2win()) + nAddress - D2WIN_IMAGE_BASE);
}

// Returns the function of the original D2Win.dll at the given address (e.g. 0x6F8AA100)
template<typename Function>
Function* original_d2win_function(uintptr_t nAddress)
{
	return reinterpret_cast<Function*>(reinterpret_cast<uintptr_t>(get_original_d2win()) + nAddress - D2WIN_IMAGE_BASE);
}


// Records the calls the D2Win functions make to other .dlls (drawing, sounds, message handlers, ...) and to the callbacks given by the tests.
// Tests run the D2MOO implementation, take the recorded calls, run the original implementation and compare both recordings.
// Pointers are described by the name given to them with name_pointer(), so that the objects of both implementations can be compared.
struct D2WinCallLog
{
	static inline std::vector<std::string> calls;
	static inline std::map<const void*, std::string> pointer_names;

	static void clear()
	{
		calls.clear();
	}

	static void record(const std::string& call)
	{
		calls.push_back(call);
	}

	// Returns all calls recorded since the last call to take() or clear(), one per line
	static std::string take()
	{
		std::string result;
		for (const auto& call : calls)
		{
			result += call;
			result += '\n';
		}

		calls.clear();
		return result;
	}

	static void name_pointer(const void* pointer, const std::string& name)
	{
		pointer_names[pointer] = name;
	}

	static std::string describe(const void* pointer)
	{
		if (pointer == nullptr)
		{
			return "nullptr";
		}

		const auto it = pointer_names.find(pointer);
		if (it != pointer_names.end())
		{
			return it->second;
		}

		return "<unnamed pointer>";
	}

	static std::string describe(const Unicode* wszText)
	{
		if (wszText == nullptr)
		{
			return "nullptr";
		}

		std::string result = "\"";
		for (const Unicode* pChar = wszText; pChar->ch; ++pChar)
		{
			if (pChar->ch >= 0x20 && pChar->ch < 0x7F)
			{
				result += static_cast<char>(pChar->ch);
			}
			else
			{
				char szBuffer[16] = {};
				std::snprintf(szBuffer, sizeof(szBuffer), "\\x%04X", pChar->ch);
				result += szBuffer;
			}
		}

		return result + "\"";
	}

	static std::string describe(const SMSGHANDLER_PARAMS* pMsg)
	{
		if (pMsg == nullptr)
		{
			return "nullptr";
		}

		std::stringstream stream;
		stream << "{ hWindow=" << describe(static_cast<const void*>(pMsg->hWindow))
			<< ", nMessage=" << pMsg->nMessage
			<< ", wParam=" << pMsg->wParam
			<< ", lParam=" << pMsg->lParam
			<< ", bUseResult=" << pMsg->bUseResult
			<< ", lResult=" << pMsg->lResult
			<< " }";
		return stream.str();
	}

	static std::string describe(const D2GfxDataStrc* pData)
	{
		if (pData == nullptr)
		{
			return "nullptr";
		}

		std::stringstream stream;
		stream << "{ pCellFile=" << describe(static_cast<const void*>(pData->pCellFile))
			<< ", nFrame=" << pData->nFrame
			<< ", nDirection=" << pData->nDirection
			<< ", nMaxDirections=" << pData->nMaxDirections
			<< ", fFlags=" << pData->fFlags
			<< ", nComponent=" << static_cast<int>(pData->nComponent)
			<< ", nUnitType=" << pData->nUnitType
			<< ", nUnitIndex=" << pData->nUnitIndex
			<< ", nMode=" << pData->nMode
			<< ", dwName=\"";
		for (const uint32_t dwToken : pData->dwName)
		{
			for (int i = 0; i < 4; ++i)
			{
				const char c = static_cast<char>(dwToken >> (8 * i));
				stream << (c >= 0x20 && c < 0x7F ? c : '?');
			}
		}

		stream << "\" }";
		return stream.str();
	}

	// Palettes are owned by the respective implementation, so their content is compared instead of their address
	static std::string describe_palette(const void* pPalette, size_t nSize)
	{
		if (pPalette == nullptr)
		{
			return "nullptr";
		}

		uint32_t nHash = 2166136261u;
		for (size_t i = 0; i < nSize; ++i)
		{
			nHash ^= static_cast<const uint8_t*>(pPalette)[i];
			nHash *= 16777619u;
		}

		char szBuffer[32] = {};
		std::snprintf(szBuffer, sizeof(szBuffer), "palette#%08X", nHash);
		return szBuffer;
	}
};


// Stands in for a .dc6 cell file. Its address can be given to the D2Win functions as D2CellFileStrc*,
// the mocked D2CMP functions read the frame count and the frame dimensions from it.
struct D2WinFakeCel
{
	int32_t nWidth;
	int32_t nHeight;
	int32_t nOffsetX;
	int32_t nOffsetY;
};

struct D2WinFakeCellFile
{
	static inline std::map<const void*, const D2WinFakeCellFile*> files;
	static inline std::map<const void*, const D2WinFakeCel*> cels;

	std::string name;
	std::vector<D2WinFakeCel> frames;

	D2WinFakeCellFile(const std::string& szName, int32_t nFrames, int32_t nWidth = 256, int32_t nHeight = 256)
		: name(szName)
	{
		// Every frame has slightly different dimensions, so that using the wrong frame changes the results
		for (int32_t i = 0; i < nFrames; ++i)
		{
			frames.push_back({ nWidth + i, nHeight - i, i, -i });
		}

		register_pointers();
	}

	D2WinFakeCellFile(const D2WinFakeCellFile&) = delete;
	D2WinFakeCellFile& operator=(const D2WinFakeCellFile&) = delete;

	~D2WinFakeCellFile()
	{
		files.erase(this);
		D2WinCallLog::pointer_names.erase(this);
		for (const auto& frame : frames)
		{
			cels.erase(&frame);
			D2WinCallLog::pointer_names.erase(&frame);
		}
	}

	D2CellFileStrc* get()
	{
		return reinterpret_cast<D2CellFileStrc*>(this);
	}

	// Must be called again after modifying frames
	void register_pointers()
	{
		files[this] = this;
		D2WinCallLog::name_pointer(this, name);

		for (size_t i = 0; i < frames.size(); ++i)
		{
			cels[&frames[i]] = &frames[i];
			D2WinCallLog::name_pointer(&frames[i], name + "[" + std::to_string(i) + "]");
		}
	}

	static const D2WinFakeCellFile* find_file(const void* pointer)
	{
		const auto it = files.find(pointer);
		return it != files.end() ? it->second : nullptr;
	}

	static const D2WinFakeCel* find_cel(const void* pointer)
	{
		const auto it = cels.find(pointer);
		return it != cels.end() ? it->second : nullptr;
	}
};


// Replacements for the functions of other .dlls called by D2Win.
// Functions with side effects (drawing, sounds, registration of message handlers, ...) are recorded in D2WinCallLog,
// queries (dimensions of a frame, size of the window, ...) only return a value.
struct D2WinMock
{
	// Values returned by the mocked functions, reset by D2WinMockFixture
	static inline int32_t nScreenWidth = 800;
	static inline int32_t nScreenHeight = 600;
	static inline int32_t nWindowState = 0;
	static inline int32_t bFullScreen = 0;
	static inline int32_t bCutScene = 0;
	static inline int32_t bHardwareAccelerated = 0;
	static inline DisplayType eDisplayType = DISPLAYTYPE_GDI;
	static inline int32_t bStartDrawResult = 1;
	static inline BOOL bLoadCellResult = 1;
	static inline BOOL bDispatchMessageResult = 0;
	static inline int32_t nSound10066Result = 0;
	static inline int32_t nSound10069Result = 0;
	static inline HWND hWindow = reinterpret_cast<HWND>(static_cast<uintptr_t>(0xD2D2D2D2));

	static void reset()
	{
		nScreenWidth = 800;
		nScreenHeight = 600;
		nWindowState = 0;
		bFullScreen = 0;
		bCutScene = 0;
		bHardwareAccelerated = 0;
		eDisplayType = DISPLAYTYPE_GDI;
		bStartDrawResult = 1;
		bLoadCellResult = 1;
		bDispatchMessageResult = 0;
		nSound10066Result = 0;
		nSound10069Result = 0;
		D2WinCallLog::name_pointer(hWindow, "hWindow");
	}

	template<typename... Args>
	static void record(const char* szFunction, const Args&... args)
	{
		std::stringstream stream;
		stream << szFunction << "(";
		const char* szSeparator = "";
		((stream << szSeparator << args, szSeparator = ", "), ...);
		stream << ")";
		D2WinCallLog::record(stream.str());
	}

	// D2Gfx

	static void __stdcall TEXTURE_CelDraw(D2GfxDataStrc* pData, int32_t nXPos, int32_t nYPos, uint32_t dwGamma, DrawMode eDrawMode, uint8_t* pPalette)
	{
		record("TEXTURE_CelDraw", D2WinCallLog::describe(pData), nXPos, nYPos, dwGamma, eDrawMode, D2WinCallLog::describe_palette(pPalette, 256));
	}

	static void __stdcall TEXTURE_CelDrawColor(D2GfxDataStrc* pData, int32_t nXPos, int32_t nYPos, uint32_t dwGamma, DrawMode eDrawMode, int32_t nGlobalPaletteShift)
	{
		record("TEXTURE_CelDrawColor", D2WinCallLog::describe(pData), nXPos, nYPos, dwGamma, eDrawMode, nGlobalPaletteShift);
	}

	static void __stdcall TEXTURE_CelDrawEx(D2GfxDataStrc* pData, int32_t nXPos, int32_t nYPos, int32_t nSkipLines, int32_t nDrawLines, DrawMode eDrawMode)
	{
		record("TEXTURE_CelDrawEx", D2WinCallLog::describe(pData), nXPos, nYPos, nSkipLines, nDrawLines, eDrawMode);
	}

	static void __stdcall TEXTURE_CelDrawClipped(D2GfxDataStrc* pData, int32_t nXPos, int32_t nYPos, void* pCropRect, DrawMode eDrawMode)
	{
		const int32_t* pRect = static_cast<const int32_t*>(pCropRect);
		std::stringstream rect;
		if (pRect)
		{
			rect << "{ " << pRect[0] << ", " << pRect[1] << ", " << pRect[2] << ", " << pRect[3] << " }";
		}
		else
		{
			rect << "nullptr";
		}

		record("TEXTURE_CelDrawClipped", D2WinCallLog::describe(pData), nXPos, nYPos, rect.str(), eDrawMode);
	}

	static void __stdcall TEXTURE_CelDrawShadow(D2GfxDataStrc* pData, int32_t nXPos, int32_t nYPos)
	{
		record("TEXTURE_CelDrawShadow", D2WinCallLog::describe(pData), nXPos, nYPos);
	}

	static void __stdcall D2GFX_DrawBox(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, DrawMode eDrawMode)
	{
		record("D2GFX_DrawBox", nXStart, nYStart, nXEnd, nYEnd, dwColor, eDrawMode);
	}

	static void __stdcall D2GFX_DrawBoxAlpha(int32_t nXStart, int32_t nYStart, int32_t nXEnd, int32_t nYEnd, uint32_t dwColor, uint8_t nAlpha)
	{
		record("D2GFX_DrawBoxAlpha", nXStart, nYStart, nXEnd, nYEnd, dwColor, static_cast<int>(nAlpha));
	}

	static void __stdcall D2GFX_UtilRect(RECT* pRect, uint8_t nPaletteIndex)
	{
		record("D2GFX_UtilRect", pRect->left, pRect->top, pRect->right, pRect->bottom, static_cast<int>(nPaletteIndex));
	}

	static void __stdcall D2GFX_SetPalette(PALETTEENTRY* pPalette)
	{
		record("D2GFX_SetPalette", D2WinCallLog::describe_palette(pPalette, 256 * sizeof(PALETTEENTRY)));
	}

	static void __stdcall D2GFX_SetPaletteTables(D2PaletteTableStrc* pPaletteTables)
	{
		record("D2GFX_SetPaletteTables");
	}

	static DisplayType __stdcall D2GFX_GetDisplayType()
	{
		return eDisplayType;
	}

	static int32_t __stdcall D2GFX_HardwareAcceleratedRenderMode()
	{
		return bHardwareAccelerated;
	}

	static int32_t __stdcall D2GFX_StartDraw(int32_t bClear, uint8_t nRed, uint8_t nGreen, uint8_t nBlue)
	{
		record("D2GFX_StartDraw", bClear, static_cast<int>(nRed), static_cast<int>(nGreen), static_cast<int>(nBlue));
		return bStartDrawResult;
	}

	static int32_t __stdcall D2GFX_EndScene()
	{
		record("D2GFX_EndScene");
		return 1;
	}

	static void __stdcall D2GFX_ClearScreen(int32_t bPartial)
	{
		record("D2GFX_ClearScreen", bPartial);
	}

	static int32_t __stdcall D2GFX_Initialize(HINSTANCE hInstance, WNDPROC pfWndProc, DisplayType nDisplayType, int32_t bWindowed)
	{
		record("D2GFX_Initialize", D2WinCallLog::describe(hInstance), nDisplayType, bWindowed);
		return 1;
	}

	static int32_t __stdcall WINDOW_Create(int32_t bWindowed, D2GameResolutionMode nResolution)
	{
		record("WINDOW_Create", bWindowed, nResolution);
		return 1;
	}

	static int32_t __stdcall WINDOW_Destroy()
	{
		record("WINDOW_Destroy");
		return 1;
	}

	static void __stdcall WINDOW_SetPaused(int32_t bPaused)
	{
		record("WINDOW_SetPaused", bPaused);
	}

	static int32_t __stdcall WINDOW_GetState()
	{
		return nWindowState;
	}

	static HWND __stdcall WINDOW_GetWindow()
	{
		return hWindow;
	}

	static int32_t __stdcall WINDOW_GetDimensions(int32_t* pWidth, int32_t* pHeight)
	{
		*pWidth = nScreenWidth;
		*pHeight = nScreenHeight;
		return 1;
	}

	static int32_t __stdcall WINDOW_IsFullScreen()
	{
		return bFullScreen;
	}

	static int32_t __stdcall WINDOW_Resize(D2GameResolutionMode nResolution, int32_t bForceResize)
	{
		record("WINDOW_Resize", nResolution, bForceResize);
		return 1;
	}

	static void __stdcall WINDOW_ClearCaches()
	{
		record("WINDOW_ClearCaches");
	}

	static void __stdcall WINDOW_PlayCutscene()
	{
		record("WINDOW_PlayCutscene");
	}

	static void __stdcall WINDOW_EndCutScene(D2GameResolutionMode nResolution)
	{
		record("WINDOW_EndCutScene", nResolution);
	}

	static int32_t __stdcall WINDOW_CheckCutScene()
	{
		return bCutScene;
	}

	static void __stdcall WINDOW_DecodeSmacker(const char* szSmacker, uint8_t* pBuffer, int32_t nVersion)
	{
		record("WINDOW_DecodeSmacker", szSmacker ? szSmacker : "nullptr", D2WinCallLog::describe(pBuffer), nVersion);
	}

	static void __stdcall WINDOW_PlaySmacker(void* pContext)
	{
		record("WINDOW_PlaySmacker", D2WinCallLog::describe(pContext));
	}

	static void __stdcall WINDOW_CloseSmacker(void* pContext)
	{
		record("WINDOW_CloseSmacker", D2WinCallLog::describe(pContext));
	}

	// D2CMP

	static D2CellFileStrc* __stdcall D2CMP_CelGetHandle(D2GfxDataStrc* pData)
	{
		const D2WinFakeCellFile* pFile = D2WinFakeCellFile::find_file(pData->pCellFile);
		if (pFile == nullptr || pFile->frames.empty())
		{
			return nullptr;
		}

		return reinterpret_cast<D2CellFileStrc*>(const_cast<D2WinFakeCel*>(&pFile->frames[pData->nFrame % pFile->frames.size()]));
	}

	static int __stdcall D2CMP_CelGetWidth(D2CellFileStrc* pCel)
	{
		const D2WinFakeCel* pFakeCel = D2WinFakeCellFile::find_cel(pCel);
		return pFakeCel ? pFakeCel->nWidth : 0;
	}

	static int __stdcall D2CMP_CelGetHeight(D2CellFileStrc* pCel)
	{
		const D2WinFakeCel* pFakeCel = D2WinFakeCellFile::find_cel(pCel);
		return pFakeCel ? pFakeCel->nHeight : 0;
	}

	static int __stdcall D2CMP_CelGetOffsetX(D2CellFileStrc* pCel)
	{
		const D2WinFakeCel* pFakeCel = D2WinFakeCellFile::find_cel(pCel);
		return pFakeCel ? pFakeCel->nOffsetX : 0;
	}

	static int __stdcall D2CMP_CelGetOffsetY(D2CellFileStrc* pCel)
	{
		const D2WinFakeCel* pFakeCel = D2WinFakeCellFile::find_cel(pCel);
		return pFakeCel ? pFakeCel->nOffsetY : 0;
	}

	static int __stdcall D2CMP_CelFileGetCelsPerDirection(D2CellFileStrc* pCelFile)
	{
		const D2WinFakeCellFile* pFile = D2WinFakeCellFile::find_file(pCelFile);
		return pFile ? static_cast<int>(pFile->frames.size()) : 0;
	}

	// Actually computes the nearest color, so that the result depends on the palette given by the respective implementation
	static int __stdcall D2CMP_GetNearestPaletteIndex(PALETTEENTRY* pPalette, int nPaletteSize, int nRed, int nGreen, int nBlue)
	{
		int nNearestIndex = 0;
		int nNearestDistance = INT_MAX;
		for (int i = 0; i < nPaletteSize; ++i)
		{
			const int nDeltaRed = pPalette[i].peRed - nRed;
			const int nDeltaGreen = pPalette[i].peGreen - nGreen;
			const int nDeltaBlue = pPalette[i].peBlue - nBlue;
			const int nDistance = nDeltaRed * nDeltaRed + nDeltaGreen * nDeltaGreen + nDeltaBlue * nDeltaBlue;
			if (nDistance < nNearestDistance)
			{
				nNearestIndex = i;
				nNearestDistance = nDistance;
			}
		}

		return nNearestIndex;
	}

	static BOOL __stdcall D2CMP_CelFileFreeHardware(D2CellFileStrc* pFile)
	{
		record("D2CMP_CelFileFreeHardware", D2WinCallLog::describe(pFile));
		return 1;
	}

	static void __stdcall D2CMP_InitSpriteCache(void* pMemPool, int dwSpriteCacheSize, int dwSize, unsigned int dwMemoryOverride)
	{
		record("D2CMP_InitSpriteCache", D2WinCallLog::describe(pMemPool), dwSpriteCacheSize, dwSize, dwMemoryOverride);
	}

	static void __stdcall D2CMP_FlushSpriteCache(BOOL bRealloc)
	{
		record("D2CMP_FlushSpriteCache", bRealloc);
	}

	static void __stdcall D2CMP_SetCompressedDataMode(BOOL bAllowCompressedMode)
	{
		record("D2CMP_SetCompressedDataMode", bAllowCompressedMode);
	}

	static BOOL __stdcall D2CMP_10055(D2GfxDataStrc* pData, int32_t a2, BOOL a3)
	{
		record("D2CMP_10055", D2WinCallLog::describe(pData), a2, a3);
		// The loaded cell is only checked for null by D2Win
		if (bLoadCellResult)
		{
			pData->pCurrentCell = reinterpret_cast<D2GfxCellStrc*>(pData);
		}

		return bLoadCellResult;
	}

	// D2Sound

	static void __fastcall D2SOUND_10034(int nValue)
	{
		record("D2SOUND_10034", nValue);
	}

	static void __fastcall D2SOUND_10039(const char* szFile)
	{
		record("D2SOUND_10039", szFile ? szFile : "nullptr");
	}

	static void* __fastcall D2SOUND_10048()
	{
		record("D2SOUND_10048");
		return reinterpret_cast<void*>(static_cast<uintptr_t>(0x50D50D));
	}

	static void __fastcall D2SOUND_10049(void* pValue)
	{
		record("D2SOUND_10049", reinterpret_cast<uintptr_t>(pValue));
	}

	static void __fastcall D2SOUND_10065()
	{
		record("D2SOUND_10065");
	}

	static int __fastcall D2SOUND_10066()
	{
		return nSound10066Result;
	}

	static int __fastcall D2SOUND_10069()
	{
		return nSound10069Result;
	}

	static void __fastcall D2SOUND_10070(int nValue)
	{
		record("D2SOUND_10070", nValue);
	}

	// Storm

	static BOOL __stdcall SMsgDispatchMessage(HWND hWnd, DWORD messageID, WPARAM wParam, LPARAM lParam, BOOL* bUseResult, LRESULT* pResult)
	{
		record("SMsgDispatchMessage", D2WinCallLog::describe(hWnd), messageID, wParam, lParam);
		if (bDispatchMessageResult)
		{
			*bUseResult = 1;
			*pResult = 0x1234;
		}

		return bDispatchMessageResult;
	}

	static BOOL __stdcall SMsgBreakHandlerChain(SMSGHANDLER_PARAMS* pData)
	{
		record("SMsgBreakHandlerChain", D2WinCallLog::describe(pData));
		return 1;
	}

	static BOOL __stdcall SMsgRegisterCommand(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgRegisterCommand", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgRegisterKeyDown(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgRegisterKeyDown", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgRegisterKeyUp(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgRegisterKeyUp", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgRegisterMessage(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgRegisterMessage", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgUnregisterCommand(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgUnregisterCommand", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgUnregisterKeyDown(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgUnregisterKeyDown", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgUnregisterKeyUp(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgUnregisterKeyUp", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}

	static BOOL __stdcall SMsgUnregisterMessage(HWND hWnd, uint32_t nId, SMSGHANDLER pHandler)
	{
		record("SMsgUnregisterMessage", D2WinCallLog::describe(hWnd), nId, D2WinCallLog::describe(reinterpret_cast<const void*>(pHandler)));
		return 1;
	}
};


// Callbacks given to the D2Win functions by the tests. Every call is recorded in D2WinCallLog.
struct D2WinCallbacks
{
	static inline int32_t nReturnValue = 1;
	static inline BOOL bCharFilterResult = 1;
	static inline char nCharFilterReplacement = 0;

	static void reset()
	{
		nReturnValue = 1;
		bCharFilterResult = 1;
		nCharFilterReplacement = 0;

		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&Callback), "D2WinCallbacks::Callback");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&Callback2), "D2WinCallbacks::Callback2");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&VoidCallback), "D2WinCallbacks::VoidCallback");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&OnReturn), "D2WinCallbacks::OnReturn");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&CharFilter), "D2WinCallbacks::CharFilter");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&OnTextChanged), "D2WinCallbacks::OnTextChanged");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&PopUpLineCallback), "D2WinCallbacks::PopUpLineCallback");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&OnQuit), "D2WinCallbacks::OnQuit");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&LoopCallback), "D2WinCallbacks::LoopCallback");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&WndProc), "D2WinCallbacks::WndProc");
		D2WinCallLog::name_pointer(reinterpret_cast<const void*>(&ShowMessage), "D2WinCallbacks::ShowMessage");
	}

	static int32_t __stdcall Callback(SMSGHANDLER_PARAMS* pMsg)
	{
		D2WinMock::record("Callback", D2WinCallLog::describe(pMsg));
		return nReturnValue;
	}

	static int32_t __stdcall Callback2(SMSGHANDLER_PARAMS* pMsg)
	{
		D2WinMock::record("Callback2", D2WinCallLog::describe(pMsg));
		return nReturnValue;
	}

	static void __stdcall VoidCallback(SMSGHANDLER_PARAMS* pMsg)
	{
		D2WinMock::record("VoidCallback", D2WinCallLog::describe(pMsg));
	}

	static void __stdcall OnReturn(const Unicode* wszText)
	{
		D2WinMock::record("OnReturn", D2WinCallLog::describe(wszText));
	}

	static BOOL __stdcall CharFilter(D2WinEditBoxStrc* pEditBox, int32_t nPosition, char* pChar)
	{
		D2WinMock::record("CharFilter", D2WinCallLog::describe(pEditBox), nPosition, static_cast<int>(*pChar));
		if (nCharFilterReplacement)
		{
			*pChar = nCharFilterReplacement;
		}

		return bCharFilterResult;
	}

	static void __stdcall OnTextChanged(int32_t nValue)
	{
		D2WinMock::record("OnTextChanged", nValue);
	}

	static void __stdcall PopUpLineCallback()
	{
		D2WinMock::record("PopUpLineCallback");
	}

	static int OnQuit()
	{
		D2WinMock::record("OnQuit");
		return 0;
	}

	static void __stdcall LoopCallback(DWORD dwCounter)
	{
		D2WinMock::record("LoopCallback", dwCounter);
	}

	static LRESULT __stdcall WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		D2WinMock::record("WndProc", D2WinCallLog::describe(hWnd), Msg, wParam, lParam);
		return 0x4321;
	}

	static BOOL __stdcall ShowMessage()
	{
		D2WinMock::record("ShowMessage");
		return 0;
	}
};


// Redirects the calls of both the D2MOO implementation (linked into the test executable)
// and the original D2Win.dll to D2WinMock, D2LangStringTblMock for the string table.
template<class Fixture>
struct D2WinMockFixture : Fixture
{
	std::vector<IatHook> d2win_hooks;

	D2WinMockFixture()
	{
		D2WinCallLog::clear();
		D2WinMock::reset();
		D2WinCallbacks::reset();
		D2LangStringTblMock::calls.clear();
		D2LangStringTblMock::tbl_index_calls.clear();

		const HMODULE modules[] = { GetModuleHandleA(nullptr), get_original_d2win() };
		d2win_hooks.reserve(2 * 80);

		const auto hook = [this, &modules](auto* target, auto* replacement)
		{
			static_assert(std::is_same_v<decltype(target), decltype(replacement)>, "The mock must have the signature of the mocked function");

			for (const auto module : modules)
			{
				d2win_hooks.emplace_back(module, reinterpret_cast<const void*>(target), reinterpret_cast<const void*>(replacement));
			}
		};

		hook(&::TEXTURE_CelDraw, &D2WinMock::TEXTURE_CelDraw);
		hook(&::TEXTURE_CelDrawColor, &D2WinMock::TEXTURE_CelDrawColor);
		hook(&::TEXTURE_CelDrawEx, &D2WinMock::TEXTURE_CelDrawEx);
		hook(&::TEXTURE_CelDrawClipped, &D2WinMock::TEXTURE_CelDrawClipped);
		hook(&::TEXTURE_CelDrawShadow, &D2WinMock::TEXTURE_CelDrawShadow);
		hook(&::D2GFX_DrawBox, &D2WinMock::D2GFX_DrawBox);
		hook(&::D2GFX_DrawBoxAlpha, &D2WinMock::D2GFX_DrawBoxAlpha);
		hook(&::D2GFX_UtilRect, &D2WinMock::D2GFX_UtilRect);
		hook(&::D2GFX_SetPalette, &D2WinMock::D2GFX_SetPalette);
		hook(&::D2GFX_SetPaletteTables, &D2WinMock::D2GFX_SetPaletteTables);
		hook(&::D2GFX_GetDisplayType, &D2WinMock::D2GFX_GetDisplayType);
		hook(&::D2GFX_HardwareAcceleratedRenderMode, &D2WinMock::D2GFX_HardwareAcceleratedRenderMode);
		hook(&::D2GFX_StartDraw, &D2WinMock::D2GFX_StartDraw);
		hook(&::D2GFX_EndScene, &D2WinMock::D2GFX_EndScene);
		hook(&::D2GFX_ClearScreen, &D2WinMock::D2GFX_ClearScreen);
		hook(&::D2GFX_Initialize, &D2WinMock::D2GFX_Initialize);
		hook(&::WINDOW_Create, &D2WinMock::WINDOW_Create);
		hook(&::WINDOW_Destroy, &D2WinMock::WINDOW_Destroy);
		hook(&::WINDOW_SetPaused, &D2WinMock::WINDOW_SetPaused);
		hook(&::WINDOW_GetState, &D2WinMock::WINDOW_GetState);
		hook(&::WINDOW_GetWindow, &D2WinMock::WINDOW_GetWindow);
		hook(&::WINDOW_GetDimensions, &D2WinMock::WINDOW_GetDimensions);
		hook(&::WINDOW_IsFullScreen, &D2WinMock::WINDOW_IsFullScreen);
		hook(&::WINDOW_Resize, &D2WinMock::WINDOW_Resize);
		hook(&::WINDOW_ClearCaches, &D2WinMock::WINDOW_ClearCaches);
		hook(&::WINDOW_PlayCutscene, &D2WinMock::WINDOW_PlayCutscene);
		hook(&::WINDOW_EndCutScene, &D2WinMock::WINDOW_EndCutScene);
		hook(&::WINDOW_CheckCutScene, &D2WinMock::WINDOW_CheckCutScene);
		hook(&::WINDOW_DecodeSmacker, &D2WinMock::WINDOW_DecodeSmacker);
		hook(&::WINDOW_PlaySmacker, &D2WinMock::WINDOW_PlaySmacker);
		hook(&::WINDOW_CloseSmacker, &D2WinMock::WINDOW_CloseSmacker);

		hook(&::D2CMP_CelGetHandle, &D2WinMock::D2CMP_CelGetHandle);
		hook(&::D2CMP_CelGetWidth, &D2WinMock::D2CMP_CelGetWidth);
		hook(&::D2CMP_CelGetHeight, &D2WinMock::D2CMP_CelGetHeight);
		hook(&::D2CMP_CelGetOffsetX, &D2WinMock::D2CMP_CelGetOffsetX);
		hook(&::D2CMP_CelGetOffsetY, &D2WinMock::D2CMP_CelGetOffsetY);
		hook(&::D2CMP_CelFileGetCelsPerDirection, &D2WinMock::D2CMP_CelFileGetCelsPerDirection);
		hook(&::D2CMP_GetNearestPaletteIndex, &D2WinMock::D2CMP_GetNearestPaletteIndex);
		hook(&::D2CMP_CelFileFreeHardware, &D2WinMock::D2CMP_CelFileFreeHardware);
		hook(&::D2CMP_InitSpriteCache, &D2WinMock::D2CMP_InitSpriteCache);
		hook(&::D2CMP_FlushSpriteCache, &D2WinMock::D2CMP_FlushSpriteCache);
		hook(&::D2CMP_SetCompressedDataMode, &D2WinMock::D2CMP_SetCompressedDataMode);
		hook(&::D2CMP_10055, &D2WinMock::D2CMP_10055);

		hook(&::D2SOUND_10034, &D2WinMock::D2SOUND_10034);
		hook(&::D2SOUND_10039, &D2WinMock::D2SOUND_10039);
		hook(&::D2SOUND_10048, &D2WinMock::D2SOUND_10048);
		hook(&::D2SOUND_10049, &D2WinMock::D2SOUND_10049);
		hook(&::D2SOUND_10065, &D2WinMock::D2SOUND_10065);
		hook(&::D2SOUND_10066, &D2WinMock::D2SOUND_10066);
		hook(&::D2SOUND_10069, &D2WinMock::D2SOUND_10069);
		hook(&::D2SOUND_10070, &D2WinMock::D2SOUND_10070);

		hook(&::SMsgDispatchMessage, &D2WinMock::SMsgDispatchMessage);
		hook(&::SMsgBreakHandlerChain, &D2WinMock::SMsgBreakHandlerChain);
		hook(&::SMsgRegisterCommand, &D2WinMock::SMsgRegisterCommand);
		hook(&::SMsgRegisterKeyDown, &D2WinMock::SMsgRegisterKeyDown);
		hook(&::SMsgRegisterKeyUp, &D2WinMock::SMsgRegisterKeyUp);
		hook(&::SMsgRegisterMessage, &D2WinMock::SMsgRegisterMessage);
		hook(&::SMsgUnregisterCommand, &D2WinMock::SMsgUnregisterCommand);
		hook(&::SMsgUnregisterKeyDown, &D2WinMock::SMsgUnregisterKeyDown);
		hook(&::SMsgUnregisterKeyUp, &D2WinMock::SMsgUnregisterKeyUp);
		hook(&::SMsgUnregisterMessage, &D2WinMock::SMsgUnregisterMessage);

		hook(&::D2LANG_GetStringFromTblIndex, &D2LangStringTblMock::GetStringFromTblIndex);
	}

	~D2WinMockFixture()
	{
		d2win_hooks.clear();
		D2WinCallLog::clear();

		// The names of the cell files of the base fixtures are removed when they are destroyed
		for (auto it = D2WinCallLog::pointer_names.begin(); it != D2WinCallLog::pointer_names.end();)
		{
			if (D2WinFakeCellFile::find_file(it->first) || D2WinFakeCellFile::find_cel(it->first))
			{
				++it;
			}
			else
			{
				it = D2WinCallLog::pointer_names.erase(it);
			}
		}
	}
};


// Global state of both implementations related to the controls.
// The globals are reset when the fixture is created and restored when it is destroyed.
// The tests must destroy the controls they create, they are not freed by the fixture.
struct D2WinControlState
{
	D2WinControlStrc*& pControlList;
	D2WinControlStrc*& pRemovedControlList;
	int32_t& nRemovedControlsLocked;
	D2WinEditBoxStrc*& pFocusedEditBox;
	D2WinEditBoxStrc*& pActiveEditBox;
	void*& pCancelButton;
	D2WinControlStrc*& pModalControlList;
	int32_t& bDimBackground;
	POINT& mousePosition;

	static D2WinControlState moo()
	{
		return { gpControlList_6F8FE24C, dword_6F8FE250, dword_6F8FE254, gpEditBox_6F8FE258, dword_6F8FE25C, dword_6F8FE260, dword_6F8FE264, dword_6F8FE278, gMousePosition_6F8FE234 };
	}

	static D2WinControlState original()
	{
		return {
			original_d2win_global<D2WinControlStrc*>(0x6F8FE24C),
			original_d2win_global<D2WinControlStrc*>(0x6F8FE250),
			original_d2win_global<int32_t>(0x6F8FE254),
			original_d2win_global<D2WinEditBoxStrc*>(0x6F8FE258),
			original_d2win_global<D2WinEditBoxStrc*>(0x6F8FE25C),
			original_d2win_global<void*>(0x6F8FE260),
			original_d2win_global<D2WinControlStrc*>(0x6F8FE264),
			original_d2win_global<int32_t>(0x6F8FE278),
			original_d2win_global<POINT>(0x6F8FE234),
		};
	}

	struct Values
	{
		D2WinControlStrc* pControlList;
		D2WinControlStrc* pRemovedControlList;
		int32_t nRemovedControlsLocked;
		D2WinEditBoxStrc* pFocusedEditBox;
		D2WinEditBoxStrc* pActiveEditBox;
		void* pCancelButton;
		D2WinControlStrc* pModalControlList;
		int32_t bDimBackground;
		POINT mousePosition;
	};

	Values save() const
	{
		return { pControlList, pRemovedControlList, nRemovedControlsLocked, pFocusedEditBox, pActiveEditBox, pCancelButton, pModalControlList, bDimBackground, mousePosition };
	}

	void restore(const Values& values)
	{
		pControlList = values.pControlList;
		pRemovedControlList = values.pRemovedControlList;
		nRemovedControlsLocked = values.nRemovedControlsLocked;
		pFocusedEditBox = values.pFocusedEditBox;
		pActiveEditBox = values.pActiveEditBox;
		pCancelButton = values.pCancelButton;
		pModalControlList = values.pModalControlList;
		bDimBackground = values.bDimBackground;
		mousePosition = values.mousePosition;
	}

	void set_mouse_position(int32_t nX, int32_t nY)
	{
		mousePosition.x = nX;
		mousePosition.y = nY;
	}
};

template<class Fixture>
struct D2WinControlStateFixture : Fixture
{
	D2WinControlState moo_state = D2WinControlState::moo();
	D2WinControlState original_state = D2WinControlState::original();
	D2WinControlState::Values saved_moo_state = moo_state.save();
	D2WinControlState::Values saved_original_state = original_state.save();

	D2WinControlStateFixture()
	{
		moo_state.restore({});
		original_state.restore({});
	}

	~D2WinControlStateFixture()
	{
		moo_state.restore(saved_moo_state);
		original_state.restore(saved_original_state);
	}

	void set_mouse_position(int32_t nX, int32_t nY)
	{
		moo_state.set_mouse_position(nX, nY);
		original_state.set_mouse_position(nX, nY);
	}
};


// Font state of both implementations. Every font uses the same fake font table and cell file,
// so that the text functions can be used without loading the fonts from the archives.
struct D2WinFontState
{
	D2FontCacheStrc* pFontCaches;
	D2CellFileStrc*& pMonsterIndicatorsCellFile;
	Unicode* wszFramedText;
	Font& eFontSize;
	int& nLineSpacing;
	int& nTextHeightScale;
	int& nTextBaselineScale;
	Unicode* wszMonsterIndicatorCode;
	Unicode* wszColorCode;
	D2CharStrc* (__fastcall*& pfGetCharInfo)(Unicode);
	DWORD& dwLastShiftedTickCount;
	BYTE& nFramedTextProgressColor;
	bool& bKoreanEnglish;
	D2CharStrc* (__fastcall* pfGetCharInfoDirect)(Unicode);
	Font(__fastcall* pfSetFont)(Font);

	static D2WinFontState moo()
	{
		return {
			stru_6F8FD8C0,
			ghCellfileFontMonsterIndicators_6F8FD9EC,
			gszFramedText_Buffer_6F8FD9F0,
			gnFontSize_6F8BDB24,
			dword_6F8BDB28,
			dword_6F8BDB2C,
			dword_6F8BDB30,
			gMonsterIndicatorCodeUnicodeChar_6F8FE204,
			gColorCodeUnicodeChar_6F8FE208,
			dword_6F8FE20C,
			gdwLastShiftedTickCount_6F8FE214,
			byte_6F8FE218,
			byte_6F8FE21A,
			&FONT_GetCharInfoDirect,
			&D2Win_10127_SetFont,
		};
	}

	static D2WinFontState original()
	{
		return {
			&original_d2win_global<D2FontCacheStrc>(0x6F8FD8C0),
			original_d2win_global<D2CellFileStrc*>(0x6F8FD9EC),
			&original_d2win_global<Unicode>(0x6F8FD9F0),
			original_d2win_global<Font>(0x6F8BDB24),
			original_d2win_global<int>(0x6F8BDB28),
			original_d2win_global<int>(0x6F8BDB2C),
			original_d2win_global<int>(0x6F8BDB30),
			&original_d2win_global<Unicode>(0x6F8FE204),
			&original_d2win_global<Unicode>(0x6F8FE208),
			original_d2win_global<D2CharStrc* (__fastcall*)(Unicode)>(0x6F8FE20C),
			original_d2win_global<DWORD>(0x6F8FE214),
			original_d2win_global<BYTE>(0x6F8FE218),
			original_d2win_global<bool>(0x6F8FE21A),
			original_d2win_function<D2CharStrc* __fastcall(Unicode)>(0x6F8AA100),
			original_d2win_function<Font __fastcall(Font)>(0x6F8A9FF0),
		};
	}

	void setup(D2CellFileStrc* pFontCellFile, D2FontStrc* pFont, D2CellFileStrc* pMonsterIndicators, Font eFont)
	{
		const DWORD dwShiftedTickCount = GetTickCount() >> 10;

		for (int i = 0; i < NUM_FONTS; ++i)
		{
			pFontCaches[i].pCellFile = pFontCellFile;
			pFontCaches[i].pFontInfo[0] = pFont;
			pFontCaches[i].pFontInfo[1] = pFont;
			pFontCaches[i].pCharInfo = pFont->pChars;
			pFontCaches[i].dwShiftedTickCount = dwShiftedTickCount;
		}

		pMonsterIndicatorsCellFile = pMonsterIndicators;
		std::memset(wszFramedText, 0, 1024 * sizeof(Unicode));
		nLineSpacing = 16;
		nTextHeightScale = 16;
		nTextBaselineScale = 3;
		wszMonsterIndicatorCode[0] = L'm';
		wszMonsterIndicatorCode[1] = 0;
		wszColorCode[0] = L'c';
		wszColorCode[1] = 0;
		pfGetCharInfo = pfGetCharInfoDirect;
		dwLastShiftedTickCount = dwShiftedTickCount;
		nFramedTextProgressColor = 0;
		bKoreanEnglish = false;

		// Switching the font updates the current font cache of the implementation, which can't be accessed directly in the original .dll
		eFontSize = eFont == D2FONT_FONT8 ? D2FONT_FONT16 : D2FONT_FONT8;
		pfSetFont(eFont);
	}

	void clear()
	{
		std::memset(pFontCaches, 0, NUM_FONTS * sizeof(D2FontCacheStrc));
		pMonsterIndicatorsCellFile = nullptr;
		std::memset(wszFramedText, 0, 1024 * sizeof(Unicode));
		pfGetCharInfo = nullptr;
		eFontSize = D2FONT_FONT8;
		nFramedTextProgressColor = 0;
	}
};

template<class Fixture>
struct D2WinFontFixture : Fixture
{
	D2WinFakeCellFile font_cell_file{ "font", 256, 8, 12 };
	D2WinFakeCellFile monster_indicators_cell_file{ "monster_indicators", 8 };
	D2FontStrc font{};
	D2WinFontState moo_font_state = D2WinFontState::moo();
	D2WinFontState original_font_state = D2WinFontState::original();

	D2WinFontFixture()
	{
		font.dwHeader = 'Woo!';
		font.wNumChars = 256;
		font.nHeight = 12;
		font.nWidth = 10;

		// Characters of various widths, sorted by character code
		for (int i = 0; i < 256; ++i)
		{
			font.pChars[i].wChar = static_cast<WORD>(i);
			font.pChars[i].nWidth = static_cast<BYTE>(4 + (i * 7) % 9);
			font.pChars[i].nHeight = 12;
			font.pChars[i].nImageIndex = static_cast<WORD>(i);
		}

		moo_font_state.setup(font_cell_file.get(), &font, monster_indicators_cell_file.get(), D2FONT_FONT16);
		original_font_state.setup(font_cell_file.get(), &font, monster_indicators_cell_file.get(), D2FONT_FONT16);
	}

	~D2WinFontFixture()
	{
		moo_font_state.clear();
		original_font_state.clear();
	}
};


// The screen palette of both implementations, used to compute palette indices of colors
template<class Fixture>
struct D2WinPaletteFixture : Fixture
{
	PALETTEENTRY* moo_palette = gRGBAPalette_6F9622C0;
	PALETTEENTRY* original_palette = &original_d2win_global<PALETTEENTRY>(0x6F9622C0);
	PALETTEENTRY saved_moo_palette[256] = {};
	PALETTEENTRY saved_original_palette[256] = {};

	D2WinPaletteFixture()
	{
		std::memcpy(saved_moo_palette, moo_palette, sizeof(saved_moo_palette));
		std::memcpy(saved_original_palette, original_palette, sizeof(saved_original_palette));

		for (int i = 0; i < 256; ++i)
		{
			const PALETTEENTRY entry = { static_cast<BYTE>(i), static_cast<BYTE>((i * 37) & 0xFF), static_cast<BYTE>((i * 101) & 0xFF), 0 };
			moo_palette[i] = entry;
			original_palette[i] = entry;
		}
	}

	~D2WinPaletteFixture()
	{
		std::memcpy(moo_palette, saved_moo_palette, sizeof(saved_moo_palette));
		std::memcpy(original_palette, saved_original_palette, sizeof(saved_original_palette));
	}
};


// Everything needed by most D2Win functions: mocked dependencies, a clean control state, fonts and a palette
template<class Fixture>
using D2WinFixture = D2WinMockFixture<D2WinControlStateFixture<D2WinFontFixture<D2WinPaletteFixture<Fixture>>>>;

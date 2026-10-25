#include <D2WinTestDefines.h>

#ifdef COMP_TESTS

#include <doctest.h>

#include <Windows.h>

#include <cstdarg>
#include <cstring>
#include <cwchar>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <D2WinTestHelpers.h>
#include <TestUtilities.h>

#include <D2WinComp.h>


// Composite unit globals of the D2MOO implementation
extern D2CompositeUnitStrc* gpCompositeUnitList_6F8FD650;
extern D2CofNodeStrc* gpCofNodeList_6F8FD654;
extern DWORD gdwNextCursorFrameTick_6F8FD658;
extern D2CellFileStrc* ghSquelchCelFile_6F8FD65C;
extern int32_t gnSquelchCelFileFrameCount_6F8FD660;
extern int32_t gnSquelchCelFileFrame_6F8FD664;
extern D2CellFileStrc* ghSelectedCelFile_6F8FD668;
extern int32_t gnSelectedCelFileFrameCount_6F8FD66C;
extern int32_t gnSelectedCelFileFrame_6F8FD670;
extern uint8_t gItemPalettes_6F8C2118[9][105][256];
extern uint8_t byte_6F8FD218[10];
extern uint8_t byte_6F8FD224[10];


// NOTE: The item tables, the item palettes and the COF files are loaded from the MPQ archives.
// The tests build the COF files in memory and fill the item palettes of both implementations with the same content.
TEST_SUITE("D2WinCompTests")
{
	const auto working_directory = std::filesystem::current_path();
	const auto dll_base = reinterpret_cast<uintptr_t>(LoadLibraryA((working_directory / "D2Win.dll").string().c_str()));

	constexpr uint32_t dwHandToHandToken = ' hth';

	// Composite unit globals of both implementations
	struct CompState
	{
		D2CompositeUnitStrc*& pCompositeUnitList;
		D2CofNodeStrc*& pCofNodeList;
		DWORD& dwNextCursorFrameTick;
		D2CellFileStrc*& pSquelchCelFile;
		int32_t& nSquelchCelFileFrameCount;
		int32_t& nSquelchCelFileFrame;
		D2CellFileStrc*& pSelectedCelFile;
		int32_t& nSelectedCelFileFrameCount;
		int32_t& nSelectedCelFileFrame;
		uint8_t* pItemPalettes;
		uint8_t* pEmblemColors2;
		uint8_t* pEmblemColors1;

		void reset()
		{
			pCompositeUnitList = nullptr;
			pCofNodeList = nullptr;
			// The frames of the squelch and selection animations change every 66 ms, which the tests avoid
			dwNextCursorFrameTick = 0xFFFFFFFF;
			pSquelchCelFile = nullptr;
			nSquelchCelFileFrameCount = 0;
			nSquelchCelFileFrame = 0;
			pSelectedCelFile = nullptr;
			nSelectedCelFileFrameCount = 0;
			nSelectedCelFileFrame = 0;
		}
	};

	void check_comp_states_eq(const CompState& moo, const CompState& original)
	{
		CHECK_EQ(moo.dwNextCursorFrameTick, original.dwNextCursorFrameTick);
		CHECK_EQ(moo.pSquelchCelFile, original.pSquelchCelFile);
		CHECK_EQ(moo.nSquelchCelFileFrameCount, original.nSquelchCelFileFrameCount);
		CHECK_EQ(moo.nSquelchCelFileFrame, original.nSquelchCelFileFrame);
		CHECK_EQ(moo.pSelectedCelFile, original.pSelectedCelFile);
		CHECK_EQ(moo.nSelectedCelFileFrameCount, original.nSelectedCelFileFrameCount);
		CHECK_EQ(moo.nSelectedCelFileFrame, original.nSelectedCelFileFrame);
		CHECK_EQ(std::memcmp(moo.pEmblemColors1, original.pEmblemColors1, 10), 0);
		CHECK_EQ(std::memcmp(moo.pEmblemColors2, original.pEmblemColors2, 10), 0);
	}

	struct CompFixture : D2WinFixture<NoopFixture>
	{
		CompState moo_comp = {
			gpCompositeUnitList_6F8FD650, gpCofNodeList_6F8FD654, gdwNextCursorFrameTick_6F8FD658,
			ghSquelchCelFile_6F8FD65C, gnSquelchCelFileFrameCount_6F8FD660, gnSquelchCelFileFrame_6F8FD664,
			ghSelectedCelFile_6F8FD668, gnSelectedCelFileFrameCount_6F8FD66C, gnSelectedCelFileFrame_6F8FD670,
			&gItemPalettes_6F8C2118[0][0][0], byte_6F8FD218, byte_6F8FD224,
		};
		CompState original_comp = {
			original_d2win_global<D2CompositeUnitStrc*>(0x6F8FD650),
			original_d2win_global<D2CofNodeStrc*>(0x6F8FD654),
			original_d2win_global<DWORD>(0x6F8FD658),
			original_d2win_global<D2CellFileStrc*>(0x6F8FD65C),
			original_d2win_global<int32_t>(0x6F8FD660),
			original_d2win_global<int32_t>(0x6F8FD664),
			original_d2win_global<D2CellFileStrc*>(0x6F8FD668),
			original_d2win_global<int32_t>(0x6F8FD66C),
			original_d2win_global<int32_t>(0x6F8FD670),
			&original_d2win_global<uint8_t>(0x6F8C2118),
			&original_d2win_global<uint8_t>(0x6F8FD218),
			&original_d2win_global<uint8_t>(0x6F8FD224),
		};

		CompFixture()
		{
			moo_comp.reset();
			original_comp.reset();
		}

		// The item palettes are only read, they are filled with the same content in both implementations
		void fill_item_palettes()
		{
			for (size_t i = 0; i < sizeof(gItemPalettes_6F8C2118); ++i)
			{
				const uint8_t nValue = static_cast<uint8_t>(i * 7 + (i >> 8));
				moo_comp.pItemPalettes[i] = nValue;
				original_comp.pItemPalettes[i] = nValue;
			}
		}

		~CompFixture()
		{
			moo_comp.reset();
			original_comp.reset();
		}

		// Runs a function taking a composite unit on both implementations and compares the results
		template<typename Function, typename... Args>
		void compare_comp_function(Function* sut, Function* original, D2CompositeUnitStrc& moo_pCompositeUnit, D2CompositeUnitStrc& original_pCompositeUnit, Args... args)
		{
			D2WinCallLog::clear();
			if constexpr (std::is_void_v<decltype(sut(&moo_pCompositeUnit, args...))>)
			{
				sut(&moo_pCompositeUnit, args...);
				const auto moo_calls = D2WinCallLog::take();
				original(&original_pCompositeUnit, args...);
				const auto original_calls = D2WinCallLog::take();
				CHECK_EQ(moo_calls, original_calls);
			}
			else
			{
				const auto moo_result = sut(&moo_pCompositeUnit, args...);
				const auto moo_calls = D2WinCallLog::take();
				const auto original_result = original(&original_pCompositeUnit, args...);
				const auto original_calls = D2WinCallLog::take();
				MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
				CHECK_EQ(moo_calls, original_calls);
			}

			MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
			check_comp_states_eq(moo_comp, original_comp);
			CHECK_EQ(moo_font_state.eFontSize, original_font_state.eFontSize);
		}
	};

	// A COF file with 3 layers, 4 frames and 8 directions, built in memory
	struct FakeCof
	{
		std::vector<uint8_t> data;
		D2CofNodeStrc node{};
		D2CofInfoStrc info{};
		D2GfxInfoStrc gfxInfo{};

		FakeCof(uint32_t nMode, uint32_t dwWClassToken, uint8_t nLayers = 3, uint8_t nFrames = 4, uint8_t nDirections = 8)
		{
			data.resize(sizeof(D2CofDataStrc) + nLayers * sizeof(D2CofLayerStrc) + nFrames + nDirections * nFrames * nLayers);
			D2CofDataStrc* pCofData = reinterpret_cast<D2CofDataStrc*>(data.data());
			pCofData->nLayers = nLayers;
			pCofData->nFrames = nFrames;
			pCofData->nDirections = nDirections;
			pCofData->nVersion = 20;
			pCofData->nAnimRate = 256;

			D2CofLayerStrc* pLayers = reinterpret_cast<D2CofLayerStrc*>(pCofData + 1);
			for (int i = 0; i < nLayers; ++i)
			{
				pLayers[i].nComponent = static_cast<uint8_t>(i * 2);
				pLayers[i].nShadow = 1;
				std::memcpy(pLayers[i].szWeaponClass, i == 1 ? "1hs" : (i == 2 ? "" : "hth"), 4);
			}

			// Priorities of the layers for each direction and frame
			uint8_t* pPriorities = reinterpret_cast<uint8_t*>(pLayers + nLayers) + nFrames;
			for (int i = 0; i < nDirections * nFrames; ++i)
			{
				for (int j = 0; j < nLayers; ++j)
				{
					pPriorities[i * nLayers + j] = static_cast<uint8_t>(((i + j) % nLayers) * 2);
				}
			}

			node.nRefCount = 1;
			node.nMode = nMode;
			node.nClass = 1;
			node.dwWClassToken = dwWClassToken;
			node.nFileSize = static_cast<uint32_t>(data.size());
			node.pCofData = pCofData;
			info.pCofNode = &node;
			gfxInfo.pCofInfo = &info;
		}
	};

	// Unit using the hand to hand weapon class in mode 1 (neutral)
	void setup_unit(D2CompositeUnitStrc& pCompositeUnit, D2GfxInfoStrc* pGfxInfo)
	{
		pCompositeUnit.dwFlags = 1 | 2 | 4 | 8;
		pCompositeUnit.nDirection = 3;
		pCompositeUnit.nDirections = 8;
		pCompositeUnit.nFrame = 0x180;
		pCompositeUnit.nFrames = 4;
		pCompositeUnit.nAnimRate = 0x80;
		pCompositeUnit.nX = 300;
		pCompositeUnit.nY = 300;
		pCompositeUnit.nClass = 1;
		pCompositeUnit.nMode = 1;
		pCompositeUnit.nWClassTokenIndex = 1;
		for (int i = 0; i < 16; ++i)
		{
			// No palette, palette 8, palette 1, an unknown palette and an unloaded shift
			const uint8_t colors[] = { 0xFF, 0x05, 0x25, 0x65, 0x1F };
			pCompositeUnit.nComponentColors[i] = colors[i % 5];
			pCompositeUnit.dwComponentTokens[i] = i % 3 ? ' til' : 0;
			pCompositeUnit.nComponentItemTypes[i] = 1;
		}

		pCompositeUnit.pGfxInfo = pGfxInfo;
		std::wcscpy(reinterpret_cast<wchar_t*>(pCompositeUnit.wszAccountName), L"AccountName");
		std::wcscpy(reinterpret_cast<wchar_t*>(pCompositeUnit.wszCharName), L"CharacterName");
		std::wcscpy(reinterpret_cast<wchar_t*>(pCompositeUnit.wszRealmName), L"Realm");
		pCompositeUnit.nLevel = 50;
		pCompositeUnit.dwProductCode = 'D2XP';
	}

	// Composite unit allocated with Fog.dll, like the units created by D2Win, so that it can be freed by the tested functions
	D2CompositeUnitStrc* create_allocated_unit(D2CofNodeStrc*& pCofNodeList, int32_t nCofInfos, bool bEmblem)
	{
		D2CompositeUnitStrc* pCompositeUnit = d2win_calloc<D2CompositeUnitStrc>();
		D2GfxInfoStrc* pGfxInfo = d2win_calloc<D2GfxInfoStrc>();
		setup_unit(*pCompositeUnit, pGfxInfo);

		for (int32_t i = 0; i < nCofInfos; ++i)
		{
			// The COF nodes are shared between the units
			D2CofNodeStrc* pCofNode = d2win_calloc<D2CofNodeStrc>();
			pCofNode->nRefCount = i + 1;
			pCofNode->nMode = i;
			pCofNode->pCofData = static_cast<D2CofDataStrc*>(D2_ALLOC(sizeof(D2CofDataStrc)));
			pCofNode->pNext = pCofNodeList;
			if (pCofNodeList)
			{
				pCofNodeList->pPrev = pCofNode;
			}

			pCofNodeList = pCofNode;

			D2CofInfoStrc* pCofInfo = d2win_calloc<D2CofInfoStrc>();
			pCofInfo->pCofNode = pCofNode;
			pCofInfo->pNext = pGfxInfo->pCofInfo;
			pGfxInfo->pCofInfo = pCofInfo;
		}

		if (bEmblem)
		{
			pCompositeUnit->pEmblemCellFile = static_cast<D2CellFileStrc*>(D2_ALLOC(16));
			D2WinCallLog::name_pointer(pCompositeUnit->pEmblemCellFile, "emblem");
		}

		return pCompositeUnit;
	}


	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A15E0")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawShadow, dll_base + 0x000015E0);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 1u, 4u, 5u);
		const bool bHasCof = GENERATE(true, false);
		const BOOL bLoadCellResult = GENERATE(1, 0);
		const uint8_t nDirection = GENERATE(0, 5);
		CAPTURE(dwFlags);
		CAPTURE(bHasCof);
		CAPTURE(bLoadCellResult);
		CAPTURE(static_cast<int>(nDirection));

		D2WinMock::bLoadCellResult = bLoadCellResult;
		FakeCof moo_cof(bHasCof ? 1 : 2, dwHandToHandToken);
		FakeCof original_cof(bHasCof ? 1 : 2, dwHandToHandToken);
		D2CompositeUnitStrc moo_pCompositeUnit{};
		D2CompositeUnitStrc original_pCompositeUnit{};
		setup_unit(moo_pCompositeUnit, &moo_cof.gfxInfo);
		setup_unit(original_pCompositeUnit, &original_cof.gfxInfo);
		for (D2CompositeUnitStrc* pCompositeUnit : { &moo_pCompositeUnit, &original_pCompositeUnit })
		{
			pCompositeUnit->dwFlags = dwFlags;
			pCompositeUnit->nDirection = nDirection;
		}

		compare_comp_function(reinterpret_cast<void(__fastcall*)(D2CompositeUnitStrc*)>(sut), reinterpret_cast<void(__fastcall*)(D2CompositeUnitStrc*)>(original), moo_pCompositeUnit, original_pCompositeUnit);
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A1890")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_Draw, dll_base + 0x00001890);

		// Input data
		// Visible, selected (flag 0x400), squelched (flag 0x200), transparent (flags 0x30 or 0x2000)
		const uint32_t dwFlags = GENERATE(0u, 1u, 1u | 0x400u | 0x200u, 1u | 0x30u, 1u | 0x2000u, 1u | 0x10u);
		const bool bHasCof = GENERATE(true, false);
		const bool bEmblem = GENERATE(false, true);
		const uint8_t nDirections = GENERATE(8, 16);
		const int32_t nFrame = GENERATE(0, 0x2C0);
		const uint32_t dwGamma = GENERATE(0xFFFFFFFFu, 3u);
		CAPTURE(dwFlags);
		CAPTURE(bHasCof);
		CAPTURE(bEmblem);
		CAPTURE(static_cast<int>(nDirections));
		CAPTURE(nFrame);
		CAPTURE(dwGamma);

		fill_item_palettes();

		D2WinFakeCellFile selectedCellFile("selected", 5);
		D2WinFakeCellFile squelchCellFile("squelch", 6);
		D2WinFakeCellFile emblemCellFile("emblem", 1);
		for (CompState* pState : { &moo_comp, &original_comp })
		{
			pState->pSelectedCelFile = selectedCellFile.get();
			pState->nSelectedCelFileFrameCount = 5;
			pState->nSelectedCelFileFrame = 3;
			pState->pSquelchCelFile = squelchCellFile.get();
			pState->nSquelchCelFileFrameCount = 6;
			pState->nSquelchCelFileFrame = 2;
		}

		FakeCof moo_cof(bHasCof ? 1 : 2, dwHandToHandToken);
		FakeCof original_cof(bHasCof ? 1 : 2, dwHandToHandToken);
		D2CompositeUnitStrc moo_pCompositeUnit{};
		D2CompositeUnitStrc original_pCompositeUnit{};
		setup_unit(moo_pCompositeUnit, &moo_cof.gfxInfo);
		setup_unit(original_pCompositeUnit, &original_cof.gfxInfo);
		for (D2CompositeUnitStrc* pCompositeUnit : { &moo_pCompositeUnit, &original_pCompositeUnit })
		{
			pCompositeUnit->dwFlags = dwFlags;
			pCompositeUnit->nDirections = nDirections;
			pCompositeUnit->nFrame = nFrame;
			pCompositeUnit->pEmblemCellFile = bEmblem ? emblemCellFile.get() : nullptr;
			pCompositeUnit->nEmblemColor1 = 12;
			pCompositeUnit->nEmblemColor2 = 34;
		}

		compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, dwGamma);
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A1D10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawName, dll_base + 0x00001D10);

		// Input data
		// Name shown (flag 2), hardcore (0x20), titles (0x40 and 0x80), offset (0x100), expansion (0x1000)
		const uint32_t dwFlags = GENERATE(0u, 2u, 2u | 0x20u, 2u | 0x40u, 2u | 0x80u | 0x1000u, 2u | 0xE0u | 0x100u);
		const uint32_t nClass = GENERATE(0u, 1u, 18u, 20u);
		const uint32_t dwProductCode = GENERATE('D2XP', 'STAR');
		const wchar_t* wszCharName = GENERATE(L"Name", L"AVeryLongCharacterNameThatIsTruncated");
		const wchar_t* wszUnk0x1CC = GENERATE(L"", L"Clan");
		CAPTURE(dwFlags);
		CAPTURE(nClass);
		CAPTURE(dwProductCode);
		CAPTURE(static_cast<const void*>(wszCharName));
		CAPTURE(static_cast<const void*>(wszUnk0x1CC));

		D2GfxInfoStrc gfxInfo{};
		D2CompositeUnitStrc moo_pCompositeUnit{};
		D2CompositeUnitStrc original_pCompositeUnit{};
		for (D2CompositeUnitStrc* pCompositeUnit : { &moo_pCompositeUnit, &original_pCompositeUnit })
		{
			setup_unit(*pCompositeUnit, &gfxInfo);
			pCompositeUnit->dwFlags = dwFlags;
			pCompositeUnit->nClass = nClass;
			pCompositeUnit->dwProductCode = dwProductCode;
			std::wcscpy(reinterpret_cast<wchar_t*>(pCompositeUnit->wszCharName), wszCharName);
			std::wcscpy(reinterpret_cast<wchar_t*>(pCompositeUnit->wszUnk0x1CC), wszUnk0x1CC);
		}

		compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit);
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A2070")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_DrawHoverInfo, dll_base + 0x00002070);

		// Input data
		const uint32_t dwFlags = GENERATE(0u, 8u, 8u | 0x20u);
		const bool bHovered = GENERATE(true, false);
		const uint32_t nClass = GENERATE(1u, 18u, 19u, 20u, 21u, 22u, 23u, 24u);
		const uint32_t dwProductCode = GENERATE('D2XP', 'D2DV', 'DSHR', 'DRTL', 'SEXP', 'SSHR', 'W2BN', 'STAR', 'W3XP', 'WAR3', 'XXXX');
		const int32_t nLevel = GENERATE(0, 50);
		const int32_t nX = GENERATE(300, 10, 790);
		CAPTURE(dwFlags);
		CAPTURE(bHovered);
		CAPTURE(nClass);
		CAPTURE(dwProductCode);
		CAPTURE(nLevel);
		CAPTURE(nX);

		D2GfxInfoStrc gfxInfo{};
		D2CompositeUnitStrc moo_pCompositeUnit{};
		D2CompositeUnitStrc original_pCompositeUnit{};
		for (D2CompositeUnitStrc* pCompositeUnit : { &moo_pCompositeUnit, &original_pCompositeUnit })
		{
			setup_unit(*pCompositeUnit, &gfxInfo);
			pCompositeUnit->dwFlags = dwFlags;
			pCompositeUnit->nClass = nClass;
			pCompositeUnit->dwProductCode = dwProductCode;
			pCompositeUnit->nLevel = nLevel;
			pCompositeUnit->nX = nX;
		}

		set_mouse_position(bHovered ? nX : 0, bHovered ? 290 : 0);

		compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit);
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A2A20 (#10142)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10142_CompUnitDestroy, dll_base + 0x00002A20);

		// Input data
		const int32_t nCofInfos = GENERATE(0, 1, 3);
		const bool bEmblem = GENERATE(false, true);
		const BOOL bFree = GENERATE(0, 1);
		// Index of the unit in the list of 3 units, -1 if the unit is not in the list
		const int nIndex = GENERATE(-1, 0, 1, 2);
		const bool bHasCofNodeList = GENERATE(true, false);
		CAPTURE(nCofInfos);
		CAPTURE(bEmblem);
		CAPTURE(bFree);
		CAPTURE(nIndex);
		CAPTURE(bHasCofNodeList);

		if (nIndex < 0 && bFree)
		{
			// The unit must be in the list to be freed
			return;
		}

		D2CompositeUnitStrc* moo_pUnits[3] = {};
		D2CompositeUnitStrc* original_pUnits[3] = {};
		for (CompState* pState : { &moo_comp, &original_comp })
		{
			D2CompositeUnitStrc** pUnits = pState == &moo_comp ? moo_pUnits : original_pUnits;
			for (int i = 0; i < 3; ++i)
			{
				pUnits[i] = create_allocated_unit(pState->pCofNodeList, i == nIndex || (nIndex < 0 && i == 0) ? nCofInfos : 0, bEmblem && (i == nIndex || (nIndex < 0 && i == 0)));
				pUnits[i]->nX = i;
				if (i > 0 && nIndex >= 0)
				{
					pUnits[i - 1]->pNext = pUnits[i];
					pUnits[i]->pPrev = pUnits[i - 1];
				}
			}

			pState->pCompositeUnitList = nIndex >= 0 ? pUnits[0] : nullptr;
			if (!bHasCofNodeList)
			{
				// Without COF node list, the COF nodes are not freed
				pState->pCofNodeList = nullptr;
			}
		}

		const int nUnit = nIndex >= 0 ? nIndex : 0;
		D2CompositeUnitStrc* moo_pCompositeUnit = moo_pUnits[nUnit];
		D2CompositeUnitStrc* original_pCompositeUnit = original_pUnits[nUnit];

		// Call both implementations
		D2WinCallLog::clear();
		sut(moo_pCompositeUnit, bFree);
		const auto moo_calls = D2WinCallLog::take();
		original(original_pCompositeUnit, bFree);
		const auto original_calls = D2WinCallLog::take();

		CHECK_EQ(moo_calls, original_calls);

		// Compare potentially modified input data
		MOO_CHECK_EQ(moo_comp.pCompositeUnitList, original_comp.pCompositeUnitList, "Comparing composite unit list");
		MOO_CHECK_EQ(moo_comp.pCofNodeList, original_comp.pCofNodeList, "Comparing COF node list");
		if (!bFree)
		{
			// The graphics info has been freed
			CHECK_EQ(moo_pCompositeUnit->pGfxInfo != nullptr, original_pCompositeUnit->pGfxInfo != nullptr);
			moo_pCompositeUnit->pGfxInfo = nullptr;
			original_pCompositeUnit->pGfxInfo = nullptr;
			MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A2BD0 (#10154)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10154, dll_base + 0x00002BD0);

		SUBCASE("")
		{
			// Input data
			const wchar_t* wszAccountName = GENERATE(L"", L"NewAccount");
			const int32_t nLevel = random_unsigned_integer(1, 99);
			const uint32_t dwProductCode = GENERATE('D2DV', 'D2XP');
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, D2_USTR(wszAccountName), D2_USTR(L"NewCharacter"), D2_USTR(L"Unknown"), D2_USTR(L"NewRealm"), nLevel, dwProductCode);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A2C50 (#10143)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10143, dll_base + 0x00002C50);

		SUBCASE("")
		{
			// Input data
			const uint32_t nMode = GENERATE(0u, 1u, 2u);
			FakeCof moo_cof(1, dwHandToHandToken, 3, 12, 16);
			FakeCof original_cof(1, dwHandToHandToken, 3, 12, 16);
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &moo_cof.gfxInfo);
			setup_unit(original_pCompositeUnit, &original_cof.gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nMode);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A3360 (#10159)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10159, dll_base + 0x00003360);

		SUBCASE("")
		{
			// Input data
			D2WinFakeCellFile squelchCellFile("squelch", 6);
			D2WinFakeCellFile selectedCellFile("selected", 9);
			D2CellFileStrc* pSquelchCelFile = GENERATE(true, false) ? squelchCellFile.get() : nullptr;
			D2CellFileStrc* pSelectedCelFile = GENERATE(true, false) ? selectedCellFile.get() : nullptr;

			// Call both implementations
			sut(pSquelchCelFile, pSelectedCelFile);
			original(pSquelchCelFile, pSelectedCelFile);

			// Compare the modified globals
			check_comp_states_eq(moo_comp, original_comp);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A3390 (#10144)" * doctest::skip("Needs the item tables and COF files from the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10144, dll_base + 0x00003390);

		SUBCASE("")
		{
			uint8_t moo_pComponents[16] = {};
			uint8_t original_pComponents[16] = {};
			const uint8_t pComponentColors[16] = {};

			// Call both implementations
			const auto moo_result = sut(1, 1, moo_pComponents, pComponentColors);
			const auto original_result = original(1, 1, original_pComponents, pComponentColors);

			// Compare return values
			MOO_CHECK_EQ(moo_result, original_result, "Comparing results");
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4260 (#10145)" * doctest::skip("Needs the item tables and COF files from the MPQ archives"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10145, dll_base + 0x00004260);

		SUBCASE("")
		{
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			uint8_t moo_pComponents[16] = {};
			uint8_t original_pComponents[16] = {};
			const uint8_t pComponentColors[16] = {};

			// Call both implementations
			sut(&moo_pCompositeUnit, 1, 1, moo_pComponents, pComponentColors);
			original(&original_pCompositeUnit, 1, 1, original_pComponents, pComponentColors);

			// Compare potentially modified input data
			MOO_CHECK_EQ(moo_pCompositeUnit, original_pCompositeUnit, "Comparing pCompositeUnit");
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A43C0 (#10146)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10146, dll_base + 0x000043C0);

		SUBCASE("")
		{
			// Input data
			const int nUnits = GENERATE(0, 1, 3);
			for (CompState* pState : { &moo_comp, &original_comp })
			{
				D2CompositeUnitStrc* pPrevious = nullptr;
				for (int i = 0; i < nUnits; ++i)
				{
					D2CompositeUnitStrc* pCompositeUnit = create_allocated_unit(pState->pCofNodeList, i, i == 1);
					pCompositeUnit->pPrev = pPrevious;
					if (pPrevious)
					{
						pPrevious->pNext = pCompositeUnit;
					}
					else
					{
						pState->pCompositeUnitList = pCompositeUnit;
					}

					pPrevious = pCompositeUnit;
				}
			}

			// Call both implementations
			D2WinCallLog::clear();
			sut();
			const auto moo_calls = D2WinCallLog::take();
			original();
			const auto original_calls = D2WinCallLog::take();

			CHECK_EQ(moo_calls, original_calls);

			// Compare the modified globals
			CHECK_EQ(moo_comp.pCompositeUnitList, nullptr);
			CHECK_EQ(original_comp.pCompositeUnitList, nullptr);
			MOO_CHECK_EQ(moo_comp.pCofNodeList, original_comp.pCofNodeList, "Comparing COF node list");
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4400 (#10147)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10147, dll_base + 0x00004400);

		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc compositeUnit{};
			D2CompositeUnitStrc* pCompositeUnitList = GENERATE(true, false) ? &compositeUnit : nullptr;
			moo_comp.pCompositeUnitList = pCompositeUnitList;
			original_comp.pCompositeUnitList = pCompositeUnitList;

			// Call both implementations
			const auto moo_result = sut();
			const auto original_result = original();

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4410 (#10148)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10148, dll_base + 0x00004410);

		SUBCASE("")
		{
			// Input data
			D2CompositeUnitStrc nextUnit{};
			D2CompositeUnitStrc compositeUnit{};
			compositeUnit.pNext = GENERATE(true, false) ? &nextUnit : nullptr;

			// Call both implementations
			const auto moo_result = sut(&compositeUnit);
			const auto original_result = original(&compositeUnit);

			// Compare return values
			CHECK_EQ(moo_result, original_result);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4440 (#10149)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10149, dll_base + 0x00004440);

		SUBCASE("")
		{
			// Input data
			const uint8_t nDirection = GENERATE(0, 7, 8, 9, 255);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nDirection);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4490 (#10150)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10150, dll_base + 0x00004490);

		SUBCASE("")
		{
			// Input data
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);
			moo_pCompositeUnit.nDirections = 16;
			original_pCompositeUnit.nDirections = 16;

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A44C0 (#10169)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10169, dll_base + 0x000044C0);

		SUBCASE("")
		{
			// Input data
			const int32_t nFrames = random_unsigned_integer(0, 30);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);
			moo_pCompositeUnit.nFrames = nFrames;
			original_pCompositeUnit.nFrames = nFrames;

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A44F0 (#10151)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10151, dll_base + 0x000044F0);

		SUBCASE("")
		{
			// Input data
			const int32_t nFrame = GENERATE(-1, 0, 0x100, 0x400, 0x401, 0x10000);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nFrame);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4540 (#10152)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10152, dll_base + 0x00004540);

		SUBCASE("")
		{
			// Input data
			const int32_t nX = random_unsigned_integer(0, 800);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nX);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4570 (#10153)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10153, dll_base + 0x00004570);

		SUBCASE("")
		{
			// Input data
			const int32_t nY = random_unsigned_integer(0, 600);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nY);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A45A0 (#10155)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10155, dll_base + 0x000045A0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = random_unsigned_integer();
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);
			moo_pCompositeUnit.dwFlags = dwFlags;
			original_pCompositeUnit.dwFlags = dwFlags;

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A45D0 (#10156)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10156, dll_base + 0x000045D0);

		SUBCASE("")
		{
			// Input data
			const uint32_t dwFlags = random_unsigned_integer();
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, dwFlags);
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4600 (#10158)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10158, dll_base + 0x00004600);

		// NOTE: Valid emblems (1 to 32) are loaded from the MPQ archives, only invalid emblems are tested
		SUBCASE("")
		{
			// Input data
			const uint8_t nEmblem = GENERATE(0, 33, 255);
			const uint8_t nEmblemColor1 = GENERATE(0, 1, 10, 11);
			const uint8_t nEmblemColor2 = GENERATE(0, 5);
			D2GfxInfoStrc gfxInfo{};
			D2CompositeUnitStrc moo_pCompositeUnit{};
			D2CompositeUnitStrc original_pCompositeUnit{};
			setup_unit(moo_pCompositeUnit, &gfxInfo);
			setup_unit(original_pCompositeUnit, &gfxInfo);

			compare_comp_function(sut, original, moo_pCompositeUnit, original_pCompositeUnit, nEmblem, nEmblemColor1, nEmblemColor2);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A46E0 (#10157)" * doctest::skip("Needs MPQ archives to load the item palettes from"))
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10157, dll_base + 0x000046E0);

		SUBCASE("")
		{
			// Call both implementations
			sut();
			original();
		}
	}

	TEST_CASE_FIXTURE(CompFixture, "D2Win.0x6F8A4C10")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(COMP_InitEmblemColors, dll_base + 0x00004C10);

		SUBCASE("")
		{
			std::memset(moo_comp.pEmblemColors1, 0xEE, 10);
			std::memset(moo_comp.pEmblemColors2, 0xEE, 10);
			std::memset(original_comp.pEmblemColors1, 0xEE, 10);
			std::memset(original_comp.pEmblemColors2, 0xEE, 10);

			// Call both implementations
			sut();
			original();

			// Compare the modified globals
			check_comp_states_eq(moo_comp, original_comp);
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4C70 (#10161)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10161, dll_base + 0x00004C70);

		for (int32_t nClass = 0; nClass < 10; ++nClass)
		{
			for (const int32_t nProgression : { 0, 3, 4, 5, 8, 10, 12, 15, 20 })
			{
				for (const BOOL bHardcore : { 0, 1 })
				{
					for (const BOOL bExpansion : { 0, 1 })
					{
						CAPTURE(nClass);
						CAPTURE(nProgression);
						CAPTURE(bHardcore);
						CAPTURE(bExpansion);

						// Call both implementations
						const char* moo_result = sut(nClass, nProgression, bHardcore, bExpansion);
						const char* original_result = original(nClass, nProgression, bHardcore, bExpansion);

						// Compare return values, which point to the strings of the respective implementation
						CHECK_EQ(std::string(moo_result), std::string(original_result));
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(NoopFixture, "D2Win.0x6F8A4CE0 (#10160)")
	{
		// Set up function pointers
		const auto [sut, original] = make_function_pair(D2Win_10160_GetPlayerTitle, dll_base + 0x00004CE0);

		for (int32_t nClass = 0; nClass < 10; ++nClass)
		{
			for (int32_t nTitle = -1; nTitle < 8; ++nTitle)
			{
				for (const BOOL bExpansion : { 0, 1 })
				{
					CAPTURE(nClass);
					CAPTURE(nTitle);
					CAPTURE(bExpansion);

					// Call both implementations
					const char* moo_result = sut(nClass, nTitle, bExpansion);
					const char* original_result = original(nClass, nTitle, bExpansion);

					// Compare return values, which point to the strings of the respective implementation
					CHECK_EQ(std::string(moo_result), std::string(original_result));
				}
			}
		}
	}
}

#endif

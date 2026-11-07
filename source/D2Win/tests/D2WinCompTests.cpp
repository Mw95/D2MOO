#include <doctest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <D2WinComp.h>

#include "D2WinFontFixtures.h"
#include "D2WinTestFixtures.h"


extern D2CompItemStrc gComponentItems_6F8C1520[255];
extern uint32_t gn2HandedHitClasses_6F8FD250[255];
extern int32_t gnComponentItems_6F8FD230;
extern D2CompItemTypesTxt* gpItemTypesTxt_6F8FD244;
extern int32_t gnItemTypesTxtRecordCount_6F8FD248;
extern D2CompositeUnitStrc* gpCompositeUnitList_6F8FD650;


namespace
{
constexpr int32_t nComponentItems = 255;
constexpr int32_t nFakeItemTypes = 60;

// The item tables of one implementation
struct CompGlobals
{
	D2CompItemStrc* pComponentItems;			// 0x6F8C1520
	uint32_t* p2HandedHitClasses;				// 0x6F8FD250
	int32_t* pnComponentItems;					// 0x6F8FD230
	D2CompItemTypesTxt** ppItemTypesTxt;		// 0x6F8FD244
	int32_t* pnItemTypesTxtRecordCount;			// 0x6F8FD248
	D2CompositeUnitStrc** ppCompositeUnitList;	// 0x6F8FD650
};

const CompGlobals& comp_globals(int nImplementation)
{
	static const CompGlobals moo = {
		gComponentItems_6F8C1520, gn2HandedHitClasses_6F8FD250, &gnComponentItems_6F8FD230, &gpItemTypesTxt_6F8FD244, &gnItemTypesTxtRecordCount_6F8FD248, &gpCompositeUnitList_6F8FD650,
	};
	static const CompGlobals original = {
		original_d2win_global<D2CompItemStrc>(0x6F8C1520),
		original_d2win_global<uint32_t>(0x6F8FD250),
		original_d2win_global<int32_t>(0x6F8FD230),
		original_d2win_global<D2CompItemTypesTxt*>(0x6F8FD244),
		original_d2win_global<int32_t>(0x6F8FD248),
		original_d2win_global<D2CompositeUnitStrc*>(0x6F8FD650),
	};
	return nImplementation == 0 ? moo : original;
}

// The legacy component item table of the original dll, compiled in both implementations
const D2CompItemStrc* original_static_component_items()
{
	return original_d2win_global<D2CompItemStrc>(0x6F8BC1D8);
}

// Fake item tables installed in both implementations, the original tables are restored at the end of the test
template<class Fixture>
struct D2WinCompFixture : D2WinFixture<Fixture>
{
	D2CompItemTypesTxt itemTypes[nFakeItemTypes] = {};

	struct Saved
	{
		D2CompItemStrc componentItems[nComponentItems];
		uint32_t twoHandedHitClasses[nComponentItems];
		int32_t nComponentItems;
		D2CompItemTypesTxt* pItemTypesTxt;
		int32_t nItemTypesTxtRecordCount;
		D2CompositeUnitStrc* pCompositeUnitList;
	};
	Saved saved[2];

	D2WinCompFixture()
	{
		// Each item type is equivalent to one or two smaller types, which builds a hierarchy without loops
		for (int32_t i = 2; i < nFakeItemTypes; ++i)
		{
			itemTypes[i].nEquiv1 = (int16_t)(i / 2);
			itemTypes[i].nEquiv2 = (int16_t)(i % 3 == 0 ? i / 3 : 0);
			itemTypes[i].szCode[0] = (char)('a' + i % 26);
		}

		for (int i = 0; i < 2; ++i)
		{
			const CompGlobals& globals = comp_globals(i);
			Saved& save = saved[i];
			std::memcpy(save.componentItems, globals.pComponentItems, sizeof(save.componentItems));
			std::memcpy(save.twoHandedHitClasses, globals.p2HandedHitClasses, sizeof(save.twoHandedHitClasses));
			save.nComponentItems = *globals.pnComponentItems;
			save.pItemTypesTxt = *globals.ppItemTypesTxt;
			save.nItemTypesTxtRecordCount = *globals.pnItemTypesTxtRecordCount;
			save.pCompositeUnitList = *globals.ppCompositeUnitList;

			// Half of the items use the codes of the legacy table, so that the remapping finds them
			for (int32_t nItem = 0; nItem < nComponentItems; ++nItem)
			{
				D2CompItemStrc& item = globals.pComponentItems[nItem];
				item.dwCode = nItem % 2 == 0 ? original_static_component_items()[(nItem * 7) % 60].dwCode : 0x20202000 + nItem;
				item.nHitClass = (nItem * 5) % 15;
				item.nItemType = nItem % nFakeItemTypes;
				globals.p2HandedHitClasses[nItem] = (nItem * 7) % 15;
			}
			*globals.pnComponentItems = nComponentItems;
			*globals.ppItemTypesTxt = itemTypes;
			*globals.pnItemTypesTxtRecordCount = nFakeItemTypes;
		}
	}

	~D2WinCompFixture()
	{
		for (int i = 0; i < 2; ++i)
		{
			const CompGlobals& globals = comp_globals(i);
			const Saved& save = saved[i];
			std::memcpy(globals.pComponentItems, save.componentItems, sizeof(save.componentItems));
			std::memcpy(globals.p2HandedHitClasses, save.twoHandedHitClasses, sizeof(save.twoHandedHitClasses));
			*globals.pnComponentItems = save.nComponentItems;
			*globals.ppItemTypesTxt = save.pItemTypesTxt;
			*globals.pnItemTypesTxtRecordCount = save.nItemTypesTxtRecordCount;
			*globals.ppCompositeUnitList = save.pCompositeUnitList;
		}
	}
};

std::string text_or_null(const char* szText)
{
	return szText ? "[" + std::string(szText) + "]" : "null";
}
}


TEST_SUITE("D2WinCompTests")
{
	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A32B0")
	{
		const auto [sut, original] = make_d2win_pair(COMP_IsItemTypeEquivalent, 0x6F8A32B0);

		for (int32_t nItemType = 0; nItemType < nFakeItemTypes; ++nItemType)
		{
			for (int32_t nRequired = 0; nRequired < nFakeItemTypes; ++nRequired)
			{
				CAPTURE(nItemType);
				CAPTURE(nRequired);
				CHECK_EQ(sut(nItemType, nRequired), original(nItemType, nRequired));
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A3DC0")
	{
		const auto [sut, original] = make_d2win_pair(COMP_GetWeaponClassTokenIndex, 0x6F8A3DC0);

		const std::vector<uint8_t> items = { 0xFF, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 25, 50, 51, 52, 100, 101, 150, 200, 254 };
		for (uint32_t nClass = 0; nClass < 8; ++nClass)
		{
			for (uint8_t nRight : items)
			{
				for (uint8_t nLeft : items)
				{
					for (uint8_t nShield : { (uint8_t)0xFF, (uint8_t)3 })
					{
						uint8_t components[16];
						std::memset(components, 0xFF, sizeof(components));
						components[5] = nRight;
						components[6] = nLeft;
						components[7] = nShield;

						CAPTURE(nClass);
						CAPTURE(nRight);
						CAPTURE(nLeft);
						CAPTURE(nShield);
						CHECK_EQ(sut(components, nClass), original(components, nClass));
					}
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A4020")
	{
		const auto [sut, original] = make_d2win_pair(COMP_RemapComponent, 0x6F8A4020);

		for (int32_t nComponent = 0; nComponent < 8; ++nComponent)
		{
			for (int32_t nItem = 0; nItem < 60; ++nItem)
			{
				for (int32_t nComponentItems : { 255, 30, 0 })
				{
					for (int i = 0; i < 2; ++i)
					{
						*comp_globals(i).pnComponentItems = nComponentItems;
					}

					uint8_t nMoo = (uint8_t)nItem;
					uint8_t nOriginal = (uint8_t)nItem;
					sut(nComponent, &nMoo);
					original(nComponent, &nOriginal);

					CAPTURE(nComponent);
					CAPTURE(nItem);
					CAPTURE(nComponentItems);
					CHECK_EQ(nMoo, nOriginal);
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A4C70 (#10161)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10161, 0x6F8A4C70);
		const auto [get_title, original_get_title] = make_d2win_pair(D2Win_10160_GetPlayerTitle, 0x6F8A4CE0);

		for (int32_t nClass = -1; nClass <= 10; ++nClass)
		{
			for (BOOL bExpansion : { FALSE, TRUE, 2 })
			{
				for (int32_t nProgression = -1; nProgression <= 16; ++nProgression)
				{
					for (BOOL bHardcore : { FALSE, TRUE })
					{
						CAPTURE(nClass);
						CAPTURE(bExpansion);
						CAPTURE(nProgression);
						CAPTURE(bHardcore);
						CHECK_EQ(text_or_null(sut(nClass, nProgression, bHardcore, bExpansion)), text_or_null(original(nClass, nProgression, bHardcore, bExpansion)));
					}
				}

				for (int32_t nTitle = -1; nTitle <= 8; ++nTitle)
				{
					CAPTURE(nClass);
					CAPTURE(bExpansion);
					CAPTURE(nTitle);
					CHECK_EQ(text_or_null(get_title(nClass, nTitle, bExpansion)), text_or_null(original_get_title(nClass, nTitle, bExpansion)));
				}
			}
		}
	}

	// Accessors of the composite units
	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A44F0 (#10151)")
	{
		const auto [set_direction, original_set_direction] = make_d2win_pair(D2Win_10149, 0x6F8A4440);
		const auto [get_directions, original_get_directions] = make_d2win_pair(D2Win_10150, 0x6F8A4490);
		const auto [get_frames, original_get_frames] = make_d2win_pair(D2Win_10169, 0x6F8A44C0);
		const auto [set_frame, original_set_frame] = make_d2win_pair(D2Win_10151, 0x6F8A44F0);
		const auto [set_x, original_set_x] = make_d2win_pair(D2Win_10152, 0x6F8A4540);
		const auto [set_y, original_set_y] = make_d2win_pair(D2Win_10153, 0x6F8A4570);
		const auto [get_flags, original_get_flags] = make_d2win_pair(D2Win_10155, 0x6F8A45A0);
		const auto [set_flags, original_set_flags] = make_d2win_pair(D2Win_10156, 0x6F8A45D0);

		for (uint8_t nDirections : { 0, 1, 8, 32 })
		{
			for (int32_t nFrames : { 0, 1, 12 })
			{
				for (int32_t nValue : { -300, -1, 0, 5, 31, 32, 200, 255, 256, 3072, 3073, 100000 })
				{
					CAPTURE(nDirections);
					CAPTURE(nFrames);
					CAPTURE(nValue);

					D2CompositeUnitStrc moo = {};
					D2CompositeUnitStrc orig = {};
					moo.nDirections = orig.nDirections = nDirections;
					moo.nFrames = orig.nFrames = nFrames;
					moo.nFrame = orig.nFrame = 77;

					set_direction(&moo, (uint8_t)nValue);
					original_set_direction(&orig, (uint8_t)nValue);
					set_frame(&moo, nValue);
					original_set_frame(&orig, nValue);
					set_x(&moo, nValue);
					original_set_x(&orig, nValue);
					set_y(&moo, -nValue);
					original_set_y(&orig, -nValue);
					set_flags(&moo, (uint32_t)nValue);
					original_set_flags(&orig, (uint32_t)nValue);

					CHECK_EQ(get_directions(&moo), original_get_directions(&orig));
					CHECK_EQ(get_frames(&moo), original_get_frames(&orig));
					CHECK_EQ(get_flags(&moo), original_get_flags(&orig));
					CHECK_EQ(describe_differences(moo, orig), "");
				}
			}
		}
	}

	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A2BD0 (#10154)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10154, 0x6F8A2BD0);

		const std::vector<Unicode> wszAccount = to_unicode("Account");
		const std::vector<Unicode> wszChar = to_unicode("Character");
		const std::vector<Unicode> wszTag = to_unicode("Tag");
		const std::vector<Unicode> wszRealm = to_unicode("USEast");
		const std::vector<Unicode> wszEmpty = to_unicode("");

		D2CompositeUnitStrc moo = {};
		D2CompositeUnitStrc orig = {};
		std::memset(&moo, 0xCD, sizeof(moo));
		std::memset(&orig, 0xCD, sizeof(orig));
		sut(&moo, wszAccount.data(), wszChar.data(), wszTag.data(), wszRealm.data(), 87, 'D2XP');
		original(&orig, wszAccount.data(), wszChar.data(), wszTag.data(), wszRealm.data(), 87, 'D2XP');
		CHECK_EQ(describe_differences(moo, orig), "");

		sut(&moo, wszEmpty.data(), wszEmpty.data(), wszEmpty.data(), wszEmpty.data(), -1, 0);
		original(&orig, wszEmpty.data(), wszEmpty.data(), wszEmpty.data(), wszEmpty.data(), -1, 0);
		CHECK_EQ(describe_differences(moo, orig), "");
	}

	// Switching to a mode found in the COF files of the unit
	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A2C50 (#10143)")
	{
		const auto [sut, original] = make_d2win_pair(D2Win_10143, 0x6F8A2C50);

		D2CofDataStrc cofData[3] = {};
		D2CofNodeStrc cofNodes[3] = {};
		D2CofInfoStrc cofInfos[3] = {};
		for (int i = 0; i < 3; ++i)
		{
			cofData[i].nLayers = (uint8_t)(i + 2);
			cofData[i].nFrames = (uint8_t)(8 + i);
			cofData[i].nDirections = (uint8_t)(1 << (i + 2));
			cofData[i].nAnimRate = 128 + 64 * i;
			cofNodes[i].nMode = (uint32_t)(i * 3 + 1);
			cofNodes[i].pCofData = &cofData[i];
			cofInfos[i].pCofNode = &cofNodes[i];
			cofInfos[i].pNext = i < 2 ? &cofInfos[i + 1] : nullptr;
		}
		D2GfxInfoStrc gfxInfo = { cofInfos };

		for (uint32_t nMode : { 0u, 1u, 4u, 7u, 8u, 100u })
		{
			CAPTURE(nMode);
			D2CompositeUnitStrc moo = {};
			D2CompositeUnitStrc orig = {};
			moo.pGfxInfo = orig.pGfxInfo = &gfxInfo;
			moo.nMode = orig.nMode = 2;
			moo.nFrame = orig.nFrame = 0x500;
			CHECK_EQ(sut(&moo, nMode), original(&orig, nMode));
			CHECK_EQ(describe_differences(moo, orig), "");
		}
	}

	TEST_CASE_FIXTURE(D2WinCompFixture<NoOpFixture>, "D2Win.0x6F8A4400 (#10147)")
	{
		const auto [first, original_first] = make_d2win_pair(D2Win_10147, 0x6F8A4400);
		const auto [next, original_next] = make_d2win_pair(D2Win_10148, 0x6F8A4410);

		D2CompositeUnitStrc units[3] = {};
		units[0].pNext = &units[1];
		units[1].pNext = &units[2];

		for (D2CompositeUnitStrc* pList : { (D2CompositeUnitStrc*)nullptr, &units[0], &units[2] })
		{
			std::vector<D2CompositeUnitStrc*> walks[2];
			for (int i = 0; i < 2; ++i)
			{
				*comp_globals(i).ppCompositeUnitList = pList;
				for (D2CompositeUnitStrc* pUnit = (i == 0 ? first : original_first)(); pUnit && walks[i].size() < 10; pUnit = (i == 0 ? next : original_next)(pUnit))
				{
					walks[i].push_back(pUnit);
				}
			}
			CHECK_EQ(walks[0], walks[1]);
		}
	}
}

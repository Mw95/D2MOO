#include <doctest.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <ChatDlg.h>

#include "D2MultiTestFixtures.h"


extern D2MultiMotdStrc* gpMotdList_6F9C28D4;


namespace
{
struct MotdEntry
{
	int32_t nId;
	std::vector<uint8_t> text;

	bool operator==(const MotdEntry& other) const { return nId == other.nId && text == other.text; }
};

std::vector<MotdEntry> read_list(D2MultiMotdStrc* pList)
{
	std::vector<MotdEntry> entries;
	for (D2MultiMotdStrc* pMotd = pList; pMotd; pMotd = pMotd->pNext)
	{
		entries.push_back({ pMotd->nId, std::vector<uint8_t>(pMotd->szText, pMotd->szText + sizeof(pMotd->szText)) });
	}
	return entries;
}

// The nodes are allocated with the mocked FOG_Alloc (malloc)
void free_list(D2MultiMotdStrc** ppList)
{
	for (D2MultiMotdStrc* pMotd = *ppList; pMotd;)
	{
		D2MultiMotdStrc* pNext = pMotd->pNext;
		std::free(pMotd);
		pMotd = pNext;
	}
	*ppList = nullptr;
}
}


TEST_SUITE("D2MultiMotdTests")
{
	TEST_CASE_FIXTURE(D2MultiFixture<NoOpFixture>, "D2Multi.0x6F9AB1E0")
	{
		const auto [sut, original] = make_d2multi_pair(CHATDLG_MotdCallback, 0x6F9AB1E0);
		D2MultiMotdStrc** ppOriginalList = original_d2multi_global<D2MultiMotdStrc*>(0x6F9C28D4);
		D2WinTextBoxStrc** ppOriginalNewsTextBox = original_d2multi_global<D2WinTextBoxStrc*>(0x6F9C2760);

		// Without news text box, nothing is displayed
		gpNewsTextBox_6F9C2760 = nullptr;
		*ppOriginalNewsTextBox = nullptr;
		free_list(&gpMotdList_6F9C28D4);
		*ppOriginalList = nullptr;

		const std::string szLong(0x300, 'L');
		// Out of order ids, a replaced message and a message longer than the buffer
		const std::vector<std::pair<int32_t, std::string>> messages = {
			{ 5, "Fifth" }, { 2, "Second" }, { 9, "Ninth" }, { 0, "Zero" }, { 5, "Fifth, replaced" }, { 7, szLong }, { 3, "" },
		};

		for (const auto& [nId, szText] : messages)
		{
			CAPTURE(nId);
			const std::vector<uint8_t> text(szText.c_str(), szText.c_str() + szText.size() + 1);
			sut(nId, (uint32_t)text.size(), text.data());
			original(nId, (uint32_t)text.size(), text.data());

			const auto moo_list = read_list(gpMotdList_6F9C28D4);
			const auto original_list = read_list(*ppOriginalList);
			REQUIRE_EQ(moo_list.size(), original_list.size());
			for (size_t i = 0; i < moo_list.size(); ++i)
			{
				CAPTURE(i);
				CHECK_EQ(moo_list[i].nId, original_list[i].nId);
				CHECK_MESSAGE(moo_list[i].text == original_list[i].text, "Comparing the message text");
			}
		}

		// Sorted by id, the long message cleared the low byte of its id
		const auto list = read_list(gpMotdList_6F9C28D4);
		REQUIRE_EQ(list.size(), 6);
		CHECK_EQ(list[0].nId, 0);
		CHECK_EQ(list[1].nId, 2);
		CHECK_EQ(std::string((const char*)list[3].text.data()), "Fifth, replaced");

		free_list(&gpMotdList_6F9C28D4);
		free_list(ppOriginalList);
	}
}

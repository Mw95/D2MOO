#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <BnDownload.h>

#include "BnclientTestFixtures.h"


extern int32_t gnBnDownloadStatus;
extern char gszBnVersionFile[MAX_PATH];
extern char gszBnPatchFiles[256];
extern char gszBnVersionFormula[MAX_PATH];


namespace
{
struct DownloadApi
{
	decltype(&BNDOWNLOAD_SetPatchFiles) SetPatchFiles;
	decltype(&BNDOWNLOAD_SetVersionFormula) SetVersionFormula;
	decltype(&BNDOWNLOAD_SetStatus) SetStatus;
	decltype(&BNDOWNLOAD_GetStatus) GetStatus;
	decltype(&BNDOWNLOAD_SetVersionFile) SetVersionFile;
	decltype(&BNDOWNLOAD_HasVersionFile) HasVersionFile;
	int32_t* pnStatus;
	char* szVersionFile;
	char* szPatchFiles;
	char* szVersionFormula;
};

const DownloadApi& moo_download_api()
{
	static const DownloadApi api = {
		&BNDOWNLOAD_SetPatchFiles, &BNDOWNLOAD_SetVersionFormula, &BNDOWNLOAD_SetStatus, &BNDOWNLOAD_GetStatus, &BNDOWNLOAD_SetVersionFile, &BNDOWNLOAD_HasVersionFile,
		&gnBnDownloadStatus, gszBnVersionFile, gszBnPatchFiles, gszBnVersionFormula,
	};
	return api;
}

const DownloadApi& original_download_api()
{
	static const DownloadApi api = {
		reinterpret_cast<decltype(&BNDOWNLOAD_SetPatchFiles)>(original_bnclient_address(0x6FF03310)),
		reinterpret_cast<decltype(&BNDOWNLOAD_SetVersionFormula)>(original_bnclient_address(0x6FF03350)),
		reinterpret_cast<decltype(&BNDOWNLOAD_SetStatus)>(original_bnclient_address(0x6FF04DD0)),
		reinterpret_cast<decltype(&BNDOWNLOAD_GetStatus)>(original_bnclient_address(0x6FF04E00)),
		reinterpret_cast<decltype(&BNDOWNLOAD_SetVersionFile)>(original_bnclient_address(0x6FF05020)),
		reinterpret_cast<decltype(&BNDOWNLOAD_HasVersionFile)>(original_bnclient_address(0x6FF05040)),
		original_bnclient_global<int32_t>(0x6FF1D584),
		original_bnclient_global<char>(0x6FF1D5A0),
		original_bnclient_global<char>(0x6FF1D6A8),
		original_bnclient_global<char>(0x6FF1D7A8),
	};
	return api;
}

// Everything the functions change
struct DownloadState
{
	int32_t nStatus;
	std::vector<char> versionFile;
	std::vector<char> patchFiles;
	std::vector<char> versionFormula;

	bool operator==(const DownloadState& other) const
	{
		return nStatus == other.nStatus && versionFile == other.versionFile && patchFiles == other.patchFiles && versionFormula == other.versionFormula;
	}
};

DownloadState capture(const DownloadApi& api)
{
	return {
		*api.pnStatus,
		std::vector<char>(api.szVersionFile, api.szVersionFile + MAX_PATH),
		std::vector<char>(api.szPatchFiles, api.szPatchFiles + 256),
		std::vector<char>(api.szVersionFormula, api.szVersionFormula + MAX_PATH),
	};
}

void reset(const DownloadApi& api)
{
	*api.pnStatus = 0x55;
	std::memset(api.szVersionFile, 'v', MAX_PATH);
	std::memset(api.szPatchFiles, 'p', 256);
	std::memset(api.szVersionFormula, 'f', MAX_PATH);
}
}


TEST_SUITE("BnclientDownloadTests")
{
	TEST_CASE_FIXTURE(BnclientStormFixture<NoOpFixture>, "Bnclient.0x6FF03310 / Bnclient.0x6FF03350 / Bnclient.0x6FF04DD0 / Bnclient.0x6FF04E00 / Bnclient.0x6FF05020 / Bnclient.0x6FF05040")
	{
		// Patch files are a list of zero terminated strings
		const char szPatchFiles[] = "D2XP_IX86_1xx_110.mpq\0patch.txt\0";
		const std::string szLongName(MAX_PATH + 20, 'L');

		struct Step
		{
			const char* szName;
			void (*pfRun)(const DownloadApi& api, std::vector<int32_t>& results);
		};

		static const char* szPatches = szPatchFiles;
		static const std::string* pszLongName = &szLongName;
		const Step steps[] = {
			{ "Initial status", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.GetStatus()); results.push_back(api.HasVersionFile()); } },
			{ "Patch files", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetPatchFiles(szPatches, sizeof(szPatchFiles))); results.push_back(api.GetStatus()); } },
			{ "Partial patch files", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetPatchFiles("abc", 2)); } },
			{ "Status", [](const DownloadApi& api, std::vector<int32_t>& results) { api.SetStatus(42); results.push_back(api.GetStatus()); } },
			{ "Negative status", [](const DownloadApi& api, std::vector<int32_t>& results) { api.SetStatus(-1); results.push_back(api.GetStatus()); } },
			{ "Version formula", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetVersionFormula("A=1 B=2 C=3 4 A=A^S B=B-C C=C+A A=A^B")); } },
			{ "Long version formula", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetVersionFormula(pszLongName->c_str())); } },
			{ "Version file", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetVersionFile("IX86ver1.mpq")); results.push_back(api.HasVersionFile()); } },
			{ "Empty version file", [](const DownloadApi& api, std::vector<int32_t>& results) { results.push_back(api.SetVersionFile("")); results.push_back(api.HasVersionFile()); } },
		};

		const DownloadState moo_before = capture(moo_download_api());
		const DownloadState original_before = capture(original_download_api());
		reset(moo_download_api());
		reset(original_download_api());

		for (const Step& step : steps)
		{
			CAPTURE(step.szName);
			std::vector<int32_t> moo_results, original_results;
			step.pfRun(moo_download_api(), moo_results);
			step.pfRun(original_download_api(), original_results);
			CHECK_EQ(moo_results, original_results);
			CHECK_MESSAGE(capture(moo_download_api()) == capture(original_download_api()), "Comparing the download state");
		}

		CHECK_EQ(std::string(gszBnVersionFormula), szLongName.substr(0, MAX_PATH - 1));
		CHECK_EQ(gszBnPatchFiles[0], '\0');

		// Restore the state for the other tests
		for (const auto& [pApi, pState] : { std::make_pair(&moo_download_api(), &moo_before), std::make_pair(&original_download_api(), &original_before) })
		{
			*pApi->pnStatus = pState->nStatus;
			std::memcpy(pApi->szVersionFile, pState->versionFile.data(), MAX_PATH);
			std::memcpy(pApi->szPatchFiles, pState->patchFiles.data(), 256);
			std::memcpy(pApi->szVersionFormula, pState->versionFormula.data(), MAX_PATH);
		}
	}
}

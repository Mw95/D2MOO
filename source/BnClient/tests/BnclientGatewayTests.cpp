#include <doctest.h>

#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include <StormStorageMocks.h>

#include <BNetGW.h>

#include "BnclientTestFixtures.h"


namespace
{
// BNGatewayAccess member functions of one implementation
struct GatewayApi
{
	std::function<int(BNGatewayAccess*)> NumGateways;
	std::function<int(BNGatewayAccess*)> CurGateway;
	std::function<void(BNGatewayAccess*)> Load;
	std::function<void(BNGatewayAccess*)> SaveAndUnload;
	std::function<char*(BNGatewayAccess*, int)> DNS;
	std::function<int(BNGatewayAccess*, int)> GMT;
	std::function<char*(BNGatewayAccess*, int)> Name;
	std::function<char*(BNGatewayAccess*, int)> Realm;
	std::function<void(BNGatewayAccess*, int)> SetCurGateway;
	std::function<void(BNGatewayAccess*, char*)> UpdateGatewaysFromIni;
};

const GatewayApi& moo_gateway_api()
{
	static const GatewayApi api = {
		[](BNGatewayAccess* p) { return p->NumGateways(); },
		[](BNGatewayAccess* p) { return p->CurGateway(); },
		[](BNGatewayAccess* p) { p->Load(); },
		[](BNGatewayAccess* p) { p->SaveAndUnload(); },
		[](BNGatewayAccess* p, int n) { return p->DNS(n); },
		[](BNGatewayAccess* p, int n) { return p->GMT(n); },
		[](BNGatewayAccess* p, int n) { return p->Name(n); },
		[](BNGatewayAccess* p, int n) { return p->Realm(n); },
		[](BNGatewayAccess* p, int n) { p->SetCurGateway(n); },
		[](BNGatewayAccess* p, char* szIni) { p->UpdateGatewaysFromIni(szIni); },
	};
	return api;
}

// The member functions are __stdcall, with `this` pushed first
template<typename Function>
Function original_member(const char* szMangledName)
{
	const auto pFunction = GetProcAddress(get_original_bnclient(), szMangledName);
	if (!pFunction)
	{
		throw std::runtime_error(std::string("The original Bnclient.dll does not export ") + szMangledName);
	}
	return reinterpret_cast<Function>(pFunction);
}

const GatewayApi& original_gateway_api()
{
	static const GatewayApi api = {
		original_member<int(__stdcall*)(BNGatewayAccess*)>("?NumGateways@BNGatewayAccess@@QAGHXZ"),
		original_member<int(__stdcall*)(BNGatewayAccess*)>("?CurGateway@BNGatewayAccess@@QAGHXZ"),
		original_member<void(__stdcall*)(BNGatewayAccess*)>("?Load@BNGatewayAccess@@QAGXXZ"),
		original_member<void(__stdcall*)(BNGatewayAccess*)>("?SaveAndUnload@BNGatewayAccess@@QAGXXZ"),
		original_member<char*(__stdcall*)(BNGatewayAccess*, int)>("?DNS@BNGatewayAccess@@QAGPADH@Z"),
		original_member<int(__stdcall*)(BNGatewayAccess*, int)>("?GMT@BNGatewayAccess@@QAGHH@Z"),
		original_member<char*(__stdcall*)(BNGatewayAccess*, int)>("?Name@BNGatewayAccess@@QAGPADH@Z"),
		original_member<char*(__stdcall*)(BNGatewayAccess*, int)>("?Realm@BNGatewayAccess@@QAGPADH@Z"),
		original_member<void(__stdcall*)(BNGatewayAccess*, int)>("?SetCurGateway@BNGatewayAccess@@QAGXH@Z"),
		original_member<void(__stdcall*)(BNGatewayAccess*, char*)>("?UpdateGatewaysFromIni@BNGatewayAccess@@QAGXPAD@Z"),
	};
	return api;
}

template<class Fixture>
struct GatewayFixture : BnclientStormFixture<Fixture>
{
	GatewayFixture()
	{
		hook_storm_storage_mocks(this->hooks);
	}

	~GatewayFixture()
	{
		StormStorageMock::reset();
	}
};

const char gszGatewaysTxt[] =
	"[Server List Version]\r\n"
	"VER=1005\r\n"
	"\r\n"
	"[Server Gateways]\r\n"
	"1=uswest.battle.net\r\n"
	"2=useast.battle.net\r\n"
	"3=asia.battle.net\r\n"
	"4=europe.battle.net\r\n"
	"\r\n"
	"[uswest.battle.net]\r\n"
	"ZONE=8\r\n"
	"ENU=U.S. West\r\n"
	"\r\n"
	"[useast.battle.net]\r\n"
	"ZONE=5\r\n"
	"ENU=U.S. East\r\n"
	"\r\n"
	"[asia.battle.net]\r\n"
	"ZONE=-9\r\n"
	"\r\n"
	"[europe.battle.net]\r\n"
	"ENU=Europe\r\n";

// Pairs of DNS and realm name
const char gszRealmsBin[] = "uswest.battle.net\0USWest\0useast.battle.net\0USEast\0europe.battle.net\0Europe\0";

std::string region_list(const char* szVersion, const char* szCurrent, const std::vector<std::string>& entries)
{
	std::string list = std::string(szVersion) + '\0' + szCurrent + '\0';
	for (const auto& entry : entries)
	{
		list += entry + '\0';
	}
	return list + '\0';
}

// Everything observable through the accessors, for gateways 0 to NumGateways + 1
struct GatewayState
{
	int nNumGateways;
	int nCurGateway;
	std::vector<std::string> dns;
	std::vector<int> gmt;
	std::vector<std::string> names;
	std::vector<std::string> realms;

	bool operator==(const GatewayState& other) const
	{
		return nNumGateways == other.nNumGateways && nCurGateway == other.nCurGateway && dns == other.dns && gmt == other.gmt && names == other.names && realms == other.realms;
	}
};

GatewayState capture(const GatewayApi& api, BNGatewayAccess* pGateway)
{
	GatewayState state = { api.NumGateways(pGateway), api.CurGateway(pGateway) };
	for (int i = 0; i <= state.nNumGateways + 1; ++i)
	{
		state.dns.emplace_back(api.DNS(pGateway, i));
		state.gmt.push_back(api.GMT(pGateway, i));
		state.names.emplace_back(api.Name(pGateway, i));
		state.realms.emplace_back(api.Realm(pGateway, i));
	}
	return state;
}

struct ScenarioResult
{
	GatewayState state;
	std::vector<StormStorageMock::RegistryWrite> writes;
	std::map<std::string, std::vector<uint8_t>> registry;
};

// Runs the same scenario on a new object of each implementation, starting from the same registry and files
std::vector<ScenarioResult> run_scenario(const std::function<void()>& setup, const std::function<void(const GatewayApi&, BNGatewayAccess*)>& scenario)
{
	std::vector<ScenarioResult> results;
	for (const GatewayApi* pApi : { &moo_gateway_api(), &original_gateway_api() })
	{
		StormStorageMock::reset();
		StormStorageMock::set_file("Data\\Global\\Realms.bin", std::string(gszRealmsBin, sizeof(gszRealmsBin)));
		StormStorageMock::set_file("DATA\\GLOBAL\\gateways.txt", gszGatewaysTxt);
		setup();

		BNGatewayAccess tGateway;
		std::memset(&tGateway, 0x00, sizeof(tGateway));
		pApi->Load(&tGateway);
		scenario(*pApi, &tGateway);

		ScenarioResult result;
		result.state = capture(*pApi, &tGateway);
		pApi->SaveAndUnload(&tGateway);
		result.writes = StormStorageMock::registry_writes;
		result.registry = StormStorageMock::registry;
		results.push_back(result);
	}

	CHECK_MESSAGE(results[0].state == results[1].state, "Comparing the gateways");
	CHECK_EQ(results[0].state.nNumGateways, results[1].state.nNumGateways);
	CHECK_EQ(results[0].state.nCurGateway, results[1].state.nCurGateway);
	CHECK_EQ(results[0].state.dns, results[1].state.dns);
	CHECK_EQ(results[0].state.names, results[1].state.names);
	CHECK_EQ(results[0].state.realms, results[1].state.realms);
	CHECK_MESSAGE(results[0].writes == results[1].writes, "Comparing the registry writes");
	CHECK_MESSAGE(results[0].registry == results[1].registry, "Comparing the final registry");
	return results;
}
}


TEST_SUITE("BnclientGatewayTests")
{
	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05090 (#11) saved gateway list")
	{
		const auto list = region_list("1003", "02", { "uswest.battle.net", "8", "U.S. West", "useast.battle.net", "5", "U.S. East", "europe.battle.net", "-1", "Europe" });
		const auto results = run_scenario(
			[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
			[](const GatewayApi&, BNGatewayAccess*) {});

		const auto& state = results[0].state;
		CHECK_EQ(state.nNumGateways, 3);
		CHECK_EQ(state.nCurGateway, 2);
		CHECK_EQ(state.dns[3], "europe.battle.net");
		CHECK_EQ(state.gmt[3], -1);
		CHECK_EQ(state.names[1], "U.S. West");
		CHECK_EQ(state.realms[2], "USEast");
		// Invalid gateways
		CHECK_EQ(state.dns[0], "");
		CHECK_EQ(state.dns[4], "");
		// Nothing changed, so nothing is written
		CHECK(results[0].writes.empty());
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05090 (#11) override list")
	{
		const auto list = region_list("1003", "01", { "uswest.battle.net", "8", "U.S. West", "useast.battle.net", "5", "U.S. East" });
		const auto override_list = region_list("1004", "01", { "private.server.net", "1", "Private" });
		const auto results = run_scenario(
			[&]
			{
				StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size());
				StormStorageMock::set_registry_data("Configuration", "Override Battle.net gateways", override_list.data(), override_list.size());
			},
			[](const GatewayApi& api, BNGatewayAccess* pGateway)
			{
				// The selection is saved to the override list
				api.SetCurGateway(pGateway, 1);
			});

		CHECK_EQ(results[0].state.nNumGateways, 1);
		CHECK_EQ(results[0].state.dns[1], "private.server.net");
		REQUIRE_EQ(results[0].writes.size(), 1);
		CHECK_EQ(results[0].writes[0].szValue, "Override Battle.net gateways");
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05090 (#11) default list from gateways.txt")
	{
		const auto results = run_scenario([] {}, [](const GatewayApi&, BNGatewayAccess*) {});

		const auto& state = results[0].state;
		CHECK_EQ(state.nNumGateways, 4);
		CHECK_EQ(state.dns[1], "uswest.battle.net");
		CHECK_EQ(state.gmt[1], 8);
		// Without ZONE. Note that keys are searched past the end of their section, so a gateway without ENU gets the next one found.
		CHECK_EQ(state.gmt[4], 0);
		CHECK_EQ(state.names[4], "Europe");
		CHECK_EQ(state.realms[3], "");
		CHECK_EQ(state.realms[4], "Europe");
		CHECK_FALSE(results[0].writes.empty());
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05090 (#11) obsolete list")
	{
		const auto list = region_list("999", "01", { "old.battle.net", "0", "Old" });
		const auto results = run_scenario(
			[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
			[](const GatewayApi&, BNGatewayAccess*) {});

		// Replaced by the default list
		CHECK_EQ(results[0].state.nNumGateways, 4);
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05090 (#11) invalid current gateway")
	{
		for (const char* szCurrent : { "00", "09", "x" })
		{
			CAPTURE(szCurrent);
			const auto list = region_list("1003", szCurrent, { "a.net", "8", "A", "b.net", "-5", "B", "c.net", "1", "C" });
			const auto results = run_scenario(
				[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
				[](const GatewayApi&, BNGatewayAccess*) {});

			// Picked from the time zone of the machine
			CHECK_GE(results[0].state.nCurGateway, 1);
			CHECK_LE(results[0].state.nCurGateway, 3);
		}
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF058F0 (#18) / Bnclient.0x6FF05580 (#17)")
	{
		const auto list = region_list("1003", "01", { "a.net", "8", "A", "b.net", "5", "B", "c.net", "1", "C" });
		for (const int nGateway : { -1, 0, 1, 2, 3, 4, 100 })
		{
			CAPTURE(nGateway);
			const auto results = run_scenario(
				[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
				[&](const GatewayApi& api, BNGatewayAccess* pGateway) { api.SetCurGateway(pGateway, nGateway); });

			const bool bValid = nGateway >= 1 && nGateway <= 3;
			CHECK_EQ(results[0].state.nCurGateway, bValid ? nGateway : 1);
			CHECK_EQ(results[0].writes.size(), bValid ? 1 : 0);
		}
	}

	TEST_CASE_FIXTURE(GatewayFixture<NoOpFixture>, "Bnclient.0x6FF05CD0 (#21)")
	{
		const auto list = region_list("1003", "02", { "a.net", "8", "A", "b.net", "5", "B" });

		SUBCASE("Newer list")
		{
			const auto results = run_scenario(
				[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
				[](const GatewayApi& api, BNGatewayAccess* pGateway)
				{
					std::string ini = gszGatewaysTxt;
					api.UpdateGatewaysFromIni(pGateway, ini.data());
				});
			CHECK_EQ(results[0].state.nNumGateways, 4);
			// The gateway closest to the previous one (GMT 5) is picked
			CHECK_EQ(results[0].state.nCurGateway, 2);
		}

		SUBCASE("Older list")
		{
			const auto results = run_scenario(
				[&] { StormStorageMock::set_registry_data("Configuration", "Diablo II Battle.net gateways", list.data(), list.size()); },
				[](const GatewayApi& api, BNGatewayAccess* pGateway)
				{
					std::string ini = gszGatewaysTxt;
					ini.replace(ini.find("1005"), 4, "1001");
					api.UpdateGatewaysFromIni(pGateway, ini.data());
				});
			CHECK_EQ(results[0].state.nNumGateways, 2);
		}
	}
}

#include <doctest.h>

#include <cstring>
#include <string>
#include <vector>

#include <BigUnsigned.h>
#include <ImportTablePatch.h>
#include <StormBigMocks.h>

#include <BnRecv.h>
#include <BnSRP.h>
#include <SRP/SRP.h>

#include "BnclientTestFixtures.h"


extern SRP gtBnSRP;
extern char gszBnSRPAccountName[256];
extern BOOL gbBnSRPUpgradingLogon;
extern BnSRPSession gtBnSRPSession;
extern uint8_t gpBnSRPNewSalt[32];
extern uint8_t gpBnSRPNewVerifier[32];


namespace
{
struct SRPApi
{
	decltype(&BNSRP_Initialize) Initialize;
	decltype(&BNSRP_Reset) Reset;
	decltype(&BNSRP_Logon) Logon;
	decltype(&BNSRP_SendLogon) SendLogon;
	decltype(&BNSRP_HandleLogonChallenge) HandleLogonChallenge;
	decltype(&BNSRP_CreateAccount) CreateAccount;
	decltype(&BNSRP_ChangePassword) ChangePassword;
	decltype(&BNSRP_HandleChangeChallenge) HandleChangeChallenge;
	decltype(&BNSRP_RequestUpgrade) RequestUpgrade;
	decltype(&BNSRP_SendUpgradeProof) SendUpgradeProof;
	decltype(&BNSRP_VerifyServerProof) VerifyServerProof;
	decltype(&BNSRP_IsUpgradingLogon) IsUpgradingLogon;
	decltype(&BNSRP_ClearPasswords) ClearPasswords;
	SRP* pSRP;
	char* szAccountName;
	BOOL* pbUpgradingLogon;
	BnSRPSession* pSession;
	uint8_t* pNewSalt;
	uint8_t* pNewVerifier;
};

const SRPApi& moo_srp_api()
{
	static const SRPApi api = {
		&BNSRP_Initialize, &BNSRP_Reset, &BNSRP_Logon, &BNSRP_SendLogon, &BNSRP_HandleLogonChallenge, &BNSRP_CreateAccount, &BNSRP_ChangePassword,
		&BNSRP_HandleChangeChallenge, &BNSRP_RequestUpgrade, &BNSRP_SendUpgradeProof, &BNSRP_VerifyServerProof, &BNSRP_IsUpgradingLogon, &BNSRP_ClearPasswords,
		&gtBnSRP, gszBnSRPAccountName, &gbBnSRPUpgradingLogon, &gtBnSRPSession, gpBnSRPNewSalt, gpBnSRPNewVerifier,
	};
	return api;
}

template<typename Function>
Function original_function(uintptr_t nAddress)
{
	return reinterpret_cast<Function>(original_bnclient_address(nAddress));
}

const SRPApi& original_srp_api()
{
	static const SRPApi api = {
		original_function<decltype(&BNSRP_Initialize)>(0x6FF08380),
		original_function<decltype(&BNSRP_Reset)>(0x6FF083C0),
		original_function<decltype(&BNSRP_Logon)>(0x6FF086C0),
		original_function<decltype(&BNSRP_SendLogon)>(0x6FF087A0),
		original_function<decltype(&BNSRP_HandleLogonChallenge)>(0x6FF087F0),
		original_function<decltype(&BNSRP_CreateAccount)>(0x6FF08850),
		original_function<decltype(&BNSRP_ChangePassword)>(0x6FF088F0),
		original_function<decltype(&BNSRP_HandleChangeChallenge)>(0x6FF08A00),
		original_function<decltype(&BNSRP_RequestUpgrade)>(0x6FF08A80),
		original_function<decltype(&BNSRP_SendUpgradeProof)>(0x6FF08AD0),
		original_function<decltype(&BNSRP_VerifyServerProof)>(0x6FF08B70),
		original_function<decltype(&BNSRP_IsUpgradingLogon)>(0x6FF08B90),
		original_function<decltype(&BNSRP_ClearPasswords)>(0x6FF08BA0),
		original_bnclient_global<SRP>(0x6FF1D948),
		original_bnclient_global<char>(0x6FF1D950),
		original_bnclient_global<BOOL>(0x6FF1DA50),
		original_bnclient_global<BnSRPSession>(0x6FF1DA58),
		original_bnclient_global<uint8_t>(0x6FF1DB18),
		original_bnclient_global<uint8_t>(0x6FF1DB38),
	};
	return api;
}

// The SRP modulus and generator of Bnclient
const uint8_t gpModulus[32] = {
	0x87, 0xC7, 0x23, 0x85, 0x65, 0xF6, 0x16, 0x12, 0xD9, 0x12, 0x32, 0xC7, 0x78, 0x6C, 0x97, 0x7E,
	0x55, 0xB5, 0x92, 0xA0, 0x8C, 0xB6, 0x86, 0x21, 0x03, 0x18, 0x99, 0x61, 0x8B, 0x1A, 0xFF, 0xF8,
};

struct TickCountMock
{
	static inline DWORD dwTickCount = 0x12345678;

	static DWORD WINAPI GetTickCount()
	{
		return dwTickCount;
	}
};

template<class Fixture>
struct SRPFixture : BnclientSendFixture<Fixture>
{
	ImportTablePatch patches;

	SRPFixture()
	{
		hook_storm_big_mocks(this->hooks);
		patches.patch_both(get_original_bnclient(), "KERNEL32.dll", "GetTickCount", reinterpret_cast<const void*>(&TickCountMock::GetTickCount));
	}
};

std::vector<uint8_t> bytes(const void* pData, size_t nSize)
{
	return std::vector<uint8_t>(static_cast<const uint8_t*>(pData), static_cast<const uint8_t*>(pData) + nSize);
}

// The random generator is seeded with the time, both implementations start from the same state instead
void set_random_state(const SRPApi& api, uint8_t nSeed)
{
	SRPContext* pContext = api.pSRP->m_pContext;
	REQUIRE(pContext != nullptr);
	for (int i = 0; i < 20; ++i)
	{
		pContext->pRandomSeed1[i] = (uint8_t)(nSeed + i);
		pContext->pRandomSeed2[i] = (uint8_t)(nSeed * 3 + i * 7);
		pContext->pRandomPool[i] = 0;
	}
	pContext->nRandomPoolAvailable = 0;
}

// Everything observable after each step of a scenario
struct Observation
{
	std::string szStep;
	int32_t nResult;
	std::vector<BnSendMock::Packet> packets;
	std::vector<uint8_t> session;
	std::vector<uint8_t> accountName;
	BOOL bUpgradingLogon;
	std::vector<uint8_t> newSaltAndVerifier;
	int nLiveNumbers;

	bool operator==(const Observation& other) const
	{
		return szStep == other.szStep && nResult == other.nResult && packets == other.packets && session == other.session && accountName == other.accountName
			&& bUpgradingLogon == other.bUpgradingLogon && newSaltAndVerifier == other.newSaltAndVerifier && nLiveNumbers == other.nLiveNumbers;
	}
};

struct Recorder
{
	const SRPApi& api;
	std::vector<Observation> observations;
	int nInitialLiveNumbers = StormBigMock::nLiveNumbers;

	void record(const char* szStep, int32_t nResult)
	{
		observations.push_back({
			szStep,
			nResult,
			BnSendMock::sent,
			bytes(api.pSession, sizeof(BnSRPSession)),
			bytes(api.szAccountName, 256),
			*api.pbUpgradingLogon,
			bytes(api.pNewSalt, 64),
			StormBigMock::nLiveNumbers - nInitialLiveNumbers,
		});
		BnSendMock::sent.clear();
	}
};

std::vector<uint8_t> server_value(uint8_t nSeed, uint8_t nTop)
{
	std::vector<uint8_t> value(32);
	for (size_t i = 0; i < value.size(); ++i)
	{
		value[i] = (uint8_t)(nSeed * 31 + i * 17);
	}
	value[31] = nTop;
	return value;
}

std::vector<Observation> run_scenario(const SRPApi& api)
{
	Recorder recorder{ api };
	BnSendMock::sent.clear();

	// The context is allocated by a global constructor, with D2MOO's Storm stubs it is missing
	static SRPContext tMooContext;
	if (!api.pSRP->m_pContext)
	{
		api.pSRP->m_pContext = &tMooContext;
	}
	// Numbers created before the mocks were installed are not deleted with them
	api.pSRP->m_pContext->bInitialized = FALSE;

	api.Initialize();
	set_random_state(api, 1);
	std::memset(api.pSession, 0, sizeof(BnSRPSession));
	*api.pbUpgradingLogon = FALSE;
	recorder.record("Initialize", 0);

	const auto salt = server_value(1, 0x42);
	const auto B = server_value(2, 0x70);
	const auto zero = std::vector<uint8_t>(32, 0);
	const auto tooBig = std::vector<uint8_t>(32, 0xFF);
	const auto equalToModulus = bytes(gpModulus, sizeof(gpModulus));

	recorder.record("Logon", api.Logon("Account", "Password"));
	recorder.record("SendLogon", api.SendLogon());
	recorder.record("Zero challenge", api.HandleLogonChallenge(salt.data(), zero.data()));

	recorder.record("Logon again", api.Logon("account", "pAsSwOrD"));
	recorder.record("Challenge too big", api.HandleLogonChallenge(salt.data(), tooBig.data()));
	recorder.record("Logon with the modulus", api.Logon("Account", "Password"));
	recorder.record("Challenge equal to the modulus", api.HandleLogonChallenge(salt.data(), equalToModulus.data()));

	recorder.record("Logon a third time", api.Logon("Account", "Password"));
	recorder.record("Challenge", api.HandleLogonChallenge(salt.data(), B.data()));

	// The server proof computed from the session, and a wrong one
	uint8_t pM2[20];
	api.pSRP->m_pContext->ComputeM2(api.pSession->A, api.pSession->M1, api.pSession->K, pM2);
	recorder.record("Valid server proof", api.VerifyServerProof(pM2));
	pM2[7] ^= 1;
	recorder.record("Invalid server proof", api.VerifyServerProof(pM2));

	recorder.record("Create account", api.CreateAccount("NewAccount", "NewPassword"));
	recorder.record("Create account with an empty password", api.CreateAccount("Other", ""));

	recorder.record("Change password", api.ChangePassword("Account", "Password", "NewPassword"));
	recorder.record("Change challenge", api.HandleChangeChallenge(salt.data(), B.data()));
	recorder.record("Change password again", api.ChangePassword("Account", "Password", "Other"));
	recorder.record("Zero change challenge", api.HandleChangeChallenge(salt.data(), zero.data()));

	recorder.record("Logon before the upgrade", api.Logon("Account", "Password"));
	recorder.record("Upgrade request", api.RequestUpgrade(TRUE));
	recorder.record("Is upgrading", api.IsUpgradingLogon());
	recorder.record("Second upgrade request", api.RequestUpgrade(TRUE));
	recorder.record("Upgrade request without logon", api.RequestUpgrade(FALSE));
	recorder.record("Upgrade proof", api.SendUpgradeProof(0xCAFEBABE));
	api.ClearPasswords();
	recorder.record("Clear passwords", 0);

	api.Reset();
	recorder.record("Reset", 0);
	if (api.pSRP->m_pContext == &tMooContext)
	{
		api.pSRP->m_pContext = nullptr;
	}
	return recorder.observations;
}
}


TEST_SUITE("BnclientSRPTests")
{
	TEST_CASE_FIXTURE(SRPFixture<NoOpFixture>, "Bnclient.0x6FF08380 / Bnclient.0x6FF086C0 / Bnclient.0x6FF087F0 / Bnclient.0x6FF08850 / Bnclient.0x6FF088F0 / Bnclient.0x6FF08A00 / Bnclient.0x6FF08A80 / Bnclient.0x6FF08AD0 / Bnclient.0x6FF08B70")
	{
		static_assert(sizeof(BnSRPSession) == 0xBC, "BnSRPSession size");
		static_assert(sizeof(SRPContext) == 0x4C, "SRPContext size");

		const std::vector<Observation> moo_observations = run_scenario(moo_srp_api());
		const std::vector<Observation> original_observations = run_scenario(original_srp_api());

		REQUIRE_EQ(moo_observations.size(), original_observations.size());
		for (size_t i = 0; i < moo_observations.size(); ++i)
		{
			const Observation& moo = moo_observations[i];
			const Observation& original = original_observations[i];
			CAPTURE(moo.szStep);
			CHECK_EQ(moo.nResult, original.nResult);
			CHECK_MESSAGE(moo.packets == original.packets, "Comparing the packets");
			CHECK_MESSAGE(moo.session == original.session, "Comparing the session");
			CHECK_MESSAGE(moo.accountName == original.accountName, "Comparing the account name");
			CHECK_EQ(moo.bUpgradingLogon, original.bUpgradingLogon);
			CHECK_MESSAGE(moo.newSaltAndVerifier == original.newSaltAndVerifier, "Comparing the new salt and verifier");
			CHECK_EQ(moo.nLiveNumbers, original.nLiveNumbers);
		}

		// The client public key is A = g^a % N
		const auto find = [&moo_observations](const char* szStep) -> const Observation&
		{
			for (const Observation& observation : moo_observations)
			{
				if (observation.szStep == szStep)
				{
					return observation;
				}
			}
			throw std::runtime_error(szStep);
		};
		const Observation& logon = find("Logon");
		REQUIRE_EQ(logon.packets.size(), 1);
		CHECK_EQ(logon.packets[0].nMessageId, SID_AUTH_ACCOUNTLOGON);
		const BnSRPSession* pSession = reinterpret_cast<const BnSRPSession*>(logon.session.data());
		const BigUnsigned A = BigUnsigned::pow_mod(BigUnsigned(0x2F), BigUnsigned::from_bytes(pSession->a, 32), BigUnsigned::from_bytes(gpModulus, 32));
		CHECK_EQ(BigUnsigned::from_bytes(pSession->A, 32).to_bytes(), A.to_bytes());
		CHECK_EQ(std::string(pSession->szUserName), "ACCOUNT");
		CHECK_EQ(std::string(pSession->szPassword), "PASSWORD");

		CHECK_EQ(find("Challenge").nResult, TRUE);
		CHECK_EQ(find("Zero challenge").nResult, FALSE);
		CHECK_EQ(find("Valid server proof").nResult, TRUE);
		CHECK_EQ(find("Invalid server proof").nResult, FALSE);
		// No number is leaked
		CHECK_EQ(moo_observations.back().nLiveNumbers, 0);
	}
}

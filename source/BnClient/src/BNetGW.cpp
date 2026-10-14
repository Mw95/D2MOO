#include "BNetGW.h"

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <Fog.h>
#include <Storm.h>

#include "BnLog.h"


static const char gszOverrideGatewaysValue[] = "Override Battle.net gateways";
static const char gszGatewaysValue[] = "Diablo II Battle.net gateways";

BNGatewayAccess gtBnGatewayAccess;


//Bnclient.0x6FF05050 (#14)
int __stdcall BNGatewayAccess::NumGateways()
{
	return m_nNumGateways;
}

//Bnclient.0x6FF05060 (#2)
int __stdcall BNGatewayAccess::CurGateway()
{
	return m_nCurrentGateway;
}

//Bnclient.0x6FF05070 (#1)
BNGatewayAccess& BNGatewayAccess::operator=(const BNGatewayAccess& other)
{
	memcpy(this, &other, sizeof(*this));
	return *this;
}

//Bnclient.0x6FF05090 (#11)
void __stdcall BNGatewayAccess::Load()
{
	if (regionList)
	{
		return;
	}

	m_nNumGateways = 0;
	m_nCurrentGateway = 0;
	m_pRealmsList = nullptr;
	regionList = nullptr;
	regionListSize = 0;
	regionListVersion = 0;
	m_szEmpty[0] = '\0';

	GetBattlenetRealmsList();
	GetBattlenetGatewayList();

	if (regionList && regionListVersion < BASE_REGIONLIST_VERSION)
	{
		BNLOG_Printf("Obsolete gateway list (%d) - autodeleting", regionListVersion);
		m_bDirty = FALSE;
		SaveAndUnload();
		SRegDeleteValue("Configuration", gszGatewaysValue, 2);
	}

	if (!regionList)
	{
		WriteDefaultGatewayList();
	}

	D2_ASSERT(regionListVersion >= BASE_REGIONLIST_VERSION);

	int count = -2;
	const char* pString = regionList;
	for (int nOffset = 0; nOffset < regionListSize; ++count)
	{
		const int nLength = SStrLen(pString) + 1;
		pString += nLength;
		nOffset += nLength;
	}
	--count;

	D2_ASSERT((count % ENTRIES_PER_GATEWAY) == 0);

	m_nNumGateways = count / ENTRIES_PER_GATEWAY;

	char* pEnd;
	m_nCurrentGateway = strtoul(&regionList[SStrLen(regionList) + 1], &pEnd, 10);
	m_bDirty = FALSE;

	if (m_nCurrentGateway < 1 || m_nCurrentGateway > m_nNumGateways)
	{
		BNLOG_Printf("Auto-picking gateway based on GMT");
		PickClosestZone(GetSystemTimeZone());
	}
}

//Bnclient.0x6FF052D0 (#10)
int BNGatewayAccess::GetSystemTimeZone()
{
	TIME_ZONE_INFORMATION tTimeZoneInformation;
	SMemZero(&tTimeZoneInformation, sizeof(tTimeZoneInformation));
	GetTimeZoneInformation(&tTimeZoneInformation);

	const LANGID nLanguageId = GetUserDefaultLangID();
	if (PRIMARYLANGID(nLanguageId) == LANG_ENGLISH && SUBLANGID(nLanguageId) == SUBLANG_ENGLISH_AUS)
	{
		return 480;
	}

	return tTimeZoneInformation.Bias;
}

//Bnclient.0x6FF05320 (#15)
void BNGatewayAccess::PickClosestZone(int nTimeZoneBias)
{
	BNLOG_Command(BNLOG_COMMAND_INDENT, 4);

	const int nHours = nTimeZoneBias / 60;
	const int nMinutes = nTimeZoneBias % 60;
	BNLOG_Printf("Find gateway closest to %02d.%02d", nHours, nMinutes);

	int nClosestGateway = 1;
	int nClosestDifference = 23 * 60;
	for (int nGateway = 1; nGateway <= m_nNumGateways; ++nGateway)
	{
		char* pGmt = Nth(nGateway);
		if (*pGmt)
		{
			pGmt += strlen(pGmt) + 1;
		}

		char* pEnd;
		const int nDifference = abs(60 * strtol(pGmt, &pEnd, 10) - nTimeZoneBias);
		if (nDifference < nClosestDifference)
		{
			nClosestDifference = nDifference;
			nClosestGateway = nGateway;
		}
	}

	char* pGmt = Nth(nClosestGateway);
	if (*pGmt)
	{
		pGmt += strlen(pGmt) + 1;
	}

	char* pEnd;
	const int nGmt = strtol(pGmt, &pEnd, 10);

	BNLOG_Printf("Gateway %d (%s at GMT %02d) is closest to %02d.%02d", nClosestGateway, Nth(nClosestGateway), nGmt, nHours, nMinutes);
	BNLOG_Command(BNLOG_COMMAND_INDENT, -4);

	SetCurGateway(nClosestGateway);
}

//Bnclient.0x6FF05580 (#17)
void __stdcall BNGatewayAccess::SaveAndUnload()
{
	if (m_bDirty && regionList)
	{
		BNLOG_Printf("Recording gateway list selection");

		char* szCurrentGateway = &regionList[SStrLen(regionList) + 1];
		szCurrentGateway[0] = '0' + m_nCurrentGateway / 10;
		szCurrentGateway[1] = '0' + m_nCurrentGateway % 10;

		const char* szRegistryValue = m_bOverride ? gszOverrideGatewaysValue : gszGatewaysValue;

		D2_ASSERT(regionList[regionListSize-1] == 0 && regionList[regionListSize-2] == 0);

		SRegSaveData("Configuration", szRegistryValue, 0x82, regionList, regionListSize);
	}

	if (regionList)
	{
		SMemFree(regionList, __FILE__, __LINE__, 0);
		regionList = nullptr;
		regionListSize = 0;
	}

	if (m_pRealmsList)
	{
		SMemFree(m_pRealmsList, __FILE__, __LINE__, 0);
		m_pRealmsList = nullptr;
	}
}

//Bnclient.0x6FF05680 (#13)
char* BNGatewayAccess::Nth(int nGateway)
{
	char* pString = regionList;
	if (!pString || nGateway < 1 || nGateway > m_nNumGateways)
	{
		return m_szEmpty;
	}

	const int nIndex = ENTRIES_PER_GATEWAY * nGateway;
	int nCurrentIndex = 1;
	int nOffset = 0;
	while (nCurrentIndex < nIndex)
	{
		if (nOffset >= regionListSize)
		{
			return m_szEmpty;
		}

		const int nLength = SStrLen(pString) + 1;
		pString += nLength;
		nOffset += nLength;
		++nCurrentIndex;
	}

	if (nOffset >= regionListSize || nCurrentIndex > nIndex)
	{
		return m_szEmpty;
	}

	return pString;
}

//Bnclient.0x6FF056E0 (#3)
char* __stdcall BNGatewayAccess::DNS(int nGateway)
{
	return Nth(nGateway);
}

//Bnclient.0x6FF05740 (#6)
int __stdcall BNGatewayAccess::GMT(int nGateway)
{
	char* pGmt = Nth(nGateway);
	if (*pGmt)
	{
		pGmt += SStrLen(pGmt) + 1;
	}

	char* pEnd;
	return strtol(pGmt, &pEnd, 10);
}

//Bnclient.0x6FF057C0 (#12)
char* __stdcall BNGatewayAccess::Name(int nGateway)
{
	char* pDns = Nth(nGateway);
	if (!*pDns)
	{
		return pDns;
	}

	char* pGmt = &pDns[SStrLen(pDns) + 1];
	if (!*pGmt)
	{
		return pGmt;
	}

	return &pGmt[SStrLen(pGmt) + 1];
}

//Bnclient.0x6FF05850 (#16)
char* __stdcall BNGatewayAccess::Realm(int nGateway)
{
	const char* szDns = Nth(nGateway);

	char* pRealmsList = m_pRealmsList;
	while (*pRealmsList)
	{
		if (!SStrCmpI(pRealmsList, szDns, INT_MAX))
		{
			return &pRealmsList[SStrLen(pRealmsList) + 1];
		}

		pRealmsList += SStrLen(pRealmsList) + 1;
		if (!*pRealmsList)
		{
			break;
		}

		pRealmsList += SStrLen(pRealmsList) + 1;
	}

	return (char*)"";
}

//Bnclient.0x6FF058F0 (#18)
void __stdcall BNGatewayAccess::SetCurGateway(int nGateway)
{
	if (regionList && nGateway >= 1 && nGateway <= m_nNumGateways)
	{
		if (nGateway > 99)
		{
			nGateway = 99;
		}

		m_nCurrentGateway = nGateway;
		m_bDirty = TRUE;
	}
}

//Bnclient.0x6FF05920 (#9)
void BNGatewayAccess::GetGatewayList(const char* szRegistryValue)
{
	D2_ASSERT(regionList == NULL);

	uint32_t nSize = 0;
	if (!SRegLoadData("Configuration", szRegistryValue, 0x82, nullptr, 0, &nSize) || !nSize)
	{
		return;
	}

	regionListSize = nSize;
	regionList = (char*)SMemAlloc(nSize, __FILE__, __LINE__, 0);
	if (!SRegLoadData("Configuration", szRegistryValue, 0x82, regionList, regionListSize, nullptr))
	{
		SMemFree(regionList, __FILE__, __LINE__, 0);
		regionList = nullptr;
		regionListSize = 0;
	}

	regionListVersion = 0;
	if (regionList)
	{
		char* pEnd = regionList;
		regionListVersion = strtoul(regionList, &pEnd, 10);
		if (regionList == pEnd)
		{
			regionListVersion = 0;
		}
	}
}

//Bnclient.0x6FF05A00 (#7)
void BNGatewayAccess::GetBattlenetGatewayList()
{
	m_bOverride = FALSE;
	GetGatewayList(gszOverrideGatewaysValue);
	if (regionList)
	{
		m_bOverride = TRUE;
		return;
	}

	GetGatewayList(gszGatewaysValue);
}

//Bnclient.0x6FF05A40 (#8)
void BNGatewayAccess::GetBattlenetRealmsList()
{
	uint32_t nSize = 0;
	const BOOL loaded = SFileLoadFile("Data\\Global\\Realms.bin", (void**)&m_pRealmsList, &nSize, 0, nullptr);
	D2_ASSERT(loaded);
}

//Bnclient.0x6FF05A90 (#22)
void BNGatewayAccess::WriteDefaultGatewayList()
{
	BNLOG_Printf("Writing default gateway list");

	char* pBuffer;
	uint32_t nSize = 0;
	const BOOL loaded = SFileLoadFile("DATA\\GLOBAL\\gateways.txt", (void**)&pBuffer, &nSize, 0, nullptr);
	D2_ASSERT(loaded);

	if (pBuffer)
	{
		UpdateGatewaysFromIni(pBuffer);
	}
}

//Bnclient.0x6FF05B00 (#20)
char* BNGatewayAccess::SkipToEOL(char* pCursor, char* pEnd)
{
	while (pCursor < pEnd && *pCursor && *pCursor != '\r' && *pCursor != '\n')
	{
		++pCursor;
	}

	return pCursor;
}

//Bnclient.0x6FF05B30 (#19)
char* BNGatewayAccess::SkipEOL(char* pCursor, char* pEnd)
{
	while (pCursor < pEnd && *pCursor && (*pCursor == '\r' || *pCursor == '\n'))
	{
		++pCursor;
	}

	return pCursor;
}

//Bnclient.0x6FF05B60 (#5)
char* BNGatewayAccess::FindSection(char* buffer, char* szSection)
{
	const size_t nBufferLength = strlen(buffer);
	const size_t nSectionLength = strlen(szSection);

	char* p = buffer;
	if (!*buffer)
	{
		return nullptr;
	}

	while (true)
	{
		while (*p && *p != '[')
		{
			++p;
		}

		D2_ASSERT(*p != 0);

		if (!_strnicmp(p + 1, szSection, nSectionLength))
		{
			char* pEnd = &buffer[nBufferLength];
			return SkipEOL(SkipToEOL(&p[nSectionLength + 2], pEnd), pEnd);
		}

		p += nSectionLength;
		if (!*p)
		{
			return nullptr;
		}
	}
}

//Bnclient.0x6FF05C30 (#4)
char* BNGatewayAccess::FindKey(char* buffer, char* szKey)
{
	const size_t nBufferLength = strlen(buffer);
	const size_t nKeyLength = strlen(szKey);

	char* p = buffer;
	if (!*buffer)
	{
		return nullptr;
	}

	while (*p != ']')
	{
		if (!_strnicmp(p, szKey, nKeyLength))
		{
			return &p[nKeyLength + 1];
		}

		char* pEnd = &buffer[nBufferLength];
		p = SkipEOL(SkipToEOL(p, pEnd), pEnd);
		if (!*p)
		{
			return nullptr;
		}
	}

	return nullptr;
}

//Bnclient.0x6FF05CD0 (#21)
void __stdcall BNGatewayAccess::UpdateGatewaysFromIni(char* szIni)
{
	char* pIniEnd = &szIni[strlen(szIni)];

	char* versHdr = FindSection(szIni, (char*)"Server List Version");
	D2_ASSERT(versHdr);

	char* vers = FindKey(versHdr, (char*)"VER");
	D2_ASSERT(vers);

	char* pEnd;
	const uint32_t nVersion = strtoul(vers, &pEnd, 10);
	if (nVersion <= regionListVersion)
	{
		return;
	}

	BNLOG_Printf("Parsing new gateway list (version %d)", nVersion);

	int nTimeZoneBias;
	if (regionList)
	{
		nTimeZoneBias = 60 * GMT(m_nCurrentGateway);
	}
	else
	{
		nTimeZoneBias = GetSystemTimeZone();
	}

	m_bDirty = FALSE;
	SaveAndUnload();
	m_bOverride = FALSE;
	m_bDirty = TRUE;
	regionListVersion = nVersion;

	int bufferlength = 2 * strlen(szIni);
	char* buffer = (char*)SMemAlloc(bufferlength, __FILE__, __LINE__, 0);
	sprintf(buffer, "%d", nVersion);

	char* curr = &buffer[strlen(buffer) + 1];
	*curr++ = '0';
	*curr++ = '0';
	*curr++ = '\0';

	char* szServerGateways = FindSection(szIni, (char*)"Server Gateways");
	for (int nGateway = 1; ; ++nGateway)
	{
		char szKey[16];
		sprintf(szKey, "%d", nGateway);

		char* szDns = FindKey(szServerGateways, szKey);
		if (!szDns)
		{
			break;
		}

		const int nDnsLength = SkipToEOL(szDns, pIniEnd) - szDns;
		SStrCopy(curr, szDns, nDnsLength + 1);

		char* szGatewaySection = FindSection(szIni, curr);
		if (!szGatewaySection)
		{
			continue;
		}

		char* pOutput = &curr[nDnsLength + 1];
		if (char* szZone = FindKey(szGatewaySection, (char*)"ZONE"))
		{
			const int nZoneLength = SkipToEOL(szZone, pIniEnd) - szZone;
			SStrCopy(pOutput, szZone, nZoneLength + 1);
			pOutput += nZoneLength + 1;
		}
		else
		{
			SStrCopy(pOutput, "0", 2);
			pOutput += 2;
		}

		int nNameLength;
		if (char* szName = FindKey(szGatewaySection, (char*)"ENU"))
		{
			nNameLength = SkipToEOL(szName, pIniEnd) - szName;
			SStrCopy(pOutput, szName, nNameLength + 1);
		}
		else
		{
			nNameLength = strlen(curr);
			SStrCopy(pOutput, curr, nNameLength + 1);
		}

		curr = &pOutput[nNameLength + 1];
	}

	*curr++ = '\0';

	D2_ASSERT(curr - buffer < bufferlength);

	bufferlength = curr - buffer;
	D2_ASSERT(buffer[bufferlength-1] == 0 && buffer[bufferlength-2] == 0);

	regionList = buffer;
	regionListSize = bufferlength;
	PickClosestZone(nTimeZoneBias);
	SaveAndUnload();
	Load();
}

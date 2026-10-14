#pragma once

#include <Windows.h>

#include <cstdint>

#define BASE_REGIONLIST_VERSION 1000
#define ENTRIES_PER_GATEWAY 3

// The gateway list (regionList) is a list of null terminated strings, terminated by an empty string:
// - the version of the list
// - the index of the currently selected gateway (two digits, 1-based)
// - ENTRIES_PER_GATEWAY strings per gateway: DNS, GMT offset (in hours), name
#pragma pack(push, 1)
class BNCLIENT_DLL_DECL BNGatewayAccess
{
public:
	char m_szEmpty[4];					//0x00 Returned when a gateway can't be found
	BOOL m_bDirty;						//0x04
	int m_nNumGateways;					//0x08
	int m_nCurrentGateway;				//0x0C
	char* regionList;					//0x10
	int regionListSize;					//0x14
	uint32_t regionListVersion;			//0x18
	BOOL m_bOverride;					//0x1C
	char* m_pRealmsList;				//0x20 Content of Data\Global\Realms.bin

	BNGatewayAccess& operator=(const BNGatewayAccess& other);

	int __stdcall NumGateways();
	int __stdcall CurGateway();
	void __stdcall Load();
	void __stdcall SaveAndUnload();
	char* __stdcall DNS(int nGateway);
	int __stdcall GMT(int nGateway);
	char* __stdcall Name(int nGateway);
	char* __stdcall Realm(int nGateway);
	void __stdcall SetCurGateway(int nGateway);
	void __stdcall UpdateGatewaysFromIni(char* szIni);

private:
	int GetSystemTimeZone();
	void PickClosestZone(int nTimeZoneBias);
	char* Nth(int nGateway);
	void GetGatewayList(const char* szRegistryValue);
	void GetBattlenetGatewayList();
	void GetBattlenetRealmsList();
	void WriteDefaultGatewayList();
	char* SkipToEOL(char* pCursor, char* pEnd);
	char* SkipEOL(char* pCursor, char* pEnd);
	char* FindSection(char* buffer, char* szSection);
	char* FindKey(char* buffer, char* szKey);
};
#pragma pack(pop)

extern BNGatewayAccess gtBnGatewayAccess;

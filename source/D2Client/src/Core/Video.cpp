#include "Core/Video.h"

#include <D2WinArchive.h>
#include <D2WinMain.h>
#include <D2WinPalette.h>
#include <D2StrTable.h>
#include <Window.h>

#include "Core/WinMain.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Draw/DLightMap.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "UI/Hireables.h"
#include "UI/UI.h"


//D2Client.0x6FB742B8
D2VideoInfoStrc gaVideoInfos[] =
{
	{ VIDEO_PROMO,          "d2_promo.bik",     FALSE, FALSE },
	{ VIDEO_INTRO,          "d2intro%s.bik",    TRUE,  TRUE },
	{ VIDEO_ACT2_START,     "ACT02START%s.BIK", TRUE,  TRUE },
	{ VIDEO_ACT3_START,     "ACT03START%s.BIK", TRUE,  TRUE },
	{ VIDEO_ACT4_START,     "ACT04START%s.BIK", TRUE,  TRUE },
	{ VIDEO_ACT4_END,       "ACT04END%s.BIK",   TRUE,  TRUE },
	{ VIDEO_EXPANSION_INTRO,"D2X_INTRO_%s.BIK", TRUE,  TRUE },
	{ VIDEO_EXPANSION_END,  "D2X_OUT_%s.BIK",   TRUE,  TRUE },
};

//D2Client.0x6FB74318
int32_t gnNumVideos = ARRAY_SIZE(gaVideoInfos);

//D2Client.0x6FB9A820
uint8_t gbVideoReplayedFromQuestLog;
//D2Client.0x6FB9A821
uint8_t gbVideoPlaying;
//D2Client.0x6FB9A822
uint8_t gbHighQualityVideo;
//D2Client.0x6FB9A823
uint8_t gbInVideoSequence;
//D2Client.0x6FB9A824
uint8_t gbChainExpansionIntro;


//D2Client.0x6FAA1510
void __fastcall VIDEO_UpdateAuxBattleNetRegistry(int32_t nVideoId)
{
	const int32_t nId = gaVideoInfos[nVideoId].nId;

	int32_t nIp0 = 0;
	int32_t nIp1 = 0;
	int32_t nIp2 = 0;
	uint32_t nIp3 = 0x22;
	char szAddress[100] = {};

	uint8_t nCurrentProgress = 0;
	if (!SRegLoadString("Diablo II", "Aux Battle.net", 0, szAddress, sizeof(szAddress)))
	{
		nCurrentProgress = 0x22;
	}
	else
	{
		sscanf(szAddress, "%d.%d.%d.%d", &nIp0, &nIp1, &nIp2, &nIp3);

		if (nIp3 & 1)
		{
			nCurrentProgress = 7;
		}
		else if ((char)nIp3 < 0)
		{
			nCurrentProgress = 6;
		}
		else if (nIp3 & 0x10)
		{
			nCurrentProgress = 5;
		}
		else if (nIp3 & 8)
		{
			nCurrentProgress = 4;
		}
		else if (nIp3 & 0x40)
		{
			nCurrentProgress = 3;
		}
		else
		{
			nCurrentProgress = ((nIp3 & 4) != 0) + 1;
		}
	}

	uint8_t nNewProgress = 0;
	switch (nId)
	{
	case VIDEO_ACT2_START:
		nNewProgress = 2;
		break;
	case VIDEO_ACT3_START:
		nNewProgress = 3;
		break;
	case VIDEO_ACT4_START:
		nNewProgress = 4;
		break;
	case VIDEO_ACT4_END:
	case VIDEO_EXPANSION_INTRO:
		nNewProgress = 5;
		break;
	case VIDEO_EXPANSION_END:
		nNewProgress = 7;
		break;
	default:
		nNewProgress = 1;
		break;
	}

	if (nCurrentProgress < nNewProgress)
	{
		switch (nNewProgress)
		{
		case 2:
			nIp3 = 0x26;
			break;
		case 3:
			nIp3 = 0x62;
			break;
		case 4:
			nIp3 = 0x2A;
			break;
		case 5:
			nIp3 = 0xB2;
			break;
		case 7:
			nIp3 = 0x23;
			break;
		default:
			nIp3 = 0x22;
			break;
		}

		sprintf(szAddress, "%d.%d.%d.%d", 216, 148, 246, nIp3);
		SRegSaveString("Diablo II", "Aux Battle.net", 0, szAddress);
	}
}

//D2Client.0x6FAA1680 (inlined)
static void VIDEO_GetLocalizedPath(char* szPath, const char* szFileName)
{
	char szLanguage[4] = {};
	D2LANG_10006(szLanguage, 0);
	sprintf(szPath, "%s\\video\\%s\\%s", "DATA\\LOCAL", szLanguage, szFileName);

	HSFILE hFile = nullptr;
	if (SFileOpenFileEx(0, szPath, 0, (int)&hFile))
	{
		SFileCloseFile(hFile);
		return;
	}

	// Fallback to another language
	sprintf(szPath, "%s\\video\\%s\\%s", "DATA\\LOCAL", STRTABLE_GetLanguage() != LANGUAGE_ENGLISH ? "ENG" : "CHI", szFileName);
	if (SFileOpenFileEx(0, szPath, 0, (int)&hFile))
	{
		SFileCloseFile(hFile);
	}
}

//D2Client.0x6FAA1680 (inlined)
static void VIDEO_GetPath(char* szPath, const D2VideoInfoStrc* pVideoInfo, const char* szFileName)
{
	if (pVideoInfo->bLocalized)
	{
		VIDEO_GetLocalizedPath(szPath, szFileName);
	}
	else
	{
		sprintf(szPath, "%s\\video\\%s", "DATA\\GLOBAL", szFileName);
	}
}

//D2Client.0x6FAA1680
void __fastcall VIDEO_Play(int32_t nVideoId)
{
	D2_ASSERT(nVideoId < gnNumVideos);

	gbInVideoSequence = TRUE;
	VIDEO_UpdateAuxBattleNetRegistry(nVideoId);

	if (gbVideoPlaying)
	{
		return;
	}

	if (nVideoId >= gnNumVideos)
	{
		CLIENT_SendSimpleMessage(0x48);
		gbInVideoSequence = FALSE;
		return;
	}

	BOOL bVideoPlayed = FALSE;
	BOOL bArchivesLoaded = FALSE;
	D2GameResolutionMode nResolution = D2GAMERES_640x480;
	char szFileName[260] = {};
	char szPath[260] = {};

	if (!gaVideoInfos[nVideoId].bHasResolutionSuffix)
	{
		strcpy(szFileName, gaVideoInfos[nVideoId].szFileName);
	}
	else if (gbHighQualityVideo)
	{
		sprintf(szFileName, gaVideoInfos[nVideoId].szFileName, "640x292");
	}
	else
	{
		nResolution = (D2GameResolutionMode)2;
		sprintf(szFileName, gaVideoInfos[nVideoId].szFileName, "640x146");
	}

	FOG_Trace("video sound prep start %d\n", GetTickCount());
	sub_6FB54CB0();
	sub_6FB56D40();
	FOG_Trace("video sound prep end %d\n", GetTickCount());

	ARCHIVE_UnloadExpansionArchives();

	BOOL bExpansion = FALSE;
	if (nVideoId == VIDEO_EXPANSION_END)
	{
		bExpansion = TRUE;

		char szGameDllPath[260] = {};
		FOG_GetInstallPath(szGameDllPath, sizeof(szGameDllPath));
		strcat(szGameDllPath, "d2game.dll");

		HANDLE hFile = CreateFileA(szGameDllPath, 0, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			sub_6FAAB350(0);
			sub_6FAAB350(0);
			gbVideoReplayedFromQuestLog = FALSE;
			sub_6FAAB230();
			sub_6FAAC2F0();
			goto RELOAD_ARCHIVES;
		}

		CloseHandle(hFile);
	}
	else if (nVideoId == VIDEO_EXPANSION_INTRO)
	{
		bExpansion = TRUE;
	}

	sub_6FADCF00(bExpansion);
	FOG_Trace("switch to video cd %d\n", GetTickCount());

	if (ARCHIVE_LoadVideoArchives(bExpansion ? sub_6FADC390 : sub_6FADCBD0, nullptr, bExpansion))
	{
		bArchivesLoaded = TRUE;

		VIDEO_GetPath(szPath, &gaVideoInfos[nVideoId], szFileName);

		gbVideoPlaying = TRUE;
		sub_6FAA62A0();
		sub_6FB23260(0x12, 0, 0);

		// TODO: D2Win_10003 returns a BOOL in the original game, the cutscene is only played when it succeeds.
		D2Win_10003();
		WINDOW_OpenSmackCutscene(szPath, nResolution, gbVideoReplayedFromQuestLog ? nullptr : sub_6FAAD3B0);
		bVideoPlayed = TRUE;

		if (nVideoId != VIDEO_ACT4_END || !gbChainExpansionIntro)
		{
			D2Win_10004(D2GFX_GetResolutionMode());
			sub_6FB23260(0x12, 1, 0);
			gbVideoPlaying = FALSE;
		}
	}

	if (gbChainExpansionIntro)
	{
		if (bArchivesLoaded)
		{
			ARCHIVE_UnloadExpansionArchives();
		}

		if (bVideoPlayed)
		{
			D2Win_10004(D2GFX_GetResolutionMode());
		}

		sub_6FADCF00(TRUE);
		if (ARCHIVE_LoadVideoArchives(sub_6FADC390, nullptr, TRUE))
		{
			nVideoId = VIDEO_EXPANSION_INTRO;

			if (gbHighQualityVideo)
			{
				sprintf(szFileName, gaVideoInfos[VIDEO_EXPANSION_INTRO].szFileName, "640x292");
			}
			else
			{
				nResolution = (D2GameResolutionMode)2;
				sprintf(szFileName, gaVideoInfos[VIDEO_EXPANSION_INTRO].szFileName, "640x146");
			}

			VIDEO_GetPath(szPath, &gaVideoInfos[VIDEO_EXPANSION_INTRO], szFileName);

			// TODO: D2Win_10003 returns a BOOL in the original game, the cutscene is only played when it succeeds.
			D2Win_10003();
			WINDOW_OpenSmackCutscene(szPath, nResolution, sub_6FAAD3B0);
			VIDEO_UpdateAuxBattleNetRegistry(VIDEO_EXPANSION_INTRO);
		}

		D2Win_10004(D2GFX_GetResolutionMode());
		sub_6FB23260(0x12, 1, 0);
		gbVideoPlaying = FALSE;
		gbChainExpansionIntro = FALSE;
		D2Win_10177(4);
	}

	CLIENT_SendSimpleMessage(0x48);

	if (gbVideoReplayedFromQuestLog)
	{
		gbVideoReplayedFromQuestLog = FALSE;
		sub_6FAAC2F0();
	}
	else if (nVideoId == VIDEO_EXPANSION_END)
	{
		sub_6FAAB350(0);
		gbVideoReplayedFromQuestLog = FALSE;
		sub_6FAAB230();
		sub_6FAAC2F0();
	}

RELOAD_ARCHIVES:
	ARCHIVE_UnloadExpansionArchives();
	ARCHIVE_LoadExpansionArchives(sub_6FADC390, sub_6FADC470, nullptr, gpConfig);
	gbInVideoSequence = FALSE;
	FOG_Trace("switch to play cd %d\n", GetTickCount());
}

//D2Client.0x6FAA1CA0
void __fastcall VIDEO_SetReplayedFromQuestLog()
{
	gbVideoReplayedFromQuestLog = TRUE;
}

//D2Client.0x6FAA1CB0
void __fastcall VIDEO_Initialize()
{
	gbVideoReplayedFromQuestLog = FALSE;
	gbHighQualityVideo = FOG_10191() == 0;
	gbChainExpansionIntro = FALSE;
	gbInVideoSequence = FALSE;
}

//D2Client.0x6FAA1CE0
void __fastcall VIDEO_SetChainExpansionIntro()
{
	gbChainExpansionIntro = TRUE;
}

//D2Client.0x6FAA1CF0
uint8_t __fastcall VIDEO_IsInVideoSequence()
{
	return gbInVideoSequence;
}

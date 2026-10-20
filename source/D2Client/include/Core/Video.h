#pragma once

#include <D2Client.h>


enum D2C_VideoIds
{
	VIDEO_PROMO = 0,
	VIDEO_INTRO = 1,
	VIDEO_ACT2_START = 2,
	VIDEO_ACT3_START = 3,
	VIDEO_ACT4_START = 4,
	VIDEO_ACT4_END = 5,
	VIDEO_EXPANSION_INTRO = 6,
	VIDEO_EXPANSION_END = 7,
};

#pragma pack(push, 1)
struct D2VideoInfoStrc
{
	int32_t nId;							//0x00
	const char* szFileName;					//0x04
	uint8_t bHasResolutionSuffix;			//0x08 File name contains a %s for the video resolution
	uint8_t bLocalized;						//0x09
	uint16_t pad0x0A;						//0x0A
};
#pragma pack(pop)


//D2Client.0x6FB742B8
extern D2VideoInfoStrc gaVideoInfos[];
//D2Client.0x6FB74318
extern int32_t gnNumVideos;
//D2Client.0x6FB9A820
extern uint8_t gbVideoReplayedFromQuestLog;
//D2Client.0x6FB9A821
extern uint8_t gbVideoPlaying;
//D2Client.0x6FB9A822
extern uint8_t gbHighQualityVideo;
//D2Client.0x6FB9A823
extern uint8_t gbInVideoSequence;
//D2Client.0x6FB9A824
extern uint8_t gbChainExpansionIntro;


//D2Client.0x6FAA1510
void __fastcall VIDEO_UpdateAuxBattleNetRegistry(int32_t nVideoId);
//D2Client.0x6FAA1680
void __fastcall VIDEO_Play(int32_t nVideoId);
//D2Client.0x6FAA1CA0
void __fastcall VIDEO_SetReplayedFromQuestLog();
//D2Client.0x6FAA1CB0
void __fastcall VIDEO_Initialize();
//D2Client.0x6FAA1CE0
void __fastcall VIDEO_SetChainExpansionIntro();
//D2Client.0x6FAA1CF0
uint8_t __fastcall VIDEO_IsInVideoSequence();

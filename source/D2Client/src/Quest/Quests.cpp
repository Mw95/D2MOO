#include "Quest/Quests.h"

#include "Core/Video.h"
#include "Game/Wall2.h"
#include "Quest/QuestsFX.h"

//D2Client.0x6FBAF944
uint32_t sgbInit;

//D2Client.0x6FAB8EE0
uint32_t __stdcall D2Client_10001(int32_t a1)
{
	return sgbInit;
}

//D2Client.0x6FAB8EF0
uint8_t __stdcall D2Client_10002(int32_t a1, int32_t a2)
{
	D2_ASSERT(sgbInit);
	if (0x24 < a2)
	{
		FOG_DisplayAssert("idx < QUEST_NUMCLASS", __FILE__, __LINE__);
		exit(-1);
	}
	return *(uint8_t*)((int)&dword_6FBAF91C + a2);
}

//D2Client.0x6FAB8F50
void __fastcall sub_6FAB8F50(int a1)
{
	VIDEO_Play((uint32_t) * (uint8_t*)(a1 + 1));
}

//D2Client.0x6FAB8F60
void __fastcall sub_6FAB8F60(int a1)
{
	sub_6FAB9800((uint32_t) * (uint8_t*)(a1 + 1));
}

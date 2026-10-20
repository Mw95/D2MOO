#include "Unit/Missile.h"
#include "Quest/Quests.h"

#include "Core/WinMain.h"
#include "Draw/DFloor.h"
#include "Draw/DLightMap.h"
#include "Engine/Gfx.h"
#include "Engine/Particle.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/PalShift.h"
#include "Game/RosterPets.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "Skills/Skills.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "Unit/CUnit.h"
#include "Unit/CUnitEvent.h"
#include "Unit/MonUnique.h"
#include "Unit/Monster.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB70160
uint8_t byte_6FB70160[256] = {0x1E, 0, 0, 0, 0x1D, 0, 0, 0, 0x1D, 0, 0, 0, 0x1C, 0, 0, 0, 0x1B, 0, 0, 0, 0x1A, 0, 0, 0, 0x18, 0, 0, 0, 0x17, 0, 0, 0, 0x15, 0, 0, 0, 0x13, 0, 0, 0, 0x10, 0, 0, 0, 0xE, 0, 0, 0, 0xB, 0, 0, 0, 8, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xF2, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xED, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xE9, 0xFF, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 0xFF, 0xE5, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE2, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xE5, 0xFF, 0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xE9, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xED, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xF2, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 0, 0xB, 0, 0, 0, 0xE, 0, 0, 0, 0x10, 0, 0, 0, 0x13, 0, 0, 0, 0x15, 0, 0, 0, 0x17, 0, 0, 0, 0x18, 0, 0, 0, 0x1A, 0, 0, 0, 0x1B, 0, 0, 0, 0x1C, 0, 0, 0, 0x1D, 0, 0, 0, 0x1D};
//D2Client.0x6FB70260
uint8_t byte_6FB70260[260] = {0, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 0, 0xB, 0, 0, 0, 0xE, 0, 0, 0, 0x10, 0, 0, 0, 0x13, 0, 0, 0, 0x15, 0, 0, 0, 0x17, 0, 0, 0, 0x18, 0, 0, 0, 0x1A, 0, 0, 0, 0x1B, 0, 0, 0, 0x1C, 0, 0, 0, 0x1D, 0, 0, 0, 0x1D, 0, 0, 0, 0x1E, 0, 0, 0, 0x1D, 0, 0, 0, 0x1D, 0, 0, 0, 0x1C, 0, 0, 0, 0x1B, 0, 0, 0, 0x1A, 0, 0, 0, 0x18, 0, 0, 0, 0x17, 0, 0, 0, 0x15, 0, 0, 0, 0x13, 0, 0, 0, 0x10, 0, 0, 0, 0xE, 0, 0, 0, 0xB, 0, 0, 0, 8, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xF2, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xED, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xE9, 0xFF, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 0xFF, 0xE5, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE2, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xE5, 0xFF, 0xFF, 0xFF, 0xE6, 0xFF, 0xFF, 0xFF, 0xE8, 0xFF, 0xFF, 0xFF, 0xE9, 0xFF, 0xFF, 0xFF, 0xEB, 0xFF, 0xFF, 0xFF, 0xED, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xF2, 0xFF, 0xFF, 0xFF, 0xF5, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0x40};
//D2Client.0x6FB70364
uint32_t dword_6FB70364 = 0xFFFFFFFF;
//D2Client.0x6FB70374
uint32_t dword_6FB70374;
//D2Client.0x6FB70388
uint32_t dword_6FB70388;
//D2Client.0x6FB7038C
uint32_t dword_6FB7038C[15] = {1, 2, 2, 2, 2, 2, 1, 0, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFF};
//D2Client.0x6FB703C8
uint32_t dword_6FB703C8 = 2;
//D2Client.0x6FB703CC
uint32_t dword_6FB703CC[15] = {2, 2, 1, 0, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFF, 0, 1, 2, 2};
//D2Client.0x6FB70408
uint32_t dword_6FB70408 = 0x10;
//D2Client.0x6FB70428
uint32_t dword_6FB70428;
//D2Client.0x6FB7044C
uint8_t byte_6FB7044C[32] = {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB7046C
uint8_t byte_6FB7046C[32] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 1};
//D2Client.0x6FB7048C
uint8_t byte_6FB7048C[4] = {4};
//D2Client.0x6FB70490
uint8_t byte_6FB70490[56] = {0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 5};
//D2Client.0x6FB704C8
uint32_t dword_6FB704C8 = 2;
//D2Client.0x6FB70510
uint32_t dword_6FB70510 = 0xFFFFFFFE;
//D2Client.0x6FB70558
uint32_t dword_6FB70558;
//D2Client.0x6FB7056C
uint32_t dword_6FB7056C;
//D2Client.0x6FB70580
uint32_t dword_6FB70580[8] = {0, 2, 2, 2, 0, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE};
//D2Client.0x6FB705A0
uint32_t dword_6FB705A0[8] = {2, 2, 0, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0, 2};
//D2Client.0x6FB705C0
uint32_t dword_6FB705C0 = 0x1E;
//D2Client.0x6FB706C0
uint32_t dword_6FB706C0;
//D2Client.0x6FB707C0
uint32_t dword_6FB707C0 = 0x1E;
//D2Client.0x6FB708C0
uint32_t dword_6FB708C0;
//D2Client.0x6FB709C0
uint32_t dword_6FB709C0[18] = {2, 0xFFFFFFFE, 0, 0, 0xFFFFFFFD, 0, 3, 0xFFFFFFFF, 1, 0xFFFFFFFF, 2, 0xFFFFFFFC, 0xFFFFFFFD, 0xFFFFFFFF, 0, 1, 3, 4};
//D2Client.0x6FB70A08
uint32_t dword_6FB70A08[20] = {0xFFFFFFFE, 0xFFFFFFFE, 2, 5, 3, 3, 3, 2, 1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFC, 0xFFFFFFFD, 0xFFFFFFFD, 0xFFFFFFFE, 3, 0xFFFFFFFE};
//D2Client.0x6FB70A58
uint8_t byte_6FB70A58 = 4;
//D2Client.0x6FB70AA8
uint32_t dword_6FB70AA8 = 0x12C;
//D2Client.0x6FB70AAC
uint8_t byte_6FB70AAC[4] = {0x19};
//D2Client.0x6FB70AB0
uint8_t byte_6FB70AB0[4] = {1};
//D2Client.0x6FB70AE4
uint32_t tbl_6FB70AE4[3] = {0, 0x64};
//D2Client.0x6FB70AF0
uint32_t dword_6FB70AF0 = 0x15E;
//D2Client.0x6FB70AF4
uint32_t dword_6FB70AF4 = 0xA;
//D2Client.0x6FB70AF8
uint8_t byte_6FB70AF8[4] = {1};
//D2Client.0x6FB70B20
uint32_t tbl_6FB70B20[3] = {0, 0x64};
//D2Client.0x6FB70B2C
uint32_t dword_6FB70B2C = 0x15E;
//D2Client.0x6FB70B30
uint32_t dword_6FB70B30 = 3;
//D2Client.0x6FB70B34
uint8_t byte_6FB70B34[4] = {5};
//D2Client.0x6FB70B5C
uint32_t tbl_6FB70B5C[3] = {0, 0x64, 5};
//D2Client.0x6FB70B68
uint32_t dword_6FB70B68 = 0x1A4;
//D2Client.0x6FB70B6C
uint32_t dword_6FB70B6C = 0x40;
//D2Client.0x6FB70B70
uint32_t dword_6FB70B70;
//D2Client.0x6FB70B98
uint32_t tbl_6FB70B98[4] = {0, 0x40, 0, 5};
//D2Client.0x6FB91208
uint32_t tbl_6FB91208[3] = {0x45, 0x68, 0x69};
//D2Client.0x6FB91214
uint32_t dword_6FB91214 = 1;
//D2Client.0x6FB91218
uint8_t byte_6FB91218[4];
//D2Client.0x6FB9121C
uint8_t byte_6FB9121C[68] = {0, 0, 0, 0, 0xB0, 0x95, 0xB3, 0x6F, 0x84, 0, 0, 0, 0x10, 0x95, 0xB3, 0x6F, 4, 1, 0, 0, 0x50, 0x96, 0xB3, 0x6F, 0x84, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x95, 0xB3, 0x6F, 4, 1, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xF0, 0x96, 0xB3, 0x6F, 0x40, 0, 0, 0, 0x50, 0x96, 0xB3, 0x6F, 0x85, 1};
//D2Client.0x6FB91260
uint8_t byte_6FB91260[364] = {0, 0, 0, 0, 0x80, 0xD8, 0xB3, 0x6F, 0x60, 2, 0xB3, 0x6F, 0xE0, 3, 0xB3, 0x6F, 0x90, 6, 0xB3, 0x6F, 0xF0, 6, 0xB3, 0x6F, 0x20, 8, 0xB3, 0x6F, 0xD0, 0xA, 0xB3, 0x6F, 0x20, 0xD, 0xB3, 0x6F, 0x80, 0xE, 0xB3, 0x6F, 0x90, 0x13, 0xB3, 0x6F, 0x40, 0x15, 0xB3, 0x6F, 0x70, 0x15, 0xB3, 0x6F, 0x90, 0x19, 0xB3, 0x6F, 0xA0, 0x1B, 0xB3, 0x6F, 0xD0, 0x1D, 0xB3, 0x6F, 0x50, 0x21, 0xB3, 0x6F, 0x10, 0x23, 0xB3, 0x6F, 0x70, 0x24, 0xB3, 0x6F, 0x10, 0x26, 0xB3, 0x6F, 0x50, 0x27, 0xB3, 0x6F, 0x70, 0x28, 0xB3, 0x6F, 0xC0, 0x2A, 0xB3, 0x6F, 0xB0, 0x2C, 0xB3, 0x6F, 0xE0, 0x2C, 0xB3, 0x6F, 0x80, 0x31, 0xB3, 0x6F, 0x40, 0x34, 0xB3, 0x6F, 0xE0, 0x37, 0xB3, 0x6F, 0xB0, 0x39, 0xB3, 0x6F, 0, 0x43, 0xB3, 0x6F, 0, 0x45, 0xB3, 0x6F, 0xE0, 0xA3, 0xB3, 0x6F, 0x60, 0xA9, 0xB3, 0x6F, 0xA0, 0xAA, 0xB3, 0x6F, 0x40, 0xAE, 0xB3, 0x6F, 0x80, 0xB2, 0xB3, 0x6F, 0xB0, 0xB4, 0xB3, 0x6F, 0xC0, 0x9A, 0xB3, 0x6F, 0xD0, 0x9E, 0xB3, 0x6F, 0, 0x9D, 0xB3, 0x6F, 0x60, 0x9B, 0xB3, 0x6F, 0x10, 0x9B, 0xB3, 0x6F, 0x30, 0xA1, 0xB3, 0x6F, 0x60, 0x47, 0xB3, 0x6F, 0xB0, 0x47, 0xB3, 0x6F, 0xF0, 0x48, 0xB3, 0x6F, 0x60, 0x49, 0xB3, 0x6F, 0x30, 0x4C, 0xB3, 0x6F, 0xC0, 0x4C, 0xB3, 0x6F, 0xF0, 0x4F, 0xB3, 0x6F, 0x10, 0x51, 0xB3, 0x6F, 0xC0, 0x53, 0xB3, 0x6F, 0x70, 0x56, 0xB3, 0x6F, 0x80, 0x57, 0xB3, 0x6F, 0x10, 0xCE, 0xB3, 0x6F, 0, 0xD2, 0xB3, 0x6F, 0x40, 0x58, 0xB3, 0x6F, 0xC0, 0x59, 0xB3, 0x6F, 0x40, 0x5B, 0xB3, 0x6F, 0x50, 0xCA, 0xB3, 0x6F, 0x80, 0xD3, 0xB3, 0x6F, 0xD0, 0xB7, 0xB3, 0x6F, 0xF0, 0xBA, 0xB3, 0x6F, 0xE0, 0xBF, 0xB3, 0x6F, 0x80, 0xC0, 0xB3, 0x6F, 0x30, 0xC6, 0xB3, 0x6F, 0xA0, 0xC8, 0xB3, 0x6F, 0x60, 0x16, 0xB3, 0x6F, 0, 0x4B, 0xB3, 0x6F};
//D2Client.0x6FB913CC
int32_t dword_6FB913CC = 91;
//D2Client.0x6FB913D0
uint8_t byte_6FB913D0[324] = {0, 0, 0, 0, 0x50, 0x62, 0xB3, 0x6F, 0x50, 0x63, 0xB3, 0x6F, 0xB0, 0x63, 0xB3, 0x6F, 0x80, 0x7E, 0xB3, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x65, 0xB3, 0x6F, 0xD0, 0x66, 0xB3, 0x6F, 0, 0, 0, 0, 0x40, 0x67, 0xB3, 0x6F, 0x90, 0x68, 0xB3, 0x6F, 0x50, 0x6B, 0xB3, 0x6F, 0, 0, 0, 0, 0xF0, 0x6D, 0xB3, 0x6F, 0, 0, 0, 0, 0x60, 0x70, 0xB3, 0x6F, 0x30, 0x73, 0xB3, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x74, 0xB3, 0x6F, 0x60, 0x75, 0xB3, 0x6F, 0, 0x78, 0xB3, 0x6F, 0, 0, 0, 0, 0x20, 0x7B, 0xB3, 0x6F, 0xB0, 0x7B, 0xB3, 0x6F, 0x70, 0x7D, 0xB3, 0x6F, 0x80, 0x98, 0xB3, 0x6F, 0x90, 0x7F, 0xB3, 0x6F, 0x60, 0x81, 0xB3, 0x6F, 0x60, 0x83, 0xB3, 0x6F, 0, 0, 0, 0, 0x80, 0x83, 0xB3, 0x6F, 0xD0, 0xA7, 0xB3, 0x6F, 0xE0, 0xAC, 0xB3, 0x6F, 0xB0, 0xB3, 0xB3, 0x6F, 0x70, 0x9A, 0xB3, 0x6F, 0x20, 0xB7, 0xB3, 0x6F, 0x20, 0x9D, 0xB3, 0x6F, 0x90, 0x9D, 0xB3, 0x6F, 0x50, 0x84, 0xB3, 0x6F, 0, 0, 0, 0, 0xC0, 0x85, 0xB3, 0x6F, 0x40, 0x87, 0xB3, 0x6F, 0x90, 0xCA, 0xB3, 0x6F, 0, 0, 0, 0, 0x40, 0x89, 0xB3, 0x6F, 0xF0, 0x8B, 0xB3, 0x6F, 0x20, 0x8D, 0xB3, 0x6F, 0, 0x8F, 0xB3, 0x6F, 0x50, 0x90, 0xB3, 0x6F, 0x50, 0x91, 0xB3, 0x6F, 0x30, 0x92, 0xB3, 0x6F, 0xF0, 0x92, 0xB3, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x94, 0xB3, 0x6F, 0xD0, 0x94, 0xB3, 0x6F, 0x40, 0xD4, 0xB3, 0x6F, 0x60, 0xD6, 0xB3, 0x6F, 0x50, 0x61, 0xB3, 0x6F};
//D2Client.0x6FB91514
int32_t dword_6FB91514 = 81;
//D2Client.0x6FBBC20C
uint32_t dword_6FBBC20C;

//D2Client.0x6FB2FF20
void __fastcall sub_6FB2FF20(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5, int a6)
{
	D2SeedStrc* pDVar1;
	uint64_t DVar2;
	D2ActiveRoomStrc* pDVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t* puVar9;
	int iVar10;
	int32_t DStack_88;
	int iStack_84;
	uint32_t uStack_80;
	D2ActiveRoomStrc** ppDStack_7c;
	int iStack_78;
	int local_74;
	int iStack_70;
	D2CoordStrc DStack_6c;
	D2CoordStrc DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	local_74 = a2;
	pDVar3 = UNITS_GetRoom(pUnit);
	if ((pDVar3 != nullptr) && (pDVar1 = &pUnit->pSeed, pDVar1 != nullptr))
	{
		puVar9 = &uStack_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		uStack_5c = 1;
		if (a5 != 0)
		{
			uStack_5c = 0x8001;
		}
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			iStack_84 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_84 = 0;
		}
		else
		{
			iStack_84 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DStack_88 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_88 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_88 + 2)) = 0;
		}
		else
		{
			DStack_88 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_78 = a4 * a4;
		iVar8 = -a4;
		iVar5 = iVar8;
		iStack_70 = iVar8;
		if (-a4 == a4 || SBORROW4(iVar8, a4) != a4 * -2 < 0)
		{
			do
			{
				iVar4 = iVar5;
				if (iVar5 <= a4)
				{
					iVar6 = iStack_84 + iVar8;
					iVar10 = (int)DStack_88 + iVar5;
					do
					{
						pDVar3 = UNITS_GetRoom(pUnit);
						if ((pDVar3 != nullptr) && (iVar5 * iVar5 + iVar8 * iVar8 <= iStack_78))
						{
							DStack_6c.nX = iVar6 + iVar8;
							DStack_6c.nY = iVar10 + iVar5;
							DStack_64.nX = iVar6;
							DStack_64.nY = iVar10;
							iVar4 = COLLISION_RayTrace(pDVar3, &DStack_64, &DStack_6c, 4);
							ppDStack_7c = (D2ActiveRoomStrc**)(uint32_t)(iVar4 == 0);
							if ((ppDStack_7c != nullptr) &&
							    (pDVar3 = UNITS_GetRoom(pUnit), pDVar3 != nullptr))
							{
								iVar4 = (pDVar3->tCoords).nSubtileX;
								if ((((iVar6 < iVar4) || ((pDVar3->tCoords).nSubtileWidth + iVar4 <= iVar6)) ||
								        (iVar4 = (pDVar3->tCoords).nSubtileY, iVar10 < iVar4)) ||
								    ((pDVar3->tCoords).nSubtileHeight + iVar4 <= iVar10))
								{
									ppDStack_7c = nullptr;
									uStack_80 = 0;
									DUNGEON_GetAdjacentRoomsListFromRoom(pDVar3, &ppDStack_7c, (int*)&uStack_80);
									uVar7 = 0;
									if (uStack_80 != 0)
									{
										do
										{
											pDVar3 = ppDStack_7c[uVar7];
											if (((pDVar3 != nullptr) &&
											        (iVar4 = (pDVar3->tCoords).nSubtileX, iVar4 <= iVar6)) &&
											    ((iVar6 < (pDVar3->tCoords).nSubtileWidth + iVar4 &&
											        ((iVar4 = (pDVar3->tCoords).nSubtileY, iVar4 <= iVar10 &&
											                                                   (iVar10 < (pDVar3->tCoords).nSubtileHeight + iVar4))))))
											{
												pDVar3 = ppDStack_7c[uVar7];
												goto LAB_6fb30147;
											}
											uVar7 = uVar7 + 1;
										} while (uVar7 < uStack_80);
									}
								}
								else
								{
								LAB_6fb30147:
									if ((pDVar3 != nullptr) &&
									    (iVar4 = DUNGEON_IsRoomInTown(pDVar3), iVar4 == 0))
									{
										if (a5 != 0)
										{
											DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
											                   (uint64_t)(pUnit->pSeed).nHighSeed);
											*(uint64_t*)pDVar1 = DVar2;
											iStack_10 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x19) + -0xc + a5;
										}
										iStack_48 = iVar6;
										iStack_44 = iVar10;
										if (a3 < 1)
										{
											uVar7 = 0;
										}
										else if ((a3 & a3 - 1U) == 0)
										{
											uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
											uVar7 = uVar7 & a3 - 1U;
										}
										else
										{
											DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
											                   (uint64_t)(pUnit->pSeed).nHighSeed);
											*(uint64_t*)pDVar1 = DVar2;
											uVar7 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)(uint32_t)a3);
										}
										uStack_4c = *(uint32_t*)(local_74 + uVar7 * 4);
										uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
										if ((int)(uVar7 % 100) < a6)
										{
											sub_6FB3E070(&uStack_5c);
										}
									}
								}
							}
						}
						iVar5 = iVar5 + 1;
						iVar10 = iVar10 + 1;
						iVar4 = iStack_70;
					} while (iVar5 <= a4);
				}
				iVar8 = iVar8 + 1;
				iVar5 = iVar4;
			} while (iVar8 <= a4);
		}
	}
}

//D2Client.0x6FB30260
void __fastcall sub_6FB30260(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;

	iVar1 = UNITS_IsAtEndOfFrameCycle(pUnit);
	if (iVar1 != 0)
	{
		sub_6FB29540((int)pUnit);
		PATH_SetVelocity(pUnit->pDynamicPath, 0, __FILE__, __LINE__);
	}
	iVar1 = UNITS_GetClientCoordX(pUnit);
	iVar2 = sub_6FAB5890();
	if ((-1 < iVar1 - iVar2) && (iVar1 - iVar2 <= gnViewWidth))
	{
		iVar1 = UNITS_GetClientCoordY(pUnit);
		iVar2 = sub_6FAB58A0();
		if ((-1 < iVar1 - iVar2) && (iVar1 - iVar2 <= gnViewHeight + 0x40))
		{
			MISSILE_SetCurrentFrame(pUnit, 0x80);
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DC50(pUnit, nullptr, 0);
}

//D2Client.0x6FB302E0
void __fastcall sub_6FB302E0(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_28;
	int iStack_10;

	iVar2 = D2Common_10234(pUnit->pDynamicPath);
	if (iVar2 != 0)
	{
		puVar3 = &uStack_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		uStack_5c = 5;
		if (0 < a3)
		{
			iStack_10 = a3;
			uStack_5c = 0x8005;
		}
		if (0 < a4)
		{
			iStack_28 = a4;
			uStack_5c = uStack_5c | 8;
		}
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uVar1 = pUnit->dwUnitType;
		pDStack_54 = pUnit;
		uStack_4c = a2;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_48 = 0;
		}
		else
		{
			iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_28 = uStack_2c * 2 + -2;
		sub_6FB3E070(&uStack_5c);
	}
}

//D2Client.0x6FB303E0
void __fastcall sub_6FB303E0(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint32_t nLevel;
	D2UnitStrc* pOwner;
	uint32_t nCalc;

	iVar2 = D2Common_10234(pUnit->pDynamicPath);
	if ((((iVar2 != 0) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x1e)))))
	{
		nLevel = MISSILE_GetLevel(pUnit);
		nCalc = *(uint32_t*)(iVar1 + 0x84);
		pOwner = sub_6FB26AD0((int)pUnit);
		iVar2 = MISSILE_EvaluateMissileFormula(pUnit, pOwner, nCalc, iVar2, nLevel);
		sub_6FB302E0(pUnit, (int)*(short*)(iVar1 + 0x1e), 0, iVar2);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB30470
void __fastcall sub_6FB30470(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, int a5)
{
	uint64_t DVar1;
	uint64_t uVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	int32_t DStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((-1 < a5) && (a5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar3 = MISSILE_GetCurrentFrame(pUnit);
		if ((iVar3 != 0) && (0 < (int)a2))
		{
			uVar5 = (pUnit->pSeed).nLowSeed;
			if ((a2 & a2 - 1) == 0)
			{
				DVar1 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar1;
				uVar5 = a2 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
			}
			else
			{
				DVar1 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar1;
				uVar5 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)a2);
			}
			if (uVar5 != 0)
			{
				return;
			}
		}
		puVar8 = &uStack_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar8 = 0;
			puVar8 = puVar8 + 1;
		}
		uStack_5c = 0x20;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		pDStack_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = a5;
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			a5 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			a5 = 0;
		}
		else
		{
			a5 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_60 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_60 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_60 + 2)) = 0;
		}
		else
		{
			DStack_60 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		if (0 < a3)
		{
			uVar5 = a4 * 2;
			do
			{
				if ((int)uVar5 < 1)
				{
					uVar6 = 0;
				}
				else
				{
					uVar6 = (pUnit->pSeed).nLowSeed;
					if ((uVar5 & uVar5 - 1) == 0)
					{
						DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar1;
						uVar6 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
					}
					else
					{
						DVar1 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar1;
						uVar6 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar5);
					}
				}
				if ((int)uVar5 < 1)
				{
					uVar7 = 0;
				}
				else
				{
					uVar7 = (pUnit->pSeed).nLowSeed;
					uVar2 = (uint64_t)(pUnit->pSeed).nHighSeed;
					if ((uVar5 & uVar5 - 1) == 0)
					{
						DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit->pSeed) = DVar1;
						uVar7 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
					}
					else
					{
						DVar1 = (uint64_t)((uint64_t)uVar7 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit->pSeed) = DVar1;
						uVar7 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar5);
					}
				}
				iVar3 = a4;
				if ((int)(uVar6 - a4) < 0)
				{
					iVar3 = -a4;
				}
				iVar4 = a4;
				if ((int)(uVar7 - a4) < 0)
				{
					iVar4 = -a4;
				}
				iStack_40 = a5 + (uVar6 - a4) + iVar3;
				iStack_3c = iVar4 + (int)DStack_60 + (uVar7 - a4);
				sub_6FB3E070(&uStack_5c);
				a3 = a3 + -1;
			} while (a3 != 0);
		}
	}
}

//D2Client.0x6FB30690
void __fastcall sub_6FB30690(D2UnitStrc* pUnit)
{
	int iVar1;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		sub_6FB30470(pUnit, *(uint32_t*)(iVar1 + 0x58), *(uint32_t*)(iVar1 + 0x5c),
		    *(uint32_t*)(iVar1 + 0x60), (int)*(short*)(iVar1 + 0x1e));
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB306F0
void __fastcall sub_6FB306F0(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	int iVar8;

	if ((((pUnit == nullptr) || (iVar5 = pUnit->dwClassId, iVar5 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar5)) ||
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar8 = pUnit->nSeqCurrentFramePrecise >> 8;
	if (iVar8 != *(uint8_t*)(iVar5 + 0x181) - 1)
	{
		bVar1 = *(uint8_t*)(iVar5 + 0x181);
		uVar7 = MISSILE_GetCurrentFrame(pUnit);
		if (uVar7 == bVar1)
		{
			iVar5 = bVar1 - 3;
			if (iVar5 < 0)
			{
				iVar5 = 0;
			}
			pUnit->nSeqCurrentFramePrecise = iVar5 << 8;
			sub_6FB3D880(pUnit);
			return;
		}
		iVar6 = MISSILE_GetCurrentFrame(pUnit);
		if (iVar6 < (int)(uint32_t) * (uint8_t*)(iVar5 + 0x181))
		{
			iVar8 = iVar8 + -2;
			if (iVar8 < 0)
			{
				iVar8 = 0;
			}
			pUnit->nSeqCurrentFramePrecise = iVar8 << 8;
		}
		sub_6FB3D880(pUnit);
		return;
	}
	uVar7 = (uint32_t) * (uint8_t*)(iVar5 + 0x182) - (uint32_t) * (uint8_t*)(iVar5 + 0x181);
	if ((int)uVar7 < 1)
	{
		pUnit->nSeqCurrentFramePrecise = iVar8 << 8;
		sub_6FB3D880(pUnit);
		return;
	}
	uVar2 = (pUnit->pSeed).nLowSeed;
	uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
	if ((uVar7 & uVar7 - 1) != 0)
	{
		DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
		(*(uint64_t*)&pUnit->pSeed) = DVar3;
		pUnit->nSeqCurrentFramePrecise =
		    ((int)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar7) + iVar8) * 0x100;
		sub_6FB3D880(pUnit);
		return;
	}
	DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
	(*(uint64_t*)&pUnit->pSeed) = DVar3;
	pUnit->nSeqCurrentFramePrecise = ((uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0))) + iVar8) * 0x100;
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB30820
void __fastcall sub_6FB30820(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	int32_t DVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	pDVar3 = sub_6FB26AD0((int)pUnit);
	iVar4 = D2Common_10234(pUnit->pDynamicPath);
	if (iVar4 == 0)
		goto LAB_6fb30ac1;
	iVar4 = pUnit->dwClassId;
	if ((((iVar4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4)) ||
	        (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4, iVar4 == 0)) ||
	    (*(short*)(iVar4 + 0x1e) < 0))
	{
	LAB_6fb30959:
		sub_6FB3DBB0(pUnit);
		return;
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		iVar5 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
	}
	else
	{
		DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	puVar10 = &uStack_5c;
	for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	uStack_5c = 0x21;
	pDStack_58 = pDVar3;
	iStack_48 = iVar5;
	DStack_44 = DVar6;
	iStack_30 = MISSILE_GetSkill(pUnit);
	uStack_2c = MISSILE_GetLevel(pUnit);
	iStack_4c = (int)*(short*)(iVar4 + 0x1e);
	iVar5 = (int)*(short*)(iVar4 + 0x1e);
	if (((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar5)) ||
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 == 0))
		goto LAB_6fb30959;
	if (*(short*)(iVar5 + 0x96) != 0)
	{
		uStack_5c = uStack_5c | 0x8000;
		iStack_10 = (int)*(short*)(iVar5 + 0x96);
	}
	if (-1 < *(short*)(iVar4 + 0x20))
	{
		if (*(short*)(iVar4 + 0x22) < 0)
		{
			uVar7 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
			if ((uVar7 & 1) == 0)
			{
				iStack_4c = (int)*(short*)(iVar4 + 0x20);
			}
		}
		else
		{
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			iVar5 = (int)(((uint64_t)DVar2 & 0xffffffff) % 3);
			if (iVar5 == 0)
			{
				iStack_4c = (int)*(short*)(iVar4 + 0x20);
			}
			else if (iVar5 == 1)
			{
				iStack_4c = (int)*(short*)(iVar4 + 0x22);
			}
		}
	}
	uVar7 = *(uint32_t*)(iVar4 + 0x58);
	if (uVar7 == 0)
	{
	LAB_6fb30a2a:
		uStack_5c = uStack_5c | 0x4000;
	}
	else
	{
		pDVar1 = &pUnit->pSeed;
		if (0 < (int)uVar7)
		{
			if ((uVar7 & uVar7 - 1) == 0)
			{
				uVar9 = sub_6FAA88D0(&pDVar1->nLowSeed);
				uVar9 = uVar9 & uVar7 - 1;
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar2;
				uVar9 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar7);
			}
			if (uVar9 != 0)
				goto LAB_6fb30a2a;
		}
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		iStack_40 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_40 = 0;
	}
	else
	{
		iStack_40 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar7 = pUnit->dwUnitType;
	if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
	{
		DStack_3c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
	}
	else
	{
		DStack_3c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	pDVar3 = sub_6FB3E070(&uStack_5c);
	if (pDVar3 != nullptr)
	{
		iVar4 = UNITS_GetPrecisionX(pUnit);
		iVar5 = UNITS_GetPrecisionY(pUnit);
		pDynamicPath = pDVar3->pDynamicPath;
		PATH_SetPrecisionX(pDynamicPath, iVar4);
		PATH_SetPrecisionY(pDynamicPath, iVar5);
	}
LAB_6fb30ac1:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB30AD0
void __fastcall sub_6FB30AD0(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pRoom;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pUnit2;
	int iVar4;

	if ((((pUnit == nullptr) || (iVar4 = pUnit->dwClassId, iVar4 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4)) ||
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4, iVar4 == 0))
	{
	LAB_6fb30bbc:
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar1 = sub_6FB26AD0((int)pUnit);
	pRoom = UNITS_GetRoom(pUnit);
	iVar2 = DUNGEON_IsRoomInTown(pRoom);
	if (iVar2 != 0)
		goto LAB_6fb30bbc;
	uVar3 = MISSILE_GetTargetX(pUnit);
	if ((uVar3 & 1) == 0)
		goto LAB_6fb30bb1;
	sub_6FB4DEC0((int)pUnit);
	pUnit2 = PATH_GetTargetUnit(pUnit->pDynamicPath);
	if (pUnit2 != nullptr)
	{
		iVar2 = sub_6FB29550((int*)pUnit2);
		if (iVar2 == 0)
		{
			if (pDVar1 != nullptr)
			{
				uVar3 = sub_6FB29D80(pDVar1, pUnit2);
				if (uVar3 == 0)
					goto LAB_6fb30b75;
			}
		}
		else
		{
		LAB_6fb30b75:
			pUnit2 = nullptr;
		}
	}
	iVar4 = *(int*)(iVar4 + 0x58);
	if (iVar4 < 1)
	{
		iVar4 = 5;
	}
	if (pUnit2 != nullptr)
	{
		iVar2 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar2 % iVar4 == 0)
		{
			iVar4 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2);
			if ((3 < iVar4) && (iVar4 < 0x19))
			{
				D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			}
		}
	}
LAB_6fb30bb1:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB30BD0
// TODO: decompilation needs review (extraout, in_reg)
void* __cdecl sub_6FB30BD0()
{
	int iVar1;
	uint64_t uVar2;
	int64_t lVar3;
	uint8_t nDirection;
	code* in_EAX;
	code* extraout_EAX;
	int in_ECX;
	int iVar4;
	int in_EDX;
	uint32_t uVar5;

	if ((in_ECX != 0) && (iVar1 = *(int*)(in_ECX + 4), -1 < iVar1))
	{
		in_EAX = (code*)(((uint8_t*)&sgptDataTables));
		if (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))
		{
			in_EAX = (code*)(iVar1 * 0x15);
			iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
			if ((iVar1 != 0) && (in_EDX != 0))
			{
				uVar5 = *(uint32_t*)(iVar1 + 0x5c);
				iVar4 = 0;
				if (0 < (int)uVar5)
				{
					if ((uVar5 & uVar5 - 1) == 0)
					{
						lVar3 = (uint64_t) * (uint32_t*)(in_EDX + 0x20) * 0x6ac690c5 +
						        (uint64_t) * (uint32_t*)(in_EDX + 0x24);
						*(int64_t*)(in_EDX + 0x20) = lVar3;
						uVar5 = uVar5 - 1 & (uint32_t)lVar3;
					}
					else
					{
						uVar2 = (uint64_t) * (uint32_t*)(in_EDX + 0x20) * 0x6ac690c5 +
						        (uint64_t) * (uint32_t*)(in_EDX + 0x24);
						*(uint64_t*)(in_EDX + 0x20) = uVar2;
						uVar5 = (uint32_t)((uVar2 & 0xffffffff) % (uint64_t)uVar5);
					}
					iVar4 = uVar5 - *(int*)(iVar1 + 0x5c) / 2;
				}
				sub_6FB5FC80(in_ECX, 0, 0, iVar4);
				nDirection = PATH_GetDirection(*(D2DynamicPathStrc**)(in_EDX + 0x2c));
				PATH_SetDirection(*(D2DynamicPathStrc**)(in_ECX + 0x2c), nDirection);
				D2COMMON_10203_PATH_SetRotateFlag(*(D2DynamicPathStrc**)(in_ECX + 0x2c), 0);
				uVar5 = (uint32_t) * (uint8_t*)(iVar1 + 0x178);
				if (uVar5 == 0)
				{
					*(uint32_t*)(in_ECX + 0x44) = 0;
					return (void*)(extraout_EAX);
				}
				if ((uVar5 & uVar5 - 1) != 0)
				{
					uVar2 = (uint64_t) * (uint32_t*)(in_ECX + 0x20) * 0x6ac690c5 +
					        (uint64_t) * (uint32_t*)(in_ECX + 0x24);
					*(uint64_t*)(in_ECX + 0x20) = uVar2;
					uVar2 = uVar2 & 0xffffffff;
					*(int*)(in_ECX + 0x44) = (int)(uVar2 % (uint64_t)uVar5) << 8;
					return (void*)((code*)(uVar2 / uVar5));
				}
				lVar3 = (uint64_t) * (uint32_t*)(in_ECX + 0x20) * 0x6ac690c5 +
				        (uint64_t) * (uint32_t*)(in_ECX + 0x24);
				in_EAX = (code*)lVar3;
				*(int64_t*)(in_ECX + 0x20) = lVar3;
				*(uint32_t*)(in_ECX + 0x44) = (uVar5 - 1 & (uint32_t)in_EAX) << 8;
			}
		}
	}
	return (void*)(in_EAX);
}

//D2Client.0x6FB30D20
void __fastcall sub_6FB30D20(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_28;
	code* pcStack_8;
	D2UnitStrc* pDStack_4;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		if (*(short*)(iVar1 + 0x1e) < 0)
		{
			sub_6FB3DBB0(pUnit);
			return;
		}
		iVar3 = MISSILE_GetRemainingFrames(pUnit);
		if ((int)(uint32_t) * (uint8_t*)(iVar1 + 0x135) <= iVar3)
		{
			iVar3 = D2Common_10234(pUnit->pDynamicPath);
			if (iVar3 != 0)
			{
				puVar4 = &uStack_5c;
				for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar4 = 0;
					puVar4 = puVar4 + 1;
				}
				uStack_5c = 1;
				pDStack_58 = sub_6FB26AD0((int)pUnit);
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_48 = 0;
				}
				else
				{
					iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
				}
				else
				{
					DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar1 + 0x1e);
				iStack_28 = 1;
				if (0 < *(int*)(iVar1 + 0x58))
				{
					iStack_28 = *(int*)(iVar1 + 0x58);
				}
				pcStack_8 = (code*)(sub_6FB30BD0);
				pDStack_4 = pUnit;
				sub_6FB3E070(&uStack_5c);
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB30E80
void __fastcall sub_6FB30E80(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint32_t nSkillLevel;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t uVar6;
	int iStack_7c;
	int iStack_78;
	int iStack_74;
	int iStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar1 = pUnit->dwClassId, iVar1 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	if (*(short*)(iVar1 + 0x1e) < 0)
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar2 = MISSILE_GetSkill(pUnit);
	if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c, iVar4 != 0))
	{
		iStack_74 = *(int*)(iVar1 + 0x58);
		if (iStack_74 < 1)
		{
			iStack_74 = 1;
		}
		iStack_7c = 1;
		if (0 < *(int*)(iVar1 + 0x5c))
		{
			iStack_7c = *(int*)(iVar1 + 0x5c);
		}
		iStack_78 = 1;
		if (0 < *(int*)(iVar1 + 0x60))
		{
			iStack_78 = *(int*)(iVar1 + 0x60);
		}
		nSkillLevel = MISSILE_GetLevel(pUnit);
		uVar6 = *(uint32_t*)(iVar4 + 0x138);
		pDVar3 = sub_6FB26AD0((int)pUnit);
		iVar2 = SKILLS_EvaluateSkillFormula(pDVar3, uVar6, iVar2, nSkillLevel);
		if (iVar2 < 2)
		{
			iVar2 = 1;
		}
		else if (0x3b < iVar2)
		{
			iVar2 = 0x3c;
		}
		uVar6 = pUnit->dwInteractGUID;
		if (uVar6 == 0)
		{
			iStack_6c = 0;
		}
		else
		{
			iStack_6c = sub_6FAA4460(uVar6);
		}
		iVar4 = MISSILE_GetRemainingFrames(pUnit);
		if ((((iVar4 + 1) % (int)(0x3c / (int64_t)iVar2) == 0) && (iStack_6c < iVar2)) && (uVar6 != 0))
		{
			sub_6FAA43E0(uVar6, iStack_6c + 1);
		}
		if (iVar4 == 0)
		{
			puVar5 = &uStack_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar5 = 0;
				puVar5 = puVar5 + 1;
			}
			uStack_5c = 1;
			pDStack_58 = sub_6FB26AD0((int)pUnit);
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_48 = 0;
			}
			else
			{
				iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
			}
			else
			{
				DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			pDVar3 = sub_6FB3E070(&uStack_5c);
			if (pDVar3 != nullptr)
			{
				sub_6FB5FC80((int)pDVar3, -(iStack_78 * iStack_74), 0, iStack_7c * iStack_74);
				sub_6FB5FCB0((int)pDVar3, iStack_78, 0, -iStack_7c, 1);
			}
			if (0 < *(short*)(iVar1 + 0x20))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x20);
				pDVar3 = sub_6FB3E070(&uStack_5c);
				if (pDVar3 != nullptr)
				{
					sub_6FB5FC80((int)pDVar3, -(iStack_78 * iStack_74), 0, iStack_7c * iStack_74);
					sub_6FB5FCB0((int)pDVar3, iStack_78, 0, -iStack_7c, 1);
				}
			}
		}
		if (iVar4 == iStack_74 + -2)
		{
			iVar2 = sub_6FB4FA10((int)pUnit);
			if (iVar2 != 0)
			{
				sub_6FB555C0(iVar2, (int)pUnit, 1);
			}
			if (0 < *(short*)(iVar1 + 0x34))
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x34), pUnit, 0.0, 0.0, 0);
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB31180
D2UnitStrc* __fastcall sub_6FB31180(D2UnitStrc* pUnit, int a2, int a3, uint32_t a4)
{
	D2SeedStrc* pSeed;
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	uint16_t uVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	D2ActiveRoomStrc* pRoom;
	int iVar7;
	int32_t DVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint32_t* puVar11;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (a3 < 1)
	{
		return nullptr;
	}
	iVar5 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar5 % a3 != 0)
	{
		return nullptr;
	}
	pDVar6 = sub_6FB26AD0((int)pUnit);
	if (pDVar6 == nullptr)
	{
		return nullptr;
	}
	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom != nullptr)
	{
		uVar10 = pUnit->dwUnitType;
		pSeed = &pUnit->pSeed;
		if ((uVar10 == 2) || ((3 < (int)uVar10 && ((int)uVar10 < 6))))
		{
			iVar5 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iVar7 = MISSILE_GetRemainingFrames(pUnit);
		SEED_InitLowSeed(pSeed, iVar7 + iVar5);
		puVar11 = &uStack_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		uStack_5c = 0x2003;
		pDStack_58 = pDVar6;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iVar5 = a2 + -1;
		uVar10 = iVar5 * 2;
		uStack_4c = a4;
		if ((int)uVar10 < 1)
		{
			uVar9 = 0;
		}
		else
		{
			uVar3 = (uint64_t)(pUnit->pSeed).nHighSeed;
			if ((uVar10 & uVar10 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar3);
				*(uint64_t*)pSeed = DVar2;
				uVar9 = uVar10 - 1 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar3);
				*(uint64_t*)pSeed = DVar2;
				uVar9 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar10);
			}
		}
		if ((int)uVar10 < 1)
		{
			uVar10 = 0;
		}
		else
		{
			uVar3 = (uint64_t)(pUnit->pSeed).nHighSeed;
			if ((uVar10 & uVar10 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar3);
				*(uint64_t*)pSeed = DVar2;
				uVar10 = uVar10 - 1 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar3);
				*(uint64_t*)pSeed = DVar2;
				uVar10 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar10);
			}
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_48 = 0;
		}
		else
		{
			iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		iStack_48 = iStack_48 + (iVar5 - uVar9);
		uVar9 = pUnit->dwUnitType;
		if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
		{
			DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
		}
		else
		{
			DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_44 = (int)DVar8 + (iVar5 - uVar10);
		uVar4 = COLLISION_CheckMask(pRoom, iStack_48, iStack_44, 4);
		if (uVar4 == 0)
		{
			pDVar6 = sub_6FB3E070(&uStack_5c);
			return pDVar6;
		}
		return nullptr;
	}
	return nullptr;
}

//D2Client.0x6FB31390
void __fastcall sub_6FB31390(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	int iVar2;
	uint64_t DVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	D2UnitStrc* pMissile;
	int iVar6;
	int iVar7;
	int iVar8;

	if ((((pUnit == nullptr) || (iVar2 = pUnit->dwClassId, iVar2 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)) ||
	    ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 == 0 ||
	                                                                                       (*(short*)(iVar2 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar8 = (int)*(short*)(iVar2 + 0x1e);
	if (iVar8 < *(short*)(iVar2 + 0x20))
	{
		uVar4 = *(short*)(iVar2 + 0x20) - iVar8;
		pDVar1 = &pUnit->pSeed;
		uVar5 = uVar4 + 1;
		if ((int)uVar5 < 1)
		{
			uVar5 = 0;
		}
		else if ((uVar5 & uVar4) == 0)
		{
			uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
			uVar5 = uVar5 & uVar4;
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar5 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar5);
		}
		iVar8 = iVar8 + uVar5;
	}
	uVar4 = MISSILE_GetLevel(pUnit);
	iVar6 = *(int*)(iVar2 + 0x60);
	if (iVar6 < 1)
	{
		iVar6 = 1;
	}
	iVar6 = (int)uVar4 / iVar6;
	iVar7 = 2;
	if (1 < iVar6)
	{
		iVar7 = iVar6;
	}
	iVar6 = *(int*)(iVar2 + 0x5c) - iVar6;
	if (iVar6 < 3)
	{
		iVar6 = 3;
	}
	pMissile = sub_6FB31180(pUnit, *(int*)(iVar2 + 0x58) + iVar7, iVar6, iVar8);
	if (pMissile != nullptr)
	{
		iVar2 = pMissile->dwClassId;
		if (((iVar2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)) ||
		    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 == 0))
		{
			sub_6FB3DBB0(pMissile);
			sub_6FB3D880(pUnit);
			return;
		}
		iVar8 = *(int*)(iVar2 + 0x5c);
		if (iVar8 < 1)
		{
			iVar8 = 1;
		}
		iVar6 = iVar8;
		if (iVar8 <= *(int*)(iVar2 + 0x58))
		{
			iVar6 = *(int*)(iVar2 + 0x58);
		}
		sub_6FB5FC80((int)pMissile, 0, 0, iVar6);
		sub_6FB5FCB0((int)pMissile, 0, 0, -iVar8, 1);
		MISSILE_SetTotalFrames(pMissile, iVar6 / iVar8);
		MISSILE_SetCurrentFrame(pMissile, iVar6 / iVar8);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB31540
void __fastcall sub_6FB31540(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = UNITS_IsAtEndOfFrameCycle(pUnit);
	if (iVar1 != 0)
	{
		sub_6FB29540((int)pUnit);
		sub_6FB296E0((int)pUnit);
		return;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB31570
void __fastcall sub_6FB31570(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	int iVar3;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                        (0 < *(int*)(iVar1 + 0x58))) &&
	        (0 < *(int*)(iVar1 + 0x5c)))))
	{
		iVar3 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar3 == 0)
		{
			iVar3 = *(int*)(iVar1 + 0x5c) / 3;
			iVar2 = (iVar3 * 25000) / 0x19;
			sub_6FAB7E70(*(uint32_t*)(iVar1 + 0x58), iVar2,
			    ((*(int*)(iVar1 + 0x5c) * 5 + iVar3 * -10) * 5000) / 0x19, iVar2);
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB31660
void __fastcall sub_6FB31660(D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	int32_t DStack_68;
	int32_t DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar6 = pUnit->dwClassId, -1 < iVar6)) &&
	        (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4, iVar6 != 0))
	{
		if ((0 < *(short*)(iVar6 + 0x1e)) &&
		    (iVar2 = MISSILE_GetRemainingFrames(pUnit), iVar2 == *(int*)(iVar6 + 0x58)))
		{
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_64 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
			}
			else
			{
				DStack_64 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_68 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
			}
			else
			{
				DStack_68 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar3 = MISSILE_GetLevel(pUnit);
			iVar2 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar6 + 0x1e);
			pDVar4 = sub_6FB26AD0((int)pUnit);
			if (pDVar4 != nullptr)
			{
				puVar7 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uStack_5c = 1;
				(*(uint16_t*)((uint8_t*)&iStack_48 + 0)) = (*(uint16_t*)((uint8_t*)&DStack_68 + 0));
				(*(uint16_t*)((uint8_t*)&iStack_48 + 2)) = (*(uint16_t*)((uint8_t*)&DStack_68 + 2));
				DStack_44 = DStack_64;
				pDStack_58 = pDVar4;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar2;
				uStack_2c = uVar3;
				sub_6FB3E070(&uStack_5c);
			}
		}
		if ((0 < *(short*)(iVar6 + 0x20)) &&
		    (iVar2 = MISSILE_GetRemainingFrames(pUnit), iVar2 == *(int*)(iVar6 + 0x5c)))
		{
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
			}
			else
			{
				DStack_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_64 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
			}
			else
			{
				DStack_64 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar3 = MISSILE_GetLevel(pUnit);
			iVar2 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar6 + 0x20);
			pDVar4 = sub_6FB26AD0((int)pUnit);
			if (pDVar4 != nullptr)
			{
				puVar7 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uStack_5c = 1;
				(*(uint16_t*)((uint8_t*)&iStack_48 + 0)) = (*(uint16_t*)((uint8_t*)&DStack_64 + 0));
				(*(uint16_t*)((uint8_t*)&iStack_48 + 2)) = (*(uint16_t*)((uint8_t*)&DStack_64 + 2));
				DStack_44 = DStack_68;
				pDStack_58 = pDVar4;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar2;
				uStack_2c = uVar3;
				sub_6FB3E070(&uStack_5c);
			}
		}
		if ((0 < *(short*)(iVar6 + 0x22)) &&
		    (iVar2 = MISSILE_GetRemainingFrames(pUnit), iVar2 == *(int*)(iVar6 + 0x60)))
		{
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
			}
			else
			{
				DStack_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_64 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
			}
			else
			{
				DStack_64 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar3 = MISSILE_GetLevel(pUnit);
			iVar2 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar6 + 0x22);
			pDVar4 = sub_6FB26AD0((int)pUnit);
			if (pDVar4 != nullptr)
			{
				puVar7 = &uStack_5c;
				for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uStack_5c = 1;
				(*(uint16_t*)((uint8_t*)&iStack_48 + 0)) = (*(uint16_t*)((uint8_t*)&DStack_64 + 0));
				(*(uint16_t*)((uint8_t*)&iStack_48 + 2)) = (*(uint16_t*)((uint8_t*)&DStack_64 + 2));
				DStack_44 = DStack_68;
				pDStack_58 = pDVar4;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar2;
				uStack_2c = uVar3;
				sub_6FB3E070(&uStack_5c);
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB31990
void __fastcall sub_6FB31990(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	int iVar8;
	int iVar9;
	int local_c;

	if ((((pUnit != nullptr) && (iVar6 = pUnit->dwClassId, -1 < iVar6)) &&
	        (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4, iVar6 != 0 &&
	                                                                                       (-1 < *(short*)(iVar6 + 0x1e)))))
	{
		local_c = (int)*(short*)(iVar6 + 0x1e);
		if (local_c < *(short*)(iVar6 + 0x20))
		{
			uVar4 = *(short*)(iVar6 + 0x20) - local_c;
			uVar5 = uVar4 + 1;
			if ((int)uVar5 < 1)
			{
				uVar4 = 0;
			}
			else
			{
				uVar3 = (uint64_t)(pUnit->pSeed).nHighSeed;
				uVar1 = (pUnit->pSeed).nLowSeed;
				if ((uVar5 & uVar4) == 0)
				{
					DVar2 = (uint64_t)((uint64_t)uVar1 * 0x6ac690c5 + uVar3);
					(*(uint64_t*)&pUnit->pSeed) = DVar2;
					uVar4 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
				}
				else
				{
					DVar2 = (uint64_t)((uint64_t)uVar1 * 0x6ac690c5 + uVar3);
					(*(uint64_t*)&pUnit->pSeed) = DVar2;
					uVar4 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar5);
				}
			}
			local_c = uVar4 + local_c;
		}
		iVar6 = MISSILE_GetSkill(pUnit);
		if (((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar6 * 0x23c, iVar9 != 0))
		{
			pDVar7 = sub_6FB26AD0((int)pUnit);
			uVar4 = MISSILE_GetLevel(pUnit);
			iVar8 = SKILLS_EvaluateSkillFormula(pDVar7, *(uint32_t*)(iVar9 + 0x138), iVar6, uVar4);
			iVar6 = SKILLS_EvaluateSkillFormula(pDVar7, *(uint32_t*)(iVar9 + 0x13c), iVar6, uVar4);
			if ((iVar6 != 0) && (0 < iVar8))
			{
				pDVar7 = sub_6FB31180(pUnit, iVar8, iVar6, local_c);
				if (pDVar7 != nullptr)
				{
					iVar6 = pDVar7->dwClassId;
					if (((iVar6 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar6)) ||
					    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4, iVar6 == 0))
					{
						sub_6FB3DBB0(pDVar7);
						sub_6FB3D880(pUnit);
						return;
					}
					iVar9 = *(int*)(iVar6 + 0x5c);
					if (iVar9 < 1)
					{
						iVar9 = 1;
					}
					iVar8 = iVar9;
					if (iVar9 <= *(int*)(iVar6 + 0x58))
					{
						iVar8 = *(int*)(iVar6 + 0x58);
					}
					sub_6FB5FC80((int)pDVar7, 0, 0, iVar8);
					sub_6FB5FCB0((int)pDVar7, 0, 0, -iVar9, 1);
					MISSILE_SetTotalFrames(pDVar7, iVar8 / iVar9);
					MISSILE_SetCurrentFrame(pDVar7, iVar8 / iVar9);
				}
				sub_6FB3D880(pUnit);
				return;
			}
		}
		sub_6FB3DBB0(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB31BA0
void __fastcall sub_6FB31BA0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pUnit2;
	int iVar3;
	int32_t DVar4;
	int32_t DVar5;
	int iVar6;
	int iVar7;
	int iStack_8;
	int32_t DStack_4;

	if ((((pUnit == nullptr) || (iVar6 = pUnit->dwClassId, iVar6 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar6)) ||
	    ((iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4, iVar6 == 0 ||
	                                                                                       (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pUnit2 = sub_6FB296A0((int)pUnit);
	if ((pUnit2 != nullptr) ||
	    (pUnit2 = sub_6FB296A0((int)pDVar2), pUnit2 != nullptr))
	{
		iVar7 = *(int*)(iVar6 + 0x60);
		if (iVar7 < 1)
		{
			iVar7 = 5;
		}
		iVar3 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar3 % iVar7 == 0)
		{
			iVar7 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2);
			if (iVar7 <= *(int*)(iVar6 + 100))
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iStack_8 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_8 = 0;
				}
				else
				{
					iStack_8 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DStack_4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_4 + 2)) = 0;
				}
				else
				{
					DStack_4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit2->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar7 = pUnit2->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit2->pDynamicPath == nullptr)
				{
					iVar7 = 0;
				}
				else
				{
					iVar7 = PATH_GetXPosition(pUnit2->pDynamicPath);
				}
				uVar1 = pUnit2->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar4 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
				}
				else if (pUnit2->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
				}
				else
				{
					DVar4 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
				}
				iVar6 = *(int*)(iVar6 + 0x68);
				if (iVar6 < 1)
				{
					iVar6 = 1;
				}
				iVar3 = iVar6;
				if ((iVar7 <= iStack_8) && (iVar3 = 0, iVar7 < iStack_8))
				{
					iVar3 = -iVar6;
				}
				iVar7 = iVar6;
				if (((int)DVar4 <= (int)DStack_4) && (iVar7 = 0, (int)DVar4 < (int)DStack_4))
				{
					iVar7 = -iVar6;
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar5 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar6 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar6 + iVar3, (int)DVar5 + iVar7);
				D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB31DD0
void __fastcall sub_6FB31DD0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	D2UnitStrc* pUnit2;
	int iVar6;
	int32_t DVar7;
	int32_t DVar8;
	int iVar9;
	uint32_t* puVar10;
	int iStack_6c;
	int32_t DStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	uint32_t uStack_34;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	if ((((pUnit == nullptr) || (iVar1 = pUnit->dwClassId, iVar1 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar3 = sub_6FB26AD0((int)pUnit);
	if (pDVar3 == nullptr)
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar4 = MISSILE_GetTargetX(pUnit);
	iVar5 = -*(int*)(iVar1 + 0x5c);
	if (iVar4 != iVar5 && SBORROW4(iVar4, iVar5) == iVar4 + *(int*)(iVar1 + 0x5c) < 0)
	{
		if (iVar4 < 1)
		{
			MISSILE_SetTargetX(pUnit, iVar4 + -1);
		}
		iVar5 = PATH_GetVelocity(pUnit->pDynamicPath);
		if (iVar5 != 0)
		{
			pUnit2 = PATH_GetTargetUnit(pUnit->pDynamicPath);
			if (pUnit2 == nullptr)
			{
				pUnit2 = sub_6FB296A0((int)pDVar3);
			}
			iVar5 = *(int*)(iVar1 + 0x60);
			if (iVar5 < 1)
			{
				iVar5 = 5;
			}
			if (((pUnit2 != nullptr) &&
			        (iVar6 = MISSILE_GetCurrentFrame(pUnit), iVar6 % iVar5 == 0)) &&
			    ((0 < iVar4 &&
			        (iVar5 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2), iVar5 < *(int*)(iVar1 + 100)))))
			{
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_6c = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_6c = 0;
				}
				else
				{
					iStack_6c = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
				}
				else
				{
					DStack_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit2->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit2->pDynamicPath == nullptr)
				{
					iVar5 = 0;
				}
				else
				{
					iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
				}
				uVar2 = pUnit2->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DVar7 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
				}
				else if (pUnit2->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
				}
				else
				{
					DVar7 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
				}
				iVar6 = *(int*)(iVar1 + 0x68);
				if (iVar6 < 1)
				{
					iVar6 = 1;
				}
				iVar9 = iVar6;
				if ((iVar5 <= iStack_6c) && (iVar9 = 0, iVar5 < iStack_6c))
				{
					iVar9 = -iVar6;
				}
				iVar5 = iVar6;
				if (((int)DVar7 <= (int)DStack_68) && (iVar5 = 0, (int)DVar7 < (int)DStack_68))
				{
					iVar5 = -iVar6;
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
				}
				else
				{
					DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iVar6 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar6 + iVar9, (int)DVar8 + iVar5);
				D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			}
			if (0 < *(short*)(iVar1 + 0x1e))
			{
				iVar5 = *(int*)(iVar1 + 0x58);
				if (iVar5 < 2)
				{
					iVar5 = 1;
				}
				iVar6 = MISSILE_GetCurrentFrame(pUnit);
				if ((iVar6 % iVar5 == 0) && (0 < iVar4))
				{
					puVar10 = &uStack_5c;
					for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
					{
						*puVar10 = 0;
						puVar10 = puVar10 + 1;
					}
					uVar2 = pUnit->dwUnitType;
					uStack_5c = 5;
					if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
					{
						iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						iStack_48 = 0;
					}
					else
					{
						iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
					}
					uVar2 = pUnit->dwUnitType;
					if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
					{
						DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
					}
					else
					{
						DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
					}
					iStack_10 = MISSILE_GetTotalFrames(pUnit);
					iStack_10 = iStack_10 + -1;
					uStack_34 = 0;
					iStack_4c = (int)*(short*)(iVar1 + 0x1e);
					pDStack_58 = pDVar3;
					iStack_30 = MISSILE_GetSkill(pUnit);
					uStack_2c = MISSILE_GetLevel(pUnit);
					pDVar3 = sub_6FB3E070(&uStack_5c);
					if (pDVar3 != nullptr)
					{
						MISSILE_SetTargetX(pDVar3, 0);
					}
				}
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB32150
void __fastcall sub_6FB32150(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x1e)))))
	{
		pDVar4 = sub_6FB26AD0((int)pUnit);
		if (pDVar4 != nullptr)
		{
			iVar5 = D2Common_10234(pUnit->pDynamicPath);
			if (iVar5 != 0)
			{
				puVar6 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar6 = 0;
					puVar6 = puVar6 + 1;
				}
				DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				uStack_5c = 0x21;
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				if (((uint64_t)DVar3 & 3) != 0)
				{
					uStack_5c = 0x4021;
				}
				pDStack_58 = sub_6FB26AD0((int)pUnit);
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_48 = 0;
				}
				else
				{
					iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
				}
				else
				{
					DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_40 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_40 = 0;
				}
				else
				{
					iStack_40 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_3c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
				}
				else
				{
					DStack_3c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar1 + 0x1e);
				sub_6FB3E070(&uStack_5c);
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB32310
void __fastcall sub_6FB32310(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	int32_t DVar7;
	uint32_t uStack_8;

	if ((((pUnit != nullptr) && (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
	        (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0))
	{
		iVar2 = MISSILE_GetStreamMissile(pUnit);
		if (iVar2 == 0)
		{
			iVar2 = (int)*(short*)(iVar5 + 0x1e);
		}
		if ((-1 < iVar2) && (uVar3 = MISSILE_GetStreamRange(pUnit), 0 < (int)uVar3))
		{
			iVar4 = MISSILE_GetRemainingFrames(pUnit);
			if ((iVar4 < *(int*)(iVar5 + 0x58)) &&
			    (iVar5 = MISSILE_GetRemainingFrames(pUnit), iVar5 % 3 == 0))
			{
				uStack_8 = uVar3;
				if (4 < (int)uVar3)
				{
					uStack_8 = (int)uVar3 / 2;
				}
				uVar6 = MISSILE_GetLevel(pUnit);
				iVar5 = MISSILE_GetSkill(pUnit);
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
				}
				else
				{
					DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar4 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				sub_6FB35D10(pUnit, iVar4, (int)DVar7, uVar3, iVar2, iVar5, uVar6, uStack_8, (4 < (int)uVar3) + 1);
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB32470
void __fastcall sub_6FB32470(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint8_t nDirection;
	int iVar2;
	int32_t DVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	int iStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	uint32_t uStack_28;

	(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
	if ((((pUnit != nullptr) && (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
	        (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0 &&
	                                                                                       (-1 < *(short*)(iVar5 + 0x1e)))))
	{
		iVar2 = MISSILE_GetRemainingFrames(pUnit);
		if ((int)(uint32_t) * (uint8_t*)(iVar5 + 0x135) <= iVar2)
		{
			iVar2 = D2Common_10234(pUnit->pDynamicPath);
			if (iVar2 != 0)
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iStack_60 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_60 = 0;
				}
				else
				{
					iStack_60 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath != nullptr)
				{
					DVar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				puVar6 = &uStack_5c;
				for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
				{
					*puVar6 = 0;
					puVar6 = puVar6 + 1;
				}
				uStack_5c = 1;
				pDStack_58 = sub_6FB26AD0((int)pUnit);
				iStack_48 = iStack_60;
				DStack_44 = DVar3;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar5 + 0x1e);
				uStack_28 = *(uint32_t*)(iVar5 + 0x58);
				pDVar4 = sub_6FB3E070(&uStack_5c);
				if (pDVar4 != nullptr)
				{
					nDirection = PATH_GetDirection(pUnit->pDynamicPath);
					PATH_SetDirection(pDVar4->pDynamicPath, nDirection);
					iVar5 = UNITS_GetPrecisionX(pUnit);
					PATH_SetPrecisionX(pDVar4->pDynamicPath, iVar5);
					iVar5 = UNITS_GetPrecisionY(pUnit);
					PATH_SetPrecisionY(pDVar4->pDynamicPath, iVar5);
					iVar5 = sub_6FB5FC40((int)pUnit);
					sub_6FB5FC80((int)pDVar4, 0, 0, iVar5);
				}
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB32610
void __fastcall sub_6FB32610(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar1 = pUnit->dwClassId, iVar1 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0 ||
	                                                                                       (*(short*)(iVar1 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar2 = sub_6FB26AD0((int)pUnit);
	iVar5 = 1;
	if (0 < *(int*)(iVar1 + 0x58))
	{
		iVar5 = *(int*)(iVar1 + 0x58);
	}
	iVar3 = MISSILE_GetRemainingFrames(pUnit);
	if (0 < iVar3 % iVar5)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	puVar6 = &uStack_5c;
	for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	uStack_5c = 2;
	pDStack_58 = pDVar2;
	pDStack_54 = pUnit;
	iStack_30 = MISSILE_GetSkill(pUnit);
	uStack_2c = MISSILE_GetLevel(pUnit);
	iStack_4c = (int)*(short*)(iVar1 + 0x1e);
	uVar4 = MISSILE_GetTargetX(pUnit);
	uVar4 = uVar4 & 0x8000003f;
	if (((int)uVar4 < 0) && (uVar4 = (uVar4 - 1 | 0xffffffc0) + 1, (int)uVar4 < 0))
	{
		uVar4 = -uVar4;
	}
	uStack_40 = *(uint32_t*)(byte_6FB70160 + uVar4 * 4);
	uStack_3c = *(uint32_t*)(byte_6FB70260 + uVar4 * 4);
	uVar4 = *(int*)(iVar1 + 0x5c) + uVar4 & 0x8000003f;
	if ((int)uVar4 < 0)
	{
		uVar4 = (uVar4 - 1 | 0xffffffc0) + 1;
	}
	MISSILE_SetTargetX(pUnit, uVar4);
	sub_6FB3E070(&uStack_5c);
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB32750
void __fastcall sub_6FB32750(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int32_t DVar5;

	if ((((pUnit != nullptr) && (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
	        (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0))
	{
		iVar4 = 1;
		if (0 < *(int*)(iVar3 + 0x5c))
		{
			iVar4 = *(int*)(iVar3 + 0x5c);
		}
		iVar2 = MISSILE_GetRemainingFrames(pUnit);
		if ((iVar2 < *(int*)(iVar3 + 0x58)) && (iVar2 % iVar4 == 0))
		{
			iVar3 = MISSILE_GetTargetX(pUnit);
			iVar4 = MISSILE_GetTargetY(pUnit);
			uVar1 = pUnit->dwUnitType;
			iVar2 = (iVar3 - iVar4) / 2;
			iVar3 = (iVar3 + iVar4) / 2;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar5 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
			}
			else
			{
				DVar5 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				iVar4 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar4 = 0;
			}
			else
			{
				iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar4 + iVar2, (int)DVar5 + iVar3);
			D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			MISSILE_SetTargetX(pUnit, iVar2);
			MISSILE_SetTargetY(pUnit, iVar3);
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB32870
void __fastcall sub_6FB32870(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t* puVar9;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar7 = pUnit->dwClassId, iVar7 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar7)) ||
	    ((iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4, iVar7 == 0 ||
	                                                                                       (*(short*)(iVar7 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar5 = sub_6FB26AD0((int)pUnit);
	if (pDVar5 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	iVar6 = MISSILE_GetTargetX(pUnit);
	if (iVar6 == 0)
	{
		puVar9 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		iStack_4c = (int)*(short*)(iVar7 + 0x1e);
		uStack_5c = 2;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uVar8 = *(int*)(iVar7 + 0x58) * 2;
		uVar1 = uVar8 + 1;
		if ((int)uVar1 < 1)
		{
			uVar8 = 0;
		}
		else
		{
			uVar2 = (pUnit->pSeed).nLowSeed;
			uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
			if ((uVar1 & uVar8) == 0)
			{
				DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				uVar8 = uVar8 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			else
			{
				DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
			}
		}
		iStack_40 = uVar8 - *(int*)(iVar7 + 0x58);
		uVar8 = *(int*)(iVar7 + 0x58) * 2;
		uVar1 = uVar8 + 1;
		if ((int)uVar1 < 1)
		{
			uVar8 = 0;
		}
		else
		{
			uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
			uVar2 = (pUnit->pSeed).nLowSeed;
			if ((uVar1 & uVar8) == 0)
			{
				DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				uVar8 = uVar8 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			else
			{
				DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
			}
		}
		uVar1 = *(uint32_t*)(iVar7 + 0x58);
		iStack_3c = uVar8 - uVar1;
		if ((iStack_40 == 0) && (iStack_3c == 0))
		{
			uVar8 = 0;
			if (0 < (int)uVar1)
			{
				uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
				uVar8 = (pUnit->pSeed).nLowSeed;
				if ((uVar1 & uVar1 - 1) == 0)
				{
					DVar3 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar4);
					(*(uint64_t*)&pUnit->pSeed) = DVar3;
					uVar8 = uVar1 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
				}
				else
				{
					DVar3 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar4);
					(*(uint64_t*)&pUnit->pSeed) = DVar3;
					uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
				}
			}
			iStack_40 = uVar8 + 1;
		}
		pDStack_58 = pDVar5;
		pDStack_54 = pDVar5;
		pDVar5 = sub_6FB3E070(&uStack_5c);
		if (pDVar5 != nullptr)
		{
			MISSILE_SetTargetX(pDVar5, iStack_40);
			MISSILE_SetTargetY(pDVar5, iStack_3c);
		}
		iVar7 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar7 < 0x7d)
		{
			MISSILE_SetTargetX(pUnit, 0x18);
			sub_6FB3D880(pUnit);
			return;
		}
		if (iVar7 < 0xaf)
		{
			MISSILE_SetTargetX(pUnit, 9);
			sub_6FB3D880(pUnit);
			return;
		}
		iVar6 = ((299 < iVar7) - 1 & 0xfffffff4) + 0xf;
	}
	MISSILE_SetTargetX(pUnit, iVar6 + -1);
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB32AC0
void __fastcall sub_6FB32AC0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t DVar6;
	int iVar7;
	uint32_t* puVar8;
	int iVar9;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;
	code* pcStack_8;
	D2UnitStrc* pDStack_4;

	if ((((pUnit != nullptr) && (iVar7 = pUnit->dwClassId, -1 < iVar7)) &&
	        (iVar7 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4, iVar7 != 0))
	{
		pDVar4 = sub_6FB26AD0((int)pUnit);
		if (pDVar4 == nullptr)
		{
			sub_6FB3D880(pUnit);
			return;
		}
		if (-1 < *(short*)(iVar7 + 0x1e))
		{
			iVar5 = D2Common_10234(pUnit->pDynamicPath);
			if (iVar5 != 0)
			{
				puVar8 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				pDStack_58 = pDVar4;
				pDStack_54 = pUnit;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar7 + 0x1e);
				pcStack_8 = (code*)(sub_6FB30BD0);
				pDStack_4 = pUnit;
				pDVar4 = sub_6FB3E070(&uStack_5c);
				if (pDVar4 != nullptr)
				{
					iVar5 = sub_6FB5FC40((int)pUnit);
					sub_6FB5FC80((int)pDVar4, 0, 0, iVar5);
				}
			}
		}
		iVar7 = *(int*)(iVar7 + 0x58);
		if (iVar7 < 1)
		{
			iVar7 = 1;
		}
		iVar5 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar5 % iVar7 == 0)
		{
			iVar7 = MISSILE_GetTargetX(pUnit);
			iVar5 = MISSILE_GetTargetY(pUnit);
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			if (((uint64_t)DVar2 & 1) == 0)
			{
				iVar9 = -iVar7;
				iVar3 = iVar5;
			}
			else
			{
				iVar9 = iVar7;
				iVar3 = -iVar5;
			}
			iVar7 = (iVar7 + iVar3) * 3;
			iVar5 = (iVar5 + iVar9) * 3;
			iVar9 = (int)(iVar7 + (iVar7 >> 0x1f & 3U)) >> 2;
			iVar7 = (int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2;
			if ((iVar9 != 0) || (iVar7 != 0))
			{
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
				}
				else
				{
					DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					iVar5 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar5 = 0;
				}
				else
				{
					iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar5 + iVar9, (int)DVar6 + iVar7);
				D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			}
			MISSILE_SetTargetX(pUnit, iVar9);
			MISSILE_SetTargetY(pUnit, iVar7);
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB32CB0
void __fastcall sub_6FB32CB0(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = MISSILE_GetCurrentFrame(pUnit);
	if (iVar1 < 100)
	{
		MISSILE_SetCurrentFrame(pUnit, 500);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB32CE0
void __fastcall sub_6FB32CE0(D2UnitStrc* pUnit)
{
	int iVar1;
	int32_t DVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	D2ActiveRoomStrc* pDVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	D2UnitStrc* pDVar10;
	int iVar11;
	uint32_t* puVar12;
	bool bVar13;
	uint32_t uStack_b8;
	D2UnitStrc* pDStack_b4;
	int iStack_a8;
	int iStack_a4;
	int32_t DStack_a0;
	int iStack_9c;
	int32_t DStack_98;
	int iStack_8c;
	uint32_t uStack_88;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		uVar3 = MISSILE_GetCurrentFrame(pUnit);
		pDVar4 = sub_6FB26AD0((int)pUnit);
		iVar7 = *(int*)(iVar1 + 0x58);
		if ((((int)uVar3 < *(short*)(iVar1 + 0x96) - iVar7) && (iVar7 < (int)uVar3)) &&
		    ((0 < *(short*)(iVar1 + 0x1e) &&
		        (pDVar5 = sub_6FB31180(pUnit, *(int*)(iVar1 + 0x60), *(int*)(iVar1 + 0x5c),
		             (int)*(short*)(iVar1 + 0x1e)),
		            pDVar5 != nullptr))))
		{
			iVar9 = pDVar5->dwClassId;
			if (((iVar9 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar9)) ||
			    (iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar9 * 0x1a4, iVar9 == 0))
			{
				sub_6FB3DBB0(pDVar5);
			}
			else if (0 < *(int*)(iVar9 + 0x5c))
			{
				sub_6FB5FC80((int)pDVar5, 0, 0, *(int*)(iVar9 + 0x58));
				sub_6FB5FCB0((int)pDVar5, 0, 0, -*(int*)(iVar9 + 0x5c), 1);
				iVar9 = *(int*)(iVar9 + 0x58) / *(int*)(iVar9 + 0x5c);
				MISSILE_SetTotalFrames(pDVar5, iVar9);
				MISSILE_SetCurrentFrame(pDVar5, iVar9);
			}
		}
		if (((int)uVar3 < iVar7 + 0x7d) && (iVar7 < (int)uVar3))
		{
			pDVar6 = UNITS_GetRoom(pUnit);
			for (pDVar5 = pDVar6->pUnitFirst; pDVar5 != nullptr; pDVar5 = pDVar5->pRoomNext)
			{
				if ((((pDVar5 != nullptr) && (pDVar5->dwUnitType == 2)) &&
				        (0x10 < (uint32_t)pDVar5->dwClassId)) &&
				    ((uint32_t)pDVar5->dwClassId < 0x16))
				{
					if (0 < *(short*)(iVar1 + 0x1e))
					{
						DVar2 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
						uVar8 = pDVar5->dwUnitType;
						if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
						{
							iVar7 = pDVar5->pDynamicPath->dwClientCoordY;
						}
						else if (pDVar5->pDynamicPath == nullptr)
						{
							iVar7 = 0;
						}
						else
						{
							iVar7 = PATH_GetXPosition(pDVar5->pDynamicPath);
						}
						uVar8 = MISSILE_GetLevel(pUnit);
						iVar9 = MISSILE_GetSkill(pUnit);
						if (pDVar4 != nullptr)
						{
							puVar12 = &uStack_5c;
							for (iVar11 = 0x17; iVar11 != 0; iVar11 = iVar11 + -1)
							{
								*puVar12 = 0;
								puVar12 = puVar12 + 1;
							}
							uStack_5c = 1;
							iStack_4c = (int)*(short*)(iVar1 + 0x1e);
							pDStack_58 = pDVar4;
							iStack_48 = iVar7;
							DStack_44 = DVar2;
							iStack_30 = iVar9;
							uStack_2c = uVar8;
							pDVar10 = sub_6FB3E070(&uStack_5c);
							if (pDVar10 != nullptr)
							{
								iVar7 = pDVar10->dwClassId;
								if (((iVar7 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar7)) ||
								    (iVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar7 * 0x1a4,
								        iVar7 == 0))
								{
									sub_6FB3DBB0(pDVar10);
								}
								else if (0 < *(int*)(iVar7 + 0x5c))
								{
									sub_6FB5FC80((int)pDVar10, 0, 0, *(int*)(iVar7 + 0x58));
									sub_6FB5FCB0((int)pDVar10, 0, 0, -*(int*)(iVar7 + 0x5c), 1);
									iVar7 = *(int*)(iVar7 + 0x58) / *(int*)(iVar7 + 0x5c);
									MISSILE_SetTotalFrames(pDVar10, iVar7);
									MISSILE_SetCurrentFrame(pDVar10, iVar7);
								}
							}
						}
					}
					if (0 < *(short*)(iVar1 + 0x20))
					{
						uVar8 = uVar3 & 0x80000007;
						bVar13 = uVar8 == 0;
						if ((int)uVar8 < 0)
						{
							bVar13 = (uVar8 - 1 | 0xfffffff8) == 0xffffffff;
						}
						if (bVar13)
						{
							uVar8 = MISSILE_GetTargetX(pUnit);
							if ((uVar8 == 0) || (pDVar10 = sub_6FB269F0(uVar8, 2), pDVar10 == nullptr))
							{
								MISSILE_SetTargetX(pUnit, pDVar5->dwUnitId);
							}
							else
							{
								puVar12 = &uStack_b8;
								for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
								{
									*puVar12 = 0;
									puVar12 = puVar12 + 1;
								}
								uStack_b8 = 0x421;
								uVar8 = pDVar5->dwUnitType;
								pDStack_b4 = pDVar4;
								if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
								{
									iStack_a4 = pDVar5->pDynamicPath->dwClientCoordY;
								}
								else if (pDVar5->pDynamicPath == nullptr)
								{
									iStack_a4 = 0;
								}
								else
								{
									iStack_a4 = PATH_GetXPosition(pDVar5->pDynamicPath);
								}
								uVar8 = pDVar5->dwUnitType;
								if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
								{
									DStack_a0 = (*(int32_t*)&pDVar5->pDynamicPath->tTargetCoord);
								}
								else if (pDVar5->pDynamicPath == nullptr)
								{
									(*(uint16_t*)((uint8_t*)&DStack_a0 + 0)) = 0;
									(*(uint16_t*)((uint8_t*)&DStack_a0 + 2)) = 0;
								}
								else
								{
									DStack_a0 = (int32_t)PATH_GetYPosition(pDVar5->pDynamicPath);
								}
								iStack_8c = MISSILE_GetSkill(pUnit);
								uStack_88 = MISSILE_GetLevel(pUnit);
								iStack_a8 = (int)*(short*)(iVar1 + 0x20);
								uVar8 = pDVar10->dwUnitType;
								if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
								{
									iStack_9c = pDVar10->pDynamicPath->dwClientCoordY;
								}
								else if (pDVar10->pDynamicPath == nullptr)
								{
									iStack_9c = 0;
								}
								else
								{
									iStack_9c = PATH_GetXPosition(pDVar10->pDynamicPath);
								}
								uVar8 = pDVar10->dwUnitType;
								if ((uVar8 == 2) || ((3 < (int)uVar8 && ((int)uVar8 < 6))))
								{
									DStack_98 = (*(int32_t*)&pDVar10->pDynamicPath->tTargetCoord);
								}
								else if (pDVar10->pDynamicPath == nullptr)
								{
									(*(uint16_t*)((uint8_t*)&DStack_98 + 0)) = 0;
									(*(uint16_t*)((uint8_t*)&DStack_98 + 2)) = 0;
								}
								else
								{
									DStack_98 = (int32_t)PATH_GetYPosition(pDVar10->pDynamicPath);
								}
								sub_6FB3E070(&uStack_b8);
								uVar8 = sub_6FAA88D0(&(pDVar10->pSeed).nLowSeed);
								if ((uVar8 & 3) == 0)
								{
									MISSILE_SetTargetX(pUnit, pDVar5->dwUnitId);
								}
							}
						}
					}
				}
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB33180
void __fastcall sub_6FB33180(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	int iVar2;
	uint64_t DVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	int iVar11;
	int iVar12;
	uint32_t* puVar13;
	int32_t DStack_70;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar2 = pUnit->dwClassId, iVar2 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)) ||
	    ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 == 0 ||
	                                                                                       (*(short*)(iVar2 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar12 = 1;
	if (0 < *(int*)(iVar2 + 0x60))
	{
		iVar12 = *(int*)(iVar2 + 0x60);
	}
	iVar4 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar4 % iVar12 == 0)
	{
		pDVar1 = &pUnit->pSeed;
		uVar6 = *(int*)(iVar2 + 0x58) * 2;
		uVar5 = uVar6 + 1;
		if ((int)uVar5 < 1)
		{
			uVar5 = 0;
		}
		else if ((uVar5 & uVar6) == 0)
		{
			uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
			uVar5 = uVar5 & uVar6;
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar5 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar5);
		}
		iVar12 = *(int*)(iVar2 + 0x58);
		uVar7 = iVar12 * 2;
		uVar6 = uVar7 + 1;
		if ((int)uVar6 < 1)
		{
			uVar6 = 0;
		}
		else if ((uVar6 & uVar7) == 0)
		{
			uVar6 = sub_6FAA88D0(&pDVar1->nLowSeed);
			uVar6 = uVar6 & uVar7;
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar6);
		}
		iVar4 = *(int*)(iVar2 + 0x58);
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DStack_70 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_70 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_70 + 2)) = 0;
		}
		else
		{
			DStack_70 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar10 = *(int*)(iVar2 + 0x5c) * 2;
		uVar7 = uVar10 + 1;
		if ((int)uVar7 < 1)
		{
			uVar7 = 0;
		}
		else if ((uVar7 & uVar10) == 0)
		{
			uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
			uVar7 = uVar7 & uVar10;
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar7 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar7);
		}
		iVar8 = (uVar7 - *(int*)(iVar2 + 0x5c)) + (int)DStack_70;
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DStack_70 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_70 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_70 + 2)) = 0;
		}
		else
		{
			DStack_70 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar10 = *(int*)(iVar2 + 0x5c) * 2;
		uVar7 = uVar10 + 1;
		if ((int)uVar7 < 1)
		{
			uVar10 = 0;
		}
		else if ((uVar7 & uVar10) == 0)
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar10 = uVar10 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			uVar10 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar7);
		}
		iVar11 = *(int*)(iVar2 + 0x5c);
		puVar13 = &uStack_5c;
		for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
		{
			*puVar13 = 0;
			puVar13 = puVar13 + 1;
		}
		iVar11 = (uVar10 - iVar11) + (int)DStack_70;
		uStack_5c = 0x21;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		iStack_40 = iVar8 + (uVar5 - iVar12);
		iStack_3c = iVar11 + (uVar6 - iVar4);
		iStack_48 = iVar8;
		iStack_44 = iVar11;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = (int)*(short*)(iVar2 + 0x1e);
		sub_6FB3E070(&uStack_5c);
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB33440
void __fastcall sub_6FB33440(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint64_t DVar4;
	uint64_t uVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;

	if (((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	    (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4;
		if (iVar2 != 0)
		{
			pDVar6 = sub_6FB26AD0((int)pUnit);
			if (pDVar6 == nullptr)
			{
				sub_6FB3D880(pUnit);
				return;
			}
			iVar3 = *(int*)(iVar2 + 0x60);
			if (0 < *(short*)(iVar2 + 0x1e))
			{
				iVar7 = MISSILE_GetTargetX(pUnit);
				if (iVar7 < 1)
				{
					sub_6FB33680(pDVar6, pUnit, (int)*(short*)(iVar2 + 0x1e), iVar3);
					iVar7 = *(int*)(iVar2 + 0x58);
				}
				MISSILE_SetTargetX(pUnit, iVar7 + -1);
			}
			if (0 < *(short*)(iVar2 + 0x20))
			{
				iVar7 = MISSILE_GetTargetY(pUnit);
				if (iVar7 < 1)
				{
					puVar10 = &uStack_5c;
					for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
					{
						*puVar10 = 0;
						puVar10 = puVar10 + 1;
					}
					uStack_5c = 0x102;
					iStack_4c = (int)*(short*)(iVar2 + 0x20);
					pDStack_58 = pDVar6;
					pDStack_54 = pUnit;
					iStack_30 = MISSILE_GetSkill(pUnit);
					DVar4 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar4;
					uVar9 = iVar3 * 2;
					uVar1 = uVar9 + 1;
					iStack_2c = (int)(((uint64_t)DVar4 & 0xffffffff) % 5) + 1;
					if ((int)uVar1 < 1)
					{
						uVar8 = 0;
					}
					else
					{
						uVar8 = (pUnit->pSeed).nLowSeed;
						uVar5 = (uint64_t)(pUnit->pSeed).nHighSeed;
						if ((uVar1 & uVar9) == 0)
						{
							DVar4 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar5);
							(*(uint64_t*)&pUnit->pSeed) = DVar4;
							uVar8 = uVar9 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
						}
						else
						{
							DVar4 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar5);
							(*(uint64_t*)&pUnit->pSeed) = DVar4;
							uVar8 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar1);
						}
					}
					iStack_40 = uVar8 - iVar3;
					if ((int)uVar1 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						uVar5 = (uint64_t)(pUnit->pSeed).nHighSeed;
						uVar8 = (pUnit->pSeed).nLowSeed;
						if ((uVar1 & uVar9) == 0)
						{
							DVar4 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar5);
							(*(uint64_t*)&pUnit->pSeed) = DVar4;
							uVar9 = uVar9 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
						}
						else
						{
							DVar4 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar5);
							(*(uint64_t*)&pUnit->pSeed) = DVar4;
							uVar9 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar1);
						}
					}
					iStack_3c = uVar9 - iVar3;
					if ((iStack_40 == 0) && (iStack_3c == 0))
					{
						uVar1 = iVar3 - 1;
						uVar9 = 0;
						if (0 < (int)uVar1)
						{
							uVar5 = (uint64_t)(pUnit->pSeed).nHighSeed;
							uVar9 = (pUnit->pSeed).nLowSeed;
							if ((uVar1 & iVar3 - 2U) == 0)
							{
								DVar4 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar5);
								(*(uint64_t*)&pUnit->pSeed) = DVar4;
								uVar9 = iVar3 - 2U & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
							}
							else
							{
								DVar4 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar5);
								(*(uint64_t*)&pUnit->pSeed) = DVar4;
								uVar9 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar1);
							}
						}
						iStack_40 = uVar9 + 1;
					}
					pDVar6 = sub_6FB3E070(&uStack_5c);
					if (pDVar6 != nullptr)
					{
						DVar4 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar4;
						MISSILE_SetTargetX(pDVar6, (int)(((uint64_t)DVar4 & 0xffffffff) % 5));
					}
					iVar7 = *(int*)(iVar2 + 0x5c);
				}
				MISSILE_SetTargetY(pUnit, iVar7 + -1);
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB33680
uint32_t* __fastcall sub_6FB33680(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3, int a4)
{
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	D2UnitStrc* pMissile;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	uint32_t local_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	puVar7 = &local_5c;
	for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar7 = 0;
		puVar7 = puVar7 + 1;
	}
	local_5c = 2;
	local_4c = a3;
	local_58 = pUnit;
	local_54 = pUnit2;
	iStack_30 = MISSILE_GetSkill(pUnit2);
	uStack_2c = MISSILE_GetLevel(pUnit2);
	uVar6 = a4 * 2;
	uVar1 = uVar6 + 1;
	if ((int)uVar1 < 1)
	{
		uVar5 = 0;
	}
	else
	{
		uVar5 = (pUnit2->pSeed).nLowSeed;
		uVar3 = (uint64_t)(pUnit2->pSeed).nHighSeed;
		if ((uVar1 & uVar6) == 0)
		{
			DVar2 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + uVar3);
			(*(uint64_t*)&pUnit2->pSeed) = DVar2;
			uVar5 = uVar6 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
		}
		else
		{
			DVar2 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + uVar3);
			(*(uint64_t*)&pUnit2->pSeed) = DVar2;
			uVar5 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar1);
		}
	}
	iStack_40 = uVar5 - a4;
	if ((int)uVar1 < 1)
	{
		uVar6 = 0;
	}
	else
	{
		uVar3 = (uint64_t)(pUnit2->pSeed).nHighSeed;
		uVar5 = (pUnit2->pSeed).nLowSeed;
		if ((uVar1 & uVar6) == 0)
		{
			DVar2 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + uVar3);
			(*(uint64_t*)&pUnit2->pSeed) = DVar2;
			uVar6 = uVar6 & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
		}
		else
		{
			DVar2 = (uint64_t)((uint64_t)uVar5 * 0x6ac690c5 + uVar3);
			(*(uint64_t*)&pUnit2->pSeed) = DVar2;
			uVar6 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar1);
		}
	}
	iStack_3c = uVar6 - a4;
	if ((iStack_40 == 0) && (iStack_3c == 0))
	{
		uVar1 = a4 - 1;
		uVar6 = 0;
		if (0 < (int)uVar1)
		{
			uVar3 = (uint64_t)(pUnit2->pSeed).nHighSeed;
			uVar6 = (pUnit2->pSeed).nLowSeed;
			if ((uVar1 & a4 - 2U) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pUnit2->pSeed) = DVar2;
				uVar6 = a4 - 2U & (*(uint32_t*)((uint8_t*)&DVar2 + 0));
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + uVar3);
				(*(uint64_t*)&pUnit2->pSeed) = DVar2;
				uVar6 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) % (uint64_t)uVar1);
			}
		}
		iStack_40 = uVar6 + 1;
	}
	pMissile = sub_6FB3E070(&local_5c);
	if (pMissile != nullptr)
	{
		MISSILE_SetTargetX(pMissile, iStack_40);
		MISSILE_SetTargetY(pMissile, iStack_3c);
	}
	return &pMissile->dwUnitType;
}

//D2Client.0x6FB337E0
void __fastcall sub_6FB337E0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t DVar6;
	int iVar7;
	int iVar8;
	uint32_t* puVar9;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar8 = pUnit->dwClassId, iVar8 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar8)) ||
	    (iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar8 * 0x1a4, iVar8 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar4 = sub_6FB26AD0((int)pUnit);
	if (pDVar4 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	if ((0 < *(short*)(iVar8 + 0x1e)) && (iVar5 = D2Common_10234(pUnit->pDynamicPath), iVar5 != 0))
	{
		puVar9 = &uStack_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		pDStack_58 = pDVar4;
		pDStack_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = (int)*(short*)(iVar8 + 0x1e);
		sub_6FB3E070(&uStack_5c);
	}
	iVar8 = *(int*)(iVar8 + 0x58);
	if (iVar8 < 1)
	{
		iVar8 = 1;
	}
	iVar5 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar5 % iVar8 != 0)
		goto LAB_6fb33997;
	iVar8 = MISSILE_GetTargetX(pUnit);
	iVar5 = MISSILE_GetTargetY(pUnit);
	DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
	(*(uint64_t*)&pUnit->pSeed) = DVar2;
	if (((uint64_t)DVar2 & 3) == 0)
	{
		iVar7 = -iVar5;
		iVar3 = iVar8;
	LAB_6fb338fc:
		iVar8 = (iVar7 + iVar8) * 3;
		iVar5 = (iVar5 + iVar3) * 3;
		iVar8 = (int)(iVar8 + (iVar8 >> 0x1f & 3U)) >> 2;
		iVar5 = (int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2;
	}
	else if (((*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 3) == 2)
	{
		iVar3 = -iVar8;
		iVar7 = iVar5;
		goto LAB_6fb338fc;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
	}
	else
	{
		DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar7 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar7 = 0;
	}
	else
	{
		iVar7 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar7 + iVar8, (int)DVar6 + iVar5);
	D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
	MISSILE_SetTargetX(pUnit, iVar8);
	MISSILE_SetTargetY(pUnit, iVar5);
LAB_6fb33997:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB339B0
void __fastcall sub_6FB339B0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int32_t DVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	    (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
		if ((iVar1 != 0) && (-1 < *(short*)(iVar1 + 0x1e)))
		{
			pDVar3 = sub_6FB26AD0((int)pUnit);
			if (pDVar3 == nullptr)
			{
				sub_6FB3D880(pUnit);
				return;
			}
			iVar4 = MISSILE_GetRemainingFrames(pUnit);
			if (iVar4 != *(int*)(iVar1 + 0x58))
			{
				sub_6FB3D880(pUnit);
				return;
			}
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar4 = pDVar3->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				iVar4 = 0;
			}
			else
			{
				iVar4 = PATH_GetXPosition(pDVar3->pDynamicPath);
			}
			uVar2 = pDVar3->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DVar5 = (*(int32_t*)&pDVar3->pDynamicPath->tTargetCoord);
			}
			else if (pDVar3->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
			}
			else
			{
				DVar5 = (int32_t)PATH_GetYPosition(pDVar3->pDynamicPath);
			}
			puVar7 = &uStack_5c;
			for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			uStack_5c = 0x2001;
			pDStack_58 = pDVar3;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iVar6 = 0;
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			do
			{
				iStack_48 = *(int*)((int)&dword_6FB70364 + iVar6) + iVar4;
				iStack_44 = *(int*)((int)&dword_6FB70374 + iVar6) + (int)DVar5;
				sub_6FB3E070(&uStack_5c);
				iVar6 = iVar6 + 4;
			} while (iVar6 < 0x10);
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB33B30
void __fastcall sub_6FB33B30(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, int a4)
{
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	uint32_t uVar11;
	uint32_t local_68;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((-1 < a3) && (a3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4, iVar1 != 0))
	{
		uVar5 = a4 * 7;
		local_68 = 8;
		if ((int)uVar5 < 9)
		{
			local_68 = uVar5;
		}
		if (0 < (int)local_68)
		{
			do
			{
				puVar10 = &local_5c;
				for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
				{
					*puVar10 = 0;
					puVar10 = puVar10 + 1;
				}
				local_58 = pUnit;
				local_54 = pUnit2;
				iStack_30 = MISSILE_GetSkill(pUnit2);
				uStack_2c = MISSILE_GetLevel(pUnit2);
				iStack_4c = a3;
				pDVar6 = sub_6FB3E070(&local_5c);
				if (pDVar6 != nullptr)
				{
					if ((int)uVar5 < 1)
					{
						uVar8 = 0;
					}
					else
					{
						uVar8 = (pUnit2->pSeed).nLowSeed;
						if ((uVar5 & uVar5 - 1) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar8 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar5);
						}
					}
					if ((int)uVar5 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						uVar9 = (pUnit2->pSeed).nLowSeed;
						if ((uVar5 & uVar5 - 1) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar9 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar5);
						}
					}
					uVar11 = *(uint32_t*)(iVar1 + 0x5c);
					if ((int)uVar11 < 1)
					{
						uVar11 = 0;
					}
					else
					{
						uVar4 = (uint64_t)(pUnit2->pSeed).nHighSeed;
						uVar2 = (pUnit2->pSeed).nLowSeed;
						if ((uVar11 & uVar11 - 1) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar11 = uVar11 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar2 * 0x6ac690c5 + uVar4);
							(*(uint64_t*)&pUnit2->pSeed) = DVar3;
							uVar11 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar11);
						}
					}
					sub_6FB5FB10((int)pDVar6);
					sub_6FB5FC80((int)pDVar6, uVar8 - (int)uVar5 / 2, uVar9 - (int)uVar5 / 2,
					    *(int*)(iVar1 + 0x58));
					sub_6FB5FCB0((int)pDVar6, 0, 0, uVar11, 1);
					sub_6FB5FD00((int)pDVar6, 0, 0, *(int*)(iVar1 + 0x60), 1);
				}
				local_68 = local_68 - 1;
			} while (local_68 != 0);
		}
	}
}

//D2Client.0x6FB33D50
void __fastcall sub_6FB33D50(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, uint32_t a4, int a5)
{
	uint64_t DVar1;
	uint64_t uVar2;
	int32_t DVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t* puVar9;
	bool bVar10;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (((-1 < a3) && (a3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4, iVar6 != 0))
	{
		if (0 < *(short*)(iVar6 + 0x1e))
		{
			sub_6FB33B30(pUnit, pUnit2, (int)*(short*)(iVar6 + 0x1e), a5);
		}
		if ((0 < *(short*)(iVar6 + 0x34)) && (a4 == 0x13b))
		{
			sub_6FB55820((int)*(short*)(iVar6 + 0x34), pUnit, 0.0, 0.0, 0);
		}
		uVar5 = a4 & 0x80000001;
		bVar10 = uVar5 == 0;
		if ((int)uVar5 < 0)
		{
			bVar10 = (uVar5 - 1 | 0xfffffffe) == 0xffffffff;
		}
		if (bVar10)
		{
			if (a5 < 3)
			{
				uVar5 = a4 & 0x8000000f;
				if ((int)uVar5 < 0)
				{
					uVar5 = (uVar5 - 1 | 0xfffffff0) + 1;
				}
				if (uVar5 != 0)
				{
					return;
				}
			}
			uVar5 = 4;
			if (a5 < 3)
			{
				uVar5 = 1;
			}
			else if (a5 < 6)
			{
				uVar5 = 2;
			}
			else if (a5 < 9)
			{
				uVar5 = 3;
			}
			iVar7 = 0;
			iVar6 = 0;
			if (1 < uVar5)
			{
				if (uVar5 == 0)
				{
					uVar8 = 0;
				}
				else
				{
					uVar2 = (uint64_t)(pUnit2->pSeed).nHighSeed;
					uVar8 = (pUnit2->pSeed).nLowSeed;
					if ((uVar5 & uVar5 - 1) == 0)
					{
						DVar1 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit2->pSeed) = DVar1;
						uVar8 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
					}
					else
					{
						DVar1 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit2->pSeed) = DVar1;
						uVar8 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar5);
					}
				}
				iVar7 = uVar8 - uVar5 / 2;
				if (uVar5 == 0)
				{
					uVar8 = 0;
				}
				else
				{
					uVar2 = (uint64_t)(pUnit2->pSeed).nHighSeed;
					uVar8 = (pUnit2->pSeed).nLowSeed;
					if ((uVar5 & uVar5 - 1) == 0)
					{
						DVar1 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit2->pSeed) = DVar1;
						uVar8 = uVar5 - 1 & (*(uint32_t*)((uint8_t*)&DVar1 + 0));
					}
					else
					{
						DVar1 = (uint64_t)((uint64_t)uVar8 * 0x6ac690c5 + uVar2);
						(*(uint64_t*)&pUnit2->pSeed) = DVar1;
						uVar8 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar5);
					}
				}
				iVar6 = uVar8 - uVar5 / 2;
			}
			puVar9 = &local_5c;
			for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 1;
			}
			local_5c = 1;
			local_58 = pUnit;
			iStack_30 = MISSILE_GetSkill(pUnit2);
			uStack_2c = MISSILE_GetLevel(pUnit2);
			uVar5 = pUnit2->dwUnitType;
			iStack_4c = a3;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				iStack_48 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				iStack_48 = 0;
			}
			else
			{
				iStack_48 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			iStack_48 = iStack_48 + iVar7;
			uVar5 = pUnit2->dwUnitType;
			if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
			{
				DVar3 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
			}
			else
			{
				DVar3 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iStack_44 = (int)DVar3 + iVar6;
			sub_6FB3E070(&local_5c);
		}
	}
}

//D2Client.0x6FB33F90
void __fastcall sub_6FB33F90(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, int a4)
{
	uint64_t DVar1;
	D2ActiveRoomStrc* pDVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	int32_t DVar8;
	D2UnitStrc* pDVar9;
	int iVar10;
	uint32_t* puVar11;
	uint32_t uStack_74;
	int iStack_70;
	int local_6c;
	D2ActiveRoomStrc** ppDStack_68;
	D2UnitStrc* local_64;
	int iStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((a3 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= a3)) ||
	        (iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4, iVar10 == 0)) ||
	    (local_6c = iVar10, local_64 = pUnit2, pDVar2 = UNITS_GetRoom(pUnit2),
	        pDVar2 == nullptr))
	{
		return;
	}
	if (a3 < *(short*)(iVar10 + 0x1e))
	{
		uVar3 = *(short*)(iVar10 + 0x1e) - a3;
		uVar4 = uVar3 + 1;
		if ((int)uVar4 < 1)
		{
			uVar5 = 0;
		}
		else if ((uVar4 & uVar3) == 0)
		{
			uVar5 = sub_6FAA88D0(&(pUnit2->pSeed).nLowSeed);
			uVar5 = uVar5 & uVar3;
		}
		else
		{
			uVar5 = sub_6FAA88D0(&(pUnit2->pSeed).nLowSeed);
			uVar5 = uVar5 % uVar4;
		}
		a3 = a3 + uVar5;
		if (a3 < 0)
		{
			return;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= a3)
		{
			return;
		}
		local_6c = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4;
		if (local_6c == 0)
		{
			return;
		}
	}
	puVar11 = &uStack_5c;
	for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
	{
		*puVar11 = 0;
		puVar11 = puVar11 + 1;
	}
	uStack_5c = 1;
	pDStack_58 = pUnit;
	iStack_4c = a3;
	iStack_30 = MISSILE_GetSkill(pUnit2);
	uStack_2c = MISSILE_GetLevel(pUnit2);
	iStack_70 = 0;
	iStack_60 = a4 * a4;
	do
	{
		uVar4 = a4 * 2;
		uVar3 = uVar4 + 1;
		iStack_70 = iStack_70 + 1;
		if ((int)uVar3 < 1)
		{
			uVar5 = 0;
		}
		else if ((uVar3 & uVar4) == 0)
		{
			uVar5 = sub_6FAA88D0(&(pUnit2->pSeed).nLowSeed);
			uVar5 = uVar5 & uVar4;
		}
		else
		{
			DVar1 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit2->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit2->pSeed) = DVar1;
			uVar5 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar3);
		}
		iVar10 = uVar5 - a4;
		if ((int)uVar3 < 1)
		{
			uVar3 = 0;
		}
		else if ((uVar3 & uVar4) == 0)
		{
			uVar3 = sub_6FAA88D0(&(pUnit2->pSeed).nLowSeed);
			uVar3 = uVar3 & uVar4;
		}
		else
		{
			DVar1 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit2->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit2->pSeed) = DVar1;
			uVar3 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar3);
		}
		iVar6 = uVar3 - a4;
		if (iVar6 * iVar6 + iVar10 * iVar10 <= iStack_60)
		{
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				iVar7 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				iVar7 = 0;
			}
			else
			{
				iVar7 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			iVar10 = iVar10 + iVar7;
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DVar8 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
			}
			else
			{
				DVar8 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iVar6 = iVar6 + (int)DVar8;
			pDVar2 = UNITS_GetRoom(pUnit2);
			if (pDVar2 != nullptr)
			{
				iVar7 = (pDVar2->tCoords).nSubtileX;
				if ((((iVar10 < iVar7) || ((pDVar2->tCoords).nSubtileWidth + iVar7 <= iVar10)) ||
				        (iVar7 = (pDVar2->tCoords).nSubtileY, iVar6 < iVar7)) ||
				    ((pDVar2->tCoords).nSubtileHeight + iVar7 <= iVar6))
				{
					ppDStack_68 = nullptr;
					uStack_74 = 0;
					DUNGEON_GetAdjacentRoomsListFromRoom(pDVar2, &ppDStack_68, (int*)&uStack_74);
					uVar3 = 0;
					if (uStack_74 != 0)
					{
						do
						{
							pDVar2 = ppDStack_68[uVar3];
							if (((pDVar2 != nullptr) &&
							        (iVar7 = (pDVar2->tCoords).nSubtileX, iVar7 <= iVar10)) &&
							    ((pUnit2 = local_64, iVar10 < (pDVar2->tCoords).nSubtileWidth + iVar7 &&
							                             ((iVar7 = (pDVar2->tCoords).nSubtileY, iVar7 <= iVar6 &&
							                                                                        (iVar6 < (pDVar2->tCoords).nSubtileHeight + iVar7))))))
							{
								pDVar2 = ppDStack_68[uVar3];
								goto LAB_6fb34256;
							}
							uVar3 = uVar3 + 1;
						} while (uVar3 < uStack_74);
					}
				}
				else
				{
				LAB_6fb34256:
					if (((pDVar2 != nullptr) &&
					        (iVar7 = COLLISION_CheckAnyCollisionWithPattern(pDVar2, iVar10, iVar6, 0, 1), iVar7 == 0)) &&
					    (iStack_48 = iVar10, iStack_44 = iVar6, pDVar9 = sub_6FB3E070(&uStack_5c),
					        pDVar9 != nullptr))
					{
						sub_6FB5FB10((int)pDVar9);
						iVar10 = local_6c;
						if (a4 != 6)
						{
							sub_6FB5FC80((int)pDVar9, 0, 0, *(int*)(local_6c + 0x58));
							sub_6FB5FCB0((int)pDVar9, 0, 0, -*(int*)(iVar10 + 0x5c), 1);
							return;
						}
						sub_6FB5FC80((int)pDVar9, 0, 0, *(int*)(local_6c + 0x58) * 2);
						sub_6FB5FCB0((int)pDVar9, 0, 0, *(int*)(iVar10 + 0x5c) * -2, 1);
						return;
					}
				}
			}
		}
		if (3 < iStack_70)
		{
			return;
		}
	} while (true);
}

//D2Client.0x6FB34300
void __fastcall sub_6FB34300(D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	int iVar6;
	bool bVar7;
	uint32_t uVar8;
	int iStack_8;

	if ((((pUnit == nullptr) || (iVar2 = pUnit->dwClassId, iVar2 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)) ||
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	pDVar4 = sub_6FB26AD0((int)pUnit);
	if (pDVar4 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	uVar5 = MISSILE_GetRemainingFrames(pUnit);
	if ((0 < *(short*)(iVar2 + 0x1e)) && (10 < (int)uVar5))
	{
		if ((int)uVar5 < 0x1e)
		{
		LAB_6fb343c9:
			iVar6 = 1;
		}
		else if ((int)uVar5 < 0x55)
		{
			iVar6 = (int)((uVar5 - 0xf) + ((int)(uVar5 - 0xf) >> 0x1f & 3U)) >> 2;
		}
		else
		{
			iVar6 = *(short*)(iVar2 + 0x96) + -0x32;
			if ((int)uVar5 < iVar6)
			{
				iVar6 = 0xc;
			}
			else
			{
				if ((int)*(short*)(iVar2 + 0x96) <= (int)uVar5)
					goto LAB_6fb343c9;
				iVar6 = uVar5 - iVar6;
				iVar6 = 0xc - ((int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
			}
		}
		sub_6FB33D50(pDVar4, pUnit, (int)*(short*)(iVar2 + 0x1e), uVar5, iVar6);
	}
	iStack_8 = 1;
	if (0 < *(int*)(iVar2 + 0x58))
	{
		iStack_8 = *(int*)(iVar2 + 0x58);
	}
	if ((0 < *(short*)(iVar2 + 0x20)) && ((int)uVar5 % iStack_8 == 0))
	{
		sub_6FB33680(pDVar4, pUnit, (int)*(short*)(iVar2 + 0x20), 0x14);
	}
	iVar6 = *(int*)(iVar2 + 0x5c);
	if ((0 < iVar6) && (uVar5 == 0x5a))
	{
		iVar3 = ((iVar6 / 3) * 25000) / 0x19;
		sub_6FAB7E70(8, iVar3, ((iVar6 * 5 + (iVar6 / 3) * -10) * 5000) / 0x19, iVar3);
	}
	sVar1 = *(short*)(iVar2 + 0x22);
	if (((0 < sVar1) && (0x73 < (int)uVar5)) && ((int)uVar5 < 0x13b))
	{
		if (((int)uVar5 < 0xc9) || (0xe0 < (int)uVar5))
		{
			uVar5 = uVar5 & 0x80000003;
			bVar7 = uVar5 == 0;
			if ((int)uVar5 < 0)
			{
				bVar7 = (uVar5 - 1 | 0xfffffffc) == 0xffffffff;
			}
			if (!bVar7)
				goto LAB_6fb344ef;
			uVar8 = 0x14;
		}
		else
		{
			sub_6FB33F90(pDVar4, pUnit, (int)sVar1, 6);
			uVar8 = 6;
		}
		sub_6FB33F90(pDVar4, pUnit, (int)sVar1, uVar8);
	}
LAB_6fb344ef:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB34500
void __fastcall sub_6FB34500(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint64_t DVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int32_t DVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	    (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4;
		if ((iVar2 != 0) && (-1 < *(short*)(iVar2 + 0x1e)))
		{
			iVar5 = MISSILE_GetRemainingFrames(pUnit);
			if (iVar5 == *(int*)(iVar2 + 0x58))
			{
				MISSILE_SetTargetY(pUnit, 1);
			}
			iVar6 = MISSILE_GetTargetY(pUnit);
			if (iVar6 != 0)
			{
				iVar6 = 1;
				if (0 < *(int*)(iVar2 + 0x5c))
				{
					iVar6 = *(int*)(iVar2 + 0x5c);
				}
				if (iVar5 % iVar6 == 0)
				{
					iVar5 = *(int*)(iVar2 + 0x60);
					pDVar1 = &pUnit->pSeed;
					uVar3 = iVar5 * 2;
					uVar8 = uVar3 + 1;
					if ((int)uVar8 < 1)
					{
						uVar7 = 0;
					}
					else if ((uVar8 & uVar3) == 0)
					{
						uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
						uVar7 = uVar7 & uVar3;
					}
					else
					{
						DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						*(uint64_t*)pDVar1 = DVar4;
						uVar7 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar8);
					}
					if ((int)uVar8 < 1)
					{
						uVar8 = 0;
					}
					else if ((uVar8 & uVar3) == 0)
					{
						uVar8 = sub_6FAA88D0(&pDVar1->nLowSeed);
						uVar8 = uVar8 & uVar3;
					}
					else
					{
						DVar4 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						*(uint64_t*)pDVar1 = DVar4;
						uVar8 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar8);
					}
					puVar10 = &uStack_5c;
					for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
					{
						*puVar10 = 0;
						puVar10 = puVar10 + 1;
					}
					uStack_5c = 0x21;
					pDStack_58 = sub_6FB26AD0((int)pUnit);
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						iStack_48 = 0;
					}
					else
					{
						iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
					}
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
					}
					else
					{
						DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
					}
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iStack_40 = pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						iStack_40 = 0;
					}
					else
					{
						iStack_40 = PATH_GetXPosition(pUnit->pDynamicPath);
					}
					iStack_40 = iStack_40 + (uVar7 - iVar5);
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						DVar9 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
					}
					else
					{
						DVar9 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
					}
					iStack_3c = (int)DVar9 + (uVar8 - iVar5);
					iStack_30 = MISSILE_GetSkill(pUnit);
					uStack_2c = MISSILE_GetLevel(pUnit);
					iStack_4c = (int)*(short*)(iVar2 + 0x1e);
					sub_6FB3E070(&uStack_5c);
				}
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB34760
void __fastcall sub_6FB34760(D2UnitStrc* pUnit)
{
	D2UnitStrc* pMountUnit;
	int iVar1;

	pMountUnit = sub_6FB26AD0((int)pUnit);
	if (pMountUnit == nullptr)
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	if ((-1 < (int)pMountUnit->dwUnitType) && ((int)pMountUnit->dwUnitType < 2))
	{
		iVar1 = sub_6FB29550((int*)pMountUnit);
		if (iVar1 != 0)
		{
			sub_6FB3DC50(pUnit, nullptr, 0);
			return;
		}
	}
	D2Common_10235_PATH_UpdateRiderPath(pUnit, pMountUnit);
	UNITS_UpdateFrame(pUnit);
}

//D2Client.0x6FB347B0
void __fastcall sub_6FB347B0(D2UnitStrc* pUnit2)
{
	short sVar1;
	D2UnitStrc* pUnit;
	D2SkillStrc* pSkill;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (pUnit2 == nullptr)
	{
		sub_6FB26C70(0xffffffff, 6);
		return;
	}
	iVar6 = pUnit2->dwClassId;
	if (((((-1 < iVar6) && (iVar6 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	         (iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4, iVar6 != 0)) &&
	        ((-1 < *(short*)(iVar6 + 0x1e) &&
	            (pUnit = sub_6FB26AD0((int)pUnit2), pUnit != nullptr)))) &&
	    (pSkill = UNITS_GetUsedSkill(pUnit), pSkill != nullptr))
	{
		iVar2 = SKILLS_GetSkillIdFromSkill(pSkill, __FILE__, __LINE__);
		iVar3 = MISSILE_GetSkill(pUnit2);
		if (iVar2 == iVar3)
		{
			iVar2 = D2Common_10234(pUnit2->pDynamicPath);
			if (iVar2 != 0)
			{
				uVar4 = MISSILE_GetLevel(pUnit2);
				iVar2 = MISSILE_GetSkill(pUnit2);
				sVar1 = *(short*)(iVar6 + 0x1e);
				pDVar5 = pUnit2;
				if (((pUnit2->dwUnitType == 0) || (pUnit2->dwUnitType == 1)) ||
				    (pDVar5 = sub_6FB26AD0((int)pUnit2), pDVar5 != nullptr))
				{
					puVar7 = &uStack_5c;
					for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
					{
						*puVar7 = 0;
						puVar7 = puVar7 + 1;
					}
					uStack_5c = 0x20;
					uStack_40 = 0;
					uStack_3c = 0;
					pDStack_58 = pDVar5;
					pDStack_54 = pUnit2;
					iStack_4c = (int)sVar1;
					iStack_30 = iVar2;
					uStack_2c = uVar4;
					sub_6FB3E070(&uStack_5c);
				}
			}
			D2Common_10235_PATH_UpdateRiderPath(pUnit2, pUnit);
			sub_6FB3D880(pUnit2);
			return;
		}
	}
	sub_6FB26C70(pUnit2->dwUnitId, pUnit2->dwUnitType);
}

//D2Client.0x6FB348F0
void __fastcall sub_6FB348F0(D2UnitStrc* pUnit)
{
	int iVar1;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x1e)))))
	{
		sub_6FB30470(pUnit, *(uint32_t*)(iVar1 + 0x58), *(uint32_t*)(iVar1 + 0x5c),
		    *(uint32_t*)(iVar1 + 0x60), (int)*(short*)(iVar1 + 0x1e));
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB34960
void __fastcall sub_6FB34960(D2UnitStrc* pUnit)
{
	int iVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;
	uint32_t uStack_28;

	if (pUnit == nullptr)
	{
		sub_6FB26C70(0xffffffff, 6);
		return;
	}
	iVar1 = pUnit->dwClassId;
	if ((-1 < iVar1) && (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
		if ((iVar1 != 0) &&
		    ((-1 < *(short*)(iVar1 + 0x1e) &&
		        (pDynamicPath = pUnit->pDynamicPath, pDynamicPath != nullptr))))
		{
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar3 = pDynamicPath->dwClientCoordY;
			}
			else
			{
				iVar3 = PATH_GetXPosition(pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iVar5 = MISSILE_GetRemainingFrames(pUnit);
			if (iVar5 < 2)
			{
				iVar5 = D2COMMON_10175_PathGetFirstPointX(pUnit->pDynamicPath);
				iVar6 = D2COMMON_10176_PathGetFirstPointY(pUnit->pDynamicPath);
				MISSILE_SetTargetX(pUnit, -(iVar6 - (int)DVar4));
				MISSILE_SetTargetY(pUnit, iVar5 - iVar3);
			}
			iVar5 = D2Common_10234(pUnit->pDynamicPath);
			if (iVar5 != 0)
			{
				puVar7 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uStack_5c = 0xb;
				pDStack_58 = sub_6FB26AD0((int)pUnit);
				iStack_48 = iVar3;
				DStack_44 = DVar4;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar1 + 0x1e);
				uStack_28 = *(uint32_t*)(iVar1 + 0x58);
				iStack_40 = MISSILE_GetTargetX(pUnit);
				iStack_3c = MISSILE_GetTargetY(pUnit);
				sub_6FB3E070(&uStack_5c);
				iStack_40 = MISSILE_GetTargetX(pUnit);
				iStack_40 = -iStack_40;
				iStack_3c = MISSILE_GetTargetY(pUnit);
				iStack_3c = -iStack_3c;
				sub_6FB3E070(&uStack_5c);
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB26C70(pUnit->dwUnitId, pUnit->dwUnitType);
}

//D2Client.0x6FB34B00
void __fastcall sub_6FB34B00(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	uint32_t uStack_28;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (*(short*)(iVar1 + 0x1e) != 0))))
	{
		iVar3 = D2Common_10234(pUnit->pDynamicPath);
		if (iVar3 != 0)
		{
			puVar4 = &uStack_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			uStack_5c = 9;
			pDStack_58 = sub_6FB26AD0((int)pUnit);
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_48 = 0;
			}
			else
			{
				iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
			}
			else
			{
				DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			uStack_28 = *(uint32_t*)(iVar1 + 0x58);
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			sub_6FB3E070(&uStack_5c);
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB34C30
void __fastcall sub_6FB34C30(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	int nTargetX;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		if (0 < *(short*)(iVar1 + 0x34))
		{
			iVar2 = MISSILE_GetTargetX(pUnit);
			nTargetX = sub_6FB5FDD0((int)pUnit);
			if ((iVar2 != 0) && (iVar2 != nTargetX))
			{
				sub_6FB55820((int)*(short*)(iVar1 + 0x34), pUnit, 0.0, 0.0, 0);
			}
			MISSILE_SetTargetX(pUnit, nTargetX);
		}
		sub_6FB30820(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB34CC0
void __fastcall sub_6FB34CC0(D2UnitStrc* pUnit)
{
	D2SeedStrc* pSeed;
	int iVar1;
	int64_t lVar2;
	uint64_t DVar3;
	uint16_t uVar4;
	D2UnitStrc* pDVar5;
	D2ActiveRoomStrc* pRoom;
	int iVar6;
	uint32_t uVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	int iVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	uint32_t* puVar13;
	int32_t DStack_70;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (((((((pUnit == nullptr) || (iVar1 = pUnit->dwClassId, iVar1 < 0)) ||
	           (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	          ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0 ||
	                                                                                             (*(short*)(iVar1 + 0x1e) < 0)))) ||
	         ((pDVar5 = sub_6FB26AD0((int)pUnit), pDVar5 == nullptr ||
	                                                  ((pRoom = UNITS_GetRoom(pUnit), pRoom == nullptr ||
	                                                                                      (iVar6 = MISSILE_GetSkill(pUnit), iVar6 < 0)))))) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar6)) ||
	    (iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar6 * 0x23c, iVar10 == 0))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	uVar7 = MISSILE_GetLevel(pUnit);
	uVar12 = *(uint32_t*)(iVar10 + 0x138);
	iVar9 = iVar6;
	uVar11 = uVar7;
	pDVar8 = sub_6FB26AD0((int)pUnit);
	iVar9 = SKILLS_EvaluateSkillFormula(pDVar8, uVar12, iVar9, uVar11);
	uVar12 = *(uint32_t*)(iVar10 + 0x13c);
	pDVar8 = sub_6FB26AD0((int)pUnit);
	iVar6 = SKILLS_EvaluateSkillFormula(pDVar8, uVar12, iVar6, uVar7);
	if (iVar6 < 1)
	{
		iVar6 = 1;
	}
	iVar10 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar10 % iVar6 == 0)
	{
		uVar12 = pUnit->dwUnitType;
		pSeed = &pUnit->pSeed;
		if ((uVar12 == 2) || ((3 < (int)uVar12 && ((int)uVar12 < 6))))
		{
			iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		SEED_InitLowSeed(pSeed, iVar6 + iVar10);
		uVar12 = pUnit->dwUnitType;
		iVar9 = iVar9 + -1;
		if ((uVar12 == 2) || ((3 < (int)uVar12 && ((int)uVar12 < 6))))
		{
			DStack_70 = (int32_t)pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_70 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_70 + 2)) = 0;
		}
		else
		{
			DStack_70 = (int32_t)PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar12 = iVar9 * 2;
		if ((int)uVar12 < 1)
		{
			uVar11 = 0;
		}
		else if ((uVar12 & uVar12 - 1) == 0)
		{
			DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pSeed = DVar3;
			uVar11 = uVar12 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
		}
		else
		{
			DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pSeed = DVar3;
			uVar11 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar12);
		}
		uVar7 = pUnit->dwUnitType;
		iVar6 = (uVar11 - iVar9) + (int)DStack_70;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DStack_70 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_70 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_70 + 2)) = 0;
		}
		else
		{
			DStack_70 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		if ((int)uVar12 < 1)
		{
			uVar12 = 0;
		}
		else
		{
			lVar2 = (uint64_t)pSeed->nLowSeed * 0x6ac690c5;
			uVar11 = (pUnit->pSeed).nHighSeed;
			if ((uVar12 & uVar12 - 1) == 0)
			{
				DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar11);
				*(uint64_t*)pSeed = DVar3;
				uVar12 = uVar12 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			else
			{
				DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar11);
				*(uint64_t*)pSeed = DVar3;
				uVar12 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar12);
			}
		}
		iVar10 = (uVar12 - iVar9) + (int)DStack_70;
		uVar4 = COLLISION_CheckMask(pRoom, iVar6, iVar10, 0x45);
		if (uVar4 == 0)
		{
			puVar13 = &uStack_5c;
			for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
			{
				*puVar13 = 0;
				puVar13 = puVar13 + 1;
			}
			uStack_5c = 0x2001;
			pDStack_58 = pDVar5;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			iStack_48 = iVar6;
			iStack_44 = iVar10;
			pDVar5 = sub_6FB3E070(&uStack_5c);
			if (pDVar5 != nullptr)
			{
				sub_6FB29540((int)pDVar5);
			}
			if (-1 < *(short*)(iVar1 + 0x20))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x20);
				sub_6FB3E070(&uStack_5c);
			}
			sub_6FB3D880(pUnit);
			return;
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB34FF0
void __fastcall sub_6FB34FF0(D2UnitStrc* pUnit)
{
	short sVar1;
	uint8_t nDirection;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar4 = pUnit->dwClassId, iVar4 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4)) ||
	    ((iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4, iVar4 == 0 ||
	                                                                                       (*(short*)(iVar4 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit);
		return;
	}
	iVar2 = MISSILE_GetRemainingFrames(pUnit);
	iVar6 = *(int*)(iVar4 + 0x58);
	if (iVar6 < 1)
	{
		iVar6 = 1;
	}
	if (iVar2 % iVar6 == 0)
	{
		sVar1 = *(short*)(iVar4 + 0x1e);
		uVar3 = MISSILE_GetLevel(pUnit);
		iVar4 = MISSILE_GetSkill(pUnit);
		pDVar5 = pUnit;
		if ((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1))
		{
			pDVar5 = sub_6FB26AD0((int)pUnit);
			if (pDVar5 == nullptr)
				goto LAB_6fb350ef;
		}
		puVar7 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		uStack_40 = 0;
		uStack_3c = 0;
		uStack_5c = 0x20;
		pDStack_58 = pDVar5;
		pDStack_54 = pUnit;
		iStack_4c = (int)sVar1;
		iStack_30 = iVar4;
		uStack_2c = uVar3;
		pDVar5 = sub_6FB3E070(&uStack_5c);
		if (pDVar5 != nullptr)
		{
			nDirection = PATH_GetDirection(pUnit->pDynamicPath);
			PATH_SetDirection(pDVar5->pDynamicPath, nDirection);
		}
	}
LAB_6fb350ef:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB35110
void __fastcall sub_6FB35110(D2UnitStrc* pUnit2)
{
	D2SeedStrc* pSeed;
	int iVar1;
	int64_t lVar2;
	uint64_t DVar3;
	int iVar4;
	uint32_t nSkillLevel;
	D2UnitStrc* pUnit;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	int iStack_14;
	int32_t DStack_10;

	if ((((pUnit2 == nullptr) || (iVar1 = pUnit2->dwClassId, iVar1 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0 ||
	                                                                                       (*(short*)(iVar1 + 0x1e) < 0))))
	{
		sub_6FB3DBB0(pUnit2);
		return;
	}
	iVar4 = MISSILE_GetSkill(pUnit2);
	if (((-1 < iVar4) && (iVar4 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
	    (iVar9 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar4 * 0x23c, iVar9 != 0))
	{
		nSkillLevel = MISSILE_GetLevel(pUnit2);
		pUnit = sub_6FB26AD0((int)pUnit2);
		iStack_14 = *(int*)(iVar1 + 0x5c);
		if ((iStack_14 < 1) &&
		    (iStack_14 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 100), iVar4, nSkillLevel),
		        iStack_14 < 1))
		{
			iStack_14 = 1;
		}
		iVar5 = *(int*)(iVar1 + 0x58);
		if ((iVar5 < 1) &&
		    (iVar5 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar9 + 0x144), iVar4, nSkillLevel),
		        iVar5 < 1))
		{
			iVar5 = 1;
		}
		iVar4 = MISSILE_GetRemainingFrames(pUnit2);
		if (((*(int*)(iVar1 + 0x60) < iVar4) && (iVar4 < *(int*)(iVar1 + 100))) &&
		    (iVar4 % iVar5 == 0))
		{
			pSeed = &pUnit2->pSeed;
			iVar4 = MISSILE_GetTargetX(pUnit2);
			SEED_InitLowSeed(pSeed, iVar4);
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_10 = (int32_t)pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_10 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_10 + 2)) = 0;
			}
			else
			{
				DStack_10 = (int32_t)PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar8 = iStack_14 * 2;
			uVar6 = uVar8 + 1;
			if ((int)uVar6 < 1)
			{
				uVar7 = 0;
			}
			else if ((uVar6 & uVar8) == 0)
			{
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				uVar7 = uVar8 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
			}
			else
			{
				DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
				*(uint64_t*)pSeed = DVar3;
				uVar7 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar6);
			}
			iVar4 = (uVar7 - iStack_14) + (int)DStack_10;
			uVar7 = pUnit2->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				DStack_10 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_10 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_10 + 2)) = 0;
			}
			else
			{
				DStack_10 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			if ((int)uVar6 < 1)
			{
				uVar8 = 0;
			}
			else
			{
				lVar2 = (uint64_t)pSeed->nLowSeed * 0x6ac690c5;
				uVar7 = (pUnit2->pSeed).nHighSeed;
				if ((uVar6 & uVar8) == 0)
				{
					DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar7);
					*(uint64_t*)pSeed = DVar3;
					uVar8 = uVar8 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
				}
				else
				{
					DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar7);
					*(uint64_t*)pSeed = DVar3;
					uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar6);
				}
			}
			uVar6 = SEED_GetLowSeed(pSeed);
			MISSILE_SetTargetX(pUnit2, uVar6);
			iVar9 = *(int*)(iVar1 + 0x68);
			iVar5 = MISSILE_GetSkill(pUnit2);
			sub_6FB3EBE0(pUnit2, (int)*(short*)(iVar1 + 0x1e), 0, 0, iVar4,
			    (uVar8 - iStack_14) + (int)DStack_10, iVar5, nSkillLevel, iVar9);
		}
		sub_6FB3D880(pUnit2);
		return;
	}
	sub_6FB3DBB0(pUnit2);
}

//D2Client.0x6FB353C0
void __fastcall sub_6FB353C0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint32_t uVar4;
	int iVar5;
	int32_t DVar6;
	D2UnitStrc* pDVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	int iStack_70;
	int iStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		iVar5 = MISSILE_GetRemainingFrames(pUnit);
		if ((-1 < *(short*)(iVar1 + 0x1e)) && (iVar5 == *(int*)(iVar1 + 0x58)))
		{
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iStack_70 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_70 = 0;
			}
			else
			{
				iStack_70 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath != nullptr)
			{
				DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			puVar10 = &uStack_5c;
			for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			uStack_5c = 0x2001;
			pDStack_58 = sub_6FB26AD0((int)pUnit);
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iStack_48 = iStack_70;
			DStack_44 = DVar6;
			sub_6FB3E070(&uStack_5c);
			iVar8 = *(int*)(iVar1 + 100);
			iStack_64 = 0;
			if (0 < *(int*)(iVar1 + 0x60))
			{
				uVar4 = iVar8 * 2;
				uVar2 = uVar4 + 1;
				do
				{
					if ((int)uVar2 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						uVar9 = (pUnit->pSeed).nLowSeed;
						if ((uVar2 & uVar4) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
						}
					}
					iStack_48 = (uVar9 - iVar8) + iStack_70;
					if ((int)uVar2 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						uVar9 = (pUnit->pSeed).nLowSeed;
						if ((uVar2 & uVar4) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
						}
					}
					DStack_44 = (int32_t)((uVar9 - iVar8) + (int)DVar6);
					sub_6FB3E070(&uStack_5c);
					iStack_64 = iStack_64 + 1;
				} while (iStack_64 < *(int*)(iVar1 + 0x60));
			}
		}
		if ((-1 < *(short*)(iVar1 + 0x20)) && (iVar5 == *(int*)(iVar1 + 0x5c)))
		{
			pDVar7 = sub_6FB26AD0((int)pUnit);
			if (pDVar7 != nullptr)
			{
				pDVar7->dwFlagEx = pDVar7->dwFlagEx | 0x40000;
				puVar10 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar10 = 0;
					puVar10 = puVar10 + 1;
				}
				iStack_4c = (int)*(short*)(iVar1 + 0x20);
				uStack_5c = 0x2000;
				pDStack_58 = pDVar7;
				pDStack_54 = pUnit;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				pDVar7 = sub_6FB3E070(&uStack_5c);
				if ((pDVar7 != nullptr) && (0 < *(short*)(iVar1 + 0x34)))
				{
					sub_6FB55820((int)*(short*)(iVar1 + 0x34), pDVar7, 0.0, 0.0, 0);
				}
			}
		}
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB35670
void __fastcall sub_6FB35670(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	    (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
		if ((iVar1 != 0) && (-1 < *(short*)(iVar1 + 0x1e)))
		{
			pDVar2 = sub_6FB26AD0((int)pUnit);
			if (pDVar2 != nullptr)
			{
				iVar3 = D2Common_10234(pUnit->pDynamicPath);
				if (iVar3 != 0)
				{
					iVar3 = MISSILE_GetTargetX(pUnit);
					iVar4 = MISSILE_GetTargetY(pUnit);
					puVar6 = &uStack_5c;
					for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
					{
						*puVar6 = 0;
						puVar6 = puVar6 + 1;
					}
					uStack_5c = 2;
					pDStack_58 = pDVar2;
					pDStack_54 = pUnit;
					iStack_30 = MISSILE_GetSkill(pUnit);
					uStack_2c = MISSILE_GetLevel(pUnit);
					iStack_4c = (int)*(short*)(iVar1 + 0x1e);
					iStack_40 = iVar3;
					iStack_3c = iVar4;
					sub_6FB3E070(&uStack_5c);
					iStack_40 = -iVar3;
					iStack_3c = -iVar4;
					sub_6FB3E070(&uStack_5c);
				}
				sub_6FB3D880(pUnit);
				return;
			}
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB35780
void __fastcall sub_6FB35780(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x1e)))))
	{
		iVar2 = D2Common_10234(pUnit->pDynamicPath);
		if (iVar2 != 0)
		{
			puVar3 = &uStack_5c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*puVar3 = 0;
				puVar3 = puVar3 + 1;
			}
			pDStack_58 = sub_6FB26AD0((int)pUnit);
			pDStack_54 = pUnit;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			sub_6FB3E070(&uStack_5c);
		}
		sub_6FB30AD0(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB35840
void __fastcall sub_6FB35840(D2UnitStrc* pUnit)
{
	D2SeedStrc* pSeed;
	int iVar1;
	uint32_t uVar2;
	int64_t lVar3;
	uint64_t DVar4;
	int iVar5;
	int nLowSeed;
	D2UnitStrc* pDVar6;
	short* psVar7;
	int* piVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	    (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
		if (iVar1 != 0)
		{
			iVar5 = MISSILE_GetRemainingFrames(pUnit);
			uVar9 = 0;
			piVar8 = (int*)(iVar1 + 0x5c);
			psVar7 = (short*)(iVar1 + 0x1e);
			do
			{
				if ((*psVar7 < 0) || (*piVar8 < 1))
					break;
				uVar9 = uVar9 + 1;
				psVar7 = psVar7 + 1;
				piVar8 = piVar8 + 1;
			} while ((int)uVar9 < 3);
			if ((int)uVar9 < 1)
			{
				sub_6FB3DC50(pUnit, nullptr, 0);
				return;
			}
			if (*(int*)(iVar1 + 0x58) <= iVar5)
			{
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					nLowSeed = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					nLowSeed = 0;
				}
				else
				{
					nLowSeed = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				pSeed = &pUnit->pSeed;
				SEED_InitLowSeed(pSeed, nLowSeed);
				lVar3 = (uint64_t)pSeed->nLowSeed * 0x6ac690c5;
				uVar2 = (pUnit->pSeed).nHighSeed;
				if ((uVar9 & uVar9 - 1) == 0)
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar2);
					*(uint64_t*)pSeed = DVar4;
					uVar9 = uVar9 - 1 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
				}
				else
				{
					DVar4 = (uint64_t)(lVar3 + (uint64_t)uVar2);
					*(uint64_t*)pSeed = DVar4;
					uVar9 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar9);
				}
				if (iVar5 % *(int*)(iVar1 + 0x5c + uVar9 * 4) == 0)
				{
					puVar10 = &uStack_5c;
					for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
					{
						*puVar10 = 0;
						puVar10 = puVar10 + 1;
					}
					pDStack_58 = sub_6FB26AD0((int)pUnit);
					pDStack_54 = pUnit;
					iStack_30 = MISSILE_GetSkill(pUnit);
					uStack_2c = MISSILE_GetLevel(pUnit);
					iStack_4c = (int)*(short*)(iVar1 + 0x1e + uVar9 * 2);
					pDVar6 = sub_6FB3E070(&uStack_5c);
					if (pDVar6 != nullptr)
					{
						sub_6FB3DC50(pDVar6, nullptr, 1);
					}
				}
			}
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB359C0
void __fastcall sub_6FB359C0(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pMountUnit;
	int iVar3;
	int iVar4;
	int* piVar5;
	int local_64;
	int local_60[2];
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((((pUnit == nullptr) || (iVar1 = pUnit->dwClassId, iVar1 < 0)) ||
	         (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar1)) ||
	        ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 == 0 ||
	                                                                                           (*(short*)(iVar1 + 0x1e) < 0)))) ||
	    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))
	{
		sub_6FB3DBB0(pUnit);
	}
	else
	{
		pMountUnit = sub_6FB26AD0((int)pUnit);
		if (pMountUnit == nullptr)
		{
			sub_6FB3DBB0(pUnit);
		}
		else if ((((int)pMountUnit->dwUnitType < 0) || (1 < (int)pMountUnit->dwUnitType)) ||
		         (iVar3 = sub_6FB29550((int*)pMountUnit), iVar3 == 0))
		{
			D2Common_10235_PATH_UpdateRiderPath(pUnit, pMountUnit);
			UNITS_UpdateFrame(pUnit);
		}
		else
		{
			sub_6FB3DC50(pUnit, nullptr, 0);
		}
		iVar3 = sub_6FABA950(pDVar2, &local_64, local_60);
		if (iVar3 != 0)
		{
			iVar3 = MISSILE_GetTargetY(pUnit);
			iVar4 = MISSILE_GetTargetX(pUnit);
			if (iVar3 < iVar4)
			{
				MISSILE_SetTargetY(pUnit, iVar3 + 1);
			}
			piVar5 = local_60;
			for (iVar3 = 0x17; piVar5 = piVar5 + 1, iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*piVar5 = 0;
			}
			local_60[1] = 0x20;
			iStack_40 = local_64;
			iStack_3c = local_60[0];
			pDStack_58 = pDVar2;
			pDStack_54 = pDVar2;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iStack_4c = (int)*(short*)(iVar1 + 0x1e);
			pDVar2 = sub_6FB3E070((uint32_t*)(local_60 + 1));
			if (pDVar2 != nullptr)
			{
				PATH_SetType(pDVar2->pDynamicPath, 0xe);
				D2Common_10142(pDVar2->pDynamicPath, pDVar2, 0);
			}
			MISSILE_SetTargetY(pUnit, 0);
			sub_6FB3D880(pUnit);
			return;
		}
	}
}

//D2Client.0x6FB35B40
void __fastcall sub_6FB35B40(D2UnitStrc* pUnit)
{
	D2SeedStrc* pSeed;
	uint64_t DVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	int32_t DStack_8;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0))
	{
		iVar2 = *(int*)(iVar2 + 0x38);
		iVar6 = 1;
		if (0 < iVar2)
		{
			iVar6 = iVar2;
		}
		iVar2 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar2 % iVar6 != 0)
		{
			sub_6FB3D880(pUnit);
			return;
		}
		pSeed = &pUnit->pSeed;
		if (pSeed != nullptr)
		{
			iVar2 = MISSILE_GetTargetX(pUnit);
			SEED_InitLowSeed(pSeed, iVar2);
			iVar2 = MISSILE_GetTargetY(pUnit);
			iVar6 = (int)(short)iVar2;
			iVar2 = (int)(short)((uint32_t)iVar2 >> 0x10);
			DVar1 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pSeed = DVar1;
			if (((uint64_t)DVar1 & 1) == 0)
			{
				iVar5 = -iVar6;
				iVar3 = iVar2;
			}
			else
			{
				iVar3 = -iVar2;
				iVar5 = iVar6;
			}
			iVar3 = iVar3 + iVar6 * 4;
			iVar5 = iVar5 + iVar2 * 4;
			uVar7 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
			iVar2 = (int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2;
			if (uVar7 == 0)
			{
				uVar7 = 1;
			}
			if (iVar2 == 0)
			{
				iVar2 = 1;
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				DStack_8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_8 + 2)) = 0;
			}
			else
			{
				DStack_8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iVar6 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			D2COMMON_10170_PathSetTargetPos(pUnit->pDynamicPath, iVar6 + uVar7, (int)DStack_8 + iVar2);
			D2Common_10142(pUnit->pDynamicPath, pUnit, 0);
			uVar4 = SEED_GetLowSeed(pSeed);
			MISSILE_SetTargetX(pUnit, uVar4);
			MISSILE_SetTargetY(pUnit, iVar2 * 0x10000 + (uVar7 & 0xffff));
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB35D10
void __fastcall sub_6FB35D10(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5, uint32_t a6, uint32_t a7, uint32_t a8, int a9)
{
	uint32_t uVar1;
	int iVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	int iVar5;
	D2ActiveRoomStrc** ppDVar6;
	D2ActiveRoomStrc* pDVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	int local_7c;
	uint32_t uStack_78;
	D2ActiveRoomStrc** ppDStack_74;
	int local_70;
	int local_6c;
	int local_68;
	int local_64;
	int local_60;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	int local_4c;
	D2ActiveRoomStrc** local_48;
	int local_44;
	uint32_t local_30;
	uint32_t local_2c;
	uint32_t local_1c;

	if ((a5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= a5))
	{
		local_7c = 0;
	}
	else
	{
		local_7c = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a5 * 0x1a4;
	}
	local_64 = a2;
	if (((pUnit != nullptr) &&
	        ((local_58 = pUnit, pUnit->dwUnitType == 0 || (pUnit->dwUnitType == 1)))) ||
	    (local_58 = sub_6FB26AD0((int)pUnit), local_58 != nullptr))
	{
		puVar10 = &local_5c;
		for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
		{
			*puVar10 = 0;
			puVar10 = puVar10 + 1;
		}
		local_5c = 0x201;
		local_2c = a7;
		local_68 = a4 * a4;
		local_70 = -a4;
		local_30 = a6;
		local_4c = a5;
		iVar8 = local_70;
		local_60 = local_70;
		if (-a4 == a4 || SBORROW4(local_70, a4) != a4 * -2 < 0)
		{
			do
			{
				local_6c = local_70 * local_70;
				iVar5 = iVar8;
				for (; iVar8 <= a4; iVar8 = iVar8 + a9)
				{
					if (iVar8 * iVar8 + local_6c <= local_68)
					{
						if (0 < (int)a8)
						{
							uVar9 = (pUnit->pSeed).nLowSeed;
							uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
							if ((a8 & a8 - 1) == 0)
							{
								DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar4);
								(*(uint64_t*)&pUnit->pSeed) = DVar3;
								uVar9 = a8 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
							}
							else
							{
								DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + uVar4);
								(*(uint64_t*)&pUnit->pSeed) = DVar3;
								uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)a8);
							}
							if (uVar9 != 0)
								goto LAB_6fb35f81;
						}
						local_48 = (D2ActiveRoomStrc**)(iVar8 + local_64);
						local_44 = local_70 + a3;
						uVar9 = *(uint32_t*)(local_7c + 0x17c);
						if (uVar9 != 0)
						{
							if ((int)uVar9 < 1)
							{
								local_1c = 0;
							}
							else
							{
								uVar1 = (pUnit->pSeed).nLowSeed;
								uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
								if ((uVar9 & uVar9 - 1) == 0)
								{
									DVar3 = (uint64_t)((uint64_t)uVar1 * 0x6ac690c5 + uVar4);
									(*(uint64_t*)&pUnit->pSeed) = DVar3;
									local_1c = uVar9 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
								}
								else
								{
									DVar3 = (uint64_t)((uint64_t)uVar1 * 0x6ac690c5 + uVar4);
									(*(uint64_t*)&pUnit->pSeed) = DVar3;
									local_1c = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar9);
								}
							}
						}
						pDVar7 = UNITS_GetRoom(pUnit);
						iVar5 = local_44;
						ppDVar6 = local_48;
						ppDStack_74 = local_48;
						if (pDVar7 != nullptr)
						{
							iVar2 = (pDVar7->tCoords).nSubtileX;
							if (((((int)local_48 < iVar2) ||
							         ((pDVar7->tCoords).nSubtileWidth + iVar2 <= (int)local_48)) ||
							        (iVar2 = (pDVar7->tCoords).nSubtileY, local_44 < iVar2)) ||
							    ((pDVar7->tCoords).nSubtileHeight + iVar2 <= local_44))
							{
								ppDStack_74 = nullptr;
								uStack_78 = 0;
								DUNGEON_GetAdjacentRoomsListFromRoom(pDVar7, &ppDStack_74, (int*)&uStack_78);
								uVar9 = 0;
								if (uStack_78 != 0)
								{
									do
									{
										pDVar7 = ppDStack_74[uVar9];
										if (((pDVar7 != nullptr) &&
										        (iVar2 = (pDVar7->tCoords).nSubtileX, iVar2 <= (int)ppDVar6)) &&
										    (((int)ppDVar6 < (pDVar7->tCoords).nSubtileWidth + iVar2 &&
										        ((iVar2 = (pDVar7->tCoords).nSubtileY, iVar2 <= iVar5 &&
										                                                   (iVar5 < (pDVar7->tCoords).nSubtileHeight + iVar2))))))
										{
											pDVar7 = ppDStack_74[uVar9];
											goto LAB_6fb35f70;
										}
										uVar9 = uVar9 + 1;
									} while (uVar9 < uStack_78);
								}
							}
							else
							{
							LAB_6fb35f70:
								if (pDVar7 != nullptr)
								{
									sub_6FB3E070(&local_5c);
								}
							}
						}
					}
				LAB_6fb35f81:
					iVar5 = local_60;
				}
				local_70 = local_70 + a9;
				iVar8 = iVar5;
			} while (local_70 <= a4);
		}
	}
}

//D2Client.0x6FB35FD0
void __fastcall sub_6FB35FD0(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int local_48;
	int32_t DStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_34;
	int iStack_30;
	uint32_t uStack_2c;
	int local_28;

	if ((a2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= a2))
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a2 * 0x1a4;
	}
	if (a2 != 0)
	{
		puVar4 = &local_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		local_5c = 0x17;
		if (0 < a5)
		{
			local_5c = 0x1f;
			local_28 = a5;
		}
		local_58 = sub_6FB26AD0((int)pUnit);
		uVar1 = pUnit->dwUnitType;
		local_54 = pUnit;
		local_4c = a2;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			local_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_48 = 0;
		}
		else
		{
			local_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_34 = *(int*)(iVar3 + 0x38) << 7;
		if (a4 < 1)
		{
			a4 = 1;
		}
		iVar2 = 0;
		do
		{
			uStack_40 = *(uint32_t*)((int)&dword_6FB70388 + iVar2);
			uStack_3c = *(uint32_t*)((int)&dword_6FB703C8 + iVar2);
			sub_6FB3E070(&local_5c);
			iVar2 = iVar2 + a4 * 4;
		} while (iVar2 < 0x40);
		if (0 < a3)
		{
			iStack_34 = *(int*)(iVar3 + 0x3c) << 7;
			iVar3 = 0;
			do
			{
				uStack_40 = *(uint32_t*)((int)dword_6FB7038C + iVar3);
				uStack_3c = *(uint32_t*)((int)dword_6FB703CC + iVar3);
				sub_6FB3E070(&local_5c);
				iVar3 = iVar3 + a3 * 4;
			} while (iVar3 < 0x3c);
		}
	}
}

//D2Client.0x6FB36150
uint32_t __fastcall sub_6FB36150(D2UnitStrc* pUnit)
{
	D2UnitStrc* pMissile;
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	local_58 = sub_6FB26AD0((int)pUnit);
	if ((((local_58 != nullptr) && (pUnit != nullptr)) &&
	        (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	    (((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
	          (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0)) &&
	        (-1 < *(short*)(iVar2 + 0x2c)))))
	{
		puVar3 = &local_5c;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_5c = 2;
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iVar2 = *(int*)(iVar2 + 0x6c);
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		iVar1 = 0;
		do
		{
			uStack_3c = *(uint32_t*)((int)&dword_6FB70428 + iVar1);
			uStack_40 = *(uint32_t*)((int)&dword_6FB70408 + iVar1);
			pMissile = sub_6FB3E070(&local_5c);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, *(int*)((int)&dword_6FB70408 + iVar1));
				MISSILE_SetTargetY(pMissile, *(int*)((int)&dword_6FB70428 + iVar1));
			}
			iVar1 = iVar1 + iVar2 * 4;
		} while (iVar1 < 0x20);
	}
	return 1;
}

//D2Client.0x6FB36250
uint32_t __fastcall sub_6FB36250(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	int32_t DVar6;
	int iVar7;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		uVar2 = *(uint32_t*)(iVar1 + 0x70);
		uVar4 = MISSILE_GetLevel(pUnit);
		iVar5 = MISSILE_GetSkill(pUnit);
		iVar1 = *(int*)(iVar1 + 0x6c);
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
		}
		else
		{
			DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			iVar7 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar7 = 0;
		}
		else
		{
			iVar7 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		sub_6FB35D10(pUnit, iVar7, (int)DVar6, iVar1, 0x109, iVar5, uVar4, uVar2, 1);
	}
	return 1;
}

//D2Client.0x6FB36350
uint32_t __fastcall sub_6FB36350(D2UnitStrc* pUnit)
{
	int iVar1;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		sub_6FB35FD0(pUnit, (int)*(short*)(iVar1 + 0x2c), *(uint32_t*)(iVar1 + 0x6c),
		    *(uint32_t*)(iVar1 + 0x70), *(int*)(iVar1 + 0x74));
	}
	return 1;
}

//D2Client.0x6FB363B0
uint32_t __fastcall sub_6FB363B0(D2UnitStrc* pUnit)
{
	short sVar1;
	short sVar2;
	uint32_t uVar3;
	uint64_t DVar4;
	uint64_t uVar5;
	uint32_t uVar6;
	int iVar7;
	D2UnitStrc* pDVar8;
	uint32_t uVar9;
	int iVar10;
	int iVar11;
	uint32_t* puVar12;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar11 = pUnit->dwClassId, -1 < iVar11)) &&
	        (iVar11 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar11 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar11 * 0x1a4, iVar11 != 0 &&
	                                                                                         (-1 < *(short*)(iVar11 + 0x2c)))))
	{
		uVar6 = MISSILE_GetLevel(pUnit);
		iVar7 = MISSILE_GetSkill(pUnit);
		sVar1 = *(short*)(iVar11 + 0x2c);
		pDVar8 = pUnit;
		if ((pUnit->dwUnitType == 0) ||
		    ((pUnit->dwUnitType == 1 ||
		        (pDVar8 = sub_6FB26AD0((int)pUnit), pDVar8 != nullptr))))
		{
			puVar12 = &uStack_5c;
			for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
			{
				*puVar12 = 0;
				puVar12 = puVar12 + 1;
			}
			uStack_5c = 0x20;
			uStack_40 = 0;
			uStack_3c = 0;
			pDStack_58 = pDVar8;
			pDStack_54 = pUnit;
			iStack_4c = (int)sVar1;
			iStack_30 = iVar7;
			uStack_2c = uVar6;
			sub_6FB3E070(&uStack_5c);
		}
		sVar1 = *(short*)(iVar11 + 0x2e);
		if (-1 < sVar1)
		{
			sVar2 = *(short*)(iVar11 + 0x30);
			iVar11 = (int)sVar1;
			if ((sVar1 < sVar2) && (iVar11 < sVar2))
			{
				uVar6 = sVar2 - iVar11;
				uVar9 = uVar6 + 1;
				if ((int)uVar9 < 1)
				{
					uVar6 = 0;
				}
				else
				{
					uVar5 = (uint64_t)(pUnit->pSeed).nHighSeed;
					uVar3 = (pUnit->pSeed).nLowSeed;
					if ((uVar9 & uVar6) == 0)
					{
						DVar4 = (uint64_t)((uint64_t)uVar3 * 0x6ac690c5 + uVar5);
						(*(uint64_t*)&pUnit->pSeed) = DVar4;
						uVar6 = uVar6 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
					}
					else
					{
						DVar4 = (uint64_t)((uint64_t)uVar3 * 0x6ac690c5 + uVar5);
						(*(uint64_t*)&pUnit->pSeed) = DVar4;
						uVar6 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar9);
					}
				}
				iVar11 = iVar11 + uVar6;
			}
			uVar6 = MISSILE_GetLevel(pUnit);
			iVar7 = MISSILE_GetSkill(pUnit);
			pDVar8 = pUnit;
			if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
			    (pDVar8 = sub_6FB26AD0((int)pUnit), pDVar8 != nullptr))
			{
				puVar12 = &uStack_5c;
				for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
				{
					*puVar12 = 0;
					puVar12 = puVar12 + 1;
				}
				uStack_5c = 0x20;
				uStack_40 = 0;
				uStack_3c = 0;
				pDStack_58 = pDVar8;
				pDStack_54 = pUnit;
				iStack_4c = iVar11;
				iStack_30 = iVar7;
				uStack_2c = uVar6;
				pDVar8 = sub_6FB3E070(&uStack_5c);
				if (pDVar8 != nullptr)
				{
					sub_6FB29540((int)pDVar8);
				}
			}
		}
	}
	return 1;
}

//D2Client.0x6FB36570
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB36570(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	bool bVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int iVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if (pUnit == nullptr)
	{
		return 1;
	}
	iVar4 = pUnit->dwClassId;
	if (iVar4 < 0)
	{
		return 1;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4)
	{
		return 1;
	}
	iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4;
	if (iVar4 != 0)
	{
		if (pUnit2 == nullptr)
		{
			return 1;
		}
		pDVar2 = sub_6FB26AD0((int)pUnit);
		if (((*(int*)(iVar4 + 0x6c) == 0) || (pDVar2 == nullptr)) ||
		    ((bVar1 = sub_6FB2A0C0(pDVar2, (int*)pUnit2), D2C_ZEXT(bVar1) == 0 &&
		                                                      (bVar1 = sub_6FB2A1C0(pDVar2, (int*)pUnit2), D2C_ZEXT(bVar1) == 0))))
		{
			if (pUnit2->dwUnitType == 0)
			{
				if (*(int*)(iVar4 + 0x70) != 0)
				{
					return 0;
				}
			}
			else
			{
				if (pUnit2->dwUnitType != 1)
				{
					return 0;
				}
				if (*(int*)(iVar4 + 0x70) == 2)
				{
					iVar3 = MONSTERS_IsDemon(pUnit2);
					if (iVar3 == 0)
					{
						return 0;
					}
				}
				else
				{
					iVar3 = MONSTERS_IsUndead(pUnit2);
					if (iVar3 == 0)
					{
						return 0;
					}
				}
			}
			if (-1 < *(short*)(iVar4 + 0x2c))
			{
				puVar5 = &local_5c;
				for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
				{
					*puVar5 = 0;
					puVar5 = puVar5 + 1;
				}
				pDStack_58 = pDVar2;
				pDStack_54 = pUnit;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				uStack_4c = 0xcc;
				sub_6FB3E070(&local_5c);
			}
		}
		else if (0 < *(short*)(iVar4 + 0x36))
		{
			sub_6FB5BA70(pUnit2, (int)*(short*)(iVar4 + 0x36), 2, 0, 0, 0, 0, 0);
			return 1;
		}
		return 1;
	}
	return 1;
}

//D2Client.0x6FB366D0
uint32_t __fastcall sub_6FB366D0(int a1, D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;

	if ((((pUnit != nullptr) && (a1 != 0)) &&
	        (iVar2 = *(int*)(a1 + 4), -1 < iVar2)) &&
	    (((iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
	          (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0)) &&
	        (sVar1 = *(short*)(iVar2 + 0x36), 0 < sVar1))))
	{
		sub_6FB5BA70(pUnit, (int)sVar1, 2, 0, 0, 0, 0, 0);
	}
	return 1;
}

//D2Client.0x6FB36740
uint32_t __fastcall sub_6FB36740(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	short* psVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	int aiStack_c[3];

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0))
	{
		iVar3 = MISSILE_GetSkill(pUnit);
		uVar4 = MISSILE_GetLevel(pUnit);
		if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar1 != 0))
		{
			iVar8 = 0;
			psVar7 = (short*)(iVar2 + 0x2c);
			do
			{
				if (*psVar7 < 0)
					break;
				aiStack_c[iVar8] = (int)*psVar7;
				iVar8 = iVar8 + 1;
				psVar7 = psVar7 + 1;
			} while (iVar8 < 3);
			if (0 < iVar8)
			{
				iVar6 = *(int*)(iVar2 + 0x6c);
				if (iVar6 < 1)
				{
					uVar9 = *(uint32_t*)(iVar1 + 0x138);
					uVar10 = uVar4;
					pDVar5 = sub_6FB26AD0((int)pUnit);
					iVar6 = SKILLS_EvaluateSkillFormula(pDVar5, uVar9, iVar3, uVar10);
					if (iVar6 < 1)
					{
						iVar6 = 1;
					}
				}
				iVar3 = pUnit->dwClassId;
				uVar9 = *(uint32_t*)(iVar2 + 0x88);
				uVar10 = uVar4;
				pDVar5 = sub_6FB26AD0((int)pUnit);
				iVar3 = MISSILE_EvaluateMissileFormula(pUnit, pDVar5, uVar9, iVar3, uVar10);
				if (iVar3 < 1)
				{
					iVar3 = (int)*(short*)(iVar2 + 0x98) * (uVar4 - 1) + (int)*(short*)(iVar2 + 0x96);
				}
				sub_6FB2FF20(pUnit, (int)aiStack_c, iVar8, iVar6, iVar3, *(uint32_t*)(iVar2 + 0x70));
			}
		}
	}
	return 1;
}

//D2Client.0x6FB36890
uint32_t __fastcall sub_6FB36890(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	D2DynamicPathStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar4;
	int32_t DVar5;
	int iVar6;
	int32_t DVar7;

	pDVar1 = pUnit->pDynamicPath;
	pDVar2 = sub_6FB26AD0((int)pUnit);
	if ((pDVar2 != nullptr) && (iVar3 = sub_6FB29550((int*)pDVar2), iVar3 == 0))
	{
		pRoom = UNITS_GetRoom(pUnit);
		if ((pRoom != nullptr) && (iVar3 = DUNGEON_IsRoomInTown(pRoom), iVar3 != 0))
		{
			return 1;
		}
		uVar4 = MISSILE_GetTargetX(pUnit);
		if ((pUnit2 != nullptr) || ((uVar4 & 4) == 0))
		{
			if ((uVar4 & 1) == 0)
			{
				if ((uVar4 & 2) != 0)
				{
					iVar3 = MISSILE_GetCurrentFrame(pUnit);
					if (0 < iVar3)
					{
						return (uVar4 & 0xff) >> 2 & 1;
					}
					iVar3 = pUnit->dwClassId;
					if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
					    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0))
					{
						iVar3 = *(int*)(iVar3 + 0x3c);
						uVar4 = MISSILE_GetTargetX(pUnit);
						if (((uVar4 & 4) == 0) &&
						    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 != nullptr))
						{
							uVar4 = pUnit->dwUnitType;
							if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
							{
								DVar5 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
							}
							else if (pUnit->pDynamicPath == nullptr)
							{
								(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
								(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
							}
							else
							{
								DVar5 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
							}
							uVar4 = pUnit->dwUnitType;
							if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
							{
								iVar6 = pUnit->pDynamicPath->dwClientCoordY;
							}
							else if (pUnit->pDynamicPath == nullptr)
							{
								iVar6 = 0;
							}
							else
							{
								iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
							}
							pDVar2 = sub_6FABB890(pDVar2, iVar6, DVar5, iVar3, 3, 0xffffffff, nullptr);
							iVar3 = pUnit->dwClassId;
							if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
							    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0))
							{
								if ((pDVar2 != nullptr) &&
								    (iVar6 = sub_6FB29550((int*)pDVar2), iVar6 != 0))
								{
									pDVar2 = nullptr;
								}
								uVar4 = MISSILE_GetLevel(pUnit);
								iVar3 = (uVar4 - 1) * (int)*(short*)(iVar3 + 0x98) + (int)*(short*)(iVar3 + 0x96);
								MISSILE_SetTotalFrames(pUnit, iVar3);
								MISSILE_SetCurrentFrame(pUnit, iVar3);
								pDVar1 = pUnit->pDynamicPath;
								if (pDVar2 == nullptr)
								{
									iVar3 = MISSILE_GetTargetY(pUnit);
									uVar4 = pUnit->dwUnitType;
									if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
									{
										iVar6 = pUnit->pDynamicPath->dwClientCoordY;
									}
									else if (pUnit->pDynamicPath == nullptr)
									{
										iVar6 = 0;
									}
									else
									{
										iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
									}
									iVar6 = (short)iVar3 + iVar6;
									uVar4 = pUnit->dwUnitType;
									if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
									{
										DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
									}
									else if (pUnit->pDynamicPath == nullptr)
									{
										(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
										(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
									}
									else
									{
										DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
									}
									iVar3 = (int)(short)((uint32_t)iVar3 >> 0x10) + (int)DVar7;
									D2COMMON_10170_PathSetTargetPos(pDVar1, iVar6, iVar3);
									MISSILE_SetTargetX(pUnit, 6);
									uVar4 = UNITS_GetDistanceToCoordinates(pUnit, iVar6, iVar3);
								}
								else
								{
									PATH_SetTargetUnit(pDVar1, pDVar2);
									MISSILE_SetTargetX(pUnit, 5);
									uVar4 = UNITS_GetDistanceToOtherUnit(pUnit, pDVar2);
								}
								if ((int)uVar4 < 0x19)
								{
									D2Common_10142(pDVar1, pUnit, 0);
								}
							}
							return 0;
						}
					}
				}
			}
			else if ((pUnit2 != nullptr) &&
			         (pDVar2 = PATH_GetTargetUnit(pDVar1), pUnit2 != pDVar2))
			{
				return 0;
			}
		}
	}
	return 1;
}

//D2Client.0x6FB36B50
uint32_t __fastcall sub_6FB36B50(D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;
	uint64_t DVar3;
	uint64_t DVar4;
	uint32_t uVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	uint32_t* puVar11;
	int32_t DStack_80;
	int local_7c;
	int* piStack_78;
	int iStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0))
	{
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			local_7c = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_7c = 0;
		}
		else
		{
			local_7c = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_80 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_80 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_80 + 2)) = 0;
		}
		else
		{
			DStack_80 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		if (-1 < *(short*)(iVar2 + 0x2c))
		{
			uVar5 = MISSILE_GetLevel(pUnit);
			iVar6 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar2 + 0x2c);
			pDVar7 = pUnit;
			if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
			    (pDVar7 = sub_6FB26AD0((int)pUnit), pDVar7 != nullptr))
			{
				puVar11 = &uStack_5c;
				for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
				{
					*puVar11 = 0;
					puVar11 = puVar11 + 1;
				}
				uStack_5c = 0x20;
				uStack_40 = 0;
				uStack_3c = 0;
				pDStack_58 = pDVar7;
				pDStack_54 = pUnit;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar6;
				uStack_2c = uVar5;
				sub_6FB3E070(&uStack_5c);
			}
		}
		if (-1 < *(short*)(iVar2 + 0x2e))
		{
			DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar3;
			iStack_6c = 0;
			DVar4 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar4;
			iVar6 = (int)(((uint64_t)DVar3 & 0xffffffff) % 3) * 0x14;
			if (0 < *(int*)(byte_6FB7048C + iVar6))
			{
				piStack_78 = (int*)(byte_6FB70490 + iVar6);
				do
				{
					uVar10 = *piStack_78 + ((*(uint32_t*)((uint8_t*)&DVar4 + 0)) & 7) & 7;
					uVar5 = MISSILE_GetLevel(pUnit);
					iVar8 = MISSILE_GetSkill(pUnit);
					sVar1 = *(short*)(iVar2 + 0x2e);
					pDVar7 = pUnit;
					if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
					    (pDVar7 = sub_6FB26AD0((int)pUnit), pDVar7 != nullptr))
					{
						puVar11 = &uStack_5c;
						for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
						{
							*puVar11 = 0;
							puVar11 = puVar11 + 1;
						}
						uStack_5c = 0x20;
						uStack_40 = 0;
						uStack_3c = 0;
						pDStack_58 = pDVar7;
						pDStack_54 = pUnit;
						iStack_4c = (int)sVar1;
						iStack_30 = iVar8;
						uStack_2c = uVar5;
						pDVar7 = sub_6FB3E070(&uStack_5c);
						if (pDVar7 != nullptr)
						{
							D2Common_10216(pDVar7->pDynamicPath, *(int*)(byte_6FB7044C + uVar10 * 4) + local_7c,
							    *(int*)(byte_6FB7046C + uVar10 * 4) + (int)DStack_80, 0);
						}
					}
					iStack_6c = iStack_6c + 1;
					piStack_78 = piStack_78 + 1;
				} while (iStack_6c < *(int*)(byte_6FB7048C + iVar6));
			}
		}
	}
	return 1;
}

//D2Client.0x6FB36DF0
uint32_t __fastcall sub_6FB36DF0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	uint32_t uVar6;
	D2UnitStrc* pDVar7;
	uint32_t* puVar8;
	int iStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_50;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	if (((((pUnit != nullptr) && (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
	         (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        ((iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0 &&
	                                                                                           (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 != nullptr)))) &&
	    (pUnit2 != nullptr))
	{
		if (0 < *(short*)(iVar5 + 0x36))
		{
			sub_6FB5BA70(pUnit2, (int)*(short*)(iVar5 + 0x36), 2, 0, 0, 0, 0, 0);
		}
		iVar3 = MISSILE_GetTargetX(pUnit);
		if (1 < iVar3)
		{
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_6c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_6c = 0;
			}
			else
			{
				iStack_6c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath != nullptr)
			{
				DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iVar5 = *(int*)(iVar5 + 0x6c);
			if (iVar5 < 1)
			{
				iVar5 = MISSILE_GetSkill(pUnit);
				uVar6 = MISSILE_GetLevel(pUnit);
				if (iVar5 < 0)
				{
					return 1;
				}
				if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar5)
				{
					return 1;
				}
				iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar5 * 0x23c;
				if (iVar1 == 0)
				{
					return 1;
				}
				iVar5 = SKILLS_EvaluateSkillFormula(pDVar2, *(uint32_t*)(iVar1 + 100), iVar5, uVar6);
				if (iVar5 < 1)
				{
					iVar5 = 1;
				}
			}
			pDVar7 = sub_6FABB890(pDVar2, iStack_6c, DVar4, iVar5, 0x88583, pUnit2->dwUnitId, nullptr);
			if ((pDVar7 != nullptr) && (pDVar7 != pUnit2))
			{
				puVar8 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				iStack_4c = pUnit->dwClassId;
				uStack_5c = 0x21;
				iStack_48 = iStack_6c;
				uVar6 = pDVar7->dwUnitType;
				pDStack_58 = pDVar2;
				pDStack_50 = pDVar7;
				DStack_44 = DVar4;
				if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
				{
					iStack_40 = pDVar7->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar7->pDynamicPath == nullptr)
				{
					iStack_40 = 0;
				}
				else
				{
					iStack_40 = PATH_GetXPosition(pDVar7->pDynamicPath);
				}
				uVar6 = pDVar7->dwUnitType;
				if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
				{
					DStack_3c = (*(int32_t*)&pDVar7->pDynamicPath->tTargetCoord);
				}
				else if (pDVar7->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
				}
				else
				{
					DStack_3c = (int32_t)PATH_GetYPosition(pDVar7->pDynamicPath);
				}
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				pDVar2 = sub_6FB3E070(&uStack_5c);
				if (pDVar2 != nullptr)
				{
					MISSILE_SetTargetX(pDVar2, iVar3 + -1);
					MISSILE_SetOwner(pDVar2, pUnit2);
				}
			}
		}
	}
	return 1;
}

//D2Client.0x6FB37060
uint32_t __fastcall sub_6FB37060(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int32_t DVar7;
	int iVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		iVar3 = MISSILE_GetSkill(pUnit);
		uVar4 = MISSILE_GetLevel(pUnit);
		if (((-1 < iVar3) && (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c != 0))
		{
			pDVar5 = sub_6FB26AD0((int)pUnit);
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar6 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			puVar10 = &uStack_5c;
			for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			uStack_5c = 0x4001;
			pDStack_58 = pDVar5;
			iStack_30 = iVar3;
			uStack_2c = uVar4;
			if (-1 < *(short*)(iVar1 + 0x2c))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x2c);
				iVar8 = *(int*)(iVar1 + 0x6c);
				iVar9 = 0;
				if (0 < iVar8)
				{
					do
					{
						DStack_44 = (int32_t)((&dword_6FB7056C)[iVar9 % 5] + (int)DVar7);
						iStack_48 = (&dword_6FB70558)[iVar9 % 5] + iVar6;
						sub_6FB3E070(&uStack_5c);
						iVar9 = iVar9 + 1;
					} while (iVar9 < iVar8);
				}
			}
			if (-1 < *(short*)(iVar1 + 0x2e))
			{
				uStack_5c = 0x8001;
				iStack_4c = (int)*(short*)(iVar1 + 0x2e);
				if ((iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0)) &&
				    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar3 * 0x23c, iVar3 != 0))
				{
					if ((int)uVar4 < 1)
					{
						iStack_10 = 0;
					}
					else
					{
						iStack_10 = *(int*)(iVar3 + 0x154) * (uVar4 - 1) + *(int*)(iVar3 + 0x150);
					}
				}
				else
				{
					iStack_10 = 0;
				}
				iStack_48 = iVar6;
				DStack_44 = DVar7;
				pDVar5 = sub_6FB3E070(&uStack_5c);
				if ((pDVar5 != nullptr) && (pDVar5->dwInteractGUID != 0))
				{
					sub_6FAA43E0(pDVar5->dwInteractGUID, 0xc);
				}
			}
			uStack_5c = 0xc001;
			iVar3 = 0;
			if (-1 < *(short*)(iVar1 + 0x30))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x30);
				iVar3 = *(int*)(iVar1 + 0x70);
				iVar8 = 0;
				if (0 < iVar3)
				{
					do
					{
						DStack_44 = (int32_t)((&dword_6FB70510)[iVar8 % 0x12] + (int)DVar7);
						iStack_48 = (&dword_6FB704C8)[iVar8 % 0x12] + iVar6;
						sub_6FB3E070(&uStack_5c);
						iVar8 = iVar8 + 1;
					} while (iVar8 < iVar3);
				}
			}
			if (-1 < *(short*)(iVar1 + 0x32))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x32);
				iVar1 = *(int*)(iVar1 + 0x74) + iVar3;
				for (; iVar3 < iVar1; iVar3 = iVar3 + 1)
				{
					DStack_44 = (int32_t)((&dword_6FB70510)[iVar3 % 0x12] + (int)DVar7);
					iStack_48 = (&dword_6FB704C8)[iVar3 % 0x12] + iVar6;
					sub_6FB3E070(&uStack_5c);
				}
			}
		}
	}
	return 1;
}

//D2Client.0x6FB37330
uint32_t __fastcall sub_6FB37330(D2UnitStrc* pUnit)
{
	short sVar1;
	short sVar2;
	uint32_t uVar3;
	uint64_t DVar4;
	uint64_t uVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int iVar8;
	D2UnitStrc* pDVar9;
	int iVar10;
	uint32_t* puVar11;
	int local_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar8 = pUnit->dwClassId, -1 < iVar8)) &&
	        (iVar8 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar8 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar8 * 0x1a4, iVar8 != 0 &&
	                                                                                       (sVar1 = *(short*)(iVar8 + 0x2c), -1 < sVar1))))
	{
		sVar2 = *(short*)(iVar8 + 0x2e);
		local_60 = (int)sVar1;
		if ((sVar1 < sVar2) && (local_60 < sVar2))
		{
			uVar6 = sVar2 - local_60;
			uVar7 = uVar6 + 1;
			if ((int)uVar7 < 1)
			{
				uVar6 = 0;
			}
			else
			{
				uVar5 = (uint64_t)(pUnit->pSeed).nHighSeed;
				uVar3 = (pUnit->pSeed).nLowSeed;
				if ((uVar7 & uVar6) == 0)
				{
					DVar4 = (uint64_t)((uint64_t)uVar3 * 0x6ac690c5 + uVar5);
					(*(uint64_t*)&pUnit->pSeed) = DVar4;
					uVar6 = uVar6 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
				}
				else
				{
					DVar4 = (uint64_t)((uint64_t)uVar3 * 0x6ac690c5 + uVar5);
					(*(uint64_t*)&pUnit->pSeed) = DVar4;
					uVar6 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar7);
				}
			}
			local_60 = local_60 + uVar6;
		}
		uVar6 = MISSILE_GetLevel(pUnit);
		iVar8 = MISSILE_GetSkill(pUnit);
		pDVar9 = pUnit;
		if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
		    (pDVar9 = sub_6FB26AD0((int)pUnit), pDVar9 != nullptr))
		{
			puVar11 = &uStack_5c;
			for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
			{
				*puVar11 = 0;
				puVar11 = puVar11 + 1;
			}
			uStack_40 = 0;
			uStack_3c = 0;
			uStack_5c = 0x20;
			iStack_4c = local_60;
			pDStack_58 = pDVar9;
			pDStack_54 = pUnit;
			iStack_30 = iVar8;
			uStack_2c = uVar6;
			sub_6FB3E070(&uStack_5c);
		}
	}
	return 1;
}

//D2Client.0x6FB37470
uint32_t __fastcall sub_6FB37470(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((((a2 != 0) && (pUnit != nullptr)) &&
	         (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
	        ((iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
	            (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0)))) &&
	    (-1 < *(short*)(iVar5 + 0x2c)))
	{
		uVar2 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		sVar1 = *(short*)(iVar5 + 0x2c);
		pDVar4 = pUnit;
		if (((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1)) &&
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 == nullptr))
		{
			return 0;
		}
		puVar6 = &uStack_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		uStack_5c = 0x20;
		uStack_40 = 0;
		uStack_3c = 0;
		pDStack_58 = pDVar4;
		pDStack_54 = pUnit;
		iStack_4c = (int)sVar1;
		iStack_30 = iVar3;
		uStack_2c = uVar2;
		sub_6FB3E070(&uStack_5c);
		return 0;
	}
	return 1;
}

//D2Client.0x6FB37560
uint32_t __fastcall sub_6FB37560(D2UnitStrc* pUnit2)
{
	int iVar1;
	uint32_t uVar2;
	int nSkillId;
	uint32_t nSkillLevel;
	D2UnitStrc* pUnit;
	int iVar3;
	int iVar4;
	int32_t DStack_24;
	int iStack_20;
	D2UnitStrc* pDStack_18;
	D2UnitStrc* pDStack_14;
	int iStack_10;
	uint32_t uStack_c;
	int iStack_8;
	int iStack_4;

	if ((((pUnit2 != nullptr) && (iVar1 = pUnit2->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		nSkillId = MISSILE_GetSkill(pUnit2);
		nSkillLevel = MISSILE_GetLevel(pUnit2);
		if (((-1 < nSkillId) &&
		        ((nSkillId < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) &&
		            (iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + nSkillId * 0x23c, iVar4 != 0)))) &&
		    (pUnit = sub_6FB26AD0((int)pUnit2), pUnit != nullptr))
		{
			uVar2 = pUnit2->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iStack_20 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				iStack_20 = 0;
			}
			else
			{
				iStack_20 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar2 = pUnit2->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				DStack_24 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_24 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_24 + 2)) = 0;
			}
			else
			{
				DStack_24 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iVar3 = *(int*)(iVar1 + 0x6c);
			if ((iVar3 < 1) &&
			    (iVar3 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 100), nSkillId, nSkillLevel),
			        iVar3 < 1))
			{
				iVar3 = 1;
			}
			iStack_8 = *(int*)(iVar1 + 0x70);
			if ((iStack_8 < 1) &&
			    (iStack_8 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar4 + 0x138), nSkillId, nSkillLevel), iStack_8 < 1))
			{
				iStack_8 = 1;
			}
			iVar4 = *(int*)(iVar4 + 0x50);
			if (iVar4 == 0)
			{
				iVar4 = 0xa783;
			}
			iStack_4 = (int)*(short*)(iVar1 + 0x2c);
			pDStack_18 = pUnit;
			pDStack_14 = pUnit2;
			iStack_10 = nSkillId;
			uStack_c = nSkillLevel;
			sub_6FABB590(pUnit, iStack_20, DStack_24, iVar3, iVar4, 0x6fb37740, (uint32_t)(&pDStack_18), 1);
		}
	}
	return 1;
}

//D2Client.0x6FB37740
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FB37740()
{
	uint32_t* puVar1;
	int in_ECX;
	int iVar2;
	int* in_EDX;
	uint32_t* puVar3;
	uint32_t auStack_5c[4];
	uint32_t uStack_4c;
	int iStack_40;
	int iStack_3c;
	uint32_t uStack_30;
	uint32_t uStack_2c;

	puVar1 = *(uint32_t**)(in_ECX + 8);
	if ((int)puVar1[4] <= *(int*)(in_ECX + 4))
	{
		return 0;
	}
	puVar3 = auStack_5c;
	for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	auStack_5c[0] = 0x20;
	auStack_5c[1] = *puVar1;
	auStack_5c[2] = puVar1[1];
	uStack_30 = puVar1[2];
	uStack_2c = puVar1[3];
	iVar2 = *in_EDX;
	uStack_4c = puVar1[5];
	if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
	{
		iStack_40 = *(int*)(in_EDX[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)in_EDX[0xb] == nullptr)
	{
		iStack_40 = 0;
	}
	else
	{
		iStack_40 = PATH_GetXPosition((D2DynamicPathStrc*)in_EDX[0xb]);
	}
	iVar2 = *in_EDX;
	if ((iVar2 == 2) || ((3 < iVar2 && (iVar2 < 6))))
	{
		iStack_3c = *(int*)(in_EDX[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)in_EDX[0xb] == nullptr)
	{
		iStack_3c = 0;
	}
	else
	{
		iStack_3c = PATH_GetYPosition((D2DynamicPathStrc*)in_EDX[0xb]);
	}
	sub_6FB3E070(auStack_5c);
	return 1;
}

//D2Client.0x6FB37800
uint32_t __fastcall sub_6FB37800(D2UnitStrc* pUnit2)
{
	int iVar1;
	D2UnitStrc* pUnit;
	int nSkillId;
	uint32_t nSkillLevel;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int32_t DStack_20;
	int iStack_1c;
	D2UnitStrc* pDStack_18;
	D2UnitStrc* pDStack_14;
	int iStack_10;
	uint32_t uStack_c;
	int iStack_4;

	if (((((pUnit2 != nullptr) && (iVar1 = pUnit2->dwClassId, -1 < iVar1)) &&
	         (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                           (-1 < *(short*)(iVar1 + 0x24))))) &&
	    (pUnit = sub_6FB26AD0((int)pUnit2), pUnit != nullptr))
	{
		nSkillId = MISSILE_GetSkill(pUnit2);
		nSkillLevel = MISSILE_GetLevel(pUnit2);
		if (((-1 < nSkillId) && (nSkillId < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
		    (iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + nSkillId * 0x23c, iVar5 != 0))
		{
			iVar2 = MISSILE_GetTargetX(pUnit2);
			uVar3 = MISSILE_GetTargetY(pUnit2);
			pDVar4 = sub_6FB269F0(uVar3, iVar2);
			if (pDVar4 == nullptr)
			{
				return 0;
			}
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				iStack_1c = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				iStack_1c = 0;
			}
			else
			{
				iStack_1c = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar3 = pUnit2->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				DStack_20 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_20 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_20 + 2)) = 0;
			}
			else
			{
				DStack_20 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iVar2 = *(int*)(iVar1 + 0x6c);
			if ((iVar2 < 1) &&
			    (iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar5 + 100), nSkillId, nSkillLevel),
			        iVar2 < 1))
			{
				iVar2 = 1;
			}
			if (*(int*)(iVar1 + 0x70) < 1)
			{
				SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar5 + 0x144), nSkillId, nSkillLevel);
			}
			iVar5 = *(int*)(iVar5 + 0x50);
			if (iVar5 != 0)
			{
				iVar5 = 0xa683;
			}
			iStack_4 = (int)*(short*)(iVar1 + 0x2c);
			pDStack_18 = pUnit;
			pDStack_14 = pUnit2;
			iStack_10 = nSkillId;
			uStack_c = nSkillLevel;
			sub_6FABB590(pUnit, iStack_1c, DStack_20, iVar2, iVar5, 0x6fb37740, (uint32_t)(&pDStack_18), 0);
		}
	}
	return 1;
}

//D2Client.0x6FB379F0
uint32_t __fastcall sub_6FB379F0(D2UnitStrc* pUnit, int* a2, int a3, uint32_t a4, int a5, int a6)
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	int* local_54;
	int local_4c;
	int local_48;
	int iStack_44;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_34;
	uint32_t uStack_30;
	int iStack_2c;
	int iStack_28;

	if (((-1 < a3) && (a3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4, iVar2 != 0))
	{
		puVar3 = &local_5c;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		iVar1 = *a2;
		local_5c = 0x1f;
		local_4c = a3;
		local_58 = pUnit;
		local_54 = a2;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
		{
			local_48 = *(int*)(a2[0xb] + 0xc);
		}
		else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
		{
			local_48 = 0;
		}
		else
		{
			local_48 = PATH_GetXPosition((D2DynamicPathStrc*)a2[0xb]);
		}
		iVar1 = *a2;
		if ((iVar1 == 2) || ((3 < iVar1 && (iVar1 < 6))))
		{
			iStack_44 = *(int*)(a2[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
		{
			iStack_44 = 0;
		}
		else
		{
			iStack_44 = PATH_GetYPosition((D2DynamicPathStrc*)a2[0xb]);
		}
		uStack_30 = a4;
		iStack_2c = a5;
		iStack_28 = a5 + -1;
		iStack_34 = *(int*)(iVar2 + 0x38) << 7;
		iVar2 = 0;
		do
		{
			uStack_40 = *(uint32_t*)((int)dword_6FB70580 + iVar2);
			uStack_3c = *(uint32_t*)((int)dword_6FB705A0 + iVar2);
			sub_6FB3E070(&local_5c);
			iVar2 = iVar2 + a6 * 4;
		} while (iVar2 < 0x20);
		return 1;
	}
	return 0;
}

//D2Client.0x6FB37B20
uint32_t __fastcall sub_6FB37B20(D2UnitStrc* pUnit, int* a2)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		pDVar2 = sub_6FB26AD0((int)pUnit);
		if (pDVar2 != nullptr)
		{
			if (a2 == nullptr)
			{
				a2 = (int*)pUnit;
			}
			iVar3 = *(int*)(iVar1 + 0x6c);
			if (iVar3 < 1)
			{
				iVar3 = 1;
			}
			uVar4 = MISSILE_GetLevel(pUnit);
			iVar5 = MISSILE_GetSkill(pUnit);
			sub_6FB379F0(pDVar2, a2, (int)*(short*)(iVar1 + 0x2c), iVar5, uVar4, iVar3);
		}
	}
	return 1;
}

//D2Client.0x6FB37BB0
uint32_t __fastcall sub_6FB37BB0(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	uint8_t nDirection;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	int iStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	uint32_t uStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                       (-1 < *(short*)(iVar2 + 0x2c)))))
	{
		pDVar4 = sub_6FB26AD0((int)pUnit);
		if (pDVar4 != nullptr)
		{
			iVar5 = MISSILE_GetSkill(pUnit);
			uVar6 = MISSILE_GetLevel(pUnit);
			if (((-1 < iVar5) && (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0))) &&
			    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar5 * 0x23c, iVar1 != 0))
			{
				iStack_68 = *(int*)(iVar2 + 0x6c);
				if (iStack_68 == 0)
				{
					iStack_68 = SKILLS_EvaluateSkillFormula(pDVar4, *(uint32_t*)(iVar1 + 0x138), iVar5, uVar6);
					if (iStack_68 < 5)
					{
						iStack_68 = 5;
					}
				}
				puVar7 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar7 = 0;
					puVar7 = puVar7 + 1;
				}
				uVar3 = pUnit->dwUnitType;
				uStack_5c = 1;
				iStack_4c = (int)*(short*)(iVar2 + 0x2c);
				pDStack_58 = pDVar4;
				uStack_30 = uVar6;
				uStack_2c = uVar6;
				if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
				{
					iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_48 = 0;
				}
				else
				{
					iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar6 = pUnit->dwUnitType;
				if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
				{
					DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
				}
				else
				{
					DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				if (0 < iStack_68)
				{
					iStack_10 = iStack_68;
					uStack_5c = uStack_5c | 0x8000;
				}
				pDVar4 = sub_6FB3E070(&uStack_5c);
				if (pDVar4 != nullptr)
				{
					nDirection = PATH_GetDirection(pUnit->pDynamicPath);
					PATH_SetDirection(pDVar4->pDynamicPath, nDirection);
				}
			}
		}
	}
	return 1;
}

//D2Client.0x6FB37D70
uint32_t __fastcall sub_6FB37D70(D2UnitStrc* pUnit)
{
	D2UnitStrc* pMissile;
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                        (-1 < *(short*)(iVar2 + 0x2c))) &&
	        (local_58 = sub_6FB26AD0((int)pUnit), local_58 != nullptr))))
	{
		puVar3 = &local_5c;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_5c = 2;
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = (int)*(short*)(iVar2 + 0x2c);
		iVar2 = *(int*)(iVar2 + 0x6c);
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		iVar1 = 0;
		do
		{
			uStack_40 = *(uint32_t*)((int)&dword_6FB705C0 + iVar1);
			uStack_3c = *(uint32_t*)((int)&dword_6FB706C0 + iVar1);
			pMissile = sub_6FB3E070(&local_5c);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, *(int*)((int)&dword_6FB705C0 + iVar1));
				MISSILE_SetTargetY(pMissile, *(int*)((int)&dword_6FB706C0 + iVar1));
			}
			iVar1 = iVar1 + iVar2 * 4;
		} while (iVar1 < 0x100);
	}
	return 1;
}

//D2Client.0x6FB37E80
uint32_t __fastcall sub_6FB37E80(D2UnitStrc* pUnit)
{
	D2UnitStrc* pMissile;
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                        (-1 < *(short*)(iVar2 + 0x2c))) &&
	        (local_58 = sub_6FB26AD0((int)pUnit), local_58 != nullptr))))
	{
		puVar3 = &local_5c;
		for (iVar1 = 0x17; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_5c = 2;
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = (int)*(short*)(iVar2 + 0x2c);
		iVar2 = *(int*)(iVar2 + 0x6c);
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		iVar1 = 0;
		do
		{
			uStack_40 = *(uint32_t*)((int)&dword_6FB707C0 + iVar1);
			uStack_3c = *(uint32_t*)((int)&dword_6FB708C0 + iVar1);
			pMissile = sub_6FB3E070(&local_5c);
			if (pMissile != nullptr)
			{
				MISSILE_SetTargetX(pMissile, *(int*)((int)&dword_6FB707C0 + iVar1));
				MISSILE_SetTargetY(pMissile, *(int*)((int)&dword_6FB708C0 + iVar1));
			}
			iVar1 = iVar1 + iVar2 * 4;
		} while (iVar1 < 0x100);
	}
	return 1;
}

//D2Client.0x6FB37F90
uint32_t __fastcall sub_6FB37F90(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	short sVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	D2UnitStrc* pDVar7;
	int32_t DVar8;
	int iVar9;
	int iVar10;
	uint32_t* puVar11;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (pUnit == nullptr)
	{
		return 1;
	}
	iVar2 = pUnit->dwClassId;
	if (iVar2 < 0)
	{
		return 1;
	}
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar2)
	{
		return 1;
	}
	iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4;
	if (iVar2 != 0)
	{
		iVar5 = MISSILE_GetSkill(pUnit);
		uVar6 = MISSILE_GetLevel(pUnit);
		sVar1 = *(short*)(iVar2 + 0x2c);
		if (-1 < sVar1)
		{
			pDVar7 = pUnit;
			if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
			    (pDVar7 = sub_6FB26AD0((int)pUnit), pDVar7 != nullptr))
			{
				puVar11 = &uStack_5c;
				for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
				{
					*puVar11 = 0;
					puVar11 = puVar11 + 1;
				}
				uStack_40 = 0;
				uStack_3c = 0;
				uStack_5c = 0x20;
				pDStack_58 = pDVar7;
				pDStack_54 = pUnit;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar5;
				uStack_2c = uVar6;
				sub_6FB3E070(&uStack_5c);
			}
		}
		sVar1 = *(short*)(iVar2 + 0x2e);
		if (-1 < sVar1)
		{
			uVar3 = *(uint32_t*)(iVar2 + 0x70);
			iVar10 = *(int*)(iVar2 + 0x6c);
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
			}
			else
			{
				DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar4 = pUnit->dwUnitType;
			if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
			{
				iVar9 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar9 = 0;
			}
			else
			{
				iVar9 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			sub_6FB35D10(pUnit, iVar9, (int)DVar8, iVar10, (int)sVar1, iVar5, uVar6, uVar3, 1);
		}
		if (pUnit2 != nullptr)
		{
			sub_6FB5BA70(pUnit2, 0x97, 2, 0, 0, 0, 0, 0);
		}
		pDVar7 = sub_6FB26AD0((int)pUnit);
		if (((pDVar7 != nullptr) && (pUnit2 != nullptr)) &&
		    (0 < *(short*)(iVar2 + 0x36)))
		{
			sub_6FB5BA70(pDVar7, (int)*(short*)(iVar2 + 0x36), 2, 0, 0, 0, 0, 0);
		}
		return 1;
	}
	return 1;
}

//D2Client.0x6FB38160
uint32_t __fastcall sub_6FB38160(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	uint64_t DVar3;
	uint32_t uVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	int iStack_60;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int local_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	int iStack_2c;

	if (((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	         (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                           (-1 < *(short*)(iVar2 + 0x2c))))) &&
	    (local_58 = sub_6FB26AD0((int)pUnit), local_58 != nullptr))
	{
		puVar8 = &local_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar8 = 0;
			puVar8 = puVar8 + 1;
		}
		local_5c = 0x102;
		local_4c = (int)*(short*)(iVar2 + 0x2c);
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uVar7 = *(uint32_t*)(iVar2 + 0x6c);
		if ((int)uVar7 < 3)
		{
			uVar7 = 3;
		}
		iStack_60 = MISSILE_GetTargetX(pUnit);
		if (0 < iStack_60)
		{
			uVar4 = uVar7 * 2;
			uVar1 = uVar4 + 1;
			do
			{
				DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar3;
				iStack_2c = (int)(((uint64_t)DVar3 & 0xffffffff) % 5) + 1;
				if ((int)uVar1 < 1)
				{
					uVar6 = 0;
				}
				else
				{
					uVar6 = (pUnit->pSeed).nLowSeed;
					if ((uVar1 & uVar4) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
					}
				}
				iStack_40 = uVar6 - uVar7;
				if ((int)uVar1 < 1)
				{
					uVar6 = 0;
				}
				else
				{
					uVar6 = (pUnit->pSeed).nLowSeed;
					if ((uVar1 & uVar4) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar3;
						uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
					}
				}
				iStack_3c = uVar6 - uVar7;
				if ((iStack_40 == 0) && (iStack_3c == 0))
				{
					uVar6 = 0;
					if (0 < (int)uVar7)
					{
						uVar6 = (pUnit->pSeed).nLowSeed;
						if ((uVar7 & uVar7 - 1) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar6 = uVar7 - 1 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar6 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar6 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar7);
						}
					}
					iStack_40 = uVar6 + 1;
				}
				sub_6FB3E070(&local_5c);
				iStack_60 = iStack_60 + -1;
			} while (iStack_60 != 0);
		}
	}
	return 1;
}

//D2Client.0x6FB38360
uint32_t __fastcall sub_6FB38360(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB26AD0(a1);
	if (pDVar1 != nullptr)
	{
		pDVar1->dwFlagEx = pDVar1->dwFlagEx | 0x40000;
	}
	return 1;
}

//D2Client.0x6FB38380
uint32_t __fastcall sub_6FB38380(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	uint16_t uVar2;
	int32_t nY;
	int iVar3;
	D2ActiveRoomStrc* pRoom;
	int nUnitSize;

	if (a2 != 0)
	{
		return 0;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		nY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
	}
	else
	{
		nY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar3 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar3 = 0;
	}
	else
	{
		iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar2 = 1;
	nUnitSize = 3;
	pRoom = UNITS_GetRoom(pUnit);
	uVar2 = COLLISION_CheckMaskWithSize(pRoom, iVar3, (int)nY, nUnitSize, uVar2);
	if ((((uVar2 == 0) && (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
	        (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0))
	{
		sub_6FB2FF20(pUnit, (int)&tbl_6FB91208, 3, *(int*)(iVar3 + 0x38), 0x19, 0x4b);
	}
	return 1;
}

//D2Client.0x6FB38450
uint32_t __fastcall sub_6FB38450(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint8_t nDirection;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (a2 == 0)
	{
		if ((((pUnit != nullptr) && (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
		        (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
		    ((iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0 &&
		                                                                                       (-1 < *(short*)(iVar5 + 0x2c)))))
		{
			uVar2 = MISSILE_GetLevel(pUnit);
			iVar3 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar5 + 0x2c);
			pDVar4 = pUnit;
			if ((pUnit->dwUnitType == 0) ||
			    ((pUnit->dwUnitType == 1 ||
			        (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 != nullptr))))
			{
				puVar6 = &uStack_5c;
				for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
				{
					*puVar6 = 0;
					puVar6 = puVar6 + 1;
				}
				uStack_5c = 0x20;
				uStack_40 = 0;
				uStack_3c = 0;
				pDStack_58 = pDVar4;
				pDStack_54 = pUnit;
				iStack_4c = (int)sVar1;
				iStack_30 = iVar3;
				uStack_2c = uVar2;
				pDVar4 = sub_6FB3E070(&uStack_5c);
				if (pDVar4 != nullptr)
				{
					pDynamicPath = pDVar4->pDynamicPath;
					nDirection = PATH_GetDirection(pUnit->pDynamicPath);
					PATH_SetDirection(pDynamicPath, nDirection);
					D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
					iVar5 = MISSILE_GetTargetX(pUnit);
					MISSILE_SetTargetX(pDVar4, iVar5);
				}
			}
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FB38570
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB38570()
{
	D2DynamicPathStrc* pDynamicPath;
	int iVar1;
	D2UnitStrc* in_ECX;
	int iVar2;

	if (in_ECX != nullptr)
	{
		iVar1 = MISSILE_GetTotalFrames(in_ECX);
		iVar2 = 0xff;
		if (iVar1 < 0x100)
		{
			iVar2 = iVar1;
		}
		pDynamicPath = in_ECX->pDynamicPath;
		iVar1 = D2COMMON_10175_PathGetFirstPointX(pDynamicPath);
		SEED_InitLowSeed(&in_ECX->pSeed, iVar1);
		PATH_SetType(pDynamicPath, 10);
		PATH_SetNewDistance(pDynamicPath, (uint8_t)iVar2);
		D2Common_10142(pDynamicPath, in_ECX, 0);
	}
}

//D2Client.0x6FB385C0
uint32_t __fastcall sub_6FB385C0(D2UnitStrc* pUnit2)
{
	D2UnitStrc* pUnit;
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	code* pcStack_8;

	if (((((pUnit2 != nullptr) && (iVar2 = pUnit2->dwClassId, -1 < iVar2)) &&
	         (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                           (-1 < *(short*)(iVar2 + 0x24))))) &&
	    (pUnit = sub_6FB26AD0((int)pUnit2), pUnit != nullptr))
	{
		puVar4 = &local_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		uVar1 = pUnit2->dwUnitType;
		local_5c = 3;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			local_48 = pUnit2->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit2->pDynamicPath == nullptr)
		{
			local_48 = 0;
		}
		else
		{
			local_48 = PATH_GetXPosition(pUnit2->pDynamicPath);
		}
		uVar1 = pUnit2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
		}
		else if (pUnit2->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
		}
		iStack_4c = (int)*(short*)(iVar2 + 0x24);
		pDStack_58 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit2);
		uStack_2c = MISSILE_GetLevel(pUnit2);
		pcStack_8 = (code*)(sub_6FB38570);
		uVar1 = MISSILE_GetLevel(pUnit2);
		iVar2 = (uVar1 - 1) * *(int*)(iVar2 + 0x70) + *(int*)(iVar2 + 0x6c);
		if (iVar2 < 1)
		{
			iVar2 = MISSILE_GetSkill(pUnit2);
			uVar1 = MISSILE_GetLevel(pUnit2);
			if (iVar2 < 0)
			{
				return 1;
			}
			if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar2)
			{
				return 1;
			}
			iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar2 * 0x23c;
			if (iVar3 == 0)
			{
				return 1;
			}
			iVar2 = SKILLS_EvaluateSkillFormula(pUnit, *(uint32_t*)(iVar3 + 0x144), iVar2, uVar1);
			if (iVar2 < 1)
			{
				iVar2 = 1;
			}
		}
		sub_6FABD690(iVar2, &local_5c);
	}
	return 1;
}

//D2Client.0x6FB38740
uint32_t __fastcall sub_6FB38740(D2UnitStrc* pUnit)
{
	short sVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	int iStack_68;
	int32_t local_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar5 = pUnit->dwClassId, -1 < iVar5)) &&
	        (iVar5 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (((iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar5 * 0x1a4, iVar5 != 0 &&
	                                                                                        (-1 < *(short*)(iVar5 + 0x2c))) &&
	        (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 != nullptr))))
	{
		uVar3 = MISSILE_GetLevel(pUnit);
		iVar6 = *(int*)(iVar5 + 0x70) * (uVar3 - 1) + *(int*)(iVar5 + 0x6c);
		if (iVar6 < 1)
		{
			iVar6 = MISSILE_GetSkill(pUnit);
			if (iVar6 < 0)
			{
				return 1;
			}
			if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar6)
			{
				return 1;
			}
			iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar6 * 0x23c;
			if (iVar4 == 0)
			{
				return 1;
			}
			iVar6 = SKILLS_EvaluateSkillFormula(pDVar2, *(uint32_t*)(iVar4 + 0x144), iVar6, uVar3);
			if (iVar6 < 1)
			{
				iVar6 = 1;
			}
		}
		iVar4 = MISSILE_GetSkill(pUnit);
		sub_6FABDB00(pUnit, (int)*(short*)(iVar5 + 0x2c), iVar6,
		    (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2, iVar4, uVar3);
		if (-1 < *(short*)(iVar5 + 0x2e))
		{
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				local_64 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&local_64 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&local_64 + 2)) = 0;
			}
			else
			{
				local_64 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar3 = pUnit->dwUnitType;
			if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
			{
				iStack_68 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_68 = 0;
			}
			else
			{
				iStack_68 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar3 = MISSILE_GetLevel(pUnit);
			iVar6 = MISSILE_GetSkill(pUnit);
			sVar1 = *(short*)(iVar5 + 0x2e);
			pDVar2 = pUnit;
			if (((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1)) &&
			    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))
			{
				return 1;
			}
			puVar7 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			uStack_5c = 0x20;
			iStack_40 = iStack_68;
			DStack_3c = local_64;
			pDStack_58 = pDVar2;
			pDStack_54 = pUnit;
			iStack_4c = (int)sVar1;
			iStack_30 = iVar6;
			uStack_2c = uVar3;
			sub_6FB3E070(&uStack_5c);
		}
	}
	return 1;
}

//D2Client.0x6FB38940
uint32_t __fastcall sub_6FB38940(D2UnitStrc* pUnit)
{
	int iVar1;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		sub_6FB389A0(pUnit, *(int*)(iVar1 + 0x6c), *(int*)(iVar1 + 0x70), (int)*(short*)(iVar1 + 0x2c), (int)*(short*)(iVar1 + 0x2e));
	}
	return 1;
}

//D2Client.0x6FB389A0
void __fastcall sub_6FB389A0(D2UnitStrc* pUnit, int a2, int a3, int a4, int a5)
{
	uint32_t uVar1;
	int64_t lVar2;
	uint64_t DVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t uVar9;
	int iVar10;
	uint32_t* puVar11;
	int iStack_78;
	int32_t DStack_74;
	int iStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_34;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar5 = sub_6FB26AD0((int)pUnit);
	if (pDVar5 != nullptr)
	{
		iVar6 = MISSILE_GetSkill(pUnit);
		uVar7 = MISSILE_GetLevel(pUnit);
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_78 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_78 = 0;
		}
		else
		{
			iStack_78 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_74 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_74 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_74 + 2)) = 0;
		}
		else
		{
			DStack_74 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		if (-1 < a4)
		{
			puVar11 = &uStack_5c;
			for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar11 = 0;
				puVar11 = puVar11 + 1;
			}
			iStack_34 = a3;
			uStack_5c = 0x524;
			iStack_4c = 0x1c8;
			pDStack_54 = pUnit;
			if (0 < a2)
			{
				uVar4 = a2 * 4;
				uVar1 = uVar4 + 1;
				iStack_6c = a2;
				pDStack_58 = pDVar5;
				iStack_30 = iVar6;
				uStack_2c = uVar7;
				do
				{
					if ((int)uVar1 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						lVar2 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5;
						uVar9 = (pUnit->pSeed).nHighSeed;
						if ((uVar1 & uVar4) == 0)
						{
							DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar9);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)(lVar2 + (uint64_t)uVar9);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
						}
					}
					iVar8 = uVar9 + a2 * -2 + iStack_78;
					if ((int)uVar1 < 1)
					{
						uVar9 = 0;
					}
					else
					{
						uVar9 = (pUnit->pSeed).nLowSeed;
						if ((uVar1 & uVar4) == 0)
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = uVar4 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
						}
						else
						{
							DVar3 = (uint64_t)((uint64_t)uVar9 * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
							(*(uint64_t*)&pUnit->pSeed) = DVar3;
							uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar1);
						}
					}
					iVar10 = uVar9 + a2 * -2 + (int)DStack_74;
					uVar9 = UNITS_GetDistanceToCoordinates(pUnit, iVar8, iVar10);
					if (3 < (int)uVar9)
					{
						iStack_40 = iVar8;
						iStack_3c = iVar10;
						sub_6FB3E070(&uStack_5c);
					}
					iStack_6c = iStack_6c + -1;
				} while (iStack_6c != 0);
			}
		}
		if (-1 < a5)
		{
			iVar8 = 0;
			do
			{
				puVar11 = &uStack_5c;
				for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
				{
					*puVar11 = 0;
					puVar11 = puVar11 + 1;
				}
				iStack_48 = *(int*)((int)dword_6FB709C0 + iVar8) + iStack_78;
				iStack_44 = *(int*)((int)dword_6FB70A08 + iVar8) + (int)DStack_74;
				uStack_5c = 1;
				iStack_4c = a5;
				pDStack_58 = pDVar5;
				iStack_30 = iVar6;
				uStack_2c = uVar7;
				sub_6FB3E070(&uStack_5c);
				iVar8 = iVar8 + 4;
			} while (iVar8 < 0x48);
		}
	}
}

//D2Client.0x6FB38BF0
uint32_t __fastcall sub_6FB38BF0(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;
	code* pcStack_8;

	if (((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	         (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                           (-1 < *(short*)(iVar1 + 0x2c))))) &&
	    (0 < *(int*)(iVar1 + 0x6c)))
	{
		puVar4 = &local_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		uVar2 = pUnit->dwUnitType;
		local_5c = 3;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			local_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_48 = 0;
		}
		else
		{
			local_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_30 = MISSILE_GetSkill(pUnit);
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		iStack_4c = (int)*(short*)(iVar1 + 0x2c);
		uStack_2c = MISSILE_GetLevel(pUnit);
		if (*(int*)(iVar1 + 0x70) != 0)
		{
			pcStack_8 = (code*)(sub_6FAC9E80);
		}
		sub_6FABD690(*(int*)(iVar1 + 0x6c), &local_5c);
	}
	return 1;
}

//D2Client.0x6FB38D20
uint32_t __fastcall sub_6FB38D20(D2UnitStrc* pUnit, int* a2)
{
	short sVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint32_t* puVar7;
	int iStack_6c;
	int32_t local_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit == nullptr) || (iVar2 = pUnit->dwClassId, iVar2 < 0)) ||
	        (iVar5 = *(int*)((uint8_t*)&sgptDataTables), *(int*)(iVar5 + 0xb6c) <= iVar2)) ||
	    (iVar2 = *(int*)(iVar5 + 0xb64) + iVar2 * 0x1a4, iVar2 == 0))
	{
		return 1;
	}
	if ((a2 != nullptr) &&
	    (((((*a2 != 1 || (iVar3 = a2[1], iVar3 < 0)) ||
	           ((*(int*)(iVar5 + 0xa80) <= iVar3 ||
	               ((iVar3 = (int)*(short*)(*(int*)(iVar5 + 0xa78) + 0x18 + iVar3 * 0x1a8), iVar3 < 0 ||
	                                                                                            (*(int*)(iVar5 + 0xa98) <= iVar3)))))) ||
	          (iVar5 = *(int*)(iVar5 + 0xa90) + iVar3 * 0x134, iVar5 == 0)) ||
	        (((uint32_t) * (uint8_t*)(iVar5 + 5) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0xc)) == 0))))
	{
		return 0;
	}
	if (-1 < *(short*)(iVar2 + 0x2c))
	{
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			local_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&local_68 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&local_68 + 2)) = 0;
		}
		else
		{
			local_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iStack_6c = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_6c = 0;
		}
		else
		{
			iStack_6c = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar4 = MISSILE_GetLevel(pUnit);
		iVar5 = MISSILE_GetSkill(pUnit);
		sVar1 = *(short*)(iVar2 + 0x2c);
		pDVar6 = sub_6FB26AD0((int)pUnit);
		if (pDVar6 != nullptr)
		{
			puVar7 = &uStack_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			iStack_48 = iStack_6c;
			uStack_5c = 1;
			DStack_44 = local_68;
			pDStack_58 = pDVar6;
			iStack_4c = (int)sVar1;
			iStack_30 = iVar5;
			uStack_2c = uVar4;
			sub_6FB3E070(&uStack_5c);
		}
	}
	sub_6FB389A0(pUnit, *(int*)(iVar2 + 0x6c), *(int*)(iVar2 + 0x70), (int)*(short*)(iVar2 + 0x2e),
	    (int)*(short*)(iVar2 + 0x30));
	return 1;
}

//D2Client.0x6FB38F00
uint32_t __fastcall sub_6FB38F00(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	int iStack_4c;
	int local_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		puVar5 = &local_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 1;
		}
		local_5c = 0x21;
		local_58 = sub_6FB26AD0((int)pUnit);
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			local_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			local_48 = 0;
		}
		else
		{
			local_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_4c = (int)*(short*)(iVar1 + 0x2c);
		iStack_40 = D2COMMON_10175_PathGetFirstPointX(pUnit->pDynamicPath);
		iStack_3c = D2COMMON_10176_PathGetFirstPointY(pUnit->pDynamicPath);
		pDVar3 = sub_6FB3E070(&local_5c);
		if (pDVar3 != nullptr)
		{
			sub_6FB5FDA0((int)pDVar3, *(uint32_t*)(iVar1 + 0x6c), *(uint32_t*)(iVar1 + 0x70));
			sub_6FB60080((int)pDVar3, 0, *(uint32_t*)(iVar1 + 0x74));
			sub_6FB5FDF0((int)pDVar3);
		}
	}
	return 1;
}

//D2Client.0x6FB39050
uint32_t __fastcall sub_6FB39050(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	uint8_t nDirection;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar3 = pUnit->dwClassId, -1 < iVar3)) &&
	        (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 != 0 &&
	                                                                                       (sVar1 = *(short*)(iVar3 + 0x2c), -1 < sVar1))))
	{
		if (a2 != 0)
		{
			return 0;
		}
		uVar2 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		pDVar4 = pUnit;
		if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 != nullptr))
		{
			puVar6 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar6 = 0;
				puVar6 = puVar6 + 1;
			}
			uStack_5c = 0x20;
			uStack_40 = 0;
			uStack_3c = 0;
			pDStack_58 = pDVar4;
			pDStack_54 = pUnit;
			iStack_4c = (int)sVar1;
			iStack_30 = iVar3;
			uStack_2c = uVar2;
			pDVar4 = sub_6FB3E070(&uStack_5c);
			if (pDVar4 != nullptr)
			{
				nDirection = PATH_GetDirection(pUnit->pDynamicPath);
				PATH_SetDirection(pDVar4->pDynamicPath, nDirection);
			}
		}
	}
	return 1;
}

//D2Client.0x6FB39150
uint32_t __fastcall sub_6FB39150(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		pDVar2 = sub_6FB26AD0((int)pUnit);
		if (pDVar2 != nullptr)
		{
			puVar4 = &local_5c;
			for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			local_58 = pDVar2;
			local_54 = pUnit;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			if (-1 < *(short*)(iVar1 + 0x2c))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x2c);
				sub_6FB3E070(&local_5c);
			}
			if (-1 < *(short*)(iVar1 + 0x2e))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x2e);
				sub_6FB3E070(&local_5c);
			}
			if (-1 < *(short*)(iVar1 + 0x30))
			{
				iStack_4c = (int)*(short*)(iVar1 + 0x30);
				sub_6FB3E070(&local_5c);
			}
		}
	}
	return 1;
}

//D2Client.0x6FB39230
uint32_t __fastcall sub_6FB39230(D2UnitStrc* pUnit)
{
	int iVar1;
	uint8_t nDirection;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int local_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                        (-1 < *(short*)(iVar1 + 0x2c))) &&
	        (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 != nullptr))))
	{
		puVar4 = &local_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		local_4c = (int)*(short*)(iVar1 + 0x2c);
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		pDStack_58 = pDVar2;
		pDStack_54 = pUnit;
		pDVar2 = sub_6FB3E070(&local_5c);
		if (pDVar2 != nullptr)
		{
			nDirection = PATH_GetDirection(pUnit->pDynamicPath);
			PATH_SetDirection(pDVar2->pDynamicPath, nDirection);
		}
	}
	return 1;
}

//D2Client.0x6FB392F0
uint32_t __fastcall sub_6FB392F0(D2UnitStrc* pUnit, int a2)
{
	short sVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	int32_t DVar7;
	int iVar8;

	if ((((pUnit != nullptr) && (iVar2 = pUnit->dwClassId, -1 < iVar2)) &&
	        (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0 &&
	                                                                                       (-1 < *(short*)(iVar2 + 0x2c)))))
	{
		if (a2 != 0)
		{
			return 0;
		}
		uVar3 = *(uint32_t*)(iVar2 + 0x70);
		uVar5 = MISSILE_GetLevel(pUnit);
		iVar6 = MISSILE_GetSkill(pUnit);
		sVar1 = *(short*)(iVar2 + 0x2c);
		iVar2 = *(int*)(iVar2 + 0x6c);
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
		}
		else
		{
			DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar8 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar8 = 0;
		}
		else
		{
			iVar8 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		sub_6FB35D10(pUnit, iVar8, (int)DVar7, iVar2, (int)sVar1, iVar6, uVar5, uVar3, 1);
	}
	return 1;
}

//D2Client.0x6FB39400
uint32_t __fastcall sub_6FB39400(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	int iStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		puVar4 = &local_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		local_58 = sub_6FB26AD0((int)pUnit);
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		if (-1 < *(short*)(iVar1 + 0x2c))
		{
			iStack_4c = (int)*(short*)(iVar1 + 0x2c);
			sub_6FB3E070(&local_5c);
		}
		if (-1 < *(short*)(iVar1 + 0x2e))
		{
			iStack_4c = (int)*(short*)(iVar1 + 0x2e);
			pDVar2 = sub_6FB3E070(&local_5c);
			if (pDVar2 != nullptr)
			{
				sub_6FB5FC80((int)pDVar2, 0, 0, *(int*)(iVar1 + 0x6c));
			}
		}
	}
	return 1;
}

//D2Client.0x6FB394D0
uint32_t __fastcall sub_6FB394D0(uint32_t a1, int a2)
{
	if (a2 == 0)
	{
		sub_6FAB7EE0();
		return 1;
	}
	return 0;
}

//D2Client.0x6FB394F0
void __fastcall sub_6FB394F0(uint32_t a1)
{
	dword_6FB91214 = a1;
}

//D2Client.0x6FB39500
uint32_t __cdecl sub_6FB39500()
{
	return dword_6FB91214;
}

//D2Client.0x6FB39510
uint32_t __fastcall sub_6FB39510(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pMissile;
	int iVar3;
	uint32_t uVar4;

	if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
	{
		return 0;
	}
	iVar1 = a2[2];
	pDVar2 = (D2UnitStrc*)a2[1];
	pMissile = (D2UnitStrc*)*a2;
	if (((pUnit->dwFlags >> 3 & 1) != 0) && ((pUnit->dwFlags >> 2 & 1) != 0))
	{
		if ((*(char*)(iVar1 + 0x188) != '\0') && (iVar3 = STATES_CheckState(pUnit, 0x56), iVar3 != 0))
		{
			return 0;
		}
		iVar3 = MISSILE_CheckUnitIfOwner(pMissile, pUnit);
		if (iVar3 == 0)
		{
			if (((pDVar2 != nullptr) && (uVar4 = sub_6FB29D80(pDVar2, pUnit), uVar4 == 0)) &&
			    (*(char*)(iVar1 + 0x187) == '\0'))
			{
				return 0;
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB395B0
uint32_t __fastcall sub_6FB395B0(D2UnitStrc* pUnit, uint32_t* a2)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pMissile;
	int iVar2;
	int iVar3;
	uint32_t uVar4;

	if (pUnit != nullptr)
	{
		if (pUnit->dwUnitType == 1)
		{
			iVar2 = STATLIST_GetUnitAlignment(pUnit);
			if (iVar2 == 2)
			{
				return 1;
			}
		}
		else if (pUnit->dwUnitType == 0)
		{
			iVar2 = a2[2];
			pDVar1 = (D2UnitStrc*)a2[1];
			pMissile = (D2UnitStrc*)*a2;
			if (((pUnit->dwFlags >> 3 & 1) != 0) && ((pUnit->dwFlags >> 2 & 1) != 0))
			{
				if ((*(char*)(iVar2 + 0x188) != '\0') &&
				    (iVar3 = STATES_CheckState(pUnit, 0x56), iVar3 != 0))
				{
					return 0;
				}
				iVar3 = MISSILE_CheckUnitIfOwner(pMissile, pUnit);
				if (iVar3 == 0)
				{
					if (((pDVar1 != nullptr) && (uVar4 = sub_6FB29D80(pDVar1, pUnit), uVar4 == 0)) && (*(char*)(iVar2 + 0x187) == '\0'))
					{
						return 0;
					}
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}

//D2Client.0x6FB39650
uint32_t __fastcall sub_6FB39650(D2UnitStrc* pUnit, uint32_t* a2)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pMissile;
	int iVar3;
	uint32_t uVar4;

	if ((pUnit == nullptr) || ((pUnit->dwUnitType != 0 && (pUnit->dwUnitType != 1))))
	{
		return 0;
	}
	iVar1 = a2[2];
	pDVar2 = (D2UnitStrc*)a2[1];
	pMissile = (D2UnitStrc*)*a2;
	if (((pUnit->dwFlags >> 3 & 1) != 0) && ((pUnit->dwFlags >> 2 & 1) != 0))
	{
		if ((*(char*)(iVar1 + 0x188) != '\0') && (iVar3 = STATES_CheckState(pUnit, 0x56), iVar3 != 0))
		{
			return 0;
		}
		iVar3 = MISSILE_CheckUnitIfOwner(pMissile, pUnit);
		if (iVar3 == 0)
		{
			if (((pDVar2 != nullptr) && (uVar4 = sub_6FB29D80(pDVar2, pUnit), uVar4 == 0)) &&
			    (*(char*)(iVar1 + 0x187) == '\0'))
			{
				return 0;
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FB396F0
uint32_t __fastcall sub_6FB396F0(int* a1)
{
	int iVar1;

	if ((((a1 != nullptr) && (*a1 == 3)) && (iVar1 = a1[1], -1 < iVar1)) &&
	    (((iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) &&
	          (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0)) &&
	        (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar1 + 4)) != 0))))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FB39750
void __fastcall sub_6FB39750(D2UnitStrc* pUnit, D2ActiveRoomStrc* pActiveRoom, int a3, int a4, uint32_t a5)
{
	int iVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar2;
	int nCollisionMask;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0))
	{
		MISSILE_AllocMissileData(pUnit);
		UNITS_ChangeAnimMode(pUnit, (uint32_t) * (uint8_t*)(iVar1 + 0x183));
		PATH_AllocDynamicPath(nullptr, pActiveRoom, a3, a4, pUnit, 1);
		pDynamicPath = pUnit->pDynamicPath;
		if (*(char*)(iVar1 + 0x184) == '\0')
		{
			nCollisionMask = 0;
		}
		else
		{
			nCollisionMask = 0x40;
		}
		PATH_SetFootprintCollisionMask(pDynamicPath, nCollisionMask);
		PATH_SetMoveTestCollisionMask(pDynamicPath, *(int*)(byte_6FB9121C + (uint32_t) * (uint8_t*)(iVar1 + 0x183) * 8));
		if (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar1 + 4)) == 0)
		{
			uVar2 = pUnit->dwFlags & 0xfffffffb;
		}
		else
		{
			uVar2 = pUnit->dwFlags | 4;
		}
		pUnit->dwFlags = uVar2;
		pUnit->dwFlags = uVar2 & 0xfffffff5 | 0x20;
	}
}

//D2Client.0x6FB39830
void __fastcall sub_6FB39830(D2UnitStrc* pUnit)
{
	MISSTREAM_FreeMissileStream(pUnit);
	MISSILE_FreeMissileData(pUnit);
	sub_6FB5FB70((int)pUnit);
	sub_6FB59320((int)pUnit);
	if (ghAct != nullptr)
	{
		D2Common_10228(pUnit);
		UNITROOM_RemoveUnitFromRoom(pUnit);
	}
	PATH_FreeDynamicPath(nullptr, pUnit->pDynamicPath);
	pUnit->pDynamicPath = nullptr;
}

//D2Client.0x6FB39880
uint32_t __fastcall sub_6FB39880(D2UnitStrc* pUnit2, int a2)
{
	D2DynamicPathStrc* pDynamicPath;
	uint8_t nDirection;
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pUnit;
	int iVar3;
	uint32_t* puVar4;
	uint32_t local_68;
	int iStack_64;
	int32_t DStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	if (a2 != 0)
	{
		return 0;
	}
	local_68 = 0xffffffff;
	iVar1 = MISSILE_GetClassId(pUnit2);
	switch (iVar1)
	{
	case 0x110:
		local_68 = 0x158;
		break;
	case 0x111:
	case 0x112:
	case 0x1a1:
		local_68 = 0x159;
	}
	uVar2 = pUnit2->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		DStack_60 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_60 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_60 + 2)) = 0;
	}
	else
	{
		DStack_60 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	uVar2 = pUnit2->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		iStack_64 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iStack_64 = 0;
	}
	else
	{
		iStack_64 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	uVar2 = MISSILE_GetLevel(pUnit2);
	iVar1 = MISSILE_GetSkill(pUnit2);
	pDStack_58 = sub_6FB26AD0((int)pUnit2);
	if (pDStack_58 != nullptr)
	{
		puVar4 = &uStack_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		DStack_44 = DStack_60;
		uStack_5c = 1;
		iStack_48 = iStack_64;
		uStack_4c = local_68;
		iStack_30 = iVar1;
		uStack_2c = uVar2;
		pUnit = sub_6FB3E070(&uStack_5c);
		if (pUnit != nullptr)
		{
			pDynamicPath = pUnit->pDynamicPath;
			nDirection = PATH_GetDirection(pUnit2->pDynamicPath);
			PATH_SetDirection(pDynamicPath, nDirection);
			UNITS_SetAnimationSpeed(pUnit, 0x80);
		}
	}
	return 1;
}

//D2Client.0x6FB39A70
bool __fastcall sub_6FB39A70(int a1, int* a2)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (a2 == nullptr)
	{
		return true;
	}
	pDVar1 = sub_6FB26AD0(a1);
	if (pDVar1 == nullptr)
	{
		return true;
	}
	if (pDVar1->dwUnitType != 0)
	{
		return false;
	}
	if (*a2 != 1)
	{
		return false;
	}
	uVar2 = sub_6FAB1B00(a2[3]);
	return uVar2 == pDVar1->dwUnitId;
}

//D2Client.0x6FB39AC0
void __fastcall sub_6FB39AC0(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = MISSILE_GetCurrentFrame(pUnit);
	if (iVar1 == 0x96)
	{
		sub_6FAB7E70(0x19, 0, 4000, 0);
		sub_6FB3D880(pUnit);
		return;
	}
	if (iVar1 == 0x32)
	{
		sub_6FB55820(0x121e, nullptr, 0.0, 0.0, 0);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB39B10
void __fastcall sub_6FB39B10(D2UnitStrc* pUnit)
{
	int iVar1;

	iVar1 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar1 == 8)
	{
		sub_6FB5FD00((int)pUnit, 0, 0, 0x100, 0);
		UNITS_SetAnimationSpeed(pUnit, (int)pUnit->wAnimSpeed >> 1);
	}
	else if (iVar1 == 0x23)
	{
		UNITS_SetAnimationSpeed(pUnit, pUnit->wAnimSpeed * 2);
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB39B60
void __fastcall sub_6FB39B60(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int32_t DVar7;
	D2UnitStrc** ppDVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar2 = sub_6FB26AD0((int)pUnit);
	if (pDVar2 != nullptr)
	{
		iVar3 = MISSILE_GetTargetY(pUnit);
		if (iVar3 == 0)
		{
			uVar4 = MISSILE_GetTargetX(pUnit);
			pDVar5 = sub_6FB269F0(uVar4, 2);
			if (pDVar5 != nullptr)
			{
				uVar4 = pUnit->dwUnitType;
				if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
				{
					iVar3 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar3 = 0;
				}
				else
				{
					iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar4 = pDVar5->dwUnitType;
				if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
				{
					iVar6 = pDVar5->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar5->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pDVar5->pDynamicPath);
				}
				uVar4 = pUnit->dwUnitType;
				if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
				{
					DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
				}
				else
				{
					DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				ppDVar8 = sub_6FAB6A90((int*)pDVar5);
				puVar10 = &uStack_5c;
				for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
				{
					*puVar10 = 0;
					puVar10 = puVar10 + 1;
				}
				pDStack_58 = pDVar2;
				pDStack_54 = pUnit;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				uStack_4c = 0x179;
				pDVar2 = sub_6FB3E070(&uStack_5c);
				if (pDVar2 != nullptr)
				{
					sub_6FB5FB10((int)pDVar2);
					sub_6FB5FC80((int)pDVar2, 0, 0, 0);
					sub_6FB5FCB0((int)pDVar2, 0, 0, 2, 1);
					sub_6FB5FD00((int)pDVar2, 0, 0, 0, 1);
					MISSILE_SetTargetX(pDVar2, iVar3 - iVar6);
					MISSILE_SetTargetY(pDVar2, (int)DVar7 - (int)ppDVar8);
				}
			}
			DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar1;
			iVar3 = (int)(((uint64_t)DVar1 & 0xffffffff) % 0x23) + 10;
		}
		MISSILE_SetTargetY(pUnit, iVar3 + -1);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB39D00
void __fastcall sub_6FB39D00(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB26AD0((int)pUnit);
	if (pDVar1 != nullptr)
	{
		pUnit->nSeqCurrentFramePrecise = 0;
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB39D20
uint32_t __fastcall sub_6FB39D20(D2UnitStrc* pUnit)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	uint32_t local_4c;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar1 = sub_6FB26AD0((int)pUnit);
	if (pDVar1 != nullptr)
	{
		puVar3 = &local_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_4c = 0x177;
		local_58 = pDVar1;
		local_54 = pUnit;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		pDVar1 = sub_6FB3E070(&local_5c);
		if (pDVar1 != nullptr)
		{
			iVar2 = MISSILE_GetTargetX(pUnit);
			MISSILE_SetTargetX(pDVar1, iVar2);
		}
	}
	return 1;
}

//D2Client.0x6FB39D90
uint32_t __fastcall sub_6FB39D90(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint64_t DVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	uint32_t local_4c;
	int iStack_48;
	int32_t DStack_44;
	uint32_t uStack_34;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) < 0x176)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + 0x263f4;
	}
	pDVar3 = sub_6FB26AD0((int)pUnit);
	if (pDVar3 != nullptr)
	{
		puVar6 = &local_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		local_5c = 0x8005;
		local_4c = 0x178;
		local_58 = pDVar3;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uStack_34 = 0;
		uVar1 = pUnit->dwUnitType;
		iStack_10 = (int)*(short*)(iVar5 + 0x96);
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_48 = 0;
		}
		else
		{
			iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		pDVar3 = sub_6FB3E070(&local_5c);
		if (pDVar3 != nullptr)
		{
			iVar5 = MISSILE_GetTargetX(pUnit);
			MISSILE_SetTargetX(pDVar3, iVar5);
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			MISSILE_SetTargetY(pDVar3, (int)(((uint64_t)DVar2 & 0xffffffff) % 0x23) + 10);
		}
	}
	return 1;
}

//D2Client.0x6FB39ED0
void __fastcall sub_6FB39ED0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	uint32_t nTargetX;
	int iVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int iVar7;
	int iStack_d4;
	int aiStack_cc[29];
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	nTargetX = MISSILE_GetTargetX(pUnit);
	iVar2 = MISSILE_GetRemainingFrames(pUnit);
	pDVar3 = sub_6FB269F0(nTargetX, 2);
	if ((pDVar3 != nullptr) && (iVar2 == 10))
	{
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) < 0x177)
		{
			iStack_d4 = 0;
		}
		else
		{
			iStack_d4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + 0x26598;
		}
		aiStack_cc[0xd] = 6;
		aiStack_cc[0xe] = 6;
		aiStack_cc[6] = 5;
		aiStack_cc[9] = 5;
		aiStack_cc[0x1a] = 5;
		aiStack_cc[0] = -4;
		aiStack_cc[1] = 2;
		aiStack_cc[2] = 4;
		aiStack_cc[3] = 0xfffffffd;
		aiStack_cc[4] = 0xfffffffe;
		aiStack_cc[5] = 3;
		aiStack_cc[7] = 0xfffffffd;
		aiStack_cc[8] = 0xfffffffb;
		aiStack_cc[10] = 0xfffffffa;
		aiStack_cc[0xb] = 0xffffffff;
		aiStack_cc[0xc] = 0;
		aiStack_cc[0xf] = 4;
		aiStack_cc[0x10] = 0xfffffffc;
		aiStack_cc[0x11] = 0xfffffffe;
		aiStack_cc[0x12] = 1;
		aiStack_cc[0x13] = 7;
		aiStack_cc[0x14] = 0;
		aiStack_cc[0x15] = 3;
		aiStack_cc[0x16] = 0xfffffffc;
		aiStack_cc[0x17] = 0xfffffffd;
		aiStack_cc[0x18] = 4;
		aiStack_cc[0x19] = 0xfffffffb;
		aiStack_cc[0x1b] = 0xfffffffd;
		pDVar3 = sub_6FB26AD0((int)pUnit);
		if (pDVar3 != nullptr)
		{
			piVar6 = aiStack_cc + 0x1c;
			for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*piVar6 = 0;
				piVar6 = piVar6 + 1;
			}
			aiStack_cc[0x1c] = 0x8102;
			uStack_4c = 0x176;
			pDStack_58 = pDVar3;
			pDStack_54 = pUnit;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			iVar2 = 0;
			do
			{
				iStack_40 = *(int*)((int)aiStack_cc + iVar2);
				iStack_3c = *(int*)((int)aiStack_cc + iVar2 + 0x38);
				iVar7 = iStack_40;
				if (iStack_40 < 0)
				{
					iVar7 = -iStack_40;
				}
				iVar5 = iStack_3c;
				if (iStack_3c < 0)
				{
					iVar5 = -iStack_3c;
				}
				iVar4 = iVar7 + iVar5 * 2;
				if (iStack_40 < iStack_3c)
				{
					iVar4 = iVar5 + iVar7 * 2;
				}
				iStack_10 = ((int)*(short*)(iStack_d4 + 0x96) * (iVar4 >> 1)) / 6;
				pDVar3 = sub_6FB3E070((uint32_t*)(aiStack_cc + 0x1c));
				if (pDVar3 != nullptr)
				{
					MISSILE_SetTargetX(pDVar3, nTargetX);
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					MISSILE_SetTargetY(pDVar3, (int)(((uint64_t)DVar1 & 0xffffffff) % 0x23) + 10);
				}
				iVar2 = iVar2 + 4;
			} while (iVar2 < 0x38);
		}
		sub_6FAB7E70(4, 0x50, 0x50, 400);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3A130
void __fastcall sub_6FB3A130(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	D2UnitStrc** ppDVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	uint32_t* puVar10;
	int32_t DStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_48;
	D2UnitStrc** ppDStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	iVar4 = MISSILE_GetCurrentFrame(pUnit);
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) < 0x17c)
	{
		(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
	}
	else
	{
		DStack_68 = (int32_t)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + 0x26dcc);
	}
	pDVar1 = &pUnit->pSeed;
	uVar5 = sub_6FAA88F0((uint64_t*)pDVar1, 0x14);
	uVar6 = sub_6FAA88F0((uint64_t*)pDVar1, 0x14);
	puVar10 = &uStack_5c;
	for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	uStack_5c = 0x21;
	pDStack_58 = sub_6FB26AD0((int)pUnit);
	uVar2 = pUnit->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_48 = 0;
	}
	else
	{
		iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	ppDStack_44 = sub_6FAB6A90((int*)pUnit);
	iStack_40 = sub_6FAB6A60((int*)pUnit);
	iStack_40 = iStack_40 + (uVar5 - 10);
	ppDVar7 = sub_6FAB6A90((int*)pUnit);
	iStack_3c = (int)ppDVar7 + (uVar6 - 10);
	iStack_30 = MISSILE_GetSkill(pUnit);
	uStack_2c = MISSILE_GetLevel(pUnit);
	uStack_4c = 0x17c;
	sub_6FB3E070(&uStack_5c);
	if (((iVar4 < (int)*(short*)((int)DStack_68 + 0x96) - *(int*)((int)DStack_68 + 0x38)) &&
	        ((int)*(short*)((int)DStack_68 + 0x96) - *(int*)((int)DStack_68 + 0x3c) < iVar4)) &&
	    (pDVar8 = sub_6FB26AD0((int)pUnit), pDVar8 != nullptr))
	{
		uVar5 = pDVar8->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_68 = (int32_t)pDVar8->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar8->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
		}
		else
		{
			DStack_68 = (int32_t)PATH_GetXPosition(pDVar8->pDynamicPath);
		}
		DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
		*(uint64_t*)pDVar1 = DVar3;
		iVar4 = (int)(((uint64_t)DVar3 & 0xffffffff) % 10) + -5 + (int)DStack_68;
		uVar5 = pDVar8->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_68 = (*(int32_t*)&pDVar8->pDynamicPath->tTargetCoord);
		}
		else if (pDVar8->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
		}
		else
		{
			DStack_68 = (int32_t)PATH_GetYPosition(pDVar8->pDynamicPath);
		}
		DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
		*(uint64_t*)pDVar1 = DVar3;
		puVar10 = &uStack_5c;
		for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
		{
			*puVar10 = 0;
			puVar10 = puVar10 + 1;
		}
		uStack_5c = 0x20;
		iStack_3c = (int)(((uint64_t)DVar3 & 0xffffffff) % 10) + -5 + (int)DStack_68;
		pDStack_58 = pDVar8;
		pDStack_54 = pUnit;
		iStack_40 = iVar4;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uStack_4c = 0x17e;
		pDVar8 = sub_6FB3E070(&uStack_5c);
		if (pDVar8 != nullptr)
		{
			DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar3;
			sub_6FB5FD00((int)pDVar8, 0, 0, -3 - (int)(((uint64_t)DVar3 & 0xffffffff) % 3), 1);
			sub_6FB60080((int)pDVar8, 0, 0xf);
			sub_6FB5FDF0((int)pDVar8);
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3A3E0
void __fastcall sub_6FB3A3E0(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint64_t uVar2;
	uint32_t uVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	D2UnitStrc* pDVar8;
	int32_t DVar9;
	int32_t DVar10;
	int iVar11;
	uint32_t* puVar12;
	bool bVar13;
	uint8_t* pbStack_6c;
	int32_t DStack_64;
	uint32_t uStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	uVar3 = MISSILE_GetCurrentFrame(pUnit);
	pDVar4 = sub_6FB26AD0((int)pUnit);
	if (uVar3 == 0x96)
	{
		sub_6FAB7E70(0x19, 0, 4000, 0);
	}
	pbStack_6c = &byte_6FB70A58;
	uStack_60 = 0x145;
	do
	{
		if ((int)uStack_60 < (int)uVar3)
			break;
		if (uVar3 == uStack_60)
		{
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_64 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
			}
			else
			{
				DStack_64 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iVar5 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar5 = 0;
			}
			else
			{
				iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar6 = MISSILE_GetLevel(pUnit);
			iVar7 = MISSILE_GetSkill(pUnit);
			if (pDVar4 != nullptr)
			{
				puVar12 = &uStack_5c;
				for (iVar11 = 0x17; iVar11 != 0; iVar11 = iVar11 + -1)
				{
					*puVar12 = 0;
					puVar12 = puVar12 + 1;
				}
				uStack_5c = 1;
				iStack_48 = *(int*)(pbStack_6c + -8) + iVar5;
				uStack_4c = 0x154;
				DStack_44 = (int32_t)(*(int*)(pbStack_6c + -4) + (int)DStack_64);
				pDStack_58 = pDVar4;
				iStack_30 = iVar7;
				uStack_2c = uVar6;
				pDVar8 = sub_6FB3E070(&uStack_5c);
				if (pDVar8 != nullptr)
				{
					PATH_SetDirection(pDVar8->pDynamicPath, *pbStack_6c);
					MISSILE_SetTotalFrames(pDVar8, uVar3);
					MISSILE_SetCurrentFrame(pDVar8, uVar3);
				}
			}
		}
		pbStack_6c = pbStack_6c + 0xc;
		uStack_60 = uStack_60 - 0x19;
	} while ((int)pbStack_6c < (int)&byte_6FB70AAC);
	if ((int)uVar3 < 0xa5)
	{
		uVar6 = uVar3 & 0x80000001;
		bVar13 = uVar6 == 0;
		if ((int)uVar6 < 0)
		{
			bVar13 = (uVar6 - 1 | 0xfffffffe) == 0xffffffff;
		}
		if (bVar13)
		{
			puVar12 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar12 = 0;
				puVar12 = puVar12 + 1;
			}
			uVar6 = pUnit->dwUnitType;
			uStack_5c = 0x21;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
				pDStack_58 = pDVar4;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_48 = 0;
				pDStack_58 = pDVar4;
			}
			else
			{
				pDStack_58 = pDVar4;
				iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
			}
			else
			{
				DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iStack_40 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iStack_40 = 0;
			}
			else
			{
				iStack_40 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			iStack_40 = iStack_40 + -0xd;
			uVar6 = pUnit->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DVar9 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
			}
			else
			{
				DVar9 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iStack_3c = (int)DVar9 + 3;
			iStack_30 = MISSILE_GetSkill(pUnit);
			uStack_2c = MISSILE_GetLevel(pUnit);
			uStack_4c = 0x153;
			pDVar8 = sub_6FB3E070(&uStack_5c);
			if (pDVar8 != nullptr)
			{
				sub_6FB5FC80((int)pDVar8, 0, 0, 0x46);
				sub_6FB5FCB0((int)pDVar8, 0, 0, -1, 1);
				pDynamicPath = pDVar8->pDynamicPath;
				PATH_SetDirection(pDynamicPath, 0x15);
				D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
			}
		}
	}
	if ((int)uVar3 < 0x96)
	{
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			iVar5 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			DVar10 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar10 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar10 + 2)) = 0;
		}
		else
		{
			DVar10 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		puVar12 = &uStack_5c;
		for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			*puVar12 = 0;
			puVar12 = puVar12 + 1;
		}
		uVar2 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		        (uint64_t)(pUnit->pSeed).nHighSeed;
		(pUnit->pSeed).nLowSeed = (uint32_t)uVar2;
		uStack_5c = 0x21;
		iStack_40 = (int)((uVar2 & 0xffffffff) % 5) + 1 + iVar5 + -0xd;
		DVar1 = (uint64_t)((uVar2 & 0xffffffff) * 0x6ac690c5 + (uVar2 >> 0x20));
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		iStack_3c = (int)(((uint64_t)DVar1 & 0xffffffff) % 10) + -5 + (int)DVar10 + 3;
		pDStack_58 = pDVar4;
		iStack_48 = iVar5 + -0xd;
		DStack_44 = (int32_t)((int)DVar10 + 3);
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uStack_4c = 0x96;
		pDVar4 = sub_6FB3E070(&uStack_5c);
		if (pDVar4 != nullptr)
		{
			UNITS_SetAnimationSpeed(pDVar4, 0x40);
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3A7D0
uint32_t __fastcall sub_6FB3A7D0(D2UnitStrc* pUnit, int a2)
{
	D2SeedStrc* pSeed;
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	int iVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t* puVar8;
	int32_t DStack_68;
	int iStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (a2 != 0)
	{
		return 0;
	}
	pSeed = &pUnit->pSeed;
	iVar4 = MISSILE_GetTargetY(pUnit);
	SEED_InitLowSeed(pSeed, iVar4);
	iVar4 = MISSILE_GetTargetX(pUnit);
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar5 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iVar5 = 0;
	}
	else
	{
		iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DStack_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
	}
	else
	{
		DStack_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	puVar8 = &uStack_5c;
	for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar8 = 0;
		puVar8 = puVar8 + 1;
	}
	uStack_5c = 0x21;
	pDStack_58 = sub_6FB26AD0((int)pUnit);
	DStack_44 = DStack_68;
	uStack_4c = 0x15d;
	iStack_48 = iVar5;
	iStack_30 = MISSILE_GetSkill(pUnit);
	uStack_2c = MISSILE_GetLevel(pUnit);
	iStack_64 = 0;
	if (0 < iVar4)
	{
		do
		{
			uVar3 = (uint64_t)pSeed->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed;
			pSeed->nLowSeed = (uint32_t)uVar3;
			iStack_40 = (int)((uVar3 & 0xffffffff) % 0x14) + -10 + iVar5;
			DVar2 = (uint64_t)((uVar3 & 0xffffffff) * 0x6ac690c5 + (uVar3 >> 0x20));
			*(uint64_t*)pSeed = DVar2;
			DStack_3c = (int32_t)((int)DStack_68 + -10 + (int)(((uint64_t)DVar2 & 0xffffffff) % 0x14));
			if ((iStack_40 == iVar5) && (DStack_3c == DStack_68))
			{
				iStack_64 = iStack_64 + -1;
			}
			else
			{
				pDVar6 = sub_6FB3E070(&uStack_5c);
				if (pDVar6 != nullptr)
				{
					sub_6FAC9E80(pDVar6);
				}
			}
			iStack_64 = iStack_64 + 1;
		} while (iStack_64 < iVar4);
	}
	return 1;
}

//D2Client.0x6FB3A960
void __fastcall sub_6FB3A960(D2UnitStrc* pUnit)
{
	int nTargetY;
	D2UnitStrc* pDVar1;
	int* piVar2;
	uint32_t uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint32_t* puVar8;
	int32_t DStack_6c;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	nTargetY = MISSILE_GetCurrentFrame(pUnit);
	pDVar1 = sub_6FB26AD0((int)pUnit);
	iVar7 = 0;
	iVar5 = 0;
	piVar2 = (int*)(&dword_6FB70AA8);
	do
	{
		if (*piVar2 < nTargetY)
			break;
		piVar2 = piVar2 + 3;
		iVar5 = iVar5 + 1;
	} while ((int)piVar2 < (int)&tbl_6FB70AE4);
	if (nTargetY % *(int*)(byte_6FB70AAC + iVar5 * 0xc) == 0)
	{
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			DStack_6c = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_6c + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_6c + 2)) = 0;
		}
		else
		{
			DStack_6c = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar3 = pUnit->dwUnitType;
		if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
		{
			iVar7 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath != nullptr)
		{
			iVar7 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar3 = MISSILE_GetLevel(pUnit);
		iVar4 = MISSILE_GetSkill(pUnit);
		if (pDVar1 != nullptr)
		{
			puVar8 = &uStack_5c;
			for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			DStack_44 = DStack_6c;
			uStack_5c = 1;
			uStack_4c = 0x15c;
			pDStack_58 = pDVar1;
			iStack_48 = iVar7;
			iStack_30 = iVar4;
			uStack_2c = uVar3;
			pDVar1 = sub_6FB3E070(&uStack_5c);
			if (pDVar1 != nullptr)
			{
				MISSILE_SetTargetX(pDVar1, *(int*)(byte_6FB70AB0 + iVar5 * 0xc));
				MISSILE_SetTargetY(pDVar1, nTargetY);
			}
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3AAA0
void __fastcall sub_6FB3AAA0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	int iVar2;
	int* piVar3;
	int32_t DVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	uint32_t* puVar12;
	int iStack_6c;
	int iStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	iVar2 = MISSILE_GetCurrentFrame(pUnit);
	(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	iVar9 = 0;
	piVar3 = (int*)(&dword_6FB70AF0);
	do
	{
		if (*piVar3 < iVar2)
			break;
		piVar3 = piVar3 + 3;
		iVar9 = iVar9 + 1;
	} while ((int)piVar3 < (int)&tbl_6FB70B20);
	iVar9 = iVar9 * 0xc;
	if (iVar2 % *(int*)(dword_6FB70AF4 + iVar9) == 0)
	{
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			iStack_6c = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_6c = 0;
		}
		else
		{
			iStack_6c = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar7 = pUnit->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath != nullptr)
		{
			DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		puVar12 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar12 = 0;
			puVar12 = puVar12 + 1;
		}
		uStack_5c = 1;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uStack_4c = 0x15f;
		iStack_30 = MISSILE_GetSkill(pUnit);
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_68 = 0;
		if (0 < *(int*)(byte_6FB70AF8 + iVar9))
		{
			do
			{
				DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                   (uint64_t)(pUnit->pSeed).nHighSeed);
				(*(uint64_t*)&pUnit->pSeed) = DVar1;
				iVar10 = (int)(((uint64_t)DVar1 & 0xffffffff) % 10) + -5;
				iVar5 = iVar10;
				if (iVar10 < 0)
				{
					iVar5 = -iVar10;
				}
				if (iVar5 < 2)
				{
					iVar10 = 5;
				}
				DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DVar1 >> 0x20));
				(*(uint64_t*)&pUnit->pSeed) = DVar1;
				iVar5 = (int)(((uint64_t)DVar1 & 0xffffffff) % 10) + -5;
				iVar11 = iVar5;
				if (iVar5 < 0)
				{
					iVar11 = -iVar5;
				}
				if (iVar11 < 2)
				{
					iVar5 = 5;
				}
				iStack_48 = iStack_6c + iVar10 * 2;
				iStack_44 = (int)DVar4 + iVar5 * 2;
				pDVar6 = sub_6FB3E070(&uStack_5c);
				if (pDVar6 != nullptr)
				{
					MISSILE_SetTargetX(pDVar6, pUnit->dwUnitId);
				}
				iStack_68 = iStack_68 + 1;
			} while (iStack_68 < *(int*)(byte_6FB70AF8 + iVar9));
		}
	}
	if (iVar2 < 0x19)
	{
		iVar9 = 3;
	}
	else
	{
		if (0x4a < iVar2)
			goto LAB_6fb3ac6f;
		iVar9 = 2;
	}
	MISSILE_SetTargetX(pUnit, iVar9);
LAB_6fb3ac6f:
	if (iVar2 < 2)
	{
		uVar7 = MISSILE_GetTargetY(pUnit);
		pDVar6 = sub_6FB269F0(uVar7, 2);
		if ((pDVar6 != nullptr) &&
		    (sub_6FB5BA70(pDVar6, 0xb6, 3, 0, 0, 0, 0, 0), pDVar6->dwInteractGUID == 0))
		{
			puVar8 = sub_6FAA4280(pDVar6, 2, 0x3c, 0xff, 0xff, 0xff, 0xff);
			pDVar6->dwInteractGUID = (uint32_t)puVar8;
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3ACE0
uint32_t __fastcall sub_6FB3ACE0(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	D2UnitStrc* pMissile;
	D2UnitStrc* pMissile_00;
	int iVar2;
	uint32_t* puVar3;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int32_t DStack_3c;
	int iStack_30;
	uint32_t uStack_2c;
	int iStack_10;

	if (a2 != 0)
	{
		return 0;
	}
	uVar1 = MISSILE_GetTargetX(pUnit);
	pMissile = sub_6FB26A60(uVar1, 3);
	if (pMissile != nullptr)
	{
		puVar3 = &uStack_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		uStack_5c = 0xa021;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uStack_4c = 0x160;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		iStack_10 = MISSILE_GetCurrentFrame(pMissile);
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_48 = 0;
		}
		else
		{
			iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar1 = pMissile->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iStack_40 = pMissile->pDynamicPath->dwClientCoordY;
		}
		else if (pMissile->pDynamicPath == nullptr)
		{
			iStack_40 = 0;
		}
		else
		{
			iStack_40 = PATH_GetXPosition(pMissile->pDynamicPath);
		}
		uVar1 = pMissile->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DStack_3c = (*(int32_t*)&pMissile->pDynamicPath->tTargetCoord);
		}
		else if (pMissile->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_3c + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_3c + 2)) = 0;
		}
		else
		{
			DStack_3c = (int32_t)PATH_GetYPosition(pMissile->pDynamicPath);
		}
		pMissile_00 = sub_6FB3E070(&uStack_5c);
		if (pMissile_00 != nullptr)
		{
			MISSILE_SetTargetX(pMissile_00, pMissile->dwUnitId);
		}
	}
	return 1;
}

//D2Client.0x6FB3AE40
void __fastcall sub_6FB3AE40(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	int iVar2;
	uint32_t uVar3;
	D2UnitStrc* pMissile;
	int iVar4;
	int iVar5;
	int32_t nY;
	int32_t DVar6;
	int32_t DVar7;
	int32_t DVar8;
	int32_t nY_00;

	iVar2 = MISSILE_GetTargetY(pUnit);
	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath != nullptr)
	{
		uVar3 = MISSILE_GetTargetX(pUnit);
		pMissile = sub_6FB26A60(uVar3, 3);
		if (pMissile != nullptr)
		{
			iVar4 = MISSILE_GetTargetX(pMissile);
			iVar5 = UNITS_GetDistanceToOtherUnit(pUnit, pMissile);
			DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar1;
			uVar3 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % 5);
			if (uVar3 < 2)
			{
				uVar3 = 1;
			}
			if ((iVar2 == iVar4) || (iVar4 < 2))
			{
				if ((iVar5 < (int)uVar3) && (iVar2 == 0))
				{
					MISSILE_SetTargetY(pUnit, 1);
					sub_6FB60130((int)pUnit);
					sub_6FB5FCB0((int)pUnit, 0, 0, 1, 1);
					sub_6FB3D880(pUnit);
					return;
				}
				if (iVar2 == 1)
				{
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iVar2 = pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						iVar2 = 0;
					}
					else
					{
						iVar2 = PATH_GetXPosition(pUnit->pDynamicPath);
					}
					uVar3 = pMissile->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iVar4 = pMissile->pDynamicPath->dwClientCoordY;
					}
					else if (pMissile->pDynamicPath == nullptr)
					{
						iVar4 = 0;
					}
					else
					{
						iVar4 = PATH_GetXPosition(pMissile->pDynamicPath);
					}
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
					}
					else
					{
						DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
					}
					uVar3 = pMissile->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						DVar7 = (*(int32_t*)&pMissile->pDynamicPath->tTargetCoord);
					}
					else if (pMissile->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
					}
					else
					{
						DVar7 = (int32_t)PATH_GetYPosition(pMissile->pDynamicPath);
					}
					if ((iVar2 - iVar4 == 0) && ((int)DVar6 - (int)DVar7 == 0))
						goto LAB_6fb3b25d;
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
					}
					else
					{
						DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
					}
					uVar3 = pUnit->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iVar5 = pUnit->pDynamicPath->dwClientCoordY;
					}
					else if (pUnit->pDynamicPath == nullptr)
					{
						iVar5 = 0;
					}
					else
					{
						iVar5 = PATH_GetXPosition(pUnit->pDynamicPath);
					}
					D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar5 - ((int)DVar6 - (int)DVar7), (int)DVar8 + (iVar2 - iVar4));
					iVar4 = 0x179e;
					iVar2 = 0xa00;
				}
				else
				{
					if (iVar2 != 3)
						goto LAB_6fb3b25d;
					uVar3 = pMissile->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						nY_00 = (*(int32_t*)&pMissile->pDynamicPath->tTargetCoord);
					}
					else if (pMissile->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&nY_00 + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&nY_00 + 2)) = 0;
					}
					else
					{
						nY_00 = (int32_t)PATH_GetYPosition(pMissile->pDynamicPath);
					}
					iVar2 = sub_6FAB6A60((int*)pMissile);
					D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar2, (int)nY_00);
					iVar4 = 0x17a7;
					iVar2 = 0x200;
				}
				PATH_SetVelocity(pDynamicPath, iVar2, __FILE__, iVar4);
				D2Common_10142(pDynamicPath, pUnit, 0);
			}
			else
			{
				MISSILE_SetTargetY(pUnit, iVar4);
				if (iVar4 == 2)
				{
					PATH_SetVelocity(pDynamicPath, 0, __FILE__, __LINE__);
					sub_6FB60130((int)pUnit);
					sub_6FB5FCB0((int)pUnit, 0, 0, 6, 1);
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					sub_6FB5FD50((int)pUnit, 0, 0, (int)(((uint64_t)DVar1 & 0xffffffff) % 0x28) + 0xaa, 0);
					sub_6FB60180((int)pUnit, 1);
					uVar3 = pMissile->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						nY = (*(int32_t*)&pMissile->pDynamicPath->tTargetCoord);
					}
					else if (pMissile->pDynamicPath == nullptr)
					{
						(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
						(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
					}
					else
					{
						nY = (int32_t)PATH_GetYPosition(pMissile->pDynamicPath);
					}
					uVar3 = pMissile->dwUnitType;
					if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
					{
						iVar2 = pMissile->pDynamicPath->dwClientCoordY;
					}
					else if (pMissile->pDynamicPath == nullptr)
					{
						iVar2 = 0;
					}
					else
					{
						iVar2 = PATH_GetXPosition(pMissile->pDynamicPath);
					}
					D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar2, (int)nY);
					PATH_SetVelocity(pDynamicPath, 0x300, __FILE__, __LINE__);
					D2Common_10142(pDynamicPath, pUnit, 0);
					sub_6FB3D880(pUnit);
					return;
				}
				if (iVar4 == 3)
				{
					sub_6FB60130((int)pUnit);
					sub_6FB5FCB0((int)pUnit, 0, 0, -6, 1);
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					sub_6FB5FD50((int)pUnit, 0, 0, (int)(((uint64_t)DVar1 & 0xffffffff) % 0x28), 0);
					sub_6FB60180((int)pUnit, 0);
					D2Common_10142(pDynamicPath, pUnit, 0);
					sub_6FB3D880(pUnit);
					return;
				}
				if (iVar4 == 4)
				{
					sub_6FB60130((int)pUnit);
					sub_6FB5FCB0((int)pUnit, 0, 0, 0x14, 1);
					sub_6FB5FD50((int)pUnit, 0, 0, 400, 0);
					sub_6FB60180((int)pUnit, 1);
					D2Common_10142(pDynamicPath, pUnit, 0);
					sub_6FB3D880(pUnit);
					return;
				}
			}
		LAB_6fb3b25d:
			sub_6FB3D880(pUnit);
			return;
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3B280
void __fastcall sub_6FB3B280(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	uVar2 = MISSILE_GetCurrentFrame(pUnit);
	uVar2 = uVar2 & 0x80000003;
	if ((int)uVar2 < 0)
	{
		uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
	}
	if (uVar2 == 0)
	{
		puVar4 = &uStack_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		uStack_5c = 0x2521;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uStack_4c = 0x162;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			iStack_48 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iStack_48 = 0;
		}
		else
		{
			iStack_48 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			DStack_44 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_44 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_44 + 2)) = 0;
		}
		else
		{
			DStack_44 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		iStack_40 = iStack_48 - (int)(((uint64_t)DVar1 & 0xffffffff) % 0xc);
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		iStack_3c = (int)(((uint64_t)DVar1 & 0xffffffff) % 0xd) + -6 + (int)DStack_44;
		sub_6FB3E070(&uStack_5c);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3B3B0
uint32_t __fastcall sub_6FB3B3B0(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint8_t nDirection;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
	(*(uint64_t*)&pUnit->pSeed) = DVar1;
	if (((uint64_t)DVar1 & 1) == 0)
	{
		if (pUnit == nullptr)
		{
			iVar6 = -1;
		}
		else
		{
			iVar6 = pUnit->dwClassId;
		}
		DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DVar1 >> 0x20));
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		uVar2 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		if ((pUnit != nullptr) &&
		    (((pDStack_58 = pUnit, pUnit->dwUnitType == 0 || (pUnit->dwUnitType == 1)) ||
		        (pDStack_58 = sub_6FB26AD0((int)pUnit), pDStack_58 != nullptr))))
		{
			puVar7 = &uStack_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 1;
			}
			uStack_5c = 0x20;
			uStack_40 = 0;
			uStack_3c = 0;
			pDStack_54 = pUnit;
			iStack_4c = ((*(uint32_t*)((uint8_t*)&DVar1 + 0)) & 1) + 1 + iVar6;
			iStack_30 = iVar3;
			uStack_2c = uVar2;
			pDVar4 = sub_6FB3E070(&uStack_5c);
			if (pDVar4 != nullptr)
			{
				pDynamicPath = pDVar4->pDynamicPath;
				nDirection = PATH_GetDirection(pUnit->pDynamicPath);
				PATH_SetDirection(pDynamicPath, nDirection);
				D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
			}
		}
	}
	return 1;
}

//D2Client.0x6FB3B4B0
void __fastcall sub_6FB3B4B0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	int iVar4;
	int* piVar5;
	int32_t DVar6;
	D2UnitStrc* pMissile;
	int iVar7;
	int iVar8;
	uint32_t* puVar9;
	int iStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	iVar4 = MISSILE_GetCurrentFrame(pUnit);
	if (iVar4 == 0x145)
	{
		sub_6FAB7E70(0x14, 0, 6000, 0);
	}
	(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
	(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
	iVar8 = 0;
	piVar5 = (int*)(&dword_6FB70B2C);
	do
	{
		if (*piVar5 < iVar4)
			break;
		piVar5 = piVar5 + 3;
		iVar8 = iVar8 + 1;
	} while ((int)piVar5 < (int)&tbl_6FB70B5C);
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iStack_68 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_68 = 0;
	}
	else
	{
		iStack_68 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath != nullptr)
	{
		DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	if (iVar4 % *(int*)(dword_6FB70B30 + iVar8 * 0xc) == 0)
	{
		puVar9 = &uStack_5c;
		for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		uStack_5c = 0x2001;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uStack_4c = 0x2a;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uVar3 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		        (uint64_t)(pUnit->pSeed).nHighSeed;
		(pUnit->pSeed).nLowSeed = (uint32_t)uVar3;
		DVar2 = (uint64_t)((uVar3 & 0xffffffff) * 0x6ac690c5 + (uVar3 >> 0x20));
		(*(uint64_t*)&pUnit->pSeed) = DVar2;
		iStack_48 = iStack_68 + -0x14 + (int)((uVar3 & 0xffffffff) % 0x28);
		iStack_44 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x28) + -0x14 + (int)DVar6;
		sub_6FB3E070(&uStack_5c);
	}
	if (iVar4 % *(int*)(byte_6FB70B34 + iVar8 * 0xc) == 0)
	{
		puVar9 = &uStack_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		uStack_5c = 0x2001;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		uStack_4c = 0x16c;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uVar3 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		        (uint64_t)(pUnit->pSeed).nHighSeed;
		(pUnit->pSeed).nLowSeed = (uint32_t)uVar3;
		DVar2 = (uint64_t)((uVar3 & 0xffffffff) * 0x6ac690c5 + (uVar3 >> 0x20));
		(*(uint64_t*)&pUnit->pSeed) = DVar2;
		iStack_48 = iStack_68 + -0x14 + (int)((uVar3 & 0xffffffff) % 0x28);
		iStack_44 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x28) + -0x14 + (int)DVar6;
		pMissile = sub_6FB3E070(&uStack_5c);
		if (pMissile != nullptr)
		{
			sub_6FB5FC80((int)pMissile, 0, 0, 0x96);
			sub_6FB5FCB0((int)pMissile, 0, 0, -10, 1);
			MISSILE_SetTotalFrames(pMissile, 0xf);
			MISSILE_SetCurrentFrame(pMissile, 0xf);
			MISSILE_SetAnimSpeed(pMissile, 0x80);
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3B720
uint32_t __fastcall sub_6FB3B720(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	uint32_t uStack_40;
	uint32_t uStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (a2 != 0)
	{
		return 0;
	}
	uVar1 = MISSILE_GetLevel(pUnit);
	iVar2 = MISSILE_GetSkill(pUnit);
	sub_6FABDB00(pUnit, 0x16d, 3, 6, iVar2, uVar1);
	uVar1 = MISSILE_GetLevel(pUnit);
	iVar2 = MISSILE_GetSkill(pUnit);
	if (pUnit != nullptr)
	{
		pDStack_58 = pUnit;
		if (((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1)) &&
		    (pDStack_58 = sub_6FB26AD0((int)pUnit), pDStack_58 == nullptr))
		{
			return 1;
		}
		puVar4 = &uStack_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		uStack_5c = 0x20;
		uStack_40 = 0;
		uStack_3c = 0;
		uStack_4c = 0x16e;
		pDStack_54 = pUnit;
		iStack_30 = iVar2;
		uStack_2c = uVar1;
		sub_6FB3E070(&uStack_5c);
	}
	return 1;
}

//D2Client.0x6FB3B7D0
void __fastcall sub_6FB3B7D0(D2UnitStrc* pUnit)
{
	uint64_t DVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;

	pDVar2 = sub_6FB26AD0((int)pUnit);
	iVar3 = MISSILE_GetTargetX(pUnit);
	if (pDVar2 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	if (iVar3 == 0)
	{
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		if (((uint64_t)DVar1 & 1) == 0)
		{
			uVar4 = 0x1a6;
		}
		else
		{
			uVar4 = 0x1a0;
		}
		sub_6FB3B8C0(pDVar2, pUnit, uVar4);
		iVar3 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar3 < 0x96)
		{
			MISSILE_SetTargetX(pUnit, 0x13);
			sub_6FB3D880(pUnit);
			return;
		}
		if (iVar3 < 200)
		{
			MISSILE_SetTargetX(pUnit, 0xe);
			sub_6FB3D880(pUnit);
			return;
		}
		if (iVar3 < 0xe1)
		{
			MISSILE_SetTargetX(pUnit, 9);
			sub_6FB3D880(pUnit);
			return;
		}
		iVar3 = ((0x176 < iVar3) - 1 & 0xffffffec) + 0x19;
	}
	MISSILE_SetTargetX(pUnit, iVar3 + -1);
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3B8C0
void __fastcall sub_6FB3B8C0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int32_t DVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	int* piVar6;
	int local_74;
	int local_70;
	int iStack_6c;
	int iStack_68;
	int iStack_64;
	int aiStack_60[2];
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	local_74 = 0;
	local_70 = 0;
	D2Common_11066(pUnit, &local_74, &local_70);
	D2_ASSERT(!((local_74 == 0) && (local_70 == 0)));
	piVar6 = aiStack_60;
	for (iVar5 = 0x17; piVar6 = piVar6 + 1, iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*piVar6 = 0;
	}
	aiStack_60[1] = 1;
	iStack_4c = a3;
	pDStack_58 = pUnit;
	iStack_30 = MISSILE_GetSkill(pUnit2);
	uStack_2c = MISSILE_GetLevel(pUnit2);
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iStack_48 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		iStack_48 = 0;
	}
	else
	{
		iStack_48 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	DVar2 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	(*(uint64_t*)&pUnit2->pSeed) = DVar2;
	iStack_48 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x14) + -10 + iStack_48;
	uVar1 = pUnit2->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar3 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
	}
	else
	{
		DVar3 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	DVar2 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	(*(uint64_t*)&pUnit2->pSeed) = DVar2;
	iStack_44 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x14) + -10 + (int)DVar3;
	pDVar4 = sub_6FB3E070((uint32_t*)(aiStack_60 + 1));
	if (pDVar4 != nullptr)
	{
		if ((a3 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= a3))
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + a3 * 0x1a4;
		}
		D2_ASSERT(*(short*)(iVar5 + 0x96) == 0x19);
		aiStack_60[0] = local_74;
		iStack_68 = local_74 * -0x19;
		iStack_64 = local_70;
		iStack_6c = local_70 * -0x19;
		DUNGEON_GameSubtileToClientCoords(&iStack_68, &iStack_6c);
		DUNGEON_GameSubtileToClientCoords(aiStack_60, &iStack_64);
		sub_6FB5FC80((int)pDVar4, iStack_68, iStack_6c, 400);
		sub_6FB5FCB0((int)pDVar4, aiStack_60[0], iStack_64, -0x10, 1);
		sub_6FB5FE00((int*)pDVar4);
	}
}

//D2Client.0x6FB3BAF0
void __fastcall sub_6FB3BAF0(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pMissile;
	int iVar5;
	int iVar6;
	uint32_t* puVar7;
	int32_t DStack_64;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar2 = sub_6FB26AD0((int)pUnit);
	iVar3 = MISSILE_GetRemainingFrames(pUnit);
	if (pDVar2 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3BDA0(pDVar2, pUnit);
	sub_6FB3BDA0(pDVar2, pUnit);
	if ((0x3c < iVar3) && (iVar3 % 0x14 == 0))
	{
		puVar7 = &uStack_5c;
		for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		pDVar1 = &pUnit->pSeed;
		uStack_5c = 2;
		pDStack_58 = pDVar2;
		pDStack_54 = pUnit;
		uVar4 = sub_6FAA88D0(&pDVar1->nLowSeed);
		iStack_40 = 0x14 - uVar4 % 0x28;
		uVar4 = sub_6FAA88F0((uint64_t*)pDVar1, 0x28);
		uStack_4c = 0x11d;
		iStack_3c = 0x14 - uVar4;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		if ((iStack_40 == 0) && (iStack_3c == 0))
		{
			uVar4 = sub_6FAA88F0((uint64_t*)pDVar1, 0x13);
			iStack_40 = uVar4 + 1;
		}
		pMissile = sub_6FB3E070(&uStack_5c);
		if (pMissile != nullptr)
		{
			MISSILE_SetTargetX(pMissile, iStack_40);
			MISSILE_SetTargetY(pMissile, iStack_3c);
			sub_6FB5FC80((int)pMissile, 0, 0, -10);
		}
	}
	if (iVar3 == 0x19)
	{
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DStack_64 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
		}
		else
		{
			DStack_64 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar4 = MISSILE_GetLevel(pUnit);
		iVar5 = MISSILE_GetSkill(pUnit);
		puVar7 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		iStack_48 = iVar3 + 2;
		iStack_44 = (int)DStack_64 + 2;
		uStack_5c = 1;
		uStack_4c = 0x26a;
		pDStack_58 = pDVar2;
		iStack_30 = iVar5;
		uStack_2c = uVar4;
		sub_6FB3E070(&uStack_5c);
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DStack_64 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_64 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_64 + 2)) = 0;
		}
		else
		{
			DStack_64 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar4 = MISSILE_GetLevel(pUnit);
		iVar5 = MISSILE_GetSkill(pUnit);
		puVar7 = &uStack_5c;
		for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar7 = 0;
			puVar7 = puVar7 + 1;
		}
		iStack_48 = iVar3 + 2;
		iStack_44 = (int)DStack_64 + 2;
		uStack_5c = 1;
		uStack_4c = 0x269;
		pDStack_58 = pDVar2;
		iStack_30 = iVar5;
		uStack_2c = uVar4;
		sub_6FB3E070(&uStack_5c);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3BDA0
void __fastcall sub_6FB3BDA0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	D2SeedStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	uint64_t DVar5;
	uint64_t DVar6;
	uint32_t uVar7;
	int32_t DVar8;
	D2UnitStrc* pMissile;
	int iVar9;
	uint32_t uVar10;
	int iVar11;
	int* piVar12;
	int local_7c[9];
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar1 = &pUnit2->pSeed;
	local_7c[0] = 1;
	local_7c[2] = 0xffffffff;
	local_7c[5] = 1;
	local_7c[7] = 0xffffffff;
	iVar11 = 0;
	DVar5 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	*(uint64_t*)pDVar1 = DVar5;
	local_7c[1] = 0;
	local_7c[3] = 0;
	local_7c[4] = 0;
	local_7c[6] = 0;
	uVar7 = sub_6FAA88D0(&pDVar1->nLowSeed);
	uVar2 = pUnit2->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		iVar11 = pUnit2->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit2->pDynamicPath != nullptr)
	{
		iVar11 = PATH_GetXPosition(pUnit2->pDynamicPath);
	}
	uVar2 = pUnit2->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		DVar8 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
	}
	else if (pUnit2->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
	}
	else
	{
		DVar8 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
	}
	iVar3 = local_7c[(uVar7 & 3) + 4];
	iVar4 = local_7c[uVar7 & 3];
	DVar6 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	*(uint64_t*)pDVar1 = DVar6;
	switch ((int)(((uint64_t)DVar6 & 0xffffffff) % 0x1e))
	{
	case 0:
		uVar10 = 0x260;
		break;
	case 1:
		uVar10 = 0x261;
		break;
	case 2:
		uVar10 = 0x262;
		break;
	case 3:
		uVar10 = 0x263;
		break;
	default:
		uVar10 = 0x25f;
	}
	piVar12 = local_7c + 8;
	for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
	{
		*piVar12 = 0;
		piVar12 = piVar12 + 1;
	}
	local_7c[8] = 3;
	pDStack_58 = pUnit;
	uStack_4c = uVar10;
	iStack_48 = iVar4 + iVar11;
	iStack_44 = iVar3 + (int)DVar8;
	iStack_30 = MISSILE_GetSkill(pUnit2);
	uStack_2c = MISSILE_GetLevel(pUnit2);
	iStack_3c = -((iVar4 + iVar11) - iVar11);
	iStack_40 = (iVar3 + (int)DVar8) - (int)DVar8;
	pMissile = sub_6FB3E070((uint32_t*)(local_7c + 8));
	if (pMissile != nullptr)
	{
		sub_6FB5FC80((int)pMissile, 0, 0, (int)(((uint64_t)DVar5 & 0xffffffff) % 0x7d));
		uVar2 = pUnit2->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			iVar11 = pUnit2->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit2->pDynamicPath == nullptr)
		{
			iVar11 = 0;
		}
		else
		{
			iVar11 = PATH_GetXPosition(pUnit2->pDynamicPath);
		}
		MISSILE_SetTargetX(pMissile, iVar11);
		uVar2 = pUnit2->dwUnitType;
		if ((uVar2 != 2) && (((int)uVar2 < 4 || (5 < (int)uVar2))))
		{
			if (pUnit2->pDynamicPath == nullptr)
			{
				MISSILE_SetTargetY(pMissile, 0);
				return;
			}
			iVar11 = PATH_GetYPosition(pUnit2->pDynamicPath);
			MISSILE_SetTargetY(pMissile, iVar11);
			return;
		}
		MISSILE_SetTargetY(pMissile, (int)(*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord));
	}
}

//D2Client.0x6FB3BFE0
void __fastcall sub_6FB3BFE0(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	D2DynamicPathStrc* pDynamicPath;
	int iVar2;
	int32_t DVar3;
	int iVar4;
	int iVar5;

	uVar1 = pUnit->dwUnitType;
	pDynamicPath = pUnit->pDynamicPath;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		iVar2 = pDynamicPath->dwClientCoordY;
	}
	else if (pDynamicPath == nullptr)
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = PATH_GetXPosition(pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DVar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
	}
	else
	{
		DVar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	iVar4 = MISSILE_GetTargetX(pUnit);
	iVar5 = MISSILE_GetTargetY(pUnit);
	D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar2 + ((int)DVar3 - iVar5), (int)DVar3 - (iVar2 - iVar4));
	D2Common_10142(pDynamicPath, pUnit, 0);
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3C080
void __fastcall sub_6FB3C080(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int* piVar4;
	uint32_t uVar5;
	D2UnitStrc* pMissile;
	int32_t DVar6;
	uint32_t uVar7;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar8;
	D2UnitStrc** ppDVar9;
	int iVar10;
	uint32_t* puVar11;
	int32_t DStack_60;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar2 = sub_6FB26AD0((int)pUnit);
	if (pDVar2 == nullptr)
	{
		sub_6FB3D880(pUnit);
		return;
	}
	iVar3 = MISSILE_GetCurrentFrame(pUnit);
	iVar10 = 0;
	piVar4 = (int*)(&dword_6FB70B68);
	do
	{
		if (*piVar4 < iVar3)
			break;
		piVar4 = piVar4 + 3;
		iVar10 = iVar10 + 1;
	} while ((int)piVar4 < (int)&tbl_6FB70B98);
	if ((iVar3 % *(int*)(dword_6FB70B6C + iVar10 * 0xc) == 0) &&
	    (*(int*)(dword_6FB70B70 + iVar10 * 0xc) != 0))
	{
		pDVar1 = &pUnit->pSeed;
		sub_6FAA88D0(&pDVar1->nLowSeed);
		puVar11 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		uStack_5c = 2;
		pDStack_58 = pDVar2;
		pDStack_54 = pUnit;
		uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
		iStack_40 = uVar5 % 0x28 - 0x14;
		uVar5 = sub_6FAA88D0(&pDVar1->nLowSeed);
		uStack_4c = 0x272;
		iStack_3c = uVar5 % 0x28 - 0x14;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		pMissile = sub_6FB3E070(&uStack_5c);
		if (pMissile != nullptr)
		{
			if (pUnit == nullptr)
			{
				uVar5 = 0xffffffff;
			}
			else
			{
				uVar5 = pUnit->dwUnitId;
			}
			MISSILE_SetTargetX(pMissile, uVar5);
		}
	}
	if (iVar3 < 0xd2)
	{
		iVar10 = 2;
	}
	else
	{
		iVar10 = 1;
	}
	MISSILE_SetTargetX(pUnit, iVar10);
	switch (iVar3)
	{
	case 0x145:
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
		}
		else
		{
			DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar5 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		uVar7 = sub_6FAB6A60((int*)pUnit);
		sub_6FB3EAF0((int)pDVar2, 0x27a, uVar7, (D2UnitStrc**)DVar6, iVar3, uVar5);
		break;
	case 0x177:
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_60 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_60 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_60 + 2)) = 0;
		}
		else
		{
			DStack_60 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = MISSILE_GetLevel(pUnit);
		iStack_30 = MISSILE_GetSkill(pUnit);
		puVar11 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		DStack_44 = DStack_60;
		uStack_5c = 1;
		uStack_4c = 0x279;
		pDStack_58 = pDVar2;
		iStack_48 = iVar3;
		uStack_2c = uVar5;
		sub_6FB3E070(&uStack_5c);
		break;
	case 0x1a9:
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_60 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_60 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_60 + 2)) = 0;
		}
		else
		{
			DStack_60 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = MISSILE_GetLevel(pUnit);
		iStack_30 = MISSILE_GetSkill(pUnit);
		puVar11 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		DStack_44 = DStack_60;
		uStack_5c = 1;
		uStack_4c = 0x278;
		pDStack_58 = pDVar2;
		iStack_48 = iVar3;
		uStack_2c = uVar5;
		sub_6FB3E070(&uStack_5c);
		break;
	case 0x1c2:
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			DStack_60 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DStack_60 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DStack_60 + 2)) = 0;
		}
		else
		{
			DStack_60 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar5 = pUnit->dwUnitType;
		if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar5 = MISSILE_GetLevel(pUnit);
		iStack_30 = MISSILE_GetSkill(pUnit);
		puVar11 = &uStack_5c;
		for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		iStack_48 = iVar3 + 1;
		DStack_44 = (int32_t)((int)DStack_60 + 1);
		uStack_5c = 1;
		uStack_4c = 0x277;
		pDStack_58 = pDVar2;
		uStack_2c = uVar5;
		sub_6FB3E070(&uStack_5c);
	}
	iVar3 = MISSILE_GetTargetY(pUnit);
	if (iVar3 != 0)
	{
		iVar10 = 0x209;
		iVar3 = 1;
		pRoom = UNITS_GetRoom(pUnit);
		pDVar2 = UNITFINDS_FindUnitInNeighboredRooms(pRoom, iVar3, iVar10);
		if (pDVar2 != nullptr)
		{
			uVar5 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 10);
			uVar8 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 10);
			iVar3 = sub_6FAB6A60((int*)pDVar2);
			ppDVar9 = sub_6FAB6A90((int*)pDVar2);
			sub_6FB3C540(pUnit, iVar3 + (uVar5 - 5), (int*)((int)ppDVar9 + (uVar8 - 5)));
		}
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3C540
int32_t __fastcall sub_6FB3C540(D2UnitStrc* pUnit, int a2, int* a3)
{
	uint64_t DVar1;
	uint16_t uVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pMissile;
	int iVar3;
	uint32_t* puVar4;
	int* nY;
	int nUnitSize;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	int iStack_4c;
	int iStack_48;
	int* piStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	uVar2 = 1;
	nUnitSize = 3;
	iVar3 = a2;
	nY = a3;
	pRoom = UNITS_GetRoom(pUnit);
	uVar2 = COLLISION_CheckMaskWithSize(pRoom, iVar3, (int)nY, nUnitSize, uVar2);
	if (uVar2 == 0)
	{
		puVar4 = &uStack_5c;
		for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		uStack_5c = 0x2001;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar1;
		iStack_4c = (int)(((uint64_t)DVar1 & 0xffffffff) % 3) + 0x27b;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		piStack_44 = a3;
		iStack_48 = a2;
		pMissile = sub_6FB3E070(&uStack_5c);
		if (pMissile != nullptr)
		{
			sub_6FB5FC80((int)pMissile, 0, 0, 0xfa);
			sub_6FB5FCB0((int)pMissile, 0, 0, -10, 1);
			MISSILE_SetTotalFrames(pMissile, 0x19);
			MISSILE_SetCurrentFrame(pMissile, 0x19);
			MISSILE_SetAnimSpeed(pMissile, 0x80);
		}
	}
	return 0;
}

//D2Client.0x6FB3C630
void __fastcall sub_6FB3C630(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar2;
	int iVar3;
	uint32_t uVar4;
	D2UnitStrc* pMissile;
	int iVar5;
	int32_t DVar6;
	int32_t DVar7;
	int32_t DVar8;
	int iVar9;

	pDVar1 = &pUnit->pSeed;
	iVar3 = MISSILE_GetTargetY(pUnit);
	pDynamicPath = pUnit->pDynamicPath;
	if (pDynamicPath == nullptr)
	{
	LAB_6fb3c891:
		sub_6FB3D880(pUnit);
		return;
	}
	uVar4 = MISSILE_GetTargetX(pUnit);
	pMissile = sub_6FB26A60(uVar4, 3);
	if (pMissile == nullptr)
		goto LAB_6fb3c891;
	iVar5 = MISSILE_GetTargetX(pMissile);
	if (((iVar3 == iVar5) || (iVar5 < 2)) ||
	    (DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed),
	        *(uint64_t*)pDVar1 = DVar2, (int)(((uint64_t)DVar2 & 0xffffffff) % 0x19) != 0))
	{
		if (iVar3 == 0)
		{
			DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
			*(uint64_t*)pDVar1 = DVar2;
			if ((int)(((uint64_t)DVar2 & 0xffffffff) % 10) == 0)
			{
				MISSILE_SetTargetY(pUnit, 1);
				sub_6FB60130((int)pUnit);
				PATH_SetVelocity(pDynamicPath, 0xf00, __FILE__, __LINE__);
				uVar4 = sub_6FAA88D0(&pDVar1->nLowSeed);
				if ((uVar4 & 1) != 0)
				{
					sub_6FB5FCB0((int)pUnit, 0, 0, 1, 1);
					sub_6FB3D880(pUnit);
					return;
				}
			}
			goto LAB_6fb3c883;
		}
		if (iVar3 != 1)
			goto LAB_6fb3c883;
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar4 = pMissile->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			iVar5 = pMissile->pDynamicPath->dwClientCoordY;
		}
		else if (pMissile->pDynamicPath == nullptr)
		{
			iVar5 = 0;
		}
		else
		{
			iVar5 = PATH_GetXPosition(pMissile->pDynamicPath);
		}
		iVar3 = iVar3 - iVar5;
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar6 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar6 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar6 + 2)) = 0;
		}
		else
		{
			DVar6 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar4 = pMissile->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar7 = (*(int32_t*)&pMissile->pDynamicPath->tTargetCoord);
		}
		else if (pMissile->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
		}
		else
		{
			DVar7 = (int32_t)PATH_GetYPosition(pMissile->pDynamicPath);
		}
		iVar5 = (int)DVar6 - (int)DVar7;
		if ((pUnit->dwUnitId & 2) != 0)
		{
			iVar3 = -iVar3;
			iVar5 = -iVar5;
		}
		if ((iVar3 == 0) && (iVar5 == 0))
			goto LAB_6fb3c883;
		uVar4 = pUnit->dwUnitType;
		if ((uVar4 == 2) || ((3 < (int)uVar4 && ((int)uVar4 < 6))))
		{
			DVar8 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
		}
		else
		{
			DVar8 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iVar3 = (int)DVar8 + iVar3;
		iVar9 = sub_6FAB6A60((int*)pUnit);
		iVar9 = iVar9 - iVar5;
	}
	else
	{
		MISSILE_SetTargetY(pUnit, iVar5);
		if (iVar5 != 2)
			goto LAB_6fb3c883;
		PATH_SetVelocity(pDynamicPath, 0xf00, __FILE__, __LINE__);
		iVar3 = 0x170c;
		iVar9 = 0x3b1f;
	}
	D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar9, iVar3);
	D2Common_10142(pDynamicPath, pUnit, 0);
LAB_6fb3c883:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3C8A0
uint32_t __fastcall sub_6FB3C8A0(D2UnitStrc* pUnit2)
{
	uint32_t uVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	bool bVar4;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;

	pUnit = sub_6FB26AD0((int)pUnit2);
	bVar4 = false;
	if (pUnit == nullptr)
	{
	LAB_6fb3ca38:
		uVar6 = sub_6FB3DBB0(pUnit2);
		return uVar6;
	}
	pRoom = UNITS_GetRoom(pUnit);
	iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom);
	if ((0x82 < iVar5) && (iVar5 < 0x85))
	{
		bVar4 = true;
	}
	if (!bVar4)
		goto LAB_6fb3ca38;
	D2Common_10235_PATH_UpdateRiderPath(pUnit2, pUnit);
	UNITS_UpdateFrame(pUnit2);
	iVar5 = MISSILE_GetTargetX(pUnit2);
	if (iVar5 != 0)
	{
		DVar2 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit2->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit2->pSeed) = DVar2;
		if (((uint64_t)DVar2 & 0x3f) != 0)
			goto LAB_6fb3c938;
	}
	sub_6FAB7E70(6, 2000, 3000, 2000);
	MISSILE_SetTargetX(pUnit2, 1);
LAB_6fb3c938:
	DVar2 = (uint64_t)((uint64_t)(pUnit2->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit2->pSeed).nHighSeed);
	uVar6 = (uint32_t)(((uint64_t)DVar2 & 0xffffffff) / 10);
	(*(uint64_t*)&pUnit2->pSeed) = DVar2;
	if ((int)(((uint64_t)DVar2 & 0xffffffff) % 10) == 0)
	{
		uVar3 = ((uint64_t)DVar2 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DVar2 >> 0x20);
		(pUnit2->pSeed).nLowSeed = (uint32_t)uVar3;
		DVar2 = (uint64_t)((uVar3 & 0xffffffff) * 0x6ac690c5 + (uVar3 >> 0x20));
		(*(uint64_t*)&pUnit2->pSeed) = DVar2;
		iVar5 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x3c);
		uVar1 = pUnit2->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar7 = pUnit2->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit2->pDynamicPath == nullptr)
		{
			iVar7 = 0;
		}
		else
		{
			iVar7 = PATH_GetXPosition(pUnit2->pDynamicPath);
		}
		iVar7 = iVar7 + -0x1e + (int)((uVar3 & 0xffffffff) % 0x3c);
		uVar1 = pUnit2->dwUnitType;
		if ((uVar1 != 2) && (((int)uVar1 < 4 || (5 < (int)uVar1))))
		{
			if (pUnit2->pDynamicPath != nullptr)
			{
				iVar8 = PATH_GetYPosition(pUnit2->pDynamicPath);
				uVar6 = sub_6FB3C540(pUnit2, iVar7, (int*)(iVar8 + -0x1e + iVar5));
				return uVar6;
			}
			uVar6 = sub_6FB3C540(pUnit2, iVar7, (int*)(iVar5 + -0x1e));
			return uVar6;
		}
		uVar6 = sub_6FB3C540(pUnit2, iVar7,
		    (int*)((int)(*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord) + -0x1e + iVar5));
	}
	return uVar6;
}

//D2Client.0x6FB3CA50
void __fastcall sub_6FB3CA50(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = MISSILE_GetTargetX(pUnit);
	iVar2 = MISSILE_GetTargetY(pUnit);
	iVar3 = sub_6FB5FC40((int)pUnit);
	if ((-iVar1 <= iVar3) && (iVar3 <= iVar2))
	{
		sub_6FB3D880(pUnit);
		return;
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB3CA90
uint32_t __fastcall sub_6FB3CA90(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int nY;
	int* piVar9;
	uint32_t* puVar10;
	int iStack_104;
	int32_t DStack_100;
	int local_fc;
	int local_f8[17];
	D2UnitStrc* pDStack_b4;
	D2UnitStrc* pDStack_b0;
	uint32_t uStack_a8;
	uint32_t uStack_9c;
	uint32_t uStack_98;
	int iStack_8c;
	uint32_t uStack_88;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	uint32_t uStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	local_f8[5] = 0xffffffff;
	local_f8[6] = 0xffffffff;
	local_f8[7] = 0xffffffff;
	local_f8[0xb] = 0xffffffff;
	local_f8[0xc] = 0xffffffff;
	local_f8[0xd] = 0xffffffff;
	uVar2 = pUnit->dwUnitType;
	local_f8[0] = 0;
	local_f8[1] = 1;
	local_f8[2] = 1;
	local_f8[3] = 1;
	local_f8[4] = 0;
	local_f8[8] = 1;
	local_f8[9] = 1;
	local_f8[10] = 0;
	local_f8[0xe] = 0;
	local_f8[0xf] = 1;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		local_fc = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_fc = 0;
	}
	else
	{
		local_fc = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar2 = pUnit->dwUnitType;
	if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
	{
		DStack_100 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_100 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_100 + 2)) = 0;
	}
	else
	{
		DStack_100 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar2 = MISSILE_GetLevel(pUnit);
	iVar3 = MISSILE_GetSkill(pUnit);
	pDVar4 = pUnit;
	if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
	    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 != nullptr))
	{
		piVar9 = local_f8 + 0x10;
		for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			*piVar9 = 0;
			piVar9 = piVar9 + 1;
		}
		local_f8[0x10] = 0x20;
		uStack_9c = 0;
		uStack_98 = 0;
		uStack_a8 = 0x58;
		pDStack_b4 = pDVar4;
		pDStack_b0 = pUnit;
		iStack_8c = iVar3;
		uStack_88 = uVar2;
		sub_6FB3E070((uint32_t*)(local_f8 + 0x10));
	}
	iStack_104 = 0;
	do
	{
		iVar7 = *(int*)((int)local_f8 + iStack_104) + local_fc;
		nY = *(int*)((int)local_f8 + iStack_104 + 0x20) + (int)DStack_100;
		uVar2 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		pDVar4 = pUnit;
		if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 != nullptr))
		{
			piVar9 = local_f8 + 0x10;
			for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*piVar9 = 0;
				piVar9 = piVar9 + 1;
			}
			uStack_9c = 0;
			uStack_98 = 0;
			local_f8[0x10] = 0x20;
			uStack_a8 = 0x59;
			pDStack_b4 = pDVar4;
			pDStack_b0 = pUnit;
			iStack_8c = iVar3;
			uStack_88 = uVar2;
			pDVar4 = sub_6FB3E070((uint32_t*)(local_f8 + 0x10));
			if (pDVar4 != nullptr)
			{
				D2Common_10216(pDVar4->pDynamicPath, iVar7, nY, 0);
			}
		}
		uVar2 = MISSILE_GetLevel(pUnit);
		iVar3 = MISSILE_GetSkill(pUnit);
		pDVar4 = pUnit;
		if (((pUnit->dwUnitType == 0) || (pUnit->dwUnitType == 1)) ||
		    (pDVar4 = sub_6FB26AD0((int)pUnit), pDVar4 != nullptr))
		{
			puVar10 = &uStack_5c;
			for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			uStack_5c = 0x20;
			uStack_4c = 0x1a1;
			pDStack_58 = pDVar4;
			pDStack_54 = pUnit;
			iStack_40 = iVar7;
			iStack_3c = nY;
			iStack_30 = iVar3;
			uStack_2c = uVar2;
			pDVar4 = sub_6FB3E070(&uStack_5c);
			if (pDVar4 != nullptr)
			{
				iVar3 = MISSILE_GetTotalFrames(pDVar4);
				uVar2 = iVar3 / 2;
				if ((int)uVar2 < 1)
				{
					uVar5 = 0;
				}
				else if ((uVar2 & uVar2 - 1) == 0)
				{
					uVar5 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
					uVar5 = uVar5 & uVar2 - 1;
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar5 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar2);
				}
				MISSILE_SetTotalFrames(pDVar4, iVar3 - uVar5);
				pDynamicPath = pDVar4->pDynamicPath;
				uVar2 = PATH_GetVelocity(pDynamicPath);
				if ((int)uVar2 < 1)
				{
					uVar6 = 0;
				}
				else if ((uVar2 & uVar2 - 1) == 0)
				{
					uVar6 = sub_6FAA88D0(&(pUnit->pSeed).nLowSeed);
					uVar6 = uVar6 & uVar2 - 1;
				}
				else
				{
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					uVar6 = (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % (uint64_t)uVar2);
				}
				PATH_SetVelocity(pDynamicPath, uVar6, __FILE__, __LINE__);
				sub_6FB60080((int)pDVar4, 0x1e, iVar3 - uVar5);
			}
		}
		iStack_104 = iStack_104 + 4;
	} while (iStack_104 < 0x20);
	return 1;
}

//D2Client.0x6FB3CE10
void __fastcall sub_6FB3CE10(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	uint64_t DVar2;
	uint64_t DVar3;
	D2UnitStrc* pDVar4;
	int iVar5;
	uint32_t uVar6;
	int iVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	int iVar10;
	uint32_t* puVar11;
	int32_t DStack_74;
	int iStack_70;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int32_t DStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	pDVar4 = sub_6FB26AD0((int)pUnit);
	iVar5 = MISSILE_GetRemainingFrames(pUnit);
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		iStack_70 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		iStack_70 = 0;
	}
	else
	{
		iStack_70 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar6 = pUnit->dwUnitType;
	if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
	{
		DStack_74 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_74 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_74 + 2)) = 0;
	}
	else
	{
		DStack_74 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	if (iVar5 < 0x6e)
	{
		if (iVar5 == 0)
		{
			uVar6 = MISSILE_GetLevel(pUnit);
			iVar7 = MISSILE_GetSkill(pUnit);
			if (pDVar4 == nullptr)
			{
			LAB_6fb3cf13:
				iVar7 = 8;
			}
			else
			{
				puVar11 = &uStack_5c;
				for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1)
				{
					*puVar11 = 0;
					puVar11 = puVar11 + 1;
				}
				iStack_48 = iStack_70;
				uStack_5c = 1;
				DStack_44 = DStack_74;
				uStack_4c = 0x214;
				pDStack_58 = pDVar4;
				iStack_30 = iVar7;
				uStack_2c = uVar6;
				sub_6FB3E070(&uStack_5c);
				iVar7 = 8;
			}
		}
		else
		{
			if (iVar5 < 0x32)
				goto LAB_6fb3cf13;
			iVar7 = (uint32_t)(iVar5 < 0x50) * 4 + 1;
		}
		for (; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			uVar6 = MISSILE_GetLevel(pUnit);
			iVar9 = MISSILE_GetSkill(pUnit);
			if (pDVar4 != nullptr)
			{
				puVar11 = &uStack_5c;
				for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1)
				{
					*puVar11 = 0;
					puVar11 = puVar11 + 1;
				}
				iStack_48 = iStack_70 + 2;
				DStack_44 = (int32_t)((int)DStack_74 + 2);
				uStack_5c = 1;
				uStack_4c = 0x255;
				pDStack_58 = pDVar4;
				iStack_30 = iVar9;
				uStack_2c = uVar6;
				pDVar8 = sub_6FB3E070(&uStack_5c);
				if (pDVar8 != nullptr)
				{
					pDVar1 = &pUnit->pSeed;
					DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					*(uint64_t*)pDVar1 = DVar2;
					DVar3 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
					*(uint64_t*)pDVar1 = DVar3;
					uVar6 = sub_6FAA88D0(&pDVar1->nLowSeed);
					sub_6FB5FC80((int)pDVar8, 0x32 - (int)(((uint64_t)DVar2 & 0xffffffff) % 100),
					    0x32 - (int)(((uint64_t)DVar3 & 0xffffffff) % 100), 0);
					sub_6FB5FCB0((int)pDVar8, 0, 0, (uVar6 & 7) + 2, 1);
				}
			}
		}
	}
	if (iVar5 == 5)
	{
		sub_6FAB7E70(3, 600, 4000, 3000);
	}
	else if (199 < iVar5)
		goto LAB_6fb3d076;
	if (iVar5 % 7 == 0)
	{
		sub_6FB3D090((int)pDVar4, pUnit, iStack_70, DStack_74);
	}
LAB_6fb3d076:
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3D090
void __fastcall sub_6FB3D090(int a1, D2UnitStrc* pUnit, int a3, int a4)
{
	uint64_t DVar1;
	bool bVar2;
	uint16_t uVar3;
	D2ActiveRoomStrc* pRoom;
	int iVar4;
	int iVar5;
	uint32_t* puVar6;
	int local_6c;
	uint32_t auStack_5c[4];
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_30;
	uint32_t uStack_2c;

	bVar2 = true;
	local_6c = 0;
	if (((pUnit != nullptr) && (a1 != 0)) &&
	    (pRoom = UNITS_GetRoom(pUnit), pRoom != nullptr))
	{
		do
		{
			if (3 < local_6c)
			{
				if (bVar2)
				{
					return;
				}
				break;
			}
			DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar1;
			iVar5 = 0x11 - (int)(((uint64_t)DVar1 & 0xffffffff) % 0x22);
			DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar1;
			iVar4 = 0x11 - (int)(((uint64_t)DVar1 & 0xffffffff) % 0x22);
			if (((iVar5 < -1) || (1 < iVar5)) || (iVar4 < -1))
			{
				iVar4 = iVar4 + a4;
				uVar3 = COLLISION_CheckMask(pRoom, iVar5 + a3, iVar4, 4);
				if (uVar3 == 0)
				{
					bVar2 = false;
					a3 = iVar5 + a3;
					a4 = iVar4;
				}
			}
			local_6c = local_6c + 1;
		} while (bVar2);
		puVar6 = auStack_5c;
		for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		auStack_5c[0] = 1;
		auStack_5c[1] = a1;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uStack_4c = 0x267;
		iStack_44 = a4;
		iStack_48 = a3;
		sub_6FB3E070(auStack_5c);
		uStack_4c = 0x268;
		sub_6FB3E070(auStack_5c);
	}
}

//D2Client.0x6FB3D200
void __fastcall sub_6FB3D200(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t DVar4;
	uint64_t uVar5;
	int iVar6;
	int32_t DVar7;
	int iVar8;
	uint32_t* puVar9;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_4c;
	int iStack_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	iVar6 = MISSILE_GetRemainingFrames(pUnit);
	if (iVar6 % 3 == 0)
	{
		uVar5 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		        (uint64_t)(pUnit->pSeed).nHighSeed;
		(pUnit->pSeed).nLowSeed = (uint32_t)uVar5;
		DVar3 = (uint64_t)((uVar5 & 0xffffffff) * 0x6ac690c5 + (uVar5 >> 0x20));
		(*(uint64_t*)&pUnit->pSeed) = DVar3;
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			iVar6 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar6 = 0;
		}
		else
		{
			iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		DVar4 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar4;
		iVar6 = (((*(uint32_t*)((uint8_t*)&DVar4 + 0)) & 1) - 1) + iVar6;
		uVar2 = pUnit->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			DVar7 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
		}
		else
		{
			DVar7 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		DVar4 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
		                   (uint64_t)(pUnit->pSeed).nHighSeed);
		(*(uint64_t*)&pUnit->pSeed) = DVar4;
		iVar1 = (((*(uint32_t*)((uint8_t*)&DVar4 + 0)) & 1) - 1) + (int)DVar7;
		puVar9 = &uStack_5c;
		for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 1;
		}
		uStack_5c = 0x21;
		pDStack_58 = sub_6FB26AD0((int)pUnit);
		iStack_40 = (int)((uVar5 & 0xffffffff) % 0x14) + -10 + iVar6;
		iStack_3c = iVar1 + -10 + (int)(((uint64_t)DVar3 & 0xffffffff) % 0x14);
		iStack_48 = iVar6;
		iStack_44 = iVar1;
		iStack_30 = MISSILE_GetSkill(pUnit);
		uStack_2c = MISSILE_GetLevel(pUnit);
		uStack_4c = 0x21e;
		sub_6FB3E070(&uStack_5c);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3D380
void __fastcall sub_6FB3D380(D2UnitStrc* pUnit)
{
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar1;
	int iVar2;
	int32_t DVar3;
	int iVar4;
	int iVar5;
	bool bVar6;

	uVar1 = MISSILE_GetRemainingFrames(pUnit);
	uVar1 = uVar1 & 0x80000001;
	bVar6 = uVar1 == 0;
	if ((int)uVar1 < 0)
	{
		bVar6 = (uVar1 - 1 | 0xfffffffe) == 0xffffffff;
	}
	if (bVar6)
	{
		uVar1 = pUnit->dwUnitType;
		pDynamicPath = pUnit->pDynamicPath;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar2 = pDynamicPath->dwClientCoordY;
		}
		else if (pDynamicPath == nullptr)
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = PATH_GetXPosition(pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			DVar3 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar3 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar3 + 2)) = 0;
		}
		else
		{
			DVar3 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		iVar4 = MISSILE_GetTargetX(pUnit);
		iVar5 = MISSILE_GetTargetY(pUnit);
		D2COMMON_10170_PathSetTargetPos(pDynamicPath, iVar2 + ((int)DVar3 - iVar5), (int)DVar3 - (iVar2 - iVar4));
		D2Common_10142(pDynamicPath, pUnit, 0);
	}
	sub_6FB3D880(pUnit);
}

//D2Client.0x6FB3D440
uint32_t __fastcall sub_6FB3D440(D2UnitStrc* pUnit)
{
	D2SeedStrc* pSeed;
	int iVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	uint64_t uVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t* puVar10;
	int iStack_70;
	int32_t DStack_68;
	uint32_t uStack_5c;
	D2UnitStrc* pDStack_58;
	D2UnitStrc* pDStack_54;
	int iStack_4c;
	int iStack_40;
	int iStack_3c;
	int iStack_30;
	uint32_t uStack_2c;

	if (((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	    (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c)))
	{
		iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4;
		if ((iVar1 != 0) && (-1 < *(short*)(iVar1 + 0x2c)))
		{
			pDVar5 = sub_6FB26AD0((int)pUnit);
			if (pDVar5 != nullptr)
			{
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iVar6 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				pSeed = &pUnit->pSeed;
				SEED_InitLowSeed(pSeed, iVar6);
				iVar6 = 1;
				if (0 < *(int*)(iVar1 + 0x6c))
				{
					iVar6 = *(int*)(iVar1 + 0x6c);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iStack_70 = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					iStack_70 = 0;
				}
				else
				{
					iStack_70 = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar2 = pUnit->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DStack_68 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_68 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_68 + 2)) = 0;
				}
				else
				{
					DStack_68 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				uVar9 = iVar6 * 2;
				uVar2 = uVar9 + 1;
				if ((int)uVar2 < 1)
				{
					uVar8 = 0;
				}
				else
				{
					uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
					if ((uVar2 & uVar9) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pSeed = DVar3;
						uVar8 = uVar9 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pSeed = DVar3;
						uVar8 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
					}
				}
				if ((int)uVar2 < 1)
				{
					uVar9 = 0;
				}
				else
				{
					uVar4 = (uint64_t)(pUnit->pSeed).nHighSeed;
					if ((uVar2 & uVar9) == 0)
					{
						DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pSeed = DVar3;
						uVar9 = uVar9 & (*(uint32_t*)((uint8_t*)&DVar3 + 0));
					}
					else
					{
						DVar3 = (uint64_t)((uint64_t)pSeed->nLowSeed * 0x6ac690c5 + uVar4);
						*(uint64_t*)pSeed = DVar3;
						uVar9 = (uint32_t)(((uint64_t)DVar3 & 0xffffffff) % (uint64_t)uVar2);
					}
				}
				puVar10 = &uStack_5c;
				for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1)
				{
					*puVar10 = 0;
					puVar10 = puVar10 + 1;
				}
				uStack_5c = 0x20;
				pDStack_58 = pDVar5;
				pDStack_54 = pUnit;
				iStack_30 = MISSILE_GetSkill(pUnit);
				uStack_2c = MISSILE_GetLevel(pUnit);
				iStack_4c = (int)*(short*)(iVar1 + 0x2c);
				iStack_3c = (uVar9 - iVar6) + (int)DStack_68;
				iStack_40 = (uVar8 - iVar6) + iStack_70;
				sub_6FB3E070(&uStack_5c);
			}
		}
	}
	return 1;
}

//D2Client.0x6FB3D660
uint32_t __fastcall sub_6FB3D660(D2UnitStrc* pUnit)
{
	int iVar1;
	int iVar2;

	if ((((pUnit != nullptr) && (iVar1 = pUnit->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar1 * 0x1a4, iVar1 != 0 &&
	                                                                                       (-1 < *(short*)(iVar1 + 0x2c)))))
	{
		iVar2 = *(int*)(iVar1 + 0x6c);
		if (iVar2 < 1)
		{
			iVar2 = 1;
		}
		sub_6FB35FD0(pUnit, (int)*(short*)(iVar1 + 0x2c), iVar2, 2, 0);
	}
	return 1;
}

//D2Client.0x6FB3D6D0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FB3D6D0(D2UnitStrc* pUnit)
{
	D2SeedStrc* pDVar1;
	int iVar2;
	short sVar3;
	int iVar4;
	uint32_t uVar5;
	uint64_t DVar6;
	int iVar7;
	uint32_t uVar8;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar9;
	int iVar10;

	if ((pUnit != nullptr) && (iVar7 = pUnit->dwClassId, -1 < iVar7))
	{
		iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c);
		if (iVar7 < iVar4)
		{
			iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64);
			iVar2 = iVar10 + iVar7 * 0x1a4;
			if (iVar2 != 0)
			{
				if (*(char*)(iVar2 + 0x131) != '\0')
				{
					if ((iVar7 < 0) || (iVar4 <= iVar7))
					{
						iVar10 = 0;
					}
					else
					{
						iVar10 = iVar10 + iVar7 * 0x1a4;
					}
					if ((pUnit->nSeqCurrentFramePrecise & 0x300U) == 0)
					{
						uVar5 = pUnit->dwInteractGUID;
						if (uVar5 != 0)
						{
							iVar7 = sub_6FAA4460(uVar5);
							if ((int)(uint32_t) * (uint8_t*)(iVar10 + 0x130) <= iVar7)
							{
								pDVar1 = &pUnit->pSeed;
								uVar9 = (uint32_t) * (uint8_t*)(iVar10 + 0x131);
								if (uVar9 == 0)
								{
									uVar8 = 0;
								}
								else if ((uVar9 & uVar9 - 1) == 0)
								{
									uVar8 = sub_6FAA88D0(&pDVar1->nLowSeed);
									uVar8 = uVar8 & uVar9 - 1;
								}
								else
								{
									DVar6 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 +
									                   (uint64_t)(pUnit->pSeed).nHighSeed);
									*(uint64_t*)pDVar1 = DVar6;
									uVar8 = (uint32_t)(((uint64_t)DVar6 & 0xffffffff) % (uint64_t)uVar9);
								}
								sub_6FAA43A0(uVar5, *(uint8_t*)(iVar10 + 0x130) + uVar8);
							}
						}
					}
				}
				pRoom = UNITS_GetRoom(pUnit);
				if (pRoom == nullptr)
				{
					uVar5 = pUnit->dwUnitType;
					if ((uVar5 != 2) &&
					    ((((int)uVar5 < 4 || (5 < (int)uVar5)) &&
					        (pUnit->pDynamicPath != nullptr))))
					{
						PATH_GetYPosition(pUnit->pDynamicPath);
					}
					uVar5 = pUnit->dwUnitType;
					if (((uVar5 != 2) && (((int)uVar5 < 4 || (5 < (int)uVar5)))) &&
					    (pUnit->pDynamicPath != nullptr))
					{
						PATH_GetXPosition(pUnit->pDynamicPath);
					}
					pRoom = nullptr;
				}
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar2 + 5)) == 0)
				{
					iVar7 = DUNGEON_IsRoomInTown(pRoom);
					if (iVar7 != 0)
					{
						sub_6FB3DBB0(pUnit);
						return;
					}
				}
				sVar3 = *(short*)(iVar2 + 8);
				if ((0 < sVar3) && (sVar3 < dword_6FB913CC))
				{
					// TODO: Ghidra: Could not recover jumptable
					// TODO: Ghidra: Treating indirect jump
					(**(code**)(byte_6FB91260 + sVar3 * 4))();
					return;
				}
				return;
			}
		}
	}
	sub_6FB3DBB0(pUnit);
}

//D2Client.0x6FB3D880
void __fastcall sub_6FB3D880(D2UnitStrc* pUnit)
{
	D2PathPointStrc* pDVar1;
	uint8_t bVar2;
	int iVar3;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t uVar4;
	bool bVar5;
	bool bVar6;
	uint16_t uVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	int iVar10;
	D2UnitStrc* pDVar11;
	D2ActiveRoomStrc* pDVar12;
	D2ActiveRoomStrc* pRoom;
	D2PathPointStrc* pDStack_18;
	uint32_t uStack_14;
	int iStack_10;
	D2UnitStrc* pDStack_c;
	D2UnitStrc* pDStack_8;
	int iStack_4;

	if ((((pUnit == nullptr) || (iVar3 = pUnit->dwClassId, iVar3 < 0)) ||
	        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar3)) ||
	    (iVar3 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar3 * 0x1a4, iVar3 == 0))
	{
		return;
	}
	bVar6 = false;
	switch (gnGameType)
	{
	case 0:
	case 1:
	case 6:
	case 8:
		pDVar11 = sub_6FB26AD0((int)pUnit);
		pDVar8 = CUNIT_GetPlayer();
		if (pDVar11 == pDVar8)
		{
			bVar6 = true;
		}
	}
	do
	{
		iVar9 = MISSILE_GetActivateFrame(pUnit);
		iVar10 = MISSILE_GetCurrentFrame(pUnit);
		bVar5 = iVar9 < iVar10;
		if ((!bVar5) &&
		    (iVar9 = MISSILE_GetRemainingFrames(pUnit), (int)(uint32_t) * (uint8_t*)(iVar3 + 0x135) < iVar9))
		{
			pUnit->dwFlagEx = pUnit->dwFlagEx & 0xfffbffff;
		}
		iVar9 = sub_6FB60150((int)pUnit);
		if (iVar9 == 0)
			goto LAB_6fb3db74;
		if (!bVar5)
		{
			if (*(char*)(iVar3 + 0x137) == '\0')
			{
				iVar9 = UNITS_IsAtEndOfFrameCycle(pUnit);
				if (iVar9 != 0)
					goto LAB_6fb3d975;
			}
			else if (*(char*)(iVar3 + 0x180) != '\0')
			{
				bVar2 = *(uint8_t*)(iVar3 + 0x182);
				iVar9 = MISSILE_GetCurrentFrame(pUnit);
				if ((int)(((uint32_t) * (uint8_t*)(iVar3 + 0x178) - (uint32_t)bVar2) + 1) < iVar9)
				{
					D2COMMON_10375_UNITS_SetFrameNonRate(pUnit, (uint32_t) * (uint8_t*)(iVar3 + 0x181), (uint32_t)bVar2);
					goto LAB_6fb3d975;
				}
			}
			UNITS_UpdateFrame(pUnit);
		}
	LAB_6fb3d975:
		pDynamicPath = pUnit->pDynamicPath;
		iVar9 = PATH_GetVelocity(pDynamicPath);
		if (iVar9 != 0)
		{
			iVar9 = sub_6FAABFE0();
			D2Common_10226(pUnit, iVar9);
		}
		iVar9 = MISSILE_GetCurrentFrame(pUnit);
		MISSILE_SetCurrentFrame(pUnit, iVar9 + -1);
		iVar9 = MISSILE_GetCurrentFrame(pUnit);
		if (iVar9 < 1)
		{
			sub_6FB3DC50(pUnit, nullptr, 0);
			return;
		}
		if (bVar5)
		{
			return;
		}
		if ((*(char*)(iVar3 + 300) != '\0') &&
		    ((pDVar11 = sub_6FB26AD0((int)pUnit), pDVar11 == nullptr ||
		                                              ((pDVar12 = UNITS_GetRoom(pDVar11), pDVar12 != nullptr &&
		                                                                                      (iVar9 = DUNGEON_IsRoomInTown(pDVar12), iVar9 != 0))))))
		{
			bVar2 = *(uint8_t*)(iVar3 + 300);
			iVar9 = MISSILE_GetCurrentFrame(pUnit);
			if (((int)(uint32_t)bVar2 <= iVar9) &&
			    ((MISSILE_SetCurrentFrame(pUnit, (uint32_t)bVar2), *(char*)(iVar3 + 0x137) == '\0' &&
			                                                           (iVar9 = (uint32_t) * (uint8_t*)(iVar3 + 0x178) - (uint32_t) * (uint8_t*)(iVar3 + 300), 0 < iVar9))))
			{
				pUnit->nSeqCurrentFramePrecise = iVar9 * 0x100;
			}
		}
		uVar4 = pUnit->dwAnimMode;
		if (uVar4 == 0)
		{
			return;
		}
		uStack_14 = uVar4;
		uVar7 = D2Common_10201(pDynamicPath);
		if ((uVar7 & 5) != 0)
		{
		LAB_6fb3db74:
			sub_6FB3DC50(pUnit, nullptr, 1);
			return;
		}
		if (uVar4 == 6)
		{
			return;
		}
		pDStack_c = pUnit;
		pDStack_8 = sub_6FB26AD0((int)pUnit);
		iStack_4 = iVar3;
		if ((*(char*)(iVar3 + 0x185) != '\0') && (uVar7 != 0))
		{
			iVar9 = D2COMMON_10198_PathGetSaveStep(pDynamicPath, &pDStack_18);
			iStack_10 = iVar9;
			pDVar12 = UNITS_GetRoom(pUnit);
			iVar10 = 0;
			if (0 < iVar9)
			{
				do
				{
					pDVar1 = pDStack_18 + iVar10;
					UNITS_GetUnitSizeX(pUnit);
					pRoom = (D2ActiveRoomStrc*)(uint32_t)pDVar1->X;
					pDVar11 = D2Common_10407(pRoom, *(int*)(byte_6FB91218 + uStack_14 * 8), (int)pDVar12, (int(__fastcall*)(D2UnitStrc*, void*))(pRoom), (void*)(uint32_t)pDVar1->Y, *(int*)(byte_6FB91218 + uStack_14 * 8));
					if ((pDVar11 != nullptr) && (iVar9 = sub_6FB29550((int*)pDVar11), iVar9 == 0))
					{
						sub_6FB3DC50(pUnit, pDVar11, 0);
						return;
					}
					iVar10 = iVar10 + 1;
				} while (iVar10 < (int)pDStack_18);
			}
		}
		if (!bVar6)
		{
			return;
		}
		iVar9 = MISSILE_GetRemainingFrames(pUnit);
		if (iVar9 != 1)
		{
			return;
		}
		iVar9 = PATH_GetVelocity(pDynamicPath);
		if (iVar9 == 0)
		{
			return;
		}
		bVar6 = false;
	} while (true);
}

//D2Client.0x6FB3DBB0
int32_t __fastcall sub_6FB3DBB0(D2UnitStrc* pUnit)
{
	short sVar1;
	int iVar2;
	D2GfxLightStrc* pDVar3;

	if (pUnit == nullptr)
	{
		return 0;
	}
	iVar2 = pUnit->dwClassId;
	if ((((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c))) &&
	        (iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar2 * 0x1a4, iVar2 != 0)) &&
	    (sVar1 = *(short*)(iVar2 + 0x12), -1 < sVar1))
	{
		iVar2 = sub_6FB4F990((int)pUnit, (int)sVar1);
		if (iVar2 != 0)
		{
			sub_6FB555C0(iVar2, (int)pUnit, 0);
		}
	}
	pDVar3 = UNITS_ResetLightMap(pUnit);
	if (pDVar3 != nullptr)
	{
		sub_6FAA4560((int)pDVar3);
	}
	if ((pUnit->dwFlags >> 0x15 & 1) == 1)
	{
		sub_6FB26C70(pUnit->dwUnitId, pUnit->dwUnitType);
		return 0;
	}
	return sub_6FB26BE0(pUnit->dwUnitId, pUnit->dwUnitType);
}

//D2Client.0x6FB3DC50
// TODO: decompilation needs review (unaff_)
uint32_t __fastcall sub_6FB3DC50(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3)
{
	short sVar1;
	uint64_t DVar2;
	uint8_t nDirection;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	D2StatListStrc* pStatList;
	int iVar6;
	D2GfxLightStrc* pDVar7;
	D2StatListStrc* pStatList_00;
	int iVar8;
	void* pfStatRemove;
	D2UnitStrc* unaff_EBX;
	uint32_t unaff_EBP;
	uint32_t uVar9;
	uint32_t* puVar10;
	D2DynamicPathStrc* pDynamicPath;
	uint32_t local_74;
	D2UnitStrc* local_70;
	uint32_t local_6c;
	uint32_t local_64;
	D2UnitStrc* pDStack_60;
	D2UnitStrc* pDStack_5c;
	uint32_t uStack_54;
	uint32_t uStack_48;
	uint32_t uStack_44;
	int iStack_38;
	uint32_t uStack_34;

	if (((pUnit == nullptr) || (iVar4 = pUnit->dwClassId, iVar4 < 0)) ||
	    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4))
	{
		local_74 = 0;
	}
	else
	{
		local_74 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4;
	}
	local_64 = (uint32_t) * (short*)(local_74 + 0x16);
	local_6c = 3;
	pDVar3 = sub_6FB26AD0((int)pUnit);
	if (pUnit == nullptr)
	{
		return 0;
	}
	uVar9 = local_74;
	local_70 = pUnit2;
	if (pUnit2 == nullptr)
	{
	LAB_6fb3dd39:
		if (pDVar3 == nullptr)
			goto LAB_6fb3de04;
		if (pUnit2 != nullptr)
		{
			if ((((((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(local_74 + 4)) != 0) &&
			         (-1 < (int)pDVar3->dwUnitType)) &&
			        ((int)pDVar3->dwUnitType < 2)) &&
			    ((iVar4 = STATES_CheckState(pDVar3, 0x45), iVar4 != 0 ||
			                                                   (iVar4 = STATLIST_UnitGetItemStatOrSkillStatValue(pDVar3, 0x9c, 0), iVar4 != 0))))
			{
				local_6c = 3;
				iVar4 = MISSILE_GetClassId(pUnit);
				if ((iVar4 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar4))
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar4 * 0x1a4;
				}
				if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar4 + 4)) == 0)
				{
					local_6c = 3;
				}
				else
				{
					iVar4 = STATLIST_UnitGetStatValue(pUnit, 0x148, 0);
					if (iVar4 != 0)
					{
						local_6c = 2;
						STATLIST_SetUnitStat(pUnit, 0x148, iVar4 + -1, 0);
					}
				}
			}
			goto LAB_6fb3de04;
		}
	LAB_6fb3de08:
		if ((a3 == 0) && (*(char*)(local_74 + 0x18c) == '\0'))
			goto LAB_6fb3dfd4;
	}
	else
	{
		if ((*(char*)(local_74 + 0x188) != '\0') &&
		    (iVar4 = STATES_CheckState(pUnit2, 0x56), iVar4 != 0))
		{
			return 0;
		}
		iVar4 = MISSILE_CheckUnitIfOwner(pUnit, pUnit2);
		if (iVar4 != 0)
		{
			return 0;
		}
		MISSILE_SetOwner(pUnit, pUnit2);
		pDStack_60 = (D2UnitStrc*)(pUnit2->dwFlags >> 2 & 1);
		if (pDStack_60 == nullptr)
		{
			return 0;
		}
		if (pDVar3 != nullptr)
		{
			uVar5 = sub_6FB29D80(pDVar3, pUnit2);
			if ((uVar5 == 0) && (*(char*)(local_74 + 0x187) == '\0'))
			{
				return 0;
			}
			goto LAB_6fb3dd39;
		}
	LAB_6fb3de04:
		if (pUnit2 == nullptr)
			goto LAB_6fb3de08;
	}
	if ((local_6c & 2) != 0)
	{
		if (((*(char*)(local_74 + 0x188) != '\0') && (pUnit2 != nullptr)) &&
		    (pStatList = STATLIST_AllocStatList(nullptr, 2, (uint32_t) * (uint8_t*)(local_74 + 0x189), pUnit2->dwUnitType,
		         pUnit2->dwUnitId),
		        pStatList != nullptr))
		{
			STATLIST_SetState(pStatList, 0x56);
			STATLIST_SetStatRemoveCallback(pStatList_00, (StatListRemoveCallback)(pfStatRemove));
			D2COMMON_10475_PostStatToStatList(pUnit2, pStatList, 1);
			STATES_ToggleState(pUnit2, 0x56, 1);
		}
		sub_6FB2A830(0, (int)pUnit2, pUnit, 0);
		sVar1 = *(short*)(local_74 + 10);
		if (((0 < sVar1) && (sVar1 < dword_6FB91514)) &&
		    ((*(code**)(byte_6FB913D0 + sVar1 * 4) != nullptr &&
		        (iVar4 = (**(code**)(byte_6FB913D0 + sVar1 * 4))(), iVar4 == 0))))
		{
			return 0;
		}
		if (-1 < *(short*)(local_74 + 0x14))
		{
			sub_6FB55820((int)*(short*)(local_74 + 0x14), pUnit, 0.0, 0.0, 0);
		}
		if ((-1 < *(short*)(local_74 + 0x16)) && (local_6c != 0xffffffff))
		{
			uVar5 = MISSILE_GetLevel(pUnit);
			iVar4 = MISSILE_GetSkill(pUnit);
			pDVar3 = pUnit;
			pUnit2 = unaff_EBX;
			uVar9 = unaff_EBP;
			if ((pUnit->dwUnitType == 0) ||
			    ((pUnit->dwUnitType == 1 ||
			        (pDVar3 = sub_6FB26AD0((int)pUnit), pDVar3 != nullptr))))
			{
				puVar10 = &local_64;
				for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1)
				{
					*puVar10 = 0;
					puVar10 = puVar10 + 1;
				}
				local_64 = 0x20;
				uStack_48 = 0;
				uStack_44 = 0;
				uStack_54 = local_6c;
				pDStack_60 = pDVar3;
				pDStack_5c = pUnit;
				iStack_38 = iVar4;
				uStack_34 = uVar5;
				local_70 = sub_6FB3E070(&local_64);
				if (local_70 != nullptr)
				{
					iVar4 = sub_6FB5FC40((int)pUnit);
					iVar8 = sub_6FB5FC20((int)pUnit);
					iVar6 = sub_6FB5FC00((int)pUnit);
					sub_6FB5FC80((int)local_70, iVar6, iVar8, iVar4);
					sub_6FB60110((int)local_70);
					sub_6FB60130((int)local_70);
					if (local_70->dwClassId == 0x92)
					{
						DVar2 = (uint64_t)((uint64_t)(local_70->pSeed).nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(local_70->pSeed).nHighSeed);
						(*(uint64_t*)&local_70->pSeed) = DVar2;
						pDynamicPath = local_70->pDynamicPath;
						nDirection = (uint8_t)(*(uint32_t*)((uint8_t*)&DVar2 + 0)) & 0x3f;
					}
					else
					{
						nDirection = PATH_GetDirection(pUnit->pDynamicPath);
						pDynamicPath = local_70->pDynamicPath;
					}
					D2COMMON_10160_PathUpdateDirection(pDynamicPath, nDirection);
				}
			}
			else
			{
				local_70 = nullptr;
			}
		}
	}
LAB_6fb3dfd4:
	if ((pUnit2 != nullptr) && (*(char*)(uVar9 + 0x186) == '\0'))
	{
		return 0;
	}
	if ((-1 < *(short*)(uVar9 + 0x12)) &&
	    (iVar4 = sub_6FB4F990((int)pUnit, (int)*(short*)(uVar9 + 0x12)), iVar4 != 0))
	{
		sub_6FB555C0(iVar4, (int)pUnit, 0);
	}
	pDVar7 = UNITS_ResetLightMap(pUnit);
	if (pDVar7 != nullptr)
	{
		sub_6FAA4560((int)pDVar7);
	}
	if ((local_74 & 1) != 0)
	{
		if ((pUnit->dwFlags >> 0x15 & 1) == 1)
		{
			sub_6FB26C70(pUnit->dwUnitId, pUnit->dwUnitType);
			return (uint32_t)local_70;
		}
		sub_6FB26BE0(pUnit->dwUnitId, pUnit->dwUnitType);
	}
	return (uint32_t)local_70;
}

//D2Client.0x6FB3E070
// TODO: decompilation needs review (extraout, unaff_)
D2UnitStrc* __fastcall sub_6FB3E070(uint32_t* a1)
{
	short sVar1;
	int* piVar2;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar3;
	float nX;
	int32_t DVar4;
	D2ActiveRoomStrc* pDVar5;
	int iVar6;
	D2StatListStrc* pStatList;
	uint32_t uVar7;
	int32_t DVar8;
	int32_t DVar9;
	float fVar10;
	int32_t DVar11;
	D2UnitStrc* pDVar12;
	int iVar13;
	D2UnitStrc* pDVar14;
	uint32_t* puVar15;
	D2UnitStrc* pUnit;
	uint32_t uVar16;
	uint32_t extraout_ECX;
	char nFlags;
	D2UnitStrc* pDVar17;
	uint32_t* unaff_EBP;
	uint32_t nVelocity;
	int64_t lVar18;
	uint64_t uVar19;
	char local_24;
	char local_20;
	int32_t local_1c;
	float local_18;
	uint32_t local_14;
	uint64_t local_10;
	D2UnitStrc* apDStack_8[2];

	uVar7 = a1[4];
	if ((((int)uVar7 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= (int)uVar7)) ||
	    (uVar7 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + uVar7 * 0x1a4, uVar7 == 0))
	{
		return nullptr;
	}
	local_14 = uVar7;
	if ((*a1 & 1) == 0)
	{
		pDVar17 = (D2UnitStrc*)a1[2];
		if (pDVar17 == nullptr)
		{
			return pDVar17;
		}
		uVar16 = pDVar17->dwUnitType;
		if ((uVar16 == 2) || ((3 < (int)uVar16 && ((int)uVar16 < 6))))
		{
			nX = (float)pDVar17->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar17->pDynamicPath == nullptr)
		{
			nX = 0.0;
		}
		else
		{
			nX = (float)PATH_GetXPosition(pDVar17->pDynamicPath);
		}
		piVar2 = (int*)a1[2];
		iVar6 = *piVar2;
		if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
		{
			DVar4 = *(int32_t*)(piVar2[0xb] + 0x10);
		}
		else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
		}
		else
		{
			DVar4 = (int32_t)PATH_GetYPosition((D2DynamicPathStrc*)piVar2[0xb]);
		}
	}
	else
	{
		nX = (float)a1[5];
		DVar4 = *(int32_t*)(a1 + 6);
	}
	(*(uint16_t*)((uint8_t*)&local_10 + 0)) = (*(uint16_t*)((uint8_t*)&DVar4 + 0));
	(*(uint16_t*)((uint8_t*)&local_10 + 2)) = (*(uint16_t*)((uint8_t*)&DVar4 + 2));
	if ((D2UnitStrc*)a1[1] == nullptr)
	{
		pDVar17 = CUNIT_GetPlayer();
		if (pDVar17 == nullptr)
			goto LAB_6fb3e2b8;
		pDVar5 = UNITS_GetRoom(pDVar17);
		if (pDVar5 != nullptr)
		{
			iVar6 = (pDVar5->tCoords).nSubtileX;
			if ((((iVar6 <= (int)nX) && ((int)nX < (pDVar5->tCoords).nSubtileWidth + iVar6)) &&
			        (iVar6 = (pDVar5->tCoords).nSubtileY, iVar6 <= (int)DVar4)) &&
			    ((int)DVar4 < (pDVar5->tCoords).nSubtileHeight + iVar6))
				goto LAB_6fb3e296;
			local_10 = (uint64_t)((uint64_t)local_10 & 0xffffffff);
			apDStack_8[0] = nullptr;
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, (D2ActiveRoomStrc***)&(*(uint32_t*)((uint8_t*)&local_10 + 4)), (int*)apDStack_8);
			pDVar17 = nullptr;
			if (apDStack_8[0] != nullptr)
			{
				do
				{
					piVar2 = *(int**)((uint8_t*)((*(uint32_t*)((uint8_t*)&local_10 + 4)) + 0x19) + (int)pDVar17 * 4 + -0x19);
					if (((piVar2 != nullptr) && (*piVar2 <= (int)nX)) &&
					    (((int)nX < piVar2[2] + *piVar2 &&
					        ((piVar2[1] <= (int)DVar4 &&
					            (pDVar12 = (D2UnitStrc*)(*(uint32_t*)((uint8_t*)&local_10 + 4)), (int)DVar4 < piVar2[3] + piVar2[1]))))))
						goto LAB_6fb3e28b;
					pDVar17 = (D2UnitStrc*)((int)&pDVar17->dwUnitType + 1);
				} while (pDVar17 < apDStack_8[0]);
			}
		}
	}
	else
	{
		pDVar5 = UNITS_GetRoom((D2UnitStrc*)a1[1]);
		if (pDVar5 != nullptr)
		{
			iVar6 = (pDVar5->tCoords).nSubtileX;
			if ((((iVar6 <= (int)nX) && ((int)nX < (pDVar5->tCoords).nSubtileWidth + iVar6)) &&
			        (iVar6 = (pDVar5->tCoords).nSubtileY, iVar6 <= (int)DVar4)) &&
			    ((int)DVar4 < (pDVar5->tCoords).nSubtileHeight + iVar6))
				goto LAB_6fb3e296;
			apDStack_8[0] = nullptr;
			local_10 = (uint64_t)((uint64_t)local_10 & 0xffffffff);
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, (D2ActiveRoomStrc***)apDStack_8, (int*)&(*(uint32_t*)((uint8_t*)&local_10 + 4)));
			pDVar17 = nullptr;
			if ((D2UnitStrc*)(*(uint32_t*)((uint8_t*)&local_10 + 4)) != nullptr)
			{
				do
				{
					piVar2 = *(int**)(apDStack_8[0]->unk0x19 + (int)pDVar17 * 4 + -0x19);
					if (((piVar2 != nullptr) && (*piVar2 <= (int)nX)) &&
					    (((int)nX < piVar2[2] + *piVar2 &&
					        ((piVar2[1] <= (int)DVar4 &&
					            (pDVar12 = apDStack_8[0], (int)DVar4 < piVar2[3] + piVar2[1]))))))
						goto LAB_6fb3e28b;
					pDVar17 = (D2UnitStrc*)((int)&pDVar17->dwUnitType + 1);
				} while (pDVar17 < (D2UnitStrc*)((*(uint32_t*)((uint8_t*)&local_10 + 4))));
			}
		}
	}
LAB_6fb3e29a:
	pDVar5 = DUNGEON_FindRoomBySubtileCoordinates(ghAct, (int)nX, (int)DVar4);
	uVar7 = local_14;
	if (pDVar5 == nullptr)
	{
		return nullptr;
	}
LAB_6fb3e2b8:
	uVar16 = *a1;
	if ((uVar16 & 2) == 0)
	{
		local_1c = DVar4;
		local_18 = nX;
		if ((uVar16 & 0x20) != 0)
		{
			local_1c = *(int32_t*)(a1 + 8);
			local_18 = (float)a1[7];
		}
	}
	else
	{
		local_1c = (int32_t)(a1[8] + (int)DVar4);
		local_18 = (float)(a1[7] + (int)nX);
	}
	if ((uVar16 & 4) == 0)
	{
		iVar6 = (uint32_t) * (uint8_t*)(uVar7 + 0x9b) * a1[0xc];
		nVelocity = ((int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3) + (uint32_t) * (uint8_t*)(uVar7 + 0x9a);
	LAB_6fb3e31c:
		nVelocity = nVelocity << 8;
	}
	else
	{
		nVelocity = a1[10];
		if ((uVar16 & 0x10) == 0)
			goto LAB_6fb3e31c;
	}
	(*(uint32_t*)((uint8_t*)&local_10 + 4)) = 100;
	if (((((D2UnitStrc*)a1[1] != nullptr) &&
	         (((uint8_t)((uint8_t*)&gdwBitMasks)[0xc] & *(uint8_t*)(uVar7 + 4)) != 0)) &&
	        (iVar6 = STATES_CheckState((D2UnitStrc*)a1[1], 0x57), iVar6 != 0)) &&
	    (pStatList = STATLIST_GetStatListFromUnitAndState((D2UnitStrc*)a1[1], 0x57),
	        pStatList != nullptr))
	{
		uVar7 = STATLIST_GetStatValue(pStatList, 0xa1, 0);
		(*(uint32_t*)((uint8_t*)&local_10 + 4)) = uVar7;
		if ((int)nVelocity < 0x100001)
		{
			if ((int)uVar7 < 0x10001)
			{
				nVelocity = (int)(uVar7 * nVelocity) / 100;
			}
			else
			{
				if ((int)(uVar7 & 0xfffffff0) < 0x640)
					goto LAB_6fb3e3ba;
				nVelocity = nVelocity * ((int)uVar7 / 100);
			}
		}
		else if ((int)(nVelocity & 0xfffffff0) < 0x640)
		{
		LAB_6fb3e3ba:
			uVar19 = D2C_alldiv((uint32_t)((int64_t)(int)uVar7 * (int64_t)(int)nVelocity),
			    (uint32_t)((uint64_t)((int64_t)(int)uVar7 * (int64_t)(int)nVelocity) >> 0x20), 100, 0);
			nVelocity = (uint32_t)uVar19;
		}
		else
		{
			nVelocity = ((int)nVelocity / 100) * uVar7;
		}
	}
	if (nVelocity != 0)
	{
		if ((int)nVelocity < 0x100001)
		{
			nVelocity = (int)(nVelocity * 0x4b) / 100;
		}
		else if ((int)(nVelocity & 0xfffffff0) < 0x640)
		{
			lVar18 = D2C_allmul(nVelocity, (int)nVelocity >> 0x1f, 0x4b, 0);
			uVar19 = D2C_alldiv((uint32_t)lVar18, (uint32_t)((uint64_t)lVar18 >> 0x20), 100, 0);
			nVelocity = (uint32_t)uVar19;
		}
		else
		{
			nVelocity = ((int)nVelocity / 100) * 0x4b;
		}
	}
	pDVar17 = (D2UnitStrc*)a1[3];
	apDStack_8[0] = pDVar17;
	if (nVelocity == 0)
		goto LAB_6fb3e628;
	pDVar12 = (D2UnitStrc*)a1[1];
	if (pDVar12 == nullptr)
	{
		if (pDVar17 != nullptr)
			goto LAB_6fb3e4c1;
	}
	else if (pDVar17 == nullptr)
	{
		if ((local_18 == nX) && (local_1c == (int32_t)(*(uint32_t*)((uint8_t*)&local_10 + 0))))
		{
			sub_6FABA860(pDVar12, (int*)&local_18, &local_1c);
		}
	}
	else
	{
	LAB_6fb3e4c1:
		if ((pDVar12 != nullptr) && (pDVar17 != pDVar12))
		{
			uVar7 = pDVar17->dwUnitType;
			if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
			{
				iVar6 = pDVar17->pDynamicPath->dwClientCoordY;
			}
			else if (pDVar17->pDynamicPath == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition(pDVar17->pDynamicPath);
			}
			piVar2 = (int*)a1[1];
			iVar13 = *piVar2;
			if ((iVar13 == 2) || ((3 < iVar13 && (iVar13 < 6))))
			{
				iVar13 = *(int*)(piVar2[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
			{
				iVar13 = 0;
			}
			else
			{
				iVar13 = PATH_GetXPosition((D2DynamicPathStrc*)piVar2[0xb]);
			}
			if (iVar6 == iVar13)
			{
				uVar7 = pDVar17->dwUnitType;
				if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
				{
					DVar8 = (*(int32_t*)&pDVar17->pDynamicPath->tTargetCoord);
				}
				else if (pDVar17->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar8 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar8 + 2)) = 0;
				}
				else
				{
					DVar8 = (int32_t)PATH_GetYPosition(pDVar17->pDynamicPath);
				}
				piVar2 = (int*)a1[1];
				iVar6 = *piVar2;
				if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
				{
					DVar9 = *(int32_t*)(piVar2[0xb] + 0x10);
				}
				else if ((D2DynamicPathStrc*)piVar2[0xb] == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
				}
				else
				{
					DVar9 = (int32_t)PATH_GetYPosition((D2DynamicPathStrc*)piVar2[0xb]);
				}
				if (DVar8 == DVar9)
				{
					sub_6FABA860((D2UnitStrc*)a1[1], (int*)&local_18, &local_1c);
					pDVar17 = nullptr;
					apDStack_8[0] = nullptr;
				}
			}
		}
	}
	DVar11 = local_1c;
	fVar10 = local_18;
	if (pDVar17 != nullptr)
	{
		uVar7 = pDVar17->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			fVar10 = (float)pDVar17->pDynamicPath->dwClientCoordY;
		}
		else if (pDVar17->pDynamicPath == nullptr)
		{
			fVar10 = 0.0;
		}
		else
		{
			fVar10 = (float)PATH_GetXPosition(pDVar17->pDynamicPath);
		}
		uVar7 = pDVar17->dwUnitType;
		if ((uVar7 == 2) || ((3 < (int)uVar7 && ((int)uVar7 < 6))))
		{
			DVar11 = (*(int32_t*)&pDVar17->pDynamicPath->tTargetCoord);
		}
		else if (pDVar17->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar11 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar11 + 2)) = 0;
		}
		else
		{
			DVar11 = (int32_t)PATH_GetYPosition(pDVar17->pDynamicPath);
		}
	}
	iVar6 = (int)fVar10 - (int)nX;
	if (iVar6 < 0)
	{
		iVar6 = -iVar6;
	}
	if (iVar6 < 100)
	{
		iVar6 = (int)DVar11 - (*(uint32_t*)((uint8_t*)&local_10 + 0));
		if (iVar6 < 0)
		{
			iVar6 = -iVar6;
		}
		if (iVar6 < 100)
		{
		LAB_6fb3e628:
			pDVar12 = sub_6FB27D50(a1[4], nX, (*(uint32_t*)((uint8_t*)&local_10 + 0)), 3, 0);
			if (pDVar12 == nullptr)
			{
				return nullptr;
			}
			UNITS_SetAnimStartFrame(pDVar12);
			STATLIST_AllocStatListEx(pUnit, nFlags, (StatListValueChangeFunc)(pDVar12), nullptr);
			pDVar12->dwFrameCountPrecise = (uint32_t) * (uint8_t*)((int)local_1c + 0x178) << 8;
			MISSILE_SetAnimSpeed(pDVar12, (uint32_t) * (uint8_t*)((int)local_1c + 0x1a1) << 4);
			if ((char)(*a1 >> 8) < '\0')
			{
				uVar7 = unaff_EBP[0x13];
			}
			else
			{
				uVar7 = (int)*(short*)((int)local_1c + 0x98) * unaff_EBP[0xc] +
				        (int)*(short*)((int)local_1c + 0x96);
				if (((*a1 & 8) != 0) && (*(char*)((int)local_1c + 0x180) != '\0'))
				{
					uVar7 = uVar7 + ((uint32_t) * (uint8_t*)((int)local_1c + 0x182) -
					                    (uint32_t) * (uint8_t*)((int)local_1c + 0x181)) *
					                    unaff_EBP[0xd];
				}
				if ((local_14 != 0) && (local_14 != 100))
				{
					if ((int)uVar7 < 0x100001)
					{
						iVar6 = (int)(uVar7 * 100) / (int)local_14;
					}
					else if ((int)uVar7 >> 4 < (int)local_14)
					{
						lVar18 = D2C_allmul(uVar7, (int)uVar7 >> 0x1f, 100, 0);
						uVar19 = D2C_alldiv((uint32_t)lVar18, (uint32_t)((uint64_t)lVar18 >> 0x20), local_14,
						    (int)local_14 >> 0x1f);
						iVar6 = (int)uVar19;
						pDVar17 = (D2UnitStrc*)(*(uint32_t*)((uint8_t*)&local_10 + 0));
					}
					else
					{
						iVar6 = ((int)uVar7 / (int)local_14) * 100;
					}
					uVar7 = uVar7 + iVar6;
				}
			}
			if ((*unaff_EBP & 0x200) != 0)
			{
				uVar7 = uVar7 - unaff_EBP[0x10];
				pDVar12->nSeqCurrentFramePrecise = unaff_EBP[0x10] << 8;
			}
			MISSILE_SetTotalFrames(pDVar12, uVar7);
			MISSILE_SetCurrentFrame(pDVar12, uVar7);
			if ((*unaff_EBP & 0x800) == 0)
			{
				uVar16 = (uint32_t) * (uint8_t*)((int)local_1c + 0x136);
			}
			else
			{
				uVar16 = unaff_EBP[0x11];
			}
			MISSILE_SetActivateFrame(pDVar12, uVar7 - uVar16);
			pDynamicPath = pDVar12->pDynamicPath;
			if (pDynamicPath != nullptr)
			{
				PATH_SetVelocity(pDynamicPath, 0, __FILE__, __LINE__);
				if (pDVar17 == nullptr)
				{
					D2COMMON_10170_PathSetTargetPos(pDynamicPath, (int)nX, (int)a1);
				}
				else
				{
					PATH_SetTargetUnit(pDynamicPath, pDVar17);
				}
				if (nVelocity != 0)
				{
					PATH_SetVelocity(pDynamicPath, nVelocity, __FILE__, __LINE__);
					D2Common_10142(pDynamicPath, pDVar12, 0);
				}
				if (*(char*)((int)local_1c + 0x135) != '\0')
				{
					pDVar12->dwFlagEx = pDVar12->dwFlagEx | 0x40000;
				}
				MISSILE_SetOwner(pDVar12, (D2UnitStrc*)unaff_EBP[1]);
				PATH_SetAcceleration(pDynamicPath, (int)*(short*)((int)local_1c + 0x9e));
				PATH_SetMaxVelocity(pDynamicPath, (uint32_t) * (uint8_t*)((int)local_1c + 0x9c) << 8);
				if ((*unaff_EBP & 0x2000) != 0)
				{
					DVar3 = (uint64_t)((uint64_t)(pDVar12->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pDVar12->pSeed).nHighSeed);
					(*(uint64_t*)&pDVar12->pSeed) = DVar3;
					PATH_SetDirection(pDVar12->pDynamicPath, (uint8_t)(*(uint32_t*)((uint8_t*)&DVar3 + 0)) & 0x3f);
				}
				sub_6FB5FB10((int)pDVar12);
				sub_6FB60130((int)pDVar12);
				if ((*unaff_EBP & 0x400) != 0)
				{
					uVar7 = UNITS_GetDistanceToCoordinates(pDVar12, (int)nX, (int)a1);
					if (uVar7 == 0)
					{
						uVar7 = 1;
					}
					if (nVelocity << 4 != 0)
					{
						uVar7 = (uVar7 << 0x10) / (nVelocity << 4);
						MISSILE_SetCurrentFrame(pDVar12, uVar7);
						MISSILE_SetTotalFrames(pDVar12, uVar7);
					}
				}
				if ((*unaff_EBP & 0x100) != 0)
				{
					uVar7 = MISSILE_GetTotalFrames(pDVar12);
					sub_6FB60080((int)pDVar12, unaff_EBP[9], uVar7);
					sub_6FB5FE00((int*)pDVar12);
					local_24 = (char)a1;
					local_20 = SUB41(nX, 0);
					PATH_SetDirection(pDynamicPath, local_24 + local_20 & 0x3f);
					D2COMMON_10203_PATH_SetRotateFlag(pDynamicPath, 0);
				}
				MISSILE_SetSkill(pDVar12, unaff_EBP[0xb]);
				MISSILE_SetLevel(pDVar12, (uint16_t)unaff_EBP[0xc]);
				if ((D2UnitStrc*)unaff_EBP[1] != nullptr)
				{
					UNITS_StoreOwner(pDVar12, (D2UnitStrc*)unaff_EBP[1]);
					pDVar17 = (D2UnitStrc*)unaff_EBP[1];
					local_18 = 0.0;
					if (((pDVar17 == nullptr) || (pDVar17->dwUnitType == 0)) ||
					    (pDVar17->dwUnitType == 1))
					{
						iVar6 = MISSILE_GetClassId(pDVar12);
						if ((iVar6 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb6c) <= iVar6))
						{
							iVar6 = 0;
						}
						else
						{
							iVar6 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb64) + iVar6 * 0x1a4;
						}
						if (((uint8_t)((uint8_t*)&gdwBitMasks)[8] & *(uint8_t*)(iVar6 + 4)) != 0)
						{
							iVar6 = STATLIST_UnitGetStatValue(pDVar17, 0xa6, 0);
							iVar13 = STATLIST_UnitGetItemStatOrSkillStatValue(pDVar17, 0x9c, 0);
							iVar6 = iVar6 + iVar13;
							if (iVar6 != 0)
							{
								if (((pDVar17 == nullptr) || (pDVar17->dwUnitType != 0)) ||
								    (pDVar14 = CUNIT_GetPlayer(), pDVar14 == pDVar17))
								{
									iVar13 = STATLIST_GetUnitBaseStat(pDVar17, 0x148, 0);
								}
								else
								{
									iVar6 = 100;
									iVar13 = 0;
								}
								SEED_InitLowSeed((D2SeedStrc*)(&local_10), iVar13);
								while (((int)local_18 < 4 &&
								        (local_10 = (uint64_t)(((uint64_t)local_10 & 0xffffffff) * 0x6ac690c5 +
								                               ((uint64_t)local_10 >> 0x20)),
								            (int)(((uint64_t)local_10 & 0xffffffff) % 100) < iVar6)))
								{
									local_18 = (float)((int)local_18 + 1);
								}
								STATLIST_SetUnitStat(pDVar12, 0x148, (int)local_18, 0);
							}
						}
					}
				}
				DVar4 = local_1c;
				pDVar12->dwFlags = pDVar12->dwFlags & 0xfffffff7;
				if ((dword_6FB91214 == 0) || ((*unaff_EBP & 0x4000) != 0))
				{
					sub_6FB296E0((int)pDVar12);
					DVar4 = local_1c;
				}
				else if ((*(char*)((int)local_1c + 0x130) != '\0') || ((char)unaff_EBP[0x14] != '\0'))
				{
					uVar19 = sub_6FB296E0((int)pDVar12);
					puVar15 = sub_6FAA4280(pDVar12, 1, (uint32_t) * (uint8_t*)((int)DVar4 + 0x130), 0xff,
					    CONCAT31((int32_t)((uint64_t)uVar19 >> 8),
					        *(uint8_t*)((int)DVar4 + 0x132)),
					    CONCAT31((int32_t)((uint64_t)uVar19 >> 0x28),
					        *(uint8_t*)((int)DVar4 + 0x133)),
					    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8),
					        *(uint8_t*)((int)DVar4 + 0x134)));
					pDVar12->dwInteractGUID = (uint32_t)puVar15;
				}
				if ((code*)unaff_EBP[0x15] != nullptr)
				{
					(*(code*)unaff_EBP[0x15])();
				}
				sVar1 = *(short*)((int)DVar4 + 0x12);
				if ((sVar1 != 0) && (sVar1 != 0))
				{
					sub_6FB55820((int)sVar1, pDVar12, 0.0, 0.0, 0);
					if ((unaff_EBP[1] != 0) && (iVar6 = sub_6FB4F990(unaff_EBP[1], 0x13a), iVar6 != 0))
					{
						sub_6FB556A0(iVar6);
					}
				}
				if ((D2UnitStrc*)unaff_EBP[1] != nullptr)
				{
					sub_6FB462A0((D2UnitStrc*)unaff_EBP[1], (int)pDVar12);
				}
				return pDVar12;
			}
			sub_6FB26C70(pDVar12->dwUnitId, pDVar12->dwUnitType);
			return nullptr;
		}
	}
	return nullptr;
LAB_6fb3e28b:
	pDVar5 = *(D2ActiveRoomStrc**)(pDVar12->unk0x19 + (int)pDVar17 * 4 + -0x19);
LAB_6fb3e296:
	uVar7 = local_14;
	if (pDVar5 == nullptr)
		goto LAB_6fb3e29a;
	goto LAB_6fb3e2b8;
}

//D2Client.0x6FB3EAF0
D2UnitStrc* __fastcall sub_6FB3EAF0(int a1, uint32_t a2, uint32_t a3, D2UnitStrc** pUnit, uint32_t a5, uint32_t a6)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c[4];
	uint32_t local_4c;
	uint32_t local_48;
	D2UnitStrc** local_44;
	uint32_t local_30;
	uint32_t local_2c;

	pDVar1 = nullptr;
	if (a1 != 0)
	{
		puVar3 = local_5c;
		for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
		local_44 = pUnit;
		local_48 = a3;
		local_2c = a6;
		local_5c[0] = 1;
		local_30 = a5;
		local_5c[1] = a1;
		local_4c = a2;
		pDVar1 = sub_6FB3E070(local_5c);
	}
	return pDVar1;
}

//D2Client.0x6FB3EB50
D2UnitStrc* __fastcall sub_6FB3EB50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, D2UnitStrc* pUnit2, uint32_t a5, uint32_t a6)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	uint32_t local_4c;
	uint32_t local_40;
	D2UnitStrc* local_3c;
	uint32_t local_30;
	uint32_t local_2c;

	if (pUnit == nullptr)
	{
		return nullptr;
	}
	pDVar1 = pUnit;
	if ((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1))
	{
		pDVar1 = sub_6FB26AD0((int)pUnit);
		if (pDVar1 == nullptr)
		{
			return nullptr;
		}
	}
	puVar3 = &local_5c;
	for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	local_40 = a3;
	local_3c = pUnit2;
	local_5c = 0x20;
	local_30 = a5;
	local_2c = a6;
	local_58 = pDVar1;
	local_54 = pUnit;
	local_4c = a2;
	pDVar1 = sub_6FB3E070(&local_5c);
	return pDVar1;
}

//D2Client.0x6FB3EBE0
uint32_t* __fastcall sub_6FB3EBE0(D2UnitStrc* pUnit, uint32_t a2, int a3, int a4, int a5, int a6, uint32_t a7, uint32_t a8, int a9)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	int32_t DVar4;
	int iVar5;
	uint32_t* puVar6;
	uint32_t local_5c;
	D2UnitStrc* local_58;
	uint32_t uStack_4c;
	int local_48;
	int iStack_44;
	int iStack_40;
	int iStack_3c;
	int iStack_38;
	uint32_t uStack_30;
	uint32_t uStack_2c;

	if (pUnit != nullptr)
	{
		pDVar2 = pUnit;
		if (((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1)) &&
		    (pDVar2 = sub_6FB26AD0((int)pUnit), pDVar2 == nullptr))
		{
			return nullptr;
		}
		if (((a5 == 0) || (a6 == 0)) &&
		    (iVar3 = sub_6FABA950(pUnit, &a5, &a6), iVar3 == 0))
		{
			return nullptr;
		}
		if ((a5 != 0) && (a6 != 0))
		{
			iVar3 = a9;
			if (a9 == 0)
			{
				iVar3 = 0x1e;
			}
			puVar6 = &local_5c;
			for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar6 = 0;
				puVar6 = puVar6 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			local_5c = 0x521;
			local_58 = pDVar2;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				local_48 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				local_48 = 0;
			}
			else
			{
				local_48 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			local_48 = local_48 + a3;
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				DVar4 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
			}
			else
			{
				DVar4 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
			}
			iStack_44 = (int)DVar4 + a4;
			iStack_40 = a5;
			iStack_3c = a6;
			uStack_30 = a7;
			uStack_2c = a8;
			uStack_4c = a2;
			iStack_38 = iVar3;
			pDVar2 = sub_6FB3E070(&local_5c);
			return &pDVar2->dwUnitType;
		}
	}
	return nullptr;
}

//D2Client.0x6FB3ED40
D2UnitStrc* __fastcall sub_6FB3ED40(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int* piVar3;
	int local_64;
	int local_60[2];
	D2UnitStrc* local_58;
	D2UnitStrc* local_54;
	uint32_t local_4c;
	int local_40;
	int local_3c;
	uint32_t local_30;
	uint32_t local_2c;

	if (pUnit == nullptr)
	{
		return nullptr;
	}
	local_58 = pUnit;
	if ((pUnit->dwUnitType != 0) && (pUnit->dwUnitType != 1))
	{
		local_58 = sub_6FB26AD0((int)pUnit);
		if (local_58 == nullptr)
		{
			return nullptr;
		}
	}
	iVar1 = sub_6FABA950(local_58, &local_64, local_60);
	if (iVar1 == 0)
	{
		return nullptr;
	}
	piVar3 = local_60;
	for (iVar1 = 0x17; piVar3 = piVar3 + 1, iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*piVar3 = 0;
	}
	local_40 = local_64;
	local_2c = a4;
	local_60[1] = 0x420;
	local_3c = local_60[0];
	local_30 = a3;
	local_54 = pUnit;
	local_4c = a2;
	pDVar2 = sub_6FB3E070((uint32_t*)(local_60 + 1));
	return pDVar2;
}

//D2Client.0x6FB3EDF0
void __fastcall sub_6FB3EDF0(D2UnitStrc* pUnit, int a2, int a3)
{
	float nX;
	int iVar1;
	uint64_t DVar2;
	uint64_t uVar3;
	uint16_t uVar4;
	D2ActiveRoomStrc* pDVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uStack_1c;
	D2ActiveRoomStrc** ppDStack_18;
	int iStack_14;
	int iStack_10;
	uint32_t local_c;
	D2CoordStrc DStack_8;

	local_c = a2;
	pDVar5 = UNITS_GetRoom(pUnit);
	if ((((-1 < a2) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a2 < *(int*)(iVar1 + 0xa80))) && (iVar6 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + a2 * 0x1a8), -1 < iVar6)) &&
	    ((iVar6 < *(int*)(iVar1 + 0xa98) &&
	        (iStack_10 = *(int*)(iVar1 + 0xa90) + iVar6 * 0x134, iStack_10 != 0))))
	{
		UNITS_GetCoords(pUnit, &DStack_8);
		iStack_14 = 0;
		do
		{
			uVar3 = (uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			        (uint64_t)(pUnit->pSeed).nHighSeed;
			(pUnit->pSeed).nLowSeed = (uint32_t)uVar3;
			nX = (float)((int)((uVar3 & 0xffffffff) % 5) + -2 + DStack_8.nX);
			DVar2 = (uint64_t)((uVar3 & 0xffffffff) * 0x6ac690c5 + (uVar3 >> 0x20));
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			iVar1 = (int)(((uint64_t)DVar2 & 0xffffffff) % 5) + -2 + DStack_8.nY;
			if (pDVar5 == nullptr)
			{
			LAB_6fb3ef49:
				pDVar5 = nullptr;
			}
			else
			{
				iVar6 = (pDVar5->tCoords).nSubtileX;
				if ((((int)nX < iVar6) || ((pDVar5->tCoords).nSubtileWidth + iVar6 <= (int)nX)) ||
				    ((iVar6 = (pDVar5->tCoords).nSubtileY, iVar1 < iVar6 ||
				                                               ((pDVar5->tCoords).nSubtileHeight + iVar6 <= iVar1))))
				{
					ppDStack_18 = nullptr;
					uStack_1c = 0;
					DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_18, (int*)&uStack_1c);
					uVar7 = 0;
					if (uStack_1c != 0)
					{
						do
						{
							pDVar5 = ppDStack_18[uVar7];
							if ((((pDVar5 != nullptr) &&
							         (iVar6 = (pDVar5->tCoords).nSubtileX, iVar6 <= (int)nX)) &&
							        ((int)nX < (pDVar5->tCoords).nSubtileWidth + iVar6)) &&
							    ((iVar6 = (pDVar5->tCoords).nSubtileY, iVar6 <= iVar1 &&
							                                               (iVar1 < (pDVar5->tCoords).nSubtileHeight + iVar6))))
							{
								pDVar5 = ppDStack_18[uVar7];
								goto LAB_6fb3ef4b;
							}
							uVar7 = uVar7 + 1;
						} while (uVar7 < uStack_1c);
					}
					goto LAB_6fb3ef49;
				}
			}
		LAB_6fb3ef4b:
			uVar4 = COLLISION_CheckMaskWithSize(pDVar5, (int)nX, iVar1, (int)*(char*)(iStack_10 + 8), 0x3f11);
			if (uVar4 == 0)
			{
				sub_6FB27D50(local_c, nX, iVar1, 1, 0);
				a3 = a3 + -1;
			}
		} while ((0 < a3) && (iStack_14 = iStack_14 + 1, iStack_14 < 10));
	}
}

//D2Client.0x6FB3EFB0
void __fastcall sub_6FB3EFB0(D2ActiveRoomStrc* pActiveRoom)
{
	uint32_t uVar1;
	char cVar2;
	int iVar3;
	uint64_t DVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	uint16_t uVar8;
	int iVar9;
	D2LevelsTxt* pDVar10;
	int iVar11;
	uint32_t uVar12;
	uint32_t uVar13;
	uint32_t uVar14;
	uint16_t* puVar15;
	D2SeedStrc* pDVar16;
	uint32_t uVar17;
	int iStack_48;
	int iStack_3c;
	int iStack_38;
	D2DrlgCoordsStrc DStack_20;

	iVar9 = DUNGEON_GetLevelIdFromRoom(pActiveRoom);
	if (iVar9 != 0)
	{
		pDVar10 = DATATBLS_GetLevelsTxtRecord(iVar9);
		if (pActiveRoom == nullptr)
		{
			pDVar16 = nullptr;
		}
		else
		{
			pDVar16 = &pActiveRoom->pSeed;
		}
		puVar15 = pDVar10->wCMon;
		iStack_38 = 0;
		do
		{
			if ((short)*puVar15 < 0)
			{
				return;
			}
			DVar4 = (uint64_t)((uint64_t)pDVar16->nLowSeed * 0x6ac690c5 + (uint64_t)pDVar16->nHighSeed);
			*(uint64_t*)pDVar16 = DVar4;
			if ((uint32_t)(((uint64_t)DVar4 & 0xffffffff) % 100) < (uint32_t)(int)(short)puVar15[4])
			{
				iVar9 = (int)(short)*puVar15;
				if ((iVar9 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar9))
				{
					iStack_48 = 0;
				}
				else
				{
					iStack_48 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar9 * 0x1a8;
				}
				uVar14 = (uint32_t) * (uint8_t*)(iStack_48 + 0x30) - (uint32_t) * (uint8_t*)(iStack_48 + 0x2f);
				if ((int)uVar14 < 1)
				{
					uVar14 = 0;
				}
				else if ((uVar14 & uVar14 - 1) == 0)
				{
					DVar4 = (uint64_t)(((uint64_t)DVar4 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar4 + 4)));
					*(uint64_t*)pDVar16 = DVar4;
					uVar14 = uVar14 - 1 & (*(uint32_t*)((uint8_t*)&DVar4 + 0));
				}
				else
				{
					DVar4 = (uint64_t)(((uint64_t)DVar4 & 0xffffffff) * 0x6ac690c5 + (uint64_t)(*(uint32_t*)((uint8_t*)&DVar4 + 4)));
					*(uint64_t*)pDVar16 = DVar4;
					uVar14 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar14);
				}
				iStack_3c = *(uint8_t*)(iStack_48 + 0x2f) + uVar14;
				if (puVar15[8] != 0)
				{
					iStack_3c = iStack_3c * (short)puVar15[8];
				}
				if (0 < iStack_3c)
				{
					do
					{
						uVar17 = (uint32_t)(short)*puVar15;
						DUNGEON_GetRoomCoordinates(pActiveRoom, &DStack_20);
						iVar7 = DStack_20.nSubtileHeight;
						iVar6 = DStack_20.nSubtileWidth;
						iVar5 = DStack_20.nSubtileY;
						iVar9 = DStack_20.nSubtileX;
						uVar14 = DStack_20.nSubtileWidth - 1;
						uVar1 = DStack_20.nSubtileHeight - 1;
						if ((((-1 < (int)uVar17) &&
						         (iVar3 = *(int*)((uint8_t*)&sgptDataTables), (int)uVar17 < *(int*)(iVar3 + 0xa80))) &&
						        (iVar11 = (int)*(short*)(*(int*)(iVar3 + 0xa78) + 0x18 + uVar17 * 0x1a8),
						            -1 < iVar11)) &&
						    ((iVar11 < *(int*)(iVar3 + 0xa98) &&
						        (iVar3 = *(int*)(iVar3 + 0xa90) + iVar11 * 0x134, iVar3 != 0))))
						{
							cVar2 = *(char*)(iVar3 + 8);
							iStack_48 = 0;
							do
							{
								if ((int)uVar14 < 1)
								{
									uVar12 = 0;
								}
								else if ((uVar14 & iVar6 - 2U) == 0)
								{
									uVar12 = sub_6FAA88D0(&pDVar16->nLowSeed);
									uVar12 = uVar12 & iVar6 - 2U;
								}
								else
								{
									uVar12 = sub_6FAA88D0(&pDVar16->nLowSeed);
									uVar12 = uVar12 % uVar14;
								}
								if ((int)uVar1 < 1)
								{
									uVar13 = 0;
								}
								else if ((uVar1 & iVar7 - 2U) == 0)
								{
									uVar13 = sub_6FAA88D0(&pDVar16->nLowSeed);
									uVar13 = uVar13 & iVar7 - 2U;
								}
								else
								{
									DVar4 = (uint64_t)((uint64_t)pDVar16->nLowSeed * 0x6ac690c5 + (uint64_t)pDVar16->nHighSeed);
									*(uint64_t*)pDVar16 = DVar4;
									uVar13 = (uint32_t)(((uint64_t)DVar4 & 0xffffffff) % (uint64_t)uVar1);
								}
								uVar8 = COLLISION_CheckMaskWithSize(pActiveRoom, uVar12 + iVar9, uVar13 + iVar5, (int)cVar2, 0x3f11);
								if (uVar8 == 0)
								{
									if (iStack_48 < 10)
									{
										sub_6FB27D50(uVar17, (float)(uVar12 + iVar9), uVar13 + iVar5, 1, 0);
									}
									break;
								}
								iStack_48 = iStack_48 + 1;
							} while (iStack_48 < 10);
						}
						iStack_3c = iStack_3c + -1;
					} while (iStack_3c != 0);
				}
			}
			puVar15 = puVar15 + 1;
			iStack_38 = iStack_38 + 1;
		} while (iStack_38 < 4);
	}
}

//D2Client.0x6FB3F270
int __fastcall sub_6FB3F270(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, code* a4)
{
	D2UnitStrc* pDVar1;
	D2ActiveRoomStrc* pRoom;
	int iVar2;
	uint32_t uStack_c;
	uint32_t uStack_8;
	D2ActiveRoomStrc** ppDStack_4;

	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom != nullptr)
	{
		DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &ppDStack_4, (int*)&uStack_8);
		uStack_c = 0;
		if (uStack_8 != 0)
		{
			do
			{
				for (pDVar1 = ppDStack_4[uStack_c]->pUnitFirst; pDVar1 != nullptr;
				     pDVar1 = pDVar1->pRoomNext)
				{
					iVar2 = (*a4)(a2, a3);
					if (iVar2 != 0)
					{
						return iVar2;
					}
				}
				uStack_c = uStack_c + 1;
			} while (uStack_c < uStack_8);
		}
	}
	return 0;
}

//D2Client.0x6FB3F2F0
void __fastcall sub_6FB3F2F0(int a1)
{
	int* piVar1;
	int iVar2;

	piVar1 = (int*)(&dword_6FBBC20C);
	iVar2 = 0;
	do
	{
		if (*piVar1 == 0)
		{
			*piVar1 = a1;
			return;
		}
		piVar1 = piVar1 + 1;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 8);
}

//D2Client.0x6FB3F310
void __fastcall sub_6FB3F310(int a1)
{
	int* piVar1;
	int iVar2;

	piVar1 = (int*)(&dword_6FBBC20C);
	iVar2 = 0;
	do
	{
		if (*piVar1 == a1)
		{
			*piVar1 = 0;
			return;
		}
		piVar1 = piVar1 + 1;
		iVar2 = iVar2 + 1;
	} while (iVar2 < 8);
}

//D2Client.0x6FB3F330
void __cdecl sub_6FB3F330()
{
	int iVar1;
	uint32_t* puVar2;

	puVar2 = &dword_6FBBC20C;
	for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
}

//D2Client.0x6FB3F350
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB3F350(D2UnitStrc* pUnit)
{
	D2UnitStrc* pUnit2;
	D2DynamicPathStrc* pDynamicPath;
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	uint32_t extraout_EDX_02;
	uint32_t extraout_EDX_03;
	uint32_t uVar4;
	int* piVar5;
	uint32_t* puVar6;
	int* local_24;
	uint32_t uStack_20;
	uint32_t uStack_1c;
	D2UnitStrc** ppDStack_18;

	pDVar1 = sub_6FB40AD0((int*)pUnit);
	if (pDVar1 == nullptr)
	{
		return;
	}
	if (0 < (int)pDVar1->dwUnitType)
	{
		pDVar1->dwUnitType = pDVar1->dwUnitType - 1;
		return;
	}
	uVar4 = 0x7fffffff;
	pDVar1 = nullptr;
	piVar5 = (int*)(&dword_6FBBC20C);
	local_24 = (int*)0x8;
	do
	{
		pUnit2 = (D2UnitStrc*)*piVar5;
		if ((((pUnit2 != nullptr) && (pUnit2->dwAnimMode != 0)) && (pUnit2->dwAnimMode != 0xc)) && (uVar2 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2), (int)uVar2 < (int)uVar4))
		{
			pDVar1 = (D2UnitStrc*)*piVar5;
			uVar4 = uVar2;
		}
		piVar5 = piVar5 + 1;
		local_24 = (int*)((int)local_24 + -1);
	} while (local_24 != nullptr);
	if ((pDVar1 == nullptr) && (pDVar1 = CUNIT_GetPlayer(), pDVar1 == nullptr))
	{
		pDVar1 = sub_6FB40AD0((int*)pUnit);
		if (pDVar1 != nullptr)
		{
			pDVar1->dwUnitType = 0x19;
		}
	LAB_6fb3f3dc:
		puVar6 = &uStack_1c;
		for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		uStack_1c = sub_6FAB6A60((int*)pUnit);
		ppDStack_18 = sub_6FAB6A90((int*)pUnit);
		sub_6FB42D40(7, pUnit, &uStack_1c);
		return;
	}
	if (0x1e < (int)uVar4)
	{
		uVar4 = uVar4 - 0xf;
		if (199 < (int)uVar4)
		{
			uVar4 = 200;
		}
		pDVar1 = sub_6FB40AD0((int*)pUnit);
		if (pDVar1 != nullptr)
		{
			pDVar1->dwUnitType = uVar4;
		}
		puVar6 = &uStack_1c;
		for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*puVar6 = 0;
			puVar6 = puVar6 + 1;
		}
		uStack_1c = sub_6FAB6A60((int*)pUnit);
		ppDStack_18 = sub_6FAB6A90((int*)pUnit);
		sub_6FB42D40(7, pUnit, &uStack_1c);
		return;
	}
	iVar3 = sub_6FAAE570(pUnit->dwClassId);
	uVar2 = extraout_EDX;
	if ((iVar3 != 0) &&
	    (uVar2 = (uint32_t) * (uint8_t*)(iVar3 + 0xe) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x18), uStack_20 = uVar2,
	        uVar2 != 0))
	{
		uVar4 = pUnit->dwAnimMode;
		iVar3 = MONSTERS_IsDead(pUnit);
		if (iVar3 != 0)
		{
			return;
		}
		if (uVar4 != 1)
		{
			return;
		}
		uVar4 = sub_6FB40970(pUnit->dwClassId, 2);
		if ((uVar4 != 0) && (uVar4 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 100), 0x27 < (int)uVar4))
		{
			if (((int)uVar4 < 0x3c) && (pDVar1 != nullptr))
			{
				sub_6FB3F830(pUnit, pDVar1, 0, 6);
				return;
			}
			if (((int)uVar4 < 0x50) && (pDVar1 != nullptr))
			{
				sub_6FB3F8A0(pUnit, (int*)pDVar1, 8, 1, 4);
				return;
			}
			sub_6FB3FA50(pUnit, CONCAT31((int32_t)((uint32_t)extraout_EDX_00 >> 8), 8), 1, 4);
			return;
		}
		sub_6FB3FC10((int*)pUnit, 0x14);
	switchD_6fb3f571_caseD_96:
		sub_6FB3FB80(pUnit);
		return;
	}
	iVar3 = pUnit->dwClassId;
	if (iVar3 < 0x11b)
	{
		if (0x115 < iVar3)
		{
			return;
		}
		switch (iVar3)
		{
		case 0x95:
		case 0x10c:
			if (pUnit->dwAnimMode == 1)
			{
				local_24 = nullptr;
				uStack_20 = 0x7fffffff;
				sub_6FB3F270(pUnit, (uint32_t)(&local_24), (uint32_t)(&uStack_20), (code*)(sub_6FB3F7D0));
				if (local_24 != nullptr)
				{
					pDynamicPath = pUnit->pDynamicPath;
					PATH_SetFootprintCollisionMask(pDynamicPath, 0x3c01);
					if (3 < (int)uStack_20)
					{
						uVar4 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 100);
						if (0x1d < (int)uVar4)
						{
							sub_6FB3FC10((int*)pUnit, 5);
							return;
						}
						sub_6FB3FA50(pUnit, CONCAT31((int32_t)((uint32_t)extraout_EDX_02 >> 8), 2), 1, 0);
						return;
					}
					PATH_SetFootprintCollisionMask(pDynamicPath, 0xc01);
					iVar3 = sub_6FB3F8A0(pUnit, local_24, 4, 0xc, 0x78);
					if (iVar3 == 0)
					{
						sub_6FB3FA50(pUnit, CONCAT31((int32_t)((uint32_t)extraout_EDX_01 >> 8), 4), 0xc, 0x78);
						return;
					}
				}
			}
			break;
		default:
			goto switchD_6fb3f571_caseD_96;
		case 0x97:
		case 0x10d:
			goto switchD_6fb3f571_caseD_97;
		case 0x9d:
		case 0x9e:
		switchD_6fb3f571_caseD_9d:
			sub_6FB3FC30(pUnit, pDVar1, uVar4);
			return;
		case 0x9f:
			if (pUnit->dwAnimMode == 1)
			{
				if (4 < uVar4)
				{
					sub_6FB3FA50(pUnit, D2C_ZEXT(9), 1, 0);
					return;
				}
				uVar4 = sub_6FAA88F0((uint64_t*)&pUnit->pSeed, 100);
				if (0x41 < (int)uVar4)
				{
					sub_6FB3FA50(pUnit, CONCAT31((int32_t)((uint32_t)extraout_EDX_03 >> 8), 0xc), 1, 0x1e);
					return;
				}
				sub_6FB3F8A0(pUnit, (int*)pDVar1, 8, 1, 0x1e);
				return;
			}
			break;
		case 0xe3:
			sub_6FB3FE20(pUnit, (int*)pDVar1, uVar4);
			return;
		}
	}
	else
	{
		if (iVar3 < 0x141)
		{
			if (iVar3 == 0x140)
				goto LAB_6fb3f3dc;
			if (iVar3 != 0x11b)
			{
				if (iVar3 == 0x13e)
				{
					sub_6FB40390(pUnit, (int*)pDVar1, uVar4);
					return;
				}
				if (iVar3 == 0x13f)
					goto switchD_6fb3f571_caseD_9d;
				goto switchD_6fb3f571_caseD_96;
			}
		}
		else if (iVar3 != 0x153)
		{
			if (iVar3 == 0x22c)
			{
				sub_6FB40560(pUnit, pDVar1, uVar4);
				return;
			}
			if (iVar3 == 0x23e)
			{
				sub_6FB40790((int*)pUnit, pDVar1, uVar4);
				return;
			}
			goto switchD_6fb3f571_caseD_96;
		}
	switchD_6fb3f571_caseD_97:
		sub_6FB3FFE0(pUnit, (int*)pDVar1, uVar4);
	}
}

//D2Client.0x6FB3F7D0
// TODO: decompilation needs review (in_reg)
uint32_t __cdecl sub_6FB3F7D0(uint32_t* a1, int* a2)
{
	int iVar1;
	D2UnitStrc* in_ECX;
	D2UnitStrc* in_EDX;

	if (((in_ECX != in_EDX) && (in_EDX != nullptr)) &&
	    ((in_EDX->dwUnitType == 0 ||
	        (((in_EDX->dwUnitType == 1 && (in_EDX->dwClassId != 0x95)) && (in_EDX->dwClassId != 0x22c))))))
	{
		iVar1 = sub_6FB29550((int*)in_ECX);
		if (iVar1 == 0)
		{
			iVar1 = UNITS_GetDistanceToOtherUnit(in_ECX, in_EDX);
			if (iVar1 < *a2)
			{
				*a1 = (uint32_t)(in_EDX);
				*a2 = iVar1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB3F830
void __fastcall sub_6FB3F830(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t a3, uint32_t a4)
{
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar1;
	uint32_t local_1c;
	uint32_t local_18;
	uint32_t local_14;
	int iStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	local_1c = 6;
	pDynamicPath = pUnit->pDynamicPath;
	if (pUnit2 == nullptr)
	{
		local_18 = 0xffffffff;
	}
	else
	{
		local_1c = pUnit2->dwUnitType;
		local_18 = pUnit2->dwUnitId;
	}
	local_14 = 0;
	iStack_10 = PATH_GetType(pDynamicPath);
	uStack_c = a4;
	bVar1 = PATH_GetMaxDistance(pDynamicPath);
	uStack_8 = (uint32_t)bVar1;
	sub_6FB42D40(a3, pUnit, &local_1c);
}

//D2Client.0x6FB3F8A0
uint32_t __fastcall sub_6FB3F8A0(D2UnitStrc* pUnit, int* a2, uint32_t a3, uint32_t a4, uint32_t a5)
{
	D2DynamicPathStrc* pDynamicPath;
	uint8_t bVar1;
	uint16_t uVar2;
	uint32_t uVar3;
	int32_t DVar4;
	int iVar5;
	D2ActiveRoomStrc* pRoom;
	int iVar6;
	int iVar7;
	int nX;
	int nUnitSize;
	uint32_t local_24;
	int32_t DStack_20;
	uint32_t uStack_1c;
	int iStack_18;
	uint32_t uStack_14;
	int iStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	uVar3 = pUnit->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		local_24 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_24 = 0;
	}
	else
	{
		local_24 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar3 = pUnit->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		DStack_20 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_20 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_20 + 2)) = 0;
	}
	else
	{
		DStack_20 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	iVar6 = *a2;
	if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
	{
		uVar3 = *(uint32_t*)(a2[0xb] + 0xc);
	}
	else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
	{
		uVar3 = 0;
	}
	else
	{
		uVar3 = PATH_GetXPosition((D2DynamicPathStrc*)a2[0xb]);
	}
	iVar6 = *a2;
	if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
	{
		DVar4 = *(int32_t*)(a2[0xb] + 0x10);
	}
	else if ((D2DynamicPathStrc*)a2[0xb] == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DVar4 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar4 + 2)) = 0;
	}
	else
	{
		DVar4 = (int32_t)PATH_GetYPosition((D2DynamicPathStrc*)a2[0xb]);
	}
	iVar7 = 0;
	iVar6 = 0;
	if (local_24 < uVar3)
	{
		iVar6 = -1;
	}
	if (uVar3 < local_24)
	{
		iVar6 = 1;
	}
	if ((uint32_t)DStack_20 < (uint32_t)DVar4)
	{
		iVar7 = -1;
	}
	if ((uint32_t)DVar4 < (uint32_t)DStack_20)
	{
		iVar7 = 1;
	}
	pDynamicPath = pUnit->pDynamicPath;
	iVar5 = PATH_GetFootprintCollisionMask(pDynamicPath);
	uVar2 = (uint16_t)iVar5;
	nUnitSize = 1;
	iVar5 = iVar7 + (int)DStack_20;
	nX = iVar6 + local_24;
	pRoom = UNITS_GetRoom(pUnit);
	uVar2 = COLLISION_CheckMaskWithSize(pRoom, nX, iVar5, nUnitSize, uVar2);
	if (uVar2 == 0)
	{
		uStack_1c = (a3 & 0xff) * iVar6 + local_24;
		uStack_14 = 0;
		iStack_18 = (a3 & 0xff) * iVar7 + (int)DStack_20;
		iStack_10 = PATH_GetType(pDynamicPath);
		uStack_c = a5;
		bVar1 = PATH_GetMaxDistance(pDynamicPath);
		uStack_8 = (uint32_t)bVar1;
		sub_6FB42D40(a4, pUnit, &uStack_1c);
		return 1;
	}
	return 0;
}

//D2Client.0x6FB3FA50
void __fastcall sub_6FB3FA50(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint8_t bVar2;
	uint32_t uVar3;
	int local_28;
	int32_t DStack_24;
	uint32_t uStack_1c;
	int iStack_18;
	uint32_t uStack_14;
	int iStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	uVar3 = pUnit->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		local_28 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_28 = 0;
	}
	else
	{
		local_28 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar3 = pUnit->dwUnitType;
	if ((uVar3 == 2) || ((3 < (int)uVar3 && ((int)uVar3 < 6))))
	{
		DStack_24 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_24 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_24 + 2)) = 0;
	}
	else
	{
		DStack_24 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	uVar3 = a2 & 0xff;
	DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
	(*(uint64_t*)&pUnit->pSeed) = DVar1;
	uStack_1c = uVar3;
	if (((uint64_t)DVar1 & 1) != 0)
	{
		uStack_1c = -uVar3;
	}
	DVar1 = (uint64_t)(((uint64_t)DVar1 & 0xffffffff) * 0x6ac690c5 + ((uint64_t)DVar1 >> 0x20));
	(*(uint64_t*)&pUnit->pSeed) = DVar1;
	if (((uint64_t)DVar1 & 1) != 0)
	{
		uVar3 = -uVar3;
	}
	pDynamicPath = pUnit->pDynamicPath;
	uStack_1c = uStack_1c + local_28;
	iStack_18 = uVar3 + (int)DStack_24;
	uStack_14 = 0;
	iStack_10 = PATH_GetType(pDynamicPath);
	uStack_c = a4;
	bVar2 = PATH_GetMaxDistance(pDynamicPath);
	uStack_8 = (uint32_t)bVar2;
	sub_6FB42D40(a3, pUnit, &uStack_1c);
}

//D2Client.0x6FB3FB80
void __fastcall sub_6FB3FB80(D2UnitStrc* pUnit)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t local_1c;
	int32_t DStack_18;

	puVar3 = &local_1c;
	for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		local_1c = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_1c = 0;
	}
	else
	{
		local_1c = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar1 = pUnit->dwUnitType;
	if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
	{
		DStack_18 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
	}
	else
	{
		DStack_18 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
	}
	sub_6FB42D40(7, pUnit, &local_1c);
}

//D2Client.0x6FB3FC10
void __fastcall sub_6FB3FC10(int* a1, int a2)
{
	D2UnitStrc* pDVar1;

	if (199 < a2)
	{
		a2 = 200;
	}
	pDVar1 = sub_6FB40AD0(a1);
	if (pDVar1 != nullptr)
	{
		pDVar1->dwUnitType = a2;
	}
}

//D2Client.0x6FB3FC30
void __fastcall sub_6FB3FC30(D2UnitStrc* pUnit, D2UnitStrc* pUnit3, uint32_t a3)
{
	D2SeedStrc* pDVar1;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar2;
	uint8_t bVar3;
	int* piVar4;
	D2UnitStrc* pUnit2;
	int iVar5;
	uint32_t uVar6;
	int32_t DVar7;
	int iVar8;
	D2UnitStrc** ppDVar9;
	int iStack_28;
	int iStack_24;
	uint32_t uStack_1c;
	int iStack_18;
	uint32_t uStack_14;
	int iStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	if ((pUnit != nullptr) && (pUnit->dwAnimMode == 1))
	{
		piVar4 = (int*)sub_6FB40B30((int*)pUnit);
		if (piVar4 != nullptr)
		{
			pUnit2 = CUNIT_GetPlayer();
			iVar5 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2);
			if ((*piVar4 != 0) && (0x19 < iVar5))
			{
				sub_6FB26C70(pUnit->dwUnitId, 1);
				return;
			}
			*piVar4 = 1;
			pDVar1 = &pUnit->pSeed;
			uVar6 = sub_6FAA88D0(&pDVar1->nLowSeed);
			if ((uVar6 & 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar2;
				iStack_24 = 0x28;
				iStack_28 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x28);
			}
			else
			{
				iStack_28 = 0x28;
				DVar2 = (uint64_t)((uint64_t)pDVar1->nLowSeed * 0x6ac690c5 + (uint64_t)(pUnit->pSeed).nHighSeed);
				*(uint64_t*)pDVar1 = DVar2;
				iStack_24 = (int)(((uint64_t)DVar2 & 0xffffffff) % 0x28);
			}
			uVar6 = sub_6FAA88D0(&pDVar1->nLowSeed);
			if ((uVar6 & 1) != 0)
			{
				iStack_28 = -iStack_28;
			}
			uVar6 = sub_6FAA88D0(&pDVar1->nLowSeed);
			if ((uVar6 & 1) != 0)
			{
				iStack_24 = -iStack_24;
			}
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				iVar5 = pUnit2->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				iVar5 = 0;
			}
			else
			{
				iVar5 = PATH_GetXPosition(pUnit2->pDynamicPath);
			}
			uVar6 = pUnit2->dwUnitType;
			if ((uVar6 == 2) || ((3 < (int)uVar6 && ((int)uVar6 < 6))))
			{
				DVar7 = (*(int32_t*)&pUnit2->pDynamicPath->tTargetCoord);
			}
			else if (pUnit2->pDynamicPath == nullptr)
			{
				(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
				(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
			}
			else
			{
				DVar7 = (int32_t)PATH_GetYPosition(pUnit2->pDynamicPath);
			}
			iVar8 = sub_6FAB6A60((int*)pUnit);
			ppDVar9 = sub_6FAB6A90((int*)pUnit);
			PATH_SetNewDistance(pUnit->pDynamicPath, 0x5a);
			pDynamicPath = pUnit->pDynamicPath;
			uStack_1c = (iVar5 + iStack_28) * 3 + iVar8 * -2;
			iStack_18 = ((int)DVar7 + iStack_24) * 3 + (int)ppDVar9 * -2;
			uStack_14 = 0;
			iStack_10 = PATH_GetType(pDynamicPath);
			uStack_c = 0;
			bVar3 = PATH_GetMaxDistance(pDynamicPath);
			uStack_8 = (uint32_t)bVar3;
			sub_6FB42D40(1, pUnit, &uStack_1c);
		}
	}
}

//D2Client.0x6FB3FE20
void __fastcall sub_6FB3FE20(D2UnitStrc* pUnit, int* a2, uint32_t a3)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int iVar3;
	D2UnitStrc** ppDVar4;
	D2UnitStrc** ppDVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t* puVar8;
	uint32_t local_24;
	uint32_t uStack_1c;
	int32_t DStack_18;

	iVar7 = 0;
	if (pUnit == nullptr)
	{
		local_24 = 0;
	}
	else
	{
		local_24 = pUnit->dwAnimMode;
	}
	iVar3 = MONSTERS_IsDead(pUnit);
	if (iVar3 == 0)
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar7 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath != nullptr)
		{
			iVar7 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		ppDVar4 = sub_6FAB6A90((int*)pUnit);
		iVar3 = sub_6FAB6A60(a2);
		ppDVar5 = sub_6FAB6A90(a2);
		if ((iVar7 == iVar3) && (ppDVar4 == ppDVar5))
		{
			puVar8 = &uStack_1c;
			for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uStack_1c = 0;
			}
			else
			{
				uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			DStack_18 = (int32_t)sub_6FAB6A90((int*)pUnit);
			sub_6FB42D40(8, pUnit, &uStack_1c);
			return;
		}
		if (local_24 == 1)
		{
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			if ((uint32_t)(((uint64_t)DVar2 & 0xffffffff) % 100) < 0x28)
			{
				pDVar6 = sub_6FB40AD0((int*)pUnit);
				if (pDVar6 != nullptr)
				{
					pDVar6->dwUnitType = 0x14;
				}
				puVar8 = &uStack_1c;
				for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					uStack_1c = 0;
				}
				else
				{
					uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DStack_18 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
				}
				else
				{
					DStack_18 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				sub_6FB42D40(7, pUnit, &uStack_1c);
				return;
			}
			sub_6FB3FA50(pUnit, 4, 1, 0);
		}
	}
}

//D2Client.0x6FB3FFE0
void __fastcall sub_6FB3FFE0(D2UnitStrc* pUnit, int* a2, uint32_t a3)
{
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar1;
	uint8_t bVar2;
	int iVar3;
	int iVar4;
	D2UnitStrc** ppDVar5;
	D2ActiveRoomStrc* pRoom;
	int* piVar6;
	D2UnitStrc* pDVar7;
	uint32_t* puVar8;
	D2UnitStrc** local_2c;
	uint32_t* local_28;
	D2ActiveRoomStrc** local_24;
	uint32_t local_20;
	uint32_t local_1c;
	D2UnitStrc** local_18;
	uint32_t uStack_14;
	int iStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;

	if (((pUnit != nullptr) &&
	        (local_24 = (D2ActiveRoomStrc**)pUnit->dwAnimMode,
	            local_24 != (D2ActiveRoomStrc**)((uint8_t*)0x0c))) &&
	    (local_24 != nullptr))
	{
		if (a3 < 2)
		{
			iVar3 = sub_6FAB6A60((int*)pUnit);
			local_2c = sub_6FAB6A90((int*)pUnit);
			iVar4 = sub_6FAB6A60(a2);
			ppDVar5 = sub_6FAB6A90(a2);
			if ((iVar3 == iVar4) && (local_2c == ppDVar5))
			{
				puVar8 = &local_1c;
				for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				local_1c = sub_6FAB6A60((int*)pUnit);
				local_18 = sub_6FAB6A90((int*)pUnit);
				sub_6FB42D40(8, pUnit, &local_1c);
				return;
			}
		}
		if (local_24 == (D2ActiveRoomStrc**)0x1)
		{
			if (a3 < 4)
			{
				sub_6FB3F8A0(pUnit, a2, 6, 1, 0);
				return;
			}
			local_28 = nullptr;
			local_20 = 0;
			if ((7 < a3) && (pRoom = UNITS_GetRoom(pUnit), pRoom != nullptr))
			{
				DUNGEON_GetAdjacentRoomsListFromRoom(pRoom, &local_24, (int*)&local_2c);
				ppDVar5 = nullptr;
				if (local_2c != nullptr)
				{
					do
					{
						for (pDVar7 = local_24[(int)ppDVar5]->pUnitFirst; pDVar7 != nullptr;
						     pDVar7 = pDVar7->pRoomNext)
						{
							iVar3 = sub_6FB402F0(pUnit, pDVar7, (uint32_t*)(&local_28), (int*)(&local_20));
							if (iVar3 != 0)
								goto LAB_6fb40118;
						}
						ppDVar5 = (D2UnitStrc**)((int)ppDVar5 + 1);
					} while (ppDVar5 < local_2c);
				}
			}
		LAB_6fb40118:
			piVar6 = (int*)sub_6FB40B30((int*)pUnit);
			if (piVar6 == nullptr)
			{
				pDVar7 = sub_6FB40AD0((int*)pUnit);
				if (pDVar7 != nullptr)
				{
					pDVar7->dwUnitType = 0x20;
				}
				puVar8 = &local_1c;
				for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				local_1c = sub_6FAB6A60((int*)pUnit);
				local_18 = sub_6FAB6A90((int*)pUnit);
				sub_6FB42D40(7, pUnit, &local_1c);
				return;
			}
			if ((local_28 == nullptr) || (a3 < 8))
			{
				if (*piVar6 == 0)
				{
					DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
					                   (uint64_t)(pUnit->pSeed).nHighSeed);
					(*(uint64_t*)&pUnit->pSeed) = DVar1;
					if (0x4a < (uint32_t)(((uint64_t)DVar1 & 0xffffffff) % 100))
					{
						sub_6FB3FA50(pUnit, 5, 1, 0);
						return;
					}
					pDVar7 = sub_6FB40AD0((int*)pUnit);
					if (pDVar7 != nullptr)
					{
						pDVar7->dwUnitType = 0x1e;
					}
					puVar8 = &local_1c;
					for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
					{
						*puVar8 = 0;
						puVar8 = puVar8 + 1;
					}
					local_1c = sub_6FAB6A60((int*)pUnit);
					local_18 = sub_6FAB6A90((int*)pUnit);
					sub_6FB42D40(7, pUnit, &local_1c);
					return;
				}
			}
			else if (*piVar6 == 0)
			{
				local_1c = *local_28;
				pDynamicPath = pUnit->pDynamicPath;
				local_18 = (D2UnitStrc**)local_28[3];
				uStack_14 = 0;
				iStack_10 = PATH_GetType(pDynamicPath);
				uStack_c = 6;
				bVar2 = PATH_GetMaxDistance(pDynamicPath);
				uStack_8 = (uint32_t)bVar2;
				sub_6FB42D40(0, pUnit, &local_1c);
				*piVar6 = 1;
				return;
			}
			DVar1 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar1;
			if ((uint32_t)(((uint64_t)DVar1 & 0xffffffff) % 100) < 0x14)
			{
				*piVar6 = 0;
			}
			pDVar7 = sub_6FB40AD0((int*)pUnit);
			if (pDVar7 != nullptr)
			{
				pDVar7->dwUnitType = 0x20;
			}
			puVar8 = &local_1c;
			for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			local_1c = sub_6FAB6A60((int*)pUnit);
			local_18 = sub_6FAB6A90((int*)pUnit);
			sub_6FB42D40(7, pUnit, &local_1c);
			return;
		}
	}
}

//D2Client.0x6FB402F0
int __fastcall sub_6FB402F0(D2UnitStrc* pUnit, D2UnitStrc* pUnit3, uint32_t* a3, int* a4)
{
	uint32_t uVar1;
	uint32_t uVar2;
	uint64_t DVar3;
	int iVar4;
	D2UnitStrc* pUnit2;
	int iVar5;

	if (pUnit3 != nullptr)
	{
		uVar1 = pUnit3->dwUnitType;
		if ((uVar1 == 0) || (uVar1 == 1))
		{
			uVar2 = pUnit3->dwAnimMode;
			if (uVar1 == 0)
			{
				if ((uVar2 != 0) && (uVar2 != 0x11))
				{
					return uVar1;
				}
			}
			else if ((uVar2 != 0) && (uVar2 != 0xc))
			{
				return 0;
			}
			iVar4 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit3);
			if ((2 < iVar4) && (iVar4 < 0x1a))
			{
				pUnit2 = CUNIT_GetPlayer();
				iVar5 = UNITS_GetDistanceToOtherUnit(pUnit3, pUnit2);
				if ((7 < iVar5) &&
				    (DVar3 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
				                        (uint64_t)(pUnit->pSeed).nHighSeed),
				        (*(uint64_t*)&pUnit->pSeed) = DVar3,
				        ((uint64_t)DVar3 & 1) != 0))
				{
					*a4 = iVar4;
					*a3 = (uint32_t)(pUnit3);
				}
			}
		}
	}
	return 0;
}

//D2Client.0x6FB40390
void __fastcall sub_6FB40390(D2UnitStrc* pUnit, int* a2, uint32_t a3)
{
	uint32_t uVar1;
	uint64_t DVar2;
	int iVar3;
	D2UnitStrc** ppDVar4;
	int iVar5;
	D2UnitStrc** ppDVar6;
	D2UnitStrc* pDVar7;
	uint32_t* puVar8;
	uint32_t uStack_1c;
	int32_t DStack_18;

	iVar3 = MONSTERS_IsDead(pUnit);
	if (iVar3 == 0)
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar3 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		ppDVar4 = sub_6FAB6A90((int*)pUnit);
		iVar5 = sub_6FAB6A60(a2);
		ppDVar6 = sub_6FAB6A90(a2);
		if ((iVar3 == iVar5) && (ppDVar4 == ppDVar6))
		{
			puVar8 = &uStack_1c;
			for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uStack_1c = 0;
			}
			else
			{
				uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			DStack_18 = (int32_t)sub_6FAB6A90((int*)pUnit);
			sub_6FB42D40(8, pUnit, &uStack_1c);
			return;
		}
		if (pUnit->dwAnimMode == 1)
		{
			if (a3 < 2)
			{
				sub_6FB3F8A0(pUnit, a2, 4, 1, 0);
				return;
			}
			DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pUnit->pSeed).nHighSeed);
			(*(uint64_t*)&pUnit->pSeed) = DVar2;
			if ((uint32_t)(((uint64_t)DVar2 & 0xffffffff) % 100) < 0x4b)
			{
				pDVar7 = sub_6FB40AD0((int*)pUnit);
				if (pDVar7 != nullptr)
				{
					pDVar7->dwUnitType = 0x20;
				}
				puVar8 = &uStack_1c;
				for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1)
				{
					*puVar8 = 0;
					puVar8 = puVar8 + 1;
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					uStack_1c = 0;
				}
				else
				{
					uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
				}
				uVar1 = pUnit->dwUnitType;
				if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
				{
					DStack_18 = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
				}
				else if (pUnit->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DStack_18 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DStack_18 + 2)) = 0;
				}
				else
				{
					DStack_18 = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
				}
				sub_6FB42D40(7, pUnit, &uStack_1c);
				return;
			}
			sub_6FB3FA50(pUnit, 4, 1, 0);
		}
	}
}

//D2Client.0x6FB40560
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB40560(D2UnitStrc* pUnit, D2UnitStrc* pUnit3, uint32_t a3)
{
	uint32_t uVar1;
	D2UnitStrc* pUnit2;
	D2DynamicPathStrc* pDynamicPath;
	uint64_t DVar2;
	uint16_t uVar3;
	int32_t nY;
	int iVar4;
	D2ActiveRoomStrc* pDVar5;
	int iVar6;
	uint32_t extraout_EDX;
	D2UnitStrc* pDVar7;
	uint32_t* puVar8;
	uint32_t uStack_28;
	uint32_t uStack_24;
	D2ActiveRoomStrc** ppDStack_20;
	uint32_t uStack_1c;
	D2UnitStrc** ppDStack_18;

	if ((pUnit != nullptr) && (pUnit->dwAnimMode == 1))
	{
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			nY = (*(int32_t*)&pUnit->pDynamicPath->tTargetCoord);
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&nY + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&nY + 2)) = 0;
		}
		else
		{
			nY = (int32_t)PATH_GetYPosition(pUnit->pDynamicPath);
		}
		uVar1 = pUnit->dwUnitType;
		if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
		{
			iVar4 = pUnit->pDynamicPath->dwClientCoordY;
		}
		else if (pUnit->pDynamicPath == nullptr)
		{
			iVar4 = 0;
		}
		else
		{
			iVar4 = PATH_GetXPosition(pUnit->pDynamicPath);
		}
		uVar3 = 0x1c0;
		pDVar5 = UNITS_GetRoom(pUnit);
		uVar3 = COLLISION_CheckMask(pDVar5, iVar4, (int)nY, uVar3);
		if (uVar3 != 0)
		{
			puVar8 = &uStack_1c;
			for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar8 = 0;
				puVar8 = puVar8 + 1;
			}
			uVar1 = pUnit->dwUnitType;
			if ((uVar1 == 2) || ((3 < (int)uVar1 && ((int)uVar1 < 6))))
			{
				uStack_1c = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				uStack_1c = 0;
			}
			else
			{
				uStack_1c = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			ppDStack_18 = sub_6FAB6A90((int*)pUnit);
			sub_6FB42D40(8, pUnit, &uStack_1c);
			return;
		}
		pDVar7 = nullptr;
		iVar4 = 0x7fffffff;
		pDVar5 = UNITS_GetRoom(pUnit);
		if (pDVar5 != nullptr)
		{
			DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_20, (int*)&uStack_24);
			uStack_28 = 0;
			if (uStack_24 != 0)
			{
				do
				{
					for (pUnit2 = ppDStack_20[uStack_28]->pUnitFirst; pUnit2 != nullptr;
					     pUnit2 = pUnit2->pRoomNext)
					{
						if ((((pUnit != pUnit2) && (pUnit2 != nullptr)) &&
						        ((pUnit2->dwUnitType == 0 ||
						            (((pUnit2->dwUnitType == 1 && (pUnit2->dwClassId != 0x95)) &&
						                (pUnit2->dwClassId != 0x22c)))))) &&
						    ((iVar6 = sub_6FB29550((int*)pUnit), iVar6 == 0 &&
						                                             (iVar6 = UNITS_GetDistanceToOtherUnit(pUnit, pUnit2), iVar6 < iVar4))))
						{
							pDVar7 = pUnit2;
							iVar4 = iVar6;
						}
					}
					uStack_28 = uStack_28 + 1;
				} while (uStack_28 < uStack_24);
				if (pDVar7 != nullptr)
				{
					pDynamicPath = pUnit->pDynamicPath;
					PATH_SetFootprintCollisionMask(pDynamicPath, 0x3c01);
					if (iVar4 < 6)
					{
						PATH_SetFootprintCollisionMask(pDynamicPath, 0xc01);
						iVar4 = sub_6FB3F8A0(pUnit, (int*)pDVar7, 6, 1, 0x78);
						if (iVar4 == 0)
						{
							sub_6FB3FA50(pUnit, CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), 6), 1, 0x78);
							return;
						}
					}
					else
					{
						DVar2 = (uint64_t)((uint64_t)(pUnit->pSeed).nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pUnit->pSeed).nHighSeed);
						(*(uint64_t*)&pUnit->pSeed) = DVar2;
						if ((uint32_t)(((uint64_t)DVar2 & 0xffffffff) % 100) < 0x1e)
						{
							sub_6FB3FA50(pUnit, 2, 1, 0);
							return;
						}
						pDVar7 = sub_6FB40AD0((int*)pUnit);
						if (pDVar7 != nullptr)
						{
							pDVar7->dwUnitType = 5;
						}
					}
				}
			}
		}
	}
}

//D2Client.0x6FB40790
// TODO: decompilation needs review (extraout)
int* __fastcall sub_6FB40790(int* a1, D2UnitStrc* pUnit, uint32_t a3)
{
	uint64_t* puVar1;
	uint64_t uVar2;
	uint64_t uVar3;
	D2UnitStrc* pDVar4;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	D2UnitStrc* extraout_EAX;
	bool bVar8;

	puVar1 = (uint64_t*)(a1 + 8);
	pDVar4 = CUNIT_GetPlayer();
	if (pDVar4 == nullptr)
	{
		pDVar4 = sub_6FB40AD0(a1);
		if (pDVar4 != nullptr)
		{
			pDVar4->dwUnitType = 5;
			return (int*)pDVar4;
		}
	}
	else
	{
		uVar2 = (uint64_t)(uint32_t)*puVar1 * 0x6ac690c5 + (uint64_t)(uint32_t)a1[9];
		*puVar1 = uVar2;
		uVar2 = uVar2 & 0xffffffff;
		pDVar4 = (D2UnitStrc*)(uVar2 / 100);
		if ((uint32_t)(uVar2 % 100) < 5)
		{
			uVar5 = sub_6FAA88D0((uint32_t*)puVar1);
			iVar6 = *a1;
			if ((iVar6 == 2) || ((3 < iVar6 && (iVar6 < 6))))
			{
				iVar6 = *(int*)(a1[0xb] + 0xc);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = PATH_GetXPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			uVar2 = (uint64_t)(uint32_t)*puVar1 * 0x6ac690c5 + (uint64_t)(uint32_t)a1[9];
			*puVar1 = uVar2;
			iVar7 = *a1;
			if ((iVar7 == 2) || ((3 < iVar7 && (iVar7 < 6))))
			{
				iVar7 = *(int*)(a1[0xb] + 0x10);
			}
			else if ((D2DynamicPathStrc*)a1[0xb] == nullptr)
			{
				iVar7 = 0;
			}
			else
			{
				iVar7 = PATH_GetYPosition((D2DynamicPathStrc*)a1[0xb]);
			}
			uVar3 = (uint64_t)(uint32_t)*puVar1 * 0x6ac690c5 + (uint64_t)(uint32_t)a1[9];
			*puVar1 = uVar3;
			pDVar4 = sub_6FB3EAF0((int)a1, (uVar5 & 3) + 0x23a,
			    (int)((uVar2 & 0xffffffff) % 0x3c) + -0x1e + iVar6,
			    (D2UnitStrc**)((int)((uVar3 & 0xffffffff) % 0x3c) + -0x1e + iVar7), 0, 1);
			if (pDVar4 != nullptr)
			{
				uVar5 = sub_6FAA88D0((uint32_t*)puVar1);
				bVar8 = (uVar5 & 1) == 0;
				if (bVar8)
				{
					sub_6FB5FC80((int)pDVar4, 0, 0, 300);
					sub_6FB5FCB0((int)pDVar4, 0, 0, -6, 1);
					sub_6FB5FD50((int)pDVar4, 0, 0, -100, 1);
				}
				else
				{
					sub_6FB5FC80((int)pDVar4, 0, 0, -100);
					sub_6FB5FCB0((int)pDVar4, 0, 0, 6, 1);
					sub_6FB5FD50((int)pDVar4, 0, 0, 300, 1);
				}
				sub_6FB60180((int)pDVar4, (uint32_t)!bVar8);
				sub_6FB5FE00((int*)pDVar4);
				MISSILE_SetTotalFrames(pDVar4, 0x3c);
				MISSILE_SetCurrentFrame(pDVar4, 0x3c);
				MISSILE_SetTargetX(pDVar4, 100);
				MISSILE_SetTargetY(pDVar4, 300);
				pDVar4 = extraout_EAX;
			}
		}
	}
	return (int*)pDVar4;
}

//D2Client.0x6FB40970
uint32_t __fastcall sub_6FB40970(int a1, uint32_t a2)
{
	int iVar1;
	int iVar2;

	if ((((-1 < a1) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a1 < *(int*)(iVar1 + 0xa80))) && (iVar2 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + a1 * 0x1a8), -1 < iVar2)) &&
	    ((iVar2 < *(int*)(iVar1 + 0xa98) &&
	        (iVar1 = *(int*)(iVar1 + 0xa90) + iVar2 * 0x134, iVar1 != 0))))
	{
		return *(uint32_t*)(((uint8_t*)&gdwBitMasks) + (a2 & 7) * 4) &
		       (uint32_t) * (uint8_t*)(((int)a2 >> 3) + 0xf0 + iVar1);
	}
	return 0;
}

//D2Client.0x6FB409E0
uint32_t __fastcall sub_6FB409E0(int a1, int a2)
{
	int iVar1;
	D2MonSoundsTxt* pDVar2;
	int iVar3;
	uint32_t uVar4;

	if ((((a1 != 0) && (iVar1 = *(int*)(a1 + 4), -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8, iVar1 != 0))
	{
		pDVar2 = DATATBLS_GetMonSoundsTxtRecordFromSoundId((int)*(short*)(iVar1 + 0x14));
		if (pDVar2 != nullptr)
		{
			uVar4 = 0;
			iVar3 = 0;
			do
			{
				if (*(short*)(iVar1 + 0x170 + iVar3 * 2) == a2)
				{
					switch (iVar3)
					{
					case 0:
						uVar4 = pDVar2->dwSkill[0];
						break;
					case 1:
						uVar4 = pDVar2->dwSkill[1];
						break;
					case 2:
						uVar4 = pDVar2->dwSkill[2];
						break;
					case 3:
						uVar4 = pDVar2->dwSkill[3];
					}
				}
				iVar3 = iVar3 + 1;
			} while (iVar3 < 8);
			return ((int)uVar4 < 0) - 1 & uVar4;
		}
		return 0;
	}
	return 0;
}

//D2Client.0x6FB40A80
void __fastcall sub_6FB40A80(int* a1, uint16_t a2)
{
	int* piVar1;
	int iVar2;

	if (((a1 != nullptr) && (*a1 == 1)) &&
	    (piVar1 = (int*)a1[5], piVar1 != nullptr))
	{
		*(uint16_t*)(piVar1 + 10) = a2;
		iVar2 = a1[1];
		if ((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80)))
		{
			*piVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar2 * 0x1a8;
			return;
		}
		*piVar1 = 0;
	}
}

//D2Client.0x6FB40AD0
D2UnitStrc* __fastcall sub_6FB40AD0(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return (D2UnitStrc*)(a1[5] + 0x30);
	}
	return nullptr;
}

//D2Client.0x6FB40AF0
uint32_t __fastcall sub_6FB40AF0(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return *(uint32_t*)(a1[5] + 0x3c);
	}
	return 0xffffffff;
}

//D2Client.0x6FB40B10
void __fastcall sub_6FB40B10(int* a1, uint32_t a2)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		*(uint32_t*)(a1[5] + 0x3c) = a2;
	}
}

//D2Client.0x6FB40B30
int __fastcall sub_6FB40B30(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 1)) && (a1[5] != 0))
	{
		return a1[5] + 0x34;
	}
	return 0;
}

//D2Client.0x6FB40B50
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB40B50(D2UnitStrc* pUnit)
{
	int iVar1;
	char cVar2;
	uint8_t uVar3;
	int iVar4;
	D2ActiveRoomStrc* pRoom;
	int iVar5;
	uint32_t extraout_var;
	uint32_t* puVar6;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar7;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t uVar8;
	uint8_t bStack_8;

	if (((pUnit != nullptr) && (pUnit->dwUnitType == 1)) &&
	    (iVar4 = pUnit->dwClassId, -1 < iVar4))
	{
		iVar5 = *(int*)((uint8_t*)&sgptDataTables);
		if (*(int*)(iVar5 + 0xa80) <= iVar4)
		{
			return;
		}
		iVar1 = *(int*)(iVar5 + 0xa78) + iVar4 * 0x1a8;
		if (iVar1 == 0)
		{
			return;
		}
		if (iVar4 < 0)
		{
			return;
		}
		if (*(int*)(iVar5 + 0xa80) <= iVar4)
		{
			return;
		}
		iVar4 = (int)*(short*)(*(int*)(iVar5 + 0xa78) + 0x18 + iVar4 * 0x1a8);
		if (iVar4 < 0)
		{
			return;
		}
		if (*(int*)(iVar5 + 0xa98) <= iVar4)
		{
			return;
		}
		iVar4 = *(int*)(iVar5 + 0xa90) + iVar4 * 0x134;
		if (iVar4 == 0)
		{
			return;
		}
		bStack_8 = MONSTERS_GetMaximalLightRadius(pUnit);
		if (bStack_8 < *(uint8_t*)(iVar4 + 0x11e))
		{
			bStack_8 = *(uint8_t*)(iVar4 + 0x11e);
		}
		pRoom = UNITS_GetRoom(pUnit);
		iVar5 = DUNGEON_GetLevelIdFromRoom(pRoom);
		uVar7 = extraout_ECX;
		uVar8 = extraout_EDX;
		if (iVar5 == 8)
		{
			uVar3 = D2Client_10002(0, 1);
			iVar5 = D2C_ZEXT(uVar3);
			uVar7 = extraout_ECX_00;
			uVar8 = extraout_EDX_00;
			if ((iVar5 != 0) && (uVar7 = pUnit->dwFlags >> 0x15 & 1, uVar7 == 0))
			{
				cVar2 = *(char*)(iVar1 + 0x4c);
				iVar5 = D2C_ZEXT(cVar2);
				if ((cVar2 != '\x01') && (cVar2 != '\x02'))
				{
					bStack_8 = 3;
					goto LAB_6fb40c58;
				}
			}
		}
		if (bStack_8 != 0)
		{
		LAB_6fb40c58:
			puVar6 = sub_6FAA4280(pUnit, 0, (uint32_t)bStack_8, 0xff,
			    D2C_ZEXT(*(uint8_t*)(iVar4 + 0x11f)),
			    CONCAT31((int32_t)((uint32_t)iVar5 >> 8), *(uint8_t*)(iVar4 + 0x120)),
			    CONCAT31((int32_t)((uint32_t)uVar8 >> 8), *(uint8_t*)(iVar4 + 0x121)));
			if (pUnit->dwInteractGUID != 0)
			{
				sub_6FB296E0((int)pUnit);
			}
			pUnit->dwInteractGUID = (uint32_t)puVar6;
			sub_6FB29AB0((int)pUnit, (uint32_t)bStack_8);
			return;
		}
	}
}

//D2Client.0x6FB40CC0
bool __fastcall sub_6FB40CC0(int* a1)
{
	bool bVar1;

	if ((a1 != nullptr) && (*a1 == 1))
	{
		bVar1 = sub_6FB449D0(a1, 4);
		return bVar1;
	}
	return false;
}

//D2Client.0x6FB40CE0
bool __fastcall sub_6FB40CE0(int* a1)
{
	bool bVar1;

	if ((a1 != nullptr) && (*a1 == 1))
	{
		bVar1 = sub_6FB449D0(a1, 0x40);
		return bVar1;
	}
	return false;
}

//D2Client.0x6FB40D00
bool __fastcall sub_6FB40D00(int* a1)
{
	bool bVar1;

	if ((a1 != nullptr) && (*a1 == 1))
	{
		bVar1 = sub_6FB449D0(a1, 8);
		return bVar1;
	}
	return false;
}

//D2Client.0x6FB40D20
bool __fastcall sub_6FB40D20(int* a1)
{
	bool bVar1;

	if ((a1 != nullptr) && (*a1 == 1))
	{
		bVar1 = sub_6FB449D0(a1, 0x10);
		return bVar1;
	}
	return false;
}

//D2Client.0x6FB40D40
bool __fastcall sub_6FB40D40(int* a1)
{
	bool bVar1;

	if ((a1 != nullptr) && (*a1 == 1))
	{
		bVar1 = sub_6FB449D0(a1, 2);
		return bVar1;
	}
	return false;
}

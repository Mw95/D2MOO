#include "UI/Inv.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Engine/GfxUtil.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/Chat.h"
#include "UI/CmdTbl.h"
#include "UI/Hireables.h"
#include "UI/Mods.h"
#include "UI/NpcMenu.h"
#include "UI/Panel.h"
#include "UI/SpellSel.h"
#include "UI/Text.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB6EFD0
uint8_t byte_6FB6EFD0[4] = {1};
//D2Client.0x6FB6EFD4
uint8_t byte_6FB6EFD4[2300] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 6};
//D2Client.0x6FB6F8D0
uint32_t dword_6FB6F8D0 = 0xF;
//D2Client.0x6FB6F8D4
uint32_t dword_6FB6F8D4;
//D2Client.0x6FB6F8D8
uint32_t dword_6FB6F8D8 = 0xEC;
//D2Client.0x6FB6F8DC
uint16_t word_6FB6F8DC[80] = {0xFDA, 0x91, 0, 0, 0, 0xEC, 0, 0xFD9, 0xC8, 0, 0, 0, 0xEC, 0, 0xFDB, 0xF, 0, 0, 0, 0x119, 0, 0xFDC, 0xF, 0, 0, 0, 0x131, 0, 0xFDE, 0xF, 0, 0, 0, 0x149, 0, 0xFDD, 0xF, 0, 0, 0, 0x161, 0, 0xFE0, 0xB4, 0, 0xF5, 0, 0x119, 0, 0xFE7, 0xB4, 0, 0xF5, 0, 0x131, 0, 0xFE8, 0xB4, 0, 0xF5, 0, 0x149, 0, 0xFE9, 0xB4, 0, 0xF5, 0, 0x161, 0, 0xFEA, 0xB4, 0, 0, 0, 0xD6, 0, 0xFE4, 4};
//D2Client.0x6FB6F97C
uint8_t* gpuint8_t_6FB6F97C = nullptr; // TODO: vtable of an abstract class (12 x _purecall)
//D2Client.0x6FB6F9B0
uint8_t* gpuint8_t_6FB6F9B0 = (uint8_t*)sub_6FAEFD00;
//D2Client.0x6FB6F9F0
uint8_t* gpuint8_t_6FB6F9F0 = (uint8_t*)sub_6FAF1100;
//D2Client.0x6FB79288
int32_t dword_6FB79288 = 1;
//D2Client.0x6FB7928C
uint32_t dword_6FB7928C = 1;
//D2Client.0x6FB79290
uint32_t dword_6FB79290 = 0xFFFFFFFF;
//D2Client.0x6FB79294
uint32_t dword_6FB79294 = 0xFFFFFFFF;
//D2Client.0x6FB79298
uint32_t dword_6FB79298 = 0xFFFFFFFF;
//D2Client.0x6FB7929C
uint32_t dword_6FB7929C = 0xFFFFFFFF;
//D2Client.0x6FB792A0
uint32_t dword_6FB792A0 = 0xFFFFFFFF;
//D2Client.0x6FB792A4
uint32_t dword_6FB792A4 = 0xFFFFFFFF;
//D2Client.0x6FB792A8
uint32_t dword_6FB792A8 = 0xFFFFFFFF;
//D2Client.0x6FB792AC
uint32_t tbl_6FB792AC[1];
//D2Client.0x6FB792D8
uint32_t dword_6FB792D8 = 0x1A;
//D2Client.0x6FB792DC
uint16_t word_6FB792DC = 0xFF5;
//D2Client.0x6FB79332
uint8_t tbl_6FB79332[6];
//D2Client.0x6FB79338
uint8_t byte_6FB79338[40] = {0xF8, 0xF, 1, 0, 0, 0, 0xF9, 0xF, 2, 0, 0, 0, 0xFA, 0xF, 3, 0, 0, 0, 0xFB, 0xF, 4, 0, 0, 0, 0xFC, 0xF, 5, 0, 0, 0, 0xFD, 0xF, 6, 0, 0, 0, 0xFE, 0xF};
//D2Client.0x6FB79360
uint8_t byte_6FB79360[360] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 3, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5};
//D2Client.0x6FB794C8
uint8_t byte_6FB794C8[56] = {0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 3};
//D2Client.0x6FB79500
int32_t dword_6FB79500 = 2;
//D2Client.0x6FB79504
int32_t dword_6FB79504 = -2;
//D2Client.0x6FB79508
int32_t dword_6FB79508;
//D2Client.0x6FB7950C
int32_t dword_6FB7950C = -1;
//D2Client.0x6FB79510
int32_t dword_6FB79510 = -1;
//D2Client.0x6FB79514
int32_t dword_6FB79514 = -4;
//D2Client.0x6FB79518
int32_t dword_6FB79518;
//D2Client.0x6FB7951C
int32_t dword_6FB7951C = -1;
//D2Client.0x6FB79520
int32_t dword_6FB79520 = -1;
//D2Client.0x6FB79524
int32_t dword_6FB79524 = -2;
//D2Client.0x6FB79528
int32_t dword_6FB79528;
//D2Client.0x6FB7952C
int32_t dword_6FB7952C = -1;
//D2Client.0x6FB79530
int32_t dword_6FB79530;
//D2Client.0x6FB79534
int32_t dword_6FB79534 = -1;
//D2Client.0x6FB79538
int32_t dword_6FB79538;
//D2Client.0x6FB7953C
int32_t dword_6FB7953C = -1;
//D2Client.0x6FB79540
int32_t dword_6FB79540;
//D2Client.0x6FB79544
int32_t dword_6FB79544 = -2;
//D2Client.0x6FB79548
int32_t dword_6FB79548;
//D2Client.0x6FB7954C
int32_t dword_6FB7954C = -2;
//D2Client.0x6FB79550
int32_t dword_6FB79550 = -5;
//D2Client.0x6FB79554
int32_t dword_6FB79554 = 4;
//D2Client.0x6FB79558
int32_t dword_6FB79558 = -5;
//D2Client.0x6FB7955C
int32_t dword_6FB7955C = 4;
//D2Client.0x6FB7956A
uint32_t dword_6FB7956A;
//D2Client.0x6FB7956E
uint32_t dword_6FB7956E;
//D2Client.0x6FB79580
int32_t dword_6FB79580;
//D2Client.0x6FB79592
int32_t dword_6FB79592;
//D2Client.0x6FB795A4
int32_t dword_6FB795A4;
//D2Client.0x6FB795A8
int32_t dword_6FB795A8 = 4;
//D2Client.0x6FB795AC
int32_t dword_6FB795AC = 3;
//D2Client.0x6FB795B0
int32_t dword_6FB795B0 = 4;
//D2Client.0x6FB795B8
uint8_t byte_6FB795B8[48] = {0x11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA9, 0, 0, 0, 0x11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA9, 0, 0, 0, 0xDD, 0, 0, 0, 0x11, 1};
//D2Client.0x6FB795F8
uint8_t byte_6FB795F8[4];
//D2Client.0x6FB795FC
uint8_t byte_6FB795FC[4] = {0x78};
//D2Client.0x6FB79600
uint8_t byte_6FB79600[4] = {0xFE};
//D2Client.0x6FB79604
uint8_t byte_6FB79604[4];
//D2Client.0x6FB79608
uint8_t byte_6FB79608[228] = {0xD, 0, 0, 0, 0, 0, 0, 0, 0xAF, 0, 0, 0, 0xFE, 0, 0, 0, 0, 0, 0, 0, 0xC, 0, 0, 0, 0, 0, 0, 0, 0x31, 1, 0, 0, 0xFE, 0, 0, 0, 0, 0, 0, 0, 0x1E, 0, 0, 0, 0, 0, 0, 0, 0x9A, 0, 0, 0, 0x1A, 1, 0, 0, 0x30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x9A, 0, 0, 0, 0x32, 1, 0, 0, 0x30, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0x9A, 0, 0, 0, 0x4A, 1, 0, 0, 0x30, 0, 0, 0, 0x15, 0, 0, 0, 0, 0, 0, 0, 0x9A, 0, 0, 0, 0x62, 1, 0, 0, 0x30, 0, 0, 0, 0x1F, 0, 0, 0, 0, 0, 0, 0, 0x35, 1, 0, 0, 0x1A, 1, 0, 0, 0x30, 0, 0, 0, 0x27, 0, 0, 0, 0, 0, 0, 0, 0x35, 1, 0, 0, 0x32, 1, 0, 0, 0x30, 0, 0, 0, 0x2B, 0, 0, 0, 0, 0, 0, 0, 0x35, 1, 0, 0, 0x4A, 1, 0, 0, 0x30, 0, 0, 0, 0x29, 0, 0, 0, 0, 0, 0, 0, 0x35, 1, 0, 0, 0x62, 1, 0, 0, 0x30, 0, 0, 0, 0x2D, 0, 0, 0, 0xD2, 0, 0, 0, 0x31, 1, 0, 0, 0xD7, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF};
//D2Client.0x6FB796FC
uint8_t byte_6FB796FC = 0x29;
//D2Client.0x6FBB36D8
uint8_t byte_6FBB36D8;
//D2Client.0x6FBB36E8
int32_t dword_6FBB36E8;
//D2Client.0x6FBB36EC
int32_t dword_6FBB36EC;
//D2Client.0x6FBB36F0
int32_t dword_6FBB36F0;
//D2Client.0x6FBB36F4
int32_t dword_6FBB36F4;
//D2Client.0x6FBB36F8
uint8_t byte_6FBB36F8;
//D2Client.0x6FBB370C
uint32_t dword_6FBB370C;
//D2Client.0x6FBB3710
uint8_t byte_6FBB3710;
//D2Client.0x6FBB3714
int32_t dword_6FBB3714;
//D2Client.0x6FBB3718
int32_t dword_6FBB3718;
//D2Client.0x6FBB371C
int32_t dword_6FBB371C;
//D2Client.0x6FBB3720
int32_t dword_6FBB3720;
//D2Client.0x6FBB3724
uint32_t dword_6FBB3724;
//D2Client.0x6FBB3728
uint8_t byte_6FBB3728;
//D2Client.0x6FBB372C
int32_t dword_6FBB372C;
//D2Client.0x6FBB3730
int32_t dword_6FBB3730;
//D2Client.0x6FBB3734
int32_t dword_6FBB3734;
//D2Client.0x6FBB3738
int32_t dword_6FBB3738;
//D2Client.0x6FBB373C
uint32_t dword_6FBB373C;
//D2Client.0x6FBB3740
uint8_t byte_6FBB3740;
//D2Client.0x6FBB3750
int32_t dword_6FBB3750;
//D2Client.0x6FBB3754
int32_t dword_6FBB3754;
//D2Client.0x6FBB375C
int32_t dword_6FBB375C;
//D2Client.0x6FBB3760
uint8_t byte_6FBB3760;
//D2Client.0x6FBB3764
int32_t dword_6FBB3764;
//D2Client.0x6FBB3768
int32_t dword_6FBB3768;
//D2Client.0x6FBB376C
int32_t dword_6FBB376C;
//D2Client.0x6FBB3770
int32_t dword_6FBB3770;
//D2Client.0x6FBB3774
uint32_t dword_6FBB3774;
//D2Client.0x6FBB3778
uint8_t byte_6FBB3778;
//D2Client.0x6FBB3779
uint8_t byte_6FBB3779;
//D2Client.0x6FBB3780
uint8_t byte_6FBB3780;
//D2Client.0x6FBB3790
uint8_t byte_6FBB3790;
//D2Client.0x6FBB3794
int32_t dword_6FBB3794;
//D2Client.0x6FBB3798
int32_t dword_6FBB3798;
//D2Client.0x6FBB37A0
int32_t dword_6FBB37A0;
//D2Client.0x6FBB37A8
uint32_t dword_6FBB37A8;
//D2Client.0x6FBB37AC
uint32_t dword_6FBB37AC;
//D2Client.0x6FBB37B0
uint16_t word_6FBB37B0;
//D2Client.0x6FBB37B2
uint32_t dword_6FBB37B2;
//D2Client.0x6FBB37B6
uint16_t word_6FBB37B6;
//D2Client.0x6FBB37B8
uint32_t dword_6FBB37B8;
//D2Client.0x6FBB37BC
uint32_t dword_6FBB37BC;
//D2Client.0x6FBB37C4
uint8_t byte_6FBB37C4;
//D2Client.0x6FBB37C6
uint8_t byte_6FBB37C6;
//D2Client.0x6FBB37CA
uint16_t word_6FBB37CA;
//D2Client.0x6FBB37CC
uint8_t byte_6FBB37CC;
//D2Client.0x6FBB37D0
uint8_t byte_6FBB37D0;
//D2Client.0x6FBB37D8
uint8_t byte_6FBB37D8;
//D2Client.0x6FBB37DA
uint8_t byte_6FBB37DA;
//D2Client.0x6FBB37DE
uint8_t byte_6FBB37DE;
//D2Client.0x6FBB37E0
uint8_t byte_6FBB37E0;
//D2Client.0x6FBB37E4
uint8_t byte_6FBB37E4;
//D2Client.0x6FBB37EC
uint8_t byte_6FBB37EC;
//D2Client.0x6FBB37EE
uint8_t byte_6FBB37EE;
//D2Client.0x6FBB37F2
uint8_t byte_6FBB37F2;
//D2Client.0x6FBB37F8
uint8_t byte_6FBB37F8;
//D2Client.0x6FBB37FC
int32_t dword_6FBB37FC;
//D2Client.0x6FBB3800
int32_t dword_6FBB3800;
//D2Client.0x6FBB3804
int32_t dword_6FBB3804;
//D2Client.0x6FBB3808
int32_t dword_6FBB3808;
//D2Client.0x6FBB3810
uint8_t byte_6FBB3810;
//D2Client.0x6FBB3820
uint8_t byte_6FBB3820;
//D2Client.0x6FBB3838
uint8_t byte_6FBB3838;
//D2Client.0x6FBB383C
int32_t dword_6FBB383C;
//D2Client.0x6FBB3840
int32_t dword_6FBB3840;
//D2Client.0x6FBB3844
int32_t dword_6FBB3844;
//D2Client.0x6FBB3848
int32_t dword_6FBB3848;
//D2Client.0x6FBB3850
int32_t dword_6FBB3850;
//D2Client.0x6FBB3854
int32_t dword_6FBB3854;
//D2Client.0x6FBB385C
int32_t dword_6FBB385C;
//D2Client.0x6FBB3860
uint8_t byte_6FBB3860;
//D2Client.0x6FBB3870
uint8_t byte_6FBB3870;
//D2Client.0x6FBB3874
uint8_t byte_6FBB3874;
//D2Client.0x6FBB388C
uint32_t dword_6FBB388C;
//D2Client.0x6FBB3890
D2CellFileStrc* gpCellFile_6FBB3890;
//D2Client.0x6FBB3894
uint32_t dword_6FBB3894;
//D2Client.0x6FBB3898
uint8_t byte_6FBB3898;
//D2Client.0x6FBB389C
int32_t dword_6FBB389C;
//D2Client.0x6FBB38A0
int32_t dword_6FBB38A0;
//D2Client.0x6FBB38A4
int32_t dword_6FBB38A4;
//D2Client.0x6FBB38A8
int32_t dword_6FBB38A8;
//D2Client.0x6FBB38B0
uint8_t byte_6FBB38B0;
//D2Client.0x6FBB38B4
int32_t dword_6FBB38B4;
//D2Client.0x6FBB38B8
int32_t dword_6FBB38B8;
//D2Client.0x6FBB38BC
int32_t dword_6FBB38BC;
//D2Client.0x6FBB38C0
int32_t dword_6FBB38C0;
//D2Client.0x6FBB38C8
int32_t dword_6FBB38C8;
//D2Client.0x6FBB38CC
int32_t dword_6FBB38CC;
//D2Client.0x6FBB38D0
int32_t dword_6FBB38D0;
//D2Client.0x6FBB38D4
int32_t dword_6FBB38D4;
//D2Client.0x6FBB38D8
uint8_t byte_6FBB38D8;
//D2Client.0x6FBB58D8
int32_t dword_6FBB58D8;
//D2Client.0x6FBB58DC
int32_t dword_6FBB58DC;
//D2Client.0x6FBB58E0
uint32_t dword_6FBB58E0;
//D2Client.0x6FBB58E4
uint32_t dword_6FBB58E4;
//D2Client.0x6FBB58E8
uint32_t dword_6FBB58E8;
//D2Client.0x6FBB58EC
int32_t dword_6FBB58EC;
//D2Client.0x6FBB58F0
D2UnitStrc* gpUnit_6FBB58F0;
//D2Client.0x6FBB58F4
uint32_t dword_6FBB58F4;
//D2Client.0x6FBB5900
uint8_t byte_6FBB5900;
//D2Client.0x6FBB5901
uint32_t dword_6FBB5901;
//D2Client.0x6FBB5904
int32_t dword_6FBB5904;
//D2Client.0x6FBB5908
uint8_t byte_6FBB5908;
//D2Client.0x6FBB590C
uint32_t dword_6FBB590C;
//D2Client.0x6FBB5910
uint32_t dword_6FBB5910;
//D2Client.0x6FBB5914
uint32_t dword_6FBB5914;
//D2Client.0x6FBB5918
DWORD dword_6FBB5918;
//D2Client.0x6FBB591C
D2CellFileStrc* gpCellFile_6FBB591C;
//D2Client.0x6FBB5920
int32_t dword_6FBB5920;
//D2Client.0x6FBB5924
D2CellFileStrc* gpCellFile_6FBB5924;
//D2Client.0x6FBB5928
D2CellFileStrc* gpCellFile_6FBB5928;
//D2Client.0x6FBB592C
D2CellFileStrc* gpCellFile_6FBB592C;
//D2Client.0x6FBB5930
D2CellFileStrc* gpCellFile_6FBB5930;
//D2Client.0x6FBB5934
D2CellFileStrc* gpCellFile_6FBB5934;
//D2Client.0x6FBB5938
D2CellFileStrc* gpCellFile_6FBB5938;
//D2Client.0x6FBB593C
D2CellFileStrc* gpCellFile_6FBB593C;
//D2Client.0x6FBB5940
int32_t dword_6FBB5940;
//D2Client.0x6FBB5944
uint32_t dword_6FBB5944;
//D2Client.0x6FBB5948
uint32_t dword_6FBB5948;
//D2Client.0x6FBB594C
uint32_t dword_6FBB594C;
//D2Client.0x6FBB5950
int32_t dword_6FBB5950;
//D2Client.0x6FBB5954
int32_t dword_6FBB5954;
//D2Client.0x6FBB5958
uint32_t dword_6FBB5958;
//D2Client.0x6FBB595C
uint32_t dword_6FBB595C;
//D2Client.0x6FBB5960
uint32_t dword_6FBB5960;
//D2Client.0x6FBB5964
uint32_t dword_6FBB5964;
//D2Client.0x6FBB5968
uint8_t byte_6FBB5968;
//D2Client.0x6FBB5969
uint8_t byte_6FBB5969[3];
//D2Client.0x6FBB596C
int32_t dword_6FBB596C;
//D2Client.0x6FBB5978
int32_t dword_6FBB5978;
//D2Client.0x6FBB5980
int32_t dword_6FBB5980;
//D2Client.0x6FBB598C
int32_t dword_6FBB598C;
//D2Client.0x6FBB5994
int32_t dword_6FBB5994;
//D2Client.0x6FBB59A0
int32_t dword_6FBB59A0;
//D2Client.0x6FBB59A8
int32_t dword_6FBB59A8;
//D2Client.0x6FBB59AC
int32_t dword_6FBB59AC;
//D2Client.0x6FBB59B0
int32_t dword_6FBB59B0;
//D2Client.0x6FBB59B4
int32_t dword_6FBB59B4;
//D2Client.0x6FBB59B8
uint32_t dword_6FBB59B8;
//D2Client.0x6FBB59BC
int32_t dword_6FBB59BC;
//D2Client.0x6FBB59C0
int32_t dword_6FBB59C0;
//D2Client.0x6FBB59C4
int32_t dword_6FBB59C4;
//D2Client.0x6FBB59C8
int32_t dword_6FBB59C8;
//D2Client.0x6FBB59CC
uint32_t dword_6FBB59CC;
//D2Client.0x6FBB59D0
int32_t dword_6FBB59D0;
//D2Client.0x6FBB59DC
int32_t dword_6FBB59DC;
//D2Client.0x6FBB59E4
int32_t dword_6FBB59E4;
//D2Client.0x6FBB59F0
int32_t dword_6FBB59F0;
//D2Client.0x6FBB59F8
int32_t dword_6FBB59F8;
//D2Client.0x6FBB5A04
int32_t dword_6FBB5A04;
//D2Client.0x6FBB5A0C
int32_t dword_6FBB5A0C;
//D2Client.0x6FBB5A18
int32_t dword_6FBB5A18;
//D2Client.0x6FBB5A20
int32_t dword_6FBB5A20;
//D2Client.0x6FBB5A2C
int32_t dword_6FBB5A2C;
//D2Client.0x6FBB5A37
uint8_t tbl_6FBB5A37[1];
//D2Client.0x6FBB5A38
uint32_t dword_6FBB5A38;
//D2Client.0x6FBB5A3C
uint32_t dword_6FBB5A3C;
//D2Client.0x6FBB5A49
uint8_t byte_6FBB5A49;
//D2Client.0x6FBB5A4C
int32_t dword_6FBB5A4C;
//D2Client.0x6FBB5A58
int32_t dword_6FBB5A58;
//D2Client.0x6FBB5A60
uint8_t byte_6FBB5A60;
//D2Client.0x6FBB5A74
int32_t dword_6FBB5A74;
//D2Client.0x6FBB5A80
int32_t dword_6FBB5A80;
//D2Client.0x6FBB5A88
int32_t dword_6FBB5A88;
//D2Client.0x6FBB5A94
int32_t dword_6FBB5A94;
//D2Client.0x6FBB5A9C
int32_t dword_6FBB5A9C;
//D2Client.0x6FBB5AA8
int32_t dword_6FBB5AA8;
//D2Client.0x6FBB5AB0
uint8_t byte_6FBB5AB0;
//D2Client.0x6FBB5AC4
uint8_t byte_6FBB5AC4;
//D2Client.0x6FBB5AD8
uint8_t byte_6FBB5AD8;
//D2Client.0x6FBB5AEC
uint8_t byte_6FBB5AEC;
//D2Client.0x6FBB5B00
uint8_t byte_6FBB5B00;
//D2Client.0x6FBB5B14
int32_t dword_6FBB5B14;
//D2Client.0x6FBB5B18
int32_t dword_6FBB5B18;
//D2Client.0x6FBB5B1C
int32_t dword_6FBB5B1C;
//D2Client.0x6FBB5B20
int32_t dword_6FBB5B20;
//D2Client.0x6FBB5B24
uint32_t dword_6FBB5B24;
//D2Client.0x6FBB5B25
uint8_t tbl_6FBB5B25[3];
//D2Client.0x6FBB5B28
uint32_t dword_6FBB5B28;
//D2Client.0x6FBB5B2C
uint32_t dword_6FBB5B2C;
//D2Client.0x6FBB5B30
uint32_t dword_6FBB5B30;
//D2Client.0x6FBB5B34
int32_t dword_6FBB5B34;
//D2Client.0x6FBB5B38
uint32_t dword_6FBB5B38;
//D2Client.0x6FBB5B3C
uint32_t dword_6FBB5B3C;
//D2Client.0x6FBB5B40
uint32_t dword_6FBB5B40;
//D2Client.0x6FBB5B44
uint32_t dword_6FBB5B44;
//D2Client.0x6FBB5B48
uint32_t dword_6FBB5B48;
//D2Client.0x6FBB5B4C
uint32_t dword_6FBB5B4C;
//D2Client.0x6FBB5B50
uint32_t dword_6FBB5B50;
//D2Client.0x6FBB5B54
uint32_t dword_6FBB5B54;
//D2Client.0x6FBB5B70
D2CellFileStrc* gpCellFile_6FBB5B70;
//D2Client.0x6FBB5B74
D2CellFileStrc* gpCellFile_6FBB5B74;
//D2Client.0x6FBB5B78
D2CellFileStrc* gpCellFile_6FBB5B78;
//D2Client.0x6FBB5B7C
D2CellFileStrc* gpCellFile_6FBB5B7C;
//D2Client.0x6FBB5B80
D2CellFileStrc* gpCellFile_6FBB5B80;
//D2Client.0x6FBB5B84
D2CellFileStrc* gpCellFile_6FBB5B84;
//D2Client.0x6FBB5B88
D2CellFileStrc* gpCellFile_6FBB5B88;
//D2Client.0x6FBB5B8C
D2CellFileStrc* gpCellFile_6FBB5B8C;
//D2Client.0x6FBB5B90
D2CellFileStrc* gpCellFile_6FBB5B90;
//D2Client.0x6FBB5B94
D2CellFileStrc* gpCellFile_6FBB5B94;
//D2Client.0x6FBB5B98
uint32_t dword_6FBB5B98;
//D2Client.0x6FBB5B9C
uint8_t byte_6FBB5B9C;
//D2Client.0x6FBB5BA8
uint32_t dword_6FBB5BA8;
//D2Client.0x6FBB5BAC
int32_t dword_6FBB5BAC;
//D2Client.0x6FBB5BB0
char* gpchar_6FBB5BB0;
//D2Client.0x6FBB5BB4
D2CellFileStrc* gpCellFile_6FBB5BB4;
//D2Client.0x6FBB5BB8
D2CellFileStrc* gpCellFile_6FBB5BB8;
//D2Client.0x6FBB5BBC
int32_t dword_6FBB5BBC;
//D2Client.0x6FBB5BC0
int32_t dword_6FBB5BC0;
//D2Client.0x6FBB5BC4
D2CellFileStrc* gpCellFile_6FBB5BC4;
//D2Client.0x6FBBA748
int32_t dword_6FBBA748;
//D2Client.0x6FBBA74C
int32_t dword_6FBBA74C;

//D2Client.0x6FADD360
// TODO: decompilation needs review (in_stack, stack0x, unaff_)
void __cdecl sub_6FADD360(uint32_t a12)
{
	uint8_t stack0x00000014[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000001c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000030[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000044[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000007e[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000084[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000086[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000484[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000486[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000614[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000a14[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000e14[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001214[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001614[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001a14[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001e14[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	char cVar1;
	D2InventoryStrc* pInventory;
	uint8_t bVar2;
	uint16_t uVar3;
	D2ItemsTxt* pDVar4;
	uint32_t uVar5;
	int iVar6;
	Unicode* pUVar7;
	D2RareAffixTxt* pDVar8;
	D2LowQualityItemsTxt* pDVar9;
	char* pcVar10;
	D2RareAffixTxt* pDVar11;
	Unicode* pUVar12;
	Unicode* pUVar13;
	D2MagicAffixTxt* pDVar14;
	D2MagicAffixTxt* pDVar15;
	char* pcVar16;
	D2C_Language DVar17;
	short sVar18;
	D2UnitStrc* pItem;
	uint32_t uVar19;
	Unicode* a1;
	D2UnitStrc* pDVar20;
	code* pcVar21;
	uint32_t unaff_EDI;
	int iVar22;
	uint32_t* puVar23;
	char* pcVar24;
	D2MagicAffixTxt* pDVar25;
	D2UnitStrc* pDStack00000008;
	D2RareAffixTxt* pDStack0000000c;
	Unicode* pUStack00000010;
	char in_stack_0000001c;
	uint32_t in_stack_0000001d;
	uint32_t in_stack_00000021;
	uint32_t in_stack_00000025;
	uint32_t in_stack_00000029;
	uint8_t in_stack_0000002d;
	int in_stack_00002218;
	uint16_t uVar26;

	if (pItem == nullptr)
	{
		return;
	}
	pUVar7 = (Unicode*)stack0x00001614;
	iVar22 = 0x200;
	pDStack00000008 = pItem;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar22 = iVar22 + -1;
	} while (iVar22 != 0);
	pUVar7 = (Unicode*)stack0x00001214;
	iVar22 = 0x200;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar22 = iVar22 + -1;
	} while (iVar22 != 0);
	pUVar7 = (Unicode*)stack0x00001a14;
	iVar22 = 0x200;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar22 = iVar22 + -1;
	} while (iVar22 != 0);
	pDStack0000000c = (D2RareAffixTxt*)D2LANG_GetStringFromTblIndex(0xf9b);
	pUStack00000010 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	iVar22 = 0;
	pDVar4 = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
	D2_ASSERT(pDVar4 != nullptr);
	uVar5 = ITEMS_GetItemType(pItem);
	iVar6 = ITEMS_CheckItemFlag(pItem, 0x4000000, __LINE__, __FILE__);
	if (iVar6 != 0)
	{
		pUVar7 = (Unicode*)stack0x00000084;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
		for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084); 0 < iVar22; iVar22 = iVar22 + -1)
		{
			if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
				goto LAB_6fadd4ac;
		}
		if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
		{
		LAB_6fadd4ac:
			if ((iVar22 < 3) ||
			    (pUVar7 = (Unicode*)(stack0x00000086 + iVar22 * 2),
			        *(short*)(stack0x0000007e + iVar22 * 2) != 0x5b))
				goto LAB_6fadd4c3;
		}
		else
		{
		LAB_6fadd4c3:
			pUVar7 = (Unicode*)stack0x00000084;
		}
		Unicode::strcpy((Unicode*)stack0x00001614, pUVar7);
		pcVar21 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat((Unicode*)stack0x00001614, pUStack00000010);
		uVar3 = ITEMS_GetPrefixId(pItem, 0);
		pDVar8 = (D2RareAffixTxt*)D2LANG_GetStringFromTblIndex(uVar3);
		if (pDVar8 == nullptr)
		{
			pDVar8 = pDStack0000000c;
		}
		Unicode::strcpy((Unicode*)stack0x00001214, (Unicode*)pDVar8);
		Unicode::strcat((Unicode*)stack0x00001a14, (Unicode*)stack0x00001214);
		sub_6FB20430((short*)stack0x00001a14, '\x04');
		Unicode::strcat(a1, (Unicode*)stack0x00001614);
		goto LAB_6fade702;
	}
	iVar6 = ITEMS_CheckItemFlag(pItem, 0x10, __LINE__, __FILE__);
	if (iVar6 == 0)
	{
		pUVar7 = (Unicode*)stack0x00000084;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		pcVar21 = (code*)(((uint8_t*)&Unicode::strcpy));
		Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
		for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084);
		     (0 < iVar22 && (*(short*)(stack0x00000084 + iVar22 * 2) != 0x5d)); iVar22 = iVar22 + -1)
		{
		}
		goto LAB_6fade702;
	}
	iVar6 = ITEMS_GetItemQuality(pItem);
	pDVar20 = pDStack00000008;
	switch (iVar6)
	{
	case 1:
		iVar22 = ITEMS_GetFileIndex(pItem);
		pDVar9 = DATATBLS_GetLowQualityItemsTxtRecord(iVar22);
		if (pDVar9 != nullptr)
		{
			uVar26 = 0;
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
			pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar9->wTblId));
			pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6b0));
			sub_6FADCFE0(a1, (char*)pUVar12, pUVar13, pUVar7, uVar26);
		}
		break;
	case 2:
		iVar22 = ITEMS_CheckItemTypeId(pItem, 0x16);
		if ((iVar22 != 0) || (iVar22 = ITEMS_CheckItemTypeId(pItem, 0x12), iVar22 != 0))
		{
			uVar3 = ITEMS_GetSuffixId(pItem, 0);
			if (uVar3 == 0)
			{
				sVar18 = 0x897;
				if (uVar5 != 0x12)
				{
					sVar18 = 0x898;
				}
			}
			else
			{
				if (uVar3 != 1)
					break;
				sVar18 = 0x899;
				if (uVar5 != 0x12)
				{
					sVar18 = 0x89a;
				}
			}
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar18));
			Unicode::strcpy(a1, pUVar7);
			break;
		}
		iVar22 = ITEMS_CheckItemTypeId(pItem, 7);
		if (iVar22 == 0)
		{
			iVar22 = ITEMS_CheckItemTypeId(pItem, 0x28);
			if (iVar22 != 0)
			{
				iVar22 = ITEMS_GetFileIndex(pItem);
				if ((iVar22 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar22))
				{
					iVar22 = 0;
				}
				else
				{
					iVar22 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar22 * 0x1a8;
				}
				uVar26 = 0;
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
				pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar22 + 6)));
				sVar18 = 0x6b4;
				goto LAB_6fadda39;
			}
			pInventory = pItem->pInventory;
			iVar22 = ITEMS_CheckItemFlag(pItem, 0x800, __LINE__, __FILE__);
			if (((iVar22 != 0) && (pInventory != nullptr)) &&
			    (iVar22 = INVENTORY_GetItemCount(pInventory), iVar22 != 0))
			{
				uVar26 = 0;
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
				pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6c0));
				pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6b3));
				sub_6FADCFE0(a1, (char*)pUVar12, pUVar13, pUVar7, uVar26);
				break;
			}
			pUVar7 = (Unicode*)stack0x00000084;
			iVar22 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
			pcVar21 = (code*)(((uint8_t*)&Unicode::strcpy));
			Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
			for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084);
			     (0 < iVar22 && (*(short*)(stack0x00000084 + iVar22 * 2) != 0x5d)); iVar22 = iVar22 + -1)
			{
			}
		}
		else
		{
			in_stack_0000001c = '\0';
			in_stack_0000001d = 0;
			pUVar7 = (Unicode*)stack0x00000614;
			in_stack_00000021 = 0;
			iVar22 = 0x100;
			in_stack_00000025 = 0;
			in_stack_00000029 = 0;
			in_stack_0000002d = 0;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)stack0x00000014;
			iVar22 = 3;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			ITEMS_GetEarLevel(pItem);
			SStrPrintf((char*)(stack0x0000001c), 3, "%d");
			Unicode::win2Unicode((Unicode*)stack0x00000014, (const char*)(stack0x0000001c), 3);
			pUVar7 = (Unicode*)stack0x00000084;
			iVar22 = 0x100;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pcVar10 = ITEMS_GetEarName(pItem);
			pcVar16 = (char*)(stack0x00000030);
			do
			{
				cVar1 = *pcVar10;
				pcVar10 = pcVar10 + 1;
				*pcVar16 = cVar1;
				pcVar16 = pcVar16 + 1;
			} while (cVar1 != '\0');
			Unicode::win2Unicode((Unicode*)stack0x00000614, (const char*)(stack0x00000030), 0x100);
			iVar22 = ITEMS_CheckItemFlag(pItem, 0x8000, __LINE__, __FILE__);
			if (iVar22 == 0)
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x102d));
				Unicode::strcpy(a1, pUVar7);
				pcVar21 = (code*)(((uint8_t*)&Unicode::strcat));
			}
			else
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1406));
				Unicode::strcpy(a1, pUVar7);
				pcVar21 = (code*)(((uint8_t*)&Unicode::strcat));
				Unicode::strcat(a1, pUStack00000010);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x102d));
				Unicode::strcat(a1, pUVar7);
			}
			(*pcVar21)();
			(*pcVar21)();
			(*pcVar21)();
			uVar5 = ITEMS_GetFileIndex(pItem);
			D2_ASSERT(6 >= uVar5);
			switch (uVar5)
			{
			case 0:
				D2LANG_GetStringFromTblIndex(0xfab);
				break;
			case 1:
				D2LANG_GetStringFromTblIndex(0xfaa);
				break;
			case 2:
				D2LANG_GetStringFromTblIndex(0xfa9);
				break;
			case 3:
				D2LANG_GetStringFromTblIndex(0xfa8);
				break;
			case 4:
				D2LANG_GetStringFromTblIndex(0xfa7);
				break;
			case 5:
				D2LANG_GetStringFromTblIndex(0x2771);
				break;
			case 6:
				D2LANG_GetStringFromTblIndex(0x2772);
			}
			(*pcVar21)();
			(*pcVar21)();
			puVar23 = (uint32_t*)stack0x00000486;
			for (iVar22 = 0x31; iVar22 != 0; iVar22 = iVar22 + -1)
			{
				*puVar23 = 0;
				puVar23 = puVar23 + 1;
			}
			*(uint16_t*)puVar23 = 0;
			pUVar7 = (Unicode*)stack0x00000486;
			iVar22 = 99;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)stack0x00000a14;
			iVar22 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
			Unicode::strcpy((Unicode*)stack0x00000a14, pUVar7);
			DVar17 = STRTABLE_GetLanguage();
			Unicode::Personalize((Unicode*)stack0x00000484, (Unicode*)stack0x00000614, (Unicode*)stack0x00000a14, 100, (ELANGUAGE)(DVar17));
		}
		goto LAB_6fade702;
	case 3:
		uVar26 = 0;
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6bf));
		sVar18 = 0x6af;
	LAB_6fadda39:
		pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar18));
		sub_6FADCFE0(a1, (char*)pUVar12, pUVar13, pUVar7, uVar26);
		break;
	case 4:
		uVar3 = ITEMS_GetPrefixId(pDStack00000008, 0);
		pDVar14 = DATATBLS_GetMagicAffixTxtRecord((uint32_t)uVar3);
		uVar3 = ITEMS_GetSuffixId(pDVar20, 0);
		pDVar15 = DATATBLS_GetMagicAffixTxtRecord((uint32_t)uVar3);
		iVar6 = 0;
		if (pDVar14 != nullptr)
		{
			if (pDVar14->wTblIndex == 0)
			{
				do
				{
					cVar1 = ("(")[iVar6];
					(stack0x00000614)[iVar6] = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				do
				{
					pDVar25 = pDVar14;
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					pDVar25 = (D2MagicAffixTxt*)(pDVar14->szName + 1);
					pcVar16 = pDVar14->szName;
					pDVar14 = pDVar25;
				} while (*pcVar16 != '\0');
				uVar5 = ~uVar5;
				iVar22 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar22 == 0)
						break;
					iVar22 = iVar22 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				pcVar16 = (char*)((int)pDVar25 - uVar5);
				pcVar10 = pcVar10 + -1;
				for (uVar19 = uVar5 >> 2; uVar19 != 0; uVar19 = uVar19 - 1)
				{
					*(uint32_t*)pcVar10 = *(uint32_t*)pcVar16;
					pcVar16 = pcVar16 + 4;
					pcVar10 = pcVar10 + 4;
				}
				for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
				{
					*pcVar10 = *pcVar16;
					pcVar16 = pcVar16 + 1;
					pcVar10 = pcVar10 + 1;
				}
				iVar22 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar22 == 0)
						break;
					iVar22 = iVar22 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				*(uint16_t*)(pcVar10 + -1) = byte_6FB796FC;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar16 + 1;
				} while (cVar1 != '\0');
				iVar22 = ~uVar5 - 1;
				Unicode::toUnicode((Unicode*)stack0x00001614, (const char*)(stack0x00000614), 0x200);
			}
			else
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar14->wTblIndex));
				iVar22 = Unicode::strlen(pUVar7);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar14->wTblIndex));
				Unicode::strcpy((Unicode*)stack0x00001614, pUVar7);
			}
		}
		if (pDVar15 != nullptr)
		{
			if (pDVar15->wTblIndex == 0)
			{
				pUVar7 = (Unicode*)stack0x00000e14;
				iVar6 = 0x200;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar6 = iVar6 + -1;
				} while (iVar6 != 0);
				iVar6 = 0;
				do
				{
					cVar1 = ("(")[iVar6];
					(stack0x00000614)[iVar6] = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				do
				{
					pDVar14 = pDVar15;
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					pDVar14 = (D2MagicAffixTxt*)(pDVar15->szName + 1);
					pcVar16 = pDVar15->szName;
					pDVar15 = pDVar14;
				} while (*pcVar16 != '\0');
				uVar5 = ~uVar5;
				iVar6 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				pcVar16 = (char*)((int)pDVar14 - uVar5);
				pcVar10 = pcVar10 + -1;
				for (uVar19 = uVar5 >> 2; uVar19 != 0; uVar19 = uVar19 - 1)
				{
					*(uint32_t*)pcVar10 = *(uint32_t*)pcVar16;
					pcVar16 = pcVar16 + 4;
					pcVar10 = pcVar10 + 4;
				}
				for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
				{
					*pcVar10 = *pcVar16;
					pcVar16 = pcVar16 + 1;
					pcVar10 = pcVar10 + 1;
				}
				iVar6 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				*(uint16_t*)(pcVar10 + -1) = byte_6FB796FC;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar16 + 1;
				} while (cVar1 != '\0');
				iVar22 = iVar22 + (~uVar5 - 1);
				Unicode::toUnicode((Unicode*)stack0x00000e14, (const char*)(stack0x00000614), 0x200);
				Unicode::strcat((Unicode*)stack0x00001214, (Unicode*)stack0x00000e14);
			}
			else
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar15->wTblIndex));
				iVar6 = Unicode::strlen(pUVar7);
				iVar22 = iVar22 + iVar6;
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar15->wTblIndex));
				Unicode::strcat((Unicode*)stack0x00001214, pUVar7);
			}
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		iVar6 = Unicode::strlen(pUVar7);
		D2_ASSERT(in_stack_00002218 > iVar22 + 3 + iVar6);
		uVar26 = SUB42(stack0x00001214, 0);
		pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		pUVar7 = (Unicode*)stack0x00001614;
		pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6b2));
		sub_6FADCFE0(a1, (char*)pUVar12, pUVar7, pUVar13, uVar26);
		break;
	case 5:
		iVar22 = ITEMS_GetFileIndex(pItem);
		if (((iVar22 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c) <= iVar22)) ||
		    (iVar22 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar22 * 0x1b8, iVar22 == 0))
			break;
		pUVar7 = (Unicode*)stack0x00000084;
		iVar6 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar6 = iVar6 + -1;
		} while (iVar6 != 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
		for (iVar6 = Unicode::strlen((Unicode*)stack0x00000084); 0 < iVar6; iVar6 = iVar6 + -1)
		{
			if (*(short*)(stack0x00000084 + iVar6 * 2) == 0x5d)
				goto LAB_6fade225;
		}
		if (*(short*)(stack0x00000084 + iVar6 * 2) == 0x5d)
		{
		LAB_6fade225:
			if ((iVar6 < 3) ||
			    (pUVar7 = (Unicode*)(stack0x00000086 + iVar6 * 2),
			        *(short*)(stack0x0000007e + iVar6 * 2) != 0x5b))
				goto LAB_6fade23c;
		}
		else
		{
		LAB_6fade23c:
			pUVar7 = (Unicode*)stack0x00000084;
		}
		Unicode::strcpy(a1, pUVar7);
		Unicode::strcat(a1, pUStack00000010);
		if (*(short*)(iVar22 + 0x24) != 0)
		{
			pUVar7 = (Unicode*)stack0x00000614;
			iVar6 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar6 = iVar6 + -1;
			} while (iVar6 != 0);
			pUVar7 = (Unicode*)stack0x00000a14;
			iVar6 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar6 = iVar6 + -1;
			} while (iVar6 != 0);
			pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar22 + 0x24)));
			Unicode::strcpy((Unicode*)stack0x00000a14, pUVar7);
			iVar22 = ITEMS_CheckItemFlag(pDStack00000008, 0x1000000, __LINE__, __FILE__);
			if (iVar22 == 0)
			{
				puVar23 = (uint32_t*)stack0x00000486;
				for (iVar22 = 0x31; iVar22 != 0; iVar22 = iVar22 + -1)
				{
					*puVar23 = 0;
					puVar23 = puVar23 + 1;
				}
				*(uint16_t*)puVar23 = 0;
				pUVar7 = (Unicode*)stack0x00000486;
				iVar22 = 99;
				do
				{
					uVar26 = (uint16_t)unaff_EDI;
					pUVar7 = pUVar7 + 1;
					iVar22 = iVar22 + -1;
				} while (iVar22 != 0);
				pUVar7 = (Unicode*)stack0x00000a14;
				pUVar12 = nullptr;
				pUVar13 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2769));
				sub_6FADCFE0((Unicode*)stack0x00000484, (char*)pUVar13, pUVar7, pUVar12, uVar26);
				Unicode::strcat(a1, (Unicode*)stack0x00000484);
			}
			else
			{
				pUVar7 = (Unicode*)stack0x00000e14;
				iVar22 = 0x200;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar22 = iVar22 + -1;
				} while (iVar22 != 0);
				pUVar7 = (Unicode*)stack0x00001e14;
				iVar22 = 0x200;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar22 = iVar22 + -1;
				} while (iVar22 != 0);
				pUVar7 = (Unicode*)stack0x00000044;
				iVar22 = 0x20;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar22 = iVar22 + -1;
				} while (iVar22 != 0);
				iVar22 = 0x20;
				pcVar16 = ITEMS_GetEarName(pDStack00000008);
				Unicode::win2Unicode((Unicode*)stack0x00000e14, pcVar16, iVar22);
				DVar17 = STRTABLE_GetLanguage();
				Unicode::Personalize((Unicode*)stack0x00000614, (Unicode*)stack0x00000e14,
				    (Unicode*)stack0x00000a14, 0x200, (ELANGUAGE)(DVar17));
				Unicode::strcat(a1, (Unicode*)stack0x00000614);
			}
		}
		break;
	case 6:
	case 8:
	case 9:
		uVar3 = ITEMS_GetRarePrefixId(pDStack00000008);
		pDVar11 = DATATBLS_GetRareAffixTxtRecord((uint32_t)uVar3);
		uVar3 = ITEMS_GetRareSuffixId(pDVar20);
		pDVar8 = DATATBLS_GetRareAffixTxtRecord((uint32_t)uVar3);
		iVar6 = 0;
		pDStack0000000c = pDVar8;
		if (pDVar11 != nullptr)
		{
			if (pDVar11->wStringId == 0)
			{
				do
				{
					cVar1 = ("(")[iVar6];
					(stack0x00000614)[iVar6] = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				pcVar16 = pDVar11->szName;
				do
				{
					pcVar10 = pcVar16;
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				uVar5 = ~uVar5;
				iVar22 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar24 = pcVar16;
					if (iVar22 == 0)
						break;
					iVar22 = iVar22 + -1;
					pcVar24 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar24;
				} while (cVar1 != '\0');
				pcVar16 = pcVar10 + -uVar5;
				pcVar10 = pcVar24 + -1;
				for (uVar19 = uVar5 >> 2; uVar19 != 0; uVar19 = uVar19 - 1)
				{
					*(uint32_t*)pcVar10 = *(uint32_t*)pcVar16;
					pcVar16 = pcVar16 + 4;
					pcVar10 = pcVar10 + 4;
				}
				for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
				{
					*pcVar10 = *pcVar16;
					pcVar16 = pcVar16 + 1;
					pcVar10 = pcVar10 + 1;
				}
				iVar22 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar22 == 0)
						break;
					iVar22 = iVar22 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				*(uint16_t*)(pcVar10 + -1) = byte_6FB796FC;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar16 + 1;
				} while (cVar1 != '\0');
				iVar22 = ~uVar5 - 1;
				Unicode::toUnicode((Unicode*)stack0x00001614, (const char*)(stack0x00000614), 0x200);
				pDVar8 = pDStack0000000c;
			}
			else
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar11->wStringId));
				iVar22 = Unicode::strlen(pUVar7);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar11->wStringId));
				Unicode::strcpy((Unicode*)stack0x00001614, pUVar7);
			}
		}
		if (pDVar8 != nullptr)
		{
			if (pDVar8->wStringId == 0)
			{
				pUVar7 = (Unicode*)stack0x00000a14;
				iVar6 = 0x200;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar6 = iVar6 + -1;
				} while (iVar6 != 0);
				iVar6 = 0;
				do
				{
					cVar1 = ("(")[iVar6];
					(stack0x00000614)[iVar6] = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
				uVar5 = 0xffffffff;
				pcVar16 = pDStack0000000c->szName;
				do
				{
					pcVar10 = pcVar16;
					if (uVar5 == 0)
						break;
					uVar5 = uVar5 - 1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				uVar5 = ~uVar5;
				iVar6 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar24 = pcVar16;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pcVar24 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar24;
				} while (cVar1 != '\0');
				pcVar16 = pcVar10 + -uVar5;
				pcVar10 = pcVar24 + -1;
				for (uVar19 = uVar5 >> 2; uVar19 != 0; uVar19 = uVar19 - 1)
				{
					*(uint32_t*)pcVar10 = *(uint32_t*)pcVar16;
					pcVar16 = pcVar16 + 4;
					pcVar10 = pcVar10 + 4;
				}
				for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
				{
					*pcVar10 = *pcVar16;
					pcVar16 = pcVar16 + 1;
					pcVar10 = pcVar10 + 1;
				}
				iVar6 = -1;
				pcVar16 = (char*)(stack0x00000614);
				do
				{
					pcVar10 = pcVar16;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pcVar10 = pcVar16 + 1;
					cVar1 = *pcVar16;
					pcVar16 = pcVar10;
				} while (cVar1 != '\0');
				*(uint16_t*)(pcVar10 + -1) = byte_6FB796FC;
				Unicode::toUnicode((Unicode*)stack0x00000a14, (const char*)(stack0x00000614), 0x200);
				iVar6 = Unicode::strlen((Unicode*)stack0x00000a14);
				pUVar7 = (Unicode*)stack0x00000a14;
			}
			else
			{
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar8->wStringId));
				iVar6 = Unicode::strlen(pUVar7);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar8->wStringId));
			}
			iVar22 = iVar22 + iVar6;
			if (pDVar11 == nullptr)
			{
				Unicode::strcpy((Unicode*)stack0x00001214, pUVar7);
			}
			else
			{
				Unicode::strcat((Unicode*)stack0x00001214, pUVar7);
			}
		}
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		iVar6 = Unicode::strlen(pUVar7);
		D2_ASSERT(in_stack_00002218 > iVar22 + 3 + iVar6);
		pUVar7 = (Unicode*)stack0x00000084;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
		for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084); 0 < iVar22; iVar22 = iVar22 + -1)
		{
			if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
				goto LAB_6faddd02;
		}
		if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
		{
		LAB_6faddd02:
			if ((iVar22 < 3) ||
			    (pUVar7 = (Unicode*)(stack0x00000086 + iVar22 * 2),
			        *(short*)(stack0x0000007e + iVar22 * 2) != 0x5b))
				goto LAB_6faddd19;
		}
		else
		{
		LAB_6faddd19:
			pUVar7 = (Unicode*)stack0x00000084;
		}
		Unicode::strcpy((Unicode*)stack0x00001a14, pUVar7);
		Unicode::strcat((Unicode*)stack0x00001a14, pUStack00000010);
		puVar23 = (uint32_t*)stack0x00000486;
		for (iVar22 = 99; iVar22 != 0; iVar22 = iVar22 + -1)
		{
			*puVar23 = 0;
			puVar23 = puVar23 + 1;
		}
		*(uint16_t*)puVar23 = 0;
		pUVar7 = (Unicode*)stack0x00000486;
		iVar22 = 199;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)stack0x00001214;
		uVar26 = 0;
		pUVar13 = (Unicode*)stack0x00001614;
		pUVar12 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x6b6));
		sub_6FADCFE0((Unicode*)stack0x00000484, (char*)pUVar12, pUVar13, pUVar7, uVar26);
		pUVar7 = (Unicode*)stack0x00000e14;
		iVar22 = 0x200;
		do
		{
			pDVar20 = pDStack00000008;
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		iVar22 = ITEMS_CheckItemFlag(pDStack00000008, 0x1000000, __LINE__, __FILE__);
		if (iVar22 == 0)
		{
			pUVar7 = (Unicode*)stack0x00000484;
		}
		else
		{
			pUVar7 = (Unicode*)stack0x00000a14;
			iVar22 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)stack0x00000614;
			iVar22 = 0x200;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			pUVar7 = (Unicode*)stack0x00000044;
			iVar22 = 0x20;
			do
			{
				pUVar7 = pUVar7 + 1;
				iVar22 = iVar22 + -1;
			} while (iVar22 != 0);
			iVar22 = 0x20;
			pcVar16 = ITEMS_GetEarName(pDVar20);
			Unicode::win2Unicode((Unicode*)stack0x00000a14, pcVar16, iVar22);
			DVar17 = STRTABLE_GetLanguage();
			Unicode::Personalize((Unicode*)stack0x00000e14, (Unicode*)stack0x00000a14, (Unicode*)stack0x00000484, 0x200, (ELANGUAGE)(DVar17));
			pUVar7 = (Unicode*)stack0x00000e14;
		}
		Unicode::strcat((Unicode*)stack0x00001a14, pUVar7);
		Unicode::strcat(a1, (Unicode*)stack0x00001a14);
		break;
	case 7:
		pUVar7 = (Unicode*)stack0x00000084;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar4->wNameStr));
		pcVar21 = (code*)(((uint8_t*)&Unicode::strcpy));
		Unicode::strcpy((Unicode*)stack0x00000084, pUVar7);
		iVar22 = ITEMS_GetFileIndex(pItem);
		if (-1 < iVar22)
		{
			iVar22 = ITEMS_GetFileIndex(pItem);
			if (((-1 < iVar22) && (iVar22 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc28))) &&
			    (iVar22 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc24) + iVar22 * 0x14c, iVar22 != 0))
			{
				if (pDVar4->nSkipName == 0)
				{
					for (iVar6 = Unicode::strlen((Unicode*)stack0x00000084); 0 < iVar6; iVar6 = iVar6 + -1)
					{
						if (*(short*)(stack0x00000084 + iVar6 * 2) == 0x5d)
							goto LAB_6faddff3;
					}
					if (*(short*)(stack0x00000084 + iVar6 * 2) == 0x5d)
					{
					LAB_6faddff3:
						if ((iVar6 < 3) ||
						    (pUVar7 = (Unicode*)(stack0x00000086 + iVar6 * 2),
						        *(short*)(stack0x0000007e + iVar6 * 2) != 0x5b))
							goto LAB_6fade00a;
					}
					else
					{
					LAB_6fade00a:
						pUVar7 = (Unicode*)stack0x00000084;
					}
					Unicode::strcpy(a1, pUVar7);
					Unicode::strcat(a1, pUStack00000010);
				}
				pUVar7 = (Unicode*)stack0x00000a14;
				iVar6 = 0x200;
				do
				{
					pUVar7 = pUVar7 + 1;
					iVar6 = iVar6 + -1;
				} while (iVar6 != 0);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar22 + 0x22)));
				for (iVar6 = Unicode::strlen(pUVar7); 0 < iVar6; iVar6 = iVar6 + -1)
				{
					if (pUVar7[iVar6].ch == 0x5d)
						goto LAB_6fade06b;
				}
				if (pUVar7[iVar6].ch == 0x5d)
				{
				LAB_6fade06b:
					if ((2 < iVar6) && (pUVar7[iVar6 + -3].ch == 0x5b))
					{
						pUVar7 = pUVar7 + iVar6 + 1;
					}
				}
				iVar6 = ITEMS_CheckItemFlag(pDStack00000008, 0x1000000, __LINE__, __FILE__);
				if (iVar6 == 0)
				{
					pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar22 + 0x22)));
					for (iVar22 = Unicode::strlen(pUVar7); 0 < iVar22; iVar22 = iVar22 + -1)
					{
						if (pUVar7[iVar22].ch == 0x5d)
							goto LAB_6fade15f;
					}
					if (pUVar7[iVar22].ch == 0x5d)
					{
					LAB_6fade15f:
						if ((2 < iVar22) && (pUVar7[iVar22 + -3].ch == 0x5b))
						{
							pUVar7 = pUVar7 + iVar22 + 1;
						}
					}
					Unicode::strcat(a1, pUVar7);
				}
				else
				{
					pUVar13 = (Unicode*)stack0x00000e14;
					iVar22 = 0x200;
					do
					{
						pUVar13 = pUVar13 + 1;
						iVar22 = iVar22 + -1;
					} while (iVar22 != 0);
					pUVar13 = (Unicode*)stack0x00000614;
					iVar22 = 0x200;
					do
					{
						pUVar13 = pUVar13 + 1;
						iVar22 = iVar22 + -1;
					} while (iVar22 != 0);
					pUVar13 = (Unicode*)stack0x00000044;
					iVar22 = 0x20;
					do
					{
						pUVar13 = pUVar13 + 1;
						iVar22 = iVar22 + -1;
					} while (iVar22 != 0);
					iVar22 = 0x20;
					pcVar16 = ITEMS_GetEarName(pDStack00000008);
					Unicode::win2Unicode((Unicode*)stack0x00000e14, pcVar16, iVar22);
					DVar17 = STRTABLE_GetLanguage();
					Unicode::Personalize((Unicode*)stack0x00000a14, (Unicode*)stack0x00000e14, pUVar7, 0x200, (ELANGUAGE)(DVar17));
					Unicode::strcat(a1, (Unicode*)stack0x00000a14);
				}
				break;
			}
			for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084); 0 < iVar22; iVar22 = iVar22 + -1)
			{
				if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
					goto LAB_6faddf85;
			}
			if (*(short*)(stack0x00000084 + iVar22 * 2) == 0x5d)
			{
			LAB_6faddf85:
				if ((iVar22 < 3) ||
				    (pUVar7 = (Unicode*)(stack0x00000086 + iVar22 * 2),
				        *(short*)(stack0x0000007e + iVar22 * 2) != 0x5b))
					goto LAB_6faddf9c;
			}
			else
			{
			LAB_6faddf9c:
				pUVar7 = (Unicode*)stack0x00000084;
			}
			Unicode::strcpy(a1, pUVar7);
			break;
		}
		for (iVar22 = Unicode::strlen((Unicode*)stack0x00000084);
		     (0 < iVar22 && (*(short*)(stack0x00000084 + iVar22 * 2) != 0x5d)); iVar22 = iVar22 + -1)
		{
		}
	LAB_6fade702:
		(*pcVar21)();
		break;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	}
	pDVar20 = pDStack00000008;
	iVar22 = ITEMS_CheckItemFlag(pDStack00000008, 0x1000000, __LINE__, __FILE__);
	if ((iVar22 != 0) && ((iVar22 = ITEMS_GetItemQuality(pDVar20), iVar22 < 5 || (9 < iVar22))))
	{
		pUVar7 = (Unicode*)stack0x00000e14;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)stack0x00000a14;
		iVar22 = 0x200;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		pUVar7 = (Unicode*)stack0x00000044;
		iVar22 = 0x20;
		do
		{
			pUVar7 = pUVar7 + 1;
			iVar22 = iVar22 + -1;
		} while (iVar22 != 0);
		iVar22 = 0x20;
		pcVar16 = ITEMS_GetEarName(pDStack00000008);
		Unicode::win2Unicode((Unicode*)stack0x00000e14, pcVar16, iVar22);
		DVar17 = STRTABLE_GetLanguage();
		Unicode::Personalize((Unicode*)stack0x00000a14, (Unicode*)stack0x00000e14, a1, 0x200, (ELANGUAGE)(DVar17));
		Unicode::strcpy(a1, (Unicode*)stack0x00000a14);
		pDVar20 = pDStack00000008;
	}
	sub_6FB5EF30(a1);
	if (pDVar4->nQuest != 0)
	{
		if (pDVar4->nQuestDiffCheck != 0)
		{
			iVar22 = STATLIST_UnitGetStatValue(pDVar20, 0x164, 0);
			bVar2 = sub_6FAAC090();
			if (iVar22 < (int)(uint32_t)bVar2)
			{
				sub_6FB20430((short*)a1, '\x01');
				return;
			}
		}
		if (pDVar4->dwCode != 0x2067656c)
		{
			sub_6FB20430((short*)a1, '\x04');
		}
	}
}

//D2Client.0x6FADE8A0
void __cdecl sub_6FADE8A0()
{
	int iVar1;

	gpCellFile_6FBB5B70 = sub_6FB20100("Panel\\inv_armor");
	gpCellFile_6FBB5B74 = sub_6FB20100("Panel\\inv_belt");
	gpCellFile_6FBB5B78 = sub_6FB20100("Panel\\inv_boots");
	gpCellFile_6FBB5B7C = sub_6FB20100("Panel\\inv_helm_glove");
	gpCellFile_6FBB5B80 = sub_6FB20100("Panel\\inv_ring_amulet");
	gpCellFile_6FBB5B84 = sub_6FB20100("Panel\\inv_weapons");
	gpCellFile_6FBB5B88 = sub_6FB20100("Panel\\tradebtn");
	gpCellFile_6FBB5934 = sub_6FB20100("Panel\\goldcoinbtn");
	iVar1 = FOG_IsExpansion();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FAAC080();
		if (iVar1 != 0)
		{
			gpCellFile_6FBB5B8C = sub_6FB20100("Panel\\invchar6Tab");
			dword_6FBB594C = 0;
			gpCellFile_6FBB5B90 = sub_6FB20100("Panel\\NPCInv");
			return;
		}
	}
	gpCellFile_6FBB5B8C = nullptr;
	dword_6FBB594C = 0;
	gpCellFile_6FBB5B90 = nullptr;
}

//D2Client.0x6FADE970
void __cdecl sub_6FADE970()
{
	int iVar1;

	if (gpCellFile_6FBB591C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB591C);
		gpCellFile_6FBB591C = nullptr;
	}
	if (gpCellFile_6FBB5B70 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B70);
		gpCellFile_6FBB5B70 = nullptr;
	}
	if (gpCellFile_6FBB5B74 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B74);
		gpCellFile_6FBB5B74 = nullptr;
	}
	if (gpCellFile_6FBB5B78 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B78);
		gpCellFile_6FBB5B78 = nullptr;
	}
	if (gpCellFile_6FBB5B7C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B7C);
		gpCellFile_6FBB5B7C = nullptr;
	}
	if (gpCellFile_6FBB5B80 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B80);
		gpCellFile_6FBB5B80 = nullptr;
	}
	if (gpCellFile_6FBB5B84 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B84);
		gpCellFile_6FBB5B84 = nullptr;
	}
	if (gpCellFile_6FBB5B88 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B88);
		gpCellFile_6FBB5B88 = nullptr;
	}
	if (gpCellFile_6FBB5934 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5934);
		gpCellFile_6FBB5934 = nullptr;
	}
	iVar1 = FOG_IsExpansion();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FAAC080();
		if ((iVar1 != 0) && (gpCellFile_6FBB5B8C != nullptr))
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB5B8C);
			gpCellFile_6FBB5B8C = nullptr;
		}
	}
	if (gpCellFile_6FBB5B90 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B90);
		gpCellFile_6FBB5B90 = nullptr;
	}
	if (gpCellFile_6FBB5B94 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5B94);
		gpCellFile_6FBB5B94 = nullptr;
	}
	gpCellFile_6FBB5B70 = nullptr;
	gpCellFile_6FBB5B74 = nullptr;
	gpCellFile_6FBB5B78 = nullptr;
	gpCellFile_6FBB5B7C = nullptr;
	gpCellFile_6FBB5B80 = nullptr;
	gpCellFile_6FBB5B84 = nullptr;
	gpCellFile_6FBB5B88 = nullptr;
	gpCellFile_6FBB5934 = nullptr;
}

//D2Client.0x6FADEAC0
// TODO: decompilation needs review (extraout, in_stack, stack0x, unaff_)
void __cdecl sub_6FADEAC0()
{
	uint8_t stack0xfffffc1c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffc28[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffc2c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	D2BitBufferStrc* pQuestFlags;
	uint8_t uVar1;
	bool bVar2;
	uint8_t bVar3;
	int iVar4;
	int iVar5;
	DWORD DVar6;
	uint32_t* puVar7;
	D2UnitStrc* pDVar8;
	Font nFontSize;
	Unicode* pUVar9;
	int iVar10;
	int iVar11;
	uint32_t extraout_var;
	uint32_t uVar12;
	D2UnitStrc* pDVar13;
	D2UnitStrc* pDVar14;
	char* a2;
	uint32_t uVar15;
	int iVar16;
	uint32_t extraout_var_00;
	D2BitBufferStrc* nTextColor;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	D2GameStrc* pGame;
	D2CellFileStrc* pDVar17;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	int extraout_EDX_01;
	D2UnitStrc* pUnit;
	uint32_t unaff_EBX;
	uint32_t unaff_EBP;
	uint32_t unaff_ESI;
	int* piVar18;
	D2GfxDataStrc* pDVar19;
	uint32_t unaff_EDI;
	int iVar20;
	D2CellFileStrc* pDVar21;
	int* bDexterity;
	int* bLevel;
	int iVar22;
	D2UnitStrc* in_stack_fffffc1c;
	uint32_t uVar23;
	uint32_t in_stack_fffffc28;
	D2InventoryStrc* pDVar24;
	D2InventoryStrc* pInventory;
	D2GfxCellStrc* in_stack_fffffc2c;
	int in_stack_fffffc3c;
	int in_stack_fffffc40;
	int iStack_38c;
	uint8_t bStack_382;
	uint32_t uStack_381;
	uint32_t uStack_37d;
	uint8_t bStack_379;
	D2UnitStrc* pDStack_378;
	int local_374;
	D2GfxDataStrc DStack_370;
	Unicode aUStack_328[24];
	char acStack_2f8[16];
	Unicode aUStack_2e8[16];
	Unicode aUStack_2c8[96];
	Unicode aUStack_208[4];
	Unicode aUStack_200[256];

	iVar4 = sub_6FB57BC0();
	local_374 = iVar4;
	iVar5 = sub_6FB57BD0();
	if (dword_6FBB58EC == 10)
	{
		return;
	}
	if ((0 < dword_6FBB58EC) && (dword_6FBB58EC < 10))
	{
		DVar6 = GetTickCount();
		if ((uint32_t)dword_6FBB5904 < DVar6)
		{
			dword_6FBB5904 = 0;
		}
		if (((dword_6FBB590C == 1) && (dword_6FBB5904 == 0)) &&
		    (iVar4 = sub_6FAFBB50((uint32_t*)stack0xfffffc1c), iVar4 != 0))
		{
			sub_6FAE8F90(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5900));
			dword_6FBB590C = 0;
		}
		if (dword_6FBB58E8 == 1)
		{
			puVar7 = &dword_6FBB37AC;
			do
			{
				*puVar7 = 0;
				puVar7 = puVar7 + 5;
			} while ((int)puVar7 < (int)&dword_6FBB37FC);
			dword_6FBB58EC = 1;
			pDVar8 = CUNIT_GetPlayer();
			pDVar8 = INVENTORY_GetCursorItem(pDVar8->pInventory);
			sub_6FB575B0(pDVar8);
			dword_6FBB58E8 = 0;
		}
		pDVar19 = &DStack_370;
		for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			pDVar19->pCurrentCell = nullptr;
			pDVar19 = (D2GfxDataStrc*)&pDVar19->pCellFile;
		}
		DStack_370.pCellFile = gpCellFile_6FBB5D98;
		DStack_370.nDirection = 0;
		DStack_370.nFrame = 0;
		TEXTURE_CelDraw(&DStack_370, dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		DStack_370.nFrame = 1;
		TEXTURE_CelDraw(&DStack_370, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		DStack_370.nFrame = 2;
		TEXTURE_CelDraw(&DStack_370, dword_6FBBA748, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		DStack_370.nFrame = 3;
		TEXTURE_CelDraw(&DStack_370, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		iVar4 = sub_6FAFBB50((uint32_t*)stack0xfffffc28);
		if ((iVar4 != 0) && (pDVar8 = sub_6FB269F0(in_stack_fffffc28, 1), pDVar8 != nullptr))
		{
			sub_6FAE0F30(pDVar8);
		}
		DStack_370.pCellFile = sub_6FB24110();
		iVar4 = 0;
		if (0 < dword_6FB795B0)
		{
			piVar18 = (int*)(&dword_6FBB37AC);
			do
			{
				DStack_370.nFrame = (uint32_t) * (uint16_t*)((int)piVar18 + 10) + *piVar18;
				TEXTURE_CelDraw(&DStack_370,
				    *(int*)(byte_6FB795B8 + (iVar4 + dword_6FB795AC * 4) * 4) + -1 +
				        dword_6FBBA748,
				    dword_6FBBA74C + -0x3f + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL,
				    nullptr);
				iVar4 = iVar4 + 1;
				piVar18 = piVar18 + 5;
			} while (iVar4 < dword_6FB795B0);
		}
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
		uVar23 = 0;
		if (0 < dword_6FB795A8)
		{
			iVar4 = 0;
			piVar18 = (int*)(&dword_6FB7956E);
			do
			{
				iVar20 = 0;
				if (piVar18[-1] != 0)
				{
					iVar20 = 4;
				}
				if (*piVar18 != 0)
				{
					pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)piVar18 + -6)));
					iVar10 = D2Win_10121_GetTextWidth(pUVar9);
					DStack_370.pCellFile = gpCellFile_6FBB5924;
					uVar12 = uVar23;
					if ((iVar20 != 4) && (uVar12 = DStack_370.nFrame, iVar20 == 0))
					{
						uVar12 = uVar23 + 4;
					}
					DStack_370.nFrame = uVar12;
					TEXTURE_CelDraw(&DStack_370, iVar4 + dword_6FBBA748, dword_6FBBA74C + -0x1c1 + gnScreenHeight,
					    0xffffffff, DRAWMODE_NORMAL, nullptr);
					iVar11 = sub_6FAFC130();
					if (iVar11 == 0)
					{
						D2Win_10117_DrawText(pUVar9, (*(int*)((int)piVar18 + -0xe) - iVar10 / 2) + dword_6FBBA748,
						    *(int*)((int)piVar18 + -10) + dword_6FBBA74C + -0x1e0 + gnScreenHeight, iVar20, 0);
					}
				}
				uVar23 = uVar23 + 1;
				iVar4 = iVar4 + 0x50;
				piVar18 = (int*)((int)piVar18 + 0x12);
			} while ((int)uVar23 < dword_6FB795A8);
		}
		D2Win_10127_SetFont(nFontSize);
		sub_6FAE97C0(2);
		iVar4 = local_374;
	}
	puVar7 = (uint32_t*)stack0xfffffc2c;
	for (iVar20 = 0x12; iVar20 != 0; iVar20 = iVar20 + -1)
	{
		*puVar7 = 0;
		puVar7 = puVar7 + 1;
	}
	uVar23 = 0;
	if (0xb < dword_6FBB58EC)
	{
		if (dword_6FBB58EC < 0xe)
		{
			if (gpCellFile_6FBB592C != nullptr)
			{
				sub_6FAAC080();
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
				    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
				    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
				    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
				    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			pDVar8 = CUNIT_GetPlayer();
			uVar12 = UNITS_GetStashGoldLimit(pDVar8);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfd3));
			Unicode::sprintf(100, aUStack_2c8, pUVar9, uVar12);
			iVar4 = sub_6FAAC080();
			if (iVar4 == 0)
			{
				iVar4 = dword_6FBBA74C + -0xdb;
			}
			else
			{
				iVar4 = dword_6FBBA74C + -0x19f;
			}
			D2Win_10117_DrawText(aUStack_2c8, dword_6FBBA748 + 0x4e, iVar4 + gnScreenHeight, 0, 0);
			uVar1 = byte_6FBB5900;
			byte_6FBB5900 = 4;
			pDVar8 = CUNIT_GetPlayer();
			sub_6FAE0F30(pDVar8);
			byte_6FBB5900 = uVar1;
			sub_6FB24110();
			iVar4 = sub_6FAAC080();
			if (iVar4 == 0)
			{
				iVar4 = dword_6FBBA74C + -0x41;
			}
			else
			{
				iVar4 = dword_6FBBA74C + -0x40;
			}
			iVar4 = iVar4 + gnScreenHeight;
			iVar5 = sub_6FAAC080();
			if (iVar5 == 0)
			{
				iVar5 = dword_6FBBA748 + 0x113;
			}
			else
			{
				iVar5 = dword_6FBBA748 + 0x110;
			}
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, iVar5, iVar4, 0xffffffff, DRAWMODE_NORMAL,
			    nullptr);
			sub_6FAE97C0(0);
			iVar4 = sub_6FB57BC0();
			iVar5 = sub_6FB57BD0();
			iVar20 = sub_6FAAC080();
			if (iVar20 == 0)
			{
				iVar20 = dword_6FBBA748 + 0x113;
			}
			else
			{
				iVar20 = dword_6FBBA748 + 0x110;
			}
			if (iVar20 <= iVar4)
			{
				iVar20 = sub_6FAAC080();
				if (iVar20 == 0)
				{
					iVar20 = dword_6FBBA748 + 0x113;
				}
				else
				{
					iVar20 = dword_6FBBA748 + 0x110;
				}
				if (iVar4 <= iVar20 + 0x28)
				{
					iVar4 = sub_6FAAC080();
					if (iVar4 == 0)
					{
						iVar4 = dword_6FBBA74C + -0x41;
					}
					else
					{
						iVar4 = dword_6FBBA74C + -0x40;
					}
					if (iVar4 + gnScreenHeight + -0x23 <= iVar5)
					{
						iVar4 = sub_6FAAC080();
						if (iVar4 == 0)
						{
							iVar4 = dword_6FBBA74C + -0x41;
						}
						else
						{
							iVar4 = dword_6FBBA74C + -0x40;
						}
						if (iVar5 <= iVar4 + gnScreenHeight + 5)
						{
							pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
							iVar4 = sub_6FAAC080();
							if (iVar4 == 0)
							{
								iVar4 = dword_6FBBA74C + -0x41;
							}
							else
							{
								iVar4 = dword_6FBBA74C + -0x40;
							}
							iVar4 = iVar4 + gnScreenHeight;
							iVar5 = sub_6FAAC080();
							if (iVar5 == 0)
							{
								iVar5 = dword_6FBBA748 + 0x113;
							}
							else
							{
								iVar5 = dword_6FBBA748 + 0x110;
							}
							iVar11 = 0;
							iVar4 = iVar4 + -0x23;
							iVar10 = 0;
							iVar20 = D2Win_10121_GetTextWidth(pUVar9);
							iVar5 = (iVar5 - iVar20 / 2) + 0xc;
							goto LAB_6fadf547;
						}
					}
				}
			}
		}
		else if (dword_6FBB58EC == 0xe)
		{
			iVar20 = sub_6FAABF20();
			if ((iVar20 != 0) || (bVar2 = sub_6FB283E0(), D2C_ZEXT(bVar2) != 0))
			{
				sub_6FB23260(0x1a, 1, 0);
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x4f), 0x17, 0, 0);
				return;
			}
			if (gpCellFile_6FBB5930 != nullptr)
			{
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
				    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
				    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
				    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
				TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
				    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			}
			uVar1 = byte_6FBB5900;
			if ((dword_6FBB5910 == 0) || (0xd < dword_6FBB5914))
			{
				byte_6FBB5900 = 3;
				pDVar8 = CUNIT_GetPlayer();
				sub_6FAE0F30(pDVar8);
			}
			byte_6FBB5900 = uVar1;
			sub_6FB24110();
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x113,
			    dword_6FBBA74C + -0x41 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x90,
			    dword_6FBBA74C + -0xbc + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			if (dword_6FBB5910 != 0)
			{
				DVar6 = GetTickCount();
				if ((DVar6 - dword_6FBB5918 < 0x47) ||
				    (dword_6FBB5914 = dword_6FBB5914 + 1, dword_6FBB5918 = DVar6, dword_6FBB5914 < 0x1e))
				{
					TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, gnScreenWidth / 2, gnScreenHeight / 2 + -1,
					    0xffffffff, DRAWMODE_MODULATE, nullptr);
				}
				else
				{
					dword_6FBB5910 = 0;
					if (gpCellFile_6FBB591C != nullptr)
					{
						CLIENT_FreeCellFile(gpCellFile_6FBB591C);
						gpCellFile_6FBB591C = nullptr;
					}
				}
			}
			D2Win_10127_SetFont(D2FONT_FONT16);
			if ((((dword_6FBBA748 + 0x113 < iVar4) && (iVar4 < dword_6FBBA748 + 0x13b)) &&
			        (dword_6FBBA74C + -100 + gnScreenHeight < iVar5)) &&
			    (iVar5 < dword_6FBBA74C + -0x3c + gnScreenHeight))
			{
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
				iVar11 = 0;
				iVar4 = dword_6FBBA74C + -100 + gnScreenHeight;
				iVar10 = 0;
				iVar5 = D2Win_10121_GetTextWidth(pUVar9);
				iVar5 = (dword_6FBBA748 - iVar5 / 2) + 0x121;
			}
			else
			{
				if (((iVar4 <= dword_6FBBA748 + 0x90) || (dword_6FBBA748 + 0xb8 <= iVar4)) ||
				    ((iVar5 <= dword_6FBBA74C + -0xdf + gnScreenHeight ||
				        (dword_6FBBA74C + -0xb7 + gnScreenHeight <= iVar5))))
					goto LAB_6fadf54c;
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd0d));
				iVar11 = 0;
				iVar4 = dword_6FBBA74C + -0xdf + gnScreenHeight;
				iVar10 = 0;
				iVar5 = D2Win_10121_GetTextWidth(pUVar9);
				iVar5 = (dword_6FBBA748 - iVar5 / 2) + 0x9e;
			}
		LAB_6fadf547:
			D2Win_10129_DrawFramedText(pUVar9, iVar5, iVar4, iVar10, iVar11);
		}
	}
LAB_6fadf54c:
	TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, (gnScreenWidth - dword_6FBBA748) + -0x140,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, (gnScreenWidth - dword_6FBBA748) + -0x40,
	    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	sub_6FAE0A10();
	if (((dword_6FBB594C != 0) && (iVar4 = FOG_IsExpansion(), iVar4 != 0)) &&
	    (iVar4 = sub_6FAAC080(), iVar4 != 0))
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79558 + dword_6FBB59BC,
		    dword_6FB7955C + dword_6FBB59C8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79550 + dword_6FBB59A8,
		    dword_6FB79554 + dword_6FBB59B4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar8 = CUNIT_GetPlayer();
	pDVar24 = pDVar8->pInventory;
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 3);
	iVar4 = 0;
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79500 + dword_6FBB5994,
		    dword_6FB79504 + dword_6FBB59A0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 8);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79508 + dword_6FBB59F8,
		    dword_6FB7950C + dword_6FBB5A04, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 9);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79510 + dword_6FBB5A0C,
		    dword_6FB79514 + dword_6FBB5A18, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 1);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79518 + dword_6FBB596C,
		    dword_6FB7951C + dword_6FBB5978, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 10);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79520 + dword_6FBB5A20,
		    dword_6FB79524 + dword_6FBB5A2C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 2);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79528 + dword_6FBB5980,
		    dword_6FB7952C + dword_6FBB598C, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 6);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79538 + dword_6FBB59D0,
		    dword_6FB7953C + dword_6FBB59DC, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 7);
	if (pDVar13 == nullptr)
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79530 + dword_6FBB59E4,
		    dword_6FB79534 + dword_6FBB59F0, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	iVar20 = 0;
	iVar5 = sub_6FAAC080();
	if ((iVar5 != 0) && (dword_6FBB594C != 0))
	{
		iVar4 = 4;
		iVar20 = -4;
	}
	pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, 4);
	pDVar14 = INVENTORY_GetItemFromBodyLoc(pDVar24, 5);
	iVar5 = INVENTORY_GetWieldType(pDVar8, pDVar24);
	uVar12 = (uint32_t)(iVar5 == 2);
	pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 5);
	if ((pDVar8 == nullptr) && ((pDVar13 == nullptr || (uVar12 == 0))))
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79548 + dword_6FBB59BC + iVar4,
		    dword_6FB7954C + dword_6FBB59C8 + iVar20, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 4);
	if ((pDVar8 == nullptr) && ((pDVar14 == nullptr || (uVar12 == 0))))
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79540 + dword_6FBB59A8 + iVar4,
		    dword_6FB79544 + dword_6FBB59B4 + iVar20, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	if (pDVar13 == nullptr)
	{
		if ((pDVar14 != nullptr) &&
		    (pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 5), pDVar8 == nullptr))
		{
			iVar5 = dword_6FB7954C + dword_6FBB59C8;
			iVar4 = dword_6FB79548 + dword_6FBB59BC;
		LAB_6fadfb93:
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, iVar4, iVar5, 0xffffffff, DRAWMODE_NORMAL,
			    nullptr);
		}
	}
	else if (pDVar14 == nullptr)
	{
		pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 4);
		if (pDVar8 == nullptr)
		{
			iVar5 = dword_6FB79544 + dword_6FBB59B4;
			iVar4 = dword_6FB79540 + dword_6FBB59A8;
			goto LAB_6fadfb93;
		}
	}
	else if (uVar12 == 0)
	{
		pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 5);
		if (pDVar8 == nullptr)
		{
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FB79548 + dword_6FBB59BC,
			    dword_6FB7954C + dword_6FBB59C8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		pDVar8 = INVENTORY_GetItemFromBodyLoc(pDVar24, 4);
		if (pDVar8 == nullptr)
		{
			iVar5 = dword_6FB79544 + dword_6FBB59B4;
			iVar4 = dword_6FB79540 + dword_6FBB59A8;
			goto LAB_6fadfb93;
		}
	}
	if ((dword_6FBB58EC == 0xb) && (gpCellFile_6FBB3890 != nullptr))
	{
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
		    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
		    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748,
		    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x100,
		    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		sub_6FB24110();
		if (dword_6FBB5B1C == 0)
		{
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x113,
			    dword_6FBBA74C + -0x116 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		else
		{
			TEXTURE_CelDrawColor((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x113,
			    dword_6FBBA74C + -0x116 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, 2);
		}
		if (dword_6FBB5B30 == 0)
		{
			if ((dword_6FBB5B18 != 0) || (dword_6FBB5B20 != 0))
			{
				iVar4 = 2;
				goto LAB_6fadfdb0;
			}
			TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0xdf,
			    dword_6FBBA74C + -0x40 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		else
		{
			iVar4 = 1;
		LAB_6fadfdb0:
			TEXTURE_CelDrawColor((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0xdf,
			    dword_6FBBA74C + -0x40 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, iVar4);
		}
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, dword_6FBBA748 + 0x113,
		    dword_6FBBA74C + -0x40 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		uVar1 = byte_6FBB5900;
		byte_6FBB5900 = 1;
		pDVar8 = CUNIT_GetPlayer();
		sub_6FAE0F30(pDVar8);
		byte_6FBB5900 = 2;
		pDVar8 = CUNIT_GetPlayer();
		sub_6FAE0F30(pDVar8);
		byte_6FBB5900 = uVar1;
		D2Win_10127_SetFont(D2FONT_FONT16);
		pDVar19 = &DStack_370;
		iVar4 = 0x17;
		do
		{
			memset((Unicode*)pDVar19, 0, sizeof(Unicode));
			pDVar19 = (D2GfxDataStrc*)((int)&pDVar19->pCurrentCell + 2);
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
		pDVar8 = CUNIT_GetPlayer();
		if ((pDVar8 != nullptr) && (a2 = (char*)sub_6FAB0C00(pDVar8), a2 != nullptr))
		{
			Unicode::win2Unicode((Unicode*)&DStack_370, a2, 0x17);
		}
		pUVar9 = (Unicode*)sub_6FB1FEC0();
		Unicode::strcpy(aUStack_328, pUVar9);
		iVar4 = Unicode::strlen(aUStack_328);
		iVar5 = D2Win_10121_GetTextWidth(aUStack_328);
		if (0x70 < iVar5)
		{
			pUVar9 = aUStack_328 + iVar4;
			do
			{
				pUVar9->ch = 0;
				pUVar9 = pUVar9 + -1;
				iVar4 = D2Win_10121_GetTextWidth(aUStack_328);
			} while (0x70 < iVar4);
		}
		D2Win_10117_DrawText(aUStack_328, dword_6FBBA748 + 0x19, 0x1b - dword_6FBBA74C, 0, 0);
		Unicode::strcpy(aUStack_328, (Unicode*)&DStack_370);
		iVar4 = Unicode::strlen(aUStack_328);
		iVar5 = D2Win_10121_GetTextWidth(aUStack_328);
		if (0x70 < iVar5)
		{
			pUVar9 = aUStack_328 + iVar4;
			do
			{
				pUVar9->ch = 0;
				pUVar9 = pUVar9 + -1;
				iVar4 = D2Win_10121_GetTextWidth(aUStack_328);
			} while (0x70 < iVar4);
		}
		D2Win_10117_DrawText(aUStack_328, dword_6FBBA748 + 0x19, 0xf2 - dword_6FBBA74C, 0, 0);
		iVar10 = 0;
		iVar5 = 0x1b - dword_6FBBA74C;
		iVar20 = 0;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x8a7));
		iVar4 = D2Win_10121_GetTextWidth(pUVar9);
		iVar4 = dword_6FBBA748 - iVar4 / 2;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x8a7));
		D2Win_10117_DrawText(pUVar9, iVar4 + 0xbb, iVar5, iVar20, iVar10);
		uVar15 = sub_6FB1FF40();
		SStrPrintf(acStack_2f8, 0xf, "%d", uVar15);
		Unicode::win2Unicode(aUStack_2e8, acStack_2f8, 0xf);
		iVar10 = 0;
		iVar4 = 0x1b - dword_6FBBA74C;
		iVar20 = 0;
		iVar5 = D2Win_10121_GetTextWidth(aUStack_2e8);
		D2Win_10117_DrawText(aUStack_2e8, (dword_6FBBA748 - iVar5) + 0x124, iVar4, iVar20, iVar10);
		iVar10 = 0;
		iVar5 = 0xf2 - dword_6FBBA74C;
		iVar20 = 0;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x8a7));
		iVar4 = D2Win_10121_GetTextWidth(pUVar9);
		iVar4 = dword_6FBBA748 - iVar4 / 2;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x8a7));
		D2Win_10117_DrawText(pUVar9, iVar4 + 0xbb, iVar5, iVar20, iVar10);
		uVar15 = sub_6FB1FF50();
		SStrPrintf(acStack_2f8, 0xf, "%d", uVar15);
		Unicode::win2Unicode(aUStack_2e8, acStack_2f8, 0xf);
		iVar10 = 0;
		iVar4 = 0xf2 - dword_6FBBA74C;
		iVar20 = 0;
		iVar5 = D2Win_10121_GetTextWidth(aUStack_2e8);
		D2Win_10117_DrawText(aUStack_2e8, (dword_6FBBA748 - iVar5) + 0x124, iVar4, iVar20, iVar10);
	}
	uVar1 = byte_6FBB5900;
	byte_6FBB5900 = 0;
	pDVar8 = CUNIT_GetPlayer();
	sub_6FAE0F30(pDVar8);
	iVar5 = 0;
	iStack_38c = 0;
	byte_6FBB5900 = uVar1;
	iVar4 = sub_6FAAC080();
	if ((iVar4 != 0) && (dword_6FBB594C != 0))
	{
		iVar5 = 4;
		iStack_38c = -4;
	}
	pDVar8 = CUNIT_GetPlayer();
	pDVar24 = pDVar8->pInventory;
	iVar4 = sub_6FAAC080();
	UNITS_GetInventoryRecordId(pDVar8, 0, iVar4);
	sub_6FAE0A10();
	iVar4 = 0;
	do
	{
		pDVar14 = nullptr;
		iVar20 = iVar4;
		pInventory = pDVar24;
		pDVar13 = INVENTORY_GetItemFromBodyLoc(pDVar24, iVar4);
		if (pDVar13 != nullptr)
		{
			ITEMS_GetDimensions(pDVar13, (uint8_t*)&uStack_381, (uint8_t*)&uStack_37d,
			    __FILE__, __LINE__);
			iVar10 = INVENTORY_GetWieldType(pDVar8, pDVar24);
			if (iVar4 == 4)
			{
				pDVar14 = INVENTORY_GetItemFromBodyLoc(pDVar24, 5);
				iVar11 = iVar20;
				if ((((((iVar10 == 2) && (iVar4 = ITEMS_GetQuiverType(pDVar14), iVar11 = iVar20, iVar4 == 0)) && (iVar4 = ITEMS_GetQuiverType(pDVar13), iVar11 = iVar20, iVar4 == 0)) &&
				         ((pDStack_378 = pDVar13,
				             sub_6FB5A320(pDVar13, (D2CellFileStrc*)(((int)((dword_6FBB59B8 & 0xff) - (dword_6FBB3724 & 0xff) * (uStack_381 & 0xff)) >> 1) + iVar5 + dword_6FBB59BC),
				                 ((int)((dword_6FBB59B8 >> 8 & 0xff) -
				                        (dword_6FBB3724 >> 8 & 0xff) * (uStack_37d & 0xff)) >>
				                     1) +
				                     dword_6FBB59C4 + iStack_38c),
				             iVar11 = iVar20, -1 < dword_6FBB59BC && (dword_6FBB59BC < gnViewWidth)))) &&
				        (-1 < dword_6FBB59C4)) &&
				    (uVar12 = dword_6FBB59CC, iVar4 = dword_6FBB59BC, uVar15 = extraout_EDX_00,
				        iVar10 = dword_6FBB59C4, dword_6FBB59C4 < gnViewHeight))
					goto LAB_6fae0380;
			}
			else
			{
				iVar11 = iVar20;
				if ((((iVar4 == 5) &&
				         (pDVar14 = INVENTORY_GetItemFromBodyLoc(pDVar24, 4), iVar11 = iVar20, iVar10 == 2)) &&
				        ((iVar4 = ITEMS_GetQuiverType(pDVar14), iVar11 = iVar20, iVar4 == 0 && (((iVar4 = ITEMS_GetQuiverType(pDVar13), iVar11 = iVar20, iVar4 == 0 && (sub_6FB5A320(pDVar13, (D2CellFileStrc*)(((int)((dword_6FBB59CC & 0xff) - (dword_6FBB3724 & 0xff) * (uStack_381 & 0xff)) >> 1) + iVar5 + dword_6FBB59A8), ((int)((dword_6FBB59CC >> 8 & 0xff) - (dword_6FBB3724 >> 8 & 0xff) * (uStack_37d & 0xff)) >> 1) + dword_6FBB59B0 + iStack_38c), iVar11 = iVar20, -1 < dword_6FBB59A8)) && (dword_6FBB59A8 < gnViewWidth)))))) &&
				    ((-1 < dword_6FBB59B0 &&
				        (uVar12 = dword_6FBB59B8, iVar4 = dword_6FBB59A8, uVar15 = extraout_EDX,
				            iVar10 = dword_6FBB59B0, dword_6FBB59B0 < gnViewHeight))))
				{
				LAB_6fae0380:
					sub_6FB5B0F0(iVar4, iVar10, uVar12 & 0xff, uVar12 >> 8 & 0xff,
					    CONCAT31((int32_t)((uint32_t)uVar15 >> 8), byte_6FBB3778), (DrawMode)(0));
					iVar11 = iVar20;
				}
			}
			iVar10 = iVar11 * 0x14;
			pDVar21 = (D2CellFileStrc*)(((int)((uint32_t)(uint8_t)(&byte_6FBB5968)[iVar10] -
			                                   (dword_6FBB3724 & 0xff) * (uStack_381 & 0xff)) >>
			                                1) +
			                            (&dword_6FBB5958)[iVar11 * 5]);
			iVar4 = ((int)((uint32_t)(uint8_t)byte_6FBB5969[iVar10] -
			               (dword_6FBB3724 >> 8 & 0xff) * (uStack_37d & 0xff)) >>
			            1) +
			        (&dword_6FBB5960)[iVar11 * 5];
			switch (iVar11)
			{
			case 3:
				pDVar21 = (D2CellFileStrc*)((int)&pDVar21->dwVersion + 3);
				break;
			case 4:
			case 5:
				pDVar21 = (D2CellFileStrc*)((int)&pDVar21->dwVersion + iVar5);
				iVar4 = iVar4 + iStack_38c;
				break;
			case 8:
				pDVar21 = (D2CellFileStrc*)((int)&pDVar21->dwVersion + 2);
			case 2:
			case 6:
			case 7:
			case 10:
				iVar4 = iVar4 + -2;
				break;
			case 9:
				pDVar21 = (D2CellFileStrc*)((int)&pDVar21->dwVersion + 2);
				iVar4 = iVar4 + -4;
			}
			iVar20 = iVar11;
			in_stack_fffffc1c = pDVar13;
			if ((pDVar13 == gpUnit_6FBB58F0) && (dword_6FBB58E4 != 0))
			{
				iVar16 = sub_6FB57CC0();
				iVar22 = (&dword_6FBB5960)[iVar11 * 5];
				iVar11 = (&dword_6FBB5958)[iVar11 * 5];
				uVar1 = byte_6FBB3779;
				if (iVar16 == 8)
				{
					uVar1 = byte_6FBB3778;
				}
				if (((-1 < iVar11) && (iVar11 < gnViewWidth)) && ((-1 < iVar22 && (iVar22 < gnViewHeight))))
				{
					sub_6FB5B0F0(iVar11, iVar22, (uint32_t)(uint8_t)(&byte_6FBB5968)[iVar10],
					    (uint32_t)(uint8_t)byte_6FBB5969[iVar10], CONCAT31((int32_t)((uint32_t)iVar16 >> 8), uVar1),
					    (DrawMode)(0));
				}
				sub_6FB5A320(pDVar13, pDVar21, iVar4);
				iVar10 = ITEMS_CheckIfSocketable(pDVar13);
				if (((iVar10 != 0) && (bVar3 = ITEMS_GetMaxSockets(pDVar13), bVar3 != 0)) &&
				    (iVar10 = ITEMS_CheckItemFlag(pDVar13, 0x800, __LINE__, __FILE__), iVar10 != 0))
				{
					sub_6FAE0DC0(pDVar13, (int)&byte_6FBB3710, pDVar21, iVar4);
				}
			}
			else
			{
				if ((((pDVar14 == nullptr) &&
				         ((iVar22 = ITEMS_GetAmmoType(pDVar13), iVar22 != 0 ||
				                                                    (iVar22 = ITEMS_GetQuiverType(pDVar13), iVar22 != 0)))) ||
				        (iVar22 = ITEMS_CheckRequirements(pDVar13, pDVar8, 0, nullptr, nullptr, nullptr),
				            iVar22 == 0)) ||
				    ((iVar22 = sub_6FB2FB90(pDVar13), iVar22 != 0 ||
				                                          (iVar22 = ITEMS_CanBeEquipped(pDVar13), iVar22 == 0))))
				{
					iVar16 = (&dword_6FBB5958)[iVar11 * 5];
					iVar11 = (&dword_6FBB5960)[iVar11 * 5];
					if ((-1 < iVar16) &&
					    (((iVar16 < gnViewWidth && (-1 < iVar11)) && (iVar11 < gnViewHeight))))
					{
						uVar12 = CONCAT31((int32_t)((uint32_t)iVar22 >> 8), byte_6FBB3778);
					LAB_6fae05c0:
						sub_6FB5B0F0(iVar16, iVar11, (uint32_t)(uint8_t)(&byte_6FBB5968)[iVar10],
						    (uint32_t)(uint8_t)byte_6FBB5969[iVar10], uVar12, (DrawMode)(0));
					}
				}
				else
				{
					iVar22 = ITEMS_CheckItemFlag(pDVar13, 0x10, __LINE__, __FILE__);
					if (iVar22 == 0)
					{
						iVar16 = (&dword_6FBB5958)[iVar11 * 5];
						iVar11 = (&dword_6FBB5960)[iVar11 * 5];
						if (((-1 < iVar16) && (iVar16 < gnViewWidth)) &&
						    ((-1 < iVar11 && (iVar11 < gnViewHeight))))
						{
							uVar12 = (uint32_t)byte_6FBB377C;
							goto LAB_6fae05c0;
						}
					}
				}
				sub_6FB5A320(pDVar13, pDVar21, iVar4);
			}
		}
		iVar4 = iVar20 + 1;
		pDVar24 = pInventory;
	} while (iVar4 < 0xb);
	if (((dword_6FBB58EC == 1) &&
	        (iVar20 = sub_6FB57BC0(), pDVar24 = pInventory, iVar20 < gnScreenWidth / 2)) ||
	    (iVar20 = sub_6FB57BD0(), pDVar24 = pInventory, gnScreenHeight + -0x27 <= iVar20))
		goto LAB_6fae0763;
	iVar20 = sub_6FB57BC0();
	pDVar24 = pInventory;
	if (iVar20 < gnScreenWidth / 2)
	{
		dword_6FBB5920 = 0;
		goto LAB_6fae0763;
	}
	pDVar8 = INVENTORY_GetCursorItem(pInventory);
	if ((pDVar8 == nullptr) || (dword_6FBB58E4 == 0))
		goto LAB_6fae0763;
	ITEMS_GetDimensions(pDVar8, &bStack_382, &bStack_379, __FILE__, __LINE__);
	iVar20 = ITEMS_CheckBodyLocation(pDVar8, (uint8_t)dword_6FBB5920);
	if (iVar20 == 0)
	{
	LAB_6fae06ca:
		pDVar13 = INVENTORY_GetItemFromBodyLoc(pInventory, dword_6FBB5920);
		bVar2 = sub_6FAE17D0(pDVar8, pDVar13);
		iVar20 = extraout_EDX_01;
		if (D2C_ZEXT(bVar2) != 0)
			goto LAB_6fae06f2;
		iVar10 = (&dword_6FBB5958)[dword_6FBB5920 * 5];
		iVar11 = (&dword_6FBB5960)[dword_6FBB5920 * 5];
		piVar18 = (int*)(&dword_6FBB5958 + dword_6FBB5920 * 5);
		if ((((iVar10 < 0) || (gnViewWidth <= iVar10)) || (iVar11 < 0)) || (gnViewHeight <= iVar11))
			goto LAB_6fae0763;
		uVar15 = CONCAT31((int32_t)((uint32_t)extraout_EDX_01 >> 8), byte_6FBB3778);
	}
	else
	{
		bLevel = nullptr;
		bDexterity = nullptr;
		piVar18 = nullptr;
		iVar20 = 0;
		pDVar13 = CUNIT_GetPlayer();
		iVar20 = ITEMS_CheckRequirements(pDVar8, pDVar13, iVar20, piVar18, bDexterity, bLevel);
		if (iVar20 == 0)
			goto LAB_6fae06ca;
		iVar20 = dword_6FBB5920 * 5;
	LAB_6fae06f2:
		piVar18 = (int*)(&dword_6FBB5958 + dword_6FBB5920 * 5);
		iVar10 = *piVar18;
		iVar11 = (&dword_6FBB5960)[dword_6FBB5920 * 5];
		if (((iVar10 < 0) || (gnViewWidth <= iVar10)) || ((iVar11 < 0 || (gnViewHeight <= iVar11))))
			goto LAB_6fae0763;
		uVar15 = CONCAT31((int32_t)((uint32_t)iVar20 >> 8), byte_6FBB3779);
	}
	sub_6FB5B0F0(iVar10, iVar11, (uint32_t) * (uint8_t*)(piVar18 + 4), (uint32_t) * (uint8_t*)((int)piVar18 + 0x11),
	    uVar15, (DrawMode)(0));
LAB_6fae0763:
	if ((((0 < dword_6FBB58EC) && (dword_6FBB58EC < 10)) &&
	        ((dword_6FBB36E8 <= (int)dword_6FBB388C &&
	            ((((int)dword_6FBB388C <= dword_6FBB36EC &&
	                  (in_stack_fffffc1c = (D2UnitStrc*)(dword_6FBBA74C + -0x6d + gnScreenHeight),
	                      (int)in_stack_fffffc1c <= (int)dword_6FBB3894)) &&
	                ((int)dword_6FBB3894 <= dword_6FBB36F4)))))) &&
	    (iVar20 = 0, 0 < dword_6FB795B0))
	{
		piVar18 = (int*)(&dword_6FBB37A8);
		while (((*piVar18 != 1 ||
		            ((int)dword_6FBB388C <=
		                *(int*)(byte_6FB795B8 + (iVar20 + dword_6FB795AC * 4) * 4) + dword_6FBBA748)) ||
		        ((*(int*)(byte_6FB795B8 + (iVar20 + dword_6FB795AC * 4) * 4) + dword_6FBBA748 + 0x2d <=
		                (int)dword_6FBB388C ||
		            (((int)dword_6FBB3894 <= (int)in_stack_fffffc1c ||
		                (dword_6FBBA74C + -0x41 + gnScreenHeight <= (int)dword_6FBB3894)))))))
		{
			iVar20 = iVar20 + 1;
			piVar18 = piVar18 + 5;
			if (dword_6FB795B0 <= iVar20)
				goto LAB_6fae0929;
		}
		if ((&word_6FBB37B0)[iVar20 * 10] != 0x276f)
		{
			iVar22 = 0;
			nTextColor = nullptr;
			iVar10 = dword_6FBBA74C + -100 + gnScreenHeight;
			iVar11 = *(int*)(byte_6FB795B8 + (iVar20 + dword_6FB795AC * 4) * 4) + dword_6FBBA748;
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex((&word_6FBB37B0)[iVar20 * 10]));
			goto LAB_6fae0924;
		}
		pDVar8 = CUNIT_GetPlayer();
		pDVar13 = sub_6FAF3930();
		if ((pDVar8 != nullptr) && (pDVar13 != nullptr))
		{
			pQuestFlags = (D2BitBufferStrc*)pDVar13->dwClassId;
			iVar22 = 0;
			nTextColor = sub_6FAFBD20();
			bVar3 = sub_6FAAC090();
			iVar10 = ITEMS_GetAllRepairCosts(pGame, pUnit, 0, (D2C_Difficulties)(int)pDVar8, pQuestFlags, (void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*))((void*)(uint32_t)bVar3));
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x276f));
			Unicode::sprintf(0x100, aUStack_208, pUVar9, iVar10);
			iVar10 = 0;
			pUVar9 = aUStack_208;
			iVar11 = *(int*)(byte_6FB795B8 + (iVar20 + dword_6FB795AC * 4) * 4) + dword_6FBBA748;
		LAB_6fae0924:
			D2Win_10129_DrawFramedText(pUVar9, iVar11, iVar10, (int)nTextColor, iVar22);
		}
	}
LAB_6fae0929:
	sub_6FAE97C0(1);
	pDVar21 = sub_6FB24110();
	pDVar17 = (D2CellFileStrc*)((dword_6FBB5B98 != 0) + 10);
	TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffc2c, (gnScreenWidth - dword_6FBBA748) + -0x12e,
	    dword_6FBBA74C + -0x40 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	CUNIT_GetPlayer();
	if ((((0 < dword_6FBB58EC) && (dword_6FBB58EC < 10)) && (local_374 < gnScreenWidth / 2)) &&
	    (iVar20 = sub_6FAFBB50((uint32_t*)stack0xfffffc1c), iVar20 != 0))
	{
		sub_6FB269F0((uint32_t)in_stack_fffffc1c, 1);
	}
	sub_6FAE1890((D2UnitStrc*)(unaff_EDI), unaff_ESI, unaff_EBP, unaff_EBX, iVar4, in_stack_fffffc1c, (Unicode*)(iVar5), pDVar14,
	    (int)pDVar24, (uint32_t)(in_stack_fffffc2c), (uint32_t)(pDVar21), pDVar17, uVar23, in_stack_fffffc3c,
	    in_stack_fffffc40);
}

//D2Client.0x6FAE0A10
void __cdecl sub_6FAE0A10()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	int nInvPage;
	uint32_t local_4;

	if (gbIsHighResolution == dword_6FBB5B14)
	{
		if (dword_6FBB58D8 != 0)
			goto LAB_6fae0d49;
	}
	else
	{
		dword_6FBB5B14 = gbIsHighResolution;
		dword_6FBB58D8 = 0;
		dword_6FBB58DC = 0;
	}
	iVar1 = sub_6FAAC080();
	nInvPage = 0;
	pDVar2 = CUNIT_GetPlayer();
	iVar1 = UNITS_GetInventoryRecordId(pDVar2, nInvPage, iVar1);
	DATATBLS_GetInventoryRect(iVar1, gbIsHighResolution, (D2InvRectStrc*)&dword_6FBB38C8);
	DATATBLS_GetInventoryGridInfo(iVar1, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3710);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB59A8, 0);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5994, 1);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB59BC, 2);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB596C, 3);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5980, 4);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB59D0, 5);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB59E4, 6);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB59F8, 7);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A0C, 8);
	DATATBLS_GetInventoryComponentGrid(iVar1, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A20, 9);
	DATATBLS_GetInventoryRect(0xd, gbIsHighResolution, (D2InvRectStrc*)&byte_6FBB3780);
	DATATBLS_GetInventoryGridInfo(0xd, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB36F8);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A88, 0);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A74, 1);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A9C, 2);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&dword_6FBB5A4C, 3);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5A60, 4);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5AB0, 5);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5AC4, 6);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5AD8, 7);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5AEC, 8);
	DATATBLS_GetInventoryComponentGrid(0xd, gbIsHighResolution, (D2InvCompGridStrc*)&byte_6FBB5B00, 9);
	DATATBLS_GetInventoryRect(6, gbIsHighResolution, (D2InvRectStrc*)&byte_6FBB3810);
	DATATBLS_GetInventoryGridInfo(6, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB37F8);
	DATATBLS_GetInventoryRect(7, gbIsHighResolution, (D2InvRectStrc*)&byte_6FBB3860);
	DATATBLS_GetInventoryGridInfo(7, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3838);
	DATATBLS_GetInventoryRect(8, gbIsHighResolution, (D2InvRectStrc*)&dword_6FBB3794);
	DATATBLS_GetInventoryGridInfo(8, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3728);
	DATATBLS_GetInventoryRect(0xc, gbIsHighResolution, (D2InvRectStrc*)&dword_6FBB3750);
	DATATBLS_GetInventoryGridInfo(0xc, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3760);
	DATATBLS_GetInventoryRect(9, gbIsHighResolution, (D2InvRectStrc*)&dword_6FBB3850);
	DATATBLS_GetInventoryGridInfo(9, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB38B0);
	DATATBLS_GetInventoryRect(10, gbIsHighResolution, (D2InvRectStrc*)&byte_6FBB3740);
	DATATBLS_GetInventoryGridInfo(10, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3874);
	DATATBLS_GetInventoryRect(0xb, gbIsHighResolution, (D2InvRectStrc*)&byte_6FBB36D8);
	DATATBLS_GetInventoryGridInfo(0xb, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3820);
	dword_6FBB58D8 = 1;
LAB_6fae0d49:
	if ((dword_6FBB58DC == 0) && (dword_6FBB58EC != 0))
	{
		iVar1 = sub_6FAFBB50(&local_4);
		if (iVar1 != 0)
		{
			pDVar2 = sub_6FB269F0(local_4, 1);
			if (pDVar2 != nullptr)
			{
				iVar1 = sub_6FAAC080();
				iVar1 = UNITS_GetInventoryRecordId(pDVar2, 0, iVar1);
				DATATBLS_GetInventoryRect(iVar1, gbIsHighResolution, (D2InvRectStrc*)&dword_6FBB36E8);
				DATATBLS_GetInventoryGridInfo(iVar1, gbIsHighResolution, (D2InventoryGridInfoStrc*)&byte_6FBB3898);
				dword_6FBB58DC = 1;
			}
		}
	}
}

//D2Client.0x6FAE0DC0
void __fastcall sub_6FAE0DC0(D2UnitStrc* pUnit, int a2, D2CellFileStrc* pCellFile2, int a4)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2CellFileStrc* pDVar4;
	int iVar5;
	int nYPos;
	D2GfxDataStrc* pDVar6;
	uint32_t uStack_60;
	D2UnitStrc* pDStack_58;
	uint32_t uStack_54;
	uint32_t uStack_50;
	D2UnitStrc* local_4c;
	D2GfxDataStrc DStack_48;

	local_4c = pUnit;
	iVar1 = ITEMS_CheckItemFlag(pUnit, 0x10, __LINE__, __FILE__);
	if (iVar1 != 0)
	{
		pDStack_58 = INVENTORY_GetFirstItem(pUnit->pInventory);
		ITEMS_GetDimensions(pUnit, (uint8_t*)&uStack_54, (uint8_t*)&uStack_50,
		    __FILE__, __LINE__);
		uVar2 = ITEMS_GetSockets(pUnit);
		uStack_60 = 0;
		iVar5 = (((uStack_50 & 0xff) - 0xd) + ((uStack_54 & 0xff) + (uVar2 & 0xff) * 2) * 4) * 0x30;
		iVar1 = ITEMS_GetSockets(pUnit);
		if ((char)iVar1 != '\0')
		{
			do
			{
				pDVar4 = (D2CellFileStrc*)((int)&pCellFile2->dwVersion +
				                           (int)((*(int*)(byte_6FB6EFD0 + uStack_60 * 8 + iVar5) + -1) *
				                                 (uint32_t) * (uint8_t*)(a2 + 0x14)) /
				                               2);
				nYPos = (int)((*(int*)(byte_6FB6EFD4 + uStack_60 * 8 + iVar5) + 1) *
				              (uint32_t) * (uint8_t*)(a2 + 0x15)) /
				            2 +
				        a4;
				pDVar6 = &DStack_48;
				for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
				{
					pDVar6->pCurrentCell = nullptr;
					pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
				}
				DStack_48.nDirection = 0;
				DStack_48.nFrame = 0;
				DStack_48.pCellFile = gpCellFile_6FBB5E34;
				TEXTURE_CelDraw(&DStack_48, (int)((int)&pDVar4[-1].pGfxCells + 3), nYPos, 0xffffffff,
				    DRAWMODE_TRANS25, nullptr);
				if (pDStack_58 != nullptr)
				{
					pDVar3 = INVENTORY_UnitIsItem(pDStack_58);
					sub_6FB5A320(pDVar3, pDVar4, nYPos - (uint32_t) * (uint8_t*)(a2 + 0x15));
					pDStack_58 = INVENTORY_GetNextItem(pDStack_58);
				}
				uStack_60 = uStack_60 + 1;
				uVar2 = ITEMS_GetSockets(local_4c);
			} while (uStack_60 < (uVar2 & 0xff));
		}
	}
}

//D2Client.0x6FAE0F30
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAE0F30(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	uint32_t uVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pItem;
	int32_t DVar5;
	D2BitBufferStrc* pDVar6;
	int iVar7;
	D2ItemsTxt* pDVar8;
	int32_t DVar9;
	uint32_t extraout_ECX;
	D2UnitStrc* pDVar10;
	int iVar11;
	int iVar12;
	D2UnitStrc* local_28;
	uint32_t uStack_24;
	uint32_t uStack_20;
	D2UnitStrc* pDStack_1c;
	D2UnitStrc* local_18;
	D2InventoryStrc* local_14;
	D2UnitStrc* local_10;
	uint32_t uStack_c;
	uint32_t uStack_8;
	D2UnitStrc* pDStack_4;

	local_10 = pUnit;
	sub_6FAE0A10();
	local_18 = CUNIT_GetPlayer();
	uVar2 = 6;
	if (pUnit != nullptr)
	{
		uVar2 = pUnit->dwUnitType;
	}
	if (uVar2 == 0)
	{
		switch (byte_6FBB5900 & 0xff)
		{
		case 1:
			pDVar10 = (D2UnitStrc*)&byte_6FBB37F8;
			break;
		case 2:
			pDVar10 = (D2UnitStrc*)&byte_6FBB3838;
			break;
		case 3:
			pDVar10 = (D2UnitStrc*)&byte_6FBB38B0;
			break;
		case 4:
			iVar3 = sub_6FAAC080();
			if (iVar3 == 0)
			{
				pDVar10 = (D2UnitStrc*)&byte_6FBB3728;
			}
			else
			{
				pDVar10 = (D2UnitStrc*)&byte_6FBB3760;
			}
			break;
		default:
			pDVar10 = (D2UnitStrc*)&byte_6FBB3710;
		}
	}
	else
	{
		if (uVar2 != 1)
		{
			return;
		}
		pDVar10 = (D2UnitStrc*)&byte_6FBB3898;
	}
	pInventory = pUnit->pInventory;
	if (pInventory == nullptr)
	{
		return;
	}
	local_28 = pDVar10;
	local_14 = pInventory;
	iVar3 = sub_6FAAC080();
	uStack_c = UNITS_GetInventoryRecordId(pUnit, CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5900), iVar3);
	pDVar4 = INVENTORY_GetFirstItem(pInventory);
	pDStack_1c = pDVar4;
	if (pDVar4 != nullptr)
	{
		do
		{
			pDStack_1c = pDVar4;
			pItem = INVENTORY_UnitIsItem(pDVar4);
			if ((pItem == nullptr) || (iVar3 = INVENTORY_GetItemNodePage(pDVar4), iVar3 != 1))
			{
			LAB_6fae12c5:
				pDVar4 = INVENTORY_GetNextItem(pDStack_1c);
			}
			else
			{
				uVar2 = pItem->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					iVar3 = pItem->pDynamicPath->dwClientCoordY;
				}
				else if (pItem->pDynamicPath == nullptr)
				{
					iVar3 = 0;
				}
				else
				{
					iVar3 = PATH_GetXPosition(pItem->pDynamicPath);
				}
				uVar2 = pItem->dwUnitType;
				if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
				{
					DVar5 = (*(int32_t*)&pItem->pDynamicPath->tTargetCoord);
				}
				else if (pItem->pDynamicPath == nullptr)
				{
					(*(uint16_t*)((uint8_t*)&DVar5 + 0)) = 0;
					(*(uint16_t*)((uint8_t*)&DVar5 + 2)) = 0;
				}
				else
				{
					DVar5 = (int32_t)PATH_GetYPosition(pItem->pDynamicPath);
				}
				ITEMS_GetDimensions(pItem, (uint8_t*)&uStack_20, (uint8_t*)&uStack_24,
				    __FILE__, __LINE__);
				bVar1 = ITEMS_GetInvPage(pItem);
				if (bVar1 == byte_6FBB5900)
				{
					if ((pItem == gpUnit_6FBB58F0) && (dword_6FBB58E0 != 0))
					{
						iVar7 = sub_6FB57CC0();
						if ((iVar7 == 8) && (uVar2 = ITEMS_GetTransmogrify(gpUnit_6FBB58F0), uVar2 == 0))
						{
							iVar7 = 0;
						}
						else
						{
							iVar7 = 1;
						}
						pDVar4 = local_28;
						sub_6FAE1710((int)local_28, iVar3, (int)DVar5, uStack_20, uStack_24, iVar7);
						sub_6FB5A320(pItem, (D2CellFileStrc*)((uint32_t) * (uint8_t*)&pDVar4->pPlayerData * iVar3 + pDVar4->dwClassId),
						    (uint32_t) * (uint8_t*)((int)&pDVar4->pPlayerData + 1) * (int)DVar5 +
						        pDVar4->dwUnitId);
						iVar7 = ITEMS_CheckIfSocketable(pItem);
						pDVar10 = pDVar4;
						if (((iVar7 != 0) &&
						        (bVar1 = ITEMS_GetMaxSockets(pItem), pDVar10 = local_28, bVar1 != 0)) &&
						    (iVar7 = ITEMS_CheckItemFlag(pItem, 0x800, __LINE__, __FILE__),
						        pDVar10 = pDVar4, iVar7 != 0))
						{
							sub_6FAE0DC0(pItem, (int)pDVar4,
							    (D2CellFileStrc*)((uint32_t) * (uint8_t*)&pDVar4->pPlayerData * iVar3 + pDVar4->dwClassId),
							    (uint32_t) * (uint8_t*)((int)&pDVar4->pPlayerData + 1) * (int)DVar5 +
							        pDVar4->dwUnitId);
						}
						goto LAB_6fae12c5;
					}
					iVar7 = ITEMS_CheckRequirements(pItem, local_18, 0, nullptr, nullptr, nullptr);
					if (((iVar7 == 0) ||
					        (iVar7 = ITEMS_CheckItemFlag(pItem, 4, __LINE__, __FILE__), iVar7 != 0)) ||
					    ((iVar7 = sub_6FB2FB90(pItem), iVar7 != 0 ||
					                                       (iVar7 = ITEMS_CanBeEquipped(pItem), iVar7 == 0))))
					{
						iVar7 = 0;
					}
					else
					{
						iVar7 = ITEMS_CheckItemFlag(pItem, 0x10, __LINE__, __FILE__);
						if (iVar7 == 0)
						{
							iVar7 = 4;
						}
						else
						{
							pDVar8 = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
							iVar7 = 2;
							if (pDVar8->nQuest != 0)
							{
								uVar2 = pDVar8->dwCode;
								if (uVar2 == 0x20737361)
								{
									iVar7 = 9;
								LAB_6fae122b:
									iVar11 = 5;
									pDVar6 = sub_6FAFBD20();
									iVar7 = QUESTRECORD_GetQuestState(pDVar6, iVar7, iVar11);
									if (iVar7 != 0)
									{
										iVar7 = 2;
										goto LAB_6fae128f;
									}
								}
								else
								{
									if (uVar2 == 0x207a7978)
									{
										iVar7 = 0x14;
										goto LAB_6fae122b;
									}
									if (uVar2 != 0x20327274)
										goto LAB_6fae128f;
									iVar12 = 8;
									iVar11 = 0x25;
									pDVar6 = sub_6FAFBD20();
									iVar11 = QUESTRECORD_GetQuestState(pDVar6, iVar11, iVar12);
									if (iVar11 != 0)
									{
										iVar12 = 7;
										iVar11 = 0x25;
										pDVar6 = sub_6FAFBD20();
										iVar11 = QUESTRECORD_GetQuestState(pDVar6, iVar11, iVar12);
										if (iVar11 == 0)
											goto LAB_6fae128f;
									}
								}
								iVar7 = 0;
							}
						}
					}
				LAB_6fae128f:
					pDVar10 = local_28;
					sub_6FAE1710((int)local_28, iVar3, (int)DVar5, uStack_20, uStack_24, iVar7);
					sub_6FB5A320(pItem, (D2CellFileStrc*)((uint32_t) * (uint8_t*)&pDVar10->pPlayerData * iVar3 + pDVar10->dwClassId),
					    (uint32_t) * (uint8_t*)((int)&pDVar10->pPlayerData + 1) * (int)DVar5 +
					        pDVar10->dwUnitId);
					goto LAB_6fae12c5;
				}
				pDVar4 = INVENTORY_GetNextItem(pDStack_1c);
				pDVar10 = local_28;
			}
		} while (pDVar4 != nullptr);
		pDStack_1c = nullptr;
		pUnit = local_10;
	}
	if (pUnit->dwUnitType == 1)
	{
		return;
	}
	pDVar4 = INVENTORY_GetCursorItem(local_18->pInventory);
	if (pDVar4 == nullptr)
	{
		return;
	}
	iVar3 = sub_6FB57BC0();
	iVar7 = sub_6FB57BD0();
	switch (dword_6FBB58EC)
	{
	case 0xb:
		if (byte_6FBB5900 == '\x01')
		{
			return;
		}
		if (byte_6FBB5900 == '\x02')
		{
			if (iVar3 <= dword_6FBB383C)
			{
				return;
			}
			if (dword_6FBB3840 <= iVar3)
			{
				return;
			}
			if (iVar7 < dword_6FBB3844)
			{
				return;
			}
			if (dword_6FBB3848 < iVar7)
			{
				return;
			}
			goto switchD_6fae1321_default;
		}
		break;
	case 0xc:
	case 0xd:
		if (byte_6FBB5900 == '\x04')
		{
			iVar11 = sub_6FAAC080();
			if (iVar11 == 0)
			{
				if (iVar3 <= dword_6FBB372C)
				{
					return;
				}
				if (dword_6FBB3730 < iVar3)
				{
					return;
				}
				if (iVar7 < dword_6FBB3734)
				{
					return;
				}
				if (dword_6FBB3738 < iVar7)
				{
					return;
				}
			}
			else
			{
				if (iVar3 <= dword_6FBB3764)
				{
					return;
				}
				if (dword_6FBB3768 < iVar3)
				{
					return;
				}
				if (iVar7 < dword_6FBB376C)
				{
					return;
				}
				if (dword_6FBB3770 < iVar7)
				{
					return;
				}
			}
			goto LAB_6fae13b7;
		}
		break;
	case 0xe:
		if (byte_6FBB5900 == '\x03')
		{
			if (iVar3 < dword_6FBB38B4)
			{
				return;
			}
			if (dword_6FBB38B8 <= iVar3)
			{
				return;
			}
			if (iVar7 < dword_6FBB38BC)
			{
				return;
			}
			if (dword_6FBB38C0 < iVar7)
			{
				return;
			}
		}
		else
		{
			if (iVar3 < dword_6FBB38C8)
			{
				return;
			}
			if (dword_6FBB38CC <= iVar3)
			{
				return;
			}
			if (iVar7 < dword_6FBB38D0)
			{
				return;
			}
			if (dword_6FBB38D4 < iVar7)
			{
				return;
			}
		}
		goto switchD_6fae1321_default;
	default:
	LAB_6fae13b7:
		goto switchD_6fae1321_default;
	}
	if (iVar3 < dword_6FBB38C8)
	{
		return;
	}
	if (dword_6FBB38CC <= iVar3)
	{
		return;
	}
	if (iVar7 < dword_6FBB38D0)
	{
		return;
	}
	if (dword_6FBB38D4 < iVar7)
	{
		return;
	}
switchD_6fae1321_default:
	local_10 = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&local_10 + 1)), byte_6FBB5900);
	if (byte_6FBB5900 == -1)
	{
		FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, __LINE__, __FILE__);
		return;
	}
	local_28 = nullptr;
	if (((dword_6FBB58E0 != 0) &&
	        (ITEMS_GetDimensions(pDVar4, (uint8_t*)&pDStack_1c, (uint8_t*)&local_18,
	             __FILE__, __LINE__),
	            -1 < dword_6FB792A0)) &&
	    (((-1 < dword_6FB792A4 &&
	          ((((dword_6FBB58EC != 1 || (iVar3 = sub_6FB57BC0(), gnScreenWidth / 2 <= iVar3)) &&
	                (iVar3 = sub_6FB57BD0(), iVar3 < gnScreenHeight + -0x27)) &&
	              ((dword_6FBB58EC != 0x13 || (iVar3 = sub_6FB57BC0(), gnScreenWidth / 2 <= iVar3)))))) &&
	        (iVar3 = sub_6FB57BD0(), uVar2 = uStack_c, iVar3 < gnScreenHeight + -0x27))))
	{
		bVar1 = (uint8_t)local_10;
		iVar3 = INVENTORY_CanItemBePlaced(local_14, pDVar4, dword_6FB792A0, dword_6FB792A4, uStack_c, &pDStack_4, &uStack_8, bVar1);
		if (iVar3 != 0)
		{
			sub_6FAE1710((int)pDVar10, dword_6FB792A0, dword_6FB792A4, (uint32_t)pDStack_1c, (uint32_t)local_18, 1);
			return;
		}
		iVar3 = INVENTORY_CanItemsBeExchanged(local_14, pDVar4, dword_6FB792A0, dword_6FB792A4, uVar2, &local_28, bVar1, 1);
		if ((iVar3 == 0) &&
		    ((local_28 == nullptr ||
		        (pDVar8 = DATATBLS_GetItemsTxtRecord(local_28->dwClassId), pDVar8->dwCode != 0x20786f62))))
		{
			sub_6FAE1710((int)pDVar10, dword_6FB792A0, dword_6FB792A4, (uint32_t)pDStack_1c, (uint32_t)local_18, 0);
			return;
		}
		ITEMS_GetDimensions(local_28, (uint8_t*)&local_10, (uint8_t*)&uStack_c,
		    __FILE__, __LINE__);
		uVar2 = local_28->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			DVar9 = (*(int32_t*)&local_28->pDynamicPath->tTargetCoord);
		}
		else if (local_28->pDynamicPath == nullptr)
		{
			(*(uint16_t*)((uint8_t*)&DVar9 + 0)) = 0;
			(*(uint16_t*)((uint8_t*)&DVar9 + 2)) = 0;
		}
		else
		{
			DVar9 = (int32_t)PATH_GetYPosition(local_28->pDynamicPath);
		}
		uVar2 = local_28->dwUnitType;
		if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
		{
			iVar3 = local_28->pDynamicPath->dwClientCoordY;
		}
		else if (local_28->pDynamicPath == nullptr)
		{
			iVar3 = 0;
		}
		else
		{
			iVar3 = PATH_GetXPosition(local_28->pDynamicPath);
		}
		sub_6FAE1710((int)pDVar10, iVar3, (int)DVar9, (uint32_t)local_10, uStack_c, 3);
	}
}

//D2Client.0x6FAE1710
void __fastcall sub_6FAE1710(int a1, int a2, int a3, uint32_t a4, uint32_t a5, int a6)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int local_8;

	iVar1 = (a5 & 0xff) + a3;
	local_8 = a3;
	if (a3 < iVar1)
	{
		iVar5 = (a4 & 0xff) + a2;
		do
		{
			iVar4 = a2;
			if (a2 < iVar5)
			{
				do
				{
					iVar2 = (uint32_t) * (uint8_t*)(a1 + 0x14) * iVar4 + *(int*)(a1 + 4);
					iVar3 = (uint32_t) * (uint8_t*)(a1 + 0x15) * local_8 + *(int*)(a1 + 0xc);
					if ((((-1 < iVar2) && (iVar2 < gnViewWidth)) && (-1 < iVar3)) && (iVar3 < gnViewHeight))
					{
						sub_6FB5B0F0(iVar2, iVar3, (uint32_t) * (uint8_t*)(a1 + 0x14), (uint32_t) * (uint8_t*)(a1 + 0x15), CONCAT31((int32_t)((uint32_t)a6 >> 8), (&byte_6FBB3778)[a6]), (DrawMode)(0));
					}
					iVar4 = iVar4 + 1;
				} while (iVar4 < iVar5);
			}
			local_8 = local_8 + 1;
		} while (local_8 < iVar1);
	}
}

//D2Client.0x6FAE17D0
bool __fastcall sub_6FAE17D0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2)
{
	D2InventoryStrc* pInventory;
	uint8_t bVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	if ((((pUnit != nullptr) && (pUnit2 != nullptr)) && (dword_6FBB58EC != 10)) && (dword_6FBB58EC != 0xb))
	{
		iVar2 = ITEMS_IsSocketFiller(pUnit);
		if (iVar2 != 0)
		{
			iVar2 = ITEMS_CheckItemFlag(pUnit2, 0x800, __LINE__, __FILE__);
			if (iVar2 != 0)
			{
				iVar2 = ITEMS_CheckIfSocketable(pUnit2);
				if (iVar2 != 0)
				{
					bVar1 = ITEMS_GetMaxSockets(pUnit2);
					if (bVar1 != 0)
					{
						iVar2 = ITEMS_CheckItemFlag(pUnit2, 0x10, __LINE__, __FILE__);
						if (iVar2 != 0)
						{
							iVar2 = ITEMS_CheckItemFlag(pUnit2, 0x100, __LINE__, __FILE__);
							if ((iVar2 == 0) &&
							    (pInventory = pUnit2->pInventory, pInventory != nullptr))
							{
								uVar3 = ITEMS_GetSockets(pUnit2);
								uVar4 = INVENTORY_GetItemCount(pInventory);
								return uVar4 < (uVar3 & 0xff);
							}
						}
					}
				}
			}
		}
	}
	return false;
}

//D2Client.0x6FAE1890
// TODO: decompilation needs review (extraout, in_stack, stack0x, unaff_)
void __cdecl sub_6FAE1890(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, uint32_t a4, int a5, D2UnitStrc* pUnit2, Unicode* pUnicode, D2UnitStrc* pUnit3, int a9, uint32_t a10, uint32_t a11, D2CellFileStrc* pCellFile, int a13, int a14, int a15)
{
	uint8_t stack0x00000040[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000044[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000048[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000004c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000060[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000064[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000078[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000178[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000001f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000009f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000009fa[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000011f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000019f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001bf8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001df8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00001ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000021f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000023f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00002bf8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00002df8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00002ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000033f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000035f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000037f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000039f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00003bf8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00003df8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00003ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000041f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000043f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000045f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000047f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000049f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00004bf8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00004df8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00004ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000051f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000053f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000055f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000057f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000059f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00005bf8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00005ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000063f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000073f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000077f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00007ff8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000087f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000089f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000091f8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	D2InventoryStrc* pDVar1;
	short* psVar2;
	bool bVar3;
	Unicode* pUVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var;
	int iVar6;
	int iVar7;
	int iVar8;
	Unicode* pUVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	D2UnitStrc* pDVar12;
	D2ItemsTxt* pDVar13;
	Unicode* pUVar14;
	D2ItemsTxt* pDVar15;
	D2GemsTxt* pDVar16;
	short sVar17;
	D2UnitStrc* pHireling;
	uint32_t uVar18;
	char cVar19;
	int extraout_EDX;
	code* pcVar20;
	uint32_t unaff_EDI;
	int iVar21;
	uint32_t* puVar22;
	uint64_t uVar23;
	int in_stack_00000040;
	int in_stack_00000044;
	int in_stack_00000048;
	Unicode in_stack_00000178;
	int iVar24;
	D2CellFileStrc* nTextColor;
	Unicode* pUVar25;

	pCellFile = nullptr;
	(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\0';
	a11 = 0;
	pUnit2 = nullptr;
	pUnit3 = nullptr;
	pUVar9 = (Unicode*)stack0x000001f8;
	iVar21 = 0x400;
	a9 = extraout_EDX;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000023f8;
	iVar21 = 0x400;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000087f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000033f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00003df8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00002bf8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000053f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000021f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00001bf8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000019f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00004df8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000049f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000045f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00004ff8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00001ff8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000041f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	a10 = 0;
	pUVar9 = (Unicode*)stack0x000059f8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00001df8;
	iVar21 = 0x100;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000089f8;
	iVar21 = 0x400;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x00007ff8;
	iVar21 = 0x400;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar9 = (Unicode*)stack0x000091f8;
	iVar21 = 0x1000;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	pUVar9 = (Unicode*)stack0x00000064;
	iVar21 = 10;
	do
	{
		pUVar9 = pUVar9 + 1;
		iVar21 = iVar21 + -1;
	} while (iVar21 != 0);
	pUnit = pHireling;
	if ((a9 != 0) && (pDVar5 = CUNIT_GetPlayer(), pDVar5 != nullptr))
	{
		pUnit = CUNIT_GetPlayer();
	}
	bVar3 = sub_6FAFE9E0();
	pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy));
	if (D2C_ZEXT(bVar3) == 0)
	{
		iVar6 = sub_6FB23230(0x24);
		iVar21 = dword_6FBBA748;
		if (iVar6 != 0)
		{
			iVar24 = dword_6FBBA74C + -0x3f + gnScreenHeight;
			iVar6 = dword_6FBBA748 + 0x110;
			iVar7 = sub_6FB57BC0();
			iVar8 = sub_6FB57BD0();
			if ((((iVar6 <= iVar7) && (iVar7 <= iVar21 + 0x130)) && (iVar24 + -0x20 <= iVar8)) &&
			    (iVar8 <= iVar24))
			{
				iVar7 = 1;
				iVar24 = 0;
				iVar6 = dword_6FBBA74C + -0x62 + gnScreenHeight;
				iVar21 = dword_6FBBA748 + 0x11f;
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
				D2Win_10129_DrawFramedText(pUVar9, iVar21, iVar6, iVar24, iVar7);
			}
		}
		iVar21 = sub_6FB23230(1);
		if ((((iVar21 != 0) || (iVar21 = sub_6FB23230(0x17), iVar21 != 0)) ||
		        ((iVar21 = sub_6FB23230(0x19), iVar21 != 0 ||
		                                           ((iVar21 = sub_6FB23230(0xc), iVar21 != 0 || (iVar21 = sub_6FB23230(0xe), iVar21 != 0)))))) ||
		    (iVar21 = sub_6FB23230(0x1a), pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy)), iVar21 != 0))
		{
			iVar7 = gnScreenWidth - dword_6FBBA748;
			iVar21 = dword_6FBBA74C + -0x40 + gnScreenHeight;
			iVar6 = sub_6FB57BC0();
			iVar24 = sub_6FB57BD0();
			if ((((iVar7 + -0x12e <= iVar6) && (iVar6 <= iVar7 + -0x10e)) && (iVar21 + -0x20 <= iVar24)) && (iVar24 <= iVar21))
			{
				iVar7 = 1;
				iVar21 = dword_6FBBA74C + -99 + gnScreenHeight;
				iVar24 = 0;
				iVar6 = gnScreenWidth - dword_6FBBA748;
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
				D2Win_10129_DrawFramedText(pUVar9, iVar6 + -0x11f, iVar21, iVar24, iVar7);
			}
			iVar7 = gnScreenWidth - dword_6FBBA748;
			iVar21 = dword_6FBBA74C + -0x45 + gnScreenHeight;
			iVar6 = sub_6FB57BC0();
			iVar24 = sub_6FB57BD0();
			if (((iVar7 + -0xed <= iVar6) && (iVar6 <= iVar7 + -0xd9)) &&
			    ((iVar21 + -0x12 <= iVar24 &&
			        ((iVar24 <= iVar21 && (iVar21 = sub_6FAFC0E0(), iVar21 == 0))))))
			{
				sVar17 = 0x101d;
				switch (dword_6FBB58EC)
				{
				case 1:
					sVar17 = 0x1003;
					break;
				case 0xb:
					sVar17 = 0x1021;
					break;
				case 0xc:
				case 0xd:
				case 0xf:
					sVar17 = 0x101e;
				}
				iVar7 = 1;
				iVar21 = dword_6FBBA74C + -0x59 + gnScreenHeight;
				iVar24 = 0;
				iVar6 = gnScreenWidth - dword_6FBBA748;
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar17));
				D2Win_10129_DrawFramedText(pUVar9, iVar6 + -0xde, iVar21, iVar24, iVar7);
			}
			iVar21 = FOG_IsExpansion();
			pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy));
			if ((iVar21 != 0) && (iVar21 = sub_6FAAC080(), pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy)), iVar21 != 0))
			{
				iVar21 = sub_6FB57BD0();
				iVar6 = sub_6FB57BC0();
				if (((dword_6FBB59BC <= iVar6) &&
				        (((iVar6 <= dword_6FBB59C0 && (dword_6FBB59C4 + -0x18 <= iVar21)) && (iVar21 < dword_6FBB59C4)))) ||
				    ((((pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy)), dword_6FBB59A8 <= iVar6 && (iVar6 <= dword_6FBB59AC)) &&
				          (dword_6FBB59B0 + -0x18 <= iVar21)) &&
				        (iVar21 < dword_6FBB59B0))))
				{
					pUVar9 = (Unicode*)stack0x00002ff8;
					iVar21 = 0x200;
					do
					{
						pUVar9 = pUVar9 + 1;
						iVar21 = iVar21 + -1;
					} while (iVar21 != 0);
					pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58c6));
					pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy));
					Unicode::strcpy((Unicode*)stack0x00002ff8, pUVar9);
					uVar10 = sub_6FAD4B60(0x2c, 1);
					if ((short)uVar10 == -1)
					{
						uVar10 = sub_6FAD4B60(0x2c, 0);
						if ((short)uVar10 != -1)
						{
							pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
							Unicode::strcat((Unicode*)stack0x00002ff8, pUVar9);
							iVar21 = 0;
							goto LAB_6fae1e5a;
						}
					}
					else
					{
						pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
						Unicode::strcat((Unicode*)stack0x00002ff8, pUVar9);
						iVar21 = 1;
					LAB_6fae1e5a:
						pUVar9 = sub_6FAD56B0(0x2c, iVar21);
						Unicode::strcat((Unicode*)stack0x00002ff8, pUVar9);
					}
					iVar6 = 0x170;
					iVar21 = sub_6FB57BC0();
					if (dword_6FBBA748 + 500 < iVar21)
					{
						iVar6 = 600;
					}
					D2Win_10129_DrawFramedText((Unicode*)stack0x00002ff8, iVar6 + dword_6FBBA748, 0x15 - dword_6FBBA74C, 0, 1);
				}
			}
		}
	}
	if ((dword_6FBB58E4 == 0) && (dword_6FBB58E0 == 0))
	{
		return;
	}
	if (gpUnit_6FBB58F0 == nullptr)
	{
		return;
	}
	if (pHireling->pInventory == nullptr)
	{
		return;
	}
	pDVar5 = INVENTORY_GetCursorItem(pHireling->pInventory);
	if (pDVar5 != nullptr)
	{
		return;
	}
	pDVar1 = pHireling->pInventory;
	iVar21 = sub_6FB23230(0x17);
	if ((((iVar21 == 0) && (pDVar1 != nullptr)) && (gpUnit_6FBB58F0 != nullptr)) && (iVar21 = INVENTORY_CompareWithItemsParentInventory(pDVar1, gpUnit_6FBB58F0), iVar21 == 0))
	{
		return;
	}
	if (((dword_6FBB58E0 == 0) || (dword_6FB7928C != 0)) ||
	    ((iVar21 = sub_6FAFC130(), iVar21 == 0 || ((dword_6FBB58EC < 1 || (9 < dword_6FBB58EC))))))
	{
		iVar21 = ITEMS_GetItemQuality(gpUnit_6FBB58F0);
		in_stack_00000040 = iVar21;
		iVar6 = sub_6FB57CC0();
		if ((iVar6 == 8) || (uVar11 = ITEMS_GetTransmogrify(gpUnit_6FBB58F0), uVar11 != 0))
		{
			pUVar9 = (Unicode*)stack0x000011f8;
			iVar21 = 0x400;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			uVar11 = ITEMS_GetTransmogrify(gpUnit_6FBB58F0);
			if (uVar11 == 0)
			{
				return;
			}
			if (gpUnit_6FBB58F0 == nullptr)
			{
				iVar21 = -1;
			}
			else
			{
				iVar21 = gpUnit_6FBB58F0->dwClassId;
			}
			pDVar13 = DATATBLS_GetItemsTxtRecord(iVar21);
			D2_ASSERT(pDVar13 != nullptr);
			pCellFile = nullptr;
			pDVar13 = DATATBLS_GetItemRecordFromItemCode(pDVar13->dwTransmogrifyType, (int*)&pCellFile);
			D2_ASSERT(pDVar13 != nullptr);
			D2LANG_GetStringFromTblIndex(0x150b);
			(*pcVar20)();
			D2LANG_GetStringFromTblIndex(pDVar13->wNameStr);
			(*pcVar20)();
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar9);
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x150b));
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar9);
			pUVar9 = (Unicode*)stack0x00000078;
			iVar21 = 0x80;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			sub_6FADD360(0x80);
			sub_6FB5EF30((Unicode*)stack0x00000078);
			Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x00000078);
			puVar22 = (uint32_t*)stack0x000009fa;
			for (iVar21 = 0x1ff; iVar21 != 0; iVar21 = iVar21 + -1)
			{
				*puVar22 = 0;
				puVar22 = puVar22 + 1;
			}
			*(uint16_t*)puVar22 = 0;
			pUVar9 = (Unicode*)stack0x000009fa;
			iVar21 = 0x3ff;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			if ((dword_6FBB58EC < 1) || (9 < dword_6FBB58EC))
			{
				(*pcVar20)();
			}
			else
			{
				sub_6FAE5A40();
			}
			sub_6FB5EF30((Unicode*)stack0x000009f8);
			D2Win_10131_GetTextDimensions((Unicode*)stack0x000009f8, &a5, (int*)(stack0x00000040));
			in_stack_00000048 = in_stack_00000040;
		LAB_6fae3e04:
			iVar21 = 0;
			nTextColor = nullptr;
			if (dword_6FB79294 != in_stack_00000048 && -1 < dword_6FB79294 - in_stack_00000048)
			{
				D2Win_10129_DrawFramedText((Unicode*)stack0x000009f8, dword_6FB79290, dword_6FB79294, 0, 0);
				return;
			}
			in_stack_00000048 = in_stack_00000048 + dword_6FB7929C;
			pUVar9 = (Unicode*)stack0x000009f8;
			goto LAB_6fae3e43;
		}
		if ((iVar21 == 5) &&
		    (iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x10, __LINE__, __FILE__), iVar21 != 0))
		{
			pUVar9 = (Unicode*)stack0x000009f8;
			a10 = 0;
			pUnit3 = nullptr;
			pUnit2 = nullptr;
			iVar21 = 0x400;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)stack0x000063f8;
			iVar21 = 0x800;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			memset(stack0x00002df8, 0, 2 * (0x100));
			memset(stack0x000037f8, 0, 2 * (0x100));
			memset(stack0x000055f8, 0, 2 * (0x100));
			memset(stack0x000057f8, 0, 2 * (0x100));
			memset(stack0x00004bf8, 0, 2 * (0x100));
			memset(stack0x000051f8, 0, 2 * (0x100));
			memset(stack0x00003ff8, 0, 2 * (0x100));
			memset(stack0x000047f8, 0, 2 * (0x100));
			memset(stack0x000043f8, 0, 2 * (0x100));
			memset(stack0x000039f8, 0, 2 * (0x100));
			memset(stack0x000011f8, 0, 2 * (0x400));
			memset(stack0x000035f8, 0, 2 * (0x100));
			memset(stack0x000073f8, 0, 2 * (0x200));
			memset(stack0x000077f8, 0, 2 * (0x400));
			memset(stack0x00005bf8, 0, 2 * (0x200));
			memset(stack0x00005ff8, 0, 2 * (0x200));
			memset(stack0x00003bf8, 0, 2 * (0x100));
			a11 = 0;
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			pDVar5 = pHireling;
			if ((pHireling->dwUnitType == 1) &&
			    (iVar21 = MONSTERS_GetHirelingTypeId(pHireling), iVar21 == 0))
			{
				pDVar5 = CUNIT_GetPlayer();
			}
			pDVar1 = pHireling->pInventory;
			if ((dword_6FBB58E4 == 0) && (dword_6FBB58E0 == 0))
			{
				return;
			}
			if (gpUnit_6FBB58F0 == nullptr)
			{
				return;
			}
			pDVar12 = INVENTORY_GetCursorItem(pDVar1);
			if (pDVar12 != nullptr)
			{
				return;
			}
			if (gpUnit_6FBB58F0 == nullptr)
			{
				iVar21 = -1;
			}
			else
			{
				iVar21 = gpUnit_6FBB58F0->dwClassId;
			}
			pDVar13 = DATATBLS_GetItemsTxtRecord(iVar21);
			D2_ASSERT(pDVar13 != nullptr);
			iVar21 = ITEMS_GetFileIndex(gpUnit_6FBB58F0);
			iVar21 = sub_6FAE5C80(iVar21);
			if (iVar21 == 0)
			{
				return;
			}
			iVar21 = sub_6FAE5C50((int)*(short*)(iVar21 + 0x2c));
			if (iVar21 == 0)
			{
				return;
			}
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar21 + 2)));
			Unicode::strcpy((Unicode*)stack0x000037f8, pUVar4);
			Unicode::strcat((Unicode*)stack0x000037f8, pUVar9);
			ITEMS_CheckRequirements(gpUnit_6FBB58F0, pDVar5, 0, (BOOL*)(stack0x00000044), (int*)&pUnicode, &a9);
			sub_6FAE4060(gpUnit_6FBB58F0, (Unicode*)(stack0x000055f8), pDVar13);
			iVar6 = ITEMS_GetLevelRequirement(gpUnit_6FBB58F0, pDVar5);
			if (1 < iVar6)
			{
				if (a9 == 0)
				{
					a10 = 1;
				}
				sub_6FAE41B0((Unicode*)(stack0x000057f8), iVar6);
			}
			iVar6 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x2d);
			if ((iVar6 != 0) || (iVar6 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x32), iVar6 != 0))
			{
				pUnit = nullptr;
				pDVar12 = nullptr;
				iVar6 = STATLIST_UnitGetItemStatOrSkillStatValue(gpUnit_6FBB58F0, 0x5b, 0);
				if (iVar6 != 0)
				{
					pUnit = sub_6FAE5BD0((uint32_t)pDVar13->wReqStr, iVar6, 100);
					pDVar12 = sub_6FAE5BD0((uint32_t)pDVar13->wReqDex, iVar6, 100);
				}
				iVar6 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x400000, __LINE__, __FILE__);
				if (iVar6 != 0)
				{
					pUnit = (D2UnitStrc*)((int)&pUnit[-1].pRoomNext + 2);
					pDVar12 = (D2UnitStrc*)((int)&pDVar12[-1].pRoomNext + 2);
				}
				if (pDVar13->wReqStr != 0)
				{
					if (in_stack_00000044 == 0)
					{
						pUnit3 = (D2UnitStrc*)0x1;
					}
					sub_6FAE4250((uint16_t*)stack0x00004bf8, (int)pDVar13, (int)pUnit);
				}
				if (pDVar13->wReqDex != 0)
				{
					if (pUnicode == nullptr)
					{
						pUnit2 = (D2UnitStrc*)0x1;
					}
					sub_6FAE4310((uint16_t*)stack0x000051f8, (int)pDVar13, (int)pDVar12);
				}
			}
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000057f8, (char)a10);
			Unicode::strcpy((Unicode*)stack0x000011f8, pUVar4);
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x00004bf8, (char)pUnit3);
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000051f8, (char)pUnit2);
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
			iVar6 = ITEMS_GetClassOfClassSpecificItem(gpUnit_6FBB58F0);
			if (iVar6 != 7)
			{
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)iVar6 + 0x2aa5));
				Unicode::strcat((Unicode*)stack0x00003bf8, pUVar4);
				Unicode::strcat((Unicode*)stack0x00003bf8, pUVar9);
				if (((pDVar5 != nullptr) && (pDVar5->dwUnitType == 0)) &&
				    (pDVar5->dwClassId != iVar6))
				{
					a11 = 1;
				}
				pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x00003bf8, (char)a11);
				Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
			}
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000055f8, '\0');
			Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
			iVar6 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x2d);
			if (iVar6 != 0)
			{
				sub_6FAE5570(gpUnit_6FBB58F0, (Unicode*)(stack0x000035f8), pDVar13);
				sub_6FB20430((short*)stack0x000035f8, '\0');
				Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x000035f8);
				iVar6 = STATLIST_GetMinDamageFromUnit(gpUnit_6FBB58F0, 0);
				if ((-1 < iVar6) && (iVar6 = STATLIST_GetMaxDamageFromUnit(gpUnit_6FBB58F0, 0), -1 < iVar6))
				{
					sub_6FAE43D0(gpUnit_6FBB58F0, (Unicode*)(stack0x00003ff8), pDVar13);
					sub_6FB20430((short*)stack0x00003ff8, '\0');
					Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x00003ff8);
				}
			}
			iVar6 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x33);
			if (iVar6 != 0)
			{
				if (((pDVar5 != nullptr) && (pDVar5->dwUnitType == 0)) &&
				    ((pDVar5->dwClassId == 3 &&
				        ((iVar6 = ITEMS_IsClassValid(gpUnit_6FBB58F0), iVar6 == 0 ||
				                                                           (iVar6 = ITEMS_GetClassOfClassSpecificItem(gpUnit_6FBB58F0), iVar6 == 3))))))
				{
					sub_6FAE5040(gpUnit_6FBB58F0, (Unicode*)(stack0x000043f8), pDVar13);
					sub_6FB20430((short*)stack0x000043f8, '\0');
					Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x000043f8);
				}
				sub_6FAE4EE0(gpUnit_6FBB58F0, (Unicode*)(stack0x000047f8), pDVar13);
				sub_6FB20430((short*)stack0x000047f8, '\0');
				Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x000047f8);
			}
			iVar6 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x32);
			if ((iVar6 != 0) && (iVar6 = STATLIST_GetDefenseFromUnit(gpUnit_6FBB58F0), 0 < iVar6))
			{
				sub_6FAE51D0(pDVar5, gpUnit_6FBB58F0, (Unicode*)(stack0x000039f8), pDVar13);
				sub_6FB20430((short*)stack0x000039f8, '\0');
				Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x000039f8);
			}
			sub_6FADD360(0x100);
			iVar6 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x100, __LINE__, __FILE__);
			cVar19 = '\x01';
			if (iVar6 == 0)
			{
				cVar19 = '\x02';
			}
			sub_6FB20430((short*)stack0x00002df8, cVar19);
			Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x00002df8);
			iVar6 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x800, __LINE__, __FILE__);
			if (iVar6 != 0)
			{
				memset(stack0x00002ff8, 0, 2 * (300));
				sub_6FAE3EE0(gpUnit_6FBB58F0);
				Unicode::strcpy((Unicode*)stack0x000077f8, (Unicode*)stack0x00002ff8);
			}
			sub_6FAF3160(gpUnit_6FBB58F0, (Unicode*)(stack0x000077f8), 0x400, 1, 0);
			sub_6FAF32B0(pDVar5, gpUnit_6FBB58F0, (uint32_t)(stack0x00005bf8), 0x200);
			if ((gpUnit_6FBB58F0 != nullptr) && (gpUnit_6FBB58F0->dwAnimMode == 1))
			{
				sub_6FAF33C0(pDVar5, gpUnit_6FBB58F0, (uint32_t)(stack0x00005ff8), 0x200);
			}
			iVar6 = 0;
			if (0 < *(int*)(iVar21 + 0xc))
			{
				pUnit = (D2UnitStrc*)(iVar21 + 0x110);
				do
				{
					psVar2 = (short*)pUnit->dwUnitType;
					if (psVar2 == nullptr)
						break;
					iVar24 = sub_6FAE5990(pDVar1, (int)*psVar2);
					if (psVar2[0x12] != 0)
					{
						pUVar25 = nullptr;
						pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(psVar2[0x12]));
						pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2769));
						sub_6FADCFE0((Unicode*)stack0x000009f8, (char*)pUVar14, pUVar4, pUVar25, (short)unaff_EDI);
						Unicode::strcat((Unicode*)stack0x000009f8, pUVar9);
					}
					cVar19 = '\x02';
					if (iVar24 == 0)
					{
						cVar19 = '\x01';
					}
					sub_6FB20430((short*)stack0x000009f8, cVar19);
					Unicode::strcat((Unicode*)stack0x000073f8, (Unicode*)stack0x000009f8);
					iVar6 = iVar6 + 1;
					pUnit = (D2UnitStrc*)&pUnit->dwClassId;
				} while (iVar6 < *(int*)(iVar21 + 0xc));
			}
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000073f8, '\x02');
			Unicode::strcpy((Unicode*)stack0x000009f8, pUVar4);
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000037f8, '\x04');
			Unicode::strcat((Unicode*)stack0x000009f8, pUVar4);
			Unicode::strcat((Unicode*)stack0x000009f8, pUVar9);
			pUVar4 = (Unicode*)sub_6FB20430((short*)stack0x000077f8, '\x03');
			Unicode::strcat((Unicode*)stack0x000009f8, pUVar4);
			Unicode::strcat((Unicode*)stack0x000009f8, (Unicode*)stack0x000011f8);
			if (((dword_6FBB58EC == 0) || (dword_6FBB58EC < 1)) || (9 < dword_6FBB58EC))
			{
				Unicode::strcpy((Unicode*)stack0x000063f8, (Unicode*)stack0x000009f8);
			}
			else
			{
				memset(stack0x00000178, 0, 2 * (0x40));
				iVar21 = sub_6FAFB200(gpUnit_6FBB58F0, dword_6FB7928C, (int*)&pCellFile, (Unicode*)(stack0x00000178), 0x40);
				if (iVar21 == 0)
				{
					Unicode::strcpy((Unicode*)stack0x000063f8, (Unicode*)stack0x000009f8);
					if (dword_6FBB58EC != 4)
					{
						memset(stack0x00000078, 0, 2 * (0x40));
						pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd05));
						Unicode::strcpy((Unicode*)stack0x00000078, pUVar4);
						Unicode::strcat((Unicode*)stack0x000063f8, pUVar9);
						pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00000078, '\x01');
						Unicode::strcat((Unicode*)stack0x000063f8, pUVar9);
					}
				}
				else
				{
					Unicode::strcpy((Unicode*)stack0x000063f8, (Unicode*)stack0x000009f8);
					if (in_stack_00000178.ch != 0)
					{
						Unicode::strcat((Unicode*)stack0x000063f8, pUVar9);
					}
					Unicode::strcat((Unicode*)stack0x000063f8, (const Unicode*)(stack0x00000178));
				}
			}
			sub_6FB5EF30((Unicode*)stack0x000063f8);
			D2Win_10131_GetTextDimensions((Unicode*)stack0x000063f8, (int*)(stack0x00000040), &a5);
			iVar21 = 1;
			nTextColor = nullptr;
			if (dword_6FB79294 != a5 && -1 < dword_6FB79294 - a5)
			{
				D2Win_10129_DrawFramedText((Unicode*)stack0x000063f8, dword_6FB79290, dword_6FB79294, 0, 1);
				return;
			}
			in_stack_00000048 = a5 + dword_6FB7929C;
			pUVar9 = (Unicode*)stack0x000063f8;
			goto LAB_6fae3e43;
		}
		uVar11 = ITEMS_GetItemType(gpUnit_6FBB58F0);
		if (uVar11 == 0x12)
		{
			pUVar9 = (Unicode*)stack0x000011f8;
			iVar21 = 0x400;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)stack0x000073f8;
			iVar21 = 0x200;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			if ((gpUnit_6FBB58F0 == nullptr) ||
			    (uVar11 = ITEMS_GetItemType(gpUnit_6FBB58F0), uVar11 != 0x12))
			{
				FOG_DisplayAssert("sghSelItem && ITEMSGetType(sghSelItem) == ITEMTYPE_BOOK",
				    __FILE__, __LINE__);
				exit(-1);
			}
			if (gpUnit_6FBB58F0 == nullptr)
			{
				iVar21 = -1;
			}
			else
			{
				iVar21 = gpUnit_6FBB58F0->dwClassId;
			}
			pDVar13 = DATATBLS_GetItemsTxtRecord(iVar21);
			D2_ASSERT(pDVar13 != nullptr);
			sub_6FAE54B0(gpUnit_6FBB58F0, (Unicode*)(stack0x000011f8), pDVar13);
			if (dword_6FBB58EC == 0)
			{
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x89b));
				Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
				Unicode::strcat((Unicode*)stack0x000011f8, pUVar9);
				pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x89e));
				Unicode::strcat((Unicode*)stack0x000011f8, pUVar4);
				Unicode::strcat((Unicode*)stack0x000011f8, pUVar9);
			}
			memset(stack0x00000078, 0, 2 * (0x80));
			sub_6FADD360(0x80);
			sub_6FB5EF30((Unicode*)stack0x00000078);
			Unicode::strcat((Unicode*)stack0x000011f8, (Unicode*)stack0x00000078);
			memset(stack0x000009f8, 0, 2 * (0x400));
			if ((dword_6FBB58EC < 1) || (9 < dword_6FBB58EC))
			{
				(*pcVar20)();
			}
			else
			{
				sub_6FAE5A40();
			}
			sub_6FB5EF30((Unicode*)stack0x000009f8);
			D2Win_10131_GetTextDimensions((Unicode*)stack0x000009f8, (int*)&pCellFile, &a5);
			in_stack_00000048 = a5;
			goto LAB_6fae3e04;
		}
		iVar21 = ITEMS_GetClassOfClassSpecificItem(gpUnit_6FBB58F0);
		if (iVar21 != 7)
		{
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)iVar21 + 0x2aa5));
			Unicode::strcat((Unicode*)stack0x000041f8, pUVar9);
			Unicode::strcat((Unicode*)stack0x000041f8, pUVar4);
			if (pUnit == nullptr)
			{
				iVar6 = -1;
			}
			else
			{
				iVar6 = pUnit->dwClassId;
			}
			if (iVar6 != iVar21)
			{
				a10 = 1;
			}
		}
		if (gpUnit_6FBB58F0 == nullptr)
		{
			iVar21 = -1;
		}
		else
		{
			iVar21 = gpUnit_6FBB58F0->dwClassId;
		}
		pDVar13 = DATATBLS_GetItemsTxtRecord(iVar21);
		D2_ASSERT(pDVar13 != nullptr);
		iVar21 = ITEMS_GetQuiverType(gpUnit_6FBB58F0);
		pDVar5 = gpUnit_6FBB58F0;
		if (iVar21 == 0)
		{
			sub_6FAE4060(gpUnit_6FBB58F0, (Unicode*)(stack0x000053f8), pDVar13);
		}
		else
		{
			pUVar9 = (Unicode*)stack0x0000004c;
			iVar21 = 10;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			iVar21 = STATLIST_UnitGetStatValue(pDVar5, 0x46, 0);
			if (0 < iVar21)
			{
				pUVar25 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd86));
				Unicode::strcpy((Unicode*)stack0x000001f8, pUVar25);
				STATLIST_UnitGetStatValue(pDVar5, 0x46, 0);
				SStrPrintf((char*)&a13, 10, "%ld");
				Unicode::win2Unicode((Unicode*)stack0x0000004c, (char*)&a13, 9);
				Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
				Unicode::strcat((Unicode*)stack0x000001f8, (Unicode*)stack0x0000004c);
				Unicode::strcat((Unicode*)stack0x000001f8, pUVar14);
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(pDVar13->wNameStr));
				Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
			}
		}
		ITEMS_CheckRequirements(gpUnit_6FBB58F0, pUnit, 0, &a9, (BOOL*)(stack0x00000044), &a5);
		iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x10, __LINE__, __FILE__);
		if ((iVar21 != 0) && (iVar21 = ITEMS_GetLevelRequirement(gpUnit_6FBB58F0, pUnit), 1 < iVar21))
		{
			if (a5 == 0)
			{
				a11 = 1;
			}
			pUVar9 = (Unicode*)stack0x0000004c;
			iVar21 = 10;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			pUVar25 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd8d));
			Unicode::strcpy((Unicode*)stack0x000021f8, pUVar25);
			SStrPrintf((char*)&a13, 10, "%i");
			Unicode::win2Unicode((Unicode*)stack0x0000004c, (char*)&a13, 9);
			Unicode::strcat((Unicode*)stack0x000021f8, pUVar9);
			Unicode::strcat((Unicode*)stack0x000021f8, (Unicode*)stack0x0000004c);
			Unicode::strcat((Unicode*)stack0x000021f8, pUVar14);
		}
		iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x35);
		if (iVar21 != 0)
		{
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x35);
			D2_ASSERT(iVar21);
			sub_6FAF1480(gpUnit_6FBB58F0, (uint16_t*)stack0x000033f8, 0x200);
			pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b48));
			Unicode::strcat((Unicode*)stack0x000033f8, pUVar14);
			Unicode::strcat((Unicode*)stack0x000033f8, pUVar9);
		}
		iVar21 = ITEMS_CheckIfSocketable(gpUnit_6FBB58F0);
		if ((iVar21 != 0) && (pDVar1 = gpUnit_6FBB58F0->pInventory, pDVar1 != nullptr))
		{
			pUVar9 = (Unicode*)&a13;
			iVar21 = 6;
			do
			{
				pUVar9 = pUVar9 + 1;
				iVar21 = iVar21 + -1;
			} while (iVar21 != 0);
			pUnicode = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			pDVar5 = INVENTORY_GetFirstItem(pDVar1);
			if (pDVar5 != nullptr)
			{
				bVar3 = false;
				do
				{
					pDVar12 = INVENTORY_UnitIsItem(pDVar5);
					if (pDVar12 == nullptr)
						break;
					iVar21 = ITEMS_CheckItemTypeId(pDVar12, 0x4a);
					if (iVar21 != 0)
					{
						pDVar15 = DATATBLS_GetItemsTxtRecord(pDVar12->dwClassId);
						if ((0 < (int)pDVar15->dwGemOffset) &&
						    (pDVar16 = DATATBLS_GetGemsTxtRecord(pDVar15->dwGemOffset),
						        pDVar16 != nullptr))
						{
							if (!bVar3)
							{
								bVar3 = true;
								pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x501a));
								Unicode::strcat((Unicode*)stack0x00002bf8, pUVar9);
							}
							Unicode::toUnicode((Unicode*)&a13, pDVar16->szLetter, 6);
							Unicode::strcat((Unicode*)stack0x00002bf8, (Unicode*)&a13);
						}
					}
					pDVar5 = INVENTORY_GetNextItem(pDVar5);
				} while (pDVar5 != nullptr);
				if (bVar3)
				{
					Unicode::toUnicode((Unicode*)&a13, "'", 5);
					Unicode::strcat((Unicode*)stack0x00002bf8, (Unicode*)&a13);
					Unicode::strcat((Unicode*)stack0x00002bf8, pUnicode);
				}
			}
		}
		iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0xd);
		if (iVar21 != 0)
		{
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
			pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x4fd6));
			Unicode::strcat((Unicode*)stack0x00003df8, pUVar14);
			Unicode::strcat((Unicode*)stack0x00003df8, pUVar9);
		}
		iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x2d);
		if ((iVar21 != 0) || (iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x32), iVar21 != 0))
		{
			sub_6FAE3EE0(gpUnit_6FBB58F0);
			iVar6 = 0;
			iVar21 = 0;
			uVar11 = STATLIST_UnitGetItemStatOrSkillStatValue(gpUnit_6FBB58F0, 0x5b, 0);
			if (uVar11 != 0)
			{
				uVar18 = (uint32_t)pDVar13->wReqStr;
				if (uVar18 < 0x100001)
				{
					if ((int)uVar11 < 0x10001)
					{
						iVar21 = (int)(uVar18 * uVar11) / 100;
					}
					else
					{
						if ((int)(uVar11 & 0xfffffff0) < 0x640)
							goto LAB_6fae3293;
						iVar21 = ((int)uVar11 / 100) * uVar18;
					}
				}
				else if ((pDVar13->wReqStr & 0xfff0) < 0x640)
				{
				LAB_6fae3293:
					uVar23 = D2C_alldiv((uint32_t)((int64_t)(int)uVar18 * (int64_t)(int)uVar11),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar18 * (int64_t)(int)uVar11) >>
					               0x20),
					    100, 0);
					iVar21 = (int)uVar23;
				}
				else
				{
					iVar21 = (uVar18 / 100) * uVar11;
				}
				uVar18 = (uint32_t)pDVar13->wReqDex;
				if (uVar18 < 0x100001)
				{
					if ((int)uVar11 < 0x10001)
					{
						iVar6 = (int)(uVar18 * uVar11) / 100;
					}
					else
					{
						if ((int)(uVar11 & 0xfffffff0) < 0x640)
							goto LAB_6fae331f;
						iVar6 = ((int)uVar11 / 100) * uVar18;
					}
				}
				else if ((uVar18 & 0xfffffff0) < 0x640)
				{
				LAB_6fae331f:
					uVar23 = D2C_alldiv((uint32_t)((int64_t)(int)uVar18 * (int64_t)(int)uVar11),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar18 * (int64_t)(int)uVar11) >>
					               0x20),
					    100, 0);
					iVar6 = (int)uVar23;
				}
				else
				{
					iVar6 = (uVar18 / 100) * uVar11;
				}
			}
			iVar24 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x400000, __LINE__, __FILE__);
			if (iVar24 != 0)
			{
				iVar21 = iVar21 + -10;
				iVar6 = iVar6 + -10;
			}
			if (pDVar13->wReqDex != 0)
			{
				if (in_stack_00000044 == 0)
				{
					pUnit3 = (D2UnitStrc*)0x1;
				}
				memset(stack0x0000004c, 0, 2 * (10));
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				pUnicode = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				if (0 < (int)((uint32_t)pDVar13->wReqDex + iVar6))
				{
					pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd83));
					Unicode::strcpy((Unicode*)stack0x000019f8, pUVar14);
					SStrPrintf((char*)&a13, 10, "%i");
					Unicode::win2Unicode((Unicode*)stack0x0000004c, (char*)&a13, 9);
					Unicode::strcat((Unicode*)stack0x000019f8, pUVar9);
					Unicode::strcat((Unicode*)stack0x000019f8, (Unicode*)stack0x0000004c);
					Unicode::strcat((Unicode*)stack0x000019f8, pUnicode);
				}
			}
			if (pDVar13->wReqStr != 0)
			{
				if (a9 == 0)
				{
					pUnit2 = (D2UnitStrc*)0x1;
				}
				memset(stack0x0000004c, 0, 2 * (10));
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				if (0 < (int)((uint32_t)pDVar13->wReqStr + iVar21))
				{
					pUVar25 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd82));
					Unicode::strcpy((Unicode*)stack0x00001bf8, pUVar25);
					SStrPrintf((char*)&a13, 10, "%i");
					Unicode::win2Unicode((Unicode*)stack0x0000004c, (char*)&a13, 9);
					Unicode::strcat((Unicode*)stack0x00001bf8, pUVar9);
					Unicode::strcat((Unicode*)stack0x00001bf8, (Unicode*)stack0x0000004c);
					Unicode::strcat((Unicode*)stack0x00001bf8, pUVar14);
				}
			}
			iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x2d);
			if (iVar21 != 0)
			{
				iVar21 = STATLIST_GetMinDamageFromUnit(gpUnit_6FBB58F0, 0);
				if ((-1 < iVar21) && (iVar21 = STATLIST_GetMaxDamageFromUnit(gpUnit_6FBB58F0, 0), -1 < iVar21))
				{
					sub_6FAE43D0(gpUnit_6FBB58F0, (Unicode*)(stack0x00004df8), pDVar13);
				}
				sub_6FAE5570(gpUnit_6FBB58F0, (Unicode*)(stack0x000089f8), pDVar13);
			}
			iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x33);
			if (iVar21 == 0)
			{
				iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0xf);
				if (((iVar21 != 0) && (pUnit != nullptr)) && (pUnit->dwClassId == 6))
				{
					sub_6FAE5040(gpUnit_6FBB58F0, (Unicode*)(stack0x000045f8), pDVar13);
				}
			}
			else
			{
				if (((pUnit != nullptr) && (pUnit->dwClassId == 3)) &&
				    ((iVar21 = ITEMS_IsClassValid(gpUnit_6FBB58F0), iVar21 == 0 ||
				                                                        (iVar21 = ITEMS_GetClassOfClassSpecificItem(gpUnit_6FBB58F0), iVar21 == 3))))
				{
					sub_6FAE5040(gpUnit_6FBB58F0, (Unicode*)(stack0x000045f8), pDVar13);
				}
				sub_6FAE4EE0(gpUnit_6FBB58F0, (Unicode*)(stack0x000049f8), pDVar13);
			}
			iVar21 = ITEMS_CheckItemTypeId(gpUnit_6FBB58F0, 0x32);
			if ((iVar21 != 0) && (iVar21 = STATLIST_GetDefenseFromUnit(gpUnit_6FBB58F0), 0 < iVar21))
			{
				sub_6FAE51D0(pUnit, gpUnit_6FBB58F0, (Unicode*)(stack0x00004ff8), pDVar13);
			}
		}
		switch (in_stack_00000040)
		{
		case 4:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\x03';
			break;
		case 5:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\x02';
			break;
		case 6:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\t';
			break;
		case 7:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\x04';
			break;
		case 8:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\b';
			break;
		case 9:
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\n';
			break;
		default:
			iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x800, __LINE__, __FILE__);
			if ((iVar21 != 0) ||
			    (iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x400000, __LINE__, __FILE__), iVar21 != 0))
			{
				(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\x05';
			}
		}
		iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x10, __LINE__, __FILE__);
		if ((((iVar21 == 0) && (0 < dword_6FBB58EC)) && (dword_6FBB58EC < 10)) && (dword_6FB7928C == 0))
		{
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\0';
		}
		iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x10, __LINE__, __FILE__);
		if (iVar21 == 0)
		{
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd7f));
			pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy));
			Unicode::strcpy((Unicode*)stack0x00001ff8, pUVar9);
			Unicode::strcat((Unicode*)stack0x00001ff8, pUVar4);
		}
		else
		{
			iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x800, __LINE__, __FILE__);
			pDVar5 = gpUnit_6FBB58F0;
			if (iVar21 == 0)
			{
				memset(stack0x0000004c, 0, 2 * (10));
				pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				pUVar14 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				iVar21 = STATLIST_UnitGetStatValue(pDVar5, 0x46, 0);
				if ((0 < iVar21) || (iVar21 = ITEMS_GetTotalMaxStack(pDVar5), 0 < iVar21))
				{
					pUVar25 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd86));
					Unicode::strcpy((Unicode*)stack0x00001df8, pUVar25);
					STATLIST_UnitGetStatValue(pDVar5, 0x46, 0);
					SStrPrintf((char*)&a13, 10, "%ld");
					Unicode::win2Unicode((Unicode*)stack0x0000004c, (char*)&a13, 9);
					Unicode::strcat((Unicode*)stack0x00001df8, pUVar9);
					Unicode::strcat((Unicode*)stack0x00001df8, (Unicode*)stack0x0000004c);
					Unicode::strcat((Unicode*)stack0x00001df8, pUVar14);
				}
			}
			sub_6FAF3160(gpUnit_6FBB58F0, (Unicode*)(stack0x000091f8), 0x1000, 1, 0);
			pcVar20 = (code*)(((uint8_t*)&Unicode::strcpy));
		}
		sub_6FAE5710(gpUnit_6FBB58F0, (Unicode*)(stack0x00001df8), (int)pDVar13);
		sub_6FADD360(0x100);
		sub_6FB20430((short*)stack0x000059f8, '\x03');
		(*pcVar20)();
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000091f8, '\x03');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00001ff8, '\x01');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000089f8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000021f8, (char)a11);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00001bf8, (char)pUnit2);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000019f8, (char)pUnit3);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000041f8, (char)a10);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000053f8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000033f8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00003df8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00001df8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00004df8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000045f8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x000049f8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00004ff8, '\0');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00002bf8, '\x04');
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		iVar21 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x100, __LINE__, __FILE__);
		if (iVar21 != 0)
		{
			(*(uint8_t*)((uint8_t*)&a2 + 0)) = '\x01';
		}
		pUVar9 = (Unicode*)sub_6FB20430((short*)stack0x00007ff8, (char)a2);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		if (((dword_6FBB58EC == 0) || (dword_6FBB58EC < 1)) || (9 < dword_6FBB58EC))
		{
			(*pcVar20)();
		}
		else
		{
			sub_6FAE5A40();
		}
		nTextColor = pCellFile;
		if ((pDVar13->nQuest != 0) && (uVar11 = pDVar13->dwCode, uVar11 != 0x2067656c))
		{
			if ((dword_6FBB58EC == 0) &&
			    ((gpUnit_6FBB58F0 == nullptr || (gpUnit_6FBB58F0->dwAnimMode == 0))))
			{
				if (uVar11 == 0x20646b62)
				{
					(*pcVar20)();
					sVar17 = 0x89d;
				}
				else
				{
					if (uVar11 != 0x20786f62)
						goto LAB_6fae3b82;
					(*pcVar20)();
					sVar17 = 0x89c;
				}
				D2LANG_GetStringFromTblIndex(sVar17);
				(*pcVar20)();
				Unicode::strcat((Unicode*)stack0x000023f8, pUVar4);
				Unicode::strcat((Unicode*)stack0x000023f8, (Unicode*)stack0x000001f8);
			}
		LAB_6fae3b82:
			sub_6FB20430((short*)stack0x000023f8, '\x04');
			nTextColor = (D2CellFileStrc*)0x4;
		}
		sub_6FB5EF30((Unicode*)stack0x000023f8);
		Unicode::strlen((Unicode*)stack0x000023f8);
		D2Win_10131_GetTextDimensions((Unicode*)stack0x000023f8, (int*)stack0x00000060, (int*)(stack0x00000048));
	}
	else
	{
		sub_6FADD360(0x80);
		D2LANG_GetStringFromTblIndex(0xd7f);
		(*pcVar20)();
		Unicode::strcat((Unicode*)stack0x00001ff8, pUVar4);
		Unicode::strcat((Unicode*)stack0x000001f8, (Unicode*)stack0x00001ff8);
		uVar11 = ITEMS_GetItemType(gpUnit_6FBB58F0);
		switch (uVar11)
		{
		case 0x3c:
		case 0x55:
		case 0x56:
		case 0x57:
			sVar17 = 0x2aa5;
			break;
		case 0x3d:
		case 0x47:
			sVar17 = 0x2aa9;
			break;
		case 0x3e:
		case 0x45:
			sVar17 = 0x2aa7;
			break;
		case 0x3f:
		case 0x46:
			sVar17 = 0x2aa8;
			break;
		case 0x40:
		case 0x44:
			sVar17 = 0x2aa6;
			break;
		case 0x41:
		case 0x43:
		case 0x58:
			sVar17 = 0x2aab;
			break;
		case 0x42:
		case 0x48:
		case 0x49:
			sVar17 = 0x2aaa;
			break;
		default:
			goto switchD_6fae1fcc_caseD_4a;
		}
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar17));
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar9);
		Unicode::strcat((Unicode*)stack0x000001f8, pUVar4);
	switchD_6fae1fcc_caseD_4a:
		Unicode::strcat((Unicode*)stack0x000001f8, (Unicode*)stack0x00007ff8);
		sub_6FB20430((short*)stack0x000001f8, '\0');
		sub_6FAE5A40();
		D2Win_10131_GetTextDimensions((Unicode*)stack0x000023f8, (int*)stack0x00000060, (int*)(stack0x00000048));
		nTextColor = nullptr;
	}
	iVar21 = 1;
	if (dword_6FB79294 != in_stack_00000048 && -1 < dword_6FB79294 - in_stack_00000048)
	{
		D2Win_10129_DrawFramedText((Unicode*)stack0x000023f8, dword_6FB79290, dword_6FB79294, (int)nTextColor, 1);
		return;
	}
	in_stack_00000048 = in_stack_00000048 + dword_6FB7929C;
	pUVar9 = (Unicode*)stack0x000023f8;
LAB_6fae3e43:
	D2Win_10129_DrawFramedText(pUVar9, dword_6FB79298, in_stack_00000048, (int)nTextColor, iVar21);
}

//D2Client.0x6FAE3EE0
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAE3EE0(D2UnitStrc* pUnit)
{
	Unicode* pUVar1;
	Unicode* pUVar2;
	uint32_t uVar3;
	Unicode* in_EDX;
	int iVar4;
	bool bVar5;
	int local_4c;
	char acStack_40[12];
	Unicode aUStack_34[10];
	Unicode local_20[16];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::win2Unicode(local_20, &byte_6FB9A828, 0xf);
	Unicode::strcpy(in_EDX, local_20);
	iVar4 = ITEMS_CheckItemFlag(pUnit, 0x400000, __LINE__, __FILE__);
	bVar5 = iVar4 != 0;
	if (bVar5)
	{
		Unicode::win2Unicode(local_20, "Ethereal", 0xf);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58d9));
		Unicode::strcat(in_EDX, pUVar2);
	}
	iVar4 = ITEMS_CheckItemFlag(pUnit, 0x800, __LINE__, __FILE__);
	if (iVar4 != 0)
	{
		if (bVar5)
		{
			Unicode::win2Unicode(local_20, ", ", 0xf);
			Unicode::strcat(in_EDX, local_20);
		}
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd7d));
		Unicode::strcat(in_EDX, pUVar2);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		uVar3 = ITEMS_GetSockets(pUnit);
		SStrPrintf(acStack_40, 10, "(%i)", uVar3 & 0xff);
		Unicode::win2Unicode(aUStack_34, acStack_40, 9);
		Unicode::strcat(in_EDX, pUVar2);
		Unicode::strcat(in_EDX, aUStack_34);
		Unicode::strcat(in_EDX, pUVar1);
		return;
	}
	if (bVar5)
	{
		Unicode::strcat(in_EDX, pUVar1);
	}
}

//D2Client.0x6FAE4060
void __fastcall sub_6FAE4060(D2UnitStrc* pUnit, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	iVar4 = ITEMS_HasDurability(pUnit);
	if (((iVar4 != 0) && (iVar4 = STATLIST_GetMaxDurabilityFromUnit(pUnit), 0 < iVar4)) &&
	    (iVar4 = ITEMS_CheckIfThrowable(pUnit), iVar4 == 0))
	{
		iVar4 = STATLIST_GetUnitStatBonus(pUnit, 0x4b, 0);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd81));
		Unicode::strcpy(pUnicode, pUVar2);
		iVar3 = STATLIST_UnitGetStatValue(pUnit, 0x48, 0);
		SStrPrintf(acStack_20, 10, "%i", iVar3);
		Unicode::strcat(pUnicode, pUVar1);
		Unicode::win2Unicode(local_14, acStack_20, 9);
		Unicode::strcat(pUnicode, local_14);
		Unicode::strcat(pUnicode, pUVar1);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd87));
		Unicode::strcat(pUnicode, pUVar2);
		Unicode::strcat(pUnicode, pUVar1);
		iVar3 = STATLIST_GetMaxDurabilityFromUnit(pUnit);
		SStrPrintf(acStack_20, 10, "%i", iVar3);
		Unicode::win2Unicode(local_14, acStack_20, 9);
		if (iVar4 != 0)
		{
			sub_6FB20430((short*)local_14, '\x03');
		}
		Unicode::strcat(pUnicode, local_14);
		Unicode::strcat(pUnicode, a2);
	}
}

//D2Client.0x6FAE41B0
void __fastcall sub_6FAE41B0(Unicode* pUnicode, uint32_t a22)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	int iVar2;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd8d));
	Unicode::strcpy(pUnicode, a2_00);
	SStrPrintf(acStack_20, 10, "%i", a22);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_14);
	Unicode::strcat(pUnicode, a2);
}

//D2Client.0x6FAE4250
void __fastcall sub_6FAE4250(uint16_t* a1, int a22, int a3)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	int iVar2;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	iVar2 = (uint32_t) * (uint16_t*)(a22 + 0x10a) + a3;
	if (iVar2 < 1)
	{
		*a1 = 0;
		return;
	}
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd82));
	Unicode::strcpy((Unicode*)a1, a2_00);
	SStrPrintf(acStack_20, 10, "%i", iVar2);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat((Unicode*)a1, pUVar1);
	Unicode::strcat((Unicode*)a1, local_14);
	Unicode::strcat((Unicode*)a1, a2);
}

//D2Client.0x6FAE4310
void __fastcall sub_6FAE4310(uint16_t* a1, int a22, int a3)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	int iVar2;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	iVar2 = (uint32_t) * (uint16_t*)(a22 + 0x10c) + a3;
	if (iVar2 < 1)
	{
		*a1 = 0;
		return;
	}
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd83));
	Unicode::strcpy((Unicode*)a1, a2_00);
	SStrPrintf(acStack_20, 10, "%i", iVar2);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat((Unicode*)a1, pUVar1);
	Unicode::strcat((Unicode*)a1, local_14);
	Unicode::strcat((Unicode*)a1, a2);
}

//D2Client.0x6FAE43D0
// TODO: decompilation needs review (unaff_)
void __fastcall sub_6FAE43D0(D2UnitStrc* pUnit, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	uint8_t bVar1;
	Unicode* pUVar2;
	D2UnitStrc* pPlayer;
	Unicode* pUVar3;
	int iVar4;
	uint32_t uVar5;
	short index;
	char cVar6;
	uint32_t unaff_EBX;
	int iVar7;
	code* pcVar8;
	code* pcVar9;
	int iStack_620;
	int iStack_61c;
	int iStack_618;
	D2UnitStrc* local_614;
	Unicode* pUStack_610;
	int iStack_60c;
	Unicode* pUStack_608;
	D2UnitStrc* pDStack_604;
	char acStack_600[256];
	Unicode aUStack_500[252];
	short asStack_308[2];
	short asStack_304[2];
	Unicode local_300[256];
	Unicode aUStack_100[128];

	pUVar2 = local_300;
	iVar7 = 0x100;
	local_614 = pUnit;
	do
	{
		pUVar2 = pUVar2 + 1;
		iVar7 = iVar7 + -1;
	} while (iVar7 != 0);
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	pUStack_608 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	pPlayer = CUNIT_GetPlayer();
	pDStack_604 = pPlayer;
	iVar7 = ITEMS_CheckItemTypeId(pUnit, 0x26);
	if (iVar7 != 0)
	{
		iVar7 = ITEMS_GetMissileType(pUnit);
		local_614 = (D2UnitStrc*)aUStack_500;
		pUStack_610 = (Unicode*)0x100;
		do
		{
			memset((Unicode*)local_614, 0, sizeof(Unicode));
			local_614 = (D2UnitStrc*)((int)local_614 + 2);
			pUStack_610 = (Unicode*)((int)pUStack_610 + -1);
		} while (pUStack_610 != nullptr);
		iStack_60c = 0;
		iStack_61c = MISSILE_GetMinElemDamage(nullptr, pPlayer, iVar7, 1);
		iStack_620 = MISSILE_GetMaxElemDamage(nullptr, pPlayer, iVar7, 1);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd8b));
		Unicode::strcpy(aUStack_500, pUVar3);
		sub_6FB20430((short*)aUStack_500, '\0');
		bVar1 = MISSILE_GetElemTypeFromMissileId(iVar7);
		switch (bVar1)
		{
		case 1:
			cVar6 = '\x01';
			break;
		case 2:
			cVar6 = '\x04';
			break;
		default:
			cVar6 = (char)iStack_60c;
			break;
		case 4:
			cVar6 = '\x03';
			break;
		case 5:
			cVar6 = '\x02';
			iVar4 = MISSILE_GetElementalLength(0, pDStack_604, iVar7, 1);
			iVar4 = iVar4 / 0x19;
			if (iVar4 < 1)
			{
				iVar4 = 1;
			}
			iStack_61c = iStack_61c / iVar4;
			iStack_620 = iStack_620 / iVar4;
		}
		iVar4 = MISSILE_GetMinDamage(nullptr, pDStack_604, iVar7, 1);
		iStack_61c = iStack_61c + iVar4;
		iVar7 = MISSILE_GetMaxDamage(nullptr, pDStack_604, iVar7, 1);
		iStack_61c = iStack_61c >> 8;
		iStack_620 = iStack_620 + iVar7 >> 8;
		if (iStack_620 <= iStack_61c)
		{
			iStack_620 = iStack_61c;
		}
		SStrPrintf(acStack_600, 0x100, "%i", iStack_61c);
		Unicode::win2Unicode(local_300, acStack_600, 9);
		sub_6FB20430((short*)local_300, cVar6);
		Unicode::strcat(aUStack_500, pUVar2);
		Unicode::strcat(aUStack_500, local_300);
		if (iStack_61c != iStack_620)
		{
			Unicode::strcat(aUStack_500, pUVar2);
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd88));
			Unicode::strcat(aUStack_500, pUVar3);
			SStrPrintf(acStack_600, 0x100, "%i", iStack_620);
			Unicode::win2Unicode(local_300, acStack_600, 9);
			sub_6FB20430((short*)local_300, cVar6);
			Unicode::strcat(aUStack_500, pUVar2);
			Unicode::strcat(aUStack_500, local_300);
		}
		Unicode::strcat(aUStack_500, pUStack_608);
		Unicode::strcpy(pUnicode, aUStack_500);
		return;
	}
	iStack_618 = 0;
	iVar7 = ITEMS_Is1Or2Handed(pPlayer, pUnit);
	if (iVar7 == 0)
	{
		uVar5 = ITEMS_CheckWeaponIfTwoHanded(pUnit);
		if (uVar5 == 0)
		{
			sub_6FAE4C60(pPlayer, pUnit, 0x15, 0x16, (uint32_t*)(&iStack_61c), (uint32_t*)(&iStack_620), (uint32_t*)(&iStack_618));
			index = 0xd89;
		}
		else
		{
			sub_6FAE4C60(pPlayer, pUnit, 0x17, 0x18, (uint32_t*)(&iStack_61c), (uint32_t*)(&iStack_620), (uint32_t*)(&iStack_618));
			index = 0xd8a;
		}
		if (iStack_620 <= iStack_61c + 1)
		{
			iStack_620 = iStack_61c + 1;
		}
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		Unicode::strcpy(pUnicode, pUVar3);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_61c);
		pcVar8 = (code*)(((uint8_t*)&Unicode::win2Unicode));
		Unicode::win2Unicode(local_300, acStack_600, 9);
		pcVar9 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(pUnicode, pUVar2);
		if (iStack_618 != 0)
		{
			sub_6FB20430((short*)local_300, '\x03');
		}
		Unicode::strcat(pUnicode, local_300);
		Unicode::strcat(pUnicode, pUVar2);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd88));
		Unicode::strcat(pUnicode, pUVar3);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_620);
		Unicode::win2Unicode(local_300, acStack_600, 9);
		Unicode::strcat(pUnicode, pUVar2);
		Unicode::strcat(pUnicode, local_300);
	}
	else
	{
		sub_6FAE4C60(pPlayer, pUnit, 0x17, 0x18, (uint32_t*)(&iStack_61c), (uint32_t*)(&iStack_620), (uint32_t*)(&iStack_618));
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd8a));
		Unicode::strcpy(aUStack_100, pUVar3);
		pcVar9 = (code*)(((uint8_t*)&Unicode::strcat));
		Unicode::strcat(aUStack_100, pUVar2);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_61c);
		pcVar8 = (code*)(((uint8_t*)&Unicode::win2Unicode));
		Unicode::win2Unicode(local_300, acStack_600, 5);
		if (iStack_618 != 0)
		{
			sub_6FB20430((short*)local_300, '\x03');
		}
		Unicode::strcat(aUStack_100, local_300);
		Unicode::strcat(aUStack_100, pUVar2);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd88));
		Unicode::strcat(aUStack_100, pUVar3);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_620);
		Unicode::win2Unicode(local_300, acStack_600, 5);
		Unicode::strcat(aUStack_100, pUVar2);
		Unicode::strcat(aUStack_100, local_300);
		Unicode::strcat(aUStack_100, pUStack_608);
		sub_6FAE4C60(pDStack_604, local_614, 0x15, 0x16, (uint32_t*)(&iStack_61c), (uint32_t*)(&iStack_620), (uint32_t*)(&iStack_618));
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd89));
		Unicode::strcpy(aUStack_500, pUVar3);
		Unicode::strcat(aUStack_500, pUVar2);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_61c);
		Unicode::win2Unicode(local_300, acStack_600, 5);
		if (iStack_618 != 0)
		{
			sub_6FB20430((short*)local_300, '\x03');
		}
		Unicode::strcat(aUStack_500, local_300);
		Unicode::strcat(aUStack_500, pUVar2);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd88));
		Unicode::strcat(aUStack_500, pUVar3);
		SStrPrintf(acStack_600, 0x100, "%i", iStack_620);
		Unicode::win2Unicode(local_300, acStack_600, 5);
		Unicode::strcat(aUStack_500, pUVar2);
		Unicode::strcat(aUStack_500, local_300);
		Unicode::strcat(aUStack_500, pUStack_608);
		sub_6FB20430((short*)aUStack_100, '\0');
		sub_6FB20430((short*)aUStack_500, '\0');
		Unicode::strcpy(pUnicode, aUStack_100);
	}
	(*pcVar9)();
	iStack_618 = 0;
	iVar7 = STATLIST_GetUnitStatBonus(local_614, 0x12, 0);
	if ((((iVar7 != 0) || (iVar7 = STATLIST_GetUnitStatBonus(local_614, 0x11, 0), iVar7 != 0)) ||
	        (iVar7 = STATLIST_GetUnitStatBonus(local_614, 0x9f, 0), iVar7 != 0)) ||
	    (iVar7 = STATLIST_GetUnitStatBonus(local_614, 0xa0, 0), iVar7 != 0))
	{
		iStack_618 = 1;
	}
	iVar7 = ITEMS_CheckIfThrowable(local_614);
	if (iVar7 != 0)
	{
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd8b));
		Unicode::strcpy(aUStack_500, pUVar2);
		sub_6FB20430((short*)aUStack_500, '\0');
		sub_6FAE4C60(pDStack_604, local_614, 0x9f, 0xa0, (uint32_t*)(&iStack_61c), (uint32_t*)(&iStack_620), (uint32_t*)(&iStack_618));
		SStrPrintf(acStack_600, 0x100, "%i", iStack_61c);
		(*pcVar8)(9);
		sub_6FB20430(asStack_304, -(iStack_61c != 0) & 3);
		(*pcVar9)();
		(*pcVar9)();
		(*pcVar9)();
		D2LANG_GetStringFromTblIndex(0xd88);
		(*pcVar9)();
		SStrPrintf((char*)&pDStack_604, 0x100, "%i", unaff_EBX);
		(*pcVar8)(9);
		sub_6FB20430(asStack_308, -(iStack_620 != 0) & 3);
		(*pcVar9)();
		(*pcVar9)();
		(*pcVar9)();
		(*pcVar9)();
	}
}

//D2Client.0x6FAE4C60
void __fastcall sub_6FAE4C60(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, int a3, int a4, uint32_t* a5, uint32_t* a6, uint32_t* a7)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint64_t uVar6;
	D2UnitStrc* local_10;
	int local_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	*a5 = 1;
	*a6 = 2;
	if ((pUnit != nullptr) && (pUnit2 != nullptr))
	{
		local_c = 0;
		pDVar1 = STATLIST_GetOwner(gpUnit_6FBB58F0, &local_c);
		uStack_4 = (uint32_t)(pDVar1 != nullptr);
		local_10 = pUnit;
		if ((pDVar1 != nullptr) && (local_10 = pUnit, pDVar1 != pUnit))
		{
			local_10 = pDVar1;
		}
		STATLIST_MergeStatLists(local_10, pUnit2, 1);
		iVar3 = a3;
		uStack_8 = STATLIST_UnitGetStatValue(pUnit2, a3, 0);
		iVar4 = a4;
		uVar2 = STATLIST_UnitGetStatValue(pUnit2, a4, 0);
		if (uStack_4 == 0)
		{
			STATLIST_ExpireUnitStatlist(local_10, pUnit2);
		}
		else
		{
			STATLIST_MergeStatLists(local_10, pUnit2, local_c);
		}
		iVar3 = STATLIST_GetUnitBaseStat(pUnit2, iVar3, 0);
		iVar4 = STATLIST_GetUnitBaseStat(pUnit2, iVar4, 0);
		if ((iVar3 < (int)uStack_8) || (iVar4 < (int)uVar2))
		{
			*a7 = 1;
		}
		if ((int)uVar2 <= (int)uStack_8)
		{
			uVar2 = uStack_8;
		}
		iVar3 = STATLIST_UnitGetStatValue(pUnit2, 0x110, 0);
		if ((((iVar3 != 0) && (0x110 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))) &&
		        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) != -0x15840)) &&
		    (local_10->pDrlgAct != nullptr))
		{
			a3 = 0;
			iVar4 = ENVIRONMENT_GetPeriodOfDayFromAct(local_10->pDrlgAct, &a3);
			iVar3 = ITEMMODS_GetByTimeAdjustment(iVar3, iVar4, a3, nullptr, nullptr, nullptr);
			uVar2 = uVar2 + iVar3;
			if (iVar3 != 0)
			{
				*a7 = 1;
			}
		}
		iVar3 = STATLIST_UnitGetStatValue(pUnit2, 0x111, 0);
		if (((iVar3 != 0) && (0x111 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))) &&
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) != -0x15984 &&
		        (local_10->pDrlgAct != nullptr))))
		{
			a3 = 0;
			iVar4 = ENVIRONMENT_GetPeriodOfDayFromAct(local_10->pDrlgAct, &a3);
			uVar5 = ITEMMODS_GetByTimeAdjustment(iVar3, iVar4, a3, nullptr, nullptr, nullptr);
			if ((int)uVar2 < 0x100001)
			{
				if ((int)uVar5 < 0x10001)
				{
					iVar3 = (int)(uVar5 * uVar2) / 100;
				}
				else if ((int)(uVar5 & 0xfffffff0) < 0x640)
				{
					uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar3 = (int)uVar6;
				}
				else
				{
					iVar3 = ((int)uVar5 / 100) * uVar2;
				}
			}
			else if ((int)(uVar2 & 0xfffffff0) < 0x640)
			{
				uVar6 = D2C_alldiv((uint32_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar5 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar3 = (int)uVar6;
			}
			else
			{
				iVar3 = ((int)uVar2 / 100) * uVar5;
			}
			uVar2 = uVar2 + iVar3;
			if (uVar5 != 0)
			{
				*a7 = 1;
			}
		}
		*a5 = uStack_8;
		*a6 = uVar2;
	}
}

//D2Client.0x6FAE4EE0
void __fastcall sub_6FAE4EE0(D2UnitStrc* pUnit2, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	int iVar1;
	D2UnitStrc* pUnit;
	D2SkillStrc* pSkill;
	int iVar2;
	Unicode* pUVar3;
	Unicode aUStack_260[32];
	char acStack_220[32];
	Unicode aUStack_200[256];

	iVar1 = STATLIST_UnitGetStatValue(pUnit2, 0x14, 0);
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		iVar2 = pUnit->dwClassId;
		if ((iVar2 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc8) <= iVar2))
		{
			iVar2 = 0;
		}
		else
		{
			iVar2 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbc4) + iVar2 * 0xc4;
		}
		iVar1 = iVar1 + (uint32_t) * (uint8_t*)(iVar2 + 0x49);
		pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0x75);
		if ((pSkill != nullptr) && (iVar2 = STATES_CheckState(pUnit, 0x65), iVar2 != 0))
		{
			iVar2 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			iVar2 = D2COMMON_11036_GetMonCurseResistanceSubtraction(iVar2, 0x75);
			iVar1 = iVar1 + iVar2;
		}
		if (0x4b < iVar1)
		{
			iVar1 = 0x4b;
			goto LAB_6fae4f7b;
		}
	}
	if (iVar1 == 0)
	{
		return;
	}
LAB_6fae4f7b:
	SStrPrintf(acStack_220, 0x20, "%d%%\n", iVar1);
	Unicode::win2Unicode(aUStack_260, acStack_220, 0x20);
	if ((int)(uint32_t)pItemsTxtRecord->nBlock < iVar1)
	{
		sub_6FB20430((short*)aUStack_260, '\x03');
	}
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b0a));
	Unicode::strcpy(aUStack_200, pUVar3);
	sub_6FB20430((short*)aUStack_200, '\0');
	Unicode::strcpy(pUnicode, aUStack_200);
	Unicode::strcat(pUnicode, aUStack_260);
}

//D2Client.0x6FAE5040
void __fastcall sub_6FAE5040(D2UnitStrc* pUnit2, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	Unicode* pUVar1;
	Unicode* a2;
	D2UnitStrc* pUnit;
	D2SkillStrc* pSkill;
	int iVar2;
	Unicode* pUVar3;
	D2ItemsTxt* pDVar4;
	int iVar5;
	uint32_t uStack_2c;
	short sStack_28;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	pDVar4 = (D2ItemsTxt*)(uint32_t)pItemsTxtRecord->nMinDam;
	uStack_2c = (uint32_t)pItemsTxtRecord->nMaxDam;
	iVar5 = ITEMS_CheckItemTypeId(pUnit2, 0x33);
	pItemsTxtRecord = pDVar4;
	if (iVar5 == 0)
	{
		iVar5 = ITEMS_CheckItemTypeId(pUnit2, 0xf);
		if (iVar5 == 0)
		{
			return;
		}
		sStack_28 = 0x5516;
	}
	else
	{
		sStack_28 = 0xd8c;
		pUnit = CUNIT_GetPlayer();
		pSkill = SKILLS_GetHighestLevelSkillFromUnitAndId(pUnit, 0x75);
		if ((pSkill != nullptr) && (iVar5 = STATES_CheckState(pUnit, 0x65), iVar5 != 0))
		{
			iVar5 = SKILLS_GetSkillLevel(pUnit, pSkill, 1);
			iVar2 = SKILLS_GetMinPhysDamage(pUnit, 0x75, iVar5, 1);
			iVar5 = SKILLS_GetMaxPhysDamage(pUnit, 0x75, iVar5, 1);
			uStack_2c = uStack_2c + (iVar5 >> 8);
			pItemsTxtRecord = (D2ItemsTxt*)(pDVar4->szFlippyFile + (iVar2 >> 8));
		}
	}
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(sStack_28));
	Unicode::strcpy(pUnicode, pUVar3);
	SStrPrintf(acStack_20, 10, "%i", pItemsTxtRecord);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_14);
	Unicode::strcat(pUnicode, pUVar1);
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd88));
	Unicode::strcat(pUnicode, pUVar3);
	SStrPrintf(acStack_20, 10, "%i", uStack_2c);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_14);
	Unicode::strcat(pUnicode, a2);
}

//D2Client.0x6FAE51D0
void __fastcall sub_6FAE51D0(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	int iVar4;
	Unicode* pUVar5;
	int iVar6;
	bool bVar7;
	uint64_t uVar8;
	int iStack_30;
	D2UnitStrc* local_2c;
	Unicode* pUStack_28;
	Unicode* pUStack_24;
	char acStack_20[12];
	Unicode local_14[10];

	if (pUnit != nullptr)
	{
		pUVar5 = local_14;
		iVar6 = 10;
		local_2c = pUnit2;
		do
		{
			pUVar5 = pUVar5 + 1;
			iVar6 = iVar6 + -1;
		} while (iVar6 != 0);
		pUStack_28 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
		pUStack_24 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
		iStack_30 = 0;
		pDVar1 = STATLIST_GetOwner(gpUnit_6FBB58F0, &iStack_30);
		if ((pDVar1 != nullptr) && (pUnit != pDVar1))
		{
			pUnit = pDVar1;
		}
		STATLIST_MergeStatLists(pUnit, gpUnit_6FBB58F0, 1);
		uVar2 = STATLIST_GetDefenseFromUnit(gpUnit_6FBB58F0);
		if (pDVar1 == nullptr)
		{
			STATLIST_ExpireUnitStatlist(pUnit, gpUnit_6FBB58F0);
		}
		else
		{
			STATLIST_MergeStatLists(pDVar1, gpUnit_6FBB58F0, iStack_30);
		}
		pDVar1 = local_2c;
		uVar3 = STATLIST_GetUnitBaseStat(local_2c, 0x1f, 0);
		bVar7 = uVar3 != uVar2;
		iVar6 = STATLIST_UnitGetStatValue(pDVar1, 0x10c, 0);
		if ((((iVar6 != 0) && (0x10c < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))) &&
		        (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) != -0x15330)) &&
		    (pUnit->pDrlgAct != nullptr))
		{
			local_2c = nullptr;
			iVar4 = ENVIRONMENT_GetPeriodOfDayFromAct(pUnit->pDrlgAct, (int*)&local_2c);
			iVar6 = ITEMMODS_GetByTimeAdjustment(iVar6, iVar4, (int)local_2c, nullptr, nullptr, nullptr);
			uVar2 = uVar2 + iVar6;
			if (iVar6 != 0)
			{
				bVar7 = true;
			}
		}
		iVar6 = STATLIST_UnitGetStatValue(pDVar1, 0x10d, 0);
		if (((iVar6 != 0) && (0x10d < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbd4))) &&
		    ((*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xbcc) != -0x15474 &&
		        (pUnit->pDrlgAct != nullptr))))
		{
			local_2c = nullptr;
			iVar4 = ENVIRONMENT_GetPeriodOfDayFromAct(pUnit->pDrlgAct, (int*)&local_2c);
			uVar3 = ITEMMODS_GetByTimeAdjustment(iVar6, iVar4, (int)local_2c, nullptr, nullptr, nullptr);
			if ((int)uVar2 < 0x100001)
			{
				if ((int)uVar3 < 0x10001)
				{
					iVar6 = (int)(uVar3 * uVar2) / 100;
				}
				else if ((int)(uVar3 & 0xfffffff0) < 0x640)
				{
					uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
					    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
					    100, 0);
					iVar6 = (int)uVar8;
				}
				else
				{
					iVar6 = ((int)uVar3 / 100) * uVar2;
				}
			}
			else if ((int)(uVar2 & 0xfffffff0) < 0x640)
			{
				uVar8 = D2C_alldiv((uint32_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2),
				    (uint32_t)((uint64_t)((int64_t)(int)uVar3 * (int64_t)(int)uVar2) >> 0x20),
				    100, 0);
				iVar6 = (int)uVar8;
			}
			else
			{
				iVar6 = ((int)uVar2 / 100) * uVar3;
			}
			uVar2 = uVar2 + iVar6;
			if (uVar3 != 0)
			{
				bVar7 = true;
			}
		}
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd85));
		Unicode::strcpy(pUnicode, pUVar5);
		Unicode::strcat(pUnicode, pUStack_28);
		SStrPrintf(acStack_20, 10, "%i", uVar2);
		Unicode::win2Unicode(local_14, acStack_20, 9);
		if (bVar7)
		{
			sub_6FB20430((short*)local_14, '\x03');
		}
		Unicode::strcat(pUnicode, local_14);
		Unicode::strcat(pUnicode, pUStack_24);
	}
}

//D2Client.0x6FAE54B0
void __fastcall sub_6FAE54B0(D2UnitStrc* pUnit, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	int iVar2;
	char acStack_20[12];
	Unicode local_14[10];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x46, 0);
	if ((iVar2 < 1) && (iVar2 = ITEMS_GetTotalMaxStack(pUnit), iVar2 < 1))
	{
		return;
	}
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd86));
	Unicode::strcpy(pUnicode, a2_00);
	iVar2 = STATLIST_UnitGetStatValue(pUnit, 0x46, 0);
	SStrPrintf(acStack_20, 10, "%ld", iVar2);
	Unicode::win2Unicode(local_14, acStack_20, 9);
	Unicode::strcat(pUnicode, pUVar1);
	Unicode::strcat(pUnicode, local_14);
	Unicode::strcat(pUnicode, a2);
}

//D2Client.0x6FAE5570
void __fastcall sub_6FAE5570(D2UnitStrc* pUnit, Unicode* pUnicode, D2ItemsTxt* pItemsTxtRecord)
{
	Unicode* pUVar1;
	Unicode* a2;
	Unicode* a2_00;
	D2UnitStrc* pDVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	Unicode* a2_01;
	int* piVar7;
	int iStack_218;
	Unicode aUStack_200[256];

	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9c));
	pDVar2 = CUNIT_GetPlayer();
	iVar3 = ITEMS_GetWeaponAttackSpeed(pDVar2, pUnit);
	iVar4 = STATLIST_GetUnitStatBonus(pUnit, 0x5d, 0);
	if (iVar3 < 0x1c)
	{
		if (iVar3 < 10)
		{
			iStack_218 = 1;
		}
		else
		{
			pDVar2 = CUNIT_GetPlayer();
			iVar6 = ITEMS_CheckItemTypeId(pUnit, 0x23);
			if ((iVar6 == 0) && (iVar6 = ITEMS_CheckItemTypeId(pUnit, 0x1b), iVar6 == 0))
			{
				iVar6 = 0;
			}
			else
			{
				iVar6 = 1;
			}
			if (pDVar2 == nullptr)
			{
				iVar5 = -1;
			}
			else
			{
				iVar5 = pDVar2->dwClassId;
			}
			iStack_218 = *(int*)(byte_6FB79360 +
			                     (iVar3 * 5 + -0x32 + *(int*)(byte_6FB794C8 + (iVar6 + iVar5 * 2) * 4)) * 4);
		}
	}
	else
	{
		iStack_218 = 5;
	}
	iVar3 = 0;
	piVar7 = (int*)(&dword_6FB792D8);
	do
	{
		iVar6 = ITEMS_CheckItemTypeId(pUnit, *piVar7);
		if (iVar6 != 0)
		{
			if (-1 < iVar3)
			{
				a2_01 = (Unicode*)(D2LANG_GetStringFromTblIndex((&word_6FB792DC)[iVar3 * 3]));
				Unicode::strcpy(pUnicode, a2_01);
				Unicode::strcat(pUnicode, pUVar1);
				Unicode::strcat(pUnicode, a2_00);
				Unicode::strcat(pUnicode, pUVar1);
			}
			break;
		}
		piVar7 = (int*)((int)piVar7 + 6);
		iVar3 = iVar3 + 1;
	} while ((int)piVar7 < (int)&tbl_6FB79332);
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(byte_6FB79338 + iStack_218 * 6)));
	Unicode::strcpy(aUStack_200, pUVar1);
	if (iVar4 != 0)
	{
		sub_6FB20430((short*)aUStack_200, '\x03');
	}
	Unicode::strcat(pUnicode, aUStack_200);
	Unicode::strcat(pUnicode, a2);
}

//D2Client.0x6FAE5710
void __fastcall sub_6FAE5710(D2UnitStrc* pUnit2, Unicode* pUnicode, int a3)
{
	D2UnitStrc* pUnit;
	Unicode* pUVar1;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	code* pcVar5;
	int iStack_430;
	char acStack_420[12];
	Unicode aUStack_414[10];
	Unicode aUStack_400[512];

	if (pUnit2 == nullptr)
	{
		return;
	}
	if (a3 == 0)
	{
		return;
	}
	if (*(char*)(a3 + 0xb4) == '\0')
	{
		return;
	}
	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		return;
	}
	if (*(short*)(a3 + 0xb6) == 0x1506)
	{
		return;
	}
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	switch (*(uint8_t*)(a3 + 0xb4))
	{
	case 1:
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(a3 + 0xb6)));
		Unicode::strcpy(pUnicode, pUVar1);
		Unicode::strcat(pUnicode, pUVar2);
		return;
	case 2:
		iVar3 = ITEMMODS_EvaluateItemFormula(pUnit, pUnit2, *(uint32_t*)(a3 + 0xa4));
		switch (*(uint16_t*)(a3 + 0x9e))
		{
		case 6:
		case 0x4a:
			iVar3 = ITEMS_GetBonusLifeBasedOnClass(pUnit, iVar3);
			break;
		case 8:
		case 0x1a:
			iVar3 = ITEMS_GetBonusManaBasedOnClass(pUnit, iVar3);
		}
		break;
	case 3:
		iVar3 = ITEMMODS_EvaluateItemFormula(pUnit, pUnit2, *(uint32_t*)(a3 + 0xa4));
		break;
	case 4:
		iVar3 = ITEMMODS_EvaluateItemFormula(pUnit, pUnit2, *(uint32_t*)(a3 + 0xa4));
		pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(a3 + 0xb6)));
		Unicode::sprintf(0x200, aUStack_400, pUVar1, iVar3);
		pcVar5 = (code*)(((uint8_t*)&Unicode::strcat));
		goto LAB_6fae590c;
	default:
		goto switchD_6fae5793_default;
	}
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(a3 + 0xb6)));
	Unicode::strcpy(pUnicode, pUVar2);
	SStrPrintf(acStack_420, 10, "%ld", iVar3);
	Unicode::win2Unicode(aUStack_414, acStack_420, 9);
	pcVar5 = (code*)(((uint8_t*)&Unicode::strcat));
	Unicode::strcat(pUnicode, pUVar1);
LAB_6fae590c:
	(*pcVar5)();
	(*pcVar5)();
switchD_6fae5793_default:
}

//D2Client.0x6FAE5990
uint32_t __fastcall sub_6FAE5990(D2InventoryStrc* pInventory, int a2)
{
	short* psVar1;
	uint8_t bVar2;
	D2UnitStrc* pItem;
	D2UnitStrc* pItem_00;
	int iVar3;

	pItem = INVENTORY_GetFirstItem(pInventory);
	while (true)
	{
		if (pItem == nullptr)
		{
			return 0;
		}
		pItem_00 = INVENTORY_UnitIsItem(pItem);
		iVar3 = ITEMS_GetItemQuality(pItem_00);
		if ((((iVar3 == 5) &&
		         ((((bVar2 = ITEMS_GetInvPage(pItem_00), bVar2 == 0 || (bVar2 == 3)) || (bVar2 == 4)) ||
		             (bVar2 == 0xff)))) &&
		        ((((iVar3 = INVENTORY_GetItemNodePage(pItem), iVar3 == 1 || (iVar3 == 3)) || (iVar3 == 4)) && ((iVar3 = ITEMS_GetFileIndex(pItem_00), -1 < iVar3 &&
		                                                                                                                                                  (iVar3 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c))))))) &&
		    ((psVar1 = (short*)(*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + iVar3 * 0x1b8),
		        psVar1 != nullptr && (*psVar1 == a2))))
			break;
		pItem = INVENTORY_GetNextItem(pItem);
	}
	return (uint32_t)(pItem_00);
}

//D2Client.0x6FAE5A40
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FAE5A40()
{
	Unicode* pUVar1;
	Unicode* pUVar2;
	Unicode* in_ECX;
	int iVar3;
	Unicode* in_EDX;
	int local_188;
	int iStack_184;
	Unicode local_180;
	Unicode local_17e[63];
	Unicode aUStack_100[128];

	local_180.ch = 0;
	pUVar1 = local_17e;
	for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*(uint32_t*)pUVar1 = 0;
		pUVar1 = pUVar1 + 2;
	}
	pUVar1->ch = 0;
	pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
	Unicode::strcpy(in_EDX, in_ECX);
	if (dword_6FBB58EC == 4)
	{
		iVar3 = ITEMS_CheckItemFlag(gpUnit_6FBB58F0, 0x400000, __LINE__, __FILE__);
		if (iVar3 != 0)
		{
			pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58da));
			Unicode::strcpy(aUStack_100, pUVar2);
			Unicode::strcat(in_EDX, pUVar1);
			pUVar2 = (Unicode*)sub_6FB20430((short*)aUStack_100, '\x01');
			Unicode::strcat(in_EDX, pUVar2);
		}
	}
	iVar3 = sub_6FAFB200(gpUnit_6FBB58F0, dword_6FB7928C, &iStack_184, &local_180, 0x40);
	if (iVar3 != 0)
	{
		if (local_180.ch != 0)
		{
			Unicode::strcat(in_EDX, pUVar1);
		}
		Unicode::strcat(in_EDX, &local_180);
		return;
	}
	if (dword_6FBB58EC != 4)
	{
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd05));
		Unicode::strcpy(aUStack_100, pUVar2);
		Unicode::strcat(in_EDX, pUVar1);
		pUVar1 = (Unicode*)sub_6FB20430((short*)aUStack_100, '\x01');
		Unicode::strcat(in_EDX, pUVar1);
	}
}

//D2Client.0x6FAE5BD0
D2UnitStrc* __fastcall sub_6FAE5BD0(int a1, int a2, uint32_t a3)
{
	uint64_t uVar1;

	if (a3 == 0)
	{
		return nullptr;
	}
	if (a1 < 0x100001)
	{
		if (a2 < 0x10001)
		{
			return (D2UnitStrc*)((a1 * a2) / (int)a3);
		}
		if ((int)a3 <= a2 >> 4)
		{
			return (D2UnitStrc*)((a2 / (int)a3) * a1);
		}
	}
	else if ((int)a3 <= a1 >> 4)
	{
		return (D2UnitStrc*)((a1 / (int)a3) * a2);
	}
	uVar1 = D2C_alldiv((uint32_t)((int64_t)a1 * (int64_t)a2),
	    (uint32_t)((uint64_t)((int64_t)a1 * (int64_t)a2) >> 0x20), a3,
	    (int)a3 >> 0x1f);
	return (D2UnitStrc*)uVar1;
}

//D2Client.0x6FAE5C50
int __fastcall sub_6FAE5C50(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc10)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc0c) + a1 * 0x128;
	}
	return 0;
}

//D2Client.0x6FAE5C80
int __fastcall sub_6FAE5C80(int a1)
{
	if ((-1 < a1) && (a1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc1c)))
	{
		return *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc18) + a1 * 0x1b8;
	}
	return 0;
}

//D2Client.0x6FAE5CB0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAE5CB0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3)
{
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	DWORD DVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t extraout_ECX_05;
	uint32_t extraout_ECX_06;
	uint32_t extraout_ECX_07;
	uint32_t extraout_ECX_08;
	uint32_t extraout_ECX_09;
	uint32_t extraout_ECX_10;
	uint32_t uVar7;
	uint32_t extraout_ECX_11;
	uint32_t extraout_ECX_12;
	uint32_t extraout_ECX_13;
	uint32_t extraout_ECX_14;
	uint32_t extraout_ECX_15;
	uint32_t extraout_ECX_16;
	uint32_t extraout_ECX_17;
	uint32_t extraout_ECX_18;
	uint32_t uVar6;
	uint32_t extraout_ECX_19;
	uint32_t extraout_ECX_20;
	uint32_t extraout_ECX_21;
	uint32_t extraout_ECX_22;
	uint32_t extraout_ECX_23;
	uint32_t extraout_ECX_24;
	uint32_t extraout_ECX_25;
	uint32_t extraout_ECX_26;
	uint32_t extraout_ECX_27;
	uint32_t extraout_ECX_28;
	uint32_t extraout_ECX_29;
	uint32_t extraout_ECX_30;
	uint32_t extraout_ECX_31;
	uint32_t extraout_ECX_32;
	uint32_t extraout_ECX_33;
	uint32_t extraout_ECX_34;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	float fVar11;
	float fVar12;
	int iVar13;

	uVar10 = 0;
	pItem = INVENTORY_GetCursorItem(pInventory);
	pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
	iVar3 = sub_6FB57CC0();
	if (iVar3 == 6)
	{
		pDVar4 = sub_6FB575E0();
		if (((pDVar4 != nullptr) && (pDVar2 != nullptr)) &&
		    (iVar3 = sub_6FB2FB90(pDVar2), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX;
			if ((iVar3 == 0) || (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_00, iVar3 == 1))
			{
			LAB_6fae5d59:
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x27), pDVar2->dwUnitId, pDVar4->dwUnitId);
			LAB_6fae5dd1:
				sub_6FB2FB30(pDVar2);
				uVar10 = 1;
			}
			else
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 == 0)
				{
					DVar5 = GetTickCount();
					if (0xfa < DVar5 - byte_6FBB3870)
					{
						byte_6FBB3870 = GetTickCount();
						uVar6 = extraout_ECX_02;
						goto LAB_6fae5d59;
					}
				}
				else
				{
					sub_6FB1FF00(extraout_ECX_01);
				}
			}
		}
	}
	else
	{
		iVar3 = sub_6FB57CC0();
		if (((iVar3 == 8) && (pDVar2 != nullptr)) &&
		    (iVar3 = sub_6FB2FB90(pDVar2), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_03;
			if ((iVar3 == 0) || (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_04, iVar3 == 1))
			{
			LAB_6fae5dc7:
				sub_6FAADA20(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x4c), pDVar2->dwUnitId);
				goto LAB_6fae5dd1;
			}
			iVar3 = sub_6FB1FFF0();
			if (iVar3 == 0)
			{
				DVar5 = GetTickCount();
				if (0xfa < DVar5 - byte_6FBB3870)
				{
					byte_6FBB3870 = GetTickCount();
					uVar6 = extraout_ECX_06;
					goto LAB_6fae5dc7;
				}
			}
			else
			{
				sub_6FB1FF00(extraout_ECX_05);
			}
		}
	}
	iVar3 = D2Common_10299(pUnit, a3, pItem, 0);
	switch (iVar3)
	{
	case 0:
		if (pItem != nullptr)
		{
			iVar3 = D2Common_10299(pUnit, a3, pItem, 1);
			if (iVar3 != 0)
			{
				iVar3 = ITEMS_GetClassOfClassSpecificItem(pItem);
				if (iVar3 == 7)
				{
				LAB_6fae5e2c:
					sub_6FB514E0(pUnit, 0x14);
					return 1;
				}
				if (pUnit == nullptr)
				{
					iVar13 = -1;
				}
				else
				{
					iVar13 = pUnit->dwClassId;
				}
				if (iVar3 == iVar13)
					goto LAB_6fae5e2c;
			}
			sub_6FB514E0(pUnit, 0x13);
		}
		return 1;
	case 1:
		iVar3 = sub_6FB2FB90(pItem);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_07;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_08, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_09);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_10;
		}
		uVar7 = (uint32_t)((uint32_t)uVar6 >> 8);
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
			uVar8 = 4;
			uVar10 = CONCAT31(uVar7, 0x1a);
		}
		else
		{
			uVar9 = pItem->dwUnitId;
			uVar8 = 4;
			uVar10 = CONCAT31(uVar7, 0x1a);
		}
		goto LAB_6fae62df;
	case 2:
		iVar3 = sub_6FB2FB90(pItem);
		if ((iVar3 == 0) && (iVar3 = sub_6FB2FB90(pDVar1), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_11;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_12, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_13);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_14;
			}
			if (pItem == nullptr)
			{
				uVar8 = 0xffffffff;
			}
			else
			{
				uVar8 = pItem->dwUnitId;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1b), uVar8, 4);
			sub_6FB2FB30(pDVar1);
			sub_6FB2FB30(pItem);
			iVar13 = 0;
			fVar12 = 0.0;
			fVar11 = 0.0;
			iVar3 = sub_6FB2E590(pItem);
			sub_6FB55820(iVar3, nullptr, fVar11, fVar12, iVar13);
			dword_6FBB58E8 = 1;
			return 1;
		}
		break;
	case 3:
		switch (dword_6FBB58EC)
		{
		case 0:
		case 1:
		case 2:
		case 0xb:
		case 0xc:
		case 0xe:
		case 0xf:
		case 0x13:
			iVar3 = sub_6FB2FB90(pDVar2);
			if (iVar3 != 0)
			{
				return uVar10;
			}
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_15;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_16, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_17);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_18;
			}
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1c), 4);
		LAB_6fae6020:
			sub_6FB2FB30(pDVar2);
			dword_6FBB58E8 = 1;
			return 1;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 0xd:
		case 0x10:
		case 0x11:
		case 0x12:
		default:
			if (0x12 < dword_6FBB58EC)
			{
				return uVar10;
			}
		}
		goto joined_r0x6fae6073;
	case 4:
		pDVar2 = pDVar1;
		if (dword_6FBB58EC != 4)
		{
			iVar3 = sub_6FB2FB90(pDVar1);
			if (iVar3 != 0)
			{
				return uVar10;
			}
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_19;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_20, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_21);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_22;
			}
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1c), 5);
			goto LAB_6fae6020;
		}
	joined_r0x6fae6073:
		if ((pDVar2 != nullptr) &&
		    (iVar3 = sub_6FAFA260(pUnit, pDVar2, 1, dword_6FBB388C, dword_6FBB3894, 0, 0, 0), iVar3 != 0))
		{
			dword_6FBB58EC = 5;
			sub_6FB575B0(nullptr);
			return uVar10;
		}
		break;
	case 5:
		iVar3 = sub_6FB2FB90(pDVar2);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_23;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_24, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_25);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_26;
		}
		uVar7 = (uint32_t)((uint32_t)uVar6 >> 8);
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
			uVar8 = 4;
			uVar10 = CONCAT31(uVar7, 0x1d);
		}
		else
		{
			uVar9 = pItem->dwUnitId;
			uVar8 = 4;
			uVar10 = CONCAT31(uVar7, 0x1d);
		}
		goto LAB_6fae62df;
	case 6:
		iVar3 = sub_6FB2FB90(pItem);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_31;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_32, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_33);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_34;
		}
		if (dword_6FBB58EC == 0xb)
		{
			return uVar10;
		}
		if (pDVar2 == nullptr)
		{
			uVar8 = 0xffffffff;
		}
		else
		{
			uVar8 = pDVar2->dwUnitId;
		}
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
		}
		else
		{
			uVar9 = pItem->dwUnitId;
		}
		uVar10 = CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x21);
	LAB_6fae62df:
		sub_6FAADA40(uVar10, uVar9, uVar8);
		sub_6FB2FB30(pItem);
		iVar13 = 0;
		fVar12 = 0.0;
		fVar11 = 0.0;
		iVar3 = sub_6FB2E590(pItem);
		sub_6FB55820(iVar3, nullptr, fVar11, fVar12, iVar13);
		uVar10 = 1;
		break;
	case 7:
		iVar3 = sub_6FB2FB90(pItem);
		if (((iVar3 == 0) && (iVar3 = sub_6FB2FB90(pDVar2), iVar3 == 0)) &&
		    (iVar3 = sub_6FB2FB90(pDVar1), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_27;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_28, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_29);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_30;
			}
			if (pItem == nullptr)
			{
				uVar8 = 0xffffffff;
			}
			else
			{
				uVar8 = pItem->dwUnitId;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1e), uVar8, 4);
			sub_6FB2FB30(pItem);
			sub_6FB2FB30(pDVar2);
			sub_6FB2FB30(pDVar1);
			return 1;
		}
	}
	return uVar10;
}

//D2Client.0x6FAE6360
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAE6360(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3)
{
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	DWORD DVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t extraout_ECX_05;
	uint32_t extraout_ECX_06;
	uint32_t extraout_ECX_07;
	uint32_t extraout_ECX_08;
	uint32_t extraout_ECX_09;
	uint32_t extraout_ECX_10;
	uint32_t uVar7;
	uint32_t extraout_ECX_11;
	uint32_t extraout_ECX_12;
	uint32_t extraout_ECX_13;
	uint32_t extraout_ECX_14;
	uint32_t extraout_ECX_15;
	uint32_t extraout_ECX_16;
	uint32_t extraout_ECX_17;
	uint32_t extraout_ECX_18;
	uint32_t uVar6;
	uint32_t extraout_ECX_19;
	uint32_t extraout_ECX_20;
	uint32_t extraout_ECX_21;
	uint32_t extraout_ECX_22;
	uint32_t extraout_ECX_23;
	uint32_t extraout_ECX_24;
	uint32_t extraout_ECX_25;
	uint32_t extraout_ECX_26;
	uint32_t extraout_ECX_27;
	uint32_t extraout_ECX_28;
	uint32_t extraout_ECX_29;
	uint32_t extraout_ECX_30;
	uint32_t extraout_ECX_31;
	uint32_t extraout_ECX_32;
	uint32_t extraout_ECX_33;
	uint32_t extraout_ECX_34;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	float fVar11;
	float fVar12;
	int iVar13;

	uVar10 = 0;
	pItem = INVENTORY_GetCursorItem(pInventory);
	pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
	pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
	iVar3 = sub_6FB57CC0();
	if (iVar3 == 6)
	{
		pDVar4 = sub_6FB575E0();
		if (((pDVar4 != nullptr) && (pDVar1 != nullptr)) &&
		    (iVar3 = sub_6FB2FB90(pDVar1), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX;
			if ((iVar3 == 0) || (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_00, iVar3 == 1))
			{
			LAB_6fae6405:
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x27), pDVar1->dwUnitId, pDVar4->dwUnitId);
			LAB_6fae6477:
				sub_6FB2FB30(pDVar1);
				uVar10 = 1;
			}
			else
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 == 0)
				{
					DVar5 = GetTickCount();
					if (0xfa < DVar5 - byte_6FBB3870)
					{
						byte_6FBB3870 = GetTickCount();
						uVar6 = extraout_ECX_02;
						goto LAB_6fae6405;
					}
				}
				else
				{
					sub_6FB1FF00(extraout_ECX_01);
				}
			}
		}
	}
	else
	{
		iVar3 = sub_6FB57CC0();
		if (((iVar3 == 8) && (pDVar1 != nullptr)) &&
		    (iVar3 = sub_6FB2FB90(pDVar1), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_03;
			if ((iVar3 == 0) || (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_04, iVar3 == 1))
			{
			LAB_6fae646d:
				sub_6FAADA20(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x4c), pDVar1->dwUnitId);
				goto LAB_6fae6477;
			}
			iVar3 = sub_6FB1FFF0();
			if (iVar3 == 0)
			{
				DVar5 = GetTickCount();
				if (0xfa < DVar5 - byte_6FBB3870)
				{
					byte_6FBB3870 = GetTickCount();
					uVar6 = extraout_ECX_06;
					goto LAB_6fae646d;
				}
			}
			else
			{
				sub_6FB1FF00(extraout_ECX_05);
			}
		}
	}
	iVar3 = D2Common_10299(pUnit, a3, pItem, 0);
	switch (iVar3)
	{
	case 0:
		if (pItem != nullptr)
		{
			iVar3 = D2Common_10299(pUnit, a3, pItem, 1);
			if (iVar3 != 0)
			{
				iVar3 = ITEMS_GetClassOfClassSpecificItem(pItem);
				if (iVar3 == 7)
				{
				LAB_6fae64d6:
					sub_6FB514E0(pUnit, 0x14);
					return 1;
				}
				if (pUnit == nullptr)
				{
					iVar13 = -1;
				}
				else
				{
					iVar13 = pUnit->dwClassId;
				}
				if (iVar3 == iVar13)
					goto LAB_6fae64d6;
			}
			sub_6FB514E0(pUnit, 0x13);
		}
		return 1;
	case 1:
		iVar3 = sub_6FB2FB90(pItem);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_07;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_08, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_09);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_10;
		}
		uVar7 = (uint32_t)((uint32_t)uVar6 >> 8);
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
			uVar8 = 5;
			uVar10 = CONCAT31(uVar7, 0x1a);
		}
		else
		{
			uVar9 = pItem->dwUnitId;
			uVar8 = 5;
			uVar10 = CONCAT31(uVar7, 0x1a);
		}
		goto LAB_6fae698a;
	case 2:
		iVar3 = sub_6FB2FB90(pItem);
		if ((iVar3 == 0) && (iVar3 = sub_6FB2FB90(pDVar2), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_11;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_12, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_13);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_14;
			}
			if (pItem == nullptr)
			{
				uVar8 = 0xffffffff;
			}
			else
			{
				uVar8 = pItem->dwUnitId;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1b), uVar8, 5);
			sub_6FB2FB30(pDVar2);
			sub_6FB2FB30(pItem);
			iVar13 = 0;
			fVar12 = 0.0;
			fVar11 = 0.0;
			iVar3 = sub_6FB2E590(pItem);
			sub_6FB55820(iVar3, nullptr, fVar11, fVar12, iVar13);
			dword_6FBB58E8 = 1;
			return 1;
		}
		break;
	case 3:
		switch (dword_6FBB58EC)
		{
		case 0:
		case 1:
		case 2:
		case 0xb:
		case 0xc:
		case 0xe:
		case 0xf:
		case 0x13:
			iVar3 = sub_6FB2FB90(pDVar1);
			if (iVar3 != 0)
			{
				return uVar10;
			}
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_15;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_16, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_17);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_18;
			}
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1c), 5);
		LAB_6fae66ca:
			sub_6FB2FB30(pDVar1);
			dword_6FBB58E8 = 1;
			return 1;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 0xd:
		case 0x10:
		case 0x11:
		case 0x12:
		default:
			if (0x12 < dword_6FBB58EC)
			{
				return uVar10;
			}
		}
		goto joined_r0x6fae671d;
	case 4:
		pDVar1 = pDVar2;
		if (dword_6FBB58EC != 4)
		{
			iVar3 = sub_6FB2FB90(pDVar2);
			if (iVar3 != 0)
			{
				return uVar10;
			}
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_19;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_20, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_21);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_22;
			}
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1c), 4);
			goto LAB_6fae66ca;
		}
	joined_r0x6fae671d:
		if ((pDVar1 != nullptr) &&
		    (iVar3 = sub_6FAFA260(pUnit, pDVar1, 1, dword_6FBB388C, dword_6FBB3894, 0, 0, 0), iVar3 != 0))
		{
			dword_6FBB58EC = 5;
			sub_6FB575B0(nullptr);
			return uVar10;
		}
		break;
	case 5:
		iVar3 = sub_6FB2FB90(pDVar1);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_23;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_24, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_25);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_26;
		}
		uVar7 = (uint32_t)((uint32_t)uVar6 >> 8);
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
			uVar8 = 5;
			uVar10 = CONCAT31(uVar7, 0x1d);
		}
		else
		{
			uVar9 = pItem->dwUnitId;
			uVar8 = 5;
			uVar10 = CONCAT31(uVar7, 0x1d);
		}
		goto LAB_6fae698a;
	case 6:
		iVar3 = sub_6FB2FB90(pItem);
		if (iVar3 != 0)
		{
			return uVar10;
		}
		iVar3 = sub_6FAABFF0();
		uVar6 = extraout_ECX_31;
		if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_32, iVar3 != 1))
		{
			iVar3 = sub_6FB1FFF0();
			if (iVar3 != 0)
			{
				sub_6FB1FF00(extraout_ECX_33);
				return uVar10;
			}
			DVar5 = GetTickCount();
			if (DVar5 - byte_6FBB3870 < 0xfb)
			{
				return uVar10;
			}
			byte_6FBB3870 = GetTickCount();
			uVar6 = extraout_ECX_34;
		}
		if (dword_6FBB58EC == 0xb)
		{
			return uVar10;
		}
		if (pDVar1 == nullptr)
		{
			uVar8 = 0xffffffff;
		}
		else
		{
			uVar8 = pDVar1->dwUnitId;
		}
		if (pItem == nullptr)
		{
			uVar9 = 0xffffffff;
		}
		else
		{
			uVar9 = pItem->dwUnitId;
		}
		uVar10 = CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x21);
	LAB_6fae698a:
		sub_6FAADA40(uVar10, uVar9, uVar8);
		sub_6FB2FB30(pItem);
		iVar13 = 0;
		fVar12 = 0.0;
		fVar11 = 0.0;
		iVar3 = sub_6FB2E590(pItem);
		sub_6FB55820(iVar3, nullptr, fVar11, fVar12, iVar13);
		uVar10 = 1;
		break;
	case 7:
		iVar3 = sub_6FB2FB90(pItem);
		if (((iVar3 == 0) && (iVar3 = sub_6FB2FB90(pDVar2), iVar3 == 0)) &&
		    (iVar3 = sub_6FB2FB90(pDVar1), iVar3 == 0))
		{
			iVar3 = sub_6FAABFF0();
			uVar6 = extraout_ECX_27;
			if ((iVar3 != 0) && (iVar3 = sub_6FAABFF0(), uVar6 = extraout_ECX_28, iVar3 != 1))
			{
				iVar3 = sub_6FB1FFF0();
				if (iVar3 != 0)
				{
					sub_6FB1FF00(extraout_ECX_29);
					return uVar10;
				}
				DVar5 = GetTickCount();
				if (DVar5 - byte_6FBB3870 < 0xfb)
				{
					return uVar10;
				}
				byte_6FBB3870 = GetTickCount();
				uVar6 = extraout_ECX_30;
			}
			if (pItem == nullptr)
			{
				uVar8 = 0xffffffff;
			}
			else
			{
				uVar8 = pItem->dwUnitId;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar6 >> 8), 0x1e), uVar8, 5);
			sub_6FB2FB30(pItem);
			sub_6FB2FB30(pDVar2);
			sub_6FB2FB30(pDVar1);
			return 1;
		}
	}
	return uVar10;
}

//D2Client.0x6FAE6A00
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAE6A00(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, uint32_t a3)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	DWORD DVar4;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t extraout_ECX_05;
	uint32_t extraout_ECX_06;
	uint32_t extraout_ECX_07;
	uint32_t extraout_ECX_08;
	uint32_t extraout_ECX_09;
	uint32_t extraout_ECX_10;
	uint32_t extraout_ECX_11;
	uint32_t extraout_ECX_12;
	uint32_t extraout_ECX_13;
	uint32_t extraout_ECX_14;
	uint32_t uVar5;
	uint32_t extraout_ECX_15;
	uint32_t extraout_ECX_16;
	uint32_t extraout_ECX_17;
	uint32_t extraout_ECX_18;
	uint32_t uVar6;
	float fVar7;
	float fVar8;
	int iVar9;
	uint32_t local_4;

	local_4 = 0;
	pDVar1 = INVENTORY_GetCursorItem(pInventory);
	iVar2 = sub_6FB57CC0();
	if (iVar2 == 6)
	{
		pDVar1 = sub_6FB575E0();
		pDVar3 = INVENTORY_GetItemFromBodyLoc(pInventory, a3);
		if (((pDVar1 != nullptr) && (pDVar3 != nullptr)) &&
		    (iVar2 = sub_6FB2FB90(pDVar3), iVar2 == 0))
		{
			iVar2 = sub_6FAABFF0();
			uVar5 = extraout_ECX;
			if ((iVar2 != 0) && (iVar2 = sub_6FAABFF0(), uVar5 = extraout_ECX_00, iVar2 != 1))
			{
				iVar2 = sub_6FB1FFF0();
				if (iVar2 != 0)
				{
					sub_6FB1FF00(extraout_ECX_01);
					return 0;
				}
				DVar4 = GetTickCount();
				if (DVar4 - byte_6FBB3870 < 0xfb)
				{
					return 0;
				}
				byte_6FBB3870 = GetTickCount();
				uVar5 = extraout_ECX_02;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x27), pDVar3->dwUnitId, pDVar1->dwUnitId);
			sub_6FB2FB30(pDVar3);
			return 1;
		}
	}
	else
	{
		iVar2 = sub_6FB57CC0();
		if (iVar2 == 8)
		{
			pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, a3);
			if ((pDVar1 != nullptr) && (iVar2 = sub_6FB2FB90(pDVar1), iVar2 == 0))
			{
				iVar2 = sub_6FAABFF0();
				uVar5 = extraout_ECX_03;
				if ((iVar2 != 0) && (iVar2 = sub_6FAABFF0(), uVar5 = extraout_ECX_04, iVar2 != 1))
				{
					iVar2 = sub_6FB1FFF0();
					if (iVar2 != 0)
					{
						sub_6FB1FF00(extraout_ECX_05);
						return 0;
					}
					DVar4 = GetTickCount();
					if (DVar4 - byte_6FBB3870 < 0xfb)
					{
						return 0;
					}
					byte_6FBB3870 = GetTickCount();
					uVar5 = extraout_ECX_06;
				}
				sub_6FAADA20(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x4c), pDVar1->dwUnitId);
				sub_6FB2FB30(pDVar1);
				return 1;
			}
		}
		else
		{
			iVar2 = D2Common_10299(pUnit, a3, pDVar1, 0);
			switch (iVar2)
			{
			case 0:
				if (pDVar1 != nullptr)
				{
					iVar2 = D2Common_10299(pUnit, a3, pDVar1, 1);
					if (iVar2 != 0)
					{
						iVar2 = ITEMS_GetClassOfClassSpecificItem(pDVar1);
						if (iVar2 == 7)
						{
						LAB_6fae6bbf:
							sub_6FB514E0(pUnit, 0x14);
							return 1;
						}
						if (pUnit == nullptr)
						{
							iVar9 = -1;
						}
						else
						{
							iVar9 = pUnit->dwClassId;
						}
						if (iVar2 == iVar9)
							goto LAB_6fae6bbf;
					}
					sub_6FB514E0(pUnit, 0x13);
				}
				return 1;
			case 1:
				iVar2 = sub_6FB2FB90(pDVar1);
				if (iVar2 == 0)
				{
					iVar2 = sub_6FAABFF0();
					uVar5 = extraout_ECX_07;
					if ((iVar2 != 0) && (iVar2 = sub_6FAABFF0(), uVar5 = extraout_ECX_08, iVar2 != 1))
					{
						iVar2 = sub_6FB1FFF0();
						if (iVar2 != 0)
						{
							sub_6FB1FF00(extraout_ECX_09);
							return 0;
						}
						DVar4 = GetTickCount();
						if (DVar4 - byte_6FBB3870 < 0xfb)
						{
							return 0;
						}
						byte_6FBB3870 = GetTickCount();
						uVar5 = extraout_ECX_10;
					}
					if (pDVar1 == nullptr)
					{
						uVar6 = 0xffffffff;
					}
					else
					{
						uVar6 = pDVar1->dwUnitId;
					}
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x1a), uVar6, a3 & 0xffff);
					sub_6FB2FB30(pDVar1);
					iVar9 = 0;
					fVar8 = 0.0;
					fVar7 = 0.0;
					iVar2 = sub_6FB2E590(pDVar1);
					sub_6FB55820(iVar2, nullptr, fVar7, fVar8, iVar9);
					dword_6FBB58E8 = 1;
					return 1;
				}
				break;
			case 3:
				switch (dword_6FBB58EC)
				{
				case 0:
				case 1:
				case 2:
				case 0xb:
				case 0xc:
				case 0xe:
				case 0xf:
				case 0x13:
					iVar2 = sub_6FAABFF0();
					uVar5 = extraout_ECX_11;
					if ((iVar2 != 0) && (iVar2 = sub_6FAABFF0(), uVar5 = extraout_ECX_12, iVar2 != 1))
					{
						iVar2 = sub_6FB1FFF0();
						if (iVar2 != 0)
						{
							sub_6FB1FF00(extraout_ECX_13);
							return 0;
						}
						DVar4 = GetTickCount();
						if (DVar4 - byte_6FBB3870 < 0xfb)
						{
							return 0;
						}
						byte_6FBB3870 = GetTickCount();
						uVar5 = extraout_ECX_14;
					}
					sub_6FAAD990(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x1c), (short)a3);
					dword_6FBB58E8 = 1;
					return 1;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 0xd:
				case 0x10:
				case 0x11:
				case 0x12:
				default:
					if (((dword_6FBB58EC < 0x13) &&
					        (pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, a3), pDVar1 != nullptr)) &&
					    (iVar2 = sub_6FAFA260(pUnit, pDVar1, 1, dword_6FBB388C, dword_6FBB3894, 0, 0, 0),
					        iVar2 != 0))
					{
						dword_6FBB58EC = 5;
						sub_6FB575B0(nullptr);
						return 0;
					}
				}
				break;
			case 5:
				iVar2 = sub_6FB2FB90(pDVar1);
				if (iVar2 == 0)
				{
					iVar2 = sub_6FAABFF0();
					uVar5 = extraout_ECX_15;
					if ((iVar2 != 0) && (iVar2 = sub_6FAABFF0(), uVar5 = extraout_ECX_16, iVar2 != 1))
					{
						iVar2 = sub_6FB1FFF0();
						if (iVar2 != 0)
						{
							sub_6FB1FF00(extraout_ECX_17);
							return 0;
						}
						DVar4 = GetTickCount();
						if (DVar4 - byte_6FBB3870 < 0xfb)
						{
							return 0;
						}
						byte_6FBB3870 = GetTickCount();
						uVar5 = extraout_ECX_18;
					}
					if (pDVar1 == nullptr)
					{
						uVar6 = 0xffffffff;
					}
					else
					{
						uVar6 = pDVar1->dwUnitId;
					}
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar5 >> 8), 0x1d), uVar6, a3 & 0xffff);
					sub_6FB2FB30(pDVar1);
					iVar9 = 0;
					fVar8 = 0.0;
					fVar7 = 0.0;
					iVar2 = sub_6FB2E590(pDVar1);
					sub_6FB55820(iVar2, nullptr, fVar7, fVar8, iVar9);
					local_4 = 1;
				}
			}
		}
	}
	return local_4;
}

//D2Client.0x6FAE6E60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAE6E60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pDVar1;
	bool bVar2;
	bool bVar3;
	int iVar4;
	uint32_t extraout_var;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var_00;
	D2UnitStrc* pDVar6;
	int* piVar7;
	int iVar8;
	uint32_t extraout_var_01;
	DWORD DVar9;
	uint32_t uVar10;
	D2GameResolutionMode DVar11;
	int iVar12;
	uint32_t* puVar13;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t uVar14;
	int iVar15;
	int iVar16;
	uint32_t uVar17;
	uint32_t uVar18;
	float fVar19;
	float fVar20;
	uint8_t* puVar21;
	uint32_t* puStack_8;

	iVar4 = sub_6FAABF20();
	if ((iVar4 == 0) && (bVar2 = sub_6FB283E0(), D2C_ZEXT(bVar2) == 0))
	{
		uVar18 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
		uVar17 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
		if (gnScreenWidth < (int)uVar18)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
		pDVar5 = CUNIT_GetPlayer();
		sub_6FAE0A10();
		bVar2 = false;
		pDVar1 = pDVar5->pInventory;
		bVar3 = sub_6FAFE9E0();
		if (D2C_ZEXT(bVar3) == 0)
		{
			pDVar6 = CUNIT_GetPlayer();
			pDVar6 = INVENTORY_GetCursorItem(pDVar6->pInventory);
			if (((((pDVar6 == nullptr) && (dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar17)) && ((int)uVar17 <= dword_6FBBA74C + -0x45 + gnScreenHeight)) &&
			        (((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar18 &&
			            ((int)uVar18 <= (gnScreenWidth - dword_6FBBA748) + -0xd9)))) &&
			    (((dword_6FBB58EC == 0 || ((dword_6FBB58EC == 0xb || (dword_6FBB58EC == 0xc)))) ||
			        (dword_6FBB58EC == 0xf))))
			{
				dword_6FBB5B38 = 1;
				sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
			}
			if (((((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar18) &&
			         ((int)uVar18 <= (gnScreenWidth - dword_6FBBA748) + -0x10e)) &&
			        (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar17)) &&
			    (((int)uVar17 <= dword_6FBBA74C + -0x40 + gnScreenHeight &&
			        ((dword_6FBB58EC == 0 || (dword_6FBB58EC == 0x13))))))
			{
				dword_6FBB5B98 = 1;
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				goto LAB_6fae7041;
			}
		}
		iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
		if (((iVar4 == 0) && (dword_6FBB38C8 <= (int)uVar18)) &&
		    (((int)uVar18 < dword_6FBB38CC &&
		        ((dword_6FBB38D0 <= (int)uVar17 && ((int)uVar17 <= dword_6FBB38D4))))))
		{
			if (((((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar18) &&
			         ((int)uVar18 <= (gnScreenWidth - dword_6FBBA748) + -0x10e)) &&
			        (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar17)) &&
			    ((int)uVar17 <= dword_6FBBA74C + -0x40 + gnScreenHeight))
			{
				dword_6FBB5B98 = 1;
				sub_6FB23260(1, 1, 0);
				pSMSGHANDLER_PARAMS->bUseResult = 1;
			LAB_6fae7041:
				pSMSGHANDLER_PARAMS->lResult = 0;
				sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			if ((((int)uVar18 < dword_6FBB3714) || (dword_6FBB3718 < (int)uVar18)) ||
			    (((int)uVar17 < dword_6FBB371C || (dword_6FBB3720 < (int)uVar17))))
			{
				iVar4 = 0;
				piVar7 = (int*)(&dword_6FBB595C);
				do
				{
					if (((piVar7[-1] <= (int)uVar18) && ((int)uVar18 <= *piVar7)) &&
					    ((piVar7[1] <= (int)uVar17 && ((int)uVar17 <= piVar7[2]))))
					{
						pDVar5 = INVENTORY_GetCursorItem(pDVar1);
						iVar8 = sub_6FB57CC0();
						if ((iVar8 != 6) && (iVar8 = sub_6FB57CC0(), iVar8 != 8))
						{
							pDVar6 = INVENTORY_GetItemFromBodyLoc(pDVar1, iVar4);
							bVar3 = sub_6FAE17D0(pDVar5, pDVar6);
							if (D2C_ZEXT(bVar3) != 0)
							{
								iVar4 = sub_6FB2FB90(pDVar5);
								if (iVar4 == 0)
								{
									iVar4 = sub_6FAABFF0();
									if ((iVar4 == 0) || (iVar4 = sub_6FAABFF0(), iVar4 == 1))
									{
									LAB_6fae71ad:
										if (pDVar6 == nullptr)
										{
											uVar10 = 0xffffffff;
										}
										else
										{
											uVar10 = pDVar6->dwUnitId;
										}
										if (pDVar5 == nullptr)
										{
											uVar14 = 0xffffffff;
										}
										else
										{
											uVar14 = pDVar5->dwUnitId;
										}
										sub_6FAADA40(CONCAT31((int32_t)((uint32_t)pDVar5 >> 8), 0x28), uVar14, uVar10);
										sub_6FB2FB30(pDVar5);
										iVar8 = 0;
										fVar20 = 0.0;
										fVar19 = 0.0;
										iVar4 = sub_6FB2E590(pDVar6);
										sub_6FB55820(iVar4, nullptr, fVar19, fVar20, iVar8);
										bVar2 = true;
									}
									else
									{
										iVar4 = sub_6FB1FFF0();
										if (iVar4 == 0)
										{
											DVar9 = GetTickCount();
											if (0xfa < DVar9 - byte_6FBB3870)
											{
												byte_6FBB3870 = GetTickCount();
												goto LAB_6fae71ad;
											}
										}
										else
										{
											sub_6FB1FF00(extraout_ECX);
										}
									}
								}
								puStack_8 = nullptr;
								if (bVar2)
									goto LAB_6fae70b7;
								break;
							}
						}
						puStack_8 = (uint32_t*)(**(code**)(iVar4 * 4 + (int)&tbl_6FB792AC))(iVar4);
						goto LAB_6fae70ab;
					}
					piVar7 = piVar7 + 5;
					iVar4 = iVar4 + 1;
				} while ((int)piVar7 < (int)&dword_6FBB5A38);
				puStack_8 = nullptr;
				iVar4 = sub_6FAAC080();
				if ((iVar4 != 0) &&
				    (((((dword_6FBB59BC <= (int)uVar18 && ((int)uVar18 <= dword_6FBB59C0)) &&
				           (dword_6FBB59C4 + -0x18 <= (int)uVar17)) &&
				          ((int)uVar17 < dword_6FBB59C4)) ||
				        (((dword_6FBB59A8 <= (int)uVar18 && ((int)uVar18 <= dword_6FBB59AC)) &&
				            ((dword_6FBB59B0 + -0x18 <= (int)uVar17 && ((int)uVar17 < dword_6FBB59B0))))))))
				{
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					iVar4 = FOG_IsExpansion();
					if ((iVar4 != 0) && (iVar4 = sub_6FAAC080(), iVar4 != 0))
					{
						sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
						CLIENT_SendSimpleMessage(0x60);
						pDVar5 = CUNIT_GetPlayer();
						pDVar1 = pDVar5->pInventory;
						pDVar5 = INVENTORY_GetItemFromBodyLoc(pDVar1, 4);
						if (pDVar5 != nullptr)
						{
							sub_6FB2FB30(pDVar5);
						}
						pDVar5 = INVENTORY_GetItemFromBodyLoc(pDVar1, 5);
						if (pDVar5 != nullptr)
						{
							sub_6FB2FB30(pDVar5);
						}
					}
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
			else
			{
				puStack_8 = sub_6FAE75C0(pDVar5, pDVar1, uVar18, uVar17, pSMSGHANDLER_PARAMS->wParam, (D2UnitStrc*)(&byte_6FBB3710), 0);
			LAB_6fae70ab:
				bVar2 = true;
			}
		LAB_6fae70b7:
			pSMSGHANDLER_PARAMS->lResult = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			if (puStack_8 == nullptr)
			{
				iVar4 = sub_6FB57CC0();
				if (iVar4 == 6)
				{
					sub_6FB23A40();
				}
				else
				{
					iVar4 = sub_6FB57CC0();
					if (iVar4 == 8)
					{
						sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x4c), 0xffffffff);
					}
				}
			}
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB58E0 = 0;
			dword_6FBB58E4 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = 0;
			if (bVar2)
			{
				dword_6FBB58E0 = 0;
				dword_6FBB58E4 = 0;
				gpUnit_6FBB58F0 = nullptr;
				dword_6FBB58F4 = 0;
				return;
			}
		}
		else
		{
			if (dword_6FBB58EC == 0xb)
			{
				if ((((dword_6FBB383C <= (int)uVar18) && ((int)uVar18 <= dword_6FBB3840)) &&
				        (dword_6FBB3844 <= (int)uVar17)) &&
				    ((int)uVar17 <= dword_6FBB3848))
				{
					puVar13 = sub_6FAE75C0(pDVar5, pDVar1, uVar18, uVar17, pSMSGHANDLER_PARAMS->wParam, (D2UnitStrc*)(&byte_6FBB3838), (D2UnitStrc*)(2));
					pSMSGHANDLER_PARAMS->lResult = 0;
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					dword_6FBB58E0 = 0;
					dword_6FBB58E4 = 0;
					gpUnit_6FBB58F0 = nullptr;
					dword_6FBB58F4 = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					if (puVar13 == nullptr)
					{
						return;
					}
					sub_6FB1FF00(extraout_ECX_01);
					return;
				}
			}
			else if (dword_6FBB58EC == 0xc)
			{
				iVar12 = sub_6FAAC080();
				iVar4 = dword_6FBB372C;
				iVar8 = dword_6FBB3730;
				iVar15 = dword_6FBB3734;
				iVar16 = dword_6FBB3738;
				if (iVar12 != 0)
				{
					iVar4 = dword_6FBB3764;
					iVar8 = dword_6FBB3768;
					iVar15 = dword_6FBB376C;
					iVar16 = dword_6FBB3770;
				}
				if (((iVar4 <= (int)uVar18) && ((int)uVar18 <= iVar8)) &&
				    ((iVar15 <= (int)uVar17 && ((int)uVar17 <= iVar16))))
				{
					iVar4 = sub_6FAAC080();
					if (iVar4 == 0)
					{
						uVar10 = pSMSGHANDLER_PARAMS->wParam;
						puVar21 = &byte_6FBB3728;
					}
					else
					{
						uVar10 = pSMSGHANDLER_PARAMS->wParam;
						puVar21 = &byte_6FBB3760;
					}
					sub_6FAE75C0(pDVar5, pDVar1, uVar18, uVar17, uVar10, (D2UnitStrc*)(puVar21), (D2UnitStrc*)(4));
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					dword_6FBB58E0 = 0;
					dword_6FBB58E4 = 0;
					gpUnit_6FBB58F0 = nullptr;
					dword_6FBB58F4 = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
			else if (((dword_6FBB58EC == 0xe) && (dword_6FBB38B4 <= (int)uVar18)) &&
			         (((int)uVar18 <= dword_6FBB38B8 &&
			             ((dword_6FBB38BC <= (int)uVar17 && ((int)uVar17 <= dword_6FBB38C0))))))
			{
				sub_6FAE75C0(pDVar5, pDVar1, uVar18, uVar17, pSMSGHANDLER_PARAMS->wParam, (D2UnitStrc*)(&byte_6FBB38B0), (D2UnitStrc*)(3));
				pSMSGHANDLER_PARAMS->lResult = 0;
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				dword_6FBB58E0 = 0;
				dword_6FBB58E4 = 0;
				gpUnit_6FBB58F0 = nullptr;
				dword_6FBB58F4 = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			pSMSGHANDLER_PARAMS->bUseResult = 0;
		}
		DVar11 = D2GFX_GetResolutionMode();
		if ((((DVar11 == NUM_GAME_RESOLUTIONS) && (iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS), iVar4 == 0)) &&
		        ((int)uVar17 <= gnScreenHeight + -0x30)) &&
		    ((iVar4 = sub_6FAB5750(), iVar4 != 1 || (gnScreenWidth / 2 <= (int)uVar18))))
		{
			iVar4 = sub_6FB57CC0();
			if (iVar4 == 6)
			{
				sub_6FB23A40();
			}
			iVar4 = sub_6FAB5750();
			if (((iVar4 != 3) || (dword_6FBB58EC != 0)) || (gnScreenWidth / 2 <= (int)uVar18))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				dword_6FBB58E0 = 0;
				dword_6FBB58E4 = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
		}
	}
	else
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
	}
}

//D2Client.0x6FAE75C0
// TODO: decompilation needs review (extraout)
uint32_t* __fastcall sub_6FAE75C0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, uint32_t a3, int a4, uint32_t a5, D2UnitStrc* pUnit2, D2UnitStrc* pUnit3)
{
	bool bVar1;
	uint8_t bVar2;
	bool bVar3;
	SHORT SVar4;
	uint16_t uVar5;
	uint16_t uVar6;
	D2UnitStrc* pDVar7;
	int iVar8;
	uint32_t uVar9;
	int iVar10;
	D2UnitStrc* pDVar11;
	D2UnitStrc* pDVar12;
	DWORD DVar13;
	D2BitBufferStrc* pQuestFlags;
	D2UnitStrc* pPlayer;
	D2ItemsTxt* pDVar14;
	uint32_t extraout_var;
	uint32_t uVar15;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	uint32_t extraout_ECX_04;
	uint32_t extraout_ECX_05;
	uint32_t extraout_ECX_06;
	uint32_t extraout_ECX_07;
	uint32_t extraout_ECX_08;
	uint32_t extraout_ECX_09;
	uint32_t extraout_ECX_10;
	uint32_t extraout_ECX_11;
	uint32_t extraout_ECX_12;
	uint32_t extraout_ECX_13;
	uint32_t extraout_ECX_14;
	uint32_t uVar17;
	uint32_t extraout_ECX_15;
	uint32_t extraout_ECX_16;
	uint32_t extraout_ECX_17;
	uint32_t extraout_ECX_18;
	uint32_t extraout_ECX_19;
	uint32_t extraout_ECX_20;
	uint32_t extraout_ECX_21;
	uint32_t extraout_ECX_22;
	uint32_t extraout_ECX_23;
	uint32_t uVar16;
	uint32_t extraout_ECX_24;
	uint32_t extraout_ECX_25;
	uint32_t extraout_ECX_26;
	uint32_t extraout_ECX_27;
	uint8_t bVar18;
	code* pcVar19;
	float fVar20;
	float fVar21;
	D2C_TransactionTypes nTransactionType;
	int iVar22;
	uint32_t* local_30;
	uint32_t local_24;
	int iStack_20;
	int iStack_1c;
	uint32_t uStack_18;
	D2UnitStrc* pDStack_14;
	uint32_t uStack_10;
	uint32_t uStack_c;
	uint32_t uStack_8;
	D2UnitStrc* pDStack_4;
	D2C_Difficulties nDifficulty;

	uVar15 = (uint32_t)pUnit3;
	bVar2 = (uint8_t)pUnit3;
	local_30 = nullptr;
	if (bVar2 == 0xff)
	{
		FOG_Trace(" Invalid page %d at line %d of file %s\n", 0xff, __LINE__, __FILE__);
		return nullptr;
	}
	pDVar7 = INVENTORY_GetCursorItem(pInventory);
	iVar8 = sub_6FAAC080();
	iVar8 = UNITS_GetInventoryRecordId(pUnit, uVar15, iVar8);
	pDVar11 = pUnit2;
	uVar9 = (a3 - pUnit2->dwClassId) / (uint32_t) * (uint8_t*)&pUnit2->pPlayerData;
	pUnit3 = (D2UnitStrc*)((a4 - pUnit2->dwUnitId) / (uint32_t) * (uint8_t*)((int)&pUnit2->pPlayerData + 1));
	iVar10 = sub_6FB57CC0();
	if (iVar10 == 6)
	{
		pDVar11 = sub_6FB575E0();
		pDVar7 = INVENTORY_GetItemFromInventoryPage(pInventory, uVar9, (int)pUnit3, &iStack_1c, &iStack_20, iVar8, bVar2);
		if (pDVar11 == nullptr)
		{
			return nullptr;
		}
		if (pDVar7 == nullptr)
		{
			return nullptr;
		}
		iVar8 = sub_6FB2FB90(pDVar7);
		if (iVar8 != 0)
		{
			return (uint32_t*)0x1;
		}
		pDVar12 = CUNIT_GetPlayer();
		if (pUnit != pDVar12)
		{
			return nullptr;
		}
		if (bVar2 == 1)
		{
			return nullptr;
		}
		if (bVar2 == 2)
		{
			return nullptr;
		}
		iVar8 = sub_6FAABFF0();
		uVar16 = extraout_ECX;
		if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), uVar16 = extraout_ECX_00, iVar8 != 1))
		{
			iVar8 = sub_6FB1FFF0();
			uVar16 = extraout_ECX_01;
			if (iVar8 != 0)
			{
			LAB_6fae77f4:
				sub_6FB1FF00(uVar16);
				return nullptr;
			}
			DVar13 = GetTickCount();
			if (DVar13 - byte_6FBB3870 < 0xfb)
			{
				return nullptr;
			}
			byte_6FBB3870 = GetTickCount();
			uVar16 = extraout_ECX_02;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar16 >> 8), 0x27), pDVar7->dwUnitId, pDVar11->dwUnitId);
		sub_6FB2FB30(pDVar7);
		return (uint32_t*)0x1;
	}
	iVar10 = sub_6FB57CC0();
	if (iVar10 == 8)
	{
		pDVar11 = INVENTORY_GetItemFromInventoryPage(pInventory, uVar9, (int)pUnit3, &iStack_1c, &iStack_20, iVar8, bVar2);
		if (pDVar11 == nullptr)
		{
			return nullptr;
		}
		iVar8 = sub_6FB2FB90(pDVar11);
		if (iVar8 != 0)
		{
			return (uint32_t*)0x1;
		}
		pDVar7 = CUNIT_GetPlayer();
		if (pUnit != pDVar7)
		{
			return nullptr;
		}
		if (bVar2 == 1)
		{
			return nullptr;
		}
		if (bVar2 == 2)
		{
			return nullptr;
		}
		iVar8 = sub_6FAABFF0();
		uVar16 = extraout_ECX_03;
		if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), uVar16 = extraout_ECX_04, iVar8 != 1))
		{
			iVar8 = sub_6FB1FFF0();
			uVar16 = extraout_ECX_05;
			if (iVar8 != 0)
				goto LAB_6fae77f4;
			DVar13 = GetTickCount();
			if (DVar13 - byte_6FBB3870 < 0xfb)
			{
				return nullptr;
			}
			byte_6FBB3870 = GetTickCount();
			uVar16 = extraout_ECX_06;
		}
		sub_6FAADA20(CONCAT31((int32_t)((uint32_t)uVar16 >> 8), 0x4c), pDVar11->dwUnitId);
		sub_6FB2FB30(pDVar11);
		return (uint32_t*)0x1;
	}
	if (pDVar7 == nullptr)
	{
		pDVar11 = INVENTORY_GetItemFromInventoryPage(pInventory, uVar9, (int)pUnit3, &iStack_1c, &iStack_20, iVar8, bVar2);
		if (pDVar11 == nullptr)
		{
			return nullptr;
		}
		pDVar7 = CUNIT_GetPlayer();
		switch (dword_6FBB58EC)
		{
		case 0:
		case 1:
		case 2:
		case 0xb:
		case 0xc:
		case 0xe:
		case 0x13:
			if ((pUnit == pDVar7) == 1)
			{
				iVar8 = sub_6FB2FB90(pDVar11);
				if (iVar8 != 0)
				{
					return nullptr;
				}
				iVar8 = sub_6FAABFF0();
				if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), iVar8 != 1))
				{
					iVar8 = sub_6FB1FFF0();
					if (iVar8 != 0)
					{
						sub_6FB1FF00(extraout_ECX_07);
						return nullptr;
					}
					DVar13 = GetTickCount();
					if (DVar13 - byte_6FBB3870 < 0xfb)
					{
						return nullptr;
					}
					byte_6FBB3870 = GetTickCount();
				}
				SVar4 = GetAsyncKeyState(0x11);
				if (SVar4 < 0)
				{
					iVar8 = sub_6FAFBB50(&a3);
					if ((iVar8 != 0) && (pDVar7 = sub_6FB269F0(a3, 1), pDVar7 != nullptr))
					{
						iVar8 = pDVar7->dwClassId;
						nTransactionType = TRANSACTIONTYPE_SELL;
						pQuestFlags = sub_6FAFBD20();
						bVar2 = sub_6FAAC090();
						nDifficulty = (D2C_Difficulties)bVar2;
						pDVar12 = pDVar11;
						pPlayer = CUNIT_GetPlayer();
						iVar8 = ITEMS_GetTransactionCost(pPlayer, pDVar12, nDifficulty, pQuestFlags, iVar8, nTransactionType);
						sub_6FAADAA0(CONCAT31((int32_t)(pDVar11->dwAnimMode >> 8), 0x33), pDVar7->dwUnitId,
						    pDVar11->dwUnitId, pDVar11->dwAnimMode, iVar8);
						sub_6FB2FB30(pDVar11);
						return (uint32_t*)0x1;
					}
				}
				else
				{
					uVar16 = extraout_ECX_08;
					if ((((a5 & 4) != 0) &&
					        (uVar15 = ITEMS_CheckIfBeltable(pDVar11), uVar16 = extraout_ECX_09, uVar15 != 0)) &&
					    (bVar2 = ITEMS_GetInvPage(pDVar11), uVar16 = extraout_ECX_10, bVar2 == 0))
					{
						sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_10 >> 8), 99), pDVar11->dwUnitId);
						sub_6FB55820(0xeb, nullptr, 0.0, 0.0, 0);
						sub_6FB2FB30(pDVar11);
						return (uint32_t*)0x1;
					}
					sub_6FAADA20(CONCAT31((int32_t)((uint32_t)uVar16 >> 8), 0x19), pDVar11->dwUnitId);
					dword_6FBB58E8 = 1;
				}
				sub_6FB2FB30(pDVar11);
				return (uint32_t*)0x1;
			}
		switchD_6fae7869_caseD_3:
			goto switchD_6fae7869_default;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 0xd:
		case 0xf:
		case 0x10:
		case 0x11:
		case 0x12:
			goto switchD_6fae7869_caseD_3;
		default:
		switchD_6fae7869_default:
			if (0x12 < dword_6FBB58EC)
			{
				return nullptr;
			}
			iVar8 = sub_6FAFA260(pUnit, pDVar11, (uint32_t)(pUnit == pDVar7), a3, a4, 0, 0, 0);
			if (iVar8 == 0)
			{
				return nullptr;
			}
			dword_6FBB58EC = 5;
			sub_6FB575B0(nullptr);
			return nullptr;
		}
	}
	INVENTORY_CanItemBePlaced(pInventory, pDVar7, dword_6FB792A0, dword_6FB792A4, iVar8, &pUnit3, &uStack_18, bVar2);
	bVar1 = true;
	pDStack_14 = nullptr;
	if (uStack_18 < 2)
	{
	LAB_6fae7aa9:
		if ((pUnit3 == nullptr) || (uStack_18 != 1))
		{
			if (bVar2 == 3)
			{
				pDVar14 = DATATBLS_GetItemsTxtRecord(pDVar7->dwClassId);
				D2_ASSERT(pDVar14 != nullptr);
				if (pDVar14->dwCode == 0x20786f62)
				{
					return (uint32_t*)0x1;
				}
			}
			uVar9 = (a3 - pDVar11->dwClassId) / (uint32_t) * (uint8_t*)&pDVar11->pPlayerData;
			local_24 = (a4 - pDVar11->dwUnitId) / (uint32_t) * (uint8_t*)((int)&pDVar11->pPlayerData + 1);
			ITEMS_GetDimensions(pDVar7, (uint8_t*)&pUnit2, (uint8_t*)&a5, __FILE__, 0x6da);
			sub_6FB5DFB0(pDVar7, 0, 0, (int*)(&uStack_10), (int*)(&uStack_c));
			if (((uint32_t)pUnit2 & 1) == 0)
			{
				uVar9 = (((uStack_10 >> 2) - pDVar11->dwClassId) + a3) /
				        (uint32_t) * (uint8_t*)&pDVar11->pPlayerData;
			}
			bVar18 = (uint8_t)pDVar11->dwUnitType;
			if ((uint8_t)pUnit2 == bVar18)
			{
				uVar9 = (uint32_t)(bVar18 >> 1);
			}
			if ((a5 & 1) == 0)
			{
				local_24 = (((uStack_c >> 2) - pDVar11->dwUnitId) + a4) /
				           (uint32_t) * (uint8_t*)((int)&pDVar11->pPlayerData + 1);
			}
			bVar18 = *(uint8_t*)((int)&pDVar11->dwUnitType + 1);
			if ((uint8_t)a5 == bVar18)
			{
				local_24 = (uint32_t)(bVar18 >> 1);
			}
			if (1 < (uint8_t)pUnit2)
			{
				bVar18 = (uint8_t)pUnit2 >> 1;
				pUnit2 = (D2UnitStrc*)CONCAT31((*(uint8_t*)((uint8_t*)&pUnit2 + 1)), bVar18);
				uVar9 = uVar9 - bVar18;
				uVar9 = uVar9 & ((int)uVar9 < 0) - 1;
			}
			if (1 < (uint8_t)a5)
			{
				bVar18 = (uint8_t)a5 >> 1;
				a5 = CONCAT31((*(uint8_t*)((uint8_t*)&a5 + 1)), bVar18);
				local_24 = local_24 - bVar18;
				local_24 = local_24 & ((int)local_24 < 0) - 1;
			}
			iVar8 = INVENTORY_CanItemBePlaced(pInventory, pDVar7, uVar9, local_24, iVar8, &pDStack_4, &uStack_8, bVar2);
			if (iVar8 == 0)
			{
				return nullptr;
			}
			iVar8 = sub_6FB2FB90(pDVar7);
			if (iVar8 != 0)
			{
				return nullptr;
			}
			iVar8 = sub_6FAABFF0();
			uVar16 = extraout_ECX_24;
			if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), uVar16 = extraout_ECX_25, iVar8 != 1))
			{
				iVar8 = sub_6FB1FFF0();
				if (iVar8 != 0)
				{
					sub_6FB1FF00(extraout_ECX_26);
					return nullptr;
				}
				DVar13 = GetTickCount();
				if (DVar13 - byte_6FBB3870 < 0xfb)
				{
					return nullptr;
				}
				byte_6FBB3870 = GetTickCount();
				uVar16 = extraout_ECX_27;
			}
			uVar15 = uVar15 & 0xff;
			uVar16 = CONCAT31((int32_t)((uint32_t)uVar16 >> 8), 0x18);
			goto LAB_6fae80e1;
		}
		iVar10 = ITEMS_AreStackablesEqual(pDVar7, pUnit3);
		if (iVar10 == 0)
		{
			if ((int)dword_6FB792A0 < 0)
			{
				return nullptr;
			}
			if ((int)dword_6FB792A4 < 0)
			{
				return nullptr;
			}
			bVar3 = sub_6FAE17D0(pDVar7, pUnit3);
			if ((D2C_ZEXT(bVar3) != 0) && (iVar10 = sub_6FB2FB90(pDVar7), iVar10 == 0))
			{
				iVar10 = sub_6FAABFF0();
				uVar16 = extraout_ECX_15;
				if ((iVar10 == 0) || (iVar10 = sub_6FAABFF0(), uVar16 = extraout_ECX_16, iVar10 == 1))
				{
				LAB_6fae7bec:
					if (pUnit3 == nullptr)
					{
						uVar15 = 0xffffffff;
					}
					else
					{
						uVar15 = pUnit3->dwUnitId;
					}
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar16 >> 8), 0x28), pDVar7->dwUnitId, uVar15);
					sub_6FB2FB30(pDVar7);
					iVar22 = 0;
					fVar21 = 0.0;
					fVar20 = 0.0;
					iVar10 = sub_6FB2E590(pUnit3);
					sub_6FB55820(iVar10, nullptr, fVar20, fVar21, iVar22);
					bVar1 = false;
					local_30 = (uint32_t*)0x1;
				}
				else
				{
					iVar10 = sub_6FB1FFF0();
					if (iVar10 == 0)
					{
						DVar13 = GetTickCount();
						if (0xfa < DVar13 - byte_6FBB3870)
						{
							byte_6FBB3870 = GetTickCount();
							uVar16 = extraout_ECX_18;
							goto LAB_6fae7bec;
						}
					}
					else
					{
						sub_6FB1FF00(extraout_ECX_17);
					}
				}
			}
			iVar10 = ITEMS_CheckItemTypeId(pDVar7, 0x16);
			if ((iVar10 != 0) && (iVar10 = ITEMS_CheckItemTypeId(pUnit3, 0x12), iVar10 != 0))
			{
				uVar5 = ITEMS_GetSuffixId(pUnit3, 0);
				uVar6 = ITEMS_GetSuffixId(pDVar7, 0);
				if ((uVar6 == uVar5) && (iVar10 = sub_6FB2FB90(pDVar7), iVar10 == 0))
				{
					iVar10 = sub_6FAABFF0();
					if ((iVar10 == 0) || (iVar10 = sub_6FAABFF0(), iVar10 == 1))
					{
					LAB_6fae7cc2:
						if (dword_6FBB58EC != 0xb)
						{
							sub_6FB19EF0();
							if (pUnit3 == nullptr)
							{
								uVar15 = 0xffffffff;
							}
							else
							{
								uVar15 = pUnit3->dwUnitId;
							}
							sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_20 >> 8), 0x29), pDVar7->dwUnitId, uVar15);
							sub_6FB2FB30(pDVar7);
							iVar22 = 0;
							fVar21 = 0.0;
							fVar20 = 0.0;
							iVar10 = sub_6FB2E590(pUnit3);
							sub_6FB55820(iVar10, nullptr, fVar20, fVar21, iVar22);
							bVar1 = false;
							local_30 = (uint32_t*)0x1;
						}
					}
					else
					{
						iVar10 = sub_6FB1FFF0();
						if (iVar10 == 0)
						{
							DVar13 = GetTickCount();
							if (0xfa < DVar13 - byte_6FBB3870)
							{
								byte_6FBB3870 = GetTickCount();
								goto LAB_6fae7cc2;
							}
						}
						else
						{
							sub_6FB1FF00(extraout_ECX_19);
						}
					}
				}
			}
			if (pUnit3 == nullptr)
			{
				iVar10 = -1;
			}
			else
			{
				iVar10 = pUnit3->dwClassId;
			}
			pDVar14 = DATATBLS_GetItemsTxtRecord(iVar10);
			pcVar19 = (code*)(((uint8_t*)&GetTickCount));
			if (pDVar14->dwCode == 0x20786f62)
				goto LAB_6fae7d36;
			goto LAB_6fae7d74;
		}
		iVar8 = sub_6FB2FB90(pDVar7);
		if (iVar8 != 0)
		{
			return nullptr;
		}
		iVar8 = sub_6FAABFF0();
		uVar16 = extraout_ECX_11;
		if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), uVar16 = extraout_ECX_12, iVar8 != 1))
		{
			iVar8 = sub_6FB1FFF0();
			if (iVar8 != 0)
			{
				sub_6FB1FF00(extraout_ECX_13);
				return nullptr;
			}
			DVar13 = GetTickCount();
			if (DVar13 - byte_6FBB3870 < 0xfb)
			{
				return nullptr;
			}
			byte_6FBB3870 = GetTickCount();
			uVar16 = extraout_ECX_14;
		}
		if (dword_6FBB58EC == 0xb)
		{
			return nullptr;
		}
		if (bVar2 == 2)
		{
			return nullptr;
		}
		uVar17 = (uint32_t)((uint32_t)uVar16 >> 8);
		if (pUnit3 == nullptr)
		{
			sub_6FAADA40(CONCAT31(uVar17, 0x21), pDVar7->dwUnitId, 0xffffffff);
		}
		else
		{
			sub_6FAADA40(CONCAT31(uVar17, 0x21), pDVar7->dwUnitId, pUnit3->dwUnitId);
		}
	}
	else
	{
		pUnit2 = nullptr;
		INVENTORY_CanItemsBeExchanged(pInventory, pDVar7, dword_6FB792A0, dword_6FB792A4, iVar8, &pUnit2, bVar2, 1);
		if ((pUnit2 == nullptr) ||
		    (pDVar14 = DATATBLS_GetItemsTxtRecord(pUnit2->dwClassId), pDVar14->dwCode != 0x20786f62))
			goto LAB_6fae7aa9;
		pUnit3 = pUnit2;
	LAB_6fae7d36:
		iVar10 = sub_6FB2FB90(pDVar7);
		pcVar19 = (code*)(((uint8_t*)&GetTickCount));
		if (iVar10 == 0)
		{
			iVar10 = sub_6FAABFF0();
			if ((iVar10 == 0) || (iVar10 = sub_6FAABFF0(), iVar10 == 1))
			{
			LAB_6fae7e13:
				iVar8 = sub_6FAAC080();
				iVar8 = UNITS_GetInventoryRecordId(pUnit, 3, iVar8);
				iVar8 = INVENTORY_GetFreePosition(pInventory, pDVar7, iVar8, &a4, (int*)&a3, 3);
				if (iVar8 == 0)
				{
					sub_6FB514E0(pUnit, 0x13);
					return local_30;
				}
				if (pUnit3 == nullptr)
				{
					uVar15 = 0xffffffff;
				}
				else
				{
					uVar15 = pUnit3->dwUnitId;
				}
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_23 >> 8), 0x2a), pDVar7->dwUnitId, uVar15);
				sub_6FB2FB30(pDVar7);
				pDVar7 = pUnit3;
				goto LAB_6fae80f2;
			}
			iVar10 = sub_6FB1FFF0();
			pcVar19 = (code*)(((uint8_t*)&GetTickCount));
			if (iVar10 == 0)
			{
				DVar13 = GetTickCount();
				if (0xfa < DVar13 - byte_6FBB3870)
				{
					byte_6FBB3870 = GetTickCount();
					goto LAB_6fae7e13;
				}
			}
			else
			{
				sub_6FB1FF00(extraout_ECX_21);
				pcVar19 = (code*)(((uint8_t*)&GetTickCount));
			}
		}
	LAB_6fae7d74:
		if (!bVar1)
		{
			return local_30;
		}
		iVar8 = INVENTORY_CanItemsBeExchanged(pInventory, pDVar7, dword_6FB792A0, dword_6FB792A4, iVar8, &pDStack_14, bVar2, 0);
		if (iVar8 == 0)
		{
			return local_30;
		}
		iVar8 = sub_6FB2FB90(pDVar7);
		if (iVar8 != 0)
		{
			return local_30;
		}
		iVar8 = sub_6FAABFF0();
		if ((iVar8 != 0) && (iVar8 = sub_6FAABFF0(), iVar8 != 1))
		{
			iVar8 = sub_6FB1FFF0();
			if (iVar8 != 0)
			{
				sub_6FB1FF00(extraout_ECX_22);
				return local_30;
			}
			iVar8 = (*pcVar19)();
			if (iVar8 - byte_6FBB3870 < 0xfb)
			{
				return local_30;
			}
			byte_6FBB3870 = (*pcVar19)();
		}
		if (bVar2 == 2)
		{
			return local_30;
		}
		if (pDStack_14 == nullptr)
		{
			uVar9 = 0xffffffff;
		}
		else
		{
			uVar9 = pDStack_14->dwUnitId;
		}
		uVar16 = D2C_ZEXT(0x1f);
		local_24 = dword_6FB792A0;
		uVar15 = dword_6FB792A4;
	LAB_6fae80e1:
		sub_6FAADAA0(uVar16, pDVar7->dwUnitId, uVar9, local_24, uVar15);
	}
	sub_6FB2FB30(pDVar7);
LAB_6fae80f2:
	iVar10 = 0;
	fVar21 = 0.0;
	fVar20 = 0.0;
	iVar8 = sub_6FB2E590(pDVar7);
	sub_6FB55820(iVar8, nullptr, fVar20, fVar21, iVar10);
	return (uint32_t*)0x1;
}

//D2Client.0x6FAE8140
void __cdecl sub_6FAE8140(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t uVar4;

	uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar3 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB5B98 = 0;
	byte_6FBB5B9C = 0;
	pDVar1 = CUNIT_GetPlayer();
	pInventory = pDVar1->pInventory;
	iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar2 == 0)
	{
		if (((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar4) &&
		    ((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0x10e))
		{
			if ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar3) &&
			    ((int)uVar3 <= dword_6FBBA74C + -0x40 + gnScreenHeight))
			{
				sub_6FB23260(1, 1, 0);
				return;
			}
		}
		INVENTORY_GetCursorItem(pInventory);
	}
	if ((dword_6FBB5B38 != 0) && (dword_6FBB58EC == 0))
	{
		dword_6FBB5B38 = 0;
		pDVar1 = CUNIT_GetPlayer();
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		if (pDVar1 == nullptr)
		{
			if ((((dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar3) &&
			         ((int)uVar3 <= dword_6FBBA74C + -0x45 + gnScreenHeight)) &&
			        ((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar4)) &&
			    (((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0xd9 && (dword_6FBB5B34 == 0))))
			{
				sub_6FB23B40(1);
			}
		}
	}
	sub_6FAABF60();
	if (((dword_6FBB38C8 <= (int)uVar4) && ((int)uVar4 < dword_6FBB38CC)) &&
	    ((dword_6FBB38D0 <= (int)uVar3 && ((int)uVar3 <= dword_6FBB38D4))))
	{
		iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
		if (iVar2 == 0)
		{
			pSMSGHANDLER_PARAMS->lResult = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FAE8290
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAE8290(int a1)
{
	D2InventoryStrc* pInventory;
	int iVar1;
	int iVar2;
	uint8_t uVar3;
	bool bVar4;
	int iVar5;
	uint32_t extraout_var;
	D2UnitStrc* pPlayer;
	D2UnitStrc* pDVar6;
	int* piVar7;
	int iVar8;
	D2UnitStrc* pItem;
	int iVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	uint8_t* puVar12;
	uint32_t uVar13;

	iVar5 = sub_6FAABF20();
	if (((iVar5 != 0) || (bVar4 = sub_6FB283E0(), D2C_ZEXT(bVar4) != 0)) ||
	    (dword_6FB79288 == 0))
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	uVar10 = (uint32_t) * (uint16_t*)(a1 + 0xc);
	uVar11 = (uint32_t) * (uint16_t*)(a1 + 0xe);
	pPlayer = CUNIT_GetPlayer();
	sub_6FAE0A10();
	pInventory = pPlayer->pInventory;
	bVar4 = false;
	iVar5 = sub_6FB01B50(a1);
	uVar3 = byte_6FBB5900;
	if (((iVar5 == 0) && (dword_6FBB38C8 <= (int)uVar10)) &&
	    (((int)uVar10 < dword_6FBB38CC &&
	        ((dword_6FBB38D0 <= (int)uVar11 && ((int)uVar11 <= dword_6FBB38D4))))))
	{
		iVar5 = 0;
		*(uint32_t*)(a1 + 0x18) = 1;
		*(uint32_t*)(a1 + 0x1c) = 0;
		if ((dword_6FBB3714 <= (int)uVar10) &&
		    ((((int)uVar10 <= dword_6FBB3718 && (dword_6FBB371C <= (int)uVar11)) &&
		        ((int)uVar11 <= dword_6FBB3720))))
		{
			pDVar6 = INVENTORY_GetCursorItem(pInventory);
			sub_6FAE87C0(pPlayer, pInventory, pDVar6, uVar10, uVar11, &byte_6FBB3710, 0);
			dword_6FBB5920 = 0;
			dword_6FB7928C = 1;
			return;
		}
		piVar7 = (int*)(&dword_6FBB595C);
		while ((((int)uVar10 < piVar7[-1] || (*piVar7 < (int)uVar10)) ||
		        (((int)uVar11 < piVar7[1] || (piVar7[2] < (int)uVar11)))))
		{
			piVar7 = piVar7 + 5;
			iVar5 = iVar5 + 1;
			if ((int)&tbl_6FBB5A37 < (int)piVar7)
			{
				dword_6FBB5920 = 0;
				*(uint32_t*)(a1 + 0x18) = 0;
				dword_6FBB58F4 = (uint32_t)(nullptr);
				gpUnit_6FBB58F0 = nullptr;
				dword_6FBB58E4 = 0;
				dword_6FBB58E0 = 0;
				dword_6FB7928C = 1;
				return;
			}
		}
		pDVar6 = INVENTORY_GetCursorItem(pInventory);
		if (pDVar6 != nullptr)
		{
			dword_6FB7928C = 1;
			dword_6FB792A0 = 0xffffffff;
			dword_6FB792A4 = 0xffffffff;
			dword_6FBB58E4 = 1;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = (uint32_t)(nullptr);
			dword_6FBB5920 = iVar5;
			return;
		}
		iVar8 = INVENTORY_GetWieldType(pPlayer, pInventory);
		pDVar6 = INVENTORY_GetItemFromBodyLoc(pPlayer->pInventory, iVar5);
		if (((iVar5 == 4) || (iVar5 == 5)) &&
		    ((iVar8 == 2 &&
		        ((pItem = INVENTORY_GetItemFromBodyLoc(pInventory, 4), pItem != nullptr ||
		                                                                   (pItem = INVENTORY_GetItemFromBodyLoc(pPlayer->pInventory, 5), pItem != nullptr))))))
		{
			if ((pDVar6 != nullptr) &&
			    ((((iVar8 = ITEMS_CheckItemTypeId(pItem, 0x23), iVar8 == 0 &&
			                                                        (iVar8 = ITEMS_CheckItemTypeId(pDVar6, 0x23), iVar8 == 0)) &&
			          (iVar8 = ITEMS_CheckItemTypeId(pItem, 0x1b), iVar8 == 0)) &&
			        (iVar8 = ITEMS_CheckItemTypeId(pDVar6, 0x1b), iVar8 == 0))))
			{
				pDVar6 = pItem;
			}
			if (pItem != nullptr)
			{
				if (pDVar6 != nullptr)
					goto LAB_6fae84be;
				pDVar6 = pItem;
				if (dword_6FBB58EC != 4)
				{
					dword_6FB7928C = 1;
					dword_6FBB58E4 = 0;
					gpUnit_6FBB58F0 = nullptr;
					dword_6FBB58F4 = (uint32_t)(nullptr);
					return;
				}
			}
		}
		if (pDVar6 == nullptr)
		{
			dword_6FB7928C = 1;
			dword_6FBB58E4 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = (uint32_t)(nullptr);
			return;
		}
	LAB_6fae84be:
		dword_6FBB58E4 = 1;
		if (pDVar6 == (D2UnitStrc*)(dword_6FBB58F4))
		{
			dword_6FB7928C = 1;
			dword_6FBB58E4 = 1;
			return;
		}
		gpUnit_6FBB58F0 = pDVar6;
		dword_6FBB58F4 = (uint32_t)(pDVar6);
		dword_6FB79290 = (int)((&dword_6FBB595C)[iVar5 * 5] + (&dword_6FBB5958)[iVar5 * 5]) / 2;
		dword_6FB79298 = dword_6FB79290;
		dword_6FB79294 = (&dword_6FBB5960)[iVar5 * 5];
		dword_6FB7929C = (&dword_6FBB5964)[iVar5 * 5];
		dword_6FB7928C = 1;
		return;
	}
	if (dword_6FBB58EC != 0xb)
	{
		if (dword_6FBB58EC == 0xc)
		{
			iVar9 = sub_6FAAC080();
			iVar5 = dword_6FBB3730;
			iVar8 = dword_6FBB3734;
			iVar1 = dword_6FBB3738;
			iVar2 = dword_6FBB372C;
			if (iVar9 != 0)
			{
				iVar5 = dword_6FBB3768;
				iVar8 = dword_6FBB376C;
				iVar1 = dword_6FBB3770;
				iVar2 = dword_6FBB3764;
			}
			if (((iVar2 < (int)uVar10) && ((int)uVar10 <= iVar5)) &&
			    ((iVar8 <= (int)uVar11 && ((int)uVar11 <= iVar1))))
			{
				byte_6FBB5900 = 4;
				pDVar6 = INVENTORY_GetCursorItem(pInventory);
				iVar5 = sub_6FAAC080();
				if (iVar5 != 0)
				{
					sub_6FAE87C0(pPlayer, pInventory, pDVar6, uVar10, uVar11, &byte_6FBB3760, 4);
					dword_6FB7928C = 1;
					byte_6FBB5900 = uVar3;
					return;
				}
				sub_6FAE87C0(pPlayer, pInventory, pDVar6, uVar10, uVar11, &byte_6FBB3728, 4);
				dword_6FB7928C = 1;
				byte_6FBB5900 = uVar3;
				return;
			}
		}
		else
		{
			if (dword_6FBB58EC != 0xe)
			{
				iVar5 = sub_6FB23230(0x24);
				if (iVar5 == 0)
				{
					*(uint32_t*)(a1 + 0x18) = 0;
					dword_6FBB58E0 = 0;
					dword_6FBB58E4 = 0;
					gpUnit_6FBB58F0 = nullptr;
					dword_6FBB58F4 = (uint32_t)(nullptr);
					dword_6FB7928C = 0;
					return;
				}
				*(uint32_t*)(a1 + 0x18) = 0;
				return;
			}
			if (((dword_6FBB38B4 <= (int)uVar10) && ((int)uVar10 < dword_6FBB38B8)) &&
			    ((dword_6FBB38BC <= (int)uVar11 && ((int)uVar11 <= dword_6FBB38C0))))
			{
				byte_6FBB5900 = 3;
				pDVar6 = INVENTORY_GetCursorItem(pInventory);
				sub_6FAE87C0(pPlayer, pInventory, pDVar6, uVar10, uVar11, &byte_6FBB38B0, 3);
				dword_6FB7928C = 1;
				byte_6FBB5900 = uVar3;
				return;
			}
		}
		*(uint32_t*)(a1 + 0x18) = 0;
		dword_6FBB58F4 = (uint32_t)(nullptr);
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58E4 = 0;
		dword_6FBB58E0 = 0;
		dword_6FB7928C = 1;
		byte_6FBB5900 = uVar3;
		return;
	}
	if ((((dword_6FBB37FC < (int)uVar10) && ((int)uVar10 < dword_6FBB3800)) &&
	        (dword_6FBB3804 <= (int)uVar11)) &&
	    ((int)uVar11 <= dword_6FBB3808))
	{
		byte_6FBB5900 = 1;
		pDVar6 = INVENTORY_GetCursorItem(pInventory);
		uVar13 = 1;
		puVar12 = &byte_6FBB37F8;
	}
	else
	{
		if ((((int)uVar10 <= dword_6FBB383C) || (dword_6FBB3840 <= (int)uVar10)) ||
		    (((int)uVar11 < dword_6FBB3844 || (dword_6FBB3848 < (int)uVar11))))
			goto LAB_6fae85cd;
		byte_6FBB5900 = 2;
		pDVar6 = INVENTORY_GetCursorItem(pInventory);
		uVar13 = 2;
		puVar12 = &byte_6FBB3838;
	}
	sub_6FAE87C0(pPlayer, pInventory, pDVar6, uVar10, uVar11, puVar12, uVar13);
	bVar4 = true;
LAB_6fae85cd:
	byte_6FBB5900 = uVar3;
	if (!bVar4)
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		dword_6FBB58E0 = 0;
		dword_6FBB58E4 = 0;
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58F4 = (uint32_t)(nullptr);
	}
	dword_6FB7928C = 1;
}

//D2Client.0x6FAE87C0
void __fastcall sub_6FAE87C0(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, D2UnitStrc* pUnit2, uint32_t a4, uint32_t a5, uint8_t* a6, uint32_t a7)
{
	uint8_t bVar1;
	uint8_t bVar2;
	uint8_t* pbVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t nGridY;
	D2UnitStrc* pDVar6;
	int32_t DVar7;
	uint32_t uStack_10;
	D2InventoryStrc* local_c;
	int iStack_8;
	int iStack_4;

	local_c = pInventory;
	iVar4 = sub_6FAAC080();
	iVar4 = UNITS_GetInventoryRecordId(pUnit, a7, iVar4);
	pbVar3 = a6;
	pDVar6 = pUnit2;
	uVar5 = (a4 - *(int*)(a6 + 4)) / (uint32_t)a6[0x14];
	nGridY = (a5 - *(int*)(a6 + 0xc)) / (uint32_t)a6[0x15];
	if (pUnit2 == nullptr)
	{
		pDVar6 = INVENTORY_GetItemFromInventoryPage(local_c, uVar5, nGridY, &iStack_4, &iStack_8, iVar4, (uint8_t)a7);
		(*(uint16_t*)((uint8_t*)&DVar7 + 0)) = 0;
		(*(uint16_t*)((uint8_t*)&DVar7 + 2)) = 0;
		if (pDVar6 == nullptr)
		{
			dword_6FBB58E0 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = (uint32_t)(nullptr);
		}
		else
		{
			dword_6FBB58E0 = 1;
			if (pDVar6 != (D2UnitStrc*)(dword_6FBB58F4))
			{
				ITEMS_GetDimensions(pDVar6, (uint8_t*)&a4, (uint8_t*)&a5,
				    __FILE__, __LINE__);
				uVar5 = pDVar6->dwUnitType;
				if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
				{
					iVar4 = pDVar6->pDynamicPath->dwClientCoordY;
				}
				else if (pDVar6->pDynamicPath == nullptr)
				{
					iVar4 = 0;
				}
				else
				{
					iVar4 = PATH_GetXPosition(pDVar6->pDynamicPath);
				}
				uVar5 = pDVar6->dwUnitType;
				if ((uVar5 == 2) || ((3 < (int)uVar5 && ((int)uVar5 < 6))))
				{
					DVar7 = (*(int32_t*)&pDVar6->pDynamicPath->tTargetCoord);
				}
				else if (pDVar6->pDynamicPath != nullptr)
				{
					DVar7 = (int32_t)PATH_GetYPosition(pDVar6->pDynamicPath);
				}
				dword_6FB79290 = ((a4 & 0xff) * (uint32_t)pbVar3[0x14]) / 2 + (uint32_t)pbVar3[0x14] * iVar4 +
				                 *(int*)(pbVar3 + 4);
				dword_6FB79298 = dword_6FB79290;
				dword_6FB79294 = (uint32_t)pbVar3[0x15] * (int)DVar7 + *(int*)(pbVar3 + 0xc);
				gpUnit_6FBB58F0 = pDVar6;
				dword_6FBB58F4 = (uint32_t)(pDVar6);
				dword_6FB7929C = ((a5 & 0xff) + (int)DVar7) * (uint32_t)pbVar3[0x15] + *(int*)(pbVar3 + 0xc);
				return;
			}
		}
		return;
	}
	ITEMS_GetDimensions(pUnit2, (uint8_t*)&a7, (uint8_t*)&a6, __FILE__, __LINE__);
	sub_6FB5DFB0(pDVar6, 0, 0, (int*)(&pUnit2), (int*)(&uStack_10));
	if ((a7 & 1) == 0)
	{
		uVar5 = ((((uint32_t)pUnit2 >> 2) - *(int*)(pbVar3 + 4)) + a4) / (uint32_t)pbVar3[0x14];
	}
	bVar1 = *pbVar3;
	if ((uint8_t)a7 == bVar1)
	{
		uVar5 = (uint32_t)(bVar1 >> 1);
	}
	if (((uint32_t)a6 & 1) == 0)
	{
		nGridY = (((uStack_10 >> 2) - *(int*)(pbVar3 + 0xc)) + a5) / (uint32_t)pbVar3[0x15];
	}
	bVar2 = pbVar3[1];
	if ((uint8_t)a6 == bVar2)
	{
		nGridY = (uint32_t)(bVar2 >> 1);
	}
	if (1 < (uint8_t)a7)
	{
		uVar5 = uVar5 - ((a7 & 0xff) >> 1);
		if ((int)uVar5 < 0)
		{
			uVar5 = 0;
		}
		if ((int)(uint32_t)bVar1 < (int)((a7 & 0xff) + uVar5))
		{
			return;
		}
	}
	if (1 < (uint8_t)a6)
	{
		nGridY = nGridY - (((uint32_t)a6 & 0xff) >> 1);
		if ((int)nGridY < 0)
		{
			nGridY = 0;
		}
		if ((int)(uint32_t)bVar2 < (int)(((uint32_t)a6 & 0xff) + nGridY))
		{
			return;
		}
	}
	dword_6FB792A4 = nGridY;
	dword_6FB792A0 = uVar5;
	dword_6FBB58E0 = 1;
	gpUnit_6FBB58F0 = nullptr;
	dword_6FBB58F4 = (uint32_t)(nullptr);
}

//D2Client.0x6FAE8AA0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAE8AA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pDVar1;
	bool bVar2;
	int iVar3;
	uint32_t extraout_var;
	D2UnitStrc* pDVar4;
	uint32_t* puVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar6;
	uint32_t uVar7;

	iVar3 = sub_6FAABF20();
	if ((iVar3 != 0) || (bVar2 = sub_6FB283E0(), D2C_ZEXT(bVar2) != 0))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar7 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	pDVar4 = CUNIT_GetPlayer();
	sub_6FAE0A10();
	pDVar1 = pDVar4->pInventory;
	iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar3 != 0)
	{
		return;
	}
	if ((int)uVar6 < dword_6FBB38C8)
	{
		return;
	}
	if (dword_6FBB38CC <= (int)uVar6)
	{
		return;
	}
	if ((int)uVar7 < dword_6FBB38D0)
	{
		return;
	}
	if (dword_6FBB38D4 < (int)uVar7)
	{
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	if (((((int)uVar6 < dword_6FBB3714) || (dword_6FBB3718 < (int)uVar6)) || ((int)uVar7 < dword_6FBB371C)) || (dword_6FBB3720 < (int)uVar7))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
	LAB_6fae8b8f:
		if (dword_6FBB58EC == 0)
		{
			iVar3 = sub_6FB57CC0();
			if (iVar3 == 6)
			{
				sub_6FB23A40();
				return;
			}
			iVar3 = sub_6FB57CC0();
			if (iVar3 != 8)
			{
				return;
			}
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x4c), 0xffffffff);
			return;
		}
		iVar3 = sub_6FB57CC0();
		if (iVar3 == 6)
		{
			sub_6FB23A40();
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		iVar3 = sub_6FB57CC0();
		if (iVar3 == 8)
		{
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), 0xffffffff);
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		if ((dword_6FBB58EC < 2) || (4 < dword_6FBB58EC))
			goto LAB_6fae8c14;
		puVar5 = &dword_6FBB37AC;
		do
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 5;
		} while ((int)puVar5 < (int)&dword_6FBB37FC);
	}
	else
	{
		iVar3 = sub_6FAE8C60(pDVar4, pDVar1, uVar6, uVar7, 0);
		if (iVar3 == 0)
			goto LAB_6fae8b8f;
		if ((dword_6FBB58EC < 2) || (4 < dword_6FBB58EC))
			goto LAB_6fae8c14;
		puVar5 = &dword_6FBB37AC;
		do
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 5;
		} while ((int)puVar5 < (int)&dword_6FBB37FC);
	}
	dword_6FBB58EC = 1;
	pDVar4 = CUNIT_GetPlayer();
	pDVar4 = INVENTORY_GetCursorItem(pDVar4->pInventory);
	sub_6FB575B0(pDVar4);
LAB_6fae8c14:
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAE8C60
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAE8C60(D2UnitStrc* pUnit, D2InventoryStrc* pInventory, int a3, int a4, int a5)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar4;
	int32_t DVar5;
	int iVar6;
	DWORD DVar7;
	D2ItemsTxt* pDVar8;
	uint32_t uVar9;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t uVar10;
	float fVar11;
	float fVar12;
	int iStack_8;
	int iStack_4;

	iVar1 = sub_6FAAC080();
	iVar1 = UNITS_GetInventoryRecordId(pUnit, a5, iVar1);
	if ((uint8_t)a5 == 0)
	{
		uVar2 = (uint32_t)(a3 - dword_6FBB3714) / (dword_6FBB3724 & 0xff);
		uVar3 = a4 - dword_6FBB371C;
		uVar9 = dword_6FBB3724 >> 8 & 0xff;
	}
	else
	{
		iVar6 = sub_6FAAC080();
		if (iVar6 == 0)
		{
			uVar2 = (uint32_t)(a3 - dword_6FBB372C) / (dword_6FBB373C & 0xff);
			uVar3 = a4 - dword_6FBB3734;
			uVar9 = dword_6FBB373C >> 8 & 0xff;
		}
		else
		{
			uVar2 = (uint32_t)(a3 - dword_6FBB3764) / (dword_6FBB3774 & 0xff);
			uVar3 = a4 - dword_6FBB376C;
			uVar9 = dword_6FBB3774 >> 8 & 0xff;
		}
	}
	pItem = INVENTORY_GetItemFromInventoryPage(pInventory, uVar2, uVar3 / uVar9, &iStack_4, &iStack_8, iVar1, (uint8_t)a5);
	if (pItem != nullptr)
	{
		pDVar4 = INVENTORY_GetCursorItem(pInventory);
		if ((pDVar4 == nullptr) && (uVar2 = ITEMS_GetTransmogrify(pItem), uVar2 != 0))
		{
			iVar1 = sub_6FB2FB90(pItem);
			if (iVar1 != 0)
			{
				return 0;
			}
			sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), pItem->dwUnitId);
			sub_6FB2FB30(pItem);
			return 1;
		}
		iVar1 = ITEMS_CheckIfUseable(pItem);
		if (iVar1 == 0)
		{
			iVar1 = ITEMS_GetUniqueColumnFromItemsTxt(pItem);
			if (iVar1 != 0)
			{
				pDVar8 = DATATBLS_GetItemsTxtRecord(pItem->dwClassId);
				uVar2 = pDVar8->dwCode;
				if (((uVar2 == 0x20737274) || (uVar2 == 0x20736b62)) || (uVar2 == 0x20646b62))
				{
					sub_6FB1EE20((int)pItem, (int)pDVar8);
				}
				return 1;
			}
		}
		else
		{
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
			{
				iVar1 = pUnit->pDynamicPath->dwClientCoordY;
			}
			else if (pUnit->pDynamicPath == nullptr)
			{
				iVar1 = 0;
			}
			else
			{
				iVar1 = PATH_GetXPosition(pUnit->pDynamicPath);
			}
			uVar2 = pUnit->dwUnitType;
			if ((uVar2 == 2) || ((3 < (int)uVar2 && ((int)uVar2 < 6))))
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
			iVar6 = sub_6FB2FB90(pItem);
			if (iVar6 == 0)
			{
				iVar6 = sub_6FAABFF0();
				if ((iVar6 != 0) && (iVar6 = sub_6FAABFF0(), iVar6 != 1))
				{
					iVar6 = sub_6FB1FFF0();
					if (iVar6 != 0)
					{
						sub_6FB1FF00(extraout_ECX_00);
						return 0;
					}
					DVar7 = GetTickCount();
					if (DVar7 - byte_6FBB3870 < 0xfb)
					{
						return 0;
					}
					byte_6FBB3870 = GetTickCount();
				}
				iVar6 = sub_6FB23230(0x19);
				uVar10 = extraout_ECX_01;
				if ((iVar6 != 0) &&
				    (uVar2 = ITEMS_GetBaseCode(pItem), uVar10 = extraout_ECX_02, uVar2 == 0x20786f62))
				{
					dword_6FBB5950 = 1;
				}
				sub_6FAADA70(CONCAT31((int32_t)((uint32_t)uVar10 >> 8), 0x20), pItem->dwUnitId, iVar1, DVar5);
				sub_6FB2FB30(pItem);
				iVar6 = 0;
				fVar12 = 0.0;
				fVar11 = 0.0;
				iVar1 = sub_6FB2E5A0(pItem);
				sub_6FB55820(iVar1, nullptr, fVar11, fVar12, iVar6);
				dword_6FBB58E0 = 0;
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAE8F10
void __cdecl sub_6FAE8F10()
{
	dword_6FB79290 = 0xffffffff;
	dword_6FB79294 = 0xffffffff;
	dword_6FB79298 = 0xffffffff;
	dword_6FB7929C = 0xffffffff;
	dword_6FB792A0 = 0xffffffff;
	dword_6FB792A4 = 0xffffffff;
	dword_6FBB58E0 = 0;
	dword_6FBB58E4 = 0;
	gpUnit_6FBB58F0 = nullptr;
	dword_6FBB58F4 = 0;
}

//D2Client.0x6FAE8F50
void __fastcall sub_6FAE8F50(D2UnitStrc* pUnit)
{
	if (gpUnit_6FBB58F0 == pUnit)
	{
		dword_6FB79290 = 0xffffffff;
		dword_6FB79294 = 0xffffffff;
		dword_6FB79298 = 0xffffffff;
		dword_6FB7929C = 0xffffffff;
		dword_6FB792A0 = 0xffffffff;
		dword_6FB792A4 = 0xffffffff;
		dword_6FBB58E0 = 0;
		dword_6FBB58E4 = 0;
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58F4 = 0;
	}
}

//D2Client.0x6FAE8F90
void __fastcall sub_6FAE8F90(uint32_t a1)
{
	uint32_t uVar1;
	uint8_t bVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pItem;
	int iVar5;
	uint32_t* puVar6;
	uint8_t bVar7;
	int iVar8;
	uint32_t local_1c;
	uint32_t uStack_18;
	int aiStack_14[5];

	bVar7 = (uint8_t)a1;
	local_1c = a1;
	if (4 < bVar7)
	{
		bVar7 = 0;
		local_1c = a1 & 0xffffff00;
	}
	uVar1 = local_1c;
	if ((((dword_6FBB5904 == 0) && (iVar3 = sub_6FAFBB50(&local_1c), iVar3 != 0)) &&
	        (pDVar4 = sub_6FB269F0(local_1c, 1), pDVar4 != nullptr)) &&
	    (pDVar4->pInventory != nullptr))
	{
		pDVar4 = INVENTORY_GetFirstItem(pDVar4->pInventory);
		aiStack_14[0] = 0;
		aiStack_14[1] = 0;
		aiStack_14[2] = 0;
		aiStack_14[3] = 0;
		aiStack_14[4] = 0;
		iVar3 = dword_6FB795A8;
		while (dword_6FB795A8 = iVar3, pDVar4 != nullptr)
		{
			pItem = INVENTORY_UnitIsItem(pDVar4);
			bVar2 = ITEMS_GetInvPage(pItem);
			uStack_18 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_18 + 1)), bVar2);
			if (bVar2 < 5)
			{
				aiStack_14[bVar2] = aiStack_14[bVar2] + 1;
			}
			pDVar4 = INVENTORY_GetNextItem(pDVar4);
			iVar3 = dword_6FB795A8;
		}
		iVar8 = 0;
		iVar5 = 0;
		dword_6FBB5901 = (uint32_t)(byte_6FBB5900 >> 8);
		byte_6FBB5900 = CONCAT31(dword_6FBB5901, bVar7);
		if (0 < iVar3)
		{
			puVar6 = &dword_6FB7956E;
			do
			{
				puVar6[-1] = 0;
				*puVar6 = (uint32_t)(aiStack_14[iVar5] != 0);
				iVar5 = iVar5 + 1;
				puVar6 = (uint32_t*)((int)puVar6 + 0x12);
			} while (iVar5 < iVar3);
		}
		if (aiStack_14[uVar1 & 0xff] == 0)
		{
			do
			{
				bVar7 = bVar7 + 1;
				iVar8 = iVar8 + 1;
				if ((byte_6FBB5908 < bVar7) || (bVar7 == 0xff))
				{
					bVar7 = 0;
				}
				byte_6FBB5900 = CONCAT31(dword_6FBB5901, bVar7);
			} while ((aiStack_14[bVar7] == 0) && (iVar8 < 4));
		}
		*(uint32_t*)((int)&dword_6FB7956A + (byte_6FBB5900 & 0xff) * 0x12) = 1;
	}
}

//D2Client.0x6FAE90F0
void __cdecl sub_6FAE90F0()
{
	dword_6FBB58EC = 0;
	byte_6FBB5900 = 0;
	dword_6FBB5B38 = 0;
	dword_6FBB388C = 0;
	dword_6FBB3894 = 0;
	if (gpCellFile_6FBB3890 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB3890);
		gpCellFile_6FBB3890 = nullptr;
	}
	byte_6FBB3870 = 0;
}

//D2Client.0x6FAE9130
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAE9130()
{
	uint32_t uVar1;
	bool bVar2;
	uint32_t* puVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	DWORD DVar6;
	int iVar7;
	uint32_t extraout_ECX;
	uint32_t local_8;
	uint32_t local_4;

	dword_6FBB5940 = -1;
	byte_6FBB5900 = 0;
	dword_6FBB5B38 = 0;
	byte_6FBB3790 = 0;
	if (0 < dword_6FB795A8)
	{
		puVar3 = &dword_6FB7956E;
		iVar7 = dword_6FB795A8;
		do
		{
			puVar3[-1] = 0;
			*puVar3 = 0;
			puVar3 = (uint32_t*)((int)puVar3 + 0x12);
			iVar7 = iVar7 + -1;
		} while (iVar7 != 0);
	}
	dword_6FBB58E8 = 0;
	dword_6FBB58EC = 1;
	iVar7 = sub_6FAFC130();
	iVar4 = sub_6FAFBB50(&local_8);
	if ((iVar4 != 0) && (pDVar5 = sub_6FB269F0(local_8, 1), pDVar5 != nullptr))
	{
		if (iVar7 == 0)
		{
			iVar7 = pDVar5->dwClassId;
			if (iVar7 < 0xfd)
			{
				if (iVar7 != 0xfc)
				{
					switch (iVar7)
					{
					case 0x93:
					case 0x94:
					case 0xb1:
					case 199:
					case 0xca:
						break;
					default:
						goto switchD_6fae92e7_caseD_95;
					case 0x9a:
					case 0xb2:
						goto switchD_6fae92e7_caseD_9a;
					}
				}
			switchD_6fae92e7_caseD_93:
				byte_6FBB5908 = 3;
				sub_6FAE9710(0);
				sub_6FAE9750(1);
				sub_6FAE9790(2);
				goto LAB_6fae922b;
			}
			if (iVar7 < 0x196)
			{
				if (iVar7 != 0x195)
				{
					switch (iVar7)
					{
					case 0xfd:
					case 0x101:
						goto switchD_6fae92e7_caseD_9a;
					case 0xfe:
					case 0xff:
						break;
					default:
						goto switchD_6fae92e7_caseD_95;
					}
				}
				goto switchD_6fae92e7_caseD_93;
			}
			if (iVar7 != 0x1ff)
			{
				if ((iVar7 < 0x200) || (0x201 < iVar7))
				{
				switchD_6fae92e7_caseD_95:
					dword_6FB795B0 = 0;
					goto LAB_6fae9272;
				}
				goto switchD_6fae92e7_caseD_93;
			}
		switchD_6fae92e7_caseD_9a:
			byte_6FBB5908 = 3;
			word_6FBB37B0 = 0xd07;
			dword_6FBB37B2 = 2;
			dword_6FBB37B8 = 3;
			word_6FBB37B6 = 2;
			dword_6FBB37A8 = 1;
			sub_6FAE9750(1);
			sub_6FAE96D0(2);
			sub_6FAE9690(3);
		}
		else
		{
			byte_6FBB5908 = 1;
			word_6FBB37B0 = 0xd07;
			dword_6FBB37B2 = 2;
			dword_6FBB37B8 = 3;
			word_6FBB37B6 = 2;
			dword_6FBB37A8 = 1;
			byte_6FBB37C4 = 0xd08;
			byte_6FBB37C6 = 3;
			byte_6FBB37CC = 4;
			word_6FBB37CA = 4;
			dword_6FBB37BC = 1;
			byte_6FBB37D8 = 0;
			byte_6FBB37DA = 1;
			byte_6FBB37E0 = 1;
			byte_6FBB37DE = 0;
			byte_6FBB37D0 = 0;
		LAB_6fae922b:
			byte_6FBB37E4 = 1;
			byte_6FBB37EC = 0x1030;
			byte_6FBB37EE = 9;
			byte_6FBB37F2 = 10;
		}
		dword_6FB795B0 = 4;
		dword_6FB795AC = 3;
		puVar3 = &dword_6FBB37AC;
		do
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 5;
		} while ((int)puVar3 < (int)&dword_6FBB37FC);
	}
LAB_6fae9272:
	iVar7 = sub_6FAFBB50(&local_4);
	if (iVar7 == 0)
	{
		return;
	}
	pDVar5 = sub_6FB269F0(local_4, 1);
	bVar2 = false;
	if (pDVar5 == nullptr)
		goto switchD_6fae92c2_caseD_95;
	uVar1 = pDVar5->dwClassId;
	if (uVar1 < 0x100)
	{
		if (uVar1 == 0xff)
			goto switchD_6fae92c2_caseD_94;
		switch (uVar1)
		{
		case 0x93:
		switchD_6fae92c2_caseD_93:
			byte_6FBB5900 = 0;
			break;
		case 0x94:
		case 0xb1:
		case 0xb2:
		case 0xca:
		case 0xfc:
		case 0xfd:
			goto switchD_6fae92c2_caseD_94;
		default:
			goto switchD_6fae92c2_caseD_95;
		case 0x9a:
		switchD_6fae92c2_caseD_9a:
			byte_6FBB5900 = 1;
		}
	}
	else
	{
		if (uVar1 < 0x200)
		{
			if (uVar1 == 0x1ff)
				goto switchD_6fae92c2_caseD_9a;
			if ((uVar1 != 0x101) && (uVar1 != 0x195))
				goto switchD_6fae92c2_caseD_95;
		}
		else
		{
			if (uVar1 == 0x200)
				goto switchD_6fae92c2_caseD_93;
			if (uVar1 != 0x201)
				goto switchD_6fae92c2_caseD_95;
		}
	switchD_6fae92c2_caseD_94:
		byte_6FBB5900 = 3;
	}
	bVar2 = true;
switchD_6fae92c2_caseD_95:
	sub_6FAE8F90(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5900));
	if (bVar2)
	{
		DVar6 = GetTickCount();
		dword_6FBB5904 = DVar6 + 500;
	}
}

//D2Client.0x6FAE94D0
void __cdecl sub_6FAE94D0()
{
	dword_6FBB590C = 1;
}

//D2Client.0x6FAE94E0
void __cdecl sub_6FAE94E0()
{
	byte_6FBB5900 = 0;
	dword_6FBB58EC = 0x13;
}

//D2Client.0x6FAE9500
void __cdecl sub_6FAE9500()
{
	uint32_t* puVar1;
	D2UnitStrc* pDVar2;

	if (dword_6FBB58EC != 5)
	{
		FOG_Trace("Inventory mode is %d\n", dword_6FBB58EC);
		return;
	}
	puVar1 = &dword_6FBB37AC;
	do
	{
		*puVar1 = 0;
		puVar1 = puVar1 + 5;
	} while ((int)puVar1 < (int)&dword_6FBB37FC);
	dword_6FBB58EC = 1;
	pDVar2 = CUNIT_GetPlayer();
	pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	sub_6FB575B0(pDVar2);
}

//D2Client.0x6FAE9550
void __cdecl sub_6FAE9550()
{
	D2_ASSERT(dword_6FBB58EC == 5);
	dword_6FBB58EC = 6;
}

//D2Client.0x6FAE9590
uint32_t __cdecl sub_6FAE9590()
{
	if (dword_6FBB58EC == 6)
	{
		return 0;
	}
	dword_6FBB58EC = 6;
	return 1;
}

//D2Client.0x6FAE95B0
void __cdecl sub_6FAE95B0()
{
	int iVar1;
	int iVar2;
	uint32_t* puVar3;
	D2UnitStrc* pDVar4;
	int* piVar5;

	iVar2 = 0;
	dword_6FBB5940 = -1;
	iVar1 = dword_6FBB5940;
	if (0 < dword_6FB795B0)
	{
		piVar5 = (int*)(&dword_6FBB37AC);
		do
		{
			iVar1 = iVar2;
			if (*piVar5 != 0)
				break;
			iVar2 = iVar2 + 1;
			piVar5 = piVar5 + 5;
			iVar1 = dword_6FBB5940;
		} while (iVar2 < dword_6FB795B0);
	}
	dword_6FBB5940 = iVar1;
	puVar3 = &dword_6FBB37AC;
	do
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 5;
	} while ((int)puVar3 < (int)&dword_6FBB37FC);
	dword_6FBB58EC = 1;
	pDVar4 = CUNIT_GetPlayer();
	pDVar4 = INVENTORY_GetCursorItem(pDVar4->pInventory);
	sub_6FB575B0(pDVar4);
}

//D2Client.0x6FAE9620
void __cdecl sub_6FAE9620()
{
	dword_6FBB58EC = 7;
}

//D2Client.0x6FAE9630
void __cdecl sub_6FAE9630()
{
	uint32_t* puVar1;
	D2UnitStrc* pDVar2;

	D2_ASSERT(dword_6FBB58EC == 7);
	puVar1 = &dword_6FBB37AC;
	do
	{
		*puVar1 = 0;
		puVar1 = puVar1 + 5;
	} while ((int)puVar1 < (int)&dword_6FBB37FC);
	dword_6FBB58EC = 1;
	pDVar2 = CUNIT_GetPlayer();
	pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	sub_6FB575B0(pDVar2);
}

//D2Client.0x6FAE9690
void __fastcall sub_6FAE9690(int a1)
{
	(&word_6FBB37B0)[a1 * 10] = 0x276f;
	(&dword_6FBB37B2)[a1 * 5] = 1;
	(&dword_6FBB37B8)[a1 * 5] = 8;
	(&word_6FBB37B6)[a1 * 10] = 0x12;
	(&dword_6FBB37A8)[a1 * 5] = 1;
}

//D2Client.0x6FAE96D0
void __fastcall sub_6FAE96D0(int a1)
{
	(&word_6FBB37B0)[a1 * 10] = 0xd0a;
	(&dword_6FBB37B2)[a1 * 5] = 4;
	(&dword_6FBB37B8)[a1 * 5] = 1;
	(&word_6FBB37B6)[a1 * 10] = 6;
	(&dword_6FBB37A8)[a1 * 5] = 1;
}

//D2Client.0x6FAE9710
void __fastcall sub_6FAE9710(int a1)
{
	(&word_6FBB37B0)[a1 * 10] = 0xd07;
	(&dword_6FBB37B2)[a1 * 5] = 2;
	(&dword_6FBB37B8)[a1 * 5] = 3;
	(&word_6FBB37B6)[a1 * 10] = 2;
	(&dword_6FBB37A8)[a1 * 5] = 1;
}

//D2Client.0x6FAE9750
void __fastcall sub_6FAE9750(int a1)
{
	(&word_6FBB37B0)[a1 * 10] = 0xd08;
	(&dword_6FBB37B2)[a1 * 5] = 3;
	(&dword_6FBB37B8)[a1 * 5] = 4;
	(&word_6FBB37B6)[a1 * 10] = 4;
	(&dword_6FBB37A8)[a1 * 5] = 1;
}

//D2Client.0x6FAE9790
void __fastcall sub_6FAE9790(int a1)
{
	(&word_6FBB37B0)[a1 * 10] = 0;
	(&dword_6FBB37B2)[a1 * 5] = 1;
	(&dword_6FBB37B8)[a1 * 5] = 1;
	(&word_6FBB37B6)[a1 * 10] = 0;
	(&dword_6FBB37A8)[a1 * 5] = 0;
}

//D2Client.0x6FAE97C0
void __fastcall sub_6FAE97C0(int a1)
{
	Font nFontSize;
	D2UnitStrc* pDVar1;
	Unicode* pUVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	D2GfxDataStrc* pDVar6;
	int iVar7;
	int iVar8;
	uint16_t nLayer;
	int iVar9;
	int iStack_118;
	int iStack_114;
	uint32_t uStack_10c;
	int iStack_108;
	int iStack_104;
	D2GfxDataStrc DStack_fc;
	Unicode aUStack_b4[20];
	char acStack_8c[20];
	Unicode aUStack_78[60];

	nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
	nLayer = 0;
	pDVar6 = &DStack_fc;
	for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	DStack_fc.nDirection = 0;
	if (a1 == 0)
	{
		iVar5 = 0xf;
		pDVar1 = CUNIT_GetPlayer();
		iStack_104 = STATLIST_UnitGetStatValue(pDVar1, iVar5, nLayer);
		iStack_114 = dword_6FBBA748 + 0xa5;
		iVar5 = sub_6FAAC080();
		if (iVar5 == 0)
		{
			iVar5 = dword_6FBBA74C + -0xf4;
			iStack_118 = dword_6FBBA74C + -0xf2;
		}
		else
		{
			iVar5 = dword_6FBBA74C + -0x1b8;
			iStack_118 = dword_6FBBA74C + -0x1b6;
		}
		iStack_118 = iStack_118 + gnScreenHeight;
		iVar5 = iVar5 + gnScreenHeight;
		iStack_108 = dword_6FBBA748 + 0x49;
		uStack_10c = (uint32_t)(dword_6FBB5B3C != 0);
		iVar8 = sub_6FAAC080();
		iVar7 = dword_6FBBA748;
		if (iVar8 == 0)
		{
			iVar9 = dword_6FBBA74C + -0xf2 + gnScreenHeight;
			iVar8 = dword_6FBBA748 + 0x49;
			iVar3 = sub_6FB57BC0();
			iVar4 = sub_6FB57BD0();
			if ((((iVar8 <= iVar3) && (iVar3 <= iVar7 + 0x5d)) && (iVar9 + -0x12 <= iVar4)) &&
			    (iVar4 <= iVar9))
			{
				iVar7 = dword_6FBBA74C + -0x106 + gnScreenHeight;
				goto LAB_6fae99af;
			}
		}
		else
		{
			iVar9 = dword_6FBBA74C + -0x1b6 + gnScreenHeight;
			iVar8 = dword_6FBBA748 + 0x49;
			iVar3 = sub_6FB57BC0();
			iVar4 = sub_6FB57BD0();
			if (((iVar8 <= iVar3) && (iVar3 <= iVar7 + 0x5d)) &&
			    ((iVar9 + -0x12 <= iVar4 && (iVar4 <= iVar9))))
			{
				iVar7 = dword_6FBBA74C + -0x1ca + gnScreenHeight;
			LAB_6fae99af:
				iVar3 = 0;
				iVar9 = 0;
				iVar8 = dword_6FBBA748 + 0x35;
				pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x101c));
				D2Win_10129_DrawFramedText(pUVar2, iVar8, iVar7, iVar9, iVar3);
			}
		}
	}
	else if (a1 == 1)
	{
		iVar5 = 0xe;
		pDVar1 = CUNIT_GetPlayer();
		iStack_104 = STATLIST_UnitGetStatValue(pDVar1, iVar5, nLayer);
		iStack_114 = (gnScreenWidth - dword_6FBBA748) + -0xd4;
		iStack_108 = (gnScreenWidth - dword_6FBBA748) + -0xed;
		iStack_118 = dword_6FBBA74C + -0x45 + gnScreenHeight;
		iVar5 = dword_6FBBA74C + -0x48 + gnScreenHeight;
		uStack_10c = (uint32_t)(dword_6FBB5B38 != 0);
	}
	else
	{
		iVar5 = 0xf;
		pDVar1 = CUNIT_GetPlayer();
		iStack_104 = STATLIST_UnitGetStatValue(pDVar1, iVar5, nLayer);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xcf3));
		iVar5 = D2Win_10121_GetTextWidth(pUVar2);
		iStack_118 = 0;
		iStack_114 = iVar5 + 0x15 + dword_6FBBA748;
		iVar5 = dword_6FBBA74C + -0x6a + gnScreenHeight;
		iStack_108 = 0;
		uStack_10c = 0;
		iVar7 = 0;
		DStack_fc.nFrame = 0;
		if (a1 == 3)
			goto LAB_6fae9a55;
	}
	SStrPrintf(acStack_8c, 0x14, "%d", iStack_104);
	Unicode::win2Unicode(aUStack_b4, acStack_8c, 0x13);
	if (a1 == 2)
	{
		iVar7 = D2Win_10121_GetTextWidth(aUStack_b4);
		iStack_114 = (dword_6FBBA748 - iVar7) + 0xc6;
	}
	D2Win_10117_DrawText(aUStack_b4, iStack_114, iVar5, 0, 0);
	iVar7 = iStack_108;
	DStack_fc.nFrame = uStack_10c;
LAB_6fae9a55:
	if (a1 == 0)
	{
		if (dword_6FBB5B3C != 0)
		{
			iStack_118 = iStack_118 + 1;
		}
		iVar7 = iVar7 + 2;
	}
	else
	{
		if (a1 != 1)
		{
			iVar9 = 0;
			iVar8 = 0;
			iVar7 = dword_6FBBA748 + 0x15;
			pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xcf3));
			D2Win_10117_DrawText(pUVar2, iVar7, iVar5, iVar8, iVar9);
			D2Win_10127_SetFont(nFontSize);
			return;
		}
		if (dword_6FBB5B38 != 0)
		{
			iStack_118 = iStack_118 + 1;
		}
		iVar7 = iVar7 + 1;
	}
	DStack_fc.pCellFile = gpCellFile_6FBB5934;
	TEXTURE_CelDraw(&DStack_fc, iVar7, iStack_118 + -2, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FAE9B60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAE9B60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	SMSGHANDLER_PARAMS* pData;
	bool bVar4;
	D2UnitStrc* pDVar5;
	int iVar6;
	uint32_t extraout_var;
	D2UnitStrc* pDVar7;
	int iVar8;
	uint32_t* puVar9;
	uint32_t extraout_ECX;
	uint32_t uVar10;
	uint32_t uVar11;

	pDVar5 = CUNIT_GetPlayer();
	iVar6 = sub_6FAABF20();
	if (iVar6 != 0)
	{
		return;
	}
	if (pDVar5 == nullptr)
	{
		return;
	}
	bVar4 = sub_6FB283E0();
	pData = pSMSGHANDLER_PARAMS;
	if (D2C_ZEXT(bVar4) != 0)
	{
		return;
	}
	uVar10 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar11 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if ((((dword_6FBB3714 <= (int)uVar10) && ((int)uVar10 <= dword_6FBB3718)) &&
	        (dword_6FBB371C <= (int)uVar11)) &&
	    ((int)uVar11 <= dword_6FBB3720))
	{
		sub_6FAE8AA0(pSMSGHANDLER_PARAMS);
		return;
	}
	iVar6 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar6 == 1)
	{
		return;
	}
	iVar6 = sub_6FB57CC0();
	if (iVar6 == 6)
	{
		sub_6FB23A40();
		goto LAB_6fae9fa3;
	}
	iVar6 = sub_6FB57CC0();
	if (iVar6 == 8)
	{
		sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4c), 0xffffffff);
		goto LAB_6fae9fa3;
	}
	pDVar7 = INVENTORY_GetCursorItem(pDVar5->pInventory);
	if (pDVar7 != nullptr)
	{
		if ((dword_6FBB58EC < 2) || (4 < dword_6FBB58EC))
			goto LAB_6fae9fa3;
		puVar9 = &dword_6FBB37AC;
		do
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 5;
		} while ((int)puVar9 < (int)&dword_6FBB37FC);
		goto LAB_6fae9f8e;
	}
	if ((dword_6FBB58EC != 1) && (dword_6FBB58EC != 2))
	{
		if (dword_6FBB58EC == 0xe)
		{
			if (((((int)uVar10 < dword_6FBB38B4) || (dword_6FBB38B8 <= (int)uVar10)) ||
			        ((int)uVar11 < dword_6FBB38BC)) ||
			    (dword_6FBB38C0 < (int)uVar11))
				goto LAB_6fae9fa3;
			goto LAB_6fae9c65;
		}
		if (dword_6FBB58EC == 0xc)
		{
			iVar8 = sub_6FAAC080();
			iVar6 = dword_6FBB3730;
			iVar1 = dword_6FBB3734;
			iVar2 = dword_6FBB3738;
			iVar3 = dword_6FBB372C;
			if (iVar8 != 0)
			{
				iVar6 = dword_6FBB3768;
				iVar1 = dword_6FBB376C;
				iVar2 = dword_6FBB3770;
				iVar3 = dword_6FBB3764;
			}
			if (((iVar3 < (int)uVar10) && ((int)uVar10 <= iVar6)) &&
			    ((iVar1 <= (int)uVar11 && ((int)uVar11 <= iVar2))))
			{
				if ((((dword_6FBB38C8 <= (int)uVar10) && ((int)uVar10 < dword_6FBB38CC)) &&
				        (dword_6FBB38D0 <= (int)uVar11)) &&
				    ((int)uVar11 <= dword_6FBB38D4))
				{
					sub_6FAE8AA0(pData);
					goto LAB_6fae9fa3;
				}
				iVar6 = sub_6FAAC080();
				if (iVar6 == 0)
				{
					if (((((int)uVar10 <= dword_6FBB372C) || (dword_6FBB3730 < (int)uVar10)) ||
					        ((int)uVar11 < dword_6FBB3734)) ||
					    (dword_6FBB3738 < (int)uVar11))
						goto LAB_6fae9c65;
				}
				else
				{
					if ((((int)uVar10 <= dword_6FBB3764) || (dword_6FBB3768 < (int)uVar10)) ||
					    ((int)uVar11 < dword_6FBB376C))
					{
					LAB_6fae9c65:
						sub_6FB514E0(pDVar5, 0x13);
						goto LAB_6fae9fa3;
					}
					if (dword_6FBB3770 < (int)uVar11)
					{
						sub_6FB514E0(pDVar5, 0x13);
						goto LAB_6fae9fa3;
					}
				}
				sub_6FAE8C60(pDVar5, pDVar5->pInventory, uVar10, uVar11, 4);
				goto LAB_6fae9fa3;
			}
		}
		if ((dword_6FBB58EC < 2) || (4 < dword_6FBB58EC))
			goto LAB_6fae9fa3;
		puVar9 = &dword_6FBB37AC;
		do
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 5;
		} while ((int)puVar9 < (int)&dword_6FBB37FC);
		goto LAB_6fae9f8e;
	}
	if ((dword_6FBB38C8 < (int)uVar10) || (dword_6FBB38D4 < (int)uVar11))
		goto LAB_6fae9fa3;
	pData->bUseResult = 1;
	pData->lResult = 0;
	SMsgBreakHandlerChain(pData);
	if (((((int)uVar10 < dword_6FBB389C) || (dword_6FBB38A0 < (int)uVar10)) ||
	        ((int)uVar11 < dword_6FBB38A4)) ||
	    (dword_6FBB38A8 < (int)uVar11))
	{
		if (((dword_6FBB58EC != 1) && (dword_6FBB58EC != 2)) && ((dword_6FBB58EC != 4 && (dword_6FBB58EC != 3))))
			goto LAB_6fae9fa3;
		pDVar5 = CUNIT_GetPlayer();
		pDVar5 = INVENTORY_GetCursorItem(pDVar5->pInventory);
		if ((pDVar5 != nullptr) ||
		    (((iVar6 = sub_6FB57CC0(), iVar6 != 7 && (iVar6 != 1)) && (iVar6 != 4))))
			goto LAB_6fae9fa3;
		puVar9 = &dword_6FBB37AC;
		do
		{
			*puVar9 = 0;
			puVar9 = puVar9 + 5;
		} while ((int)puVar9 < (int)&dword_6FBB37FC);
	LAB_6fae9f8e:
		dword_6FBB58EC = 1;
		pDVar5 = CUNIT_GetPlayer();
		pDVar5 = INVENTORY_GetCursorItem(pDVar5->pInventory);
	}
	else
	{
		if (gpUnit_6FBB58F0 == nullptr)
		{
			if ((((dword_6FBB58EC != 1) && (dword_6FBB58EC != 2)) && (dword_6FBB58EC != 4)) &&
			    (dword_6FBB58EC != 3))
				goto LAB_6fae9fa3;
			pDVar5 = CUNIT_GetPlayer();
			pDVar5 = INVENTORY_GetCursorItem(pDVar5->pInventory);
			if ((pDVar5 != nullptr) ||
			    (((iVar6 = sub_6FB57CC0(), iVar6 != 7 && (iVar6 != 1)) && (iVar6 != 4))))
				goto LAB_6fae9fa3;
			puVar9 = &dword_6FBB37AC;
			do
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 5;
			} while ((int)puVar9 < (int)&dword_6FBB37FC);
			goto LAB_6fae9f8e;
		}
		iVar6 = sub_6FAFBB50((uint32_t*)(&pSMSGHANDLER_PARAMS));
		if (iVar6 == 0)
		{
			puVar9 = &dword_6FBB37AC;
			do
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 5;
			} while ((int)puVar9 < (int)&dword_6FBB37FC);
			goto LAB_6fae9f8e;
		}
		pDVar5 = sub_6FB269F0((uint32_t)pSMSGHANDLER_PARAMS, 1);
		if (pDVar5 == nullptr)
		{
			puVar9 = &dword_6FBB37AC;
			do
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 5;
			} while ((int)puVar9 < (int)&dword_6FBB37FC);
			goto LAB_6fae9f8e;
		}
		if ((gpUnit_6FBB58F0 == nullptr) ||
		    (iVar6 = sub_6FAFA260(pDVar5, gpUnit_6FBB58F0, 0, uVar10, uVar11, pData->wParam, 1, 0), iVar6 == 0))
			goto LAB_6fae9fa3;
		pDVar5 = nullptr;
	}
	sub_6FB575B0(pDVar5);
LAB_6fae9fa3:
	pData->bUseResult = 1;
	pData->lResult = 0;
	SMsgBreakHandlerChain(pData);
}

//D2Client.0x6FAE9FC0
void __cdecl sub_6FAE9FC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	D2UnitStrc* pDVar2;

	if ((((dword_6FBB58EC == 1) || (dword_6FBB58EC == 2)) || (dword_6FBB58EC == 3)) ||
	    ((dword_6FBB58EC == 4 || (dword_6FBB58EC == 9))))
	{
		iVar1 = sub_6FB23860(5);
		if (iVar1 == 0)
		{
			dword_6FBB58DC = 0;
			pDVar2 = CUNIT_GetPlayer();
			pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
			sub_6FB575B0(pDVar2);
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB5BA8 = 0;
			sub_6FAF9E60();
			dword_6FBB388C = 0;
			dword_6FBB3894 = 0;
			dword_6FBB58E0 = 0;
			dword_6FBB58E4 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = 0;
			dword_6FB79290 = 0xffffffff;
			dword_6FB79294 = 0xffffffff;
			dword_6FB79298 = 0xffffffff;
			dword_6FB7929C = 0xffffffff;
			dword_6FB792A0 = 0xffffffff;
			dword_6FB792A4 = 0xffffffff;
		}
	}
}

//D2Client.0x6FAEA080
void __cdecl sub_6FAEA080(uint32_t a1)
{
	D2InventoryStrc* pDVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;

	uVar2 = a1;
	if ((((dword_6FBB58EC == 0) || (dword_6FBB58EC == 1)) || (dword_6FBB58EC == 3)) ||
	    ((dword_6FBB58EC == 2 || (dword_6FBB58EC == 4))))
	{
		uVar6 = (uint32_t) * (uint16_t*)(a1 + 0xc);
		uVar5 = (uint32_t) * (uint16_t*)(a1 + 0xe);
		dword_6FBB388C = uVar6;
		dword_6FBB3894 = uVar5;
		pDVar3 = sub_6FB575E0();
		if ((((pDVar3 == nullptr) ||
		         (((int)uVar6 < dword_6FBB36E8 || (dword_6FBB36EC < (int)uVar6)))) ||
		        ((int)uVar5 < dword_6FBB36F0)) ||
		    (dword_6FBB36F4 < (int)uVar5))
		{
			if (dword_6FBB58EC != 0)
			{
				iVar4 = sub_6FAFBB50(&a1);
				if (iVar4 != 0)
				{
					pDVar3 = sub_6FB269F0(a1, 1);
					iVar4 = dword_6FBB36E8;
					if (pDVar3 != nullptr)
					{
						pDVar1 = pDVar3->pInventory;
						if ((((dword_6FBB36E8 <= (int)uVar6) && ((int)uVar6 <= dword_6FBB36EC)) &&
						        (dword_6FBB36F0 <= (int)uVar5)) &&
						    ((int)uVar5 <= dword_6FBB36F4))
						{
							*(uint32_t*)(uVar2 + 0x18) = 1;
							*(uint32_t*)(uVar2 + 0x1c) = 0;
							if (((dword_6FBB389C <= (int)uVar6) && ((int)uVar6 <= dword_6FBB38A0)) &&
							    ((dword_6FBB38A4 <= (int)uVar5 && ((int)uVar5 <= dword_6FBB38A8))))
							{
								sub_6FAE87C0(pDVar3, pDVar1, nullptr, uVar6, uVar5, &byte_6FBB3898,
								    CONCAT31((int32_t)((uint32_t)iVar4 >> 8), byte_6FBB5900));
								*(uint32_t*)(uVar2 + 0x18) = 1;
								*(uint32_t*)(uVar2 + 0x1c) = 0;
								dword_6FB7928C = 0;
								return;
							}
						}
					}
				}
			}
			sub_6FAE8290(uVar2);
		}
	}
}

//D2Client.0x6FAEA1C0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEA1C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t* puVar4;
	int iVar5;
	uint32_t extraout_ECX;
	uint32_t uVar6;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t extraout_ECX_03;
	int* piVar7;
	Unicode* pUVar8;
	int* piVar9;
	uint32_t uVar10;
	uint32_t* puVar11;
	uint32_t uVar12;
	uint32_t local_8c;
	uint32_t local_88;
	D2UnitStrc* local_84;
	Unicode aUStack_80[64];

	uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar10 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if ((((dword_6FBB58EC != 0) && (dword_6FBB58EC != 1)) && (dword_6FBB58EC != 3)) &&
	    ((dword_6FBB58EC != 2 && (dword_6FBB58EC != 4))))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if ((((iVar2 == 0) && ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar6)) &&
	        (((int)uVar6 <= (gnScreenWidth - dword_6FBBA748) + -0x10e &&
	            ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar10 &&
	                ((int)uVar10 <= dword_6FBBA74C + -0x40 + gnScreenHeight)))))) &&
	    ((dword_6FBB58EC == 0 ||
	        ((((dword_6FBB58EC == 1 || (dword_6FBB58EC == 3)) || (dword_6FBB58EC == 2)) || (dword_6FBB58EC == 4))))))
	{
		dword_6FBB5B98 = 1;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	pDVar3 = sub_6FB575E0();
	if (pDVar3 != nullptr)
	{
		iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
		if (iVar2 != 1)
		{
			if (((int)uVar6 <= dword_6FBB38C8) && ((int)uVar10 <= dword_6FBB38D4))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				if ((int)uVar6 < dword_6FBB389C)
				{
					return;
				}
				if (dword_6FBB38A0 < (int)uVar6)
				{
					return;
				}
				if ((int)uVar10 < dword_6FBB38A4)
				{
					return;
				}
				if (dword_6FBB38A8 < (int)uVar10)
				{
					return;
				}
				iVar2 = sub_6FB57CC0();
				if (iVar2 == 6)
				{
					return;
				}
				iVar2 = sub_6FAFBB50(&local_8c);
				if (iVar2 == 0)
				{
					return;
				}
				local_84 = sub_6FB269F0(local_8c, 1);
				if (local_84 == nullptr)
				{
					return;
				}
				pUVar8 = aUStack_80;
				uVar12 = 0x40;
				puVar11 = &local_88;
				pDVar3 = sub_6FB575E0();
				iVar2 = sub_6FAFB200(pDVar3, 1, (int*)puVar11, pUVar8, uVar12);
				if (iVar2 == 0)
				{
					return;
				}
				uVar1 = pSMSGHANDLER_PARAMS->wParam;
				pDVar3 = sub_6FB575E0();
				if (pDVar3 == nullptr)
				{
					return;
				}
				iVar2 = sub_6FAFA260(local_84, pDVar3, 1, uVar6, uVar10, uVar1, 1, 0);
				if (iVar2 == 0)
				{
					return;
				}
				sub_6FB575B0(nullptr);
				return;
			}
		LAB_6faea82f:
			sub_6FAE6E60(pSMSGHANDLER_PARAMS);
			return;
		}
		puVar4 = &dword_6FBB37AC;
		do
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 5;
		} while ((int)puVar4 < (int)&dword_6FBB37FC);
	LAB_6faea420:
		dword_6FBB58EC = 1;
		pDVar3 = CUNIT_GetPlayer();
		pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
		sub_6FB575B0(pDVar3);
		return;
	}
	iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar2 == 1)
	{
		puVar4 = &dword_6FBB37AC;
		do
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 5;
		} while ((int)puVar4 < (int)&dword_6FBB37FC);
		goto LAB_6faea420;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
	if ((((int)uVar6 < dword_6FBBA748) || (gnScreenWidth / 2 + -1 < (int)uVar6)) ||
	    (((int)uVar10 < gnScreenHeight + -0x1df + dword_6FBBA74C ||
	        (gnScreenHeight + -0x1c1 + dword_6FBBA74C < (int)uVar10))))
	{
		if ((dword_6FBB36E8 <= (int)uVar6) && ((int)uVar6 <= dword_6FBB36EC))
		{
			local_88 = gnScreenHeight + -0x6d + dword_6FBBA74C;
			if (((int)local_88 <= (int)uVar10) && ((int)uVar10 <= dword_6FBB36F4))
			{
				iVar5 = 0;
				iVar2 = 0;
				local_8c = 0;
				local_84 = (D2UnitStrc*)0xffffffff;
				if (0 < dword_6FB795B0)
				{
					piVar9 = (int*)(&dword_6FBB37AC);
					piVar7 = (int*)(byte_6FB795B8 + dword_6FB795AC * 0x10);
					do
					{
						if (*piVar9 == 1)
						{
							local_8c = 1;
							iVar2 = iVar5;
						}
						if ((((*piVar7 + dword_6FBBA748 < (int)dword_6FBB388C) &&
						         ((int)dword_6FBB388C < *piVar7 + dword_6FBBA748 + 0x2d)) &&
						        ((int)local_88 < (int)dword_6FBB3894)) &&
						    ((int)dword_6FBB3894 < dword_6FBBA74C + -0x41 + gnScreenHeight))
						{
							local_84 = (D2UnitStrc*)iVar5;
						}
						pDVar3 = local_84;
						iVar5 = iVar5 + 1;
						piVar7 = piVar7 + 1;
						piVar9 = piVar9 + 5;
					} while (iVar5 < dword_6FB795B0);
					if (local_84 != (D2UnitStrc*)0xffffffff)
					{
						if ((&dword_6FBB37A8)[(int)local_84 * 5] == 1)
						{
							sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
							if (local_8c == 1)
							{
								if (pDVar3 == (D2UnitStrc*)iVar2)
								{
									(&dword_6FBB37AC)[(int)pDVar3 * 5] = 0;
									dword_6FBB58EC = 1;
									pDVar3 = CUNIT_GetPlayer();
									if (pDVar3 != nullptr)
									{
										pDVar3 = CUNIT_GetPlayer();
										if ((pDVar3->pInventory != nullptr) &&
										    (pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory),
										        pDVar3 == nullptr))
										{
											sub_6FB575B0(nullptr);
										}
									}
									dword_6FBB5BA8 = 1;
								}
								else
								{
									(&dword_6FBB37AC)[(int)pDVar3 * 5] = 1;
									dword_6FBB5BA8 = 1;
									(&dword_6FBB37AC)[iVar2 * 5] = 0;
								}
							}
							else
							{
								(&dword_6FBB37AC)[(int)pDVar3 * 5] = 1;
								dword_6FBB5BA8 = 1;
							}
						}
						else
						{
							puVar4 = &dword_6FBB37AC;
							do
							{
								*puVar4 = 0;
								puVar4 = puVar4 + 5;
							} while ((int)puVar4 < (int)&dword_6FBB37FC);
							dword_6FBB58EC = 1;
							pDVar3 = CUNIT_GetPlayer();
							pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
							sub_6FB575B0(pDVar3);
							dword_6FBB5BA8 = 0;
						}
					}
				}
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			if ((dword_6FBB36F0 <= (int)uVar10) && ((int)uVar10 <= dword_6FBB36F4))
			{
				if (((dword_6FBB58EC == 1) || (dword_6FBB58EC == 2)) &&
				    (((((dword_6FBB389C <= (int)uVar6 && ((int)uVar6 <= dword_6FBB38A0)) &&
				           (dword_6FBB38A4 <= (int)uVar10)) &&
				          (((int)uVar10 <= dword_6FBB38A8 && (iVar2 = sub_6FAFBB50(&local_88), iVar2 != 0)))) &&
				        (pDVar3 = sub_6FB269F0(local_88, 1), pDVar3 != nullptr))))
				{
					sub_6FAE75C0(pDVar3, pDVar3->pInventory, uVar6, uVar10, pSMSGHANDLER_PARAMS->wParam, (D2UnitStrc*)(&byte_6FBB3898),
					    (D2UnitStrc*)(CONCAT31((int32_t)((uint32_t)extraout_ECX_03 >> 8), byte_6FBB5900)));
				}
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
		}
		goto LAB_6faea82f;
	}
	if (dword_6FBBA748 + 0x50 < (int)uVar6)
	{
		if (dword_6FBBA748 + 0xa0 < (int)uVar6)
		{
			if (dword_6FBBA748 + 0xf0 < (int)uVar6)
			{
				if ((((int)uVar6 <= dword_6FBBA748 + 0xf0) || (dword_6FBBA748 + 0x140 <= (int)uVar6)) ||
				    ((dword_6FB795A4 == 0 || (byte_6FBB5900 == '\x03'))))
					goto LAB_6faea598;
				sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
				uVar6 = CONCAT31((int32_t)((uint32_t)extraout_ECX_02 >> 8), 3);
			}
			else
			{
				if ((dword_6FB79592 == 0) || (byte_6FBB5900 == '\x02'))
					goto LAB_6faea598;
				sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
				uVar6 = CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 2);
			}
		}
		else
		{
			if ((dword_6FB79580 == 0) || (byte_6FBB5900 == '\x01'))
				goto LAB_6faea598;
			sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
			uVar6 = CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 1);
		}
	}
	else
	{
		if ((dword_6FB7956E == 0) || (byte_6FBB5900 == '\0'))
			goto LAB_6faea598;
		sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
		uVar6 = extraout_ECX & 0xffffff00;
	}
	dword_6FBB5904 = 0;
	sub_6FAE8F90(uVar6);
LAB_6faea598:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAEA850
void __cdecl sub_6FAEA850(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short sVar1;
	D2InventoryStrc* pInventory;
	bool bVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int* piVar5;
	uint32_t uVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	int iVar13;

	uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB5B98 = 0;
	byte_6FBB5B9C = 0;
	pDVar3 = sub_6FB575E0();
	if (pDVar3 != nullptr)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FBB5BA8 != 1)
		goto LAB_6faeab4f;
	bVar2 = false;
	if (((((int)uVar6 < dword_6FBB36E8) || (dword_6FBB36EC < (int)uVar6)) ||
	        ((int)uVar4 < dword_6FBBA74C + -0x6d + gnScreenHeight)) ||
	    ((dword_6FBB36F4 < (int)uVar4 || (iVar7 = 0, dword_6FB795B0 < 1))))
	{
	LAB_6faeaa5c:
		if (((dword_6FBB58EC == 1) || (dword_6FBB58EC == 2)) || ((dword_6FBB58EC == 4 || (dword_6FBB58EC == 3))))
		{
			pDVar3 = CUNIT_GetPlayer();
			pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
			if ((pDVar3 == nullptr) &&
			    (((iVar7 = sub_6FB57CC0(), iVar7 == 7 || (iVar7 == 1)) || (iVar7 == 4))))
			{
				pDVar3 = CUNIT_GetPlayer();
				pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
				sub_6FB575B0(pDVar3);
			}
		}
		if (0 < dword_6FB795B0)
		{
			piVar5 = (int*)(&dword_6FBB37AC);
			iVar7 = dword_6FB795B0;
			do
			{
				if (*piVar5 == 1)
				{
					*piVar5 = 0;
				}
				piVar5 = piVar5 + 5;
				iVar7 = iVar7 + -1;
			} while (iVar7 != 0);
		}
	}
	else
	{
		piVar5 = (int*)(&dword_6FBB37B2);
		do
		{
			if (((*(int*)((int)piVar5 + -10) == 1) &&
			        (*(int*)(byte_6FB795B8 + (iVar7 + dword_6FB795AC * 4) * 4) + dword_6FBBA748 <
			            (int)dword_6FBB388C)) &&
			    (((int)dword_6FBB388C <
			            *(int*)(byte_6FB795B8 + (iVar7 + dword_6FB795AC * 4) * 4) + dword_6FBBA748 + 0x2d &&
			        (((dword_6FBBA74C + -0x6d + gnScreenHeight < (int)dword_6FBB3894 &&
			              ((int)dword_6FBB3894 < dword_6FBBA74C + -0x41 + gnScreenHeight)) &&
			            (*(int*)((int)piVar5 + -6) == 1))))))
			{
				iVar13 = *piVar5;
				if (iVar13 == 9)
				{
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					dword_6FBB5BA8 = 0;
					pDVar3 = CUNIT_GetPlayer();
					pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
					if (pDVar3 == nullptr)
					{
						sub_6FB575B0(nullptr);
					}
					sub_6FAF9E60();
					dword_6FBB388C = 0;
					dword_6FBB3894 = 0;
					return;
				}
				dword_6FBB58EC = iVar13;
				D2_ASSERT(4 >= byte_6FBB5908);
				sVar1 = (short)piVar5[1];
				if ((sVar1 == 0xe) || (sVar1 == 0xc))
				{
					dword_6FB79290 = 0xffffffff;
					dword_6FB79294 = 0xffffffff;
					dword_6FB79298 = 0xffffffff;
					dword_6FB7929C = 0xffffffff;
					dword_6FB792A0 = 0xffffffff;
					dword_6FB792A4 = 0xffffffff;
					dword_6FBB58E0 = 0;
					dword_6FBB58E4 = 0;
					gpUnit_6FBB58F0 = nullptr;
					dword_6FBB58F4 = 0;
					bVar2 = false;
				}
				else
				{
					bVar2 = true;
					if (sVar1 == 0x12)
					{
						iVar13 = 1;
						uVar12 = 1;
						uVar11 = 0;
						uVar8 = 1;
						dword_6FBB5948 = 1;
						uVar9 = uVar6;
						uVar10 = uVar4;
						pDVar3 = CUNIT_GetPlayer();
						sub_6FAFA260(pDVar3, nullptr, uVar8, uVar9, uVar10, uVar11, uVar12, iVar13);
						dword_6FBB5948 = 0;
					}
					else
					{
						sub_6FB57580(*(uint32_t*)((int)piVar5 + 6), 0);
						dword_6FBB5944 = (uint32_t) * (uint16_t*)(piVar5 + 1);
						dword_6FBB5940 = iVar7;
					}
				}
			}
			iVar7 = iVar7 + 1;
			piVar5 = piVar5 + 5;
		} while (iVar7 < dword_6FB795B0);
		if (!bVar2)
			goto LAB_6faeaa5c;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	dword_6FBB5BA8 = 0;
LAB_6faeab4f:
	pDVar3 = CUNIT_GetPlayer();
	pInventory = pDVar3->pInventory;
	iVar7 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (((iVar7 == 0) && (pDVar3 = INVENTORY_GetCursorItem(pInventory), pDVar3 == nullptr)) && ((((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar6 &&
	                                                                                                 (((int)uVar6 <= (gnScreenWidth - dword_6FBBA748) + -0x10e &&
	                                                                                                     (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar4)))) &&
	                                                                                               ((int)uVar4 <= dword_6FBBA74C + -0x40 + gnScreenHeight))))
	{
		pDVar3 = CUNIT_GetPlayer();
		pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
		sub_6FB575B0(pDVar3);
		sub_6FAF9E60();
	}
}

//D2Client.0x6FAEABD0
void __cdecl sub_6FAEABD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAEABF0
void __cdecl sub_6FAEABF0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FB23860(5);
	if (iVar1 == 0)
	{
		iVar1 = sub_6FAFC0E0();
		if (iVar1 == 0)
		{
			if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
			{
				sub_6FB23260(5, 0, 0);
			}
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FAEAC40
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEAC40()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	uint32_t* puVar3;
	uint32_t* puVar4;
	uint32_t uVar5;
	uint32_t extraout_ECX;
	uint32_t uStack_4;

	if ((((dword_6FBB58EC == 1) || (dword_6FBB58EC == 2)) || (dword_6FBB58EC == 4)) || (dword_6FBB58EC == 3))
	{
		pDVar1 = CUNIT_GetPlayer();
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		if (pDVar1 == nullptr)
		{
			iVar2 = sub_6FB57CC0();
			if (((iVar2 == 7) || (iVar2 == 1)) || (iVar2 == 4))
			{
				puVar3 = &dword_6FBB37AC;
				do
				{
					*puVar3 = 0;
					puVar3 = puVar3 + 5;
				} while ((int)puVar3 < (int)&dword_6FBB37FC);
				dword_6FBB58EC = 1;
				pDVar1 = CUNIT_GetPlayer();
				pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
				sub_6FB575B0(pDVar1);
				uVar5 = dword_6FBB5944;
				iVar2 = dword_6FBB5940;
				if (((-1 < dword_6FBB5940) && (dword_6FBB5940 < dword_6FB795B0)) &&
				    ((&word_6FBB37B0)[dword_6FBB5940 * 10] != 0x276f))
				{
					puVar4 = &dword_6FBB37AC;
					do
					{
						*puVar4 = (uint32_t)(*(uint16_t*)((int)puVar4 + 10) == uVar5);
						puVar4 = puVar4 + 5;
					} while ((int)puVar4 < (int)&dword_6FBB37FC);
					dword_6FBB58EC = (&dword_6FBB37B2)[iVar2 * 5];
					sub_6FB57580((&dword_6FBB37B8)[iVar2 * 5], 0);
				}
				iVar2 = sub_6FAFBB50(&uStack_4);
				if (iVar2 != 0)
				{
					pDVar1 = sub_6FB269F0(uStack_4, 1);
					if (pDVar1 != nullptr)
					{
						uVar5 = sub_6FB57BC0();
						iVar2 = sub_6FB57BD0();
						if ((((dword_6FBB389C <= (int)uVar5) && ((int)uVar5 <= dword_6FBB38A0)) &&
						        (dword_6FBB38A4 <= iVar2)) &&
						    (iVar2 <= dword_6FBB38A8))
						{
							sub_6FAE87C0(pDVar1, pDVar1->pInventory, nullptr, uVar5, iVar2, &byte_6FBB3898,
							    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBB5900));
							dword_6FB7928C = 0;
						}
					}
				}
			}
		}
	}
}

//D2Client.0x6FAEADA0
uint32_t __cdecl sub_6FAEADA0(int a1)
{
	dword_6FBB388C = (uint32_t) * (uint16_t*)(a1 + 0xc);
	dword_6FBB3894 = (uint32_t) * (uint16_t*)(a1 + 0xe);
	if ((((dword_6FBB38C8 <= (int)dword_6FBB388C) && ((int)dword_6FBB388C < dword_6FBB38CC)) &&
	        (dword_6FBB38D0 <= (int)dword_6FBB3894)) &&
	    ((int)dword_6FBB3894 <= dword_6FBB38D4))
	{
		sub_6FAE8290(a1);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAEAE00
uint32_t __cdecl sub_6FAEAE00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	uint32_t uVar2;

	uVar2 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar1 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB388C = uVar2;
	dword_6FBB3894 = uVar1;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if ((((dword_6FBB38C8 <= (int)uVar2) && ((int)uVar2 < dword_6FBB38CC)) && (dword_6FBB38D0 <= (int)uVar1)) && ((int)uVar1 <= dword_6FBB38D4))
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		return 1;
	}
	return 0;
}

//D2Client.0x6FAEAE70
uint32_t __cdecl sub_6FAEAE70(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	uint32_t uVar2;

	uVar2 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar1 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB388C = uVar2;
	dword_6FBB3894 = uVar1;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if ((((dword_6FBB38C8 <= (int)uVar2) && ((int)uVar2 < dword_6FBB38CC)) && (dword_6FBB38D0 <= (int)uVar1)) && ((int)uVar1 <= dword_6FBB38D4))
	{
		if (((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar2) &&
		    ((int)uVar2 <= (gnScreenWidth - dword_6FBBA748) + -0x10e))
		{
			if ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar1) &&
			    (((int)uVar1 <= dword_6FBBA74C + -0x40 + gnScreenHeight && (dword_6FBB5B98 != 0))))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				sub_6FB249D0();
			}
		}
		dword_6FBB5B98 = 0;
		return 1;
	}
	dword_6FBB5B98 = 0;
	return 0;
}

//D2Client.0x6FAEAF40
uint32_t __fastcall sub_6FAEAF40(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint32_t uVar1;
	uint32_t uVar2;

	uVar2 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar1 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if (((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar2) &&
	    ((int)uVar2 <= (gnScreenWidth - dword_6FBBA748) + -0x10e))
	{
		if ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar1) &&
		    ((int)uVar1 <= dword_6FBBA74C + -0x40 + gnScreenHeight))
		{
			dword_6FBB5B98 = 1;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAEAFD0
void __cdecl sub_6FAEAFD0()
{
	int iVar1;
	char local_104[260];

	if (gpCellFile_6FBB5924 == nullptr)
	{
		SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\buyselltabs", "DATA\\GLOBAL");
		gpCellFile_6FBB5924 = CLIENT_LoadCellFile(local_104, 0);
	}
	if (gpCellFile_6FBB5928 == nullptr)
	{
		SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\miniconvert", "DATA\\GLOBAL");
		gpCellFile_6FBB5928 = CLIENT_LoadCellFile(local_104, 0);
	}
	if (gpCellFile_6FBB5938 == nullptr)
	{
		iVar1 = FOG_IsExpansion();
		if (iVar1 != 0)
		{
			iVar1 = sub_6FAAC080();
			if (iVar1 != 0)
			{
				SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\invchar6tab", "DATA\\GLOBAL");
				gpCellFile_6FBB5938 = CLIENT_LoadCellFile(local_104, 0);
			}
		}
	}
}

//D2Client.0x6FAEB090
void __cdecl sub_6FAEB090()
{
	int iVar1;

	if (gpCellFile_6FBB3890 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB3890);
		gpCellFile_6FBB3890 = nullptr;
	}
	if (gpCellFile_6FBB5924 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5924);
		gpCellFile_6FBB5924 = nullptr;
	}
	if (gpCellFile_6FBB5928 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5928);
		gpCellFile_6FBB5928 = nullptr;
	}
	iVar1 = sub_6FAAC080();
	if ((iVar1 != 0) && (gpCellFile_6FBB5938 != nullptr))
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5938);
		gpCellFile_6FBB5938 = nullptr;
	}
}

//D2Client.0x6FAEB100
void __fastcall sub_6FAEB100(int a1)
{
	char acStack_104[260];

	if ((dword_6FBB5B18 != 0) || (dword_6FBB5B1C != 0))
	{
		sub_6FB55820(3, nullptr, 0.0, 0.0, 0);
	}
	dword_6FBB5B18 = 0;
	dword_6FBB5B1C = 0;
	dword_6FBB5B38 = 0;
	if (a1 == 0)
	{
		dword_6FBB58EC = 10;
		sub_6FAB5760(0);
	}
	else
	{
		byte_6FBB3870 = 0;
		dword_6FBB58EC = 0xb;
		sub_6FAB5760(3);
		if (gpCellFile_6FBB3890 == nullptr)
		{
			SStrPrintf(acStack_104, 0x104, "%s\\ui\\panel\\trade", "DATA\\GLOBAL");
			gpCellFile_6FBB3890 = CLIENT_LoadCellFile(acStack_104, 0);
		}
	}
	dword_6FBB5BA8 = 0;
	dword_6FBB5B20 = 0;
	dword_6FBB5B24 = 0;
	dword_6FBB5B28 = 0;
	dword_6FBB5B2C = 0;
}

//D2Client.0x6FAEB1D0
void __cdecl sub_6FAEB1D0(int a1)
{
	if (dword_6FBB58EC == 0xb)
	{
		dword_6FBB388C = (uint32_t) * (uint16_t*)(a1 + 0xc);
		dword_6FBB3894 = (uint32_t) * (uint16_t*)(a1 + 0xe);
		if ((((dword_6FBB38C8 <= (int)dword_6FBB388C) && ((int)dword_6FBB388C < dword_6FBB38CC)) &&
		        (dword_6FBB38D0 <= (int)dword_6FBB3894)) &&
		    ((int)dword_6FBB3894 <= dword_6FBB38D4))
		{
			sub_6FAE8290(a1);
			return;
		}
		if (((dword_6FBB383C < (int)dword_6FBB388C) && ((int)dword_6FBB388C < dword_6FBB3840)) &&
		    ((dword_6FBB3844 <= (int)dword_6FBB3894 && ((int)dword_6FBB3894 <= dword_6FBB3848))))
		{
			sub_6FAE8290(a1);
			return;
		}
		if (((dword_6FBB37FC < (int)dword_6FBB388C) && ((int)dword_6FBB388C < dword_6FBB3800)) &&
		    ((dword_6FBB3804 <= (int)dword_6FBB3894 && ((int)dword_6FBB3894 <= dword_6FBB3808))))
		{
			sub_6FAE8290(a1);
			return;
		}
		dword_6FB79290 = 0xffffffff;
		dword_6FB79294 = 0xffffffff;
		dword_6FB79298 = 0xffffffff;
		dword_6FB7929C = 0xffffffff;
		dword_6FB792A0 = 0xffffffff;
		dword_6FB792A4 = 0xffffffff;
		dword_6FBB58E0 = 0;
		dword_6FBB58E4 = 0;
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58F4 = 0;
		D2Win_10129_DrawFramedText(nullptr, -1, -1, 0, 0);
	}
}

//D2Client.0x6FAEB2D0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEB2D0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	uint32_t uVar3;
	uint32_t uVar4;

	if (dword_6FBB58EC != 0xb)
	{
		return;
	}
	uVar3 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB388C = uVar3;
	dword_6FBB3894 = uVar4;
	iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if ((((iVar1 == 0) && ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar3)) &&
	        ((int)uVar3 <= (gnScreenWidth - dword_6FBBA748) + -0x10e)) &&
	    ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar4 &&
	        ((int)uVar4 <= dword_6FBBA74C + -0x40 + gnScreenHeight))))
	{
		dword_6FBB5B98 = 1;
	LAB_6faeb4b0:
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar1 == 1)
	{
		return;
	}
	if (((dword_6FBB38C8 <= (int)uVar3) && ((int)uVar3 < dword_6FBB38CC)) &&
	    ((dword_6FBB38D0 <= (int)uVar4 && ((int)uVar4 <= dword_6FBB38D4))))
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		return;
	}
	if ((((dword_6FBB383C < (int)uVar3) && ((int)uVar3 < dword_6FBB3840)) && (dword_6FBB3844 <= (int)uVar4)) && ((int)uVar4 <= dword_6FBB3848))
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		return;
	}
	pDVar2 = CUNIT_GetPlayer();
	pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	if (pDVar2 == nullptr)
	{
		if ((((int)uVar3 <= dword_6FBBA748 + 0xdf) || (dword_6FBBA748 + 0xff <= (int)uVar3)) ||
		    (((int)uVar4 <= dword_6FBBA74C + -0x60 + gnScreenHeight ||
		        (dword_6FBBA74C + -0x40 + gnScreenHeight <= (int)uVar4))))
		{
			if ((((int)uVar3 <= dword_6FBBA748 + 0x113) || (dword_6FBBA748 + 0x133 <= (int)uVar3)) ||
			    (((int)uVar4 <= dword_6FBBA74C + -0x60 + gnScreenHeight ||
			        (dword_6FBBA74C + -0x40 + gnScreenHeight <= (int)uVar4))))
			{
				pDVar2 = CUNIT_GetPlayer();
				pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
				if ((((pDVar2 == nullptr) && (dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar4)) && ((int)uVar4 <= dword_6FBBA74C + -0x45 + gnScreenHeight)) &&
				    (((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar3 &&
				        ((int)uVar3 <= (gnScreenWidth - dword_6FBBA748) + -0xd9))))
				{
					dword_6FBB5B38 = 1;
					dword_6FBB5B28 = 0;
					dword_6FBB5B20 = 0;
					dword_6FBB5BA8 = 0;
					dword_6FBB5B24 = 0;
					sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
				}
				else
				{
					iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
					if (iVar1 == 1)
					{
						dword_6FBB5B20 = 0;
						dword_6FBB5BA8 = 0;
						dword_6FBB5B24 = 0;
						dword_6FBB5B28 = 0;
						return;
					}
				}
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				dword_6FBB5B2C = 0;
				dword_6FBB5B28 = 0;
				return;
			}
			dword_6FBB5B2C = 1;
			dword_6FBB5B24 = 1;
			dword_6FBB5BA8 = 1;
			goto LAB_6faeb4b0;
		}
		dword_6FBB5B28 = 1;
		if (dword_6FBB5B20 == 1)
		{
			dword_6FBB5B20 = 0;
			sub_6FB1FF00(1);
		}
		else
		{
			dword_6FBB5B20 = 1;
			dword_6FBB5BA8 = 1;
			sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		}
	}
	else
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B20 = 0;
		dword_6FBB5BA8 = 0;
		dword_6FBB5B24 = 0;
		sub_6FB1FF00(extraout_ECX);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAEB5B0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEB5B0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	int iVar2;
	int extraout_ECX;
	int extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t uVar3;
	uint32_t uVar4;

	if (dword_6FBB58EC != 0xb)
	{
		dword_6FBB5BA8 = 0;
		return;
	}
	uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar3 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB5B98 = 0;
	byte_6FBB5B9C = 0;
	dword_6FBB388C = uVar4;
	dword_6FBB3894 = uVar3;
	pDVar1 = CUNIT_GetPlayer();
	pInventory = pDVar1->pInventory;
	iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (((((iVar2 == 0) && (pDVar1 = INVENTORY_GetCursorItem(pInventory), pDVar1 == nullptr)) && ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar4)) &&
	        (((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0x10e &&
	            (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar3)))) &&
	    ((int)uVar3 <= dword_6FBBA74C + -0x40 + gnScreenHeight))
	{
		sub_6FB1F6A0(dword_6FBBA74C);
		return;
	}
	if (((dword_6FBB383C < (int)uVar4) && ((int)uVar4 < dword_6FBB3840)) &&
	    ((dword_6FBB3844 <= (int)uVar3 && ((int)uVar3 <= dword_6FBB3848))))
	{
	LAB_6faeb836:
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		if (dword_6FBB5B20 != 0)
		{
			sub_6FB1FF00(extraout_ECX_01);
		}
		dword_6FBB5BA8 = 0;
		dword_6FBB5B24 = 0;
		dword_6FBB5B20 = 0;
		return;
	}
	if ((((dword_6FBBA748 + 0xdf < (int)uVar4) && ((int)uVar4 < dword_6FBBA748 + 0xff)) &&
	        (dword_6FBBA74C + -0x60 + gnScreenHeight < (int)uVar3)) &&
	    ((int)uVar3 < dword_6FBBA74C + -0x40 + gnScreenHeight))
	{
		if ((dword_6FBB5B20 != 0) && (dword_6FBB5B28 != 0))
		{
			sub_6FB1FED0(0);
		}
		dword_6FBB5B28 = 0;
	}
	else
	{
		if ((((int)uVar4 <= dword_6FBBA748 + 0x113) || (dword_6FBBA748 + 0x133 <= (int)uVar4)) ||
		    (((int)uVar3 <= dword_6FBBA74C + -0x60 + gnScreenHeight ||
		        (dword_6FBBA74C + -0x40 + gnScreenHeight <= (int)uVar3))))
		{
			iVar2 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
			if (iVar2 == 1)
			{
				dword_6FBB5B28 = 0;
				dword_6FBB5B20 = 0;
				dword_6FBB5BA8 = 0;
				dword_6FBB5B24 = 0;
				return;
			}
			pDVar1 = CUNIT_GetPlayer();
			pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
			iVar2 = extraout_ECX;
			if (((pDVar1 == nullptr) &&
			        (iVar2 = gnScreenHeight, dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar3)) &&
			    ((int)uVar3 <= dword_6FBBA74C + -0x45 + gnScreenHeight))
			{
				iVar2 = (gnScreenWidth - dword_6FBBA748) + -0xed;
				if (((iVar2 <= (int)uVar4) && ((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0xd9)) &&
				    (dword_6FBB5B34 == 0))
				{
					sub_6FB23B40(2);
					iVar2 = extraout_ECX_00;
				}
			}
			if (dword_6FBB5BA8 != 0)
			{
				dword_6FBB5BA8 = 0;
				if (dword_6FBB5B28 == 0)
				{
					if ((dword_6FBB5B2C != 0) && (dword_6FBB5B24 != 0))
					{
						dword_6FBB5B24 = 0;
					}
				}
				else if (dword_6FBB5B20 == 1)
				{
					dword_6FBB5B20 = 0;
					sub_6FB1FF00(iVar2);
				}
				dword_6FBB5B28 = 0;
				dword_6FBB5B2C = 0;
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			goto LAB_6faeb836;
		}
		if ((dword_6FBB5B24 != 0) && (dword_6FBB5B2C != 0))
		{
			sub_6FB1F6A0(dword_6FBBA74C);
			dword_6FBB5B24 = 0;
		}
		dword_6FBB5B2C = 0;
	}
	dword_6FBB5BA8 = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAEB870
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEB870(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	uint32_t extraout_ECX;

	if (dword_6FBB58EC == 0xb)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		iVar1 = sub_6FB23860(5);
		if (iVar1 == 0)
		{
			sub_6FB1F6A0(extraout_ECX);
		}
	}
}

//D2Client.0x6FAEB8B0
void __fastcall sub_6FAEB8B0(int a1, int a2)
{
	int iVar1;

	if ((dword_6FBB5B18 == 0) && (dword_6FBB5B1C == 0))
	{
	LAB_6faeb8d5:
		if (a1 == 0)
			goto LAB_6faeb8d9;
	}
	else
	{
		if ((a1 == 0) || (a2 == 0))
		{
			iVar1 = 3;
			goto LAB_6faeb8ed;
		}
		if (dword_6FBB5B18 == 0)
			goto LAB_6faeb8d5;
	LAB_6faeb8d9:
		if (a2 == 0)
		{
			dword_6FBB5B18 = a1;
			dword_6FBB5B1C = a2;
			return;
		}
		if (dword_6FBB5B1C != 0)
		{
			dword_6FBB5B18 = a1;
			dword_6FBB5B1C = a2;
			return;
		}
	}
	iVar1 = 1;
LAB_6faeb8ed:
	sub_6FB55820(iVar1, nullptr, 0.0, 0.0, 0);
	dword_6FBB5B18 = a1;
	dword_6FBB5B1C = a2;
}

//D2Client.0x6FAEB910
uint32_t __cdecl sub_6FAEB910()
{
	if (((dword_6FBB58EC != 1) && (dword_6FBB58EC != 2)) && (dword_6FBB58EC != 3))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FAEB930
bool __cdecl sub_6FAEB930()
{
	return dword_6FBB58EC == 4;
}

//D2Client.0x6FAEB940
uint32_t __cdecl sub_6FAEB940()
{
	return dword_6FBB5948;
}

//D2Client.0x6FAEB950
void __cdecl sub_6FAEB950()
{
	dword_6FBB5B34 = 0;
	if (dword_6FBB58EC == 0xd)
	{
		dword_6FBB58EC = 0xc;
	}
}

//D2Client.0x6FAEB970
void __cdecl sub_6FAEB970()
{
	dword_6FBB5B34 = 1;
	if (dword_6FBB58EC == 0xd)
	{
		dword_6FBB58EC = 0xc;
	}
	sub_6FB23260(5, 1, 0);
}

//D2Client.0x6FAEB9A0
void __fastcall sub_6FAEB9A0(int a1)
{
	dword_6FB79288 = a1;
	if (a1 == 0)
	{
		dword_6FBB58E0 = 0;
		dword_6FB79290 = 0xffffffff;
		dword_6FB79294 = 0xffffffff;
		dword_6FB79298 = 0xffffffff;
		dword_6FB7929C = 0xffffffff;
		dword_6FB792A0 = 0xffffffff;
		dword_6FB792A4 = 0xffffffff;
		dword_6FBB58E4 = 0;
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58F4 = 0;
	}
}

//D2Client.0x6FAEB9F0
void __cdecl sub_6FAEB9F0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;

	if ((dword_6FBB58EC == 0xc) || (dword_6FBB58EC == 0xd))
	{
		uVar6 = (uint32_t) * (uint16_t*)(a1 + 0xc);
		uVar7 = (uint32_t) * (uint16_t*)(a1 + 0xe);
		dword_6FBB388C = uVar6;
		dword_6FBB3894 = uVar7;
		if (((int)uVar6 < dword_6FBB38C8) ||
		    (((dword_6FBB38CC <= (int)uVar6 || ((int)uVar7 < dword_6FBB38D0)) || (dword_6FBB38D4 < (int)uVar7))))
		{
			iVar5 = sub_6FAAC080();
			iVar1 = dword_6FBB3730;
			iVar2 = dword_6FBB3734;
			iVar3 = dword_6FBB3738;
			iVar4 = dword_6FBB372C;
			if (iVar5 != 0)
			{
				iVar1 = dword_6FBB3768;
				iVar2 = dword_6FBB376C;
				iVar3 = dword_6FBB3770;
				iVar4 = dword_6FBB3764;
			}
			if ((((int)uVar6 <= iVar4) || (iVar1 < (int)uVar6)) ||
			    (((int)uVar7 < iVar2 || (iVar3 < (int)uVar7))))
			{
				dword_6FBB58E0 = 0;
				dword_6FBB58E4 = 0;
				gpUnit_6FBB58F0 = nullptr;
				dword_6FBB58F4 = 0;
				D2Win_10129_DrawFramedText(nullptr, -1, -1, 0, 0);
				return;
			}
		}
		sub_6FAE8290(a1);
	}
}

//D2Client.0x6FAEBAD0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEBAD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	bool bVar3;
	uint32_t extraout_var;
	int iVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	D2GameResolutionMode DVar8;
	uint32_t uVar9;
	uint32_t uVar10;

	if ((dword_6FBB58EC != 0xc) && (dword_6FBB58EC != 0xd))
	{
		return;
	}
	uVar10 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar9 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB388C = uVar10;
	dword_6FBB3894 = uVar9;
	bVar3 = sub_6FAFE9E0();
	if ((((D2C_ZEXT(bVar3) == 0) || (iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS), iVar4 == 0)) &&
	        ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar10)) &&
	    ((((int)uVar10 <= (gnScreenWidth - dword_6FBBA748) + -0x10e &&
	          (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar9)) &&
	        ((int)uVar9 <= dword_6FBBA74C + -0x40 + gnScreenHeight))))
	{
		dword_6FBB5B98 = 1;
		goto LAB_6faebca6;
	}
	iVar4 = sub_6FAAC080();
	if (iVar4 == 0)
	{
		if (dword_6FBBA74C + -0x103 + gnScreenHeight <= (int)uVar9)
		{
			iVar4 = dword_6FBBA74C + -0xf2;
			goto joined_r0x6faebbcb;
		}
	}
	else if (dword_6FBBA74C + -0x1c7 + gnScreenHeight <= (int)uVar9)
	{
		iVar4 = dword_6FBBA74C + -0x1b6;
	joined_r0x6faebbcb:
		if ((((int)uVar9 <= iVar4 + gnScreenHeight) && (dword_6FBBA748 + 0x49 <= (int)uVar10)) &&
		    ((int)uVar10 <= dword_6FBBA748 + 0x96))
		{
			dword_6FBB5B3C = 1;
			goto LAB_6faebca6;
		}
	}
	iVar4 = sub_6FAAC080();
	if (iVar4 == 0)
	{
		iVar4 = dword_6FBBA748 + 0x113;
	}
	else
	{
		iVar4 = dword_6FBBA748 + 0x110;
	}
	if (iVar4 < (int)uVar10)
	{
		iVar4 = sub_6FAAC080();
		if (iVar4 == 0)
		{
			iVar4 = dword_6FBBA748 + 0x113;
		}
		else
		{
			iVar4 = dword_6FBBA748 + 0x110;
		}
		if ((int)uVar10 < iVar4 + 0x28)
		{
			iVar4 = sub_6FAAC080();
			if (iVar4 == 0)
			{
				iVar4 = dword_6FBBA74C + -0x41;
			}
			else
			{
				iVar4 = dword_6FBBA74C + -0x40;
			}
			if (iVar4 + gnScreenHeight + -0x23 < (int)uVar9)
			{
				iVar4 = sub_6FAAC080();
				if (iVar4 == 0)
				{
					iVar4 = dword_6FBBA74C + -0x41;
				}
				else
				{
					iVar4 = dword_6FBBA74C + -0x40;
				}
				if ((int)uVar9 < iVar4 + gnScreenHeight + 5)
				{
					dword_6FBB5B44 = 1;
					dword_6FBB5B40 = 1;
					dword_6FBB5BA8 = 1;
				LAB_6faebca6:
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
		}
	}
	iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar4 == 1)
	{
		dword_6FBB5B3C = 0;
		dword_6FBB5B20 = 0;
		dword_6FBB5BA8 = 0;
		dword_6FBB5B40 = 0;
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	if ((((dword_6FBB38C8 <= (int)uVar10) && ((int)uVar10 < dword_6FBB38CC)) &&
	        (dword_6FBB38D0 <= (int)uVar9)) &&
	    ((int)uVar9 <= dword_6FBB38D4))
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		goto LAB_6faec016;
	}
	iVar5 = sub_6FAAC080();
	iVar4 = dword_6FBB3730;
	iVar1 = dword_6FBB3734;
	iVar2 = dword_6FBB3738;
	iVar7 = dword_6FBB372C;
	if (iVar5 != 0)
	{
		iVar4 = dword_6FBB3768;
		iVar1 = dword_6FBB376C;
		iVar2 = dword_6FBB3770;
		iVar7 = dword_6FBB3764;
	}
	if (((iVar7 < (int)uVar10) && ((int)uVar10 <= iVar4)) &&
	    ((iVar1 <= (int)uVar9 && ((int)uVar9 <= iVar2))))
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		goto LAB_6faec016;
	}
	pDVar6 = CUNIT_GetPlayer();
	pDVar6 = INVENTORY_GetCursorItem(pDVar6->pInventory);
	if ((((pDVar6 == nullptr) && (dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar9)) &&
	        ((int)uVar9 <= dword_6FBBA74C + -0x45 + gnScreenHeight)) &&
	    (((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar10 &&
	        ((int)uVar10 <= (gnScreenWidth - dword_6FBBA748) + -0xd9))))
	{
		dword_6FBB5B38 = 1;
		dword_6FBB5B28 = 0;
		dword_6FBB5B20 = 0;
		dword_6FBB5BA8 = 0;
		dword_6FBB5B40 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		goto LAB_6faec016;
	}
	iVar4 = sub_6FAAC080();
	if (iVar4 == 0)
	{
		if (dword_6FBBA74C + -0x103 + gnScreenHeight <= (int)uVar9)
		{
			iVar4 = dword_6FBBA74C + -0xf2;
			goto joined_r0x6faebee0;
		}
	}
	else if (dword_6FBBA74C + -0x1c7 + gnScreenHeight <= (int)uVar9)
	{
		iVar4 = dword_6FBBA74C + -0x1b6;
	joined_r0x6faebee0:
		if ((((int)uVar9 <= iVar4 + gnScreenHeight) && (dword_6FBBA748 + 0x49 <= (int)uVar10)) &&
		    ((int)uVar10 <= dword_6FBBA748 + 0x96))
		{
			dword_6FBB5B3C = 1;
			dword_6FBB5B28 = 0;
			dword_6FBB5B20 = 0;
			dword_6FBB5BA8 = 0;
			dword_6FBB5B40 = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB5B44 = 0;
			return;
		}
	}
	iVar7 = sub_6FAAC080();
	iVar4 = dword_6FBB3798;
	iVar1 = dword_6FBB37A0;
	iVar2 = dword_6FBB3794;
	if (iVar7 != 0)
	{
		iVar4 = dword_6FBB3754;
		iVar1 = dword_6FBB375C;
		iVar2 = dword_6FBB3750;
	}
	if (((iVar2 <= (int)uVar10) && ((int)uVar10 < iVar4)) && ((int)uVar9 <= iVar1))
	{
		dword_6FBB5B3C = 0;
		dword_6FBB5B28 = 0;
		dword_6FBB5B20 = 0;
		dword_6FBB5BA8 = 0;
		dword_6FBB5B40 = 0;
		dword_6FBB5B44 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	DVar8 = D2GFX_GetResolutionMode();
	if (DVar8 != NUM_GAME_RESOLUTIONS)
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	iVar4 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar4 != 0)
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	if (gnScreenHeight + -0x30 < (int)uVar9)
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	iVar4 = sub_6FAB5750();
	if ((iVar4 == 1) && ((int)uVar10 < gnScreenWidth / 2))
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	iVar4 = sub_6FB57CC0();
	if (iVar4 == 6)
	{
		sub_6FB23A40();
	}
	iVar4 = sub_6FAB5750();
	if (((iVar4 == 3) && (dword_6FBB58EC == 0)) && ((int)uVar10 < gnScreenWidth / 2))
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	dword_6FBB58E0 = 0;
	dword_6FBB58E4 = 0;
LAB_6faec016:
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	dword_6FBB5B44 = 0;
	dword_6FBB5B28 = 0;
}

//D2Client.0x6FAEC030
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEC030(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pInventory;
	bool bVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_var;
	int iVar3;
	uint32_t extraout_var_00;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;

	if ((dword_6FBB58EC != 0xc) && (dword_6FBB58EC != 0xd))
	{
		dword_6FBB5BA8 = 0;
		return;
	}
	uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB5B98 = 0;
	byte_6FBB5B9C = 0;
	dword_6FBB388C = uVar5;
	dword_6FBB3894 = uVar4;
	pDVar2 = CUNIT_GetPlayer();
	pInventory = pDVar2->pInventory;
	bVar1 = sub_6FAFE9E0();
	if (((((D2C_ZEXT(bVar1) == 0) || (iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS), iVar3 == 0)) &&
	         (pDVar2 = INVENTORY_GetCursorItem(pInventory), pDVar2 == nullptr)) &&
	        (((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar5 &&
	            ((int)uVar5 <= (gnScreenWidth - dword_6FBBA748) + -0x10e)))) &&
	    ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar4 &&
	        ((int)uVar4 <= dword_6FBBA74C + -0x40 + gnScreenHeight))))
	{
		sub_6FB23260(0x19, 1, 0);
		return;
	}
	iVar3 = sub_6FAAC080();
	if (iVar3 == 0)
	{
		iVar3 = dword_6FBBA748 + 0x113;
	}
	else
	{
		iVar3 = dword_6FBBA748 + 0x110;
	}
	if (iVar3 < (int)uVar5)
	{
		iVar3 = sub_6FAAC080();
		if (iVar3 == 0)
		{
			iVar3 = dword_6FBBA748 + 0x113;
		}
		else
		{
			iVar3 = dword_6FBBA748 + 0x110;
		}
		if ((int)uVar5 < iVar3 + 0x28)
		{
			iVar3 = sub_6FAAC080();
			if (iVar3 == 0)
			{
				iVar3 = dword_6FBBA74C + -0x41;
			}
			else
			{
				iVar3 = dword_6FBBA74C + -0x40;
			}
			if (iVar3 + gnScreenHeight + -0x23 < (int)uVar4)
			{
				iVar3 = sub_6FAAC080();
				if (iVar3 == 0)
				{
					iVar3 = dword_6FBBA74C + -0x41;
				}
				else
				{
					iVar3 = dword_6FBBA74C + -0x40;
				}
				if ((int)uVar4 < iVar3 + gnScreenHeight + 5)
				{
					if (dword_6FBB5B40 != 0)
					{
						dword_6FBB5B40 = 0;
						sub_6FB23260(0x19, 1, 0);
						sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x12, 0, 0);
					}
					dword_6FBB5B44 = 0;
					dword_6FBB5BA8 = 0;
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
		}
	}
	dword_6FBB5B40 = 0;
	dword_6FBB5B44 = 0;
	bVar1 = sub_6FAFE9E0();
	if (D2C_ZEXT(bVar1) == 0)
	{
		pDVar2 = CUNIT_GetPlayer();
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		if (((pDVar2 == nullptr) && (dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar4)) &&
		    (((int)uVar4 <= dword_6FBBA74C + -0x45 + gnScreenHeight &&
		        ((((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar5 &&
		              ((int)uVar5 <= (gnScreenWidth - dword_6FBBA748) + -0xd9)) &&
		            (dword_6FBB5B34 == 0))))))
		{
			sub_6FB23B40(3);
		}
	}
	iVar3 = sub_6FAAC080();
	if (iVar3 == 0)
	{
		if ((int)uVar4 < dword_6FBBA74C + -0x103 + gnScreenHeight)
			goto LAB_6faec2f8;
		iVar3 = dword_6FBBA74C + -0xf2;
	}
	else
	{
		if ((int)uVar4 < dword_6FBBA74C + -0x1c7 + gnScreenHeight)
			goto LAB_6faec2f8;
		iVar3 = dword_6FBBA74C + -0x1b6;
	}
	if ((((int)uVar4 <= iVar3 + gnScreenHeight) && (dword_6FBBA748 + 0x49 <= (int)uVar5)) &&
	    (((int)uVar5 <= dword_6FBBA748 + 0x96 && (dword_6FBB5B34 == 0))))
	{
		sub_6FB23B40(4);
	}
LAB_6faec2f8:
	iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar3 == 1)
	{
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		return;
	}
	dword_6FBB5B3C = 0;
	dword_6FBB5B38 = 0;
	if (dword_6FBB5BA8 != 0)
	{
		dword_6FBB5BA8 = 0;
		if (dword_6FBB5B28 == 0)
		{
			if ((dword_6FBB5B44 != 0) && (dword_6FBB5B40 != 0))
			{
				dword_6FBB5B40 = 0;
			}
		}
		else if (dword_6FBB5B20 == 1)
		{
			dword_6FBB5B20 = 0;
		}
		dword_6FBB5B28 = 0;
		dword_6FBB5B44 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	dword_6FBB5BA8 = 0;
	dword_6FBB5B40 = 0;
	dword_6FBB5B20 = 0;
}

//D2Client.0x6FAEC3B0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEC3B0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	uint32_t extraout_ECX;

	if (dword_6FBB58EC == 0xc)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		iVar1 = sub_6FB23860(5);
		if (iVar1 == 0)
		{
			sub_6FB23260(0x19, 1, 0);
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x12, 0, 0);
			dword_6FBB58E0 = 0;
			dword_6FB79290 = 0xffffffff;
			dword_6FB79294 = 0xffffffff;
			dword_6FB79298 = 0xffffffff;
			dword_6FB7929C = 0xffffffff;
			dword_6FB792A0 = 0xffffffff;
			dword_6FB792A4 = 0xffffffff;
			dword_6FBB58E4 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = 0;
		}
	}
}

//D2Client.0x6FAEC440
void __cdecl sub_6FAEC440(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		sub_6FAD3CB0();
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAEC470
void __cdecl sub_6FAEC470(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pInventory;
	int iVar1;
	D2UnitStrc* pDVar2;

	iVar1 = sub_6FAAC080();
	if (iVar1 != 0)
	{
		if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
		{
			iVar1 = sub_6FB23860(5);
			if (iVar1 == 0)
			{
				iVar1 = FOG_IsExpansion();
				if (iVar1 != 0)
				{
					iVar1 = sub_6FAAC080();
					if (iVar1 != 0)
					{
						sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
						CLIENT_SendSimpleMessage(0x60);
						pDVar2 = CUNIT_GetPlayer();
						pInventory = pDVar2->pInventory;
						pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
						if (pDVar2 != nullptr)
						{
							sub_6FB2FB30(pDVar2);
						}
						pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
						if (pDVar2 != nullptr)
						{
							sub_6FB2FB30(pDVar2);
						}
					}
				}
			}
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAEC510
void __cdecl sub_6FAEC510()
{
	int iVar1;

	iVar1 = sub_6FB23260(0x19, 0, 0);
	if (iVar1 != 0)
	{
		dword_6FBB5950 = 0;
		sub_6FB297A0((uint8_t*)(sub_6FAEC560));
		dword_6FBB58EC = 0xc;
		sub_6FAABF30();
		dword_6FBB5B38 = 0;
		dword_6FBB5B3C = 0;
		dword_6FBB5B40 = 0;
		dword_6FBB5B44 = 0;
	}
}

//D2Client.0x6FAEC560
void __fastcall sub_6FAEC560(D2UnitStrc* pUnit2)
{
	uint8_t bVar1;
	uint8_t bVar2;
	D2ActiveRoomStrc* pRoom;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom_00;
	int iVar3;

	if ((pUnit2 != nullptr) && (pUnit2->dwClassId == 0x10b))
	{
		pRoom = UNITS_GetRoom(pUnit2);
		if (pRoom != nullptr)
		{
			pUnit = CUNIT_GetPlayer();
			pRoom_00 = UNITS_GetRoom(pUnit);
			if (pRoom_00 != nullptr)
			{
				iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom_00);
				bVar1 = DRLG_GetActNoFromLevelId(iVar3);
				iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom);
				bVar2 = DRLG_GetActNoFromLevelId(iVar3);
				if (bVar1 == bVar2)
				{
					dword_6FB792A8 = pUnit2->dwUnitId;
				}
			}
		}
	}
}

//D2Client.0x6FAEC5C0
void __cdecl sub_6FAEC5C0()
{
	int iVar1;
	char local_104[260];

	byte_6FBB3790 = 0;
	if (gpCellFile_6FBB592C == nullptr)
	{
		SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\bank", "DATA\\GLOBAL");
		gpCellFile_6FBB592C = CLIENT_LoadCellFile(local_104, 0);
		iVar1 = FOG_IsExpansion();
		if (iVar1 != 0)
		{
			SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\TradeStash", "DATA\\GLOBAL");
			gpCellFile_6FBB593C = CLIENT_LoadCellFile(local_104, 0);
		}
	}
}

//D2Client.0x6FAEC650
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEC650()
{
	uint32_t extraout_ECX;

	if ((dword_6FBB58EC == 0xc) || (dword_6FBB58EC == 0xd))
	{
		dword_6FBB58EC = 0;
		sub_6FB23260(0x19, 1, 0);
		sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x12, 0, 0);
	}
	if (gpCellFile_6FBB592C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB592C);
		gpCellFile_6FBB592C = nullptr;
	}
	if (gpCellFile_6FBB593C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB593C);
		gpCellFile_6FBB593C = nullptr;
	}
}

//D2Client.0x6FAEC6C0
void __cdecl sub_6FAEC6C0()
{
	if ((dword_6FBB58EC == 0xc) || (dword_6FBB58EC == 0xd))
	{
		dword_6FBB58EC = 0;
		sub_6FB23260(0x19, 1, 0);
	}
	if (gpCellFile_6FBB592C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB592C);
		gpCellFile_6FBB592C = nullptr;
	}
	if (gpCellFile_6FBB593C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB593C);
		gpCellFile_6FBB593C = nullptr;
	}
}

//D2Client.0x6FAEC720
void __cdecl sub_6FAEC720(int a1)
{
	if (dword_6FBB58EC == 0xe)
	{
		dword_6FBB388C = (uint32_t) * (uint16_t*)(a1 + 0xc);
		dword_6FBB3894 = (uint32_t) * (uint16_t*)(a1 + 0xe);
		if (((((dword_6FBB38C8 <= (int)dword_6FBB388C) && ((int)dword_6FBB388C < dword_6FBB38CC)) &&
		         (dword_6FBB38D0 <= (int)dword_6FBB3894)) &&
		        ((int)dword_6FBB3894 <= dword_6FBB38D4)) ||
		    (((dword_6FBB38B4 <= (int)dword_6FBB388C && ((int)dword_6FBB388C < dword_6FBB38B8)) &&
		        ((dword_6FBB38BC <= (int)dword_6FBB3894 && ((int)dword_6FBB3894 <= dword_6FBB38C0))))))
		{
			sub_6FAE8290(a1);
			return;
		}
		dword_6FBB58E0 = 0;
		dword_6FBB58E4 = 0;
		gpUnit_6FBB58F0 = nullptr;
		dword_6FBB58F4 = 0;
		D2Win_10129_DrawFramedText(nullptr, -1, -1, 0, 0);
	}
}

//D2Client.0x6FAEC7C0
void __cdecl sub_6FAEC7C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2GameResolutionMode DVar3;
	uint32_t uVar4;
	uint32_t uVar5;

	if (dword_6FBB58EC != 0xe)
	{
		return;
	}
	uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB388C = uVar4;
	dword_6FBB3894 = uVar5;
	iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if ((((iVar1 == 0) && ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar4)) &&
	        ((int)uVar4 <= (gnScreenWidth - dword_6FBBA748) + -0x10e)) &&
	    ((dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar5 &&
	        ((int)uVar5 <= dword_6FBBA74C + -0x40 + gnScreenHeight))))
	{
		dword_6FBB5B98 = 1;
	LAB_6faec890:
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	if (((dword_6FBBA748 + 0x113 < (int)uVar4) && ((int)uVar4 < dword_6FBBA748 + 0x13b)) &&
	    ((dword_6FBBA74C + -100 + gnScreenHeight < (int)uVar5 &&
	        ((int)uVar5 < dword_6FBBA74C + -0x3c + gnScreenHeight))))
	{
		dword_6FBB5B4C = 1;
		dword_6FBB5B48 = 1;
		dword_6FBB5B54 = 0;
		dword_6FBB5B50 = 0;
		dword_6FBB5BA8 = 1;
		goto LAB_6faec890;
	}
	if ((((dword_6FBBA748 + 0x90 < (int)uVar4) && ((int)uVar4 < dword_6FBBA748 + 0xb8)) &&
	        (dword_6FBBA74C + -0xdf + gnScreenHeight < (int)uVar5)) &&
	    ((int)uVar5 < dword_6FBBA74C + -0xb7 + gnScreenHeight))
	{
		dword_6FBB5B4C = 0;
		dword_6FBB5B48 = 0;
		pDVar2 = sub_6FB575E0();
		if (pDVar2 == nullptr)
		{
			dword_6FBB5B54 = 1;
			dword_6FBB5B50 = 1;
			dword_6FBB5BA8 = 1;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		}
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
	if (iVar1 == 1)
	{
		dword_6FBB5B20 = 0;
		dword_6FBB5B28 = 0;
		dword_6FBB5B48 = 0;
		dword_6FBB5B4C = 0;
		dword_6FBB5B50 = 0;
		dword_6FBB5B54 = 0;
		dword_6FBB5BA8 = 0;
		return;
	}
	if (((((int)uVar4 < dword_6FBB38C8) || (dword_6FBB38CC <= (int)uVar4)) ||
	        (((int)uVar5 < dword_6FBB38D0 || (dword_6FBB38D4 < (int)uVar5)))) &&
	    (((((int)uVar4 < dword_6FBB38B4 || (dword_6FBB38B8 <= (int)uVar4)) || ((int)uVar5 < dword_6FBB38BC)) || (dword_6FBB38C0 < (int)uVar5))))
	{
		pDVar2 = CUNIT_GetPlayer();
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		if ((((pDVar2 != nullptr) || ((int)uVar5 < dword_6FBBA74C + -0x57 + gnScreenHeight)) ||
		        (dword_6FBBA74C + -0x45 + gnScreenHeight < (int)uVar5)) ||
		    (((int)uVar4 < (gnScreenWidth - dword_6FBBA748) + -0xed ||
		        ((gnScreenWidth - dword_6FBBA748) + -0xd9 < (int)uVar4))))
		{
			if (((dword_6FBB3850 <= (int)uVar4) && ((int)uVar4 < dword_6FBB3854)) &&
			    ((int)uVar5 <= dword_6FBB385C))
			{
				dword_6FBB5B28 = 0;
				dword_6FBB5B20 = 0;
				dword_6FBB5BA8 = 0;
				dword_6FBB5B48 = 0;
				dword_6FBB5B4C = 0;
				dword_6FBB5B50 = 0;
				dword_6FBB5B54 = 0;
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			goto LAB_6faec99a;
		}
		dword_6FBB5B38 = 1;
		dword_6FBB5B28 = 0;
		dword_6FBB5B20 = 0;
		dword_6FBB5BA8 = 0;
		dword_6FBB5B48 = 0;
		dword_6FBB5B50 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
	}
	else
	{
		sub_6FAE6E60(pSMSGHANDLER_PARAMS);
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
	}
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
LAB_6faec99a:
	if (((((pSMSGHANDLER_PARAMS->bUseResult == 0) &&
	          (DVar3 = D2GFX_GetResolutionMode(), DVar3 == NUM_GAME_RESOLUTIONS)) &&
	         (iVar1 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS), iVar1 == 0)) &&
	        ((int)uVar5 <= gnScreenHeight + -0x30)) &&
	    ((iVar1 = sub_6FAB5750(), iVar1 != 1 || (gnScreenWidth / 2 <= (int)uVar4))))
	{
		iVar1 = sub_6FB57CC0();
		if (iVar1 == 6)
		{
			sub_6FB23A40();
		}
		iVar1 = sub_6FAB5750();
		if (((iVar1 != 3) || (dword_6FBB58EC != 0)) || (gnScreenWidth / 2 <= (int)uVar4))
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			dword_6FBB58E0 = 0;
			dword_6FBB58E4 = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
	dword_6FBB5B54 = 0;
	dword_6FBB5B4C = 0;
	dword_6FBB5B28 = 0;
}

//D2Client.0x6FAECB60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAECB60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2InventoryStrc* pInventory;
	bool bVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_var;
	int iVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;

	if (dword_6FBB58EC != 0xe)
	{
		dword_6FBB5BA8 = 0;
		return;
	}
	uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	dword_6FBB5B98 = 0;
	byte_6FBB5B9C = 0;
	dword_6FBB388C = uVar5;
	dword_6FBB3894 = uVar4;
	pDVar2 = CUNIT_GetPlayer();
	pInventory = pDVar2->pInventory;
	bVar1 = sub_6FAFE9E0();
	if (((((D2C_ZEXT(bVar1) == 0) &&
	          (pDVar2 = INVENTORY_GetCursorItem(pInventory), pDVar2 == nullptr)) &&
	         ((gnScreenWidth - dword_6FBBA748) + -0x12e <= (int)uVar5)) &&
	        (((int)uVar5 <= (gnScreenWidth - dword_6FBBA748) + -0x10e &&
	            (dword_6FBBA74C + -0x60 + gnScreenHeight <= (int)uVar4)))) &&
	    ((int)uVar4 <= dword_6FBBA74C + -0x40 + gnScreenHeight))
	{
		sub_6FB23260(0x1a, 1, 0);
		return;
	}
	if (((dword_6FBBA748 + 0x113 < (int)uVar5) && ((int)uVar5 < dword_6FBBA748 + 0x13b)) &&
	    ((dword_6FBBA74C + -100 + gnScreenHeight < (int)uVar4 &&
	        ((int)uVar4 < dword_6FBBA74C + -0x3c + gnScreenHeight))))
	{
		if (dword_6FBB5B48 != 0)
		{
			dword_6FBB5B48 = 0;
			dword_6FBB5910 = 0;
			sub_6FB23260(0x1a, 1, 0);
			if (dword_6FBB5954 == 0)
			{
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x17, 0, 0);
				dword_6FBB5954 = 1;
			}
			if (dword_6FBB5950 != 0)
			{
				pDVar2 = sub_6FB269F0(dword_6FB792A8, 2);
				if (pDVar2 != nullptr)
				{
					sub_6FB4E7E0(2, dword_6FB792A8);
				}
				dword_6FBB5950 = 0;
			}
		}
	}
	else
	{
		if ((((dword_6FBBA748 + 0x90 < (int)uVar5) && ((int)uVar5 < dword_6FBBA748 + 0xb8)) &&
		        (dword_6FBBA74C + -0xdf + gnScreenHeight < (int)uVar4)) &&
		    ((int)uVar4 < dword_6FBBA74C + -0xb7 + gnScreenHeight))
		{
			if (dword_6FBB5B50 != 0)
			{
				dword_6FBB5B50 = 0;
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)dword_6FBBA74C >> 8), 0x4f), 0x18, 0, 0);
			}
			dword_6FBB5B54 = 0;
			goto LAB_6faece57;
		}
		dword_6FBB5B48 = 0;
		dword_6FBB5B4C = 0;
		dword_6FBB5B50 = 0;
		dword_6FBB5B54 = 0;
		iVar3 = sub_6FB01B50((int)pSMSGHANDLER_PARAMS);
		if (iVar3 == 1)
		{
			dword_6FBB5B28 = 0;
			dword_6FBB5B4C = 0;
			dword_6FBB5B54 = 0;
			return;
		}
		pDVar2 = CUNIT_GetPlayer();
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		if ((((pDVar2 == nullptr) && (dword_6FBBA74C + -0x57 + gnScreenHeight <= (int)uVar4)) &&
		        (((int)uVar4 <= dword_6FBBA74C + -0x45 + gnScreenHeight &&
		            (((gnScreenWidth - dword_6FBBA748) + -0xed <= (int)uVar5 &&
		                ((int)uVar5 <= (gnScreenWidth - dword_6FBBA748) + -0xd9)))))) &&
		    (dword_6FBB5B34 == 0))
		{
			sub_6FB23B40(1);
		}
		dword_6FBB5B38 = 0;
		if (dword_6FBB5BA8 == 0)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB5BA8 = 0;
			dword_6FBB5B48 = 0;
			dword_6FBB5B50 = 0;
			dword_6FBB5B20 = 0;
			return;
		}
		if (dword_6FBB5B28 == 0)
		{
			if (dword_6FBB5B4C == 0)
			{
				if ((dword_6FBB5B54 != 0) && (dword_6FBB5B50 != 0))
				{
					dword_6FBB5B50 = 0;
				}
			}
			else if (dword_6FBB5B48 != 0)
			{
				dword_6FBB5B48 = 0;
			}
		}
		else if (dword_6FBB5B20 != 0)
		{
			dword_6FBB5B20 = 0;
		}
		dword_6FBB5B28 = 0;
		dword_6FBB5B54 = 0;
	}
	dword_6FBB5B4C = 0;
LAB_6faece57:
	dword_6FBB5BA8 = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAECEA0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAECEA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;

	if (dword_6FBB58EC == 0xe)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		iVar1 = sub_6FB23230(1);
		if (iVar1 == 0)
		{
			dword_6FBB58E0 = 0;
			dword_6FB79290 = 0xffffffff;
			dword_6FB79294 = 0xffffffff;
			dword_6FB79298 = 0xffffffff;
			dword_6FB7929C = 0xffffffff;
			dword_6FB792A0 = 0xffffffff;
			dword_6FB792A4 = 0xffffffff;
			dword_6FBB58E4 = 0;
			gpUnit_6FBB58F0 = nullptr;
			dword_6FBB58F4 = 0;
		}
		iVar1 = sub_6FB23860(5);
		if (iVar1 == 0)
		{
			dword_6FBB5910 = 0;
			sub_6FB23260(0x1a, 1, 0);
			if (dword_6FBB5954 == 0)
			{
				sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x17, 0, 0);
				dword_6FBB5954 = 1;
			}
			if (dword_6FBB5950 != 0)
			{
				pDVar2 = sub_6FB269F0(dword_6FB792A8, 2);
				if (pDVar2 != nullptr)
				{
					sub_6FB4E7E0(2, dword_6FB792A8);
				}
				dword_6FBB5950 = 0;
			}
		}
	}
}

//D2Client.0x6FAECF90
void __cdecl sub_6FAECF90()
{
	int iVar1;

	iVar1 = sub_6FB23260(0x1a, 0, 0);
	if (iVar1 != 0)
	{
		dword_6FBB5954 = 0;
		dword_6FBB58EC = 0xe;
		sub_6FAABF30();
		dword_6FBB5B38 = 0;
		dword_6FBB5B48 = 0;
		dword_6FBB5B4C = 0;
		dword_6FBB5B50 = 0;
		dword_6FBB5B54 = 0;
	}
}

//D2Client.0x6FAECFE0
void __cdecl sub_6FAECFE0()
{
	char local_104[260];

	byte_6FBB3790 = 0;
	if (gpCellFile_6FBB5930 == nullptr)
	{
		SStrPrintf(local_104, 0x104, "%s\\ui\\panel\\supertransmogrifier", "DATA\\GLOBAL");
		gpCellFile_6FBB5930 = CLIENT_LoadCellFile(local_104, 0);
	}
}

//D2Client.0x6FAED030
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAED030()
{
	D2UnitStrc* pDVar1;
	uint32_t extraout_ECX;

	if (dword_6FBB58EC == 0xe)
	{
		dword_6FBB58EC = 0;
		dword_6FBB5910 = 0;
		sub_6FB23260(0x1a, 1, 0);
		if (dword_6FBB5954 == 0)
		{
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 0x17, 0, 0);
			dword_6FBB5954 = 1;
		}
		if (dword_6FBB5950 != 0)
		{
			pDVar1 = sub_6FB269F0(dword_6FB792A8, 2);
			if (pDVar1 != nullptr)
			{
				sub_6FB4E7E0(2, dword_6FB792A8);
			}
			dword_6FBB5950 = 0;
		}
	}
	if (gpCellFile_6FBB5930 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5930);
		gpCellFile_6FBB5930 = nullptr;
	}
}

//D2Client.0x6FAED0D0
void __fastcall sub_6FAED0D0(int a1)
{
	D2BitBufferStrc* pQuestRecord;
	int iVar1;
	char acStack_104[260];

	pQuestRecord = sub_6FAFBD20();
	if (a1 == 0x20747368)
	{
		if (pQuestRecord == nullptr)
		{
			return;
		}
		iVar1 = QUESTRECORD_GetQuestState(pQuestRecord, 10, 0xb);
		if (iVar1 != 0)
		{
			return;
		}
		iVar1 = 10;
	}
	else
	{
		if (a1 != 0x20326671)
			goto LAB_6faed129;
		if (pQuestRecord == nullptr)
		{
			return;
		}
		iVar1 = QUESTRECORD_GetQuestState(pQuestRecord, 0x12, 0xb);
		if (iVar1 != 0)
		{
			return;
		}
		iVar1 = 0x12;
	}
	QUESTRECORD_SetQuestState(pQuestRecord, iVar1, 0xb);
LAB_6faed129:
	dword_6FBB5910 = 1;
	dword_6FBB5914 = 0;
	dword_6FBB5918 = GetTickCount();
	if (gpCellFile_6FBB591C == nullptr)
	{
		SStrPrintf(acStack_104, 0x104, "%s\\ui\\menu\\horadric", "DATA\\GLOBAL");
		gpCellFile_6FBB591C = CLIENT_LoadCellFile(acStack_104, 0);
	}
}

//D2Client.0x6FAED190
void __cdecl sub_6FAED190()
{
	if (gpCellFile_6FBB591C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB591C);
		gpCellFile_6FBB591C = nullptr;
	}
	dword_6FBB5910 = 0;
	dword_6FBB5914 = 0;
	dword_6FBB5918 = 0;
}

//D2Client.0x6FAED1C0
void __cdecl sub_6FAED1C0()
{
	D2UnitStrc* pDVar1;
	uint8_t uStack_28;
	uint8_t uStack_27;
	uint8_t uStack_26;
	uint32_t uStack_25;

	dword_6FBB58EC = 1;
	pDVar1 = CUNIT_GetPlayer();
	pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
	sub_6FB575B0(pDVar1);
	uStack_28 = 0x5a;
	uStack_26 = 1;
	uStack_25 = 0;
	uStack_27 = 0xe;
	sub_6FB1D3C0((int)&uStack_28);
}

//D2Client.0x6FAED210
void __cdecl sub_6FAED210()
{
	byte_6FBB3790 = 0;
}

//D2Client.0x6FAED220
void __cdecl sub_6FAED220()
{
	D2UnitStrc* pDVar1;

	dword_6FBB5BA8 = 0;
	dword_6FBB58EC = 0;
	dword_6FBB388C = 0;
	dword_6FBB3894 = 0;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		if (pDVar1 != nullptr)
		{
			return;
		}
	}
	sub_6FB575B0(nullptr);
}

//D2Client.0x6FAED260
void __cdecl sub_6FAED260()
{
	dword_6FBB5B30 = 1;
}

//D2Client.0x6FAED270
void __cdecl sub_6FAED270()
{
	dword_6FBB5B30 = 0;
}

//D2Client.0x6FAED280
void __cdecl sub_6FAED280()
{
	int iVar1;

	iVar1 = FOG_IsExpansion();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FAAC080();
		if (iVar1 != 0)
		{
			dword_6FBB594C = (uint32_t)(dword_6FBB594C == 0);
		}
	}
}

//D2Client.0x6FAED2B0
void __cdecl sub_6FAED2B0()
{
	D2InventoryStrc* pInventory;
	int iVar1;
	D2UnitStrc* pDVar2;

	iVar1 = FOG_IsExpansion();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FAAC080();
		if (iVar1 != 0)
		{
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
			CLIENT_SendSimpleMessage(0x60);
			pDVar2 = CUNIT_GetPlayer();
			pInventory = pDVar2->pInventory;
			pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
			if (pDVar2 != nullptr)
			{
				sub_6FB2FB30(pDVar2);
			}
			pDVar2 = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
			if (pDVar2 != nullptr)
			{
				sub_6FB2FB30(pDVar2);
				return;
			}
		}
	}
}

//D2Client.0x6FAED310
void __cdecl sub_6FAED310()
{
	D2UnitStrc* pUnit;
	D2UnitStrc* pDVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	uint8_t* pbVar7;
	uint8_t bStack_1a;
	uint8_t bStack_19;
	int iStack_18;
	int iStack_14;
	int iStack_10;
	D2UnitStrc* pDStack_c;
	uint32_t uStack_8;
	D2UnitStrc* local_4;

	pDVar1 = CUNIT_GetPlayer();
	pDStack_c = INVENTORY_GetCursorItem(pDVar1->pInventory);
	if (pDStack_c != nullptr)
	{
		iStack_18 = 0;
		pbVar7 = &byte_6FBB5A49;
		do
		{
			iVar4 = *(int*)(pbVar7 + -0x11);
			if (0 < iVar4)
			{
				iStack_10 = *(int*)(pbVar7 + -5);
				iStack_14 = *(int*)(pbVar7 + -9);
				iVar6 = *(int*)(pbVar7 + -0xd);
				iVar2 = sub_6FB57BC0();
				iVar3 = sub_6FB57BD0();
				pDVar1 = pDStack_c;
				if ((((iVar4 <= iVar2) && (iVar2 <= iVar6)) && (iStack_14 <= iVar3)) && (iVar3 <= iStack_10))
				{
					ITEMS_GetDimensions(pDStack_c, &bStack_19, &bStack_1a, __FILE__, __LINE__);
					uStack_8 = 0;
					iVar4 = ITEMS_CheckBodyLocation(pDVar1, (uint8_t)iStack_18);
					pUnit = local_4;
					if (((iVar4 == 0) || (iVar4 = sub_6FAED470(local_4, pDVar1, &uStack_8), iVar4 == 0)) ||
					    (iVar4 = ITEMS_CheckRequirements(pDVar1, pUnit, 0, nullptr, nullptr, nullptr),
					        iVar4 == 0))
					{
						iVar6 = *(int*)(pbVar7 + -0x11);
						iVar2 = *(int*)(pbVar7 + -9);
						if (((-1 < iVar6) && (iVar6 < gnViewWidth)) && ((-1 < iVar2 && (iVar2 < gnViewHeight))))
						{
							uVar5 = CONCAT31((int32_t)((uint32_t)iVar4 >> 8), byte_6FBB3778);
							goto LAB_6faed434;
						}
					}
					else
					{
						iVar6 = *(int*)(pbVar7 + -0x11);
						iVar2 = *(int*)(pbVar7 + -9);
						if ((((-1 < iVar6) && (iVar6 < gnViewWidth)) && (-1 < iVar2)) && (iVar2 < gnViewHeight))
						{
							uVar5 = CONCAT31((int32_t)((uint32_t)iVar4 >> 8), byte_6FBB3779);
						LAB_6faed434:
							sub_6FB5B0F0(iVar6, iVar2, (uint32_t)pbVar7[-1], (uint32_t)*pbVar7, uVar5, (DrawMode)(0));
						}
					}
				}
			}
			pbVar7 = pbVar7 + 0x14;
			iStack_18 = iStack_18 + 1;
		} while ((int)pbVar7 < (int)&tbl_6FBB5B25);
	}
}

//D2Client.0x6FAED470
int __fastcall sub_6FAED470(D2UnitStrc* pUnit, D2UnitStrc* pUnit2, uint32_t* a3)
{
	int iVar1;
	uint32_t uVar2;
	int iVar3;

	*a3 = 0;
	iVar1 = sub_6FAAC080();
	if (iVar1 == 0)
	{
		return 0;
	}
	iVar3 = 0;
	iVar1 = ITEMS_CheckItemFlag(pUnit2, 0x10, __LINE__, __FILE__);
	if (iVar1 == 0)
	{
		return 0;
	}
	iVar1 = ITEMS_CheckItemFlag(pUnit2, 0x100, __LINE__, __FILE__);
	if (iVar1 != 0)
	{
		return 0;
	}
	iVar1 = ITEMS_CheckItemTypeId(pUnit2, 3);
	if ((iVar1 != 0) || (iVar1 = ITEMS_CheckItemTypeId(pUnit2, 0x25), iVar1 != 0))
	{
		iVar3 = 1;
		*a3 = 1;
	}
	if (pUnit == nullptr)
	{
		uVar2 = 0xffffffff;
	}
	else
	{
		uVar2 = pUnit->dwUnitId;
	}
	iVar1 = sub_6FAB1AE0(uVar2);
	if (iVar1 < 0x168)
	{
		if (iVar1 != 0x167)
		{
			if (iVar1 == 0x10f)
			{
				iVar1 = 0x1b;
			}
			else
			{
				if (iVar1 != 0x152)
					goto LAB_6faed55f;
				iVar1 = ITEMS_CheckItemTypeId(pUnit2, 0x21);
				if (iVar1 != 0)
					goto LAB_6faed5c2;
				iVar1 = 0x22;
			}
			goto LAB_6faed5b8;
		}
		iVar1 = ITEMS_CheckItemTypeId(pUnit2, 2);
		if (iVar1 != 0)
		{
			iVar3 = 1;
			*a3 = 1;
		}
		iVar1 = ITEMS_CheckItemTypeId(pUnit2, 0x1e);
		if ((iVar1 == 0) || (uVar2 = ITEMS_CheckWeaponIfTwoHanded(pUnit2), uVar2 != 0))
			goto LAB_6faed55f;
	}
	else
	{
		if (iVar1 == 0x230)
		{
			iVar1 = ITEMS_CheckItemTypeId(pUnit2, 0x1c);
			if ((iVar1 != 0) && (uVar2 = ITEMS_CheckWeaponIfTwoHanded(pUnit2), uVar2 == 0))
			{
			LAB_6faed5af:
				iVar3 = 1;
				*a3 = 1;
			}
		}
		else
		{
			if (iVar1 != 0x231)
				goto LAB_6faed55f;
			iVar1 = ITEMS_CheckItemTypeId(pUnit2, 0x1e);
			if (iVar1 != 0)
				goto LAB_6faed5af;
		}
		iVar1 = 0x47;
	LAB_6faed5b8:
		iVar1 = ITEMS_CheckItemTypeId(pUnit2, iVar1);
		if (iVar1 == 0)
		{
		LAB_6faed55f:
			if (iVar3 == 0)
			{
				return 0;
			}
			goto LAB_6faed563;
		}
	}
LAB_6faed5c2:
	iVar3 = 1;
	*a3 = 1;
LAB_6faed563:
	iVar1 = ITEMS_CheckRequirements(pUnit2, pUnit, 0, nullptr, nullptr, nullptr);
	if (iVar1 == 0)
	{
		iVar3 = 0;
	}
	return iVar3;
}

//D2Client.0x6FAED5D0
// TODO: decompilation needs review (in_stack, stack0x, unaff_)
void __cdecl sub_6FAED5D0()
{
	uint8_t stack0xfffffe98[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffea4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffea8[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0xfffffeb0[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	D2CellFileStrc* pDVar5;
	Font nFontSize;
	Unicode* pUVar6;
	D2UnitStrc* pDVar7;
	uint32_t unaff_EBX;
	int iVar8;
	uint32_t unaff_EBP;
	uint32_t uVar9;
	uint32_t unaff_ESI;
	uint16_t* puVar10;
	int nX;
	uint32_t unaff_EDI;
	uint32_t* puVar11;
	int iVar12;
	D2CellFileStrc* pDVar13;
	int* in_stack_fffffe98;
	int* piVar14;
	D2UnitStrc* pDVar15;
	D2UnitStrc* in_stack_fffffea4;
	uint32_t in_stack_fffffea8;
	D2InventoryStrc* pInventory;
	D2GfxCellStrc* in_stack_fffffeb0;
	uint32_t uVar16;
	int in_stack_fffffec0;
	Unicode aUStack_108[30];
	Unicode aUStack_cc[101];
	uint16_t uStack_2;

	iVar2 = sub_6FAAC080();
	if (iVar2 != 0)
	{
		iVar2 = 0;
		pDVar3 = CUNIT_GetPlayer();
		uVar4 = sub_6FAB1920((int)pDVar3, 7, iVar2);
		if ((uVar4 == 0xffffffff) || (pDVar3 = sub_6FB269F0(uVar4, 1), pDVar3 == nullptr))
		{
			sub_6FB23260(0x24, 2, 0);
			return;
		}
		pDVar7 = pDVar3;
		sub_6FAE0A10();
		puVar11 = (uint32_t*)stack0xfffffeb0;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		uVar16 = 0;
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffeb0, dword_6FBBA748,
		    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffeb0, dword_6FBBA748 + 0x100,
		    dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffeb0, dword_6FBBA748,
		    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffeb0, dword_6FBBA748 + 0x100,
		    dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		pDVar5 = sub_6FB24110();
		uVar4 = (dword_6FBB5BAC != 0) + 10;
		TEXTURE_CelDraw((D2GfxDataStrc*)stack0xfffffeb0, dword_6FBBA748 + 0x110,
		    dword_6FBBA74C + -0x3f + gnScreenHeight, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT6);
		iVar2 = 0x20;
		pUVar6 = sub_6FB297F0(pDVar3);
		Unicode::strncpy(aUStack_108, pUVar6, iVar2);
		aUStack_cc[1].ch = 0;
		puVar10 = &aUStack_cc[1].ch;
		iVar2 = D2Win_10121_GetTextWidth(aUStack_108);
		while (0xa0 < iVar2)
		{
			puVar10 = puVar10 + -1;
			*puVar10 = 0;
			iVar2 = D2Win_10121_GetTextWidth(aUStack_108);
		}
		D2Win_10117_DrawText(aUStack_108, dword_6FBBA748 + 0xf, 0xd6 - dword_6FBBA74C, 0, 0);
		D2Win_10127_SetFont(nFontSize);
		pDVar3 = (D2UnitStrc*)D2Win_10127_SetFont(D2FONT_FONT6);
		uVar9 = 0;
		do
		{
			pUVar6 = aUStack_cc + 2;
			iVar2 = 100;
			do
			{
				pUVar6 = pUVar6 + 1;
				iVar2 = iVar2 + -1;
			} while (iVar2 != 0);
			iVar2 = 99;
			pUVar6 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)word_6FB6F8DC + uVar9)));
			Unicode::strncpy(aUStack_cc + 2, pUVar6, iVar2);
			uStack_2 = 0;
			iVar8 = *(int*)((int)&dword_6FB6F8D8 + uVar9) - dword_6FBBA74C;
			nX = *(int*)((int)&dword_6FB6F8D0 + uVar9) + dword_6FBBA748;
			iVar12 = *(int*)((int)&dword_6FB6F8D4 + uVar9) + dword_6FBBA748;
			iVar2 = sub_6FACFD10((short*)(aUStack_cc + 2), (uint32_t*)stack0xfffffe98);
			if (iVar2 == 0)
			{
				if (iVar12 == 0)
				{
					D2Win_10117_DrawText(aUStack_cc + 2, nX, iVar8, 0, 0);
				}
				else
				{
					sub_6FACFCD0(nX, iVar8, iVar12, aUStack_cc + 2, nullptr);
				}
			}
			else
			{
				sub_6FACFCD0(nX, iVar8 + -4, iVar12, aUStack_cc + 2, nullptr);
				sub_6FACFCD0(nX, iVar8 + 4, iVar12, (Unicode*)(in_stack_fffffe98), nullptr);
			}
			uVar9 = uVar9 + 0xe;
		} while (uVar9 < 0xa8);
		D2Win_10127_SetFont((Font)(int)pDVar3);
		pDVar15 = pDVar7;
		sub_6FAEDA20(pDVar7);
		sub_6FAEE150(pDVar7);
		pInventory = pDVar7->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = nullptr;
			in_stack_fffffe98 = (int*)(&dword_6FBB5A38);
			do
			{
				piVar14 = in_stack_fffffe98;
				pDVar7 = INVENTORY_GetItemFromBodyLoc(pInventory, (int)pDVar3);
				if (pDVar7 != nullptr)
				{
					ITEMS_GetDimensions(pDVar7, stack0xfffffea4, stack0xfffffea8,
					    __FILE__, __LINE__);
					pDVar13 = (D2CellFileStrc*)((int)((uint32_t) * (uint8_t*)(in_stack_fffffe98 + 4) -
					                                  ((uint32_t)in_stack_fffffea4 & 0xff) * (dword_6FBB370C & 0xff)) /
					                                2 +
					                            *in_stack_fffffe98);
					iVar2 = (int)((uint32_t) * (uint8_t*)((int)in_stack_fffffe98 + 0x11) -
					              (in_stack_fffffea8 & 0xff) * (dword_6FBB370C & 0xff)) /
					            2 +
					        in_stack_fffffe98[2];
					sub_6FB5A320(pDVar7, pDVar13, iVar2);
					if ((((gpUnit_6FBB58F0 == pDVar7) && (iVar8 = ITEMS_CheckIfSocketable(pDVar7), iVar8 != 0)) && (in_stack_fffffe98 = piVar14, bVar1 = ITEMS_GetMaxSockets(pDVar7), bVar1 != 0)) &&
					    (iVar8 = ITEMS_CheckItemFlag(pDVar7, 0x800, __LINE__, __FILE__), iVar8 != 0))
					{
						sub_6FAE0DC0(pDVar7, (int)&byte_6FBB36F8, pDVar13, iVar2);
					}
				}
				in_stack_fffffe98 = in_stack_fffffe98 + 5;
				pDVar3 = (D2UnitStrc*)((int)&pDVar3->dwUnitType + D2FONT_FONT16);
			} while ((int)in_stack_fffffe98 < (int)&dword_6FBB5B14);
		}
		sub_6FAED310();
		sub_6FAE1890((D2UnitStrc*)(unaff_EDI), unaff_ESI, unaff_EBP, unaff_EBX, (int)(in_stack_fffffe98), pDVar3, (Unicode*)(pDVar15),
		    in_stack_fffffea4, in_stack_fffffea8, (uint32_t)(pInventory), (uint32_t)(in_stack_fffffeb0), pDVar5, uVar4,
		    uVar16, in_stack_fffffec0);
	}
}

//D2Client.0x6FAEDA20
void __fastcall sub_6FAEDA20(D2UnitStrc* pUnit)
{
	uint8_t bVar1;
	char cVar2;
	short sVar3;
	int iVar4;
	int iVar5;
	int nY;
	int iVar6;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	D2DifficultyLevelsTxt* pDVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iVar14;
	D2UnitStrc* pItem;
	Unicode* pThis;
	int* piVar15;
	int iVar16;
	D2SkillsTxt* pDStack_1e4;
	int iStack_1e0;
	int iStack_1dc;
	int iStack_1d8;
	uint32_t uStack_1d4;
	int aiStack_1bc[3];
	uint32_t uStack_1b0;
	int aiStack_1ac[11];
	Unicode aUStack_180[128];
	char acStack_80[128];

	if (pUnit != nullptr)
	{
		aiStack_1bc[2] = D2Win_10127_SetFont(D2FONT_FONT8);
		uStack_1d4 = 0;
		do
		{
			pDStack_1e4 = nullptr;
			iVar13 = uStack_1d4 * 0x14;
			iStack_1dc = STATLIST_UnitGetStatValue(pUnit, *(int*)(byte_6FB79608 + iVar13), 0);
			iVar12 = STATLIST_GetUnitBaseStat(pUnit, *(int*)(byte_6FB79608 + iVar13), 0);
			if (iVar12 < iStack_1dc)
			{
				pDStack_1e4 = (D2SkillsTxt*)0x3;
			}
			else if (iStack_1dc < iVar12)
			{
				pDStack_1e4 = (D2SkillsTxt*)0x1;
			}
			iVar12 = *(int*)(byte_6FB795F8 + iVar13) + dword_6FBBA748;
			iVar4 = *(int*)(byte_6FB795FC + iVar13) + dword_6FBBA748;
			iVar5 = *(int*)(byte_6FB79600 + iVar13) - dword_6FBBA74C;
			nY = iVar5 + -2;
			switch (*(uint32_t*)(byte_6FB79608 + iVar13))
			{
			case 6:
				iVar11 = STATLIST_GetMaxLifeFromUnit(pUnit);
				iVar11 = iVar11 >> 8;
				iVar16 = sub_6FAB1AC0(pUnit->dwUnitId);
				iVar16 = (iVar16 * iVar11) / 100;
				iVar6 = sub_6FB29550((int*)pUnit);
				if ((iVar6 == 0) && (iVar16 < 0))
				{
					iVar16 = 1;
				}
				SStrPrintf(acStack_80, 0x80, "%d / %d", iVar16, iVar11);
				Unicode::toUnicode(aUStack_180, acStack_80, 0x80);
				iVar16 = STATLIST_GetUnitBaseStat(pUnit, 7, 0);
				if (iVar16 >> 8 < iVar11)
				{
					pDStack_1e4 = (D2SkillsTxt*)0x3;
				}
				goto LAB_6faee01f;
			default:
				break;
			case 0x15:
				iVar14 = 0;
				pItem = nullptr;
				iVar16 = STATLIST_UnitGetStatValue(pUnit, 0x19, 0);
				iVar11 = STATLIST_UnitGetStatValue(pUnit, 0x12, 0);
				iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x11, 0);
				if (iVar11 + iVar16 < 1)
				{
					if (iVar11 + iVar16 < 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
				}
				else
				{
					pDStack_1e4 = (D2SkillsTxt*)0x3;
				}
				if (pUnit->pInventory != nullptr)
				{
					pItem = INVENTORY_GetItemFromBodyLoc(pUnit->pInventory, 4);
				}
				iStack_1e0 = STATLIST_UnitGetStatValue(pUnit, 0x16, 0);
				if (pItem == nullptr)
				{
					if (pUnit->dwClassId == 0x10f)
					{
						iVar8 = 2;
					}
					else
					{
						iVar8 = 0;
					}
					iVar8 = STATLIST_UnitGetStatValue(pUnit, iVar8, 0);
					iVar16 = iVar16 + iVar8;
				}
				else
				{
					uVar7 = ITEMS_CheckWeaponIfTwoHanded(pItem);
					if (uVar7 != 0)
					{
						iVar14 = STATLIST_UnitGetStatValue(pItem, 0x15, 0);
						iVar8 = STATLIST_UnitGetStatValue(pItem, 0x16, 0);
						iVar9 = STATLIST_UnitGetStatValue(pUnit, 0x17, 0);
						iStack_1dc = (iStack_1dc - iVar14) + iVar9;
						iVar14 = STATLIST_UnitGetStatValue(pUnit, 0x18, 0);
						iStack_1e0 = (iStack_1e0 - iVar8) + iVar14;
					}
					sVar3 = ITEMS_GetStrengthBonus(pItem);
					if (sVar3 != 0)
					{
						iVar14 = STATLIST_UnitGetStatValue(pUnit, 0, 0);
						iVar16 = iVar16 + (iVar14 * sVar3) / 100;
					}
					sVar3 = ITEMS_GetDexBonus(pItem);
					if (sVar3 != 0)
					{
						iVar14 = STATLIST_UnitGetStatValue(pUnit, 2, 0);
						iVar16 = iVar16 + (iVar14 * sVar3) / 100;
					}
					iVar14 = SKILLS_GetWeaponMasteryBonus(pUnit, pItem, nullptr, 1);
					iVar16 = iVar16 + iVar14;
					iVar14 = STATLIST_UnitGetItemStatOrSkillStatValue(pItem, 0x6f, 0);
				}
				if (iVar16 < -0x59)
				{
					iVar16 = -0x5a;
				}
				uStack_1b0 = 0x30;
				aiStack_1ac[0] = 0x31;
				aiStack_1ac[1] = 1;
				aiStack_1ac[2] = 0x32;
				iVar11 = ((iVar11 + 100 + iVar16) * iStack_1dc) / 100 + iVar14;
				aiStack_1ac[3] = 0x33;
				aiStack_1ac[4] = 9;
				iVar14 = ((iVar6 + 100 + iVar16) * iStack_1e0) / 100 + iVar14;
				aiStack_1ac[5] = 0x34;
				aiStack_1ac[6] = 0x35;
				aiStack_1ac[7] = 3;
				aiStack_1ac[8] = 0x36;
				aiStack_1ac[9] = 0x37;
				aiStack_1ac[10] = 3;
				piVar15 = aiStack_1ac;
				iStack_1d8 = 4;
				do
				{
					iVar16 = STATLIST_UnitGetStatValue(pUnit, piVar15[-1], 0);
					iVar6 = STATLIST_UnitGetStatValue(pUnit, *piVar15, 0);
					if ((iVar16 != 0) || (iVar6 != 0))
					{
						pDStack_1e4 = (D2SkillsTxt*)piVar15[1];
					}
					iVar14 = iVar14 + iVar6;
					iVar11 = iVar11 + iVar16;
					piVar15 = piVar15 + 3;
					iStack_1d8 = iStack_1d8 + -1;
				} while (iStack_1d8 != 0);
				iVar16 = STATLIST_UnitGetStatValue(pUnit, 0x39, 0);
				iVar6 = STATLIST_UnitGetStatValue(pUnit, 0x3a, 0);
				if ((iVar16 != 0) || (iVar6 != 0))
				{
					iVar8 = STATLIST_UnitGetStatValue(pUnit, 0x65, 0);
					if (iVar8 < 1)
					{
						iVar9 = STATLIST_UnitGetStatValue(pUnit, 0x146, 0);
						if (iVar9 < 1)
						{
							iVar9 = 1;
						}
						iVar8 = STATLIST_UnitGetStatValue(pUnit, 0x3b, 0);
						iVar8 = iVar8 / iVar9;
					}
					iVar11 = iVar11 + (iVar8 * iVar16 >> 8);
					pDStack_1e4 = (D2SkillsTxt*)0x2;
					iVar14 = iVar14 + (iVar8 * iVar6 >> 8);
				}
				SStrPrintf(acStack_80, 0x80, "%d-%d", iVar11, iVar14);
				Unicode::toUnicode(aUStack_180, acStack_80, 0x80);
				goto LAB_6faee01f;
			case 0x1f:
				iStack_1dc = UNITS_GetDefense(pUnit);
				iVar16 = STATES_CheckStateMaskArmBlueOnUnit(pUnit);
				if (iVar16 != 0)
				{
					pDStack_1e4 = (D2SkillsTxt*)0x3;
				}
				break;
			case 0x27:
			case 0x29:
			case 0x2b:
			case 0x2d:
				bVar1 = sub_6FAAC090();
				pDVar10 = DATATBLS_GetDifficultyLevelsTxtRecord((uint32_t)bVar1);
				iVar16 = 0;
				switch (*(uint32_t*)(byte_6FB79608 + iVar13))
				{
				case 0x27:
					iVar16 = STATES_CheckStateMaskRFBlueOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x3;
					}
					iVar16 = STATES_CheckStateMaskRFRedOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
					iVar16 = 0x28;
					break;
				default:
					goto switchD_6faedee2_caseD_28;
				case 0x29:
					iVar16 = STATES_CheckStateMaskRLBlueOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x3;
					}
					iVar16 = STATES_CheckStateMaskRLRedOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
					iVar16 = 0x2a;
					break;
				case 0x2b:
					iVar16 = STATES_CheckStateMaskRCBlueOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x3;
					}
					iVar16 = STATES_CheckStateMaskRCRedOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
					iVar16 = 0x2c;
					break;
				case 0x2d:
					iVar16 = STATES_CheckStateMaskRPBlueOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x3;
					}
					iVar16 = STATES_CheckStateMaskRPRedOnUnit(pUnit);
					if (iVar16 != 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
					iVar16 = 0x2e;
				}
				iVar16 = STATLIST_UnitGetStatValue(pUnit, iVar16, 0);
			switchD_6faedee2_caseD_28:
				iVar11 = sub_6FAAC080();
				if (iVar11 == 0)
				{
					cVar2 = sub_6FAAC090();
					if (cVar2 == '\x01')
					{
						iStack_1dc = iStack_1dc + -0x14;
					}
					else if (cVar2 == '\x02')
					{
						iStack_1dc = iStack_1dc + -0x32;
					}
				}
				else
				{
					iStack_1dc = iStack_1dc + pDVar10->dwResistPenalty;
				}
				iVar16 = iVar16 + 0x4b;
				if (0x5e < iVar16)
				{
					iVar16 = 0x5f;
				}
				if (iStack_1dc < -99)
				{
					iStack_1dc = -100;
				}
				if (iStack_1dc < iVar16)
				{
					if (iStack_1dc < 0)
					{
						pDStack_1e4 = (D2SkillsTxt*)0x1;
					}
				}
				else
				{
					pDStack_1e4 = (D2SkillsTxt*)0x4;
					iStack_1dc = iVar16;
				}
			}
			STR_GroupIntDigits(aUStack_180, iStack_1dc, 0x80);
		LAB_6faee01f:
			D2Win_10127_SetFont(D2FONT_FONT8);
			aiStack_1bc[0] = 0;
			aiStack_1bc[1] = 0;
			D2Win_10131_GetTextDimensions(aUStack_180, aiStack_1bc, aiStack_1bc + 1);
			if ((*(int*)(byte_6FB79604 + iVar13) != 0) &&
			    (*(int*)(byte_6FB79604 + iVar13) < aiStack_1bc[0]))
			{
				D2Win_10127_SetFont(D2FONT_FONT6);
				nY = iVar5 + -1;
			}
			if (*(int*)(byte_6FB795F8 + iVar13) == 0)
			{
				iVar13 = 0;
				iVar12 = D2Win_10121_GetTextWidth(aUStack_180);
				D2Win_10117_DrawText(aUStack_180, iVar4 - iVar12, nY, (int)pDStack_1e4, iVar13);
			}
			else if (*(int*)(byte_6FB795FC + iVar13) == 0)
			{
				D2Win_10117_DrawText(aUStack_180, iVar12, nY, (int)pDStack_1e4, 0);
			}
			else
			{
				sub_6FACFCD0(iVar12, nY, iVar4, aUStack_180, pDStack_1e4);
			}
			uStack_1d4 = uStack_1d4 + 1;
		} while (uStack_1d4 < 0xc);
		D2Win_10127_SetFont((Font)(aiStack_1bc[2]));
	}
}

//D2Client.0x6FAEE150
void __fastcall sub_6FAEE150(D2UnitStrc* pUnit)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc* pDVar3;
	bool bVar4;
	D2UnitStrc* pDStack_4c;
	D2GfxDataStrc local_48;

	pInventory = pUnit->pInventory;
	pDVar3 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	if ((pInventory == nullptr) ||
	    (pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, 3), pDVar1 == nullptr))
	{
		local_48.pCellFile = gpCellFile_6FBB5B70;
		local_48.nFrame = 0;
		TEXTURE_CelDraw(&local_48, dword_6FB79500 + dword_6FBB5A74, dword_6FB79504 + dword_6FBB5A80, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
	}
	if ((pInventory == nullptr) ||
	    (pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, 1), pDVar1 == nullptr))
	{
		local_48.pCellFile = gpCellFile_6FBB5B7C;
		local_48.nFrame = 1;
		TEXTURE_CelDraw(&local_48, dword_6FB79518 + dword_6FBB5A4C, dword_6FB7951C + dword_6FBB5A58, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
	}
	if (pInventory == nullptr)
	{
		pDVar1 = nullptr;
		pDStack_4c = nullptr;
		bVar4 = false;
	LAB_6faee23e:
		local_48.pCellFile = gpCellFile_6FBB5B84;
		local_48.nFrame = 0;
		if (pDVar1 == nullptr)
		{
			TEXTURE_CelDraw(&local_48, dword_6FB79548 + dword_6FBB5A9C, dword_6FB7954C + dword_6FBB5AA8, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			goto LAB_6faee28b;
		}
		if (!bVar4)
		{
			TEXTURE_CelDraw(&local_48, dword_6FB79548 + dword_6FBB5A9C, dword_6FB7954C + dword_6FBB5AA8, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
		}
	}
	else
	{
		pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, 4);
		pDStack_4c = INVENTORY_GetItemFromBodyLoc(pInventory, 5);
		iVar2 = INVENTORY_GetWieldType(pUnit, pInventory);
		bVar4 = iVar2 == 2;
		if (pDStack_4c == nullptr)
			goto LAB_6faee23e;
	}
	if (pDVar1 != nullptr)
	{
		return;
	}
LAB_6faee28b:
	local_48.pCellFile = gpCellFile_6FBB5B84;
	local_48.nFrame = 0;
	if (pDStack_4c == nullptr)
	{
		TEXTURE_CelDraw(&local_48, dword_6FB79540 + dword_6FBB5A88, dword_6FB79544 + dword_6FBB5A94, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
	}
	else if (!bVar4)
	{
		TEXTURE_CelDraw(&local_48, dword_6FB79540 + dword_6FBB5A88, dword_6FB79544 + dword_6FBB5A94, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		return;
	}
}

//D2Client.0x6FAEE340
void __cdecl sub_6FAEE340(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar8 = 0;
	pDVar1 = CUNIT_GetPlayer();
	uVar2 = sub_6FAB1920((int)pDVar1, 7, iVar8);
	if (uVar2 == 0xffffffff)
	{
		sub_6FB23260(0x24, 2, 0);
		return;
	}
	pDVar1 = sub_6FB269F0(uVar2, 1);
	if (pDVar1 == nullptr)
	{
		sub_6FB23260(0x24, 2, 0);
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
	iVar8 = gnScreenHeight + -0x31;
	iVar7 = gnScreenWidth / 2;
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	if ((((-1 < iVar3) && (iVar3 <= iVar7)) && (-1 < iVar4)) && (iVar4 <= iVar8))
	{
		iVar4 = dword_6FBBA74C + -0x3f + gnScreenHeight;
		iVar7 = dword_6FBBA74C + -0x5f + gnScreenHeight;
		iVar8 = dword_6FBBA748 + 0x130;
		iVar3 = dword_6FBBA748 + 0x110;
		iVar5 = sub_6FB57BC0();
		iVar6 = sub_6FB57BD0();
		if (((iVar3 <= iVar5) && (iVar5 <= iVar8)) && ((iVar7 <= iVar6 && (iVar6 <= iVar4))))
		{
			dword_6FBB5BAC = 1;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAEE490
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAEE490(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t uVar7;
	int iVar8;
	int* piVar9;
	float fVar10;
	float fVar11;
	int iVar12;
	int iStack_14;
	int local_c;
	int iStack_8;
	D2UnitStrc* pDStack_4;

	iVar12 = 0;
	pDVar1 = CUNIT_GetPlayer();
	uVar2 = sub_6FAB1920((int)pDVar1, 7, iVar12);
	if ((uVar2 == 0xffffffff) || (pDVar1 = sub_6FB269F0(uVar2, 1), pDVar1 == nullptr))
	{
	LAB_6faee4c5:
		sub_6FB23260(0x24, 2, 0);
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
	sub_6FB57500((int)pSMSGHANDLER_PARAMS);
	dword_6FBB5BAC = 0;
	iVar12 = gnScreenHeight + -0x31;
	iVar8 = gnScreenWidth / 2;
	iVar3 = sub_6FB57BC0();
	iVar4 = sub_6FB57BD0();
	if ((-1 < iVar3) && (((iVar3 <= iVar8 && (-1 < iVar4)) && (iVar4 <= iVar12))))
	{
		local_c = dword_6FBBA74C + -0x3f + gnScreenHeight;
		iVar4 = dword_6FBBA74C + -0x5f + gnScreenHeight;
		iVar12 = dword_6FBBA748 + 0x130;
		iVar3 = dword_6FBBA748 + 0x110;
		iVar8 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		if ((((iVar3 <= iVar8) && (iVar8 <= iVar12)) && (iVar4 <= iVar5)) && (iVar5 <= local_c))
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			goto LAB_6faee4c5;
		}
		pDVar6 = CUNIT_GetPlayer();
		pDStack_4 = INVENTORY_GetCursorItem(pDVar6->pInventory);
		piVar9 = (int*)(&dword_6FBB5A3C);
		iStack_14 = 0;
		do
		{
			iVar12 = piVar9[-1];
			if (0 < iVar12)
			{
				iStack_8 = piVar9[2];
				local_c = piVar9[1];
				iVar3 = *piVar9;
				iVar4 = sub_6FB57BC0();
				iVar8 = sub_6FB57BD0();
				pDVar6 = pDStack_4;
				if (((iVar12 <= iVar4) && (iVar4 <= iVar3)) && ((local_c <= iVar8 && (iVar8 <= iStack_8))))
				{
					if (pDStack_4 != nullptr)
					{
						local_c = 0;
						iVar12 = ITEMS_CheckBodyLocation(pDStack_4, (uint8_t)iStack_14);
						if (((iVar12 == 0) ||
						        (iVar12 = ITEMS_CheckRequirements(pDVar6, pDVar1, 0, nullptr, nullptr, nullptr),
						            iVar12 == 0)) ||
						    (iVar12 = sub_6FAED470(pDVar1, pDVar6, (uint32_t*)(&local_c)), iVar12 == 0))
						{
							iVar12 = ITEMS_CheckBodyLocation(pDVar6, (uint8_t)iStack_14);
							uVar7 = extraout_EDX;
							if (((iVar12 == 0) ||
							        (iVar12 = sub_6FAED470(pDVar1, pDVar6, (uint32_t*)(&local_c)), uVar7 = extraout_EDX_00,
							            iVar12 == 0)) ||
							    (local_c == 0))
							{
								sub_6FB51920(pDVar1->dwUnitId, CONCAT31((int32_t)((uint32_t)uVar7 >> 8), 1), 0x55);
								pSMSGHANDLER_PARAMS->lResult = 0;
							}
							else
							{
								sub_6FB51920(pDVar1->dwUnitId, CONCAT31((int32_t)((uint32_t)extraout_EDX_00 >> 8), 1), 0x56);
								pSMSGHANDLER_PARAMS->lResult = 0;
							}
						}
						else
						{
							sub_6FB2FB30(pDVar6);
							iVar3 = 0;
							fVar11 = 0.0;
							fVar10 = 0.0;
							iVar12 = sub_6FB2E590(pDVar6);
							sub_6FB55820(iVar12, nullptr, fVar10, fVar11, iVar3);
							sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x61), 0);
							pSMSGHANDLER_PARAMS->lResult = 0;
						}
						goto LAB_6faee656;
					}
					if ((pDVar1->pInventory != nullptr) &&
					    (pDVar6 = INVENTORY_GetItemFromBodyLoc(pDVar1->pInventory, iStack_14),
					        pDVar6 != nullptr))
					{
						sub_6FB2FB30(pDVar6);
						sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x61), (short)iStack_14);
						dword_6FBB58E0 = 0;
						dword_6FBB58E4 = 0;
						gpUnit_6FBB58F0 = nullptr;
					}
				}
			}
			piVar9 = piVar9 + 5;
			iStack_14 = iStack_14 + 1;
		} while ((int)piVar9 < (int)&dword_6FBB5B18);
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->lResult = 0;
	LAB_6faee656:
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAEE730
void __cdecl sub_6FAEE730(int a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int* piVar8;
	int iVar9;

	iVar9 = 0;
	pDVar1 = CUNIT_GetPlayer();
	uVar2 = sub_6FAB1920((int)pDVar1, 7, iVar9);
	if (uVar2 == 0xffffffff)
	{
		sub_6FB23260(0x24, 2, 0);
		return;
	}
	pDVar1 = sub_6FB269F0(uVar2, 1);
	if (pDVar1 != nullptr)
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		iVar9 = gnScreenHeight + -0x31;
		iVar7 = gnScreenWidth / 2;
		iVar3 = sub_6FB57BC0();
		iVar4 = sub_6FB57BD0();
		if ((((-1 < iVar3) && (iVar3 <= iVar7)) && (-1 < iVar4)) && (iVar4 <= iVar9))
		{
			if (dword_6FBB5BAC != 0)
			{
				iVar4 = dword_6FBBA74C + -0x3f + gnScreenHeight;
				iVar7 = dword_6FBBA74C + -0x5f + gnScreenHeight;
				iVar9 = dword_6FBBA748 + 0x130;
				iVar3 = dword_6FBBA748 + 0x110;
				iVar5 = sub_6FB57BC0();
				iVar6 = sub_6FB57BD0();
				if (((iVar5 < iVar3) || (iVar9 < iVar5)) || ((iVar6 < iVar7 || (iVar4 < iVar6))))
				{
					dword_6FBB5BAC = 0;
				}
			}
			pInventory = pDVar1->pInventory;
			if (pInventory != nullptr)
			{
				dword_6FB79290 = -1;
				dword_6FB79294 = -1;
				dword_6FB79298 = -1;
				dword_6FB7929C = -1;
				dword_6FB792A0 = 0xffffffff;
				dword_6FB792A4 = 0xffffffff;
				dword_6FBB58E0 = 0;
				dword_6FBB58E4 = 0;
				gpUnit_6FBB58F0 = nullptr;
				dword_6FBB58F4 = (uint32_t)(nullptr);
				pDVar1 = CUNIT_GetPlayer();
				pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
				if (pDVar1 == nullptr)
				{
					piVar8 = (int*)(&dword_6FBB5A38);
					a1 = 0;
					do
					{
						iVar9 = *piVar8;
						if (0 < iVar9)
						{
							iVar3 = piVar8[3];
							iVar4 = piVar8[2];
							iVar7 = piVar8[1];
							iVar5 = sub_6FB57BC0();
							iVar6 = sub_6FB57BD0();
							if (((iVar9 <= iVar5) && (iVar5 <= iVar7)) &&
							    ((iVar4 <= iVar6 &&
							        (((iVar6 <= iVar3 &&
							              (pDVar1 = INVENTORY_GetItemFromBodyLoc(pInventory, a1),
							                  pDVar1 != nullptr)) &&
							            (dword_6FBB58E4 = 1, pDVar1 != (D2UnitStrc*)(dword_6FBB58F4)))))))
							{
								dword_6FB79294 = piVar8[2];
								dword_6FB79290 = (piVar8[1] + *piVar8) / 2;
								dword_6FB7929C = piVar8[3];
								dword_6FB79298 = dword_6FB79290;
								gpUnit_6FBB58F0 = pDVar1;
								dword_6FBB58F4 = (uint32_t)(pDVar1);
							}
						}
						piVar8 = piVar8 + 5;
						a1 = a1 + 1;
					} while ((int)piVar8 < (int)&dword_6FBB5B14);
				}
			}
		}
		return;
	}
	sub_6FB23260(0x24, 2, 0);
}

//D2Client.0x6FAEE970
void __cdecl sub_6FAEE970()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB38D8;
	iVar1 = 0x1000;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAEE990
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAEE990(char* a1)
{
	Unicode* in_ECX;

	Unicode::strcpy((Unicode*)&byte_6FBB38D8, in_ECX);
	gpchar_6FBB5BB0 = a1;
	sub_6FB23260(0x25, 0, 0);
}

//D2Client.0x6FAEE9C0
void __cdecl sub_6FAEE9C0()
{
	int iVar1;
	Font nFontSize;
	D2GfxDataStrc* pDVar2;
	D2GfxDataStrc local_48;

	iVar1 = sub_6FAAC080();
	if ((iVar1 != 0) && (iVar1 = sub_6FB23230(0x25), iVar1 != 0))
	{
		if ((gpCellFile_6FBB5B94 == nullptr) &&
		    (gpCellFile_6FBB5B94 = sub_6FB20100("menu\\recipescroll"),
		        gpCellFile_6FBB5B94 == nullptr))
		{
			return;
		}
		pDVar2 = &local_48;
		for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			pDVar2->pCurrentCell = 0;
			pDVar2 = (D2GfxDataStrc*)((int)pDVar2 + 4);
		}
		local_48.nDirection = 0;
		local_48.nFrame = 0;
		local_48.pCellFile = gpCellFile_6FBB5B94;
		TEXTURE_CelDraw(&local_48, dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		local_48.nFrame = 1;
		TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0xe0 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		local_48.nFrame = 2;
		TEXTURE_CelDraw(&local_48, dword_6FBBA748, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		local_48.nFrame = 3;
		TEXTURE_CelDraw(&local_48, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x30 + gnScreenHeight, 0xffffffff,
		    DRAWMODE_NORMAL, nullptr);
		nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL10);
		D2Win_10117_DrawText((Unicode*)&byte_6FBB38D8, dword_6FBBA748 + 0x50, 0x82 - dword_6FBBA74C, (int)gpchar_6FBB5BB0, 0);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FAEEB30
void __cdecl sub_6FAEEB30(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = gnScreenHeight + -0x31;
	iVar4 = gnScreenWidth / 2;
	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	if ((((-1 < iVar2) && (iVar2 <= iVar4)) && (-1 < iVar3)) && (iVar3 <= iVar1))
	{
		sub_6FB23260(0x25, 1, 0);
		sub_6FAABF60();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
}

//D2Client.0x6FAEEBA0
void __cdecl sub_6FAEEBA0()
{
	gpCellFile_6FBB5BB4 = sub_6FB20100("Panel\\Level");
	gpCellFile_6FBB5BB8 = sub_6FB20100("Panel\\Levelsocket");
}

//D2Client.0x6FAEEBC0
void __cdecl sub_6FAEEBC0()
{
	if (gpCellFile_6FBB5BB4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5BB4);
		gpCellFile_6FBB5BB4 = nullptr;
	}
	if (gpCellFile_6FBB5BB8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5BB8);
		gpCellFile_6FBB5BB8 = nullptr;
	}
}

//D2Client.0x6FAEEC00
void __cdecl sub_6FAEEC00()
{
	int iVar1;
	D2UnitStrc* pUnit;
	uint32_t uVar2;

	iVar1 = sub_6FB23230(0xb);
	if (iVar1 != 0)
	{
		return;
	}
	pUnit = CUNIT_GetPlayer();
	iVar1 = sub_6FB23230(6);
	if (iVar1 == 0)
	{
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
		if ((iVar1 == 0) || (iVar1 = sub_6FB23230(2), iVar1 != 0))
			goto LAB_6faeec62;
		uVar2 = 0;
	}
	else
	{
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 4, 0);
		if (iVar1 != 0)
			goto LAB_6faeec62;
		uVar2 = 1;
	}
	sub_6FB23260(6, uVar2, 0);
LAB_6faeec62:
	iVar1 = sub_6FB23230(7);
	if (iVar1 == 0)
	{
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
		if ((0 < iVar1) && (iVar1 = sub_6FB23230(4), iVar1 == 0))
		{
			sub_6FB23260(7, 0, 0);
		}
	}
	else
	{
		iVar1 = STATLIST_GetUnitBaseStat(pUnit, 5, 0);
		if (iVar1 < 1)
		{
			sub_6FB23260(7, 1, 0);
			return;
		}
	}
}

//D2Client.0x6FAEECC0
uint32_t __fastcall sub_6FAEECC0(int a1, int a2, int a3)
{
	int iVar1;
	bool bVar2;

	if (a1 == 2)
	{
		if (a2 <= gnScreenWidth / 2 + 0x28)
		{
			return 0;
		}
		iVar1 = gnScreenWidth / 2 + 0x4a;
		bVar2 = SBORROW4(a2, iVar1);
		iVar1 = -iVar1;
	}
	else
	{
		if (a2 < 0x29)
		{
			return 0;
		}
		bVar2 = SBORROW4(a2, 0x4a);
		iVar1 = -0x4a;
	}
	if (((bVar2 != a2 + iVar1 < 0) && (gnScreenHeight + -0x8b < a3)) &&
	    (a3 < gnScreenHeight + -0x66))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAEED20
uint32_t __fastcall sub_6FAEED20(int a1, int a2, int a3)
{
	int iVar1;

	iVar1 = gnScreenWidth;
	if (a1 == 1)
	{
		iVar1 = gnScreenWidth - gnScreenWidth / 2;
	}
	if ((((iVar1 + -0x49 < a2) && (a2 < iVar1 + -0x28)) && (gnScreenHeight + -0x8a < a3)) && (a3 < gnScreenHeight + -0x66))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAEED80
void __cdecl sub_6FAEED80(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	bool bVar7;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar6 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	DVar2 = D2GFX_GetResolutionMode();
	if ((DVar2 == NUM_GAME_RESOLUTIONS) && (iVar3 = sub_6FB23230(9), iVar3 != 0))
	{
		return;
	}
	iVar3 = sub_6FAB5750();
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		iVar4 = sub_6FB57BC0();
		iVar5 = sub_6FB57BD0();
		if (((iVar4 < 0xcf) || (0xef < iVar4)) || (iVar5 <= gnScreenHeight + -0x2a))
			goto LAB_6faeedf0;
		bVar7 = SBORROW4(iVar5, gnScreenHeight + -8);
		iVar5 = iVar5 - (gnScreenHeight + -8);
	}
	else
	{
		if (iVar3 == 2)
		{
			if (((gnScreenWidth / 2 + 0x28 < (int)(uint32_t)uVar1) &&
			        ((int)(uint32_t)uVar1 < gnScreenWidth / 2 + 0x4a)) &&
			    ((gnScreenHeight + -0x8b < (int)uVar6 && ((int)uVar6 < gnScreenHeight + -0x66))))
				goto LAB_6faeee4e;
			goto LAB_6faeedf0;
		}
		if (((uVar1 < 0x29) || (0x49 < uVar1)) || ((int)uVar6 <= gnScreenHeight + -0x8b))
			goto LAB_6faeedf0;
		bVar7 = SBORROW4(uVar6, gnScreenHeight + -0x66);
		iVar5 = uVar6 - (gnScreenHeight + -0x66);
	}
	if (bVar7 != iVar5 < 0)
	{
	LAB_6faeee4e:
		dword_6FBB5BBC = 1;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		sub_6FB57480((int)pSMSGHANDLER_PARAMS);
		if ((iVar3 == 2) && (iVar3 = sub_6FAFC0B0(), iVar3 != 0))
		{
			return;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
LAB_6faeedf0:
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAEEEA0
void __cdecl sub_6FAEEEA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2GameResolutionMode DVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	bool bVar7;

	uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	DVar1 = D2GFX_GetResolutionMode();
	if ((DVar1 == NUM_GAME_RESOLUTIONS) && (iVar2 = sub_6FB23230(9), iVar2 != 0))
	{
		return;
	}
	iVar2 = sub_6FAB5750();
	DVar1 = D2GFX_GetResolutionMode();
	if (DVar1 == NUM_GAME_RESOLUTIONS)
	{
		iVar4 = sub_6FB57BC0();
		iVar3 = sub_6FB57BD0();
		if (((iVar4 < 0x234) || (0x254 < iVar4)) || (iVar3 <= gnScreenHeight + -0x2a))
			goto LAB_6faeef0b;
		bVar7 = SBORROW4(iVar3, gnScreenHeight + -8);
		iVar3 = iVar3 - (gnScreenHeight + -8);
	}
	else
	{
		if (iVar2 != 1)
		{
			if (((gnScreenWidth + -0x49 < (int)uVar6) && ((int)uVar6 < gnScreenWidth + -0x28)) &&
			    ((gnScreenHeight + -0x8a < (int)uVar5 && ((int)uVar5 < gnScreenHeight + -0x66))))
				goto LAB_6faeef80;
			goto LAB_6faeef0b;
		}
		iVar3 = gnScreenWidth - gnScreenWidth / 2;
		if ((((int)uVar6 <= iVar3 + -0x49) || (iVar3 + -0x28 <= (int)uVar6)) ||
		    ((int)uVar5 <= gnScreenHeight + -0x8a))
			goto LAB_6faeef0b;
		bVar7 = SBORROW4(uVar5, gnScreenHeight + -0x66);
		iVar3 = uVar5 - (gnScreenHeight + -0x66);
	}
	if (bVar7 != iVar3 < 0)
	{
	LAB_6faeef80:
		dword_6FBB5BC0 = 1;
		sub_6FB55820(4, nullptr, 0.0, 0.0, 0);
		sub_6FB57480((int)pSMSGHANDLER_PARAMS);
		if ((iVar2 == 1) && (iVar2 = sub_6FAFC0B0(), iVar2 != 0))
		{
			return;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
LAB_6faeef0b:
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAEEFD0
void __cdecl sub_6FAEEFD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;

	uVar1 = (uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	DVar2 = D2GFX_GetResolutionMode();
	if ((DVar2 == NUM_GAME_RESOLUTIONS) && (iVar3 = sub_6FB23230(9), iVar3 != 0))
	{
		return;
	}
	sub_6FB57500((int)pSMSGHANDLER_PARAMS);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		if (dword_6FBB5BBC != 0)
		{
			iVar3 = sub_6FB57BC0();
			iVar4 = sub_6FB57BD0();
			if ((((0xce < iVar3) && (iVar3 < 0xf0)) && (gnScreenHeight + -0x2a < iVar4)) &&
			    (iVar4 < gnScreenHeight + -8))
			{
				dword_6FBB5BBC = 0;
				sub_6FB23260(2, 0, 0);
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
		}
	}
	else if (dword_6FBB5BBC != 0)
	{
		iVar3 = sub_6FAB5750();
		if (iVar3 == 2)
		{
			if (((int)(uint32_t)uVar1 <= gnScreenWidth / 2 + 0x28) ||
			    (gnScreenWidth / 2 + 0x4a <= (int)(uint32_t)uVar1))
				goto LAB_6faef053;
		}
		else if ((uVar1 < 0x29) || (0x49 < uVar1))
			goto LAB_6faef053;
		if ((gnScreenHeight + -0x8b < (int)uVar5) && ((int)uVar5 < gnScreenHeight + -0x66))
		{
			dword_6FBB5BBC = 0;
			sub_6FB23260(6, 1, 0);
			sub_6FB23260(2, 0, 0);
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
LAB_6faef053:
	dword_6FBB5BBC = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAEF130
void __cdecl sub_6FAEF130(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2GameResolutionMode DVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t uVar5;

	uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	DVar1 = D2GFX_GetResolutionMode();
	if ((DVar1 != NUM_GAME_RESOLUTIONS) || (iVar2 = sub_6FB23230(9), iVar2 == 0))
	{
		sub_6FB57500((int)pSMSGHANDLER_PARAMS);
		DVar1 = D2GFX_GetResolutionMode();
		if (DVar1 == NUM_GAME_RESOLUTIONS)
		{
			if (dword_6FBB5BC0 != 0)
			{
				iVar2 = sub_6FB57BC0();
				iVar3 = sub_6FB57BD0();
				if ((((0x233 < iVar2) && (iVar2 < 0x255)) && (gnScreenHeight + -0x2a < iVar3)) &&
				    (iVar3 < gnScreenHeight + -8))
				{
					dword_6FBB5BC0 = 0;
					sub_6FB23260(4, 0, 0);
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
					return;
				}
			}
		}
		else if (dword_6FBB5BC0 != 0)
		{
			iVar3 = sub_6FAB5750();
			iVar2 = gnScreenWidth;
			if (iVar3 == 1)
			{
				iVar2 = gnScreenWidth - gnScreenWidth / 2;
			}
			if (((iVar2 + -0x49 < (int)uVar5) && ((int)uVar5 < iVar2 + -0x28)) &&
			    ((gnScreenHeight + -0x8a < (int)uVar4 && ((int)uVar4 < gnScreenHeight + -0x66))))
			{
				dword_6FBB5BC0 = 0;
				sub_6FB23260(7, 1, 0);
				sub_6FB23260(4, 0, 0);
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
		}
		dword_6FBB5BC0 = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 0;
	}
}

//D2Client.0x6FAEF2A0
void __cdecl sub_6FAEF2A0()
{
	D2GameResolutionMode DVar1;
	int iVar2;
	Unicode* wszText;
	int iVar3;
	D2GfxDataStrc* pDVar4;
	int nAlign;
	D2GfxDataStrc DStack_48;

	DVar1 = D2GFX_GetResolutionMode();
	if (DVar1 == NUM_GAME_RESOLUTIONS)
	{
		pDVar4 = &DStack_48;
		for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			pDVar4->pCurrentCell = 0;
			pDVar4 = (D2GfxDataStrc*)((int)pDVar4 + 4);
		}
		DStack_48.nDirection = 0;
		DStack_48.pCellFile = gpCellFile_6FBB5BB4;
		DStack_48.nFrame = 2;
		iVar3 = sub_6FB57BC0();
		iVar2 = sub_6FB57BD0();
		if ((((0xce < iVar3) && (iVar3 < 0xf0)) && (gnScreenHeight + -0x2a < iVar2)) &&
		    (iVar2 < gnScreenHeight + -8))
		{
			iVar3 = sub_6FB23230(9);
			if (iVar3 == 0)
			{
				nAlign = 1;
				iVar2 = 0x226;
				wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
				D2Win_10129_DrawFramedText(wszText, 0xdd, iVar2, iVar3, nAlign);
			}
		}
		TEXTURE_CelDraw(&DStack_48, 0xce, gnScreenHeight + -8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
}

//D2Client.0x6FAEF360
void __cdecl sub_6FAEF360()
{
	int iVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	D2CellFileStrc* pDVar4;
	Unicode* pUVar5;
	int iVar6;
	int nY;
	int iVar7;
	D2GfxDataStrc* pDVar8;
	bool bVar9;
	int nColor;
	int bCentered;
	D2GfxDataStrc DStack_48;

	iVar1 = sub_6FAB5750();
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 != NUM_GAME_RESOLUTIONS)
	{
		if (iVar1 == 3)
		{
			dword_6FBB5BBC = 0;
			return;
		}
		iVar3 = sub_6FB23230(2);
		if (iVar3 != 0)
		{
			dword_6FBB5BBC = 0;
			return;
		}
		iVar3 = sub_6FB23230(0x16);
		if ((iVar3 != 0) && (iVar3 = sub_6FB23230(1), iVar3 != 0))
		{
			dword_6FBB5BBC = 0;
			return;
		}
		iVar3 = sub_6FB23230(0x16);
		if ((iVar3 != 0) && (iVar3 = sub_6FB23230(4), iVar3 != 0))
		{
			dword_6FBB5BBC = 0;
			return;
		}
		iVar3 = sub_6FB23230(0xc);
		if (iVar3 != 0)
		{
			dword_6FBB5BBC = 0;
			return;
		}
	}
	if (iVar1 == 2)
	{
		iVar3 = gnScreenWidth / 2 + 0x28;
	}
	else
	{
		iVar3 = 0x28;
	}
	pDVar8 = &DStack_48;
	for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar8->pCurrentCell = nullptr;
		pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
	}
	DStack_48.nDirection = 0;
	DStack_48.pCellFile = gpCellFile_6FBB5BB8;
	DStack_48.nFrame = 0;
	pDVar4 = D2CMP_CelGetHandle(&DStack_48);
	iVar7 = D2CMP_CelGetWidth(pDVar4);
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
	iVar6 = D2Win_10121_GetTextWidth(pUVar5);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 != NUM_GAME_RESOLUTIONS)
	{
		bCentered = 0;
		nY = gnScreenHeight + -0x8e;
		nColor = 0;
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
		D2Win_10117_DrawText(pUVar5, (iVar7 / 2 - iVar6 / 2) + 1 + iVar3, nY, nColor, bCentered);
		TEXTURE_CelDraw(&DStack_48, iVar3, gnScreenHeight + -0x69, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	pDVar8 = &DStack_48;
	for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar8->pCurrentCell = nullptr;
		pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
	}
	DStack_48.nDirection = 0;
	DStack_48.pCellFile = gpCellFile_6FBB5BB4;
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		if (dword_6FBB5BBC != 0)
		{
			iVar1 = sub_6FB57BC0();
			iVar7 = sub_6FB57BD0();
			if (((0xce < iVar1) && (iVar1 < 0xf0)) && (gnScreenHeight + -0x2a < iVar7))
			{
				bVar9 = SBORROW4(iVar7, gnScreenHeight + -8);
				iVar7 = iVar7 - (gnScreenHeight + -8);
			LAB_6faef5d4:
				if (bVar9 != iVar7 < 0)
					goto LAB_6faef5da;
			}
		}
	}
	else if (dword_6FBB5BBC != 0)
	{
		iVar7 = sub_6FB57BD0();
		iVar6 = sub_6FB57BC0();
		if (iVar1 == 2)
		{
			if (((gnScreenWidth / 2 + 0x28 < iVar6) && (iVar6 < gnScreenWidth / 2 + 0x4a)) &&
			    ((gnScreenHeight + -0x8b < iVar7 && (iVar7 < gnScreenHeight + -0x66))))
			{
			LAB_6faef5da:
				DStack_48.nFrame = 1;
				goto LAB_6faef522;
			}
		}
		else if (((0x28 < iVar6) && (iVar6 < 0x4a)) && (gnScreenHeight + -0x8b < iVar7))
		{
			bVar9 = SBORROW4(iVar7, gnScreenHeight + -0x66);
			iVar7 = iVar7 - (gnScreenHeight + -0x66);
			goto LAB_6faef5d4;
		}
	}
	DStack_48.nFrame = 0;
LAB_6faef522:
	pDVar4 = D2CMP_CelGetHandle(&DStack_48);
	D2CMP_CelGetWidth(pDVar4);
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
	D2Win_10121_GetTextWidth(pUVar5);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		iVar1 = sub_6FB57BC0();
		iVar3 = sub_6FB57BD0();
		if ((((0xce < iVar1) && (iVar1 < 0xf0)) && (gnScreenHeight + -0x2a < iVar3)) &&
		    ((iVar3 < gnScreenHeight + -8 && (iVar1 = sub_6FB23230(9), iVar1 == 0))))
		{
			iVar7 = 1;
			iVar3 = 0x226;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf92));
			D2Win_10129_DrawFramedText(pUVar5, 0xdd, iVar3, iVar1, iVar7);
		}
		TEXTURE_CelDraw(&DStack_48, 0xce, gnScreenHeight + -8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		return;
	}
	TEXTURE_CelDraw(&DStack_48, iVar3 + 3, gnScreenHeight + -0x6d, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FAEF670
void __cdecl sub_6FAEF670()
{
	D2GameResolutionMode DVar1;
	int iVar2;
	Unicode* wszText;
	int iVar3;
	D2GfxDataStrc* pDVar4;
	int nAlign;
	D2GfxDataStrc DStack_48;

	DVar1 = D2GFX_GetResolutionMode();
	if (DVar1 == NUM_GAME_RESOLUTIONS)
	{
		pDVar4 = &DStack_48;
		for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			pDVar4->pCurrentCell = 0;
			pDVar4 = (D2GfxDataStrc*)((int)pDVar4 + 4);
		}
		DStack_48.nDirection = 0;
		DStack_48.pCellFile = gpCellFile_6FBB5BB4;
		DStack_48.nFrame = 2;
		iVar3 = sub_6FB57BC0();
		iVar2 = sub_6FB57BD0();
		if ((((0x233 < iVar3) && (iVar3 < 0x255)) && (gnScreenHeight + -0x2a < iVar2)) &&
		    (iVar2 < gnScreenHeight + -8))
		{
			iVar3 = sub_6FB23230(9);
			if (iVar3 == 0)
			{
				nAlign = 1;
				iVar2 = 0x226;
				wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
				D2Win_10129_DrawFramedText(wszText, 0x242, iVar2, iVar3, nAlign);
			}
		}
		TEXTURE_CelDraw(&DStack_48, 0x233, gnScreenHeight + -8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
}

//D2Client.0x6FAEF730
void __cdecl sub_6FAEF730()
{
	int iVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	D2CellFileStrc* pDVar4;
	Unicode* pUVar5;
	int iVar6;
	int nY;
	int iVar7;
	D2GfxDataStrc* pDVar8;
	bool bVar9;
	int nColor;
	int bCentered;
	D2GfxDataStrc DStack_48;

	iVar1 = sub_6FAB5750();
	DVar2 = D2GFX_GetResolutionMode();
	if ((DVar2 != NUM_GAME_RESOLUTIONS) &&
	    ((((iVar1 == 3 || (iVar3 = sub_6FB23230(4), iVar3 != 0)) ||
	          (iVar3 = sub_6FB23230(0xc), iVar3 != 0)) ||
	        ((iVar3 = sub_6FB23230(0x16), iVar3 != 0 && (iVar3 = sub_6FB23230(1), iVar3 != 0))))))
	{
		dword_6FBB5BC0 = 0;
		return;
	}
	iVar3 = gnScreenWidth;
	if (iVar1 == 1)
	{
		iVar3 = gnScreenWidth - gnScreenWidth / 2;
	}
	pDVar8 = &DStack_48;
	for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar8->pCurrentCell = nullptr;
		pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
	}
	DStack_48.nDirection = 0;
	DStack_48.pCellFile = gpCellFile_6FBB5BB8;
	DStack_48.nFrame = 0;
	pDVar4 = D2CMP_CelGetHandle(&DStack_48);
	iVar7 = D2CMP_CelGetWidth(pDVar4);
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
	iVar6 = D2Win_10121_GetTextWidth(pUVar5);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 != NUM_GAME_RESOLUTIONS)
	{
		bCentered = 0;
		nY = gnScreenHeight + -0x8e;
		nColor = 0;
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
		D2Win_10117_DrawText(pUVar5, (iVar7 / 2 - iVar6 / 2) + 1 + iVar3 + -0x49, nY, nColor, bCentered);
		TEXTURE_CelDraw(&DStack_48, iVar3 + -0x49, gnScreenHeight + -0x69, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
	}
	pDVar8 = &DStack_48;
	for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar8->pCurrentCell = nullptr;
		pDVar8 = (D2GfxDataStrc*)&pDVar8->pCellFile;
	}
	DStack_48.nDirection = 0;
	DStack_48.pCellFile = gpCellFile_6FBB5BB4;
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		if (dword_6FBB5BC0 != 0)
		{
			iVar1 = sub_6FB57BC0();
			iVar7 = sub_6FB57BD0();
			if (((0x233 < iVar1) && (iVar1 < 0x255)) && (gnScreenHeight + -0x2a < iVar7))
			{
				bVar9 = SBORROW4(iVar7, gnScreenHeight + -8);
				iVar7 = iVar7 - (gnScreenHeight + -8);
			LAB_6faef9aa:
				if (bVar9 != iVar7 < 0)
					goto LAB_6faef9b0;
			}
		}
	}
	else if (dword_6FBB5BC0 != 0)
	{
		iVar7 = sub_6FB57BD0();
		iVar6 = sub_6FB57BC0();
		if (iVar1 == 1)
		{
			iVar1 = gnScreenWidth - gnScreenWidth / 2;
			if (((iVar1 + -0x49 < iVar6) && (iVar6 < iVar1 + -0x28)) && (gnScreenHeight + -0x8a < iVar7))
			{
				bVar9 = SBORROW4(iVar7, gnScreenHeight + -0x66);
				iVar7 = iVar7 - (gnScreenHeight + -0x66);
				goto LAB_6faef9aa;
			}
		}
		else if (((gnScreenWidth + -0x49 < iVar6) && (iVar6 < gnScreenWidth + -0x28)) &&
		         ((gnScreenHeight + -0x8a < iVar7 && (iVar7 < gnScreenHeight + -0x66))))
		{
		LAB_6faef9b0:
			DStack_48.nFrame = 1;
			goto LAB_6faef8d8;
		}
	}
	DStack_48.nFrame = 0;
LAB_6faef8d8:
	pDVar4 = D2CMP_CelGetHandle(&DStack_48);
	D2CMP_CelGetWidth(pDVar4);
	pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
	D2Win_10121_GetTextWidth(pUVar5);
	DVar2 = D2GFX_GetResolutionMode();
	if (DVar2 == NUM_GAME_RESOLUTIONS)
	{
		iVar1 = sub_6FB57BC0();
		iVar3 = sub_6FB57BD0();
		if (((0x233 < iVar1) && (iVar1 < 0x255)) &&
		    ((gnScreenHeight + -0x2a < iVar3 &&
		        ((iVar3 < gnScreenHeight + -8 && (iVar1 = sub_6FB23230(9), iVar1 == 0))))))
		{
			iVar7 = 1;
			iVar3 = 0x226;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf93));
			D2Win_10129_DrawFramedText(pUVar5, 0x242, iVar3, iVar1, iVar7);
		}
		TEXTURE_CelDraw(&DStack_48, 0x233, gnScreenHeight + -8, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		return;
	}
	TEXTURE_CelDraw(&DStack_48, iVar3 + -0x46, gnScreenHeight + -0x6d, 0xffffffff, DRAWMODE_NORMAL,
	    nullptr);
}

//D2Client.0x6FAEFA40
void __cdecl sub_6FAEFA40()
{
	char local_104[260];

	sprintf(local_104, "%s\\ui\\menu\\textslid", "DATA\\GLOBAL");
	gpCellFile_6FBB5BC4 = CLIENT_LoadCellFile(local_104, 0);
}

//D2Client.0x6FAEFA80
void __cdecl sub_6FAEFA80()
{
	if (gpCellFile_6FBB5BC4 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5BC4);
		gpCellFile_6FBB5BC4 = nullptr;
	}
}

//D2Client.0x6FAEFAA0
void* __fastcall sub_6FAEFAA0(void* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10, uint32_t a11)
{
	uint16_t* puVar1;
	D2GameResolutionMode DVar2;
	int iVar3;
	int iVar4;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	*(uint8_t***)a1 = &gpuint8_t_6FB6F97C;
	iVar4 = (int)a1 + 8;
	local_4 = 0;
	iVar3 = 0x80;
	do
	{
		memset((void*)(iVar4), 0, 2 * (0x400));
		memset((void*)(iVar4 + 0x800), 0, 2 * (0x400));
		memset((void*)(iVar4 + 0x1000), 0, 2 * (0x400));
		memset((void*)(iVar4 + 0x1800), 0, 2 * (0x400));
		memset((void*)(iVar4 + 0x2000), 0, 2 * (0x400));
		memset((void*)(iVar4 + 0x2800), 0, 2 * (0x400));
		iVar4 = iVar4 + 0x300e;
		iVar3 = iVar3 + -1;
	} while (iVar3 != 0);
	*(uint32_t*)((int)a1 + 0x18070c) = a4;
	*(uint32_t*)((int)a1 + 0x180710) = a5;
	*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
	*(uint32_t*)((int)a1 + 0x180738) = 0xffffffff;
	*(uint32_t*)((int)a1 + 0x180708) = a3;
	*(uint32_t*)((int)a1 + 0x180740) = a8;
	*(uint32_t*)((int)a1 + 0x180744) = a9;
	*(uint8_t***)a1 = &gpuint8_t_6FB6F9B0;
	*(uint32_t*)((int)a1 + 0x180714) = a6;
	*(uint32_t*)((int)a1 + 0x18071c) = 0;
	*(uint32_t*)((int)a1 + 0x180728) = 0;
	*(uint32_t*)((int)a1 + 0x180720) = 0;
	*(uint32_t*)((int)a1 + 0x180724) = 0;
	*(uint32_t*)((int)a1 + 0x180772) = 0;
	*(uint32_t*)((int)a1 + 0x180730) = 0;
	*(uint16_t*)((int)a1 + 0x180748) = 0;
	puVar1 = (uint16_t*)((int)a1 + 0x808);
	iVar4 = 0x80;
	do
	{
		puVar1[-0x400] = 0;
		*puVar1 = 0;
		puVar1[0x400] = 0;
		puVar1[0x800] = 0;
		puVar1[0xc00] = 0;
		puVar1[0x1000] = 0;
		puVar1[0x1400] = 0;
		*(uint32_t*)(puVar1 + 0x1403) = 0;
		*(uint32_t*)(puVar1 + 0x1405) = 1;
		*(uint32_t*)(puVar1 + 0x1401) = 0;
		puVar1 = puVar1 + 0x1807;
		iVar4 = iVar4 + -1;
	} while (iVar4 != 0);
	*(uint32_t*)((int)a1 + 0x18074a) = a10;
	*(uint32_t*)((int)a1 + 0x18076a) = a7;
	*(uint32_t*)((int)a1 + 0x180766) = 0xe;
	*(int*)((int)a1 + 0x18075a) =
	    *(int*)((int)a1 + 0x180708) + -0x12 + *(int*)((int)a1 + 0x180710);
	*(int*)((int)a1 + 0x18075e) = *(int*)((int)a1 + 0x18070c) + 0x10;
	if (*(int*)((int)a1 + 0x180714) < 0x20)
	{
		*(uint32_t*)((int)a1 + 0x180762) = 1;
	}
	else
	{
		*(int*)((int)a1 + 0x180762) = (*(int*)((int)a1 + 0x180714) + -0x10) / 0xc + -1;
	}
	*(uint32_t*)((int)a1 + 0x18074e) = 1;
	DVar2 = D2GFX_GetResolutionMode();
	if ((DVar2 == NUM_GAME_RESOLUTIONS) && ((char)a11 != '\0'))
	{
		*(uint32_t*)((int)a1 + 0x180718) = 0x1c;
	}
	else
	{
		*(uint32_t*)((int)a1 + 0x180718) = 0x12;
	}
	return a1;
}

//D2Client.0x6FAEFD00
void* __fastcall sub_6FAEFD00(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAEFD30((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAEFD30
void __fastcall sub_6FAEFD30(uint32_t* a1)
{
	*a1 = (uint32_t)(&gpuint8_t_6FB6F97C);
}

//D2Client.0x6FAEFD40
uint16_t __fastcall sub_6FAEFD40(int a1)
{
	return *(uint16_t*)(a1 + 0x180748);
}

//D2Client.0x6FAEFD50
void __fastcall sub_6FAEFD50(int a1)
{
	uint16_t* puVar1;
	int iVar2;

	iVar2 = 0;
	if (*(short*)(a1 + 0x180748) != 0)
	{
		puVar1 = (uint16_t*)(a1 + 0x808);
		do
		{
			puVar1[-0x400] = 0;
			*puVar1 = 0;
			puVar1[0x400] = 0;
			puVar1[0x800] = 0;
			puVar1[0xc00] = 0;
			puVar1[0x1000] = 0;
			iVar2 = iVar2 + 1;
			puVar1 = puVar1 + 0x1807;
		} while (iVar2 < (int)(uint32_t) * (uint16_t*)(a1 + 0x180748));
	}
	*(uint16_t*)(a1 + 0x180748) = 0;
}

//D2Client.0x6FAEFDB0
void __fastcall sub_6FAEFDB0(int a1)
{
	short* psVar1;
	int iVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t uVar5;
	int iVar6;
	D2GfxDataStrc* pDVar7;
	uint32_t local_58;
	int iStack_54;
	D2GfxDataStrc local_48;

	iVar2 = 0;
	iVar6 = *(int*)(a1 + 0x180730);
	uVar5 = (uint32_t) * (uint16_t*)(a1 + 0x180748);
	*(uint32_t*)(a1 + 0x180752) = 0;
	*(uint32_t*)(a1 + 0x180756) = 0;
	*(uint32_t*)(a1 + 0x18074e) = 0;
	if (iVar6 < (int)uVar5)
	{
		psVar1 = (short*)(a1 + 0x808 + iVar6 * 0x300e);
		iVar4 = uVar5 - iVar6;
		do
		{
			if (psVar1[-0x400] != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			if (*psVar1 != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			if (psVar1[0x400] != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			if (psVar1[0x800] != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			if (psVar1[0xc00] != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			if (psVar1[0x1000] != 0)
			{
				iVar2 = iVar2 + *(int*)(a1 + 0x180766);
			}
			iVar2 = iVar2 + *(int*)(a1 + 0x18076a);
			if (iVar2 < *(int*)(a1 + 0x180714) + -0x14)
			{
				*(int*)(a1 + 0x18074e) = *(int*)(a1 + 0x18074e) + 1;
			}
			psVar1 = psVar1 + 0x1807;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
	}
	iVar2 = *(int*)(a1 + 0x18074e);
	if ((int)uVar5 <= iVar2)
	{
		return;
	}
	iVar4 = (iVar2 << 7) / (int)uVar5;
	if (iVar6 == 0)
	{
		uVar3 = (uint32_t)(*(int*)(a1 + 0x180718) * iVar4) >> 7;
		uVar5 = 0;
	}
	else if (iVar6 < (int)(uVar5 - iVar2))
	{
		local_58 = *(uint32_t*)(a1 + 0x180718);
		uVar5 = (int)(local_58 * iVar6) / (int)uVar5;
		uVar5 = ((int)uVar5 < 0) - 1 & uVar5;
		uVar3 = (local_58 * iVar4 >> 7) + uVar5;
		if ((int)local_58 < (int)uVar3)
			goto LAB_6faefefe;
	}
	else
	{
		uVar3 = *(uint32_t*)(a1 + 0x180718);
		uVar5 = uVar3 - (uVar3 * iVar4 >> 7);
		if ((int)uVar3 < (int)uVar5)
		{
			uVar5 = uVar3;
		}
	}
	local_58 = uVar3;
LAB_6faefefe:
	iVar6 = *(int*)(a1 + 0x18075a);
	iVar4 = *(int*)(a1 + 0x18075e) + 0xd;
	pDVar7 = &local_48;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	iVar6 = iVar6 + -1;
	local_48.pCellFile = gpCellFile_6FBB5BC4;
	local_48.nDirection = 0;
	local_48.nFrame = 0x10;
	TEXTURE_CelDraw(&local_48, iVar6, iVar4 + uVar5 * 0xc, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 0xe;
	uVar3 = uVar5;
	if ((int)uVar5 < (int)local_58)
	{
		iVar2 = local_58 - uVar5;
		iStack_54 = iVar4 + (uVar5 * 3 + 3) * 4;
		uVar3 = iVar2 + uVar5;
		do
		{
			TEXTURE_CelDraw(&local_48, iVar6, iStack_54, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			iStack_54 = iStack_54 + 0xc;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
	}
	local_48.nFrame = 0xf;
	TEXTURE_CelDraw(&local_48, iVar6, iVar4 + (uVar3 * 3 + 3) * 4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	*(uint32_t*)(a1 + 0x180752) = uVar5;
	*(uint32_t*)(a1 + 0x180756) = local_58;
}

//D2Client.0x6FAEFFE0
// TODO: decompilation needs review (unaff_)
uint32_t __fastcall sub_6FAEFFE0(int a1)
{
	int iVar1;
	int iVar2;
	short* psVar3;
	uint32_t unaff_EDI;
	uint32_t uVar4;

	iVar2 = 0;
	uVar4 = (uint32_t) * (uint16_t*)(a1 + 0x180748);
	iVar1 = 0;
	if (uVar4 != 0)
	{
		psVar3 = (short*)(a1 + 0x808);
		do
		{
			if ((*(int*)(a1 + 0x180730) <= iVar1) && (iVar1 < (int)uVar4))
			{
				if (psVar3[-0x400] != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				if (*psVar3 != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				if (psVar3[0x400] != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				if (psVar3[0x800] != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				if (psVar3[0xc00] != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				if (psVar3[0x1000] != 0)
				{
					iVar2 = iVar2 + *(int*)(a1 + 0x180766);
				}
				iVar2 = iVar2 + *(int*)(a1 + 0x18076a);
			}
			if (*(int*)(a1 + 0x180714) + -0x14 < iVar2)
			{
				if (0 < iVar1 - *(int*)(a1 + 0x180730))
				{
					return unaff_EDI;
				}
				return unaff_EDI;
			}
			iVar1 = iVar1 + 1;
			psVar3 = psVar3 + 0x1807;
		} while (iVar1 < (int)uVar4);
	}
	return unaff_EDI;
}

//D2Client.0x6FAF00A0
void __fastcall sub_6FAF00A0(void* a1, uint32_t a2, Unicode* pUnicode, int a4, int a5, int a6)
{
	int iVar1;
	Unicode* pThis;
	Unicode local_800[1024];

	Unicode::strcpy(local_800, pUnicode);
	iVar1 = Unicode::strlen(local_800);
	iVar1 = D2Win_10123(local_800, iVar1);
	if (*(int*)((int)a1 + 0x180710) + -0x32 <= iVar1)
	{
		iVar1 = Unicode::strlen(local_800);
		iVar1 = D2Win_10123(local_800, iVar1);
		if (*(int*)((int)a1 + 0x180710) + -0x32 < iVar1)
		{
			do
			{
				iVar1 = Unicode::strlen(local_800);
				local_800[iVar1 + -1].ch = 0;
				iVar1 = Unicode::strlen(local_800);
				iVar1 = D2Win_10123(local_800, iVar1);
			} while (*(int*)((int)a1 + 0x180710) + -0x32 < iVar1);
		}
	}
	D2Win_10117_DrawText(local_800, a4, a5, a6, 0);
}

//D2Client.0x6FAF0190
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF0190(int* a1)
{
	Font nFontSize;
	int extraout_EAX;
	uint32_t uVar1;
	uint32_t uVar2;
	int iVar3;
	Font nFontSize_00;
	Font* pFVar4;
	int iVar5;
	Font FVar6;
	D2GfxDataStrc* pDVar7;
	uint32_t uVar8;
	Font FStack_84;
	int local_78;
	int local_74;
	int local_70;
	int local_6c;
	uint8_t auStack_68[12];
	uint16_t uStack_5c;
	uint16_t uStack_5a;
	D2GfxDataStrc DStack_48;

	local_78 = a1[0x601c2];
	local_74 = a1[0x601c3];
	local_70 = a1[0x601c4] + -1 + local_78;
	local_6c = a1[0x601c5] + -1 + local_74;
	sub_6FB21790(&local_78);
	nFontSize = D2Win_10127_SetFont((Font)(a1[0x601d1]));
	iVar5 = a1[0x601c8];
	pDVar7 = &DStack_48;
	for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		pDVar7->pCurrentCell = nullptr;
		pDVar7 = (D2GfxDataStrc*)&pDVar7->pCellFile;
	}
	iVar3 = 0;
	DStack_48.pCellFile = gpCellFile_6FBB5BC4;
	DStack_48.nFrame = (uint32_t)(iVar5 != 0) * 2 + 9;
	DStack_48.nDirection = 0;
	TEXTURE_CelDraw(&DStack_48, *(int*)((int)a1 + 0x18075a), *(int*)((int)a1 + 0x18075e),
	    0xffffffff, DRAWMODE_NORMAL, nullptr);
	if (0 < *(int*)((int)a1 + 0x180762))
	{
		iVar5 = 0xc;
		do
		{
			DStack_48.nFrame = 0xd;
			TEXTURE_CelDraw(&DStack_48, *(int*)((int)a1 + 0x18075a),
			    *(int*)((int)a1 + 0x18075e) + iVar5, 0xffffffff, DRAWMODE_NORMAL,
			    nullptr);
			iVar3 = iVar3 + 1;
			iVar5 = iVar5 + 0xc;
		} while (iVar3 < *(int*)((int)a1 + 0x180762));
	}
	DStack_48.nFrame = (uint32_t)(a1[0x601c9] != 0) * 2 + 8;
	TEXTURE_CelDraw(&DStack_48, *(int*)((int)a1 + 0x18075a),
	    *(int*)((int)a1 + 0x18075e) + iVar3 * 0xc, 0xffffffff, DRAWMODE_NORMAL,
	    nullptr);
	uVar8 = sub_6FAEFFE0((int)a1);
	FStack_84 = (Font)(a1[0x601cc]);
	iVar5 = 0;
	if ((int)FStack_84 < (int)(extraout_EAX + FStack_84))
	{
		pFVar4 = (Font*)((int)a1 + FStack_84 * 0x300e + 0x3012);
		do
		{
			if (0x7f < (int)FStack_84)
				break;
			if ((a1[0x601ce] != FStack_84) ||
			    (FVar6 = D2FONT_FONT42, *(int*)((int)a1 + 0x18074a) == 0))
			{
				FVar6 = pFVar4[-1];
			}
			nFontSize_00 = *pFVar4;
			if (nFontSize_00 == NUM_FONTS)
			{
				nFontSize_00 = (Font)(a1[0x601d1]);
			}
			D2Win_10127_SetFont(nFontSize_00);
			if (*(short*)((int)pFVar4 + -0x300a) != 0)
			{
				iVar3 = *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3];
				sub_6FAF00A0(a1, iVar3, (Unicode*)((uint8_t*)((int)pFVar4 + -0x300a)), a1[0x601c2] + 0x20, iVar3,
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			if (*(short*)((int)pFVar4 + -0x280a) != 0)
			{
				sub_6FAF00A0(a1, a1[0x601c2] + 0x20, (Unicode*)((uint8_t*)((int)pFVar4 + -0x280a)),
				    a1[0x601c2] + 0x20,
				    *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3],
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			if (*(short*)((int)pFVar4 + -0x200a) != 0)
			{
				sub_6FAF00A0(a1, a1[0x601c2] + 0x20, (Unicode*)((uint8_t*)((int)pFVar4 + -0x200a)),
				    a1[0x601c2] + 0x20,
				    *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3],
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			if (*(short*)((int)pFVar4 + -0x180a) != 0)
			{
				sub_6FAF00A0(a1, a1[0x601c2] + 0x20, (Unicode*)((uint8_t*)((int)pFVar4 + -0x180a)),
				    a1[0x601c2] + 0x20,
				    *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3],
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			if (*(short*)((int)pFVar4 + -0x100a) != 0)
			{
				sub_6FAF00A0(a1, a1[0x601c2] + 0x20, (Unicode*)((uint8_t*)((int)pFVar4 + -0x100a)),
				    a1[0x601c2] + 0x20,
				    *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3],
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			if (*(short*)((int)pFVar4 + -0x80a) != 0)
			{
				sub_6FAF00A0(a1, a1[0x601c2] + 0x20, (Unicode*)((uint8_t*)((int)pFVar4 + -0x80a)),
				    a1[0x601c2] + 0x20,
				    *(int*)((int)a1 + 0x18076a) * iVar5 +
				        *(int*)((int)a1 + 0x180766) * uVar8 + 0x19 + a1[0x601c3],
				    FVar6);
				uVar8 = uVar8 + 1;
			}
			pFVar4 = (Font*)((int)pFVar4 + 0x300e);
			iVar5 = iVar5 + 1;
			FStack_84 = (Font)(FStack_84 + D2FONT_FONT16);
		} while ((int)FStack_84 < a1[0x601cc] + extraout_EAX);
	}
	(**(code**)(*a1 + 0x30))();
	*(int*)((int)a1 + 0x180772) = *(int*)((int)a1 + 0x180772) + 1;
	uVar8 = sub_6FB57BD0();
	uVar1 = sub_6FB57BC0();
	iVar5 = *(int*)((int)a1 + 0x18075a);
	uVar2 = uVar1 & 0xffff;
	uStack_5c = (uint16_t)uVar1;
	uStack_5a = (uint16_t)uVar8;
	uVar8 = uVar8 & 0xffff;
	if (iVar5 < (int)uVar2)
	{
		if (((((int)uVar2 < iVar5 + 0x10) && (*(int*)((int)a1 + 0x18075e) + -0xc < (int)uVar8)) &&
		        ((int)uVar8 < *(int*)((int)a1 + 0x18075e))) &&
		    (a1[0x601c8] == 1))
		{
			uVar8 = *(int*)((int)a1 + 0x18076e) + 1;
			*(uint32_t*)((int)a1 + 0x18076e) = uVar8;
			if ((uVar8 != 0) && (uVar8 % 10 != 0))
			{
				(**(code**)(*a1 + 0x1c))(auStack_68);
				D2Win_10127_SetFont(FStack_84);
				return;
			}
		}
		else if (((iVar5 < (int)uVar2) && ((int)uVar2 < iVar5 + 0x10)) &&
		         ((iVar5 = *(int*)((int)a1 + 0x18075e) + *(int*)((int)a1 + 0x180762) * 0xc,
		             iVar5 + -0xc < (int)uVar8 && (((int)uVar8 < iVar5 && (a1[0x601c9] == 1))))))
		{
			uVar8 = *(int*)((int)a1 + 0x18076e) + 1;
			*(uint32_t*)((int)a1 + 0x18076e) = uVar8;
			if ((uVar8 != 0) && (uVar8 % 10 != 0))
			{
				(**(code**)(*a1 + 0x20))(auStack_68);
			}
		}
	}
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FAF0610
void __fastcall sub_6FAF0610(void* a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, uint32_t a9, int a10, int a11, uint32_t a12)
{
	uint16_t uVar1;

	if (*(uint16_t*)((int)a1 + 0x180748) < 0x80)
	{
		*(uint32_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x300a) =
		    a9;
		if (*(int*)((int)a1 + 0x180738) == -1)
		{
			*(uint32_t*)((int)a1 + 0x180738) = 0;
		}
		if (a3 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 8),
			    (Unicode*)a3, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x806) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a4 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x808),
			    (Unicode*)a4, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x1006) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a5 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x1008), (Unicode*)a5, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x1806) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a6 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x1808), (Unicode*)a6, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x2006) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a7 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x2008), (Unicode*)a7, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x2806) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a8 != 0)
		{
			Unicode::strncpy((Unicode*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x2808), (Unicode*)a8, 0x3ff);
			*(uint16_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x3006) =
			    0;
			*(int*)((int)a1 + 0x18073c) = *(int*)((int)a1 + 0x18073c) + 1;
		}
		if (a11 == 0)
		{
			uVar1 = *(uint16_t*)((int)a1 + 0x180748);
		}
		else
		{
			uVar1 = *(uint16_t*)((int)a1 + 0x180748);
			a10 = *(int*)((int)a1 + 0x180740);
		}
		*(int*)((int)a1 + (uVar1 + 1) * 0x300e) = a10;
		*(uint32_t*)((int)a1 + (uint32_t) * (uint16_t*)((int)a1 + 0x180748) * 0x300e + 0x3012) =
		    a12;
		*(short*)((int)a1 + 0x180748) = *(short*)((int)a1 + 0x180748) + 1;
	}
}

//D2Client.0x6FAF08E0
uint32_t __fastcall sub_6FAF08E0(void* a1, int a2, int a3)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;

	uVar3 = (uint32_t) * (uint16_t*)(a3 + 0xe);
	uVar4 = *(uint32_t*)((int)a1 + 0x18075e);
	if (*(uint16_t*)((int)a1 + 0x180748) != 0)
	{
		iVar1 = *(int*)((int)a1 + 0x18074e);
		uVar2 = (uint32_t) * (uint16_t*)((int)a1 + 0x180748);
		if ((iVar1 <= (int)uVar2) && (uVar3 != uVar4 && -1 < (int)(uVar3 - uVar4)))
		{
			if (*(int*)((int)a1 + 0x180752) != *(int*)((int)a1 + 0x180756))
			{
				if ((int)uVar3 < (int)(uVar4 + 0xd + *(int*)((int)a1 + 0x180752) * 0xc))
				{
					uVar4 = *(int*)((int)a1 + 0x180738) - iVar1;
					*(uint32_t*)((int)a1 + 0x180738) = ((int)uVar4 < 1) - 1 & uVar4;
				}
				else
				{
					if ((int)uVar3 <= (int)(uVar4 + 0xd + *(int*)((int)a1 + 0x180756) * 0xc))
					{
						return 0;
					}
					iVar5 = *(int*)((int)a1 + 0x180738) + iVar1;
					if ((int)uVar2 <= iVar5)
					{
						iVar5 = uVar2 - 1;
					}
					*(int*)((int)a1 + 0x180738) = iVar5;
					if ((int)(uVar2 - *(int*)((int)a1 + 0x180738)) < iVar1)
					{
						if ((int)uVar2 < iVar1)
						{
							*(uint32_t*)((int)a1 + 0x180738) = 0;
						}
						else
						{
							*(uint32_t*)((int)a1 + 0x180738) = uVar2 - iVar1;
						}
					}
				}
				if (0x7f < *(int*)((int)a1 + 0x180738))
				{
					uVar2 = uVar2 - 1;
					*(uint32_t*)((int)a1 + 0x180738) = uVar2;
					*(uint32_t*)((int)a1 + 0x180738) = uVar2 & ((int)uVar2 < 0) - 1;
				}
				*(uint32_t*)((int)a1 + 0x180730) = *(uint32_t*)((int)a1 + 0x180738);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				iVar1 = *(int*)((int)a1 + 0x180738);
				if (iVar1 < *(int*)((int)a1 + 0x180730))
				{
					*(int*)((int)a1 + 0x180730) = iVar1;
				}
				if (*(int*)((int)a1 + 0x18074e) + *(int*)((int)a1 + 0x180730) <= iVar1)
				{
					*(int*)((int)a1 + 0x180730) = *(int*)((int)a1 + 0x180730) + 1;
				}
				return 1;
			}
		}
	}
	return 0;
}

//D2Client.0x6FAF0A30
uint32_t __fastcall sub_6FAF0A30(void* a1, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS2)
{
	short sVar1;

	sVar1 = *(short*)((int)&pSMSGHANDLER_PARAMS2->wParam + 2);
	if (sVar1 < 1)
	{
		if (sVar1 < 0)
		{
			*(int*)((int)a1 + 0x180738) =
			    *(int*)((int)a1 + 0x18074e) + -1 + *(int*)((int)a1 + 0x180730);
			(**(code**)(*(uint32_t*)(a1) + 0x20))(pSMSGHANDLER_PARAMS2);
		}
	}
	else
	{
		*(uint32_t*)((int)a1 + 0x180738) = *(uint32_t*)((int)a1 + 0x180730);
		(**(code**)(*(uint32_t*)(a1) + 0x1c))(pSMSGHANDLER_PARAMS2);
	}
	pSMSGHANDLER_PARAMS2->bUseResult = 1;
	pSMSGHANDLER_PARAMS2->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS2);
	return 1;
}

//D2Client.0x6FAF0A90
uint32_t __fastcall sub_6FAF0A90(void* a1, int a2, int a3)
{
	int iVar1;
	uint32_t uVar2;
	uint32_t uVar3;
	int iVar4;

	if ((((*(int*)((int)a1 + 0x180708) < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
	         ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) <
	             *(int*)((int)a1 + 0x180710) + *(int*)((int)a1 + 0x180708))) &&
	        (*(int*)((int)a1 + 0x18070c) < (int)(uint32_t) * (uint16_t*)(a3 + 0xe))) &&
	    ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) <
	        *(int*)((int)a1 + 0x180714) + *(int*)((int)a1 + 0x18070c)))
	{
		iVar4 = *(int*)((int)a1 + 0x18075a);
		*(uint32_t*)((int)a1 + 0x18071c) = 1;
		uVar3 = (uint32_t) * (uint16_t*)(a3 + 0xc);
		uVar2 = (uint32_t) * (uint16_t*)(a3 + 0xe);
		if (iVar4 < (int)uVar3)
		{
			if ((((int)uVar3 < iVar4 + 0x10) && (*(int*)((int)a1 + 0x18075e) + -0xc < (int)uVar2)) && ((int)uVar2 < *(int*)((int)a1 + 0x18075e)))
			{
				*(uint32_t*)((int)a1 + 0x180720) = 1;
				*(uint32_t*)((int)a1 + 0x18076e) = 0;
				return 1;
			}
			if (iVar4 < (int)uVar3)
			{
				if ((((int)uVar3 < iVar4 + 0x10) &&
				        (iVar1 = *(int*)((int)a1 + 0x18075e) + *(int*)((int)a1 + 0x180762) * 0xc,
				            iVar1 + -0xc < (int)uVar2)) &&
				    ((int)uVar2 < iVar1))
				{
					*(uint32_t*)((int)a1 + 0x180724) = 1;
					*(uint32_t*)((int)a1 + 0x18076e) = 0;
					return 1;
				}
				if ((((iVar4 < (int)uVar3) && (iVar4 = iVar4 + 0x10, (int)uVar3 < iVar4)) &&
				        (iVar4 = *(int*)((int)a1 + 0x18075e),
				            (int)uVar2 < iVar4 + -0xc + *(int*)((int)a1 + 0x180762) * 0xc)) &&
				    (iVar4 < (int)uVar2))
				{
					*(uint32_t*)((int)a1 + 0x18072c) = uVar2;
					*(uint32_t*)((int)a1 + 0x180728) = 1;
					return 1;
				}
			}
		}
		if (*(int*)((int)a1 + 0x18074a) != 0)
		{
			iVar4 = sub_6FAF0ED0(a1, iVar4, a3);
			*(int*)((int)a1 + 0x180734) = iVar4;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAF0BF0
uint32_t __fastcall sub_6FAF0BF0(void* a1, int a2, int a3)
{
	int iVar1;

	if (*(int*)((int)a1 + 0x18071c) == 0)
	{
		*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
		return 1;
	}
	*(uint32_t*)((int)a1 + 0x18071c) = 0;
	if (*(int*)((int)a1 + 0x180720) == 1)
	{
		*(uint32_t*)((int)a1 + 0x180720) = 0;
		if (((*(int*)((int)a1 + 0x18075a) < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
		        ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) < *(int*)((int)a1 + 0x18075a) + 0x10)) &&
		    ((*(int*)((int)a1 + 0x18075e) + -0xc < (int)(uint32_t) * (uint16_t*)(a3 + 0xe) &&
		        ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) < *(int*)((int)a1 + 0x18075e)))))
		{
			(**(code**)(*(uint32_t*)(a1) + 0x1c))(a3);
		}
	}
	else if (*(int*)((int)a1 + 0x180724) == 1)
	{
		*(uint32_t*)((int)a1 + 0x180724) = 0;
		if (((*(int*)((int)a1 + 0x18075a) < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
		        ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) < *(int*)((int)a1 + 0x18075a) + 0x10)) &&
		    ((iVar1 = *(int*)((int)a1 + 0x18075e) + *(int*)((int)a1 + 0x180762) * 0xc,
		        iVar1 + -0xc < (int)(uint32_t) * (uint16_t*)(a3 + 0xe) &&
		            ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) < iVar1))))
		{
			(**(code**)(*(uint32_t*)(a1) + 0x20))(a3);
			*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
			return 0;
		}
	}
	else
	{
		if (*(int*)((int)a1 + 0x180728) != 1)
		{
			if (*(int*)((int)a1 + 0x18074a) == 0)
			{
				return 0;
			}
			iVar1 = sub_6FAF0ED0(a1, a2, a3);
			if (*(int*)((int)a1 + 0x180734) != iVar1)
			{
				return 0;
			}
			if (*(int*)((int)a1 + 0x180734) == -1)
			{
				return 0;
			}
			*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
			(**(code**)((int)a1 + 0x18074a))();
			return 1;
		}
		*(uint32_t*)((int)a1 + 0x180728) = 0;
		if ((((*(int*)((int)a1 + 0x18075a) < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
		         ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) < *(int*)((int)a1 + 0x18075a) + 0x10)) &&
		        (iVar1 = *(int*)((int)a1 + 0x18075e),
		            (int)(uint32_t) * (uint16_t*)(a3 + 0xe) <
		                iVar1 + -0xc + *(int*)((int)a1 + 0x180762) * 0xc)) &&
		    (iVar1 < (int)(uint32_t) * (uint16_t*)(a3 + 0xe)))
		{
			sub_6FAF08E0(a1, iVar1, a3);
			*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
			return 0;
		}
	}
	*(uint32_t*)((int)a1 + 0x180734) = 0xffffffff;
	return 0;
}

//D2Client.0x6FAF0DA0
uint32_t __fastcall sub_6FAF0DA0(int a1, uint32_t a2, uint32_t a3)
{
	int iVar1;

	if (*(int*)(a1 + 0x18074a) == 0)
	{
		*(uint32_t*)(a1 + 0x180738) = *(uint32_t*)(a1 + 0x180730);
	}
	if (0 < *(int*)(a1 + 0x180738))
	{
		*(int*)(a1 + 0x180738) = *(int*)(a1 + 0x180738) + -1;
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		iVar1 = *(int*)(a1 + 0x180738);
		if (iVar1 < *(int*)(a1 + 0x180730))
		{
			*(int*)(a1 + 0x180730) = iVar1;
		}
		if (*(int*)(a1 + 0x18074e) + *(int*)(a1 + 0x180730) <= iVar1)
		{
			*(int*)(a1 + 0x180730) = *(int*)(a1 + 0x180730) + 1;
			return 1;
		}
	}
	return 1;
}

//D2Client.0x6FAF0E20
uint32_t __fastcall sub_6FAF0E20(int a1, uint32_t a2, uint32_t a3)
{
	int iVar1;

	if (*(int*)(a1 + 0x18074a) == 0)
	{
		iVar1 = *(int*)(a1 + 0x18074e) + -1 + *(int*)(a1 + 0x180730);
		*(int*)(a1 + 0x180738) = iVar1;
		if ((int)(uint32_t) * (uint16_t*)(a1 + 0x180748) <= iVar1)
		{
			*(uint32_t*)(a1 + 0x180738) = *(uint16_t*)(a1 + 0x180748) - 1;
		}
	}
	if (*(int*)(a1 + 0x180738) < (int)(*(uint16_t*)(a1 + 0x180748) - 1))
	{
		*(int*)(a1 + 0x180738) = *(int*)(a1 + 0x180738) + 1;
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		if (*(int*)(a1 + 0x180738) < *(int*)(a1 + 0x180730))
		{
			*(int*)(a1 + 0x180730) = *(int*)(a1 + 0x180738);
		}
		if (*(int*)(a1 + 0x18074e) + *(int*)(a1 + 0x180730) <= *(int*)(a1 + 0x180738))
		{
			*(int*)(a1 + 0x180730) = *(int*)(a1 + 0x180730) + 1;
		}
	}
	return 1;
}

//D2Client.0x6FAF0ED0
int __fastcall sub_6FAF0ED0(void* a1, int a2, int a3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	short* psVar4;

	if ((*(int*)((int)a1 + 0x18075a) + -0xf < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) ||
	    (*(int*)((int)a1 + 0x18074a) == 0))
	{
		return -1;
	}
	iVar1 = *(int*)((int)a1 + 0x180730);
	iVar2 = 0;
	if (iVar1 < (int)(uint32_t) * (uint16_t*)((int)a1 + 0x180748))
	{
		psVar4 = (short*)((int)a1 + iVar1 * 0x300e + 0x808);
		do
		{
			iVar3 = iVar2;
			if (psVar4[-0x400] != 0)
			{
				iVar3 = iVar2 + *(int*)((int)a1 + 0x180766);
			}
			if (*psVar4 != 0)
			{
				iVar3 = iVar3 + *(int*)((int)a1 + 0x180766);
			}
			if (psVar4[0x400] != 0)
			{
				iVar3 = iVar3 + *(int*)((int)a1 + 0x180766);
			}
			if (psVar4[0x800] != 0)
			{
				iVar3 = iVar3 + *(int*)((int)a1 + 0x180766);
			}
			if (psVar4[0xc00] != 0)
			{
				iVar3 = iVar3 + *(int*)((int)a1 + 0x180766);
			}
			if (psVar4[0x1000] != 0)
			{
				iVar3 = iVar3 + *(int*)((int)a1 + 0x180766);
			}
			if ((*(int*)((int)a1 + 0x18070c) + 0xc + iVar2 < (int)(uint32_t) * (uint16_t*)(a3 + 0xe)) && ((int)(uint32_t) * (uint16_t*)(a3 + 0xe) < *(int*)((int)a1 + 0x18070c) + 0xc + iVar3))
				goto LAB_6faf0fcc;
			psVar4 = psVar4 + 0x1807;
			iVar2 = iVar3 + *(int*)((int)a1 + 0x18076a);
			iVar1 = iVar1 + 1;
		} while (iVar1 < (int)(uint32_t) * (uint16_t*)((int)a1 + 0x180748));
	}
	iVar1 = -1;
LAB_6faf0fcc:
	*(int*)((int)a1 + 0x180738) = iVar1;
	return iVar1;
}

//D2Client.0x6FAF0FF0
uint32_t __fastcall sub_6FAF0FF0(void* a1, int a2, int a3)
{
	uint32_t uVar1;

	uVar1 = (uint32_t) * (uint16_t*)(a3 + 0xe);
	if ((((*(int*)((int)a1 + 0x180708) < (int)(uint32_t) * (uint16_t*)(a3 + 0xc)) &&
	         ((int)(uint32_t) * (uint16_t*)(a3 + 0xc) <
	             *(int*)((int)a1 + 0x180710) + *(int*)((int)a1 + 0x180708))) &&
	        (*(int*)((int)a1 + 0x18070c) < (int)uVar1)) &&
	    ((int)uVar1 < *(int*)((int)a1 + 0x180714) + *(int*)((int)a1 + 0x18070c)))
	{
		sub_6FAF0ED0(a1, uVar1, a3);
	}
	return 0;
}

//D2Client.0x6FAF1040
uint32_t __fastcall sub_6FAF1040(void* a1, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS, SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS2)
{
	if (*(int*)((int)a1 + 0x18074a) != 0)
	{
		pSMSGHANDLER_PARAMS2->bUseResult = 1;
		pSMSGHANDLER_PARAMS2->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS2);
		if (1 < *(uint32_t*)((int)a1 + 0x180772))
		{
			if ((*(int*)((int)a1 + 0x180738) != -1) && (pSMSGHANDLER_PARAMS2->wParam == 0xd))
			{
				(**(code**)((int)a1 + 0x18074a))();
			}
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAF10A0
uint32_t __fastcall sub_6FAF10A0(int a1)
{
	return *(uint32_t*)(a1 + 0x180738);
}

//D2Client.0x6FAF10B0
void __fastcall sub_6FAF10B0(uint32_t* a1)
{
	void* local_c;
	code* pcStack_8;
	uint32_t local_4;

	*a1 = (uint32_t)(&gpuint8_t_6FB6F9F0);
	local_4 = 0;
	if ((uint32_t*)a1[2] != nullptr)
	{
		(*(code*)**(uint32_t**)a1[2])(1);
	}
	*a1 = (uint32_t)(&gpuint8_t_6FB6F97C);
}

//D2Client.0x6FAF1100
void* __fastcall sub_6FAF1100(void* a1, uint32_t a2, uint32_t a3)
{
	sub_6FAF10B0((uint32_t*)a1);
	if (((a3 & 1) != 0) && (a1 != nullptr))
	{
		SMemFree(a1, "delete", -1, 0);
	}
	return a1;
}

//D2Client.0x6FAF1130
void* __fastcall sub_6FAF1130(void* a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10, uint32_t a11)
{
	void* pvVar1;
	void* pvStack_c;
	code* pcStack_8;
	uint32_t local_4;

	local_4 = 0;
	*(uint8_t***)a1 = &gpuint8_t_6FB6F9F0;
	pvVar1 = SMemAlloc(0x180776, "new", -1, 0);
	local_4 = CONCAT31((*(uint8_t*)((uint8_t*)&local_4 + 1)), 1);
	if (pvVar1 == nullptr)
	{
		pvVar1 = nullptr;
	}
	else
	{
		pvVar1 = sub_6FAEFAA0(pvVar1, a4, a3, a4, a5, a6, a7, a8, a9,
		    a10, a11);
	}
	*(void**)((int)a1 + 8) = pvVar1;
	return a1;
}

//D2Client.0x6FAF11D0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAF11D0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 4))();
}

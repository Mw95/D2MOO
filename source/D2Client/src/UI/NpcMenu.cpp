#include "UI/NpcMenu.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/PalShift.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Game/View.h"
#include "Sound/SoundInst.h"
#include "UI/CmdTbl.h"
#include "UI/Dialog.h"
#include "UI/Hireables.h"
#include "UI/Inv.h"
#include "UI/Mods.h"
#include "UI/Restart.h"
#include "UI/Text.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "UI/UseItem.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"
#include "Unit/UnitMode.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB7A520
uint32_t dword_6FB7A520;
//D2Client.0x6FB7A5B8
int32_t dword_6FB7A5B8 = 8;
//D2Client.0x6FB7A5BC
int16_t word_6FB7A5BC = -1;
//D2Client.0x6FB7ADD8
uint8_t byte_6FB7ADD8[2976] = {0xFD, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xFD, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xFF, 0, 1, 0, 0, 0, 0, 9, 0, 0, 0, 7, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 9, 0, 0, 0, 7, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 3, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 4, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 5, 1, 1, 0, 0, 0, 0, 0xE, 0, 0, 0, 7, 0, 0, 0, 6, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0x12, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x12, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x13, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x14, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x15, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x16, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x17, 1, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 0x18, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x19, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x1A, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x1B, 1, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 0x1C, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 7, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 8, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 3, 0, 0, 0, 9, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 3, 0, 0, 0, 0xA, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xB, 1, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 0xC, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xD, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xE, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xF, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x10, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0x11, 1, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0xF1, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xF2, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 0, 0, 0, 0, 0xF3, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 0, 0, 0, 0, 0xF4, 0, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 0xF5, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xF6, 0, 1, 0, 0, 0, 0, 0xE, 0, 0, 0, 7, 0, 0, 0, 0xF7, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xF8, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xF9, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xFA, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xFB, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xFC, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0xD7, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xD8, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xD8, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xD9, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xDA, 0, 1, 0, 0, 0, 0, 0xB, 0, 0, 0, 7, 0, 0, 0, 0xDB, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0xDC, 0, 0, 1, 0, 0, 0, 0xF, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDE, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xDF, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 4, 0, 0, 0, 0xE0, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 4, 0, 0, 0, 0xE1, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE2, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE3, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE4, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE5, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE6, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE7, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE8, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0xD1, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD2, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 1, 0, 0, 0, 0xD3, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 1, 0, 0, 0, 0xD4, 1, 1, 0, 0, 0, 0, 0x16, 0, 0, 0, 7, 0, 0, 0, 0xD5, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD6, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD7, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD8, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD9, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xDA, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xDB, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xDC, 1, 1, 1, 0, 0, 0, 0x20, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0xEA, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xEB, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 0, 0, 0, 0, 0xEC, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 0, 0, 0, 0, 0xED, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xEE, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xEF, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xF0, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xF1, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xF2, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0xF5, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xF6, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 2, 0, 0, 0, 0xF7, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 2, 0, 0, 0, 0xF8, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xF9, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xFA, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xFC, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xFD, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xFE, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xFF, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 3, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 3, 0, 0, 0, 4, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 3, 0, 0, 0, 6, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 7, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 8, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 9, 2, 1, 0, 0, 0, 0, 0x16, 0, 0, 0, 7, 0, 0, 0, 0xA, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xB, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xD, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xE, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0x98, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0x98, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0x99, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0x9A, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0x9A, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0x9B, 2, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC5, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC5, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC6, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC7, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC8, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0xC9, 1, 0, 1, 0, 0, 0, 0x17, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x23, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x23, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x24, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x25, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x26, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x27, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x28, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x29, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2A, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2B, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2C, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2D, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0x2E, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2E, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x2F, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x30, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x31, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x32, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x33, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x34, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x35, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x36, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x37, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x38, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0x39, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x3A, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 0, 0, 0, 0, 0x3B, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 0, 0, 0, 0, 0x3C, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 0, 0, 0, 0, 0x3D, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x3E, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x3F, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x40, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x41, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x42, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x43, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x44, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0x45, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x46, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 1, 0, 0, 0, 0x48, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 1, 0, 0, 0, 0x49, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 4, 0, 0, 0, 0x4A, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x4B, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x4C, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x4D, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x4E, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x4F, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x50, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x51, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x52, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x53, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x54, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x47, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 4, 0, 0, 0, 0x55, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x56, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 6, 0, 0, 0, 0x58, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 6, 0, 0, 0, 0x59, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 2, 0, 0, 0, 0x5A, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x5B, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x5C, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x5D, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x5E, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x5F, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x60, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x57, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0x61, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x63, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 5, 0, 0, 0, 0x64, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 3, 0, 0, 0, 0x65, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 5, 0, 0, 0, 0x66, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x67, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x68, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x69, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x6A, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x6B, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 7, 0, 0, 0, 0x62, 0x4E, 0, 1, 0, 0, 0, 0x1C, 0, 0, 0, 3};
//D2Client.0x6FB7B978
uint32_t dword_6FB7B978[4] = {0x94, 0xB7A98800, 0xD6F};
//D2Client.0x6FB7B989
uint8_t byte_6FB7B989;
//D2Client.0x6FB7B98A
uint8_t byte_6FB7B98A[2];
//D2Client.0x6FB7B98C
uint8_t byte_6FB7B98C;
//D2Client.0x6FB7B98D
uint8_t byte_6FB7B98D = 1;
//D2Client.0x6FB7BD6C
int32_t dword_6FB7BD6C = 46;
//D2Client.0x6FB7BD70
uint32_t dword_6FB7BD70 = 0x94;
//D2Client.0x6FB7BD74
uint32_t dword_6FB7BD74 = 3;
//D2Client.0x6FB7BD78
uint16_t word_6FB7BD78 = 0xD35;
//D2Client.0x6FB7BD7A
uint8_t byte_6FB7BD7A[2] = {0x44, 0xD};
//D2Client.0x6FB7BD7C
uint8_t byte_6FB7BD7C[2];
//D2Client.0x6FB7BD7E
uint8_t byte_6FB7BD7E[2];
//D2Client.0x6FB7BD80
uint8_t byte_6FB7BD80[2];
//D2Client.0x6FB7BD82
uint8_t* ptr_6FB7BD82 = (uint8_t*)sub_6FAF3C40;
//D2Client.0x6FB7BD86
uint8_t* ptr_6FB7BD86 = (uint8_t*)sub_6FAF5B80;
//D2Client.0x6FB7BD8A
uint8_t byte_6FB7BD8A[4];
//D2Client.0x6FB7BD8E
uint8_t byte_6FB7BD8E[4];
//D2Client.0x6FB7BD92
uint8_t byte_6FB7BD92[5] = {0, 0, 0, 0, 1};
//D2Client.0x6FB7BDE9
uint8_t byte_6FB7BDE9 = 3;
//D2Client.0x6FB7BDF1
uint8_t byte_6FB7BDF1;
//D2Client.0x6FB7BDFF
uint8_t byte_6FB7BDFF;
//D2Client.0x6FB7BF21
uint8_t byte_6FB7BF21 = 2;
//D2Client.0x6FB7BF27
uint8_t byte_6FB7BF27;
//D2Client.0x6FB7BF33
uint8_t byte_6FB7BF33;
//D2Client.0x6FB7BF6F
uint8_t byte_6FB7BF6F = 2;
//D2Client.0x6FB7BF75
uint8_t byte_6FB7BF75;
//D2Client.0x6FB7BF81
uint8_t byte_6FB7BF81;
//D2Client.0x6FB7BFBD
uint8_t byte_6FB7BFBD = 2;
//D2Client.0x6FB7BFC3
uint8_t byte_6FB7BFC3;
//D2Client.0x6FB7BFCF
uint8_t byte_6FB7BFCF;
//D2Client.0x6FB7BFE4
uint8_t byte_6FB7BFE4 = 3;
//D2Client.0x6FB7C00B
uint8_t byte_6FB7C00B = 3;
//D2Client.0x6FB7C032
uint8_t byte_6FB7C032 = 3;
//D2Client.0x6FB7C059
uint8_t byte_6FB7C059 = 3;
//D2Client.0x6FB7C0A7
uint8_t byte_6FB7C0A7 = 2;
//D2Client.0x6FB7C0AD
uint8_t byte_6FB7C0AD;
//D2Client.0x6FB7C0B9
uint8_t byte_6FB7C0B9;
//D2Client.0x6FB7C33E
uint8_t byte_6FB7C33E = 3;
//D2Client.0x6FB7C365
uint8_t byte_6FB7C365 = 3;
//D2Client.0x6FB7C36D
uint8_t byte_6FB7C36D;
//D2Client.0x6FB7C37B
uint8_t byte_6FB7C37B;
//D2Client.0x6FB7C3B3
uint8_t byte_6FB7C3B3 = 4;
//D2Client.0x6FB7C3BD
uint8_t byte_6FB7C3BD;
//D2Client.0x6FB7C3CD
uint8_t byte_6FB7C3CD;
//D2Client.0x6FB7C401
uint8_t byte_6FB7C401 = 2;
//D2Client.0x6FB7C407
uint8_t byte_6FB7C407;
//D2Client.0x6FB7C413
uint8_t* gpuint8_t_6FB7C413;
//D2Client.0x6FB7C4C0
int32_t dword_6FB7C4C0 = 48;
//D2Client.0x6FB7C4C8
uint16_t word_6FB7C4C8[4] = {0x7B, 0x7E, 0x109};
//D2Client.0x6FB7C4D4
int32_t dword_6FB7C4D4 = 2;
//D2Client.0x6FB7C828
uint8_t byte_6FB7C828;
//D2Client.0x6FB7CA28
uint8_t byte_6FB7CA28;
//D2Client.0x6FB7CC94
uint8_t* gpuint8_t_6FB7CC94 = (uint8_t*)&byte_6FB7C828;
//D2Client.0x6FB7CC98
uint16_t word_6FB7CC98 = 0xF86;
//D2Client.0x6FB7CC9A
uint8_t byte_6FB7CC9A[4] = {0x90, 0xC2, 0xAF, 0x6F};
//D2Client.0x6FB7CC9E
uint32_t dword_6FB7CC9E = 1;
//D2Client.0x6FB7CCA2
uint32_t dword_6FB7CCA2;
//D2Client.0x6FB7CCA6
uint32_t dword_6FB7CCA6;
//D2Client.0x6FB7CCAA
uint32_t dword_6FB7CCAA;
//D2Client.0x6FB7CCAE
uint32_t dword_6FB7CCAE;
//D2Client.0x6FB7CCE8
int32_t dword_6FB7CCE8 = 1;
//D2Client.0x6FB7CCEC
int32_t dword_6FB7CCEC = 1;
//D2Client.0x6FB7CCF0
uint32_t tbl_6FB7CCF0[18] = {0, 0x201, (uint32_t)sub_6FAFDC60, 0, 0x204, (uint32_t)sub_6FAFDC60, 0, 0x100, (uint32_t)sub_6FAFDD30, 0, 0x104, (uint32_t)sub_6FAFDD30, 0, 0x101, (uint32_t)sub_6FAFDF10, 0, 0x105, (uint32_t)sub_6FAFDF10};
//D2Client.0x6FB7CD38
uint32_t tbl_6FB7CD38[3] = {0, 0x207, (uint32_t)sub_6FAFE040};
//D2Client.0x6FB7CD44
uint32_t tbl_6FB7CD44[3] = {0, 0x20B, (uint32_t)sub_6FAFE140};
//D2Client.0x6FB7CD50
uint8_t tbl_6FB7CD50[11] = {0, 0, 0, 0, 0xA, 2, 0, 0, 0x50, 0xE2, 0xAF};
//D2Client.0x6FB7CD5B
uint32_t dword_6FB7CD5B = 0x5C73256F;
//D2Client.0x6FBA7990
int32_t dword_6FBA7990;
//D2Client.0x6FBB5BC8
int32_t dword_6FBB5BC8;
//D2Client.0x6FBB5BCC
D2CellFileStrc* gpCellFile_6FBB5BCC;
//D2Client.0x6FBB5BD0
char byte_6FBB5BD0;
//D2Client.0x6FBB5BD1
uint8_t byte_6FBB5BD1;
//D2Client.0x6FBB5BD5
uint32_t dword_6FBB5BD5;
//D2Client.0x6FBB5BD9
int32_t dword_6FBB5BD9;
//D2Client.0x6FBB5BDD
uint32_t dword_6FBB5BDD;
//D2Client.0x6FBB5BE1
uint8_t byte_6FBB5BE1;
//D2Client.0x6FBB5C38
uint8_t byte_6FBB5C38;
//D2Client.0x6FBB5C39
uint8_t byte_6FBB5C39;
//D2Client.0x6FBB5C3A
uint8_t byte_6FBB5C3A;
//D2Client.0x6FBB5C3B
uint8_t byte_6FBB5C3B;
//D2Client.0x6FBB5C43
uint8_t byte_6FBB5C43;
//D2Client.0x6FBB5C47
uint16_t word_6FBB5C47;
//D2Client.0x6FBB5C49
uint16_t word_6FBB5C49;
//D2Client.0x6FBB5C4B
uint16_t word_6FBB5C4B;
//D2Client.0x6FBB5C4D
int32_t dword_6FBB5C4D;
//D2Client.0x6FBB5C51
int32_t dword_6FBB5C51;
//D2Client.0x6FBB5C55
uint16_t word_6FBB5C55[4];
//D2Client.0x6FBB5C5D
uint32_t dword_6FBB5C5D[2];
//D2Client.0x6FBB5CF5
uint32_t dword_6FBB5CF5;
//D2Client.0x6FBB5CF9
int32_t dword_6FBB5CF9;
//D2Client.0x6FBB5CFC
uint8_t tbl_6FBB5CFC[1];
//D2Client.0x6FBB5CFD
int32_t dword_6FBB5CFD;
//D2Client.0x6FBB5D01
int32_t dword_6FBB5D01;
//D2Client.0x6FBB5D09
int32_t dword_6FBB5D09;
//D2Client.0x6FBB5D0D
uint8_t byte_6FBB5D0D;
//D2Client.0x6FBB5D0F
uint32_t dword_6FBB5D0F;
//D2Client.0x6FBB5D13
D2BitBufferStrc* gpBitBuffer_6FBB5D13;
//D2Client.0x6FBB5D17
D2BitBufferStrc* gpBitBuffer_6FBB5D17;
//D2Client.0x6FBB5D1B
uint8_t byte_6FBB5D1B;
//D2Client.0x6FBB5D1F
uint8_t byte_6FBB5D1F;
//D2Client.0x6FBB5D23
int32_t dword_6FBB5D23;
//D2Client.0x6FBB5D27
int32_t dword_6FBB5D27;
//D2Client.0x6FBB5D2B
uint32_t dword_6FBB5D2B;
//D2Client.0x6FBB5D2F
int32_t dword_6FBB5D2F;
//D2Client.0x6FBB5D33
int32_t dword_6FBB5D33;
//D2Client.0x6FBB5D37
int32_t dword_6FBB5D37;
//D2Client.0x6FBB5D3B
int32_t dword_6FBB5D3B;
//D2Client.0x6FBB5D3F
int32_t dword_6FBB5D3F;
//D2Client.0x6FBB5D43
int32_t dword_6FBB5D43;
//D2Client.0x6FBB5D47
int32_t dword_6FBB5D47;
//D2Client.0x6FBB5D4B
int32_t dword_6FBB5D4B;
//D2Client.0x6FBB5D4F
uint32_t* gpuint32_t_6FBB5D4F;
//D2Client.0x6FBB5D53
D2NpcTransactionPacketStrc gNpcTransactionPacket;
//D2Client.0x6FBB5D62
int32_t dword_6FBB5D62;
//D2Client.0x6FBB5D66
uint16_t word_6FBB5D66;
//D2Client.0x6FBB5D7A
uint16_t word_6FBB5D7A;
//D2Client.0x6FBB5D7C
int32_t dword_6FBB5D7C;
//D2Client.0x6FBB5D80
int32_t dword_6FBB5D80;
//D2Client.0x6FBB5D84
int32_t dword_6FBB5D84;
//D2Client.0x6FBB5D88
uint32_t dword_6FBB5D88;
//D2Client.0x6FBB5D8C
uint32_t dword_6FBB5D8C;
//D2Client.0x6FBB5D90
uint32_t dword_6FBB5D90;
//D2Client.0x6FBB5D94
uint32_t dword_6FBB5D94;
//D2Client.0x6FBB5D98
D2CellFileStrc* gpCellFile_6FBB5D98;
//D2Client.0x6FBB5D9C
uint32_t dword_6FBB5D9C;
//D2Client.0x6FBB5DA0
int32_t dword_6FBB5DA0;
//D2Client.0x6FBB5DA4
uint8_t byte_6FBB5DA4;
//D2Client.0x6FBB5DA8
uint8_t byte_6FBB5DA8;
//D2Client.0x6FBB5DAC
char byte_6FBB5DAC;
//D2Client.0x6FBB5DB0
int32_t dword_6FBB5DB0;
//D2Client.0x6FBB5DB4
int32_t dword_6FBB5DB4;
//D2Client.0x6FBB5DB8
int32_t dword_6FBB5DB8;
//D2Client.0x6FBB5DBC
int32_t dword_6FBB5DBC;
//D2Client.0x6FBB5DC0
uint32_t dword_6FBB5DC0;
//D2Client.0x6FBB5DC4
int32_t dword_6FBB5DC4;
//D2Client.0x6FBB5DC8
uint32_t dword_6FBB5DC8;
//D2Client.0x6FBB5DCC
int32_t dword_6FBB5DCC;
//D2Client.0x6FBB5DD0
int32_t dword_6FBB5DD0;
//D2Client.0x6FBB5DD4
uint8_t byte_6FBB5DD4;
//D2Client.0x6FBB5DD8
uint32_t dword_6FBB5DD8;
//D2Client.0x6FBB5DDC
uint8_t byte_6FBB5DDC;
//D2Client.0x6FBB5DE0
int32_t dword_6FBB5DE0;
//D2Client.0x6FBB5DE4
uint32_t dword_6FBB5DE4;
//D2Client.0x6FBB5DE8
int32_t dword_6FBB5DE8;
//D2Client.0x6FBB5DEC
int32_t dword_6FBB5DEC;
//D2Client.0x6FBB5DF0
int32_t dword_6FBB5DF0;
//D2Client.0x6FBB5DF4
int32_t dword_6FBB5DF4;
//D2Client.0x6FBB5DF8
uint32_t dword_6FBB5DF8;
//D2Client.0x6FBB5DFC
D2CellFileStrc* gpCellFile_6FBB5DFC;
//D2Client.0x6FBB5E00
DWORD dword_6FBB5E00;
//D2Client.0x6FBB5E04
uint8_t byte_6FBB5E04;
//D2Client.0x6FBB5E08
DWORD dword_6FBB5E08;
//D2Client.0x6FBB5E0C
int32_t dword_6FBB5E0C;
//D2Client.0x6FBB5E10
int32_t dword_6FBB5E10;
//D2Client.0x6FBB5E14
int32_t dword_6FBB5E14;
//D2Client.0x6FBB5E18
D2CellFileStrc* gpCellFile_6FBB5E18;
//D2Client.0x6FBB5E1C
D2CellFileStrc* gpCellFile_6FBB5E1C;
//D2Client.0x6FBB5E20
D2CellFileStrc* gpCellFile_6FBB5E20;
//D2Client.0x6FBB5E24
D2CellFileStrc* gpCellFile_6FBB5E24;
//D2Client.0x6FBB5E28
D2CellFileStrc* gpCellFile_6FBB5E28;
//D2Client.0x6FBB5E2C
D2CellFileStrc* gpCellFile_6FBB5E2C;
//D2Client.0x6FBB5E30
D2CellFileStrc* gpCellFile_6FBB5E30;
//D2Client.0x6FBB5E34
D2CellFileStrc* gpCellFile_6FBB5E34;
//D2Client.0x6FBB5E3C
D2CellFileStrc* gpCellFile_6FBB5E3C;
//D2Client.0x6FBB5E40
D2CellFileStrc* gpCellFile_6FBB5E40;
//D2Client.0x6FBB5E44
D2CellFileStrc* gpCellFile_6FBB5E44;
//D2Client.0x6FBB5E48
D2CellFileStrc* gpCellFile_6FBB5E48;
//D2Client.0x6FBB5E4C
D2CellFileStrc* gpCellFile_6FBB5E4C;
//D2Client.0x6FBB5E50
D2CellFileStrc* gpCellFile_6FBB5E50;
//D2Client.0x6FBB5E54
D2CellFileStrc* gpCellFile_6FBB5E54;
//D2Client.0x6FBB5E58
D2CellFileStrc* gpCellFile_6FBB5E58;
//D2Client.0x6FBB5E5C
uint32_t dword_6FBB5E5C;
//D2Client.0x6FBB5E8C
D2CellFileStrc* gpCellFile_6FBB5E8C;

//D2Client.0x6FAF3DF0
void __cdecl sub_6FAF3DF0(int a1)
{
	uint16_t uVar1;
	D2UnitStrc* pDVar2;
	Unicode* pUVar3;
	D2TextHeaderStrc* pTextHeader;
	D2UnitStrc* pItem;
	uint32_t uVar4;
	short in_DX;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	code* pcVar10;
	int iVar11;
	int iVar12;
	int iVar13;
	int iStack_30;
	int iStack_2c;
	D2CoordStrc local_28;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	tagRECT tStack_10;

	D2_ASSERT(!dword_6FBB5D3F);
	local_28.nX = 0;
	local_28.nY = 0;
	if ((dword_6FBB5CF9 != 0) && (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
	{
		if (dword_6FBB5CF9 == 0)
		{
			pDVar2 = nullptr;
		}
		else
		{
			pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		UNITS_GetClientCoords(pDVar2, &local_28);
		sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_20), (uint32_t*)(&iStack_1c), (uint32_t*)(&iStack_18), (uint32_t*)(&iStack_14));
		sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_2c), (uint32_t*)(&iStack_30));
		SetRect(&tStack_10, iStack_2c, iStack_30, (iStack_18 - iStack_20) + iStack_2c,
		    (iStack_30 - iStack_1c) + iStack_14);
		local_28.nY = local_28.nY + (-0x96 - tStack_10.top);
		local_28.nX = local_28.nX - tStack_10.left;
		if (local_28.nY < 0x14)
		{
			local_28.nY = 0x14;
		}
	}
	dword_6FBB5D3F = (int)sub_6FAD6BE0(local_28.nX, local_28.nY, 0x6faf4110, 0x6faf4160, 0, 0, 1, 0, 0, 0, 1);
	sub_6FAD7150(dword_6FBB5D3F, 1);
	iVar11 = 0;
	uVar9 = 0;
	uVar8 = 1;
	iVar7 = 4;
	uVar6 = 0;
	uVar5 = 0x15;
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(in_DX));
	sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar7, uVar8, uVar9, iVar11);
	pTextHeader = sub_6FB1E6B0();
	if (pTextHeader != nullptr)
	{
		iVar7 = TEXT_GetMenuType2NodeCount(pTextHeader);
		dword_6FBB5C51 = a1;
		if ((&byte_6FB7B98C)[a1 * 0x16] == '\0')
		{
			iVar12 = 1;
			pcVar10 = (code*)(sub_6FAF4760);
			uVar8 = 1;
			iVar11 = 0;
			uVar6 = 0;
			uVar5 = 0xf;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd47));
			sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar11, uVar8, (int)(pcVar10), iVar12);
		}
		iVar12 = 1;
		pcVar10 = (code*)(sub_6FAF4300);
		uVar8 = 1;
		iVar11 = 0;
		uVar6 = 0;
		uVar5 = 0xf;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd43));
		sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar11, uVar8, (int)(pcVar10), iVar12);
		iVar11 = 0;
		if (0 < iVar7)
		{
			do
			{
				uVar1 = TEXT_GetStringIdOfMenuType2Node(pTextHeader, iVar11);
				iVar13 = 1;
				pcVar10 = (code*)(sub_6FAF4C30);
				uVar8 = 1;
				iVar12 = 0;
				uVar6 = 0;
				uVar5 = 0xf;
				pUVar3 = sub_6FB1E6C0(uVar1);
				sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar12, uVar8, (int)(pcVar10), iVar13);
				iVar11 = iVar11 + 1;
			} while (iVar11 < iVar7);
		}
		if (dword_6FBB5CFD == 0xc9)
		{
			iVar11 = 1;
			pcVar10 = (code*)(sub_6FAF4D30);
			uVar8 = 1;
			iVar7 = 0;
			uVar6 = 0;
			uVar5 = 0xf;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd40));
			sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar7, uVar8, (int)(pcVar10), iVar11);
		}
		if (((((dword_6FBB5CFD == 0x109) || (dword_6FBB5CFD == 0xf4)) || (dword_6FBB5CFD == 0xf5)) ||
		        ((dword_6FBB5CFD == 0x208 || (dword_6FBB5CFD == 0xf6)))) &&
		    ((pDVar2 = CUNIT_GetPlayer(), pDVar2 != nullptr &&
		                                      (pDVar2->pInventory != nullptr))))
		{
			for (pDVar2 = INVENTORY_GetFirstItem(pDVar2->pInventory); pDVar2 != nullptr;
			     pDVar2 = INVENTORY_GetNextItem(pDVar2))
			{
				pItem = INVENTORY_UnitIsItem(pDVar2);
				if ((pItem != nullptr) && (uVar4 = ITEMS_GetBaseCode(pItem), uVar4 == 0x20786f62))
				{
					iVar11 = 1;
					pcVar10 = (code*)(sub_6FAF4DB0);
					uVar8 = 1;
					iVar7 = 0;
					uVar6 = 0;
					uVar5 = 0xf;
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x8b7));
					sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar7, uVar8, (int)(pcVar10), iVar11);
					break;
				}
			}
		}
	}
	iVar11 = 1;
	pcVar10 = (code*)(sub_6FAF4110);
	uVar8 = 1;
	iVar7 = 0;
	uVar6 = 0;
	uVar5 = 0xf;
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd48));
	sub_6FAD7180(dword_6FBB5D3F, pUVar3, uVar5, uVar6, iVar7, uVar8, (int)(pcVar10), iVar11);
}

//D2Client.0x6FAF4110
uint32_t __cdecl sub_6FAF4110()
{
	if (byte_6FBB5C39 != '\0')
	{
		return 0;
	}
	if (dword_6FBB5D3F != 0)
	{
		sub_6FAD6DC0();
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		dword_6FBB5D3F = 0;
		sub_6FAF65C0();
	}
	return 1;
}

//D2Client.0x6FAF4160
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF4160()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (byte_6FBB5C39 == '\0')
	{
		if (dword_6FBB5D3F != 0)
		{
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
			byte_6FBB5C3B = 0;
			sub_6FAE8F10();
			uVar2 = dword_6FBB5CF5;
			pDVar3 = CUNIT_GetPlayer();
			if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) && (pDVar3->dwUnitType == 0)) && (pDVar3->pPlayerData != nullptr))
			{
				pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
				pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
			}
			if (uVar2 != dword_6FBB5CF5)
			{
				FOG_Trace("mismatch npc ids\n");
			}
			pDVar3 = sub_6FB269F0(uVar2, 1);
			if (pDVar3 != nullptr)
			{
				sub_6FAFBD00();
				pInventory = pDVar3->pInventory;
				if (pInventory != nullptr)
				{
					pDVar3 = INVENTORY_GetFirstItem(pInventory);
					while (pDVar3 != nullptr)
					{
						pDVar4 = INVENTORY_GetNextItem(pDVar3);
						pDVar5 = INVENTORY_UnitIsItem(pDVar3);
						pDVar3 = pDVar4;
						if (pDVar5 != nullptr)
						{
							sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
						}
					}
					INVENTORY_RemoveInventoryItems(pInventory);
					D2COMMON_10251_Return((int)pInventory);
				}
			}
			if (dword_6FBB5D80 != 0)
			{
				sub_6FB556A0(dword_6FBB5D84);
			}
			dword_6FBB5D80 = 0;
			dword_6FBB5D84 = 0;
			pDVar3 = sub_6FB269F0(uVar2, 1);
			if (pDVar3 != nullptr)
			{
				pDVar3->dwFlags = pDVar3->dwFlags | 2;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
			sub_6FB1E710();
			dword_6FBB5CF9 = 0;
			sub_6FB23260(8, 1, 0);
			if (pDVar3 != nullptr)
			{
				if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
				{
					puVar1 = &pDVar3->pPlayerData->unk0x28;
					*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
				}
				sub_6FB4F410(pDVar3, (int*)0x1);
			}
			sub_6FB23260(8, 1, 0);
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAF4300
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF4300()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar3;
	int iVar4;
	uint32_t* puVar5;

	iVar4 = *(int*)(dword_6FBB5C4D + 0xd);
	if (dword_6FBB5CF9 != 0)
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar2 != nullptr)
		{
			byte_6FBB5C39 = 1;
			sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
			*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
			if (byte_6FBB5C3A == '\0')
			{
				iVar4 = 0;
				if (0 < dword_6FB7BD6C)
				{
					puVar5 = dword_6FB7B978;
					do
					{
						sub_6FAF44C0((int)puVar5);
						iVar4 = iVar4 + 1;
						puVar5 = (uint32_t*)((int)puVar5 + 0x16);
					} while (iVar4 < dword_6FB7BD6C);
				}
				byte_6FBB5C3A = '\x01';
				iVar4 = *(int*)(dword_6FBB5C4D + 0xd);
			}
			if (dword_6FBB5CF9 == 0)
			{
				pDVar2 = nullptr;
			}
			else
			{
				pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			sub_6FB1CC20(pDVar2, CONCAT22((short)((uint32_t) * (int*)(dword_6FBB5C4D + 5) >> 0x10), *(uint16_t*)((iVar4 % *(int*)(dword_6FBB5C4D + 9)) * 0xf + *(int*)(dword_6FBB5C4D + 5))), 0);
			return 1;
		}
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar1 = dword_6FBB5CF5;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (((pDVar2 != nullptr) && (pDVar2->dwUnitType == 0)) &&
		    (pDVar2->pPlayerData != nullptr))
		{
			pDVar2->pPlayerData->unk0xA8[0x2a] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2c] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2d] = 0;
		}
	}
	sub_6FAF7950(uVar1);
	pDVar2 = sub_6FB269F0(uVar1, 1);
	uVar3 = extraout_ECX;
	if (pDVar2 != nullptr)
	{
		sub_6FAFA230((int)pDVar2, 2, 1);
		uVar3 = extraout_ECX_00;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar3 >> 8), 0x30), 1, uVar1);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar2 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar2, 1, 0);
		sub_6FB4F410(pDVar2, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF44C0
uint32_t __fastcall sub_6FAF44C0(int a1)
{
	uint64_t uVar1;
	uint64_t DVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t local_8;

	iVar6 = 10;
	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		local_8 = 0xffffffff;
		uVar4 = 0;
	}
	else
	{
		uVar4 = pDVar3->dwClassId;
		local_8 = uVar4;
	}
	do
	{
		uVar5 = *(uint32_t*)(a1 + 9);
		iVar6 = iVar6 + -1;
		if ((int)uVar5 < 1)
		{
			uVar5 = 0;
		}
		else
		{
			uVar4 = (pDVar3->pSeed).nLowSeed;
			uVar1 = (uint64_t)(pDVar3->pSeed).nHighSeed;
			if ((uVar5 & uVar5 - 1) == 0)
			{
				DVar2 = (uint64_t)((uint64_t)uVar4 * 0x6ac690c5 + uVar1);
				uVar4 = (*(uint32_t*)((uint8_t*)&DVar2 + 0));
				(*(uint64_t*)&pDVar3->pSeed) = DVar2;
				uVar5 = uVar5 - 1 & uVar4;
			}
			else
			{
				DVar2 = (uint64_t)((uint64_t)uVar4 * 0x6ac690c5 + uVar1);
				(*(uint64_t*)&pDVar3->pSeed) = DVar2;
				uVar1 = (uint64_t)DVar2 & 0xffffffff;
				uVar4 = (uint32_t)(uVar1 / uVar5);
				uVar5 = (uint32_t)(uVar1 % (uint64_t)uVar5);
			}
		}
		*(uint32_t*)(a1 + 0xd) = uVar5;
		if (1 < (int)uVar5)
		{
			uVar4 = uVar5 * 0xf + *(int*)(a1 + 5);
			if ((*(uint32_t*)(uVar4 + 0xb) == local_8) || (*(uint32_t*)(uVar4 + 0xb) == 7))
			{
				if (*(char*)(uVar4 + 2) == '\0')
				{
					return uVar4;
				}
				uVar4 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, *(int*)(uVar4 + 7), 0);
				if (uVar4 == *(uint32_t*)(*(int*)(a1 + 0xd) * 0xf + 3 + *(int*)(a1 + 5)))
				{
					if (*(uint8_t**)(a1 + 5) != byte_6FB7ADD8)
					{
						return uVar4;
					}
					if (*(short*)(byte_6FB7ADD8 + *(int*)(a1 + 0xd) * 0xf) != 0xff)
					{
						return *(int*)(a1 + 0xd) * 3;
					}
					uVar4 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D17, 0xc, 0xd);
					if (uVar4 != 1)
					{
						return uVar4;
					}
					*(uint32_t*)(a1 + 0xd) = 2;
					return 1;
				}
			}
		}
		if (iVar6 == 0)
		{
			*(uint32_t*)(a1 + 0xd) = 2;
			return uVar4;
		}
	} while (true);
}

//D2Client.0x6FAF45E0
// TODO: decompilation needs review (extraout, in_reg, unaff_)
uint32_t __cdecl sub_6FAF45E0(uint32_t a1)
{
	bool bVar1;
	short sVar2;
	int iVar3;
	D2TextHeaderStrc* pTextHeader;
	uint16_t extraout_var;
	uint16_t extraout_var_00;
	D2UnitStrc* pDVar5;
	uint32_t in_ECX;
	int iVar6;
	uint32_t* puVar7;
	short sVar8;
	uint32_t unaff_ESI;
	uint32_t uVar4;

	sVar8 = word_6FBB5C4B;
	if (byte_6FBB5C39 == '\x01')
	{
		iVar3 = 0;
		if (0 < dword_6FB7C4D4)
		{
			do
			{
				if (word_6FB7C4C8[iVar3 * 4] == word_6FBB5C4B)
				{
					uVar4 = CONCAT22((short)((uint32_t)unaff_ESI >> 0x10), word_6FB7C4C8[iVar3 * 4 + 1]);
					goto LAB_6faf46b3;
				}
				iVar3 = iVar3 + 1;
			} while (iVar3 < dword_6FB7C4D4);
		}
		pTextHeader = sub_6FB1E6B0();
		iVar3 = 0;
		sVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pTextHeader, 0);
		uVar4 = D2C_ZEXT(sVar2);
		while (sVar2 != -1)
		{
			if ((short)uVar4 != sVar8)
			{
				iVar6 = 0;
				if (word_6FBB5D7A == 0)
					goto LAB_6faf46b3;
				while ((&word_6FBB5D66)[iVar6] != (short)uVar4)
				{
					iVar6 = iVar6 + 1;
					if ((int)(uint32_t)word_6FBB5D7A <= iVar6)
						goto LAB_6faf46b3;
				}
			}
			iVar3 = iVar3 + 1;
			sVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pTextHeader, iVar3);
			uVar4 = D2C_ZEXT(sVar2);
		}
	}
LAB_6faf4667:
	byte_6FBB5C39 = 0;
	sub_6FB1CBD0(0, in_ECX);
	iVar3 = 0;
	bVar1 = false;
	byte_6FBB5C3B = 1;
	if (0 < dword_6FB7BD6C)
	{
		puVar7 = dword_6FB7B978;
		do
		{
			if (bVar1)
				break;
			if (*puVar7 == dword_6FBB5CFD)
			{
				bVar1 = true;
			}
			else
			{
				iVar3 = iVar3 + 1;
				puVar7 = (uint32_t*)((int)puVar7 + 0x16);
			}
		} while (iVar3 < dword_6FB7BD6C);
		if (bVar1)
			goto LAB_6faf4731;
	}
	iVar3 = 0;
LAB_6faf4731:
	dword_6FBB5C4D = (int)dword_6FB7B978 + iVar3 * 0x16;
	sub_6FAF3DF0(iVar3);
	return 1;
LAB_6faf46b3:
	sVar8 = (short)uVar4;
	if (((sVar8 != -1) && (dword_6FBB5CF9 != 0)) &&
	    (pDVar5 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar5 != nullptr))
	{
		word_6FBB5C4B = sVar8;
		if (dword_6FBB5CF9 == 0)
		{
			pDVar5 = nullptr;
		}
		else
		{
			pDVar5 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		sub_6FB1CC20(pDVar5, uVar4, 0);
		sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
		return 1;
	}
	goto LAB_6faf4667;
}

//D2Client.0x6FAF4760
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF4760()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint16_t extraout_var;
	int iVar4;
	uint32_t* puVar5;
	uint32_t uVar6;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		iVar4 = -1;
	}
	else
	{
		iVar4 = pDVar2->dwClassId;
	}
	if (dword_6FBB5CF9 != 0)
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar2 != nullptr)
		{
			iVar1 = pDVar2->dwClassId;
			if (iVar1 == 0x201)
			{
				if (iVar4 == 4)
				{
					if (dword_6FBB5CF9 == 0)
					{
					LAB_6faf48fb:
						byte_6FBB5C3B = 0;
						sub_6FAE8F10();
						sub_6FAFBB60(dword_6FBB5CF5);
						sub_6FB23260(8, 1, 0);
						return 1;
					}
					pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
					if (pDVar2 == nullptr)
						goto LAB_6faf48fb;
					byte_6FBB5C39 = 1;
					sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
					sub_6FAD6DC0();
					dword_6FBB5D3F = 0;
					*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
					if (byte_6FBB5C3A == '\0')
					{
						iVar4 = 0;
						if (0 < dword_6FB7BD6C)
						{
							puVar5 = dword_6FB7B978;
							do
							{
								sub_6FAF44C0((int)puVar5);
								iVar4 = iVar4 + 1;
								puVar5 = (uint32_t*)((int)puVar5 + 0x16);
							} while (iVar4 < dword_6FB7BD6C);
						}
						byte_6FBB5C3A = '\x01';
					}
					uVar3 = 0xf;
					goto LAB_6faf4991;
				}
			}
			else if (iVar1 == 0x202)
			{
				if (iVar4 == 2)
				{
					if (dword_6FBB5CF9 != 0)
					{
						pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
						if (pDVar2 != nullptr)
						{
							byte_6FBB5C39 = 1;
							sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
							sub_6FAD6DC0();
							dword_6FBB5D3F = 0;
							*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
							if (byte_6FBB5C3A == '\0')
							{
								sub_6FAF4A40();
							}
							if (dword_6FBB5CF9 == 0)
							{
								pDVar2 = nullptr;
							}
							else
							{
								pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
							}
							iVar4 = (int)(0xb % (int64_t) * (int*)(dword_6FBB5C4D + 9)) * 0xf;
							sub_6FB1CC20(pDVar2, CONCAT22((short)((uint32_t)iVar4 >> 0x10), *(uint16_t*)(iVar4 + *(int*)(dword_6FBB5C4D + 5))), 0);
							return 1;
						}
					}
					goto LAB_6faf48fb;
				}
			}
			else if ((iVar1 == 0x203) && (iVar4 == 3))
			{
				if (dword_6FBB5CF9 != 0)
				{
					pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
					if (pDVar2 != nullptr)
					{
						byte_6FBB5C39 = 1;
						sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
						sub_6FAD6DC0();
						dword_6FBB5D3F = 0;
						*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
						if (byte_6FBB5C3A == '\0')
						{
							sub_6FAF4A40();
						}
						uVar3 = 10;
						goto LAB_6faf4991;
					}
				}
				goto LAB_6faf48fb;
			}
		}
	}
	if (iVar4 != *(int*)(*(int*)(dword_6FBB5C4D + 5) + 0x1a))
	{
		sub_6FAF4A70(0, '\0');
		return 1;
	}
	pDVar2 = sub_6FAF3930();
	if (pDVar2 == nullptr)
	{
		sub_6FAF7A60();
		return 1;
	}
	byte_6FBB5C39 = 1;
	sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
	sub_6FAD6DC0();
	dword_6FBB5D3F = 0;
	*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
	if (byte_6FBB5C3A == '\0')
	{
		sub_6FAF4A40();
	}
	uVar3 = 1;
LAB_6faf4991:
	uVar6 = 0;
	iVar4 = *(int*)(dword_6FBB5C4D + 9);
	iVar1 = *(int*)(dword_6FBB5C4D + 5);
	pDVar2 = sub_6FAF3930();
	sub_6FB1CC20(pDVar2, D2C_ZEXT(*(uint16_t*)((int)((int64_t)(uint64_t)uVar3 % (int64_t)iVar4) * 0xf + iVar1)), uVar6);
	return 1;
}

//D2Client.0x6FAF4A40
void __cdecl sub_6FAF4A40()
{
	int iVar1;
	uint32_t* puVar2;

	iVar1 = 0;
	if (0 < dword_6FB7BD6C)
	{
		puVar2 = dword_6FB7B978;
		do
		{
			sub_6FAF44C0((int)puVar2);
			iVar1 = iVar1 + 1;
			puVar2 = (uint32_t*)((int)puVar2 + 0x16);
		} while (iVar1 < dword_6FB7BD6C);
	}
	byte_6FBB5C3A = 1;
}

//D2Client.0x6FAF4A70
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF4A70(int a1, char a2)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	int iVar3;
	uint32_t* puVar4;

	if (dword_6FBB5CF9 != 0)
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar2 != nullptr)
		{
			byte_6FBB5C39 = 1;
			sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
			*(uint8_t*)(dword_6FBB5C4D + 0x11) = 1;
			if (byte_6FBB5C3A == '\0')
			{
				iVar3 = 0;
				if (0 < dword_6FB7BD6C)
				{
					puVar4 = dword_6FB7B978;
					do
					{
						sub_6FAF44C0((int)puVar4);
						iVar3 = iVar3 + 1;
						puVar4 = (uint32_t*)((int)puVar4 + 0x16);
					} while (iVar3 < dword_6FB7BD6C);
				}
				byte_6FBB5C3A = '\x01';
				if (a2 != '\0')
				{
					a1 = *(int*)(dword_6FBB5C4D + 0xd);
				}
			}
			if (dword_6FBB5CF9 == 0)
			{
				pDVar2 = nullptr;
			}
			else
			{
				pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			sub_6FB1CC20(pDVar2, CONCAT22((short)((uint32_t) * (int*)(dword_6FBB5C4D + 5) >> 0x10), *(uint16_t*)((a1 % *(int*)(dword_6FBB5C4D + 9)) * 0xf + *(int*)(dword_6FBB5C4D + 5))), 0);
			return;
		}
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar1 = dword_6FBB5CF5;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (((pDVar2 != nullptr) && (pDVar2->dwUnitType == 0)) &&
		    (pDVar2->pPlayerData != nullptr))
		{
			pDVar2->pPlayerData->unk0xA8[0x2a] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2c] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2d] = 0;
		}
	}
	sub_6FAF7950(uVar1);
	pDVar2 = sub_6FB269F0(uVar1, 1);
	if (pDVar2 != nullptr)
	{
		pDVar2->dwFlags = pDVar2->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar1);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar2 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar2, 1, 0);
		sub_6FB4F410(pDVar2, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF4C30
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF4C30()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2TextHeaderStrc* pTextHeader;
	uint32_t uVar3;
	int iVar4;
	uint16_t extraout_var;

	iVar1 = sub_6FAD7520(dword_6FBB5D3F);
	iVar4 = 3 - (uint32_t)((&byte_6FB7B98C)[dword_6FBB5C51 * 0x16] != '\0');
	if ((iVar4 <= iVar1) && (dword_6FBB5CF9 != 0))
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar2 != nullptr)
		{
			iVar1 = sub_6FAD7520(dword_6FBB5D3F);
			pTextHeader = sub_6FB1E6B0();
			D2_ASSERT(pTextHeader != nullptr);
			word_6FBB5C4B = TEXT_GetStringIdOfMenuType2Node(pTextHeader, iVar1 - iVar4);
			uVar3 = D2C_ZEXT(word_6FBB5C4B);
			if (dword_6FBB5CF9 == 0)
			{
				pDVar2 = nullptr;
			}
			else
			{
				pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			sub_6FB1CC20(pDVar2, uVar3, 0);
			byte_6FBB5C39 = 1;
			sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAF4D30
uint32_t __cdecl sub_6FAF4D30()
{
	D2UnitStrc* pDVar1;

	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			sub_6FB1CC20(pDVar1, 0xfe, 0);
			byte_6FBB5C39 = 1;
			sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
		}
	}
	return 1;
}

//D2Client.0x6FAF4DB0
uint32_t __cdecl sub_6FAF4DB0()
{
	D2UnitStrc* pDVar1;

	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			sub_6FB1CC20(pDVar1, 0x152, 0);
			byte_6FBB5C39 = 1;
			sub_6FB1CBD0((uint8_t*)(sub_6FAF45E0), 0);
			sub_6FAD6DC0();
			dword_6FBB5D3F = 0;
		}
	}
	return 1;
}

//D2Client.0x6FAF4E30
// TODO: decompilation needs review (unaff_)
uint32_t __cdecl sub_6FAF4E30()
{
	uint8_t bVar1;
	D2UnitStrc* pDVar2;
	Unicode* pUVar3;
	uint32_t uVar4;
	int bExpansion;
	uint16_t uVar5;
	uint32_t unaff_EDI;
	int iVar6;
	uint32_t* unaff_FS_OFFSET;
	uint32_t uVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	int iVar13;
	code* pcVar14;
	uint32_t uVar15;
	D2HirelingInitStrc* pHirelingInit;
	Unicode* pUVar16;
	uint32_t uVar17;
	int iStack_6a0;
	uint16_t* puStack_698;
	int iStack_694;
	CHAR aCStack_690[12];
	void* pvStack_684;
	int iStack_680;
	int iStack_67c;
	int iStack_678;
	int iStack_674;
	char acStack_670[16];
	Unicode aUStack_660[10];
	Unicode aUStack_64c[20];
	D2HirelingInitStrc DStack_624;
	Unicode aUStack_5e8[150];
	Unicode aUStack_4bc[150];
	Unicode aUStack_390[150];
	Unicode local_264[300];
	uint32_t uStack_c;
	code* pcStack_8;
	uint32_t uStack_4;
	uint32_t nDifficulty;

	iVar6 = dword_6FBB5D3B;
	uStack_c = *unaff_FS_OFFSET;
	uStack_4 = 0xffffffff;
	*unaff_FS_OFFSET = (uint32_t)(&uStack_c);
	if (iVar6 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	if (dword_6FBB5D43 == 0)
	{
		dword_6FBB5D43 = (int)sub_6FAD6BE0((gnScreenWidth + -0x1ea) / 2, gnViewHeight / 2 - 0xc3, 0x6faf55b0,
		    0, 0, 0, 0, 0x1ea, 0x15e, 0, 1);
		sub_6FAD7150(dword_6FBB5D43, 1);
		uVar5 = 0;
		iVar6 = 0xf;
		pDVar2 = CUNIT_GetPlayer();
		iVar6 = STATLIST_UnitGetStatValue(pDVar2, iVar6, uVar5);
		uVar5 = 0;
		iVar13 = 0xe;
		pDVar2 = CUNIT_GetPlayer();
		iVar13 = STATLIST_UnitGetStatValue(pDVar2, iVar13, uVar5);
		iVar6 = iVar6 + iVar13;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd24));
		Unicode::sprintf(300, local_264, pUVar3, iVar6);
		sub_6FAD7180(dword_6FBB5D43, local_264, 0x15, 0, 4, 1, 0, 0);
		iVar13 = 1;
		pcVar14 = (code*)(sub_6FAF55B0);
		uVar11 = 1;
		iVar6 = 0;
		uVar8 = 0;
		uVar4 = 0x13b;
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd48));
		sub_6FAD7180(dword_6FBB5D43, pUVar3, uVar4, uVar8, iVar6, uVar11, (int)(pcVar14), iVar13);
		pvStack_684 = SMemAlloc(0xc, "new", -1, 0);
		uStack_4 = 0;
		if (pvStack_684 == nullptr)
		{
			gpuint32_t_6FBB5D4F = nullptr;
		}
		else
		{
			gpuint32_t_6FBB5D4F = (uint32_t*)
			    sub_6FAF1130(pvStack_684, gnScreenWidth + -0x1ea >> 0x1f,
			        (gnScreenWidth + -0x1ea) / 2, gnViewHeight / 2 + -0xa0, 0x1ea, 0x118, 6, 0, 1, (uint32_t)(sub_6FAF55F0), 0);
		}
		uStack_4 = 0xffffffff;
		if (gpuint32_t_6FBB5D4F != nullptr)
		{
			sub_6FAD68F0(dword_6FBB5D43, (uint32_t)(gpuint32_t_6FBB5D4F), 0x23, 0x1e);
			puStack_698 = word_6FBB5C55;
			iStack_694 = 0;
			iStack_680 = 0;
			do
			{
				iVar6 = iStack_680;
				if (*(int*)(puStack_698 + 4) != 0)
				{
					uVar5 = *puStack_698;
					iVar6 = sub_6FAAC080();
					iVar13 = MONSTERS_GetActFromHirelingTxt(iVar6, 0, uVar5);
					bVar1 = sub_6FAAC090();
					nDifficulty = (uint32_t)bVar1;
					pHirelingInit = &DStack_624;
					iVar6 = *(int*)(puStack_698 + 2);
					pDVar2 = CUNIT_GetPlayer();
					bExpansion = sub_6FAAC080();
					iVar13 = MONSTERS_HirelingInit(bExpansion, pDVar2, iVar6, iVar13, nDifficulty, pHirelingInit);
					iVar6 = DStack_624.nHireDesc;
					if (iVar13 == 0)
						goto LAB_6faf5021;
					iStack_678 = DStack_624.nLevel;
					iStack_67c = DStack_624.nHitpoints;
					iStack_674 = DStack_624.nDefense;
					pvStack_684 = (void*)DStack_624.nGold;
					uVar5 = *puStack_698;
					if (uVar5 == 0x421)
					{
						uVar5 = 0x2b0d;
					}
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(uVar5));
					Unicode::strcpy(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9c));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					iVar13 = 0x14;
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd28));
					Unicode::strncpy(aUStack_64c, pUVar3, iVar13);
					Unicode::strcat(aUStack_5e8, aUStack_64c);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					wsprintfA(aCStack_690, "%2u", iStack_678);
					Unicode::win2Unicode(aUStack_660, aCStack_690, 9);
					Unicode::strcat(aUStack_5e8, aUStack_660);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					iVar13 = 0x14;
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd26));
					Unicode::strncpy(aUStack_64c, pUVar3, iVar13);
					Unicode::strcat(aUStack_5e8, aUStack_64c);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					wsprintfA(aCStack_690, "%2u", iStack_67c);
					Unicode::win2Unicode(aUStack_660, aCStack_690, 9);
					Unicode::strcat(aUStack_5e8, aUStack_660);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					iVar13 = 0x14;
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd27));
					Unicode::strncpy(aUStack_64c, pUVar3, iVar13);
					Unicode::strcat(aUStack_5e8, aUStack_64c);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					wsprintfA(aCStack_690, "%2u", iStack_674);
					Unicode::win2Unicode(aUStack_660, aCStack_690, 9);
					Unicode::strcat(aUStack_5e8, aUStack_660);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					iVar13 = 0x14;
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd29));
					Unicode::strncpy(aUStack_64c, pUVar3, iVar13);
					Unicode::strcat(aUStack_5e8, aUStack_64c);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9d));
					Unicode::strcat(aUStack_5e8, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_5e8, pUVar3);
					wsprintfA(aCStack_690, "%2u", pvStack_684);
					Unicode::win2Unicode(aUStack_660, aCStack_690, 9);
					Unicode::strcat(aUStack_5e8, aUStack_660);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_4bc, pUVar3);
					pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat(aUStack_4bc, pUVar3);
					pUVar3 = (Unicode*)(MONSTERS_GetHirelingDescString(iVar6));
					if (pUVar3 != nullptr)
					{
						pUVar16 = nullptr;
						acStack_670[0] = 'a';
						acStack_670[1] = '\0';
						acStack_670[2] = '0';
						acStack_670[3] = '\0';
						acStack_670[4] = ':';
						acStack_670[5] = '\0';
						acStack_670[6] = '%';
						acStack_670[7] = '\0';
						acStack_670[8] = '0';
						acStack_670[9] = '\0';
						acStack_670[10] = '\0';
						acStack_670[0xb] = '\0';
						pUVar3 = (Unicode*)(MONSTERS_GetHirelingDescString(iVar6));
						sub_6FADCFE0(aUStack_390, acStack_670, pUVar3, pUVar16, (short)unaff_EDI);
						Unicode::strcat(aUStack_4bc, aUStack_390);
					}
					iVar6 = iStack_680;
					(**(code**)(*gpuint32_t_6FBB5D4F + 0x30))(aUStack_5e8, aUStack_4bc, 0, 0, 0, 0, iStack_680, 0, 1, 0xe);
					iStack_694 = iStack_694 + 1;
				}
				puStack_698 = puStack_698 + 8;
				iStack_680 = iVar6 + 1;
			} while (iStack_680 < 10);
			if (iStack_694 == 0)
			{
				uVar17 = 0xe;
				uVar15 = 1;
				uVar12 = 0;
				iVar6 = *gpuint32_t_6FBB5D4F;
				uVar10 = 10;
				uVar9 = 0;
				uVar7 = 0;
				uVar11 = 0;
				uVar8 = 0;
				uVar4 = 0;
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd25));
				(**(code**)(iVar6 + 0x30))(pUVar3, uVar4, uVar8, uVar11, uVar7, uVar9, uVar10, uVar12, uVar15, uVar17);
			}
			sub_6FAD7090(dword_6FBB5D43, -1);
			uVar4 = 1;
			goto LAB_6faf5597;
		}
		if (dword_6FBB5D43 != 0)
		{
			sub_6FAD6DC0();
			if (gpuint32_t_6FBB5D4F != nullptr)
			{
				(**(code**)*gpuint32_t_6FBB5D4F)(1);
			}
			goto LAB_6faf5010;
		}
	}
	else
	{
		sub_6FAD6DC0();
		if (gpuint32_t_6FBB5D4F != nullptr)
		{
			(**(code**)*gpuint32_t_6FBB5D4F)(1);
		}
	LAB_6faf5010:
		gpuint32_t_6FBB5D4F = nullptr;
		dword_6FBB5D43 = 0;
	}
	sub_6FAF65C0();
LAB_6faf5021:
	uVar4 = 0;
LAB_6faf5597:
	*unaff_FS_OFFSET = uStack_c;
	return uVar4;
}

//D2Client.0x6FAF55B0
uint32_t __cdecl sub_6FAF55B0()
{
	if (dword_6FBB5D43 != 0)
	{
		sub_6FAD6DC0();
		if (gpuint32_t_6FBB5D4F != nullptr)
		{
			(**(code**)*gpuint32_t_6FBB5D4F)(1);
		}
		gpuint32_t_6FBB5D4F = nullptr;
		dword_6FBB5D43 = 0;
	}
	sub_6FAF65C0();
	return 1;
}

//D2Client.0x6FAF55F0
uint32_t __cdecl sub_6FAF55F0()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	int iVar3;

	sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
	dword_6FBB5BC8 = (**(code**)(*gpuint32_t_6FBB5D4F + 0x2c))();
	dword_6FBB5D94 = dword_6FBB5CF5;
	if (dword_6FBB5BC8 < 10)
	{
		uVar1 = (**(code**)(*gpuint32_t_6FBB5D4F + 0x34))(dword_6FBB5BC8);
		if (uVar1 < 10)
		{
			iVar3 = 0;
			pDVar2 = CUNIT_GetPlayer();
			iVar3 = sub_6FAB1920((int)pDVar2, 7, iVar3);
			if (iVar3 == -1)
			{
				iVar3 = sub_6FAAC080();
				if (iVar3 == 0)
				{
				LAB_6faf567d:
					sub_6FAF56D0();
					return 0;
				}
				pDVar2 = CUNIT_GetPlayer();
				iVar3 = sub_6FAB18F0((int)pDVar2, 7);
				if ((iVar3 == 0) && (word_6FB7A5BC == -1))
					goto LAB_6faf567d;
			}
			if (dword_6FBB5D43 != 0)
			{
				sub_6FAD6DC0();
				if (gpuint32_t_6FBB5D4F != nullptr)
				{
					(**(code**)*gpuint32_t_6FBB5D4F)(1);
				}
				gpuint32_t_6FBB5D4F = nullptr;
				dword_6FBB5D43 = 0;
			}
			dword_6FBB5D01 = 5;
			sub_6FAFB710();
		}
	}
	return 0;
}

//D2Client.0x6FAF56D0
void __cdecl sub_6FAF56D0()
{
	D2UnitStrc* pDVar1;
	DWORD DVar2;
	Unicode* pUVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	int iStack_30;
	int iStack_2c;
	D2CoordStrc local_28;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	tagRECT tStack_10;

	sub_6FAADA40(CONCAT31((uint32_t)(uint8_t)((uint16_t)word_6FBB5C55[dword_6FBB5BC8 * 8] >> 8), 0x36),
	    dword_6FBB5D94, (uint32_t)(uint16_t)word_6FBB5C55[dword_6FBB5BC8 * 8]);
	if (dword_6FBB5D43 != 0)
	{
		sub_6FAD6DC0();
		if (gpuint32_t_6FBB5D4F != nullptr)
		{
			(**(code**)*gpuint32_t_6FBB5D4F)(1);
		}
		gpuint32_t_6FBB5D4F = nullptr;
		dword_6FBB5D43 = 0;
	}
	byte_6FBB5C3B = 10;
	local_28.nX = 0;
	local_28.nY = 0;
	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			UNITS_GetClientCoords(pDVar1, &local_28);
			sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_20), (uint32_t*)(&iStack_1c), (uint32_t*)(&iStack_18), (uint32_t*)(&iStack_14));
			sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_2c), (uint32_t*)(&iStack_30));
			SetRect(&tStack_10, iStack_2c, iStack_30, (iStack_18 - iStack_20) + iStack_2c,
			    (iStack_30 - iStack_1c) + iStack_14);
			local_28.nY = local_28.nY + (-0x96 - tStack_10.top);
			local_28.nX = local_28.nX - tStack_10.left;
			if (local_28.nY < 0x14)
			{
				local_28.nY = 0x14;
			}
		}
	}
	dword_6FBB5D37 = (int)sub_6FAD6BE0(local_28.nX, local_28.nY, 0x6fb24f70, 0, 0, 0, 1, 0, 0, 0, 1);
	DVar2 = GetTickCount();
	dword_6FBB5D23 = DVar2 + 60000;
	dword_6FBB5D27 = 0;
	sub_6FAD7150(dword_6FBB5D37, 0);
	iVar9 = 0;
	uVar8 = 0;
	uVar7 = 1;
	iVar6 = 0;
	uVar5 = 0;
	uVar4 = 0xf;
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd19));
	sub_6FAD7180(dword_6FBB5D37, pUVar3, uVar4, uVar5, iVar6, uVar7, uVar8, iVar9);
}

//D2Client.0x6FAF5880
void __fastcall sub_6FAF5880(uint32_t* a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	DWORD DVar3;
	DWORD DVar4;
	Unicode* pUVar5;
	short index;
	code* pcVar6;
	DWORD DVar7;
	DWORD DVar8;
	DWORD DVar9;
	DWORD DVar10;
	DWORD DVar11;
	DWORD DVar12;
	uint32_t uVar13;
	int iVar14;
	uint32_t uVar15;
	uint32_t uVar16;
	uint16_t nLayer;
	uint32_t uVar17;
	int iVar18;

	nLayer = 0;
	iVar14 = 0xe;
	memcpy(&gNpcTransactionPacket, a1, sizeof(gNpcTransactionPacket));
	pDVar1 = CUNIT_GetPlayer();
	byte_6FBB5C43 = STATLIST_UnitGetStatValue(pDVar1, iVar14, nLayer);
	if (byte_6FBB5C3B != 5)
	{
		if (byte_6FBB5C3B == 10)
		{
			sub_6FAFB030();
			return;
		}
		if (*(char*)((int)a1 + 2) == '\x01')
		{
			sub_6FB55820(0xdd, nullptr, 0.0, 0.0, 0);
		}
		return;
	}
	pDVar1 = CUNIT_GetPlayer();
	pInventory = pDVar1->pInventory;
	if (6 < (uint8_t)gNpcTransactionPacket.nTransactionType)
	{
		if (dword_6FBB5D37 != 0)
		{
			sub_6FAD6DC0();
			dword_6FBB5D37 = 0;
		}
		switch (gNpcTransactionPacket.nTransactionType)
		{
		case '\a':
		case '\b':
			index = 0xd1e;
			break;
		default:
			index = 0xd21;
			break;
		case '\n':
			index = 0xd1c;
			break;
		case '\v':
			index = 0xd20;
			break;
		case '\f':
			index = 0xd22;
			break;
		case '\x0f':
			index = 0xd23;
			break;
		case '\x10':
			index = 0xd1d;
		}
		if (byte_6FBB5C3B == 5)
		{
			byte_6FBB5C3B = 6;
			sub_6FAE9620();
			D2_ASSERT(!dword_6FBB5D33);
			if ((((dword_6FBB5D01 == 2) &&
			         (pDVar1 = INVENTORY_GetCursorItem(pInventory), dword_6FBB5D0F == 1)) &&
			        (pDVar1 != nullptr)) &&
			    (pDVar2 = sub_6FB575E0(), pDVar2 == nullptr))
			{
				sub_6FB575B0(pDVar1);
			}
			uVar17 = 1;
			uVar15 = 0;
			DVar12 = 0;
			DVar11 = 0;
			DVar10 = 1;
			DVar9 = 1;
			DVar8 = 0;
			DVar7 = 0;
			pcVar6 = (code*)(sub_6FAF6EE0);
			DVar3 = sub_6FB57BD0();
			DVar4 = sub_6FB57BC0();
			dword_6FBB5D33 = (int)sub_6FAD6BE0(DVar4, DVar3, (DWORD)pcVar6, DVar7, DVar8, DVar9, DVar10, DVar11,
			    DVar12, uVar15, uVar17);
			sub_6FAD7150(dword_6FBB5D33, 1);
			iVar18 = 0;
			uVar16 = 0;
			uVar13 = 1;
			iVar14 = 1;
			uVar17 = 0;
			uVar15 = 0x15;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
			sub_6FAD7180(dword_6FBB5D33, pUVar5, uVar15, uVar17, iVar14, uVar13, uVar16, iVar18);
			iVar18 = 1;
			pcVar6 = (code*)(sub_6FAF6EE0);
			uVar13 = 1;
			iVar14 = 0;
			uVar17 = 0;
			uVar15 = 0xf;
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd4b));
			sub_6FAD7180(dword_6FBB5D33, pUVar5, uVar15, uVar17, iVar14, uVar13, (int)(pcVar6), iVar18);
			return;
		}
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	}
	if (gNpcTransactionPacket.nTransactionType == '\0')
	{
		sub_6FB55820(dword_6FBB5D2B, nullptr, 0.0, 0.0, 0);
		dword_6FBB5D2B = 0;
		pDVar1 = sub_6FB269F0(gNpcTransactionPacket.dwItemGUID, 4);
		if (pDVar1 == nullptr)
		{
			dword_6FBB5D62 = 1;
			return;
		}
	}
	else if (gNpcTransactionPacket.nTransactionType == '\x01')
	{
		sub_6FB55820(0xdd, nullptr, 0.0, 0.0, 0);
		pDVar1 = sub_6FB269F0(gNpcTransactionPacket.dwItemGUID, 4);
		if (pDVar1 != nullptr)
		{
			dword_6FBB5D62 = 1;
			return;
		}
	}
	else if (gNpcTransactionPacket.nTransactionType == '\x05')
	{
		sub_6FADBF00();
	}
	dword_6FBB5D62 = 0;
	if (dword_6FBB5D37 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D37 = 0;
	}
	sub_6FAB5D40();
	byte_6FBB5BD0 = '\0';
	byte_6FBB5BD1 = 0;
	dword_6FBB5BD5 = 0;
	byte_6FBB5C3B = 3;
	sub_6FAE95B0();
	sub_6FAEAC40();
}

//D2Client.0x6FAF5B80
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF5B80()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar3;
	uint32_t extraout_ECX_01;

	if (dword_6FBB5D80 != 0)
	{
		if (dword_6FBB5D84 != 0)
		{
			sub_6FB556A0(dword_6FBB5D84);
			dword_6FBB5D84 = 0;
		}
		dword_6FBB5D80 = 0;
	}
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
	if ((pDVar2 != nullptr) && (pDVar2->pInventory != nullptr))
	{
		byte_6FBB5C3B = 3;
		dword_6FBB5D7C = 0;
		sub_6FB23260(0xc, 0, 0);
		sub_6FAADA70(CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 0x38), 1, dword_6FBB5CF5, 0);
		dword_6FBB5DA0 = (int)CUNIT_GetPlayer();
		byte_6FBB5DA4 = 0;
		return 1;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar1 = dword_6FBB5CF5;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		sub_6FAFBB10((int*)pDVar2);
	}
	if (uVar1 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar2 = sub_6FB269F0(uVar1, 1);
	if (pDVar2 != nullptr)
	{
		sub_6FAF78E0((int)pDVar2);
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar2 = sub_6FB269F0(uVar1, 1);
	uVar3 = extraout_ECX;
	if (pDVar2 != nullptr)
	{
		sub_6FAFA230((int)pDVar2, 2, 1);
		uVar3 = extraout_ECX_00;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar3 >> 8), 0x30), 1, uVar1);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar2 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar2, 1, 0);
		sub_6FB4F410(pDVar2, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF5D20
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF5D20()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar3;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
	uVar1 = dword_6FBB5CF5;
	if ((pDVar2 != nullptr) && (pDVar2->pInventory != nullptr))
	{
		byte_6FBB5C3B = 3;
		dword_6FBB5D7C = 1;
		sub_6FB23260(0xc, 0, 0);
		sub_6FAADA70(D2C_ZEXT(0x38), 2, dword_6FBB5CF5, 0);
		dword_6FBB5DA0 = (int)CUNIT_GetPlayer();
		byte_6FBB5DA4 = 0;
		return 1;
	}
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (((pDVar2 != nullptr) && (pDVar2->dwUnitType == 0)) &&
		    (pDVar2->pPlayerData != nullptr))
		{
			pDVar2->pPlayerData->unk0xA8[0x2a] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2c] = 0;
			pDVar2->pPlayerData->unk0xA8[0x2d] = 0;
		}
	}
	if (uVar1 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar2 = sub_6FB269F0(uVar1, 1);
	if (pDVar2 != nullptr)
	{
		sub_6FAF78E0((int)pDVar2);
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar2 = sub_6FB269F0(uVar1, 1);
	uVar3 = extraout_ECX;
	if (pDVar2 != nullptr)
	{
		sub_6FAFA230((int)pDVar2, 2, 1);
		uVar3 = extraout_ECX_00;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar3 >> 8), 0x30), 1, uVar1);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar2 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar2, 1, 0);
		sub_6FB4F410(pDVar2, (int*)0x1);
	}
	return 1;
}

//D2Client.0x6FAF5EB0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF5EB0()
{
	D2UnitStrc* pDVar1;
	DWORD DVar2;
	Unicode* pUVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	int iStack_30;
	int iStack_2c;
	D2CoordStrc local_28;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	tagRECT tStack_10;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	D2_ASSERT(!dword_6FBB5D37);
	local_28.nX = 0;
	local_28.nY = 0;
	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			UNITS_GetClientCoords(pDVar1, &local_28);
			sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_20), (uint32_t*)(&iStack_1c), (uint32_t*)(&iStack_18), (uint32_t*)(&iStack_14));
			sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_2c), (uint32_t*)(&iStack_30));
			SetRect(&tStack_10, iStack_2c, iStack_30, (iStack_18 - iStack_20) + iStack_2c,
			    (iStack_30 - iStack_1c) + iStack_14);
			local_28.nY = local_28.nY + (-0x96 - tStack_10.top);
			local_28.nX = local_28.nX - tStack_10.left;
			if (local_28.nY < 0x14)
			{
				local_28.nY = 0x14;
			}
		}
	}
	dword_6FBB5D37 = (int)sub_6FAD6BE0(local_28.nX, local_28.nY, 0x6fb24f70, 0, 0, 0, 1, 0, 0, 0, 1);
	DVar2 = GetTickCount();
	dword_6FBB5D23 = DVar2 + 60000;
	dword_6FBB5D27 = 0;
	sub_6FAD7150(dword_6FBB5D37, 0);
	iVar9 = 0;
	uVar8 = 0;
	uVar7 = 1;
	iVar6 = 0;
	uVar5 = 0;
	uVar4 = 0xf;
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd19));
	sub_6FAD7180(dword_6FBB5D37, pUVar3, uVar4, uVar5, iVar6, uVar7, uVar8, iVar9);
	byte_6FBB5C3B = 10;
	dword_6FBB5D01 = 4;
	dword_6FBB5D62 = 0;
	sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x34), dword_6FBB5CF5);
	return 1;
}

//D2Client.0x6FAF6070
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF6070()
{
	uint64_t DVar1;
	bool bVar2;
	uint32_t extraout_var;
	D2UnitStrc* pDVar3;
	DWORD DVar4;
	int iVar5;
	uint32_t extraout_ECX;

	bVar2 = sub_6FB283E0();
	if ((D2C_ZEXT(bVar2) == 0) && (dword_6FBB5CF9 != 0))
	{
		pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar3 == nullptr)
		{
		LAB_6faf60b9:
			if (dword_6FBB5CF9 != 0)
			{
				pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
				if (pDVar3 != nullptr)
					goto LAB_6faf6106;
			}
		}
		else if (dword_6FBB5CF9 != 0)
		{
			pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
			if ((pDVar3 == nullptr) || (pDVar3->dwAnimMode != 0xc))
				goto LAB_6faf60b9;
		}
	}
	sub_6FAF6340();
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	sub_6FAFBB60(dword_6FBB5CF5);
	sub_6FB23260(8, 1, 0);
LAB_6faf6106:
	if (dword_6FBB5D3F != 0)
	{
		sub_6FAD6EB0(dword_6FBB5D3F);
		return;
	}
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAABF30();
		sub_6FAD6EB0(dword_6FBB5D3B);
		return;
	}
	if (dword_6FBB5D33 != 0)
	{
		sub_6FAD6EB0(dword_6FBB5D33);
		return;
	}
	if (dword_6FBB5D37 == 0)
	{
		if (dword_6FBB5D2F == 0)
		{
			if (dword_6FBB5D43 != 0)
			{
				sub_6FAD6EB0(dword_6FBB5D43);
				return;
			}
			if (dword_6FBB5D47 != 0)
			{
				sub_6FAD6EB0(dword_6FBB5D47);
				return;
			}
		}
		else
		{
			pDVar3 = CUNIT_GetPlayer();
			pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
			if (pDVar3 == nullptr)
			{
				pDVar3 = sub_6FB575E0();
				if (pDVar3 == nullptr)
				{
					sub_6FAD6EB0(dword_6FBB5D2F);
					return;
				}
			}
			byte_6FBB5C3B = 3;
			sub_6FAED1C0();
			dword_6FBB5BD9 = GetTickCount();
			dword_6FBB5BDD = dword_6FBB5BDD + 1;
			sub_6FAD6DC0();
			dword_6FBB5D2F = 0;
		}
	}
	else
	{
		if (dword_6FBB5CF9 != 0)
		{
			pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
			if ((pDVar3 != nullptr) && (dword_6FBB5CF9 != 0))
			{
				pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
				if ((pDVar3 != nullptr) && ((pDVar3->dwClassId == 0x202 && (dword_6FBB5D88 == 0))))
				{
					if (dword_6FBB5D8C == 0)
					{
						dword_6FBB5D8C = 1;
						pDVar3 = CUNIT_GetPlayer();
						DVar1 = (uint64_t)((uint64_t)(pDVar3->pSeed).nLowSeed * 0x6ac690c5 +
						                   (uint64_t)(pDVar3->pSeed).nHighSeed);
						(*(uint64_t*)&pDVar3->pSeed) = DVar1;
						DVar4 = GetTickCount();
						dword_6FBB5D90 = DVar4 + ((int)(((uint64_t)DVar1 & 0xffffffff) % 0x1e) * 5 + 600) * 200;
					}
					DVar4 = GetTickCount();
					if (DVar4 < dword_6FBB5D90)
					{
						dword_6FBB5D88 = 1;
						sub_6FB55820(0x11d0, nullptr, 0.0, 0.0, 0);
					}
				}
			}
		}
		iVar5 = sub_6FAABFF0();
		if ((iVar5 != 0) && (dword_6FBB5D27 != 0))
		{
			DVar4 = GetTickCount();
			if ((uint32_t)dword_6FBB5D27 < DVar4)
			{
				if (dword_6FBB5D37 != 0)
				{
					sub_6FAD6DC0();
					dword_6FBB5D37 = 0;
				}
				byte_6FBB5C3B = 3;
				sub_6FAE95B0();
				sub_6FAEAC40();
				sub_6FAB5D40();
				return;
			}
		}
		DVar4 = GetTickCount();
		if ((uint32_t)dword_6FBB5D23 < DVar4)
		{
			sub_6FAAD420((int32_t)extraout_ECX);
			CLIENT_SetExitToMenu(0);
			sub_6FAA9430(1);
			sub_6FAAB240();
			return;
		}
	}
}

//D2Client.0x6FAF6340
void __cdecl sub_6FAF6340()
{
	if (dword_6FBB5D3F != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3F = 0;
	}
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	if (dword_6FBB5D47 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D47 = 0;
	}
	if (dword_6FBB5D2F != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D2F = 0;
	}
	if (dword_6FBB5D33 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D33 = 0;
	}
	if (dword_6FBB5D37 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D37 = 0;
	}
	if (dword_6FBB5D43 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D43 = 0;
	}
}

//D2Client.0x6FAF63E0
uint32_t __cdecl sub_6FAF63E0()
{
	byte_6FB7BF21 = 3;
	byte_6FB7BF33 = (uint8_t)(sub_6FAF4E30);
	byte_6FB7BF27 = 0xd45;
	return 1;
}

//D2Client.0x6FAF6410
uint32_t __cdecl sub_6FAF6410()
{
	byte_6FB7BF6F = 3;
	byte_6FB7BF81 = (uint8_t)(sub_6FAF70C0);
	byte_6FB7BF75 = 0xd36;
	return 1;
}

//D2Client.0x6FAF6440
uint32_t __cdecl sub_6FAF6440()
{
	byte_6FB7BFBD = 3;
	byte_6FB7BFCF = (uint8_t)(sub_6FAF7260);
	byte_6FB7BFC3 = 0xd38;
	return 1;
}

//D2Client.0x6FAF6470
uint32_t __cdecl sub_6FAF6470()
{
	byte_6FB7BDE9 = 4;
	byte_6FB7BDFF = (uint8_t)(sub_6FAF64A0);
	byte_6FB7BDF1 = 0xfb1;
	return 1;
}

//D2Client.0x6FAF64A0
uint32_t __cdecl sub_6FAF64A0()
{
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	sub_6FB23260(8, 1, 0);
	sub_6FB238B0();
	sub_6FAE8F10();
	byte_6FBB5C3B = 7;
	dword_6FBB5D01 = 0;
	sub_6FB25BA0(dword_6FBB5CF5);
	return 1;
}

//D2Client.0x6FAF6500
uint32_t __cdecl sub_6FAF6500()
{
	byte_6FB7C365 = 4;
	byte_6FB7C37B = (uint8_t)(sub_6FAF64A0);
	byte_6FB7C36D = 0x58dc;
	return 1;
}

//D2Client.0x6FAF6530
uint32_t __cdecl sub_6FAF6530()
{
	byte_6FB7C3B3 = 5;
	byte_6FB7C3CD = (uint8_t)(sub_6FAF64A0);
	byte_6FB7C3BD = 0x58dd;
	return 1;
}

//D2Client.0x6FAF6560
uint32_t __cdecl sub_6FAF6560()
{
	byte_6FB7C401 = 3;
	gpuint8_t_6FB7C413 = (uint8_t*)(sub_6FAF4E30);
	byte_6FB7C407 = 0xd45;
	return 1;
}

//D2Client.0x6FAF6590
uint32_t __cdecl sub_6FAF6590()
{
	int iVar1;

	iVar1 = sub_6FAAC080();
	if (iVar1 != 0)
	{
		byte_6FB7C0A7 = 3;
		byte_6FB7C0B9 = (uint8_t)(sub_6FAF7400);
		byte_6FB7C0AD = 0x58d2;
	}
	return 1;
}

//D2Client.0x6FAF65C0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF65C0()
{
	bool bVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	Unicode* pUVar4;
	Unicode* a3;
	int iVar5;
	short index;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	int* piVar6;
	short* psVar7;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	code* pcVar13;
	uint16_t nLayer;
	int iStack_500;
	short* psStack_4fc;
	D2CoordStrc local_4f8;
	uint32_t* puStack_4f0;
	int iStack_4ec;
	int iStack_4e8;
	int iStack_4e4;
	int iStack_4e0;
	int iStack_4dc;
	tagRECT tStack_4d8;
	Unicode aUStack_4c8[10];
	Unicode aUStack_4b4[10];
	Unicode aUStack_4a0[80];
	Unicode aUStack_400[512];

	D2_ASSERT(!dword_6FBB5D3B);
	if ((dword_6FBB5CF9 == 0) || (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 == nullptr))
	{
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		uVar3 = dword_6FBB5CF5;
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 != nullptr)
		{
			pDVar2 = CUNIT_GetPlayer();
			sub_6FAFBB10((int*)pDVar2);
		}
		sub_6FAF7950(uVar3);
		pDVar2 = sub_6FB269F0(uVar3, 1);
		uVar10 = extraout_ECX;
		if (pDVar2 != nullptr)
		{
			sub_6FAFA230((int)pDVar2, 2, 1);
			uVar10 = extraout_ECX_00;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar10 >> 8), 0x30), 1, uVar3);
		sub_6FB1E710();
		sub_6FAF3DC0(0);
		sub_6FB23260(8, 1, 0);
		if (pDVar2 != nullptr)
		{
			sub_6FAFB6E0((int*)pDVar2, 1, 0);
			sub_6FB4F410(pDVar2, (int*)0x1);
		}
		sub_6FB23260(8, 1, 0);
		return;
	}
	if ((((dword_6FBB5CFD == 0xfc) || (dword_6FBB5CFD == 0xc6)) || (dword_6FBB5CFD == 0x203)) ||
	    (dword_6FBB5CFD == 0x96))
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar2->dwUnitId;
		}
		sub_6FAADA70(CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 0x38), 3, dword_6FBB5CF5, uVar3);
	}
	local_4f8.nX = 0;
	local_4f8.nY = 0;
	if ((dword_6FBB5CF9 != 0) && (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
	{
		if (dword_6FBB5CF9 == 0)
		{
			pDVar2 = nullptr;
		}
		else
		{
			pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		UNITS_GetClientCoords(pDVar2, &local_4f8);
		sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_4e8), (uint32_t*)(&iStack_4e4), (uint32_t*)(&iStack_4e0), (uint32_t*)(&iStack_4dc));
		sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_500), (uint32_t*)(&psStack_4fc));
		SetRect(&tStack_4d8, iStack_500, (int)psStack_4fc, (iStack_4e0 - iStack_4e8) + iStack_500,
		    (int)psStack_4fc + (iStack_4dc - iStack_4e4));
		local_4f8.nX = local_4f8.nX - tStack_4d8.left;
		local_4f8.nY = local_4f8.nY + (-0x96 - tStack_4d8.top);
		if (local_4f8.nY < 0x14)
		{
			local_4f8.nY = 0x14;
		}
	}
	dword_6FBB5D3B = (int)sub_6FAD6BE0(local_4f8.nX, local_4f8.nY, 0x6faf6bc0, 0x6faf6d50, 0, 0, 1, 0, 0, 0, 1);
	sub_6FAD7150(dword_6FBB5D3B, 1);
	if (dword_6FBB5CF9 == 0)
	{
		pDVar2 = nullptr;
	}
	else
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
	}
	pUVar4 = sub_6FB297F0(pDVar2);
	Unicode::strcpy(aUStack_4a0, pUVar4);
	Unicode::strlen(aUStack_4a0);
	sub_6FAD7180(dword_6FBB5D3B, aUStack_4a0, 0x15, 0, 4, 1, 0, 0);
	if ((dword_6FBB5CF9 != 0) && (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
	{
		iVar8 = 0;
		if (0 < dword_6FB7C4C0)
		{
			piVar6 = (int*)(&dword_6FB7BD70);
			do
			{
				if (*piVar6 == pDVar2->dwClassId)
				{
					if (iVar8 < 0)
					{
						return;
					}
					goto LAB_6faf68d6;
				}
				iVar8 = iVar8 + 1;
				piVar6 = (int*)((int)piVar6 + 0x27);
			} while (iVar8 < dword_6FB7C4C0);
		}
		iVar8 = 0;
	LAB_6faf68d6:
		if (iVar8 < dword_6FB7C4C0)
		{
			byte_6FBB5C3B = 1;
			iVar8 = iVar8 * 0x27;
			iStack_500 = 0;
			if (*(int*)((int)&dword_6FB7BD74 + iVar8) != 1 &&
			    -1 < *(int*)((int)&dword_6FB7BD74 + iVar8) + -1)
			{
				puStack_4f0 = (uint32_t*)((int)&ptr_6FB7BD82 + iVar8);
				psVar7 = (short*)((int)&word_6FB7BD78 + iVar8);
				do
				{
					pUVar4 = aUStack_400;
					iVar9 = 0x200;
					psStack_4fc = psVar7;
					do
					{
						pUVar4 = pUVar4 + 1;
						iVar9 = iVar9 + -1;
					} while (iVar9 != 0);
					index = *psVar7;
					iStack_4ec = 1;
					if (index == 0x1507)
					{
						pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2b0d));
						if ((short)word_6FB7A5BC != 0x421)
						{
							pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)word_6FB7A5BC));
						}
						uVar10 = dword_6FBB5D9C;
						a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x58a8));
						Unicode::sprintf(0x200, aUStack_400, a3, pUVar4, uVar10);
					LAB_6faf6b2a:
						sub_6FAD7180(dword_6FBB5D3B, aUStack_400, 0xf, 0, 0, 1, *puStack_4f0, iStack_4ec);
					}
					else
					{
						if (index != 0xd09)
						{
							if (index == 0xfb4)
							{
								bVar1 = false;
								iVar9 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, 4, 0);
								if ((iVar9 == 0) &&
								    (iVar9 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, 4, 1), iVar9 == 0))
								{
									bVar1 = true;
								}
								pDVar2 = CUNIT_GetPlayer();
								iVar9 = ITEMS_GetNoOfUnidItems(pDVar2);
								if (iVar9 == 0)
								{
									*(uint32_t*)((int)&dword_6FB7BD74 + iVar8) = 2;
									goto LAB_6faf6b50;
								}
								*(uint32_t*)((int)&dword_6FB7BD74 + iVar8) = 3;
								if (bVar1)
								{
									pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfb5));
									Unicode::strcpy(aUStack_400, pUVar4);
									wsprintfA((LPSTR)&iStack_4e8, "%d", iVar9 * 100);
									Unicode::win2Unicode(aUStack_4c8, (char*)&iStack_4e8, 9);
									Unicode::strcat(aUStack_400, aUStack_4c8);
									goto LAB_6faf6b2a;
								}
								index = 0xfb4;
							}
							pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
							Unicode::strcpy(aUStack_400, pUVar4);
							goto LAB_6faf6b2a;
						}
						nLayer = 0;
						iVar9 = 6;
						pDVar2 = CUNIT_GetPlayer();
						iVar9 = STATLIST_UnitGetStatValue(pDVar2, iVar9, nLayer);
						pDVar2 = CUNIT_GetPlayer();
						iVar5 = STATLIST_GetMaxLifeFromUnit(pDVar2);
						if (iVar9 < iVar5)
						{
							pDVar2 = CUNIT_GetPlayer();
							uVar3 = UNITS_GetHealingCost(pDVar2);
							if (uVar3 == 0)
							{
								uVar3 = 1;
							}
							pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(*psVar7));
							Unicode::strcpy(aUStack_400, pUVar4);
							wsprintfA((LPSTR)&tStack_4d8, "%d", uVar3);
							Unicode::win2Unicode(aUStack_4b4, (char*)&tStack_4d8, 9);
							Unicode::strcat(aUStack_400, aUStack_4b4);
							if (uVar3 == 0)
							{
								iStack_4ec = 0;
							}
							goto LAB_6faf6b2a;
						}
					}
				LAB_6faf6b50:
					iStack_500 = iStack_500 + 1;
					psVar7 = psStack_4fc + 1;
					puStack_4f0 = puStack_4f0 + 1;
					psStack_4fc = psVar7;
				} while (iStack_500 < *(int*)((int)&dword_6FB7BD74 + iVar8) + -1);
			}
			iVar9 = 1;
			pcVar13 = (code*)(sub_6FAF6BC0);
			uVar12 = 1;
			iVar8 = 0;
			uVar11 = 0;
			uVar10 = 0xf;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x102e));
			sub_6FAD7180(dword_6FBB5D3B, pUVar4, uVar10, uVar11, iVar8, uVar12, (int)(pcVar13), iVar9);
		}
	}
}

//D2Client.0x6FAF6BC0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF6BC0()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF6D50
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF6D50()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF6EE0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF6EE0()
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;

	sub_6FAB5D40();
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	sub_6FAD6DC0();
	uVar1 = dword_6FBB5CF5;
	dword_6FBB5D33 = 0;
	if (byte_6FBB5C3B == 0xc)
	{
		if (dword_6FBB5D01 == 5)
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				pDVar2 = CUNIT_GetPlayer();
				if (((pDVar2 != nullptr) && (pDVar2->dwUnitType == 0)) &&
				    (pDVar2->pPlayerData != nullptr))
				{
					pDVar2->pPlayerData->unk0xA8[0x2a] = 0;
					pDVar2->pPlayerData->unk0xA8[0x2b] = 0;
					pDVar2->pPlayerData->unk0xA8[0x2c] = 0;
					pDVar2->pPlayerData->unk0xA8[0x2d] = 0;
				}
			}
			if (uVar1 != dword_6FBB5CF5)
			{
				FOG_Trace("mismatch npc ids\n");
			}
			pDVar2 = sub_6FB269F0(uVar1, 1);
			if (pDVar2 != nullptr)
			{
				sub_6FAF78E0((int)pDVar2);
			}
			if (dword_6FBB5D80 != 0)
			{
				sub_6FB556A0(dword_6FBB5D84);
			}
			dword_6FBB5D80 = 0;
			dword_6FBB5D84 = 0;
			pDVar2 = sub_6FB269F0(uVar1, 1);
			if (pDVar2 != nullptr)
			{
				pDVar2->dwFlags = pDVar2->dwFlags | 2;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar1);
			sub_6FB1E710();
			dword_6FBB5CF9 = 0;
			sub_6FB23260(8, 1, 0);
			if (pDVar2 != nullptr)
			{
				sub_6FAFB6E0((int*)pDVar2, 1, 0);
				sub_6FB4F410(pDVar2, (int*)0x1);
			}
			sub_6FB23260(8, 1, 0);
			return 1;
		}
		sub_6FAF65C0();
		return 1;
	}
	D2_ASSERT(dword_6FBB5D01 != 6);
	D2_ASSERT(byte_6FBB5C3B != 8);
	byte_6FBB5C3B = 3;
	sub_6FAE9630();
	return 1;
}

//D2Client.0x6FAF70A0
void __fastcall sub_6FAF70A0(uint32_t a1)
{
	dword_6FBB5D62 = 0;
	sub_6FAADA70(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x38), 0, dword_6FBB5CF5, a1);
}

//D2Client.0x6FAF70C0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF70C0()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	sub_6FAADA70(D2C_ZEXT(0x38), 0, dword_6FBB5CF5, 0x28);
	return 1;
}

//D2Client.0x6FAF7260
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF7260()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	sub_6FAADA70(D2C_ZEXT(0x38), 0, dword_6FBB5CF5, 0x4b);
	return 1;
}

//D2Client.0x6FAF7400
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF7400()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	sub_6FAADA70(D2C_ZEXT(0x38), 0, dword_6FBB5CF5, 0x6d);
	return 1;
}

//D2Client.0x6FAF75A0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF75A0()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	sub_6FAADA70(D2C_ZEXT(0x38), 0, dword_6FBB5CF5, 0x28);
	return 1;
}

//D2Client.0x6FAF7740
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF7740()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	sub_6FAADA70(D2C_ZEXT(0x38), 0, dword_6FBB5CF5, 1);
	return 1;
}

//D2Client.0x6FAF78E0
void __fastcall sub_6FAF78E0(int a1)
{
	D2InventoryStrc* pInventory;
	uint32_t* puVar1;
	D2UnitStrc* pItem;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;

	puVar1 = dword_6FBB5C5D;
	do
	{
		*puVar1 = 0;
		puVar1 = puVar1 + 4;
	} while ((int)puVar1 < (int)&dword_6FBB5CFD);
	if ((a1 != 0) &&
	    (pInventory = *(D2InventoryStrc**)(a1 + 0x60), pInventory != nullptr))
	{
		pItem = INVENTORY_GetFirstItem(pInventory);
		while (pItem != nullptr)
		{
			pDVar2 = INVENTORY_GetNextItem(pItem);
			pDVar3 = INVENTORY_UnitIsItem(pItem);
			pItem = pDVar2;
			if (pDVar3 != nullptr)
			{
				sub_6FB26BE0(pDVar3->dwUnitId, pDVar3->dwUnitType);
			}
		}
		INVENTORY_RemoveInventoryItems(pInventory);
		D2COMMON_10251_Return((int)pInventory);
	}
}

//D2Client.0x6FAF7950
void __fastcall sub_6FAF7950(uint32_t a1)
{
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	uint32_t* puVar4;

	if (a1 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar1 = sub_6FB269F0(a1, 1);
	if (pDVar1 != nullptr)
	{
		puVar4 = dword_6FBB5C5D;
		do
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 4;
		} while ((int)puVar4 < (int)&dword_6FBB5CFD);
		pInventory = pDVar1->pInventory;
		if (pInventory != nullptr)
		{
			pDVar1 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar1 != nullptr)
			{
				pDVar2 = INVENTORY_GetNextItem(pDVar1);
				pDVar3 = INVENTORY_UnitIsItem(pDVar1);
				pDVar1 = pDVar2;
				if (pDVar3 != nullptr)
				{
					sub_6FB26BE0(pDVar3->dwUnitId, pDVar3->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
}

//D2Client.0x6FAF7A00
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAF7A00()
{
	int iVar1;
	D2UnitStrc* in_ECX;

	if ((((in_ECX != nullptr) && (iVar1 = in_ECX->dwClassId, -1 < iVar1)) &&
	        (iVar1 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
	    ((iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar1 * 0x1a8, iVar1 != 0 &&
	                                                                                       (((uint32_t) * (uint8_t*)(iVar1 + 0xd) & *(uint32_t*)((uint8_t*)&gdwBitMasks)) != 0))))
	{
		sub_6FB5BEC0(in_ECX, 0, 0x48);
	}
}

//D2Client.0x6FAF7A60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF7A60()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF7BD0
void __cdecl sub_6FAF7BD0()
{
	int iVar1;
	uint32_t* puVar2;
	char acStack_104[260];

	dword_6FBB5D8C = 0;
	dword_6FBB5D88 = 0;
	GetTickCount();
	puVar2 = (uint32_t*)&byte_6FBB5C38;
	for (iVar1 = 0x57; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	gpBitBuffer_6FBB5D13 = QUESTRECORD_AllocRecord(nullptr);
	gpBitBuffer_6FBB5D17 = QUESTRECORD_AllocRecord(nullptr);
	byte_6FBB5C3B = 0;
	sprintf(acStack_104, "%s\\ui\\panel\\buysell", "DATA\\GLOBAL");
	gpCellFile_6FBB5D98 = CLIENT_LoadCellFile(acStack_104, 0);
	sprintf(acStack_104, "%s\\ui\\menu\\goldbtn", "DATA\\GLOBAL");
	gpCellFile_6FBB5BCC = CLIENT_LoadCellFile(acStack_104, 0);
	dword_6FBB5BDD = 0;
	byte_6FBB5BD0 = '\0';
	byte_6FBB5BE1 = 0;
	dword_6FBB5BD9 = 0;
}

//D2Client.0x6FAF7C90
void __cdecl sub_6FAF7C90()
{
	QUESTRECORD_FreeRecord(nullptr, gpBitBuffer_6FBB5D13);
	QUESTRECORD_FreeRecord(nullptr, gpBitBuffer_6FBB5D17);
	gpBitBuffer_6FBB5D13 = nullptr;
	gpBitBuffer_6FBB5D17 = nullptr;
	if (gpCellFile_6FBB5D98 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5D98);
		gpCellFile_6FBB5D98 = nullptr;
	}
	if (gpCellFile_6FBB5BCC != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5BCC);
		gpCellFile_6FBB5BCC = nullptr;
	}
	if (gpuint32_t_6FBB5D4F != nullptr)
	{
		(**(code**)*gpuint32_t_6FBB5D4F)(1);
		gpuint32_t_6FBB5D4F = nullptr;
	}
	if (dword_6FBB5D2F != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D2F = 0;
	}
	if (dword_6FBB5D33 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D33 = 0;
	}
	if (dword_6FBB5D37 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D37 = 0;
	}
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
	}
	if (dword_6FBB5D43 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D43 = 0;
	}
	if (dword_6FBB5D47 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D47 = 0;
	}
	if (dword_6FBB5D3F != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3F = 0;
	}
}

//D2Client.0x6FAF7D90
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF7D90(D2UnitStrc* pUnit)
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	uint32_t extraout_ECX;
	char* pcVar4;
	int iVar5;

	pDVar3 = CUNIT_GetPlayer();
	if (pUnit == pDVar3)
	{
		iVar5 = 0;
		if (0 < dword_6FB7BD6C)
		{
			pcVar4 = (char*)(&byte_6FB7B989);
			do
			{
				if (*pcVar4 == '\x01')
				{
					*pcVar4 = '\0';
					pDVar3 = CUNIT_GetPlayer();
					D2_ASSERT(pDVar3 != nullptr);
					sub_6FAF44C0((int)(pcVar4 + -0x11));
				}
				iVar1 = dword_6FB7BD6C;
				pcVar4[4] = '\x01';
				iVar5 = iVar5 + 1;
				pcVar4 = pcVar4 + 0x16;
			} while (iVar5 < iVar1);
		}
		if (dword_6FBB5CF9 != 0)
		{
			pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
			if (pDVar3 != nullptr)
			{
				byte_6FBB5C3B = 0;
				sub_6FAE8F10();
				uVar2 = dword_6FBB5CF5;
				pDVar3 = CUNIT_GetPlayer();
				if (pDVar3 != nullptr)
				{
					pDVar3 = CUNIT_GetPlayer();
					if (((pDVar3 != nullptr) && (pDVar3->dwUnitType == 0)) &&
					    (pDVar3->pPlayerData != nullptr))
					{
						pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
						pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
						pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
						pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
					}
				}
				if (uVar2 != dword_6FBB5CF5)
				{
					FOG_Trace("mismatch npc ids\n");
				}
				pDVar3 = sub_6FB269F0(uVar2, 1);
				if (pDVar3 != nullptr)
				{
					sub_6FAF78E0((int)pDVar3);
				}
				if (dword_6FBB5D80 != 0)
				{
					sub_6FB556A0(dword_6FBB5D84);
				}
				dword_6FBB5D80 = 0;
				dword_6FBB5D84 = 0;
				pDVar3 = sub_6FB269F0(uVar2, 1);
				if (pDVar3 != nullptr)
				{
					pDVar3->dwFlags = pDVar3->dwFlags | 2;
				}
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
				sub_6FB1E710();
				dword_6FBB5CF9 = 0;
				sub_6FB23260(8, 1, 0);
				if (pDVar3 != nullptr)
				{
					sub_6FAFB6E0((int*)pDVar3, 1, 0);
					sub_6FB4F410(pDVar3, (int*)0x1);
				}
				sub_6FB23260(8, 1, 0);
				dword_6FBB5CF9 = 0;
			}
		}
	}
}

//D2Client.0x6FAF7F40
void __fastcall sub_6FAF7F40(int ptCmd)
{
	D2UnitStrc* pDVar1;

	D2_ASSERT(ptCmd);
	if (*(short*)(ptCmd + 1) == 3)
	{
		if (dword_6FBB5CF9 != 0)
		{
			pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			if (pDVar1 != nullptr)
			{
				if (dword_6FBB5D09 == 1)
				{
					FOG_Trace("%d %s\n", __LINE__, __FILE__);
				}
				dword_6FBB5D09 = 1;
				byte_6FBB5D0D = *(uint16_t*)(ptCmd + 1);
				return;
			}
		}
	}
	else
	{
		FOG_Trace("%d %s\n", __LINE__, __FILE__);
	}
}

//D2Client.0x6FAF7FE0
void __fastcall sub_6FAF7FE0(uint8_t* a1)
{
	QUESTRECORD_CopyBufferToRecord(gpBitBuffer_6FBB5D17, a1, 0x60, 0);
}

//D2Client.0x6FAF8000
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF8000(uint8_t a1, uint32_t a2)
{
	uint32_t uVar1;
	D2UnitStrc* pDVar2;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	char* szFormat;

	pDVar2 = nullptr;
	if (a1 < 6)
	{
		pDVar2 = sub_6FB269F0(a2, (uint32_t)a1);
	}
	switch (a1)
	{
	case 1:
		break;
	case 2:
	case 4:
	case 6:
		sub_6FB23800(1, 0);
		return;
	default:
		goto switchD_6faf802f_caseD_3;
	}
	if (pDVar2 != nullptr)
	{
		pDVar2->dwFlags = pDVar2->dwFlags | 2;
	}
	if (byte_6FBB5C3B == 1)
	{
		szFormat = "SCMD_INTERACTION_STOP while menus active";
	LAB_6faf8165:
		byte_6FBB5C39 = '\0';
		FOG_Trace(szFormat);
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		uVar1 = dword_6FBB5CF5;
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 != nullptr)
		{
			pDVar2 = CUNIT_GetPlayer();
			sub_6FAFBB10((int*)pDVar2);
		}
		sub_6FAF7950(uVar1);
		pDVar2 = sub_6FB269F0(uVar1, 1);
		if (pDVar2 != nullptr)
		{
			pDVar2->dwFlags = pDVar2->dwFlags | 2;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x30), 1, uVar1);
		sub_6FB1E710();
		sub_6FAF3DC0(0);
		sub_6FB23260(8, 1, 0);
		if (pDVar2 != nullptr)
		{
			sub_6FAFB6E0((int*)pDVar2, 1, 0);
			sub_6FB4F410(pDVar2, (int*)0x1);
		}
		sub_6FB23260(8, 1, 0);
	}
	else
	{
		if ((2 < byte_6FBB5C3B) && (byte_6FBB5C3B < 7))
		{
			sub_6FB23260(0xc, 1, 0);
			byte_6FBB5C3B = 0;
			sub_6FAE8F10();
			uVar1 = dword_6FBB5CF5;
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 != nullptr)
			{
				pDVar2 = CUNIT_GetPlayer();
				sub_6FAFBB10((int*)pDVar2);
			}
			sub_6FAF7950(uVar1);
			pDVar2 = sub_6FB269F0(uVar1, 1);
			if (pDVar2 != nullptr)
			{
				pDVar2->dwFlags = pDVar2->dwFlags | 2;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar1);
			sub_6FB1E710();
			sub_6FAF3DC0(0);
			sub_6FB23260(8, 1, 0);
			if (pDVar2 != nullptr)
			{
				sub_6FAFB6E0((int*)pDVar2, 1, 0);
				sub_6FB4F410(pDVar2, (int*)0x1);
			}
			sub_6FB23260(8, 1, 0);
			sub_6FAED220();
			FOG_Trace("SCMD_INTERACTION_STOP");
			sub_6FAF6340();
			byte_6FBB5C3B = 0;
			return;
		}
		if (byte_6FBB5C3B == 7)
		{
			sub_6FB249D0();
			sub_6FAF6340();
			byte_6FBB5C3B = 0;
			return;
		}
		if (byte_6FBB5C39 != '\0')
		{
			szFormat = "SCMD_INTERACTION_STOP while text active";
			goto LAB_6faf8165;
		}
	}
	sub_6FAF6340();
	byte_6FBB5C3B = 0;
switchD_6faf802f_caseD_3:
}

//D2Client.0x6FAF8250
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF8250(uint8_t a1, uint32_t a2, uint8_t* a3, uint32_t a4)
{
	uint32_t uVar1;
	char cVar2;
	uint16_t uVar3;
	uint16_t uVar4;
	D2UnitStrc* pDVar5;
	D2TextHeaderStrc* pDVar6;
	uint16_t extraout_var;
	int iVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	D2PlayerDataStrc* extraout_ECX;
	D2PlayerDataStrc* pDVar10;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t uVar11;
	int extraout_ECX_03;
	int extraout_ECX_04;
	int extraout_ECX_05;
	float fVar12;
	float fVar13;
	int iVar14;

	if (a1 == 6)
	{
		QUESTRECORD_CopyBufferToRecord(gpBitBuffer_6FBB5D13, a3, 0x60, 0);
		return;
	}
	pDVar5 = sub_6FB269F0(a2, (uint32_t)a1);
	if (pDVar5 == nullptr)
	{
		pDVar5 = CUNIT_GetPlayer();
		pDVar10 = extraout_ECX;
		if (((pDVar5 != nullptr) && (pDVar5->dwUnitType == 0)) &&
		    (pDVar10 = pDVar5->pPlayerData, pDVar10 != nullptr))
		{
			pDVar10->unk0xA8[0x2a] = 0;
			pDVar5->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar10 = pDVar5->pPlayerData;
			pDVar10->unk0xA8[0x2c] = 0;
			pDVar5->pPlayerData->unk0xA8[0x2d] = 0;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)pDVar10 >> 8), 0x30), a4 & 0xff, a2);
		if (a2 != dword_6FBB5CF5)
		{
			FOG_Trace("mismatch npc ids\n");
		}
		pDVar5 = sub_6FB269F0(a2, 1);
		if (pDVar5 != nullptr)
		{
			sub_6FAF78E0((int)pDVar5);
		}
		if (dword_6FBB5D80 != 0)
		{
			sub_6FB556A0(dword_6FBB5D84);
		}
		dword_6FBB5D80 = 0;
		dword_6FBB5D84 = 0;
		return;
	}
	sub_6FB29750((uint8_t*)(sub_6FAF7A00));
	pDVar5->dwFlags = pDVar5->dwFlags | 2;
	QUESTRECORD_CopyBufferToRecord(gpBitBuffer_6FBB5D13, a3, 0x60, 0);
	sub_6FAF9010(0xb);
	sub_6FAF9010(0xd);
	sub_6FAF9010(0xf);
	sub_6FAF9040(3);
	sub_6FAF9010(0x2b);
	if ((code*)gpuint8_t_6FB7C413 == (code*)(sub_6FAF8E80))
	{
		byte_6FB7C401 = 3;
	}
	sub_6FAF9040(0x27);
	sub_6FAF9070(0x29);
	sub_6FAF9010(0x15);
	byte_6FB7C0AD = 0;
	byte_6FB7C0B9 = 0;
	sub_6FAF90A0(0x10);
	sub_6FAF90A0(0x11);
	sub_6FAF90A0(0x12);
	sub_6FAF90A0(0x13);
	sub_6FAF90A0(0x26);
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x2f), (uint32_t)a1, a2);
	sub_6FAABF30();
	if (byte_6FBB5C38 != '\0')
	{
		byte_6FBB5C39 = 1;
		dword_6FBB5CF9 = 1;
		dword_6FBB5CF5 = pDVar5->dwUnitId;
		dword_6FBB5CFD = pDVar5->dwClassId;
		pDVar5->dwFlags = pDVar5->dwFlags & 0xfffffffd;
		return;
	}
	pDVar6 = sub_6FB1E6B0();
	if (pDVar6 == nullptr)
	{
		FOG_DisplayAssert("hTextList != NULL", __FILE__, __LINE__);
		exit(-1);
	}
	uVar3 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar6, 0);
	iVar7 = sub_6FAAE570(pDVar5->dwClassId);
	if ((((iVar7 != 0) && (((uint32_t) * (uint8_t*)(iVar7 + 0xd) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) != 0)) &&
	        ((iVar7 = pDVar5->dwClassId, iVar7 != 0x219 && ((iVar7 != 0x21a && (iVar7 != 0x21b)))))) &&
	    (iVar7 != 0x20f))
	{
		sub_6FB29100(pDVar5);
	}
	pDVar8 = CUNIT_GetPlayer();
	pDVar8 = INVENTORY_GetCursorItem(pDVar8->pInventory);
	if (pDVar8 != nullptr)
	{
		dword_6FBB5CF9 = 1;
		uVar1 = pDVar5->dwUnitId;
		dword_6FBB5CFD = pDVar5->dwClassId;
		dword_6FBB5CF5 = uVar1;
		pDVar5 = CUNIT_GetPlayer();
		if (pDVar5 != nullptr)
		{
			pDVar5 = CUNIT_GetPlayer();
			sub_6FAFBB10((int*)pDVar5);
		}
		sub_6FAF7950(uVar1);
		pDVar5 = sub_6FB269F0(uVar1, 1);
		uVar11 = extraout_ECX_01;
		if (pDVar5 != nullptr)
		{
			sub_6FAFA230((int)pDVar5, 2, 1);
			uVar11 = extraout_ECX_02;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar11 >> 8), 0x30), 1, uVar1);
		sub_6FB1E710();
		sub_6FAF3DC0(0);
		sub_6FB23260(8, 1, 0);
		if (pDVar5 != nullptr)
		{
			sub_6FAFB6E0((int*)pDVar5, 1, 0);
			sub_6FB4F410(pDVar5, (int*)0x1);
		}
	LAB_6faf88d8:
		sub_6FB23260(8, 1, 0);
		return;
	}
	word_6FBB5D7A = 0;
	if (uVar3 != 0xffff)
	{
		sub_6FB23800(0, 0);
		word_6FBB5C47 = uVar3;
		sub_6FB1CC20(pDVar5, D2C_ZEXT(uVar3), 1);
		if (word_6FBB5D7A < 9)
		{
			(&word_6FBB5D66)[word_6FBB5D7A] = uVar3;
			word_6FBB5D7A = word_6FBB5D7A + 1;
		}
		iVar7 = 0;
		if (0 < dword_6FB7C4D4)
		{
			do
			{
				if (word_6FB7C4C8[iVar7 * 4] == uVar3)
				{
					uVar4 = word_6FB7C4C8[iVar7 * 4 + 1];
					iVar7 = dword_6FB7C4D4;
					goto LAB_6faf864a;
				}
				iVar7 = iVar7 + 1;
			} while (iVar7 < dword_6FB7C4D4);
		}
		pDVar6 = sub_6FB1E6B0();
		a3 = nullptr;
		uVar4 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar6, 0);
		iVar7 = extraout_ECX_03;
		while (uVar4 != 0xffff)
		{
			if (((uVar4 != uVar3) && (uVar4 != 0xffff)) &&
			    (iVar9 = sub_6FAF8940(uVar4), iVar7 = extraout_ECX_04, (char)iVar9 != '\0'))
				goto LAB_6faf864a;
			a3 = (uint8_t*)((int)a3 + 1);
			uVar4 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar6, (int)a3);
			iVar7 = extraout_ECX_05;
		}
		uVar4 = 0xffff;
	LAB_6faf864a:
		word_6FBB5C49 = uVar4;
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar7 >> 8), 0x31), pDVar5->dwUnitId, (uint32_t)uVar3);
		byte_6FBB5C39 = 1;
		sub_6FB1CBD0((uint8_t*)(sub_6FAF89E0), 0);
		dword_6FBB5CF9 = 1;
		dword_6FBB5CF5 = pDVar5->dwUnitId;
		dword_6FBB5CFD = pDVar5->dwClassId;
		dword_6FBB5D7C = 0;
		return;
	}
	uVar3 = TEXT_GetStringIdOfMenuType0Or2Node(pDVar6, 0);
	if (pDVar5->dwClassId != 0x20f)
	{
		sub_6FB291C0((int*)pDVar5);
	}
	if (pDVar5->pDynamicPath != nullptr)
	{
		D2Common_10153(pDVar5->pDynamicPath);
	}
	if (uVar3 == 0xffff)
	{
		iVar7 = sub_6FAAE570(pDVar5->dwClassId);
		if ((iVar7 != 0) && (((uint32_t) * (uint8_t*)(iVar7 + 0xd) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4)) != 0))
		{
			cVar2 = sub_6FAF8970(pDVar5->dwClassId);
			if (cVar2 == '\0')
			{
				sub_6FAE8F10();
				sub_6FB23800(0, 0);
				sub_6FAF98D0(pDVar5, 0);
				dword_6FBB5D7C = 0;
				return;
			}
			dword_6FBB5CF9 = 1;
			dword_6FBB5CF5 = pDVar5->dwUnitId;
			dword_6FBB5CFD = pDVar5->dwClassId;
			sub_6FAFBB60(dword_6FBB5CF5);
			goto LAB_6faf88d8;
		}
		sub_6FAFBB60(dword_6FBB5CF5);
		sub_6FB23260(8, 1, 0);
	}
	else
	{
		sub_6FAE8F10();
		sub_6FB23800(0, 0);
		iVar7 = 0;
		word_6FBB5C47 = uVar3;
		if (0 < dword_6FB7C4D4)
		{
			do
			{
				if (word_6FB7C4C8[iVar7 * 4] == uVar3)
				{
					uVar4 = word_6FB7C4C8[iVar7 * 4 + 1];
					goto LAB_6faf875f;
				}
				iVar7 = iVar7 + 1;
			} while (iVar7 < dword_6FB7C4D4);
		}
		pDVar6 = sub_6FB1E6B0();
		iVar7 = 0;
		uVar4 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar6, 0);
		while (uVar4 != 0xffff)
		{
			if (((uVar4 != uVar3) && (uVar4 != 0xffff)) &&
			    (iVar9 = sub_6FAF8940(uVar4), (char)iVar9 != '\0'))
				goto LAB_6faf875f;
			iVar7 = iVar7 + 1;
			uVar4 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar6, iVar7);
		}
		uVar4 = 0xffff;
	LAB_6faf875f:
		word_6FBB5C49 = uVar4;
		sub_6FAABF30();
		pDVar8 = sub_6FAF3930();
		if (pDVar8 != nullptr)
		{
			sub_6FAF7A60();
			dword_6FBB5D7C = 0;
			return;
		}
		uVar3 = 0;
		iVar7 = 0xe;
		byte_6FBB5C3B = 1;
		dword_6FBB5D01 = 0;
		pDVar8 = CUNIT_GetPlayer();
		byte_6FBB5C43 = STATLIST_UnitGetStatValue(pDVar8, iVar7, uVar3);
		sub_6FB23800(0, 0);
		sub_6FAABF30();
		pDVar8 = sub_6FAF3930();
		D2_ASSERT(pDVar8 == nullptr);
		sub_6FAF3DC0((int)pDVar5);
		iVar7 = 0;
		pDVar8 = sub_6FAF3930();
		sub_6FAFA230((int)pDVar8, 2, iVar7);
		iVar7 = sub_6FB23260(8, 2, 0);
		if (iVar7 == 0)
		{
			sub_6FAF7A60();
			dword_6FBB5D7C = 0;
			return;
		}
		sub_6FAF90D0();
		iVar7 = sub_6FAF8E40();
		if ((&byte_6FB7B98D)[iVar7 * 0x16] != '\0')
		{
			pDVar8 = sub_6FAF3930();
			iVar9 = sub_6FB464A0((int)pDVar8, 1);
			if (iVar9 != 0)
			{
				sub_6FB50290(pDVar5);
				iVar14 = 0;
				fVar13 = 1.4013e-45;
				fVar12 = 0.0;
				pDVar5 = CUNIT_GetPlayer();
				sub_6FB55820(iVar9, pDVar5, fVar12, fVar13, iVar14);
			}
			(&byte_6FB7B98D)[iVar7 * 0x16] = 0;
			dword_6FBB5D7C = 0;
			return;
		}
	}
	dword_6FBB5D7C = 0;
}

//D2Client.0x6FAF8940
int __fastcall sub_6FAF8940(short a1)
{
	uint32_t uVar1;
	int iVar2;

	iVar2 = 0;
	uVar1 = (uint32_t)(uint8_t)(word_6FBB5D7A >> 8);
	if (word_6FBB5D7A != 0)
	{
		do
		{
			if ((&word_6FBB5D66)[iVar2] == a1)
			{
				return (uint32_t)uVar1 << 8;
			}
			iVar2 = iVar2 + 1;
		} while (iVar2 < (int)(uint32_t)word_6FBB5D7A);
	}
	return CONCAT31(uVar1, 1);
}

//D2Client.0x6FAF8970
uint8_t __fastcall sub_6FAF8970(int a1)
{
	if (((((a1 != 0x92) && (a1 != 0x20f)) && (a1 != 0x219)) &&
	        (((a1 != 0x21a && (a1 != 0x21b)) &&
	            ((a1 != 0x209 && ((a1 != 0x10a && (a1 != 0x17a)))))))) &&
	    ((a1 != 0xfb &&
	        ((((a1 != 0x179 && (a1 != 0x14b)) && (a1 != 0x196)) && (a1 != 0x198))))))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FAF89E0
// TODO: decompilation needs review (extraout, in_reg)
uint32_t __cdecl sub_6FAF89E0(int a1)
{
	uint16_t uVar1;
	uint16_t uVar2;
	int iVar3;
	D2TextHeaderStrc* pDVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	uint16_t extraout_CX;
	uint16_t extraout_CX_00;
	uint32_t in_ECX;
	int* piVar7;
	int in_EDX;
	uint16_t extraout_var;
	uint16_t extraout_var_00;
	uint16_t uVar8;

	uVar1 = word_6FBB5C47;
	iVar3 = 0;
	if (0 < dword_6FB7C4D4)
	{
		do
		{
			if (word_6FB7C4C8[iVar3 * 4] == word_6FBB5C47)
			{
				uVar2 = word_6FB7C4C8[iVar3 * 4 + 1];
				goto LAB_6faf8a6e;
			}
			iVar3 = iVar3 + 1;
		} while (iVar3 < dword_6FB7C4D4);
	}
	pDVar4 = sub_6FB1E6B0();
	iVar3 = 0;
	uVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar4, 0);
	while (uVar2 != 0xffff)
	{
		if (((uVar2 != uVar1) && (uVar2 != 0xffff)) &&
		    (iVar5 = sub_6FAF8940(uVar2), uVar2 = extraout_CX, (char)iVar5 != '\0'))
			goto LAB_6faf8a6e;
		iVar3 = iVar3 + 1;
		uVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar4, iVar3);
	}
	uVar2 = 0xffff;
LAB_6faf8a6e:
	word_6FBB5C49 = uVar2;
	if (word_6FBB5C47 == 0x251)
	{
		sub_6FB55820(0xf1, nullptr, 0.0, 0.0, 0);
	}
	if (word_6FBB5C47 == 0x21a)
	{
		sub_6FB55820(0xed, nullptr, 0.0, 0.0, 0);
	}
	if (byte_6FBB5C39 != '\x01')
	{
		byte_6FBB5C39 = 0;
		sub_6FB1CBD0(0, in_ECX);
		word_6FBB5C47 = 0xffff;
		sub_6FAF90D0();
		return 0;
	}
	if (((word_6FBB5C49 != 0xffff) && (dword_6FBB5CF9 != 0)) &&
	    (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 != nullptr))
	{
		word_6FBB5C4B = word_6FBB5C49;
		if (dword_6FBB5CF9 == 0)
		{
			pDVar6 = nullptr;
			uVar8 = extraout_var;
		}
		else
		{
			pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1);
			uVar8 = extraout_var_00;
		}
		sub_6FB1CC20(pDVar6, CONCAT22(uVar8, word_6FBB5C4B), 1);
		if (word_6FBB5D7A < 9)
		{
			(&word_6FBB5D66)[word_6FBB5D7A] = word_6FBB5C4B;
			word_6FBB5D7A = word_6FBB5D7A + 1;
		}
		sub_6FB1CBD0((uint8_t*)(sub_6FAF89E0), 0);
		word_6FBB5C47 = word_6FBB5C4B;
		sub_6FAADA40(CONCAT31((uint32_t)(uint8_t)(word_6FBB5C4B >> 8), 0x31), dword_6FBB5CF5, (uint32_t)word_6FBB5C4B);
		uVar1 = word_6FBB5C4B;
		iVar3 = 0;
		if (0 < dword_6FB7C4D4)
		{
			do
			{
				if (word_6FB7C4C8[iVar3 * 4] == word_6FBB5C4B)
				{
					word_6FBB5C49 = word_6FB7C4C8[iVar3 * 4 + 1];
					return 1;
				}
				iVar3 = iVar3 + 1;
			} while (iVar3 < dword_6FB7C4D4);
		}
		pDVar4 = sub_6FB1E6B0();
		iVar3 = 0;
		uVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar4, 0);
		while (true)
		{
			if (uVar2 == 0xffff)
			{
				word_6FBB5C49 = 0xffff;
				return 1;
			}
			if (((uVar2 != uVar1) && (uVar2 != 0xffff)) &&
			    (iVar5 = sub_6FAF8940(uVar2), (char)iVar5 != '\0'))
				break;
			iVar3 = iVar3 + 1;
			uVar2 = TEXT_GetStringIdOfMenuType1Or2Node(pDVar4, iVar3);
		}
		word_6FBB5C49 = extraout_CX_00;
		return 1;
	}
	byte_6FBB5C39 = 0;
	sub_6FB1CBD0(0, 0);
	if ((dword_6FBB5CF9 == 0) || (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
	{
		iVar3 = -1;
	}
	else
	{
		iVar3 = 0;
		if (0 < dword_6FB7C4C0)
		{
			piVar7 = (int*)(&dword_6FB7BD70);
			do
			{
				if (*piVar7 == pDVar6->dwClassId)
					goto LAB_6faf8c82;
				iVar3 = iVar3 + 1;
				piVar7 = (int*)((int)piVar7 + 0x27);
			} while (iVar3 < dword_6FB7C4C0);
		}
		iVar3 = 0;
	}
LAB_6faf8c82:
	if ((((((in_EDX == 0) || (a1 == 0)) && (dword_6FBB5CFD != 0x92)) &&
	         (((dword_6FBB5CFD != 0x20f && (dword_6FBB5CFD != 0x219)) &&
	             ((dword_6FBB5CFD != 0x21a && ((dword_6FBB5CFD != 0x21b && (dword_6FBB5CFD != 0x209)))))))) &&
	        (dword_6FBB5CFD != 0x10a)) &&
	    (((((((dword_6FBB5CFD != 0x17a && (dword_6FBB5CFD != 0xfb)) && (dword_6FBB5CFD != 0x179)) &&
	            ((dword_6FBB5CFD != 0x14b && (dword_6FBB5CFD != 0x196)))) &&
	           ((dword_6FBB5CFD != 0x198 && ((-1 < iVar3 && (dword_6FBB5CF9 != 0)))))) &&
	          ((pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 != nullptr &&
	                                                          (((iVar3 < dword_6FB7C4C0 && (byte_6FB7BD92[iVar3 * 0x27 + 4] != '\0')) &&
	                                                              (byte_6FBB5C3B = 1, dword_6FBB5CF9 != 0)))))) &&
	        (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 != nullptr))))
	{
		if (dword_6FBB5CF9 == 0)
		{
			pDVar6 = nullptr;
		}
		else
		{
			pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		sub_6FAF98D0(pDVar6, 1);
		return 1;
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	sub_6FAFBB60(dword_6FBB5CF5);
	sub_6FB23260(8, 1, 0);
	return 0;
}

//D2Client.0x6FAF8E40
int __cdecl sub_6FAF8E40()
{
	bool bVar1;
	int iVar2;
	uint32_t* puVar3;

	iVar2 = 0;
	bVar1 = false;
	if (0 < dword_6FB7BD6C)
	{
		puVar3 = dword_6FB7B978;
		do
		{
			if (bVar1)
				break;
			if (*puVar3 == dword_6FBB5CFD)
			{
				bVar1 = true;
			}
			else
			{
				iVar2 = iVar2 + 1;
				puVar3 = (uint32_t*)((int)puVar3 + 0x16);
			}
		} while (iVar2 < dword_6FB7BD6C);
		if (bVar1)
		{
			return iVar2;
		}
	}
	return 0;
}

//D2Client.0x6FAF8E80
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF8E80()
{
	D2UnitStrc* pDVar1;
	DWORD DVar2;
	Unicode* pUVar3;
	int extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	int iStack_30;
	int iStack_2c;
	D2CoordStrc local_28;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	tagRECT tStack_10;

	iVar6 = dword_6FBB5D3B;
	if (dword_6FBB5D3B != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D3B = 0;
		iVar6 = extraout_ECX;
	}
	sub_6FAADA20(CONCAT31((int32_t)((uint32_t)iVar6 >> 8), 0x62), dword_6FBB5CF5);
	byte_6FBB5C3B = 10;
	local_28.nX = 0;
	local_28.nY = 0;
	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			UNITS_GetClientCoords(pDVar1, &local_28);
			sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_20), (uint32_t*)(&iStack_1c), (uint32_t*)(&iStack_18), (uint32_t*)(&iStack_14));
			sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_2c), (uint32_t*)(&iStack_30));
			SetRect(&tStack_10, iStack_2c, iStack_30, (iStack_18 - iStack_20) + iStack_2c,
			    (iStack_30 - iStack_1c) + iStack_14);
			local_28.nY = local_28.nY + (-0x96 - tStack_10.top);
			local_28.nX = local_28.nX - tStack_10.left;
			if (local_28.nY < 0x14)
			{
				local_28.nY = 0x14;
			}
		}
	}
	dword_6FBB5D37 = (int)sub_6FAD6BE0(local_28.nX, local_28.nY, 0x6fb24f70, 0, 0, 0, 1, 0, 0, 0, 1);
	DVar2 = GetTickCount();
	dword_6FBB5D23 = DVar2 + 60000;
	dword_6FBB5D27 = 0;
	sub_6FAD7150(dword_6FBB5D37, 0);
	iVar9 = 0;
	uVar8 = 0;
	uVar7 = 1;
	iVar6 = 0;
	uVar5 = 0;
	uVar4 = 0xf;
	pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd19));
	sub_6FAD7180(dword_6FBB5D37, pUVar3, uVar4, uVar5, iVar6, uVar7, uVar8, iVar9);
	return 1;
}

//D2Client.0x6FAF9010
void __fastcall sub_6FAF9010(int a1)
{
	int iVar1;

	iVar1 = a1 * 0x27;
	*(uint32_t*)((int)&dword_6FB7BD74 + iVar1) = 2;
	*(uint16_t*)(byte_6FB7BD7C + iVar1) = 0;
	*(uint32_t*)(byte_6FB7BD8A + iVar1) = 0;
}

//D2Client.0x6FAF9040
void __fastcall sub_6FAF9040(int a1)
{
	int iVar1;

	iVar1 = a1 * 0x27;
	*(uint32_t*)((int)&dword_6FB7BD74 + iVar1) = 3;
	*(uint16_t*)(byte_6FB7BD7E + iVar1) = 0;
	*(uint32_t*)(byte_6FB7BD8E + iVar1) = 0;
}

//D2Client.0x6FAF9070
void __fastcall sub_6FAF9070(int a1)
{
	int iVar1;

	iVar1 = a1 * 0x27;
	*(uint32_t*)((int)&dword_6FB7BD74 + iVar1) = 4;
	*(uint16_t*)(byte_6FB7BD80 + iVar1) = 0;
	*(uint32_t*)(byte_6FB7BD92 + iVar1) = 0;
}

//D2Client.0x6FAF90A0
void __fastcall sub_6FAF90A0(int a1)
{
	int iVar1;

	iVar1 = a1 * 0x27;
	*(uint16_t*)(byte_6FB7BD7A + iVar1) = 0xfb4;
	*(code**)((int)&ptr_6FB7BD86 + iVar1) = (code*)(sub_6FAF5EB0);
	*(uint32_t*)((int)&dword_6FB7BD74 + iVar1) = 3;
}

//D2Client.0x6FAF90D0
void __cdecl sub_6FAF90D0()
{
	uint64_t DVar1;
	D2UnitStrc* pDVar2;
	Unicode* pUVar3;
	uint16_t uVar4;
	int iVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	code* pcVar10;
	D2CoordStrc local_d0;
	int iStack_c8;
	int iStack_c4;
	int iStack_c0;
	int iStack_bc;
	int iStack_b8;
	int iStack_b4;
	tagRECT tStack_b0;
	Unicode aUStack_a0[80];

	if ((dword_6FBB5CF9 != 0) && (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
	{
		if (dword_6FBB5D47 == 0)
		{
			local_d0.nX = 0;
			local_d0.nY = 0;
			if ((dword_6FBB5CF9 != 0) &&
			    (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
			{
				if (dword_6FBB5CF9 == 0)
				{
					pDVar2 = nullptr;
				}
				else
				{
					pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
				}
				UNITS_GetClientCoords(pDVar2, &local_d0);
				sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_c8), (uint32_t*)(&iStack_c4), (uint32_t*)(&iStack_c0), (uint32_t*)(&iStack_bc));
				sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_b8), (uint32_t*)(&iStack_b4));
				SetRect(&tStack_b0, iStack_b8, iStack_b4, (iStack_c0 - iStack_c8) + iStack_b8,
				    (iStack_b4 - iStack_c4) + iStack_bc);
				local_d0.nY = local_d0.nY + (-0x96 - tStack_b0.top);
				local_d0.nX = local_d0.nX - tStack_b0.left;
				if (local_d0.nY < 0x14)
				{
					local_d0.nY = 0x14;
				}
			}
			dword_6FBB5D47 = (int)sub_6FAD6BE0(local_d0.nX, local_d0.nY, 0x6faf93d0, 0x6faf9570, 0, 0, 1, 0, 0, 0, 1);
			sub_6FAD7150(dword_6FBB5D47, 1);
			if (dword_6FBB5CF9 == 0)
			{
				pDVar2 = nullptr;
			}
			else
			{
				pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			pUVar3 = sub_6FB297F0(pDVar2);
			Unicode::strcpy(aUStack_a0, pUVar3);
			iVar6 = Unicode::strlen(aUStack_a0);
			iVar5 = 0;
			if (0 < iVar6)
			{
				do
				{
					uVar4 = aUStack_a0[iVar5].ch;
					if (uVar4 < 0x100)
					{
						uVar4 = Unicode((unsigned short)((uint32_t)uVar4)).toLower().ch;
					}
					aUStack_a0[iVar5].ch = uVar4;
					iVar5 = iVar5 + 1;
				} while (iVar5 < iVar6);
			}
			sub_6FAD7180(dword_6FBB5D47, aUStack_a0, 0x15, 0, 4, 1, 0, 0);
			byte_6FBB5C3B = 1;
			iStack_c8 = 0xd3b0d3a;
			iStack_c4 = 0xd3d0d3c;
			iStack_c0 = CONCAT22((*(uint16_t*)((uint8_t*)&iStack_c0 + 2)), 0xd3e);
			pDVar2 = CUNIT_GetPlayer();
			DVar1 = (uint64_t)((uint64_t)(pDVar2->pSeed).nLowSeed * 0x6ac690c5 +
			                   (uint64_t)(pDVar2->pSeed).nHighSeed);
			iVar5 = 1;
			(*(uint64_t*)&pDVar2->pSeed) = DVar1;
			pcVar10 = (code*)(sub_6FAF9710);
			uVar9 = 1;
			iVar6 = 0;
			uVar8 = 0;
			uVar7 = 0xf;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)&iStack_c8 +
			                                                           (int)(((uint64_t)DVar1 & 0xffffffff) % 5) * 2)));
			sub_6FAD7180(dword_6FBB5D47, pUVar3, uVar7, uVar8, iVar6, uVar9, (int)(pcVar10), iVar5);
			iVar5 = 1;
			pcVar10 = (code*)(sub_6FAF93D0);
			uVar9 = 1;
			iVar6 = 0;
			uVar8 = 0;
			uVar7 = 0xf;
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x102e));
			sub_6FAD7180(dword_6FBB5D47, pUVar3, uVar7, uVar8, iVar6, uVar9, (int)(pcVar10), iVar5);
			sub_6FAD7090(dword_6FBB5D47, 1);
			return;
		}
		FOG_DisplayAssert("sgUIState.hDialogInterrupt == NULL",
		    __FILE__, __LINE__);
		exit(-1);
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	sub_6FAFBB60(dword_6FBB5CF5);
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF93D0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF93D0()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;

	if (dword_6FBB5D47 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D47 = 0;
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x31), dword_6FBB5CF5, (uint32_t)word_6FBB5C47);
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF9570
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF9570()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;

	if (dword_6FBB5D47 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D47 = 0;
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x31), dword_6FBB5CF5, (uint32_t)word_6FBB5C47);
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF9710
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAF9710()
{
	D2UnitStrc* pDVar1;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t uVar2;
	uint32_t extraout_ECX_01;
	uint32_t uVar3;
	uint32_t extraout_ECX_02;
	uint16_t extraout_var;
	uint16_t extraout_var_00;
	uint16_t uVar4;

	if (dword_6FBB5D47 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D47 = 0;
	}
	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if (pDVar1 != nullptr)
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar1 = nullptr;
				uVar4 = extraout_var;
			}
			else
			{
				pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
				uVar4 = extraout_var_00;
			}
			sub_6FB1CC20(pDVar1, CONCAT22(uVar4, word_6FBB5C47), 0);
			uVar3 = extraout_ECX_01;
			if (word_6FBB5D7A < 9)
			{
				uVar3 = (uint32_t)word_6FBB5D7A;
				(&word_6FBB5D66)[uVar3] = word_6FBB5C47;
				word_6FBB5D7A = word_6FBB5D7A + 1;
			}
			if (word_6FBB5C49 == 0xffff)
			{
				byte_6FBB5C3B = 0;
			}
			else
			{
				byte_6FBB5C39 = 1;
				sub_6FB1CBD0((uint8_t*)(sub_6FAF89E0), 0);
				uVar3 = extraout_ECX_02;
			}
			sub_6FAADA40(D2C_ZEXT(0x31), dword_6FBB5CF5, (uint32_t)word_6FBB5C47);
			return 1;
		}
	}
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar3 = dword_6FBB5CF5;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		pDVar1 = CUNIT_GetPlayer();
		sub_6FAFBB10((int*)pDVar1);
	}
	if (uVar3 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar1 = sub_6FB269F0(uVar3, 1);
	if (pDVar1 != nullptr)
	{
		sub_6FAF78E0((int)pDVar1);
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar1 = sub_6FB269F0(uVar3, 1);
	uVar2 = extraout_ECX;
	if (pDVar1 != nullptr)
	{
		sub_6FAFA230((int)pDVar1, 2, 1);
		uVar2 = extraout_ECX_00;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar2 >> 8), 0x30), 1, uVar3);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar1 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar1, 1, 0);
		sub_6FB4F410(pDVar1, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
	return 1;
}

//D2Client.0x6FAF98D0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAF98D0(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	D2InventoryStrc* pInventory;
	D2BitBufferStrc* pQuestRecord;
	D2UnitStrc* pDVar2;
	int iVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;
	uint32_t* puVar6;
	uint32_t extraout_ECX_00;
	int iVar7;
	int* piVar8;
	float fVar9;
	int iVar10;
	float fVar11;
	uint16_t uVar12;
	int iVar13;

	sub_6FAABF30();
	if (pUnit == nullptr)
	{
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		sub_6FAFBB60(dword_6FBB5CF5);
		sub_6FB23260(8, 1, 0);
		return;
	}
	uVar12 = 0;
	iVar10 = 0xe;
	byte_6FBB5C3B = 1;
	dword_6FBB5D01 = 0;
	pDVar2 = CUNIT_GetPlayer();
	byte_6FBB5C43 = STATLIST_UnitGetStatValue(pDVar2, iVar10, uVar12);
	sub_6FB23800(0, 0);
	if (a2 == 0)
	{
		if (dword_6FBB5CF9 == 0)
		{
			pDVar2 = nullptr;
		}
		else
		{
			pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		if (pUnit == pDVar2)
		{
			return;
		}
		if ((dword_6FBB5CF9 != 0) && (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 != nullptr))
		{
			byte_6FBB5C3B = 0;
			sub_6FAE8F10();
			sub_6FAFBB60(dword_6FBB5CF5);
			sub_6FB23260(8, 1, 0);
			return;
		}
	}
	else
	{
		if (dword_6FBB5CF9 == 0)
		{
			pDVar2 = nullptr;
		}
		else
		{
			pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		if (pUnit != pDVar2)
		{
			FOG_Trace("log at %d %s\n", __LINE__, __FILE__);
		}
	}
	dword_6FBB5CF9 = 1;
	dword_6FBB5CF5 = pUnit->dwUnitId;
	dword_6FBB5CFD = pUnit->dwClassId;
	iVar10 = pUnit->dwClassId;
	pUnit->dwFlags = pUnit->dwFlags & 0xfffffffd;
	pQuestRecord = gpBitBuffer_6FBB5D13;
	if (0 < dword_6FB7A5B8)
	{
		piVar8 = (int*)(&dword_6FB7A520);
		iVar7 = dword_6FB7A5B8;
		do
		{
			if (piVar8[-2] == iVar10)
			{
				if (piVar8[1] == 0)
				{
					iVar3 = QUESTRECORD_GetQuestState(pQuestRecord, piVar8[-1], *piVar8);
					if (iVar3 == 0)
						goto LAB_6faf9a57;
				}
				else
				{
					iVar3 = QUESTRECORD_GetQuestState(pQuestRecord, piVar8[-1], *piVar8);
					if (iVar3 != 0)
					{
					LAB_6faf9a57:
						(*(code*)piVar8[2])();
					}
				}
			}
			piVar8 = piVar8 + 5;
			iVar7 = iVar7 + -1;
		} while (iVar7 != 0);
	}
	if (dword_6FBB5D80 != 0)
	{
		if (dword_6FBB5D84 != 0)
		{
			sub_6FB556A0(dword_6FBB5D84);
			dword_6FBB5D84 = 0;
		}
		dword_6FBB5D80 = 0;
	}
	uVar1 = pUnit->dwClassId;
	if (uVar1 < 0xfd)
	{
		if (uVar1 == 0xfc)
		{
			iVar7 = 0x18;
		}
		else if (uVar1 == 0x96)
		{
			uVar12 = 0;
			iVar7 = 0xc;
			pDVar2 = CUNIT_GetPlayer();
			iVar7 = STATLIST_UnitGetStatValue(pDVar2, iVar7, uVar12);
			if (7 < iVar7)
			{
				byte_6FB7BF21 = 3;
				byte_6FB7BF33 = (uint8_t)(sub_6FAF4E30);
				byte_6FB7BF27 = 0xd45;
			}
			iVar7 = 0xb;
		}
		else
		{
			if (uVar1 != 0xc6)
				goto LAB_6faf9b13;
			iVar7 = 8;
		}
	}
	else if (uVar1 == 0x16f)
	{
		iVar7 = 0x15;
	}
	else
	{
		if (uVar1 != 0x203)
			goto LAB_6faf9b13;
		iVar7 = 0x2b;
	}
	sub_6FAF9CB0(iVar7, (uint32_t)(word_6FB7A5BC != -1));
LAB_6faf9b13:
	iVar7 = sub_6FB23260(8, 0, 0);
	if (iVar7 == 0)
	{
		byte_6FBB5C3B = 0;
		pUnit->dwFlags = pUnit->dwFlags | 2;
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, pUnit->dwUnitId);
		dword_6FBB5CF9 = 0;
		uVar1 = pUnit->dwUnitId;
		if (uVar1 != dword_6FBB5CF5)
		{
			FOG_Trace("mismatch npc ids\n");
		}
		pDVar2 = sub_6FB269F0(uVar1, 1);
		if (pDVar2 != nullptr)
		{
			puVar6 = dword_6FBB5C5D;
			do
			{
				*puVar6 = 0;
				puVar6 = puVar6 + 4;
			} while ((int)puVar6 < (int)&dword_6FBB5CFD);
			pInventory = pDVar2->pInventory;
			if (pInventory != nullptr)
			{
				pDVar2 = INVENTORY_GetFirstItem(pInventory);
				while (pDVar2 != nullptr)
				{
					pDVar4 = INVENTORY_GetNextItem(pDVar2);
					pDVar5 = INVENTORY_UnitIsItem(pDVar2);
					pDVar2 = pDVar4;
					if (pDVar5 != nullptr)
					{
						sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
					}
				}
				INVENTORY_RemoveInventoryItems(pInventory);
				D2COMMON_10251_Return((int)pInventory);
			}
		}
		if (dword_6FBB5D80 != 0)
		{
			sub_6FB556A0(dword_6FBB5D84);
		}
		dword_6FBB5D80 = 0;
	}
	else
	{
		sub_6FAF65C0();
		if (a2 != 0)
		{
			return;
		}
		iVar3 = 0;
		iVar7 = 0;
		if (0 < dword_6FB7BD6C)
		{
			puVar6 = dword_6FB7B978;
			do
			{
				if (*puVar6 == iVar10)
				{
					iVar13 = iVar7 * 0x16;
					if (byte_6FB7B98A[iVar7 * 0x16] == '\x01')
					{
						byte_6FB7B98A[iVar13] = 0;
						iVar3 = 2;
					}
					if ((&byte_6FB7B98D)[iVar13] != '\x01')
					{
						return;
					}
					(&byte_6FB7B98D)[iVar13] = 0;
					break;
				}
				iVar7 = iVar7 + 1;
				puVar6 = (uint32_t*)((int)puVar6 + 0x16);
			} while (iVar7 < dword_6FB7BD6C);
		}
		iVar7 = sub_6FB464A0((int)pUnit, iVar3);
		if (iVar7 == 0)
		{
			return;
		}
		sub_6FB50290(pUnit);
		iVar13 = 0;
		fVar11 = 1.4013e-45;
		fVar9 = 0.0;
		pDVar2 = CUNIT_GetPlayer();
		dword_6FBB5D84 = sub_6FB55820(iVar7, pDVar2, fVar9, fVar11, iVar13);
		if (iVar3 == 2)
		{
			sub_6FAAD990(CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x4d), (short)iVar10);
			dword_6FBB5D80 = 1;
			return;
		}
	}
	dword_6FBB5D84 = 0;
}

//D2Client.0x6FAF9CB0
uint32_t __fastcall sub_6FAF9CB0(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int iVar3;
	uint32_t* puVar4;
	int iVar5;
	int* piVar6;
	uint16_t* puVar7;

	iVar1 = FOG_IsExpansion();
	if ((iVar1 != 0) && (iVar1 = sub_6FAAC080(), iVar1 != 0))
	{
		iVar1 = a1 * 0x27;
		if (a2 != 0)
		{
			iVar2 = *(int*)((int)&dword_6FB7BD74 + iVar1);
			iVar5 = 0;
			if (0 < iVar2)
			{
				piVar6 = (int*)((int)&ptr_6FB7BD82 + iVar1);
				do
				{
					if ((code*)*piVar6 == (code*)(sub_6FAF8E80))
					{
						return 1;
					}
					iVar5 = iVar5 + 1;
					piVar6 = piVar6 + 1;
				} while (iVar5 < iVar2);
			}
			iVar5 = 0;
			if (0 < iVar2)
			{
				piVar6 = (int*)((int)&ptr_6FB7BD82 + iVar1);
				do
				{
					if ((code*)*piVar6 == (code*)(sub_6FAF4E30))
					{
						iVar2 = iVar2 + -1;
						if (iVar5 <= iVar2)
						{
							puVar4 = (uint32_t*)((int)&ptr_6FB7BD86 + iVar2 * 4 + iVar1);
							iVar3 = (iVar2 - iVar5) + 1;
							puVar7 = (uint16_t*)(byte_6FB7BD7A + iVar2 * 2 + iVar1);
							do
							{
								*puVar4 = puVar4[-1];
								*puVar7 = puVar7[-1];
								puVar4 = puVar4 + -1;
								iVar3 = iVar3 + -1;
								puVar7 = puVar7 + -1;
							} while (iVar3 != 0);
						}
						*(int*)((int)&dword_6FB7BD74 + iVar1) = *(int*)((int)&dword_6FB7BD74 + iVar1) + 1;
						*(code**)((int)&ptr_6FB7BD82 + iVar5 * 4 + iVar1) = (code*)(sub_6FAF8E80);
						*(uint16_t*)((int)&word_6FB7BD78 + iVar5 * 2 + iVar1) = 0x1507;
						return 1;
					}
					iVar5 = iVar5 + 1;
					piVar6 = piVar6 + 1;
				} while (iVar5 < iVar2);
			}
			iVar2 = iVar2 + -1;
			if (!SBORROW4(iVar2, iVar2))
			{
				puVar4 = (uint32_t*)((int)&ptr_6FB7BD86 + iVar2 * 4 + iVar1);
				iVar5 = 1;
				puVar7 = (uint16_t*)(byte_6FB7BD7A + iVar2 * 2 + iVar1);
				do
				{
					*puVar4 = puVar4[-1];
					*puVar7 = puVar7[-1];
					puVar4 = puVar4 + -1;
					iVar5 = iVar5 + -1;
					puVar7 = puVar7 + -1;
				} while (iVar5 != 0);
			}
			*(int*)((int)&dword_6FB7BD74 + iVar1) = *(int*)((int)&dword_6FB7BD74 + iVar1) + 1;
			*(code**)((int)&ptr_6FB7BD82 + iVar2 * 4 + iVar1) = (code*)(sub_6FAF8E80);
			*(uint16_t*)((int)&word_6FB7BD78 + iVar2 * 2 + iVar1) = 0x1507;
			return 1;
		}
		iVar2 = *(int*)((int)&dword_6FB7BD74 + iVar1);
		iVar5 = 0;
		if (0 < iVar2)
		{
			piVar6 = (int*)((int)&ptr_6FB7BD82 + iVar1);
			while ((code*)*piVar6 != (code*)(sub_6FAF8E80))
			{
				iVar5 = iVar5 + 1;
				piVar6 = piVar6 + 1;
				if (iVar2 <= iVar5)
				{
					return 1;
				}
			}
			if (iVar5 < iVar2 + -1)
			{
				puVar7 = (uint16_t*)((int)&word_6FB7BD78 + iVar5 * 2 + iVar1);
				puVar4 = (uint32_t*)((int)&ptr_6FB7BD82 + iVar5 * 4 + iVar1);
				do
				{
					iVar5 = iVar5 + 1;
					*puVar4 = puVar4[1];
					*puVar7 = puVar7[1];
					puVar4 = puVar4 + 1;
					puVar7 = puVar7 + 1;
				} while (iVar5 < *(int*)((int)&dword_6FB7BD74 + iVar1) + -1);
			}
			*(int*)((int)&dword_6FB7BD74 + iVar1) = *(int*)((int)&dword_6FB7BD74 + iVar1) + -1;
		}
		return 1;
	}
	return 0;
}

//D2Client.0x6FAF9E60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF9E60()
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	uint32_t uVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_ECX;

	sub_6FB23260(0xc, 1, 0);
	byte_6FBB5C3B = 0;
	sub_6FAE8F10();
	uVar2 = dword_6FBB5CF5;
	pDVar3 = CUNIT_GetPlayer();
	if ((((pDVar3 != nullptr) && (pDVar3 = CUNIT_GetPlayer(), pDVar3 != nullptr)) &&
	        (pDVar3->dwUnitType == 0)) &&
	    (pDVar3->pPlayerData != nullptr))
	{
		pDVar3->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar3->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (uVar2 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		sub_6FAFBD00();
		pInventory = pDVar3->pInventory;
		if (pInventory != nullptr)
		{
			pDVar3 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar3 != nullptr)
			{
				pDVar4 = INVENTORY_GetNextItem(pDVar3);
				pDVar5 = INVENTORY_UnitIsItem(pDVar3);
				pDVar3 = pDVar4;
				if (pDVar5 != nullptr)
				{
					sub_6FB26BE0(pDVar5->dwUnitId, pDVar5->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar3 = sub_6FB269F0(uVar2, 1);
	if (pDVar3 != nullptr)
	{
		pDVar3->dwFlags = pDVar3->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, uVar2);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar3 != nullptr)
	{
		if ((pDVar3->dwUnitType == 1) && (pDVar3->pPlayerData != nullptr))
		{
			puVar1 = &pDVar3->pPlayerData->unk0x28;
			*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
		}
		sub_6FB4F410(pDVar3, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
}

//D2Client.0x6FAF9FE0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAF9FE0()
{
	D2UnitStrc* pDVar1;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t extraout_ECX_02;
	uint32_t uVar2;
	uint32_t uVar3;

	if (byte_6FBB5C3B == 1)
	{
		byte_6FBB5C39 = '\0';
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		uVar3 = dword_6FBB5CF5;
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			pDVar1 = CUNIT_GetPlayer();
			if (((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0)) &&
			    (pDVar1->pPlayerData != nullptr))
			{
				pDVar1->pPlayerData->unk0xA8[0x2a] = 0;
				pDVar1->pPlayerData->unk0xA8[0x2b] = 0;
				pDVar1->pPlayerData->unk0xA8[0x2c] = 0;
				pDVar1->pPlayerData->unk0xA8[0x2d] = 0;
			}
		}
		sub_6FAF7950(uVar3);
		pDVar1 = sub_6FB269F0(uVar3, 1);
		uVar2 = extraout_ECX;
		if (pDVar1 != nullptr)
		{
			sub_6FAFA230((int)pDVar1, 2, 1);
			uVar2 = extraout_ECX_00;
		}
	}
	else
	{
		if ((2 < byte_6FBB5C3B) && (byte_6FBB5C3B < 7))
		{
			sub_6FB23260(0xc, 1, 0);
			byte_6FBB5C3B = 0;
			sub_6FAE8F10();
			uVar3 = dword_6FBB5CF5;
			pDVar1 = CUNIT_GetPlayer();
			if (pDVar1 != nullptr)
			{
				pDVar1 = CUNIT_GetPlayer();
				sub_6FAFBB10((int*)pDVar1);
			}
			sub_6FAF7950(uVar3);
			pDVar1 = sub_6FB269F0(uVar3, 1);
			if (pDVar1 != nullptr)
			{
				pDVar1->dwFlags = pDVar1->dwFlags | 2;
			}
			sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX_01 >> 8), 0x30), 1, uVar3);
			sub_6FB1E710();
			sub_6FAF3DC0(0);
			sub_6FB23260(8, 1, 0);
			if (pDVar1 != nullptr)
			{
				sub_6FAFB6E0((int*)pDVar1, 1, 0);
				sub_6FB4F410(pDVar1, (int*)0x1);
			}
			sub_6FB23260(8, 1, 0);
			sub_6FAED220();
			sub_6FAF6340();
			byte_6FBB5C3B = 0;
			return;
		}
		if (byte_6FBB5C3B == 7)
		{
			sub_6FB249D0();
			sub_6FAF6340();
			byte_6FBB5C3B = 0;
			return;
		}
		if (byte_6FBB5C39 == '\0')
			goto LAB_6fafa21f;
		byte_6FBB5C39 = '\0';
		byte_6FBB5C3B = 0;
		sub_6FAE8F10();
		uVar3 = dword_6FBB5CF5;
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 != nullptr)
		{
			pDVar1 = CUNIT_GetPlayer();
			sub_6FAFBB10((int*)pDVar1);
		}
		sub_6FAF7950(uVar3);
		pDVar1 = sub_6FB269F0(uVar3, 1);
		uVar2 = extraout_ECX_02;
		if (pDVar1 != nullptr)
		{
			pDVar1->dwFlags = pDVar1->dwFlags | 2;
		}
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)uVar2 >> 8), 0x30), 1, uVar3);
	sub_6FB1E710();
	sub_6FAF3DC0(0);
	sub_6FB23260(8, 1, 0);
	if (pDVar1 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar1, 1, 0);
		sub_6FB4F410(pDVar1, (int*)0x1);
	}
	sub_6FB23260(8, 1, 0);
LAB_6fafa21f:
	sub_6FAF6340();
	byte_6FBB5C3B = 0;
}

//D2Client.0x6FAFA230
int32_t __fastcall sub_6FAFA230(int a1, uint32_t a2, int a3)
{
	if (a1 != 0)
	{
		if (a3 != 0)
		{
			*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) | a2;
			return 0;
		}
		*(uint32_t*)(a1 + 0xc4) = *(uint32_t*)(a1 + 0xc4) & ~a2;
	}
	return 0;
}

//D2Client.0x6FAFA260
// TODO: decompilation needs review (extraout, unaff_)
uint32_t __fastcall sub_6FAFA260(D2UnitStrc* pUnit2, D2UnitStrc* pUnit3, int a3, uint32_t a4, uint32_t a5, uint32_t a6, int a7, int a8)
{
	uint8_t bVar1;
	D2UnitStrc* pDVar2;
	int iVar3;
	uint32_t uVar4;
	DWORD DVar5;
	uint32_t extraout_var;
	int iVar6;
	D2C_Difficulties DVar7;
	D2UnitStrc* pDVar8;
	D2GameStrc* pGame;
	D2UnitStrc* pUnit;
	bool bVar9;
	uint32_t unaff_retaddr;
	D2BitBufferStrc* pDVar10;
	D2BitBufferStrc* pQuestFlags;
	D2C_TransactionTypes DVar11;

	if ((dword_6FBB5CF9 == 0) || (pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar2 == nullptr))
	{
		return 0;
	}
	pQuestFlags = (D2BitBufferStrc*)pDVar2->dwClassId;
	if (a8 != 0)
	{
		if ((int)pQuestFlags < 0xfe)
		{
			if ((pQuestFlags == (D2BitBufferStrc*)0xfd) || (pQuestFlags == (D2BitBufferStrc*)0x9a))
				goto LAB_6fafa2cb;
			bVar9 = pQuestFlags == (D2BitBufferStrc*)0xb2;
		}
		else
		{
			if (pQuestFlags == (D2BitBufferStrc*)0x101)
				goto LAB_6fafa2cb;
			bVar9 = pQuestFlags == (D2BitBufferStrc*)0x1ff;
		}
		if (!bVar9)
		{
			return 0;
		}
	LAB_6fafa2cb:
		iVar3 = sub_6FAEB940();
		if (iVar3 == 0)
		{
			return 1;
		}
		bVar1 = sub_6FAAC090();
		dword_6FBB5D4B = ITEMS_GetAllRepairCosts(pGame, pUnit, 0, (D2C_Difficulties)(int)pUnit2, pQuestFlags,
		    (void(__fastcall*)(D2GameStrc*, D2UnitStrc*, D2UnitStrc*))((void*)(uint32_t)bVar1));
		dword_6FBB5D01 = 3;
		byte_6FBB5BD0 = '\x01';
		dword_6FBB5BD5 = 0;
		sub_6FAB5A90(nullptr);
		byte_6FBB5D1F = a3;
		byte_6FBB5D1B = unaff_retaddr;
		sub_6FAFA6E0(1, a4);
		return 1;
	}
	uVar4 = ITEMS_GetItemType(pUnit3);
	iVar3 = a7;
	if (uVar4 == 4)
	{
		return 0;
	}
	if ((a7 != 0) && (DVar5 = GetTickCount(), DVar5 - byte_6FBB5BE1 < 500))
	{
		return 0;
	}
	byte_6FBB5D1B = a4;
	byte_6FBB5D1F = a5;
	if (a3 != 1)
	{
		pDVar2 = CUNIT_GetPlayer();
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		if (pDVar2 != nullptr)
		{
			return 0;
		}
		DVar11 = TRANSACTIONTYPE_BUY;
		dword_6FBB5D01 = 1;
		if (dword_6FBB5D7C != 0)
		{
			DVar11 = TRANSACTIONTYPE_GAMBLE;
		}
		pDVar10 = gpBitBuffer_6FBB5D13;
		bVar1 = sub_6FAAC090();
		DVar7 = (D2C_Difficulties)bVar1;
		pDVar2 = pUnit3;
		pDVar8 = CUNIT_GetPlayer();
		dword_6FBB5D4B = ITEMS_GetTransactionCost(pDVar8, pDVar2, DVar7, pDVar10, (int)pQuestFlags, DVar11);
		goto LAB_6fafa59e;
	}
	if ((int)pQuestFlags < 0xfe)
	{
		if (pQuestFlags != (D2BitBufferStrc*)0xfd)
		{
			switch ((int32_t)(pQuestFlags))
			{
			case 0x93:
			case 0x94:
			case 0xb1:
			case 0xc7:
			case 0xca:
			case 0xfc:
				goto switchD_6fafa3bf_caseD_93;
			default:
				goto switchD_6fafa3bf_caseD_95;
			case 0x9a:
			case 0xb2:
				break;
			case 0xf4:
			case 0xf5:
			case 0xf6:
				goto switchD_6fafa3bf_caseD_f4;
			}
		}
	switchD_6fafa3bf_caseD_9a:
		bVar9 = sub_6FAEB930();
		if (D2C_ZEXT(bVar9) != 0)
		{
			uVar4 = ITEMS_GetItemType(pUnit3);
			if (uVar4 == 4)
			{
				return 0;
			}
			iVar3 = ITEMS_IsRepairable(pUnit3);
			if (iVar3 == 0)
			{
				return 0;
			}
			iVar3 = ITEMS_HasDurability(pUnit3);
			if (((iVar3 == 0) || (iVar3 = STATLIST_GetMaxDurabilityFromUnit(pUnit3), iVar3 == 0)) ||
			    (iVar6 = STATLIST_UnitGetStatValue(pUnit3, 0x48, 0), iVar3 <= iVar6))
			{
				uVar4 = ITEMS_CheckIfStackable(pUnit3);
				if (uVar4 != 0)
				{
					iVar3 = STATLIST_UnitGetStatValue(pUnit3, 0x46, 0);
					iVar6 = ITEMS_GetTotalMaxStack(pUnit3);
					if (iVar3 < iVar6)
						goto LAB_6fafa495;
				}
				iVar3 = ITEMS_HasUsedCharges(pUnit3, (int*)&a4);
				if ((iVar3 == 0) || (a4 != 0))
				{
					return 0;
				}
			}
		LAB_6fafa495:
			DVar11 = TRANSACTIONTYPE_REPAIR;
			dword_6FBB5D01 = 3;
			pDVar10 = gpBitBuffer_6FBB5D13;
			bVar1 = sub_6FAAC090();
			DVar7 = (D2C_Difficulties)bVar1;
			pDVar2 = pUnit3;
			pDVar8 = CUNIT_GetPlayer();
			dword_6FBB5D4B = ITEMS_GetTransactionCost(pDVar8, pDVar2, DVar7, pDVar10, (int)pQuestFlags, DVar11);
			iVar3 = a7;
			goto LAB_6fafa59e;
		}
	}
	else
	{
		if (0x195 < (int)pQuestFlags)
		{
			switch ((int32_t)(pQuestFlags))
			{
			case 0x1ff:
				goto switchD_6fafa3bf_caseD_9a;
			case 0x200:
			case 0x201:
			case 0x202:
				goto switchD_6fafa3bf_caseD_93;
			default:
			switchD_6fafa3bf_caseD_95:
				return 0;
			case 0x208:
			switchD_6fafa3bf_caseD_f4:
				iVar6 = ITEMS_CheckItemFlag(pUnit3, 0x10, __LINE__, __FILE__);
				if (iVar6 == 1)
				{
					return 0;
				}
				dword_6FBB5D01 = 4;
				goto LAB_6fafa59e;
			}
		}
		if (pQuestFlags != (D2BitBufferStrc*)0x195)
		{
			switch ((int32_t)(pQuestFlags))
			{
			case 0xfe:
			case 0xff:
				break;
			default:
				goto switchD_6fafa3bf_caseD_95;
			case 0x101:
				goto switchD_6fafa3bf_caseD_9a;
			case 0x109:
				goto switchD_6fafa3bf_caseD_f4;
			}
		}
	switchD_6fafa3bf_caseD_93:
	}
	DVar11 = TRANSACTIONTYPE_SELL;
	pDVar10 = gpBitBuffer_6FBB5D13;
	bVar1 = sub_6FAAC090();
	DVar7 = (D2C_Difficulties)bVar1;
	pDVar2 = pUnit3;
	pDVar8 = CUNIT_GetPlayer();
	dword_6FBB5D4B = ITEMS_GetTransactionCost(pDVar8, pDVar2, DVar7, pDVar10, (int)pQuestFlags, DVar11);
	iVar6 = ITEMS_IsNotQuestItem(pUnit3);
	if (iVar6 == 0)
	{
		return 0;
	}
	dword_6FBB5D01 = 2;
LAB_6fafa59e:
	byte_6FBB5BD0 = '\x01';
	if (pUnit3 == nullptr)
	{
		dword_6FBB5BD5 = 0xffffffff;
		byte_6FBB5BD1 = -1;
	}
	else
	{
		dword_6FBB5BD5 = pUnit3->dwUnitId;
		byte_6FBB5BD1 = pUnit3->dwClassId;
	}
	sub_6FAB5A90(nullptr);
	if (((dword_6FBB5D01 == 2) || (dword_6FBB5D01 == 1)) && (iVar3 != 0))
	{
		sub_6FAFA6E0(1, a6);
		return 1;
	}
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	byte_6FBB5C3B = 4;
	sub_6FAFB710();
	return 1;
}

//D2Client.0x6FAFA6E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAFA6E0(int a1, uint32_t a2)
{
	int iVar1;
	DWORD DVar2;
	D2UnitStrc* pDVar3;
	D2ItemsTxt* pDVar4;
	Unicode* pUVar5;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t uVar6;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	char cVar7;
	uint32_t uVar8;
	D2UnitStrc* pDVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	uint32_t uVar12;
	uint32_t uVar13;
	int iVar14;
	uint32_t local_30;
	int iStack_2c;
	D2CoordStrc DStack_28;
	int iStack_20;
	int iStack_1c;
	int iStack_18;
	int iStack_14;
	tagRECT tStack_10;

	local_30 = a2;
	if (byte_6FBB5BD0 == '\0')
	{
		FOG_Trace("Error at line %d of file %s\n", __LINE__, __FILE__);
		sub_6FAE9500();
		return;
	}
	if (dword_6FBB5D01 == 1)
	{
		cVar7 = '2';
	}
	else if (dword_6FBB5D01 == 2)
	{
		cVar7 = '3';
	}
	else
	{
		if (dword_6FBB5D01 != 3)
		{
			byte_6FBB5C3B = 3;
			sub_6FAE9500();
			return;
		}
		cVar7 = '5';
		sub_6FB55820(0xf, nullptr, 0.0, 0.0, 0);
	}
	pDVar9 = nullptr;
	uVar8 = 0;
	dword_6FBB5D62 = 0;
	iVar1 = sub_6FAEB940();
	if (iVar1 == 0)
	{
		pDVar9 = sub_6FB269F0(dword_6FBB5BD5, 4);
		if (pDVar9 == nullptr)
		{
			byte_6FBB5C3B = 3;
			sub_6FAED1C0();
			FOG_Trace("buy cancelled for non existant item?");
			dword_6FBB5BD9 = GetTickCount();
			dword_6FBB5BDD = dword_6FBB5BDD + 1;
			byte_6FBB5BD0 = '\0';
			return;
		}
		uVar8 = pDVar9->dwAnimMode;
		if (dword_6FBB5D01 == 2)
		{
			pDVar3 = INVENTORY_GetCursorItem(*(D2InventoryStrc**)(dword_6FBB5DA0 + 0x60));
			dword_6FBB5D0F = (uint32_t)(pDVar3 == pDVar9);
		}
	}
	else
	{
		DVar2 = GetTickCount();
		if (DVar2 - byte_6FBB5DA8 < 2000)
		{
			sub_6FAE9500();
			return;
		}
		byte_6FBB5DA8 = GetTickCount();
	}
	if (a1 == 0)
	{
		sub_6FAE9550();
	}
	else
	{
		sub_6FAE9590();
	}
	byte_6FBB5C3B = 5;
	byte_6FBB5BE1 = GetTickCount();
	if (cVar7 == '2')
	{
		uVar8 = uVar8 << 0x10;
		if (dword_6FBB5D7C != 0)
		{
			uVar8 = uVar8 | 2;
		}
		uVar6 = extraout_var;
		if ((local_30 & 4) != 0)
		{
			if (pDVar9 == nullptr)
			{
				iVar1 = -1;
			}
			else
			{
				iVar1 = pDVar9->dwClassId;
			}
			pDVar4 = DATATBLS_GetItemsTxtRecord(iVar1);
			uVar6 = extraout_var_00;
			if ((pDVar4 != nullptr) && (pDVar4->nMultibuy != 0))
			{
				uVar8 = uVar8 | 0x80000000;
			}
		}
		sub_6FAADAA0(CONCAT31(uVar6, 0x32), dword_6FBB5CF5, dword_6FBB5BD5, uVar8, dword_6FBB5D4B);
		dword_6FBB5D2B = sub_6FB2E590(pDVar9);
	}
	else
	{
		if (cVar7 == '5')
		{
			iVar1 = sub_6FAEB940();
			if (iVar1 == 0)
			{
				if (pDVar9 == nullptr)
				{
					uVar10 = CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x35);
					iVar1 = 0;
				}
				else
				{
					iVar1 = STATLIST_UnitGetStatValue(pDVar9, 0x48, 0);
					uVar10 = CONCAT31((int32_t)((uint32_t)extraout_ECX_00 >> 8), 0x35);
				}
			}
			else
			{
				uVar10 = D2C_ZEXT(0x35);
				iVar1 = -0x80000000;
			}
		}
		else
		{
			uVar10 = CONCAT31((int32_t)((uint32_t)dword_6FBB5D4B >> 8), cVar7);
			iVar1 = dword_6FBB5D4B;
		}
		sub_6FAADAA0(uVar10, dword_6FBB5CF5, dword_6FBB5BD5, uVar8 & 0xffff, iVar1);
	}
	if (dword_6FBB5D37 == 0)
	{
		DStack_28.nX = 0;
		DStack_28.nY = 0;
		if ((dword_6FBB5CF9 != 0) && (pDVar9 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar9 != nullptr))
		{
			if (dword_6FBB5CF9 == 0)
			{
				pDVar9 = nullptr;
			}
			else
			{
				pDVar9 = sub_6FB269F0(dword_6FBB5CF5, 1);
			}
			UNITS_GetClientCoords(pDVar9, &DStack_28);
			sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_20), (uint32_t*)(&iStack_1c), (uint32_t*)(&iStack_18), (uint32_t*)(&iStack_14));
			sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_2c), &local_30);
			SetRect(&tStack_10, iStack_2c, local_30, (iStack_18 - iStack_20) + iStack_2c,
			    (local_30 - iStack_1c) + iStack_14);
			DStack_28.nY = DStack_28.nY + (-0x96 - tStack_10.top);
			DStack_28.nX = DStack_28.nX - tStack_10.left;
			if (DStack_28.nY < 0x14)
			{
				DStack_28.nY = 0x14;
			}
		}
		dword_6FBB5D37 = (int)sub_6FAD6BE0(DStack_28.nX, DStack_28.nY, 0x6fb24f70, 0, 0, 0, 1, 0, 0, 0, 1);
		DVar2 = GetTickCount();
		dword_6FBB5D23 = DVar2 + 60000;
		dword_6FBB5D27 = 0;
		sub_6FAD7150(dword_6FBB5D37, 0);
		iVar14 = 0;
		uVar13 = 0;
		uVar12 = 1;
		iVar1 = 0;
		uVar11 = 0;
		uVar10 = 0xf;
		pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd19));
		sub_6FAD7180(dword_6FBB5D37, pUVar5, uVar10, uVar11, iVar1, uVar12, uVar13, iVar14);
		return;
	}
	FOG_DisplayAssert("sgUIState.hDialogWaiting == NULL",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAFAAA0
void __fastcall sub_6FAFAAA0(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\x01')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAB80
void __fastcall sub_6FAFAB80(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\x01')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAC60
void __fastcall sub_6FAFAC60(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\x01')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAD40
void __fastcall sub_6FAFAD40(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\0')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAE20
void __fastcall sub_6FAFAE20(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\0')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAF00
void __fastcall sub_6FAFAF00(int a1)
{
	DWORD DVar1;
	int iVar2;
	uint32_t uVar3;

	if (((dword_6FBB5D62 != 0) && (gNpcTransactionPacket.nTransactionType == '\0')) && (a1 == gNpcTransactionPacket.dwItemGUID))
	{
		DVar1 = GetTickCount();
		if (DVar1 - dword_6FBB5BD9 < 0x3e9)
		{
			uVar3 = dword_6FBB5BDD;
			if (9 < dword_6FBB5BDD)
			{
				uVar3 = 10;
			}
			dword_6FBB5D27 = DVar1 + (uVar3 * 5 + 0x96) * 100;
		}
		else
		{
			dword_6FBB5D27 = DVar1 + 100;
		}
		dword_6FBB5D62 = 0;
		if (byte_6FBB5BD0 == '\0')
		{
			FOG_Trace("got overlapping item msgs at line %d of file %s\n", __LINE__, __FILE__);
		}
		byte_6FBB5BD0 = '\0';
		byte_6FBB5BD1 = 0;
		dword_6FBB5BD5 = 0;
		iVar2 = sub_6FAABFF0();
		if (iVar2 == 0)
		{
			if (dword_6FBB5D37 != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D37 = 0;
			}
			byte_6FBB5C3B = 3;
			sub_6FAE95B0();
			sub_6FAEAC40();
			sub_6FAB5D40();
			return;
		}
	}
}

//D2Client.0x6FAFAFE0
void __fastcall sub_6FAFAFE0(uint32_t a1)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;

	pDVar1 = sub_6FAB5A20();
	if ((pDVar1 != nullptr) && (dword_6FBB5CF9 != 0))
	{
		pDVar2 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if ((pDVar2 != nullptr) &&
		    ((pDVar1->dwUnitType == 4 && (pDVar1->dwUnitId == a1))))
		{
			sub_6FAB5D40();
			sub_6FAE8F10();
			return;
		}
	}
}

//D2Client.0x6FAFB030
void __cdecl sub_6FAFB030()
{
	uint32_t uVar1;
	DWORD DVar2;
	DWORD DVar3;
	Unicode* pUVar4;
	D2UnitStrc* pDVar5;
	short index;
	code* pcVar6;
	DWORD DVar7;
	DWORD DVar8;
	DWORD DVar9;
	DWORD DVar10;
	DWORD DVar11;
	int iVar12;
	DWORD DVar13;
	uint32_t uVar14;
	uint32_t uVar15;
	uint32_t uVar16;
	uint32_t uVar17;
	int iVar18;

	if (dword_6FBB5D37 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB5D37 = 0;
	}
	if (gNpcTransactionPacket.nTransactionType == '\x05')
	{
		sub_6FADBF00();
	}
	else if ((gNpcTransactionPacket.nTransactionType != '\x06') && (gNpcTransactionPacket.nTransactionType != '\x03'))
	{
		switch (gNpcTransactionPacket.nTransactionType)
		{
		case '\a':
		case '\b':
			index = 0xd1e;
			break;
		default:
			index = 0xd21;
			break;
		case '\n':
			index = 0xd1c;
			break;
		case '\v':
			index = 0xd20;
			break;
		case '\f':
			index = 0xd22;
			break;
		case '\x0f':
			index = 0xd23;
			break;
		case '\x10':
			index = 0xd1d;
		}
		byte_6FBB5C3B = 0xc;
		D2_ASSERT(!dword_6FBB5D33);
		uVar17 = 1;
		uVar15 = 0;
		DVar13 = 0;
		DVar11 = 0;
		DVar10 = 1;
		DVar9 = 1;
		DVar8 = 0;
		DVar7 = 0;
		pcVar6 = (code*)(sub_6FAF6EE0);
		DVar2 = sub_6FB57BD0();
		DVar3 = sub_6FB57BC0();
		dword_6FBB5D33 = (int)sub_6FAD6BE0(DVar3, DVar2, (DWORD)pcVar6, DVar7, DVar8, DVar9, DVar10, DVar11,
		    DVar13, uVar15, uVar17);
		sub_6FAD7150(dword_6FBB5D33, 1);
		iVar18 = 0;
		uVar16 = 0;
		uVar14 = 1;
		iVar12 = 1;
		uVar17 = 0;
		uVar15 = 0x15;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		sub_6FAD7180(dword_6FBB5D33, pUVar4, uVar15, uVar17, iVar12, uVar14, uVar16, iVar18);
		iVar18 = 1;
		pcVar6 = (code*)(sub_6FAF6EE0);
		uVar14 = 1;
		iVar12 = 0;
		uVar17 = 0;
		uVar15 = 0xf;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd4b));
		sub_6FAD7180(dword_6FBB5D33, pUVar4, uVar15, uVar17, iVar12, uVar14, (int)(pcVar6), iVar18);
		return;
	}
	if ((dword_6FBB5CF9 != 0) && (pDVar5 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar5 != nullptr))
	{
		uVar1 = pDVar5->dwClassId;
		if (uVar1 < 0x10a)
		{
			if (uVar1 != 0x109)
			{
				if (uVar1 < 0xf4)
					goto LAB_6fafb1c8;
				if (0xf6 < uVar1)
				{
					sub_6FAF65C0();
					return;
				}
			}
		}
		else if (uVar1 != 0x208)
			goto LAB_6fafb1c8;
		byte_6FB7BFE4 = 2;
		byte_6FB7C00B = 2;
		byte_6FB7C032 = 2;
		byte_6FB7C059 = 2;
		byte_6FB7C33E = 2;
	}
LAB_6fafb1c8:
	sub_6FAF65C0();
}

//D2Client.0x6FAFB200
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAFB200(D2UnitStrc* pUnit, int a2, int* a3, Unicode* pUnicode, int a5)
{
	int* piVar1;
	Unicode* pUVar2;
	bool bVar3;
	uint8_t bVar4;
	uint32_t uVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	uint32_t extraout_var;
	int iVar8;
	D2C_Difficulties DVar9;
	Unicode* pUVar10;
	short index;
	D2BitBufferStrc* pDVar11;
	D2C_TransactionTypes DVar12;
	CHAR aCStack_3c[20];
	Unicode aUStack_28[20];

	piVar1 = a3;
	*a3 = 0;
	if (pUnit == nullptr)
	{
		return 0;
	}
	uVar5 = ITEMS_GetItemType(pUnit);
	if (uVar5 == 4)
	{
		return 0;
	}
	if (a2 == 0)
	{
		DVar12 = TRANSACTIONTYPE_BUY;
		if (dword_6FBB5D7C != 0)
		{
			DVar12 = TRANSACTIONTYPE_GAMBLE;
		}
		if ((dword_6FBB5CF9 == 0) || (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
		{
			iVar7 = -1;
		}
		else
		{
			iVar7 = pDVar6->dwClassId;
		}
		pDVar11 = gpBitBuffer_6FBB5D13;
		bVar4 = sub_6FAAC090();
		DVar9 = (D2C_Difficulties)bVar4;
		pDVar6 = CUNIT_GetPlayer();
		iVar7 = ITEMS_GetTransactionCost(pDVar6, pUnit, DVar9, pDVar11, iVar7, DVar12);
		index = 0xd01;
	}
	else
	{
		iVar7 = pUnit->dwClassId;
		if ((dword_6FBB5CF9 == 0) || (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
		{
			return 0;
		}
		if ((dword_6FBB5CF9 == 0) || (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
		{
			uVar5 = 0xffffffff;
		}
		else
		{
			uVar5 = pDVar6->dwClassId;
		}
		DATATBLS_GetItemsTxtRecord(iVar7);
		if (uVar5 < 0xfd)
		{
			if (uVar5 != 0xfc)
			{
				switch (uVar5)
				{
				case 0x93:
				case 0x94:
				case 0xb1:
				case 199:
				case 0xca:
				case 0xf6:
					break;
				default:
					goto switchD_6fafb2c1_caseD_95;
				case 0x9a:
				case 0xb2:
					goto switchD_6fafb2c1_caseD_9a;
				case 0xf4:
				case 0xf5:
					goto switchD_6fafb2c1_caseD_f4;
				}
			}
		}
		else
		{
			if (uVar5 < 0x10a)
			{
				if (uVar5 != 0x109)
				{
					switch (uVar5)
					{
					case 0xfd:
					case 0x101:
						goto switchD_6fafb2c1_caseD_9a;
					case 0xfe:
					case 0xff:
						goto switchD_6fafb2c1_caseD_93;
					default:
						goto switchD_6fafb2c1_caseD_95;
					}
				}
			switchD_6fafb2c1_caseD_f4:
				iVar7 = ITEMS_CheckItemFlag(pUnit, 0x10, __LINE__, __FILE__);
				if (iVar7 == 1)
				{
					*(uint32_t*)pUnicode = 0;
					return 1;
				}
				iVar7 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, 4, 0);
				index = 0xd04;
				iVar7 = (-(uint32_t)(iVar7 != 0) & 0xffffff9c) + 100;
				goto LAB_6fafb532;
			}
			switch (uVar5)
			{
			case 0x195:
			case 0x200:
			case 0x201:
			case 0x202:
				break;
			default:
				goto switchD_6fafb2c1_caseD_95;
			case 0x1ff:
			switchD_6fafb2c1_caseD_9a:
				bVar3 = sub_6FAEB930();
				if (D2C_ZEXT(bVar3) != 0)
				{
					iVar7 = ITEMS_CheckItemFlag(pUnit, 0x10, __LINE__, __FILE__);
					if (iVar7 == 0)
					{
						pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfb6));
						pUVar2 = pUnicode;
						Unicode::strcat(pUnicode, pUVar10);
						sub_6FB20430((short*)pUVar2, '\x01');
						return 1;
					}
					uVar5 = ITEMS_GetItemType(pUnit);
					if (uVar5 == 4)
					{
						return 0;
					}
					iVar7 = ITEMS_IsRepairable(pUnit);
					if (iVar7 == 0)
					{
						return 0;
					}
					iVar7 = ITEMS_HasDurability(pUnit);
					if (((iVar7 == 0) || (iVar7 = STATLIST_GetMaxDurabilityFromUnit(pUnit), iVar7 == 0)) ||
					    (iVar8 = STATLIST_UnitGetStatValue(pUnit, 0x48, 0), iVar7 <= iVar8))
					{
						uVar5 = ITEMS_CheckIfStackable(pUnit);
						if (uVar5 != 0)
						{
							iVar7 = STATLIST_UnitGetStatValue(pUnit, 0x46, 0);
							iVar8 = ITEMS_GetTotalMaxStack(pUnit);
							if (iVar7 < iVar8)
								goto LAB_6fafb45e;
						}
						iVar7 = ITEMS_HasUsedCharges(pUnit, (int*)&a3);
						if ((iVar7 == 0) || (a3 != nullptr))
						{
							return 0;
						}
					}
				LAB_6fafb45e:
					if ((dword_6FBB5CF9 == 0) ||
					    (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
					{
						iVar7 = -1;
					}
					else
					{
						iVar7 = pDVar6->dwClassId;
					}
					DVar12 = TRANSACTIONTYPE_REPAIR;
					pDVar11 = gpBitBuffer_6FBB5D13;
					bVar4 = sub_6FAAC090();
					DVar9 = (D2C_Difficulties)bVar4;
					pDVar6 = CUNIT_GetPlayer();
					iVar7 = ITEMS_GetTransactionCost(pDVar6, pUnit, DVar9, pDVar11, iVar7, DVar12);
					index = 0xd02;
					goto LAB_6fafb532;
				}
			}
		}
	switchD_6fafb2c1_caseD_93:
		iVar7 = ITEMS_IsNotQuestItem(pUnit);
		if (iVar7 == 0)
		{
			return 0;
		}
		if ((dword_6FBB5CF9 == 0) || (pDVar6 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar6 == nullptr))
		{
			iVar7 = -1;
		}
		else
		{
			iVar7 = pDVar6->dwClassId;
		}
		DVar12 = TRANSACTIONTYPE_SELL;
		pDVar11 = gpBitBuffer_6FBB5D13;
		bVar4 = sub_6FAAC090();
		DVar9 = (D2C_Difficulties)bVar4;
		pDVar6 = CUNIT_GetPlayer();
		iVar7 = ITEMS_GetTransactionCost(pDVar6, pUnit, DVar9, pDVar11, iVar7, DVar12);
		index = 0xd03;
	}
LAB_6fafb532:
	*piVar1 = iVar7;
	pUVar10 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
	iVar7 = Unicode::strlen(pUVar10);
	pUVar2 = pUnicode;
	if (iVar7 + 10 <= a5)
	{
		Unicode::strcpy(pUnicode, pUVar10);
		wsprintfA(aCStack_3c, "%d", *piVar1);
		Unicode::win2Unicode(aUStack_28, aCStack_3c, 0x13);
		Unicode::strcat(pUVar2, aUStack_28);
		return 1;
	}
switchD_6fafb2c1_caseD_95:
	return 0;
}

//D2Client.0x6FAFB6D0
bool __cdecl sub_6FAFB6D0()
{
	return byte_6FBB5C3B != 0;
}

//D2Client.0x6FAFB6E0
void __fastcall sub_6FAFB6E0(int* a1, uint16_t a2, int a3)
{
	int iVar1;

	if (((a1 != nullptr) && (*a1 == 1)) && (iVar1 = a1[5], iVar1 != 0))
	{
		if (a3 != 0)
		{
			*(uint16_t*)(iVar1 + 0x28) = *(uint16_t*)(iVar1 + 0x28) | a2;
			return;
		}
		*(uint16_t*)(iVar1 + 0x28) = *(uint16_t*)(iVar1 + 0x28) & ~a2;
	}
}

//D2Client.0x6FAFB710
void __cdecl sub_6FAFB710()
{
	DWORD DVar1;
	DWORD DVar2;
	D2UnitStrc* pDVar3;
	Unicode* pUVar4;
	short index;
	code* pcVar5;
	DWORD DVar6;
	DWORD DVar7;
	DWORD DVar8;
	DWORD DVar9;
	DWORD DVar10;
	int iVar11;
	DWORD DVar12;
	uint32_t uVar13;
	uint32_t uVar14;
	uint32_t uVar15;
	uint32_t uVar16;
	int iVar17;
	int iVar18;
	int iStack_1a4;
	CHAR aCStack_1a0[12];
	Unicode aUStack_194[10];
	Unicode aUStack_180[192];

	D2_ASSERT(!dword_6FBB5D2F);
	uVar16 = 1;
	uVar14 = 0;
	DVar12 = 0;
	DVar10 = 0;
	DVar9 = 1;
	DVar8 = 1;
	DVar7 = 0;
	DVar6 = 0;
	pcVar5 = (code*)(sub_6FAFBAC0);
	byte_6FBB5C3B = 4;
	DVar1 = sub_6FB57BD0();
	DVar2 = sub_6FB57BC0();
	dword_6FBB5D2F = (int)sub_6FAD6BE0(DVar2, DVar1, (DWORD)pcVar5, DVar6, DVar7, DVar8, DVar9, DVar10, DVar12,
	    uVar14, uVar16);
	sub_6FAD7150(dword_6FBB5D2F, 1);
	switch (dword_6FBB5D01)
	{
	case 1:
		iVar18 = 0;
		uVar15 = 0;
		uVar13 = 1;
		iVar11 = 4;
		uVar16 = 0;
		uVar14 = 0x15;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd14));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, uVar15, iVar18);
		iVar11 = 0;
		break;
	case 2:
		iVar18 = 0;
		uVar15 = 0;
		uVar13 = 1;
		iVar11 = 4;
		uVar16 = 0;
		uVar14 = 0x15;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd13));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, uVar15, iVar18);
		iVar11 = 1;
		break;
	case 3:
		index = 0xd17;
		goto LAB_6fafb880;
	case 4:
		index = 0xd16;
	LAB_6fafb880:
		iVar17 = 0;
		uVar15 = 0;
		uVar13 = 1;
		iVar18 = 4;
		uVar16 = 0;
		uVar14 = 0x15;
		iVar11 = 1;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar18, uVar13, uVar15, iVar17);
		break;
	case 5:
		iVar18 = 0;
		uVar15 = 0;
		uVar13 = 1;
		iVar11 = 4;
		uVar16 = 0;
		uVar14 = 0x15;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd18));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, uVar15, iVar18);
		goto LAB_6fafb99d;
	default:
		FOG_DisplayAssert("0", __FILE__, __LINE__);
		exit(-1);
	}
	if (byte_6FBB5BD0 == '\0')
	{
		FOG_Trace("Error at line %d of file %s\n", __LINE__, __FILE__);
	}
	pDVar3 = sub_6FB269F0(dword_6FBB5BD5, 4);
	if (pDVar3 != nullptr)
	{
		sub_6FADD360(0xbf);
		iVar18 = Unicode::strlen(aUStack_180);
		for (iVar17 = 0; iVar17 < iVar18; iVar17 = iVar17 + 1)
		{
			if (aUStack_180[iVar17].ch == 10)
			{
				aUStack_180[iVar17].ch = 0;
				break;
			}
		}
		sub_6FAD7180(dword_6FBB5D2F, aUStack_180, 0xf, 0, 4, 1, (int)(sub_6FAFBA30), 0);
		byte_6FBB5BE5 = 0;
		sub_6FAFB200(pDVar3, iVar11, &iStack_1a4, (Unicode*)&byte_6FBB5BE5, 0x28);
		wsprintfA(aCStack_1a0, "%d", iStack_1a4);
		Unicode::win2Unicode(aUStack_194, aCStack_1a0, 9);
		Unicode::strcpy((Unicode*)&byte_6FBB5BE5, aUStack_194);
		iVar18 = 0;
		pcVar5 = (code*)(sub_6FAFBA30);
		uVar13 = 1;
		iVar11 = 4;
		uVar16 = 0;
		uVar14 = 0xf;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd12));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, (int)(pcVar5), iVar18);
		sub_6FAD7180(dword_6FBB5D2F, (Unicode*)&byte_6FBB5BE5, 0xf, 0, 4, 1, (int)(sub_6FAFBA30), 0);
	LAB_6fafb99d:
		iVar18 = 1;
		pcVar5 = (code*)(sub_6FAFBA30);
		uVar13 = 1;
		iVar11 = 0;
		uVar16 = 0;
		uVar14 = 0xf;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd10));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, (int)(pcVar5), iVar18);
		iVar18 = 1;
		pcVar5 = (code*)(sub_6FAFBAC0);
		uVar13 = 1;
		iVar11 = 0;
		uVar16 = 0;
		uVar14 = 0xf;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd11));
		sub_6FAD7180(dword_6FBB5D2F, pUVar4, uVar14, uVar16, iVar11, uVar13, (int)(pcVar5), iVar18);
	}
}

//D2Client.0x6FAFBA30
uint32_t __cdecl sub_6FAFBA30()
{
	if (dword_6FBB5D01 == 5)
	{
		if (dword_6FBB5D2F != 0)
		{
			sub_6FAD6DC0();
			dword_6FBB5D2F = 0;
		}
		sub_6FAF56D0();
	}
	else
	{
		if (byte_6FBB5C3B == 4)
		{
			if (dword_6FBB5D2F != 0)
			{
				sub_6FAD6DC0();
				dword_6FBB5D2F = 0;
			}
			sub_6FAFA6E0(0, 0);
			return 1;
		}
		sub_6FAB5D40();
		D2_ASSERT(byte_6FBB5C3B != 4);
	}
	return 1;
}

//D2Client.0x6FAFBAC0
uint32_t __cdecl sub_6FAFBAC0()
{
	sub_6FAD6DC0();
	dword_6FBB5D2F = 0;
	if (dword_6FBB5D01 == 5)
	{
		sub_6FAF4E30();
		return 1;
	}
	sub_6FAE9500();
	byte_6FBB5C3B = 3;
	sub_6FAB5D40();
	return 1;
}

//D2Client.0x6FAFBB10
void __fastcall sub_6FAFBB10(int* a1)
{
	if (((a1 != nullptr) && (*a1 == 0)) && (a1[5] != 0))
	{
		*(uint32_t*)(a1[5] + 0x150) = 0;
		*(uint32_t*)(a1[5] + 0x154) = 0;
		*(uint32_t*)(a1[5] + 0x158) = 0;
		*(uint32_t*)(a1[5] + 0x15c) = 0;
	}
}

//D2Client.0x6FAFBB50
int __fastcall sub_6FAFBB50(uint32_t* a1)
{
	*a1 = dword_6FBB5CF5;
	return dword_6FBB5CF9;
}

//D2Client.0x6FAFBB60
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAFBB60(uint32_t a1)
{
	uint32_t* puVar1;
	D2InventoryStrc* pInventory;
	D2UnitStrc* pDVar2;
	D2UnitStrc* pDVar3;
	D2UnitStrc* pDVar4;
	uint32_t* puVar5;
	uint32_t extraout_ECX;

	pDVar2 = CUNIT_GetPlayer();
	if ((((pDVar2 != nullptr) && (pDVar2 = CUNIT_GetPlayer(), pDVar2 != nullptr)) &&
	        (pDVar2->dwUnitType == 0)) &&
	    (pDVar2->pPlayerData != nullptr))
	{
		pDVar2->pPlayerData->unk0xA8[0x2a] = 0;
		pDVar2->pPlayerData->unk0xA8[0x2b] = 0;
		pDVar2->pPlayerData->unk0xA8[0x2c] = 0;
		pDVar2->pPlayerData->unk0xA8[0x2d] = 0;
	}
	if (a1 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar2 = sub_6FB269F0(a1, 1);
	if (pDVar2 != nullptr)
	{
		puVar5 = dword_6FBB5C5D;
		do
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 4;
		} while ((int)puVar5 < (int)&dword_6FBB5CFD);
		pInventory = pDVar2->pInventory;
		if (pInventory != nullptr)
		{
			pDVar2 = INVENTORY_GetFirstItem(pInventory);
			while (pDVar2 != nullptr)
			{
				pDVar3 = INVENTORY_GetNextItem(pDVar2);
				pDVar4 = INVENTORY_UnitIsItem(pDVar2);
				pDVar2 = pDVar3;
				if (pDVar4 != nullptr)
				{
					sub_6FB26BE0(pDVar4->dwUnitId, pDVar4->dwUnitType);
				}
			}
			INVENTORY_RemoveInventoryItems(pInventory);
			D2COMMON_10251_Return((int)pInventory);
		}
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar2 = sub_6FB269F0(a1, 1);
	if (pDVar2 != nullptr)
	{
		pDVar2->dwFlags = pDVar2->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, a1);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar2 == nullptr)
	{
		return;
	}
	if ((pDVar2->dwUnitType == 1) && (pDVar2->pPlayerData != nullptr))
	{
		puVar1 = &pDVar2->pPlayerData->unk0x28;
		*(uint8_t*)puVar1 = (uint8_t)*puVar1 & 0xfe;
	}
	sub_6FB4F410(pDVar2, (int*)0x1);
}

//D2Client.0x6FAFBCC0
void __fastcall sub_6FAFBCC0(int a1)
{
	uint32_t* puVar1;
	int iVar2;

	if (a1 != 0)
	{
		iVar2 = 0;
		puVar1 = dword_6FBB5C5D;
		while (*puVar1 != 0)
		{
			puVar1 = puVar1 + 4;
			iVar2 = iVar2 + 1;
			if ((int)&tbl_6FBB5CFC < (int)puVar1)
			{
				return;
			}
		}
		word_6FBB5C55[iVar2 * 8] = *(uint16_t*)(a1 + 1);
		*(uint32_t*)(word_6FBB5C55 + iVar2 * 8 + 2) = *(uint32_t*)(a1 + 3);
		dword_6FBB5C5D[iVar2 * 4] = 1;
	}
}

//D2Client.0x6FAFBD00
void __cdecl sub_6FAFBD00()
{
	uint32_t* puVar1;

	puVar1 = dword_6FBB5C5D;
	do
	{
		*puVar1 = 0;
		puVar1 = puVar1 + 4;
	} while ((int)puVar1 < (int)&dword_6FBB5CFD);
}

//D2Client.0x6FAFBD20
D2BitBufferStrc* __cdecl sub_6FAFBD20()
{
	return gpBitBuffer_6FBB5D13;
}

//D2Client.0x6FAFBD30
D2BitBufferStrc* __cdecl sub_6FAFBD30()
{
	return gpBitBuffer_6FBB5D17;
}

//D2Client.0x6FAFBD40
void __cdecl sub_6FAFBD40()
{
	uint8_t* puVar1;
	int iVar2;
	uint32_t* puVar3;
	char acStack_104[260];

	word_6FB7A5BC = -1;
	sub_6FAF7C90();
	dword_6FBB5D8C = 0;
	dword_6FBB5D88 = 0;
	GetTickCount();
	puVar3 = (uint32_t*)&byte_6FBB5C38;
	for (iVar2 = 0x57; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	gpBitBuffer_6FBB5D13 = QUESTRECORD_AllocRecord(nullptr);
	gpBitBuffer_6FBB5D17 = QUESTRECORD_AllocRecord(nullptr);
	byte_6FBB5C3B = 0;
	sprintf(acStack_104, "%s\\ui\\panel\\buysell", "DATA\\GLOBAL");
	gpCellFile_6FBB5D98 = CLIENT_LoadCellFile(acStack_104, 0);
	sprintf(acStack_104, "%s\\ui\\menu\\goldbtn", "DATA\\GLOBAL");
	gpCellFile_6FBB5BCC = CLIENT_LoadCellFile(acStack_104, 0);
	dword_6FBB5BDD = 0;
	byte_6FBB5BD0 = '\0';
	byte_6FBB5BE1 = 0;
	dword_6FBB5BD9 = 0;
	byte_6FBB5C3A = 0;
	if (0 < dword_6FB7BD6C)
	{
		puVar1 = byte_6FB7B98A;
		iVar2 = dword_6FB7BD6C;
		do
		{
			puVar1[-1] = 0;
			*puVar1 = 0;
			puVar1 = puVar1 + 0x16;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
	}
}

//D2Client.0x6FAFBE30
void __fastcall sub_6FAFBE30(short a1)
{
	uint16_t* puVar1;

	puVar1 = word_6FBB5C55;
	do
	{
		if (*puVar1 == a1)
			break;
		puVar1 = puVar1 + 8;
	} while ((int)puVar1 < (int)&dword_6FBB5CF5);
	sub_6FADBF00();
}

//D2Client.0x6FAFBE50
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FAFBE50()
{
	int in_ECX;

	if (((in_ECX != 0) && (*(int*)(in_ECX + 4) == 0x13e)) && (*(int*)(in_ECX + 0x10) == 2))
	{
		byte_6FBB5DAC = '\x01';
	}
}

//D2Client.0x6FAFBE70
void __fastcall sub_6FAFBE70(int a1)
{
	D2UnitStrc* pDVar1;
	int iVar2;
	D2UnitStrc* pDVar3;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		if (pDVar1->dwClassId == 0x216)
		{
			iVar2 = sub_6FB40AF0((int*)pDVar1);
			if (iVar2 == -1)
			{
				sub_6FB55820(0x11ff, pDVar1, 0.0, 0.0, 0);
				return;
			}
			sub_6FB55820(0x11fb, pDVar1, 0.0, 0.0, 0);
			return;
		}
		if (dword_6FBB5CF9 == 0)
		{
			pDVar3 = nullptr;
		}
		else
		{
			pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1);
		}
		if ((pDVar1 != pDVar3) && (sub_6FB5BA70(pDVar1, 0x48, 3, 0, 0, 0, 0, 0), pDVar1->dwClassId == 0x14b))
		{
			if ((dword_6FBB5CF9 != 0) &&
			    (pDVar3 = sub_6FB269F0(dword_6FBB5CF5, 1), pDVar3 != nullptr))
			{
				return;
			}
			if (((gpBitBuffer_6FBB5D13 != nullptr) &&
			        (iVar2 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, 0xc, 8), iVar2 == 0)) &&
			    (iVar2 = QUESTRECORD_GetQuestState(gpBitBuffer_6FBB5D13, 0xc, 1), iVar2 == 0))
			{
				byte_6FBB5DAC = '\0';
				sub_6FB297A0((uint8_t*)(sub_6FAFBE50));
				if (byte_6FBB5DAC == '\0')
				{
					sub_6FB55820(0xf8f, pDVar1, 0.0, 0.0, 0);
				}
			}
		}
	}
}

//D2Client.0x6FAFBF80
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAFBF80(uint32_t a1)
{
	D2UnitStrc* pDVar1;
	uint32_t extraout_ECX;

	if (a1 != dword_6FBB5CF5)
	{
		FOG_Trace(" different ids at line %d file %s\n", __LINE__, __FILE__);
	}
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (((pDVar1 != nullptr) && (pDVar1->dwUnitType == 0)) &&
		    (pDVar1->pPlayerData != nullptr))
		{
			pDVar1->pPlayerData->unk0xA8[0x2a] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2b] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2c] = 0;
			pDVar1->pPlayerData->unk0xA8[0x2d] = 0;
		}
	}
	if (a1 != dword_6FBB5CF5)
	{
		FOG_Trace("mismatch npc ids\n");
	}
	pDVar1 = sub_6FB269F0(a1, 1);
	if (pDVar1 != nullptr)
	{
		sub_6FAF78E0((int)pDVar1);
	}
	if (dword_6FBB5D80 != 0)
	{
		sub_6FB556A0(dword_6FBB5D84);
	}
	dword_6FBB5D80 = 0;
	dword_6FBB5D84 = 0;
	pDVar1 = sub_6FB269F0(a1, 1);
	if (pDVar1 != nullptr)
	{
		pDVar1->dwFlags = pDVar1->dwFlags | 2;
	}
	sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, a1);
	sub_6FB1E710();
	dword_6FBB5CF9 = 0;
	sub_6FB23260(8, 1, 0);
	if (pDVar1 != nullptr)
	{
		sub_6FAFB6E0((int*)pDVar1, 1, 0);
		sub_6FB4F410(pDVar1, (int*)0x1);
	}
	pDVar1 = sub_6FB269F0(a1, 1);
	if (pDVar1 != nullptr)
	{
		pDVar1->dwFlags = pDVar1->dwFlags | 2;
	}
}

//D2Client.0x6FAFC0B0
uint32_t __cdecl sub_6FAFC0B0()
{
	D2UnitStrc* pDVar1;

	if (dword_6FBB5CF9 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB5CF5, 1);
		if ((pDVar1 != nullptr) && (byte_6FBB5C3B == 1))
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAFC0E0
uint32_t __cdecl sub_6FAFC0E0()
{
	if ((((dword_6FBB5D2F == 0) && (dword_6FBB5D33 == 0)) && (dword_6FBB5D37 == 0)) &&
	    (((dword_6FBB5D3B == 0 && (dword_6FBB5D3F == 0)) && ((dword_6FBB5D43 == 0 && (dword_6FBB5D47 == 0))))))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FAFC130
int __cdecl sub_6FAFC130()
{
	return dword_6FBB5D7C;
}

//D2Client.0x6FAFC140
void __fastcall sub_6FAFC140(int a1)
{
	code* pcVar1;
	int iVar2;
	uint8_t* puVar3;
	int iVar4;
	uint16_t* puVar5;
	int iVar6;

	iVar2 = dword_6FB7BD6C;
	pcVar1 = (code*)(((uint8_t*)&sgptDataTables));
	puVar5 = (uint16_t*)(a1 + 2);
	iVar6 = 0xc;
	do
	{
		if (((int)(uint32_t)*puVar5 < *(int*)(*(int*)pcVar1 + 0xa80)) && (0 < iVar2))
		{
			puVar3 = byte_6FB7B98A;
			iVar4 = iVar2;
			do
			{
				if (*(uint32_t*)(puVar3 + -0x12) == (uint32_t)*puVar5)
				{
					*puVar3 = 1;
				}
				puVar3 = puVar3 + 0x16;
				iVar4 = iVar4 + -1;
			} while (iVar4 != 0);
		}
		puVar5 = puVar5 + 1;
		iVar6 = iVar6 + -1;
	} while (iVar6 != 0);
}

//D2Client.0x6FAFC190
void __fastcall sub_6FAFC190(short a1, uint32_t a2)
{
	word_6FB7A5BC = a1;
	dword_6FBB5D9C = a2;
	if (a1 == -1)
	{
		sub_6FAF9CB0(0xb, 0);
		sub_6FAF9CB0(8, 0);
		sub_6FAF9CB0(0x18, 0);
		sub_6FAF9CB0(0x15, 0);
		sub_6FAF9CB0(0x2b, 0);
		return;
	}
}

//D2Client.0x6FAFC1F0
void __cdecl sub_6FAFC1F0()
{
	if (gpuint32_t_6FBB5D4F != nullptr)
	{
		if (dword_6FBB5D43 != 0)
		{
			sub_6FAD6DC0();
			if (gpuint32_t_6FBB5D4F != nullptr)
			{
				(**(code**)*gpuint32_t_6FBB5D4F)(1);
			}
			gpuint32_t_6FBB5D4F = nullptr;
			dword_6FBB5D43 = 0;
		}
		sub_6FAF65C0();
		return;
	}
}

//D2Client.0x6FAFC240
void __cdecl sub_6FAFC240()
{
	dword_6FBB5DB0 = (gnViewHeight + -0x1a4) / 2 + 0x2f;
}

//D2Client.0x6FAFC260
void __cdecl sub_6FAFC260()
{
	sub_6FAD49E0(0);
}

//D2Client.0x6FAFC270
void __cdecl sub_6FAFC270()
{
	sub_6FAD4EB0();
	sub_6FB23260(0xb, 1, 0);
	sub_6FB08860(1);
}

//D2Client.0x6FAFC290
void __cdecl sub_6FAFC290()
{
	sub_6FAD4EC0();
	sub_6FB23260(0xb, 1, 0);
	sub_6FB08700(0, 1);
}

//D2Client.0x6FAFC2C0
void __cdecl sub_6FAFC2C0()
{
	char local_104[260];

	sub_6FAFC310();
	sprintf(local_104, (const char*)(dword_6FB7CD5B + 1), "DATA\\GLOBAL");
	gpCellFile_6FBB5DFC = CLIENT_LoadCellFile(local_104, 0);
	sub_6FAFC3F0();
	dword_6FBB5DEC = 0;
	dword_6FBB5DF0 = 0;
}

//D2Client.0x6FAFC310
void __cdecl sub_6FAFC310()
{
	int iVar1;

	iVar1 = sub_6FAAC080();
	if (iVar1 != 0)
	{
		gpuint8_t_6FB7CC94 = &byte_6FB7CA28;
		dword_6FBB5DB4 = 0x3e;
		dword_6FBB5DB8 = 5;
		dword_6FBB5DBC = 0x2f;
		return;
	}
	gpuint8_t_6FB7CC94 = &byte_6FB7C828;
	dword_6FBB5DB4 = 0x33;
	dword_6FBB5DB8 = 6;
	dword_6FBB5DBC = 0x24;
}

//D2Client.0x6FAFC3F0
void __cdecl sub_6FAFC3F0()
{
	Font nFontSize;
	Unicode* wszText;
	int iVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;

	nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	iVar5 = 0;
	uVar6 = 0;
	do
	{
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)&word_6FB7CC98 + uVar6)));
		iVar1 = D2Win_10121_GetTextWidth(wszText);
		iVar3 = gnViewHeight;
		uVar7 = uVar6 + 0x1a;
		iVar4 = (gnScreenWidth + -0x26c) / 2;
		uVar2 = (uint32_t)(gnScreenWidth + iVar4 * -2) / 3;
		iVar4 = iVar4 + uVar2 * iVar5 + uVar2 / 2;
		*(int*)((int)&dword_6FB7CCA6 + uVar6) = iVar1 / 2 + 10 + iVar4;
		*(int*)((int)&dword_6FB7CCA2 + uVar6) = (iVar4 - iVar1 / 2) + -10;
		iVar3 = (iVar3 + -0x1a4) / 2;
		*(int*)((int)&dword_6FB7CCAA + uVar6) = iVar3 + 0x149;
		*(int*)((int)&dword_6FB7CCAE + uVar6) = iVar3 + 0x16f;
		iVar5 = iVar5 + 1;
		uVar6 = uVar7;
	} while (uVar7 < 0x4e);
	D2Win_10127_SetFont(nFontSize);
	sub_6FAFC4C0(0);
}

//D2Client.0x6FAFC4C0
void __fastcall sub_6FAFC4C0(int a1)
{
	int iVar1;
	int iVar2;

	if (a1 < -1)
	{
		if (-1 < a1)
		{
			return;
		}
		iVar1 = -a1;
		do
		{
			sub_6FAFC4C0(-1);
			iVar1 = iVar1 + -1;
		} while (iVar1 != 0);
		return;
	}
	if (1 < a1)
	{
		if (a1 < 1)
		{
			return;
		}
		do
		{
			sub_6FAFC4C0(1);
			a1 = a1 + -1;
		} while (a1 != 0);
		return;
	}
	iVar2 = 0;
	iVar1 = dword_6FBB5DB4;
	do
	{
		iVar1 = iVar1 + -1;
		if (iVar1 < 1)
		{
			iVar1 = 0;
			break;
		}
		iVar2 = iVar2 + 1;
	} while (iVar2 < 0xf);
	iVar2 = dword_6FBB5DEC;
	if (a1 < 0)
	{
		if (0 < dword_6FBB5DEC)
		{
			iVar2 = dword_6FBB5DEC + -1;
		}
		if (iVar2 < 0)
			goto LAB_6fafc563;
	}
	else
	{
		if (a1 < 1)
			goto LAB_6fafc563;
		if (dword_6FBB5DEC < iVar1)
		{
			iVar2 = dword_6FBB5DEC + 1;
		}
		if (iVar1 < iVar2)
			goto LAB_6fafc563;
	}
	dword_6FBB5DEC = iVar2;
LAB_6fafc563:
	dword_6FBB5DB0 = ((dword_6FBB5DB8 * -0xc + 0xf6) * dword_6FBB5DEC) / iVar1 + 0x2f +
	                 (gnViewHeight + -0x1a4) / 2;
}

//D2Client.0x6FAFC590
void __cdecl sub_6FAFC590()
{
	if (gpCellFile_6FBB5DFC != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5DFC);
		gpCellFile_6FBB5DFC = nullptr;
	}
}

//D2Client.0x6FAFC5B0
void __fastcall sub_6FAFC5B0(int a1)
{
	sub_6FAFC310();
	if (a1 != 0)
	{
		if (dword_6FBB5DF8 == 0)
		{
			sub_6FAD4E90();
			sub_6FAD5BE0(0, 0);
			sub_6FAAC0A0();
			sub_6FAB5A90(nullptr);
		}
		dword_6FBB5DEC = 0;
		dword_6FBB5DF0 = 0;
		sub_6FAFC3F0();
		return;
	}
	if (dword_6FBB5DF8 == 0)
	{
		sub_6FAD5BE0(1, 0);
		sub_6FAAC1B0();
		sub_6FAB5D40();
	}
	sub_6FAFC3F0();
}

//D2Client.0x6FAFC620
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFC620()
{
	int iVar1;
	bool bVar2;
	bool bVar3;
	int iVar4;
	int iVar5;
	Font nFontSize;
	int iVar6;
	int iVar7;
	Unicode* pUVar8;
	uint32_t uVar9;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	uint32_t extraout_var_03;
	uint32_t extraout_var_04;
	DWORD DVar10;
	int iVar11;
	int iVar12;
	D2GfxDataStrc* pDVar13;
	int iVar14;
	int iVar15;
	int iVar16;
	int iVar17;
	int bCentered;
	int iStack_58;
	int iStack_54;
	int iStack_50;
	int iStack_4c;
	D2GfxDataStrc DStack_48;

	iVar4 = sub_6FB57BC0();
	iVar5 = sub_6FB57BD0();
	sub_6FAFC310();
	if (((dword_6FBB5E10 != iVar4) || (dword_6FBB5E14 != iVar5)) || (dword_6FBB5DC0 != 0))
	{
		dword_6FBB5E10 = iVar4;
		dword_6FBB5E14 = iVar5;
		sub_6FAFCE10(iVar4, iVar5);
	}
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	iVar6 = (gnScreenWidth + -0x26c) / 2;
	sub_6FB5B0F0(iVar6, (gnViewHeight + -0x1a4) / 2, gnScreenWidth + iVar6 * -2, 0x171, 0, (DrawMode)(1));
	iStack_58 = (gnScreenWidth + -0x26c) / 2;
	iStack_4c = (gnViewHeight + -0x1a4) / 2;
	iStack_50 = (gnScreenWidth - iStack_58) + -3;
	iStack_54 = iStack_4c + 3;
	iStack_4c = iStack_4c + 0x170;
	sub_6FB21790(&iStack_58);
	iStack_54 = (gnViewHeight + -0x1a4) / 2 + 0x143;
	sub_6FB21790(&iStack_58);
	iVar15 = 0;
	iVar14 = 4;
	iVar7 = (gnViewHeight + -0x1a4) / 2 + 0x1e;
	iVar6 = gnScreenWidth + -0x26c;
	pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf51));
	D2Win_10117_DrawText(pUVar8, iVar6 / 2 + 0x12, iVar7, iVar14, iVar15);
	iVar16 = 0;
	iVar14 = (gnScreenWidth + -0x26c) / 2;
	iVar15 = 4;
	iVar6 = (gnViewHeight + -0x1a4) / 2 + 0x1e;
	iVar7 = gnScreenWidth + iVar14 * -2;
	pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf52));
	D2Win_10117_DrawText(pUVar8, (iVar7 + -0x31) / 3 + 0x12 + iVar14, iVar6, iVar15, iVar16);
	iVar16 = 0;
	iVar15 = 4;
	iVar14 = (gnScreenWidth + -0x26c) / 2;
	iVar6 = (gnViewHeight + -0x1a4) / 2 + 0x1e;
	iVar7 = gnScreenWidth + iVar14 * -2;
	pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf53));
	D2Win_10117_DrawText(pUVar8, iVar14 + 0x12 + ((iVar7 + -0x31) / 3) * 2, iVar6, iVar15, iVar16);
	iVar6 = 0;
	iVar7 = 0;
	do
	{
		iVar14 = gnScreenWidth;
		if (dword_6FBB5DB4 <= iVar6)
			break;
		iVar16 = iVar7 + 0x22 + (gnViewHeight + -0x1a4) / 2;
		iVar15 = dword_6FBB5DEC + iVar6;
		if (((dword_6FBB5DF8 == 0) || (iVar15 != dword_6FBB5DF0)) ||
		    (bVar3 = false, 4 < ((uint8_t)dword_6FBB5E0C & 0xf)))
		{
			bVar3 = true;
		}
		iVar7 = iVar7 + 0x12;
		iVar1 = iVar15 * 10;
		iVar6 = iVar6 + 1;
		if (*(int*)(gpuint8_t_6FB7CC94 + iVar1) != 0x39)
		{
			if (iVar15 == dword_6FBB5DF0)
			{
				iVar14 = (gnScreenWidth + -0x26c) / 2;
				sub_6FB5B0F0(iVar14 + 0x12, iVar16 + 1, ((gnScreenWidth + iVar14 * -2 + -0x31) / 3) * 3, 0x12, 0,
				    (DrawMode)(1));
				iVar14 = gnScreenWidth;
				iVar11 = iVar16 + 0x12;
				iVar17 = 0;
				uVar9 = -(uint32_t)(dword_6FBB5DF8 != 0) & 3;
				pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(gpuint8_t_6FB7CC94 + iVar1 + 4)));
			}
			else
			{
				iVar11 = iVar16 + 0x12;
				iVar17 = 0;
				uVar9 = 0;
				pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(gpuint8_t_6FB7CC94 + iVar1 + 4)));
			}
			iVar16 = iVar16 + 0x12;
			D2Win_10117_DrawText(pUVar8, (iVar14 + -0x26c) / 2 + 0x1e, iVar11, uVar9, iVar17);
			if ((bVar3) || (dword_6FB7CCE8 == 0))
			{
				if ((iVar15 == dword_6FBB5DF0) && ((dword_6FBB5DF8 != 0 || (dword_6FB7CCE8 == 1))))
				{
					iVar14 = 3;
				}
				else
				{
					bVar2 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 1);
					if ((D2C_ZEXT(bVar2) == 0) &&
					    (bVar2 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 0),
					        D2C_ZEXT(bVar2) == 0))
					{
						iVar14 = 1;
					}
					else
					{
						bVar2 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 1);
						iVar14 = 5 - (uint32_t)(D2C_ZEXT(bVar2) != 0);
					}
				}
				bCentered = 0;
				iVar12 = (gnScreenWidth + -0x26c) / 2;
				iVar17 = gnScreenWidth + iVar12 * -2;
				iVar11 = iVar16;
				pUVar8 = sub_6FAD4F50(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 1);
				D2Win_10117_DrawText(pUVar8, (iVar17 + -0x31) / 3 + 0x1e + iVar12, iVar11, iVar14, bCentered);
				if ((!bVar3) && (dword_6FB7CCE8 == 0))
					goto LAB_6fafcaf8;
			}
			if ((iVar15 == dword_6FBB5DF0) && ((dword_6FBB5DF8 != 0 || (dword_6FB7CCE8 == 0))))
			{
				iVar14 = 3;
			}
			else
			{
				bVar3 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 1);
				if ((D2C_ZEXT(bVar3) == 0) &&
				    (bVar3 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 0),
				        D2C_ZEXT(bVar3) == 0))
				{
					iVar14 = 1;
				}
				else
				{
					bVar3 = sub_6FAD4F00(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 0);
					iVar14 = 5 - (uint32_t)(D2C_ZEXT(bVar3) != 0);
				}
			}
			iVar17 = 0;
			iVar11 = (gnScreenWidth + -0x26c) / 2;
			iVar15 = gnScreenWidth + iVar11 * -2;
			pUVar8 = sub_6FAD4F50(*(int*)(gpuint8_t_6FB7CC94 + iVar1), 0);
			D2Win_10117_DrawText(pUVar8, iVar11 + 0x1e + ((iVar15 + -0x31) / 3) * 2, iVar16, iVar14, iVar17);
		}
	LAB_6fafcaf8:
	} while (iVar6 < 0xf);
	pDVar13 = &DStack_48;
	for (iVar6 = 0x12; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		pDVar13->pCurrentCell = nullptr;
		pDVar13 = (D2GfxDataStrc*)&pDVar13->pCellFile;
	}
	DStack_48.pCellFile = gpCellFile_6FBB5DFC;
	iVar7 = 0;
	DStack_48.nFrame = 0xd;
	iVar6 = 0;
	do
	{
		TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - (gnScreenWidth + -0x26c) / 2) + -0x1f,
		    iVar6 + 0x3b + (gnViewHeight + -0x1a4) / 2, 0xffffffff, DRAWMODE_NORMAL,
		    nullptr);
		iVar7 = iVar7 + 1;
		iVar6 = iVar6 + 0xc;
	} while (iVar7 < 0x15);
	iVar6 = 0;
	DStack_48.nFrame = 0xe;
	if (0 < dword_6FBB5DB8)
	{
		iVar7 = 0xc;
		do
		{
			TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - (gnScreenWidth + -0x26c) / 2) + -0x20,
			    dword_6FBB5DB0 + iVar7, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			iVar6 = iVar6 + 1;
			iVar7 = iVar7 + 0xc;
		} while (iVar6 < dword_6FBB5DB8);
	}
	if ((((dword_6FBB5DCC == 0) ||
	         (iVar6 = (gnScreenWidth + -0x26c) / 2, iVar4 < (gnScreenWidth - iVar6) + -0x1f)) ||
	        ((gnScreenWidth - iVar6) + -0x12 < iVar4)) ||
	    ((iVar6 = (gnViewHeight + -0x1a4) / 2, iVar5 < iVar6 + 0x23 ||
	                                               (DStack_48.nFrame = 9, iVar6 + 0x2f < iVar5))))
	{
		DStack_48.nFrame = 0xb;
	}
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - (gnScreenWidth + -0x26c) / 2) + -0x1f,
	    (gnViewHeight + -0x1a4) / 2 + 0x2f, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	if (((dword_6FBB5DD0 == 0) ||
	        (iVar6 = (gnScreenWidth + -0x26c) / 2, iVar4 < (gnScreenWidth - iVar6) + -0x1f)) ||
	    (((gnScreenWidth - iVar6) + -0x12 < iVar4 ||
	        ((iVar4 = (gnViewHeight + -0x1a4) / 2, iVar5 < iVar4 + 0x125 ||
	                                                   (DStack_48.nFrame = 8, iVar4 + 0x131 < iVar5))))))
	{
		DStack_48.nFrame = 10;
	}
	TEXTURE_CelDraw(&DStack_48, (gnScreenWidth - (gnScreenWidth + -0x26c) / 2) + -0x1f,
	    (gnViewHeight + -0x1a4) / 2 + 0x131, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	iVar4 = 0;
	uVar9 = 0;
	do
	{
		if (iVar4 == dword_6FBB5DF4)
		{
			iVar5 = *(int*)((int)&dword_6FB7CC9E + uVar9);
		}
		else
		{
			iVar5 = 4;
		}
		iVar6 = *(int*)((int)&dword_6FB7CCA2 + uVar9);
		iVar14 = 0;
		iVar7 = (gnViewHeight + -0x1a4) / 2 + 0x15f;
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)((int)&word_6FB7CC98 + uVar9)));
		D2Win_10117_DrawText(pUVar8, iVar6 + 10, iVar7, iVar5, iVar14);
		uVar9 = uVar9 + 0x1a;
		iVar4 = iVar4 + 1;
	} while (uVar9 < 0x4e);
	DVar10 = GetTickCount();
	if (DVar10 < dword_6FBB5E08 + 2000)
	{
		iVar6 = gnScreenWidth / 2;
		iVar4 = (gnViewHeight + -0x1a4) / 2 + 399;
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)byte_6FBB5E04));
		iVar5 = D2Win_10121_GetTextWidth(pUVar8);
		iVar14 = 1;
		iVar7 = 1;
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)byte_6FBB5E04));
		D2Win_10117_DrawText(pUVar8, iVar6 - iVar5 / 2, iVar4, iVar7, iVar14);
	}
	D2Win_10127_SetFont(nFontSize);
	dword_6FBB5E0C = dword_6FBB5E0C + 1;
}

//D2Client.0x6FAFCE10
void __fastcall sub_6FAFCE10(int a1, int a2)
{
	bool bVar1;
	bool bVar2;
	bool bVar3;
	bool bVar4;
	bool bVar5;
	bool bVar6;
	int iVar7;
	int iVar8;
	int* piVar9;
	int iVar10;
	DWORD DVar11;
	uint32_t uVar12;
	int iVar13;

	dword_6FBB5DF4 = 3;
	if (dword_6FBB5DC4 != 0)
	{
		dword_6FBB5DF4 = 3;
		return;
	}
	iVar13 = (gnScreenWidth + -0x26c) / 2;
	if ((((a1 < iVar13 + 0x12) ||
	         (iVar13 + ((gnScreenWidth + iVar13 * -2 + -0x31) / 3 + 6) * 3 < a1)) ||
	        (iVar7 = (gnViewHeight + -0x1a4) / 2, a2 < iVar7 + 0x28)) ||
	    (bVar1 = true, iVar7 + 0x136 < a2))
	{
		bVar1 = false;
	}
	iVar7 = (gnScreenWidth - iVar13) + -0x1f;
	if (((a1 < iVar7) || ((gnScreenWidth - iVar13) + -0x12 < a1)) ||
	    ((iVar8 = (gnViewHeight + -0x1a4) / 2, a2 < iVar8 + 0x23 || (iVar8 + 0x2f < a2))))
	{
		bVar2 = false;
	}
	else
	{
		bVar2 = true;
	}
	if (((a1 < iVar7) || ((gnScreenWidth - iVar13) + -0x12 < a1)) ||
	    ((iVar8 = (gnViewHeight + -0x1a4) / 2, a2 < iVar8 + 0x125 ||
	                                               (bVar3 = true, iVar8 + 0x131 < a2))))
	{
		bVar3 = false;
	}
	if ((((a1 < iVar7) || ((gnScreenWidth - iVar13) + -0x12 < a1)) ||
	        (a2 <= (gnViewHeight + -0x1a4) / 2 + 0x2f)) ||
	    (bVar4 = true, dword_6FBB5DB0 <= a2))
	{
		bVar4 = false;
	}
	if (((a1 < iVar7) || ((gnScreenWidth - iVar13) + -0x12 < a1)) ||
	    ((a2 < dword_6FBB5DB0 || (bVar5 = true, dword_6FBB5DB0 + dword_6FBB5DB8 * 0xc < a2))))
	{
		bVar5 = false;
	}
	if (((a1 < iVar7) || ((gnScreenWidth - iVar13) + -0x12 < a1)) ||
	    (((gnViewHeight + -0x1a4) / 2 + 0x125 <= a2 ||
	        (bVar6 = true, a2 <= dword_6FBB5DB0 + dword_6FBB5DB8 * 0xc))))
	{
		bVar6 = false;
	}
	iVar13 = sub_6FAFD520(a1, a2);
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != (int*)(&dword_6FBB5DE4)))
			goto LAB_6fafd08d;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if ((((!bVar1) && (!bVar2)) && (!bVar3)) &&
	    (((!bVar4 && (!bVar5)) && ((!bVar6 && (iVar13 == 3))))))
	{
		dword_6FBB5DC4 = dword_6FBB5DC0;
		return;
	}
LAB_6fafd08d:
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		iVar7 = dword_6FBB5DF0;
		uVar12 = dword_6FB7CCE8;
		if ((*piVar9 != 0) && (piVar9 != (int*)(&dword_6FBB5DC8)))
			goto LAB_6fafd1dc;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (((bVar1) || (dword_6FBB5DC8 != 0)) && (dword_6FBB5DC8 = dword_6FBB5DC0, dword_6FBB5DC0 != 0))
	{
		if (a2 < (gnViewHeight + -0x1a4) / 2 + 0x28)
		{
			sub_6FAFD470(-1);
		}
		if ((gnViewHeight + -0x1a4) / 2 + 0x136 < a2)
		{
			sub_6FAFD470(1);
		}
		iVar8 = 0;
		if (dword_6FBB5DEC < dword_6FBB5DB4)
		{
			iVar10 = (gnViewHeight + -0x1a4) / 2 + 0x3a;
			iVar7 = dword_6FBB5DEC;
			do
			{
				if (0xe < iVar8)
				{
					if (iVar7 < dword_6FBB5DB4)
						goto LAB_6fafd16e;
					break;
				}
				if (a2 <= iVar10)
					goto LAB_6fafd16e;
				iVar8 = iVar8 + 1;
				iVar10 = iVar10 + 0x12;
				iVar7 = iVar7 + 1;
			} while (iVar7 < dword_6FBB5DB4);
		}
		iVar7 = dword_6FBB5DB4;
		if (-1 < dword_6FBB5DB4)
		{
			iVar7 = dword_6FBB5DB4 + -1;
		}
	LAB_6fafd16e:
		iVar8 = (gnScreenWidth + -0x26c) / 2;
		uVar12 = (uint32_t)(a1 < iVar8 + 0x12 + ((gnScreenWidth + iVar8 * -2 + -0x31) / 3) * 2);
		if (*(int*)(gpuint8_t_6FB7CC94 + iVar7 * 10) == 0x39)
		{
			uVar12 = dword_6FB7CCE8;
			iVar7 = dword_6FBB5DF0;
		}
	}
LAB_6fafd1dc:
	dword_6FBB5DF0 = iVar7;
	dword_6FB7CCE8 = uVar12;
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != &dword_6FBB5DCC))
			goto LAB_6fafd234;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (((bVar2) && (dword_6FBB5DCC = dword_6FBB5DC0, dword_6FBB5DC0 != 0)) &&
	    (DVar11 = GetTickCount(), dword_6FBB5E00 + 0x32 < DVar11))
	{
		dword_6FBB5E00 = GetTickCount();
		sub_6FAFC4C0(-1);
	}
LAB_6fafd234:
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != &dword_6FBB5DD0))
			goto LAB_6fafd287;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (((bVar3) && (dword_6FBB5DD0 = dword_6FBB5DC0, dword_6FBB5DC0 != 0)) &&
	    (DVar11 = GetTickCount(), dword_6FBB5E00 + 0x32 < DVar11))
	{
		dword_6FBB5E00 = GetTickCount();
		sub_6FAFC4C0(1);
	}
LAB_6fafd287:
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != (int*)&byte_6FBB5DD4))
			goto LAB_6fafd2eb;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (((bVar4) && (byte_6FBB5DD4 = dword_6FBB5DC0, dword_6FBB5DC0 != 0)) &&
	    (DVar11 = GetTickCount(), dword_6FBB5E00 + 0x32 < DVar11))
	{
		dword_6FBB5E00 = GetTickCount();
		sub_6FAFC4C0(-0xe);
	}
LAB_6fafd2eb:
	iVar7 = dword_6FBB5DC0;
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != (int*)(&dword_6FBB5DD8)))
			goto LAB_6fafd3a3;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (bVar5)
	{
		if ((dword_6FBB5DD8 == 0) && (dword_6FBB5DC0 != 0))
		{
			dword_6FBB5DE4 = dword_6FBB5DB0;
			dword_6FBB5DE8 = a2;
		}
	}
	else if (dword_6FBB5DD8 == 0)
		goto LAB_6fafd3a3;
	dword_6FBB5DD8 = dword_6FBB5DC0;
	if (dword_6FBB5DC0 != 0)
	{
		sub_6FAFC4C0(((((dword_6FBB5DE4 - (gnViewHeight + -0x1a4) / 2) - dword_6FBB5DE8) + -0x2f + a2) * (dword_6FBB5DBC + 1)) / (dword_6FBB5DB8 * -0xc + 0xf6) - dword_6FBB5DEC);
	}
LAB_6fafd3a3:
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != (int*)&byte_6FBB5DDC))
			goto LAB_6fafd405;
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (((bVar6) && (byte_6FBB5DDC = iVar7, iVar7 != 0)) &&
	    (DVar11 = GetTickCount(), iVar7 = dword_6FBB5DC0, dword_6FBB5E00 + 0x32 < DVar11))
	{
		dword_6FBB5E00 = GetTickCount();
		sub_6FAFC4C0(0xe);
		iVar7 = dword_6FBB5DC0;
	}
LAB_6fafd405:
	piVar9 = (int*)(&dword_6FBB5DC8);
	do
	{
		if ((*piVar9 != 0) && (piVar9 != &dword_6FBB5DE0))
		{
			return;
		}
		piVar9 = piVar9 + 1;
	} while ((int)piVar9 < (int)&dword_6FBB5DE4);
	if (iVar13 != 3)
	{
		dword_6FBB5DF4 = 0;
		uVar12 = 0;
		do
		{
			if (((*(int*)((int)&dword_6FB7CCA2 + uVar12) <= a1) &&
			        (a1 <= *(int*)((int)&dword_6FB7CCA6 + uVar12))) &&
			    ((*(int*)((int)&dword_6FB7CCAA + uVar12) <= a2 &&
			        (a2 <= *(int*)((int)&dword_6FB7CCAE + uVar12)))))
			{
				dword_6FBB5DE0 = iVar7;
				return;
			}
			uVar12 = uVar12 + 0x1a;
			dword_6FBB5DF4 = dword_6FBB5DF4 + 1;
			dword_6FBB5DE0 = iVar7;
		} while (uVar12 < 0x4e);
	}
}

//D2Client.0x6FAFD470
void __fastcall sub_6FAFD470(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar3 = dword_6FBB5DB4;
	if (a1 == 0)
	{
		return;
	}
	if (a1 < -1)
	{
		if (-1 < a1)
		{
			return;
		}
		iVar3 = -a1;
		do
		{
			sub_6FAFD470(-1);
			iVar3 = iVar3 + -1;
		} while (iVar3 != 0);
		return;
	}
	if (1 < a1)
	{
		if (a1 < 1)
		{
			return;
		}
		do
		{
			sub_6FAFD470(1);
			a1 = a1 + -1;
		} while (a1 != 0);
		return;
	}
	if (a1 < 0)
	{
		iVar1 = dword_6FBB5DF0;
		if (0 < dword_6FBB5DF0)
		{
			iVar1 = dword_6FBB5DF0 + -1;
		}
		if (iVar1 < 0)
			goto LAB_6fafd4e0;
	}
	else if (((a1 < 1) || (dword_6FBB5DB4 <= dword_6FBB5DF0)) ||
	         (iVar1 = dword_6FBB5DF0 + 1, dword_6FBB5DB4 <= iVar1))
		goto LAB_6fafd4e0;
	dword_6FBB5DF0 = iVar1;
LAB_6fafd4e0:
	iVar1 = dword_6FBB5DF0;
	if (dword_6FBB5DEC <= dword_6FBB5DF0)
	{
		while (true)
		{
			iVar2 = dword_6FBB5DEC;
			for (iVar4 = 0; (iVar2 < iVar3 && (iVar4 < 0xf)); iVar4 = iVar4 + 1)
			{
				iVar2 = iVar2 + 1;
			}
			if (iVar1 < iVar2)
				break;
			sub_6FAFC4C0(1);
		}
		return;
	}
	dword_6FBB5DEC = dword_6FBB5DF0;
	sub_6FAFC4C0(0);
}

//D2Client.0x6FAFD520
int __fastcall sub_6FAFD520(int a1, int a2)
{
	int iVar1;
	uint32_t uVar2;

	iVar1 = 0;
	uVar2 = 0;
	while ((((a1 < *(int*)((int)&dword_6FB7CCA2 + uVar2) ||
	             (*(int*)((int)&dword_6FB7CCA6 + uVar2) < a1)) ||
	            (a2 < *(int*)((int)&dword_6FB7CCAA + uVar2))) ||
	        (*(int*)((int)&dword_6FB7CCAE + uVar2) < a2)))
	{
		uVar2 = uVar2 + 0x1a;
		iVar1 = iVar1 + 1;
		if (0x4d < uVar2)
		{
			return iVar1;
		}
	}
	return iVar1;
}

//D2Client.0x6FAFD550
void __cdecl sub_6FAFD550(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	dword_6FBB5DC0 = 1;
	sub_6FAFCE10((uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam, (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2));
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFD5A0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFD5A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	uint32_t uVar5;
	uint32_t* puVar6;
	uint32_t uVar7;

	iVar2 = sub_6FAABF20();
	if (iVar2 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	uVar4 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar5 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if (dword_6FBB5DC8 != 0)
	{
		iVar2 = (gnScreenWidth + -0x26c) / 2;
		if ((((iVar2 + 0x12 <= (int)uVar4) &&
		         ((int)uVar4 <= iVar2 + ((gnScreenWidth + iVar2 * -2 + -0x31) / 3 + 6) * 3)) &&
		        (iVar2 = (gnViewHeight + -0x1a4) / 2, iVar2 + 0x28 <= (int)uVar5)) &&
		    ((int)uVar5 <= iVar2 + 0x136))
		{
			iVar2 = sub_6FAFD7E0(uVar5);
			if (((iVar2 == dword_6FBB5DF0) &&
			        (iVar2 = (gnScreenWidth + -0x26c) / 2,
			            (uint32_t)((int)uVar4 < iVar2 + 0x12 + ((gnScreenWidth + iVar2 * -2 + -0x31) / 3) * 2) ==
			                dword_6FB7CCE8)) &&
			    (*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10) != 0x39))
			{
				dword_6FBB5DF8 = 1;
				sub_6FB22D60(0xb);
				uVar7 = 6;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar7);
				iVar2 = sub_6FAAB2E0();
				if (iVar2 != 0)
				{
					uVar7 = 1;
					pHVar3 = WINDOW_GetWindow();
					WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar7);
				}
				iVar2 = sub_6FAAB320();
				if (iVar2 != 0)
				{
					uVar7 = 1;
					pHVar3 = WINDOW_GetWindow();
					WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar7);
				}
				bVar1 = sub_6FAAB290();
				if (D2C_ZEXT(bVar1) != 0)
				{
					uVar7 = 1;
					pHVar3 = WINDOW_GetWindow();
					WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar7);
				}
				sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
			}
		}
	}
	if ((dword_6FBB5DE0 != 0) && (dword_6FBB5DF4 != 3))
	{
		iVar2 = 0;
		uVar7 = 0;
		do
		{
			if ((((*(int*)((int)&dword_6FB7CCA2 + uVar7) <= (int)uVar4) &&
			         ((int)uVar4 <= *(int*)((int)&dword_6FB7CCA6 + uVar7))) &&
			        (*(int*)((int)&dword_6FB7CCAA + uVar7) <= (int)uVar5)) &&
			    ((int)uVar5 <= *(int*)((int)&dword_6FB7CCAE + uVar7)))
				break;
			uVar7 = uVar7 + 0x1a;
			iVar2 = iVar2 + 1;
		} while (uVar7 < 0x4e);
		if (iVar2 == dword_6FBB5DF4)
		{
			(**(code**)(byte_6FB7CC9A + dword_6FBB5DF4 * 0x1a))();
			sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
		}
	}
	puVar6 = &dword_6FBB5DC8;
	for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	dword_6FBB5DC4 = 0;
	dword_6FBB5DC0 = 0;
	sub_6FAFCE10(uVar4, uVar5);
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFD7E0
int __fastcall sub_6FAFD7E0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar2 = 0;
	if (dword_6FBB5DEC < dword_6FBB5DB4)
	{
		iVar1 = (gnViewHeight + -0x1a4) / 2 + 0x3a;
		iVar3 = dword_6FBB5DEC;
		do
		{
			if (0xe < iVar2)
			{
				if (iVar3 < dword_6FBB5DB4)
				{
					return iVar3;
				}
				break;
			}
			if (a1 <= iVar1)
			{
				return iVar3;
			}
			iVar2 = iVar2 + 1;
			iVar1 = iVar1 + 0x12;
			iVar3 = iVar3 + 1;
		} while (iVar3 < dword_6FBB5DB4);
	}
	iVar2 = dword_6FBB5DB4;
	if (-1 < dword_6FBB5DB4)
	{
		iVar2 = dword_6FBB5DB4 + -1;
	}
	return iVar2;
}

//D2Client.0x6FAFD830
void __cdecl sub_6FAFD830(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	iVar1 = (int)*(short*)((int)&pSMSGHANDLER_PARAMS->wParam + 2) / 0x78;
	if (iVar1 != 0)
	{
		sub_6FAFC4C0(iVar1 * -2);
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFD8A0
void __cdecl sub_6FAFD8A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint8_t* puVar1;
	int iVar2;
	int iVar3;

	iVar3 = sub_6FAABF20();
	iVar2 = dword_6FBB5DF0;
	puVar1 = gpuint8_t_6FB7CC94;
	if (iVar3 == 0)
	{
		do
		{
			sub_6FAFD470(-1);
		} while (*(int*)(puVar1 + dword_6FBB5DF0 * 10) == 0x39);
		if (iVar2 != dword_6FBB5DF0)
		{
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAFD910
void __cdecl sub_6FAFD910(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint8_t* puVar1;
	int iVar2;
	int iVar3;

	iVar3 = sub_6FAABF20();
	iVar2 = dword_6FBB5DF0;
	puVar1 = gpuint8_t_6FB7CC94;
	if (iVar3 == 0)
	{
		do
		{
			sub_6FAFD470(1);
		} while (*(int*)(puVar1 + dword_6FBB5DF0 * 10) == 0x39);
		if (iVar2 != dword_6FBB5DF0)
		{
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 0;
}

//D2Client.0x6FAFD980
void __cdecl sub_6FAFD980(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FB7CCE8 == 0)
	{
		dword_6FB7CCE8 = 1;
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFD9E0
void __cdecl sub_6FAFD9E0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FB7CCE8 == 1)
	{
		dword_6FB7CCE8 = 0;
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDA40
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFDA40(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint32_t uVar4;

	iVar2 = sub_6FAABF20();
	if (iVar2 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FB7CCEC == 0)
	{
		dword_6FB7CCEC = 1;
	}
	else if (((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0) &&
	         (*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10) != 0x39))
	{
		dword_6FBB5DF8 = 1;
		sub_6FB22D60(0xb);
		uVar4 = 6;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar4);
		iVar2 = sub_6FAAB2E0();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar4);
		}
		iVar2 = sub_6FAAB320();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar4);
		}
		bVar1 = sub_6FAAB290();
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar4);
		}
		sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
		dword_6FB7CCEC = 0;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDB50
void __cdecl sub_6FAFDB50(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FB7CCEC == 0)
	{
		dword_6FB7CCEC = 1;
	}
	else if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		sub_6FAD4EE0(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8);
		sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDBD0
void __cdecl sub_6FAFDBD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	if (dword_6FB7CCEC == 0)
	{
		dword_6FB7CCEC = 1;
	}
	else if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		sub_6FAD4EC0();
		sub_6FB23260(0xb, 1, 0);
		sub_6FB08700(0, 1);
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDC60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFDC60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	bool bVar2;
	int iVar3;
	HWND__* pHVar4;
	uint32_t extraout_var;
	int iVar5;
	uint32_t uVar6;

	iVar3 = sub_6FAABF20();
	if (iVar3 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	iVar3 = pSMSGHANDLER_PARAMS->lParam;
	uVar1 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	uVar6 = 6;
	pHVar4 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar6);
	bVar2 = sub_6FAAB290();
	if (D2C_ZEXT(bVar2) != 0)
	{
		uVar6 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar6);
	}
	iVar5 = sub_6FAAB320();
	if (iVar5 != 0)
	{
		uVar6 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar6);
	}
	iVar5 = sub_6FAAB2E0();
	if (iVar5 != 0)
	{
		uVar6 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar6);
	}
	sub_6FB24790();
	dword_6FBB5DF8 = 0;
	dword_6FBB5DC0 = 1;
	sub_6FAFCE10((uint32_t)(uint16_t)iVar3, (uint32_t)uVar1);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDD30
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFDD30(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint16_t extraout_var_01;
	uint32_t uVar4;
	uint32_t local_4;

	iVar2 = sub_6FAABF20();
	if (iVar2 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	local_4 = 0;
	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) != 0)
		goto LAB_6fafdeeb;
	if (pSMSGHANDLER_PARAMS->wParam == 0x1b)
	{
		uVar4 = 6;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar4);
		bVar1 = sub_6FAAB290();
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar4);
		}
		iVar2 = sub_6FAAB320();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar4);
		}
		iVar2 = sub_6FAAB2E0();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar4);
		}
		sub_6FB24790();
		dword_6FBB5DF8 = 0;
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		dword_6FB7CCEC = 0;
	}
	else
	{
		iVar2 = sub_6FAD4D20(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8,
		    (void*)D2C_ZEXT((short)pSMSGHANDLER_PARAMS->wParam),
		    (uint16_t*)&local_4);
		if (iVar2 != 0)
		{
			uVar4 = 6;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar4);
			bVar1 = sub_6FAAB290();
			if (D2C_ZEXT(bVar1) != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar4);
			}
			iVar2 = sub_6FAAB320();
			if (iVar2 != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar4);
			}
			iVar2 = sub_6FAAB2E0();
			if (iVar2 != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar4);
			}
			sub_6FB24790();
			dword_6FBB5DF8 = 0;
			sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
			uVar4 = pSMSGHANDLER_PARAMS->wParam;
			if ((((uVar4 == 0xd) || (uVar4 == 0x2e)) || (uVar4 == 8)) || (uVar4 == 0x20))
			{
				dword_6FB7CCEC = 0;
				goto LAB_6fafded1;
			}
		}
		dword_6FB7CCEC = 1;
	}
LAB_6fafded1:
	if ((short)local_4 != 0)
	{
		byte_6FBB5E04 = (short)local_4;
		dword_6FBB5E08 = GetTickCount();
	}
LAB_6fafdeeb:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFDF10
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFDF10(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint16_t extraout_var_00;
	uint32_t uVar4;
	uint32_t local_4;

	iVar2 = sub_6FAABF20();
	if (iVar2 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	local_4 = 0;
	if (dword_6FB7CCEC == 0)
	{
		dword_6FB7CCEC = 1;
	}
	else
	{
		iVar2 = sub_6FAD4D20(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8,
		    (void*)D2C_ZEXT((short)pSMSGHANDLER_PARAMS->wParam),
		    (uint16_t*)&local_4);
		if (iVar2 != 0)
		{
			uVar4 = 6;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar4);
			bVar1 = sub_6FAAB290();
			if (D2C_ZEXT(bVar1) != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar4);
			}
			iVar2 = sub_6FAAB320();
			if (iVar2 != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar4);
			}
			iVar2 = sub_6FAAB2E0();
			if (iVar2 != 0)
			{
				uVar4 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar4);
			}
			sub_6FB24790();
			dword_6FBB5DF8 = 0;
			sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
		}
		if ((short)local_4 != 0)
		{
			byte_6FBB5E04 = (short)local_4;
			dword_6FBB5E08 = GetTickCount();
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFE040
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFE040(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	uint32_t local_4;

	iVar2 = sub_6FAABF20();
	if (iVar2 != 0)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 0;
		return;
	}
	local_4 = 0;
	iVar2 = sub_6FAD4D20(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8, (void*)0x100,
	    (uint16_t*)&local_4);
	if (iVar2 == 0)
	{
		if ((short)local_4 != 0)
		{
			byte_6FBB5E04 = (short)local_4;
			dword_6FBB5E08 = GetTickCount();
		}
	}
	else
	{
		uVar4 = 6;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar4);
		bVar1 = sub_6FAAB290();
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar4);
		}
		iVar2 = sub_6FAAB320();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar4);
		}
		iVar2 = sub_6FAAB2E0();
		if (iVar2 != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar4);
		}
		sub_6FB24790();
		dword_6FBB5DF8 = 0;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAFE140
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFE140(int a1)
{
	int pData;
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	void* pvVar4;
	uint32_t uVar5;

	iVar2 = sub_6FAABF20();
	pData = a1;
	if (iVar2 != 0)
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	if (*(short*)(a1 + 10) == 1)
	{
		pvVar4 = (void*)0x101;
	}
	else
	{
		if (*(short*)(a1 + 10) != 2)
			goto LAB_6fafe23a;
		pvVar4 = (void*)0x102;
	}
	a1 = 0;
	iVar2 = sub_6FAD4D20(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8, pvVar4,
	    (uint16_t*)&a1);
	if (iVar2 == 0)
	{
		if ((short)a1 != 0)
		{
			byte_6FBB5E04 = (short)a1;
			dword_6FBB5E08 = GetTickCount();
		}
	}
	else
	{
		uVar5 = 6;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar5);
		bVar1 = sub_6FAAB290();
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar5 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar5);
		}
		iVar2 = sub_6FAAB320();
		if (iVar2 != 0)
		{
			uVar5 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar5);
		}
		iVar2 = sub_6FAAB2E0();
		if (iVar2 != 0)
		{
			uVar5 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar5);
		}
		sub_6FB24790();
		dword_6FBB5DF8 = 0;
	}
LAB_6fafe23a:
	*(uint32_t*)(pData + 0x18) = 1;
	*(uint32_t*)(pData + 0x1c) = 0;
	SMsgBreakHandlerChain((SMSGHANDLER_PARAMS*)pData);
}

//D2Client.0x6FAFE250
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAFE250(int a1)
{
	int pData;
	bool bVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	int iVar4;
	uint32_t uVar5;

	iVar2 = sub_6FAABF20();
	pData = a1;
	if (iVar2 != 0)
	{
		*(uint32_t*)(a1 + 0x18) = 0;
		return;
	}
	iVar2 = (int)*(short*)(a1 + 10) >> 0x1f;
	iVar4 = (int)*(short*)(a1 + 10) / 0x78 + iVar2;
	if (iVar4 != iVar2)
	{
		a1 = 0;
		iVar2 = sub_6FAD4D20(*(int*)(gpuint8_t_6FB7CC94 + dword_6FBB5DF0 * 10), dword_6FB7CCE8,
		    (void*)((iVar4 - iVar2 < 0) + 0x103), (uint16_t*)&a1);
		if (iVar2 == 0)
		{
			if ((short)a1 != 0)
			{
				byte_6FBB5E04 = (short)a1;
				dword_6FBB5E08 = GetTickCount();
			}
		}
		else
		{
			uVar5 = 6;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CCF0), uVar5);
			bVar1 = sub_6FAAB290();
			if (D2C_ZEXT(bVar1) != 0)
			{
				uVar5 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD50), uVar5);
			}
			iVar2 = sub_6FAAB320();
			if (iVar2 != 0)
			{
				uVar5 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD44), uVar5);
			}
			iVar2 = sub_6FAAB2E0();
			if (iVar2 != 0)
			{
				uVar5 = 1;
				pHVar3 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB7CD38), uVar5);
			}
			sub_6FB24790();
			dword_6FBB5DF8 = 0;
		}
	}
	*(uint32_t*)(pData + 0x18) = 1;
	*(uint32_t*)(pData + 0x1c) = 0;
	SMsgBreakHandlerChain((SMSGHANDLER_PARAMS*)pData);
}

//D2Client.0x6FAFE370
void __cdecl sub_6FAFE370()
{
	bool bVar1;
	D2C_Language DVar2;
	int iVar3;
	uint32_t* puVar4;
	char* pcVar5;
	char acStack_104[260];

	gpCellFile_6FBB5E2C = sub_6FB20100("Panel\\btn");
	DVar2 = STRTABLE_GetLanguage();
	bVar1 = false;
	iVar3 = FOG_IsExpansion();
	if (iVar3 != 0)
	{
		iVar3 = sub_6FAAC080();
		if (iVar3 != 0)
		{
			bVar1 = true;
		}
	}
	if (((int)DVar2 < 6) || (9 < (int)DVar2))
	{
		pcVar5 = "Panel\\InvChar6";
		if (!bVar1)
		{
			pcVar5 = "Panel\\InvChar";
		}
		gpCellFile_6FBB5E24 = sub_6FB20100(pcVar5);
	}
	else
	{
		if (bVar1)
		{
			pcVar5 = "%s\\UI\\InvChar6";
		}
		else
		{
			pcVar5 = "%s\\UI\\InvChar";
		}
		sprintf(acStack_104, pcVar5, "DATA\\LOCAL");
		gpCellFile_6FBB5E24 = CLIENT_LoadCellFile(acStack_104, 0);
	}
	gpCellFile_6FBB5E20 = sub_6FB20100("Panel\\Arrow");
	gpCellFile_6FBB5E58 = sub_6FB20100("Panel\\Invwarn");
	gpCellFile_6FBB5E28 = sub_6FB20100("Panel\\DuroIcon");
	gpCellFile_6FBB5E34 = sub_6FB20100("Panel\\GemSocket");
	gpCellFile_6FBB5E1C = sub_6FB20100("Panel\\ctrlpnl_popbelt");
	gpCellFile_6FBB5E30 = sub_6FB20100("Panel\\Hlthmana");
	gpCellFile_6FBB5E8C = sub_6FB20100("Panel\\overlap");
	gpCellFile_6FBB5E18 = sub_6FB20100("Panel\\menubutton");
	gpCellFile_6FBB5E4C = sub_6FB20100("Panel\\menupanel");
	gpCellFile_6FBB5E50 = sub_6FB20100("Panel\\skillpoints");
	gpCellFile_6FBB5E48 = sub_6FB20100("Panel\\runbutton");
	gpCellFile_6FBB5E40 = sub_6FB20100("Panel\\hostilepic");
	puVar4 = &dword_6FBB5E5C;
	for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
}

//D2Client.0x6FAFE4D0
void __cdecl sub_6FAFE4D0()
{
	int iVar1;
	uint32_t* puVar2;

	if (gpCellFile_6FBB5E2C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E2C);
		gpCellFile_6FBB5E2C = nullptr;
	}
	if (gpCellFile_6FBB5E24 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E24);
		gpCellFile_6FBB5E24 = nullptr;
	}
	if (gpCellFile_6FBB5E20 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E20);
		gpCellFile_6FBB5E20 = nullptr;
	}
	if (gpCellFile_6FBB5E58 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E58);
		gpCellFile_6FBB5E58 = nullptr;
	}
	if (gpCellFile_6FBB5E28 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E28);
		gpCellFile_6FBB5E28 = nullptr;
	}
	if (gpCellFile_6FBB5E34 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E34);
		gpCellFile_6FBB5E34 = nullptr;
	}
	if (gpCellFile_6FBB5E1C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E1C);
		gpCellFile_6FBB5E1C = nullptr;
	}
	if (gpCellFile_6FBB5E54 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E54);
		gpCellFile_6FBB5E54 = nullptr;
	}
	if (gpCellFile_6FBB5E3C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E3C);
		gpCellFile_6FBB5E3C = nullptr;
	}
	if (gpCellFile_6FBB5E44 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E44);
		gpCellFile_6FBB5E44 = nullptr;
	}
	if (gpCellFile_6FBB5E30 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E30);
		gpCellFile_6FBB5E30 = nullptr;
	}
	if (gpCellFile_6FBB5E8C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E8C);
		gpCellFile_6FBB5E8C = nullptr;
	}
	if (gpCellFile_6FBB5E18 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E18);
		gpCellFile_6FBB5E18 = nullptr;
	}
	if (gpCellFile_6FBB5E4C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E4C);
		gpCellFile_6FBB5E4C = nullptr;
	}
	if (gpCellFile_6FBB5E50 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E50);
		gpCellFile_6FBB5E50 = nullptr;
	}
	if (gpCellFile_6FBB5E48 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E48);
		gpCellFile_6FBB5E48 = nullptr;
	}
	if (gpCellFile_6FBB5E40 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB5E40);
		gpCellFile_6FBB5E40 = nullptr;
	}
	puVar2 = &dword_6FBB5E5C;
	for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
}

//D2Client.0x6FAFE650
void __cdecl sub_6FAFE650()
{
	int iVar1;
	uint32_t uVar2;
	D2GfxDataStrc* pDVar3;
	int iVar4;
	D2GfxDataStrc local_48;

	uVar2 = 0;
	pDVar3 = &local_48;
	for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		pDVar3->pCurrentCell = nullptr;
		pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
	}
	iVar4 = 0;
	iVar1 = sub_6FAB12F0();
	if (iVar1 != 0)
	{
		iVar1 = sub_6FB23230(0x19);
		if ((((iVar1 != 0) || (iVar1 = sub_6FB23230(0xc), iVar1 != 0)) ||
		        (iVar1 = sub_6FB23230(0x18), iVar1 != 0)) ||
		    ((iVar1 = sub_6FB23230(1), iVar1 != 0 || (iVar1 = sub_6FB23230(4), iVar1 != 0))))
		{
			uVar2 = 1;
		}
		iVar1 = sub_6FB23230(0x17);
		if ((iVar1 != 0) && (iVar1 = sub_6FB1F680(), iVar1 == 0))
		{
			return;
		}
		if (uVar2 == 0)
		{
			local_48.pCellFile = gpCellFile_6FBB5E40;
			local_48.nFrame = uVar2;
			local_48.nDirection = uVar2;
			iVar1 = sub_6FB23230(10);
			if (iVar1 != 0)
			{
				iVar4 = 0x46;
			}
			TEXTURE_CelDraw(&local_48, gnScreenWidth + -0x3a, iVar4 + 0x2d, 0xffffffff, DRAWMODE_TRANS50,
			    nullptr);
		}
		return;
	}
}

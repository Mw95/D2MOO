#include "Unit/UnitSnd.h"

#include "Game/Game.h"
#include "Sound/SoundChan.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "UI/QuestLog.h"
#include "UI/Text.h"
#include "Unit/CUnit.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"
#include "Unit/Monster.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB960F8
uint32_t unk_6FB960F8[11] = { 0xB3E, 0xB43, 0xB89, 0xB8D, 0xB8B, 0xB76, 0xB78, 0xB8F, 0xB79, 0xB91, 0xAD0 };
//D2Client.0x6FB96124
uint32_t unk_6FB96124[11] = { 0xB56, 0xB5B, 0xBD7, 0xBDB, 0xBD9, 0xBC4, 0xBC6, 0xBDD, 0xBC7, 0xBDF, 0xB00 };
//D2Client.0x6FB96150
uint32_t unk_6FB96150[11] = { 0xB4E, 0xB53, 0xC25, 0xC29, 0xC27, 0xC12, 0xC14, 0xC2B, 0xC15, 0xC2D, 0xAA0 };
//D2Client.0x6FB9617C
uint32_t unk_6FB9617C[11] = { 0xB46, 0xB4B, 0xC73, 0xC77, 0xC75, 0xC60, 0xC62, 0xC79, 0xC63, 0xC7B, 0xAD0 };
//D2Client.0x6FB961A8
uint32_t unk_6FB961A8[11] = { 0xB5E, 0xB63, 0xCC1, 0xCC5, 0xCC3, 0xCAE, 0xCB0, 0xCC7, 0xCB1, 0xCC9, 0xAA0 };
//D2Client.0x6FB961D4
uint32_t unk_6FB961D4[11] = { 0xB66, 0xB6B, 0xD0F, 0xD13, 0xD11, 0xCFC, 0xCFE, 0xD15, 0xCFF, 0xD17, 0xAA0 };
//D2Client.0x6FB96200
uint32_t unk_6FB96200[11] = { 0xB6E, 0xB73, 0xD5D, 0xD61, 0xD5F, 0xD4A, 0xD4C, 0xD63, 0xD4D, 0xD65, 0xAA0 };
//D2Client.0x6FB96248
uint32_t unk_6FB96248[1] = { 0x11 };

//D2Client.0x6FB940D0
uint8_t byte_6FB940D0[4];
//D2Client.0x6FB940D4
uint8_t byte_6FB940D4[108] = {0, 0, 0, 0, 0xFB, 0, 0, 0, 6, 0, 0, 0, 6, 1, 0, 0, 6, 0, 0, 0, 0xC, 1, 0, 0, 6, 0, 0, 0, 0x12, 1, 0, 0, 8, 0, 0, 0, 0x18, 1, 0, 0, 8, 0, 0, 0, 0x1E, 1, 0, 0, 6, 0, 0, 0, 0x24, 1, 0, 0, 8, 0, 0, 0, 0xC, 1, 0, 0, 6, 0, 0, 0, 0x2A, 1, 0, 0, 6};
//D2Client.0x6FB94530
uint8_t byte_6FB94530[48] = {0, 0, 0, 0, 0x9D, 1, 0, 0, 0x9E, 1, 0, 0, 0x9F, 1, 0, 0, 0xA0, 1, 0, 0, 0xA1, 1};
//D2Client.0x6FB95520
uint8_t byte_6FB95520;
//D2Client.0x6FB957F0
uint8_t byte_6FB957F0[2312] = {0, 0, 0, 0, 0xC0, 0x45, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0xE0, 0x46, 0xB9, 0x6F, 0xE0, 0x46, 0xB9, 0x6F, 0xA0, 0x41, 0xB9, 0x6F, 0xA0, 0x53, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0x42, 0xB9, 0x6F, 0x90, 0x4B, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0x90, 0x45, 0xB9, 0x6F, 0xC0, 0x48, 0xB9, 0x6F, 0xC0, 0x48, 0xB9, 0x6F, 0xC0, 0x48, 0xB9, 0x6F, 0xC0, 0x4B, 0xB9, 0x6F, 0x60, 0x48, 0xB9, 0x6F, 0x80, 0x4C, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xE0, 0x43, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x41, 0xB9, 0x6F, 0xC0, 0x48, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0x70, 0x47, 0xB9, 0x6F, 0x70, 0x47, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F, 0x60, 0x45, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0x60, 0x4E, 0xB9, 0x6F, 0x60, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xE0, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x45, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x43, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0, 0, 0, 0, 0xB0, 0x49, 0xB9, 0x6F, 0xB0, 0x49, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x4F, 0xB9, 0x6F, 0xB0, 0x49, 0xB9, 0x6F, 0xB0, 0x49, 0xB9, 0x6F, 0x90, 0x48, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x30, 0x4B, 0xB9, 0x6F, 0x70, 0x41, 0xB9, 0x6F, 0x70, 0x41, 0xB9, 0x6F, 0xF0, 0x54, 0xB9, 0x6F, 0xF0, 0x54, 0xB9, 0x6F, 0xA0, 0x4D, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x30, 0x42, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x60, 0x42, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x90, 0x42, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x10, 0x50, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x4F, 0xB9, 0x6F, 0x80, 0x4F, 0xB9, 0x6F, 0, 0x51, 0xB9, 0x6F, 0x70, 0x50, 0xB9, 0x6F, 0x60, 0x51, 0xB9, 0x6F, 0x30, 0x51, 0xB9, 0x6F, 0x50, 0x49, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x90, 0x54, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0x55, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x40, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0x4D, 0xB9, 0x6F, 0x90, 0x48, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0x10, 0x53, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0x10, 0x53, 0xB9, 0x6F, 0xA0, 0x4A, 0xB9, 0x6F, 0xA0, 0x4A, 0xB9, 0x6F, 0xA0, 0x4A, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x10, 0x4D, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xE0, 0x52, 0xB9, 0x6F, 0xE0, 0x52, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0x70, 0x47, 0xB9, 0x6F, 0x10, 0x44, 0xB9, 0x6F, 0x10, 0x44, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x10, 0x47, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0x90, 0x51, 0xB9, 0x6F, 0xC0, 0x51, 0xB9, 0x6F, 0xF0, 0x51, 0xB9, 0x6F, 0x20, 0x52, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0x70, 0x53, 0xB9, 0x6F, 0xA0, 0x53, 0xB9, 0x6F, 0xA0, 0x50, 0xB9, 0x6F, 0xA0, 0x50, 0xB9, 0x6F, 0x60, 0x4B, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x4E, 0xB9, 0x6F, 0x50, 0x52, 0xB9, 0x6F, 0x80, 0x52, 0xB9, 0x6F, 0x90, 0x51, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xB0, 0x49, 0xB9, 0x6F, 0xC0, 0x42, 0xB9, 0x6F, 0xC0, 0x42, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x44, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x51, 0xB9, 0x6F, 0x40, 0x47, 0xB9, 0x6F, 0x40, 0x47, 0xB9, 0x6F, 0x70, 0x50, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0, 0, 0, 0, 0x80, 0x49, 0xB9, 0x6F, 0x80, 0x49, 0xB9, 0x6F, 0x80, 0x49, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0x80, 0x4F, 0xB9, 0x6F, 0xD0, 0x50, 0xB9, 0x6F, 0x80, 0x49, 0xB9, 0x6F, 0x80, 0x49, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xD0, 0x44, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0x30, 0x4E, 0xB9, 0x6F, 0, 0x45, 0xB9, 0x6F, 0x30, 0x4E, 0xB9, 0x6F, 0xF0, 0x42, 0xB9, 0x6F, 0xF0, 0x42, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xD0, 0x47, 0xB9, 0x6F, 0, 0, 0, 0, 0xF0, 0x4B, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0x50, 0xB9, 0x6F, 0xB0, 0x4F, 0xB9, 0x6F, 0x60, 0x4B, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0x4C, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xF0, 0x42, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0x20, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0xE0, 0x49, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x30, 0x48, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0x50, 0x4F, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0x70, 0x53, 0xB9, 0x6F, 0x70, 0x53, 0xB9, 0x6F, 0x70, 0x53, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0x40, 0x41, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xF0, 0x4E, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x4D, 0xB9, 0x6F, 0xF0, 0x48, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x47, 0xB9, 0x6F, 0x10, 0x47, 0xB9, 0x6F, 0x10, 0x47, 0xB9, 0x6F, 0xA0, 0x53, 0xB9, 0x6F, 0xB0, 0x4C, 0xB9, 0x6F, 0xB0, 0x4C, 0xB9, 0x6F, 0x90, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0x40, 0x4A, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0x70, 0x4A, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xA0, 0x50, 0xB9, 0x6F, 0x70, 0x4D, 0xB9, 0x6F, 0, 0, 0, 0, 0xB0, 0x52, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x70, 0x50, 0xB9, 0x6F, 0x40, 0x50, 0xB9, 0x6F, 0, 0, 0, 0, 0x50, 0x46, 0xB9, 0x6F, 0xE0, 0x4C, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x52, 0xB9, 0x6F, 0xB0, 0x52, 0xB9, 0x6F, 0, 0, 0, 0, 0xB0, 0x52, 0xB9, 0x6F, 0xB0, 0x52, 0xB9, 0x6F, 0, 0, 0, 0, 0xA0, 0x50, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0, 0x48, 0xB9, 0x6F, 0, 0x48, 0xB9, 0x6F, 0, 0x48, 0xB9, 0x6F, 0, 0x48, 0xB9, 0x6F, 0, 0x48, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xD0, 0x4A, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x54, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0, 0x4E, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xF0, 0x45, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x57, 0xB9, 0x6F, 0, 0, 0, 0, 0x60, 0x57, 0xB9, 0x6F, 0x60, 0x57, 0xB9, 0x6F, 0x30, 0x57, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x10, 0x56, 0xB9, 0x6F, 0x10, 0x56, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xB0, 0x46, 0xB9, 0x6F, 0x30, 0x57, 0xB9, 0x6F, 0xB0, 0x46, 0xB9, 0x6F, 0xB0, 0x46, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x56, 0xB9, 0x6F, 0x50, 0x55, 0xB9, 0x6F, 0, 0, 0, 0, 0x90, 0x57, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x60, 0x54, 0xB9, 0x6F, 0x80, 0x46, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x43, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x43, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0x30, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0x80, 0x55, 0xB9, 0x6F, 0x80, 0x55, 0xB9, 0x6F, 0x80, 0x55, 0xB9, 0x6F, 0xA0, 0x47, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x4E, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x57, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x46, 0xB9, 0x6F, 0x50, 0x46, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0x56, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x54, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0x4B, 0xB9, 0x6F, 0, 0x4B, 0xB9, 0x6F, 0x50, 0x4C, 0xB9, 0x6F, 0x20, 0x55, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0xC0, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0xC0, 0x45, 0xB9, 0x6F, 0x50, 0x4C, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0xC0, 0x54, 0xB9, 0x6F, 0xD0, 0x56, 0xB9, 0x6F, 0x90, 0x4E, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x90, 0x4E, 0xB9, 0x6F, 0, 0x57, 0xB9, 0x6F, 0, 0, 0, 0, 0xB0, 0x55, 0xB9, 0x6F, 0xF0, 0x54, 0xB9, 0x6F, 0xF0, 0x54, 0xB9, 0x6F, 0x70, 0x41, 0xB9, 0x6F, 0x70, 0x41, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0x70, 0x44, 0xB9, 0x6F, 0xD0, 0x53, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0x57, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x53, 0xB9, 0x6F, 0xA0, 0x4A, 0xB9, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xE0, 0x55, 0xB9, 0x6F, 0xA0, 0x56, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F, 0, 0x54, 0xB9, 0x6F};
//D2Client.0x6FB9622C
uint8_t* gpuint8_t_6FB9622C[7] = {(uint8_t*)&unk_6FB960F8, (uint8_t*)&unk_6FB961A8, (uint8_t*)&unk_6FB96150, (uint8_t*)&unk_6FB9617C, (uint8_t*)&unk_6FB96124, (uint8_t*)&unk_6FB96200, (uint8_t*)&unk_6FB961D4};
//D2Client.0x6FB964E8
uint8_t* ptr_6FB964E8 = (uint8_t*)&unk_6FB96248;
//D2Client.0x6FB96537
uint8_t tbl_6FB96537[53] = {0x3D, 0x20, 0x45, 0x48, 0x49, 0x54, 0x43, 0x4C, 0x41, 0x53, 0x53, 0x5F, 0x4E, 0x4F, 0x4E, 0x45, 0x20, 0x26, 0x26, 0x20, 0x65, 0x48, 0x69, 0x74, 0x43, 0x6C, 0x61, 0x73, 0x73, 0x42, 0x61, 0x73, 0x65, 0x20, 0x3C, 0x20, 0x4E, 0x55, 0x4D, 0x5F, 0x45, 0x48, 0x49, 0x54, 0x43, 0x4C, 0x41, 0x53, 0x53, 0x45, 0x53};
//D2Client.0x6FBBD250
uint32_t dword_6FBBD250;
//D2Client.0x6FBBD254
uint8_t byte_6FBBD254;
//D2Client.0x6FBBD258
uint32_t dword_6FBBD258;
//D2Client.0x6FBBD264
int32_t dword_6FBBD264;

//D2Client.0x6FB4F4D0
uint32_t __fastcall sub_6FB4F4D0(int ptUnit, uint32_t a2)
{
	D2_ASSERT(ptUnit);
	D2_ASSERT(0xd >= (a2 & 0xf));
	return *(uint32_t*)(byte_6FB940D0 + (a2 & 0xf) * 8);
}

//D2Client.0x6FB4F530
uint32_t __fastcall sub_6FB4F530(int ptUnit, uint32_t a2)
{
	uint32_t uVar1;

	D2_ASSERT(ptUnit);
	D2_ASSERT(0xd >= (a2 & 0xf));
	uVar1 = (uint32_t) * (short*)(ptUnit + 0x4c);
	if (uVar1 == 0)
	{
		uVar1 = 1;
	}
	return (*(int*)(byte_6FB940D4 + (a2 & 0xf) * 8) * 0x100 + 0x80U) / uVar1;
}

//D2Client.0x6FB4F5A0
void __fastcall sub_6FB4F5A0(D2UnitStrc* ptUnit, uint32_t a2, int* a3, int* a4, int* a5)
{
	int iVar1;
	int* piVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	D2_ASSERT(ptUnit != nullptr);
	local_c = ptUnit->dwUnitType;
	local_4 = ptUnit->dwClassId;
	iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
	uVar4 = local_c;
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
		uVar4 = local_c;
	}
	piVar2 = a4;
	*a4 = 0;
	*a5 = 0;
	if (uVar4 == 1)
	{
		a4 = (int*)ptUnit->dwUnitType;
		local_c = ptUnit->dwClassId;
		local_4 = UNITS_GetAnimOrSeqMode(ptUnit);
		if (a4 == nullptr)
		{
			D2COMMON_11013_ConvertMode(ptUnit, (int*)&a4, (int*)&local_c, &local_4,
			    __FILE__, __LINE__);
		}
		if ((((-1 < (int)local_c) &&
		         (iVar1 = *(int*)((uint8_t*)&sgptDataTables), (int)local_c < *(int*)(iVar1 + 0xa80))) &&
		        (iVar3 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + local_c * 0x1a8), -1 < iVar3)) &&
		    (((iVar3 < *(int*)(iVar1 + 0xa98) &&
		          (iVar1 = *(int*)(iVar1 + 0xa90) + iVar3 * 0x134, iVar1 != 0)) &&
		        (((uint32_t) * (uint8_t*)(iVar1 + 5) & *(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x14)) != 0))))
		{
			return;
		}
	}
	switch (a2 & 0xf)
	{
	case 1:
		*piVar2 = 0x141;
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		*piVar2 = 0x155;
		break;
	case 6:
	case 7:
		*piVar2 = 0x14f;
		break;
	case 8:
	case 9:
		*piVar2 = 0x149;
		break;
	case 10:
	case 0xb:
		*piVar2 = 0x15b;
		break;
	case 0xc:
		*piVar2 = 0x145;
	}
	switch (a2 & 0xf0)
	{
	case 0x10:
		if (*piVar2 != 0)
		{
			*a5 = 0x17b;
			return;
		}
		break;
	case 0x20:
		*a5 = (-(uint32_t)(*piVar2 != 0) & 3) + 0x161;
		return;
	case 0x30:
		if (*piVar2 == 0)
		{
			*a5 = 0x167;
			return;
		}
		if (((uVar4 != 0) && (uVar4 != 1)) || (a3 != nullptr))
		{
			*a5 = 0x16a;
			return;
		}
		break;
	case 0x40:
		*a5 = (uint32_t)(*piVar2 != 0) * 4 + 0x170;
		return;
	case 0x50:
		if (*piVar2 == 0)
		{
			*a5 = 0x178;
			return;
		}
		if (((uVar4 != 0) && (uVar4 != 1)) || (a3 != nullptr))
		{
			*a5 = 0x178;
			return;
		}
		break;
	case 0x60:
		*a5 = 0x17e;
		return;
	case 0x70:
		*a5 = 0x18b;
		return;
	case 0x80:
		*a5 = 0x956;
		return;
	case 0xb0:
		*a5 = 0x187;
	}
}

//D2Client.0x6FB4F930
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FB4F930(int ptUnit)
{
	int in_EDX;

	D2_ASSERT(ptUnit);
	D2SOUND_10058(ptUnit + 0x78, in_EDX);
}

//D2Client.0x6FB4F960
// TODO: decompilation needs review (in_reg)
void __fastcall sub_6FB4F960(int ptUnit)
{
	int in_EDX;

	D2_ASSERT(ptUnit);
	D2SOUND_10059(ptUnit + 0x78, in_EDX);
}

//D2Client.0x6FB4F990
int __fastcall sub_6FB4F990(int ptUnit, int a2)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	uint32_t uVar4;
	int iVar5;

	D2_ASSERT(ptUnit);
	iVar3 = sub_6FB52D00();
	if (iVar3 != 0)
	{
		iVar3 = sub_6FB53C30(a2);
		uVar4 = sub_6FB53C60(iVar3);
		for (piVar1 = *(int**)(ptUnit + 0x78); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
		{
			iVar2 = *piVar1;
			iVar5 = sub_6FB56090(iVar2);
			if ((iVar3 <= iVar5) && (iVar5 < (int)(iVar3 + (uVar4 & 0xff))))
			{
				return iVar2;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB4FA10
uint32_t __fastcall sub_6FB4FA10(int ptUnit)
{
	D2_ASSERT(ptUnit);
	if (*(uint32_t**)(ptUnit + 0x78) != nullptr)
	{
		return **(uint32_t**)(ptUnit + 0x78);
	}
	return 0;
}

//D2Client.0x6FB4FA40
void __fastcall sub_6FB4FA40(int ptUnit, int a2)
{
	int* piVar1;
	int iVar2;

	D2_ASSERT(ptUnit);
	piVar1 = *(int**)(ptUnit + 0x78);
	while (piVar1 != nullptr)
	{
		iVar2 = *piVar1;
		piVar1 = (int*)piVar1[1];
		sub_6FB555C0(iVar2, ptUnit, a2);
	}
}

//D2Client.0x6FB4FA90
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB4FA90(D2UnitStrc* pUnit)
{
	uint16_t uVar1;
	uint8_t uVar2;
	uint32_t extraout_var;
	int iVar3;
	int32_t DVar4;
	D2ActiveRoomStrc* pDVar5;
	D2DrlgTileDataStrc* pDVar6;
	int* piVar7;
	int iVar8;
	uint32_t uVar9;
	int local_38;
	int iStack_34;
	uint32_t uStack_30;
	int local_2c;
	D2ActiveRoomStrc** ppDStack_28;
	uint32_t uStack_24;
	D2DrlgCoordsStrc DStack_20;

	uVar2 = sub_6FB53CF0();
	iVar3 = sub_6FB53D30(D2C_ZEXT(uVar2));
	local_2c = 1;
	if (((iVar3 != 0) && (iVar3 = *(int*)(iVar3 + 0x1c), 0 < iVar3)) && (iVar3 < 7))
	{
		local_2c = iVar3;
	}
	uVar9 = pUnit->dwUnitType;
	if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
	{
		local_38 = pUnit->pDynamicPath->dwClientCoordY;
	}
	else if (pUnit->pDynamicPath == nullptr)
	{
		local_38 = 0;
	}
	else
	{
		local_38 = PATH_GetXPosition(pUnit->pDynamicPath);
	}
	uVar9 = pUnit->dwUnitType;
	if ((uVar9 == 2) || ((3 < (int)uVar9 && ((int)uVar9 < 6))))
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
	pDVar5 = UNITS_GetRoom(pUnit);
	if (pDVar5 == nullptr)
	{
		return 0;
	}
	DUNGEON_GetRoomCoordinates(pDVar5, &DStack_20);
	iVar3 = local_38 - DStack_20.nSubtileX;
	iVar8 = (int)DVar4 - DStack_20.nSubtileY;
	pDVar6 = DUNGEON_GetFloorTilesFromRoom(pDVar5, (int*)&uStack_30);
	uVar9 = 0;
	if (uStack_30 != 0)
	{
		piVar7 = &pDVar6->nPosY;
		do
		{
			if ((piVar7[-1] == iVar3 / 5) && (*piVar7 == iVar8 / 5))
			{
			LAB_6fb4fc5f:
				if ((D2TileLibraryEntryStrc*)piVar7[3] == nullptr)
				{
					return local_2c;
				}
				uVar1 = ((D2TileLibraryEntryStrc*)piVar7[3])->nFlags;
				if ((uVar1 & 0x20) != 0)
				{
					return 1;
				}
				if ((uVar1 & 8) != 0)
				{
					return 2;
				}
				if ((uVar1 & 0x10) == 0)
				{
					if ((uVar1 & 0x40) != 0)
					{
						return 4;
					}
					if (-1 < (char)uVar1)
					{
						if ((uVar1 & 0x400) == 0)
						{
							return local_2c;
						}
						return 5;
					}
					return 6;
				}
				return 3;
			}
			uVar9 = uVar9 + 1;
			piVar7 = piVar7 + 0xc;
		} while (uVar9 < uStack_30);
	}
	DUNGEON_GetAdjacentRoomsListFromRoom(pDVar5, &ppDStack_28, (int*)&uStack_30);
	iStack_34 = 0;
	if ((int)uStack_30 < 1)
	{
		return local_2c;
	}
	do
	{
		pDVar5 = ppDStack_28[iStack_34];
		DUNGEON_GetRoomCoordinates(pDVar5, &DStack_20);
		iVar3 = local_38 - DStack_20.nSubtileX;
		iVar8 = (int)DVar4 - DStack_20.nSubtileY;
		pDVar6 = DUNGEON_GetFloorTilesFromRoom(pDVar5, (int*)&uStack_24);
		uVar9 = 0;
		if (uStack_24 != 0)
		{
			piVar7 = &pDVar6->nPosY;
			do
			{
				if ((piVar7[-1] == iVar3 / 5) && (*piVar7 == iVar8 / 5))
					goto LAB_6fb4fc5f;
				uVar9 = uVar9 + 1;
				piVar7 = piVar7 + 0xc;
			} while (uVar9 < uStack_24);
		}
		iStack_34 = iStack_34 + 1;
		if ((int)uStack_30 <= iStack_34)
		{
			return local_2c;
		}
	} while (true);
}

//D2Client.0x6FB4FCE0
int __fastcall sub_6FB4FCE0(D2UnitStrc* pUnit, int a2)
{
	uint32_t uVar1;
	int iVar2;
	uint32_t local_c;
	uint32_t uStack_8;
	int local_4;

	local_c = 6;
	if (pUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
	}
	uStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
	if ((local_c == 0) &&
	    (D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, (int*)&uStack_8,
	         __FILE__, __LINE__),
	        local_c == 0))
	{
		local_c = 6;
		if (pUnit == nullptr)
		{
			uStack_8 = 0xffffffff;
		}
		else
		{
			local_c = pUnit->dwUnitType;
			uStack_8 = pUnit->dwClassId;
		}
		local_4 = UNITS_GetAnimOrSeqMode(pUnit);
		if (local_c == 0)
		{
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, (int*)&uStack_8, &local_4,
			    __FILE__, __LINE__);
		}
		D2_ASSERT(6 >= uStack_8);
		iVar2 = *(int*)(gpuint8_t_6FB9622C[uStack_8] + 0x28);
	}
	else
	{
		if (local_c != 1)
		{
			return 0;
		}
		iVar2 = sub_6FB4FE50(pUnit);
		if (iVar2 == 0)
		{
			return 0;
		}
		iVar2 = *(int*)(iVar2 + 0x54);
	}
	if (iVar2 == 0)
	{
		return 0;
	}
	uVar1 = sub_6FB4FA90(pUnit);
	switch (uVar1)
	{
	case 2:
		iVar2 = iVar2 + 4;
		break;
	case 3:
		iVar2 = iVar2 + 8;
		break;
	case 4:
		iVar2 = iVar2 + 0xc;
		break;
	case 5:
		iVar2 = iVar2 + 0x10;
		break;
	case 6:
		iVar2 = iVar2 + 0x14;
	}
	if (a2 != 0)
	{
		iVar2 = iVar2 + 0x18;
	}
	return iVar2;
}

//D2Client.0x6FB4FE50
// TODO: decompilation needs review (extraout)
int32_t __fastcall sub_6FB4FE50(D2UnitStrc* pUnit)
{
	int iVar1;
	int nMonsterId;
	bool bVar2;
	short sVar3;
	uint32_t extraout_var;
	D2SuperUniquesTxt* pDVar4;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t local_c;
	int local_8;
	int iStack_4;

	if (pUnit == nullptr)
	{
		DATATBLS_GetMonSoundsTxtRecordFromSoundId(0);
		return 0;
	}
	local_c = pUnit->dwUnitType;
	local_8 = pUnit->dwClassId;
	iStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_8, &iStack_4,
		    __FILE__, __LINE__);
	}
	nMonsterId = local_8;
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= local_8)
	{
		DATATBLS_GetMonSoundsTxtRecordFromSoundId(0);
		return 0;
	}
	if (pUnit->dwUnitType == 1)
	{
		bVar2 = sub_6FB40D40((int*)pUnit);
		if (D2C_ZEXT(bVar2) != 0)
		{
			sVar3 = sub_6FB449B0((int*)pUnit);
			pDVar4 = DATATBLS_GetSuperUniquesTxtRecord((int)sVar3);
			if ((pDVar4 != nullptr) && (0 < (int)pDVar4->dwMonSound))
			{
				DATATBLS_GetMonSoundsTxtRecordFromSoundId(pDVar4->dwMonSound);
				return 0;
			}
		}
		bVar2 = sub_6FB40D00((int*)pUnit);
		if (D2C_ZEXT(bVar2) == 0)
		{
			bVar2 = sub_6FB40D20((int*)pUnit);
			if (D2C_ZEXT(bVar2) == 0)
				goto LAB_6fb4ff66;
		}
		if (((nMonsterId < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= nMonsterId)) ||
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + nMonsterId * 0x1a8, iVar1 == 0))
		{
			DATATBLS_GetMonSoundsTxtRecordFromSoundId(0);
			return 0;
		}
		sVar3 = *(short*)(iVar1 + 0x16);
		if (0 < sVar3)
		{
			DATATBLS_GetMonSoundsTxtRecordFromSoundId((int)sVar3);
			return 0;
		}
	}
LAB_6fb4ff66:
	return (int32_t)(DATATBLS_GetMonSoundsTxtRecordFromMonsterId(nMonsterId));
}

//D2Client.0x6FB4FF80
uint32_t __fastcall sub_6FB4FF80(D2UnitStrc* pUnit)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;
	uint32_t uVar5;
	bool bVar6;
	float fVar7;
	float fVar8;
	uint32_t local_28;
	int iStack_24;
	uint32_t uStack_20;
	uint32_t uStack_1c;
	int iStack_18;
	uint32_t local_14;
	uint32_t uStack_10;
	int iStack_c;
	uint32_t uStack_8;
	uint32_t uStack_4;

	local_28 = 6;
	if (pUnit == nullptr)
	{
		local_14 = 0xffffffff;
	}
	else
	{
		local_28 = pUnit->dwUnitType;
		local_14 = pUnit->dwClassId;
	}
	uStack_10 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_28 == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_28, (int*)&local_14, (int*)&uStack_10,
		    __FILE__, __LINE__);
	}
	uStack_20 = 6;
	if (pUnit == nullptr)
	{
		uStack_10 = 0xffffffff;
	}
	else
	{
		uStack_20 = pUnit->dwUnitType;
		uStack_10 = pUnit->dwClassId;
	}
	iStack_24 = UNITS_GetAnimOrSeqMode(pUnit);
	if (uStack_20 == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_20, (int*)&uStack_10, &iStack_24,
		    __FILE__, __LINE__);
	}
	if (local_28 == 1)
	{
		uStack_20 = 6;
		if (pUnit == nullptr)
		{
			uStack_1c = 0xffffffff;
		}
		else
		{
			uStack_20 = pUnit->dwUnitType;
			uStack_1c = pUnit->dwClassId;
		}
		uStack_10 = UNITS_GetAnimOrSeqMode(pUnit);
		if (uStack_20 == 0)
		{
			D2COMMON_11013_ConvertMode(pUnit, (int*)&uStack_20, (int*)&uStack_1c, (int*)&uStack_10,
			    __FILE__, __LINE__);
		}
		if (((int)uStack_1c < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= (int)uStack_1c))
		{
			uStack_1c = 0xffffffff;
		}
		bVar6 = false;
		if ((iStack_24 == 2) || (iStack_24 == 0xf))
		{
			bVar6 = true;
		}
		if (uStack_1c == 0xf)
		{
			if (iStack_24 == 1)
				goto LAB_6fb500d9;
		}
		else if (uStack_1c == 0x6e)
		{
			bVar6 = iStack_24 == 8;
		}
		if (!bVar6)
		{
			return 0;
		}
	}
LAB_6fb500d9:
	iVar4 = (int)pUnit->wAnimSpeed;
	uStack_20 = pUnit->nSeqCurrentFramePrecise;
	uStack_1c = pUnit->dwFrameCountPrecise;
	if (iVar4 == 0)
	{
		return uStack_20;
	}
	uVar5 = 0;
	uVar3 = 2;
	iStack_18 = 0;
	local_14 = 100;
	if ((local_28 == 1) && (iVar1 = sub_6FB4FE50(pUnit), iVar1 != 0))
	{
		uVar3 = *(uint32_t*)(iVar1 + 0x5c);
		iStack_18 = *(int*)(iVar1 + 0x58);
		local_14 = *(uint32_t*)(iVar1 + 100);
		uVar5 = *(int*)(iVar1 + 0x60) << 8;
		if (uVar3 == 0)
		{
			return local_14;
		}
	}
	uStack_10 = sub_6FAABF80();
	uStack_8 = uStack_1c / (uVar3 * iVar4);
	uStack_4 = uStack_10 - pUnit->dwSfxStepTicks;
	if ((1 < uVar3) && (uStack_4 < (uStack_8 * 2) / 3))
	{
		return uStack_8 * 0x55555556;
	}
	uVar3 = uStack_1c / uVar3;
	uStack_1c = sub_6FB572D0(uStack_20, uVar5, uVar3);
	iStack_c = sub_6FB572D0(uStack_20 + iVar4, uVar5, uVar3);
	uVar3 = sub_6FB572D0(uStack_20 - iVar4, uVar5, uVar3);
	if (iStack_c <= (int)uStack_1c)
	{
		return uVar3;
	}
	if ((int)uVar3 <= (int)uStack_1c)
	{
		return uVar3;
	}
	iVar4 = 0;
	if (local_28 == 0)
	{
		bVar6 = iStack_24 == 3;
	}
	else
	{
		if (local_28 != 1)
			goto LAB_6fb501f1;
		bVar6 = iStack_24 == 0xf;
	}
	if (bVar6)
	{
		iVar4 = 1;
	}
LAB_6fb501f1:
	iVar1 = 0;
	fVar8 = 0.0;
	fVar7 = 0.0;
	iVar4 = sub_6FB4FCE0(pUnit, iVar4);
	uVar3 = sub_6FB55820(iVar4, pUnit, fVar7, fVar8, iVar1);
	if (uVar3 != 0)
	{
		uVar5 = 0xff;
		pDVar2 = CUNIT_GetPlayer();
		if (pUnit != pDVar2)
		{
			uVar5 = 200;
		}
		if (uStack_8 * 3 >> 1 < uStack_4)
		{
			uVar5 = (uVar5 * 0xa0) / 0xff;
		}
		uVar3 = sub_6FB55BC0(uVar3, uVar5);
	}
	iVar4 = iStack_18;
	if ((iStack_18 != 0) && (uVar3 = sub_6FB57150(100), uVar3 < local_14))
	{
		uVar3 = sub_6FB55820(iVar4, pUnit, 0.0, 0.0, 0);
	}
	pUnit->dwSfxStepTicks = uStack_10;
	return uVar3;
}

//D2Client.0x6FB50290
void __fastcall sub_6FB50290(D2UnitStrc* ptUnit)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	local_c = 6;
	if (ptUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = ptUnit->dwUnitType;
		local_4 = ptUnit->dwClassId;
	}
	iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
	}
	if ((local_c == 1) && (iVar3 = sub_6FB4FE50(ptUnit), iVar3 != 0))
	{
		D2_ASSERT(ptUnit != nullptr);
		piVar1 = (int*)ptUnit->pUnitSfxData;
		while (piVar1 != nullptr)
		{
			iVar2 = *piVar1;
			piVar1 = (int*)piVar1[1];
			iVar4 = sub_6FB56090(iVar2);
			iVar4 = sub_6FB53C30(iVar4);
			if ((((iVar4 == *(int*)(iVar3 + 0x44)) || (iVar4 == *(int*)(iVar3 + 0x48))) ||
			        (iVar4 == *(int*)(iVar3 + 0x4c))) ||
			    (iVar4 == *(int*)(iVar3 + 0x50)))
			{
				sub_6FB555C0(iVar2, (int)ptUnit, 1);
			}
		}
	}
}

//D2Client.0x6FB50370
// TODO: decompilation needs review (extraout)
int32_t __fastcall sub_6FB50370(D2UnitStrc* ptUnit)
{
	int* piVar1;
	uint8_t* puVar2;
	bool bVar3;
	uint8_t uVar4;
	D2UnitStrc* pUnit2;
	int iVar5;
	uint32_t uVar6;
	uint32_t* puVar7;
	int iVar8;
	int iVar9;
	uint32_t extraout_var;
	uint8_t* puVar10;
	D2ActiveRoomStrc* pRoom;
	uint32_t uVar11;
	uint32_t uStack_18;
	uint32_t uStack_14;
	uint32_t local_10;
	uint32_t uStack_c;
	int local_8;
	uint32_t uStack_4;

	local_10 = 6;
	if (ptUnit == nullptr)
	{
		local_8 = -1;
	}
	else
	{
		local_10 = ptUnit->dwUnitType;
		local_8 = ptUnit->dwClassId;
	}
	uStack_18 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (local_10 == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_10, &local_8, (int*)&uStack_18,
		    __FILE__, __LINE__);
	}
	uVar11 = uStack_18;
	uStack_14 = 6;
	if (ptUnit == nullptr)
	{
		uStack_4 = 0xffffffff;
	}
	else
	{
		uStack_14 = ptUnit->dwUnitType;
		uStack_4 = ptUnit->dwClassId;
	}
	uStack_c = UNITS_GetAnimOrSeqMode(ptUnit);
	if (uStack_14 == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&uStack_14, (int*)&uStack_4, (int*)&uStack_c,
		    __FILE__, __LINE__);
	}
	if (uStack_14 != 2)
	{
		puVar10 = sub_6FB508B0(ptUnit);
		if (puVar10 != (uint8_t*)0x1)
		{
			return 0;
		}
		iVar5 = sub_6FB522F0((int*)ptUnit);
		if ((iVar5 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar5))
		{
			iVar5 = -1;
		}
		bVar3 = false;
		if (((uVar11 == 1) || (uVar11 == 2)) || (uVar11 == 0xf))
		{
			bVar3 = true;
		}
		if (iVar5 == 0x6e)
		{
			if (uVar11 == 8)
				goto LAB_6fb50772;
		}
		else if ((iVar5 == 0x88) && (uVar11 == 0xb))
			goto LAB_6fb50772;
		if (!bVar3)
		{
			return 0;
		}
	LAB_6fb50772:
		iVar5 = sub_6FB4FE50(ptUnit);
		if (iVar5 != 0)
		{
			iVar9 = sub_6FB4FE50(ptUnit);
			if (iVar9 == 0)
			{
				iVar9 = 0;
			}
			else
			{
				iVar9 = *(int*)(iVar9 + 0x68);
			}
			uVar6 = sub_6FAABF80();
			uVar11 = *(uint32_t*)(iVar5 + 0x6c);
			if ((((((iVar9 != 0) && (iVar5 = sub_6FB4F990((int)ptUnit, iVar9), iVar5 == 0)) &&
			          (dword_6FBBD258 <= uVar6 - dword_6FBBD250)) &&
			         ((iVar5 = sub_6FB509A0((int)ptUnit), uVar11 <= uVar6 - iVar5 &&
			                                                  (iVar5 = sub_6FB509D0((int)ptUnit), uVar11 <= uVar6 - iVar5)))) &&
			        ((pRoom = UNITS_GetRoom(ptUnit), pRoom == nullptr ||
			                                             (iVar5 = DUNGEON_IsRoomInTown(pRoom), iVar5 == 0)))) &&
			    ((iVar5 = sub_6FB56C30(ptUnit), iVar5 != 0 && (uVar11 = sub_6FB57150(0xf), uVar11 == 0))))
			{
				sub_6FB55820(iVar9, ptUnit, 0.0, 0.0, 0);
				dword_6FBBD250 = uVar6;
				sub_6FB50A00((int)ptUnit, uVar6);
				dword_6FBBD258 = sub_6FB571B0(0x1e, 0x5a);
			}
		}
		return 0;
	}
	uStack_14 = 6;
	if (ptUnit == nullptr)
	{
		uStack_c = 0xffffffff;
	}
	else
	{
		uStack_14 = ptUnit->dwUnitType;
		uStack_c = ptUnit->dwClassId;
	}
	uStack_4 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (uStack_14 == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&uStack_14, (int*)&uStack_c, (int*)&uStack_4,
		    __FILE__, __LINE__);
	}
	if ((uStack_c == 0x1a) && (uVar11 == 0))
	{
		D2_ASSERT(ptUnit != nullptr);
		if (ptUnit->dwSfxAsyncTicks == 0)
		{
			pUnit2 = CUNIT_GetPlayer();
			iVar5 = UNITS_GetDistanceToOtherUnit(ptUnit, pUnit2);
			if (iVar5 < 0x14)
			{
				sub_6FB55820(0xe57, ptUnit, 0.0, 0.0, 0);
				uVar6 = sub_6FAABF80();
				ptUnit->dwSfxAsyncTicks = uVar6;
			}
		}
	}
	D2_ASSERT(ptUnit != nullptr);
	if (((char)ptUnit->bUnitSfx != '\0') && (uVar11 == ptUnit->dwSfxMode))
	{
		return 0;
	}
	uVar6 = sub_6FB50850(ptUnit);
	D2_ASSERT(!((0x23c < uVar6) || (7 < (int)uVar11)));
	iVar5 = *(int*)(byte_6FB957F0 + uVar6 * 4);
	if (iVar5 != 0)
	{
		if (uVar6 == 0x3d)
		{
			uVar6 = *(uint32_t*)(byte_6FB94530 + uVar11 * 4);
		}
		else
		{
			uVar6 = *(uint32_t*)(iVar5 + 0x20);
			if ((uVar6 == 0) && (*(int*)(iVar5 + 0x28) == 0))
				goto LAB_6fb505e6;
			if ((*(uint32_t*)(iVar5 + 0x24) != uVar11) && (*(uint32_t*)(iVar5 + 0x24) != 8))
			{
				if ((*(uint32_t*)(iVar5 + 0x2c) != uVar11) && (*(uint32_t*)(iVar5 + 0x2c) != 8))
					goto LAB_6fb505e6;
				uVar6 = *(uint32_t*)(iVar5 + 0x28);
			}
		}
		uStack_14 = uVar6;
		if (uVar6 != 0)
		{
			iVar5 = sub_6FB52D00();
			if (iVar5 != 0)
			{
				iVar5 = sub_6FB53C30(uVar6);
				uStack_4 = sub_6FB53C60(iVar5);
				uStack_4 = uStack_4 & 0xff;
				puVar7 = (uint32_t*)sub_6FB50910((int)ptUnit);
				for (piVar1 = (int*)*puVar7; piVar1 != nullptr; piVar1 = (int*)piVar1[1])
				{
					iVar9 = *piVar1;
					iVar8 = sub_6FB56090(iVar9);
					uVar6 = uStack_14;
					if ((iVar5 <= iVar8) && (iVar8 < (int)(uStack_4 + iVar5)))
					{
						if (iVar9 != 0)
							goto LAB_6fb5061b;
						break;
					}
				}
			}
			sub_6FB55820(uVar6, ptUnit, 0.0, 0.0, 0);
			goto LAB_6fb5061b;
		}
	}
LAB_6fb505e6:
	puVar7 = (uint32_t*)sub_6FB50910((int)ptUnit);
	piVar1 = (int*)*puVar7;
	while (piVar1 != nullptr)
	{
		iVar5 = *piVar1;
		piVar1 = (int*)piVar1[1];
		iVar9 = sub_6FB56090(iVar5);
		uVar4 = sub_6FB53C90(iVar9);
		if (D2C_ZEXT(uVar4) != 0)
		{
			sub_6FB555C0(iVar5, (int)ptUnit, 0);
		}
	}
LAB_6fb5061b:
	uStack_c = ptUnit->dwUnitType;
	uStack_14 = ptUnit->dwClassId;
	uStack_4 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (uStack_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&uStack_c, (int*)&uStack_14, (int*)&uStack_4,
		    __FILE__, __LINE__);
	}
	if (((char)ptUnit->bUnitSfx != '\0') || (uStack_14 == 0x3b))
	{
		uVar11 = ptUnit->dwSfxMode;
		uVar6 = sub_6FB50850(ptUnit);
		D2_ASSERT(0x23c >= uVar6);
		puVar2 = *(uint8_t**)(byte_6FB957F0 + uVar6 * 4);
		if ((puVar2 != nullptr) &&
		    (((puVar2 != &byte_6FB95520 || ((int)uVar11 <= (int)uStack_18)) &&
		        (*(int*)(puVar2 + uStack_18 * 4) != 0))))
		{
			sub_6FB55820(*(int*)(puVar2 + uStack_18 * 4), ptUnit, 0.0, 0.0, 0);
		}
	}
	sub_6FB50940((int)ptUnit, 1);
	return sub_6FB50970((int)ptUnit, uStack_18);
}

//D2Client.0x6FB50850
int __fastcall sub_6FB50850(D2UnitStrc* pUnit)
{
	int local_c;
	uint32_t local_8;
	int iStack_4;

	local_8 = 6;
	if (pUnit == nullptr)
	{
		local_c = -1;
	}
	else
	{
		local_8 = pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	iStack_4 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_8 == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_8, &local_c, &iStack_4,
		    __FILE__, __LINE__);
	}
	return local_c;
}

//D2Client.0x6FB508B0
uint8_t* __fastcall sub_6FB508B0(D2UnitStrc* pUnit)
{
	uint8_t* local_c;
	int iStack_8;
	int local_4;

	local_c = (uint8_t*)0x6;
	if (pUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = (uint8_t*)pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
	}
	iStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_c == nullptr)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
	}
	return local_c;
}

//D2Client.0x6FB50910
int __fastcall sub_6FB50910(int ptUnit)
{
	D2_ASSERT(ptUnit);
	return ptUnit + 0x78;
}

//D2Client.0x6FB50940
void __fastcall sub_6FB50940(int ptUnit, uint8_t a2)
{
	D2_ASSERT(ptUnit);
	*(uint8_t*)(ptUnit + 0x70) = a2;
}

//D2Client.0x6FB50970
int32_t __fastcall sub_6FB50970(int ptUnit, uint32_t a2)
{
	D2_ASSERT(ptUnit);
	*(uint32_t*)(ptUnit + 0x74) = a2;
	return 0;
}

//D2Client.0x6FB509A0
uint32_t __fastcall sub_6FB509A0(int ptUnit)
{
	D2_ASSERT(ptUnit);
	return *(uint32_t*)(ptUnit + 0x7c);
}

//D2Client.0x6FB509D0
uint32_t __fastcall sub_6FB509D0(int ptUnit)
{
	D2_ASSERT(ptUnit);
	return *(uint32_t*)(ptUnit + 0x80);
}

//D2Client.0x6FB50A00
void __fastcall sub_6FB50A00(int ptUnit, uint32_t a2)
{
	D2_ASSERT(ptUnit);
	*(uint32_t*)(ptUnit + 0x80) = a2;
}

//D2Client.0x6FB50A30
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB50A30(D2UnitStrc* ptUnit, int a2, int a3)
{
	int* piVar1;
	int* piVar2;
	bool bVar3;
	uint32_t uVar4;
	float fVar5;
	int iVar6;
	int iVar7;
	uint32_t extraout_var;
	int iVar8;
	int iVar9;
	uint32_t uVar10;
	uint32_t uVar11;
	bool bVar12;
	float local_10;
	int iStack_c;
	int local_8;
	int local_4;

	local_10 = 8.40779e-45;
	if (ptUnit == nullptr)
	{
		local_8 = -1;
	}
	else
	{
		local_10 = (float)ptUnit->dwUnitType;
		local_8 = ptUnit->dwClassId;
	}
	local_4 = a2;
	iStack_c = UNITS_GetAnimOrSeqMode(ptUnit);
	if ((local_10 == 0.0) &&
	    (D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_10, &local_8, &iStack_c,
	         __FILE__, __LINE__),
	        local_10 == 0.0))
	{
		uVar4 = UNITS_GetHitClass(ptUnit);
		D2_ASSERT(ptUnit != nullptr);
		uVar4 = uVar4 & 0xf;
		if (uVar4 < 0xe)
		{
			D2_ASSERT(0xd >= uVar4);
			uVar11 = (uint32_t)ptUnit->wAnimSpeed;
			if (uVar11 == 0)
			{
				uVar11 = 1;
			}
			fVar5 = (float)((*(int*)(byte_6FB940D4 + uVar4 * 8) * 0x100 + 0x80U) / uVar11);
			if (a3 == 0)
			{
				fVar5 = 0.0;
			}
			sub_6FB55820(*(int*)(byte_6FB940D0 + uVar4 * 8), ptUnit, fVar5, 0.0, 0);
			uVar4 = sub_6FAABF80();
			ptUnit->dwSfxTicks = uVar4;
			return;
		}
		FOG_DisplayAssert("eHitClassBase >= EHITCLASS_NONE && eHitClassBase < NUM_EHITCLASSES",
		    __FILE__, __LINE__);
		exit(-1);
	}
	if (local_10 != 1.4013e-45)
	{
		return;
	}
	iVar6 = sub_6FB4FE50(ptUnit);
	if (iVar6 == 0)
	{
		return;
	}
	if (a2 == 4)
	{
		iStack_c = *(int*)(iVar6 + 4);
		local_10 = *(float*)(iVar6 + 8);
	}
	else
	{
		iStack_c = *(int*)(iVar6 + 0x1c);
		local_10 = *(float*)(iVar6 + 0x20);
	}
	if (a3 == 0)
	{
		local_10 = 0.0;
	}
	if (a2 == 4)
	{
		uVar4 = *(uint32_t*)(iVar6 + 0xc);
	}
	else
	{
		uVar4 = *(uint32_t*)(iVar6 + 0x24);
	}
	bVar12 = iStack_c != 0;
	local_8 = iVar6;
	if (uVar4 < 100)
	{
		iVar7 = sub_6FAABF80();
		bVar12 = 0xe < (uint32_t)(iVar7 - byte_6FBBD254) && bVar12;
		bVar3 = sub_6FB56C70((int)ptUnit);
		if (D2C_ZEXT(bVar3) != 0)
			goto LAB_6fb50cb7;
	}
	if ((bVar12) && (uVar11 = sub_6FB57150(100), (int)uVar11 < (int)uVar4))
	{
		D2_ASSERT(ptUnit != nullptr);
		piVar2 = (int*)ptUnit->pUnitSfxData;
		while (piVar2 != nullptr)
		{
			piVar1 = (int*)piVar2[1];
			iVar7 = *piVar2;
			iVar6 = sub_6FB4FE50(ptUnit);
			if (iVar6 == 0)
			{
				iVar9 = 0;
			}
			else
			{
				iVar9 = *(int*)(iVar6 + 0x68);
			}
			iVar6 = sub_6FB56090(iVar7);
			iVar8 = sub_6FB53C30(iVar6);
			piVar2 = piVar1;
			iVar6 = local_8;
			if (iVar8 == iVar9)
			{
				iVar6 = sub_6FB55D60(iVar7);
				if (iVar6 == 0)
				{
					sub_6FB55BF0(iVar7, 0, 0, 6);
					iVar6 = local_8;
				}
				else
				{
					sub_6FB555C0(iVar7, (int)ptUnit, 1);
					iVar6 = local_8;
				}
			}
		}
		sub_6FB55820(iStack_c, ptUnit, local_10, 0.0, 0);
		uVar4 = sub_6FAABF80();
		ptUnit->dwSfxTicks = uVar4;
		byte_6FBBD254 = sub_6FAABF80();
	}
LAB_6fb50cb7:
	uVar4 = (uint32_t)ptUnit->wAnimSpeed;
	if (uVar4 == 0)
	{
		uVar4 = 1;
	}
	if (local_4 == 4)
	{
		iVar7 = *(int*)(iVar6 + 0x10);
		iVar9 = *(int*)(iVar6 + 0x14);
	}
	else
	{
		iVar7 = *(int*)(iVar6 + 0x28);
		iVar9 = *(int*)(iVar6 + 0x2c);
	}
	if (local_4 == 4)
	{
		uVar10 = *(uint32_t*)(iVar6 + 0x18);
	}
	else
	{
		uVar10 = *(uint32_t*)(iVar6 + 0x30);
	}
	iVar6 = sub_6FB55820(iVar7, ptUnit, (float)((iVar9 * 0x100 + 0x80U) / uVar4), 0.0, 0);
	if (iVar6 != 0)
	{
		sub_6FB55BC0(iVar6, uVar10);
	}
}

//D2Client.0x6FB50D20
void __fastcall sub_6FB50D20(D2UnitStrc* pUnit, int* a2, uint32_t a3)
{
	uint32_t uVar1;
	int iVar2;
	int* piVar3;
	uint32_t local_c;
	int* piStack_8;
	int local_4;

	local_c = 6;
	if (pUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
	}
	piStack_8 = (int*)UNITS_GetAnimOrSeqMode(pUnit);
	uVar1 = local_c;
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, (int*)&piStack_8,
		    __FILE__, __LINE__);
		uVar1 = local_c;
	}
	piStack_8 = (int*)0x6;
	if (pUnit == nullptr)
	{
		local_c = 0xffffffff;
	}
	else
	{
		piStack_8 = (int*)pUnit->dwUnitType;
		local_c = pUnit->dwClassId;
	}
	local_4 = UNITS_GetAnimOrSeqMode(pUnit);
	if (piStack_8 == nullptr)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&piStack_8, (int*)&local_c, &local_4,
		    __FILE__, __LINE__);
	}
	if (a3 == 0)
	{
		a3 = 6;
		if (pUnit == nullptr)
		{
			local_4 = -1;
		}
		else
		{
			a3 = pUnit->dwUnitType;
			local_4 = pUnit->dwClassId;
		}
		a2 = (int*)UNITS_GetAnimOrSeqMode(pUnit);
		piStack_8 = a2;
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pUnit, (int*)&a3, &local_4, (int*)&piStack_8,
			    __FILE__, __LINE__);
			a2 = piStack_8;
		}
	}
	if (uVar1 == 0)
	{
		switch ((int32_t)(a2))
		{
		case 0:
		case 0x4:
		case 0x13:
		switchD_6fb50e43_caseD_0:
			sub_6FB51140(pUnit, a2);
			return;
		case 0x7:
		case 0x8:
			sub_6FB50A30(pUnit, (int)a2, 1);
			return;
		case 0x9:
			iVar2 = 0;
			switch ((int32_t)(pUnit->dwLastHitClass & 0xf))
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				iVar2 = 0x18e;
				break;
			case 10:
			case 0xb:
				iVar2 = 0x191;
			}
			sub_6FB55820(iVar2, pUnit, 0.0, 0.0, 0);
			uVar1 = sub_6FAABF80();
			pUnit->dwSfxTicks = uVar1;
			byte_6FBBD254 = sub_6FAABF80();
			return;
		case 0xc:
			if (local_c != 6)
			{
				sub_6FB55820(0xff, pUnit, 0.0, 0.0, 0);
				return;
			}
			sub_6FB55820(0xff, pUnit, 5.60519e-45, 0.0, 0);
			return;
		case 0xf:
			if (local_c == 4)
			{
				sub_6FB50A30(pUnit, 0xf, 1);
				return;
			}
			break;
		case 0x10:
			if (local_c == 6)
			{
				sub_6FB50A30(pUnit, 0x10, 1);
				return;
			}
		}
	}
	else if ((uVar1 == 1) && (iVar2 = sub_6FB4FE50(pUnit), iVar2 != 0))
	{
		piVar3 = (int*)(iVar2 + 0x80);
		iVar2 = 3;
		do
		{
			if ((a2 == (int*)(uint32_t) * (uint8_t*)(piVar3 + -1)) && (*piVar3 < 0))
			{
				a2 = (int*)(uint32_t) * (uint8_t*)((int)piVar3 + -3);
			}
			piVar3 = piVar3 + 2;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
		switch ((int32_t)(a2))
		{
		case 0:
		case 0x3:
		case 0xd:
			goto switchD_6fb50e43_caseD_0;
		case 0x4:
		case 0x5:
			sub_6FB50A30(pUnit, (int)a2, 1);
			return;
		case 0x8:
		case 0x9:
		case 0xa:
		case 0xb:
			sub_6FB513B0(pUnit, (int)a2);
			return;
		case 0xc:
			sub_6FB51030(pUnit);
		}
	}
}

//D2Client.0x6FB51030
void __fastcall sub_6FB51030(D2UnitStrc* ptUnit)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	local_c = 6;
	if (ptUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = ptUnit->dwUnitType;
		local_4 = ptUnit->dwClassId;
	}
	iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
	}
	if ((local_c == 1) && (iVar3 = sub_6FB4FE50(ptUnit), iVar3 != 0))
	{
		D2_ASSERT(ptUnit != nullptr);
		piVar1 = (int*)ptUnit->pUnitSfxData;
		while (piVar1 != nullptr)
		{
			iVar2 = *piVar1;
			piVar1 = (int*)piVar1[1];
			iVar4 = sub_6FB56090(iVar2);
			iVar4 = sub_6FB53C30(iVar4);
			if ((((((iVar4 == *(int*)(iVar3 + 4)) || (iVar4 == *(int*)(iVar3 + 0x1c))) ||
			          (iVar4 == *(int*)(iVar3 + 0x34))) ||
			         ((iVar4 == *(int*)(iVar3 + 0x68) || (iVar4 == *(int*)(iVar3 + 0x44))))) ||
			        ((iVar4 == *(int*)(iVar3 + 0x48) ||
			            ((iVar4 == *(int*)(iVar3 + 0x4c) || (iVar4 == *(int*)(iVar3 + 0x50))))))) ||
			    ((iVar4 == *(int*)(iVar3 + 0x70) ||
			        ((iVar4 == *(int*)(iVar3 + 0x74) || (iVar4 == *(int*)(iVar3 + 0x78)))))))
			{
				sub_6FB555C0(iVar2, (int)ptUnit, 1);
			}
		}
	}
}

//D2Client.0x6FB51140
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB51140(D2UnitStrc* pUnit, int* a2)
{
	int* piVar1;
	uint32_t uVar2;
	bool bVar3;
	int iVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t uVar6;
	int iVar7;
	float fVar8;
	uint32_t local_10;
	int* local_c;
	uint32_t uStack_8;
	int local_4;

	local_10 = 6;
	if (pUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_10 = pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
	}
	local_c = a2;
	uStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_10 == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_10, &local_4, (int*)&uStack_8,
		    __FILE__, __LINE__);
	}
	uVar2 = local_10;
	uVar6 = pUnit->dwLastHitClass;
	if ((local_10 == 1) && (iVar4 = STATES_CheckState(pUnit, 0x92), iVar4 != 0))
	{
		return;
	}
	sub_6FB4F5A0(pUnit, uVar6, a2, &local_4, (int*)(&uStack_8));
	iVar4 = sub_6FB55820(local_4, pUnit, 0.0, 0.0, 0);
	sub_6FB55820(uStack_8, pUnit, 0.0, 0.0, 0);
	if ((iVar4 != 0) && (pDVar5 = CUNIT_GetPlayer(), pUnit == pDVar5))
	{
		sub_6FB55BC0(iVar4, 0xff);
	}
	if ((uVar2 == 1) && (local_c == nullptr))
	{
		sub_6FB51030(pUnit);
		sub_6FB51F00(pUnit, -1);
	}
	iVar4 = STATES_CheckState(pUnit, 1);
	if (iVar4 != 0)
	{
		return;
	}
	if (((uint8_t)uVar6 & 0xf0) == 0xa0)
	{
		return;
	}
	if (uVar2 == 1)
	{
		iVar4 = sub_6FB4FE50(pUnit);
		if (iVar4 == 0)
			goto LAB_6fb51387;
		if ((local_c == (int*)0x3) || (local_c == (int*)0xd))
		{
			bVar3 = sub_6FB56C70((int)pUnit);
			if (D2C_ZEXT(bVar3) != 0)
				goto LAB_6fb51387;
			iVar7 = *(int*)(iVar4 + 0x34);
			fVar8 = *(float*)(iVar4 + 0x38);
		}
		else
		{
			iVar7 = *(int*)(iVar4 + 0x3c);
			fVar8 = *(float*)(iVar4 + 0x40);
		}
		if (iVar7 != 0)
		{
			sub_6FB55820(iVar7, pUnit, fVar8, 0.0, 0);
		}
		if (iVar7 != 0x2e9)
			goto LAB_6fb51387;
		sub_6FB55820(0x2ea, pUnit, 1.48538e-43, 0.0, 0);
		iVar4 = 0x2eb;
		fVar8 = 2.70451e-43;
	}
	else
	{
		if (uVar2 != 0)
			goto LAB_6fb51387;
		local_10 = pUnit->dwUnitType;
		uStack_8 = pUnit->dwClassId;
		local_4 = UNITS_GetAnimOrSeqMode(pUnit);
		if (local_10 == 0)
		{
			D2COMMON_11013_ConvertMode(pUnit, (int*)&local_10, (int*)&uStack_8, &local_4,
			    __FILE__, __LINE__);
		}
		D2_ASSERT(6 >= uStack_8);
		piVar1 = (int*)gpuint8_t_6FB9622C[uStack_8];
		if (piVar1 == nullptr)
			goto LAB_6fb51387;
		if ((local_c == (int*)0x4) || (local_c == (int*)0x13))
		{
			bVar3 = sub_6FB56C70((int)pUnit);
			if (D2C_ZEXT(bVar3) != 0)
				goto LAB_6fb51387;
			iVar4 = *piVar1;
			fVar8 = 2.8026e-45;
		}
		else
		{
			iVar4 = piVar1[1];
			fVar8 = 1.4013e-45;
		}
		if (iVar4 == 0)
			goto LAB_6fb51387;
	}
	sub_6FB55820(iVar4, pUnit, fVar8, 0.0, 0);
LAB_6fb51387:
	uVar6 = sub_6FAABF80();
	pUnit->dwSfxTicks = uVar6;
	byte_6FBBD254 = sub_6FAABF80();
}

//D2Client.0x6FB513B0
void __fastcall sub_6FB513B0(D2UnitStrc* ptUnit, int a2)
{
	int iVar1;
	int iVar2;
	uint32_t uVar3;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	local_c = 6;
	if (ptUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = ptUnit->dwUnitType;
		local_4 = ptUnit->dwClassId;
	}
	iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
	}
	if ((local_c == 1) && (iVar1 = sub_6FB4FE50(ptUnit), iVar1 != 0))
	{
		iVar2 = sub_6FAABF80();
		if (a2 == 8)
		{
			iVar1 = *(int*)(iVar1 + 0x44);
		}
		else if (a2 == 9)
		{
			iVar1 = *(int*)(iVar1 + 0x48);
		}
		else if (a2 == 10)
		{
			iVar1 = *(int*)(iVar1 + 0x4c);
		}
		else
		{
			if (a2 != 0xb)
			{
				return;
			}
			iVar1 = *(int*)(iVar1 + 0x50);
		}
		if (iVar1 == 0xa84)
		{
			D2_ASSERT(ptUnit != nullptr);
			if (iVar2 - ptUnit->dwSfxTicks < 0x19)
			{
				return;
			}
		}
		else if (iVar1 == 0)
		{
			return;
		}
		sub_6FB55820(iVar1, ptUnit, 0.0, 0.0, 0);
		uVar3 = sub_6FAABF80();
		D2_ASSERT(ptUnit != nullptr);
		ptUnit->dwSfxTicks = uVar3;
		byte_6FBBD254 = sub_6FAABF80();
	}
}

//D2Client.0x6FB514E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB514E0(D2UnitStrc* pUnit, uint32_t a2)
{
	uint8_t* puVar1;
	int iVar2;
	bool bVar3;
	bool bVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	float fVar6;
	uint32_t extraout_var_01;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	D2UnitStrc* local_8;

	D2_ASSERT(!((pUnit == nullptr) || (6 < (uint32_t)pUnit->dwClassId)));
	puVar1 = gpuint8_t_6FB9622C[pUnit->dwClassId];
	if (puVar1 == nullptr)
	{
		return;
	}
	uVar8 = a2 & 0xffff;
	iVar9 = 0;
	pDVar5 = CUNIT_GetPlayer();
	if ((pUnit == pDVar5) && (bVar3 = sub_6FB283E0(), D2C_ZEXT(bVar3) != 0))
	{
		return;
	}
	if (((0x18 < uVar8) && (uVar8 < 0x21)) &&
	    (bVar3 = sub_6FB56C70((int)pUnit), D2C_ZEXT(bVar3) == 0))
	{
		iVar9 = *(int*)(puVar1 + 0x20) + -0x32 + uVar8 * 2;
	}
	if ((0x20 < uVar8) && (uVar8 < 0x54))
	{
		iVar9 = *(int*)(puVar1 + 0x24) + -0x21 + uVar8;
		if (uVar8 == 0x23)
		{
			sub_6FB57030(0x1250, 0, 300, 1, iVar9, 0xfa, 1);
			return;
		}
		if (uVar8 == 0x22)
		{
			sub_6FB57030(0x124e, 0x1db, 800, 1, iVar9, 0x20d, 1);
			return;
		}
		if (uVar8 == 0x25)
		{
			sub_6FB57030(0, 0, 0x5dc, 0, iVar9, 0, 0);
			return;
		}
		if (uVar8 == 0x21)
		{
			sub_6FB57030(0x124d, 0, 0x1db, 0, iVar9, 0x1a9, 1);
			return;
		}
		if (uVar8 == 0x32)
		{
			sub_6FB57030(0x1255, 0x1db, 0x44c, 1, iVar9, 0x20d, 1);
			return;
		}
		if (uVar8 == 0x34)
		{
			sub_6FB57030(0x1256, 0, 0x1a9, 1, iVar9, 0x177, 1);
			return;
		}
		if (uVar8 == 0x42)
		{
			sub_6FB57030(0x1254, 0, 0x1a9, 0, iVar9, 0x177, 1);
			return;
		}
		if (uVar8 != 0x4b)
		{
			if (uVar8 == 0x50)
			{
				sub_6FB57030(0x125a, 0, 500, 1, iVar9, 0x1db, 1);
				return;
			}
			if (uVar8 != 0x52)
			{
				if (uVar8 == 0x53)
				{
					sub_6FB57030(0x1258, 0, 0x20d, 1, iVar9, 0x1a9, 1);
					return;
				}
				switch (uVar8)
				{
				case 0x26:
				case 0x28:
				case 0x29:
				case 0x2a:
				case 0x2b:
				case 0x2c:
				case 0x2e:
				case 0x2f:
				case 0x37:
				case 0x38:
					fVar6 = 0.0;
					break;
				default:
					fVar6 = 1.68156e-44;
				}
				iVar9 = sub_6FB55820(iVar9, pUnit, fVar6, 0.0, 0);
				uVar8 = sub_6FB56090(iVar9);
				sub_6FB1F1C0((int*)pUnit, uVar8);
				return;
			}
			sub_6FB57030(0x1259, 0, 0x226, 1, iVar9, 400, 1);
			return;
		}
		sub_6FB57030(0x1257, 0, 0x1db, 0, iVar9, 0x145, 1);
		return;
	}
	bVar3 = false;
	iVar7 = dword_6FBBD25C;
	iVar2 = dword_6FBBD260;
	local_8 = pUnit;
	switch (uVar8)
	{
	case 1:
		iVar9 = 0xeb;
		break;
	case 2:
		iVar9 = 7;
		local_8 = nullptr;
		break;
	case 3:
		iVar9 = 10;
		local_8 = nullptr;
		break;
	case 4:
		iVar9 = 0xb;
		local_8 = nullptr;
		break;
	case 5:
		iVar9 = 0xc;
		local_8 = nullptr;
		break;
	case 6:
		iVar9 = 0xd;
		local_8 = nullptr;
		break;
	case 7:
		iVar9 = 0x8b6;
		break;
	case 8:
		iVar9 = 0x8b7;
		break;
	case 9:
		iVar9 = 9;
		break;
	default:
		goto switchD_6fb5177a_caseD_a;
	case 0xb:
		iVar9 = 0xe4;
		break;
	case 0x13:
		iVar9 = *(int*)(puVar1 + 8);
		goto LAB_6fb51784;
	case 0x14:
		iVar9 = *(int*)(puVar1 + 0x18);
		goto LAB_6fb51784;
	case 0x15:
		iVar9 = *(int*)(puVar1 + 0xc);
		goto LAB_6fb51784;
	case 0x16:
		iVar9 = *(int*)(puVar1 + 0x10);
		goto LAB_6fb51784;
	case 0x17:
		iVar9 = *(int*)(puVar1 + 0x14);
		goto LAB_6fb51784;
	case 0x18:
		iVar9 = *(int*)(puVar1 + 0x1c);
	LAB_6fb51784:
		bVar3 = true;
		bVar4 = sub_6FB56C70((int)pUnit);
		if (D2C_ZEXT(bVar4) == 0)
		{
		switchD_6fb5177a_caseD_a:
			if ((iVar9 != 0) &&
			    (((iVar7 = dword_6FBBD25C, iVar2 = dword_6FBBD260, !bVar3 || (iVar7 = sub_6FAABF80(), iVar2 = iVar9, iVar9 != dword_6FBBD260)) ||
			        (0x4a < (uint32_t)(iVar7 - dword_6FBBD25C)))))
				break;
		}
		return;
	}
	dword_6FBBD260 = iVar2;
	dword_6FBBD25C = iVar7;
	iVar9 = sub_6FB55820(iVar9, local_8, 0.0, 0.0, 0);
	uVar8 = sub_6FB56090(iVar9);
	sub_6FB1F1C0((int*)pUnit, uVar8);
}

//D2Client.0x6FB51920
void __fastcall sub_6FB51920(uint32_t a1, uint32_t a2, uint32_t a3)
{
	short sVar1;
	D2UnitStrc* pDVar2;
	D2StatListStrc* pStatList;
	D2SkillStrc* pDVar3;
	uint32_t uVar4;
	D2UnitStrc* pDVar5;
	uint32_t uVar6;
	float fVar7;
	float fVar8;
	int iVar9;
	int iVar10;
	int local_8;
	int iStack_4;

	pDVar2 = sub_6FB269F0(a1, a2 & 0xff);
	uVar4 = a3;
	if (pDVar2 == nullptr)
	{
		return;
	}
	switch (a3 & 0xffff)
	{
	case 10:
		iVar10 = sub_6FB55820(0xa71, pDVar2, 0.0, 0.0, 0);
		sub_6FB55BC0(iVar10, 0x78);
		return;
	default:
		goto switchD_6fb51959_caseD_b;
	case 0xc:
		pStatList = STATLIST_GetStatListFromUnitAndState(pDVar2, 0x44);
		if (pStatList == nullptr)
		{
			return;
		}
		iVar10 = STATLIST_GetStatValue(pStatList, 0x15e, 0);
		pDVar3 = SKILLS_GetHighestLevelSkillFromUnitAndId(pDVar2, iVar10);
		if (pDVar3 == nullptr)
		{
			return;
		}
		if (iVar10 < 0)
		{
			return;
		}
		if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xba0) <= iVar10)
		{
			return;
		}
		iVar10 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xb98) + iVar10 * 0x23c;
		if (iVar10 == 0)
		{
			return;
		}
		sVar1 = *(short*)(iVar10 + 0xfc);
		if (sVar1 < 1)
		{
			return;
		}
		sub_6FB55820((int)sVar1, pDVar2, 0.0, 0.0, 0);
		return;
	case 0xd:
		sub_6FB55820(0xa4a, pDVar2, 0.0, 0.0, 0);
		return;
	case 0xe:
		sub_6FB55820(0xa4b, pDVar2, 0.0, 0.0, 0);
		return;
	case 0xf:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (local_8 != 0x10f)
		{
			return;
		}
		sub_6FB55820(0x10c2, pDVar2, 0.0, 0.0, 0);
		return;
	case 0x10:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (a3 != 1)
		{
			return;
		}
		iVar10 = sub_6FB4FE50(pDVar2);
		if (iVar10 != 0)
		{
			sub_6FB55820(*(int*)(iVar10 + 0x74), pDVar2, 0.0, 0.0, 0);
			return;
		}
		sub_6FB55820(0, pDVar2, 0.0, 0.0, 0);
		return;
	case 0x11:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (a3 != 1)
		{
			return;
		}
		iVar10 = sub_6FB4FE50(pDVar2);
		if (iVar10 == 0)
		{
			return;
		}
		iVar9 = sub_6FAABF80();
		if ((uint32_t)(iVar9 - byte_6FBBD254) < 4)
		{
			return;
		}
		iVar9 = 0;
		fVar7 = 0.0;
		uVar4 = sub_6FB57150(3);
		sub_6FB55820(*(int*)(iVar10 + 0x78), pDVar2, (float)(uVar4 + 6), fVar7, iVar9);
		uVar4 = sub_6FAABF80();
		pDVar2->dwSfxTicks = uVar4;
		byte_6FBBD254 = sub_6FAABF80();
		return;
	case 0x12:
		iVar9 = 0;
		fVar8 = 1.4013e-45;
		fVar7 = 0.0;
		pDVar5 = CUNIT_GetPlayer();
		iVar10 = sub_6FB464A0((int)pDVar2, 1);
		sub_6FB55820(iVar10, pDVar5, fVar7, fVar8, iVar9);
		return;
	case 0x54:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (local_8 == 0x10f)
		{
			sub_6FB55820(0x1207, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1207;
		}
		else
		{
			sub_6FB55820(0x1211, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1211;
		}
		break;
	case 0x55:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (local_8 == 0x10f)
		{
			sub_6FB55820(0x1204, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1204;
		}
		else
		{
			sub_6FB55820(0x1208, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1208;
		}
		break;
	case 0x56:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (local_8 == 0x10f)
		{
			sub_6FB55820(0x1205, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1205;
		}
		else
		{
			sub_6FB55820(0x120b, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x120b;
		}
		break;
	case 0x57:
		a3 = pDVar2->dwUnitType;
		local_8 = pDVar2->dwClassId;
		iStack_4 = UNITS_GetAnimOrSeqMode(pDVar2);
		if (a3 == 0)
		{
			D2COMMON_11013_ConvertMode(pDVar2, (int*)&a3, &local_8, &iStack_4,
			    __FILE__, __LINE__);
		}
		if (local_8 == 0x10f)
		{
			sub_6FB55820(0x1206, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x1206;
		}
		else
		{
			sub_6FB55820(0x120e, pDVar2, 0.0, 0.0, 0);
			uVar6 = 0x120e;
		}
		break;
	case 0x5a:
		sub_6FB55820(0x111b, pDVar2, 0.0, 0.0, 0);
		return;
	case 0x5b:
		iVar10 = 0;
		fVar8 = 0.0;
		fVar7 = 0.0;
		pDVar2 = CUNIT_GetPlayer();
		sub_6FB55820(8, pDVar2, fVar7, fVar8, iVar10);
		return;
	case 0x5c:
		sub_6FB57100(0x19, 1);
		return;
	case 0x5d:
		sub_6FB55820(0x9f9, pDVar2, 0.0, 0.0, 0);
		return;
	}
	sub_6FB1F1C0((int*)pDVar2, uVar6);
switchD_6fb51959_caseD_b:
	if (pDVar2->dwUnitType == 0)
	{
		sub_6FB514E0(pDVar2, uVar4);
	}
}

//D2Client.0x6FB51F00
void __fastcall sub_6FB51F00(D2UnitStrc* pUnit, int a2)
{
	int iVar1;
	int iVar2;
	uint32_t local_c;
	uint32_t uStack_8;
	int local_4;

	local_c = 6;
	if (pUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = pUnit->dwUnitType;
		local_4 = pUnit->dwClassId;
	}
	uStack_8 = UNITS_GetAnimOrSeqMode(pUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, &local_4, (int*)&uStack_8,
		    __FILE__, __LINE__);
	}
	if (pUnit != nullptr)
	{
		if (pUnit->bHasActiveSound == 0)
		{
			if (a2 < 0)
			{
				return;
			}
		}
		else if (0 < a2)
		{
			return;
		}
		pUnit->bHasActiveSound = (uint32_t)(0 < a2);
		if (local_c == 1)
		{
			iVar1 = sub_6FB4FE50(pUnit);
			if (iVar1 != 0)
			{
				sub_6FB549C0(*(int*)(iVar1 + 4), a2);
				sub_6FB549C0(*(int*)(iVar1 + 0x1c), a2);
				sub_6FB549C0(*(int*)(iVar1 + 0x34), a2);
				sub_6FB549C0(*(int*)(iVar1 + 0x3c), a2);
				sub_6FB549C0(*(int*)(iVar1 + 0x78), a2);
				sub_6FB549C0(*(int*)(iVar1 + 0x58), a2);
				return;
			}
		}
		else if (local_c == 2)
		{
			local_c = pUnit->dwUnitType;
			uStack_8 = pUnit->dwClassId;
			local_4 = UNITS_GetAnimOrSeqMode(pUnit);
			if (local_c == 0)
			{
				D2COMMON_11013_ConvertMode(pUnit, (int*)&local_c, (int*)&uStack_8, &local_4,
				    __FILE__, __LINE__);
			}
			D2_ASSERT(0x23c >= uStack_8);
			iVar1 = *(int*)(byte_6FB957F0 + uStack_8 * 4);
			if (iVar1 != 0)
			{
				iVar2 = 0;
				do
				{
					sub_6FB549C0(*(int*)(iVar1 + iVar2 * 4), a2);
					iVar2 = iVar2 + 1;
				} while (iVar2 < 8);
			}
		}
		return;
	}
	FOG_DisplayAssert("ptUnit", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB520A0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB520A0()
{
	uint8_t* puVar1;
	uint32_t uVar2;
	D2UnitStrc* pUnit;
	D2ActiveRoomStrc* pRoom;
	int iVar3;
	int iVar4;
	uint16_t extraout_var;
	uint8_t** ppuVar5;

	pUnit = CUNIT_GetPlayer();
	pRoom = UNITS_GetRoom(pUnit);
	if (pRoom == nullptr)
	{
		return;
	}
	iVar3 = DUNGEON_GetLevelIdFromRoom(pRoom);
	if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xc5c) <= iVar3)
	{
		return;
	}
	if (iVar3 == dword_6FBBD264)
	{
		return;
	}
	if ((&dword_6FBBC250)[iVar3] != 0)
	{
		dword_6FBBD264 = iVar3;
		return;
	}
	ppuVar5 = &ptr_6FB964E8;
	do
	{
		puVar1 = *ppuVar5;
		if (puVar1 == nullptr)
		{
			dword_6FBBD264 = iVar3;
			return;
		}
		iVar4 = 0;
		do
		{
			if (*(int*)(puVar1 + iVar4 * 4) == 0)
				break;
			if (*(int*)(puVar1 + iVar4 * 4) == iVar3)
			{
				iVar4 = 0;
				dword_6FBBD264 = iVar3;
				goto LAB_6fb52116;
			}
			iVar4 = iVar4 + 1;
		} while (iVar4 < 10);
		ppuVar5 = ppuVar5 + 1;
		if ((int)&tbl_6FB96537 < (int)ppuVar5)
		{
			dword_6FBBD264 = iVar3;
			return;
		}
	} while (true);
	while (true)
	{
		iVar4 = iVar4 + 1;
		(&dword_6FBBC250)[*(int*)(puVar1 + iVar3)] = 1;
		if (9 < iVar4)
			break;
	LAB_6fb52116:
		iVar3 = iVar4 * 4;
		if (*(int*)(puVar1 + iVar3) == 0)
			break;
	}
	if ((*(int*)(puVar1 + 0x28) != 0) && (iVar3 = sub_6FB06D80(*(int*)(puVar1 + 0x28)), iVar3 == 0))
	{
		return;
	}
	D2_ASSERT(pUnit != nullptr);
	uVar2 = pUnit->dwSfxTicks;
	iVar3 = sub_6FAABF80();
	if ((0x3e < iVar3 - uVar2) && (iVar3 = sub_6FB56010(), iVar3 == 0))
	{
		sub_6FB514E0(pUnit, D2C_ZEXT(*(uint16_t*)(puVar1 + 0x2c)));
		return;
	}
}

//D2Client.0x6FB52190
void __fastcall sub_6FB52190(D2UnitStrc* ptUnit)
{
	uint32_t uVar1;
	int iVar2;
	int iVar3;
	uint32_t local_c;
	int iStack_8;
	int local_4;

	local_c = 6;
	if (ptUnit == nullptr)
	{
		local_4 = -1;
	}
	else
	{
		local_c = ptUnit->dwUnitType;
		local_4 = ptUnit->dwClassId;
	}
	iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
	if (local_c == 0)
	{
		D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
		    __FILE__, __LINE__);
	}
	if (local_c == 1)
	{
		uVar1 = sub_6FAABF80();
		iVar2 = sub_6FB4FE50(ptUnit);
		if (iVar2 != 0)
		{
			iVar2 = *(int*)(iVar2 + 0x70);
			if ((iVar2 != 0) && (iVar3 = sub_6FB29550((int*)ptUnit), iVar3 == 0))
			{
				D2_ASSERT(ptUnit != nullptr);
				if (ptUnit->dwSfxAsyncTicks == 0)
				{
					sub_6FB55820(iVar2, ptUnit, 0.0, 0.0, 0);
					dword_6FBBD250 = uVar1;
					ptUnit->dwSfxAsyncTicks = uVar1;
					dword_6FBBD258 = sub_6FB571B0(0x1e, 0x5a);
					return;
				}
			}
			local_c = 6;
			if (ptUnit == nullptr)
			{
				local_4 = -1;
			}
			else
			{
				local_c = ptUnit->dwUnitType;
				local_4 = ptUnit->dwClassId;
			}
			iStack_8 = UNITS_GetAnimOrSeqMode(ptUnit);
			if (local_c == 0)
			{
				D2COMMON_11013_ConvertMode(ptUnit, (int*)&local_c, &local_4, &iStack_8,
				    __FILE__, __LINE__);
			}
			if (iStack_8 == 8)
			{
				sub_6FB513B0(ptUnit, 8);
			}
		}
	}
}

//D2Client.0x6FB522F0
int __fastcall sub_6FB522F0(int* a1)
{
	int iVar1;
	int iVar2;

	if ((a1 == nullptr) || (*a1 != 1))
	{
		iVar2 = -1;
	}
	else
	{
		iVar2 = a1[1];
		if (((-1 < iVar2) && (iVar2 < *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80))) &&
		    (iVar1 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar2 * 0x1a8, iVar1 != 0))
		{
			return (int)*(short*)(iVar1 + 2);
		}
	}
	return iVar2;
}

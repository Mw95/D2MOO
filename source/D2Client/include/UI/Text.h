#pragma once

#include <D2Client.h>


#pragma pack(push, 1)
struct D2HoverTextBoxStrc
{
	D2SplittedTextStrc* pLines;				//0x00
	int32_t nLines;							//0x04
	int32_t unk0x08;						//0x08
	uint32_t unk0x0C;						//0x0C
	uint16_t nWidth;						//0x10
	uint16_t nHeight;						//0x12
	uint16_t unk0x14;						//0x14
	uint8_t unk0x16[0x16];					//0x16
};
#pragma pack(pop)

//D2Client.0x6FB8D220
extern int32_t dword_6FB8D220;
//D2Client.0x6FB8D228
extern uint32_t tbl_6FB8D228[21];
//D2Client.0x6FB8D27C
extern uint32_t dword_6FB8D27C;
//D2Client.0x6FB8D29C
extern int32_t dword_6FB8D29C;
//D2Client.0x6FB8D2A0
extern uint16_t word_6FB8D2A0[2];
//D2Client.0x6FB8D430
extern uint16_t word_6FB8D430;
//D2Client.0x6FB8DADC
extern int32_t dword_6FB8DADC;
//D2Client.0x6FB8DAE0
extern uint8_t byte_6FB8DAE0[4];
//D2Client.0x6FB8DAE4
extern uint8_t byte_6FB8DAE4[36];
//D2Client.0x6FB8DB08
extern uint8_t byte_6FB8DB08[4];
//D2Client.0x6FB8DB0C
extern uint8_t byte_6FB8DB0C[36];
//D2Client.0x6FB8DB30
extern uint32_t dword_6FB8DB30;
//D2Client.0x6FB8E360
extern uint8_t* gpuint8_t_6FB8E360[7];
//D2Client.0x6FB8E37C
extern uint16_t word_6FB8E37C[2];
//D2Client.0x6FBB9D90
extern RECT gaHoverTextRects[16];
//D2Client.0x6FBB9E90
extern uint32_t* gpuint32_t_6FBB9E90;
//D2Client.0x6FBB9E98
extern int32_t dword_6FBB9E98;
//D2Client.0x6FBB9E9C
extern int32_t* gpint32_t_6FBB9E9C;
//D2Client.0x6FBB9EA4
extern uint32_t dword_6FBB9EA4;
//D2Client.0x6FBB9EA8
extern int32_t dword_6FBB9EA8;
//D2Client.0x6FBB9EAC
extern int32_t dword_6FBB9EAC;
//D2Client.0x6FBB9EB0
extern int32_t dword_6FBB9EB0;
//D2Client.0x6FBB9EB8
extern int32_t dword_6FBB9EB8;
//D2Client.0x6FBB9EBC
extern int32_t dword_6FBB9EBC;
//D2Client.0x6FBB9EC8
extern uint8_t byte_6FBB9EC8;
//D2Client.0x6FBB9ECC
extern uint8_t* ptr_6FBB9ECC;
//D2Client.0x6FBB9ED0
extern int16_t word_6FBB9ED0;
//D2Client.0x6FBB9ED2
extern uint8_t* ptr_6FBB9ED2;
//D2Client.0x6FBB9ED6
extern int16_t word_6FBB9ED6;
//D2Client.0x6FBB9ED8
extern uint32_t* gpuint32_t_6FBB9ED8;
//D2Client.0x6FBB9EDC
extern int16_t word_6FBB9EDC;
//D2Client.0x6FBB9EDE
extern uint32_t dword_6FBB9EDE;
//D2Client.0x6FBB9EE2
extern uint32_t dword_6FBB9EE2;
//D2Client.0x6FBB9EEA
extern uint32_t dword_6FBB9EEA;
//D2Client.0x6FBB9EEE
extern uint32_t dword_6FBB9EEE;
//D2Client.0x6FBB9EF2
extern int32_t dword_6FBB9EF2;
//D2Client.0x6FBB9EF6
extern int32_t dword_6FBB9EF6;
//D2Client.0x6FBB9EFA
extern uint16_t word_6FBB9EFA;
//D2Client.0x6FBB9EFC
extern uint32_t dword_6FBB9EFC;
//D2Client.0x6FBB9F00
extern uint32_t dword_6FBB9F00;
//D2Client.0x6FBB9F0C
extern uint32_t dword_6FBB9F0C;
//D2Client.0x6FBB9F10
extern int32_t dword_6FBB9F10;
//D2Client.0x6FBB9F14
extern uint8_t byte_6FBB9F14;
//D2Client.0x6FBB9F18
extern int32_t dword_6FBB9F18;
//D2Client.0x6FBB9F1C
extern uint8_t byte_6FBB9F1C;
//D2Client.0x6FBB9F1E
extern uint32_t dword_6FBB9F1E;
//D2Client.0x6FBB9F22
extern uint8_t byte_6FBB9F22;
//D2Client.0x6FBB9F23
extern uint32_t dword_6FBB9F23;
//D2Client.0x6FBB9F27
extern uint32_t dword_6FBB9F27;
//D2Client.0x6FBB9F2B
extern DWORD dword_6FBB9F2B;
//D2Client.0x6FBB9F2F
extern uint32_t dword_6FBB9F2F;
//D2Client.0x6FBB9F33
extern uint32_t dword_6FBB9F33;
//D2Client.0x6FBB9F38
extern uint32_t* gpuint32_t_6FBB9F38;
//D2Client.0x6FBB9F3C
extern uint32_t dword_6FBB9F3C;
//D2Client.0x6FBB9F40
extern D2TextHeaderStrc* gpTextHeader_6FBB9F40;
//D2Client.0x6FBB9F44
extern uint16_t word_6FBB9F44;
//D2Client.0x6FBB9F48
extern uint8_t byte_6FBB9F48;
//D2Client.0x6FBB9F4C
extern uint8_t byte_6FBB9F4C;
//D2Client.0x6FBB9F50
extern uint32_t dword_6FBB9F50;
//D2Client.0x6FBB9F54
extern int32_t dword_6FBB9F54;
//D2Client.0x6FBB9F58
extern uint8_t* gpuint8_t_6FBB9F58;
//D2Client.0x6FBB9F5C
extern uint32_t dword_6FBB9F5C;
//D2Client.0x6FBB9F60
extern int32_t dword_6FBB9F60;
//D2Client.0x6FBB9F64
extern int32_t dword_6FBB9F64;
//D2Client.0x6FBB9F68
extern int32_t dword_6FBB9F68;
//D2Client.0x6FBB9F70
extern D2CellFileStrc* gpCellFile_6FBB9F70;
//D2Client.0x6FBB9F74
extern D2CellFileStrc* gpCellFile_6FBB9F74;
//D2Client.0x6FBB9F78
extern D2CellFileStrc* gpCellFile_6FBB9F78;
//D2Client.0x6FBB9F7C
extern int32_t dword_6FBB9F7C;
//D2Client.0x6FBB9FA8
extern uint8_t byte_6FBB9FA8;
//D2Client.0x6FBB9FBC
extern uint8_t byte_6FBB9FBC;

//D2Client.0x6FB1A7C0
void __cdecl sub_6FB1A7C0(int* a1);
//D2Client.0x6FB1A820
void __cdecl sub_6FB1A820();
//D2Client.0x6FB1A870
void __cdecl sub_6FB1A870();
//D2Client.0x6FB1AAF0
void __fastcall sub_6FB1AAF0(int* a1);
//D2Client.0x6FB1AB80
void __fastcall sub_6FB1AB80(uint32_t a1);
//D2Client.0x6FB1ABA0
void __fastcall sub_6FB1ABA0(int* a1, int a2, int a3);
//D2Client.0x6FB1AC60
void __cdecl sub_6FB1AC60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FB1AD00
void __cdecl sub_6FB1AD00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FB1ADA0
void __cdecl sub_6FB1ADA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FB1AE00
uint32_t __cdecl sub_6FB1AE00();
//D2Client.0x6FB1B0B0
void __fastcall sub_6FB1B0B0(int a1);
//D2Client.0x6FB1B0F0
void __cdecl sub_6FB1B0F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FB1B1D0
void __fastcall sub_6FB1B1D0(int a1);
//D2Client.0x6FB1B1F0
void __cdecl sub_6FB1B1F0();
//D2Client.0x6FB1B200
void __fastcall sub_6FB1B200(int a1);
//D2Client.0x6FB1B260
void __cdecl sub_6FB1B260();
//D2Client.0x6FB1B4F0
void __fastcall sub_6FB1B4F0(int a1, D2HoverTextStrc* pHoverText, Unicode* pUnicode, POINT* pPosition);
//D2Client.0x6FB1B820
uint32_t __fastcall sub_6FB1B820(int* a1, int* a2);
//D2Client.0x6FB1B8A0
void __cdecl sub_6FB1B8A0();
//D2Client.0x6FB1BA00
void __fastcall sub_6FB1BA00(int a1);
//D2Client.0x6FB1BE70
uint32_t __fastcall sub_6FB1BE70(int* a1);
//D2Client.0x6FB1C1C0
void __cdecl sub_6FB1C1C0();
//D2Client.0x6FB1C450
void __cdecl sub_6FB1C450();
//D2Client.0x6FB1C600
void __fastcall sub_6FB1C600(Unicode* pUnicode, uint32_t a2);
//D2Client.0x6FB1C830
void __fastcall sub_6FB1C830(int a12);
//D2Client.0x6FB1C950
void __fastcall sub_6FB1C950(int a1, int a22);
//D2Client.0x6FB1CBD0
void __fastcall sub_6FB1CBD0(uint8_t* a1, uint32_t a2);
//D2Client.0x6FB1CBE0
void __cdecl sub_6FB1CBE0();
//D2Client.0x6FB1CC20
void __fastcall sub_6FB1CC20(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3);
//D2Client.0x6FB1CF10
uint32_t* __fastcall sub_6FB1CF10(short* a1, int* a2, uint16_t* a3);
//D2Client.0x6FB1D110
void __fastcall sub_6FB1D110(uint32_t a1, int a2, int a3);
//D2Client.0x6FB1D380
D2UnitStrc* __cdecl sub_6FB1D380();
//D2Client.0x6FB1D3C0
void __fastcall sub_6FB1D3C0(int a1);
//D2Client.0x6FB1DE10
void __fastcall sub_6FB1DE10(int a1);
//D2Client.0x6FB1E060
void __fastcall sub_6FB1E060(int* a1);
//D2Client.0x6FB1E0B0
void __fastcall sub_6FB1E0B0(D2HoverTextStrc* pHoverText);
//D2Client.0x6FB1E120
void __fastcall sub_6FB1E120(int a1);
//D2Client.0x6FB1E670
void __fastcall sub_6FB1E670(int a1);
//D2Client.0x6FB1E6B0
D2TextHeaderStrc* __cdecl sub_6FB1E6B0();
//D2Client.0x6FB1E6C0
Unicode* __fastcall sub_6FB1E6C0(uint16_t a1);
//D2Client.0x6FB1E710
void __cdecl sub_6FB1E710();
//D2Client.0x6FB1E810
void __cdecl sub_6FB1E810();
//D2Client.0x6FB1E8F0
void __cdecl sub_6FB1E8F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FB1E990
void __cdecl sub_6FB1E990();
//D2Client.0x6FB1E9E0
void __cdecl sub_6FB1E9E0();
//D2Client.0x6FB1EB70
void __fastcall sub_6FB1EB70(int a1);
//D2Client.0x6FB1EDF0
void __fastcall sub_6FB1EDF0(int a1);
//D2Client.0x6FB1EE20
void __fastcall sub_6FB1EE20(int a1, int a2);
//D2Client.0x6FB1EE90
bool __cdecl sub_6FB1EE90();
//D2Client.0x6FB1EEA0
void __cdecl sub_6FB1EEA0();
//D2Client.0x6FB1EFB0
void __cdecl sub_6FB1EFB0();
//D2Client.0x6FB1F140
uint32_t __cdecl sub_6FB1F140();
//D2Client.0x6FB1F160
void __cdecl sub_6FB1F160();
//D2Client.0x6FB1F1A0
void __cdecl sub_6FB1F1A0();
//D2Client.0x6FB1F1C0
void __fastcall sub_6FB1F1C0(int* a1, uint32_t a2);
//D2Client.0x6FB1F320
void __cdecl sub_6FB1F320();
//D2Client.0x6FB1F350
void __cdecl sub_6FB1F350();
//D2Client.0x6FB1F370
void __cdecl sub_6FB1F370();
//D2Client.0x6FB1F380
void __cdecl sub_6FB1F380();
//D2Client.0x6FB1F390
void __cdecl sub_6FB1F390();
//D2Client.0x6FB1F590
void __cdecl sub_6FB1F590();
//D2Client.0x6FB1F5B0
void __fastcall sub_6FB1F5B0(int a1);
//D2Client.0x6FB1F680
uint32_t __cdecl sub_6FB1F680();
//D2Client.0x6FB1F6A0
void __fastcall sub_6FB1F6A0(uint32_t a1);

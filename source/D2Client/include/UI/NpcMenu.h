#pragma once

#include <D2Client.h>


#pragma pack(push, 1)
struct D2NpcTransactionPacketStrc
{
	uint8_t nHeader;						//0x00
	uint8_t unk0x01;						//0x01
	char nTransactionType;					//0x02
	uint8_t unk0x03[4];						//0x03
	uint32_t dwItemGUID;					//0x07
	uint8_t unk0x0B[4];						//0x0B
};
#pragma pack(pop)

//D2Client.0x6FB7A520
extern uint32_t dword_6FB7A520;
//D2Client.0x6FB7A5B8
extern int32_t dword_6FB7A5B8;
//D2Client.0x6FB7A5BC
extern int16_t word_6FB7A5BC;
//D2Client.0x6FB7ADD8
extern uint8_t byte_6FB7ADD8[2976];
//D2Client.0x6FB7B978
extern uint32_t dword_6FB7B978[4];
//D2Client.0x6FB7B989
extern uint8_t byte_6FB7B989;
//D2Client.0x6FB7B98A
extern uint8_t byte_6FB7B98A[2];
//D2Client.0x6FB7B98C
extern uint8_t byte_6FB7B98C;
//D2Client.0x6FB7B98D
extern uint8_t byte_6FB7B98D;
//D2Client.0x6FB7BD6C
extern int32_t dword_6FB7BD6C;
//D2Client.0x6FB7BD70
extern uint32_t dword_6FB7BD70;
//D2Client.0x6FB7BD74
extern uint32_t dword_6FB7BD74;
//D2Client.0x6FB7BD78
extern uint16_t word_6FB7BD78;
//D2Client.0x6FB7BD7A
extern uint8_t byte_6FB7BD7A[2];
//D2Client.0x6FB7BD7C
extern uint8_t byte_6FB7BD7C[2];
//D2Client.0x6FB7BD7E
extern uint8_t byte_6FB7BD7E[2];
//D2Client.0x6FB7BD80
extern uint8_t byte_6FB7BD80[2];
//D2Client.0x6FB7BD82
extern uint8_t* ptr_6FB7BD82;
//D2Client.0x6FB7BD86
extern uint8_t* ptr_6FB7BD86;
//D2Client.0x6FB7BD8A
extern uint8_t byte_6FB7BD8A[4];
//D2Client.0x6FB7BD8E
extern uint8_t byte_6FB7BD8E[4];
//D2Client.0x6FB7BD92
extern uint8_t byte_6FB7BD92[5];
//D2Client.0x6FB7BDE9
extern uint8_t byte_6FB7BDE9;
//D2Client.0x6FB7BDF1
extern uint8_t byte_6FB7BDF1;
//D2Client.0x6FB7BDFF
extern uint8_t byte_6FB7BDFF;
//D2Client.0x6FB7BF21
extern uint8_t byte_6FB7BF21;
//D2Client.0x6FB7BF27
extern uint8_t byte_6FB7BF27;
//D2Client.0x6FB7BF33
extern uint8_t byte_6FB7BF33;
//D2Client.0x6FB7BF6F
extern uint8_t byte_6FB7BF6F;
//D2Client.0x6FB7BF75
extern uint8_t byte_6FB7BF75;
//D2Client.0x6FB7BF81
extern uint8_t byte_6FB7BF81;
//D2Client.0x6FB7BFBD
extern uint8_t byte_6FB7BFBD;
//D2Client.0x6FB7BFC3
extern uint8_t byte_6FB7BFC3;
//D2Client.0x6FB7BFCF
extern uint8_t byte_6FB7BFCF;
//D2Client.0x6FB7BFE4
extern uint8_t byte_6FB7BFE4;
//D2Client.0x6FB7C00B
extern uint8_t byte_6FB7C00B;
//D2Client.0x6FB7C032
extern uint8_t byte_6FB7C032;
//D2Client.0x6FB7C059
extern uint8_t byte_6FB7C059;
//D2Client.0x6FB7C0A7
extern uint8_t byte_6FB7C0A7;
//D2Client.0x6FB7C0AD
extern uint8_t byte_6FB7C0AD;
//D2Client.0x6FB7C0B9
extern uint8_t byte_6FB7C0B9;
//D2Client.0x6FB7C33E
extern uint8_t byte_6FB7C33E;
//D2Client.0x6FB7C365
extern uint8_t byte_6FB7C365;
//D2Client.0x6FB7C36D
extern uint8_t byte_6FB7C36D;
//D2Client.0x6FB7C37B
extern uint8_t byte_6FB7C37B;
//D2Client.0x6FB7C3B3
extern uint8_t byte_6FB7C3B3;
//D2Client.0x6FB7C3BD
extern uint8_t byte_6FB7C3BD;
//D2Client.0x6FB7C3CD
extern uint8_t byte_6FB7C3CD;
//D2Client.0x6FB7C401
extern uint8_t byte_6FB7C401;
//D2Client.0x6FB7C407
extern uint8_t byte_6FB7C407;
//D2Client.0x6FB7C413
extern uint8_t* gpuint8_t_6FB7C413;
//D2Client.0x6FB7C4C0
extern int32_t dword_6FB7C4C0;
//D2Client.0x6FB7C4C8
extern uint16_t word_6FB7C4C8[4];
//D2Client.0x6FB7C4D4
extern int32_t dword_6FB7C4D4;
//D2Client.0x6FB7C828
extern uint8_t byte_6FB7C828;
//D2Client.0x6FB7CA28
extern uint8_t byte_6FB7CA28;
//D2Client.0x6FB7CC94
extern uint8_t* gpuint8_t_6FB7CC94;
//D2Client.0x6FB7CC98
extern uint16_t word_6FB7CC98;
//D2Client.0x6FB7CC9A
extern uint8_t byte_6FB7CC9A[4];
//D2Client.0x6FB7CC9E
extern uint32_t dword_6FB7CC9E;
//D2Client.0x6FB7CCA2
extern uint32_t dword_6FB7CCA2;
//D2Client.0x6FB7CCA6
extern uint32_t dword_6FB7CCA6;
//D2Client.0x6FB7CCAA
extern uint32_t dword_6FB7CCAA;
//D2Client.0x6FB7CCAE
extern uint32_t dword_6FB7CCAE;
//D2Client.0x6FB7CCE8
extern int32_t dword_6FB7CCE8;
//D2Client.0x6FB7CCEC
extern int32_t dword_6FB7CCEC;
//D2Client.0x6FB7CCF0
extern uint32_t tbl_6FB7CCF0[18];
//D2Client.0x6FB7CD38
extern uint32_t tbl_6FB7CD38[3];
//D2Client.0x6FB7CD44
extern uint32_t tbl_6FB7CD44[3];
//D2Client.0x6FB7CD50
extern uint8_t tbl_6FB7CD50[11];
//D2Client.0x6FB7CD5B
extern uint32_t dword_6FB7CD5B;
//D2Client.0x6FBA7990
extern int32_t dword_6FBA7990;
//D2Client.0x6FBB5BC8
extern int32_t dword_6FBB5BC8;
//D2Client.0x6FBB5BCC
extern D2CellFileStrc* gpCellFile_6FBB5BCC;
//D2Client.0x6FBB5BD0
extern char byte_6FBB5BD0;
//D2Client.0x6FBB5BD1
extern uint8_t byte_6FBB5BD1;
//D2Client.0x6FBB5BD5
extern uint32_t dword_6FBB5BD5;
//D2Client.0x6FBB5BD9
extern int32_t dword_6FBB5BD9;
//D2Client.0x6FBB5BDD
extern uint32_t dword_6FBB5BDD;
//D2Client.0x6FBB5BE1
extern uint8_t byte_6FBB5BE1;
//D2Client.0x6FBB5C38
extern uint8_t byte_6FBB5C38;
//D2Client.0x6FBB5C39
extern uint8_t byte_6FBB5C39;
//D2Client.0x6FBB5C3A
extern uint8_t byte_6FBB5C3A;
//D2Client.0x6FBB5C3B
extern uint8_t byte_6FBB5C3B;
//D2Client.0x6FBB5C43
extern uint8_t byte_6FBB5C43;
//D2Client.0x6FBB5C47
extern uint16_t word_6FBB5C47;
//D2Client.0x6FBB5C49
extern uint16_t word_6FBB5C49;
//D2Client.0x6FBB5C4B
extern uint16_t word_6FBB5C4B;
//D2Client.0x6FBB5C4D
extern int32_t dword_6FBB5C4D;
//D2Client.0x6FBB5C51
extern int32_t dword_6FBB5C51;
//D2Client.0x6FBB5C55
extern uint16_t word_6FBB5C55[4];
//D2Client.0x6FBB5C5D
extern uint32_t dword_6FBB5C5D[2];
//D2Client.0x6FBB5CF5
extern uint32_t dword_6FBB5CF5;
//D2Client.0x6FBB5CF9
extern int32_t dword_6FBB5CF9;
//D2Client.0x6FBB5CFC
extern uint8_t tbl_6FBB5CFC[1];
//D2Client.0x6FBB5CFD
extern int32_t dword_6FBB5CFD;
//D2Client.0x6FBB5D01
extern int32_t dword_6FBB5D01;
//D2Client.0x6FBB5D09
extern int32_t dword_6FBB5D09;
//D2Client.0x6FBB5D0D
extern uint8_t byte_6FBB5D0D;
//D2Client.0x6FBB5D0F
extern uint32_t dword_6FBB5D0F;
//D2Client.0x6FBB5D13
extern D2BitBufferStrc* gpBitBuffer_6FBB5D13;
//D2Client.0x6FBB5D17
extern D2BitBufferStrc* gpBitBuffer_6FBB5D17;
//D2Client.0x6FBB5D1B
extern uint8_t byte_6FBB5D1B;
//D2Client.0x6FBB5D1F
extern uint8_t byte_6FBB5D1F;
//D2Client.0x6FBB5D23
extern int32_t dword_6FBB5D23;
//D2Client.0x6FBB5D27
extern int32_t dword_6FBB5D27;
//D2Client.0x6FBB5D2B
extern uint32_t dword_6FBB5D2B;
//D2Client.0x6FBB5D2F
extern int32_t dword_6FBB5D2F;
//D2Client.0x6FBB5D33
extern int32_t dword_6FBB5D33;
//D2Client.0x6FBB5D37
extern int32_t dword_6FBB5D37;
//D2Client.0x6FBB5D3B
extern int32_t dword_6FBB5D3B;
//D2Client.0x6FBB5D3F
extern int32_t dword_6FBB5D3F;
//D2Client.0x6FBB5D43
extern int32_t dword_6FBB5D43;
//D2Client.0x6FBB5D47
extern int32_t dword_6FBB5D47;
//D2Client.0x6FBB5D4B
extern int32_t dword_6FBB5D4B;
//D2Client.0x6FBB5D4F
extern uint32_t* gpuint32_t_6FBB5D4F;
//D2Client.0x6FBB5D53
extern D2NpcTransactionPacketStrc gNpcTransactionPacket;
//D2Client.0x6FBB5D62
extern int32_t dword_6FBB5D62;
//D2Client.0x6FBB5D66
extern uint16_t word_6FBB5D66;
//D2Client.0x6FBB5D7A
extern uint16_t word_6FBB5D7A;
//D2Client.0x6FBB5D7C
extern int32_t dword_6FBB5D7C;
//D2Client.0x6FBB5D80
extern int32_t dword_6FBB5D80;
//D2Client.0x6FBB5D84
extern int32_t dword_6FBB5D84;
//D2Client.0x6FBB5D88
extern uint32_t dword_6FBB5D88;
//D2Client.0x6FBB5D8C
extern uint32_t dword_6FBB5D8C;
//D2Client.0x6FBB5D90
extern uint32_t dword_6FBB5D90;
//D2Client.0x6FBB5D94
extern uint32_t dword_6FBB5D94;
//D2Client.0x6FBB5D98
extern D2CellFileStrc* gpCellFile_6FBB5D98;
//D2Client.0x6FBB5D9C
extern uint32_t dword_6FBB5D9C;
//D2Client.0x6FBB5DA0
extern int32_t dword_6FBB5DA0;
//D2Client.0x6FBB5DA4
extern uint8_t byte_6FBB5DA4;
//D2Client.0x6FBB5DA8
extern uint8_t byte_6FBB5DA8;
//D2Client.0x6FBB5DAC
extern char byte_6FBB5DAC;
//D2Client.0x6FBB5DB0
extern int32_t dword_6FBB5DB0;
//D2Client.0x6FBB5DB4
extern int32_t dword_6FBB5DB4;
//D2Client.0x6FBB5DB8
extern int32_t dword_6FBB5DB8;
//D2Client.0x6FBB5DBC
extern int32_t dword_6FBB5DBC;
//D2Client.0x6FBB5DC0
extern uint32_t dword_6FBB5DC0;
//D2Client.0x6FBB5DC4
extern int32_t dword_6FBB5DC4;
//D2Client.0x6FBB5DC8
extern uint32_t dword_6FBB5DC8;
//D2Client.0x6FBB5DCC
extern int32_t dword_6FBB5DCC;
//D2Client.0x6FBB5DD0
extern int32_t dword_6FBB5DD0;
//D2Client.0x6FBB5DD4
extern uint8_t byte_6FBB5DD4;
//D2Client.0x6FBB5DD8
extern uint32_t dword_6FBB5DD8;
//D2Client.0x6FBB5DDC
extern uint8_t byte_6FBB5DDC;
//D2Client.0x6FBB5DE0
extern int32_t dword_6FBB5DE0;
//D2Client.0x6FBB5DE4
extern uint32_t dword_6FBB5DE4;
//D2Client.0x6FBB5DE8
extern int32_t dword_6FBB5DE8;
//D2Client.0x6FBB5DEC
extern int32_t dword_6FBB5DEC;
//D2Client.0x6FBB5DF0
extern int32_t dword_6FBB5DF0;
//D2Client.0x6FBB5DF4
extern int32_t dword_6FBB5DF4;
//D2Client.0x6FBB5DF8
extern uint32_t dword_6FBB5DF8;
//D2Client.0x6FBB5DFC
extern D2CellFileStrc* gpCellFile_6FBB5DFC;
//D2Client.0x6FBB5E00
extern DWORD dword_6FBB5E00;
//D2Client.0x6FBB5E04
extern uint8_t byte_6FBB5E04;
//D2Client.0x6FBB5E08
extern DWORD dword_6FBB5E08;
//D2Client.0x6FBB5E0C
extern int32_t dword_6FBB5E0C;
//D2Client.0x6FBB5E10
extern int32_t dword_6FBB5E10;
//D2Client.0x6FBB5E14
extern int32_t dword_6FBB5E14;
//D2Client.0x6FBB5E18
extern D2CellFileStrc* gpCellFile_6FBB5E18;
//D2Client.0x6FBB5E1C
extern D2CellFileStrc* gpCellFile_6FBB5E1C;
//D2Client.0x6FBB5E20
extern D2CellFileStrc* gpCellFile_6FBB5E20;
//D2Client.0x6FBB5E24
extern D2CellFileStrc* gpCellFile_6FBB5E24;
//D2Client.0x6FBB5E28
extern D2CellFileStrc* gpCellFile_6FBB5E28;
//D2Client.0x6FBB5E2C
extern D2CellFileStrc* gpCellFile_6FBB5E2C;
//D2Client.0x6FBB5E30
extern D2CellFileStrc* gpCellFile_6FBB5E30;
//D2Client.0x6FBB5E34
extern D2CellFileStrc* gpCellFile_6FBB5E34;
//D2Client.0x6FBB5E3C
extern D2CellFileStrc* gpCellFile_6FBB5E3C;
//D2Client.0x6FBB5E40
extern D2CellFileStrc* gpCellFile_6FBB5E40;
//D2Client.0x6FBB5E44
extern D2CellFileStrc* gpCellFile_6FBB5E44;
//D2Client.0x6FBB5E48
extern D2CellFileStrc* gpCellFile_6FBB5E48;
//D2Client.0x6FBB5E4C
extern D2CellFileStrc* gpCellFile_6FBB5E4C;
//D2Client.0x6FBB5E50
extern D2CellFileStrc* gpCellFile_6FBB5E50;
//D2Client.0x6FBB5E54
extern D2CellFileStrc* gpCellFile_6FBB5E54;
//D2Client.0x6FBB5E58
extern D2CellFileStrc* gpCellFile_6FBB5E58;
//D2Client.0x6FBB5E5C
extern uint32_t dword_6FBB5E5C;
//D2Client.0x6FBB5E8C
extern D2CellFileStrc* gpCellFile_6FBB5E8C;

//D2Client.0x6FAF3DF0
void __cdecl sub_6FAF3DF0(int a1);
//D2Client.0x6FAF4110
uint32_t __cdecl sub_6FAF4110();
//D2Client.0x6FAF4160
uint32_t __cdecl sub_6FAF4160();
//D2Client.0x6FAF4300
uint32_t __cdecl sub_6FAF4300();
//D2Client.0x6FAF44C0
uint32_t __fastcall sub_6FAF44C0(int a1);
//D2Client.0x6FAF45E0
uint32_t __cdecl sub_6FAF45E0(uint32_t a1);
//D2Client.0x6FAF4760
uint32_t __cdecl sub_6FAF4760();
//D2Client.0x6FAF4A40
void __cdecl sub_6FAF4A40();
//D2Client.0x6FAF4A70
void __fastcall sub_6FAF4A70(int a1, char a2);
//D2Client.0x6FAF4C30
uint32_t __cdecl sub_6FAF4C30();
//D2Client.0x6FAF4D30
uint32_t __cdecl sub_6FAF4D30();
//D2Client.0x6FAF4DB0
uint32_t __cdecl sub_6FAF4DB0();
//D2Client.0x6FAF4E30
uint32_t __cdecl sub_6FAF4E30();
//D2Client.0x6FAF55B0
uint32_t __cdecl sub_6FAF55B0();
//D2Client.0x6FAF55F0
uint32_t __cdecl sub_6FAF55F0();
//D2Client.0x6FAF56D0
void __cdecl sub_6FAF56D0();
//D2Client.0x6FAF5880
void __fastcall sub_6FAF5880(uint32_t* a1);
//D2Client.0x6FAF5B80
uint32_t __cdecl sub_6FAF5B80();
//D2Client.0x6FAF5D20
uint32_t __cdecl sub_6FAF5D20();
//D2Client.0x6FAF5EB0
uint32_t __cdecl sub_6FAF5EB0();
//D2Client.0x6FAF6070
void __cdecl sub_6FAF6070();
//D2Client.0x6FAF6340
void __cdecl sub_6FAF6340();
//D2Client.0x6FAF63E0
uint32_t __cdecl sub_6FAF63E0();
//D2Client.0x6FAF6410
uint32_t __cdecl sub_6FAF6410();
//D2Client.0x6FAF6440
uint32_t __cdecl sub_6FAF6440();
//D2Client.0x6FAF6470
uint32_t __cdecl sub_6FAF6470();
//D2Client.0x6FAF64A0
uint32_t __cdecl sub_6FAF64A0();
//D2Client.0x6FAF6500
uint32_t __cdecl sub_6FAF6500();
//D2Client.0x6FAF6530
uint32_t __cdecl sub_6FAF6530();
//D2Client.0x6FAF6560
uint32_t __cdecl sub_6FAF6560();
//D2Client.0x6FAF6590
uint32_t __cdecl sub_6FAF6590();
//D2Client.0x6FAF65C0
void __cdecl sub_6FAF65C0();
//D2Client.0x6FAF6BC0
uint32_t __cdecl sub_6FAF6BC0();
//D2Client.0x6FAF6D50
uint32_t __cdecl sub_6FAF6D50();
//D2Client.0x6FAF6EE0
uint32_t __cdecl sub_6FAF6EE0();
//D2Client.0x6FAF70A0
void __fastcall sub_6FAF70A0(uint32_t a1);
//D2Client.0x6FAF70C0
uint32_t __cdecl sub_6FAF70C0();
//D2Client.0x6FAF7260
uint32_t __cdecl sub_6FAF7260();
//D2Client.0x6FAF7400
uint32_t __cdecl sub_6FAF7400();
//D2Client.0x6FAF75A0
uint32_t __cdecl sub_6FAF75A0();
//D2Client.0x6FAF7740
uint32_t __cdecl sub_6FAF7740();
//D2Client.0x6FAF78E0
void __fastcall sub_6FAF78E0(int a1);
//D2Client.0x6FAF7950
void __fastcall sub_6FAF7950(uint32_t a1);
//D2Client.0x6FAF7A00
void __cdecl sub_6FAF7A00();
//D2Client.0x6FAF7A60
void __cdecl sub_6FAF7A60();
//D2Client.0x6FAF7BD0
void __cdecl sub_6FAF7BD0();
//D2Client.0x6FAF7C90
void __cdecl sub_6FAF7C90();
//D2Client.0x6FAF7D90
void __fastcall sub_6FAF7D90(D2UnitStrc* pUnit);
//D2Client.0x6FAF7F40
void __fastcall sub_6FAF7F40(int ptCmd);
//D2Client.0x6FAF7FE0
void __fastcall sub_6FAF7FE0(uint8_t* a1);
//D2Client.0x6FAF8000
void __fastcall sub_6FAF8000(uint8_t a1, uint32_t a2);
//D2Client.0x6FAF8250
void __fastcall sub_6FAF8250(uint8_t a1, uint32_t a2, uint8_t* a3, uint32_t a4);
//D2Client.0x6FAF8940
int __fastcall sub_6FAF8940(short a1);
//D2Client.0x6FAF8970
uint8_t __fastcall sub_6FAF8970(int a1);
//D2Client.0x6FAF89E0
uint32_t __cdecl sub_6FAF89E0(int a1);
//D2Client.0x6FAF8E40
int __cdecl sub_6FAF8E40();
//D2Client.0x6FAF8E80
uint32_t __cdecl sub_6FAF8E80();
//D2Client.0x6FAF9010
void __fastcall sub_6FAF9010(int a1);
//D2Client.0x6FAF9040
void __fastcall sub_6FAF9040(int a1);
//D2Client.0x6FAF9070
void __fastcall sub_6FAF9070(int a1);
//D2Client.0x6FAF90A0
void __fastcall sub_6FAF90A0(int a1);
//D2Client.0x6FAF90D0
void __cdecl sub_6FAF90D0();
//D2Client.0x6FAF93D0
uint32_t __cdecl sub_6FAF93D0();
//D2Client.0x6FAF9570
uint32_t __cdecl sub_6FAF9570();
//D2Client.0x6FAF9710
uint32_t __cdecl sub_6FAF9710();
//D2Client.0x6FAF98D0
void __fastcall sub_6FAF98D0(D2UnitStrc* pUnit, int a2);
//D2Client.0x6FAF9CB0
uint32_t __fastcall sub_6FAF9CB0(int a1, int a2);
//D2Client.0x6FAF9E60
void __cdecl sub_6FAF9E60();
//D2Client.0x6FAF9FE0
void __cdecl sub_6FAF9FE0();
//D2Client.0x6FAFA230
int32_t __fastcall sub_6FAFA230(int a1, uint32_t a2, int a3);
//D2Client.0x6FAFA260
uint32_t __fastcall sub_6FAFA260(D2UnitStrc* pUnit2, D2UnitStrc* pUnit3, int a3, uint32_t a4, uint32_t a5, uint32_t a6, int a7, int a8);
//D2Client.0x6FAFA6E0
void __fastcall sub_6FAFA6E0(int a1, uint32_t a2);
//D2Client.0x6FAFAAA0
void __fastcall sub_6FAFAAA0(int a1);
//D2Client.0x6FAFAB80
void __fastcall sub_6FAFAB80(int a1);
//D2Client.0x6FAFAC60
void __fastcall sub_6FAFAC60(int a1);
//D2Client.0x6FAFAD40
void __fastcall sub_6FAFAD40(int a1);
//D2Client.0x6FAFAE20
void __fastcall sub_6FAFAE20(int a1);
//D2Client.0x6FAFAF00
void __fastcall sub_6FAFAF00(int a1);
//D2Client.0x6FAFAFE0
void __fastcall sub_6FAFAFE0(uint32_t a1);
//D2Client.0x6FAFB030
void __cdecl sub_6FAFB030();
//D2Client.0x6FAFB200
uint32_t __fastcall sub_6FAFB200(D2UnitStrc* pUnit, int a2, int* a3, Unicode* pUnicode, int a5);
//D2Client.0x6FAFB6D0
bool __cdecl sub_6FAFB6D0();
//D2Client.0x6FAFB6E0
void __fastcall sub_6FAFB6E0(int* a1, uint16_t a2, int a3);
//D2Client.0x6FAFB710
void __cdecl sub_6FAFB710();
//D2Client.0x6FAFBA30
uint32_t __cdecl sub_6FAFBA30();
//D2Client.0x6FAFBAC0
uint32_t __cdecl sub_6FAFBAC0();
//D2Client.0x6FAFBB10
void __fastcall sub_6FAFBB10(int* a1);
//D2Client.0x6FAFBB50
int __fastcall sub_6FAFBB50(uint32_t* a1);
//D2Client.0x6FAFBB60
void __fastcall sub_6FAFBB60(uint32_t a1);
//D2Client.0x6FAFBCC0
void __fastcall sub_6FAFBCC0(int a1);
//D2Client.0x6FAFBD00
void __cdecl sub_6FAFBD00();
//D2Client.0x6FAFBD20
D2BitBufferStrc* __cdecl sub_6FAFBD20();
//D2Client.0x6FAFBD30
D2BitBufferStrc* __cdecl sub_6FAFBD30();
//D2Client.0x6FAFBD40
void __cdecl sub_6FAFBD40();
//D2Client.0x6FAFBE30
void __fastcall sub_6FAFBE30(short a1);
//D2Client.0x6FAFBE50
void __cdecl sub_6FAFBE50();
//D2Client.0x6FAFBE70
void __fastcall sub_6FAFBE70(int a1);
//D2Client.0x6FAFBF80
void __fastcall sub_6FAFBF80(uint32_t a1);
//D2Client.0x6FAFC0B0
uint32_t __cdecl sub_6FAFC0B0();
//D2Client.0x6FAFC0E0
uint32_t __cdecl sub_6FAFC0E0();
//D2Client.0x6FAFC130
int __cdecl sub_6FAFC130();
//D2Client.0x6FAFC140
void __fastcall sub_6FAFC140(int a1);
//D2Client.0x6FAFC190
void __fastcall sub_6FAFC190(short a1, uint32_t a2);
//D2Client.0x6FAFC1F0
void __cdecl sub_6FAFC1F0();
//D2Client.0x6FAFC240
void __cdecl sub_6FAFC240();
//D2Client.0x6FAFC260
void __cdecl sub_6FAFC260();
//D2Client.0x6FAFC270
void __cdecl sub_6FAFC270();
//D2Client.0x6FAFC290
void __cdecl sub_6FAFC290();
//D2Client.0x6FAFC2C0
void __cdecl sub_6FAFC2C0();
//D2Client.0x6FAFC310
void __cdecl sub_6FAFC310();
//D2Client.0x6FAFC3F0
void __cdecl sub_6FAFC3F0();
//D2Client.0x6FAFC4C0
void __fastcall sub_6FAFC4C0(int a1);
//D2Client.0x6FAFC590
void __cdecl sub_6FAFC590();
//D2Client.0x6FAFC5B0
void __fastcall sub_6FAFC5B0(int a1);
//D2Client.0x6FAFC620
void __cdecl sub_6FAFC620();
//D2Client.0x6FAFCE10
void __fastcall sub_6FAFCE10(int a1, int a2);
//D2Client.0x6FAFD470
void __fastcall sub_6FAFD470(int a1);
//D2Client.0x6FAFD520
int __fastcall sub_6FAFD520(int a1, int a2);
//D2Client.0x6FAFD550
void __cdecl sub_6FAFD550(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD5A0
void __cdecl sub_6FAFD5A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD7E0
int __fastcall sub_6FAFD7E0(int a1);
//D2Client.0x6FAFD830
void __cdecl sub_6FAFD830(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD8A0
void __cdecl sub_6FAFD8A0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD910
void __cdecl sub_6FAFD910(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD980
void __cdecl sub_6FAFD980(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFD9E0
void __cdecl sub_6FAFD9E0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDA40
void __cdecl sub_6FAFDA40(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDB50
void __cdecl sub_6FAFDB50(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDBD0
void __cdecl sub_6FAFDBD0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDC60
void __cdecl sub_6FAFDC60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDD30
void __cdecl sub_6FAFDD30(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFDF10
void __cdecl sub_6FAFDF10(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFE040
void __cdecl sub_6FAFE040(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS);
//D2Client.0x6FAFE140
void __cdecl sub_6FAFE140(int a1);
//D2Client.0x6FAFE250
void __cdecl sub_6FAFE250(int a1);
//D2Client.0x6FAFE370
void __cdecl sub_6FAFE370();
//D2Client.0x6FAFE4D0
void __cdecl sub_6FAFE4D0();
//D2Client.0x6FAFE650
void __cdecl sub_6FAFE650();

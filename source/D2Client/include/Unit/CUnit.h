#pragma once

#include <D2Client.h>

//D2Client.0x6FB70148
extern uint32_t dword_6FB70148;
//D2Client.0x6FB908FC
extern uint32_t dword_6FB908FC;
//D2Client.0x6FB90900
extern uint8_t byte_6FB90900[28];
//D2Client.0x6FB9091C
extern int32_t dword_6FB9091C;
//D2Client.0x6FBBAA00
extern uint32_t dword_6FBBAA00;
//D2Client.0x6FBBAC00
extern uint32_t dword_6FBBAC00;
//D2Client.0x6FBBAE00
extern uint32_t dword_6FBBAE00;
//D2Client.0x6FBBB000
extern uint32_t dword_6FBBB000;
//D2Client.0x6FBBB200
extern uint32_t dword_6FBBB200;
//D2Client.0x6FBBB400
extern uint32_t tbl_6FBBB400[128];
//D2Client.0x6FBBB600
extern uint32_t dword_6FBBB600;
//D2Client.0x6FBBB800
extern uint32_t dword_6FBBB800;
//D2Client.0x6FBBBA00
extern uint32_t dword_6FBBBA00;
//D2Client.0x6FBBBC00
extern uint32_t dword_6FBBBC00;
//D2Client.0x6FBBBE00
extern uint32_t tbl_6FBBBE00[256];
//D2Client.0x6FBBC200
extern D2UnitStrc* gpUnit_6FBBC200;
//D2Client.0x6FBBC204
extern int32_t dword_6FBBC204;

//D2Client.0x6FB269F0
D2UnitStrc* __fastcall sub_6FB269F0(uint32_t a1, int a2);
//D2Client.0x6FB26A60
D2UnitStrc* __fastcall sub_6FB26A60(uint32_t a1, int a2);
//D2Client.0x6FB26AD0
D2UnitStrc* __fastcall sub_6FB26AD0(int ptUnit);
//D2Client.0x6FB26BE0
int32_t __fastcall sub_6FB26BE0(uint32_t a1, uint32_t a2);
//D2Client.0x6FB26C00
int32_t __fastcall sub_6FB26C00(int a1, int a2, uint32_t a3, uint32_t a4);
//D2Client.0x6FB26C70
int32_t __fastcall sub_6FB26C70(uint32_t a1, uint32_t a2);
//D2Client.0x6FB26C90
D2ActiveRoomStrc* __fastcall sub_6FB26C90(int a1, int a2);
//D2Client.0x6FB26DD0
void __fastcall sub_6FB26DD0(D2UnitStrc* pUnit, char* a2, char* a3, int a4);
//D2Client.0x6FB27040
D2UnitStrc* __fastcall sub_6FB27040(uint32_t a1, uint32_t a2, float a3, int a4, uint32_t a5, int a6);
//D2Client.0x6FB27080
D2UnitStrc* __fastcall sub_6FB27080(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, float a4, int a5, uint32_t a6, int a7, uint32_t a8);
//D2Client.0x6FB27280
D2UnitStrc* __fastcall sub_6FB27280(D2UnitStrc* pUnit);
//D2Client.0x6FB27320
D2UnitStrc* __fastcall sub_6FB27320(int a1, int a2, int a3, int a4);
//D2Client.0x6FB27390
uint32_t __fastcall sub_6FB27390(D2UnitStrc* pUnit);
//D2Client.0x6FB27570
uint32_t* __fastcall sub_6FB27570(uint32_t a1, uint32_t a2, float a3, int a4, char* a5);
//D2Client.0x6FB275C0
uint32_t* __fastcall sub_6FB275C0(uint32_t a1, uint32_t a2, float a3, int a4, uint32_t a5, int a6, uint32_t a7, uint32_t a8);
//D2Client.0x6FB27630
D2UnitStrc* __fastcall sub_6FB27630(void* a1, uint32_t* a2, int a3, uint32_t a4, uint32_t a5, int a6);
//D2Client.0x6FB27D50
D2UnitStrc* __fastcall sub_6FB27D50(uint32_t a1, float a2, int a3, uint32_t a4, int a5);
//D2Client.0x6FB27E10
void __fastcall sub_6FB27E10(D2UnitStrc* pUnit, char a2, char a3);
//D2Client.0x6FB27E70
void __fastcall sub_6FB27E70(D2ActiveRoomStrc* pActiveRoom);
//D2Client.0x6FB27ED0
void __fastcall sub_6FB27ED0(D2UnitStrc* pUnit);
//D2Client.0x6FB28020
void __cdecl sub_6FB28020();
//D2Client.0x6FB28040
void __cdecl sub_6FB28040();
//D2Client.0x6FB280F0
void __cdecl sub_6FB280F0();
//D2Client.0x6FB28350
void __fastcall sub_6FB28350(int a1, uint8_t* a2);
//D2Client.0x6FB28380
void __cdecl sub_6FB28380();
//D2Client.0x6FB28390
void __fastcall sub_6FB28390(D2UnitStrc* pUnit);
//D2Client.0x6FB283D0
D2UnitStrc* __fastcall CUNIT_GetPlayer();
//D2Client.0x6FB283E0
bool __cdecl sub_6FB283E0();
//D2Client.0x6FB28400
uint32_t __fastcall sub_6FB28400(int a1);
//D2Client.0x6FB28410
void __fastcall sub_6FB28410(int hUnit, uint32_t a2);
//D2Client.0x6FB28440
int32_t __fastcall sub_6FB28440(int hUnit);
//D2Client.0x6FB28470
void __fastcall sub_6FB28470(int hUnit, uint32_t a2);
//D2Client.0x6FB284A0
int32_t __fastcall sub_6FB284A0(int hUnit);
//D2Client.0x6FB284D0
uint32_t __fastcall sub_6FB284D0(D2UnitStrc* pUnit, int a2, int a3);
//D2Client.0x6FB285D0
void __fastcall sub_6FB285D0(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB285E0
void __fastcall sub_6FB285E0(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB285F0
uint32_t __fastcall sub_6FB285F0(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB28680
void __fastcall sub_6FB28680(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB28690
void __fastcall sub_6FB28690(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB286A0
void __fastcall sub_6FB286A0(uint32_t a1, D2UnitStrc* pUnit);
//D2Client.0x6FB286B0
bool __fastcall sub_6FB286B0(D2UnitStrc* pUnit);
//D2Client.0x6FB286F0
uint32_t __fastcall sub_6FB286F0(D2UnitStrc* pUnit2, uint32_t a2, int a3, int a4);
//D2Client.0x6FB28D90
uint32_t __fastcall sub_6FB28D90(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3, D2CellFileStrc* pCellFile, int* a5, uint32_t a6);
//D2Client.0x6FB28F20
uint32_t __cdecl sub_6FB28F20(int a1);
//D2Client.0x6FB28F90
void __fastcall sub_6FB28F90(D2UnitStrc* pUnit, int a2, uint32_t a3);
//D2Client.0x6FB29010
void __fastcall sub_6FB29010(D2UnitStrc* pUnit, int a2);
//D2Client.0x6FB29100
void __fastcall sub_6FB29100(D2UnitStrc* pUnit);
//D2Client.0x6FB291C0
void __fastcall sub_6FB291C0(int* a1);
//D2Client.0x6FB29290
bool __fastcall sub_6FB29290(D2UnitStrc* pUnit);
//D2Client.0x6FB29370
D2ActiveRoomStrc* __fastcall CUNIT_GetPlayerRoom();
//D2Client.0x6FB29390
void __cdecl sub_6FB29390();
//D2Client.0x6FB29450
uint32_t __fastcall sub_6FB29450(int ptUnit);
//D2Client.0x6FB29480
void __fastcall sub_6FB29480(int ptUnit, uint32_t a2);
//D2Client.0x6FB294B0
void __fastcall sub_6FB294B0(int* a1);
//D2Client.0x6FB29540
void __fastcall sub_6FB29540(int a1);
//D2Client.0x6FB29550
uint32_t __fastcall sub_6FB29550(int* a1);
//D2Client.0x6FB29590
bool __fastcall sub_6FB29590(uint32_t* a1);
//D2Client.0x6FB296A0
D2UnitStrc* __fastcall sub_6FB296A0(int a1);
//D2Client.0x6FB296E0
int32_t __fastcall sub_6FB296E0(int a1);
//D2Client.0x6FB29700
void __fastcall sub_6FB29700(uint8_t* a1);
//D2Client.0x6FB29750
void __fastcall sub_6FB29750(uint8_t* a1);
//D2Client.0x6FB297A0
void __fastcall sub_6FB297A0(uint8_t* a1);
//D2Client.0x6FB297F0
Unicode* __fastcall sub_6FB297F0(D2UnitStrc* ptUnit);
//D2Client.0x6FB29A40
uint32_t __fastcall sub_6FB29A40(D2UnitStrc* ptUnit);
//D2Client.0x6FB29A80
void __fastcall sub_6FB29A80(int ptUnit);
//D2Client.0x6FB29AB0
void __fastcall sub_6FB29AB0(int ptUnit, uint32_t a2);
//D2Client.0x6FB29AE0
void __fastcall sub_6FB29AE0(D2UnitStrc* hUnit, int a2);
//D2Client.0x6FB29D10
void __fastcall sub_6FB29D10(D2UnitStrc* pUnit, int a2, uint32_t a3);
//D2Client.0x6FB29D80
uint32_t __fastcall sub_6FB29D80(D2UnitStrc* pUnit, D2UnitStrc* pUnit2);
//D2Client.0x6FB2A0C0
bool __fastcall sub_6FB2A0C0(D2UnitStrc* pUnit, int* a2);
//D2Client.0x6FB2A1C0
bool __fastcall sub_6FB2A1C0(D2UnitStrc* pUnit, int* a2);
//D2Client.0x6FB2A2D0
void __cdecl sub_6FB2A2D0();
//D2Client.0x6FB2A6E0
uint16_t __fastcall sub_6FB2A6E0(int* a1);

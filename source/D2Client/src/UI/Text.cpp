#include "UI/Text.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DFloor.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Game/View.h"
#include "Sound/SoundHdr.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/CmdTbl.h"
#include "UI/Dialog.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/Trade.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/MonUnique.h"
#include "Unit/PlayerList.h"
#include "Unit/UnitSnd.h"

//D2Client.0x6FB8DB48
uint32_t unk_6FB8DB48[74] = { 0x42D0B89, 0x42E0B8A, 0x4300B79, 0x42F0B7A, 0x4310B7B, 0x4320B7C, 0x4330B7D, 0x4340B7E, 0x4360B7F, 0x4350B80, 0x4380B81, 0x4370B82, 0x43A0B83, 0x4390B84, 0x43B0B85, 0x43C0B86, 0x43D0B8D, 0x43E0B8E, 0x43F0B78, 0x4410B76, 0x4400B77, 0x4430B8F, 0x4420B90, 0x4460B8B, 0x4450B8C, 0x4470B9F, 0x44C0B99, 0x4510B96, 0x4560B9B, 0x45B0B9C, 0x4600B9A, 0x46A0B98, 0x46F0B93, 0x4740B92, 0x4790B9D, 0x47E0B97, 0x4830B9E, 0x4880BA0, 0x48D0B94, 0x4920B95, 0x4970B91, 0x49C0BA9, 0x4A10BA2, 0x4A60BA1, 0x4AB0BA8, 0x4B00BA4, 0x4B50BA7, 0x4BA0BAA, 0x4BF0BA3, 0x4C40BAB, 0x4C90BAC, 0x4CE0BA6, 0x4D40BB9, 0x4D90BB3, 0x4DE0BB4, 0x4E30BB6, 0x4E80BAF, 0x4ED0BB1, 0x4F20BB8, 0x4F70BB5, 0x4FC0BB0, 0x5010BB7, 0x5060BB2, 0x50B0BBA, 0x2AA40B87, 0x55860B88, 0x55E20BBC, 0x55F70BBD, 0x56050BBE, 0x560C0BBF, 0x55E90BC0, 0x55F00BC1, 0x55FE0BC2, 0x56130BC3 };
//D2Client.0x6FB8DC70
uint32_t unk_6FB8DC70[74] = { 0x42D0CC1, 0x42E0CC2, 0x4300CB1, 0x42F0CB2, 0x4310CB3, 0x4320CB4, 0x4330CB5, 0x4340CB6, 0x4360CB7, 0x4350CB8, 0x4380CB9, 0x4370CBA, 0x43A0CBB, 0x4390CBC, 0x43B0CBD, 0x43C0CBE, 0x43D0CC5, 0x43E0CC6, 0x43F0CB0, 0x4410CAE, 0x4400CAF, 0x4430CC7, 0x4420CC8, 0x4460CC3, 0x4450CC4, 0x44A0CD7, 0x44F0CD1, 0x4540CCE, 0x4590CD3, 0x45E0CD4, 0x4630CD2, 0x46D0CD0, 0x4720CCB, 0x4770CCA, 0x47C0CD5, 0x4810CCF, 0x4860CD6, 0x48B0CD8, 0x4900CCC, 0x4950CCD, 0x49A0CC9, 0x49F0CE1, 0x4A40CDA, 0x4A90CD9, 0x4AE0CE0, 0x4B30CDC, 0x4B80CDF, 0x4BD0CE2, 0x4C20CDB, 0x4C70CE3, 0x4CC0CE4, 0x4D10CDE, 0x4D70CF1, 0x4DC0CEB, 0x4E10CEC, 0x4E60CEE, 0x4EB0CE7, 0x4F00CE9, 0x4F50CF0, 0x4FA0CED, 0x4FF0CE8, 0x5040CEF, 0x5090CEA, 0x50E0CF2, 0x2AA40CBF, 0x55860CC0, 0x55DE0CF4, 0x55F30CF5, 0x56010CF6, 0x56080CF7, 0x55E50CF8, 0x55EC0CF9, 0x55FA0CFA, 0x560F0CFB };
//D2Client.0x6FB8DD98
uint32_t unk_6FB8DD98[74] = { 0x42D0C25, 0x42E0C26, 0x4300C15, 0x42F0C16, 0x4310C17, 0x4320C18, 0x4330C19, 0x4340C1A, 0x4360C1B, 0x4350C1C, 0x4380C1D, 0x4370C1E, 0x43A0C1F, 0x4390C20, 0x43B0C21, 0x43C0C22, 0x43D0C29, 0x43E0C2A, 0x43F0C14, 0x4410C12, 0x4400C13, 0x4430C2B, 0x4420C2C, 0x4460C27, 0x4450C28, 0x44B0C3B, 0x4500C35, 0x4550C32, 0x45A0C37, 0x45F0C38, 0x4640C36, 0x46E0C34, 0x4730C2F, 0x4780C2E, 0x47D0C39, 0x4820C33, 0x4870C3A, 0x48C0C3C, 0x4910C30, 0x4960C31, 0x49B0C2D, 0x4A00C45, 0x4A50C3E, 0x4AA0C3D, 0x4AF0C44, 0x4B40C40, 0x4B90C43, 0x4BE0C46, 0x4C30C3F, 0x4C80C47, 0x4CD0C48, 0x4D20C42, 0x4D80C55, 0x4DD0C4F, 0x4E20C50, 0x4E70C52, 0x4EC0C4B, 0x4F10C4D, 0x4F60C54, 0x4FB0C51, 0x5000C4C, 0x5050C53, 0x50A0C4E, 0x50F0C56, 0x2AA40C23, 0x55860C24, 0x55E00C58, 0x55F50C59, 0x56030C5A, 0x560A0C5B, 0x55E70C5C, 0x55EE0C5D, 0x55FC0C5E, 0x56110C5F };
//D2Client.0x6FB8DEC0
uint32_t unk_6FB8DEC0[74] = { 0x42D0C73, 0x42E0C74, 0x4300C63, 0x42F0C64, 0x4310C65, 0x4320C66, 0x4330C67, 0x4340C68, 0x4360C69, 0x4350C6A, 0x4380C6B, 0x4370C6C, 0x43A0C6D, 0x4390C6E, 0x43B0C6F, 0x43C0C70, 0x43D0C77, 0x43E0C78, 0x43F0C62, 0x4410C60, 0x4400C61, 0x4430C79, 0x4420C7A, 0x4460C75, 0x4450C76, 0x4490C89, 0x44E0C83, 0x4530C80, 0x4580C85, 0x45D0C86, 0x4620C84, 0x46C0C82, 0x4710C7D, 0x4760C7C, 0x47B0C87, 0x4800C81, 0x4850C88, 0x48A0C8A, 0x48F0C7E, 0x4940C7F, 0x4990C7B, 0x49E0C93, 0x4A30C8C, 0x4A80C8B, 0x4AD0C92, 0x4B20C8E, 0x4B70C91, 0x4BC0C94, 0x4C10C8D, 0x4C60C95, 0x4CB0C96, 0x4D00C90, 0x4D60CA3, 0x4DB0C9D, 0x4E00C9E, 0x4E50CA0, 0x4EA0C99, 0x4EF0C9B, 0x4F40CA2, 0x4F90C9F, 0x4FE0C9A, 0x5030CA1, 0x5080C9C, 0x50D0CA4, 0x2AA40C71, 0x55860C72, 0x55E10CA6, 0x55F60CA7, 0x56040CA8, 0x560B0CA9, 0x55E80CAA, 0x55EF0CAB, 0x55FD0CAC, 0x56120CAD };
//D2Client.0x6FB8DFE8
uint32_t unk_6FB8DFE8[74] = { 0x42D0BD7, 0x42E0BD8, 0x4300BC7, 0x42F0BC8, 0x4310BC9, 0x4320BCA, 0x4330BCB, 0x4340BCC, 0x4360BCD, 0x4350BCE, 0x4380BCF, 0x4370BD0, 0x43A0BD1, 0x4390BD2, 0x43B0BD3, 0x43C0BD4, 0x43D0BDB, 0x43E0BDC, 0x43F0BC6, 0x4410BC4, 0x4400BC5, 0x4430BDD, 0x4420BDE, 0x4460BD9, 0x4450BDA, 0x4480BED, 0x44D0BE7, 0x4520BE4, 0x4570BE9, 0x45C0BEA, 0x4610BE8, 0x46B0BE6, 0x4700BE1, 0x4750BE0, 0x47A0BEB, 0x47F0BE5, 0x4840BEC, 0x4890BEE, 0x48E0BE2, 0x4930BE3, 0x4980BDF, 0x49D0BF7, 0x4A20BF0, 0x4A70BEF, 0x4AC0BF6, 0x4B10BF2, 0x4B60BF5, 0x4BB0BF8, 0x4C00BF1, 0x4C50BF9, 0x4CA0BFA, 0x4CF0BF4, 0x4D50C07, 0x4DA0C01, 0x4DF0C02, 0x4E40C04, 0x4E90BFD, 0x4EE0BFF, 0x4F30C06, 0x4F80C03, 0x4FD0BFE, 0x5020C05, 0x5070C00, 0x50C0C08, 0x2AA40BD5, 0x55860BD6, 0x55DF0C0A, 0x55F40C0B, 0x56020C0C, 0x56090C0D, 0x55E60C0E, 0x55ED0C0F, 0x55FB0C10, 0x56100C11 };
//D2Client.0x6FB8E110
uint32_t unk_6FB8E110[74] = { 0x42D0D5D, 0x42E0D5E, 0x4300D4D, 0x42F0D4E, 0x4310D4F, 0x4320D50, 0x4330D51, 0x4340D52, 0x4360D53, 0x4350D54, 0x4380D55, 0x4370D56, 0x43A0D57, 0x4390D58, 0x43B0D59, 0x43C0D5A, 0x43D0D61, 0x43E0D62, 0x43F0D4C, 0x4410D4A, 0x4400D4B, 0x4430D63, 0x4420D64, 0x4460D5F, 0x4450D60, 0x55870D73, 0x558A0D6D, 0x558C0D6A, 0x558E0D6F, 0x55900D70, 0x55920D6E, 0x55940D6C, 0x55960D67, 0x55980D66, 0x559A0D71, 0x559C0D6B, 0x559E0D72, 0x55A00D74, 0x55A20D68, 0x55A40D69, 0x55A60D65, 0x55A80D7D, 0x55AA0D76, 0x55AC0D75, 0x55AE0D7C, 0x55B00D78, 0x55B20D7B, 0x55B40D7E, 0x55B60D77, 0x55B80D7F, 0x55BA0D80, 0x55BC0D7A, 0x55BE0D8D, 0x55C10D87, 0x55C30D88, 0x55C50D8A, 0x55C70D83, 0x55C90D85, 0x55CB0D8C, 0x55CD0D89, 0x55CF0D84, 0x55D10D8B, 0x55D30D86, 0x55D60D8E, 0x2AA40D5B, 0x55860D5C, 0x55E40D90, 0x55F90D91, 0x56070D92, 0x560E0D93, 0x55EB0D94, 0x55F20D95, 0x56000D96, 0x56150D97 };
//D2Client.0x6FB8E238
uint32_t unk_6FB8E238[74] = { 0x42D0D0F, 0x42E0D10, 0x4300CFF, 0x42F0D00, 0x4310D01, 0x4320D02, 0x4330D03, 0x4340D04, 0x4360D05, 0x4350D06, 0x4380D07, 0x4370D08, 0x43A0D09, 0x4390D0A, 0x43B0D0B, 0x43C0D0C, 0x43D0D13, 0x43E0D14, 0x43F0CFE, 0x4410CFC, 0x4400CFD, 0x4430D15, 0x4420D16, 0x4460D11, 0x4450D12, 0x55880D25, 0x55890D1F, 0x558B0D1C, 0x558D0D21, 0x558F0D22, 0x55910D20, 0x55930D1E, 0x55950D19, 0x55970D18, 0x55990D23, 0x559B0D1D, 0x559D0D24, 0x559F0D26, 0x55A10D1A, 0x55A30D1B, 0x55A50D17, 0x55A70D2F, 0x55A90D28, 0x55AB0D27, 0x55AD0D2E, 0x55AF0D2A, 0x55B10D2D, 0x55B30D30, 0x55B50D29, 0x55B70D31, 0x55B90D32, 0x55BB0D2C, 0x55BD0D3F, 0x55BF0D39, 0x55C20D3A, 0x55C40D3C, 0x55C60D35, 0x55C80D37, 0x55CA0D3E, 0x55CC0D3B, 0x55CE0D36, 0x55D00D3D, 0x55D20D38, 0x55D40D40, 0x2AA40D0D, 0x55860D0E, 0x55E30D42, 0x55F80D43, 0x56060D44, 0x560D0D45, 0x55EA0D46, 0x55F10D47, 0x55FF0D48, 0x56140D49 };

//D2Client.0x6FB8D220
int32_t dword_6FB8D220 = 12;
//D2Client.0x6FB8D228
uint32_t tbl_6FB8D228[21] = {0, 0x205, (uint32_t)sub_6FAEABD0, 0, 0x204, (uint32_t)sub_6FB1B0F0, 0, 0x201, (uint32_t)sub_6FB1B0F0, 3, 0x1B, (uint32_t)sub_6FB1ADA0, 3, 0x20, (uint32_t)sub_6FB1ADA0, 0, 0x102, (uint32_t)sub_6FB1AD00, 0, 0x104, (uint32_t)sub_6FB1AC60};
//D2Client.0x6FB8D27C
uint32_t dword_6FB8D27C = 1;
//D2Client.0x6FB8D29C
int32_t dword_6FB8D29C = 8;
//D2Client.0x6FB8D2A0
uint16_t word_6FB8D2A0[2] = {0x40, 0xE82};
//D2Client.0x6FB8D430
uint16_t word_6FB8D430 = 0xA4;
//D2Client.0x6FB8DADC
int32_t dword_6FB8DADC = 527;
//D2Client.0x6FB8DAE0
uint8_t byte_6FB8DAE0[4] = {0xF2};
//D2Client.0x6FB8DAE4
uint8_t byte_6FB8DAE4[36] = {0x68, 0, 0, 0, 0xFF, 0, 0, 0, 0xDE, 0, 0, 0, 0x94, 0, 0, 0, 0x36, 1, 0, 0, 0x2F, 0, 0, 0, 0xDE, 0, 0, 0, 0x4B, 0, 0, 0, 0x68};
//D2Client.0x6FB8DB08
uint8_t byte_6FB8DB08[4] = {0x2F, 1};
//D2Client.0x6FB8DB0C
uint8_t byte_6FB8DB0C[36] = {0xA1, 0, 0, 0, 0x42, 1, 0, 0, 0xF2, 0, 0, 0, 0xFE, 0, 0, 0, 0x22, 1, 0, 0, 0xBE, 0, 0, 0, 0xEE, 0, 0, 0, 0xD3, 0, 0, 0, 0xA2};
//D2Client.0x6FB8DB30
uint32_t dword_6FB8DB30;
//D2Client.0x6FB8E360
uint8_t* gpuint8_t_6FB8E360[7] = {(uint8_t*)&unk_6FB8DB48, (uint8_t*)&unk_6FB8DC70, (uint8_t*)&unk_6FB8DD98, (uint8_t*)&unk_6FB8DEC0, (uint8_t*)&unk_6FB8DFE8, (uint8_t*)&unk_6FB8E110, (uint8_t*)&unk_6FB8E238};
//D2Client.0x6FB8E37C
uint16_t word_6FB8E37C[2] = {0x1207, 0x58A9};
//D2Client.0x6FBB9D90
RECT gaHoverTextRects[16];
//D2Client.0x6FBB9E90
uint32_t* gpuint32_t_6FBB9E90;
//D2Client.0x6FBB9E98
int32_t dword_6FBB9E98;
//D2Client.0x6FBB9E9C
int32_t* gpint32_t_6FBB9E9C;
//D2Client.0x6FBB9EA4
uint32_t dword_6FBB9EA4;
//D2Client.0x6FBB9EA8
int32_t dword_6FBB9EA8;
//D2Client.0x6FBB9EAC
int32_t dword_6FBB9EAC;
//D2Client.0x6FBB9EB0
int32_t dword_6FBB9EB0;
//D2Client.0x6FBB9EB8
int32_t dword_6FBB9EB8;
//D2Client.0x6FBB9EBC
int32_t dword_6FBB9EBC;
//D2Client.0x6FBB9EC8
uint8_t byte_6FBB9EC8;
//D2Client.0x6FBB9ECC
uint8_t* ptr_6FBB9ECC;
//D2Client.0x6FBB9ED0
int16_t word_6FBB9ED0;
//D2Client.0x6FBB9ED2
uint8_t* ptr_6FBB9ED2;
//D2Client.0x6FBB9ED6
int16_t word_6FBB9ED6;
//D2Client.0x6FBB9ED8
uint32_t* gpuint32_t_6FBB9ED8;
//D2Client.0x6FBB9EDC
int16_t word_6FBB9EDC;
//D2Client.0x6FBB9EDE
uint32_t dword_6FBB9EDE;
//D2Client.0x6FBB9EE2
uint32_t dword_6FBB9EE2;
//D2Client.0x6FBB9EEA
uint32_t dword_6FBB9EEA;
//D2Client.0x6FBB9EEE
uint32_t dword_6FBB9EEE;
//D2Client.0x6FBB9EF2
int32_t dword_6FBB9EF2;
//D2Client.0x6FBB9EF6
int32_t dword_6FBB9EF6;
//D2Client.0x6FBB9EFA
uint16_t word_6FBB9EFA;
//D2Client.0x6FBB9EFC
uint32_t dword_6FBB9EFC;
//D2Client.0x6FBB9F00
uint32_t dword_6FBB9F00;
//D2Client.0x6FBB9F0C
uint32_t dword_6FBB9F0C;
//D2Client.0x6FBB9F10
int32_t dword_6FBB9F10;
//D2Client.0x6FBB9F14
uint8_t byte_6FBB9F14;
//D2Client.0x6FBB9F18
int32_t dword_6FBB9F18;
//D2Client.0x6FBB9F1C
uint8_t byte_6FBB9F1C;
//D2Client.0x6FBB9F1E
uint32_t dword_6FBB9F1E;
//D2Client.0x6FBB9F22
uint8_t byte_6FBB9F22;
//D2Client.0x6FBB9F23
uint32_t dword_6FBB9F23;
//D2Client.0x6FBB9F27
uint32_t dword_6FBB9F27;
//D2Client.0x6FBB9F2B
DWORD dword_6FBB9F2B;
//D2Client.0x6FBB9F2F
uint32_t dword_6FBB9F2F;
//D2Client.0x6FBB9F33
uint32_t dword_6FBB9F33;
//D2Client.0x6FBB9F38
uint32_t* gpuint32_t_6FBB9F38;
//D2Client.0x6FBB9F3C
uint32_t dword_6FBB9F3C;
//D2Client.0x6FBB9F40
D2TextHeaderStrc* gpTextHeader_6FBB9F40;
//D2Client.0x6FBB9F44
uint16_t word_6FBB9F44;
//D2Client.0x6FBB9F48
uint8_t byte_6FBB9F48;
//D2Client.0x6FBB9F4C
uint8_t byte_6FBB9F4C;
//D2Client.0x6FBB9F50
uint32_t dword_6FBB9F50;
//D2Client.0x6FBB9F54
int32_t dword_6FBB9F54;
//D2Client.0x6FBB9F58
uint8_t* gpuint8_t_6FBB9F58;
//D2Client.0x6FBB9F5C
uint32_t dword_6FBB9F5C;
//D2Client.0x6FBB9F60
int32_t dword_6FBB9F60;
//D2Client.0x6FBB9F64
int32_t dword_6FBB9F64;
//D2Client.0x6FBB9F68
int32_t dword_6FBB9F68;
//D2Client.0x6FBB9F70
D2CellFileStrc* gpCellFile_6FBB9F70;
//D2Client.0x6FBB9F74
D2CellFileStrc* gpCellFile_6FBB9F74;
//D2Client.0x6FBB9F78
D2CellFileStrc* gpCellFile_6FBB9F78;
//D2Client.0x6FBB9F7C
int32_t dword_6FBB9F7C;
//D2Client.0x6FBB9FA8
uint8_t byte_6FBB9FA8;
//D2Client.0x6FBB9FBC
uint8_t byte_6FBB9FBC;

//D2Client.0x6FB1A7C0
void __cdecl sub_6FB1A7C0(int* a1)
{
	uint32_t* puVar1;
	uint32_t* pFree;

	if (a1 != nullptr)
	{
		pFree = (uint32_t*)*a1;
		while (pFree != nullptr)
		{
			puVar1 = (uint32_t*)pFree[1];
			D2_FREE((void*)*pFree);
			D2_FREE(pFree);
			pFree = puVar1;
		}
		D2_FREE(a1);
	}
}

//D2Client.0x6FB1A820
void __cdecl sub_6FB1A820()
{
	int iVar1;
	int* piVar2;
	uint32_t local_4;

	piVar2 = &dword_6FBB9E98;
	for (iVar1 = 0x27; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*piVar2 = 0;
		piVar2 = piVar2 + 1;
	}
	*(uint16_t*)piVar2 = 0;
	*(uint8_t*)((int)piVar2 + 2) = 0;
	iVar1 = SRegLoadValue("Diablo II", "Text Display Beta", 0, (DWORD*)(&local_4));
	if (iVar1 == 0)
	{
		dword_6FBB9EDE = 1;
		return;
	}
	dword_6FBB9EDE = local_4;
}

//D2Client.0x6FB1A870
void __cdecl sub_6FB1A870()
{
	uint32_t* puVar1;
	void* pvVar2;
	void* pvVar3;
	uint32_t* puVar4;
	short sVar5;
	uint32_t* puVar6;
	void* pvVar7;
	int iVar8;
	short sStack_4;

	if (gpTextHeader_6FBB9F40 != nullptr)
	{
		TEXT_FreeTextHeader(gpTextHeader_6FBB9F40);
		gpTextHeader_6FBB9F40 = nullptr;
	}
	puVar6 = gpuint32_t_6FBB9E90;
	if (gpuint32_t_6FBB9E90 != nullptr)
	{
		puVar4 = (uint32_t*)*gpuint32_t_6FBB9E90;
		while (puVar4 != nullptr)
		{
			puVar1 = (uint32_t*)puVar4[1];
			D2_FREE((void*)*puVar4);
			D2_FREE(puVar4);
			puVar4 = puVar1;
		}
		D2_FREE(puVar6);
		gpuint32_t_6FBB9E90 = nullptr;
	}
	puVar6 = gpuint32_t_6FBB9F38;
	if (gpuint32_t_6FBB9F38 != nullptr)
	{
		puVar4 = (uint32_t*)*gpuint32_t_6FBB9F38;
		while (puVar4 != nullptr)
		{
			puVar1 = (uint32_t*)puVar4[1];
			D2_FREE((void*)*puVar4);
			D2_FREE(puVar4);
			puVar4 = puVar1;
		}
		D2_FREE(puVar6);
		D2_FREE(gpuint32_t_6FBB9F38);
		gpuint32_t_6FBB9F38 = nullptr;
	}
	if (dword_6FBB9E98 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB9E98 = 0;
	}
	if (gpint32_t_6FBB9E9C != nullptr)
	{
		(**(code**)*gpint32_t_6FBB9E9C)(1);
		gpint32_t_6FBB9E9C = nullptr;
	}
	if (gpCellFile_6FBB9F74 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB9F74);
		gpCellFile_6FBB9F74 = nullptr;
	}
	if (gpCellFile_6FBB9F70 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB9F70);
		gpCellFile_6FBB9F70 = nullptr;
	}
	if (gpCellFile_6FBB9F78 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBB9F78);
		gpCellFile_6FBB9F78 = nullptr;
	}
	sub_6FAB6450(nullptr);
	sStack_4 = 0;
	pvVar7 = ptr_6FBB9ECC;
	sVar5 = 0;
	if (ptr_6FBB9ECC != nullptr)
	{
		do
		{
			pvVar2 = *(void**)((int)pvVar7 + 0x22);
			iVar8 = 0;
			do
			{
				pvVar3 = *(void**)((int)pvVar7 + iVar8 * 4);
				if (pvVar3 != nullptr)
				{
					D2_FREE(pvVar3);
				}
				iVar8 = iVar8 + 1;
			} while (iVar8 < 6);
			D2_FREE(pvVar7);
			sStack_4 = sVar5 + 1;
			pvVar7 = pvVar2;
			sVar5 = sStack_4;
		} while (pvVar2 != nullptr);
		ptr_6FBB9ECC = nullptr;
	}
	D2_ASSERT(sStack_4 == word_6FBB9ED0);
	word_6FBB9ED0 = 0;
	sStack_4 = 0;
	pvVar7 = ptr_6FBB9ED2;
	sVar5 = 0;
	if (ptr_6FBB9ED2 != nullptr)
	{
		do
		{
			pvVar2 = *(void**)((int)pvVar7 + 0x22);
			iVar8 = 0;
			do
			{
				pvVar3 = *(void**)((int)pvVar7 + iVar8 * 4);
				if (pvVar3 != nullptr)
				{
					D2_FREE(pvVar3);
				}
				iVar8 = iVar8 + 1;
			} while (iVar8 < 6);
			D2_FREE(pvVar7);
			sStack_4 = sVar5 + 1;
			pvVar7 = pvVar2;
			sVar5 = sStack_4;
		} while (pvVar2 != nullptr);
		ptr_6FBB9ED2 = nullptr;
	}
	if (sStack_4 == word_6FBB9ED6)
	{
		word_6FBB9ED6 = 0;
		sub_6FB1AAF0((int*)&gpuint32_t_6FBB9ED8);
		dword_6FBB9F33 = 0;
		return;
	}
	FOG_DisplayAssert("wCountDeleted == pGlobalMessageList->wCount",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB1AAF0
void __fastcall sub_6FB1AAF0(int* a1)
{
	void* pvVar1;
	void* pFree;
	void* pFree_00;
	short sVar2;
	short sVar3;
	int iVar4;

	pFree_00 = (void*)*a1;
	sVar3 = 0;
	sVar2 = 0;
	if (pFree_00 != nullptr)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree_00 + 0x22);
			iVar4 = 0;
			do
			{
				pFree = *(void**)((int)pFree_00 + iVar4 * 4);
				if (pFree != nullptr)
				{
					D2_FREE(pFree);
				}
				iVar4 = iVar4 + 1;
			} while (iVar4 < 6);
			D2_FREE(pFree_00);
			sVar2 = sVar3 + 1;
			pFree_00 = pvVar1;
			sVar3 = sVar2;
		} while (pvVar1 != nullptr);
		*a1 = 0;
	}
	if (sVar2 == (short)a1[1])
	{
		*(uint16_t*)(a1 + 1) = 0;
		return;
	}
	FOG_DisplayAssert("wCountDeleted == pGlobalMessageList->wCount",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB1AB80
void __fastcall sub_6FB1AB80(uint32_t a1)
{
	dword_6FBB9EDE = a1;
	SRegSaveValue("Diablo II", "Text Display Beta", 0, a1);
}

//D2Client.0x6FB1ABA0
void __fastcall sub_6FB1ABA0(int* a1, int a2, int a3)
{
	Font nFontSize;
	uint32_t uVar1;
	int iVar2;
	uint32_t* puVar3;

	uVar1 = a1[1];
	if (10 < uVar1)
	{
		uVar1 = 10;
	}
	puVar3 = (uint32_t*)*a1;
	if ((((uVar1 != 0) && (puVar3 != nullptr)) && (-1 < a3)) &&
	    ((int)((uint32_t) * (uint16_t*)((int)a1 + 0x12) + a3) < gnScreenHeight))
	{
		sub_6FB5B0F0(a2, a3 + 4, (uint32_t) * (uint16_t*)(a1 + 4),
		    *(uint16_t*)((int)a1 + 0x12) - 5, 0, (DrawMode)(1));
		iVar2 = 0;
		nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
		if (0 < (int)uVar1)
		{
			do
			{
				if (puVar3 == nullptr)
					break;
				D2Win_10117_DrawText((Unicode*)*puVar3, a2 + 10,
				    ((iVar2 - uVar1) + a1[1]) * 0xf + 0x12 + a3, 0, 0);
				puVar3 = (uint32_t*)puVar3[1];
				iVar2 = iVar2 + 1;
			} while (iVar2 < (int)uVar1);
		}
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FB1AC60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB1AC60(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t uVar2;
	DWORD DVar3;
	int iVar4;

	if (pSMSGHANDLER_PARAMS->wParam != 0x73)
	{
		bVar1 = sub_6FAD4F00(7, 1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(7, 1);
			if ((((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0)) &&
			    (pSMSGHANDLER_PARAMS->wParam == (uVar2 & 0xffff)))
			{
				return;
			}
		}
		dword_6FBB9EE2 = 0;
		DVar3 = GetTickCount();
		if (DVar3 - byte_6FBB9F14 < 100)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			dword_6FBB9F27 = 0;
			return;
		}
		iVar4 = sub_6FB1AE00();
		if (iVar4 != 0)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FB1AD00
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB1AD00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t uVar2;
	DWORD DVar3;
	int iVar4;

	bVar1 = sub_6FAD4F00(7, 1);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar2 = sub_6FAD4B60(7, 1);
		if ((((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0)) &&
		    (pSMSGHANDLER_PARAMS->wParam == (uVar2 & 0xffff)))
		{
			return;
		}
	}
	dword_6FBB9EE2 = 0;
	DVar3 = GetTickCount();
	if (99 < DVar3 - byte_6FBB9F14)
	{
		iVar4 = sub_6FB1AE00();
		if (iVar4 != 0)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
		return;
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	dword_6FBB9F27 = 0;
}

//D2Client.0x6FB1ADA0
void __cdecl sub_6FB1ADA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	DWORD DVar1;
	int iVar2;

	dword_6FBB9EE2 = 0;
	DVar1 = GetTickCount();
	if (DVar1 - byte_6FBB9F14 < 100)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		dword_6FBB9F27 = 0;
	}
	else
	{
		iVar2 = sub_6FB1AE00();
		if (iVar2 != 0)
		{
			pSMSGHANDLER_PARAMS->lResult = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
}

//D2Client.0x6FB1AE00
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FB1AE00()
{
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* puVar2;
	int iVar3;
	int iVar4;
	HWND__* pHVar5;
	uint32_t extraout_ECX;
	int extraout_ECX_00;
	int extraout_ECX_01;
	int extraout_ECX_02;
	uint32_t uVar6;

	puVar2 = gpuint32_t_6FBB9F38;
	dword_6FBB9EA4 = 1;
	if ((dword_6FBB9EF2 != 0) || (dword_6FBB9EA8 == 1))
	{
		if (gpuint8_t_6FBB9F58 == nullptr)
		{
			if (dword_6FBB9EF2 == 0)
			{
				sub_6FAB6450(nullptr);
				puVar2 = gpuint32_t_6FBB9E90;
				if (gpuint32_t_6FBB9E90 != nullptr)
				{
					sub_6FB1B0B0(*gpuint32_t_6FBB9E90);
					D2_FREE(puVar2);
					gpuint32_t_6FBB9E90 = nullptr;
				}
				iVar3 = dword_6FBB9F60;
				if (dword_6FBB9F60 != 0)
				{
					iVar4 = sub_6FB556F0(dword_6FBB9F60);
					iVar3 = extraout_ECX_00;
					if (iVar4 != 0)
					{
						sub_6FB55BF0(iVar4, 0, 0, 4);
						iVar3 = extraout_ECX_01;
					}
					dword_6FBB9F60 = 0;
				}
				dword_6FBB9F33 = 0;
				if (dword_6FBB9F68 == 1)
				{
					uVar6 = 7;
					dword_6FBB9F68 = 0;
					pHVar5 = WINDOW_GetWindow();
					WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar6);
					iVar3 = extraout_ECX_02;
				}
				if (dword_6FBB9F18 != 0)
				{
					sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar3 >> 8), 0x31), 0xffffffff, (uint32_t)word_6FBB9EFA);
					dword_6FBB9F18 = 0;
				}
			}
			else
			{
				sub_6FAFBF80(dword_6FBB9EEA);
			}
			sub_6FB238B0();
		}
		else
		{
			sub_6FAB6450(nullptr);
			puVar2 = gpuint32_t_6FBB9E90;
			if (gpuint32_t_6FBB9E90 != nullptr)
			{
				sub_6FB1B0B0(*gpuint32_t_6FBB9E90);
				D2_FREE(puVar2);
				gpuint32_t_6FBB9E90 = nullptr;
			}
			if (dword_6FBB9F60 != 0)
			{
				iVar3 = sub_6FB556F0(dword_6FBB9F60);
				if (iVar3 != 0)
				{
					sub_6FB55BF0(iVar3, 0, 0, 4);
				}
				dword_6FBB9F60 = 0;
			}
			dword_6FBB9F33 = 0;
			sub_6FB1B200(0);
			if (dword_6FBB9F18 != 0)
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x31), 0xffffffff, (uint32_t)word_6FBB9EFA);
				dword_6FBB9F18 = 0;
			}
			sub_6FB238B0();
			iVar3 = (*(code*)gpuint8_t_6FBB9F58)(dword_6FBB9F27);
			if (iVar3 != 0)
			{
				dword_6FBB9F27 = 0;
				return 1;
			}
			if (dword_6FBB9EF2 != 0)
			{
				sub_6FAFBF80(dword_6FBB9EEA);
			}
		}
		dword_6FBB9EF2 = 0;
		if (dword_6FBB9F68 == 1)
		{
			uVar6 = 7;
			dword_6FBB9F68 = 0;
			pHVar5 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar6);
		}
		dword_6FBB9F27 = 0;
		return 1;
	}
	if (dword_6FBB9EAC != 1)
	{
		dword_6FBB9EA4 = 1;
		dword_6FBB9F27 = 0;
		return 0;
	}
	if (dword_6FBB9EB0 == 1)
	{
		dword_6FBB9F27 = 0;
		return 0;
	}
	D2_ASSERT(gpuint32_t_6FBB9F38 != nullptr);
	dword_6FBB9EF2 = 0;
	dword_6FBB9EAC = 1;
	pFree = (uint32_t*)*gpuint32_t_6FBB9F38;
	while (pFree != nullptr)
	{
		puVar1 = (uint32_t*)pFree[1];
		D2_FREE((void*)*pFree);
		D2_FREE(pFree);
		pFree = puVar1;
	}
	D2_FREE(puVar2);
	D2_FREE(gpuint32_t_6FBB9F38);
	gpuint32_t_6FBB9F38 = nullptr;
	dword_6FBB9EAC = 0;
	dword_6FBB9EB0 = 0;
	dword_6FBB9F27 = 0;
	return 1;
}

//D2Client.0x6FB1B0B0
void __fastcall sub_6FB1B0B0(int a1)
{
	uint32_t* puVar1;

	if (a1 != 0)
	{
		do
		{
			puVar1 = *(uint32_t**)(a1 + 4);
			D2_FREE(*(void**)a1);
			D2_FREE((void*)a1);
			a1 = (int)puVar1;
		} while (puVar1 != nullptr);
	}
}

//D2Client.0x6FB1B0F0
void __cdecl sub_6FB1B0F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2UnitStrc* pDVar1;
	D2UnitStrc* pDVar2;
	DWORD DVar3;
	uint32_t uVar4;
	int iVar5;

	dword_6FBB9F27 = 1;
	pDVar1 = sub_6FAB5A20();
	if (pDVar1 == nullptr)
	{
		pDVar1 = sub_6FAB5A20();
		if ((pDVar1 == nullptr) && (byte_6FBB9F22 != '\0'))
		{
			pDVar1 = sub_6FB269F0(dword_6FBB9F23, 1);
			if (pDVar1 == nullptr)
			{
				return;
			}
			pDVar2 = sub_6FB269F0(dword_6FBB9EEA, 1);
			if (pDVar1 != pDVar2)
			{
				return;
			}
			goto LAB_6fb1b1b6;
		}
		dword_6FBB9EE2 = 0;
		DVar3 = GetTickCount();
		uVar4 = DVar3 - byte_6FBB9F14;
	}
	else
	{
		if (dword_6FBB9EF2 != 0)
		{
			pDVar1 = sub_6FB269F0(dword_6FBB9EEA, 1);
			pDVar2 = sub_6FAB5A20();
			if (pDVar1 == pDVar2)
			{
				return;
			}
		}
		dword_6FBB9EE2 = 0;
		DVar3 = GetTickCount();
		uVar4 = DVar3 - byte_6FBB9F14;
	}
	if (uVar4 < 100)
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		dword_6FBB9F27 = 0;
	}
	else
	{
		iVar5 = sub_6FB1AE00();
		if (iVar5 != 0)
		{
		LAB_6fb1b1b6:
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
}

//D2Client.0x6FB1B1D0
void __fastcall sub_6FB1B1D0(int a1)
{
	if (a1 != 0)
	{
		byte_6FBB9F22 = 1;
		dword_6FBB9F23 = *(uint32_t*)(a1 + 0xc);
		return;
	}
	byte_6FBB9F22 = 0;
}

//D2Client.0x6FB1B1F0
void __cdecl sub_6FB1B1F0()
{
	byte_6FBB9F22 = 0;
}

//D2Client.0x6FB1B200
void __fastcall sub_6FB1B200(int a1)
{
	HWND__* pHVar1;
	uint32_t uVar2;

	if (a1 == 0)
	{
		if (dword_6FBB9F68 == 1)
		{
			uVar2 = 7;
			dword_6FBB9F68 = a1;
			pHVar1 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar2);
			return;
		}
	}
	else if ((a1 == 1) && (dword_6FBB9F68 == 0))
	{
		dword_6FBB9F68 = a1;
		byte_6FBB9F14 = GetTickCount();
		uVar2 = 7;
		pHVar1 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar2);
	}
}

//D2Client.0x6FB1B260
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB1B260()
{
	Unicode UVar1;
	D2HoverTextStrc* pHoverMsg;
	uint8_t bVar2;
	int iVar3;
	Unicode* pUVar4;
	D2C_Language DVar6;
	D2UnitStrc* in_ECX;
	Unicode* pUVar7;
	uint32_t* puVar8;
	D2CoordStrc DStack_4a0;
	D2UnitStrc* pDStack_498;
	char cStack_494;
	char cStack_493;
	char acStack_492[258];
	uint32_t uStack_390;
	uint16_t uStack_192;
	Unicode aUStack_190[200];
	D2C_Language DVar5;

	if (in_ECX == nullptr)
	{
		return;
	}
	pHoverMsg = in_ECX->pHoverText;
	if (pHoverMsg == nullptr)
	{
		return;
	}
	pDStack_498 = in_ECX;
	UNITS_GetClientCoords(in_ECX, &DStack_4a0);
	DStack_4a0.nX = DStack_4a0.nX - dword_6FBB9EFC;
	DStack_4a0.nY = DStack_4a0.nY + (-0x1e - dword_6FBB9F00);
	iVar3 = sub_6FAB5750();
	if (iVar3 == 1)
	{
		iVar3 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
	LAB_6fb1b2eb:
		DStack_4a0.nX = DStack_4a0.nX + iVar3;
	}
	else
	{
		if (iVar3 == 2)
		{
			iVar3 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
			goto LAB_6fb1b2eb;
		}
		if (iVar3 == 3)
		{
			return;
		}
	}
	if (DStack_4a0.nY < 1)
	{
		return;
	}
	if (gnScreenHeight <= DStack_4a0.nY)
	{
		return;
	}
	if (DStack_4a0.nX < -99)
	{
		return;
	}
	if (gnScreenWidth + 100 <= DStack_4a0.nX)
	{
		return;
	}
	CHAT_CopyHoverMsgToBuffer(pHoverMsg, &cStack_494);
	if ((((cStack_494 == -1) && (cStack_493 == -1)) &&
	        (((iVar3 = atoi(acStack_492), 0x42c < iVar3 && (iVar3 < 0x510)) ||
	            ((((0x5586 < iVar3 && (iVar3 < 0x5616)) || (iVar3 == 0x2aa4)) || (iVar3 == 0x5586)))))) &&
	    (pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)iVar3)), in_ECX = pDStack_498,
	        pUVar4 != nullptr))
	{
		pUVar7 = aUStack_190;
		for (iVar3 = 100; iVar3 != 0; iVar3 = iVar3 + -1)
		{
			*(uint32_t*)pUVar7 = 0;
			pUVar7 = pUVar7 + 2;
		}
		iVar3 = Unicode::strlen(pUVar4);
		if (199 < iVar3)
		{
			iVar3 = 199;
		}
		Unicode::strncpy(aUStack_190, pUVar4, iVar3);
		sub_6FB1B4F0((int)pDStack_498, pHoverMsg, aUStack_190, (POINT*)(&DStack_4a0));
		return;
	}
	pUVar4 = (Unicode*)&uStack_390;
	iVar3 = 0x100;
	do
	{
		pUVar4 = pUVar4 + 1;
		iVar3 = iVar3 + -1;
	} while (iVar3 != 0);
	bVar2 = CHAT_GetLangIdFromHoverMsg(pHoverMsg);
	DVar5 = (D2C_Language)bVar2;
	puVar8 = &uStack_390;
	if (((DVar5 == LANGUAGE_KOREAN) || (DVar5 == LANGUAGE_ENGLISHKOR)) ||
	    ((DVar5 == LANGUAGE_JAPANESE || (DVar5 == LANGUAGE_CHINESETWN))))
	{
		MultiByteToWideChar(0, 1, &cStack_494, 0x100, (LPWSTR)&uStack_390, 0x100);
		DVar6 = STRTABLE_GetLanguage();
		if (DVar6 != DVar5)
		{
			if (DVar6 == LANGUAGE_KOREAN)
			{
				if (DVar5 == LANGUAGE_ENGLISHKOR)
					goto LAB_6fb1b4bb;
			}
			else if ((DVar6 == LANGUAGE_ENGLISHKOR) && (DVar5 == LANGUAGE_KOREAN))
				goto LAB_6fb1b4bb;
			UVar1.ch = (*(uint16_t*)((uint8_t*)&uStack_390 + 0));
			while (UVar1.ch != 0)
			{
				if (0x7f < (uint16_t)uStack_390)
				{
					return;
				}
				UVar1.ch = *(uint16_t*)((int)puVar8 + 2);
				uStack_390 = (uint32_t)UVar1.ch;
				puVar8 = (uint32_t*)((int)puVar8 + 2);
			}
		}
	}
	else
	{
		Unicode::win2Unicode((Unicode*)&uStack_390, &cStack_494, 0x100);
	}
LAB_6fb1b4bb:
	uStack_192 = 0;
	sub_6FB1B4F0((int)in_ECX, pHoverMsg, (Unicode*)(&uStack_390), (POINT*)(&DStack_4a0));
}

//D2Client.0x6FB1B4F0
void __fastcall sub_6FB1B4F0(int a1, D2HoverTextStrc* pHoverText, Unicode* pUnicode, POINT* pPosition)
{
	if (CHAT_GetTimeoutFromHoverMsg(pHoverText) < (uint32_t)dword_6FBB9EF6)
	{
		CHAT_FreeHoverMsg(nullptr, pHoverText);
		if (a1)
		{
			*(uint32_t*)(a1 + 0xA4) = 0;
		}
	}

	const Font nOldFont = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);

	D2HoverTextBoxStrc* pBox = (D2HoverTextBoxStrc*)D2_ALLOC(sizeof(D2HoverTextBoxStrc));
	D2SplittedTextStrc* pLines = D2Win_10199(pUnicode, &pBox->nLines, 180);
	pBox->pLines = pLines;
	pBox->unk0x08 = 0;
	pBox->unk0x0C = pBox->unk0x14;

	int32_t nMaxWidth = 0;
	for (D2SplittedTextStrc* pLine = pLines; pLine; pLine = pLine->pNextLine)
	{
		const int32_t nWidth = D2Win_10121_GetTextWidth(pLine->wszLine);
		if (nWidth >= nMaxWidth)
		{
			nMaxWidth = nWidth;
		}
	}

	pBox->nWidth = (uint16_t)(nMaxWidth + 20);
	pBox->nHeight = (uint16_t)(15 * pBox->nLines + 6);

	pPosition->x -= pBox->nWidth >> 1;
	pPosition->y -= 50;
	pPosition->y = pPosition->y - 15 * pBox->nLines - 3;

	RECT tRect;
	tRect.left = pPosition->x;
	tRect.top = pPosition->y;
	tRect.right = pPosition->x + pBox->nWidth;
	tRect.bottom = pPosition->y + pBox->nHeight;

	const int32_t nRects = dword_6FBB9F0C;
	if (nRects < ARRAY_SIZE(gaHoverTextRects))
	{
		if (nRects == 0)
		{
			gaHoverTextRects[0] = tRect;
		}
		else
		{
			BOOL bIntersects = FALSE;
			for (int32_t i = 0; i < nRects; ++i)
			{
				RECT tIntersection;
				if (IntersectRect(&tIntersection, &gaHoverTextRects[i], &tRect))
				{
					bIntersects = TRUE;
					break;
				}
			}

			if (bIntersects)
			{
				// Look for a free spot around the original position
				for (int32_t nOffsetX = 50; nOffsetX < 400; nOffsetX += 50)
				{
					for (int32_t nOffsetY = 35; nOffsetY < 280; nOffsetY += 35)
					{
						for (int32_t i = 0; i < dword_6FB8D29C; ++i)
						{
							RECT tCandidate;
							tCandidate.left = tRect.left + (&dword_6FB8D27C)[i] * nOffsetX;
							tCandidate.top = tRect.top + (&dword_6FB8D27C)[i] * nOffsetY;
							tCandidate.right = tCandidate.left + 400;
							tCandidate.bottom = tCandidate.top + 280;

							if (tCandidate.left < 0 || tCandidate.right > gnScreenWidth || tCandidate.top < 0 || tCandidate.bottom > gnScreenHeight)
							{
								continue;
							}

							BOOL bOverlaps = FALSE;
							for (int32_t j = 0; j < nRects; ++j)
							{
								RECT tIntersection;
								if (IntersectRect(&tIntersection, &gaHoverTextRects[j], &tCandidate))
								{
									bOverlaps = TRUE;
								}
							}

							if (!bOverlaps)
							{
								tRect = tCandidate;
								gaHoverTextRects[nRects] = tCandidate;
								goto DRAW;
							}
						}
					}
				}

				sub_6FB1B0B0((int)pBox->pLines);
				D2_FREE(pBox);
				return;
			}

			gaHoverTextRects[nRects] = tRect;
		}
	}

DRAW:
	++dword_6FBB9F0C;
	sub_6FB1B820((int*)pBox, (int*)&tRect);
	sub_6FB1B0B0((int)pBox->pLines);
	D2_FREE(pBox);
	D2Win_10127_SetFont(nOldFont);
}

//D2Client.0x6FB1B820
uint32_t __fastcall sub_6FB1B820(int* a1, int* a2)
{
	int iVar1;

	if (*(int*)((int)a1 + 0x16) == 0)
	{
		*(uint32_t*)((int)a1 + 0x16) = 1;
	}
	else if (*(int*)((int)a1 + 0x16) == 3)
	{
		return 1;
	}
	iVar1 = sub_6FAB5750();
	if (iVar1 == 1)
	{
		if (gnScreenWidth / 2 + -10 < *a2)
		{
			return 1;
		}
	}
	else if (iVar1 == 2)
	{
		if (*a2 < gnScreenWidth / 2 + 10)
		{
			return 1;
		}
	}
	else if (iVar1 == 3)
	{
		return 1;
	}
	sub_6FB1ABA0(a1, *a2, a2[1]);
	return 1;
}

//D2Client.0x6FB1B8A0
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB1B8A0()
{
	D2HoverTextStrc* pHoverMsg;
	int iVar1;
	Unicode* a1;
	D2UnitStrc* in_ECX;
	Unicode* pUVar2;
	D2CoordStrc DStack_29c;
	D2HoverTextStrc* pDStack_294;
	Unicode aUStack_290[200];
	char acStack_100[256];

	if (in_ECX == nullptr)
	{
		return;
	}
	pHoverMsg = in_ECX->pHoverText;
	if (pHoverMsg == nullptr)
	{
		return;
	}
	pDStack_294 = pHoverMsg;
	UNITS_GetClientCoords(in_ECX, &DStack_29c);
	DStack_29c.nX = DStack_29c.nX - dword_6FBB9EFC;
	DStack_29c.nY = DStack_29c.nY + (-10 - dword_6FBB9F00);
	iVar1 = sub_6FAB5750();
	if (iVar1 == 1)
	{
		iVar1 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
	}
	else
	{
		if (iVar1 != 2)
		{
			if (iVar1 == 3)
			{
				return;
			}
			goto LAB_6fb1b92f;
		}
		iVar1 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
	}
	DStack_29c.nX = DStack_29c.nX + iVar1;
LAB_6fb1b92f:
	if ((((0 < DStack_29c.nY) && (DStack_29c.nY < gnScreenHeight)) && (-100 < DStack_29c.nX)) &&
	    (DStack_29c.nX < gnScreenWidth + 100))
	{
		CHAT_CopyHoverMsgToBuffer(pHoverMsg, acStack_100);
		iVar1 = atoi(acStack_100);
		if (((0 < iVar1) && (iVar1 < 0xffff)) &&
		    (a1 = (Unicode*)(D2LANG_GetStringFromTblIndex((short)iVar1)), a1 != nullptr))
		{
			pUVar2 = aUStack_290;
			for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1)
			{
				*(uint32_t*)pUVar2 = 0;
				pUVar2 = pUVar2 + 2;
			}
			iVar1 = Unicode::strlen(a1);
			if (199 < iVar1)
			{
				iVar1 = 199;
			}
			Unicode::strncpy(aUStack_290, a1, iVar1);
			sub_6FB1B4F0((int)in_ECX, pDStack_294, aUStack_290, (POINT*)(&DStack_29c));
		}
	}
}

//D2Client.0x6FB1BA00
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1BA00(int a1)
{
	uint32_t* puVar1;
	bool bVar2;
	int* piVar3;
	uint32_t extraout_var;
	HWND__* pHVar4;
	DWORD DVar5;
	int iVar6;
	uint32_t extraout_ECX;
	int iVar7;
	D2UnitStrc* pDVar8;
	int iVar9;
	uint32_t uVar10;
	int local_18;
	int local_14;
	int local_10;
	int local_c;
	int local_8;
	int local_4;

	dword_6FBB9EF6 = dword_6FBB9EF6 + 1;
	iVar7 = 0;
	sub_6FAB7180(a1, (uint32_t*)(&local_10), (uint32_t*)(&local_c), (uint32_t*)(&local_8), (uint32_t*)(&local_4));
	sub_6FAB71E0(a1, (uint32_t*)(&local_14), (uint32_t*)(&local_18));
	SetRect((LPRECT)&dword_6FBB9EFC, local_14, local_18, (local_8 - local_10) + local_14,
	    (local_18 - local_c) + local_4);
	if (dword_6FBB9EA8 == 1)
	{
		gaHoverTextRects[0].left = dword_6FBB9F54;
		gaHoverTextRects[0].right = dword_6FBB9F54 + 0x145;
		gaHoverTextRects[0].top = dword_6FB8D220;
		gaHoverTextRects[0].bottom = dword_6FB8D220 + 0x70;
	}
	dword_6FBB9F0C = (uint32_t)(dword_6FBB9EA8 == 1);
	sub_6FB29700((uint8_t*)(sub_6FB1B260));
	sub_6FB29750((uint8_t*)(sub_6FB1B8A0));
	sub_6FB297A0((uint8_t*)(sub_6FB1B8A0));
	puVar1 = gpuint32_t_6FBB9E90;
	if (((dword_6FBB9EA8 == 1) && (gpuint32_t_6FBB9E90 != nullptr)) &&
	    ((*(int*)((int)gpuint32_t_6FBB9E90 + 0x16) == 1 || (*(int*)((int)gpuint32_t_6FBB9E90 + 0x16) == 0))))
	{
		if (dword_6FBB9EA4 == 0)
		{
			iVar7 = D2SOUND_10046();
			if (((dword_6FBB9F33 == 0) || (piVar3 = sub_6FB55550(dword_6FBB9F33), piVar3 != nullptr)) ||
			    (iVar7 == 0))
			{
				dword_6FBB9F33 = 0;
				iVar7 = sub_6FB1BE70((int*)(puVar1));
				puVar1 = gpuint32_t_6FBB9E90;
				if (iVar7 != 0)
				{
					dword_6FBB9EA4 = 1;
					if ((dword_6FBB9EF2 == 0) && (gpuint32_t_6FBB9E90 != nullptr))
					{
						sub_6FB1B0B0(*gpuint32_t_6FBB9E90);
						D2_FREE(puVar1);
						gpuint32_t_6FBB9E90 = nullptr;
						sub_6FAB6450(nullptr);
					}
					sub_6FB1E810();
					if (gpuint8_t_6FBB9F58 == nullptr)
					{
						if (dword_6FBB9EAC == 1)
						{
							dword_6FBB9EAC = 0;
						}
						else if (dword_6FBB9EF2 != 0)
						{
							sub_6FAFBF80(dword_6FBB9EEA);
						}
						sub_6FB238B0();
						dword_6FBB9EF2 = 0;
						sub_6FAB6450(nullptr);
						sub_6FB1B200(0);
						iVar7 = 0;
					}
					else
					{
						iVar7 = (*(code*)gpuint8_t_6FBB9F58)(0);
					}
					goto LAB_6fb1bbf3;
				}
			}
			iVar7 = 1;
		}
		else
		{
			*(uint32_t*)((int)gpuint32_t_6FBB9E90 + 0x16) = 2;
			iVar7 = 0;
		}
	LAB_6fb1bbf3:
		pDVar8 = nullptr;
		if (dword_6FBB9EF2 != 0)
		{
			pDVar8 = sub_6FB269F0(dword_6FBB9EEA, 1);
		}
		bVar2 = sub_6FB283E0();
		if ((D2C_ZEXT(bVar2) != 0) ||
		    (((dword_6FBB9EF2 != 0 && (pDVar8 != nullptr)) && (pDVar8->dwAnimMode == 0xc))))
		{
			if (dword_6FBB9EF2 == 0)
			{
			LAB_6fb1bc70:
				sub_6FAB6450(nullptr);
				if (gpuint32_t_6FBB9E90 != nullptr)
				{
					sub_6FB1A7C0((int*)(gpuint32_t_6FBB9E90));
					gpuint32_t_6FBB9E90 = nullptr;
				}
				sub_6FB1CBE0();
				sub_6FB1B200(0);
				if (dword_6FBB9F18 != 0)
				{
					sub_6FAADA40(CONCAT31((uint32_t)(uint8_t)(word_6FBB9EFA >> 8), 0x31), 0xffffffff,
					    (uint32_t)word_6FBB9EFA);
					dword_6FBB9F18 = 0;
				}
			}
			else
			{
				sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x30), 1, dword_6FBB9EEA);
				sub_6FAF7950(dword_6FBB9EEA);
				if (dword_6FBB9EF2 == 0)
					goto LAB_6fb1bc70;
				sub_6FAFBF80(dword_6FBB9EEA);
			}
			sub_6FB238B0();
			dword_6FBB9EF2 = 0;
			if (dword_6FBB9F68 == 1)
			{
				uVar10 = 7;
				dword_6FBB9F68 = 0;
				pHVar4 = WINDOW_GetWindow();
				WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar10);
			}
		}
	}
	if (dword_6FBB9EAC == 0)
		goto LAB_6fb1bd48;
	D2_ASSERT(dword_6FBB9EB0);
	DVar5 = GetTickCount();
	puVar1 = gpuint32_t_6FBB9F38;
	if (dword_6FBB9F3C < DVar5)
	{
		iVar9 = 0;
		if (gpuint32_t_6FBB9F38 != nullptr)
		{
			sub_6FB1B0B0(*gpuint32_t_6FBB9F38);
			D2_FREE(puVar1);
			gpuint32_t_6FBB9F38 = nullptr;
		}
		dword_6FBB9EAC = 0;
		dword_6FBB9EF2 = 0;
	}
	else
	{
		iVar9 = 1;
		if (*(int*)((int)gpuint32_t_6FBB9F38 + 0x16) == 0)
		{
			*(uint32_t*)((int)gpuint32_t_6FBB9F38 + 0x16) = 1;
		}
		else if (*(int*)((int)gpuint32_t_6FBB9F38 + 0x16) == 3)
			goto LAB_6fb1bd46;
		iVar6 = sub_6FAB5750();
		if (iVar6 == 1)
		{
			if (dword_6FBB9EB8 <= gnScreenWidth / 2 + -10)
				goto LAB_6fb1be31;
		}
		else if (iVar6 == 2)
		{
			if (gnScreenWidth / 2 + 10 <= dword_6FBB9EB8)
				goto LAB_6fb1be31;
		}
		else if (iVar6 != 3)
		{
		LAB_6fb1be31:
			sub_6FB1ABA0((int*)(puVar1), dword_6FBB9EB8, dword_6FBB9EBC);
		}
	}
LAB_6fb1bd46:
	iVar7 = iVar7 + iVar9;
LAB_6fb1bd48:
	if ((iVar7 == 0) && (dword_6FBB9EA8 == 1))
	{
		dword_6FBB9EE2 = 0;
		dword_6FBB9EF2 = 0;
		dword_6FBB9EA4 = 1;
		dword_6FBB9EA8 = 0;
		if (dword_6FBB9F68 == 1)
		{
			uVar10 = 7;
			dword_6FBB9F68 = 0;
			pHVar4 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar10);
		}
	}
	dword_6FBB9EA4 = 0;
	iVar7 = sub_6FB23230(0x18);
	if (iVar7 == 0)
	{
		sub_6FB1C1C0();
		sub_6FB1C450();
	}
	if (dword_6FBB9E98 != 0)
	{
		sub_6FAD6EB0(dword_6FBB9E98);
	}
}

//D2Client.0x6FB1BE70
// TODO: decompilation needs review (unaff_)
uint32_t __fastcall sub_6FB1BE70(int* a1)
{
	Font nFontSize;
	DWORD DVar1;
	uint32_t* puVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t* puVar6;
	int iVar7;
	uint32_t uVar8;
	int unaff_ESI;
	uint32_t* puVar9;
	uint32_t uVar10;
	uint32_t* puStack_20;
	uint32_t* puStack_1c;
	uint32_t uStack_18;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	if (a1 == nullptr)
	{
		FOG_DisplayAssert("pTextNode != NULL", __FILE__, __LINE__);
		exit(-1);
	}
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
	DVar1 = timeGetTime();
	if (*(int*)((int)a1 + 0x1e) == 0)
	{
		*(DWORD*)((int)a1 + 0x1a) = DVar1;
		*(DWORD*)((int)a1 + 0x1e) = DVar1;
	}
	else
	{
		iVar7 = *(int*)((int)a1 + 0x22);
		iVar3 = 0;
		if (*(DWORD*)((int)a1 + 0x1a) == DVar1)
		{
			if (iVar7 == 0)
			{
				*(short*)((int)a1 + 0x2a) = *(short*)((int)a1 + 0x2a) + 1;
			}
			else
			{
				iVar3 = *(int*)((int)a1 + 0x26) + iVar7;
				*(int*)((int)a1 + 0x26) = iVar3;
			}
		}
		else
		{
			*(uint32_t*)((int)a1 + 0x26) = 0;
			if ((iVar7 == 0) && (*(uint16_t*)((int)a1 + 0x2a) != 0))
			{
				*(uint32_t*)((int)a1 + 0x22) =
				    (DVar1 - *(DWORD*)((int)a1 + 0x1a)) / (uint32_t) * (uint16_t*)((int)a1 + 0x2a);
			}
			*(DWORD*)((int)a1 + 0x1a) = DVar1;
		}
		a1[2] = (iVar3 + (DVar1 - *(int*)((int)a1 + 0x1e) >> 2)) * a1[3];
	}
	if ((dword_6FBB9F1E == 0) && ((dword_6FBB9EDE != 0 || (dword_6FBB9EE2 != 0))))
	{
		sub_6FB5B0F0(dword_6FBB9F54, dword_6FB8D220 + -5, 0x145, 0x7a, 0, (DrawMode)(1));
		iStack_10 = dword_6FBB9F54 + -1;
		iStack_8 = dword_6FBB9F54 + 0x146;
		iStack_c = dword_6FB8D220 + -6;
		iStack_4 = dword_6FB8D220 + 0x75;
		sub_6FB21790(&iStack_10);
	}
	puVar9 = (uint32_t*)*a1;
	puStack_1c = nullptr;
	uStack_18 = 0;
	uVar10 = a1[2];
	puVar6 = nullptr;
	uVar8 = 0;
	puStack_20 = nullptr;
	if ((uVar10 != 0) && (puVar9 != nullptr))
	{
		do
		{
			if (uVar10 < 0x17800)
			{
				if ((dword_6FBB9EDE != 0) || (dword_6FBB9EE2 != 0))
				{
					D2Win_10117_DrawText((Unicode*)*puVar9, dword_6FBB9F54 + 0x10, dword_6FB8D220 + (0x70 - (uVar10 >> 10)), 0, 0);
				}
				puVar6 = puStack_20;
				puStack_1c = puVar9;
				uStack_18 = uVar10;
				if (puStack_20 == nullptr)
				{
					puVar6 = puVar9;
					uVar8 = uVar10;
					puStack_20 = puVar9;
				}
			}
			if (uVar10 < 0x4800)
				break;
			puVar9 = (uint32_t*)puVar9[1];
			uVar10 = uVar10 - 0x4800;
		} while (puVar9 != nullptr);
		if ((puVar6 != nullptr) &&
		    (puVar9 = (uint32_t*)*a1, (uint32_t*)*a1 != puVar6))
		{
			do
			{
				puVar2 = puVar9;
				puVar9 = (uint32_t*)puVar2[1];
			} while ((uint32_t*)puVar2[1] != puVar6);
			if (puVar2 != nullptr)
			{
				iVar3 = 0x5e - (uVar8 >> 10);
				iVar7 = iVar3;
				if (0x11 < iVar3)
				{
					iVar7 = 0x12;
				}
				if ((dword_6FBB9EDE != 0) || (dword_6FBB9EE2 != 0))
				{
					D2Win_10119_DrawCroppedText((Unicode*)*puVar2, dword_6FBB9F54 + 0x10, dword_6FB8D220 + iVar3, 3, 0, iVar7, unaff_ESI);
				}
			}
		}
		if ((puStack_1c != nullptr) &&
		    (puVar9 = (uint32_t*)puStack_1c[1], puVar9 != nullptr))
		{
			iVar3 = -(uStack_18 + 0x400 >> 10);
			iVar7 = iVar3 + 0x12;
			iVar4 = D2Win_10125();
			if ((iVar7 < iVar4) && ((dword_6FBB9EDE != 0 || (dword_6FBB9EE2 != 0))))
			{
				D2Win_10119_DrawCroppedText((Unicode*)*puVar9, dword_6FBB9F54 + 0x10, dword_6FB8D220 + iVar3 + 0x83, 0, iVar7,
				    iVar4 - iVar7, unaff_ESI);
			}
		}
		if ((puStack_20 != nullptr) || (puStack_1c != nullptr))
			goto LAB_6fb1c15f;
	}
	uVar10 = a1[2];
	puVar9 = (uint32_t*)*a1;
	for (puVar6 = (uint32_t*)((uint32_t*)*a1)[1]; puVar6 != nullptr;
	     puVar6 = (uint32_t*)puVar6[1])
	{
		uVar10 = uVar10 - 0x4800;
		puVar9 = puVar6;
	}
	if (uVar10 < 0x1c000)
	{
		iVar7 = 0x70 - (uVar10 + 0x400 >> 10);
		if (iVar7 < 0x12)
		{
			iVar3 = iVar7;
			if (iVar7 == 0)
				goto LAB_6fb1c15f;
		}
		else
		{
			iVar3 = 0x12;
		}
		if ((dword_6FBB9EDE != 0) || (dword_6FBB9EE2 != 0))
		{
			D2Win_10119_DrawCroppedText((Unicode*)*puVar9, dword_6FBB9F54 + 0x10, dword_6FB8D220 + iVar7, 3, 0, iVar3, unaff_ESI);
		}
	}
LAB_6fb1c15f:
	D2Win_10127_SetFont(nFontSize);
	iVar7 = a1[1] + -1;
	if (iVar7 < 1)
	{
		iVar7 = 1;
	}
	if (iVar7 * 0x12 + 0x70U < (uint32_t)a1[2] >> 10)
	{
		uVar5 = 1;
		if (dword_6FBB9F64 == 1)
		{
			dword_6FBB9F64 = 0;
			return uVar5;
		}
	}
	else
	{
		uVar5 = 0;
	}
	return uVar5;
}

//D2Client.0x6FB1C1C0
void __cdecl sub_6FB1C1C0()
{
	int nY;
	D2SplittedTextStrc* pDVar1;
	void* pvVar2;
	void* pvVar3;
	void* pFree;
	void* pvVar4;
	bool bVar5;
	Font nFontSize;
	int iVar6;
	int iVar7;
	D2SplittedTextStrc* pFree_00;
	DWORD DVar8;
	int nX;
	Unicode* pUVar9;
	int iStack_33c;
	int iStack_338;
	int iStack_334;
	int iStack_330;
	int iStack_324;
	Unicode aUStack_320[400];

	if (word_6FBB9ED0 == 0)
	{
		return;
	}
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	pvVar2 = ptr_6FBB9ECC;
	iStack_330 = 0x14;
	iVar6 = sub_6FB23230(0x13);
	if (iVar6 != 0)
	{
		iStack_330 = 0x5f;
	}
	iVar6 = 0;
	nX = 0xf;
	iStack_334 = 0;
	bVar5 = false;
	iVar7 = sub_6FAB5750();
	pvVar4 = ptr_6FBB9ECC;
	if (iVar7 != 1)
	{
		if (iVar7 != 2)
			goto joined_r0x6fb1c23d;
		nX = gnScreenWidth / 2 + 0xf;
	}
	bVar5 = true;
joined_r0x6fb1c23d:
	for (; ptr_6FBB9ECC = (uint8_t*)(pvVar4), pvVar2 != nullptr; pvVar2 = *(void**)((int)pvVar2 + 0x22))
	{
		iStack_338 = 0;
		do
		{
			pUVar9 = *(Unicode**)((int)pvVar2 + iStack_338 * 4);
			if (pUVar9 != nullptr)
			{
				if (bVar5)
				{
					Unicode::strcpy(aUStack_320, *(Unicode**)((int)pvVar2 + iStack_338 * 4));
					pFree_00 = D2Win_10199(aUStack_320, &iStack_324, 300);
					if (pFree_00 != nullptr)
					{
						iVar7 = iStack_330 + iVar6 * 0xf;
						do
						{
							pDVar1 = pFree_00->pNextLine;
							iVar6 = Unicode::strlen(pFree_00->wszLine);
							iVar6 = D2Win_10123(pFree_00->wszLine, iVar6);
							if (iVar6 != 0)
							{
								sub_6FB5B0F0(nX + -5, iVar7 + -0xe, iVar6 + 10, 0x10, 0, (DrawMode)(1));
								D2Win_10117_DrawText(pFree_00->wszLine, nX, iVar7, *(int*)((int)pvVar2 + 0x1a), 0);
								iStack_334 = iStack_334 + 1;
								iVar7 = iVar7 + 0xf;
							}
							D2_FREE(pFree_00->wszLine);
							D2_FREE(pFree_00);
							pFree_00 = pDVar1;
							iVar6 = iStack_334;
						} while (pDVar1 != nullptr);
					}
				}
				else
				{
					iVar7 = Unicode::strlen(pUVar9);
					iVar7 = D2Win_10123(*(Unicode**)((int)pvVar2 + iStack_338 * 4), iVar7);
					if (iVar7 != 0)
					{
						nY = iStack_330 + iVar6 * 0xf;
						sub_6FB5B0F0(nX + -4, nY + -0xe, iVar7 + 8, 0x10, 0, (DrawMode)(1));
						D2Win_10117_DrawText(*(Unicode**)((int)pvVar2 + iStack_338 * 4), nX, nY,
						    *(int*)((int)pvVar2 + 0x1a), 0);
						iStack_334 = iVar6 + 1;
						iVar6 = iStack_334;
					}
				}
			}
			iStack_338 = iStack_338 + 1;
		} while (iStack_338 < 6);
		pvVar4 = ptr_6FBB9ECC;
	}
	DVar8 = GetTickCount();
	pvVar2 = nullptr;
	while (pvVar4 != nullptr)
	{
		if (*(uint32_t*)((int)pvVar4 + 0x1e) < DVar8)
		{
			word_6FBB9ED0 = word_6FBB9ED0 + -1;
			pvVar3 = *(void**)((int)pvVar4 + 0x22);
			if (ptr_6FBB9ECC == pvVar4)
			{
				ptr_6FBB9ECC = (uint8_t*)(pvVar3);
			}
			iVar6 = 0;
			do
			{
				pFree = *(void**)((int)pvVar4 + iVar6 * 4);
				if (pFree != nullptr)
				{
					D2_FREE(pFree);
				}
				iVar6 = iVar6 + 1;
			} while (iVar6 < 6);
			D2_FREE(pvVar4);
			pvVar4 = pvVar3;
			if (pvVar2 != nullptr)
			{
				*(void**)((int)pvVar2 + 0x22) = pvVar3;
			}
		}
		else
		{
			pvVar2 = pvVar4;
			pvVar4 = *(void**)((int)pvVar4 + 0x22);
		}
	}
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FB1C450
void __cdecl sub_6FB1C450()
{
	void* pvVar1;
	void* pFree;
	void* pvVar2;
	void* pFree_00;
	Font nFontSize;
	int iVar3;
	int iVar4;
	DWORD DVar5;
	int nX;
	uint32_t* puVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	uint32_t* puStack_10;
	int iStack_c;
	int iStack_8;

	if (word_6FBB9ED6 == 0)
	{
		return;
	}
	nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	pvVar2 = ptr_6FBB9ED2;
	puStack_10 = (uint32_t*)ptr_6FBB9ED2;
	nX = 0xf;
	iVar3 = sub_6FB23230(6);
	if ((iVar3 != 0) || (iVar3 = sub_6FB23230(0x11), iVar3 != 0))
	{
		nX = 100;
	}
	if (pvVar2 != nullptr)
	{
		iStack_8 = 0;
		iStack_c = 0;
		do
		{
			iVar3 = 0;
			puVar6 = puStack_10;
			do
			{
				if ((Unicode*)*puVar6 != nullptr)
				{
					uVar9 = 1;
					uVar8 = 0;
					iVar7 = 0x10;
					iVar4 = Unicode::strlen((Unicode*)*puVar6);
					iVar4 = D2Win_10123((Unicode*)*puVar6, iVar4);
					sub_6FB5B0F0(nX + -5, (iStack_c - iVar3 / 2) + -0x81 + gnScreenHeight, iVar4 + 10, iVar7, uVar8,
					    (DrawMode)(uVar9));
					D2Win_10117_DrawText((Unicode*)*puVar6, nX, (iStack_8 - iVar3 / 2) + -0x73 + gnScreenHeight,
					    *(int*)((int)puStack_10 + 0x1a), 0);
				}
				iVar3 = iVar3 + 0x19;
				puVar6 = puVar6 + 1;
			} while (iVar3 < 0x96);
			puStack_10 = *(uint32_t**)((int)puStack_10 + 0x22);
			iStack_c = iStack_c + -0x19;
			iStack_8 = iStack_8 + -0x19;
		} while (puStack_10 != nullptr);
	}
	pFree_00 = ptr_6FBB9ED2;
	DVar5 = GetTickCount();
	pvVar2 = nullptr;
	while (pFree_00 != nullptr)
	{
		if (*(uint32_t*)((int)pFree_00 + 0x1e) < DVar5)
		{
			word_6FBB9ED6 = word_6FBB9ED6 + -1;
			pvVar1 = *(void**)((int)pFree_00 + 0x22);
			if (ptr_6FBB9ED2 == pFree_00)
			{
				ptr_6FBB9ED2 = (uint8_t*)(pvVar1);
			}
			iVar3 = 0;
			do
			{
				pFree = *(void**)((int)pFree_00 + iVar3 * 4);
				if (pFree != nullptr)
				{
					D2_FREE(pFree);
				}
				iVar3 = iVar3 + 1;
			} while (iVar3 < 6);
			D2_FREE(pFree_00);
			pFree_00 = pvVar1;
			if (pvVar2 != nullptr)
			{
				*(void**)((int)pvVar2 + 0x22) = pvVar1;
			}
		}
		else
		{
			pvVar2 = pFree_00;
			pFree_00 = *(void**)((int)pFree_00 + 0x22);
		}
	}
	D2Win_10127_SetFont(nFontSize);
}

//D2Client.0x6FB1C600
void __fastcall sub_6FB1C600(Unicode* pUnicode, uint32_t a2)
{
	uint16_t* puVar1;
	D2SplittedTextStrc* pDVar2;
	void* pvVar3;
	void* pvVar4;
	uint32_t* puVar5;
	DWORD DVar6;
	D2SplittedTextStrc* pFree;
	uint32_t uVar7;
	void* pvVar8;
	int iVar9;
	uint32_t* puVar10;
	uint32_t uStack_c;
	uint32_t local_8;
	Font FStack_4;

	local_8 = a2;
	puVar5 = (uint32_t*)D2_ALLOC(0x26);
	puVar10 = puVar5;
	for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1)
	{
		*puVar10 = 0;
		puVar10 = puVar10 + 1;
	}
	*(uint16_t*)puVar10 = 0;
	iVar9 = 0;
	*(uint32_t*)((int)puVar5 + 0x22) = 0;
	DVar6 = GetTickCount();
	*(DWORD*)((int)puVar5 + 0x1e) = DVar6 + 10000;
	FStack_4 = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	pFree = D2Win_10199(pUnicode, (int*)&uStack_c, gnScreenWidth + -0x46);
	uVar7 = uStack_c;
	if (6 < uStack_c)
	{
		uVar7 = 6;
	}
	*(short*)(puVar5 + 6) = (short)uVar7;
	if (0 < (int)uStack_c)
	{
		do
		{
			if (iVar9 < (int)(uint32_t) * (uint16_t*)(puVar5 + 6))
			{
				puVar5[iVar9] = (uint32_t)(pFree->wszLine);
			}
			else
			{
				D2_FREE(pFree->wszLine);
			}
			pDVar2 = pFree->pNextLine;
			D2_FREE(pFree);
			iVar9 = iVar9 + 1;
			a2 = local_8;
			pFree = pDVar2;
		} while (iVar9 < (int)uStack_c);
	}
	*(uint32_t*)((int)puVar5 + 0x1a) = a2 & 0xff;
	puVar10 = puVar5;
	if (ptr_6FBB9ECC != nullptr)
	{
		uVar7 = 0;
		pvVar4 = *(void**)((int)ptr_6FBB9ECC + 0x22);
		pvVar8 = ptr_6FBB9ECC;
		while (pvVar3 = pvVar4, pvVar3 != nullptr)
		{
			uVar7 = uVar7 + 1;
			pvVar8 = pvVar3;
			pvVar4 = *(void**)((int)pvVar3 + 0x22);
		}
		D2_ASSERT((uVar7 & 0xffff) == (word_6FBB9ED0 & 0xffff) - 1);
		*(uint32_t**)((int)pvVar8 + 0x22) = puVar5;
		puVar10 = (uint32_t*)ptr_6FBB9ECC;
	}
	ptr_6FBB9ECC = (uint8_t*)(puVar10);
	sub_6FB1C830((int)puVar5);
	uVar7 = word_6FBB9ED0;
	pvVar4 = ptr_6FBB9ECC;
	word_6FBB9ED0 = word_6FBB9ED0 + 1;
	iVar9 = 0;
	pvVar8 = ptr_6FBB9ECC;
	if (ptr_6FBB9ECC != nullptr)
	{
		do
		{
			puVar1 = (uint16_t*)((int)pvVar8 + 0x18);
			pvVar8 = *(void**)((int)pvVar8 + 0x22);
			iVar9 = iVar9 + (uint32_t)*puVar1;
		} while (pvVar8 != nullptr);
		if (0x12 < iVar9)
		{
			ptr_6FBB9ECC = (uint8_t*)(*(void**)((int)ptr_6FBB9ECC + 0x22));
			iVar9 = 0;
			word_6FBB9ED0 = uVar7;
			do
			{
				pvVar8 = *(void**)((int)pvVar4 + iVar9 * 4);
				if (pvVar8 != nullptr)
				{
					D2_FREE(pvVar8);
				}
				iVar9 = iVar9 + 1;
			} while (iVar9 < 6);
			D2_FREE(pvVar4);
		}
	}
	sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
	iVar9 = sub_6FB23230(0x18);
	if ((iVar9 != 0) && (gpint32_t_6FBB9E9C != nullptr))
	{
		(**(code**)(*gpint32_t_6FBB9E9C + 0x3c))();
		for (puVar10 = gpuint32_t_6FBB9ED8; puVar10 != nullptr;
		     puVar10 = *(uint32_t**)((int)puVar10 + 0x22))
		{
			(**(code**)(*gpint32_t_6FBB9E9C + 0x30))(*puVar10, puVar10[1], puVar10[2], puVar10[3], puVar10[4], puVar10[5], 0,
			    *(uint32_t*)((int)puVar10 + 0x1a), 0, 0xd);
		}
	}
	D2Win_10127_SetFont(FStack_4);
}

//D2Client.0x6FB1C830
void __fastcall sub_6FB1C830(int a12)
{
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* puVar2;
	uint32_t* puVar3;
	int iVar4;
	Unicode* a1;
	int iVar5;
	uint32_t* puVar6;
	int nLine;
	int n0;

	puVar3 = (uint32_t*)D2_ALLOC(0x26);
	puVar6 = puVar3;
	for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		*puVar6 = 0;
		puVar6 = puVar6 + 1;
	}
	*(uint16_t*)puVar6 = 0;
	iVar5 = 0;
	if (*(short*)(a12 + 0x18) != 0)
	{
		puVar6 = (uint32_t*)a12;
		do
		{
			n0 = 0;
			nLine = 0x9d0;
			iVar4 = Unicode::strlen((Unicode*)*puVar6);
			a1 = (Unicode*)FOG_Alloc(iVar4 * 2 + __LINE__, __FILE__, nLine, n0);
			*(Unicode**)((int)puVar6 + ((int)puVar3 - a12)) = a1;
			Unicode::strcpy(a1, (Unicode*)*puVar6);
			iVar5 = iVar5 + 1;
			puVar6 = puVar6 + 1;
		} while (iVar5 < (int)(uint32_t) * (uint16_t*)(a12 + 0x18));
	}
	*(uint16_t*)(puVar3 + 6) = *(uint16_t*)(a12 + 0x18);
	*(uint32_t*)((int)puVar3 + 0x1a) = *(uint32_t*)(a12 + 0x1a);
	if ((0x7f < (uint16_t)word_6FBB9EDC) && (gpuint32_t_6FBB9ED8 != nullptr))
	{
		puVar2 = *(uint32_t**)((int)gpuint32_t_6FBB9ED8 + 0x22);
		puVar6 = nullptr;
		pFree = gpuint32_t_6FBB9ED8;
		while (puVar1 = puVar2, puVar1 != nullptr)
		{
			puVar6 = pFree;
			pFree = puVar1;
			puVar2 = *(uint32_t**)((int)puVar1 + 0x22);
		}
		iVar5 = 0;
		do
		{
			if ((void*)pFree[iVar5] != nullptr)
			{
				D2_FREE((void*)pFree[iVar5]);
			}
			iVar5 = iVar5 + 1;
		} while (iVar5 < 6);
		D2_FREE(pFree);
		if (puVar6 != nullptr)
		{
			*(uint32_t*)((int)puVar6 + 0x22) = 0;
		}
		if (word_6FBB9EDC != 0)
		{
			word_6FBB9EDC = word_6FBB9EDC + -1;
		}
	}
	*(uint32_t**)((int)puVar3 + 0x22) = gpuint32_t_6FBB9ED8;
	word_6FBB9EDC = word_6FBB9EDC + 1;
	gpuint32_t_6FBB9ED8 = puVar3;
}

//D2Client.0x6FB1C950
void __fastcall sub_6FB1C950(int a1, int a22)
{
	Unicode* a2;
	void* pvVar1;
	void* pvVar2;
	Font nFontSize;
	uint32_t* puVar3;
	DWORD DVar4;
	int iVar5;
	void* pvVar6;
	int iVar7;
	uint32_t uVar8;
	uint32_t uVar9;
	int nTextLength;
	int iVar10;
	uint32_t* puVar11;
	char acStack_400[1024];

	nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	puVar3 = (uint32_t*)D2_ALLOC(0x26);
	puVar11 = puVar3;
	for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar11 = 0;
		puVar11 = puVar11 + 1;
	}
	*(uint16_t*)puVar11 = 0;
	*(uint32_t*)((int)puVar3 + 0x22) = 0;
	DVar4 = GetTickCount();
	*(DWORD*)((int)puVar3 + 0x1e) = DVar4 + 10000;
	iVar5 = Unicode::strlen((Unicode*)a1);
	*(uint16_t*)(puVar3 + 6) = 0;
	iVar7 = iVar5;
	iVar10 = 0;
	while (true)
	{
		while ((nTextLength = iVar7, 0 < nTextLength &&
		                                 (iVar7 = D2Win_10123((Unicode*)(a1 + iVar10 * 2), nTextLength),
		                                     gnScreenWidth + -0x46 < iVar7)))
		{
			iVar7 = nTextLength + -1;
		}
		if (iVar10 + nTextLength != iVar5)
		{
			while ((0 < nTextLength &&
			        (iVar7 = Unicode::isLineBreak((Unicode*)(a1 + iVar10 * 2), nTextLength + 1),
			            iVar7 == 0)))
			{
				nTextLength = nTextLength + -1;
			}
		}
		if (nTextLength == 0)
			break;
		a2 = (Unicode*)(a1 + iVar10 * 2);
		Unicode::toUtf(acStack_400, a2, nTextLength);
		if (5 < *(uint16_t*)(puVar3 + 6))
			break;
		uVar9 = nTextLength * 2 + 2;
		pvVar6 = D2_ALLOC(uVar9);
		puVar3[*(uint16_t*)(puVar3 + 6)] = (uint32_t)(pvVar6);
		puVar11 = (uint32_t*)puVar3[*(uint16_t*)(puVar3 + 6)];
		for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1)
		{
			*puVar11 = 0;
			puVar11 = puVar11 + 1;
		}
		for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1)
		{
			*(uint8_t*)puVar11 = 0;
			puVar11 = (uint32_t*)((int)puVar11 + 1);
		}
		Unicode::strncpy((Unicode*)puVar3[*(uint16_t*)(puVar3 + 6)], a2, nTextLength);
		*(short*)(puVar3 + 6) = *(short*)(puVar3 + 6) + 1;
		iVar7 = iVar5 - nTextLength;
		iVar10 = nTextLength;
	}
	*(uint32_t*)((int)puVar3 + 0x1a) = a22 & 0xff;
	puVar11 = puVar3;
	if (ptr_6FBB9ED2 != nullptr)
	{
		uVar9 = 0;
		pvVar1 = *(void**)((int)ptr_6FBB9ED2 + 0x22);
		pvVar6 = ptr_6FBB9ED2;
		while (pvVar2 = pvVar1, pvVar2 != nullptr)
		{
			uVar9 = uVar9 + 1;
			pvVar6 = pvVar2;
			pvVar1 = *(void**)((int)pvVar2 + 0x22);
		}
		D2_ASSERT((uVar9 & 0xffff) == (uint16_t)word_6FBB9ED6 - 1);
		*(uint32_t**)((int)pvVar6 + 0x22) = puVar3;
		puVar11 = (uint32_t*)ptr_6FBB9ED2;
	}
	ptr_6FBB9ED2 = (uint8_t*)(puVar11);
	word_6FBB9ED6 = word_6FBB9ED6 + 1;
	sub_6FB1C830((int)puVar3);
	pvVar6 = ptr_6FBB9ED2;
	if (2 < (uint16_t)word_6FBB9ED6)
	{
		iVar7 = 0;
		ptr_6FBB9ED2 = (uint8_t*)(*(void**)((int)ptr_6FBB9ED2 + 0x22));
		do
		{
			pvVar1 = *(void**)((int)pvVar6 + iVar7 * 4);
			if (pvVar1 != nullptr)
			{
				D2_FREE(pvVar1);
			}
			iVar7 = iVar7 + 1;
		} while (iVar7 < 6);
		D2_FREE(pvVar6);
		word_6FBB9ED6 = word_6FBB9ED6 + -1;
	}
	iVar7 = sub_6FB23230(0x18);
	if ((iVar7 != 0) && (gpint32_t_6FBB9E9C != nullptr))
	{
		(**(code**)(*gpint32_t_6FBB9E9C + 0x3c))();
		for (puVar11 = gpuint32_t_6FBB9ED8; puVar11 != nullptr;
		     puVar11 = *(uint32_t**)((int)puVar11 + 0x22))
		{
			(**(code**)(*gpint32_t_6FBB9E9C + 0x30))(*puVar11, puVar11[1], puVar11[2], puVar11[3], puVar11[4], puVar11[5], 0,
			    *(uint32_t*)((int)puVar11 + 0x1a), 0, 0xd);
		}
	}
	D2Win_10127_SetFont(nFontSize);
	sub_6FB55820(6, nullptr, 0.0, 0.0, 0);
}

//D2Client.0x6FB1CBD0
void __fastcall sub_6FB1CBD0(uint8_t* a1, uint32_t a2)
{
	gpuint8_t_6FBB9F58 = a1;
	dword_6FBB9F5C = a2;
}

//D2Client.0x6FB1CBE0
void __cdecl sub_6FB1CBE0()
{
	int iVar1;

	if (dword_6FBB9F60 != 0)
	{
		iVar1 = sub_6FB556F0(dword_6FBB9F60);
		if (iVar1 != 0)
		{
			sub_6FB55BF0(iVar1, 0, 0, 4);
		}
		dword_6FBB9F60 = 0;
	}
	dword_6FBB9F33 = 0;
}

//D2Client.0x6FB1CC20
void __fastcall sub_6FB1CC20(D2UnitStrc* pUnit, uint32_t a2, uint32_t a3)
{
	uint32_t* puVar1;
	int iVar2;
	Font nFontSize;
	Unicode* pUVar3;
	uint32_t* puVar4;
	Font nFontSize_00;
	uint32_t* puVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	HWND__* pHVar8;
	float fVar9;
	float fVar10;
	uint32_t uVar11;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	dword_6FBB9F54 = (gnScreenWidth + -0x145) / 2;
	dword_6FBB9F1E = 0;
	dword_6FB8D220 = 0xc;
	dword_6FBB9F18 = 0;
	sub_6FAABF30();
	if (dword_6FBB9F60 != 0)
	{
		iVar2 = sub_6FB556F0(dword_6FBB9F60);
		if (iVar2 != 0)
		{
			sub_6FB55BF0(iVar2, 0, 0, 4);
		}
		dword_6FBB9F60 = 0;
	}
	puVar5 = gpuint32_t_6FBB9F38;
	dword_6FBB9F33 = 0;
	if (pUnit == nullptr)
	{
		if (dword_6FBB9EAC != 0)
		{
			if (gpuint32_t_6FBB9F38 != nullptr)
			{
				puVar4 = (uint32_t*)*gpuint32_t_6FBB9F38;
				while (puVar4 != nullptr)
				{
					puVar1 = (uint32_t*)puVar4[1];
					D2_FREE((void*)*puVar4);
					D2_FREE(puVar4);
					puVar4 = puVar1;
				}
				D2_FREE(puVar5);
				gpuint32_t_6FBB9F38 = nullptr;
			}
			dword_6FBB9EAC = 0;
		}
		dword_6FBB9EF2 = 0;
		dword_6FBB9EEA = 0;
	}
	else
	{
		if (((dword_6FBB9EF2 != 0) &&
		        (pDVar7 = sub_6FB269F0(dword_6FBB9EEA, 1), pDVar7 != nullptr)) &&
		    (pDVar7 != pUnit))
		{
			sub_6FAADA40(D2C_ZEXT(0x30), 1, dword_6FBB9EEA);
			sub_6FAF7950(dword_6FBB9EEA);
		}
		dword_6FBB9EF2 = 1;
		dword_6FBB9EEA = pUnit->dwUnitId;
	}
	iStack_c = dword_6FB8D220;
	iStack_4 = dword_6FB8D220 + 0xb6;
	if (gnScreenHeight + -0x35 <= dword_6FB8D220 + 0xb6)
	{
		iStack_4 = gnScreenHeight + -0x35;
	}
	iStack_10 = dword_6FBB9F54 + -10;
	iStack_8 = dword_6FBB9F54 + 0x14f;
	sub_6FAB6450((uint32_t*)(&iStack_10));
	sub_6FAB5D40();
	word_6FBB9EFA = (uint16_t)a2;
	if (gpuint32_t_6FBB9E90 == nullptr)
	{
		dword_6FBB9EA4 = 0;
		nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex((uint16_t)a2));
		puVar4 = (uint32_t*)D2_ALLOC(0x2c);
		nFontSize_00 = D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
		puVar5 = sub_6FB1CF10((short*)pUVar3, (int*)(puVar4 + 1), (uint16_t*)(puVar4 + 5));
		*puVar4 = (uint32_t)(puVar5);
		*(uint16_t*)(puVar4 + 4) = 0x145;
		*(uint16_t*)((int)puVar4 + 0x12) = 0x70;
		*(uint32_t*)((int)puVar4 + 0x1a) = 0;
		*(uint32_t*)((int)puVar4 + 0x1e) = 0;
		*(uint32_t*)((int)puVar4 + 0x22) = 0;
		*(uint32_t*)((int)puVar4 + 0x26) = 0;
		*(uint16_t*)((int)puVar4 + 0x2a) = 0;
		D2Win_10127_SetFont(nFontSize_00);
		iVar2 = 0;
		puVar5 = (uint32_t*)*puVar4;
		puVar4[2] = 0;
		puVar4[3] = (uint32_t) * (uint16_t*)(puVar4 + 5);
		for (; puVar5 != nullptr; puVar5 = (uint32_t*)puVar5[1])
		{
			iVar6 = D2Win_10121_GetTextWidth((Unicode*)*puVar5);
			if (iVar2 <= iVar6)
			{
				iVar2 = iVar6;
			}
		}
		*(short*)(puVar4 + 4) = (short)iVar2 + 0x14;
		*(short*)((int)puVar4 + 0x12) = *(short*)(puVar4 + 1) * 0xf + 6;
		gpuint32_t_6FBB9E90 = puVar4;
		D2Win_10127_SetFont(nFontSize);
		sub_6FB55F60();
		dword_6FBB9F33 = 0;
		iVar2 = sub_6FB467A0((uint16_t)a2);
		if (iVar2 != 0)
		{
			sub_6FB50290(pUnit);
			iVar6 = 0;
			fVar10 = 0.0;
			fVar9 = 7.00649e-45;
			pDVar7 = CUNIT_GetPlayer();
			dword_6FBB9F33 = sub_6FB55820(iVar2, pDVar7, fVar9, fVar10, iVar6);
			dword_6FBB9F60 = iVar2;
		}
		*(uint32_t*)((int)gpuint32_t_6FBB9E90 + 0x16) = 0;
		dword_6FBB9EA8 = 1;
		if (dword_6FBB9F68 == 0)
		{
			dword_6FBB9F68 = 1;
			byte_6FBB9F14 = GetTickCount();
			uVar11 = 7;
			pHVar8 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar8, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar11);
		}
	}
}

//D2Client.0x6FB1CF10
uint32_t* __fastcall sub_6FB1CF10(short* a1, int* a2, uint16_t* a3)
{
	uint16_t uVar1;
	bool bVar2;
	uint32_t* puVar3;
	uint32_t* puVar4;
	Unicode* pUVar5;
	int iVar6;
	int iVar7;
	uint32_t* local_1d8;
	uint32_t* local_1d0;
	Unicode local_1cc;
	uint32_t local_1ca[49];
	char acStack_104[100];
	CHAR aCStack_a0[80];
	CHAR aCStack_50[80];

	*a2 = 0;
	uVar1 = *a1;
	local_1d0 = nullptr;
	bVar2 = true;
	puVar3 = nullptr;
	do
	{
		if (uVar1 == 0)
		{
			return puVar3;
		}
		local_1cc.ch = 0;
		iVar7 = 99;
		puVar4 = local_1ca;
		for (iVar6 = 0x31; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*puVar4 = 0;
			puVar4 = puVar4 + 1;
		}
		*(uint16_t*)puVar4 = 0;
		pUVar5 = (Unicode*)local_1ca;
		do
		{
			pUVar5 = pUVar5 + 1;
			iVar7 = iVar7 + -1;
		} while (iVar7 != 0);
		iVar7 = 0;
		pUVar5 = &local_1cc;
		for (iVar6 = 0x32; iVar6 != 0; iVar6 = iVar6 + -1)
		{
			*(uint32_t*)pUVar5 = 0;
			pUVar5 = pUVar5 + 2;
		}
		do
		{
			if (*a1 == 10)
			{
				if ((iVar7 < 100) && (*a1 == 10))
				{
					a1 = (short*)((uint16_t*)a1 + 1);
				}
				break;
			}
			(&local_1cc)[iVar7].ch = *a1;
			iVar7 = iVar7 + 1;
			a1 = (short*)((uint16_t*)a1 + 1);
		} while (iVar7 < 100);
		puVar4 = (uint32_t*)D2_ALLOC(8);
		if (bVar2)
		{
			iVar6 = Unicode::strlen(&local_1cc);
			iVar7 = 0;
			if (iVar6 < 1)
			{
			LAB_6fb1cfe4:
				Unicode::toUtf(acStack_104, &local_1cc, 100);
				iVar6 = atoi(acStack_104);
				*a3 = (short)iVar6;
			}
			else
			{
				do
				{
					if (0x7f < (&local_1cc)[iVar7].ch)
					{
						bVar2 = false;
					}
					iVar7 = iVar7 + 1;
				} while (iVar7 < iVar6);
				if (bVar2)
					goto LAB_6fb1cfe4;
				wsprintfA(aCStack_a0, "line 0 of char does not contain scroll rate");
				*a3 = 8;
			}
			bVar2 = false;
			iVar7 = 0;
			pUVar5 = &local_1cc;
			for (iVar6 = 0x32; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*(uint32_t*)pUVar5 = 0;
				pUVar5 = pUVar5 + 2;
			}
			do
			{
				if (*a1 == 10)
				{
					if ((iVar7 < 100) && (*a1 == 10))
					{
						a1 = (short*)((uint16_t*)a1 + 1);
					}
					break;
				}
				(&local_1cc)[iVar7].ch = *a1;
				iVar7 = iVar7 + 1;
				a1 = (short*)((uint16_t*)a1 + 1);
			} while (iVar7 < 100);
		}
		iVar6 = Unicode::strlen(&local_1cc);
		iVar7 = D2Win_10121_GetTextWidth(&local_1cc);
		if (0x133 < iVar7)
		{
			wsprintfA(aCStack_50, "line %d of char is too long", *a2);
		}
		pUVar5 = (Unicode*)D2_ALLOC(iVar6 * 2 + 2);
		*puVar4 = (uint32_t)(pUVar5);
		Unicode::strcpy(pUVar5, &local_1cc);
		puVar4[1] = 0;
		local_1d8 = puVar4;
		if (local_1d0 != nullptr)
		{
			local_1d0[1] = (uint32_t)(puVar4);
			local_1d8 = puVar3;
		}
		*a2 = *a2 + 1;
		uVar1 = *a1;
		puVar3 = local_1d8;
		local_1d0 = puVar4;
	} while (true);
}

//D2Client.0x6FB1D110
void __fastcall sub_6FB1D110(uint32_t a1, int a2, int a3)
{
	int iVar1;
	Font nFontSize;
	Unicode* pUVar2;
	uint32_t* puVar3;
	Font nFontSize_00;
	uint32_t* puVar4;
	int iVar5;
	HWND__* pHVar6;
	D2UnitStrc* pDVar7;
	float fVar8;
	float fVar9;
	uint32_t uVar10;
	int local_10;
	int local_c;
	int local_8;
	int local_4;

	if (a2 != 0)
	{
		dword_6FB8D220 = 0x105 - dword_6FBBA74C;
		dword_6FBB9F54 = dword_6FBBA748;
	}
	else
	{
		dword_6FB8D220 = 0xc;
		dword_6FBB9F54 = (gnScreenWidth + -0x145) / 2;
	}
	dword_6FBB9F1E = (uint32_t)(a2 != 0);
	sub_6FAABF30();
	if (dword_6FBB9F60 != 0)
	{
		iVar1 = sub_6FB556F0(dword_6FBB9F60);
		if (iVar1 != 0)
		{
			sub_6FB55BF0(iVar1, 0, 0, 4);
		}
		dword_6FBB9F60 = 0;
	}
	local_c = dword_6FB8D220;
	dword_6FBB9F33 = 0;
	dword_6FBB9EF2 = 0;
	local_4 = dword_6FB8D220 + 0xb6;
	if (gnScreenHeight + -0x35 <= dword_6FB8D220 + 0xb6)
	{
		local_4 = gnScreenHeight + -0x35;
	}
	local_10 = dword_6FBB9F54 + -10;
	local_8 = dword_6FBB9F54 + 0x14f;
	sub_6FAB6450((uint32_t*)(&local_10));
	sub_6FAB5D40();
	word_6FBB9EFA = (uint16_t)a1;
	if (gpuint32_t_6FBB9E90 == nullptr)
	{
		dword_6FBB9EA4 = 0;
		nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex((uint16_t)a1));
		puVar3 = (uint32_t*)D2_ALLOC(0x2c);
		nFontSize_00 = D2Win_10127_SetFont(D2FONT_FONTFORMAL11);
		puVar4 = sub_6FB1CF10((short*)pUVar2, (int*)(puVar3 + 1), (uint16_t*)(puVar3 + 5));
		*puVar3 = (uint32_t)(puVar4);
		*(uint16_t*)(puVar3 + 4) = 0x145;
		*(uint16_t*)((int)puVar3 + 0x12) = 0x70;
		*(uint32_t*)((int)puVar3 + 0x1a) = 0;
		*(uint32_t*)((int)puVar3 + 0x1e) = 0;
		*(uint32_t*)((int)puVar3 + 0x22) = 0;
		*(uint32_t*)((int)puVar3 + 0x26) = 0;
		*(uint16_t*)((int)puVar3 + 0x2a) = 0;
		D2Win_10127_SetFont(nFontSize_00);
		iVar1 = 0;
		puVar4 = (uint32_t*)*puVar3;
		puVar3[2] = 0;
		puVar3[3] = (uint32_t) * (uint16_t*)(puVar3 + 5);
		for (; puVar4 != nullptr; puVar4 = (uint32_t*)puVar4[1])
		{
			iVar5 = D2Win_10121_GetTextWidth((Unicode*)*puVar4);
			if (iVar1 <= iVar5)
			{
				iVar1 = iVar5;
			}
		}
		*(short*)(puVar3 + 4) = (short)iVar1 + 0x14;
		*(short*)((int)puVar3 + 0x12) = *(short*)(puVar3 + 1) * 0xf + 6;
		gpuint32_t_6FBB9E90 = puVar3;
		D2Win_10127_SetFont(nFontSize);
		*(uint32_t*)((int)gpuint32_t_6FBB9E90 + 0x16) = 0;
		dword_6FBB9EA8 = 1;
		dword_6FBB9EE2 = 1;
		if (dword_6FBB9F68 == 0)
		{
			dword_6FBB9F68 = 1;
			byte_6FBB9F14 = GetTickCount();
			uVar10 = 7;
			pHVar6 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar6, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar10);
		}
		iVar1 = sub_6FB467A0((uint16_t)a1);
		if (iVar1 != 0)
		{
			iVar5 = 0;
			fVar9 = 0.0;
			fVar8 = 7.00649e-45;
			pDVar7 = CUNIT_GetPlayer();
			dword_6FBB9F33 = sub_6FB55820(iVar1, pDVar7, fVar8, fVar9, iVar5);
			dword_6FBB9F60 = iVar1;
		}
		if ((((((uint16_t)a1 == 0x7f) || ((uint16_t)a1 == 0x4e22)) || ((uint16_t)a1 == 0x4ec9)) || (((uint16_t)a1 == 0x4ea3 || ((uint16_t)a1 == 0x18c)))) && (a3 != 0))
		{
			dword_6FBB9F18 = 1;
		}
	}
}

//D2Client.0x6FB1D380
D2UnitStrc* __cdecl sub_6FB1D380()
{
	D2UnitStrc* pDVar1;

	if (dword_6FBB9EF2 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB9EEA, 1);
		return pDVar1;
	}
	if (dword_6FBB9EA8 != 0)
	{
		pDVar1 = sub_6FB269F0(dword_6FBB9EEE, 2);
		return pDVar1;
	}
	return nullptr;
}

//D2Client.0x6FB1D3C0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1D3C0(int a1)
{
	uint8_t* a2;
	uint8_t bVar1;
	char cVar2;
	uint8_t* pbVar3;
	D2ObjectsTxt* pDVar4;
	D2SuperUniquesTxt* pDVar5;
	D2UnitStrc* pDVar6;
	char* pcVar7;
	Unicode* pUVar8;
	Unicode* pUVar9;
	D2ActiveRoomStrc* pRoom;
	short sVar10;
	uint16_t index;
	uint32_t uVar11;
	uint8_t* pbVar12;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	uint32_t extraout_var_03;
	uint32_t extraout_var_04;
	char* pcVar13;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	uint32_t extraout_EDX_02;
	uint32_t extraout_EDX_03;
	uint32_t extraout_EDX_04;
	uint32_t uVar14;
	uint32_t extraout_EDX_05;
	uint32_t extraout_var_05;
	uint32_t extraout_var_06;
	uint32_t extraout_var_07;
	uint32_t extraout_var_08;
	uint32_t uVar15;
	uint16_t index_00;
	int iVar16;
	bool bVar17;
	int iVar18;
	Unicode* pUVar19;
	uint32_t uVar20;
	int iVar21;
	Unicode aUStack_2d4[16];
	Unicode aUStack_2b4[16];
	char acStack_294[16];
	Unicode aUStack_284[16];
	Unicode local_264[306];

	a2 = (uint8_t*)(a1 + 8);
	uVar11 = 0xffffffff;
	pbVar12 = a2;
	do
	{
		if (uVar11 == 0)
			break;
		uVar11 = uVar11 - 1;
		bVar1 = *pbVar12;
		pbVar12 = pbVar12 + 1;
	} while (bVar1 != 0);
	if (0xe < ~uVar11 - 1)
	{
		*(uint8_t*)(a1 + 0x17) = 0;
	}
	switch (*(uint8_t*)(a1 + 1))
	{
	case 0:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe37));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xe37;
		goto LAB_6fb1d9c9;
	case 1:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe38));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xe38;
		goto LAB_6fb1d9c9;
	case 2:
		pDVar6 = CUNIT_GetPlayer();
		if (pDVar6 != nullptr)
		{
			pDVar6 = CUNIT_GetPlayer();
			pbVar3 = (uint8_t*)sub_6FAB0C00(pDVar6);
			pbVar12 = a2;
			do
			{
				bVar1 = *pbVar12;
				bVar17 = bVar1 < *pbVar3;
				if (bVar1 != *pbVar3)
				{
				LAB_6fb1d5c8:
					iVar16 = (1 - (uint32_t)bVar17) - (uint32_t)(bVar17 != 0);
					goto LAB_6fb1d5cd;
				}
				if (bVar1 == 0)
					break;
				bVar1 = pbVar12[1];
				bVar17 = bVar1 < pbVar3[1];
				if (bVar1 != pbVar3[1])
					goto LAB_6fb1d5c8;
				pbVar12 = pbVar12 + 2;
				pbVar3 = pbVar3 + 2;
			} while (bVar1 != 0);
			iVar16 = 0;
		LAB_6fb1d5cd:
			uVar15 = extraout_var_00;
			if (iVar16 == 0)
				break;
		}
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe39));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		iVar16 = -1;
		pcVar13 = (char*)(a1 + 0x18);
		do
		{
			if (iVar16 == 0)
				break;
			iVar16 = iVar16 + -1;
			cVar2 = *pcVar13;
			pcVar13 = pcVar13 + 1;
		} while (cVar2 != '\0');
		if (iVar16 == -2)
		{
			sVar10 = 0xe39;
			goto LAB_6fb1d66b;
		}
		Unicode::win2Unicode(aUStack_2b4, (char*)(a1 + 0x18), 0x10);
		sVar10 = 0xe3b;
	LAB_6fb1d717:
		pUVar19 = aUStack_2b4;
		pUVar9 = aUStack_2d4;
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		Unicode::sprintf(0x132, local_264, pUVar8, pUVar9, pUVar19);
		uVar15 = extraout_var_02;
		break;
	case 3:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe3a));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		iVar16 = -1;
		pcVar13 = (char*)(a1 + 0x18);
		do
		{
			if (iVar16 == 0)
				break;
			iVar16 = iVar16 + -1;
			cVar2 = *pcVar13;
			pcVar13 = pcVar13 + 1;
		} while (cVar2 != '\0');
		if (iVar16 != -2)
		{
			Unicode::win2Unicode(aUStack_2b4, (char*)(a1 + 0x18), 0x10);
			sVar10 = 0xe3c;
			goto LAB_6fb1d717;
		}
		sVar10 = 0xe3a;
	LAB_6fb1d66b:
		pUVar8 = aUStack_2d4;
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		Unicode::sprintf(0x132, local_264, pUVar9, pUVar8);
		uVar15 = extraout_var_01;
		break;
	case 4:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe3d));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xe3d;
		goto LAB_6fb1d9c9;
	case 5:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe3e));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xe3e;
		goto LAB_6fb1d9c9;
	case 6:
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		cVar2 = *(char*)(a1 + 7);
		if (cVar2 == '\0')
		{
			iVar16 = -1;
			pcVar13 = (char*)(a1 + 0x18);
			do
			{
				if (iVar16 == 0)
					break;
				iVar16 = iVar16 + -1;
				cVar2 = *pcVar13;
				pcVar13 = pcVar13 + 1;
			} while (cVar2 != '\0');
			if (iVar16 == -2)
				goto LAB_6fb1d9b3;
			Unicode::win2Unicode(aUStack_284, (char*)(a1 + 0x18), 0x10);
			index_00 = 0xe40;
			pUVar9 = aUStack_284;
		}
		else if (cVar2 == '\x01')
		{
			if (*(char*)(a1 + 0x18) == '\0')
			{
				iVar16 = *(int*)(a1 + 3);
				if (((iVar16 < 0) || (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar16)) ||
				    (iVar16 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar16 * 0x1a8, iVar16 == 0))
				{
				LAB_6fb1d9b3:
					Unicode::strcpy(local_264, aUStack_2d4);
					sVar10 = 0xe41;
					goto LAB_6fb1d9c9;
				}
				index = *(uint16_t*)(iVar16 + 6);
				index_00 = 0xe3f;
			}
			else
			{
				index_00 = 0xe40;
				pDVar5 = DATATBLS_GetSuperUniquesTxtRecord((uint32_t) * (uint16_t*)(a1 + 0x18));
				if (pDVar5 == nullptr)
					goto LAB_6fb1d9b3;
				index = pDVar5->wNameStr;
			}
		LAB_6fb1d8bf:
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		}
		else
		{
			if ((cVar2 != '\x02') ||
			    (pDVar4 = DATATBLS_GetObjectsTxtRecord(*(int*)(a1 + 3)),
			        pDVar4 == nullptr))
				goto LAB_6fb1d9b3;
			index_00 = 0xe3f;
			if (*(int*)(a1 + 3) == 0xb)
			{
				index = 0xc98;
				goto LAB_6fb1d8bf;
			}
			pUVar9 = pDVar4->wszName;
		}
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(index_00));
		iVar16 = Unicode::strlen(pUVar8);
		iVar18 = Unicode::strlen(pUVar9);
		if (0x131 < iVar18 + 0x10 + iVar16)
		{
			iVar16 = Unicode::strlen(pUVar9);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(index_00));
			iVar18 = Unicode::strlen(pUVar9);
			iVar21 = Unicode::strlen(aUStack_2d4);
			FOG_Trace("text.cpp %d %d %d %d\n", (uint32_t)index_00, iVar21, iVar18, iVar16);
			return;
		}
		Unicode::strcpy(local_264, aUStack_2d4);
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(index_00));
		Unicode::strcat(local_264, pUVar8);
		Unicode::strcat(local_264, pUVar9);
		uVar15 = extraout_var_04;
		break;
	case 7:
		iVar16 = sub_6FAAFD60(*(int*)(a1 + 3));
		pDVar6 = CUNIT_GetPlayer();
		if (iVar16 == 0)
		{
			iVar18 = 0;
			do
			{
				cVar2 = (&byte_6FB9A828)[iVar18];
				acStack_294[iVar18] = cVar2;
				iVar18 = iVar18 + 1;
			} while (cVar2 != '\0');
		}
		else
		{
			pcVar7 = (char*)sub_6FAAF5D0(iVar16);
			pcVar13 = acStack_294;
			do
			{
				cVar2 = *pcVar7;
				pcVar7 = pcVar7 + 1;
				*pcVar13 = cVar2;
				pcVar13 = pcVar13 + 1;
			} while (cVar2 != '\0');
		}
		Unicode::win2Unicode(aUStack_2b4, acStack_294, 0x10);
		uVar14 = extraout_EDX;
		switch (*(uint8_t*)(a1 + 7))
		{
		case 1:
			sVar10 = 0x277a;
			goto LAB_6fb1dc23;
		case 2:
			pUVar9 = aUStack_2b4;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x277b));
			goto LAB_6fb1dc31;
		case 3:
			Unicode::strcpy(local_264, aUStack_2b4);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfba));
			Unicode::strcat(local_264, pUVar9);
			sub_6FB55820(0x10, nullptr, 0.0, 0.0, 0);
			sub_6FB1C950((int)local_264,
			    CONCAT31((int32_t)((uint32_t)extraout_EDX_00 >> 8), *(uint8_t*)(a1 + 2)));
			return;
		case 4:
			Unicode::strcpy(local_264, aUStack_2b4);
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfbb));
			Unicode::strcat(local_264, pUVar9);
			sub_6FB1C950((int)local_264,
			    CONCAT31((int32_t)((uint32_t)extraout_EDX_01 >> 8), *(uint8_t*)(a1 + 2)));
			return;
		case 5:
			Unicode::strcpy(local_264, aUStack_2b4);
			sVar10 = 0xfbc;
			break;
		case 6:
			Unicode::strcpy(local_264, aUStack_2b4);
			sVar10 = 0xfbd;
			break;
		case 7:
			Unicode::strcpy(local_264, aUStack_2b4);
			sVar10 = 0xfbe;
			break;
		case 8:
			pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfbf));
			Unicode::strcpy(local_264, pUVar9);
			Unicode::strcat(local_264, aUStack_2b4);
			uVar14 = extraout_EDX_02;
			goto switchD_6fb1da92_default;
		case 9:
			Unicode::strcpy(local_264, aUStack_2b4);
			sVar10 = 0xfc0;
			break;
		case 10:
			pUVar9 = aUStack_2b4;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x277c));
			goto LAB_6fb1dc31;
		case 0xb:
			sVar10 = 0x277d;
		LAB_6fb1dc23:
			pUVar9 = aUStack_2b4;
			pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		LAB_6fb1dc31:
			Unicode::sprintf(0x132, local_264, pUVar8, pUVar9);
			uVar14 = extraout_EDX_04;
		default:
			goto switchD_6fb1da92_default;
		}
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		Unicode::strcat(local_264, pUVar9);
		uVar14 = extraout_EDX_03;
	switchD_6fb1da92_default:
		if (pDVar6 != nullptr)
		{
			uVar11 = pDVar6->dwUnitId;
			uVar20 = 4;
			iVar16 = sub_6FAB0870(iVar16);
			uVar11 = sub_6FB4B900(uVar11, iVar16, uVar20);
			uVar14 = extraout_EDX_05;
			if (uVar11 != 0)
			{
				return;
			}
		}
		sub_6FB1C950((int)local_264, CONCAT31((int32_t)((uint32_t)uVar14 >> 8), *(uint8_t*)(a1 + 2)));
		return;
	case 8:
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xfcc;
		goto LAB_6fb1d9c9;
	case 9:
		sVar10 = 0xfcf;
		goto LAB_6fb1d485;
	case 10:
		if (*a2 == 0)
		{
			sVar10 = 0x1027;
			goto LAB_6fb1d485;
		}
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0x1026;
		goto LAB_6fb1d9c9;
	case 0xb:
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		pUVar9 = aUStack_2d4;
		pUVar8 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x69b));
		Unicode::sprintf(0x132, local_264, pUVar8, pUVar9);
		uVar15 = extraout_var_05;
		break;
	default:
		goto switchD_6fb1d43d_caseD_c;
	case 0xd:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe44));
		iVar16 = Unicode::strlen(pUVar9);
		D2_ASSERT(0x103 >= iVar16);
		Unicode::win2Unicode(aUStack_2d4, (char*)a2, 0x10);
		Unicode::strcpy(local_264, aUStack_2d4);
		sVar10 = 0xe44;
	LAB_6fb1d9c9:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		Unicode::strcat(local_264, pUVar9);
		uVar15 = extraout_var_03;
		break;
	case 0xf:
		uVar14 = *(uint32_t*)(a1 + 3);
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe43));
		Unicode::sprintf(0x132, local_264, pUVar9, uVar14);
		uVar15 = extraout_var_06;
		break;
	case 0x10:
		sVar10 = 0x2a38;
	LAB_6fb1d485:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar10));
		Unicode::strcpy(local_264, pUVar9);
		uVar15 = extraout_var;
		break;
	case 0x11:
		uVar14 = *(uint32_t*)(a1 + 3);
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2afc));
		Unicode::sprintf(0x132, local_264, pUVar9, uVar14);
		uVar15 = extraout_var_07;
		break;
	case 0x12:
		pUVar9 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x2afd));
		Unicode::sprintf(0x132, local_264, pUVar9);
		if (ghAct != nullptr)
		{
			iVar21 = 1;
			iVar18 = 0;
			iVar16 = 5;
			pRoom = CUNIT_GetPlayerRoom();
			ENVIRONMENT_InitializeEnvironment(ghAct, pRoom, iVar16, iVar18, iVar21);
		}
		sub_6FAB7E70(6, 4000, 10000, 4000);
		sub_6FB55820(0x1220, nullptr, 0.0, 0.0, 0);
		uVar15 = extraout_var_08;
	}
	sub_6FB1C600(local_264, CONCAT31(uVar15, *(uint8_t*)(a1 + 2)));
switchD_6fb1d43d_caseD_c:
}

//D2Client.0x6FB1DE10
void __fastcall sub_6FB1DE10(int a1)
{
	short index;
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* pFree_00;
	D2UnitStrc* pDVar2;
	D2HoverTextStrc* pDVar3;
	Unicode* wszText;
	Font nFontSize;
	int* piVar4;
	D2SplittedTextStrc* pDVar5;
	int iVar6;
	DWORD DVar7;
	char local_14[20];

	if (*(char*)(a1 + 1) == '\x01')
	{
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), 1);
		if (((pDVar2 != nullptr) && (*(char*)(a1 + 6) == '\x01')) &&
		    (*(char*)(a1 + 8) == '\x03'))
		{
			if (pDVar2->pHoverText != nullptr)
			{
				CHAT_FreeHoverMsg(nullptr, pDVar2->pHoverText);
			}
			sprintf(local_14, "%d", (uint32_t) * (uint16_t*)(a1 + 10));
			pDVar3 = CHAT_AllocHoverMsg(nullptr, local_14, dword_6FBB9EF6);
			pDVar2->pHoverText = pDVar3;
			return;
		}
		if (gpTextHeader_6FBB9F40 != nullptr)
		{
			TEXT_FreeTextHeader(gpTextHeader_6FBB9F40);
		}
		gpTextHeader_6FBB9F40 = TEXT_AllocTextHeader(nullptr);
		TEXT_CreateTextHeaderFromMessageList(gpTextHeader_6FBB9F40, (D2MessageListStrc*)(a1 + 6));
		TEXT_SortTextNodeListByStringId(gpTextHeader_6FBB9F40);
		return;
	}
	if (*(char*)(a1 + 1) == '\x02')
	{
		pDVar2 = sub_6FB269F0(*(uint32_t*)(a1 + 2), 2);
		pFree_00 = gpuint32_t_6FBB9F38;
		if (*(char*)(a1 + 8) != '\x03')
		{
			byte_6FBB9F1C = 0;
			dword_6FBB9EEE = *(uint32_t*)(a1 + 2);
			if (pDVar2 != nullptr)
			{
				byte_6FBB9F1C = (uint16_t)pDVar2->dwClassId;
			}
			sub_6FB1D110(CONCAT22((short)(dword_6FBB9EEE >> 0x10), *(uint16_t*)(a1 + 10)), 0, 1);
			return;
		}
		index = *(short*)(a1 + 10);
		if (gpuint32_t_6FBB9F38 != nullptr)
		{
			pFree = (uint32_t*)*gpuint32_t_6FBB9F38;
			while (pFree != nullptr)
			{
				puVar1 = (uint32_t*)pFree[1];
				D2_FREE((void*)*pFree);
				D2_FREE(pFree);
				pFree = puVar1;
			}
			D2_FREE(pFree_00);
			gpuint32_t_6FBB9F38 = nullptr;
		}
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		nFontSize = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
		piVar4 = (int*)D2_ALLOC(0x2c);
		pDVar5 = D2Win_10199(wszText, piVar4 + 1, 0xb4);
		*piVar4 = (int)pDVar5;
		sub_6FB1E060(piVar4);
		gpuint32_t_6FBB9F38 = (uint32_t*)(piVar4);
		D2Win_10127_SetFont(nFontSize);
		if (gpuint32_t_6FBB9F38 != nullptr)
		{
			*(uint32_t*)((int)gpuint32_t_6FBB9F38 + 0x16) = 1;
			iVar6 = Unicode::strlen(wszText);
			DVar7 = GetTickCount();
			dword_6FBB9F3C = DVar7 + (iVar6 + 0x19) * 200;
			dword_6FBB9EB0 = 1;
			dword_6FBB9EAC = 1;
			dword_6FBB9EBC = 100 - (uint32_t)(*(uint16_t*)((int)gpuint32_t_6FBB9F38 + 0x12) >> 2);
			dword_6FBB9EB8 = 0x140 - (uint32_t)(*(uint16_t*)(gpuint32_t_6FBB9F38 + 4) >> 1);
			return;
		}
	}
	else
	{
		TEXT_FreeTextHeader(gpTextHeader_6FBB9F40);
		gpTextHeader_6FBB9F40 = nullptr;
	}
}

//D2Client.0x6FB1E060
void __fastcall sub_6FB1E060(int* a1)
{
	uint32_t* puVar1;
	int iVar2;
	int iVar3;

	iVar3 = 0;
	puVar1 = (uint32_t*)*a1;
	a1[2] = 0;
	a1[3] = (uint32_t) * (uint16_t*)(a1 + 5);
	for (; puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[1])
	{
		iVar2 = D2Win_10121_GetTextWidth((Unicode*)*puVar1);
		if (iVar3 <= iVar2)
		{
			iVar3 = iVar2;
		}
	}
	*(short*)(a1 + 4) = (short)iVar3 + 0x14;
	*(short*)((int)a1 + 0x12) = (short)a1[1] * 0xf + 6;
}

//D2Client.0x6FB1E0B0
void __fastcall sub_6FB1E0B0(D2HoverTextStrc* pHoverText)
{
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* pFree_00;

	pFree_00 = (uint32_t*)CHAT_GetUsedFromHoverMsg(pHoverText);
	if (pFree_00 != nullptr)
	{
		pFree = (uint32_t*)*pFree_00;
		while (pFree != nullptr)
		{
			puVar1 = (uint32_t*)pFree[1];
			D2_FREE((void*)*pFree);
			D2_FREE(pFree);
			pFree = puVar1;
		}
		D2_FREE(pFree_00);
		CHAT_SetUsedInHoverMsg(pHoverText, 0);
	}
	CHAT_FreeHoverMsg(nullptr, pHoverText);
}

//D2Client.0x6FB1E120
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1E120(int a1)
{
	char cVar1;
	uint8_t bVar2;
	Unicode UVar3;
	bool bVar4;
	uint32_t extraout_var;
	D2C_Language DVar5;
	D2UnitStrc* pDVar6;
	Unicode* a3;
	Unicode* pUVar7;
	D2HoverTextStrc* pHoverMsg;
	D2C_Language DVar8;
	uint32_t uVar9;
	uint32_t uVar10;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t uVar11;
	uint32_t extraout_EDX_01;
	uint32_t extraout_EDX_02;
	uint32_t extraout_EDX_03;
	uint32_t extraout_EDX_04;
	uint32_t extraout_EDX_05;
	uint32_t extraout_EDX_06;
	int iVar12;
	uint32_t* puVar13;
	char* lpMultiByteStr;
	char* pcVar14;
	Unicode* pUVar15;
	Unicode aUStack_dd0[16];
	Unicode aUStack_db0[16];
	uint32_t local_d90;
	uint16_t uStack_b92;
	Unicode aUStack_b90[612];
	Unicode UStack_6c8;
	uint16_t auStack_6c6[255];
	Unicode aUStack_4c8[612];

	if ((*(char*)(a1 + 3) == '\0') &&
	    (bVar4 = sub_6FAB0B20(*(int*)(a1 + 4)), D2C_ZEXT(bVar4) == 0))
	{
		return;
	}
	pUVar7 = (Unicode*)&local_d90;
	iVar12 = 0x100;
	do
	{
		pUVar7 = pUVar7 + 1;
		iVar12 = iVar12 + -1;
	} while (iVar12 != 0);
	lpMultiByteStr = (char*)(a1 + 0x1a);
	DVar8 = (D2C_Language) * (uint8_t*)(a1 + 2);
	puVar13 = &local_d90;
	if ((((DVar8 == LANGUAGE_KOREAN) || (DVar8 == LANGUAGE_ENGLISHKOR)) ||
	        (DVar8 == LANGUAGE_JAPANESE)) ||
	    (DVar8 == LANGUAGE_CHINESETWN))
	{
		MultiByteToWideChar(0, 1, lpMultiByteStr, 0x100, (LPWSTR)&local_d90, 0x100);
		DVar5 = STRTABLE_GetLanguage();
		uVar11 = extraout_EDX_00;
		if (DVar5 != DVar8)
		{
			if (DVar5 == LANGUAGE_KOREAN)
			{
				if (DVar8 == LANGUAGE_ENGLISHKOR)
					goto LAB_6fb1e1ee;
			}
			else if ((DVar5 == LANGUAGE_ENGLISHKOR) && (DVar8 == LANGUAGE_KOREAN))
				goto LAB_6fb1e1ee;
			UVar3.ch = (*(uint16_t*)((uint8_t*)&local_d90 + 0));
			while (UVar3.ch != 0)
			{
				if (0x7f < (uint16_t)local_d90)
				{
					return;
				}
				UVar3.ch = *(uint16_t*)((int)puVar13 + 2);
				local_d90 = (uint32_t)UVar3.ch;
				puVar13 = (uint32_t*)((int)puVar13 + 2);
			}
		}
	}
	else
	{
		Unicode::win2Unicode((Unicode*)&local_d90, lpMultiByteStr, 0x100);
		uVar11 = extraout_EDX;
	}
LAB_6fb1e1ee:
	uStack_b92 = 0;
	if (*(char*)(a1 + 1) != '\x04')
	{
		pDVar6 = sub_6FB269F0(*(uint32_t*)(a1 + 4), (uint32_t) * (uint8_t*)(a1 + 3));
		cVar1 = *(char*)(a1 + 1);
		if (cVar1 == '\x06')
		{
			Unicode::win2Unicode(aUStack_4c8, lpMultiByteStr, 0x100);
			Unicode::win2Unicode(aUStack_dd0, (char*)(a1 + 10), 0x10);
			pUVar15 = aUStack_4c8;
			pUVar7 = aUStack_dd0;
			a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe4a));
			Unicode::sprintf(0x264, aUStack_b90, a3, pUVar7, pUVar15);
			sub_6FB20500(aUStack_b90);
			sub_6FB1C600(aUStack_b90, CONCAT31((int32_t)((uint32_t)extraout_EDX_02 >> 8), 2));
			return;
		}
		if (cVar1 == '\x02')
		{
			uVar9 = 0xffffffff;
			pcVar14 = (char*)(a1 + 10);
			do
			{
				if (uVar9 == 0)
					break;
				uVar9 = uVar9 - 1;
				cVar1 = *pcVar14;
				pcVar14 = pcVar14 + 1;
			} while (cVar1 != '\0');
			uVar10 = 0xffffffff;
			do
			{
				if (uVar10 == 0)
					break;
				uVar10 = uVar10 - 1;
				cVar1 = *lpMultiByteStr;
				lpMultiByteStr = lpMultiByteStr + 1;
			} while (cVar1 != '\0');
			if ((0 < (int)(~uVar9 - 1)) && ((int)(~uVar9 - 1) < 0x10))
			{
				Unicode::win2Unicode(aUStack_dd0, (char*)(a1 + 10), 0x10);
				Unicode::strcpy(aUStack_b90, aUStack_dd0);
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe46));
				Unicode::strcat(aUStack_b90, pUVar7);
				Unicode::strcpy(aUStack_4c8, (Unicode*)&local_d90);
				Unicode::strcat(aUStack_b90, aUStack_4c8);
				sub_6FB1C600(aUStack_b90, CONCAT31((int32_t)((uint32_t)extraout_EDX_03 >> 8), 2));
				return;
			}
			if (0x131 < (int)(~uVar10 - 1))
			{
				FOG_Trace("invalid msg len at %d of %s\n", __LINE__, __FILE__);
				return;
			}
			Unicode::strcpy(aUStack_b90, (Unicode*)&local_d90);
			sub_6FB1C600(aUStack_b90, CONCAT31((int32_t)((uint32_t)extraout_EDX_04 >> 8), 2));
			return;
		}
		if (cVar1 != '\x01')
		{
			if (cVar1 == '\x05')
			{
				if (pDVar6 != nullptr)
				{
					iVar12 = -1;
					pcVar14 = lpMultiByteStr;
					do
					{
						if (iVar12 == 0)
							break;
						iVar12 = iVar12 + -1;
						cVar1 = *pcVar14;
						pcVar14 = pcVar14 + 1;
					} while (cVar1 != '\0');
					bVar2 = *(uint8_t*)(a1 + 2);
					if (iVar12 == -2)
					{
						if (pDVar6->pHoverText != nullptr)
						{
							CHAT_FreeHoverMsg(nullptr, pDVar6->pHoverText);
						}
						pDVar6->pHoverText = nullptr;
						return;
					}
					pHoverMsg = CHAT_AllocHoverMsg(nullptr, lpMultiByteStr, dword_6FBB9EF6);
					CHAT_SetLangIdInHoverMsg(pHoverMsg, bVar2);
					if (pDVar6->pHoverText != nullptr)
					{
						CHAT_FreeHoverMsg(nullptr, pDVar6->pHoverText);
					}
					pDVar6->pHoverText = pHoverMsg;
					return;
				}
			}
			else
			{
				if (cVar1 == '\a')
				{
					pUVar7 = &UStack_6c8;
					iVar12 = 0x100;
					do
					{
						pUVar7 = pUVar7 + 1;
						iVar12 = iVar12 + -1;
					} while (iVar12 != 0);
					MultiByteToWideChar(0, 1, lpMultiByteStr, 0x100, (LPWSTR)&UStack_6c8, 0x100);
					bVar2 = *(uint8_t*)(a1 + 2);
					DVar8 = STRTABLE_GetLanguage();
					if (bVar2 != DVar8)
					{
						pUVar7 = &UStack_6c8;
						while (UStack_6c8.ch != 0)
						{
							pUVar7 = pUVar7 + 1;
							UStack_6c8.ch = pUVar7->ch;
						}
					}
					sub_6FAEE990((char*)(uint32_t) * (uint8_t*)(a1 + 8));
					return;
				}
				FOG_Trace("invalid msg param at %d of %s\n", __LINE__, __FILE__);
			}
			return;
		}
		uVar11 = extraout_EDX_01;
		if ((*(char*)(a1 + 3) != '\0') && (*(char*)(a1 + 3) != '\x01'))
		{
			uVar9 = 0xffffffff;
			pcVar14 = (char*)(a1 + 10);
			do
			{
				if (uVar9 == 0)
					break;
				uVar9 = uVar9 - 1;
				cVar1 = *pcVar14;
				pcVar14 = pcVar14 + 1;
			} while (cVar1 != '\0');
			uVar10 = 0xffffffff;
			do
			{
				if (uVar10 == 0)
					break;
				uVar10 = uVar10 - 1;
				cVar1 = *lpMultiByteStr;
				lpMultiByteStr = lpMultiByteStr + 1;
			} while (cVar1 != '\0');
			if ((0 < (int)(~uVar9 - 1)) && ((int)(~uVar9 - 1) < 0x10))
			{
				Unicode::win2Unicode(aUStack_db0, (char*)(a1 + 10), 0x10);
				Unicode::strcpy(aUStack_b90, aUStack_db0);
				sub_6FB20430((short*)aUStack_b90, '\x04');
				pUVar7 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfd0));
				Unicode::strcpy(aUStack_4c8, pUVar7);
				Unicode::strcat(aUStack_4c8, (Unicode*)&local_d90);
				sub_6FB20430((short*)aUStack_4c8, '\0');
				Unicode::strcat(aUStack_b90, aUStack_4c8);
				sub_6FB1C600(aUStack_b90,
				    CONCAT31((int32_t)((uint32_t)extraout_EDX_05 >> 8), *(uint8_t*)(a1 + 8)));
				return;
			}
			if (0x131 < (int)(~uVar10 - 1))
			{
				FOG_Trace("invalid msg len at %d of %s\n", __LINE__, __FILE__);
				return;
			}
			Unicode::strcpy(aUStack_b90, (Unicode*)&local_d90);
			sub_6FB1C600(aUStack_b90,
			    CONCAT31((int32_t)((uint32_t)extraout_EDX_06 >> 8), *(uint8_t*)(a1 + 8)));
			return;
		}
	}
	sub_6FB1C600((Unicode*)(&local_d90), CONCAT31((int32_t)((uint32_t)uVar11 >> 8), *(uint8_t*)(a1 + 8)));
}

//D2Client.0x6FB1E670
void __fastcall sub_6FB1E670(int a1)
{
	D2UnitStrc* pDVar1;

	pDVar1 = sub_6FB269F0(*(uint32_t*)(a1 + 2), (uint32_t) * (uint8_t*)(a1 + 1));
	if (pDVar1 != nullptr)
	{
		if (pDVar1->pHoverText != nullptr)
		{
			CHAT_FreeHoverMsg(nullptr, pDVar1->pHoverText);
		}
		pDVar1->pHoverText = nullptr;
	}
}

//D2Client.0x6FB1E6B0
D2TextHeaderStrc* __cdecl sub_6FB1E6B0()
{
	return gpTextHeader_6FBB9F40;
}

//D2Client.0x6FB1E6C0
Unicode* __fastcall sub_6FB1E6C0(uint16_t a1)
{
	int iVar1;
	Unicode* pUVar2;
	int iVar3;

	if (a1 < word_6FB8D430)
	{
		iVar1 = 0;
		iVar3 = 100;
	}
	else
	{
		iVar1 = 100;
		iVar3 = dword_6FB8DADC;
	}
	while (true)
	{
		if (iVar3 <= iVar1)
		{
			pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xe8c));
			return pUVar2;
		}
		if (word_6FB8D2A0[iVar1 * 2] == a1)
			break;
		iVar1 = iVar1 + 1;
	}
	pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(word_6FB8D2A0[iVar1 * 2 + 1]));
	return pUVar2;
}

//D2Client.0x6FB1E710
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB1E710()
{
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* pFree_00;
	int iVar2;
	HWND__* pHVar3;
	int extraout_ECX;
	int extraout_ECX_00;
	int extraout_ECX_01;
	int iVar4;
	uint32_t uVar5;

	sub_6FAB6450(nullptr);
	pFree_00 = gpuint32_t_6FBB9E90;
	if (gpuint32_t_6FBB9E90 != nullptr)
	{
		pFree = (uint32_t*)*gpuint32_t_6FBB9E90;
		while (pFree != nullptr)
		{
			puVar1 = (uint32_t*)pFree[1];
			D2_FREE((void*)*pFree);
			D2_FREE(pFree);
			pFree = puVar1;
		}
		D2_FREE(pFree_00);
		gpuint32_t_6FBB9E90 = nullptr;
	}
	iVar4 = dword_6FBB9F60;
	if (dword_6FBB9F60 != 0)
	{
		iVar2 = sub_6FB556F0(dword_6FBB9F60);
		iVar4 = extraout_ECX;
		if (iVar2 != 0)
		{
			sub_6FB55BF0(iVar2, 0, 0, 4);
			iVar4 = extraout_ECX_00;
		}
		dword_6FBB9F60 = 0;
	}
	dword_6FBB9F33 = 0;
	if (dword_6FBB9F68 == 1)
	{
		uVar5 = 7;
		dword_6FBB9F68 = 0;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar5);
		iVar4 = extraout_ECX_01;
	}
	if (dword_6FBB9F18 != 0)
	{
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar4 >> 8), 0x31), 0xffffffff, (uint32_t)word_6FBB9EFA);
		dword_6FBB9F18 = 0;
	}
	dword_6FBB9EE2 = 0;
	if (gpTextHeader_6FBB9F40 != nullptr)
	{
		TEXT_FreeTextHeader(gpTextHeader_6FBB9F40);
		gpTextHeader_6FBB9F40 = nullptr;
	}
}

//D2Client.0x6FB1E810
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB1E810()
{
	uint32_t* puVar1;
	uint32_t* pFree;
	uint32_t* pFree_00;
	int iVar2;
	HWND__* pHVar3;
	int extraout_ECX;
	int extraout_ECX_00;
	int extraout_ECX_01;
	int iVar4;
	uint32_t uVar5;

	sub_6FAB6450(nullptr);
	pFree_00 = gpuint32_t_6FBB9E90;
	if (gpuint32_t_6FBB9E90 != nullptr)
	{
		pFree = (uint32_t*)*gpuint32_t_6FBB9E90;
		while (pFree != nullptr)
		{
			puVar1 = (uint32_t*)pFree[1];
			D2_FREE((void*)*pFree);
			D2_FREE(pFree);
			pFree = puVar1;
		}
		D2_FREE(pFree_00);
		gpuint32_t_6FBB9E90 = nullptr;
	}
	iVar4 = dword_6FBB9F60;
	if (dword_6FBB9F60 != 0)
	{
		iVar2 = sub_6FB556F0(dword_6FBB9F60);
		iVar4 = extraout_ECX;
		if (iVar2 != 0)
		{
			sub_6FB55BF0(iVar2, 0, 0, 4);
			iVar4 = extraout_ECX_00;
		}
		dword_6FBB9F60 = 0;
	}
	dword_6FBB9F33 = 0;
	if (dword_6FBB9F68 == 1)
	{
		uVar5 = 7;
		dword_6FBB9F68 = 0;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8D228), uVar5);
		iVar4 = extraout_ECX_01;
	}
	if (dword_6FBB9F18 != 0)
	{
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)iVar4 >> 8), 0x31), 0xffffffff, (uint32_t)word_6FBB9EFA);
		dword_6FBB9F18 = 0;
	}
}

//D2Client.0x6FB1E8F0
void __cdecl sub_6FB1E8F0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	if (((int)(uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2) < gnScreenHeight + -0x30) &&
	    ((int)(uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam < gnScreenWidth / 2))
	{
		sub_6FB23260(0x10, 2, 0);
		if (gpCellFile_6FBB9F74 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB9F74);
			gpCellFile_6FBB9F74 = nullptr;
		}
		if (gpCellFile_6FBB9F70 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB9F70);
			gpCellFile_6FBB9F70 = nullptr;
		}
		if (gpCellFile_6FBB9F78 != nullptr)
		{
			CLIENT_FreeCellFile(gpCellFile_6FBB9F78);
			gpCellFile_6FBB9F78 = nullptr;
		}
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		sub_6FAABF30();
	}
}

//D2Client.0x6FB1E990
void __cdecl sub_6FB1E990()
{
	int iVar1;

	if (dword_6FBB9F10 == 0)
	{
		return;
	}
	iVar1 = *(int*)(dword_6FBB9F10 + 0x80);
	if (iVar1 != 0x20736b62)
	{
		if (iVar1 == 0x20646b62)
		{
			if (dword_6FBB9F50 == 0)
			{
				sub_6FB1EB70(1);
				return;
			}
		}
		else if (iVar1 != 0x20317274)
		{
			return;
		}
		sub_6FB1E9E0();
		return;
	}
	sub_6FB1EB70(0);
}

//D2Client.0x6FB1E9E0
void __cdecl sub_6FB1E9E0()
{
	D2GfxDataStrc* pDVar1;
	int iVar2;
	D2GfxDataStrc DStack_14c;
	CHAR aCStack_104[260];

	D2GFX_DrawBox(dword_6FBBA748, dword_6FBBA74C + -0xe0 + gnScreenHeight, gnScreenWidth / 2,
	    gnScreenHeight + -0x30, 0, DRAWMODE_NORMAL);
	if (gpCellFile_6FBB9F78 == nullptr)
	{
		wsprintfA(aCStack_104, "%s\\UI\\MENU\\scroin", "DATA\\GLOBAL");
		gpCellFile_6FBB9F78 = CLIENT_LoadCellFile(aCStack_104, 0);
	}
	pDVar1 = &DStack_14c;
	for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		pDVar1->pCurrentCell = 0;
		pDVar1 = (D2GfxDataStrc*)((int)pDVar1 + 4);
	}
	DStack_14c.nDirection = 0;
	DStack_14c.nFrame = 0;
	DStack_14c.pCellFile = gpCellFile_6FBB9F78;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748, dword_6FBBA74C + -0x6d + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 1;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x6d + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 2;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748, dword_6FBBA74C + -0x31 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.nFrame = 3;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x100, dword_6FBBA74C + -0x31 + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
	DStack_14c.pCellFile = sub_6FB24110();
	DStack_14c.nFrame = 10;
	TEXTURE_CelDraw(&DStack_14c, dword_6FBBA748 + 0x115, dword_6FBBA74C + -0x3d + gnScreenHeight, 0xffffffff,
	    DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB1EB70
void __fastcall sub_6FB1EB70(int a1)
{
	uint16_t uVar1;
	D2UnitStrc* pDVar2;
	Font nFontSize;
	DWORD DVar3;
	DrawMode eDrawMode;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	int iVar8;
	uint32_t* puVar9;
	D2GfxDataStrc* pDVar10;
	D2GfxDataStrc local_194;
	D2GfxDataStrc DStack_14c;
	char local_104;
	uint32_t local_103;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar10 = &local_194;
		for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			pDVar10->pCurrentCell = nullptr;
			pDVar10 = (D2GfxDataStrc*)&pDVar10->pCellFile;
		}
		sub_6FB1E9E0();
		uVar7 = 0;
		if (gpCellFile_6FBB9F74 == nullptr)
		{
			local_104 = byte_6FB9A828;
			puVar9 = &local_103;
			for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 1;
			}
			*(uint16_t*)puVar9 = 0;
			*(uint8_t*)((int)puVar9 + 2) = 0;
			sprintf(&local_104, "%s\\%s", "DATA\\GLOBAL", "UI\\menu\\scroin2");
			gpCellFile_6FBB9F74 = CLIENT_LoadCellFile(&local_104, 0);
		}
		if (gpCellFile_6FBB9F70 == nullptr)
		{
			local_104 = byte_6FB9A828;
			puVar9 = &local_103;
			for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar9 = 0;
				puVar9 = puVar9 + 1;
			}
			*(uint16_t*)puVar9 = 0;
			*(uint8_t*)((int)puVar9 + 2) = 0;
			sprintf(&local_104, "%s\\%s", "DATA\\GLOBAL", "UI\\menu\\scroin3");
			gpCellFile_6FBB9F70 = CLIENT_LoadCellFile(&local_104, 0);
		}
		if (a1 != 0)
		{
			nFontSize = D2Win_10127_SetFont(D2FONT_FONTFORMAL12);
			local_194.pCellFile = gpCellFile_6FBB9F74;
			if (dword_6FBB9F2B == 0)
			{
				dword_6FBB9F2B = GetTickCount();
				dword_6FBB9F2F = 0;
			}
			else
			{
				DVar3 = GetTickCount();
				if (dword_6FBB9F2B + 0x32 < DVar3)
				{
					dword_6FBB9F2B = GetTickCount();
					dword_6FBB9F2F = dword_6FBB9F2F + 1;
				}
			}
			do
			{
				if ((uint32_t)(&dword_6FB8DB30)[uVar7] < dword_6FBB9F2F)
				{
					uVar6 = dword_6FBB9F2F - (&dword_6FB8DB30)[uVar7];
					eDrawMode = DRAWMODE_NORMAL;
					local_194.nFrame = uVar7;
					if (uVar6 == 1)
					{
						sub_6FB55820(0xa6f, nullptr, 0.0, 0.0, 0);
						eDrawMode = DRAWMODE_TRANS25;
					}
					else if ((int)uVar6 < 5)
					{
						eDrawMode = DRAWMODE_TRANS25;
					}
					else if ((int)uVar6 < 10)
					{
						eDrawMode = DRAWMODE_TRANS50;
					}
					else if ((int)uVar6 < 0xf)
					{
						eDrawMode = DRAWMODE_TRANS75;
					}
					uVar1 = (&word_6FBB9F44)[uVar7];
					if (uVar1 < 6)
					{
						D2_ASSERT(4 >= uVar1);
						iVar8 = (uint32_t)uVar1 * 8;
						TEXTURE_CelDraw(&local_194, *(int*)(byte_6FB8DAE0 + iVar8) + dword_6FBBA748,
						    *(int*)(byte_6FB8DAE4 + iVar8) - dword_6FBBA74C, 0xffffffff, eDrawMode,
						    nullptr);
						iVar4 = *(int*)(byte_6FB8DB0C + iVar8);
						pDVar10 = &DStack_14c;
						for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
						{
							pDVar10->pCurrentCell = nullptr;
							pDVar10 = (D2GfxDataStrc*)&pDVar10->pCellFile;
						}
						DStack_14c.nFrame = (0x14 < (int)uVar6) - 1 & uVar6;
						DStack_14c.pCellFile = gpCellFile_6FBB9F70;
						TEXTURE_CelDraw(&DStack_14c, *(int*)(byte_6FB8DB08 + iVar8) + dword_6FBBA748,
						    iVar4 - dword_6FBBA74C, 0xffffffff, DRAWMODE_MODULATE, nullptr);
					}
				}
				uVar7 = uVar7 + 1;
			} while ((int)uVar7 < 5);
			D2Win_10127_SetFont(nFontSize);
		}
	}
}

//D2Client.0x6FB1EDF0
void __fastcall sub_6FB1EDF0(int a1)
{
	if (*(short*)(a1 + 1) == 4)
	{
		word_6FBB9F44 = *(uint32_t*)(a1 + 3);
		byte_6FBB9F48 = *(uint32_t*)(a1 + 7);
		byte_6FBB9F4C = *(uint32_t*)(a1 + 0xb);
		dword_6FBB9F50 = 0;
	}
}

//D2Client.0x6FB1EE20
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1EE20(int a1, int a2)
{
	uint32_t extraout_ECX;
	uint32_t uVar1;

	dword_6FBB9F10 = a2;
	sub_6FB23260(0x10, 2, 0);
	sub_6FAABF30();
	if (*(int*)(dword_6FBB9F10 + 0x80) == 0x20646b62)
	{
		dword_6FBB9F50 = 1;
		if (a1 == 0)
		{
			uVar1 = 0xffffffff;
		}
		else
		{
			uVar1 = *(uint32_t*)(a1 + 0xc);
		}
		sub_6FAADA20(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x3e), uVar1);
		byte_6FBB9EC8 = 0;
		return;
	}
	dword_6FBB9F50 = 0;
	byte_6FBB9EC8 = 1;
}

//D2Client.0x6FB1EE90
bool __cdecl sub_6FB1EE90()
{
	return gpuint32_t_6FBB9E90 != nullptr;
}

//D2Client.0x6FB1EEA0
void __cdecl sub_6FB1EEA0()
{
	void* pvVar1;
	void* pFree;
	uint32_t* puVar2;
	void* pFree_00;
	uint32_t* pFree_01;
	short sVar3;
	short sVar4;
	int iVar5;

	sVar3 = 0;
	pFree_00 = ptr_6FBB9ECC;
	sVar4 = 0;
	if (ptr_6FBB9ECC != nullptr)
	{
		do
		{
			pvVar1 = *(void**)((int)pFree_00 + 0x22);
			iVar5 = 0;
			do
			{
				pFree = *(void**)((int)pFree_00 + iVar5 * 4);
				if (pFree != nullptr)
				{
					D2_FREE(pFree);
				}
				iVar5 = iVar5 + 1;
			} while (iVar5 < 6);
			D2_FREE(pFree_00);
			sVar3 = sVar4 + 1;
			pFree_00 = pvVar1;
			sVar4 = sVar3;
		} while (pvVar1 != nullptr);
		ptr_6FBB9ECC = nullptr;
	}
	D2_ASSERT(sVar3 == word_6FBB9ED0);
	sVar3 = 0;
	word_6FBB9ED0 = 0;
	pFree_01 = gpuint32_t_6FBB9ED8;
	sVar4 = 0;
	if (gpuint32_t_6FBB9ED8 != nullptr)
	{
		do
		{
			puVar2 = *(uint32_t**)((int)pFree_01 + 0x22);
			iVar5 = 0;
			do
			{
				if ((void*)pFree_01[iVar5] != nullptr)
				{
					D2_FREE((void*)pFree_01[iVar5]);
				}
				iVar5 = iVar5 + 1;
			} while (iVar5 < 6);
			D2_FREE(pFree_01);
			sVar3 = sVar4 + 1;
			pFree_01 = puVar2;
			sVar4 = sVar3;
		} while (puVar2 != nullptr);
		gpuint32_t_6FBB9ED8 = nullptr;
	}
	D2_ASSERT(sVar3 == word_6FBB9EDC);
	word_6FBB9EDC = 0;
}

//D2Client.0x6FB1EFB0
void __cdecl sub_6FB1EFB0()
{
	uint32_t* puVar1;
	Unicode* pUVar2;
	void* pvVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	code* pcVar9;
	int iVar10;
	int iVar11;
	void* local_c;
	code* pcStack_8;
	uint32_t uStack_4;

	uStack_4 = 0xffffffff;
	if (dword_6FBB9E98 == 0)
	{
		dword_6FBB9E98 = (int)sub_6FAD6BE0(5, 0x1e, 0x6fb1f140, 0, 0, 0, 0, gnScreenWidth - 0x14,
		    gnScreenHeight - 0x82, 0, 0);
		sub_6FAD7150(dword_6FBB9E98, 1);
		iVar10 = 0;
		uVar8 = 0;
		uVar7 = 1;
		iVar6 = 4;
		uVar5 = 0;
		uVar4 = 0x15;
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xfc3));
		sub_6FAD7180(dword_6FBB9E98, pUVar2, uVar4, uVar5, iVar6, uVar7, uVar8, iVar10);
		iVar11 = 1;
		pcVar9 = (code*)(sub_6FB1F140);
		uVar5 = 1;
		iVar10 = 0;
		iVar6 = gnScreenHeight + -0xa5;
		uVar4 = 0;
		pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1030));
		sub_6FAD7180(dword_6FBB9E98, pUVar2, iVar6, uVar4, iVar10, uVar5, (int)(pcVar9), iVar11);
		pvVar3 = SMemAlloc(0xc, "new", -1, 0);
		uStack_4 = 0;
		if (pvVar3 == nullptr)
		{
			gpint32_t_6FBB9E9C = nullptr;
		}
		else
		{
			gpint32_t_6FBB9E9C = (int*)sub_6FAF1130(pvVar3, gnScreenWidth + -0x14, 5, 0x41, gnScreenWidth + -0x14,
			    gnScreenHeight + -200, 2, 0, 0xd, 0, 1);
		}
		uStack_4 = 0xffffffff;
		if (gpint32_t_6FBB9E9C != nullptr)
		{
			sub_6FAD68F0(dword_6FBB9E98, (uint32_t)(gpint32_t_6FBB9E9C), 0x19, 0x1e);
			for (puVar1 = gpuint32_t_6FBB9ED8; puVar1 != nullptr;
			     puVar1 = *(uint32_t**)((int)puVar1 + 0x22))
			{
				(**(code**)(*gpint32_t_6FBB9E9C + 0x30))(*puVar1, puVar1[1], puVar1[2], puVar1[3], puVar1[4], puVar1[5], 0,
				    *(uint32_t*)((int)puVar1 + 0x1a), 0, 0xd);
			}
			sub_6FAD7090(dword_6FBB9E98, -1);
		}
	}
}

//D2Client.0x6FB1F140
uint32_t __cdecl sub_6FB1F140()
{
	sub_6FB23260(0x18, 1, 0);
	return 1;
}

//D2Client.0x6FB1F160
void __cdecl sub_6FB1F160()
{
	if (dword_6FBB9E98 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB9E98 = 0;
	}
	if (gpint32_t_6FBB9E9C != nullptr)
	{
		(**(code**)*gpint32_t_6FBB9E9C)(1);
		gpint32_t_6FBB9E9C = nullptr;
	}
}

//D2Client.0x6FB1F1A0
void __cdecl sub_6FB1F1A0()
{
	void* pvVar1;

	pvVar1 = ptr_6FBB9ECC;
	if (ptr_6FBB9ECC != nullptr)
	{
		do
		{
			*(uint32_t*)((int)pvVar1 + 0x1e) = 0;
			pvVar1 = *(void**)((int)pvVar1 + 0x22);
		} while (pvVar1 != nullptr);
	}
}

//D2Client.0x6FB1F1C0
void __fastcall sub_6FB1F1C0(int* a1, uint32_t a2)
{
	char cVar1;
	D2C_Language DVar2;
	uint32_t uVar3;
	D2HoverTextStrc* pHoverMsg;
	int iVar4;
	char* pcVar5;
	char acStack_c[12];

	if ((((a1 != nullptr) && (DVar2 = STRTABLE_GetLanguage(), 5 < (int)DVar2)) &&
	        (((int)DVar2 < 8 || (DVar2 == LANGUAGE_CHINESETWN)))) &&
	    ((0xb75 < (int)a2 && ((int)a2 < 0x1231))))
	{
		if (*a1 == 0)
		{
			uVar3 = 0;
			while (*(uint16_t*)(gpuint8_t_6FB8E360[a1[1]] + uVar3 * 4) != a2)
			{
				uVar3 = uVar3 + 1;
				if (0x49 < uVar3)
				{
					return;
				}
			}
			sprintf(acStack_c, "%c%c%d", 0xffffffff, 0xffffffff,
			    (uint32_t) * (uint16_t*)(gpuint8_t_6FB8E360[a1[1]] + uVar3 * 4 + 2));
		}
		else
		{
			if (*a1 != 1)
			{
				return;
			}
			uVar3 = 0;
			while ((uint16_t)word_6FB8E37C[uVar3 * 2] != a2)
			{
				uVar3 = uVar3 + 1;
				if (5 < uVar3)
				{
					return;
				}
			}
			sprintf(acStack_c, "%d", (uint32_t)(uint16_t)word_6FB8E37C[uVar3 * 2 + 1]);
		}
		DVar2 = STRTABLE_GetLanguage();
		iVar4 = -1;
		pcVar5 = acStack_c;
		do
		{
			if (iVar4 == 0)
				break;
			iVar4 = iVar4 + -1;
			cVar1 = *pcVar5;
			pcVar5 = pcVar5 + 1;
		} while (cVar1 != '\0');
		if (iVar4 == -2)
		{
			if ((D2HoverTextStrc*)a1[0x29] != nullptr)
			{
				CHAT_FreeHoverMsg(nullptr, (D2HoverTextStrc*)a1[0x29]);
			}
			a1[0x29] = 0;
			return;
		}
		pHoverMsg = CHAT_AllocHoverMsg(nullptr, acStack_c, dword_6FBB9EF6);
		CHAT_SetLangIdInHoverMsg(pHoverMsg, (uint8_t)DVar2);
		if ((D2HoverTextStrc*)a1[0x29] != nullptr)
		{
			CHAT_FreeHoverMsg(nullptr, (D2HoverTextStrc*)a1[0x29]);
		}
		a1[0x29] = (int)pHoverMsg;
	}
}

//D2Client.0x6FB1F320
void __cdecl sub_6FB1F320()
{
	if (dword_6FBB9E98 != 0)
	{
		sub_6FB23260(0x18, 1, 0);
		sub_6FB23260(0x18, 0, 0);
	}
}

//D2Client.0x6FB1F350
void __cdecl sub_6FB1F350()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB9F80;
	iVar1 = 0x10;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FB1F370
void __cdecl sub_6FB1F370()
{
	dword_6FBB9FB8 = 0;
	byte_6FBB9FA8 = 0;
}

//D2Client.0x6FB1F380
void __cdecl sub_6FB1F380()
{
	sub_6FB1F5B0(0);
}

//D2Client.0x6FB1F390
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB1F390()
{
	bool bVar1;
	int iVar2;
	int iVar3;
	uint32_t extraout_var;
	Unicode* pUVar4;
	D2UnitStrc* pDVar5;
	D2ActiveRoomStrc* pRoom;
	uint32_t extraout_var_00;
	uint32_t extraout_ECX;
	int iVar6;
	int iVar7;
	int iVar8;
	int iVar9;

	iVar2 = sub_6FB57BC0();
	iVar3 = sub_6FB57BD0();
	if ((2 < dword_6FBB9FB8) && (bVar1 = sub_6FB247E0(), D2C_ZEXT(bVar1) == 0))
	{
		if ((dword_6FBBA748 + 0x111 <= iVar2) &&
		    (((iVar2 <= dword_6FBBA748 + 0x133 && (0xa8 - dword_6FBBA74C <= iVar3)) &&
		        (iVar3 <= 0xca - dword_6FBBA74C))))
		{
			iVar8 = 0;
			iVar6 = 0xa7 - dword_6FBBA74C;
			iVar7 = 0;
			iVar9 = dword_6FBBA748 + 0xef;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1023));
			D2Win_10129_DrawFramedText(pUVar4, iVar9, iVar6, iVar7, iVar8);
		}
		if (((dword_6FBBA748 + 0xdd <= iVar2) && (iVar2 <= dword_6FBBA748 + 0xff)) &&
		    ((0x17f - dword_6FBBA74C <= iVar3 && (iVar3 <= 0x1a1 - dword_6FBBA74C))))
		{
			iVar8 = 0;
			iVar6 = 0x17e - dword_6FBBA74C;
			iVar7 = 0;
			iVar9 = dword_6FBBA748 + 0xbb;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1023));
			D2Win_10129_DrawFramedText(pUVar4, iVar9, iVar6, iVar7, iVar8);
		}
		if (((dword_6FBBA748 + 0x111 <= iVar2) && (iVar2 <= dword_6FBBA748 + 0x133)) &&
		    ((0x17f - dword_6FBBA74C <= iVar3 && (iVar3 <= 0x1a1 - dword_6FBBA74C))))
		{
			iVar6 = 0;
			iVar3 = 0x17e - dword_6FBBA74C;
			iVar9 = 0;
			iVar2 = dword_6FBBA748 + 0x107;
			pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x1022));
			D2Win_10129_DrawFramedText(pUVar4, iVar2, iVar3, iVar9, iVar6);
		}
	}
	pDVar5 = CUNIT_GetPlayer();
	if (pDVar5 != nullptr)
	{
		pDVar5 = CUNIT_GetPlayer();
		pRoom = UNITS_GetRoom(pDVar5);
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) != 0)
		{
		LAB_6fb1f4fe:
			iVar2 = sub_6FB23230(0x17);
			if (iVar2 == 0)
			{
				return;
			}
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x4f), 2, 0, 0);
			sub_6FB23260(0x17, 1, 0);
			sub_6FAED270();
			sub_6FAE90F0();
			dword_6FBB9FB8 = 0;
			return;
		}
		if (pRoom != nullptr)
		{
			iVar2 = DUNGEON_GetLevelIdFromRoom(pRoom);
			iVar2 = DUNGEON_IsTownLevelId(iVar2);
			if (iVar2 == 0)
				goto LAB_6fb1f4fe;
		}
	}
	if (((dword_6FBB9FB8 < 3) || (6 < dword_6FBB9FB8)) && (dword_6FBB9FB8 != 0))
	{
		if (dword_6FBB9FB8 == 1)
		{
			if (dword_6FBB9F7C != 0)
			{
				sub_6FAD6EB0(dword_6FBB9F7C);
				return;
			}
		}
		else if ((dword_6FBB9FB8 == 2) && (dword_6FBB9FB4 != 0))
		{
			sub_6FAD6EB0(dword_6FBB9FB4);
			return;
		}
	}
}

//D2Client.0x6FB1F590
void __cdecl sub_6FB1F590()
{
	byte_6FBB9FBC = 1;
	dword_6FBB9FA4 = 0;
	byte_6FBB9FAC = 0;
}

//D2Client.0x6FB1F5B0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB1F5B0(int a1)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	uint32_t extraout_ECX;
	uint32_t extraout_ECX_00;
	uint32_t extraout_ECX_01;
	uint32_t uVar3;

	byte_6FBB9FBC = 0;
	if (dword_6FBB9F7C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB9F7C = 0;
	}
	if (dword_6FBB9FB4 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB9FB4 = 0;
	}
	if (dword_6FBB9FB8 != 7)
	{
		iVar2 = sub_6FB23230(0x17);
		uVar3 = extraout_ECX;
		if (iVar2 != 0)
		{
			sub_6FB23260(0x17, 1, 0);
			sub_6FAED270();
			sub_6FAE90F0();
			bVar1 = sub_6FB283E0();
			if ((D2C_ZEXT(bVar1) == 0) && (a1 != 0))
			{
				sub_6FB23260(1, 2, 0);
			}
			iVar2 = sub_6FB23230(5);
			uVar3 = extraout_ECX_00;
			if (iVar2 != 0)
			{
				sub_6FB23260(5, 1, 0);
				uVar3 = extraout_ECX_01;
			}
		}
		if (dword_6FBB9FB8 != 0)
		{
			sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)uVar3 >> 8), 0x4f), 2, 0, 0);
			dword_6FBB9FB8 = 0;
		}
	}
}

//D2Client.0x6FB1F680
uint32_t __cdecl sub_6FB1F680()
{
	if ((dword_6FBB9FB8 != 1) && (dword_6FBB9FB8 != 2))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FB1F6A0
void __fastcall sub_6FB1F6A0(uint32_t a1)
{
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x4f), 2, 0, 0);
	if (dword_6FBB9FB8 != 7)
	{
		byte_6FBB9FA8 = 1;
		dword_6FBB9FA0 = GetTickCount();
		dword_6FBB9FB8 = 7;
	}
}

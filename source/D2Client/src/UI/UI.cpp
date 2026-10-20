#include "UI/UI.h"
#include "Quest/Quests.h"

#include "Core/Archive.h"
#include "Core/MemoryPartitions.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Draw/DFloor.h"
#include "Draw/DWall.h"
#include "Engine/Cursor.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/PalShift.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/SCmd.h"
#include "Game/Scroll.h"
#include "Game/Select.h"
#include "Game/View.h"
#include "Quest/QuestsFX.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/Char.h"
#include "UI/Chat.h"
#include "UI/CmdTbl.h"
#include "UI/Dialog.h"
#include "UI/EditBox.h"
#include "UI/Hireables.h"
#include "UI/Inv.h"
#include "UI/Mods.h"
#include "UI/NpcMenu.h"
#include "UI/Panel.h"
#include "UI/Party.h"
#include "UI/QuestLog.h"
#include "UI/Restart.h"
#include "UI/ShowItems.h"
#include "UI/SkillsTree.h"
#include "UI/SpellSel.h"
#include "UI/Text.h"
#include "UI/Trade.h"
#include "UI/UseItem.h"
#include "Unit/CUnit.h"
#include "Unit/Item.h"
#include "Unit/Missile.h"
#include "Unit/MonUnique.h"
#include "Unit/Object.h"

//D2Client.0x6FBBA7A0
uint32_t unk_6FBBA7A0[38] = {  };

//D2Client.0x6FB6FC18
uint32_t tbl_6FB6FC18[12] = {0, 0x201, (uint32_t)sub_6FB00CD0, 0, 0x202, (uint32_t)sub_6FB00E20, 0, 0x200, (uint32_t)sub_6FB01430, 0, 0x204, (uint32_t)sub_6FB01730};
//D2Client.0x6FB6FC48
uint32_t tbl_6FB6FC48[12] = {0, 0x201, (uint32_t)sub_6FAE6E60, 0, 0x202, (uint32_t)sub_6FAE8140, 0, 0x204, (uint32_t)sub_6FAE8AA0, 0, 0x200, (uint32_t)sub_6FAE8290};
//D2Client.0x6FB6FC78
uint8_t byte_6FB6FC78 = 4;
//D2Client.0x6FB6FC9C
uint32_t tbl_6FB6FC9C[6] = {0, 0x201, (uint32_t)sub_6FB17A80, 0, 0x202, (uint32_t)sub_6FB18100};
//D2Client.0x6FB6FCB4
uint32_t tbl_6FB6FCB4[3] = {0, 0x201, (uint32_t)sub_6FB19BB0};
//D2Client.0x6FB6FCC0
uint32_t tbl_6FB6FCC0[6] = {0, 0x201, (uint32_t)sub_6FAD1290, 0, 0x202, (uint32_t)sub_6FAD1470};
//D2Client.0x6FB6FCD8
uint32_t tbl_6FB6FCD8[6] = {0, 0x201, (uint32_t)sub_6FAEED80, 0, 0x202, (uint32_t)sub_6FAEEFD0};
//D2Client.0x6FB6FCF0
uint32_t tbl_6FB6FCF0[3] = {3, 0x7A, (uint32_t)sub_6FADB980};
//D2Client.0x6FB6FCFC
uint32_t tbl_6FB6FCFC[7] = {0, 0x201, (uint32_t)sub_6FAEEEA0, 0, 0x202, (uint32_t)sub_6FAEF130};
//D2Client.0x6FB6FD18
uint32_t tbl_6FB6FD18[22] = {0, 0x201, (uint32_t)sub_6FB07A50, 0, 0x202, (uint32_t)sub_6FB07CC0, 3, 0x28, (uint32_t)sub_6FB07E20, 3, 0x26, (uint32_t)sub_6FB07EA0, 3, 0x25, (uint32_t)sub_6FB07F20, 3, 0x27, (uint32_t)sub_6FB08060, 3, 0xD, (uint32_t)sub_6FB081A0};
//D2Client.0x6FB6FD70
uint32_t tbl_6FB6FD70[39] = {0, 0x201, (uint32_t)sub_6FAFD550, 0, 0x202, (uint32_t)sub_6FAFD5A0, 0, 0x204, (uint32_t)sub_6FAFD550, 0, 0x205, (uint32_t)sub_6FAFD5A0, 3, 0x28, (uint32_t)sub_6FAFD910, 3, 0x26, (uint32_t)sub_6FAFD8A0, 3, 0x25, (uint32_t)sub_6FAFD980, 3, 0x27, (uint32_t)sub_6FAFD9E0, 3, 0xD, (uint32_t)sub_6FAFDA40, 3, 0x2E, (uint32_t)sub_6FAFDB50, 3, 8, (uint32_t)sub_6FAFDB50, 3, 0x1B, (uint32_t)sub_6FAFDBD0, 3, 0x20, (uint32_t)sub_6FAFDBD0};
//D2Client.0x6FB6FE0C
uint32_t tbl_6FB6FE0C[3] = {0, 0x20A, (uint32_t)sub_6FAFD830};
//D2Client.0x6FB6FE18
uint32_t tbl_6FB6FE18[15] = {3, 0x26, (uint32_t)sub_6FACB6B0, 3, 0x28, (uint32_t)sub_6FACB6A0, 3, 0x27, (uint32_t)sub_6FACB6D0, 3, 0x25, (uint32_t)sub_6FACB6C0, 3, 0x23, (uint32_t)sub_6FADA310};
//D2Client.0x6FB6FE54
uint32_t tbl_6FB6FE54[12] = {0, 0x204, (uint32_t)sub_6FB06320, 0, 0x205, (uint32_t)sub_6FB06480, 0, 0x201, (uint32_t)sub_6FB06320, 0, 0x202, (uint32_t)sub_6FB06480};
//D2Client.0x6FB6FE84
uint8_t byte_6FB6FE84 = 5;
//D2Client.0x6FB6FEA8
uint32_t tbl_6FB6FEA8[6] = {0, 0x201, (uint32_t)sub_6FB1E8F0, 0, 0x204, (uint32_t)sub_6FB1E8F0};
//D2Client.0x6FB6FEC0
uint32_t tbl_6FB6FEC0[15] = {0, 0x201, (uint32_t)sub_6FB267A0, 0, 0x202, (uint32_t)sub_6FB265C0, 0, 0x204, (uint32_t)sub_6FB267A0, 0, 0x205, (uint32_t)sub_6FB265C0, 0, 0x102, (uint32_t)sub_6FB26250};
//D2Client.0x6FB6FEFC
uint32_t tbl_6FB6FEFC[6] = {0, 0x201, (uint32_t)sub_6FB099F0, 0, 0x202, (uint32_t)sub_6FB09730};
//D2Client.0x6FB6FF14
uint32_t tbl_6FB6FF14[6] = {0, 0x201, (uint32_t)sub_6FB03870, 0, 0x202, (uint32_t)sub_6FB03AC0};
//D2Client.0x6FB6FF2C
uint8_t byte_6FB6FF2C = 5;
//D2Client.0x6FB6FF50
uint8_t byte_6FB6FF50 = 4;
//D2Client.0x6FB6FF74
uint8_t byte_6FB6FF74 = 4;
//D2Client.0x6FB6FF98
uint8_t byte_6FB6FF98;
//D2Client.0x6FB6FFBC
uint32_t tbl_6FB6FFBC[15] = {0, 0x201, (uint32_t)sub_6FADA190, 0, 0x202, (uint32_t)sub_6FADA220, 3, 0x20, (uint32_t)sub_6FADA2D0, 3, 0x1B, (uint32_t)sub_6FADA2D0, 0, 0x102, (uint32_t)sub_6FADA310};
//D2Client.0x6FB6FFF8
uint32_t tbl_6FB6FFF8[6] = {0, 0x201, (uint32_t)sub_6FADA5F0, 0, 0x202, (uint32_t)sub_6FADA660};
//D2Client.0x6FB70010
uint32_t tbl_6FB70010[9] = {0, 0x201, (uint32_t)sub_6FADBA00, 0, 0x200, (uint32_t)sub_6FADBC90, 0, 0x204, (uint32_t)sub_6FADBE20};
//D2Client.0x6FB70034
uint32_t tbl_6FB70034[9] = {0, 0x201, (uint32_t)sub_6FAEE340, 0, 0x202, (uint32_t)sub_6FAEE490, 0, 0x200, (uint32_t)sub_6FAEE730};
//D2Client.0x6FB70058
uint32_t tbl_6FB70058[6] = {0, 0x201, (uint32_t)sub_6FAEEB30, 0, 0x200, (uint32_t)sub_6FADA310};
//D2Client.0x6FB70074
uint16_t word_6FB70074 = 0x2765;
//D2Client.0x6FB700B0
uint32_t dword_6FB700B0;
//D2Client.0x6FB8EA28
int32_t dword_6FB8EA28 = -1;
//D2Client.0x6FB8EA2C
int32_t dword_6FB8EA2C = -1;
//D2Client.0x6FB8EA30
uint32_t tbl_6FB8EA30[24] = {0, 0x204, (uint32_t)sub_6FAE9B60, 0, 0x201, (uint32_t)sub_6FAEA1C0, 0, 0x202, (uint32_t)sub_6FAEA850, 0, 0x200, (uint32_t)sub_6FAEA080, 3, 0x1B, (uint32_t)sub_6FAE9FC0, 3, 0x20, (uint32_t)sub_6FAE9FC0, 3, 0xD, (uint32_t)sub_6FAEABF0, 3, 0x57, (uint32_t)sub_6FAEC470};
//D2Client.0x6FB8EA90
uint32_t tbl_6FB8EA90[22] = {0, 0x204, (uint32_t)sub_6FB05A30, 0, 0x205, (uint32_t)sub_6FB05E40, 0, 0x201, (uint32_t)sub_6FB05A30, 0, 0x202, (uint32_t)sub_6FB05E40, 3, 0x1B, (uint32_t)sub_6FB060C0, 3, 0x1B, (uint32_t)sub_6FB060C0, 3, 0x1B, (uint32_t)sub_6FB060C0};
//D2Client.0x6FB8EAE8
uint32_t tbl_6FB8EAE8[40] = {0, 0x204, (uint32_t)sub_6FAEABD0, 0, 0x205, (uint32_t)sub_6FAEABD0, 0, 0x201, (uint32_t)sub_6FAEB2D0, 0, 0x202, (uint32_t)sub_6FAEB5B0, 0, 0x200, (uint32_t)sub_6FAEB1D0, 3, 0x1B, (uint32_t)sub_6FAEB870, 3, 0x20, (uint32_t)sub_6FAEB870, 3, 0xC0, (uint32_t)sub_6FAEC440, 3, 0xD, (uint32_t)sub_6FAEABF0, 3, 0x20, (uint32_t)sub_6FAEB870, 3, 0xC0, (uint32_t)sub_6FAEC440, 3, 0x4E, (uint32_t)sub_6FB200E0, 3, 0x57, (uint32_t)sub_6FAEC470};
//D2Client.0x6FB8EB88
uint32_t tbl_6FB8EB88[24] = {0, 0x204, (uint32_t)sub_6FAE9B60, 0, 0x201, (uint32_t)sub_6FAEBAD0, 0, 0x202, (uint32_t)sub_6FAEC030, 0, 0x200, (uint32_t)sub_6FAEB9F0, 3, 0x1B, (uint32_t)sub_6FAEC3B0, 3, 0x20, (uint32_t)sub_6FAEC3B0, 3, 0xD, (uint32_t)sub_6FAEABF0, 3, 0x57, (uint32_t)sub_6FAEC470};
//D2Client.0x6FB8EBE8
uint32_t tbl_6FB8EBE8[21] = {0, 0x204, (uint32_t)sub_6FAE9B60, 0, 0x201, (uint32_t)sub_6FAEC7C0, 0, 0x202, (uint32_t)sub_6FAECB60, 0, 0x200, (uint32_t)sub_6FAEC720, 3, 0x1B, (uint32_t)sub_6FAECEA0, 3, 0x20, (uint32_t)sub_6FAECEA0, 3, 0xD, (uint32_t)sub_6FAEABF0};
//D2Client.0x6FB8EC3C
uint32_t tbl_6FB8EC3C[6] = {3, 0x20, (uint32_t)sub_6FB01A00, 3, 0x20, (uint32_t)sub_6FB01A00};
//D2Client.0x6FB8EC58
uint32_t dword_6FB8EC58 = 1;
//D2Client.0x6FB8EC70
int32_t dword_6FB8EC70 = 2;
//D2Client.0x6FB8EC74
int32_t dword_6FB8EC74 = 148;
//D2Client.0x6FB8EC78
int32_t dword_6FB8EC78 = 64;
//D2Client.0x6FB8EC7C
int32_t dword_6FB8EC7C = 64;
//D2Client.0x6FB90310
uint8_t* ptr_6FB90310 = (uint8_t*)&unk_6FBBA7A0;
//D2Client.0x6FB903A8
int32_t dword_6FB903A8 = 38;
//D2Client.0x6FB903AC
int32_t dword_6FB903AC = 1;
//D2Client.0x6FB9067A
uint32_t dword_6FB9067A = 0xE0;
//D2Client.0x6FB9067E
uint32_t dword_6FB9067E = 0x100;
//D2Client.0x6FB90686
uint8_t byte_6FB90686;
//D2Client.0x6FB90687
uint8_t byte_6FB90687;
//D2Client.0x6FB906B0
int32_t dword_6FB906B0 = 2;
//D2Client.0x6FB906B8
uint8_t tbl_6FB906B8[30] = {0, 0, 0, 0, 2, 2, 0, 0, 0x20, 0x4B, 0xB2, 0x6F, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0x50, 0xB2, 0x6F, 0, 0, 0, 0, 4, 2};
//D2Client.0x6FB90717
uint32_t dword_6FB90717 = 0x6E656D6F;
//D2Client.0x6FBA798C
int32_t dword_6FBA798C;
//D2Client.0x6FBB9FC0
int32_t dword_6FBB9FC0;
//D2Client.0x6FBB9FC4
int32_t dword_6FBB9FC4;
//D2Client.0x6FBB9FC8
uint32_t* gpuint32_t_6FBB9FC8;
//D2Client.0x6FBB9FCC
int32_t* gpint32_t_6FBB9FCC;
//D2Client.0x6FBB9FD0
int32_t* gpint32_t_6FBB9FD0;
//D2Client.0x6FBB9FD4
uint32_t* gpuint32_t_6FBB9FD4;
//D2Client.0x6FBB9FD8
int32_t dword_6FBB9FD8;
//D2Client.0x6FBB9FE0
uint16_t word_6FBB9FE0;
//D2Client.0x6FBBA1E0
uint32_t dword_6FBBA1E0;
//D2Client.0x6FBBA1E8
D2CellFileStrc* gpCellFile_6FBBA1E8;
//D2Client.0x6FBBA1F0
uint32_t dword_6FBBA1F0;
//D2Client.0x6FBBA290
int32_t dword_6FBBA290;
//D2Client.0x6FBBA294
int32_t dword_6FBBA294;
//D2Client.0x6FBBA298
uint8_t byte_6FBBA298;
//D2Client.0x6FBBA2A0
uint16_t word_6FBBA2A0;
//D2Client.0x6FBBA4A0
uint8_t byte_6FBBA4A0;
//D2Client.0x6FBBA6A0
uint32_t dword_6FBBA6A0;
//D2Client.0x6FBBA6A8
uint32_t dword_6FBBA6A8;
//D2Client.0x6FBBA6AC
int32_t dword_6FBBA6AC;
//D2Client.0x6FBBA6B0
int32_t dword_6FBBA6B0;
//D2Client.0x6FBBA6B4
int32_t dword_6FBBA6B4;
//D2Client.0x6FBBA6B8
int32_t dword_6FBBA6B8;
//D2Client.0x6FBBA6BC
uint32_t dword_6FBBA6BC;
//D2Client.0x6FBBA6C0
int32_t dword_6FBBA6C0;
//D2Client.0x6FBBA6C4
int32_t dword_6FBBA6C4;
//D2Client.0x6FBBA6C8
int32_t dword_6FBBA6C8;
//D2Client.0x6FBBA6CC
int32_t dword_6FBBA6CC;
//D2Client.0x6FBBA6D0
int32_t dword_6FBBA6D0;
//D2Client.0x6FBBA6D4
int32_t dword_6FBBA6D4;
//D2Client.0x6FBBA6D8
int32_t dword_6FBBA6D8;
//D2Client.0x6FBBA6DC
int32_t dword_6FBBA6DC;
//D2Client.0x6FBBA6E0
int32_t dword_6FBBA6E0;
//D2Client.0x6FBBA6E4
int32_t dword_6FBBA6E4;
//D2Client.0x6FBBA6E8
int32_t dword_6FBBA6E8;
//D2Client.0x6FBBA6EC
int32_t dword_6FBBA6EC;
//D2Client.0x6FBBA6F0
int32_t dword_6FBBA6F0;
//D2Client.0x6FBBA6F4
int32_t dword_6FBBA6F4;
//D2Client.0x6FBBA6F8
int32_t dword_6FBBA6F8;
//D2Client.0x6FBBA6FC
int32_t dword_6FBBA6FC;
//D2Client.0x6FBBA700
int32_t dword_6FBBA700;
//D2Client.0x6FBBA704
int32_t dword_6FBBA704;
//D2Client.0x6FBBA708
int32_t dword_6FBBA708;
//D2Client.0x6FBBA70C
int32_t dword_6FBBA70C;
//D2Client.0x6FBBA710
int32_t dword_6FBBA710;
//D2Client.0x6FBBA714
int32_t dword_6FBBA714;
//D2Client.0x6FBBA718
int32_t dword_6FBBA718;
//D2Client.0x6FBBA71C
int32_t dword_6FBBA71C;
//D2Client.0x6FBBA720
int32_t dword_6FBBA720;
//D2Client.0x6FBBA724
int32_t dword_6FBBA724;
//D2Client.0x6FBBA728
int32_t dword_6FBBA728;
//D2Client.0x6FBBA72C
int32_t dword_6FBBA72C;
//D2Client.0x6FBBA730
int32_t dword_6FBBA730;
//D2Client.0x6FBBA734
int32_t dword_6FBBA734;
//D2Client.0x6FBBA738
int32_t dword_6FBBA738;
//D2Client.0x6FBBA73C
int32_t dword_6FBBA73C;
//D2Client.0x6FBBA740
int32_t dword_6FBBA740;
//D2Client.0x6FBBA744
int32_t dword_6FBBA744;
//D2Client.0x6FBBA754
uint8_t byte_6FBBA754;
//D2Client.0x6FBBA758
uint32_t dword_6FBBA758;
//D2Client.0x6FBBA774
uint8_t byte_6FBBA774;
//D2Client.0x6FBBA778
D2CellFileStrc* sghLoadScreenProgress;
//D2Client.0x6FBBA77C
uint8_t byte_6FBBA77C;
//D2Client.0x6FBBA780
uint8_t byte_6FBBA780;
//D2Client.0x6FBBA784
int32_t dword_6FBBA784;
//D2Client.0x6FBBA788
int32_t dword_6FBBA788;
//D2Client.0x6FBBA78C
D2CellFileStrc* gpCellFile_6FBBA78C;
//D2Client.0x6FBBA790
D2CellFileStrc* gpCellFile_6FBBA790;
//D2Client.0x6FBBA794
int32_t dword_6FBBA794;
//D2Client.0x6FBBA798
uint8_t byte_6FBBA798;
//D2Client.0x6FBBA968
uint32_t dword_6FBBA968;
//D2Client.0x6FBBA96C
uint32_t dword_6FBBA96C;
//D2Client.0x6FBBA970
uint8_t byte_6FBBA970;
//D2Client.0x6FBBA971
uint8_t byte_6FBBA971;
//D2Client.0x6FBBA974
DWORD dword_6FBBA974;
//D2Client.0x6FBBA97C
int32_t dword_6FBBA97C;
//D2Client.0x6FBBA980
uint8_t byte_6FBBA980;
//D2Client.0x6FBBA984
uint32_t dword_6FBBA984;
//D2Client.0x6FBBA99C
D2CellFileStrc* gpCellFile_6FBBA99C;
//D2Client.0x6FBBA9A0
D2CellFileStrc* gpCellFile_6FBBA9A0;

//D2Client.0x6FB20500
Unicode* __fastcall sub_6FB20500(Unicode* pUnicode)
{
	int iVar1;
	Unicode* a1;
	Unicode* a1_00;
	int iVar2;

	iVar1 = Unicode::strlen(pUnicode);
	if (iVar1 < 500)
	{
		a1 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9a));
		iVar1 = Unicode::strlen(a1);
		a1_00 = Unicode::strstr(pUnicode, a1);
		while ((a1_00 != nullptr && (a1_00[iVar1].ch != 0)))
		{
			iVar2 = Unicode::strlen(a1_00);
			memmove(a1_00, a1_00 + iVar1 + 1, (iVar2 - iVar1) * 2);
			a1_00 = Unicode::strstr(pUnicode, a1);
		}
		return pUnicode;
	}
	FOG_DisplayAssert("Unicode::strlen(pszSrc) < 500",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FB20590
void __fastcall sub_6FB20590(int a1, int a2, int a3, uint32_t a4)
{
	(*(uint16_t*)((uint8_t*)&dword_6FBBA1F0 + 0)) = 0;
	if (a1 != 0)
	{
		Unicode::strcpy((Unicode*)&dword_6FBBA1F0, (Unicode*)a1);
		dword_6FBBA294 = a3;
		byte_6FBBA298 = a4;
		dword_6FBBA290 = a2;
	}
}

//D2Client.0x6FB205D0
void __fastcall sub_6FB205D0(int a1, uint32_t a2)
{
	if (a1 == 0)
	{
		word_6FBB9FE0 = 0;
		return;
	}
	Unicode::strcpy((Unicode*)&word_6FBB9FE0, (Unicode*)a1);
	dword_6FBBA1E0 = a2;
}

//D2Client.0x6FB20600
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB20600(int* a1, short a2)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int* local_4;

	local_4 = a1;
	iVar2 = sub_6FAB5750();
	if (iVar2 == 3)
	{
		return 0;
	}
	iVar2 = sub_6FAFBB50((uint32_t*)(&local_4));
	if (iVar2 != 0)
	{
		return 0;
	}
	word_6FBBA2A0 = 0;
	bVar1 = sub_6FB40D00(a1);
	if (D2C_ZEXT(bVar1) == 0)
	{
		bVar1 = sub_6FB40D20(a1);
		if (D2C_ZEXT(bVar1) == 0)
		{
			return 0;
		}
	}
	sub_6FB462C0(a1, &word_6FBBA2A0, 0x100, a2);
	return 1;
}

//D2Client.0x6FB20670
int __fastcall sub_6FB20670(D2UnitStrc* pUnit)
{
	bool bVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	uint32_t uVar4;
	int iVar5;

	if ((pUnit == nullptr) || (pUnit->dwUnitType != 1))
	{
		return 0;
	}
	iVar2 = sub_6FB29550((int*)pUnit);
	if (iVar2 != 0)
	{
		return 0;
	}
	iVar2 = 0x80;
	if ((pUnit->dwFlags >> 2 & 1) == 0)
	{
	LAB_6fb206c6:
		bVar1 = false;
	}
	else
	{
		pDVar3 = CUNIT_GetPlayer();
		uVar4 = sub_6FB29D80(pDVar3, pUnit);
		if (uVar4 == 0)
			goto LAB_6fb206c6;
		bVar1 = true;
	}
	iVar5 = sub_6FAB1AC0(pUnit->dwUnitId);
	if ((bVar1) || (iVar5 < 1))
	{
		iVar5 = STATLIST_GetMaxLifeFromUnit(pUnit);
		if (iVar5 == 0)
			goto LAB_6fb20715;
		iVar2 = STATLIST_UnitGetStatValue(pUnit, 6, 0);
		iVar2 = (iVar2 << 7) / iVar5;
	}
	else
	{
		iVar2 = (iVar5 << 7) / 100;
	}
	if (iVar2 < 3)
	{
		return 2;
	}
LAB_6fb20715:
	if (0x7f < iVar2)
	{
		iVar2 = 0x80;
	}
	return iVar2;
}

//D2Client.0x6FB20740
void __fastcall sub_6FB20740(D2UnitStrc* pUnit, Unicode* pUnicode, int a3)
{
	Unicode* pUVar1;
	int iVar2;
	D2ItemsTxt* pDVar3;
	uint32_t uVar4;
	Unicode* pUVar5;
	int nTextColor;
	int iVar6;
	CHAR aCStack_220[12];
	Unicode aUStack_214[10];
	Unicode UStack_200;
	Unicode aUStack_1fe[127];
	Unicode UStack_100;
	Unicode aUStack_fe[127];

	dword_6FB8EA2C = dword_6FB8EA2C + -0x10;
	if (pUnit != nullptr)
	{
		pUVar1 = sub_6FB297F0(pUnit);
		nTextColor = 0;
		iVar2 = ITEMS_GetItemQuality(pUnit);
		switch (iVar2)
		{
		case 4:
			nTextColor = 3;
			break;
		case 5:
			nTextColor = 2;
			break;
		case 6:
			nTextColor = 9;
			break;
		case 7:
			nTextColor = 4;
			break;
		case 8:
			nTextColor = 8;
			break;
		case 9:
			nTextColor = 10;
			break;
		default:
			iVar2 = ITEMS_CheckItemFlag(pUnit, 0x800, __LINE__, __FILE__);
			if ((iVar2 != 0) ||
			    (iVar2 = ITEMS_CheckItemFlag(pUnit, 0x400000, __LINE__, __FILE__), iVar2 != 0))
			{
				nTextColor = 5;
			}
		}
		pDVar3 = DATATBLS_GetItemsTxtRecord(pUnit->dwClassId);
		if ((pDVar3->nQuest != 0) && (pDVar3->dwCode != 0x2067656c))
		{
			nTextColor = 4;
		}
		UStack_200.ch = 0;
		pUVar5 = aUStack_1fe;
		for (iVar2 = 0x3f; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*(uint32_t*)pUVar5 = 0;
			pUVar5 = pUVar5 + 2;
		}
		pUVar5->ch = 0;
		uVar4 = ITEMS_GetItemType(pUnit);
		if (uVar4 == 4)
		{
			iVar2 = STATLIST_UnitGetStatValue(pUnit, 0xe, 0);
			wsprintfA(aCStack_220, "%i", iVar2);
			Unicode::win2Unicode(aUStack_214, aCStack_220, 9);
			Unicode::strcpy(&UStack_200, aUStack_214);
			pUVar5 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
			Unicode::strcat(&UStack_200, pUVar5);
			Unicode::strcat(&UStack_200, pUVar1);
			if (pUnicode != nullptr)
			{
				sub_6FB20430((short*)&UStack_200, (char)nTextColor);
				iVar2 = Unicode::strlen(&UStack_200);
				if (iVar2 < a3)
				{
					Unicode::strcpy(pUnicode, &UStack_200);
					return;
				}
				FOG_DisplayAssert("Unicode::strlen(szString) < nSize",
				    __FILE__, __LINE__);
				exit(-1);
			}
			D2Win_10129_DrawFramedText(&UStack_200, dword_6FB8EA28, dword_6FB8EA2C, nTextColor, 1);
			return;
		}
		UStack_100.ch = 0;
		pUVar1 = aUStack_fe;
		for (iVar2 = 0x3f; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			*(uint32_t*)pUVar1 = 0;
			pUVar1 = pUVar1 + 2;
		}
		pUVar1->ch = 0;
		sub_6FADD360(0x100);
		if (pUnicode == nullptr)
		{
			D2Win_10129_DrawFramedText(&UStack_100, dword_6FB8EA28, dword_6FB8EA2C, nTextColor, 1);
			return;
		}
		sub_6FB20430((short*)&UStack_100, (char)nTextColor);
		iVar2 = Unicode::strlen(&UStack_100);
		D2_ASSERT(a3 > iVar2);
		Unicode::strcpy(pUnicode, &UStack_100);
	}
}

//D2Client.0x6FB20A30
// TODO: decompilation needs review (extraout, in_stack, stack0x, unaff_)
void __cdecl sub_6FB20A30()
{
	uint8_t stack0x00000000[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000004[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000008[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x0000000c[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000010[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000014[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000024[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000124[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000001a4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000001a6[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000002a4[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x000002a6[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000434[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	uint8_t stack0x00000834[0x100]; // TODO: stack reference that Ghidra could not map to a variable
	char cVar1;
	uint8_t bVar2;
	bool bVar3;
	uint8_t uVar4;
	int iVar5;
	D2UnitStrc* pDVar6;
	int iVar7;
	int iVar8;
	uint32_t uVar9;
	uint32_t extraout_var;
	Font nFontSize;
	D2C_Language DVar10;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t extraout_var_02;
	int iVar11;
	uint32_t extraout_var_03;
	uint32_t extraout_var_04;
	uint32_t uVar12;
	D2ObjectsTxt* pDVar13;
	D2LevelsTxt* pDVar14;
	uint32_t extraout_var_05;
	char* pcVar15;
	D2ActiveRoomStrc* pDVar16;
	D2LvlWarpTxt* pDVar17;
	uint32_t extraout_var_06;
	Unicode* pUVar18;
	D2UnitStrc* pUnit1;
	short sVar19;
	uint32_t* puVar20;
	int unaff_retaddr;
	D2LevelsTxt* in_stack_00000004;
	Font in_stack_00000008;
	int in_stack_0000000c;
	int in_stack_00000014;
	int in_stack_0000001c;
	Unicode UStack000001a4;

	iVar5 = sub_6FAB5750();
	if (iVar5 == 3)
	{
		return;
	}
	if (pUnit1 == nullptr)
	{
		return;
	}
	if (pUnit1->dwUnitType == 5)
	{
		pDVar6 = CUNIT_GetPlayer();
		iVar5 = UNITS_GetDistanceToOtherUnit(pUnit1, pDVar6);
		if (100 < iVar5)
		{
			return;
		}
	}
	iVar5 = D2GFX_CheckPerspective();
	if (iVar5 == 0)
	{
		iVar5 = UNITS_GetClientCoordX(pUnit1);
		iVar7 = sub_6FAB5890();
		dword_6FB8EA28 = iVar5 - iVar7;
		iVar5 = UNITS_GetClientCoordY(pUnit1);
		iVar7 = sub_6FAB58A0();
		dword_6FB8EA2C = iVar5 - iVar7;
	}
	else
	{
		iVar5 = UNITS_GetPrecisionX(pUnit1);
		iVar7 = UNITS_GetPrecisionY(pUnit1);
		iVar8 = SCALE_CheckPerspectivePosition(iVar5, iVar7);
		if (iVar8 == 0)
		{
			return;
		}
		SCALE_AdjustPerspectivePosition(iVar5, iVar7, 0, (int*)stack0x00000000, (int*)stack0x00000008);
		iVar5 = sub_6FAB5750();
		if (iVar5 == 1)
		{
			iVar5 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
		LAB_6fb20ad9:
			dword_6FB8EA28 = unaff_retaddr + iVar5;
		}
		else
		{
			dword_6FB8EA28 = unaff_retaddr;
			if (iVar5 == 2)
			{
				iVar5 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
				goto LAB_6fb20ad9;
			}
		}
		dword_6FB8EA2C = in_stack_00000008 + 0x10;
	}
	switch (pUnit1->dwUnitType)
	{
	case 0:
		pUVar18 = (Unicode*)stack0x00000024;
		iVar5 = 0x80;
		do
		{
			pUVar18 = pUVar18 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		sub_6FB21680(pUnit1, (int*)stack0x00000008, (Unicode*)stack0x0000000c,
		    (Unicode*)stack0x00000024, 0x80);
		D2Win_10130_DrawFramedTextEx((Unicode*)stack0x00000024, dword_6FB8EA28, dword_6FB8EA2C + -0x48, in_stack_0000000c, 1,
		    in_stack_00000008);
		return;
	case 1:
		iVar5 = pUnit1->dwClassId;
		if ((iVar5 == 0x1a1) || (iVar5 == 0x1a2))
		{
			if (iVar5 < 0)
			{
				word_6FBB9FE0 = 0;
				word_6FBBA2A0 = 0;
				byte_6FBBA4A0 = 0;
				return;
			}
			if (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= iVar5)
			{
				word_6FBB9FE0 = 0;
				word_6FBBA2A0 = 0;
				byte_6FBBA4A0 = 0;
				return;
			}
			iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + iVar5 * 0x1a8;
			if (iVar5 == 0)
			{
				word_6FBB9FE0 = 0;
				word_6FBBA2A0 = 0;
				byte_6FBBA4A0 = 0;
				return;
			}
			pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar5 + 6)));
			MONSTERS_SetMonsterNameInMonsterData(pUnit1, pUVar18);
			iVar5 = sub_6FAFBB50((uint32_t*)(stack0x00000004));
			if (iVar5 != 0)
			{
				word_6FBB9FE0 = 0;
				word_6FBBA2A0 = 0;
				byte_6FBBA4A0 = 0;
				return;
			}
			iVar5 = sub_6FB20670(pUnit1);
		}
		else
		{
			in_stack_00000004 = (D2LevelsTxt*)(pUnit1->dwFlags >> 9 & 1);
			if (in_stack_00000004 == nullptr)
			{
				in_stack_00000004 = nullptr;
				if (iVar5 == 0x164)
				{
					pUVar18 = (Unicode*)stack0x00000024;
					iVar5 = 0x80;
					do
					{
						pUVar18 = pUVar18 + 1;
						iVar5 = iVar5 + -1;
					} while (iVar5 != 0);
					iVar5 = sub_6FAB1B00(pUnit1->dwUnitId);
					if (iVar5 != -1)
					{
						if (pUnit1->dwAnimMode == 0)
						{
							return;
						}
						if (pUnit1->dwAnimMode == 0xc)
						{
							return;
						}
						pcVar15 = (char*)sub_6FAB0BC0(iVar5);
						if (pcVar15 != nullptr)
						{
							Unicode::toUnicode((Unicode*)stack0x00000024, pcVar15, 0x80);
							iVar7 = sub_6FAB1460(iVar5);
							pDVar6 = CUNIT_GetPlayer();
							if (pDVar6 == nullptr)
							{
								uVar9 = 0xffffffff;
							}
							else
							{
								uVar9 = pDVar6->dwUnitId;
							}
							bVar3 = sub_6FAB07D0(uVar9, iVar5);
							D2Win_10130_DrawFramedTextEx((Unicode*)stack0x00000024, dword_6FB8EA28, dword_6FB8EA2C + -0x48,
							    (uint32_t)(D2C_ZEXT(bVar3) != 0), 1, (iVar7 << 7) / 100);
							return;
						}
					}
				}
				nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
				in_stack_00000004 = (D2LevelsTxt*)pUnit1->dwClassId;
				if (((int)in_stack_00000004 < 0) ||
				    (*(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa80) <= (int)in_stack_00000004))
				{
					iVar5 = 0;
				}
				else
				{
					iVar5 = *(int*)(*(int*)((uint8_t*)&sgptDataTables) + 0xa78) + (int)in_stack_00000004 * 0x1a8;
				}
				in_stack_0000000c = 0;
				in_stack_00000008 = nFontSize;
				memset(stack0x00000834, 0, 2 * (0x800));
				if ((((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 4) & (uint32_t) * (uint8_t*)(iVar5 + 0xd)) != 0) ||
				        ((*(uint32_t*)(((uint8_t*)&gdwBitMasks) + 0x1c) & (uint32_t) * (uint8_t*)(iVar5 + 0xd)) == 0)) ||
				    (*(short*)(iVar5 + 6) == 0))
				{
					word_6FBBA2A0 = 0;
					iVar5 = sub_6FAFBB50((uint32_t*)(stack0x00000004));
					if ((iVar5 == 0) && (bVar3 = sub_6FB1EE90(), D2C_ZEXT(bVar3) == 0))
					{
						iVar5 = sub_6FB247F0(pUnit1->dwClassId);
						if (iVar5 != 0)
						{
							dword_6FB8EA2C = dword_6FB8EA2C - (uint32_t) * (uint8_t*)(iVar5 + 0xd);
						}
						iVar8 = 1;
						iVar7 = 0;
						iVar5 = dword_6FB8EA2C;
						pUVar18 = sub_6FB297F0(pUnit1);
						D2Win_10129_DrawFramedText(pUVar18, dword_6FB8EA28, iVar5, iVar7, iVar8);
						D2Win_10127_SetFont(in_stack_00000008);
						return;
					}
					D2Win_10127_SetFont(nFontSize);
					return;
				}
				iVar5 = sub_6FB247F0(pUnit1->dwClassId);
				if (iVar5 != 0)
				{
					dword_6FB8EA2C = dword_6FB8EA2C - (uint32_t) * (uint8_t*)(iVar5 + 0xd);
				}
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				Unicode::strcpy((Unicode*)stack0x00000834, pUVar18);
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
				pUVar18 = sub_6FB297F0(pUnit1);
				Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
				if (pUnit1->dwAnimMode == 0xc)
				{
					pDVar16 = UNITS_GetRoom(pUnit1);
					iVar5 = DUNGEON_IsRoomInTown(pDVar16);
					if (iVar5 != 0)
					{
						return;
					}
					in_stack_0000000c = 1;
					DVar10 = STRTABLE_GetLanguage();
					if (DVar10 == LANGUAGE_ENGLISH)
					{
						pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x90b));
					}
					else
					{
						memset(stack0x00000010, 0, 2 * (2));
						iVar5 = 0;
						do
						{
							cVar1 = ("(")[iVar5];
							(stack0x00000000)[iVar5] = cVar1;
							iVar5 = iVar5 + 1;
						} while (cVar1 != '\0');
						Unicode::win2Unicode((Unicode*)stack0x00000010, (const char*)(stack0x00000000), 2);
						Unicode::strcat((Unicode*)stack0x00000834, (Unicode*)stack0x00000010);
						pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x90b));
						Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
						iVar5 = 0;
						do
						{
							cVar1 = (&byte_6FB796FC)[iVar5];
							(stack0x00000000)[iVar5] = cVar1;
							iVar5 = iVar5 + 1;
						} while (cVar1 != '\0');
						Unicode::win2Unicode((Unicode*)stack0x00000010, (const char*)(stack0x00000000), 2);
						pUVar18 = (Unicode*)stack0x00000010;
					}
					Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
					pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
					Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
				}
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				Unicode::strcat((Unicode*)stack0x00000834, pUVar18);
				iVar5 = sub_6FB20670(pUnit1);
				iVar7 = 0;
				iVar8 = 0;
				bVar3 = sub_6FB40D00((int*)pUnit1);
				if (D2C_ZEXT(bVar3) != 0)
				{
					iVar7 = 4;
					iVar8 = 4;
				}
				bVar3 = sub_6FB40CC0((int*)pUnit1);
				if (D2C_ZEXT(bVar3) != 0)
				{
					iVar7 = 3;
					iVar8 = 3;
				}
				if (in_stack_0000000c != 0)
				{
					iVar7 = 1;
					iVar8 = 1;
				}
				if ((((in_stack_00000004 == (D2LevelsTxt*)0xf3) ||
				         (in_stack_00000004 == (D2LevelsTxt*)0x14d)) ||
				        ((in_stack_00000004 == (D2LevelsTxt*)0xf2 ||
				            (((in_stack_00000004 == (D2LevelsTxt*)0xd3 ||
				                  (in_stack_00000004 == (D2LevelsTxt*)0x220)) ||
				                (in_stack_00000004 == (D2LevelsTxt*)0x23a)))))) ||
				    (in_stack_00000004 == (D2LevelsTxt*)0xe5))
				{
					iVar7 = 4;
					iVar8 = 4;
				}
				bVar3 = sub_6FB24690((int*)(stack0x00000014));
				if (D2C_ZEXT(bVar3) == 0)
				{
					D2Win_10127_SetFont(in_stack_00000008);
					return;
				}
				iVar11 = D2Win_10121_GetTextWidth((Unicode*)stack0x00000834);
				D2Win_10130_DrawFramedTextEx((Unicode*)stack0x00000834,
				    (in_stack_0000001c + in_stack_00000014 >> 1) - (iVar11 >> 1), 0x20, iVar7, 0, iVar5);
				if (in_stack_0000000c != 0)
				{
					word_6FBBA2A0 = 0;
					D2Win_10127_SetFont(in_stack_00000008);
					return;
				}
				iVar5 = sub_6FAAE570(pUnit1->dwClassId);
				sVar19 = 0;
				iVar7 = MONSTERS_IsDemon(pUnit1);
				if (iVar7 == 0)
				{
					iVar7 = MONSTERS_IsUndead(pUnit1);
					if (iVar7 != 0)
					{
						sVar19 = 0x275d;
					}
				}
				else
				{
					sVar19 = 0x275e;
				}
				iVar7 = sub_6FB20600((int*)pUnit1, sVar19);
				if (iVar7 == 0)
				{
					if (sVar19 == 0)
					{
						if (*(short*)(iVar5 + 8) == 0x1506)
							goto LAB_6fb2109c;
						pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar5 + 8)));
					}
					else
					{
						memset(stack0x00000434, 0, 2 * (0x200));
						pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar19));
						Unicode::strcpy((Unicode*)stack0x00000434, pUVar18);
						pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
						Unicode::strcat((Unicode*)stack0x00000434, pUVar18);
						if (*(short*)(iVar5 + 8) != 0x1506)
						{
							pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(*(short*)(iVar5 + 8)));
							Unicode::strcat((Unicode*)stack0x00000434, pUVar18);
						}
						pUVar18 = (Unicode*)stack0x00000434;
					}
					sub_6FB205D0((int)pUVar18, iVar8);
				}
			LAB_6fb2109c:
				sub_6FB21570(pUnit1);
				D2Win_10127_SetFont(in_stack_00000008);
				return;
			}
			iVar5 = sub_6FAFBB50((uint32_t*)(stack0x00000004));
			if (iVar5 != 0)
			{
				word_6FBB9FE0 = 0;
				word_6FBBA2A0 = 0;
				byte_6FBBA4A0 = 0;
				return;
			}
			iVar5 = sub_6FB20670(pUnit1);
		}
		iVar7 = dword_6FB8EA28;
		iVar8 = dword_6FB8EA2C + -0x48;
		pUVar18 = sub_6FB297F0(pUnit1);
		D2Win_10130_DrawFramedTextEx(pUVar18, iVar7, iVar8, 0, 1, iVar5);
		word_6FBB9FE0 = 0;
		byte_6FBBA4A0 = 0;
		word_6FBBA2A0 = 0;
		return;
	case 2:
		pUVar18 = (Unicode*)stack0x000002a4;
		iVar5 = 0x80;
		do
		{
			pUVar18 = pUVar18 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		pUVar18 = (Unicode*)stack0x00000434;
		iVar5 = 0x100;
		do
		{
			pUVar18 = pUVar18 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		UStack000001a4.ch = 0;
		puVar20 = (uint32_t*)stack0x000001a6;
		for (iVar5 = 0x3f; iVar5 != 0; iVar5 = iVar5 + -1)
		{
			*puVar20 = 0;
			puVar20 = puVar20 + 1;
		}
		*(uint16_t*)puVar20 = 0;
		pUVar18 = (Unicode*)stack0x000001a6;
		iVar5 = 0x7f;
		do
		{
			pUVar18 = pUVar18 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		iVar5 = sub_6FAFBB50((uint32_t*)(stack0x00000004));
		if (iVar5 != 0)
		{
			return;
		}
		bVar3 = sub_6FB1EE90();
		if (D2C_ZEXT(bVar3) == 1)
		{
			return;
		}
		pUVar18 = sub_6FB297F0(pUnit1);
		uVar9 = pUnit1->dwClassId;
		uVar12 = UNITS_GetNameOffsetFromObject(pUnit1);
		pDVar13 = DATATBLS_GetObjectsTxtRecord(uVar9 & 0xffff);
		bVar2 = pDVar13->nSubClass;
		if ((bVar2 & 4) == 0)
		{
			if ((char)bVar2 < '\0')
			{
				return;
			}
			if ((bVar2 & 0x40) != 0)
			{
				pUVar18 = sub_6FB297F0(pUnit1);
				pDVar16 = UNITS_GetRoom(pUnit1);
				if (pDVar16 == nullptr)
				{
					return;
				}
				iVar5 = DUNGEON_GetLevelIdFromRoom(pDVar16);
				pDVar14 = DATATBLS_GetLevelsTxtRecord(iVar5);
				Unicode::strcpy((Unicode*)stack0x00000434, pUVar18);
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
				Unicode::strcat((Unicode*)stack0x00000434, pUVar18);
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9e));
				Unicode::strcat((Unicode*)stack0x00000434, pUVar18);
				pUVar18 = (Unicode*)(D2LANG_GetStringByReferenceString(pDVar14->szLevelName));
				Unicode::strcat((Unicode*)stack0x00000434, pUVar18);
				D2Win_10129_DrawFramedText((Unicode*)stack0x00000434, dword_6FB8EA28, dword_6FB8EA2C + uVar12, 0, 1);
				return;
			}
			D2Win_10129_DrawFramedText(pUVar18, dword_6FB8EA28, dword_6FB8EA2C + uVar12, 0, 1);
			return;
		}
		pUVar18 = (Unicode*)stack0x00000024;
		iVar5 = 0x80;
		do
		{
			pUVar18 = pUVar18 + 1;
			iVar5 = iVar5 + -1;
		} while (iVar5 != 0);
		uVar9 = (uint32_t)(uint8_t)pUnit1->pPlayerData->szName[4];
		pDVar14 = DATATBLS_GetLevelsTxtRecord(uVar9);
		if (pDVar14 == nullptr)
		{
			sVar19 = 0x150d;
		LAB_6fb212cd:
			pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar19));
		}
		else
		{
			if (uVar9 == 8)
			{
				uVar4 = D2Client_10002(0, 1);
				if (D2C_ZEXT(uVar4) == 0)
				{
					sVar19 = 0x13b7;
				}
				else
				{
					sVar19 = 0x13b8;
				}
				goto LAB_6fb212cd;
			}
			pUVar18 = pDVar14->wszLevelName;
		}
		Unicode::strcpy((Unicode*)(stack0x000001a4), pUVar18);
		if ((gnGameType != 0) && (gnGameType != 1))
		{
			iVar5 = sub_6FAB0D00(pUnit1->dwUnitId);
			if (iVar5 == 0)
			{
				pcVar15 = (char*)sub_6FB48550((int)pUnit1);
				iVar5 = -1;
				do
				{
					if (iVar5 == 0)
						break;
					iVar5 = iVar5 + -1;
					cVar1 = *pcVar15;
					pcVar15 = pcVar15 + 1;
				} while (cVar1 != '\0');
				if (iVar5 == -2)
					goto LAB_6fb21364;
				sub_6FB48550((int)pUnit1);
			}
			sprintf((char*)(stack0x00000124), " (%s) ");
			Unicode::win2Unicode((Unicode*)stack0x00000024, (const char*)(stack0x00000124), 0x80);
			Unicode::strcat((Unicode*)(stack0x000001a4), (Unicode*)stack0x00000024);
		}
	LAB_6fb21364:
		D2Win_10129_DrawFramedText((const Unicode*)(stack0x000001a4), dword_6FB8EA28, dword_6FB8EA2C + uVar12, 0, 1);
		return;
	case 4:
		if (dword_6FBBA6DC == 0)
		{
			sub_6FB20740(pUnit1, nullptr, 0);
			return;
		}
		break;
	case 5:
		pDVar16 = UNITS_GetRoom(pUnit1);
		in_stack_00000008 = (Font)(DUNGEON_GetWarpDestinationLevel(pDVar16, pUnit1->dwClassId));
		in_stack_00000004 = DATATBLS_GetLevelsTxtRecord(in_stack_00000008);
		if ((in_stack_00000004 != nullptr) &&
		    (pDVar17 = DUNGEON_GetLvlWarpTxtRecordFromRoomAndUnit(pDVar16, pUnit1),
		        pDVar17 != nullptr))
		{
			iVar8 = (pDVar17->dwSelectDX >> 1) + pDVar17->dwSelectX + dword_6FB8EA28;
			iVar7 = (pDVar17->dwSelectDY >> 1) + pDVar17->dwSelectY + dword_6FB8EA2C;
			puVar20 = (uint32_t*)stack0x000002a6;
			for (iVar5 = 99; iVar5 != 0; iVar5 = iVar5 + -1)
			{
				*puVar20 = 0;
				puVar20 = puVar20 + 1;
			}
			*(uint16_t*)puVar20 = 0;
			pUVar18 = (Unicode*)stack0x000002a6;
			iVar5 = 199;
			do
			{
				pUVar18 = pUVar18 + 1;
				iVar5 = iVar5 + -1;
			} while (iVar5 != 0);
			pUVar18 = in_stack_00000004->wszLevelWarp;
			if (in_stack_00000008 == 8)
			{
				uVar4 = D2Client_10002(0, 1);
				sVar19 = 0x13de;
				if (D2C_ZEXT(uVar4) == 0)
				{
					sVar19 = 0x13dd;
				}
				pUVar18 = (Unicode*)(D2LANG_GetStringFromTblIndex(sVar19));
			}
			Unicode::strncpy((Unicode*)stack0x000002a4, pUVar18, 199);
			D2Win_10129_DrawFramedText((Unicode*)stack0x000002a4, iVar8, iVar7, 0, 1);
		}
	}
}

//D2Client.0x6FB21570
void __fastcall sub_6FB21570(D2UnitStrc* pUnit)
{
	Unicode* a2;
	Unicode* a2_00;
	Unicode* pUVar1;
	int iVar2;
	short* psVar3;
	Unicode aUStack_400[256];
	Unicode aUStack_200[256];

	a2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf9b));
	a2_00 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0c));
	aUStack_400[0].ch = 0;
	psVar3 = (short*)(&word_6FB70074);
	do
	{
		iVar2 = STATLIST_UnitGetStatValue(pUnit, *(int*)(psVar3 + -2), 0);
		if (99 < iVar2)
		{
			if (aUStack_400[0].ch != 0)
			{
				Unicode::strcat(aUStack_400, a2_00);
				Unicode::strcat(aUStack_400, a2);
			}
			pUVar1 = (Unicode*)(D2LANG_GetStringFromTblIndex(*psVar3));
			Unicode::strcpy(aUStack_200, pUVar1);
			sub_6FB20430((short*)aUStack_200, (char)*(uint32_t*)(psVar3 + 1));
			Unicode::strcat(aUStack_400, aUStack_200);
		}
		psVar3 = psVar3 + 5;
	} while ((int)psVar3 < (int)&dword_6FB700B0);
	Unicode::strcpy((Unicode*)&byte_6FBBA4A0, aUStack_400);
	dword_6FBBA6A0 = 4;
}

//D2Client.0x6FB21680
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB21680(D2UnitStrc* pUnit, int* a22, Unicode* pUnicode, Unicode* pUnicode2, int a52)
{
	bool bVar1;
	char* a2;
	D2C_Language a5;
	Unicode* pUVar2;
	D2UnitStrc* pDVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	uint32_t uVar5;
	int iVar6;
	Unicode local_100[128];

	a2 = (char*)sub_6FAB0C00(pUnit);
	if (pUnit == nullptr)
	{
		uVar5 = 0xffffffff;
	}
	else
	{
		if (pUnit->dwAnimMode == 0x11)
		{
			*a22 = 0;
			Unicode::win2Unicode(local_100, a2, 0x80);
			a5 = STRTABLE_GetLanguage();
			pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x90b));
			Unicode::Personalize((Unicode*)pUnicode2, local_100, pUVar2, a52, (ELANGUAGE)(a5));
			*(uint32_t*)pUnicode = 1;
			return;
		}
		uVar5 = pUnit->dwUnitId;
	}
	iVar6 = sub_6FAB1460(uVar5);
	*a22 = (iVar6 << 7) / 100;
	*(uint32_t*)pUnicode = 0;
	if (pUnit == nullptr)
	{
		uVar5 = 0xffffffff;
	}
	else
	{
		uVar5 = pUnit->dwUnitId;
	}
	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		uVar4 = 0xffffffff;
	}
	else
	{
		uVar4 = pDVar3->dwUnitId;
	}
	bVar1 = sub_6FAB07D0(uVar4, uVar5);
	if (D2C_ZEXT(bVar1) != 0)
	{
		*(uint32_t*)pUnicode = 1;
	}
	Unicode::win2Unicode((Unicode*)pUnicode2, a2, 0x80);
}

//D2Client.0x6FB21790
void __fastcall sub_6FB21790(int* a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int nXPos;
	int iVar4;
	int iVar5;
	D2GfxDataStrc* pDVar6;
	int iVar7;
	D2GfxDataStrc local_48;

	nXPos = *a1;
	iVar4 = a1[1];
	iVar2 = (a1[2] - nXPos) + 1 + nXPos;
	iVar3 = (a1[3] - iVar4) + 1 + iVar4;
	pDVar6 = &local_48;
	for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1)
	{
		pDVar6->pCurrentCell = nullptr;
		pDVar6 = (D2GfxDataStrc*)&pDVar6->pCellFile;
	}
	iVar5 = 0;
	local_48.nDirection = 0;
	local_48.pCellFile = gpCellFile_6FBBA1E4;
	iVar7 = nXPos;
	while (iVar7 = iVar7 + 0xc, iVar7 < iVar2 + -0xd)
	{
		iVar5 = iVar5 + 1;
		local_48.nFrame = iVar5 % 6 + 2;
		TEXTURE_CelDraw(&local_48, iVar7, iVar4 + 0xc, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	for (iVar7 = nXPos + 0xd; iVar7 < iVar2 + -0xd; iVar7 = iVar7 + 0xc)
	{
		iVar5 = iVar5 + 1;
		local_48.nFrame = iVar5 % 6 + 0x10;
		TEXTURE_CelDraw(&local_48, iVar7, iVar3 + 10, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	}
	iVar7 = iVar4 + 0x16;
	iVar1 = iVar3 + -1;
	if (iVar7 < iVar1)
	{
		do
		{
			iVar5 = iVar5 + 1;
			local_48.nFrame = iVar5 % 3 + 10;
			TEXTURE_CelDraw(&local_48, nXPos + -4, iVar7, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			iVar7 = iVar7 + 0xc;
		} while (iVar7 < iVar1);
	}
	iVar7 = iVar4 + 0x18;
	if (iVar7 < iVar1)
	{
		do
		{
			iVar5 = iVar5 + 1;
			local_48.nFrame = iVar5 % 3 + 0xd;
			TEXTURE_CelDraw(&local_48, iVar2 + -7, iVar7, 0xffffffff, DRAWMODE_NORMAL, nullptr);
			iVar7 = iVar7 + 0xc;
		} while (iVar7 < iVar1);
	}
	local_48.nFrame = 0;
	TEXTURE_CelDraw(&local_48, nXPos, iVar4 + 0xc, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 1;
	TEXTURE_CelDraw(&local_48, iVar2 + -0xc, iVar4 + 0xc, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 8;
	TEXTURE_CelDraw(&local_48, nXPos, iVar3 + 1, 0xffffffff, DRAWMODE_NORMAL, nullptr);
	local_48.nFrame = 9;
	TEXTURE_CelDraw(&local_48, iVar2 + -0xc, iVar3 + 1, 0xffffffff, DRAWMODE_NORMAL, nullptr);
}

//D2Client.0x6FB21970
void __cdecl sub_6FB21970()
{
	int iVar1;
	int iVar2;
	int nX;
	uint32_t* puVar3;

	iVar1 = Unicode::strlen((Unicode*)&dword_6FBBA1F0);
	if (iVar1 != 0)
	{
		iVar1 = D2Win_10121_GetTextWidth((Unicode*)&dword_6FBBA1F0);
		iVar1 = iVar1 + 8;
		iVar2 = D2Win_10125();
		nX = dword_6FBBA290 - (iVar1 >> 1);
		if (nX < 0)
		{
			nX = 0;
		}
		if (gnScreenWidth < nX + iVar1)
		{
			nX = gnScreenWidth - iVar1;
		}
		iVar1 = dword_6FBBA294 + 2;
		if ((dword_6FBBA294 + 2) - (iVar2 + 7) < 0)
		{
			iVar1 = iVar2 + 7;
		}
		if (gnScreenHeight + -0x1f < iVar1)
		{
			iVar1 = gnScreenHeight + -0x1f;
		}
		D2Win_10117_DrawText((Unicode*)&dword_6FBBA1F0, nX, iVar1 + -2, 0, 1);
		puVar3 = &dword_6FBBA1F0;
		for (iVar1 = 0x28; iVar1 != 0; iVar1 = iVar1 + -1)
		{
			*puVar3 = 0;
			puVar3 = puVar3 + 1;
		}
	}
}

//D2Client.0x6FB21A00
void __cdecl sub_6FB21A00()
{
	short sVar1;
	D2UnitStrc* pDVar2;
	D2ActiveRoomStrc* pDVar3;
	D2GameResolutionMode DVar4;
	int iVar5;
	D2StatListStrc* pDVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iStack_4;

	if (ghAct != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 != nullptr)
		{
			pDVar2 = CUNIT_GetPlayer();
			pDVar3 = UNITS_GetRoom(pDVar2);
			if ((pDVar3 != nullptr) && (dword_6FBBA794 != 0))
			{
				iStack_4 = gnScreenHeight - dword_6FB8EC78;
				iVar7 = gnScreenWidth - dword_6FB8EC74;
				DVar4 = D2GFX_GetResolutionMode();
				if (DVar4 == NUM_GAME_RESOLUTIONS)
				{
					iStack_4 = gnScreenHeight - dword_6FB8EC7C;
				}
				pDVar2 = CUNIT_GetPlayer();
				iVar8 = 0;
				iVar5 = *(int*)((uint8_t*)&sgptDataTables);
				if (0 < *(short*)(iVar5 + 0x170))
				{
					do
					{
						iVar9 = (int)*(short*)(*(int*)(iVar5 + 0x16c) + iVar8 * 2);
						iVar5 = STATES_CheckState(pDVar2, iVar9);
						if (iVar5 != 0)
						{
							pDVar6 = STATLIST_GetStatListFromUnitAndState(pDVar2, iVar9);
							if ((((((pDVar6 != nullptr) && (-1 < iVar9)) &&
							          (iVar5 = *(int*)((uint8_t*)&sgptDataTables), iVar9 < *(int*)(iVar5 + 0xc4))) &&
							         ((iVar9 = *(int*)(iVar5 + 0xbc) + iVar9 * 0x3c, iVar9 != 0 &&
							                                                             (((uint8_t)((uint8_t*)&gdwBitMasks)[0x10] & *(uint8_t*)(iVar9 + 0x10)) != 0)))) &&
							        ((0 < *(short*)(iVar9 + 0xe) &&
							            (((int)*(short*)(iVar9 + 0xe) < *(int*)(iVar5 + 0xbc0) &&
							                (sVar1 = *(short*)(iVar9 + 0x18), -1 < sVar1)))))) &&
							    ((int)sVar1 <= *(int*)(iVar5 + 0xbd4)))
							{
								iVar5 = STATLIST_UnitGetStatValue(pDVar2, (int)sVar1, 0);
								if ((0 < iVar5) && (iVar5 < 4))
								{
									sub_6FB57D20(pDVar2, *(short*)(iVar9 + 0xe) + -1 + iVar5, iVar7, iStack_4);
									iVar7 = iVar7 - byte_6FBBA798;
								}
							}
						}
						iVar8 = iVar8 + 1;
						iVar5 = *(int*)((uint8_t*)&sgptDataTables);
					} while (iVar8 < *(short*)(iVar5 + 0x170));
				}
			}
		}
	}
}

//D2Client.0x6FB21B70
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB21B70()
{
	char cVar1;
	uint8_t bVar2;
	uint8_t uVar3;
	bool bVar4;
	D2GameResolutionMode DVar5;
	int iVar6;
	D2UnitStrc* pDVar7;
	uint32_t uVar8;
	int iVar9;
	int iVar10;
	Unicode* pUVar11;
	D2ActiveRoomStrc* pRoom;
	D2LevelsTxt* pDVar12;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	uint32_t uVar13;
	int* piVar14;
	int iStack_13c;
	int iStack_138;
	int local_134;
	Unicode aUStack_130[16];
	CHAR aCStack_110[12];
	char acStack_104[260];

	if (dword_6FBBA6F0 != 0)
	{
		return;
	}
	DVar5 = D2GFX_GetResolutionMode();
	if (DVar5 == NUM_GAME_RESOLUTIONS)
	{
		dword_6FBBA748 = 0x50;
		dword_6FBBA74C = -0x3c;
	}
	else
	{
		dword_6FBBA748 = 0;
		dword_6FBBA74C = 0;
	}
	D2Win_10129_DrawFramedText(nullptr, 0, 0, 0, 0);
	word_6FBB9FE0 = 0;
	byte_6FBBA4A0 = 0;
	if (dword_6FBBA6CC != 0)
	{
		sub_6FB088B0();
	}
	if (dword_6FBBA6D4 != 0)
	{
		sub_6FAFC620();
	}
	sub_6FAB5A20();
	sub_6FB20A30();
	if ((dword_6FBBA734 != 0) && (iVar6 = sub_6FAB5750(), iVar6 != 3))
	{
		iVar6 = 0;
		pDVar7 = CUNIT_GetPlayer();
		uVar8 = sub_6FAB1920((int)pDVar7, 7, iVar6);
		if ((uVar8 != 0xffffffff) &&
		    ((iVar6 = sub_6FAB18D0(uVar8), *(int*)(iVar6 + 8) == 1 &&
		                                       (pDVar7 = sub_6FB269F0(uVar8, 1), pDVar7 != nullptr))))
		{
			iVar6 = D2GFX_CheckPerspective();
			if (iVar6 == 0)
			{
				iVar6 = UNITS_GetClientCoordX(pDVar7);
				iVar9 = sub_6FAB5890();
				dword_6FB8EA28 = iVar6 - iVar9;
				iVar6 = UNITS_GetClientCoordY(pDVar7);
				iVar9 = sub_6FAB58A0();
				dword_6FB8EA2C = iVar6 - iVar9;
			}
			else
			{
				iVar6 = UNITS_GetPrecisionX(pDVar7);
				iVar9 = UNITS_GetPrecisionY(pDVar7);
				iVar10 = SCALE_CheckPerspectivePosition(iVar6, iVar9);
				if (iVar10 == 0)
					goto LAB_6fb21d35;
				SCALE_AdjustPerspectivePosition(iVar6, iVar9, 0, &iStack_13c, &iStack_138);
				iVar6 = sub_6FAB5750();
				if (iVar6 == 1)
				{
					iVar6 = -((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
				LAB_6fb21cbd:
					iStack_13c = iStack_13c + iVar6;
				}
				else if (iVar6 == 2)
				{
					iVar6 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
					goto LAB_6fb21cbd;
				}
				dword_6FB8EA2C = iStack_138 + 0x10;
				dword_6FB8EA28 = iStack_13c;
			}
			iVar6 = sub_6FAFBB50((uint32_t*)(&iStack_138));
			if (iVar6 == 0)
			{
				iVar6 = sub_6FB20670(pDVar7);
				iVar9 = dword_6FB8EA2C + -0x48;
				pUVar11 = sub_6FB297F0(pDVar7);
				sub_6FB20590((int)pUVar11, dword_6FB8EA28, iVar9, iVar6);
			}
		}
	}
LAB_6fb21d35:
	if (((dword_6FBBA6AC == 0) && (dword_6FBBA6D8 == 0)) && (dword_6FBBA6E0 == 0))
	{
		sub_6FAFEE70();
		sub_6FAFEA40();
	}
	if ((dword_6FBBA6D0 != 0) && (iVar6 = sub_6FAB5750(), iVar6 != 3))
	{
		sub_6FACDCB0();
	}
	pRoom = CUNIT_GetPlayerRoom();
	if (pRoom != nullptr)
	{
		iVar6 = DUNGEON_GetLevelIdFromRoom(pRoom);
		if (iVar6 != dword_6FBBA784)
		{
			sub_6FADA970(1);
			if (gpCellFile_6FBBA1E8 != nullptr)
			{
				CLIENT_FreeCellFile(gpCellFile_6FBBA1E8);
				gpCellFile_6FBBA1E8 = nullptr;
			}
			dword_6FBBA788 = (-(uint32_t)(dword_6FBBA784 != 0) & 0xffffff88) + 0x78;
			dword_6FBBA784 = iVar6;
		}
		if (dword_6FBBA788 < 0x78)
		{
			dword_6FBBA788 = dword_6FBBA788 + 1;
			pDVar12 = DATATBLS_GetLevelsTxtRecord(iVar6);
			if (iVar6 < 0x6d)
			{
				bVar2 = DRLG_GetActNoFromLevelId(iVar6);
				sprintf((char*)aUStack_130, "ACT%d", bVar2 + 1);
			}
			else
			{
				iVar9 = 0;
				do
				{
					cVar1 = "EXPANSION"[iVar9];
					*(char*)((int)&aUStack_130[0].ch + iVar9) = cVar1;
					iVar9 = iVar9 + 1;
				} while (cVar1 != '\0');
			}
			D2LANG_10006((char*)((int)&iStack_13c), 0);
			sprintf(acStack_104, "%s\\UI\\%s\\%s\\%s", "DATA\\LOCAL", &iStack_13c, aUStack_130,
			    pDVar12->szEntryFile);
			iVar9 = 0;
			if (0 < dword_6FB8EC70)
			{
				piVar14 = (int*)(&dword_6FB8EC58);
				do
				{
					if ((iVar6 == piVar14[-1]) &&
					    (uVar3 = D2Client_10002(0, *piVar14), D2C_ZEXT(uVar3) != 0))
					{
						sprintf(acStack_104, "%s\\UI\\%s\\ACT1\\%s", "DATA\\LOCAL", &iStack_13c,
						    "A1Q1" + iVar9 * 0xd);
						break;
					}
					iVar9 = iVar9 + 1;
					piVar14 = (int*)((int)piVar14 + 0xd);
				} while (iVar9 < dword_6FB8EC70);
			}
			if (gpCellFile_6FBBA1E8 == nullptr)
			{
				gpCellFile_6FBBA1E8 = CLIENT_LoadCellFile(acStack_104, 0);
			}
			D2Win_10134_DrawCellFile(gpCellFile_6FBBA1E8, gnScreenWidth / 2, gnScreenHeight / 2 + -0x8c, 1, DRAWMODE_NORMAL, 1);
			goto LAB_6fb21f08;
		}
	}
	if (gpCellFile_6FBBA1E8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA1E8);
		gpCellFile_6FBBA1E8 = nullptr;
	}
LAB_6fb21f08:
	sub_6FADB890();
	if (dword_6FBBA6F4 != 0)
	{
		sub_6FADAB00();
	}
	if (dword_6FBBA738 != 0)
	{
		sub_6FAED5D0();
	}
	if (dword_6FBBA73C != 0)
	{
		sub_6FAEE9C0();
	}
	if (dword_6FBBA6E4 != 0)
	{
		sub_6FB042D0();
	}
	if (((((dword_6FBBA6AC != 0) || (dword_6FBBA6D8 != 0)) || (dword_6FBBA6E0 != 0)) ||
	        ((dword_6FBBA70C != 0 || (dword_6FBBA710 != 0)))) ||
	    ((dword_6FBBA718 != 0 || (dword_6FBBA71C != 0))))
	{
		sub_6FADEAC0();
	}
	if (dword_6FBBA704 != 0)
	{
		sub_6FB1F390();
		sub_6FADEAC0();
	}
	sub_6FB21A00();
	if (dword_6FBBA6B8 != 0)
	{
		sub_6FB16C00();
	}
	if (dword_6FBBA6B0 != 0)
	{
		sub_6FACFD60();
	}
	if (dword_6FBBA700 != 0)
	{
		sub_6FB01F10();
	}
	if (dword_6FBB9FC4 != 0)
	{
		sub_6FAD6EB0(dword_6FBB9FC4);
	}
	if (dword_6FBBA6E8 != 0)
	{
		sub_6FB1E990();
	}
	if (dword_6FBBA6F8 != 0)
	{
		sub_6FB25C70();
	}
	if (dword_6FBBA72C != 0)
	{
		sub_6FAD81F0();
		sub_6FAD82E0();
	}
	sub_6FAFF480();
	if (dword_6FBBA6B4 != 0)
	{
		sub_6FB19660();
	}
	if (dword_6FBBA724 != 0)
	{
		sub_6FB01C20();
	}
	sub_6FAEEC00();
	if (dword_6FBBA730 != 0)
	{
		sub_6FADA350();
	}
	if (dword_6FBBA6C0 == 0)
	{
		sub_6FAEF2A0();
	}
	else
	{
		sub_6FAEF360();
	}
	if (dword_6FBBA6C4 == 0)
	{
		sub_6FAEF670();
	}
	else
	{
		sub_6FAEF730();
	}
	if (dword_6FBBA6EC != 0)
	{
		sub_6FB065F0();
	}
	sub_6FAFF0B0();
	if (dword_6FBBA6FC != 0)
	{
		sub_6FB08DE0();
	}
	if (dword_6FBBA6BC != 0)
	{
		sub_6FAD2100();
	}
	if (dword_6FBBA72C != 0)
	{
		uVar8 = 0;
		do
		{
			if ((((&dword_6FBBA6A8)[uVar8] == 1) && ((&dword_6FB700B0)[uVar8] == 1)) &&
			    ((sub_6FB23260(uVar8, 1, 0), uVar8 == 0x19 || (uVar8 == 1))))
			{
				sub_6FAE8F10();
			}
			uVar8 = uVar8 + 1;
		} while ((int)uVar8 < 0x26);
		sub_6FB23260(0x21, 2, 0);
		sub_6FAD8310();
	}
	if ((dword_6FBBA6DC != 0) && (iVar6 = sub_6FAB5750(), iVar6 != 3))
	{
		sub_6FB09F60();
		iVar6 = sub_6FAABFF0();
		if (iVar6 != 0)
		{
			sub_6FB29700((uint8_t*)(sub_6FB22560));
		}
	}
	if (dword_6FBBA6C8 != 0)
	{
		sub_6FAF6070();
	}
	if (dword_6FBBA6E0 != 0)
	{
		sub_6FB25320();
	}
	sub_6FAFE650();
	sub_6FB1BA00(local_134);
	D2Win_10124();
	pDVar7 = sub_6FAB5A20();
	if ((pDVar7 != nullptr) && (pDVar7->dwUnitType == 1))
	{
		iVar6 = D2Win_10125();
		iVar6 = iVar6 + 0x27;
		sub_6FB22280(&word_6FBB9FE0, (Font)(6), iVar6, dword_6FBBA1E0);
		if ((word_6FBB9FE0 != 0) || (word_6FBBA2A0 != 0))
		{
			iVar9 = D2Win_10125();
			iVar6 = iVar6 + iVar9;
		}
		sub_6FB22280(&byte_6FBBA4A0, (Font)(6), iVar6, dword_6FBBA6A0);
	}
	sub_6FB21970();
	iVar6 = Unicode::strlen((Unicode*)&word_6FBBA2A0);
	if (((iVar6 != 0) && (pDVar7 = sub_6FAB5A20(), pDVar7 != nullptr)) &&
	    (pDVar7->dwUnitType == 1))
	{
		uVar13 = 0;
		bVar4 = sub_6FB40D00((int*)pDVar7);
		if (D2C_ZEXT(bVar4) != 0)
		{
			uVar13 = 4;
		}
		bVar4 = sub_6FB40CC0((int*)pDVar7);
		if (D2C_ZEXT(bVar4) != 0)
		{
			uVar13 = 3;
		}
		iVar6 = D2Win_10125();
		sub_6FB22280(&word_6FBBA2A0, (Font)(6), iVar6 + 0x27, uVar13);
	}
	uVar8 = sub_6FAA6990();
	if (((uVar8 != 0) && (pDVar7 = CUNIT_GetPlayer(), pDVar7 != nullptr)) &&
	    (iVar6 = sub_6FAAFD60(pDVar7->dwUnitId), iVar6 != 0))
	{
		uVar13 = sub_6FAAFD30(iVar6);
		memset(aUStack_130, 0, 2 * (0xc));
		wsprintfA(aCStack_110, "%d", uVar13);
		Unicode::win2Unicode(aUStack_130, aCStack_110, 0xc);
		D2Win_10117_DrawText(aUStack_130, 600, 0x19, 4, 0);
	}
	sub_6FB22320();
	sub_6FABA4A0();
}

//D2Client.0x6FB22280
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB22280(void* a1, Font a2, int a3, int a4)
{
	bool bVar1;
	uint32_t extraout_var;
	Font nFontSize;
	Unicode* pThis;
	int iVar2;
	int aiStack_110[2];
	int iStack_108;
	Unicode local_100[128];

	bVar1 = sub_6FB24690(aiStack_110);
	if ((D2C_ZEXT(bVar1) != 0) && (a1 != nullptr))
	{
		nFontSize = D2Win_10127_SetFont(a2);
		Unicode::strcpy(local_100, (Unicode*)a1);
		iVar2 = D2Win_10121_GetTextWidth(local_100);
		D2Win_10117_DrawText(local_100, (iStack_108 + aiStack_110[0] >> 1) - (iVar2 >> 1), a3, a4, 1);
		D2Win_10127_SetFont(nFontSize);
	}
}

//D2Client.0x6FB22320
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB22320()
{
	uint8_t bVar1;
	char cVar2;
	D2UnitStrc* pUnit;
	int iVar3;
	uint32_t extraout_var;
	Unicode* pUVar4;
	uint32_t extraout_var_00;
	int iVar5;
	int iVar6;
	int nColor;
	int bCentered;
	uint32_t local_308;
	char acStack_304[260];
	Unicode aUStack_200[256];

	pUnit = CUNIT_GetPlayer();
	if (pUnit == nullptr)
	{
		return;
	}
	iVar3 = sub_6FB29550((int*)pUnit);
	if (iVar3 == 0)
	{
		byte_6FBBA780 = 0;
		return;
	}
	iVar3 = gnScreenHeight / 2;
	D2LANG_10006((char*)((int)local_308), 0);
	if (gpCellFile_6FBBA78C == nullptr)
	{
		sprintf(acStack_304, "%s\\UI\\%s\\youdiedhardcore", "DATA\\LOCAL", local_308);
		gpCellFile_6FBBA78C = CLIENT_LoadCellFile(acStack_304, 0);
		if (gpCellFile_6FBBA78C != nullptr)
			goto LAB_6fb2239f;
	}
	else
	{
	LAB_6fb2239f:
		D2Win_10134_DrawCellFile(gpCellFile_6FBBA78C, gnScreenWidth / 2, iVar3 + -0x5e, 1, DRAWMODE_NORMAL, 1);
	}
	iVar6 = iVar3 + -0x2e;
	byte_6FBBA780 = 1;
	if (gpCellFile_6FBBA790 == nullptr)
	{
		sprintf(acStack_304, "%s\\UI\\%s\\youdiedinst", "DATA\\LOCAL", local_308);
		gpCellFile_6FBBA790 = CLIENT_LoadCellFile(acStack_304, 0);
		if (gpCellFile_6FBBA790 != nullptr)
			goto LAB_6fb22401;
	}
	else
	{
	LAB_6fb22401:
		D2Win_10134_DrawCellFile(gpCellFile_6FBBA790, gnScreenWidth / 2, iVar6, 1, DRAWMODE_NORMAL, 1);
	}
	bVar1 = CLIENT_IsHardcore();
	if (D2C_ZEXT(bVar1) == 0)
	{
		iVar5 = STATLIST_UnitGetStatValue(pUnit, 0xaf, 0);
		if (iVar5 == 0)
			goto LAB_6fb224dc;
		iVar6 = STATLIST_UnitGetStatValue(pUnit, 0xaf, 0);
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13e6));
		Unicode::sprintf(0x100, aUStack_200, pUVar4, iVar6);
	}
	else
	{
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13e8));
		Unicode::strcpy(aUStack_200, pUVar4);
	}
	iVar6 = iVar3 + 2;
	D2Win_10127_SetFont(D2FONT_FONT30);
	iVar3 = D2Win_10121_GetTextWidth(aUStack_200);
	D2Win_10117_DrawText(aUStack_200, gnViewWidth / 2 - iVar3 / 2, iVar6, 1, 1);
LAB_6fb224dc:
	cVar2 = sub_6FAAC090();
	if ((cVar2 != '\0') && (bVar1 = CLIENT_IsHardcore(), D2C_ZEXT(bVar1) == 0))
	{
		D2Win_10127_SetFont(D2FONT_FONT30);
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13e7));
		iVar3 = D2Win_10121_GetTextWidth(pUVar4);
		bCentered = 1;
		iVar6 = iVar6 + 0x30;
		iVar5 = gnViewWidth / 2;
		nColor = 1;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13e7));
		D2Win_10117_DrawText(pUVar4, iVar5 - iVar3 / 2, iVar6, nColor, bCentered);
		return;
	}
}

//D2Client.0x6FB22560
// TODO: decompilation needs review (in_reg)
void __cdecl sub_6FB22560()
{
	int iVar1;
	D2UnitStrc* pDVar2;
	D2UnitStrc* in_ECX;
	Unicode* pThis;
	D2CoordStrc DStack_138;
	int iStack_130;
	int iStack_12c;
	int iStack_128;
	int iStack_124;
	int iStack_120;
	int iStack_11c;
	int iStack_118;
	Unicode aUStack_114[2];
	tagRECT tStack_110;
	Unicode aUStack_100[128];

	iVar1 = sub_6FAB5750();
	if ((iVar1 != 3) && (pDVar2 = CUNIT_GetPlayer(), in_ECX != pDVar2))
	{
		sub_6FAB7180(dword_6FBA7990, (uint32_t*)(&iStack_128), (uint32_t*)(&iStack_124), (uint32_t*)(&iStack_120), (uint32_t*)(&iStack_11c));
		sub_6FAB71E0(dword_6FBA7990, (uint32_t*)(&iStack_130), (uint32_t*)(&iStack_12c));
		SetRect(&tStack_110, iStack_130, iStack_12c, (iStack_120 - iStack_128) + iStack_130,
		    (iStack_12c - iStack_124) + iStack_11c);
		UNITS_GetClientCoords(in_ECX, &DStack_138);
		DStack_138.nX = DStack_138.nX - tStack_110.left;
		DStack_138.nY = DStack_138.nY + (-0x46 - tStack_110.top);
		if (iVar1 == 1)
		{
			DStack_138.nX = DStack_138.nX - ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2);
			if (gnScreenWidth / 2 < DStack_138.nX)
			{
				return;
			}
		}
		else if ((iVar1 == 2) &&
		         (DStack_138.nX =
		                 DStack_138.nX + ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2),
		             DStack_138.nX < gnScreenWidth / 2))
		{
			return;
		}
		if ((((0 < DStack_138.nY) && (DStack_138.nY < gnScreenWidth)) && (-0x32 < DStack_138.nX)) &&
		    (DStack_138.nX < gnScreenHeight + 0x32))
		{
			sub_6FB21680(in_ECX, &iStack_118, aUStack_114, (Unicode*)aUStack_100, 0x80);
		}
	}
}

//D2Client.0x6FB226C0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB226C0(uint32_t a1)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	HWND__* pHVar2;
	uint32_t uVar3;

	switch (a1)
	{
	case 0:
		uVar3 = 4;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC18), uVar3);
		return;
	case 1:
		sub_6FAE90F0();
		uVar3 = 4;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC48), uVar3);
		return;
	case 2:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCC0), uVar3);
		return;
	case 3:
		uVar3 = 1;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCB4), uVar3);
		return;
	case 4:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC9C), uVar3);
		return;
	case 5:
		sub_6FAD1DA0();
		sub_6FAD5BE0(0, 1);
		if (dword_6FBBA6D0 != 0)
		{
			uVar3 = 5;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar3);
		}
		MEMORY_Nop();
		return;
	case 6:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCD8), uVar3);
		return;
	case 7:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCFC), uVar3);
		return;
	case 9:
		uVar3 = 7;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FD18), uVar3);
		sub_6FAB5A90(nullptr);
		return;
	case 10:
		uVar3 = 5;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar3);
		byte_6FBBA754 = 1;
		return;
	case 0xb:
		sub_6FAFC5B0(1);
		uVar3 = 0xd;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FD70), uVar3);
		bVar1 = sub_6FAAB290();
		if ((D2C_ZEXT(bVar1) != 0) ||
		    (bVar1 = sub_6FAAB250(), D2C_ZEXT(bVar1) != 0))
		{
			uVar3 = 1;
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE0C), uVar3);
			return;
		}
		break;
	case 0xc:
		sub_6FAD5BE0(2, 1);
		sub_6FAE9130();
		sub_6FB22AA0((int*)&byte_6FB6FC78);
		uVar3 = 8;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EA30), uVar3);
		return;
	case 0xf:
		sub_6FB22AA0((int*)&byte_6FB6FE84);
		uVar3 = 7;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EA90), uVar3);
		return;
	case 0x10:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEA8), uVar3);
		return;
	case 0x11:
		uVar3 = 4;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE54), uVar3);
		return;
	case 0x13:
		uVar3 = 1;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCF0), uVar3);
		return;
	case 0x14:
		uVar3 = 5;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEC0), uVar3);
		return;
	case 0x15:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEFC), uVar3);
		return;
	case 0x16:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FF14), uVar3);
		sub_6FB01CB0();
		return;
	case 0x17:
		sub_6FAD5BE0(0, 1);
		sub_6FB1F590();
		sub_6FAED210();
		sub_6FB22AA0((int*)&byte_6FB6FF2C);
		uVar3 = 0xd;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EAE8), uVar3);
		return;
	case 0x18:
		sub_6FB1EFB0();
		return;
	case 0x19:
		sub_6FAD5BE0(2, 1);
		sub_6FAEC5C0();
		sub_6FB22AA0((int*)&byte_6FB6FF50);
		uVar3 = 8;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EB88), uVar3);
		return;
	case 0x1a:
		sub_6FAD5BE0(2, 1);
		sub_6FAECFE0();
		sub_6FB22AA0((int*)&byte_6FB6FF74);
		uVar3 = 7;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EBE8), uVar3);
		return;
	case 0x1f:
		sub_6FB22AA0((int*)&byte_6FB6FF98);
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EC3C), uVar3);
		return;
	case 0x21:
		uVar3 = 5;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FFBC), uVar3);
		return;
	case 0x22:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FFF8), uVar3);
		return;
	case 0x23:
		uVar3 = 3;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70010), uVar3);
		return;
	case 0x24:
		uVar3 = 3;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70034), uVar3);
		return;
	case 0x25:
		uVar3 = 2;
		pHVar2 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70058), uVar3);
	}
}

//D2Client.0x6FB22AA0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB22AA0(int* a1)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t uVar2;
	uint32_t extraout_var_00;
	uint32_t extraout_var_01;
	int iVar3;
	uint32_t extraout_var_02;
	uint32_t extraout_var_03;
	uint32_t extraout_var_04;
	uint32_t extraout_var_05;

	iVar3 = a1[1];
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x16, 1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x16, 1);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22af9;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0xc0;
	}
LAB_6fb22af9:
	iVar3 = *a1;
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x26, 1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x26, 1);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22b4d;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0x1b;
	}
LAB_6fb22b4d:
	iVar3 = a1[4];
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x29, 1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x29, 1);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22ba2;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0x4e;
	}
LAB_6fb22ba2:
	iVar3 = FOG_IsExpansion();
	if ((iVar3 != 0) && (iVar3 = a1[6], iVar3 != -1))
	{
		bVar1 = sub_6FAD4F00(0x2c, 1);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x2c, 1);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22c00;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0x57;
	}
LAB_6fb22c00:
	iVar3 = a1[3];
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x16, 0);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x16, 0);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22c4f;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0xc0;
	}
LAB_6fb22c4f:
	iVar3 = a1[2];
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x26, 0);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x26, 0);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22c9e;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0x1b;
	}
LAB_6fb22c9e:
	iVar3 = a1[5];
	if (iVar3 != -1)
	{
		bVar1 = sub_6FAD4F00(0x29, 0);
		if (D2C_ZEXT(bVar1) != 0)
		{
			uVar2 = sub_6FAD4B60(0x29, 0);
			if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			{
				*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = uVar2 & 0xffff;
				goto LAB_6fb22ced;
			}
		}
		*(uint32_t*)(a1[8] + 4 + iVar3 * 0xc) = 0x4e;
	}
LAB_6fb22ced:
	iVar3 = FOG_IsExpansion();
	if ((iVar3 != 0) && (a1[7] != -1))
	{
		sub_6FB22D10(a1[7], 0x2c, 0, (int)a1, 0x57);
	}
}

//D2Client.0x6FB22D10
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB22D10(int a1, int a2, int a3, int a4, uint32_t a5)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t uVar2;

	if (a1 == -1)
	{
		return;
	}
	bVar1 = sub_6FAD4F00(a2, a3);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar2 = sub_6FAD4B60(a2, a3);
		if (((uint16_t)uVar2 != 0xffff) && ((uint16_t)uVar2 < 0xe0))
			goto LAB_6fb22d46;
	}
	uVar2 = a5;
LAB_6fb22d46:
	*(uint32_t*)(*(int*)(a4 + 0x20) + 4 + a1 * 0xc) = uVar2 & 0xffff;
}

//D2Client.0x6FB22D60
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB22D60(uint32_t a1)
{
	bool bVar1;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int iVar2;
	DWORD DVar3;
	HWND__* pHVar4;
	uint32_t uVar5;

	switch (a1)
	{
	case 0:
		uVar5 = 4;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC18), uVar5);
		return;
	case 1:
		sub_6FB23A60();
		uVar5 = 4;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC48), uVar5);
		break;
	case 2:
		sub_6FB23A60();
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCC0), uVar5);
		break;
	case 3:
		uVar5 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCB4), uVar5);
		return;
	case 4:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FC9C), uVar5);
		if (dword_6FB903AC != 0)
		{
			DVar3 = GetTickCount();
			dword_6FBBA740 = DVar3 + 100;
		}
		sub_6FB18580();
		return;
	case 5:
		sub_6FAD2030();
		MEMORY_Nop();
		if ((((((dword_6FBBA6D8 == 0) && (dword_6FBBA704 == 0)) && (dword_6FBBA70C == 0)) &&
		         ((dword_6FBBA710 == 0 && (dword_6FBBA714 == 0)))) &&
		        ((dword_6FBBA718 == 0 && ((dword_6FBBA71C == 0 && (dword_6FBBA720 == 0)))))) &&
		    (dword_6FBBA728 == 0))
		{
			sub_6FAD5BE0(1, 1);
		}
		if (dword_6FBBA6D0 == 0)
		{
			return;
		}
		uVar5 = 5;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar5);
		return;
	case 6:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCD8), uVar5);
		return;
	case 7:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCFC), uVar5);
		return;
	case 8:
	case 0xe:
		if (dword_6FB903AC != 0)
		{
			DVar3 = GetTickCount();
			dword_6FBBA740 = DVar3 + 100;
		}
		sub_6FAF9FE0();
		return;
	case 9:
		uVar5 = 7;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FD18), uVar5);
		sub_6FAB5D40();
		return;
	case 10:
		uVar5 = 5;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar5);
		byte_6FBBA754 = 0;
		return;
	case 0xb:
		bVar1 = sub_6FAAB290();
		if ((D2C_ZEXT(bVar1) != 0) ||
		    (bVar1 = sub_6FAAB250(), D2C_ZEXT(bVar1) != 0))
		{
			uVar5 = 1;
			pHVar4 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE0C), uVar5);
		}
		uVar5 = 0xd;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FD70), uVar5);
		sub_6FAFC5B0(0);
		return;
	case 0xc:
		uVar5 = 8;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EA30), uVar5);
		sub_6FAF9FE0();
		sub_6FAD5BE0(1, 1);
		return;
	default:
		goto switchD_6fb22d69_caseD_d;
	case 0xf:
		uVar5 = 7;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EA90), uVar5);
		sub_6FB062B0();
		break;
	case 0x10:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEA8), uVar5);
		MEMORY_Nop();
		break;
	case 0x11:
		uVar5 = 4;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE54), uVar5);
		sub_6FB06D20();
		return;
	case 0x12:
		break;
	case 0x13:
		uVar5 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FCF0), uVar5);
		return;
	case 0x14:
		uVar5 = 5;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEC0), uVar5);
		sub_6FB262E0();
		break;
	case 0x15:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FEFC), uVar5);
		return;
	case 0x16:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FF14), uVar5);
		sub_6FB01C70();
		break;
	case 0x17:
		iVar2 = sub_6FB1FFF0();
		if (iVar2 != 0)
		{
			return;
		}
		sub_6FAB5760(0);
		sub_6FB23A60();
		uVar5 = 0xd;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EAE8), uVar5);
		if (dword_6FB903AC != 0)
		{
			DVar3 = GetTickCount();
			dword_6FBBA740 = DVar3 + 100;
		}
		sub_6FB1F5B0(0);
		sub_6FAD5BE0(1, 1);
		return;
	case 0x18:
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
		return;
	case 0x19:
		sub_6FB23A60();
		sub_6FAB5760(0);
		sub_6FAEC650();
		uVar5 = 8;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EB88), uVar5);
		if (dword_6FB903AC != 0)
		{
			DVar3 = GetTickCount();
			dword_6FBBA740 = DVar3 + 100;
			sub_6FAD5BE0(1, 1);
			return;
		}
		goto LAB_6fb230fb;
	case 0x1a:
		sub_6FAB5760(0);
		sub_6FAED030();
		uVar5 = 7;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EBE8), uVar5);
		if (dword_6FB903AC != 0)
		{
			DVar3 = GetTickCount();
			dword_6FBBA740 = DVar3 + 100;
		}
	LAB_6fb230fb:
		sub_6FAD5BE0(1, 1);
		return;
	case 0x1f:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB8EC3C), uVar5);
		return;
	case 0x21:
		sub_6FADA320();
		uVar5 = 5;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FFBC), uVar5);
		return;
	case 0x22:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FFF8), uVar5);
		return;
	case 0x23:
		uVar5 = 3;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70010), uVar5);
		return;
	case 0x24:
		uVar5 = 3;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70034), uVar5);
		sub_6FAE8F10();
		return;
	case 0x25:
		uVar5 = 2;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB70058), uVar5);
		goto switchD_6fb22d69_caseD_d;
	}
	if (dword_6FB903AC != 0)
	{
		DVar3 = GetTickCount();
		dword_6FBBA740 = DVar3 + 100;
		return;
	}
switchD_6fb22d69_caseD_d:
}

//D2Client.0x6FB23230
uint32_t __fastcall sub_6FB23230(uint32_t a1)
{
	D2_ASSERT(0x25 >= a1);
	return (&dword_6FBBA6A8)[a1];
}

//D2Client.0x6FB23260
// TODO: decompilation needs review (extraout)
int32_t __fastcall sub_6FB23260(int32_t a1, int32_t a2, int32_t a3)
{
	uint8_t bVar1;
	bool bVar2;
	int iVar3;
	DWORD DVar4;
	D2UnitStrc* pDVar5;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	int iVar6;
	int iVar7;
	uint32_t extraout_ECX;
	uint32_t uVar8;
	uint32_t uStack_8;
	int local_4;

	D2_ASSERT(0x25 >= a1);
	D2_ASSERT(2 >= a2);
	local_4 = (&dword_6FBBA6A8)[a1];
	iVar3 = FOG_IsExpansion();
	if ((iVar3 == 0) || (iVar3 = sub_6FAAC080(), iVar3 == 0))
	{
		if (a1 == 0x23)
		{
			return 0;
		}
		if (a1 == 0x24)
		{
			return 0;
		}
		if (a1 == 0x25)
		{
			return 0;
		}
	}
	D2_ASSERT(dword_6FB903A8 == 0x26);
	if ((a2 == 0) || ((a2 == 2 && ((&dword_6FBBA6A8)[a1] == 0))))
	{
		if ((a1 == 5) || (a1 == 9))
		{
			iVar3 = sub_6FAD7530();
			if (((iVar3 != 0) && (a1 == 5)) && (dword_6FBBA708 == 0))
			{
				return 0;
			}
			DVar4 = GetTickCount();
			if (DVar4 < (uint32_t)dword_6FBBA740)
			{
				return 0;
			}
			if (a1 == 9)
			{
				pDVar5 = CUNIT_GetPlayer();
				if (pDVar5 == nullptr)
				{
					return 0;
				}
				if ((pDVar5->dwUnitType == 0) && (pDVar5->dwAnimMode == 0x11))
				{
					sub_6FB294B0((int*)pDVar5);
					CLIENT_SendSimpleMessage(0x41);
					bVar1 = CLIENT_IsHardcore();
					if (D2C_ZEXT(bVar1) == 0)
					{
						return 0;
					}
					sub_6FAAD420((int32_t)extraout_ECX);
					dword_6FBA796C = 0;
					dword_6FBA7968 = 0;
					CLIENT_SetCharacterDied();
					CLIENT_SetExitToMenu(0);
					sub_6FAAB240();
					return 0;
				}
			}
		}
		bVar2 = sub_6FB1EE90();
		if (((D2C_ZEXT(bVar2) != 0) && (a1 != 10)) &&
		    ((a1 != 0x13 && (((a1 != 0x11 && (a1 != 6)) && (a1 != 7))))))
		{
		switchD_6fb23409_caseD_2:
			return 0;
		}
		uVar8 = 0;
		if (0 < dword_6FB903A8)
		{
			do
			{
				if ((&dword_6FBBA6A8)[uVar8] == 1)
				{
					switch (*(uint32_t*)((&ptr_6FB90310)[uVar8] + a1 * 4))
					{
					case 0:
						break;
					case 1:
						sub_6FB23260(uVar8, 1, 0);
						break;
					case 2:
						goto switchD_6fb23409_caseD_2;
					default:
						if (a1 != 0)
						{
							FOG_Trace(" requested %d but %d says it's an error in ui.cpp\n", a1, uVar8);
							return 0;
						}
						FOG_DisplayAssert("nUIId != UI_STATE_SHARE",
						    __FILE__, __LINE__);
						exit(-1);
					case 4:
						iVar3 = sub_6FAFBB50(&uStack_8);
						if (iVar3 != 0)
						{
							sub_6FAFBB60(uStack_8);
						}
					}
				}
				uVar8 = uVar8 + 1;
			} while ((int)uVar8 < dword_6FB903A8);
		}
	}
	pDVar5 = CUNIT_GetPlayer();
	if (a2 == 0)
	{
		if ((pDVar5 == nullptr) ||
		    ((pDVar5->dwUnitType == 0 && (iVar3 = sub_6FB29550((int*)pDVar5), iVar3 == 0))))
		{
			(&dword_6FBBA6A8)[a1] = 1;
		}
	}
	else if (a2 == 1)
	{
		(&dword_6FBBA6A8)[a1] = 0;
	}
	else if (a2 == 2)
	{
		if (pDVar5 == nullptr)
		{
			(&dword_6FBBA6A8)[a1] = (uint32_t)((&dword_6FBBA6A8)[a1] == 0);
		}
		else if ((pDVar5->dwUnitType == 0) && (iVar3 = sub_6FB29550((int*)pDVar5), iVar3 == 0))
		{
			(&dword_6FBBA6A8)[a1] = (uint32_t)((&dword_6FBBA6A8)[a1] == 0);
		}
		else if (a1 == 5)
		{
			dword_6FBBA6BC = (uint32_t)(dword_6FBBA6BC == 0);
		}
	}
	iVar3 = (&dword_6FBBA6A8)[a1];
	if (local_4 == 0)
	{
		if ((iVar3 != 0) && (sub_6FB226C0(a1), a1 == 5))
		{
			sub_6FAD2F90();
		}
	}
	else if (iVar3 == 0)
	{
		sub_6FB22D60(a1);
	}
	iVar6 = sub_6FB57BC0();
	iVar7 = sub_6FB57BD0();
	switch (a1)
	{
	case 1:
		sub_6FAE8F10();
	case 4:
		if (((((dword_6FBBA6B0 != 0) || (dword_6FBBA6F8 != 0)) || (dword_6FBBA6E4 != 0)) ||
		        ((dword_6FBBA6E8 != 0 || (dword_6FBBA738 != 0)))) ||
		    ((dword_6FBBA73C != 0 || (dword_6FBBA700 != 0))))
		{
			if (iVar3 == 0)
			{
				sub_6FAB5760(2);
				return 1;
			}
			sub_6FAB5760(3);
			return 1;
		}
		if (iVar3 == 0)
		{
			sub_6FAB5760(0);
			if ((a3 != 0) && (iVar6 < gnScreenWidth / 2))
			{
				sub_6FB57BE0(((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2) + iVar6, iVar7);
				return 1;
			}
		}
		else
		{
			sub_6FAB5760(1);
			if ((a3 != 0) &&
			    (iVar3 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2, iVar3 < iVar6))
			{
				sub_6FB57BE0(iVar6 - iVar3, iVar7);
				return 1;
			}
		}
		break;
	case 2:
	case 0xf:
	case 0x10:
	case 0x14:
	case 0x16:
	case 0x24:
	case 0x25:
		if ((dword_6FBBA6AC == 0) && (dword_6FBBA6B8 == 0))
		{
			if (iVar3 == 0)
			{
				sub_6FAB5760(0);
				if (a3 == 0)
				{
					return 1;
				}
				if (iVar6 <= gnScreenWidth / 2)
				{
					return 1;
				}
				sub_6FB57BE0(iVar6 - ((int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2), iVar7);
				return 1;
			}
			sub_6FAB5760(2);
			if (a3 == 0)
			{
				return 1;
			}
			iVar3 = (int)(gnScreenWidth + (gnScreenWidth >> 0x1f & 3U)) >> 2;
			if (gnScreenWidth - iVar3 <= iVar6)
			{
				return 1;
			}
			sub_6FB57BE0(iVar3 + iVar6, iVar7);
			return 1;
		}
		uVar8 = 3;
		if (iVar3 == 0)
			goto LAB_6fb23790;
		goto LAB_6fb23795;
	default:
		break;
	case 0xc:
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x1d:
	case 0x20:
		if (iVar3 != 0)
		{
			sub_6FAB5760(3);
			return 1;
		}
	LAB_6fb2357e:
		sub_6FAB5760(0);
		return 1;
	case 0xe:
		if (iVar3 == 0)
			goto LAB_6fb2357e;
	LAB_6fb23790:
		uVar8 = 1;
	LAB_6fb23795:
		sub_6FAB5760(uVar8);
	}
	return 1;
}

//D2Client.0x6FB23800
uint32_t __fastcall sub_6FB23800(int a1, int a2)
{
	uint32_t uVar1;
	uint32_t uVar2;

	uVar2 = 0;
	uVar1 = 0;
	do
	{
		if (((&dword_6FBBA6A8)[uVar1] == 1) &&
		    (((&dword_6FB700B0)[uVar1] == 1 || ((a1 != 0 && (uVar1 == 10))))))
		{
			sub_6FB23260(uVar1, 1, a2);
			uVar2 = 1;
			if ((uVar1 == 0x19) || (uVar1 == 1))
			{
				sub_6FAE8F10();
			}
		}
		uVar1 = uVar1 + 1;
	} while ((int)uVar1 < 0x26);
	return uVar2;
}

//D2Client.0x6FB23860
uint32_t __fastcall sub_6FB23860(int a1)
{
	return (&dword_6FBBA6A8)[a1];
}

//D2Client.0x6FB23870
D2CellFileStrc* __cdecl sub_6FB23870()
{
	return gpCellFile_6FBBA768;
}

//D2Client.0x6FB23880
D2CellFileStrc* __cdecl sub_6FB23880()
{
	return gpCellFile_6FBBA770;
}

//D2Client.0x6FB23890
void __cdecl sub_6FB23890()
{
	dword_6FB903AC = 0;
	dword_6FBBA740 = 0;
}

//D2Client.0x6FB238A0
void __cdecl sub_6FB238A0()
{
	dword_6FB903AC = 1;
}

//D2Client.0x6FB238B0
void __cdecl sub_6FB238B0()
{
	DWORD DVar1;

	if (dword_6FB903AC != 0)
	{
		DVar1 = GetTickCount();
		dword_6FBBA740 = DVar1 + 100;
	}
}

//D2Client.0x6FB238D0
void __cdecl sub_6FB238D0()
{
	int iVar1;
	uint32_t uVar2;
	HWND__* hWnd;
	UINT Msg;
	WPARAM wParam;

	iVar1 = sub_6FB57BD0();
	uVar2 = sub_6FB57BC0();
	uVar2 = iVar1 << 0x10 | uVar2 & 0xffff;
	wParam = 0;
	Msg = 0x200;
	hWnd = WINDOW_GetWindow();
	SendMessageA((HWND)hWnd, Msg, wParam, uVar2);
}

//D2Client.0x6FB23910
void __cdecl sub_6FB23910()
{
	sub_6FB03FA0();
	sub_6FAD16E0();
	sub_6FB16310();
	sub_6FB185C0();
	sub_6FB1F370();
	sub_6FAE8F10();
	sub_6FB01C10();
	sub_6FAED190();
	sub_6FB06D60();
	sub_6FADBF00();
	sub_6FACB6E0(1);
	sub_6FB08D90();
}

//D2Client.0x6FB23960
void __cdecl sub_6FB23960()
{
	sub_6FB03FF0();
	MEMORY_Nop();
	sub_6FB16370();
	sub_6FB18680();
	sub_6FB06D40();
	sub_6FAFBD40();
	sub_6FB1F380();
	sub_6FB1EEA0();
	sub_6FADA9D0();
	if (gpCellFile_6FBBA1E8 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA1E8);
		gpCellFile_6FBBA1E8 = nullptr;
	}
	if (gpCellFile_6FBBA78C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA78C);
		gpCellFile_6FBBA78C = nullptr;
	}
	if (gpCellFile_6FBBA790 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA790);
		gpCellFile_6FBBA790 = nullptr;
	}
	sub_6FB08DC0();
	sub_6FB575B0(nullptr);
}

//D2Client.0x6FB239F0
// TODO: decompilation needs review (extraout)
Unicode* __fastcall sub_6FB239F0(int a1)
{
	uint8_t uVar1;
	D2LevelsTxt* pDVar2;
	uint32_t extraout_var;
	Unicode* pUVar3;

	pDVar2 = DATATBLS_GetLevelsTxtRecord(a1);
	if (pDVar2 == nullptr)
	{
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x150d));
		return pUVar3;
	}
	if (a1 == 8)
	{
		uVar1 = D2Client_10002(0, 1);
		if (D2C_ZEXT(uVar1) != 0)
		{
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13b8));
			return pUVar3;
		}
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0x13b7));
		return pUVar3;
	}
	return pDVar2->wszLevelName;
}

//D2Client.0x6FB23A40
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB23A40()
{
	D2UnitStrc* pDVar1;
	uint32_t extraout_ECX;

	pDVar1 = sub_6FB575E0();
	if (pDVar1 != nullptr)
	{
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x27), pDVar1->dwUnitId, pDVar1->dwUnitId);
	}
}

//D2Client.0x6FB23A60
void __cdecl sub_6FB23A60()
{
	if (dword_6FBB9FD8 != 0)
	{
		sub_6FAD5BE0(1, 1);
		dword_6FBB9FD8 = 0;
	}
	if (gpint32_t_6FBB9FCC != nullptr)
	{
		dword_6FBBA968 = (**(code**)(*gpint32_t_6FBB9FCC + 0x2c))();
	}
	if (dword_6FBB9FC4 != 0)
	{
		sub_6FAD6DC0();
		dword_6FBB9FC4 = 0;
	}
	if (gpuint32_t_6FBB9FC8 != nullptr)
	{
		(**(code**)*gpuint32_t_6FBB9FC8)(1);
		gpuint32_t_6FBB9FC8 = nullptr;
	}
	if (gpint32_t_6FBB9FCC != nullptr)
	{
		(**(code**)*gpint32_t_6FBB9FCC)(1);
		gpint32_t_6FBB9FCC = nullptr;
	}
	if (gpint32_t_6FBB9FD0 != nullptr)
	{
		(**(code**)*gpint32_t_6FBB9FD0)(1);
		gpint32_t_6FBB9FD0 = nullptr;
	}
	if (gpuint32_t_6FBB9FD4 != nullptr)
	{
		(**(code**)*gpuint32_t_6FBB9FD4)(1);
		gpuint32_t_6FBB9FD4 = nullptr;
	}
	if (dword_6FBBA744 != 0)
	{
		if ((0 < dword_6FBBA744) && (dword_6FBBA744 < 5))
		{
			sub_6FAEB950();
			return;
		}
		FOG_Trace("not implemented dummy %s %d ", __FILE__, __LINE__);
		return;
	}
	sub_6FAD16C0();
}

//D2Client.0x6FB23B40
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB23B40(int a1)
{
	D2SplittedTextStrc* pDVar1;
	D2UnitStrc* pDVar2;
	Unicode* pUVar3;
	D2SplittedTextStrc* pFree;
	uint32_t* puVar4;
	void* pvVar5;
	uint32_t extraout_ECX;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	uint32_t extraout_EDX_01;
	int iVar6;
	short index;
	int iVar7;
	int iVar8;
	uint16_t uVar9;
	int iStack_210;
	Unicode aUStack_20c[256];
	void* local_c;
	code* pcStack_8;
	uint32_t uStack_4;

	uStack_4 = 0xffffffff;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 != nullptr)
	{
		pDVar2 = CUNIT_GetPlayer();
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		if (pDVar2 == nullptr)
		{
			if (dword_6FBB9FC4 != 0)
			{
				return;
			}
			if (dword_6FBB9FD8 == 0)
			{
				sub_6FAD5BE0(0, 1);
				dword_6FBB9FD8 = 1;
			}
			dword_6FBBA968 = 0;
			switch (a1)
			{
			case 0:
				sub_6FAD16D0();
				index = 0xfc1;
				iVar7 = 0xe;
				break;
			case 1:
				index = 0xfc1;
				sub_6FAEB970();
				iVar7 = 0xe;
				break;
			case 2:
				index = 0xfce;
				sub_6FAEB970();
				iVar7 = 0xe;
				break;
			case 3:
				index = 0xfd1;
				sub_6FAEB970();
				iVar7 = 0xe;
				break;
			case 4:
				index = 0xfd2;
				sub_6FAEB970();
				iVar7 = 0xf;
				break;
			default:
				goto switchD_6fb23bc6_default;
			}
			uVar9 = 0;
			pDVar2 = CUNIT_GetPlayer();
			iVar7 = STATLIST_UnitGetStatValue(pDVar2, iVar7, uVar9);
			dword_6FBBA744 = a1;
			dword_6FBB9FC4 = (int)sub_6FAD6950(0xd7, 0x8c, 0x6fb23f60, 0, 0, 1);
			sub_6FAD7150(dword_6FBB9FC4, 1);
			D2Win_10127_SetFont(D2FONT_FONT16);
			pUVar3 = aUStack_20c;
			for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*(uint32_t*)pUVar3 = 0;
				pUVar3 = pUVar3 + 2;
			}
			if (a1 == 5)
			{
				uVar9 = 0;
				iVar6 = 0xf;
				pDVar2 = CUNIT_GetPlayer();
				iVar6 = STATLIST_UnitGetStatValue(pDVar2, iVar6, uVar9);
				uVar9 = 0;
				iVar8 = 0xe;
				pDVar2 = CUNIT_GetPlayer();
				iVar8 = STATLIST_UnitGetStatValue(pDVar2, iVar8, uVar9);
				iVar6 = iVar6 + iVar8;
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
				Unicode::sprintf(0x100, aUStack_20c, pUVar3, iVar6);
			}
			else
			{
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
				Unicode::strcpy(aUStack_20c, pUVar3);
			}
			pFree = D2Win_10199(aUStack_20c, &iStack_210, 200);
			while (pFree != nullptr)
			{
				sub_6FAD7180(dword_6FBB9FC4, pFree->wszLine, 0x18, 0, 4, 1, 0, 0);
				pDVar1 = pFree->pNextLine;
				D2_FREE(pFree->wszLine);
				D2_FREE(pFree);
				pFree = pDVar1;
			}
			puVar4 = (uint32_t*)SMemAlloc(0xc, "new", -1, 0);
			uStack_4 = 0;
			if (puVar4 == nullptr)
			{
				gpuint32_t_6FBB9FC8 = nullptr;
			}
			else
			{
				gpuint32_t_6FBB9FC8 = sub_6FB1A700(puVar4, extraout_EDX, 0xdf, 0xdb, 0, (uint32_t)(sub_6FB23F70));
			}
			uStack_4 = 0xffffffff;
			sub_6FAD68F0(dword_6FBB9FC4, (uint32_t)(gpuint32_t_6FBB9FC8), 0, 0);
			pvVar5 = SMemAlloc(0xc, "new", -1, 0);
			uStack_4 = 1;
			if (pvVar5 == nullptr)
			{
				gpint32_t_6FBB9FCC = nullptr;
			}
			else
			{
				gpint32_t_6FBB9FCC = (int*)sub_6FAD8060(pvVar5, iVar7, 0x102, 0xe4, 100, 1, iVar7, 10, (uint32_t)(sub_6FB24F70), 1);
			}
			uStack_4 = 0xffffffff;
			sub_6FAD68F0(dword_6FBB9FC4, (uint32_t)(gpint32_t_6FBB9FCC), 0, 0);
			if (gpint32_t_6FBB9FCC != nullptr)
			{
				(**(code**)(*gpint32_t_6FBB9FCC + 0x44))(1);
			}
			puVar4 = (uint32_t*)SMemAlloc(0xc, "new", -1, 0);
			uStack_4 = 2;
			if (puVar4 == nullptr)
			{
				gpint32_t_6FBB9FD0 = nullptr;
			}
			else
			{
				gpint32_t_6FBB9FD0 = (int32_t*)(sub_6FACFC50(puVar4, extraout_EDX_00, 0xfa, 0x11f, 0, (uint32_t)(sub_6FB24010)));
			}
			uStack_4 = 0xffffffff;
			sub_6FAD68F0(dword_6FBB9FC4, (uint32_t)(gpint32_t_6FBB9FD0), 0, 0);
			(**(code**)(*gpint32_t_6FBB9FD0 + 0x30))(1);
			puVar4 = (uint32_t*)SMemAlloc(0xc, "new", -1, 0);
			uStack_4 = 3;
			if (puVar4 == nullptr)
			{
				gpuint32_t_6FBB9FD4 = nullptr;
			}
			else
			{
				gpuint32_t_6FBB9FD4 = sub_6FACFC50(puVar4, extraout_EDX_01, 0x163, 0x11f, 1, (uint32_t)(sub_6FB240C0));
			}
			uStack_4 = 0xffffffff;
			sub_6FAD68F0(dword_6FBB9FC4, (uint32_t)(gpuint32_t_6FBB9FD4), 0, 0);
			if (a1 == 2)
			{
				sub_6FB1FF00(extraout_ECX);
				return;
			}
			if (((a1 != 3) && (a1 != 7)) && (a1 != 6))
			{
				return;
			}
			if (gpint32_t_6FBB9FCC == nullptr)
			{
				return;
			}
			(**(code**)(*gpint32_t_6FBB9FCC + 0x38))(iVar7);
			return;
		}
	}
switchD_6fb23bc6_default:
	sub_6FB23A60();
}

//D2Client.0x6FB23F60
uint32_t __cdecl sub_6FB23F60()
{
	sub_6FB23A60();
	return 0;
}

//D2Client.0x6FB23F70
uint32_t __cdecl sub_6FB23F70()
{
	int iVar1;
	uint32_t uVar2;
	D2UnitStrc* pUnit;
	uint32_t uVar3;
	uint32_t uVar4;
	int nStatId;
	uint16_t nLayer;

	iVar1 = (**(code**)(*gpuint32_t_6FBB9FC8 + 0x2c))();
	uVar2 = (**(code**)(*gpuint32_t_6FBB9FC8 + 0x30))(0);
	if (gpint32_t_6FBB9FCC != nullptr)
	{
		dword_6FBBA968 = (**(code**)(*gpint32_t_6FBB9FCC + 0x2c))();
	}
	uVar4 = dword_6FBBA968;
	nLayer = 0;
	if (dword_6FBBA744 == 4)
	{
		nStatId = 0xf;
	}
	else
	{
		nStatId = 0xe;
	}
	pUnit = CUNIT_GetPlayer();
	uVar3 = STATLIST_UnitGetStatValue(pUnit, nStatId, nLayer);
	if (iVar1 == 1)
	{
		uVar4 = uVar4 + uVar2;
		if (uVar3 < uVar4)
		{
			uVar4 = uVar3;
		}
	}
	else if (iVar1 == 2)
	{
		if (uVar4 < uVar2)
		{
			uVar4 = 0;
		}
		else if (uVar4 != 0)
		{
			uVar4 = uVar4 - uVar2;
		}
	}
	dword_6FBBA968 = uVar4;
	if (gpint32_t_6FBB9FCC != nullptr)
	{
		(**(code**)(*gpint32_t_6FBB9FCC + 0x38))(uVar4);
	}
	return 0;
}

//D2Client.0x6FB24010
uint32_t __cdecl sub_6FB24010()
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint16_t uVar3;

	sub_6FB23A60();
	if (dword_6FBBA968 == 0)
	{
		if (dword_6FBBA744 != 2)
		{
			return 1;
		}
		sub_6FB1FF60(0);
		return 1;
	}
	switch (dword_6FBBA744)
	{
	case 0:
	case 1:
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar2 = 0xffffffff;
		}
		else
		{
			uVar2 = pDVar1->dwUnitId;
		}
		sub_6FAADA40(CONCAT31((int32_t)((uint32_t)dword_6FBBA968 >> 8), 0x50), uVar2, dword_6FBBA968);
		return 1;
	case 2:
		sub_6FB1FF60(dword_6FBBA968);
		goto LAB_6fb24092;
	case 3:
		uVar3 = 0x14;
		break;
	case 4:
		uVar3 = 0x13;
		break;
	default:
		goto switchD_6fb24039_default;
	}
	sub_6FAAD9E0(CONCAT31((int32_t)((uint32_t)dword_6FBBA968 >> 8), 0x4f), uVar3, (*(uint16_t*)((uint8_t*)&dword_6FBBA968 + 2)),
	    (short)dword_6FBBA968);
LAB_6fb24092:
	sub_6FB55820(0xdd, nullptr, 0.0, 0.0, 0);
switchD_6fb24039_default:
	return 1;
}

//D2Client.0x6FB240C0
uint32_t __cdecl sub_6FB240C0()
{
	sub_6FB23A60();
	return 1;
}

//D2Client.0x6FB240D0
void __fastcall sub_6FB240D0(int a1)
{
	HWND__* pHVar1;
	uint32_t uVar2;

	if (a1 == 0)
	{
		if (dword_6FBBA6D0 != 0)
		{
			uVar2 = 5;
			pHVar1 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar2);
		}
	}
	else if (dword_6FBBA6D0 != 0)
	{
		uVar2 = 5;
		pHVar1 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE18), uVar2);
		return;
	}
}

//D2Client.0x6FB24110
D2CellFileStrc* __cdecl sub_6FB24110()
{
	CHAR local_104[260];

	if (gpCellFile_6FBBA76C == nullptr)
	{
		wsprintfA(local_104, "%s\\ui\\panel\\buysellbtn", "DATA\\GLOBAL");
		gpCellFile_6FBBA76C = CLIENT_LoadCellFile(local_104, 0);
	}
	return gpCellFile_6FBBA76C;
}

//D2Client.0x6FB24150
void __cdecl sub_6FB24150()
{
	char local_208[260];
	char local_104[260];

	sprintf(local_104, "%s\\Palette\\Loading\\pal.dat", "DATA\\GLOBAL");
	sprintf(local_208, "%s\\Palette\\Loading\\pal.pl2", "DATA\\GLOBAL");
	D2Win_10028(local_104, local_208);
}

//D2Client.0x6FB241A0
void __cdecl sub_6FB241A0()
{
	D2C_Language DVar1;
	char* p2;
	char* pcVar2;
	char acStack_30c[260];
	char acStack_208[260];
	char local_104[260];

	if (sghLoadScreenProgress != nullptr)
	{
		CLIENT_FreeCellFile(sghLoadScreenProgress);
		sghLoadScreenProgress = nullptr;
		D2Win_10177(byte_6FBBA77C);
		D2CMP_10097(byte_6FBBA77C);
		sub_6FACF730();
		sub_6FADD2F0();
		sub_6FB01C30();
		sub_6FB01C50();
		sub_6FB16BE0();
		sub_6FAFE930();
		sub_6FAFE950();
		sub_6FAFE990();
		sub_6FAFE970();
		sub_6FAA7050(dword_6FBA798C);
		sub_6FAAC000(2000);
	}
	byte_6FBBA774 = 0;
	sghLoadScreenProgress = nullptr;
	dword_6FBBA758 = 0;
	sprintf(local_104, "%s\\Palette\\Loading\\pal.dat", "DATA\\GLOBAL");
	sprintf(acStack_208, "%s\\Palette\\Loading\\pal.pl2", "DATA\\GLOBAL");
	D2Win_10028(local_104, acStack_208);
	DVar1 = STRTABLE_GetLanguage();
	if (DVar1 == LANGUAGE_ENGLISH)
	{
		pcVar2 = "DATA\\GLOBAL";
		p2 = "%s\\UI\\Loading\\Loadingscreen";
	}
	else
	{
		pcVar2 = "DATA\\LOCAL";
		p2 = "%s\\UI\\LoadingScreen";
	}
	sprintf(acStack_30c, p2, pcVar2);
	sghLoadScreenProgress = CLIENT_LoadCellFile(acStack_30c, 0);
	dword_6FBBA96C = 0;
	dword_6FBBA758 = 1;
	sub_6FAAD530(0, 0);
	dword_6FBB9FC0 = dword_6FBA7974;
}

//D2Client.0x6FB242E0
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FB242E0(int a1)
{
	int iVar1;
	int iVar2;
	D2C_Language DVar3;
	uint32_t extraout_ECX;
	char* p2;
	char* pcVar4;
	D2GfxDataStrc DStack_354;
	char acStack_30c[260];
	char acStack_208[260];
	char acStack_104[260];

	iVar1 = WINDOW_GetState();
	if (iVar1 == 0)
	{
		D2GFX_ClearScreen(0);
	}
	iVar1 = sub_6FAABFF0();
	sub_6FAA9A10();
	iVar2 = WINDOW_GetState();
	if (iVar2 == 0)
	{
		D2Win_10179();
		iVar2 = D2GFX_StartDraw(1, 0, 0, 0);
		if (iVar2 != 0)
		{
			if (sghLoadScreenProgress == nullptr)
			{
				byte_6FBBA774 = 0;
				sghLoadScreenProgress = nullptr;
				dword_6FBBA758 = 0;
				sprintf(acStack_104, "%s\\Palette\\Loading\\pal.dat", "DATA\\GLOBAL");
				sprintf(acStack_208, "%s\\Palette\\Loading\\pal.pl2", "DATA\\GLOBAL");
				D2Win_10028(acStack_104, acStack_208);
				DVar3 = STRTABLE_GetLanguage();
				if (DVar3 == LANGUAGE_ENGLISH)
				{
					pcVar4 = "DATA\\GLOBAL";
					p2 = "%s\\UI\\Loading\\Loadingscreen";
				}
				else
				{
					pcVar4 = "DATA\\LOCAL";
					p2 = "%s\\UI\\LoadingScreen";
				}
				sprintf(acStack_30c, p2, pcVar4);
				sghLoadScreenProgress = CLIENT_LoadCellFile(acStack_30c, 0);
				dword_6FBBA96C = 0;
				dword_6FBBA758 = 1;
				sub_6FAAD530(0, 0);
				dword_6FBB9FC0 = dword_6FBA7974;
				D2_ASSERT(sghLoadScreenProgress != nullptr);
			}
			if ((((iVar1 == 6) || (iVar1 == 8)) || (iVar1 == 7)) || (iVar1 == 9))
			{
				if (byte_6FBBA970 == 0)
				{
					byte_6FBBA970 = D2Win_10034_MixRGB(0x60, 0, 0);
					byte_6FBBA971 = D2Win_10034_MixRGB(0xff, 0xff, 0);
				}
				if (dword_6FBB9FC0 == 0)
				{
					D2GFX_DrawBox(gnScreenWidth / 2 + -0x82, gnScreenHeight / 2 + 0x9e, gnScreenWidth / 2 + 0x82,
					    gnScreenHeight / 2 + 0xb2, CONCAT31((int32_t)(gnScreenWidth >> 0x1f), byte_6FBBA971), DRAWMODE_TRANS50);
					D2GFX_DrawBox(gnScreenWidth / 2 + -0x80, gnScreenHeight / 2 + 0xa0, gnScreenWidth / 2 + 0x80,
					    gnScreenHeight / 2 + 0xb0, 0, DRAWMODE_NORMAL);
					iVar1 = sub_6FAAD550();
					if (iVar1 != 0)
					{
						sub_6FB5B0F0(gnScreenWidth / 2 + -0x80, gnScreenHeight / 2 + 0xa0, iVar1, 0x10,
						    CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), byte_6FBBA970), (DrawMode)(5));
					}
				}
			}
			iVar1 = D2CMP_CelFileGetCelsPerDirection(sghLoadScreenProgress);
			if (iVar1 <= (int)dword_6FBBA96C)
			{
				dword_6FBBA96C = iVar1 - 1;
			}
			DStack_354.pCellFile = sghLoadScreenProgress;
			DStack_354.nDirection = 0;
			DStack_354.nFrame = dword_6FBBA96C;
			TEXTURE_CelDraw(&DStack_354, gnScreenWidth / 2 + -0x80, gnScreenHeight / 2 + 0x80, 0xffffffff,
			    DRAWMODE_NORMAL, nullptr);
			D2GFX_EndScene();
			sub_6FAABF30();
			sub_6FAABF60();
		}
	}
	if (a1 != 0)
	{
		dword_6FBBA96C = dword_6FBBA96C + 1;
	}
}

//D2Client.0x6FB245B0
void __fastcall sub_6FB245B0(uint32_t a1)
{
	byte_6FBBA77C = a1;
}

//D2Client.0x6FB245C0
void __cdecl sub_6FB245C0()
{
	if (sghLoadScreenProgress != nullptr)
	{
		CLIENT_FreeCellFile(sghLoadScreenProgress);
		sghLoadScreenProgress = nullptr;
		D2Win_10177(byte_6FBBA77C);
		D2CMP_10097(byte_6FBBA77C);
		sub_6FACF730();
		sub_6FADD2F0();
		sub_6FB01C30();
		sub_6FB01C50();
		sub_6FB16BE0();
		sub_6FAFE930();
		sub_6FAFE950();
		sub_6FAFE990();
		sub_6FAFE970();
		sub_6FAA7050(dword_6FBA798C);
		sub_6FAAC000(2000);
	}
	byte_6FBBA774 = 0;
	sghLoadScreenProgress = nullptr;
	dword_6FBBA758 = 0;
}

//D2Client.0x6FB24650
uint32_t __cdecl sub_6FB24650()
{
	return dword_6FBBA758;
}

//D2Client.0x6FB24660
uint32_t __cdecl sub_6FB24660()
{
	DWORD DVar1;

	DVar1 = GetTickCount();
	if (0x32 < DVar1 - dword_6FBBA974)
	{
		dword_6FBBA974 = DVar1;
		return 1;
	}
	return 0;
}

//D2Client.0x6FB24690
bool __fastcall sub_6FB24690(int* a1)
{
	*a1 = 0;
	a1[2] = gnScreenWidth;
	a1[1] = 0;
	a1[3] = gnScreenWidth;
	if ((((dword_6FBBA704 == 0) && (dword_6FBBA70C == 0)) && (dword_6FBBA710 == 0)) &&
	    (((dword_6FBBA6D8 == 0 && (dword_6FBBA718 == 0)) && (dword_6FBBA714 == 0))))
	{
		if (((dword_6FBBA71C != 0) || (dword_6FBBA700 != 0)) ||
		    ((dword_6FBBA6B0 != 0 ||
		        ((((dword_6FBBA6E4 != 0 || (dword_6FBBA738 != 0)) || (dword_6FBBA73C != 0)) || (dword_6FBBA6F8 != 0))))))
		{
			*a1 = gnScreenWidth / 2;
		}
		if ((dword_6FBBA6AC != 0) || (dword_6FBBA6B8 != 0))
		{
			a1[2] = gnScreenWidth / 2;
		}
		return *a1 != a1[2];
	}
	return false;
}

//D2Client.0x6FB24780
int __cdecl sub_6FB24780()
{
	return gnScreenHeight + -0x31;
}

//D2Client.0x6FB24790
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB24790()
{
	bool bVar1;
	HWND__* pHVar2;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	uint32_t uVar3;

	uVar3 = 0xd;
	pHVar2 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FD70), uVar3);
	bVar1 = sub_6FAAB290();
	if ((D2C_ZEXT(bVar1) == 0) &&
	    (bVar1 = sub_6FAAB250(), D2C_ZEXT(bVar1) == 0))
	{
		return;
	}
	uVar3 = 1;
	pHVar2 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB6FE0C), uVar3);
}

//D2Client.0x6FB247D0
void __fastcall sub_6FB247D0()
{
	sub_6FB1F320();
	sub_6FAFC1F0();
}

//D2Client.0x6FB247E0
bool __cdecl sub_6FB247E0()
{
	return dword_6FBB9FC4 != 0;
}

//D2Client.0x6FB247F0
int __fastcall sub_6FB247F0(int a1)
{
	int iVar1;
	int iVar2;

	if ((((-1 < a1) && (iVar1 = *(int*)((uint8_t*)&sgptDataTables), a1 < *(int*)(iVar1 + 0xa80))) && (iVar2 = (int)*(short*)(*(int*)(iVar1 + 0xa78) + 0x18 + a1 * 0x1a8), -1 < iVar2)) &&
	    (iVar2 < *(int*)(iVar1 + 0xa98)))
	{
		return *(int*)(iVar1 + 0xa90) + iVar2 * 0x134;
	}
	return 0;
}

//D2Client.0x6FB24840
void __cdecl sub_6FB24840()
{
	uint8_t* puVar1;
	int iVar2;

	dword_6FBBA97C = 0;
	dword_6FBBA984 = 0;
	byte_6FBBA980 = 0;
	byte_6FBBA990 = 0;
	gpCellFile_6FBBA99C = sub_6FB20100("menu\\upgrade");
	gpCellFile_6FBBA9A0 = sub_6FB20100((char*)(dword_6FB90717 + 1));
	if (0 < dword_6FB906B0)
	{
		puVar1 = &byte_6FB90686;
		iVar2 = dword_6FB906B0;
		do
		{
			puVar1[1] = 0;
			*puVar1 = 0;
			puVar1 = puVar1 + 0x28;
			iVar2 = iVar2 + -1;
		} while (iVar2 != 0);
	}
}

//D2Client.0x6FB248A0
void __cdecl sub_6FB248A0()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	HWND__* pHVar3;
	float fVar4;
	float fVar5;
	int iVar6;
	uint32_t uVar7;

	if (dword_6FBBA97C == 0)
		goto LAB_6fb24973;
	dword_6FBBA97C = 0;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		pDVar1 = nullptr;
	}
	else
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar1 != nullptr)
		{
			dword_6FBBA988 = pDVar1->dwUnitId;
			iVar6 = 0;
			fVar5 = 0.0;
			fVar4 = 0.0;
			iVar2 = sub_6FB2E590(pDVar1);
		LAB_6fb2492c:
			sub_6FB55820(iVar2, nullptr, fVar4, fVar5, iVar6);
		}
	}
	else if (dword_6FBBA97C == 2)
	{
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar1 != nullptr)
		{
			sub_6FB575B0(pDVar1);
		}
		iVar6 = 0;
		fVar5 = 0.0;
		fVar4 = 0.0;
		iVar2 = 1;
		goto LAB_6fb2492c;
	}
	uVar7 = 8;
	pHVar3 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar7);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
LAB_6fb24973:
	if (gpCellFile_6FBBA99C != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA99C);
		gpCellFile_6FBBA99C = nullptr;
	}
	if (gpCellFile_6FBBA9A0 != nullptr)
	{
		CLIENT_FreeCellFile(gpCellFile_6FBBA9A0);
		gpCellFile_6FBBA9A0 = nullptr;
	}
}

//D2Client.0x6FB249A0
void __cdecl sub_6FB249A0(int a1)
{
	D2Win_10129_DrawFramedText(nullptr, -1, -1, 0, 0);
	sub_6FB01B50(a1);
	if (dword_6FBBA97C == 1)
	{
		sub_6FAEADA0(a1);
	}
}

//D2Client.0x6FB249D0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB249D0()
{
	D2UnitStrc* pDVar1;
	int iVar2;
	HWND__* pHVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	float fVar5;
	float fVar6;
	int iVar7;

	if (dword_6FBBA97C == 3)
	{
		return;
	}
	if (dword_6FBBA97C == 2)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			pDVar1 = nullptr;
		}
		else
		{
			pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
		}
		sub_6FB575B0(pDVar1);
	}
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	if (dword_6FBBA978 == 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar4 = 0xffffffff;
		}
		else
		{
			uVar4 = pDVar1->dwUnitId;
		}
		sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar4, dword_6FBBA984, 0, 2);
	}
	else
	{
		sub_6FAF3AD0();
	}
	dword_6FBBA97C = 0;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		pDVar1 = nullptr;
	}
	else
	{
		pDVar1 = INVENTORY_GetCursorItem(pDVar1->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar1 == nullptr)
			goto LAB_6fb24ad5;
		dword_6FBBA988 = pDVar1->dwUnitId;
		iVar7 = 0;
		fVar6 = 0.0;
		fVar5 = 0.0;
		iVar2 = sub_6FB2E590(pDVar1);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb24ad5;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar1 != nullptr)
		{
			sub_6FB575B0(pDVar1);
		}
		iVar7 = 0;
		fVar6 = 0.0;
		fVar5 = 0.0;
		iVar2 = 1;
	}
	sub_6FB55820(iVar2, nullptr, fVar5, fVar6, iVar7);
LAB_6fb24ad5:
	uVar4 = 8;
	pHVar3 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar4);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB24B20
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FB24B20(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	D2UnitStrc* pDVar2;
	HWND__* pHVar3;
	uint32_t extraout_ECX;
	uint32_t uVar4;
	uint32_t uVar5;
	float fVar6;
	float fVar7;
	int iVar8;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	uVar5 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
	uVar4 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	if (dword_6FBBA97C != 2)
	{
		iVar1 = sub_6FAEAE70(pSMSGHANDLER_PARAMS);
		if (iVar1 == 0)
		{
			sub_6FB24CD0(uVar5, uVar4);
		}
		return;
	}
	iVar1 = sub_6FB24CD0(uVar5, uVar4);
	if (iVar1 != 0)
	{
		return;
	}
	iVar1 = sub_6FAEAF40(pSMSGHANDLER_PARAMS);
	if (iVar1 == 0)
	{
		return;
	}
	if (dword_6FBBA97C == 3)
	{
		return;
	}
	if (dword_6FBBA97C == 2)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 == nullptr)
		{
			pDVar2 = nullptr;
		}
		else
		{
			pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
		}
		sub_6FB575B0(pDVar2);
	}
	sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	if (dword_6FBBA978 == 0)
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 == nullptr)
		{
			uVar4 = 0xffffffff;
		}
		else
		{
			uVar4 = pDVar2->dwUnitId;
		}
		sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar4, dword_6FBBA984, 0, 2);
	}
	else
	{
		sub_6FAF3AD0();
	}
	dword_6FBBA97C = 0;
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		pDVar2 = nullptr;
	}
	else
	{
		pDVar2 = INVENTORY_GetCursorItem(pDVar2->pInventory);
	}
	if (dword_6FBBA97C == 1)
	{
		dword_6FBBA97C = 2;
		sub_6FB575B0(nullptr);
		if (pDVar2 == nullptr)
			goto LAB_6fb24c65;
		dword_6FBBA988 = pDVar2->dwUnitId;
		iVar8 = 0;
		fVar7 = 0.0;
		fVar6 = 0.0;
		iVar1 = sub_6FB2E590(pDVar2);
	}
	else
	{
		if (dword_6FBBA97C != 2)
			goto LAB_6fb24c65;
		dword_6FBBA97C = 1;
		dword_6FBBA988 = 0;
		if (pDVar2 != nullptr)
		{
			sub_6FB575B0(pDVar2);
		}
		iVar8 = 0;
		fVar7 = 0.0;
		fVar6 = 0.0;
		iVar1 = 1;
	}
	sub_6FB55820(iVar1, nullptr, fVar6, fVar7, iVar8);
LAB_6fb24c65:
	uVar4 = 8;
	pHVar3 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar4);
	if (dword_6FBBA98C != 0)
	{
		sub_6FAD6DC0();
		dword_6FBBA98C = 0;
	}
	sub_6FB23260(0xe, 1, 0);
	sub_6FAB6450(nullptr);
}

//D2Client.0x6FB24CD0
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FB24CD0(int a1, int a2)
{
	uint32_t uVar1;
	Unicode* pUVar2;
	D2UnitStrc* pDVar3;
	HWND__* pHVar4;
	uint32_t extraout_ECX;
	uint8_t* puVar5;
	uint32_t uVar6;
	int iVar7;
	uint32_t uVar8;
	int iVar9;
	uint32_t uVar10;
	float fVar11;
	uint32_t uVar12;
	float fVar13;
	int iVar14;

	uVar1 = 0;
	iVar7 = 0;
	if (0 < dword_6FB906B0)
	{
		do
		{
			if (((((&byte_6FB90687)[iVar7 * 0x28] != '\0') && ((int)("z")[iVar7 * 10] <= a1)) && (a1 <= (int)(&dword_6FB90676)[iVar7 * 10])) &&
			    (((int)(&dword_6FB9067A)[iVar7 * 10] <= a2 &&
			        (a2 <= (int)(&dword_6FB9067E)[iVar7 * 10]))))
			{
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				if (iVar7 == 0)
				{
					if (dword_6FBBA97C == 2)
					{
						sub_6FB55820(2, nullptr, 0.0, 0.0, 0);
						dword_6FBBA98C = (int)sub_6FAD6BE0(0x96, 0x82, 0x6fb24f70, 0, 1, 0, 1, 0, 0, 0, 1);
						sub_6FAD7150(dword_6FBBA98C, 0);
						iVar14 = 0;
						uVar12 = 0;
						uVar10 = 1;
						iVar9 = 0;
						uVar8 = 0;
						uVar1 = 0xf;
						pUVar2 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd19));
						sub_6FAD7180(dword_6FBBA98C, pUVar2, uVar1, uVar8, iVar9, uVar10, uVar12, iVar14);
						dword_6FBBA97C = 3;
						if (dword_6FBBA978 == 0)
						{
							pDVar3 = CUNIT_GetPlayer();
							if (pDVar3 == nullptr)
							{
								uVar6 = 0xffffffff;
							}
							else
							{
								uVar6 = pDVar3->dwUnitId;
							}
							sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)dword_6FBBA984 >> 8), 0x44), uVar6, dword_6FBBA984,
							    dword_6FBBA988, 3);
						}
						else
						{
							sub_6FAF70A0(dword_6FBBA988);
						}
					}
				}
				else if (dword_6FBBA97C != 3)
				{
					if (dword_6FBBA97C == 2)
					{
						pDVar3 = CUNIT_GetPlayer();
						if (pDVar3 == nullptr)
						{
							pDVar3 = nullptr;
						}
						else
						{
							pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
						}
						sub_6FB575B0(pDVar3);
					}
					sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
					if (dword_6FBBA978 == 0)
					{
						pDVar3 = CUNIT_GetPlayer();
						if (pDVar3 == nullptr)
						{
							uVar6 = 0xffffffff;
						}
						else
						{
							uVar6 = pDVar3->dwUnitId;
						}
						sub_6FAADAA0(CONCAT31((int32_t)((uint32_t)extraout_ECX >> 8), 0x44), uVar6, dword_6FBBA984, 0, 2);
					}
					else
					{
						sub_6FAF3AD0();
					}
					dword_6FBBA97C = 0;
					pDVar3 = CUNIT_GetPlayer();
					if (pDVar3 == nullptr)
					{
						pDVar3 = nullptr;
					}
					else
					{
						pDVar3 = INVENTORY_GetCursorItem(pDVar3->pInventory);
					}
					if (dword_6FBBA97C == 1)
					{
						dword_6FBBA97C = 2;
						sub_6FB575B0(nullptr);
						if (pDVar3 != nullptr)
						{
							dword_6FBBA988 = pDVar3->dwUnitId;
							iVar14 = 0;
							fVar13 = 0.0;
							fVar11 = 0.0;
							iVar9 = sub_6FB2E590(pDVar3);
						LAB_6fb24eee:
							sub_6FB55820(iVar9, nullptr, fVar11, fVar13, iVar14);
						}
					}
					else if (dword_6FBBA97C == 2)
					{
						dword_6FBBA97C = 1;
						dword_6FBBA988 = 0;
						if (pDVar3 != nullptr)
						{
							sub_6FB575B0(pDVar3);
						}
						iVar14 = 0;
						fVar13 = 0.0;
						fVar11 = 0.0;
						iVar9 = 1;
						goto LAB_6fb24eee;
					}
					uVar6 = 8;
					pHVar4 = WINDOW_GetWindow();
					WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB906B8), uVar6);
					if (dword_6FBBA98C != 0)
					{
						sub_6FAD6DC0();
						dword_6FBBA98C = 0;
					}
					sub_6FB23260(0xe, 1, 0);
					sub_6FAB6450(nullptr);
				}
				uVar1 = 1;
			}
			iVar7 = iVar7 + 1;
		} while (iVar7 < dword_6FB906B0);
		if (0 < dword_6FB906B0)
		{
			puVar5 = &byte_6FB90686;
			iVar7 = dword_6FB906B0;
			do
			{
				puVar5[1] = 0;
				*puVar5 = 0;
				puVar5 = puVar5 + 0x28;
				iVar7 = iVar7 + -1;
			} while (iVar7 != 0);
		}
	}
	return uVar1;
}

//D2Client.0x6FB24F70
uint32_t __cdecl sub_6FB24F70()
{
	return 0;
}

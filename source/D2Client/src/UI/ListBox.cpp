#include "UI/ListBox.h"

//D2Client.0x6FAF11E0
uint32_t __fastcall sub_6FAF11E0(void* a1, int a2, int a3)
{
	int iVar1;

	iVar1 = *(int*)((int)a1 + 8);
	if (((-1 < a3) && (a3 < (int)(uint32_t) * (uint16_t*)(iVar1 + 0x180748))) && (a3 < 0x80))
	{
		return *(uint32_t*)(iVar1 + 0x300a + a3 * 0x300e);
	}
	D2_ASSERT(0x7f >= *(uint16_t*)(iVar1 + 0x180748));
	D2_ASSERT(a3 > (int)(uint32_t) * (uint16_t*)(iVar1 + 0x180748));
	D2_ASSERT(a3 >= 0);
	return 0;
}

//D2Client.0x6FAF12A0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAF12A0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 0x34))();
}

//D2Client.0x6FAF12B0
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAF12B0(int a1)
{
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(**(code**)(**(int**)(a1 + 8) + 8))();
}

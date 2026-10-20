#include "UI/CmdTbl.h"

#include "Core/WndProc.h"
#include "Game/Game.h"
#include "Sound/SoundInst.h"
#include "UI/Automap.h"
#include "UI/Chat.h"
#include "UI/Dialog.h"

//D2Client.0x6FB78500
uint32_t dword_6FB78500;
//D2Client.0x6FB78978
uint8_t* ptr_6FB78978 = (uint8_t*)sub_6FAD3720;
//D2Client.0x6FB7897C
uint8_t byte_6FB7897C[4];
//D2Client.0x6FB78980
uint8_t byte_6FB78980[676] = {0, 0, 0, 0, 0x30, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x50, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x90, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0xD0, 0x37, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xC0, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x39, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x60, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x90, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x3C, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0xF0, 0x3C, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x10, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x40, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x50, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x60, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x70, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x80, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x90, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0xB0, 0x3D, 0xAD, 0x6F, 0x70, 0x3F, 0xAD, 0x6F, 0, 0, 0, 0, 0x10, 0x3E, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x3E, 0xAD, 0x6F, 0xB0, 0x3F, 0xAD, 0x6F, 0, 0, 0, 0, 0x40, 0x3E, 0xAD, 0x6F, 0xC0, 0x3F, 0xAD, 0x6F, 0, 0, 0, 0, 0x50, 0x3E, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x3E, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xD0, 0x3E, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x60, 0x3F, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0xFA, 0xBF, 0xB6, 0x6F, 1, 0, 0, 0, 0x70, 0xBD, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xF0, 0x3E, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0xE0, 0x38, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0xC0, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xF0, 0x3A, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x3B, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x3B, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xB0, 0x3B, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xF0, 0x3B, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x30, 0x3C, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x70, 0x3C, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0x3F, 0xAD, 0x6F, 0, 0, 0, 0, 0, 0, 0, 0, 0xA0, 0x3D, 0xAD, 0x6F, 0, 0, 0, 0, 1, 0, 0, 0, 0x60, 0x3E, 0xAD, 0x6F};
//D2Client.0x6FB78C24
uint32_t tbl_6FB78C24[12] = {0, 0x100, (uint32_t)sub_6FAD5A00, 0, 0x104, (uint32_t)sub_6FAD5A00, 0, 0x101, (uint32_t)sub_6FAD5B00, 0, 0x105, (uint32_t)sub_6FAD5B00};
//D2Client.0x6FB78C54
uint8_t tbl_6FB78C54[23] = {0, 0, 0, 0, 1, 1, 0, 0, 0, 0x5B, 0xAD, 0x6F, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0x5B, 0xAD};
//D2Client.0x6FBB2D20
FARPROC gfarproc_6FBB2D20;
//D2Client.0x6FBB2D28
uint8_t byte_6FBB2D28;
//D2Client.0x6FBB2D2C
FARPROC gfarproc_6FBB2D2C;
//D2Client.0x6FBB2D30
FARPROC gfarproc_6FBB2D30;
//D2Client.0x6FBB2D34
FARPROC gfarproc_6FBB2D34;
//D2Client.0x6FBB2D38
uint32_t dword_6FBB2D38;
//D2Client.0x6FBB2D3C
uint32_t dword_6FBB2D3C;
//D2Client.0x6FBB31AB
uint8_t tbl_6FBB31AB[1];
//D2Client.0x6FBB31AC
FARPROC gfarproc_6FBB31AC;
//D2Client.0x6FBB31B0
uint32_t dword_6FBB31B0;
//D2Client.0x6FBB31B1
uint8_t tbl_6FBB31B1[3];
//D2Client.0x6FBB31B2
uint8_t tbl_6FBB31B2[2];
//D2Client.0x6FBB3624
FARPROC gfarproc_6FBB3624;
//D2Client.0x6FBB3628
FARPROC gfarproc_6FBB3628;
//D2Client.0x6FBB362C
FARPROC gfarproc_6FBB362C;
//D2Client.0x6FBB3630
int32_t dword_6FBB3630;
//D2Client.0x6FBB3634
int32_t dword_6FBB3634;
//D2Client.0x6FBB3638
int32_t dword_6FBB3638;

//D2Client.0x6FAD3FE0
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD3FE0()
{
	BOOL BVar1;

	if (gfarproc_6FBB3624 == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB3624);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse3DownFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB3624)();
}

//D2Client.0x6FAD4020
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD4020()
{
	BOOL BVar1;

	if (gfarproc_6FBB3628 == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB3628);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse3LiftFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB3628)();
}

//D2Client.0x6FAD4060
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD4060()
{
	BOOL BVar1;

	if (gfarproc_6FBB31AC == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB31AC);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse4DownFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB31AC)();
}

//D2Client.0x6FAD40A0
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD40A0()
{
	BOOL BVar1;

	if (gfarproc_6FBB2D34 == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB2D34);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse4LiftFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB2D34)();
}

//D2Client.0x6FAD40E0
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD40E0()
{
	BOOL BVar1;

	if (gfarproc_6FBB2D2C == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB2D2C);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse5DownFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB2D2C)();
}

//D2Client.0x6FAD4120
// TODO: decompilation needs review (jumptable)
void __cdecl sub_6FAD4120()
{
	BOOL BVar1;

	if (gfarproc_6FBB2D20 == (FARPROC)0x0)
	{
		return;
	}
	BVar1 = IsBadCodePtr(gfarproc_6FBB2D20);
	if (BVar1 != 0)
	{
		FOG_DisplayAssert("sgpfnMouse5LiftFn", __FILE__, __LINE__);
		exit(-1);
	}
	// TODO: Ghidra: Could not recover jumptable
	// TODO: Ghidra: Treating indirect jump
	(*gfarproc_6FBB2D20)();
}

//D2Client.0x6FAD4160
// TODO: decompilation needs review (jumptable)
void __fastcall sub_6FAD4160(int a1)
{
	BOOL BVar1;

	if (a1 < 1)
	{
		if ((a1 < 0) && (gfarproc_6FBB2D30 != (FARPROC)0x0))
		{
			BVar1 = IsBadCodePtr(gfarproc_6FBB2D30);
			D2_ASSERT(!BVar1);
			// TODO: Ghidra: Could not recover jumptable
			// TODO: Ghidra: Treating indirect jump
			(*gfarproc_6FBB2D30)();
			return;
		}
	}
	else if (gfarproc_6FBB362C != (FARPROC)0x0)
	{
		BVar1 = IsBadCodePtr(gfarproc_6FBB362C);
		D2_ASSERT(!BVar1);
		// TODO: Ghidra: Could not recover jumptable
		// TODO: Ghidra: Treating indirect jump
		(*gfarproc_6FBB362C)();
		return;
	}
}

//D2Client.0x6FAD41E0
void __cdecl sub_6FAD41E0()
{
	char cVar1;
	bool bVar2;
	void* pvVar3;
	int iVar4;
	uint32_t* puVar5;
	D2CellFileStrc* pFree;
	HD2ARCHIVE__* pHVar6;
	int iVar7;
	int* piVar8;
	short* psVar9;
	uint32_t* puVar10;
	uint8_t* pbVar11;
	short* psVar12;
	uint32_t* puVar13;
	char* pcVar14;
	D2CellFileStrc* pDVar15;
	char* pcVar16;
	uint32_t uVar17;
	int local_588;
	uint32_t local_584;
	char acStack_580[260];
	uint8_t local_47c[2];
	int local_47a;
	short asStack_476[571];

	pvVar3 = (void*)sub_6FAD4760(0x80000000, 3);
	if (pvVar3 != (void*)0xffffffff)
	{
		*(uint16_t*)local_47c = (uint16_t)0x0;
		puVar5 = (uint32_t*)(local_47c + 2);
		for (iVar7 = 0x11d; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 1;
		}
		local_588 = 0;
		FOG_10110((int)pvVar3, (int)local_47c, 0x476, (int)&local_588, 0);
		FOG_CloseFile(pvVar3);
		if ((local_588 == 0x476) && (*(uint16_t*)local_47c == 0x25))
		{
			iVar7 = 0;
			do
			{
				bVar2 = false;
				iVar4 = 0;
				piVar8 = (int*)(local_47c + 2);
				do
				{
					if (bVar2)
						goto LAB_6fad4284;
					if (*piVar8 == iVar7)
					{
						bVar2 = true;
					}
					iVar4 = iVar4 + 1;
					piVar8 = (int*)((int)piVar8 + 10);
				} while (iVar4 < 0x72);
				if (!bVar2)
					goto LAB_6fad42f2;
			LAB_6fad4284:
				iVar7 = iVar7 + 1;
			} while (iVar7 < 0x39);
			iVar7 = 0;
			psVar12 = asStack_476;
			do
			{
				iVar4 = 0;
				psVar9 = asStack_476;
				do
				{
					if (((*psVar12 != -1) && (iVar7 != iVar4)) && (*psVar12 == *psVar9))
						goto LAB_6fad42f2;
					iVar4 = iVar4 + 1;
					psVar9 = psVar9 + 5;
				} while (iVar4 < 0x72);
				iVar7 = iVar7 + 1;
				psVar12 = psVar12 + 5;
			} while (iVar7 < 0x72);
			puVar5 = &dword_6FBB2D3C;
			do
			{
				*(uint16_t*)puVar5 = 0xffff;
				puVar5 = (uint32_t*)((int)puVar5 + 10);
			} while ((int)puVar5 < (int)&dword_6FBB31B0);
			puVar5 = (uint32_t*)(local_47c + 2);
			puVar13 = &dword_6FBB2D38;
			for (iVar7 = 0x11d; iVar7 != 0; iVar7 = iVar7 + -1)
			{
				*puVar13 = *puVar5;
				puVar5 = puVar5 + 1;
				puVar13 = puVar13 + 1;
			}
			sub_6FAD4470();
			goto LAB_6fad4456;
		}
	}
LAB_6fad42f2:
	D2LANG_10006((char*)((int)local_584), 0);
	FOG_GetInstallPath(acStack_580, 0xdc);
	iVar7 = -1;
	pcVar16 = acStack_580;
	do
	{
		pcVar14 = pcVar16;
		if (iVar7 == 0)
			break;
		iVar7 = iVar7 + -1;
		pcVar14 = pcVar16 + 1;
		cVar1 = *pcVar16;
		pcVar16 = pcVar14;
	} while (cVar1 != '\0');
	*(uint32_t*)(pcVar14 + -1) = (*(uint32_t*)((uint8_t*)&"default.key" + 0));
	*(uint32_t*)(pcVar14 + 3) = (*(uint32_t*)((uint8_t*)&"default.key" + 4));
	*(uint32_t*)(pcVar14 + 7) = (*(uint32_t*)((uint8_t*)&"default.key" + 8));
	pvVar3 = FOG_CreateFileA(acStack_580, 0x80000000, 0, nullptr, 3, 0x80, nullptr);
	if (pvVar3 == (void*)0xffffffff)
	{
	LAB_6fad43aa:
		sprintf(acStack_580, "%s\\CMD\\%s\\default.key", "DATA\\LOCAL", local_584);
		uVar17 = 0x536;
		pcVar16 = __FILE__;
		piVar8 = nullptr;
		pHVar6 = D2Win_GetArchive();
		pFree = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar6), acStack_580, (size_t*)(piVar8), pcVar16, uVar17));
	}
	else
	{
		FOG_10110((int)pvVar3, (int)local_47c, 0x47a, (int)&local_588, 0);
		FOG_CloseFile(pvVar3);
		if (local_588 != 0x47a)
			goto LAB_6fad43aa;
		pFree = (D2CellFileStrc*)
		    D2_ALLOC_POOL(nullptr, 0x47a);
		puVar10 = (uint32_t*)local_47c;
		pDVar15 = pFree;
		for (iVar7 = 0x11e; iVar7 != 0; iVar7 = iVar7 + -1)
		{
			pDVar15->dwVersion = *puVar10;
			puVar10 = puVar10 + 1;
			pDVar15 = (D2CellFileStrc*)&pDVar15->dwFlags;
		}
		*(short*)&pDVar15->dwVersion = (short)*puVar10;
	}
	if (pFree != nullptr)
	{
		if ((((short)pFree->dwVersion == 0x5357) && (*(short*)((int)&pFree->dwVersion + 2) == 0x25)) &&
		    (pFree->dwFlags == 0x47a))
		{
			pbVar11 = &pFree->mylastcol;
			puVar5 = &dword_6FB78500;
			for (iVar7 = 0x11d; iVar7 != 0; iVar7 = iVar7 + -1)
			{
				*puVar5 = *(uint32_t*)pbVar11;
				pbVar11 = pbVar11 + 4;
				puVar5 = puVar5 + 1;
			}
			iVar7 = 0x544;
		}
		else
		{
			iVar7 = 0x549;
		}
		D2_FREE(pFree);
	}
	puVar5 = &dword_6FBB2D3C;
	do
	{
		*(uint16_t*)puVar5 = 0xffff;
		puVar5 = (uint32_t*)((int)puVar5 + 10);
	} while ((int)puVar5 < (int)&dword_6FBB31B0);
	puVar5 = &dword_6FB78500;
	puVar13 = &dword_6FBB2D38;
	for (iVar7 = 0x11d; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*puVar13 = *puVar5;
		puVar5 = puVar5 + 1;
		puVar13 = puVar13 + 1;
	}
	sub_6FAD4470();
	sub_6FAD4890();
LAB_6fad4456:
	sub_6FAD5BE0(1, 0);
}

//D2Client.0x6FAD4470
void __cdecl sub_6FAD4470()
{
	gfarproc_6FBB362C = nullptr;
	gfarproc_6FBB2D30 = nullptr;
	gfarproc_6FBB3624 = nullptr;
	gfarproc_6FBB3628 = nullptr;
	gfarproc_6FBB31AC = nullptr;
	gfarproc_6FBB2D34 = nullptr;
	gfarproc_6FBB2D2C = nullptr;
	gfarproc_6FBB2D20 = nullptr;

	// Key bindings: 10 byte records { int32_t nCommand; uint16_t nKey; ... }
	for (uint8_t* pBinding = (uint8_t*)&dword_6FBB2D38; pBinding < (uint8_t*)&gfarproc_6FBB31AC; pBinding += 10)
	{
		uint16_t* pKey = (uint16_t*)(pBinding + 4);
		const int32_t nCommand = *(int32_t*)pBinding;
		if (*pKey <= 0xDF || nCommand >= 0x39)
		{
			continue;
		}

		const uint32_t nButton = *pKey - 0x100;
		if (nButton > 4)
		{
			continue;
		}

		int32_t bValid = 0;
		switch (nButton)
		{
		case 0:
			bValid = sub_6FAAB2E0();
			break;
		case 1:
		case 2:
			bValid = sub_6FAAB320();
			break;
		case 3:
		case 4:
			bValid = (sub_6FAAB250() || sub_6FAAB290()) && *(int32_t*)(byte_6FB7897C + nCommand * 0xC) == 0;
			break;
		}

		if (!bValid)
		{
			*pKey = 0xFFFF;
			continue;
		}

		FARPROC pfCommand = (FARPROC)(&ptr_6FB78978)[nCommand * 3];
		FARPROC pfCommandUp = *(FARPROC*)(byte_6FB7897C + nCommand * 0xC);
		switch (nButton)
		{
		case 0:
			gfarproc_6FBB3624 = pfCommand;
			gfarproc_6FBB3628 = pfCommandUp;
			break;
		case 1:
			gfarproc_6FBB31AC = pfCommand;
			gfarproc_6FBB2D34 = pfCommandUp;
			break;
		case 2:
			gfarproc_6FBB2D2C = pfCommand;
			gfarproc_6FBB2D20 = pfCommandUp;
			break;
		case 3:
			gfarproc_6FBB362C = pfCommand;
			break;
		case 4:
			gfarproc_6FBB2D30 = pfCommand;
			break;
		}
	}
}

//D2Client.0x6FAD4760
int32_t __fastcall sub_6FAD4760(uint32_t a1, uint32_t a2)
{
	void* pvVar1;
	int iVar2;
	uint32_t* puVar3;
	char local_30c;
	uint32_t local_30b;
	char local_208;
	uint32_t local_207;
	char local_104;
	uint32_t local_103;

	local_104 = byte_6FB9A828;
	puVar3 = &local_103;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint16_t*)puVar3 = 0;
	*(uint8_t*)((int)puVar3 + 2) = 0;
	local_30c = byte_6FB9A828;
	puVar3 = &local_30b;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint16_t*)puVar3 = 0;
	*(uint8_t*)((int)puVar3 + 2) = 0;
	local_208 = byte_6FB9A828;
	puVar3 = &local_207;
	for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	*(uint16_t*)puVar3 = 0;
	*(uint8_t*)((int)puVar3 + 2) = 0;
	FOG_GetSavePath(&local_104, 0x104);
	if (byte_6FBA77F0 != '\0')
	{
		SStrPrintf(&local_208, 0x104, "%s%s\\", &local_104, &byte_6FBA77F0);
		FOG_10114((int)&local_208);
		SStrPrintf(&local_30c, 0x104, "%s%s.key", &local_208, gszPlayerName);
		pvVar1 = FOG_CreateFileA(&local_30c, a1, 0, nullptr, a2, 0x80,
		    nullptr);
		if (pvVar1 != (void*)0xffffffff)
		{
			return 0;
		}
	}
	SStrPrintf(&local_30c, 0x104, "%s%s.key", &local_104, gszPlayerName);
	return (int32_t)(FOG_CreateFileA(&local_30c, a1, 0, nullptr, a2, 0x80, nullptr));
}

//D2Client.0x6FAD4890
void __cdecl sub_6FAD4890()
{
	char cVar1;
	void* pvVar2;
	uint16_t* puVar3;
	int iVar4;
	uint32_t* puVar5;
	uint32_t* puVar6;
	char* pcVar7;
	char* pcVar8;
	uint32_t local_588;
	uint16_t uStack_584;
	uint16_t uStack_582;
	uint16_t uStack_580;
	char acStack_57c[260];
	uint16_t local_478;
	uint32_t local_476;
	uint16_t local_472[569];

	pvVar2 = (void*)sub_6FAD4760(0x40000000, 2);
	if (pvVar2 != (void*)0xffffffff)
	{
		puVar5 = &local_476;
		for (iVar4 = 0x11d; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar5 = 0;
			puVar5 = puVar5 + 1;
		}
		local_588 = 0;
		local_478 = 0x25;
		puVar3 = local_472;
		iVar4 = 0x72;
		do
		{
			*puVar3 = 0xffff;
			puVar3 = puVar3 + 5;
			iVar4 = iVar4 + -1;
		} while (iVar4 != 0);
		puVar5 = &dword_6FBB2D38;
		puVar6 = &local_476;
		for (iVar4 = 0x11d; iVar4 != 0; iVar4 = iVar4 + -1)
		{
			*puVar6 = *puVar5;
			puVar5 = puVar5 + 1;
			puVar6 = puVar6 + 1;
		}
		FOG_10111((int)pvVar2, (int)&local_478, 0x476, (int)&local_588, 0);
		FOG_CloseFile(pvVar2);
		FOG_GetInstallPath(acStack_57c, 0xdc);
		iVar4 = -1;
		pcVar7 = acStack_57c;
		do
		{
			pcVar8 = pcVar7;
			if (iVar4 == 0)
				break;
			iVar4 = iVar4 + -1;
			pcVar8 = pcVar7 + 1;
			cVar1 = *pcVar7;
			pcVar7 = pcVar8;
		} while (cVar1 != '\0');
		*(uint32_t*)(pcVar8 + -1) = (*(uint32_t*)((uint8_t*)&"default.key" + 0));
		*(uint32_t*)(pcVar8 + 3) = (*(uint32_t*)((uint8_t*)&"default.key" + 4));
		*(uint32_t*)(pcVar8 + 7) = (*(uint32_t*)((uint8_t*)&"default.key" + 8));
		pvVar2 = FOG_CreateFileA(acStack_57c, 0x40000000, 0, nullptr, 2, 0x80, nullptr);
		if (pvVar2 != (void*)0xffffffff)
		{
			uStack_584 = 0x5357;
			uStack_582 = 0x25;
			uStack_580 = 0x47a;
			FOG_10111((int)pvVar2, (int)&uStack_584, 6, (int)&local_588, 0);
			FOG_10111((int)pvVar2, (int)&dword_6FBB2D38, 0x474, (int)&local_588, 0);
			FOG_CloseFile(pvVar2);
		}
	}
}

//D2Client.0x6FAD49D0
void __cdecl sub_6FAD49D0()
{
	sub_6FAD5BE0(0, 0);
}

//D2Client.0x6FAD49E0
void __fastcall sub_6FAD49E0(int a1)
{
	char cVar1;
	void* hFILE;
	D2CellFileStrc* pFree;
	HD2ARCHIVE__* pHVar2;
	uint32_t* puVar3;
	int iVar4;
	uint32_t* puVar5;
	uint8_t* pbVar6;
	char* pcVar7;
	D2CellFileStrc* pDVar8;
	uint32_t* puVar9;
	int* piVar10;
	char* pcVar11;
	uint32_t uVar12;
	uint32_t local_588;
	int iStack_584;
	char acStack_580[260];
	uint32_t auStack_47c[287];

	D2LANG_10006((char*)((int)local_588), 0);
	if (a1 != 0)
	{
		FOG_GetInstallPath(acStack_580, 0xdc);
		iVar4 = -1;
		pcVar11 = acStack_580;
		do
		{
			pcVar7 = pcVar11;
			if (iVar4 == 0)
				break;
			iVar4 = iVar4 + -1;
			pcVar7 = pcVar11 + 1;
			cVar1 = *pcVar11;
			pcVar11 = pcVar7;
		} while (cVar1 != '\0');
		*(uint32_t*)(pcVar7 + -1) = (*(uint32_t*)((uint8_t*)&"default.key" + 0));
		*(uint32_t*)(pcVar7 + 3) = (*(uint32_t*)((uint8_t*)&"default.key" + 4));
		*(uint32_t*)(pcVar7 + 7) = (*(uint32_t*)((uint8_t*)&"default.key" + 8));
		hFILE = FOG_CreateFileA(acStack_580, 0x80000000, 0, nullptr, 3, 0x80, nullptr);
		if (hFILE != (void*)0xffffffff)
		{
			FOG_10110((int)hFILE, (int)auStack_47c, 0x47a, (int)&iStack_584, 0);
			FOG_CloseFile(hFILE);
			if (iStack_584 == 0x47a)
			{
				pFree = (D2CellFileStrc*)
				    D2_ALLOC_POOL(nullptr, 0x47a);
				puVar5 = auStack_47c;
				pDVar8 = pFree;
				for (iVar4 = 0x11e; iVar4 != 0; iVar4 = iVar4 + -1)
				{
					pDVar8->dwVersion = *puVar5;
					puVar5 = puVar5 + 1;
					pDVar8 = (D2CellFileStrc*)&pDVar8->dwFlags;
				}
				*(short*)&pDVar8->dwVersion = (short)*puVar5;
				goto LAB_6fad4ae2;
			}
		}
	}
	sprintf(acStack_580, "%s\\CMD\\%s\\default.key", "DATA\\LOCAL", local_588);
	uVar12 = 0x536;
	pcVar11 = __FILE__;
	piVar10 = nullptr;
	pHVar2 = D2Win_GetArchive();
	pFree = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar2), acStack_580, (size_t*)(piVar10), pcVar11, uVar12));
LAB_6fad4ae2:
	if (pFree != nullptr)
	{
		if ((((short)pFree->dwVersion == 0x5357) && (*(short*)((int)&pFree->dwVersion + 2) == 0x25)) &&
		    (pFree->dwFlags == 0x47a))
		{
			pbVar6 = &pFree->mylastcol;
			puVar3 = &dword_6FB78500;
			for (iVar4 = 0x11d; iVar4 != 0; iVar4 = iVar4 + -1)
			{
				*puVar3 = *(uint32_t*)pbVar6;
				pbVar6 = pbVar6 + 4;
				puVar3 = puVar3 + 1;
			}
			iVar4 = 0x544;
		}
		else
		{
			iVar4 = 0x549;
		}
		D2_FREE(pFree);
	}
	puVar3 = &dword_6FBB2D3C;
	do
	{
		*(uint16_t*)puVar3 = 0xffff;
		puVar3 = (uint32_t*)((int)puVar3 + 10);
	} while ((int)puVar3 < (int)&dword_6FBB31B0);
	puVar3 = &dword_6FB78500;
	puVar9 = &dword_6FBB2D38;
	for (iVar4 = 0x11d; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar9 = *puVar3;
		puVar3 = puVar3 + 1;
		puVar9 = puVar9 + 1;
	}
	sub_6FAD4470();
}

//D2Client.0x6FAD4B60
uint32_t __fastcall sub_6FAD4B60(int a1, int a2)
{
	int* piVar1;
	int iVar2;

	iVar2 = 0;
	piVar1 = (int*)((int)&dword_6FBB2D3C + 2);
	while ((*(int*)((int)piVar1 + -6) != a1 || (*piVar1 != a2)))
	{
		piVar1 = (int*)((int)piVar1 + 10);
		iVar2 = iVar2 + 1;
		if ((int)&tbl_6FBB31B1 < (int)piVar1)
		{
			return CONCAT22((short)((uint32_t)piVar1 >> 0x10), 0xffff);
		}
	}
	return CONCAT22((short)((uint32_t)(iVar2 * 5) >> 0x10),
	    *(uint16_t*)((int)&dword_6FBB2D3C + iVar2 * 10));
}

//D2Client.0x6FAD4B90
uint32_t __fastcall sub_6FAD4B90(void* a1)
{
	int iVar1;
	uint32_t p1;

	p1 = (uint32_t)a1 & 0xffff;
	if (p1 < 0x2b)
	{
		if (p1 == 0x2a)
		{
			return 1;
		}
		switch (p1)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 0x15:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1b:
		case 0x1c:
		case 0x1d:
		case 0x1e:
		case 0x1f:
		case 0x25:
		case 0x26:
		case 0x27:
		case 0x28:
		case 0x29:
			goto switchD_6fad4bb0_caseD_1;
		default:
		switchD_6fad4bb0_caseD_5:
			iVar1 = isalpha(p1);
			if (iVar1 != 0)
			{
				return 1;
			}
			iVar1 = isdigit(p1);
			if (iVar1 != 0)
			{
				return 1;
			}
			return 0;
		case 8:
		case 9:
		case 0xc:
		case 0xd:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		switchD_6fad4bb0_caseD_8:
			return 1;
		}
	}
	switch (p1)
	{
	case 0x2b:
	case 0x5b:
	case 0x5c:
	case 0x5d:
	case 0x90:
	switchD_6fad4bb0_caseD_1:
		return 0;
	case 0x2c:
	case 0x2d:
	case 0x2e:
	case 0x2f:
	case 0x60:
	case 0x61:
	case 0x62:
	case 99:
	case 100:
	case 0x65:
	case 0x66:
	case 0x67:
	case 0x68:
	case 0x69:
	case 0x6a:
	case 0x6b:
	case 0x6c:
	case 0x6d:
	case 0x6e:
	case 0x6f:
	case 0x70:
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:
	case 0x75:
	case 0x76:
	case 0x77:
	case 0x78:
	case 0x79:
	case 0x7a:
	case 0x7b:
	case 0x7c:
	case 0x7d:
	case 0x7e:
	case 0x7f:
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0x87:
	case 0x91:
	case 0xba:
	case 0xbb:
	case 0xbc:
	case 0xbd:
	case 0xbe:
	case 0xbf:
	case 0xc0:
	case 0xdb:
	case 0xdc:
	case 0xdd:
	case 0xde:
	case 0x100:
	case 0x101:
	case 0x102:
	case 0x103:
	case 0x104:
		goto switchD_6fad4bb0_caseD_8;
	default:
		goto switchD_6fad4bb0_caseD_5;
	}
}

//D2Client.0x6FAD4D20
// TODO: decompilation needs review (extraout)
uint32_t __fastcall sub_6FAD4D20(int a1, int a2, void* a3, uint16_t* a4)
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	uint32_t extraout_var_00;
	short* psVar3;
	int* piVar4;
	int iVar5;
	short sVar6;

	if (a4 != nullptr)
	{
		*a4 = 0;
	}
	if (0x38 < a1)
	{
		return 0;
	}
	if (a1 == 0x38)
	{
		return 0;
	}
	iVar2 = sub_6FAD4B90(a3);
	if (iVar2 == 0)
	{
		if (a4 == nullptr)
		{
			return 0;
		}
		*a4 = 0xf8b;
		return 0;
	}
	switch ((uint32_t)a3 & 0xffff)
	{
	case 0x100:
		iVar2 = sub_6FAAB2E0();
		break;
	case 0x101:
	case 0x102:
		iVar2 = sub_6FAAB320();
		break;
	case 0x103:
	case 0x104:
		bVar1 = sub_6FAAB250();
		if (((D2C_ZEXT(bVar1) == 0) &&
		        (bVar1 = sub_6FAAB290(), D2C_ZEXT(bVar1) == 0)) ||
		    (*(int*)(byte_6FB7897C + a1 * 0xc) != 0))
		{
			if (a4 == nullptr)
			{
				return 0;
			}
			*a4 = 0xf8a;
			return 0;
		}
	default:
		goto switchD_6fad4d78_default;
	}
	if (iVar2 == 0)
	{
		if (a4 == nullptr)
		{
			return 0;
		}
		*a4 = 0xf89;
		return 0;
	}
switchD_6fad4d78_default:
	sVar6 = (short)a3;
	if ((sVar6 == 0x2c) && ((&ptr_6FB78978)[a1 * 3] != nullptr))
	{
		if (a4 != nullptr)
		{
			*a4 = 0xf8b;
			return 0;
		}
	}
	else
	{
		iVar2 = 0x72;
		iVar5 = 0;
		psVar3 = (short*)&dword_6FBB2D3C;
		do
		{
			if (*psVar3 == sVar6)
			{
				*(uint16_t*)((int)&dword_6FBB2D3C + iVar5 * 10) = 0xffff;
				iVar2 = iVar5;
				break;
			}
			psVar3 = psVar3 + 5;
			iVar5 = iVar5 + 1;
		} while ((int)psVar3 < (int)&dword_6FBB31B0);
		iVar5 = 0;
		piVar4 = (int*)((int)&dword_6FBB2D3C + 2);
		do
		{
			if ((*(int*)((int)piVar4 + -6) == a1) && (*piVar4 == a2))
			{
				*(short*)((int)&dword_6FBB2D3C + iVar5 * 10) = sVar6;
				return 1;
			}
			piVar4 = (int*)((int)piVar4 + 10);
			iVar5 = iVar5 + 1;
		} while ((int)piVar4 < (int)&tbl_6FBB31B2);
		if (iVar2 != 0x72)
		{
			*(short*)((int)&dword_6FBB2D3C + iVar2 * 10) = sVar6;
		}
	}
	return 0;
}

//D2Client.0x6FAD4E90
void __cdecl sub_6FAD4E90()
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t* puVar3;

	puVar2 = &dword_6FBB2D38;
	puVar3 = &dword_6FBB31B0;
	for (iVar1 = 0x11d; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
	sub_6FAD4470();
}

//D2Client.0x6FAD4EB0
void __cdecl sub_6FAD4EB0()
{
	sub_6FAD4890();
	sub_6FAD4470();
}

//D2Client.0x6FAD4EC0
void __cdecl sub_6FAD4EC0()
{
	int iVar1;
	uint32_t* puVar2;
	uint32_t* puVar3;

	puVar2 = &dword_6FBB31B0;
	puVar3 = &dword_6FBB2D38;
	for (iVar1 = 0x11d; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar3 = *puVar2;
		puVar2 = puVar2 + 1;
		puVar3 = puVar3 + 1;
	}
	sub_6FAD4470();
}

//D2Client.0x6FAD4EE0
void __fastcall sub_6FAD4EE0(int a1, int a2)
{
	int* piVar1;

	piVar1 = (int*)((int)&dword_6FBB2D3C + 2);
	do
	{
		if ((a1 == *(int*)((int)piVar1 + -6)) && (a2 == *piVar1))
		{
			*(uint16_t*)((int)piVar1 + -2) = 0xffff;
		}
		piVar1 = (int*)((int)piVar1 + 10);
	} while ((int)piVar1 < (int)&tbl_6FBB31B2);
}

//D2Client.0x6FAD4F00
bool __fastcall sub_6FAD4F00(int a1, int a2)
{
	int* piVar1;
	int iVar2;

	iVar2 = 0;
	piVar1 = (int*)((int)&dword_6FBB2D3C + 2);
	while ((*(int*)((int)piVar1 + -6) != a1 || (*piVar1 != a2)))
	{
		piVar1 = (int*)((int)piVar1 + 10);
		iVar2 = iVar2 + 1;
		if ((int)&tbl_6FBB31B1 < (int)piVar1)
		{
			return false;
		}
	}
	return *(short*)((int)&dword_6FBB2D3C + iVar2 * 10) != -1;
}

//D2Client.0x6FAD4F50
Unicode* __fastcall sub_6FAD4F50(int a1, int a2)
{
	uint16_t uVar1;
	int* piVar2;
	Unicode* pUVar3;
	int iVar4;

	iVar4 = 0;
	piVar2 = (int*)((int)&dword_6FBB2D3C + 2);
	while ((*(int*)((int)piVar2 + -6) != a1 || (*piVar2 != a2)))
	{
		piVar2 = (int*)((int)piVar2 + 10);
		iVar4 = iVar4 + 1;
		if ((int)&tbl_6FBB31B1 < (int)piVar2)
		{
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb2));
			return pUVar3;
		}
	}
	uVar1 = *(uint16_t*)((int)&dword_6FBB2D3C + iVar4 * 10);
	if (uVar1 == 0xffff)
	{
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb2));
		return pUVar3;
	}
	if (0xdf < uVar1)
	{
		switch (uVar1)
		{
		case 0x100:
			goto switchD_6fad4fb0_caseD_100;
		case 0x101:
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb7));
			return pUVar3;
		case 0x102:
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb8));
			return pUVar3;
		case 0x103:
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb9));
			return pUVar3;
		case 0x104:
			pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeba));
			return pUVar3;
		default:
		switchD_6fad4fb0_default:
			byte_6FBB2D28 = 0;
			byte_6FBB2D24 = uVar1 & 0xffff00ff;
			return (Unicode*)&byte_6FBB2D24;
		}
	}
	switch (uVar1)
	{
	case 1:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb3));
		return pUVar3;
	case 2:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb4));
		return pUVar3;
	case 3:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb5));
		return pUVar3;
	case 4:
	switchD_6fad4fb0_caseD_100:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeb6));
		return pUVar3;
	default:
		goto switchD_6fad4fb0_default;
	case 8:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xece));
		return pUVar3;
	case 9:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xecf));
		return pUVar3;
	case 0xc:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed0));
		return pUVar3;
	case 0xd:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed1));
		return pUVar3;
	case 0x10:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed2));
		return pUVar3;
	case 0x11:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed3));
		return pUVar3;
	case 0x12:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed4));
		return pUVar3;
	case 0x13:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed5));
		return pUVar3;
	case 0x14:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed6));
		return pUVar3;
	case 0x15:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xebb));
		return pUVar3;
	case 0x17:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xebc));
		return pUVar3;
	case 0x18:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xebd));
		return pUVar3;
	case 0x19:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xebe));
		return pUVar3;
	case 0x1b:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xebf));
		return pUVar3;
	case 0x1c:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec0));
		return pUVar3;
	case 0x1d:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec1));
		return pUVar3;
	case 0x1e:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec2));
		return pUVar3;
	case 0x1f:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec3));
		return pUVar3;
	case 0x20:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed7));
		return pUVar3;
	case 0x21:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed8));
		return pUVar3;
	case 0x22:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xed9));
		return pUVar3;
	case 0x23:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeda));
		return pUVar3;
	case 0x24:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xedb));
		return pUVar3;
	case 0x25:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec4));
		return pUVar3;
	case 0x26:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec5));
		return pUVar3;
	case 0x27:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec6));
		return pUVar3;
	case 0x28:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec7));
		return pUVar3;
	case 0x29:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec8));
		return pUVar3;
	case 0x2a:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xedc));
		return pUVar3;
	case 0x2b:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xec9));
		return pUVar3;
	case 0x2c:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xedd));
		return pUVar3;
	case 0x2d:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xede));
		return pUVar3;
	case 0x2e:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xedf));
		return pUVar3;
	case 0x2f:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee0));
		return pUVar3;
	case 0x5b:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeca));
		return pUVar3;
	case 0x5c:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xecb));
		return pUVar3;
	case 0x5d:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xecc));
		return pUVar3;
	case 0x60:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee1));
		return pUVar3;
	case 0x61:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee2));
		return pUVar3;
	case 0x62:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee3));
		return pUVar3;
	case 99:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee4));
		return pUVar3;
	case 100:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee5));
		return pUVar3;
	case 0x65:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee6));
		return pUVar3;
	case 0x66:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee7));
		return pUVar3;
	case 0x67:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee8));
		return pUVar3;
	case 0x68:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xee9));
		return pUVar3;
	case 0x69:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeea));
		return pUVar3;
	case 0x6a:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeeb));
		return pUVar3;
	case 0x6b:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeec));
		return pUVar3;
	case 0x6c:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeed));
		return pUVar3;
	case 0x6d:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeee));
		return pUVar3;
	case 0x6e:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeef));
		return pUVar3;
	case 0x6f:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef0));
		return pUVar3;
	case 0x70:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef1));
		return pUVar3;
	case 0x71:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef2));
		return pUVar3;
	case 0x72:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef3));
		return pUVar3;
	case 0x73:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef4));
		return pUVar3;
	case 0x74:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef5));
		return pUVar3;
	case 0x75:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef6));
		return pUVar3;
	case 0x76:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef7));
		return pUVar3;
	case 0x77:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef8));
		return pUVar3;
	case 0x78:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xef9));
		return pUVar3;
	case 0x79:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xefa));
		return pUVar3;
	case 0x7a:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xefb));
		return pUVar3;
	case 0x7b:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xefc));
		return pUVar3;
	case 0x7c:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xefd));
		return pUVar3;
	case 0x7d:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xefe));
		return pUVar3;
	case 0x7e:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xeff));
		return pUVar3;
	case 0x7f:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf00));
		return pUVar3;
	case 0x80:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf01));
		return pUVar3;
	case 0x81:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf02));
		return pUVar3;
	case 0x82:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf03));
		return pUVar3;
	case 0x83:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf04));
		return pUVar3;
	case 0x84:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf05));
		return pUVar3;
	case 0x85:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf06));
		return pUVar3;
	case 0x86:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf07));
		return pUVar3;
	case 0x87:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf08));
		return pUVar3;
	case 0x90:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xecd));
		return pUVar3;
	case 0x91:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf09));
		return pUVar3;
	case 0xba:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0a));
		return pUVar3;
	case 0xbb:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0b));
		return pUVar3;
	case 0xbc:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0c));
		return pUVar3;
	case 0xbd:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0d));
		return pUVar3;
	case 0xbe:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0e));
		return pUVar3;
	case 0xbf:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf0f));
		return pUVar3;
	case 0xc0:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf10));
		return pUVar3;
	case 0xdb:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf11));
		return pUVar3;
	case 0xdc:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf12));
		return pUVar3;
	case 0xdd:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf13));
		return pUVar3;
	case 0xde:
		pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf14));
		return pUVar3;
	}
}

//D2Client.0x6FAD56B0
Unicode* __fastcall sub_6FAD56B0(int a1, int a2)
{
	uint16_t uVar1;
	int* piVar2;
	Unicode* pUVar3;
	int iVar4;

	iVar4 = 0;
	piVar2 = (int*)((int)&dword_6FBB2D3C + 2);
	while ((*(int*)((int)piVar2 + -6) != a1 || (*piVar2 != a2)))
	{
		piVar2 = (int*)((int)piVar2 + 10);
		iVar4 = iVar4 + 1;
		if ((int)&tbl_6FBB31B1 < (int)piVar2)
		{
			uVar1 = 0xffff;
		LAB_6fad56d4:
			switch (uVar1)
			{
			case 8:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf2c));
				return pUVar3;
			default:
				pUVar3 = sub_6FAD4F50(a1, a2);
				return pUVar3;
			case 0x10:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf2f));
				return pUVar3;
			case 0x11:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf30));
				return pUVar3;
			case 0x1b:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf1e));
				return pUVar3;
			case 0x21:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf34));
				return pUVar3;
			case 0x22:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf35));
				return pUVar3;
			case 0x2c:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf37));
				return pUVar3;
			case 0x2d:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf38));
				return pUVar3;
			case 0x2e:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf39));
				return pUVar3;
			case 0x60:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf3b));
				return pUVar3;
			case 0x61:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf3c));
				return pUVar3;
			case 0x62:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf3d));
				return pUVar3;
			case 99:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf3e));
				return pUVar3;
			case 100:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf3f));
				return pUVar3;
			case 0x65:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf40));
				return pUVar3;
			case 0x66:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf41));
				return pUVar3;
			case 0x67:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf42));
				return pUVar3;
			case 0x68:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf43));
				return pUVar3;
			case 0x69:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf44));
				return pUVar3;
			case 0x6a:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf45));
				return pUVar3;
			case 0x6b:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf46));
				return pUVar3;
			case 0x6c:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf48));
				return pUVar3;
			case 0x6d:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf47));
				return pUVar3;
			case 0x6f:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf49));
				return pUVar3;
			case 0x90:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf2b));
				return pUVar3;
			case 0x91:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf4a));
				return pUVar3;
			case 0x100:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf15));
				return pUVar3;
			case 0x101:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf16));
				return pUVar3;
			case 0x102:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf17));
				return pUVar3;
			case 0x103:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf18));
				return pUVar3;
			case 0x104:
				pUVar3 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xf19));
				return pUVar3;
			}
		}
	}
	uVar1 = *(uint16_t*)((int)&dword_6FBB2D3C + iVar4 * 10);
	goto LAB_6fad56d4;
}

//D2Client.0x6FAD5A00
void __cdecl sub_6FAD5A00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	SHORT SVar2;
	BOOL BVar3;
	int* piVar4;
	int iVar5;

	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		iVar5 = 0;
		piVar4 = (int*)(&dword_6FBB2D38);
		while (((((uint32_t) * (uint16_t*)(piVar4 + 1) != pSMSGHANDLER_PARAMS->wParam || (iVar1 = *piVar4, iVar1 == 0xffff)) || (0x38 < iVar1)) ||
		        ((0xdf < iVar1 || ((&ptr_6FB78978)[iVar1 * 3] == nullptr)))))
		{
			piVar4 = (int*)((int)piVar4 + 10);
			iVar5 = iVar5 + 1;
			if ((int)&tbl_6FBB31AB < (int)piVar4)
			{
				return;
			}
		}
		iVar5 = iVar5 * 10;
		if ((*(short*)((int)&dword_6FBB2D3C + iVar5) == 0x73) && (SVar2 = GetKeyState(0x12), SVar2 < 0))
		{
			return;
		}
		if ((dword_6FBB3630 != 2) ||
		    (*(int*)(byte_6FB78980 + *(int*)((int)&dword_6FBB2D38 + iVar5) * 0xc) != 0))
		{
			BVar3 = IsBadCodePtr((FARPROC)(&ptr_6FB78978)[*(int*)((int)&dword_6FBB2D38 + iVar5) * 3]);
			D2_ASSERT(!BVar3);
			(*(code*)(&ptr_6FB78978)[*(int*)((int)&dword_6FBB2D38 + iVar5) * 3])();
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		}
	}
}

//D2Client.0x6FAD5B00
void __cdecl sub_6FAD5B00(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	BOOL BVar2;
	int* piVar3;
	int iVar4;

	iVar4 = 0;
	piVar3 = (int*)(&dword_6FBB2D38);
	while (((((uint32_t) * (uint16_t*)(piVar3 + 1) != pSMSGHANDLER_PARAMS->wParam || (iVar1 = *piVar3, iVar1 == 0xffff)) || (0x38 < iVar1)) || ((0xdf < iVar1 || (*(int*)(byte_6FB7897C + iVar1 * 0xc) == 0)))))
	{
		piVar3 = (int*)((int)piVar3 + 10);
		iVar4 = iVar4 + 1;
		if ((int)&tbl_6FBB31AB < (int)piVar3)
		{
			return;
		}
	}
	if ((dword_6FBB3630 != 2) ||
	    (*(int*)(byte_6FB78980 + *(int*)((int)&dword_6FBB2D38 + iVar4 * 10) * 0xc) != 0))
	{
		BVar2 = IsBadCodePtr(*(FARPROC*)(byte_6FB7897C + *(int*)((int)&dword_6FBB2D38 + iVar4 * 10) * 0xc));
		D2_ASSERT(!BVar2);
		(**(code**)(byte_6FB7897C + *(int*)((int)&dword_6FBB2D38 + iVar4 * 10) * 0xc))();
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAD5BE0
void __fastcall sub_6FAD5BE0(int a1, int a2)
{
	HWND__* pHVar1;
	uint32_t uVar2;

	dword_6FBB3630 = a1;
	if (a1 == 0)
	{
		if (dword_6FBB3634 == 1)
		{
			uVar2 = 4;
			dword_6FBB3634 = 0;
			pHVar1 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78C24), uVar2);
			if ((a2 != 0) && (dword_6FBB3638 == 0))
			{
				uVar2 = 2;
				pHVar1 = WINDOW_GetWindow();
				WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78C54), uVar2);
				dword_6FBB3638 = 1;
			}
		}
	}
	else if (dword_6FBB3634 == 0)
	{
		dword_6FBB3634 = 1;
		if ((a2 != 0) && (dword_6FBB3638 != 0))
		{
			uVar2 = 2;
			pHVar1 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78C54), uVar2);
			dword_6FBB3638 = 0;
		}
		uVar2 = 4;
		pHVar1 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78C24), uVar2);
		return;
	}
}

//D2Client.0x6FAD5CA0
void __cdecl sub_6FAD5CA0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	int iVar2;
	DWORD DVar3;
	int iVar4;
	int iVar5;

	iVar2 = dword_6FBB3644;
	DVar3 = GetTickCount();
	if (*(int*)iVar2 + 0x50U <= DVar3)
	{
		for (piVar1 = *(int**)(iVar2 + 0xb08); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
		{
			if (((int*)*piVar1 != nullptr) &&
			    (iVar4 = (**(code**)(*(int*)*piVar1 + 0x14))(pSMSGHANDLER_PARAMS), iVar4 == 1))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
		}
		iVar4 = *(int*)(iVar2 + 0x44);
		iVar5 = sub_6FAD5D30(iVar2, (int)pSMSGHANDLER_PARAMS);
		*(int*)(iVar2 + 0x44) = iVar5;
		*(int*)(iVar2 + 0x48) = iVar5;
		if ((iVar5 != iVar4) && (iVar5 != -1))
		{
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
		}
	}
}

//D2Client.0x6FAD5D30
int __fastcall sub_6FAD5D30(int a1, int a2)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int local_4;

	iVar2 = 0;
	if (a1 != 0)
	{
		local_4 = 0;
		if (0 < *(int*)(a1 + 0x50))
		{
			piVar1 = (int*)(a1 + 0x158);
			do
			{
				if ((((piVar1[7] == 1) &&
				         (*(int*)(a1 + 0x2c) + 0xf < (int)(uint32_t) * (uint16_t*)(a2 + 0xc))) &&
				        ((int)(uint32_t) * (uint16_t*)(a2 + 0xc) <
				            *(int*)(a1 + 0x34) + -0xf + *(int*)(a1 + 0x2c))) &&
				    ((iVar3 = *piVar1 + *(int*)(a1 + 0x30) + iVar2,
				        iVar3 + -0xb < (int)(uint32_t) * (uint16_t*)(a2 + 0xe) &&
				            ((int)(uint32_t) * (uint16_t*)(a2 + 0xe) < iVar3 + 4))))
				{
					return local_4;
				}
				iVar2 = iVar2 + *piVar1;
				local_4 = local_4 + 1;
				piVar1 = piVar1 + 0x44;
			} while (local_4 < *(int*)(a1 + 0x50));
		}
	}
	return -1;
}

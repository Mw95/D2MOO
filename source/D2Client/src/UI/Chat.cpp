#include "UI/Chat.h"

#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Gfx.h"
#include "Game/Env.h"
#include "Game/Game.h"
#include "Game/Msg.h"
#include "Game/Roster.h"
#include "Game/RosterPets.h"
#include "Game/Select.h"
#include "Skills/SkillsPal.h"
#include "Sound/SoundInst.h"
#include "UI/Char.h"
#include "UI/EditBox.h"
#include "UI/Inv.h"
#include "UI/NpcMenu.h"
#include "UI/QuestLog.h"
#include "UI/Restart.h"
#include "UI/SkillsTree.h"
#include "UI/SpellSel.h"
#include "UI/Text.h"
#include "UI/UI.h"
#include "Unit/CUnit.h"
#include "Unit/UnitMode.h"

//D2Client.0x6FB783B0
uint32_t unk_6FB783B0[1] = { 0x2F };

//D2Client.0x6FB782E8
int32_t dword_6FB782E8 = 7;
//D2Client.0x6FB782EC
int32_t dword_6FB782EC = 7;
//D2Client.0x6FB782F0
uint32_t tbl_6FB782F0[12] = {0, 0x102, (uint32_t)sub_6FAD2890, 3, 0x26, (uint32_t)sub_6FAD2760, 3, 0x28, (uint32_t)sub_6FAD2760, 0, 0x201, (uint32_t)sub_6FAD2720};
//D2Client.0x6FB78320
uint32_t tbl_6FB78320[21] = {0, 0x282, (uint32_t)sub_6FAD1A70, 0, 0x10F, (uint32_t)sub_6FAD1790, 0, 0x10D, (uint32_t)sub_6FAD19B0, 0, 0x10E, (uint32_t)sub_6FAD1A20, 0, 0x284, (uint32_t)sub_6FAD1D80, 0, 0x285, (uint32_t)sub_6FAD1D80, 0, 0x283, (uint32_t)sub_6FAD1D80};
//D2Client.0x6FB78374
int32_t dword_6FB78374 = 1;
//D2Client.0x6FB78378
uint32_t dword_6FB78378 = 0x1F4;
//D2Client.0x6FB7837C
uint8_t* ptr_6FB7837C = (uint8_t*)&unk_6FB783B0;
//D2Client.0x6FB78380
uint16_t word_6FB78380 = 3;
//D2Client.0x6FB78382
uint32_t dword_6FB78382;
//D2Client.0x6FB783A5
uint8_t tbl_6FB783A5[1];
//D2Client.0x6FB7847C
uint16_t word_6FB7847C = 0x20;
//D2Client.0x6FBB1A58
uint16_t word_6FBB1A58;
//D2Client.0x6FBB1CA0
int32_t dword_6FBB1CA0;
//D2Client.0x6FBB1CA8
uint32_t dword_6FBB1CA8;
//D2Client.0x6FBB2CF8
uint8_t byte_6FBB2CF8;
//D2Client.0x6FBB2CFC
uint8_t byte_6FBB2CFC;
//D2Client.0x6FBB2D00
int16_t word_6FBB2D00;
//D2Client.0x6FBB2D04
uint32_t dword_6FBB2D04;
//D2Client.0x6FBB2D08
int32_t dword_6FBB2D08;
//D2Client.0x6FBB2D0C
uint32_t dword_6FBB2D0C;
//D2Client.0x6FBB2D10
uint8_t* ptr_6FBB2D10;
//D2Client.0x6FBB2D14
char byte_6FBB2D14;
//D2Client.0x6FBB2D18
DWORD dword_6FBB2D18;
//D2Client.0x6FBB2D24
uint8_t byte_6FBB2D24;

//D2Client.0x6FAD1A70
void __cdecl sub_6FAD1A70(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	SMSGHANDLER_PARAMS* pSVar1;
	HWND__* pHVar2;
	HIMC pHVar3;
	BOOL BVar4;
	DWORD DVar5;
	DWORD DVar6;
	HKL pHVar7;
	DWORD DStack_8;
	DWORD DStack_4;

	pSVar1 = pSMSGHANDLER_PARAMS;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	pHVar2 = WINDOW_GetWindow();
	pHVar3 = ImmGetContext((HWND)pHVar2);
	if (pHVar3 == (HIMC)0x0)
	{
		return;
	}
	switch (pSVar1->wParam)
	{
	case 2:
		if (byte_6FBB2CFC != 9)
			goto switchD_6fad1ab2_caseD_7;
		pHVar7 = GetKeyboardLayout(0);
		BVar4 = ImmIsIME(pHVar7);
		dword_6FBB2D0C = (-(uint32_t)(BVar4 != 0) & 0xfffffffc) + 4;
		break;
	case 3:
		if (byte_6FBB2CFC != 9)
			goto switchD_6fad1ab2_caseD_7;
		goto LAB_6fad1c9e;
	case 4:
		if (byte_6FBB2CFC == 9)
		{
			if (ptr_6FBB2D10 != nullptr)
			{
				D2_FREE(ptr_6FBB2D10);
				ptr_6FBB2D10 = nullptr;
			}
			pSVar1->bUseResult = 1;
			pSVar1->lResult = 0;
		}
		if (byte_6FBB2CFC != 8)
			goto switchD_6fad1ab2_caseD_7;
		if (ptr_6FBB2D10 != nullptr)
		{
			D2_FREE(ptr_6FBB2D10);
			ptr_6FBB2D10 = nullptr;
		}
		break;
	case 5:
		if (byte_6FBB2CFC == 9)
		{
			DVar5 = ImmGetCandidateListCountA(pHVar3, &DStack_4);
			DVar6 = ImmGetCandidateListA(pHVar3, 0, (LPCANDIDATELIST)0x0, 0);
			if ((DVar6 != 0) && (DVar5 != 0))
			{
				if (ptr_6FBB2D10 != nullptr)
				{
					D2_FREE(ptr_6FBB2D10);
				}
				ptr_6FBB2D10 = (uint8_t*)(D2_ALLOC(DVar5));
				ImmGetCandidateListA(pHVar3, 0, (LPCANDIDATELIST)ptr_6FBB2D10, DVar5);
				if ((*(int*)((int)ptr_6FBB2D10 + 4) == 2) && (*(int*)((int)ptr_6FBB2D10 + 8) == 1))
				{
					D2_FREE(ptr_6FBB2D10);
					ptr_6FBB2D10 = nullptr;
				}
			}
			pSVar1->bUseResult = 1;
			pSVar1->lResult = 0;
		}
		if (byte_6FBB2CFC != 8)
			goto switchD_6fad1ab2_caseD_7;
	LAB_6fad1c9e:
		DVar5 = ImmGetCandidateListCountA(pHVar3, &DStack_4);
		DVar6 = ImmGetCandidateListA(pHVar3, 0, (LPCANDIDATELIST)0x0, 0);
		if ((DVar6 != 0) && (DVar5 != 0))
		{
			if (ptr_6FBB2D10 != nullptr)
			{
				D2_FREE(ptr_6FBB2D10);
			}
			ptr_6FBB2D10 = (uint8_t*)(D2_ALLOC(DVar5));
			ImmGetCandidateListA(pHVar3, 0, (LPCANDIDATELIST)ptr_6FBB2D10, DVar5);
			if ((*(int*)((int)ptr_6FBB2D10 + 4) == 2) && (*(int*)((int)ptr_6FBB2D10 + 8) == 1))
			{
				D2_FREE(ptr_6FBB2D10);
				ptr_6FBB2D10 = nullptr;
			}
		}
		pSVar1->bUseResult = 1;
		goto LAB_6fad1d49;
	case 6:
		ImmGetConversionStatus(pHVar3, (LPDWORD)&pSMSGHANDLER_PARAMS, &DStack_8);
		if ((byte_6FBB2CFC != 7) && (byte_6FBB2CFC != 0xc))
			goto switchD_6fad1ab2_caseD_7;
		if (((uint32_t)pSMSGHANDLER_PARAMS & 1) != 0)
		{
			dword_6FBB2D0C = 1;
			byte_6FBB2CF8 = 1;
			goto switchD_6fad1ab2_caseD_7;
		}
		goto LAB_6fad1aef;
	default:
		goto switchD_6fad1ab2_caseD_7;
	case 8:
		if (byte_6FBB2CFC == 6)
		{
			BVar4 = ImmGetOpenStatus(pHVar3);
			if (BVar4 != 0)
			{
				byte_6FBB2CF8 = 1;
				dword_6FBB2D0C = 3;
				goto switchD_6fad1ab2_caseD_7;
			}
		}
		else if (byte_6FBB2CFC == 8)
		{
			BVar4 = ImmGetOpenStatus(pHVar3);
			if (BVar4 != 0)
			{
				byte_6FBB2CF8 = 1;
				dword_6FBB2D0C = 5;
				goto switchD_6fad1ab2_caseD_7;
			}
		}
		else
		{
			if (byte_6FBB2CFC != 9)
				goto switchD_6fad1ab2_caseD_7;
			BVar4 = ImmGetOpenStatus(pHVar3);
			if (BVar4 != 0)
			{
				byte_6FBB2CF8 = 1;
				dword_6FBB2D0C = 4;
				goto switchD_6fad1ab2_caseD_7;
			}
		}
	LAB_6fad1aef:
		byte_6FBB2CF8 = 0;
		dword_6FBB2D0C = 0;
		goto switchD_6fad1ab2_caseD_7;
	}
	pSVar1->bUseResult = 1;
LAB_6fad1d49:
	pSVar1->lResult = 0;
switchD_6fad1ab2_caseD_7:
	pHVar2 = WINDOW_GetWindow();
	ImmReleaseContext((HWND)pHVar2, pHVar3);
}

//D2Client.0x6FAD1D80
void __cdecl sub_6FAD1D80(int a1)
{
	*(uint32_t*)(a1 + 0x18) = 1;
	*(uint32_t*)(a1 + 0x1c) = 0;
}

//D2Client.0x6FAD1DA0
void __cdecl sub_6FAD1DA0()
{
	LANGID LVar1;
	HWND__* pHVar2;
	HKL pHVar3;
	BOOL BVar4;
	HIMC pHVar5;
	DWORD DVar6;
	uint32_t uVar7;
	DWORD DStack_8;
	uint8_t abStack_4[4];

	uVar7 = 4;
	pHVar2 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB782F0), uVar7);
	byte_6FBB2CFC = STRTABLE_GetLanguage();
	if ((((byte_6FBB2CFC != LANGUAGE_JAPANESE) && (byte_6FBB2CFC != LANGUAGE_CHINESETWN)) &&
	        (byte_6FBB2CFC != LANGUAGE_CHINESESIN)) &&
	    ((byte_6FBB2CFC != LANGUAGE_KOREAN && (byte_6FBB2CFC != LANGUAGE_ENGLISHKOR))))
	{
		return;
	}
	byte_6FBB2D14 = '\0';
	if (byte_6FBB2CFC == LANGUAGE_CHINESETWN)
	{
		LVar1 = GetSystemDefaultLangID();
		if ((LVar1 != 0x404) && (LVar1 != 0xc04))
		{
			return;
		}
	}
	else if (byte_6FBB2CFC == LANGUAGE_CHINESESIN)
	{
		LVar1 = GetSystemDefaultLangID();
		if ((LVar1 != 0x804) && (LVar1 != 0x1004))
		{
			return;
		}
	}
	else
	{
		pHVar3 = GetKeyboardLayout(0);
		BVar4 = ImmIsIME(pHVar3);
		if (BVar4 == 0)
		{
			return;
		}
	}
	LVar1 = GetSystemDefaultLangID();
	pHVar2 = WINDOW_GetWindow();
	pHVar5 = ImmGetContext((HWND)pHVar2);
	if (pHVar5 == (HIMC)0x0)
	{
		return;
	}
	byte_6FBB2CB8 = 0;
	byte_6FBB1C60 = 0;
	switch (byte_6FBB2CFC)
	{
	case LANGUAGE_JAPANESE:
		if (LVar1 == 0x411)
		{
			uVar7 = 7;
			byte_6FBB2D14 = '\x01';
			pHVar2 = WINDOW_GetWindow();
			WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78320), uVar7);
			BVar4 = ImmSetOpenStatus(pHVar5, 1);
			if (BVar4 == 0)
			{
				byte_6FBB2CF8 = 0;
				dword_6FBB2D0C = 0;
				pHVar2 = WINDOW_GetWindow();
				ImmReleaseContext((HWND)pHVar2, pHVar5);
				return;
			}
			byte_6FBB2CF8 = 1;
			dword_6FBB2D0C = 3;
			pHVar2 = WINDOW_GetWindow();
			ImmReleaseContext((HWND)pHVar2, pHVar5);
			return;
		}
		goto switchD_6fad1e70_caseD_a;
	case LANGUAGE_KOREAN:
	case LANGUAGE_ENGLISHKOR:
		if ((LVar1 != 0x412) && (LVar1 != 0x812))
			goto switchD_6fad1e70_caseD_a;
		ImmSetOpenStatus(pHVar5, 1);
		ImmGetConversionStatus(pHVar5, (LPDWORD)abStack_4, &DStack_8);
		ImmSetConversionStatus(pHVar5, 1, DStack_8);
		ImmGetConversionStatus(pHVar5, (LPDWORD)abStack_4, &DStack_8);
		if ((abStack_4[0] & 1) == 0)
		{
			dword_6FBB2D0C = 0;
			byte_6FBB2D14 = '\x01';
		}
		else
		{
			dword_6FBB2D0C = 1;
			byte_6FBB2CF8 = 1;
			byte_6FBB2D14 = '\x01';
		}
		break;
	case LANGUAGE_CHINESESIN:
		byte_6FBB2CF8 = 0;
		byte_6FBB2D14 = '\x01';
		pHVar3 = GetKeyboardLayout(0);
		BVar4 = ImmIsIME(pHVar3);
		if (BVar4 == 0)
		{
			DVar6 = 0x10;
			pHVar2 = WINDOW_GetWindow();
			ImmSimulateHotKey((HWND)pHVar2, DVar6);
		}
		ImmSetOpenStatus(pHVar5, 1);
		dword_6FBB2D0C = 5;
		break;
	case LANGUAGE_CHINESETWN:
		byte_6FBB2CF8 = 0;
		byte_6FBB2D14 = '\x01';
		pHVar3 = GetKeyboardLayout(0);
		BVar4 = ImmIsIME(pHVar3);
		if (BVar4 == 0)
		{
			DVar6 = 0x70;
			pHVar2 = WINDOW_GetWindow();
			ImmSimulateHotKey((HWND)pHVar2, DVar6);
		}
		ImmSetOpenStatus(pHVar5, 1);
		dword_6FBB2D0C = 4;
		break;
	default:
		goto switchD_6fad1e70_caseD_a;
	}
	uVar7 = 7;
	pHVar2 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar2, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78320), uVar7);
switchD_6fad1e70_caseD_a:
	pHVar2 = WINDOW_GetWindow();
	ImmReleaseContext((HWND)pHVar2, pHVar5);
}

//D2Client.0x6FAD2030
void __cdecl sub_6FAD2030()
{
	HWND__* pHVar1;
	HIMC pHVar2;
	uint32_t uVar3;
	DWORD DStack_8;
	DWORD DStack_4;

	uVar3 = 4;
	pHVar1 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB782F0), uVar3);
	if (byte_6FBB2D14 != '\0')
	{
		uVar3 = 7;
		pHVar1 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar1, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78320), uVar3);
		pHVar1 = WINDOW_GetWindow();
		pHVar2 = ImmGetContext((HWND)pHVar1);
		if (pHVar2 != (HIMC)0x0)
		{
			ImmSetOpenStatus(pHVar2, 0);
			if ((byte_6FBB2CFC == 7) || (byte_6FBB2CFC == 0xc))
			{
				ImmGetConversionStatus(pHVar2, &DStack_4, &DStack_8);
				ImmSetConversionStatus(pHVar2, 0, DStack_8);
			}
			pHVar1 = WINDOW_GetWindow();
			ImmReleaseContext((HWND)pHVar1, pHVar2);
		}
		byte_6FBB1C60 = 0;
		byte_6FBB2CB8 = 0;
		if (ptr_6FBB2D10 != nullptr)
		{
			D2_FREE(ptr_6FBB2D10);
			ptr_6FBB2D10 = nullptr;
		}
	}
}

//D2Client.0x6FAD2100
void __cdecl sub_6FAD2100()
{
	D2SplittedTextStrc* pDVar1;
	void* pvVar2;
	D2SplittedTextStrc* pSplitText;
	int iVar3;
	Unicode* pUVar4;
	DWORD DVar5;
	D2SplittedTextStrc* pDVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int iStack_284;
	int iStack_280;
	int* piStack_274;
	int iStack_270;
	Font FStack_26c;
	Unicode UStack_268;
	uint16_t uStack_266;
	uint16_t uStack_264;
	uint16_t uStack_262;
	char acStack_240[20];
	Unicode aUStack_22c[20];
	Unicode aUStack_204[258];

	FStack_26c = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
	if (byte_6FBB2D14 == '\0')
		goto switchD_6fad214a_default;
	pUVar4 = &UStack_268;
	iVar7 = 0x14;
	do
	{
		pUVar4 = pUVar4 + 1;
		iVar7 = iVar7 + -1;
	} while (iVar7 != 0);
	switch (dword_6FBB2D0C)
	{
	case 0:
		Unicode::win2Unicode(&UStack_268, "Alphanumeric", 0x14);
		iVar7 = gnScreenHeight + -0x80;
		break;
	case 1:
		iVar7 = gnScreenHeight + -0x80;
		UStack_268.ch = 0xd55c;
		uStack_266 = 0xae00;
		uStack_264 = 0;
		break;
	case 2:
	case 3:
		iVar7 = gnScreenHeight + -0x80;
		UStack_268.ch = 0x65e5;
		uStack_266 = 0x672c;
		uStack_264 = 0x8a9e;
		uStack_262 = 0;
		break;
	case 4:
	case 5:
		uStack_266 = 0x6f22;
		uStack_264 = 0;
		D2Win_10117_DrawText(&UStack_268, 0x14, gnScreenHeight + -0x80, 0, 0);
		pvVar2 = ptr_6FBB2D10;
		if (ptr_6FBB2D10 != nullptr)
		{
			if (*(int*)((int)ptr_6FBB2D10 + 0x14) == 0)
			{
				iStack_284 = *(int*)((int)ptr_6FBB2D10 + 8);
				iStack_280 = 0;
				if (0x13 < iStack_284)
				{
					iStack_284 = 0x14;
				}
			}
			else
			{
				iStack_280 = *(int*)((int)ptr_6FBB2D10 + 0x10);
				iStack_284 = *(int*)((int)ptr_6FBB2D10 + 0x14) + iStack_280;
				if (*(int*)((int)ptr_6FBB2D10 + 8) < iStack_284)
				{
					iStack_284 = *(int*)((int)ptr_6FBB2D10 + 8);
				}
			}
			iStack_270 = 0;
			iVar7 = D2Win_10125();
			if (iStack_280 < iStack_284)
			{
				piStack_274 = (int*)((int)pvVar2 + iStack_280 * 4 + 0x18);
				iVar9 = 0;
				do
				{
					pUVar4 = aUStack_22c;
					iVar3 = *piStack_274;
					iVar8 = 0x14;
					do
					{
						pUVar4 = pUVar4 + 1;
						iVar8 = iVar8 + -1;
					} while (iVar8 != 0);
					iStack_270 = iStack_270 + 1;
					iVar9 = iVar9 + iVar7;
					sprintf(acStack_240, "%d: ", iStack_270);
					Unicode::win2Unicode(aUStack_22c, acStack_240, 0x14);
					D2Win_10117_DrawText(aUStack_22c, 0x14, gnScreenHeight + -0x170 + iVar9, 0, 0);
					iVar3 = MultiByteToWideChar(0, 1, (LPCSTR)(iVar3 + (int)pvVar2), -1, (LPWSTR)aUStack_204, 0x101);
					if (iVar3 != 0)
					{
						D2Win_10117_DrawText(aUStack_204, 0x1e, gnScreenHeight + -0x170 + iVar9, 0, 0);
					}
					if (0x118 < iVar9)
						break;
					iStack_280 = iStack_280 + 1;
					piStack_274 = piStack_274 + 1;
				} while (iStack_280 < iStack_284);
			}
		}
	default:
		goto switchD_6fad214a_default;
	}
	D2Win_10117_DrawText(&UStack_268, 0x14, iVar7, 0, 0);
switchD_6fad214a_default:
	dword_6FBB2D08 = dword_6FBB2D08 + 1;
	sub_6FB5B0F0(0x7f, gnScreenHeight + -0x67, gnScreenWidth + -0xff, 0x2f, 0, (DrawMode)(1));
	iStack_280 = 0;
	iVar7 = sub_6FAABF20();
	if (iVar7 != 0)
	{
		sub_6FB23260(5, 1, 0);
	}
	iStack_284 = 0;
	iVar7 = Unicode::strlen((Unicode*)&word_6FBB1A58);
	if (iVar7 < 1)
	{
		iVar7 = 0;
		if (byte_6FBB2D14 != '\0')
		{
			if (byte_6FBB2CF8 != '\0')
			{
				sub_6FAD25F0(0x83, gnScreenHeight + -0x58);
			}
			goto LAB_6fad24f6;
		}
	}
	else
	{
		Unicode::strncpy(aUStack_204, (Unicode*)&word_6FBB1A58, 0x100);
		pSplitText = D2Win_10199(aUStack_204, &iStack_270, gnScreenWidth + -0x109);
		iVar7 = 0;
		if (pSplitText != nullptr)
		{
			iVar9 = 0;
			pDVar6 = pSplitText;
			do
			{
				iStack_284 = iVar7;
				if (iVar9 < 0x2d)
				{
					D2Win_10117_DrawText(pDVar6->wszLine, 0x83, iVar9 + -0x58 + gnScreenHeight, 0, 0);
					iStack_280 = D2Win_10121_GetTextWidth(pDVar6->wszLine);
				}
				pDVar1 = pDVar6->pNextLine;
				if (((pDVar1 == nullptr) && (byte_6FBB2D14 != '\0')) &&
				    (byte_6FBB2CF8 != '\0'))
				{
					iVar7 = iVar9 + -0x58 + gnScreenHeight;
					iVar3 = D2Win_10121_GetTextWidth(pDVar6->wszLine);
					sub_6FAD25F0(iVar3 + 0x83, iVar7);
				}
				iVar7 = iStack_284 + 1;
				iVar9 = iVar9 + 0xf;
				pDVar6 = pDVar1;
			} while (pDVar1 != nullptr);
		}
		D2Win_10200(pSplitText);
		if ((0 < iVar7) && (iStack_284 = iVar7 + -1, 2 < iStack_284))
		{
			iStack_284 = 2;
		}
	LAB_6fad24f6:
		iVar7 = iStack_284;
		if ((byte_6FBB2D14 != '\0') && (byte_6FBB2CF8 != '\0'))
			goto LAB_6fad25b5;
	}
	iVar7 = iVar7 * 0xf + -0x58 + gnScreenHeight;
	if (dword_6FB78374 == 1)
	{
		iVar3 = 0;
		iVar9 = 0;
		pUVar4 = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd4c));
		D2Win_10117_DrawText(pUVar4, iStack_280 + 0x83, iVar7, iVar9, iVar3);
	}
	DVar5 = GetTickCount();
	if ((dword_6FB78378 & 0xffff) < DVar5 - dword_6FBB2D18)
	{
		dword_6FBB2D18 = DVar5;
		if (dword_6FB78374 != 0)
		{
			dword_6FB78378 = CONCAT22((*(uint16_t*)((uint8_t*)&dword_6FB78378 + 2)), 100);
			dword_6FB78374 = 0;
			D2Win_10127_SetFont(FStack_26c);
			return;
		}
		dword_6FB78378 = CONCAT22((*(uint16_t*)((uint8_t*)&dword_6FB78378 + 2)), 500);
		dword_6FB78374 = 1;
	}
LAB_6fad25b5:
	D2Win_10127_SetFont(FStack_26c);
}

//D2Client.0x6FAD25F0
void __fastcall sub_6FAD25F0(int a1, int a2)
{
	int iVar1;
	int iVar2;
	Unicode* wszText;
	DWORD DVar3;
	int iVar4;
	int bCentered;

	iVar4 = 0;
	iVar1 = Unicode::strlen((Unicode*)&byte_6FBB1C60);
	if (iVar1 != 0)
	{
		iVar4 = D2Win_10121_GetTextWidth((Unicode*)&byte_6FBB1C60);
		if (gnScreenWidth + -0x109 < iVar4 + -0x83 + a1)
		{
			a1 = 0x83;
			a2 = a2 + 0xf;
		}
		D2Win_10117_DrawText((Unicode*)&byte_6FBB1C60, a1, a2, 4, 0);
	}
	iVar1 = D2Win_10121_GetTextWidth((Unicode*)&byte_6FBB2CB8);
	iVar2 = Unicode::strlen((Unicode*)&byte_6FBB2CB8);
	if (iVar2 != 0)
	{
		if (gnScreenWidth + -0x109 < a1 + iVar1 + -0x83 + iVar4)
		{
			a1 = 0x83;
			a2 = a2 + 0xf;
		}
		D2Win_10117_DrawText((Unicode*)&byte_6FBB2CB8, a1 + iVar4, a2, 4, 0);
	}
	if (dword_6FB78374 == 1)
	{
		bCentered = 0;
		iVar2 = 4;
		wszText = (Unicode*)(D2LANG_GetStringFromTblIndex(0xd4c));
		D2Win_10117_DrawText(wszText, a1 + iVar1 + iVar4, a2, iVar2, bCentered);
	}
	DVar3 = GetTickCount();
	if ((dword_6FB78378 & 0xffff) < DVar3 - dword_6FBB2D18)
	{
		dword_6FBB2D18 = DVar3;
		if (dword_6FB78374 != 0)
		{
			dword_6FB78378 = CONCAT22((*(uint16_t*)((uint8_t*)&dword_6FB78378 + 2)), 100);
			dword_6FB78374 = 0;
			return;
		}
		dword_6FB78378 = CONCAT22((*(uint16_t*)((uint8_t*)&dword_6FB78378 + 2)), 500);
		dword_6FB78374 = 1;
	}
}

//D2Client.0x6FAD2720
void __cdecl sub_6FAD2720(int a1)
{
	if (gnScreenHeight + -0x31 < (int)(uint32_t) * (uint16_t*)(a1 + 0xe))
	{
		sub_6FB23260(5, 1, 0);
		return;
	}
}

//D2Client.0x6FAD2760
void __cdecl sub_6FAD2760(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	Unicode* pUVar1;
	int iVar2;
	Unicode* pUVar3;
	uint16_t* puVar4;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar2 = dword_6FBB1CA0;
	if ((pSMSGHANDLER_PARAMS->lParam & 0x40000000U) == 0)
	{
		if (pSMSGHANDLER_PARAMS->wParam == 0x26)
		{
			pUVar1 = (Unicode*)((int)&dword_6FBB1CA8 + dword_6FBB1CA0 * 0x202);
			pUVar3 = pUVar1;
			puVar4 = &word_6FBB1A58;
			for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*(uint32_t*)puVar4 = *(uint32_t*)pUVar3;
				pUVar3 = pUVar3 + 2;
				puVar4 = puVar4 + 2;
			}
			*puVar4 = pUVar3->ch;
			dword_6FBB2D04 = Unicode::strlen(pUVar1);
			iVar2 = dword_6FBB1CA0 + 1;
			if (iVar2 < 8)
			{
				if (iVar2 < 0)
				{
					iVar2 = 7;
				}
			}
			else
			{
				iVar2 = 0;
			}
			if (((uint16_t)word_6FBB2D00 < 7) && ((int)(word_6FBB2D00 & 0xffff) < 8 - iVar2))
			{
				iVar2 = dword_6FBB1CA0;
			}
		}
		else if (pSMSGHANDLER_PARAMS->wParam == 0x28)
		{
			iVar2 = dword_6FBB1CA0 + -1;
			if (iVar2 < 8)
			{
				if (iVar2 < 0)
				{
					iVar2 = 7;
				}
			}
			else
			{
				iVar2 = 0;
			}
			if (((uint16_t)word_6FBB2D00 < 7) && ((int)(word_6FBB2D00 & 0xffff) < 8 - iVar2))
			{
				iVar2 = dword_6FBB1CA0;
			}
			dword_6FBB1CA0 = iVar2;
			pUVar1 = (Unicode*)((int)&dword_6FBB1CA8 + dword_6FBB1CA0 * 0x202);
			pUVar3 = pUVar1;
			puVar4 = &word_6FBB1A58;
			for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1)
			{
				*(uint32_t*)puVar4 = *(uint32_t*)pUVar3;
				pUVar3 = pUVar3 + 2;
				puVar4 = puVar4 + 2;
			}
			*puVar4 = pUVar3->ch;
			dword_6FBB2D04 = Unicode::strlen(pUVar1);
			return;
		}
	}
	dword_6FBB1CA0 = iVar2;
}

//D2Client.0x6FAD2890
void __cdecl sub_6FAD2890(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	D2SplittedTextStrc* pDVar1;
	Unicode** ppUVar2;
	int iVar3;
	uint32_t uVar4;
	D2SplittedTextStrc* pDVar5;
	int iVar6;
	Unicode* pUVar7;
	uint8_t* pbVar8;
	uint16_t* puVar9;
	uint32_t* puVar10;
	uint8_t* pbStack_220;
	Font FStack_21c;
	uint8_t uStack_218;
	char cStack_217;
	uint8_t uStack_216;
	uint32_t uStack_215;
	uint8_t uStack_116;
	uint8_t auStack_115[17];
	uint8_t local_104[260];

	if (dword_6FBB2D08 < 1)
	{
		return;
	}
	iVar3 = Unicode::strlen((Unicode*)&word_6FBB1A58);
	uVar4 = pSMSGHANDLER_PARAMS->wParam;
	if (uVar4 == 8)
	{
		if (dword_6FBB2D04 != 0)
		{
			dword_6FBB2D04 = dword_6FBB2D04 - 1;
			(&word_6FBB1A58)[dword_6FBB2D04] = 0;
		}
		goto LAB_6fad2d82;
	}
	if (uVar4 == 0xd)
	{
		iVar3 = 0;
		while (((uint16_t)(&word_6FBB1A58)[iVar3] < 0x100 &&
		        (iVar6 = isspace((uint32_t)(uint16_t)(&word_6FBB1A58)[iVar3]), iVar6 != 0)))
		{
			iVar3 = iVar3 + 1;
		}
		iVar6 = Unicode::strlen((Unicode*)(&word_6FBB1A58 + iVar3));
		if (iVar6 != 0)
		{
			if (word_6FBB2D00 == 8)
			{
				iVar6 = dword_6FB782EC + -1;
				dword_6FB782E8 = dword_6FB782EC;
				dword_6FB782EC = iVar6;
				if (iVar6 < 0)
				{
					dword_6FB782EC = 7;
				}
			}
			else
			{
				if ((word_6FBB2D00 != 0) && (dword_6FB782E8 = dword_6FB782E8 + -1, dword_6FB782E8 < 0))
				{
					dword_6FB782E8 = 7;
				}
				word_6FBB2D00 = word_6FBB2D00 + 1;
			}
			dword_6FBB1CA0 = dword_6FB782E8;
			pUVar7 = (Unicode*)(&word_6FBB1A58 + iVar3);
			puVar9 = (uint16_t*)((int)&dword_6FBB1CA8 + dword_6FB782E8 * 0x202);
			for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*(uint32_t*)puVar9 = *(uint32_t*)pUVar7;
				pUVar7 = pUVar7 + 2;
				puVar9 = puVar9 + 2;
			}
			*puVar9 = pUVar7->ch;
			WideCharToMultiByte(0, 0x250, (LPCWCH)(&word_6FBB1A58), -1, (LPSTR)local_104, 0x100, (LPCSTR)0x0, (LPBOOL)0x0);
			puVar10 = &uStack_215;
			for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1)
			{
				*puVar10 = 0;
				puVar10 = puVar10 + 1;
			}
			uStack_216 = byte_6FBB2CFC;
			pbStack_220 = local_104 + iVar3;
			iVar3 = _stricmp((char*)pbStack_220, "/fps");
			if (iVar3 == 0)
			{
				WNDPROC_ToggleDebugInfoNoCacheStats();
			}
			else
			{
				iVar3 = _stricmp((char*)pbStack_220, "/framerate");
				if (iVar3 == 0)
				{
					WNDPROC_ToggleDebugInfo();
				}
				else
				{
					iVar3 = _strnicmp((char*)pbStack_220, "/players", 8);
					if ((iVar3 == 0) &&
					    ((((iVar3 = sub_6FAABFF0(), iVar3 == 0 || (iVar3 = sub_6FAABFF0(), iVar3 == 1)) ||
					          (iVar3 = sub_6FAABFF0(), iVar3 == 6)) ||
					        (iVar3 = sub_6FAABFF0(), iVar3 == 8))))
					{
						iVar3 = atoi((char*)(pbStack_220 + 8));
						if (iVar3 < 2)
						{
							iVar3 = 1;
						}
						else if (7 < iVar3)
						{
							iVar3 = 8;
						}
						PLAYER_SetVirtualPlayerCount(iVar3);
						sprintf((char*)pbStack_220, "players set to %d", iVar3);
					}
					iVar3 = _stricmp((char*)pbStack_220, "/nopickup");
					if (iVar3 == 0)
					{
						dword_6FBAB9E4 = (uint32_t)(dword_6FBAB9E4 == 0);
					}
					else
					{
						iVar3 = _stricmp((char*)pbStack_220, "soundchaosdebug");
						if (iVar3 == 0)
						{
							sub_6FB56CD0();
						}
						else
						{
							cStack_217 = '\x01';
							uStack_218 = 0x15;
							uStack_216 = byte_6FBB2CFC;
							if (byte_6FBB2D14 != '\0')
							{
								iVar3 = Unicode::strlen((Unicode*)&word_6FBB1A58);
								iVar6 = 0;
								if (0 < iVar3)
								{
									do
									{
										if (0xff < (uint16_t)(&word_6FBB1A58)[iVar3])
											goto LAB_6fad2c93;
										iVar6 = iVar6 + 1;
									} while (iVar6 < iVar3);
								}
							}
							iVar3 = sub_6FAD2DB0(&pbStack_220, (uint8_t*)(&cStack_217), (char*)(auStack_115));
							if ((iVar3 == 0) || (cStack_217 != '\0'))
							{
							LAB_6fad2c93:
								if (cStack_217 == '\x03')
								{
									if (byte_6FBB2D14 != '\0')
									{
										iVar3 = Unicode::strlen((Unicode*)&word_6FBB1A58);
										iVar6 = 0;
										if (0 < iVar3)
										{
											do
											{
												if (0xff < (uint16_t)(&word_6FBB1A58)[iVar3])
													goto LAB_6fad2c58;
												iVar6 = iVar6 + 1;
											} while (iVar6 < iVar3);
										}
									}
									iVar3 = sub_6FAD34A0(pbStack_220, "/msg", 1);
									if ((((iVar3 == 0) &&
									         (iVar3 = sub_6FAD34A0(pbStack_220, "/m", 1), iVar3 == 0)) &&
									        ((iVar3 = sub_6FAD34A0(pbStack_220, "/whisper", 1), iVar3 == 0 &&
									                                                                (((iVar3 = sub_6FAD34A0(pbStack_220, "/w", 1), iVar3 == 0 &&
									                                                                                                                   (iVar3 = sub_6FAD3350(pbStack_220, "/help"), iVar3 == 0)) &&
									                                                                    (iVar3 = sub_6FAD3350(pbStack_220, "/?"), iVar3 == 0)))))) &&
									    (iVar3 = (int)(CLIENT_GetComInterface()), iVar3 != 0))
									{
										(**(code**)(iVar3 + 0x14))();
									}
									goto LAB_6fad2a1a;
								}
							}
							else
							{
								uStack_218 = 0x14;
							}
						LAB_6fad2c58:
							iVar3 = Unicode::strlen((Unicode*)&word_6FBB1A58);
							if (0 < iVar3)
							{
								pbVar8 = pbStack_220;
								puVar10 = &uStack_215;
								for (iVar3 = 0x3f; iVar3 != 0; iVar3 = iVar3 + -1)
								{
									*puVar10 = *(uint32_t*)pbVar8;
									pbVar8 = pbVar8 + 4;
									puVar10 = puVar10 + 1;
								}
								*(uint16_t*)puVar10 = *(uint16_t*)pbVar8;
								*(uint8_t*)((int)puVar10 + 2) = pbVar8[2];
								uStack_116 = 0;
								sub_6FAADB50((int)&uStack_218);
							}
						}
					}
				}
			}
		}
	}
	else if (uVar4 != 0x1b)
	{
		if (((byte_6FBB2D14 != '\0') || (uVar4 = D2Win_10128((uint8_t)pSMSGHANDLER_PARAMS->wParam), uVar4 != 0)) &&
		    ((dword_6FBB2D04 < 0xff && (iVar3 < 0xff))))
		{
			FStack_21c = D2Win_10127_SetFont(D2FONT_FONTINGAMECHAT);
			pDVar5 = D2Win_10199((Unicode*)&word_6FBB1A58, (int*)&pbStack_220, gnScreenWidth + -0x109);
			iVar6 = 0;
			pDVar1 = pDVar5;
			while (pDVar1 != nullptr)
			{
				ppUVar2 = &pDVar1->wszLine;
				pDVar1 = pDVar1->pNextLine;
				iVar6 = D2Win_10121_GetTextWidth(*ppUVar2);
			}
			D2Win_10200(pDVar5);
			if ((pbStack_220 < (uint8_t*)0x4) &&
			    ((pbStack_220 != (uint8_t*)0x3 || (iVar6 <= gnScreenWidth + -0x113))))
			{
				iVar6 = gnScreenWidth + -0x109;
				(&word_6FBB1A58)[iVar3] = (short)pSMSGHANDLER_PARAMS->wParam;
				pDVar5 = D2Win_10199((Unicode*)&word_6FBB1A58, (int*)&pbStack_220, iVar6);
				iVar3 = 0;
				pDVar1 = pDVar5;
				while (pDVar1 != nullptr)
				{
					ppUVar2 = &pDVar1->wszLine;
					pDVar1 = pDVar1->pNextLine;
					iVar3 = D2Win_10121_GetTextWidth(*ppUVar2);
				}
				D2Win_10200(pDVar5);
				if ((pbStack_220 != (uint8_t*)0x3) || (iVar3 < gnScreenWidth + -0x113))
				{
					dword_6FBB2D04 = dword_6FBB2D04 + 1;
				}
			}
			D2Win_10127_SetFont(FStack_21c);
		}
		goto LAB_6fad2d82;
	}
LAB_6fad2a1a:
	sub_6FB23260(5, 1, 0);
LAB_6fad2d82:
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD2DB0
uint32_t __fastcall sub_6FAD2DB0(void* a1, uint8_t* a2, char* a3)
{
	char cVar1;
	uint32_t MaxCount;
	int iVar2;
	uint32_t uVar3;
	uint8_t** ppuVar4;
	int iVar5;
	char* pcVar6;
	char* local_210;
	uint8_t* local_20c;
	uint32_t uStack_208;
	char acStack_204[260];
	char local_100[256];

	local_210 = local_100;
	*a3 = '\0';
	local_20c = a2;
	strncpy(local_100, (const char* __restrict)(*(uint32_t*)(a1)), 0x100);
	uStack_208 = SStrLen(local_210);
	iVar5 = 0;
	ppuVar4 = &ptr_6FB7837C;
	do
	{
		MaxCount = SStrLen((const char*)(*ppuVar4));
		if ((*(int*)((int)ppuVar4 + 10) != 0) || (iVar2 = sub_6FAABFF0(), iVar2 != 0))
		{
			if (*(short*)(ppuVar4 + 1) == 3)
			{
				if (((int)MaxCount <= (int)uStack_208) &&
				    (iVar2 = SStrCmpI(local_210, (const char*)(*ppuVar4), MaxCount), iVar2 == 0))
				{
					*local_20c = *(uint8_t*)(&word_6FB78380 + iVar5 * 7);
					return 1;
				}
			}
			else if ((((int)MaxCount < (int)uStack_208) &&
			             (iVar2 = SStrCmpI(local_210, (const char*)(*ppuVar4), MaxCount), iVar2 == 0)) &&
			         (local_210[MaxCount] != '\0'))
			{
				local_210 = local_210 + MaxCount;
				if (*(int*)((int)&dword_6FB78382 + iVar5 * 0xe) != 0)
				{
					SStrTokenize((const char**)(&local_210), acStack_204, 0x100, (char*)&word_6FB7847C, nullptr);
					iVar2 = -1;
					pcVar6 = local_210;
					break;
				}
				*(uint32_t*)a1 = *(uint32_t*)(a1) + MaxCount;
				goto LAB_6fad2f36;
			}
		}
		ppuVar4 = (uint8_t**)((int)ppuVar4 + 0xe);
		iVar5 = iVar5 + 1;
		if ((int)&tbl_6FB783A5 < (int)ppuVar4)
		{
			return 0;
		}
	} while (true);
	while (true)
	{
		iVar2 = iVar2 + -1;
		cVar1 = *pcVar6;
		pcVar6 = pcVar6 + 1;
		if (cVar1 == '\0')
			break;
		if (iVar2 == 0)
			break;
	}
	if (iVar2 != -2)
	{
		uVar3 = 0xffffffff;
		pcVar6 = acStack_204;
		do
		{
			if (uVar3 == 0)
				break;
			uVar3 = uVar3 - 1;
			cVar1 = *pcVar6;
			pcVar6 = pcVar6 + 1;
		} while (cVar1 != '\0');
		if (~uVar3 - 1 < 0x32)
		{
			SStrCopy(a3, acStack_204, 0x7fffffff);
			uVar3 = 0xffffffff;
			pcVar6 = acStack_204;
			do
			{
				if (uVar3 == 0)
					break;
				uVar3 = uVar3 - 1;
				cVar1 = *pcVar6;
				pcVar6 = pcVar6 + 1;
			} while (cVar1 != '\0');
			*(uint32_t*)a1 = *(uint32_t*)(a1) + ~uVar3 + MaxCount;
		LAB_6fad2f36:
			*local_20c = *(uint8_t*)(&word_6FB78380 + iVar5 * 7);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAD2F60
void __cdecl sub_6FAD2F60()
{
	dword_6FB782E8 = 7;
	dword_6FB782EC = 7;
	dword_6FBB1CA0 = 0;
	word_6FBB2D00 = 0;
	dword_6FBB2D04 = 0;
}

//D2Client.0x6FAD2F90
void __cdecl sub_6FAD2F90()
{
	int iVar1;
	uint32_t* puVar2;

	puVar2 = (uint32_t*)&word_6FBB1A58;
	for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1)
	{
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
	*(uint16_t*)puVar2 = 0;
	dword_6FBB2D04 = 0;
	dword_6FBB2D08 = 0;
}

//D2Client.0x6FAD2FB0
// TODO: decompilation needs review (extraout)
uint32_t __cdecl sub_6FAD2FB0()
{
	uint8_t bVar1;
	char cVar2;
	int iVar3;
	uint32_t uVar4;
	char* pcVar5;
	uint8_t* pbVar6;
	uint8_t* pbVar7;
	Unicode* a3;
	int iVar8;
	short index;
	uint32_t uVar9;
	uint32_t uVar10;
	Unicode* pUVar11;
	uint32_t extraout_EDX;
	uint32_t extraout_EDX_00;
	bool bVar12;
	Unicode* pUVar13;
	int local_ca0;
	char acStack_c9c[20];
	int local_c88;
	uint8_t abStack_c70[464];
	uint8_t abStack_aa0[340];
	Unicode aUStack_94c[339];
	uint16_t uStack_6a6;
	Unicode aUStack_6a4[339];
	uint16_t uStack_3fe;
	char acStack_3fc[340];
	Unicode aUStack_2a8[339];
	uint16_t uStack_2;

	iVar3 = (int)(CLIENT_GetComInterface());
	if (iVar3 == 0)
	{
		return 0;
	}
	iVar3 = (**(code**)(iVar3 + 0x24))();
	if (iVar3 == 0)
	{
		return 0;
	}
	if (local_ca0 != 0)
	{
		return 1;
	}
	uVar9 = 0xffffffff;
	pbVar6 = abStack_c70;
	do
	{
		if (uVar9 == 0)
			break;
		uVar9 = uVar9 - 1;
		bVar1 = *pbVar6;
		pbVar6 = pbVar6 + 1;
	} while (bVar1 != 0);
	switch (local_c88)
	{
	case 1:
	case 2:
	case 3:
	case 5:
	case 7:
	case 9:
	case 0x15:
	case 0x16:
	case 0x17:
		goto switchD_6fad3072_caseD_1;
	case 4:
	case 6:
	case 10:
		if ((abStack_c70[0] == 0x2a) ||
		    (pcVar5 = (char*)(SStrChr((char*)abStack_c70, '*')), pcVar5 == nullptr))
		{
			SStrCopy((char*)abStack_aa0, (char*)abStack_c70, 0x7fffffff);
		}
		else
		{
			uVar4 = (int)pcVar5 - (int)abStack_c70;
			pbVar6 = abStack_c70;
			pbVar7 = abStack_aa0;
			for (uVar10 = uVar4 >> 2; uVar10 != 0; uVar10 = uVar10 - 1)
			{
				*(uint32_t*)pbVar7 = *(uint32_t*)pbVar6;
				pbVar6 = pbVar6 + 4;
				pbVar7 = pbVar7 + 4;
			}
			for (uVar10 = uVar4 & 3; uVar10 != 0; uVar10 = uVar10 - 1)
			{
				*pbVar7 = *pbVar6;
				pbVar6 = pbVar6 + 1;
				pbVar7 = pbVar7 + 1;
			}
			abStack_aa0[uVar4] = 0;
		}
		if (abStack_aa0[0] == 0)
		{
		LAB_6fad31a1:
			sprintf(acStack_3fc, "%s", abStack_aa0);
		}
		else
		{
			if (abStack_aa0[0] == 0x2a)
			{
				pcVar5 = (char*)(SStrChr((char*)abStack_c70, '*'));
				if ((pcVar5 == nullptr) || (pbVar6 = (uint8_t*)(pcVar5 + 1), pcVar5[1] == '\0'))
				{
					pbVar6 = abStack_c70;
				}
				pcVar5 = (char*)(SStrChr((char*)abStack_aa0, '*'));
				if ((pcVar5 == nullptr) || (pbVar7 = (uint8_t*)(pcVar5 + 1), pcVar5[1] == '\0'))
				{
					pbVar7 = abStack_aa0;
				}
				do
				{
					bVar1 = *pbVar7;
					bVar12 = bVar1 < *pbVar6;
					if (bVar1 != *pbVar6)
					{
					LAB_6fad315c:
						iVar3 = (1 - (uint32_t)bVar12) - (uint32_t)(bVar12 != 0);
						goto LAB_6fad3161;
					}
					if (bVar1 == 0)
						break;
					bVar1 = pbVar7[1];
					bVar12 = bVar1 < pbVar6[1];
					if (bVar1 != pbVar6[1])
						goto LAB_6fad315c;
					pbVar7 = pbVar7 + 2;
					pbVar6 = pbVar6 + 2;
				} while (bVar1 != 0);
				iVar3 = 0;
			LAB_6fad3161:
				if (iVar3 == 0)
					goto LAB_6fad31a1;
			}
			pcVar5 = (char*)(SStrChr((char*)abStack_c70, '*'));
			if ((pcVar5 == nullptr) || (pbVar6 = (uint8_t*)(pcVar5 + 1), pcVar5[1] == '\0'))
			{
				pbVar6 = abStack_c70;
			}
			sprintf(acStack_3fc, "%s (*%s)", abStack_aa0, pbVar6);
		}
		Unicode::win2Unicode(aUStack_94c, acStack_3fc, 0x154);
		Unicode::win2Unicode(aUStack_6a4, (char*)(abStack_c70 + ~uVar9), 0x154);
		pUVar11 = aUStack_6a4;
		uStack_6a6 = 0;
		pUVar13 = aUStack_94c;
		uStack_3fe = 0;
		index = 0x14d5;
		if (local_c88 != 10)
		{
			index = 0x14d4;
		}
		a3 = (Unicode*)(D2LANG_GetStringFromTblIndex(index));
		Unicode::sprintf(0x153, aUStack_2a8, a3, pUVar13, pUVar11);
		uStack_2 = 0;
		uVar9 = CONCAT31((int32_t)((uint32_t)extraout_EDX >> 8), 2);
		pUVar11 = aUStack_2a8;
		break;
	default:
		iVar3 = 0;
		do
		{
			cVar2 = "<BattleNet>: "[iVar3];
			acStack_c9c[iVar3] = cVar2;
			iVar3 = iVar3 + 1;
		} while (cVar2 != '\0');
		Unicode::win2Unicode(aUStack_94c, acStack_c9c, 0x154);
		Unicode::win2Unicode(aUStack_6a4, (char*)(abStack_c70 + ~uVar9), 0x154);
		uStack_6a6 = 0;
		uStack_3fe = 0;
		iVar3 = Unicode::strlen(aUStack_6a4);
		iVar8 = Unicode::strlen(aUStack_94c);
		if (0x153 < iVar3 + iVar8)
		{
			iVar3 = Unicode::strlen(aUStack_94c);
			if (iVar3 < 0x153)
			{
				aUStack_2a8[-0xab - iVar3].ch = 0;
			}
			else
			{
				aUStack_6a4[0].ch = 0;
			}
		}
		Unicode::strcat(aUStack_94c, aUStack_6a4);
		uStack_6a6 = 0;
		uVar9 = CONCAT31((int32_t)((uint32_t)extraout_EDX_00 >> 8), 3);
		pUVar11 = aUStack_94c;
	}
	sub_6FB1C600(pUVar11, uVar9);
switchD_6fad3072_caseD_1:
	return 1;
}

//D2Client.0x6FAD3350
uint32_t __fastcall sub_6FAD3350(uint8_t* a1, char* a2)
{
	char cVar1;
	uint8_t bVar2;
	int iVar3;
	int iVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	char* pcVar8;
	uint8_t* pbVar9;
	uint32_t* puVar10;
	uint16_t local_22a;
	uint8_t* local_228;
	int local_224;
	int local_220;
	uint8_t local_21c;
	uint8_t local_21b;
	uint8_t local_214;
	uint32_t local_202[64];
	char local_100[256];

	uVar5 = 0xffffffff;
	pcVar8 = a2;
	do
	{
		if (uVar5 == 0)
			break;
		uVar5 = uVar5 - 1;
		cVar1 = *pcVar8;
		pcVar8 = pcVar8 + 1;
	} while (cVar1 != '\0');
	local_220 = ~uVar5 - 1;
	uVar5 = 0xffffffff;
	pbVar9 = a1;
	do
	{
		if (uVar5 == 0)
			break;
		uVar5 = uVar5 - 1;
		bVar2 = *pbVar9;
		pbVar9 = pbVar9 + 1;
	} while (bVar2 != 0);
	uVar6 = 0xffffffff;
	pcVar8 = a2;
	do
	{
		if (uVar6 == 0)
			break;
		uVar6 = uVar6 - 1;
		cVar1 = *pcVar8;
		pcVar8 = pcVar8 + 1;
	} while (cVar1 != '\0');
	if (~uVar6 - 1 <= ~uVar5 - 1)
	{
		uVar5 = 0xffffffff;
		pcVar8 = a2;
		do
		{
			if (uVar5 == 0)
				break;
			uVar5 = uVar5 - 1;
			cVar1 = *pcVar8;
			pcVar8 = pcVar8 + 1;
		} while (cVar1 != '\0');
		iVar7 = ~uVar5 - 1;
		local_228 = a1;
		if (iVar7 != 0)
		{
			local_224 = (int)a1 - (int)a2;
			pcVar8 = a2;
			do
			{
				iVar7 = iVar7 + -1;
				iVar3 = toupper((int)pcVar8[local_224]);
				iVar4 = toupper((int)*pcVar8);
				if (iVar3 != iVar4)
				{
					return 0;
				}
				pcVar8 = pcVar8 + 1;
			} while (iVar7 != 0);
		}
		if ((local_228[local_220] == 0x20) || (local_228[local_220] == 0))
		{
			local_22a = word_6FB7847C;
			iVar7 = 0;
			pcVar8 = strtok((char*)local_228, (char*)&local_22a);
			if (pcVar8 != nullptr)
			{
				do
				{
					if (1 < iVar7)
						break;
					iVar7 = iVar7 + 1;
					pcVar8 = strtok(nullptr, (char*)&local_22a);
				} while (pcVar8 != nullptr);
				if (iVar7 == 1)
				{
					iVar7 = (int)(CLIENT_GetComInterface());
					if (iVar7 != 0)
					{
						(**(code**)(iVar7 + 0x14))();
					}
					return 1;
				}
			}
			local_21b = 4;
			local_214 = 3;
			sprintf(local_100, "<BattleNet>: Correct usage is: %s", a2);
			pcVar8 = local_100;
			puVar10 = local_202;
			for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1)
			{
				*puVar10 = *(uint32_t*)pcVar8;
				pcVar8 = pcVar8 + 4;
				puVar10 = puVar10 + 1;
			}
			sub_6FB1E120((int)&local_21c);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAD34A0
uint32_t __fastcall sub_6FAD34A0(uint8_t* a1, char* a2, int a3)
{
	char cVar1;
	uint8_t bVar2;
	int iVar3;
	int iVar4;
	uint8_t* pbVar5;
	char* p1;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;
	int iVar9;
	char* pcVar10;
	uint32_t* puVar11;
	uint8_t local_430[258];
	uint8_t local_32e;
	char acStack_32d[17];
	char local_31c[256];
	uint8_t local_21c;
	uint8_t local_21b;
	uint8_t local_214;
	uint32_t local_202[64];
	char local_100[256];

	uVar6 = 0xffffffff;
	pcVar10 = a2;
	do
	{
		if (uVar6 == 0)
			break;
		uVar6 = uVar6 - 1;
		cVar1 = *pcVar10;
		pcVar10 = pcVar10 + 1;
	} while (cVar1 != '\0');
	uVar7 = 0xffffffff;
	pbVar5 = a1;
	do
	{
		if (uVar7 == 0)
			break;
		uVar7 = uVar7 - 1;
		bVar2 = *pbVar5;
		pbVar5 = pbVar5 + 1;
	} while (bVar2 != 0);
	uVar8 = 0xffffffff;
	pcVar10 = a2;
	do
	{
		if (uVar8 == 0)
			break;
		uVar8 = uVar8 - 1;
		cVar1 = *pcVar10;
		pcVar10 = pcVar10 + 1;
	} while (cVar1 != '\0');
	if (~uVar8 - 1 <= ~uVar7 - 1)
	{
		uVar7 = 0xffffffff;
		pcVar10 = a2;
		do
		{
			if (uVar7 == 0)
				break;
			uVar7 = uVar7 - 1;
			cVar1 = *pcVar10;
			pcVar10 = pcVar10 + 1;
		} while (cVar1 != '\0');
		iVar9 = ~uVar7 - 1;
		if (iVar9 != 0)
		{
			pcVar10 = a2;
			do
			{
				iVar9 = iVar9 + -1;
				iVar3 = toupper((int)pcVar10[(int)a1 - (int)a2]);
				iVar4 = toupper((int)*pcVar10);
				if (iVar3 != iVar4)
				{
					return 0;
				}
				pcVar10 = pcVar10 + 1;
			} while (iVar9 != 0);
		}
		if ((a1[~uVar6 - 1] == 0x20) || (a1[~uVar6 - 1] == 0))
		{
			pbVar5 = a1;
			do
			{
				bVar2 = *pbVar5;
				pbVar5[(int)(local_430 + -(int)a1)] = bVar2;
				pbVar5 = pbVar5 + 1;
			} while (bVar2 != 0);
			pcVar10 = strtok((char*)a1, " ");
			iVar9 = 0;
			if (pcVar10 != nullptr)
			{
				do
				{
					iVar9 = iVar9 + 1;
					if (iVar9 == 2)
					{
						iVar3 = -(int)pcVar10;
						do
						{
							cVar1 = *pcVar10;
							pcVar10[(int)(local_31c + iVar3)] = cVar1;
							pcVar10 = pcVar10 + 1;
						} while (cVar1 != '\0');
					}
					else if (iVar9 == 3)
					{
						pcVar10 = pcVar10 + (int)(local_430 + -(int)a1);
						iVar9 = -(int)pcVar10;
						do
						{
							cVar1 = *pcVar10;
							pcVar10[(int)(local_100 + iVar9)] = cVar1;
							pcVar10 = pcVar10 + 1;
						} while (cVar1 != '\0');
						goto LAB_6fad35ff;
					}
					pcVar10 = strtok(nullptr, " ");
				} while (pcVar10 != nullptr);
				if (iVar9 == 3)
				{
				LAB_6fad35ff:
					if (a3 != 0)
					{
						for (iVar9 = sub_6FAAF5B0(0); iVar9 != 0; iVar9 = sub_6FAAF5B0(iVar9))
						{
							pcVar10 = local_31c;
							p1 = (char*)sub_6FAAF5D0(iVar9);
							iVar3 = _stricmp(p1, pcVar10);
							if (iVar3 == 0)
							{
								strncpy((char*)(local_430 + 3), local_100, 0xff);
								local_32e = 0;
								iVar9 = 0;
								do
								{
									pcVar10 = local_31c + iVar9;
									acStack_32d[iVar9] = *pcVar10;
									iVar9 = iVar9 + 1;
								} while (*pcVar10 != '\0');
								local_430[1] = 2;
								local_430[2] = byte_6FBB2CFC;
								local_430[0] = 0x15;
								sub_6FAADB50((int)local_430);
								return 1;
							}
						}
					}
					sprintf((char*)a1, "%s %s %s", a2, local_31c, local_100);
					iVar9 = (int)(CLIENT_GetComInterface());
					if (iVar9 != 0)
					{
						(**(code**)(iVar9 + 0x14))();
					}
					return 1;
				}
			}
			local_21b = 4;
			local_214 = 3;
			sprintf((char*)local_430, "<BattleNet>: Correct usage is: %s (name) (message)", a2);
			pbVar5 = local_430;
			puVar11 = local_202;
			for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1)
			{
				*puVar11 = *(uint32_t*)pbVar5;
				pbVar5 = pbVar5 + 4;
				puVar11 = puVar11 + 1;
			}
			sub_6FB1E120((int)&local_21c);
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAD3700
void __cdecl sub_6FAD3700()
{
	Unicode* pThis;
	int iVar1;

	pThis = (Unicode*)&byte_6FBB2D24;
	iVar1 = 4;
	do
	{
		pThis = pThis + 1;
		iVar1 = iVar1 + -1;
	} while (iVar1 != 0);
}

//D2Client.0x6FAD3720
void __cdecl sub_6FAD3720()
{
	sub_6FB23260(2, 2, 1);
}

//D2Client.0x6FAD3730
void __cdecl sub_6FAD3730()
{
	sub_6FB23260(1, 2, 1);
}

//D2Client.0x6FAD3750
void __cdecl sub_6FAD3750()
{
	int iVar1;

	iVar1 = sub_6FAABFF0();
	if (iVar1 != 0)
	{
		sub_6FB23260(0x16, 2, 1);
	}
}

//D2Client.0x6FAD3770
void __cdecl sub_6FAD3770()
{
	sub_6FB23260(0x18, 2, 0);
}

//D2Client.0x6FAD3790
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3790()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			sub_6FB06120(1);
			return;
		}
	}
}

//D2Client.0x6FAD37B0
void __cdecl sub_6FAD37B0()
{
	int iVar1;

	iVar1 = sub_6FAABF20();
	if (iVar1 == 0)
	{
		sub_6FB23260(5, 2, 0);
	}
}

//D2Client.0x6FAD37D0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD37D0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;
	uint32_t local_4;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			sub_6FB23260(0x21, 2, 0);
			iVar2 = SRegLoadValue("Diablo II", (const char*)(dword_6FB78C6B + 1), 1, (DWORD*)(&local_4));
			if ((iVar2 == 0) || (local_4 == 0))
			{
				local_4 = 1;
				SRegSaveValue("Diablo II", (const char*)(dword_6FB78C6B + 1), 1, 1);
			}
		}
	}
}

//D2Client.0x6FAD3840
void __cdecl sub_6FAD3840()
{
	int iVar1;

	sub_6FB23260(10, 2, 0);
	iVar1 = sub_6FB23230(10);
	if (iVar1 == 0)
	{
		sub_6FACB6E0(0);
		return;
	}
}

//D2Client.0x6FAD3870
void __cdecl sub_6FAD3870()
{
	sub_6FACB6E0(1);
}

//D2Client.0x6FAD3880
void __cdecl sub_6FAD3880()
{
	int iVar1;
	uint32_t uVar2;

	iVar1 = sub_6FACB8F0();
	uVar2 = iVar1 + 1U & 0x80000003;
	if ((int)uVar2 < 0)
	{
		uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
	}
	sub_6FACB920(uVar2);
}

//D2Client.0x6FAD38A0
void __cdecl sub_6FAD38A0()
{
	int iVar1;

	iVar1 = sub_6FACB9E0();
	sub_6FACB9F0((uint32_t)(iVar1 == 0));
}

//D2Client.0x6FAD38C0
void __cdecl sub_6FAD38C0()
{
	int iVar1;

	iVar1 = sub_6FACBA10();
	sub_6FACBA20((uint32_t)(iVar1 == 0));
}

//D2Client.0x6FAD38E0
void __cdecl sub_6FAD38E0()
{
	int iVar1;

	iVar1 = sub_6FACB9A0();
	sub_6FACB9B0((uint32_t)(iVar1 == 0));
}

//D2Client.0x6FAD3900
void __cdecl sub_6FAD3900()
{
	sub_6FB23260(4, 2, 1);
}

//D2Client.0x6FAD3920
void __cdecl sub_6FAD3920()
{
	sub_6FB23260(3, 2, 0);
	sub_6FB18760(0);
}

//D2Client.0x6FAD3940
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3940()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(0);
				return;
			}
			sub_6FB1A130(0);
			return;
		}
	}
}

//D2Client.0x6FAD3970
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3970()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(1);
				return;
			}
			sub_6FB1A130(1);
			return;
		}
	}
}

//D2Client.0x6FAD39A0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD39A0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(2);
				return;
			}
			sub_6FB1A130(2);
			return;
		}
	}
}

//D2Client.0x6FAD39D0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD39D0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(3);
				return;
			}
			sub_6FB1A130(3);
			return;
		}
	}
}

//D2Client.0x6FAD3A00
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3A00()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(4);
				return;
			}
			sub_6FB1A130(4);
			return;
		}
	}
}

//D2Client.0x6FAD3A30
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3A30()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(5);
				return;
			}
			sub_6FB1A130(5);
			return;
		}
	}
}

//D2Client.0x6FAD3A60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3A60()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(6);
				return;
			}
			sub_6FB1A130(6);
			return;
		}
	}
}

//D2Client.0x6FAD3A90
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3A90()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(7);
				return;
			}
			sub_6FB1A130(7);
			return;
		}
	}
}

//D2Client.0x6FAD3AC0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3AC0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(3);
			if (iVar2 != 0)
			{
				sub_6FB19FE0(8);
				return;
			}
			sub_6FB1A130(8);
			return;
		}
	}
}

//D2Client.0x6FAD3AF0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3AF0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(9);
					return;
				}
				sub_6FB1A130(9);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3B30
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3B30()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(10);
					return;
				}
				sub_6FB1A130(10);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3B70
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3B70()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(0xb);
					return;
				}
				sub_6FB1A130(0xb);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3BB0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3BB0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(0xc);
					return;
				}
				sub_6FB1A130(0xc);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3BF0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3BF0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(0xd);
					return;
				}
				sub_6FB1A130(0xd);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3C30
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3C30()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(0xe);
					return;
				}
				sub_6FB1A130(0xe);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3C70
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3C70()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FAAC080();
			if (iVar2 != 0)
			{
				iVar2 = sub_6FB23230(3);
				if (iVar2 != 0)
				{
					sub_6FB19FE0(0xf);
					return;
				}
				sub_6FB1A130(0xf);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3CB0
void __cdecl sub_6FAD3CB0()
{
	D2UnitStrc* pDVar1;
	int iVar2;

	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		pDVar1 = INVENTORY_GetItemFromBodyLoc(pDVar1->pInventory, 8);
		if (pDVar1 != nullptr)
		{
			iVar2 = ITEMS_CheckItemTypeId(pDVar1, 0x13);
			if (iVar2 != 0)
			{
				sub_6FB23260(0x1f, 2, 0);
			}
		}
	}
}

//D2Client.0x6FAD3D30
void __fastcall sub_6FAD3D30(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x19);
}

//D2Client.0x6FAD3D40
void __fastcall sub_6FAD3D40(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1a);
}

//D2Client.0x6FAD3D50
void __fastcall sub_6FAD3D50(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1b);
}

//D2Client.0x6FAD3D60
void __fastcall sub_6FAD3D60(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1c);
}

//D2Client.0x6FAD3D70
void __fastcall sub_6FAD3D70(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1d);
}

//D2Client.0x6FAD3D80
void __fastcall sub_6FAD3D80(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1e);
}

//D2Client.0x6FAD3D90
void __fastcall sub_6FAD3D90(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x1f);
}

//D2Client.0x6FAD3DA0
void __fastcall sub_6FAD3DA0(uint32_t a1)
{
	sub_6FAAD990(CONCAT31((int32_t)((uint32_t)a1 >> 8), 0x3f), 0x20);
}

//D2Client.0x6FAD3DB0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3DB0()
{
	bool bVar1;
	D2UnitStrc* pUnit;
	int iVar2;
	uint32_t extraout_var;

	sub_6FAA8B10(1);
	pUnit = CUNIT_GetPlayer();
	if (pUnit != nullptr)
	{
		iVar2 = sub_6FAABF20();
		if (iVar2 == 0)
		{
			bVar1 = sub_6FB283E0();
			if (((D2C_ZEXT(bVar1) == 0) && (pUnit->dwUnitType == 0)) &&
			    (pUnit->dwAnimMode == 2))
			{
				iVar2 = STATLIST_UnitGetStatValue(pUnit, 10, 0);
				if (iVar2 != 0)
				{
					sub_6FB4F410(pUnit, (int*)0x3);
					CLIENT_SendSimpleMessage(0x53);
					return;
				}
			}
		}
	}
}

//D2Client.0x6FAD3E10
void __cdecl sub_6FAD3E10()
{
	int iVar1;

	iVar1 = sub_6FAA8B30();
	sub_6FAA8B20((uint32_t)(iVar1 == 0));
}

//D2Client.0x6FAD3E30
void __cdecl sub_6FAD3E30()
{
	sub_6FAA8B40(1);
}

//D2Client.0x6FAD3E40
void __cdecl sub_6FAD3E40()
{
	sub_6FB23260(0xd, 0, 0);
}

//D2Client.0x6FAD3E60
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3E60()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAFC0E0();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB1EE90();
		if (D2C_ZEXT(bVar1) == 0)
		{
			iVar2 = sub_6FB23230(9);
			if (iVar2 != 0)
			{
				sub_6FB08860(1);
				return;
			}
			iVar2 = sub_6FB23800(0, 1);
			if (iVar2 == 0)
			{
				sub_6FB08700(1, 0);
				return;
			}
		}
	}
}

//D2Client.0x6FAD3EB0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3EB0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			sub_6FB19D30(-1);
			return;
		}
	}
}

//D2Client.0x6FAD3ED0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD3ED0()
{
	bool bVar1;
	int iVar2;
	uint32_t extraout_var;

	iVar2 = sub_6FAABF20();
	if (iVar2 == 0)
	{
		bVar1 = sub_6FB283E0();
		if (D2C_ZEXT(bVar1) == 0)
		{
			sub_6FB19D30(1);
			return;
		}
	}
}

//D2Client.0x6FAD3EF0
void __cdecl sub_6FAD3EF0()
{
	int iVar1;

	iVar1 = sub_6FB23230(0xc);
	if (iVar1 == 0)
	{
		iVar1 = sub_6FB23230(0x17);
		if (iVar1 == 0)
		{
			iVar1 = sub_6FB23230(0x19);
			if (iVar1 == 0)
			{
				sub_6FAED2B0();
				return;
			}
		}
	}
}

//D2Client.0x6FAD3F20
void __cdecl sub_6FAD3F20()
{
	int iVar1;
	D2UnitStrc* pDVar2;

	iVar1 = sub_6FAAC080();
	if (iVar1 != 0)
	{
		iVar1 = 0;
		pDVar2 = CUNIT_GetPlayer();
		iVar1 = sub_6FAB1920((int)pDVar2, 7, iVar1);
		if (iVar1 != -1)
		{
			iVar1 = FOG_IsExpansion();
			if (iVar1 != 0)
			{
				sub_6FB23260(0x24, 2, 1);
			}
		}
	}
}

//D2Client.0x6FAD3F70
void __cdecl sub_6FAD3F70()
{
	D2UnitStrc* pDVar1;
	int iVar2;

	sub_6FAA8B10(0);
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 != nullptr)
	{
		iVar2 = sub_6FAA8B30();
		if (((iVar2 == 0) && (pDVar1->dwUnitType == 0)) && (pDVar1->dwAnimMode == 3))
		{
			sub_6FB4F410(pDVar1, (int*)0x2);
			CLIENT_SendSimpleMessage(0x54);
			return;
		}
	}
}

//D2Client.0x6FAD3FB0
void __cdecl sub_6FAD3FB0()
{
	sub_6FAA8B40(0);
}

//D2Client.0x6FAD3FC0
void __cdecl sub_6FAD3FC0()
{
	sub_6FB23260(0xd, 1, 0);
	sub_6FAB5D40();
}

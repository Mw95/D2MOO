#include "UI/Dialog.h"

#include "Core/Archive.h"
#include "Core/WinMain.h"
#include "Core/WndProc.h"
#include "Engine/Gfx.h"
#include "Game/Game.h"
#include "Game/SCmd.h"
#include "Game/Select.h"
#include "Sound/SoundInst.h"
#include "UI/CmdTbl.h"
#include "UI/Inv.h"
#include "UI/Restart.h"
#include "UI/UI.h"

//D2Client.0x6FB78DF8
uint32_t tbl_6FB78DF8[1] = {3};
//D2Client.0x6FB78DFC
uint8_t byte_6FB78DFC = 0x1B;
//D2Client.0x6FB78E08
uint8_t byte_6FB78E08 = 0x1B;
//D2Client.0x6FB78EA0
uint32_t tbl_6FB78EA0[8] = {0, 0x20A, (uint32_t)sub_6FAD6150, 0x6C616964, 0x6162676F, 0x72676B63, 0x646E756F};
//D2Client.0x6FB78EC0
uint8_t* ptr_6FB78EC0 = (uint8_t*)"dialogbackground";
//D2Client.0x6FBB363C
int32_t dword_6FBB363C;
//D2Client.0x6FBB3640
int32_t dword_6FBB3640;
//D2Client.0x6FBB3644
int32_t dword_6FBB3644;
//D2Client.0x6FBB3648
uint32_t dword_6FBB3648;
//D2Client.0x6FBB364C
int32_t dword_6FBB364C;

//D2Client.0x6FAD5DC0
void __cdecl sub_6FAD5DC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	uint16_t uVar1;
	code* pcVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	DWORD DVar6;
	int* piVar7;
	bool bVar8;

	iVar3 = dword_6FBB3644;
	iVar5 = pSMSGHANDLER_PARAMS->lParam;
	uVar1 = *(uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
	iVar4 = sub_6FB23230(0x15);
	if ((iVar4 == 0) || (iVar5 = sub_6FB09C50((uint32_t)(uint16_t)iVar5, (uint32_t)uVar1), iVar5 == 0))
	{
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		pSMSGHANDLER_PARAMS->lResult = 0;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		if (iVar3 == 0)
		{
			FOG_DisplayAssert("pDialog != NULL", __FILE__, __LINE__);
			exit(-1);
		}
		if (*(int*)(iVar3 + 0x10) != 1)
		{
			piVar7 = *(int**)(iVar3 + 0xb08);
			if (piVar7 == nullptr)
			{
				return;
			}
			while (((int*)*piVar7 == nullptr ||
			        (iVar5 = (**(code**)(*(int*)*piVar7 + 0x10))(pSMSGHANDLER_PARAMS), iVar5 != 1)))
			{
				piVar7 = (int*)piVar7[1];
				if (piVar7 == nullptr)
				{
					return;
				}
			}
			return;
		}
		DVar6 = GetTickCount();
		if (DVar6 < *(int*)iVar3 + 0x50U)
		{
			return;
		}
		iVar5 = sub_6FAD5D30(iVar3, (int)pSMSGHANDLER_PARAMS);
		if ((((*(int*)(iVar3 + 0x48) != iVar5) || (iVar5 < 0)) || (*(int*)(iVar3 + 0x50) <= iVar5)) ||
		    (pcVar2 = *(code**)(*(int*)(iVar3 + 0x44) * 0x110 + 0x170 + iVar3), pcVar2 == nullptr))
			goto LAB_6fad5eae;
		iVar5 = (*pcVar2)();
		bVar8 = iVar5 == 0;
	}
	else
	{
		if (iVar3 == 0)
		{
			return;
		}
		bVar8 = *(int*)(iVar3 + 0x10) == 1;
	}
	if (!bVar8)
	{
		return;
	}
LAB_6fad5eae:
	*(uint32_t*)(iVar3 + 0x10) = 0;
}

//D2Client.0x6FAD5EC0
void __cdecl sub_6FAD5EC0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	DWORD DVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	uint32_t uVar8;

	iVar5 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	DVar2 = GetTickCount();
	if (DVar2 < *(int*)iVar5 + 0x50U)
	{
		pSMSGHANDLER_PARAMS->lResult = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
		return;
	}
	for (piVar1 = *(int**)(iVar5 + 0xb08); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
	{
		if (((int*)*piVar1 != nullptr) &&
		    (iVar3 = (**(code**)(*(int*)*piVar1 + 0xc))(pSMSGHANDLER_PARAMS), iVar3 == 1))
			goto LAB_6fad609b;
	}
	iVar3 = *(int*)(iVar5 + 0x44);
	*(uint32_t*)(iVar5 + 0x10) = 1;
	iVar4 = sub_6FAD5D30(iVar5, (int)pSMSGHANDLER_PARAMS);
	*(int*)(iVar5 + 0x44) = iVar4;
	*(int*)(iVar5 + 0x48) = iVar4;
	if ((iVar4 == iVar3) || (iVar4 == -1))
	{
		uVar6 = (uint32_t)(uint16_t)pSMSGHANDLER_PARAMS->lParam;
		uVar7 = (uint32_t) * (uint16_t*)((int)&pSMSGHANDLER_PARAMS->lParam + 2);
		if (((int)uVar6 < *(int*)(iVar5 + 0x2c) + -4) ||
		    (((*(int*)(iVar5 + 0x34) + 4 + *(int*)(iVar5 + 0x2c) < (int)uVar6 ||
		          ((int)uVar7 < *(int*)(iVar5 + 0x30) + -4)) ||
		        (*(int*)(iVar5 + 0x38) + 4 + *(int*)(iVar5 + 0x30) < (int)uVar7))))
		{
			iVar3 = sub_6FB23230(0x15);
			if ((iVar3 != 0) && (iVar3 = sub_6FB09C50(uVar6, uVar7), iVar3 != 0))
			{
				return;
			}
			if (*(code**)(iVar5 + 100) == nullptr)
			{
				D2_ASSERT(*(code**)(iVar5 + 0x60) != nullptr);
				(**(code**)(iVar5 + 0x60))();
				pSMSGHANDLER_PARAMS->lResult = 0;
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				return;
			}
			iVar5 = (**(code**)(iVar5 + 100))();
			if (iVar5 == 0)
			{
				return;
			}
			iVar5 = sub_6FB23230(6);
			if (iVar5 != 0)
			{
				uVar8 = uVar7;
				iVar5 = sub_6FAB5750();
				iVar5 = sub_6FAEECC0(iVar5, uVar6, uVar8);
				if (iVar5 != 0)
				{
					pSMSGHANDLER_PARAMS->bUseResult = 1;
					pSMSGHANDLER_PARAMS->lResult = 0;
					SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				}
			}
			iVar5 = sub_6FB23230(7);
			if (iVar5 == 0)
			{
				return;
			}
			iVar5 = sub_6FAB5750();
			iVar5 = sub_6FAEED20(iVar5, uVar6, uVar7);
			if (iVar5 == 0)
			{
				return;
			}
			pSMSGHANDLER_PARAMS->lResult = 0;
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
	else
	{
		sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
	}
LAB_6fad609b:
	pSMSGHANDLER_PARAMS->lResult = 0;
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD60C0
void __cdecl sub_6FAD60C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	int iVar2;

	iVar1 = dword_6FBB3644;
	if ((*(int*)(dword_6FBB3644 + 0x20) == 0) && (iVar2 = sub_6FB23230(5), iVar2 != 0))
	{
		return;
	}
	iVar1 = *(int*)(iVar1 + 0x1c);
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	if (iVar1 == 0)
	{
		if (dword_6FBB3644 == 0)
		{
			FOG_DisplayAssert("pDialog != NULL", __FILE__, __LINE__);
			exit(-1);
		}
		if ((4 < *(uint32_t*)(dword_6FBB3644 + 0x54)) && (*(code**)(dword_6FBB3644 + 0x60) != nullptr))
		{
			(**(code**)(dword_6FBB3644 + 0x60))();
			sub_6FB238B0();
		}
	}
}

//D2Client.0x6FAD6150
void __cdecl sub_6FAD6150(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	short sVar1;
	int* piVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar3 = dword_6FBB3644;
	sVar1 = *(short*)((int)&pSMSGHANDLER_PARAMS->wParam + 2);
	if (sVar1 != 0)
	{
		iVar6 = (int)sVar1 >> 0x1f;
		iVar5 = (int)sVar1 / 0x78 + iVar6;
		if (iVar5 != iVar6)
		{
			D2_ASSERT(dword_6FBB3644);
			for (piVar2 = *(int**)(dword_6FBB3644 + 0xb08); piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (((int*)*piVar2 != nullptr) &&
				    (iVar4 = (**(code**)(*(int*)*piVar2 + 8))(pSMSGHANDLER_PARAMS), iVar4 == 1))
				{
					return;
				}
			}
			if (iVar5 - iVar6 < 1)
			{
				if (*(int*)(iVar3 + 0x4c) < 2)
					goto LAB_6fad6252;
				iVar6 = *(int*)(iVar3 + 0x44);
				do
				{
					iVar6 = iVar6 + 1;
					if (iVar6 < *(int*)(iVar3 + 0x50))
					{
						if (iVar6 < 0)
						{
							iVar6 = *(int*)(iVar3 + 0x50) + -1;
						}
					}
					else
					{
						iVar6 = 0;
					}
				} while (*(int*)(iVar6 * 0x110 + 0x174 + iVar3) == 0);
			}
			else
			{
				if (*(int*)(iVar3 + 0x4c) < 2)
					goto LAB_6fad6252;
				iVar6 = *(int*)(iVar3 + 0x44);
				do
				{
					iVar6 = iVar6 + -1;
					if (iVar6 < *(int*)(iVar3 + 0x50))
					{
						if (iVar6 < 0)
						{
							iVar6 = *(int*)(iVar3 + 0x50) + -1;
						}
					}
					else
					{
						iVar6 = 0;
					}
				} while (*(int*)(iVar6 * 0x110 + 0x174 + iVar3) == 0);
			}
			sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
			*(int*)(iVar3 + 0x44) = iVar6;
		}
	}
LAB_6fad6252:
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
}

//D2Client.0x6FAD6270
void __cdecl sub_6FAD6270(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int iVar1;
	DWORD DVar2;

	iVar1 = dword_6FBB3644;
	if (dword_6FBB3644 != 0)
	{
		DVar2 = GetTickCount();
		if (DVar2 < *(int*)iVar1 + 0x50U)
		{
			pSMSGHANDLER_PARAMS->bUseResult = 1;
			pSMSGHANDLER_PARAMS->lResult = 0;
			SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
			return;
		}
	}
	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	D2_ASSERT(dword_6FBB3644);
	if ((4 < *(uint32_t*)(dword_6FBB3644 + 0x54)) && (*(code**)(dword_6FBB3644 + 0x60) != nullptr))
	{
		(**(code**)(dword_6FBB3644 + 0x60))();
		sub_6FB238B0();
	}
}

//D2Client.0x6FAD6300
void __cdecl sub_6FAD6300(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	int iVar2;
	int iVar3;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar2 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	piVar1 = *(int**)(dword_6FBB3644 + 0xb08);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			if (1 < *(int*)(iVar2 + 0x4c))
			{
				iVar3 = *(int*)(iVar2 + 0x44);
				do
				{
					iVar3 = iVar3 + -1;
					if (iVar3 < *(int*)(iVar2 + 0x50))
					{
						if (iVar3 < 0)
						{
							iVar3 = *(int*)(iVar2 + 0x50) + -1;
						}
					}
					else
					{
						iVar3 = 0;
					}
				} while (*(int*)(iVar3 * 0x110 + 0x174 + iVar2) == 0);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				*(int*)(iVar2 + 0x44) = iVar3;
			}
			return;
		}
		if (((int*)*piVar1 != nullptr) &&
		    (iVar3 = (**(code**)(*(int*)*piVar1 + 0x24))(pSMSGHANDLER_PARAMS), iVar3 == 1))
			break;
		piVar1 = (int*)piVar1[1];
	}
}

//D2Client.0x6FAD63C0
void __cdecl sub_6FAD63C0(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	int iVar2;
	int iVar3;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar2 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	piVar1 = *(int**)(dword_6FBB3644 + 0xb08);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			if (1 < *(int*)(iVar2 + 0x4c))
			{
				iVar3 = *(int*)(iVar2 + 0x44);
				do
				{
					iVar3 = iVar3 + 1;
					if (iVar3 < *(int*)(iVar2 + 0x50))
					{
						if (iVar3 < 0)
						{
							iVar3 = *(int*)(iVar2 + 0x50) + -1;
						}
					}
					else
					{
						iVar3 = 0;
					}
				} while (*(int*)(iVar3 * 0x110 + 0x174 + iVar2) == 0);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				*(int*)(iVar2 + 0x44) = iVar3;
			}
			return;
		}
		if (((int*)*piVar1 != nullptr) &&
		    (iVar3 = (**(code**)(*(int*)*piVar1 + 0x28))(pSMSGHANDLER_PARAMS), iVar3 == 1))
			break;
		piVar1 = (int*)piVar1[1];
	}
}

//D2Client.0x6FAD6480
void __cdecl sub_6FAD6480(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	int iVar2;
	int iVar3;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar2 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	piVar1 = *(int**)(dword_6FBB3644 + 0xb08);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			if (1 < *(int*)(iVar2 + 0x4c))
			{
				iVar3 = *(int*)(iVar2 + 0x44);
				do
				{
					iVar3 = iVar3 + -1;
					if (iVar3 < *(int*)(iVar2 + 0x50))
					{
						if (iVar3 < 0)
						{
							iVar3 = *(int*)(iVar2 + 0x50) + -1;
						}
					}
					else
					{
						iVar3 = 0;
					}
				} while (*(int*)(iVar3 * 0x110 + 0x174 + iVar2) == 0);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				*(int*)(iVar2 + 0x44) = iVar3;
			}
			return;
		}
		if (((int*)*piVar1 != nullptr) &&
		    (iVar3 = (**(code**)(*(int*)*piVar1 + 0x1c))(pSMSGHANDLER_PARAMS), iVar3 == 1))
			break;
		piVar1 = (int*)piVar1[1];
	}
}

//D2Client.0x6FAD6540
void __cdecl sub_6FAD6540(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	int iVar2;
	int iVar3;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar2 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	piVar1 = *(int**)(dword_6FBB3644 + 0xb08);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			if (1 < *(int*)(iVar2 + 0x4c))
			{
				iVar3 = *(int*)(iVar2 + 0x44);
				do
				{
					iVar3 = iVar3 + 1;
					if (iVar3 < *(int*)(iVar2 + 0x50))
					{
						if (iVar3 < 0)
						{
							iVar3 = *(int*)(iVar2 + 0x50) + -1;
						}
					}
					else
					{
						iVar3 = 0;
					}
				} while (*(int*)(iVar3 * 0x110 + 0x174 + iVar2) == 0);
				sub_6FB55820(1, nullptr, 0.0, 0.0, 0);
				*(int*)(iVar2 + 0x44) = iVar3;
			}
			return;
		}
		if (((int*)*piVar1 != nullptr) &&
		    (iVar3 = (**(code**)(*(int*)*piVar1 + 0x20))(pSMSGHANDLER_PARAMS), iVar3 == 1))
			break;
		piVar1 = (int*)piVar1[1];
	}
}

//D2Client.0x6FAD6600
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD6600(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	code* pcVar1;
	bool bVar2;
	uint32_t extraout_var;
	uint32_t uVar3;
	uint32_t extraout_var_00;
	int iVar4;
	int iVar5;
	int* piVar6;

	pSMSGHANDLER_PARAMS->bUseResult = 1;
	pSMSGHANDLER_PARAMS->lResult = 0;
	SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	iVar4 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	if (4 < *(uint32_t*)(dword_6FBB3644 + 0x54))
	{
		if (*(int*)(dword_6FBB3644 + 0x20) == 0)
		{
			bVar2 = sub_6FAD4F00(5, 1);
			if ((D2C_ZEXT(bVar2) != 0) && (uVar3 = sub_6FAD4B60(5, 1), (short)uVar3 == 0xd))
			{
				return;
			}
			bVar2 = sub_6FAD4F00(5, 0);
			if ((D2C_ZEXT(bVar2) != 0) && (uVar3 = sub_6FAD4B60(5, 0), (short)uVar3 == 0xd))
			{
				return;
			}
		}
		iVar5 = *(int*)(iVar4 + 0x44);
		if ((iVar5 < 0) || (*(int*)(iVar4 + 0x50) <= iVar5))
		{
			iVar5 = 0;
			if (0 < *(int*)(iVar4 + 0x50))
			{
				piVar6 = (int*)(iVar4 + 0x174);
				while (*piVar6 == 0)
				{
					iVar5 = iVar5 + 1;
					piVar6 = piVar6 + 0x44;
					if (*(int*)(iVar4 + 0x50) <= iVar5)
					{
						return;
					}
				}
				*(int*)(iVar4 + 0x44) = iVar5;
			}
		}
		else
		{
			pcVar1 = *(code**)(iVar5 * 0x110 + 0x170 + iVar4);
			if ((pcVar1 != nullptr) && (iVar4 = (*pcVar1)(), iVar4 == 1))
			{
				sub_6FB238B0();
				return;
			}
		}
	}
}

//D2Client.0x6FAD6700
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD6700(SMSGHANDLER_PARAMS* pSMSGHANDLER_PARAMS)
{
	int* piVar1;
	uint32_t uVar2;
	int iVar3;
	bool bVar4;
	int iVar5;
	uint32_t extraout_var;
	uint32_t uVar6;
	uint32_t extraout_var_00;
	int* piVar7;
	DWORD DVar8;

	iVar3 = dword_6FBB3644;
	D2_ASSERT(dword_6FBB3644);
	piVar7 = (int*)dword_6FBB3644;
	for (piVar1 = *(int**)(dword_6FBB3644 + 0xb08); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
	{
		if (((int*)*piVar1 != nullptr) &&
		    (iVar5 = (**(code**)(*(int*)*piVar1 + 0x18))(pSMSGHANDLER_PARAMS), piVar7 = (int*)dword_6FBB3644,
		        iVar5 != 0))
		{
			return;
		}
	}
	uVar2 = pSMSGHANDLER_PARAMS->wParam;
	if ((*(int*)(iVar3 + 0x20) != 0) ||
	    (((bVar4 = sub_6FAD4F00(5, 1), D2C_ZEXT(bVar4) == 0 ||
	                                       (uVar6 = sub_6FAD4B60(5, 1), (uVar6 & 0xffff) != uVar2)) &&
	        ((bVar4 = sub_6FAD4F00(5, 0), piVar7 = (int*)dword_6FBB3644,
	            D2C_ZEXT(bVar4) == 0 ||
	                (uVar6 = sub_6FAD4B60(5, 0), piVar7 = (int*)dword_6FBB3644, (uVar6 & 0xffff) != uVar2))))))
	{
		if (pSMSGHANDLER_PARAMS->wParam == 0xd)
		{
			sub_6FAD6600(pSMSGHANDLER_PARAMS);
			return;
		}
		if (pSMSGHANDLER_PARAMS->wParam == 0x1b)
		{
			if ((piVar7 == nullptr) || (DVar8 = GetTickCount(), *piVar7 + 0x50U <= DVar8))
			{
				pSMSGHANDLER_PARAMS->bUseResult = 1;
				pSMSGHANDLER_PARAMS->lResult = 0;
				SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
				D2_ASSERT(dword_6FBB3644);
				if (*(uint32_t*)(dword_6FBB3644 + 0x54) < 5)
				{
					return;
				}
				if (*(code**)(dword_6FBB3644 + 0x60) == nullptr)
				{
					return;
				}
				(**(code**)(dword_6FBB3644 + 0x60))();
				sub_6FB238B0();
				return;
			}
		}
		else if (*(int*)(iVar3 + 0x18) != 1)
		{
			return;
		}
		pSMSGHANDLER_PARAMS->lResult = 0;
		pSMSGHANDLER_PARAMS->bUseResult = 1;
		SMsgBreakHandlerChain(pSMSGHANDLER_PARAMS);
	}
}

//D2Client.0x6FAD6860
void __cdecl sub_6FAD6860()
{
	dword_6FBB3648 = 0;
}

//D2Client.0x6FAD6870
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD6870()
{
	void* pvVar1;
	void* pFree;
	bool bVar2;
	HWND__* pHVar3;
	uint32_t extraout_var;
	uint32_t uVar4;

	pFree = (void*)dword_6FBB3644;
	if (dword_6FBB3648 != 0)
	{
		uVar4 = 0xe;
		pHVar3 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78DF8), uVar4);
		bVar2 = sub_6FAAB290();
		if (D2C_ZEXT(bVar2) != 0)
		{
			uVar4 = 1;
			pHVar3 = WINDOW_GetWindow();
			WNDPROC_UnregisterMessageHandlers(pHVar3, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78EA0), uVar4);
		}
		dword_6FBB363C = dword_6FBB363C + -1;
		pFree = (void*)dword_6FBB3644;
	}
	while (pFree != nullptr)
	{
		pvVar1 = *(void**)((int)pFree + 0xb0c);
		D2_FREE(pFree);
		pFree = pvVar1;
	}
	dword_6FBB3644 = 0;
}

//D2Client.0x6FAD68F0
void __fastcall sub_6FAD68F0(int a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
	uint32_t uVar1;
	void* pvVar2;

	D2_ASSERT(a1);
	uVar1 = *(uint32_t*)(a1 + 0xb08);
	pvVar2 = D2_ALLOC(8);
	*(void**)(a1 + 0xb08) = pvVar2;
	*(uint32_t*)((int)pvVar2 + 4) = uVar1;
	**(uint32_t**)(a1 + 0xb08) = a2;
}

//D2Client.0x6FAD6950
// TODO: decompilation needs review (extraout)
DWORD* __fastcall sub_6FAD6950(DWORD a1, DWORD a2, int a3, DWORD a4, int a5, DWORD a6)
{
	bool bVar1;
	DWORD* pDVar2;
	DWORD DVar3;
	D2CellFileStrc* pDVar4;
	uint32_t extraout_var;
	uint32_t uVar5;
	uint32_t extraout_var_00;
	HWND__* pHVar6;
	uint32_t extraout_var_01;
	int iVar7;
	DWORD* pDVar8;
	D2GfxDataStrc* pDVar9;
	D2GfxDataStrc DStack_14c;
	char acStack_104[260];

	sub_6FB240D0(0);
	sub_6FAEB9A0(0);
	sub_6FAABF30();
	if (a3 == 0)
	{
		return nullptr;
	}
	if (0 < a5)
	{
		return nullptr;
	}
	dword_6FBB364C = dword_6FBB364C + 1;
	pDVar2 = (DWORD*)D2_ALLOC(0xb10);
	pDVar8 = pDVar2;
	for (iVar7 = 0x2c4; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*pDVar8 = 0;
		pDVar8 = pDVar8 + 1;
	}
	pDVar2[0x2c3] = dword_6FBB3644;
	pDVar8 = pDVar2;
	dword_6FBB3644 = (int)pDVar2;
	for (iVar7 = 0x2c4; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*pDVar8 = 0;
		pDVar8 = pDVar8 + 1;
	}
	pDVar2[0xd] = 0;
	pDVar2[0xe] = 0;
	pDVar2[0x14] = 0;
	pDVar2[0x13] = 0;
	pDVar2[0x11] = 0xffffffff;
	pDVar2[0x17] = 2;
	pDVar2[0xb] = 0;
	pDVar2[0xc] = 0;
	pDVar2[0x2c2] = 0;
	pDVar2[0x18] = a3;
	pDVar2[0x19] = a4;
	pDVar2[0x16] = 0;
	pDVar2[5] = 0;
	DVar3 = GetTickCount();
	*pDVar2 = DVar3;
	pDVar2[0x12] = 0xffffffff;
	pDVar2[4] = 0;
	pDVar2[6] = a6;
	pDVar2[0x15] = 0;
	pDVar2[3] = 1;
	sprintf(acStack_104, "%s\\ui\\menu\\%s", "DATA\\GLOBAL",
	    (&ptr_6FB78EC0)[a5]);
	pDVar4 = CLIENT_LoadCellFile(acStack_104, 0);
	pDVar2[2] = (DWORD)pDVar4;
	pDVar9 = &DStack_14c;
	for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		pDVar9->pCurrentCell = nullptr;
		pDVar9 = (D2GfxDataStrc*)&pDVar9->pCellFile;
	}
	DStack_14c.pCellFile = (D2CellFileStrc*)pDVar2[2];
	DStack_14c.nDirection = 0;
	DStack_14c.nFrame = 0;
	pDVar4 = D2CMP_CelGetHandle(&DStack_14c);
	D2_ASSERT(pDVar4 != nullptr);
	DVar3 = D2CMP_CelGetWidth(pDVar4);
	pDVar2[0xd] = DVar3;
	DVar3 = D2CMP_CelGetHeight(pDVar4);
	pDVar2[0xe] = DVar3;
	pDVar2[10] = a2;
	pDVar2[9] = a1;
	pDVar2[0xb] = a1;
	pDVar2[0xc] = a2;
	dword_6FBB3648 = 1;
	bVar1 = sub_6FAD4F00(0x26, 1);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar5 = sub_6FAD4B60(0x26, 1);
		if (((uint16_t)uVar5 != 0xffff) && ((uint16_t)uVar5 < 0xe0))
		{
			byte_6FB78DFC = uVar5 & 0xffff;
		}
	}
	bVar1 = sub_6FAD4F00(0x26, 0);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar5 = sub_6FAD4B60(0x26, 0);
		if (((uint16_t)uVar5 != 0xffff) && ((uint16_t)uVar5 < 0xe0))
		{
			byte_6FB78E08 = uVar5 & 0xffff;
		}
	}
	uVar5 = 0xe;
	pHVar6 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar6, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78DF8), uVar5);
	bVar1 = sub_6FAAB290();
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar5 = 1;
		pHVar6 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar6, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78EA0), uVar5);
	}
	dword_6FBB363C = dword_6FBB363C + 1;
	D2_ASSERT(dword_6FBB364C == 1);
	return pDVar2;
}

//D2Client.0x6FAD6BE0
// TODO: decompilation needs review (extraout)
DWORD* __fastcall sub_6FAD6BE0(DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9, DWORD a10, DWORD a11)
{
	bool bVar1;
	DWORD* pDVar2;
	DWORD DVar3;
	uint32_t extraout_var;
	uint32_t uVar4;
	uint32_t extraout_var_00;
	HWND__* pHVar5;
	uint32_t extraout_var_01;
	int iVar6;
	DWORD* pDVar7;

	sub_6FB240D0(0);
	sub_6FAEB9A0(0);
	sub_6FAABF30();
	if (a3 == 0)
	{
		return nullptr;
	}
	dword_6FBB364C = dword_6FBB364C + 1;
	pDVar2 = (DWORD*)D2_ALLOC(0xb10);
	pDVar7 = pDVar2;
	for (iVar6 = 0x2c4; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*pDVar7 = 0;
		pDVar7 = pDVar7 + 1;
	}
	pDVar2[0x2c3] = dword_6FBB3644;
	pDVar7 = pDVar2;
	dword_6FBB3644 = (int)pDVar2;
	for (iVar6 = 0x2c4; iVar6 != 0; iVar6 = iVar6 + -1)
	{
		*pDVar7 = 0;
		pDVar7 = pDVar7 + 1;
	}
	pDVar2[9] = a1;
	pDVar2[0xb] = a1;
	pDVar2[0x18] = a3;
	pDVar2[0x19] = a4;
	pDVar2[0x16] = a7;
	pDVar2[0xe] = 0;
	pDVar2[0x14] = 0;
	pDVar2[0x13] = 0;
	pDVar2[0x11] = 0xffffffff;
	pDVar2[0x17] = 2;
	pDVar2[0x2c2] = 0;
	pDVar2[10] = a2;
	pDVar2[0xc] = a2;
	pDVar2[5] = a6;
	pDVar2[7] = a10;
	pDVar2[0xd] = a8;
	DVar3 = GetTickCount();
	*pDVar2 = DVar3;
	pDVar2[4] = 0;
	pDVar2[0x15] = 0;
	pDVar2[3] = 0;
	pDVar2[2] = 0;
	pDVar2[0xe] = a9;
	pDVar2[6] = a5;
	pDVar2[0x12] = 0xffffffff;
	pDVar2[8] = a11;
	dword_6FBB3648 = 1;
	bVar1 = sub_6FAD4F00(0x26, 1);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar4 = sub_6FAD4B60(0x26, 1);
		if (((uint16_t)uVar4 != 0xffff) && ((uint16_t)uVar4 < 0xe0))
		{
			byte_6FB78DFC = uVar4 & 0xffff;
		}
	}
	bVar1 = sub_6FAD4F00(0x26, 0);
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar4 = sub_6FAD4B60(0x26, 0);
		if (((uint16_t)uVar4 != 0xffff) && ((uint16_t)uVar4 < 0xe0))
		{
			byte_6FB78E08 = uVar4 & 0xffff;
		}
	}
	uVar4 = 0xe;
	pHVar5 = WINDOW_GetWindow();
	WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78DF8), uVar4);
	bVar1 = sub_6FAAB290();
	if (D2C_ZEXT(bVar1) != 0)
	{
		uVar4 = 1;
		pHVar5 = WINDOW_GetWindow();
		WNDPROC_RegisterMessageHandlers(pHVar5, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78EA0), uVar4);
	}
	dword_6FBB363C = dword_6FBB363C + 1;
	D2_ASSERT(dword_6FBB364C == 1);
	return pDVar2;
}

//D2Client.0x6FAD6DC0
// TODO: decompilation needs review (extraout)
void __cdecl sub_6FAD6DC0()
{
	void* pvVar1;
	int iVar2;
	void* pFree;
	int pFree_00;
	bool bVar3;
	HWND__* pHVar4;
	uint32_t extraout_var;
	uint32_t uVar5;

	dword_6FBB364C = dword_6FBB364C + -1;
	D2_ASSERT(!dword_6FBB364C);
	sub_6FB240D0(1);
	uVar5 = 0xe;
	pHVar4 = WINDOW_GetWindow();
	WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78DF8), uVar5);
	bVar3 = sub_6FAAB290();
	if (D2C_ZEXT(bVar3) != 0)
	{
		uVar5 = 1;
		pHVar4 = WINDOW_GetWindow();
		WNDPROC_UnregisterMessageHandlers(pHVar4, (const D2WindowMessageHandlerStrc*)((int)&tbl_6FB78EA0), uVar5);
	}
	sub_6FAEB9A0(1);
	sub_6FAB6450(nullptr);
	pFree_00 = dword_6FBB3644;
	dword_6FBB3648 = 0;
	pFree = *(void**)(dword_6FBB3644 + 0xb08);
	while (pFree != nullptr)
	{
		pvVar1 = *(void**)((int)pFree + 4);
		D2_FREE(pFree);
		pFree = pvVar1;
	}
	if ((*(int*)(pFree_00 + 0xc) != 0) &&
	    (*(D2CellFileStrc**)(pFree_00 + 8) != nullptr))
	{
		CLIENT_FreeCellFile(*(D2CellFileStrc**)(pFree_00 + 8));
	}
	iVar2 = *(int*)(pFree_00 + 0xb0c);
	D2_FREE((void*)pFree_00);
	dword_6FBB3644 = iVar2;
}

//D2Client.0x6FAD6EB0
void __fastcall sub_6FAD6EB0(int a1)
{
	int* piVar1;
	Font nFontSize;
	int iVar2;
	int nX;
	D2GfxDataStrc* pDVar3;
	Font* pFVar4;
	int iStack_68;
	int iStack_64;
	Font FStack_60;
	int local_58;
	int local_54;
	int local_50;
	int local_4c;
	D2GfxDataStrc local_48;

	if (a1 != 0)
	{
		pDVar3 = &local_48;
		for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1)
		{
			pDVar3->pCurrentCell = nullptr;
			pDVar3 = (D2GfxDataStrc*)&pDVar3->pCellFile;
		}
		local_48.nDirection = 0;
		local_54 = *(int*)(a1 + 0x30);
		*(int*)(a1 + 0x54) = *(int*)(a1 + 0x54) + 1;
		local_58 = *(int*)(a1 + 0x2c);
		local_50 = *(int*)(a1 + 0x34) + -1 + local_58;
		iVar2 = *(int*)(a1 + 0x38) + local_54;
		local_4c = iVar2 + -1;
		if (*(int*)(a1 + 0xc) == 0)
		{
			sub_6FB5B0F0(local_58, local_54, (local_50 - local_58) + 1, (local_4c - local_54) + 1, 0, (DrawMode)(1));
			sub_6FB21790(&local_58);
		}
		else if (*(D2CellFileStrc**)(a1 + 8) != nullptr)
		{
			local_48.nFrame = 0;
			local_48.pCellFile = *(D2CellFileStrc**)(a1 + 8);
			TEXTURE_CelDraw(&local_48, local_58, iVar2, 0xffffffff, DRAWMODE_NORMAL, nullptr);
		}
		for (piVar1 = *(int**)(a1 + 0xb08); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
		{
			if ((int*)*piVar1 != nullptr)
			{
				(**(code**)(*(int*)*piVar1 + 4))();
			}
		}
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
		iStack_68 = 0;
		iStack_64 = 0;
		if (0 < *(int*)(a1 + 0x50))
		{
			pFVar4 = (Font*)(a1 + 0x168);
			do
			{
				FStack_60 = pFVar4[1];
				D2Win_10127_SetFont(*pFVar4);
				nX = pFVar4[-3] + *(int*)(a1 + 0x2c);
				iVar2 = pFVar4[-4] + *(int*)(a1 + 0x30) + iStack_68;
				if (*(int*)(a1 + 0x44) == iStack_64)
				{
					if (*(int*)(a1 + 0x5c) == 1)
					{
						FStack_60 = D2FONT_FONT42;
					}
					if (*(int*)(a1 + 0x5c) == 2)
					{
						local_48.pCellFile = sub_6FB23880();
						local_48.nFrame = dword_6FBB3640 % 7;
						TEXTURE_CelDraw(&local_48, nX + -0x18, iVar2 + 4, 0xffffffff, DRAWMODE_NORMAL, nullptr);
						TEXTURE_CelDraw(&local_48, pFVar4[-2] + D2FONT_FONT30 + nX, iVar2 + 4, 0xffffffff,
						    DRAWMODE_NORMAL, nullptr);
						dword_6FBB3640 = dword_6FBB3640 + 1;
					}
				}
				D2Win_10117_DrawText((Unicode*)(pFVar4 + -0x40), nX, iVar2, FStack_60, 0);
				iStack_68 = iStack_68 + pFVar4[-4];
				iStack_64 = iStack_64 + 1;
				pFVar4 = pFVar4 + 0x44;
			} while (iStack_64 < *(int*)(a1 + 0x50));
		}
		D2Win_10127_SetFont(nFontSize);
		return;
	}
	FOG_DisplayAssert("pDialog != NULL", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAD7090
void __fastcall sub_6FAD7090(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int* piVar3;

	D2_ASSERT(a1);
	iVar1 = *(int*)(a1 + 0x50);
	D2_ASSERT(iVar1 > a2);
	if (a2 == -1)
	{
		*(uint32_t*)(a1 + 0x44) = 0xffffffff;
		return;
	}
	iVar2 = 0;
	if (0 < iVar1)
	{
		piVar3 = (int*)(a1 + 0x174);
		do
		{
			if (a2 == iVar2)
			{
				if (*piVar3 != 0)
				{
					*(int*)(a1 + 0x44) = a2;
					return;
				}
				FOG_DisplayAssert("pDialog->Line[idx].bSelectable",
				    __FILE__, __LINE__);
				exit(-1);
			}
			iVar2 = iVar2 + 1;
			piVar3 = piVar3 + 0x44;
		} while (iVar2 < iVar1);
	}
	FOG_DisplayAssert("0", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAD7150
void __fastcall sub_6FAD7150(int a1, uint32_t a2)
{
	D2_ASSERT(a1);
	*(uint32_t*)(a1 + 0x5c) = a2;
}

//D2Client.0x6FAD7180
void __fastcall sub_6FAD7180(int a1, Unicode* pUnicode, uint32_t a3, uint32_t a4, int a5, uint32_t a6, int a7, int a8)
{
	int iVar1;
	int iVar2;
	int iVar3;
	Font nFontSize;
	int iStack_10;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	iVar2 = *(int*)(a1 + 0x50);
	D2_ASSERT(9 >= iVar2);
	*(int*)(a1 + 0x50) = iVar2 + 1;
	iVar1 = iVar2 * 0x110 + a1;
	*(uint32_t*)(iVar1 + 0x158) = a3;
	*(uint32_t*)(iVar1 + 0x168) = a6;
	*(uint32_t*)(iVar1 + 0x15c) = 0;
	*(uint32_t*)(iVar1 + 0x164) = a4;
	D2_ASSERT(!((a5 == 3) && (*(int*)(a1 + 0x5c) == 1)));
	*(int*)(iVar1 + 0x16c) = a5;
	*(int*)(iVar1 + 0x170) = a7;
	*(int*)(iVar1 + 0x174) = a8;
	iVar3 = Unicode::strlen(pUnicode);
	iVar3 = iVar3 + 1;
	if (0x77 < iVar3)
	{
		iVar3 = 0x77;
	}
	Unicode::strncpy((Unicode*)(iVar1 + 0x68), pUnicode, iVar3);
	*(uint16_t*)(a1 + 0x68 + (iVar3 + iVar2 * 0x88) * 2) = 0;
	if (a8 != 0)
	{
		*(int*)(a1 + 0x4c) = *(int*)(a1 + 0x4c) + 1;
	}
	if (*(int*)(a1 + 0x58) == 0)
	{
		nFontSize = D2Win_10127_SetFont(D2FONT_FONT16);
		D2Win_10127_SetFont(*(Font*)(iVar1 + 0x168));
		iVar3 = D2Win_10121_GetTextWidth((Unicode*)(iVar1 + 0x68));
		if (iVar3 < *(int*)(a1 + 0x34))
		{
			*(int*)(iVar1 + 0x15c) = ((*(int*)(a1 + 0x34) - iVar3) + 1) / 2 + 1;
		}
		else
		{
			*(uint32_t*)(iVar1 + 0x15c) = 0;
		}
		*(int*)(iVar1 + 0x160) = iVar3;
		D2Win_10127_SetFont(nFontSize);
	}
	else
	{
		sub_6FAD7320(a1);
	}
	iStack_c = *(int*)(a1 + 0x30);
	iStack_10 = *(int*)(a1 + 0x2c);
	iStack_4 = *(int*)(a1 + 0x38) + iStack_c;
	iStack_8 = *(int*)(a1 + 0x34) + iStack_10;
	sub_6FAB6450((uint32_t*)(&iStack_10));
	if ((*(int*)(a1 + 0x44) == -1) && (a8 != 0))
	{
		sub_6FAD7090(a1, iVar2);
	}
}

//D2Client.0x6FAD7320
void __fastcall sub_6FAD7320(int a1)
{
	int* piVar1;
	Font FVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int* piVar6;
	int local_c;
	int iStack_8;

	iVar5 = 0;
	iVar4 = 0;
	local_c = 0;
	D2_ASSERT(*(int*)(a1 + 0x58));
	FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
	iStack_8 = 0;
	iVar3 = 0;
	if (0 < *(int*)(a1 + 0x50))
	{
		piVar6 = (int*)(a1 + 0x174);
		do
		{
			iVar3 = D2Win_10121_GetTextWidth((Unicode*)(piVar6 + -0x43));
			if (local_c < iVar3)
			{
				local_c = iVar3;
			}
			if (*piVar6 == 0)
			{
				iStack_8 = iStack_8 + 1;
			}
			piVar1 = piVar6 + -7;
			piVar6 = piVar6 + 0x44;
			iVar4 = iVar4 + *piVar1;
			iVar5 = iVar5 + 1;
			iVar3 = local_c;
		} while (iVar5 < *(int*)(a1 + 0x50));
	}
	iVar3 = iVar3 + 0x14;
	iVar4 = iVar4 + 0xf;
	D2Win_10127_SetFont(FVar2);
	iVar5 = *(int*)(a1 + 0x24) - iVar3 / 2;
	*(int*)(a1 + 0x2c) = iVar5;
	if (*(int*)(a1 + 0x14) == 0)
	{
		*(int*)(a1 + 0x30) = *(int*)(a1 + 0x28) - iVar4 / 3;
	}
	else
	{
		*(int*)(a1 + 0x30) = *(int*)(a1 + 0x28) + iStack_8 * -0x15;
	}
	if (iVar3 <= gnScreenWidth + -0x50)
	{
		if (iVar4 <= gnScreenHeight + -0x62)
		{
			if (gnScreenWidth + -10 < iVar5 + iVar3)
			{
				*(int*)(a1 + 0x2c) = gnScreenWidth - iVar3;
			}
			if (gnScreenHeight + -0x3a < *(int*)(a1 + 0x30) + iVar4)
			{
				*(int*)(a1 + 0x30) = (gnScreenHeight - iVar4) + -0x30;
			}
			if (*(int*)(a1 + 0x2c) < 0xb)
			{
				*(uint32_t*)(a1 + 0x2c) = 10;
			}
			if (*(int*)(a1 + 0x30) < 0xb)
			{
				*(uint32_t*)(a1 + 0x30) = 10;
			}
			*(int*)(a1 + 0x34) = iVar3;
			*(int*)(a1 + 0x38) = iVar4;
			iStack_8 = 0;
			if (0 < *(int*)(a1 + 0x50))
			{
				piVar6 = (int*)(a1 + 0x15c);
				do
				{
					FVar2 = D2Win_10127_SetFont(D2FONT_FONT16);
					D2Win_10127_SetFont((Font)(piVar6[3]));
					iVar4 = D2Win_10121_GetTextWidth((Unicode*)(piVar6 + -0x3d));
					if (iVar4 < *(int*)(a1 + 0x34))
					{
						*piVar6 = ((*(int*)(a1 + 0x34) - iVar4) + 1) / 2 + 1;
					}
					else
					{
						*piVar6 = 0;
					}
					piVar6[1] = iVar4;
					D2Win_10127_SetFont(FVar2);
					iStack_8 = iStack_8 + 1;
					piVar6 = piVar6 + 0x44;
				} while (iStack_8 < *(int*)(a1 + 0x50));
			}
			return;
		}
		FOG_DisplayAssert("MaxHeight <= DIALOG_MAX_HEIGHT",
		    __FILE__, __LINE__);
		exit(-1);
	}
	FOG_DisplayAssert("MaxWidth <= DIALOG_MAX_WIDTH",
	    __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAD7520
uint32_t __fastcall sub_6FAD7520(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x44);
	}
	return 0xffffffff;
}

//D2Client.0x6FAD7530
int __cdecl sub_6FAD7530()
{
	return dword_6FBB364C;
}

#include "Unit/CUnitEvent.h"

//D2Client.0x6FB2A700
void __fastcall sub_6FB2A700(int a1)
{
	void* pvVar1;
	void* pFree;

	if (a1 != 0)
	{
		pFree = *(void**)(a1 + 0x90);
		while (pFree != nullptr)
		{
			pvVar1 = *(void**)((int)pFree + 0x1c);
			D2_FREE_POOL(*(void**)(a1 + 8), pFree);
			pFree = pvVar1;
		}
		*(uint32_t*)(a1 + 0x90) = 0;
	}
}

//D2Client.0x6FB2A740
uint32_t* __fastcall sub_6FB2A740(int a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
	uint32_t* puVar1;
	int iVar2;
	uint32_t* puVar3;

	if (a1 == 0)
	{
		return nullptr;
	}
	puVar1 = (uint32_t*)
	    D2_ALLOC_POOL(*(void**)(a1 + 8), 0x20);
	puVar3 = puVar1;
	for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1)
	{
		*puVar3 = 0;
		puVar3 = puVar3 + 1;
	}
	puVar1[3] = a3;
	*puVar1 = a2;
	puVar1[4] = a4;
	puVar1[5] = a5;
	puVar1[7] = *(uint32_t*)(a1 + 0x90);
	puVar1[1] = a6;
	puVar1[2] = a7;
	if (*(int*)(a1 + 0x90) != 0)
	{
		*(uint32_t**)(*(int*)(a1 + 0x90) + 0x18) = puVar1;
	}
	*(uint32_t**)(a1 + 0x90) = puVar1;
	return puVar1;
}

//D2Client.0x6FB2A7C0
void __fastcall sub_6FB2A7C0(int a1, int a2, int a3)
{
	void* pvVar1;
	void* pFree;

	if (a1 != 0)
	{
		pvVar1 = *(void**)(a1 + 0x90);
		while (pFree = pvVar1, pFree != nullptr)
		{
			pvVar1 = *(void**)((int)pFree + 0x1c);
			if ((*(int*)((int)pFree + 4) == a2) && (*(int*)((int)pFree + 8) == a3))
			{
				if (*(int*)((int)pFree + 0x18) == 0)
				{
					*(void**)(a1 + 0x90) = pvVar1;
				}
				else
				{
					*(void**)(*(int*)((int)pFree + 0x18) + 0x1c) = pvVar1;
				}
				if (*(int*)((int)pFree + 0x1c) != 0)
				{
					*(uint32_t*)(*(int*)((int)pFree + 0x1c) + 0x18) = *(uint32_t*)((int)pFree + 0x18);
				}
				D2_FREE_POOL(*(void**)(a1 + 8), pFree);
			}
		}
	}
}

//D2Client.0x6FB2A830
uint32_t __fastcall sub_6FB2A830(int a1, int a2, D2UnitStrc* pUnit, uint32_t a4)
{
	int* piVar1;
	int* piVar2;
	uint32_t uVar3;

	uVar3 = 0;
	if (a2 != 0)
	{
		piVar1 = *(int**)(a2 + 0x90);
		while (piVar2 = piVar1, piVar2 != nullptr)
		{
			piVar1 = (int*)piVar2[7];
			if (*piVar2 == a1)
			{
				uVar3 = (*(code*)piVar2[5])(pUnit, a4, piVar2[3], piVar2[4]);
			}
		}
	}
	return uVar3;
}

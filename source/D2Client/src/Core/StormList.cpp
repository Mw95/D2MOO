#include "Core/StormList.h"

//D2Client.0x6FB9A6E8
char str_6FB9A6E8[24] = ".?AUTMESSAGESOURCE@@";

//D2Client.0x6FB6BC43
void __fastcall sub_6FB6BC43(uint32_t* a1)
{
	uint32_t* puVar1;

	puVar1 = a1 + 1;
	*puVar1 = 0;
	a1[2] = 0;
	*puVar1 = (uint32_t)(puVar1);
	*a1 = 0;
	a1[2] = ~(uint32_t)puVar1;
}

//D2Client.0x6FB6BC59
void __fastcall sub_6FB6BC59(int a1)
{
	int* location;

	while (true)
	{
		location = *(int**)(a1 + 8);
		if ((int)location < 1)
		{
			location = nullptr;
		}
		if (location == nullptr)
			break;
		sub_6FB6BD6E(location);
		SMemFree(location, str_6FB9A6E8, -2, 0);
	}
}

//D2Client.0x6FB6BC89
uint32_t* __fastcall sub_6FB6BC89(void* pThis, int a2, int a3, uint32_t a4)
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)SMemAlloc(a3 + 0xc, str_6FB9A6E8, -2, a4 | 8);
	if (puVar1 == nullptr)
	{
		puVar1 = nullptr;
	}
	else
	{
		*puVar1 = 0;
		puVar1[1] = 0;
	}
	if (a2 != 0)
	{
		sub_6FB6BCD8(pThis, (int)puVar1, a2, 0);
	}
	return puVar1;
}

//D2Client.0x6FB6BCD8
void __fastcall sub_6FB6BCD8(void* pThis, int a2, int a3, int a4)
{
	uint32_t uVar1;
	int* piVar2;
	uint32_t* puVar3;
	int* piVar4;
	int iVar5;

	if (a2 == 0)
	{
		piVar4 = (int*)((int)pThis + 4);
	}
	else
	{
		piVar4 = (int*)(*(uint32_t*)(pThis) + a2);
	}
	if (*piVar4 != 0)
	{
		sub_6FB6BD6E(piVar4);
	}
	if (a4 == 0)
	{
		piVar2 = (int*)((int)pThis + 4);
	}
	else
	{
		piVar2 = (int*)(*(uint32_t*)(pThis) + a4);
	}
	if (a3 == 1)
	{
		*piVar4 = (int)piVar2;
		piVar4[1] = piVar2[1];
		uVar1 = piVar2[1];
		iVar5 = *(uint32_t*)(pThis);
		if ((int)uVar1 < 0)
		{
			puVar3 = (uint32_t*)~uVar1;
		}
		else
		{
			if (iVar5 < 0)
			{
				iVar5 = (int)piVar2 - *(int*)(*piVar2 + 4);
			}
			puVar3 = (uint32_t*)(uVar1 + iVar5);
		}
		*puVar3 = (uint32_t)(piVar4);
		piVar2[1] = a2;
	}
	else
	{
		iVar5 = *piVar2;
		*piVar4 = iVar5;
		piVar4[1] = *(int*)(iVar5 + 4);
		*(int*)(iVar5 + 4) = a2;
		*piVar2 = (int)piVar4;
	}
}

//D2Client.0x6FB6BD51
void __fastcall sub_6FB6BD51(int* a1)
{
	while (0 < a1[2])
	{
		sub_6FB6BD6E((int*)(*a1 + a1[2]));
	}
}

//D2Client.0x6FB6BD6E
void __fastcall sub_6FB6BD6E(int* a1)
{
	int iVar1;
	uint32_t uVar2;
	int* piVar3;

	iVar1 = *a1;
	if (iVar1 != 0)
	{
		uVar2 = a1[1];
		if ((int)uVar2 < 0)
		{
			piVar3 = (int*)~uVar2;
		}
		else
		{
			piVar3 = (int*)((int)a1 + (uVar2 - *(int*)(iVar1 + 4)));
		}
		*piVar3 = iVar1;
		*(int*)(*a1 + 4) = a1[1];
		*a1 = 0;
		a1[1] = 0;
	}
}

//D2Client.0x6FB6BD9A
int32_t __fastcall sub_6FB6BD9A(SIZE_T a1)
{
	return (int32_t)(VirtualAlloc((LPVOID)0x0, a1, 0x3000, 0x40));
}

//D2Client.0x6FB6BDAB
void __fastcall sub_6FB6BDAB(LPVOID a1)
{
	VirtualFree(a1, 0, 0x8000);
}

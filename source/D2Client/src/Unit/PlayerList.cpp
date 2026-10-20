#include "Unit/PlayerList.h"

#include "Game/Roster.h"

//D2Client.0x6FB4B7C0
int32_t __cdecl sub_6FB4B7C0()
{
	uint32_t* puVar1;

	puVar1 = (uint32_t*)D2_ALLOC(4);
	D2_ASSERT(puVar1 != nullptr);
	*puVar1 = 0;
	return 0;
}

//D2Client.0x6FB4B800
void __fastcall sub_6FB4B800(int* a1)
{
	void* pvVar1;
	void* pFree;

	if (a1 != nullptr)
	{
		pFree = (void*)*a1;
		while (pFree != nullptr)
		{
			pvVar1 = *(void**)((int)pFree + 8);
			D2_FREE(pFree);
			pFree = pvVar1;
		}
		D2_FREE(a1);
	}
}

//D2Client.0x6FB4B840
void __fastcall sub_6FB4B840(int a1, int a2)
{
	int* piVar1;
	uint32_t* puVar2;
	int* piVar3;

	piVar1 = (int*)sub_6FAB0D80(a1);
	if ((piVar1 != nullptr) && (a1 != a2))
	{
		puVar2 = (uint32_t*)sub_6FAB0D80(a1);
		if (puVar2 != nullptr)
		{
			for (piVar3 = (int*)*puVar2; piVar3 != nullptr; piVar3 = (int*)piVar3[2])
			{
				if (*piVar3 == a2)
				{
					return;
				}
			}
		}
		piVar3 = (int*)D2_ALLOC(0xc);
		*piVar3 = 0;
		piVar3[1] = 0;
		piVar3[2] = 0;
		*piVar3 = a2;
		piVar3[2] = *piVar1;
		*piVar1 = (int)piVar3;
	}
}

//D2Client.0x6FB4B8A0
void __fastcall sub_6FB4B8A0(int a1, int a2, uint32_t a3, int a4)
{
	int* piVar1;

	piVar1 = (int*)sub_6FAB0D80(a1);
	if (((piVar1 != nullptr) && (a1 != a2)) &&
	    (piVar1 = (int*)*piVar1, piVar1 != nullptr))
	{
		while (*piVar1 != a2)
		{
			piVar1 = (int*)piVar1[2];
			if (piVar1 == nullptr)
			{
				return;
			}
		}
		if (a4 != 0)
		{
			piVar1[1] = piVar1[1] | a3;
			return;
		}
		piVar1[1] = piVar1[1] & ~a3;
	}
}

//D2Client.0x6FB4B900
uint32_t __fastcall sub_6FB4B900(int a1, int a2, uint32_t a3)
{
	int* piVar1;
	uint32_t* puVar2;

	puVar2 = (uint32_t*)sub_6FAB0D80(a1);
	if ((puVar2 != nullptr) && (a1 != a2))
	{
		for (piVar1 = (int*)*puVar2; piVar1 != nullptr; piVar1 = (int*)piVar1[2])
		{
			if (*piVar1 == a2)
			{
				return piVar1[1] & a3;
			}
		}
	}
	return 0;
}

//D2Client.0x6FB4B940
void __fastcall sub_6FB4B940(int a1, int a2, uint32_t a3)
{
	int* piVar1;

	piVar1 = (int*)sub_6FAB0D80(a1);
	if (((piVar1 != nullptr) && (a1 != a2)) &&
	    (piVar1 = (int*)*piVar1, piVar1 != nullptr))
	{
		while (*piVar1 != a2)
		{
			piVar1 = (int*)piVar1[2];
			if (piVar1 == nullptr)
			{
				return;
			}
		}
		*(uint16_t*)(piVar1 + 1) = 0;
		piVar1[1] = piVar1[1] | a3;
	}
}

#include "Game/Roster.h"

#include "Draw/DWall.h"
#include "Game/Msg.h"
#include "Game/RosterPets.h"
#include "UI/Party.h"
#include "Unit/CUnit.h"
#include "Unit/PlayerList.h"

//D2Client.0x6FBAB994
int32_t dword_6FBAB994;
//D2Client.0x6FBAB998
uint32_t* gpuint32_t_6FBAB998;
//D2Client.0x6FBAB99C
int16_t* gpint16_t_6FBAB99C;

//D2Client.0x6FAAEC80
void __fastcall sub_6FAAEC80(int a1, uint32_t a2, uint8_t* a3, uint16_t a4, uint16_t a5, uint32_t a6, uint32_t a7, uint16_t a8, char* a9, char* a10)
{
	uint32_t* puVar1;
	uint8_t bVar2;
	char cVar3;
	int iVar4;
	uint32_t* puVar5;
	uint8_t* pbVar6;
	uint32_t uVar7;
	uint32_t* puVar8;
	uint32_t uVar9;
	uint8_t* pbVar10;
	char* pcVar11;
	D2UnitStrc* pDVar12;
	int iVar13;
	short* psVar14;
	short sVar15;
	uint8_t* pbVar16;
	uint32_t uVar17;
	bool bVar18;

	D2_ASSERT(a1 != -1);
	pbVar10 = (uint8_t*)dword_6FBAB994;
	if (dword_6FBAB994 != 0)
	{
		do
		{
			pbVar6 = pbVar10;
			pbVar16 = a3;
			if (*(int*)(pbVar10 + 0x10) == a1)
			{
			LAB_6faaed33:
				pbVar6 = a3;
				do
				{
					bVar2 = *pbVar6;
					pbVar6[(int)pbVar10 - (int)a3] = bVar2;
					pbVar6 = pbVar6 + 1;
				} while (bVar2 != 0);
				*(uint16_t*)(pbVar10 + 0x22) = a5;
				*(uint32_t*)(pbVar10 + 0x1c) = a2;
				*(uint16_t*)(pbVar10 + 0x20) = a4;
				*(uint32_t*)(pbVar10 + 0x30) = a7;
				*(int*)(pbVar10 + 0x10) = a1;
				*(uint16_t*)(pbVar10 + 0x44) = a8;
				pcVar11 = a9;
				do
				{
					cVar3 = *pcVar11;
					pcVar11[(int)(pbVar10 + (0x46 - (int)a9))] = cVar3;
					pcVar11 = pcVar11 + 1;
				} while (cVar3 != '\0');
				iVar4 = 0x4a - (int)a10;
				do
				{
					cVar3 = *a10;
					a10[(int)(pbVar10 + iVar4)] = cVar3;
					a10 = a10 + 1;
				} while (cVar3 != '\0');
				if (*a9 == '\0')
				{
					iVar4 = 0x66 - (int)a3;
					do
					{
						bVar2 = *a3;
						a3[(int)(pbVar10 + iVar4)] = bVar2;
						a3 = a3 + 1;
					} while (bVar2 != 0);
				}
				else
				{
					sprintf((char*)(pbVar10 + 0x66), "%s {%s}", a3, a9);
				}
				pDVar12 = CUNIT_GetPlayer();
				if (pDVar12 == nullptr)
				{
					uVar17 = 0xffffffff;
				}
				else
				{
					uVar17 = pDVar12->dwUnitId;
				}
				iVar4 = dword_6FBAB994;
				if (uVar17 == 0xffffffff)
				{
				LAB_6faaee06:
					sVar15 = -1;
				}
				else
				{
					while (true)
					{
						if (iVar4 == 0)
							goto LAB_6faaee06;
						if ((*(uint32_t*)(iVar4 + 0x10) == uVar17) ||
						    (iVar13 = sub_6FAAF050(iVar4, uVar17), iVar13 != 0))
							break;
						iVar4 = *(int*)(iVar4 + 0x80);
					}
					sVar15 = *(short*)(iVar4 + 0x22);
				}
				while (dword_6FBAB994 != 0)
				{
					psVar14 = (short*)sub_6FAAF740(*(short*)(dword_6FBAB994 + 0x22));
					sub_6FAAF7D0(psVar14);
				}
				dword_6FBAB994 = 0;
				for (psVar14 = gpint16_t_6FBAB99C; psVar14 != nullptr; psVar14 = *(short**)(psVar14 + 4))
				{
					uVar7 = sub_6FAA6990();
					if (uVar7 == 0)
					{
						uVar9 = sub_6FAAF600(*(uint8_t**)(psVar14 + 2));
					}
					else
					{
						uVar9 = sub_6FAAF6C0((int)*(uint8_t**)(psVar14 + 2));
					}
					*(uint32_t*)(psVar14 + 2) = uVar9;
				}
				sub_6FAAF830();
				sub_6FAAF890(uVar17, sVar15);
				sub_6FAAFA90();
				sub_6FAAF790();
				if (sVar15 == -1)
				{
					sub_6FAAFAE0(uVar17);
					sub_6FB01CB0();
					return;
				}
				goto LAB_6faaf02e;
			}
			do
			{
				bVar2 = *pbVar6;
				bVar18 = bVar2 < *pbVar16;
				if (bVar2 != *pbVar16)
				{
				LAB_6faaecf4:
					iVar4 = (1 - (uint32_t)bVar18) - (uint32_t)(bVar18 != 0);
					goto LAB_6faaecf9;
				}
				if (bVar2 == 0)
					break;
				bVar2 = pbVar6[1];
				bVar18 = bVar2 < pbVar16[1];
				if (bVar2 != pbVar16[1])
					goto LAB_6faaecf4;
				pbVar6 = pbVar6 + 2;
				pbVar16 = pbVar16 + 2;
			} while (bVar2 != 0);
			iVar4 = 0;
		LAB_6faaecf9:
			if (iVar4 == 0)
				goto LAB_6faaed33;
			pbVar10 = *(uint8_t**)(pbVar10 + 0x80);
		} while (pbVar10 != nullptr);
	}
	puVar5 = nullptr;
	puVar8 = gpuint32_t_6FBAB998;
	if (gpuint32_t_6FBAB998 != nullptr)
	{
		do
		{
			if (puVar8[4] == a1)
			{
				if (puVar8 != nullptr)
				{
					if (puVar5 == nullptr)
					{
						gpuint32_t_6FBAB998 = (uint32_t*)puVar8[0x20];
						puVar8[0x20] = 0;
					}
					else
					{
						puVar5[0x20] = puVar8[0x20];
						puVar8[0x20] = 0;
					}
					goto LAB_6faaeef2;
				}
				break;
			}
			puVar1 = puVar8 + 0x20;
			puVar5 = puVar8;
			puVar8 = (uint32_t*)*puVar1;
		} while ((uint32_t*)*puVar1 != nullptr);
	}
	puVar8 = (uint32_t*)D2_ALLOC(0x84);
	puVar5 = puVar8;
	for (iVar4 = 0x21; iVar4 != 0; iVar4 = iVar4 + -1)
	{
		*puVar5 = 0;
		puVar5 = puVar5 + 1;
	}
LAB_6faaeef2:
	uVar9 = sub_6FB4B7C0();
	puVar8[0xd] = uVar9;
	pbVar10 = a3;
	do
	{
		bVar2 = *pbVar10;
		pbVar10[(int)puVar8 - (int)a3] = bVar2;
		pbVar10 = pbVar10 + 1;
	} while (bVar2 != 0);
	puVar8[7] = a2;
	puVar8[0xc] = a7;
	*(uint16_t*)(puVar8 + 8) = a4;
	*(uint16_t*)((int)puVar8 + 0x22) = a5;
	*(uint16_t*)(puVar8 + 0x11) = a8;
	puVar8[4] = a1;
	pcVar11 = a9;
	do
	{
		cVar3 = *pcVar11;
		pcVar11[(int)puVar8 + (0x46 - (int)a9)] = cVar3;
		pcVar11 = pcVar11 + 1;
	} while (cVar3 != '\0');
	iVar4 = 0x4a - (int)a10;
	do
	{
		cVar3 = *a10;
		a10[(int)puVar8 + iVar4] = cVar3;
		a10 = a10 + 1;
	} while (cVar3 != '\0');
	if (*a9 == '\0')
	{
		iVar4 = 0x66 - (int)a3;
		do
		{
			bVar2 = *a3;
			a3[(int)puVar8 + iVar4] = bVar2;
			a3 = a3 + 1;
		} while (bVar2 != 0);
	}
	else
	{
		sprintf((char*)((int)puVar8 + 0x66), "%s {%s}", a3, a9);
	}
	puVar8[0x20] = dword_6FBAB994;
	dword_6FBAB994 = (int)puVar8;
	pDVar12 = CUNIT_GetPlayer();
	if (pDVar12 == nullptr)
	{
		uVar17 = 0xffffffff;
	}
	else
	{
		uVar17 = pDVar12->dwUnitId;
	}
	iVar4 = dword_6FBAB994;
	if (uVar17 != 0xffffffff)
	{
		for (; iVar4 != 0; iVar4 = *(int*)(iVar4 + 0x80))
		{
			if ((*(uint32_t*)(iVar4 + 0x10) == uVar17) || (iVar13 = sub_6FAAF050(iVar4, uVar17), iVar13 != 0))
			{
				sVar15 = *(short*)(iVar4 + 0x22);
				goto joined_r0x6faaefed;
			}
		}
	}
	sVar15 = -1;
joined_r0x6faaefed:
	while (dword_6FBAB994 != 0)
	{
		psVar14 = (short*)sub_6FAAF740(*(short*)(dword_6FBAB994 + 0x22));
		sub_6FAAF7D0(psVar14);
	}
	sub_6FAAF900();
	sub_6FAAF890(uVar17, sVar15);
	sub_6FAAFA90();
	sub_6FAAF790();
	if (sVar15 == -1)
	{
		sub_6FAAFAE0(uVar17);
	}
LAB_6faaf02e:
	sub_6FB01CB0();
}

//D2Client.0x6FAAF050
uint32_t __fastcall sub_6FAAF050(int a1, int a2)
{
	int* piVar1;

	piVar1 = *(int**)(a1 + 0x38);
	while (true)
	{
		if (piVar1 == nullptr)
		{
			return 0;
		}
		if (*piVar1 == a2)
			break;
		piVar1 = (int*)piVar1[1];
	}
	return 1;
}

//D2Client.0x6FAAF070
void __fastcall sub_6FAAF070(int a1, uint16_t a2, uint16_t a3, uint32_t a4, uint32_t a5)
{
	int* piVar1;
	uint32_t* puVar2;
	D2UnitStrc* pDVar3;
	short* psVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	short* psVar7;
	int iVar8;
	short* psVar9;
	int iVar10;
	uint32_t uVar11;
	int iVar12;
	short sVar13;

	if ((a1 != -1) && (iVar8 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar8 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar8 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6faaf0af;
			}
			iVar8 = *(int*)(iVar8 + 0x80);
			if (iVar8 == 0)
			{
				return;
			}
		}
	LAB_6faaf0af:
		for (piVar1 = *(int**)(iVar8 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
		{
			if (*piVar1 == a1)
			{
				return;
			}
		}
		*(uint16_t*)(iVar8 + 0x22) = a2;
		*(uint16_t*)(iVar8 + 0x20) = a3;
		*(uint32_t*)(iVar8 + 0x30) = a5;
		sub_6FAB19A0();
		pDVar3 = CUNIT_GetPlayer();
		if (pDVar3 == nullptr)
		{
			uVar11 = 0xffffffff;
		}
		else
		{
			uVar11 = pDVar3->dwUnitId;
		}
		iVar8 = dword_6FBAB994;
		if (uVar11 != 0xffffffff)
		{
			for (; iVar8 != 0; iVar8 = *(int*)(iVar8 + 0x80))
			{
				if (*(uint32_t*)(iVar8 + 0x10) == uVar11)
				{
				LAB_6faaf162:
					sVar13 = *(short*)(iVar8 + 0x22);
					goto joined_r0x6faaf129;
				}
				for (puVar2 = *(uint32_t**)(iVar8 + 0x38); puVar2 != nullptr; puVar2 = (uint32_t*)puVar2[1])
				{
					if (*puVar2 == uVar11)
						goto LAB_6faaf162;
				}
			}
		}
		sVar13 = -1;
	joined_r0x6faaf129:
		while (dword_6FBAB994 != 0)
		{
			psVar4 = (short*)sub_6FAAF740(*(short*)(dword_6FBAB994 + 0x22));
			sub_6FAAF7D0(psVar4);
		}
		dword_6FBAB994 = 0;
		for (psVar4 = gpint16_t_6FBAB99C; psVar4 != nullptr; psVar4 = *(short**)(psVar4 + 4))
		{
			uVar5 = sub_6FAA6990();
			if (uVar5 == 0)
			{
				uVar6 = sub_6FAAF600(*(uint8_t**)(psVar4 + 2));
			}
			else
			{
				uVar6 = sub_6FAAF6C0((int)*(uint8_t**)(psVar4 + 2));
			}
			*(uint32_t*)(psVar4 + 2) = uVar6;
		}
		sub_6FAAF830();
		psVar4 = gpint16_t_6FBAB99C;
		psVar9 = nullptr;
		if (sVar13 != -1)
		{
			while (psVar7 = psVar4, psVar7 != nullptr)
			{
				if (*psVar7 == sVar13)
				{
					if (psVar9 != nullptr)
					{
						*(uint32_t*)(psVar9 + 4) = *(uint32_t*)(psVar7 + 4);
						*(short**)(psVar7 + 4) = gpint16_t_6FBAB99C;
						gpint16_t_6FBAB99C = psVar7;
					}
					iVar8 = *(int*)(psVar7 + 2);
					iVar12 = 0;
					goto LAB_6faaf1bd;
				}
				psVar9 = psVar7;
				psVar4 = *(short**)(psVar7 + 4);
			}
		}
	LAB_6faaf1f2:
		iVar8 = 0;
		for (psVar4 = gpint16_t_6FBAB99C; psVar4 != nullptr; psVar4 = *(short**)(psVar4 + 4))
		{
			if (iVar8 == 0)
			{
				dword_6FBAB994 = *(int*)(psVar4 + 2);
				iVar8 = *(int*)(psVar4 + 2);
			}
			else
			{
				*(uint32_t*)(iVar8 + 0x80) = *(uint32_t*)(psVar4 + 2);
			}
			psVar4[2] = 0;
			psVar4[3] = 0;
			if (iVar8 != 0)
			{
				iVar12 = *(int*)(iVar8 + 0x80);
				while (iVar10 = iVar12, iVar10 != 0)
				{
					iVar8 = iVar10;
					iVar12 = *(int*)(iVar10 + 0x80);
				}
			}
		}
		sub_6FAAF790();
		if (sVar13 == -1)
		{
			sub_6FAAFAE0(uVar11);
		}
		sub_6FB01CB0();
	}
	return;
LAB_6faaf1bd:
	iVar10 = iVar8;
	if (iVar10 == 0)
		goto LAB_6faaf1f2;
	if (*(uint32_t*)(iVar10 + 0x10) == uVar11)
	{
		if (iVar12 != 0)
		{
			*(uint32_t*)(iVar12 + 0x80) = *(uint32_t*)(iVar10 + 0x80);
			*(uint32_t*)(iVar10 + 0x80) = *(uint32_t*)(psVar7 + 2);
			*(int*)(psVar7 + 2) = iVar10;
		}
		goto LAB_6faaf1f2;
	}
	iVar8 = *(int*)(iVar10 + 0x80);
	iVar12 = iVar10;
	goto LAB_6faaf1bd;
}

//D2Client.0x6FAAF260
void __fastcall sub_6FAAF260(int a1)
{
	short sVar1;
	uint32_t* puVar2;
	void* pvVar3;
	D2UnitStrc* pDVar4;
	short* psVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	short* psVar8;
	int iVar9;
	short* psVar10;
	int iVar11;
	uint32_t uVar12;
	void* pFree;
	int iVar13;
	short sVar14;
	void* pvVar15;

	pvVar3 = (void*)dword_6FBAB994;
	if (a1 == -1)
	{
		FOG_DisplayWarning("dwUnitId != INVALID_PLAYER_ID",
		    __FILE__, __LINE__);
	}
	pvVar15 = nullptr;
	if (pvVar3 != nullptr)
	{
	LAB_6faaf290:
		pFree = pvVar3;
		if (*(int*)((int)pFree + 0x10) != a1)
			goto code_r0x6faaf295;
		if (pvVar15 == nullptr)
		{
			dword_6FBAB994 = *(int*)((int)pFree + 0x80);
		}
		else
		{
			*(uint32_t*)((int)pvVar15 + 0x80) = *(uint32_t*)((int)pFree + 0x80);
		}
		sub_6FB4B800(*(int**)((int)pFree + 0x34));
		*(uint32_t*)((int)pFree + 0x34) = 0;
		pvVar3 = *(void**)((int)pFree + 0x38);
		while (pvVar3 != nullptr)
		{
			pvVar15 = *(void**)((int)pvVar3 + 4);
			D2_FREE(pvVar3);
			pvVar3 = pvVar15;
		}
		*(uint32_t*)((int)pFree + 0x38) = 0;
		D2_FREE(pFree);
	}
LAB_6faaf301:
	pDVar4 = CUNIT_GetPlayer();
	if (pDVar4 == nullptr)
	{
		uVar12 = 0xffffffff;
	}
	else
	{
		uVar12 = pDVar4->dwUnitId;
	}
	iVar9 = dword_6FBAB994;
	if (uVar12 != 0xffffffff)
	{
		for (; iVar9 != 0; iVar9 = *(int*)(iVar9 + 0x80))
		{
			if (*(uint32_t*)(iVar9 + 0x10) == uVar12)
			{
			LAB_6faaf3c4:
				sVar14 = *(short*)(iVar9 + 0x22);
				goto joined_r0x6faaf353;
			}
			for (puVar2 = *(uint32_t**)(iVar9 + 0x38); puVar2 != nullptr; puVar2 = (uint32_t*)puVar2[1])
			{
				if (*puVar2 == uVar12)
					goto LAB_6faaf3c4;
			}
		}
	}
	sVar14 = -1;
joined_r0x6faaf353:
	while (dword_6FBAB994 != 0)
	{
		sVar1 = *(short*)(dword_6FBAB994 + 0x22);
		psVar5 = sub_6FAAF720(sVar1);
		if (psVar5 == nullptr)
		{
			psVar5 = (short*)D2_ALLOC(0xc);
			psVar5[0] = 0;
			psVar5[1] = 0;
			psVar5[2] = 0;
			psVar5[3] = 0;
			psVar5[4] = 0;
			psVar5[5] = 0;
			*psVar5 = sVar1;
			*(short**)(psVar5 + 4) = gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = psVar5;
		}
		sub_6FAAF7D0(psVar5);
	}
	dword_6FBAB994 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
	{
		uVar6 = sub_6FAA6990();
		if (uVar6 == 0)
		{
			uVar7 = sub_6FAAF600(*(uint8_t**)(psVar5 + 2));
		}
		else
		{
			uVar7 = sub_6FAAF6C0((int)*(uint8_t**)(psVar5 + 2));
		}
		*(uint32_t*)(psVar5 + 2) = uVar7;
	}
	sub_6FAAF830();
	psVar5 = gpint16_t_6FBAB99C;
	psVar10 = nullptr;
	if (sVar14 != -1)
	{
		while (psVar8 = psVar5, psVar8 != nullptr)
		{
			if (*psVar8 == sVar14)
			{
				if (psVar10 != nullptr)
				{
					*(uint32_t*)(psVar10 + 4) = *(uint32_t*)(psVar8 + 4);
					*(short**)(psVar8 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar8;
				}
				iVar9 = *(int*)(psVar8 + 2);
				iVar13 = 0;
				goto LAB_6faaf41f;
			}
			psVar10 = psVar8;
			psVar5 = *(short**)(psVar8 + 4);
		}
	}
LAB_6faaf454:
	iVar9 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar10 = gpint16_t_6FBAB99C, psVar5 != nullptr;
	     psVar5 = *(short**)(psVar5 + 4))
	{
		if (iVar9 == 0)
		{
			dword_6FBAB994 = *(int*)(psVar5 + 2);
			iVar9 = *(int*)(psVar5 + 2);
		}
		else
		{
			*(uint32_t*)(iVar9 + 0x80) = *(uint32_t*)(psVar5 + 2);
		}
		psVar5[2] = 0;
		psVar5[3] = 0;
		if (iVar9 != 0)
		{
			iVar13 = *(int*)(iVar9 + 0x80);
			while (iVar11 = iVar13, iVar11 != 0)
			{
				iVar9 = iVar11;
				iVar13 = *(int*)(iVar11 + 0x80);
			}
		}
	}
	while (psVar10 != nullptr)
	{
		psVar5 = *(short**)(psVar10 + 4);
		D2_FREE(psVar10);
		psVar10 = psVar5;
	}
	gpint16_t_6FBAB99C = nullptr;
	if (sVar14 == -1)
	{
		sub_6FAAFAE0(uVar12);
	}
	sub_6FB01CB0();
	return;
code_r0x6faaf295:
	pvVar3 = *(void**)((int)pFree + 0x80);
	pvVar15 = pFree;
	if (*(void**)((int)pFree + 0x80) == nullptr)
		goto LAB_6faaf301;
	goto LAB_6faaf290;
LAB_6faaf41f:
	iVar11 = iVar9;
	if (iVar11 == 0)
		goto LAB_6faaf454;
	if (*(uint32_t*)(iVar11 + 0x10) == uVar12)
	{
		if (iVar13 != 0)
		{
			*(uint32_t*)(iVar13 + 0x80) = *(uint32_t*)(iVar11 + 0x80);
			*(uint32_t*)(iVar11 + 0x80) = *(uint32_t*)(psVar8 + 2);
			*(int*)(psVar8 + 2) = iVar11;
		}
		goto LAB_6faaf454;
	}
	iVar9 = *(int*)(iVar11 + 0x80);
	iVar13 = iVar11;
	goto LAB_6faaf41f;
}

//D2Client.0x6FAAF4E0
void __cdecl sub_6FAAF4E0()
{
	void* pvVar1;
	void* pvVar2;
	uint32_t* puVar3;
	void* pFree;
	uint32_t* pFree_00;
	void* pvVar4;

	pvVar4 = (void*)dword_6FBAB994;
	if (dword_6FBAB994 != 0)
	{
		do
		{
			pvVar1 = *(void**)((int)pvVar4 + 0x80);
			sub_6FB4B800(*(int**)((int)pvVar4 + 0x34));
			*(uint32_t*)((int)pvVar4 + 0x34) = 0;
			pFree = *(void**)((int)pvVar4 + 0x38);
			while (pFree != nullptr)
			{
				pvVar2 = *(void**)((int)pFree + 4);
				D2_FREE(pFree);
				pFree = pvVar2;
			}
			*(uint32_t*)((int)pvVar4 + 0x38) = 0;
			D2_FREE(pvVar4);
			pvVar4 = pvVar1;
		} while (pvVar1 != nullptr);
	}
	dword_6FBAB994 = 0;
	pFree_00 = gpuint32_t_6FBAB998;
	while (pFree_00 != nullptr)
	{
		puVar3 = (uint32_t*)pFree_00[0x20];
		sub_6FB4B800((int*)pFree_00[0xd]);
		pFree_00[0xd] = 0;
		pvVar4 = (void*)pFree_00[0xe];
		while (pvVar4 != nullptr)
		{
			pvVar1 = *(void**)((int)pvVar4 + 4);
			D2_FREE(pvVar4);
			pvVar4 = pvVar1;
		}
		pFree_00[0xe] = 0;
		D2_FREE(pFree_00);
		pFree_00 = puVar3;
	}
	gpuint32_t_6FBAB998 = nullptr;
}

//D2Client.0x6FAAF5B0
uint32_t __fastcall sub_6FAAF5B0(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x80);
	}
	return dword_6FBAB994;
}

//D2Client.0x6FAAF5D0
int __fastcall sub_6FAAF5D0(int a1)
{
	if (a1 == 0)
	{
		FOG_DisplayWarning("ptRoster", __FILE__, __LINE__);
	}
	return a1 + 0x66;
}

//D2Client.0x6FAAF600
int32_t __fastcall sub_6FAAF600(uint8_t* a1)
{
	uint8_t* pbVar1;
	uint8_t bVar2;
	uint8_t* pbVar3;
	uint8_t* pbVar4;
	int iVar5;
	uint8_t* pbVar6;
	uint8_t* pbVar7;
	uint8_t* pbVar8;
	bool bVar9;
	uint8_t* local_c;
	uint8_t* local_8;

	local_8 = nullptr;
	local_c = a1;
	if (a1 == nullptr)
	{
		return 0;
	}
LAB_6faaf619:
	pbVar1 = local_c + 0x80;
	pbVar3 = *(uint8_t**)pbVar1;
	pbVar4 = local_c;
	pbVar7 = local_8;
	pbVar8 = local_8;
	pbVar6 = nullptr;
	if (local_8 != nullptr)
	{
	LAB_6faaf633:
		do
		{
			bVar2 = *pbVar4;
			bVar9 = bVar2 < *pbVar7;
			if (bVar2 == *pbVar7)
			{
				if (bVar2 != 0)
				{
					bVar2 = pbVar4[1];
					bVar9 = bVar2 < pbVar7[1];
					if (bVar2 != pbVar7[1])
						goto LAB_6faaf657;
					pbVar4 = pbVar4 + 2;
					pbVar7 = pbVar7 + 2;
					if (bVar2 != 0)
						goto LAB_6faaf633;
				}
				iVar5 = 0;
			}
			else
			{
			LAB_6faaf657:
				iVar5 = (1 - (uint32_t)bVar9) - (uint32_t)(bVar9 != 0);
			}
			if ((iVar5 < 0) ||
			    (pbVar7 = *(uint8_t**)(pbVar8 + 0x80), pbVar4 = local_c, pbVar6 = pbVar8, pbVar8 = pbVar7,
			        pbVar7 == nullptr))
				goto LAB_6faaf66c;
		} while (true);
	}
	goto LAB_6faaf694;
LAB_6faaf66c:
	if (pbVar6 == nullptr)
	{
	LAB_6faaf694:
		*(uint8_t**)pbVar1 = local_8;
		local_8 = local_c;
	}
	else
	{
		*(uint32_t*)pbVar1 = *(uint32_t*)(pbVar6 + 0x80);
		*(uint8_t**)(pbVar6 + 0x80) = local_c;
	}
	local_c = pbVar3;
	if (pbVar3 == nullptr)
	{
		return 0;
	}
	goto LAB_6faaf619;
}

//D2Client.0x6FAAF6C0
int32_t __fastcall sub_6FAAF6C0(int a1)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int iVar5;
	int iVar6;

	iVar4 = 0;
	if (a1 != 0)
	{
		do
		{
			piVar1 = (int*)(a1 + 0x80);
			iVar2 = *piVar1;
			if (iVar4 == 0)
			{
			LAB_6faaf704:
				*piVar1 = iVar4;
			}
			else
			{
				iVar3 = iVar4;
				iVar6 = 0;
				do
				{
					iVar5 = iVar3;
					if (*(int*)(iVar5 + 0x18) < *(int*)(a1 + 0x18))
						break;
					iVar3 = *(int*)(iVar5 + 0x80);
					iVar6 = iVar5;
				} while (*(int*)(iVar5 + 0x80) != 0);
				if (iVar6 == 0)
					goto LAB_6faaf704;
				*piVar1 = *(int*)(iVar6 + 0x80);
				*(int*)(iVar6 + 0x80) = a1;
				a1 = iVar4;
			}
			iVar4 = a1;
			a1 = iVar2;
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAAF720
short* __fastcall sub_6FAAF720(short a1)
{
	short* psVar1;

	psVar1 = gpint16_t_6FBAB99C;
	if (gpint16_t_6FBAB99C != nullptr)
	{
		do
		{
			if (*psVar1 == a1)
			{
				return psVar1;
			}
			psVar1 = *(short**)(psVar1 + 4);
		} while (psVar1 != nullptr);
	}
	return nullptr;
}

//D2Client.0x6FAAF740
int32_t __fastcall sub_6FAAF740(short a1)
{
	short* psVar1;

	psVar1 = gpint16_t_6FBAB99C;
	if (gpint16_t_6FBAB99C != nullptr)
	{
		do
		{
			if (*psVar1 == a1)
			{
				return 0;
			}
			psVar1 = *(short**)(psVar1 + 4);
		} while (psVar1 != nullptr);
	}
	psVar1 = (short*)D2_ALLOC(0xc);
	psVar1[0] = 0;
	psVar1[1] = 0;
	psVar1[2] = 0;
	psVar1[3] = 0;
	psVar1[4] = 0;
	psVar1[5] = 0;
	*psVar1 = a1;
	*(short**)(psVar1 + 4) = gpint16_t_6FBAB99C;
	gpint16_t_6FBAB99C = psVar1;
	return 0;
}

//D2Client.0x6FAAF790
void __cdecl sub_6FAAF790()
{
	short* psVar1;
	short* pFree;

	pFree = gpint16_t_6FBAB99C;
	if (gpint16_t_6FBAB99C != nullptr)
	{
		do
		{
			psVar1 = *(short**)(pFree + 4);
			D2_FREE(pFree);
			pFree = psVar1;
		} while (psVar1 != nullptr);
	}
	gpint16_t_6FBAB99C = nullptr;
}

//D2Client.0x6FAAF7D0
void __fastcall sub_6FAAF7D0(short* a1)
{
	int* piVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar4 = 0;
	iVar2 = dword_6FBAB994;
	if (dword_6FBAB994 != 0)
	{
		do
		{
			if (*(short*)(iVar2 + 0x22) == *a1)
			{
				piVar1 = (int*)(iVar2 + 0x80);
				iVar3 = *piVar1;
				if (iVar4 == 0)
				{
					dword_6FBAB994 = iVar3;
					*piVar1 = *(int*)(a1 + 2);
					*(int*)(a1 + 2) = iVar2;
				}
				else
				{
					*(int*)(iVar4 + 0x80) = iVar3;
					*piVar1 = *(int*)(a1 + 2);
					*(int*)(a1 + 2) = iVar2;
				}
			}
			else
			{
				iVar3 = *(int*)(iVar2 + 0x80);
				iVar4 = iVar2;
			}
			iVar2 = iVar3;
		} while (iVar3 != 0);
	}
}

//D2Client.0x6FAAF830
void __cdecl sub_6FAAF830()
{
	uint16_t* puVar1;
	uint16_t* puVar2;
	uint16_t* puVar3;
	uint16_t* puVar4;
	uint16_t* puVar5;

	puVar4 = nullptr;
	puVar5 = puVar4;
	if (gpint16_t_6FBAB99C != nullptr)
	{
		do
		{
			puVar5 = (uint16_t*)gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = *(short**)(puVar5 + 4);
			if (puVar4 == nullptr)
			{
			LAB_6faaf86c:
				*(uint16_t**)(puVar5 + 4) = puVar4;
			}
			else
			{
				puVar1 = puVar4;
				puVar3 = nullptr;
				do
				{
					puVar2 = puVar1;
					if (*puVar5 < *puVar2)
						break;
					puVar1 = *(uint16_t**)(puVar2 + 4);
					puVar3 = puVar2;
				} while (*(uint16_t**)(puVar2 + 4) != nullptr);
				if (puVar3 == nullptr)
					goto LAB_6faaf86c;
				*(uint32_t*)(puVar5 + 4) = *(uint32_t*)(puVar3 + 4);
				*(uint16_t**)(puVar3 + 4) = puVar5;
				puVar5 = puVar4;
			}
			puVar4 = puVar5;
		} while ((uint16_t*)gpint16_t_6FBAB99C != nullptr);
	}
	gpint16_t_6FBAB99C = (short*)puVar5;
}

//D2Client.0x6FAAF890
void __fastcall sub_6FAAF890(int a1, short a2)
{
	short* psVar1;
	int iVar2;
	short* psVar3;
	int iVar4;
	short* psVar5;
	int iVar6;

	psVar1 = gpint16_t_6FBAB99C;
	psVar5 = nullptr;
	if (a2 != -1)
	{
		while (psVar3 = psVar1, psVar3 != nullptr)
		{
			if (*psVar3 == a2)
			{
				if (psVar5 != nullptr)
				{
					*(uint32_t*)(psVar5 + 4) = *(uint32_t*)(psVar3 + 4);
					*(short**)(psVar3 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar3;
				}
				iVar2 = *(int*)(psVar3 + 2);
				iVar6 = 0;
				while (true)
				{
					iVar4 = iVar2;
					if (iVar4 == 0)
					{
						return;
					}
					if (*(int*)(iVar4 + 0x10) == a1)
						break;
					iVar2 = *(int*)(iVar4 + 0x80);
					iVar6 = iVar4;
				}
				if (iVar6 == 0)
				{
					return;
				}
				*(uint32_t*)(iVar6 + 0x80) = *(uint32_t*)(iVar4 + 0x80);
				*(uint32_t*)(iVar4 + 0x80) = *(uint32_t*)(psVar3 + 2);
				*(int*)(psVar3 + 2) = iVar4;
				return;
			}
			psVar5 = psVar3;
			psVar1 = *(short**)(psVar3 + 4);
		}
	}
}

//D2Client.0x6FAAF900
void __cdecl sub_6FAAF900()
{
	int* piVar1;
	uint8_t* pbVar2;
	uint8_t bVar3;
	int iVar4;
	uint8_t* pbVar5;
	uint16_t* puVar6;
	uint8_t* pbVar7;
	uint16_t* puVar8;
	int iVar9;
	int iVar10;
	uint16_t* puVar11;
	uint32_t uVar12;
	int iVar13;
	uint8_t* pbVar14;
	int iVar15;
	uint16_t* puVar16;
	int iVar17;
	uint16_t* puVar18;
	uint8_t* pbVar19;
	uint8_t* pbVar20;
	uint8_t* pbVar21;
	bool bVar22;
	short* local_10;
	uint8_t* local_8;

	local_10 = gpint16_t_6FBAB99C;
	if (gpint16_t_6FBAB99C != nullptr)
	{
	LAB_6faaf918:
		uVar12 = sub_6FAA6990();
		if (uVar12 != 0)
		{
			iVar15 = 0;
			iVar9 = *(int*)(local_10 + 2);
		joined_r0x6faaf92e:
			do
			{
				if (iVar9 == 0)
					goto LAB_6faaf976;
				piVar1 = (int*)(iVar9 + 0x80);
				iVar4 = *piVar1;
				if (iVar15 != 0)
				{
					iVar10 = iVar15;
					iVar17 = 0;
					do
					{
						iVar13 = iVar10;
						if (*(int*)(iVar13 + 0x18) < *(int*)(iVar9 + 0x18))
							break;
						iVar10 = *(int*)(iVar13 + 0x80);
						iVar17 = iVar13;
					} while (*(int*)(iVar13 + 0x80) != 0);
					if (iVar17 != 0)
					{
						*piVar1 = *(int*)(iVar17 + 0x80);
						*(int*)(iVar17 + 0x80) = iVar9;
						iVar9 = iVar4;
						goto joined_r0x6faaf92e;
					}
				}
				*piVar1 = iVar15;
				iVar15 = iVar9;
				iVar9 = iVar4;
			} while (true);
		}
		local_8 = nullptr;
		pbVar5 = *(uint8_t**)(local_10 + 2);
	joined_r0x6faaf991:
		pbVar7 = pbVar5;
		if (pbVar7 != nullptr)
		{
			pbVar2 = pbVar7 + 0x80;
			pbVar5 = *(uint8_t**)pbVar2;
			pbVar14 = pbVar7;
			pbVar20 = local_8;
			pbVar21 = local_8;
			pbVar19 = nullptr;
			if (local_8 != nullptr)
			{
			LAB_6faaf9af:
				do
				{
					bVar3 = *pbVar14;
					bVar22 = bVar3 < *pbVar20;
					if (bVar3 == *pbVar20)
					{
						if (bVar3 != 0)
						{
							bVar3 = pbVar14[1];
							bVar22 = bVar3 < pbVar20[1];
							if (bVar3 != pbVar20[1])
								goto LAB_6faaf9d3;
							pbVar14 = pbVar14 + 2;
							pbVar20 = pbVar20 + 2;
							if (bVar3 != 0)
								goto LAB_6faaf9af;
						}
						iVar15 = 0;
					}
					else
					{
					LAB_6faaf9d3:
						iVar15 = (1 - (uint32_t)bVar22) - (uint32_t)(bVar22 != 0);
					}
					if ((iVar15 < 0) ||
					    (pbVar20 = *(uint8_t**)(pbVar21 + 0x80), pbVar14 = pbVar7, pbVar19 = pbVar21,
					        pbVar21 = pbVar20, pbVar20 == nullptr))
						goto LAB_6faaf9e8;
				} while (true);
			}
			goto LAB_6faafa0c;
		}
		*(uint8_t**)(local_10 + 2) = local_8;
		goto LAB_6faafa29;
	}
LAB_6faafa3e:
	puVar8 = nullptr;
	do
	{
		while (true)
		{
			if ((uint16_t*)gpint16_t_6FBAB99C == nullptr)
			{
				gpint16_t_6FBAB99C = (short*)puVar8;
				return;
			}
			puVar6 = *(uint16_t**)((uint16_t*)gpint16_t_6FBAB99C + 4);
			if (puVar8 != nullptr)
				break;
		LAB_6faafa73:
			*(uint16_t**)((uint16_t*)gpint16_t_6FBAB99C + 4) = puVar8;
			puVar8 = (uint16_t*)gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = (short*)puVar6;
		}
		puVar11 = puVar8;
		puVar18 = nullptr;
		do
		{
			puVar16 = puVar11;
			if ((uint16_t)*gpint16_t_6FBAB99C < *puVar16)
				break;
			puVar11 = *(uint16_t**)(puVar16 + 4);
			puVar18 = puVar16;
		} while (*(uint16_t**)(puVar16 + 4) != nullptr);
		if (puVar18 == nullptr)
			goto LAB_6faafa73;
		*(uint32_t*)((uint16_t*)gpint16_t_6FBAB99C + 4) = *(uint32_t*)(puVar18 + 4);
		*(short**)(puVar18 + 4) = gpint16_t_6FBAB99C;
		gpint16_t_6FBAB99C = (short*)puVar6;
	} while (true);
LAB_6faaf9e8:
	if (pbVar19 == nullptr)
	{
	LAB_6faafa0c:
		*(uint8_t**)pbVar2 = local_8;
		local_8 = pbVar7;
	}
	else
	{
		*(uint32_t*)pbVar2 = *(uint32_t*)(pbVar19 + 0x80);
		*(uint8_t**)(pbVar19 + 0x80) = pbVar7;
	}
	goto joined_r0x6faaf991;
LAB_6faaf976:
	*(int*)(local_10 + 2) = iVar15;
LAB_6faafa29:
	local_10 = *(short**)(local_10 + 4);
	if (local_10 == nullptr)
		goto LAB_6faafa3e;
	goto LAB_6faaf918;
}

//D2Client.0x6FAAFA90
void __cdecl sub_6FAAFA90()
{
	int iVar1;
	int iVar2;
	int iVar3;
	short* psVar4;

	iVar3 = 0;
	psVar4 = gpint16_t_6FBAB99C;
	if (gpint16_t_6FBAB99C != nullptr)
	{
		do
		{
			if (iVar3 == 0)
			{
				dword_6FBAB994 = *(int*)(psVar4 + 2);
				iVar3 = *(int*)(psVar4 + 2);
			}
			else
			{
				*(uint32_t*)(iVar3 + 0x80) = *(uint32_t*)(psVar4 + 2);
			}
			psVar4[2] = 0;
			psVar4[3] = 0;
			if (iVar3 != 0)
			{
				iVar2 = *(int*)(iVar3 + 0x80);
				while (iVar1 = iVar2, iVar1 != 0)
				{
					iVar3 = iVar1;
					iVar2 = *(int*)(iVar1 + 0x80);
				}
			}
			psVar4 = *(short**)(psVar4 + 4);
		} while (psVar4 != nullptr);
	}
}

//D2Client.0x6FAAFAE0
void __fastcall sub_6FAAFAE0(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar3 = 0;
	iVar1 = dword_6FBAB994;
	if (dword_6FBAB994 != 0)
	{
		do
		{
			iVar2 = iVar1;
			if ((*(int*)(iVar2 + 0x10) == a1) && (iVar3 != 0))
			{
				*(uint32_t*)(iVar3 + 0x80) = *(uint32_t*)(iVar2 + 0x80);
				*(int*)(iVar2 + 0x80) = dword_6FBAB994;
				dword_6FBAB994 = iVar2;
			}
			iVar1 = *(int*)(iVar2 + 0x80);
			iVar3 = iVar2;
		} while (*(int*)(iVar2 + 0x80) != 0);
	}
}

//D2Client.0x6FAAFB20
void __fastcall sub_6FAAFB20(int a1, uint32_t a2)
{
	short sVar1;
	int* piVar2;
	uint32_t* puVar3;
	D2UnitStrc* pDVar4;
	short* psVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	short* psVar8;
	int iVar9;
	short* psVar10;
	int iVar11;
	uint32_t uVar12;
	short sVar13;
	int iVar14;

	if ((a1 != -1) && (iVar9 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar9 + 0x10) == a1)
			{
			LAB_6faafb55:
				if ((char)(a2 >> 8) < '\0')
				{
					uVar12 = (a2 & 0xffff) - 0x10000;
				}
				else
				{
					uVar12 = a2 & 0xffff;
				}
				*(uint32_t*)(iVar9 + 0x18) = uVar12;
				pDVar4 = CUNIT_GetPlayer();
				if (pDVar4 == nullptr)
				{
					uVar12 = 0xffffffff;
				}
				else
				{
					uVar12 = pDVar4->dwUnitId;
				}
				iVar9 = dword_6FBAB994;
				if (uVar12 != 0xffffffff)
					goto joined_r0x6faafb91;
				goto LAB_6faafbbc;
			}
			for (piVar2 = *(int**)(iVar9 + 0x38); piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (*piVar2 == a1)
					goto LAB_6faafb55;
			}
			iVar9 = *(int*)(iVar9 + 0x80);
		} while (iVar9 != 0);
	}
	return;
joined_r0x6faafb91:
	if (iVar9 == 0)
		goto LAB_6faafbbc;
	if (*(uint32_t*)(iVar9 + 0x10) == uVar12)
	{
	LAB_6faafc34:
		sVar13 = *(short*)(iVar9 + 0x22);
		goto joined_r0x6faafbc3;
	}
	for (puVar3 = *(uint32_t**)(iVar9 + 0x38); puVar3 != nullptr; puVar3 = (uint32_t*)puVar3[1])
	{
		if (*puVar3 == uVar12)
			goto LAB_6faafc34;
	}
	iVar9 = *(int*)(iVar9 + 0x80);
	goto joined_r0x6faafb91;
LAB_6faafc8f:
	iVar11 = iVar9;
	if (iVar11 == 0)
		goto LAB_6faafcc4;
	if (*(uint32_t*)(iVar11 + 0x10) == uVar12)
	{
		if (iVar14 != 0)
		{
			*(uint32_t*)(iVar14 + 0x80) = *(uint32_t*)(iVar11 + 0x80);
			*(uint32_t*)(iVar11 + 0x80) = *(uint32_t*)(psVar8 + 2);
			*(int*)(psVar8 + 2) = iVar11;
		}
		goto LAB_6faafcc4;
	}
	iVar9 = *(int*)(iVar11 + 0x80);
	iVar14 = iVar11;
	goto LAB_6faafc8f;
LAB_6faafbbc:
	sVar13 = -1;
joined_r0x6faafbc3:
	while (dword_6FBAB994 != 0)
	{
		sVar1 = *(short*)(dword_6FBAB994 + 0x22);
		psVar5 = sub_6FAAF720(sVar1);
		if (psVar5 == nullptr)
		{
			psVar5 = (short*)D2_ALLOC(0xc);
			psVar5[0] = 0;
			psVar5[1] = 0;
			psVar5[2] = 0;
			psVar5[3] = 0;
			psVar5[4] = 0;
			psVar5[5] = 0;
			*psVar5 = sVar1;
			*(short**)(psVar5 + 4) = gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = psVar5;
		}
		sub_6FAAF7D0(psVar5);
	}
	dword_6FBAB994 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
	{
		uVar6 = sub_6FAA6990();
		if (uVar6 == 0)
		{
			uVar7 = sub_6FAAF600(*(uint8_t**)(psVar5 + 2));
		}
		else
		{
			uVar7 = sub_6FAAF6C0((int)*(uint8_t**)(psVar5 + 2));
		}
		*(uint32_t*)(psVar5 + 2) = uVar7;
	}
	sub_6FAAF830();
	psVar5 = gpint16_t_6FBAB99C;
	psVar10 = nullptr;
	if (sVar13 != -1)
	{
		while (psVar8 = psVar5, psVar8 != nullptr)
		{
			if (*psVar8 == sVar13)
			{
				if (psVar10 != nullptr)
				{
					*(uint32_t*)(psVar10 + 4) = *(uint32_t*)(psVar8 + 4);
					*(short**)(psVar8 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar8;
				}
				iVar9 = *(int*)(psVar8 + 2);
				iVar14 = 0;
				goto LAB_6faafc8f;
			}
			psVar10 = psVar8;
			psVar5 = *(short**)(psVar8 + 4);
		}
	}
LAB_6faafcc4:
	iVar9 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
	{
		if (iVar9 == 0)
		{
			dword_6FBAB994 = *(int*)(psVar5 + 2);
			iVar9 = *(int*)(psVar5 + 2);
		}
		else
		{
			*(uint32_t*)(iVar9 + 0x80) = *(uint32_t*)(psVar5 + 2);
		}
		psVar5[2] = 0;
		psVar5[3] = 0;
		if (iVar9 != 0)
		{
			iVar14 = *(int*)(iVar9 + 0x80);
			while (iVar11 = iVar14, iVar11 != 0)
			{
				iVar9 = iVar11;
				iVar14 = *(int*)(iVar11 + 0x80);
			}
		}
	}
	sub_6FAAF790();
	if (sVar13 == -1)
	{
		sub_6FAAFAE0(uVar12);
	}
	sub_6FB01CB0();
}

//D2Client.0x6FAAFD30
uint32_t __fastcall sub_6FAAFD30(int a1)
{
	if (a1 == 0)
	{
		return 0;
	}
	return *(uint32_t*)(a1 + 0x18);
}

//D2Client.0x6FAAFD40
uint16_t __fastcall sub_6FAAFD40(int a1)
{
	uint16_t uVar1;

	uVar1 = 0;
	if (a1 != 0)
	{
		uVar1 = *(uint16_t*)(a1 + 0x20);
	}
	return uVar1;
}

//D2Client.0x6FAAFD50
uint32_t __fastcall sub_6FAAFD50(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x1c);
	}
	return 0;
}

//D2Client.0x6FAAFD60
int __fastcall sub_6FAAFD60(int a1)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a1)
			{
				return iVar2;
			}
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
				{
					return iVar2;
				}
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAAFDA0
short __fastcall sub_6FAAFDA0(int a1)
{
	int iVar1;
	int iVar2;

	iVar2 = 0;
	if ((a1 != 0) && (dword_6FBAB994 != 0))
	{
		iVar1 = dword_6FBAB994;
		do
		{
			if (*(short*)(iVar1 + 0x22) == *(short*)(a1 + 0x22))
			{
				iVar2 = iVar2 + 1;
			}
			iVar1 = *(int*)(iVar1 + 0x80);
		} while (iVar1 != 0);
		if (1 < iVar2)
		{
			return *(short*)(a1 + 0x22);
		}
	}
	return -1;
}

//D2Client.0x6FAAFDE0
uint16_t __fastcall sub_6FAAFDE0(int a1)
{
	int iVar1;
	int* piVar2;
	int iVar3;

	if (((a1 != 0) && (iVar1 = *(int*)(a1 + 0xc), iVar1 != -1)) &&
	    (iVar3 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar3 + 0x10) == iVar1)
			{
			LAB_6faafe1c:
				return *(uint16_t*)(iVar3 + 0x22);
			}
			for (piVar2 = *(int**)(iVar3 + 0x38); piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (*piVar2 == iVar1)
					goto LAB_6faafe1c;
			}
			iVar3 = *(int*)(iVar3 + 0x80);
		} while (iVar3 != 0);
	}
	return 0xffff;
}

//D2Client.0x6FAAFE30
uint32_t __fastcall sub_6FAAFE30(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (a1 == 0)
	{
		return 0;
	}
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		uVar2 = sub_6FB4B900(-1, *(int*)(a1 + 0x10), 1);
		return uVar2;
	}
	uVar2 = sub_6FB4B900(pDVar1->dwUnitId, *(int*)(a1 + 0x10), 1);
	return uVar2;
}

//D2Client.0x6FAAFE70
uint32_t __fastcall sub_6FAAFE70(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (a1 == 0)
	{
		return 0;
	}
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		uVar2 = sub_6FB4B900(-1, *(int*)(a1 + 0x10), 2);
		return uVar2;
	}
	uVar2 = sub_6FB4B900(pDVar1->dwUnitId, *(int*)(a1 + 0x10), 2);
	return uVar2;
}

//D2Client.0x6FAAFEB0
uint32_t __fastcall sub_6FAAFEB0(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (a1 == 0)
	{
		return 0;
	}
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		uVar2 = sub_6FB4B900(-1, *(int*)(a1 + 0x10), 4);
		return uVar2;
	}
	uVar2 = sub_6FB4B900(pDVar1->dwUnitId, *(int*)(a1 + 0x10), 4);
	return uVar2;
}

//D2Client.0x6FAAFEF0
uint32_t __fastcall sub_6FAAFEF0(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	if (a1 != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar2 = 0xffffffff;
		}
		else
		{
			uVar2 = pDVar1->dwUnitId;
		}
		uVar2 = sub_6FB4B900(uVar2, *(int*)(a1 + 0x10), 8);
		if (uVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAAFF30
uint32_t __fastcall sub_6FAAFF30(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x30);
	}
	return 1;
}

//D2Client.0x6FAAFF40
void __fastcall sub_6FAAFF40(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	if (a1 != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		sub_6FB4B840(uVar3, *(int*)(a1 + 0x10));
		uVar2 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 1);
		sub_6FB4B8A0(uVar3, *(int*)(a1 + 0x10), 1, (uint32_t)(uVar2 == 0));
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		uVar3 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 1);
		sub_6FAADAE0(1, *(uint32_t*)(a1 + 0x10), uVar3);
	}
}

//D2Client.0x6FAAFFB0
void __fastcall sub_6FAAFFB0(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	if (a1 != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		sub_6FB4B840(uVar3, *(int*)(a1 + 0x10));
		uVar2 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 2);
		sub_6FB4B8A0(uVar3, *(int*)(a1 + 0x10), 2, (uint32_t)(uVar2 == 0));
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		uVar3 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 2);
		sub_6FAADAE0(2, *(uint32_t*)(a1 + 0x10), uVar3);
	}
}

//D2Client.0x6FAB0020
void __fastcall sub_6FAB0020(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	uint32_t uVar3;

	if (a1 != 0)
	{
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		sub_6FB4B840(uVar3, *(int*)(a1 + 0x10));
		uVar2 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 4);
		sub_6FB4B8A0(uVar3, *(int*)(a1 + 0x10), 4, (uint32_t)(uVar2 == 0));
		pDVar1 = CUNIT_GetPlayer();
		if (pDVar1 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar1->dwUnitId;
		}
		uVar3 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 4);
		sub_6FAADAE0(3, *(uint32_t*)(a1 + 0x10), uVar3);
	}
}

//D2Client.0x6FAB0090
void __fastcall sub_6FAB0090(int a1)
{
	short sVar1;
	uint32_t* puVar2;
	D2UnitStrc* pDVar3;
	short* psVar4;
	uint32_t uVar5;
	short* psVar6;
	int iVar7;
	uint32_t uVar8;
	short* psVar9;
	int iVar10;
	short sVar11;
	uint32_t uVar12;
	int iVar13;

	uVar8 = 0;
	if (a1 == 0)
	{
		return;
	}
	switch (*(uint32_t*)(a1 + 0x30))
	{
	case 0:
		*(uint32_t*)(a1 + 0x30) = 4;
		uVar8 = 6;
		break;
	case 1:
		FOG_DisplayAssert("ptRoster->eButton != PARTYBUTTON_NONE",
		    __FILE__, __LINE__);
		exit(-1);
	case 2:
		uVar8 = 8;
		goto LAB_6fab00f0;
	case 3:
		uVar8 = 9;
	LAB_6fab00f0:
		*(uint32_t*)(a1 + 0x30) = 1;
		break;
	case 4:
		*(uint32_t*)(a1 + 0x30) = 0;
		uVar8 = 7;
	}
	sub_6FAADB20(uVar8, *(uint32_t*)(a1 + 0x10));
	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		uVar12 = 0xffffffff;
	}
	else
	{
		uVar12 = pDVar3->dwUnitId;
	}
	iVar7 = dword_6FBAB994;
	if (uVar12 != 0xffffffff)
	{
		for (; iVar7 != 0; iVar7 = *(int*)(iVar7 + 0x80))
		{
			if (*(uint32_t*)(iVar7 + 0x10) == uVar12)
			{
			LAB_6fab01c5:
				sVar11 = *(short*)(iVar7 + 0x22);
				goto joined_r0x6fab0154;
			}
			for (puVar2 = *(uint32_t**)(iVar7 + 0x38); puVar2 != nullptr; puVar2 = (uint32_t*)puVar2[1])
			{
				if (*puVar2 == uVar12)
					goto LAB_6fab01c5;
			}
		}
	}
	sVar11 = -1;
joined_r0x6fab0154:
	while (dword_6FBAB994 != 0)
	{
		sVar1 = *(short*)(dword_6FBAB994 + 0x22);
		psVar4 = sub_6FAAF720(sVar1);
		if (psVar4 == nullptr)
		{
			psVar4 = (short*)D2_ALLOC(0xc);
			psVar4[0] = 0;
			psVar4[1] = 0;
			psVar4[2] = 0;
			psVar4[3] = 0;
			psVar4[4] = 0;
			psVar4[5] = 0;
			*psVar4 = sVar1;
			*(short**)(psVar4 + 4) = gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = psVar4;
		}
		sub_6FAAF7D0(psVar4);
	}
	dword_6FBAB994 = 0;
	for (psVar4 = gpint16_t_6FBAB99C; psVar4 != nullptr; psVar4 = *(short**)(psVar4 + 4))
	{
		uVar5 = sub_6FAA6990();
		if (uVar5 == 0)
		{
			uVar8 = sub_6FAAF600(*(uint8_t**)(psVar4 + 2));
		}
		else
		{
			uVar8 = sub_6FAAF6C0((int)*(uint8_t**)(psVar4 + 2));
		}
		*(uint32_t*)(psVar4 + 2) = uVar8;
	}
	sub_6FAAF830();
	psVar4 = gpint16_t_6FBAB99C;
	psVar9 = nullptr;
	if (sVar11 != -1)
	{
		while (psVar6 = psVar4, psVar6 != nullptr)
		{
			if (*psVar6 == sVar11)
			{
				if (psVar9 != nullptr)
				{
					*(uint32_t*)(psVar9 + 4) = *(uint32_t*)(psVar6 + 4);
					*(short**)(psVar6 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar6;
				}
				iVar7 = *(int*)(psVar6 + 2);
				iVar13 = 0;
				goto LAB_6fab0220;
			}
			psVar9 = psVar6;
			psVar4 = *(short**)(psVar6 + 4);
		}
	}
LAB_6fab0255:
	iVar7 = 0;
	for (psVar4 = gpint16_t_6FBAB99C; psVar9 = gpint16_t_6FBAB99C, psVar4 != nullptr;
	     psVar4 = *(short**)(psVar4 + 4))
	{
		if (iVar7 == 0)
		{
			dword_6FBAB994 = *(int*)(psVar4 + 2);
			iVar7 = *(int*)(psVar4 + 2);
		}
		else
		{
			*(uint32_t*)(iVar7 + 0x80) = *(uint32_t*)(psVar4 + 2);
		}
		psVar4[2] = 0;
		psVar4[3] = 0;
		if (iVar7 != 0)
		{
			iVar13 = *(int*)(iVar7 + 0x80);
			while (iVar10 = iVar13, iVar10 != 0)
			{
				iVar7 = iVar10;
				iVar13 = *(int*)(iVar10 + 0x80);
			}
		}
	}
	while (psVar9 != nullptr)
	{
		psVar4 = *(short**)(psVar9 + 4);
		D2_FREE(psVar9);
		psVar9 = psVar4;
	}
	gpint16_t_6FBAB99C = nullptr;
	if (sVar11 == -1)
	{
		iVar7 = 0;
		for (iVar13 = dword_6FBAB994; iVar13 != 0; iVar13 = *(int*)(iVar13 + 0x80))
		{
			if ((*(uint32_t*)(iVar13 + 0x10) == uVar12) && (iVar7 != 0))
			{
				*(uint32_t*)(iVar7 + 0x80) = *(uint32_t*)(iVar13 + 0x80);
				*(int*)(iVar13 + 0x80) = dword_6FBAB994;
				dword_6FBAB994 = iVar13;
			}
			iVar7 = iVar13;
		}
	}
	sub_6FB01CB0();
	return;
LAB_6fab0220:
	iVar10 = iVar7;
	if (iVar10 == 0)
		goto LAB_6fab0255;
	if (*(uint32_t*)(iVar10 + 0x10) == uVar12)
	{
		if (iVar13 != 0)
		{
			*(uint32_t*)(iVar13 + 0x80) = *(uint32_t*)(iVar10 + 0x80);
			*(uint32_t*)(iVar10 + 0x80) = *(uint32_t*)(psVar6 + 2);
			*(int*)(psVar6 + 2) = iVar10;
		}
		goto LAB_6fab0255;
	}
	iVar7 = *(int*)(iVar10 + 0x80);
	iVar13 = iVar10;
	goto LAB_6fab0220;
}

//D2Client.0x6FAB0330
void __cdecl sub_6FAB0330()
{
	uint32_t* puVar1;
	int iVar2;
	D2UnitStrc* pDVar3;
	short* psVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	short* psVar7;
	int iVar8;
	uint32_t uVar9;
	short* psVar10;
	int iVar11;
	int iVar12;
	short sVar13;

	pDVar3 = CUNIT_GetPlayer();
	if (pDVar3 == nullptr)
	{
		uVar9 = 0xffffffff;
	}
	else
	{
		uVar9 = pDVar3->dwUnitId;
	}
	iVar2 = dword_6FBAB994;
	if (uVar9 != 0xffffffff)
	{
		for (; iVar2 != 0; iVar2 = *(int*)(iVar2 + 0x80))
		{
			if (*(uint32_t*)(iVar2 + 0x10) == uVar9)
			{
			LAB_6fab03a0:
				sVar13 = -1;
				*(uint32_t*)(iVar2 + 0x30) = 1;
				*(uint16_t*)(iVar2 + 0x22) = 0xffff;
				pDVar3 = CUNIT_GetPlayer();
				if (pDVar3 == nullptr)
				{
					uVar9 = 0xffffffff;
				}
				else
				{
					uVar9 = pDVar3->dwUnitId;
				}
				if (uVar9 == 0xffffffff)
					goto joined_r0x6fab03fd;
				iVar8 = dword_6FBAB994;
				psVar4 = gpint16_t_6FBAB99C;
				if (dword_6FBAB994 != 0)
					goto LAB_6fab03d4;
				goto joined_r0x6fab0421;
			}
			for (puVar1 = *(uint32_t**)(iVar2 + 0x38); puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[1])
			{
				if (*puVar1 == uVar9)
					goto LAB_6fab03a0;
			}
		}
	}
	FOG_DisplayAssert("ptRoster", __FILE__, __LINE__);
	exit(-1);
LAB_6fab048b:
	iVar11 = iVar8;
	if (iVar11 == 0)
		goto LAB_6fab04c0;
	if (*(uint32_t*)(iVar11 + 0x10) == uVar9)
	{
		if (iVar12 != 0)
		{
			*(uint32_t*)(iVar12 + 0x80) = *(uint32_t*)(iVar11 + 0x80);
			*(uint32_t*)(iVar11 + 0x80) = *(uint32_t*)(psVar7 + 2);
			*(int*)(psVar7 + 2) = iVar11;
		}
		goto LAB_6fab04c0;
	}
	iVar8 = *(int*)(iVar11 + 0x80);
	iVar12 = iVar11;
	goto LAB_6fab048b;
	while (true)
	{
		for (puVar1 = *(uint32_t**)(iVar8 + 0x38); puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[1])
		{
			if (*puVar1 == uVar9)
				goto LAB_6fab03f7;
		}
		iVar8 = *(int*)(iVar8 + 0x80);
		if (iVar8 == 0)
			break;
	LAB_6fab03d4:
		if (*(uint32_t*)(iVar8 + 0x10) == uVar9)
		{
		LAB_6fab03f7:
			sVar13 = *(short*)(iVar8 + 0x22);
			break;
		}
	}
joined_r0x6fab03fd:
	while (psVar4 = gpint16_t_6FBAB99C, dword_6FBAB994 != 0)
	{
		psVar4 = (short*)sub_6FAAF740(*(short*)(dword_6FBAB994 + 0x22));
		sub_6FAAF7D0(psVar4);
	}
joined_r0x6fab0421:
	for (; psVar4 != nullptr; psVar4 = *(short**)(psVar4 + 4))
	{
		uVar5 = sub_6FAA6990();
		if (uVar5 == 0)
		{
			uVar6 = sub_6FAAF600(*(uint8_t**)(psVar4 + 2));
		}
		else
		{
			uVar6 = sub_6FAAF6C0((int)*(uint8_t**)(psVar4 + 2));
		}
		*(uint32_t*)(psVar4 + 2) = uVar6;
	}
	sub_6FAAF830();
	psVar4 = gpint16_t_6FBAB99C;
	psVar10 = nullptr;
	if (sVar13 != -1)
	{
		while (psVar7 = psVar4, psVar7 != nullptr)
		{
			if (*psVar7 == sVar13)
			{
				if (psVar10 != nullptr)
				{
					*(uint32_t*)(psVar10 + 4) = *(uint32_t*)(psVar7 + 4);
					*(short**)(psVar7 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar7;
				}
				iVar8 = *(int*)(psVar7 + 2);
				iVar12 = 0;
				goto LAB_6fab048b;
			}
			psVar10 = psVar7;
			psVar4 = *(short**)(psVar7 + 4);
		}
	}
LAB_6fab04c0:
	iVar8 = 0;
	for (psVar4 = gpint16_t_6FBAB99C; psVar4 != nullptr; psVar4 = *(short**)(psVar4 + 4))
	{
		if (iVar8 == 0)
		{
			dword_6FBAB994 = *(int*)(psVar4 + 2);
			iVar8 = *(int*)(psVar4 + 2);
		}
		else
		{
			*(uint32_t*)(iVar8 + 0x80) = *(uint32_t*)(psVar4 + 2);
		}
		psVar4[2] = 0;
		psVar4[3] = 0;
		if (iVar8 != 0)
		{
			iVar12 = *(int*)(iVar8 + 0x80);
			while (iVar11 = iVar12, iVar11 != 0)
			{
				iVar8 = iVar11;
				iVar12 = *(int*)(iVar11 + 0x80);
			}
		}
	}
	sub_6FAAF790();
	if (sVar13 == -1)
	{
		sub_6FAAFAE0(uVar9);
	}
	sub_6FB01CB0();
	sub_6FAADB20(9, *(uint32_t*)(iVar2 + 0x10));
}

//D2Client.0x6FAB0540
// TODO: decompilation needs review (extraout)
void __fastcall sub_6FAB0540(int a1)
{
	uint32_t* puVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	uint32_t uVar4;
	int iVar5;
	short* psVar6;
	uint32_t uVar7;
	int iVar8;
	int iVar9;
	int extraout_ECX;
	short sVar10;
	uint32_t uVar11;

	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		uVar11 = 0xffffffff;
	}
	else
	{
		uVar11 = pDVar2->dwUnitId;
	}
	if ((a1 != 0) &&
	    ((uVar3 = sub_6FB4B900(uVar11, *(int*)(a1 + 0x10), 8), uVar3 != 0 ||
	                                                               (8 < *(uint16_t*)(a1 + 0x20)))))
	{
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar2->dwUnitId;
		}
		sub_6FB4B840(uVar3, *(int*)(a1 + 0x10));
		uVar4 = sub_6FB4B900(uVar3, *(int*)(a1 + 0x10), 8);
		sub_6FB4B8A0(uVar3, *(int*)(a1 + 0x10), 8, (uint32_t)(uVar4 == 0));
		uVar3 = sub_6FB4B900(uVar11, *(int*)(a1 + 0x10), 8);
		sub_6FAADAE0(4, *(uint32_t*)(a1 + 0x10), uVar3);
		uVar11 = sub_6FB4B900(uVar11, *(int*)(a1 + 0x10), 8);
		if ((uVar11 != 0) && (sVar10 = -1, *(short*)(a1 + 0x22) != -1))
		{
			pDVar2 = CUNIT_GetPlayer();
			if (pDVar2 == nullptr)
			{
				uVar11 = 0xffffffff;
			}
			else
			{
				uVar11 = pDVar2->dwUnitId;
			}
			iVar8 = dword_6FBAB994;
			if (uVar11 != 0xffffffff)
			{
				for (; iVar8 != 0; iVar8 = *(int*)(iVar8 + 0x80))
				{
					if (*(uint32_t*)(iVar8 + 0x10) == uVar11)
					{
					LAB_6fab064b:
						if (*(short*)(iVar8 + 0x22) != *(short*)(a1 + 0x22))
						{
							return;
						}
						pDVar2 = CUNIT_GetPlayer();
						if (pDVar2 == nullptr)
						{
							uVar11 = 0xffffffff;
						}
						else
						{
							uVar11 = pDVar2->dwUnitId;
						}
						iVar8 = dword_6FBAB994;
						if (uVar11 == 0xffffffff)
							goto LAB_6fab069a;
						goto joined_r0x6fab0677;
					}
					for (puVar1 = *(uint32_t**)(iVar8 + 0x38); puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[1])
					{
						if (*puVar1 == uVar11)
							goto LAB_6fab064b;
					}
				}
			}
			FOG_DisplayAssert("ptRoster", __FILE__, __LINE__);
			exit(-1);
		}
	}
	return;
joined_r0x6fab0677:
	if (iVar8 == 0)
	{
	LAB_6fab069a:
		FOG_DisplayAssert("ptRoster", __FILE__, __LINE__);
		exit(-1);
	}
	if (*(uint32_t*)(iVar8 + 0x10) == uVar11)
	{
	LAB_6fab06b8:
		*(uint16_t*)(iVar8 + 0x22) = 0xffff;
		*(uint32_t*)(iVar8 + 0x30) = 1;
		pDVar2 = CUNIT_GetPlayer();
		iVar8 = dword_6FBAB994;
		if (pDVar2 == nullptr)
		{
			uVar11 = 0xffffffff;
		}
		else
		{
			uVar11 = pDVar2->dwUnitId;
		}
		if (uVar11 == 0xffffffff)
			goto joined_r0x6fab0707;
		iVar9 = dword_6FBAB994;
		psVar6 = gpint16_t_6FBAB99C;
		if (dword_6FBAB994 != 0)
			goto LAB_6fab06e5;
		goto joined_r0x6fab072b;
	}
	for (puVar1 = *(uint32_t**)(iVar8 + 0x38); puVar1 != nullptr; puVar1 = (uint32_t*)puVar1[1])
	{
		if (*puVar1 == uVar11)
			goto LAB_6fab06b8;
	}
	iVar8 = *(int*)(iVar8 + 0x80);
	goto joined_r0x6fab0677;
LAB_6fab06e5:
	if ((*(uint32_t*)(iVar9 + 0x10) == uVar11) ||
	    (iVar5 = sub_6FAAF050(iVar9, uVar11), iVar9 = extraout_ECX, iVar5 != 0))
	{
		sVar10 = *(short*)(iVar9 + 0x22);
		goto joined_r0x6fab0707;
	}
	iVar9 = *(int*)(extraout_ECX + 0x80);
	if (iVar9 == 0)
	{
	joined_r0x6fab0707:
		while (psVar6 = gpint16_t_6FBAB99C, iVar8 != 0)
		{
			psVar6 = (short*)sub_6FAAF740(*(short*)(iVar8 + 0x22));
			sub_6FAAF7D0(psVar6);
			iVar8 = dword_6FBAB994;
		}
	joined_r0x6fab072b:
		for (; psVar6 != nullptr; psVar6 = *(short**)(psVar6 + 4))
		{
			uVar3 = sub_6FAA6990();
			if (uVar3 == 0)
			{
				uVar7 = sub_6FAAF600(*(uint8_t**)(psVar6 + 2));
			}
			else
			{
				uVar7 = sub_6FAAF6C0((int)*(uint8_t**)(psVar6 + 2));
			}
			*(uint32_t*)(psVar6 + 2) = uVar7;
		}
		sub_6FAAF830();
		sub_6FAAF890(uVar11, sVar10);
		iVar8 = 0;
		for (psVar6 = gpint16_t_6FBAB99C; psVar6 != nullptr; psVar6 = *(short**)(psVar6 + 4))
		{
			if (iVar8 == 0)
			{
				dword_6FBAB994 = *(int*)(psVar6 + 2);
				iVar8 = *(int*)(psVar6 + 2);
			}
			else
			{
				*(uint32_t*)(iVar8 + 0x80) = *(uint32_t*)(psVar6 + 2);
			}
			psVar6[2] = 0;
			psVar6[3] = 0;
			if (iVar8 != 0)
			{
				iVar9 = *(int*)(iVar8 + 0x80);
				while (iVar5 = iVar9, iVar5 != 0)
				{
					iVar8 = iVar5;
					iVar9 = *(int*)(iVar5 + 0x80);
				}
			}
		}
		sub_6FAAF790();
		if (sVar10 == -1)
		{
			sub_6FAAFAE0(uVar11);
		}
		sub_6FB01CB0();
		return;
	}
	goto LAB_6fab06e5;
}

//D2Client.0x6FAB07D0
bool __fastcall sub_6FAB07D0(int a1, int a2)
{
	int* piVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;

	if ((a1 != -1) && (iVar4 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar4 + 0x10) == a1)
				goto LAB_6fab0806;
			for (piVar1 = *(int**)(iVar4 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0806;
			}
			iVar4 = *(int*)(iVar4 + 0x80);
		} while (iVar4 != 0);
	}
	iVar4 = 0;
LAB_6fab0806:
	if ((a2 != -1) && (iVar3 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar3 + 0x10) == a2)
				goto LAB_6fab0834;
			for (piVar1 = *(int**)(iVar3 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a2)
					goto LAB_6fab0834;
			}
			iVar3 = *(int*)(iVar3 + 0x80);
		} while (iVar3 != 0);
	}
	iVar3 = 0;
LAB_6fab0834:
	if ((iVar4 == 0) || (iVar3 == 0))
	{
		return true;
	}
	if ((*(short*)(iVar4 + 0x22) == *(short*)(iVar3 + 0x22)) && (*(short*)(iVar4 + 0x22) != -1))
	{
		return false;
	}
	uVar2 = sub_6FB4B900(*(int*)(iVar4 + 0x10), *(int*)(iVar3 + 0x10), 8);
	return uVar2 != 0;
}

//D2Client.0x6FAB0870
uint32_t __fastcall sub_6FAB0870(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x10);
	}
	return 0xffffffff;
}

//D2Client.0x6FAB0880
void __fastcall sub_6FAB0880(int a1, uint32_t a2, uint32_t a3)
{
	short sVar1;
	int* piVar2;
	uint32_t* puVar3;
	D2UnitStrc* pDVar4;
	short* psVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	short* psVar8;
	int iVar9;
	short* psVar10;
	int iVar11;
	short sVar12;
	uint32_t uVar13;
	int iVar14;

	if ((a1 != -1) && (iVar9 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar9 + 0x10) != a1)
		{
			for (piVar2 = *(int**)(iVar9 + 0x38); piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (*piVar2 == a1)
					goto LAB_6fab08bf;
			}
			iVar9 = *(int*)(iVar9 + 0x80);
			if (iVar9 == 0)
			{
				return;
			}
		}
	LAB_6fab08bf:
		*(uint32_t*)(iVar9 + 0x14) = a2;
		*(uint32_t*)(iVar9 + 0x24) = a3 & 0xffff;
		pDVar4 = CUNIT_GetPlayer();
		if (pDVar4 == nullptr)
		{
			uVar13 = 0xffffffff;
		}
		else
		{
			uVar13 = pDVar4->dwUnitId;
		}
		iVar9 = dword_6FBAB994;
		if (uVar13 != 0xffffffff)
		{
			for (; iVar9 != 0; iVar9 = *(int*)(iVar9 + 0x80))
			{
				if (*(uint32_t*)(iVar9 + 0x10) == uVar13)
				{
				LAB_6fab0992:
					sVar12 = *(short*)(iVar9 + 0x22);
					goto joined_r0x6fab0921;
				}
				for (puVar3 = *(uint32_t**)(iVar9 + 0x38); puVar3 != nullptr; puVar3 = (uint32_t*)puVar3[1])
				{
					if (*puVar3 == uVar13)
						goto LAB_6fab0992;
				}
			}
		}
		sVar12 = -1;
	joined_r0x6fab0921:
		while (dword_6FBAB994 != 0)
		{
			sVar1 = *(short*)(dword_6FBAB994 + 0x22);
			psVar5 = sub_6FAAF720(sVar1);
			if (psVar5 == nullptr)
			{
				psVar5 = (short*)D2_ALLOC(0xc);
				psVar5[0] = 0;
				psVar5[1] = 0;
				psVar5[2] = 0;
				psVar5[3] = 0;
				psVar5[4] = 0;
				psVar5[5] = 0;
				*psVar5 = sVar1;
				*(short**)(psVar5 + 4) = gpint16_t_6FBAB99C;
				gpint16_t_6FBAB99C = psVar5;
			}
			sub_6FAAF7D0(psVar5);
		}
		dword_6FBAB994 = 0;
		for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
		{
			uVar6 = sub_6FAA6990();
			if (uVar6 == 0)
			{
				uVar7 = sub_6FAAF600(*(uint8_t**)(psVar5 + 2));
			}
			else
			{
				uVar7 = sub_6FAAF6C0((int)*(uint8_t**)(psVar5 + 2));
			}
			*(uint32_t*)(psVar5 + 2) = uVar7;
		}
		sub_6FAAF830();
		psVar5 = gpint16_t_6FBAB99C;
		psVar10 = nullptr;
		if (sVar12 != -1)
		{
			while (psVar8 = psVar5, psVar8 != nullptr)
			{
				if (*psVar8 == sVar12)
				{
					if (psVar10 != nullptr)
					{
						*(uint32_t*)(psVar10 + 4) = *(uint32_t*)(psVar8 + 4);
						*(short**)(psVar8 + 4) = gpint16_t_6FBAB99C;
						gpint16_t_6FBAB99C = psVar8;
					}
					iVar9 = *(int*)(psVar8 + 2);
					iVar14 = 0;
					goto LAB_6fab09ed;
				}
				psVar10 = psVar8;
				psVar5 = *(short**)(psVar8 + 4);
			}
		}
	LAB_6fab0a22:
		iVar9 = 0;
		for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
		{
			if (iVar9 == 0)
			{
				dword_6FBAB994 = *(int*)(psVar5 + 2);
				iVar9 = *(int*)(psVar5 + 2);
			}
			else
			{
				*(uint32_t*)(iVar9 + 0x80) = *(uint32_t*)(psVar5 + 2);
			}
			psVar5[2] = 0;
			psVar5[3] = 0;
			if (iVar9 != 0)
			{
				iVar14 = *(int*)(iVar9 + 0x80);
				while (iVar11 = iVar14, iVar11 != 0)
				{
					iVar9 = iVar11;
					iVar14 = *(int*)(iVar11 + 0x80);
				}
			}
		}
		sub_6FAAF790();
		if (sVar12 == -1)
		{
			sub_6FAAFAE0(uVar13);
		}
		sub_6FB01CB0();
	}
	return;
LAB_6fab09ed:
	iVar11 = iVar9;
	if (iVar11 == 0)
		goto LAB_6fab0a22;
	if (*(uint32_t*)(iVar11 + 0x10) == uVar13)
	{
		if (iVar14 != 0)
		{
			*(uint32_t*)(iVar14 + 0x80) = *(uint32_t*)(iVar11 + 0x80);
			*(uint32_t*)(iVar11 + 0x80) = *(uint32_t*)(psVar8 + 2);
			*(int*)(psVar8 + 2) = iVar11;
		}
		goto LAB_6fab0a22;
	}
	iVar9 = *(int*)(iVar11 + 0x80);
	iVar14 = iVar11;
	goto LAB_6fab09ed;
}

//D2Client.0x6FAB0A90
void __fastcall sub_6FAB0A90(int a1, uint32_t a2, uint32_t a3)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar2 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0ac5;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
			if (iVar2 == 0)
			{
				return;
			}
		}
	LAB_6fab0ac5:
		*(uint32_t*)(iVar2 + 0x28) = a2;
		*(uint32_t*)(iVar2 + 0x2c) = a3;
	}
}

//D2Client.0x6FAB0AE0
uint32_t __fastcall sub_6FAB0AE0(int a1)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a1)
			{
			LAB_6fab0b13:
				return *(uint32_t*)(iVar2 + 0x14);
			}
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0b13;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAB0B20
bool __fastcall sub_6FAB0B20(int a1)
{
	int* piVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;

	if ((a1 != -1) && (iVar4 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar4 + 0x10) == a1)
			{
			LAB_6fab0b58:
				pDVar2 = CUNIT_GetPlayer();
				if (pDVar2 == nullptr)
				{
					uVar3 = 0xffffffff;
				}
				else
				{
					uVar3 = pDVar2->dwUnitId;
				}
				uVar3 = sub_6FB4B900(uVar3, *(int*)(iVar4 + 0x10), 4);
				return uVar3 == 0;
			}
			for (piVar1 = *(int**)(iVar4 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0b58;
			}
			iVar4 = *(int*)(iVar4 + 0x80);
		} while (iVar4 != 0);
	}
	return true;
}

//D2Client.0x6FAB0B80
void __fastcall sub_6FAB0B80(int a1, uint32_t* a2, uint32_t* a3)
{
	if (a1 != 0)
	{
		*a2 = *(uint32_t*)(a1 + 0x28);
		*a3 = *(uint32_t*)(a1 + 0x2c);
		return;
	}
	*a2 = 0;
	*a3 = 0;
}

//D2Client.0x6FAB0BB0
uint32_t __fastcall sub_6FAB0BB0(int a1)
{
	if (a1 != 0)
	{
		return *(uint32_t*)(a1 + 0x24);
	}
	return 0;
}

//D2Client.0x6FAB0BC0
int __fastcall sub_6FAB0BC0(int a1)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a1)
			{
			LAB_6fab0bf3:
				return iVar2 + 0x66;
			}
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0bf3;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAB0C00
int __fastcall sub_6FAB0C00(D2UnitStrc* hPlayer)
{
	uint32_t uVar1;
	uint32_t* puVar2;
	D2PlayerDataStrc* pDVar3;
	int iVar4;

	D2_ASSERT(hPlayer != nullptr);
	D2_ASSERT(!hPlayer->dwUnitType);
	uVar1 = hPlayer->dwUnitId;
	if ((uVar1 != 0xffffffff) && (iVar4 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(uint32_t*)(iVar4 + 0x10) == uVar1)
			{
			LAB_6fab0ca1:
				return iVar4 + 0x66;
			}
			for (puVar2 = *(uint32_t**)(iVar4 + 0x38); puVar2 != nullptr; puVar2 = (uint32_t*)puVar2[1])
			{
				if (*puVar2 == uVar1)
					goto LAB_6fab0ca1;
			}
			iVar4 = *(int*)(iVar4 + 0x80);
		} while (iVar4 != 0);
	}
	pDVar3 = UNITS_GetPlayerData(hPlayer);
	if (pDVar3 != nullptr)
	{
		return (int)pDVar3;
	}
	FOG_DisplayAssert("ptPlayerInfo", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAB0CB0
void __fastcall sub_6FAB0CB0(int a1, uint32_t a2, uint32_t a3)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar2 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0ce5;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
			if (iVar2 == 0)
			{
				return;
			}
		}
	LAB_6fab0ce5:
		*(uint32_t*)(iVar2 + 0x3c) = a2;
		*(uint32_t*)(iVar2 + 0x40) = a3;
	}
}

//D2Client.0x6FAB0D00
int __fastcall sub_6FAB0D00(int a1)
{
	int iVar1;

	iVar1 = dword_6FBAB994;
	if (dword_6FBAB994 != 0)
	{
		do
		{
			if ((*(int*)(iVar1 + 0x3c) == a1) || (*(int*)(iVar1 + 0x40) == a1))
			{
				return iVar1 + 0x66;
			}
			iVar1 = *(int*)(iVar1 + 0x80);
		} while (iVar1 != 0);
	}
	return 0;
}

//D2Client.0x6FAB0D30
uint32_t __fastcall sub_6FAB0D30(int* a1)
{
	short sVar1;
	int iVar2;
	int iVar3;

	iVar2 = dword_6FBAB994;
	if (a1 == nullptr)
	{
		iVar3 = -1;
	}
	else
	{
		iVar3 = a1[3];
	}
	sVar1 = sub_6FB2A6E0(a1);
	if ((sVar1 != -1) && (iVar2 != 0))
	{
		do
		{
			if ((*(short*)(iVar2 + 0x22) == sVar1) && (*(int*)(iVar2 + 0x10) != iVar3))
			{
				return 1;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAB0D80
uint32_t __fastcall sub_6FAB0D80(int a1)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a1)
			{
			LAB_6fab0db3:
				return *(uint32_t*)(iVar2 + 0x34);
			}
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0db3;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	return 0;
}

//D2Client.0x6FAB0DC0
void __fastcall sub_6FAB0DC0(int a1, uint16_t a2)
{
	short sVar1;
	int* piVar2;
	uint32_t* puVar3;
	D2UnitStrc* pDVar4;
	short* psVar5;
	uint32_t uVar6;
	uint32_t uVar7;
	short* psVar8;
	int iVar9;
	short* psVar10;
	int iVar11;
	short sVar12;
	uint32_t uVar13;
	int iVar14;

	if ((a1 != -1) && (iVar9 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar9 + 0x10) == a1)
			{
			LAB_6fab0df5:
				*(uint16_t*)(iVar9 + 0x22) = a2;
				pDVar4 = CUNIT_GetPlayer();
				if (pDVar4 == nullptr)
				{
					uVar13 = 0xffffffff;
				}
				else
				{
					uVar13 = pDVar4->dwUnitId;
				}
				iVar9 = dword_6FBAB994;
				if (uVar13 != 0xffffffff)
					goto joined_r0x6fab0e1a;
				goto LAB_6fab0e45;
			}
			for (piVar2 = *(int**)(iVar9 + 0x38); piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (*piVar2 == a1)
					goto LAB_6fab0df5;
			}
			iVar9 = *(int*)(iVar9 + 0x80);
		} while (iVar9 != 0);
	}
	return;
joined_r0x6fab0e1a:
	if (iVar9 == 0)
		goto LAB_6fab0e45;
	if (*(uint32_t*)(iVar9 + 0x10) == uVar13)
	{
	LAB_6fab0ebd:
		sVar12 = *(short*)(iVar9 + 0x22);
		goto joined_r0x6fab0e4c;
	}
	for (puVar3 = *(uint32_t**)(iVar9 + 0x38); puVar3 != nullptr; puVar3 = (uint32_t*)puVar3[1])
	{
		if (*puVar3 == uVar13)
			goto LAB_6fab0ebd;
	}
	iVar9 = *(int*)(iVar9 + 0x80);
	goto joined_r0x6fab0e1a;
LAB_6fab0f18:
	iVar11 = iVar9;
	if (iVar11 == 0)
		goto LAB_6fab0f4d;
	if (*(uint32_t*)(iVar11 + 0x10) == uVar13)
	{
		if (iVar14 != 0)
		{
			*(uint32_t*)(iVar14 + 0x80) = *(uint32_t*)(iVar11 + 0x80);
			*(uint32_t*)(iVar11 + 0x80) = *(uint32_t*)(psVar8 + 2);
			*(int*)(psVar8 + 2) = iVar11;
		}
		goto LAB_6fab0f4d;
	}
	iVar9 = *(int*)(iVar11 + 0x80);
	iVar14 = iVar11;
	goto LAB_6fab0f18;
LAB_6fab0e45:
	sVar12 = -1;
joined_r0x6fab0e4c:
	while (dword_6FBAB994 != 0)
	{
		sVar1 = *(short*)(dword_6FBAB994 + 0x22);
		psVar5 = sub_6FAAF720(sVar1);
		if (psVar5 == nullptr)
		{
			psVar5 = (short*)D2_ALLOC(0xc);
			psVar5[0] = 0;
			psVar5[1] = 0;
			psVar5[2] = 0;
			psVar5[3] = 0;
			psVar5[4] = 0;
			psVar5[5] = 0;
			*psVar5 = sVar1;
			*(short**)(psVar5 + 4) = gpint16_t_6FBAB99C;
			gpint16_t_6FBAB99C = psVar5;
		}
		sub_6FAAF7D0(psVar5);
	}
	dword_6FBAB994 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
	{
		uVar6 = sub_6FAA6990();
		if (uVar6 == 0)
		{
			uVar7 = sub_6FAAF600(*(uint8_t**)(psVar5 + 2));
		}
		else
		{
			uVar7 = sub_6FAAF6C0((int)*(uint8_t**)(psVar5 + 2));
		}
		*(uint32_t*)(psVar5 + 2) = uVar7;
	}
	sub_6FAAF830();
	psVar5 = gpint16_t_6FBAB99C;
	psVar10 = nullptr;
	if (sVar12 != -1)
	{
		while (psVar8 = psVar5, psVar8 != nullptr)
		{
			if (*psVar8 == sVar12)
			{
				if (psVar10 != nullptr)
				{
					*(uint32_t*)(psVar10 + 4) = *(uint32_t*)(psVar8 + 4);
					*(short**)(psVar8 + 4) = gpint16_t_6FBAB99C;
					gpint16_t_6FBAB99C = psVar8;
				}
				iVar9 = *(int*)(psVar8 + 2);
				iVar14 = 0;
				goto LAB_6fab0f18;
			}
			psVar10 = psVar8;
			psVar5 = *(short**)(psVar8 + 4);
		}
	}
LAB_6fab0f4d:
	iVar9 = 0;
	for (psVar5 = gpint16_t_6FBAB99C; psVar5 != nullptr; psVar5 = *(short**)(psVar5 + 4))
	{
		if (iVar9 == 0)
		{
			dword_6FBAB994 = *(int*)(psVar5 + 2);
			iVar9 = *(int*)(psVar5 + 2);
		}
		else
		{
			*(uint32_t*)(iVar9 + 0x80) = *(uint32_t*)(psVar5 + 2);
		}
		psVar5[2] = 0;
		psVar5[3] = 0;
		if (iVar9 != 0)
		{
			iVar14 = *(int*)(iVar9 + 0x80);
			while (iVar11 = iVar14, iVar11 != 0)
			{
				iVar9 = iVar11;
				iVar14 = *(int*)(iVar11 + 0x80);
			}
		}
	}
	sub_6FAAF790();
	if (sVar12 == -1)
	{
		sub_6FAAFAE0(uVar13);
	}
	sub_6FB01CB0();
}

//D2Client.0x6FAB0FB0
void __fastcall sub_6FAB0FB0(int a1, uint32_t a2)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a1)
			{
			LAB_6fab0fe3:
				*(uint32_t*)(iVar2 + 0x30) = a2 & 0xff;
				sub_6FB01CB0();
				return;
			}
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab0fe3;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
}

//D2Client.0x6FAB1000
void __fastcall sub_6FAB1000(int a1, int a2, uint32_t a3)
{
	int* piVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;

	if ((a1 != -1) && (iVar4 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar4 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar4 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab103b;
			}
			iVar4 = *(int*)(iVar4 + 0x80);
			if (iVar4 == 0)
			{
				return;
			}
		}
	LAB_6fab103b:
		sub_6FB4B840(a1, a2);
		sub_6FB4B940(a1, a2, a3 & 0xffff);
		sub_6FB01CB0();
		pDVar2 = CUNIT_GetPlayer();
		if (pDVar2 == nullptr)
		{
			uVar3 = 0xffffffff;
		}
		else
		{
			uVar3 = pDVar2->dwUnitId;
		}
		if (a2 == uVar3)
		{
			sub_6FAB1BB0(a1);
		}
	}
}

//D2Client.0x6FAB1080
void __fastcall sub_6FAB1080(int a1, int a2)
{
	uint32_t* puVar1;
	int* piVar2;
	int iVar3;
	uint32_t* puVar4;

	if ((a1 != -1) && (puVar1 = (uint32_t*)dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (puVar1[4] == a1)
				goto LAB_6fab1116;
			for (piVar2 = (int*)puVar1[0xe]; piVar2 != nullptr; piVar2 = (int*)piVar2[1])
			{
				if (*piVar2 == a1)
					goto LAB_6fab1116;
			}
			puVar1 = (uint32_t*)puVar1[0x20];
		} while (puVar1 != nullptr);
	}
	puVar1 = (uint32_t*)D2_ALLOC(0x84);
	D2_ASSERT(puVar1 != nullptr);
	puVar4 = puVar1;
	for (iVar3 = 0x21; iVar3 != 0; iVar3 = iVar3 + -1)
	{
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	puVar1[4] = a1;
	puVar1[0x20] = (uint32_t)(gpuint32_t_6FBAB998);
	gpuint32_t_6FBAB998 = puVar1;
LAB_6fab1116:
	for (piVar2 = (int*)puVar1[0xe]; piVar2 != nullptr; piVar2 = (int*)piVar2[1])
	{
		if (*piVar2 == a2)
		{
			return;
		}
	}
	piVar2 = (int*)D2_ALLOC(8);
	if (piVar2 != nullptr)
	{
		*piVar2 = 0;
		piVar2[1] = 0;
		*piVar2 = a2;
		piVar2[1] = puVar1[0xe];
		puVar1[0xe] = (uint32_t)(piVar2);
		return;
	}
	FOG_DisplayAssert("ptBody", __FILE__, __LINE__);
	exit(-1);
}

//D2Client.0x6FAB1180
void __fastcall sub_6FAB1180(int a1, int a2)
{
	int* piVar1;
	int* pFree;
	int iVar2;
	int* piVar3;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar2 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab11b7;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
			if (iVar2 == 0)
			{
				return;
			}
		}
	LAB_6fab11b7:
		piVar1 = *(int**)(iVar2 + 0x38);
		piVar3 = nullptr;
		if (*(int**)(iVar2 + 0x38) != nullptr)
		{
			while (pFree = piVar1, *pFree != a2)
			{
				piVar1 = (int*)pFree[1];
				piVar3 = pFree;
				if ((int*)pFree[1] == nullptr)
				{
					return;
				}
			}
			if (piVar3 == nullptr)
			{
				*(int*)(iVar2 + 0x38) = pFree[1];
			}
			else
			{
				piVar3[1] = pFree[1];
			}
			D2_FREE(pFree);
		}
	}
}

//D2Client.0x6FAB1200
uint32_t __fastcall sub_6FAB1200(int a1, int a2)
{
	int* piVar1;
	uint32_t uVar2;
	int iVar3;

	if ((a2 != -1) && (iVar3 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar3 + 0x10) == a2)
			{
			LAB_6fab1235:
				if (a1 == *(int*)(iVar3 + 0x10))
				{
					return 1;
				}
				uVar2 = sub_6FB4B900(*(int*)(iVar3 + 0x10), a1, 1);
				if (uVar2 == 0)
				{
					return 0;
				}
				return 1;
			}
			for (piVar1 = *(int**)(iVar3 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a2)
					goto LAB_6fab1235;
			}
			iVar3 = *(int*)(iVar3 + 0x80);
		} while (iVar3 != 0);
	}
	return 0;
}

//D2Client.0x6FAB1260
uint32_t __fastcall sub_6FAB1260(int a1, int a2)
{
	int* piVar1;
	int iVar2;
	int iVar3;

	if ((a1 != -1) && (iVar3 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar3 + 0x10) == a1)
				goto LAB_6fab1296;
			for (piVar1 = *(int**)(iVar3 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab1296;
			}
			iVar3 = *(int*)(iVar3 + 0x80);
		} while (iVar3 != 0);
	}
	iVar3 = 0;
LAB_6fab1296:
	if ((a2 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar2 + 0x10) == a2)
				goto LAB_6fab12c4;
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a2)
					goto LAB_6fab12c4;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
		} while (iVar2 != 0);
	}
	iVar2 = 0;
LAB_6fab12c4:
	if ((((iVar3 != 0) && (iVar2 != 0)) && (*(short*)(iVar3 + 0x22) == *(short*)(iVar2 + 0x22))) &&
	    (*(short*)(iVar3 + 0x22) != -1))
	{
		return 1;
	}
	return 0;
}

//D2Client.0x6FAB12F0
uint32_t __cdecl sub_6FAB12F0()
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;
	int iVar3;
	uint32_t uVar4;

	iVar3 = dword_6FBAB994;
	pDVar1 = CUNIT_GetPlayer();
	if (pDVar1 == nullptr)
	{
		uVar4 = 0xffffffff;
	}
	else
	{
		uVar4 = pDVar1->dwUnitId;
	}
	if (iVar3 != 0)
	{
		do
		{
			uVar2 = sub_6FB4B900(*(int*)(iVar3 + 0x10), uVar4, 8);
			if (uVar2 != 0)
			{
				return 1;
			}
			iVar3 = *(int*)(iVar3 + 0x80);
		} while (iVar3 != 0);
	}
	return 0;
}

//D2Client.0x6FAB1340
uint32_t __fastcall sub_6FAB1340(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	pDVar1 = CUNIT_GetPlayer();
	if ((a1 != 0) && (pDVar1 != nullptr))
	{
		uVar2 = sub_6FB4B900(*(int*)(a1 + 0x10), pDVar1->dwUnitId, 8);
		if (uVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAB1370
uint32_t __fastcall sub_6FAB1370(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	pDVar1 = CUNIT_GetPlayer();
	if ((a1 != 0) && (pDVar1 != nullptr))
	{
		uVar2 = sub_6FB4B900(pDVar1->dwUnitId, *(int*)(a1 + 0x10), 8);
		if (uVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAB13A0
uint32_t __fastcall sub_6FAB13A0(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	pDVar1 = CUNIT_GetPlayer();
	if ((a1 != 0) && (pDVar1 != nullptr))
	{
		uVar2 = sub_6FB4B900(*(int*)(a1 + 0x10), pDVar1->dwUnitId, 1);
		if (uVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAB13D0
uint32_t __fastcall sub_6FAB13D0(int a1)
{
	D2UnitStrc* pDVar1;
	uint32_t uVar2;

	pDVar1 = CUNIT_GetPlayer();
	if ((a1 != 0) && (pDVar1 != nullptr))
	{
		uVar2 = sub_6FB4B900(pDVar1->dwUnitId, *(int*)(a1 + 0x10), 1);
		if (uVar2 != 0)
		{
			return 1;
		}
	}
	return 0;
}

//D2Client.0x6FAB1400
uint32_t __fastcall sub_6FAB1400(int a1)
{
	int iVar1;

	if (((a1 != 0) && (iVar1 = *(int*)(a1 + 0x1c), -1 < iVar1)) &&
	    ((iVar1 < 2 || (iVar1 == 6))))
	{
		return 0;
	}
	return 1;
}

//D2Client.0x6FAB1420
void __fastcall sub_6FAB1420(int a1, uint32_t a2)
{
	int* piVar1;
	int iVar2;

	if ((a1 != -1) && (iVar2 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		while (*(int*)(iVar2 + 0x10) != a1)
		{
			for (piVar1 = *(int**)(iVar2 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab1453;
			}
			iVar2 = *(int*)(iVar2 + 0x80);
			if (iVar2 == 0)
			{
				return;
			}
		}
	LAB_6fab1453:
		*(uint32_t*)(iVar2 + 0x14) = a2 & 0xff;
	}
}

//D2Client.0x6FAB1460
uint32_t __fastcall sub_6FAB1460(int a1)
{
	int* piVar1;
	D2UnitStrc* pDVar2;
	uint32_t uVar3;
	int iVar4;

	if ((a1 != -1) && (iVar4 = dword_6FBAB994, dword_6FBAB994 != 0))
	{
		do
		{
			if (*(int*)(iVar4 + 0x10) == a1)
				goto LAB_6fab1496;
			for (piVar1 = *(int**)(iVar4 + 0x38); piVar1 != nullptr; piVar1 = (int*)piVar1[1])
			{
				if (*piVar1 == a1)
					goto LAB_6fab1496;
			}
			iVar4 = *(int*)(iVar4 + 0x80);
		} while (iVar4 != 0);
	}
	iVar4 = 0;
LAB_6fab1496:
	pDVar2 = CUNIT_GetPlayer();
	if (pDVar2 == nullptr)
	{
		uVar3 = 0xffffffff;
	}
	else
	{
		uVar3 = pDVar2->dwUnitId;
	}
	if ((a1 != uVar3) && (iVar4 != 0))
	{
		return *(uint32_t*)(iVar4 + 0x14);
	}
	return 0;
}

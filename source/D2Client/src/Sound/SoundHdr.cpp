#include "Sound/SoundHdr.h"

#include "Sound/SoundChan.h"
#include "Sound/SoundInst.h"

//D2Client.0x6FB96A84
uint32_t dword_6FB96A84 = 0x5846535C;
//D2Client.0x6FB96A88
uint16_t word_6FB96A88 = 0x5C;
//D2Client.0x6FB96A8C
uint32_t dword_6FB96A8C = 0x53554D5C;
//D2Client.0x6FB96A90
uint32_t dword_6FB96A90 = 0x5C4349;
//D2Client.0x6FBBD498
int32_t dword_6FBBD498;
//D2Client.0x6FBBD49C
int32_t dword_6FBBD49C;
//D2Client.0x6FBBD4A0
uint8_t* ptr_6FBBD4A0;
//D2Client.0x6FBBD4A4
int32_t dword_6FBBD4A4;
//D2Client.0x6FBBD4A8
uint32_t dword_6FBBD4A8;
//D2Client.0x6FBBD4AC
uint32_t dword_6FBBD4AC;
//D2Client.0x6FBBD4B0
int32_t* gpint32_t_6FBBD4B0;
//D2Client.0x6FBBD4B4
uint32_t dword_6FBBD4B4;
//D2Client.0x6FBBD4BC
uint8_t byte_6FBBD4BC;
//D2Client.0x6FBBD4C0
uint32_t dword_6FBBD4C0;
//D2Client.0x6FBBD4C4
uint32_t dword_6FBBD4C4;
//D2Client.0x6FBBD4C8
int32_t dword_6FBBD4C8;

//D2Client.0x6FB53DE0
void __cdecl sub_6FB53DE0()
{
	HD2ARCHIVE__* pHVar1;
	D2CellFileStrc* pDVar2;
	D2BinFileStrc* pDVar3;
	uint8_t bVar4;
	uint32_t uVar5;
	uint32_t uVar6;
	int iVar7;
	int iVar8;
	int iVar9;
	int* piVar10;
	int iVar11;
	uint32_t* puVar12;
	char* pcVar13;
	uint32_t uVar14;
	int local_4bc;
	int iStack_4b8;
	uint32_t uStack_4b4;
	D2BinFieldStrc local_4b0;
	char* local_49c;
	uint32_t local_498;
	uint32_t local_494;
	uint32_t local_490;
	uint32_t local_48c;
	char* local_488;
	uint32_t local_484;
	uint32_t local_480;
	uint32_t local_47c;
	uint32_t local_478;
	char* local_474;
	uint32_t local_470;
	uint32_t local_46c;
	uint32_t local_468;
	uint32_t local_464;
	char* local_460;
	uint32_t local_45c;
	uint32_t local_458;
	uint32_t local_454;
	uint32_t local_450;
	char* local_44c;
	uint32_t local_448;
	uint32_t local_444;
	uint32_t local_440;
	uint32_t local_43c;
	char* local_438;
	uint32_t local_434;
	uint32_t local_430;
	uint32_t local_42c;
	uint32_t local_428;
	char* local_424;
	uint32_t local_420;
	uint32_t local_41c;
	uint32_t local_418;
	uint32_t local_414;
	char* local_410;
	uint32_t local_40c;
	uint32_t local_408;
	uint32_t local_404;
	uint32_t local_400;
	char* local_3fc;
	uint32_t local_3f8;
	uint32_t local_3f4;
	uint32_t local_3f0;
	uint32_t local_3ec;
	char* local_3e8;
	uint32_t local_3e4;
	uint32_t local_3e0;
	uint32_t local_3dc;
	uint32_t local_3d8;
	char* local_3d4;
	uint32_t local_3d0;
	uint32_t local_3cc;
	uint32_t local_3c8;
	uint32_t local_3c4;
	char* local_3c0;
	uint32_t local_3bc;
	uint32_t local_3b8;
	uint32_t local_3b4;
	uint32_t local_3b0;
	char* local_3ac;
	uint32_t local_3a8;
	uint32_t local_3a4;
	uint32_t local_3a0;
	uint32_t local_39c;
	char* local_398;
	uint32_t local_394;
	uint32_t local_390;
	uint32_t local_38c;
	uint32_t local_388;
	char* local_384;
	uint32_t local_380;
	uint32_t local_37c;
	uint32_t local_378;
	uint32_t local_374;
	char* local_370;
	uint32_t local_36c;
	uint32_t local_368;
	uint32_t local_364;
	uint32_t local_360;
	char* local_35c;
	uint32_t local_358;
	uint32_t local_354;
	uint32_t local_350;
	uint32_t local_34c;
	char* local_348;
	uint32_t local_344;
	uint32_t local_340;
	uint32_t local_33c;
	uint32_t local_338;
	char* local_334;
	uint32_t local_330;
	uint32_t local_32c;
	uint32_t local_328;
	uint32_t local_324;
	char* local_320;
	uint32_t local_31c;
	uint32_t local_318;
	uint32_t local_314;
	uint32_t local_310;
	char* local_30c;
	uint32_t local_308;
	uint32_t local_304;
	uint32_t local_300;
	uint32_t local_2fc;
	uint8_t* local_2f8;
	uint32_t local_2f4;
	uint32_t local_2f0;
	uint32_t local_2ec;
	uint32_t local_2e8;
	D2BinFieldStrc local_2e4;
	char* local_2d0;
	uint32_t local_2cc;
	uint32_t local_2c8;
	uint32_t local_2c4;
	uint32_t local_2c0;
	char* local_2bc;
	uint32_t local_2b8;
	uint32_t local_2b4;
	uint32_t local_2b0;
	uint32_t local_2ac;
	uint8_t* local_2a8;
	uint32_t local_2a4;
	uint32_t local_2a0;
	uint32_t local_29c;
	uint32_t local_298;
	char* local_294;
	uint32_t local_290;
	uint32_t local_28c;
	uint32_t local_288;
	uint32_t local_284;
	char* local_280;
	uint32_t local_27c;
	uint32_t local_278;
	uint32_t local_274;
	uint32_t local_270;
	char* local_26c;
	uint32_t local_268;
	uint32_t local_264;
	uint32_t local_260;
	uint32_t local_25c;
	char* local_258;
	uint32_t local_254;
	uint32_t local_250;
	uint32_t local_24c;
	uint32_t local_248;
	char* local_244;
	uint32_t local_240;
	uint32_t local_23c;
	uint32_t local_238;
	uint32_t local_234;
	char* local_230;
	uint32_t local_22c;
	uint32_t local_228;
	uint32_t local_224;
	uint32_t local_220;
	char* local_21c;
	uint32_t local_218;
	uint32_t local_214;
	uint32_t local_210;
	uint32_t local_20c;
	char* local_208;
	uint32_t local_204;
	uint32_t local_200;
	uint32_t local_1fc;
	uint32_t local_1f8;
	char* local_1f4;
	uint32_t local_1f0;
	uint32_t local_1ec;
	uint32_t local_1e8;
	uint32_t local_1e4;
	char* local_1e0;
	uint32_t local_1dc;
	uint32_t local_1d8;
	uint32_t local_1d4;
	uint32_t local_1d0;
	char* local_1cc;
	uint32_t local_1c8;
	uint32_t local_1c4;
	uint32_t local_1c0;
	uint32_t local_1bc;
	char* local_1b8;
	uint32_t local_1b4;
	uint32_t local_1b0;
	uint32_t local_1ac;
	uint32_t local_1a8;
	char* local_1a4;
	uint32_t local_1a0;
	uint32_t local_19c;
	uint32_t local_198;
	uint32_t local_194;
	char* local_190;
	uint32_t local_18c;
	uint32_t local_188;
	uint32_t local_184;
	uint32_t local_180;
	uint8_t* local_17c;
	uint32_t local_178;
	uint32_t local_174;
	uint32_t local_170;
	uint32_t local_16c;
	char* local_168;
	uint32_t local_164;
	uint32_t local_160;
	uint32_t local_15c;
	uint32_t local_158;
	char* local_154;
	uint32_t local_150;
	uint32_t local_14c;
	uint32_t local_148;
	uint32_t local_144;
	char* local_140;
	uint32_t local_13c;
	uint32_t local_138;
	uint32_t local_134;
	uint32_t local_130;
	char* local_12c;
	uint32_t local_128;
	uint32_t local_124;
	uint32_t local_120;
	uint32_t local_11c;
	uint8_t* local_118;
	uint32_t local_114;
	uint32_t local_110;
	uint32_t local_10c;
	uint32_t local_108;
	CHAR local_104[260];

	local_240 = 3;
	local_22c = 3;
	local_2e4.szFieldName = "Filename";
	local_2e4.nFieldType = TXTFIELD_ASCII;
	local_2e4.nFieldLength = 0x3b;
	local_2e4.nFieldOffset = 0;
	local_2e4.pLinkField = nullptr;
	local_2d0 = "Volume";
	local_2cc = 4;
	local_2c8 = 0;
	local_2c4 = 0x3c;
	local_2c0 = 0;
	local_2bc = "Group Size";
	local_2b8 = 4;
	local_2b4 = 0;
	local_2b0 = 0x3d;
	local_2ac = 0;
	local_2a8 = (uint8_t*)("Loop");
	local_2a4 = 4;
	local_2a0 = 0;
	local_29c = 0x3e;
	local_298 = 0;
	local_294 = "Fade In";
	local_290 = 4;
	local_28c = 0;
	local_288 = 0x3f;
	local_284 = 0;
	local_280 = "Fade Out";
	local_27c = 4;
	local_278 = 0;
	local_274 = 0x40;
	local_270 = 0;
	local_26c = "Defer Inst";
	local_268 = 4;
	local_264 = 0;
	local_260 = 0x41;
	local_25c = 0;
	local_258 = "Stop Inst";
	local_254 = 4;
	local_250 = 0;
	local_24c = 0x42;
	local_248 = 0;
	local_244 = "Duration";
	local_23c = 0;
	local_238 = 0x43;
	local_234 = 0;
	local_230 = "Compound";
	local_228 = 0;
	local_224 = 0x45;
	local_220 = 0;
	local_21c = "Falloff";
	local_218 = 2;
	local_214 = 0;
	local_210 = 0x47;
	local_20c = 0;
	local_208 = "Reverb";
	local_204 = 4;
	local_200 = 0;
	local_1fc = 0x4b;
	local_1f8 = 0;
	local_1f4 = "Cache";
	local_1f0 = 4;
	local_1ec = 0;
	local_1e8 = 0x4c;
	local_1e4 = 0;
	local_1e0 = "Async Only";
	local_1dc = 4;
	local_1d8 = 0;
	local_1d4 = 0x4d;
	local_1d0 = 0;
	local_1cc = "Priority";
	local_1c8 = 4;
	local_1c4 = 0;
	local_1c0 = 0x4e;
	local_1bc = 0;
	local_1b8 = "Stream";
	local_1b4 = 4;
	local_1b0 = 0;
	local_1ac = 0x4f;
	local_1a8 = 0;
	local_1a4 = "Stereo";
	local_1a0 = 4;
	local_19c = 0;
	local_198 = 0x50;
	local_194 = 0;
	local_190 = "Tracking";
	local_18c = 4;
	local_188 = 0;
	local_184 = 0x51;
	local_180 = 0;
	local_17c = (uint8_t*)("Solo");
	local_178 = 4;
	local_174 = 0;
	local_170 = 0x52;
	local_16c = 0;
	local_168 = "Music Vol";
	local_164 = 4;
	local_160 = 0;
	local_15c = 0x53;
	local_158 = 0;
	local_154 = "Block 1";
	local_150 = 2;
	local_14c = 0;
	local_148 = 0x54;
	local_144 = 0;
	local_140 = "Block 2";
	local_13c = 2;
	local_138 = 0;
	local_134 = 0x58;
	local_130 = 0;
	local_12c = "Block 3";
	local_128 = 2;
	local_124 = 0;
	local_120 = 0x5c;
	local_11c = 0;
	local_118 = (uint8_t*)("end");
	local_114 = 0;
	local_110 = 0;
	local_10c = 0;
	local_108 = 0;
	local_4b0.szFieldName = "Song";
	local_4b0.nFieldType = TXTFIELD_DWORD;
	local_4b0.nFieldLength = 0;
	local_4b0.nFieldOffset = 0;
	local_4b0.pLinkField = nullptr;
	local_49c = "Day Ambience";
	local_498 = 2;
	local_494 = 0;
	local_490 = 4;
	local_48c = 0;
	local_488 = "Night Ambience";
	local_484 = 2;
	local_480 = 0;
	local_47c = 8;
	local_478 = 0;
	local_474 = "Day Event";
	local_470 = 2;
	local_46c = 0;
	local_468 = 0xc;
	local_464 = 0;
	local_460 = "Night Event";
	local_45c = 2;
	local_458 = 0;
	local_454 = 0x10;
	local_450 = 0;
	local_44c = "Event Delay";
	local_448 = 2;
	local_444 = 0;
	local_440 = 0x14;
	local_43c = 0;
	local_438 = "Indoors";
	local_434 = 4;
	local_430 = 0;
	local_42c = 0x18;
	local_428 = 0;
	local_424 = "Material 1";
	local_420 = 2;
	local_41c = 0;
	local_418 = 0x1c;
	local_414 = 0;
	local_410 = "Material 2";
	local_40c = 2;
	local_408 = 0;
	local_404 = 0x20;
	local_400 = 0;
	local_3fc = "EAX Environ";
	local_3f8 = 2;
	local_3f4 = 0;
	local_3f0 = 0x24;
	local_3ec = 0;
	local_3e8 = "EAX Env Size";
	local_3e4 = 2;
	local_3e0 = 0;
	local_3dc = 0x28;
	local_3d8 = 0;
	local_3d4 = "EAX Env Diff";
	local_3d0 = 2;
	local_3cc = 0;
	local_3c8 = 0x2c;
	local_3c4 = 0;
	local_3c0 = "EAX Room Vol";
	local_3bc = 2;
	local_3b8 = 0;
	local_3b4 = 0x30;
	local_3b0 = 0;
	local_3ac = "EAX Room HF";
	local_3a8 = 2;
	local_3a4 = 0;
	local_3a0 = 0x34;
	local_39c = 0;
	local_398 = "EAX Decay Time";
	local_394 = 2;
	local_390 = 0;
	local_38c = 0x38;
	local_388 = 0;
	local_384 = "EAX Decay HF";
	local_380 = 2;
	local_37c = 0;
	local_378 = 0x3c;
	local_374 = 0;
	local_370 = "EAX Reflect";
	local_36c = 2;
	local_368 = 0;
	local_364 = 0x40;
	local_360 = 0;
	local_35c = "EAX Reflect Delay";
	local_358 = 2;
	local_354 = 0;
	local_350 = 0x44;
	local_34c = 0;
	local_348 = "EAX Reverb";
	local_344 = 2;
	local_340 = 0;
	local_33c = 0x48;
	local_338 = 0;
	local_334 = "EAX Rev Delay";
	local_330 = 2;
	local_32c = 0;
	local_328 = 0x4c;
	local_324 = 0;
	local_320 = "EAX Room Roll";
	local_31c = 2;
	local_318 = 0;
	local_314 = 0x50;
	local_310 = 0;
	local_30c = "EAX Air Absorb";
	local_308 = 2;
	local_304 = 0;
	local_300 = 0x54;
	local_2fc = 0;
	local_2f8 = (uint8_t*)("end");
	local_2f4 = 0;
	local_2f0 = 0;
	local_2ec = 0;
	local_2e8 = 0;
	D2_ASSERT(!dword_6FBBD498);
	D2_ASSERT(ptr_6FBBD4A0 == nullptr);
	wsprintfA(local_104, "%s\\sounds.txt", "DATA\\GLOBAL\\EXCEL");
	piVar10 = &local_4bc;
	uVar14 = 0x101;
	pcVar13 = __FILE__;
	pHVar1 = D2Win_GetArchive();
	pDVar2 = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar1), local_104, (size_t*)(piVar10), pcVar13, uVar14));
	pDVar3 = FOG_CreateBinFile(pDVar2, local_4bc);
	dword_6FBBD49C = FOG_GetRecordCountFromBinFile(pDVar3);
	dword_6FBBD498 = (int)D2_ALLOC(dword_6FBBD49C * 0x8e);
	uVar6 = dword_6FBBD49C * 0x8e;
	puVar12 = (uint32_t*)dword_6FBBD498;
	for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
	{
		*puVar12 = 0;
		puVar12 = puVar12 + 1;
	}
	for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1)
	{
		*(uint8_t*)puVar12 = 0;
		puVar12 = (uint32_t*)((int)puVar12 + 1);
	}
	FOG_10207(pDVar3, &local_2e4, (void*)dword_6FBBD498, dword_6FBBD49C, 0x8e);
	FOG_FreeBinFile(pDVar3);
	wsprintfA(local_104, "%s\\soundenviron.txt", "DATA\\GLOBAL\\EXCEL");
	piVar10 = &local_4bc;
	uVar14 = 0x10d;
	pcVar13 = __FILE__;
	pHVar1 = D2Win_GetArchive();
	pDVar2 = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar1), local_104, (size_t*)(piVar10), pcVar13, uVar14));
	pDVar3 = FOG_CreateBinFile(pDVar2, local_4bc);
	dword_6FBBD4A4 = FOG_GetRecordCountFromBinFile(pDVar3);
	ptr_6FBBD4A0 = (uint8_t*)(D2_ALLOC(dword_6FBBD4A4 * 0x58));
	puVar12 = (uint32_t*)ptr_6FBBD4A0;
	for (uVar6 = (uint32_t)(dword_6FBBD4A4 * 0x58) >> 2; uVar6 != 0; uVar6 = uVar6 - 1)
	{
		*puVar12 = 0;
		puVar12 = puVar12 + 1;
	}
	for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*(uint8_t*)puVar12 = 0;
		puVar12 = (uint32_t*)((int)puVar12 + 1);
	}
	FOG_10207(pDVar3, &local_4b0, ptr_6FBBD4A0, dword_6FBBD4A4, 0x58);
	FOG_FreeBinFile(pDVar3);
	iVar7 = 1;
	if (1 < dword_6FBBD49C)
	{
		iStack_4b8 = 0x8e;
		uVar6 = 1;
		iVar8 = 0;
		do
		{
			iVar9 = iStack_4b8 + dword_6FBBD498;
			if (((iVar8 == 0) || (iVar7 < iVar8)) || ((int)(uVar6 + iVar8) <= iVar7))
			{
				*(int*)(iVar9 + 0x60) = iVar7;
			}
			else
			{
				*(int*)(iVar9 + 0x60) = iVar8;
			}
			uVar5 = (uint32_t) * (uint8_t*)(iVar9 + 0x3d);
			iVar11 = iVar7;
			if (*(uint8_t*)(iVar9 + 0x3d) == 0)
			{
				*(uint8_t*)(iVar9 + 0x3d) = 1;
				uVar5 = uVar6;
				iVar11 = iVar8;
			}
			bVar4 = 0;
			uStack_4b4 = uStack_4b4 & 0xffffff00;
			do
			{
				if (*(int*)(iVar9 + 0x54 + (uStack_4b4 & 0xff) * 4) == -1)
					break;
				bVar4 = bVar4 + 1;
				uStack_4b4 = CONCAT31((*(uint8_t*)((uint8_t*)&uStack_4b4 + 1)), bVar4);
			} while (bVar4 < 3);
			*(uint8_t*)(iVar9 + 0x80) = bVar4;
			iVar7 = iVar7 + 1;
			iStack_4b8 = iStack_4b8 + 0x8e;
			uVar6 = uVar5;
			iVar8 = iVar11;
		} while (iVar7 < dword_6FBBD49C);
	}
	iVar7 = 0;
	dword_6FBBD4A8 = dword_6FBBD49C;
	dword_6FBBD4AC = 0;
	iVar8 = dword_6FBBD49C;
	piVar10 = (int*)ptr_6FBBD4A0;
	iVar9 = dword_6FBBD4A4;
	if (0 < dword_6FBBD4A4)
	{
		do
		{
			iVar11 = *piVar10;
			if (0 < iVar11)
			{
				if (iVar11 < iVar8)
				{
					iVar8 = iVar11;
					dword_6FBBD4A8 = iVar11;
				}
				if (iVar7 < iVar11)
				{
					iVar7 = iVar11;
					dword_6FBBD4AC = iVar11;
				}
			}
			iVar9 = iVar9 + -1;
			piVar10 = piVar10 + 0x16;
		} while (iVar9 != 0);
	}
	uVar6 = (iVar7 - iVar8) + 1;
	gpuint32_t_6FBBD494 = (uint32_t*)
	    D2_ALLOC(uVar6 * 4);
	puVar12 = gpuint32_t_6FBBD494;
	for (uVar6 = uVar6 & 0x3fffffff; uVar6 != 0; uVar6 = uVar6 - 1)
	{
		*puVar12 = 0;
		puVar12 = puVar12 + 1;
	}
	for (iVar7 = 0; iVar7 != 0; iVar7 = iVar7 + -1)
	{
		*(uint8_t*)puVar12 = 0;
		puVar12 = (uint32_t*)((int)puVar12 + 1);
	}
}

//D2Client.0x6FB54860
void __cdecl sub_6FB54860()
{
	int iVar1;
	int* piVar2;
	int iVar3;
	void* pFree;
	int iVar4;
	int iVar5;

	iVar1 = D2SOUND_10002();
	if (iVar1 != 0)
	{
		sub_6FB52940();
		sub_6FB55FC0();
		sub_6FB56AC0();
		sub_6FB53170();
		if (ptr_6FBBD4A0 != nullptr)
		{
			D2_FREE(ptr_6FBBD4A0);
			ptr_6FBBD4A0 = nullptr;
			dword_6FBBD4A4 = 0;
		}
		if (dword_6FBBD498 != 0)
		{
			iVar1 = 1;
			pFree = (void*)dword_6FBBD498;
			if (1 < dword_6FBBD49C)
			{
				iVar4 = 0x8e;
				iVar3 = dword_6FBBD49C;
				do
				{
					if (((pFree == nullptr) || (iVar4 < 0)) || (iVar3 <= iVar1))
					{
						iVar5 = 0;
					}
					else
					{
						iVar5 = (int)pFree + iVar4;
					}
					if (*(int*)(iVar5 + 0x86) != 0)
					{
						piVar2 = sub_6FB53780(iVar1);
						D2_ASSERT(piVar2 == nullptr);
						dword_6FBBD4C8 = dword_6FBBD4C8 - *(int*)(iVar5 + 0x70);
						D2SOUND_10059((int)&gpint32_t_6FBBD4B0, iVar1);
						*(uint32_t*)(iVar5 + 0x7c) = 0;
						if (*(AsyncData**)(iVar5 + 0x82) == nullptr)
						{
							D2_FREE(*(void**)(iVar5 + 0x6c));
						}
						else
						{
							FOG_AsyncDataFree(*(AsyncData**)(iVar5 + 0x82));
							*(uint32_t*)(iVar5 + 0x82) = 0;
						}
						*(uint32_t*)(iVar5 + 0x6c) = 0;
						*(uint32_t*)(iVar5 + 0x86) = 0;
						iVar3 = dword_6FBBD49C;
						pFree = (void*)dword_6FBBD498;
					}
					iVar1 = iVar1 + 1;
					iVar4 = iVar4 + 0x8e;
				} while (iVar1 < iVar3);
			}
			D2_FREE(pFree);
			dword_6FBBD498 = 0;
			dword_6FBBD49C = 0;
		}
		dword_6FBBD4A8 = 0;
		dword_6FBBD4AC = 0;
	}
}

//D2Client.0x6FB549C0
void __fastcall sub_6FB549C0(int a1, int a2)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	if (((((a1 != 0) && (dword_6FBBD498 != 0)) && (-1 < a1)) &&
	        ((a1 < dword_6FBBD49C && (iVar1 = dword_6FBBD498 + a1 * 0x8e, iVar1 != 0)))) &&
	    (((*(int*)(iVar1 + 0x8a) != 0 || (a2 != -1)) &&
	        (iVar3 = *(int*)(iVar1 + 0x60), iVar3 < (int)((uint32_t) * (uint8_t*)(iVar1 + 0x3d) + iVar3)))))
	{
		iVar4 = iVar3 * 0x8e;
		do
		{
			if (((dword_6FBBD498 == 0) || (iVar4 < 0)) || (dword_6FBBD49C <= iVar3))
			{
				iVar2 = 0;
			}
			else
			{
				iVar2 = dword_6FBBD498 + iVar4;
			}
			D2_ASSERT(!((*(int*)(iVar2 + 0x8a) == 0) && (a2 == -1)));
			iVar3 = iVar3 + 1;
			*(int*)(iVar2 + 0x8a) = *(int*)(iVar2 + 0x8a) + a2;
			iVar4 = iVar4 + 0x8e;
		} while (iVar3 < (int)((uint32_t) * (uint8_t*)(iVar1 + 0x3d) + *(int*)(iVar1 + 0x60)));
	}
}

//D2Client.0x6FB54A90
void __fastcall sub_6FB54A90(int a1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	if (((((a1 != 0) && (dword_6FBBD498 != 0)) && (-1 < a1)) &&
	        ((a1 < dword_6FBBD49C && (iVar1 = dword_6FBBD498 + a1 * 0x8e, iVar1 != 0)))) &&
	    (iVar2 = *(int*)(iVar1 + 0x60), iVar2 < (int)((uint32_t) * (uint8_t*)(iVar1 + 0x3d) + iVar2)))
	{
		iVar4 = iVar2 * 0x8e;
		do
		{
			if (((dword_6FBBD498 == 0) || (iVar4 < 0)) || (dword_6FBBD49C <= iVar2))
			{
				iVar3 = 0;
			}
			else
			{
				iVar3 = iVar4 + dword_6FBBD498;
			}
			*(uint32_t*)(iVar3 + 0x8a) = 0;
			iVar2 = iVar2 + 1;
			iVar4 = iVar4 + 0x8e;
		} while (iVar2 < (int)((uint32_t) * (uint8_t*)(iVar1 + 0x3d) + *(int*)(iVar1 + 0x60)));
	}
}

//D2Client.0x6FB54B20
void __fastcall sub_6FB54B20(int a1)
{
	int iVar1;
	int iVar2;
	void* pvVar3;
	uint32_t uVar4;
	int iVar5;
	int iVar6;

	iVar1 = dword_6FBBD4B8;
	if ((dword_6FBBD498 != 0) && ((a1 == 0 || (0x18 < (uint32_t)(a1 - dword_6FBBD4B8)))))
	{
		iVar5 = 1;
		iVar6 = 0x8e;
		do
		{
			iVar1 = iVar6 + dword_6FBBD498;
			if ((*(int*)(iVar6 + 0x86 + dword_6FBBD498) == 0) &&
			    ((*(int*)(iVar1 + 0x8a) != 0 || (*(char*)(iVar1 + 0x4c) != '\0'))))
			{
				if (((a1 == 0) != 0) ||
				    ((dword_6FBBD4C0 < 0xf && (0xf9 < (uint32_t)(a1 - byte_6FBBD4BC)))))
				{
					sub_6FB54D90(iVar5, (uint32_t)(a1 == 0), 1);
					goto LAB_6fb54bb0;
				}
			}
			else
			{
			LAB_6fb54bb0:
				if ((*(int*)(iVar1 + 0x86) == 1) &&
				    (iVar2 = FOG_AsyncDataTestLoaded(*(AsyncData**)(iVar1 + 0x82)), iVar2 != 0))
				{
					D2_ASSERT(*(int*)(iVar1 + 0x86) == 1);
					pvVar3 = FOG_AsyncDataGetBuffer(*(AsyncData**)(iVar1 + 0x82));
					*(void**)(iVar1 + 0x6c) = pvVar3;
					uVar4 = FOG_AsyncDataGetBufferSize(*(AsyncData**)(iVar1 + 0x82));
					*(uint32_t*)(iVar1 + 0x70) = uVar4;
					*(uint32_t*)(iVar1 + 0x86) = 2;
					sub_6FB52330(iVar1);
					dword_6FBBD4C0 = dword_6FBBD4C0 - 1;
				}
			}
			iVar6 = iVar6 + 0x8e;
			iVar5 = iVar5 + 1;
			iVar1 = a1;
		} while (iVar6 < 0x65ae7);
	}
	dword_6FBBD4B8 = iVar1;
}

//D2Client.0x6FB54C50
uint32_t __cdecl sub_6FB54C50()
{
	return dword_6FBBD4B4;
}

//D2Client.0x6FB54C60
void __cdecl sub_6FB54C60()
{
	int iVar1;

	iVar1 = sub_6FB52CF0();
	if (iVar1 != 0)
	{
		sub_6FB53860();
		sub_6FB56DA0(dword_6FBBD4B4);
		sub_6FB54B20(dword_6FBBD4B4);
		sub_6FB560C0(dword_6FBBD4B4);
		sub_6FB52D10();
		dword_6FBBD4B4 = dword_6FBBD4B4 + 1;
		Sleep(0);
	}
}

//D2Client.0x6FB54CB0
void __fastcall sub_6FB54CB0()
{
	sub_6FB52940();
	sub_6FB55FC0();
}

//D2Client.0x6FB54CC0
void __fastcall sub_6FB54CC0(int a1)
{
	int* piVar1;
	int iVar2;

	if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
	{
		iVar2 = 0;
	}
	else
	{
		iVar2 = dword_6FBBD498 + a1 * 0x8e;
	}
	if (*(int*)(iVar2 + 0x86) != 0)
	{
		piVar1 = sub_6FB53780(a1);
		D2_ASSERT(piVar1 == nullptr);
		dword_6FBBD4C8 = dword_6FBBD4C8 - *(int*)(iVar2 + 0x70);
		D2SOUND_10059((int)&gpint32_t_6FBBD4B0, a1);
		*(uint32_t*)(iVar2 + 0x7c) = 0;
		if (*(AsyncData**)(iVar2 + 0x82) != nullptr)
		{
			FOG_AsyncDataFree(*(AsyncData**)(iVar2 + 0x82));
			*(uint32_t*)(iVar2 + 0x82) = 0;
			*(uint32_t*)(iVar2 + 0x6c) = 0;
			*(uint32_t*)(iVar2 + 0x86) = 0;
			return;
		}
		D2_FREE(*(void**)(iVar2 + 0x6c));
		*(uint32_t*)(iVar2 + 0x6c) = 0;
		*(uint32_t*)(iVar2 + 0x86) = 0;
	}
}

//D2Client.0x6FB54D90
void __fastcall sub_6FB54D90(int a1, int a2, int a3)
{
	char cVar1;
	int iVar2;
	bool bVar3;
	void* pvVar4;
	uint32_t uVar5;
	int iVar6;
	int iVar7;
	int* piVar8;
	HD2ARCHIVE__* pHVar9;
	D2CellFileStrc* pDVar10;
	AsyncData* pAsyncData;
	uint32_t uVar11;
	int iVar12;
	HSFILE__* pHVar13;
	HSFILE__* pHVar14;
	char* pcVar15;
	int* piVar16;
	char* pcVar17;
	uint32_t uVar18;
	int local_6c;
	HSFILE__* local_68;
	int local_64;
	int iStack_60;
	uint32_t uStack_5c;
	int local_58;
	int local_54;
	HSFILE__ local_50[20];

	if (dword_6FBBD498 == 0)
	{
		local_6c = 0;
	}
	else if ((a1 < 0) || (dword_6FBBD49C <= a1))
	{
		local_6c = 0;
	}
	else
	{
		local_6c = dword_6FBBD498 + a1 * 0x8e;
	}
	local_54 = dword_6FBBD4B4;
	if ((*(char*)(local_6c + 0x81) == '\0') && (iVar6 = *(int*)(local_6c + 0x86), iVar6 != 2))
	{
		local_64 = a2;
		local_58 = a1;
		if (iVar6 == 1)
		{
			if (a2 == 0)
			{
				return;
			}
			if (a2 != 0)
			{
				pvVar4 = FOG_AsyncDataGetBuffer(*(AsyncData**)(local_6c + 0x82));
				*(void**)(local_6c + 0x6c) = pvVar4;
				uVar5 = FOG_AsyncDataGetBufferSize(*(AsyncData**)(local_6c + 0x82));
				*(uint32_t*)(local_6c + 0x70) = uVar5;
				*(uint32_t*)(local_6c + 0x86) = 2;
				sub_6FB52330(local_6c);
				dword_6FBBD4C0 = dword_6FBBD4C0 - 1;
				return;
			}
		}
		if (iVar6 == 0)
		{
			if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
			{
				pcVar17 = nullptr;
			}
			else
			{
				pcVar17 = (char*)(dword_6FBBD498 + a1 * 0x8e);
			}
			if ((a1 < 0xb76) || (0x1230 < a1))
			{
				iVar6 = 0;
				do
				{
					cVar1 = "DATA\\GLOBAL"[iVar6];
					*(char*)((int)&local_50[0].unused + iVar6) = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
			}
			else
			{
				iVar6 = 0;
				do
				{
					cVar1 = "DATA\\LOCAL"[iVar6];
					*(char*)((int)&local_50[0].unused + iVar6) = cVar1;
					iVar6 = iVar6 + 1;
				} while (cVar1 != '\0');
			}
			if ((a1 < 0x1231) || (0x125a < a1))
			{
				iVar6 = -1;
				pHVar13 = local_50;
				do
				{
					pHVar14 = pHVar13;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pHVar14 = (HSFILE__*)((int)&pHVar13->unused + 1);
					piVar16 = &pHVar13->unused;
					pHVar13 = pHVar14;
				} while ((char)*piVar16 != '\0');
				*(uint32_t*)((int)&pHVar14[-1].unused + 3) = dword_6FB96A84;
				*(uint16_t*)((int)&pHVar14->unused + 3) = word_6FB96A88;
			}
			else
			{
				iVar6 = -1;
				pHVar13 = local_50;
				do
				{
					pHVar14 = pHVar13;
					if (iVar6 == 0)
						break;
					iVar6 = iVar6 + -1;
					pHVar14 = (HSFILE__*)((int)&pHVar13->unused + 1);
					piVar16 = &pHVar13->unused;
					pHVar13 = pHVar14;
				} while ((char)*piVar16 != '\0');
				*(uint32_t*)((int)&pHVar14[-1].unused + 3) = dword_6FB96A8C;
				*(uint32_t*)((int)&pHVar14->unused + 3) = dword_6FB96A90;
			}
			uVar5 = 0xffffffff;
			pcVar15 = pcVar17;
			do
			{
				if (uVar5 == 0)
					break;
				uVar5 = uVar5 - 1;
				cVar1 = *pcVar15;
				pcVar15 = pcVar15 + 1;
			} while (cVar1 != '\0');
			uVar11 = 0xffffffff;
			pHVar13 = local_50;
			do
			{
				if (uVar11 == 0)
					break;
				uVar11 = uVar11 - 1;
				piVar16 = &pHVar13->unused;
				pHVar13 = (HSFILE__*)((int)&pHVar13->unused + 1);
			} while ((char)*piVar16 != '\0');
			D2_ASSERT(0x4f >= ~uVar5 + (~uVar11 - 2));
			local_68 = local_50;
			uVar5 = 0xffffffff;
			do
			{
				pcVar15 = pcVar17;
				if (uVar5 == 0)
					break;
				uVar5 = uVar5 - 1;
				pcVar15 = pcVar17 + 1;
				cVar1 = *pcVar17;
				pcVar17 = pcVar15;
			} while (cVar1 != '\0');
			uVar5 = ~uVar5;
			iVar6 = -1;
			pHVar13 = local_68;
			do
			{
				pHVar14 = pHVar13;
				if (iVar6 == 0)
					break;
				iVar6 = iVar6 + -1;
				pHVar14 = (HSFILE__*)((int)&pHVar13->unused + 1);
				piVar16 = &pHVar13->unused;
				pHVar13 = pHVar14;
			} while ((char)*piVar16 != '\0');
			pcVar17 = pcVar15 + -uVar5;
			pcVar15 = (char*)((int)&pHVar14[-1].unused + 3);
			for (uVar11 = uVar5 >> 2; uVar11 != 0; uVar11 = uVar11 - 1)
			{
				*(uint32_t*)pcVar15 = *(uint32_t*)pcVar17;
				pcVar17 = pcVar17 + 4;
				pcVar15 = pcVar15 + 4;
			}
			for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
			{
				*pcVar15 = *pcVar17;
				pcVar17 = pcVar17 + 1;
				pcVar15 = pcVar15 + 1;
			}
			iVar6 = FOG_FOpenFile((char*)local_50, &local_68);
			if (iVar6 == 0)
			{
				*(uint8_t*)(local_6c + 0x81) = 1;
				return;
			}
			uVar5 = FOG_FGetFileSize(local_68, nullptr);
			FOG_FCloseFile(local_68);
			if (dword_6FBBD4C4 < dword_6FBBD4C8 + uVar5)
			{
				uStack_5c = dword_6FBBD4C4 - uVar5;
				iStack_60 = dword_6FBBD4B4;
				iVar6 = dword_6FBBD498;
				if (uStack_5c < (uint32_t)dword_6FBBD4C8)
				{
				LAB_6fb54fe0:
					bVar3 = false;
					iVar12 = 0;
					piVar16 = gpint32_t_6FBBD4B0;
				joined_r0x6fb54fec:
					do
					{
						if (piVar16 != nullptr)
						{
							iVar2 = *piVar16;
							if (((iVar6 == 0) || (iVar2 < 0)) || (dword_6FBBD49C <= iVar2))
							{
								iVar7 = 0;
							}
							else
							{
								iVar7 = iVar6 + iVar2 * 0x8e;
							}
							if ((((iVar12 == 0) &&
							         ((*(int*)(iVar7 + 0x8a) != 0 || (*(char*)(iVar7 + 0x4c) != '\0')))) ||
							        ((a3 != 0 && ((uint32_t)(iStack_60 - *(int*)(iVar7 + 0x7c)) < 0x2ee)))) ||
							    (piVar8 = sub_6FB53780(iVar2), iVar6 = dword_6FBBD498, piVar8 != nullptr))
							{
								piVar16 = (int*)piVar16[1];
								goto joined_r0x6fb54fec;
							}
							sub_6FB54CC0(iVar2);
							bVar3 = true;
							iVar6 = dword_6FBBD498;
						}
						if ((local_64 == 0) || (iVar12 = iVar12 + 1, piVar16 = gpint32_t_6FBBD4B0, 1 < iVar12))
							goto LAB_6fb5507c;
					} while (true);
				}
			}
		LAB_6fb5509e:
			if (local_64 != 0)
			{
				uVar18 = 0x301;
				pcVar17 = __FILE__;
				piVar16 = (int*)(local_6c + 0x70);
				pHVar9 = D2Win_GetArchive();
				pDVar10 = (D2CellFileStrc*)(ARCHIVE_AllocateBufferAndReadFile((HD2ARCHIVE)((HSFILE__*)pHVar9), (const char*)(local_50), (size_t*)(piVar16), pcVar17, uVar18));
				*(D2CellFileStrc**)(local_6c + 0x6c) = pDVar10;
				if ((pDVar10 != nullptr) && (iVar6 = *(int*)(local_6c + 0x70), iVar6 != 0))
				{
					dword_6FBBD4C8 = dword_6FBBD4C8 + iVar6;
					if ((dword_6FBBD498 == 0) || ((a1 < 0 || (dword_6FBBD49C <= a1))))
					{
						iVar6 = 0;
					}
					else
					{
						iVar6 = dword_6FBBD498 + a1 * 0x8e;
					}
					*(int*)(iVar6 + 0x7c) = dword_6FBBD4B4;
					D2SOUND_10059((int)&gpint32_t_6FBBD4B0, a1);
					D2SOUND_10063((int)&gpint32_t_6FBBD4B0, a1);
					*(uint32_t*)(local_6c + 0x86) = 2;
					sub_6FB52330(local_6c);
					return;
				}
				FOG_DisplayAssert("ptHeader->pbWaveData && ptHeader->dwWaveSize",
				    __FILE__, __LINE__);
				exit(-1);
			}
			pAsyncData = FOG_AsyncDataLoadFileEx(nullptr, (char*)local_50, 1, 0, -1, nullptr,
			    nullptr, -2,
			    __FILE__, __LINE__);
			*(AsyncData**)(local_6c + 0x82) = pAsyncData;
			if (pAsyncData != nullptr)
			{
				uVar5 = FOG_AsyncDataGetBufferSize(pAsyncData);
				*(uint32_t*)(local_6c + 0x70) = uVar5;
				dword_6FBBD4C8 = dword_6FBBD4C8 + uVar5;
				if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
				{
					iVar6 = 0;
				}
				else
				{
					iVar6 = dword_6FBBD498 + a1 * 0x8e;
				}
				*(int*)(iVar6 + 0x7c) = dword_6FBBD4B4;
				D2SOUND_10059((int)&gpint32_t_6FBBD4B0, a1);
				D2SOUND_10063((int)&gpint32_t_6FBBD4B0, a1);
				*(uint32_t*)(local_6c + 0x86) = 1;
				dword_6FBBD4C0 = dword_6FBBD4C0 + 1;
			}
		}
	}
	return;
LAB_6fb5507c:
	if (!bVar3)
	{
		byte_6FBBD4BC = local_54;
		return;
	}
	a1 = local_58;
	if ((uint32_t)dword_6FBBD4C8 <= uStack_5c)
		goto LAB_6fb5509e;
	goto LAB_6fb54fe0;
}

//D2Client.0x6FB55230
double __fastcall sub_6FB55230(int a1)
{
	int iVar1;

	if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
	{
		iVar1 = 0;
	}
	else
	{
		iVar1 = dword_6FBBD498 + a1 * 0x8e;
	}
	switch (*(uint32_t*)(iVar1 + 0x47))
	{
	default:
		return (double)60.0;
	case 2:
		return (double)200.0;
	case 3:
		return (double)400.0;
	case 4:
		return (double)2000.0;
	}
}

//D2Client.0x6FB552A0
double __fastcall sub_6FB552A0(int a1)
{
	int iVar1;

	if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
	{
		iVar1 = 0;
	}
	else
	{
		iVar1 = dword_6FBBD498 + a1 * 0x8e;
	}
	switch (*(uint32_t*)(iVar1 + 0x47))
	{
	case 0:
		return (double)400.0;
	default:
		return (double)700.0;
	case 2:
		return (double)1000.0;
	case 3:
		return (double)1500.0;
	case 4:
		return (double)2000.0;
	}
}

//D2Client.0x6FB55310
int __fastcall sub_6FB55310(int a1)
{
	uint8_t bVar1;
	uint32_t uVar2;
	int iVar3;
	int iVar4;
	int* piVar5;
	int iVar6;
	int iVar7;

	if (dword_6FBBD498 == 0)
	{
		return a1;
	}
	if ((a1 < 0) || (dword_6FBBD49C <= a1))
	{
		iVar6 = 0;
	}
	else
	{
		iVar6 = dword_6FBBD498 + a1 * 0x8e;
	}
	bVar1 = *(uint8_t*)(iVar6 + 0x3d);
	if (1 < bVar1)
	{
		iVar7 = bVar1 - 1;
		if (1 < iVar7)
		{
			iVar7 = 2;
		}
		if ((bVar1 < 4) && (uVar2 = sub_6FB57150(bVar1 + 1), uVar2 == 0))
		{
			iVar7 = iVar7 + -1;
		}
		do
		{
			uVar2 = sub_6FB57150((uint32_t) * (uint8_t*)(iVar6 + 0x3d));
			iVar3 = uVar2 + a1;
			iVar4 = 0;
			if (iVar7 < 1)
			{
				return iVar3;
			}
			piVar5 = (int*)(iVar6 + 100);
			while (iVar3 != *piVar5)
			{
				iVar4 = iVar4 + 1;
				piVar5 = piVar5 + 1;
				if (iVar7 <= iVar4)
				{
					return iVar3;
				}
			}
		} while (true);
	}
	return a1;
}

//D2Client.0x6FB553A0
void __fastcall sub_6FB553A0(uint32_t a1)
{
	dword_6FBBD4C4 = a1;
}

//D2Client.0x6FB553B0
void __fastcall sub_6FB553B0(int a1, char* a2)
{
	char cVar1;
	char* pcVar2;
	int iVar3;
	uint32_t uVar4;
	uint32_t uVar5;
	char* pcVar6;
	char* pcVar7;

	if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
	{
		pcVar6 = nullptr;
	}
	else
	{
		pcVar6 = (char*)(dword_6FBBD498 + a1 * 0x8e);
	}
	if ((a1 < 0xb76) || (0x1230 < a1))
	{
		pcVar2 = "DATA\\GLOBAL";
		do
		{
			cVar1 = *pcVar2;
			(a2 + -(int)"DATA\\GLOBAL")[(int)pcVar2] = cVar1;
			pcVar2 = pcVar2 + 1;
		} while (cVar1 != '\0');
	}
	else
	{
		pcVar2 = "DATA\\LOCAL";
		do
		{
			cVar1 = *pcVar2;
			(a2 + -(int)"DATA\\LOCAL")[(int)pcVar2] = cVar1;
			pcVar2 = pcVar2 + 1;
		} while (cVar1 != '\0');
	}
	if ((a1 < 0x1231) || (0x125a < a1))
	{
		iVar3 = -1;
		pcVar2 = a2;
		do
		{
			pcVar7 = pcVar2;
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			pcVar7 = pcVar2 + 1;
			cVar1 = *pcVar2;
			pcVar2 = pcVar7;
		} while (cVar1 != '\0');
		*(uint32_t*)(pcVar7 + -1) = dword_6FB96A84;
		*(uint16_t*)(pcVar7 + 3) = word_6FB96A88;
	}
	else
	{
		iVar3 = -1;
		pcVar2 = a2;
		do
		{
			pcVar7 = pcVar2;
			if (iVar3 == 0)
				break;
			iVar3 = iVar3 + -1;
			pcVar7 = pcVar2 + 1;
			cVar1 = *pcVar2;
			pcVar2 = pcVar7;
		} while (cVar1 != '\0');
		*(uint32_t*)(pcVar7 + -1) = dword_6FB96A8C;
		*(uint32_t*)(pcVar7 + 3) = dword_6FB96A90;
	}
	uVar4 = 0xffffffff;
	pcVar2 = pcVar6;
	do
	{
		if (uVar4 == 0)
			break;
		uVar4 = uVar4 - 1;
		cVar1 = *pcVar2;
		pcVar2 = pcVar2 + 1;
	} while (cVar1 != '\0');
	uVar5 = 0xffffffff;
	pcVar2 = a2;
	do
	{
		if (uVar5 == 0)
			break;
		uVar5 = uVar5 - 1;
		cVar1 = *pcVar2;
		pcVar2 = pcVar2 + 1;
	} while (cVar1 != '\0');
	D2_ASSERT(0x4f >= ~uVar4 + (~uVar5 - 2));
	uVar4 = 0xffffffff;
	do
	{
		pcVar2 = pcVar6;
		if (uVar4 == 0)
			break;
		uVar4 = uVar4 - 1;
		pcVar2 = pcVar6 + 1;
		cVar1 = *pcVar6;
		pcVar6 = pcVar2;
	} while (cVar1 != '\0');
	uVar4 = ~uVar4;
	iVar3 = -1;
	do
	{
		pcVar6 = a2;
		if (iVar3 == 0)
			break;
		iVar3 = iVar3 + -1;
		pcVar6 = a2 + 1;
		cVar1 = *a2;
		a2 = pcVar6;
	} while (cVar1 != '\0');
	pcVar2 = pcVar2 + -uVar4;
	pcVar6 = pcVar6 + -1;
	for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
	{
		*(uint32_t*)pcVar6 = *(uint32_t*)pcVar2;
		pcVar2 = pcVar2 + 4;
		pcVar6 = pcVar6 + 4;
	}
	for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1)
	{
		*pcVar6 = *pcVar2;
		pcVar2 = pcVar2 + 1;
		pcVar6 = pcVar6 + 1;
	}
}

//D2Client.0x6FB554D0
void __fastcall sub_6FB554D0(int a1)
{
	int iVar1;

	if (((dword_6FBBD498 == 0) || (a1 < 0)) || (dword_6FBBD49C <= a1))
	{
		iVar1 = 0;
	}
	else
	{
		iVar1 = dword_6FBBD498 + a1 * 0x8e;
	}
	*(uint32_t*)(iVar1 + 0x7c) = dword_6FBBD4B4;
	D2SOUND_10059((int)&gpint32_t_6FBBD4B0, a1);
	D2SOUND_10063((int)&gpint32_t_6FBBD4B0, a1);
}

//D2Client.0x6FB55520
bool __fastcall sub_6FB55520(int a1)
{
	int* piVar1;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar1 + 8) == a1)
			{
				return *(int*)(*piVar1 + 0x30) == 1;
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return false;
}

//D2Client.0x6FB55550
int* __fastcall sub_6FB55550(int a1)
{
	int* piVar1;
	int* piVar2;
	int iVar3;

	if ((a1 != 0) && (piVar1 = gpint32_t_6FBC1A58, gpint32_t_6FBC1A58 != nullptr))
	{
		do
		{
			if (*(int*)(*piVar1 + 8) == a1)
			{
				piVar1 = *(int**)(*piVar1 + 0x2c);
				piVar2 = gpint32_t_6FBC1A58;
				if (piVar1 == nullptr)
				{
					return nullptr;
				}
				while (*(int*)(*piVar2 + 8) != a1)
				{
					piVar2 = (int*)piVar2[1];
					if (piVar2 == nullptr)
					{
						return piVar2;
					}
				}
				if (*(int*)(*piVar2 + 0x30) != 1)
				{
					return nullptr;
				}
				iVar3 = sub_6FB537E0(piVar1);
				if (iVar3 == 0)
				{
					return nullptr;
				}
				return (int*)0x1;
			}
			piVar1 = (int*)piVar1[1];
		} while (piVar1 != nullptr);
	}
	return nullptr;
}

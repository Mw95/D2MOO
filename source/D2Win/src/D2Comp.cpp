#include "D2WinComp.h"

#include <algorithm>
#include <cstring>
#include <iterator>

#include <D2BasicTypes.h>
#include <D2Math.h>

#include <Fog.h>
#include <D2BitManip.h>
#include <D2CMP.h>
#include <Archive.h>
#include <D2Lang.h>

#include <D2Gfx.h>
#include <Texture.h>

#include "D2WinArchive.h"
#include "D2WinFont.h"
#include "D2WinMain.h"
#include "D2WinPalette.h"


#pragma pack(push, 1)
// Layout of the ItemTypes.txt records, D2Win only loads a few columns
struct D2CompItemTypesTxt
{
	char szCode[4];							//0x00
	int16_t nEquiv1;						//0x04
	int16_t nEquiv2;						//0x06
	uint8_t nRepair;						//0x08
	uint8_t nBody;							//0x09
	uint8_t nBodyLoc1;						//0x0A
	uint8_t nBodyLoc2;						//0x0B
	uint16_t wShoots;						//0x0C
	uint16_t wQuiver;						//0x0E
	uint8_t nThrowable;						//0x10
	uint8_t nReload;						//0x11
	uint8_t nReEquip;						//0x12
	uint8_t nAutoStack;						//0x13
	uint8_t nMagic;							//0x14
	uint8_t nRare;							//0x15
	uint8_t nNormal;						//0x16
	uint8_t nCharm;							//0x17
	uint8_t nGem;							//0x18
	uint8_t nBeltable;						//0x19
	uint8_t nMaxSock1;						//0x1A
	uint8_t nMaxSock25;						//0x1B
	uint8_t nMaxSock40;						//0x1C
	uint8_t nTreasureClass;					//0x1D
	uint8_t nRarity;						//0x1E
	uint8_t nStaffMods;						//0x1F
	uint8_t nCostFormula;					//0x20
	uint8_t nClass;							//0x21
	uint8_t nStorePage;						//0x22
	uint8_t nVarInvGfx;						//0x23
	char szInvGfx[6][32];					//0x24
};

// Layout of the Weapons.txt/Armor.txt/Misc.txt records, D2Win only loads a few columns
struct D2CompItemsTxt
{
	char szFlippyFile[32];					//0x00
	char szInvFile[32];						//0x20
	char szUniqueInvFile[32];				//0x40
	char szSetInvFile[32];					//0x60
	uint32_t dwCode;						//0x80
	uint32_t dwNormCode;					//0x84
	uint32_t dwUberCode;					//0x88
	uint32_t dwUltraCode;					//0x8C
	uint32_t dwAlternateGfx;				//0x90
	uint32_t dwPspell;						//0x94
	uint16_t wState;						//0x98
	uint16_t wCurseState[2];				//0x9A
	uint16_t wStat[3];						//0x9E
	uint32_t dwCalc[3];						//0xA4
	uint32_t dwLen;							//0xB0
	uint8_t nSpellDesc;						//0xB4
	uint8_t pad0xB5;						//0xB5
	uint16_t wSpellDescStr;					//0xB6
	uint32_t dwSpellDescCalc;				//0xB8
	uint32_t dwBetterGem;					//0xBC
	uint32_t dwWeapClass;					//0xC0
	uint32_t dwWeapClass2Hand;				//0xC4
	uint32_t dwTransmogrifyType;			//0xC8
	int32_t dwMinAc;						//0xCC
	int32_t dwMaxAc;						//0xD0
	uint32_t dwGambleCost;					//0xD4
	int32_t dwSpeed;						//0xD8
	uint32_t dwBitField1;					//0xDC
	uint32_t dwCost;						//0xE0
	uint32_t dwMinStack;					//0xE4
	uint32_t dwMaxStack;					//0xE8
	uint32_t dwSpawnStack;					//0xEC
	uint32_t dwGemOffset;					//0xF0
	uint16_t wNameStr;						//0xF4
	uint16_t wVersion;						//0xF6
	uint16_t wAutoPrefix;					//0xF8
	uint16_t wMissileType;					//0xFA
	uint8_t nRarity;						//0xFC
	uint8_t nLevel;							//0xFD
	uint8_t nMinDam;						//0xFE
	uint8_t nMaxDam;						//0xFF
	uint8_t nMinMisDam;						//0x100
	uint8_t nMaxMisDam;						//0x101
	uint8_t n2HandMinDam;					//0x102
	uint8_t n2HandMaxDam;					//0x103
	uint8_t nRangeAdder;					//0x104
	uint8_t pad0x105;						//0x105
	int16_t nStrBonus;						//0x106
	int16_t nDexBonus;						//0x108
	uint16_t wReqStr;						//0x10A
	uint16_t wReqDex;						//0x10C
	uint8_t nAbsorb;						//0x10E
	uint8_t nInvWidth;						//0x10F
	uint8_t nInvHeight;						//0x110
	uint8_t nBlock;							//0x111
	uint8_t nDurability;					//0x112
	uint8_t nNoDurability;					//0x113
	uint8_t nMissile;						//0x114
	uint8_t nComponent;						//0x115
	uint8_t nArmorComp[6];					//0x116
	uint8_t n2Handed;						//0x11C
	uint8_t nUseable;						//0x11D
	int16_t wType;							//0x11E
	int16_t wType2;							//0x120
	uint8_t nSubType;						//0x122
	uint8_t pad0x123;						//0x123
	uint16_t wDropSound;					//0x124
	uint16_t wUseSound;						//0x126
	uint8_t nDropSfxFrame;					//0x128
	uint8_t nUnique;						//0x129
	uint8_t nQuest;							//0x12A
	uint8_t nQuestDiffCheck;				//0x12B
	uint8_t nTransparent;					//0x12C
	uint8_t nTransTbl;						//0x12D
	uint8_t pad0x12E;						//0x12E
	uint8_t nLightRadius;					//0x12F
	uint8_t nBelt;							//0x130
	uint8_t nAutoBelt;						//0x131
	uint8_t nStackable;						//0x132
	uint8_t nSpawnable;						//0x133
	uint8_t nSpellIcon;						//0x134
	uint8_t nDurWarning;					//0x135
	uint8_t nQuantityWarning;				//0x136
	uint8_t nHasInv;						//0x137
	uint8_t nGemSockets;					//0x138
	uint8_t nTransmogrify;					//0x139
	uint8_t nTmogMin;						//0x13A
	uint8_t nTmogMax;						//0x13B
	uint8_t nHitClass;						//0x13C
	uint8_t n1or2Handed;					//0x13D
	uint8_t nGemApplyType;					//0x13E
	uint8_t nLevelReq;						//0x13F
	uint8_t nMagicLevel;					//0x140
	int8_t nTransform;						//0x141
	int8_t nInvTrans;						//0x142
	uint8_t nCompactSave;					//0x143
	uint8_t nSkipName;						//0x144
	uint8_t nNameable;						//0x145
	uint8_t nVendorMin[17];					//0x146
	uint8_t nVendorMax[17];					//0x157
	uint8_t nVendorMagicMin[17];			//0x168
	uint8_t nVendorMagicMax[17];			//0x179
	uint8_t nVendorMagicLvl[17];			//0x18A
	uint8_t pad0x19B;						//0x19B
	uint32_t dwNightmareUpgrade;			//0x19C
	uint32_t dwHellUpgrade;					//0x1A0
	uint8_t nPermStoreItem;					//0x1A4
	uint8_t nMultibuy;						//0x1A5
	uint16_t pad0x1A6;						//0x1A6
};

struct D2CompItemDataTbl
{
	int32_t nItemsTxtRecordCount;			//0x00
	D2CompItemsTxt* pItemsTxt;				//0x04
	D2CompItemsTxt* pWeapons;				//0x08
	int32_t nWeaponsTxtRecordCount;			//0x0C
	D2CompItemsTxt* pArmor;					//0x10
	int32_t nArmorTxtRecordCount;			//0x14
	D2CompItemsTxt* pMisc;					//0x18
	int32_t nMiscTxtRecordCount;			//0x1C
};

struct D2CompItemStrc
{
	uint32_t dwCode;						//0x00
	uint32_t nHitClass;						//0x04
	int32_t nItemType;						//0x08
};

struct D2CompHitClassMappingStrc
{
	uint32_t dwToken;						//0x00
	int32_t nIndex;							//0x04
};

struct D2CompExtraDataStringStrc
{
	Unicode wszText[256];					//0x00
	int32_t nWidth;							//0x200
	int32_t nHeight;						//0x204
};
#pragma pack(pop)

static_assert(sizeof(D2CompItemTypesTxt) == 0xE4, "D2CompItemTypesTxt size mismatch");
static_assert(sizeof(D2CompItemsTxt) == 0x1A8, "D2CompItemsTxt size mismatch");


constexpr int32_t COMPOSITEUNITCLASS_NUMCLASSES = 25;
constexpr int32_t NUM_COMPONENTS = 16;
constexpr int32_t CELFILE_NUMGAMEDIRECTIONS = 64;
constexpr int32_t MAX_COMPONENT_ITEMS = 255;
constexpr int32_t MAXIMUM_NUMBER_OF_EXTRA_DATA_STRINGS = 7;
constexpr int32_t ITEM_PALETTE_SHIFTS = 21;
constexpr uint8_t COF_VERSION = 20;


//D2Win.0x6F8BC040
const uint32_t gdwUnitTokens_6F8BC040[COMPOSITEUNITCLASS_NUMCLASSES] =
{
	'  MA', '  OS', '  EN', '  AP', '  AB', '  ZD', '  IA', '  OR', '  HR', '  HR', '  1O', '  2O', '  3O',
	'  4O', '  DM', '  9O', '  YO', '  YO', '  5O', '  7O', '  8O', '  6O', '  0O', '  CT', '  OR',
};
//D2Win.0x6F8BC0A4
const int32_t gnUnitTokenTblSize_6F8BC0A4 = COMPOSITEUNITCLASS_NUMCLASSES;
//D2Win.0x6F8BC0A8
const uint32_t gdwPlayerModeTokens_6F8BC0A8[] =
{
	'  TD', '  UN', '  LW', '  NR', '  HG', '  NT', '  WT', '  1A', '  2A', '  LB',
	'  CS', '  HT', '  KK', '  1S', '  2S', '  3S', '  4S', '  DD', '  HG', '  HG',
};
//D2Win.0x6F8BC0F8
const uint32_t gnPlayerModeTokenTblSize_6F8BC0F8 = ARRAY_SIZE(gdwPlayerModeTokens_6F8BC0A8);
//D2Win.0x6F8BC100
const uint32_t gdwComponentTokens_6F8BC100[NUM_COMPONENTS] =
{
	'  DH', '  RT', '  GL', '  AR', '  AL', '  HR', '  HL', '  HS', '  1S', '  2S', '  3S', '  4S', '  5S', '  6S', '  7S', '  8S',
};
//D2Win.0x6F8BC154
const uint32_t gdwWClassTokens_6F8BC154[] =
{
	0,
	' hth',
	' th1',
	' th2',
	' sh1',
	' sh2',
	' wob',
	' wbx',
	' fts',
	' sj1',
	' tj1',
	' ss1',
	' ts1',
	' 1th',
	' 2th',
};
//D2Win.0x6F8BC190
const uint32_t gnWClassTokenTblSize_6F8BC190 = ARRAY_SIZE(gdwWClassTokens_6F8BC154);

// Legacy component item table (item code, hit class, item type)
//D2Win.0x6F8BC1D8
const D2CompItemStrc gStaticComponentItems_6F8BC1D8[] =
{
	{ 0, 0, 1 },
	{ ' til', 0, 1 },
	{ ' dem', 0, 1 },
	{ ' yvh', 0, 1 },
	{ ' pac', 0, 37 },
	{ ' pks', 0, 37 },
	{ ' mlh', 0, 37 },
	{ ' lhf', 0, 37 },
	{ ' mhg', 0, 37 },
	{ ' nrc', 0, 37 },
	{ ' ksm', 0, 37 },
	{ ' epc', 0, 3 },
	{ ' klc', 0, 3 },
	{ ' bor', 0, 3 },
	{ ' iuq', 0, 3 },
	{ ' ael', 0, 3 },
	{ ' alh', 0, 3 },
	{ ' uts', 0, 3 },
	{ ' gnr', 0, 3 },
	{ ' lcs', 0, 3 },
	{ ' nhc', 0, 3 },
	{ ' srb', 0, 3 },
	{ ' lps', 0, 3 },
	{ ' tlp', 0, 3 },
	{ ' dlf', 0, 3 },
	{ ' htg', 0, 3 },
	{ ' luf', 0, 3 },
	{ ' cub', 0, 2 },
	{ ' grl', 0, 2 },
	{ ' tik', 0, 2 },
	{ ' wot', 0, 2 },
	{ ' lgl', 0, 16 },
	{ ' lgm', 0, 16 },
	{ ' lgh', 0, 16 },
	{ ' tbl', 0, 15 },
	{ ' tbm', 0, 15 },
	{ ' tbh', 0, 15 },
	{ ' lbl', 0, 19 },
	{ ' lbm', 0, 19 },
	{ ' lbh', 0, 19 },
	{ ' mhb', 0, 37 },
	{ ' hsb', 0, 2 },
	{ ' kps', 0, 2 },
	{ ' dnw', 4, 25 },
	{ ' nwy', 4, 25 },
	{ ' nwb', 4, 25 },
	{ ' blc', 4, 29 },
	{ ' xah', 4, 43 },
	{ ' dss', 4, 30 },
	{ ' mcs', 4, 30 },
	{ ' cam', 4, 36 },
	{ ' exa', 4, 28 },
	{ ' clf', 4, 30 },
	{ ' dsl', 4, 30 },
	{ ' alf', 4, 36 },
	{ ' mdh', 4, 31 },
	{ ' mhw', 4, 31 },
	{ ' src', 4, 30 },
	{ ' slf', 4, 30 },
	{ ' lpg', 2, 38 },
	{ ' spg', 2, 38 },
	{ ' lpo', 2, 38 },
	{ ' spo', 2, 38 },
	{ ' rgd', 2, 32 },
	{ ' 33d', 2, 32 },
	{ ' 33g', 2, 32 },
	{ ' rid', 2, 32 },
	{ ' vaj', 2, 33 },
	{ ' vlg', 2, 33 },
	{ ' lip', 2, 33 },
	{ ' mlc', 5, 30 },
	{ ' dsg', 5, 30 },
	{ ' rps', 3, 33 },
	{ ' irt', 3, 33 },
	{ ' kip', 3, 33 },
	{ ' rps', 3, 33 },
	{ ' wbs', 6, 27 },
	{ ' wbl', 6, 27 },
	{ ' bbs', 6, 27 },
	{ ' bbl', 6, 27 },
	{ ' tss', 8, 26 },
	{ ' tsl', 8, 26 },
	{ ' tsc', 8, 26 },
	{ ' tsb', 8, 26 },
	{ ' xal', 8, 28 },
	{ ' ycs', 8, 34 },
	{ ' xig', 8, 28 },
	{ ' xtb', 8, 28 },
	{ ' lah', 8, 34 },
	{ ' uam', 8, 31 },
	{ ' xap', 8, 34 },
	{ ' lah', 8, 34 },
	{ ' bxh', 7, 35 },
	{ ' bxl', 7, 35 },
	{ ' xat', 4, 43 },
	{ ' cps', 4, 29 },
	{ ' rbs', 4, 30 },
	{ ' tsm', 4, 36 },
	{ ' pcs', 4, 24 },
	{ ' mpg', 2, 38 },
	{ ' mpo', 2, 38 },
	{ ' fkt', 2, 42 },
	{ ' dlb', 2, 32 },
	{ ' dsb', 4, 30 },
	{ ' wsb', 4, 30 },
	{ ' sh2', 5, 30 },
	{ ' nrb', 3, 33 },
	{ ' wbh', 6, 27 },
	{ ' wbc', 6, 27 },
	{ ' bws', 6, 27 },
	{ ' bwl', 6, 27 },
	{ ' tsw', 8, 26 },
	{ ' xab', 8, 28 },
	{ ' rab', 8, 34 },
	{ ' xag', 8, 28 },
	{ ' bxr', 7, 35 },
	{ ' bxm', 7, 35 },
	{ ' tbz', 0, 1 },
	{ ' raa', 0, 3 },
	{ ' ptl', 0, 3 },
	{ ' lms', 0, 2 },
	{ ' stg', 0, 3 },
	{ ' vqa', 0, 40 },
	{ ' vqc', 0, 40 },
	{ ' lbv', 0, 19 },
	{ ' lbt', 0, 19 },
	{ ' lgv', 0, 16 },
	{ ' lgt', 0, 16 },
	{ ' tbv', 0, 15 },
	{ ' tbt', 0, 15 },
	{ ' blf', 5, 30 },
	{ ' ipm', 4, 28 },
	{ ' lab', 4, 43 },
	{ ' gel', 4, 29 },
	{ ' tlq', 0, 3 },
	{ ' xa2', 4, 28 },
	{ ' xaw', 4, 28 },
	{ ' nwg', 4, 36 },
	{ ' amg', 8, 36 },
	{ ' dsw', 4, 30 },
	{ ' sig', 5, 30 },
	{ ' dlb', 2, 32 },
	{ ' fkb', 2, 32 },
	{ ' pss', 2, 33 },
	{ ' pst', 2, 33 },
	{ ' eps', 3, 33 },
	{ ' uov', 8, 34 },
	{ ' csw', 8, 34 },
	{ ' irk', 2, 32 },
	{ ' tps', 2, 33 },
	{ ' csg', 2, 24 },
	{ ' psw', 2, 24 },
	{ ' tsh', 3, 26 },
	{ ' fsm', 3, 26 },
	{ ' hfh', 4, 36 },
	{ ' ah9', 4, 28 },
	{ ' xa9', 4, 28 },
	{ ' a29', 4, 28 },
	{ ' pm9', 4, 28 },
	{ ' aw9', 4, 28 },
	{ ' al9', 8, 28 },
	{ ' ab9', 8, 28 },
	{ ' tb9', 8, 28 },
	{ ' ag9', 8, 28 },
	{ ' ig9', 8, 28 },
	{ ' nw9', 4, 25 },
	{ ' wy9', 4, 25 },
	{ ' wb9', 4, 25 },
	{ ' wg9', 4, 25 },
	{ ' lc9', 4, 36 },
	{ ' cs9', 4, 24 },
	{ ' sq9', 4, 24 },
	{ ' sw9', 4, 24 },
	{ ' ps9', 4, 36 },
	{ ' am9', 4, 36 },
	{ ' tm9', 4, 36 },
	{ ' lf9', 4, 36 },
	{ ' hw9', 4, 36 },
	{ ' 9m9', 8, 36 },
	{ ' mg9', 8, 36 },
	{ ' ss9', 4, 30 },
	{ ' ms9', 4, 30 },
	{ ' bs9', 4, 30 },
	{ ' cf9', 4, 30 },
	{ ' rc9', 4, 30 },
	{ ' sb9', 4, 30 },
	{ ' sl9', 4, 30 },
	{ ' dw9', 4, 30 },
	{ ' h29', 4, 30 },
	{ ' mc9', 4, 30 },
	{ ' sg9', 4, 30 },
	{ ' 9b9', 4, 30 },
	{ ' bf9', 4, 30 },
	{ ' dg9', 4, 30 },
	{ ' gd9', 2, 32 },
	{ ' id9', 2, 32 },
	{ ' rk9', 2, 32 },
	{ ' lb9', 2, 32 },
	{ ' kt9', 2, 42 },
	{ ' at9', 4, 43 },
	{ ' kb9', 2, 42 },
	{ ' 8b9', 4, 43 },
	{ ' aj9', 2, 33 },
	{ ' ip9', 2, 33 },
	{ ' 9s9', 2, 33 },
	{ ' lg9', 2, 33 },
	{ ' st9', 2, 33 },
	{ ' rs9', 3, 33 },
	{ ' rt9', 3, 33 },
	{ ' rb9', 3, 33 },
	{ ' ts9', 3, 33 },
	{ ' 9p9', 3, 33 },
	{ ' 7b9', 8, 34 },
	{ ' ov9', 8, 34 },
	{ ' 8s9', 8, 34 },
	{ ' ap9', 8, 34 },
	{ ' 9h9', 8, 34 },
	{ ' cw9', 8, 34 },
	{ ' ss8', 8, 26 },
	{ ' sl8', 8, 26 },
	{ ' sc8', 8, 26 },
	{ ' sb8', 8, 26 },
	{ ' sw8', 8, 26 },
	{ ' bs8', 6, 27 },
	{ ' bh8', 6, 27 },
	{ ' bl8', 6, 27 },
	{ ' bc8', 6, 27 },
	{ ' 8s8', 6, 27 },
	{ ' 8l8', 6, 27 },
	{ ' ws8', 6, 27 },
	{ ' wl8', 6, 27 },
	{ ' xl8', 7, 35 },
	{ ' xm8', 7, 35 },
	{ ' xh8', 7, 35 },
	{ ' xr8', 7, 35 },
	{ ' pax', 0, 37 },
	{ ' pkx', 0, 37 },
	{ ' mlx', 0, 37 },
	{ ' lhx', 0, 37 },
	{ ' mhx', 0, 37 },
	{ ' nrx', 0, 37 },
	{ ' ksx', 0, 37 },
	{ ' iux', 0, 3 },
	{ ' aex', 0, 3 },
	{ ' alx', 0, 3 },
	{ ' utx', 0, 3 },
	{ ' gnx', 0, 3 },
	{ ' lcx', 0, 3 },
	{ ' nhx', 0, 3 },
	{ ' srx', 0, 3 },
	{ ' lpx', 0, 3 },
	{ ' tlx', 0, 3 },
	{ ' dlx', 0, 3 },
	{ ' htx', 0, 3 },
	{ ' lux', 0, 3 },
	{ ' rax', 0, 3 },
	{ ' ptx', 0, 3 },
	{ ' cux', 0, 2 },
	{ ' lmx', 0, 2 },
	{ ' grx', 0, 2 },
	{ ' tix', 0, 2 },
	{ ' wox', 0, 2 },
	{ ' stx', 0, 2 },
	{ ' glx', 0, 16 },
	{ ' gvx', 0, 16 },
	{ ' gmx', 0, 16 },
	{ ' gtx', 0, 16 },
	{ ' ghx', 0, 16 },
	{ ' blx', 0, 15 },
	{ ' bvx', 0, 15 },
	{ ' bmx', 0, 15 },
	{ ' btx', 0, 15 },
	{ ' bhx', 0, 15 },
	{ ' blz', 0, 19 },
	{ ' bvz', 0, 19 },
	{ ' bmz', 0, 19 },
	{ ' btz', 0, 19 },
	{ ' bhz', 0, 19 },
	{ ' 9hx', 0, 37 },
	{ ' hsx', 0, 2 },
	{ ' kpx', 0, 2 },
	{ ' 1fq', 4, 36 },
	{ ' 2fq', 4, 36 },
};

//D2Win.0x6F8BCF28
const D2CompHitClassMappingStrc gHitClassMappings_6F8BCF28[] =
{
	{ ' wob', 1 },
	{ ' sh1', 2 },
	{ ' th1', 3 },
	{ ' fts', 4 },
	{ ' sh2', 5 },
	{ ' th2', 6 },
	{ ' wbx', 7 },
	{ ' sj1', 8 },
	{ ' tj1', 9 },
	{ ' ss1', 10 },
	{ ' ts1', 11 },
	{ ' 1th', 12 },
	{ ' 2th', 13 },
};
//D2Win.0x6F8BCF90
const uint32_t gnHitClassMappings_6F8BCF90 = ARRAY_SIZE(gHitClassMappings_6F8BCF28);
//D2Win.0x6F8BCF94
int32_t dword_6F8BCF94 = 1;
// Converts a hitclass.txt record index to an index in gdwWClassTokens_6F8BC154
//D2Win.0x6F8BCF98
const uint32_t gnHitClassToWClassTokenIndex_6F8BCF98[] = { 1, 6, 4, 2, 8, 5, 3, 7, 9, 10, 11, 12, 13, 14 };

// Converts a direction index to a game direction (out of CELFILE_NUMGAMEDIRECTIONS), the row is selected using the number of directions in the COF file
//D2Win.0x6F8BA370
const uint8_t gnDirectionMapping_6F8BA370[7][CELFILE_NUMGAMEDIRECTIONS] =
{
	{ 0 },
	{ 0 },
	{ 0, 32 },
	{ 0, 16, 32, 48 },
	{ 0, 8, 16, 24, 32, 40, 48, 56 },
	{ 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60 },
	{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62 },
};

//D2Win.0x6F8C14F8
D2CompItemDataTbl gItemDataTbl_6F8C14F8;
//D2Win.0x6F8C1518
uint16_t* gpItemIndices_6F8C1518;
//D2Win.0x6F8C1520
D2CompItemStrc gComponentItems_6F8C1520[MAX_COMPONENT_ITEMS];
// Only the first ITEM_PALETTE_SHIFTS shifts of each palette are loaded
//D2Win.0x6F8C2118
uint8_t gItemPalettes_6F8C2118[9][105][256];
//D2Win.0x6F8FD218
uint8_t byte_6F8FD218[10];
//D2Win.0x6F8FD224
uint8_t byte_6F8FD224[10];
//D2Win.0x6F8FD230
int32_t gnComponentItems_6F8FD230;
//D2Win.0x6F8FD234
uint32_t* gpHitClassTxt_6F8FD234;
//D2Win.0x6F8FD238
void* gpHitClassLinker_6F8FD238;
//D2Win.0x6F8FD23C
void* gpItemsLinker_6F8FD23C;
//D2Win.0x6F8FD240
void* gpItemTypesLinker_6F8FD240;
//D2Win.0x6F8FD244
D2CompItemTypesTxt* gpItemTypesTxt_6F8FD244;
//D2Win.0x6F8FD248
int32_t gnItemTypesTxtRecordCount_6F8FD248;
//D2Win.0x6F8FD250
uint32_t gn2HandedHitClasses_6F8FD250[MAX_COMPONENT_ITEMS];
//D2Win.0x6F8FD650
D2CompositeUnitStrc* gpCompositeUnitList_6F8FD650;
//D2Win.0x6F8FD654
D2CofNodeStrc* gpCofNodeList_6F8FD654;
//D2Win.0x6F8FD658
DWORD gdwNextCursorFrameTick_6F8FD658;
//D2Win.0x6F8FD65C
D2CellFileStrc* ghSquelchCelFile_6F8FD65C;
//D2Win.0x6F8FD660
int32_t gnSquelchCelFileFrameCount_6F8FD660;
//D2Win.0x6F8FD664
int32_t gnSquelchCelFileFrame_6F8FD664;
//D2Win.0x6F8FD668
D2CellFileStrc* ghSelectedCelFile_6F8FD668;
//D2Win.0x6F8FD66C
int32_t gnSelectedCelFileFrameCount_6F8FD66C;
//D2Win.0x6F8FD670
int32_t gnSelectedCelFileFrame_6F8FD670;
//D2Win.0x6F8FD674
BOOL gbComponentTablesInitialized_6F8FD674;
//D2Win.0x6F8FD678
char byte_6F8FD678[4];


//D2Win.0x6F8A32B0
BOOL __stdcall COMP_IsItemTypeEquivalent(int32_t nItemType, int32_t nRequiredItemType);
//D2Win.0x6F8A3570
int __fastcall COMP_ValidateAnimation(D2CompositeUnitStrc* pCompositeUnit);
//D2Win.0x6F8A3680
void __stdcall COMP_LoadItemPalettes();
//D2Win.0x6F8A3DC0
uint32_t __fastcall COMP_GetWeaponClassTokenIndex(const uint8_t* pComponents, uint32_t nClass);
//D2Win.0x6F8A4020
void __fastcall COMP_RemapComponent(int32_t nComponent, uint8_t* pComponent);
//D2Win.0x6F8A4B10
void __fastcall COMP_LoadItemPalette(const char* szPaletteName, int32_t nPaletteIndex);


// Converts a token such as 'hth ' to a string, removing the trailing spaces
static void COMP_TokenToString(uint32_t dwToken, char* szString)
{
	for (int32_t i = 0; i < 3; ++i)
	{
		const char c = (char)(dwToken >> (8 * i));
		szString[i] = (c != ' ') ? c : '\0';
	}
	szString[3] = '\0';
}

// Helper function, inlined in the original game
static D2CofDataStrc* COMP_FindCofData(D2GfxInfoStrc* pGfxInfo, uint32_t nMode, uint32_t dwWClassToken)
{
	for (D2CofInfoStrc* pCofInfo = pGfxInfo->pCofInfo; pCofInfo; pCofInfo = pCofInfo->pNext)
	{
		if (pCofInfo->pCofNode->nMode == nMode && pCofInfo->pCofNode->dwWClassToken == dwWClassToken)
		{
			D2CofDataStrc* pCofData = pCofInfo->pCofNode->pCofData;
			D2_ASSERT(pCofData);
			return pCofData;
		}
	}

	return nullptr;
}

// Helper function, inlined in the original game
static uint8_t* COMP_GetLayerPriorities(D2CofDataStrc* pCofData, int32_t nDirection, int32_t nFrame)
{
	uint8_t* pFirstByte = (uint8_t*)pCofData + sizeof(D2CofDataStrc) + pCofData->nLayers * sizeof(D2CofLayerStrc) + pCofData->nFrames + pCofData->nLayers * (nDirection * pCofData->nFrames + nFrame);
	D2_ASSERT(pFirstByte);
	return pFirstByte;
}

// Helper function, statically linked in the original game (D2Win.0x6F8B256F)
static int32_t COMP_GetDirectionMappingIndex(uint32_t nDirections)
{
	if (!nDirections)
	{
		return 0;
	}

	int32_t nIndex = 1;
	while (!(nDirections & 1))
	{
		nDirections >>= 1;
		++nIndex;
	}

	return nIndex;
}

// Helper function, inlined in the original game
static uint8_t* COMP_GetItemPalette(uint8_t nColor)
{
	if (nColor == 0xFF)
	{
		return nullptr;
	}

	int32_t nPalette = nColor >> 5;
	const int32_t nShift = nColor & 0x1F;
	if (nShift >= ITEM_PALETTE_SHIFTS)
	{
		return nullptr;
	}

	if (nPalette == 0)
	{
		nPalette = 8;
	}
	else if (nPalette >= 9 || (nPalette > 2 && nPalette <= 4))
	{
		return nullptr;
	}

	return gItemPalettes_6F8C2118[nPalette][nShift];
}

//D2Win.0x6F8A1250
D2CofDataStrc* __fastcall COMP_GetCofData(D2GfxInfoStrc* pGfxInfo, uint32_t nClass, uint32_t nMode, int32_t* pUnused1, int32_t* pUnused2, uint32_t dwWClassToken);

//D2Win.0x6F8A1000
void __fastcall COMP_FillGfxData(D2CompositeUnitStrc* pCompositeUnit, D2GfxDataStrc* pGfxData)
{
	pGfxData->nUnitIndex = pCompositeUnit->nClass;
	pGfxData->nMode = pCompositeUnit->nMode;

	const int32_t nComponent = pGfxData->nComponent;
	pGfxData->dwName[1] = gdwComponentTokens_6F8BC100[nComponent];
	pGfxData->dwName[4] = gdwWClassTokens_6F8BC154[pCompositeUnit->nWClassTokenIndex];
	pGfxData->dwName[0] = gdwUnitTokens_6F8BC040[pCompositeUnit->nClass];
	pGfxData->dwName[2] = ' til';
	if (pCompositeUnit->dwComponentTokens[nComponent])
	{
		pGfxData->dwName[2] = pCompositeUnit->dwComponentTokens[nComponent];
	}

	D2_ASSERT(pCompositeUnit->pGfxInfo);

	int32_t nUnused1 = 0;
	int32_t nUnused2 = 0;
	D2CofDataStrc* pCofData = COMP_GetCofData(pCompositeUnit->pGfxInfo, pCompositeUnit->nClass, pCompositeUnit->nMode, &nUnused2, &nUnused1, gdwWClassTokens_6F8BC154[pCompositeUnit->nWClassTokenIndex]);
	D2_ASSERT(pCofData);

	D2CofLayerStrc* pLayer = (D2CofLayerStrc*)&pCofData[1];
	for (int32_t i = 0; i < pCofData->nLayers; ++i)
	{
		D2_ASSERT(nComponent < NUM_COMPONENTS);

		if (pLayer->nComponent == nComponent)
		{
			pGfxData->nUnitType = pGfxData->nUnitIndex >= 7;
			pGfxData->dwName[3] = gdwPlayerModeTokens_6F8BC0A8[pGfxData->nMode];

			if (!pGfxData->dwName[2])
			{
				FOG_DisplayHalt("[sGetCelContextInfo] This should not happen.\n", __FILE__, __LINE__);
				exit(-1);
			}

			uint8_t szWClass[4] = { ' ', ' ', ' ', ' ' };
			if (pLayer->szWeaponClass[0])
			{
				szWClass[0] = pLayer->szWeaponClass[0];
				if (pLayer->szWeaponClass[1])
				{
					szWClass[1] = pLayer->szWeaponClass[1];
					if (pLayer->szWeaponClass[2])
					{
						szWClass[2] = pLayer->szWeaponClass[2];
					}
				}
			}
			memcpy(&pGfxData->dwName[4], szWClass, sizeof(szWClass));
			break;
		}

		++pLayer;
	}

	D2_ASSERT(pGfxData->dwName[1]);
	D2_ASSERT(pGfxData->dwName[0]);
	D2_ASSERT(pGfxData->dwName[4]);

	if (!pGfxData->dwName[2])
	{
		pGfxData->dwName[2] = ' xxx';
	}

	if (!pGfxData->dwName[3])
	{
		pGfxData->dwName[3] = ' xxx';
	}
}

//D2Win.0x6F8A1250
D2CofDataStrc* __fastcall COMP_GetCofData(D2GfxInfoStrc* pGfxInfo, uint32_t nClass, uint32_t nMode, int32_t* pUnused1, int32_t* pUnused2, uint32_t dwWClassToken)
{
	D2_ASSERT(pGfxInfo);

	D2CofInfoStrc* pUnitCofNode = pGfxInfo->pCofInfo;
	while (pUnitCofNode)
	{
		if (pUnitCofNode->pCofNode->nMode == nMode && pUnitCofNode->pCofNode->dwWClassToken == dwWClassToken)
		{
			break;
		}

		pUnitCofNode = pUnitCofNode->pNext;
	}

	if (!pUnitCofNode)
	{
		char szPath[MAX_PATH] = {};

		D2_ASSERT(nClass < COMPOSITEUNITCLASS_NUMCLASSES);
		D2_ASSERT(nMode < gnPlayerModeTokenTblSize_6F8BC0F8);

		char szUnit[4] = {};
		char szMode[4] = {};
		char szWClass[4] = {};
		COMP_TokenToString(dwWClassToken, szWClass);
		COMP_TokenToString(gdwUnitTokens_6F8BC040[nClass], szUnit);
		COMP_TokenToString(gdwPlayerModeTokens_6F8BC0A8[nMode], szMode);

		wsprintfA(szPath, "%s\\%s\\COF\\%s%s%s.COF", (nClass < 7) ? "DATA\\GLOBAL\\CHARS" : "DATA\\GLOBAL\\MONSTERS", szUnit, szUnit, szMode, szWClass);

		HSFILE hFile = nullptr;
		if (!FOG_FOpenFile(szPath, &hFile))
		{
			return nullptr;
		}

		FOG_FCloseFile(hFile);

		if (!szPath[0])
		{
			return nullptr;
		}

		pUnitCofNode = (D2CofInfoStrc*)D2_ALLOC(sizeof(D2CofInfoStrc));
		D2_ASSERT(pUnitCofNode);

		pUnitCofNode->pCofNode = nullptr;
		pUnitCofNode->pNext = nullptr;

		D2CofNodeStrc* pCofNode = gpCofNodeList_6F8FD654;
		while (pCofNode)
		{
			if (pCofNode->nMode == nMode && pCofNode->nClass == nClass && pCofNode->dwWClassToken == dwWClassToken)
			{
				break;
			}

			pCofNode = pCofNode->pNext;
		}

		if (pCofNode)
		{
			++pCofNode->nRefCount;
		}
		else
		{
			pCofNode = (D2CofNodeStrc*)D2_ALLOC(sizeof(D2CofNodeStrc));
			memset(pCofNode, 0x00, sizeof(D2CofNodeStrc));
			++pCofNode->nRefCount;
			pCofNode->nMode = nMode;
			pCofNode->nClass = nClass;
			pCofNode->dwWClassToken = dwWClassToken;
			pCofNode->pNext = gpCofNodeList_6F8FD654;
			pCofNode->pPrev = nullptr;
			if (gpCofNodeList_6F8FD654)
			{
				gpCofNodeList_6F8FD654->pPrev = pCofNode;
			}
			gpCofNodeList_6F8FD654 = pCofNode;

			D2CofDataStrc* pCofData = (D2CofDataStrc*)ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(D2Win_GetArchive(), szPath, (size_t*)&pCofNode->nFileSize);
			D2_ASSERT(pCofData);
			D2_ASSERT(pCofData->nVersion == COF_VERSION);
			pCofNode->pCofData = pCofData;
		}

		D2_ASSERT(pCofNode);

		pUnitCofNode->pCofNode = pCofNode;
		pUnitCofNode->pNext = pGfxInfo->pCofInfo;
		pGfxInfo->pCofInfo = pUnitCofNode;
	}

	D2CofDataStrc* pCofData = pUnitCofNode->pCofNode->pCofData;
	D2_ASSERT(pCofData);
	return pCofData;
}

//D2Win.0x6F8A15E0
void __fastcall COMP_DrawShadow(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	if (!(pCompositeUnit->dwFlags & gdwBitMasks[0]) || !(pCompositeUnit->dwFlags & gdwBitMasks[2]))
	{
		return;
	}

	const int32_t nX = pCompositeUnit->nX - 2;
	const int32_t nY = pCompositeUnit->nY;

	D2_ASSERT(pCompositeUnit->pGfxInfo);

	D2CofDataStrc* pCofData = COMP_FindCofData(pCompositeUnit->pGfxInfo, pCompositeUnit->nMode, gdwWClassTokens_6F8BC154[pCompositeUnit->nWClassTokenIndex]);
	if (!pCofData)
	{
		return;
	}

	const int32_t nFrame = pCompositeUnit->nFrame >> 8;
	const uint8_t* pLayerPriorities = COMP_GetLayerPriorities(pCofData, pCompositeUnit->nDirection, nFrame);

	int32_t nValidLayers = 0;
	for (int32_t i = 0; i < pCofData->nLayers; ++i)
	{
		const int32_t nComponent = pLayerPriorities[i];
		D2_ASSERT(nComponent < NUM_COMPONENTS);

		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = nullptr;
		gfxData.nComponent = nComponent;
		gfxData.nDirection = pCompositeUnit->nDirection;
		gfxData.nFrame = nFrame;
		COMP_FillGfxData(pCompositeUnit, &gfxData);
		gfxData.fFlags |= 2;

		// The original game also computes the highest pCompositeUnit->nX + D2CMP_CelGetOffsetY(gfxData.pCurrentCell) here, but never uses it
		if (D2CMP_10055(&gfxData, 0, 1) && gfxData.pCurrentCell)
		{
			++nValidLayers;
		}
	}

	if (nValidLayers <= 0)
	{
		return;
	}

	for (int32_t i = 0; i < pCofData->nLayers; ++i)
	{
		const int32_t nComponent = pLayerPriorities[i];
		D2_ASSERT(nComponent < NUM_COMPONENTS);

		D2GfxDataStrc gfxData = {};
		gfxData.nComponent = nComponent;
		gfxData.nDirection = pCompositeUnit->nDirection;
		gfxData.pCellFile = nullptr;
		gfxData.nFrame = nFrame;
		COMP_FillGfxData(pCompositeUnit, &gfxData);
		gfxData.fFlags |= 2;
		TEXTURE_CelDrawShadow(&gfxData, nX, nY);
	}
}

//D2Win.0x6F8A1890
BOOL __fastcall COMP_Draw(D2CompositeUnitStrc* pCompositeUnit, uint32_t dwGamma)
{
	D2_ASSERT(pCompositeUnit);

	if (!(pCompositeUnit->dwFlags & gdwBitMasks[0]))
	{
		return FALSE;
	}

	if (pCompositeUnit->dwFlags & gdwBitMasks[10])
	{
		D2_ASSERT(ghSelectedCelFile_6F8FD668);

		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = ghSelectedCelFile_6F8FD668;
		gfxData.nFrame = gnSelectedCelFileFrame_6F8FD670;
		gfxData.nDirection = 0;
		TEXTURE_CelDraw(&gfxData, pCompositeUnit->nX + 5, pCompositeUnit->nY - 5, -1, DRAWMODE_MODULATE, nullptr);
	}

	if (pCompositeUnit->pEmblemCellFile)
	{
		// Only the entries 1 and 2 are initialized in the original game
		uint8_t emblemPalette[256] = {};
		emblemPalette[1] = pCompositeUnit->nEmblemColor1;
		emblemPalette[2] = pCompositeUnit->nEmblemColor2;

		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = pCompositeUnit->pEmblemCellFile;
		gfxData.nDirection = 0;
		gfxData.nFrame = 0;
		gfxData.nMaxDirections = 1;
		TEXTURE_CelDraw(&gfxData, pCompositeUnit->nX - 20, pCompositeUnit->nY - 60, -1, DRAWMODE_NORMAL, emblemPalette);
	}

	D2_ASSERT(pCompositeUnit->pGfxInfo);

	D2CofDataStrc* pCofData = COMP_FindCofData(pCompositeUnit->pGfxInfo, pCompositeUnit->nMode, gdwWClassTokens_6F8BC154[pCompositeUnit->nWClassTokenIndex]);
	if (!pCofData)
	{
		return FALSE;
	}

	const int32_t nFrame = pCompositeUnit->nFrame >> 8;
	const uint8_t* pLayerPriorities = COMP_GetLayerPriorities(pCofData, pCompositeUnit->nDirection, nFrame);

	DrawMode eDrawMode = DRAWMODE_NORMAL;
	if (((pCompositeUnit->dwFlags & gdwBitMasks[5]) && (pCompositeUnit->dwFlags & gdwBitMasks[4])) || (pCompositeUnit->dwFlags & gdwBitMasks[13]))
	{
		eDrawMode = DRAWMODE_TRANS50;
	}

	for (int32_t i = 0; i < pCofData->nLayers; ++i)
	{
		const int32_t nComponent = pLayerPriorities[i];

		D2GfxDataStrc gfxData = {};

		D2_ASSERT(pCompositeUnit->nDirection < CELFILE_NUMGAMEDIRECTIONS);
		const uint8_t nDirection = gnDirectionMapping_6F8BA370[COMP_GetDirectionMappingIndex(pCompositeUnit->nDirections)][pCompositeUnit->nDirection];
		D2_ASSERT(nDirection <= CELFILE_NUMGAMEDIRECTIONS);

		gfxData.nDirection = nDirection;
		gfxData.pCellFile = nullptr;
		gfxData.nFrame = nFrame;
		gfxData.nComponent = nComponent;
		COMP_FillGfxData(pCompositeUnit, &gfxData);
		gfxData.fFlags |= 2;

		TEXTURE_CelDraw(&gfxData, pCompositeUnit->nX, pCompositeUnit->nY, dwGamma, eDrawMode, COMP_GetItemPalette(pCompositeUnit->nComponentColors[nComponent]));
	}

	pCompositeUnit->nFrame += pCompositeUnit->nAnimRate;
	if ((pCompositeUnit->nFrame >> 8) >= pCompositeUnit->nFrames - 1)
	{
		pCompositeUnit->nFrame = 0;
	}

	const DWORD dwTickCount = GetTickCount();
	if (dwTickCount > gdwNextCursorFrameTick_6F8FD658)
	{
		gdwNextCursorFrameTick_6F8FD658 = dwTickCount + 66;

		++gnSquelchCelFileFrame_6F8FD664;
		if (gnSquelchCelFileFrame_6F8FD664 >= gnSquelchCelFileFrameCount_6F8FD660)
		{
			gnSquelchCelFileFrame_6F8FD664 = 0;
		}

		++gnSelectedCelFileFrame_6F8FD670;
		if (gnSelectedCelFileFrame_6F8FD670 >= gnSelectedCelFileFrameCount_6F8FD66C)
		{
			gnSelectedCelFileFrame_6F8FD670 = 0;
		}
	}

	if (pCompositeUnit->dwFlags & gdwBitMasks[9])
	{
		D2_ASSERT(ghSquelchCelFile_6F8FD65C);

		D2GfxDataStrc gfxData = {};
		gfxData.pCellFile = ghSquelchCelFile_6F8FD65C;
		gfxData.nFrame = gnSquelchCelFileFrame_6F8FD664;
		gfxData.nDirection = 0;
		TEXTURE_CelDraw(&gfxData, pCompositeUnit->nX, pCompositeUnit->nY + 10, -1, DRAWMODE_MODULATE, nullptr);
	}

	return TRUE;
}

//D2Win.0x6F8A1D10
BOOL __fastcall COMP_DrawName(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	if (!(pCompositeUnit->dwFlags & gdwBitMasks[1]))
	{
		return FALSE;
	}

	int32_t nY = pCompositeUnit->nY + 6;

	Unicode wszText[256];

	// The original game also sets an unused flag for classes 18 and 20
	int32_t nColor = 0;
	if (pCompositeUnit->nClass == 20 || pCompositeUnit->nClass == 18)
	{
		nColor = 3;
	}
	else if (pCompositeUnit->dwFlags & gdwBitMasks[5])
	{
		nColor = 1;
	}

	if (pCompositeUnit->dwFlags & gdwBitMasks[8])
	{
		nY += 15;
	}

	const uint32_t dwFlags = pCompositeUnit->dwFlags;
	if ((dwFlags & gdwBitMasks[6]) || (dwFlags & gdwBitMasks[7]))
	{
		const int32_t nTitle = 3 * ((dwFlags >> 5) & 1) + 2 * ((dwFlags >> 7) & 1) + ((dwFlags >> 6) & 1);
		const char* szTitle = D2Win_10160_GetPlayerTitle(pCompositeUnit->nClass, nTitle, (dwFlags >> 12) & 1);

		Unicode wszTitle[256];
		Unicode::win2Unicode(wszTitle, szTitle, 255);
		memset(wszText, 0x00, sizeof(wszText));
		Unicode::strcpy(wszText, wszTitle);
		Unicode::strcat(wszText, pCompositeUnit->wszCharName);
	}
	else if (pCompositeUnit->dwProductCode == 'D2DV' || pCompositeUnit->dwProductCode == 'D2ST' || pCompositeUnit->dwProductCode == 'D2XP')
	{
		Unicode::strcpy(wszText, pCompositeUnit->wszCharName);
	}
	else
	{
		Unicode::strcpy(wszText, pCompositeUnit->wszAccountName);
	}

	Unicode wszTemp[256];
	if (Unicode::strlen(pCompositeUnit->wszUnk0x1CC))
	{
		Unicode::toUnicode(wszTemp, " {", 256);
		Unicode::strcat(wszText, wszTemp);
		Unicode::strcat(wszText, pCompositeUnit->wszUnk0x1CC);
		Unicode::toUnicode(wszTemp, "}", 256);
		Unicode::strcat(wszText, wszTemp);
	}

	D2Win_10127_SetFont(D2FONT_REALLYTHELASTSUCKER);

	char szText[512];
	Unicode::unicode2Win(szText, wszText, 300);

	const int32_t nLength = strlen(szText);
	BOOL bTruncated = FALSE;
	int32_t nVisibleLength = 0;
	while (nVisibleLength < nLength)
	{
		if (D2Win_10122(wszText, nVisibleLength + 1) >= 120)
		{
			bTruncated = TRUE;
			break;
		}

		++nVisibleLength;
	}

	szText[nVisibleLength] = '\0';
	if (bTruncated)
	{
		strcat(szText, "...");
	}

	Unicode::win2Unicode(wszText, szText, 299);

	int32_t nWidth = 0;
	int32_t nHeight = 0;
	D2Win_10131_GetTextDimensions(wszText, &nWidth, &nHeight);

	if (nWidth)
	{
		D2Win_10117_DrawText(wszText, pCompositeUnit->nX - nWidth / 2 - 1, nY - 1, 6, 0);
	}

	D2Win_10117_DrawText(wszText, pCompositeUnit->nX - nWidth / 2, nY, nColor, 0);
	return TRUE;
}

//D2Win.0x6F8A2040
void __stdcall COMP_ConstructUnicodeArray(Unicode* pArray, int32_t nStride, int32_t nCount, void(__fastcall* pfConstructor)(Unicode*))
{
	Unicode* pCurrent = pArray;
	for (int32_t i = 0; i < nCount; ++i)
	{
		pfConstructor(pCurrent);
		pCurrent = (Unicode*)((char*)pCurrent + nStride);
	}
}

// Helper function, inlined in the original game
static void COMP_AddExtraDataString(D2CompExtraDataStringStrc* pStrings, int32_t* nStrCount, const Unicode* wszText, int32_t* pMaxWidth, int32_t* pTotalHeight)
{
	D2_ASSERT(*nStrCount < MAXIMUM_NUMBER_OF_EXTRA_DATA_STRINGS);

	D2CompExtraDataStringStrc* pString = &pStrings[*nStrCount];
	Unicode::strcpy(pString->wszText, wszText);
	D2Win_10131_GetTextDimensions(pString->wszText, &pString->nWidth, &pString->nHeight);

	*pMaxWidth = std::max(*pMaxWidth, pString->nWidth + 6);
	*pTotalHeight += pString->nHeight;
	++*nStrCount;
}

//D2Win.0x6F8A2070
BOOL __fastcall COMP_DrawHoverInfo(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	Unicode wszText[256];

	if (!(pCompositeUnit->dwFlags & gdwBitMasks[3]))
	{
		return FALSE;
	}

	RECT rect = {};
	SetRect(&rect, pCompositeUnit->nX - 30, pCompositeUnit->nY - 80, pCompositeUnit->nX + 30, pCompositeUnit->nY + 20);
	if (!CONTROL_MouseInsideRect(&rect))
	{
		return FALSE;
	}

	int32_t nX = pCompositeUnit->nX;
	const int32_t nY = pCompositeUnit->nY - 80;
	int32_t nMaxWidth = 0;
	int32_t nTotalHeight = 0;

	D2CompExtraDataStringStrc strings[MAXIMUM_NUMBER_OF_EXTRA_DATA_STRINGS];

	int32_t nStrCount = 0;
	int32_t nFirstLineColor = 0;
	D2Win_10127_SetFont(D2FONT_FONT16);

	if (pCompositeUnit->dwProductCode == 'D2XP')
	{
		Unicode::toUnicode(wszText, "Expansion", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
	}

	bool bShowCharacterInfo = false;
	switch (pCompositeUnit->nClass)
	{
	case 19:
		Unicode::toUnicode(wszText, "Moderator", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		bShowCharacterInfo = true;
		break;

	case 20:
		Unicode::toUnicode(wszText, "Sysop", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		nFirstLineColor = 3;
		break;

	case 18:
		Unicode::toUnicode(wszText, "Blizzard Rep", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		nFirstLineColor = 3;
		break;

	case 23:
		Unicode::toUnicode(wszText, "Speaker", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		break;

	case 21:
		Unicode::toUnicode(wszText, "Referee", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		break;

	case 22:
		Unicode::toUnicode(wszText, "Chat", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		break;

	case 24:
		Unicode::toUnicode(wszText, "Open Character", 256);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		break;

	default:
	{
		const char* szProduct = nullptr;
		switch (pCompositeUnit->dwProductCode)
		{
		case 'D2DV':
		case 'D2XP':
		case 'D2ST':
			bShowCharacterInfo = true;
			break;

		case 'DSHR':
			szProduct = "Diablo Shareware";
			break;

		case 'DTST':
		case 'DRTL':
			szProduct = "Diablo";
			break;

		case 'SEXP':
			szProduct = "Brood War";
			break;

		case 'SSHR':
			szProduct = "Starcraft Shareware";
			break;

		case 'W2BN':
			szProduct = "Warcraft II";
			break;

		case 'JSTR':
		case 'STAR':
			szProduct = "Starcraft";
			break;

		case 'W3XP':
			szProduct = "Frozen Throne";
			break;

		case 'WAR3':
			szProduct = "Warcraft III";
			break;

		default:
			szProduct = "Unknown";
			break;
		}

		if (szProduct)
		{
			Unicode::toUnicode(wszText, szProduct, 256);
			COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
		}
		break;
	}
	}

	if (bShowCharacterInfo && pCompositeUnit->nLevel > 0)
	{
		memset(wszText, 0x00, sizeof(wszText));
		Unicode::sprintf(256, wszText, D2LANG_GetStringFromTblIndex(5017), pCompositeUnit->nLevel);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);

		if (pCompositeUnit->dwFlags & gdwBitMasks[5])
		{
			COMP_AddExtraDataString(strings, &nStrCount, D2LANG_GetStringFromTblIndex(5016), &nMaxWidth, &nTotalHeight);
		}

		Unicode::toUnicode(wszText, "Realm: ", 256);
		Unicode::strcat(wszText, pCompositeUnit->wszRealmName);
		COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);
	}

	Unicode::toUnicode(wszText, "Account Name: ", 256);
	Unicode::strcat(wszText, pCompositeUnit->wszAccountName);
	COMP_AddExtraDataString(strings, &nStrCount, wszText, &nMaxWidth, &nTotalHeight);

	const int32_t nBoxHeight = nTotalHeight + 6;

	int32_t nLeft = nX - nMaxWidth / 2;
	int32_t nOffsetX = 0;
	if (nLeft < 0)
	{
		nOffsetX = -nLeft;
		nLeft = 0;
	}
	else if (nLeft + nMaxWidth > 800)
	{
		nOffsetX = 800 - nLeft - nMaxWidth;
		nLeft = 800 - nMaxWidth;
	}

	const int32_t nTop = nY - nBoxHeight;
	D2GFX_DrawBox(nLeft, nTop, nLeft + nMaxWidth, nY, 0, DRAWMODE_TRANS75);

	int32_t nTextY = nTop + 3;
	nX += nOffsetX;

	D2_ASSERT(nStrCount <= MAXIMUM_NUMBER_OF_EXTRA_DATA_STRINGS);

	for (int32_t i = 0; i < nStrCount; ++i)
	{
		nTextY += strings[i].nHeight;
		D2Win_10117_DrawText(strings[i].wszText, nX - strings[i].nWidth / 2, nTextY, i == 0 ? nFirstLineColor : 0, 0);
	}

	return TRUE;
}

//D2Win.0x6F8A2A20 (#10142)
void __stdcall D2Win_10142_CompUnitDestroy(D2CompositeUnitStrc* pCompositeUnit, BOOL bFree)
{
	D2_ASSERT(pCompositeUnit);

	D2GfxInfoStrc* pGfxInfo = pCompositeUnit->pGfxInfo;

	D2_ASSERT(pGfxInfo);

	D2CofInfoStrc* pCofInfo = pGfxInfo->pCofInfo;
	while (pCofInfo)
	{
		D2CofNodeStrc* pRemCofNode = pCofInfo->pCofNode;
		D2CofInfoStrc* pNextCofInfo = pCofInfo->pNext;

		D2_ASSERT(pRemCofNode);

		if (gpCofNodeList_6F8FD654)
		{
			--pRemCofNode->nRefCount;
			if (pRemCofNode->nRefCount <= 0)
			{
				D2CofNodeStrc* pPrev = pRemCofNode->pPrev;
				D2CofNodeStrc* pNext = pRemCofNode->pNext;

				D2_FREE(pRemCofNode->pCofData);
				pRemCofNode->pCofData = nullptr;

				if (pPrev)
				{
					if (pNext)
					{
						pPrev->pNext = pNext;
						pNext->pPrev = pPrev;
					}
					else
					{
						pPrev->pNext = nullptr;
					}
				}
				else
				{
					gpCofNodeList_6F8FD654 = pNext;
					if (pNext)
					{
						pNext->pPrev = nullptr;
					}
				}
				D2_FREE(pRemCofNode);
			}
		}

		D2_FREE(pCofInfo);
		pCofInfo = pNextCofInfo;
	}

	pGfxInfo->pCofInfo = nullptr;
	D2_FREE(pGfxInfo);

	if (pCompositeUnit->pEmblemCellFile)
	{
		ARCHIVE_FreeCellFile(pCompositeUnit->pEmblemCellFile);
		pCompositeUnit->pEmblemCellFile = nullptr;
	}

	if (bFree)
	{
		D2CompositeUnitStrc* pPrev = pCompositeUnit->pPrev;
		D2CompositeUnitStrc* pNext = pCompositeUnit->pNext;
		if (pPrev)
		{
			pPrev->pNext = pNext;
			if (pNext)
			{
				pNext->pPrev = pPrev;
			}
		}
		else
		{
			gpCompositeUnitList_6F8FD650 = pNext;
			if (pNext)
			{
				pNext->pPrev = nullptr;
			}
		}
		D2_FREE(pCompositeUnit);
	}
}

//D2Win.0x6F8A2BD0 (#10154)
void __stdcall D2Win_10154(D2CompositeUnitStrc* pCompositeUnit, const Unicode* wszAccountName, const Unicode* wszCharName, const Unicode* wszUnk0x1CC, const Unicode* wszRealmName, int32_t nLevel, uint32_t dwProductCode)
{
	D2_ASSERT(pCompositeUnit);

	Unicode::strcpy(pCompositeUnit->wszAccountName, wszAccountName);
	Unicode::strcpy(pCompositeUnit->wszCharName, wszCharName);
	Unicode::strcpy(pCompositeUnit->wszUnk0x1CC, wszUnk0x1CC);
	Unicode::strcpy(pCompositeUnit->wszRealmName, wszRealmName);
	pCompositeUnit->nLevel = nLevel;
	pCompositeUnit->dwProductCode = dwProductCode;
}

//D2Win.0x6F8A2C50 (#10143)
BOOL __fastcall D2Win_10143(D2CompositeUnitStrc* pCompositeUnit, uint32_t nMode)
{
	D2_ASSERT(pCompositeUnit);

	for (D2CofInfoStrc* pCofInfo = pCompositeUnit->pGfxInfo->pCofInfo; pCofInfo; pCofInfo = pCofInfo->pNext)
	{
		if (pCofInfo->pCofNode->nMode == nMode)
		{
			D2CofDataStrc* pCofData = pCofInfo->pCofNode->pCofData;

			D2_ASSERT(pCofData);

			pCompositeUnit->nMode = nMode;
			pCompositeUnit->nFrame = 0;
			pCompositeUnit->nFrames = pCofData->nFrames;
			pCompositeUnit->nAnimRate = pCofData->nAnimRate;
			pCompositeUnit->nDirections = pCofData->nDirections;

			return TRUE;
		}
	}

	return FALSE;
}

//D2Win.0x6F8A2CE0
void* __stdcall COMP_LoadTxtFile(HD2ARCHIVE hArchive, const char* szName, D2BinFieldStrc* pBinField, int* pRecordCount, int nRecordSize)
{
	char szFilename[260] = {};

	if (dword_6F8BCF94)
	{
		wsprintfA(szFilename, "%s\\%s%s", "DATA\\GLOBAL\\EXCEL", szName, ".bin");
	}
	else if (_strcmpi(szName, "leveldefs"))
	{
		wsprintfA(szFilename, "%s\\%s%s", "DATA\\GLOBAL\\EXCEL", szName, ".txt");
	}
	else
	{
		wsprintfA(szFilename, "%s\\%s%s", "DATA\\GLOBAL\\EXCEL", "levels", ".txt");
	}

	unsigned int nFileSize = 0;
	void* pFileData = ARCHIVE_ALLOC_BUFFER_AND_READ_FILE_TO_IT(hArchive, szFilename, &nFileSize);

	D2_ASSERT(pFileData);

	void* pBinData = nullptr;
	int nRecordCount = 0;
	if (dword_6F8BCF94)
	{
		nRecordCount = *(int*)pFileData;
		pBinData = (char*)pFileData + 4;
	}
	else
	{
		D2BinFileStrc* pBinFile = FOG_CreateBinFile(pFileData, nFileSize);
		nRecordCount = FOG_GetRecordCountFromBinFile(pBinFile);
		pBinData = FOG_AllocPool(0, nRecordSize * nRecordCount, __FILE__, __LINE__, 0);
		memset(pBinData, 0x00, nRecordSize * nRecordCount);

		FOG_10207(pBinFile, pBinField, pBinData, nRecordCount, nRecordSize);
		FOG_FreeBinFile(pBinFile);
	}

	if (pRecordCount)
	{
		*pRecordCount = nRecordCount;
	}

	return pBinData;
}

//D2Win.0x6F8A2E70
void __fastcall COMP_LoadItemTables(HD2ARCHIVE hArchive)
{
	D2BinFieldStrc itemsFields[] =
	{
		{ "version", TXTFIELD_WORD, 0, offsetof(D2CompItemsTxt, wVersion), nullptr },
		{ "type", TXTFIELD_CODETOWORD, 0, offsetof(D2CompItemsTxt, wType), &gpItemTypesLinker_6F8FD240 },
		{ "code", TXTFIELD_RAW, 0, offsetof(D2CompItemsTxt, dwCode), nullptr },
		{ "alternategfx", TXTFIELD_RAW, 0, offsetof(D2CompItemsTxt, dwAlternateGfx), nullptr },
		{ "spawnable", TXTFIELD_BYTE, 0, offsetof(D2CompItemsTxt, nSpawnable), nullptr },
		{ "level", TXTFIELD_BYTE, 0, offsetof(D2CompItemsTxt, nLevel), nullptr },
		{ "component", TXTFIELD_BYTE, 0, offsetof(D2CompItemsTxt, nComponent), nullptr },
		{ "wclass", TXTFIELD_RAW, 0, offsetof(D2CompItemsTxt, dwWeapClass), nullptr },
		{ "2handedwclass", TXTFIELD_RAW, 0, offsetof(D2CompItemsTxt, dwWeapClass2Hand), nullptr },
		{ "1or2handed", TXTFIELD_UNKNOWN2, 0, offsetof(D2CompItemsTxt, n1or2Handed), nullptr },
		{ "Transform", TXTFIELD_BYTE, 0, offsetof(D2CompItemsTxt, nTransform), nullptr },
		{ "end", TXTFIELD_NONE, 0, 0, nullptr },
	};

	D2CompItemsTxt* pWeapons = (D2CompItemsTxt*)COMP_LoadTxtFile(hArchive, "weapons", itemsFields, &gItemDataTbl_6F8C14F8.nWeaponsTxtRecordCount, sizeof(D2CompItemsTxt));
	D2CompItemsTxt* pArmor = (D2CompItemsTxt*)COMP_LoadTxtFile(hArchive, "armor", itemsFields, &gItemDataTbl_6F8C14F8.nArmorTxtRecordCount, sizeof(D2CompItemsTxt));
	D2CompItemsTxt* pMisc = (D2CompItemsTxt*)COMP_LoadTxtFile(hArchive, "misc", itemsFields, &gItemDataTbl_6F8C14F8.nMiscTxtRecordCount, sizeof(D2CompItemsTxt));

	gItemDataTbl_6F8C14F8.nItemsTxtRecordCount = gItemDataTbl_6F8C14F8.nWeaponsTxtRecordCount + gItemDataTbl_6F8C14F8.nArmorTxtRecordCount + gItemDataTbl_6F8C14F8.nMiscTxtRecordCount;
	gItemDataTbl_6F8C14F8.pItemsTxt = (D2CompItemsTxt*)D2_ALLOC_POOL(nullptr, sizeof(D2CompItemsTxt) * gItemDataTbl_6F8C14F8.nItemsTxtRecordCount);

	gItemDataTbl_6F8C14F8.pWeapons = gItemDataTbl_6F8C14F8.pItemsTxt;
	memcpy(gItemDataTbl_6F8C14F8.pWeapons, pWeapons, sizeof(D2CompItemsTxt) * gItemDataTbl_6F8C14F8.nWeaponsTxtRecordCount);

	gItemDataTbl_6F8C14F8.pArmor = &gItemDataTbl_6F8C14F8.pWeapons[gItemDataTbl_6F8C14F8.nWeaponsTxtRecordCount];
	memcpy(gItemDataTbl_6F8C14F8.pArmor, pArmor, sizeof(D2CompItemsTxt) * gItemDataTbl_6F8C14F8.nArmorTxtRecordCount);

	gItemDataTbl_6F8C14F8.pMisc = &gItemDataTbl_6F8C14F8.pArmor[gItemDataTbl_6F8C14F8.nArmorTxtRecordCount];
	memcpy(gItemDataTbl_6F8C14F8.pMisc, pMisc, sizeof(D2CompItemsTxt) * gItemDataTbl_6F8C14F8.nMiscTxtRecordCount);

	// Frees the buffers of the .bin files (the record count is stored before the records)
	D2_FREE_POOL(nullptr, (char*)pWeapons - 4);
	D2_FREE_POOL(nullptr, (char*)pArmor - 4);
	D2_FREE_POOL(nullptr, (char*)pMisc - 4);

	gpItemIndices_6F8C1518 = (uint16_t*)D2_ALLOC_POOL(nullptr, sizeof(uint16_t) * gItemDataTbl_6F8C14F8.nItemsTxtRecordCount);
	memset(gpItemIndices_6F8C1518, 0x00, sizeof(uint16_t) * gItemDataTbl_6F8C14F8.nItemsTxtRecordCount);

	int32_t nIndices = 0;
	for (int32_t i = 0; i < gItemDataTbl_6F8C14F8.nItemsTxtRecordCount; ++i)
	{
		if (!gItemDataTbl_6F8C14F8.pItemsTxt[i].wVersion)
		{
			gpItemIndices_6F8C1518[nIndices] = i;
			++nIndices;
		}
	}

	gpItemsLinker_6F8FD23C = FOG_AllocLinker(__FILE__, __LINE__);
	for (int32_t i = 0; i < gItemDataTbl_6F8C14F8.nItemsTxtRecordCount; ++i)
	{
		FOG_10215(gpItemsLinker_6F8FD23C, gItemDataTbl_6F8C14F8.pItemsTxt[i].dwCode);
	}
}

//D2Win.0x6F8A32B0
BOOL __stdcall COMP_IsItemTypeEquivalent(int32_t nItemType, int32_t nRequiredItemType)
{
	if (!nRequiredItemType)
	{
		return TRUE;
	}

	if (!nItemType)
	{
		return FALSE;
	}

	int32_t itemTypeStack[64] = {};
	itemTypeStack[0] = nItemType;

	int32_t nStackIndex = 1;
	while (nStackIndex)
	{
		--nStackIndex;
		const int32_t nCurrentItemType = itemTypeStack[nStackIndex];

		if (nRequiredItemType == nCurrentItemType)
		{
			return TRUE;
		}

		D2CompItemTypesTxt* pItemTypesTxtRecord = &gpItemTypesTxt_6F8FD244[nCurrentItemType];
		if (pItemTypesTxtRecord->nEquiv1)
		{
			itemTypeStack[nStackIndex] = pItemTypesTxtRecord->nEquiv1;
			++nStackIndex;

			if (pItemTypesTxtRecord->nEquiv2)
			{
				itemTypeStack[nStackIndex] = pItemTypesTxtRecord->nEquiv2;
				++nStackIndex;
			}
		}

		D2_ASSERT(nStackIndex < 64);
	}

	return FALSE;
}

//D2Win.0x6F8A3360 (#10159)
void __stdcall D2Win_10159(D2CellFileStrc* pSquelchCelFile, D2CellFileStrc* pSelectedCelFile)
{
	ghSquelchCelFile_6F8FD65C = pSquelchCelFile;
	gnSquelchCelFileFrameCount_6F8FD660 = D2CMP_CelFileGetCelsPerDirection(pSquelchCelFile);
	ghSelectedCelFile_6F8FD668 = pSelectedCelFile;
	gnSelectedCelFileFrameCount_6F8FD66C = D2CMP_CelFileGetCelsPerDirection(pSelectedCelFile);
}

// Helper function, inlined in the original game
static D2GfxInfoStrc* COMP_CreateGfxInfo()
{
	D2GfxInfoStrc* pGfxInfo = (D2GfxInfoStrc*)D2_ALLOC(sizeof(D2GfxInfoStrc));
	D2_ASSERT(pGfxInfo);
	pGfxInfo->pCofInfo = nullptr;
	return pGfxInfo;
}

// Helper function, inlined in the original game
static void COMP_InitializeComponents(D2CompositeUnitStrc* pCompositeUnit, uint32_t nMode, uint8_t* pComponents, const uint8_t* pComponentColors, int32_t nMaxComponentItem)
{
	pCompositeUnit->nMode = nMode;
	pCompositeUnit->dwFlags |= gdwBitMasks[0];
	pCompositeUnit->dwFlags |= gdwBitMasks[1];
	pCompositeUnit->dwFlags |= gdwBitMasks[2];

	for (int32_t i = 0; i < NUM_COMPONENTS; ++i)
	{
		pCompositeUnit->nComponentItemTypes[i] = 1;

		if (pComponents[i] && pComponents[i] < nMaxComponentItem && pComponents[i] != 0xFF)
		{
			COMP_RemapComponent(i, &pComponents[i]);
			pCompositeUnit->dwComponentTokens[i] = gComponentItems_6F8C1520[pComponents[i]].dwCode;
			pCompositeUnit->nComponentItemTypes[i] = gComponentItems_6F8C1520[pComponents[i]].nItemType;
		}
		else
		{
			pCompositeUnit->dwComponentTokens[i] = 0;
		}
	}

	for (int32_t i = 0; i < NUM_COMPONENTS; ++i)
	{
		pCompositeUnit->nComponentColors[i] = pComponentColors[i];
		if (pComponentColors[i] != 0xFF)
		{
			pCompositeUnit->nComponentColors[i] = pComponentColors[i] - 1;
		}
	}
}

//D2Win.0x6F8A3390 (#10144)
D2CompositeUnitStrc* __stdcall D2Win_10144(uint32_t nClass, uint32_t nMode, uint8_t* pComponents, const uint8_t* pComponentColors)
{
	D2CompositeUnitStrc* pNewUnit = (D2CompositeUnitStrc*)D2_ALLOC(sizeof(D2CompositeUnitStrc));
	D2_ASSERT(pNewUnit);
	memset(pNewUnit, 0x00, sizeof(D2CompositeUnitStrc));

	pNewUnit->pGfxInfo = COMP_CreateGfxInfo();

	COMP_LoadItemPalettes();

	pNewUnit->nClass = nClass;
	if (nClass < 7)
	{
		pNewUnit->nWClassTokenIndex = COMP_GetWeaponClassTokenIndex(pComponents, nClass);
		if (!pNewUnit->nWClassTokenIndex)
		{
			// The original game leaks pNewUnit here
			return nullptr;
		}
	}
	else
	{
		pNewUnit->nWClassTokenIndex = 1;
	}

	COMP_InitializeComponents(pNewUnit, nMode, pComponents, pComponentColors, gnComponentItems_6F8FD230);

	if (COMP_ValidateAnimation(pNewUnit) && !D2Win_10143(pNewUnit, nMode))
	{
		// The original game leaks pNewUnit here
		return nullptr;
	}

	pNewUnit->pPrev = nullptr;
	pNewUnit->pNext = gpCompositeUnitList_6F8FD650;
	if (gpCompositeUnitList_6F8FD650)
	{
		gpCompositeUnitList_6F8FD650->pPrev = pNewUnit;
	}
	gpCompositeUnitList_6F8FD650 = pNewUnit;

	return pNewUnit;
}

//D2Win.0x6F8A3570
int __fastcall COMP_ValidateAnimation(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	if (pCompositeUnit->nClass >= (uint32_t)gnUnitTokenTblSize_6F8BC0A4 || pCompositeUnit->nMode >= gnPlayerModeTokenTblSize_6F8BC0F8 || pCompositeUnit->nWClassTokenIndex >= gnWClassTokenTblSize_6F8BC190)
	{
		pCompositeUnit->nClass = 7;
		pCompositeUnit->nMode = 5;
		pCompositeUnit->nWClassTokenIndex = 1;
	}

	D2GfxInfoStrc* pGfxInfo = pCompositeUnit->pGfxInfo;

	D2_ASSERT(pGfxInfo);

	int32_t nUnused = 0;
	if (COMP_GetCofData(pGfxInfo, pCompositeUnit->nClass, pCompositeUnit->nMode, &nUnused, &nUnused, gdwWClassTokens_6F8BC154[pCompositeUnit->nWClassTokenIndex]))
	{
		return 1;
	}

	pCompositeUnit->nMode = 5;
	pCompositeUnit->nClass = 7;
	pCompositeUnit->nWClassTokenIndex = 1;

	D2CofDataStrc* pCurrCofData = COMP_GetCofData(pGfxInfo, 7, 5, &nUnused, &nUnused, gdwWClassTokens_6F8BC154[1]);

	D2_ASSERT(pCurrCofData);
	return 1;
}

// Helper function, inlined in the original game
static int32_t COMP_GetHitClassIndex(uint32_t dwWClassToken)
{
	for (uint32_t i = 0; i < gnHitClassMappings_6F8BCF90; ++i)
	{
		if (dwWClassToken == gHitClassMappings_6F8BCF28[i].dwToken)
		{
			return gHitClassMappings_6F8BCF28[i].nIndex;
		}
	}

	return 0;
}

//D2Win.0x6F8A3680
void __stdcall COMP_LoadItemPalettes()
{
	if (gbComponentTablesInitialized_6F8FD674)
	{
		return;
	}

	memset(gComponentItems_6F8C1520, 0x00, sizeof(gComponentItems_6F8C1520));
	gbComponentTablesInitialized_6F8FD674 = TRUE;

	D2BinFieldStrc itemTypesFields[] =
	{
		{ "code", TXTFIELD_ASCIITOCODE, 0, offsetof(D2CompItemTypesTxt, szCode), &gpItemTypesLinker_6F8FD240 },
		{ "equiv1", TXTFIELD_CODETOWORD, 0, offsetof(D2CompItemTypesTxt, nEquiv1), &gpItemTypesLinker_6F8FD240 },
		{ "equiv2", TXTFIELD_CODETOWORD, 0, offsetof(D2CompItemTypesTxt, nEquiv2), &gpItemTypesLinker_6F8FD240 },
		{ "repair", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nRepair), nullptr },
		{ "body", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nBody), nullptr },
		{ "shoots", TXTFIELD_CODETOWORD, 0, offsetof(D2CompItemTypesTxt, wShoots), &gpItemTypesLinker_6F8FD240 },
		{ "quiver", TXTFIELD_CODETOWORD, 0, offsetof(D2CompItemTypesTxt, wQuiver), &gpItemTypesLinker_6F8FD240 },
		{ "throwable", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nThrowable), nullptr },
		{ "reload", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nReload), nullptr },
		{ "reequip", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nReEquip), nullptr },
		{ "autostack", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nAutoStack), nullptr },
		{ "magic", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nMagic), nullptr },
		{ "normal", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nNormal), nullptr },
		{ "charm", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nCharm), nullptr },
		{ "gem", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nGem), nullptr },
		{ "beltable", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nBeltable), nullptr },
		{ "costformula", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nCostFormula), nullptr },
		{ "varinvgfx", TXTFIELD_BYTE, 0, offsetof(D2CompItemTypesTxt, nVarInvGfx), nullptr },
		{ "invgfx1", TXTFIELD_ASCII, 31, offsetof(D2CompItemTypesTxt, szInvGfx[0]), nullptr },
		{ "invgfx2", TXTFIELD_ASCII, 31, offsetof(D2CompItemTypesTxt, szInvGfx[1]), nullptr },
		{ "invgfx3", TXTFIELD_ASCII, 31, offsetof(D2CompItemTypesTxt, szInvGfx[2]), nullptr },
		{ "invgfx4", TXTFIELD_ASCII, 31, offsetof(D2CompItemTypesTxt, szInvGfx[3]), nullptr },
		{ "invgfx5", TXTFIELD_ASCII, 31, offsetof(D2CompItemTypesTxt, szInvGfx[4]), nullptr },
		{ "end", TXTFIELD_NONE, 0, 0, nullptr },
	};

	gpItemTypesLinker_6F8FD240 = FOG_AllocLinker(__FILE__, __LINE__);
	gpItemTypesTxt_6F8FD244 = (D2CompItemTypesTxt*)COMP_LoadTxtFile(D2Win_GetArchive(), "itemtypes", itemTypesFields, &gnItemTypesTxtRecordCount_6F8FD248, sizeof(D2CompItemTypesTxt));

	D2BinFieldStrc hitClassFields[] =
	{
		{ "code", TXTFIELD_ASCIITOCODE, 0, 0, &gpHitClassLinker_6F8FD238 },
		{ "end", TXTFIELD_NONE, 0, 0, nullptr },
	};

	gpHitClassLinker_6F8FD238 = FOG_AllocLinker(__FILE__, __LINE__);
	gpHitClassTxt_6F8FD234 = (uint32_t*)COMP_LoadTxtFile(D2Win_GetArchive(), "hitclass", hitClassFields, nullptr, sizeof(uint32_t));

	COMP_LoadItemTables(D2Win_GetArchive());

	gComponentItems_6F8C1520[1].dwCode = ' til';
	gComponentItems_6F8C1520[1].nHitClass = gnHitClassToWClassTokenIndex_6F8BCF98[0];
	gComponentItems_6F8C1520[1].nItemType = 3;
	gComponentItems_6F8C1520[2].dwCode = ' dem';
	gComponentItems_6F8C1520[2].nHitClass = gnHitClassToWClassTokenIndex_6F8BCF98[0];
	gComponentItems_6F8C1520[2].nItemType = 3;
	gComponentItems_6F8C1520[3].dwCode = ' yvh';
	gComponentItems_6F8C1520[3].nHitClass = gnHitClassToWClassTokenIndex_6F8BCF98[0];
	gComponentItems_6F8C1520[3].nItemType = 3;

	int32_t nNextIndex = 4;
	for (int32_t i = 0; i < gItemDataTbl_6F8C14F8.nItemsTxtRecordCount; ++i)
	{
		D2CompItemsTxt* pItemsTxtRecord = &gItemDataTbl_6F8C14F8.pItemsTxt[i];
		const uint32_t dwCode = pItemsTxtRecord->dwAlternateGfx ? pItemsTxtRecord->dwAlternateGfx : pItemsTxtRecord->dwCode;
		const int32_t nItemType = pItemsTxtRecord->wType;

		BOOL bIsComponent = FALSE;
		if (COMP_IsItemTypeEquivalent(nItemType, 45) || COMP_IsItemTypeEquivalent(nItemType, 3) || COMP_IsItemTypeEquivalent(nItemType, 51) || COMP_IsItemTypeEquivalent(nItemType, 37))
		{
			bIsComponent = !COMP_IsItemTypeEquivalent(nItemType, 75);
		}

		bool bAlreadyAdded = false;
		for (int32_t j = 0; j < nNextIndex; ++j)
		{
			if (gComponentItems_6F8C1520[j].dwCode == dwCode)
			{
				bAlreadyAdded = true;
				break;
			}
		}

		if (bAlreadyAdded || !bIsComponent)
		{
			continue;
		}

		int32_t nIndex = nNextIndex;
		while (nIndex < MAX_COMPONENT_ITEMS)
		{
			const int32_t nStaticItemType = gStaticComponentItems_6F8BC1D8[nIndex].nItemType;
			if (!(COMP_IsItemTypeEquivalent(nStaticItemType, 45) && COMP_IsItemTypeEquivalent(nItemType, 45))
				&& !(COMP_IsItemTypeEquivalent(nStaticItemType, 50) && COMP_IsItemTypeEquivalent(nItemType, 50))
				&& !gComponentItems_6F8C1520[nIndex].dwCode)
			{
				break;
			}

			++nIndex;
		}

		if (nIndex >= MAX_COMPONENT_ITEMS)
		{
			nIndex = nNextIndex;
		}

		gComponentItems_6F8C1520[nIndex].dwCode = dwCode;
		gComponentItems_6F8C1520[nIndex].nItemType = nItemType;
		gComponentItems_6F8C1520[nIndex].nHitClass = gnHitClassToWClassTokenIndex_6F8BCF98[COMP_GetHitClassIndex(pItemsTxtRecord->dwWeapClass)];
		gn2HandedHitClasses_6F8FD250[nIndex] = gnHitClassToWClassTokenIndex_6F8BCF98[COMP_GetHitClassIndex(pItemsTxtRecord->dwWeapClass2Hand)];

		if (nNextIndex == nIndex)
		{
			++nNextIndex;
		}
	}

	gnComponentItems_6F8FD230 = MAX_COMPONENT_ITEMS;
}

// Helper function, inlined in the original game
static uint32_t COMP_GetHandHitClass(const uint8_t* pComponents, int32_t nComponent, uint32_t nClass, BOOL bBothHands, BOOL bCheckOtherHands)
{
	const uint8_t nItem = pComponents[nComponent];
	if (nItem == 0xFF)
	{
		return 0;
	}

	uint32_t nHitClass = 0;
	if (bBothHands)
	{
		nHitClass = gn2HandedHitClasses_6F8FD250[nItem];
	}
	else
	{
		nHitClass = gComponentItems_6F8C1520[nItem].nHitClass;
		if (bCheckOtherHands && pComponents[6] == 0xFF && pComponents[7] == 0xFF && gn2HandedHitClasses_6F8FD250[nItem] != nHitClass)
		{
			nHitClass = gn2HandedHitClasses_6F8FD250[nItem];
		}
	}

	const int32_t nItemType = gComponentItems_6F8C1520[nItem].nItemType;
	if (((nHitClass == 13 || nHitClass == 14) && nClass != 6) || COMP_IsItemTypeEquivalent(nItemType, 50))
	{
		nHitClass = gStaticComponentItems_6F8BC1D8[nItem].nHitClass;
	}

	return nHitClass;
}

//D2Win.0x6F8A3DC0
uint32_t __fastcall COMP_GetWeaponClassTokenIndex(const uint8_t* pComponents, uint32_t nClass)
{
	// Components 5 and 6 are the right and left hands
	const BOOL bBothHands = pComponents[5] != 0xFF && pComponents[6] != 0xFF;

	uint32_t nRightHitClass = COMP_GetHandHitClass(pComponents, 5, nClass, bBothHands, TRUE);
	uint32_t nLeftHitClass = COMP_GetHandHitClass(pComponents, 6, nClass, bBothHands, FALSE);

	// Only the Assassin can use claws
	if ((nRightHitClass == 13 || nRightHitClass == 14) && nClass != 6)
	{
		nRightHitClass = 0;
	}

	if ((nLeftHitClass == 13 || nLeftHitClass == 14) && nClass != 6)
	{
		nLeftHitClass = 0;
	}

	if (!nRightHitClass)
	{
		return nLeftHitClass ? nLeftHitClass : 1;
	}

	if (nRightHitClass == nLeftHitClass && (nRightHitClass == 6 || nRightHitClass == 7))
	{
		return nRightHitClass;
	}

	if (nRightHitClass == 8 || !nLeftHitClass)
	{
		return nRightHitClass;
	}

	if (nRightHitClass == 4 && nLeftHitClass == 4)
	{
		return 11;
	}

	if (nRightHitClass == 4 && nLeftHitClass == 2)
	{
		return 9;
	}

	if (nRightHitClass == 2 && nLeftHitClass == 4)
	{
		return 12;
	}

	if (nRightHitClass == 2 && nLeftHitClass == 2)
	{
		return 10;
	}

	if ((nRightHitClass == 2 || nRightHitClass == 4 || nRightHitClass == 5) && (nLeftHitClass == 2 || nLeftHitClass == 4 || nLeftHitClass == 5))
	{
		return 11;
	}

	if ((nRightHitClass == 13 || nRightHitClass == 14) && nLeftHitClass == nRightHitClass)
	{
		return 13;
	}

	if (nRightHitClass == 1 && nLeftHitClass == 1)
	{
		return 1;
	}

	return 0;
}

// Helper function, inlined in the original game
static void COMP_RemapComponentItem(uint8_t* pComponent)
{
	for (int32_t i = 0; i < gnComponentItems_6F8FD230; ++i)
	{
		if (gComponentItems_6F8C1520[i].dwCode == gStaticComponentItems_6F8BC1D8[*pComponent].dwCode)
		{
			*pComponent = i;
			return;
		}
	}

	*pComponent = *pComponent % 3 + 1;
}

//D2Win.0x6F8A4020
void __fastcall COMP_RemapComponent(int32_t nComponent, uint8_t* pComponent)
{
	if (nComponent == 1 || nComponent == 2 || nComponent == 3 || nComponent == 4)
	{
		if (*pComponent > 3)
		{
			constexpr int32_t nItemTypes[] = { 3, 16, 15, 51 };
			for (int32_t nItemType : nItemTypes)
			{
				if (COMP_IsItemTypeEquivalent(gStaticComponentItems_6F8BC1D8[*pComponent].nItemType, nItemType))
				{
					COMP_RemapComponentItem(pComponent);
				}
			}
		}
	}
	else if (nComponent == 0)
	{
		if (!COMP_IsItemTypeEquivalent(gComponentItems_6F8C1520[*pComponent].nItemType, 37))
		{
			if (COMP_IsItemTypeEquivalent(gStaticComponentItems_6F8BC1D8[*pComponent].nItemType, 37))
			{
				for (int32_t i = 0; i < gnComponentItems_6F8FD230; ++i)
				{
					if (gComponentItems_6F8C1520[i].dwCode == gStaticComponentItems_6F8BC1D8[*pComponent].dwCode)
					{
						*pComponent = i;
						return;
					}
				}
			}

			*pComponent = 1;
		}
	}
}

//D2Win.0x6F8A4260 (#10145)
void __stdcall D2Win_10145(D2CompositeUnitStrc* pCompositeUnit, uint32_t nClass, uint32_t nMode, uint8_t* pComponents, const uint8_t* pComponentColors)
{
	D2_ASSERT(pCompositeUnit);

	pCompositeUnit->pGfxInfo = COMP_CreateGfxInfo();

	pCompositeUnit->nClass = nClass;
	if (nClass < 7)
	{
		pCompositeUnit->nWClassTokenIndex = COMP_GetWeaponClassTokenIndex(pComponents, nClass);
		if (!pCompositeUnit->nWClassTokenIndex)
		{
			return;
		}
	}
	else
	{
		pCompositeUnit->nWClassTokenIndex = 1;
	}

	COMP_InitializeComponents(pCompositeUnit, nMode, pComponents, pComponentColors, 0xFF);

	if (COMP_ValidateAnimation(pCompositeUnit))
	{
		D2Win_10143(pCompositeUnit, nMode);
	}
}

//D2Win.0x6F8A43C0 (#10146)
void __stdcall D2Win_10146()
{
	D2CompositeUnitStrc* pCompositeUnit = gpCompositeUnitList_6F8FD650;
	while (pCompositeUnit)
	{
		D2CompositeUnitStrc* pNext = pCompositeUnit->pNext;
		D2Win_10142_CompUnitDestroy(pCompositeUnit, FALSE);
		D2_FREE(pCompositeUnit);
		pCompositeUnit = pNext;
	}
	gpCompositeUnitList_6F8FD650 = nullptr;
}

//D2Win.0x6F8A4400 (#10147)
D2CompositeUnitStrc* __stdcall D2Win_10147()
{
	return gpCompositeUnitList_6F8FD650;
}

//D2Win.0x6F8A4410 (#10148)
D2CompositeUnitStrc* __stdcall D2Win_10148(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	return pCompositeUnit->pNext;
}

//D2Win.0x6F8A4440 (#10149)
void __stdcall D2Win_10149(D2CompositeUnitStrc* pCompositeUnit, uint8_t nDirection)
{
	D2_ASSERT(pCompositeUnit);

	pCompositeUnit->nDirection = std::min(nDirection, pCompositeUnit->nDirections);
}

//D2Win.0x6F8A4490 (#10150)
uint8_t __stdcall D2Win_10150(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	return pCompositeUnit->nDirections;
}

//D2Win.0x6F8A44C0 (#10169)
int32_t __stdcall D2Win_10169(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	return pCompositeUnit->nFrames;
}

//D2Win.0x6F8A44F0 (#10151)
void __stdcall D2Win_10151(D2CompositeUnitStrc* pCompositeUnit, int32_t nFrame)
{
	D2_ASSERT(pCompositeUnit);

	const int32_t nMax = pCompositeUnit->nFrames << 8;
	pCompositeUnit->nFrame = D2Clamp(nFrame, 0, nMax);
}

//D2Win.0x6F8A4540 (#10152)
void __stdcall D2Win_10152(D2CompositeUnitStrc* pCompositeUnit, int32_t nX)
{
	D2_ASSERT(pCompositeUnit);

	pCompositeUnit->nX = nX;
}

//D2Win.0x6F8A4570 (#10153)
void __stdcall D2Win_10153(D2CompositeUnitStrc* pCompositeUnit, int32_t nY)
{
	D2_ASSERT(pCompositeUnit);

	pCompositeUnit->nY = nY;
}

//D2Win.0x6F8A45A0 (#10155)
uint32_t __stdcall D2Win_10155(D2CompositeUnitStrc* pCompositeUnit)
{
	D2_ASSERT(pCompositeUnit);

	return pCompositeUnit->dwFlags;
}

//D2Win.0x6F8A45D0 (#10156)
void __stdcall D2Win_10156(D2CompositeUnitStrc* pCompositeUnit, uint32_t dwFlags)
{
	D2_ASSERT(pCompositeUnit);

	pCompositeUnit->dwFlags = dwFlags;
}

//D2Win.0x6F8A4600 (#10158)
void __stdcall D2Win_10158(D2CompositeUnitStrc* pCompositeUnit, uint8_t nEmblem, uint8_t nEmblemColor1, uint8_t nEmblemColor2)
{
	D2_ASSERT(pCompositeUnit);

	if (nEmblem < 1u || nEmblem > 32u)
	{
		return;
	}

	char szFile[512] = {};

	wsprintfA(szFile, "%s\\ui\\emblems\\icon%02dc", "DATA\\GLOBAL", nEmblem - 1);
	pCompositeUnit->pEmblemCellFile = ARCHIVE_LoadCellFile(szFile, 0);

	if (nEmblemColor1 >= 1u && nEmblemColor1 <= 10u)
	{
		pCompositeUnit->nEmblemColor1 = byte_6F8FD224[nEmblemColor1 - 1];
	}
	else
	{
		pCompositeUnit->nEmblemColor1 = 0;
	}

	if (nEmblemColor2 >= 1u && nEmblemColor2 <= 10u)
	{
		pCompositeUnit->nEmblemColor2 = byte_6F8FD218[nEmblemColor2 - 1];
	}
	else
	{
		pCompositeUnit->nEmblemColor2 = 0;
	}
}

//D2Win.0x6F8A46E0 (#10157)
void __stdcall D2Win_10157()
{
	// The original game inlines the 6 first calls
	COMP_LoadItemPalette("grey", 1);
	COMP_LoadItemPalette("grey2", 2);
	COMP_LoadItemPalette("gold", 3);
	COMP_LoadItemPalette("brown", 4);
	COMP_LoadItemPalette("greybrown", 5);
	COMP_LoadItemPalette("invgrey", 6);
	COMP_LoadItemPalette("invgrey2", 7);
	COMP_LoadItemPalette("invgreybrown", 8);
}

//D2Win.0x6F8A4B10
void __fastcall COMP_LoadItemPalette(const char* szPaletteName, int32_t nPaletteIndex)
{
	char szPath[260];
	strcpy(szPath, "Data\\Global\\Items\\Palette\\");
	strcat(szPath, szPaletteName);
	strcat(szPath, ".dat");

	HSFILE hFile = nullptr;
	if (!ARCHIVE_OpenFile(nullptr, szPath, &hFile, TRUE))
	{
		FOG_DisplayWarning("0", __FILE__, __LINE__);
		memset(gItemPalettes_6F8C2118[nPaletteIndex], 0x00, ITEM_PALETTE_SHIFTS * 256);
		return;
	}

	ARCHIVE_ReadFileToBuffer(nullptr, hFile, gItemPalettes_6F8C2118[nPaletteIndex], ITEM_PALETTE_SHIFTS * 256);
	ARCHIVE_CloseFile(nullptr, hFile);
}

//D2Win.0x6F8A4C10
void __stdcall COMP_InitEmblemColors()
{
	constexpr uint8_t byte_6F8BC194[] =
	{
		0xBC, 0x00, 0x00,
		0xE0, 0x70, 0x20,
		0xFC, 0xD4, 0x5C,
		0xFC, 0xE4, 0xA4,
		0xF4, 0xF4, 0xF4,
		0xB8, 0xB8, 0xB8,
		0x74, 0x74, 0x74,
		0x4C, 0x6C, 0xAC,
		0x58, 0x90, 0x4C,
		0xB2, 0x7C, 0x58,
	};

	for (int32_t i = 0; i < std::size(byte_6F8FD224); ++i)
	{
		byte_6F8FD224[i] = D2Win_10034_MixRGB(byte_6F8BC194[3 * i], byte_6F8BC194[3 * i + 1], byte_6F8BC194[3 * i + 2]);
	}

	constexpr uint8_t byte_6F8BC1B4[] =
	{
		0x5C, 0x00, 0x00,
		0x90, 0x00, 0x00,
		0x30, 0x1C, 0x10,
		0x5C, 0x24, 0x08,
		0x04, 0x24, 0x10,
		0x24, 0x5C, 0x24,
		0x00, 0x00, 0x58,
		0x28, 0x28, 0x78,
		0x40, 0x40, 0x40,
		0x00, 0x00, 0x00,
	};

	for (int32_t i = 0; i < std::size(byte_6F8FD218); ++i)
	{
		byte_6F8FD218[i] = D2Win_10034_MixRGB(byte_6F8BC1B4[3 * i], byte_6F8BC1B4[3 * i + 1], byte_6F8BC1B4[3 * i + 2]);
	}
}

//D2Win.0x6F8A4C70 (#10161)
const char* __stdcall D2Win_10161(int32_t nClass, int32_t nProgression, BOOL bHardcore, BOOL bExpansion)
{
	int32_t nTitle = 0;

	if (bExpansion)
	{
		if (nProgression >= 5)
		{
			if (nProgression < 10)
			{
				nTitle = 1;
			}
			else if (nProgression < 15)
			{
				nTitle = 2;
			}
			else
			{
				nTitle = 3;
			}
		}
	}
	else
	{
		if (nProgression >= 4)
		{
			if (nProgression < 8)
			{
				nTitle = 1;
			}
			else if (nProgression < 12)
			{
				nTitle = 2;
			}
			else
			{
				nTitle = 3;
			}
		}
	}

	if (bHardcore && nTitle)
	{
		nTitle += 3;
	}

	return D2Win_10160_GetPlayerTitle(nClass, nTitle, bExpansion);
}

//D2Win.0x6F8A4CE0 (#10160)
const char* __stdcall D2Win_10160_GetPlayerTitle(int32_t nClass, int32_t nTitle, BOOL bExpansion)
{
	// Amazon, Sorceress, Assassin and class 9 use the female titles
	const bool bFemale = nClass == 0 || nClass == 1 || nClass == 6 || nClass == 9;

	if (bExpansion)
	{
		switch (nTitle)
		{
		case 1:
			return "Slayer ";
		case 2:
			return "Champion ";
		case 3:
			return bFemale ? "Matriarch " : "Patriarch ";
		case 4:
			return "Destroyer ";
		case 5:
			return "Conqueror ";
		case 6:
			return "Guardian ";
		default:
			break;
		}
	}
	else if (bFemale)
	{
		switch (nTitle)
		{
		case 1:
			return "Dame ";
		case 2:
			return "Lady ";
		case 3:
			return "Baroness ";
		case 4:
			return "Countess ";
		case 5:
			return "Duchess ";
		case 6:
			return "Queen ";
		default:
			break;
		}
	}
	else
	{
		switch (nTitle)
		{
		case 1:
			return "Sir ";
		case 2:
			return "Lord ";
		case 3:
			return "Baron ";
		case 4:
			return "Count ";
		case 5:
			return "Duke ";
		case 6:
			return "King ";
		default:
			break;
		}
	}

	return byte_6F8FD678;
}

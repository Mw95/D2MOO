#include <Path/PathUtil.h>
#include <Units/Units.h>
#include <Fog.h>

// Helper function
static void __fastcall AdvanceTowardsTarget(D2DynamicPathStrc* pDynamicPath, D2PathPointStrc& PathPoint)
{
	D2_ASSERT(pDynamicPath);
	D2_ASSERT(pDynamicPath->pTargetUnit);

	uint8_t nDirection = PATH_GetDirection(pDynamicPath->pTargetUnit->pDynamicPath);
	int nSpeed = pDynamicPath->dwSpeed;
	uint16_t v4 = (uint16_t)nSpeed << 8;
	const float nDistance = nSpeed;
	const uint16_t nAngleRad512 = (8 * nDirection - v4) & 0x1FF;
	PathPoint.X += (int64_t)(FOG_10083_Cos_LUT(nAngleRad512) * nDistance);
	PathPoint.Y += (int64_t)(FOG_10084_Sin_LUT(nAngleRad512) * nDistance);
}

//1.10f: D2Common.0x6FDAB890
//1.13c: D2Common.0x6FD8E080
void __fastcall PATHUtil_AdvanceTowardsTarget_6FDAB890(D2DynamicPathStrc* pDynamicPath)
{
	AdvanceTowardsTarget(pDynamicPath, pDynamicPath->tTargetCoord);
}

//1.10f: D2Common.0x6FDAB940
//1.13c: D2Common.0x6FD8E310
void __fastcall sub_6FDAB940(D2PathPointStrc* pOutPathPoint, D2DynamicPathStrc* pDynamicPath)
{
	D2_ASSERT(pDynamicPath);
	D2_ASSERT(pDynamicPath->pTargetUnit);

	D2CoordStrc tTargetCoords = {};
	UNITS_GetCoords(pDynamicPath->pTargetUnit, &tTargetCoords);

	pOutPathPoint->X = tTargetCoords.nX;
	pOutPathPoint->Y = tTargetCoords.nY;

	if (pDynamicPath->dwSpeed)
	{
		AdvanceTowardsTarget(pDynamicPath, *pOutPathPoint);
	}
}

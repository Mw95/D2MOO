#include <Fog.h>

#include <cmath>

// 1.10f: 0x6FF51C00 (#10198)
// Fills a gamma correction table, blending a power curve with a linear ramp.
// nGammaValue is a percentage (100 = no correction), flPercentLinear the percentage of the linear ramp in [0, 100].
void __fastcall FOG_ComputeGammaTable(int nGammaValue, void* pGammaTable, double flPercentLinear, int nGammaTableEntrySize, int nEntries, int nMaxValue)
{
	D2_ASSERT((nGammaTableEntrySize == 1) || (nGammaTableEntrySize == 2) || (nGammaTableEntrySize == 4));
	D2_ASSERT(nGammaValue >= 0);
	D2_ASSERT((flPercentLinear >= 0.0) && (flPercentLinear <= 100.0));

	const double flPercentPower = 100.0 - flPercentLinear;
	const double flLinearScale = 0.01 * nGammaValue;
	const double flExponent = 100.0 / nGammaValue;
	const double flLastIndex = nEntries - 1.0;
	const double flMaxValue = nMaxValue;
	if (0.0 > flLastIndex)
	{
		return;
	}

	const double flInvLastIndex = 1.0 / flLastIndex;
	uint8_t* pEntries8 = (uint8_t*)pGammaTable;
	uint16_t* pEntries16 = (uint16_t*)pGammaTable;
	uint32_t* pEntries32 = (uint32_t*)pGammaTable;
	for (double flIndex = 0.0; flIndex <= flLastIndex; flIndex += 1.0)
	{
		const double flRatio = flInvLastIndex * flIndex;
		double flLinearValue = flRatio * flMaxValue * flLinearScale;
		if (!(flLinearValue < flMaxValue))
		{
			flLinearValue = flMaxValue;
		}

		const double flPowerValue = pow(flRatio, flExponent) * flMaxValue * flPercentPower;
		const int32_t nValue = (int32_t)((flPowerValue + flLinearValue * flPercentLinear) * 0.01);
		switch (nGammaTableEntrySize)
		{
		case 1:
			*pEntries8++ = (uint8_t)nValue;
			break;
		case 2:
			*pEntries16++ = (uint16_t)nValue;
			break;
		case 4:
			*pEntries32++ = (uint32_t)nValue;
			break;
		default:
			break;
		}
	}
}

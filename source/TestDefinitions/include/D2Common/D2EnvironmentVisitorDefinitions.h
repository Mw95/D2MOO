#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2Environment.h>


BEGIN_VISIT(D2EnvironmentCycleStrc)
	FIELD(nTicksBegin)
	FIELD(nPeriodOfDay)
	FIELD(nRed)
	FIELD(nGreen)
	FIELD(nBlue)
	FIELD(nIntensity)
END_VISIT()

BEGIN_VISIT(D2DrlgEnvironmentStrc)
	FIELD(nCycleIndex)
	FIELD(nPeriodOfDay)
	FIELD(nTicks)
	INTEGRAL_FIELD(nIntensity, 1) // Since this can be calculated by floating point operations, we allow an 'Off by 1' rounding error
	FIELD(dwInitTick)
	FIELD(unk0x14)
	INTEGRAL_FIELD(nRed, 1) // Since this can be calculated by floating point operations, we allow an 'Off by 1' rounding error
	INTEGRAL_FIELD(nGreen, 1) // Since this can be calculated by floating point operations, we allow an 'Off by 1' rounding error
	INTEGRAL_FIELD(nBlue, 1) // Since this can be calculated by floating point operations, we allow an 'Off by 1' rounding error
	FIELD(pad0x1B)
	FIELD(fCos)
	FIELD(fLast)
	FIELD(fSin)
	FIELD(nTimeRate)
	FIELD(nTimeRateIndex)
	FIELD(bEclipse)
	FIELD(nPrev)
END_VISIT()

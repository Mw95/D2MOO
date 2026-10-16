#include "SCompInternal.h"

#include <cstring>

// IMA ADPCM like compression of 16 bit PCM samples

#define SCOMP_ADPCM_INITIAL_STEP_INDEX  0x2C
#define SCOMP_ADPCM_MAX_STEP_INDEX      0x58
#define SCOMP_ADPCM_MAX_CHANNELS        2

#define SCOMP_ADPCM_REPEAT_SAMPLE       0x80 // Repeat the previous sample, decrease the step index
#define SCOMP_ADPCM_INCREASE_STEP       0x81 // Increase the step index
#define SCOMP_ADPCM_DECREASE_STEP       0x82 // Decrease the step index

// Storm.0x6FFE2090
static const int32_t sgnNextStepIndex[32] =
{
	-1, 0, -1, 4, -1, 2, -1, 6, -1, 1, -1, 5, -1, 3, -1, 7,
	-1, 1, -1, 5, -1, 3, -1, 7, -1, 2, -1, 4, -1, 6, -1, 8,
};

// Storm.0x6FFE2110
static const int32_t sgnStepSize[89] =
{
	7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31,
	34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143,
	157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658,
	724, 796, 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024,
	3327, 3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
	15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767,
};

static inline int32_t SCompADPCMClampStepIndex(int32_t nStepIndex)
{
	if (nStepIndex < 0)
	{
		return 0;
	}
	if (nStepIndex > SCOMP_ADPCM_MAX_STEP_INDEX)
	{
		return SCOMP_ADPCM_MAX_STEP_INDEX;
	}
	return nStepIndex;
}

uint32_t SCompADPCMCompress(void* pOut, uint32_t nOutSize, const void* pIn, uint32_t nInSize, uint32_t nChannels, uint32_t nLevel)
{
	uint8_t* pOutput = (uint8_t*)pOut;
	const int16_t* pInput = (const int16_t*)pIn;
	if (nOutSize < 2)
	{
		return 2;
	}

	// Header: 0, shift
	const uint8_t nShift = (uint8_t)(nLevel - 1);
	pOutput[0] = 0;
	pOutput[1] = nShift;
	uint8_t* pCurrent = pOutput + 2;
	if ((int32_t)(nChannels * 2 + (pCurrent - pOutput)) > (int32_t)nOutSize)
	{
		return (uint32_t)(nChannels * 2 + (pCurrent - pOutput));
	}

	// Initial samples
	int32_t nStepIndex[SCOMP_ADPCM_MAX_CHANNELS] = { SCOMP_ADPCM_INITIAL_STEP_INDEX, SCOMP_ADPCM_INITIAL_STEP_INDEX };
	int32_t nPredicted[SCOMP_ADPCM_MAX_CHANNELS];
	for (uint32_t i = 0; i < nChannels; ++i)
	{
		const int16_t nSample = *pInput++;
		memcpy(pCurrent, &nSample, sizeof(nSample));
		nPredicted[i] = nSample;
		pCurrent += sizeof(nSample);
	}

	// Number of step increase markers that can be written
	int32_t nIncreaseMarkersLeft = (int32_t)(pOutput + (int32_t)nInSize / 2 - pCurrent);
	if (nIncreaseMarkersLeft < 0)
	{
		nIncreaseMarkersLeft = 0;
	}

	uint32_t nChannel = nChannels - 1;
	const uint32_t nSamples = nInSize >> 1;
	for (uint32_t nSample = nChannels; nSample < nSamples; ++nSample)
	{
		if ((int32_t)(pCurrent - pOutput + 2) > (int32_t)nOutSize)
		{
			return (uint32_t)(pCurrent - pOutput + 2);
		}

		if (nChannels == 2)
		{
			nChannel = !nChannel;
		}

		const int32_t nInputSample = *pInput++;
		int32_t nDifference = nInputSample - nPredicted[nChannel];
		const uint8_t nSign = nInputSample < nPredicted[nChannel] ? 0x40 : 0;
		if (nDifference < 0)
		{
			nDifference = -nDifference;
		}

		int32_t nStepSize = sgnStepSize[nStepIndex[nChannel]];
		if ((uint32_t)nDifference < ((uint32_t)nStepSize >> nLevel))
		{
			if (nStepIndex[nChannel])
			{
				--nStepIndex[nChannel];
			}
			*pCurrent++ = SCOMP_ADPCM_REPEAT_SAMPLE;
			continue;
		}

		while ((uint32_t)nDifference > (uint32_t)nStepSize * 2)
		{
			if (nStepIndex[nChannel] >= SCOMP_ADPCM_MAX_STEP_INDEX || !nIncreaseMarkersLeft)
			{
				break;
			}

			nStepIndex[nChannel] += 8;
			if (nStepIndex[nChannel] > SCOMP_ADPCM_MAX_STEP_INDEX)
			{
				nStepIndex[nChannel] = SCOMP_ADPCM_MAX_STEP_INDEX;
			}
			nStepSize = sgnStepSize[nStepIndex[nChannel]];
			*pCurrent++ = SCOMP_ADPCM_INCREASE_STEP;
			--nIncreaseMarkersLeft;
		}

		const uint32_t nBaseDifference = (uint32_t)nStepSize >> nShift;
		uint32_t nMaxBit = 1u << (nLevel - 2);
		if (nMaxBit > 0x20)
		{
			nMaxBit = 0x20;
		}

		uint32_t nEncoded = 0;
		uint32_t nTotalStep = 0;
		uint32_t nStep = (uint32_t)nStepSize;
		for (uint32_t nBit = 1; ; nBit *= 2)
		{
			if (nTotalStep + nStep <= (uint32_t)nDifference)
			{
				nEncoded |= nBit;
				nTotalStep += nStep;
			}
			if (nBit == nMaxBit)
			{
				break;
			}
			nStep >>= 1;
		}

		const int32_t nDelta = (int32_t)(nTotalStep + nBaseDifference);
		int32_t nNewSample;
		if (nSign)
		{
			nNewSample = nPredicted[nChannel] - nDelta;
			if (nNewSample < -0x8000)
			{
				nNewSample = -0x8000;
			}
		}
		else
		{
			nNewSample = nPredicted[nChannel] + nDelta;
			if (nNewSample > 0x7FFF)
			{
				nNewSample = 0x7FFF;
			}
		}
		nPredicted[nChannel] = nNewSample;

		*pCurrent++ = (uint8_t)(nEncoded | nSign);
		nStepIndex[nChannel] = SCompADPCMClampStepIndex(nStepIndex[nChannel] + sgnNextStepIndex[nEncoded & 0x1F]);
	}

	return (uint32_t)(pCurrent - pOutput);
}

uint32_t SCompADPCMDecompress(void* pOut, uint32_t nOutSize, const void* pIn, uint32_t nInSize, uint32_t nChannels)
{
	uint8_t* pOutput = (uint8_t*)pOut;
	const uint8_t* pInput = (const uint8_t*)pIn;
	const uint8_t* pInputEnd = pInput + nInSize;
	const uint8_t nShift = pInput[1];
	const uint8_t* pCurrent = pInput + 2;

	int32_t nStepIndex[SCOMP_ADPCM_MAX_CHANNELS] = { SCOMP_ADPCM_INITIAL_STEP_INDEX, SCOMP_ADPCM_INITIAL_STEP_INDEX };
	int32_t nPredicted[SCOMP_ADPCM_MAX_CHANNELS];
	uint8_t* pOutCurrent = pOutput;
	for (uint32_t i = 0; i < nChannels; ++i)
	{
		int16_t nSample;
		memcpy(&nSample, pCurrent, sizeof(nSample));
		pCurrent += sizeof(nSample);
		nPredicted[i] = nSample;
		if (nOutSize < 2)
		{
			return (uint32_t)(pOutCurrent - pOutput);
		}
		memcpy(pOutCurrent, &nSample, sizeof(nSample));
		pOutCurrent += sizeof(nSample);
		nOutSize -= 2;
	}

	uint32_t nChannel = nChannels - 1;
	while (pCurrent < pInputEnd)
	{
		if (nChannels == 2)
		{
			nChannel = !nChannel;
		}

		const uint8_t nEncoded = *pCurrent++;
		if (nEncoded & 0x80)
		{
			switch (nEncoded & 0x7F)
			{
			case 0: // SCOMP_ADPCM_REPEAT_SAMPLE
			{
				if (nStepIndex[nChannel])
				{
					--nStepIndex[nChannel];
				}
				if (nOutSize < 2)
				{
					return (uint32_t)(pOutCurrent - pOutput);
				}
				const int16_t nSample = (int16_t)nPredicted[nChannel];
				memcpy(pOutCurrent, &nSample, sizeof(nSample));
				pOutCurrent += sizeof(nSample);
				nOutSize -= 2;
				break;
			}
			case 1: // SCOMP_ADPCM_INCREASE_STEP
				nStepIndex[nChannel] += 8;
				if (nStepIndex[nChannel] > SCOMP_ADPCM_MAX_STEP_INDEX)
				{
					nStepIndex[nChannel] = SCOMP_ADPCM_MAX_STEP_INDEX;
				}
				// The marker does not use a sample of the channel
				if (nChannels == 2)
				{
					nChannel = !nChannel;
				}
				break;
			case 2: // SCOMP_ADPCM_DECREASE_STEP
				nStepIndex[nChannel] -= 8;
				if (nStepIndex[nChannel] < 0)
				{
					nStepIndex[nChannel] = 0;
				}
				if (nChannels == 2)
				{
					nChannel = !nChannel;
				}
				break;
			default:
				break;
			}
			continue;
		}

		const uint32_t nStepSize = (uint32_t)sgnStepSize[nStepIndex[nChannel]];
		uint32_t nDelta = nStepSize >> nShift;
		if (nEncoded & 0x01)
		{
			nDelta += nStepSize;
		}
		if (nEncoded & 0x02)
		{
			nDelta += nStepSize >> 1;
		}
		if (nEncoded & 0x04)
		{
			nDelta += nStepSize >> 2;
		}
		if (nEncoded & 0x08)
		{
			nDelta += nStepSize >> 3;
		}
		if (nEncoded & 0x10)
		{
			nDelta += nStepSize >> 4;
		}
		if (nEncoded & 0x20)
		{
			nDelta += nStepSize >> 5;
		}

		int32_t nNewSample;
		if (nEncoded & 0x40)
		{
			nNewSample = nPredicted[nChannel] - (int32_t)nDelta;
			if (nNewSample <= -0x8000)
			{
				nNewSample = -0x8000;
			}
		}
		else
		{
			nNewSample = nPredicted[nChannel] + (int32_t)nDelta;
			if (nNewSample >= 0x7FFF)
			{
				nNewSample = 0x7FFF;
			}
		}
		nPredicted[nChannel] = nNewSample;

		if (nOutSize < 2)
		{
			return (uint32_t)(pOutCurrent - pOutput);
		}
		const int16_t nSample = (int16_t)nNewSample;
		memcpy(pOutCurrent, &nSample, sizeof(nSample));
		pOutCurrent += sizeof(nSample);
		nOutSize -= 2;

		nStepIndex[nChannel] = SCompADPCMClampStepIndex(nStepIndex[nChannel] + sgnNextStepIndex[nEncoded & 0x1F]);
	}

	return (uint32_t)(pOutCurrent - pOutput);
}

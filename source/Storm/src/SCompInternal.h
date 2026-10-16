#pragma once

#include <cstdint>

// Compression algorithms used by SCompCompress / SCompDecompress

#define SCOMP_HUFFMAN_TYPES 9

// Storm.0x6FFBBC00
uint32_t SCompHuffmanCompress(void* pOut, uint32_t nOutSize, const void* pIn, uint32_t nInSize, uint32_t nType);
// Storm.0x6FFBB7E0
uint32_t SCompHuffmanDecompress(void* pOut, uint32_t nOutSize, const void* pIn);

// Storm.0x6FFBC260
uint32_t SCompADPCMCompress(void* pOut, uint32_t nOutSize, const void* pIn, uint32_t nInSize, uint32_t nChannels, uint32_t nLevel);
// Storm.0x6FFBC560
uint32_t SCompADPCMDecompress(void* pOut, uint32_t nOutSize, const void* pIn, uint32_t nInSize, uint32_t nChannels);

#pragma once

// PKWARE Data Compression Library for Win32, Version 1.11, statically linked into Storm.dll.
// Copyright 1989-1995 PKWARE Inc. Patent No. 5,051,745
//
// This is a reimplementation of the "implode" and "explode" functions of the library,
// producing the same output as the original code.

#include <cstdint>

#define PKWARE_CMP_BINARY            0
#define PKWARE_CMP_ASCII             1

#define PKWARE_CMP_NO_ERROR          0
#define PKWARE_CMP_INVALID_DICTSIZE  1
#define PKWARE_CMP_INVALID_MODE      2
#define PKWARE_CMP_BAD_DATA          3
#define PKWARE_CMP_ABORT             4

// Size of the work buffers that must be provided to implode / explode
#define PKWARE_IMPLODE_BUFFER_SIZE   36312
#define PKWARE_EXPLODE_BUFFER_SIZE   12596

typedef uint32_t (__cdecl* PKWAREREADBUF)(char* buf, uint32_t* size, void* param);
typedef void (__cdecl* PKWAREWRITEBUF)(char* buf, uint32_t* size, void* param);

// Storm.0x6FFDF450
uint32_t __cdecl PKWareImplode(PKWAREREADBUF pfnReadBuf, PKWAREWRITEBUF pfnWriteBuf, void* pWorkBuffer, void* pParam, uint32_t* pType, uint32_t* pDictSize);

// Storm.0x6FFDFEF0
uint32_t __cdecl PKWareExplode(PKWAREREADBUF pfnReadBuf, PKWAREWRITEBUF pfnWriteBuf, void* pWorkBuffer, void* pParam);

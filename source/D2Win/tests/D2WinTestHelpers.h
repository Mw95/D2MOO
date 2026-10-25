#pragma once


#include <cstdint>
#include <cstring>
#include <cwchar>

#include <D2Unicode.h>
#include <Fog.h>

#include <D2WinTestDefinitions.h>
#include <Fixtures/D2Win/D2WinFixtures.h>


#define D2_USTR(widestr) reinterpret_cast<const Unicode*>(widestr)


// The D2Win structs are allocated with Fog.dll, so that the functions freeing them can be tested
template<typename T>
T* d2win_calloc()
{
	T* pObject = static_cast<T*>(D2_ALLOC(sizeof(T)));
	std::memset(pObject, 0, sizeof(T));
	return pObject;
}

inline Unicode* d2win_alloc_string(const wchar_t* wszText)
{
	const size_t nSize = (std::wcslen(wszText) + 1) * sizeof(Unicode);
	Unicode* pString = static_cast<Unicode*>(D2_ALLOC(nSize));
	std::memcpy(pString, wszText, nSize);
	return pString;
}

inline bool unicode_equals(const Unicode* wszText, const wchar_t* wszExpected)
{
	if (wszText == nullptr || wszExpected == nullptr)
	{
		return static_cast<const void*>(wszText) == static_cast<const void*>(wszExpected);
	}

	return std::wcscmp(reinterpret_cast<const wchar_t*>(wszText), wszExpected) == 0;
}

inline bool unicode_equals(const Unicode* wszText, const Unicode* wszExpected)
{
	return unicode_equals(wszText, reinterpret_cast<const wchar_t*>(wszExpected));
}

// Fills the common control header fields like the creation functions do (enabled and visible)
inline void d2win_init_control(D2WinControlStrc& control, int32_t nType, int32_t nX = 100, int32_t nY = 200, int32_t nWidth = 120, int32_t nHeight = 40)
{
	control.nType = nType;
	control.dwFlags = 1 | 4;
	control.nImageX = nX;
	control.nImageY = nY;
	control.nWidth = nWidth;
	control.nHeight = nHeight;
}

#pragma once


#include <cstdint>


template<typename T>
struct TypeId
{
	static_assert(sizeof(T) == 0, "TypeId<T> has not been registered.");
};

template<typename T>
inline constexpr uint64_t TypeId_v = TypeId<T>::value;

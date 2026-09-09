#pragma once


#include "Deserializer.h"
#include "TypeId.h"
#include "TypeInfo.h"
#include "TypeRegistry.h"
#include "Serializer.h"
#include "VisitorTraits.h"


template<typename T>
struct TypeRegistration
{
	static void* Allocate()
	{
		return new T;
	}

	static void VisitWithSerializer(Serializer& serializer, void* object)
	{
		VisitorTraits<T>::Visit(serializer, *static_cast<T*>(object));
	}

	static void VisitWithDeserializer(Deserializer& deserializer, void* object)
	{
		VisitorTraits<T>::Visit(deserializer, *static_cast<T*>(object));
	}

	static void Register()
	{
		const auto typeInfo = TypeInfo{
			TypeId_v<T>,
			Allocate,
			VisitWithSerializer,
			VisitWithDeserializer
		};

		TypeRegistry::Instance().Register(typeInfo);
	}

	inline static bool Registered = (Register(), true);
};


//#define REGISTER_TYPE(TYPE)													\
//	template<>																\
//	struct TypeId<TYPE>														\
//	{																		\
//		static constexpr uint64_t value = fnv1a(#TYPE);						\
//	};																		\
//	const auto _##TYPE##_Registered = TypeRegistration<TYPE>::Registered;

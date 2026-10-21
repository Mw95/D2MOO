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
	// Value-initialized, so members which are not visited (e.g. OMIT) are zeroed instead of left indeterminate
	static void* Allocate()
	{
		return new T();
	}

	static void Destroy(void* object)
	{
		delete static_cast<T*>(object);
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
			Destroy,
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

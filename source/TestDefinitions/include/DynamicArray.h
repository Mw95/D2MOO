#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TestComparator.h>
#include <TypeId.h>
#include <TypeRegistration.h>


template<typename T>
struct DynamicArray
{
	T* data;
	int count;
};


//template <>
//struct TestComparator<DynamicArray<uint32_t>> {
//	static bool compare(DynamicArray<uint32_t>& a, DynamicArray<uint32_t>& b, const char* context_title, std::string& diff_description)
//	{
//		DiffContext context(context_title);
//		DiffVisitor visitor(a, context);
//		visitor.CompareWith(b);
//		diff_description = context.DifferenceDescription();
//		return context.differences.empty();
//	}
//};
//template<>
//struct TypeId<DynamicArray<uint32_t>>
//{
//	static constexpr uint64_t value = fnv1a("DynamicArray<uint32_t>");
//};
//const auto _DynamicArray_uint32_t__Registered = TypeRegistration<DynamicArray<uint32_t>>::Registered;
//template<>
//struct VisitorTraits<DynamicArray<uint32_t>>
//{
//	using Self = DynamicArray<uint32_t>;
//	template<class Visitor>
//	static void Visit(Visitor& visitor, DynamicArray<uint32_t>& object)
//	{
//		visitor.DynamicArray<&Self::data, &Self::count>(object, "data");
//		visitor.Field<&Self::count>(object, "count");
//	}
//};

#define DYNAMIC_ARRAY_TYPE(TYPE)																										\
	template <>																															\
	struct TestComparator<DynamicArray<TYPE>> {																							\
		static bool compare(DynamicArray<TYPE>& a, DynamicArray<TYPE>& b, const char* context_title, std::string& diff_description)		\
		{																																\
			DiffContext context(context_title);																							\
			DiffVisitor visitor(a, context);																							\
			visitor.CompareWith(b);																										\
			diff_description = context.DifferenceDescription();																			\
			return context.differences.empty();																							\
		}																																\
	};																																	\
	template<>																															\
	struct TypeId<DynamicArray<TYPE>>																									\
	{																																	\
		static constexpr uint64_t value = fnv1a("DynamicArray<"#TYPE">");																\
	};																																	\
	const auto _DynamicArray_##TYPE##_Registered = TypeRegistration<DynamicArray<TYPE>>::Registered;									\
	template<>																															\
	struct VisitorTraits<DynamicArray<TYPE>>																							\
	{																																	\
		using Self = DynamicArray<TYPE>;																								\
		template<class Visitor>																											\
		static void Visit(Visitor& visitor, DynamicArray<TYPE>& object)																	\
		{																																\
			visitor.DynamicArray<&Self::data, &Self::count>(object, "data");															\
			visitor.Field<&Self::count>(object, "count");																				\
		}																																\
	};
add_library(VisitorFramework STATIC 
  include/BinaryReader.h
  include/BinaryWriter.h
  include/Deserializer.h
  include/DifferenceDescriptor.h
  include/DifferenceType.h
  include/DiffContext.h
  include/DiffVisitor.h
  include/FieldVisitor.h
  include/Macros.h
  include/ObjectRegistry.h
  include/PointerFixups.h
  include/Serializer.h
  include/TestComparator.h
  include/TypeId.h
  include/TypeInfo.h
  include/TypeRegistration.h
  include/TypeRegistry.h
  include/VisitorTraits.h

  src/BinaryReader.cpp
  src/BinaryWriter.cpp
  src/DifferenceDescriptor.cpp
  src/ObjectRegistry.cpp
  src/PointerFixups.cpp
  src/TypeRegistry.cpp
)
target_include_directories(VisitorFramework PUBLIC include)
target_compile_features(VisitorFramework PRIVATE cxx_std_17)


add_subdirectory(tests)

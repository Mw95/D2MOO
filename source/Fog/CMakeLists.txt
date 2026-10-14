
D2MOO_prepare_targets(Fog)

target_link_libraries(${FogImplName} PUBLIC D2CommonDefinitions Storm)
target_link_libraries(${FogImplName} PRIVATE ws2_32)

target_sources(${FogImplName}
  PRIVATE
	src/Fog.cpp
	
	# Official file names
	src/AsyncData.cpp
	src/BitManip/BitManip.cpp
	src/BitManip/StringPack.cpp
	src/D2QSQueue.cpp
	src/D2QSSocket.cpp
	src/DataArrays.cpp
	src/ErrorManager.cpp
	src/Excel/Excel.cpp
	src/Exceptions.cpp
	src/Gamma.cpp
	src/IFF.cpp
	src/LogManager.cpp
	src/Mem/Mem.cpp
	src/QServer/QServer.cpp
	src/QServer/QServer98.cpp
	src/QServer/QServerNT.cpp
	src/SafeSock.cpp
	src/String/FogString.cpp
	src/System/System.cpp
	
	# Made up filename
	src/Calc.cpp
	src/Math.cpp
	src/Huffman.cpp
	src/Sha1.cpp
	src/Noop.cpp
	
	# Headers
	include/Fog.h
	include/D2BitManip.h
	include/DataArrays.h
	include/IFF.h
	include/Sha1.h
	include/Mem/Mem.h
	include/Safesock.h
	include/System/System.h
)

if(D2MOO_WITH_STATIC_TESTS)
  target_sources(Fog
    PRIVATE
      statictests/Fog_staticchecks.cpp
  )
endif()

D2MOO_target_source_group(Fog)

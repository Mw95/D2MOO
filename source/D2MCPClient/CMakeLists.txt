
D2MOO_prepare_targets(D2MCPClient STUB)

target_link_libraries(${D2MCPClientImplName} PUBLIC D2CommonDefinitions)

target_sources(${D2MCPClientImplName}
  PRIVATE
	src/D2MCPClient.cpp
	include/D2MCPClient.h
)
D2MOO_target_source_group(D2MCPClient)

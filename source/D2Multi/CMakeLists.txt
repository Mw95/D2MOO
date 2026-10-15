
D2MOO_prepare_targets(D2Multi)

target_link_libraries(${D2MultiImplName}
  PRIVATE
    D2CommonDefinitions
    D2CMP
    D2Gfx
    D2Lang
    D2MCPClient
    D2Sound
    D2Win
    Fog
    Storm
)

# src/DllMain.cpp is compiled in the D2Multi target (for shared builds) and uses the string tables and the control definitions
target_link_libraries(D2Multi
  PRIVATE
    D2CommonDefinitions
    D2Lang
    D2Win
)

target_sources(${D2MultiImplName}
  PRIVATE
    src/ChatDlg.cpp
    src/ComCallback.cpp
    src/D2Multi.cpp
    src/Gate.cpp

    include/ChatDlg.h
    include/ComCallback.h
    include/D2Multi.h
    include/Gate.h
)

D2MOO_target_source_group(D2Multi)

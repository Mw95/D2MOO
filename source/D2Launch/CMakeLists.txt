D2MOO_prepare_targets(D2Launch)

target_compile_features(${D2LaunchImplName} PRIVATE cxx_std_17)

target_link_libraries(${D2LaunchImplName}
  PRIVATE
    Fog
    Storm
    D2Gfx
    D2Lang
    D2Net
    D2Sound
    D2MCPClient
    D2Win
  PUBLIC
    D2CommonDefinitions
)

target_sources(${D2LaunchImplName}
  PRIVATE
    src/BNet.cpp
    src/CharSel.cpp
    src/D2Launch.cpp
    src/MainMenus.cpp
    src/SaveLoad.cpp

    include/BNet.h
    include/CharSel.h
    include/D2Launch.h
    include/MainMenus.h
    include/SaveLoad.h
)

D2MOO_target_source_group(D2Launch)

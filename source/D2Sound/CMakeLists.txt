D2MOO_prepare_targets(D2Sound)

target_link_libraries(${D2SoundImplName}
  PUBLIC
    D2CommonDefinitions
    Storm
  PRIVATE
    D2Gfx
    D2Hell
    Fog
    dsound
    dxguid
    version
)

target_compile_features(${D2SoundImplName} PRIVATE cxx_std_17)

target_sources(${D2SoundImplName}
  PRIVATE
    src/D2Sound.cpp
    src/D2SoundEAX.h
    src/D2SoundFast.cpp
    src/D2SoundSettings.cpp
    src/D2SoundSmp.cpp
    src/D2SoundStrm.cpp
    src/D2SoundUtil.cpp

    include/D2Sound.h
    include/D2SoundFast.h
    include/D2SoundSettings.h
    include/D2SoundSmp.h
    include/D2SoundStrm.h
    include/D2SoundUtil.h
)

D2MOO_target_source_group(D2Sound)

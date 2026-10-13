
D2MOO_prepare_targets(D2OpenGL)

# D2Gfx is only needed for its headers, the renderer does not call it.
target_link_libraries(${D2OpenGLImplName} PRIVATE Fog D2Gfx D2CommonDefinitions opengl32)

target_sources(${D2OpenGLImplName}
  PRIVATE
    src/D2OpenGL.cpp
    src/OglBink.cpp
    src/OglCore.cpp
    src/OglDevice.cpp
    src/OglEngine.cpp
    src/OglFunctions.cpp
    src/OglImports.cpp
    src/OglSmack.cpp
    src/OglSprite.cpp
    src/OglTile.cpp

    include/D2OpenGL.h
    include/OglBink.h
    include/OglCore.h
    include/OglDevice.h
    include/OglEngine.h
    include/OglFunctions.h
    include/OglImports.h
    include/OglSmack.h
    include/OglSprite.h
    include/OglTile.h
)

D2MOO_target_source_group(D2OpenGL)

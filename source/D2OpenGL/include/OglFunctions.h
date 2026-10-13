#pragma once

#include <Windows.h>
#include <GL/gl.h>


// The Windows SDK only provides the OpenGL 1.1 headers, everything newer is declared here and loaded at runtime
// with wglGetProcAddress by FUNCTIONS_Load once an OpenGL 3.3 core context is current.

typedef char GLchar;
typedef void(APIENTRY* GLDEBUGPROC)(GLenum nSource, GLenum nType, GLuint nId, GLenum nSeverity, GLsizei nLength, const GLchar* szMessage, const void* pUserParam);

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#ifndef GL_R8UI
#define GL_R8UI 0x8232
#endif
#ifndef GL_RED_INTEGER
#define GL_RED_INTEGER 0x8D94
#endif
#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif
#ifndef GL_TEXTURE1
#define GL_TEXTURE1 0x84C1
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif
#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif
#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif
#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif
#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_READ_FRAMEBUFFER
#define GL_READ_FRAMEBUFFER 0x8CA8
#endif
#ifndef GL_DRAW_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#endif
#ifndef GL_DEBUG_OUTPUT_SYNCHRONOUS
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#endif
#ifndef GL_DEBUG_SEVERITY_NOTIFICATION
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#endif
#ifndef GL_DEBUG_OUTPUT
#define GL_DEBUG_OUTPUT 0x92E0
#endif

#ifndef WGL_CONTEXT_MAJOR_VERSION_ARB
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#endif
#ifndef WGL_CONTEXT_MINOR_VERSION_ARB
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#endif
#ifndef WGL_CONTEXT_FLAGS_ARB
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#endif
#ifndef WGL_CONTEXT_PROFILE_MASK_ARB
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#endif
#ifndef WGL_CONTEXT_DEBUG_BIT_ARB
#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#endif
#ifndef WGL_CONTEXT_CORE_PROFILE_BIT_ARB
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x0001
#endif


// X(name, return type, parameters)
// Functions required by the renderer, all of them are part of OpenGL 3.3
#define OGL_REQUIRED_FUNCTIONS(X) \
    X(glActiveTexture, void, (GLenum nTexture)) \
    X(glCreateShader, GLuint, (GLenum nType)) \
    X(glShaderSource, void, (GLuint nShader, GLsizei nCount, const GLchar* const* pStrings, const GLint* pLengths)) \
    X(glCompileShader, void, (GLuint nShader)) \
    X(glGetShaderiv, void, (GLuint nShader, GLenum nName, GLint* pParam)) \
    X(glGetShaderInfoLog, void, (GLuint nShader, GLsizei nBufferSize, GLsizei* pLength, GLchar* szLog)) \
    X(glDeleteShader, void, (GLuint nShader)) \
    X(glCreateProgram, GLuint, ()) \
    X(glAttachShader, void, (GLuint nProgram, GLuint nShader)) \
    X(glLinkProgram, void, (GLuint nProgram)) \
    X(glGetProgramiv, void, (GLuint nProgram, GLenum nName, GLint* pParam)) \
    X(glGetProgramInfoLog, void, (GLuint nProgram, GLsizei nBufferSize, GLsizei* pLength, GLchar* szLog)) \
    X(glDeleteProgram, void, (GLuint nProgram)) \
    X(glUseProgram, void, (GLuint nProgram)) \
    X(glGetUniformLocation, GLint, (GLuint nProgram, const GLchar* szName)) \
    X(glUniform1i, void, (GLint nLocation, GLint nValue)) \
    X(glGenVertexArrays, void, (GLsizei nCount, GLuint* pArrays)) \
    X(glBindVertexArray, void, (GLuint nArray)) \
    X(glDeleteVertexArrays, void, (GLsizei nCount, const GLuint* pArrays)) \
    X(glGenFramebuffers, void, (GLsizei nCount, GLuint* pFramebuffers)) \
    X(glBindFramebuffer, void, (GLenum nTarget, GLuint nFramebuffer)) \
    X(glFramebufferTexture2D, void, (GLenum nTarget, GLenum nAttachment, GLenum nTexTarget, GLuint nTexture, GLint nLevel)) \
    X(glCheckFramebufferStatus, GLenum, (GLenum nTarget)) \
    X(glDeleteFramebuffers, void, (GLsizei nCount, const GLuint* pFramebuffers)) \
    X(glBlitFramebuffer, void, (GLint nSrcX0, GLint nSrcY0, GLint nSrcX1, GLint nSrcY1, GLint nDstX0, GLint nDstY0, GLint nDstX1, GLint nDstY1, GLbitfield nMask, GLenum nFilter))

// Functions that may be missing (OpenGL 4.3 or GL_KHR_debug)
#define OGL_OPTIONAL_FUNCTIONS(X) \
    X(glDebugMessageCallback, void, (GLDEBUGPROC pfCallback, const void* pUserParam))

// The pointers are prefixed so that they never clash with the symbols of opengl32.dll or other OpenGL headers
#define OGL_DECLARE_FUNCTION(name, ret, params) \
    typedef ret(APIENTRY* PFN_##name##_D2)params; \
    extern PFN_##name##_D2 gpf_##name;
OGL_REQUIRED_FUNCTIONS(OGL_DECLARE_FUNCTION)
OGL_OPTIONAL_FUNCTIONS(OGL_DECLARE_FUNCTION)
#undef OGL_DECLARE_FUNCTION

#define glActiveTexture gpf_glActiveTexture
#define glCreateShader gpf_glCreateShader
#define glShaderSource gpf_glShaderSource
#define glCompileShader gpf_glCompileShader
#define glGetShaderiv gpf_glGetShaderiv
#define glGetShaderInfoLog gpf_glGetShaderInfoLog
#define glDeleteShader gpf_glDeleteShader
#define glCreateProgram gpf_glCreateProgram
#define glAttachShader gpf_glAttachShader
#define glLinkProgram gpf_glLinkProgram
#define glGetProgramiv gpf_glGetProgramiv
#define glGetProgramInfoLog gpf_glGetProgramInfoLog
#define glDeleteProgram gpf_glDeleteProgram
#define glUseProgram gpf_glUseProgram
#define glGetUniformLocation gpf_glGetUniformLocation
#define glUniform1i gpf_glUniform1i
#define glGenVertexArrays gpf_glGenVertexArrays
#define glBindVertexArray gpf_glBindVertexArray
#define glDeleteVertexArrays gpf_glDeleteVertexArrays
#define glGenFramebuffers gpf_glGenFramebuffers
#define glBindFramebuffer gpf_glBindFramebuffer
#define glFramebufferTexture2D gpf_glFramebufferTexture2D
#define glCheckFramebufferStatus gpf_glCheckFramebufferStatus
#define glDeleteFramebuffers gpf_glDeleteFramebuffers
#define glBlitFramebuffer gpf_glBlitFramebuffer
#define glDebugMessageCallback gpf_glDebugMessageCallback


typedef HGLRC(WINAPI* PFN_wglCreateContextAttribsARB_D2)(HDC hDC, HGLRC hShareContext, const int* pAttribList);
typedef BOOL(WINAPI* PFN_wglSwapIntervalEXT_D2)(int nInterval);


// Loads the functions of the current context, returns FALSE if a required function is missing
BOOL __fastcall FUNCTIONS_Load();
// Resets all the function pointers
void __fastcall FUNCTIONS_Unload();

#include "OglDevice.h"

#include <Fog.h>

#include "OglFunctions.h"


// Draws a triangle covering the whole viewport, without any vertex buffer
static const char* const gszVertexShader = R"(#version 330 core
void main()
{
    vec2 position = vec2((gl_VertexID << 1) & 2, gl_VertexID & 2);
    gl_Position = vec4(position * 2.0 - 1.0, 0.0, 1.0);
}
)";

// Converts the 8 bits indices with the palette, one fragment per pixel of the frame
static const char* const gszPaletteFragmentShader = R"(#version 330 core
uniform usampler2D uIndices;
uniform sampler2D uPalette;
out vec4 oColor;
void main()
{
    uint nIndex = texelFetch(uIndices, ivec2(gl_FragCoord.xy), 0).r;
    oColor = vec4(texelFetch(uPalette, ivec2(int(nIndex), 0), 0).rgb, 1.0);
}
)";


static HWND ghDeviceWnd;
static HDC ghDeviceDC;
static HGLRC ghGLRC;
static PFN_wglSwapIntervalEXT_D2 gpfSwapIntervalEXT;
static BOOL gbDisplayModeChanged;

static GLuint gnPaletteProgram;
static GLuint gnVertexArray;
// 8 bits indices of the game frame
static GLuint gnIndexTexture;
// 256x1 palette
static GLuint gnPaletteTexture;
// 32 bits frame, scaled to the window when presenting
static GLuint gnFrameTexture;
static GLuint gnFrameFramebuffer;

static uint32_t* gpFrameBuffer;
static int32_t gnFrameWidth;
static int32_t gnFrameHeight;


#ifdef _DEBUG
static void APIENTRY DEVICE_DebugMessageCallback(GLenum nSource, GLenum nType, GLuint nId, GLenum nSeverity, GLsizei nLength, const GLchar* szMessage, const void* pUserParam)
{
    if (nSeverity != GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        FOG_Trace("D2OpenGL: %s", szMessage);
    }
}
#endif

static GLuint DEVICE_CompileShader(GLenum nType, const char* szSource)
{
    const GLuint nShader = glCreateShader(nType);
    glShaderSource(nShader, 1, &szSource, nullptr);
    glCompileShader(nShader);

    GLint nStatus = GL_FALSE;
    glGetShaderiv(nShader, GL_COMPILE_STATUS, &nStatus);
    if (!nStatus)
    {
        char szLog[1024] = {};
        glGetShaderInfoLog(nShader, sizeof(szLog), nullptr, szLog);
        FOG_Trace("D2OpenGL: Unable to compile the shader: %s", szLog);
        glDeleteShader(nShader);
        return 0;
    }

    return nShader;
}

static GLuint DEVICE_CreateProgram(const char* szVertexShader, const char* szFragmentShader)
{
    const GLuint nVertexShader = DEVICE_CompileShader(GL_VERTEX_SHADER, szVertexShader);
    const GLuint nFragmentShader = DEVICE_CompileShader(GL_FRAGMENT_SHADER, szFragmentShader);
    if (!nVertexShader || !nFragmentShader)
    {
        glDeleteShader(nVertexShader);
        glDeleteShader(nFragmentShader);
        return 0;
    }

    GLuint nProgram = glCreateProgram();
    glAttachShader(nProgram, nVertexShader);
    glAttachShader(nProgram, nFragmentShader);
    glLinkProgram(nProgram);
    // The shaders are freed with the program
    glDeleteShader(nVertexShader);
    glDeleteShader(nFragmentShader);

    GLint nStatus = GL_FALSE;
    glGetProgramiv(nProgram, GL_LINK_STATUS, &nStatus);
    if (!nStatus)
    {
        char szLog[1024] = {};
        glGetProgramInfoLog(nProgram, sizeof(szLog), nullptr, szLog);
        FOG_Trace("D2OpenGL: Unable to link the program: %s", szLog);
        glDeleteProgram(nProgram);
        return 0;
    }

    return nProgram;
}

// Creates a texture sampled without filtering, the filtering is done by glBlitFramebuffer
static GLuint DEVICE_CreateTexture(GLint nInternalFormat, int32_t nWidth, int32_t nHeight, GLenum nFormat, GLenum nType)
{
    GLuint nTexture = 0;
    glGenTextures(1, &nTexture);
    glBindTexture(GL_TEXTURE_2D, nTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, nInternalFormat, nWidth, nHeight, 0, nFormat, nType, nullptr);
    return nTexture;
}

static void DEVICE_DeleteTexture(GLuint* pTexture)
{
    if (*pTexture)
    {
        glDeleteTextures(1, pTexture);
        *pTexture = 0;
    }
}

static void DEVICE_FreeFrame()
{
    if (gnFrameFramebuffer)
    {
        glDeleteFramebuffers(1, &gnFrameFramebuffer);
        gnFrameFramebuffer = 0;
    }

    DEVICE_DeleteTexture(&gnFrameTexture);
    DEVICE_DeleteTexture(&gnIndexTexture);

    if (gpFrameBuffer)
    {
        D2_FREE(gpFrameBuffer);
        gpFrameBuffer = nullptr;
    }

    gnFrameWidth = 0;
    gnFrameHeight = 0;
}

// Creates an OpenGL 3.3 core context. wglCreateContextAttribsARB can only be retrieved with a current context,
// so a legacy context is created first.
static HGLRC DEVICE_CreateCoreContext(HDC hDC)
{
    HGLRC hLegacyContext = wglCreateContext(hDC);
    if (!hLegacyContext || !wglMakeCurrent(hDC, hLegacyContext))
    {
        FOG_Trace("D2OpenGL: Unable to create the OpenGL context (%d)", GetLastError());
        if (hLegacyContext)
        {
            wglDeleteContext(hLegacyContext);
        }
        return nullptr;
    }

    const PFN_wglCreateContextAttribsARB_D2 pfCreateContextAttribsARB = (PFN_wglCreateContextAttribsARB_D2)wglGetProcAddress("wglCreateContextAttribsARB");

    HGLRC hContext = nullptr;
    if (pfCreateContextAttribsARB)
    {
        const int pAttributes[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef _DEBUG
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            0
        };
        hContext = pfCreateContextAttribsARB(hDC, nullptr, pAttributes);
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hLegacyContext);

    if (!hContext)
    {
        FOG_Trace("D2OpenGL: OpenGL 3.3 is not supported");
        return nullptr;
    }

    if (!wglMakeCurrent(hDC, hContext))
    {
        FOG_Trace("D2OpenGL: Unable to make the OpenGL context current (%d)", GetLastError());
        wglDeleteContext(hContext);
        return nullptr;
    }

    return hContext;
}

BOOL __fastcall DEVICE_Create(HWND hWnd)
{
    D2_ASSERT(hWnd);

    if (ghGLRC)
    {
        D2_ASSERT(hWnd == ghDeviceWnd);
        return TRUE;
    }

    ghDeviceWnd = hWnd;
    ghDeviceDC = GetDC(hWnd);
    if (!ghDeviceDC)
    {
        FOG_Trace("D2OpenGL: GetDC failed (%d)", GetLastError());
        return FALSE;
    }

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
    pixelFormatDescriptor.nSize = sizeof(pixelFormatDescriptor);
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits = 32;
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

    // The pixel format of a window can only be set once, we keep the window and context alive until DEVICE_Destroy
    if (!GetPixelFormat(ghDeviceDC))
    {
        const int32_t nPixelFormat = ChoosePixelFormat(ghDeviceDC, &pixelFormatDescriptor);
        if (!nPixelFormat || !SetPixelFormat(ghDeviceDC, nPixelFormat, &pixelFormatDescriptor))
        {
            FOG_Trace("D2OpenGL: Unable to set the pixel format (%d)", GetLastError());
            DEVICE_Destroy();
            return FALSE;
        }
    }

    ghGLRC = DEVICE_CreateCoreContext(ghDeviceDC);
    if (!ghGLRC)
    {
        DEVICE_Destroy();
        return FALSE;
    }

    FOG_Trace("\tVendor: %s", (const char*)glGetString(GL_VENDOR));
    FOG_Trace("\tRenderer: %s", (const char*)glGetString(GL_RENDERER));
    FOG_Trace("\tVersion: %s", (const char*)glGetString(GL_VERSION));

    if (!FUNCTIONS_Load())
    {
        DEVICE_Destroy();
        return FALSE;
    }

#ifdef _DEBUG
    if (glDebugMessageCallback)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DEVICE_DebugMessageCallback, nullptr);
    }
#endif

    gpfSwapIntervalEXT = (PFN_wglSwapIntervalEXT_D2)wglGetProcAddress("wglSwapIntervalEXT");

    gnPaletteProgram = DEVICE_CreateProgram(gszVertexShader, gszPaletteFragmentShader);
    if (!gnPaletteProgram)
    {
        DEVICE_Destroy();
        return FALSE;
    }

    glUseProgram(gnPaletteProgram);
    glUniform1i(glGetUniformLocation(gnPaletteProgram, "uIndices"), 0);
    glUniform1i(glGetUniformLocation(gnPaletteProgram, "uPalette"), 1);

    // Core profiles require a vertex array object to draw, even without vertex attributes
    glGenVertexArrays(1, &gnVertexArray);
    glBindVertexArray(gnVertexArray);

    gnPaletteTexture = DEVICE_CreateTexture(GL_RGBA8, 256, 1, GL_BGRA, GL_UNSIGNED_BYTE);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    // Rows of the frames are tightly packed
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return TRUE;
}

void __fastcall DEVICE_Destroy()
{
    if (ghGLRC)
    {
        DEVICE_FreeFrame();
        DEVICE_DeleteTexture(&gnPaletteTexture);

        if (gnVertexArray)
        {
            glDeleteVertexArrays(1, &gnVertexArray);
            gnVertexArray = 0;
        }

        if (gnPaletteProgram)
        {
            glDeleteProgram(gnPaletteProgram);
            gnPaletteProgram = 0;
        }

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(ghGLRC);
        ghGLRC = nullptr;
    }
    else if (gpFrameBuffer)
    {
        D2_FREE(gpFrameBuffer);
        gpFrameBuffer = nullptr;
    }

    if (ghDeviceDC)
    {
        ReleaseDC(ghDeviceWnd, ghDeviceDC);
        ghDeviceDC = nullptr;
    }

    FUNCTIONS_Unload();
    gpfSwapIntervalEXT = nullptr;
    ghDeviceWnd = nullptr;
}

BOOL __fastcall DEVICE_IsCreated()
{
    return ghGLRC != nullptr;
}

BOOL __fastcall DEVICE_SetFrameSize(int32_t nWidth, int32_t nHeight)
{
    D2_ASSERT(ghGLRC);
    D2_ASSERT(nWidth > 0 && nHeight > 0);

    if (nWidth == gnFrameWidth && nHeight == gnFrameHeight)
    {
        return TRUE;
    }

    DEVICE_FreeFrame();

    gpFrameBuffer = (uint32_t*)D2_CALLOC(sizeof(uint32_t) * nWidth * nHeight);
    gnFrameWidth = nWidth;
    gnFrameHeight = nHeight;

    GLint nMaxTextureSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nMaxTextureSize);
    if (nWidth > nMaxTextureSize || nHeight > nMaxTextureSize)
    {
        FOG_Trace("D2OpenGL: %dx%d textures are not supported (max %d)", nWidth, nHeight, nMaxTextureSize);
        return FALSE;
    }

    // The frames are stored top-down: the first row of the textures is the top of the screen
    gnIndexTexture = DEVICE_CreateTexture(GL_R8UI, nWidth, nHeight, GL_RED_INTEGER, GL_UNSIGNED_BYTE);
    gnFrameTexture = DEVICE_CreateTexture(GL_RGBA8, nWidth, nHeight, GL_BGRA, GL_UNSIGNED_BYTE);

    glGenFramebuffers(1, &gnFrameFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gnFrameFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gnFrameTexture, 0);
    const GLenum nStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (nStatus == GL_FRAMEBUFFER_COMPLETE)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (nStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        FOG_Trace("D2OpenGL: Unable to create a %dx%d frame buffer (0x%X)", nWidth, nHeight, nStatus);
        return FALSE;
    }

    if (const GLenum nError = glGetError())
    {
        FOG_Trace("D2OpenGL: Unable to create %dx%d textures (0x%X)", nWidth, nHeight, nError);
        return FALSE;
    }

    return TRUE;
}

// Scales the frame to the client area of the window and swaps the buffers
static void DEVICE_PresentFrame()
{
    RECT clientRect = {};
    GetClientRect(ghDeviceWnd, &clientRect);
    if (clientRect.right <= 0 || clientRect.bottom <= 0)
    {
        return;
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, clientRect.right, clientRect.bottom);
    glClear(GL_COLOR_BUFFER_BIT);

    // Pixel perfect when the window matches the frame, otherwise smooth the scaling
    const GLenum nFilter = clientRect.right == gnFrameWidth && clientRect.bottom == gnFrameHeight ? GL_NEAREST : GL_LINEAR;

    // The frame is top-down while the window is bottom-up, flip it vertically
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gnFrameFramebuffer);
    glBlitFramebuffer(0, 0, gnFrameWidth, gnFrameHeight, 0, clientRect.bottom, clientRect.right, 0, GL_COLOR_BUFFER_BIT, nFilter);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    SwapBuffers(ghDeviceDC);
}

void __fastcall DEVICE_PresentIndexed(const uint8_t* pIndices, const uint32_t* pPalette)
{
    if (!ghGLRC || !gnFrameFramebuffer)
    {
        return;
    }

    D2_ASSERT(pIndices && pPalette);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gnPaletteTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 1, GL_BGRA, GL_UNSIGNED_BYTE, pPalette);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gnIndexTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, gnFrameWidth, gnFrameHeight, GL_RED_INTEGER, GL_UNSIGNED_BYTE, pIndices);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gnFrameFramebuffer);
    glViewport(0, 0, gnFrameWidth, gnFrameHeight);
    glUseProgram(gnPaletteProgram);
    glBindVertexArray(gnVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    DEVICE_PresentFrame();
}

uint32_t* __fastcall DEVICE_GetFrameBuffer()
{
    return gpFrameBuffer;
}

void __fastcall DEVICE_PresentFrameBuffer()
{
    if (!ghGLRC || !gnFrameFramebuffer)
    {
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gnFrameTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, gnFrameWidth, gnFrameHeight, GL_BGRA, GL_UNSIGNED_BYTE, gpFrameBuffer);

    DEVICE_PresentFrame();
}

void __fastcall DEVICE_SetVSync(BOOL bVSync)
{
    if (ghGLRC && gpfSwapIntervalEXT)
    {
        gpfSwapIntervalEXT(bVSync ? 1 : 0);
    }
}

BOOL __fastcall DEVICE_SetDisplayMode(int32_t nWidth, int32_t nHeight)
{
    DEVMODEA deviceMode = {};
    deviceMode.dmSize = sizeof(deviceMode);
    deviceMode.dmPelsWidth = nWidth;
    deviceMode.dmPelsHeight = nHeight;
    deviceMode.dmBitsPerPel = 32;
    deviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettingsA(&deviceMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        // Keep the current color depth
        deviceMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
        if (ChangeDisplaySettingsA(&deviceMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            FOG_Trace("D2OpenGL: Unable to change the display mode to %dx%d", nWidth, nHeight);
            return FALSE;
        }
    }

    gbDisplayModeChanged = TRUE;
    return TRUE;
}

void __fastcall DEVICE_RestoreDisplayMode()
{
    if (gbDisplayModeChanged)
    {
        ChangeDisplaySettingsA(nullptr, 0);
        gbDisplayModeChanged = FALSE;
    }
}

#include "OglDevice.h"

#include <GL/gl.h>

#include <Fog.h>


#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC_D2)(int nInterval);


static HWND ghDeviceWnd;
static HDC ghDeviceDC;
static HGLRC ghGLRC;
static GLuint gnTexture;
static int32_t gnTextureWidth;
static int32_t gnTextureHeight;
static GLint gnTextureFilter;
static uint32_t* gpFrameBuffer;
static int32_t gnFrameWidth;
static int32_t gnFrameHeight;
static BOOL gbDisplayModeChanged;
static PFNWGLSWAPINTERVALEXTPROC_D2 gpfSwapIntervalEXT;


static int32_t DEVICE_NextPowerOfTwo(int32_t nValue)
{
    int32_t nResult = 1;
    while (nResult < nValue)
    {
        nResult <<= 1;
    }

    return nResult;
}

static void DEVICE_SetTextureFilter(GLint nFilter)
{
    if (gnTextureFilter != nFilter)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nFilter);
        gnTextureFilter = nFilter;
    }
}

static void DEVICE_FreeFrame()
{
    if (gnTexture)
    {
        glDeleteTextures(1, &gnTexture);
        gnTexture = 0;
    }

    if (gpFrameBuffer)
    {
        D2_FREE(gpFrameBuffer);
        gpFrameBuffer = nullptr;
    }

    gnTextureWidth = 0;
    gnTextureHeight = 0;
    gnFrameWidth = 0;
    gnFrameHeight = 0;
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

    ghGLRC = wglCreateContext(ghDeviceDC);
    if (!ghGLRC || !wglMakeCurrent(ghDeviceDC, ghGLRC))
    {
        FOG_Trace("D2OpenGL: Unable to create the OpenGL context (%d)", GetLastError());
        DEVICE_Destroy();
        return FALSE;
    }

    FOG_Trace("\tVendor: %s", (const char*)glGetString(GL_VENDOR));
    FOG_Trace("\tRenderer: %s", (const char*)glGetString(GL_RENDERER));
    FOG_Trace("\tVersion: %s", (const char*)glGetString(GL_VERSION));

    gpfSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC_D2)wglGetProcAddress("wglSwapIntervalEXT");

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DITHER);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return TRUE;
}

void __fastcall DEVICE_Destroy()
{
    if (ghGLRC)
    {
        DEVICE_FreeFrame();
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

    // Only use power of two textures to support OpenGL 1.1
    gnTextureWidth = DEVICE_NextPowerOfTwo(nWidth);
    gnTextureHeight = DEVICE_NextPowerOfTwo(nHeight);

    GLint nMaxTextureSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nMaxTextureSize);
    if (gnTextureWidth > nMaxTextureSize || gnTextureHeight > nMaxTextureSize)
    {
        FOG_Trace("D2OpenGL: %dx%d textures are not supported (max %d)", gnTextureWidth, gnTextureHeight, nMaxTextureSize);
        return FALSE;
    }

    glGenTextures(1, &gnTexture);
    glBindTexture(GL_TEXTURE_2D, gnTexture);

    gnTextureFilter = 0;
    DEVICE_SetTextureFilter(GL_NEAREST);

    while (glGetError() != GL_NO_ERROR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (glGetError() != GL_NO_ERROR)
    {
        // OpenGL 1.1 without GL_EXT_texture_edge_clamp
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, gnTextureWidth, gnTextureHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, nullptr);
    if (const GLenum nError = glGetError())
    {
        FOG_Trace("D2OpenGL: Unable to create a %dx%d texture (0x%X)", gnTextureWidth, gnTextureHeight, nError);
        return FALSE;
    }

    return TRUE;
}

uint32_t* __fastcall DEVICE_GetFrameBuffer()
{
    return gpFrameBuffer;
}

void __fastcall DEVICE_Present()
{
    if (!ghGLRC || !gnTexture)
    {
        return;
    }

    RECT clientRect = {};
    GetClientRect(ghDeviceWnd, &clientRect);
    if (clientRect.right <= 0 || clientRect.bottom <= 0)
    {
        return;
    }

    glViewport(0, 0, clientRect.right, clientRect.bottom);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, gnTexture);
    // Pixel perfect when the window matches the frame, otherwise smooth the scaling
    DEVICE_SetTextureFilter(clientRect.right == gnFrameWidth && clientRect.bottom == gnFrameHeight ? GL_NEAREST : GL_LINEAR);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, gnFrameWidth, gnFrameHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE, gpFrameBuffer);

    const float fMaxU = (float)gnFrameWidth / (float)gnTextureWidth;
    const float fMaxV = (float)gnFrameHeight / (float)gnTextureHeight;

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(fMaxU, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(fMaxU, fMaxV);
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(0.0f, fMaxV);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    SwapBuffers(ghDeviceDC);
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

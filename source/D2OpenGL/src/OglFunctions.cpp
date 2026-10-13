#include "OglFunctions.h"

#include <cstdint>

#include <Fog.h>


#define OGL_DEFINE_FUNCTION(name, ret, params) PFN_##name##_D2 gpf_##name;
OGL_REQUIRED_FUNCTIONS(OGL_DEFINE_FUNCTION)
OGL_OPTIONAL_FUNCTIONS(OGL_DEFINE_FUNCTION)
#undef OGL_DEFINE_FUNCTION


static PROC FUNCTIONS_GetProcAddress(const char* szName)
{
    PROC pProc = wglGetProcAddress(szName);
    // Some drivers return small values instead of nullptr for missing functions
    if ((uintptr_t)pProc <= 3 || (intptr_t)pProc == -1)
    {
        return nullptr;
    }

    return pProc;
}

BOOL __fastcall FUNCTIONS_Load()
{
    BOOL bResult = TRUE;

#define OGL_LOAD_REQUIRED_FUNCTION(name, ret, params) \
    gpf_##name = (PFN_##name##_D2)FUNCTIONS_GetProcAddress(#name); \
    if (!gpf_##name) \
    { \
        FOG_Trace("D2OpenGL: Missing OpenGL function %s", #name); \
        bResult = FALSE; \
    }
    OGL_REQUIRED_FUNCTIONS(OGL_LOAD_REQUIRED_FUNCTION)
#undef OGL_LOAD_REQUIRED_FUNCTION

#define OGL_LOAD_OPTIONAL_FUNCTION(name, ret, params) gpf_##name = (PFN_##name##_D2)FUNCTIONS_GetProcAddress(#name);
    OGL_OPTIONAL_FUNCTIONS(OGL_LOAD_OPTIONAL_FUNCTION)
#undef OGL_LOAD_OPTIONAL_FUNCTION

    return bResult;
}

void __fastcall FUNCTIONS_Unload()
{
#define OGL_UNLOAD_FUNCTION(name, ret, params) gpf_##name = nullptr;
    OGL_REQUIRED_FUNCTIONS(OGL_UNLOAD_FUNCTION)
    OGL_OPTIONAL_FUNCTIONS(OGL_UNLOAD_FUNCTION)
#undef OGL_UNLOAD_FUNCTION
}

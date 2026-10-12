#include "D2OpenGL.h"

#include "OglBink.h"
#include "OglCore.h"
#include "OglEngine.h"
#include "OglSmack.h"
#include "OglSprite.h"
#include "OglTile.h"


static D2GraphicsInterfaceStrc gOpenGLInterface =
{
    OGL_Detect,
    OGL_Init,
    OGL_Close,
    OGL_CreateSurface,
    OGL_CloseSurface,
    OGL_PauseSurface,
    OGL_StartDraw,
    OGL_EndDraw,
    OGL_Blit,
    OGL_ChangeRes,
    OGL_GetBackBuffer,
    OGL_ActivateWindow,
    OGL_SetOption,
    OGL_PlayCutscene,
    OGL_OpenSmackCutscene,
    OGL_CheckCutScene,
    OGL_DecodeSmacker,
    OGL_PlaySmacker,
    OGL_CloseSmacker,
    OGL_GetCacheResults,
    OGL_GetDimensions,
    OGL_SetGlobalScale,
    OGL_SetGamma,
    OGL_GammaCanBeControlled,
    OGL_UpdatePerspective,
    OGL_PerspectiveTransform,
    OGL_PerspectiveTransformScale,
    OGL_PerspectiveClearScale,
    OGL_SetPalette,
    OGL_SetPaletteTables,
    OGL_SetAmbientColor,
    OGL_FloorTileDraw,
    OGL_CelFlatSpriteDraw,
    OGL_CelDraw,
    OGL_CelDrawColor,
    OGL_CelDrawEx,
    OGL_CelDrawShadow,
    OGL_CelDrawHilight,
    OGL_CelDrawClipped,
    OGL_TileDrawLit,
    OGL_TileDrawTrans,
    OGL_ShadowTileDraw,
    OGL_UtilDiamond,
    OGL_UtilRect,
    OGL_UtilFilledRect,
    OGL_UtilPoint,
    OGL_DrawBox,
    OGL_DrawBoxAlpha,
    OGL_DrawLine,
    OGL_ClearScreen,
    OGL_OutputString,
    OGL_DebugDraw,
    OGL_DebugFillBackBuffer,
    OGL_ClearCaches,
};


//D2OpenGL (#10000)
D2GraphicsInterfaceStrc* __fastcall D2OpenGL_GetGraphicsInterface()
{
    return &gOpenGLInterface;
}

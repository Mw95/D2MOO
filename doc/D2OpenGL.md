# D2OpenGL renderer

`D2OpenGL.dll` is a renderer for `D2Gfx.dll`, like `D2Gdi.dll`, `D2DDraw.dll`, `D2Glide.dll` and `D2Direct3D.dll`.
The original game reserves the `DISPLAYTYPE_OPENGL` display type but never shipped a renderer for it.

It exports the same interface as the other renderers: ordinal `#10000` returns a `D2GraphicsInterfaceStrc` (see [D2Gfx.h](../source/D2Gfx/include/D2Gfx.h)).

## How it renders

The game is drawn exactly like `D2Gdi.dll` and `D2DDraw.dll` draw it: into an 8 bits back buffer, with the `D2CMP.dll` software cel functions and the `D2Gfx.dll` tile helpers. This keeps the output identical to the original software renderers.

OpenGL is used to present the back buffer:
- each frame is uploaded as is to an 8 bits integer texture, and a fragment shader converts it with the gamma corrected palette into an offscreen frame buffer,
- the offscreen frame buffer is scaled to the whole window with `glBlitFramebuffer` (nearest filtering when the window matches the game resolution, linear otherwise), so the window can have any size,
- vertical synchronization uses `WGL_EXT_swap_control` when available,
- in fullscreen mode the screen resolution is changed to the game resolution, and restored while the game is minimized,
- Bink cutscenes are decoded to 32 bits, uploaded to the offscreen frame buffer and presented the same way.

OpenGL 3.3 (core profile) is required. The context is created with `WGL_ARB_create_context`, and the functions newer than OpenGL 1.1 are loaded at runtime (see [OglFunctions.h](../source/D2OpenGL/include/OglFunctions.h)).
Debug builds create a debug context and trace the OpenGL debug messages when `GL_KHR_debug` is available.

Like the other software renderers, it does not support the perspective mode, the colored lights (only their intensity is used) or `pfCelDrawHilight`.

Functions that D2MOO does not implement yet (`D2CMP.dll`, `Storm.dll`, `D2Sound.dll`, `binkw32.dll` and `smackw32.dll`) are resolved at runtime from the game modules, see [OglImports.h](../source/D2OpenGL/include/OglImports.h).

## Usage

The original `D2Gfx.dll` refuses to load an OpenGL renderer, D2MOO's `D2Gfx.dll` is required.
`D2OpenGL.dll` must be in the game folder (next to `D2Gfx.dll`).

With `Game.D2MOO.exe`, use the `-opengl` command line option (or set the `Render` value of the `SOFTWARE\Blizzard Entertainment\Diablo II\VideoConfig` registry key to `2`).
This is enabled by the `D2MOO_GAME_WITH_OPENGL` CMake option (`ON` by default).

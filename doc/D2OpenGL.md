# D2OpenGL renderer

`D2OpenGL.dll` is a renderer for `D2Gfx.dll`, like `D2Gdi.dll`, `D2DDraw.dll`, `D2Glide.dll` and `D2Direct3D.dll`.
The original game reserves the `DISPLAYTYPE_OPENGL` display type but never shipped a renderer for it.

It exports the same interface as the other renderers: ordinal `#10000` returns a `D2GraphicsInterfaceStrc` (see [D2Gfx.h](../source/D2Gfx/include/D2Gfx.h)).

## How it renders

The game is drawn exactly like `D2Gdi.dll` and `D2DDraw.dll` draw it: into an 8 bits back buffer, with the `D2CMP.dll` software cel functions and the `D2Gfx.dll` tile helpers. This keeps the output identical to the original software renderers.

OpenGL is used to present the back buffer:
- each frame is converted to 32 bits with the gamma corrected palette and uploaded to a texture drawn over the whole window, so the window can have any size,
- vertical synchronization uses `WGL_EXT_swap_control` when available,
- in fullscreen mode the screen resolution is changed to the game resolution, and restored while the game is minimized,
- Bink cutscenes are decoded to 32 bits and presented the same way.

Only OpenGL 1.1 is required.

Like the other software renderers, it does not support the perspective mode, the colored lights (only their intensity is used) or `pfCelDrawHilight`.

Functions that D2MOO does not implement yet (`D2CMP.dll`, `Storm.dll`, `D2Sound.dll`, `binkw32.dll` and `smackw32.dll`) are resolved at runtime from the game modules, see [OglImports.h](../source/D2OpenGL/include/OglImports.h).

## Usage

The original `D2Gfx.dll` refuses to load an OpenGL renderer, D2MOO's `D2Gfx.dll` is required.
`D2OpenGL.dll` must be in the game folder (next to `D2Gfx.dll`).

With `Game.D2MOO.exe`, use the `-opengl` command line option (or set the `Render` value of the `SOFTWARE\Blizzard Entertainment\Diablo II\VideoConfig` registry key to `2`).
This is enabled by the `D2MOO_GAME_WITH_OPENGL` CMake option (`ON` by default).

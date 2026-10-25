#pragma once


#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include <Windows.h>

#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>

#include <D2Constants.h>

#include <D2Gfx.h>
#include <DisplayType.h>

#include <D2Gfx/D2GfxVisitorDefinitions.h>
#include <Fixtures/D2Gfx/D2GfxOriginalDll.h>
#include <Fixtures/D2Gfx/D2GraphicsInterfaceMockFixture.h>


// Globals of the D2MOO implementation that are not declared in a header
extern DisplayType gnDisplayType;
extern int32_t gnViewMatrixAdjust_6FA8D254;
extern PALETTEENTRY gpPalette_6FA8D278[256];
extern int32_t gnScaleFactor;
extern HWND ghWnd;
extern int32_t gbIsWindowed;
extern D2GameResolutionMode gnResolutionMode;
extern int32_t gnWindowBorderHeight_6FA8D740;
extern int32_t gbNoWindowCreated_6FA8D848;
extern int32_t gbPaused_6FA8D84C;
extern int32_t gbWindowState_6FA8D850;


// Copy of the globals of D2Gfx.cpp, Scale.cpp and Window.cpp, used to compare the state of both implementations
struct D2GfxStateStrc
{
	D2GraphicsInterfaceStrc* pGraphicsInterface;
	DisplayType nDisplayType;
	D2GfxSettingsStrc GfxSettings;
	int32_t nViewMatrixAdjust;
	PALETTEENTRY Palette[256];
	int32_t nScaleFactor;
	HWND hWnd;
	int32_t bIsWindowed;
	D2GameResolutionMode nResolutionMode;
	int32_t nWindowBorderHeight;
	int32_t bNoWindowCreated;
	int32_t bPaused;
	int32_t bWindowState;
};

BEGIN_VISIT(D2GfxStateStrc)
	FIELD(pGraphicsInterface)
	FIELD(nDisplayType)
	OBJECT(GfxSettings)
	FIELD(nViewMatrixAdjust)
	ARRAY(Palette)
	FIELD(nScaleFactor)
	FIELD(hWnd)
	FIELD(bIsWindowed)
	FIELD(nResolutionMode)
	FIELD(nWindowBorderHeight)
	FIELD(bNoWindowCreated)
	FIELD(bPaused)
	FIELD(bWindowState)
END_VISIT()


// References to the globals of one implementation
struct D2GfxGlobals
{
	D2GraphicsInterfaceStrc*& pGraphicsInterface;
	DisplayType& nDisplayType;
	D2GfxSettingsStrc& GfxSettings;
	int32_t& nViewMatrixAdjust;
	PALETTEENTRY(&Palette)[256];
	int32_t& nScaleFactor;
	HWND& hWnd;
	int32_t& bIsWindowed;
	D2GameResolutionMode& nResolutionMode;
	int32_t& nWindowBorderHeight;
	int32_t& bNoWindowCreated;
	int32_t& bPaused;
	int32_t& bWindowState;

	D2GfxStateStrc snapshot() const
	{
		D2GfxStateStrc state{};
		state.pGraphicsInterface = pGraphicsInterface;
		state.nDisplayType = nDisplayType;
		state.GfxSettings = GfxSettings;
		state.nViewMatrixAdjust = nViewMatrixAdjust;
		std::memcpy(state.Palette, Palette, sizeof(state.Palette));
		state.nScaleFactor = nScaleFactor;
		state.hWnd = hWnd;
		state.bIsWindowed = bIsWindowed;
		state.nResolutionMode = nResolutionMode;
		state.nWindowBorderHeight = nWindowBorderHeight;
		state.bNoWindowCreated = bNoWindowCreated;
		state.bPaused = bPaused;
		state.bWindowState = bWindowState;
		return state;
	}
};

inline D2GfxGlobals make_moo_d2gfx_globals()
{
	return D2GfxGlobals{
		gpGraphicsInterface,
		gnDisplayType,
		gGfxSettings,
		gnViewMatrixAdjust_6FA8D254,
		gpPalette_6FA8D278,
		gnScaleFactor,
		ghWnd,
		gbIsWindowed,
		gnResolutionMode,
		gnWindowBorderHeight_6FA8D740,
		gbNoWindowCreated_6FA8D848,
		gbPaused_6FA8D84C,
		gbWindowState_6FA8D850,
	};
}

inline D2GfxSettingsStrc& d2gfx_original_gfx_settings()
{
	// D2GFX_CheckLowQuality, D2GFX_CheckBlendedShadows and D2GFX_CheckUnitPerspective all read a member of gGfxSettings
	auto& settings = d2gfx_original_global_from_function<D2GfxSettingsStrc>(0x00003BE0, offsetof(D2GfxSettingsStrc, bLowQuality));
	if (&settings != &d2gfx_original_global_from_function<D2GfxSettingsStrc>(0x00003BA0, offsetof(D2GfxSettingsStrc, bBlendedShadows))
		|| &settings != &d2gfx_original_global_from_function<D2GfxSettingsStrc>(0x00003AF0, offsetof(D2GfxSettingsStrc, bPerspectiveCapable)))
	{
		throw std::runtime_error("Inconsistent addresses for gGfxSettings in the original D2Gfx.dll");
	}

	return settings;
}

inline D2GfxGlobals make_original_d2gfx_globals()
{
	return D2GfxGlobals{
		d2gfx_original_global_from_function<D2GraphicsInterfaceStrc*>(0x00003C20),		// D2GFX_GammaCanBeControlled
		d2gfx_original_global_from_function<DisplayType>(0x00003AC0),					// D2GFX_GetDisplayType
		d2gfx_original_gfx_settings(),
		d2gfx_original_global<int32_t>(0x0001D254),
		d2gfx_original_global<PALETTEENTRY[256]>(0x0001D278),
		d2gfx_original_global_from_function<int32_t>(0x00003F50),						// SCALE_GetFactor
		d2gfx_original_global_from_function<HWND>(0x000049C0),							// WINDOW_GetWindow
		d2gfx_original_global_from_function<int32_t>(0x00003AD0),						// D2GFX_CheckWindowed
		d2gfx_original_global_from_function<D2GameResolutionMode>(0x00003AE0),			// D2GFX_GetResolutionMode
		d2gfx_original_global<int32_t>(0x0001D740),
		d2gfx_original_global<int32_t>(0x0001D848),
		d2gfx_original_global<int32_t>(0x0001D84C),
		d2gfx_original_global<int32_t>(0x0001D850),
	};
}


// Makes both implementations use the graphics interface mock and gives access to their globals.
// The globals are reset to the same values for both implementations.
template<class Fixture>
struct D2GfxGlobalsFixture : Fixture
{
	D2GraphicsInterfaceStrc graphics_interface = make_graphics_interface_mock();
	D2GfxGlobals moo_globals = make_moo_d2gfx_globals();
	D2GfxGlobals original_globals = make_original_d2gfx_globals();

	D2GfxGlobalsFixture()
	{
		const auto setup_data = [this](
			D2GfxGlobals& globals
		) {
			globals.pGraphicsInterface = &graphics_interface;
			globals.nDisplayType = DISPLAYTYPE_DDRAW;
			globals.GfxSettings = { 0, 1, 0, 155, 1, 1 };
			globals.nViewMatrixAdjust = 0;
			std::memset(globals.Palette, 0, sizeof(globals.Palette));
			globals.nScaleFactor = 256;
			globals.hWnd = nullptr;
			globals.bIsWindowed = 0;
			globals.nResolutionMode = D2GAMERES_640x480;
			globals.nWindowBorderHeight = 0;
			globals.bNoWindowCreated = 0;
			globals.bPaused = 0;
			globals.bWindowState = 0;
		};

		setup_data(moo_globals);
		setup_data(original_globals);

		D2GraphicsInterfaceMock::return_value = 0;
		D2GraphicsInterfaceMock::calls.clear();
		D2GraphicsInterfaceMock::output_strings.clear();
	}

	~D2GfxGlobalsFixture()
	{
		// Do not leave a dangling pointer to the mock
		moo_globals.pGraphicsInterface = nullptr;
		original_globals.pGraphicsInterface = nullptr;
	}

	// Snapshots the globals of both implementations and compares them
	void check_globals_eq(const char* context_title)
	{
		auto moo_state = moo_globals.snapshot();
		auto original_state = original_globals.snapshot();
		MOO_CHECK_EQ(moo_state, original_state, context_title);
	}

	// Compares the calls to the graphics interface since the last call to take_calls()
	void check_calls_eq(std::vector<D2GfxInterfaceCallStrc>& moo_calls, std::vector<D2GfxInterfaceCallStrc>& original_calls)
	{
		check_interface_calls_eq(moo_calls, original_calls, "Comparing calls to the graphics interface");
	}
};

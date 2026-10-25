#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include <D2WinPalette.h>


BEGIN_VISIT(PALETTEENTRY)
	FIELD(peRed)
	FIELD(peGreen)
	FIELD(peBlue)
	FIELD(peFlags)
END_VISIT()

BEGIN_VISIT(D2ShadowLightGammaPaletteStrc)
	//BEGIN_UNION()
		//ARRAY(shadowsPalette)
		//ARRAY(lightPalette)
		//ARRAY(gammaPalette)
		ARRAY(palettes)
	//END_UNION()
END_VISIT()

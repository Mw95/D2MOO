#pragma once


#include <DiffContext.h>
#include <DiffVisitor.h>
#include <Macros.h>
#include <TypeId.h>
#include <TypeRegistration.h>


#include "../D2Lang/D2UnicodeVisitorDefinitions.h"

#include <D2WinComp.h>


BEGIN_VISIT(D2CofDataStrc)
	FIELD(nLayers)
	FIELD(nFrames)
	FIELD(nDirections)
	FIELD(nVersion)
	FIELD(dwReserved)
	ARRAY(nBoundingBox)
	FIELD(nAnimRate)
END_VISIT()

BEGIN_VISIT(D2CofLayerStrc)
	FIELD(nComponent)
	FIELD(nShadow)
	FIELD(nSelectable)
	FIELD(nTransparent)
	FIELD(nDrawEffect)
	ARRAY(szWeaponClass)
END_VISIT()

BEGIN_VISIT(D2CofNodeStrc)
	FIELD(nRefCount)
	FIELD(nMode)
	FIELD(nClass)
	FIELD(dwWClassToken)
	FIELD(nFileSize)
	POINTER(pCofData)
	POINTER(pNext)
	POINTER(pPrev)
END_VISIT()

BEGIN_VISIT(D2CofInfoStrc)
	POINTER(pCofNode)
	POINTER(pNext)
END_VISIT()

BEGIN_VISIT(D2GfxInfoStrc)
	POINTER(pCofInfo)
END_VISIT()

BEGIN_VISIT(D2CompositeUnitStrc)
	FIELD(dwFlags)
	FIELD(nDirection)
	FIELD(nDirections)
	//ARRAY(pad0x06)
	FIELD(nFrame)
	FIELD(nFrames)
	FIELD(nAnimRate)
	FIELD(nX)
	FIELD(nY)
	FIELD(nClass)
	FIELD(nMode)
	FIELD(nWClassTokenIndex)
	ARRAY(nComponentColors)
	ARRAY(dwComponentTokens)
	ARRAY(nComponentItemTypes)
	POINTER(pGfxInfo)
	FIELD(pEmblemCellFile)
	FIELD(nEmblemColor1)
	FIELD(nEmblemColor2)
	//ARRAY(pad0xC2)
	POINTER(pNext)
	POINTER(pPrev)
	ARRAY(wszAccountName)
	ARRAY(wszCharName)
	ARRAY(wszUnk0x1CC)
	ARRAY(wszRealmName)
	FIELD(nLevel)
	FIELD(dwProductCode)
END_VISIT()

#pragma once


#include <cstdint>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <D2Unicode.h>
#include <D2WinComp.h>
#include <D2WinEditBox.h>
#include <D2WinMain.h>
#include <D2WinTextBox.h>

#include <ImportHooks.h>


// Recording replacements of the D2Win functions used by the D2Multi user interface.
// Composite units are fake objects, and every call is logged as text with the units and controls replaced by names,
// so that the logs of both implementations can be compared.
struct D2WinRecorder
{
	struct FakeUnit
	{
		int nId;
		uint32_t nClass;
		int nMode;
		uint8_t pComponents[16];
		uint8_t pComponentColors[16];
		int nFlags;
		int nFrame;
		int nX;
		int nY;
		bool bDestroyed;
	};

	static inline std::vector<std::unique_ptr<FakeUnit>> units;
	static inline std::vector<std::string> log;
	static inline std::map<const void*, std::string> names;
	// Classes for which creating a composite unit fails
	static inline std::vector<uint32_t> failingClasses;
	static inline int nFrameCount = 10;
	// Random start frames are not compared, they come from the CRT of each implementation
	static inline bool bFrameOutOfRange = false;
	static inline std::vector<Unicode> editBoxText;

	static void reset()
	{
		units.clear();
		log.clear();
		names.clear();
		failingClasses.clear();
		nFrameCount = 10;
		bFrameOutOfRange = false;
		editBoxText.clear();
	}

	// Units are numbered in creation order, so each implementation gets the same names
	static void start_run()
	{
		units.clear();
		log.clear();
		bFrameOutOfRange = false;
	}

	static std::string name(const void* p)
	{
		if (!p)
		{
			return "null";
		}
		for (const auto& unit : units)
		{
			if (unit.get() == p)
			{
				return "unit" + std::to_string(unit->nId);
			}
		}
		const auto it = names.find(p);
		return it != names.end() ? it->second : "unknown";
	}

	static int unit_id(const void* p)
	{
		for (const auto& unit : units)
		{
			if (unit.get() == p)
			{
				return unit->nId;
			}
		}
		return p ? -2 : -1;
	}

	static std::string bytes(const uint8_t* p, size_t nSize)
	{
		static const char szHex[] = "0123456789ABCDEF";
		std::string szBytes;
		for (size_t i = 0; i < nSize; ++i)
		{
			szBytes += szHex[p[i] >> 4];
			szBytes += szHex[p[i] & 0xF];
		}
		return szBytes;
	}

	static std::string narrow(const Unicode* wszText)
	{
		if (!wszText)
		{
			return "(null)";
		}
		std::string szText;
		for (; *wszText != 0; ++wszText)
		{
			const uint16_t nChar = *wszText;
			szText += nChar < 0x80 ? std::string(1, (char)nChar) : "\\u" + std::to_string(nChar);
		}
		return szText;
	}

	static FakeUnit* unit(D2CompositeUnitStrc* pUnit)
	{
		return reinterpret_cast<FakeUnit*>(pUnit);
	}

	// D2Win.#10144
	static D2CompositeUnitStrc* __stdcall CreateUnit(unsigned int nClass, int nMode, BYTE* pComponents, BYTE* pComponentColors)
	{
		const std::string szArguments = std::to_string(nClass) + " " + std::to_string(nMode) + " " + bytes(pComponents, 16) + " " + bytes(pComponentColors, 16);
		for (const uint32_t nFailingClass : failingClasses)
		{
			if (nClass == nFailingClass)
			{
				log.push_back("CreateUnit " + szArguments + " -> null");
				return nullptr;
			}
		}

		auto pUnit = std::make_unique<FakeUnit>();
		std::memset(pUnit.get(), 0, sizeof(FakeUnit));
		pUnit->nId = (int)units.size();
		pUnit->nClass = nClass;
		pUnit->nMode = nMode;
		std::memcpy(pUnit->pComponents, pComponents, 16);
		std::memcpy(pUnit->pComponentColors, pComponentColors, 16);
		units.push_back(std::move(pUnit));
		log.push_back("CreateUnit " + szArguments + " -> " + name(units.back().get()));
		return reinterpret_cast<D2CompositeUnitStrc*>(units.back().get());
	}

	// D2Win.#10145
	static void __stdcall SetUnit(D2CompositeUnitStrc* pUnit, unsigned int nClass, int nMode, BYTE* pComponents, BYTE* pComponentColors)
	{
		log.push_back("SetUnit " + name(pUnit) + " " + std::to_string(nClass) + " " + std::to_string(nMode) + " " + bytes(pComponents, 16) + " " + bytes(pComponentColors, 16));
	}

	// D2Win.#10142
	static void __stdcall DestroyUnit(D2CompositeUnitStrc* pUnit, int bUnlinkAndFree)
	{
		log.push_back("DestroyUnit " + name(pUnit) + " " + std::to_string(bUnlinkAndFree));
		if (pUnit)
		{
			unit(pUnit)->bDestroyed = true;
		}
	}

	// D2Win.#10149
	static void __stdcall Unit10149(D2CompositeUnitStrc* pUnit, uint8_t nValue)
	{
		log.push_back("10149 " + name(pUnit) + " " + std::to_string(nValue));
	}

	// D2Win.#10151, the start frame
	static void __stdcall SetFrame(D2CompositeUnitStrc* pUnit, int nFrame)
	{
		log.push_back("SetFrame " + name(pUnit));
		if (nFrame < 0 || nFrame >= (nFrameCount << 8))
		{
			bFrameOutOfRange = true;
		}
		unit(pUnit)->nFrame = nFrame;
	}

	// D2Win.#10152
	static void __stdcall SetX(D2CompositeUnitStrc* pUnit, int nX)
	{
		log.push_back("10152 " + name(pUnit) + " " + std::to_string(nX));
		unit(pUnit)->nX = nX;
	}

	// D2Win.#10153
	static void __stdcall SetY(D2CompositeUnitStrc* pUnit, int nY)
	{
		log.push_back("10153 " + name(pUnit) + " " + std::to_string(nY));
		unit(pUnit)->nY = nY;
	}

	// D2Win.#10154
	static void __stdcall SetDescription(D2CompositeUnitStrc* pUnit, const Unicode* wszUserName, const Unicode* wszCharacterName, const Unicode* wszUnk, const Unicode* wszRealmName, int nLevel, int dwProduct)
	{
		log.push_back("SetDescription " + name(pUnit) + " [" + narrow(wszUserName) + "] [" + narrow(wszCharacterName) + "] [" + narrow(wszUnk) + "] [" + narrow(wszRealmName) + "] "
			+ std::to_string(nLevel) + " " + std::to_string((uint32_t)dwProduct));
	}

	// D2Win.#10155
	static int __stdcall GetFlags(D2CompositeUnitStrc* pUnit)
	{
		return unit(pUnit)->nFlags;
	}

	// D2Win.#10156
	static void __stdcall SetFlags(D2CompositeUnitStrc* pUnit, int nFlags)
	{
		log.push_back("SetFlags " + name(pUnit) + " " + std::to_string((uint32_t)nFlags));
		unit(pUnit)->nFlags = nFlags;
	}

	// D2Win.#10169
	static int __stdcall GetFrameCount(D2CompositeUnitStrc* pUnit)
	{
		return nFrameCount;
	}

	// D2Win.#10025
	static void __fastcall SetEnabled(D2WinControlStrc* pControl, int bEnabled)
	{
		log.push_back("SetEnabled " + name(pControl) + " " + std::to_string(bEnabled));
	}

	// D2Win.#10047
	static BOOL __fastcall ClearText(D2WinTextBoxStrc* pTextBox)
	{
		log.push_back("ClearText " + name(pTextBox));
		return TRUE;
	}

	// D2Win.#10051
	static BOOL __fastcall AddLine(D2WinTextBoxStrc* pTextBox, const Unicode* wszText, int32_t nColor, char bIsWrapped, int32_t nIndent)
	{
		log.push_back("AddLine " + name(pTextBox) + " [" + narrow(wszText) + "] " + std::to_string(nColor) + " " + std::to_string((int)bIsWrapped) + " " + std::to_string(nIndent));
		return TRUE;
	}

	// D2Win.#10077
	static const Unicode* __fastcall GetEditBoxText(D2WinEditBoxStrc* pEditBox)
	{
		if (editBoxText.empty())
		{
			editBoxText.push_back(0);
		}
		return editBoxText.data();
	}
};

inline void hook_d2win_recorder(ImportHooks& hooks)
{
	const auto hook = [&hooks](WORD nOrdinal, void* pMooTarget, const void* pReplacement) { hooks.hook("D2Win.dll", nOrdinal, pMooTarget, pReplacement, false); };
	hook(10142, reinterpret_cast<void*>(&D2Win_10142_CompUnitDestroy), reinterpret_cast<const void*>(&D2WinRecorder::DestroyUnit));
	hook(10144, reinterpret_cast<void*>(&D2Win_10144), reinterpret_cast<const void*>(&D2WinRecorder::CreateUnit));
	hook(10145, reinterpret_cast<void*>(&D2Win_10145), reinterpret_cast<const void*>(&D2WinRecorder::SetUnit));
	hook(10149, reinterpret_cast<void*>(&D2Win_10149), reinterpret_cast<const void*>(&D2WinRecorder::Unit10149));
	hook(10151, reinterpret_cast<void*>(&D2Win_10151), reinterpret_cast<const void*>(&D2WinRecorder::SetFrame));
	hook(10152, reinterpret_cast<void*>(&D2Win_10152), reinterpret_cast<const void*>(&D2WinRecorder::SetX));
	hook(10153, reinterpret_cast<void*>(&D2Win_10153), reinterpret_cast<const void*>(&D2WinRecorder::SetY));
	hook(10154, reinterpret_cast<void*>(&D2Win_10154), reinterpret_cast<const void*>(&D2WinRecorder::SetDescription));
	hook(10155, reinterpret_cast<void*>(&D2Win_10155), reinterpret_cast<const void*>(&D2WinRecorder::GetFlags));
	hook(10156, reinterpret_cast<void*>(&D2Win_10156), reinterpret_cast<const void*>(&D2WinRecorder::SetFlags));
	hook(10169, reinterpret_cast<void*>(&D2Win_10169), reinterpret_cast<const void*>(&D2WinRecorder::GetFrameCount));
	hook(10025, reinterpret_cast<void*>(&CONTROL_SetEnabled), reinterpret_cast<const void*>(&D2WinRecorder::SetEnabled));
	hook(10047, reinterpret_cast<void*>(&D2Win_10047), reinterpret_cast<const void*>(&D2WinRecorder::ClearText));
	hook(10051, reinterpret_cast<void*>(&D2Win_10051), reinterpret_cast<const void*>(&D2WinRecorder::AddLine));
	hook(10077, reinterpret_cast<void*>(&D2Win_10077_EDITBOX_GetText), reinterpret_cast<const void*>(&D2WinRecorder::GetEditBoxText));
	D2WinRecorder::reset();
}

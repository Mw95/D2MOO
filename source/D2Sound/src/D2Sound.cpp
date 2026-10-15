#include <cstring>

#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>

#include "D2Sound.h"

#include <Fog.h>
#include <Window.h>

#include "D2SoundEAX.h"


static_assert(sizeof(DSCAPS) == 0x60, "DSCAPS must match the size used by the original game");
static_assert(sizeof(DSBUFFERDESC1) == 0x14, "DSBUFFERDESC1 must match the size used by the original game");


DSCAPS gDirectSoundCaps;								//D2Sound.0x6F992C38
IDirectSoundBuffer* gpEAXSoundBuffer;					//D2Sound.0x6F992C98
CRITICAL_SECTION gD2SoundCriticalSection;				//D2Sound.0x6F992C9C
IDirectSoundBuffer* gpPrimarySoundBuffer;				//D2Sound.0x6F992CB4
IKsPropertySet* gpEAXPropertySet;						//D2Sound.0x6F992CB8
IDirectSound3DBuffer* gpEAX3DBuffer;					//D2Sound.0x6F992CBC
BOOL gbSoundSystemInitialized;							//D2Sound.0x6F992CC0
IDirectSound* gpDirectSound;							//D2Sound.0x6F992CC4
BOOL gbUse3D;											//D2Sound.0x6F992CC8
BOOL gbUseEAX;											//D2Sound.0x6F992CCC
int32_t gnEAXVersion;									//D2Sound.0x6F992CD0
BOOL gbReverbOff;										//D2Sound.0x6F992CD4
BOOL sgfCriticalSectionActive;							//D2Sound.0x6F992CD8
BOOL gbDriverEnumerated;								//D2Sound.0x6F992CDC
BOOL gbBuggy3DDriver;									//D2Sound.0x6F992CE0
BOOL gbEMU10K1Driver;									//D2Sound.0x6F992CE4
BOOL gbCrystalDriver;									//D2Sound.0x6F992CE8
BOOL gbExpansion;										//D2Sound.0x6F992CEC
BOOL gbCanReuseSampleBuffers = TRUE;					//D2Sound.0x6F98F03C


// Inlined
static const char* SOUND_GetDirectSoundErrorString(HRESULT hResult)
{
	switch (hResult)
	{
	case DSERR_NOINTERFACE:
		return "DSERR_NOINTERFACE";
	case DSERR_UNSUPPORTED:
		return "DSERR_UNSUPPORTED";
	case DSERR_GENERIC:
		return "DSERR_GENERIC";
	case DSERR_NOAGGREGATION:
		return "DSERR_NOAGGREGATION";
	case DSERR_OUTOFMEMORY:
		return "DSERR_OUTOFMEMORY";
	case DSERR_INVALIDPARAM:
		return "DSERR_INVALIDPARAM";
	case DSERR_ALLOCATED:
		return "DSERR_ALLOCATED";
	case DSERR_CONTROLUNAVAIL:
		return "DSERR_CONTROLUNAVAIL";
	case DSERR_INVALIDCALL:
		return "DSERR_INVALIDCALL";
	case DSERR_PRIOLEVELNEEDED:
		return "DSERR_PRIOLEVELNEEDED";
	case DSERR_BADFORMAT:
		return "DSERR_BADFORMAT";
	case DSERR_NODRIVER:
		return "DSERR_NODRIVER";
	case DSERR_ALREADYINITIALIZED:
		return "DSERR_ALREADYINITIALIZED";
	case DSERR_BUFFERLOST:
		return "DSERR_BUFFERLOST";
	case DSERR_OTHERAPPHASPRIO:
		return "DSERR_OTHERAPPHASPRIO";
	case DSERR_UNINITIALIZED:
		return "DSERR_UNINITIALIZED";
	default:
		return nullptr;
	}
}

// Inlined
template<typename T>
static void SOUND_ReleaseInterface(T*& pInterface)
{
	if (pInterface)
	{
		pInterface->Release();
		pInterface = nullptr;
	}
}

//D2Sound.0x6F981000
static BOOL CALLBACK SOUND_DirectSoundEnumerateCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	D2_MAYBE_UNUSED(lpContext);

	// Only check the first device that is not the primary sound driver
	if (!lpGuid || gbDriverEnumerated)
	{
		return TRUE;
	}

	FOG_Trace("\tDriver: %s", lpcstrDescription);
	FOG_Trace("\tModule: %s", lpcstrModule);

	if (!strcmp(lpcstrModule, "EMU10K1.VXD"))
	{
		gbEMU10K1Driver = TRUE;
	}

	if (!strcmp(lpcstrModule, "es197x.vxd"))
	{
		gbCrystalDriver = TRUE;
	}

	if (!strcmp(lpcstrDescription, "Crystal SoundFusion(tm)"))
	{
		gbCrystalDriver = TRUE;
	}

	if (!strcmp(lpcstrModule, "YDSXG.VXD"))
	{
		gbCanReuseSampleBuffers = FALSE;
	}

	if (!strcmp(lpcstrModule, "RIPTIDE.VXD"))
	{
		gbCanReuseSampleBuffers = FALSE;
	}

	gbDriverEnumerated = TRUE;
	return TRUE;
}

//D2Sound.0x6F9810D0
BOOL __fastcall SOUND_IsExpansion()
{
	return gbExpansion;
}

//D2Sound.0x6F982260
static void __fastcall SOUND_ReleaseEAXInterfaces()
{
	SOUND_ReleaseInterface(gpEAXPropertySet);
	SOUND_ReleaseInterface(gpEAX3DBuffer);
	SOUND_ReleaseInterface(gpEAXSoundBuffer);
}

//D2Sound.0x6F982320
static BOOL __fastcall SOUND_DisableReverb(int32_t nEAXVersion)
{
	if (!gpEAXPropertySet)
	{
		return FALSE;
	}

	if (nEAXVersion == 1)
	{
		float fVolume = 0.0f;
		if (FAILED(gpEAXPropertySet->Set(DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_VOLUME, nullptr, 0, &fVolume, sizeof(fVolume))))
		{
			return FALSE;
		}
	}
	else
	{
		int32_t nRoom = EAXLISTENER_MINROOM;
		if (FAILED(gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, nullptr, 0, &nRoom, sizeof(nRoom))))
		{
			return FALSE;
		}

		if (FAILED(gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOMHF, nullptr, 0, &nRoom, sizeof(nRoom))))
		{
			return FALSE;
		}
	}

	gbReverbOff = TRUE;
	return TRUE;
}

// Inlined
static BOOL SOUND_CreateEAXInterfaces(const DSBUFFERDESC1* pBufferDesc, REFGUID guidPropertySet, ULONG nProperty)
{
	if (FAILED(gpDirectSound->CreateSoundBuffer((LPCDSBUFFERDESC)pBufferDesc, &gpEAXSoundBuffer, nullptr)))
	{
		return FALSE;
	}

	if (FAILED(gpEAXSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, (void**)&gpEAX3DBuffer)))
	{
		return FALSE;
	}

	if (FAILED(gpEAX3DBuffer->QueryInterface(IID_IKsPropertySet, (void**)&gpEAXPropertySet)))
	{
		return FALSE;
	}

	ULONG nSupport;
	if (FAILED(gpEAXPropertySet->QuerySupport(guidPropertySet, nProperty, &nSupport)))
	{
		return FALSE;
	}

	return (nSupport & (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET)) == (KSPROPERTY_SUPPORT_GET | KSPROPERTY_SUPPORT_SET);
}

//D2Sound.0x6F9812E0
static void __fastcall SOUND_InitDirectSound()
{
	if (gbUse3D && gbBuggy3DDriver)
	{
		return;
	}

	D2_ASSERT(!sgfCriticalSectionActive);
	InitializeCriticalSection(&gD2SoundCriticalSection);
	sgfCriticalSectionActive = TRUE;

	HRESULT hResult = DirectSoundCreate(nullptr, &gpDirectSound, nullptr);
	if (FAILED(hResult))
	{
		FOG_Trace("DirectSound error: %s returned on DirectSoundCreate", SOUND_GetDirectSoundErrorString(hResult));
		D2SOUND_CloseSoundSystem();
		return;
	}

	hResult = gpDirectSound->SetCooperativeLevel(WINDOW_GetWindow(), DSSCL_PRIORITY);
	if (FAILED(hResult))
	{
		FOG_Trace("DirectSound error: %s returned on SetCooperativeLevel", SOUND_GetDirectSoundErrorString(hResult));
		D2SOUND_CloseSoundSystem();
		return;
	}

	DSBUFFERDESC1 tPrimaryBufferDesc = {};
	tPrimaryBufferDesc.dwSize = sizeof(tPrimaryBufferDesc);
	tPrimaryBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	if (gbUse3D)
	{
		tPrimaryBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
	}
	tPrimaryBufferDesc.dwBufferBytes = 0;
	tPrimaryBufferDesc.lpwfxFormat = nullptr;

	hResult = gpDirectSound->CreateSoundBuffer((LPCDSBUFFERDESC)&tPrimaryBufferDesc, &gpPrimarySoundBuffer, nullptr);
	if (FAILED(hResult))
	{
		FOG_Trace("........DirectSound progress: %s returned on failed CreateSoundBuffer", SOUND_GetDirectSoundErrorString(hResult));
		D2SOUND_CloseSoundSystem();
		return;
	}

	gDirectSoundCaps.dwSize = sizeof(gDirectSoundCaps);
	hResult = gpDirectSound->GetCaps(&gDirectSoundCaps);
	if (FAILED(hResult))
	{
		FOG_Trace("........DirectSound progress: %s returned on failed GetCaps", SOUND_GetDirectSoundErrorString(hResult));
		D2SOUND_CloseSoundSystem();
		return;
	}

	constexpr uint32_t nMinHardware3DBuffers = 16;
	if (gbUse3D && gDirectSoundCaps.dwMaxHw3DAllBuffers < nMinHardware3DBuffers)
	{
		FOG_Trace("........DirectSound progress: %d buffers available is less than min needed %d buffers for 3d sound", gDirectSoundCaps.dwMaxHw3DAllBuffers, nMinHardware3DBuffers);
		D2SOUND_CloseSoundSystem();
		return;
	}

	WAVEFORMATEX tPrimaryWaveFormat = {};
	tPrimaryWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	tPrimaryWaveFormat.nChannels = 2;
	tPrimaryWaveFormat.nSamplesPerSec = 22050;
	tPrimaryWaveFormat.nAvgBytesPerSec = 88200;
	tPrimaryWaveFormat.nBlockAlign = 4;
	tPrimaryWaveFormat.wBitsPerSample = 16;
	tPrimaryWaveFormat.cbSize = 0;

	hResult = gpPrimarySoundBuffer->SetFormat(&tPrimaryWaveFormat);
	if (FAILED(hResult))
	{
		FOG_Trace("........DirectSound progress: %s returned on failed SetFormat", SOUND_GetDirectSoundErrorString(hResult));
		// The original game did not reset the pointer here, and would release the primary buffer twice.
		SOUND_ReleaseInterface(gpPrimarySoundBuffer);
		D2SOUND_CloseSoundSystem();
		return;
	}

	gnEAXVersion = 0;
	if (gbUseEAX)
	{
		WAVEFORMATEX tWaveFormat;
		UTIL_InitWaveFormat(&tWaveFormat, 1);

		DSBUFFERDESC1 tBufferDesc = {};
		tBufferDesc.dwSize = sizeof(tBufferDesc);
		tBufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_STATIC;
		tBufferDesc.dwBufferBytes = 1024;
		tBufferDesc.dwReserved = 0;
		tBufferDesc.lpwfxFormat = &tWaveFormat;

		if (SOUND_CreateEAXInterfaces(&tBufferDesc, DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ALLPARAMETERS) && SOUND_DisableReverb(2))
		{
			gnEAXVersion = 2;
		}
		else
		{
			SOUND_ReleaseEAXInterfaces();

			if (SOUND_CreateEAXInterfaces(&tBufferDesc, DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_ALL) && SOUND_DisableReverb(1))
			{
				gnEAXVersion = 1;
			}
			else
			{
				SOUND_ReleaseEAXInterfaces();

				FOG_Trace("........DirectSound progress: Unsupported EAX or EAX emulation");
				D2SOUND_CloseSoundSystem();
				return;
			}
		}
	}

	DSBCAPS tPrimaryBufferCaps = {};
	tPrimaryBufferCaps.dwSize = sizeof(tPrimaryBufferCaps);
	gpPrimarySoundBuffer->GetCaps(&tPrimaryBufferCaps);
	SAMPLE_ClearBuffer(gpPrimarySoundBuffer, 0, tPrimaryBufferCaps.dwBufferBytes);
	gpPrimarySoundBuffer->Play(0, 0, DSBPLAY_LOOPING);

	SAMPLE_StartMixerThread();
	STREAM_Initialize();
	D2SOUND_LoadSettings();
	D2SOUND_SetMasterVolume(255);

	if (gbUse3D)
	{
		if (!gbUseEAX)
		{
			FOG_Trace("\tDirectSound3D initialized");
		}
		else if (gnEAXVersion == 1)
		{
			FOG_Trace("\tDirectSound3D with EAX initialized");
		}
		else
		{
			FOG_Trace("\tDirectSound3D with EAX 2 initialized");
		}

		FOG_Trace("\tHardware 3D buffers: %i", gDirectSoundCaps.dwMaxHw3DAllBuffers);
	}

	if (gDirectSoundCaps.dwFlags & DSCAPS_EMULDRIVER)
	{
		FOG_Trace("\tDirectSound is emulated");
	}

	gbSoundSystemInitialized = TRUE;
}

// Inlined
static void SOUND_CheckBuggy3DDrivers()
{
	char szPath[MAX_PATH];
	uint32_t nMajor;
	uint32_t nMinor;
	uint32_t nBuild;

	if (gbEMU10K1Driver)
	{
		GetWindowsDirectoryA(szPath, sizeof(szPath));
		strcat(szPath, "\\SYSTEM\\EMU10K1.VXD");
		if (UTIL_GetVxdVersion(szPath, &nMajor, &nMinor, &nBuild))
		{
			FOG_Trace("\tVersion of EMU10K1.VXD driver: %i.%i.%i", nMajor, nMinor, nBuild);

			if (nMajor == 4)
			{
				if (nMinor == 6)
				{
					if (nBuild >= 622 && nBuild <= 710)
					{
						gbBuggy3DDriver = TRUE;
					}
				}
				else if (nMinor == 11)
				{
					if (nBuild >= 628 && nBuild <= 629)
					{
						gbBuggy3DDriver = TRUE;
					}
				}
			}
		}
	}

	if (gbCrystalDriver)
	{
		GetWindowsDirectoryA(szPath, sizeof(szPath));
		strcat(szPath, "\\SYSTEM\\CRLDS3D.VXD");
		if (UTIL_GetVxdVersion(szPath, &nMajor, &nMinor, &nBuild))
		{
			FOG_Trace("\tVersion of CRLDS3D.VXD driver: %i.%i.%i", nMajor, nMinor, nBuild);

			if (nMajor < 4 || (nMajor == 4 && (nMinor < 12 || (nMinor == 12 && nBuild < 1035))))
			{
				gbBuggy3DDriver = TRUE;
			}
		}
	}
}

//D2Sound.0x6F9810E0 (#10000)
#if D2_VERSION_MAJOR >= 1 && D2_VERSION_MINOR >= 13
void __fastcall D2SOUND_OpenSoundSystem(BOOL bExpansion, BOOL bSoundBackground)
{
	D2_MAYBE_UNUSED(bSoundBackground);
#else
void __fastcall D2SOUND_OpenSoundSystem(BOOL bExpansion)
{
#endif
	gbExpansion = bExpansion;

	FOG_Trace("\n----------------------------------------------\n");
	FOG_Trace("Initializing sound engine...");

	gbDriverEnumerated = FALSE;
	DirectSoundEnumerateA(SOUND_DirectSoundEnumerateCallback, nullptr);

	SOUND_CheckBuggy3DDrivers();

	// Try 3D + EAX, then 3D only, then 2D only
	if (!gbSoundSystemInitialized)
	{
		gbUse3D = TRUE;
		gbUseEAX = TRUE;
		SOUND_InitDirectSound();
	}

	if (!gbSoundSystemInitialized)
	{
		gbUse3D = TRUE;
		gbUseEAX = FALSE;
		SOUND_InitDirectSound();
	}

	if (!gbSoundSystemInitialized)
	{
		gbUse3D = FALSE;
		gbUseEAX = FALSE;
		SOUND_InitDirectSound();
	}

	if (!gbSoundSystemInitialized)
	{
		FOG_Trace("\tCouldn't initialize DirectSound");
	}

	FOG_Trace("\n----------------------------------------------\n");
}

//D2Sound.0x6F9821C0 (#10001)
void __fastcall D2SOUND_CloseSoundSystem()
{
	gbSoundSystemInitialized = FALSE;
	D2SOUND_SetMasterVolume(0);
	STREAM_Shutdown();
	SAMPLE_StopMixerThread();

	SOUND_ReleaseEAXInterfaces();
	SOUND_ReleaseInterface(gpPrimarySoundBuffer);
	SOUND_ReleaseInterface(gpDirectSound);

	if (sgfCriticalSectionActive)
	{
		DeleteCriticalSection(&gD2SoundCriticalSection);
		sgfCriticalSectionActive = FALSE;
	}
}

//D2Sound.0x6F9822B0 (#10002)
IDirectSound* __fastcall D2SOUND_GetDirectSound()
{
	return gpDirectSound;
}

//D2Sound.0x6F9822C0 (#10003)
BOOL __fastcall D2SOUND_Is3DEnabled()
{
	return gbUse3D;
}

//D2Sound.0x6F9822D0 (#10004)
BOOL __fastcall D2SOUND_IsEAXEnabled()
{
	return gbUseEAX;
}

//D2Sound.0x6F9822E0 (#10005)
BOOL __fastcall D2SOUND_10005()
{
	return FALSE;
}

//D2Sound.0x6F9822F0
int32_t __fastcall SOUND_GetEAXVersion()
{
	return gnEAXVersion;
}

//D2Sound.0x6F982300
BOOL __fastcall SOUND_IsReverbOff()
{
	return gbReverbOff;
}

//D2Sound.0x6F982310
BOOL __fastcall SOUND_CanReuseSampleBuffers()
{
	return gbCanReuseSampleBuffers;
}

//D2Sound.0x6F9823C0 (#10006)
void __fastcall D2SOUND_SetEnvironment(const D2SoundEnvironmentStrc* pEnvironment)
{
	if (!gbUseEAX || !gpEAXPropertySet)
	{
		return;
	}

	if (gnEAXVersion == 1)
	{
		float fVolume = D2SOUND_DecibelsToLinear((float)pEnvironment->lRoom);
		gpEAXPropertySet->Set(DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_ENVIRONMENT, nullptr, 0, (void*)&pEnvironment->dwEnvironment, sizeof(uint32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_VOLUME, nullptr, 0, &fVolume, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX_ReverbProperties, DSPROPERTY_EAX_DECAYTIME, nullptr, 0, (void*)&pEnvironment->flDecayTime, sizeof(float));
	}

	if (gnEAXVersion == 2)
	{
		uint32_t dwFlags = EAXLISTENERFLAGS_DECAYHFLIMIT;
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, nullptr, 0, (void*)&pEnvironment->dwEnvironment, sizeof(uint32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_FLAGS, nullptr, 0, &dwFlags, sizeof(dwFlags));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENT, nullptr, 0, (void*)&pEnvironment->dwEnvironment, sizeof(uint32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE, nullptr, 0, (void*)&pEnvironment->flEnvironmentSize, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ENVIRONMENTDIFFUSION, nullptr, 0, (void*)&pEnvironment->flEnvironmentDiffusion, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOM, nullptr, 0, (void*)&pEnvironment->lRoom, sizeof(int32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOMHF, nullptr, 0, (void*)&pEnvironment->lRoomHF, sizeof(int32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_DECAYTIME, nullptr, 0, (void*)&pEnvironment->flDecayTime, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_DECAYHFRATIO, nullptr, 0, (void*)&pEnvironment->flDecayHFRatio, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_REFLECTIONS, nullptr, 0, (void*)&pEnvironment->lReflections, sizeof(int32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_REFLECTIONSDELAY, nullptr, 0, (void*)&pEnvironment->flReflectionsDelay, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_REVERB, nullptr, 0, (void*)&pEnvironment->lReverb, sizeof(int32_t));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_REVERBDELAY, nullptr, 0, (void*)&pEnvironment->flReverbDelay, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_ROOMROLLOFFFACTOR, nullptr, 0, (void*)&pEnvironment->flRoomRolloffFactor, sizeof(float));
		gpEAXPropertySet->Set(DSPROPSETID_EAX20_ListenerProperties, DSPROPERTY_EAXLISTENER_AIRABSORPTIONHF, nullptr, 0, (void*)&pEnvironment->flAirAbsorptionHF, sizeof(float));
	}

	gbReverbOff = pEnvironment->lRoom == EAXLISTENER_MINROOM;
}

//D2Sound.0x6F9848E0 (#10067)
void __fastcall D2SOUND_10067()
{
}

//D2Sound.0x6F9848E0 (#10068)
// Same function as #10067 in the original game (identical code folding)
void __fastcall D2SOUND_10068()
{
}

// Inlined
void __fastcall SOUND_EnterCriticalSection()
{
	EnterCriticalSection(&gD2SoundCriticalSection);
}

// Inlined
void __fastcall SOUND_LeaveCriticalSection()
{
	LeaveCriticalSection(&gD2SoundCriticalSection);
}

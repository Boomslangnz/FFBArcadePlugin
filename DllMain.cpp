/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <Windows.h>
#include <math.h>
#include <dinput.h>
#include <stdio.h>
#include <tchar.h>
#include "SDL.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <thread>
#include "IDirectInputDevice.h"
#include <d3d11.h>
#include <sapi.h>
#include <atlcomcli.h>
#include <TlHelp32.h>
#include "Config/PersistentValues.h"

// include all game header files here.
#include "Game Files/TestGame.h"
#include "Game Files/AliensExtermination.h"
#include "Game Files/Batman.h"
#include "Game Files/BG4JP.h"
#include "Game Files/ChaseHQ2.h"
#include "Game Files/CrazyTaxi.h"
#include "Game Files/CruisnBlast.h"
#include "Game Files/D1GP.h"
#include "Game Files/Daytona3.h"
#include "Game Files/Daytona3NSE.h"
#include "Game Files/DeadHeat.h"
#include "Game Files/DeadHeatRiders.h"
#include "Game Files/DirtyDrivin.h"
#include "Game Files/FnF.h"
#include "Game Files/FnFDrift.h"
#include "Game Files/FnFSuperCars.h"
#include "Game Files/FordRacing.h"
#include "Game Files/FordRacingOther.h"
#include "Game Files/GaelcoTuningRace.h"
#include "Game Files/GRIDReal.h"
#include "Game Files/GRIDCustom.h"
#include "Game Files/GoldenGun.h"
#include "Game Files/HummerExtreme.h"
#include "Game Files/InitialD0v131.h"
#include "Game Files/InitialD0v211.h"
#include "Game Files/InitialD0v230.h"
#include "Game Files/InitialD4.h"
#include "Game Files/InitialD4Japan.h"
#include "Game Files/InitialD5.h"
#include "Game Files/InitialD6.h"
#include "Game Files/InitialD7.h"
#include "Game Files/InitialD8.h"
#include "Game Files/IDTAv231.h"
#include "Game Files/MarioKartGPDXCustom.h"
#include "Game Files/MarioKartGPDX1.10Custom.h"
#include "Game Files/MarioKartGPDX1.10Real.h"
#include "Game Files/MarioKartGPDX1.18Custom.h"
#include "Game Files/MarioKartGPDX1.18Real.h"
#include "Game Files/MarioKartGPDXUSACustom.h"
#include "Game Files/MarioKartGPDXUSAReal.h"
#include "Game Files/MAMESupermodel.h"
#include "Game Files/OutRun2Fake.h"
#include "Game Files/OutRun2Real.h"
#include "Game Files/SegaRaceTV.h"
#include "Game Files/SegaRacingClassic.h"
#include "Game Files/SegaRally3.h"
#include "Game Files/SegaRally3Other.h"
#include "Game Files/Showdown.h"
#include "Game Files/SnoCross.h"
#include "Game Files/WackyRaces.h"
#include "Game Files/WastelandRacers2071.h"
#include "Game Files/WMMT3.h"
#include "Game Files/WMMT5.h"
#include "Game Files/WMMT5DX.h"
#include "Game Files/WMMT5DX+.h"
#include "Game Files/WMMT6.h"
#include "Game Files/WMMT6R.h"
#include "Game Files/WMMT6RR.h"
#include "Game Files/Machstorm.h"
#include "Game Files/AfterburnerClimax.h"
#include "Game Files/PokkenTournament.h"
#include "Game Files/SonicSegaAllStarsRacing.h"
#include "Game Files/SpringEffect.h"
#include "Game Files/M2Emulator.h"
#include "Game Files/GTIClub3.h"
#include "Game Files/Demul.h"
#include "Game Files/ButtonRumble.h"
#include "Game Files/RingRiders.h"
#include "Game Files/RoadFighters3D.h"
#include "Game Files/LGI3D.h"
#include "Game Files/LGI.h"
#include "Game Files/KODrive.h"
#include "Game Files/HOTD4.h"
#include "Game Files/Rambo.h"
#include "Game Files/R-Tuned.h"
#include "Game Files/SWDC2018.h"
#include "Game Files/TokyoCop.h"
#include "Game Files/Transformers.h"
#include "Game Files/H2Overdrive.h"
#include "Game Files/StormRacerG.h"
#include "Game Files/ArcticThunder.h"

// typedefs 
typedef unsigned char U8;
typedef unsigned int U32;

// DINPUT8 FUNCTION DEFINITIONS
typedef HRESULT(WINAPI* pfnDirectInputDirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
typedef HRESULT(WINAPI* pfnDirectInputDllRegisterServer)(void);
typedef HRESULT(WINAPI* pfnDirectInputDllUnregisterServer)(void);
typedef HRESULT(WINAPI* pfnDirectInputDllCanUnloadNow)(void);
typedef HRESULT(WINAPI* pfnDirectInputDllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
typedef LPCDIDATAFORMAT(WINAPI* pfnDirectInputGetdfDIJoystick)();

// DINPUT FUNCTION DEFINITIONS
typedef HRESULT(WINAPI* pfnDirectInputDirectInputCreateA)(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA* ppDI, LPUNKNOWN punkOuter);
typedef HRESULT(WINAPI* pfnDirectInputDirectInputCreateW)(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTW* ppDI, LPUNKNOWN punkOuter);
typedef HRESULT(WINAPI* pfnDirectInputDirectInputCreateEx)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

// DINPUT8 REAL FUNCTIONS
pfnDirectInputDirectInput8Create originalDirectInputDirectInput8Create = NULL;
pfnDirectInputDllRegisterServer originalDirectInputDllRegisterServer = NULL;
pfnDirectInputDllUnregisterServer originalDirectInputDllUnregisterServer = NULL;
pfnDirectInputDllCanUnloadNow originalDirectInputDllCanUnloadNow = NULL;
pfnDirectInputDllGetClassObject originalDirectInputDllGetClassObject = NULL;
pfnDirectInputGetdfDIJoystick originalGetdfDIJoystick = NULL;

// DINPUT REAL FUNCTIONS
pfnDirectInputDirectInputCreateA originalDirectInputDirectInputCreateA = NULL;
pfnDirectInputDirectInputCreateW originalDirectInputDirectInputCreateW = NULL;
pfnDirectInputDirectInputCreateEx originalDirectInputDirectInputCreateEx = NULL;

// DX11 REAL FUNCTIONS
extern "C"
{
	FARPROC originalCreateDirect3D11DeviceFromDXGIDevice;
	FARPROC originalCreateDirect3D11SurfaceFromDXGISurface;
	FARPROC originalD3D11CoreCreateDevice;
	FARPROC originalD3D11CoreCreateLayeredDevice;
	FARPROC originalD3D11CoreGetLayeredDeviceSize;
	FARPROC originalD3D11CoreRegisterLayers;
	FARPROC originalD3D11CreateDevice;
	FARPROC originalD3D11CreateDeviceAndSwapChain;
	FARPROC originalD3D11CreateDeviceForD3D12;
	FARPROC originalD3D11On12CreateDevice;
	FARPROC originalD3DKMTCloseAdapter;
	FARPROC originalD3DKMTCreateAllocation;
	FARPROC originalD3DKMTCreateContext;
	FARPROC originalD3DKMTCreateDevice;
	FARPROC originalD3DKMTCreateSynchronizationObject;
	FARPROC originalD3DKMTDestroyAllocation;
	FARPROC originalD3DKMTDestroyContext;
	FARPROC originalD3DKMTDestroyDevice;
	FARPROC originalD3DKMTDestroySynchronizationObject;
	FARPROC originalD3DKMTEscape;
	FARPROC originalD3DKMTGetContextSchedulingPriority;
	FARPROC originalD3DKMTGetDeviceState;
	FARPROC originalD3DKMTGetDisplayModeList;
	FARPROC originalD3DKMTGetMultisampleMethodList;
	FARPROC originalD3DKMTGetRuntimeData;
	FARPROC originalD3DKMTGetSharedPrimaryHandle;
	FARPROC originalD3DKMTLock;
	FARPROC originalD3DKMTOpenAdapterFromHdc;
	FARPROC originalD3DKMTOpenResource;
	FARPROC originalD3DKMTPresent;
	FARPROC originalD3DKMTQueryAdapterInfo;
	FARPROC originalD3DKMTQueryAllocationResidency;
	FARPROC originalD3DKMTQueryResourceInfo;
	FARPROC originalD3DKMTRender;
	FARPROC originalD3DKMTSetAllocationPriority;
	FARPROC originalD3DKMTSetContextSchedulingPriority;
	FARPROC originalD3DKMTSetDisplayMode;
	FARPROC originalD3DKMTSetDisplayPrivateDriverFormat;
	FARPROC originalD3DKMTSetGammaRamp;
	FARPROC originalD3DKMTSetVidPnSourceOwner;
	FARPROC originalD3DKMTSignalSynchronizationObject;
	FARPROC originalD3DKMTUnlock;
	FARPROC originalD3DKMTWaitForSynchronizationObject;
	FARPROC originalD3DKMTWaitForVerticalBlankEvent;
	FARPROC originalD3DPerformance_BeginEvent;
	FARPROC originalD3DPerformance_EndEvent;
	FARPROC originalD3DPerformance_GetStatus;
	FARPROC originalD3DPerformance_SetMarker;
	FARPROC originalEnableFeatureLevelUpgrade;
	FARPROC originalOpenAdapter10;
	FARPROC originalOpenAdapter10_2;
}

// XINPUT1_3 REAL FUNCTIONS
extern "C"
{
	FARPROC originalXInputGetState;
	FARPROC originalXInputSetState;
	FARPROC originalXInputGetCapabilities;
	FARPROC originalXInputEnable;
	FARPROC originalXInputGetDSoundAudioDeviceGuids;
	FARPROC originalXInputGetBatteryInformation;
	FARPROC originalXInputGetKeystroke;
	FARPROC originalXInputGetStateEx;
	FARPROC originalXInputWaitForGuideButton;
	FARPROC originalXInputCancelGuideButtonWait;
	FARPROC originalXInputPowerOffController;
}

// D3D9 REAL FUNCTIONS
extern "C"
{
	FARPROC originalDirect3DShaderValidatorCreate9;
	FARPROC originalPSGPError;
	FARPROC originalPSGPSampleTexture;
	FARPROC originalD3DPERF_BeginEvent;
	FARPROC originalD3DPERF_EndEvent;
	FARPROC originalD3DPERF_GetStatus;
	FARPROC originalD3DPERF_QueryRepeatFrame;
	FARPROC originalD3DPERF_SetMarker;
	FARPROC originalD3DPERF_SetOptions;
	FARPROC originalD3DPERF_SetRegion;
	FARPROC originalDebugSetLevel;
	FARPROC originalDebugSetMute;
	FARPROC originalDirect3D9EnableMaximizedWindowedModeShim;
	FARPROC originalDirect3DCreate9;
	FARPROC originalDirect3DCreate9Ex;
}

// WINMM REAL FUNCTIONS
extern "C"
{
	FARPROC	originalPlaySoundW;
	FARPROC	originaltimeSetEvent;
	FARPROC	originaltimeKillEvent;
	FARPROC originalmidiOutMessage;
	FARPROC	originaltimeBeginPeriod;
	FARPROC	originaltimeGetTime;
	FARPROC	originalNotifyCallbackData;
	FARPROC	originalWOW32DriverCallback;
	FARPROC	originalWOW32ResolveMultiMediaHandle;
	FARPROC	originalaux32Message;
	FARPROC	originaljoy32Message;
	FARPROC	originalmid32Message;
	FARPROC	originalmod32Message;
	FARPROC	originalmxd32Message;
	FARPROC	originaltid32Message;
	FARPROC	originalwid32Message;
	FARPROC	originalwod32Message;
	FARPROC	originalmci32Message;
	FARPROC	originalCloseDriver;
	FARPROC	originalDefDriverProc;
	FARPROC	originalDriverCallback;
	FARPROC	originalDrvGetModuleHandle;
	FARPROC	originalGetDriverModuleHandle;
	FARPROC	originalOpenDriver;
	FARPROC	originalPlaySound;
	FARPROC	originalOrdinal2;
	FARPROC	originalSendDriverMessage;
	FARPROC	originalauxGetDevCapsA;
	FARPROC	originalauxGetDevCapsW;
	FARPROC	originalauxGetNumDevs;
	FARPROC	originalauxGetVolume;
	FARPROC	originalauxOutMessage;
	FARPROC	originalauxSetVolume;
	FARPROC	originaljoyConfigChanged;
	FARPROC	originaljoyGetDevCapsA;
	FARPROC	originaljoyGetDevCapsW;
	FARPROC	originaljoyGetNumDevs;
	FARPROC	originaljoyGetPosEx;
	FARPROC	originaljoyGetPos;
	FARPROC	originaljoyGetThreshold;
	FARPROC	originaljoyReleaseCapture;
	FARPROC	originaljoySetCapture;
	FARPROC	originaljoySetThreshold;
	FARPROC	originalmidiConnect;
	FARPROC	originalmidiDisconnect;
	FARPROC	originalmidiInAddBuffer;
	FARPROC	originalmidiInClose;
	FARPROC	originalmidiInGetDevCapsA;
	FARPROC	originalmidiInGetDevCapsW;
	FARPROC	originalmidiInGetErrorTextA;
	FARPROC	originalmidiInGetErrorTextW;
	FARPROC	originalmidiInGetID;
	FARPROC	originalmidiInGetNumDevs;
	FARPROC	originalmidiInMessage;
	FARPROC	originalmidiInOpen;
	FARPROC	originalmidiInPrepareHeader;
	FARPROC	originalmidiInReset;
	FARPROC	originalmidiInStart;
	FARPROC	originalmidiInStop;
	FARPROC	originalmidiInUnprepareHeader;
	FARPROC	originalmidiOutCacheDrumPatches;
	FARPROC	originalmidiOutCachePatches;
	FARPROC originalmidiOutClose;
	FARPROC	originalmidiOutGetDevCapsA;
	FARPROC	originalmidiOutGetDevCapsW;
	FARPROC	originalmidiOutGetErrorTextA;
	FARPROC	originalmidiOutGetErrorTextW;
	FARPROC	originalmidiOutGetID;
	FARPROC	originalmidiOutGetNumDevs;
	FARPROC	originalmidiOutGetVolume;
	FARPROC	originalmidiOutLongMsg;
	FARPROC	originalmidiOutOpen;
	FARPROC	originalmidiOutPrepareHeader;
	FARPROC	originalmidiOutReset;
	FARPROC	originalmidiOutSetVolume;
	FARPROC	originalmidiOutShortMsg;
	FARPROC	originalmidiOutUnprepareHeader;
	FARPROC	originalmidiStreamClose;
	FARPROC	originalmidiStreamOpen;
	FARPROC	originalmidiStreamOut;
	FARPROC	originalmidiStreamPause;
	FARPROC	originalmidiStreamPosition;
	FARPROC	originalmidiStreamProperty;
	FARPROC	originalmidiStreamRestart;
	FARPROC	originalmidiStreamStop;
	FARPROC	originalmixerClose;
	FARPROC	originalmixerGetControlDetailsA;
	FARPROC	originalmixerGetControlDetailsW;
	FARPROC	originalmixerGetDevCapsA;
	FARPROC	originalmixerGetDevCapsW;
	FARPROC	originalmixerGetID;
	FARPROC	originalmixerGetLineControlsA;
	FARPROC	originalmixerGetLineControlsW;
	FARPROC	originalmixerGetLineInfoA;
	FARPROC	originalmixerGetLineInfoW;
	FARPROC	originalmixerGetNumDevs;
	FARPROC	originalmixerMessage;
	FARPROC	originalmixerOpen;
	FARPROC	originalmixerSetControlDetails;
	FARPROC	originalmmDrvInstall;
	FARPROC	originalmmGetCurrentTask;
	FARPROC	originalmmTaskBlock;
	FARPROC	originalmmTaskCreate;
	FARPROC	originalmmTaskSignal;
	FARPROC	originalmmTaskYield;
	FARPROC	originalmmioAdvance;
	FARPROC	originalmmioAscend;
	FARPROC	originalmmioClose;
	FARPROC originalmmioCreateChunk;
	FARPROC	originalmmioDescend;
	FARPROC originalmmioFlush;
	FARPROC	originalmmioGetInfo;
	FARPROC	originalmmioInstallIOProcA;
	FARPROC	originalmmioInstallIOProcW;
	FARPROC	originalmmioOpenA;
	FARPROC	originalmmioOpenW;
	FARPROC	originalmmioRead;
	FARPROC	originalmmioRenameA;
	FARPROC	originalmmioRenameW;
	FARPROC originalmmioSeek;
	FARPROC	originalmmioSendMessage;
	FARPROC	originalmmioSetBuffer;
	FARPROC	originalmmioSetInfo;
	FARPROC	originalmmioStringToFOURCCA;
	FARPROC	originalmmioStringToFOURCCW;
	FARPROC	originalmmioWrite;
	FARPROC	originaltimeEndPeriod;
	FARPROC	originaltimeGetDevCaps;
	FARPROC	originaltimeGetSystemTime;
	FARPROC	originalwaveInAddBuffer;
	FARPROC	originalwaveInClose;
	FARPROC	originalwaveInGetDevCapsA;
	FARPROC	originalwaveInGetDevCapsW;
	FARPROC	originalwaveInGetErrorTextA;
	FARPROC	originalwaveInGetErrorTextW;
	FARPROC	originalwaveInGetID;
	FARPROC	originalwaveInGetNumDevs;
	FARPROC	originalwaveInGetPosition;
	FARPROC	originalwaveInMessage;
	FARPROC	originalwaveInOpen;
	FARPROC	originalwaveInPrepareHeader;
	FARPROC	originalwaveInReset;
	FARPROC	originalwaveInStart;
	FARPROC	originalwaveInStop;
	FARPROC	originalwaveInUnprepareHeader;
	FARPROC	originalwaveOutBreakLoop;
	FARPROC	originalwaveOutClose;
	FARPROC	originalwaveOutGetDevCapsA;
	FARPROC	originalwaveOutGetDevCapsW;
	FARPROC	originalwaveOutGetErrorTextA;
	FARPROC	originalwaveOutGetErrorTextW;
	FARPROC	originalwaveOutGetID;
	FARPROC	originalwaveOutGetNumDevs;
	FARPROC	originalwaveOutGetPitch;
	FARPROC	originalwaveOutGetPlaybackRate;
	FARPROC	originalwaveOutGetPosition;
	FARPROC	originalwaveOutGetVolume;
	FARPROC	originalwaveOutMessage;
	FARPROC	originalwaveOutOpen;
	FARPROC	originalwaveOutPause;
	FARPROC	originalwaveOutPrepareHeader;
	FARPROC	originalwaveOutReset;
	FARPROC	originalwaveOutRestart;
	FARPROC	originalwaveOutSetPitch;
	FARPROC	originalwaveOutSetPlaybackRate;
	FARPROC	originalwaveOutSetVolume;
	FARPROC	originalwaveOutUnprepareHeader;
	FARPROC	originalwaveOutWrite;
	FARPROC	originalmciExecute;
	FARPROC	originalmciGetErrorStringA;
	FARPROC	originalmciGetErrorStringW;
	FARPROC	originalmciSendCommandA;
	FARPROC	originalmciSendCommandW;
	FARPROC	originalmciSendStringA;
	FARPROC	originalmciSendStringW;
	FARPROC	originalmciFreeCommandResource;
	FARPROC	originalmciLoadCommandResource;
	FARPROC	originalmciDriverNotify;
	FARPROC	originalmciDriverYield;
	FARPROC	originalmciGetCreatorTask;
	FARPROC	originalmciGetDeviceIDA;
	FARPROC originalmciGetDeviceIDFromElementIDA;
	FARPROC	originalmciGetDeviceIDFromElementIDW;
	FARPROC	originalmciGetDeviceIDW;
	FARPROC	originalmciGetDriverData;
	FARPROC	originalmciGetYieldProc;
	FARPROC	originalmciSetDriverData;
	FARPROC	originalmciSetYieldProc;
	FARPROC	originalPlaySoundA;
	FARPROC	originalsndPlaySoundA;
	FARPROC	originalsndPlaySoundW;
	FARPROC	originalWOWAppExit;
	FARPROC	originalmmsystemGetVersion;
}

// OpenGL32 REAL FUNCTIONS
extern "C"
{
	FARPROC originalwglUseFontOutlinesA;
	FARPROC originalwglUseFontOutlinesW;
	FARPROC originalwglDescribeLayerPlane;
	FARPROC originalwglSetLayerPaletteEntries;
	FARPROC originalwglGetLayerPaletteEntries;
	FARPROC originalwglRealizeLayerPalette;
	FARPROC originalwglSwapLayerBuffers;
	FARPROC originalwglMakeCurrent;
	FARPROC originalGlmfInitPlayback;
	FARPROC originalGlmfBeginGlsBlock;
	FARPROC originalGlmfPlayGlsRecord;
	FARPROC originalGlmfEndGlsBlock;
	FARPROC originalGlmfEndPlayback;
	FARPROC originalGlmfCloseMetaFile;
	FARPROC originalwglSwapMultipleBuffers;
	FARPROC originalwglCreateLayerContext;
	FARPROC originalwglCreateContext;
	FARPROC originalwglDeleteContext;
	FARPROC originalwglGetCurrentContext;
	FARPROC originalwglGetCurrentDC;
	FARPROC originalwglUseFontBitmapsA;
	FARPROC originalwglUseFontBitmapsW;
	FARPROC originalwglShareLists;
	FARPROC originalwglGetDefaultProcAddress;
	FARPROC originalwglGetProcAddress;
	FARPROC originalwglCopyContext;
	FARPROC originalglDebugEntry;
	FARPROC originalwglGetPixelFormat;
	FARPROC originalwglSetPixelFormat;
	FARPROC originalwglChoosePixelFormat;
	FARPROC originalwglDescribePixelFormat;
	FARPROC originalwglSwapBuffers;
	FARPROC originalglNewList;
	FARPROC originalglEndList;
	FARPROC originalglCallList;
	FARPROC originalglCallLists;
	FARPROC originalglBegin;
	FARPROC originalglColor3b;
	FARPROC originalglColor3bv;
	FARPROC originalglColor3d;
	FARPROC originalglColor3dv;
	FARPROC originalglColor3f;
	FARPROC originalglColor3fv;
	FARPROC originalglColor3i;
	FARPROC originalglColor3iv;
	FARPROC originalglColor3s;
	FARPROC originalglColor3sv;
	FARPROC originalglColor3ub;
	FARPROC originalglColor3ubv;
	FARPROC originalglColor3ui;
	FARPROC originalglColor3uiv;
	FARPROC originalglColor3us;
	FARPROC originalglColor3usv;
	FARPROC originalglColor4b;
	FARPROC originalglColor4bv;
	FARPROC originalglColor4d;
	FARPROC originalglColor4dv;
	FARPROC originalglColor4f;
	FARPROC originalglColor4fv;
	FARPROC originalglColor4i;
	FARPROC originalglColor4iv;
	FARPROC originalglColor4s;
	FARPROC originalglColor4sv;
	FARPROC originalglColor4ub;
	FARPROC originalglColor4ubv;
	FARPROC originalglColor4ui;
	FARPROC originalglColor4uiv;
	FARPROC originalglColor4us;
	FARPROC originalglColor4usv;
	FARPROC originalglEdgeFlag;
	FARPROC originalglEdgeFlagv;
	FARPROC originalglEnd;
	FARPROC originalglIndexd;
	FARPROC originalglIndexdv;
	FARPROC originalglIndexf;
	FARPROC originalglIndexfv;
	FARPROC originalglIndexi;
	FARPROC originalglIndexiv;
	FARPROC originalglIndexs;
	FARPROC originalglIndexsv;
	FARPROC originalglNormal3b;
	FARPROC originalglNormal3bv;
	FARPROC originalglNormal3d;
	FARPROC originalglNormal3dv;
	FARPROC originalglNormal3f;
	FARPROC originalglNormal3fv;
	FARPROC originalglNormal3i;
	FARPROC originalglNormal3iv;
	FARPROC originalglNormal3s;
	FARPROC originalglNormal3sv;
	FARPROC originalglTexCoord1d;
	FARPROC originalglTexCoord1dv;
	FARPROC originalglTexCoord1f;
	FARPROC originalglTexCoord1fv;
	FARPROC originalglTexCoord1i;
	FARPROC originalglTexCoord1iv;
	FARPROC originalglTexCoord1s;
	FARPROC originalglTexCoord1sv;
	FARPROC originalglTexCoord2d;
	FARPROC originalglTexCoord2dv;
	FARPROC originalglTexCoord2f;
	FARPROC originalglTexCoord2fv;
	FARPROC originalglTexCoord2i;
	FARPROC originalglTexCoord2iv;
	FARPROC originalglTexCoord2s;
	FARPROC originalglTexCoord2sv;
	FARPROC originalglTexCoord3d;
	FARPROC originalglTexCoord3dv;
	FARPROC originalglTexCoord3f;
	FARPROC originalglTexCoord3fv;
	FARPROC originalglTexCoord3i;
	FARPROC originalglTexCoord3iv;
	FARPROC originalglTexCoord3s;
	FARPROC originalglTexCoord3sv;
	FARPROC originalglTexCoord4d;
	FARPROC originalglTexCoord4dv;
	FARPROC originalglTexCoord4f;
	FARPROC originalglTexCoord4fv;
	FARPROC originalglTexCoord4i;
	FARPROC originalglTexCoord4iv;
	FARPROC originalglTexCoord4s;
	FARPROC originalglTexCoord4sv;
	FARPROC originalglVertex2d;
	FARPROC originalglVertex2dv;
	FARPROC originalglVertex2f;
	FARPROC originalglVertex2fv;
	FARPROC originalglVertex2i;
	FARPROC originalglVertex2iv;
	FARPROC originalglVertex2s;
	FARPROC originalglVertex2sv;
	FARPROC originalglVertex3d;
	FARPROC originalglVertex3dv;
	FARPROC originalglVertex3f;
	FARPROC originalglVertex3fv;
	FARPROC originalglVertex3i;
	FARPROC originalglVertex3iv;
	FARPROC originalglVertex3s;
	FARPROC originalglVertex3sv;
	FARPROC originalglVertex4d;
	FARPROC originalglVertex4dv;
	FARPROC originalglVertex4f;
	FARPROC originalglVertex4fv;
	FARPROC originalglVertex4i;
	FARPROC originalglVertex4iv;
	FARPROC originalglVertex4s;
	FARPROC originalglVertex4sv;
	FARPROC originalglMaterialf;
	FARPROC originalglMaterialfv;
	FARPROC originalglMateriali;
	FARPROC originalglMaterialiv;
	FARPROC originalglDisable;
	FARPROC originalglEnable;
	FARPROC originalglPopAttrib;
	FARPROC originalglPushAttrib;
	FARPROC originalglEvalCoord1d;
	FARPROC originalglEvalCoord1dv;
	FARPROC originalglEvalCoord1f;
	FARPROC originalglEvalCoord1fv;
	FARPROC originalglEvalCoord2d;
	FARPROC originalglEvalCoord2dv;
	FARPROC originalglEvalCoord2f;
	FARPROC originalglEvalCoord2fv;
	FARPROC originalglEvalPoint1;
	FARPROC originalglEvalPoint2;
	FARPROC originalglLoadIdentity;
	FARPROC originalglLoadMatrixf;
	FARPROC originalglLoadMatrixd;
	FARPROC originalglMatrixMode;
	FARPROC originalglMultMatrixf;
	FARPROC originalglMultMatrixd;
	FARPROC originalglPopMatrix;
	FARPROC originalglPushMatrix;
	FARPROC originalglRotated;
	FARPROC originalglRotatef;
	FARPROC originalglScaled;
	FARPROC originalglScalef;
	FARPROC originalglTranslated;
	FARPROC originalglTranslatef;
	FARPROC originalglArrayElement;
	FARPROC originalglBindTexture;
	FARPROC originalglColorPointer;
	FARPROC originalglDisableClientState;
	FARPROC originalglDrawArrays;
	FARPROC originalglDrawElements;
	FARPROC originalglEdgeFlagPointer;
	FARPROC originalglEnableClientState;
	FARPROC originalglIndexPointer;
	FARPROC originalglIndexub;
	FARPROC originalglIndexubv;
	FARPROC originalglInterleavedArrays;
	FARPROC originalglNormalPointer;
	FARPROC originalglPolygonOffset;
	FARPROC originalglTexCoordPointer;
	FARPROC originalglVertexPointer;
	FARPROC originalglGetPointerv;
	FARPROC originalglPopClientAttrib;
	FARPROC originalglPushClientAttrib;
	FARPROC originalglClear;
	FARPROC originalglClearAccum;
	FARPROC originalglClearIndex;
	FARPROC originalglClearColor;
	FARPROC originalglClearStencil;
	FARPROC originalglClearDepth;
	FARPROC originalglBitmap;
	FARPROC originalglTexImage1D;
	FARPROC originalglTexImage2D;
	FARPROC originalglCopyPixels;
	FARPROC originalglReadPixels;
	FARPROC originalglDrawPixels;
	FARPROC originalglRectd;
	FARPROC originalglRectdv;
	FARPROC originalglRectf;
	FARPROC originalglRectfv;
	FARPROC originalglRecti;
	FARPROC originalglRectiv;
	FARPROC originalglRects;
	FARPROC originalglRectsv;
	FARPROC originalglDeleteLists;
	FARPROC originalglGenLists;
	FARPROC originalglListBase;
	FARPROC originalglRasterPos2d;
	FARPROC originalglRasterPos2dv;
	FARPROC originalglRasterPos2f;
	FARPROC originalglRasterPos2fv;
	FARPROC originalglRasterPos2i;
	FARPROC originalglRasterPos2iv;
	FARPROC originalglRasterPos2s;
	FARPROC originalglRasterPos2sv;
	FARPROC originalglRasterPos3d;
	FARPROC originalglRasterPos3dv;
	FARPROC originalglRasterPos3f;
	FARPROC originalglRasterPos3fv;
	FARPROC originalglRasterPos3i;
	FARPROC originalglRasterPos3iv;
	FARPROC originalglRasterPos3s;
	FARPROC originalglRasterPos3sv;
	FARPROC originalglRasterPos4d;
	FARPROC originalglRasterPos4dv;
	FARPROC originalglRasterPos4f;
	FARPROC originalglRasterPos4fv;
	FARPROC originalglRasterPos4i;
	FARPROC originalglRasterPos4iv;
	FARPROC originalglRasterPos4s;
	FARPROC originalglRasterPos4sv;
	FARPROC originalglClipPlane;
	FARPROC originalglColorMaterial;
	FARPROC originalglCullFace;
	FARPROC originalglFogf;
	FARPROC originalglFogfv;
	FARPROC originalglFogi;
	FARPROC originalglFogiv;
	FARPROC originalglFrontFace;
	FARPROC originalglHint;
	FARPROC originalglLightf;
	FARPROC originalglLightfv;
	FARPROC originalglLighti;
	FARPROC originalglLightiv;
	FARPROC originalglLightModelf;
	FARPROC originalglLightModelfv;
	FARPROC originalglLightModeli;
	FARPROC originalglLightModeliv;
	FARPROC originalglLineStipple;
	FARPROC originalglLineWidth;
	FARPROC originalglPointSize;
	FARPROC originalglPolygonMode;
	FARPROC originalglPolygonStipple;
	FARPROC originalglScissor;
	FARPROC originalglFinish;
	FARPROC originalglShadeModel;
	FARPROC originalglTexParameterf;
	FARPROC originalglTexParameterfv;
	FARPROC originalglTexParameteri;
	FARPROC originalglTexParameteriv;
	FARPROC originalglTexEnvf;
	FARPROC originalglTexEnvfv;
	FARPROC originalglTexEnvi;
	FARPROC originalglTexEnviv;
	FARPROC originalglTexGend;
	FARPROC originalglTexGendv;
	FARPROC originalglTexGenf;
	FARPROC originalglTexGenfv;
	FARPROC originalglTexGeni;
	FARPROC originalglTexGeniv;
	FARPROC originalglFeedbackBuffer;
	FARPROC originalglSelectBuffer;
	FARPROC originalglRenderMode;
	FARPROC originalglInitNames;
	FARPROC originalglLoadName;
	FARPROC originalglPassThrough;
	FARPROC originalglPopName;
	FARPROC originalglPushName;
	FARPROC originalglDrawBuffer;
	FARPROC originalglStencilMask;
	FARPROC originalglColorMask;
	FARPROC originalglDepthMask;
	FARPROC originalglIndexMask;
	FARPROC originalglAccum;
	FARPROC originalglFlush;
	FARPROC originalglMap1d;
	FARPROC originalglMap1f;
	FARPROC originalglMap2d;
	FARPROC originalglMap2f;
	FARPROC originalglMapGrid1d;
	FARPROC originalglMapGrid1f;
	FARPROC originalglMapGrid2d;
	FARPROC originalglMapGrid2f;
	FARPROC originalglEvalMesh1;
	FARPROC originalglEvalMesh2;
	FARPROC originalglAlphaFunc;
	FARPROC originalglBlendFunc;
	FARPROC originalglLogicOp;
	FARPROC originalglStencilFunc;
	FARPROC originalglStencilOp;
	FARPROC originalglDepthFunc;
	FARPROC originalglPixelZoom;
	FARPROC originalglPixelTransferf;
	FARPROC originalglPixelTransferi;
	FARPROC originalglPixelStoref;
	FARPROC originalglPixelStorei;
	FARPROC originalglPixelMapfv;
	FARPROC originalglPixelMapuiv;
	FARPROC originalglPixelMapusv;
	FARPROC originalglReadBuffer;
	FARPROC originalglGetBooleanv;
	FARPROC originalglGetClipPlane;
	FARPROC originalglGetDoublev;
	FARPROC originalglGetError;
	FARPROC originalglGetFloatv;
	FARPROC originalglGetIntegerv;
	FARPROC originalglGetLightfv;
	FARPROC originalglGetLightiv;
	FARPROC originalglGetMapdv;
	FARPROC originalglGetMapfv;
	FARPROC originalglGetMapiv;
	FARPROC originalglGetMaterialfv;
	FARPROC originalglGetMaterialiv;
	FARPROC originalglGetPixelMapfv;
	FARPROC originalglGetPixelMapuiv;
	FARPROC originalglGetPixelMapusv;
	FARPROC originalglGetPolygonStipple;
	FARPROC originalglGetString;
	FARPROC originalglGetTexEnvfv;
	FARPROC originalglGetTexEnviv;
	FARPROC originalglGetTexGendv;
	FARPROC originalglGetTexGenfv;
	FARPROC originalglGetTexGeniv;
	FARPROC originalglGetTexImage;
	FARPROC originalglGetTexParameterfv;
	FARPROC originalglGetTexParameteriv;
	FARPROC originalglGetTexLevelParameterfv;
	FARPROC originalglGetTexLevelParameteriv;
	FARPROC originalglIsEnabled;
	FARPROC originalglIsList;
	FARPROC originalglDepthRange;
	FARPROC originalglFrustum;
	FARPROC originalglOrtho;
	FARPROC originalglViewport;
	FARPROC originalglAreTexturesResident;
	FARPROC originalglCopyTexImage1D;
	FARPROC originalglCopyTexImage2D;
	FARPROC originalglCopyTexSubImage1D;
	FARPROC originalglCopyTexSubImage2D;
	FARPROC originalglDeleteTextures;
	FARPROC originalglGenTextures;
	FARPROC originalglIsTexture;
	FARPROC originalglPrioritizeTextures;
	FARPROC originalglTexSubImage1D;
	FARPROC originalglTexSubImage2D;
}

// SUPPORT FOR WRAPPING DIFFERENT LIBRARIES

enum lib
{
	unknown = 0,
	dinput8,
	d3d11,
	xinput1_3,
	d3d9,
	opengl32,
	winmm,
	dinput
};

lib currentLibrary = lib::unknown;

// DINPUT WRAPPER
HRESULT WINAPI DirectInputDirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA* ppDI, LPUNKNOWN punkOuter)
{
	HRESULT res = originalDirectInputDirectInputCreateA(hinst, dwVersion, ppDI, punkOuter);
	return res;
}
HRESULT WINAPI DirectInputDirectInputCreateW(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTW* ppDI, LPUNKNOWN punkOuter)
{
	HRESULT res = originalDirectInputDirectInputCreateW(hinst, dwVersion, ppDI, punkOuter);
	return res;
}
HRESULT WINAPI DirectInputDirectInputCreateEx(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	HRESULT res = originalDirectInputDirectInputCreateEx(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	return res;
}
// DINPUT8 WRAPPER
HRESULT WINAPI DirectInputDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	LPVOID val;
	HRESULT res = originalDirectInputDirectInput8Create(hinst, dwVersion, riidltf, &val, punkOuter);
	*ppvOut = new DirectInputDeviceWrapper(val, (IID_IDirectInput8W == riidltf));
	return res;
}

HRESULT WINAPI DirectInputDllRegisterServer(void)
{
	return originalDirectInputDllRegisterServer();
}

HRESULT WINAPI DirectInputDllUnregisterServer(void)
{
	return originalDirectInputDllUnregisterServer();
}

HRESULT WINAPI DirectInputDllCanUnloadNow(void)
{
	return originalDirectInputDllCanUnloadNow();
}

HRESULT WINAPI DirectInputDllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return originalDirectInputDllGetClassObject(rclsid, riid, ppv);
}

LPCDIDATAFORMAT WINAPI DirectInputGetdfDIJoystick()
{
	return originalGetdfDIJoystick();
}

void MEMwrite(void* adr, void* ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr, ptr, size);
	VirtualProtect(adr, size, OldProtection, &OldProtection);
}

extern DWORD WINAPI ThreadForOutputs(LPVOID lpParam);

// global variables 
SDL_Haptic* haptic;
SDL_Haptic* haptic2 = NULL;
SDL_Haptic* haptic3 = NULL;
EffectCollection effects;
EffectConstants effectConst;
Helpers hlp;
EffectTriggers t;

bool CustomStrength = false;
bool WaitForGame = false;
bool keepRunning = true;
float wheel = 0.0f;

SDL_Joystick* GameController = NULL;
SDL_Haptic* ControllerHaptic = NULL;
SDL_Joystick* GameController2 = NULL;
SDL_Haptic* ControllerHaptic2 = NULL;
SDL_Joystick* GameController3 = NULL;
SDL_Haptic* ControllerHaptic3 = NULL;
HINSTANCE gl_hOriginalDll = NULL;
HINSTANCE gl_hjgtDll = NULL;
HINSTANCE gl_cgGLDll = NULL;
HINSTANCE gl_hlibavs = NULL;
extern HINSTANCE ProcDLL;
int joystick_index1;
int joystick1Index = -1;
int joystick_index2 = -1;
int joystick_index3 = -1;
static DWORD GameProcessID;

LPCSTR CustomAlternativeMaxForceLeft;
LPCSTR CustomAlternativeMaxForceRight;
LPCSTR CustomMaxForce;

// settings
wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
int configMinForce = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForce"), 0, settingsFilename);
int configMaxForce = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForce"), 100, settingsFilename);
int enableLogging = GetPrivateProfileInt(TEXT("Settings"), TEXT("Logging"), 0, settingsFilename);
int PowerMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerMode"), 0, settingsFilename);
int EnableRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableRumble"), 0, settingsFilename);
int EnableRumbleTriggers = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableRumbleTriggers"), 0, settingsFilename);
int ReverseRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReverseRumble"), 0, settingsFilename);
int SingleRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("SingleRumbleMotor"), 0, settingsFilename);
int EnableDamper = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamper"), 0, settingsFilename);
int DamperStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrength"), 100, settingsFilename);
wchar_t* deviceGUIDString = new wchar_t[256];
int DeviceGUID = GetPrivateProfileString(TEXT("Settings"), TEXT("DeviceGUID"), NULL, deviceGUIDString, 256, settingsFilename);
int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
int configGameId = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 0, settingsFilename);
int configDefaultCentering = GetPrivateProfileInt(TEXT("Settings"), TEXT("DefaultCentering"), 0, settingsFilename);
int configDefaultFriction = GetPrivateProfileInt(TEXT("Settings"), TEXT("DefaultFriction"), 0, settingsFilename);
int BeepWhenHook = GetPrivateProfileInt(TEXT("Settings"), TEXT("BeepWhenHook"), 0, settingsFilename);
int AlternativeFFB = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeFFB"), 0, settingsFilename);
int configAlternativeMinForceLeft = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeft"), 0, settingsFilename);
int configAlternativeMaxForceLeft = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeft"), 100, settingsFilename);
int configAlternativeMinForceRight = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRight"), 0, settingsFilename);
int configAlternativeMaxForceRight = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRight"), 100, settingsFilename);
int ForceShowDeviceGUIDMessageBox = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceShowDeviceGUIDMessageBox"), 0, settingsFilename);
int configMinForceDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDevice2"), 0, settingsFilename);
int configMaxForceDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDevice2"), 100, settingsFilename);
int EnableRumbleDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableRumbleDevice2"), 0, settingsFilename);
int ReverseRumbleDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReverseRumbleDevice2"), 0, settingsFilename);
int AlternativeFFBDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeFFBDevice2"), 0, settingsFilename);
int configAlternativeMinForceLeftDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDevice2"), 0, settingsFilename);
int configAlternativeMaxForceLeftDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDevice2"), 100, settingsFilename);
int configAlternativeMinForceRightDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDevice2"), 0, settingsFilename);
int configAlternativeMaxForceRightDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDevice2"), 100, settingsFilename);
int configMinForceDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDevice3"), 0, settingsFilename);
int configMaxForceDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDevice3"), 100, settingsFilename);
int EnableRumbleDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableRumbleDevice3"), 0, settingsFilename);
int ReverseRumbleDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReverseRumbleDevice3"), 0, settingsFilename);
int AlternativeFFBDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeFFBDevice3"), 0, settingsFilename);
int configAlternativeMinForceLeftDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDevice3"), 0, settingsFilename);
int configAlternativeMaxForceLeftDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDevice3"), 100, settingsFilename);
int configAlternativeMinForceRightDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDevice3"), 0, settingsFilename);
int configAlternativeMaxForceRightDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDevice3"), 100, settingsFilename);
int SinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriod"), 0, settingsFilename);
int SineFadePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriod"), 0, settingsFilename);
int SineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrength"), 0, settingsFilename);
int RumbleStrengthLeftMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotor"), 0, settingsFilename);
int RumbleStrengthRightMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotor"), 0, settingsFilename);
int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);
int AutoCloseWindowError = GetPrivateProfileInt(TEXT("Settings"), TEXT("AutoCloseWindowError"), 0, settingsFilename);
int EnableFFBStrengthDynamicAdjustment = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableFFBStrengthDynamicAdjustment"), 0, settingsFilename);
int IncreaseFFBStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("IncreaseFFBStrength"), NULL, settingsFilename);
int DecreaseFFBStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("DecreaseFFBStrength"), NULL, settingsFilename);
int ResetFFBStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ResetFFBStrength"), NULL, settingsFilename);
int StepFFBStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("StepFFBStrength"), 5, settingsFilename);
int EnableFFBStrengthPersistence = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableFFBStrengthPersistence"), 0, settingsFilename);
int EnableFFBStrengthTextToSpeech = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableFFBStrengthTextToSpeech"), 0, settingsFilename);
int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
int IgnoreFirstMatchingGUID = GetPrivateProfileInt(TEXT("Settings"), TEXT("IgnoreFirstMatchingGUID"), 0, settingsFilename);
int DoubleSine = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSine"), 0, settingsFilename);
int DoubleConstant = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleConstant"), 0, settingsFilename);
int DoubleSpring = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSpring"), 0, settingsFilename);
int DoubleFriction = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleFriction"), 0, settingsFilename);
int FFBOrRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBOrRumble"), 0, settingsFilename);
int StartDelay = GetPrivateProfileInt(TEXT("Settings"), TEXT("StartDelay"), 0, settingsFilename);

extern void DefaultConfigValues();
extern void CustomFFBStrengthSetup();

char chainedDLL[256];
static char FFBStrength1[256];
static wchar_t FFBStrength2[256];

SDL_Event e;
HRESULT hr;
CComPtr<ISpVoice> cpVoice;

const int TEST_GAME_CONST = -1;
const int TEST_GAME_SINE = -2;
const int TEST_GAME_FRICTION = -3;
const int TEST_GAME_SPRING = -4;
const int TEST_GAME_HEAVY = -5;
const int TEST_GAME_LOOSE = -6;
const int TEST_GAME_RUMBLE = -7;
const int TEST_GAME_RUMBLE_TRIGGER = -8;

const int DAYTONA_3 = 1;
const int WACKY_RACES = 2;
const int CHASE_HQ_2 = 3;
const int HOTD_4 = 4;
const int SEGA_RACING_CLASSIC = 5;
const int SEGA_RALLY_3 = 6;
const int FORD_RACING = 7;
const int INITIAL_D_6 = 8;
const int WMMT_5 = 9;
const int GRID_Real = 10;
const int MARIO_KART_GPDX_CUSTOM = 11;
const int OUTRUN_2Fake = 12;
const int BG4_JP = 13;
const int MACH_STORM = 14;
const int AFTER_BURNER_CLIMAX = 15;
const int INITIAL_D_4 = 16;
const int INITIAL_D_7 = 17;
const int INITIAL_D_8 = 18;
const int POKKEN_TOURNAMENT = 19;
const int MARIO_KART_GPDX_110_CUSTOM = 20;
const int Sonic_Sega_AllStars_Racing = 21;
const int MAME_ = 22;
const int INITIAL_D_5 = 23;
const int INITIAL_D_4_Japan = 24;
const int M2_Emulator = 25;
const int Demul_Emulator = 26;
const int GTI_Club_3 = 27;
const int Button_Rumble = 28;
const int Road_Fighters_3D = 29;
const int LGI_3D = 30;
const int LGI_ = 31;
const int INITIAL_D_0 = 32;
const int SUPERMODEL_ = 34;
const int OUTRUN_2Real = 35;
const int ALIENS_EXTERMINATION = 36;
const int RAMBO_ = 37;
const int FORD_RACING_OTHER = 38;
const int KO_Drive = 39;
const int Transformers_ = 40;
const int Golden_Gun = 41;
const int Dirty_Drivin = 42;
const int H2_Overdrive = 43;
const int Sno_Cross = 44;
const int Bat_man = 45;
const int R_Tuned = 46;
const int SEGA_RALLY_3_Other = 47;
const int INITIAL_D_0_211 = 49;
const int SWDC_2018 = 50;
const int MARIO_KART_GPDX_USA_CUSTOM = 51;
const int WMMT_6 = 52;
const int WMMT_6_R = 53;
const int SRG = 54;
const int D1_GP = 55;
const int WMMT_5DXPlus = 56;
const int WMMT_5DX = 57;
const int Crazy_Taxi = 58;
const int DAYTONA_3_NSE = 59;
const int FLYCAST = 60;
const int WMMT_3 = 61;
const int DEAD_HEAT = 62;
const int DEAD_HEAT_RIDERS = 63;
const int GAELCO_TUNING_RACE = 64;
const int TOKYO_COP = 65;
const int RING_RIDERS = 66;
const int INITIAL_D_0_230 = 67;
const int MARIO_KART_GPDX_118_REAL = 68;
const int MARIO_KART_GPDX_110_REAL = 69;
const int MARIO_KART_GPDX_USA_REAL = 70;
const int GRID_Custom = 71;
const int MARIO_KART_GPDX_118_CUSTOM = 72;
const int SEGA_SHOWDOWN = 73;
const int SPRING_EFFECT = 74;
const int ARCTIC_THUNDER = 75;
const int CRUISN_BLAST = 76;
const int FNF = 77;
const int FNF_DRIFT = 78;
const int FNF_SUPERCARS = 79;
const int SEGA_RACE_TV = 80;
const int HUMMER_EXTREME = 81;
const int INITIAL_D_THEARCADE_V231 = 82;
const int WASTELAND_RACERS_2071 = 83;
const int WMMT_6_RR = 84;

HINSTANCE Get_hInstance()
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(Get_hInstance, &mbi, sizeof(mbi));
	return reinterpret_cast<HINSTANCE>(mbi.AllocationBase);
}

void Initialize(int device_index)
{
	hlp.log("in initialize");
	SDL_SetHint(SDL_HINT_JOYSTICK_RAWINPUT, "0");
	if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) < 0)
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickUpdate();
	char joystick_guid[256];
	sprintf(joystick_guid, "%S", deviceGUIDString);
	SDL_JoystickGUID guid, dev_guid;
	int numJoysticks = SDL_NumJoysticks();
	hlp.log("numJoysticks = ");
	std::string njs = std::to_string(numJoysticks);
	hlp.log((char*)njs.c_str());
	char firstJoystickSelectedText[256];
	SDL_Joystick* FirstGameController = NULL;
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		SDL_Joystick* js = SDL_JoystickOpen(i);
		const char* name = SDL_JoystickName(js);
		guid = SDL_JoystickGetGUID(js);
		if (ForceShowDeviceGUIDMessageBox == 1)
		{
			char text[256];
			SDL_JoystickGetGUIDString(guid, text, 256);
			MessageBoxA(NULL, name, "", 0);
			MessageBoxA(NULL, text, "", 0);
		}
		char guid_str[1024];
		SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
		char text[256];
		sprintf(text, "Joystick: %d / Name: %s / GUID: %s\n", i, name, guid_str);
		hlp.log(text);
		guid = SDL_JoystickGetGUIDFromString(joystick_guid);
		dev_guid = SDL_JoystickGetGUID(js);
		SDL_JoystickClose(js);
		if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
		{
			if (!IgnoreFirstMatchingGUID)
			{
				joystick1Index = i;
				GameController = SDL_JoystickOpen(i);
				joystick_index1 = SDL_JoystickInstanceID(GameController);
				ControllerHaptic = SDL_HapticOpenFromJoystick(GameController);

				if (FirstGameController == NULL)
				{
					sprintf(firstJoystickSelectedText, "No haptic joystick found, selecting first joystick matching the GUID: %d / Name: %s / GUID: %s\n", i, name, guid_str);
					FirstGameController = GameController;
				}

				if (ControllerHaptic != NULL)
				{
					sprintf(text, "Haptic joystick found: %d / Name: %s / GUID: %s\n", i, name, guid_str);
					hlp.log(text);
					break;
				}
			}
			IgnoreFirstMatchingGUID = 0;
		}
	}

	if (ControllerHaptic == NULL && FirstGameController != NULL) // If no haptic controller has been found, we select the first controller matching the guid.
	{
		GameController = FirstGameController;
		hlp.log(firstJoystickSelectedText);
	}
	haptic = ControllerHaptic;
	if ((SDL_HapticRumbleSupported(haptic) == SDL_TRUE && EnableRumble))
	{
		SDL_HapticRumbleInit(ControllerHaptic);
		hlp.log("Rumble Init");
	}
	hlp.log("disabling all current FFB effects");
	SDL_HapticStopAll(haptic);
	hlp.log("setting haptic gain to 100");
	SDL_HapticSetGain(haptic, 100); // HapticSetGain should be between 0 and 100 as per https://wiki.libsdl.org/SDL_HapticSetGain
	hlp.log("setting haptic auto center to 0");
	SDL_HapticSetAutocenter(haptic, 0); // 0 disables autocenter https://wiki.libsdl.org/SDL_HapticSetAutocenter

	SDL_HapticEffect tempEffect;
	hlp.log("creating base effects...");

	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_CONSTANT;
	tempEffect.constant.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.constant.direction.dir[0] = -1; //left => right is +1 as per this 2d array explanation: https://wiki.libsdl.org/SDL_HapticDirection
	tempEffect.constant.length = configFeedbackLength; // presumably is ms, but is not documented
	tempEffect.constant.delay = 0;
	tempEffect.constant.level = 9999; // this is an sint16 => -32768 to 32767
	effects.effect_constant_id = SDL_HapticNewEffect(haptic, &tempEffect); // Upload the effect

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_FRICTION;
	tempEffect.constant.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_friction_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_SINE;
	tempEffect.constant.direction.type = SDL_HAPTIC_CARTESIAN;
	effects.effect_sine_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_SPRING;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_spring_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_INERTIA;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_inertia_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_DAMPER;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_damper_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_TRIANGLE;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_triangle_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_RAMP;
	tempEffect.ramp.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.ramp.delay = 0;
	tempEffect.ramp.length = 5000;
	effects.effect_ramp_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_SAWTOOTHUP;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_sawtoothup_id = SDL_HapticNewEffect(haptic, &tempEffect);

	tempEffect = SDL_HapticEffect();
	tempEffect.type = SDL_HAPTIC_SAWTOOTHDOWN;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = 5000;
	effects.effect_sawtoothdown_id = SDL_HapticNewEffect(haptic, &tempEffect);

	if (haptic2 != NULL)
	{
		SDL_HapticEffect tempEffect2;
		SDL_memset(&tempEffect2, 0, sizeof(SDL_HapticEffect));
		tempEffect2 = SDL_HapticEffect();
		tempEffect2.type = SDL_HAPTIC_SINE;
		tempEffect2.constant.direction.type = SDL_HAPTIC_CARTESIAN;
		effects.effect_sine_id_device2 = SDL_HapticNewEffect(haptic2, &tempEffect2);
	}

	if (haptic3 != NULL)
	{
		SDL_HapticEffect tempEffect3;
		SDL_memset(&tempEffect3, 0, sizeof(SDL_HapticEffect));
		tempEffect3 = SDL_HapticEffect();
		tempEffect3.type = SDL_HAPTIC_SINE;
		tempEffect3.constant.direction.type = SDL_HAPTIC_CARTESIAN;
		effects.effect_sine_id_device3 = SDL_HapticNewEffect(haptic3, &tempEffect3);
	}
	
	// TODO: why don't we just define this as hackFix = true in the other file?
	// Was there a reason to put it here?
//	extern bool hackFix;
//	hackFix = true;

}

using namespace std::chrono;
std::chrono::milliseconds timeOfLastSineEffect = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
std::chrono::milliseconds timeOfLastSineEffectDevice2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
std::chrono::milliseconds timeOfLastSineEffectDevice3 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
double lastSineEffectStrength = 0;
double lastSineEffectStrengthDevice2 = 0;
double lastSineEffectStrengthDevice3 = 0;
double lastSineEffectPeriod = 0;
double lastSineEffectPeriodDevice2 = 0;
double lastSineEffectPeriodDevice3 = 0;

void TriggerConstantEffect(int direction, double strength)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_CONSTANT;
	tempEffect.constant.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.constant.direction.dir[0] = direction;
	tempEffect.constant.length = configFeedbackLength;
	tempEffect.constant.delay = 0;

	int confMinForce = configMinForce;
	int confMaxForce = configMaxForce;

	if (AlternativeFFB)
	{
		if (direction == -1)
		{
			confMinForce = configAlternativeMinForceLeft;
			confMaxForce = configAlternativeMaxForceLeft;
		}
		else
		{
			confMinForce = configAlternativeMinForceRight;
			confMaxForce = configAlternativeMaxForceRight;
		}
	}

	if (PowerMode)
		strength = pow(strength, 0.5);

	if (DoubleConstant)
	{
		strength = strength * 2.0;

		if (strength > 1.0)
			strength = 1.0;
	}

	SHORT MinForce = (SHORT)(strength > 0.001 ? (confMinForce / 100.0 * 32767.0) : 0);
	SHORT MaxForce = (SHORT)(confMaxForce / 100.0 * 32767.0);
	SHORT range = MaxForce - MinForce;
	SHORT level = (SHORT)(strength * range + MinForce);

	if (range > 0 && level < 0)
		level = 32767;
	else if (range < 0 && level > 0)
		level = -32767;

	tempEffect.constant.level = level;

	SDL_HapticUpdateEffect(haptic, effects.effect_constant_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_constant_id, 1);
}

void TriggerFrictionEffectWithDefaultOption(double strength, bool isDefault)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_FRICTION;
	tempEffect.condition.type = SDL_HAPTIC_FRICTION;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = isDefault ? SDL_HAPTIC_INFINITY : configFeedbackLength;
	tempEffect.condition.left_sat[0] = 0xFFFF;
	tempEffect.condition.right_sat[0] = 0xFFFF;

	if (DoubleFriction)
	{
		strength = strength * 2.0;

		if (strength > 1.0)
			strength = 1.0;
	}

	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT coeff = (SHORT)(strength * range + minForce);

	if (coeff < 0)
		coeff = 32767;

	tempEffect.condition.left_coeff[0] = (short)(coeff);
	tempEffect.condition.right_coeff[0] = (short)(coeff);
	SDL_HapticUpdateEffect(haptic, effects.effect_friction_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_friction_id, 1);
}

void TriggerInertiaEffect(double strength)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_INERTIA;
	tempEffect.condition.type = SDL_HAPTIC_INERTIA;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = configFeedbackLength;
	tempEffect.condition.direction.dir[0] = 1;
	tempEffect.condition.direction.dir[1] = 1; //Y Position
	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT coeff = (SHORT)(strength * range + minForce);

	if (coeff < 0)
		coeff = 32767;

	tempEffect.condition.left_coeff[0] = (short)(coeff);
	tempEffect.condition.right_coeff[0] = (short)(coeff);
	tempEffect.condition.left_sat[0] = (short)(coeff) * 10;
	tempEffect.condition.right_sat[0] = (short)(coeff) * 10;
	tempEffect.condition.center[0] = 0;

	SDL_HapticUpdateEffect(haptic, effects.effect_inertia_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_inertia_id, 1);
}

void TriggerTriangleEffect(double strength, double length)
{
	int direction = 1;
	if (strength < -0.001) {
		strength *= -1;
		direction = -1;
	}

	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_TRIANGLE;
	tempEffect.condition.type = SDL_HAPTIC_TRIANGLE;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.direction.dir[0] = direction;
	tempEffect.condition.direction.dir[1] = 0; //Y Position
	tempEffect.periodic.period = 500;

	int confMinForce = configMinForce;
	int confMaxForce = configMaxForce;

	if (AlternativeFFB)
	{
		if (direction == -1)
		{
			confMinForce = configAlternativeMinForceLeft;
			confMaxForce = configAlternativeMaxForceLeft;
		}
		else
		{
			confMinForce = configAlternativeMinForceRight;
			confMaxForce = configAlternativeMaxForceRight;
		}
	}
	SHORT minForce = (SHORT)(strength > 0.001 ? (confMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(confMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT power = (SHORT)(strength * range + minForce);

	if (range > 0 && power < 0)
		power = 32767;
	else if (range < 0 && power > 0)
		power = -32767;

	tempEffect.periodic.magnitude = power;
	tempEffect.periodic.length = length;
	tempEffect.periodic.attack_length = 1000;
	tempEffect.periodic.fade_length = 1000;

	SDL_HapticUpdateEffect(haptic, effects.effect_triangle_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_triangle_id, 1);
}

void TriggerDamperEffect(double strength)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_DAMPER;
	tempEffect.condition.type = SDL_HAPTIC_DAMPER;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = configFeedbackLength;
	tempEffect.condition.direction.dir[0] = 1; // not used
	tempEffect.condition.direction.dir[1] = 0; //Y Position
	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT coeff = (SHORT)(strength * range + minForce);

	if (coeff < 0)
		coeff = 32767;

	tempEffect.condition.left_coeff[0] = (short)(coeff);
	tempEffect.condition.right_coeff[0] = (short)(coeff);
	tempEffect.condition.left_sat[0] = (DWORD)(coeff) * 2;
	tempEffect.condition.right_sat[0] = (DWORD)(coeff) * 2;

	SDL_HapticUpdateEffect(haptic, effects.effect_damper_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_damper_id, 1);
}

void TriggerRampEffect(double start, double end, double length)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_RAMP;
	tempEffect.ramp.type = SDL_HAPTIC_RAMP;
	tempEffect.ramp.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.ramp.length = length;
	SHORT minForce = (SHORT)(start > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT start1 = (SHORT)(start * range + minForce);

	if (start1 < 0)
		start1 = 32767;

	SHORT minForce2 = (SHORT)(end > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce2 = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range2 = maxForce - minForce;
	SHORT start2 = (SHORT)(end * range + minForce);

	if (start2 < 0)
		start2 = 32767;

	tempEffect.ramp.delay = 0;
	tempEffect.ramp.start = start1;
	tempEffect.ramp.end = -start2;

	SDL_HapticUpdateEffect(haptic, effects.effect_ramp_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_ramp_id, 1);
}

void TriggerSawtoothUpEffect(double strength, double length)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_SAWTOOTHUP;
	tempEffect.condition.type = SDL_HAPTIC_SAWTOOTHUP;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.periodic.period = 500;
	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT power = (SHORT)(strength * range + minForce);

	if (power < 0)
		power = 32767;

	tempEffect.periodic.magnitude = power;
	tempEffect.periodic.length = length;
	tempEffect.periodic.attack_length = 1000;
	tempEffect.periodic.fade_length = 1000;

	SDL_HapticUpdateEffect(haptic, effects.effect_sawtoothup_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_sawtoothup_id, 1);
}

void TriggerSawtoothDownEffect(double strength, double length) {
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_SAWTOOTHDOWN;
	tempEffect.condition.type = SDL_HAPTIC_SAWTOOTHDOWN;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.periodic.period = 500;
	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT power = (SHORT)(strength * range + minForce);

	if (power < 0)
		power = 32767;

	tempEffect.periodic.magnitude = power;
	tempEffect.periodic.length = length;
	tempEffect.periodic.attack_length = 1000;
	tempEffect.periodic.fade_length = 1000;

	SDL_HapticUpdateEffect(haptic, effects.effect_sawtoothdown_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_sawtoothdown_id, 1);
}

void TriggerFrictionEffect(double strength)
{
	TriggerFrictionEffectWithDefaultOption(strength, false);
}

void TriggerSineEffect(UINT16 period, UINT16 fadePeriod, double strength)
{
	std::chrono::milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long long elapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now - timeOfLastSineEffect)).count();

	int direction = 1;

	if (period < 1)
		return;

	if (strength < -0.001) {
		strength *= -1;
		direction = -1;
	}

	// if no strength, we do nothing
	if (strength <= 0.001) 
		return;

	// we ignore the new effect until the last one is completed, unless the new one is significantly stronger
	if (elapsedTime < lastSineEffectPeriod && strength < (lastSineEffectStrength * 1.5)) {
		return;
	}

	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	hlp.log("Doing sine...");
	tempEffect.type = SDL_HAPTIC_SINE;
	tempEffect.periodic.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.periodic.direction.dir[0] = direction;
	tempEffect.constant.direction.dir[1] = 0; //Y Position
	tempEffect.periodic.period = period;

	int confMinForce = configMinForce;
	int confMaxForce = configMaxForce;

	if (AlternativeFFB)
	{
		if (direction == -1)
		{
			confMinForce = configAlternativeMinForceLeft;
			confMaxForce = configAlternativeMaxForceLeft;
		}
		else
		{
			confMinForce = configAlternativeMinForceRight;
			confMaxForce = configAlternativeMaxForceRight;
		}
	}

	if (DoubleSine)
	{
		strength = strength * 2.0;

		if (strength > 1.0)
			strength = 1.0;
	}

	SHORT minForce = (SHORT)(strength > 0.001 ? (confMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(confMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT magnitude = (SHORT)(strength * range + minForce);

	if (range > 0 && magnitude < 0)
		magnitude = 32767;
	else if (range < 0 && magnitude > 0)
		magnitude = -32767;

	tempEffect.periodic.magnitude = (SHORT)(magnitude);
	tempEffect.periodic.length = period;
	tempEffect.periodic.attack_length = fadePeriod;
	tempEffect.periodic.fade_length = fadePeriod;

	SDL_HapticUpdateEffect(haptic, effects.effect_sine_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_sine_id, 1);

	timeOfLastSineEffect = now;
	lastSineEffectStrength = strength;
	lastSineEffectPeriod = period;
}

void TriggerSineEffectDevice2(UINT16 period, UINT16 fadePeriod, double strength)
{
	std::chrono::milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long long elapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now - timeOfLastSineEffectDevice2)).count();

	int direction = 1;
	if (strength < -0.001) {
		strength *= -1;
		direction = -1;
	}

	// if no strength, we do nothing
	if (strength <= 0.001) 
		return;

	// we ignore the new effect until the last one is completed, unless the new one is significantly stronger
	if (elapsedTime < lastSineEffectPeriodDevice2 && strength < (lastSineEffectStrengthDevice2 * 1.5)) {
		return;
	}

	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	hlp.log("Doing Device2 sine...");
	tempEffect.type = SDL_HAPTIC_SINE;
	tempEffect.periodic.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.periodic.direction.dir[0] = direction;
	tempEffect.constant.direction.dir[1] = 0; //Y Position
	tempEffect.periodic.period = period;

	int confMinForce = configMinForceDevice2;
	int confMaxForce = configMaxForceDevice2;

	if (AlternativeFFBDevice2)
	{
		if (direction == -1)
		{
			confMinForce = configAlternativeMinForceLeftDevice2;
			confMaxForce = configAlternativeMaxForceLeftDevice2;
		}
		else
		{
			confMinForce = configAlternativeMinForceRightDevice2;
			confMaxForce = configAlternativeMaxForceRightDevice2;
		}
	}
	SHORT minForce = (SHORT)(strength > 0.001 ? (confMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(confMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT magnitude = (SHORT)(strength * range + minForce);

	if (range > 0 && magnitude < 0)
		magnitude = 32767;
	else if (range < 0 && magnitude > 0)
		magnitude = -32767;

	tempEffect.periodic.magnitude = (SHORT)(magnitude);
	tempEffect.periodic.length = period;
	tempEffect.periodic.attack_length = fadePeriod;
	tempEffect.periodic.fade_length = fadePeriod;

	SDL_HapticUpdateEffect(haptic2, effects.effect_sine_id_device2, &tempEffect);
	SDL_HapticRunEffect(haptic2, effects.effect_sine_id_device2, 1);

	timeOfLastSineEffectDevice2 = now;
	lastSineEffectStrengthDevice2 = strength;
	lastSineEffectPeriodDevice2 = period;
}

void TriggerSineEffectDevice3(UINT16 period, UINT16 fadePeriod, double strength)
{
	std::chrono::milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long long elapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now - timeOfLastSineEffectDevice3)).count();

	int direction = 1;
	if (strength < -0.001) {
		strength *= -1;
		direction = -1;
	}

	// if no strength, we do nothing
	if (strength <= 0.001) 
		return;

	// we ignore the new effect until the last one is completed, unless the new one is significantly stronger
	if (elapsedTime < lastSineEffectPeriodDevice3 && strength < (lastSineEffectStrengthDevice3 * 1.5)) {
		return;
	}

	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	hlp.log("Doing Device3 sine...");
	tempEffect.type = SDL_HAPTIC_SINE;
	tempEffect.periodic.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.periodic.direction.dir[0] = direction;
	tempEffect.constant.direction.dir[1] = 0; //Y Position
	tempEffect.periodic.period = period;

	int confMinForce = configMinForceDevice3;
	int confMaxForce = configMaxForceDevice3;

	if (AlternativeFFBDevice3)
	{
		if (direction == -1)
		{
			confMinForce = configAlternativeMinForceLeftDevice3;
			confMaxForce = configAlternativeMaxForceLeftDevice3;
		}
		else
		{
			confMinForce = configAlternativeMinForceRightDevice3;
			confMaxForce = configAlternativeMaxForceRightDevice3;
		}
	}
	SHORT minForce = (SHORT)(strength > 0.001 ? (confMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(confMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT magnitude = (SHORT)(strength * range + minForce);

	if (range > 0 && magnitude < 0)
		magnitude = 32767;
	else if (range < 0 && magnitude > 0)
		magnitude = -32767;

	tempEffect.periodic.magnitude = (SHORT)(magnitude);
	tempEffect.periodic.length = period;
	tempEffect.periodic.attack_length = fadePeriod;
	tempEffect.periodic.fade_length = fadePeriod;

	SDL_HapticUpdateEffect(haptic3, effects.effect_sine_id_device3, &tempEffect);
	SDL_HapticRunEffect(haptic3, effects.effect_sine_id_device3, 1);

	timeOfLastSineEffectDevice3 = now;
	lastSineEffectStrengthDevice3 = strength;
	lastSineEffectPeriodDevice3 = period;
}

void TriggerSpringEffectWithDefaultOption(double strength, bool isDefault)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));
	tempEffect.type = SDL_HAPTIC_SPRING;
	tempEffect.condition.type = SDL_HAPTIC_SPRING;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = isDefault ? SDL_HAPTIC_INFINITY : configFeedbackLength;
	tempEffect.condition.direction.dir[0] = 1;
	tempEffect.constant.direction.dir[1] = 0; //Y Position

	if (DoubleSpring)
	{
		strength = strength * 2.0;

		if (strength > 1.0)
			strength = 1.0;
	}

	SHORT minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
	SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	SHORT range = maxForce - minForce;
	SHORT coeff = (SHORT)(strength * range + minForce);

	if (coeff < 0)
		coeff = 32767;

	tempEffect.condition.left_coeff[0] = (short)(coeff);
	tempEffect.condition.right_coeff[0] = (short)(coeff);
	tempEffect.condition.left_sat[0] = (short)(coeff * 2.0); //Needed for Logitech G920 wheel
	tempEffect.condition.right_sat[0] = (short)(coeff * 2.0); //Needed for Logitech G920 wheel
	tempEffect.condition.center[0] = 0;

	SDL_HapticUpdateEffect(haptic, effects.effect_spring_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_spring_id, 1);
}

void TriggerSpringEffectInfinite(double strength)
{
	SDL_HapticEffect tempEffect;
	SDL_memset(&tempEffect, 0, sizeof(SDL_HapticEffect));

	tempEffect.type = SDL_HAPTIC_SPRING;
	tempEffect.condition.type = SDL_HAPTIC_SPRING;
	tempEffect.condition.direction.type = SDL_HAPTIC_CARTESIAN;
	tempEffect.condition.delay = 0;
	tempEffect.condition.length = SDL_HAPTIC_INFINITY;
	tempEffect.condition.direction.dir[0] = 1;
	tempEffect.constant.direction.dir[1] = 1; //Y Position

	SHORT minForce;
	SHORT maxForce;

	if (EnableForceSpringEffect)
	{
		minForce = (SHORT)(0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
		maxForce = (SHORT)(ForceSpringStrength / 100.0 * 32767.0);

	}
	else
	{
		minForce = (SHORT)(strength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
		maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
	}

	SHORT range = maxForce - minForce;
	SHORT coeff = (SHORT)(strength * range + minForce);

	if (coeff < 0)
		coeff = 32767;

	tempEffect.condition.left_coeff[0] = (short)(coeff);
	tempEffect.condition.right_coeff[0] = (short)(coeff);
	tempEffect.condition.left_sat[0] = (short)(coeff * 2.0); //Needed for Logitech G920 wheel
	tempEffect.condition.right_sat[0] = (short)(coeff * 2.0); //Needed for Logitech G920 wheel
	tempEffect.condition.center[0] = 0;

	SDL_HapticUpdateEffect(haptic, effects.effect_spring_id, &tempEffect);
	SDL_HapticRunEffect(haptic, effects.effect_spring_id, 1);
}

void TriggerLeftRightEffect(double smallstrength, double largestrength, double length)
{
	if (EnableRumble)
	{
		if (!ReverseRumble)
		{
			SDL_HapticEffect tempEffect;
			tempEffect.type = SDL_HAPTIC_LEFTRIGHT;
			tempEffect.leftright.length = length;
			SHORT minForce = (SHORT)(smallstrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range = maxForce - minForce;
			tempEffect.leftright.small_magnitude = (SHORT)(smallstrength * range + minForce);
			SHORT minForce1 = (SHORT)(largestrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce1 = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range1 = maxForce1 - minForce1;
			tempEffect.leftright.large_magnitude = (SHORT)(largestrength * range1 + minForce1);
			SDL_HapticUpdateEffect(haptic, effects.effect_leftright_id, &tempEffect);
			SDL_HapticRunEffect(haptic, effects.effect_leftright_id, 1);
		}
		else
		{
			SDL_HapticEffect tempEffect;
			tempEffect.type = SDL_HAPTIC_LEFTRIGHT;
			tempEffect.leftright.length = length;
			SHORT minForce = (SHORT)(largestrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range = maxForce - minForce;
			tempEffect.leftright.small_magnitude = (SHORT)(largestrength * range + minForce);
			SHORT minForce1 = (SHORT)(smallstrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce1 = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range1 = maxForce1 - minForce1;
			tempEffect.leftright.large_magnitude = (SHORT)(smallstrength * range1 + minForce1);
			SDL_HapticUpdateEffect(haptic, effects.effect_leftright_id, &tempEffect);
			SDL_HapticRunEffect(haptic, effects.effect_leftright_id, 1);
		}
	}
}

void TriggerLeftRightDevice2Effect(double smallstrength, double largestrength, double length)
{
	if (EnableRumble)
	{
		if (!ReverseRumble)
		{
			SDL_HapticEffect tempEffect;
			tempEffect.type = SDL_HAPTIC_LEFTRIGHT;
			tempEffect.leftright.length = length;
			SHORT minForce = (SHORT)(smallstrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range = maxForce - minForce;
			tempEffect.leftright.small_magnitude = (SHORT)(smallstrength * range + minForce);
			SHORT minForce1 = (SHORT)(largestrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce1 = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range1 = maxForce1 - minForce1;
			tempEffect.leftright.large_magnitude = (SHORT)(largestrength * range1 + minForce1);
			SDL_HapticUpdateEffect(haptic2, effects.effect_leftright_id, &tempEffect);
			SDL_HapticRunEffect(haptic2, effects.effect_leftright_id, 1);
		}
		else
		{
			SDL_HapticEffect tempEffect;
			tempEffect.type = SDL_HAPTIC_LEFTRIGHT;
			tempEffect.leftright.length = length;
			SHORT minForce = (SHORT)(largestrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range = maxForce - minForce;
			tempEffect.leftright.small_magnitude = (SHORT)(largestrength * range + minForce);
			SHORT minForce1 = (SHORT)(smallstrength > 0.001 ? (configMinForce / 100.0 * 32767.0) : 0); // strength is a double so we do an epsilon check of 0.001 instead of > 0.
			SHORT maxForce1 = (SHORT)(configMaxForce / 100.0 * 32767.0);
			SHORT range1 = maxForce1 - minForce1;
			tempEffect.leftright.large_magnitude = (SHORT)(smallstrength * range1 + minForce1);
			SDL_HapticUpdateEffect(haptic2, effects.effect_leftright_id, &tempEffect);
			SDL_HapticRunEffect(haptic2, effects.effect_leftright_id, 1);
		}
	}
}

void TriggerRumbleEffect(double highfrequency, double lowfrequency, double length)
{
	if (EnableRumble)
	{
		DWORD minForceLow = (DWORD)(lowfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD minForceHigh = (DWORD)(highfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD maxForce = (DWORD)(configMaxForce / 100.0 * 65535.0);
		DWORD rangeLow = maxForce - minForceLow;
		DWORD rangeHigh = maxForce - minForceHigh;
		DWORD LowMotor = (DWORD)(lowfrequency * rangeLow + minForceLow);
		DWORD HighMotor = (DWORD)(highfrequency * rangeHigh + minForceHigh);

		if (SingleRumbleMotor)
		{
			double LowPercent = (LowMotor / 65535.0) * 100.0;
			double LowPercentRange = 100.0 - LowPercent;
			double HighPercent = (HighMotor / 65535.0) * 100.0;
			double Calculation = LowPercent + ((LowPercentRange * HighPercent) / 100.0);
			LowMotor = 65535.0 * (Calculation / 100.0);
		}

		if (ReverseRumble)
		{
			int ReverseRumble = SDL_JoystickRumble(GameController, HighMotor, LowMotor, length);

			if (ReverseRumble == -1)
				EnableRumble = 0;
		}
		else
		{
			int Rumble = SDL_JoystickRumble(GameController, LowMotor, HighMotor, length);

			if (Rumble == -1)
				EnableRumble = 0;
		}
	}
}

void TriggerRumbleEffectDevice2(double highfrequency, double lowfrequency, double length)
{
	if (EnableRumbleDevice2)
	{
		DWORD minForceLow = (DWORD)(lowfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD minForceHigh = (DWORD)(highfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD maxForce = (DWORD)(configMaxForce / 100.0 * 65535.0);
		DWORD rangeLow = maxForce - minForceLow;
		DWORD rangeHigh = maxForce - minForceHigh;
		DWORD LowMotor = (DWORD)(lowfrequency * rangeLow + minForceLow);
		DWORD HighMotor = (DWORD)(highfrequency * rangeHigh + minForceHigh);

		if (ReverseRumbleDevice2)
		{
			int ReverseRumble2 = SDL_JoystickRumble(GameController2, HighMotor, LowMotor, length);

			if (ReverseRumble2 == -1)
				EnableRumbleDevice2 = 0;
		}
		else
		{
			int Rumble2 = SDL_JoystickRumble(GameController2, LowMotor, HighMotor, length);

			if (Rumble2 == -1)
				EnableRumbleDevice2 = 0;
		}
	}
}

void TriggerRumbleEffectDevice3(double highfrequency, double lowfrequency, double length)
{
	if (EnableRumbleDevice3)
	{
		DWORD minForceLow = (DWORD)(lowfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD minForceHigh = (DWORD)(highfrequency > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD maxForce = (DWORD)(configMaxForce / 100.0 * 65535.0);
		DWORD rangeLow = maxForce - minForceLow;
		DWORD rangeHigh = maxForce - minForceHigh;
		DWORD LowMotor = (DWORD)(lowfrequency * rangeLow + minForceLow);
		DWORD HighMotor = (DWORD)(highfrequency * rangeHigh + minForceHigh);

		if (ReverseRumbleDevice3)
		{
			int ReverseRumble3 = SDL_JoystickRumble(GameController3, HighMotor, LowMotor, length);

			if (ReverseRumble3 == -1)
				EnableRumbleDevice3 = 0;
		}
		else
		{
			int Rumble3 = SDL_JoystickRumble(GameController3, LowMotor, HighMotor, length);

			if (Rumble3 == -1)
				EnableRumbleDevice3 = 0;
		}
	}
}

void TriggerRumbleTriggerEffect(double lefttrigger, double righttrigger, double length)
{
	if (EnableRumbleTriggers)
	{
		DWORD minForceLow = (DWORD)(lefttrigger > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD minForceHigh = (DWORD)(righttrigger > 0.001 ? (configMinForce / 100.0 * 65535.0) : 0);
		DWORD maxForce = (DWORD)(configMaxForce / 100.0 * 65535.0);
		DWORD rangeLow = maxForce - minForceLow;
		DWORD rangeHigh = maxForce - minForceHigh;
		DWORD LeftMotor = (DWORD)(lefttrigger * rangeLow + minForceLow);
		DWORD RightMotor = (DWORD)(righttrigger * rangeHigh + minForceHigh);

		int RumbleTriggers = SDL_JoystickRumbleTriggers(GameController, LeftMotor, RightMotor, length);

		if (RumbleTriggers == -1)
			EnableRumbleTriggers = 0;
	}
}

void TriggerSpringEffect(double strength)
{
	TriggerSpringEffectWithDefaultOption(strength, false);
}

int WorkaroundToFixRumble(void* ptr)
{
	while (SDL_WaitEvent(&e) != 0){}
	return 0;
}

void WritePersistentMaxForce()
{
	if (EnableFFBStrengthPersistence)
	{
		if (AlternativeFFB)
		{
			WritePrivateProfileStringA("Settings", CustomAlternativeMaxForceLeft, (char*)(std::to_string(configAlternativeMaxForceLeft)).c_str(), ".\\FFBPlugin.ini");
			WritePrivateProfileStringA("Settings", CustomAlternativeMaxForceRight, (char*)(std::to_string(configAlternativeMaxForceRight)).c_str(), ".\\FFBPlugin.ini");
		}
		else
			WritePrivateProfileStringA("Settings", CustomMaxForce, (char*)(std::to_string(configMaxForce)).c_str(), ".\\FFBPlugin.ini");
	}
}

static int StrengthLoopWaitEvent()
{
	if (!WaitForGame)
	{
		if (configGameId != 26)
		{
			Sleep(4000);
			WaitForGame = true;
		}
	}
	else
	{
		if (!CustomStrength)
		{
			CustomFFBStrengthSetup();
			CustomStrength = true;
		}

		while (SDL_WaitEvent(&e) != 0)
		{
			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == IncreaseFFBStrength)
					{
						if (AlternativeFFB)
						{
							if (configAlternativeMaxForceRight >= 0 && configAlternativeMaxForceRight < 100)
							{
								configAlternativeMaxForceRight += StepFFBStrength;
								configAlternativeMaxForceRight = max(0, min(100, configAlternativeMaxForceRight));
							}
							if (configAlternativeMaxForceLeft <= 0 && configAlternativeMaxForceLeft > -100)
							{
								configAlternativeMaxForceLeft -= StepFFBStrength;
								configAlternativeMaxForceLeft = max(-100, min(0, configAlternativeMaxForceLeft));
							}
						}
						else
						{
							if (configMaxForce >= 0 && configMaxForce < 100)
							{
								configMaxForce += StepFFBStrength;
								configMaxForce = max(0, min(100, configMaxForce));
							}
						}
						WritePersistentMaxForce();
					}

					if (e.jbutton.button == DecreaseFFBStrength)
					{
						if (AlternativeFFB)
						{
							if (configAlternativeMaxForceRight > 0 && configAlternativeMaxForceRight <= 100)
							{
								configAlternativeMaxForceRight -= StepFFBStrength;
								configAlternativeMaxForceRight = max(0, min(100, configAlternativeMaxForceRight));
							}
							if (configAlternativeMaxForceLeft < 0 && configAlternativeMaxForceLeft >= -100)
							{
								configAlternativeMaxForceLeft += StepFFBStrength;
								configAlternativeMaxForceLeft = max(-100, min(0, configAlternativeMaxForceLeft));
							}
						}
						else
						{
							if (configMaxForce > 0 && configMaxForce <= 100)
							{
								configMaxForce -= StepFFBStrength;
								configMaxForce = max(0, min(100, configMaxForce));
							}
						}
						WritePersistentMaxForce();
					}

					if (e.jbutton.button == ResetFFBStrength)
					{
						DefaultConfigValues();
						WritePersistentMaxForce();
					}

					if (EnableFFBStrengthTextToSpeech)
					{
						if (e.jbutton.button == IncreaseFFBStrength || e.jbutton.button == DecreaseFFBStrength || e.jbutton.button == ResetFFBStrength)
						{
							if (AlternativeFFB)
								sprintf(FFBStrength1, "Max Force: %d", configAlternativeMaxForceRight);
							else
								sprintf(FFBStrength1, "Max Force: %d", configMaxForce);

							hr = ::CoInitialize(nullptr);
							hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
							mbstowcs(FFBStrength2, FFBStrength1, strlen(FFBStrength1) + 1);
							LPWSTR ptr = FFBStrength2;

							if (SUCCEEDED(hr))
							{
								hr = cpVoice->SetRate(3);
								hr = cpVoice->SetOutput(NULL, TRUE);
								hr = cpVoice->Speak(ptr, SPF_PURGEBEFORESPEAK, NULL);
								::CoUninitialize();
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

static int StrengthLoopNoWaitEvent()
{
	if (!WaitForGame)
	{
		if (configGameId != 26)
		{
			Sleep(4000);
			WaitForGame = true;
		}
	}
	else
	{
		if (!CustomStrength)
		{
			CustomFFBStrengthSetup();
			CustomStrength = true;
		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jbutton.which == joystick_index1)
			{
				if (e.jbutton.button == IncreaseFFBStrength)
				{
					if (AlternativeFFB)
					{
						if (configAlternativeMaxForceRight >= 0 && configAlternativeMaxForceRight < 100)
						{
							configAlternativeMaxForceRight += StepFFBStrength;
							configAlternativeMaxForceRight = max(0, min(100, configAlternativeMaxForceRight));
						}

						if (configAlternativeMaxForceLeft <= 0 && configAlternativeMaxForceLeft > -100)
						{
							configAlternativeMaxForceLeft -= StepFFBStrength;
							configAlternativeMaxForceLeft = max(-100, min(0, configAlternativeMaxForceLeft));
						}
					}
					else
					{
						if (configMaxForce >= 0 && configMaxForce < 100)
						{
							configMaxForce += StepFFBStrength;
							configMaxForce = max(0, min(100, configMaxForce));
						}
					}
					WritePersistentMaxForce();
				}

				if (e.jbutton.button == DecreaseFFBStrength)
				{
					if (AlternativeFFB)
					{
						if (configAlternativeMaxForceRight > 0 && configAlternativeMaxForceRight <= 100)
						{
							configAlternativeMaxForceRight -= StepFFBStrength;
							configAlternativeMaxForceRight = max(0, min(100, configAlternativeMaxForceRight));
						}
						if (configAlternativeMaxForceLeft < 0 && configAlternativeMaxForceLeft >= -100)
						{
							configAlternativeMaxForceLeft += StepFFBStrength;
							configAlternativeMaxForceLeft = max(-100, min(0, configAlternativeMaxForceLeft));
						}
					}
					else
					{
						if (configMaxForce > 0 && configMaxForce <= 100)
						{
							configMaxForce -= StepFFBStrength;
							configMaxForce = max(0, min(100, configMaxForce));
						}
					}
					WritePersistentMaxForce();
				}

				if (e.jbutton.button == ResetFFBStrength)
				{
					DefaultConfigValues();
					WritePersistentMaxForce();
				}

				if (EnableFFBStrengthTextToSpeech)
				{
					if (e.jbutton.button == IncreaseFFBStrength || e.jbutton.button == DecreaseFFBStrength || e.jbutton.button == ResetFFBStrength)
					{
						if (AlternativeFFB)
							sprintf(FFBStrength1, "Max Force: %d", configAlternativeMaxForceRight);
						else
							sprintf(FFBStrength1, "Max Force: %d", configMaxForce);

						hr = ::CoInitialize(nullptr);
						hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
						mbstowcs(FFBStrength2, FFBStrength1, strlen(FFBStrength1) + 1);
						LPWSTR ptr = FFBStrength2;

						if (SUCCEEDED(hr))
						{
							hr = cpVoice->SetRate(3);
							hr = cpVoice->SetOutput(NULL, TRUE);
							hr = cpVoice->Speak(ptr, SPF_PURGEBEFORESPEAK, NULL);
							::CoUninitialize();
						}
					}
				}
			}
		}
	}	
	return 0;
}

DWORD WINAPI AdjustFFBStrengthLoopWaitEvent(LPVOID lpParam)
{
	while (true)
	{
		StrengthLoopWaitEvent();
		Sleep(16);
	}
}

DWORD WINAPI AdjustFFBStrengthLoopNoWaitEvent(LPVOID lpParam)
{
	while (true)
	{
		StrengthLoopNoWaitEvent();
		Sleep(16);
	}
}

static DWORD MyGetProcessId(LPCTSTR ProcessName)
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) {
		do {
			if (!lstrcmpi(pt.szExeFile, ProcessName)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap);
	return 0;
}

static BOOL IsProcessRunning(DWORD pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}

DWORD WINAPI FFBLoop(LPVOID lpParam)
{
	hlp.log("In FFBLoop");

	if (StartDelay) //For games which need code to run quicker etc. Some games will crash if no sleep added
		Sleep(2500);

	Initialize(0);
	hlp.log("Initialize() complete");
	if (EnableRumble)
	{
		if (!EnableFFBStrengthDynamicAdjustment && !InputDeviceWheelEnable)
		{
			if (configGameId != 9 && configGameId != 12 && configGameId != 28 && configGameId != 29 && configGameId != 35) // Workaround for SDL_JoystickRumble rumble not stopping issue
				SDL_CreateThread(WorkaroundToFixRumble, "WorkaroundToFixRumble", (void*)NULL);
		}

		//SPECIAL K DISABLES RUMBLE BY DEFAULT. WRITE IT TO FALSE
		char RumbleDisableChar[256];
		GetPrivateProfileStringA("Input.Gamepad", "DisableRumble", "", RumbleDisableChar, 256, ".\\dxgi.ini");
		std::string rumbletrue("true");
		std::string rumbleTRUE("TRUE");
		std::string rumbleTrue("True");
		std::string rumdisable(RumbleDisableChar);

		if (rumdisable.compare(rumbletrue) == 0 || rumdisable.compare(rumbleTrue) == 0 || rumdisable.compare(rumbleTRUE) == 0)
			WritePrivateProfileStringA("Input.Gamepad", "DisableRumble", "false", ".\\dxgi.ini");
	}

	// assign FFB effects here
	t.Constant = &TriggerConstantEffect;
	t.Spring = &TriggerSpringEffect;
	t.Friction = &TriggerFrictionEffect;
	t.Sine = &TriggerSineEffect;
	t.SineDevice2 = &TriggerSineEffectDevice2;
	t.SineDevice3 = &TriggerSineEffectDevice3;
	t.Rumble = &TriggerRumbleEffect;
	t.RumbleDevice2 = &TriggerRumbleEffectDevice2;
	t.RumbleDevice3 = &TriggerRumbleEffectDevice3;
	t.RumbleTriggers = &TriggerRumbleTriggerEffect;
	t.LeftRight = &TriggerLeftRightEffect;
	t.LeftRightDevice2 = &TriggerLeftRightDevice2Effect;
	t.Springi = &TriggerSpringEffectInfinite;
	t.Damper = &TriggerDamperEffect;
	t.Inertia = &TriggerInertiaEffect;
	t.Ramp = &TriggerRampEffect;
	t.SawtoothUp = &TriggerSawtoothUpEffect;
	t.SawtoothDown = &TriggerSawtoothDownEffect;
	t.Triangle = &TriggerTriangleEffect;

	Game* game;
	switch (configGameId) {
	case AFTER_BURNER_CLIMAX:
		game = new AfterburnerClimax;
		break;
	case CHASE_HQ_2:
		game = new ChaseHQ2;
		break;
	case DAYTONA_3:
		game = new Daytona3;
		break;
	case DAYTONA_3_NSE:
		game = new Daytona3NSE;
		break;
	case MAME_:
	case SUPERMODEL_:
	case FLYCAST:
		game = new MAMESupermodel;
		break;
	case FORD_RACING:
		game = new FordRacing;
		break;
	case FORD_RACING_OTHER:
		game = new FordRacingOther;
		break;
	case GRID_Real:
		game = new GRIDReal;
		break;
	case Golden_Gun:
		game = new GoldenGun;
		break;
	case Transformers_:
		game = new Transformers;
		break;
	case INITIAL_D_0:
		game = new InitialD0;
		break;
	case INITIAL_D_0_211:
		game = new InitialD0v211;
		break;
	case INITIAL_D_0_230:
		game = new InitialD0v230;
		break;
	case INITIAL_D_4:
		game = new InitialD4;
		break;
	case INITIAL_D_4_Japan:
		game = new InitialD4Japan;
		break;
	case INITIAL_D_5:
		game = new InitialD5;
		break;
	case INITIAL_D_6:
		game = new InitialD6;
		break;
	case INITIAL_D_7:
		game = new InitialD7;
		break;
	case INITIAL_D_8:
		game = new InitialD8;
		break;
	case SEGA_RACING_CLASSIC:
		game = new SegaRacingClassic;
		break;
	case SEGA_RALLY_3:
		game = new SegaRally3;
		break;
	case SEGA_RALLY_3_Other:
		game = new SegaRally3Other;
		break;
	case WACKY_RACES:
		game = new WackyRaces;
		break;
	case WMMT_5:
		game = new WMMT5;
		break;
	case WMMT_5DX:
		game = new WMMT5DX;
		break;
	case WMMT_5DXPlus:
		game = new WMMT5DXPlus;
		break;
	case MARIO_KART_GPDX_CUSTOM:
		game = new MarioKartGPDX100Custom;
		break;
	case OUTRUN_2Fake:
		game = new OutRun2Fake;
		break;
	case OUTRUN_2Real:
		game = new OutRun2Real;
		break;
	case BG4_JP:
		game = new BG4JP;
		break;
	case MACH_STORM:
		game = new Machstorm;
		break;
	case POKKEN_TOURNAMENT:
		game = new PokkenTournament;
		break;
	case RAMBO_:
		game = new Rambo;
		break;
	case MARIO_KART_GPDX_110_CUSTOM:
		game = new MarioKartGPDX110Custom;
		break;
	case MARIO_KART_GPDX_118_CUSTOM:
		game = new MarioKartGPDX118Custom;
		break;
	case MARIO_KART_GPDX_USA_CUSTOM:
		game = new MarioKartGPDXUSACustom;
		break;
	case Sonic_Sega_AllStars_Racing:
		game = new SonicSegaAllStarsRacing;
		break;
	case M2_Emulator:
		game = new M2Emulator;
		break;
	case Demul_Emulator:
		game = new Demul;
		break;
	case ALIENS_EXTERMINATION:
		game = new AliensExtermination;
		break;
	case GTI_Club_3:
		game = new GTIClub3;
		break;
	case Button_Rumble:
		game = new ButtonRumble;
		break;
	case Road_Fighters_3D:
		game = new RoadFighters3D;
		break;
	case LGI_3D:
		game = new LGI3D;
		break;
	case LGI_:
		game = new LGI;
		break;
	case KO_Drive:
		game = new KODrive;
		break;
	case HOTD_4:
		game = new HOTD4;
		break;
	case Dirty_Drivin:
		game = new DirtyDrivin;
		break;
	case H2_Overdrive:
		game = new H2Overdrive;
		break;
	case Sno_Cross:
		game = new SnoCross;
		break;
	case Bat_man:
		game = new Batman;
		break;
	case R_Tuned:
		game = new RTuned;
		break;
	case SWDC_2018:
		game = new SWDC;
		break;
	case WMMT_6:
		game = new WMMT6;
		break;
	case WMMT_6_R:
		game = new WMMT6R;
		break;
	case WMMT_6_RR:
		game = new WMMT6RR;
		break;
	case SRG:
		game = new StormRacerG;
		break;
	case D1_GP:
		game = new D1GP;
		break;
	case Crazy_Taxi:
		game = new CrazyTaxi;
		break;
	case WMMT_3:
		game = new WMMT3;
		break;
	case DEAD_HEAT:
		game = new DeadHeat;
		break;
	case DEAD_HEAT_RIDERS:
		game = new DeadHeatRiders;
		break;
	case GAELCO_TUNING_RACE:
		game = new GaelcoTuningRace;
		break;
	case TOKYO_COP:
		game = new TokyoCop;
		break;
	case RING_RIDERS:
		game = new RingRiders;
		break;
	case MARIO_KART_GPDX_118_REAL:
		game = new MarioKartGPDX118Real;
		break;
	case MARIO_KART_GPDX_110_REAL:
		game = new MarioKartGPDX110Real;
		break;
	case MARIO_KART_GPDX_USA_REAL:
		game = new MarioKartGPDXUSAReal;
		break;
	case GRID_Custom:
		game = new GRIDCustom;
		break;
	case SEGA_SHOWDOWN:
		game = new Showdown;
		break;
	case SPRING_EFFECT:
		game = new SpringEffect;
		break;
	case ARCTIC_THUNDER:
		game = new ArcticThunder;
		break;
	case CRUISN_BLAST:
		game = new CruisnBlast;
		break;
	case FNF:
		game = new FnF;
		break;
	case FNF_DRIFT:
		game = new FnFDrift;
		break;
	case FNF_SUPERCARS:
		game = new FnFSuperCars;
		break;
	case SEGA_RACE_TV:
		game = new SegaRaceTV;
		break;
	case HUMMER_EXTREME:
		game = new HummerExtreme;
		break;
	case INITIAL_D_THEARCADE_V231:
		game = new InitialDTA231;
		break;
	case WASTELAND_RACERS_2071:
		game = new WasteLandRacers2071;
		break;
	case TEST_GAME_CONST:
	case TEST_GAME_FRICTION:
	case TEST_GAME_SINE:
	case TEST_GAME_SPRING:
	case TEST_GAME_HEAVY:
	case TEST_GAME_LOOSE:
	case TEST_GAME_RUMBLE:
		game = new TestGame;
		break;
	default:
		game = 0;
	}
	hlp.log("Setting DefaultCentering & DefaultFriction forces...");
	if (configDefaultCentering >= 0 && configDefaultCentering <= 100) {
		TriggerSpringEffectWithDefaultOption(configDefaultCentering / 100.0, true);
	}
	if (configDefaultFriction >= 0 && configDefaultFriction <= 100) {
		TriggerFrictionEffectWithDefaultOption(configDefaultFriction / 100.0, true);
	}

	if (EnableFFBStrengthDynamicAdjustment == 1)
	{
		if (configGameId != 9 && configGameId != 12 && configGameId != 28 && configGameId != 29 && configGameId != 35)
		{
			if (configGameId == 26 && InputDeviceWheelEnable)
				CreateThread(NULL, 0, AdjustFFBStrengthLoopNoWaitEvent, NULL, 0, NULL);
			else
				CreateThread(NULL, 0, AdjustFFBStrengthLoopWaitEvent, NULL, 0, NULL);
		}
		else
			CreateThread(NULL, 0, AdjustFFBStrengthLoopNoWaitEvent, NULL, 0, NULL);
	}

	hlp.log("Entering Game's FFBLoop loop");
	bool* kr = (bool*)lpParam;
	while (*kr)
	{
		if (game != 0)
		{
			game->FFBLoop(&effectConst, &hlp, &t);
			Sleep(16);
		}
	}
	hlp.log("about to exit FFBLoop");
	return 0;
}

void CreateFFBLoopThread()
{
	hlp.log("Before CreateThread");
	CreateThread(NULL, 0, FFBLoop, (LPVOID)&keepRunning, 0, NULL);
	hlp.log("After CreateThread");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
	BOOL result = TRUE;
	hlp.enableLogging = enableLogging;
	char buff[MAX_PATH];
	hlp.log("DLLMAIN ENTERED");
	GetModuleFileNameA(NULL, buff, MAX_PATH);
	std::string processName = std::string(buff);
	hlp.log("process name:");
	hlp.log((char*)processName.c_str());
	hlp.log("default centering & friction values:");
	hlp.logInt(configDefaultCentering);
	hlp.logInt(configDefaultFriction);

	switch (ulReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		// log, etc.
		hlp.log("dll process attach:");
		hlp.log((char*)processName.c_str());
		hlp.log((char*)(std::to_string(configMinForce)).c_str());
		hlp.log((char*)(std::to_string(configMaxForce)).c_str());
		DisableThreadLibraryCalls(hModule);
		hlp.log("loading original library...");

		GetPrivateProfileStringA("Settings", "ChainLoad", "", chainedDLL, 256, ".\\FFBplugin.ini");

		if (0 == strlen(chainedDLL))
		{
			char buffer[MAX_PATH];
			GetSystemDirectoryA(buffer, MAX_PATH);

			char libName[256];
			GetModuleFileNameA(hModule, libName, 256);
			_strupr(libName);

			if (NULL != strstr(libName, "DINPUT8"))
			{
				currentLibrary = lib::dinput8;
				strcat_s(buffer, MAX_PATH, "\\dinput8.dll");
			}
			else if (NULL != strstr(libName, "DINPUT"))
			{
				currentLibrary = lib::dinput;
				strcat_s(buffer, MAX_PATH, "\\dinput.dll");
			}
			else if (NULL != strstr(libName, "D3D11"))
			{
				currentLibrary = lib::d3d11;
				strcat_s(buffer, MAX_PATH, "\\d3d11.dll");
			}
			else if (NULL != strstr(libName, "XINPUT1_3"))
			{
				currentLibrary = lib::xinput1_3;
				strcat_s(buffer, MAX_PATH, "\\xinput1_3.dll");
			}
			else if (NULL != strstr(libName, "XINPUT1_4"))
			{
				currentLibrary = lib::xinput1_3;
				strcat_s(buffer, MAX_PATH, "\\xinput1_4.dll");
			}
			else if (NULL != strstr(libName, "OPENGL32"))
			{
				currentLibrary = lib::opengl32;
				strcat_s(buffer, MAX_PATH, "\\opengl32.dll");
			}
			else if (NULL != strstr(libName, "D3D9"))
			{
				currentLibrary = lib::d3d9;
				strcat_s(buffer, MAX_PATH, "\\d3d9.dll");
			}
			else if (NULL != strstr(libName, "WINMM"))
			{
				currentLibrary = lib::winmm;
				strcat_s(buffer, MAX_PATH, "\\winmm.dll");
			}	

			hlp.log(buffer);

			gl_hOriginalDll = LoadLibraryA(buffer);

			if (configGameId == 22 || configGameId == 34 || configGameId == 60)
				CreateThread(NULL, 0, ThreadForOutputs, NULL, 0, NULL);

			if (configGameId == 47)
				MEMwrite((void*)(0x57B2F0), (void*)"\x33\xC0\x40\xC3", 4);

			if (configGameId == 29)
			{
				gl_hjgtDll = LoadLibraryA("jgt.dll");
				gl_hlibavs = LoadLibraryA("libavs-win32-ea3.dll");
			}

			if (configGameId == 4 || configGameId == 37)
				gl_cgGLDll = LoadLibraryA("cgGL.dll");
		}
		else
		{
			hlp.log(chainedDLL);
			gl_hOriginalDll = LoadLibraryA(chainedDLL);
			// e.g. ChainLoad = dinput8-old.dll (if we need to intercept another dinput8.dll file).
		}

		if (!gl_hOriginalDll)
		{
			hlp.log("library load process failed");
			ExitProcess(0);
		}
		else {
			hlp.log("library loaded");
		}

		if (currentLibrary == lib::dinput8)
		{
			originalDirectInputDirectInput8Create = (pfnDirectInputDirectInput8Create)GetProcAddress(gl_hOriginalDll, "DirectInput8Create");
			originalDirectInputDllRegisterServer = (pfnDirectInputDllRegisterServer)GetProcAddress(gl_hOriginalDll, "DllRegisterServer");
			originalDirectInputDllUnregisterServer = (pfnDirectInputDllUnregisterServer)GetProcAddress(gl_hOriginalDll, "DllUnregisterServer");
			originalDirectInputDllCanUnloadNow = (pfnDirectInputDllCanUnloadNow)GetProcAddress(gl_hOriginalDll, "DllCanUnloadNow");
			originalDirectInputDllGetClassObject = (pfnDirectInputDllGetClassObject)GetProcAddress(gl_hOriginalDll, "DllGetClassObject");
			originalGetdfDIJoystick = (pfnDirectInputGetdfDIJoystick)GetProcAddress(gl_hOriginalDll, "GetdfDIJoystick");
		}

		if (currentLibrary == lib::dinput)
		{
			originalDirectInputDllRegisterServer = (pfnDirectInputDllRegisterServer)GetProcAddress(gl_hOriginalDll, "DllRegisterServer");
			originalDirectInputDllUnregisterServer = (pfnDirectInputDllUnregisterServer)GetProcAddress(gl_hOriginalDll, "DllUnregisterServer");
			originalDirectInputDllCanUnloadNow = (pfnDirectInputDllCanUnloadNow)GetProcAddress(gl_hOriginalDll, "DllCanUnloadNow");
			originalDirectInputDllGetClassObject = (pfnDirectInputDllGetClassObject)GetProcAddress(gl_hOriginalDll, "DllGetClassObject");
			originalDirectInputDirectInputCreateA = (pfnDirectInputDirectInputCreateA)GetProcAddress(gl_hOriginalDll, "DirectInputCreateA");
			originalDirectInputDirectInputCreateW = (pfnDirectInputDirectInputCreateW)GetProcAddress(gl_hOriginalDll, "DirectInputCreateW");
			originalDirectInputDirectInputCreateEx = (pfnDirectInputDirectInputCreateEx)GetProcAddress(gl_hOriginalDll, "DirectInputCreateEx");
		}

		if (currentLibrary == lib::d3d11)
		{
			originalCreateDirect3D11DeviceFromDXGIDevice = GetProcAddress(gl_hOriginalDll, "CreateDirect3D11DeviceFromDXGIDevice");
			originalCreateDirect3D11SurfaceFromDXGISurface = GetProcAddress(gl_hOriginalDll, "CreateDirect3D11SurfaceFromDXGISurface");
			originalD3D11CoreCreateDevice = GetProcAddress(gl_hOriginalDll, "D3D11CoreCreateDevice");
			originalD3D11CoreCreateLayeredDevice = GetProcAddress(gl_hOriginalDll, "D3D11CoreCreateLayeredDevice");
			originalD3D11CoreGetLayeredDeviceSize = GetProcAddress(gl_hOriginalDll, "D3D11CoreGetLayeredDeviceSize");
			originalD3D11CoreRegisterLayers = GetProcAddress(gl_hOriginalDll, "D3D11CoreRegisterLayers");
			originalD3D11CreateDevice = GetProcAddress(gl_hOriginalDll, "D3D11CreateDevice");
			originalD3D11CreateDeviceAndSwapChain = GetProcAddress(gl_hOriginalDll, "D3D11CreateDeviceAndSwapChain");
			originalD3D11CreateDeviceForD3D12 = GetProcAddress(gl_hOriginalDll, "D3D11CreateDeviceForD3D12");
			originalD3D11On12CreateDevice = GetProcAddress(gl_hOriginalDll, "D3D11On12CreateDevice");
			originalD3DKMTCloseAdapter = GetProcAddress(gl_hOriginalDll, "D3DKMTCloseAdapter");
			originalD3DKMTCreateAllocation = GetProcAddress(gl_hOriginalDll, "D3DKMTCreateAllocation");
			originalD3DKMTCreateContext = GetProcAddress(gl_hOriginalDll, "D3DKMTCreateContext");
			originalD3DKMTCreateDevice = GetProcAddress(gl_hOriginalDll, "D3DKMTCreateDevice");
			originalD3DKMTCreateSynchronizationObject = GetProcAddress(gl_hOriginalDll, "D3DKMTCreateSynchronizationObject");
			originalD3DKMTDestroyAllocation = GetProcAddress(gl_hOriginalDll, "D3DKMTDestroyAllocation");
			originalD3DKMTDestroyContext = GetProcAddress(gl_hOriginalDll, "D3DKMTDestroyContext");
			originalD3DKMTDestroyDevice = GetProcAddress(gl_hOriginalDll, "D3DKMTDestroyDevice");
			originalD3DKMTDestroySynchronizationObject = GetProcAddress(gl_hOriginalDll, "D3DKMTDestroySynchronizationObject");
			originalD3DKMTEscape = GetProcAddress(gl_hOriginalDll, "D3DKMTEscape");
			originalD3DKMTGetContextSchedulingPriority = GetProcAddress(gl_hOriginalDll, "D3DKMTGetContextSchedulingPriority");
			originalD3DKMTGetDeviceState = GetProcAddress(gl_hOriginalDll, "D3DKMTGetDeviceState");
			originalD3DKMTGetDisplayModeList = GetProcAddress(gl_hOriginalDll, "D3DKMTGetDisplayModeList");
			originalD3DKMTGetMultisampleMethodList = GetProcAddress(gl_hOriginalDll, "D3DKMTGetMultisampleMethodList");
			originalD3DKMTGetRuntimeData = GetProcAddress(gl_hOriginalDll, "D3DKMTGetRuntimeData");
			originalD3DKMTGetSharedPrimaryHandle = GetProcAddress(gl_hOriginalDll, "D3DKMTGetSharedPrimaryHandle");
			originalD3DKMTLock = GetProcAddress(gl_hOriginalDll, "D3DKMTLock");
			originalD3DKMTOpenAdapterFromHdc = GetProcAddress(gl_hOriginalDll, "D3DKMTOpenAdapterFromHdc");
			originalD3DKMTOpenResource = GetProcAddress(gl_hOriginalDll, "D3DKMTOpenResource");
			originalD3DKMTPresent = GetProcAddress(gl_hOriginalDll, "D3DKMTPresent");
			originalD3DKMTQueryAdapterInfo = GetProcAddress(gl_hOriginalDll, "D3DKMTQueryAdapterInfo");
			originalD3DKMTQueryAllocationResidency = GetProcAddress(gl_hOriginalDll, "D3DKMTQueryAllocationResidency");
			originalD3DKMTQueryResourceInfo = GetProcAddress(gl_hOriginalDll, "D3DKMTQueryResourceInfo");
			originalD3DKMTRender = GetProcAddress(gl_hOriginalDll, "D3DKMTRender");
			originalD3DKMTSetAllocationPriority = GetProcAddress(gl_hOriginalDll, "D3DKMTSetAllocationPriority");
			originalD3DKMTSetContextSchedulingPriority = GetProcAddress(gl_hOriginalDll, "D3DKMTSetContextSchedulingPriority");
			originalD3DKMTSetDisplayMode = GetProcAddress(gl_hOriginalDll, "D3DKMTSetDisplayMode");
			originalD3DKMTSetDisplayPrivateDriverFormat = GetProcAddress(gl_hOriginalDll, "D3DKMTSetDisplayPrivateDriverFormat");
			originalD3DKMTSetGammaRamp = GetProcAddress(gl_hOriginalDll, "D3DKMTSetGammaRamp");
			originalD3DKMTSetVidPnSourceOwner = GetProcAddress(gl_hOriginalDll, "D3DKMTSetVidPnSourceOwner");
			originalD3DKMTSignalSynchronizationObject = GetProcAddress(gl_hOriginalDll, "D3DKMTSignalSynchronizationObject");
			originalD3DKMTUnlock = GetProcAddress(gl_hOriginalDll, "D3DKMTUnlock");
			originalD3DKMTWaitForSynchronizationObject = GetProcAddress(gl_hOriginalDll, "D3DKMTWaitForSynchronizationObject");
			originalD3DKMTWaitForVerticalBlankEvent = GetProcAddress(gl_hOriginalDll, "D3DKMTWaitForVerticalBlankEvent");
			originalD3DPerformance_BeginEvent = GetProcAddress(gl_hOriginalDll, "D3DPerformance_BeginEvent");
			originalD3DPerformance_EndEvent = GetProcAddress(gl_hOriginalDll, "D3DPerformance_EndEvent");
			originalD3DPerformance_GetStatus = GetProcAddress(gl_hOriginalDll, "D3DPerformance_GetStatus");
			originalD3DPerformance_SetMarker = GetProcAddress(gl_hOriginalDll, "D3DPerformance_SetMarker");
			originalEnableFeatureLevelUpgrade = GetProcAddress(gl_hOriginalDll, "EnableFeatureLevelUpgrade");
			originalOpenAdapter10 = GetProcAddress(gl_hOriginalDll, "OpenAdapter10");
			originalOpenAdapter10_2 = GetProcAddress(gl_hOriginalDll, "OpenAdapter10_2");
		}

		if (currentLibrary == lib::xinput1_3)
		{
			originalXInputGetState = GetProcAddress(gl_hOriginalDll, "XInputGetState");
			originalXInputSetState = GetProcAddress(gl_hOriginalDll, "XInputSetState");
			originalXInputGetCapabilities = GetProcAddress(gl_hOriginalDll, "XInputGetCapabilities");
			originalXInputEnable = GetProcAddress(gl_hOriginalDll, "XInputEnable");
			originalXInputGetDSoundAudioDeviceGuids = GetProcAddress(gl_hOriginalDll, "XInputGetDSoundAudioDeviceGuids");
			originalXInputGetBatteryInformation = GetProcAddress(gl_hOriginalDll, "XInputGetBatteryInformation");
			originalXInputGetKeystroke = GetProcAddress(gl_hOriginalDll, "XInputGetKeystroke");
			originalXInputGetStateEx = GetProcAddress(gl_hOriginalDll, MAKEINTRESOURCEA(100));
			originalXInputWaitForGuideButton = GetProcAddress(gl_hOriginalDll, MAKEINTRESOURCEA(101));
			originalXInputCancelGuideButtonWait = GetProcAddress(gl_hOriginalDll, MAKEINTRESOURCEA(102));
			originalXInputPowerOffController = GetProcAddress(gl_hOriginalDll, MAKEINTRESOURCEA(103));
		}

		if (currentLibrary == lib::d3d9)
		{
			originalDirect3DShaderValidatorCreate9 = GetProcAddress(gl_hOriginalDll, "Direct3DShaderValidatorCreate9");
			originalPSGPError = GetProcAddress(gl_hOriginalDll, "PSGPError");
			originalPSGPSampleTexture = GetProcAddress(gl_hOriginalDll, "PSGPSampleTexture");
			originalD3DPERF_BeginEvent = GetProcAddress(gl_hOriginalDll, "D3DPERF_BeginEvent");
			originalD3DPERF_EndEvent = GetProcAddress(gl_hOriginalDll, "D3DPERF_EndEvent");
			originalD3DPERF_GetStatus = GetProcAddress(gl_hOriginalDll, "D3DPERF_GetStatus");
			originalD3DPERF_QueryRepeatFrame = GetProcAddress(gl_hOriginalDll, "D3DPERF_QueryRepeatFrame");
			originalD3DPERF_SetMarker = GetProcAddress(gl_hOriginalDll, "D3DPERF_SetMarker");
			originalD3DPERF_SetOptions = GetProcAddress(gl_hOriginalDll, "D3DPERF_SetOptions");
			originalD3DPERF_SetRegion = GetProcAddress(gl_hOriginalDll, "D3DPERF_SetRegion");
			originalDebugSetLevel = GetProcAddress(gl_hOriginalDll, "DebugSetLevel");
			originalDebugSetMute = GetProcAddress(gl_hOriginalDll, "DebugSetMute");
			originalDirect3D9EnableMaximizedWindowedModeShim = GetProcAddress(gl_hOriginalDll, "Direct3D9EnableMaximizedWindowedModeShim");
			originalDirect3DCreate9 = GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");
			originalDirect3DCreate9Ex = GetProcAddress(gl_hOriginalDll, "Direct3DCreate9Ex");
		}

		if (currentLibrary == lib::opengl32)
		{
			originalwglUseFontOutlinesA = GetProcAddress(gl_hOriginalDll, "wglUseFontOutlinesA");
			originalwglUseFontOutlinesW = GetProcAddress(gl_hOriginalDll, "wglUseFontOutlinesW");
			originalwglDescribeLayerPlane = GetProcAddress(gl_hOriginalDll, "wglDescribeLayerPlane");
			originalwglSetLayerPaletteEntries = GetProcAddress(gl_hOriginalDll, "wglSetLayerPaletteEntries");
			originalwglGetLayerPaletteEntries = GetProcAddress(gl_hOriginalDll, "wglGetLayerPaletteEntries");
			originalwglRealizeLayerPalette = GetProcAddress(gl_hOriginalDll, "wglRealizeLayerPalette");
			originalwglSwapLayerBuffers = GetProcAddress(gl_hOriginalDll, "wglSwapLayerBuffers");
			originalwglMakeCurrent = GetProcAddress(gl_hOriginalDll, "wglMakeCurrent");
			originalGlmfInitPlayback = GetProcAddress(gl_hOriginalDll, "GlmfInitPlayback");
			originalGlmfBeginGlsBlock = GetProcAddress(gl_hOriginalDll, "GlmfBeginGlsBlock");
			originalGlmfPlayGlsRecord = GetProcAddress(gl_hOriginalDll, "GlmfPlayGlsRecord");
			originalGlmfEndGlsBlock = GetProcAddress(gl_hOriginalDll, "GlmfEndGlsBlock");
			originalGlmfEndPlayback = GetProcAddress(gl_hOriginalDll, "GlmfEndPlayback");
			originalGlmfCloseMetaFile = GetProcAddress(gl_hOriginalDll, "GlmfCloseMetaFile");
			originalwglSwapMultipleBuffers = GetProcAddress(gl_hOriginalDll, "wglSwapMultipleBuffers");
			originalwglCreateLayerContext = GetProcAddress(gl_hOriginalDll, "wglCreateLayerContext");
			originalwglCreateContext = GetProcAddress(gl_hOriginalDll, "wglCreateContext");
			originalwglDeleteContext = GetProcAddress(gl_hOriginalDll, "wglDeleteContext");
			originalwglGetCurrentContext = GetProcAddress(gl_hOriginalDll, "wglGetCurrentContext");
			originalwglGetCurrentDC = GetProcAddress(gl_hOriginalDll, "wglGetCurrentDC");
			originalwglUseFontBitmapsA = GetProcAddress(gl_hOriginalDll, "wglUseFontBitmapsA");
			originalwglUseFontBitmapsW = GetProcAddress(gl_hOriginalDll, "wglUseFontBitmapsW");
			originalwglShareLists = GetProcAddress(gl_hOriginalDll, "wglShareLists");
			originalwglGetDefaultProcAddress = GetProcAddress(gl_hOriginalDll, "wglGetDefaultProcAddress");
			originalwglGetProcAddress = GetProcAddress(gl_hOriginalDll, "wglGetProcAddress");
			originalwglCopyContext = GetProcAddress(gl_hOriginalDll, "wglCopyContext");
			originalglDebugEntry = GetProcAddress(gl_hOriginalDll, "glDebugEntry");
			originalwglGetPixelFormat = GetProcAddress(gl_hOriginalDll, "wglGetPixelFormat");
			originalwglSetPixelFormat = GetProcAddress(gl_hOriginalDll, "wglSetPixelFormat");
			originalwglChoosePixelFormat = GetProcAddress(gl_hOriginalDll, "wglChoosePixelFormat");
			originalwglDescribePixelFormat = GetProcAddress(gl_hOriginalDll, "wglDescribePixelFormat");
			originalwglSwapBuffers = GetProcAddress(gl_hOriginalDll, "wglSwapBuffers");
			originalglCallList = GetProcAddress(gl_hOriginalDll, "glCallList");
			originalglCallLists = GetProcAddress(gl_hOriginalDll, "glCallLists");
			originalglBegin = GetProcAddress(gl_hOriginalDll, "glBegin");
			originalglColor3b = GetProcAddress(gl_hOriginalDll, "glColor3b");
			originalglColor3bv = GetProcAddress(gl_hOriginalDll, "glColor3bv");
			originalglColor3d = GetProcAddress(gl_hOriginalDll, "glColor3d");
			originalglColor3dv = GetProcAddress(gl_hOriginalDll, "glColor3dv");
			originalglColor3f = GetProcAddress(gl_hOriginalDll, "glColor3f");
			originalglColor3fv = GetProcAddress(gl_hOriginalDll, "glColor3fv");
			originalglColor3i = GetProcAddress(gl_hOriginalDll, "glColor3i");
			originalglColor3iv = GetProcAddress(gl_hOriginalDll, "glColor3iv");
			originalglColor3s = GetProcAddress(gl_hOriginalDll, "glColor3s");
			originalglColor3sv = GetProcAddress(gl_hOriginalDll, "glColor3sv");
			originalglColor3ub = GetProcAddress(gl_hOriginalDll, "glColor3ub");
			originalglColor3ubv = GetProcAddress(gl_hOriginalDll, "glColor3ubv");
			originalglColor3ui = GetProcAddress(gl_hOriginalDll, "glColor3ui");
			originalglColor3uiv = GetProcAddress(gl_hOriginalDll, "glColor3uiv");
			originalglColor3us = GetProcAddress(gl_hOriginalDll, "glColor3us");
			originalglColor3usv = GetProcAddress(gl_hOriginalDll, "glColor3usv");
			originalglColor4b = GetProcAddress(gl_hOriginalDll, "glColor4b");
			originalglColor4bv = GetProcAddress(gl_hOriginalDll, "glColor4bv");
			originalglColor4d = GetProcAddress(gl_hOriginalDll, "glColor4d");
			originalglColor4dv = GetProcAddress(gl_hOriginalDll, "glColor4dv");
			originalglColor4f = GetProcAddress(gl_hOriginalDll, "glColor4f");
			originalglColor4fv = GetProcAddress(gl_hOriginalDll, "glColor4fv");
			originalglColor4i = GetProcAddress(gl_hOriginalDll, "glColor4i");
			originalglColor4iv = GetProcAddress(gl_hOriginalDll, "glColor4iv");
			originalglColor4s = GetProcAddress(gl_hOriginalDll, "glColor4s");
			originalglColor4sv = GetProcAddress(gl_hOriginalDll, "glColor4sv");
			originalglColor4ub = GetProcAddress(gl_hOriginalDll, "glColor4ub");
			originalglColor4ubv = GetProcAddress(gl_hOriginalDll, "glColor4ubv");
			originalglColor4ui = GetProcAddress(gl_hOriginalDll, "glColor4ui");
			originalglColor4uiv = GetProcAddress(gl_hOriginalDll, "glColor4uiv");
			originalglColor4us = GetProcAddress(gl_hOriginalDll, "glColor4us");
			originalglColor4usv = GetProcAddress(gl_hOriginalDll, "glColor4usv");
			originalglEdgeFlag = GetProcAddress(gl_hOriginalDll, "glEdgeFlag");
			originalglEdgeFlagv = GetProcAddress(gl_hOriginalDll, "glEdgeFlagv");
			originalglEnd = GetProcAddress(gl_hOriginalDll, "glEnd");
			originalglIndexd = GetProcAddress(gl_hOriginalDll, "glIndexd");
			originalglIndexdv = GetProcAddress(gl_hOriginalDll, "glIndexdv");
			originalglIndexf = GetProcAddress(gl_hOriginalDll, "glIndexf");
			originalglIndexfv = GetProcAddress(gl_hOriginalDll, "glIndexfv");
			originalglIndexi = GetProcAddress(gl_hOriginalDll, "glIndexi");
			originalglIndexiv = GetProcAddress(gl_hOriginalDll, "glIndexiv");
			originalglIndexs = GetProcAddress(gl_hOriginalDll, "glIndexs");
			originalglIndexsv = GetProcAddress(gl_hOriginalDll, "glIndexsv");
			originalglNormal3b = GetProcAddress(gl_hOriginalDll, "glNormal3b");
			originalglNormal3bv = GetProcAddress(gl_hOriginalDll, "glNormal3bv");
			originalglNormal3d = GetProcAddress(gl_hOriginalDll, "glNormal3d");
			originalglNormal3dv = GetProcAddress(gl_hOriginalDll, "glNormal3dv");
			originalglNormal3f = GetProcAddress(gl_hOriginalDll, "glNormal3f");
			originalglNormal3fv = GetProcAddress(gl_hOriginalDll, "glNormal3fv");
			originalglNormal3i = GetProcAddress(gl_hOriginalDll, "glNormal3i");
			originalglNormal3iv = GetProcAddress(gl_hOriginalDll, "glNormal3iv");
			originalglNormal3s = GetProcAddress(gl_hOriginalDll, "glNormal3s");
			originalglNormal3sv = GetProcAddress(gl_hOriginalDll, "glNormal3sv");
			originalglTexCoord1d = GetProcAddress(gl_hOriginalDll, "glTexCoord1d");
			originalglTexCoord1dv = GetProcAddress(gl_hOriginalDll, "glTexCoord1dv");
			originalglTexCoord1f = GetProcAddress(gl_hOriginalDll, "glTexCoord1f");
			originalglTexCoord1fv = GetProcAddress(gl_hOriginalDll, "glTexCoord1fv");
			originalglTexCoord1i = GetProcAddress(gl_hOriginalDll, "glTexCoord1i");
			originalglTexCoord1iv = GetProcAddress(gl_hOriginalDll, "glTexCoord1iv");
			originalglTexCoord1s = GetProcAddress(gl_hOriginalDll, "glTexCoord1s");
			originalglTexCoord1sv = GetProcAddress(gl_hOriginalDll, "glTexCoord1sv");
			originalglTexCoord2d = GetProcAddress(gl_hOriginalDll, "glTexCoord2d");
			originalglTexCoord2dv = GetProcAddress(gl_hOriginalDll, "glTexCoord2dv");
			originalglTexCoord2f = GetProcAddress(gl_hOriginalDll, "glTexCoord2f");
			originalglTexCoord2fv = GetProcAddress(gl_hOriginalDll, "glTexCoord2fv");
			originalglTexCoord2i = GetProcAddress(gl_hOriginalDll, "glTexCoord2i");
			originalglTexCoord2iv = GetProcAddress(gl_hOriginalDll, "glTexCoord2iv");
			originalglTexCoord2s = GetProcAddress(gl_hOriginalDll, "glTexCoord2s");
			originalglTexCoord2sv = GetProcAddress(gl_hOriginalDll, "glTexCoord2sv");
			originalglTexCoord3d = GetProcAddress(gl_hOriginalDll, "glTexCoord3d");
			originalglTexCoord3dv = GetProcAddress(gl_hOriginalDll, "glTexCoord3dv");
			originalglTexCoord3f = GetProcAddress(gl_hOriginalDll, "glTexCoord3f");
			originalglTexCoord3fv = GetProcAddress(gl_hOriginalDll, "glTexCoord3fv");
			originalglTexCoord3i = GetProcAddress(gl_hOriginalDll, "glTexCoord3i");
			originalglTexCoord3iv = GetProcAddress(gl_hOriginalDll, "glTexCoord3iv");
			originalglTexCoord3s = GetProcAddress(gl_hOriginalDll, "glTexCoord3s");
			originalglTexCoord3sv = GetProcAddress(gl_hOriginalDll, "glTexCoord3sv");
			originalglTexCoord4d = GetProcAddress(gl_hOriginalDll, "glTexCoord4d");
			originalglTexCoord4dv = GetProcAddress(gl_hOriginalDll, "glTexCoord4dv");
			originalglTexCoord4f = GetProcAddress(gl_hOriginalDll, "glTexCoord4f");
			originalglTexCoord4fv = GetProcAddress(gl_hOriginalDll, "glTexCoord4fv");
			originalglTexCoord4i = GetProcAddress(gl_hOriginalDll, "glTexCoord4i");
			originalglTexCoord4iv = GetProcAddress(gl_hOriginalDll, "glTexCoord4iv");
			originalglTexCoord4s = GetProcAddress(gl_hOriginalDll, "glTexCoord4s");
			originalglTexCoord4sv = GetProcAddress(gl_hOriginalDll, "glTexCoord4sv");
			originalglVertex2d = GetProcAddress(gl_hOriginalDll, "glVertex2d");
			originalglVertex2dv = GetProcAddress(gl_hOriginalDll, "glVertex2dv");
			originalglVertex2f = GetProcAddress(gl_hOriginalDll, "glVertex2f");
			originalglVertex2fv = GetProcAddress(gl_hOriginalDll, "glVertex2fv");
			originalglVertex2i = GetProcAddress(gl_hOriginalDll, "glVertex2i");
			originalglVertex2iv = GetProcAddress(gl_hOriginalDll, "glVertex2iv");
			originalglVertex2s = GetProcAddress(gl_hOriginalDll, "glVertex2s");
			originalglVertex2sv = GetProcAddress(gl_hOriginalDll, "glVertex2sv");
			originalglVertex3d = GetProcAddress(gl_hOriginalDll, "glVertex3d");
			originalglVertex3dv = GetProcAddress(gl_hOriginalDll, "glVertex3dv");
			originalglVertex3f = GetProcAddress(gl_hOriginalDll, "glVertex3f");
			originalglVertex3fv = GetProcAddress(gl_hOriginalDll, "glVertex3fv");
			originalglVertex3i = GetProcAddress(gl_hOriginalDll, "glVertex3i");
			originalglVertex3iv = GetProcAddress(gl_hOriginalDll, "glVertex3iv");
			originalglVertex3s = GetProcAddress(gl_hOriginalDll, "glVertex3s");
			originalglVertex3sv = GetProcAddress(gl_hOriginalDll, "glVertex3sv");
			originalglVertex4d = GetProcAddress(gl_hOriginalDll, "glVertex4d");
			originalglVertex4dv = GetProcAddress(gl_hOriginalDll, "glVertex4dv");
			originalglVertex4f = GetProcAddress(gl_hOriginalDll, "glVertex4f");
			originalglVertex4fv = GetProcAddress(gl_hOriginalDll, "glVertex4fv");
			originalglVertex4i = GetProcAddress(gl_hOriginalDll, "glVertex4i");
			originalglVertex4iv = GetProcAddress(gl_hOriginalDll, "glVertex4iv");
			originalglVertex4s = GetProcAddress(gl_hOriginalDll, "glVertex4s");
			originalglVertex4sv = GetProcAddress(gl_hOriginalDll, "glVertex4sv");
			originalglMaterialf = GetProcAddress(gl_hOriginalDll, "glMaterialf");
			originalglMaterialfv = GetProcAddress(gl_hOriginalDll, "glMaterialfv");
			originalglMateriali = GetProcAddress(gl_hOriginalDll, "glMateriali");
			originalglMaterialiv = GetProcAddress(gl_hOriginalDll, "glMaterialiv");
			originalglDisable = GetProcAddress(gl_hOriginalDll, "glDisable");
			originalglEnable = GetProcAddress(gl_hOriginalDll, "glEnable");
			originalglPopAttrib = GetProcAddress(gl_hOriginalDll, "glPopAttrib");
			originalglPushAttrib = GetProcAddress(gl_hOriginalDll, "glPushAttrib");
			originalglEvalCoord1d = GetProcAddress(gl_hOriginalDll, "glEvalCoord1d");
			originalglEvalCoord1dv = GetProcAddress(gl_hOriginalDll, "glEvalCoord1dv");
			originalglEvalCoord1f = GetProcAddress(gl_hOriginalDll, "glEvalCoord1f");
			originalglEvalCoord1fv = GetProcAddress(gl_hOriginalDll, "glEvalCoord1fv");
			originalglEvalCoord2d = GetProcAddress(gl_hOriginalDll, "glEvalCoord2d");
			originalglEvalCoord2dv = GetProcAddress(gl_hOriginalDll, "glEvalCoord2dv");
			originalglEvalCoord2f = GetProcAddress(gl_hOriginalDll, "glEvalCoord2f");
			originalglEvalCoord2fv = GetProcAddress(gl_hOriginalDll, "glEvalCoord2fv");
			originalglEvalPoint1 = GetProcAddress(gl_hOriginalDll, "glEvalPoint1");
			originalglEvalPoint2 = GetProcAddress(gl_hOriginalDll, "glEvalPoint2");
			originalglLoadIdentity = GetProcAddress(gl_hOriginalDll, "glLoadIdentity");
			originalglLoadMatrixf = GetProcAddress(gl_hOriginalDll, "glLoadMatrixf");
			originalglLoadMatrixd = GetProcAddress(gl_hOriginalDll, "glLoadMatrixd");
			originalglMatrixMode = GetProcAddress(gl_hOriginalDll, "glMatrixMode");
			originalglMultMatrixf = GetProcAddress(gl_hOriginalDll, "glMultMatrixf");
			originalglMultMatrixd = GetProcAddress(gl_hOriginalDll, "glMultMatrixd");
			originalglPopMatrix = GetProcAddress(gl_hOriginalDll, "glPopMatrix");
			originalglPushMatrix = GetProcAddress(gl_hOriginalDll, "glPushMatrix");
			originalglRotated = GetProcAddress(gl_hOriginalDll, "glRotated");
			originalglRotatef = GetProcAddress(gl_hOriginalDll, "glRotatef");
			originalglScaled = GetProcAddress(gl_hOriginalDll, "glScaled");
			originalglScalef = GetProcAddress(gl_hOriginalDll, "glScalef");
			originalglTranslated = GetProcAddress(gl_hOriginalDll, "glTranslated");
			originalglTranslatef = GetProcAddress(gl_hOriginalDll, "glTranslatef");
			originalglArrayElement = GetProcAddress(gl_hOriginalDll, "glArrayElement");
			originalglBindTexture = GetProcAddress(gl_hOriginalDll, "glBindTexture");
			originalglColorPointer = GetProcAddress(gl_hOriginalDll, "glColorPointer");
			originalglDisableClientState = GetProcAddress(gl_hOriginalDll, "glDisableClientState");
			originalglDrawArrays = GetProcAddress(gl_hOriginalDll, "glDrawArrays");
			originalglDrawElements = GetProcAddress(gl_hOriginalDll, "glDrawElements");
			originalglEdgeFlagPointer = GetProcAddress(gl_hOriginalDll, "glEdgeFlagPointer");
			originalglEnableClientState = GetProcAddress(gl_hOriginalDll, "glEnableClientState");
			originalglIndexPointer = GetProcAddress(gl_hOriginalDll, "glIndexPointer");
			originalglIndexub = GetProcAddress(gl_hOriginalDll, "glIndexub");
			originalglIndexubv = GetProcAddress(gl_hOriginalDll, "glIndexubv");
			originalglInterleavedArrays = GetProcAddress(gl_hOriginalDll, "glInterleavedArrays");
			originalglNormalPointer = GetProcAddress(gl_hOriginalDll, "glNormalPointer");
			originalglPolygonOffset = GetProcAddress(gl_hOriginalDll, "glPolygonOffset");
			originalglTexCoordPointer = GetProcAddress(gl_hOriginalDll, "glTexCoordPointer");
			originalglVertexPointer = GetProcAddress(gl_hOriginalDll, "glVertexPointer");
			originalglGetPointerv = GetProcAddress(gl_hOriginalDll, "glGetPointerv");
			originalglPopClientAttrib = GetProcAddress(gl_hOriginalDll, "glPopClientAttrib");
			originalglPushClientAttrib = GetProcAddress(gl_hOriginalDll, "glPushClientAttrib");
			originalglClear = GetProcAddress(gl_hOriginalDll, "glClear");
			originalglClearAccum = GetProcAddress(gl_hOriginalDll, "glClearAccum");
			originalglClearIndex = GetProcAddress(gl_hOriginalDll, "glClearIndex");
			originalglClearColor = GetProcAddress(gl_hOriginalDll, "glClearColor");
			originalglClearStencil = GetProcAddress(gl_hOriginalDll, "glClearStencil");
			originalglClearDepth = GetProcAddress(gl_hOriginalDll, "glClearDepth");
			originalglBitmap = GetProcAddress(gl_hOriginalDll, "glBitmap");
			originalglTexImage1D = GetProcAddress(gl_hOriginalDll, "glTexImage1D");
			originalglTexImage2D = GetProcAddress(gl_hOriginalDll, "glTexImage2D");
			originalglCopyPixels = GetProcAddress(gl_hOriginalDll, "glCopyPixels");
			originalglReadPixels = GetProcAddress(gl_hOriginalDll, "glReadPixels");
			originalglDrawPixels = GetProcAddress(gl_hOriginalDll, "glDrawPixels");
			originalglRectd = GetProcAddress(gl_hOriginalDll, "glRectd");
			originalglRectdv = GetProcAddress(gl_hOriginalDll, "glRectdv");
			originalglRectf = GetProcAddress(gl_hOriginalDll, "glRectf");
			originalglRectfv = GetProcAddress(gl_hOriginalDll, "glRectfv");
			originalglRecti = GetProcAddress(gl_hOriginalDll, "glRecti");
			originalglRectiv = GetProcAddress(gl_hOriginalDll, "glRectiv");
			originalglRects = GetProcAddress(gl_hOriginalDll, "glRects");
			originalglRectsv = GetProcAddress(gl_hOriginalDll, "glRectsv");
			originalglNewList = GetProcAddress(gl_hOriginalDll, "glNewList");
			originalglEndList = GetProcAddress(gl_hOriginalDll, "glEndList");
			originalglDeleteLists = GetProcAddress(gl_hOriginalDll, "glDeleteLists");
			originalglGenLists = GetProcAddress(gl_hOriginalDll, "glGenLists");
			originalglListBase = GetProcAddress(gl_hOriginalDll, "glListBase");
			originalglRasterPos2d = GetProcAddress(gl_hOriginalDll, "glRasterPos2d");
			originalglRasterPos2dv = GetProcAddress(gl_hOriginalDll, "glRasterPos2dv");
			originalglRasterPos2f = GetProcAddress(gl_hOriginalDll, "glRasterPos2f");
			originalglRasterPos2fv = GetProcAddress(gl_hOriginalDll, "glRasterPos2fv");
			originalglRasterPos2i = GetProcAddress(gl_hOriginalDll, "glRasterPos2i");
			originalglRasterPos2iv = GetProcAddress(gl_hOriginalDll, "glRasterPos2iv");
			originalglRasterPos2s = GetProcAddress(gl_hOriginalDll, "glRasterPos2s");
			originalglRasterPos2sv = GetProcAddress(gl_hOriginalDll, "glRasterPos2sv");
			originalglRasterPos3d = GetProcAddress(gl_hOriginalDll, "glRasterPos3d");
			originalglRasterPos3dv = GetProcAddress(gl_hOriginalDll, "glRasterPos3dv");
			originalglRasterPos3f = GetProcAddress(gl_hOriginalDll, "glRasterPos3f");
			originalglRasterPos3fv = GetProcAddress(gl_hOriginalDll, "glRasterPos3fv");
			originalglRasterPos3i = GetProcAddress(gl_hOriginalDll, "glRasterPos3i");
			originalglRasterPos3iv = GetProcAddress(gl_hOriginalDll, "glRasterPos3iv");
			originalglRasterPos3s = GetProcAddress(gl_hOriginalDll, "glRasterPos3s");
			originalglRasterPos3sv = GetProcAddress(gl_hOriginalDll, "glRasterPos3sv");
			originalglRasterPos4d = GetProcAddress(gl_hOriginalDll, "glRasterPos4d");
			originalglRasterPos4dv = GetProcAddress(gl_hOriginalDll, "glRasterPos4dv");
			originalglRasterPos4f = GetProcAddress(gl_hOriginalDll, "glRasterPos4f");
			originalglRasterPos4fv = GetProcAddress(gl_hOriginalDll, "glRasterPos4fv");
			originalglRasterPos4i = GetProcAddress(gl_hOriginalDll, "glRasterPos4i");
			originalglRasterPos4iv = GetProcAddress(gl_hOriginalDll, "glRasterPos4iv");
			originalglRasterPos4s = GetProcAddress(gl_hOriginalDll, "glRasterPos4s");
			originalglRasterPos4sv = GetProcAddress(gl_hOriginalDll, "glRasterPos4sv");
			originalglClipPlane = GetProcAddress(gl_hOriginalDll, "glClipPlane");
			originalglColorMaterial = GetProcAddress(gl_hOriginalDll, "glColorMaterial");
			originalglCullFace = GetProcAddress(gl_hOriginalDll, "glCullFace");
			originalglFogf = GetProcAddress(gl_hOriginalDll, "glFogf");
			originalglFogfv = GetProcAddress(gl_hOriginalDll, "glFogfv");
			originalglFogi = GetProcAddress(gl_hOriginalDll, "glFogi");
			originalglFogiv = GetProcAddress(gl_hOriginalDll, "glFogiv");
			originalglFrontFace = GetProcAddress(gl_hOriginalDll, "glFrontFace");
			originalglHint = GetProcAddress(gl_hOriginalDll, "glHint");
			originalglLightf = GetProcAddress(gl_hOriginalDll, "glLightf");
			originalglLightfv = GetProcAddress(gl_hOriginalDll, "glLightfv");
			originalglLighti = GetProcAddress(gl_hOriginalDll, "glLighti");
			originalglLightiv = GetProcAddress(gl_hOriginalDll, "glLightiv");
			originalglLightModelf = GetProcAddress(gl_hOriginalDll, "glLightModelf");
			originalglLightModelfv = GetProcAddress(gl_hOriginalDll, "glLightModelfv");
			originalglLightModeli = GetProcAddress(gl_hOriginalDll, "glLightModeli");
			originalglLightModeliv = GetProcAddress(gl_hOriginalDll, "glLightModeliv");
			originalglLineStipple = GetProcAddress(gl_hOriginalDll, "glLineStipple");
			originalglLineWidth = GetProcAddress(gl_hOriginalDll, "glLineWidth");
			originalglPointSize = GetProcAddress(gl_hOriginalDll, "glPointSize");
			originalglPolygonMode = GetProcAddress(gl_hOriginalDll, "glPolygonMode");
			originalglPolygonStipple = GetProcAddress(gl_hOriginalDll, "glPolygonStipple");
			originalglScissor = GetProcAddress(gl_hOriginalDll, "glScissor");
			originalglFinish = GetProcAddress(gl_hOriginalDll, "glFinish");
			originalglShadeModel = GetProcAddress(gl_hOriginalDll, "glShadeModel");
			originalglTexParameterf = GetProcAddress(gl_hOriginalDll, "glTexParameterf");
			originalglTexParameterfv = GetProcAddress(gl_hOriginalDll, "glTexParameterfv");
			originalglTexParameteri = GetProcAddress(gl_hOriginalDll, "glTexParameteri");
			originalglTexParameteriv = GetProcAddress(gl_hOriginalDll, "glTexParameteriv");
			originalglTexEnvf = GetProcAddress(gl_hOriginalDll, "glTexEnvf");
			originalglTexEnvfv = GetProcAddress(gl_hOriginalDll, "glTexEnvfv");
			originalglTexEnvi = GetProcAddress(gl_hOriginalDll, "glTexEnvi");
			originalglTexEnviv = GetProcAddress(gl_hOriginalDll, "glTexEnviv");
			originalglTexGend = GetProcAddress(gl_hOriginalDll, "glTexGend");
			originalglTexGendv = GetProcAddress(gl_hOriginalDll, "glTexGendv");
			originalglTexGenf = GetProcAddress(gl_hOriginalDll, "glTexGenf");
			originalglTexGenfv = GetProcAddress(gl_hOriginalDll, "glTexGenfv");
			originalglTexGeni = GetProcAddress(gl_hOriginalDll, "glTexGeni");
			originalglTexGeniv = GetProcAddress(gl_hOriginalDll, "glTexGeniv");
			originalglFeedbackBuffer = GetProcAddress(gl_hOriginalDll, "glFeedbackBuffer");
			originalglSelectBuffer = GetProcAddress(gl_hOriginalDll, "glSelectBuffer");
			originalglRenderMode = GetProcAddress(gl_hOriginalDll, "glRenderMode");
			originalglInitNames = GetProcAddress(gl_hOriginalDll, "glInitNames");
			originalglLoadName = GetProcAddress(gl_hOriginalDll, "glLoadName");
			originalglPassThrough = GetProcAddress(gl_hOriginalDll, "glPassThrough");
			originalglPopName = GetProcAddress(gl_hOriginalDll, "glPopName");
			originalglPushName = GetProcAddress(gl_hOriginalDll, "glPushName");
			originalglDrawBuffer = GetProcAddress(gl_hOriginalDll, "glDrawBuffer");
			originalglStencilMask = GetProcAddress(gl_hOriginalDll, "glStencilMask");
			originalglColorMask = GetProcAddress(gl_hOriginalDll, "glColorMask");
			originalglDepthMask = GetProcAddress(gl_hOriginalDll, "glDepthMask");
			originalglIndexMask = GetProcAddress(gl_hOriginalDll, "glIndexMask");
			originalglAccum = GetProcAddress(gl_hOriginalDll, "glAccum");
			originalglFlush = GetProcAddress(gl_hOriginalDll, "glFlush");
			originalglMap1d = GetProcAddress(gl_hOriginalDll, "glMap1d");
			originalglMap1f = GetProcAddress(gl_hOriginalDll, "glMap1f");
			originalglMap2d = GetProcAddress(gl_hOriginalDll, "glMap2d");
			originalglMap2f = GetProcAddress(gl_hOriginalDll, "glMap2f");
			originalglMapGrid1d = GetProcAddress(gl_hOriginalDll, "glMapGrid1d");
			originalglMapGrid1f = GetProcAddress(gl_hOriginalDll, "glMapGrid1f");
			originalglMapGrid2d = GetProcAddress(gl_hOriginalDll, "glMapGrid2d");
			originalglMapGrid2f = GetProcAddress(gl_hOriginalDll, "glMapGrid2f");
			originalglEvalMesh1 = GetProcAddress(gl_hOriginalDll, "glEvalMesh1");
			originalglEvalMesh2 = GetProcAddress(gl_hOriginalDll, "glEvalMesh2");
			originalglAlphaFunc = GetProcAddress(gl_hOriginalDll, "glAlphaFunc");
			originalglBlendFunc = GetProcAddress(gl_hOriginalDll, "glBlendFunc");
			originalglLogicOp = GetProcAddress(gl_hOriginalDll, "glLogicOp");
			originalglStencilFunc = GetProcAddress(gl_hOriginalDll, "glStencilFunc");
			originalglStencilOp = GetProcAddress(gl_hOriginalDll, "glStencilOp");
			originalglDepthFunc = GetProcAddress(gl_hOriginalDll, "glDepthFunc");
			originalglPixelZoom = GetProcAddress(gl_hOriginalDll, "glPixelZoom");
			originalglPixelTransferf = GetProcAddress(gl_hOriginalDll, "glPixelTransferf");
			originalglPixelTransferi = GetProcAddress(gl_hOriginalDll, "glPixelTransferi");
			originalglPixelStoref = GetProcAddress(gl_hOriginalDll, "glPixelStoref");
			originalglPixelStorei = GetProcAddress(gl_hOriginalDll, "glPixelStorei");
			originalglPixelMapfv = GetProcAddress(gl_hOriginalDll, "glPixelMapfv");
			originalglPixelMapuiv = GetProcAddress(gl_hOriginalDll, "glPixelMapuiv");
			originalglPixelMapusv = GetProcAddress(gl_hOriginalDll, "glPixelMapusv");
			originalglReadBuffer = GetProcAddress(gl_hOriginalDll, "glReadBuffer");
			originalglGetBooleanv = GetProcAddress(gl_hOriginalDll, "glGetBooleanv");
			originalglGetClipPlane = GetProcAddress(gl_hOriginalDll, "glGetClipPlane");
			originalglGetDoublev = GetProcAddress(gl_hOriginalDll, "glGetDoublev");
			originalglGetError = GetProcAddress(gl_hOriginalDll, "glGetError");
			originalglGetFloatv = GetProcAddress(gl_hOriginalDll, "glGetFloatv");
			originalglGetIntegerv = GetProcAddress(gl_hOriginalDll, "glGetIntegerv");
			originalglGetLightfv = GetProcAddress(gl_hOriginalDll, "glGetLightfv");
			originalglGetLightiv = GetProcAddress(gl_hOriginalDll, "glGetLightiv");
			originalglGetMapdv = GetProcAddress(gl_hOriginalDll, "glGetMapdv");
			originalglGetMapfv = GetProcAddress(gl_hOriginalDll, "glGetMapfv");
			originalglGetMapiv = GetProcAddress(gl_hOriginalDll, "glGetMapiv");
			originalglGetMaterialfv = GetProcAddress(gl_hOriginalDll, "glGetMaterialfv");
			originalglGetMaterialiv = GetProcAddress(gl_hOriginalDll, "glGetMaterialiv");
			originalglGetPixelMapfv = GetProcAddress(gl_hOriginalDll, "glGetPixelMapfv");
			originalglGetPixelMapuiv = GetProcAddress(gl_hOriginalDll, "glGetPixelMapuiv");
			originalglGetPixelMapusv = GetProcAddress(gl_hOriginalDll, "glGetPixelMapusv");
			originalglGetPolygonStipple = GetProcAddress(gl_hOriginalDll, "glGetPolygonStipple");
			originalglGetString = GetProcAddress(gl_hOriginalDll, "glGetString");
			originalglGetTexEnvfv = GetProcAddress(gl_hOriginalDll, "glGetTexEnvfv");
			originalglGetTexEnviv = GetProcAddress(gl_hOriginalDll, "glGetTexEnviv");
			originalglGetTexGendv = GetProcAddress(gl_hOriginalDll, "glGetTexGendv");
			originalglGetTexGenfv = GetProcAddress(gl_hOriginalDll, "glGetTexGenfv");
			originalglGetTexGeniv = GetProcAddress(gl_hOriginalDll, "glGetTexGeniv");
			originalglGetTexImage = GetProcAddress(gl_hOriginalDll, "glGetTexImage");
			originalglGetTexParameterfv = GetProcAddress(gl_hOriginalDll, "glGetTexParameterfv");
			originalglGetTexParameteriv = GetProcAddress(gl_hOriginalDll, "glGetTexParameteriv");
			originalglGetTexLevelParameterfv = GetProcAddress(gl_hOriginalDll, "glGetTexLevelParameterfv");
			originalglGetTexLevelParameteriv = GetProcAddress(gl_hOriginalDll, "glGetTexLevelParameteriv");
			originalglIsEnabled = GetProcAddress(gl_hOriginalDll, "glIsEnabled");
			originalglIsList = GetProcAddress(gl_hOriginalDll, "glIsList");
			originalglDepthRange = GetProcAddress(gl_hOriginalDll, "glDepthRange");
			originalglFrustum = GetProcAddress(gl_hOriginalDll, "glFrustum");
			originalglOrtho = GetProcAddress(gl_hOriginalDll, "glOrtho");
			originalglViewport = GetProcAddress(gl_hOriginalDll, "glViewport");
			originalglAreTexturesResident = GetProcAddress(gl_hOriginalDll, "glAreTexturesResident");
			originalglCopyTexImage1D = GetProcAddress(gl_hOriginalDll, "glCopyTexImage1D");
			originalglCopyTexImage2D = GetProcAddress(gl_hOriginalDll, "glCopyTexImage2D");
			originalglCopyTexSubImage1D = GetProcAddress(gl_hOriginalDll, "glCopyTexSubImage1D");
			originalglCopyTexSubImage2D = GetProcAddress(gl_hOriginalDll, "glCopyTexSubImage2D");
			originalglDeleteTextures = GetProcAddress(gl_hOriginalDll, "glDeleteTextures");
			originalglGenTextures = GetProcAddress(gl_hOriginalDll, "glGenTextures");
			originalglIsTexture = GetProcAddress(gl_hOriginalDll, "glIsTexture");
			originalglPrioritizeTextures = GetProcAddress(gl_hOriginalDll, "glPrioritizeTextures");
			originalglTexSubImage1D = GetProcAddress(gl_hOriginalDll, "glTexSubImage1D");
			originalglTexSubImage2D = GetProcAddress(gl_hOriginalDll, "glTexSubImage2D");
		}

		if (currentLibrary == lib::winmm)
		{
			originalPlaySoundW = GetProcAddress(gl_hOriginalDll, "PlaySoundW");
			originaltimeSetEvent = GetProcAddress(gl_hOriginalDll, "timeSetEvent");
			originaltimeKillEvent = GetProcAddress(gl_hOriginalDll, "timeKillEvent");
			originalmidiOutMessage = GetProcAddress(gl_hOriginalDll, "midiOutMessage");
			originaltimeBeginPeriod = GetProcAddress(gl_hOriginalDll, "timeBeginPeriod");
			originaltimeGetTime = GetProcAddress(gl_hOriginalDll, "timeGetTime");
			originalNotifyCallbackData = GetProcAddress(gl_hOriginalDll, "NotifyCallbackData");
			originalWOW32DriverCallback = GetProcAddress(gl_hOriginalDll, "WOW32DriverCallback");
			originalWOW32ResolveMultiMediaHandle = GetProcAddress(gl_hOriginalDll, "WOW32ResolveMultiMediaHandle");
			originalaux32Message = GetProcAddress(gl_hOriginalDll, "aux32Message");
			originaljoy32Message = GetProcAddress(gl_hOriginalDll, "joy32Message");
			originalmid32Message = GetProcAddress(gl_hOriginalDll, "mid32Message");
			originalmod32Message = GetProcAddress(gl_hOriginalDll, "mod32Message");
			originalmxd32Message = GetProcAddress(gl_hOriginalDll, "mxd32Message");
			originaltid32Message = GetProcAddress(gl_hOriginalDll, "tid32Message");
			originalwid32Message = GetProcAddress(gl_hOriginalDll, "wid32Message");
			originalwod32Message = GetProcAddress(gl_hOriginalDll, "wod32Message");
			originalmci32Message = GetProcAddress(gl_hOriginalDll, "mci32Message");
			originalCloseDriver = GetProcAddress(gl_hOriginalDll, "CloseDriver");
			originalDefDriverProc = GetProcAddress(gl_hOriginalDll, "DefDriverProc");
			originalDriverCallback = GetProcAddress(gl_hOriginalDll, "DriverCallback");
			originalDrvGetModuleHandle = GetProcAddress(gl_hOriginalDll, "DrvGetModuleHandle");
			originalGetDriverModuleHandle = GetProcAddress(gl_hOriginalDll, "GetDriverModuleHandle");
			originalOpenDriver = GetProcAddress(gl_hOriginalDll, "OpenDriver");
			originalPlaySound = GetProcAddress(gl_hOriginalDll, "PlaySound");
			originalOrdinal2 = GetProcAddress(gl_hOriginalDll, "Ordinal2");
			originalSendDriverMessage = GetProcAddress(gl_hOriginalDll, "SendDriverMessage");
			originalauxGetDevCapsA = GetProcAddress(gl_hOriginalDll, "auxGetDevCapsA");
			originalauxGetDevCapsW = GetProcAddress(gl_hOriginalDll, "auxGetDevCapsW");
			originalauxGetNumDevs = GetProcAddress(gl_hOriginalDll, "auxGetNumDevs");
			originalauxGetVolume = GetProcAddress(gl_hOriginalDll, "auxGetVolume");
			originalauxOutMessage = GetProcAddress(gl_hOriginalDll, "auxOutMessage");
			originalauxSetVolume = GetProcAddress(gl_hOriginalDll, "auxSetVolume");
			originaljoyConfigChanged = GetProcAddress(gl_hOriginalDll, "joyConfigChanged");
			originaljoyGetDevCapsA = GetProcAddress(gl_hOriginalDll, "joyGetDevCapsA");
			originaljoyGetDevCapsW = GetProcAddress(gl_hOriginalDll, "joyGetDevCapsW");
			originaljoyGetNumDevs = GetProcAddress(gl_hOriginalDll, "joyGetNumDevs");
			originaljoyGetPosEx = GetProcAddress(gl_hOriginalDll, "joyGetPosEx");
			originaljoyGetPos = GetProcAddress(gl_hOriginalDll, "joyGetPos");
			originaljoyGetThreshold = GetProcAddress(gl_hOriginalDll, "joyGetThreshold");
			originaljoyReleaseCapture = GetProcAddress(gl_hOriginalDll, "joyReleaseCapture");
			originaljoySetCapture = GetProcAddress(gl_hOriginalDll, "joySetCapture");
			originaljoySetThreshold = GetProcAddress(gl_hOriginalDll, "joySetThreshold");
			originalmidiConnect = GetProcAddress(gl_hOriginalDll, "midiConnect");
			originalmidiDisconnect = GetProcAddress(gl_hOriginalDll, "midiDisconnect");
			originalmidiInAddBuffer = GetProcAddress(gl_hOriginalDll, "midiInAddBuffer");
			originalmidiInClose = GetProcAddress(gl_hOriginalDll, "midiInClose");
			originalmidiInGetDevCapsA = GetProcAddress(gl_hOriginalDll, "midiInGetDevCapsA");
			originalmidiInGetDevCapsW = GetProcAddress(gl_hOriginalDll, "midiInGetDevCapsW");
			originalmidiInGetErrorTextA = GetProcAddress(gl_hOriginalDll, "midiInGetErrorTextA");
			originalmidiInGetErrorTextW = GetProcAddress(gl_hOriginalDll, "midiInGetErrorTextW");
			originalmidiInGetID = GetProcAddress(gl_hOriginalDll, "midiInGetID");
			originalmidiInGetNumDevs = GetProcAddress(gl_hOriginalDll, "midiInGetNumDevs");
			originalmidiInMessage = GetProcAddress(gl_hOriginalDll, "midiInMessage");
			originalmidiInOpen = GetProcAddress(gl_hOriginalDll, "midiInOpen");
			originalmidiInPrepareHeader = GetProcAddress(gl_hOriginalDll, "midiInPrepareHeader");
			originalmidiInReset = GetProcAddress(gl_hOriginalDll, "midiInReset");
			originalmidiInStart = GetProcAddress(gl_hOriginalDll, "midiInStart");
			originalmidiInStop = GetProcAddress(gl_hOriginalDll, "midiInStop");
			originalmidiInUnprepareHeader = GetProcAddress(gl_hOriginalDll, "midiInUnprepareHeader");
			originalmidiOutCacheDrumPatches = GetProcAddress(gl_hOriginalDll, "midiOutCacheDrumPatches");
			originalmidiOutCachePatches = GetProcAddress(gl_hOriginalDll, "midiOutCachePatches");
			originalmidiOutClose = GetProcAddress(gl_hOriginalDll, "midiOutClose");
			originalmidiOutGetDevCapsA = GetProcAddress(gl_hOriginalDll, "midiOutGetDevCapsA");
			originalmidiOutGetDevCapsW = GetProcAddress(gl_hOriginalDll, "midiOutGetDevCapsW");
			originalmidiOutGetErrorTextA = GetProcAddress(gl_hOriginalDll, "midiOutGetErrorTextA");
			originalmidiOutGetErrorTextW = GetProcAddress(gl_hOriginalDll, "midiOutGetErrorTextW");
			originalmidiOutGetID = GetProcAddress(gl_hOriginalDll, "midiOutGetID");
			originalmidiOutGetNumDevs = GetProcAddress(gl_hOriginalDll, "midiOutGetNumDevs");
			originalmidiOutGetVolume = GetProcAddress(gl_hOriginalDll, "midiOutGetVolume");
			originalmidiOutLongMsg = GetProcAddress(gl_hOriginalDll, "midiOutLongMsg");
			originalmidiOutOpen = GetProcAddress(gl_hOriginalDll, "midiOutOpen");
			originalmidiOutPrepareHeader = GetProcAddress(gl_hOriginalDll, "midiOutPrepareHeader");
			originalmidiOutReset = GetProcAddress(gl_hOriginalDll, "midiOutReset");
			originalmidiOutSetVolume = GetProcAddress(gl_hOriginalDll, "midiOutSetVolume");
			originalmidiOutShortMsg = GetProcAddress(gl_hOriginalDll, "midiOutShortMsg");
			originalmidiOutUnprepareHeader = GetProcAddress(gl_hOriginalDll, "midiOutUnprepareHeader");
			originalmidiStreamClose = GetProcAddress(gl_hOriginalDll, "midiStreamClose");
			originalmidiStreamOpen = GetProcAddress(gl_hOriginalDll, "midiStreamOpen");
			originalmidiStreamOut = GetProcAddress(gl_hOriginalDll, "midiStreamOut");
			originalmidiStreamPause = GetProcAddress(gl_hOriginalDll, "midiStreamPause");
			originalmidiStreamPosition = GetProcAddress(gl_hOriginalDll, "midiStreamPosition");
			originalmidiStreamProperty = GetProcAddress(gl_hOriginalDll, "midiStreamProperty");
			originalmidiStreamRestart = GetProcAddress(gl_hOriginalDll, "midiStreamRestart");
			originalmidiStreamStop = GetProcAddress(gl_hOriginalDll, "midiStreamStop");
			originalmixerClose = GetProcAddress(gl_hOriginalDll, "mixerClose");
			originalmixerGetControlDetailsA = GetProcAddress(gl_hOriginalDll, "mixerGetControlDetailsA");
			originalmixerGetControlDetailsW = GetProcAddress(gl_hOriginalDll, "mixerGetControlDetailsW");
			originalmixerGetDevCapsA = GetProcAddress(gl_hOriginalDll, "mixerGetDevCapsA");
			originalmixerGetDevCapsW = GetProcAddress(gl_hOriginalDll, "mixerGetDevCapsW");
			originalmixerGetID = GetProcAddress(gl_hOriginalDll, "mixerGetID");
			originalmixerGetLineControlsA = GetProcAddress(gl_hOriginalDll, "mixerGetLineControlsA");
			originalmixerGetLineControlsW = GetProcAddress(gl_hOriginalDll, "mixerGetLineControlsW");
			originalmixerGetLineInfoA = GetProcAddress(gl_hOriginalDll, "mixerGetLineInfoA");
			originalmixerGetLineInfoW = GetProcAddress(gl_hOriginalDll, "mixerGetLineInfoW");
			originalmixerGetNumDevs = GetProcAddress(gl_hOriginalDll, "mixerGetNumDevs");
			originalmixerMessage = GetProcAddress(gl_hOriginalDll, "mixerMessage");
			originalmixerOpen = GetProcAddress(gl_hOriginalDll, "mixerOpen");
			originalmixerSetControlDetails = GetProcAddress(gl_hOriginalDll, "mixerSetControlDetails");
			originalmmDrvInstall = GetProcAddress(gl_hOriginalDll, "mmDrvInstall");
			originalmmGetCurrentTask = GetProcAddress(gl_hOriginalDll, "mmGetCurrentTask");
			originalmmTaskBlock = GetProcAddress(gl_hOriginalDll, "mmTaskBlock");
			originalmmTaskCreate = GetProcAddress(gl_hOriginalDll, "mmTaskCreate");
			originalmmTaskSignal = GetProcAddress(gl_hOriginalDll, "mmTaskSignal");
			originalmmTaskYield = GetProcAddress(gl_hOriginalDll, "mmTaskYield");
			originalmmioAdvance = GetProcAddress(gl_hOriginalDll, "mmioAdvance");
			originalmmioAscend = GetProcAddress(gl_hOriginalDll, "mmioAscend");
			originalmmioClose = GetProcAddress(gl_hOriginalDll, "mmioClose");
			originalmmioCreateChunk = GetProcAddress(gl_hOriginalDll, "mmioCreateChunk");
			originalmmioDescend = GetProcAddress(gl_hOriginalDll, "mmioDescend");
			originalmmioFlush = GetProcAddress(gl_hOriginalDll, "mmioFlush");
			originalmmioGetInfo = GetProcAddress(gl_hOriginalDll, "mmioGetInfo");
			originalmmioInstallIOProcA = GetProcAddress(gl_hOriginalDll, "mmioInstallIOProcA");
			originalmmioInstallIOProcW = GetProcAddress(gl_hOriginalDll, "mmioInstallIOProcW");
			originalmmioOpenA = GetProcAddress(gl_hOriginalDll, "mmioOpenA");
			originalmmioOpenW = GetProcAddress(gl_hOriginalDll, "mmioOpenW");
			originalmmioRead = GetProcAddress(gl_hOriginalDll, "mmioRead");
			originalmmioRenameA = GetProcAddress(gl_hOriginalDll, "mmioRenameA");
			originalmmioRenameW = GetProcAddress(gl_hOriginalDll, "mmioRenameW");
			originalmmioSeek = GetProcAddress(gl_hOriginalDll, "mmioSeek");
			originalmmioSendMessage = GetProcAddress(gl_hOriginalDll, "mmioSendMessage");
			originalmmioSetBuffer = GetProcAddress(gl_hOriginalDll, "mmioSetBuffer");
			originalmmioSetInfo = GetProcAddress(gl_hOriginalDll, "mmioSetInfo");
			originalmmioStringToFOURCCA = GetProcAddress(gl_hOriginalDll, "mmioStringToFOURCCA");
			originalmmioStringToFOURCCW = GetProcAddress(gl_hOriginalDll, "mmioStringToFOURCCW");
			originalmmioWrite = GetProcAddress(gl_hOriginalDll, "mmioWrite");
			originaltimeEndPeriod = GetProcAddress(gl_hOriginalDll, "timeEndPeriod");
			originaltimeGetDevCaps = GetProcAddress(gl_hOriginalDll, "timeGetDevCaps");
			originaltimeGetSystemTime = GetProcAddress(gl_hOriginalDll, "timeGetSystemTime");
			originalwaveInAddBuffer = GetProcAddress(gl_hOriginalDll, "waveInAddBuffer");
			originalwaveInClose = GetProcAddress(gl_hOriginalDll, "waveInClose");
			originalwaveInGetDevCapsA = GetProcAddress(gl_hOriginalDll, "waveInGetDevCapsA");
			originalwaveInGetDevCapsW = GetProcAddress(gl_hOriginalDll, "waveInGetDevCapsW");
			originalwaveInGetErrorTextA = GetProcAddress(gl_hOriginalDll, "waveInGetErrorTextA");
			originalwaveInGetErrorTextW = GetProcAddress(gl_hOriginalDll, "waveInGetErrorTextW");
			originalwaveInGetID = GetProcAddress(gl_hOriginalDll, "waveInGetID");
			originalwaveInGetNumDevs = GetProcAddress(gl_hOriginalDll, "waveInGetNumDevs");
			originalwaveInGetPosition = GetProcAddress(gl_hOriginalDll, "waveInGetPosition");
			originalwaveInMessage = GetProcAddress(gl_hOriginalDll, "waveInMessage");
			originalwaveInOpen = GetProcAddress(gl_hOriginalDll, "waveInOpen");
			originalwaveInPrepareHeader = GetProcAddress(gl_hOriginalDll, "waveInPrepareHeader");
			originalwaveInReset = GetProcAddress(gl_hOriginalDll, "waveInReset");
			originalwaveInStart = GetProcAddress(gl_hOriginalDll, "waveInStart");
			originalwaveInStop = GetProcAddress(gl_hOriginalDll, "waveInStop");
			originalwaveInUnprepareHeader = GetProcAddress(gl_hOriginalDll, "waveInUnprepareHeader");
			originalwaveOutBreakLoop = GetProcAddress(gl_hOriginalDll, "waveOutBreakLoop");
			originalwaveOutClose = GetProcAddress(gl_hOriginalDll, "waveOutClose");
			originalwaveOutGetDevCapsA = GetProcAddress(gl_hOriginalDll, "waveOutGetDevCapsA");
			originalwaveOutGetDevCapsW = GetProcAddress(gl_hOriginalDll, "waveOutGetDevCapsW");
			originalwaveOutGetErrorTextA = GetProcAddress(gl_hOriginalDll, "waveOutGetErrorTextA");
			originalwaveOutGetErrorTextW = GetProcAddress(gl_hOriginalDll, "waveOutGetErrorTextW");
			originalwaveOutGetID = GetProcAddress(gl_hOriginalDll, "waveOutGetID");
			originalwaveOutGetNumDevs = GetProcAddress(gl_hOriginalDll, "waveOutGetNumDevs");
			originalwaveOutGetPitch = GetProcAddress(gl_hOriginalDll, "waveOutGetPitch");
			originalwaveOutGetPlaybackRate = GetProcAddress(gl_hOriginalDll, "waveOutGetPlaybackRate");
			originalwaveOutGetPosition = GetProcAddress(gl_hOriginalDll, "waveOutGetPosition");
			originalwaveOutGetVolume = GetProcAddress(gl_hOriginalDll, "waveOutGetVolume");
			originalwaveOutMessage = GetProcAddress(gl_hOriginalDll, "waveOutMessage");
			originalwaveOutOpen = GetProcAddress(gl_hOriginalDll, "waveOutOpen");
			originalwaveOutPause = GetProcAddress(gl_hOriginalDll, "waveOutPause");
			originalwaveOutPrepareHeader = GetProcAddress(gl_hOriginalDll, "waveOutPrepareHeader");
			originalwaveOutReset = GetProcAddress(gl_hOriginalDll, "waveOutReset");
			originalwaveOutRestart = GetProcAddress(gl_hOriginalDll, "waveOutRestart");
			originalwaveOutSetPitch = GetProcAddress(gl_hOriginalDll, "waveOutSetPitch");
			originalwaveOutSetPlaybackRate = GetProcAddress(gl_hOriginalDll, "waveOutSetPlaybackRate");
			originalwaveOutSetVolume = GetProcAddress(gl_hOriginalDll, "waveOutSetVolume");
			originalwaveOutUnprepareHeader = GetProcAddress(gl_hOriginalDll, "waveOutUnprepareHeader");
			originalwaveOutWrite = GetProcAddress(gl_hOriginalDll, "waveOutWrite");
			originalmciExecute = GetProcAddress(gl_hOriginalDll, "mciExecute");
			originalmciGetErrorStringA = GetProcAddress(gl_hOriginalDll, "mciGetErrorStringA");
			originalmciGetErrorStringW = GetProcAddress(gl_hOriginalDll, "mciGetErrorStringW");
			originalmciSendCommandA = GetProcAddress(gl_hOriginalDll, "mciSendCommandA");
			originalmciSendCommandW = GetProcAddress(gl_hOriginalDll, "mciSendCommandW");
			originalmciSendStringA = GetProcAddress(gl_hOriginalDll, "mciSendStringA");
			originalmciSendStringW = GetProcAddress(gl_hOriginalDll, "mciSendStringW");
			originalmciFreeCommandResource = GetProcAddress(gl_hOriginalDll, "mciFreeCommandResource");
			originalmciLoadCommandResource = GetProcAddress(gl_hOriginalDll, "mciLoadCommandResource");
			originalmciDriverNotify = GetProcAddress(gl_hOriginalDll, "mciDriverNotify");
			originalmciDriverYield = GetProcAddress(gl_hOriginalDll, "mciDriverYield");
			originalmciGetCreatorTask = GetProcAddress(gl_hOriginalDll, "mciGetCreatorTask");
			originalmciGetDeviceIDA = GetProcAddress(gl_hOriginalDll, "mciGetDeviceIDA");
			originalmciGetDeviceIDFromElementIDA = GetProcAddress(gl_hOriginalDll, "mciGetDeviceIDFromElementIDA");
			originalmciGetDeviceIDFromElementIDW = GetProcAddress(gl_hOriginalDll, "mciGetDeviceIDFromElementIDW");
			originalmciGetDeviceIDW = GetProcAddress(gl_hOriginalDll, "mciGetDeviceIDW");
			originalmciGetDriverData = GetProcAddress(gl_hOriginalDll, "mciGetDriverData");
			originalmciGetYieldProc = GetProcAddress(gl_hOriginalDll, "mciGetYieldProc");
			originalmciSetDriverData = GetProcAddress(gl_hOriginalDll, "mciSetDriverData");
			originalmciSetYieldProc = GetProcAddress(gl_hOriginalDll, "mciSetYieldProc");
			originalPlaySoundA = GetProcAddress(gl_hOriginalDll, "PlaySoundA");
			originalsndPlaySoundA = GetProcAddress(gl_hOriginalDll, "sndPlaySoundA");
			originalsndPlaySoundW = GetProcAddress(gl_hOriginalDll, "sndPlaySoundW");
			originalWOWAppExit = GetProcAddress(gl_hOriginalDll, "WOWAppExit");
			originalmmsystemGetVersion = GetProcAddress(gl_hOriginalDll, "mmsystemGetVersion");
		}

		if (configGameId == 60)
		{
			DWORD ProcessID = GetPrivateProfileInt(TEXT("Settings"), TEXT("ProcessID"), 0, settingsFilename);

			if (IsProcessRunning(ProcessID))
				break;

			GameProcessID = MyGetProcessId(L"flycast.exe");

			if (GameProcessID)
				WritePrivateProfileStringA("Settings", "ProcessID", (char*)(std::to_string(GameProcessID)).c_str(), ".\\FFBPlugin.ini");
		}

		if (processName.find("FFBPluginGUI.exe") != std::string::npos)
		{
			hlp.log("hooked FFBPluginGUI.exe, aborting");
			break;
		}

		SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

		hlp.log("creating ffb loop thread...");
		CreateFFBLoopThread();
		if (BeepWhenHook)
			MessageBeep(MB_ICONASTERISK);
		break;

	case DLL_THREAD_ATTACH:
		hlp.log("dll thread attach");
		break;

	case DLL_THREAD_DETACH:
		hlp.log("dll thread detach");
		break;

	case DLL_PROCESS_DETACH:
		hlp.log("detaching from process:");
		hlp.log((char*)processName.c_str());
		keepRunning = false;

		if (configGameId == 60)
			WritePrivateProfileStringA("Settings", "ProcessID", 0, ".\\FFBPlugin.ini");

		if (haptic)
		{
			SDL_HapticStopAll(haptic);
			SDL_HapticClose(haptic);
		}

		if (haptic2)
		{
			SDL_HapticStopAll(haptic2);
			SDL_HapticClose(haptic2);
		}

		if (haptic3)
		{
			SDL_HapticStopAll(haptic3);
			SDL_HapticClose(haptic3);
		}

		if (GameController)
		{
			if (EnableRumble)
				SDL_JoystickRumble(GameController, 0, 0, 0);

			if (EnableRumbleTriggers)
				SDL_JoystickRumbleTriggers(GameController, 0, 0, 0);

			SDL_JoystickClose(GameController);
		}

		if (GameController2)
		{
			if (EnableRumbleDevice2)
				SDL_JoystickRumble(GameController2, 0, 0, 0);

			SDL_JoystickClose(GameController2);
		}

		if (GameController3)
		{
			if (EnableRumbleDevice3)
				SDL_JoystickRumble(GameController3, 0, 0, 0);

			SDL_JoystickClose(GameController3);
		}

		break;
	}

	return result;
}
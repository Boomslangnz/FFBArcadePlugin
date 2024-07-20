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

#include <string>
#include <tchar.h>
#include "Demul.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SDL.h"
#include "../Common Files/CRCCheck.h"
#include "../Common Files/SignatureScanning.h"

//Demul Emulator Games
std::string Nascar("Nascar");
std::string InitialDArcadeStage("Initial D Arcade Stage");
std::string SmashingDrive("Smashing Drive");
std::string MaximumSpeed("Maximum Speed");
std::string FasterThanSpeed("Faster Than Speed");
std::string ATVTrack("ATV Track");

extern void NascarInputsEnabled(Helpers* helpers);
extern void InitialDInputsEnabled(Helpers* helpers);
extern void SmashingDriveInputsEnabled(Helpers* helpers);
extern void ATVTrackInputsEnabled(Helpers* helpers);
extern void FasterThanSpeedInputsEnabled(Helpers* helpers);
extern void MaximumSpeedInputsEnabled(Helpers* helpers);

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
static HINSTANCE gl_padDemul;

extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern bool WaitForGame;
static bool testbuttonA;
static bool servicebuttonA;
static bool startbuttonA;
static bool viewbuttonA;
static bool shiftupA;
static bool shiftdownA;
static bool coinA;
static bool VolumeMute = false;
static bool CRCinit = false;
static bool NOPinit = false;
static bool InputFind = false;
static SDL_Event e;

INT_PTR SteeringAddress;
INT_PTR AcclAddress;
INT_PTR BrakeAddress;
INT_PTR StartViewAddress;
INT_PTR ShiftUpDownAddress;
INT_PTR ServiceTestAddress;
INT_PTR CoinAddress;
INT_PTR CardAddress;
INT_PTR CardAddress2;

static HWND hWnd;

static bool Demul180428 = false;
static bool Demul111117 = false;

extern wchar_t* settingsFilename;
extern int DeviceGUID;
extern int configFeedbackLength;
extern int configGameId;
extern int configMinForce;
extern int configMaxForce;
extern int PowerMode;
extern int EnableRumble;
extern int ReverseRumble;
extern int configFeedbackLength;
extern int configAlternativeMinForceLeft;
extern int configAlternativeMaxForceLeft;
extern int configAlternativeMinForceRight;
extern int configAlternativeMaxForceRight;
extern int EnableForceSpringEffect;
extern int ForceSpringStrength;
extern int AutoCloseWindowError;
extern int EnableDamper;
extern int DamperStrength;
extern int DoubleConstant;
extern int DoubleSine;

static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);

static int configMinForceInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceInitialDDemul"), 0, settingsFilename);
static int configMaxForceInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceInitialDDemul"), 100, settingsFilename);
static int configAlternativeMinForceLeftInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftInitialDDemul"), 0, settingsFilename);
static int configAlternativeMaxForceLeftInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftInitialDDemul"), 100, settingsFilename);
static int configAlternativeMinForceRightInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightInitialDDemul"), 0, settingsFilename);
static int configAlternativeMaxForceRightInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightInitialDDemul"), 100, settingsFilename);
static int PowerModeInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeInitialDDemul"), 0, settingsFilename);
static int configFeedbackLengthInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthInitialDDemul"), 120, settingsFilename);
static int EnableForceSpringEffectInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectInitialDDemul"), 0, settingsFilename);
static int ForceSpringStrengthInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthInitialDDemul"), 0, settingsFilename);
static int EnableDamperInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperInitialDDemul"), 0, settingsFilename);
static int DamperStrengthInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthInitialDDemul"), 100, settingsFilename);
static int DoubleSineInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSineInitialDDemul"), 0, settingsFilename);
static int DoubleConstantInitialDDemul = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleConstantInitialDDemul"), 0, settingsFilename);

static int configMinForceNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceNascarRacing"), 0, settingsFilename);
static int configMaxForceNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceNascarRacing"), 100, settingsFilename);
static int configAlternativeMinForceLeftNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftNascarRacing"), 0, settingsFilename);
static int configAlternativeMaxForceLeftNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftNascarRacing"), 100, settingsFilename);
static int configAlternativeMinForceRightNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightNascarRacing"), 0, settingsFilename);
static int configAlternativeMaxForceRightNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightNascarRacing"), 100, settingsFilename);
static int PowerModeNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeNascarRacing"), 0, settingsFilename);
static int configFeedbackLengthNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthNascarRacing"), 120, settingsFilename);
static int EnableForceSpringEffectNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectNascarRacing"), 0, settingsFilename);
static int ForceSpringStrengthNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthNascarRacing"), 0, settingsFilename);
static int EnableDamperNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperNascarRacing"), 0, settingsFilename);
static int DamperStrengthNascarRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthNascarRacing"), 100, settingsFilename);

static int configMinForceSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSmashingDrive"), 0, settingsFilename);
static int configMaxForceSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSmashingDrive"), 100, settingsFilename);
static int configAlternativeMinForceLeftSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSmashingDrive"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSmashingDrive"), 100, settingsFilename);
static int configAlternativeMinForceRightSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSmashingDrive"), 0, settingsFilename);
static int configAlternativeMaxForceRightSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSmashingDrive"), 100, settingsFilename);
static int PowerModeSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSmashingDrive"), 0, settingsFilename);
static int configFeedbackLengthSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSmashingDrive"), 120, settingsFilename);
static int EnableForceSpringEffectSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSmashingDrive"), 0, settingsFilename);
static int ForceSpringStrengthSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSmashingDrive"), 0, settingsFilename);
static int EnableDamperSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSmashingDrive"), 0, settingsFilename);
static int DamperStrengthSmashingDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSmashingDrive"), 100, settingsFilename);

static int configMinForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceMaximumSpeed"), 0, settingsFilename);
static int configMaxForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceMaximumSpeed"), 100, settingsFilename);
static int configAlternativeMinForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftMaximumSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftMaximumSpeed"), 100, settingsFilename);
static int configAlternativeMinForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightMaximumSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightMaximumSpeed"), 100, settingsFilename);
static int PowerModeMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeMaximumSpeed"), 0, settingsFilename);
static int configFeedbackLengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthMaximumSpeed"), 120, settingsFilename);
static int EnableForceSpringEffectMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectMaximumSpeed"), 0, settingsFilename);
static int ForceSpringStrengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthMaximumSpeed"), 0, settingsFilename);
static int EnableDamperMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperMaximumSpeed"), 0, settingsFilename);
static int DamperStrengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthMaximumSpeed"), 100, settingsFilename);

static int configMinForceFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceFasterSpeed"), 0, settingsFilename);
static int configMaxForceFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceFasterSpeed"), 100, settingsFilename);
static int configAlternativeMinForceLeftFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftFasterSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceLeftFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftFasterSpeed"), 100, settingsFilename);
static int configAlternativeMinForceRightFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightFasterSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceRightFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightFasterSpeed"), 100, settingsFilename);
static int PowerModeFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeFasterSpeed"), 0, settingsFilename);
static int configFeedbackLengthFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthFasterSpeed"), 120, settingsFilename);
static int EnableForceSpringEffectFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectFasterSpeed"), 0, settingsFilename);
static int ForceSpringStrengthFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthFasterSpeed"), 0, settingsFilename);
static int EnableDamperFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperFasterSpeed"), 0, settingsFilename);
static int DamperStrengthFasterSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthFasterSpeed"), 100, settingsFilename);

static int configMinForceATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceATVTrack"), 0, settingsFilename);
static int configMaxForceATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceATVTrack"), 100, settingsFilename);
static int configAlternativeMinForceLeftATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftATVTrack"), 0, settingsFilename);
static int configAlternativeMaxForceLeftATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftATVTrack"), 100, settingsFilename);
static int configAlternativeMinForceRightATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightATVTrack"), 0, settingsFilename);
static int configAlternativeMaxForceRightATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightATVTrack"), 100, settingsFilename);
static int PowerModeATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeATVTrack"), 0, settingsFilename);
static int configFeedbackLengthATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthATVTrack"), 120, settingsFilename);
static int EnableForceSpringEffectATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectATVTrack"), 0, settingsFilename);
static int ForceSpringStrengthATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthATVTrack"), 0, settingsFilename);
static int EnableDamperATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperATVTrack"), 0, settingsFilename);
static int DamperStrengthATVTrack = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthATVTrack"), 100, settingsFilename);

static bool NascarRunning = false;
static bool InitialDRunning = false;
static bool SmashingDriveRunning = false;
static bool MaximumSpeedRunning = false;
static bool FasterThanSpeedRunning = false;
static bool ATVTrackRunning = false;
static bool FFBGameInit = false;
static bool KickStartWait = false;
static bool WindowSearch = false;

static INT_PTR FFBAddress;
static int ffnascar = 0;
static int fffaster = 0;

char* romnameDemul;

int nascar(int ffnas) {
	switch (ffnas) {

	case 0x04:
		return 32;
	case 0x84:
		return 31;
	case 0x44:
		return 30;
	case 0xC4:
		return 29;
	case 0x24:
		return 28;
	case 0xA4:
		return 27;
	case 0x64:
		return 26;
	case 0xE4:
		return 25;
	case 0x14:
		return 24;
	case 0x94:
		return 23;
	case 0x54:
		return 22;
	case 0xD4:
		return 21;
	case 0x34:
		return 20;
	case 0xB4:
		return 19;
	case 0x74:
		return 18;
	case 0xF4:
		return 17;

	case 0xFC:
		return 16;
	case 0x7C:
		return 15;
	case 0xBC:
		return 14;
	case 0x3C:
		return 13;
	case 0xDC:
		return 12;
	case 0x5C:
		return 11;
	case 0x9C:
		return 10;
	case 0x1C:
		return 9;
	case 0xEC:
		return 8;
	case 0x6C:
		return 7;
	case 0xAC:
		return 6;
	case 0x2C:
		return 5;
	case 0xCC:
		return 4;
	case 0x4C:
		return 3;
	case 0x8C:
		return 2;
	case 0x0C:
		return 1;
	default:
		return 0;
	}
}

int fasterspeed(int ffspeed) {
	switch (ffspeed) {
	case 0x1F:
		return 22;
	case 0x1D:
		return 21;
	case 0x1B:
		return 20;
	case 0x19:
		return 19;
	case 0x17:
		return 18;
	case 0x15:
		return 17;
	case 0x13:
		return 16;
	case 0x11:
		return 15;
	case 0x0F:
		return 14;
	case 0x0D:
		return 13;
	case 0x0B:
		return 12;

	case 0x1E:
		return 11;
	case 0x1C:
		return 10;
	case 0x1A:
		return 9;
	case 0x18:
		return 8;
	case 0x16:
		return 7;
	case 0x14:
		return 6;
	case 0x12:
		return 5;
	case 0x10:
		return 4;
	case 0x0E:
		return 3;
	case 0x0C:
		return 2;
	case 0x0A:
		return 1;
	default:
		return 0;
	}
}

static int InitialDFFBLoop()
{
	DWORD FFB = myHelpers->ReadInt32(FFBAddress, false);
	WORD FFBStr = myHelpers->ReadWord(FFBAddress + 0x02, false);

	BYTE* ffb = reinterpret_cast<BYTE*>(&FFB);

	if (KickStartWait)
	{
		if (ffb[0] == 0x80 && ffb[2] == 0x01)
		{
			myTriggers->Spring(1.0);
		}

		if (ffb[0] == 0x85 && ffb[1] > 0x00 && FFBStr > 0x00)
		{
			double percentForce = FFBStr / 32767.0;
			double Period = ffb[1] / 127.0 * 120.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, percentForce, percentLength);
			myTriggers->Sine(static_cast<int>(Period), 0, percentForce);
		}

		if (ffb[0] == 0x86 && FFBStr)
		{
			double percentForce = FFBStr / 32767.0;
			double percentLength = 100;
			myTriggers->Spring(percentForce);
		}

		if (ffb[0] == 0x84 && FFBStr > 0x00)
		{
			if (ffb[1] == 0x00)
			{
				double percentForce = (32767.0 - FFBStr) / 32767.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if (ffb[1] == 0x01)
			{
				double percentForce = (FFBStr / 32767.0);
				double percentLength = 100;
				myTriggers->Rumble(0, percentForce, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
	return 0;
}

static int SmashingDriveFFBLoop()
{
	INT_PTR FFBSmashingDrive = myHelpers->ReadIntPtr(FFBAddress, false);

	if ((FFBSmashingDrive > 0x01) && (FFBSmashingDrive < 0x100))
	{
		double percentForce = FFBSmashingDrive / 255.0;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((FFBSmashingDrive > 0x1FF) && (FFBSmashingDrive < 0xFF01))
	{
		double percentForce = (FFBSmashingDrive / 65280.0);
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static int ATVTrackFFBLoop()
{
	float FFBATVTrack = myHelpers->ReadFloat32(FFBAddress, false);

	if (FFBATVTrack > 0)
	{
		double percentForce = FFBATVTrack;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if (FFBATVTrack < 0)
	{
		double percentForce = -FFBATVTrack;
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static int FasterThanSpeedFFBLoop()
{
	UINT8 ffbfaster = myHelpers->ReadByte(FFBAddress, false);
	fffaster = fasterspeed(ffbfaster);

	if ((fffaster > 0x0B) && (fffaster < 0x17))
	{
		double percentForce = (fffaster - 11) / 11.0;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((fffaster > 0x00) && (fffaster < 0x0C))
	{
		double percentForce = fffaster / 11.0;
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static int MaximumSpeedFFBLoop()
{
	UINT8 FFBMaximumSpeed = myHelpers->ReadIntPtr(FFBAddress, false);
	UINT8 FFBMaximumSpeed2 = myHelpers->ReadByte(FFBAddress + 0x01, false);

	if ((FFBMaximumSpeed > 0x7F) && (FFBMaximumSpeed < 0x100) && (FFBMaximumSpeed2 == 0xFF))
	{
		double percentForce = (256 - FFBMaximumSpeed) / 128.0;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((FFBMaximumSpeed > 0x00) && (FFBMaximumSpeed < 0x81) && (FFBMaximumSpeed2 == 0x00))
	{
		double percentForce = FFBMaximumSpeed / 128.0;
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static int NascarFFBLoop()
{
	UINT8 ffnas = myHelpers->ReadByte(FFBAddress, false);
	ffnascar = nascar(ffnas);

	if ((ffnascar > 0x10) && (ffnascar < 0x21))
	{
		double percentForce = (ffnascar - 16) / 16.0;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((ffnascar > 0x00) && (ffnascar < 0x11))
	{
		double percentForce = (17 - ffnascar) / 16.0;
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static DWORD WINAPI NascarRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		NascarFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI InitialDRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		InitialDFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI SmashingDriveRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		SmashingDriveFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI ATVTrackRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		ATVTrackFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI FasterThanSpeedRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		FasterThanSpeedFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI MaximumSpeedRunningLoop(LPVOID lpParam)
{
	while (true)
	{
		MaximumSpeedFFBLoop();
		Sleep(16);
	}
}

static DWORD WINAPI CloseErrorThread(LPVOID lpParam)
{
	SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	VolumeMute = true;
	return 0;
}

static BOOL CALLBACK FindWindowBySubstr(HWND hwnd, LPARAM substring)
{
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];

	if (GetWindowText(hwnd, windowTitle, TITLE_SIZE))
	{
		if (_tcsstr(windowTitle, LPCTSTR(substring)) != NULL)
		{
			return false;
		}
	}
	return true;
}

const TCHAR substring[] = TEXT("FPS");
const TCHAR substring0[] = TEXT("spg");
const TCHAR substring1[] = TEXT("NASCAR");
const TCHAR substring2[] = TEXT("Initial D Arcade Stage");
const TCHAR substring3[] = TEXT("Smashing Drive");
const TCHAR substring4[] = TEXT("Maximum Speed");
const TCHAR substring5[] = TEXT("Faster Than Speed");
const TCHAR substring6[] = TEXT("ATV Track");

void Demul::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;

	if (AutoCloseWindowError == 1)
	{
		if (!VolumeMute)
		{
			//Remove window error popup
			hWnd = FindWindowA(0, ("padDemul"));
			if (hWnd > NULL)
			{
				CreateThread(NULL, 0, CloseErrorThread, NULL, 0, NULL);
			}
		}
	}

	if (!CRCinit)
	{
		if (InputDeviceWheelEnable == 1)
		{
			static char newCrc[0x400];
			// Craft CRC detection without virtual address
			memcpy(newCrc, GetModuleHandle(nullptr), 0x400);
			DWORD pePTR = *(DWORD*)(newCrc + 0x3C);

			// Overwrite ImageBase with 8 bytes of 0
			*(DWORD*)(newCrc + pePTR + 0x18) = 0x00000000;
			*(DWORD*)(newCrc + pePTR + 0x18 + 4) = 0x00000000;
#ifdef _AMD64_
			* (DWORD*)(newCrc + pePTR + 50) = 0x00000000;
#endif
			* (DWORD*)(newCrc + pePTR + 54) = 0x00000000;
			uint32_t newCrcResult = GetCRC32(newCrc, 0x400);
			switch (newCrcResult)
			{
			case 0x875a800d:
				Demul180428 = true;
				break;
			case 0x04f85ceb:
				Demul111117 = true;
				break;
			}

			if ((Demul180428) || (Demul111117))
			{
				CRCinit = true;
			}
		}
	}

	if (NOPinit)
	{
		gl_padDemul = LoadLibraryA("padDemul.dll");

		if (Demul180428)
		{
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x27013, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26F31, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x271F7, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x276BD, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x272FF, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26FBD, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x27685, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x276A2, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26FEC, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x270A3, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26FE1, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x27048, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x2703A, 4, false);
		}

		if (Demul111117)
		{
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26B31, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26DD0, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x272AD, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26B9C, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x27275, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x27292, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26BC2, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26BBA, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26BE3, 3, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26C1E, 4, false);
			helpers->WriteNop((INT_PTR)gl_padDemul + 0x26C10, 4, false);
		}

		if (NascarRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			helpers->WriteByte(AcclAddress, 0x00, false);
			helpers->WriteByte(BrakeAddress, 0x00, false);
			helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
			NascarInputsEnabled(helpers);
		}

		if (InitialDRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			helpers->WriteByte(AcclAddress, 0x00, false);
			helpers->WriteByte(BrakeAddress, 0x00, false);
			InitialDInputsEnabled(helpers);
		}

		if (SmashingDriveRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			SmashingDriveInputsEnabled(helpers);
		}

		if (ATVTrackRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			helpers->WriteByte(AcclAddress, 0x00, false);
			ATVTrackInputsEnabled(helpers);
		}

		if (FasterThanSpeedRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			helpers->WriteByte(AcclAddress, 0x00, false);
			helpers->WriteByte(BrakeAddress, 0x00, false);
			FasterThanSpeedInputsEnabled(helpers);
		}

		if (MaximumSpeedRunning)
		{
			helpers->WriteByte(SteeringAddress, 0x80, false);
			helpers->WriteByte(AcclAddress, 0x00, false);
			helpers->WriteByte(BrakeAddress, 0x00, false);
			MaximumSpeedInputsEnabled(helpers);
		}
	}
		
	if (EnableForceSpringEffect == 1)
	{
		triggers->Springi(ForceSpringStrength / 100.0);
	}

	if (!WindowSearch)
	{
		if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring) || !EnumWindows(FindWindowBySubstr, (LPARAM)substring0))
		{
			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring1))
			{
				configMinForce = configMinForceNascarRacing;
				configMaxForce = configMaxForceNascarRacing;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftNascarRacing;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftNascarRacing;
				configAlternativeMinForceRight = configAlternativeMinForceRightNascarRacing;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightNascarRacing;
				configFeedbackLength = configFeedbackLengthNascarRacing;
				PowerMode = PowerModeNascarRacing;
				EnableForceSpringEffect = EnableForceSpringEffectNascarRacing;
				ForceSpringStrength = ForceSpringStrengthNascarRacing;
				EnableDamper = EnableDamperNascarRacing;
				DamperStrength = DamperStrengthNascarRacing;

				romnameDemul = "Nascar";

				WaitForGame = true;
				NascarRunning = true;
				WindowSearch = true;	
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring2))
			{
				configMinForce = configMinForceInitialDDemul;
				configMaxForce = configMaxForceInitialDDemul;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftInitialDDemul;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftInitialDDemul;
				configAlternativeMinForceRight = configAlternativeMinForceRightInitialDDemul;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightInitialDDemul;
				configFeedbackLength = configFeedbackLengthInitialDDemul;
				PowerMode = PowerModeInitialDDemul;
				EnableForceSpringEffect = EnableForceSpringEffectInitialDDemul;
				ForceSpringStrength = ForceSpringStrengthInitialDDemul;
				EnableDamper = EnableDamperInitialDDemul;
				DamperStrength = DamperStrengthInitialDDemul;
				DoubleSine = DoubleSineInitialDDemul;
				DoubleConstant = DoubleConstantInitialDDemul;

				romnameDemul = "Initial D Arcade Stage";

				WaitForGame = true;
				InitialDRunning = true;
				WindowSearch = true;	
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring3))
			{
				configMinForce = configMinForceSmashingDrive;
				configMaxForce = configMaxForceSmashingDrive;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSmashingDrive;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSmashingDrive;
				configAlternativeMinForceRight = configAlternativeMinForceRightSmashingDrive;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSmashingDrive;
				configFeedbackLength = configFeedbackLengthSmashingDrive;
				PowerMode = PowerModeSmashingDrive;
				EnableForceSpringEffect = EnableForceSpringEffectSmashingDrive;
				ForceSpringStrength = ForceSpringStrengthSmashingDrive;
				EnableDamper = EnableDamperSmashingDrive;
				DamperStrength = DamperStrengthSmashingDrive;

				romnameDemul = "Smashing Drive";

				WaitForGame = true;
				SmashingDriveRunning = true;
				WindowSearch = true;	
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring4))
			{
				configMinForce = configMinForceMaximumSpeed;
				configMaxForce = configMaxForceMaximumSpeed;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftMaximumSpeed;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftMaximumSpeed;
				configAlternativeMinForceRight = configAlternativeMinForceRightMaximumSpeed;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightMaximumSpeed;
				configFeedbackLength = configFeedbackLengthMaximumSpeed;
				PowerMode = PowerModeMaximumSpeed;
				EnableForceSpringEffect = EnableForceSpringEffectMaximumSpeed;
				ForceSpringStrength = ForceSpringStrengthMaximumSpeed;
				EnableDamper = EnableDamperMaximumSpeed;
				DamperStrength = DamperStrengthMaximumSpeed;

				romnameDemul = "Maximum Speed";

				WaitForGame = true;
				MaximumSpeedRunning = true;
				WindowSearch = true;
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring5))
			{
				configMinForce = configMinForceFasterSpeed;
				configMaxForce = configMaxForceFasterSpeed;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftFasterSpeed;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftFasterSpeed;
				configAlternativeMinForceRight = configAlternativeMinForceRightFasterSpeed;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightFasterSpeed;
				configFeedbackLength = configFeedbackLengthFasterSpeed;
				PowerMode = PowerModeFasterSpeed;
				EnableForceSpringEffect = EnableForceSpringEffectFasterSpeed;
				ForceSpringStrength = ForceSpringStrengthFasterSpeed;
				EnableDamper = EnableDamperFasterSpeed;
				DamperStrength = DamperStrengthFasterSpeed;

				romnameDemul = "Faster Than Speed";

				WaitForGame = true;
				FasterThanSpeedRunning = true;
				WindowSearch = true;
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring6))
			{
				configMinForce = configMinForceATVTrack;
				configMaxForce = configMaxForceATVTrack;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftATVTrack;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftATVTrack;
				configAlternativeMinForceRight = configAlternativeMinForceRightATVTrack;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightATVTrack;
				configFeedbackLength = configFeedbackLengthATVTrack;
				PowerMode = PowerModeATVTrack;
				EnableForceSpringEffect = EnableForceSpringEffectATVTrack;
				ForceSpringStrength = ForceSpringStrengthATVTrack;
				EnableDamper = EnableDamperATVTrack;
				DamperStrength = DamperStrengthATVTrack;

				romnameDemul = "ATV Track";

				WaitForGame = true;
				ATVTrackRunning = true;
				WindowSearch = true;
			}
		}
	}

	if (NascarRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(5000);
			aAddy2 = PatternScan("\x13\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x50\x72\x6F\x64\x75\x63\x65\x64\x20\x42\x79\x20", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
			FFBAddress = (int)aAddy2 - 0x2F0;
			CreateThread(NULL, 0, NascarRunningLoop, NULL, 0, NULL);
			FFBGameInit = true;
		}
		else
		{
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x11\x00\x16\x1F\x05\x04\x1D\x0D\x07\x12\x18\x14\x02\x13\x09\x15\x0E\x19\x01\x1C\x08\x1A\x17\x03\x0F\x1B\x00\x10\x0A\x0B\x0C\x06\x01", "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy + 0x01, false);
					if (CheckaAddy == 0x1E)
					{
						SteeringAddress = (int)aAddy - 0xC45;
						AcclAddress = (int)aAddy - 0xC0D;
						BrakeAddress = (int)aAddy - 0xBD5;
						ShiftUpDownAddress = (int)aAddy - 0xDEA;
						ServiceTestAddress = (int)aAddy - 0x108A;
						StartViewAddress = (int)aAddy - 0xF8E;
						CoinAddress = (int)aAddy - 0xFE2;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}	
	}

	if (InitialDRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(6000);
			aAddy2 = PatternScan("\x88\xA9\x00\x09", "xxxx");
			FFBAddress = (int)aAddy2 + 0x01;
			FFBGameInit = true;
		}

		if (!KickStartWait)
		{
			if (FFBAddress > 0)
			{
				Sleep(6000);
				CreateThread(NULL, 0, InitialDRunningLoop, NULL, 0, NULL);
				KickStartWait = true;
			}
		}
		else
		{ 
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xFF\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x20", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy - 0x2A0, false);
					if (CheckaAddy == 0x01)
					{
						SteeringAddress = (int)aAddy - 0x85;
						AcclAddress = (int)aAddy - 0x4D;
						BrakeAddress = (int)aAddy - 0x15;
						StartViewAddress = (int)aAddy - 0x14A;
						ShiftUpDownAddress = (int)aAddy - 0xDA;
						ServiceTestAddress = (int)aAddy - 0x246;
						CoinAddress = (int)aAddy - 0x19E;
						CardAddress = (int)aAddy + 0x3E;
						CardAddress2 = (int)aAddy + 0x22;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}
	}
		
	if (SmashingDriveRunning)
	{
		if (!FFBGameInit)
		{	
			Sleep(5000);
			aAddy2 = PatternScan("\xC0\xF3\x51\x00\x60\x9A\x2C\x01", "xxxxxxxx");
			
			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 - 0x0E, false);
			if (CheckAddy == 0x07)
			{
				FFBAddress = (int)aAddy2 - 0xD0;
				CreateThread(NULL, 0, SmashingDriveRunningLoop, NULL, 0, NULL);
				FFBGameInit = true;
			}
		}
		else
		{
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x0C\x00\x0E\x0F\x08\x09\x0A\x0B\x1C\x1D\x1E\x1F\x18\x19\x1A\x1B\x04\x05\x06\x07\x00\x01\x02\x03\x14\x15\x16\x17\x10\x11", "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy + 0x01, false);
					if (CheckaAddy == 0x0D)
					{
						SteeringAddress = (int)aAddy - 0x80A;
						ServiceTestAddress = (int)aAddy - 0x95A;
						AcclAddress = (int)aAddy - 0x896;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}
	}

	if (MaximumSpeedRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(10000);
			aAddy2 = PatternScan("\x48\x03\x00\x00\xE0\x01\x00\x00\x2C\x01\x00\x00\xB4\x00\x00\x00\x00\x00\x00\x00\x20\xFE\xFF\xFF", "xxxxxxxxxxxxxxxxxxxxxxxx");

			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 + 0x21, false);
			if (CheckAddy == 0xFC)
			{
				FFBAddress = (int)aAddy2 + 0x18;
				CreateThread(NULL, 0, MaximumSpeedRunningLoop, NULL, 0, NULL);
				FFBGameInit = true;
			}
		}
		else
		{
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x14\x00\x05\x10\x0C\x18\x19\x04\x0B\x11\x0D\x1C\x1D\x02\x1F\x08\x06\x17\x0A\x0E\x16\x1A\x07\x15\x0F\x13\x01\x12\x03\x1E\x09", "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy + 0x01, false);
					if (CheckaAddy == 0x1B)
					{
						SteeringAddress = (int)aAddy - 0x1316;
						AcclAddress = (int)aAddy - 0x12DE;
						BrakeAddress = (int)aAddy - 0x12A6;
						ShiftUpDownAddress = (int)aAddy - 0x14F2;
						ServiceTestAddress = (int)aAddy - 0x14F1;
						CoinAddress = (int)aAddy - 0x136A;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}
	}

	if (FasterThanSpeedRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(10000);
			aAddy2 = PatternScan("\x01\x00\x10\x00\x00\x00\x00\x00\x00\x2F\x76", "xxxxxxxxxxx");

			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 + 0x0E, false);
			if (CheckAddy == 0x0C)
			{
				FFBAddress = (int)aAddy2 + 0x0F;
				CreateThread(NULL, 0, FasterThanSpeedRunningLoop, NULL, 0, NULL);
				FFBGameInit = true;
			}
		}
		else
		{
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x14\x00\x05\x10\x0C\x18\x19\x04\x0B\x11\x0D\x1C\x1D\x02\x1F\x08\x06\x17\x0A\x0E\x16\x1A\x07\x15\x0F\x13\x01\x12\x03\x1E\x09", "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy + 0x01, false);
					if (CheckaAddy == 0x1B)
					{
						SteeringAddress = (int)aAddy - 0x1316;
						AcclAddress = (int)aAddy - 0x12DE;
						BrakeAddress = (int)aAddy - 0x12A6;
						ShiftUpDownAddress = (int)aAddy - 0x14F2;
						ServiceTestAddress = (int)aAddy - 0x14F1;
						CoinAddress = (int)aAddy - 0x136A;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}	
	}

	if (ATVTrackRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(15000);
			aAddy2 = PatternScan("\x49\x55\x4C\x00\x00\x00\x05", "xxxxxxx");
			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 - 0x04, false);
			if (CheckAddy == 0x1E)
			{
				FFBAddress = (int)aAddy2 - 0x1A;
				CreateThread(NULL, 0, ATVTrackRunningLoop, NULL, 0, NULL);
				FFBGameInit = true;
			}
		}
		else
		{ 
			if (InputDeviceWheelEnable == 1)
			{
				if (!InputFind)
				{
					aAddy = PatternScan("\x11\x00\x16\x1F\x05\x04\x1D\x0D\x07\x12\x18\x14\x02\x13\x09\x15\x0E\x19\x01\x1C\x08\x1A\x17\x03\x0F\x1B\x00\x10\x0A\x0B\x0C\x06\x01", "x?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
					UINT8 CheckaAddy = helpers->ReadByte((int)aAddy + 0x01, false);
					if (CheckaAddy == 0x1E)
					{
						SteeringAddress = (int)aAddy - 0xA16;
						AcclAddress = (int)aAddy - 0x9DE;
						BrakeAddress = (int)aAddy - 0xABE;
						ServiceTestAddress = (int)aAddy - 0xB82;
						NOPinit = true;
						InputFind = true;
					}
				}
			}
		}
	}
}
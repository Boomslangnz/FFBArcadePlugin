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
#include "../Common Files/SignatureScanning.h"

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

static int configMinForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSmashingDrive"), 0, settingsFilename);
static int configMaxForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSmashingDrive"), 100, settingsFilename);
static int configAlternativeMinForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSmashingDrive"), 0, settingsFilename);
static int configAlternativeMaxForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSmashingDrive"), 100, settingsFilename);
static int configAlternativeMinForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSmashingDrive"), 0, settingsFilename);
static int configAlternativeMaxForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSmashingDrive"), 100, settingsFilename);
static int PowerModeMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSmashingDrive"), 0, settingsFilename);
static int configFeedbackLengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSmashingDrive"), 120, settingsFilename);
static int EnableForceSpringEffectMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSmashingDrive"), 0, settingsFilename);
static int ForceSpringStrengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSmashingDrive"), 0, settingsFilename);

static bool NascarRunning = false;
static bool InitialDRunning = false;
static bool SmashingDriveRunning = false;
static bool MaximumSpeedRunning = false;
static bool FFBGameInit = false;
static bool KickStartWait = false;
static bool WindowSearch = false;

static INT_PTR FFBAddress;
static int ffnascar = 0;

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

void Demul::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

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

				MaximumSpeedRunning = true;
				WindowSearch = true;
			}
		}
	}

	if (NascarRunning)
	{
		if (!FFBGameInit)
		{
			FFBGameInit = true;
			aAddy2 = PatternScan("\x13\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x50\x72\x6F\x64\x75\x63\x65\x64\x20\x42\x79\x20", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
			FFBAddress = (int)aAddy2 - 0x2F0;
		}

		UINT8 ffnas = helpers->ReadByte(FFBAddress, false);
		std::string ffs = std::to_string(ffnas);
		helpers->log((char*)ffs.c_str());
		helpers->log("got value: ");
		ffnascar = nascar(ffnas);

		if ((ffnascar > 0x10) && (ffnascar < 0x21))
		{
			helpers->log("moving wheel right");
			double percentForce = (ffnascar - 16) / 16.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ffnascar > 0x00) && (ffnascar < 0x11))
		{
			helpers->log("moving wheel left");
			double percentForce = (17 - ffnascar) / 16.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}

	if (InitialDRunning)
	{
		if (!FFBGameInit)
		{
			Sleep(6000);
			FFBGameInit = true;
			aAddy2 = PatternScan("\x88\xA9\x00\x09", "xxxx");
			FFBAddress = (int)aAddy2 + 0x01;
		}

		UINT8 ff1 = helpers->ReadByte(FFBAddress, false);
		UINT8 ff2 = helpers->ReadByte(FFBAddress + 0x01, false);
		UINT8 ff3 = helpers->ReadByte(FFBAddress + 0x02, false);

		std::string ffs = std::to_string(ff1);
		helpers->log((char*)ffs.c_str());
		helpers->log("got value: ");

		if (!KickStartWait)
		{
			if (FFBAddress > 0)
			{
				Sleep(6000);
				KickStartWait = true;
			}
		}

		if (KickStartWait)
		{
			if ((ff1 == 0x80) && (ff3 == 0x01))
			{
				triggers->Spring(1.0);
			}

			if ((ff1 == 0x85) && (ff2 == 0x3F) && (ff3 > 0x00) && (ff3 < 0x30))
			{
				double percentForce = ff3 / 47.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, percentForce, percentLength);
				triggers->Sine(40, 0, percentForce);
			}

			if ((ff1 == 0x86) && (ff2 == 0x02) && (ff3 > 0x09) && (ff3 < 0x3C))
			{
				double percentForce = (60 - ff3) / 43.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}

			if ((ff1 == 0x84) && (ff2 == 0x00) && (ff3 > 0x37) && (ff3 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (128 - ff3) / 72.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff1 == 0x84) && (ff2 == 0x01) && (ff3 > 0x00) && (ff3 < 0x49))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff3 / 72.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}

	if (SmashingDriveRunning)
	{
		if (!FFBGameInit)
		{	
			aAddy2 = PatternScan("\xC0\xF3\x51\x00\x60\x9A\x2C\x01", "xxxxxxxx");
			
			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 - 0x0E, false);
			if (CheckAddy == 0x07)
			{
				FFBAddress = (int)aAddy2 - 0xD0;
				FFBGameInit = true;
			}
		}
		else
		{
			INT_PTR FFBSmashingDrive = helpers->ReadIntPtr(FFBAddress, false);

			std::string ffs = std::to_string(FFBSmashingDrive);
			helpers->log((char*)ffs.c_str());
			helpers->log("got value: ");

			if ((FFBSmashingDrive > 0x01) && (FFBSmashingDrive < 0x100))
			{
				helpers->log("moving wheel right");
				double percentForce = FFBSmashingDrive / 255.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((FFBSmashingDrive > 0x1FF) && (FFBSmashingDrive < 0xFF01))
			{
				helpers->log("moving wheel left");
				double percentForce = (FFBSmashingDrive / 65280.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}

	if (MaximumSpeedRunning)
	{
		if (!FFBGameInit)
		{
			aAddy2 = PatternScan("\x48\x03\x00\x00\xE0\x01\x00\x00\x2C\x01\x00\x00\xB4\x00\x00\x00\x00\x00\x00\x00\x20\xFE\xFF\xFF", "xxxxxxxxxxxxxxxxxxxxxxxx");

			UINT8 CheckAddy = helpers->ReadByte((int)aAddy2 + 0x21, false);
			if (CheckAddy == 0xFC)
			{
				FFBAddress = (int)aAddy2 + 0x18;
				FFBGameInit = true;
			}
		}
		else
		{
			UINT8 FFBMaximumSpeed = helpers->ReadIntPtr(FFBAddress, false);
			UINT8 FFBMaximumSpeed2 = helpers->ReadByte(FFBAddress + 0x01, false);

			std::string ffs = std::to_string(FFBMaximumSpeed);
			helpers->log((char*)ffs.c_str());
			helpers->log("got value: ");

			if ((FFBMaximumSpeed > 0x7F) && (FFBMaximumSpeed < 0x100) && (FFBMaximumSpeed2 == 0xFF))
			{
				helpers->log("moving wheel right");
				double percentForce = (256 - FFBMaximumSpeed) / 128.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((FFBMaximumSpeed > 0x00) && (FFBMaximumSpeed < 0x81) && (FFBMaximumSpeed2 == 0x00))
			{
				helpers->log("moving wheel left");
				double percentForce = FFBMaximumSpeed / 128.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
}
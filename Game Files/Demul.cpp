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

static bool NascarRunning = false;
static bool InitialDRunning = false;
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

void Demul::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!WindowSearch)
	{
		if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring) || !EnumWindows(FindWindowBySubstr, (LPARAM)substring0))
		{
			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring1))
			{
				NascarRunning = true;
				WindowSearch = true;
			}

			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring2))
			{
				InitialDRunning = true;
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
			helpers->log("moving wheel left");
			double percentForce = (ffnascar - 16) / 16.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ffnascar > 0x00) && (ffnascar < 0x11))
		{
			helpers->log("moving wheel right");
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
				helpers->log("moving wheel left");
				double percentForce = (128 - ff3) / 72.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff1 == 0x84) && (ff2 == 0x01) && (ff3 > 0x00) && (ff3 < 0x49))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff3 / 72.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
}
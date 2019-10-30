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

BOOL CALLBACK FindWindowBySubstr(HWND hwnd, LPARAM substring)
{
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];

	if (GetWindowText(hwnd, windowTitle, TITLE_SIZE))
	{
		//_tprintf(TEXT("%s\n"), windowTitle);
		// Uncomment to print all windows being enumerated
		if (_tcsstr(windowTitle, LPCTSTR(substring)) != NULL)
		{
			// We found the window! Stop enumerating.
			return false;
		}
	}
	return true; // Need to continue enumerating windows
}

void Demul::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {

	const TCHAR substring[] = TEXT("NASCAR");
	EnumWindows(FindWindowBySubstr, (LPARAM)substring);
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);

	{
		int ffnascar = 0;
		{
			if (!EnumWindows(FindWindowBySubstr, (LPARAM)substring))
			{
				UINT8 ffnas = helpers->ReadByte(0x30060C, /* isRelativeOffset */ true); //Nascar Arcade
				std::string ffs = std::to_string(ffnas);
				helpers->log((char *)ffs.c_str());
				helpers->log("got value: ");
				ffnascar = nascar(ffnas);

				if (FFBMode == 0)
				{
					if ((ffnascar > 16) & (ffnascar < 33))
					{
						helpers->log("moving wheel left");
						double percentForce = (ffnascar - 16) / 16.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					else if ((ffnascar > 0) & (ffnascar < 17))
					{
						helpers->log("moving wheel right");
						double percentForce = (17 - ffnascar) / 16.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
				}
				else
				{
					if ((ffnascar > 16) & (ffnascar < 33))
					{
						helpers->log("moving wheel left");
						double percentForce = (ffnascar - 16) / 16.0;
						double percentLength = 100;
						triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
					}
					else if ((ffnascar > 0) & (ffnascar < 17))
					{
						helpers->log("moving wheel right");
						double percentForce = (17 - ffnascar) / 16.0;
						double percentLength = 100;
						triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
					}
				}
			}
		}
	}

}


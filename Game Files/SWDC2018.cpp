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
#include "SWDC2018.h"

extern int EnableDamper;
extern int DamperStrength;

static bool VersionFound;
static bool Version103;
static bool Version230;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);

static UINT8 ff1;
static UINT8 ff2;
static UINT8 ff3;

static const char* SDDS = "SDDS";

static void getSDDS103(char* Name)
{
	if (strcmp(Name, SDDS) == 0)
	{
		Version103 = true;
		VersionFound = true;
	}
}

static void getSDDS230(char* Name)
{
	if (strcmp(Name, SDDS) == 0)
	{
		Version230 = true;
		VersionFound = true;
	}
}

void SWDC::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
	{
		ExitProcess(0);
	}

	if (!VersionFound)
	{
		DWORD SDDS103 = helpers->ReadInt32(0x8E5CBD0, true);
		DWORD SDDS230 = helpers->ReadInt32(0x9BC7B20, true);

		char Version103[256] = { 0 };
		std::memcpy(Version103, &SDDS103, 4);
		std::string myString103(Version103);

		char Version230[256] = { 0 };
		std::memcpy(Version230, &SDDS230, 4);
		std::string myString230(Version230);

		getSDDS103((char*)myString103.c_str());
		getSDDS230((char*)myString230.c_str());
	}
	else
	{
		if (Version103)
		{
			ff1 = helpers->ReadByte(0x8E5CCF4, true);
			ff2 = helpers->ReadByte(0x8E5CCF5, true);
			ff3 = helpers->ReadByte(0x8E5CCF6, true);
		}
		
		if (Version230)
		{
			ff1 = helpers->ReadByte(0x9BC7B18, true);
			ff2 = helpers->ReadByte(0x9BC7B19, true);
			ff3 = helpers->ReadByte(0x9BC7B1A, true);
		}

		if (EnableDamper == 1)
		{
			triggers->Damper(DamperStrength / 100.0);
		}

		if (ff1 == 80)
		{
			triggers->Spring(1.0);
		}
		else if (ff1 == 0x85)
		{
			if ((ff2 > 0x00) && (ff2 < 0x30))
			{
				double percentForce = ff2 / 47.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, percentForce, percentLength);
				triggers->Sine(40, 0, percentForce);
			}
		}
		else if (ff1 == 0x86)
		{
			if ((ff3 > 0x00) && (ff3 < 0x4E))
			{
				double percentForce = ff3 / 77.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
		}
		else if (ff1 == 0x84)
		{
			if ((ff2 == 0x00) && (ff3 > 0x37) && (ff3 < 0x80))
			{
				double percentForce = (128 - ff3) / 72.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff2 == 0x01) && (ff3 > 0x00) && (ff3 < 0x49))
			{
				double percentForce = (ff3 / 72.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else
			{
				if ((ff2 == 0x00) && (ff3 > 0x00) && (ff3 < 0x38))
				{
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ff2 == 0x01) && (ff3 > 0x48))
				{
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}
	}	
}
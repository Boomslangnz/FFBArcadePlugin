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

static DWORD FFB;
static WORD FFBStr;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);

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
		ExitProcess(0);

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
			FFB = helpers->ReadInt32(0x8E5CCF4, true);
			FFBStr = helpers->ReadWord(0x8E5CCF6, true);
		}

		if (Version230)
		{
			FFB = helpers->ReadInt32(0x9BC7B18, true);
			FFBStr = helpers->ReadWord(0x9BC7B1A, true);
		}

		if (EnableDamper)
			triggers->Damper(DamperStrength / 100.0);

		BYTE* ffb = reinterpret_cast<BYTE*>(&FFB);

		if (ffb[0] == 0x80 && ffb[2] == 0x01)
		{
			triggers->Spring(1.0);
		}

		if (ffb[0] == 0x85 && ffb[1] > 0x00 && FFBStr > 0x00)
		{
			double percentForce = FFBStr / 32767.0;
			double Period = ffb[1] / 127.0 * 120.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, percentForce, percentLength);
			triggers->Sine(static_cast<int>(Period), 0, percentForce);
		}

		if (ffb[0] == 0x86 && FFBStr)
		{
			double percentForce = FFBStr / 32767.0;
			double percentLength = 100;
			triggers->Spring(percentForce);
		}

		if (ffb[0] == 0x84 && FFBStr > 0x00)
		{
			if (ffb[1] == 0x00)
			{
				double percentForce = (32767.0 - FFBStr) / 32767.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if (ffb[1] == 0x01)
			{
				double percentForce = (FFBStr / 32767.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
}
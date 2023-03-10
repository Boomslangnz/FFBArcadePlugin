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
#include "ChaseHQ2.h"
extern int EnableDamper;
extern int DamperStrength;
static bool removecel = false;
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int RemoveCelShadedFilter = GetPrivateProfileInt(TEXT("Settings"), TEXT("RemoveCelShadedFilter"), 0, settingsFilename);

int ttx2chasehq2(int ffRaw) {
	switch (ffRaw) {
	case 28672:
		return 30;
	case 24640:
		return 29;
	case 28736:
		return 28;
	case 16624:
		return 27;
	case 30720:
		return 26;
	case 26688:
		return 25;
	case 30784:
		return 24;
	case 24608:
		return 23;
	case 28704:
		return 22;
	case 24672:
		return 21;
	case 28768:
		return 20;
	case 26656:
		return 19;
	case 30752:
		return 18;
	case 26720:
		return 17;
	case 30816:
		return 16;

	case 20480:
		return 15;
	case 16448:
		return 14;
	case 20544:
		return 13;
	case 18432:
		return 12;
	case 22528:
		return 11;
	case 18496:
		return 10;
	case 22592:
		return 9;
	case 16416:
		return 8;
	case 20512:
		return 7;
	case 16480:
		return 6;
	case 20576:
		return 5;
	case 18464:
		return 4;
	case 22560:
		return 3;
	case 18528:
		return 2;
	case 22624:
		return 1;
	default:
		return 0;
	}
}

void ChaseHQ2::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	int ff = 0;
	{
		long ffAddress = helpers->ReadInt32(0x130B558, true);
		int ffRaw = helpers->ReadInt32(ffAddress + 0x45, false);
		int lampArray[8] = { (16384) + 1, 16 ,1024 ,512, 128, 8, 256 }; //The 1 isn't needed but I wasn't sure how to get the 16384 to see the first digit any other way lol
		for (int i = 0; i < 7; i++) {
			if ((ffRaw & lampArray[i]) == lampArray[i]) {
				ffRaw -= lampArray[i];
			}
		};

		ff = ttx2chasehq2(ffRaw);
	}

	if (RemoveCelShadedFilter)
	{
		if (!removecel)
		{
			helpers->WriteNop(0x31FFA, 6, true);
			removecel = true;
		}
		helpers->WriteByte(0x130CB30, 0x00, true); // Remove Cel Shaded Filter
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char*)ffs.c_str());

	if (ff > 15)
	{
		helpers->log("moving wheel right");
		double percentForce = (31 - ff) / 15.0;
		double percentLength = 100;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if (ff > 0)
	{
		helpers->log("moving wheel left");
		double percentForce = (16 - ff) / 15.0;
		double percentLength = 100;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
}
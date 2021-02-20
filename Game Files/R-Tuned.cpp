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
#include "R-Tuned.h"

extern int EnableDamper;
extern int DamperStrength;
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 0, settingsFilename);

void RTuned::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	UINT8 SpringCrash = helpers->ReadByte(0x8519D18, /* isRelativeOffset */ false);
	UINT8 BoostEffect = helpers->ReadByte(0x8519D10, /* isRelativeOffset */ false);
	UINT8 WhenBoost = helpers->ReadByte(0x8519D20, /* isRelativeOffset */ false);

	helpers->log("got value: ");
	std::string ffs = std::to_string(BoostEffect);
	helpers->log((char*)ffs.c_str());

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	UINT8 LetsEnableFFB = helpers->ReadByte(0x8519C58, /* isRelativeOffset */ false);

	if (LetsEnableFFB == 0x01)
	{
		helpers->WriteByte(0x8519C58, 0x09, false);	
	}

	if (SpringCrash == 0xFF)
	{
		double percentForce = 1.0;
		triggers->Sine(300, 300, percentForce);
		triggers->Rumble(percentForce, percentForce, 100);
	}
	else if (SpringCrash == 0x04)
	{
		double percentForce = SpringStrength / 100.0;
		triggers->Spring(percentForce);
	}

	if (WhenBoost == 0x7F)
	{
		double percentForce = (BoostEffect / 400.0);
		double percentLength = (100);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(60, 60, percentForce);
	}
}
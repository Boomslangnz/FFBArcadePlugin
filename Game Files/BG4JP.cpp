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
#include "BG4JP.h"

extern int EnableDamper;
extern int DamperStrength;
static bool GearShift;
static bool WeAreRacing;
static UINT8 oldgear;
static UINT8 newgear;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 100, settingsFilename);
static int GearChangeStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearChangeStrength"), 100, settingsFilename);
static int GearChangeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearSinePeriod"), 100, settingsFilename);
static int EnableBoostEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableBoostEffect"), 0, settingsFilename);
static int EnableGearShiftEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableGearShiftEffect"), 0, settingsFilename);
static int BoostSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostSinePeriod"), 0, settingsFilename);
static int BoostFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostFadeSinePeriod"), 0, settingsFilename);

void BG4JP::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	UINT8 InRace = helpers->ReadInt32(0x4A9508, true);
	UINT8 GoundContact = helpers->ReadInt32(0x42EBB1, true);
	UINT8 WallContact = helpers->ReadInt32(0x42EBB2, true);
	UINT8 CarContact = helpers->ReadInt32(0x42EBB3, true);
	UINT8 ShiftEffect = helpers->ReadInt32(0x42ECF0, true);
	UINT8 CurrentView = helpers->ReadInt32(0x3F2654, true);
	float ffspeed = helpers->ReadFloat32(0x3F3000, true);
	newgear = ShiftEffect;

	helpers->log("got value: ");
	std::string ffs = std::to_string(WallContact);
	helpers->log((char *)ffs.c_str());

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	double percentForce = ffspeed / 180.00;
	double percentLength = 100.0;

	if (percentForce > 1.0)
		percentForce = 1.0;

	if (InRace)
	{
		triggers->Spring(SpringStrength / 100.0);

		if (EnableGearShiftEffect)
		{
			if (oldgear != newgear && ShiftEffect != 0x00)
			{
				double percentForceShift = GearChangeStrength / 100.0;
				triggers->Sine(GearChangeSinePeriod, 0, percentForceShift);
				triggers->Rumble(0, percentForceShift, 100.0);
			}
		}

		if (EnableBoostEffect)
		{
			if (WallContact & 0x02)
			{
				triggers->Sine(BoostSinePeriod, BoostFadeSinePeriod, percentForce);
				triggers->Rumble(percentForce, percentForce, percentLength);
			}
		}

		if (CarContact & 0x01)
		{
			triggers->Sine(120, 0, percentForce);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}

		if (WallContact & 0x10 || CarContact & 0x08)
		{
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (WallContact & 0x20 || CarContact & 0x02)
		{
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
	oldgear = newgear;
}
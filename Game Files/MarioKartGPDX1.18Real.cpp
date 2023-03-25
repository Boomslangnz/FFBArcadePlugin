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
#include "MarioKartGPDX1.18Real.h"

extern int EnableDamper;
extern int DamperStrength;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int SpringEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringEnable"), 0, settingsFilename);
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 0, settingsFilename);

void MarioKartGPDX118Real::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (SpringEnable)
		triggers->Springi(SpringStrength / 100.0);

	DWORD Base = helpers->ReadInt32(0xAAEEA0, true);
	DWORD BaseOff0 = helpers->ReadInt32(Base + 0x08, false);
	float FFB = helpers->ReadFloat32(BaseOff0 + 0xBC8, false);

	if (FFB > 0)
	{
		double percentForce = FFB;
		double percentLength = 100;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if (FFB < 0)
	{
		double percentForce = -FFB;
		double percentLength = 100;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
}
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
#include "WMMT3.h"
#include "../Common Files/Game.h"

extern int EnableDamper;
extern int DamperStrength;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int CenterOffsetStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CenterOffsetStrength"), 100, settingsFilename);
static int ReflectStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReflectStrength"), 100, settingsFilename);
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 100, settingsFilename);
static int ViosityStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViosityStrength"), 100, settingsFilename);

void WMMT3::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	int setSpring = GetTeknoParrotFFB();
	int setViosity = GetTeknoParrotFFB2();
	int setCenterOffset = GetTeknoParrotFFB3();
	int setReflect = GetTeknoParrotFFB4();

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (setSpring)
	{
		double percentForce = (setSpring / 63.0) * (SpringStrength / 100.0);
		triggers->Spring(percentForce);
	}

	if (setViosity)
	{
		double percentForce = (setViosity / 63.0) * (ViosityStrength / 100.0);
		triggers->Friction(percentForce);
	}

	if (setReflect == 0x00 && setCenterOffset == 0x00)
	{
		triggers->Rumble(0, 0, 0);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
	}
	else
	{
		if (setReflect > 0x00 && setReflect <= 0x3F)
		{
			double percentForce = (setReflect / 63.0) * (ReflectStrength / 100.0);
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if (setReflect < 0x00)
		{
			double percentForce = (((0xFFFFFFFF - setReflect) + 1) / 63.0) * (ReflectStrength / 100.0);
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}

		if (setCenterOffset > 0x00 && setCenterOffset <= 0x3F)
		{
			double percentForce = (setCenterOffset / 63.0) * (CenterOffsetStrength / 100.0);
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (setCenterOffset < 0x00)
		{
			double percentForce = (((0xFFFFFFFF - setCenterOffset) + 1) / 63.0) * (CenterOffsetStrength / 100.0);
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
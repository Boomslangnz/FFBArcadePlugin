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
#include "D1GP.h"
#include "SDL.h"

extern int EnableDamper;
extern int DamperStrength;
static int ShakeCount;
static bool LetsShake;
static UINT8 oldEffect;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EnableGroundEffects = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableGroundEffects"), 0, settingsFilename);
static int FFBGrassSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBGrassSinePeriod"), 0, settingsFilename);
static int FFBGrassFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBGrassFadeSinePeriod"), 0, settingsFilename);
static int FFBRumbleStripSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRumbleStripSinePeriod"), 0, settingsFilename);
static int FFBRumbleStripFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRumbleStripFadeSinePeriod"), 0, settingsFilename);

void D1GP::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	float FFBConstant = GetTeknoParrotFFB() / 1000.0;
	int Effect = GetTeknoParrotFFB2();
	float Speedo = helpers->ReadFloat32(0x2150F4, true);

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (FFBConstant > 0)
	{
		double percentForce = FFBConstant * 5.0;
		double percentLength = 100;

		if (percentForce > 1.0)
			percentForce = 1.0;

		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if (FFBConstant < 0)
	{
		double percentForce = -FFBConstant * 5.0;
		double percentLength = 100;

		if (percentForce > 1.0)
			percentForce = 1.0;

		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}

	double percentForce = Speedo / 200.0;

	if (percentForce > 1.0)
		percentForce = 1.0;

	if (Effect != oldEffect)
	{
		switch (Effect)
		{
		case 0x01:
			triggers->Spring(0.8);
			break;
		case 0x02:
			triggers->Rumble(0.3, 0.3, 100);
			triggers->Sine(35, 0, 0.3);
			break;
		case 0x04:
			LetsShake = true;
			break;
		}	
	}

	if (EnableGroundEffects == 1 && Speedo > 0.1)
	{
		switch (Effect)
		{
		case 0x08:
		case 0x20:
		case 0x80:
		case 0x200:
			triggers->Rumble(percentForce, percentForce, 100);
			triggers->Sine(FFBGrassSinePeriod, FFBGrassFadeSinePeriod, percentForce);
			break;
		case 0x10:
		case 0x40:
		case 0x100:
		case 0x400:
			triggers->Rumble(percentForce, percentForce, 100);
			triggers->Sine(FFBRumbleStripSinePeriod, FFBRumbleStripFadeSinePeriod, percentForce);
			break;
		}
	}

	if (LetsShake)
	{
		++ShakeCount;

		if (ShakeCount >= 32)
		{
			ShakeCount = 0;
			LetsShake = false;
		}

		triggers->Rumble(0.6, 0.6, 100);
		triggers->Sine(70, 60, 0.4);
	}

	oldEffect = Effect;
}
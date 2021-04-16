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
#include "StormRacerG.h"

extern int EnableDamper;
extern int DamperStrength;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EnableShakeEffectsWhileRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableShakeEffectsWhileRacing"), 0, settingsFilename);
static int EnableShakeEffectsinMenu = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableShakeEffectsinMenu"), 0, settingsFilename);
static int EnableGroundEffects = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableGroundEffects"), 0, settingsFilename);
static int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
static int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);
static int MinFFBConstantStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinFFBConstantStrength"), 0, settingsFilename);
static int FFBShakeSineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBShakeSineStrength"), 0, settingsFilename);
static int FFBShakeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBShakeSinePeriod"), 0, settingsFilename);
static int FFBShakeFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBShakeFadeSinePeriod"), 0, settingsFilename);
static int FFBGrassSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBGrassSinePeriod"), 0, settingsFilename);
static int FFBGrassSineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBGrassSineStrength"), 0, settingsFilename);
static int FFBGrassFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBGrassFadeSinePeriod"), 0, settingsFilename);
static int FFBRoughTerrainSineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRoughTerrainSineStrength"), 0, settingsFilename);
static int FFBRoughTerrainSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRoughTerrainSinePeriod"), 0, settingsFilename);
static int FFBRoughTerrainFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRoughTerrainFadeSinePeriod"), 0, settingsFilename);
static int FFBRumbleStripSineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRumbleStripSineStrength"), 0, settingsFilename);
static int FFBRumbleStripSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRumbleStripSinePeriod"), 0, settingsFilename);
static int FFBRumbleStripFadeSinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBRumbleStripFadeSinePeriod"), 0, settingsFilename);

void StormRacerG::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	float FFBConstant = GetTeknoParrotFFB() / 1000.0;
	int Shake = GetTeknoParrotFFB2();
	float Ground = GetTeknoParrotFFB3();
	float Speedo = helpers->ReadFloat32(0x10BE22D8, true);
	UINT8 Racing = helpers->ReadByte(0x10BD5B20, true);

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	if (EnableForceSpringEffect == 1)
	{
		triggers->Springi(ForceSpringStrength / 100.0);
	}
	else if (EnableForceSpringEffect == 2)
	{
		if (Racing == 0x00)
		{
			triggers->Spring(ForceSpringStrength / 100.0);
		}
	}

	if (FFBConstant > 0)
	{
		double percentForce = FFBConstant / (MinFFBConstantStrength / 2.173913043478261);
		double percentLength = 100;

		if (percentForce > 1.0)
			percentForce = 1.0;

		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if (FFBConstant < 0)
	{
		double percentForce = -FFBConstant / (MinFFBConstantStrength / 2.173913043478261);
		double percentLength = 100;

		if (percentForce > 1.0)
			percentForce = 1.0;

		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}

	if (EnableShakeEffectsWhileRacing == 1)
	{
		if (Racing == 0x01)
		{
			if (Shake > 0)
			{
				double percentForce = ((Shake / 1500.0) * (FFBShakeSineStrength / 100.0));
				double percentLength = 100;

				if (percentForce > 1.0)
					percentForce = 1.0;

				triggers->Rumble(percentForce, percentForce, percentLength);
				triggers->Sine(FFBShakeSinePeriod, FFBShakeFadeSinePeriod, percentForce);
			}
		}
	}

	if (EnableShakeEffectsinMenu == 1)
	{
		if (Racing == 0x00)
		{
			if (Shake > 0)
			{
				double percentForce = ((Shake / 1500.0) * (FFBShakeSineStrength / 100.0));
				double percentLength = 100;

				if (percentForce > 1.0)
					percentForce = 1.0;

				triggers->Rumble(percentForce, percentForce, percentLength);
				triggers->Sine(FFBShakeSinePeriod, FFBShakeFadeSinePeriod, percentForce);
			}
		}
	}
	
	if (EnableGroundEffects == 1)
	{ 
		if (Speedo > 1.0)
		{
			if (Ground < 10000) // Driving on Road (Not implemented yet)
			{
				Ground = Ground / 1000.0;
			}
			else if (Ground < 300000) // Driving on Grass
			{
				Ground = ((Ground - 10000) / 1000.0);

				Ground = Ground * (FFBGrassSineStrength / 100.0);

				triggers->Rumble(Ground, Ground, 100);
				triggers->Sine(FFBGrassSinePeriod, FFBGrassFadeSinePeriod, Ground);
			}
			else if (Ground < 700000) // Driving on Rough Ground
			{
				Ground = ((Ground - 300000) / 1000.0);

				Ground = Ground * (FFBRoughTerrainSineStrength / 100.0);

				triggers->Rumble(Ground, Ground, 100);
				triggers->Sine(FFBRoughTerrainSinePeriod, FFBRoughTerrainFadeSinePeriod, Ground);
			}
			else
			{
				Ground = ((Ground - 700000) / 1000.0); // Driving on Rumble Strip

				Ground = Ground * (FFBRumbleStripSineStrength / 100.0);

				triggers->Rumble(Ground, Ground, 100);
				triggers->Sine(FFBRumbleStripSinePeriod, FFBRumbleStripFadeSinePeriod, Ground);
			}
		}
	}
}
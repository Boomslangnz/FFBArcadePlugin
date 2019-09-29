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
#include "WMMT5.h"

wchar_t* settingsWMMT5 = TEXT(".\\FFBPlugin.ini");
bool gameFfbStarted = false;
int SpringStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 0, settingsWMMT5);
int FrictionStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FrictionStrength"), 0, settingsWMMT5);
int JointsAndStripesStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("JointsAndStripesStrength"), 0, settingsWMMT5);
int CollisionsStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CollisionsStrength"), 0, settingsWMMT5);
int TiresSlipStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("TiresSlipStrength"), 0, settingsWMMT5);
int HighhSpeedVibrationsStrengthWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("HighhSpeedVibrationsStrength"), 0, settingsWMMT5);
int LimitBetweenHighSpeedVibrationsAndTiresSlipWMMT5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("LimitBetweenHighSpeedVibrationsAndTiresSlip"), 0, settingsWMMT5);

void WMMT5::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	float spring = helpers->ReadFloat32(0x196F18C, /* isRelativeOffset*/ true);
	float friction = helpers->ReadFloat32(0x196F190, /* isRelativeOffset*/ true);
	float collisions = helpers->ReadFloat32(0x196F194, /* isRelativeOffset*/ true);
	float tiresSlip = helpers->ReadFloat32(0x196F188, /* isRelativeOffset*/ true);
	helpers->log("got value: ");
	std::string ffs = "spring: " + std::to_string(spring);
	helpers->log((char*)ffs.c_str());
	ffs = "friction: " + std::to_string(friction);
	helpers->log((char*)ffs.c_str());
	ffs = "collisions: " + std::to_string(collisions);
	helpers->log((char*)ffs.c_str());
	ffs = "tires slip: " + std::to_string(tiresSlip);
	helpers->log((char*)ffs.c_str());

	double percentForce;
	if (0 < spring)
	{
		if (!gameFfbStarted)
		{
			helpers->log("game's FFB started");
			gameFfbStarted = true;
		}
		percentForce = (1.0 * spring) * SpringStrengthWMMT5 / 100.0;
		triggers->Spring(percentForce);
	}
	else if (!gameFfbStarted)
	{
		helpers->log("fake spring/friction until game's FFB starts");
		percentForce = 0.4 * SpringStrengthWMMT5 / 100.0;
		triggers->Spring(percentForce);
		percentForce = 0.5 * FrictionStrengthWMMT5 / 100.0;
		triggers->Friction(percentForce);
	}
	if (0 < friction)
	{
		percentForce = (1.0 * friction) * FrictionStrengthWMMT5 / 100.0;
		triggers->Friction(percentForce);
	}
	if (0 < collisions)
	{
		if (0.209 <= collisions && 0.311 >= collisions)
		{
			helpers->log("joint/stripe on the right");
			percentForce = (1.0 * collisions) * JointsAndStripesStrengthWMMT5 / 100.0;
			triggers->Sine(80, 80, percentForce);
			triggers->LeftRight(0, percentForce, 150);
		}
		else
		{
			helpers->log("collision on the right");
			percentForce = (1.0 * collisions) * CollisionsStrengthWMMT5 / 100.0;
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			triggers->LeftRight(0, percentForce, 150);
		}
	}
	else if (0 > collisions)
	{
		if (-0.209 >= collisions && -0.311 <= collisions)
		{
			helpers->log("joint/stripe on the left");
			percentForce = (1.0 * collisions) * JointsAndStripesStrengthWMMT5 / 100.0;
			triggers->Sine(80, 80, percentForce);
			triggers->LeftRight(0, -1.0 * percentForce, 150);
		}
		else
		{
			helpers->log("collision on the left");
			percentForce = (-1.0 * collisions) * CollisionsStrengthWMMT5 / 100.0;
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			triggers->LeftRight(0, percentForce, 150);
		}

	}
	if (0 < tiresSlip)
	{
		helpers->log("tires slip left");
		bool highSpeedVibrations = (1.0 * tiresSlip) < (LimitBetweenHighSpeedVibrationsAndTiresSlipWMMT5 / 1000.0);
		percentForce = (-1.0 * tiresSlip) * (highSpeedVibrations ? HighhSpeedVibrationsStrengthWMMT5 : TiresSlipStrengthWMMT5) / 100.0;
		triggers->Sine(100, 100, percentForce);

		if ((0 == JointsAndStripesStrengthWMMT5 && 0 == CollisionsStrengthWMMT5) || (0.001 > collisions && -0.001 < collisions))
		{
			triggers->LeftRight(highSpeedVibrations ? (-1.0 * percentForce) : 0, highSpeedVibrations ? 0 : (-1.0 * percentForce), 150);
		}
	}
	else if (0 > tiresSlip)
	{
		helpers->log("tires slip right");
		bool highSpeedVibrations = (-1.0 * tiresSlip) < (LimitBetweenHighSpeedVibrationsAndTiresSlipWMMT5 / 1000.0);
		percentForce = (-1.0 * tiresSlip) * (highSpeedVibrations ? HighhSpeedVibrationsStrengthWMMT5 : TiresSlipStrengthWMMT5) / 100.0;
		triggers->Sine(100, 100, percentForce);

		if ((0 == JointsAndStripesStrengthWMMT5 && 0 == CollisionsStrengthWMMT5) || (0.001 > collisions && -0.001 < collisions))
		{
			triggers->LeftRight(highSpeedVibrations ? percentForce : 0, highSpeedVibrations ? 0 : percentForce, 150);
		}
	}
}
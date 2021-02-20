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
static int SpeedStrength;
extern int EnableDamper;
extern int DamperStrength;
void BG4JP::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	int ff = helpers->ReadInt32(0x42EBB0, /* isRelativeOffset */ true);
	float ffspeed = helpers->ReadFloat32(0x3F3000, /* isRelativeOffset */ true);
	float ff2 = helpers->ReadFloat32(0x42EAB4, /* isRelativeOffset */ true);
	if ((ffspeed >= 0.1) & (ffspeed <= 15))
	{
		SpeedStrength = 10;
	}
	else if ((ffspeed >= 15.01) & (ffspeed <= 35))
	{
		SpeedStrength = 20;
	}
	else if ((ffspeed >= 35.01) & (ffspeed <= 55))
	{
		SpeedStrength = 30;
	}
	else if ((ffspeed >= 55.01) & (ffspeed <= 75))
	{
		SpeedStrength = 40;
	}
	else if ((ffspeed >= 75.01) & (ffspeed <= 90))
	{
		SpeedStrength = 51;
	}
	else if ((ffspeed >= 90.01) & (ffspeed <= 110))
	{
		SpeedStrength = 62;
	}
	else if ((ffspeed >= 110.01) & (ffspeed <= 130))
	{
		SpeedStrength = 75;
	}
	else if ((ffspeed >= 130.01) & (ffspeed <= 150))
	{
		SpeedStrength = 90;
	}
	else if (ffspeed > 150.01)
	{
		SpeedStrength = 100;
	}
	else
	{
		SpeedStrength = 0;
	}
	
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}
		
	if ((2000000 < ff) && (ff < 4000000))
	{
		double percentForce = SpeedStrength / 100.0;
		double percentLength = 150;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) && (ff < 1600000))
	{
		double percentForce = SpeedStrength / 100.0;
		double percentLength = 150;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((0.00000000000000000001 < ff2) && (ffspeed > 0.01))
	{
		double percentForce = (0.1);
		double percentLength = (50);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((0.00000000000000000001 > ff2) && (ffspeed > 0.01))
	{
		double percentForce = (0.1);
		double percentLength = (50);
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}
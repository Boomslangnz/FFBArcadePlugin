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
#include "MarioKartGPDXCustom.h"

extern int EnableDamper;
extern int DamperStrength;

void MarioKartGPDX100Custom::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("in MKDX Ffbloop");
	
	int ff1 = helpers->ReadInt32(0x564C5F, /* isRelativeOffset */ true); //shake
	int ff2 = helpers->ReadInt32(0x559B68,/* isRelativeOffset */ true);
	int ff3 = helpers->ReadInt32(ff2 + 0x5F8, /* isRelativeOffset */ false); // terrain data
	int ff4 = helpers->ReadInt32(0x563860, /* isRelativeOffset */ true); //0-255 accl
	int ff5 = helpers->ReadInt32(ff2 + 0x628, /* isRelativeOffset */ false); //kart flying or on ground
	int ff6 = helpers->ReadInt32(0x5532C4,/* isRelativeOffset */ true);
	int ff7 = helpers->ReadInt32(ff6 + 0x1F0, /* isRelativeOffset */ false);
	int ff8 = helpers->ReadInt32(ff7 + 0x18, /* isRelativeOffset */ false);
	int ff9 = helpers->ReadInt32(ff8 + 0x7C, /* isRelativeOffset */ false);
	int ff10 = helpers->ReadInt32(ff9 + 0x164, /* isRelativeOffset */ false); // 1 during race only
	int ff11 = helpers->ReadInt32(ff2 + 0x520, /* isRelativeOffset */ false); //1065353216 when kart moves
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff1);
	helpers->log((char *)ffs.c_str()); helpers->log("got value: ");

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	// Large Shake when hitting walls, other karts or getting hit by items
	if ((4194308 == ff1) && (ff10 == 1))
	{
		double percentForce = 1.0;
		double percentForce1 = 3.5;
		double percentLength = (500);
		triggers->Rumble(percentForce1, percentForce1, percentLength);
		triggers->Sine(200, 200, percentForce);
	}

	// small friction when driving on dirt while moving
	if ((3 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = (0.3);
		double percentLength = (100);
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Friction(percentForce);
	}
	//	Small constant when hitting bumps
	if ((10 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = (0.2);
		double percentLength = (50);
		double percentForce1 = 3.0;
		triggers->Rumble(percentForce1, percentForce1, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	// Wheel rumbles while driving on grass
	if ((4 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = 0.2;
		double percentLength = (50);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}
	//wheel hard to turn while driving through water
	if ((7 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = (0.65);
		triggers->Friction(percentForce);
	}
	//Wheel rumbles lightly when driving over tiles
	if ((12 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = 0.1;
		double percentForce1 = 0.2;
		double percentLength = (150);
		triggers->Rumble(percentForce1, 0, percentLength);
		triggers->Sine(70, 70, percentForce);
	}
	//Wheel rumbles lightly when driving over sand
	if ((14 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = 0.1;
		double percentForce1 = 0.2;
		double percentLength = (50);
		triggers->Rumble(percentForce1, 0, percentLength);
		triggers->Sine(70, 70, percentForce);
	}
	//Wheel rumbles lightly when driving over rough part of track
	if ((11 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = 0.1;
		double percentForce1 = 0.2;
		double percentLength = (250);
		triggers->Rumble(0, percentForce1, percentLength);
		triggers->Sine(40, 50, percentForce);
	}
	//Wheel rumbles moderately when driving over wooden bridges
	if ((8 == ff3) && (ff10 == 1) && (ff5 == 1) && (ff11 == 1065353216))
	{
		double percentForce = 0.4;
		double percentLength = (100);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(120, 120, percentForce);
	}
}
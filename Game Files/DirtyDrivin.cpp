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
#include "DirtyDrivin.h"
extern int EnableDamper;
extern int DamperStrength;
static bool ReverseFFB;

void DirtyDrivin::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	float ffstiffness = helpers->ReadFloat32(0x886EC0, false);
	float ff = helpers->ReadFloat32(0x886EC4, false);
	UINT8 TrackSelected = helpers->ReadByte(0x96F770, false);

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char*)ffs.c_str());

	//if (ffstiffness > 0)
	//{
		//double percentForce = ffstiffness / 1.25;
		//triggers->Spring(percentForce);
	//}

	switch (TrackSelected)
	{
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		ReverseFFB = true;
		break;
	default:
		ReverseFFB = false;
		break;
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (ff > 0)
	{
		double percentForce = ff;
		double percentLength = 100;

		if (ReverseFFB)
		{
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else
		{
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	else if (ff < 0)
	{
		double percentForce = -ff;
		double percentLength = 100;

		if (ReverseFFB)
		{
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else
		{
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
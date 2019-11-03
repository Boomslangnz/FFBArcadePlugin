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
#include "InitialD4Japan.h"
#include "math.h"

void InitialD4Japan::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	UINT8 ff = helpers->ReadByte(0x0898985A, /* isRelativeOffset */ false);
	UINT8 ff1 = helpers->ReadByte(0x08989859, /* isRelativeOffset */ false);
	UINT8 ff2 = helpers->ReadByte(0x08989858, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char*)ffs.c_str());

	if (ff2 == 0x86)
	{
		triggers->Spring(0.8);
	}
	if (ff2 == 0x85) //cars colliding or rubbing against wall etc
	{
		if (ff1 > 0)
		{
			double percentLength = 200;
			double percentForce = (0.6);
			triggers->Friction(percentForce);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
	}
	if (ff2 == 0x84)
	{
		if ((ff > 0x37) && (ff < 0x80) && (ff1 == 0))
		{
			helpers->log("moving wheel right");
			double percentForce = (128 - ff) / 72.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ff > 0x00) && (ff < 0x49) && (ff1 == 1))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 72.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
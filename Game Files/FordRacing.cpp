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
#include "FordRacing.h"

void FordRacing::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("in FR Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (ff < -65505 && ff > -65515)
	{
		helpers->log("moving wheel left");
		// -65507 => 9
		// -65508 => 8
		// -65515 => 1
		// weirdly, FR has 9 levels, not 15, utilizing only -65506 (weakest) to -65514 (strongest)
		double percentForce = (-65505 - ff) / 9.0;
		double percentLength = 50;
		// direction from left => makes wheel turn right
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		lastWasStop = 0;
	}
	else if (ff > 0 && ff < 16)
	{
		helpers->log("moving wheel right");
		// weirdly, FR has 9 levels, not 15, utilizing 15 (weakest) through 7 (strongest)
		double percentForce = (16 - ff) / 9.0;
		double percentLength = 50;
		// direction from right => makes wheel turn left
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		lastWasStop = 0;
	}
	else
	{
		if (lastWasStop == 0) {
			triggers->Constant(constants->DIRECTION_FROM_LEFT, 0); // just pass the hash of 0 strength so we update lastEffectHash & lastEffectTime
			lastWasStop = 1;
		}
	}
}
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

#include "SonicSegaAllStarsRacing.h"

extern int EnableDamper;
extern int DamperStrength;

void SonicSegaAllStarsRacing::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	INT_PTR FFBEnable = helpers->ReadByte(0x5CD858, true);
	INT_PTR FFB = helpers->ReadByte(0x5CD864, true);

	helpers->WriteByte(0x5CD858, 0x03, true);

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	if ((FFB > 0) && (FFB < 19))
	{
		helpers->log("moving wheel left");
		double percentForce = FFB / 18.0;
		double percentLength = 100;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}	
	else if ((FFB > 237) && (FFB < 256))
	{
		helpers->log("moving wheel right");
		double percentForce = (256 - FFB) / 18.0;
		double percentLength = 100;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}

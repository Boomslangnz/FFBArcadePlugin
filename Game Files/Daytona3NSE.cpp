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
#include "Daytona3NSE.h"
extern int EnableDamper;
extern int DamperStrength;

void Daytona3NSE::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	UINT8 FFB = helpers->ReadByte(0x1334061, true);

	if (FFB >= 0xF8 && FFB <= 0xFF)
	{
		double percentForce = (256 - FFB) / 8.0;
		triggers->Springi(percentForce);
	}

	if (FFB >= 0xC4 && FFB <= 0xC7)
	{
		double percentForce = ((199 - FFB) / 4.0) / 6.0;
		double percentLength = 100.0;
		triggers->Sine(35, 0, percentForce);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}

	if (FFB >= 0xD8 && FFB <= 0xDF)
	{
		double percentForce = (224 - FFB) / 8.0;
		triggers->Friction(percentForce);
	}

	if (FFB == 0xBD || FFB == 0xCD)
	{
		double percentForce = 0.35;
		double percentLength = 100.0;
		triggers->Sine(140, 0, percentForce);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}

	if (FFB >= 0xA8 && FFB <= 0xAF) // Roll Left
	{
		double percentForce = (176 - FFB) / 8.0;
		double percentLength = 100.0;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}

	if (FFB >= 0x98 && FFB <= 0x9F) // Roll Right
	{
		double percentForce = (160 - FFB) / 8.0;
		double percentLength = 100.0;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}
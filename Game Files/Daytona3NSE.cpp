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

	if (FFB > 0x80 && FFB <= 0x8F) // ????
	{
		double percentForce = (144 - FFB) / 16.0;
		double percentLength = 100.0;
		triggers->Spring(percentForce);
	}

	if (FFB > 0x90 && FFB <= 0x9F) // Roll Right
	{
		double percentForce = (160 - FFB) / 16.0;
		double percentLength = 100.0;
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}

	if (FFB > 0xA0 && FFB <= 0xAF) // Roll Left
	{
		double percentForce = (176 - FFB) / 16.0;
		double percentLength = 100.0;
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}

	if (FFB > 0xB0 && FFB <= 0xBF)
	{
		double percentForce = (192 - FFB) / 16.0;
		double percentLength = 100.0;
		triggers->Sine(40, 0, percentForce);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}

	if (FFB > 0xC0 && FFB <= 0xCF)
	{
		double percentForce = (207 - FFB) / 16.0;
		triggers->Spring(percentForce);
	}

	if (FFB > 0xD0 && FFB <= 0xDF)
	{
		double percentForce = (224 - FFB) / 16.0;
		triggers->Friction(percentForce);
	}

	if (FFB > 0xE0 && FFB <= 0xEF) //????
	{
		double percentForce = (FFB - 224) / 16.0;
		triggers->Spring(percentForce);
	}

	if (FFB > 0xF0 && FFB <= 0xFF)
	{
		double percentForce = (FFB - 240) / 16.0;
		triggers->Spring(percentForce);
	}
}
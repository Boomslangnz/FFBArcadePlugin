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
	UINT8 GameState = helpers->ReadByte(0x15C98C4, true);
	DWORD TrackSelectedBase = helpers->ReadInt32(0x11C22A0, true);
	UINT8 TrackSelected = helpers->ReadByte(TrackSelectedBase + 0x4, false);

	if (FFB > 0x80 && FFB <= 0x8F) // ????
	{
		double percentForce = (144 - FFB) / 15.0;
		double percentLength = 100.0;
		triggers->Spring(percentForce);
	}

	if (FFB > 0x90 && FFB <= 0x9F) // Roll Right
	{
		double percentForce = (160 - FFB) / 15.0;
		double percentLength = 100.0;

		if ((TrackSelected == 2 || TrackSelected == 4) && GameState == 0x16)
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

	if (FFB > 0xA0 && FFB <= 0xAF) // Roll Left
	{
		double percentForce = (176 - FFB) / 15.0;
		double percentLength = 100.0;
		
		if ((TrackSelected == 2 || TrackSelected == 4) && GameState == 0x16)
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

	if (FFB > 0xB0 && FFB <= 0xBF) // Shaking across grass etc
	{
		double percentForce = (192 - FFB) / 15.0;
		double percentLength = 100.0;
		triggers->Sine(180, 0, percentForce);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}

	if (FFB > 0xC0 && FFB <= 0xCF) // Spring + Rumble on wheel while racing
	{
		double percentForce = (207 - FFB) / 15.0;
		double SinepercentForce = (FFB - 192) / 96.0;
		triggers->Spring(percentForce);
		triggers->Sine(40, 0, SinepercentForce);
	}

	if (FFB > 0xD0 && FFB <= 0xDF) // Wheel loose as tyres spin (no effect)
	{
		double percentForce = (224 - FFB) / 15.0;
	}

	if (FFB > 0xE0 && FFB <= 0xEF) // Big crash ?
	{
		double percentForce = (FFB - 224) / 15.0;
		triggers->Spring(percentForce);
	}

	if (FFB > 0xF0 && FFB <= 0xFF) // Menu only
	{
		double percentForce = (FFB - 240) / 15.0;
		triggers->Spring(percentForce);
	}
}
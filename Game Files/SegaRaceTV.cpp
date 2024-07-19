
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
#include "SegaRaceTV.h"
#include <sstream>

static bool init;
extern int EnableDamper;
extern int DamperStrength;
extern int EnableForceSpringEffect;
extern int ForceSpringStrength;

void SegaRaceTV::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{
		//enable IO calls
		helpers->WriteIntPtr(0x8b3fe90, 0x1, true);
		init = true;
	}

	int ff = helpers->ReadInt32(0x8b44210, false);
	
	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);
	if (EnableForceSpringEffect)
		triggers->Springi(ForceSpringStrength / 100.0);

	if (ff > 0 && ff < 128)
	{
		double percentForce = ((128.0 - ff) / 127.0);

		//std::ostringstream ss;
		//ss << "LEFT: " << percentForce << " FF: " << ff;
		//OutputDebugStringA(ss.str().c_str());


		
		triggers->Rumble(0, percentForce, 100.0);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if (ff > 128)
	{
		double percentForce = ((ff - 128.0) / 127.0);
		//std::ostringstream ss;
		//ss << "RIGHT: " << percentForce << " FF: " << ff;
		//OutputDebugStringA(ss.str().c_str());
		triggers->Rumble(percentForce, 0, 100.0);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
}
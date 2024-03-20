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
#include "ArcticThunder.h"

extern int EnableDamper;
extern int DamperStrength;
extern int EnableForceSpringEffect;
extern int ForceSpringStrength;

void ArcticThunder::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (EnableForceSpringEffect)
		triggers->Springi(ForceSpringStrength / 100.0);

	if (GetTeknoParrotFFB2() != 0xFF && GetTeknoParrotFFB2())
	{
		float FFBSine = (GetTeknoParrotFFB2() / 255.0);
		triggers->Sine(50, 0, FFBSine);
		triggers->Rumble(0, FFBSine, 100.0);
	}

	int FFB = GetTeknoParrotFFB3();

	if (FFB)
	{
		if (FFB > 0x80)
		{
			double percentForce = ((FFB - 128.0) / 127.0);

			triggers->Rumble(0, percentForce, 100.0);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (FFB < 0x80)
		{
			double percentForce = ((128.0 - FFB) / 127.0);

			triggers->Rumble(percentForce, 0, 100.0);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
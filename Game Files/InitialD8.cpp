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
#include "InitialD8.h"

extern int EnableDamper;
extern int DamperStrength;

static int carscollide(int ffcollide) {
	switch (ffcollide) {
	case 0x50F05:
		return 16;
	case 0x50E05:
		return 15;
	case 0x50D05:
		return 14;
	case 0x50C05:
		return 13;
	case 0x50B05:
		return 12;
	case 0x50A05:
		return 11;
	case 0x50905:
		return 10;
	case 0x50805:
		return 9;
	case 0x50705:
		return 8;
	case 0x50605:
		return 7;
	case 0x050505:
		return 6;
	case 0x050405:
		return 5;
	case 0x050305:
		return 4;
	case 0x50205:
		return 3;
	case 0x50105:
		return 2;
	case 0x50005:
		return 1;
	default:
		return 0;
	}
}

static int rubbingwalls(int ffwalls) {
	switch (ffwalls) {
	case 0x51F08:
		return 31;
	case 0x51E08:
		return 30;
	case 0x51D08:
		return 29;
	case 0x51C08:
		return 28;
	case 0x51B08:
		return 27;
	case 0x51A08:
		return 26;
	case 0x51908:
		return 25;
	case 0x51808:
		return 24;
	case 0x51708:
		return 23;
	case 0x51608:
		return 22;
	case 0x51508:
		return 21;
	case 0x51408:
		return 20;
	case 0x51308:
		return 19;
	case 0x51208:
		return 18;
	case 0x51108:
		return 17;
	case 0x50F08:
		return 16;
	case 0x50E08:
		return 15;
	case 0x50D08:
		return 14;
	case 0x50C08:
		return 13;
	case 0x50B08:
		return 12;
	case 0x50A08:
		return 11;
	case 0x50908:
		return 10;
	case 0x50808:
		return 9;
	case 0x50708:
		return 8;
	case 0x50608:
		return 7;
	case 0x50508:
		return 6;
	case 0x50408:
		return 5;
	case 0x50308:
		return 4;
	case 0x50208:
		return 3;
	case 0x50108:
		return 2;
	case 0x50008:
		return 1;
	default:
		return 0;
	}
}

void InitialD8::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	int ffrubbingwalls = 0;
	int ffcarcollision = 0;
	{
		helpers->log("in ID8 Ffbloop");
		const int ff = GetTeknoParrotFFB();
		std::string ffs = std::to_string(ff);
		helpers->log((char*)ffs.c_str());
		ffcarcollision = carscollide(ff);
		ffrubbingwalls = rubbingwalls(ff);

		if (EnableDamper == 1)
		{
			triggers->Damper(DamperStrength / 100.0);
		}

		if (ff == 0x60000)
		{
			triggers->Spring(0.8);
		}
		if (ffrubbingwalls > 0) // car rubbing against wall
		{
			double percentLength = 200;
			double percentForce = (ffrubbingwalls / 31.0);
			triggers->Friction(percentForce);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		if (ffcarcollision > 0) //cars colliding or rubbing with each other
		{
			double percentLength = 200;
			double percentForce = (ffcarcollision / 16.0);
			triggers->Friction(percentForce);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		if ((ff > 0x40037) && (ff < 0x40080))
		{
			double percentForce = (262272 - ff) / 72.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ff > 0x40100) && (ff < 0x40149))
		{
			double percentForce = (ff - 262400) / 72.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
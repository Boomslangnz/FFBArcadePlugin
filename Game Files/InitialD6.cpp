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
#include "InitialD6.h"

extern int EnableDamper;
extern int DamperStrength;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int IncreaseSine = GetPrivateProfileInt(TEXT("Settings"), TEXT("IncreaseSine"), 0, settingsFilename);

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

void InitialD6::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	DWORD FFB = GetTeknoParrotFFB();

	BYTE* ffb = reinterpret_cast<BYTE*>(&FFB);

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (ffb[2] == 0x00 && ffb[0] == 0x01)
	{
		triggers->Spring(1.0);
	}

	if (ffb[2] == 0x05 && ffb[1] > 0x00 && ffb[0] > 0x00)
	{
		double percentForce = ffb[0] / 127.0;

		if (IncreaseSine)
		{
			percentForce = percentForce * 2.0;

			if (percentForce > 1.0)
				percentForce = 1.0;
		}

		double Period = ffb[1] / 127.0 * 120.0;
		double percentLength = 100;
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(static_cast<int>(Period), 0, percentForce);
	}

	if (ffb[2] == 0x06 && ffb[0] > 0x00 && ffb[0] < 0x80)
	{
		double percentForce = ffb[0] / 127.0;
		double percentLength = 100;
		triggers->Spring(percentForce);
	}

	if (ffb[2] == 0x04 && ffb[0] > 0x00 && ffb[0] < 0x80)
	{
		if (ffb[1] == 0x00)
		{
			double percentForce = (128 - ffb[0]) / 127.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else
		{
			double percentForce = (ffb[0] / 127.0);
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
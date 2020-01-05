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
#include "InitialD0.h"
#include "math.h"

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
static int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);

void InitialD0::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
	{
		ExitProcess(0);
	}

	UINT8 ff = helpers->ReadByte(0x168317F, true);
	UINT8 static oldff = 0;
	UINT8 newff = ff;

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char*)ffs.c_str());

	if (EnableForceSpringEffect == 1)
	{
		triggers->Springi(ForceSpringStrength / 100.0);
	}

	if (oldff != newff)
	{
		if ((ff > 0x37) && (ff < 0x80))
		{
			helpers->log("moving wheel right");
			double percentForce = (128 - ff) / 72.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ff > 0x00) && (ff < 0x49))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 72.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
	oldff = newff;
}
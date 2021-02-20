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
#include "InitialD0v131.h"
#include "math.h"

static UINT8 ff;
static UINT8 oldff;
static UINT8 newff;
static UINT8 ff1;
static UINT8 ff2;
static UINT8 ff3;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
static int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);
static int IDZMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("IDZMode"), 0, settingsFilename);

void InitialD0::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
	{
		ExitProcess(0);
	}

	if (IDZMode == 0)
	{
		ff = helpers->ReadByte(0x168317F, true);
		oldff = 0;
		newff = ff;

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
	else
	{
		ff1 = helpers->ReadByte(0x168317C, true);
		ff2 = helpers->ReadByte(0x168317D, true);
		if (IDZMode == 1)
		{
			ff3 = helpers->ReadByte(0x168317E, true);
		}
		else if (IDZMode == 2)
		{
			ff3 = helpers->ReadByte(0x168317F, true);
		}

		if (ff1 == 80)
		{
			helpers->log("Spring");
			triggers->Spring(1.0);
		}
		else if (ff1 == 0x85)
		{
			if ((ff2 > 0x00) && (ff2 < 0x30))
			{
				helpers->log("Sine");
				double percentForce = ff2 / 47.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, percentForce, percentLength);
				triggers->Sine(40, 0, percentForce);
			}
		}
		else if (ff1 == 0x86)
		{
			if ((ff3 > 0x00) && (ff3 < 0x4E))
			{
				helpers->log("Spring");
				double percentForce = ff3 / 77.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
		}
		else if (ff1 == 0x84)
		{
			if ((ff2 == 0x00) && (ff3 > 0x37) && (ff3 < 0x80))
			{
				helpers->log("moving wheel right");
				double percentForce = (128 - ff3) / 72.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff2 == 0x01) && (ff3 > 0x00) && (ff3 < 0x49))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff3 / 72.0);
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else
			{
				if ((ff2 == 0x00) && (ff3 > 0x00) && (ff3 < 0x38))
				{
					helpers->log("moving wheel right");
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ff2 == 0x01) && (ff3 > 0x48))
				{
					helpers->log("moving wheel left");
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}
	}
}
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
#include "InitialD0v230.h"
#include "math.h"

extern int EnableDamper;
extern int DamperStrength;

static bool outputinit;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
static int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);
static int EnableOutputs = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableOutputs"), 0, settingsFilename);

void InitialD0v230::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!outputinit)
	{
		if (EnableOutputs)
		{
			outputinit = true;
			LoadLibraryA("OutputBlaster.dll");
		}
	}

	if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
		ExitProcess(0);

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	DWORD FFB = helpers->ReadInt32(0x18B54DC, true);
	WORD FFBStr = helpers->ReadWord(0x18B54DE, true);

	BYTE* ffb = reinterpret_cast<BYTE*>(&FFB);

	if (ffb[0] == 0x80 && ffb[2] == 0x01)
	{
		triggers->Spring(1.0);
	}

	if (ffb[0] == 0x85 && ffb[1] > 0x00 && FFBStr > 0x00)
	{
		double percentForce = FFBStr / 32767.0;
		double Period = ffb[1] / 127.0 * 120.0;
		double percentLength = 100;
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(static_cast<int>(Period), 0, percentForce);
	}

	if (ffb[0] == 0x86 && FFBStr)
	{
		double percentForce = FFBStr / 32767.0;
		double percentLength = 100;
		triggers->Spring(percentForce);
	}

	if (ffb[0] == 0x84 && FFBStr > 0x00)
	{
		if (ffb[1] == 0x00)
		{
			double percentForce = (32767.0 - FFBStr) / 32767.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (ffb[1] == 0x01)
		{
			double percentForce = (FFBStr / 32767.0);
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}
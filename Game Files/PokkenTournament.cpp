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
#include "PokkenTournament.h"

void PokkenTournament::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {


	INT_PTR ffAddress = helpers->ReadIntPtr(0x00E97F10, /* isRelativeOffset*/ true); 
	INT_PTR ff1 = helpers->ReadIntPtr(ffAddress + 0x60, /* isRelativeOffset */ false);
	INT_PTR ff2 = helpers->ReadIntPtr(ff1 + 0x8, /* isRelativeOffset */ false);
	float ff3 = helpers->ReadFloat32(ff2 + 0xCC, /* isRelativeOffset */ false); //health
	INT_PTR ffAddress4 = helpers->ReadIntPtr(0x00EC4C20, /* isRelativeOffset*/ true);
	INT_PTR ff5 = helpers->ReadIntPtr(ffAddress4 + 0x60, /* isRelativeOffset */ false);
	INT_PTR ff6 = helpers->ReadIntPtr(ff5 + 0x120, /* isRelativeOffset */ false);
	INT_PTR ff7 = helpers->ReadIntPtr(ff6 + 0x698, /* isRelativeOffset */ false); //1 during battle except for first startup

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrength"), 0, settingsFilename);
	int RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleLength"), 0, settingsFilename);
	int HowtoRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumble"), 0, settingsFilename);

	float static oldFloat = 0.0;
	float newFloat = ff3;

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff3);
	helpers->log((char *)ffs.c_str());


	if ((oldFloat != newFloat))
	{
		if (HowtoRumble == 0)
		{
			double percentForce = ((RumbleStrength) / 100.0);
			double percentLength = (RumbleLength);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumble == 1)
		{
			double percentForce = ((RumbleStrength) / 100.0);
			double percentLength = (RumbleLength);
			triggers->Rumble(0, percentForce, percentLength);
		}
		else if (HowtoRumble == 2)
		{
			double percentForce = ((RumbleStrength) / 100.0);
			double percentLength = (RumbleLength);
			triggers->Rumble(percentForce, 0, percentLength);
		}
	}
	oldFloat = newFloat;
}
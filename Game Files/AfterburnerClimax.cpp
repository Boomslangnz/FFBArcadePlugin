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
#include "AfterburnerClimax.h"
#include "SDL.h"
void AfterburnerClimax::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	UINT8 ff = helpers->ReadByte(0x08347A5E, /* isRelativeOffset */ false);
		
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int Rumble1Strength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble1Strength"), 0, settingsFilename);
	int Rumble2Strength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble2Strength"), 0, settingsFilename);
	int Rumble1Length = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble1Length"), 0, settingsFilename);
	int Rumble2Length = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble2Length"), 0, settingsFilename);
	
	if (ff == 0x40)
	{
		double percentForce = ((Rumble1Strength) / 100.0);
		double percentLength = (Rumble1Length);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}
		
	if (ff == 0x50)
	{
		double percentForce = ((Rumble2Strength) / 100.0);
		double percentLength = (Rumble2Length);
		triggers->Rumble(percentForce, percentForce, percentLength);
	}
		
}
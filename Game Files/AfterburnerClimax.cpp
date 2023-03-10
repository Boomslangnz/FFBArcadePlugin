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
static bool Version;
static bool NewVersion;
static bool OldVersion;
UINT8 Vibration;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrength"), 0, settingsFilename);

void AfterburnerClimax::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	if (!Version)
	{
		DWORD VersionOrig = helpers->ReadInt32(0x8347A5A, false);
		DWORD VersionNew = helpers->ReadInt32(0x834A51A, false);

		if (VersionOrig == 0x1320221)
		{
			OldVersion = true;
			Version = true;
		}

		if (VersionNew == 0x1320221)
		{
			NewVersion = true;
			Version = true;
		}		
	}

	if (NewVersion)
		Vibration = helpers->ReadByte(0x834A51E, false);

	if (OldVersion)
		Vibration = helpers->ReadByte(0x8347A5E, false);
		
	helpers->log("got value: ");
	std::string ffs = std::to_string(Vibration);
	helpers->log((char *)ffs.c_str());

	if (Vibration & 0x40)
	{
		double percentForce = RumbleStrength / 100.0;
		double percentLength = 100.0;
		triggers->Rumble(percentForce, percentForce, percentLength);
	}
}
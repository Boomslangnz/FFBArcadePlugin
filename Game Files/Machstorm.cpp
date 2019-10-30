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
#include "Machstorm.h"
typedef unsigned char U8;
typedef unsigned int U32;
typedef uint16_t U16;
void Machstorm::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int DomeFix = GetPrivateProfileInt(TEXT("Settings"), TEXT("DomeFix"), 0, settingsFilename);
	int Power1RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power1RumbleStrength"), 0, settingsFilename);
	int Power2RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power2RumbleStrength"), 0, settingsFilename);
	int Power3RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power3RumbleStrength"), 0, settingsFilename);
	int Power4RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power4RumbleStrength"), 0, settingsFilename);
	int Power5RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power5RumbleStrength"), 0, settingsFilename);
	int Power6RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power6RumbleStrength"), 0, settingsFilename);
	int Power7RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power7RumbleStrength"), 0, settingsFilename);
	int Power8RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power8RumbleStrength"), 0, settingsFilename);
	int Power9RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power9RumbleStrength"), 0, settingsFilename);
	int Power10RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power10RumbleStrength"), 0, settingsFilename);
	int Power1RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power1RumbleLength"), 0, settingsFilename);
	int Power2RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power2RumbleLength"), 0, settingsFilename);
	int Power3RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power3RumbleLength"), 0, settingsFilename);
	int Power4RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power4RumbleLength"), 0, settingsFilename);
	int Power5RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power5RumbleLength"), 0, settingsFilename);
	int Power6RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power6RumbleLength"), 0, settingsFilename);
	int Power7RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power7RumbleLength"), 0, settingsFilename);
	int Power8RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power8RumbleLength"), 0, settingsFilename);
	int Power9RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power9RumbleLength"), 0, settingsFilename);
	int Power10RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Power10RumbleLength"), 0, settingsFilename);
	int vibration = helpers->ReadInt32(0x6390E9, /* relative */ true);
	int power = helpers->ReadInt32(0x639109, /* relative */ true);

	if (vibration == 16842753)
	{
		if (power == 61542)
		{
			double percentLength = (Power1RumbleLength);
			double percentForce = ((Power1RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61543)
		{
			double percentLength = (Power2RumbleLength);
			double percentForce = ((Power2RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61544)
		{
			double percentLength = (Power3RumbleLength);
			double percentForce = ((Power3RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61545)
		{
			double percentLength = (Power4RumbleLength);
			double percentForce = ((Power4RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61546)
		{
			double percentLength = (Power5RumbleLength);
			double percentForce = ((Power5RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61547)
		{
			double percentLength = (Power6RumbleLength);
			double percentForce = ((Power6RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61548)
		{
			double percentLength = (Power7RumbleLength);
			double percentForce = ((Power7RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61549)
		{
			double percentLength = (Power8RumbleLength);
			double percentForce = ((Power8RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61550)
		{
			double percentLength = (Power9RumbleLength);
			double percentForce = ((Power9RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 61551)
		{
			double percentLength = (Power10RumbleLength);
			double percentForce = ((Power10RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
	}
	if (vibration == 1)
	{
		if (power == 16773366)
		{
			double percentLength = (Power1RumbleLength);
			double percentForce = ((Power1RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773367)
		{
			double percentLength = (Power2RumbleLength);
			double percentForce = ((Power2RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}		
		else if (power == 16773368)
		{
			double percentLength = (Power3RumbleLength);
			double percentForce = ((Power3RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773369)
		{
			double percentLength = (Power4RumbleLength);
			double percentForce = ((Power4RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773370)
		{
			double percentLength = (Power5RumbleLength);
			double percentForce = ((Power5RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773371)
		{
			double percentLength = (Power6RumbleLength);
			double percentForce = ((Power6RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773372)
		{
			double percentLength = (Power7RumbleLength);
			double percentForce = ((Power7RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773373)
		{
			double percentLength = (Power8RumbleLength);
			double percentForce = ((Power8RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773374)
		{
			double percentLength = (Power9RumbleLength);
			double percentForce = ((Power9RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (power == 16773375)
		{
			double percentLength = (Power10RumbleLength);
			double percentForce = ((Power10RumbleStrength) / 100.0);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
	}
}
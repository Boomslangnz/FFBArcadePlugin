#include <string>
#include "AfterburnerClimax.h"
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
	
	if (ff == 64)
		{
			double percentForce = ((Rumble1Strength) / 100.0);
			double percentLength = (Rumble1Length);
			triggers->LeftRight(percentForce, percentForce, percentLength);
		}
	else if (ff == 80)
		{
			double percentForce = ((Rumble2Strength) / 100.0);
			double percentLength = (Rumble2Length);
			triggers->LeftRight(percentForce, percentForce, percentLength);
		}
}
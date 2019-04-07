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
			triggers->LeftRight(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumble == 1)
		{
			double percentForce = ((RumbleStrength) / 100.0);
			double percentLength = (RumbleLength);
			triggers->LeftRight(0, percentForce, percentLength);
		}
		else if (HowtoRumble == 2)
		{
			double percentForce = ((RumbleStrength) / 100.0);
			double percentLength = (RumbleLength);
			triggers->LeftRight(percentForce, 0, percentLength);
		}
	}
	oldFloat = newFloat;
}
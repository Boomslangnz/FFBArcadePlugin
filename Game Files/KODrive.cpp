#include <string>
#include "KODrive.h"

void KODrive::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
	UINT8 ff = helpers->ReadByte(0x00B261F6, /* isRelativeOffset */ false);
	UINT8 ff1 = helpers->ReadByte(0x00B261F5, /* isRelativeOffset */ false);
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if ((ff == 10) & (ff1 == 30))
	{
		double percentForce = 0.4;
		double percentForce1 = 2.7;
		double percentLength = 100;
		triggers->LeftRight(percentForce1, percentForce1, percentLength);
		triggers->Sine(80, 80, percentForce);
	}
	if (FFBMode == 1)
	{
		if ((ff > 0x66) & (ff < 0x80) & (ff1 == 0))
		{
			helpers->log("moving wheel right");
			double percentForce = (128 - ff) / 24.0;
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((ff > 0x00) & (ff < 0x19) & (ff1 == 1))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 24.0;
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
	}
	else
	{
		if ((ff > 0x66) & (ff < 0x80) & (ff1 == 0))
		{
			helpers->log("moving wheel right");
			double percentForce = (128 - ff) / 24.0;
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ff > 0x00) & (ff < 0x19) & (ff1 == 1))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 24.0;
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}	
}
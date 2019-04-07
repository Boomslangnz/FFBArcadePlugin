#include <string>
#include "GTIClub3.h"
#include "math.h"

void GTIClub3::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	UINT8 ff = helpers->ReadByte(0x00918CBC, /* isRelativeOffset */ false);
	UINT8 ff1 = helpers->ReadByte(0x00918CBD, /* isRelativeOffset */ false);
	UINT8 ff2 = helpers->ReadByte(0x00918CBE, /* isRelativeOffset */ false);
	UINT8 menu = helpers->ReadByte(0x518E8E, /* isRelativeOffset */ true);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff2);
	helpers->log((char *)ffs.c_str());

	if (FFBMode == 0)
	{
		if ((ff1 > 0x00) & (ff1 < 0x40) & (menu == 0))
		{
			double percentForce = (ff1) / 63.0;
			double percentLength = 100;
			triggers->LeftRight(percentForce, percentForce, percentLength);
			triggers->Sine(120, 120, percentForce);
		}
		if ((ff > 0x80) & (ff < 0x101) & (menu == 0))
		{
			helpers->log("moving wheel right");
			double percentForce = (257 - ff) / 128.0;
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ff > 0x00) & (ff < 0x80) & (menu == 0))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 127.0;
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	else
	{
		if ((ff1 > 0x00) & (ff1 < 0x40) & (menu == 0))
		{
			double percentForce = (ff1) / 63.0;
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), pow(percentForce, 0.5), percentLength);
			triggers->Sine(120, 120, pow(percentForce, 0.5));
		}
		if ((ff > 0x80) & (ff < 0x101) & (menu == 0))
		{
			helpers->log("moving wheel right");
			double percentForce = (257 - ff) / 128.0;
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((ff > 0x00) & (ff < 0x80) & (menu == 0))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff) / 127.0;
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
	}
}
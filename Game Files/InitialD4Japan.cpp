#include <string>
#include "InitialD4Japan.h"
#include "math.h"

void InitialD4Japan::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	UINT8 ff = helpers->ReadByte(0x0898985A, /* isRelativeOffset */ false);
	UINT8 ff1 = helpers->ReadByte(0x08989859, /* isRelativeOffset */ false);
	UINT8 ff2 = helpers->ReadByte(0x08989858, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (ff2 == 0x86)
	{
		triggers->Spring(0.8);
	}
	if (ff2 == 0x85) //cars colliding or rubbing against wall etc
	{
		if (ff1 > 0)
		{
			double percentLength = 200;
			double percentForce = (0.6);
			triggers->Inertia(percentForce);
			triggers->Friction(percentForce);
			triggers->Damper(percentForce);
			triggers->LeftRight(percentForce, percentForce, percentLength);
		}
	}
	if (FFBMode == 1)
	{
		if (ff2 == 0x84)
		{
			if ((ff > 0x37) && (ff < 0x80) && (ff1 == 0))
			{
				helpers->log("moving wheel right");
				double percentForce = (128 - ff) / 72.0;
				double percentLength = 100;
				double powforce = (ff - 55) / 72.0;
				triggers->LeftRight(pow(percentForce, powforce), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, powforce)));
			}
			else if ((ff > 0x00) && (ff < 0x49) && (ff1 == 1))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff) / 72.0;
				double percentLength = 100;
				double powforce = (73 - ff) / 72.0;
				triggers->LeftRight(0, pow(percentForce, powforce), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, powforce)));
			}
		}
	}
	else
	{
		if (ff2 == 0x84)
		{
			if ((ff > 0x37) && (ff < 0x80) && (ff1 == 0))
			{
				helpers->log("moving wheel right");
				double percentForce = (128 - ff) / 72.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff > 0x00) && (ff < 0x49) && (ff1 == 1))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff) / 72.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
}
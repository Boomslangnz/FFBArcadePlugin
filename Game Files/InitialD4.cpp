#include <string>
#include "InitialD4.h"
#include "math.h"

void InitialD4::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers){

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	UINT8 ff = helpers->ReadByte(0x089AE89A, /* isRelativeOffset */ false);
	UINT8 ff1 = helpers->ReadByte(0x089AE899, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if ((ff > 0x37) & (ff < 0x80) & (ff1 == 0) & (FFBMode == 0))
	{
		helpers->log("moving wheel right");
		double percentForce = (128 - ff) / 73.0;
		double percentLength = 100;
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((ff > 0x00) & (ff < 0x49) & (ff1 == 1) & (FFBMode == 0))
	{
		helpers->log("moving wheel left");
		double percentForce = (ff) / 73.0;
		double percentLength = 100;
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((ff > 0x37) & (ff < 0x80) & (ff1 == 0) & (FFBMode == 1))
	{
		helpers->log("moving wheel right");
		double percentForce = (128 - ff) / 73.0;
		double percentLength = 100;
		triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
	}
	else if ((ff > 0x00) & (ff < 0x49) & (ff1 == 1) & (FFBMode == 1))
	{
		helpers->log("moving wheel left");
		double percentForce = (ff) / 73.0;
		double percentLength = 100;
		triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT,(pow(percentForce, 0.5)));
	}		
}
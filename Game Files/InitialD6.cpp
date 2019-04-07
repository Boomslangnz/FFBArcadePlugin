#include <string>
#include "InitialD6.h"

void InitialD6::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers)
{
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int SineDivision = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineDivision"), 0, settingsFilename);
	helpers->log("in ID6 Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if ((ff > 0x4005B) & (ff < 0x40080))
	{
		helpers->log("moving wheel right");
		double percentForce = (262272 - ff) / 36.0;
		double percentLength = 100;
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((ff > 0x40100) & (ff < 0x40125))
	{
		helpers->log("moving wheel left");
		double percentForce = (ff - 262400) / 36.0;
		double percentLength = 100;
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((ff >= 390001) && (ff <= 399999))
	{
		helpers->log("sine1");
		double percentForce = (ff - 390000) / ((SineDivision) / 1.0);
		double percentLength = 100;
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(120, 100, percentForce);
	}
	else if ((ff >= 380001) && (ff <= 389999))
	{
		helpers->log("sine2");
		double percentLength = 100;
		double percentForce = (ff - 380000) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(130, 120, percentForce);
	}
	else if ((ff >= 370001) && (ff <= 379999))
	{
		helpers->log("sine3");
		double percentLength = 100;
		double percentForce = (ff - 370000) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(140, 140, percentForce);
	}
	else if ((ff >= 360001) && (ff <= 369999))
	{
		helpers->log("sine4");
		double percentForce = (ff - 360000) / ((SineDivision) / 1.0);
		double percentLength = 100;
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(150, 150, percentForce);
	}
	else if ((ff >= 350001) && (ff <= 359999))
	{
		helpers->log("sine5");
		double percentLength = 100;
		double percentForce = (ff - 350000) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(160, 160, percentForce);
	}
	else if ((ff >= 340001) && (ff <= 349999))
	{
		helpers->log("sine6");
		double percentLength = 100;
		double percentForce = (ff - 340000) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(170, 170, percentForce);
	}
	else if ((ff >= 330001) && (ff <= 339999))
	{
		helpers->log("sine7");
		double percentLength = 100;
		double percentForce = (ff - 330000) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(180, 180, percentForce);
	}
	else if ((ff >= 327681) && (ff <= 329999))
	{
		helpers->log("sine8");
		double percentLength = 100;
		double percentForce = (ff - 327680) / ((SineDivision) / 1.0);
		triggers->Rumble(percentForce, percentLength);
		triggers->Sine(190, 190, percentForce);
	}
}
#include <string>
#include "Outrun2Fake.h"

void OutRun2Fake::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	int ff = helpers->ReadInt32(0x0827A1A0, /* isRelativeOffset */ false);
	int ffwall = helpers->ReadInt32(0x08273FAC, /* isRelativeOffset */ false);
	float ffspeed = helpers->ReadFloat32(0x08273DF0, /* isRelativeOffset */ false); //speedo
	int ff3 = helpers->ReadInt32(0x0827A1DA, /* isRelativeOffset */ false);
	int ff4 = helpers->ReadInt32(0x0827A35D, /* isRelativeOffset */ false);
	int ff5 = helpers->ReadInt32(0x0827A1D4, /* isRelativeOffset */ false);
	UINT8 ff6 = helpers->ReadByte(0x08670DC8, /* isRelativeOffset */ false); // steering
	float ff7 = helpers->ReadFloat32(0x08273AD4, /* isRelativeOffset */ false);
	UINT8 ff8 = helpers->ReadByte(0x08304ADC, /* isRelativeOffset */ false); // 1 when race
	UINT8 ff9 = helpers->ReadByte(0x086749CA, /* isRelativeOffset */ false); // 1 when menu

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	int static oldFloat = 0.0;
	int newFloat = ff3;
	int static oldFloat1 = 0.0;
	int newFloat1 = ff4;
	if (FFBMode == 1)
	{
		if ((ff6 >= 0x00) & (ff6 < 0x7F) & (ff8 == 1))
		{
			double percentForce = ((127 - ff6) / 127.0);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		if ((ff6 > 0x7F) & (ff6 < 0x100) & (ff8 == 1))
		{
			double percentForce = ((ff6 - 127) / 128.0);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		if ((ff6 >= 0x00) & (ff6 < 0x7F) & (ff9 == 1))
		{
			double percentForce = ((127 - ff6) / 127.0);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		if ((ff6 > 0x7F) & (ff6 < 0x100) & (ff9 == 1))
		{
			double percentForce = ((ff6 - 127) / 128.0);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		if ((oldFloat != newFloat) & (ffspeed >= 0.1) & (ffspeed <= 80) & (ff5 == 2))
		{
			double percentForce = (0.1);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 80.1) & (ffspeed <= 130) & (ff5 == 2))
		{
			double percentForce = (0.2);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 130.1) & (ffspeed <= 180) & (ff5 == 2))
		{
			double percentForce = (0.3);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 180.1) & (ffspeed <= 220) & (ff5 == 2))
		{
			double percentForce = (0.4);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 220.1) & (ffspeed <= 270) & (ff5 == 2))
		{
			double percentForce = (0.5);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 270.1) & (ffspeed <= 320) & (ff5 == 2))
		{
			double percentForce = (0.6);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 320.1) & (ffspeed <= 380) & (ff5 == 2))
		{
			double percentForce = (0.7);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 380.1) & (ffspeed <= 430) & (ff5 == 2))
		{
			double percentForce = (0.8);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 430.1) & (ffspeed <= 500) & (ff5 == 2))
		{
			double percentForce = (0.9);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 500.1) & (ffspeed <= 1000) & (ff5 == 2))
		{
			double percentForce = (1.0);
			double percentLength = 100;
			triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 0.1) & (ffspeed <= 80) & (ff5 == 1))
		{
			double percentForce = (0.1);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 80.1) & (ffspeed <= 130) & (ff5 == 1))
		{
			double percentForce = (0.2);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 130.1) & (ffspeed <= 180) & (ff5 == 1))
		{
			double percentForce = (0.3);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 180.1) & (ffspeed <= 220) & (ff5 == 1))
		{
			double percentForce = (0.4);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 220.1) & (ffspeed <= 270) & (ff5 == 1))
		{
			double percentForce = (0.5);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 270.1) & (ffspeed <= 320) & (ff5 == 1))
		{
			double percentForce = (0.6);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 320.1) & (ffspeed <= 380) & (ff5 == 1))
		{
			double percentForce = (0.7);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 380.1) & (ffspeed <= 430) & (ff5 == 1))
		{
			double percentForce = (0.8);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 430.1) & (ffspeed <= 500) & (ff5 == 1))
		{
			double percentForce = (0.9);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 500.1) & (ffspeed <= 1000) & (ff5 == 1))
		{
			double percentForce = (1.0);
			double percentLength = 100;
			triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
		}
	}
	else
	{
		if ((ff6 >= 0x00) & (ff6 < 0x7F) & (ff8 == 1) & (FFBMode == 0))
		{
			double percentForce = ((127 - ff6) / 127.0);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		if ((ff6 > 0x7F) & (ff6 < 0x100) & (ff8 == 1))
		{
			double percentForce = ((ff6 - 127) / 128.0);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		if ((ff6 >= 0x00) & (ff6 < 0x7F) & (ff9 == 1))
		{
			double percentForce = ((127 - ff6) / 127.0);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		if ((ff6 > 0x7F) & (ff6 < 0x100) & (ff9 == 1))
		{
			double percentForce = ((ff6 - 127) / 128.0);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		if ((oldFloat != newFloat) & (ffspeed >= 0.1) & (ffspeed <= 80) & (ff5 == 2))
		{
			double percentForce = (0.1);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 80.1) & (ffspeed <= 130) & (ff5 == 2))
		{
			double percentForce = (0.2);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 130.1) & (ffspeed <= 180) & (ff5 == 2))
		{
			double percentForce = (0.3);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 180.1) & (ffspeed <= 220) & (ff5 == 2))
		{
			double percentForce = (0.4);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 220.1) & (ffspeed <= 270) & (ff5 == 2))
		{
			double percentForce = (0.5);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 270.1) & (ffspeed <= 320) & (ff5 == 2))
		{
			double percentForce = (0.6);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 320.1) & (ffspeed <= 380) & (ff5 == 2))
		{
			double percentForce = (0.7);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 380.1) & (ffspeed <= 430) & (ff5 == 2))
		{
			double percentForce = (0.8);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 430.1) & (ffspeed <= 500) & (ff5 == 2))
		{
			double percentForce = (0.9);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 500.1) & (ffspeed <= 1000) & (ff5 == 2))
		{
			double percentForce = (1.0);
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 0.1) & (ffspeed <= 80) & (ff5 == 1))
		{
			double percentForce = (0.1);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 80.1) & (ffspeed <= 130) & (ff5 == 1))
		{
			double percentForce = (0.2);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 130.1) & (ffspeed <= 180) & (ff5 == 1))
		{
			double percentForce = (0.3);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 180.1) & (ffspeed <= 220) & (ff5 == 1))
		{
			double percentForce = (0.4);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 220.1) & (ffspeed <= 270) & (ff5 == 1))
		{
			double percentForce = (0.5);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 270.1) & (ffspeed <= 320) & (ff5 == 1))
		{
			double percentForce = (0.6);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 320.1) & (ffspeed <= 380) & (ff5 == 1))
		{
			double percentForce = (0.7);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 380.1) & (ffspeed <= 430) & (ff5 == 1))
		{
			double percentForce = (0.8);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 430.1) & (ffspeed <= 500) & (ff5 == 1))
		{
			double percentForce = (0.9);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((oldFloat != newFloat) & (ffspeed >= 500.1) & (ffspeed <= 1000) & (ff5 == 1))
		{
			double percentForce = (1.0);
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((oldFloat1 != newFloat1) & (ffspeed >= 0.1) & (ffspeed <= 50))
	{
		double percentForce = (0.1);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 50.1) & (ffspeed <= 100))
	{
		double percentForce = (0.2);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 100.1) & (ffspeed <= 150))
	{
		double percentForce = (0.3);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 150.1) & (ffspeed <= 200))
	{
		double percentForce = (0.4);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 200.1) & (ffspeed <= 250))
	{
		double percentForce = (0.5);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 250.1) & (ffspeed <= 300))
	{
		double percentForce = (0.6);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 300.1) & (ffspeed <= 350))
	{
		double percentForce = (0.7);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 350.1) & (ffspeed <= 400))
	{
		double percentForce = (0.8);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 450.1) & (ffspeed <= 500))
	{
		double percentForce = (0.9);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((oldFloat1 != newFloat1) & (ffspeed >= 500.1) & (ffspeed <= 1000))
	{
		double percentForce = (1.0);
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((ff == 8) & (ffspeed >= 0.1) & (ffspeed <= 1000))
	{
		double percentForce = 0.1;
		double percentLength = 100;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(70, 70, percentForce);
	}
	else if ((ff == 4) & (ffspeed >= 0.1) & (ffspeed <= 1000))
	{
		double percentForce = 0.2;
		double percentLength = 50;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}
	else if ((ff == 16) & (ffspeed >= 0.1) & (ffspeed <= 1000))
	{
		double percentForce = 0.2;
		double percentLength = 50;
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(100, 50, percentForce);
	}
	oldFloat = newFloat;
	oldFloat1 = newFloat1;
}
#include <string>
#include "BG4JP.h"

void BG4JP::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	int ff = helpers->ReadInt32(0x42EBB0, /* isRelativeOffset */ true);
	float ffspeed = helpers->ReadFloat32(0x3F3000, /* isRelativeOffset */ true);
	float ff2 = helpers->ReadFloat32(0x42EAB4, /* isRelativeOffset */ true);
	
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

		
	if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 0.1) & (ffspeed <= 15))
	{
		double percentForce = (0.1);
		double percentLength = (200);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 0.1) & (ffspeed <= 15))
	{
		double percentForce = (0.1);
		double percentLength = (200);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 15.01) & (ffspeed <= 35))
	{
		double percentForce = (0.2);
		double percentLength = (200);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 15.01) & (ffspeed <= 35))
	{
		double percentForce = (0.2);
		double percentLength = (200);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		triggers->Rumble(percentForce, percentLength);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 35.01) & (ffspeed <= 55))
	{
		double percentForce = (0.3);
		double percentLength = (250);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 35.01) & (ffspeed <= 55))
	{
		double percentForce = (0.3);
		double percentLength = (250);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		triggers->Rumble(percentForce, percentLength);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 55.01) & (ffspeed <= 75))
	{
		double percentForce = (0.4);
		double percentLength = (280);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		triggers->Rumble(percentForce, percentLength);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 55.01) & (ffspeed <= 75))
	{
		double percentForce = (0.4);
		double percentLength = (280);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 75.01) & (ffspeed <= 90))
	{
		double percentForce = (0.5);
		double percentLength = (320);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 75.01) & (ffspeed <= 90))
	{
		double percentForce = (0.5);
		double percentLength = (320);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 90.01) & (ffspeed <= 110))
	{
		double percentForce = (0.6);
		double percentLength = (370);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 90.01) & (ffspeed <= 110))
	{
		double percentForce = (0.6);
		double percentLength = (370);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 110.01) & (ffspeed <= 130))
	{
		double percentForce = (0.7);
		double percentLength = (400);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 110.01) & (ffspeed <= 130))
	{
		double percentForce = (0.7);
		double percentLength = (400);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed >= 130.01) & (ffspeed <= 150))
	{
		double percentForce = (0.9);
		double percentLength = (450);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed >= 130.01) & (ffspeed <= 150))
	{
		double percentForce = (0.9);
		double percentLength = (450);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((2000000 < ff) & (ff < 4000000) & (ffspeed > 150.01))
	{
		double percentForce = (1.0);
		double percentLength = (500);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((1000000 < ff) & (ff < 1600000) & (ffspeed > 150.01))
	{
		double percentForce = (1.0);
		double percentLength = (500);
		triggers->Rumble(percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if ((0.00000000000000000001 < ff2) & (ffspeed > 0.01))
	{
		double percentForce = (0.1);
		double percentLength = (50);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((0.00000000000000000001 > ff2) & (ffspeed > 0.01))
	{
		double percentForce = (0.1);
		double percentLength = (50);
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}
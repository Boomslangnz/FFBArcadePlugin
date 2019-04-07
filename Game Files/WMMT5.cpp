#include <string>
#include "WMMT5.h"

void WMMT5::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	float roll = helpers->ReadFloat32(0x196F194, /* isRelativeOffset*/ true);
	float friction = helpers->ReadFloat32(0x196F18C, /* isRelativeOffset*/ true);
	float sine = helpers->ReadFloat32(0x196F188, /* isRelativeOffset*/ true);
	helpers->log("got value: ");
	std::string ffs = std::to_string(roll);
	helpers->log((char *)ffs.c_str());

	{
		//Trigger Spring the entire time like real cabinet
		double percentForce = 0.7;
		triggers->Springi(percentForce);
	}

	if (0 < roll)
	{
		helpers->log("moving wheel right");
		double percentForce = (1.0 - roll);
		double percentLength = (250);
		// direction from right => makes wheel turn left
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);

	}
	else if (0 > roll)
	{
		helpers->log("moving wheel left");
		double percentForce = (roll + 1.0);
		double percentLength = (250);
		// direction from left => makes wheel turn right
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);

	}
	else if (0 < friction)
	{
		helpers->log("moving wheel right");
		double percentForce = (0.7 - friction);
		triggers->Friction(percentForce);
	}
	else if (0 < sine)
	{
		helpers->log("moving wheel right");
		double percentForce = (0.6 - sine);
		triggers->Sine(120, 120, percentForce);
	}
	else if (0 > sine)
	{
		helpers->log("moving wheel left");
		double percentForce = (sine + 0.6);
		triggers->Sine(120, 120, percentForce);
	}
}
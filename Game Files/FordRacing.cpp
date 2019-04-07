#include <string>
#include "FordRacing.h"

void FordRacing::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("in FR Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (ff < -65505 && ff > -65515)
	{
		helpers->log("moving wheel left");
		// -65507 => 9
		// -65508 => 8
		// -65515 => 1
		// weirdly, FR has 9 levels, not 15, utilizing only -65506 (weakest) to -65514 (strongest)
		double percentForce = (-65505 - ff) / 9.0;
		double percentLength = 50;
		// direction from left => makes wheel turn right
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		lastWasStop = 0;
	}
	else if (ff > 0 && ff < 16)
	{
		helpers->log("moving wheel right");
		// weirdly, FR has 9 levels, not 15, utilizing 15 (weakest) through 7 (strongest)
		double percentForce = (16 - ff) / 9.0;
		double percentLength = 50;
		// direction from right => makes wheel turn left
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		lastWasStop = 0;
	}
	else
	{
		if (lastWasStop == 0) {
			triggers->Constant(constants->DIRECTION_FROM_LEFT, 0); // just pass the hash of 0 strength so we update lastEffectHash & lastEffectTime
			lastWasStop = 1;
		}
	}
}
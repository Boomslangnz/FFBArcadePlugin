#include <string>
#include "SegaRally3.h"

void SegaRally3::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("in SR3 Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (ff > 15)
	{
		helpers->log("moving wheel right");
		// assume that 30 is the weakest and 16 is the strongest
		double percentForce = (31 - ff) / 15.0;
		double percentLength = 100;
		// direction from left => makes wheel turn right
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		lastWasStop = 0;
	}
	else if (ff > 0)
	{
		helpers->log("moving wheel left");
		// assume that 1 is the strongest and 15 is the weakest
		double percentForce = (16 - ff) / 15.0;
		double percentLength = 100;
		// direction from right => makes wheel turn left
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
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
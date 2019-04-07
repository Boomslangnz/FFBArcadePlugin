#include <string>
#include "Outrun2Real.h"
EffectTriggers* myTriggers;
EffectConstants *myConstants;
Helpers *myHelpers;

void SendForceFeedback(__int8 force)
{
	if (force >= 1 && force <= 0x0F)
	{
		// direction from right => makes wheel turn left
		double percentForce = (16 - force) / 15.0;
		double percentLength = 100;
		//myHelpers->log("got value: ");
		//std::string ffs = std::to_string(force);
		//myHelpers->log((char *)ffs.c_str());
		myTriggers->LeftRight(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);	
	}
	else if (force >= 0x10 && force <= 0x1E)
	{
		// direction from left => makes wheel turn right
		double percentForce = (31 - force) / 15.0;
		double percentLength = 100;
		//myHelpers->log("got value: ");
		//std::string ffs = std::to_string(force);
		//myHelpers->log((char *)ffs.c_str());
		myTriggers->LeftRight(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
}

signed int cdecl or2FfbFunction(unsigned __int8 unk1, unsigned __int8 unk2, unsigned __int8 force, char unk3)
{
	if (unk1 == 0x7D)
	{
		// not used afaik
	}
	if (unk1 == 0x7B)
	{
		SendForceFeedback(force);
	}

	return 0;
}

void OutRun2Real::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	bool init = false;
	if (!init)
	{
		DWORD tempdw = 0x08105A48;
		DWORD cock = (DWORD)(void *)or2FfbFunction;
		DWORD tempdw2 = cock - tempdw - 5;
		*(BYTE *)tempdw = 0xE9;
		*(DWORD *)(tempdw + 1) = tempdw2;
		init = true;
	}

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}
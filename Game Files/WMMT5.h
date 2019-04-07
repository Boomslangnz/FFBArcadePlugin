#pragma once
#include "../Common Files/Game.h"
class WMMT5 : public Game {
	int lastWasStop = 0;
	
	public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
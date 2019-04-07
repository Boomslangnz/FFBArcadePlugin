#pragma once
#include "../Common Files/Game.h"

class OutRun2Fake : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
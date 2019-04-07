#pragma once
#include "../Common Files/Game.h"

class OutRun2Real : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
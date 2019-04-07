#pragma once
#include "../Common Files/Game.h"

class InitialD4Japan : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};

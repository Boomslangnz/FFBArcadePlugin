#pragma once
#include "../Common Files/Game.h"
class Mame019964bit : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
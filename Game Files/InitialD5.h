#pragma once
#include "../Common Files/Game.h"

class InitialD5 : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
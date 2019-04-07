#pragma once
#include "../Common Files/Game.h"

class LGI : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};

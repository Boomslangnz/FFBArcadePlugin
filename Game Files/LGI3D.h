#pragma once
#include "../Common Files/Game.h"

class LGI3D : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};

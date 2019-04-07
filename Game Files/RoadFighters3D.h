#pragma once
#include "../Common Files/Game.h"
class RoadFighters3D : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
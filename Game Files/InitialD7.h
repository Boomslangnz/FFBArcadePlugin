#pragma once
#include "../Common Files/TeknoParrotGame.h"

class InitialD7 : public TeknoParrotGame {
public:
	InitialD7() : TeknoParrotGame() { }
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
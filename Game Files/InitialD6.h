#pragma once
#include "../Common Files/TeknoParrotGame.h"

class InitialD6 : public TeknoParrotGame {
public:
	InitialD6() : TeknoParrotGame() { }
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
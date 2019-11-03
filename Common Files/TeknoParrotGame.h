#pragma once
#include "Game.h"

class TeknoParrotGame : public Game {

	// TP-related
	HANDLE hSection;
	LPVOID secData;
	int ffbOffset = 0;

protected:
	int GetTeknoParrotFFB();
	TeknoParrotGame();

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
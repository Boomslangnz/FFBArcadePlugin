#pragma once
#include "Game.h"

class TeknoParrotGame : public Game {

	// TP-related
	HANDLE hSection;
	LPVOID secData;
	int ffbOffset = 0;
	int ffbOffset2 = 0;

protected:
	int GetTeknoParrotFFB();
	int GetTeknoParrotFFB2();
	TeknoParrotGame();

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
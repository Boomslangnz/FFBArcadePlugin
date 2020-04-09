#include "TeknoParrotGame.h"
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int configGameId = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 0, settingsFilename);

TeknoParrotGame::TeknoParrotGame()
{
	hSection = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 64, L"TeknoParrot_JvsState");
	secData = MapViewOfFile(hSection, FILE_MAP_ALL_ACCESS, 0, 0, 64);

	if (configGameId == 19)
	{
		ffbOffset = *((int*)secData + 6);
		ffbOffset2 = *((int*)secData + 7);
	}
	else
	{
		ffbOffset = *((int*)secData + 2);
	}	
}

int TeknoParrotGame::GetTeknoParrotFFB()
{
	if (configGameId == 19)
	{
		ffbOffset = *((int*)secData + 6);
	}
	else
	{
		ffbOffset = *((int*)secData + 2);
	}
	
	return ffbOffset;
}

int TeknoParrotGame::GetTeknoParrotFFB2()
{
	ffbOffset2 = *((int*)secData + 7);
	return ffbOffset2;
}

void TeknoParrotGame::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("TeknoParrot game not implemented");
}
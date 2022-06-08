#include "TeknoParrotGame.h"
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int configGameId = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 0, settingsFilename);

TeknoParrotGame::TeknoParrotGame()
{
	secData = 0;
	hSection = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 64, L"TeknoParrot_JvsState");
	if (hSection)
	secData = MapViewOfFile(hSection, FILE_MAP_ALL_ACCESS, 0, 0, 64);

	if (secData)
	{
		if (*((int*)secData + 2) > 0)
			*((int*)secData + 2) = 0;

		if (*((int*)secData + 6) > 0)
			*((int*)secData + 6) = 0;

		if (*((int*)secData + 7) > 0)
			*((int*)secData + 7) = 0;

		if (*((int*)secData + 8) > 0)
			*((int*)secData + 8) = 0;

		if (*((int*)secData + 9) > 0)
			*((int*)secData + 9) = 0;

		if (configGameId == 61)
		{
			ffbOffset = *((int*)secData + 6);
			ffbOffset2 = *((int*)secData + 7);
			ffbOffset3 = *((int*)secData + 8);
			ffbOffset4 = *((int*)secData + 9);
		}
		else if (configGameId == 54 || configGameId == 55)
		{
			ffbOffset = *((int*)secData + 6);
			ffbOffset2 = *((int*)secData + 7);
			ffbOffset3 = *((int*)secData + 8);
		}
		else if (configGameId == 19)
		{
			ffbOffset = *((int*)secData + 6);
			ffbOffset2 = *((int*)secData + 7);
		}
		else if (configGameId == 62)
			ffbOffset = *((int*)secData + 6);
		else
			ffbOffset = *((int*)secData + 2);
	}
}

int TeknoParrotGame::GetTeknoParrotFFB()
{
	if (configGameId == 19 || configGameId == 54 || configGameId == 55 || configGameId == 61 || configGameId == 62)
		ffbOffset = *((int*)secData + 6);
	else
		ffbOffset = *((int*)secData + 2);
	
	return ffbOffset;
}

int TeknoParrotGame::GetTeknoParrotFFB2()
{
	ffbOffset2 = *((int*)secData + 7);
	return ffbOffset2;
}

int TeknoParrotGame::GetTeknoParrotFFB3()
{
	ffbOffset3 = *((int*)secData + 8);
	return ffbOffset3;
}

int TeknoParrotGame::GetTeknoParrotFFB4()
{
	ffbOffset4 = *((int*)secData + 9);
	return ffbOffset4;
}

void TeknoParrotGame::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("TeknoParrot game not implemented");
}
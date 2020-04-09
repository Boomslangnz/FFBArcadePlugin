/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "PokkenTournament.h"

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);

void PokkenTournament::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
		helpers->log("in PokkenTournament Ffbloop");
		const int LeftMotor = GetTeknoParrotFFB();
		const int RightMotor = GetTeknoParrotFFB2();
		std::string ffs = std::to_string(LeftMotor);
		helpers->log((char*)ffs.c_str());

		if (LeftMotor > 3)
		{
			double percentForce = (LeftMotor / 255.0);
			triggers->Rumble(0, percentForce, configFeedbackLength);
		}

		if (RightMotor > 3)
		{
			double percentForce = (RightMotor / 255.0);
			triggers->Rumble(percentForce, 0, configFeedbackLength);
		}
}
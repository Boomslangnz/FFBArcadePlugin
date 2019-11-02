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

#pragma once
#include "../Common Files/Game.h"

class WMMT5 : public Game {
	UINT8 oldgear = 0;
	bool gameFfbStarted = false;
	int SpringStrength = hlp->GetIniValueInt("SpringStrength", 100);
	int FrictionStrength = hlp->GetIniValueInt("FrictionStrength", 0);
	int JointsAndStripesStrength = hlp->GetIniValueInt("JointsAndStripesStrength", 100);
	int CollisionsStrength = hlp->GetIniValueInt("CollisionsStrength", 100);
	int TiresSlipStrength = hlp->GetIniValueInt("TiresSlipStrength", 100);
	int HighSpeedVibrationsStrength = hlp->GetIniValueInt("HighSpeedVibrationsStrength", 100);
	int LimitBetweenHighSpeedVibrationsAndTiresSlip = hlp->GetIniValueInt("LimitBetweenHighSpeedVibrationsAndTiresSlip", 75);
	int WheelSpinStrength = hlp->GetIniValueInt("WheelSpinStrength", 100);
	int ForceFullTune = hlp->GetIniValueInt("ForceFullTune", 0);
	int DisableRaceTimer = hlp->GetIniValueInt("DisableRaceTimer", 0);
	int EnableForceFinish = hlp->GetIniValueInt("EnableForceFinish", 0);
	int EnableForceTimeUp = hlp->GetIniValueInt("EnableForceTimeUp", 0);
	int ForceFinishButton = hlp->GetIniValueInt("ForceFinishButton", 99);
	int ForceTimeUpButton = hlp->GetIniValueInt("ForceTimeUpButton", 99);
	void InputThread();
	void SpamThread();

public:
	void Loop();
};
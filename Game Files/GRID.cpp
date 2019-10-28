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
#include "GRID.h"

void GRID::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	INT_PTR WallBase = helpers->ReadIntPtr(0xB1B7F0, true);
	INT_PTR WallBase1 = helpers->ReadIntPtr(WallBase + 0x730, false);
	INT_PTR WallBase2 = helpers->ReadIntPtr(WallBase1 + 0x4, false);
	INT_PTR WallBase3 = helpers->ReadIntPtr(WallBase2 + 0x4, false);
	float WallBase4 = helpers->ReadFloat32(WallBase3 + 0x118, false);

	INT_PTR PanelBase = helpers->ReadIntPtr(0xA3FA34, true);
	INT_PTR PanelBase1 = helpers->ReadIntPtr(PanelBase + 0x678, false);
	INT_PTR PanelBase2 = helpers->ReadIntPtr(PanelBase1 + 0x14, false);
	INT_PTR PanelBase3 = helpers->ReadIntPtr(PanelBase2 + 0x30, false);
	UINT8 PanelBase4 = helpers->ReadByte(PanelBase3 + 0x2C, false);
	UINT8 Wheels = helpers->ReadByte(PanelBase3 + 0xB4, false);

	if (WallBase4 != NULL)
	{
		triggers->Springi(0.6);
	}

	if (Wheels > 0)
	{
		double percentForce = Wheels / 37.0;
		triggers->Sine(80, 80, percentForce);
	}

	if ((WallBase4 > 0) && (PanelBase4 > 0))
	{
		double percentForce = (PanelBase4) / 8.0;
		double percentLength = 100;
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((WallBase4 < 0) && (PanelBase4 > 0))
	{
		double percentForce = (PanelBase4) / 8.0;
		double percentLength = 100;
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
	}
}
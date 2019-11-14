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
#include "SDL.h"
#include "FastBeatLoopPC.h"
#include <Windows.h>
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
static SDL_Event e;
static bool confirmA;
static bool cancelA;
static bool saveA;
static bool viewA;
static bool shiftupA;
static bool shiftdownA;
static bool dpadupA;
static bool dpaddownA;
static bool dpadleftA;
static bool dpadrightA;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
static int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
static int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
//static int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
static int InputDeviceCombinedPedals = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceCombinedPedals"), 0, settingsFilename);
static int SteeringDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("SteeringDeadzone"), 0, settingsFilename);
static int PedalDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("PedalDeadzone"), 0, settingsFilename);
static int SequentialGears = GetPrivateProfileInt(TEXT("Settings"), TEXT("SequentialGears"), 0, settingsFilename);
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ShowAxisForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowAxisForSetup"), 0, settingsFilename);
static int ExitButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButton"), 0, settingsFilename);
static int ConfirmButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConfirmButton"), 0, settingsFilename);
static int CancelButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("CancelButton"), 0, settingsFilename);
static int SaveDeleteButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("SaveDeleteButton"), 0, settingsFilename);
static int ViewButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButton"), 0, settingsFilename);
static int ShiftUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUp"), 0, settingsFilename);
static int ShiftDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDown"), 0, settingsFilename);
static int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
static int ConfirmButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConfirmButtonDevice2"), 0, settingsFilename);
static int CancelButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CancelButtonDevice2"), 0, settingsFilename);
static int SaveDeleteButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SaveDeleteButtonDevice2"), 0, settingsFilename);
static int ViewButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButtonDevice2"), 0, settingsFilename);
static int ShiftUpDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUpDevice2"), 0, settingsFilename);
static int ShiftDownDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDownDevice2"), 0, settingsFilename);

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		//if (GetAsyncKeyState(VK_ESCAPE))
		//{
		//	TerminateProcess(GetCurrentProcess(), 0);
		//}

		//Config Below In Game
		myHelpers->WriteByte(0xA4136C, 0xB, false); //Accl
		myHelpers->WriteByte(0xA41368, 0x1, false); //Axis or Button
		myHelpers->WriteByte(0xA4137C, 0xA, false); //Brake
		myHelpers->WriteByte(0xA41378, 0x1, false); //Axis or Button
		myHelpers->WriteByte(0xA41394, 0x5, false); //Shift Up
		myHelpers->WriteByte(0xA41390, 0x0, false); //Axis or Button
		myHelpers->WriteByte(0xA4138C, 0x4, false); //Shift Down
		myHelpers->WriteByte(0xA41388, 0x0, false); //Axis or Button
		myHelpers->WriteByte(0xA4135C, 0x9, false); //Steering Left
		myHelpers->WriteByte(0xA41358, 0x1, false); //Axis or Button
		myHelpers->WriteByte(0xA41364, 0x8, false); //Steering Right
		myHelpers->WriteByte(0xA41360, 0x1, false); //Axis or Button
		myHelpers->WriteByte(0xA41384, 0x2, false); //Save Delete
		myHelpers->WriteByte(0xA41380, 0x0, false); //Axis or Button
		myHelpers->WriteByte(0xA4134C, 0x0, false); //Confirm
		myHelpers->WriteByte(0xA41348, 0x0, false); //Axis or Button
		myHelpers->WriteByte(0xA41354, 0x1, false); //Cancel
		myHelpers->WriteByte(0xA41350, 0x0, false); //Axis or Button
		myHelpers->WriteByte(0xA41374, 0x3, false); //View Change
		myHelpers->WriteByte(0xA41370, 0x0, false); //Axis or Button
	}	
	return 0;
}

void FastBeatPC::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (InputDeviceWheelEnable == 1)
	{
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
		SDL_Thread* thread;
		thread = SDL_CreateThread(RunningThread, "RunningThread", (void*)NULL);

		// Dpad stuff here to set as any button
		char DpadUpChar[256];
		char DpadDownChar[256];
		char DpadLeftChar[256];
		char DpadRightChar[256];
		char DpadUpCharDevice2[256];
		char DpadDownCharDevice2[256];
		char DpadLeftCharDevice2[256];
		char DpadRightCharDevice2[256];
		GetPrivateProfileStringA("Settings", "DpadUp", "", DpadUpChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadDown", "", DpadDownChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadLeft", "", DpadLeftChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadRight", "", DpadRightChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadUpDevice2", "", DpadUpCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadDownDevice2", "", DpadDownCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadLeftDevice2", "", DpadLeftCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadRightDevice2", "", DpadRightCharDevice2, 256, ".\\FFBplugin.ini");
		std::string exit("ExitButton");
		std::string confirm("ConfirmButton");
		std::string cancel("CancelButton");
		std::string save("SaveDeleteButton");
		std::string view("ViewButton");
		std::string sftup("ShiftUp");
		std::string sftdown("ShiftDown");
		std::string dpdupgame("DpadUpGame");
		std::string dpddowngame("DpadDownGame");
		std::string dpdleftgame("DpadLeftGame");
		std::string dpdrightgame("DpadRightGame");
		std::string exit2("ExitButtonDevice2");
		std::string confirm2("ConfirmButtonDevice2");
		std::string cancel2("CancelButtonDevice2");
		std::string save2("SaveDeleteButtonDevice2");
		std::string view2("ViewButtonDevice2");
		std::string sftup2("ShiftUpDevice2");
		std::string sftdown2("ShiftDownDevice2");
		std::string dpdupgame2("DpadUpGameDevice2");
		std::string dpddowngame2("DpadDownGameDevice2");
		std::string dpdleftgame2("DpadLeftGameDevice2");
		std::string dpdrightgame2("DpadRightGameDevice2");
		std::string dpdup(DpadUpChar);
		std::string dpddown(DpadDownChar);
		std::string dpdleft(DpadLeftChar);
		std::string dpdright(DpadRightChar);
		std::string dpdup2(DpadUpCharDevice2);
		std::string dpddown2(DpadDownCharDevice2);
		std::string dpdleft2(DpadLeftCharDevice2);
		std::string dpdright2(DpadRightCharDevice2);

		//Added 2nd device stuff from here
		wchar_t* deviceGUIDString2 = new wchar_t[256];
		int Device2GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device2GUID"), NULL, deviceGUIDString2, 256, settingsFilename);
		char joystick_guid[256];
		sprintf(joystick_guid, "%S", deviceGUIDString2);
		SDL_JoystickGUID guid, dev_guid;
		int numJoysticks = SDL_NumJoysticks();
		std::string njs = std::to_string(numJoysticks);
		((char)njs.c_str());
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* js2 = SDL_JoystickOpen(i);
			joystick_index2 = SDL_JoystickInstanceID(js2);
			SDL_JoystickGUID guid = SDL_JoystickGetGUID(js2);
			char guid_str[1024];
			SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
			const char* name = SDL_JoystickName(js2);
			char text[256];
			sprintf(text, "Joystick: %d / Name: %s / GUID: %s\n", i, name, guid_str);
			guid = SDL_JoystickGetGUIDFromString(joystick_guid);
			dev_guid = SDL_JoystickGetGUID(js2);
			SDL_JoystickClose(js2);
			if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
			{
				GameController2 = SDL_JoystickOpen(i);
				break;
			}
		}

		const int WHEEL_DEAD_ZONE = (SteeringDeadzone * 100.0);
		const int ACCL_DEAD_ZONE = (PedalDeadzone * 100.0);
		const int BRAKE_DEAD_ZONE = (PedalDeadzone * 100.0);
		const int SETUP_DEAD_ZONE = 20000;

		HMODULE hMod = GetModuleHandleA("dinput8.dll");
		if (hMod)
		{
			void* fn = GetProcAddress(hMod, "GetdfDIJoystick");
			helpers->WriteNop((INT_PTR)fn + 0x5C0C, false);
			helpers->WriteNop((INT_PTR)fn + 0x5C0D, false);
			helpers->WriteNop((INT_PTR)fn + 0x5C14, false);
			helpers->WriteNop((INT_PTR)fn + 0x5C15, false);
		}

		while (SDL_WaitEvent(&e) != 0)
		{
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;
			INT_PTR InputBase = helpers->ReadIntPtr(0x641074, true);
			INT_PTR InputBase1 = helpers->ReadIntPtr(InputBase + 0x8, false);
			INT_PTR InputBase2 = helpers->ReadIntPtr(InputBase1 + 0x450, false);
			INT_PTR InputBase3 = helpers->ReadIntPtr(InputBase2 + 0x8, false);
			INT_PTR InputBase4 = helpers->ReadIntPtr(InputBase3 + 0x8, false);
			UINT8 DinputConfirm = helpers->ReadByte(InputBase4 + 0x164, false);
			UINT8 DinputCancel = helpers->ReadByte(InputBase4 + 0x165, false);
			UINT8 DinputSave = helpers->ReadByte(InputBase4 + 0x166, false);
			UINT8 DinputView = helpers->ReadByte(InputBase4 + 0x167, false);			
			UINT8 DinputShiftDown = helpers->ReadByte(InputBase4 + 0x168, false);
			UINT8 DinputShiftUp = helpers->ReadByte(InputBase4 + 0x169, false);
			INT_PTR DinputDpad = helpers->ReadIntPtr(InputBase4 + 0xA8, false);
			UINT8 XinputConfirm = helpers->ReadByte(InputBase4 + 0x27, false);
			UINT8 XinputCancel = helpers->ReadByte(InputBase4 + 0x28, false);
			UINT8 XinputSave = helpers->ReadByte(InputBase4 + 0x29, false);
			UINT8 XinputView = helpers->ReadByte(InputBase4 + 0x2A, false);
			UINT8 XinputShiftDown = helpers->ReadByte(InputBase4 + 0x2B, false);
			UINT8 XinputShiftUp = helpers->ReadByte(InputBase4 + 0x2C, false);
			INT_PTR XinputDpad = helpers->ReadIntPtr(InputBase4 + 0x23, false);
			
			if ((e.type == SDL_JOYAXISMOTION) & (ShowAxisForSetup == 0))
			{
				if (e.jaxis.which == joystick_index1)
				{
					if (e.jaxis.axis == InputDeviceWheelSteeringAxis)
					{
						if (e.jaxis.value < -WHEEL_DEAD_ZONE)
						{
							e.jaxis.value = e.jaxis.value + WHEEL_DEAD_ZONE;
							{
								helpers->WriteIntPtr(InputBase4 + 0x98, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
								helpers->WriteIntPtr(InputBase4 + 0x13, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
							}						
						}
						else if (e.jaxis.value > WHEEL_DEAD_ZONE)
						{
							e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
							{
								helpers->WriteIntPtr(InputBase4 + 0x98, (e.jaxis.value / 32567.0) * 1000000000.0, false);
								helpers->WriteIntPtr(InputBase4 + 0x13, (e.jaxis.value / 32567.0) * 1000000000.0, false);
							}
						}
						else if ((e.jaxis.value < WHEEL_DEAD_ZONE) & (e.jaxis.value > -WHEEL_DEAD_ZONE))
						{
							helpers->WriteIntPtr(InputBase4 + 0x98, 0, false);
							helpers->WriteIntPtr(InputBase4 + 0x13, 0, false);
						}
					}
					/*if (InputDeviceWheelReverseAxis == 1)
					{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (e.jaxis.value / 32567.0) * 1000000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, (e.jaxis.value / 32567.0) * 1000000000.0, false);
									}
								}
								else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
								{
									helpers->WriteIntPtr(InputBase4 + 0x9C, 0, false);
									helpers->WriteIntPtr(InputBase4 + 0xF, 0, false);
								}
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (e.jaxis.value / 32567.0) * 1000000000.0, false);
									}
								}
							}
							else if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + BRAKE_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
									}
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - BRAKE_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (e.jaxis.value / 32567.0) * 1000000000.0, false);
									}
								}
							}
						}
					}*/
					//else
					//{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, (-e.jaxis.value / -32568.0) * 1000000000.0, false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, (e.jaxis.value / 32567.0) * 1000000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, (e.jaxis.value / 32567.0) * 1000000000.0, false);
									}
								}
								else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
								{
									helpers->WriteIntPtr(InputBase4 + 0x9C, 0, false);
									helpers->WriteIntPtr(InputBase4 + 0xF, 0, false);
								}
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, -((-e.jaxis.value / -32568.0) * 500000000.0) - 500000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, -((-e.jaxis.value / -32568.0) * 500000000.0) - 500000000.0, false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, -((e.jaxis.value / 32567.0) * 500000000.0) - 500000000.0, false);
										helpers->WriteIntPtr(InputBase4 + 0xF, -((e.jaxis.value / 32567.0) * 500000000.0) - 500000000.0, false);
									}
								}
							}
							if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + BRAKE_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, 500000000.0 + ((-e.jaxis.value / -32568.0) * 500000000.0), false);
										helpers->WriteIntPtr(InputBase4 + 0xF, 500000000.0 + ((-e.jaxis.value / -32568.0) * 500000000.0), false);
									}
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - BRAKE_DEAD_ZONE;
									{
										helpers->WriteIntPtr(InputBase4 + 0x9C, 500000000.0 + ((e.jaxis.value / 32567.0) * 500000000.0), false);
										helpers->WriteIntPtr(InputBase4 + 0xF, 500000000.0 + ((e.jaxis.value / 32567.0) * 500000000.0), false);
									}
								}
							}
						}
					}
				}
			//}

			if (ShowAxisForSetup == 1)
			{
				if (e.type == SDL_JOYAXISMOTION)
				{
					if (e.jaxis.which == joystick_index1)
					{
						if (e.jaxis.axis >= 0)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								char buff[100];
								sprintf_s(buff, "Axis %d Moved", e.jaxis.axis);
								MessageBoxA(NULL, buff, "", NULL);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								char buff[100];
								sprintf_s(buff, "Axis %d Moved", e.jaxis.axis);
								MessageBoxA(NULL, buff, "", NULL);
							}
						}
					}
				}
			}

			if (ShowButtonNumbersForSetup == 1)
			{
				if (e.type == SDL_JOYBUTTONDOWN)
				{
					if (e.jaxis.which == joystick_index1 || e.jaxis.which == joystick_index2)
					{
						if (e.jbutton.button >= 0)
						{
							char buff[100];
							sprintf_s(buff, "Button %d Pressed", e.jbutton.button);
							MessageBoxA(NULL, buff, "", NULL);
						}
					}
				}
			}

			if (e.jhat.type == SDL_JOYHATMOTION)
			{
				if (e.jhat.value == SDL_HAT_CENTERED)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (confirmA)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm -= 0x80, false);
							confirmA = false;
						}
						if (cancelA)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel -= 0x80, false);
							cancelA = false;
						}
						if (saveA)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave -= 0x80, false);
							saveA = false;
						}
						if (viewA)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView -= 0x80, false);
							viewA = false;
						}
						if (shiftupA)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp -= 0x80, false);
							shiftupA = false;
						}
						if (shiftdownA)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown -= 0x80, false);
							shiftdownA = false;
						}
						if (dpadupA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad += 0xFFFFFFFF, false);
							dpadupA = false;
						}
						if (dpaddownA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFFB9AF, false);
							dpaddownA = false;
						}
						if (dpadleftA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFF9687, false);
							dpadleftA = false;
						}
						if (dpadrightA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFFDCD7, false);
							dpadrightA = false;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (confirmA)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm -= 0x80, false);
							confirmA = false;
						}
						if (cancelA)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel -= 0x80, false);
							cancelA = false;
						}
						if (saveA)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave -= 0x80, false);
							saveA = false;
						}
						if (viewA)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView -= 0x80, false);
							viewA = false;
						}
						if (shiftupA)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp -= 0x80, false);
							shiftupA = false;
						}
						if (shiftdownA)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown -= 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown -= 0x80, false);
							shiftdownA = false;
						}
						if (dpadupA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad += 0xFFFFFFFF, false);
							dpadupA = false;
						}
						if (dpaddownA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFFB9AF, false);
							dpaddownA = false;
						}
						if (dpadleftA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFF9687, false);
							dpadleftA = false;
						}
						if (dpadrightA)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad += 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad += 0xFFFFDCD7, false);
							dpadrightA = false;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_UP)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdup.compare(exit) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdup.compare(confirm) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdup.compare(cancel) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdup.compare(view) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdup.compare(save) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdup.compare(sftup) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdup.compare(sftdown) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdup.compare(dpdupgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdup.compare(dpddowngame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdup.compare(dpdleftgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdup.compare(dpdrightgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdup2.compare(exit2) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdup2.compare(confirm2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdup2.compare(cancel2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdup2.compare(view2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdup2.compare(save2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdup2.compare(sftup2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdup2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdup2.compare(dpdupgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdup2.compare(dpddowngame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdup2.compare(dpdleftgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdup2.compare(dpdrightgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_DOWN)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpddown.compare(exit) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpddown.compare(confirm) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpddown.compare(cancel) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpddown.compare(view) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpddown.compare(save) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpddown.compare(sftup) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpddown.compare(sftdown) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpddown.compare(dpdupgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpddown.compare(dpddowngame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpddown.compare(dpdleftgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpddown.compare(dpdrightgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpddown2.compare(exit2) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpddown2.compare(confirm2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpddown2.compare(cancel2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpddown2.compare(view2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpddown2.compare(save2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpddown2.compare(sftup2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpddown2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpddown2.compare(dpdupgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpddown2.compare(dpddowngame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpddown2.compare(dpdleftgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpddown2.compare(dpdrightgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_LEFT)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdleft.compare(exit) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdleft.compare(confirm) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdleft.compare(cancel) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdleft.compare(view) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdleft.compare(save) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdleft.compare(sftup) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdleft.compare(sftdown) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdleft.compare(dpdupgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdleft.compare(dpddowngame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdleft.compare(dpdleftgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdleft.compare(dpdrightgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdleft2.compare(exit2) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdleft2.compare(confirm2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdleft2.compare(cancel2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdleft2.compare(view2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdleft2.compare(save2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdleft2.compare(sftup2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdleft2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdleft2.compare(dpdupgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdleft2.compare(dpddowngame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdleft2.compare(dpdleftgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdleft2.compare(dpdrightgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_RIGHT)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdright.compare(exit) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdright.compare(confirm) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdright.compare(cancel) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdright.compare(view) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdright.compare(save) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdright.compare(sftup) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdright.compare(sftdown) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdright.compare(dpdupgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdright.compare(dpddowngame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdright.compare(dpdleftgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdright.compare(dpdrightgame) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdright2.compare(exit2) == 0)
						{
							TerminateProcess(GetCurrentProcess(), 0);
						}
						if (dpdright2.compare(confirm2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
							confirmA = true;
						}
						if (dpdright2.compare(cancel2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
							cancelA = true;
						}
						if (dpdright2.compare(view2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
							viewA = true;
						}
						if (dpdright2.compare(save2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
							saveA = true;
						}
						if (dpdright2.compare(sftup2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
							shiftupA = true;
						}
						if (dpdright2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
							helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
							shiftdownA = true;
						}
						if (dpdright2.compare(dpdupgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFFFFF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, XinputDpad -= 0xFFFFFFFF, false);
							dpadupA = true;
						}
						if (dpdright2.compare(dpddowngame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFB9AF, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFB9AF, false);
							dpaddownA = true;
						}
						if (dpdright2.compare(dpdleftgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFF9687, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFF9687, false);
							dpadleftA = true;
						}
						if (dpdright2.compare(dpdrightgame2) == 0)
						{
							helpers->WriteIntPtr(InputBase4 + 0xA8, DinputDpad -= 0xFFFFDCD7, false);
							helpers->WriteIntPtr(InputBase4 + 0x23, DinputDpad -= 0xFFFFDCD7, false);
							dpadrightA = true;
						}
					}
				}
			}

			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == ConfirmButton)
					{
						helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
					}
					if (e.jbutton.button == ExitButton)
					{
						TerminateProcess(GetCurrentProcess(), 0);
					}
					if (e.jbutton.button == CancelButton)
					{
						helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
					}
					if (e.jbutton.button == SaveDeleteButton)
					{
						helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
					}					
					if (e.jbutton.button == ShiftDown)
					{
						helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
					}
					if (e.jbutton.button == ShiftUp)
					{
						helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == ConfirmButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x164, DinputConfirm += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x27, XinputConfirm += 0x80, false);
					}
					if (e.jbutton.button == ExitButtonDevice2)
					{
						TerminateProcess(GetCurrentProcess(), 0);
					}
					if (e.jbutton.button == CancelButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x165, DinputCancel += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x28, XinputCancel += 0x80, false);
					}
					if (e.jbutton.button == SaveDeleteButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x166, DinputSave += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x29, XinputSave += 0x80, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x167, DinputView += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2A, XinputView += 0x80, false);
					}
					if (e.jbutton.button == ShiftDownDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown += 0x80, false);
					}
					if (e.jbutton.button == ShiftUpDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp += 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp += 0x80, false);
					}
				}
			}
			if (e.type == SDL_JOYBUTTONUP)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == ConfirmButton)
					{
						helpers->WriteByte(InputBase4 + 0x164, DinputConfirm -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x27, XinputConfirm -= 0x80, false);
					}
					if (e.jbutton.button == CancelButton)
					{
						helpers->WriteByte(InputBase4 + 0x165, DinputCancel -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x28, XinputCancel -= 0x80, false);
					}
					if (e.jbutton.button == SaveDeleteButton)
					{
						helpers->WriteByte(InputBase4 + 0x166, DinputSave -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x29, XinputSave -= 0x80, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteByte(InputBase4 + 0x167, DinputView -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2A, XinputView -= 0x80, false);
					}
					if (e.jbutton.button == ShiftDown)
					{
						helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown -= 0x80, false);
					}
					if (e.jbutton.button == ShiftUp)
					{
						helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp -= 0x80, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == ConfirmButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x164, DinputConfirm -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x27, XinputConfirm -= 0x80, false);
					}
					if (e.jbutton.button == CancelButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x165, DinputCancel -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x28, XinputCancel -= 0x80, false);
					}
					if (e.jbutton.button == SaveDeleteButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x166, DinputSave -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x29, XinputSave -= 0x80, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x167, DinputView -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2A, XinputView -= 0x80, false);
					}
					if (e.jbutton.button == ShiftDownDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x168, DinputShiftDown -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2B, XinputShiftDown -= 0x80, false);
					}
					if (e.jbutton.button == ShiftUpDevice2)
					{
						helpers->WriteByte(InputBase4 + 0x169, DinputShiftUp -= 0x80, false);
						helpers->WriteByte(InputBase4 + 0x2C, XinputShiftUp -= 0x80, false);
					}
				}
			}
		}
	}
	else
	{
		SDL_Thread* thread;
		thread = SDL_CreateThread(RunningThread, "RunningThread", (void*)NULL);
		while (SDL_WaitEvent(&e) != 0)
		{
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;
		}
	}
}
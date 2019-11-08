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
extern HINSTANCE gl_dinput8Dll;
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

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
static int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
static int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
static int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
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
static int ShiftUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUp"), 0, settingsFilename);
static int ShiftDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDown"), 0, settingsFilename);
static int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
static int ConfirmButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConfirmButtonDevice2"), 0, settingsFilename);
static int CancelButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CancelButtonDevice2"), 0, settingsFilename);
static int SaveDeleteButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SaveDeleteButtonDevice2"), 0, settingsFilename);
static int ViewButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButtonDevice2"), 0, settingsFilename);
static int ShiftUpDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUpDevice2"), 0, settingsFilename);
static int ShiftDownDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDownDevice2"), 0, settingsFilename);

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			TerminateProcess(GetCurrentProcess(), 0);
		}
	}
	return 0;
}

void FastBeatPC::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (InputDeviceWheelEnable == 1)
	{
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
		std::string exit2("ExitButtonDevice2");
		std::string confirm2("ConfirmButtonDevice2");
		std::string cancel2("CancelButtonDevice2");
		std::string save2("SaveDeleteButtonDevice2");
		std::string view2("ViewButtonDevice2");
		std::string sftup2("ShiftUpDevice2");
		std::string sftdown2("ShiftDownDevice2");
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
		const int ACCL_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int BRAKE_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int SETUP_DEAD_ZONE = 20000;

		/*helpers->WriteNop(0x2F07A, true);
		helpers->WriteNop(0x2F07B, true);
		helpers->WriteNop(0x2F07C, true);
		helpers->WriteNop(0x2F07D, true);
		helpers->WriteNop(0x2F07E, true);
		helpers->WriteNop(0x2F07F, true);

		helpers->WriteNop(0x2F1E0, true);
		helpers->WriteNop(0x2F1E1, true);
		helpers->WriteNop(0x2F1E2, true);
		helpers->WriteNop(0x2F1E3, true);
		helpers->WriteNop(0x2F1E4, true);
		helpers->WriteNop(0x2F1E5, true);*/

		helpers->WriteNop(0x2E35C, true);
		helpers->WriteNop(0x2E35D, true);
		helpers->WriteNop(0x2E35E, true);
		helpers->WriteNop(0x2E35F, true);
		helpers->WriteNop(0x2E360, true);
		helpers->WriteNop(0x2E361, true);

		helpers->WriteNop(0x2E381, true);
		helpers->WriteNop(0x2E382, true);
		helpers->WriteNop(0x2E383, true);
		helpers->WriteNop(0x2E384, true);
		helpers->WriteNop(0x2E385, true);
		helpers->WriteNop(0x2E386, true);

		helpers->WriteNop(0x2E456, true);
		helpers->WriteNop(0x2E457, true);
		helpers->WriteNop(0x2E458, true);
		helpers->WriteNop(0x2E459, true);
		helpers->WriteNop(0x2E45A, true);
		helpers->WriteNop(0x2E45B, true);

		helpers->WriteNop(0x2E5E2, true);
		helpers->WriteNop(0x2E5E3, true);
		helpers->WriteNop(0x2E5E4, true);
		helpers->WriteNop(0x2E5E5, true);
		helpers->WriteNop(0x2E5E6, true);
		helpers->WriteNop(0x2E5E7, true);

		helpers->WriteNop(0x2E81B, true);
		helpers->WriteNop(0x2E81C, true);
		helpers->WriteNop(0x2E81D, true);
		helpers->WriteNop(0x2E81E, true);
		helpers->WriteNop(0x2E81F, true);
		helpers->WriteNop(0x2E820, true);

		helpers->WriteNop(0x2E9A7, true);
		helpers->WriteNop(0x2E9A8, true);
		helpers->WriteNop(0x2E9A9, true);
		helpers->WriteNop(0x2E9AA, true);
		helpers->WriteNop(0x2E9AB, true);
		helpers->WriteNop(0x2E9AC, true);

		helpers->WriteNop(0x2EA6D, true);
		helpers->WriteNop(0x2EA6E, true);
		helpers->WriteNop(0x2EA6F, true);
		helpers->WriteNop(0x2EA70, true);
		helpers->WriteNop(0x2EA71, true);
		helpers->WriteNop(0x2EA72, true);

		helpers->WriteNop(0x2E6A0, true);
		helpers->WriteNop(0x2E6A1, true);
		helpers->WriteNop(0x2E6A2, true);
		helpers->WriteNop(0x2E6A3, true);
		helpers->WriteNop(0x2E6A4, true);
		helpers->WriteNop(0x2E6A5, true);

		helpers->WriteNop(0x2E75C, true);
		helpers->WriteNop(0x2E75D, true);
		helpers->WriteNop(0x2E75E, true);
		helpers->WriteNop(0x2E75F, true);
		helpers->WriteNop(0x2E760, true);
		helpers->WriteNop(0x2E761, true);

		/*helpers->WriteNop(0x2F17C, true);
		helpers->WriteNop(0x2F17D, true);
		helpers->WriteNop(0x2F17E, true);
		helpers->WriteNop(0x2F17F, true);
		helpers->WriteNop(0x2F180, true);
		helpers->WriteNop(0x2F181, true);

		helpers->WriteNop(0x2F024, true);
		helpers->WriteNop(0x2F025, true);
		helpers->WriteNop(0x2F026, true);
		helpers->WriteNop(0x2F027, true);
		helpers->WriteNop(0x2F028, true);
		helpers->WriteNop(0x2F029, true);*/

		while (SDL_WaitEvent(&e) != 0)
		{
			INT_PTR AcclBase = helpers->ReadIntPtr(0x641074, true);
			INT_PTR AcclBase1 = helpers->ReadIntPtr(AcclBase + 0x8, false);
			INT_PTR AcclBase2 = helpers->ReadIntPtr(AcclBase1 + 0x0, false);
			UINT8 Buttons = helpers->ReadByte(AcclBase2 + 0x5A0, false);
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;
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
								helpers->WriteFloat32(AcclBase1 + 0x654, -1.0 - (-e.jaxis.value / -32568.0) + 1.0, false);
								helpers->WriteFloat32(AcclBase1 + 0x650, 0.0, false);
							}
						}
						else if (e.jaxis.value > WHEEL_DEAD_ZONE)
						{
							e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
							{
								helpers->WriteFloat32(AcclBase1 + 0x650, (e.jaxis.value / 32567.0), false);
								helpers->WriteFloat32(AcclBase1 + 0x654, 0.0, false);
							}
						}
						else if ((e.jaxis.value < WHEEL_DEAD_ZONE) & (e.jaxis.value > -WHEEL_DEAD_ZONE))
						{
							helpers->WriteFloat32(AcclBase1 + 0x650, 0.0, false);
							helpers->WriteFloat32(AcclBase1 + 0x654, 0.0, false);
						}
					}
					if (InputDeviceWheelReverseAxis == 1)
					{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									int acclfloat = ((-e.jaxis.value + ACCL_DEAD_ZONE) / 128.5);
									if ((acclfloat >= 0) && (acclfloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x664, ((acclfloat) / 255.0), false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									int brakefloat = ((e.jaxis.value + ACCL_DEAD_ZONE) / 128);
									if ((brakefloat >= 0) && (brakefloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x660, ((brakefloat) / 255.0), false);
									}
								}
								else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
								{
									helpers->WriteFloat32(AcclBase1 + 0x664, 0.0, false);
									helpers->WriteFloat32(AcclBase1 + 0x660, 0.0, false);
								}
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int acclfloat = 127 - e.jaxis.value;
									if ((acclfloat > 127) && (acclfloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x664, ((acclfloat) / 255.0), false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int acclfloat = 128 - e.jaxis.value;
									if ((acclfloat >= 0) && (acclfloat < 128))
									{
										helpers->WriteFloat32(AcclBase1 + 0x664, ((acclfloat) / 255.0), false);
									}
								}
							}
							else if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int brakefloat = 127 - e.jaxis.value;
									if ((brakefloat > 127) && (brakefloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x660, ((brakefloat) / 255.0), false);
									}
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int brakefloat = 128 - e.jaxis.value;
									if ((brakefloat >= 0) && (brakefloat < 128))
									{
										helpers->WriteFloat32(AcclBase1 + 0x660, ((brakefloat) / 255.0), false);
									}
								}
							}
						}
					}
					else
					{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.value < -ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value;
								int acclfloat = ((e.jaxis.value) / 128.5);
								{
									helpers->WriteFloat32(AcclBase1 + 0x664, ((255 + acclfloat) / 255.0), false);
								}
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value;
								int brakefloat = ((-e.jaxis.value) / 128.5);
								{
									helpers->WriteFloat32(AcclBase1 + 0x660, ((254 + brakefloat) / 255.0), false);
								}
							}
							else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
							{
								helpers->WriteFloat32(AcclBase1 + 0x664, 1.0, false);
								helpers->WriteFloat32(AcclBase1 + 0x660, 1.0, false);
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int acclfloat = 128 + e.jaxis.value;
									if ((acclfloat >= 0) && (acclfloat < 128))
									{
										helpers->WriteFloat32(AcclBase1 + 0x664, ((acclfloat) / 255.0), false);
									}
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int acclfloat = 127 + e.jaxis.value;
									if ((acclfloat > 127) && (acclfloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x664, ((acclfloat) / 255.0), false);
									}
								}
							}
							if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int brakefloat = 128 + e.jaxis.value;
									if ((brakefloat >= 0) && (brakefloat < 128))
									{
										helpers->WriteFloat32(AcclBase1 + 0x660, ((brakefloat) / 255.0), false);
									}
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									int brakefloat = 127 + e.jaxis.value;
									if ((brakefloat > 127) && (brakefloat < 256))
									{
										helpers->WriteFloat32(AcclBase1 + 0x660, ((brakefloat) / 255.0), false);
									}
								}
							}
						}
					}
				}
			}

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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x20, false);
							confirmA = false;
						}
						if (cancelA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x10, false);
							cancelA = false;
						}
						if (saveA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x8, false);
							saveA = false;
						}
						if (viewA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x4, false);
							viewA = false;
						}
						if (shiftupA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x2, false);
							shiftupA = false;
						}
						if (shiftdownA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x1, false);
							shiftdownA = false;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (confirmA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x20, false);
							confirmA = false;
						}
						if (cancelA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x10, false);
							cancelA = false;
						}
						if (saveA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x8, false);
							saveA = false;
						}
						if (viewA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x4, false);
							viewA = false;
						}
						if (shiftupA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x2, false);
							shiftupA = false;
						}
						if (shiftdownA)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x1, false);
							shiftdownA = false;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdup.compare(cancel) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdup.compare(view) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdup.compare(save) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdup.compare(sftup) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdup.compare(sftdown) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdup2.compare(cancel2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdup2.compare(view2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdup2.compare(save2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdup2.compare(sftup2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdup2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpddown.compare(cancel) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpddown.compare(view) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpddown.compare(save) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpddown.compare(sftup) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpddown.compare(sftdown) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpddown2.compare(cancel2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpddown2.compare(view2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpddown2.compare(save2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpddown2.compare(sftup2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpddown2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdleft.compare(cancel) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdleft.compare(view) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdleft.compare(save) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdleft.compare(sftup) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdleft.compare(sftdown) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdleft2.compare(cancel2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdleft2.compare(view2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdleft2.compare(save2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdleft2.compare(sftup2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdleft2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdright.compare(cancel) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdright.compare(view) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdright.compare(save) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdright.compare(sftup) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdright.compare(sftdown) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
							confirmA = true;
						}
						if (dpdright2.compare(cancel2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
							cancelA = true;
						}
						if (dpdright2.compare(view2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
							viewA = true;
						}
						if (dpdright2.compare(save2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
							saveA = true;
						}
						if (dpdright2.compare(sftup2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
							shiftupA = true;
						}
						if (dpdright2.compare(sftdown2) == 0)
						{
							helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
							shiftdownA = true;
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
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
					}
					if (e.jbutton.button == ExitButton)
					{
						TerminateProcess(GetCurrentProcess(), 0);
					}
					if (e.jbutton.button == CancelButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
					}
					if (e.jbutton.button == SaveDeleteButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
					}
					if (e.jbutton.button == ShiftUp)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
					}
					if (e.jbutton.button == ShiftDown)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == ConfirmButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x20, false);
					}
					if (e.jbutton.button == ExitButtonDevice2)
					{
						TerminateProcess(GetCurrentProcess(), 0);
					}
					if (e.jbutton.button == CancelButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x10, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x4, false);
					}
					if (e.jbutton.button == SaveDeleteButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x8, false);
					}
					if (e.jbutton.button == ShiftUpDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x2, false);
					}
					if (e.jbutton.button == ShiftDownDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons += 0x1, false);
					}
				}
			}
			if (e.type == SDL_JOYBUTTONUP)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == ConfirmButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x20, false);
					}
					if (e.jbutton.button == CancelButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x10, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x4, false);
					}
					if (e.jbutton.button == SaveDeleteButton)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x8, false);
					}
					if (e.jbutton.button == ShiftUp)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x2, false);
					}
					if (e.jbutton.button == ShiftDown)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x1, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == ConfirmButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x20, false);
					}
					if (e.jbutton.button == CancelButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x10, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x4, false);
					}
					if (e.jbutton.button == SaveDeleteButtonDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x8, false);
					}
					if (e.jbutton.button == ShiftUpDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x2, false);
					}
					if (e.jbutton.button == ShiftDownDevice2)
					{
						helpers->WriteByte(AcclBase2 + 0x5A0, Buttons -= 0x1, false);
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
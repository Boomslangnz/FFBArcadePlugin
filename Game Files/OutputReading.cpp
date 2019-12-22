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

#include "OutputReading.h"
#include <string>
#include <tchar.h>
#include "SDL.h"

HINSTANCE ProcDLL = NULL;
extern int joystick_index1;
extern int joystick_index2;
extern int joystick_index3;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
extern SDL_Joystick* GameController3;
extern SDL_Haptic* ControllerHaptic3;
extern SDL_Haptic* haptic3;

//Config Settings
extern wchar_t* settingsFilename;
extern int DeviceGUID;
extern int configFeedbackLength;
extern int configGameId;
extern int configMinForce;
extern int configMaxForce;
extern int PowerMode;
extern int EnableRumble;
extern int ReverseRumble;
extern int configFeedbackLength;
extern int configAlternativeMinForceLeft;
extern int configAlternativeMaxForceLeft;
extern int configAlternativeMinForceRight;
extern int configAlternativeMaxForceRight;
extern int configMinForceDevice2;
extern int configMaxForceDevice2;
extern int EnableRumbleDevice2;
extern int ReverseRumbleDevice2;
extern int configAlternativeMinForceLeftDevice2;
extern int configAlternativeMaxForceLeftDevice2;
extern int configAlternativeMinForceRightDevice2;
extern int configAlternativeMaxForceRightDevice2;
extern int configMinForceDevice3;
extern int configMaxForceDevice3;
extern int EnableRumbleDevice3;
extern int ReverseRumbleDevice3;
extern int configAlternativeMinForceLeftDevice3;
extern int configAlternativeMaxForceLeftDevice3;
extern int configAlternativeMinForceRightDevice3;
extern int configAlternativeMaxForceRightDevice3;
extern int SinePeriod;
extern int SineFadePeriod;
extern int SineStrength;
extern int RumbleStrengthLeftMotor;
extern int RumbleStrengthRightMotor;
extern int EnableForceSpringEffect;
extern int ForceSpringStrength;

static int configMinForceDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDaytona2"), 0, settingsFilename);
static int configMaxForceDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDaytona2"), 100, settingsFilename);
static int configAlternativeMinForceLeftDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDaytona2"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDaytona2"), 100, settingsFilename);
static int configAlternativeMinForceRightDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDaytona2"), 0, settingsFilename);
static int configAlternativeMaxForceRightDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDaytona2"), 100, settingsFilename);
static int configFeedbackLengthDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDaytona2"), 120, settingsFilename);
static int PowerModeDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeDaytona2"), 0, settingsFilename);
static int EnableForceSpringEffectDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDaytona2"), 0, settingsFilename);
static int ForceSpringStrengthDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDaytona2"), 0, settingsFilename);

static int configMinForceScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceScud"), 0, settingsFilename);
static int configMaxForceScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceScud"), 100, settingsFilename);
static int configAlternativeMinForceLeftScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftScud"), 0, settingsFilename);
static int configAlternativeMaxForceLeftScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftScud"), 100, settingsFilename);
static int configAlternativeMinForceRightScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightScud"), 0, settingsFilename);
static int configAlternativeMaxForceRightScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightScud"), 100, settingsFilename);
static int configFeedbackLengthScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthScud"), 120, settingsFilename);
static int PowerModeScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeScud"), 0, settingsFilename);
static int EnableForceSpringEffectScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectScud"), 0, settingsFilename);
static int ForceSpringStrengthScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthScud"), 0, settingsFilename);

static int configMinForceLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceLeMans"), 0, settingsFilename);
static int configMaxForceLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceLeMans"), 100, settingsFilename);
static int configAlternativeMinForceLeftLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftLeMans"), 0, settingsFilename);
static int configAlternativeMaxForceLeftLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftLeMans"), 100, settingsFilename);
static int configAlternativeMinForceRightLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightLeMans"), 0, settingsFilename);
static int configAlternativeMaxForceRightLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightLeMans"), 100, settingsFilename);
static int configFeedbackLengthLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthLeMans"), 120, settingsFilename);
static int PowerModeLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeLeMans"), 0, settingsFilename);
static int EnableForceSpringEffectLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectLeMans"), 0, settingsFilename);

static int ForceSpringStrengthLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthLeMans"), 0, settingsFilename);
static int configMinForceDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDirtDevils"), 0, settingsFilename);
static int configMaxForceDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDirtDevils"), 100, settingsFilename);
static int configAlternativeMinForceLeftDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDirtDevils"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDirtDevils"), 100, settingsFilename);
static int configAlternativeMinForceRightDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDirtDevils"), 0, settingsFilename);
static int configAlternativeMaxForceRightDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDirtDevils"), 100, settingsFilename);
static int configFeedbackLengthDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDirtDevils"), 120, settingsFilename);
static int PowerModeDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeDirtDevils"), 0, settingsFilename);
static int EnableForceSpringEffectDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDirtDevils"), 0, settingsFilename);
static int ForceSpringStrengthDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDirtDevils"), 0, settingsFilename);

static int configMinForceSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSRally2"), 0, settingsFilename);
static int configMaxForceSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSRally2"), 100, settingsFilename);
static int configAlternativeMinForceLeftSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSRally2"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSRally2"), 100, settingsFilename);
static int configAlternativeMinForceRightSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSRally2"), 0, settingsFilename);
static int configAlternativeMaxForceRightSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSRally2"), 100, settingsFilename);
static int configFeedbackLengthSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSRally2"), 120, settingsFilename);
static int PowerModeSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSRally2"), 0, settingsFilename);
static int EnableForceSpringEffectSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSRally2"), 0, settingsFilename);
static int ForceSpringStrengthSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSRally2"), 0, settingsFilename);

static int configMinForceECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceECA"), 0, settingsFilename);
static int configMaxForceECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceECA"), 100, settingsFilename);
static int configAlternativeMinForceLeftECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftECA"), 0, settingsFilename);
static int configAlternativeMaxForceLeftECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftECA"), 100, settingsFilename);
static int configAlternativeMinForceRightECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightECA"), 0, settingsFilename);
static int configAlternativeMaxForceRightECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightECA"), 100, settingsFilename);
static int configFeedbackLengthECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthECA"), 120, settingsFilename);
static int PowerModeECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeECA"), 0, settingsFilename);
static int EnableForceSpringEffectECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectECA"), 0, settingsFilename);
static int ForceSpringStrengthECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthECA"), 0, settingsFilename);

static int configMinForceVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceVirtuaRacing"), 0, settingsFilename);
static int configMaxForceVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceVirtuaRacing"), 100, settingsFilename);
static int configAlternativeMinForceLeftVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftVirtuaRacing"), 0, settingsFilename);
static int configAlternativeMaxForceLeftVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftVirtuaRacing"), 100, settingsFilename);
static int configAlternativeMinForceRightVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightVirtuaRacing"), 0, settingsFilename);
static int configAlternativeMaxForceRightVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightVirtuaRacing"), 100, settingsFilename);
static int configFeedbackLengthVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthVirtuaRacing"), 120, settingsFilename);
static int EnableForceSpringEffectVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectVirtuaRacing"), 0, settingsFilename);
static int ForceSpringStrengthVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthVirtuaRacing"), 0, settingsFilename);

static int configMinForceSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSFRush"), 0, settingsFilename);
static int configMaxForceSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSFRush"), 100, settingsFilename);
static int configAlternativeMinForceLeftSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSFRush"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSFRush"), 100, settingsFilename);
static int configAlternativeMinForceRightSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSFRush"), 0, settingsFilename);
static int configAlternativeMaxForceRightSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSFRush"), 100, settingsFilename);
static int configFeedbackLengthSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSFRush"), 120, settingsFilename);
static int PowerModeSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSFRush"), 0, settingsFilename);
static int EnableForceSpringEffectSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSFRush"), 0, settingsFilename);
static int ForceSpringStrengthSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSFRush"), 0, settingsFilename);
static int configMinForceSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSFRushRock"), 0, settingsFilename);
static int configMaxForceSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSFRushRock"), 100, settingsFilename);

static int configAlternativeMinForceLeftSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSFRushRock"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSFRushRock"), 100, settingsFilename);
static int configAlternativeMinForceRightSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSFRushRock"), 0, settingsFilename);
static int configAlternativeMaxForceRightSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSFRushRock"), 100, settingsFilename);
static int configFeedbackLengthSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSFRushRock"), 120, settingsFilename);
static int PowerModeSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSFRushRock"), 0, settingsFilename);
static int EnableForceSpringEffectSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSFRushRock"), 0, settingsFilename);
static int ForceSpringStrengthSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSFRushRock"), 0, settingsFilename);

static int configMinForceCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceCrusnWld"), 0, settingsFilename);
static int configMaxForceCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceCrusnWld"), 100, settingsFilename);
static int configAlternativeMinForceLeftCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftCrusnWld"), 0, settingsFilename);
static int configAlternativeMaxForceLeftCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftCrusnWld"), 100, settingsFilename);
static int configAlternativeMinForceRightCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightCrusnWld"), 0, settingsFilename);
static int configAlternativeMaxForceRightCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightCrusnWld"), 100, settingsFilename);
static int configFeedbackLengthCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthCrusnWld"), 120, settingsFilename);
static int PowerModeCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeCrusnWld"), 0, settingsFilename);
static int EnableForceSpringEffectCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectCrusnWld"), 0, settingsFilename);
static int ForceSpringStrengthCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthCrusnWld"), 0, settingsFilename);

static int configMinForceOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOffRoadC"), 0, settingsFilename);
static int configMaxForceOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOffRoadC"), 100, settingsFilename);
static int configAlternativeMinForceLeftOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftOffRoadC"), 0, settingsFilename);
static int configAlternativeMaxForceLeftOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftOffRoadC"), 100, settingsFilename);
static int configAlternativeMinForceRightOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightOffRoadC"), 0, settingsFilename);
static int configAlternativeMaxForceRightOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightOffRoadC"), 100, settingsFilename);
static int configFeedbackLengthOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthOffRoadC"), 120, settingsFilename);
static int PowerModeOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeOffRoadC"), 0, settingsFilename);
static int EnableForceSpringEffectOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectOffRoadC"), 0, settingsFilename);
static int ForceSpringStrengthOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthOffRoadC"), 0, settingsFilename);

static int configMinForceCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceCrusnUSA"), 0, settingsFilename);
static int configMaxForceCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceCrusnUSA"), 100, settingsFilename);
static int configAlternativeMinForceLeftCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftCrusnUSA"), 0, settingsFilename);
static int configAlternativeMaxForceLeftCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftCrusnUSA"), 100, settingsFilename);
static int configAlternativeMinForceRightCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightCrusnUSA"), 0, settingsFilename);
static int configAlternativeMaxForceRightCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightCrusnUSA"), 100, settingsFilename);
static int configFeedbackLengthCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthCrusnUSA"), 120, settingsFilename);
static int PowerModeCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeCrusnUSA"), 0, settingsFilename);
static int EnableForceSpringEffectCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectCrusnUSA"), 0, settingsFilename);
static int ForceSpringStrengthCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthCrusnUSA"), 0, settingsFilename);

static int configMinForceCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceCalSpeed"), 0, settingsFilename);
static int configMaxForceCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceCalSpeed"), 100, settingsFilename);
static int configAlternativeMinForceLeftCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftCalSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceLeftCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftCalSpeed"), 100, settingsFilename);
static int configAlternativeMinForceRightCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightCalSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceRightCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightCalSpeed"), 100, settingsFilename);
static int configFeedbackLengthCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthCalSpeed"), 120, settingsFilename);
static int PowerModeCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeCalSpeed"), 0, settingsFilename);
static int EnableForceSpringEffectCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectCalSpeed"), 0, settingsFilename);
static int ForceSpringStrengthCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthCalSpeed"), 0, settingsFilename);

static int configMinForceSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSFRush2049"), 0, settingsFilename);
static int configMaxForceSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSFRush2049"), 100, settingsFilename);
static int configAlternativeMinForceLeftSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSFRush2049"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSFRush2049"), 100, settingsFilename);
static int configAlternativeMinForceRightSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSFRush2049"), 0, settingsFilename);
static int configAlternativeMaxForceRightSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSFRush2049"), 100, settingsFilename);
static int configFeedbackLengthSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSFRush2049"), 120, settingsFilename);
static int PowerModeSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSFRush2049"), 0, settingsFilename);
static int EnableForceSpringEffectSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSFRush2049"), 0, settingsFilename);
static int ForceSpringStrengthSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSFRush2049"), 0, settingsFilename);

static int configMinForceHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceHardD"), 0, settingsFilename);
static int configMaxForceHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceHardD"), 100, settingsFilename);
static int configAlternativeMinForceLeftHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftHardD"), 0, settingsFilename);
static int configAlternativeMaxForceLeftHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftHardD"), 100, settingsFilename);
static int configAlternativeMinForceRightHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightHardD"), 0, settingsFilename);
static int configAlternativeMaxForceRightHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightHardD"), 100, settingsFilename);
static int configFeedbackLengthHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthHardD"), 120, settingsFilename);
static int PowerModeHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeHardD"), 0, settingsFilename);
static int EnableForceSpringEffectHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectHardD"), 0, settingsFilename);
static int ForceSpringStrengthHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthHardD"), 0, settingsFilename);

static int configMinForceRevX = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRevX"), 0, settingsFilename);
static int configMaxForceRevX = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRevX"), 100, settingsFilename);
static int configMinForceRevXDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRevXDevice2"), 0, settingsFilename);
static int configMaxForceRevXDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRevXDevice2"), 100, settingsFilename);
static int configMinForceRevXDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRevXDevice3"), 0, settingsFilename);
static int configMaxForceRevXDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRevXDevice3"), 100, settingsFilename);
static int RumbleStrengthLeftMotorRevX = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorRevX"), 0, settingsFilename);
static int RumbleStrengthRightMotorRevX = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorRevX"), 0, settingsFilename);

static int configMinForceZombRaid = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceZombRaid"), 0, settingsFilename);
static int configMaxForceZombRaid = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceZombRaid"), 100, settingsFilename);
static int configMinForceZombRaidDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceZombRaidDevice2"), 0, settingsFilename);
static int configMaxForceZombRaidDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceZombRaidDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorZombRaid = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorZombRaid"), 0, settingsFilename);
static int RumbleStrengthRightMotorZombRaid = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorZombRaid"), 0, settingsFilename);

static int configMinForceBBusters = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceBBusters"), 0, settingsFilename);
static int configMaxForceBBusters = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceBBusters"), 100, settingsFilename);
static int configMinForceBBustersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceBBustersDevice2"), 0, settingsFilename);
static int configMaxForceBBustersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceBBustersDevice2"), 100, settingsFilename);
static int configMinForceBBustersDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceBBustersDevice3"), 0, settingsFilename);
static int configMaxForceBBustersDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceBBustersDevice3"), 100, settingsFilename);
static int RumbleStrengthLeftMotorBBusters = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorBBusters"), 0, settingsFilename);
static int RumbleStrengthRightMotorBBusters = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorBBusters"), 0, settingsFilename);

static int configMinForceMechatt = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceMechatt"), 0, settingsFilename);
static int configMaxForceMechatt = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceMechatt"), 100, settingsFilename);
static int configMinForceMechattDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceMechattDevice2"), 0, settingsFilename);
static int configMaxForceMechattDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceMechattDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorMechatt = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorMechatt"), 0, settingsFilename);
static int RumbleStrengthRightMotorMechatt = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorMechatt"), 0, settingsFilename);

static int configMinForceTShoot = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTShoot"), 0, settingsFilename);
static int configMaxForceTShoot = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTShoot"), 100, settingsFilename);
static int configMinForceTShootDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTShootDevice2"), 0, settingsFilename);
static int configMaxForceTShootDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTShootDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorTShoot = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorTShoot"), 0, settingsFilename);
static int RumbleStrengthRightMotorTShoot = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorTShoot"), 0, settingsFilename);

static int configMinForceGunBuster = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceGunBuster"), 0, settingsFilename);
static int configMaxForceGunBuster = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceGunBuster"), 100, settingsFilename);
static int configMinForceGunBusterDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceGunBusterDevice2"), 0, settingsFilename);
static int configMaxForceGunBusterDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceGunBusterDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorGunBuster = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorGunBuster"), 0, settingsFilename);
static int RumbleStrengthRightMotorGunBuster = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorGunBuster"), 0, settingsFilename);

static int configMinForceAlien3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceAlien3"), 0, settingsFilename);
static int configMaxForceAlien3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceAlien3"), 100, settingsFilename);
static int configMinForceAlien3Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceAlien3Device2"), 0, settingsFilename);
static int configMaxForceAlien3Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceAlien3Device2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorAlien3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorAlien3"), 0, settingsFilename);
static int RumbleStrengthRightMotorAlien3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorAlien3"), 0, settingsFilename);

static int configMinForcePointBlank2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForcePointBlank2"), 0, settingsFilename);
static int configMaxForcePointBlank2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForcePointBlank2"), 100, settingsFilename);
static int configMinForcePointBlank2Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForcePointBlank2Device2"), 0, settingsFilename);
static int configMaxForcePointBlank2Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForcePointBlank2Device2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorPointBlank2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorPointBlank2"), 0, settingsFilename);
static int RumbleStrengthRightMotorPointBlank2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorPointBlank2"), 0, settingsFilename);

static int configMinForceGhoulPanic = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceGhoulPanic"), 0, settingsFilename);
static int configMaxForceGhoulPanic = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceGhoulPanic"), 100, settingsFilename);
static int configMinForceGhoulPanicDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceGhoulPanicDevice2"), 0, settingsFilename);
static int configMaxForceGhoulPanicDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceGhoulPanicDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorGhoulPanic = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorGhoulPanic"), 0, settingsFilename);
static int RumbleStrengthRightMotorGhoulPanic = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorGhoulPanic"), 0, settingsFilename);

static int configMinForceSpacegun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSpacegun"), 0, settingsFilename);
static int configMaxForceSpacegun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSpacegun"), 100, settingsFilename);
static int configMinForceSpacegunDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSpacegunDevice2"), 0, settingsFilename);
static int configMaxForceSpacegunDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSpacegunDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorSpacegun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorSpacegun"), 0, settingsFilename);
static int RumbleStrengthRightMotorSpacegun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorSpacegun"), 0, settingsFilename);

static int configMinForceTerm2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTerm2"), 0, settingsFilename);
static int configMaxForceTerm2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTerm2"), 100, settingsFilename);
static int configMinForceTerm2Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTerm2Device2"), 0, settingsFilename);
static int configMaxForceTerm2Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTerm2Device2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorTerm2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorTerm2"), 0, settingsFilename);
static int RumbleStrengthRightMotorTerm2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorTerm2"), 0, settingsFilename);

static int configMinForceRchase = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRchase"), 0, settingsFilename);
static int configMaxForceRchase = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRchase"), 100, settingsFilename);
static int configMinForceRchaseDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRchaseDevice2"), 0, settingsFilename);
static int configMaxForceRchaseDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRchaseDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorRchase = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorRchase"), 0, settingsFilename);
static int RumbleStrengthRightMotorRchase = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorRchase"), 0, settingsFilename);

static int configMinForceLGhost = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceLGhost"), 0, settingsFilename);
static int configMaxForceLGhost = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceLGhost"), 100, settingsFilename);
static int configMinForceLGhostDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceLGhostDevice2"), 0, settingsFilename);
static int configMaxForceLGhostDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceLGhostDevice2"), 100, settingsFilename);
static int configMinForceLGhostDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceLGhostDevice3"), 0, settingsFilename);
static int configMaxForceLGhostDevice3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceLGhostDevice3"), 100, settingsFilename);
static int RumbleStrengthLeftMotorLGhost = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorLGhost"), 0, settingsFilename);
static int RumbleStrengthRightMotorLGhost = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorLGhost"), 0, settingsFilename);

static int configMinForceTimeCris = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTimeCris"), 0, settingsFilename);
static int configMaxForceTimeCris = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTimeCris"), 100, settingsFilename);
static int RumbleStrengthLeftMotorTimeCris = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorTimeCris"), 0, settingsFilename);
static int RumbleStrengthRightMotorTimeCris = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorTimeCris"), 0, settingsFilename);

static int configMinForceOThunder = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOThunder"), 0, settingsFilename);
static int configMaxForceOThunder = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOThunder"), 100, settingsFilename);
static int configMinForceOThunderDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOThunderDevice2"), 0, settingsFilename);
static int configMaxForceOThunderDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOThunderDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorOThunder = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorOThunder"), 0, settingsFilename);
static int RumbleStrengthRightMotorOThunder = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorOThunder"), 0, settingsFilename);

static int configMinForceOpWolf = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOpWolf"), 0, settingsFilename);
static int configMaxForceOpWolf = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOpWolf"), 100, settingsFilename);
static int configMinForceOpWolfDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOpWolfDevice2"), 0, settingsFilename);
static int configMaxForceOpWolfDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOpWolfDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorOpWolf = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorOpWolf"), 0, settingsFilename);
static int RumbleStrengthRightMotorOpWolf = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorOpWolf"), 0, settingsFilename);

static int configMinForceUFire = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceUFire"), 0, settingsFilename);
static int configMaxForceUFire = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceUFire"), 100, settingsFilename);
static int configMinForceUFireDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceUFireDevice2"), 0, settingsFilename);
static int configMaxForceUFireDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceUFireDevice2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorUFire = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorUFire"), 0, settingsFilename);
static int RumbleStrengthRightMotorUFire = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorUFire"), 0, settingsFilename);

static int configMinForceORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceORunners"), 0, settingsFilename);
static int configMaxForceORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceORunners"), 100, settingsFilename);
static int configAlternativeMinForceLeftORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftORunners"), 0, settingsFilename);
static int configAlternativeMaxForceLeftORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftORunners"), 100, settingsFilename);
static int configAlternativeMinForceRightORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightORunners"), 0, settingsFilename);
static int configAlternativeMaxForceRightORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightORunners"), 100, settingsFilename);
static int configMinForceORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceORunnersDevice2"), 0, settingsFilename);
static int configMaxForceORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceORunnersDevice2"), 100, settingsFilename);
static int configAlternativeMinForceLeftORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftORunnersDevice2"), 0, settingsFilename);
static int configAlternativeMaxForceLeftORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftORunnersDevice2"), 100, settingsFilename);
static int configAlternativeMinForceRightORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightORunnersDevice2"), 0, settingsFilename);
static int configAlternativeMaxForceRightORunnersDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightORunnersDevice2"), 100, settingsFilename);
static int configFeedbackLengthORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthORunners"), 120, settingsFilename);
static int EnableForceSpringEffectORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectORunners"), 0, settingsFilename);
static int ForceSpringStrengthORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthORunners"), 0, settingsFilename);
static int SinePeriodORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodORunners"), 0, settingsFilename);
static int SineFadePeriodORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodORunners"), 0, settingsFilename);
static int SineStrengthORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthORunners"), 0, settingsFilename);

static int configMinForceTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceTOutrun"), 0, settingsFilename);
static int configMaxForceTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceTOutrun"), 100, settingsFilename);
static int configAlternativeMinForceLeftTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftTOutrun"), 0, settingsFilename);
static int configAlternativeMaxForceLeftTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftTOutrun"), 100, settingsFilename);
static int configAlternativeMinForceRightTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightTOutrun"), 0, settingsFilename);
static int configAlternativeMaxForceRightTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightTOutrun"), 100, settingsFilename);
static int configFeedbackLengthTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthTOutrun"), 120, settingsFilename);
static int EnableForceSpringEffectTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectTOutrun"), 0, settingsFilename);
static int ForceSpringStrengthTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthTOutrun"), 0, settingsFilename);
static int SinePeriodTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodTOutrun"), 0, settingsFilename);
static int SineFadePeriodTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodTOutrun"), 0, settingsFilename);
static int SineStrengthTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthTOutrun"), 0, settingsFilename);

static int configMinForceCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceCBombers"), 0, settingsFilename);
static int configMaxForceCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceCBombers"), 100, settingsFilename);
static int configAlternativeMinForceLeftCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftCBombers"), 0, settingsFilename);
static int configAlternativeMaxForceLeftCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftCBombers"), 100, settingsFilename);
static int configAlternativeMinForceRightCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightCBombers"), 0, settingsFilename);
static int configAlternativeMaxForceRightCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightCBombers"), 100, settingsFilename);
static int configFeedbackLengthCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthCBombers"), 120, settingsFilename);
static int EnableForceSpringEffectCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectCBombers"), 0, settingsFilename);
static int ForceSpringStrengthCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthCBombers"), 0, settingsFilename);
static int SinePeriodCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodCBombers"), 0, settingsFilename);
static int SineFadePeriodCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodCBombers"), 0, settingsFilename);
static int SineStrengthCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthCBombers"), 0, settingsFilename);

static int configMinForceOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOutrun"), 0, settingsFilename);
static int configMaxForceOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOutrun"), 100, settingsFilename);
static int configAlternativeMinForceLeftOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftOutrun"), 0, settingsFilename);
static int configAlternativeMaxForceLeftOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftOutrun"), 100, settingsFilename);
static int configAlternativeMinForceRightOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightOutrun"), 0, settingsFilename);
static int configAlternativeMaxForceRightOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightOutrun"), 100, settingsFilename);
static int configFeedbackLengthOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthOutrun"), 120, settingsFilename);
static int EnableForceSpringEffectOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectOutrun"), 0, settingsFilename);
static int ForceSpringStrengthOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthOutrun"), 0, settingsFilename);
static int SinePeriodOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodOutrun"), 0, settingsFilename);
static int SineFadePeriodOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodOutrun"), 0, settingsFilename);
static int SineStrengthOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthOutrun"), 0, settingsFilename);

static int configMinForcePDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForcePDrift"), 0, settingsFilename);
static int configMaxForcePDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForcePDrift"), 100, settingsFilename);
static int configAlternativeMinForceLeftPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftPDrift"), 0, settingsFilename);
static int configAlternativeMaxForceLeftPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftPDrift"), 100, settingsFilename);
static int configAlternativeMinForceRightPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightPDrift"), 0, settingsFilename);
static int configAlternativeMaxForceRightPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightPDrift"), 100, settingsFilename);
static int configFeedbackLengthPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthPDrift"), 120, settingsFilename);
static int EnableForceSpringEffectPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectPDrift"), 0, settingsFilename);
static int ForceSpringStrengthPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthPDrift"), 0, settingsFilename);
static int SinePeriodPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodPDrift"), 0, settingsFilename);
static int SineFadePeriodPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodPDrift"), 0, settingsFilename);
static int SineStrengthPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthPDrift"), 0, settingsFilename);

static int configMinForceAfterBurner2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceAfterBurner2"), 0, settingsFilename);
static int configMaxForceAfterBurner2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceAfterBurner2"), 100, settingsFilename);
static int RumbleStrengthLeftMotorAfterBurner2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorAfterBurner2"), 0, settingsFilename);
static int RumbleStrengthRightMotorAfterBurner2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorAfterBurner2"), 0, settingsFilename);

static int configMinForceCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceCisHeat"), 0, settingsFilename);
static int configMaxForceCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceCisHeat"), 100, settingsFilename);
static int configAlternativeMinForceLeftCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftCisHeat"), 0, settingsFilename);
static int configAlternativeMaxForceLeftCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftCisHeat"), 100, settingsFilename);
static int configAlternativeMinForceRightCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightCisHeat"), 0, settingsFilename);
static int configAlternativeMaxForceRightCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightCisHeat"), 100, settingsFilename);
static int configFeedbackLengthCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthCisHeat"), 120, settingsFilename);
static int EnableForceSpringEffectCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectCisHeat"), 0, settingsFilename);
static int ForceSpringStrengthCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthCisHeat"), 0, settingsFilename);
static int SinePeriodCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodCisHeat"), 0, settingsFilename);
static int SineFadePeriodCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodCisHeat"), 0, settingsFilename);
static int SineStrengthCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthCisHeat"), 0, settingsFilename);

static int configMinForceF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceF1GpStar"), 0, settingsFilename);
static int configMaxForceF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceF1GpStar"), 100, settingsFilename);
static int configAlternativeMinForceLeftF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftF1GpStar"), 0, settingsFilename);
static int configAlternativeMaxForceLeftF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftF1GpStar"), 100, settingsFilename);
static int configAlternativeMinForceRightF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightF1GpStar"), 0, settingsFilename);
static int configAlternativeMaxForceRightF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightF1GpStar"), 100, settingsFilename);
static int configFeedbackLengthF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthF1GpStar"), 120, settingsFilename);
static int EnableForceSpringEffectF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectF1GpStar"), 0, settingsFilename);
static int ForceSpringStrengthF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthF1GpStar"), 0, settingsFilename);
static int SinePeriodF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodF1GpStar"), 0, settingsFilename);
static int SineFadePeriodF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodF1GpStar"), 0, settingsFilename);
static int SineStrengthF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthF1GpStar"), 0, settingsFilename);

static int configMinForceF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceF1GpStar2"), 0, settingsFilename);
static int configMaxForceF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceF1GpStar2"), 100, settingsFilename);
static int configAlternativeMinForceLeftF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftF1GpStar2"), 0, settingsFilename);
static int configAlternativeMaxForceLeftF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftF1GpStar2"), 100, settingsFilename);
static int configAlternativeMinForceRightF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightF1GpStar2"), 0, settingsFilename);
static int configAlternativeMaxForceRightF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightF1GpStar2"), 100, settingsFilename);
static int configFeedbackLengthF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthF1GpStar2"), 120, settingsFilename);
static int EnableForceSpringEffectF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectF1GpStar2"), 0, settingsFilename);
static int ForceSpringStrengthF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthF1GpStar2"), 0, settingsFilename);
static int SinePeriodF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodF1GpStar2"), 0, settingsFilename);
static int SineFadePeriodF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodF1GpStar2"), 0, settingsFilename);
static int SineStrengthF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthF1GpStar2"), 0, settingsFilename);

static bool init = false;
static bool initSpring = false;
static bool EmuName = false;
static bool RomGameName = false;
static bool Effect1 = false;
static bool Effect2 = false;
static bool Effect3 = false;
static bool DirtDevilSine = false;
static bool ForceSpringEffect = false;
static bool DontSineUntilRaceStart = false;
static bool HardDrivinFrame = false;
static bool Motion = false;
static bool MotionFalse = false;

HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;

const char* nameFFB;
const char* romFFB;
const char* EmulatorName;
char* name;
char* romname;
char* RunningFFB;
char* Emulator;
int vals[8] = { 0 };
int frame = 0;
int HardDrivinFFB;
int StopConstant;
int newstateFFB;
int stateFFB;
int stateFFB2;
int stateFFB3;
int stateFFBDevice2;
int stateFFBDevice3;

std::string wheelA("wheel");

typedef int(__stdcall* MAME_START)(int hWnd);
typedef int(__stdcall* MAME_STOP)(void);
typedef int(__stdcall* MAME_COPYDATA)(int id, const char* name);
typedef int(__stdcall* MAME_UPDATESTATE)(const char* id, int state);
typedef int(__stdcall* MAME_OUTPUT)(const char* name, int value);
typedef int(__stdcall* INIT_MAME)(int clientid, PWCHAR name, MAME_START start, MAME_STOP stop, MAME_COPYDATA copydata, MAME_UPDATESTATE updatestate, MAME_OUTPUT output);

MAME_START mame_start_ptr;
MAME_STOP mame_stop_ptr;
MAME_COPYDATA mame_copydata_ptr;
MAME_UPDATESTATE mame_updatestate_ptr;
MAME_OUTPUT mame_output_ptr;
INIT_MAME dll_init;

int __stdcall mame_start(int hWnd);
int __stdcall mame_stop(void);
int __stdcall mame_copydata(int id, const char* name);
int __stdcall mame_updatestate(const char* id, int state);
int __stdcall mame_output(const char* name, int value);

void CallTheOutputs()
{
#ifdef _WIN64  
	ProcDLL = LoadLibrary(TEXT("MAME64.dll"));
#else  
	ProcDLL = LoadLibrary(TEXT("MAME32.dll"));
#endif
	if (ProcDLL != NULL)
	{
		dll_init = (INIT_MAME)GetProcAddress(ProcDLL, "init_mame");
	}
	else
	{
#ifdef _WIN64
		MessageBoxA(NULL, "MAME64.dll is missing!", "FFBPluginError", NULL);
#else
		MessageBoxA(NULL, "MAME32.dll is missing!", "FFBPluginError", NULL);
#endif
	}
}

typedef struct _id_map_entry id_map_entry;
struct _id_map_entry
{
	id_map_entry* next;
	const char* name;
	WPARAM					id;
};

void AppendTextToEditCtrl(HWND hWnd, LPCTSTR lpString);
void reset_id_to_outname_cache(void);
const char* get_name_from_id(int id);
void add_map_entry(id_map_entry* entry, int id, char* name);

id_map_entry* idmaplist;

HWND hEdit;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void AppendTextToEditCtrl(HWND hWnd, LPCTSTR pszText);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CallTheOutputs();
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MAMEInterop";
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(L"MAMEInterop", L"MAMEInterop", WS_OVERLAPPEDWINDOW,
		0, 0, 512, 512, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		MessageBox(hWnd, L"Could not create window", L"Error", MB_OK | MB_ICONERROR);

	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		8, 8, 488, 464, hWnd, NULL, GetModuleHandle(NULL), NULL);

	if (hEdit == NULL)
		MessageBox(hWnd, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);

	if (hWnd != NULL)
	{
		//ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}
	
	mame_start_ptr = mame_start;
	mame_stop_ptr = mame_stop;
	mame_copydata_ptr = mame_copydata;
	mame_updatestate_ptr = mame_updatestate;
	mame_output_ptr = mame_output;

	dll_init(1, L"Test", mame_start_ptr, mame_stop_ptr, mame_copydata_ptr, mame_updatestate_ptr, mame_output_ptr);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		reset_id_to_outname_cache();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void AppendTextToEditCtrl(HWND hWnd, LPCTSTR lpString)
{
	int iPrevLen = GetWindowTextLength(hWnd);
	SendMessage(hWnd, EM_SETSEL, iPrevLen, iPrevLen);
	SendMessage(hWnd, EM_REPLACESEL, 0, (LPARAM)lpString);
}

void reset_id_to_outname_cache(void)
{
	while (idmaplist != NULL)
	{
		id_map_entry* temp = idmaplist;
		idmaplist = temp->next;
		free(temp);
	}
}

const char* get_name_from_id(int id)
{
	while (idmaplist != NULL)
	{
		id_map_entry* temp = idmaplist;

		if (temp->id == (WPARAM)id)
			return temp->name;

		idmaplist = temp->next;
	}

	return NULL;
}

void add_map_entry(id_map_entry* entry, int id, char* name)
{
	char* string;

	entry = (id_map_entry*)malloc(sizeof(entry));
	string = (char*)malloc(strlen(name) + 1);

	if (entry != NULL && string != NULL)
	{
		entry->next = idmaplist;
		entry->name = string;
		entry->id = id;

		strcpy(string, name);
		idmaplist = entry;
	}
}


int __stdcall mame_start(int hWnd)
{
	WCHAR buf[256];

	wsprintf(buf, L"mame_start hwnd = 0x%08x\r\n", hWnd);

	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

int __stdcall mame_stop(void)
{
	reset_id_to_outname_cache();

	AppendTextToEditCtrl(hEdit, TEXT("mame_stop\r\n"));

	StopConstant = 255;

	return 1;
}

int __stdcall mame_copydata(int id, const char* name)
{
	WCHAR buf[256];

	wsprintf(buf, L"id %d = '%S'\r\n", id, name);

	if (id == 0)
	{
		romFFB = name;
	}

	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

int __stdcall mame_updatestate(const char* id, int state)
{
	WCHAR buf[256];

	LPCSTR name = get_name_from_id((int)id);

	if (name == NULL)
		name = id;

	wsprintf(buf, L"updatestate: id=%d (%S) state=%d\r\n", id, name, state);
	AppendTextToEditCtrl(hEdit, buf);

	nameFFB = name;
	newstateFFB = state;

	if (HardDrivinFrame)
	{
		if (name == wheelA)
		{
			//if (!(((state == 0xE0) || (state == 0)) && ((frame == 0) || (frame == 4))))
			if ((state != 0xE0) && (state != 0x00))
			{
				vals[frame & 0x7] = state;
				frame++;
			}
		}
	}
	
	return 1;
}

int __stdcall mame_output(const char* name, int value)
{
	WCHAR buf[256];

	wsprintf(buf, L"output: name=%S value=%d\r\n", name, value);
	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

static BOOL CALLBACK FindWindowBySubstr(HWND hwnd, LPARAM substring)
{
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];

	if (GetWindowText(hwnd, windowTitle, TITLE_SIZE))
	{
		if (_tcsstr(windowTitle, LPCTSTR(substring)) != NULL)
		{
			return false;
		}
	}
	return true;
}

DWORD WINAPI ThreadForOutputs(LPVOID lpParam)
{
	WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}

DWORD WINAPI ThreadForForcedSpring(LPVOID lpParam)
{
	if (configGameId == 34)
	{
		Sleep(2500);
		ForceSpringEffect = true;
	}
	else
	{
		ForceSpringEffect = true;
	}	

	return 0;
}

//Supermodel Emulator Games
std::string dayto2pe("dayto2pe");
std::string daytona2("daytona2");
std::string dirtdvlsa("dirtdvlsa");
std::string dirtdvls("dirtdvls");
std::string dirtdvlsj("dirtdvlsj");
std::string dirtdvlsg("dirtdvlsg");
std::string ecau("ecau");
std::string eca("eca");
std::string ecap("ecap");
std::string ecaj("ecaj");
std::string lemans24("lemans24");
std::string scud("scud");
std::string scuda("scuda");
std::string scudj("scudj");
std::string scudplus("scudplus");
std::string scudplusa("scudplusa");
std::string srally2("srally2");
std::string srally2x("srally2x");
std::string srally2p("srally2p");
std::string srally2pa("srally2pa");

//MAME Games
std::string aburner2("aburner2");
std::string aburner2g("aburner2g");
std::string vformula("vformula");
std::string vr("vr");
std::string sfrush("sfrush");
std::string sfrushrk("sfrushrk");
std::string sfrushrkwo("sfrushrkwo");
std::string sfrusha("sfrusha");
std::string crusnwld("crusnwld");
std::string crusnwld24("crusnwld24");
std::string crusnwld23("crusnwld23");
std::string crusnwld20("crusnwld20");
std::string crusnwld19("crusnwld19");
std::string crusnwld17("crusnwld17");
std::string crusnwld13("crusnwld13");
std::string offroadc("offroadc");
std::string offroadc4("offroadc4");
std::string offroadc3("offroadc3");
std::string offroadc1("offroadc1");
std::string crusnusa("crusnusa");
std::string crusnusa40("crusnusa40");
std::string crusnusa21("crusnusa21");
std::string calspeed("calspeed");
std::string calspeeda("calspeeda");
std::string calspeedb("calspeedb");
std::string outrunra("outrunra");
std::string outrun("outrun");
std::string outruneh("outruneh");
std::string toutrun("toutrun");
std::string toutrund("toutrund");
std::string toutrunj("toutrunj");
std::string toutrunjd("toutrunjd");
std::string pdrift("pdrift");
std::string pdrifta("pdrifta");
std::string pdrifte("pdrifte");
std::string pdriftj("pdriftj");
std::string pdriftl("pdriftl");
std::string orunners("orunners");
std::string orunnersu("orunnersu");
std::string orunnersj("orunnersj");
std::string sf2049("sf2049");
std::string sf2049se("sf2049se");
std::string sf2049te("sf2049te");
std::string harddriv("harddriv");
std::string harddriv1("harddriv1");
std::string harddrivb6("harddrivb6");
std::string harddrivb("harddrivb");
std::string harddrivg4("harddrivg4");
std::string harddrivg("harddrivg");
std::string harddrivj6("harddrivj6");
std::string harddrivj("harddrivj");
std::string harddriv2("harddriv2");
std::string harddriv3("harddriv3");
std::string harddrivcb("harddrivcb");
std::string harddrivcg("harddrivcg");
std::string harddrivc1("harddrivc1");
std::string harddrivc("harddrivc");
std::string hdrivairp("hdrivairp");
std::string hdrivair("hdrivair");
std::string racedrivb1("racedrivb1");
std::string racedrivb4("racedrivb4");
std::string racedrivb("racedrivb");
std::string racedrivg1("racedrivg1");
std::string racedrivg4("racedrivg4");
std::string racedrivg("racedrivg");
std::string racedriv1("racedriv1");
std::string racedriv2("racedriv2");
std::string racedriv3("racedriv3");
std::string racedriv4("racedriv4");
std::string racedriv("racedriv");
std::string racedrivcb4("racedrivcb4");
std::string racedrivcb("racedrivcb");
std::string racedrivcg4("racedrivcg4");
std::string racedrivcg("racedrivcg");
std::string racedrivc2("racedrivc2");
std::string racedrivc4("racedrivc4");
std::string racedrivc("racedrivc");
std::string racedrivpan("racedrivpan");
std::string othunder("othunder");
std::string othundero("othundero");
std::string othunderuo("othunderuo");
std::string othunderu("othunderu");
std::string othunderj("othunderj");
std::string opwolf("opwolf");
std::string opwolfp("opwolfp");
std::string opwolfj("opwolfj");
std::string opwolfu("opwolfu");
std::string opwolfa("opwolfa");
std::string revx("revx");
std::string revxp5("revxp5");
std::string term2("term2");
std::string term2la1("term2la1");
std::string term2pa2("term2pa2");
std::string term2la2("term2la2");
std::string term2la3("term2la3");
std::string term2lg1("term2lg1");
std::string zombraid("zombraid");
std::string zombraidpj("zombraidpj");
std::string zombraidp("zombraidp");
std::string bbusters("bbusters");
std::string bbustersu("bbustersu");
std::string bbustersua("bbustersua");
std::string bbustersj("bbustersj");
std::string mechatt("mechatt");
std::string mechattu("mechattu");
std::string mechattu1("mechattu1");
std::string mechattj("mechattj");
std::string tshoot("tshoot");
std::string gunbustru("gunbustru");
std::string gunbustr("gunbustr");
std::string gunbustrj("gunbustrj");
std::string alien3("alien3");
std::string alien3u("alien3u");
std::string ptblank2("ptblank2");
std::string ptblank2ua("ptblank2ua");
std::string ghlpanic("ghlpanic");
std::string spacegun("spacegun");
std::string spacegunu("spacegunu");
std::string spacegunj("spacegunj");
std::string rchase("rchase");
std::string rchasej("rchasej");
std::string lghost("lghost");
std::string lghostd("lghostd");
std::string lghostu("lghostu");
std::string lghostud("lghostud");
std::string lghostj("lghostj");
std::string timecris("timecris");
std::string timecrisa("timecrisa");
std::string cischeat("cischeat");
std::string f1gpstar("f1gpstar");
std::string f1gpstaro("f1gpstaro");
std::string f1gpstr2("f1gpstr2");
std::string undrfire("undrfire");
std::string undrfireu("undrfireu");
std::string undrfirej("undrfirej");
std::string cbombers("cbombers");
std::string cbombersj("cbombersj");
std::string cbombersp("cbombersp");

//Our string to load game from
std::string Daytona2Active("Daytona2Active");
std::string DirtDevilsActive("DirtDevilsActive");
std::string Srally2Active("Srally2Active");
std::string VirtuaRacingActive("VirtuaRacingActive");
std::string SanFranActive("SanFranActive");
std::string SanFranRockActive("SanFranRockActive");
std::string CrusnWldActive("CrusnWldActive");
std::string OffroadChallengeActive("OffroadChallengeActive");
std::string CrusnUSAActive("CrusnUSAActive");
std::string CalSpeedActive("CalSpeedActive");
std::string SanFran2049Active("SanFran2049Active");
std::string HardDrivinActive("HardDrivinActive"); 
std::string LightGunActive("LightGunActive");
std::string RacingActive1("RacingActive1");
std::string RacingActive2("RacingActive2");
std::string AfterburnerActive("AfterburnerActive");
std::string OutrunActive("OutrunActive");
std::string PDriftActive("PDriftActive");

//Names of FFB Outputs
std::string RawDrive("RawDrive");
std::string digit0("digit0");
std::string wheel("wheel");
std::string lamp1("lamp1");
std::string led2("led2");
std::string Vibration_motor("Vibration_motor");
std::string vibration_motor("vibration_motor");
std::string Wheel_vibration("Wheel_vibration");
std::string upright_wheel_motor("upright_wheel_motor");
std::string MA_Steering_Wheel_motor("MA_Steering_Wheel_motor");
std::string MB_Steering_Wheel_motor("MB_Steering_Wheel_motor");
std::string Left_Gun_Recoil("Left_Gun_Recoil");
std::string Right_Gun_Recoil("Right_Gun_Recoil");
std::string Player1_Recoil_Piston("Player1_Recoil_Piston");
std::string Player2_Recoil_Piston("Player2_Recoil_Piston");
std::string Player1_Gun_Recoil("Player1_Gun_Recoil");
std::string Player2_Gun_Recoil("Player2_Gun_Recoil");
std::string Player3_Gun_Recoil("Player3_Gun_Recoil");
std::string P1_Gun_Recoil("P1_Gun_Recoil");
std::string P2_Gun_Recoil("P2_Gun_Recoil");
std::string P3_Gun_Recoil("P3_Gun_Recoil");
std::string P1_gun_recoil("P1_gun_recoil");
std::string P2_gun_recoil("P2_gun_recoil");
std::string mcuout1("mcuout1");
std::string Bank_Motor_Speed("Bank_Motor_Speed");
std::string Bank_Motor_Direction("Bank_Motor_Direction");
std::string bank_motor_position("bank_motor_position");

//Emulator Name
std::string MAME("MAME");
std::string Supermodel("Supermodel");

void OutputReading::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		CreateThread(NULL, 0, ThreadForOutputs, NULL, 0, NULL);

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
			extern int joystick1Index;
			if (i == joystick1Index)
			{
				continue;
			}
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
			if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
			{
				GameController2 = SDL_JoystickOpen(i);
				ControllerHaptic2 = SDL_HapticOpenFromJoystick(GameController2);
				break;
			}
			SDL_JoystickClose(js2);
		}
		haptic2 = ControllerHaptic2;
		if ((SDL_HapticRumbleSupported(haptic2) == SDL_TRUE))
		{
			SDL_HapticRumbleInit;
			SDL_HapticRumbleInit(ControllerHaptic2);
		}
		SDL_HapticSetGain(haptic2, 100);

		wchar_t* deviceGUIDString3 = new wchar_t[256];
		int Device3GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device3GUID"), NULL, deviceGUIDString3, 256, settingsFilename);
		char joystick_guid2[256];
		sprintf(joystick_guid2, "%S", deviceGUIDString3);
		SDL_JoystickGUID guid2, dev_guid2;
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			extern int joystick1Index;
			if (i == joystick1Index)
			{
				continue;
			}
			SDL_Joystick* js3 = SDL_JoystickOpen(i);
			joystick_index3 = SDL_JoystickInstanceID(js3);
			SDL_JoystickGUID guid2 = SDL_JoystickGetGUID(js3);
			char guid_str2[1024];
			SDL_JoystickGetGUIDString(guid2, guid_str2, sizeof(guid_str2));
			const char* name2 = SDL_JoystickName(js3);
			char text2[256];
			sprintf(text2, "Joystick: %d / Name: %s / GUID: %s\n", i, name2, guid_str2);
			guid2 = SDL_JoystickGetGUIDFromString(joystick_guid2);
			dev_guid2 = SDL_JoystickGetGUID(js3);
			if (!memcmp(&guid2, &dev_guid2, sizeof(SDL_JoystickGUID)))
			{
				GameController3 = SDL_JoystickOpen(i);
				ControllerHaptic3 = SDL_HapticOpenFromJoystick(GameController3);
				break;
			}
			SDL_JoystickClose(js3);
		}
		haptic3 = ControllerHaptic3;
		if ((SDL_HapticRumbleSupported(haptic3) == SDL_TRUE))
		{
			SDL_HapticRumbleInit;
			SDL_HapticRumbleInit(ControllerHaptic3);
		}
		SDL_HapticSetGain(haptic3, 100);
		init = true;
	}

	if (EnableForceSpringEffect == 1)
	{
		if (!initSpring)
		{
			CreateThread(NULL, 0, ThreadForForcedSpring, NULL, 0, NULL);
			initSpring = true;
		}	
	}

	if (EnableForceSpringEffect == 1)
	{
		if (ForceSpringEffect)
		{
			triggers->Springi(ForceSpringStrength / 100.0);
		}
	}

	romname = new char[256]; //name of rom being played
	sprintf(romname, "%s", romFFB);

	name = new char[256]; //name of FFB currently
	sprintf(name, "%s", nameFFB);

	if (!RomGameName)
	{
		if (romname != NULL)
		{
			//Select code to run via rom name
			if (romname == dayto2pe || romname == daytona2)
			{				
				configMinForce = configMinForceDaytona2;
				configMaxForce = configMaxForceDaytona2;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftDaytona2;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDaytona2;
				configAlternativeMinForceRight = configAlternativeMinForceRightDaytona2;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightDaytona2;
				configFeedbackLength = configFeedbackLengthDaytona2;
				PowerMode = PowerModeDaytona2;					
				EnableForceSpringEffect = EnableForceSpringEffectDaytona2;
				ForceSpringStrength = ForceSpringStrengthDaytona2;

				RunningFFB = "Daytona2Active";
			}

			if (romname == scud || romname == scuda || romname == scudj || romname == scudplus || romname == scudplusa)
			{
				configMinForce = configMinForceScud;
				configMaxForce = configMaxForceScud;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftScud;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftScud;
				configAlternativeMinForceRight = configAlternativeMinForceRightScud;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightScud;
				configFeedbackLength = configFeedbackLengthScud;
				PowerMode = PowerModeScud;
				EnableForceSpringEffect = EnableForceSpringEffectScud;
				ForceSpringStrength = ForceSpringStrengthScud;

				RunningFFB = "Daytona2Active";
			}

			if (romname == lemans24)
			{
				configMinForce = configMinForceLeMans;
				configMaxForce = configMaxForceLeMans;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftLeMans;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftLeMans;
				configAlternativeMinForceRight = configAlternativeMinForceRightLeMans;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightLeMans;
				configFeedbackLength = configFeedbackLengthLeMans;
				PowerMode = PowerModeLeMans;
				EnableForceSpringEffect = EnableForceSpringEffectLeMans;
				ForceSpringStrength = ForceSpringStrengthLeMans;

				RunningFFB = "Daytona2Active";
			}

			if (romname == dirtdvlsa || romname == dirtdvls || romname == dirtdvlsj || romname == dirtdvlsg)
			{
				configMinForce = configMinForceDirtDevils;
				configMaxForce = configMaxForceDirtDevils;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftDirtDevils;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDirtDevils;
				configAlternativeMinForceRight = configAlternativeMinForceRightDirtDevils;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightDirtDevils;
				configFeedbackLength = configFeedbackLengthDirtDevils;
				PowerMode = PowerModeDirtDevils;
				EnableForceSpringEffect = EnableForceSpringEffectDirtDevils;
				ForceSpringStrength = ForceSpringStrengthDirtDevils;

				RunningFFB = "DirtDevilsActive";
			}

			if (romname == srally2 || romname == srally2x || romname == srally2p || romname == srally2pa)
			{
				configMinForce = configMinForceSRally2;
				configMaxForce = configMaxForceSRally2;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSRally2;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSRally2;
				configAlternativeMinForceRight = configAlternativeMinForceRightSRally2;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSRally2;
				configFeedbackLength = configFeedbackLengthSRally2;
				PowerMode = PowerModeSRally2;
				EnableForceSpringEffect = EnableForceSpringEffectSRally2;
				ForceSpringStrength = ForceSpringStrengthSRally2;

				RunningFFB = "Srally2Active";
			}

			if (romname == ecau || romname == eca || romname == ecap || romname == ecaj)
			{
				configMinForce = configMinForceECA;
				configMaxForce = configMaxForceECA;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftECA;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftECA;
				configAlternativeMinForceRight = configAlternativeMinForceRightECA;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightECA;
				configFeedbackLength = configFeedbackLengthECA;
				PowerMode = PowerModeECA;
				EnableForceSpringEffect = EnableForceSpringEffectECA;
				ForceSpringStrength = ForceSpringStrengthECA;

				RunningFFB = "Srally2Active";
			}

			if (romname == vr)
			{
				configMinForce = configMinForceVirtuaRacing;
				configMaxForce = configMaxForceVirtuaRacing;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftVirtuaRacing;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftVirtuaRacing;
				configAlternativeMinForceRight = configAlternativeMinForceRightVirtuaRacing;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightVirtuaRacing;
				configFeedbackLength = configFeedbackLengthVirtuaRacing;
				EnableForceSpringEffect = EnableForceSpringEffectVirtuaRacing;
				ForceSpringStrength = ForceSpringStrengthVirtuaRacing;

				RunningFFB = "VirtuaRacingActive";
			}

			if (romname == sfrush || romname == sfrusha)
			{
				configMinForce = configMinForceSFRush;
				configMaxForce = configMaxForceSFRush;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSFRush;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSFRush;
				configAlternativeMinForceRight = configAlternativeMinForceRightSFRush;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSFRush;
				configFeedbackLength = configFeedbackLengthSFRush;
				PowerMode = PowerModeSFRush;
				EnableForceSpringEffect = EnableForceSpringEffectSFRush;
				ForceSpringStrength = ForceSpringStrengthSFRush;

				RunningFFB = "SanFranActive";
			}

			if (romname == sfrushrk || romname == sfrushrkwo)
			{
				configMinForce = configMinForceSFRushRock;
				configMaxForce = configMaxForceSFRushRock;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSFRushRock;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSFRushRock;
				configAlternativeMinForceRight = configAlternativeMinForceRightSFRushRock;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSFRushRock;
				configFeedbackLength = configFeedbackLengthSFRushRock;
				PowerMode = PowerModeSFRushRock;
				EnableForceSpringEffect = EnableForceSpringEffectSFRushRock;
				ForceSpringStrength = ForceSpringStrengthSFRushRock;

				RunningFFB = "SanFranRockActive";
			}

			if (romname == crusnwld || romname == crusnwld24 || romname == crusnwld23 || romname == crusnwld20 || romname == crusnwld19 || romname == crusnwld17 || romname == crusnwld13)
			{


				configMinForce = configMinForceCrusnWld;
				configMaxForce = configMaxForceCrusnWld;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftCrusnWld;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftCrusnWld;
				configAlternativeMinForceRight = configAlternativeMinForceRightCrusnWld;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightCrusnWld;
				configFeedbackLength = configFeedbackLengthCrusnWld;
				PowerMode = PowerModeCrusnWld;
				EnableForceSpringEffect = EnableForceSpringEffectCrusnWld;
				ForceSpringStrength = ForceSpringStrengthCrusnWld;

				RunningFFB = "CrusnWldActive";
			}

			if (romname == offroadc || romname == offroadc4 || romname == offroadc3 || romname == offroadc1)
			{
				configMinForce = configMinForceOffRoadC;
				configMaxForce = configMaxForceOffRoadC;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftOffRoadC;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftOffRoadC;
				configAlternativeMinForceRight = configAlternativeMinForceRightOffRoadC;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightOffRoadC;
				configFeedbackLength = configFeedbackLengthOffRoadC;
				PowerMode = PowerModeOffRoadC;
				EnableForceSpringEffect = EnableForceSpringEffectOffRoadC;
				ForceSpringStrength = ForceSpringStrengthOffRoadC;

				RunningFFB = "OffroadChallengeActive";
			}

			if (romname == crusnusa || romname == crusnusa40 || romname == crusnusa21)
			{
				configMinForce = configMinForceCrusnUSA;
				configMaxForce = configMaxForceCrusnUSA;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftCrusnUSA;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftCrusnUSA;
				configAlternativeMinForceRight = configAlternativeMinForceRightCrusnUSA;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightCrusnUSA;
				configFeedbackLength = configFeedbackLengthCrusnUSA;
				PowerMode = PowerModeCrusnUSA;
				EnableForceSpringEffect = EnableForceSpringEffectCrusnUSA;
				ForceSpringStrength = ForceSpringStrengthCrusnUSA;

				RunningFFB = "CrusnUSAActive";
			}

			if (romname == calspeed || romname == calspeeda || romname == calspeedb)
			{
				configMinForce = configMinForceCalSpeed;
				configMaxForce = configMaxForceCalSpeed;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftCalSpeed;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftCalSpeed;
				configAlternativeMinForceRight = configAlternativeMinForceRightCalSpeed;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightCalSpeed;
				configFeedbackLength = configFeedbackLengthCalSpeed;
				PowerMode = PowerModeCalSpeed;
				EnableForceSpringEffect = EnableForceSpringEffectCalSpeed;
				ForceSpringStrength = ForceSpringStrengthCalSpeed;

				RunningFFB = "CalSpeedActive";
			}

			if (romname == sf2049 || romname == sf2049se || romname == sf2049te)
			{
				configMinForce = configMinForceSFRush2049;
				configMaxForce = configMaxForceSFRush2049;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSFRush2049;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSFRush2049;
				configAlternativeMinForceRight = configAlternativeMinForceRightSFRush2049;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSFRush2049;
				configFeedbackLength = configFeedbackLengthSFRush2049;
				PowerMode = PowerModeSFRush2049;
				EnableForceSpringEffect = EnableForceSpringEffectSFRush2049;
				ForceSpringStrength = ForceSpringStrengthSFRush2049;

				RunningFFB = "SanFran2049Active";
			}

			if (romname == harddriv1 || romname == harddrivb6 || romname == harddrivb || romname == harddrivg4 || romname == harddrivg || romname == harddrivj6 || romname == harddrivj ||
				romname == harddriv2 || romname == harddriv3 || romname == harddriv || romname == harddrivcb || romname == harddrivcg || romname == harddrivc1 || romname == harddrivc ||
				romname == hdrivairp || romname == hdrivair || romname == racedrivb1 || romname == racedrivb4 || romname == racedrivb || romname == racedrivg1 || romname == racedrivg4 ||
				romname == racedrivg || romname == racedriv1 || romname == racedriv2 || romname == racedriv3 || romname == racedriv4 || romname == racedriv || romname == racedrivcb4 || 
				romname == racedrivcb || romname == racedrivcg4 || romname == racedrivcg || romname == racedrivc2 || romname == racedrivc4 || romname == racedrivc || romname == racedrivpan)
			{
				configMinForce = configMinForceHardD;
				configMaxForce = configMaxForceHardD;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftHardD;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftHardD;
				configAlternativeMinForceRight = configAlternativeMinForceRightHardD;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightHardD;
				configFeedbackLength = configFeedbackLengthHardD;
				PowerMode = PowerModeHardD;
				EnableForceSpringEffect = EnableForceSpringEffectHardD;
				ForceSpringStrength = ForceSpringStrengthHardD;

				RunningFFB = "HardDrivinActive";
			}

			if (romname == revx || romname == revxp5)
			{
				configMinForce = configMinForceRevX;
				configMaxForce = configMaxForceRevX;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorRevX;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorRevX;
				configMinForceDevice2 = configMinForceRevXDevice2;
				configMaxForceDevice2 = configMaxForceRevXDevice2;
				configMinForceDevice3 = configMinForceRevXDevice3;
				configMaxForceDevice3 = configMaxForceRevXDevice3;

				RunningFFB = "LightGunActive";
			}

			if (romname == zombraid || romname == zombraidpj || romname == zombraidp)
			{
				configMinForce = configMinForceZombRaid;
				configMaxForce = configMaxForceZombRaid;
				configMinForceDevice2 = configMinForceZombRaidDevice2;
				configMaxForceDevice2 = configMaxForceZombRaidDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorZombRaid;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorZombRaid;

				RunningFFB = "LightGunActive";
			}

			if (romname == bbusters || romname == bbustersu || romname == bbustersua || romname == bbustersj)
			{
				configMinForce = configMinForceBBusters;
				configMaxForce = configMaxForceBBusters;
				configMinForceDevice2 = configMinForceBBustersDevice2;
				configMaxForceDevice2 = configMaxForceBBustersDevice2;
				configMinForceDevice3 = configMinForceBBustersDevice3;
				configMaxForceDevice3 = configMaxForceBBustersDevice3;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorBBusters;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorBBusters;

				RunningFFB = "LightGunActive";
			}

			if (romname == mechatt || romname == mechattu || romname == mechattu1 || romname == mechattj)
			{
				configMinForce = configMinForceMechatt;
				configMaxForce = configMaxForceMechatt;
				configMinForceDevice2 = configMinForceMechattDevice2;
				configMaxForceDevice2 = configMaxForceMechattDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorMechatt;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorMechatt;

				RunningFFB = "LightGunActive";
			}

			if (romname == tshoot)
			{
				configMinForce = configMinForceTShoot;
				configMaxForce = configMaxForceTShoot;
				configMinForceDevice2 = configMinForceTShootDevice2;
				configMaxForceDevice2 = configMaxForceTShootDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorTShoot;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorTShoot;

				RunningFFB = "LightGunActive";
			}

			if (romname == gunbustru || romname == gunbustr || romname == gunbustrj)
			{
				configMinForce = configMinForceGunBuster;
				configMaxForce = configMaxForceGunBuster;
				configMinForceDevice2 = configMinForceGunBusterDevice2;
				configMaxForceDevice2 = configMaxForceGunBusterDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorGunBuster;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorGunBuster;

				RunningFFB = "LightGunActive";
			}

			if (romname == alien3 || romname == alien3u)
			{
				configMinForce = configMinForceAlien3;
				configMaxForce = configMaxForceAlien3;
				configMinForceDevice2 = configMinForceAlien3Device2;
				configMaxForceDevice2 = configMaxForceAlien3Device2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorAlien3;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorAlien3;

				RunningFFB = "LightGunActive";
			}

			if (romname == ptblank2 || romname == ptblank2ua)
			{
				configMinForce = configMinForcePointBlank2;
				configMaxForce = configMaxForcePointBlank2;
				configMinForceDevice2 = configMinForcePointBlank2Device2;
				configMaxForceDevice2 = configMaxForcePointBlank2Device2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorPointBlank2;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorPointBlank2;

				RunningFFB = "LightGunActive";
			}

			if (romname == ghlpanic)
			{
				configMinForce = configMinForceGhoulPanic;
				configMaxForce = configMaxForceGhoulPanic;
				configMinForceDevice2 = configMinForceGhoulPanicDevice2;
				configMaxForceDevice2 = configMaxForceGhoulPanicDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorGhoulPanic;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorGhoulPanic;

				RunningFFB = "LightGunActive";
			}

			if (romname == spacegun || romname == spacegunu || romname == spacegunj)
			{
				configMinForce = configMinForceSpacegun;
				configMaxForce = configMaxForceSpacegun;
				configMinForceDevice2 = configMinForceSpacegunDevice2;
				configMaxForceDevice2 = configMaxForceSpacegunDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorSpacegun;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorSpacegun;

				RunningFFB = "LightGunActive";
			}

			if (romname == term2 || romname == term2la1 || romname == term2la2 || romname == term2la3 || romname == term2lg1)
			{
				configMinForce = configMinForceTerm2;
				configMaxForce = configMaxForceTerm2;
				configMinForceDevice2 = configMinForceTerm2Device2;
				configMaxForceDevice2 = configMaxForceTerm2Device2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorTerm2;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorTerm2;

				RunningFFB = "LightGunActive";
			}

			if (romname == rchase || romname == rchasej)
			{
				configMinForce = configMinForceRchase;
				configMaxForce = configMaxForceRchase;
				configMinForceDevice2 = configMinForceRchaseDevice2;
				configMaxForceDevice2 = configMaxForceRchaseDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorRchase;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorRchase;

				RunningFFB = "LightGunActive";
			}

			if (romname == lghost || romname == lghostd || romname == lghostu || romname == lghostud || romname == lghostj)
			{
				configMinForce = configMinForceLGhost;
				configMaxForce = configMaxForceLGhost;
				configMinForceDevice2 = configMinForceLGhostDevice2;
				configMaxForceDevice2 = configMaxForceLGhostDevice2;
				configMinForceDevice3 = configMinForceLGhostDevice3;
				configMaxForceDevice3 = configMaxForceLGhostDevice3;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorLGhost;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorLGhost;

				RunningFFB = "LightGunActive";
			}

			if (romname == timecris || romname == timecrisa)
			{
				configMinForce = configMinForceTimeCris;
				configMaxForce = configMaxForceTimeCris;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorTimeCris;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorTimeCris;

				RunningFFB = "LightGunActive";
			}

			if (romname == othunder || romname == othundero || romname == othunderuo || romname == othunderu || romname == othunderj)
			{
				configMinForce = configMinForceOThunder;
				configMaxForce = configMaxForceOThunder;
				configMinForceDevice2 = configMinForceOThunderDevice2;
				configMaxForceDevice2 = configMaxForceOThunderDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorOThunder;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorOThunder;

				RunningFFB = "LightGunActive";
			}

			if (romname == opwolf || romname == opwolfp || romname == opwolfj || romname == opwolfu || romname == opwolfa)
			{
				configMinForce = configMinForceOpWolf;
				configMaxForce = configMaxForceOpWolf;
				configMinForceDevice2 = configMinForceOpWolfDevice2;
				configMaxForceDevice2 = configMaxForceOpWolfDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorOpWolf;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorOpWolf;

				RunningFFB = "LightGunActive";
			}

			if (romname == undrfire || romname == undrfireu || romname == undrfirej)
			{
				configMinForce = configMinForceUFire;
				configMaxForce = configMaxForceUFire;
				configMinForceDevice2 = configMinForceUFireDevice2;
				configMaxForceDevice2 = configMaxForceUFireDevice2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorUFire;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorUFire;

				RunningFFB = "LightGunActive";
			}

			if (romname == orunners || romname == orunnersu || romname == orunnersj)
			{
				configMinForce = configMinForceORunners;
				configMaxForce = configMaxForceORunners;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftORunners;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftORunners;
				configAlternativeMinForceRight = configAlternativeMinForceRightORunners;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightORunners;
				configMinForceDevice2 = configMinForceORunnersDevice2;
				configMaxForceDevice2 = configMaxForceORunnersDevice2;
				configAlternativeMinForceLeftDevice2 = configAlternativeMinForceLeftORunnersDevice2;
				configAlternativeMaxForceLeftDevice2 = configAlternativeMaxForceLeftORunnersDevice2;
				configAlternativeMinForceRightDevice2 = configAlternativeMinForceRightORunnersDevice2;
				configAlternativeMaxForceRightDevice2 = configAlternativeMaxForceRightORunnersDevice2;
				configFeedbackLength = configFeedbackLengthORunners;
				EnableForceSpringEffect = EnableForceSpringEffectORunners;
				ForceSpringStrength = ForceSpringStrengthORunners;
				SinePeriod = SinePeriodORunners;
				SineFadePeriod = SineFadePeriodORunners;
				SineStrength = SineStrengthORunners;

				RunningFFB = "RacingActive1";
			}

			if (romname == toutrun || romname == toutrund || romname == toutrunj || romname == toutrunjd)
			{
				configMinForce = configMinForceTOutrun;
				configMaxForce = configMaxForceTOutrun;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftTOutrun;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftTOutrun;
				configAlternativeMinForceRight = configAlternativeMinForceRightTOutrun;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightTOutrun;
				configFeedbackLength = configFeedbackLengthTOutrun;
				EnableForceSpringEffect = EnableForceSpringEffectTOutrun;
				ForceSpringStrength = ForceSpringStrengthTOutrun;
				SinePeriod = SinePeriodTOutrun;
				SineFadePeriod = SineFadePeriodTOutrun;
				SineStrength = SineStrengthTOutrun;

				RunningFFB = "RacingActive1";
			}

			if (romname == cbombers || romname == cbombersj || romname == cbombersp)
			{
				configMinForce = configMinForceCBombers;
				configMaxForce = configMaxForceCBombers;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftCBombers;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftCBombers;
				configAlternativeMinForceRight = configAlternativeMinForceRightCBombers;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightCBombers;
				configFeedbackLength = configFeedbackLengthCBombers;
				EnableForceSpringEffect = EnableForceSpringEffectCBombers;
				ForceSpringStrength = ForceSpringStrengthCBombers;
				SinePeriod = SinePeriodCBombers;
				SineFadePeriod = SineFadePeriodCBombers;
				SineStrength = SineStrengthCBombers;

				RunningFFB = "RacingActive1";
			}

			if (romname == outrunra || romname == outrun || romname == outruneh)
			{
				configMinForce = configMinForceOutrun;
				configMaxForce = configMaxForceOutrun;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftOutrun;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftOutrun;
				configAlternativeMinForceRight = configAlternativeMinForceRightOutrun;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightOutrun;
				configFeedbackLength = configFeedbackLengthOutrun;
				EnableForceSpringEffect = EnableForceSpringEffectOutrun;
				ForceSpringStrength = ForceSpringStrengthOutrun;
				SinePeriod = SinePeriodOutrun;
				SineFadePeriod = SineFadePeriodOutrun;
				SineStrength = SineStrengthOutrun;

				RunningFFB = "OutrunActive";
			}

			if (romname == pdrift || romname == pdrifta || romname == pdrifte || romname == pdriftj || romname == pdriftl)
			{
				configMinForce = configMinForcePDrift;
				configMaxForce = configMaxForcePDrift;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftPDrift;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftPDrift;
				configAlternativeMinForceRight = configAlternativeMinForceRightPDrift;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightPDrift;
				configFeedbackLength = configFeedbackLengthPDrift;
				EnableForceSpringEffect = EnableForceSpringEffectPDrift;
				ForceSpringStrength = ForceSpringStrengthPDrift;
				SinePeriod = SinePeriodPDrift;
				SineFadePeriod = SineFadePeriodPDrift;
				SineStrength = SineStrengthPDrift;

				RunningFFB = "PDriftActive";
			}

			if (romname == aburner2 || romname == aburner2g)
			{
				configMinForce = configMinForceAfterBurner2;
				configMaxForce = configMaxForceAfterBurner2;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorAfterBurner2;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorAfterBurner2;

				RunningFFB = "AfterburnerActive";
			}

			if (romname == cischeat)
			{
				configMinForce = configMinForceCisHeat;
				configMaxForce = configMaxForceCisHeat;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftCisHeat;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftCisHeat;
				configAlternativeMinForceRight = configAlternativeMinForceRightCisHeat;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightCisHeat;
				configFeedbackLength = configFeedbackLengthCisHeat;
				EnableForceSpringEffect = EnableForceSpringEffectCisHeat;
				ForceSpringStrength = ForceSpringStrengthCisHeat;
				SinePeriod = SinePeriodCisHeat;
				SineFadePeriod = SineFadePeriodCisHeat;
				SineStrength = SineStrengthCisHeat;

				RunningFFB = "RacingActive2";
			}

			if (romname == f1gpstar || romname == f1gpstaro)
			{
				configMinForce = configMinForceF1GpStar;
				configMaxForce = configMaxForceF1GpStar;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftF1GpStar;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftF1GpStar;
				configAlternativeMinForceRight = configAlternativeMinForceRightF1GpStar;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightF1GpStar;
				configFeedbackLength = configFeedbackLengthF1GpStar;
				EnableForceSpringEffect = EnableForceSpringEffectF1GpStar;
				ForceSpringStrength = ForceSpringStrengthF1GpStar;
				SinePeriod = SinePeriodF1GpStar;
				SineFadePeriod = SineFadePeriodF1GpStar;
				SineStrength = SineStrengthF1GpStar;

				RunningFFB = "RacingActive2";
			}

			if (romname == f1gpstr2)
			{
				configMinForce = configMinForceF1GpStar2;
				configMaxForce = configMaxForceF1GpStar2;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftF1GpStar2;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftF1GpStar2;
				configAlternativeMinForceRight = configAlternativeMinForceRightF1GpStar2;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightF1GpStar2;
				configFeedbackLength = configFeedbackLengthF1GpStar2;
				EnableForceSpringEffect = EnableForceSpringEffectF1GpStar2;
				ForceSpringStrength = ForceSpringStrengthF1GpStar2;
				SinePeriod = SinePeriodF1GpStar2;
				SineFadePeriod = SineFadePeriodF1GpStar2;
				SineStrength = SineStrengthF1GpStar2;

				RunningFFB = "RacingActive2";
			}

			if ((RunningFFB != NULL) && (RunningFFB[0] != '\0'))
			{
				RomGameName = true;
			}
		}
	}

	if (!EmuName)
	{
		//Select code to run via emulator name using partial window title to avoid issues with FPS showing etc
		const TCHAR MAMEstring[] = TEXT("MAME");
		EnumWindows(FindWindowBySubstr, (LPARAM)MAMEstring);

		const TCHAR Supermodelstring[] = TEXT("Supermodel");
		EnumWindows(FindWindowBySubstr, (LPARAM)Supermodelstring);

		if (!EnumWindows(FindWindowBySubstr, (LPARAM)MAMEstring))
		{
			EmulatorName = "MAME";
		}

		if (!EnumWindows(FindWindowBySubstr, (LPARAM)Supermodelstring))
		{
			EmulatorName = "Supermodel";
		}

		Emulator = new char[256]; // Emulator name
		sprintf(Emulator, "%s", EmulatorName);

		if ((EmulatorName != NULL) && (EmulatorName[0] != '\0'))
		{
			EmuName = true;
		}
	}
	
	if (RomGameName && EmuName)
	{
		if (RunningFFB == Daytona2Active) //Daytona 2,Scud Race,Le Mans 24
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x09) && (stateFFB < 0x10))
				{
					//Spring
					double percentForce = (stateFFB - 9) / 16.0;
					triggers->Spring(percentForce);
				}

				if ((stateFFB > 0x1F) && (stateFFB < 0x30))
				{
					//Clutch
					double percentForce = (stateFFB - 31) / 16.0;
					triggers->Friction(percentForce);
				}

				if ((stateFFB > 0x2F) && (stateFFB < 0x40))
				{
					//Centering
					double percentForce = (stateFFB - 47) / 16.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(40, 0, percentForce);
				}

				if ((stateFFB > 0x3F) && (stateFFB < 0x50))
				{
					//Uncentering
					double percentForce = (stateFFB - 63) / 16.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(40, 0, percentForce);
				}

				if ((stateFFB > 0x4F) && (stateFFB < 0x60))
				{
					//Roll Right
					double percentForce = (stateFFB - 79) / 16.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x5F) && (stateFFB < 0x70))
				{
					//Roll Left
					double percentForce = (stateFFB - 95) / 16.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}

				//Test Menu
				if (stateFFB == 0x80)
				{
					triggers->Rumble(0, 0, 0);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
				}
				else if (stateFFB == 0x81)
				{
					triggers->Rumble(0.5, 0, 100);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0.5);
				}
				else if (stateFFB == 0x82)
				{
					triggers->Rumble(0, 0.5, 100);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0.5);
				}
			}
		}

		if (RunningFFB == DirtDevilsActive) //Dirt Devils
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if (stateFFB == 0x10)
				{
					double percentForce = 0.7;
					triggers->Spring(percentForce);
				}

				if ((stateFFB == 0x27) || (stateFFB == 0x30))
				{
					DirtDevilSine = false;
				}

				if (stateFFB == 0x2F)
				{
					DirtDevilSine = true;
				}

				if (DirtDevilSine)
				{
					double percentForce = (stateFFB - 31) / 16.0;
					triggers->Sine(60, 0, percentForce);
					triggers->Rumble(percentForce, percentForce, 100);
				}
			}
		}

		if (RunningFFB == Srally2Active) //Sega Rally 2, Emergency Call Ambulance
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x00) && (stateFFB < 0x26))
				{
					double percentForce = (stateFFB) / 37.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x3F) && (stateFFB < 0x66))
				{
					double percentForce = (stateFFB - 64) / 37.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == VirtuaRacingActive) //Virtua Racing
		{
			if (Emulator == MAME)
			{
				if (name == digit0)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB == 0x03) || (stateFFB == 0x07) || (stateFFB == 0x09) || (stateFFB == 0x10))
				{
					if (stateFFB == 0x07)
					{
						DontSineUntilRaceStart = true;
					}
					if (stateFFB == 0x09)
					{
						DontSineUntilRaceStart = false;
					}
					//Spring
					double percentForce = 0.8;
					triggers->Spring(percentForce);
				}

				else if ((stateFFB == 0x20) || (stateFFB == 0x28))
				{
					//Clutch
					double percentForce = 0.4;
					triggers->Friction(percentForce);
				}

				else if ((stateFFB > 0x2F) && (stateFFB < 0x40))
				{
					//Centering
					double percentForce = (stateFFB - 47) / 11.0;
					triggers->Spring(percentForce);
				}

				else if ((stateFFB == 0x40) || (stateFFB == 0x46) || (stateFFB == 0x4A))
				{
					if (stateFFB == 0x40)
					{
						//Uncentering
						double percentForce = 0.4;
						triggers->Rumble(percentForce, percentForce, 100);
						triggers->Sine(70, 30, percentForce);
					}
					else
					{
						if (DontSineUntilRaceStart)
						{
							//Uncentering
							double percentForce = 0.4;
							triggers->Rumble(percentForce, percentForce, 100);
							triggers->Sine(70, 30, percentForce);
						}
					}
				}

				else if ((stateFFB == 0x50) || (stateFFB == 0x5F))
				{
					//Roll Left
					double percentForce = 0.5;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB == 0x60) || (stateFFB == 0x6F))
				{
					//Roll Right
					double percentForce = 0.5;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}			
		}

		if (RunningFFB == SanFranActive) //San Francisco Rush
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == SanFranActive) //San Francisco Rush The Rock
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CrusnWldActive) //Cruis'n World
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == OffroadChallengeActive) //Off Road Challenge
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CrusnUSAActive) //Crusn USA
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CalSpeedActive) //California Speed
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}

		if (RunningFFB == LightGunActive) //LightGun Games
		{
			if (Emulator == MAME)
			{
				if (name == Player1_Recoil_Piston || name == Player1_Gun_Recoil || name == Left_Gun_Recoil || name == P1_Gun_Recoil || name == mcuout1 || name == P1_gun_recoil)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (name == Player2_Recoil_Piston || name == Player2_Gun_Recoil || name == Right_Gun_Recoil || name == P2_Gun_Recoil || name == P2_gun_recoil)
				{
					helpers->log("P2 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect2 = false;
					}

					stateFFBDevice2 = newstateFFB;
				}

				if (name == Player3_Gun_Recoil || name == P3_Gun_Recoil)
				{
					helpers->log("P3 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect3 = false;
					}

					stateFFBDevice3 = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (stateFFBDevice2 == 0x01)
				{
					Effect2 = true;
				}
				else
				{
					Effect2 = false;
				}

				if (stateFFBDevice3 == 0x01)
				{
					Effect3 = true;
				}
				else
				{
					Effect3 = false;
				}

				if (Effect1)
				{
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Rumble(0, 0, 0);
				}

				if (Effect2)
				{
					triggers->RumbleDevice2(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect2)
				{
					triggers->RumbleDevice2(0, 0, 0);
				}

				if (Effect3)
				{
					triggers->RumbleDevice3(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect3)
				{
					triggers->RumbleDevice3(0, 0, 0);
				}
			}
		}

		if (RunningFFB == RacingActive1) //Outrunners,Turbo Outrun,CBombers
		{
			if (Emulator == MAME)
			{
				if (name == MA_Steering_Wheel_motor || name == upright_wheel_motor || name == Vibration_motor || name == Wheel_vibration)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (name == MB_Steering_Wheel_motor)
				{
					helpers->log("P2 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect2 = false;
					}

					stateFFBDevice2 = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (stateFFBDevice2 == 0x01)
				{
					Effect2 = true;
				}
				else
				{
					Effect2 = false;
				}

				if (Effect1)
				{
					triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Sine(0, 0, 0);
					triggers->Rumble(0, 0, 0);
				}

				if (Effect2)
				{
					triggers->SineDevice2(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->RumbleDevice2(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect2)
				{
					triggers->SineDevice2(0, 0, 0);
					triggers->RumbleDevice2(0, 0, 0);
				}
			}
		}

		if (RunningFFB == RacingActive2) //Cisco Heat,F1 GpStar //Keep seperate as names is led2 and could possibly interfere with other outputs
		{
			if (Emulator == MAME)
			{
				if (name == led2)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (Effect1)
				{
					triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Sine(0, 0, 0);
					triggers->Rumble(0, 0, 0);
				}
			}
		}

		if (RunningFFB == AfterburnerActive) //Afterburner
		{
			if (Emulator == MAME)
			{
				if (name == lamp1)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (Effect1)
				{
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Rumble(0, 0, 0);
				}
			}
		}

		if (RunningFFB == OutrunActive)
		{
			if (Emulator == MAME)
			{
				if (name == Bank_Motor_Direction)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB != 0)
					{
						stateFFB = newstateFFB;
					}				
				}

				if (name == Vibration_motor)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB2 = newstateFFB;
				}

				if (name == Bank_Motor_Speed)
				{
					stateFFB3 = newstateFFB;					
				}

				if (Motion)
				{
					if (stateFFB == 0x01)
					{
						double percentForce = (1 + stateFFB3) / 8.0;
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					if (stateFFB == 0x02)
					{
						double percentForce = (1 + stateFFB3) / 8.0;
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
				}
				
				if (stateFFB == 1)
				{
					Motion = true;
					MotionFalse = false;
				}

				if (stateFFB2 == 1)
				{
					Motion = false;
				}

				if (StopConstant == 255)
				{
					MotionFalse = true;
				}

				if (MotionFalse)
				{
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
					Motion = false;
					StopConstant = 0;
					MotionFalse = false;				
				}

				if (!Motion)
				{
					
					if (stateFFB2 == 0x01)
					{
						Effect1 = true;
					}
					else
					{
						Effect1 = false;
					}

					if (Effect1)
					{
						triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
						triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
					}

					if (!Effect1)
					{
						triggers->Sine(0, 0, 0);
						triggers->Rumble(0, 0, 0);
					}
				}			
			}
		}

		if (RunningFFB == PDriftActive)
		{
			if (Emulator == MAME)
			{
				if (name == bank_motor_position)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if (name == vibration_motor)
				{
					stateFFB2 = newstateFFB;
				}

				if (name == upright_wheel_motor)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB3 = newstateFFB;
				}

				if (Motion)
				{
					if ((stateFFB > 0x00) && (stateFFB < 0x04))
					{
						double percentForce = (4 - stateFFB) / 3.0;
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					else if ((stateFFB > 0x04) && (stateFFB < 0x08))
					{
						double percentForce = (stateFFB - 4) / 3.0;
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}

					if (stateFFB2 >= 0)
					{
						double percentForce = stateFFB2 / 7.0;
						triggers->Sine(60, 0, percentForce / 3.0);
					}
				}

				if (stateFFB == 4)
				{
					Motion = true;
					MotionFalse = false;
				}

				if (stateFFB3 == 1)
				{
					Motion = false;
				}

				if (StopConstant == 255)
				{
					MotionFalse = true;
				}

				if (MotionFalse)
				{
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
					Motion = false;
					StopConstant = 0;
					MotionFalse = false;
				}

				if (!Motion)
				{
					if (stateFFB3 == 0x01)
					{
						Effect1 = true;
					}
					else
					{
						Effect1 = false;
					}

					if (Effect1)
					{
						triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
						triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
					}

					if (!Effect1)
					{
						triggers->Sine(0, 0, 0);
						triggers->Rumble(0, 0, 0);
					}
				}
			}
		}

		if (RunningFFB == SanFran2049Active) //San Fran 2049
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}

		if (RunningFFB == HardDrivinActive) //Hard Drivin
		{
			if (Emulator == MAME)
			{
				if (!HardDrivinFrame)
				{
					HardDrivinFrame = true;
				}
			
				if ((frame & 7) == 4)
				{
					HardDrivinFFB = (vals[0] & 15) + ((vals[3] & 7) << 5);

					if ((vals[1] & 0xF0) == 0xF0)
					{
						HardDrivinFFB |= 0x10;
					}
					 
					if ((vals[2] & 0xF0) == 0xF0)
					{
						HardDrivinFFB = -HardDrivinFFB;
					}

					helpers->log("got value: ");
					std::string ffs = std::to_string(HardDrivinFFB);
					helpers->log((char*)ffs.c_str());			

					static char test[256];
					memset(test, 0, 256);
					sprintf(test, "hex print: %d", HardDrivinFFB);
					OutputDebugStringA(test);

/*					if (HardDrivinFFB > 0)
					{
						double percentForce = HardDrivinFFB / 100.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}

					if (HardDrivinFFB < 0)
					{
						HardDrivinFFB = -HardDrivinFFB;
						double percentForce = HardDrivinFFB / 100.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}	*/				
				}
			}
		}
	}
}
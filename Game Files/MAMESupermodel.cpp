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

#include "MAMESupermodel.h"
#include <string>
#include <tchar.h>
#include <atlstr.h>
#include "SDL.h"
#include "../Common Files/SignatureScanning.h"

static char GameName[256];

//Supermodel Emulator Games
std::string dayto2pe("dayto2pe");
std::string daytona2("daytona2");
std::string dirtdvlsa("dirtdvlsa");
std::string dirtdvlsau("dirtdvlsau");
std::string dirtdvls("dirtdvls");
std::string dirtdvlsu("dirtdvlsu");
std::string dirtdvlsj("dirtdvlsj");
std::string dirtdvlsg("dirtdvlsg");
std::string ecau("ecau");
std::string eca("eca");
std::string ecap("ecap");
std::string ecaj("ecaj");
std::string lemans24("lemans24");
std::string scud("scud");
std::string scuda("scuda");
std::string scuddx("scuddx");
std::string scudau("scudau");
std::string scudj("scudj");
std::string scudplus("scudplus");
std::string scudplusa("scudplusa");
std::string srally2("srally2");
std::string srally2x("srally2x");
std::string srally2dx("srally2dx");
std::string srally2p("srally2p");
std::string srally2pa("srally2pa");

//MAME Games
std::string aburner2("aburner2");
std::string aburner2g("aburner2g");
std::string acedrive("acedrive");
std::string acedrvrw("acedrvrw");
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
std::string daytona("daytona");
std::string daytonas("daytonas");
std::string daytonase("daytonase");
std::string dirtdash("dirtdash");
std::string dirtdasha("dirtdasha");
std::string dirtdashj("dirtdashj");
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
std::string indy500("indy500");
std::string indy500d("indy500d");
std::string indy500to("indy500to");
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
std::string raverace("raverace");
std::string raveracw("raveracw");
std::string raveracj("raveracj");
std::string raveracja("raveracja");
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
std::string sgt24h("sgt24h");
std::string srallyc("srallyc");
std::string srallycb("srallycb");
std::string srallycdxa("srallycdxa");
std::string srallycdx("srallycdx");
std::string spacegun("spacegun");
std::string spacegunu("spacegunu");
std::string spacegunj("spacegunj");
std::string superchs("superchs");
std::string superchsp("superchsp");
std::string superchsj("superchsj");
std::string superchsu("superchsu");
std::string stcc("stcc");
std::string stcca("stcca");
std::string stccb("stccb");
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
std::string hyprdriv("hyprdriv");
std::string vaportrx("vaportrx");
std::string vaportrp("vaportrp");
std::string victlapw("victlapw");
std::string victlap("victlap");
std::string dblaxle("dblaxle");
std::string dblaxleu("dblaxleu");
//Flycast Below
std::string InitialDVer1("INITIAL D\n");
std::string InitialDVer2("INITIAL D Ver.2\n");
std::string InitialDVer3("INITIAL D Ver.3\n");
std::string EighteenWheeler("18WHEELER\n");
std::string MaximumSPEED("MAXIMUM SPEED\n");
std::string FasterThanSPEED("FASTER THAN SPEED\n");
std::string F355ChallengeJapan("F355 CHALLENGE JAPAN\n");
std::string ClubKartInJapan("CLUB KART IN JAPAN\n");
std::string TheKingOfRoute66("THE KING OF ROUTE66\n");

//Our string to load game from
std::string M2Active("M2Active");
std::string M2PatternActive("M2PatternActive");
std::string Daytona2Active("Daytona2Active");
std::string DirtDevilsActive("DirtDevilsActive");
std::string SrallyActive("SrallyActive");
std::string Srally2Active("Srally2Active");
std::string VirtuaRacingActive("VirtuaRacingActive");
std::string HardDrivinActive("HardDrivinActive");
std::string LightGunActive("LightGunActive");
std::string NamcoFFBActive("NamcoFFBActive");
std::string RacingFullValueActive1("RacingFullValueActive1");
std::string RacingFullValueActive2("RacingFullValueActive2");
std::string RacingActive1("RacingActive1");
std::string RacingActive2("RacingActive2");
std::string RaveRacerActive("RaveRacerActive");
std::string AfterburnerActive("AfterburnerActive");
std::string OutrunActive("OutrunActive");
std::string PDriftActive("PDriftActive");
std::string SuperChaseActive("SuperChaseActive");
std::string MaximumSpeedActive("MaximumSpeedActive");
std::string InitialDActive("InitialDActive");
std::string NaomiFFBActive("NaomiFFBActive");

//Names of FFB Outputs
std::string RawDrive("RawDrive");
std::string digit0("digit0");
std::string digit1("digit1");
std::string wheel("wheel");
std::string lamp1("lamp1");
std::string led2("led2");
std::string cpuled6("cpuled6");
std::string Vibration_motor("Vibration_motor");
std::string vibration_motor("vibration_motor");
std::string Wheel_vibration("Wheel_vibration");
std::string Wheel_Vibration("Wheel_Vibration");
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
//Flycast
std::string awffb("awffb");
std::string midiffb("midiffb");
std::string m3ffb("m3ffb");

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
extern int enableLogging;
extern int configFeedbackLength;
extern int configGameId;
extern int AlternativeFFB;
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
extern int EnableDamper;
extern int DamperStrength;
extern int DoubleConstant;
extern int DoubleSine;

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
static int EnableDamperDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperDaytona2"), 0, settingsFilename);
static int DamperStrengthDaytona2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthDaytona2"), 100, settingsFilename);

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
static int EnableDamperScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperScud"), 0, settingsFilename);
static int DamperStrengthScud = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthScud"), 100, settingsFilename);

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
static int EnableDamperLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperLeMans"), 0, settingsFilename);
static int DamperStrengthLeMans = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthLeMans"), 100, settingsFilename);

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
static int EnableDamperDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperDirtDevils"), 0, settingsFilename);
static int DamperStrengthDirtDevils = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthDirtDevils"), 100, settingsFilename);

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
static int EnableDamperSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSRally2"), 0, settingsFilename);
static int DamperStrengthSRally2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSRally2"), 100, settingsFilename);

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
static int EnableDamperECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperECA"), 0, settingsFilename);
static int DamperStrengthECA = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthECA"), 100, settingsFilename);

static int configMinForceVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceVirtuaRacing"), 0, settingsFilename);
static int configMaxForceVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceVirtuaRacing"), 100, settingsFilename);
static int configAlternativeMinForceLeftVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftVirtuaRacing"), 0, settingsFilename);
static int configAlternativeMaxForceLeftVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftVirtuaRacing"), 100, settingsFilename);
static int configAlternativeMinForceRightVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightVirtuaRacing"), 0, settingsFilename);
static int configAlternativeMaxForceRightVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightVirtuaRacing"), 100, settingsFilename);
static int configFeedbackLengthVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthVirtuaRacing"), 120, settingsFilename);
static int EnableForceSpringEffectVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectVirtuaRacing"), 0, settingsFilename);
static int ForceSpringStrengthVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthVirtuaRacing"), 0, settingsFilename);
static int EnableDamperVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperVirtuaRacing"), 0, settingsFilename);
static int DamperStrengthVirtuaRacing = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthVirtuaRacing"), 100, settingsFilename);

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
static int EnableDamperSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSFRush"), 0, settingsFilename);
static int DamperStrengthSFRush = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSFRush"), 100, settingsFilename);

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
static int EnableDamperSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSFRushRock"), 0, settingsFilename);
static int DamperStrengthSFRushRock = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSFRushRock"), 100, settingsFilename);

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
static int EnableDamperCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperCrusnWld"), 0, settingsFilename);
static int DamperStrengthCrusnWld = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthCrusnWld"), 100, settingsFilename);

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
static int EnableDamperOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperOffRoadC"), 0, settingsFilename);
static int DamperStrengthOffRoadC = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthOffRoadC"), 100, settingsFilename);

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
static int EnableDamperCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperCrusnUSA"), 0, settingsFilename);
static int DamperStrengthCrusnUSA = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthCrusnUSA"), 100, settingsFilename);

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
static int EnableDamperCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperCalSpeed"), 0, settingsFilename);
static int DamperStrengthCalSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthCalSpeed"), 100, settingsFilename);

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
static int EnableDamperSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSFRush2049"), 0, settingsFilename);
static int DamperStrengthSFRush2049 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSFRush2049"), 100, settingsFilename);

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
static int EnableDamperHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperHardD"), 0, settingsFilename);
static int DamperStrengthHardD = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthHardD"), 100, settingsFilename);

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
static int RumbleStrengthLeftMotorORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorORunners"), 0, settingsFilename);
static int RumbleStrengthRightMotorORunners = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorORunners"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorTOutrun"), 0, settingsFilename);
static int RumbleStrengthRightMotorTOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorTOutrun"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorCBombers"), 0, settingsFilename);
static int RumbleStrengthRightMotorCBombers = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorCBombers"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorOutrun"), 0, settingsFilename);
static int RumbleStrengthRightMotorOutrun = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorOutrun"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorPDrift"), 0, settingsFilename);
static int RumbleStrengthRightMotorPDrift = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorPDrift"), 0, settingsFilename);

static int configMinForceDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDAxle"), 0, settingsFilename);
static int configMaxForceDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDAxle"), 100, settingsFilename);
static int configAlternativeMinForceLeftDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDAxle"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDAxle"), 100, settingsFilename);
static int configAlternativeMinForceRightDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDAxle"), 0, settingsFilename);
static int configAlternativeMaxForceRightDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDAxle"), 100, settingsFilename);
static int configFeedbackLengthDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDAxle"), 120, settingsFilename);
static int EnableForceSpringEffectDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDAxle"), 0, settingsFilename);
static int ForceSpringStrengthDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDAxle"), 0, settingsFilename);
static int SinePeriodDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriodDAxle"), 0, settingsFilename);
static int SineFadePeriodDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriodDAxle"), 0, settingsFilename);
static int SineStrengthDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrengthDAxle"), 0, settingsFilename);
static int RumbleStrengthLeftMotorDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorDAxle"), 0, settingsFilename);
static int RumbleStrengthRightMotorDAxle = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorDAxle"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorCisHeat"), 0, settingsFilename);
static int RumbleStrengthRightMotorCisHeat = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorCisHeat"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorF1GpStar"), 0, settingsFilename);
static int RumbleStrengthRightMotorF1GpStar = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorF1GpStar"), 0, settingsFilename);

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
static int RumbleStrengthLeftMotorF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotorF1GpStar2"), 0, settingsFilename);
static int RumbleStrengthRightMotorF1GpStar2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotorF1GpStar2"), 0, settingsFilename);

static int configMinForceHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceHyperDrive"), 0, settingsFilename);
static int configMaxForceHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceHyperDrive"), 100, settingsFilename);
static int configAlternativeMinForceLeftHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftHyperDrive"), 0, settingsFilename);
static int configAlternativeMaxForceLeftHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftHyperDrive"), 100, settingsFilename);
static int configAlternativeMinForceRightHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightHyperDrive"), 0, settingsFilename);
static int configAlternativeMaxForceRightHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightHyperDrive"), 100, settingsFilename);
static int configFeedbackLengthHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthHyperDrive"), 120, settingsFilename);
static int EnableForceSpringEffectHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectHyperDrive"), 0, settingsFilename);
static int ForceSpringStrengthHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthHyperDrive"), 0, settingsFilename);
static int EnableDamperHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperHyperDrive"), 0, settingsFilename);
static int DamperStrengthHyperDrive = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthHyperDrive"), 100, settingsFilename);

static int configMinForceVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceVaporTrx"), 0, settingsFilename);
static int configMaxForceVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceVaporTrx"), 100, settingsFilename);
static int configAlternativeMinForceLeftVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftVaporTrx"), 0, settingsFilename);
static int configAlternativeMaxForceLeftVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftVaporTrx"), 100, settingsFilename);
static int configAlternativeMinForceRightVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightVaporTrx"), 0, settingsFilename);
static int configAlternativeMaxForceRightVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightVaporTrx"), 100, settingsFilename);
static int configFeedbackLengthVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthVaporTrx"), 120, settingsFilename);
static int EnableForceSpringEffectVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectVaporTrx"), 0, settingsFilename);
static int ForceSpringStrengthVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthVaporTrx"), 0, settingsFilename);
static int EnableDamperVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperVaporTrx"), 0, settingsFilename);
static int DamperStrengthVaporTrx = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthVaporTrx"), 100, settingsFilename);

static int configMinForceRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceRaveRacer"), 0, settingsFilename);
static int configMaxForceRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceRaveRacer"), 100, settingsFilename);
static int configAlternativeMinForceLeftRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftRaveRacer"), 0, settingsFilename);
static int configAlternativeMaxForceLeftRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftRaveRacer"), 100, settingsFilename);
static int configAlternativeMinForceRightRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightRaveRacer"), 0, settingsFilename);
static int configAlternativeMaxForceRightRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightRaveRacer"), 100, settingsFilename);
static int PowerModeRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeRaveRacer"), 0, settingsFilename);
static int configFeedbackLengthRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthRaveRacer"), 120, settingsFilename);
static int EnableForceSpringEffectRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectRaveRacer"), 0, settingsFilename);
static int ForceSpringStrengthRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthRaveRacer"), 0, settingsFilename);
static int EnableDamperRaveRacer= GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperRaveRacer"), 0, settingsFilename);
static int DamperStrengthRaveRacer = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthRaveRacer"), 100, settingsFilename);

static int configMinForceDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDaytona"), 0, settingsFilename);
static int configMaxForceDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDaytona"), 100, settingsFilename);
static int configAlternativeMinForceLeftDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDaytona"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDaytona"), 100, settingsFilename);
static int configAlternativeMinForceRightDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDaytona"), 0, settingsFilename);
static int configAlternativeMaxForceRightDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDaytona"), 100, settingsFilename);
static int PowerModeDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeDaytona"), 0, settingsFilename);
static int configFeedbackLengthDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDaytona"), 120, settingsFilename);
static int EnableForceSpringEffectDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDaytona"), 0, settingsFilename);
static int ForceSpringStrengthDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDaytona"), 0, settingsFilename);
static int EnableDamperDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperDaytona"), 0, settingsFilename);
static int DamperStrengthDaytonaMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthDaytona"), 100, settingsFilename);

static int configMinForceSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSRally"), 0, settingsFilename);
static int configMaxForceSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSRally"), 100, settingsFilename);
static int configAlternativeMinForceLeftSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSRally"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSRally"), 100, settingsFilename);
static int configAlternativeMinForceRightSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSRally"), 0, settingsFilename);
static int configAlternativeMaxForceRightSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSRally"), 100, settingsFilename);
static int PowerModeSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSRally"), 0, settingsFilename);
static int configFeedbackLengthSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSRally"), 120, settingsFilename);
static int EnableForceSpringEffectSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSRally"), 0, settingsFilename);
static int ForceSpringStrengthSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSRally"), 0, settingsFilename);
static int EnableDamperSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSRally"), 0, settingsFilename);
static int DamperStrengthSRallyMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSRally"), 100, settingsFilename);

static int configMinForceIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceIndy500"), 0, settingsFilename);
static int configMaxForceIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceIndy500"), 100, settingsFilename);
static int configAlternativeMinForceLeftIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftIndy500"), 0, settingsFilename);
static int configAlternativeMaxForceLeftIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftIndy500"), 100, settingsFilename);
static int configAlternativeMinForceRightIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightIndy500"), 0, settingsFilename);
static int configAlternativeMaxForceRightIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightIndy500"), 100, settingsFilename);
static int PowerModeIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeIndy500"), 0, settingsFilename);
static int configFeedbackLengthIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthIndy500"), 120, settingsFilename);
static int EnableForceSpringEffectIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectIndy500"), 0, settingsFilename);
static int ForceSpringStrengthIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthIndy500"), 0, settingsFilename);
static int EnableDamperIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperIndy500"), 0, settingsFilename);
static int DamperStrengthIndy500MAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthIndy500"), 100, settingsFilename);

static int configMinForceSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSuperGT"), 0, settingsFilename);
static int configMaxForceSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSuperGT"), 100, settingsFilename);
static int configAlternativeMinForceLeftSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSuperGT"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSuperGT"), 100, settingsFilename);
static int configAlternativeMinForceRightSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSuperGT"), 0, settingsFilename);
static int configAlternativeMaxForceRightSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSuperGT"), 100, settingsFilename);
static int PowerModeSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSuperGT"), 0, settingsFilename);
static int configFeedbackLengthSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSuperGT"), 120, settingsFilename);
static int EnableForceSpringEffectSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSuperGT"), 0, settingsFilename);
static int ForceSpringStrengthSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSuperGT"), 0, settingsFilename);
static int EnableDamperSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSuperGT"), 0, settingsFilename);
static int DamperStrengthSuperGTMAME = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSuperGT"), 100, settingsFilename);

static int configMinForceSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSuperChase"), 0, settingsFilename);
static int configMaxForceSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSuperChase"), 100, settingsFilename);
static int configAlternativeMinForceLeftSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSuperChase"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSuperChase"), 100, settingsFilename);
static int configAlternativeMinForceRightSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSuperChase"), 0, settingsFilename);
static int configAlternativeMaxForceRightSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSuperChase"), 100, settingsFilename);
static int PowerModeSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSuperChase"), 0, settingsFilename);
static int configFeedbackLengthSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSuperChase"), 120, settingsFilename);
static int EnableForceSpringEffectSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSuperChase"), 0, settingsFilename);
static int ForceSpringStrengthSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSuperChase"), 0, settingsFilename);
static int EnableDamperSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperSuperChase"), 0, settingsFilename);
static int DamperStrengthSuperChase = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthSuperChase"), 100, settingsFilename);

static int configMinForceDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDirtDash"), 0, settingsFilename);
static int configMaxForceDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDirtDash"), 100, settingsFilename);
static int configAlternativeMinForceLeftDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDirtDash"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDirtDash"), 100, settingsFilename);
static int configAlternativeMinForceRightDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDirtDash"), 0, settingsFilename);
static int configAlternativeMaxForceRightDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDirtDash"), 100, settingsFilename);
static int PowerModeDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeDirtDash"), 0, settingsFilename);
static int configFeedbackLengthDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDirtDash"), 120, settingsFilename);
static int EnableForceSpringEffectDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDirtDash"), 0, settingsFilename);
static int ForceSpringStrengthDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDirtDash"), 0, settingsFilename);
static int FFBDivideDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBDivideDirtDash"), 0, settingsFilename);
static int EnableDamperDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperDirtDash"), 0, settingsFilename);
static int DamperStrengthDirtDash = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthDirtDash"), 100, settingsFilename);

static int configMinForceAceDriverVictory= GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceAceDriverVictory"), 0, settingsFilename);
static int configMaxForceAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceAceDriverVictory"), 100, settingsFilename);
static int configAlternativeMinForceLeftAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftAceDriverVictory"), 0, settingsFilename);
static int configAlternativeMaxForceLeftAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftAceDriverVictory"), 100, settingsFilename);
static int configAlternativeMinForceRightAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightAceDriverVictory"), 0, settingsFilename);
static int configAlternativeMaxForceRightAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightAceDriverVictory"), 100, settingsFilename);
static int PowerModeAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeAceDriverVictory"), 0, settingsFilename);
static int configFeedbackLengthAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthAceDriverVictory"), 120, settingsFilename);
static int EnableForceSpringEffectAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectAceDriverVictory"), 0, settingsFilename);
static int ForceSpringStrengthAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthAceDriverVictory"), 0, settingsFilename);
static int FFBDivideAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBDivideAceDriverVictory"), 0, settingsFilename);
static int EnableDamperAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperAceDriverVictory"), 0, settingsFilename);
static int DamperStrengthAceDriverVictory = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthAceDriverVictory"), 100, settingsFilename);

static int configMinForceAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceAceDriver"), 0, settingsFilename);
static int configMaxForceAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceAceDriver"), 100, settingsFilename);
static int configAlternativeMinForceLeftAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftAceDriver"), 0, settingsFilename);
static int configAlternativeMaxForceLeftAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftAceDriver"), 100, settingsFilename);
static int configAlternativeMinForceRightAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightAceDriver"), 0, settingsFilename);
static int configAlternativeMaxForceRightAceDriver= GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightAceDriver"), 100, settingsFilename);
static int PowerModeAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeAceDriver"), 0, settingsFilename);
static int configFeedbackLengthAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthAceDriver"), 120, settingsFilename);
static int EnableForceSpringEffectAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectAceDriver"), 0, settingsFilename);
static int ForceSpringStrengthAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthAceDriver"), 0, settingsFilename);
static int FFBDivideAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBDivideAceDriver"), 0, settingsFilename);
static int EnableDamperAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperAceDriver"), 0, settingsFilename);
static int DamperStrengthAceDriver = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthAceDriver"), 100, settingsFilename);

static int configMinForceInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceInitialD"), 0, settingsFilename);
static int configMaxForceInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceInitialD"), 100, settingsFilename);
static int configAlternativeMinForceLeftInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftInitialD"), 0, settingsFilename);
static int configAlternativeMaxForceLeftInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftInitialD"), 100, settingsFilename);
static int configAlternativeMinForceRightInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightInitialD"), 0, settingsFilename);
static int configAlternativeMaxForceRightInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightInitialD"), 100, settingsFilename);
static int configFeedbackLengthInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthInitialD"), 120, settingsFilename);
static int PowerModeInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeInitialD"), 0, settingsFilename);
static int EnableForceSpringEffectInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectInitialD"), 0, settingsFilename);
static int ForceSpringStrengthInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthInitialD"), 0, settingsFilename);
static int EnableDamperInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperInitialD"), 0, settingsFilename);
static int DamperStrengthInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthInitialD"), 100, settingsFilename);
static int DoubleSineInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSineInitialD"), 0, settingsFilename);
static int DoubleConstantInitialD = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleConstantInitialD"), 0, settingsFilename);

static int configMinForceF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceF355"), 0, settingsFilename);
static int configMaxForceF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceF355"), 100, settingsFilename);
static int configAlternativeMinForceLeftF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftF355"), 0, settingsFilename);
static int configAlternativeMaxForceLeftF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftF355"), 100, settingsFilename);
static int configAlternativeMinForceRightF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightF355"), 0, settingsFilename);
static int configAlternativeMaxForceRightF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightF355"), 100, settingsFilename);
static int configFeedbackLengthF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthF355"), 120, settingsFilename);
static int PowerModeF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeF355"), 0, settingsFilename);
static int EnableForceSpringEffectF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectF355"), 0, settingsFilename);
static int ForceSpringStrengthF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthF355"), 0, settingsFilename);
static int EnableDamperF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperF355"), 0, settingsFilename);
static int DamperStrengthF355 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthF355"), 100, settingsFilename);

static int configMinForce18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForce18Wheeler"), 0, settingsFilename);
static int configMaxForce18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForce18Wheeler"), 100, settingsFilename);
static int configAlternativeMinForceLeft18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeft18Wheeler"), 0, settingsFilename);
static int configAlternativeMaxForceLeft18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeft18Wheeler"), 100, settingsFilename);
static int configAlternativeMinForceRight18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRight18Wheeler"), 0, settingsFilename);
static int configAlternativeMaxForceRight18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRight18Wheeler"), 100, settingsFilename);
static int configFeedbackLength18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength18Wheeler"), 120, settingsFilename);
static int PowerMode18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerMode18Wheeler"), 0, settingsFilename);
static int EnableForceSpringEffect18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect18Wheeler"), 0, settingsFilename);
static int ForceSpringStrength18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength18Wheeler"), 0, settingsFilename);
static int EnableDamper18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamper18Wheeler"), 0, settingsFilename);
static int DamperStrength18Wheeler = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrength18Wheeler"), 100, settingsFilename);

static int configMinForceFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceFasterThanSpeed"), 0, settingsFilename);
static int configMaxForceFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceFasterThanSpeed"), 100, settingsFilename);
static int configAlternativeMinForceLeftFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftFasterThanSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceLeftFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftFasterThanSpeed"), 100, settingsFilename);
static int configAlternativeMinForceRightFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightFasterThanSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceRightFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightFasterThanSpeed"), 100, settingsFilename);
static int configFeedbackLengthFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthFasterThanSpeed"), 120, settingsFilename);
static int PowerModeFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeFasterThanSpeed"), 0, settingsFilename);
static int EnableForceSpringEffectFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectFasterThanSpeed"), 0, settingsFilename);
static int ForceSpringStrengthFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthFasterThanSpeed"), 0, settingsFilename);
static int EnableDamperFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperFasterThanSpeed"), 0, settingsFilename);
static int DamperStrengthFasterThanSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthFasterThanSpeed"), 100, settingsFilename);

static int configMinForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceMaximumSpeed"), 0, settingsFilename);
static int configMaxForceMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceMaximumSpeed"), 100, settingsFilename);
static int configAlternativeMinForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftMaximumSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceLeftMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftMaximumSpeed"), 100, settingsFilename);
static int configAlternativeMinForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightMaximumSpeed"), 0, settingsFilename);
static int configAlternativeMaxForceRightMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightMaximumSpeed"), 100, settingsFilename);
static int configFeedbackLengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthMaximumSpeed"), 120, settingsFilename);
static int PowerModeMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeMaximumSpeed"), 0, settingsFilename);
static int EnableForceSpringEffectMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectMaximumSpeed"), 0, settingsFilename);
static int ForceSpringStrengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthMaximumSpeed"), 0, settingsFilename);
static int EnableDamperMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperMaximumSpeed"), 0, settingsFilename);
static int DamperStrengthMaximumSpeed = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthMaximumSpeed"), 100, settingsFilename);

static int configMinForceClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceClubKart"), 0, settingsFilename);
static int configMaxForceClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceClubKart"), 100, settingsFilename);
static int configAlternativeMinForceLeftClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftClubKart"), 0, settingsFilename);
static int configAlternativeMaxForceLeftClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftClubKart"), 100, settingsFilename);
static int configAlternativeMinForceRightClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightClubKart"), 0, settingsFilename);
static int configAlternativeMaxForceRightClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightClubKart"), 100, settingsFilename);
static int configFeedbackLengthClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthClubKart"), 120, settingsFilename);
static int PowerModeClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeClubKart"), 0, settingsFilename);
static int EnableForceSpringEffectClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectClubKart"), 0, settingsFilename);
static int ForceSpringStrengthClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthClubKart"), 0, settingsFilename);
static int EnableDamperClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperClubKart"), 0, settingsFilename);
static int DamperStrengthClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthClubKart"), 100, settingsFilename);
static int DoubleSineClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSineClubKart"), 0, settingsFilename);
static int DoubleConstantClubKart = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleConstantClubKart"), 0, settingsFilename);

static int configMinForceKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceKingOfRoute66"), 0, settingsFilename);
static int configMaxForceKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceKingOfRoute66"), 100, settingsFilename);
static int configAlternativeMinForceLeftKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftKingOfRoute66"), 0, settingsFilename);
static int configAlternativeMaxForceLeftKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftKingOfRoute66"), 100, settingsFilename);
static int configAlternativeMinForceRightKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightKingOfRoute66"), 0, settingsFilename);
static int configAlternativeMaxForceRightKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightKingOfRoute66"), 100, settingsFilename);
static int configFeedbackLengthKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthKingOfRoute66"), 120, settingsFilename);
static int PowerModeKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeKingOfRoute66"), 0, settingsFilename);
static int EnableForceSpringEffectKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectKingOfRoute66"), 0, settingsFilename);
static int ForceSpringStrengthKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthKingOfRoute66"), 0, settingsFilename);
static int EnableDamperKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperKingOfRoute66"), 0, settingsFilename);
static int DamperStrengthKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthKingOfRoute66"), 100, settingsFilename);
static int DoubleSineKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleSineKingOfRoute66"), 0, settingsFilename);
static int DoubleConstantKingOfRoute66 = GetPrivateProfileInt(TEXT("Settings"), TEXT("DoubleConstantKingOfRoute66"), 0, settingsFilename);

static bool init = false;
static bool initSpring = false;
static bool EmuName = false;
static bool RomGameName = false;
static bool Effect1 = false;
static bool Effect2 = false;
static bool Effect3 = false;
static bool DirtDevilSine = false;
static bool DontSineUntilRaceStart = false;
static bool HardDrivinFrame = false;
static bool NaomiFFBGo = false;
static bool Motion = false;
static bool MotionFalse = false;
static bool StartEffectOnce = false;
static bool PatternFind = false;
static bool Scan = false;
static bool ScanFirstBootDelay = false;
static bool PatternLaunch = false;

HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;

static const char* FlycastnameFFB;
const char* nameFFB;
const char* EmulatorName;
char* name;
char* romname;
char* RunningFFB;
char* Emulator;
int vals[5] = { 0 };
int state4 = 0;
int state3 = 0;
int state2 = 0;
int state1 = 0;
int state0 = 0;
int frame = 0;
int HardDrivinFFB;
int StopConstant;
int newstateFFB;
int oldstateFFB;
int EffectCount;
int stateFFB;
int stateFFB2;
int stateFFB3;
int stateFFBDevice2;
int stateFFBDevice3;
int SineEffectState;
double Divide;
static INT_PTR FFBAddress;
static UINT8 ff;

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
static int(__stdcall* ExitOri)(UINT uExitCode);
static int __stdcall ExitHook(UINT uExitCode)
{
	TerminateProcess(GetCurrentProcess(), 0);
	return 0;
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

	dll_init(0, L"Test", mame_start_ptr, mame_stop_ptr, mame_copydata_ptr, mame_updatestate_ptr, mame_output_ptr);

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

static void removeWord(char* str, char* toRemove)
{
	int i, j, stringLen, toRemoveLen;
	int found;

	stringLen = strlen(str);
	toRemoveLen = strlen(toRemove);


	for (i = 0; i <= stringLen - toRemoveLen; i++)
	{
		found = 1;
		for (j = 0; j < toRemoveLen; j++)
		{
			if (str[i + j] != toRemove[j])
			{
				found = 0;
				break;
			}
		}

		if (str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n' && str[i + j] != '\0')
		{
			found = 0;
		}


		if (found == 1)
		{
			for (j = i; j <= stringLen - toRemoveLen; j++)
			{
				str[j] = str[j + toRemoveLen];
			}

			stringLen = stringLen - toRemoveLen;

			i--;
		}
	}
}

static void CurrentGameName(Helpers* helpers)
{
	helpers->info("Game = %s", GameName);
}

int __stdcall mame_copydata(int id, const char* name)
{
	WCHAR buf[256];

	wsprintf(buf, L"id %d = '%S'\r\n", id, name);

	if (id == 0)
	{
		char RomName[256];
		sprintf(RomName, "%s", name);

		removeWord(RomName, "game =");

		int whitespace = 0;

		for (int i = 0; i < strlen(RomName); i++)
		{
			if (RomName[i] == ' ' || RomName[i] == '\t')
				whitespace++;
			else
				break;
		}

		for (int i = 0; i < strlen(RomName); i++)
		{
			if (i + whitespace < strlen(RomName))
				RomName[i] = RomName[i + whitespace];
			else
				RomName[i] = 0;
		}

		sprintf(GameName, "%s", RomName);

		CurrentGameName(0);
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

	CStringA stringName(name);
	nameFFB = stringName;

	newstateFFB = state;

	if (HardDrivinFrame)
	{
		if (name == wheelA)
		{
			state3 = state2;
			state2 = state1;
			state1 = state0;
			state0 = state;

			//detect 0xE0 and 0x00 
			boolean stop = false;
			if ((state == 0xE0 && state1 == 0x00 && state2 == 0xE0 && state3 == 0x00) || 
				(state == 0x00 && state1 == 0xE0 && state2 == 0x00 && state3 == 0xE0)) 
			{
				stop = true;
				frame = 0;
			}
			if (frame > 4) {
				frame = 0;
			}
			//vals[0] should always be < 200. vals[1] should always be > 200. If not, the state is invalid, start over. 
			if (frame > 2 && (vals[0] > 200 || (vals[1] < 200 && vals[1] != 0))) {
				frame = 0;
				vals[1] = 0;
				vals[2] = 0;
				vals[3] = 0;
			}

			//if (!(((state == 0xE0) || (state == 0)) && ((frame == 0) || (frame == 4))))
			//if ((state != 0xE0) && (state != 0x00))
			if(!stop)
			{
				vals[frame] = state;
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

static DWORD WINAPI ScanThread(LPVOID lpParam)
{
	if (romname == raveracw || romname == raveracj || romname == raveracja || romname == raverace) //Rave Racer
	{
		aAddy2 = PatternScan("\xF8\x89\xC2\x00\x9C\x0B\x40\x05\x64\x38\x05\x64\x39\x36\x14\x74\x07\x14\x73\x07", "xxxxxxxxxxxxxxxxxxxx");
	}

	if (romname == daytona || romname == daytonas || romname == daytonase) //Daytona USA
	{
		aAddy2 = PatternScan("\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x8E\x0E\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\x00\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3F\x42\x3F\x00\x02\x02\x01\x00\x00\x14\x1C\x00\x00\x00\x00\x00", "xxxxxxxxxxx??xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx???x?x?xx?x?xxxx");
	}

	if (romname == indy500 || romname == indy500d || romname == indy500to) //Indy500
	{
		aAddy2 = PatternScan("\x01\xFF\xFF\xFF\x10\x00\xFF\x4E", "xxxx??xx");
	}

	if (romname == sgt24h) //Sega GT 24hr
	{
		aAddy2 = PatternScan("\x03\x00\x00\x00\x09\x00\x00\x00\x1F\x00\x00\x00\x13\x00\x00\x00\x04\x00\x00\x00\x0F", "xxxxxxxxxxxxxxxxxxxxx");
	}

	if (romname == srallyc || romname == srallycb || romname == srallycdx || romname == srallycdxa) //Sega Rally
	{
		aAddy2 = PatternScan("\x01\x04\x00\x00\x80\x3F\xF2\xFF\xFF\xFF\x01\x00\x02\x00\x00\x00\x0B\x00\x01\x00\x01", "xxxxxxxxxxxxxxxxxxxxx");
	}

	if (romname == superchs || romname == superchsj || romname == superchsp || romname == superchsu) //Super Chase Criminal Termination
	{
		aAddy2 = PatternScan("\x80\x38\x00\x50\x49\x5A\x05\x70\x11\x01\x4B\x54\x4F", "xxxxxxxxxxxxx");
	}

	if (romname == dirtdash || romname == dirtdasha || romname == dirtdashj || romname == acedrvrw || romname == acedrive || romname == victlapw || romname == victlap) //Dirt Dash, Ace Driver & Ace Driver Victory Lap
	{
		aAddy2 = PatternScan("\xC8\x00\xC8\x00\xC8\x00\xC8\x00\xC8\x00\xC8\x00\xC8\x00\xC8\x00\x14\x00\x14\x00\x14\x00\x14\x00\x14\x00\x14\x00\x14\x00\x14", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	}

	return 0;
}

static int speedffb(int ffRaw) {
	switch (ffRaw) {
	case 0x1E:
		return 31;
	case 0x1C:
		return 30;
	case 0x1A:
		return 29;
	case 0x18:
		return 28;
	case 0x16:
		return 27;
	case 0x14:
		return 26;
	case 0x12:
		return 25;
	case 0x10:
		return 24;
	case 0x0E:
		return 23;
	case 0x0C:
		return 22;
	case 0x0A:
		return 21;
	case 0x08:
		return 20;
	case 0x06:
		return 19;
	case 0x04:
		return 18;
	case 0x02:
		return 17;

	case 0x1F:
		return 16;
	case 0x1D:
		return 15;
	case 0x1B:
		return 14;
	case 0x19:
		return 13;
	case 0x17:
		return 12;
	case 0x15:
		return 11;
	case 0x13:
		return 10;
	case 0x11:
		return 9;
	case 0x0F:
		return 8;
	case 0x0D:
		return 7;
	case 0x0B:
		return 6;
	case 0x09:
		return 5;
	case 0x07:
		return 4;
	case 0x05:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	}
}

static int raveracer(int ffRaw) {
	switch (ffRaw) {

		//case 0xFE:
			//return 128;
	case 0x7E:
		return 123;
		//case 0xBE:
			//return 126;
	case 0x3E:
		return 122;
	case 0xDE:
		return 121;
	case 0x5E:
		return 120;
	case 0x9E:
		return 119;
	case 0x1E:
		return 118;
	case 0xEE:
		return 117;
	case 0x6E:
		return 116;
	case 0xAE:
		return 115;
	case 0xCE:
		return 114;
	case 0x2E:
		return 113;
	case 0x4E:
		return 112;
	case 0x8E:
		return 111;
	case 0x0E:
		return 110;
	case 0xF6:
		return 109;
	case 0x76:
		return 108;
	case 0xB6:
		return 107;
	case 0x36:
		return 106;
	case 0xD6:
		return 105;
	case 0x56:
		return 104;
	case 0x96:
		return 103;
	case 0x16:
		return 102;
	case 0xE6:
		return 101;
	case 0x66:
		return 100;
	case 0xA6:
		return 99;
	case 0xC6:
		return 98;
	case 0x26:
		return 97;
	case 0x46:
		return 96;
	case 0x86:
		return 95;
	case 0x06:
		return 94;
	case 0xFA:
		return 93;
	case 0x7A:
		return 92;
	case 0xBA:
		return 91;
	case 0x3A:
		return 90;
	case 0xDA:
		return 89;
	case 0x5A:
		return 88;
	case 0x9A:
		return 87;
	case 0x1A:
		return 86;
	case 0xEA:
		return 85;
	case 0x6A:
		return 84;
	case 0xAA:
		return 83;
	case 0xCA:
		return 82;
	case 0x2A:
		return 81;
	case 0x4A:
		return 80;
	case 0x8A:
		return 79;
	case 0x0A:
		return 78;
	case 0xF2:
		return 77;
	case 0x72:
		return 76;
	case 0xB2:
		return 75;
	case 0x32:
		return 74;
	case 0xD2:
		return 73;
	case 0x52:
		return 72;
	case 0x92:
		return 71;
	case 0x12:
		return 70;
	case 0xE2:
		return 69;
	case 0x62:
		return 68;
	case 0xA2:
		return 67;
	case 0xC2:
		return 66;
	case 0x22:
		return 65;
	case 0x42:
		return 64;
	case 0x82:
		return 63;
	case 0x02:
		return 62;


	case 0x80:
		return 61;
	case 0x40:
		return 60;
	case 0x20:
		return 59;
	case 0xC0:
		return 58;
	case 0xA0:
		return 57;
	case 0x60:
		return 56;
	case 0xE0:
		return 55;
	case 0x10:
		return 54;
	case 0x90:
		return 53;
	case 0x50:
		return 52;
	case 0xD0:
		return 51;
	case 0x30:
		return 50;
	case 0xB0:
		return 49;
	case 0x70:
		return 48;
	case 0xF0:
		return 47;
	case 0x08:
		return 46;
	case 0x88:
		return 45;
	case 0x48:
		return 44;
	case 0x28:
		return 43;
	case 0xC8:
		return 42;
	case 0xA8:
		return 41;
	case 0x68:
		return 40;
	case 0xE8:
		return 39;
	case 0x18:
		return 38;
	case 0x98:
		return 37;
	case 0x58:
		return 36;
	case 0xD8:
		return 35;
	case 0x38:
		return 34;
	case 0xB8:
		return 33;
	case 0x78:
		return 32;
	case 0xF8:
		return 31;
	case 0x04:
		return 30;
	case 0x84:
		return 29;
	case 0x44:
		return 28;
	case 0x24:
		return 27;
	case 0xC4:
		return 26;
	case 0xA4:
		return 25;
	case 0x64:
		return 24;
	case 0xE4:
		return 23;
	case 0x14:
		return 22;
	case 0x94:
		return 21;
	case 0x54:
		return 20;
	case 0xD4:
		return 19;
	case 0x34:
		return 18;
	case 0xB4:
		return 17;
	case 0x74:
		return 16;
	case 0xF4:
		return 15;
	case 0x0C:
		return 14;
	case 0x8C:
		return 13;
	case 0x4C:
		return 12;
	case 0x2C:
		return 11;
	case 0xCC:
		return 10;
	case 0xAC:
		return 9;
	case 0x6C:
		return 8;
	case 0xEC:
		return 7;
	case 0x1C:
		return 6;
	case 0x9C:
		return 5;
	case 0x5C:
		return 4;
	case 0xDC:
		return 3;
	case 0x3C:
		return 2;
		//case 0xBC:
			//return 3;
	case 0x7C:
		return 1;
		//case 0xFC:
			//return 1;
	}
}

DWORD WINAPI ThreadForOutputs(LPVOID lpParam)
{
	WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}

DWORD WINAPI ThreadForDaytonaStartEffect(LPVOID lpParam)
{
	Sleep(1300);
	Effect2 = false;
	return 0;
}

void MAMESupermodel::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

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
				joystick_index2 = SDL_JoystickInstanceID(GameController2);
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
				joystick_index3 = SDL_JoystickInstanceID(GameController3);
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

		if (configGameId == 60)
		{
			MH_Initialize();
			MH_CreateHookApi(L"KERNEL32.dll", "ExitProcess", ExitHook, (void**)&ExitOri);
			MH_EnableHook(MH_ALL_HOOKS);
		}
		init = true;
	}

	if (EnableForceSpringEffect)
	{
		triggers->Springi(ForceSpringStrength / 100.0);
	}

	romname = new char[256]; //name of rom being played
	sprintf(romname, "%s", GameName);

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
				EnableDamper = EnableDamperDaytona2;
				DamperStrength = DamperStrengthDaytona2;
				EnableForceSpringEffect = EnableForceSpringEffectDaytona2;
				ForceSpringStrength = ForceSpringStrengthDaytona2;

				RunningFFB = "Daytona2Active";
			}

			if (romname == scud || romname == scuda || romname == scudau || romname == scuddx|| romname == scudj || romname == scudplus || romname == scudplusa)
			{
				configMinForce = configMinForceScud;
				configMaxForce = configMaxForceScud;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftScud;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftScud;
				configAlternativeMinForceRight = configAlternativeMinForceRightScud;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightScud;
				configFeedbackLength = configFeedbackLengthScud;
				PowerMode = PowerModeScud;
				EnableDamper = EnableDamperScud;
				DamperStrength = DamperStrengthScud;
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
				EnableDamper = EnableDamperLeMans;
				DamperStrength = DamperStrengthLeMans;
				EnableForceSpringEffect = EnableForceSpringEffectLeMans;
				ForceSpringStrength = ForceSpringStrengthLeMans;

				RunningFFB = "Daytona2Active";
			}

			if (romname == dirtdvlsa || romname == dirtdvls || romname == dirtdvlsj || romname == dirtdvlsg || romname == dirtdvlsu || romname == dirtdvlsau)
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
				EnableDamper = EnableDamperDirtDevils;
				DamperStrength = DamperStrengthDirtDevils;

				RunningFFB = "DirtDevilsActive";
			}

			if (romname == srally2 || romname == srally2x || romname == srally2dx || romname == srally2p || romname == srally2pa)
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
				EnableDamper = EnableDamperSRally2;
				DamperStrength = DamperStrengthSRally2;

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
				EnableDamper = EnableDamperECA;
				DamperStrength = DamperStrengthECA;

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
				EnableDamper = EnableDamperVirtuaRacing;
				DamperStrength = DamperStrengthVirtuaRacing;

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
				EnableDamper = EnableDamperSFRush;
				DamperStrength = DamperStrengthSFRush;

				RunningFFB = "RacingFullValueActive2";
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
				EnableDamper = EnableDamperSFRushRock;
				DamperStrength = DamperStrengthSFRushRock;

				RunningFFB = "RacingFullValueActive2";
			}

			if (romname == crusnwld || romname == crusnwld24 || romname == crusnwld23 || romname == crusnwld20 || romname == crusnwld19 || romname == crusnwld17)
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
				EnableDamper = EnableDamperCrusnWld;
				DamperStrength = DamperStrengthCrusnWld;

				RunningFFB = "RacingFullValueActive2";
			}

			if (romname == superchs || romname == superchsj || romname == superchsp || romname == superchsu)
			{
				configMinForce = configMinForceSuperChase;
				configMaxForce = configMaxForceSuperChase;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSuperChase;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSuperChase;
				configAlternativeMinForceRight = configAlternativeMinForceRightSuperChase;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSuperChase;
				configFeedbackLength = configFeedbackLengthSuperChase;
				PowerMode = PowerModeSuperChase;
				EnableForceSpringEffect = EnableForceSpringEffectSuperChase;
				ForceSpringStrength = ForceSpringStrengthSuperChase;
				EnableDamper = EnableDamperSuperChase;
				DamperStrength = DamperStrengthSuperChase;

				RunningFFB = "SuperChaseActive";
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
				EnableDamper = EnableDamperOffRoadC;
				DamperStrength = DamperStrengthOffRoadC;

				RunningFFB = "RacingFullValueActive2";
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
				EnableDamper = EnableDamperCrusnUSA;
				DamperStrength = DamperStrengthCrusnUSA;

				RunningFFB = "RacingFullValueActive2";
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
				EnableDamper = EnableDamperCalSpeed;
				DamperStrength = DamperStrengthCalSpeed;

				RunningFFB = "RacingFullValueActive1";
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
				EnableDamper = EnableDamperSFRush2049;
				DamperStrength = DamperStrengthSFRush2049;

				RunningFFB = "RacingFullValueActive1";
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
				EnableDamper = EnableDamperHardD;
				DamperStrength = DamperStrengthHardD;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorORunners;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorORunners;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorTOutrun;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorTOutrun;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorCBombers;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorCBombers;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorOutrun;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorOutrun;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorPDrift;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorPDrift;

				RunningFFB = "PDriftActive";
			}

			if (romname == dblaxle || romname == dblaxleu)
			{
				configMinForce = configMinForceDAxle;
				configMaxForce = configMaxForceDAxle;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftDAxle;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDAxle;
				configAlternativeMinForceRight = configAlternativeMinForceRightDAxle;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightDAxle;
				configFeedbackLength = configFeedbackLengthDAxle;
				EnableForceSpringEffect = EnableForceSpringEffectDAxle;
				ForceSpringStrength = ForceSpringStrengthDAxle;
				SinePeriod = SinePeriodDAxle;
				SineFadePeriod = SineFadePeriodDAxle;
				SineStrength = SineStrengthDAxle;
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorDAxle;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorDAxle;

				RunningFFB = "RacingActive1";
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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorCisHeat;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorCisHeat;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorF1GpStar;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorF1GpStar;

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
				RumbleStrengthLeftMotor = RumbleStrengthLeftMotorF1GpStar2;
				RumbleStrengthRightMotor = RumbleStrengthRightMotorF1GpStar2;

				RunningFFB = "RacingActive2";
			}

			if (romname == hyprdriv)
			{
				configMinForce = configMinForceHyperDrive;
				configMaxForce = configMaxForceHyperDrive;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftHyperDrive;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftHyperDrive;
				configAlternativeMinForceRight = configAlternativeMinForceRightHyperDrive;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightHyperDrive;
				configFeedbackLength = configFeedbackLengthHyperDrive;
				EnableForceSpringEffect = EnableForceSpringEffectHyperDrive;
				ForceSpringStrength = ForceSpringStrengthHyperDrive;
				EnableDamper = EnableDamperHyperDrive;
				DamperStrength = DamperStrengthHyperDrive;
				
				RunningFFB = "RacingFullValueActive1";
			}

			if (romname == vaportrx || romname == vaportrp)
			{
				configMinForce = configMinForceVaporTrx;
				configMaxForce = configMaxForceVaporTrx;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftVaporTrx;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftVaporTrx;
				configAlternativeMinForceRight = configAlternativeMinForceRightVaporTrx;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightVaporTrx;
				configFeedbackLength = configFeedbackLengthVaporTrx;
				EnableForceSpringEffect = EnableForceSpringEffectVaporTrx;
				ForceSpringStrength = ForceSpringStrengthVaporTrx;
				EnableDamper = EnableDamperVaporTrx;
				DamperStrength = DamperStrengthVaporTrx;
				
				RunningFFB = "RacingFullValueActive1";
			}

			if (romname == raveracw || romname == raveracj || romname == raveracja || romname == raverace)
			{
				configMinForce = configMinForceRaveRacer;
				configMaxForce = configMaxForceRaveRacer;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftRaveRacer;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftRaveRacer;
				configAlternativeMinForceRight = configAlternativeMinForceRightRaveRacer;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightRaveRacer;
				configFeedbackLength = configFeedbackLengthRaveRacer;
				PowerMode = PowerModeRaveRacer;
				EnableForceSpringEffect = EnableForceSpringEffectRaveRacer;
				ForceSpringStrength = ForceSpringStrengthRaveRacer;
				EnableDamper = EnableDamperRaveRacer;
				DamperStrength = DamperStrengthRaveRacer;

				RunningFFB = "RaveRacerActive";
			}

			if (romname == daytona || romname == daytonas || romname == daytonase)
			{
				configMinForce = configMinForceDaytonaMAME;
				configMaxForce = configMaxForceDaytonaMAME;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftDaytonaMAME;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDaytonaMAME;
				configAlternativeMinForceRight = configAlternativeMinForceRightDaytonaMAME;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightDaytonaMAME;
				configFeedbackLength = configFeedbackLengthDaytonaMAME;
				PowerMode = PowerModeDaytonaMAME;
				EnableForceSpringEffect = EnableForceSpringEffectDaytonaMAME;
				ForceSpringStrength = ForceSpringStrengthDaytonaMAME;
				EnableDamper = EnableDamperDaytonaMAME;
				DamperStrength = DamperStrengthDaytonaMAME;

				RunningFFB = "M2PatternActive";
			}

			if (romname == indy500 || romname == indy500d || romname == indy500to)
			{
				configMinForce = configMinForceIndy500MAME;
				configMaxForce = configMaxForceIndy500MAME;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftIndy500MAME;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftIndy500MAME;
				configAlternativeMinForceRight = configAlternativeMinForceRightIndy500MAME;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightIndy500MAME;
				configFeedbackLength = configFeedbackLengthIndy500MAME;
				PowerMode = PowerModeIndy500MAME;
				EnableForceSpringEffect = EnableForceSpringEffectIndy500MAME;
				ForceSpringStrength = ForceSpringStrengthIndy500MAME;
				EnableDamper = EnableDamperIndy500MAME;
				DamperStrength = DamperStrengthIndy500MAME;

				RunningFFB = "M2PatternActive";
			}

			if (romname == sgt24h)
			{
				configMinForce = configMinForceSuperGTMAME;
				configMaxForce = configMaxForceSuperGTMAME;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSuperGTMAME;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSuperGTMAME;
				configAlternativeMinForceRight = configAlternativeMinForceRightSuperGTMAME;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSuperGTMAME;
				configFeedbackLength = configFeedbackLengthSuperGTMAME;
				PowerMode = PowerModeSuperGTMAME;
				EnableForceSpringEffect = EnableForceSpringEffectSuperGTMAME;
				ForceSpringStrength = ForceSpringStrengthSuperGTMAME;
				EnableDamper = EnableDamperSuperGTMAME;
				DamperStrength = DamperStrengthSuperGTMAME;

				RunningFFB = "M2PatternActive";
			}

			if (romname == srallyc || romname == srallycb || romname == srallycdx || romname == srallycdxa)
			{
				configMinForce = configMinForceSRallyMAME;
				configMaxForce = configMaxForceSRallyMAME;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftSRallyMAME;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSRallyMAME;
				configAlternativeMinForceRight = configAlternativeMinForceRightSRallyMAME;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightSRallyMAME;
				configFeedbackLength = configFeedbackLengthSRallyMAME;
				PowerMode = PowerModeSRallyMAME;
				EnableForceSpringEffect = EnableForceSpringEffectSRallyMAME;
				ForceSpringStrength = ForceSpringStrengthSRallyMAME;
				EnableDamper = EnableDamperSRallyMAME;
				DamperStrength = DamperStrengthSRallyMAME;

				RunningFFB = "SrallyActive";
			}

			if (romname == dirtdash || romname == dirtdasha || romname == dirtdashj)
			{
				configMinForce = configMinForceDirtDash;
				configMaxForce = configMaxForceDirtDash;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftDirtDash;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDirtDash;
				configAlternativeMinForceRight = configAlternativeMinForceRightDirtDash;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightDirtDash;
				configFeedbackLength = configFeedbackLengthDirtDash;
				PowerMode = PowerModeDirtDash;
				EnableForceSpringEffect = EnableForceSpringEffectDirtDash;
				ForceSpringStrength = ForceSpringStrengthDirtDash;
				Divide = FFBDivideDirtDash * 1.0;
				EnableDamper = EnableDamperDirtDash;
				DamperStrength = DamperStrengthDirtDash;

				RunningFFB = "NamcoFFBActive";
			}

			if (romname == victlapw || romname == victlap)
			{
				configMinForce = configMinForceAceDriverVictory;
				configMaxForce = configMaxForceAceDriverVictory;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftAceDriverVictory;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftAceDriverVictory;
				configAlternativeMinForceRight = configAlternativeMinForceRightAceDriverVictory;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightAceDriverVictory;
				configFeedbackLength = configFeedbackLengthAceDriverVictory;
				PowerMode = PowerModeAceDriverVictory;
				EnableForceSpringEffect = EnableForceSpringEffectAceDriverVictory;
				ForceSpringStrength = ForceSpringStrengthAceDriverVictory;
				Divide = FFBDivideAceDriverVictory * 1.0;
				EnableDamper = EnableDamperAceDriverVictory;
				DamperStrength = DamperStrengthAceDriverVictory;

				RunningFFB = "NamcoFFBActive";
			}

			if (romname == acedrvrw || romname == acedrive)
			{
				configMinForce = configMinForceAceDriver;
				configMaxForce = configMaxForceAceDriver;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftAceDriver;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftAceDriver;
				configAlternativeMinForceRight = configAlternativeMinForceRightAceDriver;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightAceDriver;
				configFeedbackLength = configFeedbackLengthAceDriver;
				PowerMode = PowerModeAceDriver;
				EnableForceSpringEffect = EnableForceSpringEffectAceDriver;
				ForceSpringStrength = ForceSpringStrengthAceDriver;
				Divide = FFBDivideAceDriver * 1.0;
				EnableDamper = EnableDamperAceDriver;
				DamperStrength = DamperStrengthAceDriver;

				RunningFFB = "NamcoFFBActive";
			}

			if (romname == InitialDVer1 || romname == InitialDVer2 || romname == InitialDVer3)
			{
				configMinForce = configMinForceInitialD;
				configMaxForce = configMaxForceInitialD;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftInitialD;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftInitialD;
				configAlternativeMinForceRight = configAlternativeMinForceRightInitialD;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightInitialD;
				configFeedbackLength = configFeedbackLengthInitialD;
				PowerMode = PowerModeInitialD;
				EnableDamper = EnableDamperInitialD;
				DamperStrength = DamperStrengthInitialD;
				EnableForceSpringEffect = EnableForceSpringEffectInitialD;
				ForceSpringStrength = ForceSpringStrengthInitialD;
				DoubleSine = DoubleSineInitialD;
				DoubleConstant = DoubleConstantInitialD;

				RunningFFB = "InitialDActive";
			}

			if (romname == TheKingOfRoute66)
			{
				configMinForce = configMinForceKingOfRoute66;
				configMaxForce = configMaxForceKingOfRoute66;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftKingOfRoute66;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftKingOfRoute66;
				configAlternativeMinForceRight = configAlternativeMinForceRightKingOfRoute66;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightKingOfRoute66;
				configFeedbackLength = configFeedbackLengthKingOfRoute66;
				PowerMode = PowerModeKingOfRoute66;
				EnableDamper = EnableDamperKingOfRoute66;
				DamperStrength = DamperStrengthKingOfRoute66;
				EnableForceSpringEffect = EnableForceSpringEffectKingOfRoute66;
				ForceSpringStrength = ForceSpringStrengthKingOfRoute66;
				DoubleSine = DoubleSineKingOfRoute66;
				DoubleConstant = DoubleConstantKingOfRoute66;

				RunningFFB = "InitialDActive";
			}

			if (romname == ClubKartInJapan)
			{
				configMinForce = configMinForceClubKart;
				configMaxForce = configMaxForceClubKart;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftClubKart;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftClubKart;
				configAlternativeMinForceRight = configAlternativeMinForceRightClubKart;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightClubKart;
				configFeedbackLength = configFeedbackLengthClubKart;
				PowerMode = PowerModeClubKart;
				EnableDamper = EnableDamperClubKart;
				DamperStrength = DamperStrengthClubKart;
				EnableForceSpringEffect = EnableForceSpringEffectClubKart;
				ForceSpringStrength = ForceSpringStrengthClubKart;
				DoubleSine = DoubleSineClubKart;
				DoubleConstant = DoubleConstantClubKart;

				RunningFFB = "InitialDActive";
			}

			if (romname == MaximumSPEED)
			{
				configMinForce = configMinForceMaximumSpeed;
				configMaxForce = configMaxForceMaximumSpeed;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftMaximumSpeed;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftMaximumSpeed;
				configAlternativeMinForceRight = configAlternativeMinForceRightMaximumSpeed;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightMaximumSpeed;
				configFeedbackLength = configFeedbackLengthMaximumSpeed;
				PowerMode = PowerModeMaximumSpeed;
				EnableDamper = EnableDamperMaximumSpeed;
				DamperStrength = DamperStrengthMaximumSpeed;
				EnableForceSpringEffect = EnableForceSpringEffectMaximumSpeed;
				ForceSpringStrength = ForceSpringStrengthMaximumSpeed;

				RunningFFB = "MaximumSpeedActive";
			}

			if (romname == FasterThanSPEED)
			{
				configMinForce = configMinForceFasterThanSpeed;
				configMaxForce = configMaxForceFasterThanSpeed;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftFasterThanSpeed;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftFasterThanSpeed;
				configAlternativeMinForceRight = configAlternativeMinForceRightFasterThanSpeed;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightFasterThanSpeed;
				configFeedbackLength = configFeedbackLengthFasterThanSpeed;
				PowerMode = PowerModeFasterThanSpeed;
				EnableDamper = EnableDamperFasterThanSpeed;
				DamperStrength = DamperStrengthFasterThanSpeed;
				EnableForceSpringEffect = EnableForceSpringEffectFasterThanSpeed;
				ForceSpringStrength = ForceSpringStrengthFasterThanSpeed;

				RunningFFB = "MaximumSpeedActive";
			}

			if (romname == F355ChallengeJapan)
			{
				configMinForce = configMinForceF355;
				configMaxForce = configMaxForceF355;
				configAlternativeMinForceLeft = configAlternativeMinForceLeftF355;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeftF355;
				configAlternativeMinForceRight = configAlternativeMinForceRightF355;
				configAlternativeMaxForceRight = configAlternativeMaxForceRightF355;
				configFeedbackLength = configFeedbackLengthF355;
				PowerMode = PowerModeF355;
				EnableDamper = EnableDamperF355;
				DamperStrength = DamperStrengthF355;
				EnableForceSpringEffect = EnableForceSpringEffectF355;
				ForceSpringStrength = ForceSpringStrengthF355;

				RunningFFB = "NaomiFFBActive";
				NaomiFFBGo = true;
			}

			if (romname == EighteenWheeler)
			{
				configMinForce = configMinForce18Wheeler;
				configMaxForce = configMaxForce18Wheeler;
				configAlternativeMinForceLeft = configAlternativeMinForceLeft18Wheeler;
				configAlternativeMaxForceLeft = configAlternativeMaxForceLeft18Wheeler;
				configAlternativeMinForceRight = configAlternativeMinForceRight18Wheeler;
				configAlternativeMaxForceRight = configAlternativeMaxForceRight18Wheeler;
				configFeedbackLength = configFeedbackLength18Wheeler;
				PowerMode = PowerMode18Wheeler;
				EnableDamper = EnableDamper18Wheeler;
				DamperStrength = DamperStrength18Wheeler;
				EnableForceSpringEffect = EnableForceSpringEffect18Wheeler;
				ForceSpringStrength = ForceSpringStrength18Wheeler;

				RunningFFB = "NaomiFFBActive";
				NaomiFFBGo = true;
			}

			if (enableLogging == 1)
			{
				char romnametext[256];
				sprintf(romnametext, "RomName = %s", romname);
				helpers->log(romnametext);

				char RunningFFBtext[256];
				sprintf(RunningFFBtext, "RunningFFB = %s", RunningFFB);
				helpers->log(RunningFFBtext);
			}

			if ((RunningFFB != NULL) && (RunningFFB[0] != '\0'))
			{
				RomGameName = true;
			}
		}
	}

	if (RomGameName && RunningFFB > 0)
	{
		if (RunningFFB > 0 && EnableDamper)
		{
			triggers->Damper(DamperStrength / 100.0);
		}

		if (RunningFFB == Daytona2Active) //Daytona 2,Scud Race & LeMans
		{
			if (name == RawDrive)
			{
				helpers->log("got value: ");
				std::string ffs = std::to_string(newstateFFB);
				helpers->log((char*)ffs.c_str());

				stateFFB = newstateFFB;
			}

			if ((stateFFB > 0x09) && (stateFFB < 0x20))
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
				triggers->Spring(0);
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

			UINT8 static oldff = 0;
			UINT8 newff = stateFFB;

			if (stateFFB == 0x9C)
			{
				if (oldff != newff)
				{
					Effect1 = true;
				}
			}

			if (Effect1)
			{
				triggers->Sine(100, 0, 0.8);
				Effect1 = false;
			}

			if (stateFFB == 0x05)
			{
				triggers->Sine(40, 0, 0.5);
				triggers->Friction(0.5);
			}

			if (stateFFB == 0x75)
			{
				if (!StartEffectOnce)
				{
					StartEffectOnce = true;
					Effect2 = true;
					CreateThread(NULL, 0, ThreadForDaytonaStartEffect, NULL, 0, NULL);
				}
			}
			else
			{
				if (StartEffectOnce)
				{
					StartEffectOnce = false;
				}
			}

			if (Effect2)
			{
				triggers->Sine(70, 60, 0.5);
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
			oldff = newff;
		}

		if (RunningFFB == DirtDevilsActive) //Dirt Devils
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

		if (RunningFFB == Srally2Active) //Sega Rally 2, Emergency Call Ambulance
		{
			if (name == RawDrive)
			{
				helpers->log("got value: ");
				std::string ffs = std::to_string(newstateFFB);
				helpers->log((char*)ffs.c_str());

				stateFFB = newstateFFB;
			}

			if (stateFFB > 0x00 && stateFFB <= 0x3F)
			{
				double percentForce = (stateFFB) / 64.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if (stateFFB > 0x3F && stateFFB <= 0x7F)
			{
				double percentForce = (stateFFB - 64) / 64.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}

		if (RunningFFB == VirtuaRacingActive) //Virtua Racing
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

			if ((stateFFB == 0x20) || (stateFFB == 0x28))
			{
				//Clutch
				double percentForce = 0.4;
				triggers->Friction(percentForce);
			}

			if ((stateFFB > 0x2F) && (stateFFB < 0x40))
			{
				//Centering
				double percentForce = (stateFFB - 47) / 11.0;
				triggers->Spring(percentForce);
			}

			if ((stateFFB == 0x40) || (stateFFB == 0x46) || (stateFFB == 0x4A))
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

			if ((stateFFB == 0x50) || (stateFFB == 0x5F))
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

		if (RunningFFB == RacingFullValueActive1) //Mame games using all values 
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
				double percentForce = (256 - stateFFB) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((stateFFB > 0x00) && (stateFFB < 0x80))
			{
				double percentForce = (stateFFB) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}

		if (RunningFFB == RacingFullValueActive2) //Mame games using all values (reverse direction to above)
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
				double percentForce = (256 - stateFFB) / 126.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((stateFFB > 0x00) && (stateFFB < 0x80))
			{
				double percentForce = (stateFFB) / 126.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}

		if (RunningFFB == LightGunActive) //LightGun Games
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

		if (RunningFFB == RacingActive1) //Outrunners,Turbo Outrun,CBombers,DAxle
		{
			if (name == MA_Steering_Wheel_motor || name == upright_wheel_motor || name == Vibration_motor || name == Wheel_vibration || name == Wheel_Vibration)
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

		if (RunningFFB == RacingActive2) //Cisco Heat,F1 GpStar //Keep seperate as names is led2 and could possibly interfere with other outputs
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

		if (RunningFFB == AfterburnerActive) //Afterburner
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

		if (RunningFFB == OutrunActive)
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
				if (newstateFFB > 0)
				{

				}

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

		if (RunningFFB == PDriftActive)
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

		if (RunningFFB == MaximumSpeedActive)
		{
			if (name == awffb)
			{
				helpers->log("got value: ");
				std::string ffs = std::to_string(newstateFFB);
				helpers->log((char*)ffs.c_str());

				stateFFB = newstateFFB;
				UINT8 FFB = speedffb(stateFFB);

				if (FFB > 0x00 && FFB < 0x11)
				{
					double percentForce = FFB / 16.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if (FFB > 0x10 && FFB < 0x20)
				{
					double percentForce = (FFB - 16) / 16.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}
		
		if (RunningFFB == NaomiFFBActive)
		{
			if (name == m3ffb)
			{
				helpers->log("got value: ");
				std::string ffs = std::to_string(newstateFFB);
				helpers->log((char*)ffs.c_str());

				if (newstateFFB != 0xD0)
					stateFFB = newstateFFB;

				if (oldstateFFB != stateFFB)
				{
					if ((stateFFB > 0xB0 && stateFFB < 0xC0) || stateFFB == 0x9F)
					{
						SineEffectState = stateFFB;
						Effect1 = true;
					}
				}

				if (stateFFB > 0x10 && stateFFB < 0x20)
				{
					double percentForce = (stateFFB - 10) / 15.0;
					triggers->Springi(percentForce);
				}

				if (stateFFB > 0x20 && stateFFB < 0x30)
				{
					double percentForce = (stateFFB - 32) / 15.0;
					triggers->Friction(percentForce);
				}

				if (stateFFB > 0x30 && stateFFB < 0x40)
				{
					double percentForce = (stateFFB - 48) / 15.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(40, 0, percentForce);
				}

				if (stateFFB > 0x40 && stateFFB < 0x50)
				{
					double percentForce = (stateFFB - 64) / 15.0;

					percentForce = percentForce * 2.0;

					if (percentForce > 1.0)
						percentForce = 1.0;

					triggers->Springi(percentForce);
				}

				if (stateFFB > 0x50 && stateFFB < 0x60)
				{
					double percentForce = (stateFFB - 80) / 15.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (stateFFB > 0x60 && stateFFB < 0x70)
				{
					if (stateFFB != 0x68 && stateFFB != 0x69 && stateFFB != 0x6A && stateFFB != 0x6B)
					{
						double percentForce = (stateFFB - 96) / 15.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
				}

				if (stateFFB > 0x80 && stateFFB < 0x90)
				{
					double percentForce = (stateFFB - 128) / 15.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}

				if (stateFFB == 0x9F)
				{
					double percentForce = 0.4;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (stateFFB > 0xA0 && stateFFB < 0xB0)
				{
					double percentForce = (stateFFB - 160) / 15.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (stateFFB == 0xBF)
				{
					double percentForce = 0.4;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}

				if (stateFFB > 0xD0 && stateFFB < 0xE0)
				{
					double percentForce = (stateFFB - 208) / 15.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (stateFFB > 0xE0 && stateFFB < 0xE9)
				{
					double percentForce = (stateFFB - 224) / 8.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (stateFFB > 0xE8 && stateFFB < 0xF0)
				{
					double percentForce = (stateFFB - 232) / 8.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}

				if (Effect1)
				{
					++EffectCount;

					if (EffectCount >= 31)
					{
						Effect1 = false;
						EffectCount = 0;
					}

					double percentForce = (SineEffectState - 176) / 15.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(60, 0, percentForce);
				}

				if (stateFFB == 0xC0)
				{
					triggers->Rumble(0, 0, 100);
					triggers->Sine(60, 0, 0);
					triggers->Friction(0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
				}
				oldstateFFB = stateFFB;
			}
		}

		if (RunningFFB == InitialDActive)
		{
			if (name == midiffb)
			{
				helpers->log("got value: ");
				std::string ffs = std::to_string(newstateFFB);
				helpers->log((char*)ffs.c_str());

				stateFFB = newstateFFB;

				BYTE* ffb = reinterpret_cast<BYTE*>(&stateFFB);

				if (ffb[2] == 0x80 && ffb[0] == 0x01)
				{
					triggers->Spring(1.0);
				}

				if (ffb[2] == 0x85 && ffb[1] > 0x00 && ffb[0] > 0x00)
				{
					double percentForce = ffb[0] / 127.0;
					double Period = ffb[1] / 127.0 * 120.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, percentForce, percentLength);
					triggers->Sine(static_cast<int>(Period), 0, percentForce);
				}				

				if (ffb[2] == 0x86 && ffb[0] > 0x00 && ffb[0] < 0x80)
				{
					double percentForce = ffb[0] / 127.0;
					double percentLength = 100;
					triggers->Spring(percentForce);
				}

				if (ffb[2] == 0x84 && ffb[0] > 0x00 && ffb[0] < 0x80)
				{
					if (ffb[1] == 0x00)
					{
						double percentForce = (128 - ffb[0]) / 127.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					else if (ffb[1] == 0x01)
					{
						double percentForce = (ffb[0] / 127.0);
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
				}
			}
		}

		if (RunningFFB == RaveRacerActive) //Rave Racer
		{
			if (!PatternFind)
			{
				if (!PatternLaunch)
				{
					if (name == cpuled6)
					{
						if (newstateFFB == 1)
						{
							Sleep(2000);
							PatternLaunch = true;
						}
					}
				}
				else
				{
					if (!Scan)
					{
						CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
						Scan = true;
					}

					UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 - 0xDF, false);
					if (CheckAddy2 == 0xC2)
					{
						FFBAddress = (INT_PTR)aAddy2 - 0x1C0;
						PatternFind = true;
					}
				}
			}
			else
			{
				UINT8 FFB = helpers->ReadByte(FFBAddress, false);
				UINT8 ffrave = raveracer(FFB);

				helpers->log("got value: ");
				std::string ffs = std::to_string(ffrave);
				helpers->log((char*)ffs.c_str());

				if ((ffrave > 0x3D) && (ffrave < 0x7C))
				{
					double percentForce = (124 - ffrave) / 61.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ffrave > 0x00) && (ffrave < 0x3E))
				{
					double percentForce = (ffrave) / 61.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}

		if (RunningFFB == M2PatternActive)
		{
			if (!PatternFind)
			{
				if (!PatternLaunch)
				{
					if (romname == daytona || romname == daytonas || romname == daytonase)
					{
						Sleep(8000);
						PatternLaunch = true;
					}

					if (romname == indy500 || romname == indy500d || romname == indy500to)
					{
						if (name == digit1)
						{
							if (newstateFFB == 0x3D)
							{
								PatternLaunch = true;
							}
						}
					}

					if (romname == sgt24h)
					{
						if (name == digit0)
						{
							if (newstateFFB == 0x01)
							{
								PatternLaunch = true;
							}
						}
					}
				}
				else
				{
					if (romname == daytona || romname == daytonas || romname == daytonase)
					{
						if (!Scan)
						{
							CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
							Scan = true;
						}

						if ((UINT8)aAddy2 == 0x05)
						{
							FFBAddress = (int)aAddy2 + 0x3D;
							PatternFind = true;
						}
					}

					if (romname == indy500 || romname == indy500d || romname == indy500to)
					{
						if (!Scan)
						{
							CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
							Scan = true;
						}
						UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 + 0x04, false);
						if (CheckAddy2 == 0x01)
						{
							FFBAddress = (INT_PTR)aAddy2 + 0x04;
							PatternFind = true;
						}
					}

					if (romname == sgt24h)
					{
						if (!Scan)
						{
							CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
							Scan = true;
						}

						UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 - 0x14, false);
						if (CheckAddy2 == 0x0C)
						{
							FFBAddress = (INT_PTR)aAddy2 + 0x50;
							PatternFind = true;
						}
					}
				}
			}
			else
			{
				ff = helpers->ReadByte(FFBAddress, false);

				helpers->log("got value: ");
				std::string ffs = std::to_string(ff);
				helpers->log((char*)ffs.c_str());

				if ((ff > 0x09) && (ff < 0x18))
				{
					//Spring
					double percentForce = (ff - 15) / 8.0;
					double percentLength = 100;
					triggers->Spring(percentForce);
				}

				if ((ff > 0x1F) && (ff < 0x28))
				{
					//Clutch
					double percentForce = (ff - 31) / 8.0;
					double percentLength = 100;
					triggers->Friction(percentForce);
				}

				if ((ff > 0x2F) && (ff < 0x3D))
				{
					//Centering
					double percentForce = (ff - 47) / 13.0;
					double percentLength = 100;
					triggers->Spring(percentForce);
				}

				if ((ff > 0x3F) && (ff < 0x48))
				{
					//Uncentering
					double percentForce = (ff - 63) / 8.0;
					double percentLength = 100;
					triggers->Sine(40, 0, percentForce);
					triggers->Rumble(percentForce, percentForce, percentLength);
				}

				if ((ff > 0x4F) && (ff < 0x58))
				{
					//Roll Left
					double percentForce = (ff - 79) / 8.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ff > 0x5F) && (ff < 0x68))
				{
					//Roll Right
					double percentForce = (ff - 95) / 8.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == SrallyActive)
		{
			if (!PatternFind)
			{
				if (!PatternLaunch)
				{
					if (name == digit1)
					{
						PatternLaunch = true;
					}
				}
				else
				{
					if (!Scan)
					{
						CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
						Scan = true;
					}

					UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 + 0x35, false);
					if (CheckAddy2 == 0xFF)
					{
						FFBAddress = (INT_PTR)aAddy2 + 0x2B;
						PatternFind = true;
					}
				}
			}
			else
			{
				ff = helpers->ReadByte(FFBAddress, false);

				helpers->log("got value: ");
				std::string ffs = std::to_string(ff);
				helpers->log((char*)ffs.c_str());

				if ((ff > 0xBF) && (ff < 0xDF))
				{
					double percentForce = (ff - 191) / 31.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((ff > 0x7F) && (ff < 0x9F))
				{
					double percentForce = (ff - 127) / 31.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}
		
		if (RunningFFB == SuperChaseActive)
		{
			if (!PatternFind)
			{
				if (!PatternLaunch)
				{
					Sleep(8000);
					PatternLaunch = true;
				}

				if (!Scan)
				{
					CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
					Scan = true;
				}

				UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 + 0x12, false);
				if (CheckAddy2 == 0x5A)
				{
					FFBAddress = (INT_PTR)aAddy2 + 0x6C8;
					PatternFind = true;
				}
			}
			else
			{
				ff = helpers->ReadByte(FFBAddress, false);

				helpers->log("got value: ");
				std::string ffs = std::to_string(ff);
				helpers->log((char*)ffs.c_str());

				if (ff & 0x01)
				{
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}

				if (ff & 0x02)
				{
					double percentForce = 1.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}
		
		if (RunningFFB == NamcoFFBActive)
		{
			if (!PatternFind)
			{
				if (!PatternLaunch)
				{
					if (name == cpuled6)
					{
						if (newstateFFB == 1)
						{
							Sleep(2000);
							PatternLaunch = true;
						}
					}
				}
				else
				{
					if (romname == acedrvrw || romname == acedrive || romname == victlapw || romname == victlap || romname == dirtdash || romname == dirtdasha || romname == dirtdashj)
					{
						if (!Scan)
						{
							CreateThread(NULL, 0, ScanThread, NULL, 0, NULL);
							Scan = true;
						}

						UINT8 CheckAddy2 = helpers->ReadByte((INT_PTR)aAddy2 - 0x3E3, false);
						if (CheckAddy2 == 0x80)
						{
							FFBAddress = (INT_PTR)aAddy2 - 0x2C6;
							PatternFind = true;
						}
					}
				}
			}
			else
			{
				DWORD FFBNamco = helpers->ReadInt32(FFBAddress, false);

				helpers->log("got value: ");
				std::string ffs = std::to_string(FFBNamco);
				helpers->log((char*)ffs.c_str());

				if ((FFBNamco >= 0x00) && (FFBNamco < 0x77A))
				{
					double percentForce = (FFBNamco / Divide);
					double percentLength = 100;
					if (percentForce > 1.0)
					{
						percentForce = 1.0;
					}
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((FFBNamco > 0xF886) && (FFBNamco < 0x10000))
				{
					double percentForce = ((65536 - FFBNamco) / Divide);
					double percentLength = 100;
					if (percentForce > 1.0)
					{
						percentForce = 1.0;
					}
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == HardDrivinActive) //Hard Drivin
		{
			if (!HardDrivinFrame)
			{
				HardDrivinFrame = true;
			}

			//if ((frame & 7) == 4)
			if(frame==4)
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
				

				//helpers->log("got value: ");
				//helpers->log((char*)ffs.c_str());

				//std::string ffs = std::to_string(HardDrivinFFB);
				//std::string val0 = std::to_string(vals[0]);
				//std::string val1 = std::to_string(vals[1]);
				//std::string val2 = std::to_string(vals[2]);
				//std::string val3 = std::to_string(vals[3]);
				//std::string val4 = std::to_string(vals[4]);
				//static char moreTest[256];
				//memset(moreTest, 0, 256);
				//sprintf(moreTest, "vals=%s %s %s %s FFS=%s", val0.c_str(), val1.c_str(), val2.c_str(), val3.c_str(), ffs.c_str());
				//helpers->log((char*)moreTest);

				if (HardDrivinFFB > 100) {
					HardDrivinFFB = 100;
				}

				if (HardDrivinFFB < -100) {
					HardDrivinFFB = -100;
				}

				if (HardDrivinFFB >= 0)
					{
					double percentForce = HardDrivinFFB / 100.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				} 
				else if (HardDrivinFFB < 0)
				{
					HardDrivinFFB = -HardDrivinFFB;
					double percentForce = HardDrivinFFB / 100.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				} 
			}
		}
	}
}
#include <Windows.h>

extern int configGameId;
extern int configMinForce;
extern int configMaxForce;
extern int AlternativeFFB;
extern int configAlternativeMinForceLeft;
extern int configAlternativeMaxForceLeft;
extern int configAlternativeMinForceRight;
extern int configAlternativeMaxForceRight;
extern char* romname;
extern char* romnameM2;
extern char* romnameDemul;
extern LPCSTR CustomAlternativeMaxForceLeft;
extern LPCSTR CustomAlternativeMaxForceRight;
extern LPCSTR CustomMaxForce;
extern int EnableFFBStrengthPersistence;

int defaultMaxForce;
int defaultAlternativeMaxForceLeft;
int defaultAlternativeMaxForceRight;

//Demul Emulator Games
static std::string Nascar("Nascar");
static std::string InitialDArcadeStage("Initial D Arcade Stage");
static std::string SmashingDrive("Smashing Drive");
static std::string MaximumSpeed("Maximum Speed");
static std::string FasterThanSpeed("Faster Than Speed");
static std::string ATVTrack("ATV Track");

//M2 Emulator Games
static std::string SegaRallyChampionship("Sega Rally Championship");
static std::string SegaRallyChampionshipRevB("Sega Rally Championship (Rev B)");
static std::string SegaRallyProDrivin("Sega Rally Pro Drivin'");
static std::string DaytonaUSA("Daytona USA");
static std::string DaytonaUSA93Edition("Daytona USA '93 Edition");
static std::string DaytonaUSASaturnAds("Daytona USA (Saturn Ads)");
static std::string DaytonaUSASpecialEdition("Daytona USA Special Edition");
static std::string DaytonaUSATurbo("Daytona USA Turbo");
static std::string DaytonaUSATurboRevA("Daytona USA Turbo (Rev A)");
static std::string DaytonaUSAGTX2004("Daytona USA: GTX 2004");
static std::string DaytonaUSAToTheMaxx("Daytona USA: To The Maxx");
static std::string Indianapolis500RevADeluxe("Indianapolis 500 (Rev A, Deluxe)");
static std::string Indianapolis500RevATwinNewerrev("Indianapolis 500 (Rev A, Twin, Newer rev)");
static std::string Indianapolis500RevATwinOlderrev("Indianapolis 500 (Rev A, Twin, Older rev)");
static std::string OverRev("Over Rev");
static std::string OverRevModel2B("Over Rev (Model 2B)");
static std::string SuperGT24h("Super GT 24h");
static std::string SegaTouringCarChampionship("Sega Touring Car Championship");
static std::string SegaTouringCarChampionshipRevA("Sega Touring Car Championship (Rev A)");
static std::string SegaTouringCarChampionshipRevB("Sega Touring Car Championship (Rev B)");

//Supermodel Emulator Games
static std::string dayto2pe("dayto2pe");
static std::string daytona2("daytona2");
static std::string dirtdvlsa("dirtdvlsa");
static std::string dirtdvls("dirtdvls");
static std::string dirtdvlsj("dirtdvlsj");
static std::string dirtdvlsg("dirtdvlsg");
static std::string ecau("ecau");
static std::string eca("eca");
static std::string ecap("ecap");
static std::string ecaj("ecaj");
static std::string lemans24("lemans24");
static std::string scud("scud");
static std::string scuda("scuda");
static std::string scudj("scudj");
static std::string scudplus("scudplus");
static std::string scudplusa("scudplusa");
static std::string srally2("srally2");
static std::string srally2x("srally2x");
static std::string srally2p("srally2p");
static std::string srally2pa("srally2pa");

//MAME Games
static std::string aburner2("aburner2");
static std::string aburner2g("aburner2g");
static std::string acedrvrw("acedrvrw");
static std::string vformula("vformula");
static std::string vr("vr");
static std::string sfrush("sfrush");
static std::string sfrushrk("sfrushrk");
static std::string sfrushrkwo("sfrushrkwo");
static std::string sfrusha("sfrusha");
static std::string crusnwld("crusnwld");
static std::string crusnwld24("crusnwld24");
static std::string crusnwld23("crusnwld23");
static std::string crusnwld20("crusnwld20");
static std::string crusnwld19("crusnwld19");
static std::string crusnwld17("crusnwld17");
static std::string crusnwld13("crusnwld13");
static std::string daytona("daytona");
static std::string daytonas("daytonas");
static std::string daytonase("daytonase");
static std::string dirtdash("dirtdash");
static std::string offroadc("offroadc");
static std::string offroadc4("offroadc4");
static std::string offroadc3("offroadc3");
static std::string offroadc1("offroadc1");
static std::string crusnusa("crusnusa");
static std::string crusnusa40("crusnusa40");
static std::string crusnusa21("crusnusa21");
static std::string calspeed("calspeed");
static std::string calspeeda("calspeeda");
static std::string calspeedb("calspeedb");
static std::string indy500("indy500");
static std::string indy500d("indy500d");
static std::string indy500to("indy500to");
static std::string outrunra("outrunra");
static std::string outrun("outrun");
static std::string outruneh("outruneh");
static std::string toutrun("toutrun");
static std::string toutrund("toutrund");
static std::string toutrunj("toutrunj");
static std::string toutrunjd("toutrunjd");
static std::string pdrift("pdrift");
static std::string pdrifta("pdrifta");
static std::string pdrifte("pdrifte");
static std::string pdriftj("pdriftj");
static std::string pdriftl("pdriftl");
static std::string orunners("orunners");
static std::string orunnersu("orunnersu");
static std::string orunnersj("orunnersj");
static std::string sf2049("sf2049");
static std::string sf2049se("sf2049se");
static std::string sf2049te("sf2049te");
static std::string harddriv("harddriv");
static std::string harddriv1("harddriv1");
static std::string harddrivb6("harddrivb6");
static std::string harddrivb("harddrivb");
static std::string harddrivg4("harddrivg4");
static std::string harddrivg("harddrivg");
static std::string harddrivj6("harddrivj6");
static std::string harddrivj("harddrivj");
static std::string harddriv2("harddriv2");
static std::string harddriv3("harddriv3");
static std::string harddrivcb("harddrivcb");
static std::string harddrivcg("harddrivcg");
static std::string harddrivc1("harddrivc1");
static std::string harddrivc("harddrivc");
static std::string hdrivairp("hdrivairp");
static std::string hdrivair("hdrivair");
static std::string racedrivb1("racedrivb1");
static std::string racedrivb4("racedrivb4");
static std::string racedrivb("racedrivb");
static std::string racedrivg1("racedrivg1");
static std::string racedrivg4("racedrivg4");
static std::string racedrivg("racedrivg");
static std::string racedriv1("racedriv1");
static std::string racedriv2("racedriv2");
static std::string racedriv3("racedriv3");
static std::string racedriv4("racedriv4");
static std::string racedriv("racedriv");
static std::string racedrivcb4("racedrivcb4");
static std::string racedrivcb("racedrivcb");
static std::string racedrivcg4("racedrivcg4");
static std::string racedrivcg("racedrivcg");
static std::string racedrivc2("racedrivc2");
static std::string racedrivc4("racedrivc4");
static std::string racedrivc("racedrivc");
static std::string racedrivpan("racedrivpan");
static std::string raveracw("raveracw");
static std::string raveracj("raveracj");
static std::string raveracja("raveracja");
static std::string othunder("othunder");
static std::string othundero("othundero");
static std::string othunderuo("othunderuo");
static std::string othunderu("othunderu");
static std::string othunderj("othunderj");
static std::string opwolf("opwolf");
static std::string opwolfp("opwolfp");
static std::string opwolfj("opwolfj");
static std::string opwolfu("opwolfu");
static std::string opwolfa("opwolfa");
static std::string revx("revx");
static std::string revxp5("revxp5");
static std::string term2("term2");
static std::string term2la1("term2la1");
static std::string term2pa2("term2pa2");
static std::string term2la2("term2la2");
static std::string term2la3("term2la3");
static std::string term2lg1("term2lg1");
static std::string zombraid("zombraid");
static std::string zombraidpj("zombraidpj");
static std::string zombraidp("zombraidp");
static std::string bbusters("bbusters");
static std::string bbustersu("bbustersu");
static std::string bbustersua("bbustersua");
static std::string bbustersj("bbustersj");
static std::string mechatt("mechatt");
static std::string mechattu("mechattu");
static std::string mechattu1("mechattu1");
static std::string mechattj("mechattj");
static std::string tshoot("tshoot");
static std::string gunbustru("gunbustru");
static std::string gunbustr("gunbustr");
static std::string gunbustrj("gunbustrj");
static std::string alien3("alien3");
static std::string alien3u("alien3u");
static std::string ptblank2("ptblank2");
static std::string ptblank2ua("ptblank2ua");
static std::string ghlpanic("ghlpanic");
static std::string sgt24h("sgt24h");
static std::string srallyc("srallyc");
static std::string srallycb("srallycb");
static std::string srallycdxa("srallycdxa");
static std::string srallycdx("srallycdx");
static std::string spacegun("spacegun");
static std::string spacegunu("spacegunu");
static std::string spacegunj("spacegunj");
static std::string superchs("superchs");
static std::string superchsp("superchsp");
static std::string superchsj("superchsj");
static std::string superchsu("superchsu");
static std::string stcc("stcc");
static std::string stcca("stcca");
static std::string stccb("stccb");
static std::string rchase("rchase");
static std::string rchasej("rchasej");
static std::string lghost("lghost");
static std::string lghostd("lghostd");
static std::string lghostu("lghostu");
static std::string lghostud("lghostud");
static std::string lghostj("lghostj");
static std::string timecris("timecris");
static std::string timecrisa("timecrisa");
static std::string cischeat("cischeat");
static std::string f1gpstar("f1gpstar");
static std::string f1gpstaro("f1gpstaro");
static std::string f1gpstr2("f1gpstr2");
static std::string undrfire("undrfire");
static std::string undrfireu("undrfireu");
static std::string undrfirej("undrfirej");
static std::string cbombers("cbombers");
static std::string cbombersj("cbombersj");
static std::string cbombersp("cbombersp");
static std::string hyprdriv("hyprdriv");
static std::string vaportrx("vaportrx");
static std::string vaportrp("vaportrp");
static std::string victlapw("victlapw");

void DefaultConfigValues()
{
	if (EnableFFBStrengthPersistence == 1)
	{
		if (configGameId == 1)
		{
			configMinForce = 0;
			configMaxForce = 90;
			configAlternativeMinForceLeft = 0;
			configAlternativeMaxForceLeft = -90;
			configAlternativeMinForceRight = 0;
			configAlternativeMaxForceRight = 90;
		}
		else if ((configGameId == 2) || (configGameId == 3) || (configGameId == 29))
		{
			configMinForce = 0;
			configMaxForce = 75;
			configAlternativeMinForceLeft = 0;
			configAlternativeMaxForceLeft = -75;
			configAlternativeMinForceRight = 0;
			configAlternativeMaxForceRight = 75;
		}
		else if (configGameId == 22)
		{
			if (romname == superchs || romname == superchsj || romname == superchsp || romname == superchsu)
			{
				configMinForce = 0;
				configMaxForce = 80;
				configAlternativeMinForceLeft = 0;
				configAlternativeMaxForceLeft = -80;
				configAlternativeMinForceRight = 0;
				configAlternativeMaxForceRight = 80;
			}
			else
			{
				configMinForce = 0;
				configMaxForce = 100;
				configAlternativeMinForceLeft = 0;
				configAlternativeMaxForceLeft = -100;
				configAlternativeMinForceRight = 0;
				configAlternativeMaxForceRight = 100;
			}
		}
		else
		{
			configMinForce = 0;
			configMaxForce = 100;
			configAlternativeMinForceLeft = 0;
			configAlternativeMaxForceLeft = -100;
			configAlternativeMinForceRight = 0;
			configAlternativeMaxForceRight = 100;
		}
	}
	else
	{
		configMaxForce = defaultMaxForce;
		configAlternativeMaxForceLeft = defaultAlternativeMaxForceLeft;
		configAlternativeMaxForceRight = defaultAlternativeMaxForceRight;
	}
}

void CustomFFBStrengthSetup()
{
	defaultMaxForce = configMaxForce;
	defaultAlternativeMaxForceLeft = configAlternativeMaxForceLeft;
	defaultAlternativeMaxForceRight = configAlternativeMaxForceRight;

	if (configGameId == 34)
	{
		if (romname == dayto2pe || romname == daytona2)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftDaytona2";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightDaytona2";
			}
			else
			{
				CustomMaxForce = "MaxForceDaytona2";
			}
		}

		if (romname == scud || romname == scuda || romname == scudj || romname == scudplus || romname == scudplusa)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftScud";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightScud";
			}
			else
			{
				CustomMaxForce = "MaxForceScud";
			}
		}

		if (romname == lemans24)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftLeMans";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightLeMans";
			}
			else
			{
				CustomMaxForce = "MaxForceLeMans";
			}
		}

		if (romname == dirtdvlsa || romname == dirtdvls || romname == dirtdvlsj || romname == dirtdvlsg)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftDirtDevils";
				CustomAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightDirtDevils";
			}
			else
			{
				CustomMaxForce = "MaxForceDirtDevils";
			}
		}

		if (romname == srally2 || romname == srally2x || romname == srally2p || romname == srally2pa)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSRally2";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSRally2";
			}
			else
			{
				CustomMaxForce = "MaxForceSRally2";
			}
		}

		if (romname == ecau || romname == eca || romname == ecap || romname == ecaj)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftECA";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightECA";
			}
			else
			{
				CustomMaxForce = "MaxForceECA";
			}
		}
	}
	else if (configGameId == 22)
	{
		if (romname == vr)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftVirtuaRacing";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightVirtuaRacing";
			}
			else
			{
				CustomMaxForce = "MaxForceVirtuaRacing";
			}
		}

		if (romname == sfrush || romname == sfrusha)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSFRush";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSFRush";
			}
			else
			{
				CustomMaxForce = "MaxForceSFRush";
			}
		}

		if (romname == sfrushrk || romname == sfrushrkwo)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSFRushRock";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSFRushRock";
			}
			else
			{
				CustomMaxForce = "MaxForceSFRushRock";
			}
		}

		if (romname == crusnwld || romname == crusnwld24 || romname == crusnwld23 || romname == crusnwld20 || romname == crusnwld19 || romname == crusnwld17)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftCrusnWld";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightCrusnWld";
			}
			else
			{
				CustomMaxForce = "MaxForceCrusnWld";
			}
		}

		if (romname == superchs || romname == superchsj || romname == superchsp || romname == superchsu)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSuperChase";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSuperChase";
			}
			else
			{
				CustomMaxForce = "MaxForceSuperChase";
			}
		}

		if (romname == offroadc || romname == offroadc4 || romname == offroadc3 || romname == offroadc1)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftOffRoadC";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightOffRoadC";
			}
			else
			{
				CustomMaxForce = "MaxForceOffRoadC";
			}
		}

		if (romname == crusnusa || romname == crusnusa40 || romname == crusnusa21)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftCrusnUSA";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightCrusnUSA";
			}
			else
			{
				CustomMaxForce = "MaxForceCrusnUSA";
			}
		}

		if (romname == calspeed || romname == calspeeda || romname == calspeedb)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftCalSpeed";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightCalSpeed";
			}
			else
			{
				CustomMaxForce = "MaxForceCalSpeed";
			}
		}

		if (romname == sf2049 || romname == sf2049se || romname == sf2049te)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSFRush2049";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSFRush2049";
			}
			else
			{
				CustomMaxForce = "MaxForceSFRush2049";
			}
		}

		if (romname == harddriv1 || romname == harddrivb6 || romname == harddrivb || romname == harddrivg4 || romname == harddrivg || romname == harddrivj6 || romname == harddrivj ||
			romname == harddriv2 || romname == harddriv3 || romname == harddriv || romname == harddrivcb || romname == harddrivcg || romname == harddrivc1 || romname == harddrivc ||
			romname == hdrivairp || romname == hdrivair || romname == racedrivb1 || romname == racedrivb4 || romname == racedrivb || romname == racedrivg1 || romname == racedrivg4 ||
			romname == racedrivg || romname == racedriv1 || romname == racedriv2 || romname == racedriv3 || romname == racedriv4 || romname == racedriv || romname == racedrivcb4 ||
			romname == racedrivcb || romname == racedrivcg4 || romname == racedrivcg || romname == racedrivc2 || romname == racedrivc4 || romname == racedrivc || romname == racedrivpan)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftHardD";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightHardD";
			}
			else
			{
				CustomMaxForce = "MaxForceHardD";
			}
		}

		if (romname == orunners || romname == orunnersu || romname == orunnersj)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftORunners";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightORunners";
			}
			else
			{
				CustomMaxForce = "MaxForceORunners";
			}
		}

		if (romname == toutrun || romname == toutrund || romname == toutrunj || romname == toutrunjd)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftTOutrun";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightTOutrun";
			}
			else
			{
				CustomMaxForce = "MaxForceTOutrun";
			}
		}

		if (romname == cbombers || romname == cbombersj || romname == cbombersp)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftCBombers";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightCBombers";
			}
			else
			{
				CustomMaxForce = "MaxForceCBombers";
			}
		}

		if (romname == outrunra || romname == outrun || romname == outruneh)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftOutrun";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightOutrun";
			}
			else
			{
				CustomMaxForce = "MaxForceOutrun";
			}
		}

		if (romname == pdrift || romname == pdrifta || romname == pdrifte || romname == pdriftj || romname == pdriftl)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftPDrift";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightPDrift";
			}
			else
			{
				CustomMaxForce = "MaxForcePDrift";
			}
		}

		if (romname == cischeat)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftCisHeat";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightCisHeat";
			}
			else
			{
				CustomMaxForce = "MaxForceCisHeat";
			}
		}

		if (romname == f1gpstar || romname == f1gpstaro)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftF1GpStar";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightF1GpStar";
			}
			else
			{
				CustomMaxForce = "MaxForceF1GpStar";
			}
		}

		if (romname == f1gpstr2)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftF1GpStar2";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightF1GpStar2";
			}
			else
			{
				CustomMaxForce = "MaxForceF1GpStar2";
			}
		}

		if (romname == hyprdriv)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftHyperDrive";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightHyperDrive";
			}
			else
			{
				CustomMaxForce = "MaxForceHyperDrive";
			}
		}

		if (romname == vaportrx || romname == vaportrp)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftVaporTrx";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightVaporTrx";
			}
			else
			{
				CustomMaxForce = "MaxForceVaporTrx";
			}
		}

		if (romname == raveracw || romname == raveracj || romname == raveracja)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "PersistentMaxForceLeftRaveRacer";
				CustomAlternativeMaxForceRight = "PersistentMaxForceRightRaveRacer";
			}
			else
			{
				CustomMaxForce = "MaxForceRaveRacer";
			}
		}

		if (romname == daytona || romname == daytonas || romname == daytonase)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftDaytona";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightDaytona";
			}
			else
			{
				CustomMaxForce = "MaxForceDaytona";
			}
		}

		if (romname == indy500 || romname == indy500d || romname == indy500to)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftIndy500";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightIndy500";
			}
			else
			{
				CustomMaxForce = "MaxForceIndy500";
			}
		}

		if (romname == sgt24h)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSuperGT";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSuperGT";
			}
			else
			{
				CustomMaxForce = "MaxForceSuperGT";
			}
		}

		if (romname == srallyc || romname == srallycb || romname == srallycdx || romname == srallycdxa)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSRally";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSRally";
			}
			else
			{
				CustomMaxForce = "MaxForceSRally";
			}
		}

		if (romname == dirtdash)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftDirtDash";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightDirtDash";
			}
			else
			{
				CustomMaxForce = "MaxForceDirtDash";
			}
		}

		if (romname == victlapw)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftAceDriverVictory";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightAceDriverVictory";
			}
			else
			{
				CustomMaxForce = "MaxForceAceDriverVictory";
			}
		}

		if (romname == acedrvrw)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftAceDriver";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightAceDriver";
			}
			else
			{
				CustomMaxForce = "MaxForceAceDriver";
			}
		}
	}
	else if (configGameId == 25)
	{
		if (romnameM2 == DaytonaUSA || romnameM2 == DaytonaUSA93Edition || romnameM2 == DaytonaUSASaturnAds || romnameM2 == DaytonaUSASpecialEdition || romnameM2 == DaytonaUSATurbo || romnameM2 == DaytonaUSATurboRevA || romnameM2 == DaytonaUSAGTX2004 || romnameM2 == DaytonaUSAToTheMaxx)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftDaytona";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightDaytona";
			}
			else
			{
				CustomMaxForce = "MaxForceDaytona";
			}
		}

		if (romnameM2 == SegaRallyChampionship || romnameM2 == SegaRallyChampionshipRevB || romnameM2 == SegaRallyProDrivin)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSRally";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSRally";
			}
			else
			{
				CustomMaxForce = "MaxForceSRally";
			}
		}

		if (romnameM2 == Indianapolis500RevADeluxe || romnameM2 == Indianapolis500RevATwinNewerrev || romnameM2 == Indianapolis500RevATwinOlderrev)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftIndy500";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightIndy500";
			}
			else
			{
				CustomMaxForce = "MaxForceIndy500";
			}
		}

		if (romnameM2 == SegaTouringCarChampionship || romnameM2 == SegaTouringCarChampionshipRevA || romnameM2 == SegaTouringCarChampionshipRevB)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSTCC";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSTCC";
			}
			else
			{
				CustomMaxForce = "MaxForceSTCC";
			}
		}

		if (romnameM2 == OverRev || romnameM2 == OverRevModel2B)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftOverRev";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightOverRev";
			}
			else
			{
				CustomMaxForce = "MaxForceOverRev";
			}
		}

		if (romnameM2 == SuperGT24h)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSuperGT";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSuperGT";
			}
			else
			{
				CustomMaxForce = "MaxForceSuperGT";
			}
		}
	}
	else if (configGameId == 26)
	{
		if (romnameDemul == Nascar)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftNascarRacing";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightNascarRacing";
			}
			else
			{
				CustomMaxForce = "MaxForceNascarRacing";
			}
		}

		if (romnameDemul == InitialDArcadeStage)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftInitialDDemul";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightInitialDDemul";
			}
			else
			{
				CustomMaxForce = "MaxForceInitialDDemul";
			}
		}

		if (romnameDemul == SmashingDrive)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftSmashingDrive";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightSmashingDrive";
			}
			else
			{
				CustomMaxForce = "MaxForceSmashingDrive";
			}
		}

		if (romnameDemul == MaximumSpeed)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftMaximumSpeed";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightMaximumSpeed";
			}
			else
			{
				CustomMaxForce = "MaxForceMaximumSpeed";
			}
		}

		if (romnameDemul == FasterThanSpeed)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftFasterSpeed";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightFasterSpeed";
			}
			else
			{
				CustomMaxForce = "MaxForceFasterSpeed";
			}
		}

		if (romnameDemul == ATVTrack)
		{
			if (AlternativeFFB == 1)
			{
				CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeftATVTrack";
				CustomAlternativeMaxForceRight = "AlternativeMaxForceRightATVTrack";
			}
			else
			{
				CustomMaxForce = "MaxForceATVTrack";
			}
		}
	}
	else
	{
		if (AlternativeFFB == 1)
		{
			CustomAlternativeMaxForceLeft = "AlternativeMaxForceLeft";
			CustomAlternativeMaxForceRight = "AlternativeMaxForceRight";
		}
		else
		{
			CustomMaxForce = "MaxForce";
		}
	}	
}
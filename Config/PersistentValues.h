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
extern LPCSTR CustomPersistentAlternativeMaxForceLeft;
extern LPCSTR CustomPersistentAlternativeMaxForceRight;
extern LPCSTR CustomPersistentMaxForce;

extern int PersistentMaxForce;
extern int PersistentAlternativeMaxForceLeft;
extern int PersistentAlternativeMaxForceRight;
extern int PersistentMaxForceDaytona2;
extern int PersistentAlternativeMaxForceLeftDaytona2;
extern int PersistentAlternativeMaxForceRightDaytona2;
extern int PersistentMaxForceScud;
extern int PersistentAlternativeMaxForceLeftScud;
extern int PersistentAlternativeMaxForceRightScud;
extern int PersistentMaxForceLeMans;
extern int PersistentAlternativeMaxForceLeftLeMans;
extern int PersistentAlternativeMaxForceRightLeMans;
extern int PersistentMaxForceDirtDevils;
extern int PersistentAlternativeMaxForceLeftDirtDevils;
extern int PersistentAlternativeMaxForceRightDirtDevils;
extern int PersistentMaxForceSRally2;
extern int PersistentAlternativeMaxForceLeftSRally2;
extern int PersistentAlternativeMaxForceRightSRally2;
extern int PersistentMaxForceECA;
extern int PersistentAlternativeMaxForceLeftECA;
extern int PersistentAlternativeMaxForceRightECA;
extern int PersistentMaxForceVirtuaRacing;
extern int PersistentAlternativeMaxForceLeftVirtuaRacing;
extern int PersistentAlternativeMaxForceRightVirtuaRacing;
extern int PersistentMaxForceSFRush;
extern int PersistentAlternativeMaxForceLeftSFRush;
extern int PersistentAlternativeMaxForceRightSFRush;
extern int PersistentMaxForceSFRushRock;
extern int PersistentAlternativeMaxForceLeftSFRushRock;
extern int PersistentAlternativeMaxForceRightSFRushRock;
extern int PersistentMaxForceCrusnWld;
extern int PersistentAlternativeMaxForceLeftCrusnWld;
extern int PersistentAlternativeMaxForceRightCrusnWld;
extern int PersistentMaxForceOffRoadC;
extern int PersistentAlternativeMaxForceLeftOffRoadC;
extern int PersistentAlternativeMaxForceRightOffRoadC;
extern int PersistentMaxForceCrusnUSA;
extern int PersistentAlternativeMaxForceLeftCrusnUSA;
extern int PersistentAlternativeMaxForceRightCrusnUSA;
extern int PersistentMaxForceCalSpeed;
extern int PersistentAlternativeMaxForceLeftCalSpeed;
extern int PersistentAlternativeMaxForceRightCalSpeed;
extern int PersistentMaxForceSFRush2049;
extern int PersistentAlternativeMaxForceLeftSFRush2049;
extern int PersistentAlternativeMaxForceRightSFRush2049;
extern int PersistentMaxForceHardD;
extern int PersistentAlternativeMaxForceLeftHardD;
extern int PersistentAlternativeMaxForceRightHardD;
extern int PersistentMaxForceORunners;
extern int PersistentAlternativeMaxForceLeftORunners;
extern int PersistentAlternativeMaxForceRightORunners;
extern int PersistentMaxForceTOutrun;
extern int PersistentAlternativeMaxForceLeftTOutrun;
extern int PersistentAlternativeMaxForceRightTOutrun;
extern int PersistentMaxForceCBombers;
extern int PersistentAlternativeMaxForceLeftCBombers;
extern int PersistentAlternativeMaxForceRightCBombers;
extern int PersistentMaxForceOutrun;
extern int PersistentAlternativeMaxForceLeftOutrun;
extern int PersistentAlternativeMaxForceRightOutrun;
extern int PersistentMaxForcePDrift;
extern int PersistentAlternativeMaxForceLeftPDrift;
extern int PersistentAlternativeMaxForceRightPDrift;
extern int PersistentMaxForceCisHeat;
extern int PersistentAlternativeMaxForceLeftCisHeat;
extern int PersistentAlternativeMaxForceRightCisHeat;
extern int PersistentMaxForceF1GpStar;
extern int PersistentAlternativeMaxForceLeftF1GpStar;
extern int PersistentAlternativeMaxForceRightF1GpStar;
extern int PersistentMaxForceF1GpStar2;
extern int PersistentAlternativeMaxForceLeftF1GpStar2;
extern int PersistentAlternativeMaxForceRightF1GpStar2;
extern int PersistentMaxForceHyperDrive;
extern int PersistentAlternativeMaxForceLeftHyperDrive;
extern int PersistentAlternativeMaxForceRightHyperDrive;
extern int PersistentMaxForceVaporTrx;
extern int PersistentAlternativeMaxForceLeftVaporTrx;
extern int PersistentAlternativeMaxForceRightVaporTrx;
extern int PersistentMaxForceRaveRacer;
extern int PersistentAlternativeMaxForceLeftRaveRacer;
extern int PersistentAlternativeMaxForceRightRaveRacer;
extern int PersistentMaxForceDaytonaMAME;
extern int PersistentAlternativeMaxForceLeftDaytonaMAME;
extern int PersistentAlternativeMaxForceRightDaytonaMAME;
extern int PersistentMaxForceSRallyMAME;
extern int PersistentAlternativeMaxForceLeftSRallyMAME;
extern int PersistentAlternativeMaxForceRightSRallyMAME;
extern int PersistentMaxForceIndy500MAME;
extern int PersistentAlternativeMaxForceLeftIndy500MAME;
extern int PersistentAlternativeMaxForceRightIndy500MAME;
extern int PersistentMaxForceSuperGTMAME;
extern int PersistentAlternativeMaxForceLeftSuperGTMAME;
extern int PersistentAlternativeMaxForceRightSuperGTMAME;
extern int PersistentMaxForceSuperChase;
extern int PersistentAlternativeMaxForceLeftSuperChase;
extern int PersistentAlternativeMaxForceRightSuperChase;
extern int PersistentMaxForceDirtDash;
extern int PersistentAlternativeMaxForceLeftDirtDash;
extern int PersistentAlternativeMaxForceRightDirtDash;
extern int PersistentMaxForceAceDriverVictory;
extern int PersistentAlternativeMaxForceLeftAceDriverVictory;
extern int PersistentAlternativeMaxForceRightAceDriverVictory;
extern int PersistentMaxForceAceDriver;
extern int PersistentAlternativeMaxForceLeftAceDriver;
extern int PersistentAlternativeMaxForceRightAceDriver;

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

void LoadPersistentSetup()
{
	if (configGameId == 34)
	{
		if (romname == dayto2pe || romname == daytona2)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftDaytona2";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightDaytona2";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftDaytona2;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightDaytona2;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceDaytona2";
				configMaxForce = PersistentMaxForceDaytona2;
			}
		}

		if (romname == scud || romname == scuda || romname == scudj || romname == scudplus || romname == scudplusa)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftScud";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightScud";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftScud;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightScud;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceScud";
				configMaxForce = PersistentMaxForceScud;
			}
		}

		if (romname == lemans24)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftLeMans";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightLeMans";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftLeMans;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightLeMans;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceLeMans";
				configMaxForce = PersistentMaxForceLeMans;
			}
		}

		if (romname == dirtdvlsa || romname == dirtdvls || romname == dirtdvlsj || romname == dirtdvlsg)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftDirtDevils";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightDirtDevils";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftDirtDevils;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightDirtDevils;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceDirtDevils";
				configMaxForce = PersistentMaxForceDirtDevils;
			}
		}

		if (romname == srally2 || romname == srally2x || romname == srally2p || romname == srally2pa)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSRally2";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSRally2";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSRally2;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSRally2;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSRally2";
				configMaxForce = PersistentMaxForceSRally2;
			}
		}

		if (romname == ecau || romname == eca || romname == ecap || romname == ecaj)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftECA";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightECA";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftECA;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightECA;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceECA";
				configMaxForce = PersistentMaxForceECA;
			}
		}
	}
	else if (configGameId == 22)
	{
		if (romname == vr)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftVirtuaRacing";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightVirtuaRacing";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftVirtuaRacing;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightVirtuaRacing;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceVirtuaRacing";
				configMaxForce = PersistentMaxForceVirtuaRacing;
			}
		}

		if (romname == sfrush || romname == sfrusha)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSFRush";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSFRush";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSFRush;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSFRush;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSFRush";
				configMaxForce = PersistentMaxForceSFRush;
			}
		}

		if (romname == sfrushrk || romname == sfrushrkwo)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSFRushRock";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSFRushRock";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSFRushRock;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSFRushRock;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSFRushRock";
				configMaxForce = PersistentMaxForceSFRushRock;
			}
		}

		if (romname == crusnwld || romname == crusnwld24 || romname == crusnwld23 || romname == crusnwld20 || romname == crusnwld19 || romname == crusnwld17)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftCrusnWld";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightCrusnWld";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftCrusnWld;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightCrusnWld;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceCrusnWld";
				configMaxForce = PersistentMaxForceCrusnWld;
			}
		}

		if (romname == superchs || romname == superchsj || romname == superchsp || romname == superchsu)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSuperChase";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSuperChase";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSuperChase;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSuperChase;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSuperChase";
				configMaxForce = PersistentMaxForceSuperChase;
			}
		}

		if (romname == offroadc || romname == offroadc4 || romname == offroadc3 || romname == offroadc1)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftOffRoadC";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightOffRoadC";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftOffRoadC;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightOffRoadC;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceOffRoadC";
				configMaxForce = PersistentMaxForceOffRoadC;
			}
		}

		if (romname == crusnusa || romname == crusnusa40 || romname == crusnusa21)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftCrusnUSA";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightCrusnUSA";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftCrusnUSA;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightCrusnUSA;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceCrusnUSA";
				configMaxForce = PersistentMaxForceCrusnUSA;
			}
		}

		if (romname == calspeed || romname == calspeeda || romname == calspeedb)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftCalSpeed";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightCalSpeed";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftCalSpeed;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightCalSpeed;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceCalSpeed";
				configMaxForce = PersistentMaxForceCalSpeed;
			}
		}

		if (romname == sf2049 || romname == sf2049se || romname == sf2049te)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSFRush2049";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSFRush2049";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSFRush2049;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSFRush2049;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSFRush2049";
				configMaxForce = PersistentMaxForceSFRush2049;
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
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftHardD";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightHardD";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftHardD;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightHardD;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceHardD";
				configMaxForce = PersistentMaxForceHardD;
			}
		}

		if (romname == orunners || romname == orunnersu || romname == orunnersj)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftORunners";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightORunners";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftORunners;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightORunners;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceORunners";
				configMaxForce = PersistentMaxForceORunners;
			}
		}

		if (romname == toutrun || romname == toutrund || romname == toutrunj || romname == toutrunjd)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftTOutrun";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightTOutrun";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftTOutrun;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightTOutrun;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceTOutrun";
				configMaxForce = PersistentMaxForceTOutrun;
			}
		}

		if (romname == cbombers || romname == cbombersj || romname == cbombersp)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftCBombers";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightCBombers";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftCBombers;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightCBombers;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceCBombers";
				configMaxForce = PersistentMaxForceCBombers;
			}
		}

		if (romname == outrunra || romname == outrun || romname == outruneh)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftOutrun";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightOutrun";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftOutrun;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightOutrun;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceOutrun";
				configMaxForce = PersistentMaxForceOutrun;
			}
		}

		if (romname == pdrift || romname == pdrifta || romname == pdrifte || romname == pdriftj || romname == pdriftl)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftPDrift";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightPDrift";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftPDrift;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightPDrift;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForcePDrift";
				configMaxForce = PersistentMaxForcePDrift;
			}
		}

		if (romname == cischeat)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftCisHeat";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightCisHeat";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftCisHeat;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightCisHeat;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceCisHeat";
				configMaxForce = PersistentMaxForceCisHeat;
			}
		}

		if (romname == f1gpstar || romname == f1gpstaro)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftF1GpStar";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightF1GpStar";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftF1GpStar;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightF1GpStar;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceF1GpStar";
				configMaxForce = PersistentMaxForceF1GpStar;
			}
		}

		if (romname == f1gpstr2)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftF1GpStar2";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightF1GpStar2";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftF1GpStar2;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightF1GpStar2;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceF1GpStar2";
				configMaxForce = PersistentMaxForceF1GpStar2;
			}
		}

		if (romname == hyprdriv)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftHyperDrive";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightHyperDrive";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftHyperDrive;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightHyperDrive;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceHyperDrive";
				configMaxForce = PersistentMaxForceHyperDrive;
			}
		}

		if (romname == vaportrx || romname == vaportrp)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftVaporTrx";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightVaporTrx";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftVaporTrx;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightVaporTrx;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceVaporTrx";
				configMaxForce = PersistentMaxForceVaporTrx;
			}
		}

		if (romname == raveracw || romname == raveracj || romname == raveracja)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftRaveRacer";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightRaveRacer";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftRaveRacer;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightRaveRacer;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceRaveRacer";
				configMaxForce = PersistentMaxForceRaveRacer;
			}
		}

		if (romname == daytona || romname == daytonas || romname == daytonase)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftDaytona";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightDaytona";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftDaytonaMAME;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightDaytonaMAME;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceDaytona";
				configMaxForce = PersistentMaxForceDaytonaMAME;
			}
		}

		if (romname == indy500 || romname == indy500d || romname == indy500to)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftIndy500";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightIndy500";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftIndy500MAME;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightIndy500MAME;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceIndy500";
				configMaxForce = PersistentMaxForceIndy500MAME;
			}
		}

		if (romname == sgt24h)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSuperGT";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSuperGT";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSuperGTMAME;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSuperGTMAME;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSuperGT";
				configMaxForce = PersistentMaxForceSuperGTMAME;
			}
		}

		if (romname == srallyc || romname == srallycb || romname == srallycdx || romname == srallycdxa)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftSRally";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightSRally";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftSRallyMAME;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightSRallyMAME;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceSRally";
				configMaxForce = PersistentMaxForceSRallyMAME;
			}
		}

		if (romname == dirtdash)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftDirtDash";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightDirtDash";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftDirtDash;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightDirtDash;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceDirtDash";
				configMaxForce = PersistentMaxForceDirtDash;
			}
		}

		if (romname == victlapw)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftAceDriverVictory";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightAceDriverVictory";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftAceDriverVictory;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightAceDriverVictory;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceAceDriverVictory";
				configMaxForce = PersistentMaxForceAceDriverVictory;
			}
		}

		if (romname == acedrvrw)
		{
			if (AlternativeFFB == 1)
			{
				CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeftAceDriver";
				CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRightAceDriver";
				configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeftAceDriver;
				configAlternativeMaxForceRight = PersistentAlternativeMaxForceRightAceDriver;
			}
			else
			{
				CustomPersistentMaxForce = "PersistentMaxForceAceDriver";
				configMaxForce = PersistentMaxForceAceDriver;
			}
		}
	}
	else
	{
		if (AlternativeFFB == 1)
		{
			CustomPersistentAlternativeMaxForceLeft = "PersistentAlternativeMaxForceLeft";
			CustomPersistentAlternativeMaxForceRight = "PersistentAlternativeMaxForceRight";
			configAlternativeMaxForceLeft = PersistentAlternativeMaxForceLeft;
			configAlternativeMaxForceRight = PersistentAlternativeMaxForceRight;
		}
		else
		{
			CustomPersistentMaxForce = "PersistentMaxForce";
			configMaxForce = PersistentMaxForce;
		}
	}	
}
#pragma once
#include <list>
#include <string>
#include <map>

using namespace std;
using std::map;

class CurrentWeapons {
public:
	std::string weapon1 = "";
	std::string weapon2 = "";
	int modBitFieldCurrentWeapon1 = 0;
	int modBitFieldCurrentWeapon2 = 0;
};

class IWeaponAttachments
{
public:
	virtual ~IWeaponAttachments() = default;

	bool purpleStock = false;
	bool blueStock = false;
	bool whiteStock = false;
	bool canHaveStock = false;
	bool isSniperStock = false;

	bool fourXtenScope = false;
	bool fourXeightScope = false;
	bool sixXScope = false;
	bool canHaveSniperScope = false;

	bool twoXfourScope = false;
	bool threeXScope = false;
	bool canHaveTwoXFourScope = false;
	bool canHaveThreeXScope = false;

	bool oneXtwoScope = false;
	bool oneHoloScope = false;
	bool twoXScope = false;
	bool oneHOKVScope = false;
	bool digitalScope = false;
	bool canHaveDigitalScope = false;

	bool goldMag = false;
	bool purpleMag = false;
	bool blueMag = false;
	bool whiteMag = false;
	bool canHaveMag = false;

	bool purpleStabi = false;
	bool blueStabi = false;
	bool whiteStabi = false;
	bool canHaveStabi = false;

	// Hop up
	bool deadEyesTempo = false;
	bool canHaveDeadEyesTempo = false; // Bocek, Sentinel
	bool hammerpoint = false;
	bool canHaveHammerpoint = false; // RE-45, P2020, Mosambique
	bool boostedLoader = false;
	bool canHaveBoostedLoader = false; // Wingman, Hemlok
	bool shatterCaps = false;
	// Dual Shell ODER Shatter Caps bei 30-30
	bool canHaveShatterCaps = false; // Bocek, 30-30
	bool dualShell = false;
	bool canHaveDualShell = false; // 30-30, Mastiff
	bool kineticFeeder = false;
	bool canHaveKineticFeeder = false; // Peacekeeper, Triple Take
	bool turboCharger = false;
	bool canHaveTurboCharger = false; // Devotion, Havoc
	bool canHaveAttachments = false;

	bool canHaveArrow = false;
	bool canHaveEnergyAmmo = false;
	bool canHaveLightAmmo = false;
	bool canHaveHeavyAmmo = false;
	bool canHaveShotgunAmmo = false;
	bool canHaveSniperAmmo = false;
private:
};

class IWeaponAttachmentValues
{
public:
	virtual ~IWeaponAttachmentValues() = default;

	int purpleStandardStock = 0;
	int blueStandardStock = 0;
	int whiteStandardStock = 0;

	int goldExtendedMag = 0;
	int purpleExtendedMag = 0;
	int blueExtendedMag = 0;
	int whiteExtendedMag = 0;

	int purpleStabilizer = 0;
	int blueStabilizer = 0;
	int whiteStabilizer = 0;

	int goldFourXten = 0;
	int purpleFourXeight = 0;
	int blueSixX = 0;
	int purpleTwoXfour = 0;
	int purpleThreeX = 0;
	int blueOneXtwo = 0;
	int whiteOneHolo = 0;
	int blueTwoX = 0;
	int whiteOneHOKV = 0;
	int goldDigitalScope = 0;

	int purpleDeadEyesTempo = 0;
	int purpleHammerpoint = 0;
	int goldBoostedLoader = 0;
	int purpleShatterCaps = 0;
	int purpleDualShell = 0;
	int purpleKineticFeeder = 0;
	int goldTurboCharger = 0;

	int standardValue = 0;

	map<int, string> listStandardStock = { };
	map<int, string> listExtendedMag = { };
	map<int, string> listStabilizer = { };
	map<int, string> listScope = { };
	map<int, string> listAttachments = { };
};

class LongbowAttachments : public IWeaponAttachments {
	public:
		LongbowAttachments() {
			 purpleStock = false;
			 blueStock = false;
			 whiteStock = false;
			 canHaveStock = true;
			 isSniperStock = true;

			 fourXtenScope = false;
			 fourXeightScope = false;
			 sixXScope = false;
			 canHaveSniperScope = true;

			 twoXfourScope = false;
			 threeXScope = false;
			 canHaveTwoXFourScope = true;
			 canHaveThreeXScope = true;

			 oneXtwoScope = false;
			 oneHoloScope = false;
			 twoXScope = false;
			 oneHOKVScope = false;
			 digitalScope = false;
			 canHaveDigitalScope = false;

			 goldMag = false;
			 purpleMag = false;
			 blueMag = false;
			 whiteMag = false;
			 canHaveMag = true;

			 purpleStabi = false;
			 blueStabi = false;
			 whiteStabi = false;
			 canHaveStabi = true;

			 deadEyesTempo = false;
			 canHaveDeadEyesTempo = false; // Bocek, Sentinel
			 hammerpoint = false;
			 canHaveHammerpoint = false; // RE-45, P2020, Mosambique
			 boostedLoader = false;
			 canHaveBoostedLoader = false; // Wingman, Hemlok
			 shatterCaps = false;
			 // Dual Shell ODER Shatter Caps bei 30-30
			 canHaveShatterCaps = false; // Bocek, 30-30
			 dualShell = false;
			 canHaveDualShell = false; // 30-30, Mastiff
			 kineticFeeder = false;
			 canHaveKineticFeeder = false; // Peacekeeper, Triple Take
			 turboCharger = false;
			 canHaveTurboCharger = false; // Devotion, Havoc

			 canHaveSniperAmmo = true;
		};

		LongbowAttachments(IWeaponAttachments attachment) {
			purpleStock = attachment.purpleStock;
			blueStock = attachment.blueStock;
			whiteStock = attachment.whiteStock;
			canHaveStock = attachment.canHaveStock;
			isSniperStock = attachment.isSniperStock;

			fourXtenScope = attachment.fourXtenScope;
			fourXeightScope = attachment.fourXeightScope;
			sixXScope = attachment.sixXScope;
			canHaveSniperScope = attachment.canHaveSniperScope;

			twoXfourScope = attachment.twoXfourScope;
			threeXScope = attachment.threeXScope;
			canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
			canHaveThreeXScope = attachment.canHaveThreeXScope;

			oneXtwoScope = attachment.oneXtwoScope;
			oneHoloScope = attachment.oneHoloScope;
			twoXScope = attachment.twoXScope;
			oneHOKVScope = attachment.oneHOKVScope;
			digitalScope = attachment.digitalScope;
			canHaveDigitalScope = attachment.canHaveDigitalScope;

			goldMag = attachment.goldMag;
			purpleMag = attachment.purpleMag;
			blueMag = attachment.blueMag;
			whiteMag = attachment.whiteMag;
			canHaveMag = attachment.canHaveMag;

			purpleStabi = attachment.purpleStabi;
			blueStabi = attachment.blueStabi;
			whiteStabi = attachment.whiteStabi;
			canHaveStabi = attachment.canHaveStabi;

			deadEyesTempo = attachment.deadEyesTempo;
			canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
			hammerpoint = attachment.hammerpoint;
			canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
			boostedLoader = attachment.boostedLoader;
			canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
			shatterCaps = attachment.shatterCaps;
			// Dual Shell ODER Shatter Caps bei 30-30
			canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
			dualShell = attachment.dualShell;
			canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
			kineticFeeder = attachment.kineticFeeder;
			canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
			turboCharger = attachment.turboCharger;
			canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

			canHaveSniperAmmo = attachment.canHaveSniperAmmo;
		};

		
	private:
};

class LongbowAttachmentValues : public IWeaponAttachmentValues {
public:
	LongbowAttachmentValues() {
		 purpleStandardStock = 536870912;
		 blueStandardStock = 268435456;
		 whiteStandardStock = 134217728;

		 goldExtendedMag = 4096;
		 purpleExtendedMag = 2048;
		 blueExtendedMag = 1024;
		 whiteExtendedMag = 512;

		 purpleStabilizer = 67108864;
		 blueStabilizer = 33554432;
		 whiteStabilizer = 16777216;

		 goldFourXten = 256;
		 purpleFourXeight = 128;
		 blueSixX = 64;
		 purpleTwoXfour = 8388608;
		 purpleThreeX = 4194304;
		 blueOneXtwo = 2097152;
		 whiteOneHolo = 1048576;
		 blueTwoX = 524288;
		 whiteOneHOKV = 262144;

		 purpleDeadEyesTempo = 0;
		 purpleHammerpoint = 0;
		 goldBoostedLoader = 0;
		 purpleShatterCaps = 0;
		 purpleDualShell = 0;
		 purpleKineticFeeder = 0;
		 goldTurboCharger = 0;

		listStandardStock = {
			{536870912, "purpleStandardStock",},
			{268435456, "blueStandardStock",},
			{134217728, "whiteStandardStock",}
		};

		listExtendedMag = {
			{4096, "goldExtendedMag",},
			{2048, "purpleExtendedMag",},
			{1024, "blueExtendedMag",},
			{512, "whiteExtendedMag",},
		};
		listStabilizer = {
			{67108864, "purpleStabilizer",},
			{33554432, "blueStabilizer",},
			{16777216, "whiteStabilizer",},
		};

		listScope = {
			{256, "goldFourXten",},
			{128, "purpleFourXeight",},
			{64, "blueSixX",},
			{8388608, "purpleTwoXfour",},
			{4194304, "purpleThreeX",},
			{2097152, "blueOneXtwo",},
			{1048576, "whiteOneHolo",},
			{524288, "blueTwoX",},
			{262144, "whiteOneHOKV",},
		};

		listAttachments = {};
	}

	LongbowAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class ChargeRifleAttachments : public IWeaponAttachments {
public:
	ChargeRifleAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = true;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = true;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveSniperAmmo = true;
	};

	ChargeRifleAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;
		isSniperStock = attachment.isSniperStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveSniperAmmo = attachment.canHaveSniperAmmo;
	};


private:
};

class ChargeRifleAttachmentValues : public IWeaponAttachmentValues {
public:
	ChargeRifleAttachmentValues() {
		purpleStandardStock = 524288;
		blueStandardStock = 262144;
		whiteStandardStock = 131072;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 65536;
		purpleFourXeight = 32768;
		blueSixX = 16384;
		purpleTwoXfour = 8192;
		purpleThreeX = 4096;
		blueOneXtwo = 2048;
		whiteOneHolo = 1024;
		blueTwoX = 512;
		whiteOneHOKV = 256;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;

		listStandardStock = {
			{524288, "purpleStandardStock",},
			{262144, "blueStandardStock",},
			{131072, "whiteStandardStock",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = { 
			{0, ""}
		};

		listScope = {
			{65536, "goldFourXten",},
			{32768, "purpleFourXeight",},
			{16384, "blueSixX",},
			{8192, "purpleTwoXfour",},
			{4096, "purpleThreeX",},
			{2048, "blueOneXtwo",},
			{1024, "whiteOneHolo",},
			{512, "blueTwoX",},
			{256, "whiteOneHOKV",},
		};

		listAttachments = {};
	}

	ChargeRifleAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class SentinelAttachments : public IWeaponAttachments {
public:
	SentinelAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = true;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = true;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = true; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc
		canHaveAttachments = true;

		canHaveSniperAmmo = true;
	};

	SentinelAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;
		isSniperStock = attachment.isSniperStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveSniperAmmo = attachment.canHaveSniperAmmo;
	};


private:
};

class SentinelAttachmentValues : public IWeaponAttachmentValues {
public:
	SentinelAttachmentValues() {
		purpleStandardStock = 67108864;
		blueStandardStock = 33554432;
		whiteStandardStock = 16777216;

		goldExtendedMag = 1048576;
		purpleExtendedMag = 524288;
		blueExtendedMag = 262144;
		whiteExtendedMag = 131072;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 1024;
		purpleFourXeight = 512;
		blueSixX = 256;
		purpleTwoXfour = 32768;
		purpleThreeX = 65536;
		blueOneXtwo = 16384;
		whiteOneHolo = 8192;
		blueTwoX = 2048;
		whiteOneHOKV = 4096;

		purpleDeadEyesTempo = 16;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;

		listStandardStock = {
			{67108864, "purpleStandardStock",},
			{33554432, "blueStandardStock",},
			{16777216, "whiteStandardStock",}
		};

		listExtendedMag = {
			{1048576, "goldExtendedMag"},
			{524288, "purpleExtendedMag"},
			{262144, "blueExtendedMag"},
			{131072, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{1024, "goldFourXten",},
			{512, "purpleFourXeight",},
			{256, "blueSixX",},
			{32768, "purpleTwoXfour",},
			{65536, "purpleThreeX",},
			{16384, "blueOneXtwo",},
			{8192, "whiteOneHolo",},
			{2048, "blueTwoX",},
			{4096, "whiteOneHOKV",},
		};

		listAttachments = {
			{16, "purpleDeadEyesTempo"}
		};
	}

	SentinelAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class AlternatorAttachments : public IWeaponAttachments {
public:
	AlternatorAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = true;
	};

	AlternatorAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
	};


private:
};

class AlternatorAttachmentValues : public IWeaponAttachmentValues {
public:
	AlternatorAttachmentValues() {
		purpleStandardStock = 8388608;
		blueStandardStock = 4194304;
		whiteStandardStock = 2097152;

		goldExtendedMag = 8192;
		purpleExtendedMag = 4096;
		blueExtendedMag = 2048;
		whiteExtendedMag = 1024;

		purpleStabilizer = 65536;
		blueStabilizer = 32768;
		whiteStabilizer = 16384;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 256;
		whiteOneHolo = 128;
		blueTwoX = 64;
		whiteOneHOKV = 32;
		goldDigitalScope = 512;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;

		listStandardStock = {
			{8388608, "purpleStandardStock",},
			{4194304, "blueStandardStock",},
			{2097152, "whiteStandardStock",}
		};

		listExtendedMag = {
			{8192, "goldExtendedMag"},
			{4096, "purpleExtendedMag"},
			{2048, "blueExtendedMag"},
			{1024, "whiteExtendedMag"}
		};

		listStabilizer = {
			{65536, "purpleStabilizer"},
			{32768, "blueStabilizer"},
			{16384, "whiteStabilizer"}
		};

		listScope = {
			{256, "blueOneXtwo",},
			{128, "whiteOneHolo",},
			{64, "blueTwoX",},
			{32, "whiteOneHOKV",},
			{512, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	AlternatorAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class R99Attachments : public IWeaponAttachments {
public:
	R99Attachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = true;
	};

	R99Attachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
	};


private:
};

class R99AttachmentValues : public IWeaponAttachmentValues {
public:
	R99AttachmentValues() {
		purpleStandardStock = 8388608;
		blueStandardStock = 4194304;
		whiteStandardStock = 2097152;

		goldExtendedMag = 16384;
		purpleExtendedMag = 8192;
		blueExtendedMag = 4096;
		whiteExtendedMag = 2048;

		purpleStabilizer = 268435456;
		blueStabilizer = 134217728;
		whiteStabilizer = 67108864;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 512;
		whiteOneHolo = 256;
		blueTwoX = 128;
		whiteOneHOKV = 64;
		goldDigitalScope = 1024;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;

		listStandardStock = {
			{8388608, "purpleStandardStock",},
			{4194304, "blueStandardStock",},
			{2097152, "whiteStandardStock",}
		};

		listExtendedMag = {
			{16384, "goldExtendedMag"},
			{8192, "purpleExtendedMag"},
			{4096, "blueExtendedMag"},
			{2048, "whiteExtendedMag"}
		};

		listStabilizer = {
			{268435456, "purpleStabilizer"},
			{134217728, "blueStabilizer"},
			{67108864, "whiteStabilizer"}
		};

		listScope = {
			{512, "blueOneXtwo",},
			{256, "whiteOneHolo",},
			{128, "blueTwoX",},
			{64, "whiteOneHOKV",},
			{1024, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	R99AttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class R301Attachments : public IWeaponAttachments {
public:
	R301Attachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = true;
	};

	R301Attachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
	};


private:
};

class R301AttachmentValues : public IWeaponAttachmentValues {
public:
	R301AttachmentValues() {
		purpleStandardStock = 4194304;
		blueStandardStock = 2097152;
		whiteStandardStock = 1048576;

		goldExtendedMag = 4096;
		purpleExtendedMag = 2048;
		blueExtendedMag = 1024;
		whiteExtendedMag = 512;

		purpleStabilizer = 134217728;
		blueStabilizer = 67108864;
		whiteStabilizer = 33554432;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 524288;
		purpleThreeX = 262144;
		blueOneXtwo = 131072;
		whiteOneHolo = 65536;
		blueTwoX = 32768;
		whiteOneHOKV = 16384;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;

		listStandardStock = {
			{4194304, "purpleStandardStock",},
			{2097152, "blueStandardStock",},
			{1048576, "whiteStandardStock",}
		};

		listExtendedMag = {
			{4096, "goldExtendedMag"},
			{2048, "purpleExtendedMag"},
			{1024, "blueExtendedMag"},
			{512, "whiteExtendedMag"}
		};

		listStabilizer = {
			{134217728, "purpleStabilizer"},
			{67108864, "blueStabilizer"},
			{33554432, "whiteStabilizer"}
		};

		listScope = {
			{131072, "blueOneXtwo",},
			{65536, "whiteOneHolo",},
			{32768, "blueTwoX",},
			{16384, "whiteOneHOKV",},
			{524288, "purpleTwoXfour"},
			{262144, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	R301AttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;
	}
};

class P2020Attachments : public IWeaponAttachments {
public:
	P2020Attachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = true; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = true;
	};

	P2020Attachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
	};


private:
};

class P2020AttachmentValues : public IWeaponAttachmentValues {
public:
	P2020AttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 32768;
		purpleExtendedMag = 16384;
		blueExtendedMag = 8192;
		whiteExtendedMag = 4096;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 1024;
		whiteOneHolo = 512;
		blueTwoX = 256;
		whiteOneHOKV = 2048;
		goldDigitalScope = 2048;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 64;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{32768, "goldExtendedMag"},
			{16384, "purpleExtendedMag"},
			{8192, "blueExtendedMag"},
			{4096, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{1024, "blueOneXtwo",},
			{512, "whiteOneHolo",},
			{256, "blueTwoX",},
			{128, "whiteOneHOKV",},
			{2048, "goldDigitalScope"}
		};

		listAttachments = {
			{64, "purpleHammerpoint"}
		};
	}

	P2020AttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class RE45Attachments : public IWeaponAttachments {
public:
	RE45Attachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = true; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = true;
	};

	RE45Attachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
	};


private:
};

class RE45AttachmentValues : public IWeaponAttachmentValues {
public:
	RE45AttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 4096;
		purpleExtendedMag = 2048;
		blueExtendedMag = 1024;
		whiteExtendedMag = 512;

		purpleStabilizer = 8388608;
		blueStabilizer = 4194304;
		whiteStabilizer = 2097152;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 262144;
		whiteOneHolo = 131072;
		blueTwoX = 65536;
		whiteOneHOKV = 32768;
		goldDigitalScope = 256;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 128;

		listStandardStock = {
			{0, ""}
		};

		listExtendedMag = {
			{4096, "goldExtendedMag"},
			{2048, "purpleExtendedMag"},
			{1024, "blueExtendedMag"},
			{512, "whiteExtendedMag"}
		};

		listStabilizer = {
			{8388608, "purpleStabi",},
			{4194304, "blueStabilizer"},
			{2097152, "whiteStabilizer"}
		};

		listScope = {
			{262144, "blueOneXtwo",},
			{131072, "whiteOneHolo",},
			{65536, "blueTwoX",},
			{32768, "whiteOneHOKV",},
			{256, "goldDigitalScope"}
		};

		listAttachments = {
			{128, "purpleHammerpoint"}
		};
	}

	RE45AttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class FlatlineAttachments : public IWeaponAttachments {
public:
	FlatlineAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	FlatlineAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class FlatlineAttachmentValues : public IWeaponAttachmentValues {
public:
	FlatlineAttachmentValues() {
		purpleStandardStock = 4194304;
		blueStandardStock = 2097152;
		whiteStandardStock = 1048576;

		goldExtendedMag = 4096;
		purpleExtendedMag = 2048;
		blueExtendedMag = 1024;
		whiteExtendedMag = 512;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 524288;
		purpleThreeX = 262144;
		blueOneXtwo = 131072;
		whiteOneHolo = 65536;
		blueTwoX = 32768;
		whiteOneHOKV = 16384;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{4194304, "purpleStandardStock",},
			{2097152, "blueStandardStock"},
			{1048576, "whiteStandardStock"}
		};

		listExtendedMag = {
			{4096, "goldExtendedMag"},
			{2048, "purpleExtendedMag"},
			{1024, "blueExtendedMag"},
			{512, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{131072, "blueOneXtwo",},
			{65536, "whiteOneHolo",},
			{32768, "blueTwoX",},
			{16384, "whiteOneHOKV",},
			{524288, "purpleTwoXfour"},
			{262144, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	FlatlineAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class HemlokAttachments : public IWeaponAttachments {
public:
	HemlokAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = true; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	HemlokAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class HemlokAttachmentValues : public IWeaponAttachmentValues {
public:
	HemlokAttachmentValues() {
		purpleStandardStock = 33554432;
		blueStandardStock = 16777216;
		whiteStandardStock = 8388608;

		goldExtendedMag = 16384;
		purpleExtendedMag = 8192;
		blueExtendedMag = 4096;
		whiteExtendedMag = 2048;

		purpleStabilizer = 1073741824;
		blueStabilizer = 536870912;
		whiteStabilizer = 268435456;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 4194304;
		purpleThreeX = 0;
		blueOneXtwo = 1048576;
		whiteOneHolo = 524288;
		blueTwoX = 262144;
		whiteOneHOKV = 131072;
		goldDigitalScope = 2097152;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 64;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{33554432, "purpleStandardStock",},
			{16777216, "blueStandardStock"},
			{8388608, "whiteStandardStock"}
		};

		listExtendedMag = {
			{16384, "goldExtendedMag"},
			{8192, "purpleExtendedMag"},
			{4096, "blueExtendedMag"},
			{2048, "whiteExtendedMag"}
		};

		listStabilizer = {
			{1073741824, "purpleStabilizer"},
			{536870912, "blueStabilizer"},
			{268435456, "whiteStabilizer"}
		};

		listScope = {
			{1048576, "blueOneXtwo",},
			{524288, "whiteOneHolo",},
			{262144, "blueTwoX",},
			{131072, "whiteOneHOKV",},
			{4194304, "purpleTwoXfour"},
			{2097152, "purpleThreeX"}
		};

		listAttachments = {
			{64, "goldBoostedLoader"}
		};
	}

	HemlokAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class ProwlerAttachments : public IWeaponAttachments {
public:
	ProwlerAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	ProwlerAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class ProwlerAttachmentValues : public IWeaponAttachmentValues {
public:
	ProwlerAttachmentValues() {
		purpleStandardStock = 1048576;
		blueStandardStock = 524288;
		whiteStandardStock = 262144;

		goldExtendedMag = 16384;
		purpleExtendedMag = 8192;
		blueExtendedMag = 4096;
		whiteExtendedMag = 2048;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 512;
		whiteOneHolo = 256;
		blueTwoX = 128;
		whiteOneHOKV = 64;
		goldDigitalScope = 1024;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 64;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{1048576, "purpleStandardStock",},
			{524288, "blueStandardStock"},
			{262144, "whiteStandardStock"}
		};

		listExtendedMag = {
			{16384, "goldExtendedMag"},
			{8192, "purpleExtendedMag"},
			{4096, "blueExtendedMag"},
			{2048, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{512, "blueOneXtwo",},
			{256, "whiteOneHolo",},
			{128, "blueTwoX",},
			{64, "whiteOneHOKV",},
			{1024, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	ProwlerAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class WingmanAttachments : public IWeaponAttachments {
public:
	WingmanAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = true; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	WingmanAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class WingmanAttachmentValues : public IWeaponAttachmentValues {
public:
	WingmanAttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 8192;
		purpleExtendedMag = 4096;
		blueExtendedMag = 2048;
		whiteExtendedMag = 1024;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 1048576;
		whiteOneHolo = 524288;
		blueTwoX = 262144;
		whiteOneHOKV = 131072;
		goldDigitalScope = 2097152;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 64;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{8192, "goldExtendedMag"},
			{4096, "purpleExtendedMag"},
			{2048, "blueExtendedMag"},
			{1024, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{1048576, "blueOneXtwo",},
			{524288, "whiteOneHolo",},
			{262144, "blueTwoX",},
			{131072, "whiteOneHOKV",},
			{2097152, "goldDigitalScope"}
		};

		listAttachments = {
			{64, "goldBoostedLoader"}
		};
	}

	WingmanAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class ThirtyThirtyAttachments : public IWeaponAttachments {
public:
	ThirtyThirtyAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = true;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = true; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = true; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	ThirtyThirtyAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;
		isSniperStock = attachment.isSniperStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class ThirtyThirtyAttachmentValues : public IWeaponAttachmentValues {
public:
	ThirtyThirtyAttachmentValues() {
		purpleStandardStock = 65536;
		blueStandardStock = 32768;
		whiteStandardStock = 16384;

		goldExtendedMag = 8192;
		purpleExtendedMag = 4096;
		blueExtendedMag = 2048;
		whiteExtendedMag = 1024;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 4194304;
		purpleThreeX = 2097152;
		blueOneXtwo = 1048576;
		whiteOneHolo = 524288;
		blueTwoX = 262144;
		whiteOneHOKV = 131072;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 96;
		purpleDualShell = 16;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{65536, "purpleStandardStock",},
			{32768, "blueStandardStock",},
			{16384, "whiteStandardStock"}
		};

		listExtendedMag = {
			{8192, "goldExtendedMag"},
			{4096, "purpleExtendedMag"},
			{2048, "blueExtendedMag"},
			{1024, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{1048576, "blueOneXtwo",},
			{524288, "whiteOneHolo",},
			{262144, "blueTwoX",},
			{131072, "whiteOneHOKV",},
			{4194304, "purpleTwoXfour"},
			{2097152, "purpleThreeX"}
		};

		listAttachments = {
			{96, "purpleShatterCaps"},
			{16, "purpleDualShell"}
		};
	}

	ThirtyThirtyAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class RampageAttachments : public IWeaponAttachments {
public:
	RampageAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	RampageAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class RampageAttachmentValues : public IWeaponAttachmentValues {
public:
	RampageAttachmentValues() {
		purpleStandardStock = 3355443;
		blueStandardStock = 16777216;
		whiteStandardStock = 8388608;

		goldExtendedMag = 131072;
		purpleExtendedMag = 65536;
		blueExtendedMag = 32768;
		whiteExtendedMag = 16384;

		purpleStabilizer = 268435456;
		blueStabilizer = 134217728;
		whiteStabilizer = 67108864;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 8192;
		purpleThreeX = 4096;
		blueOneXtwo = 2048;
		whiteOneHolo = 1024;
		blueTwoX = 512;
		whiteOneHOKV = 256;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{3355443, "purpleStandardStock",},
			{16777216, "blueStandardStock",},
			{8388608, "whiteStandardStock"}
		};

		listExtendedMag = {
			{131072, "goldExtendedMag"},
			{65536, "purpleExtendedMag"},
			{32768, "blueExtendedMag"},
			{16384, "whiteExtendedMag"}
		};

		listStabilizer = {
			{268435456, "purpleStabilizer"},
			{134217728, "blueStabilizer"},
			{67108864, "whiteStabilizer"}
		};

		listScope = {
			{2048, "blueOneXtwo",},
			{1024, "whiteOneHolo",},
			{512, "blueTwoX",},
			{256, "whiteOneHOKV",},
			{8192, "purpleTwoXfour"},
			{4096, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	RampageAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class CARAttachments : public IWeaponAttachments {
public:
	CARAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = true;
	};

	CARAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
	};


private:
};

class CARAttachmentValues : public IWeaponAttachmentValues {
public:
	CARAttachmentValues() {
		purpleStandardStock = 16777216;
		blueStandardStock = 8388608;
		whiteStandardStock = 4194304;

		goldExtendedMag = 16384;
		purpleExtendedMag = 8192;
		blueExtendedMag = 4096;
		whiteExtendedMag = 2048;

		purpleStabilizer = 536870912;
		blueStabilizer = 268435456;
		whiteStabilizer = 134217728;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 512;
		whiteOneHolo = 256;
		blueTwoX = 128;
		whiteOneHOKV = 64;
		goldDigitalScope = 1024;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{16777216, "purpleStandardStock",},
			{8388608, "blueStandardStock",},
			{4194304, "whiteStandardStock"}
		};

		listExtendedMag = {
			{16384, "goldExtendedMag"},
			{8192, "purpleExtendedMag"},
			{4096, "blueExtendedMag"},
			{2048, "whiteExtendedMag"}
		};

		listStabilizer = {
			{536870912, "purpleStabilizer"},
			{268435456, "blueStabilizer"},
			{134217728, "whiteStabilizer"}
		};

		listScope = {
			{512, "blueOneXtwo",},
			{256, "whiteOneHolo",},
			{128, "blueTwoX",},
			{64, "whiteOneHOKV",},
			{1024, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	CARAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class LStarAttachments : public IWeaponAttachments {
public:
	LStarAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = true;
	};

	LStarAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class LStarAttachmentValues : public IWeaponAttachmentValues {
public:
	LStarAttachmentValues() {
		purpleStandardStock = 64;
		blueStandardStock = 32;
		whiteStandardStock = 16;

		goldExtendedMag = 1024;
		purpleExtendedMag = 512;
		blueExtendedMag = 256;
		whiteExtendedMag = 128;

		purpleStabilizer = 8192;
		blueStabilizer = 4096;
		whiteStabilizer = 2048;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 524288;
		purpleThreeX = 262144;
		blueOneXtwo = 131072;
		whiteOneHolo = 65536;
		blueTwoX = 32768;
		whiteOneHOKV = 16384;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{64, "purpleStandardStock",},
			{32, "blueStandardStock",},
			{16, "whiteStandardStock"}
		};

		listExtendedMag = {
			{1024, "goldExtendedMag"},
			{512, "purpleExtendedMag"},
			{256, "blueExtendedMag"},
			{128, "whiteExtendedMag"}
		};

		listStabilizer = {
			{8192, "purpleStabilizer"},
			{4096, "blueStabilizer"},
			{2048, "whiteStabilizer"}
		};

		listScope = {
			{131072, "blueOneXtwo",},
			{65536, "whiteOneHolo",},
			{32768, "blueTwoX",},
			{16384, "whiteOneHOKV",},
			{524288, "purpleTwoXfour"},
			{262144, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	LStarAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class HavocAttachments : public IWeaponAttachments {
public:
	HavocAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = true; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = true;
	};

	HavocAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class HavocAttachmentValues : public IWeaponAttachmentValues {
public:
	HavocAttachmentValues() {
		purpleStandardStock = 524288;
		blueStandardStock = 262144;
		whiteStandardStock = 131072;

		goldExtendedMag = 16384;
		purpleExtendedMag = 8192;
		blueExtendedMag = 4096;
		whiteExtendedMag = 2048;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 1024;
		purpleThreeX = 512;
		blueOneXtwo = 256;
		whiteOneHolo = 128;
		blueTwoX = 64;
		whiteOneHOKV = 32;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 16;
		purpleHammerpoint = 0;

		listStandardStock = {
			{524288, "purpleStandardStock",},
			{262144, "blueStandardStock",},
			{131072, "whiteStandardStock"}
		};

		listExtendedMag = {
			{16384, "goldExtendedMag"},
			{8192, "purpleExtendedMag"},
			{4096, "blueExtendedMag"},
			{2048, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{256, "blueOneXtwo",},
			{128, "whiteOneHolo",},
			{64, "blueTwoX",},
			{32, "whiteOneHOKV",},
			{1024, "purpleTwoXfour"},
			{512, "purpleThreeX"}
		};

		listAttachments = {
			{16, "goldTurboCharger"}
		};
	}

	HavocAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class DevotionAttachments : public IWeaponAttachments {
public:
	DevotionAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = true; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = true;
	};

	DevotionAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class DevotionAttachmentValues : public IWeaponAttachmentValues {
public:
	DevotionAttachmentValues() {
		purpleStandardStock = 33554432;
		blueStandardStock = 16777216;
		whiteStandardStock = 8388608;

		goldExtendedMag = 512;
		purpleExtendedMag = 256;
		blueExtendedMag = 128;
		whiteExtendedMag = 64;

		purpleStabilizer = 4194304;
		blueStabilizer = 2097152;
		whiteStabilizer = 1048576;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 32768;
		purpleThreeX = 16384;
		blueOneXtwo = 8192;
		whiteOneHolo = 4096;
		blueTwoX = 2048;
		whiteOneHOKV = 1024;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 32;
		purpleHammerpoint = 0;

		listStandardStock = {
			{33554432, "purpleStandardStock",},
			{16777216, "blueStandardStock",},
			{8388608, "whiteStandardStock"}
		};

		listExtendedMag = {
			{512, "goldExtendedMag"},
			{256, "purpleExtendedMag"},
			{128, "blueExtendedMag"},
			{64, "whiteExtendedMag"}
		};

		listStabilizer = {
			{4194304, "purpleStabilizer"},
			{2097152, "blueStabilizer"},
			{1048576, "whiteStabilizer"}
		};

		listScope = {
			{8192, "blueOneXtwo",},
			{4096, "whiteOneHolo",},
			{2048, "blueTwoX",},
			{1024, "whiteOneHOKV",},
			{32768, "purpleTwoXfour"},
			{16384, "purpleThreeX"}
		};

		listAttachments = {
			{32, "goldTurboCharger"}
		};
	}

	DevotionAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class TripleTakeAttachments : public IWeaponAttachments {
public:
	TripleTakeAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = true;
		isSniperStock = true;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = true;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = true; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = true;
	};

	TripleTakeAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;
		isSniperStock = attachment.isSniperStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class TripleTakeAttachmentValues : public IWeaponAttachmentValues {
public:
	TripleTakeAttachmentValues() {
		standardValue = 768;

		purpleStandardStock = 4864;
		blueStandardStock = 2816;
		whiteStandardStock = 1792;

		goldExtendedMag = 4195072;
		purpleExtendedMag = 2097920;
		blueExtendedMag = 1049344;
		whiteExtendedMag = 525056;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 262912;
		purpleThreeX = 131840;
		blueOneXtwo = 66304;
		whiteOneHolo = 33536;
		blueTwoX = 17152;
		whiteOneHOKV = 8960;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 864;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{4864 - standardValue, "purpleStandardStock",},
			{2816 - standardValue, "blueStandardStock",},
			{1792 - standardValue, "whiteStandardStock"}
		};

		listExtendedMag = {
			{4195072 - standardValue, "goldExtendedMag"},
			{2097920 - standardValue, "purpleExtendedMag"},
			{1049344 - standardValue, "blueExtendedMag"},
			{525056 - standardValue, "whiteExtendedMag"}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{66304 - standardValue, "blueOneXtwo",},
			{33536 - standardValue, "whiteOneHolo",},
			{17152 - standardValue, "blueTwoX",},
			{8960 - standardValue, "whiteOneHOKV",},
			{262912 - standardValue, "purpleTwoXfour"},
			{131840 - standardValue, "purpleThreeX"}
		};

		listAttachments = {
			{864 - standardValue, "purpleKineticFeeder"}
		};
	}

	TripleTakeAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class BocekAttachments : public IWeaponAttachments {
public:
	BocekAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = true; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = true; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = true;
	};

	BocekAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
		canHaveArrow = attachment.canHaveArrow;
	};


private:
};

class BocekAttachmentValues : public IWeaponAttachmentValues {
public:
	BocekAttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 67108864;
		blueOneXtwo = 33554432;
		whiteOneHolo = 16777216;
		blueTwoX = 8388608;
		whiteOneHOKV = 4194304;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 16;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 384;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{33554432, "blueOneXtwo",},
			{16777216, "whiteOneHolo",},
			{8388608, "blueTwoX",},
			{4194304, "whiteOneHOKV",},
			{67108864, "purpleThreeX"}
		};

		listAttachments = {
			{384, "purpleShatterCaps"},
			{16, "purpleDeadEyesTempo"}
		};
	}

	BocekAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class G7ScoutAttachments : public IWeaponAttachments {
public:
	G7ScoutAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
	};

	G7ScoutAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class G7ScoutAttachmentValues : public IWeaponAttachmentValues {
public:
	G7ScoutAttachmentValues() {
		standardValue = 270794864;

		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 270811248;
		purpleThreeX = 270803056;
		blueOneXtwo = 270798960;
		whiteOneHolo = 270796912;
		blueTwoX = 270795888;
		whiteOneHOKV = 270795376;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{270798960 - standardValue, "blueOneXtwo",},
			{270796912 - standardValue, "whiteOneHolo",},
			{270795888 - standardValue, "blueTwoX",},
			{270795376 - standardValue, "whiteOneHOKV",},
			{270811248 - standardValue, "purpleTwoXfour"},
			{270803056 - standardValue, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	G7ScoutAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class VoltAttachments : public IWeaponAttachments {
public:
	VoltAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
	};

	VoltAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class VoltAttachmentValues : public IWeaponAttachmentValues {
public:
	VoltAttachmentValues() {
		standardValue = 34619408;

		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 34619920;
		whiteOneHolo = 34619664;
		blueTwoX = 34619536;
		whiteOneHOKV = 34619472;
		goldDigitalScope = 34620432;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{34619920 - standardValue, "blueOneXtwo",},
			{34619664 - standardValue, "whiteOneHolo",},
			{34619536 - standardValue, "blueTwoX",},
			{34619472 - standardValue, "whiteOneHOKV",},
			{34620432 - standardValue, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	VoltAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class SpitfireAttachments : public IWeaponAttachments {
public:
	SpitfireAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = true;
		canHaveThreeXScope = true;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = false;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = false;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
	};

	SpitfireAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
	};


private:
};

class SpitfireAttachmentValues : public IWeaponAttachmentValues {
public:
	SpitfireAttachmentValues() {
		standardValue = 151060496;

		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 0;
		blueStabilizer = 0;
		whiteStabilizer = 0;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 151064592;
		purpleThreeX = 151062544;
		blueOneXtwo = 151061520;
		whiteOneHolo = 151061008;
		blueTwoX = 151060752;
		whiteOneHOKV = 151060624;
		goldDigitalScope = 0;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{0, ""}
		};

		listScope = {
			{151061520 - standardValue, "blueOneXtwo",},
			{151061008 - standardValue, "whiteOneHolo",},
			{151060752 - standardValue, "blueTwoX",},
			{151060624 - standardValue, "whiteOneHOKV",},
			{151064592 - standardValue, "purpleTwoXfour"},
			{151062544 - standardValue, "purpleThreeX"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	SpitfireAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class MastiffAttachments : public IWeaponAttachments {
public:
	MastiffAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = true; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
		canHaveShotgunAmmo = true;
	};

	MastiffAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
		canHaveArrow = attachment.canHaveArrow;
		canHaveShotgunAmmo = attachment.canHaveShotgunAmmo;
	};


private:
};

class MastiffAttachmentValues : public IWeaponAttachmentValues {
public:
	MastiffAttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 1024;
		blueStabilizer = 512;
		whiteStabilizer = 256;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 16384;
		whiteOneHolo = 4096;
		blueTwoX = 32768;
		whiteOneHOKV = 2048;
		goldDigitalScope = 8192;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 32;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{1024, "purpleStabilizer"},
			{512, "blueStabilizer"},
			{256, "whiteStabilizer"}
		};

		listScope = {
			{16384, "blueOneXtwo",},
			{4096, "whiteOneHolo",},
			{32768, "blueTwoX",},
			{2048, "whiteOneHOKV",},
			{8192, "goldDigitalScope"}
		};

		listAttachments = {
			{32, "purpleDualShell"}
		};
	}

	MastiffAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class EVA8Attachments : public IWeaponAttachments {
public:
	EVA8Attachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
		canHaveShotgunAmmo = true;
	};

	EVA8Attachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
		canHaveArrow = attachment.canHaveArrow;
		canHaveShotgunAmmo = attachment.canHaveShotgunAmmo;
	};


private:
};

class EVA8AttachmentValues : public IWeaponAttachmentValues {
public:
	EVA8AttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 64;
		blueStabilizer = 32;
		whiteStabilizer = 16;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 131072;
		whiteOneHolo = 65536;
		blueTwoX = 32768;
		whiteOneHOKV = 16384;
		goldDigitalScope = 262144;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 32;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{64, "purpleStabilizer"},
			{32, "blueStabilizer"},
			{16, "whiteStabilizer"}
		};

		listScope = {
			{131072, "blueOneXtwo",},
			{65536, "whiteOneHolo",},
			{32768, "blueTwoX",},
			{16384, "whiteOneHOKV",},
			{262144, "goldDigitalScope"}
		};

		listAttachments = {
			{0, ""}
		};
	}

	EVA8AttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};

class PeacekeeperAttachments : public IWeaponAttachments {
public:
	PeacekeeperAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = false; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = true; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
		canHaveShotgunAmmo = true;
	};

	PeacekeeperAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
		canHaveArrow = attachment.canHaveArrow;
		canHaveShotgunAmmo = attachment.canHaveShotgunAmmo;
	};


private:
};

class PeacekeeperAttachmentValues : public IWeaponAttachmentValues {
public:
	PeacekeeperAttachmentValues() {
		standardValue = 384;

		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 65920;
		blueStabilizer = 33152;
		whiteStabilizer = 16768;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 4480;
		whiteOneHolo = 2432;
		blueTwoX = 1408;
		whiteOneHOKV = 896;
		goldDigitalScope = 8576;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 432;
		goldTurboCharger = 0;
		purpleHammerpoint = 0;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{65920 - standardValue, "purpleStabilizer"},
			{33152 - standardValue, "blueStabilizer"},
			{16768 - standardValue, "whiteStabilizer"}
		};

		listScope = {
			{4480 - standardValue, "blueOneXtwo",},
			{2432 - standardValue, "whiteOneHolo",},
			{1408 - standardValue, "blueTwoX",},
			{896 - standardValue, "whiteOneHOKV",},
			{8576 - standardValue, "goldDigitalScope"}
		};

		listAttachments = {
			{432 - standardValue, "purpleKineticFeeder"}
		};
	}

	PeacekeeperAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;

		standardValue = attachment.standardValue;
	}
};

class MozambiqueAttachments : public IWeaponAttachments {
public:
	MozambiqueAttachments() {
		purpleStock = false;
		blueStock = false;
		whiteStock = false;
		canHaveStock = false;
		isSniperStock = false;

		fourXtenScope = false;
		fourXeightScope = false;
		sixXScope = false;
		canHaveSniperScope = false;

		twoXfourScope = false;
		threeXScope = false;
		canHaveTwoXFourScope = false;
		canHaveThreeXScope = false;

		oneXtwoScope = false;
		oneHoloScope = false;
		twoXScope = false;
		oneHOKVScope = false;
		digitalScope = false;
		canHaveDigitalScope = true;

		goldMag = false;
		purpleMag = false;
		blueMag = false;
		whiteMag = false;
		canHaveMag = false;

		purpleStabi = false;
		blueStabi = false;
		whiteStabi = false;
		canHaveStabi = true;

		deadEyesTempo = false;
		canHaveDeadEyesTempo = false; // Bocek, Sentinel
		hammerpoint = false;
		canHaveHammerpoint = true; // RE-45, P2020, Mosambique
		boostedLoader = false;
		canHaveBoostedLoader = false; // Wingman, Hemlok
		shatterCaps = false;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = false; // Bocek, 30-30
		dualShell = false;
		canHaveDualShell = false; // 30-30, Mastiff
		kineticFeeder = false;
		canHaveKineticFeeder = false; // Peacekeeper, Triple Take
		turboCharger = false;
		canHaveTurboCharger = false; // Devotion, Havoc

		canHaveLightAmmo = false;
		canHaveHeavyAmmo = false;
		canHaveEnergyAmmo = false;
		canHaveArrow = false;
		canHaveShotgunAmmo = true;
	};

	MozambiqueAttachments(IWeaponAttachments attachment) {
		purpleStock = attachment.purpleStock;
		blueStock = attachment.blueStock;
		whiteStock = attachment.whiteStock;
		canHaveStock = attachment.canHaveStock;

		fourXtenScope = attachment.fourXtenScope;
		fourXeightScope = attachment.fourXeightScope;
		sixXScope = attachment.sixXScope;
		canHaveSniperScope = attachment.canHaveSniperScope;

		twoXfourScope = attachment.twoXfourScope;
		threeXScope = attachment.threeXScope;
		canHaveTwoXFourScope = attachment.canHaveTwoXFourScope;
		canHaveThreeXScope = attachment.canHaveThreeXScope;

		oneXtwoScope = attachment.oneXtwoScope;
		oneHoloScope = attachment.oneHoloScope;
		twoXScope = attachment.twoXScope;
		oneHOKVScope = attachment.oneHOKVScope;
		digitalScope = attachment.digitalScope;
		canHaveDigitalScope = attachment.canHaveDigitalScope;

		goldMag = attachment.goldMag;
		purpleMag = attachment.purpleMag;
		blueMag = attachment.blueMag;
		whiteMag = attachment.whiteMag;
		canHaveMag = attachment.canHaveMag;

		purpleStabi = attachment.purpleStabi;
		blueStabi = attachment.blueStabi;
		whiteStabi = attachment.whiteStabi;
		canHaveStabi = attachment.canHaveStabi;

		deadEyesTempo = attachment.deadEyesTempo;
		canHaveDeadEyesTempo = attachment.canHaveDeadEyesTempo; // Bocek, Sentinel
		hammerpoint = attachment.hammerpoint;
		canHaveHammerpoint = attachment.canHaveHammerpoint; // RE-45, P2020, Mosambique
		boostedLoader = attachment.boostedLoader;
		canHaveBoostedLoader = attachment.canHaveBoostedLoader; // Wingman, Hemlok
		shatterCaps = attachment.shatterCaps;
		// Dual Shell ODER Shatter Caps bei 30-30
		canHaveShatterCaps = attachment.canHaveShatterCaps; // Bocek, 30-30
		dualShell = attachment.dualShell;
		canHaveDualShell = attachment.canHaveDualShell; // 30-30, Mastiff
		kineticFeeder = attachment.kineticFeeder;
		canHaveKineticFeeder = attachment.canHaveKineticFeeder; // Peacekeeper, Triple Take
		turboCharger = attachment.turboCharger;
		canHaveTurboCharger = attachment.canHaveTurboCharger; // Devotion, Havoc

		canHaveLightAmmo = attachment.canHaveLightAmmo;
		canHaveHeavyAmmo = attachment.canHaveHeavyAmmo;
		canHaveEnergyAmmo = attachment.canHaveEnergyAmmo;
		canHaveArrow = attachment.canHaveArrow;
		canHaveShotgunAmmo = attachment.canHaveShotgunAmmo;
	};


private:
};

class MozambiqueAttachmentValues : public IWeaponAttachmentValues {
public:
	MozambiqueAttachmentValues() {
		purpleStandardStock = 0;
		blueStandardStock = 0;
		whiteStandardStock = 0;

		goldExtendedMag = 0;
		purpleExtendedMag = 0;
		blueExtendedMag = 0;
		whiteExtendedMag = 0;

		purpleStabilizer = 524288;
		blueStabilizer = 262144;
		whiteStabilizer = 131072;

		goldFourXten = 0;
		purpleFourXeight = 0;
		blueSixX = 0;
		purpleTwoXfour = 0;
		purpleThreeX = 0;
		blueOneXtwo = 8192;
		whiteOneHolo = 4096;
		blueTwoX = 2048;
		whiteOneHOKV = 1024;
		goldDigitalScope = 16384;

		purpleDeadEyesTempo = 0;
		purpleHammerpoint = 0;
		goldBoostedLoader = 0;
		purpleShatterCaps = 0;
		purpleDualShell = 0;
		purpleKineticFeeder = 0;
		goldTurboCharger = 0;
		purpleHammerpoint = 128;

		listStandardStock = {
			{0, "",}
		};

		listExtendedMag = {
			{0, ""}
		};

		listStabilizer = {
			{524288, "purpleStabilizer"},
			{262144, "blueStabilizer"},
			{131072, "whiteStabilizer"}
		};

		listScope = {
			{8192, "blueOneXtwo",},
			{4096, "whiteOneHolo",},
			{2048, "blueTwoX",},
			{1024, "whiteOneHOKV",},
			{16384, "goldDigitalScope"}
		};

		listAttachments = {
			{128, "purpleHammerpoint"}
		};
	}

	MozambiqueAttachmentValues(IWeaponAttachmentValues attachment) {
		purpleStandardStock = attachment.purpleStandardStock;
		blueStandardStock = attachment.blueStandardStock;
		whiteStandardStock = attachment.whiteStandardStock;

		goldExtendedMag = attachment.goldExtendedMag;
		purpleExtendedMag = attachment.purpleExtendedMag;
		blueExtendedMag = attachment.blueExtendedMag;
		whiteExtendedMag = attachment.whiteExtendedMag;

		purpleStabilizer = attachment.purpleStabilizer;
		blueStabilizer = attachment.blueStabilizer;
		whiteStabilizer = attachment.whiteStabilizer;

		goldFourXten = attachment.goldFourXten;
		purpleFourXeight = attachment.purpleFourXeight;
		blueSixX = attachment.blueSixX;
		purpleTwoXfour = attachment.purpleTwoXfour;
		purpleThreeX = attachment.purpleThreeX;
		blueOneXtwo = attachment.blueOneXtwo;
		whiteOneHolo = attachment.whiteOneHolo;
		blueTwoX = attachment.blueTwoX;
		whiteOneHOKV = attachment.whiteOneHOKV;

		listStandardStock = attachment.listStandardStock;
		listExtendedMag = attachment.listExtendedMag;
		listStabilizer = attachment.listStabilizer;
		listScope = attachment.listScope;

		purpleHammerpoint = attachment.purpleHammerpoint;
	}
};
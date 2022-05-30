#pragma once
#include <d3dx9.h>
#include <string>

using namespace std;

// definiert die Farben des Item-ESP
static D3DCOLOR colorGoldItem = D3DCOLOR_ARGB(255, 242, 235, 31);
static D3DCOLOR colorRedItem = D3DCOLOR_ARGB(255, 255, 62, 48);
static D3DCOLOR colorBlueItem = D3DCOLOR_ARGB(255, 5, 132, 250);
static D3DCOLOR colorPurpleItem = D3DCOLOR_ARGB(255, 234, 5, 250);
static D3DCOLOR colorWhiteItem = D3DCOLOR_ARGB(255, 255, 255, 255);

enum class ItemType {
	ExtendedMagSniper = 1,
	SniperStock = 2,
	DeadeyesTempoWeaponHopup = 3, // Deadeye's Tempo
	Stabilizer = 4,
	SniperScope = 5,
	ARSniperScope = 6, // 2-4fach und 3-fach
	StandardScope = 7, // weiﬂ und blau, quasi 1-Holo, 1 HOKV, 1-2fach, 2fach
	DigitalScope = 8, // RE-45, Mastiff, Mosambique, Peacekeeper
	WeaponAR = 9, // Havoc, Flatline, Hemlok, R301
	Grenade = 10,
	Healing = 11, // Shield battery, Shield cell, Med Kit...
	SurvivalItems = 12, // Ultimte Accelerant, Mobile Respawner, Heatshield
	EvoShield = 13,
	Helmet = 14,
	Backpack = 15,
	KnockdownShield = 16,
	StandardStock = 17,
	ExtendedLightMag = 18,
	LightAmmo = 19,
	BoostedLoader = 20,
	ShatterCaps = 21,
	ExtendedHeavyMag = 22,
	DualShell = 23,
	HeavyAmmo = 24,
	KineticFeeder = 25,
	Turbocharger = 26,
	ExtendedEnergyMag = 27,
	EnergyAmmo = 28,
	Arrow = 29,
	ShotgunBolt = 30,
	ShotgunShells = 31,
	WeaponSMG = 32, // Alternator, Prowler, R-99, Volt, Car
	WeaponLMG = 33, // Devotion, L-Star, Spitfire, Rampage
	WeaponMarksman = 34, // G7-Scout, Triple-Take, 30-30, Bocek
	WeaponSniperRifle = 35, // Charge Rifle, Longbow, Kraber, Sentinel
	WeaponShotguns = 36, // EVA-8, Mastiff, Mozambique, Peacekeeper
	WeaponPistols = 37, // RE-45, P2020, Wingman
	SniperAmmo = 38,
	HammerPoint = 39
};

class ItemBase {
public:
	friend bool operator==(const ItemBase& left, int value) {
		return left.itemID == value;
	}

	int itemID = 0;
	D3DCOLOR rareColor;
	ItemType type;
	std::string name;
};

class ExtendedSniperMagGold : public ItemBase {
public:
	ExtendedSniperMagGold() {
		itemID = 221;
		rareColor = colorGoldItem;
		type = ItemType::ExtendedMagSniper;
		name = "Extended Sniper Mag";
	}
};

class ExtendedSniperMagWhite : public ItemBase {
public:
	ExtendedSniperMagWhite() {
		itemID = 218;
		rareColor = colorWhiteItem;
		type = ItemType::ExtendedMagSniper;
		name = "Extended Sniper Mag";
	}
};

class ExtendedSniperMagBlue : public ItemBase {
public:
	ExtendedSniperMagBlue() {
		itemID = 219;
		rareColor = colorBlueItem;
		type = ItemType::ExtendedMagSniper;
		name = "Extended Sniper Mag";
	}
};

class ExtendedSniperMagPurple : public ItemBase {
public:
	ExtendedSniperMagPurple() {
		itemID = 220;
		rareColor = colorPurpleItem;
		type = ItemType::ExtendedMagSniper;
		name = "Extended Sniper Mag";
	}
};

class SniperStockWhite : public ItemBase {
public:
	SniperStockWhite() {
		itemID = 228;
		rareColor = colorWhiteItem;
		type = ItemType::SniperStock;
		name = "Sniper Stock";
	}
};

class SniperStockBlue : public ItemBase {
public:
	SniperStockBlue() {
		itemID = 229;
		rareColor = colorBlueItem;
		type = ItemType::SniperStock;
		name = "Sniper Stock";
	}
};

class SniperStockPurple : public ItemBase {
public:
	SniperStockPurple() {
		itemID = 230;
		rareColor = colorPurpleItem;
		type = ItemType::SniperStock;
		name = "Sniper Stock";
	}
};

class DeadeyesTempoPurple : public ItemBase {
public:
	DeadeyesTempoPurple() {
		itemID = 240;
		rareColor = colorPurpleItem;
		type = ItemType::DeadeyesTempoWeaponHopup;
		name = "Deadeye's Tempo";
	}
};

class StabilizerWhite : public ItemBase {
public:
	StabilizerWhite() {
		itemID = 202;
		rareColor = colorWhiteItem;
		type = ItemType::Stabilizer;
		name = "Barrel Stabilizer";
	}
};


class StabilizerBlue : public ItemBase {
public:
	StabilizerBlue() {
		itemID = 203;
		rareColor = colorBlueItem;
		type = ItemType::Stabilizer;
		name = "Barrel Stabilizer";
	}
};

class StabilizerPurple : public ItemBase {
public:
	StabilizerPurple() {
		itemID = 204;
		rareColor = colorPurpleItem;
		type = ItemType::Stabilizer;
		name = "Barrel Stabilizer";
	}
};

class TwoXFourAOG : public ItemBase {
public:
	TwoXFourAOG() {
		itemID = 198;
		rareColor = colorPurpleItem;
		type = ItemType::ARSniperScope;
		name = "2X-4X AOG";
	}
};

class SixXSniper : public ItemBase {
public:
	SixXSniper() {
		itemID = 199;
		rareColor = colorBlueItem;
		type = ItemType::SniperScope;
		name = "6X Sniper";
	}
};

class FourXSixSniper : public ItemBase {
public:
	FourXSixSniper() {
		itemID = 200;
		rareColor = colorPurpleItem;
		type = ItemType::SniperScope;
		name = "4X-6X Sniper";
	}
};

class FourXTenDigital : public ItemBase {
public:
	FourXTenDigital() {
		itemID = 201;
		rareColor = colorGoldItem;
		type = ItemType::SniperScope;
		name = "4X-10X Digital";
	}
};

class OneXHCOG : public ItemBase {
public:
	OneXHCOG() {
		itemID = 192;
		rareColor = colorWhiteItem;
		type = ItemType::StandardScope;
		name = "1X HCOG";
	}
};

class TwoXHCOG : public ItemBase {
public:
	TwoXHCOG() {
		itemID = 193;
		rareColor = colorBlueItem;
		type = ItemType::StandardScope;
		name = "2X HCOG";
	}
};

class OneXHOLO : public ItemBase {
public:
	OneXHOLO() {
		itemID = 194;
		rareColor = colorWhiteItem;
		type = ItemType::StandardScope;
		name = "1X HOLO";
	}
};

class OneXTwoXHOLO : public ItemBase {
public:
	OneXTwoXHOLO() {
		itemID = 195;
		rareColor = colorBlueItem;
		type = ItemType::StandardScope;
		name = "1X-2X HOLO";
	}
};

class ThreeXHCOG : public ItemBase {
public:
	ThreeXHCOG() {
		itemID = 197;
		rareColor = colorPurpleItem;
		type = ItemType::ARSniperScope;
		name = "3X HCOG";
	}
};

class OneXDigital : public ItemBase {
public:
	OneXDigital() {
		itemID = 196;
		rareColor = colorGoldItem;
		type = ItemType::DigitalScope;
		name = "1X Digital";
	}
};

class LongbowWepaon : public ItemBase {
public:
	LongbowWepaon() {
		itemID = 58;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSniperRifle;
		name = "Longbow";
	}
};

class ChargeRifleWeapon : public ItemBase {
public:
	ChargeRifleWeapon() {
		itemID = 63;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSniperRifle;
		name = "Charge Rifle";
	}
};

class SentinelWeapon : public ItemBase {
public:
	SentinelWeapon() {
		itemID = 104;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSniperRifle;
		name = "Sentinel";
	}
};

class SniperAmmo : public ItemBase {
public:
	SniperAmmo() {
		itemID = 124;
		rareColor = colorWhiteItem;
		type = ItemType::SniperAmmo;
		name = "Sniper Ammo";
	}
};

class ArcstarGrenade : public ItemBase {
public:
	ArcstarGrenade() {
		itemID = 191;
		rareColor = colorWhiteItem;
		type = ItemType::Grenade;
		name = "Arcstar";
	}
};

class FragGrenade : public ItemBase {
public:
	FragGrenade() {
		itemID = 190;
		rareColor = colorWhiteItem;
		type = ItemType::Grenade;
		name = "Frag Grenade";
	}
};

class ThermiteGrenade : public ItemBase {
public:
	ThermiteGrenade() {
		itemID = 189;
		rareColor = colorWhiteItem;
		type = ItemType::Grenade;
		name = "Thermite Grenade";
	}
};

class ShieldCellHealing : public ItemBase {
public:
	ShieldCellHealing() {
		itemID = 166;
		rareColor = colorWhiteItem;
		type = ItemType::Healing;
		name = "Shield Cell";
	}
};

class ShieldBatteryHealing : public ItemBase {
public:
	ShieldBatteryHealing() {
		itemID = 165;
		rareColor = colorBlueItem;
		type = ItemType::Healing;
		name = "Shield Battery";
	}
};

class SyringeHealing : public ItemBase {
public:
	SyringeHealing() {
		itemID = 164;
		rareColor = colorWhiteItem;
		type = ItemType::Healing;
		name = "Syringe";
	}
};

class MedKitHealing : public ItemBase {
public:
	MedKitHealing() {
		itemID = 163;
		rareColor = colorBlueItem;
		type = ItemType::Healing;
		name = "Med Kit";
	}
};

class PhoenixKitHealing : public ItemBase {
public:
	PhoenixKitHealing() {
		itemID = 162;
		rareColor = colorPurpleItem;
		type = ItemType::Healing;
		name = "Phoenix Kit";
	}
};

class UltimateAccelerantSurvivalItems : public ItemBase {
public:
	UltimateAccelerantSurvivalItems() {
		itemID = 161;
		rareColor = colorBlueItem;
		type = ItemType::SurvivalItems;
		name = "Ultimate Accelerant";
	}
};

class MobileRespawnerSurvivalItems : public ItemBase {
public:
	MobileRespawnerSurvivalItems() {
		itemID = 252;
		rareColor = colorBlueItem;
		type = ItemType::SurvivalItems;
		name = "Mobile Respawner";
	}
};

class HeatshieldSurvivalItems : public ItemBase {
public:
	HeatshieldSurvivalItems() {
		itemID = 251;
		rareColor = colorBlueItem;
		type = ItemType::SurvivalItems;
		name = "Heatshield";
	}
};

class BodyShieldGold : public ItemBase {
public:
	BodyShieldGold() {
		itemID = 174;
		rareColor = colorGoldItem;
		type = ItemType::EvoShield;
		name = "Body Shield";
	}
};

class BodyShieldPurple : public ItemBase {
public:
	BodyShieldPurple() {
		itemID = 173;
		rareColor = colorPurpleItem;
		type = ItemType::EvoShield;
		name = "Body Shield";
	}
};

class BodyShieldBlue : public ItemBase {
public:
	BodyShieldBlue() {
		itemID = 172;
		rareColor = colorBlueItem;
		type = ItemType::EvoShield;
		name = "Body Shield";
	}
};

class BodyShieldWhite : public ItemBase {
public:
	BodyShieldWhite() {
		itemID = 171;
		rareColor = colorWhiteItem;
		type = ItemType::EvoShield;
		name = "Body Shield";
	}
};

class EvoShieldRed : public ItemBase {
public:
	EvoShieldRed() {
		itemID = 179;
		rareColor = colorRedItem;
		type = ItemType::EvoShield;
		name = "Evo Shield";
	}
};

class EvoShieldPurple : public ItemBase {
public:
	EvoShieldPurple() {
		itemID = 178;
		rareColor = colorPurpleItem;
		type = ItemType::EvoShield;
		name = "Evo Shield";
	}
};

class EvoShieldBlue : public ItemBase {
public:
	EvoShieldBlue() {
		itemID = 177;
		rareColor = colorBlueItem;
		type = ItemType::EvoShield;
		name = "Evo Shield";
	}
};

class EvoShieldWhite : public ItemBase {
public:
	EvoShieldWhite() {
		itemID = 176;
		rareColor = colorWhiteItem;
		type = ItemType::EvoShield;
		name = "Evo Shield";
	}
};

class HelmetGold : public ItemBase {
public:
	HelmetGold() {
		itemID = 170;
		rareColor = colorGoldItem;
		type = ItemType::Helmet;
		name = "Helmet";
	}
};

class HelmetPurple : public ItemBase {
public:
	HelmetPurple() {
		itemID = 169;
		rareColor = colorPurpleItem;
		type = ItemType::Helmet;
		name = "Helmet";
	}
};

class HelmetBlue : public ItemBase {
public:
	HelmetBlue() {
		itemID = 168;
		rareColor = colorBlueItem;
		type = ItemType::Helmet;
		name = "Helmet";
	}
};

class HelmetWhite : public ItemBase {
public:
	HelmetWhite() {
		itemID = 167;
		rareColor = colorWhiteItem;
		type = ItemType::Helmet;
		name = "Helmet";
	}
};

class BackpackGold : public ItemBase {
public:
	BackpackGold() {
		itemID = 188;
		rareColor = colorGoldItem;
		type = ItemType::Backpack;
		name = "Backpack";
	}
};

class BackpackPurple : public ItemBase {
public:
	BackpackPurple() {
		itemID = 187;
		rareColor = colorPurpleItem;
		type = ItemType::Backpack;
		name = "Backpack";
	}
};

class BackpackBlue : public ItemBase {
public:
	BackpackBlue() {
		itemID = 186;
		rareColor = colorBlueItem;
		type = ItemType::Backpack;
		name = "Backpack";
	}
};

class BackpackWhite : public ItemBase {
public:
	BackpackWhite() {
		itemID = 185;
		rareColor = colorWhiteItem;
		type = ItemType::Backpack;
		name = "Backpack";
	}
};

class KnockdownShieldGold : public ItemBase {
public:
	KnockdownShieldGold() {
		itemID = 184;
		rareColor = colorGoldItem;
		type = ItemType::KnockdownShield;
		name = "Knockdown Shield";
	}
};

class KnockdownShieldPurple : public ItemBase {
public:
	KnockdownShieldPurple() {
		itemID = 183;
		rareColor = colorPurpleItem;
		type = ItemType::KnockdownShield;
		name = "Knockdown Shield";
	}
};

class KnockdownShieldBlue : public ItemBase {
public:
	KnockdownShieldBlue() {
		itemID = 182;
		rareColor = colorBlueItem;
		type = ItemType::KnockdownShield;
		name = "Knockdown Shield";
	}
};

class KnockdownShieldWhite : public ItemBase {
public:
	KnockdownShieldWhite() {
		itemID = 181;
		rareColor = colorWhiteItem;
		type = ItemType::KnockdownShield;
		name = "Knockdown Shield";
	}
};

class HammerpointHopup : public ItemBase {
public:
	HammerpointHopup() {
		itemID = 233;
		rareColor = colorPurpleItem;
		type = ItemType::HammerPoint;
		name = "Hammerpoint";
	}
};

class StandardStockPurple : public ItemBase {
public:
	StandardStockPurple() {
		itemID = 227;
		rareColor = colorPurpleItem;
		type = ItemType::StandardStock;
		name = "Standard Stock";
	}
};

class StandardStockBlue : public ItemBase {
public:
	StandardStockBlue() {
		itemID = 226;
		rareColor = colorBlueItem;
		type = ItemType::StandardStock;
		name = "Standard Stock";
	}
};

class StandardStockWhite : public ItemBase {
public:
	StandardStockWhite() {
		itemID = 225;
		rareColor = colorWhiteItem;
		type = ItemType::StandardStock;
		name = "Standard Stock";
	}
};

class ExtendedLightMagGold : public ItemBase {
public:
	ExtendedLightMagGold() {
		itemID = 209;
		rareColor = colorGoldItem;
		type = ItemType::ExtendedLightMag;
		name = "Extended Light Mag";
	}
};

class ExtendedLightMagPurple : public ItemBase {
public:
	ExtendedLightMagPurple() {
		itemID = 208;
		rareColor = colorPurpleItem;
		type = ItemType::ExtendedLightMag;
		name = "Extended Light Mag";
	}
};

class ExtendedLightMagBlue : public ItemBase {
public:
	ExtendedLightMagBlue() {
		itemID = 207;
		rareColor = colorBlueItem;
		type = ItemType::ExtendedLightMag;
		name = "Extended Light Mag";
	}
};

class ExtendedLightMagWhite : public ItemBase {
public:
	ExtendedLightMagWhite() {
		itemID = 206;
		rareColor = colorWhiteItem;
		type = ItemType::ExtendedLightMag;
		name = "Extended Light Mag";
	}
};

class AlternatorWeapon : public ItemBase {
public:
	AlternatorWeapon() {
		itemID = 42;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSMG;
		name = "Alternator";
	}
};

class R99Weapon : public ItemBase {
public:
	R99Weapon() {
		itemID = 47;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSMG;
		name = "R-99";
	}
};

class R301Weapon : public ItemBase {
public:
	R301Weapon() {
		itemID = 69;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponAR;
		name = "R-301";
	}
};

class P2020Weapon : public ItemBase {
public:
	P2020Weapon() {
		itemID = 94;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponPistols;
		name = "P2020";
	}
};

class RE45Weapon : public ItemBase {
public:
	RE45Weapon() {
		itemID = 99;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponPistols;
		name = "RE-45";
	}
};

class LightAmmo : public ItemBase {
public:
	LightAmmo() {
		itemID = 120;
		rareColor = colorWhiteItem;
		type = ItemType::LightAmmo;
		name = "Light Ammo";
	}
};

class BoostedLoaderHopup : public ItemBase {
public:
	BoostedLoaderHopup() {
		itemID = 244;
		rareColor = colorGoldItem;
		type = ItemType::BoostedLoader;
		name = "Boosted Loader";
	}
};

class ShatterCapsHopup : public ItemBase {
public:
	ShatterCapsHopup() {
		itemID = 242;
		rareColor = colorPurpleItem;
		type = ItemType::ShatterCaps;
		name = "Shatter Caps";
	}
};

class ExtendedHeavyMagGold : public ItemBase {
public:
	ExtendedHeavyMagGold() {
		itemID = 213;
		rareColor = colorGoldItem;
		type = ItemType::ExtendedHeavyMag;
		name = "Extended Heavy Mag";
	}
};

class ExtendedHeavyMagPurple : public ItemBase {
public:
	ExtendedHeavyMagPurple() {
		itemID = 212;
		rareColor = colorPurpleItem;
		type = ItemType::ExtendedHeavyMag;
		name = "Extended Heavy Mag";
	}
};

class ExtendedHeavyMagBlue : public ItemBase {
public:
	ExtendedHeavyMagBlue() {
		itemID = 211;
		rareColor = colorBlueItem;
		type = ItemType::ExtendedHeavyMag;
		name = "Extended Heavy Mag";
	}
};

class ExtendedHeavyMagWhite : public ItemBase {
public:
	ExtendedHeavyMagWhite() {
		itemID = 210;
		rareColor = colorWhiteItem;
		type = ItemType::ExtendedHeavyMag;
		name = "Extended Heavy Mag";
	}
};

class DualShellHopup : public ItemBase {
public:
	DualShellHopup() {
		itemID = 119;
		rareColor = colorPurpleItem;
		type = ItemType::DualShell;
		name = "Dual Shell";
	}
};

class FlatlineWeapon : public ItemBase {
public:
	FlatlineWeapon() {
		itemID = 27;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponAR;
		name = "Flatline";
	}
};

class HemlokWeapon : public ItemBase {
public:
	HemlokWeapon() {
		itemID = 32;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponAR;
		name = "Hemlok";
	}
};

class ProwlerWeapon : public ItemBase {
public:
	ProwlerWeapon() {
		itemID = 52;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSMG;
		name = "Prowler";
	}
};

class WingmanWeapon : public ItemBase {
public:
	WingmanWeapon() {
		itemID = 89;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponPistols;
		name = "Wingman";
	}
};

class ThirtyThirtyWeapon : public ItemBase {
public:
	ThirtyThirtyWeapon() {
		itemID = 114;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponMarksman;
		name = "30-30";
	}
};

class RampageWeapon : public ItemBase {
public:
	RampageWeapon() {
		itemID = 126;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponLMG;
		name = "Rampage";
	}
};

class CARWeapon : public ItemBase {
public:
	CARWeapon() {
		itemID = 131;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponSMG;
		name = "C.A.R";
	}
};

class HeavyAmmo : public ItemBase {
public:
	HeavyAmmo() {
		itemID = 123;
		rareColor = colorWhiteItem;
		type = ItemType::HeavyAmmo;
		name = "Heavy Ammo";
	}
};

class KineticFeederHopup : public ItemBase {
public:
	KineticFeederHopup() {
		itemID = 243;
		rareColor = colorPurpleItem;
		type = ItemType::KineticFeeder;
		name = "Kinetic Feeder";
	}
};

class TurbochargerHopup : public ItemBase {
public:
	TurbochargerHopup() {
		itemID = 231;
		rareColor = colorGoldItem;
		type = ItemType::Turbocharger;
		name = "Turbocharger";
	}
};

class ExtendedEnergyMagGold : public ItemBase {
public:
	ExtendedEnergyMagGold() {
		itemID = 217;
		rareColor = colorGoldItem;
		type = ItemType::ExtendedEnergyMag;
		name = "Extended Energy Mag";
	}
};

class ExtendedEnergyMagPurple : public ItemBase {
public:
	ExtendedEnergyMagPurple() {
		itemID = 216;
		rareColor = colorPurpleItem;
		type = ItemType::ExtendedEnergyMag;
		name = "Extended Energy Mag";
	}
};

class ExtendedEnergyMagBlue : public ItemBase {
public:
	ExtendedEnergyMagBlue() {
		itemID = 215;
		rareColor = colorBlueItem;
		type = ItemType::ExtendedEnergyMag;
		name = "Extended Energy Mag";
	}
};

class ExtendedEnergyMagWhite : public ItemBase {
public:
	ExtendedEnergyMagWhite() {
		itemID = 214;
		rareColor = colorWhiteItem;
		type = ItemType::ExtendedEnergyMag;
		name = "Extended Energy Mag";
	}
};

class LStarWeapon : public ItemBase {
public:
	LStarWeapon() {
		itemID = 7;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponLMG;
		name = "L-Star";
	}
};

class HavocWeapon : public ItemBase {
public:
	HavocWeapon() {
		itemID = 12;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponAR;
		name = "HAVOC";
	}
};

class DevotionWeapon : public ItemBase {
public:
	DevotionWeapon() {
		itemID = 17;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponLMG;
		name = "Devotion";
	}
};

class TripleTakeWeapon : public ItemBase {
public:
	TripleTakeWeapon() {
		itemID = 22;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponMarksman;
		name = "Triple Take";
	}
};

class EnergyAmmo : public ItemBase {
public:
	EnergyAmmo() {
		itemID = 121;
		rareColor = colorWhiteItem;
		type = ItemType::EnergyAmmo;
		name = "Energy Ammo";
	}
};

class ArrowAmmo : public ItemBase {
public:
	ArrowAmmo() {
		itemID = 125;
		rareColor = colorWhiteItem;
		type = ItemType::Arrow;
		name = "Arrow";
	}
};

class BocekWeapon : public ItemBase {
public:
	BocekWeapon() {
		itemID = 109;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponMarksman;
		name = "Bocek";
	}
};

class KraberWeapon : public ItemBase {
public:
	KraberWeapon() {
		itemID = 1;
		rareColor = colorRedItem;
		type = ItemType::WeaponSniperRifle;
		name = "Kraber";
	}
};

class G7ScoutWeapon : public ItemBase {
public:
	G7ScoutWeapon() {
		itemID = 37;
		rareColor = colorRedItem;
		type = ItemType::WeaponMarksman;
		name = "G7 Scout";
	}
};

class VoltWeapon : public ItemBase {
public:
	VoltWeapon() {
		itemID = 57;
		rareColor = colorRedItem;
		type = ItemType::WeaponSMG;
		name = "Volt";
	}
};

class SpitfireWeapon : public ItemBase {
public:
	SpitfireWeapon() {
		itemID = 68;
		rareColor = colorRedItem;
		type = ItemType::WeaponLMG;
		name = "Spitfire";
	}
};

class ShotgunboltPurple : public ItemBase {
public:
	ShotgunboltPurple() {
		itemID = 224;
		rareColor = colorPurpleItem;
		type = ItemType::ShotgunBolt;
		name = "Shotgun bolt";
	}
};

class ShotgunboltBlue : public ItemBase {
public:
	ShotgunboltBlue() {
		itemID = 223;
		rareColor = colorBlueItem;
		type = ItemType::ShotgunBolt;
		name = "Shotgun bolt";
	}
};

class ShotgunboltWhite : public ItemBase {
public:
	ShotgunboltWhite() {
		itemID = 222;
		rareColor = colorWhiteItem;
		type = ItemType::ShotgunBolt;
		name = "Shotgun bolt";
	}
};

class MastiffWeapon : public ItemBase {
public:
	MastiffWeapon() {
		itemID = 2;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponShotguns;
		name = "Mastiff";
	}
};

class EVA8Weapon : public ItemBase {
public:
	EVA8Weapon() {
		itemID = 74;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponShotguns;
		name = "EVA-8";
	}
};

class PeacekeeperWeapon : public ItemBase {
public:
	PeacekeeperWeapon() {
		itemID = 79;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponShotguns;
		name = "Peacekeeper";
	}
};

class MozambiqueWeapon : public ItemBase {
public:
	MozambiqueWeapon() {
		itemID = 84;
		rareColor = colorWhiteItem;
		type = ItemType::WeaponShotguns;
		name = "Mozambique";
	}
};

class ShotgunShells : public ItemBase {
public:
	ShotgunShells() {
		itemID = 122;
		rareColor = colorWhiteItem;
		type = ItemType::ShotgunShells;
		name = "Shotgun Shells";
	}
};
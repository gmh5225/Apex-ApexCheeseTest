#include <chrono>
#include "Overlay.h"
#include "imgui/imgui_internal.h"
#include <random>
#include <dwmapi.h>
#include "Items.h"

using namespace std;
using namespace std::chrono;

static ImFont* verdanaFont;
D3DPRESENT_PARAMETERS p_Params;
HWND overlayWindow;
IDirect3D9Ex* p_Object;
ID3DXFont* pFont;
ID3DXFont* pItemFont;
ID3DXFont* pBoldFont;
ID3DXFont* pModuleFont;
ID3DXFont* pESPFont;
MARGINS margin = { -1 };
MSG message;
HWND hWnd = NULL;
RECT rc;
POINT windowWH = { 0, 0 };
IDirect3DTexture9* ksk;
IDirect3DTexture9* unknownCtrl;
ID3DXLine* p_Line;
IDirect3DDevice9Ex* p_Device;
bool menuActive = true;

std::mutex accessMutexOverlay;

#define IDR_FONT1                       104
#define IDR_FONT2                       105
#define IDR_FONT3                       106

bool IsKeyDown(int KEY)
{
	return (bool)(GetAsyncKeyState(KEY) & 0x8000);
}

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// definiert die Farben des Item-ESP
static D3DCOLOR colorGold = D3DCOLOR_ARGB(255, 242, 235, 31);
static D3DCOLOR colorRed = D3DCOLOR_ARGB(255, 255, 62, 48);
static D3DCOLOR colorBlue = D3DCOLOR_ARGB(255, 5, 132, 250);
static D3DCOLOR colorPurple = D3DCOLOR_ARGB(255, 234, 5, 250);
static D3DCOLOR colorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);

PlayerData playerBase[62] = {};
ItemData itemBase[66001] = {};
Vector3 mylocalPlayerPosition = Vector3();
CurrentWeapons currentWeapons = CurrentWeapons();

// Initialisierung der Waffen mit deren ModelName
map<string, string> weaponNameIndexMap =
{
{"mdl/weapons/rspn101_dmr/ptpov_rspn101_dmr.rmdl", "Longbow",},
{"mdl/weapons/defender/ptpov_defender.rmdl", "Elektrogewehr",},
{"mdl/weapons/sentinel/ptpov_sentinel.rmdl", "Sentinel",},
{"mdl/weapons/alternator_smg/ptpov_alternator_smg.rmdl", "Alternator",},
{"mdl/weapons/r97/ptpov_r97.rmdl", "R99",},
{"mdl/weapons/rspn101/ptpov_rspn101.rmdl", "R301",},
{"mdl/weapons/p2011/ptpov_p2011.rmdl", "P2020",},
{"mdl/weapons/p2011_auto/ptpov_p2011_auto.rmdl", "RE-45",},
{"mdl/techart/mshop/weapons/class/assault/flatline/flatline_base_v.rmdl", "Flatline",},
{"mdl/weapons/m1a1_hemlok/ptpov_hemlok.rmdl", "Hemlok",},
{"mdl/weapons/prowler_smg/ptpov_prowler_smg.rmdl", "Prowler",},
{"mdl/weapons/b3wing/ptpov_b3wing.rmdl", "Wingman",},
{"mdl/weapons/3030repeater/ptpov_3030repeater.rmdl", "30-30",},
{"mdl/techart/mshop/weapons/class/lmg/dragon/dragon_base_v.rmdl", "Rampage",},
{"mdl/techart/mshop/weapons/class/smg/car/car_base_v.rmdl", "C.A.R",},
{"mdl/weapons/lstar/ptpov_lstar.rmdl", "L-Star",},
{"mdl/weapons/beam_ar/ptpov_beam_ar.rmdl", "Havoc",},
{"mdl/weapons/hemlock_br/ptpov_hemlock_br.rmdl", "Devotion",},
{"mdl/weapons/doubletake/ptpov_doubletake.rmdl", "Triple Take",},
{"mdl/weapons/at_rifle/ptpov_at_rifle.rmdl", "Kraber",},
{"mdl/weapons/g2/ptpov_g2a4.rmdl", "G7-Scout",},
{"mdl/weapons/hemlok_smg/ptpov_hemlok_smg.rmdl", "Volt",},
{"mdl/weapons/lmg_hemlok/ptpov_lmg_hemlok.rmdl", "Spitfire",},
{"mdl/weapons/mastiff_stgn/ptpov_mastiff.rmdl", "Mastiff",},
{"mdl/weapons/w1128/ptpov_w1128.rmdl", "EVA-8",},
{"mdl/weapons/peacekeeper/ptpov_peacekeeper.rmdl", "Peacekeeper",},
{"mdl/weapons/pstl_sa3/ptpov_pstl_sa3.rmdl", "Mosambik",},
{"mdl/weapons/compound_bow/ptpov_compound_bow.rmdl", "Bocek"},
};

LongbowAttachments longbowAttachments = LongbowAttachments();
LongbowAttachmentValues longbowAttachmentValues = LongbowAttachmentValues();
ChargeRifleAttachments chargeRifleAttachments = LongbowAttachments();
ChargeRifleAttachmentValues chargeRifleAttachmentValues = LongbowAttachmentValues();
SentinelAttachments sentinelAttachments = SentinelAttachments();
SentinelAttachmentValues sentinelAttachmentValues = SentinelAttachmentValues();
AlternatorAttachments alternatorAttachments = AlternatorAttachments();
AlternatorAttachmentValues alternatorAttachmentValues = AlternatorAttachmentValues();
R99Attachments r99Attachments = R99Attachments();
R99AttachmentValues r99AttachmentValues = R99AttachmentValues();
R301Attachments r301Attachments = R301Attachments();
R301AttachmentValues r301AttachmentValues = R301AttachmentValues();
P2020Attachments p2020Attachments = P2020Attachments();
P2020AttachmentValues p2020AttachmentValues = P2020AttachmentValues();
RE45Attachments re45Attachments = RE45Attachments();
RE45AttachmentValues re45AttachmentValues = RE45AttachmentValues();
FlatlineAttachments flatlineAttachments = FlatlineAttachments();
FlatlineAttachmentValues flatlineAttachmentValues = FlatlineAttachmentValues();
HemlokAttachments hemlokAttachments = HemlokAttachments();
HemlokAttachmentValues hemlokAttachmentValues = HemlokAttachmentValues();
ProwlerAttachments prowlerAttachments = ProwlerAttachments();
ProwlerAttachmentValues prowlerAttachmentValues = ProwlerAttachmentValues();
WingmanAttachments wingmanAttachments = WingmanAttachments();
WingmanAttachmentValues wingmanAttachmentValues = WingmanAttachmentValues();
ThirtyThirtyAttachments thirtyThirtyAttachments = ThirtyThirtyAttachments();
ThirtyThirtyAttachmentValues thirtyThirtyAttachmentValues = ThirtyThirtyAttachmentValues();
RampageAttachments rampageAttachments = RampageAttachments();
RampageAttachmentValues rampageAttachmentValues = RampageAttachmentValues();
CARAttachments carAttachments = CARAttachments();
CARAttachmentValues carAttachmentValues = CARAttachmentValues();
LStarAttachments lStarAttachments = LStarAttachments();
LStarAttachmentValues lStarAttachmentValues = LStarAttachmentValues();
HavocAttachments havocAttachments = HavocAttachments();
HavocAttachmentValues havocAttachmentValues = HavocAttachmentValues();
DevotionAttachments devotionAttachments = DevotionAttachments();
DevotionAttachmentValues devotionAttachmentValues = DevotionAttachmentValues();
TripleTakeAttachments tripleTakeAttachments = TripleTakeAttachments();
TripleTakeAttachmentValues tripleTakeAttachmentValues = TripleTakeAttachmentValues();
BocekAttachments bocekAttachments = BocekAttachments();
BocekAttachmentValues bocekAttachmentValues = BocekAttachmentValues();
G7ScoutAttachments g7ScoutAttachments = G7ScoutAttachments();
G7ScoutAttachmentValues g7ScoutAttachmentValues = G7ScoutAttachmentValues();
VoltAttachments voltAttachments = VoltAttachments();
VoltAttachmentValues voltAttachmentValues = VoltAttachmentValues();
SpitfireAttachments spitfireAttachments = SpitfireAttachments();
SpitfireAttachmentValues spitfireAttachmentValues = SpitfireAttachmentValues();
MastiffAttachments mastiffAttachments = MastiffAttachments();
MastiffAttachmentValues mastiffAttachmentValues = MastiffAttachmentValues();
EVA8Attachments eva8Attachments = EVA8Attachments();
EVA8AttachmentValues eva8AttachmentValues = EVA8AttachmentValues();
PeacekeeperAttachments peacekeeperAttachments = PeacekeeperAttachments();
PeacekeeperAttachmentValues peacekeeperAttachmentValues = PeacekeeperAttachmentValues();
MozambiqueAttachments mozambiqueAttachments = MozambiqueAttachments();
MozambiqueAttachmentValues mozambiqueAttachmentValues = MozambiqueAttachmentValues();

std::list<ItemBase> itemList = {
	ExtendedSniperMagGold(),
	ExtendedSniperMagWhite(),
	ExtendedSniperMagBlue(),
	ExtendedSniperMagPurple(),
	SniperStockWhite(),
	SniperStockBlue(),
	SniperStockPurple(),
	DeadeyesTempoPurple(),
	StabilizerWhite(),
	StabilizerBlue(),
	StabilizerPurple(),
	TwoXFourAOG(),
	SixXSniper(),
	FourXSixSniper(),
	FourXTenDigital(),
	OneXHCOG(),
	TwoXHCOG(),
	OneXHOLO(),
	OneXTwoXHOLO(),
	ThreeXHCOG(),
	OneXDigital(),
	LongbowWepaon(),
	ChargeRifleWeapon(),
	SentinelWeapon(),
	SniperAmmo(),
	ArcstarGrenade(),
	FragGrenade(),
	ThermiteGrenade(),
	ShieldCellHealing(),
	ShieldBatteryHealing(),
	SyringeHealing(),
	MedKitHealing(),
	PhoenixKitHealing(),
	UltimateAccelerantSurvivalItems(),
	MobileRespawnerSurvivalItems(),
	HeatshieldSurvivalItems(),
	BodyShieldGold(),
	BodyShieldPurple(),
	BodyShieldBlue(),
	BodyShieldWhite(),
	EvoShieldRed(),
	EvoShieldPurple(),
	EvoShieldBlue(),
	EvoShieldWhite(),
	HelmetGold(),
	HelmetPurple(),
	HelmetBlue(),
	HelmetWhite(),
	BackpackGold(),
	BackpackPurple(),
	BackpackBlue(),
	BackpackWhite(),
	KnockdownShieldGold(),
	KnockdownShieldPurple(),
	KnockdownShieldBlue(),
	KnockdownShieldWhite(),
	HammerpointHopup(),
	StandardStockPurple(),
	StandardStockBlue(),
	StandardStockWhite(),
	StabilizerWhite(),
	ExtendedLightMagGold(),
	ExtendedLightMagPurple(),
	ExtendedLightMagBlue(),
	ExtendedLightMagWhite(),
	AlternatorWeapon(),
	R99Weapon(),
	R301Weapon(),
	P2020Weapon(),
	RE45Weapon(),
	LightAmmo(),
	BoostedLoaderHopup(),
	ShatterCapsHopup(),
	ExtendedHeavyMagGold(),
	ExtendedHeavyMagPurple(),
	ExtendedHeavyMagBlue(),
	ExtendedHeavyMagWhite(),
	DualShellHopup(),
	FlatlineWeapon(),
	HemlokWeapon(),
	ProwlerWeapon(),
	WingmanWeapon(),
	ThirtyThirtyWeapon(),
	RampageWeapon(),
	CARWeapon(),
	HeavyAmmo(),
	KineticFeederHopup(),
	TurbochargerHopup(),
	ExtendedEnergyMagGold(),
	ExtendedEnergyMagPurple(),
	ExtendedEnergyMagBlue(),
	ExtendedEnergyMagWhite(),
	LStarWeapon(),
	HavocWeapon(),
	DevotionWeapon(),
	TripleTakeWeapon(),
	EnergyAmmo(),
	ArrowAmmo(),
	BocekWeapon(),
	KraberWeapon(),
	G7ScoutWeapon(),
	VoltWeapon(),
	SpitfireWeapon(),
	ShotgunboltPurple(),
	ShotgunboltBlue(),
	ShotgunboltWhite(),
	MastiffWeapon(),
	EVA8Weapon(),
	PeacekeeperWeapon(),
	MozambiqueWeapon(),
	ShotgunShells()
};

// setzt WeaponNameIndex und modbitfield der jeweiligen Waffe - für Smart Item ESP
string myWeaponIndex1 = "";
string myWeaponIndex2 = "";
int myModBitField1 = 0;
int myModBitField2 = 0;

// für Smart-Items
int currentEvoShieldType = 0;
int currentHelmetType = 0;

void Overlay::SetCurrentWeapon(string weaponIndex1, string weaponIndex2, int modBitField1, int modBitField2) {
	myWeaponIndex1 = weaponIndex1;
	myWeaponIndex2 = weaponIndex2;
	myModBitField1 = modBitField1;
	myModBitField2 = modBitField2;
}

void Overlay::SetShieldHelmet(int shieldType, int helmetType) {
	currentEvoShieldType = shieldType;
	currentHelmetType = helmetType;
}

void DrawEsp() {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (Config.DrawFoV)
	{
		DrawCircle((windowWH.x / 2), (windowWH.y / 2), Config.Fov * 10, 1, 50, 0xffffffff);
	}

	if (Config.enableESP) {
		for (int i = 0; i < 61; i++) {

			if (playerBase[i].realDistance == 0.f || playerBase[i].centity == 0 || playerBase[i].localPlayer == 0 || !playerBase[i].isPlayer || !playerBase[i].isEnemy ||
				playerBase[i].w2sHead.X == 0 || playerBase[i].w2sHead.Y == 0 || playerBase[i].w2sHead.Z == 0 || playerBase[i].w2sBase.Z == 0) {

			}
			else {

				if (playerBase[i].centity != 0 && playerBase[i].localPlayer != playerBase[i].centity && playerBase[i].isPlayer && playerBase[i].isEnemy) {
					if (playerBase[i].distance > 0 && playerBase[i].realDistance < Config.maxDistance) {
						if ((playerBase[i].w2sHead.X < screenWidth || playerBase[i].w2sHead.Y < screenHeight) && ((playerBase[i].w2sHead.X > 0 && playerBase[i].w2sHead.Y > 0) && (playerBase[i].w2sHead.Z > 0 && playerBase[i].w2sBase.Z > 0))) {
							if (playerBase[i].visible) {
								//DrawBox(ImColor(255.f / 255, 0.f, 0.f, 1.f), w2sHead.X - (box_width / 2), w2sBase.Y, box_width, box_height);
								DrawBorderBox(playerBase[i].middle, playerBase[i].w2sHead.Y, playerBase[i].width, playerBase[i].height, playerBase[i].boxThickness, D3DCOLOR_ARGB(255, 245, 103, 145));
							}
							else {
								//DrawBox(ImColor(0.f, 0.f, 255.f / 255, 1.f), w2sHead.X - (box_width / 2), w2sBase.Y, box_width, box_height);
								DrawBorderBox(playerBase[i].middle, playerBase[i].w2sHead.Y, playerBase[i].width, playerBase[i].height, playerBase[i].boxThickness, D3DCOLOR_ARGB(255, 0, 38, 255));
							}

							if (Config.showNames) {
								DrawString(playerBase[i].name.c_str(), playerBase[i].middle, playerBase[i].w2sHead.Y - 20, D3DCOLOR_ARGB(255, 245, 103, 145), pBoldFont);
							}

							if (Config.showDistance) {
								char dist[20];
								sprintf_s(dist, "%d m", static_cast<int>(playerBase[i].distance / 40));
								if (Config.showDistance) {
									DrawString(dist, playerBase[i].middle, playerBase[i].w2sBase.Y + 23, D3DCOLOR_ARGB(255, 245, 103, 145), pBoldFont);
								}
							}

							if (Config.showKnocked) {
								if (playerBase[i].isDown) {
									DrawString("KNOCKED", playerBase[i].middle, playerBase[i].w2sHead.Y - 40, D3DCOLOR_ARGB(255, 191, 6, 6), pBoldFont);
								}
							}

							//if (!playerBase[i].modelName.empty()) {
							//	string realModelName = "";
							//	if (playerBase[i].modelName.find("bloodhound") != std::string::npos) {
							//		realModelName = "Bloodhound";
							//	} else if (playerBase[i].modelName.find("gibraltar") != std::string::npos) {
							//		realModelName = "Gibraltar";
							//	} else if (playerBase[i].modelName.find("lifeline") != std::string::npos) {
							//		realModelName = "Lifeline";
							//	}
							//	else if (playerBase[i].modelName.find("pathfinder") != std::string::npos) {
							//		realModelName = "Pathfinder";
							//	}
							//	else if (playerBase[i].modelName.find("wraith") != std::string::npos) {
							//		realModelName = "Wraith";
							//	}
							//	else if (playerBase[i].modelName.find("bangalore") != std::string::npos) {
							//		realModelName = "Bangalore";
							//	}
							//	else if (playerBase[i].modelName.find("caustic") != std::string::npos) {
							//		realModelName = "Caustic";
							//	}
							//	else if (playerBase[i].modelName.find("holo") != std::string::npos) {
							//		realModelName = "Mirage";
							//	}
							//	else if (playerBase[i].modelName.find("stim") != std::string::npos) {
							//		realModelName = "Octane";
							//	}
							//	else if (playerBase[i].modelName.find("wattson") != std::string::npos) {
							//		realModelName = "Wattson";
							//	}
							//	else if (playerBase[i].modelName.find("crypto") != std::string::npos) {
							//		realModelName = "Crypto";
							//	}
							//	else if (playerBase[i].modelName.find("revenant") != std::string::npos) {
							//		realModelName = "Revenant";
							//	}
							//	else if (playerBase[i].modelName.find("loba") != std::string::npos) {
							//		realModelName = "Loba";
							//	}
							//	else if (playerBase[i].modelName.find("rampart") != std::string::npos) {
							//		realModelName = "Rampart";
							//	}
							//	else if (playerBase[i].modelName.find("nova") != std::string::npos) {
							//		realModelName = "Horizon";
							//	}
							//	else if (playerBase[i].modelName.find("fuse") != std::string::npos) {
							//		realModelName = "Fuse";
							//	}
							//	else if (playerBase[i].modelName.find("valkyrie") != std::string::npos) {
							//		realModelName = "Valkyrie";
							//	}
							//	else if (playerBase[i].modelName.find("seer") != std::string::npos) {
							//		realModelName = "Seer";
							//	}
							//	else if (playerBase[i].modelName.find("ash") != std::string::npos) {
							//		realModelName = "Ash";
							//	}
							//	else if (playerBase[i].modelName.find("madmaggie") != std::string::npos) {
							//		realModelName = "Mad Maggie";
							//	}

							//	DrawString(realModelName.c_str(), playerBase[i].middle, playerBase[i].w2sHead.Y - 30, D3DCOLOR_ARGB(255, 245, 103, 145), pBoldFont);
							//}

							D3DCOLOR shieldColor = D3DCOLOR_ARGB(255, 255, 255, 255);
							if (playerBase[i].armorType == 1) {
								shieldColor = D3DCOLOR_ARGB(255, 255, 255, 255);
							}
							else if (playerBase[i].armorType == 2) {
								shieldColor = D3DCOLOR_ARGB(255, 65, 149, 232);
							}
							else if (playerBase[i].armorType == 3) {
								shieldColor = D3DCOLOR_ARGB(255, 160, 2, 222);
							}
							else if (playerBase[i].armorType == 4) {
								shieldColor = D3DCOLOR_ARGB(255, 242, 235, 31);
							}
							else if (playerBase[i].armorType == 5) {
								shieldColor = D3DCOLOR_ARGB(255, 207, 4, 4);
							}

							DrawBorderBox(playerBase[i].middle - 1, playerBase[i].w2sBase.Y + 6, playerBase[i].width + 2, 8, 1, D3DCOLOR_ARGB(255, 0, 0, 0));
							DrawFilledRectangle(playerBase[i].middle, playerBase[i].w2sBase.Y + 8, (playerBase[i].width / float(playerBase[i].sMaxHealth) * (float)playerBase[i].shealth), 6, shieldColor);

							DrawBorderBox(playerBase[i].middle - 1, playerBase[i].w2sBase.Y + 15, playerBase[i].width + 2, 8, 1, D3DCOLOR_ARGB(255, 0, 0, 0));
							DrawFilledRectangle(playerBase[i].middle, playerBase[i].w2sBase.Y + 17, (playerBase[i].width / float(100) * (float)playerBase[i].health), 6, D3DCOLOR_ARGB(255, 0, 219, 44));
						}
					}
				}
			}
		}
	}
}

void SeparatePanel(const char* panelTitle, ImVec2 controlLocation = ImGui::GetWindowPos(), float cursorPosY = 30.0f)
{
	ImVec4 vecColorWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 vecColorDarkRed = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
	ImU32 imColorWhite = ImGui::ColorConvertFloat4ToU32(vecColorWhite);
	ImU32 imColorDarkRed = ImGui::ColorConvertFloat4ToU32(vecColorDarkRed);
	ImGui::Text(panelTitle);
	ImGui::SetCursorPosY(cursorPosY);
}

void Overlay::AimbotMenu() {
	SeparatePanel("Aimbot Panel");
	ImGui::BeginChild("Slider");

	ImGui::Checkbox("Enable Aimbot", &Config.bAimbot);
	ImGui::Checkbox("Visibility Check", &Config.visibilityCheck);
	ImGui::SliderFloat("Max FoV", &Config.Fov, 5.f, 90.f);
	ImGui::Checkbox("Draw FoV", &Config.DrawFoV);
	ImGui::SliderFloat("Smootheness ", &Config.smoothness, 1.f, 100.f);
	ImGui::Checkbox("Triggerbot", &Config.enableTriggerbot);

	ImGui::SameLine();
	ImGui::EndChild();
}

void Overlay::ESPMenu() {
	SeparatePanel("Visual Customization Panel");
	ImGui::BeginChild("Slider");

	ImGui::Checkbox("Show knocked ", &Config.showKnocked);
	ImGui::Checkbox("Show names ", &Config.showNames);
	ImGui::Checkbox("Show distance ", &Config.showDistance);
	ImGui::SliderFloat("Maximum distance", &Config.maxDistance, 100.f, 800.f);

	ImGui::SameLine();
	ImGui::EndChild();
}

std::string RandomString(const int len)
{
	const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

	std::string str(len, 0);
	for (auto& it : str)
		it = alpha_numeric[distribution(generator)];

	return str;
}

bool Overlay::DirectXInit()
{
	// initialize directx
	while (!overlayWindow) {}

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		return false;

	GetClientRect(hWnd, &rc);

	windowWH = { rc.right - rc.left, rc.bottom - rc.top };

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = overlayWindow;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = windowWH.x;
	p_Params.BackBufferHeight = windowWH.y;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlayWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
		return false;

	D3DXCreateLine(p_Device, &p_Line);

	D3DXCreateFont(p_Device, 50, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Helvetica", &pFont); // Create the font used for text rendering
	D3DXCreateFont(p_Device, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Helvetica", &pESPFont); // Create the font used for esp rendering
	D3DXCreateFont(p_Device, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Helvetica", &pItemFont); // Create the font used for text rendering
	D3DXCreateFont(p_Device, 14, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Helvetica", &pBoldFont); // Create the font used for text rendering

	if (FAILED(D3DXCreateTextureFromFileInMemory(p_Device, kskPng, sizeof(kskPng), &ksk)))
		return false;

	if (FAILED(D3DXCreateTextureFromFileInMemory(p_Device, unknownController, sizeof(unknownController), &unknownCtrl)))
		return false;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	// add default font and merge fontawesome icons
	//io.Fonts->AddFontFromMemoryTTF(comfortaaRegular, sizeof(comfortaaRegular), 13.f);
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Ruda-Bold.ttf", 12);

	// you can uncomment this if you want to load the icon font/bold font
	//static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	//ImFontConfig icons_config;
	//icons_config.MergeMode = true;
	//icons_config.PixelSnapH = true;
	//icons_config.GlyphOffset = ImVec2(0.f, 2.f);
	//io.Fonts->AddFontFromMemoryTTF(font_awesome_data, sizeof(font_awesome_data), 16.f, &icons_config, icons_ranges); // icons font

	//// add title font and merge fontawesome icons
	//ImFontConfig titleConfig;
	//titleConfig.GlyphOffset = ImVec2(0.f, -2.f);
	//titleFont = io.Fonts->AddFontFromMemoryTTF(comfortaaBold, sizeof(comfortaaBold), 19.f, &titleConfig); // bold font

	//io.Fonts->AddFontFromMemoryTTF(font_awesome_data, sizeof(font_awesome_data), 21.f, &icons_config, icons_ranges);

	//// add big font and merge fontawesome icons
	//bigFont = io.Fonts->AddFontFromMemoryTTF(comfortaaRegular, sizeof(comfortaaRegular), 16.f);

	//icons_config.GlyphOffset = ImVec2(0.f, 1.f);
	//io.Fonts->AddFontFromMemoryTTF(font_awesome_data, sizeof(font_awesome_data), 18.f, &icons_config, icons_ranges);

	ImGui_ImplWin32_Init(overlayWindow);
	ImGui_ImplDX9_Init(p_Device);

	return true;
}

void DirectXShutdown()
{
	// destroy everything
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();

	p_Object->Release();
	p_Device->Release();
	pFont->Release();
	pESPFont->Release();
	p_Line->Release();

	DestroyWindow(overlayWindow);
}

// winprochandler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;

	case WM_DESTROY:
		DirectXShutdown();
		PostQuitMessage(0);
		return 0;
		break;

	default:
		return DefWindowProcW(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void HandleMessages(std::wstring lClassName, std::wstring lWindowName)
{
	// create the window and set window attributes
	overlayWindow = CreateWindowExW(/*WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED*/NULL, lClassName.c_str(), lWindowName.c_str(), WS_POPUP | WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0, 0, 0, 0);
	SetWindowLongA(overlayWindow, GWL_EXSTYLE, (WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT));
	DwmExtendFrameIntoClientArea(overlayWindow, &margin);
	ShowWindow(overlayWindow, SW_SHOW);
	UpdateWindow(overlayWindow);

	while (true)
	{
		if (PeekMessageW(&message, overlayWindow, 0, 0, PM_REMOVE))
		{
			DispatchMessageW(&message);
			TranslateMessage(&message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hWnd)
		{
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(overlayWindow, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		Sleep(1);
	}
}

bool Overlay::InitWindow(HWND apexhwnd) {
	// create a window class
	std::string r1 = RandomString(16);
	std::string r2 = RandomString(16);

	std::wstring lClassName = std::wstring(r1.begin(), r1.end());
	std::wstring lWindowName = std::wstring(r2.begin(), r2.end());

	WNDCLASSEXW wClass;
	wClass.cbSize = sizeof(WNDCLASSEXW);
	wClass.style = 0;
	wClass.lpfnWndProc = WinProc;
	wClass.cbClsExtra = NULL;
	wClass.cbWndExtra = NULL;
	wClass.hInstance = nullptr;
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hbrBackground = nullptr;
	wClass.lpszMenuName = lWindowName.c_str();
	wClass.lpszClassName = lClassName.c_str();
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);

	if (!RegisterClassExW(&wClass))
		return false;

	std::thread msgThread(HandleMessages, lClassName, lWindowName);
	msgThread.detach();

	hWnd = apexhwnd;

	return true;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	g_d3dpp.hDeviceWindow = hWnd;
	g_d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	g_d3dpp.BackBufferCount = 1;
	g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	g_d3dpp.BackBufferWidth = 0;
	g_d3dpp.BackBufferHeight = 0;
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

int actualTab = 0;

void ESPMenuPanel() {
	ImGui::BeginChild("ESP");
	ImGui::Spacing();
	ImGui::Text("Visuals");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Enable ESP", &Config.enableESP);
	
	ImGui::SliderFloat("ESP Distance", &Config.maxDistance, 50, 900);
	ImGui::Checkbox("Show knocked", &Config.showKnocked);
	ImGui::Checkbox("Show names", &Config.showNames);
	ImGui::Checkbox("Show distance", &Config.showDistance);

	ImGui::EndChild();
}

void AimbotMenuPanel() {
	ImGui::BeginChild("Aimbot");
	ImGui::Spacing();
	ImGui::Text("Aim configuration");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Enable Aimbot", &Config.bAimbot);

	ImGui::SliderFloat("Aim-FOV", &Config.Fov, 1, 90);
	ImGui::Checkbox("Draw Fov", &Config.DrawFoV);
	ImGui::SliderFloat("Smootheness", &Config.smoothness, 1, 100);
	ImGui::SliderFloat("Max Aim distance", &Config.maxAimDistance, 10, 500);
	ImGui::Checkbox("Triggerbot", &Config.enableTriggerbot);

	ImGui::EndChild();
}

void ItemESPPanel() {
	ImGui::BeginChild("Item ESP");
	ImGui::Spacing();
	ImGui::Text("Configurate Item ESP");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Enable Item ESP", &Config.enableItemESP);
	ImGui::Checkbox("Enable Smart Item ESP", &Config.enableSmartItemESP);

	ImGui::SliderFloat("Item ESP Distance", &Config.maxItemDistance, 10, 200);

	ImGui::EndChild();
}

void SaveSettingsPanel() {
	Configuration::WriteToConfigFile();
}

void LoadSettingsPanel() {
	Configuration::UpdateConfigFromFile();
}

void ShowMenu() {

#pragma region Styling
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
#pragma endregion

	ImGui::SetNextWindowSize(ImVec2(600, 700));
	ImGui::Begin("Apex Legends Cheese", (bool*)0, 0);
	/*ImGui::Checkbox("ESP", &MenuSettings::espEnabled);
	ImGui::Checkbox("Snaplines", &MenuSettings::snaplinesEnabled);
	ImGui::Checkbox("Healthbar", &MenuSettings::healthbarEnabled);
	ImGui::Checkbox("Glow ESP", &MenuSettings::glowEnabled);*/

	if (ImGui::Button("ESP", ImVec2(100.f, 0.f))) {
		actualTab = 0;
	}

	ImGui::SameLine(0.0, 2.0f);

	if (ImGui::Button("Aimbot", ImVec2(100.0f, 0.0f))) {
		actualTab = 1;
	}

	ImGui::SameLine(0.0, 2.0f);

	if (ImGui::Button("Item ESP", ImVec2(100.0f, 0.0f))) {
		actualTab = 2;
	}

	if (ImGui::Button("Save settings", ImVec2(100.0f, 0.0f))) {
		SaveSettingsPanel();
	}

	ImGui::SameLine(0.0, 2.0f);

	if (ImGui::Button("Load settings", ImVec2(100.0f, 0.0f))) {
		LoadSettingsPanel();
	}

	switch (actualTab) {
	case 0:
		ESPMenuPanel();
		break;
	case 1:
		AimbotMenuPanel();
		break;
	case 2:
		ItemESPPanel();
		break;
	}

	/*ImGui::Checkbox("Show knocked", &Config.showKnocked);
	ImGui::Checkbox("Show distance", &Config.showDistance);
	ImGui::SliderFloat("Max FoV", &Config.Fov, 5.f, 90.f);
	ImGui::Checkbox("Draw FoV", &Config.DrawFoV);
	ImGui::SliderFloat("Smootheness ", &Config.smoothness, 1.f, 100.f);
	ImGui::SliderFloat("Maximum distance", &Config.maxDistance, 100.f, 800.f);*/

	ImGui::Spacing();

	//ImGui::Checkbox("No Recoil", &MenuSettings::noRecoilEnabled);

	ImGui::Spacing();

	/*ImGui::Checkbox("Aimbot", &MenuSettings::aimbotEnabled);
	ImGui::SliderInt("Aimbot Smoothness", &MenuSettings::aimbotSmoothness, 1, 15);
	ImGui::Checkbox("Aimbot FOV Circle", &MenuSettings::fovCircle);
	ImGui::SliderInt("Aimbot FOV", &MenuSettings::aimbotFOV, 10, 500);*/

	ImGui::Spacing();

	ImGui::End();
}

bool IsWindowIngame = false;

void InputHandler() {
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;
	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;
	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}

void DrawImGui(LONG menu, LONG ingame)
{
	// pass input to imgui
	InputHandler();

	// create an imgui frame

	// set the right window flags

	if (GetAsyncKeyState(VK_INSERT))
	{
		menuActive = !menuActive;
		Sleep(100);
	}

	if (menuActive) {
		SetWindowLongA(overlayWindow, GWL_EXSTYLE, (menu));
		IsWindowIngame = false;
	} else {
		if (!IsWindowIngame) {
			SetWindowLongA(overlayWindow, GWL_EXSTYLE, (ingame));
			IsWindowIngame = true;
		}
	}

	// MENU
	if (menuActive) {
		ShowMenu();
	}
}

void Overlay::InitVariables(Driver* driv, Driver::Module mod) {
	myDriver = driv;
	myModule = mod;
}

void Overlay::GetDriverData() {
	/*Matrix myMatrix = GetMatrix(myDriver, myModule);
	Overlay::RenderEsp(1, myMatrix);*/
}

void Overlay::SetPlayerBase(PlayerData newPlayerBase[62]) {
	for (int i = 0; i < 62; i++) {
		playerBase[i] = newPlayerBase[i];
	}
}

void Overlay::SetItemBase(ItemData newPlayerBase[66001], int startIndex, int endIndex) {
	for (int i = startIndex; i < endIndex; i++) {
		itemBase[i] = newPlayerBase[i];
	}
}

void DeviceEndScenePresentEx() {
	p_Device->EndScene();
	p_Device->PresentEx(0, 0, 0, 0, 0);
}

void DrawListPushCliptRectFullScreen(ImDrawList* drawList) {
	drawList->PushClipRectFullScreen();
}

void DeviceClearBeginScene() {
	p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.f, 0);
	p_Device->BeginScene();
}

IWeaponAttachments GetWeaponAttachmentFromName(std::string weaponName) {
	IWeaponAttachments returnWeapon;

	if (weaponName == "Longbow") {
		returnWeapon = longbowAttachments;
	}
	else if (weaponName == "Elektrogewehr") {
		returnWeapon = chargeRifleAttachments;
	}
	else if (weaponName == "Sentinel") {
		returnWeapon = sentinelAttachments;
	}
	else if (weaponName == "Alternator") {
		returnWeapon = alternatorAttachments;
	}
	else if (weaponName == "R99") {
		returnWeapon = r99Attachments;
	}
	else if (weaponName == "R301") {
		returnWeapon = r301Attachments;
	}
	else if (weaponName == "P2020") {
		returnWeapon = p2020Attachments;
	}
	else if (weaponName == "RE-45") {
		returnWeapon = re45Attachments;
	}
	else if (weaponName == "Flatline") {
		returnWeapon = flatlineAttachments;
	}
	else if (weaponName == "Hemlok") {
		returnWeapon = hemlokAttachments;
	}
	else if (weaponName == "Prowler") {
		returnWeapon = prowlerAttachments;
	}
	else if (weaponName == "Wingman") {
		returnWeapon = wingmanAttachments;
	}
	else if (weaponName == "30-30") {
		returnWeapon = thirtyThirtyAttachments;
	}
	else if (weaponName == "Rampage") {
		returnWeapon = rampageAttachments;
	}
	else if (weaponName == "C.A.R") {
		returnWeapon = carAttachments;
	}
	else if (weaponName == "L-Star") {
		returnWeapon = lStarAttachments;
	}
	else if (weaponName == "Havoc") {
		returnWeapon = havocAttachments;
	}
	else if (weaponName == "Devotion") {
		returnWeapon = devotionAttachments;
	}
	else if (weaponName == "Triple Take") {
		returnWeapon = tripleTakeAttachments;
	}
	else if (weaponName == "Bocek") {
		returnWeapon = bocekAttachments;
	}
	else if (weaponName == "G7-Scout") {
		returnWeapon = g7ScoutAttachments;
	}
	else if (weaponName == "Volt") {
		returnWeapon = voltAttachments;
	}
	else if (weaponName == "Spitfire") {
		returnWeapon = spitfireAttachments;
	}
	else if (weaponName == "Mastiff") {
		returnWeapon = mastiffAttachments;
	}
	else if (weaponName == "EVA-8") {
		returnWeapon = eva8Attachments;
	}
	else if (weaponName == "Peacekeeper") {
		returnWeapon = peacekeeperAttachments;
	}
	else if (weaponName == "Mosambik") {
		returnWeapon = mozambiqueAttachments;
	}

	return returnWeapon;
}

bool IsItemBetterThanBefore(std::list<ItemBase>::iterator itemBase, IWeaponAttachments weapon) {
	bool isExtendedMagSniper = itemBase->type == ItemType::ExtendedMagSniper;
	bool isSniperStock = itemBase->type == ItemType::SniperStock;
	bool isDeadeyesTempoWeaponHopup = itemBase->type == ItemType::DeadeyesTempoWeaponHopup;
	bool isStabilizer = itemBase->type == ItemType::Stabilizer;
	bool isSniperScope = itemBase->type == ItemType::SniperScope;
	bool isARSniperScope = itemBase->type == ItemType::ARSniperScope;
	bool isStandardScope = itemBase->type == ItemType::StandardScope;
	bool isDigitalScope = itemBase->type == ItemType::DigitalScope;
	bool isWeaponAR = itemBase->type == ItemType::WeaponAR;
	bool isGrenade = itemBase->type == ItemType::Grenade;
	bool isHealing = itemBase->type == ItemType::Healing;
	bool isSurvivalItems = itemBase->type == ItemType::SurvivalItems;
	bool isEvoShield = itemBase->type == ItemType::EvoShield;
	bool isHelmet = itemBase->type == ItemType::Helmet;
	bool isBackpack = itemBase->type == ItemType::Backpack;
	bool isKnockdownShield = itemBase->type == ItemType::KnockdownShield;
	bool isStandardStock = itemBase->type == ItemType::StandardStock;
	bool isExtendedLightMag = itemBase->type == ItemType::ExtendedLightMag;
	bool isLightAmmo = itemBase->type == ItemType::LightAmmo;
	bool isBoostedLoader = itemBase->type == ItemType::BoostedLoader;
	bool isShatterCaps = itemBase->type == ItemType::ShatterCaps;
	bool isExtendedHeavyMag = itemBase->type == ItemType::ExtendedHeavyMag;
	bool isDualShell = itemBase->type == ItemType::DualShell;
	bool isHeavyAmmo = itemBase->type == ItemType::HeavyAmmo;
	bool isKineticFeeder = itemBase->type == ItemType::KineticFeeder;
	bool isTurbocharger = itemBase->type == ItemType::Turbocharger;
	bool isExtendedEnergyMag = itemBase->type == ItemType::ExtendedEnergyMag;
	bool isEnergyAmmo = itemBase->type == ItemType::EnergyAmmo;
	bool isArrow = itemBase->type == ItemType::Arrow;
	bool isShotgunBolt = itemBase->type == ItemType::ShotgunBolt;
	bool isShotgunShells = itemBase->type == ItemType::ShotgunShells;
	bool isWeaponSMG = itemBase->type == ItemType::WeaponSMG;
	bool isWeaponLMG = itemBase->type == ItemType::WeaponLMG;
	bool isWeaponMarksman = itemBase->type == ItemType::WeaponMarksman;
	bool isWeaponSniperRifle = itemBase->type == ItemType::WeaponSniperRifle;
	bool isWeaponShotguns = itemBase->type == ItemType::WeaponShotguns;
	bool isWeaponPistols = itemBase->type == ItemType::WeaponPistols;
	bool isSniperAmmo = itemBase->type == ItemType::SniperAmmo;
	bool isHammerPoint = itemBase->type == ItemType::HammerPoint;

	if (isExtendedMagSniper && weapon.canHaveSniperAmmo && weapon.canHaveMag) {
		bool isItemGold = itemBase->rareColor == colorGoldItem;
		bool isItemPurple = itemBase->rareColor == colorPurpleItem;
		bool isItemBlue = itemBase->rareColor == colorBlueItem;
		bool isItemWhite = itemBase->rareColor == colorWhiteItem;

		if (isItemGold && weapon.goldMag) {
			return false;
		}
		if (isItemPurple && (weapon.goldMag || weapon.purpleMag)) {
			return false;
		}
		if (isItemBlue && (weapon.goldMag || weapon.purpleMag || weapon.blueMag)) {
			return false;
		}
		if (isItemWhite && (weapon.goldMag || weapon.purpleMag || weapon.blueMag || weapon.whiteMag)) {
			return false;
		}

		return true;
	}
	else if (isExtendedMagSniper) {
		return false;
	}

	if (isSniperStock && weapon.isSniperStock) {
		bool purpleStock = itemBase->rareColor == colorPurpleItem;
		bool blueStock = itemBase->rareColor == colorBlueItem;
		bool whiteStock = itemBase->rareColor == colorWhiteItem;

		if (purpleStock && (weapon.purpleStock)) {
			return false;
		}
		if (blueStock && (weapon.purpleStock || weapon.blueStock)) {
			return false;
		}
		if (whiteStock && (weapon.purpleStock || weapon.blueStock || weapon.whiteStock)) {
			return false;
		}
		return true;
	}
	else if (isSniperStock) {
		return false;
	}

	if (isDeadeyesTempoWeaponHopup && weapon.canHaveDeadEyesTempo) {
		if (weapon.deadEyesTempo) {
			return false;
		}
		return true;
	}
	else if (isDeadeyesTempoWeaponHopup) {
		return false;
	}

	if (isStabilizer && weapon.canHaveStabi && !weapon.canHaveShotgunAmmo) {
		bool purpleStabilizer = itemBase->rareColor == colorPurpleItem;
		bool blueStabilizer = itemBase->rareColor == colorBlueItem;
		bool whiteStabilizer = itemBase->rareColor == colorWhiteItem;

		if (purpleStabilizer && (weapon.purpleStabi)) {
			return false;
		}
		if (blueStabilizer && (weapon.purpleStabi || weapon.blueStabi)) {
			return false;
		}
		if (whiteStabilizer && (weapon.purpleStabi || weapon.blueStabi || weapon.whiteStabi)) {
			return false;
		}

		return true;
	}
	else if (isStabilizer) {
		return false;
	}

	if (isSniperScope && weapon.canHaveSniperScope) {
		return true;
	}
	else if (isSniperScope) {
		return false;
	}

	if (isARSniperScope && (weapon.canHaveTwoXFourScope || weapon.canHaveThreeXScope)) {
		return true;
	}
	else if (isARSniperScope) {
		return false;
	}

	if (isStandardScope) {
		return true;
	}

	if (isDigitalScope && weapon.canHaveDigitalScope) {
		return true;
	}
	else if (isDigitalScope) {
		return false;
	}

	if (isWeaponAR) {
		return true;
	}

	if (isGrenade) {
		return true;
	}

	if (isHealing) {
		return true;
	}

	if (isSurvivalItems) {
		return true;
	}

	if (isEvoShield) {
		bool redEvoShield = itemBase->rareColor == colorRedItem;
		bool goldEvoShield = itemBase->rareColor == colorGoldItem;
		bool purpleEvoShield = itemBase->rareColor == colorPurpleItem;
		bool blueEvoShield = itemBase->rareColor == colorBlueItem;
		bool whiteEvoShield = itemBase->rareColor == colorWhiteItem;

		if (redEvoShield && currentEvoShieldType == 5) {
			return false;
		}
		if (goldEvoShield && currentEvoShieldType == 4) {
			return false;
		}
		if (purpleEvoShield && (currentEvoShieldType >= 3)) {
			return false;
		}
		if (blueEvoShield && (currentEvoShieldType >= 2)) {
			return false;
		}
		if (whiteEvoShield && (currentEvoShieldType >= 1)) {
			return false;
		}

		return true;
	}

	if (isHelmet) {
		bool redHelmet = itemBase->rareColor == colorRedItem;
		bool goldHelmet = itemBase->rareColor == colorGoldItem;
		bool purpleHelmet = itemBase->rareColor == colorPurpleItem;
		bool blueHelmet = itemBase->rareColor == colorBlueItem;
		bool whiteHelmet = itemBase->rareColor == colorWhiteItem;

		if (redHelmet && currentHelmetType == 5) {
			return false;
		}
		if (goldHelmet && currentHelmetType == 4) {
			return false;
		}
		if (purpleHelmet && (currentHelmetType >= 3)) {
			return false;
		}
		if (blueHelmet && (currentHelmetType >= 2)) {
			return false;
		}
		if (whiteHelmet && (currentHelmetType >= 1)) {
			return false;
		}

		return true;
	}

	if (isStandardStock && weapon.canHaveStock && !weapon.isSniperStock) {
		bool purpleStandardStock = itemBase->rareColor == colorPurpleItem;
		bool blueStandardStock = itemBase->rareColor == colorBlueItem;
		bool whiteStandardStock = itemBase->rareColor == colorWhiteItem;

		if (purpleStandardStock && weapon.purpleStock) {
			return false;
		}
		if (blueStandardStock && (weapon.purpleStock || weapon.blueStock)) {
			return false;
		}
		if (whiteStandardStock && (weapon.purpleStock || weapon.blueStock || weapon.whiteStock)) {
			return false;
		}

		return true;
	}
	else if (isStandardStock) {
		return false;
	}

	if (isExtendedLightMag && weapon.canHaveMag && weapon.canHaveLightAmmo) {
		bool goldLightMag = itemBase->rareColor == colorGoldItem;
		bool purpleLightMag = itemBase->rareColor == colorPurpleItem;
		bool blueLightMag = itemBase->rareColor == colorBlueItem;
		bool whiteLightMag = itemBase->rareColor == colorWhiteItem;

		if (goldLightMag && (weapon.goldMag)) {
			return false;
		}
		if (purpleLightMag && (weapon.goldMag || weapon.purpleMag)) {
			return false;
		}
		if (blueLightMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag)) {
			return false;
		}
		if (whiteLightMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag || weapon.whiteMag)) {
			return false;
		}
		return true;
	}
	else if (isExtendedLightMag) {
		return false;
	}

	if (isLightAmmo && weapon.canHaveLightAmmo) {
		return true;
	}
	else if (isLightAmmo) {
		return false;
	}

	if (isBoostedLoader && weapon.canHaveBoostedLoader) {
		if (weapon.boostedLoader) {
			return false;
		}
		return true;
	}
	else if (isBoostedLoader) {
		return false;
	}

	if (isShatterCaps && weapon.canHaveShatterCaps) {
		if (weapon.shatterCaps) {
			return false;
		}
		return true;
	}
	else if (isShatterCaps) {
		return false;
	}

	if (isExtendedHeavyMag && weapon.canHaveHeavyAmmo) {
		bool goldMag = itemBase->rareColor == colorGoldItem;
		bool purpleMag = itemBase->rareColor == colorPurpleItem;
		bool blueMag = itemBase->rareColor == colorBlueItem;
		bool whiteMag = itemBase->rareColor == colorWhiteItem;

		if (goldMag && weapon.goldMag) {
			return false;
		}
		if (purpleMag && (weapon.goldMag || weapon.purpleMag)) {
			return false;
		}
		if (blueMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag)) {
			return false;
		}
		if (whiteMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag || weapon.whiteMag)) {
			return false;
		}
		return true;
	}
	else if (isExtendedHeavyMag) {
		return false;
	}

	if (isDualShell && weapon.canHaveDualShell) {
		if (weapon.dualShell) {
			return false;
		}
		return true;
	}
	else if (isDualShell) {
		return false;
	}

	if (isHeavyAmmo && weapon.canHaveHeavyAmmo) {
		return true;
	}
	else if (isHeavyAmmo) {
		return false;
	}

	if (isKineticFeeder && weapon.canHaveKineticFeeder) {
		if (weapon.kineticFeeder) {
			return false;
		}
		return true;
	}
	else if (isKineticFeeder) {
		return false;
	}

	if (isTurbocharger && weapon.canHaveTurboCharger) {
		if (weapon.turboCharger) {
			return false;
		}
		return true;
	}
	else if (isTurbocharger) {
		return false;
	}

	if (isExtendedEnergyMag && weapon.canHaveEnergyAmmo) {
		bool goldMag = itemBase->rareColor == colorGoldItem;
		bool purpleMag = itemBase->rareColor == colorPurpleItem;
		bool blueMag = itemBase->rareColor == colorBlueItem;
		bool whiteMag = itemBase->rareColor == colorWhiteItem;

		if (goldMag && weapon.goldMag) {
			return false;
		}
		if (purpleMag && (weapon.goldMag || weapon.purpleMag)) {
			return false;
		}
		if (blueMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag)) {
			return false;
		}
		if (whiteMag && (weapon.goldMag || weapon.purpleMag || weapon.blueMag || weapon.whiteMag)) {
			return false;
		}
		return true;
	}
	else if (isExtendedEnergyMag) {
		return false;
	}

	if (isEnergyAmmo && weapon.canHaveEnergyAmmo) {
		return true;
	}
	else if (isEnergyAmmo) {
		return false;
	}

	if (isArrow && weapon.canHaveArrow) {
		return true;
	}
	else if (isArrow) {
		return false;
	}

	if (isShotgunBolt && weapon.canHaveShotgunAmmo) {
		bool purpleBolt = itemBase->rareColor == colorPurpleItem;
		bool blueBolt = itemBase->rareColor == colorBlueItem;
		bool whiteBolt = itemBase->rareColor == colorWhiteItem;

		if (purpleBolt && weapon.purpleStabi) {
			return false;
		}
		if (blueBolt && (weapon.purpleStabi || weapon.blueStabi)) {
			return false;
		}
		if (whiteBolt && (weapon.purpleStabi || weapon.blueStabi || weapon.whiteStabi)) {
			return false;
		}
		return true;
	}
	else if (isShotgunBolt) {
		return false;
	}

	if (isShotgunShells && weapon.canHaveShotgunAmmo) {
		return true;
	}
	else if (isShotgunShells) {
		return false;
	}

	if (isWeaponSMG) {
		return true;
	}

	if (isWeaponLMG) {
		return true;
	}

	if (isWeaponMarksman) {
		return true;
	}

	if (isWeaponSniperRifle) {
		return true;
	}

	if (isWeaponShotguns) {
		return true;
	}

	if (isWeaponPistols) {
		return true;
	}

	if (isSniperAmmo && weapon.canHaveSniperAmmo) {
		return true;
	}
	else if (isSniperAmmo) {
		return false;
	}

	if (isHammerPoint && weapon.canHaveHammerpoint && !weapon.hammerpoint) {
		return true;
	}
	else if (isHammerPoint) {
		return false;
	}
}

void CheckWeaponAndItem(std::list<ItemBase>::iterator itemBase, ItemData* item) {
	bool useWeapon1 = false;
	bool useWeapon2 = false;

	if (!currentWeapons.weapon1.empty())
		useWeapon1 = true;
	if (!currentWeapons.weapon2.empty())
		useWeapon2 = true;

	IWeaponAttachments weapon1 = GetWeaponAttachmentFromName(currentWeapons.weapon1);
	IWeaponAttachments weapon2 = GetWeaponAttachmentFromName(currentWeapons.weapon2);

	bool isItemBetterThanBefore1 = IsItemBetterThanBefore(itemBase, weapon1);
	bool isItemBetterThanBefore2 = IsItemBetterThanBefore(itemBase, weapon2);

	if (!isItemBetterThanBefore1 && !isItemBetterThanBefore2) {
		item->isItem = false;
	}
}

void ItemIDToName(int lootID, ItemData* itemBaseItem) {
	std::ostringstream oss;
	oss << "XLootID " << lootID;
	std::string s = oss.str();

	if (itemBaseItem->name[0] != 'X' && !itemBaseItem->name.empty()) {
		return;
	}

	auto it = std::find(itemList.begin(), itemList.end(), lootID);
	if (it != itemList.end()) {
		bool showItem = true;
		if (Config.enableSmartItemESP) {
			CheckWeaponAndItem(it, itemBaseItem);
		}

		s = it->name;
		itemBaseItem->itemTextColor = it->rareColor;
	}

#pragma region OldSwitchCase Code
	//switch (lootID) {
	//case 221:
	//	s = "Extended Sniper Mag"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 228:
	//	s = "Sniper Stock"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 229:
	//	s = "Sniper Stock"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 230:
	//	s = "Sniper Stock"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 240:
	//	s = "Deadeye's Tempo"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 203:
	//	s = "Barrel Stabilizer"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 204:
	//	s = "Barrel Stabilizer"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 218:
	//	s = "Extended Sniper Mag"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 219:
	//	s = "Extended Sniper Mag"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 220:
	//	s = "Extended Sniper Mag"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 198:
	//	s = "2X-4X AOG"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 199:
	//	s = "6X Sniper"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 200:
	//	s = "4X-6X Sniper"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 201:
	//	s = "4X-10X Digital"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 202:
	//	s = "Barrel Stabilizer"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 192:
	//	s = "1X HCOG"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 193:
	//	s = "2X HCOG"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 194:
	//	s = "1X HOLO"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 195:
	//	s = "1X-2X HOLO"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 197:
	//	s = "3X HCOG"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 58:
	//	s = "Longbow"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 63:
	//	s = "Charge Rifle"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 104:
	//	s = "Sentinel"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 124:
	//	s = "Sniper Ammo"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 191:
	//	s = "Arcstar"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 190:
	//	s = "Frag Grenade"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 189:
	//	s = "Thermite Grenade"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 166:
	//	s = "Shield Cell"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 165:
	//	s = "Shield Battery"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 164:
	//	s = "Syringe"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 163:
	//	s = "Med Kit"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 162:
	//	s = "Phoenix Kit"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 161:
	//	s = "Ultimate Accelerant"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 174:
	//	s = "Body Shield"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 173:
	//	s = "Body Shield"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 172:
	//	s = "Body Shield"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 171:
	//	s = "Body Shield"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 179:
	//	s = "Evo Shield"; // rot
	//	itemBaseItem->itemTextColor = colorRed;
	//	break;
	//case 178:
	//	s = "Evo Shield"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 177:
	//	s = "Evo Shield"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 176:
	//	s = "Evo Shield"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 170:
	//	s = "Helmet"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 169:
	//	s = "Helmet"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 168:
	//	s = "Helmet"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 167:
	//	s = "Helmet"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 188:
	//	s = "Backpack"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 187:
	//	s = "Backpack"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 186:
	//	s = "Backpack"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 185:
	//	s = "Backpack"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 184:
	//	s = "Knockdown Shield"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 183:
	//	s = "Knockdown Shield"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 182:
	//	s = "Knockdown Shield"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 181:
	//	s = "Knockdown Shield"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 233:
	//	s = "Hammerpoint"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 227:
	//	s = "Standard Stock"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 226:
	//	s = "Standard Stock"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 225:
	//	s = "Standard Stock"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 209:
	//	s = "Extended Light Mag"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 208:
	//	s = "Extended Light Mag"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 207:
	//	s = "Extended Light Mag"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 206:
	//	s = "Extended Light Mag"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 196:
	//	s = "1X Digital"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 42:
	//	s = "Alternator"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 47:
	//	s = "R-99"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 69:
	//	s = "R-301"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 94:
	//	s = "P2020"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 99:
	//	s = "RE-45"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 120:
	//	s = "Light Ammo"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 244:
	//	s = "Boosted Loader"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 242:
	//	s = "Shatter Caps"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 213:
	//	s = "Extended Heavy Mag"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 212:
	//	s = "Extended Heavy Mag"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 211:
	//	s = "Extended Heavy Mag"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 210:
	//	s = "Extended Heavy Mag"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 119:
	//	s = "Dual Shell"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 27:
	//	s = "Flatline"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 32:
	//	s = "Hemlok"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 52:
	//	s = "Prowler"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 89:
	//	s = "Wingman"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 114:
	//	s = "30-30"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 126:
	//	s = "Rampage"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 131:
	//	s = "C.A.R"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 123:
	//	s = "Heavy Ammo"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 243:
	//	s = "Kinetic Feeder"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 231:
	//	s = "Turbocharger"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 217:
	//	s = "Extended Energy Mag"; // gold
	//	itemBaseItem->itemTextColor = colorGold;
	//	break;
	//case 216:
	//	s = "Extended Energy Mag"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 215:
	//	s = "Extended Energy Mag"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 214:
	//	s = "Extended Energy Mag"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 7:
	//	s = "L-Star"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 12:
	//	s = "HAVOC"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 17:
	//	s = "Devotion"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 22:
	//	s = "Triple Take"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 121:
	//	s = "Energy Ammo"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 125:
	//	s = "Arrow"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 109:
	//	s = "Bocek"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 1:
	//	s = "Kraber"; // rot
	//	itemBaseItem->itemTextColor = colorRed;
	//	break;
	//case 37:
	//	s = "G7 Scout"; // rot
	//	itemBaseItem->itemTextColor = colorRed;
	//	break;
	//case 57:
	//	s = "Volt"; // rot
	//	itemBaseItem->itemTextColor = colorRed;
	//	break;
	//case 68:
	//	s = "Spitfire"; // rot
	//	itemBaseItem->itemTextColor = colorRed;
	//	break;
	//case 224:
	//	s = "Shotgun bolt"; // lila
	//	itemBaseItem->itemTextColor = colorPurple;
	//	break;
	//case 223:
	//	s = "Shotgun bolt"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 222:
	//	s = "Shotgun bolt"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 2:
	//	s = "Mastiff"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 74:
	//	s = "EVA-8"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 79:
	//	s = "Peacekeeper"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 84:
	//	s = "Mozambique"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 122:
	//	s = "Shotgun Shells"; // weiß
	//	itemBaseItem->itemTextColor = colorWhite;
	//	break;
	//case 252:
	//	s = "Mobile Respawner"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//case 251:
	//	s = "Heatshield"; // blau
	//	itemBaseItem->itemTextColor = colorBlue;
	//	break;
	//}
#pragma endregion

	itemBaseItem->name = s;
}

Vector3 WorldToScreenItems(Vector3 from, Matrix myMatrix)
{
	Vector3 out = Vector3();
	float _x = myMatrix.matrix[0] * from.X + myMatrix.matrix[1] * from.Y + myMatrix.matrix[2] * from.Z + myMatrix.matrix[3];
	float _y = myMatrix.matrix[4] * from.X + myMatrix.matrix[5] * from.Y + myMatrix.matrix[6] * from.Z + myMatrix.matrix[7];
	out.Z = myMatrix.matrix[12] * from.X + myMatrix.matrix[13] * from.Y + myMatrix.matrix[14] * from.Z + myMatrix.matrix[15];

	_x *= 1.f / out.Z;
	_y *= 1.f / out.Z;

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	out.X = width * .5f;
	out.Y = height * .5f;

	out.X += 0.5f * _x * width + 0.5f;
	out.Y -= 0.5f * _y * height + 0.5f;

	return out;
}

float GetDistanceItemsToPlayer(Vector3 localPlayerPosition, Vector3 entityPlayerPosition) {
	return sqrtf((localPlayerPosition.X - entityPlayerPosition.X) * (localPlayerPosition.X - entityPlayerPosition.X) + (localPlayerPosition.Y - entityPlayerPosition.Y) * (localPlayerPosition.Y - entityPlayerPosition.Y) + (localPlayerPosition.Z - entityPlayerPosition.Z) * (localPlayerPosition.Z - entityPlayerPosition.Z));
}


Matrix myNewMatrix = Matrix();
Vector3 myNewLocalPlayerPosition = Vector3();
void Overlay::SetMatrixLocalPlayer(Matrix newMatrix, Vector3 localPlayerPos) {
	myNewMatrix = newMatrix;
	myNewLocalPlayerPosition = localPlayerPos;
}

void SetAttachment(const std::pair<const int, std::string> attachmentIterator, IWeaponAttachments& weapon) {
	if (attachmentIterator.second.rfind("purpleDeadEyesTempo", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.deadEyesTempo = true;
	}
	else if (attachmentIterator.second.rfind("purpleHammerpoint", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.hammerpoint = true;
	}
	else if (attachmentIterator.second.rfind("goldBoostedLoader", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.boostedLoader = true;
	}
	else if (attachmentIterator.second.rfind("purpleShatterCaps", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.shatterCaps = true;
	}
	else if (attachmentIterator.second.rfind("purpleDualShell", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.dualShell = true;
	}
	else if (attachmentIterator.second.rfind("purpleKineticFeeder", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.kineticFeeder = true;
	}
	else if (attachmentIterator.second.rfind("goldTurboCharger", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.turboCharger = true;
	}
}

void SetStabi(const std::pair<const int, std::string> stabiIterator, IWeaponAttachments& weapon) {
	if (stabiIterator.second.rfind("purple", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.purpleStabi = true;
	}
	else if (stabiIterator.second.rfind("blue", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.blueStabi = true;
	}
	else if (stabiIterator.second.rfind("white", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.whiteStabi = true;
	}
}

void SetMag(const std::pair<const int, std::string> magIterator, IWeaponAttachments& weapon) {
	if (magIterator.second.rfind("gold", 0) == 0) {
		weapon.goldMag = true;
	}
	else if (magIterator.second.rfind("purple", 0) == 0) {
		weapon.purpleMag = true;
	}
	else if (magIterator.second.rfind("blue", 0) == 0) {
		weapon.blueMag = true;
	}
	else if (magIterator.second.rfind("white", 0) == 0) {
		weapon.whiteMag = true;
	}
}

void SetScope(const std::pair<const int, std::string> scopeIterator, IWeaponAttachments& weapon) {
	if (scopeIterator.second.rfind("goldFourXten", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.fourXtenScope = true;
	}
	else if (scopeIterator.second.rfind("purpleFourXeight", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.fourXeightScope = true;
	}
	else if (scopeIterator.second.rfind("blueSixX", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.sixXScope = true;
	}
	else if (scopeIterator.second.rfind("purpleTwoXfour", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.twoXfourScope = true;
	}
	else if (scopeIterator.second.rfind("purpleThreeX", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.threeXScope = true;
	}
	else if (scopeIterator.second.rfind("blueOneXtwo", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.oneXtwoScope = true;
	}
	else if (scopeIterator.second.rfind("whiteOneHolo", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.oneHoloScope = true;
	}
	else if (scopeIterator.second.rfind("blueTwoX", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.twoXScope = true;
	}
	else if (scopeIterator.second.rfind("whiteOneHOKV", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.oneHOKVScope = true;
	}
	else if (scopeIterator.second.rfind("goldDigitalScope", 0) == 0) {
		weapon.digitalScope = true;
	}
}

// setzt den Standard Stock basierend auf den angegebenen Iterator
void SetStandardStock(const std::pair<const int, std::string> stockIterator, IWeaponAttachments& weapon) {
	if (stockIterator.second.rfind("purple", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.purpleStock = true;
	}
	else if (stockIterator.second.rfind("blue", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.blueStock = true;
	}
	else if (stockIterator.second.rfind("white", 0) == 0) { // pos=0 limits the search to the prefix
		weapon.whiteStock = true;
	}
}

void EvaluateAttachments(IWeaponAttachments& weapon, IWeaponAttachmentValues& weaponValues, int modBitFieldCurrent) {
	map<string, int>::iterator stabiIt;

	// Erster Wert ist IMMER die Zahl!
	for (auto const& stabiIterator : weaponValues.listStabilizer)
	{
		for (auto const& magIterator : weaponValues.listExtendedMag)
		{
			for (auto const& scopeIterator : weaponValues.listScope)
			{
				for (auto const& stockIterator : weaponValues.listStandardStock)
				{
					if (weaponValues.listAttachments.size() > 0) {
						for (auto const& attachmentIterator : weaponValues.listAttachments) {
							int stockValue = stockIterator.first;
							int scopeValue = scopeIterator.first;
							int magValue = magIterator.first;
							int stabiValue = stabiIterator.first;
							int attachmentValue = attachmentIterator.first;

							if (weaponValues.standardValue + stockValue == modBitFieldCurrent) {
								SetStandardStock(stockIterator, weapon);
							}

							if (weaponValues.standardValue + scopeValue == modBitFieldCurrent) {
								SetScope(scopeIterator, weapon);
							}

							if (weaponValues.standardValue + magValue == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
							}

							if (weaponValues.standardValue + stabiValue == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
							}

							if (weaponValues.standardValue + attachmentValue == modBitFieldCurrent) {
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stockValue + magValue) == modBitFieldCurrent) {
								SetStandardStock(stockIterator, weapon);
								SetMag(magIterator, weapon);
							}

							if ((weaponValues.standardValue + stockValue + scopeValue) == modBitFieldCurrent) {
								SetStandardStock(stockIterator, weapon);
								SetScope(scopeIterator, weapon);
							}

							if ((weaponValues.standardValue + stockValue + stabiValue) == modBitFieldCurrent) {
								SetStandardStock(stockIterator, weapon);
								SetStabi(stabiIterator, weapon);
							}

							if ((weaponValues.standardValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + scopeValue + magValue) == modBitFieldCurrent) {
								SetScope(scopeIterator, weapon);
								SetMag(magIterator, weapon);
							}

							if ((weaponValues.standardValue + scopeValue + stabiValue) == modBitFieldCurrent) {
								SetScope(scopeIterator, weapon);
								SetMag(magIterator, weapon);
							}

							if ((weaponValues.standardValue + scopeValue + attachmentValue) == modBitFieldCurrent) {
								SetScope(scopeIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + magValue + stabiValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetStabi(stabiIterator, weapon);
							}

							if ((weaponValues.standardValue + magValue + attachmentValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + scopeValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + stockValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetStandardStock(stockIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + scopeValue + stockValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
							}

							if ((weaponValues.standardValue + magValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + magValue + scopeValue + stockValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
							}

							if ((weaponValues.standardValue + scopeValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + scopeValue + stockValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetStabi(stabiIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + scopeValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + scopeValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + stabiValue + magValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}

							if ((weaponValues.standardValue + magValue + scopeValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
								SetAttachment(attachmentIterator, weapon);
							}


							if ((weaponValues.standardValue + stabiValue + magValue + scopeValue + stockValue + attachmentValue) == modBitFieldCurrent) {
								SetStabi(stabiIterator, weapon);
								SetMag(magIterator, weapon);
								SetScope(scopeIterator, weapon);
								SetStandardStock(stockIterator, weapon);
							}
						}
					}
					else {
						int stockValue = stockIterator.first;
						int scopeValue = scopeIterator.first;
						int magValue = magIterator.first;
						int stabiValue = stabiIterator.first;

						if (weaponValues.standardValue + stockValue == modBitFieldCurrent) {
							SetStandardStock(stockIterator, weapon);
						}

						if (weaponValues.standardValue + scopeValue == modBitFieldCurrent) {
							SetScope(scopeIterator, weapon);
						}

						if (weaponValues.standardValue + magValue == modBitFieldCurrent) {
							SetMag(magIterator, weapon);
						}

						if (weaponValues.standardValue + stabiValue == modBitFieldCurrent) {
							SetStabi(stabiIterator, weapon);
						}

						if ((weaponValues.standardValue + stockValue + magValue) == modBitFieldCurrent) {
							SetStandardStock(stockIterator, weapon);
							SetMag(magIterator, weapon);
						}

						if ((weaponValues.standardValue + stockValue + scopeValue) == modBitFieldCurrent) {
							SetStandardStock(stockIterator, weapon);
							SetScope(scopeIterator, weapon);
						}

						if ((weaponValues.standardValue + stockValue + magValue) == modBitFieldCurrent) {
							SetStandardStock(stockIterator, weapon);
							SetMag(magIterator, weapon);
						}

						if ((weaponValues.standardValue + stockValue + stabiValue) == modBitFieldCurrent) {
							SetStandardStock(stockIterator, weapon);
							SetStabi(stabiIterator, weapon);
						}

						if ((weaponValues.standardValue + scopeValue + magValue) == modBitFieldCurrent) {
							SetScope(scopeIterator, weapon);
							SetMag(magIterator, weapon);
						}

						if ((weaponValues.standardValue + scopeValue + stabiValue) == modBitFieldCurrent) {
							SetScope(scopeIterator, weapon);
							SetMag(magIterator, weapon);
						}

						if ((weaponValues.standardValue + magValue + stabiValue) == modBitFieldCurrent) {
							SetMag(magIterator, weapon);
							SetStabi(stabiIterator, weapon);
						}

						if ((weaponValues.standardValue + stabiValue + magValue + scopeValue) == modBitFieldCurrent) {
							SetStabi(stabiIterator, weapon);
							SetMag(magIterator, weapon);
							SetScope(scopeIterator, weapon);
						}

						if ((weaponValues.standardValue + stabiValue + magValue + stockValue) == modBitFieldCurrent) {
							SetStabi(stabiIterator, weapon);
							SetMag(magIterator, weapon);
							SetStandardStock(stockIterator, weapon);
						}

						if ((weaponValues.standardValue + stabiValue + scopeValue + stockValue) == modBitFieldCurrent) {
							SetStabi(stabiIterator, weapon);
							SetScope(scopeIterator, weapon);
							SetStandardStock(stockIterator, weapon);
						}

						if ((weaponValues.standardValue + magValue + scopeValue + stockValue) == modBitFieldCurrent) {
							SetMag(magIterator, weapon);
							SetScope(scopeIterator, weapon);
							SetStandardStock(stockIterator, weapon);
						}

						if ((weaponValues.standardValue + magValue + scopeValue + stockValue + stabiValue) == modBitFieldCurrent) {
							SetMag(magIterator, weapon);
							SetScope(scopeIterator, weapon);
							SetStandardStock(stockIterator, weapon);
							SetStabi(stabiIterator, weapon);
						}
					}
				}
			}
		}
	}
}

void CheckWeaponAndSetAttachments(string weaponName, int modBitFieldCurrent) {
	IWeaponAttachments weaponAttachments;
	IWeaponAttachmentValues weaponValues;

	if (weaponName == "Longbow") {
		weaponAttachments = LongbowAttachments();
		weaponValues = LongbowAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		longbowAttachments = LongbowAttachments(weaponAttachments);
		longbowAttachmentValues = weaponValues;
	}
	else if (weaponName == "Elektrogewehr") {
		weaponAttachments = ChargeRifleAttachments();
		weaponValues = ChargeRifleAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		chargeRifleAttachments = ChargeRifleAttachments(weaponAttachments);
		chargeRifleAttachmentValues = weaponValues;
	}
	else if (weaponName == "Sentinel") {
		weaponAttachments = SentinelAttachments();
		weaponValues = SentinelAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		sentinelAttachments = SentinelAttachments(weaponAttachments);
		sentinelAttachmentValues = weaponValues;
	}
	else if (weaponName == "Alternator") {
		weaponAttachments = AlternatorAttachments();
		weaponValues = AlternatorAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		alternatorAttachments = AlternatorAttachments(weaponAttachments);
		alternatorAttachmentValues = weaponValues;
	}
	else if (weaponName == "R99") {
		weaponAttachments = R99Attachments();
		weaponValues = R99AttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		r99Attachments = R99Attachments(weaponAttachments);
		r99AttachmentValues = weaponValues;
	}
	else if (weaponName == "R301") {
		weaponAttachments = R301Attachments();
		weaponValues = R301AttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		r301Attachments = R301Attachments(weaponAttachments);
		r301AttachmentValues = weaponValues;
	}
	else if (weaponName == "P2020") {
		weaponAttachments = P2020Attachments();
		weaponValues = P2020AttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		p2020Attachments = P2020Attachments(weaponAttachments);
		p2020AttachmentValues = weaponValues;
	}
	else if (weaponName == "RE-45") {
		weaponAttachments = RE45Attachments();
		weaponValues = RE45AttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		re45Attachments = RE45Attachments(weaponAttachments);
		re45AttachmentValues = weaponValues;
	}
	else if (weaponName == "Flatline") {
		weaponAttachments = FlatlineAttachments();
		weaponValues = FlatlineAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		flatlineAttachments = FlatlineAttachments(weaponAttachments);
		flatlineAttachmentValues = weaponValues;
	}
	else if (weaponName == "Hemlok") {
		weaponAttachments = HemlokAttachments();
		weaponValues = HemlokAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		hemlokAttachments = HemlokAttachments(weaponAttachments);
		hemlokAttachmentValues = weaponValues;
	}
	else if (weaponName == "Prowler") {
		weaponAttachments = ProwlerAttachments();
		weaponValues = ProwlerAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		prowlerAttachments = ProwlerAttachments(weaponAttachments);
		prowlerAttachmentValues = weaponValues;
	}
	else if (weaponName == "Wingman") {
		weaponAttachments = WingmanAttachments();
		weaponValues = WingmanAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		wingmanAttachments = WingmanAttachments(weaponAttachments);
		wingmanAttachmentValues = weaponValues;
	}
	else if (weaponName == "30-30") {
		weaponAttachments = ThirtyThirtyAttachments();
		weaponValues = ThirtyThirtyAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		thirtyThirtyAttachments = ThirtyThirtyAttachments(weaponAttachments);
		thirtyThirtyAttachmentValues = weaponValues;
	}
	else if (weaponName == "Rampage") {
		weaponAttachments = RampageAttachments();
		weaponValues = RampageAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		rampageAttachments = RampageAttachments(weaponAttachments);
		rampageAttachmentValues = weaponValues;
	}
	else if (weaponName == "C.A.R") {
		weaponAttachments = CARAttachments();
		weaponValues = CARAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		carAttachments = CARAttachments(weaponAttachments);
		carAttachmentValues = weaponValues;
	}
	else if (weaponName == "L-Star") {
		weaponAttachments = LStarAttachments();
		weaponValues = LStarAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		lStarAttachments = LStarAttachments(weaponAttachments);
		lStarAttachmentValues = weaponValues;
	}
	else if (weaponName == "Havoc") {
		weaponAttachments = HavocAttachments();
		weaponValues = HavocAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		havocAttachments = HavocAttachments(weaponAttachments);
		havocAttachmentValues = weaponValues;
	}
	else if (weaponName == "Devotion") {
		weaponAttachments = DevotionAttachments();
		weaponValues = DevotionAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		devotionAttachments = DevotionAttachments(weaponAttachments);
		devotionAttachmentValues = weaponValues;
	}
	else if (weaponName == "Triple Take") {
		weaponAttachments = TripleTakeAttachments();
		weaponValues = TripleTakeAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		tripleTakeAttachments = TripleTakeAttachments(weaponAttachments);
		tripleTakeAttachmentValues = weaponValues;
	}
	else if (weaponName == "Bocek") {
		weaponAttachments = BocekAttachments();
		weaponValues = BocekAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		bocekAttachments = BocekAttachments(weaponAttachments);
		bocekAttachmentValues = weaponValues;
	}
	else if (weaponName == "G7-Scout") {
		weaponAttachments = G7ScoutAttachments();
		weaponValues = G7ScoutAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		g7ScoutAttachments = G7ScoutAttachments(weaponAttachments);
		g7ScoutAttachmentValues = weaponValues;
	}
	else if (weaponName == "Volt") {
		weaponAttachments = VoltAttachments();
		weaponValues = VoltAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		voltAttachments = VoltAttachments(weaponAttachments);
		voltAttachmentValues = weaponValues;
	}
	else if (weaponName == "Spitfire") {
		weaponAttachments = SpitfireAttachments();
		weaponValues = SpitfireAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		spitfireAttachments = SpitfireAttachments(weaponAttachments);
		spitfireAttachmentValues = weaponValues;
	}
	else if (weaponName == "Mastiff") {
		weaponAttachments = MastiffAttachments();
		weaponValues = MastiffAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		mastiffAttachments = MastiffAttachments(weaponAttachments);
		mastiffAttachmentValues = weaponValues;
	}
	else if (weaponName == "EVA-8") {
		weaponAttachments = EVA8Attachments();
		weaponValues = EVA8AttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		eva8Attachments = EVA8Attachments(weaponAttachments);
		eva8AttachmentValues = weaponValues;
	}
	else if (weaponName == "Peacekeeper") {
		weaponAttachments = PeacekeeperAttachments();
		weaponValues = PeacekeeperAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		peacekeeperAttachments = PeacekeeperAttachments(weaponAttachments);
		peacekeeperAttachmentValues = weaponValues;
	}
	else if (weaponName == "Mosambik") {
		weaponAttachments = MozambiqueAttachments();
		weaponValues = MozambiqueAttachmentValues();

		EvaluateAttachments(weaponAttachments, weaponValues, modBitFieldCurrent);

		mozambiqueAttachments = MozambiqueAttachments(weaponAttachments);
		mozambiqueAttachmentValues = weaponValues;
	}
}

void PrepareSmartItemESP() {
	while (true) {
		if (Config.enableItemESP && Config.enableSmartItemESP) {
			if (myWeaponIndex1.empty() && myWeaponIndex2.empty()) {
				currentWeapons.weapon1 = "";
				currentWeapons.weapon2 = "";
				currentWeapons.modBitFieldCurrentWeapon1 = 0;
				currentWeapons.modBitFieldCurrentWeapon2 = 0;
			}
			else {
				if (myWeaponIndex1.empty()) {
					currentWeapons.weapon1 = "";
					currentWeapons.modBitFieldCurrentWeapon1 = 0;
				}
				else if (myWeaponIndex2.empty()) {
					currentWeapons.weapon2 = "";
					currentWeapons.modBitFieldCurrentWeapon2 = 0;
				}

				auto weapon1Iterator = weaponNameIndexMap.find(myWeaponIndex1);
				auto weapon2Iterator = weaponNameIndexMap.find(myWeaponIndex2);

				/*cout << "Weapon ID 1: " << myWeaponIndex1 << endl;*/

				if (weapon1Iterator != weaponNameIndexMap.end()) {
					currentWeapons.weapon1 = weapon1Iterator->second;
					currentWeapons.modBitFieldCurrentWeapon1 = myModBitField1;
				}

				if (weapon2Iterator != weaponNameIndexMap.end()) {
					currentWeapons.weapon2 = weapon2Iterator->second;
					currentWeapons.modBitFieldCurrentWeapon2 = myModBitField2;
				}

				// wir holen uns die aktuellen Waffen
				if (!currentWeapons.weapon1.empty() || !currentWeapons.weapon2.empty()) {
					// wir tun nur etwas, wenn wir auch eine Waffe schon bereits haben!
					if (!currentWeapons.weapon1.empty()) {
						CheckWeaponAndSetAttachments(currentWeapons.weapon1, currentWeapons.modBitFieldCurrentWeapon1);
					}

					if (!currentWeapons.weapon2.empty()) {
						CheckWeaponAndSetAttachments(currentWeapons.weapon2, currentWeapons.modBitFieldCurrentWeapon2);
					}
				}
				else {
					// wir setzen alle Klassen auf ihren Standardwert zurück!
					longbowAttachments = LongbowAttachments();
					longbowAttachmentValues = LongbowAttachmentValues();

					chargeRifleAttachments = ChargeRifleAttachments();
					chargeRifleAttachmentValues = ChargeRifleAttachmentValues();

					sentinelAttachments = SentinelAttachments();
					sentinelAttachmentValues = SentinelAttachmentValues();

					alternatorAttachments = AlternatorAttachments();
					alternatorAttachmentValues = AlternatorAttachmentValues();

					r301Attachments = R301Attachments();
					r301AttachmentValues = R301AttachmentValues();

					p2020Attachments = P2020Attachments();
					p2020AttachmentValues = P2020AttachmentValues();

					re45Attachments = RE45Attachments();
					re45AttachmentValues = RE45AttachmentValues();

					flatlineAttachments = FlatlineAttachments();
					flatlineAttachmentValues = FlatlineAttachmentValues();

					prowlerAttachments = ProwlerAttachments();
					prowlerAttachmentValues = ProwlerAttachmentValues();

					wingmanAttachments = WingmanAttachments();
					wingmanAttachmentValues = WingmanAttachmentValues();
				
					thirtyThirtyAttachments = ThirtyThirtyAttachments();
					thirtyThirtyAttachmentValues = ThirtyThirtyAttachmentValues();

					rampageAttachments = RampageAttachments();
					rampageAttachmentValues = RampageAttachmentValues();

					carAttachments = CARAttachments();
					carAttachmentValues = CARAttachmentValues();

					lStarAttachments = LStarAttachments();
					lStarAttachmentValues = LStarAttachmentValues();

					havocAttachments = HavocAttachments();
					havocAttachmentValues = HavocAttachmentValues();

					devotionAttachments = DevotionAttachments();
					devotionAttachmentValues = DevotionAttachmentValues();

					tripleTakeAttachments = TripleTakeAttachments();
					tripleTakeAttachmentValues = TripleTakeAttachmentValues();

					g7ScoutAttachments = G7ScoutAttachments();
					g7ScoutAttachmentValues = G7ScoutAttachmentValues();

					voltAttachments = VoltAttachments();
					voltAttachmentValues = VoltAttachmentValues();

					spitfireAttachments = SpitfireAttachments();
					spitfireAttachmentValues = SpitfireAttachmentValues();

					mastiffAttachments = MastiffAttachments();
					mastiffAttachmentValues = MastiffAttachmentValues();

					peacekeeperAttachments = PeacekeeperAttachments();
					peacekeeperAttachmentValues = PeacekeeperAttachmentValues();

					mozambiqueAttachments = MozambiqueAttachments();
					mozambiqueAttachmentValues = MozambiqueAttachmentValues();
				}
			}
		}
	}
}

void DrawItems() {
	//while (true) {
	if (Config.enableItemESP) {
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		for (int i = 60; i < 65001; i++) {
			if (itemBase[i].isItem) {
				Vector3 worldToScreen = WorldToScreenItems(itemBase[i].position, myNewMatrix);

				float distance = GetDistanceItemsToPlayer(myNewLocalPlayerPosition, itemBase[i].position);
				float realDistance = distance / 40;

				itemBase[i].distance = distance;
				itemBase[i].realDistance = realDistance;
				itemBase[i].w2sBase = worldToScreen;

				if ((itemBase[i].w2sBase.X < screenWidth || itemBase[i].w2sBase.Y < screenHeight) && ((itemBase[i].w2sBase.X > 0 && itemBase[i].w2sBase.Y > 0) && (itemBase[i].w2sBase.Z > 0)) &&
					itemBase[i].realDistance <= Config.maxItemDistance) {
					char dist[20];
					sprintf_s(dist, "%d m", static_cast<int>(itemBase[i].distance / 40));

					ItemIDToName(itemBase[i].lootID, &itemBase[i]);

					// prüfen ob es noch ein Item ist, da 'ItemIDToName' auch prüft zwecks SmartItemESP
					if (itemBase[i].isItem) {
						DrawString(itemBase[i].name.c_str(), itemBase[i].w2sBase.X, itemBase[i].w2sBase.Y, itemBase[i].itemTextColor, pItemFont);
						DrawString(dist, itemBase[i].w2sBase.X, itemBase[i].w2sBase.Y + 15, itemBase[i].itemTextColor, pItemFont);
					}
				}
			}
		}
	}
	//}
}

void Overlay::DrawItemMenu() {
	while (true) {
		DrawItems();
	}
}

void Overlay::DrawRenderMenu()
{
	static ImDrawList* drawList;
	
	LONG menu = WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT;
	LONG ingame = WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT;

	std::thread prepareSmartItem = std::thread(PrepareSmartItemESP);

	int itemStart = 0;
	int itemEnd = 32500;

	while (true) {
		//auto t1 = std::chrono::high_resolution_clock::now();
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawImGui(menu, ingame);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

		ImGui::Begin("##scene", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		drawList = ImGui::GetWindowDrawList();

		DeviceClearBeginScene();

		DrawEsp();

		if (Config.enableItemESP) {
			DrawItems();
		}

		DrawListPushCliptRectFullScreen(drawList);
		
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		DeviceEndScenePresentEx();

		//auto t2 = std::chrono::high_resolution_clock::now();

		/* Getting number of milliseconds as an integer. */
		//auto ms_int = duration_cast<milliseconds>(t2 - t1);

		//cout << "Needed time: " << ms_int.count() << endl;
	}
}
#include <chrono>
#include "Overlay.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <iosfwd>
#include <random>
#include <map>

#define OFFSET_ORIGIN 0x014c // m_vecAbsOrigin
#define OFFSET_NAME 0x0589 //m_iName
#define OFFSET_NAMELIST 0xb9315d0 // NameList
#define OFFSET_LOCALPLAYER 0x1d243d8 // LocalPlayer
#define OFFSET_ENTITYLIST 0x1974ad8 // cl_entitylist
#define OFFSET_SHIELDMAXHEALTH 0x0174 // m_shieldHealthMax
#define OFFSET_SHIELDHEALTH 0x0170 // m_shieldHealth
#define OFFSET_HEALTH 0x0438 // m_iHealth
#define OFFSET_BONES 0x0f38 // m_bConstrainBetweenEndpoints
#define OFFSET_VIEWRENDERER 0x7431238  // ViewRender
#define OFFSET_VIEWMATRIX 0x10e8d0 // ViewMatrix
#define OFFSET_BLEEDOUTSTATE 0x2708 // m_bleedoutState
#define OFFSET_TEAMNUM 0x0448 // m_iTeamNum
#define OFFSET_CURRENTWEAPON 0x1a8c // m_latestPrimaryWeapons
#define OFFSET_BULLETSPEED 0x1f18 // CWeaponX!m_flProjectileSpeed
#define OFFSET_BULLETGRAVITY OFFSET_BULLETSPEED + 0x8
#define OFFSET_VIEWANGLES 0x257c - 0x14 // m_ammoPoolCapacity - 0x14
#define OFFSET_VISIBLETIME 0x1af4 // CPlayer!lastVisibleTime
#define OFFSET_ARMORTYPE 0x4594 // CPlayer!armorType
#define OFFSET_HELMETTYPE 0x4590 // CPlayer!helmetType
#define OFFSET_ITEMID 0x1698 // m_customScriptInt
#define OFFSET_WEAPONNAMEINDEX 0x16A4 // m_weaponNameIndex DT_PropSurvival
#define OFFSETS_PROPSURVIVAL 0x01238228 // CPropSurvival
#define OFFSET_MODELNAME 0x0030 // m_ModelName
#define OFFSET_SIGNIFIERNAME 0x0580 // m_iSignifierName
#define OFFSET_WEAPONOWNER 0x1690 // m_weaponOwner
#define OFFSET_SCRIPTNAMEINDEX 0x0690 // m_scriptNameIndex
#define OFFSET_CURRENTATTACHMENTS 0x1844 // m_modBitFieldCurrent
#define OFFSET_IWORLDINDEX 0x16a8 // m_iWorldModelIndex
#define OFFSET_ABS_VELOCITY 0x0140 // m_vecAbsVelocity
#define OFFSET_BREATH_ANGLES (OFFSET_VIEWANGLES - 0x10)
#define OFFSET_ZOOMING 0x1c31 // m_bZooming

#define OFFSET_ITEM_GLOW 0x2C0 // m_highlightFunctionBits // check if glow is enabled
#define OFFSET_GLOWENABLE 0x3c8 // _ragdoll.list[24 + 0].originParentSpace=0x03c8 ??? // 7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS 0x3d0 // 2 enabled, 5 disabled
#define OFFSET_GLOWCOLOR 0x1D0 // m_ragdoll.list[8 + 3].pObject=0x01d0 ??
#define OFFSET_GLOW_T1              0x262 //16256 = enabled, 0 = disabled 
#define OFFSET_GLOW_T2              0x2dc //1193322764 = enabled, 0 = disabled 


using namespace std;
using namespace std::chrono;
using std::map; 

const wchar_t g_szClassName[] = L"Test";
const MARGINS margins = { -1 ,-1, -1, -1 };
static HWND OverlayHWND;
Overlay myOverlay;
Driver::Module mod;
PlayerData myPlayerBase[62] = {};
ItemData myItemPlayerBase[66001] = {};
Matrix myMatrix = Matrix();
uint64_t globalLocalPlayer;

static D3DCOLOR colorGreen = D3DCOLOR_ARGB(255, 24, 173, 10);
static D3DCOLOR colorRedDB = D3DCOLOR_ARGB(255, 255, 62, 48);

void itemEspThread() {
	//myOverlay.DrawItemMenu();
}

void espThread()
{
	myOverlay.DrawRenderMenu();
}

void dataThread() {
	myOverlay.GetDriverData();
}

//void aimbotThread(Driver* driv, Driver::Module modu)
//{
//	while (true)
//	{
//		myOverlay.StartAimbot(driv, modu);
//	}
//}

struct ClientClass
{
	uint64_t pCreateFn;
	uint64_t pCreateEventFn;
	uint64_t pNetworkName;
	uint64_t pRecvTable;
	uint64_t pNext;
	uint32_t ClassID;
	uint32_t ClassSize;
};

CurrentWeapons mainCurrentWeapons = CurrentWeapons();

struct ReadNameStruct {
	char name[128];
};

int getClassID(Driver* driv, uint64_t centity) {
	uintptr_t clientNetworkableVTable;
	driv->GetAddress<uintptr_t>((void*)(centity + 8 * 3), clientNetworkableVTable);
	uintptr_t getClientClass;
	driv->GetAddress<uintptr_t>((void*)(clientNetworkableVTable + 8 * 3), getClientClass);
	uint32_t disp;
	driv->GetAddress<uint32_t>((void*)(getClientClass + 3), disp);
	const uint64_t client_class_ptr = getClientClass + disp + 7;
	// Get the ClientClass instance itself.
	ClientClass clientClass = ClientClass();
	driv->GetAddress<ClientClass>((void*)(client_class_ptr), clientClass);
	return clientClass.ClassID;
}

char* getClassName(Driver* driv, uintptr_t ent)
{
	uintptr_t clientNetworkableVTable;
	driv->GetAddress<uintptr_t>((void*)(ent + 8 * 3), clientNetworkableVTable);
	uintptr_t getClientClass;
	driv->GetAddress<uintptr_t>((void*)(clientNetworkableVTable + 8 * 3), getClientClass);
	uint32_t disp;
	driv->GetAddress<uint32_t>((void*)(getClientClass + 3), disp);
	const uint64_t client_class_ptr = getClientClass + disp + 7;
	// Get the ClientClass instance itself.
	ClientClass clientClass = ClientClass();
	driv->GetAddress<ClientClass>((void*)(client_class_ptr), clientClass);

	// Finally grab some bytes to be interpreted as a nul terminated c-string.
	uint64_t emptyTargetAddress;
	ReadNameStruct nameStruct = ReadNameStruct();
	//auto className = driv->GetString((void*)(clientClass.pNetworkName), &emptyTargetAddress, L"r5apex.exe");
	driv->GetAddress<ReadNameStruct>((void*)(clientClass.pNetworkName), nameStruct);

	char name[128];
	memcpy(name, nameStruct.name, sizeof name);
	return name;
}

SignifierNameStruct getSignifierName(Driver* driv, DWORD_PTR Entity) {
	uint64_t emptyTarget;
	SignifierNameStruct signifierName = SignifierNameStruct();

	DWORD_PTR iSignifierName;
	driv->GetAddress<DWORD_PTR>((void*)(Entity + OFFSET_SIGNIFIERNAME), iSignifierName);

	if (iSignifierName > 0) {	
		driv->GetAddress<SignifierNameStruct>((void*)(iSignifierName), signifierName);
	}

	return signifierName;
}

float GetDistance(Vector3 localPlayerPosition, Vector3 entityPlayerPosition) {
	return sqrtf((localPlayerPosition.X - entityPlayerPosition.X) * (localPlayerPosition.X - entityPlayerPosition.X) + (localPlayerPosition.Y - entityPlayerPosition.Y) * (localPlayerPosition.Y - entityPlayerPosition.Y) + (localPlayerPosition.Z - entityPlayerPosition.Z) * (localPlayerPosition.Z - entityPlayerPosition.Z));
}

Vector3 GetEntityPlayerPosition(Driver* driv, uint64_t centity) {
	Vector3 entityPlayerPosition = Vector3();
	driv->GetAddress<Vector3>((void*)(centity + OFFSET_ORIGIN), entityPlayerPosition); // offset origin
	return entityPlayerPosition;
}

Vector3 GetLocalPlayerPosition(Driver* driv, uint64_t localPlayer) {
	Vector3 localPlayerPosition = Vector3();
	driv->GetAddress<Vector3>((void*)(localPlayer + OFFSET_ORIGIN), localPlayerPosition); // offset origin
	return localPlayerPosition;
}

uint64_t GetName(Driver* driv, uint64_t centity) {
	uint64_t name;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_NAME), name); // m_iName
	return name;
}

string GetName(Driver* driv, int i, Driver::Module module) {
	int entityNumber = (i - 1) * 0x10;
	uint64_t newNameAddress;
	driv->GetAddress<uint64_t>((void*)(module.addr + OFFSET_NAMELIST + entityNumber), newNameAddress); // offset name_list
	ReadNameStruct nameStruct = ReadNameStruct();
	driv->GetAddress<ReadNameStruct>((void*)newNameAddress, nameStruct);
	return string(nameStruct.name);
}

uint64_t GetLocalPlayer(Driver* driv, Driver::Module mod) {
	uint64_t localPlayer;
	driv->GetAddress<uint64_t>((void*)(mod.addr + OFFSET_LOCALPLAYER), localPlayer); // dwLocalPlayer
	return localPlayer;
}

uint64_t GetEntityBase(Driver* driv, Driver::Module mod, int i) {
	uint64_t centity;	
	driv->GetAddress<uint64_t>((void*)((mod.addr + OFFSET_ENTITYLIST) + (i << 5)), centity); // cl_entitylist
	return centity;
}

int GetHelmetType(Driver* driv, uint64_t centity) {
	uint64_t helmetType;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_HELMETTYPE), helmetType); // Helmet type
	return (int)helmetType;
}

int GetArmorType(Driver* driv, uint64_t centity) {
	uint64_t armorType;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_ARMORTYPE), armorType); // ArmorType
	return (int)armorType;
}

struct WeaponName {
	char name[128];
};

uint64_t GetWeaponNameIndex(Driver* driv, uint64_t centity) {
	uint64_t weaponIndex;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_WEAPONNAMEINDEX), weaponIndex);
	return weaponIndex;
}

int GetLootID(Driver* driv, uint64_t centity) {
	int lootID;
	driv->GetAddress<int>((void*)(centity + OFFSET_ITEMID), lootID);
	return (int)lootID;
}

int GetShieldMaxHealth(Driver* driv, uint64_t centity) {
	uint64_t sMaxHealth64;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_SHIELDMAXHEALTH), sMaxHealth64); // entity + shield max health
	return (int)sMaxHealth64;
}

int GetShieldHealth(Driver* driv, uint64_t centity) {
	uint64_t shealth64;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_SHIELDHEALTH), shealth64); // entity + shield health
	return (int)shealth64;
}

int GetHealth(Driver* driv, uint64_t centity) {
	uint64_t healthRead;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_HEALTH), healthRead); // entity + leben
	return (int)healthRead;
}

string GetModelName(Driver* driv, uint64_t centity) {
	uint64_t modelNamePointer;
	ReadNameStruct modelName = ReadNameStruct();
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_MODELNAME), modelNamePointer); // entity + modelname
	driv->GetAddress<ReadNameStruct>((void*)(modelNamePointer), modelName);

	string name = string(modelName.name);
	return name;
}

bool IsLootBox(Driver* driv, uint64_t centity) {
	uint64_t teamNumLootBox;
	driv->GetAddress<uint64_t>((void*)(centity + OFFSET_SCRIPTNAMEINDEX), teamNumLootBox); // m_scriptNameIndex
	return teamNumLootBox == 8535013380602200064;
}

Vector GetEntityPosition(Driver* driv, uint64_t centity) {
	Vector entityPosition = Vector();
	driv->GetAddress<Vector>((void*)(centity + OFFSET_ORIGIN), entityPosition);
	return entityPosition;
}

Vector3 GetEntityPositionVec3(Driver* driv, uint64_t centity) {
	Vector3 entityPosition = Vector3();
	driv->GetAddress<Vector3>((void*)(centity + OFFSET_ORIGIN), entityPosition);
	return entityPosition;
}

Vector GetEntityBonePos(Driver* driv, uint64_t pEntityBase, uint32_t dwBoneId)
{
	uintptr_t pBone;
	driv->GetAddress<uintptr_t>((void*)(pEntityBase + OFFSET_BONES), pBone); // offset bones

	Vector EntityHead = Vector();
	Vector BasePosition = GetEntityPosition(driv, pEntityBase);

	float x = driv->GetAddress<float>((void*)(pBone + 0xCC + (dwBoneId * 0x30)));
	float y = driv->GetAddress<float>((void*)(pBone + 0xDC + (dwBoneId * 0x30)));
	float z = driv->GetAddress<float>((void*)(pBone + 0xEC + (dwBoneId * 0x30)));

	EntityHead.x = x + BasePosition.x;
	EntityHead.y = y + BasePosition.y;
	EntityHead.z = z + BasePosition.z;

	return EntityHead;
}

Vector3 GetEntityBonePosVec3(Driver* driv, uint64_t pEntityBase, uint32_t dwBoneId)
{
	uintptr_t pBone;
	driv->GetAddress<uintptr_t>((void*)(pEntityBase + OFFSET_BONES), pBone); // offset bones

	Vector3 EntityHead = Vector3();
	Vector3 BasePosition = GetEntityPositionVec3(driv, pEntityBase);

	float x = driv->GetAddress<float>((void*)(pBone + 0xCC + (dwBoneId * 0x30)));
	float y = driv->GetAddress<float>((void*)(pBone + 0xDC + (dwBoneId * 0x30)));
	float z = driv->GetAddress<float>((void*)(pBone + 0xEC + (dwBoneId * 0x30)));

	EntityHead.X = x + BasePosition.X;
	EntityHead.Y = y + BasePosition.Y;
	EntityHead.Z = z + BasePosition.Z;

	return EntityHead;
}

bool IsPlayer(Driver* driv, uintptr_t pEntityBase)
{
	uint64_t name = GetName(driv, pEntityBase);
	return name == 125780153691248;
}

Matrix GetMatrix(Driver* driv, Driver::Module apexLegends) {
	uint64_t viewRenderer;
	uint64_t viewMatrix;
	driv->GetAddress<uint64_t>((void*)(apexLegends.addr + OFFSET_VIEWRENDERER), viewRenderer); // viewRenderer
	driv->GetAddress<uint64_t>((void*)(viewRenderer + OFFSET_VIEWMATRIX), viewMatrix); // viewMatrix
	Matrix myMatrix = Matrix();
	driv->GetAddress<Matrix>((void*)viewMatrix, myMatrix);
	return myMatrix;
}

int GetWeaponOwner(Driver* driv, Driver::Module apexLegends) {
	uint16_t weaponIndex;
	// get the current equipped weapon
	driver->GetAddress<uint16_t>((void*)(globalLocalPlayer + OFFSET_CURRENTWEAPON), weaponIndex);
	// get the entity of it
	uint64_t entityBase = GetEntityBase(driver, mod, weaponIndex);
	int weaponOwner;
	// get the weapon owner in int
	driver->GetAddress<int>((void*)(entityBase + OFFSET_WEAPONOWNER), weaponOwner);
	return weaponOwner;
}

uint64_t GetButtonState(int address) {
	uint64_t result;
	driver->GetAddress<uint64_t>((void*)(mod.addr + address + 0x8), result);
	return result;
}

Vector3 WorldToScreen(Vector3 from, Matrix myMatrix)
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


bool IsVisible(Driver* driv, const uint64_t& entity, const size_t& i)
{
	const auto GetMs = []()
	{
		LARGE_INTEGER PerformanceFrequency;
		QueryPerformanceFrequency(&PerformanceFrequency);
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (10ll * now.QuadPart) / PerformanceFrequency.QuadPart;
	};

	static float LastVisibleTime[101] = { NULL };
	static bool LastVisibleState[101] = { NULL };
	static uint64_t LastVisibleCheckTime[101] = { NULL };

	if (GetMs() >= (LastVisibleCheckTime[i] + 1)) // only check every 1 ms
	{
		float VisibleTime;
		driv->GetAddress<float>((void*)(entity + OFFSET_VISIBLETIME), VisibleTime); // visibleTime
		LastVisibleState[i] = VisibleTime > LastVisibleTime[i] || VisibleTime < 0.0f && LastVisibleTime[i] > 0.0f;
		LastVisibleTime[i] = VisibleTime;
		LastVisibleCheckTime[i] = GetMs();
	}

	return LastVisibleState[i];
}

bool IsDowned(Driver* driv, uint64_t pEntityBase) {
	int bleedOutState;
	driv->GetAddress<int>((void*)(pEntityBase + OFFSET_BLEEDOUTSTATE), bleedOutState); // bleedOutState
	return  bleedOutState > 0;
}

bool IsEnemy(Driver* driv, uint64_t pEntityBase, Driver::Module module)
{
	uint64_t localPlayerNumber;
	driv->GetAddress<uint64_t>((void*)(GetLocalPlayer(driv, module) + OFFSET_TEAMNUM), localPlayerNumber); // offset m_iTeamNum;
	uint64_t entityNumber;
	driv->GetAddress<uint64_t>((void*)(pEntityBase + OFFSET_TEAMNUM), entityNumber); // offset m_iTeamNum;

	return localPlayerNumber != entityNumber;
}

int GetTeamID(Driver* driv, uint64_t pEntityBase, Driver::Module module) {
	int entityNumber;
	driv->GetAddress<int>((void*)(pEntityBase + OFFSET_TEAMNUM), entityNumber); // offset m_iTeamNum;
	return entityNumber;
}

bool IsPlayerZooming() {
	uint64_t zoom;
	driver->GetAddress<uint64_t>((void*)(globalLocalPlayer + OFFSET_ZOOMING), zoom);
	return zoom > 0;
}

Vector3 GetEntityAbsVelocity(Driver* driv, uintptr_t pEntityBase)
{
	Vector3 result;
	driver->GetAddress<Vector3>((void*)(pEntityBase + OFFSET_ABS_VELOCITY), result);
	return result;
}

QAngle GetEntitySwayAngle(uintptr_t pEntityBase)
{
	QAngle result;
	driver->GetAddress<QAngle>((void*)(pEntityBase + OFFSET_BREATH_ANGLES), result);
	return result;
}

struct AimContext {
	int FOV;
	int aSmoothAmount;

	int crosshairX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int crosshairY = GetSystemMetrics(SM_CYSCREEN) / 2;

	int entX = 0;
	int entY = 0;

	int closestX = 0;
	int closestY = 0;

	int aX = 0;
	int aY = 0;

	float entNewVisTime = 0;
	float entOldVisTime[100];
	int visCooldownTime[100];
};

bool isPlayerLocked = false;
int playerLockedNumber = 0;

float DistTo(Vector3 me, Vector3 ape)
{
	return (me - ape).Length();
}

struct PredictCtx
{
	Vector StartPos;
	Vector TargetPos;
	Vector TargetVel;
	float BulletSpeed;
	float BulletGravity;

	Vector2D AimAngles;
};

Vector ExtrapolatePos(const PredictCtx& Ctx, float Time)
{
	return Ctx.TargetPos + (Ctx.TargetVel * Time);
}

bool OptimalPitch(const PredictCtx& Ctx, const Vector2D& Dir2D, float* OutPitch)
{
	float Vel = Ctx.BulletSpeed, Grav = Ctx.BulletGravity, DirX = Dir2D.x, DirY = Dir2D.y;
	float Root = Vel * Vel * Vel * Vel - Grav * (Grav * DirX * DirX + 2.f * DirY * Vel * Vel);
	if (Root >= 0.f) { *OutPitch = atanf((Vel * Vel - sqrt(Root)) / (Grav * DirX)); return true; }
	return false;
}

bool SolveTrajectory(PredictCtx& Ctx, const Vector& ExtrPos, float* TravelTime)
{
	Vector Dir = ExtrPos - Ctx.StartPos;
	Vector2D Dir2D = { sqrtf(Dir.x * Dir.x + Dir.y * Dir.y), Dir.z };

	float CurPitch;
	if (!OptimalPitch(Ctx, Dir2D, &CurPitch))
	{
		return false;
	}
	*TravelTime = Dir2D.x / (cosf(CurPitch) * Ctx.BulletSpeed);
	Ctx.AimAngles.y = atan2f(Dir.y, Dir.x);
	Ctx.AimAngles.x = CurPitch;
	return true;
}

bool BulletPredict(PredictCtx& Ctx)
{
	float MAX_TIME = 1.f, TIME_STEP = (1.f / 256.f);
	for (float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP)
	{
		float TravelTime = 1.f;
		Vector ExtrPos = ExtrapolatePos(Ctx, CurrentTime);
		if (!SolveTrajectory(Ctx, ExtrPos, &TravelTime))
		{
			return false;
		}
		if (TravelTime < CurrentTime)
		{
			Ctx.AimAngles = { -RAD2DEG(Ctx.AimAngles.x), RAD2DEG(Ctx.AimAngles.y) };
			return true;
		}
	}
	return false;
}

void NormalizeAngles(QAngle& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

QAngle CalcAngle(Vector& src, Vector& dst)
{
	QAngle angle = QAngle();
	Vector delta = Vector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

	angle.x = atanf(delta.z / hyp) * (180.0f / M_PI);
	angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}

QAngle CalculatePredictionAngle(uintptr_t pLocalPlayer, QAngle  LocalCam, QAngle  LocalSway, Vector TargetBone, Vector TargetAbsVelocity, float smooth) {
	QAngle CalculatedAngles = QAngle(0, 0, 0);
	
	uintptr_t actWeaponID;
	driver->GetAddress<uintptr_t>((void*)(globalLocalPlayer + OFFSET_CURRENTWEAPON), actWeaponID) & 0xFFFF; // offset current weapon
	uintptr_t currentWeapon = GetEntityBase(driver, mod, actWeaponID);
	
	float BulletSpeed;
	float BulletGrav;

	driver->GetAddress<float>((void*)(currentWeapon + OFFSET_BULLETSPEED), BulletSpeed); // offset bullet speed
	driver->GetAddress<float>((void*)(currentWeapon + (OFFSET_BULLETGRAVITY)), BulletGrav); // offset bullet gravity


	Vector StartPos = GetEntityBonePos(driver, globalLocalPlayer, 8);
	//if (StartPos.DistTo(TargetBone) < 75.f * 15)
	 //   StartPos.z += 10.f;
   // else StartPos.z += 5.f;
	if (BulletSpeed > 1.f)
	{
		PredictCtx Ctx;
		Ctx.StartPos = StartPos;
		Ctx.TargetPos = TargetBone;
		Ctx.BulletSpeed = BulletSpeed;// - (BulletSpeed * 0.08);
		Ctx.BulletGravity = BulletGrav;
		Ctx.TargetVel = TargetAbsVelocity;

		if (BulletPredict(Ctx)) {
			CalculatedAngles = QAngle{ Ctx.AimAngles.x, Ctx.AimAngles.y, 0.f };
		}

	}
	if (CalculatedAngles == QAngle(0, 0, 0)) {
		CalculatedAngles = CalcAngle(StartPos, TargetBone);
	}
	CalculatedAngles -= LocalSway - LocalCam;
	NormalizeAngles(CalculatedAngles);
	QAngle Delta = CalculatedAngles - LocalCam;
	NormalizeAngles(Delta);
	QAngle SmoothedAngles = LocalCam + (Delta / smooth);
	SmoothedAngles.z = 0.f;
	return SmoothedAngles;
}

Vector3 PredictPosition(Driver* driv, Driver::Module mod, uint64_t pLocal, Vector3 bonePos, uint64_t pEntity)
{
	uintptr_t actWeaponID;
	driv->GetAddress<uintptr_t>((void*)(pLocal + OFFSET_CURRENTWEAPON), actWeaponID) & 0xFFFF; // offset current weapon
	uintptr_t currentWeapon = GetEntityBase(driv, mod, actWeaponID);

	if (currentWeapon != 0)
	{
		float bulletSpeed;
		driv->GetAddress<float>((void*)(currentWeapon + OFFSET_BULLETSPEED), bulletSpeed); // offset bullet speed
		float bulletGravity;
		driv->GetAddress<float>((void*)(currentWeapon + (OFFSET_BULLETGRAVITY)), bulletGravity); // offset bullet gravity

		if (bulletSpeed > 1.f)
		{
			Vector3 muzzle;
			driv->GetAddress<Vector3>((void*)(pLocal + OFFSET_BULLETSPEED), muzzle); // offset camera pos
			float time = DistTo(bonePos, muzzle) / bulletSpeed;
			bonePos.Z += (700.f * bulletGravity * 0.5f) * (time * time);
			Vector3 vec = Vector3();
			Vector3 velDelta;
			driv->GetAddress<Vector3>((void*)(pEntity + OFFSET_ORIGIN - 0xC), velDelta); // pEntity + Offset Origin - 0xC
			velDelta = velDelta * time;
			bonePos.X += velDelta.X;
			bonePos.Y += velDelta.Y;
			bonePos.Z += velDelta.Z;
		}
	}

	return bonePos;
}

void AimbotMove(AimContext* Ctx, PlayerData player) {

	if (Ctx->closestX != 50000 && Ctx->closestY != 50000)
	{
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			isPlayerLocked = true;
			playerLockedNumber = player.playerIterateNumber;

			Ctx->aX = (Ctx->closestX - Ctx->crosshairX) / Ctx->aSmoothAmount;
			Ctx->aY = (Ctx->closestY - Ctx->crosshairY) / Ctx->aSmoothAmount;

			CURSORINFO ci = { sizeof(CURSORINFO) };
			if (GetCursorInfo(&ci))
			{
				if (ci.flags == 0)
					mouse_event(MOUSEEVENTF_MOVE, Ctx->aX, Ctx->aY, 0, 0);
			}
		}
		else {
			if (isPlayerLocked && playerLockedNumber == player.playerIterateNumber) {
				isPlayerLocked = false;
				playerLockedNumber = -1;
			}
		}
	}
}

Vector3 ClampAngle(Vector3 vecAngle)
{
	Vector3 clampedVector = vecAngle;
	if (clampedVector.X > 89.0f)
	{
		clampedVector.X -= 179.0f;
	}
	if (clampedVector.X < -89.0f)
	{
		clampedVector.X += 179.0f;
	}
	if (clampedVector.Y > 179.0f)
	{
		clampedVector.Y -= 360.0f;
	}
	if (clampedVector.Y < -179.0f)
	{
		clampedVector.Y += 360.0f;
	}
	if (clampedVector.X < -89.0f)
	{
		clampedVector.X = -89.0f;
	}
	if (clampedVector.X > 89.0f)
	{
		clampedVector.X = 89.0f;
	}
	if (clampedVector.Y > 179.0f)
	{
		clampedVector.Y = 179.0f;
	}
	if (clampedVector.Y < -179.0f)
	{
		clampedVector.Y = -179.0f;
	}
	clampedVector.Z = 0.0f;
	return clampedVector;
}

Vector3 NormalizeAngle(Vector3 vecAngle)
{
	Vector3 normalizedAngles = vecAngle;
	if (normalizedAngles.X > 89.0f)
	{
		normalizedAngles.X = 89.0f;
	}
	else if (-89.0f > normalizedAngles.X)
	{
		normalizedAngles.X = -89.0f;
	}

	if (normalizedAngles.Y > 180.0f)
	{
		normalizedAngles.Y -= 360.0f;
	}
	else if (-180.0f > normalizedAngles.Y)
	{
		normalizedAngles.Y += 360.0f;
	}
	normalizedAngles.Z = 0.0f;
	return normalizedAngles;
}

Vector3 FinalizeAngle(Vector3 vecAngle)
{
	return NormalizeAngle(ClampAngle(vecAngle));
}

QAngle FinalQAngle(QAngle Angle)
{
	Vector3 Ang = { Angle.x,Angle.y,Angle.z };
	Vector3 angle = FinalizeAngle(Ang);
	return QAngle(angle.X, angle.Y, angle.Z);
}

double GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	QAngle delta = aimAngle - viewAngle;
	NormalizeAngles(delta);
	return sqrt(pow(delta.x, 2.0f) + pow(delta.y, 2.0f));
}

QAngle GetViewAngle(Driver* driv, uintptr_t pEntityBase)
{
	QAngle viewAngle = QAngle();
	driv->GetAddress<QAngle>((void*)(pEntityBase + OFFSET_VIEWANGLES), viewAngle); // offset view angles
	return viewAngle;
}

float findSmallestElement(float arr[], int n) {
	/* We are assigning the first array element to
	 * the temp variable and then we are comparing
	 * all the array elements with the temp inside
	 * loop and if the element is smaller than temp
	 * then the temp value is replaced by that. This
	 * way we always have the smallest value in temp.
	 * Finally we are returning temp.
	 */
	float temp = arr[0];
	for (int i = 0; i < n; i++) {
		if (temp > arr[i]) {
			temp = arr[i];
		}
	}
	return temp;
}

int CalculateBestBone(Driver* driv, uint64_t pLocal, uint64_t pEntity) {
	int localBone;
	float fovList[101] = {};
	float boneList[101] = {};

	for (int i = 0; i < 100; i++)
	{
		if (i == 73 || i == 0) {

		}
		else {
			auto vecLocalBonePosition = GetEntityBonePos(driv, pLocal, 8);
			Vector vecEntityBonePositionFoV = GetEntityBonePos(driv, pEntity, i);
			auto vecLocalViewAngle = GetViewAngle(driv, pLocal);
			float flBoneFoV = GetFov(vecLocalViewAngle, FinalQAngle(CalcAngle(vecLocalBonePosition, vecEntityBonePositionFoV)));
			int maxFOV = Config.Fov;
			if (flBoneFoV < maxFOV)
			{
				maxFOV = flBoneFoV;
				localBone = i;

				fovList[i] = flBoneFoV;
				boneList[i] = localBone;
			}
		}
	}

	int entry = 0;
	float smallestElement = findSmallestElement(fovList, 100);

	for (int i = 0; i < 100; i++) {
		if (fovList[i] == smallestElement) {
			localBone = boneList[i];
			break;
		}
	}

	return localBone;
}

void Aimbot(Driver* driv, Driver::Module module, uint64_t pEntity, Vector3 entityPosition, uint64_t pLocal, AimContext* Ctx, int index, float xLeft, float xRight, Matrix myMatrix, PlayerData player) {
	Vector3 entAimPos = GetEntityBonePosVec3(driv, pEntity, CalculateBestBone(driv, pLocal, pEntity)); //0 Hips //5 Body //7 Neck //8 Head
	entAimPos = PredictPosition(driv, module, pLocal, entAimPos, pEntity);
	Vector3 w2sEntAimPos = WorldToScreen(entAimPos, myMatrix); if (w2sEntAimPos.Z <= 0.f) return;

	int entX = w2sEntAimPos.X;
	int entY = w2sEntAimPos.Y;

	if (!player.isDown)
	{
		int linkestesX = Ctx->crosshairX - (Config.Fov * 10);
		int rechtestesX = Ctx->crosshairX + (Config.Fov * 10);
		int oberstesY = Ctx->crosshairY - (Config.Fov * 10);
		int unterstesY = Ctx->crosshairY + (Config.Fov * 10);

		if ((entX >= linkestesX && entX <= rechtestesX) && (entY >= oberstesY && entY <= unterstesY)) {
			Ctx->closestX = entX;
			Ctx->closestY = entY;
		}
		else {
			// wenn nicht in FOV, dann alles freigeben
			isPlayerLocked = false;
			playerLockedNumber = -1;
		}
	}
	else {
		if (isPlayerLocked && playerLockedNumber == player.playerIterateNumber) {
			isPlayerLocked = false;
			playerLockedNumber = -1;
		}
	}
}

/// <summary> Prüft nach, ob die angegebene Item ID derzeitig offiziell benutzt wird</summary>
bool IsItemIDValidItem(int itemID) {
	switch (itemID) {
	case 221:
	case 228:
	case 229:
	case 230:
	case 240:
	case 203:
	case 204:
	case 218:
	case 219:
	case 220:
	case 198:
	case 199:
	case 200:
	case 201:
	case 202:
	case 192:
	case 193:
	case 194:
	case 195:
	case 197:
	case 58:
	case 63:
	case 104:
	case 124:
	case 191:
	case 190:
	case 189:
	case 166:
	case 165:
	case 164:
	case 163:
	case 162:
	case 161:
	case 174:
	case 173:
	case 172:
	case 171:
	case 179:
	case 178:
	case 177:
	case 176:
	case 170:
	case 169:
	case 168:
	case 167:
	case 188:
	case 187:
	case 186:
	case 185:
	case 184:
	case 183:
	case 182:
	case 181:
	case 233:
	case 227:
	case 226:
	case 225:
	case 209:
	case 208:
	case 207:
	case 206:
	case 196:
	case 42:
	case 47:
	case 69:
	case 94:
	case 99:
	case 120:
	case 244:
	case 242:
	case 213:
	case 212:
	case 211:
	case 210:
	case 119:
	case 27:
	case 32:
	case 52:
	case 89:
	case 114:
	case 126:
	case 131:
	case 243:
	case 231:
	case 217:
	case 216:
	case 215:
	case 214:
	case 7:
	case 12:
	case 17:
	case 22:
	case 121:
	case 125:
	case 109:
	case 1:
	case 37:
	case 57:
	case 68:
	case 224:
	case 223:
	case 222:
	case 2:
	case 74:
	case 79:
	case 84:
	case 122:
	case 252:
	case 251:
	case 123:
		return true;
	default:
		return false;
	}
	return false;
}

string weaponNameIndexWeapon1 = "";
string weaponNameIndexWeapon2 = "";
int weapon1ModBitFieldCurrent = 0;
int weapon2ModBitFieldCurrent = 0;
bool hasWeapon = false;

struct ObserverStruct {
	int observes[2];
};

void RenderAllItems(int startIndex, int stopIndex, int& weapon1, int& weapon2) {
	if (Config.enableItemESP) {
		for (int i = startIndex; i < stopIndex; i++) {

			uint64_t centity = GetEntityBase(driver, mod, i);

			myItemPlayerBase[i].centity = centity;
			myItemPlayerBase[i].localPlayer = globalLocalPlayer;

			int myLootID = GetLootID(driver, centity);
			SignifierNameStruct signifierName = getSignifierName(driver, centity);
			std::string mySignifierName = std::string(signifierName.signifierName);

			if ((mySignifierName == "prop_survival" || (mySignifierName == "prop_dynamic" && IsLootBox(driver, centity))
				|| mySignifierName == "prop_death_box" || mySignifierName == "weaponx" )) {
				
				myItemPlayerBase[i].isItem = true;
				myItemPlayerBase[i].signifierNameStruct = signifierName;

				if (strcmp(signifierName.signifierName, "prop_dynamic") == 0) {
					myItemPlayerBase[i].name = "Lootbox";
					myItemPlayerBase[i].itemTextColor = colorGreen;
				}
				else if (strcmp(signifierName.signifierName, "prop_death_box") == 0) {
					myItemPlayerBase[i].name = "Deathbox";
					myItemPlayerBase[i].itemTextColor = colorRedDB;
				}
				else if (strcmp(signifierName.signifierName, "weaponx") == 0) {
					myItemPlayerBase[i].isItem = false;
					// Das hier wird nur benutzt, um das 'Smart Item ESP' auszuführen! Hiermit bekommen wir die aktuellen Waffen des Spielers
					// und prüfen nach, welche Aufsätze drauf sind
					int m_weaponOwner = 0;
					int m_modBitfieldCurrent = 0;
					int m_modBitfieldInternal = 0;
					int m_modBitfieldFromPlayer = 0;
					int m_ammoInClip = 0;

					driver->GetAddress<int>((void*)(centity + 0x1690), m_weaponOwner);

					if (GetWeaponOwner(driver, mod) == m_weaponOwner) {
						int weaponNameIndex;
						driver->GetAddress<int>((void*)(centity + OFFSET_WEAPONNAMEINDEX), weaponNameIndex);

						if (weaponNameIndex > 0) {
							bool writeInWeapon1 = true;

							int activeState = 0;
							driver->GetAddress<int>((void*)(centity + 0x16c0), activeState); // m_ActiveState=0x16c0

							if (activeState == 2) {
								hasWeapon = true;
							}

							if (weapon1 == 1) {
								weapon2 = 1;
								writeInWeapon1 = false;
							}
							else {
								weapon1 = 1;
							}

							driver->GetAddress<int>((void*)(centity + OFFSET_CURRENTATTACHMENTS), m_modBitfieldCurrent);

							if (writeInWeapon1) {
								weaponNameIndexWeapon1 = GetModelName(driver, centity);
								weapon1ModBitFieldCurrent = m_modBitfieldCurrent;
							}
							else {
								weaponNameIndexWeapon2 = GetModelName(driver, centity);
								weapon2ModBitFieldCurrent = m_modBitfieldCurrent;
							}
						}
					}
				}
				else {
					if (IsItemIDValidItem(myLootID)) {
						myItemPlayerBase[i].lootID = myLootID;
					}
					else {
						//myItemPlayerBase[i].lootID = myLootID;
						myItemPlayerBase[i].isItem = false;
					}
				}

				if (myItemPlayerBase[i].isItem) {
					Vector3 position = GetEntityPlayerPosition(driver, myItemPlayerBase[i].centity);
					myItemPlayerBase[i].position = position;
				}
			}
			else {
				myItemPlayerBase[i].isItem = false;
			}
		}
	}
}

void Triggerbot(PlayerData player) {
	if (Config.enableTriggerbot && GetAsyncKeyState(VK_RBUTTON) && !(GetAsyncKeyState(VK_LBUTTON)) && player.visible && !player.isDown) {

		uintptr_t actWeaponID;
		driver->GetAddress<uintptr_t>((void*)(globalLocalPlayer + OFFSET_CURRENTWEAPON), actWeaponID) & 0xFFFF; // offset current weapon
		uintptr_t currentWeapon = GetEntityBase(driver, mod, actWeaponID);

		if (currentWeapon != 0 || hasWeapon) {
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);

			int cursorX = screenWidth / 2;
			int cursorY = screenHeight / 2;

			// prüfen ob die Mitte des Bildschirmes sich zwischen ganz links und ganz rechts vom Spieler befindet

			int playerMiddleX = (player.middle + (player.width / 2));
			int playerMiddleY = (player.w2sHead.Y + (player.height / 2));
			int toleranceXY = 100 / player.realDistance;
			// 1 m = 50 Pixel Toleranz50
			// 10m = Toleranz von 5 Pixel
			// 20m = Toleranz von 2,5 Pixel
			// 5m = Toleranz von 7,5 Pixel

			if (cursorX >= playerMiddleX - toleranceXY && cursorX <= (playerMiddleX + toleranceXY)) {
				// prüfen ob die Mitte des Bildschirmes sich zwischen ganz oben und ganz unten vom Spieler befindet
				if (cursorY >= (player.w2sHead.Y) && cursorY <= (player.w2sHead.Y + player.height)) {
					// dann automatisch Links klick!
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(1);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}
			}
		}
	}
}

void SetViewQAngle(QAngle vecViewAngle)
{
	driver->SetAdress((void*)(globalLocalPlayer + OFFSET_VIEWANGLES), vecViewAngle);
}

void MemoryAimbot(PlayerData enemy) {
	int LocalBone = CalculateBestBone(driver, globalLocalPlayer, enemy.centity);
	Vector vecLocalBonePosition = GetEntityBonePos(driver, globalLocalPlayer, 8);
	Vector vecEntityBonePositionFoV = GetEntityBonePos(driver, enemy.centity, LocalBone);
	auto vecLocalViewAngle = GetViewAngle(driver, globalLocalPlayer);
	float flCalculatedFov = GetFov(vecLocalViewAngle, FinalQAngle(CalcAngle(vecLocalBonePosition, vecEntityBonePositionFoV)));
	float localSmooth = Config.smoothness;
	float dynamicFOV = Config.Fov;

	if (IsPlayerZooming()) {
		dynamicFOV = dynamicFOV * 0.50; // wenn Spieler zoomed, nur noch 50% des FOV's nehmen!
	}

	if (flCalculatedFov > (dynamicFOV))
		return;

	// ranged smooth
	// fov based smooth

	/*if (CFG.Safebot)
	{
		if (flCalculatedFov < (1 - ((flDistance / 100) / 10))) continue;
	}*/

	/*if (CFG.RandomizeSmoothness)
	{
		localSmooth = (CFG.MinSmooth + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (CFG.flSmooth - CFG.MinSmooth)))) * 1.2;
	}
	if (CFG.DyanamicSmooth)
	{
		if (flCalculatedFov > 1)
		{
			localSmooth += 37.f;
			localSmooth = localSmooth / (flCalculatedFov / 4);
		}
	}*/
	/*if (CFG.bRandomBones)
	{
		LocalBone = globalbone;
	}*/

	auto absVelocity = GetEntityAbsVelocity(driver, enemy.centity);
	absVelocity *= Config.smoothness / 40.f;
	Vector vecVelocity = { absVelocity.X, absVelocity.Y, absVelocity.Z };
	QAngle vecAimAngle = CalculatePredictionAngle(globalLocalPlayer, GetViewAngle(driver, globalLocalPlayer), GetEntitySwayAngle(globalLocalPlayer), GetEntityBonePos(driver, enemy.centity, LocalBone), vecVelocity, localSmooth * 1.f);
	if (vecAimAngle.x != 0 && vecAimAngle.y != 0)
	{
		Sleep(1);
		SetViewQAngle(vecAimAngle);
	}
}

void RenderEsp(Driver* myDriver, Driver::Module myModule, int dwEntity) {
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	for (int i = 0; i < 61; i++) {
		// ---------------------------------------------------------------
		// ENTITY BASE CODE	
		// ---------------------------------------------------------------
		myPlayerBase[i].playerIterateNumber = i;

		uint64_t centity = GetEntityBase(myDriver, myModule, i);
		uint64_t localPlayer = GetLocalPlayer(myDriver, myModule);
		globalLocalPlayer = localPlayer;

		myPlayerBase[i].centity = centity;
		myPlayerBase[i].localPlayer = localPlayer;

		if (centity != 0 && localPlayer == centity) {
			myOverlay.SetShieldHelmet(GetArmorType(driver, centity), GetHelmetType(driver, centity));
		}

		if (centity != 0 && localPlayer != centity && IsPlayer(myDriver, centity) && IsEnemy(myDriver, centity, myModule)) {
			myPlayerBase[i].visibleCount = myPlayerBase[i].visibleCount + 1;
			myPlayerBase[i].isPlayer = true;
			myPlayerBase[i].isEnemy = true;
			myPlayerBase[i].modelName = GetModelName(driver, centity);

			Vector3 localPlayerPosition = GetLocalPlayerPosition(myDriver, localPlayer);
			Vector3 entityPlayerPosition = GetEntityPlayerPosition(myDriver, centity);

			myPlayerBase[i].localPlayerPosition = localPlayerPosition;
			myPlayerBase[i].entityPlayerPosition = entityPlayerPosition;

			float distance = GetDistance(localPlayerPosition, entityPlayerPosition);
			float realDistance = distance / 40;

			myPlayerBase[i].distance = distance;
			myPlayerBase[i].realDistance = realDistance;

			if (distance > 0 && realDistance < Config.maxDistance) {
				string charName = GetModelName(driver, centity);

				auto headPosition = GetEntityBonePos(myDriver, centity, 8);
				Vector3 w2sHead = WorldToScreen({ headPosition.x, headPosition.y, headPosition.z }, myMatrix);
				Vector3 w2sBase = WorldToScreen(GetEntityPositionVec3(myDriver, centity), myMatrix);

				myPlayerBase[i].headPosition = headPosition;
				myPlayerBase[i].w2sHead = w2sHead;
				myPlayerBase[i].w2sBase = w2sBase;

				if ((w2sHead.X < screenWidth || w2sHead.Y < screenHeight) && ((w2sHead.X > 0 && w2sHead.Y > 0) && (w2sHead.Z > 0 && w2sBase.Z > 0))) {
					int health = GetHealth(myDriver, centity);
					int shealth = GetShieldHealth(myDriver, centity);
					int sMaxHealth = GetShieldMaxHealth(myDriver, centity);
					int armorType = GetArmorType(myDriver, centity);

					myPlayerBase[i].health = health;
					myPlayerBase[i].shealth = shealth;
					myPlayerBase[i].sMaxHealth = sMaxHealth;
					myPlayerBase[i].armorType = armorType;
				
					// Auslesen des Spielernamens wenn der Spieler erstmalig abgesprungen, und in Sichtweite ist
					if (myPlayerBase[i].firstTimeNameRead && myPlayerBase[i].visibleCount > 50) {
						string playerName = GetName(driver, i, mod);
						myPlayerBase[i].name = playerName;
						myPlayerBase[i].firstTimeNameRead = false;
					}

					float height = abs(abs(w2sHead.Y) - abs(w2sBase.Y));
					float width = height / 2.f;
					float middle = w2sBase.X - (width / 2.f); // x -> links

					float box_height = abs((w2sHead.Y - w2sBase.Y));
					float box_width = abs(box_height / 2.f);

					myPlayerBase[i].height = box_height;
					myPlayerBase[i].width = box_width;
					myPlayerBase[i].middle = middle;

					float boxThickness = 3;

					myPlayerBase[i].boxThickness = boxThickness;

					bool visible = IsVisible(myDriver, centity, i);
					myPlayerBase[i].visible = visible;

					bool isKnocked = IsDowned(myDriver, centity);
					myPlayerBase[i].isDown = isKnocked;

					// AIMBOT
					if (Config.bAimbot && visible) {
						if (playerLockedNumber >= 0) {
							if ((!myPlayerBase[playerLockedNumber].visible) || (myPlayerBase[playerLockedNumber].distance > Config.maxAimDistance) ||
								myPlayerBase[playerLockedNumber].health == 0 || !(GetAsyncKeyState(VK_RBUTTON))) {
								// freigeben falls nötig!
								isPlayerLocked = false;
								playerLockedNumber = -1;
							}
						}

						if (!isPlayerLocked || (isPlayerLocked && playerLockedNumber == i)) {
							//Aimbot Context Reset
							if (GetAsyncKeyState(VK_RBUTTON) && myPlayerBase[i].realDistance <= Config.maxAimDistance) {
								AimContext aimCtx; aimCtx.closestX = 50000; aimCtx.closestY = 50000; aimCtx.FOV = Config.Fov; aimCtx.aSmoothAmount = Config.smoothness * 2;
								Aimbot(myDriver, myModule, centity, entityPlayerPosition, localPlayer, &aimCtx, i, middle, middle + width, myMatrix, myPlayerBase[i]);
								AimbotMove(&aimCtx, myPlayerBase[i]);
							}

							//if (GetAsyncKeyState(VK_RBUTTON)) {
							//	MemoryAimbot(myPlayerBase[i]);
							//}

							Triggerbot(myPlayerBase[i]);
						}
					}
				}
			}
		}
		else {
			myPlayerBase[i].isPlayer = false;
			myPlayerBase[i].isEnemy = false;
			myPlayerBase[i].firstTimeNameRead = true;
		}
	}

	bool foundOnePlayerOrEnemy = false;
	for (int j = 0; j < 61; j++) {
		if (myPlayerBase[j].isPlayer == true || myPlayerBase[j].isEnemy == true) {
			foundOnePlayerOrEnemy = true;
		}
	}

	if (!foundOnePlayerOrEnemy) {
		for (int j = 0; j < 65001; j++) {
			myItemPlayerBase[j].centity = 0;
			myItemPlayerBase[j].distance = 0;
			myItemPlayerBase[j].isItem = false;
			myItemPlayerBase[j].localPlayer = 0;
			myItemPlayerBase[j].localPlayerPosition = Vector3();
			myItemPlayerBase[j].lootID = 0;
			myItemPlayerBase[j].myMatrix = Matrix();
			myItemPlayerBase[j].name = "";
			myItemPlayerBase[j].position = Vector3();
			myItemPlayerBase[j].realDistance = 0;
			myItemPlayerBase[j].signifierNameStruct = SignifierNameStruct();
			myItemPlayerBase[j].w2sBase = Vector3();
		}
	}
}

void renderEspThread() {
	//bool setMatrix = true;
	
	// SO WIE ES HIER IST: 22 MS für ITEM ESP!!
	//int startIndex = 0;
	//int endIndex = 1000;

	//auto t1 = std::chrono::high_resolution_clock::now();
	//while (true)
	//{
	//	myMatrix = GetMatrix(driver, mod);

	//	RenderEsp(driver, mod, 1);
	//	myOverlay.SetPlayerBase(myPlayerBase);

	//	// Item ESP funktioniert wie folgt: wir iterieren pro Durchgang nur 100 Items bis wir einmal über die 65k durch sind
	//	// und fangen dann wieder von vorne an!
	//	if (Config.enableItemESP) {
	//		RenderAllItems(startIndex, endIndex);
	//		myOverlay.SetItemBase(myItemPlayerBase);
	//	}

	//	if (startIndex + 1000 <= 10000 && endIndex + 10000 <= 11000) {
	//		startIndex = startIndex + 1000;
	//		endIndex = endIndex + 1000;
	//	}
	//	else {
	//		startIndex = 0;
	//		endIndex = 1000;

	//		auto t2 = std::chrono::high_resolution_clock::now();

	//		/* Getting number of milliseconds as an integer. */
	//		auto ms_int = duration_cast<milliseconds>(t2 - t1);

	//		cout << "Needed time: " << ms_int.count() << endl;

	//		t1 = std::chrono::high_resolution_clock::now();
	//	}
	//}



	int startIndex = 0;
	int endIndex = 500;
	int weapon1 = 0;
	int weapon2 = 0;

	//auto t1 = std::chrono::high_resolution_clock::now();
	while (true)
	{
		myMatrix = GetMatrix(driver, mod);

		RenderEsp(driver, mod, 1);

		myOverlay.SetMatrixLocalPlayer(myMatrix, GetLocalPlayerPosition(driver, globalLocalPlayer));
		myOverlay.SetPlayerBase(myPlayerBase);

		// Item ESP funktioniert wie folgt: wir iterieren pro Durchgang nur 100 Items bis wir einmal über die 65k durch sind
		// und fangen dann wieder von vorne an!
		if (Config.enableItemESP) {
			RenderAllItems(startIndex, endIndex, weapon1, weapon2);
			/*RenderAllItems(startIndex, endIndex);
			myOverlay.SetItemBase(myItemPlayerBase);*/

			myOverlay.SetItemBase(myItemPlayerBase, startIndex, endIndex);

			if (startIndex + 500 <= 65000 && endIndex + 500 <= 65000) {
				startIndex = startIndex + 500;
				endIndex = endIndex + 500;
			}
			else {
				startIndex = 0;
				endIndex = 500;

				weapon1 = 0;
				weapon2 = 0;

				myOverlay.SetCurrentWeapon(weaponNameIndexWeapon1, weaponNameIndexWeapon2, weapon1ModBitFieldCurrent, weapon2ModBitFieldCurrent);

				weaponNameIndexWeapon1 = "";
				weaponNameIndexWeapon2 = "";
				weapon1ModBitFieldCurrent = 0;
				weapon2ModBitFieldCurrent = 0;

				hasWeapon = false;



				//auto t2 = std::chrono::high_resolution_clock::now();

				///* Getting number of milliseconds as an integer. */
				//auto ms_int = duration_cast<milliseconds>(t2 - t1);

				//cout << "Needed time: " << ms_int.count() << endl;

				//t1 = std::chrono::high_resolution_clock::now();
			}
		}
	}
}

std::string MyRandomString(const int len)
{
	const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

	std::string str(len, 0);
	for (auto& it : str)
		it = alpha_numeric[distribution(generator)];

	return str;
}

bool startOnce = true;

int main() {
	std::string myString = MyRandomString(16);
	std::wstring stemp = std::wstring(myString.begin(), myString.end());
	SetConsoleTitle(stemp.c_str());
	printf("[!] Open driver connection: ");
	if (driver->Init(FALSE)) {
		printf("Success!\n");

		while (driver->GetProcessId(L"r5apex.exe") == 0) {
			// Warten
		}

		HWND apexHwnd = NULL;
		while (apexHwnd == NULL) {
			apexHwnd = FindWindow(NULL, L"Apex Legends");
		}

		printf(" Injecting. ");

		driver->Attach(L"r5apex.exe");
		mod = driver->GetModuleBase(L"r5apex.exe");
		
		myOverlay = Overlay();
		if (!myOverlay.InitWindow(apexHwnd)) {
			return 0;
		}

		if (!myOverlay.DirectXInit()) {
			return 0;
		}

		if (Configuration::FileExists(Config.chConfigFile))
		{
			Configuration::UpdateConfigFromFile();
		}
		else
		{
			Configuration::WriteToConfigFile();
			Configuration::UpdateConfigFromFile();
		}

		std::thread espOverlay = std::thread(espThread); // Overlay zeichnen ESP
		std::thread renderEspThreadM = std::thread(renderEspThread); // Auslesen der Daten ESP
		
		while (true) {
			
		}
	}
	printf("Failed!\n");
	system("pause");
	return 1;
}
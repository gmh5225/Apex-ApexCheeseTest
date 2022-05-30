#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "stdafx.h"
#include "vector.h"
#include "Structs.h"
#include "driver.h"
#include <string>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include <sstream>
#include "XorStr.h"
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include "Config.h"
#include "ksk.h"
#include "unknownController.h"
#include "Drawings.h"
#include "PlayerData.h"
#include "WeaponAttachments.h"

#define GREEN ImColor(0, 255, 0)
#define RED ImColor(255, 0, 0)
#define BLUE ImColor(0, 0, 255)
#define ORANGE ImColor(255, 165, 0)
#define WHITE ImColor(255, 255, 255)

static bool fontIsInstalled = false;
static int currentMenu = 0;
static bool pushCalled = false;
static bool executedOnce = false;

extern HWND overlayWindow;
extern IDirect3D9Ex* p_Object;
extern IDirect3DDevice9Ex* p_Device;
extern D3DPRESENT_PARAMETERS p_Params;
extern ID3DXLine* p_Line;
extern POINT windowWH;

typedef struct visuals
{
	bool box = true;
	bool line = true;
	bool distance = true;
	bool healthbar = true;
	bool shieldbar = true;
	bool name = true;
}visuals;










class Overlay
{
public:
	LONG nv_default = WS_POPUP | WS_CLIPSIBLINGS;
	LONG nv_default_in_game = nv_default | WS_DISABLED;
	LONG nv_edit = nv_default_in_game | WS_VISIBLE;
	LONG nv_ex_default = WS_EX_TOOLWINDOW;
	LONG nv_ex_edit = nv_ex_default | WS_EX_LAYERED | WS_EX_TRANSPARENT;
	LONG nv_ex_edit_menu = nv_ex_default | WS_EX_TRANSPARENT;
	bool bESP;
	bool bItemGlow;
	bool bPlayerGlow;
	bool bAimbot;
	float flMaxDist;
	float flsmooth;
	float flFov;
	int dwbone;
	int dwwidth;
	int dwheight;
	bool bLeftclick = false;
	bool bIns = false;
	bool bMenu = false;
	visuals v;
	bool bActive;
	HWND overlayHWND;
	Driver* myDriver;
	Driver::Module myModule;
	void RenderEsp(int dwEntity, Matrix myMatrix);
	void ESPMenu();
	void AimbotMenu();
	bool InitWindow(HWND apexhwnd);
	bool DirectXInit();
	void DrawRenderMenu();
	void DrawItemMenu();
	void DirectXShutdown();
	void StartAimbot(Driver* driv, Driver::Module mod);
	void InitVariables(Driver* driv, Driver::Module mod);
	void GetDriverData();
	void SetPlayerBase(PlayerData newPlayerBase[62]);
	void SetItemBase(ItemData newPlayerBase[66001], int startIndex, int endIndex);
	void SetMatrixLocalPlayer(Matrix newMatrix, Vector3 localPlayerPos);
	void SetCurrentWeapon(string weaponIndex1, string weaponIndex2, int modBitField1, int modBitField2);
	void SetShieldHelmet(int shieldType, int helmetType);

private:
	bool isInitialized = true;
	bool isVisible = true;
};
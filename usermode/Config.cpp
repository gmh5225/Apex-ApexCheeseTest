#include "Config.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>

using namespace std;

bool Configuration::FileExists(const char* chDir)
{
	return std::filesystem::exists(chDir);
}

bool Configuration::WriteToConfigFile()
{
	if (!std::filesystem::exists(Config.chConfigDirectory))
	{
		if (!std::filesystem::create_directory(Config.chConfigDirectory))
		{
			return false;
		}
	}
	if (std::filesystem::exists(Config.chConfigDirectory))
	{
		if (!FileExists(Config.chConfigFile))
		{
			std::ofstream ofsOutfile(Config.chConfigFile);
			ofsOutfile << ("FOV=20.0\nSmoothness=17.0\nEnable_Aimbot=TRUE\nEnable_ESP=TRUE\nDraw_FOV=TRUE\nMax_Distance=300.0\nShow_Distance=TRUE\nShow_Names=TRUE\nShow_Knocked=TRUE\nEnable_ItemESP=TRUE\nMax_ItemDistance=50.0\nMax_AimDistance=100.0\nEnable_Triggerbot=TRUE\nSmart_ItemESP=TRUE");
			ofsOutfile.close();
			return true;
		}
		else
		{			
			const char* EnableAimbot = "FALSE";
			const char* EnableESP = "FALSE";
			const char* DrawFOV = "FALSE";
			const char* ShowDistance = "FALSE";
			const char* ShowNames = "FALSE";
			const char* ShowKnocked = "FALSE";
			const char* EnableItemESP = "FALSE";
			const char* EnableTriggerbot = "FALSE";
			const char* EnableSmartItemESP = "FALSE";

			if (Config.bAimbot) EnableAimbot = "TRUE";
			if (Config.enableESP) EnableESP = "TRUE";
			if (Config.DrawFoV) DrawFOV = "TRUE";
			if (Config.showDistance) ShowDistance = "TRUE";
			if (Config.showNames) ShowNames = "TRUE";
			if (Config.showKnocked) ShowKnocked = "TRUE";
			if (Config.enableItemESP) EnableItemESP = "TRUE";
			if (Config.enableTriggerbot) EnableTriggerbot = "TRUE";
			if (Config.enableSmartItemESP) EnableSmartItemESP = "TRUE";

			string toWrite = "";
			toWrite += string("FOV=") + to_string(Config.Fov) + string("\n");
			toWrite += string("Smoothness=") + to_string(Config.smoothness) + string("\n");
			toWrite += string("Enable_Aimbot=") + string(EnableAimbot) + string("\n");
			toWrite += string("Enable_ESP=") + string(EnableESP) + string("\n");
			toWrite += string("Draw_FOV=") + string(DrawFOV) + string("\n");
			toWrite += string("Max_Distance=") + to_string(Config.maxDistance) + string("\n");
			toWrite += string("Show_Distance=") + string(ShowDistance) + string("\n");
			toWrite += string("Show_Names=") + string(ShowNames) + string("\n");
			toWrite += string("Show_Knocked=") + string(ShowKnocked) + string("\n");
			toWrite += string("Enable_ItemESP=") + string(EnableItemESP) + string("\n");
			toWrite += string("Max_ItemDistance=") + to_string(Config.maxItemDistance) + string("\n");
			toWrite += string("Max_AimDistance=") + to_string(Config.maxAimDistance) + string("\n");
			toWrite += string("Enable_Triggerbot=") + string(EnableTriggerbot) + string("\n");
			toWrite += string("Smart_ItemESP=") + string(EnableTriggerbot) + string("\n");

			std::ofstream ofsOutfile(Config.chConfigFile);
			ofsOutfile << toWrite;
			ofsOutfile.close();
			return true;
		}
	}

	return false;
}

bool Configuration::UpdateConfigFromFile()
{
	string strContent;
	ifstream inFile(Config.chConfigFile);
	if (inFile)
	{
		std::string strContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		char EnableAimbot[64] = "FALSE";
		char EnableESP[64] = "FALSE";
		char DrawFOV[64] = "FALSE";
		char ShowDistance[64] = "FALSE";
		char ShowNames[64] = "FALSE";
		char ShowKnocked[64] = "FALSE";
		char EnableItemESP[64] = "FALSE";
		char EnableTriggerbot[64] = "FALSE";
		char EnableSmartItemESP[64] = "FALSE";

		sscanf(strContent.c_str(), "FOV=%f\nSmoothness=%f\nEnable_Aimbot=%s\nEnable_ESP=%s\nDraw_FOV=%s\nMax_Distance=%f\nShow_Distance=%s\nShow_Names=%s\nShow_Knocked=%s\nEnable_ItemESP=%s\nMax_ItemDistance=%f\nMax_AimDistance=%f\nEnable_Triggerbot=%s\nSmart_ItemESP=%s", &Config.Fov, &Config.smoothness, &EnableAimbot, &EnableESP, &DrawFOV, &Config.maxDistance, &ShowDistance, &ShowNames, &ShowKnocked, &EnableItemESP, &Config.maxItemDistance, &Config.maxAimDistance, &EnableTriggerbot, &EnableSmartItemESP);

		if (strcmp(EnableAimbot, "TRUE") == 0)
			Config.bAimbot = true;
		else
			Config.bAimbot = false;
		
		if (strcmp(EnableESP, "TRUE") == 0)
			Config.enableESP = true;
		else
			Config.enableESP = false;

		if (strcmp(DrawFOV, "TRUE") == 0)
			Config.DrawFoV = true;
		else
			Config.DrawFoV = false;

		if (strcmp(ShowDistance, "TRUE") == 0)
			Config.showDistance = true;
		else
			Config.showDistance = false;

		if (strcmp(ShowNames, "TRUE") == 0)
			Config.showNames = true;
		else
			Config.showNames = false;

		if (strcmp(ShowKnocked, "TRUE") == 0)
			Config.showKnocked = true;
		else
			Config.showKnocked = false;

		if (strcmp(EnableItemESP, "TRUE") == 0)
			Config.enableItemESP = true;
		else
			Config.enableItemESP = false;

		if (strcmp(EnableTriggerbot, "TRUE") == 0)
			Config.enableTriggerbot = true;
		else
			Config.enableTriggerbot = false;

		if (strcmp(EnableSmartItemESP, "TRUE") == 0)
			Config.enableSmartItemESP = true;
		else
			Config.enableSmartItemESP = false;
		
		inFile.close();
		return true;
	}
	return false;
}
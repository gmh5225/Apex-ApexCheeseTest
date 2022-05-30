#pragma once
#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "imgui/imgui.h"
#include "Singleton.h"

inline namespace Configuration
{
	class Settings : public Singleton<Settings>
	{
	public:

		const char* chConfigDirectory = "C:/Test/";
		const char* chConfigFile = "C:/Test/Config.txt";

		bool showKnocked = true;
		bool showNames = true;
		bool showDistance = true;
		float maxDistance = 300.f;
		float maxItemDistance = 50.f;
		bool visibilityCheck = true;
		float Fov = 20.f;
		bool DrawFoV = true;
		bool RandomizeSmoothness = true;
		float flSmooth = 60.f;
		float MinSmooth = 50.f;
		bool bClosestBone = true;
		int dwAimKey = 0x02; // rechte Maustaste
		int bone = 2;
		bool bAimbot = true;
		float smoothness = 17.f;
		bool enableESP = true;
		bool enableItemESP = false;
		float maxAimDistance = 100.f;
		bool enableTriggerbot = true;
		bool enableSmartItemESP = true;
	};
#define Config Configuration::Settings::Get()
	bool FileExists(const char* chDir);
	bool WriteToConfigFile();
	bool UpdateConfigFromFile();
}
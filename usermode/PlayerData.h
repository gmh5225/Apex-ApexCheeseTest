#pragma once

class PlayerData
{
public:
	bool isLocalPlayer = false;
	Vector3 localPlayerPosition = Vector3();
	Vector3 entityPlayerPosition = Vector3();
	float distance = 0.f;
	float realDistance = 0.f;
	Vector headPosition = Vector();
	Vector3 w2sHead = Vector3();
	Vector3 w2sBase = Vector3();
	int health = 0;
	int shealth = 0;
	int sMaxHealth = 0;
	string name = "";
	float height = 0.f;
	float width = 0.f;
	float middle = 0.f; // x -> links
	float boxThickness = 3;
	bool visible = false;
	uint64_t centity = 0;
	uint64_t localPlayer = 0;
	bool isPlayer = false;
	bool isEnemy = false;
	bool firstTimeNameRead = true;
	INT64 visibleCount = 0;
	bool isDown = false;
	int armorType = 0;
	bool isItem = false;
	string modelName = "";
	int lootID = 0;
	D3DCOLOR itemTextColor = D3DCOLOR_ARGB(255, 245, 103, 145);
	int playerIterateNumber = 0;

private:
	
};

class ItemData
{
public:
	float distance = 0.f;
	float realDistance = 0.f;
	Vector3 w2sBase = Vector3();
	std::string name = "";
	uint64_t centity = 0;
	uint64_t localPlayer = 0;
	bool isItem = false;
	int lootID = 0;
	D3DCOLOR itemTextColor = D3DCOLOR_ARGB(255, 245, 103, 145);
	Vector3 position = Vector3();
	Matrix myMatrix = Matrix();
	Vector3 localPlayerPosition = Vector3();
	SignifierNameStruct signifierNameStruct = SignifierNameStruct();
	string modelName = "";

private:

};
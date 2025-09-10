#pragma once
#include <iostream>
#include <fstream>
#include <string>

#define SAVE_FILENAME "savedata.save"
#define WEAPON_DIVIDER "@@@"
#define INVENTORY_DIVIDER "###"
#define ITEM_DIVIDER "$$$"

// 전방 선언
class Weapon;
class Item;
class HealthPotion;
class AttackBoost;
class Character;

using namespace std;

class SaveLoadManager
{
public:
    bool SaveGame(Character* _player);
    bool LoadGame(Character* _player);
    bool saveDeleter();

private:
    // const string WEAPON_DIVIDER = "@@@";
    // const string INVENTORY_DIVIDER = "###";
	// const string SAVE_FILE = "savefile.txt";
};


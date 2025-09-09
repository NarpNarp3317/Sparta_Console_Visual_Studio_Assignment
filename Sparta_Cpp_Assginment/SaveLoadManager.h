#pragma once
#include <iostream>
#include <fstream>
#include <string>

#define SAVE_FILENAME "savedata.save"
#define WEAPON_DIVIDER "@@@"
#define INVENTORY_DIVIDER "###"
#define ITEM_DIVIDER "$$$"

// ���� ����
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

    void saveToNote(const std::string& filename, const std::string& content) {
        // ofstream�� ���Ͽ� ���⸦ ���� Ŭ����
        std::ofstream file(filename);

        if (file.is_open()) {
            file << content; // ���Ͽ� content�� ���ϴ�.
            file.close();    // ������ �ݽ��ϴ�.
            std::cout << "�޸��忡 ���������� �����߽��ϴ�." << std::endl;
        }
        else {
            std::cerr << "����: ������ �� �� �����ϴ�." << std::endl;
        }
    }

    std::string loadFromNote(const std::string& filename) {
        // ifstream�� ���Ͽ��� �б⸦ ���� Ŭ����
        std::ifstream file(filename);
        std::string content;
        std::string line;

        if (file.is_open()) {
            while (std::getline(file, line)) { // ������ ������ �� �پ� �н��ϴ�.
                content += line + "\n";
            }
            file.close();
            std::cout << "�޸��忡�� ���������� �ҷ��Խ��ϴ�." << std::endl;
        }
        else {
            std::cerr << "����: ������ �� �� �����ϴ�." << std::endl;
        }
        return content;
    }

private:
    // const string WEAPON_DIVIDER = "@@@";
    // const string INVENTORY_DIVIDER = "###";
	// const string SAVE_FILE = "savefile.txt";
};


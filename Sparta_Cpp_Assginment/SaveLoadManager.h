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

    void saveToNote(const std::string& filename, const std::string& content) {
        // ofstream은 파일에 쓰기를 위한 클래스
        std::ofstream file(filename);

        if (file.is_open()) {
            file << content; // 파일에 content를 씁니다.
            file.close();    // 파일을 닫습니다.
            std::cout << "메모장에 성공적으로 저장했습니다." << std::endl;
        }
        else {
            std::cerr << "오류: 파일을 열 수 없습니다." << std::endl;
        }
    }

    std::string loadFromNote(const std::string& filename) {
        // ifstream은 파일에서 읽기를 위한 클래스
        std::ifstream file(filename);
        std::string content;
        std::string line;

        if (file.is_open()) {
            while (std::getline(file, line)) { // 파일의 내용을 한 줄씩 읽습니다.
                content += line + "\n";
            }
            file.close();
            std::cout << "메모장에서 성공적으로 불러왔습니다." << std::endl;
        }
        else {
            std::cerr << "오류: 파일을 열 수 없습니다." << std::endl;
        }
        return content;
    }

private:
    // const string WEAPON_DIVIDER = "@@@";
    // const string INVENTORY_DIVIDER = "###";
	// const string SAVE_FILE = "savefile.txt";
};


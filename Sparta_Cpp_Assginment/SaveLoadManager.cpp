#include "SaveLoadManager.h"
#include "Character.h"

bool SaveLoadManager::SaveGame(Character* _player)
{
	if (_player == nullptr)
	{
		std::cerr << "Error: Player is null, cannot save game." << std::endl;
		return false;
	}
	std::ofstream saveFile(SAVE_FILENAME);
	if (!saveFile.is_open())
	{
		std::cerr << "Error: Could not open save file." << std::endl;
		return false;
	}
	
	/// CHARACTER DATA ///
	saveFile << _player->getName() << endl;
	saveFile << _player->getHealth() << endl;
	saveFile << _player->getMaxHealth() << endl;
	saveFile << _player->getBaseAttack() << endl;
	saveFile << _player->getAttack() << endl;
	saveFile << _player->getLevel() << endl;
	saveFile << _player->getExperience() << endl;
	saveFile << _player->getGold() << endl;

	/// CHARACTER EQUIPPED DATA ///
	//saveFile << _player->getEquippedWeapon() << "DIVISION_WORD\n";
	//

	//const auto& inventory = _player->getInventory();
	//saveFile << inventory.size() << "\n"; // Save inventory size
	//for (const auto& item : inventory)
	//{
	//	saveFile << item << "\n"; // Assuming item can be represented as a string
	//}

	saveFile.close();
	std::cout << "Game saved successfully." << std::endl;


	return true;
}

bool SaveLoadManager::LoadGame(Character* _player)
{
	std::ifstream loadFile(SAVE_FILENAME);
	if (!loadFile.is_open())
			{
		std::cerr << "Error: Could not open load file." << std::endl;
		return false;
	}
	else
	{
		vector<string> data;
		std::string line;

		
		while (std::getline(loadFile, line)) { // 파일의 내용을 한 줄씩 읽습니다.
			cout << line << endl;
			data.push_back(line);
		}
		loadFile.close();
	

		_player->setName(data[0]);
		_player->setHealth(stoi(data[1]));
		_player->setMaxHealth(stoi(data[2]));
		_player->setBaseAttack(stoi(data[3]));
		_player->setAttack(stoi(data[4]));
		_player->setLevel(stoi(data[5]));
		_player->setExperience(stoi(data[6]));
		_player->setGold(stoi(data[7]));


	}
	return true;
}
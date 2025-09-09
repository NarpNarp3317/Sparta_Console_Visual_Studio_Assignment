#include "SaveLoadManager.h"
#include "Character.h"
#include "Weapon.h"
#include "Item.h"
#include "AttackBoost.h"
#include "HealthPotion.h"

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
	
	/// 장비중인 무기 있을 시 저장
	/// equimentWeapon Divider///
	if (_player->getEquippedWeapon())
	{
		saveFile << WEAPON_DIVIDER << endl;
		saveFile << _player->getEquippedWeapon()->getName() << endl;
		saveFile << _player->getEquippedWeapon()->getPrice() << endl;
		saveFile << _player->getEquippedWeapon()->getDamage() << endl;
		saveFile << (_player->getEquippedWeapon()->isUsable() ? "1" : "0") << endl;
		saveFile << (_player->getEquippedWeapon()->isConsumable() ? "1" : "0") << endl;
		saveFile << _player->getEquippedWeapon()->getDescription() << endl;
	}
	saveFile << INVENTORY_DIVIDER << endl;
	/// inventory Divider///
	for (int i = 0; i < _player->getInventorySize(); i++)
	{
		Item* item = _player->GetItem(i);
		if (item == nullptr) continue; // 안전장치
		saveFile << item->getTypeName() << endl; // 아이템 종류 구분
		saveFile << item->getName() << endl;
		saveFile << item->getPrice() << endl;
		saveFile << (item->isUsable() ? "1" : "0") << endl;
		saveFile << (item->isConsumable() ? "1" : "0") << endl;
		saveFile << item->getDescription() << endl;

		/// 신규 아이템 종류 추가시 이곳에 저장될 수 있도록 추가해야 함
		if (item->getTypeName() == ITEM_HPPOTION) {
			HealthPotion* HPpotion = static_cast<HealthPotion*>(item);
			saveFile << HPpotion->getAmount() << std::endl;
		}
		else if (item->getTypeName() == ITEM_ATKBOOST) {
			AttackBoost* ATKpotion = static_cast<AttackBoost*>(item);
			saveFile << ATKpotion->getAmount() << std::endl;
		}
		else if (item->getTypeName() == ITEM_WEAPON) {
			Weapon* weapon = static_cast<Weapon*>(item);
			saveFile << weapon->getDamage() << std::endl;
		}
	}


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
		vector<string> Playerdata;
		vector<string> PlayerWeapon;
		vector<string> PlayerInventory;
		std::string line;
		bool weaponTrigger = false;
		bool InventoryTrigger = false;
		bool equipmentTrigger = false;
		
		while (std::getline(loadFile, line)) { // 파일의 내용을 한 줄씩 읽습니다.
			cout << line << endl;
			if (line == WEAPON_DIVIDER)
			{
				weaponTrigger = true;
				equipmentTrigger = true;
				continue;
			}

			if(line == INVENTORY_DIVIDER)
			{
				weaponTrigger = false;
				InventoryTrigger = true;
				continue;
			}

			/// 실제 읽음 부분
			Playerdata.push_back(line);
			if (weaponTrigger)
				PlayerWeapon.push_back(line);
			if(InventoryTrigger)
				PlayerInventory.push_back(line);
		}
		loadFile.close();
		_player->setName(Playerdata[0]);
		_player->setHealth(stoi(Playerdata[1]));
		_player->setMaxHealth(stoi(Playerdata[2]));
		_player->setBaseAttack(stoi(Playerdata[3]));
		_player->setAttack(stoi(Playerdata[4]));
		_player->setLevel(stoi(Playerdata[5]));
		_player->setExperience(stoi(Playerdata[6]));
		_player->setGold(stoi(Playerdata[7]));
		// 끼고 있던 무기 장착
		if (equipmentTrigger)
		{
			Weapon* weapon = new Weapon(
				PlayerWeapon[0],
				stoi(PlayerWeapon[1]),
				stoi(PlayerWeapon[2]),
				(PlayerWeapon[3] == "1"),
				(PlayerWeapon[4] == "1"),
				PlayerWeapon[5]
			);
			_player->setEquippedWeapon(weapon);
		}
		cout << "========PlayerData========" << endl;
		for(int i = 0; i < Playerdata.size(); i++)
		{
			cout << Playerdata[i] << endl;
		}

		cout << "========WeaponData========" << endl;
		for(int i = 0 ; i < PlayerWeapon.size(); i++)
		{
			cout << PlayerWeapon[i] << endl;
		}
		cout << "========Inventory========" << endl;
		for(int i = 0; i < PlayerInventory.size(); i++)
		{
			cout << PlayerInventory[i] << endl;
		}
	}
	return true;
}


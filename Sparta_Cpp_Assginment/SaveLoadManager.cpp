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
		// std::cerr << "Error: Player is null, cannot save game." << std::endl;
		return false;
	}
	std::ofstream saveFile(SAVE_FILENAME);
	if (!saveFile.is_open())
	{
		// std::cerr << "Error: Could not open save file." << std::endl;
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
	/// equimentWeapon Divider///
	saveFile << WEAPON_DIVIDER << endl;
	saveFile << _player->getEquippedWeapon()->getName() << endl;
	saveFile << _player->getEquippedWeapon()->getPrice() << endl;
	saveFile << _player->getEquippedWeapon()->getDamage() << endl;
	saveFile << (_player->getEquippedWeapon()->isUsable() ? "1" : "0") << endl;
	saveFile << (_player->getEquippedWeapon()->isConsumable() ? "1" : "0") << endl;
	saveFile << _player->getEquippedWeapon()->getDescription() << endl;
	saveFile << INVENTORY_DIVIDER << endl;
	/// inventory Divider///
	for (int i = 0; i < _player->getInventorySize(); i++)
	{
		Item* item = _player->GetItem(i);
		if (item == nullptr) continue; // ������ġ
		saveFile << item->getTypeName() << endl; // ������ ���� ����
		saveFile << item->getName() << endl;
		saveFile << item->getPrice() << endl;
		saveFile << (item->isUsable() ? "1" : "0") << endl;
		saveFile << (item->isConsumable() ? "1" : "0") << endl;
		saveFile << item->getDescription() << endl;

		/// �ű� ������ ���� �߰��� �̰��� ����� �� �ֵ��� �߰��ؾ� ��
		if (item->getTypeName() == ITEM_HPPOTION) {
			HealthPotion* potion = static_cast<HealthPotion*>(item);
			saveFile << potion->getAmount() << std::endl;
		}
		else if (item->getTypeName() == ITEM_ATKBOOST) {
			AttackBoost* potion = static_cast<AttackBoost*>(item);
			saveFile << potion->getAmount() << std::endl;
		}
		else if (item->getTypeName() == ITEM_WEAPON) {
			Weapon* potion = static_cast<Weapon*>(item);
			saveFile << potion->getDamage() << std::endl;
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
	// std::cout << "Game saved successfully." << std::endl;


	return true;
}

bool SaveLoadManager::LoadGame(Character* _player)
{
	std::ifstream loadFile(SAVE_FILENAME);
	if (!loadFile.is_open())
			{
		LOG("LOAD FAIL Could not open load file.");
		return false;
	}
	else
	{
		LOG("Load Start");
		vector<string> Playerdata;
		vector<string> PlayerWeapon;
		vector<string> PlayerInventory;
		std::string line;
		bool weaponTrigger = false;
		bool InventoryTrigger = false;
		
		while (std::getline(loadFile, line)) { // ������ ������ �� �پ� �н��ϴ�.
			cout << line << endl;
			if (line == WEAPON_DIVIDER)
			{
				weaponTrigger = true;
				continue;
			}

			if(line == INVENTORY_DIVIDER)
			{
				weaponTrigger = false;
				InventoryTrigger = true;
				continue;
			}

			/// ���� ���� �κ�
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

		// ���� �ִ� ���� ����
		Weapon *weapon = new Weapon(
			PlayerWeapon[0],
			stoi(PlayerWeapon[1]),
			stoi(PlayerWeapon[2]),
			(PlayerWeapon[3] == "1"),
			(PlayerWeapon[4] == "1"),
			PlayerWeapon[5]
		);
		_player->setEquippedWeapon(weapon);

		for(int i = 0; i < Playerdata.size(); i++)
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

		if (inventoryLoadTrigger)
		{
			/// ������ ����̴��� ���ö� ���� �������� �����
			std::vector<std::vector<std::string>> nowLoadedItem;
			std::vector<std::string> tempVec;

			for (const std::string& item : PlayerInventory) {
				if (item == ITEM_DIVIDER) {
					nowLoadedItem.push_back(tempVec);
					tempVec.clear();
					continue;
				}
				tempVec.push_back(item);
			}

			if (!tempVec.empty()) {
				nowLoadedItem.push_back(tempVec);
			}

			// ������ ����̴��� ������ �������� ������ �����ؼ� add ��Ű��
			for(int i = 0; i < nowLoadedItem.size(); i++)
			{
				if(nowLoadedItem[i][0] == ITEM_HPPOTION)
				{
					HealthPotion* HPpotion = new HealthPotion(
						nowLoadedItem[i][1],
						stoi(nowLoadedItem[i][2]),
						stoi(nowLoadedItem[i][6]),
						(nowLoadedItem[i][3] == "1"),
						(nowLoadedItem[i][4] == "1"),
						nowLoadedItem[i][5]
					);
					_player->addItem(HPpotion);
				}
				else if(nowLoadedItem[i][0] == ITEM_ATKBOOST)
				{
					AttackBoost* ATKpotion = new AttackBoost(
						nowLoadedItem[i][1],
						stoi(nowLoadedItem[i][2]),
						stoi(nowLoadedItem[i][6]),
						(nowLoadedItem[i][3] == "1"),
						(nowLoadedItem[i][4] == "1"),
						nowLoadedItem[i][5]
					);
					_player->addItem(ATKpotion);
				}
				else if(nowLoadedItem[i][0] == ITEM_WEAPON)
				{
					Weapon* weapon = new Weapon(
						nowLoadedItem[i][1],
						stoi(nowLoadedItem[i][2]),
						stoi(nowLoadedItem[i][6]),
						(nowLoadedItem[i][3] == "1"),
						(nowLoadedItem[i][4] == "1"),
						nowLoadedItem[i][5]
					);
					_player->addItem(weapon);
				}
			}
		}
	}
	return true;
}


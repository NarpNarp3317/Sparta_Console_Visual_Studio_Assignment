#include "Character.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Monster.h"
#include "Logger.h"
#include "StringUpdater.h"

//�� ������ �ӽ÷� ���
Character::Character()
{
	name = "test";
	maxHealth = 100;
	baseAttack = 50;
	attack = baseAttack;
	level = 1;
	experience = 0;
	gold = 0;
	health = maxHealth;
	equippedWeapon = nullptr;
	//inventory.push_back(new Item("Junk", 0, true, false, "is Junk"));	// ���������� �⺻ �������� �߰��߽��ϴ� [������]
}

Character::Character(string name)
{
	this->name = name;
	maxHealth = 100;
	baseAttack = 50;
	attack = baseAttack;
	level = 1;
	experience = 0;
	gold = 10000;
	health = maxHealth;
	equippedWeapon = nullptr;

	// ���� �� �κ��丮�� ������ �߰�
	setInventory();


	//addItem(new HealthPotion("HealthPotion", 0, true, false, "is Junk")); // �ӽ� �߰�
}

//void Character::useItem(int index)
//{
//	Item* item = inventory[index];
//	string itemname = item->getName();
//	item->use(this);
//	removeItemIdx(index);
//
//	if (item->isConsumable())
//	{
//		//if(itemCountMap[itemname] > 0)
//			itemCountMap[item->getName()]--;
//		//else
//
//		// ������ ���� ������� ����
//		/*int count = itemCountMap[item->getName()];
//		if (count <= 0)
//		{
//			RemoveItemCountMap(item->getName());
//			removeItemIdx(index);
//		}*/
//	}
//}

void Character::useItem(int key_num)		// �κ��丮�� ��Ÿ�Ͽ��� �������� ����ϴ� ���� ������ 09.09
{
	auto item_map = itemCountMap.begin();
	advance(item_map, key_num);	// index �̵�
	string itemname = inventory[key_num]->getName();

	if (itemCountMap[itemname] > 0)
	{
		//for (int index = 0; index < inventory.size(); index++)
		//	if (inventory[index]->getName() == itemname) 
		//	{
		//		cout << inventory[index]->getName() << endl;
		//		inventory[index]->use(this);
		//		if (inventory[index]->isConsumable()) 
		//		{
		//			itemCountMap[itemname] -= 1;
		//			//removeItemIdx(index);
		//		}
		//		return;
		//	}
		 
		 //ui �������� cout ����
		 //cout << "Error. Item not found." << endl;

		inventory[key_num]->use(this);
		itemCountMap[itemname]--;
	}
	else
	{
		LOG("NO ITEM ERROR");
		// UI���� �޽��� ��� �� �ֵ��� ������ ����
	}
		// cout << "No items left." << endl;
}

void Character::addItem(Item* item)	// �������� �κ��丮�� �߰��ϴ� �Լ�
{
	if (itemCountMap[item->getName()] > 8) {
		std::cout << "You have exceeded the maximum number of items.\n";
		return;
	}
	// ���ο� ������ ���
	if (itemCountMap.find(item->getName()) != itemCountMap.end())
	{
		int itemCount = itemCountMap[item->getName()];
		
		if (itemCount + 1 > 10)
		{
			return;
		}

		itemCountMap[item->getName()]++; // �ִٸ� ������ ���� �߰�
		inventory.push_back(item);
	}
	else // �� ��� �߻��ϸ� ���??
	{
		itemCountMap.insert(make_pair(item->getName(), 1));
		inventory.push_back(item);
	}
}

//bool Character::removeItem(string name)	// ������ ���� �Լ�
//{
//	for (int i = 0; i < inventory.size(); i++)
//		if (inventory[i]->getName() == name)
//		{
//			delete inventory[i]; // �޸� ����
//			inventory[i] = nullptr;
//			inventory.erase(inventory.begin() + i);
//			RemoveItemCountMap(name);
//			return true;
//		}
//	return false;
//}

bool Character::removeItemIdx(int index)	// �������� �ε����� �����ϴ� �Լ�
{
	if (checkingInventory(index)) 
	{
		//RemoveItemCountMap(inventory[index]->getName());
		delete inventory[index]; // �޸� ����
		inventory[index] = nullptr;
		inventory.erase(inventory.begin() + index);
		return true;
	}
	return false;
}

void Character::levelUp()
{
	level++;
	maxHealth += (level * 20);
	baseAttack += (level * 5);
	refreshATK();
	health = maxHealth;
	experience = 0;
}

void Character::getStatus()
{
	StringUpdater string_update({ 20, 30 });
	string status = "Name : " + name + "\n";
	status += "HP : " + to_string(health) + "\n";
	status += "Level : " + to_string(level) + "\n";
	status += "ATK : " + to_string(attack);
	if (equippedWeapon != nullptr)
	{
		status += "(" + to_string(equippedWeapon->getDamage()) + ")";
	}
	status += "\n";

	status += "EXP : " + to_string(experience) + "\n";
	status += "GOLD : " + to_string(gold);

	string_update.StringUpdate(status);


	/*vector<string> statVec;
	statVec.push_back("Name : " + name);
	statVec.push_back("HP : " + to_string(health));
	statVec.push_back("Level : " + to_string(level));
	statVec.push_back("ATK : " + to_string(attack));
	if (equippedWeapon != nullptr)
	{
		statVec.push_back("(" + to_string(equippedWeapon->getDamage()) + ")");
	}
	statVec.push_back("EXP : " + to_string(experience));
	statVec.push_back("GOLD : " + to_string(gold));*/

	///return statVec;
}

void Character::reward(int exp, int gainGold)
{
	experience += exp;
	gold += gainGold;

	if (experience >= MAX_EXPERIENCE)
	{
		int remainExp = experience - MAX_EXPERIENCE;
		levelUp();
		experience += remainExp;
	}
}

void Character::takeDamage(int damage)
{
 	health -= damage;
	if (health <= 0)
	{
		health = 0;
	}
}

void Character::printInventory()
{
	/// 25.09.07. mpyi
	/// �κ��丮�� �ƹ��͵� ���� �� �޽��� �߰�
	if (inventory.size() <= 0)
	{
		cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << endl;
		cout << "Your inventory is empty!" << endl;
		cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << endl;
	}
	else
	{
		// ������ ���� �ڵ� �߰�
		cout << "===========INVENTORY===========" << endl;
		//for (int i = 0; i < inventory.size(); i++)
		//{
		//	cout << i + 1 << ". " << inventory[i]->getName() << "/Count : " << itemCountMap[inventory[i]->getName()] << endl;
		//}
		int i = 1;
		for (auto item : itemCountMap) {
			cout << i << ". " << item.first << "/Count : " << item.second << endl;
			i++;
		}
	}
}

bool Character::checkingInventory(int index)
{
	if (index < 0 || index >= inventory.size())
	{
		return false;
	}
	return true;
}

bool Character::checkingInventorymap(int key_num)		// 09.09 ���� �߰���
{
	//auto item_map = itemCountMap.begin();
	//advance(item_map, key_num);	// index �̵�
	//string itemname = item_map->first;

	//for (auto item : itemCountMap) 
	//{
	//	if (item.first == itemname)
	//	{
	//		return item.second > 0 ? true : false;
	//	}
	//}

	if (itemCountMap[inventory[key_num]->getName()] > 0)
	{
		return true;
	}

	return false;
}

// 09.08 ������� �����߰��� �Լ� ---------
void Character::refreshATK()
{
	if (equippedWeapon == nullptr) {	// ������ ���Ⱑ ����
		attack = baseAttack;
		return;
	}
	attack = baseAttack + equippedWeapon->getDamage();
}

Weapon* Character::getEquippedWeapon()
{
	return this->equippedWeapon;
}

void Character::refreshInventory()
{
	for (int i = 0; i < inventory.size(); i++) {
		string itemname = inventory[i]->getName();
		if (itemCountMap.find(itemname) == itemCountMap.end())	// item not found
			itemCountMap[itemname] = 0;
		itemCountMap[itemname] += 1;
	}
}

void Character::setEquippedWeapon(Weapon* weapon)
{
	if (equippedWeapon != nullptr) {
		delete equippedWeapon;
		equippedWeapon = nullptr;
	}
	equippedWeapon = weapon;
}

int Character::getBaseAttack() const
{
	return this->baseAttack;
}

void Character::setBaseAttack(int atk)
{
	this->baseAttack = atk;
	this->refreshATK();
}

// ---------------------

int Character::getHealth() const
{
	return health;
}

int Character::getAttack() const
{
	return attack;
}

size_t Character::getInventorySize() const
{
	return inventory.size();
}

string Character::getName() const
{
	return name;
}

int Character::getLevel() const
{
	return level;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

int Character::getItemCount(int index)
{
	Logger::getInstance().myLog(to_string(itemCountMap[inventory[index]->getName()]));
	return itemCountMap[inventory[index]->getName()];
}

void Character::setName(string _name)
{
	this->name = _name;
}

void Character::setHealth(int _health)
{
	this->health += health;

	if (this->health > maxHealth)
	{
		this->health = maxHealth;
	}
}

void Character::setMaxHealth(int _maxHealth)
{
	this->maxHealth = _maxHealth;
}

void Character::setAttack(int _attack)
{
	this->attack = _attack;
}

void Character::setLevel(int _level)
{
	this->level = _level;
}

void Character::setExperience(int _exp)
{
	this->experience = _exp;
}

void Character::setGold(int _gold)
{
	this->gold = _gold;
}

void Character::setInventory(const vector<Item*>& items)
{
	// ���� �κ��丮 �޸� ����
	for (int i = 0; i < inventory.size(); i++)
	{
		delete inventory[i];
		inventory[i] = nullptr;
	}
	inventory.clear();
	// ���ο� ������ �߰�
	for (const auto& item : items)
	{
		inventory.push_back(item);
	}
}

void Character::setInventoryMap(const map<string, int>& itemCountMap)
{
	this->itemCountMap = itemCountMap;
}

// For Shop (���� ������ �Լ�)
bool Character::SpendGold(int amount)
{
	if (gold >= amount) {
		gold -= amount;
		return true;
	}
	return false;
}

void Character::AddGold(int amount)
{
	gold += amount;
}

Item* Character::GetItem(int index)
{
	if (index >= 0 && index < inventory.size()) {
		return inventory[index];
	}
	return nullptr;
}

bool Character::RemoveItem(int index)
{
	if (index >= 0 && index < inventory.size()) {
		inventory.erase(inventory.begin() + index);
		return true;
	}
	return false;
}

void Character::RemoveItemCountMap(const string& name)
{
	itemCountMap.erase(name);
}

void Character::setInventory()
{
	inventory.push_back(new HealthPotion(ITEM_HPPOTION, 15, 15, true, true));
	inventory.push_back(new AttackBoost(ITEM_ATKBOOST, 15, 15, true, true));

	itemCountMap.insert(make_pair(inventory[0]->getName(), 2));
	itemCountMap.insert(make_pair(inventory[1]->getName(), 1));
	//refreshInventory();
}

Character::~Character()
{
	delete equippedWeapon;
	for (int i = 0; i < inventory.size(); i++)
	{
		delete inventory[i];
		inventory[i] = nullptr;
	}
}


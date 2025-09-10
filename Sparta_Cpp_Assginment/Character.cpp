#include "Character.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Monster.h"

//이 생성자 임시로 사용
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
	inventory.push_back(new Item("Junk", 0, true, false, "is Junk"));	// 실험적으로 기본 아이템을 추가했습니다 [조기혁]
}

Character::Character(string name)
{
	this->name = name;
	maxHealth = 100;
	baseAttack = 50;
	attack = baseAttack;
	level = 1;
	experience = 0;
	gold = 0;
	health = maxHealth;
	equippedWeapon = nullptr;

	// 생성 시 인벤토리에 아이템 추가
	setInventory();


	//addItem(new HealthPotion("HealthPotion", 0, true, false, "is Junk")); // 임시 추가
}

void Character::useItem(int index)
{
	Item* item = inventory[index];
	item->use(this);

	if (item->isConsumable()) 
	{
		itemCountMap[item->getName()]--;
		// 아이템 이제 사라지지 않음
		/*int count = itemCountMap[item->getName()];
		if (count <= 0)
		{
			RemoveItemCountMap(item->getName());
			removeItemIdx(index);
		}*/
	}
}


void Character::addItem(Item* item)	// 아이템을 인벤토리에 추가하는 함수
{
	
	// 새로운 아이템 등록
	if (itemCountMap.find(item->getName()) != itemCountMap.end())
	{
		int itemCount = itemCountMap[item->getName()];
		
		if (itemCount + 1 > 10)
		{
			return;
		}

		itemCountMap[item->getName()]++; // 있다면 아이템 수량 추가
	}
	else // 이 경우 발생하면 사고??
	{
		itemCountMap.insert(make_pair(item->getName(), 1));
		inventory.push_back(item);
	}
}

bool Character::removeItem(string name)	// 아이템 삭제 함수
{
	for (int i = 0; i < inventory.size(); i++)
		if (inventory[i]->getName() == name)
		{
			delete inventory[i]; // 메모리 해제
			inventory[i] = nullptr;
			inventory.erase(inventory.begin() + i);
			RemoveItemCountMap(name);
			return true;
		}
	return false;
}

bool Character::removeItemIdx(int index)	// 아이템을 인덱스로 삭제하는 함수
{
	if (checkingInventory(index)) 
	{
		RemoveItemCountMap(inventory[index]->getName());
		delete inventory[index]; // 메모리 해제
		inventory[index] = nullptr;
		inventory.erase(inventory.begin() + index);
		return true;
	}
	return false;
}

void Character::levelUp()
{
	cout << "===========MESSAGE===========" << endl;
	cout << "LEVEL UP!! " << level << " >> " << level + 1 << endl;

	level++;
	maxHealth += (level * 20);
	baseAttack += (level * 5);
	refreshATK();
	health = maxHealth;
	experience = 0;
}

void Character::displayStatus()
{
	cout << "===========STATUS===========" << endl;
	cout << "Name : " << name << endl;
	cout << "HP : " << health << endl;
	cout << "level : " << level << endl;
	cout << "ATK : " << baseAttack;
	if (equippedWeapon != nullptr) cout << " (+" << equippedWeapon->getDamage() << ")";		// format "ATK: basedamage (+Weapondamage)"
	cout << "" << endl;
	cout << "EXP : " << experience << endl;
	cout << "GOLD : " << gold << endl;
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
	/// 인벤토리에 아무것도 없을 시 메시지 추가
	if (inventory.size() <= 0)
	{
		cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << endl;
		cout << "Your inventory is empty!" << endl;
		cout << "=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << endl;
	}
	else
	{
		// 아이템 수량 코드 추가
		cout << "===========INVENTORY===========" << endl;
		for (int i = 0; i < inventory.size(); i++)
		{

			cout << i + 1 << ". " << inventory[i]->getName() << "/Count : " << itemCountMap[inventory[i]->getName()] << endl;
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

// 09.08 무기관련 새로추가된 함수 ---------
void Character::refreshATK()
{
	if (equippedWeapon == nullptr) {	// 장착한 무기가 없음
		attack = baseAttack;
		return;
	}
	attack = baseAttack + equippedWeapon->getDamage();
}

Weapon* Character::getEquippedWeapon()
{
	return this->equippedWeapon;
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
	// 기존 인벤토리 메모리 해제
	for (int i = 0; i < inventory.size(); i++)
	{
		delete inventory[i];
		inventory[i] = nullptr;
	}
	inventory.clear();
	// 새로운 아이템 추가
	for (const auto& item : items)
	{
		inventory.push_back(item);
	}
}

void Character::setInventoryMap(const map<string, int>& itemCountMap)
{
	this->itemCountMap = itemCountMap;
}

// For Shop (상점 연동용 함수)
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

	itemCountMap.insert(make_pair(inventory[0]->getName(), 0));
	itemCountMap.insert(make_pair(inventory[1]->getName(), 0));
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


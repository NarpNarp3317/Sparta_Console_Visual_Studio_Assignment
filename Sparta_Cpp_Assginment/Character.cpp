#include "Character.h"
#include "Item.h"

//이 생성자 임시로 사용
Character::Character()
{
	name = "test";
	maxHealth = 100;
	attack = 50;
	level = 1;
	experience = 0;
	gold = 0;
	health = maxHealth;
	inventory.push_back(new Item("Junk", 0, true, false, "is Junk"));	// 실험적으로 기본 아이템을 추가했습니다 [조기혁]
}

Character::Character(string name)
{
	this->name = name;
	maxHealth = 100;
	attack = 1;
	level = 1;
	experience = 0;
	gold = 0;
	health = maxHealth;
}

void Character::useItem(int index)
{
	Item* item = inventory[index];

	item->use(this);
	if (item->isConsumable()) {
		removeItemIdx(index);
		delete item;
		item = nullptr;
	}
}

void Character::addItem(Item* item)	// 아이템을 인벤토리에 추가하는 함수
{
	inventory.push_back(item);
}

bool Character::removeItem(string name)	// 아이템 삭제 함수
{
	for (int i = 0; i < inventory.size(); i++)
		if (inventory[i]->getName() == name) {
			inventory.erase(inventory.begin() + i);
			return true;
		}
	return false;
}

bool Character::removeItemIdx(int index)	// 아이템을 인덱스로 삭제하는 함수
{
	if (checkingInventory(index)) {
		inventory.erase(inventory.begin() + index);
		return true;
	}
	return false;
}

void Character::levelUp()
{
	level++;
	maxHealth += (level * 20);
	attack += (level * 5);
	health = maxHealth;
	experience = 0;
}

void Character::displayStatus()
{
	cout << "===========STATUS===========" << endl;
	cout << "Name : " << name << endl;
	cout << "HP : " << health << endl;
	cout << "level : " << level << endl;
	cout << "ATK : " << attack << endl;
	cout << "EXP : " << experience << endl;
	cout << "GOLD : " << gold << endl;
}

void Character::reward(int exp, int gainGold)
{
	experience += exp;
	gold += gainGold;

	if (experience >= MAX_EXPERIENCE)
	{
		levelUp();
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

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << " . " << inventory[i]->getName();
	}
}

bool Character::checkingInventory(int index)
{
	if (index <= 0 || index >= inventory.size())
	{
		return false;
	}
	return true;
}

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

void Character::setHealth(int _health)
{
	this->health += health;

	if (this->health > maxHealth)
	{
		this->health = maxHealth;
	}
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


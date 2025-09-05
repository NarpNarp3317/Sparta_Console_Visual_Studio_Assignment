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
}

Character::Character(string name)
{
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

	//TODO : UseItem

	inventory.erase(inventory.begin() + index);
	delete item;
	item = nullptr;
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

int Character::getInventorySize() const
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



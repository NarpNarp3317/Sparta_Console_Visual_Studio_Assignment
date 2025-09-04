#include "Character.h"
#include "Item.h"

//이 생성자 임시로 사용
Character::Character()
{
	name = "test";
	maxHealth = 100;
	attack = 1;
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

int Character::getHealth()
{
	return health;
}

int Character::getAttack()
{
	return attack;
}

string Character::getName()
{
	return name;
}



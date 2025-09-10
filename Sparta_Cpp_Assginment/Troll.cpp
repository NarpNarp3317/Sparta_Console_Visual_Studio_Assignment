#include "Troll.h"
#include "StringUpdater.h"

Troll::Troll()
{
	this->name = "Troll";
	this->maxHealth = 100;
	this->attack = 10;
	health = maxHealth;
}

Troll::Troll(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "Troll";
	this->maxHealth = maxHealth;
	this->attack = attack;
	health = maxHealth;

	rw_exp = randomValue(15, 30);
	rw_gold = randomValue(10, 15);
}

Troll::~Troll()
{
}

void Troll::displayStatus()
{
	stringUpdater->CleanStrings();
	string status = "Name : " + name + " ";
	status += "ATK : " + to_string(attack);
	stringUpdater->StringUpdate(status);
}

#include "Orc.h"
#include "StringUpdater.h"

Orc::Orc()
{
	this->name = "Orc";
	this->maxHealth = 100;
	this->attack = 10;
	health = maxHealth;
}
Orc::Orc(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "Orc";
	this->maxHealth = maxHealth;
	this->attack = attack;
	health = maxHealth;

	rw_exp = randomValue(15, 30);
	rw_gold = randomValue(10, 15);
}


Orc::~Orc()
{

}

void Orc::displayStatus()
{
	stringUpdater->CleanStrings();
	string status = "Name : " + name + " ";
	status += "ATK : " + to_string(attack);
	stringUpdater->StringUpdate(status);
}

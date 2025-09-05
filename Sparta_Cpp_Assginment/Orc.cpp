#include "Orc.h"
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
}


Orc::~Orc()
{

}
#include "Troll.h"

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
}

Troll::~Troll()
{
}
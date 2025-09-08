#include "BossMonster.h"
BossMonster::BossMonster(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "BossMonster";
	this->maxHealth = maxHealth;
	this->attack = attack;
	health = maxHealth;

	rw_exp = randomValue(100, 150);
	rw_gold = randomValue(30, 50);

}


BossMonster::~BossMonster()
{

}
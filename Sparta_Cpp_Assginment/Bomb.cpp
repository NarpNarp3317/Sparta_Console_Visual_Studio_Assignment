#include "Bomb.h"

void Bomb::use(Character* character, Monster* monster) {
	int damage = this->getDamage();
	// monster.hp -= damage;
}

int Bomb::getDamage()
{
	return this->damage;
}

void Bomb::setDamage(int damage)
{
	this->damage = damage;
}

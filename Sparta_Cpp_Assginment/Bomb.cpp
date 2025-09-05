#include "Bomb.h"

// This class is unlikely to be used.

void Bomb::use(Character* character, Monster* monster) {
	Item::use(character);
	int damage = this->getDamage();
	// monster.hp -= damage;
}

int Bomb::getDamage() { return this->damage; }
void Bomb::setDamage(int dmg) { this->damage = dmg; }

#include "Weapon.h"

void Weapon::use(Character* character)
{
	Weapon* curr_w = character->getEquippedWeapon();
	if(curr_w != nullptr)
		character->addItem(new Weapon(*curr_w));

	curr_w = nullptr;
	character->setEquippedWeapon(new Weapon(*this));
	character->refreshATK();
}

int Weapon::getDamage() { return this->damage; }
void Weapon::setDamage(int dmg) { this->damage = dmg; }

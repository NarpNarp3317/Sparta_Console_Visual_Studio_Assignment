#pragma once
#include "Item.h"

class Dagger : public Item
{
private:
	int damage;
public:
	Dagger(string name, int price, int damage, bool usable = false, bool consumable = true, string description = "None")
		: Item(name, price, usable, consumable, description), damage(damage) {
		if (damage < 1)
			this->damage = 1;
		if (description == "None")
			this->setDescription("Very fast weapon. Damage: "+ to_string(damage));
	}
	~Dagger();
	int getDamage();
	void setDamage(int dmg);
};
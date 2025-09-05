#pragma once
#include "Item.h"
#include "Character.h"
#include "Monster.h"

class Bomb : public Item
{
private:
	int damage;
public:
	Bomb(string name, int price, int damage, bool usable = true, bool consumable = true, string description = "None")
		: Item(name, price, usable, consumable, description), damage(damage) {
		if (damage < 1)
			this->damage = 1;
		if (description == "None")
			this->setDescription("An explosive that deals damage to enemies. Damage: " + to_string(damage));
	}
	~Bomb();
	int getDamage();
	void setDamage(int dmg);
	void use(Character* character, Monster* monster);
};


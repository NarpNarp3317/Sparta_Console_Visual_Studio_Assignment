#pragma once
#include "Item.h"
#include "Character.h"
#include "Monster.h"
class Bomb : public Item
{
private:
	int damage;
public:
	Bomb(string name, int price, int damage, bool consumable = true, string description = "None")
		: Item(name, price, consumable, description), damage(damage) {
		if (damage < 1)
			damage = 1;
		if (description == "None")
			this->setDescription("An explosive that deals damage to enemies. Damage: " + to_string(damage));
	}
	~Bomb();
	int getDamage();
	void setDamage(int damage);
	void use(Character* character, Monster* monster);
};


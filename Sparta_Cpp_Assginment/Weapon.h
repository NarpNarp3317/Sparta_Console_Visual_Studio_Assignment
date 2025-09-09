#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damage;
public:
	Weapon(string name, int price, int damage, bool usable = true, bool consumable = true, string description = "None")
		: Item(name, price, usable, consumable, description), damage(damage) {
		if (damage < 1)
			this->damage = 1;
		if (description == "None")
			this->setDescription("is Weapon.");
		this->typeName = ITEM_WEAPON;
	} // Weapon("iron sword", 30, 15, true, true, "A balanced weapon.")
	~Weapon() {};
	int getDamage();
	void setDamage(int dmg);
	void use(Character* character) override;
	virtual std::string getTypeName() const override {
		return this->typeName;
	}
};
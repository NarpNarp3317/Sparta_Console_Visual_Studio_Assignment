#pragma once
#include "Item.h"

class HealthPotion : public Item
{
private:
	int amount;
public:
	HealthPotion(string name, int price, int amount)
	: Item(name, price), amount(amount) {
			this->setDescription("Restores "+to_string(amount)+" HP.");
	}
	~HealthPotion();
	void use(Character* character) override;
};
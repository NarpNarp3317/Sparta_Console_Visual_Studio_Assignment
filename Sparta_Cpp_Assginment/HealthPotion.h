#pragma once
#include "Item.h"

class HealthPotion : public Item
{
private:
	int amount;
public:
	HealthPotion(string name, int price, int amount, bool consumable = true, string description = "None")
		: Item(name, price, consumable, description), amount(amount) {
		if (amount < 1)
			amount = 1;
		if(description == "None")
			this->setDescription("Restores "+to_string(amount)+" HP.");
	}
	~HealthPotion() {};
	void use(Character* character) override;
};
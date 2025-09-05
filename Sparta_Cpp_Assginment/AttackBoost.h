#pragma once
#include "Item.h"
#include "Character.h"

class AttackBoost : public Item
{
private:
	int amount;
public:
	AttackBoost(string name, int price, int amount, bool consumable = true, string description = "None")
		: Item(name, price, consumable, description), amount(amount) {
		if (amount < 1)
			amount = 1;
		if (description == "None")
			this->setDescription(to_string(amount)+" Attack Boost.");
	}
	~AttackBoost() {};
	void use(Character* character) override;
};


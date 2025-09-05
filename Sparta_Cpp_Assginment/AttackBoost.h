#pragma once
#include "Item.h"
#include "Character.h"

class AttackBoost : public Item
{
private:
	int amount;
public:
	AttackBoost(string name, int price, int amount, bool usable = true, bool consumable = true, string description = "None")
		: Item(name, price, usable, consumable, description), amount(amount) {
		if (amount < 1)
			this->amount = 1;
		if (description == "None")
			this->setDescription(to_string(amount)+" Attack Boost.");
	}
	~AttackBoost() {};
	int getAmount();
	void setAmount(int amt);
	void use(Character* character) override;
};
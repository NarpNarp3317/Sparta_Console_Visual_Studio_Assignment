#pragma once
#include "Item.h"

class HealthPotion : public Item
{
private:
	int amount;
public:
	HealthPotion(string name, int price, int amount, bool usable = true, bool consumable = true, string description = "None")
		: Item(name, price, usable, consumable, description), amount(amount) {
		if (amount < 1)
			this->amount = 1;
		if(description == "None")
			this->setDescription("Restores "+to_string(amount)+" HP.");
	}
	~HealthPotion() {};
	int getAmount();
	void setAmount(int amt);
	void use(Character* character) override;
};
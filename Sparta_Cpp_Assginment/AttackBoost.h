#pragma once
#include "Item.h"
#include "Character.h"

class AttackBoost : public Item
{
private:
	int amount;
public:
	AttackBoost(string name, int price, int amount)
	: Item(name, price), amount(amount) {
		this->setDescription(to_string(amount)+" Attack Boost.");
	}
	~AttackBoost() {};
	void use(Character* character) override;
};


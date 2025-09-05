#pragma once
#include "Item.h"
#include "Character.h"

class AttackBoost : public Item
{
	int amount;
public:
		AttackBoost(string name, int price, int healthRestore) : Item(name, price), amount(amount) {}
		~AttackBoost();
		void use(Character* chracter);
};


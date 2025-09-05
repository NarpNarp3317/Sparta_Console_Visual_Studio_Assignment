#pragma once
#include "Item.h"

class HealthPotion : public Item
{
	int amount;
public:
	HealthPotion(string name, int price, int healthRestore) : Item(name, price), amount(amount) {}
	~HealthPotion();
	void use(Character* chracter);
};
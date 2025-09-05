#pragma once
#include <string>
#include "Character.h"

class Character;

using namespace std;

class Item
{
private:
	string name;
	int price;
	bool consumable;
	string description;
public:
	Item(string name, int price, bool consumable = false, string description = "None")
		: name(name), price(price), consumable(consumable), description(description) {
		if (price < 0)
			price = 0;
	};
	~Item() {};
	string getName();
	int getPrice();
	bool isConsumable();
	string getDescription();
	void setDescription(string desc);
	virtual void use(Character* character);
};


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
	string description;
public:
	Item(string name, int price, string description = "None")
		: name(name), price(price) , description(description){};
	~Item() {};
	string getName();
	int getPrice();
	string getDescription();
	void setDescription(string desc);
	virtual void use(Character* character);
};


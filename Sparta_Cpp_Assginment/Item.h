#pragma once
#include <string>
#include "Character.h"

using namespace std;

class Item
{
private:
	string name;
	int price;
public:
	Item(string name, int price) : name(name), price(price) {};
	string getName();
	void use(Character* character);
	~Item();
};


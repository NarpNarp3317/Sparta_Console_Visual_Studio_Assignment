#include "Item.h"

string Item::getName() {
	return this->name;
}

int Item::getPrice()
{
	return this->price;
}

string Item::getDescription()
{
	return this->description;
}

void Item::setDescription(string desc)
{
	this->description = desc;
}
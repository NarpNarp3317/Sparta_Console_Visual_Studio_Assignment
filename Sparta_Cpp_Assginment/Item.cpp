#include "Item.h"

using namespace std;

void Item::use(Character* character)
{
	cout << character->getName() + " used " + this->getName() << endl;
}

//void Item::use(Character* character, Monster* monster)
//{
//	cout << character->getName() + " used " + this->getName() + " on " + monster->getName() << endl;
//}

string Item::getName() { return this->name; }
int Item::getPrice() { return this->price; }
bool Item::isConsumable() { return this->consumable; }
bool Item::isUsable() { return this->usable; }
string Item::getDescription() { return this->description; }
void Item::setDescription(string desc) { this->description = desc; }
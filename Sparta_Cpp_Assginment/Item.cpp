#include "Item.h"

void Item::use(Character* character)
{
	// 25.09.05. 이무표
	// 아무 기능 없어도 함수 생성해두지 않으면 컴파일되지 않아 추가함
}

string Item::getName() { return this->name; }
int Item::getPrice() { return this->price; }
bool Item::isConsumable() { return this->consumable; }
string Item::getDescription() { return this->description; }
void Item::setDescription(string desc) { this->description = desc; }
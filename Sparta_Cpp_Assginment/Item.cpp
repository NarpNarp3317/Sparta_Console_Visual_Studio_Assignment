#include "Item.h"

void Item::use(Character* character)
{
	// 25.09.05. �̹�ǥ
	// �ƹ� ��� ��� �Լ� �����ص��� ������ �����ϵ��� �ʾ� �߰���
}

string Item::getName() { return this->name; }
int Item::getPrice() { return this->price; }
bool Item::isConsumable() { return this->consumable; }
string Item::getDescription() { return this->description; }
void Item::setDescription(string desc) { this->description = desc; }
#include "HealthPotion.h"

using namespace std;

void HealthPotion::use(Character* character)
{
	Item::use(character);
	int updatedValue = character->getHealth() + this->amount;
	character->setHealth(updatedValue);
}

int HealthPotion::getAmount(){ return this->amount; }
void HealthPotion::setAmount(int amt) { this->amount = amt; }
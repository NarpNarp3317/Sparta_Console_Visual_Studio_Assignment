#include "AttackBoost.h"

using namespace std;

void AttackBoost::use(Character* character)
{
	Item::use(character);
	int updatedValue = character->getAttack() + this->amount;
	// character->setAttack(updatedValue);
}

int AttackBoost::getAmount() { return this->amount; }
void AttackBoost::setAmount(int amt) { this->amount = amt; }

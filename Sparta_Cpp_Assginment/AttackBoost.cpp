#include "AttackBoost.h"
#include "Logger.h"
using namespace std;

void AttackBoost::use(Character* character)
{
	Item::use(character);
	int updatedValue = character->getBaseAttack() + this->amount;
	character->setBaseAttack(updatedValue);

	LOG("ATK BOOST : " + to_string(character->getBaseAttack()));

	// cout Á¦°Å
	// cout << "Attack increased by " + to_string(this->amount) + "." << endl;
}

int AttackBoost::getAmount() { return this->amount; }
void AttackBoost::setAmount(int amt) { this->amount = amt; }

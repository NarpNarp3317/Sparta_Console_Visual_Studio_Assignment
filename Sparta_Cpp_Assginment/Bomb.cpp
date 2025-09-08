#include "Bomb.h"

// This class is unlikely to be used.

void Bomb::use(Character* character, Monster* monster) {
	Item::use(character);
	int damage = this->getDamage();
	//monster->takeDamage(damage);
	//임시 테스트 코드
	cout << "Player use Bomb!\nMonster TakeDamage : " << damage << endl;
}

int Bomb::getDamage() { return this->damage; }
void Bomb::setDamage(int dmg) { this->damage = dmg; }

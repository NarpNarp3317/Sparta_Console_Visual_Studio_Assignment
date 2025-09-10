#include "Goblin.h"
#include "StringUpdater.h"

//이 생성자 임시로 사용
Goblin::Goblin() : Monster()
{
	this->name = "Goblin";
	this->maxHealth = 100;
	this->attack = 10;
	health = maxHealth;
}

Goblin::Goblin(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "Goblin";
	//레벨에 따른 체력 공격력 받아와서 처리
	this->maxHealth = maxHealth;
	this->attack = attack;
	health = maxHealth;

	rw_exp = randomValue(15, 30);
	rw_gold = randomValue(10, 15);
}


Goblin::~Goblin()
{

}

void Goblin::displayStatus()
{
	stringUpdater->CleanStrings();
	string status = "Name : " + name + " ";
	status += "ATK : " + to_string(attack);
	stringUpdater->StringUpdate(status);
}

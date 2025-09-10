#include "Goblin.h"
#include "StringUpdater.h"

//�� ������ �ӽ÷� ���
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
	//������ ���� ü�� ���ݷ� �޾ƿͼ� ó��
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

#include "Goblin.h"

//�� ������ �ӽ÷� ���
Goblin::Goblin() : Monster()
{
	this->maxHealth = 100;
	this->attack = 10;
	health = maxHealth;
}

Goblin::Goblin(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "Goblin";
	//������ ���� ü�� ���ݷ� �޾ƿͼ� ó��
}


Goblin::~Goblin()
{
}
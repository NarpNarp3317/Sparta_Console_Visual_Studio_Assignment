#pragma once
#include "Character.h"

class Monster
{
public:
	Monster();
	Monster(int maxHealth, int attack);
	virtual void takeDamage(int damage);
	virtual ~Monster();


	//Getter
	virtual string getName();
	virtual int getHealth();
	virtual int getAttack();

protected:
	string name;
	int health;
	int maxHealth;
	int attack;
};


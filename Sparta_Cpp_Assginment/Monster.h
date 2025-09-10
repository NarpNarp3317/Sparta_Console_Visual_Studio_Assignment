#pragma once
#include "Character.h"

class StringUpdater;

class Monster
{
public:
	Monster();
	Monster(int maxHealth, int attack);
	virtual void takeDamage(int damage);
	virtual ~Monster();

	virtual int randomItem();
	virtual int randomValue(const int& minValue, const int& maxValue);
	virtual void displayStatus();

	//Getter
	virtual string getName();
	virtual int getHealth();
	virtual int getAttack();
	virtual int getRewardExp();
	virtual int getRewardGold();

protected:
	string name;
	int health;
	int maxHealth;
	int attack;
	int rw_exp;
	int rw_gold;
	StringUpdater* stringUpdater;
};


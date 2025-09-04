//Player, Monster 부모 클래스
#pragma once
#include <iostream>
#include <vector>


using namespace std;

class Character
{
public:
	////Character();
	Character(string name);

public:
	void useItem(int index);
	void levelUp();
	void displayStatus();
	void reward(int exp, int gainGold);
	void takeDamage(int damage);

	//Getter
	int getHealth();
	int getAttack();
	string getName();

protected: 
	const int MAX_EXPERIENCE = 100;
	string name;
	int health;
	int maxHealth;
	int attack;
	int level;
	int experience;
	int gold;
	vector <class Item*> inventory;
};


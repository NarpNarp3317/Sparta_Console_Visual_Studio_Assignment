#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Item;

class Character
{
public:
	Character();
	Character(string name);

public:
	void useItem(int index);
	void levelUp();
	void displayStatus();
	void reward(int exp, int gainGold);
	void takeDamage(int damage);
	void PrintInventory();
	bool checkingInventory(int index);

	//Getter
	int getHealth();
	int getAttack();
	int getLevel(); // 09.05. �̹�ǥ_�ٷ����� ��� �߰�
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
	vector <Item*> inventory;
};


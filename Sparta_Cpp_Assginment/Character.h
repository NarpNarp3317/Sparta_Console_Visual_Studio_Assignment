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
	void addItem(Item* item);
	bool removeItem(string name);
	bool removeItemIdx(int index);
	void levelUp();
	void displayStatus();
	void reward(int exp, int gainGold);
	void takeDamage(int damage);
	void printInventory();
	bool checkingInventory(int index);

	//Getter
	int getHealth() const;
	int getAttack() const;
	int getInventorySize() const;
	string getName() const;
	int getLevel() const;

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


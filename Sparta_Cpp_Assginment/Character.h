#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;
class Item;
class Monster;


class Character
{
public:
	Character();
	Character(string name);
	~Character();
public:
	void useItem(int index, Monster* monster);
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
	size_t getInventorySize() const;
	string getName() const;
	int getLevel() const;
	int getMaxHealth() const;
	int getGold() const { return gold; }

	//Setter
	void setHealth(int _health);
	// 라운지에서 회복 기능을 추가하기 위해 getMaxHealth() 및
	// set Health 추가하였습니다
	// 25.09.05. 이무표

	// For Shop (상점 연동용 함수)
	bool SpendGold(int amount);      // 골드 차감
	void AddGold(int amount);        // 골드 추가
	Item* GetItem(int index);        // 인벤토리에서 아이템 가져오기
	bool RemoveItem(int index);      // 인벤토리에서 아이템 제거

private:
	void RemoveItemCountMap(const string& name);

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
	map<string, int> itemCountMap; //아이템 수량을 위해 추가
};


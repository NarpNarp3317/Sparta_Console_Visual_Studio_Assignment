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
	// ��������� ȸ�� ����� �߰��ϱ� ���� getMaxHealth() ��
	// set Health �߰��Ͽ����ϴ�
	// 25.09.05. �̹�ǥ

	// For Shop (���� ������ �Լ�)
	bool SpendGold(int amount);      // ��� ����
	void AddGold(int amount);        // ��� �߰�
	Item* GetItem(int index);        // �κ��丮���� ������ ��������
	bool RemoveItem(int index);      // �κ��丮���� ������ ����

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
	map<string, int> itemCountMap; //������ ������ ���� �߰�
};


#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;
class Item;
class Monster;
class Weapon;

class Character
{
public:
	Character();
	Character(string name);
	~Character();
public:
	void useItem(int index);
	void addItem(Item* item);
	// ��� x
	//bool removeItem(string name);
	//bool removeItemIdx(int index);
	//
	void levelUp();
	void displayStatus();
	void reward(int exp, int gainGold);
	void takeDamage(int damage);
	void printInventory();
	bool checkingInventory(int index);
	bool checkingInventorymap(int key_num);	// 09.09 battle.cpp���� useitem�� �ǵ��ѹٿ� �۵��ϵ��� ���� �Լ��� ������

	void refreshATK();						// ���� �߰��� �Լ� 09.08 -----
	Weapon* getEquippedWeapon(); // save/load Ȱ���� ���� const ����
	// --------------------------------------------
	void refreshInventory();

	//Getter
	int getHealth() const;
	int getAttack() const;
	size_t getInventorySize() const;
	string getName() const;
	int getLevel() const;
	int getMaxHealth() const;
	int getGold() const { return gold; }
	int getBaseAttack() const;
	int getExperience() const { return experience; }

	//Setter <-- SAVE/LOAD���� ���
	void setName(string _name);
	void setHealth(int _health);
	void setMaxHealth(int _maxHealth);
	void setBaseAttack(int _baseAttack);
	void setAttack(int _attack);
	void setLevel(int _level);
	void setExperience(int _exp);
	void setGold(int _gold);
	void setEquippedWeapon(Weapon* _weapon);
	void setInventory(const vector<Item*>& items);
	void setInventoryMap(const map<string, int>& itemCountMap);
	
	
	

	// For Shop (���� ������ �Լ�)
	bool SpendGold(int amount);      // ��� ����
	void AddGold(int amount);        // ��� �߰�
	Item* GetItem(int index);        // �κ��丮���� ������ ��������
	bool RemoveItem(int index);      // �κ��丮���� ������ ����

private:
	void RemoveItemCountMap(const string& name);
	void setInventory();
protected: 
	const int MAX_EXPERIENCE = 100;
	string name;
	int health;
	int maxHealth;
	int baseAttack;					// �⺻�� �Ǵ� ATK ��
	int attack;							// ���������� �ݿ��� ���� ATK�� (baseAttack + Weapon.damage)
	int level;
	int experience;
	int gold;
	Weapon* equippedWeapon;			// ���� ����
	vector <Item*> inventory;
	map<string, int> itemCountMap; //������ ������ ���� �߰�
};


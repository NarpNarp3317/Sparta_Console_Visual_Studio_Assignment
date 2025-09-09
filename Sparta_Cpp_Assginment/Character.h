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
	bool removeItem(string name);
	bool removeItemIdx(int index);
	void levelUp();
	void displayStatus();
	void reward(int exp, int gainGold);
	void takeDamage(int damage);
	void printInventory();
	bool checkingInventory(int index);

	void refreshATK();						// 새로 추가된 함수 09.08 -----
	Weapon* getEquippedWeapon() const;
	void setEquippedWeapon(Weapon* weapon);
	int getBaseAttack() const;
	void setBaseAttack(int atk);
	// --------------------------------------------

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
	void setInventory();
protected: 
	const int MAX_EXPERIENCE = 100;
	string name;
	int health;
	int maxHealth;
	int baseAttack;					// 기본이 되는 ATK 값
	int attack;							// 무기장착이 반영된 최종 ATK값 (baseAttack + Weapon.damage)
	int level;
	int experience;
	int gold;
	Weapon* equippedWeapon;			// 장착 무기
	vector <Item*> inventory;
	map<string, int> itemCountMap; //아이템 수량을 위해 추가
};


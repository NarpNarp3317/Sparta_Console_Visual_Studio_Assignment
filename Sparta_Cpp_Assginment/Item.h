#pragma once
#include <string>
#include "Character.h"
#include "Monster.h"
using namespace std;

enum class EItem
{
	AttackBoost,
	HealthPotion,
	Weapon
};


class Item
{
private:
	string name;			// 아이템의 이름을 의미합니다 (ex: healthPotion)
	int price;				// 아이템의 가격을 의미합니다 (ex: 15) 아마 골드 단위
	bool usable;			// 전투중 아이템 사용가능 여부 (ex: healthPotion은 사용가능함) 
	bool consumable;		// 아이템이 소모형인지 여부 / 사용하면 삭제될 것. (ex: healthPotion은 사용하면 제거 됨)
	string description;	// 아이템의 설명을 의미합니다 (ex: Restores 15 HP.)
public:
	Item(string name, int price, bool usable = false, bool consumable = false, string description = "None")
	{
		this->name = name;
		this->description;
		this->usable = usable;
		this->consumable = consumable;
		if (price < 0)
			price = 0;
		this->price = price;
	}
	~Item() {}
	string getName();
	int getPrice();
	bool isConsumable();
	bool isUsable();
	string getDescription();
	void setDescription(string desc);
	virtual void use(Character* character);
	virtual void use(Character* character, Monster* monster);
};


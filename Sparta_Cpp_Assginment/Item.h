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
	string name;			// �������� �̸��� �ǹ��մϴ� (ex: healthPotion)
	int price;				// �������� ������ �ǹ��մϴ� (ex: 15) �Ƹ� ��� ����
	bool usable;			// ������ ������ ��밡�� ���� (ex: healthPotion�� ��밡����) 
	bool consumable;		// �������� �Ҹ������� ���� / ����ϸ� ������ ��. (ex: healthPotion�� ����ϸ� ���� ��)
	string description;	// �������� ������ �ǹ��մϴ� (ex: Restores 15 HP.)
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


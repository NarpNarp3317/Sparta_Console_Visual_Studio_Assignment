#pragma once
#include <string>
#include "Character.h"
#define ITEM_WEAPON "Weapon"
#define ITEM_ATKBOOST "Attack Boost"
#define ITEM_HPPOTION "Health Potion"

using namespace std;

//ItemEnum
enum class EItem
{
	HealthPotion,
	AttackBoost,
	Weapon
};


class Item
{
	// 25.09.09. �̹�ǥ
	// private���� protected�� ���� -> ��ӹ��� Ŭ�������� ���� �����ϵ���
protected:
	string name;			// �������� �̸��� �ǹ��մϴ� (ex: healthPotion)
	int price;				// �������� ������ �ǹ��մϴ� (ex: 15) �Ƹ� ��� ����
	bool usable;			// ������ ������ ��밡�� ���� (ex: healthPotion�� ��밡����) 
	bool consumable;		// �������� �Ҹ������� ���� / ����ϸ� ������ ��. (ex: healthPotion�� ����ϸ� ���� ��)
	string description;		// �������� ������ �ǹ��մϴ� (ex: Restores 15 HP.)
	string typeName;		// SAVE/LOAD���� ������ ���� ���п�
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
		this->typeName = "Item";
	}
	~Item() {}
	string getName();
	int getPrice();
	bool isConsumable();
	bool isUsable();
	string getDescription();
	void setDescription(string desc);
	virtual void use(Character* character);

	// SAVE/LOAD��
	virtual std::string getTypeName() const {
		return typeName;
	}
	void setname(string name) { Item::setDescription(name); }
	void setprice(int price) { Item::setDescription(to_string(price)); }
	void setusable(bool usable) { Item::setDescription(usable ? "true" : "false"); }
	void setconsumable(bool consumable) { Item::setDescription(consumable ? "true" : "false"); }
	void setdescription(string desc) { Item::setDescription(desc); }
};


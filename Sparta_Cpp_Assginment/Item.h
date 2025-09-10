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
	// 25.09.09. 이무표
	// private에서 protected로 변경 -> 상속받은 클래스에서 접근 가능하도록
protected:
	string name;			// 아이템의 이름을 의미합니다 (ex: healthPotion)
	int price;				// 아이템의 가격을 의미합니다 (ex: 15) 아마 골드 단위
	bool usable;			// 전투중 아이템 사용가능 여부 (ex: healthPotion은 사용가능함) 
	bool consumable;		// 아이템이 소모형인지 여부 / 사용하면 삭제될 것. (ex: healthPotion은 사용하면 제거 됨)
	string description;		// 아이템의 설명을 의미합니다 (ex: Restores 15 HP.)
	string typeName;		// SAVE/LOAD에서 아이템 종류 구분용
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

	// SAVE/LOAD용
	virtual std::string getTypeName() const {
		return typeName;
	}
	void setname(string name) { Item::setDescription(name); }
	void setprice(int price) { Item::setDescription(to_string(price)); }
	void setusable(bool usable) { Item::setDescription(usable ? "true" : "false"); }
	void setconsumable(bool consumable) { Item::setDescription(consumable ? "true" : "false"); }
	void setdescription(string desc) { Item::setDescription(desc); }
};


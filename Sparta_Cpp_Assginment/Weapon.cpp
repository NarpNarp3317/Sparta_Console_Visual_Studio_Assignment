#include "Weapon.h"

void Weapon::use(Character* character)
{
	// 캐릭터 클래스에서 Item* euipmentweapon 멤버변수를 만든다면
	// character.getEquipmentWeapon()로 현재 장착중인 무기를 불러옴
	// inventory.push_back(euipmentweapon); 현재 장비중인 무기는 인벤토리로 돌려보냄
	// character->euipmentweapon = this;	// 캐릭터장비를 현재 아이템(장비)로 변경
	// 캐릭터의 공격력이 변화하면 될 것 같음
}


int Weapon::getDamage() { return this->damage; }
void Weapon::setDamage(int dmg) { this->damage = dmg; }

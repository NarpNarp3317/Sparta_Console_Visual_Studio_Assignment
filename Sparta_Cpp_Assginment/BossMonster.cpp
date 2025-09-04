#include "BossMonster.h"
BossMonster::BossMonster(int maxHealth, int attack) : Monster(maxHealth, attack)
{
	this->name = "BossMonster";
}


BossMonster::~BossMonster()
{

}
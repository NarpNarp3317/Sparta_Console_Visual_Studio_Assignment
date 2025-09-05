#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
	BossMonster(int maxHealth, int attack);
	~BossMonster();
};


#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin();
	Goblin(int maxHealth, int attack);
	~Goblin();
};


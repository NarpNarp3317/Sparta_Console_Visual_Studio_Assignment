#pragma once
#include "Monster.h"

class Troll : public Monster
{
public:
	Troll();
	Troll(int maxHealth, int attack);
	~Troll();
};


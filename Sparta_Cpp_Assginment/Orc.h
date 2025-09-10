#pragma once
#include "Monster.h"

class Orc : public Monster
{
public:
	Orc();
	Orc(int maxHealth, int attack);
	~Orc();
};


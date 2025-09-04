#pragma once
#include "Character.h"
#include "Item.h"
#include <vector>
class Player : public Character
{
public:

private:
	int level;
	int experience;
	int gold;
	vector<Item*> inventory;
};


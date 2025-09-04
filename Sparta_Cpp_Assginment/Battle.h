#pragma once
#include <iostream>

using namespace std;

class Character;
class Monster;

class Battle
{
public:
		Battle();
		~Battle();
		void startBattle(Character* _player, Monster* _monster);
};


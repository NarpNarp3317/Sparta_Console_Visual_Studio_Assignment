#pragma once
#include <iostream>

using namespace std;

class Character;
class Monster;

class Battle
{
public:
	Battle();
	void startBattle(Character* _player, Monster* _monster);
	void PrintSelectList();
	void PlayerAttackBehavior(Character* _player, Monster* _monster);
	void PlayerUseItemBehavior(Character* _player);
	void PlayerRecallBehavior();
	void PrintAttackBehaviorResult(const string& name, const int& damage, const int& curHp);
	bool BattleResult();
	~Battle();
private:
	bool isWin;
};


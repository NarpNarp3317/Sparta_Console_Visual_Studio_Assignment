#pragma once
#include <iostream>

using namespace std;

class Character;
class Monster;
class BattleStage;

class Battle
{
public:
	Battle();
	void printMonsterDie(const string& name);
	void startBattle(Character* _player);
	void printSelectList();
	void playerAttackBehavior(Character* _player);
	void playerUseItemBehavior(Character* _player);
	void playerRecallBehavior();
	void printAttackBehaviorResult(const string& name, const int& damage, const int& curHp);
	int selecting(const Character& _player);
	void battleResult(Character* _player, const BattleStage& battleStage);
	~Battle();
private:
	bool isWin;
	Monster* _monster;
};


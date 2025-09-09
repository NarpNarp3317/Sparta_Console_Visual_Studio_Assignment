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
	void playerAttackBehavior();
	void playerUseItemBehavior();
	void playerRecallBehavior();
	void printAttackBehaviorResult(const string& name, const int& damage, const int& curHp);
	//int selecting(const Character& _player);
	void battleResult(Character* _player);
	void resultPrint();
	void battleturnBehavior(int index);
	void monsterturnBehavior();
	~Battle();
private:
	bool isWin;
	int monsterIndex;
	Monster* _monster;
	Character* _player;
	BattleStage* battleStage;
};


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
	void startBattle(Character* _player);
	void playerAttackBehavior();
	void playerUseItemBehavior(int useItemIndex);
	void playerRecallBehavior();
	void battleResult(Character* _player);
	bool battleturnBehavior(int index, int itemIndex = 0);
	void monsterturnBehavior();
	void ShowReward(const string& item, const string& exp, const string& gold);
	~Battle();
private:
	bool isWin;
	int monsterIndex;
	Monster* _monster;
	Character* _player;
	BattleStage* battleStage;
};


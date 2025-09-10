#pragma once
#include <iostream>

using namespace std;

class Character;
class Monster;
class BattleStage;
class BattleStage_Layout;
class StringUpdater;

class Battle
{
public:
	Battle();
	void startBattle(Character* _player, BattleStage_Layout* layout);
	bool battleturnBehavior(int index, int itemIndex = 0);

	~Battle();

private:
	void playerAttackBehavior();
	void playerRecallBehavior();
	void playerUseItemBehavior(int useItemIndex);
	void battleResult(Character* _player);
	void monsterturnBehavior();
	void monsterCreateButton();
	void ShowReward(const string& item, const string& exp, const string& gold);
private:
	bool isWin;
	int monsterIndex;
	Monster* _monster;
	Character* _player;
	BattleStage* battleStage;
	BattleStage_Layout* layout;
	StringUpdater* string_updater;
};


#pragma once
#include <iostream>

using namespace std;

class Character;
class Monster;
class BattleStage;
class BattleStage_Layout;
class StringUpdater;
class Button;
class Layout;
class ConsoleManager;
class Lounge_Layout;
class Battle
{
public:
	Battle(Lounge_Layout* _LoungeLayout, ConsoleManager* _MyCM, BattleStage_Layout* _MyBattleStage);
	void startBattle(Character* _player, BattleStage_Layout* layout);
	bool battleturnBehavior(int index, int itemIndex = 0);
	void playerStatRefresh();
	~Battle();

private:
	void playerAttackBehavior();
	void playerRecallBehavior();
	void playerUseItemBehavior(int useItemIndex);
	void battleResult(Character* _player);
	void monsterturnBehavior();
	void monsterCreateButton();
	void monsterStatRefresh();
	void playerCreateButton();

	void ShowReward(const string& item, const string& exp, const string& gold);
private:
	bool isWin;
	int monsterIndex;
	Monster* _monster;
	Character* _player;
	BattleStage* battleStage;
	BattleStage_Layout* layout;
	Button* monsterTagBtn;
	Button* monsterStatBtn;

	//// 라운지 정보
	Lounge_Layout* LoungeLayout;
	ConsoleManager* MyCM;
	BattleStage_Layout* MyBattleStage;

	
	///  플레이어 정보
	Button* playerTagBtn = nullptr;
	Button* lbl_name = nullptr;
	Button* lbl_Lv = nullptr;
	Button* lbl_hp = nullptr;
	Button* lbl_atk = nullptr;
	Button* lbl_exp = nullptr;
	Button* lbl_gold = nullptr;

	Button* lbl_reward = nullptr;
};


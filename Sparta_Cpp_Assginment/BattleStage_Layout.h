#pragma once
#include "Layout.h"

class Battle;
class Character;
class ConsoleManager;
class StringUpdater;

class BattleStage_Layout:public Layout
{ 
public:
	BattleStage_Layout(Character* _chara, Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su);
	~BattleStage_Layout();
	void CreateButton(const string& name);
	void DeleteButton();
	void BattleStartSetup(Character* player);
	
public:
	Button* monsterButton;
	Battle* battle;
	StringUpdater* SU;
	ConsoleManager* mainCM;
	Character* mainPlayer;
	Layout* mainLoungeLayout;
};

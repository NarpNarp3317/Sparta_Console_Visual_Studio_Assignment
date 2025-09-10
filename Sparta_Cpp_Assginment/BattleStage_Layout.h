#pragma once
#include "Layout.h"

class Battle;
class Character;
class ConsoleManager;

class BattleStage_Layout:public Layout
{ 
public:
	BattleStage_Layout();
	void CreateButton(const string& name);
	void DeleteButton();
	void BattleStartSetup(Character* player);
	~BattleStage_Layout();

public:
	Button* monsterButton;
	Battle* battle;
};

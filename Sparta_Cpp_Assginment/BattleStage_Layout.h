#pragma once
#include "Layout.h"

class Battle;

class BattleStage_Layout:public Layout
{ 
public:
	BattleStage_Layout();
	void CreateButton(const string& name, Battle* battle);
	void DeleteButton();

public:
	Button* monsterButton;
};

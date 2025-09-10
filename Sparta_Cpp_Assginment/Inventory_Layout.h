#pragma once
#include "Layout.h"
#include "Character.h"
#include "StringUpdater.h"
#include "ConsoleManager.h"
#include "Button.h"

class Inventory_Layout:public Layout
{ 
public:
	Inventory_Layout(Character* _chara, Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su);
	void ButtonRefresh();
	void InventoryDisplay();
	void printLog(map<string, int> Inventorymap, Character* chara);

private:
	StringUpdater* SU;
	ConsoleManager* mainCM;
	Character* mainPlayer;
	Layout* mainLoungeLayout;
	vector<Button*> itemButtons;
	std::vector<std::string> itemNames;


};

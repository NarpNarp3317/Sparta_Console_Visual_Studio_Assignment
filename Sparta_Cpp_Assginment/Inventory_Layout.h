#pragma once
#include "Layout.h"
#include "Character.h"
#include "StringUpdater.h"
#include "ConsoleManager.h"
#include "Button.h"

class Lounge_Layout;

class Inventory_Layout:public Layout
{ 
public:
	Inventory_Layout(Character* _chara, Lounge_Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su);
	void ButtonRefresh();
	void InventoryDisplay();
	void printLog(map<string, int> Inventorymap, Character* chara);

private:
	StringUpdater* SU;
	ConsoleManager* mainCM;
	Character* mainPlayer;
	Lounge_Layout* mainLoungeLayout;
	vector<Button*> itemButtons;
	std::vector<std::string> itemNames;


};

#pragma once
#include "Layout.h"
#include "Character.h"
#include "StringUpdater.h"
#include "ConsoleManager.h"

class Inventory_Layout:public Layout
{ 
public:
	Inventory_Layout(Character* _chara, Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su);
	void InventoryDisplay();
	void printLog(map<string, int> Inventorymap, Character* chara);

private:
	StringUpdater *_su;
	ConsoleManager* mainCM;
	Character* mainPlayer;
	Layout* mainLoungeLayout;
};

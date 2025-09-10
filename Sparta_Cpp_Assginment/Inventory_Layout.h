#pragma once
#include "Layout.h"
#include "Character.h"
#include "StringUpdater.h"

class Inventory_Layout:public Layout
{ 
public:
	
	Inventory_Layout();
	void InventoryDisplay(Character* chara);
	void printLog(map<string, int> Inventorymap, Character* chara);

private:
	StringUpdater *_su;
};

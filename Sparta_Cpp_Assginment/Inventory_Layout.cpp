#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include "Character.h"
#include "Logger.h"
#include "Weapon.h"
#include "StringUpdater.h"


Inventory_Layout::Inventory_Layout(Character* _chara, Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su):
mainCM(_mainCM),
mainLoungeLayout(_LoungeLayout),
mainPlayer(_chara)
{
	_su = new StringUpdater({ 10, 2 });
};

void Inventory_Layout::printLog(map<string, int> Inventorymap, Character* chara) {	// 로그 확인
	map<string, int> curr_Inventorymap = chara->getItemCountMap();
	string logstr;
	if (!Inventorymap.empty())
		for (auto item : Inventorymap)
			logstr += item.first + ": " + to_string(curr_Inventorymap[item.first]) + "\t";
	else
		logstr = "None";
	Logger::getInstance().myLog(logstr);
	_su->StringUpdate(logstr);

	logstr = "Inventory: ";
	vector<Item*> curr_Inventory = chara->getInventory();
	for (int i = 0; i < curr_Inventory.size(); i++)
		logstr += "[" + curr_Inventory[i]->getName() + "]\t";
	Logger::getInstance().myLog(logstr);
}

void Inventory_Layout::InventoryDisplay() {
	//===== Example ======//
	mainPlayer->addItem(new Weapon("Iron sword", 50, 20, true, true, "strong weapon"));
	mainPlayer->addItem(new Weapon("Wooden Bow", 50, 20, true, true, "strong weapon"));
	vector<Button*> itemButtons;
	int i = 0;

	map<string, int> Inventorymap = mainPlayer->getItemCountMap();
	for (auto item : Inventorymap) {
		int index = i;
		string temp_name = item.first;
		int pos = temp_name.find(" ");
		if (pos != string::npos)
			temp_name.replace(pos, 1, "_");

		// 아이템 버튼 생성 수정
		COORD width = { 20, 5 };
		COORD offset = { (short)i * 22, 0 };
		itemButtons.push_back(new Button(
			0,
			1,
			temp_name,
			center_center,
			width,     // Pass the COORD object
			offset,    // Pass the COORD object
			double_line,
			White,
			Black
		));

		itemButtons[i]->SetOnLeftPressed([this, index]() {
			// Get the current item map inside the lambda, when the button is pressed.
			map<string, int> current_Inventorymap = this->mainPlayer->getItemCountMap();
			// Use the correct member variable for the player.
			this->mainPlayer->useItem(index);
			// Pass the correct map and player object.
			this->printLog(current_Inventorymap, this->mainPlayer);
			});

		AddButton(itemButtons[i]);
		i += 1;
	}
};

#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include "Character.h"
#include "Logger.h"
#include "Weapon.h"
#include "StringUpdater.h"


Inventory_Layout::Inventory_Layout(Character* _chara, Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su):
mainCM(_mainCM),
mainLoungeLayout(_LoungeLayout),
mainPlayer(_chara),
SU(_su)
{
};

// 람다식 개선으로 이 함수 사용 안함
void Inventory_Layout::printLog(map<string, int> Inventorymap, Character* chara) {	// 로그 확인
	map<string, int> curr_Inventorymap = chara->getItemCountMap();
	string logstr;
	if (!Inventorymap.empty())
		for (auto item : Inventorymap)
			logstr += item.first + ": " + to_string(curr_Inventorymap[item.first]) + "\t";
	else
		logstr = "None";
	Logger::getInstance().myLog(logstr);
	SU->StringUpdate(logstr);

	logstr = "Inventory: ";
	vector<Item*> curr_Inventory = chara->getInventory();
	for (int i = 0; i < curr_Inventory.size(); i++)
		logstr += "[" + curr_Inventory[i]->getName() + "]\t";
	Logger::getInstance().myLog(logstr);
}

void Inventory_Layout::InventoryDisplay() {
	//===== Example ======//
	//mainPlayer->addItem(new Weapon("Iron sword", 50, 20, true, true, "strong weapon"));
	//mainPlayer->addItem(new Weapon("Wooden Bow", 50, 20, true, true, "strong weapon"));

	for (Button* btn : itemButtons) {
		delete btn;
	}
	itemButtons.clear();

	int i = 0;
	map<string, int> Inventorymap = mainPlayer->getItemCountMap();
	int garo = 0;
	int sero = 0;
	for (auto item : Inventorymap) {
		int index = i;
		if (index % 4 == 0)
		{
			sero += 5;
			garo = 0;
		}
		string temp_name = item.first;
		int pos = temp_name.find(" ");
		temp_name += "(" + to_string(Inventorymap[item.first]);
		temp_name += ")";

		LOG(item.first);
		LOG(to_string(Inventorymap[item.first]));

		if (pos != string::npos)
			temp_name.replace(pos, 1, "_");

		// 아이템 버튼 생성 수정
		COORD width = { 30, 5 };
		COORD offset = { (short)garo * 30 - 45, sero };
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

		this->itemNames.push_back(item.first);

		//itemButtons[i]->SetOnLeftPressed([this, index]() {
		//	map<string, int> current_Inventorymap = this->mainPlayer->getItemCountMap();
		//	this->mainPlayer->useItem(index);
		//	this->printLog(current_Inventorymap, this->mainPlayer);
		//	});

		itemButtons[index]->SetOnLeftPressed([this, index]() {
			this->mainPlayer->useItem(index);
			map<string, int> current_Inventorymap = this->mainPlayer->getItemCountMap();

			string logstr;
			if (!current_Inventorymap.empty())
				for (auto item : current_Inventorymap)
					logstr += item.first + ": " + to_string(current_Inventorymap[item.first]) + "\t";
			else
				logstr = "None";

			LOG(logstr);
			SU->StringUpdate("NOW ITEM : " + logstr);
			LOG("----------");
			LOG(this->itemButtons[index]->GetLable());

			// 무기는 다른걸 끼면 다른걸 해제하면서 숫자가 +1 되어야 해서 모든 버튼을 재구성
			for (int k = 0; k < this->itemButtons.size(); k++)
			{
				string newLableName = "";
				string currentItemName = this->itemNames[k]; // Get the correct item name for this button
				int pos = currentItemName.find(" ");
				int currentCount = current_Inventorymap[currentItemName];

				newLableName = currentItemName;
				if (pos != string::npos) {
					newLableName.replace(pos, 1, "_");
				}
				newLableName += "(" + to_string(currentCount) + ")";

				this->itemButtons[k]->SetLable(newLableName);
				this->itemButtons[k]->UpdateButton();
			}
		});



		AddButton(itemButtons[i]);
		i += 1;
		garo++;
	}

	// 되돌아가는 버튼
	Button* ReturnBtn = new Button(
		0,
		1,
		"Back_Lounge",
		center_center,
		{20, 5},
		{0, -5},
		double_line,
		White,
		Black
	);
	ReturnBtn->SetOnLeftPressed([this]() {
		this->mainCM->SetCurrentDisplay(mainLoungeLayout);
	});
	AddButton(ReturnBtn);
};

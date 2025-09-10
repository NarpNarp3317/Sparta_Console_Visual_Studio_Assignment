#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include "Character.h"
#include "Logger.h"
#include "Weapon.h"

void printLog(map<string, int> Inventorymap, Character* chara) {	// 로그 확인
	map<string, int> curr_Inventorymap = chara->getItemCountMap();
	string logstr;
	if (!Inventorymap.empty())
		for (auto item : Inventorymap)
			logstr += item.first + ": " + to_string(curr_Inventorymap[item.first]) + "\t";
	else
		logstr = "None";
	Logger::getInstance().myLog(logstr);

	logstr = "Inventory: ";
	vector<Item*> curr_Inventory = chara->getInventory();
	for (int i = 0; i < curr_Inventory.size(); i++)
		logstr += "[" + curr_Inventory[i]->getName() + "]\t";
	Logger::getInstance().myLog(logstr);
}

Inventory_Layout::Inventory_Layout()
{
	//===== Example ======//
	Character *chara = new Character("hello");
	chara->addItem(new Weapon("Iron sword", 50, 20, true, true, "strong weapon"));
	chara->addItem(new Weapon("Wooden Bow", 50, 20, true, true, "strong weapon"));
	map<string, int> Inventorymap = chara->getItemCountMap();
	vector<Button*> itemButtons;
	int i = 0;
	for (auto item : Inventorymap) {
		int index = i;
		string temp_name = item.first;
		int pos = temp_name.find(" ");
		if (pos != string::npos)
			temp_name.replace(pos, 1, "_");
		itemButtons.push_back(new Button(0, 1, temp_name, center_center, { 20,5 }, { (short)i*22, 0}, double_line, White, Black));
		itemButtons[i]->SetOnLeftPressed([chara, index,  Inventorymap]() { chara->useItem(index); printLog(Inventorymap, chara); });// function 추가
		AddButton(itemButtons[i]);// 다 만든후 layer에 보관
		i += 1;
	}
	/*
			- 버튼 아이디는 지금은 0으로;
			- priority는 0아니면 됨
			- 버튼에 표기할 label
			- 버튼의 뿌리 좌표 위치
			- 크기{x,y}
			- 오프셋 {x,y}  ({5,20 }--> y방향 아래로 20만큼, 방향으로 5만큼)
			- 외벽 프레임 스타일(두줄, 한줄, 줄 없음)
			- 글자색상, 배경 색상 (' '는 배경색상 지정해도 비어서 나오니 219 = █ 나 '_'사용 )
	*/



	//===== Extra ====//

	Scene newScene;

	SceneMaker::PrepareCanvas(&newScene, { 20,20 });// Scene maker로 이미지 만들어서 버튼 이미지를 바꿀수 있음. 반드시 크기는 버튼의 크기와 같아야 함
	//프레임 만들기, 색채우기, 색반전시키기, 글자 여러줄 넣기등 있음

	// 만들어낸 이미지를 버튼에 넣기는 잠시 미루기



		//----> 팝업창 작업중
		// 
		//----> popup 창이 필요하다면 여기에 필요로하는 기능과 글을 적어둘 것
		// 선택가능한 팝업창 기능 1.글자 표시+끄기 2. 다음으로 넘기기, 2. 대상 값(int)올리기 내리기








};

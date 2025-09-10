#include "BattleStage_Layout.h"
#include "SceneMaker.h"
#include "Battle.h"
#include "BattleStage.h"
#include "Character.h"
#include "Logger.h"
#include "ConsoleManager.h"
#include "StringUpdater.h"
#include "Lounge_Layout.h"
BattleStage_Layout::BattleStage_Layout(Character* _chara, Lounge_Layout* _LoungeLayout, ConsoleManager* _mainCM, StringUpdater* _su):
	mainCM(_mainCM),
	mainLoungeLayout(_LoungeLayout),
	mainPlayer(_chara),
	SU(_su)
{
	monsterButton = nullptr;
	battle = nullptr;
}

void BattleStage_Layout::CreateButton(const string& name)
{
	monsterButton = new Button(10, 1, name , center_center, { 20, 11 }, { 0,0 }, double_line, White, Black);
	monsterButton->SetOnLeftPressed([this] 
	{
		battle->battleturnBehavior(0);
	});

	AddButton(monsterButton);
}

// 전투 중 드랍템으로 획득했을 때 갱신하기 위해 추가
void BattleStage_Layout::updatePotionBtn(Character* player)
{
	string newitemcount0 = "Health_Potion(" + to_string(player->getItemCount(0)) + ")";
	UseItemButton1->SetLable(newitemcount0);
	UseItemButton1->UpdateButton();

	string newitemcount1 = "Attack_Boost(" + to_string(player->getItemCount(1)) + ")";
	UseItemButton2->SetLable(newitemcount1);
	UseItemButton2->UpdateButton();

	LOG("Update_btn");
}

void BattleStage_Layout::DeleteButton()
{
	RemoveButton(monsterButton);
}

void BattleStage_Layout::BattleStartSetup(Character* player)
{
	battle = new Battle(mainLoungeLayout, mainCM, this);
	battle->startBattle(player, this);
	string itemcount0 = "Health_Potion(" + to_string(player->getItemCount(0)) + ")";
	string itemcount1 = "Attack_Boost(" + to_string(player->getItemCount(1)) + ")";

	UseItemButton1 = new Button(0, 1, itemcount0, center_center, { 25, 5 }, { -25, 15 }, double_line, White, Black);
	UseItemButton1->SetOnLeftPressed([this, player]
		{
			if (battle->battleturnBehavior(1, 0) == false)
			{
				UseItemButton1->OnInvalidInput();
			}
			else
			{
				string newitemcount0 = "Health_Potion(" + to_string(player->getItemCount(0)) + ")";
				UseItemButton1->SetLable(newitemcount0);
				UseItemButton1->UpdateButton();
				battle->playerStatRefresh();
				LOG("UPDATE_BTN_1");
			}
		});// function 추가


		UseItemButton2 = new Button(0, 1, itemcount1, center_center, { 25, 5 }, { 0, 15 }, double_line, White, Black);
		UseItemButton2->SetOnLeftPressed([this, player]
		{
			if (battle->battleturnBehavior(1, 1) == false)
			{
				UseItemButton2->OnInvalidInput();
			}
			else
			{
				string newitemcount1 = "Attack_Boost(" + to_string(player->getItemCount(1)) + ")";
				UseItemButton2->SetLable(newitemcount1);
				UseItemButton2->UpdateButton();
				battle->playerStatRefresh();
				LOG("UPDATE_BTN_2");
			}
		});// function 추가

		Button* RecallButton = new Button(0, 1, "Recall", center_center, { 17, 5 }, { 25, 15 }, double_line, White, Black);
		RecallButton->SetOnLeftPressed([this, RecallButton]
		{
				/// 25.09.10. mpyi _ 라운지로 복귀
			if (battle->battleturnBehavior(2) == false)
			{
				LOG("ERROR_LOUNGE_FAIL");
				RecallButton->OnInvalidInput();
			}
			/*this->mainCM->SetCurrentDisplay(mainLoungeLayout);*/
			// this->~BattleStage_Layout();
		});

		player->getStatus();
		AddButton(UseItemButton1);// 다 만든후 layer에 보관
		AddButton(UseItemButton2);// 다 만든후 layer에 보관
		AddButton(RecallButton);
		//===== Extra ====//

		//Scene newScene;

		//SceneMaker::PrepareCanvas(&newScene, { 20,20 });// Scene maker로 이미지 만들어서 버튼 이미지를 바꿀수 있음. 반드시 크기는 버튼의 크기와 같아야 함

		//SceneMaker::AddTexts(&newScene, { 50, 50 }, { -70, 0 }, { "test1","test2","test3","test4" }, center_center, White, Black);
}

BattleStage_Layout::~BattleStage_Layout()
{
	if (monsterButton != nullptr)
	{
		DeleteButton();
	}

	delete battle;
	battle = nullptr;
}


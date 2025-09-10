#include "BattleStage_Layout.h"
#include "SceneMaker.h"
#include "Popup.h"
#include "Battle.h"
#include "BattleStage.h"
#include "Character.h"

BattleStage_Layout::BattleStage_Layout()
{
	monsterButton = nullptr;
	battle = nullptr;
}

void BattleStage_Layout::CreateButton(const string& name, Battle* battle)
{
	monsterButton = new Button(0, 1, name , center_center, { 20, 11 }, { 0,0 }, double_line, White, Black);
	monsterButton->SetOnLeftPressed([battle] {battle->battleturnBehavior(0); });
	AddButton(monsterButton);
}

void BattleStage_Layout::DeleteButton()
{
	RemoveButton(monsterButton);// remove from the list of interactables first

	delete monsterButton;
	monsterButton = nullptr;
}

void BattleStage_Layout::BattleStartSetup(Character* player)
{
	battle = new Battle();
	battle->startBattle(player, this);

	Button* UseItemButton1 = new Button(0, 1, "<<HealItem>>", center_center, { 20, 11 }, { -25, 15 }, double_line, White, Black);
	UseItemButton1->SetOnLeftPressed([this, UseItemButton1]
		{
			if (battle->battleturnBehavior(1, 0) == false)
			{
				UseItemButton1->OnInvalidInput();
			}
		});// function 추가

		Button* UseItemButton2 = new Button(0, 1, "<<AttackBoost>>", center_center, { 20, 11 }, { 0, 15 }, double_line, White, Black);
		UseItemButton2->SetOnLeftPressed([this, UseItemButton2]
		{
			if (battle->battleturnBehavior(1, 0) == false)
			{
				UseItemButton2->OnInvalidInput();
			}
		});// function 추가

		Button* RecallButton = new Button(0, 1, "<<Recall>>", center_center, { 20, 11 }, { 25, 15 }, double_line, White, Black);
		RecallButton->SetOnLeftPressed([this, RecallButton]
		{
			if (battle->battleturnBehavior(2) == false)
			{
				RecallButton->OnInvalidInput();
			}
		});

		AddButton(UseItemButton1);// 다 만든후 layer에 보관
		AddButton(UseItemButton2);// 다 만든후 layer에 보관
		AddButton(RecallButton);


		//===== Extra ====//

		Scene newScene;

		SceneMaker::PrepareCanvas(&newScene, { 20,20 });// Scene maker로 이미지 만들어서 버튼 이미지를 바꿀수 있음. 반드시 크기는 버튼의 크기와 같아야 함

		SceneMaker::AddTexts(&newScene, { 50, 50 }, { -70, 0 }, { "test1","test2","test3","test4" }, center_center, White, Black);
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


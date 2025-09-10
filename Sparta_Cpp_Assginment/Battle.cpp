#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Logger.h"
#include "StringUpdater.h"
#include "BattleStage_Layout.h"
#include "Button.h"
#include "ConsoleManager.h"
#include "BattleStage_Layout.h"

#include <limits> 

Button* ExampleButton;

Battle::Battle(Layout* _LoungeLayout, ConsoleManager* _MyCM, BattleStage_Layout* _MyBattleStage):
	LoungeLayout(_LoungeLayout),
	MyCM(_MyCM),
	MyBattleStage(_MyBattleStage)
{
	isWin = false;
	_monster = nullptr;
	_player = nullptr;
	battleStage = new BattleStage();
	monsterIndex = 0;
	string_updater = new StringUpdater({ 10,2 });
}

// 25.09.04. 이무표
// 이곳에 전투 로직을 작성하면 될 것 같습니다.
// 필요한 함수나 변수가 있다면 해당 Battle 클래스에 추가해서 사용하면 됩니다.
// 일단 몬스터나 플레이어 동적 할당 해제 코드 여기 작성

void Battle::startBattle(Character* _player, BattleStage_Layout* layout)
{
	cout << "Battle Start" << endl;
	this->_player = _player;
	this->layout = layout;
	battleStage->randomMonsterAdded(_player->getLevel());
	_monster = battleStage->getMonster(monsterIndex);

	Logger::getInstance().myLog("monster Count : " + to_string(battleStage->getMonsterSize()));

	monsterCreateButton();
}

void Battle::playerAttackBehavior()
{
	if (_player != nullptr && _monster != nullptr)
	{
		_monster->takeDamage(_player->getAttack());
		monsterStatRefresh();
	}
}

void Battle::playerUseItemBehavior(int useItemIndex)
{
	_player->useItem(useItemIndex); //있다면 아이템 사용	
}

void Battle::playerRecallBehavior()
{
	///cout << "Leave Dungeon, Return to Lounge." << endl;

	/// 라운지로 이동시키는 코드 필요
	this->MyCM->SetCurrentDisplay(LoungeLayout);
	MyBattleStage->~BattleStage_Layout();

	/// 
}


void Battle::battleResult(Character* _player){
	int randomItemIndex = _monster->randomItem();
	string getItemName = "";
	// 30퍼 확률로 아이템 획득
	if (randomItemIndex >= 0)
	{
		EItem item_enum = static_cast<EItem>(randomItemIndex);
		switch (item_enum)
		{
		case EItem::HealthPotion:
			getItemName = "HealthPotion";
			_player->addItem(new HealthPotion(ITEM_HPPOTION, 15, 15));
			break;
		case EItem::AttackBoost:
			getItemName = "AttackBoost";
			_player->addItem(new AttackBoost(ITEM_ATKBOOST, 15, 15));
			break;
		default:
			break;
		}
	}
	_player->reward(_monster->getRewardExp(), _monster->getRewardGold());

	ShowReward(getItemName, to_string(_monster->getRewardExp()), to_string(_monster->getRewardGold()));
}

bool Battle::battleturnBehavior(int index, int itemIndex)
{
	switch (index)
	{
	case 0:
		playerAttackBehavior();
		break;
	case 1:
		if (_player->checkingInventorymap(itemIndex) == false) // 디버깅시 지켜볼 것
		{
			return false;
		}
		playerUseItemBehavior(itemIndex);
		return true;
	case 2:
		playerRecallBehavior();
		return true;
	default:
		break;
	}

	monsterturnBehavior();

	return true;
}



void Battle::monsterturnBehavior()
{
	if (_monster != nullptr && _player != nullptr)
	{
		if (_monster->getHealth() <= 0)
		{
			battleResult(_player); //보상 지급 처리
			_monster = battleStage->getMonster(++monsterIndex); //다음 몬스터
			layout->DeleteButton();

			if (_monster == nullptr) // 다음 몬스터가 없으면 승리로 처리하고 break
			{
				isWin = true;
				//라운지로 이동 코드 필요
				playerRecallBehavior();
			}
			else
			{
				monsterCreateButton();
				monsterStatRefresh();
			}
		}
		else
		{
			// 몬스터 -> 플레이어 공격
			_player->takeDamage(_monster->getAttack());

			StringUpdater string_updater({ 20,10 });
			string_updater.CleanStrings();
			string_updater.StringUpdate("Monster Attack >> Player");
		}
	}

	if (_player->getHealth() <= 0)
	{
		// 라운지로 이동 코드 필요
	}

}

void Battle::monsterCreateButton()
{
	layout->CreateButton(_monster->getName());

	string stats = "HP=" + to_string(_monster->getHealth()) + "_ATK=" + to_string(_monster->getAttack());
	monsterStatBtn = new Button(10, 1, stats, center_center, { 17, 5 }, { 0, -10 }, double_line, White, Black);

	layout->AddButton(monsterStatBtn);
}

void Battle::monsterStatRefresh()
{
	string stats = "HP=" + to_string(_monster->getHealth()) + "_ATK=" + to_string(_monster->getAttack());
	monsterStatBtn->SetLable(stats);
	monsterStatBtn->UpdateButton();
}

void Battle::ShowReward(const string& item, const string& exp, const string& gold)
{
	string_updater->CleanStrings();
	string text = "Reward : ";
	text += item.empty() ? "" : item + ", ";
	text += "EXP : +" + exp + " ";
	text += "Gold : +" + gold;
	string_updater->StringUpdate(text);

	_player->getStatus();
}

Battle::~Battle()
{
	battleStage->removeMonsterList();
	delete battleStage;
	delete string_updater;
	battleStage = nullptr;
	string_updater = nullptr;
}



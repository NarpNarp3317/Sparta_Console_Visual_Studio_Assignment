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
#include "Lounge_Layout.h"
#include "Weapon.h"

#include <limits> 
StringUpdater string_updater({ 20,10 });

Battle::Battle(Lounge_Layout* _LoungeLayout, ConsoleManager* _MyCM, BattleStage_Layout* _MyBattleStage):
	LoungeLayout(_LoungeLayout),
	MyCM(_MyCM),
	MyBattleStage(_MyBattleStage)
{
	isWin = false;
	_monster = nullptr;
	_player = nullptr;
	battleStage = new BattleStage();
	monsterIndex = 0;
}

// 25.09.04. �̹�ǥ
// �̰��� ���� ������ �ۼ��ϸ� �� �� �����ϴ�.
// �ʿ��� �Լ��� ������ �ִٸ� �ش� Battle Ŭ������ �߰��ؼ� ����ϸ� �˴ϴ�.
// �ϴ� ���ͳ� �÷��̾� ���� �Ҵ� ���� �ڵ� ���� �ۼ�

void Battle::startBattle(Character* _player, BattleStage_Layout* layout)
{
	cout << "Battle Start" << endl;
	this->_player = _player;
	this->layout = layout;
	battleStage->randomMonsterAdded(_player->getLevel());
	_monster = battleStage->getMonster(monsterIndex);

	Logger::getInstance().myLog("monster Count : " + to_string(battleStage->getMonsterSize()));

	monsterCreateButton();
	playerCreateButton();
}

void Battle::playerAttackBehavior()
{
	if (_player != nullptr && _monster != nullptr)
	{
		_monster->takeDamage(_player->getAttack());
		monsterStatRefresh();
		playerStatRefresh();
	}
}

void Battle::playerUseItemBehavior(int useItemIndex)
{
	_player->useItem(useItemIndex); //�ִٸ� ������ ���	
}

void Battle::playerRecallBehavior()
{
	///cout << "Leave Dungeon, Return to Lounge." << endl;

	/// ������� �̵���Ű�� �ڵ� �ʿ�
	LoungeLayout->updateStatus();
	this->MyCM->SetCurrentDisplay(LoungeLayout->getLayout());
	MyBattleStage->~BattleStage_Layout();

	/// 
}


void Battle::battleResult(Character* _player){
	int randomItemIndex = _monster->randomItem();
	string getItemName = "";
	// 30�� Ȯ���� ������ ȹ��
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

	/// ������ ������� ���� ȹ��� UI �ݿ�
	layout->updatePotionBtn(_player);
	_player->reward(_monster->getRewardExp(), _monster->getRewardGold());

	ShowReward(getItemName, to_string(_monster->getRewardExp()), to_string(_monster->getRewardGold()));
}

bool Battle::battleturnBehavior(int index, int itemIndex)
{
	switch (index)
	{
	case 0:
	{
		playerAttackBehavior();
		monsterturnBehavior();
		break;
	}
	case 1:
	{
		int idx = 0;
		int havingPoint = 0;
		for (auto it : _player->getItemCountMap())
		{
			if (itemIndex == 0)
			{
				if (it.first == ITEM_HPPOTION)
				{
					LOG("now have HP potion : "+to_string(it.second));
					havingPoint = it.second;
					break;
				}
			}
			else if (itemIndex == 1)
			{
				if (it.first == ITEM_ATKBOOST)
				{
					LOG("now have ATK Boost : " + to_string(it.second));
					havingPoint = it.second;
					break;
				}
			}
			idx++;
		}
		if (havingPoint <= 0) return false;
		// ����üũ ������ ��
		//if (_player->checkingInventorymap(idx) == false) // ������ ���Ѻ� ��
		//{
		//	LOG("No item now...");
		//	return false;
		//}
		
		playerUseItemBehavior(idx);
		monsterturnBehavior();
		break;
	}
	case 2:
	{
		playerRecallBehavior();
		break;
	}
	default:
		return false;
	}

	return true;
}



void Battle::monsterturnBehavior()
{
	if (_monster != nullptr && _player != nullptr)
	{
		if (_monster->getHealth() <= 0)
		{
			battleResult(_player); //���� ���� ó��
			_monster = battleStage->getMonster(++monsterIndex); //���� ����
			layout->DeleteButton();
			if (_monster == nullptr) // ���� ���Ͱ� ������ �¸��� ó���ϰ� break
			{
				LOG("sssdd");
				isWin = true;
				// ������� �ٷ� �̵������� ��Ʈ�� ������Ʈ ����
				// string_updater.StringUpdate("Win!! Press the recall button to leave");

				if (battleStage->getBossCount() == 2)
				{
					LoungeLayout->createSysMsg("You_Clear_Game!!!!");
				}
				else
				{
					LoungeLayout->createSysMsg("Win_the_Battle!!!");
				}
				
				playerRecallBehavior();
				return;
			}
			else
			{
				monsterCreateButton();
				monsterStatRefresh();
				playerStatRefresh();
			}
		}
		else
		{
			// ���� -> �÷��̾� ����
			_player->takeDamage(_monster->getAttack());
			_player->getStatus();
		}
	}
	if (_player != nullptr)
	{
		if (_player->getHealth() <= 0)
		{
			// string_updater.StringUpdate("DEFEAT.. Press the recall button to leave");
			// ������� �ٷ� �̵������� ��Ʈ�� ������Ʈ ����
			// string_updater.StringUpdate("Win!! Press the recall button to leave");
			LoungeLayout->createSysMsg("DEFEAT..");
			playerRecallBehavior();
		}
	}
}

void Battle::playerCreateButton()
{
	// ��Ʈ������
	string str_Lv = "LV_:_" + to_string(_player->getLevel());
	string strHP = "HP_:_" + to_string(_player->getHealth()) + "/" + to_string(_player->getMaxHealth());
	string strATK = "ATK_:_";
	if (_player->getEquippedWeapon() != nullptr)
	{
		strATK += to_string(_player->getBaseAttack()) + "(" + to_string(_player->getEquippedWeapon()->getDamage()) + ")";
	}
	else
	{
		strATK += to_string(_player->getBaseAttack());
	}
	string str_exp = "EXP_:_" + to_string(_player->getExperience());
	string str_gold = "GOLD_:_" + to_string(_player->getGold());

	// ��ư �ʱ�ȭ

	string monsterTag = "PLAYER_INFO";
	playerTagBtn = new Button(10, 1, monsterTag, center_center, { 50, 3 }, { 0, -22 }, double_line, White, Black);
	lbl_name = new Button(0, 2, _player->getName(), center_center, { 50, 3 }, { 0, -20 }, double_line, White, Gray);
	lbl_Lv = new Button(0, 2, str_Lv, center_center, { 50, 3 }, { 0, -18 }, double_line, White, Gray);
	lbl_hp = new Button(0, 2, strHP, center_center, { 50, 3 }, { 0, -16 }, double_line, White, Gray);
	lbl_atk = new Button(0, 2, strATK, center_center, { 50, 3 }, { 0, -14 }, double_line, White, Gray);
	lbl_exp = new Button(0, 2, str_exp, center_center, { 50, 3 }, { 0, -12 }, double_line, White, Gray);
	lbl_gold = new Button(0, 2, str_gold, center_center, { 50, 3 }, { 0, -10 }, double_line, White, Gray);

	// ���� ǥ�� ����
	layout->AddButton(playerTagBtn);
	layout->AddButton(lbl_name);
	layout->AddButton(lbl_Lv);
	layout->AddButton(lbl_hp);
	layout->AddButton(lbl_atk);
	layout->AddButton(lbl_exp);
	layout->AddButton(lbl_gold);
}
void Battle::playerStatRefresh()
{
	string str_Lv = "LV_:_" + to_string(_player->getLevel());
	string strHP = "HP_:_" + to_string(_player->getHealth()) + "/" + to_string(_player->getMaxHealth());
	string strATK = "ATK_:_";
	if (_player->getEquippedWeapon() != nullptr)
	{
		strATK += to_string(_player->getBaseAttack()) + "(" + to_string(_player->getEquippedWeapon()->getDamage()) + ")";
	}
	else
	{
		strATK += to_string(_player->getBaseAttack());
	}
	string str_exp = "EXP_:_" + to_string(_player->getExperience());
	string str_gold = "GOLD_:_" + to_string(_player->getGold());

	lbl_Lv->SetLable(str_Lv);
	lbl_hp->SetLable(strHP);
	lbl_atk->SetLable(strATK);
	lbl_exp->SetLable(str_exp);
	lbl_gold->SetLable(str_gold);

	lbl_Lv->UpdateButton();
	lbl_hp->UpdateButton();
	lbl_atk->UpdateButton();
	lbl_exp->UpdateButton();
	lbl_gold->UpdateButton();

}

void Battle::monsterCreateButton()
{
	layout->CreateButton(_monster->getName());

	string monsterTag = "Monster_INFO";
	monsterTagBtn = new Button(10, 1, monsterTag, center_center, { 30, 3 }, { 0, 03 }, double_line, White, Black);

	string stats = "HP=" + to_string(_monster->getHealth()) + "_ATK=" + to_string(_monster->getAttack());
	monsterStatBtn = new Button(10, 1, stats, center_center, { 30, 5 }, { 0, 0 }, double_line, White, Black);

	layout->AddButton(monsterTagBtn);
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
	// string_updater.NextLine();
	string text = "Reward : ";
	text += item.empty() ? "" : item + ", ";
	text += "EXP : +" + exp + " ";
	text += "Gold : +" + gold;
	// string_updater.StringUpdate(text);

	if (lbl_reward != nullptr)
	{
		layout->RemoveButton(lbl_reward);
		delete lbl_reward;
		lbl_reward = nullptr;		
	}

	if(lbl_reward == nullptr)
	lbl_reward = new Button(10, 1, text, center_center, { 90, 3 }, { 0, -5 }, double_line, White, Black);
	layout->AddButton(lbl_reward);
	lbl_reward->UpdateButton();

	// _player->getStatus();
}

Battle::~Battle()
{
	battleStage->removeMonsterList();
	delete battleStage;
	battleStage = nullptr;
}



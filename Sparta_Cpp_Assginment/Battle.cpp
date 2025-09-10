#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "Logger.h"
#include "StringUpdater.h"
#include <limits> 

Battle::Battle()
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

void Battle::startBattle(Character* _player)
{
	cout << "Battle Start" << endl;
	this->_player = _player;
	battleStage->randomMonsterAdded(_player->getLevel());
	_monster = battleStage->getMonster(monsterIndex);
}

void Battle::playerAttackBehavior()
{
	if (_player != nullptr && _monster != nullptr)
	{
		_monster->takeDamage(_player->getAttack());
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
		if (_player->checkingInventorymap(itemIndex) == false) // ������ ���Ѻ� ��
		{
			return false;
		}
		playerUseItemBehavior(itemIndex);
		break;
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
			battleResult(_player); //���� ���� ó��
			_monster = battleStage->getMonster(++monsterIndex); //���� ����

			if (_monster == nullptr) // ���� ���Ͱ� ������ �¸��� ó���ϰ� break
			{
				isWin = true;
				//������� �̵� �ڵ� �ʿ�
				//
			}
		}
		else
		{
			// ���� -> �÷��̾� ����
			_player->takeDamage(_monster->getAttack());
		}
	}
}

void Battle::ShowReward(const string& item, const string& exp, const string& gold)
{
	StringUpdater string_updater({ 10,2 });
	string_updater.CleanStrings();
	string text = "Reward : ";
	text += item.empty() ? "" : item + ", ";
	text += "EXP : +" + exp + " ";
	text += "Gold : +" + gold;
	string_updater.StringUpdate(text);
}

Battle::~Battle()
{
	battleStage->removeMonsterList();
	delete battleStage;
	battleStage = nullptr;
}



#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include <Windows.h>
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
	cout << _monster->getName() << endl;
	cout << _player->getName() << endl;
	
	battleturnBehavior(0);

	//if (_player->getLevel() >= 10)
	//{
	//	cout << "===========BossStage!!===========" << endl;
	//}
	//else
	//{
	//	cout << "===========Battle===========" << endl;
	//}

	//cout << _player->getName() << " vs " << _monster->getName() << endl;
	//cout << "Battle Start!" << endl;


	/*while (true)
	{*/
	//	if (_player->getHealth() <= 0)
	//	{
	//		isWin = false;
	//		break;
	//	}

	//


	//	//printSelectList();


	//	int selectNum = selecting(*_player);
	//	cout << "===========Player Behavior===========" << endl;
	//	switch (selectNum)
	//	{
	//	case 1:
	//		playerAttackBehavior();
	//		printAttackBehaviorResult(_monster->getName(), _player->getAttack(), _monster->getHealth());
	//		break;
	//	case 2:
	//		playerUseItemBehavior();
	//		break;
	//	case 3:
	//		playerRecallBehavior();
	//		battleStage.removeMonsterList(); 	// ���� ���� ��� �����Ҵ� ����
	//		return;
	//	default:
	//		break;
	//	}
	//}

	//battleStage.removeMonsterList(); 	// ���� ���� ��� �����Ҵ� ����
	//resultPrint();
}




void Battle::printSelectList()
{
	cout << "===========SELECT===========" << endl;
	cout << "1. Attack" << endl;
	cout << "2. UseItem" << endl;
	cout << "3. Recall" << endl;
}

void Battle::playerAttackBehavior()
{
	cout << _monster->getName() << endl;
	_monster->takeDamage(_player->getAttack());
}

void Battle::playerUseItemBehavior()
{
	
	_player->printInventory();

	while (true)
	{
		int selectNum = 0;

		cout << "Select Item : ";
		cin >> selectNum;


		if (_player->checkingInventory(selectNum - 1)) //������ ��ȣ�� ���濡 �ִ��� Ȯ��
		{
			_player->useItem(selectNum - 1); //�ִٸ� ������ ���
			break;
		}
		else
		{
			cout << "Invalid number, Please re-enter" << endl;
		}
	}
	
}

void Battle::playerRecallBehavior()
{
	cout << "Leave Dungeon, Return to Lounge." << endl;
}

void Battle::printAttackBehaviorResult(const string& name, const int& damage, const int& curHp)
{
	cout << name << " TakeDamage: " << damage << " HP : " << curHp << endl;
}



//int Battle::selecting(const Character& _player)
//{
//	while (true)
//	{
//		int selectNum = 0;
//
//		cout << "SELECT NUM : ";
//		cin >> selectNum;
//
//
//		if (selectNum == 1 || selectNum == 2 ||selectNum == 3)
//		{
//			if (selectNum == 2 && _player.getInventorySize() <= 0)
//			{
//				cout << "No Item, Please re-enter" << endl;
//				continue;
//			}
//			return selectNum;
//		}
//		else
//		{
//			cout << "Invalid number, Please re-enter" << endl;
//		}
//	}
//
//}

void Battle::battleResult(Character* _player){
	cout << "===========Slayed a monster ===========" << endl;
	cout << "Gold : +" << _monster->getRewardGold() << " , EXP : +" << _monster->getRewardExp() << endl;
	int randomItemIndex = _monster->randomItem();

	// 30�� Ȯ���� ������ ȹ��
	if (randomItemIndex >= 0)
	{
		EItem item_enum = static_cast<EItem>(randomItemIndex);

		cout << "Got a random item!! >> ";

		switch (item_enum)
		{
		case EItem::AttackBoost:
			cout << ITEM_ATKBOOST << endl;
			_player->addItem(new AttackBoost(ITEM_ATKBOOST, 15, 15));
			break;
		case EItem::HealthPotion:
			cout << ITEM_HPPOTION << endl;
			_player->addItem(new HealthPotion(ITEM_HPPOTION, 15, 15));
			break;
		default:
			break;
		}
	}
	_player->reward(_monster->getRewardExp(), _monster->getRewardGold());
	_player->displayStatus();
}

void Battle::resultPrint()
{
	cout << "===========BATTLE RESULT===========" << endl;
	if (isWin)
	{
		cout << "WIN!!\nReturn to Lounge.." << endl;
	}
	else
	{
		cout << "DEFEAT..\nReturn to Lounge.." << endl;
	}
}

void Battle::battleturnBehavior(int index)
{
	cout << index << endl;

	if (_player == nullptr)
	{
		cout << "NULLPTR!!!" << endl;
	}
	else
	{
		cout << "NO NULLPTR!!!" << endl;
	}


	cout << index << endl;
	switch (index)
	{
	case 0:
		playerAttackBehavior();
		break;
	case 1:
		playerUseItemBehavior();
		break;
	case 2:
		playerRecallBehavior();
		return;
	default:
		break;
	}

	//monsterturnBehavior();
}

void Battle::monsterturnBehavior()
{
	cout << 2 << endl;
	if (_monster->getHealth() <= 0)
	{
		printMonsterDie(_monster->getName());
		battleResult(_player); //���� ���� ó��
		_monster = battleStage->getMonster(++monsterIndex); //���� ����

		if (_monster == nullptr) // ���� ���Ͱ� ������ �¸��� ó���ϰ� break
		{
			isWin = true;
		}
		else //�ִٸ� �޽����� ���� ���� �����
		{
			cout << "===========Battle===========" << endl;
			cout << _player->getName() << " vs " << _monster->getName() << endl;
			cout << "Battle Start!" << endl;
		}
	}

	// ���� -> �÷��̾� ����
	cout << "===========Monster Behavior===========" << endl;
	_player->takeDamage(_monster->getAttack());
	printAttackBehaviorResult(_player->getName(), _monster->getAttack(), _player->getHealth());
}

void Battle::printMonsterDie(const string& name)
{
	cout << "===========MESSAGE===========" << endl;
	cout << name << " Die" << endl;
}


Battle::~Battle()
{

}



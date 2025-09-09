#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include <limits> 

Battle::Battle()
{
	isWin = false;
}

// 25.09.04. �̹�ǥ
// �̰��� ���� ������ �ۼ��ϸ� �� �� �����ϴ�.
// �ʿ��� �Լ��� ������ �ִٸ� �ش� Battle Ŭ������ �߰��ؼ� ����ϸ� �˴ϴ�.
// �ϴ� ���ͳ� �÷��̾� ���� �Ҵ� ���� �ڵ� ���� �ۼ�

void Battle::startBattle(Character* _player)
{
	int monsterIndex = 0;
	BattleStage battleStage;
	battleStage.randomMonsterAdded(_player->getLevel());
	_monster = battleStage.getMonster(monsterIndex);

	if (_player->getLevel() >= 10)
	{
		cout << "===========BossStage!!===========" << endl;
	}
	else
	{
		cout << "===========Battle===========" << endl;
	}

	cout << _player->getName() << " vs " << _monster->getName() << endl;
	cout << "Battle Start!" << endl;


	while (true)
	{
		if (_player->getHealth() <= 0)
		{
			isWin = false;
			break;
		}

		printSelectList();


		int selectNum = selecting(*_player);
		cout << "===========Player Behavior===========" << endl;
		switch (selectNum)
		{
		case 1:
			playerAttackBehavior(_player);
			printAttackBehaviorResult(_monster->getName(), _player->getAttack(), _monster->getHealth());
			break;
		case 2:
			playerUseItemBehavior(_player);
			break;
		case 3:
			playerRecallBehavior();
			battleStage.removeMonsterList(); 	// ���� ���� ��� �����Ҵ� ����
			return;
		default:
			break;
		}


		if (_monster->getHealth() <= 0)
		{
			printMonsterDie(_monster->getName());
			battleResult(_player, battleStage); //���� ���� ó��
			_monster = battleStage.getMonster(++monsterIndex); //���� ����

			if (_monster == nullptr) // ���� ���Ͱ� ������ �¸��� ó���ϰ� break
			{
				isWin = true;
				break;
			}
			else //�ִٸ� �޽����� ���� ���� �����
			{
				cout << "===========Battle===========" << endl;
				cout << _player->getName() << " vs " << _monster->getName() << endl;
				cout << "Battle Start!" << endl;
				continue;
			}
		}

		// ���� -> �÷��̾� ����
		cout << "===========Monster Behavior===========" << endl;
		_player->takeDamage(_monster->getAttack());
		printAttackBehaviorResult(_player->getName(), _monster->getAttack(), _player->getHealth());
	}

	battleStage.removeMonsterList(); 	// ���� ���� ��� �����Ҵ� ����
	resultPrint();
}

void Battle::printSelectList()
{
	cout << "===========SELECT===========" << endl;
	cout << "1. Attack" << endl;
	cout << "2. UseItem" << endl;
	cout << "3. Recall" << endl;
}

void Battle::playerAttackBehavior(Character* _player)
{
	_monster->takeDamage(_player->getAttack());
}

void Battle::playerUseItemBehavior(Character* _player)
{
	
	_player->printInventory();

	while (true)
	{
		int selectNum = 0;

		cout << "Select Item : ";
		cin >> selectNum;

		if (!inputCheck())
		{
			continue;
		}


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



int Battle::selecting(const Character& _player)
{
	while (true)
	{
		int selectNum = 0;

		cout << "SELECT NUM : ";
		cin >> selectNum;


		if (!inputCheck())
		{
			continue;
		}

		if (selectNum == 1 || selectNum == 2 ||selectNum == 3)
		{
			if (selectNum == 2 && _player.getInventorySize() <= 0)
			{
				cout << "No Item, Please re-enter" << endl;
				continue;
			}
			return selectNum;
		}
		else
		{
			cout << "Invalid number, Please re-enter" << endl;
		}
	}

}

void Battle::battleResult(Character* _player, BattleStage& battleStage){
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
			cout << "AttackBoost" << endl;
			_player->addItem(new AttackBoost("AttackBoost", 15, 15));
			break;
		case EItem::HealthPotion:
			cout << "HealthPotion" << endl;
			_player->addItem(new HealthPotion("HealthPotion", 15, 15));
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


bool Battle::inputCheck()
{
	// �Է¿� ���ڰ� �ƴ� ���ڳ� ��Ÿ �ٸ� �̻��Ѱ� ������ fail ó��
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a number." << endl;
		return false;
	}

	return true;
}

void Battle::printMonsterDie(const string& name)
{
	cout << "===========MESSAGE===========" << endl;
	cout << name << " Die" << endl;
}


Battle::~Battle()
{

}



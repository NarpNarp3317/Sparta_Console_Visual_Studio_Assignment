#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"

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

	cout << "===========Battle===========" << endl;
	cout << _player->getName() <<" vs " << _monster->getName() << endl;
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
			playerAttackBehavior(_player, _monster);
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
	battleResult(_player, battleStage); //���� ���� ó��
}

void Battle::printSelectList()
{
	cout << "===========SELECT===========" << endl;
	cout << "1. Attack" << endl;
	cout << "2. UseItem" << endl;
	cout << "3. Recall" << endl;
}

void Battle::playerAttackBehavior(Character* _player, Monster* _monster)
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

void Battle::battleResult(Character* _player, const BattleStage& battleStage){
	if (isWin)
	{
		cout << "===========RESULT===========" << endl;
		cout << "Win!\nGold : +" << battleStage.getRewardGold() << " , EXP : +" << battleStage.getRewardExp() << endl;
		_player->reward(battleStage.getRewardExp(), battleStage.getRewardGold());
		_player->displayStatus();
	}
}

void Battle::printMonsterDie(const string& name)
{
	cout << name << " Die" << endl;
}


Battle::~Battle()
{

}



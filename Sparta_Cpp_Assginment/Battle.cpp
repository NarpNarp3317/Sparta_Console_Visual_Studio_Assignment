#include "Battle.h"
#include "Character.h"
#include "Monster.h"

Battle::Battle()
{
	isWin = false;
}
Battle::~Battle()
{

}

// 25.09.04. �̹�ǥ
// �̰��� ���� ������ �ۼ��ϸ� �� �� �����ϴ�.
// �ʿ��� �Լ��� ������ �ִٸ� �ش� Battle Ŭ������ �߰��ؼ� ����ϸ� �˴ϴ�.
// �ϴ� ���ͳ� �÷��̾� ���� �Ҵ� ���� �ڵ� ���� �ۼ�

void Battle::startBattle(Character* _player, Monster* _monster)
{
	bool isWin = false;

	cout << _player->getName() <<" vs " << _monster->getName() << endl;
	cout << "Battle Start!" << endl;

	while (true)
	{
		if (_player->getHealth() <= 0)
		{
			isWin = false;
			break;
		}

		PrintSelectList();
		int selectNum = 0;

		cout << "SELECT NUM : ";
		cin >> selectNum;

		switch (selectNum)
		{
		case 1:
			PlayerAttackBehavior(_player, _monster);
			PrintAttackBehaviorResult(_monster->getName(), _player->getAttack(), _monster->getHealth());
			break;
		case 2:
			PlayerUseItemBehavior(_player);
			break;
		case 3:
			PlayerRecallBehavior();
			break;
		default:
			break;
		}

		if (_monster->getHealth() <= 0)
		{
			delete _monster;
			_monster = nullptr;
			isWin = true;
			break;
		}

		_player->takeDamage(_monster->getAttack());
		PrintAttackBehaviorResult(_player->getName(), _monster->getAttack(), _player->getHealth());
	}


}

void Battle::PrintSelectList()
{
	cout << "===========SELECT===========" << endl;
	cout << "1. Attack" << endl;
	cout << "2. UseItem" << endl;
	cout << "3. Recall" << endl;
}

void Battle::PlayerAttackBehavior(Character* _player, Monster* _monster)
{
	_monster->takeDamage(_player->getAttack());
}

void Battle::PlayerUseItemBehavior(Character* _player)
{

}

void Battle::PlayerRecallBehavior()
{

}

void Battle::PrintAttackBehaviorResult(const string& name, const int& damage, const int& curHp)
{
	cout << name << " TakeDamage: " << damage << " HP : " << curHp << endl;
}

bool Battle::BattleResult()
{
	if (isWin)
	{
		//Reward
	}
	return isWin;
}



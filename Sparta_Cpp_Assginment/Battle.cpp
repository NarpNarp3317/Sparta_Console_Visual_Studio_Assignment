#include "Battle.h"
#include "Character.h"
#include "Monster.h"
#include "BattleStage.h"

Battle::Battle()
{
	isWin = false;
}

// 25.09.04. 이무표
// 이곳에 전투 로직을 작성하면 될 것 같습니다.
// 필요한 함수나 변수가 있다면 해당 Battle 클래스에 추가해서 사용하면 됩니다.
// 일단 몬스터나 플레이어 동적 할당 해제 코드 여기 작성

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
			battleStage.removeMonsterList(); 	// 벡터 내부 요소 동적할당 해제
			return;
		default:
			break;
		}


		if (_monster->getHealth() <= 0)
		{
			printMonsterDie(_monster->getName());
			_monster = battleStage.getMonster(++monsterIndex); //다음 몬스터

			if (_monster == nullptr) // 다음 몬스터가 없으면 승리로 처리하고 break
			{
				isWin = true;
				break;
			}
			else //있다면 메시지를 띄우고 전투 재시작
			{
				cout << "===========Battle===========" << endl;
				cout << _player->getName() << " vs " << _monster->getName() << endl;
				cout << "Battle Start!" << endl;
				continue; 
			}
		}

		// 몬스터 -> 플레이어 공격
		cout << "===========Monster Behavior===========" << endl;
		_player->takeDamage(_monster->getAttack());
		printAttackBehaviorResult(_player->getName(), _monster->getAttack(), _player->getHealth());
	}

	battleStage.removeMonsterList(); 	// 벡터 내부 요소 동적할당 해제
	battleResult(_player, battleStage); //보상 지급 처리
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

		if (_player->checkingInventory(selectNum - 1)) //선택한 번호가 가방에 있는지 확인
		{
			_player->useItem(selectNum - 1); //있다면 아이템 사용
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



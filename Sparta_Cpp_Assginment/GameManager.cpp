#include "GameManager.h"


GameManager::GameManager()
{
	// player1 = new Character(); // makePlayer로 이동
	player1 = nullptr;
}
GameManager::~GameManager()
{
	player1 = nullptr;
	delete player1;
}

// 25.09.04. 이무표
// Log를 찍어보며 디버깅할 것이 있다면 이곳에 추가해서 확인하세요
void GameManager::StartGame()
{

	this->startMenu();

}

// 25.09.05. 이무표
// 게임 시작 메뉴
void GameManager::startMenu()
{	
	cout << "==========================" << endl;
	cout << "1. First Play" << endl;
	cout << "2. Load Data" << endl;
	cout << "3. Exit Game" << endl;
	cout << "==========================" << endl;
	while(true)
	{
		int selectNum = 0;
		cout << "Select Num : ";
		cin >> selectNum;
		if (selectNum == 1)
		{
			this->makePlayer();
			break;
		}
		else if (selectNum == 2)
		{
			this->loadPlayer();
			break;
		}
		else if (selectNum == 3)
		{
			exit(0);
		}
		else
		{
			cout << "Invalid number, Please re-enter" << endl;
		}
	}
	if(player1 == nullptr)
	{
		cout << "Player creation failed. Exiting game." << endl;
		exit(0);
	}

	visitLounge(player1);
}
// 25.09.05. 이무표
// 라운지 방문
void GameManager::visitLounge(Character* _player)
{
	while (true)
	{
		// 라운지 진입시 일단 플레이어 최대체력 회복
		_player->setHealth(_player->getMaxHealth());


		cout << "==========================" << endl;
		cout << "Welcome to the Lounge, " << _player->getName() << "!" << endl;
		cout << "You can choose one of the following options:" << endl;
		cout << "==========================" << endl;

		cout << "1. Battle" << endl;
		cout << "2. Visit Shop" << endl;
		cout << "3. Display Player Status" << endl;
		cout << "4. Display Inventory" << endl;
		cout << "5. Exit Game" << endl;
		int selectNum = 0;
		cout << "Select Num : ";
		cin >> selectNum;
		if (selectNum == 1)
		{
			this->battle(_player);
		}
		else if (selectNum == 2)
		{
			this->vistShop(_player);
		}
		else if (selectNum == 3)
		{
			_player->displayStatus();
		}
		else if (selectNum == 4)
		{
			_player->printInventory();
		}
		else if (selectNum == 5)
		{
			cout << "Exiting game. Goodbye!" << endl;
			exit(0);
		}
		else
		{
			cout << "Invalid number, Please re-enter" << endl;
		}
	}
}


// 25.09.05. 이무표
// 게임을 진행할 플레이어를 생성한다.
void GameManager::makePlayer()
{
	cout << "Welcome to the Dungeon" << endl;
	cout << "Please tell me your name" << endl;
	cout << "Name : ";
	string playerName = "";
	cin >> playerName;

	player1 = new Character(playerName);
}

// 25.09.05. 이무표
// 플레이어 로드
void GameManager::loadPlayer()
{
	// 추후 구현 일단 makePlayer로 대체
	this->makePlayer();
}

void GameManager::battle(Character* _player)
{
	Battle battle;
	battle.startBattle(_player);

}

void GameManager::vistShop(Character* _player)
{

}

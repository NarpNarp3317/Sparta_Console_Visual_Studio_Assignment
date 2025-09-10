#include "GameManager.h"


GameManager::GameManager()
{
	// player1 = new Character(); // makePlayer로 이동
	player1 = nullptr;
	// 외부 기능 생성
	nowShop = new Shop();
	saveManager = new SaveLoadManager();

}
GameManager::~GameManager()
{
	player1 = nullptr;
	delete player1;

	nowShop = nullptr;
	delete nowShop;

	saveManager = nullptr;
	delete saveManager;
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
	cout << "3. Save Delete" << endl;
	cout << "4. Exit Game" << endl;
	cout << "==========================" << endl;
	while(true)
	{
		int selectNum = 0;
		cout << "Select Num : ";
		cin >> selectNum;

		if (!inputCheck())
		{
			continue;
		}

		if (selectNum == 1)
		{
			this->makePlayer("TEMP");
			break;
		}
		else if (selectNum == 2)
		{
			this->loadPlayer();
			break;
		}
		else if (selectNum == 3)
		{
			this->deletePlayer();
			this->makePlayer("TEMP");
			break;
		}
		else if (selectNum == 4)
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
		cout << "5. Save Game" << endl;
		cout << "6. Exit Game" << endl;
		int selectNum = 0;
		cout << "Select Num : ";
		cin >> selectNum;

		if (!inputCheck())
		{
			continue;
		}

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
			//_player->displayStatus();
		}
		else if (selectNum == 4)
		{
			_player->printInventory();
		}
		else if (selectNum == 5)
		{
			this->savePlayer();
		}
		else if (selectNum == 6)
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
void GameManager::makePlayer(string _name)
{
	//cout << "Welcome to the Dungeon" << endl;
	//cout << "Please tell me your name" << endl;
	//cout << "Name : ";
	//string playerName = "";
	//cin >> playerName;

	// player1 = new Character(playerName);

	/// UI 시스템에 맞춰 위는 전부 주석처리
	player1 = new Character(_name);
}

// 입력 단계에서 숫자가 아닌게 들어왔을 때 확인 후 다시 입력하게하기 위해 추가된 함수
bool GameManager::inputCheck()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a number." << endl;
		return false;
	}

	return true;
}

// 25.09.05. 이무표
// 플레이어 로드
bool GameManager::loadPlayer()
{
	//player1 = new Character();
	//if (!saveManager->LoadGame(this->player1))
	//{
	//	// 로드 실패시 신규 생성으로 진입
	//	player1 = nullptr;
	//	delete player1;
	//	this->makePlayer("TEMP");
	//}

	/// UI화에 맞춰 UI 클래스에서 로드 실패 후 진행 담당
	return saveManager->LoadGame(this->player1);
}
bool GameManager::deletePlayer()
{
	return saveManager->saveDeleter();
	// std::cout << "Playe the New Character!" << std::endl;
}

void GameManager::savePlayer()
{
	saveManager->SaveGame(this->player1);
}

void GameManager::battle(Character* _player)
{
	// Battle battle;
	//battle.startBattle(_player);

}

void GameManager::vistShop(Character* _player)
{
	bool shopFlag = true;
	while (shopFlag)
	{
		int selectNum = 0;
		cout << "==========================" << endl;
		cout << "Welcome to the Shop!" << endl;
		cout << "You can choose one of the following options:" << endl;
		cout << "1. Buy Item" << endl;
		cout << "2. Sell Item" << endl;
		cout << "3. Exit Shop" << endl;
		cout << "==========================" << endl;
		cin >> selectNum;

		switch (selectNum)
		{

		case(1):
			nowShop->BuyItem(*_player);
			break;
		case(2):
			nowShop->SellItem(*_player);
			break;
		case(3):
			shopFlag = false;
			break;
		default:			
			break;
		}
	}
}

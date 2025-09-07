#include "GameManager.h"


GameManager::GameManager()
{
	// player1 = new Character(); // makePlayer�� �̵�
	player1 = nullptr;
}
GameManager::~GameManager()
{
	player1 = nullptr;
	delete player1;
}

// 25.09.04. �̹�ǥ
// Log�� ���� ������� ���� �ִٸ� �̰��� �߰��ؼ� Ȯ���ϼ���
void GameManager::StartGame()
{

	this->startMenu();

}

// 25.09.05. �̹�ǥ
// ���� ���� �޴�
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
// 25.09.05. �̹�ǥ
// ����� �湮
void GameManager::visitLounge(Character* _player)
{
	while (true)
	{
		// ����� ���Խ� �ϴ� �÷��̾� �ִ�ü�� ȸ��
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


// 25.09.05. �̹�ǥ
// ������ ������ �÷��̾ �����Ѵ�.
void GameManager::makePlayer()
{
	cout << "Welcome to the Dungeon" << endl;
	cout << "Please tell me your name" << endl;
	cout << "Name : ";
	string playerName = "";
	cin >> playerName;

	player1 = new Character(playerName);
}

// 25.09.05. �̹�ǥ
// �÷��̾� �ε�
void GameManager::loadPlayer()
{
	// ���� ���� �ϴ� makePlayer�� ��ü
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

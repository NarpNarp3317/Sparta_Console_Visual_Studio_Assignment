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
		cout << "==========================" << endl;
		cout << "Welcome to the Lounge, " << _player->getName() << "!" << endl;
		cout << "You can choose one of the following options:" << endl;
		cout << "==========================" << endl;

		cout << "1. Battle" << endl;
		cout << "2. Visit Shop" << endl;
		cout << "3. Display Inventory" << endl;
		cout << "4. Exit Game" << endl;
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
			this->displayInventory(_player);
		}
		else if (selectNum == 4)
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
	// Monster* monster = generateMonster(_player->getLevel());
	Monster* monster = generateMonster(1); // getLevel() �Լ��� ��� �ӽ÷� 1�� ����
	battle.startBattle(_player);

}

void GameManager::vistShop(Character* _player)
{

}

void GameManager::displayInventory(Character* _player)
{
	_player->printInventory();
}

Monster* GameManager::generateMonster(int _level)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, static_cast<int>(MonsterType::SIZE) - 1);
	MonsterType randomMonster = static_cast<MonsterType>(distrib(gen));

	Monster* rtrMonster = nullptr;	
	/// ������ ���缭 ������ ���� ���͸� ���׷���Ʈ �� �� �ֵ��� �ؾ� ��
	switch (randomMonster)
	{
		case(MonsterType::en_Gobling):
		{
			rtrMonster = new Goblin();
			break;
		}
		case(MonsterType::en_Orc):
		{
			rtrMonster = new Goblin();
			break;
		}
		case(MonsterType::en_Troll):
		{
			rtrMonster = new Goblin();
			break;
		}
	}


	/// ���� ���� Ŭ���� ���ۼ����� �ӽ� ���� ����
	return rtrMonster;
}

BossMonster* GameManager::generateBossMonster(int _level)
{
	return nullptr;
}

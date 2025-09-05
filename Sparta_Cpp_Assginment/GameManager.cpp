#include "GameManager.h"
#include "Item.h"
#include "HealthPotion.h"
using namespace std;
GameManager::GameManager()
{
	player1 = new Character();
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
	cout << "hello" << endl;
	Item* item;
	//item("stone", 50, true);
	item = new HealthPotion("healthPotion", 5, 10);
	item->use(player1);

	cout << "-------------------" << endl;
	static vector<Item> itemlist;
	itemlist.push_back(*item);
	itemlist.push_back(HealthPotion("hell", 10, 5));
	cout << itemlist[0].getName() << endl;
	auto temp = itemlist[1];
	cout << temp.getAmount() << endl;
	cout << "-------------------" << endl;

	cout << item->getDescription() << endl;
	battle(player1);
	
}

void GameManager::battle(Character* _player)
{
	Battle battle;
	// Monster* monster = generateMonster(_player->getLevel());
	Monster* monster = generateMonster(1); // getLevel() �Լ��� ��� �ӽ÷� 1�� ����
	battle.startBattle(_player, monster);

}

void GameManager::vistShop(Character* _player)
{
}

void GameManager::displayInventory(Character* _player)
{
}

Monster* GameManager::generateMonster(int _level)
{
	/// ���� ���� Ŭ���� ���ۼ����� �ӽ� ���� ����
	Goblin* rtrMonster = new Goblin();
	return rtrMonster;
}

BossMonster* GameManager::generateBossMonster(int _level)
{
	return nullptr;
}

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

// 25.09.04. 이무표
// Log를 찍어보며 디버깅할 것이 있다면 이곳에 추가해서 확인하세요
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
	Monster* monster = generateMonster(1); // getLevel() 함수가 없어서 임시로 1로 설정
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
	/// 아직 몬스터 클래스 미작성으로 임시 몬스터 리턴
	Goblin* rtrMonster = new Goblin();
	return rtrMonster;
}

BossMonster* GameManager::generateBossMonster(int _level)
{
	return nullptr;
}

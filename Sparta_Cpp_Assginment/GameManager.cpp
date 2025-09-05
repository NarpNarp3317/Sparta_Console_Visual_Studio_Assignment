#include "GameManager.h"


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
	battle(player1);
}

void GameManager::battle(Character* _player)
{
	Battle battle;
	// Monster* monster = generateMonster(_player->getLevel());
	Monster* monster = generateMonster(1); // getLevel() 함수가 없어서 임시로 1로 설정
	battle.startBattle(_player);

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

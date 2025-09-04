#include "GameManager.h"

GameManager::GameManager()
{
	player1 = new Player();
}
GameManager::~GameManager()
{
	player1 = nullptr;
	delete player1;
}

void GameManager::StartGame()
{

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

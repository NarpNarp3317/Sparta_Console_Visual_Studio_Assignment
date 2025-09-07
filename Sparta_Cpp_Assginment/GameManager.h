#pragma once
#include <iostream>
#include <random>
#include "Character.h"
#include "Player.h"
#include "Battle.h"
#include "Monster.h"
#include "BossMonster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"

using namespace std;

enum MonsterType
{
	en_Gobling,
	en_Orc,
	en_Troll,
	LAST_SIZE
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void StartGame();

private : // 함수
	void battle(Character* _player);
	void vistShop(Character* _player);
	void visitLounge(Character* _player);

	void startMenu();
	void loadPlayer();
	void makePlayer();

private: // 변수
	Character* player1;
};


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
#include "Shop.h"
#include "SaveLoadManager.h"

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

public : // �Լ�
	void battle(Character* _player);
	void vistShop(Character* _player);
	void visitLounge(Character* _player);

	void startMenu();
	void savePlayer();
	bool loadPlayer();
	bool deletePlayer();
	void makePlayer(string _name);
	void loadPlayer();
	void makePlayer();

	// �Է� ó�� ���� Ȯ��
	// 2025.09.08 ������ �߰�
	bool inputCheck();

	Character* getPlayer() { return this->player1; }

private: // ����
	Character* player1;
	Shop* nowShop;
	SaveLoadManager* saveManager;
};


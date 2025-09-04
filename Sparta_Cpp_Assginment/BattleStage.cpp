#include "BattleStage.h"
#include "Item.h"
#include "Goblin.h"
#include <random>

BattleStage::BattleStage()
{
	//임시 코드
	rewardExp = 50;
	rewardGold = 15;

	random_device rd;

	mt19937 gen(rd());

	uniform_int_distribution<int> dis(2, 3);

	int randomVal = dis(gen);

	for (int i = 0; i < randomVal; i++)
	{
		monsterList.push_back(new Goblin());
	}
}

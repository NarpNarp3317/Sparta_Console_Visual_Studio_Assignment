#include "BattleStage.h"
#include "Item.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include <random>

BattleStage::BattleStage()
{
	//ÀÓ½Ã ÄÚµå
	rewardExp = 50;
	rewardGold = 15;
}

Monster* BattleStage::getMonster(int index)
{
	if (index >= monsterList.size())
	{
		return nullptr;
	}

	return monsterList[index];
}

void BattleStage::removeMonsterList()
{
	for (int i = 0; i < monsterList.size(); i++)
	{
		delete monsterList[i];
		monsterList[i] = nullptr;
	}
}

 

int BattleStage::getRewardGold() const
{
	return rewardGold;
}

int BattleStage::getRewardExp() const
{
	return rewardExp;
}



void BattleStage::randomMonsterAdded(const int& playerLevel)
{
	//·£´ý 2~3
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(2, 3);

	int randomVal = dis(gen);

	for (int i = 0; i < randomVal; i++)
	{
		monsterList.push_back(randomMonster(playerLevel));
	}
}

Monster* BattleStage::randomMonster(const int& playerLevel)
{
	//·£´ý 0~2
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 2);

	int value = dis(gen);

	switch (value)
	{
	case 0:
		return new Orc();
	case 1:
		return new Goblin();
	case 2:
		return new Troll();
	default:
		return nullptr;
	}
}



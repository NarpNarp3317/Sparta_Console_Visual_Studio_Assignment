#include <random>
#include "BattleStage.h"
#include "Item.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "BossMonster.h"

BattleStage::BattleStage()
{
	rewardExp = 0;
	rewardGold = 0;
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
	if (playerLevel >= 10)
	{
		monsterList.push_back(new BossMonster(randomValue(playerLevel * 30, playerLevel * 40), randomValue(playerLevel * 7.5f, playerLevel * 15)));
		return;
	}
	//랜덤 1~3
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 3);

	int randomVal = dis(gen);

	for (int i = 0; i < randomVal; i++)
	{
		monsterList.push_back(randomMonster(playerLevel));
	}
}


/// <summary>
/// 범위 안에서 랜덤값 리턴
/// </summary>
/// <param name="minValue">최소값</param>
/// <param name="maxValue">최대값</param>
/// <returns></returns>
int BattleStage::randomValue(const int& minValue, const int& maxValue)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(minValue, maxValue);

	return dis(gen);
}



Monster* BattleStage::randomMonster(const int& playerLevel)
{
	//랜덤 0~2
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 2);

	int value = dis(gen);

	int healthRange[2] = { playerLevel * 20, playerLevel * 30 };
	int atkRange[2] = { playerLevel * 5, playerLevel * 10 };

	switch (value)
	{
	case 0:
		return new Orc(randomValue(healthRange[0], healthRange[1]), randomValue(atkRange[0], atkRange[1]));
	case 1:
		return new Goblin(randomValue(healthRange[0], healthRange[1]), randomValue(atkRange[0], atkRange[1]));
	case 2:
		return new Troll(randomValue(healthRange[0], healthRange[1]), randomValue(atkRange[0], atkRange[1]));
	default:
		return nullptr;
	}
}



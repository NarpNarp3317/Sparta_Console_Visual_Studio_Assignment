#pragma once
#include <vector>
#include <memory>

class Monster;
class Item;

using namespace std;

class BattleStage
{
public:
	BattleStage();
	Monster* getMonster(int index);
	void removeMonsterList();
	void randomMonsterAdded(const int& playerLevel);
	int randomItem();

	//getter
	int getRewardGold() const;
	int getRewardExp() const;


private:
	Monster* randomMonster(const int& playerLevel);
	int randomValue(const int& minValue, const int& maxValue);

private:
	vector<Monster*> monsterList;

	int rewardGold;
	int rewardExp;
};


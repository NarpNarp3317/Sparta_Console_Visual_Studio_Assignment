#pragma once
#include <vector>
#include <memory>

class Monster;

using namespace std;

class BattleStage
{
public:
	BattleStage();
	Monster* getMonster(int index);
	void removeMonsterList();
	void randomMonsterAdded(const int& playerLevel);


	//getter
	int getRewardGold() const;
	int getRewardExp() const;


private:
	Monster* randomMonster(const int& playerLevel);

private:
	vector<Monster*> monsterList;
	int rewardGold;
	int rewardExp;
};


#pragma once
#include <vector>
#include <memory>

class Monster;

using namespace std;

class BattleStage
{
public:
	BattleStage();
	unique_ptr<Monster> getMonster();
	void removeMonster();
	void randomMonsterAdded(const int& playerLevel);


	//getter
	int getRewardGold() const;
	int getRewardExp() const;


private:
	unique_ptr<Monster> randomMonster(const int& playerLevel);

private:
	vector<unique_ptr<Monster>> monsterList;
	int rewardGold;
	int rewardExp;
};


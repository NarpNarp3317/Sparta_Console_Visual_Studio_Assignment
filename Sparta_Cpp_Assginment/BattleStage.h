#pragma once

#include <vector>
class Monster;

using namespace std;

class BattleStage
{
public:
	BattleStage();


private:
	vector<Monster*> monsterList;
	int rewardGold;
	int rewardExp;
};


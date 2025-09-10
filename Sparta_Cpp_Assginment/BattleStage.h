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
	int getMonsterSize();


private:
	Monster* randomMonster(const int& playerLevel);
	int randomValue(const int& minValue, const int& maxValue);

private:
	vector<Monster*> monsterList;
};


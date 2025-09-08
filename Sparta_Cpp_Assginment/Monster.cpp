#include "Monster.h"
#include <random>

//이 생성자 임시로 사용
Monster::Monster()
{
    this->maxHealth = 100;
    this->attack = 10;
    health = maxHealth;
}

Monster::Monster(int maxHealth, int attack)
{
    this->maxHealth = maxHealth;
    this->attack = attack;
    health = maxHealth;
}

void Monster::takeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        health = 0;
    }
}



string Monster::getName()
{
    return name;
}

int Monster::getHealth()
{
    return health;
}

int Monster::getAttack()
{
    return attack;
}

int Monster::getRewardExp()
{
    return rw_exp;
}

int Monster::getRewardGold()
{
    return rw_gold;
}


int Monster::randomItem()
{
    if (randomValue(1, 100) <= 30) //30퍼의 확률
    {
        int randomVal = randomValue(0, 1);
        return randomVal;
    }

    return -1;
}

int Monster::randomValue(const int& minValue, const int& maxValue)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(minValue, maxValue);

    return dis(gen);
}

Monster::~Monster()
{

}

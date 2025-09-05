#include "Monster.h"

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

Monster::~Monster()
{

}

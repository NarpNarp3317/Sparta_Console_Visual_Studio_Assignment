#include "Battle.h"
#include "Character.h"
#include "Monster.h"

Battle::Battle()
{

}
Battle::~Battle()
{

}

// 25.09.04. �̹�ǥ
// �̰��� ���� ������ �ۼ��ϸ� �� �� �����ϴ�.
// �ʿ��� �Լ��� ������ �ִٸ� �ش� Battle Ŭ������ �߰��ؼ� ����ϸ� �˴ϴ�.
void Battle::startBattle(Character* _player, Monster* _monster)
{

	cout << _player << " vs " << _monster << endl;
	cout << "Battle Start!" << endl;

}
#include "Battle.h"
#include "Character.h"
#include "Monster.h"

Battle::Battle()
{

}
Battle::~Battle()
{

}

// 25.09.04. 이무표
// 이곳에 전투 로직을 작성하면 될 것 같습니다.
// 필요한 함수나 변수가 있다면 해당 Battle 클래스에 추가해서 사용하면 됩니다.
void Battle::startBattle(Character* _player, Monster* _monster)
{

	cout << _player << " vs " << _monster << endl;
	cout << "Battle Start!" << endl;

}
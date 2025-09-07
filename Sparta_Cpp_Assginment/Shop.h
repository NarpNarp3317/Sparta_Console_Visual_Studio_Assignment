#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"
#include "Player.h"

class Shop
{
private:
	std::vector<Item*> items; //판매할 아이템 목록

public:
	Shop();
	~Shop();

	void ShowItems();                  //아이템 목록 출력
	void BuyItem(Character& player);   //아이템 구매
	void SellItem(Character& player);  //아이템 판매
};


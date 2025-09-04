#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"
#include "Player.h"

class Shop
{
private:
	std::vector<Item*> items; //�Ǹ��� ������ ���

public:
	Shop();
	~Shop();

	void ShowItems();                  //������ ��� ���
	void BuyItem(Player& player);   //������ ����
	void SellItem(Player& player);  //������ �Ǹ�
};


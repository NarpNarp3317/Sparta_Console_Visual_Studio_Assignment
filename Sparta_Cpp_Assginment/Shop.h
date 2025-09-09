#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"

class Shop {
private:
    std::vector<Item*> items;   // ������ �ǸŵǴ� ������ ���

public:
    Shop();
    ~Shop();

    void ShowItems();
    void BuyItem(Character& player);   // ���� �ܼ� �Է� ���
    void SellItem(Character& player);  // ���� �ܼ� �Է� ���

    // ��ư �̺�Ʈ��
    void BuyItemByIndex(Character& player, int index);
    void SellItemByIndex(Character& player, int index);
};

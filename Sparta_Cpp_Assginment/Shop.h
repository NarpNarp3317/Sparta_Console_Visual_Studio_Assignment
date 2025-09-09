#pragma once
#include <vector>
#include "Item.h"
#include "Character.h"

class Shop {
private:
    std::vector<Item*> items;   // 상점에 판매되는 아이템 목록

public:
    Shop();
    ~Shop();

    void ShowItems();
    void BuyItem(Character& player);   // 기존 콘솔 입력 방식
    void SellItem(Character& player);  // 기존 콘솔 입력 방식

    // 버튼 이벤트용
    void BuyItemByIndex(Character& player, int index);
    void SellItemByIndex(Character& player, int index);
};

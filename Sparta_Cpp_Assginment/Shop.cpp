#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>
#include "Player.h"

Shop::Shop() {
    // 판매할 아이템 등록
    items.push_back(new HealthPotion("Health Potion", 10, 50));   // +50 HP, 10 Gold
    items.push_back(new AttackBoost("Attack Boost", 15, 10));     // +10 ATK, 15 Gold
}

Shop::~Shop() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}

void Shop::ShowItems() {
    std::cout << "\n[Shop Items]\n";
    for (size_t i = 0; i < items.size(); i++) {
        std::cout << i + 1 << ". " << items[i]->getName()
            << " - " << items[i]->getPrice() << " Gold\n";
    }
}

void Shop::BuyItem(Player& player) {
    ShowItems();
    std::cout << "Select the item number to purchase (0: Cancel): ";
    int choice;
    std::cin >> choice;

    if (choice <= 0 || choice > (int)items.size()) return;

    Item* selected = items[choice - 1];
    if (player.SpendGold(selected->getPrice())) {
        // 아이템 복사본을 인벤토리에 추가
        if (selected->getName().find("Health") != std::string::npos) {
            player.AddItem(new HealthPotion("Health Potion", 10, 50));
        }
        else if (selected->getName().find("Attack") != std::string::npos) {
            player.AddItem(new AttackBoost("Attack Boost", 15, 10));
        }
        std::cout << selected->getName() << " has been purchased!\n";
    }
    else {
        std::cout << "Not enough gold!\n";
    }
}

void Shop::SellItem(Player& player) {
    player.ShowInventory();
    std::cout << "Select the item number to sell (0: Cancel): ";
    int choice;
    std::cin >> choice;

    if (choice <= 0 || choice > (int)player.GetInventorySize()) return;

    Item* sellingItem = player.GetItem(choice - 1);
    int sellPrice = (sellingItem->getPrice() * 60) / 100;

    player.AddGold(sellPrice);
    player.RemoveItem(choice - 1);

    std::cout << sellingItem->getName() << " has been sold! +"
        << sellPrice << " Gold\n";
}

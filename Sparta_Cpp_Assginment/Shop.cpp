#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include "Bomb.h"
#include <iostream>
#include "Character.h"

Shop::Shop() {
    // 판매할 아이템 등록
    items.push_back(new HealthPotion("Health Potion", 10, 50));   // +50 HP, 10 Gold
    items.push_back(new AttackBoost("Attack Boost", 15, 10));     // +10 ATK, 15 Gold
    items.push_back(new Weapon("Iron Sword", 30, 15, true, false, "A balanced weapon.")); // 무기
    items.push_back(new Bomb("Bomb", 20, 30, true, true, "Deals 30 damage to an enemy.")); // 폭탄 (20 Gold, 30 Damage)
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

void Shop::BuyItem(Character& player) {
    ShowItems();
    std::cout << "Select the item number to purchase (0: Cancel): ";
    int choice;
    std::cin >> choice;

    if (choice <= 0 || choice > (int)items.size()) return;

    Item* selected = items[choice - 1];
    if (player.SpendGold(selected->getPrice())) {
        // 아이템 복사본을 인벤토리에 추가
        if (selected->getName().find("Health") != std::string::npos) {
            player.addItem(new HealthPotion("Health Potion", 10, 50));
        }
        else if (selected->getName().find("Attack") != std::string::npos) {
            player.addItem(new AttackBoost("Attack Boost", 15, 10));
        }
        else if (selected->getName().find("Sword") != std::string::npos) {
            player.addItem(new Weapon("Iron Sword", 30, 15, true, false, "A balanced weapon."));
        }
        else if (selected->getName().find("Bomb") != std::string::npos) {
            player.addItem(new Bomb("Bomb", 20, 30, true, true, "Deals 30 damage to an enemy."));
        }

        std::cout << selected->getName() << " has been purchased!\n";
        std::cout << "Current Gold: " << player.getGold() << "\n"; // 보유 골드 표시
    }
    else {
        std::cout << "Not enough gold!\n";
    }
}

void Shop::SellItem(Character& player) {
    player.printInventory();
    std::cout << "Select the item number to sell (0: Cancel): ";
    int choice;
    std::cin >> choice;

    if (choice <= 0 || choice > (int)player.getInventorySize()) return;

    Item* sellingItem = player.GetItem(choice - 1);
    int sellPrice = (sellingItem->getPrice() * 60) / 100;

    player.AddGold(sellPrice);
    player.RemoveItem(choice - 1);

    std::cout << sellingItem->getName() << " has been sold! +"
        << sellPrice << " Gold\n";
    std::cout << "Current Gold: " << player.getGold() << "\n"; // 보유 골드 표시
}

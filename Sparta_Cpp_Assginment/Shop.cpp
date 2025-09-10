#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "Weapon.h"
#include <iostream>
#include "Character.h"
#include "StringUpdater.h"

StringUpdater stringUpdater({ 10, 12 });

Shop::Shop() {
    // 판매할 아이템 등록
    items.push_back(new HealthPotion("Health Potion", 10, 50));   // +50 HP, 10 Gold
    items.push_back(new AttackBoost("Attack Boost", 15, 10));     // +10 ATK, 15 Gold
    items.push_back(new Weapon("Iron Sword", 30, 15, true, true, "A balanced weapon.")); // 무기
    //items.push_back(new Bomb("Bomb", 20, 30, true, true, "Deals 30 damage to an enemy.")); // 폭탄
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
        if (selected->getName().find("Health") != std::string::npos) {
            player.addItem(new HealthPotion(ITEM_HPPOTION, 10, 50));
        }
        else if (selected->getName().find("Attack") != std::string::npos) {
            player.addItem(new AttackBoost(ITEM_ATKBOOST, 15, 10));
        }
        else if (selected->getName().find("Sword") != std::string::npos) {
            player.addItem(new Weapon("Iron Sword", 30, 15, true, true, "A balanced weapon."));
        }
        //std::cout << selected->getName() << " has been purchased!\n";
        //std::cout << "Current Gold: " << player.getGold() << "\n";
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
    std::cout << "Current Gold: " << player.getGold() << "\n";
}

void Shop::BuyItemByIndex(Character& player, int index) {
    if (index < 0 || index >= (int)items.size()) return;
    map<string, int> player_invmap = player.getItemCountMap();

    Item* selected = items[index];
   
    if (player.getGold() > selected->getPrice()) {
        if (selected->getName().find("Health") != std::string::npos) {
           if (player_invmap[ITEM_HPPOTION] > 8) {
              std::cout << "You have exceeded the maximum number of items.\n";
              return;
           }
            player.addItem(new HealthPotion(ITEM_HPPOTION, 10, 50));
            player.SpendGold(selected->getPrice());
        }
        else if (selected->getName().find("Attack") != std::string::npos) {
           if (player_invmap[ITEM_ATKBOOST] > 8) {
              std::cout << "You have exceeded the maximum number of items.\n";
              return;
           }
            player.addItem(new AttackBoost(ITEM_ATKBOOST, 15, 10));
            player.SpendGold(selected->getPrice());
        }
        else if (selected->getName().find("Sword") != std::string::npos) {
           if (player_invmap["Iron Sword"] > 8) {
              std::cout << "You have exceeded the maximum number of items.\n";
              return;
           }
            player.addItem(new Weapon("Iron Sword", 30, 15, true, true, "A balanced weapon."));
            player.SpendGold(selected->getPrice());
        }

  
        string str = selected->getName() + " has been purchased! ";
        str += "Current Gold: " + player.getGold();
        stringUpdater.StringUpdate(str);
    }
    else {

        string str = "Not enough gold!";
        stringUpdater.StringUpdate(str);
        //std::cout << "Not enough gold!\n";
    }
}

void Shop::SellItemByIndex(Character& player, int index) {
    if (index < 0 || index >= (int)player.getInventorySize()) return;

    Item* sellingItem = player.GetItem(index);
    int sellPrice = (sellingItem->getPrice() * 60) / 100;

    player.AddGold(sellPrice);
    player.RemoveItem(index);

    string str = sellingItem->getName() + " has been sold! + " + to_string(sellPrice) + " Gold";
    str += "Current Gold: " + player.getGold();
    stringUpdater.StringUpdate(str);


   /* std::cout << sellingItem->getName() << " has been sold! +"
        << sellPrice << " Gold\n";
    std::cout << "Current Gold: " << player.getGold() << "\n";*/
}

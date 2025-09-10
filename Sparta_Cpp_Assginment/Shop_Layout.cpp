#include "Shop_Layout.h"
#include "SceneMaker.h"
#include "Shop.h"
#include "Character.h"
#include "Layout.h"
#include "Logger.h"   

extern Shop shop;
extern Character player;

Shop_Layout::Shop_Layout()
    : Layout()
{
    // ====== Health Potion ======
    Button* buyHpBtn = new Button(0, 1, "BuyHPPotion",
        center_center, { 20,5 }, { -25,-10 }, double_line, White, Gray);
    buyHpBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(player, 0);
        Logger::getInstance().myLog("플레이어가 Health Potion 구매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(buyHpBtn);

    Button* sellHpBtn = new Button(0, 1, "SellHPPotion",
        center_center, { 20,5 }, { 25,-10 }, double_line, White, Gray);
    sellHpBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(player, 0);
        Logger::getInstance().myLog("플레이어가 Health Potion 판매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(sellHpBtn);

    // ====== Attack Boost ======
    Button* buyAtkBtn = new Button(0, 1, "BuyATKBoost",
        center_center, { 20,5 }, { -25,0 }, double_line, White, Gray);
    buyAtkBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(player, 1);
        Logger::getInstance().myLog("플레이어가 Attack Boost 구매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(buyAtkBtn);

    Button* sellAtkBtn = new Button(0, 1, "SellATKBoost",
        center_center, { 20,5 }, { 25,0 }, double_line, White, Gray);
    sellAtkBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(player, 1);
        Logger::getInstance().myLog("플레이어가 Attack Boost 판매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(sellAtkBtn);

    // ====== Iron Sword ======
    Button* buySwordBtn = new Button(0, 1, "BuyIronSword",
        center_center, { 20,5 }, { -25,10 }, double_line, White, Gray);
    buySwordBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(player, 2);
        Logger::getInstance().myLog("플레이어가 Iron Sword 구매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(buySwordBtn);

    Button* sellSwordBtn = new Button(0, 1, "SellIronSword",
        center_center, { 20,5 }, { 25,10 }, double_line, White, Gray);
    sellSwordBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(player, 2);
        Logger::getInstance().myLog("플레이어가 Iron Sword 판매, 현재 Gold: " + std::to_string(player.getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(player.getGold()) },
            left_center, White, Black);
        });
    AddButton(sellSwordBtn);

    // ====== Exit Shop ======
    Button* exitBtn = new Button(0, 1, "Exit Shop",
        center_center, { 20,5 }, { 0,25 }, double_line, White, Gray);
    exitBtn->SetOnLeftPressed([] {
        Logger::getInstance().myLog("플레이어가 상점을 나감");
        // TODO: 라운지 화면으로 전환
        });
    AddButton(exitBtn);

    // ====== Gold Scene 초기화 ======
    SceneMaker::PrepareCanvas(&goldScene, { 20,3 });
    SceneMaker::FillColor(&goldScene, { 20,3 }, White, Black);
    SceneMaker::AddTexts(&goldScene, { 20,3 }, { 1,1 },
        { "Gold: " + std::to_string(player.getGold()) },
        left_center, White, Black);
}

#include "Shop_Layout.h"
#include "SceneMaker.h"
#include "Shop.h"
#include "Character.h"
#include "Layout.h"
#include "Logger.h"   

extern Shop shop;
// extern Character player;

Shop_Layout::Shop_Layout(ConsoleManager* _cm, Lounge_Layout* _lounge, Character* _Player)
    : Layout(),
    _C_manager(_cm),
    loungeLayout(_lounge),
    nowPlayer(_Player)
{
    // ====== Health Potion ======
    Button* buyHpBtn = new Button(0, 1, "Buy_HP_Potion",
        center_center, { 20,5 }, { -25,-10 }, double_line, White, Gray);
    buyHpBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(*nowPlayer, 0);
        Logger::getInstance().myLog("플레이어가 Health Potion 구매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(buyHpBtn);

    Button* sellHpBtn = new Button(0, 1, "Sell_HP_Potion",
        center_center, { 20,5 }, { 25,-10 }, double_line, White, Gray);
    sellHpBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(*nowPlayer, 0);
        Logger::getInstance().myLog("플레이어가 Health Potion 판매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(sellHpBtn);

    // ====== Attack Boost ======
    Button* buyAtkBtn = new Button(0, 1, "Buy_ATK_Boost",
        center_center, { 20,5 }, { -25,0 }, double_line, White, Gray);
    buyAtkBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(*nowPlayer, 1);
        Logger::getInstance().myLog("플레이어가 Attack Boost 구매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(buyAtkBtn);

    Button* sellAtkBtn = new Button(0, 1, "Sell_ATK_Boost",
        center_center, { 20,5 }, { 25,0 }, double_line, White, Gray);
    sellAtkBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(*nowPlayer, 1);
        Logger::getInstance().myLog("플레이어가 Attack Boost 판매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(sellAtkBtn);

    // ====== Iron Sword ======
    Button* buySwordBtn = new Button(0, 1, "Buy_Iron_Sword",
        center_center, { 20,5 }, { -25,10 }, double_line, White, Gray);
    buySwordBtn->SetOnLeftPressed([this] {
        shop.BuyItemByIndex(*nowPlayer, 2);
        Logger::getInstance().myLog("플레이어가 Iron Sword 구매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(buySwordBtn);

    Button* sellSwordBtn = new Button(0, 1, "Sell_Iron_Sword",
        center_center, { 20,5 }, { 25,10 }, double_line, White, Gray);
    sellSwordBtn->SetOnLeftPressed([this] {
        shop.SellItemByIndex(*nowPlayer, 2);
        Logger::getInstance().myLog("플레이어가 Iron Sword 판매, 현재 Gold: " + std::to_string(nowPlayer->getGold()));
        SceneMaker::AddTexts(&this->goldScene, { 20,3 }, { 1,1 },
            { "Gold: " + std::to_string(nowPlayer->getGold()) },
            left_center, White, Black);
        });
    AddButton(sellSwordBtn);

    // ====== Exit Shop ======
    Button* exitBtn = new Button(0, 1, "Exit_Shop",
        center_center, { 20,5 }, { 0,25 }, double_line, White, Gray);
    exitBtn->SetOnLeftPressed([this] {
        Logger::getInstance().myLog("플레이어가 상점을 나감");
        // TODO: 라운지 화면으로 전환
        this->loungeLayout->updateStatus();
        this->_C_manager->SetCurrentDisplay(this->loungeLayout->getLayout());
        });

    AddButton(exitBtn);

    // ====== Gold Scene 초기화 ======
    SceneMaker::PrepareCanvas(&goldScene, { 20,3 });
    SceneMaker::FillColor(&goldScene, { 20,3 }, White, Black);
    SceneMaker::AddTexts(&goldScene, { 20,3 }, { 1,1 },
        { "Gold: " + std::to_string(nowPlayer->getGold()) },
        left_center, White, Black);
}
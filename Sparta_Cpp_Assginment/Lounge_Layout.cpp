#include "Lounge_Layout.h"
#include "BattleStage_Layout.h"
#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include <iostream>
#include "Logger.h"
#include "Shop_Layout.h"

// 생성자: 필요한 모든 화면(Layout) 객체를 만들고 초기 화면을 설정합니다.
Lounge_Layout::Lounge_Layout(ConsoleManager* _C_manager, StringUpdater* su, GameManager* _GM)
    : _C_manager(_C_manager),
    GM_Logic(_GM),
    _su(su),
    mainLounge_Layout(new Layout()),
    myShopLayout(new Shop_Layout(_C_manager, mainLounge_Layout, _GM->getPlayer())),
    inventory_Layout(new Inventory_Layout(_GM->getPlayer(), mainLounge_Layout, _C_manager, su))

{
    this->makeLayout();
    Logger::getInstance().myLog("PLAYER NAME : " + GM_Logic->getPlayer()->getName());
    inventory_Layout->InventoryDisplay();
}

Lounge_Layout::~Lounge_Layout()
{
    delete mainLounge_Layout;
    delete myShopLayout;

    myShopLayout = nullptr;
    mainLounge_Layout = nullptr;
}

void Lounge_Layout::setLayout(Layout* _Lay)
{
    this->mainLounge_Layout = _Lay;
}
Layout* Lounge_Layout::getLayout()
{
    return this->mainLounge_Layout;
}

void Lounge_Layout::makeLayout()
{
    // 메인 메뉴에 들어갈 버튼들을 만듭니다.
    Button* btn_goBattle = new Button(0, 2, "<<BATTLE>>", center_center, { 20, 5 }, { 0, 4 }, single_line, White, Gray);
    Button* btn_goShop = new Button(0, 2, "<<Visit_Shop>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* btn_showPlayerStatus = new Button(0, 2, "<<Status>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);
    Button* btn_showInventory = new Button(0, 2, "<<Inventory>>", center_center, { 20, 5 }, { 0, 19 }, double_line, White, Gray);
    Button* btn_save = new Button(0, 2, "<<SAVE>>", center_center, { 20, 5 }, { 0, 24 }, double_line, White, Gray);
    Button* btn_exit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 29 }, double_line, White, Gray);

    // 람다 함수를 통해 버튼 클릭 시 화면을 전환하는 로직을 추가합니다.
    btn_goBattle->SetOnLeftPressed([this]() {
        this->onBtnBattle();
        });

    btn_goShop->SetOnLeftPressed([this]() {
        this->onBtnShop();
        });

    btn_showPlayerStatus->SetOnLeftPressed([this]() {
        this->onBtnPlayerStatus();
        });

    btn_showInventory->SetOnLeftPressed([this]() {
        this->onBtnInventory();
        });

    btn_save->SetOnLeftPressed([this]() {
        this->onBtnSave();
        });

    btn_exit->SetOnLeftPressed([this]() {
        this->_C_manager->gameExit();
        });

    // 버튼들을 메인 메뉴 화면에 추가합니다.
    mainLounge_Layout->AddButton(btn_goBattle);
    mainLounge_Layout->AddButton(btn_goShop);
    mainLounge_Layout->AddButton(btn_showPlayerStatus);
    mainLounge_Layout->AddButton(btn_showInventory);
    mainLounge_Layout->AddButton(btn_save);
    mainLounge_Layout->AddButton(btn_exit);

    // 프로그램의 시작 화면을 메인 메뉴로 설정합니다.
    // _C_manager->SetCurrentDisplay(mainLounge_Layout);
}

/// <summary>
/// 일단 레이아웃에 진입하는 것까지만 연결해 주시면
/// 해당 기능 종료 후 라운지로 돌아오는 것은 제가 작업하겠습니다.
/// 25.09.10. 이무표
/// </summary>
void Lounge_Layout::onBtnBattle()
{
    //// 이곳에서 Battle 레이아웃을 불러오면 됩니다
    // 예시
    // this->_C_manager->SetCurrentDisplay(여기에 레이아웃 포인터);
    BattleStage_Layout* battleStage_layout = new BattleStage_Layout();
    this->_C_manager->SetCurrentDisplay(battleStage_layout);
    battleStage_layout->BattleStartSetup(GM_Logic->getPlayer());
}

void Lounge_Layout::onBtnShop()
{
    this->_C_manager->SetCurrentDisplay(myShopLayout);
    //// 이곳에서 샵 레이아웃을 불러오면 됩니다
    // 예시
    // this->_C_manager->SetCurrentDisplay(여기에 레이아웃 포인터);
}

void Lounge_Layout::onBtnPlayerStatus()
{
    //// 이곳에서 스테이터스 레이아웃을 불러오면 됩니다
    // 예시
    // this->_C_manager->SetCurrentDisplay(여기에 레이아웃 포인터);
}

void Lounge_Layout::onBtnInventory()
{
    //// 이곳에서 인벤토리 레이아웃을 불러오면 됩니다
    // 예시
    // this->_C_manager->SetCurrentDisplay(여기에 레이아웃 포인터);
   this->_C_manager->SetCurrentDisplay(inventory_Layout);

}

void Lounge_Layout::onBtnSave()
{
    GM_Logic->savePlayer();
}

void Lounge_Layout::onBtnEXIT()
{
    exit(0);
}
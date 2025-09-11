#include "Lounge_Layout.h"
#include "BattleStage_Layout.h"
#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include <iostream>
#include "Logger.h"
#include "Shop_Layout.h"
#include "Weapon.h"


// 생성자: 필요한 모든 화면(Layout) 객체를 만들고 초기 화면을 설정합니다.
Lounge_Layout::Lounge_Layout(ConsoleManager* _C_manager, StringUpdater* su, GameManager* _GM)
    : _C_manager(_C_manager),
    GM_Logic(_GM),
    _su(su),
    mainLounge_Layout(new Layout()),
    myShopLayout(new Shop_Layout(_C_manager, this, _GM->getPlayer())),
    inventory_Layout(nullptr),
    mainBattleStage_layout(nullptr) // 배틀스테이지는 매번 새로 생성
{
    this->makeLayout();
    this->makeStatus();
    Logger::getInstance().myLog("PLAYER NAME : " + GM_Logic->getPlayer()->getName());
    // inventory_Layout->InventoryDisplay();
}

Lounge_Layout::~Lounge_Layout()
{
    delete mainLounge_Layout;
    delete myShopLayout;

    myShopLayout = nullptr;
    mainLounge_Layout = nullptr;

    // 버튼은 Layout 부모 클래스 소멸자에서 소멸시켜서 굳이 소멸시키지 않는다
}

void Lounge_Layout::createSysMsg(string _msg)
{
    lbl_sysMsg = new Button(0, 2, _msg, center_center, { 80, 5 }, { 0, -20 }, no_line, White, Gray);
    mainLounge_Layout->AddButton(lbl_sysMsg);
}

void Lounge_Layout::deleteSysMsg()
{
    mainLounge_Layout->RemoveButton(lbl_sysMsg);
}

void Lounge_Layout::setLayout(Layout* _Lay)
{
    this->mainLounge_Layout = _Lay;
}
Layout* Lounge_Layout::getLayout()
{
    return this->mainLounge_Layout;
}

void Lounge_Layout::makeStatus()
{
    // 스트링먼저
    string str_Lv = "LV_:_" + to_string(GM_Logic->getPlayer()->getLevel());
    string strHP = "HP_:_" + to_string(GM_Logic->getPlayer()->getHealth()) + "/" + to_string(GM_Logic->getPlayer()->getMaxHealth());
    string strATK = "ATK_:_";
    if (GM_Logic->getPlayer()->getEquippedWeapon() != nullptr)
    {
        LOG("YES WEAPON");
        strATK += to_string(GM_Logic->getPlayer()->getBaseAttack()) + "(" + to_string(GM_Logic->getPlayer()->getEquippedWeapon()->getDamage()) + ")";
    }
    else
    {
        LOG("NO WEAPON");
        strATK += to_string(GM_Logic->getPlayer()->getBaseAttack());
    }
    string str_exp = "EXP_:_" + to_string(GM_Logic->getPlayer()->getExperience());
    string str_gold = "GOLD_:_" + to_string(GM_Logic->getPlayer()->getGold());

    // 버튼 초기화
    lbl_name = new Button(0, 2, GM_Logic->getPlayer()->getName(), center_center, { 50, 3 }, { 0, -15 }, double_line, White, Gray);
    lbl_Lv = new Button(0, 2, str_Lv, center_center, { 50, 3 }, { 0, -13 }, double_line, White, Gray);
    lbl_hp = new Button(0, 2, strHP, center_center, { 50, 3 }, { 0, -11 }, double_line, White, Gray);
    lbl_atk = new Button(0, 2, strATK, center_center, { 50, 3 }, { 0, -9 }, double_line, White, Gray);
    lbl_exp = new Button(0, 2, str_exp, center_center, { 50, 3 }, { 0, -7 }, double_line, White, Gray);
    lbl_gold = new Button(0, 2, str_gold, center_center, { 50, 3 }, { 0, -5 }, double_line, White, Gray);

    // 스탯 표기 먼저
    mainLounge_Layout->AddButton(lbl_name);
    mainLounge_Layout->AddButton(lbl_Lv);
    mainLounge_Layout->AddButton(lbl_hp);
    mainLounge_Layout->AddButton(lbl_atk);
    mainLounge_Layout->AddButton(lbl_exp);
    mainLounge_Layout->AddButton(lbl_gold);
}
void Lounge_Layout::updateStatus()
{
    // 업데이트 된다 = 라운지에 돌아왔다 = 플레이어 체력 회복
    GM_Logic->getPlayer()->setHealth(GM_Logic->getPlayer()->getMaxHealth());

    LOG("MAX : ");
    LOG(to_string(GM_Logic->getPlayer()->getMaxHealth()));
    LOG("NOW : ");
    LOG(to_string(GM_Logic->getPlayer()->getHealth()));
    string str_Lv = "LV_:_" + to_string(GM_Logic->getPlayer()->getLevel());
    string strHP = "HP_:_" + to_string(GM_Logic->getPlayer()->getHealth()) + "/" + to_string(GM_Logic->getPlayer()->getMaxHealth());
    string strATK = "ATK_:_";
    if (GM_Logic->getPlayer()->getEquippedWeapon() != nullptr)
    {
        LOG("YES WEAPON");
        strATK += to_string(GM_Logic->getPlayer()->getBaseAttack()) + "(" + to_string(GM_Logic->getPlayer()->getEquippedWeapon()->getDamage()) + ")";
    }
    else
    {
        LOG("NO WEAPON");
        strATK += to_string(GM_Logic->getPlayer()->getBaseAttack());
    }
    string str_exp = "EXP_:_" + to_string(GM_Logic->getPlayer()->getExperience());
    string str_gold = "GOLD_:_" + to_string(GM_Logic->getPlayer()->getGold());

    lbl_Lv->SetLable(str_Lv);
    lbl_hp->SetLable(strHP);
    lbl_atk->SetLable(strATK);
    lbl_exp->SetLable(str_exp);
    lbl_gold->SetLable(str_gold);

    lbl_Lv->UpdateButton();
    lbl_hp->UpdateButton();
    lbl_atk->UpdateButton();
    lbl_exp->UpdateButton();
    lbl_gold->UpdateButton();
}


void Lounge_Layout::makeLayout()
{
    Button* btn_goBattle = new Button(0, 2, "<<BATTLE>>", center_center, { 20, 5 }, { 0, 4 }, single_line, White, Gray);
    Button* btn_goShop = new Button(0, 2, "<<Visit_Shop>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* btn_showInventory = new Button(0, 2, "<<Inventory>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);
    Button* btn_save = new Button(0, 2, "<<SAVE>>", center_center, { 20, 5 }, { 0, 19 }, double_line, White, Gray);
    Button* btn_exit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 24 }, double_line, White, Gray);

    // 람다 함수를 통해 버튼 클릭 시 화면을 전환하는 로직을 추가합니다.
    btn_goBattle->SetOnLeftPressed([this]() {
        this->onBtnBattle();
        deleteSysMsg();
        });

    btn_goShop->SetOnLeftPressed([this]() {
        this->onBtnShop();
        deleteSysMsg();
        });

    btn_showInventory->SetOnLeftPressed([this]() {
        this->onBtnInventory();
        deleteSysMsg();
        });

    btn_save->SetOnLeftPressed([this]() {
        this->onBtnSave();
        });

    btn_exit->SetOnLeftPressed([this]() {
        deleteSysMsg();
        this->_C_manager->gameExit();
        });

    // 버튼
    mainLounge_Layout->AddButton(btn_goBattle);
    mainLounge_Layout->AddButton(btn_goShop);
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

    mainBattleStage_layout = new BattleStage_Layout(GM_Logic->getPlayer(), this, _C_manager, _su);
    mainBattleStage_layout->BattleStartSetup(GM_Logic->getPlayer());
    this->_C_manager->SetCurrentDisplay(mainBattleStage_layout);

}

void Lounge_Layout::onBtnShop()
{
    myShopLayout->updateGoldBtn();
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
   // inventory_Layout->ButtonRefresh();
   if (inventory_Layout != nullptr)
   {
        delete inventory_Layout;
        inventory_Layout = nullptr;
   }
   inventory_Layout = new Inventory_Layout(GM_Logic->getPlayer(), this, _C_manager, _su);
   inventory_Layout->InventoryDisplay();
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
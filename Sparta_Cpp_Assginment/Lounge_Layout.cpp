#include "Lounge_Layout.h"
#include "BattleStage_Layout.h"
#include "Inventory_Layout.h"
#include "SceneMaker.h"
#include <iostream>
#include "Logger.h"
#include "Shop_Layout.h"

// ������: �ʿ��� ��� ȭ��(Layout) ��ü�� ����� �ʱ� ȭ���� �����մϴ�.
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
    // ���� �޴��� �� ��ư���� ����ϴ�.
    Button* btn_goBattle = new Button(0, 2, "<<BATTLE>>", center_center, { 20, 5 }, { 0, 4 }, single_line, White, Gray);
    Button* btn_goShop = new Button(0, 2, "<<Visit_Shop>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* btn_showPlayerStatus = new Button(0, 2, "<<Status>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);
    Button* btn_showInventory = new Button(0, 2, "<<Inventory>>", center_center, { 20, 5 }, { 0, 19 }, double_line, White, Gray);
    Button* btn_save = new Button(0, 2, "<<SAVE>>", center_center, { 20, 5 }, { 0, 24 }, double_line, White, Gray);
    Button* btn_exit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 29 }, double_line, White, Gray);

    // ���� �Լ��� ���� ��ư Ŭ�� �� ȭ���� ��ȯ�ϴ� ������ �߰��մϴ�.
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

    // ��ư���� ���� �޴� ȭ�鿡 �߰��մϴ�.
    mainLounge_Layout->AddButton(btn_goBattle);
    mainLounge_Layout->AddButton(btn_goShop);
    mainLounge_Layout->AddButton(btn_showPlayerStatus);
    mainLounge_Layout->AddButton(btn_showInventory);
    mainLounge_Layout->AddButton(btn_save);
    mainLounge_Layout->AddButton(btn_exit);

    // ���α׷��� ���� ȭ���� ���� �޴��� �����մϴ�.
    // _C_manager->SetCurrentDisplay(mainLounge_Layout);
}

/// <summary>
/// �ϴ� ���̾ƿ��� �����ϴ� �ͱ����� ������ �ֽø�
/// �ش� ��� ���� �� ������� ���ƿ��� ���� ���� �۾��ϰڽ��ϴ�.
/// 25.09.10. �̹�ǥ
/// </summary>
void Lounge_Layout::onBtnBattle()
{
    //// �̰����� Battle ���̾ƿ��� �ҷ����� �˴ϴ�
    // ����
    // this->_C_manager->SetCurrentDisplay(���⿡ ���̾ƿ� ������);
    BattleStage_Layout* battleStage_layout = new BattleStage_Layout();
    this->_C_manager->SetCurrentDisplay(battleStage_layout);
    battleStage_layout->BattleStartSetup(GM_Logic->getPlayer());
}

void Lounge_Layout::onBtnShop()
{
    this->_C_manager->SetCurrentDisplay(myShopLayout);
    //// �̰����� �� ���̾ƿ��� �ҷ����� �˴ϴ�
    // ����
    // this->_C_manager->SetCurrentDisplay(���⿡ ���̾ƿ� ������);
}

void Lounge_Layout::onBtnPlayerStatus()
{
    //// �̰����� �������ͽ� ���̾ƿ��� �ҷ����� �˴ϴ�
    // ����
    // this->_C_manager->SetCurrentDisplay(���⿡ ���̾ƿ� ������);
}

void Lounge_Layout::onBtnInventory()
{
    //// �̰����� �κ��丮 ���̾ƿ��� �ҷ����� �˴ϴ�
    // ����
    // this->_C_manager->SetCurrentDisplay(���⿡ ���̾ƿ� ������);
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
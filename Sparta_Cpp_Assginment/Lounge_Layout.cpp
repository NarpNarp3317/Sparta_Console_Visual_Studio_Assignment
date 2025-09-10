#include "Lounge_Layout.h"
#include "SceneMaker.h"
#include <iostream>
#include "Logger.h"

// 생성자: 필요한 모든 화면(Layout) 객체를 만들고 초기 화면을 설정합니다.
Lounge_Layout::Lounge_Layout(ConsoleManager* _C_manager, StringUpdater* su, GameManager* _GM)
    : _C_manager(_C_manager),
    GM_Logic(_GM),
    _su(su),
    mainLounge_Layout(new Layout())
{
    this->makeLayout();
    Logger::getInstance().myLog(GM_Logic->getPlayer()->getName());
}

Lounge_Layout::~Lounge_Layout()
{
    delete mainLounge_Layout;


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
    Button* btn_goShop = new Button(0, 2, "<<Visit Shop>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* btn_showPlayerStatus = new Button(0, 2, "<<Status>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);
    Button* btn_showInventory = new Button(0, 2, "<<Inventory>>", center_center, { 20, 5 }, { 0, 19 }, double_line, White, Gray);
    Button* btn_save = new Button(0, 2, "<<SAVE>>", center_center, { 20, 5 }, { 0, 24 }, double_line, White, Gray);
    Button* btn_exit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 29 }, double_line, White, Gray);

    // 람다 함수를 통해 버튼 클릭 시 화면을 전환하는 로직을 추가합니다.
    btn_goBattle->SetOnLeftPressed([this]() {
        this->_su->StringUpdate("This is Main Lounge");
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

void Lounge_Layout::onBtnBattle()
{

}

void Lounge_Layout::onBtnShop()
{

}

void Lounge_Layout::onBtnPlayerStatus()
{

}

void Lounge_Layout::onBtnInventory()
{

}

void Lounge_Layout::onBtnSave()
{
    GM_Logic->savePlayer();
}

void Lounge_Layout::onBtnEXIT()
{
    exit(0);
}
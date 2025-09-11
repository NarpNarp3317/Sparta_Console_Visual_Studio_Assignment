#pragma once
#include "Layout.h"
#include "SceneMaker.h"
#include "ConsoleManager.h"
#include "Character.h"
#include "Lounge_Layout.h"

class Shop_Layout : public Layout {
public:
    Shop_Layout(ConsoleManager* _cm, Lounge_Layout* _lounge, Character* _player);
    ~Shop_Layout() = default;
    void setLoungeLayout(Lounge_Layout* _Lay) { this->loungeLayout = _Lay; }
    Layout* getLoungeLayout() { return this->loungeLayout->getLayout(); }

private:
    ConsoleManager* _C_manager;
    Character* nowPlayer;
    Scene goldScene;   // °ñµå Ç¥½Ã¿ë Scene
    Lounge_Layout* loungeLayout;

    Button* goldBtn = nullptr;
    void updateGoldBtn();
};

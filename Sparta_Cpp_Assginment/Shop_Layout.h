#pragma once
#include "Layout.h"
#include "SceneMaker.h"
#include "ConsoleManager.h"
#include "Character.h"

class Shop_Layout : public Layout {
public:
    Shop_Layout(ConsoleManager* _cm, Layout* _lounge, Character* _player);
    ~Shop_Layout() = default;
    void setLoungeLayout(Layout* _Lay) { this->loungeLayout = _Lay; }
    Layout* getLoungeLayout() { return this->loungeLayout; }

private:
    ConsoleManager* _C_manager;
    Character* nowPlayer;
    Scene goldScene;   // °ñµå Ç¥½Ã¿ë Scene
    Layout* loungeLayout;
};

#pragma once
#include "Layout.h"
#include "SceneMaker.h"

class Shop_Layout : public Layout {
public:
    Shop_Layout();
    ~Shop_Layout() = default;

private:
    Scene goldScene;   // ��� ǥ�ÿ� Scene
};

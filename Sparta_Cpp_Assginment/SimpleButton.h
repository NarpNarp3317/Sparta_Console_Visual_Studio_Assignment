#pragma once
#include "BaseFrame.h"
#include <functional>
#include "interaction_Component.h" 

using namespace std;

class SimpleButton : public BaseFrame, public Interactable// using minimum
{
public:

    SimpleButton(int buttonID, int priority, PivotPoiontLocation anchor, COORD width, Text_Color text_color, Text_Color bg_color);

protected:
    function<void()> _onLeftPressed;
    function<void()> _onLeftReleased;

public:
    bool IsDetected(COORD mouse_coord) override;

    void SetOnLeftPressed(function<void()> function);
    void OnLeftPressed() override;

    void SetOnLeftReleased(function<void()> function);
    void OnLeftReleased() override;

    void FillAlpha();

    vector<vector<bool>> _collision_mask;
};
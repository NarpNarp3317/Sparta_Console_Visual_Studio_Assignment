#pragma once
#include "Button.h"

// no default texture, just simple plain tirgger box
class SimpleButton : public Button
{
public:
    SimpleButton(int buttonID, int priority, PivotPoiontLocation anchor_type, COORD width)
        : Button(buttonID, priority, anchor_type, width, { 0,0 }, FrameStyle::no_line, Text_Color::Black, Text_Color::Black)
    {
        // Don't call GenerateDefaultButtonSet() here
        FillAlpha();
    }
};
#pragma once
#include "SimpleButton.h"

class ExitButton :public SimpleButton
{
public:
    ExitButton(int buttonID, int priority, PivotPoiontLocation anchor, COORD width, Text_Color text_color, Text_Color bg_color);
        
};
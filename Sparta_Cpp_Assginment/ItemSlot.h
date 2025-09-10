#pragma once
#include "Button.h"

class ItemSlot :public Button
{
public:
	ItemSlot(int button_ID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color);// 
	
};
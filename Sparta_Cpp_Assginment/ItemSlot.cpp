#include "ItemSlot.h"

ItemSlot::ItemSlot(int button_ID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color)
	:Button( button_ID, priority, lable, anchor_type, width,offset,frame_style, text_color, bg_color)
{
}

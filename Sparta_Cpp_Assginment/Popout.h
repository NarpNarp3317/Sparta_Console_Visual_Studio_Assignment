#pragma once
#include "BaseFrame.h"
#include "interaction_Component.h"
#include "Button.h"
#include "Enum_MouseInput.h"


class Popout :public BaseFrame
{
public:
	Popout(int priority, PivotPoiontLocation anchor_type, COORD witdh, FrameStyle frame_style, Text_Color text, Text_Color bg);

private:
	std::vector<Button*> _buttons;

public:

	void P_AddButton(Button* button);

	void P_OnMouseEvent(COORD mouse_coord, Enum_MouseInput input_type);

};
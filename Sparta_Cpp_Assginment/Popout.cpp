#include "Popout.h"


Popout::Popout(int priority, PivotPoiontLocation anchor_type, COORD witdh, FrameStyle frame_style, Text_Color text, Text_Color bg):BaseFrame (0, anchor_type, witdh, frame_style,text, bg )
{
}

void Popout::P_AddButton(Button* button)
{
	_buttons.push_back(button);
}

void Popout::P_OnMouseEvent(COORD mouse_coord, Enum_MouseInput input_type)// only for the buttons
{
	for (Button* button : _buttons)
	{
		if (button->IsDetected(mouse_coord))
		{
			switch (input_type)
			{
			case Left_click: button->OnLeftClick(); break;
			case Right_click: button->OnRightClick(); break;
			case Hovering: button->OnHovering_started(); break;
			default: break;
			}
		}
		else button->OnHovering_ended();
	}
}
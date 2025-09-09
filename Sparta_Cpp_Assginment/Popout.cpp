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
	for (Interactable* interactable : _buttons)
	{
		if (interactable->IsDetected(mouse_coord))
		{
			switch (input_type)
			{
			case Left_Pressed: interactable->OnLeftPressed(); break;
			case Left_Released:interactable->OnLeftReleased(); break;
			case Right_Pressed: interactable->OnRightPressed(); break;
			case Right_Released: interactable->OnRightReleased(); break;
			default: break;
			}
		}
		else interactable->OnHovering_ended();
	}
}
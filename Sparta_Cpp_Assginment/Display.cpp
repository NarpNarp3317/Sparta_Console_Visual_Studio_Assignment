#include "Display.h"

Display::Display() :BaseFrame(1, top_left, GetScreenLimits(), {0,0})
{
}

void Display::AddButton(Button* new_button)
{
	_buttons.push_back(new_button);
}

vector<Button*> Display::GetInteractables()
{
	return _buttons;
}

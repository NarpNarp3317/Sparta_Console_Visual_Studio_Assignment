#include "Layout.h"

Layout::Layout() :BaseFrame(1, top_left, GetScreenLimits(), {0,0})
{
}

void Layout::AddButton(Button* new_button)
{
	_buttons.push_back(new_button);
}

vector<Button*> Layout::GetInteractables()
{
	return _buttons;
}

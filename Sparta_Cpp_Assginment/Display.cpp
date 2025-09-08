#include "Display.h"

Display::Display(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset) :BaseFrame(priority, anchor_type, width, offset)
{
	GenerateFrame();
}

void Display::AddButton(Button* new_button)
{
	_buttons.push_back(new_button);
}

vector<Button*> Display::GetInteractables()
{
	return _buttons;
}

#pragma once
#include "BaseFrame.h"
#include "Button.h"
#include <vector>

//Display is a class that store UI elements

class Display :public BaseFrame
{
public:
	Display();


private:
	vector<Button*> _buttons;// containter for buttonPtrs

public:
	void AddButton(Button* new_button);

	vector<Button*> GetInteractables();
};
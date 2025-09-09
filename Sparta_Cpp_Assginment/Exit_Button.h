#pragma once
#include "Button.h"

class ExitButton :public Button
{
public:
	ExitButton();

private: 
	Scene _default_Scene;
	Scene _pressed_Scene;
};
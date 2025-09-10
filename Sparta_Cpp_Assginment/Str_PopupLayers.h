#pragma once
#include <map>
#include "Scene.h"
#include "Button.h"

using namespace std;

struct PopupLayer
{
	PopupType layer_type;
	Scene texture;
	vector<Button*> buttons;// the required buttons
	vector<string> texts;// for update texts

	//for custom only
	vector<function<void()>> custom_functions;


	//function<void()> onPopup;//entering the popout
	//function<void()> onPopout;// leaving the popout
};
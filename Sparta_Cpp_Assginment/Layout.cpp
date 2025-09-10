#include "Layout.h"
#include "SceneMaker.h"

Layout::Layout() :BaseFrame(1, top_left, GetScreenLimits(), { 0,0 }, double_line, White, Black)// generate the layout the size of the max screen size
{
	SceneMaker::AddFrame_withChosenColor(&_texture, _width_XY, double_line, _text_color);// outer frame

}

Layout::~Layout()
{
	// 25.09.10. 이무표
	// button이 포인터로 되어 있어 메모리 해제 추가
	for (Button* btn : _buttons) {
		delete btn;
	}
	_buttons.clear();
}

void Layout::AddButton(Button* new_button)
{
	_buttons.push_back(new_button);
}

void Layout::RemoveButton(Button* new_button)
{
	vector<Button*>::iterator it = find(_buttons.begin(), _buttons.end(), new_button);

	if (it != _buttons.end())
	{
		_buttons.erase(it);
	}
}

vector<Button*> Layout::GetInteractables()
{
	return _buttons;
}

void Layout::RemoveButton(Button* new_button)
{
	vector<Button*>::iterator it = find(_buttons.begin(), _buttons.end(), new_button);
	if (it != _buttons.end())
	{
		_buttons.erase(it);
	}
}

/*
void Layout::AddScene(Scene* scene)
{
	_Scenes.push_back(scene);
}

vector<Scene*> Layout::GetScenes()
{
	return _Scenes;
}
*/

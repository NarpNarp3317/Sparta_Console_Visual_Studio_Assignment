#include "Layout.h"
#include "SceneMaker.h"

Layout::Layout() :BaseFrame(1, top_left, GetScreenLimits(), {0,0},White,Black)// generate the layout the size of the max screen size
{
	SceneMaker::AddFrame_withChosenColor(&_texture, _width_XY, double_line, _text_color);// outer frame

}

void Layout::AddButton(Button* new_button)
{
	_buttons.push_back(new_button);
}

vector<Button*> Layout::GetInteractables()
{
	return _buttons;
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

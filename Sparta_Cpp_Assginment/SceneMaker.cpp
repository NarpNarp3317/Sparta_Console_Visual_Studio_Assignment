#include "SceneMaker.h"
#include "Text_Align.h"
using namespace std;

SceneMaker::SceneMaker():_width_XY{0,0}, _scene{nullptr}
{
}

void SceneMaker::ImportScene(Scene* scene, COORD width_XY, COORD offset)
{
	// reset the previous 
	_scene = nullptr;
	_width_XY = { 0,0 };

	if (scene == nullptr) return;

	_scene = scene;
	_width_XY = width_XY;

	COORD imported_wdith;
	imported_wdith.Y = _scene->_alpha.size();// get the y size and get the y length
	imported_wdith.X = _scene->_alpha[0].size();// this is only if the scene is rectangular shaped 

	vector<vector<T_Pixel>> newFrame(_width_XY.Y, vector<T_Pixel>(_width_XY.X, T_Pixel{ 7, ' ' }));
	vector<vector<bool>> newAlpha(_width_XY.Y, vector<bool>(_width_XY.X, false));

	for (int y = 0; y < imported_wdith.Y; y++)
	{
		for (int x = 0; x < imported_wdith.X; x++)
		{
			int newX = x + offset.X;
			int newY = y + offset.Y;

			if (newX < 0 || newX >= _width_XY.X) continue;//out of range conditions
			if (newY < 0 || newY >= _width_XY.Y) continue;

			newFrame[newY][newX] = _scene->_T_Pixel_frame[y][x];
			newAlpha[newY][newX] = _scene->_alpha[y][x];
		}
	}
	_scene->_T_Pixel_frame = newFrame;
	_scene->_alpha = newAlpha;
}

void SceneMaker::AddTexts(std::vector<std::string> Texts, PivotPoiontLocation anchor_type, COORD offset, int color)
{
	
	if (_scene == nullptr || Texts.empty()) return;

	int lineCount = (Texts.size() < _width_XY.Y - 2) ? Texts.size() : _width_XY.Y - 2;// chose smallest one// -2 for margine by frame

	vector<std::string> valid_lines(lineCount);//clamp the strings from texts vector
	
	Text_Align t_align;// the alignment of text by anchor type

	switch (anchor_type)
	{
	case top_left:
		t_align = left;
		break;
	case top_center:
		t_align = center;
		break;
	case top_right:
		t_align = right;
		break;
	case left_center:
		t_align = left;
		break;
	case center_center:
		t_align = center;
		break;
	case right_center:
		t_align = right;
		break;
	case bottom_left:
		t_align = left;
		break;
	case bottom_center:
		t_align = center;
		break;
	case bottom_right:
		t_align = right;
		break;
	default:
		//error! invalid enum detected!
		break;
	}
}


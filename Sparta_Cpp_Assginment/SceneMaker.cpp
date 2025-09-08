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

void SceneMaker::AddTexts(std::vector<std::string> Texts, PivotPoiontLocation anchor_type, COORD offset,short int color)
{
	
	if (_scene == nullptr || Texts.empty()) return;

	int max_LineCount = _width_XY.Y;
	int lineCount = (Texts.size() < _width_XY.Y - 2) ? Texts.size() : _width_XY.Y - 2;// chose smallest one// -2 for margine by frame

	for (int i = 0; i < lineCount; i++)
	{
		string current_Line = Texts[i];
		int current_Line_Length = (current_Line.length() < _width_XY.X-2) ? current_Line.length() : _width_XY.X-2;// same here

		//Text_Align t_align;// the alignment of text by anchor type ---> not necessary

		COORD string_start = { 0, 0 };// the starting point of string based on the anchor(alignment)


		//======== X coord =======//
		if (anchor_type == top_left || anchor_type == left_center || anchor_type == bottom_left)
		{
			string_start.X = 1;
		}
		else if (anchor_type == top_center || anchor_type == center_center || anchor_type == bottom_center)
		{
			string_start.X = (_width_XY.X - current_Line_Length) / 2;
		}
		else if (anchor_type == top_right || anchor_type == right_center || anchor_type == bottom_right)
		{
			string_start.X = _width_XY.X - current_Line_Length;
		}
		else
		{
			//error, invalid enum
		}

		//======== Y coord =======//
		if (anchor_type == top_left || anchor_type == top_center || anchor_type == top_right)
		{
			string_start.Y = 1;
		}
		else if (anchor_type == left_center || anchor_type == center_center || anchor_type == right_center)
		{
			string_start.Y = (_width_XY.Y - lineCount) / 2+i;
		}
		else if (anchor_type == bottom_left || anchor_type == bottom_center || anchor_type == bottom_right)
		{
			string_start.Y = _width_XY.Y - lineCount + i;
		}
		else
		{
			//error, invalid enum
		}

		//=== apply offset ===//
		string_start.X += offset.X;
		string_start.Y += offset.Y;

		for (int c = 0; c < current_Line_Length; c++)
		{
			int c_coordX = string_start.X + c;
			int  c_coordY = string_start.Y;


			if (c_coordX < 0 || c_coordX >= _width_XY.X || c_coordY < 0 || c_coordY >= _width_XY.Y) continue;

			_scene->_T_Pixel_frame[c_coordY][c_coordX] = T_Pixel{ color ,static_cast<unsigned char>(current_Line[c]) };
			_scene->_alpha[c_coordY][c_coordX] = true;
		}
	}
}

void SceneMaker::AddFrame(FrameStyle style, short int color)
{

}
void SceneMaker::ChangeColor(short int color)
{
	_color = color;
}

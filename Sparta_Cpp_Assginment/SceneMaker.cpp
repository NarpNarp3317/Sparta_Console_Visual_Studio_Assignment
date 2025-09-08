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

void SceneMaker::AddTexts(std::vector<std::string> Texts, PivotPoiontLocation anchor_type, COORD offset, Text_Color text_color, Text_Color background_color)
{
	short int color = FindColorCode(text_color, background_color);

	if (_scene == nullptr) return;
	if (Texts.empty()) return;

	int max_LineCount = _width_XY.Y-2;
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
			string_start.X = 1+((_width_XY.X - current_Line_Length) / 2);
		}
		else if (anchor_type == top_right || anchor_type == right_center || anchor_type == bottom_right)
		{
			string_start.X = _width_XY.X - current_Line_Length-1;
		}
		else
		{
			//error, invalid enum
		}

		//======== Y coord =======//
		if (anchor_type == top_left || anchor_type == top_center || anchor_type == top_right)
		{
			string_start.Y = 1+i;
		}
		else if (anchor_type == left_center || anchor_type == center_center || anchor_type == right_center)
		{
			string_start.Y = ((_width_XY.Y - lineCount) / 2)+i+1;
		}
		else if (anchor_type == bottom_left || anchor_type == bottom_center || anchor_type == bottom_right)
		{
			string_start.Y = _width_XY.Y - lineCount + i-1;
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


			if (c_coordX < 1 || c_coordX >= _width_XY.X-1 || c_coordY < 1 || c_coordY >= _width_XY.Y-1) continue;

			_scene->_T_Pixel_frame[c_coordY][c_coordX] = T_Pixel{ color ,static_cast<unsigned char>(current_Line[c]) };
			_scene->_alpha[c_coordY][c_coordX] = true;
		}
	}
}

void SceneMaker::AddFrame(FrameStyle style, Text_Color text_color, Text_Color background_color)
{
	short int color = FindColorCode(text_color, background_color);

	if (_scene == nullptr) return;
	if (style == no_line) return;// do not allocate any thing when ther is no frame

	//==== frame style ====//

	unsigned char top_left, top_right, bottom_left, bottom_right, horizontal, vertical;// for frame

	switch (style)
	{
	case double_line:
		top_left = 201; top_right = 187; bottom_left = 200; bottom_right = 188; horizontal = 205; vertical = 186;
		break;

	case single_line:
		top_left = 218; top_right = 191; bottom_left = 192; bottom_right = 217; horizontal = 196; vertical = 179;
		break;

	default:
		//error no enum detected
		break;
	}

	short int x = _width_XY.X;
	short int y = _width_XY.Y;

	if (x < 2 || y < 2)// the frame needs to be at least bigger than 2*2 so that corner can be made
	{
		return;
	}
	// change corner chars

	_scene->_T_Pixel_frame[0][0] = T_Pixel{ color,top_left };
	_scene->_alpha[0][0] = true;

	_scene->_T_Pixel_frame[0][x - 1] = T_Pixel{ color,top_right };
	_scene->_alpha[0][x - 1] = true;

	_scene->_T_Pixel_frame[y - 1][0] = T_Pixel{ color,bottom_left };
	_scene->_alpha[y - 1][0] = true;

	_scene->_T_Pixel_frame[y - 1][x - 1] = T_Pixel{ color,bottom_right };
	_scene->_alpha[y - 1][x - 1] = true;


	for (int i = 1; i < x - 1; i++)//same here/alsnkljkb adsljkbf saflsdjkbsdfhajk fuck
	{
		_scene->_T_Pixel_frame[0][i] = T_Pixel{ color,  horizontal };
		_scene->_alpha[0][i] = true;
		_scene->_T_Pixel_frame[y - 1][i] = T_Pixel{ color,  horizontal };
		_scene->_alpha[y - 1][i] = true;
	}
	for (int j = 1; j < y - 1; j++)//same here
	{
		_scene->_T_Pixel_frame[j][0] = T_Pixel{ color,  vertical };
		_scene->_alpha[j][0] = true;
		_scene->_T_Pixel_frame[j][x - 1] = T_Pixel{ color,  vertical };
		_scene->_alpha[j][x - 1] = true;
	}
}
void SceneMaker::ChangeWholeColor(Text_Color text_color, Text_Color background_color)
{
	short int color = FindColorCode(text_color, background_color);

	if (_scene == nullptr) return;

	for (int y = 0; y < _width_XY.Y; y++)
	{
		for (int x=0; x < _width_XY.X; x++)
		{
			if (_scene->_alpha[y][x])
			{
				_scene->_T_Pixel_frame[y][x].color = color;
			}
		}
	}
}

void SceneMaker::InvertWholeColor()
{
	if (_scene == nullptr) return;

	for (int y = 0; y < _width_XY.Y; y++)
	{
		for (int x=0; x < _width_XY.X; x++)
		{
			if (_scene->_alpha[y][x])
			{
				short int color = _scene->_T_Pixel_frame[y][x].color;// find the color;

				short int text = color % 16;// get the rest of division(text)X coord
				short int bg = (color- text) / 16;// Background Y coord

				_scene->_T_Pixel_frame[y][x].color = (text * 16) + bg;

				//_scene->_T_Pixel_frame[y][x].color = FindColorCode(bg, text);// this is using enum for color

			}
		}
	}
}

short int FindColorCode(Text_Color text_color, Text_Color background_color)
{
	return ((background_color*16) + text_color);// use color chart (X--> 0~15(16)colors, same for Y)--> overflow--> set color
}
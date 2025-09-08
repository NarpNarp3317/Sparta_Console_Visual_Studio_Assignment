#include "BaseFrame.h"

// for static data, _screen_Limit;// definition for static member of this class

COORD BaseFrame::_screen_Limit = { 0,0 };// for default
//without this, unresolved external symbol "private: static struct _COORD BaseFrame::_screen_Limit" (?_screen_Limit@BaseFrame@@0U_COORD@@A)

BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_Style)
	:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ offset },
	_frame_color{ 7 },//default white
	print_start_coord{ 0,0 },
	_frame_style{ frame_Style },
	_texture{}// blank frame at begining

{
	GenerateFrame();
}
BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_Style)
	:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ 0, 0 },
	_frame_color{ 7 },//default white
	print_start_coord{ 0,0 },
	_frame_style{ frame_Style },
	_texture{}// blank frame at begining
{
	GenerateFrame();
}
BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset)// offset 과 함께 생성
	:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ offset },
	_frame_color{7},//default white
	print_start_coord{0,0},
	_frame_style{ double_line },
	_texture{}

{
	GenerateFrame();
}


BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width)//offset 없이 생성
:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ 0,0 },//default offset == no offset
	print_start_coord{ 0,0 },
	_frame_style{ double_line },
	_frame_color{ 7 },//default white
	_texture{}
{
	GenerateFrame();
}

void BaseFrame::CalculatePrintStartCoord(PivotPoiontLocation anchor_type)
{
	short int lX = _screen_Limit.X;
	short int lY = _screen_Limit.Y;
	short int wX = _width_XY.X;
	short int wY = _width_XY.Y;

	switch (anchor_type)
	{
	case top_left:
		print_start_coord = { 0,0 };
		break;
	case top_center:
		print_start_coord = { static_cast<short>((lX - wX) / 2),0 };
		break;
	case top_right:
		print_start_coord = { static_cast<short>(lX - wX),0 };
		break;
	case left_center:
		print_start_coord = { 0,static_cast<short>((lY - wY)/2) };
		break;
	case center_center:
		print_start_coord = { static_cast<short>((lX - wX) / 2),static_cast<short>((lY - wY) / 2) };
		break;
	case right_center:
		print_start_coord = { static_cast<short>(lX - wX),static_cast<short>((lY - wY) / 2) };
		break;
	case bottom_left:
		print_start_coord = { 0,static_cast<short>(lY - wY) };
		break;
	case bottom_center:
		print_start_coord = { static_cast<short>((lX - wX) / 2),static_cast<short>(lY - wY) };
		break;
	case bottom_right:
		print_start_coord = { static_cast<short>(lX - wX),static_cast<short>(lY - wY) };
		break;
	default:
		//error, invalid enum detected, do not add more pivotpoint
		break;
	}
	//add offset

	print_start_coord.X += _offset.X;
	print_start_coord.Y += _offset.Y;

	// clamp the size of the frame based on console screen limit// dont create frame? or cut out the frame?
	// decided by isclampable//-----> *** not done yey ***

	//if (print_start_coord.X < 0 || print_start_coord.Y < 0)// min<0
	//{
	//	//error, the frame will be out of the console window.
	//	print_start_coord = { 0,0 };
	//}
	//else if(print_start_coord.X+ _width_XY.X> _screen_Limit.X|| print_start_coord.Y + _width_XY.Y > _screen_Limit.Y)//max>>limit
	//{
	//	//error, the frame will be out of the console window.
	//	print_start_coord = { 0,0 };
	//}

	// Clamp min
	if (print_start_coord.X < 0) print_start_coord.X = 0;
	if (print_start_coord.Y < 0) print_start_coord.Y = 0;

	// Clamp max (so frame fits on screen)
	if (print_start_coord.X + _width_XY.X > _screen_Limit.X)
		print_start_coord.X = _screen_Limit.X - _width_XY.X;

	if (print_start_coord.Y + _width_XY.Y > _screen_Limit.Y)
		print_start_coord.Y = _screen_Limit.Y - _width_XY.Y;

	//return _print_start;

}

COORD BaseFrame::GetPrintStartCoord()
{
	return print_start_coord;
}

COORD BaseFrame::GetWidthXY()
{
	return _width_XY;
}


Scene* BaseFrame::GetTexturePtr()
{
	return &_texture;
}


void BaseFrame::SetPicture(const Scene& new_picture)// trim out where frames are( if its no visible frame, just as size of frame)
{
	_texture = new_picture;
}

bool BaseFrame::IsOuterFrameVisible()
{
	return _frame_style != no_line;// if style is noline--> return false, else, return true
}


void BaseFrame::GenerateFrame()
{

	CalculatePrintStartCoord(_anchor_type);// calculate the print start first

	//==== frame style ====//

	unsigned char top_left, top_right, bottom_left, bottom_right, horizontal, vertical;// for frame

	switch (_frame_style)
	{
	case double_line:
		top_left = 201; top_right = 187; bottom_left = 200; bottom_right = 188; horizontal = 205; vertical = 186;
		break;

	case single_line:
		top_left = 218; top_right = 191; bottom_left = 192; bottom_right = 217; horizontal = 196; vertical = 179;
		break;

	case no_line:// nothing
		top_left = ' '; top_right = ' '; bottom_left = ' '; bottom_right = ' '; horizontal = ' '; vertical = ' ';
		break;

	default:
		printf("Error, invalid frame style detected");
		//error no enum detected
		break;
	}


	short int x = _width_XY.X;
	short int y = _width_XY.Y;
	//short int off_x = _offset.X;//---> offset is for print start position
	//short int off_y = _offset.Y;// same as x

	if (x < 2 || y < 2)// the frame needs to be at least bigger than 2*2 so that corner can be made
	{
		//print error code
		return;
	}

	_texture._T_Pixel_frame.assign(y, vector< T_Pixel>(x, T_Pixel{ _frame_color ,' ' }));// fill the fame with blank first.
	_texture._alpha.assign(y, vector<bool>(x, false));// fill alpha mask with false(empty)

	if (_frame_style == no_line) return;// do not allocate any thing when ther is no frame

	// change corner chars

	_texture._T_Pixel_frame[0][0] = T_Pixel{ _frame_color,top_left };
	_texture._alpha[0][0] = true;

	_texture._T_Pixel_frame[0][x - 1] = T_Pixel{ _frame_color,top_right };
	_texture._alpha[0][x - 1] = true;

	_texture._T_Pixel_frame[y - 1][0] = T_Pixel{ _frame_color,bottom_left};
	_texture._alpha[y - 1][0] = true;

	_texture._T_Pixel_frame[y - 1][x - 1] = T_Pixel{ _frame_color,bottom_right };
	_texture._alpha[y - 1][x - 1] = true;


	for (int i = 1; i < x - 1; i++)//same here/alsnkljkb adsljkbf saflsdjkbsdfhajk fuck
	{
		_texture._T_Pixel_frame[0][i] = T_Pixel{ _frame_color,  horizontal };
		_texture._alpha[0][i] = true;
		_texture._T_Pixel_frame[y - 1][i] = T_Pixel{ _frame_color,  horizontal };
		_texture._alpha[y - 1][i] = true;
	}
	for (int j = 1; j < y - 1; j++)//same here
	{
		_texture._T_Pixel_frame[j][0] = T_Pixel{ _frame_color,  vertical };
		_texture._alpha[j][0] = true;
		_texture._T_Pixel_frame[j][x - 1] = T_Pixel{ _frame_color,  vertical };
		_texture._alpha[j][x - 1] = true;
	}
}
/*
void BaseFrame::FillAlpha()
{
	short int x = _width_XY.X;
	short int y = _width_XY.Y;

	_frame._alpha.assign(y, vector<bool>(x, true));// just assign it all true
}
*/ //----> its not for base frame, but for buttons, and not alphamask from scene, but for collision mask

void BaseFrame::SetScreenLimits(COORD limit_area)
{
	_screen_Limit = limit_area;
}

COORD BaseFrame::GetScreenLimits()
{
	return _screen_Limit;
}

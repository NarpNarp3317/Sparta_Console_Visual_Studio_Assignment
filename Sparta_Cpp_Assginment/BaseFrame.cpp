#include "BaseFrame.h"

// for static data, _screen_Limit;// definition for static member of this class

COORD BaseFrame::_screen_Limit = { 0,0 };// for default
//without this, unresolved external symbol "private: static struct _COORD BaseFrame::_screen_Limit" (?_screen_Limit@BaseFrame@@0U_COORD@@A)

BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset)// offset 과 함께 생성
	:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ offset },
	_frame{},// blank frame at begining
	_frame_color{7}//default white
{
	GenerateFrame();
}


BaseFrame::BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width)//offset 없이 생성
:
	_layerPriority{ priority },
	_width_XY{ width },
	_anchor_type{ anchor_type },
	_offset{ 0,0 },//default offset == no offset
	_frame{},
	_frame_color{ 7 }//default white
{
	GenerateFrame();
}

void BaseFrame::CalulatePrintStartCoord(PivotPoiontLocation anchor_type)
{
	short int lX = _screen_Limit.X;
	short int lY = _screen_Limit.Y;
	short int wX = _width_XY.X;
	short int wY = _width_XY.Y;

	switch (anchor_type)
	{
	case top_left:
		_print_start = { 0,0 };
		break;
	case top_center:
		_print_start = { static_cast<short>((lX - wX) / 2),0 };
		break;
	case top_right:
		_print_start = { static_cast<short>(lX - wX),0 };
		break;
	case left_center:
		_print_start = { 0,static_cast<short>((lY - wY)/2) };
		break;
	case center:
		_print_start = { static_cast<short>((lX - wX) / 2),static_cast<short>((lY - wY) / 2) };
		break;
	case right_center:
		_print_start = { static_cast<short>(lX - wX),static_cast<short>((lY - wY) / 2) };
		break;
	case bottom_left:
		_print_start = { 0,static_cast<short>(lY - wY) };
		break;
	case bottom_center:
		_print_start = { static_cast<short>((lX - wX) / 2),static_cast<short>(lY - wY) };
		break;
	case bottom_right:
		_print_start = { static_cast<short>(lX - wX),static_cast<short>(lY - wY) };
		break;
	default:
		//error, invalid enum detected, do not add more pivotpoint
		break;
	}
	//add offset

	_print_start.X += _offset.X;
	_print_start.Y += _offset.Y;

	// clamp the size of the frame based on console screen limit// dont create frame? or cut out the frame?
	// decided by isclampable//-----> *** not done yey ***

	if (_print_start.X < 0 || _print_start.Y < 0)// min<0
	{
		//error, the frame will be out of the console window.
		_print_start = { 0,0 };
	}
	else if(_print_start.X+ _width_XY.X> _screen_Limit.X|| _print_start.Y + _width_XY.Y > _screen_Limit.Y)//max>>limit
	{
		//error, the frame will be out of the console window.
		_print_start = { 0,0 };
	}

	//return _print_start;

}

COORD BaseFrame::GetPrintStartCoord()
{
	return _print_start;
}

COORD BaseFrame::GetWidthXY()
{
	return _width_XY;
}

const Scene& BaseFrame::GetFramePtr()
{
	return _frame;
}

void BaseFrame::GenerateFrame()
{
	short int x = _width_XY.X;
	short int y = _width_XY.Y;
	//short int off_x = _offset.X;//---> offset is for print start position
	//short int off_y = _offset.Y;// same as x

	if (x < 2 || y < 2)// the frame needs to be at least bigger than 2*2 so that corner can be made
	{
		//print error code
		return;
	}

	_frame._T_Pixel_frame.assign(y, vector< T_Pixel>(x, T_Pixel{ _frame_color ,' ' }));// fill the fame with blannk first.
	_frame._alpha.assign(y, vector<bool>(x, false));// fill alpha mask with false(empty)

	// change corner chars
	_frame._T_Pixel_frame[0][0] = T_Pixel{ _frame_color,201 };        // top-left ╔
	_frame._alpha[0][0] = true;

	_frame._T_Pixel_frame[0][x - 1] = T_Pixel{ _frame_color,187 };    // top-right ╗
	_frame._alpha[0][x - 1] = true;

	_frame._T_Pixel_frame[y - 1][0] = T_Pixel{ _frame_color,200 };    // bottom-left ╚
	_frame._alpha[y - 1][0] = true;

	_frame._T_Pixel_frame[y - 1][x - 1] = T_Pixel{ _frame_color,188 };// bottom-right ╝
	_frame._alpha[y - 1][x - 1] = true;

	// now for ║, ═
	for (int i = 1; i < x - 1; i++)//first and last on top and bottom is corners
	{
		_frame._T_Pixel_frame[0][i] = T_Pixel{ _frame_color, 205 }; // top ═
		_frame._alpha[0][i] = true;
		_frame._T_Pixel_frame[y - 1][i] = T_Pixel{ _frame_color, 205 }; // bottom ═
		_frame._alpha[y - 1][i] = true;
	}
	for (int j = 1; j < y - 1; j++)//same here
	{
		_frame._T_Pixel_frame[j][0] = T_Pixel{ _frame_color, 186 }; // left ║
		_frame._alpha[j][0] = true;
		_frame._T_Pixel_frame[j][x - 1] = T_Pixel{ _frame_color, 186 }; // right ║
		_frame._alpha[j][x - 1] = true;
	}
}

void BaseFrame::SetScreenLimits(COORD limit_area)
{
	_screen_Limit = limit_area;
}

COORD BaseFrame::GetScreenLimits()
{
	return _screen_Limit;
}

#include "Button.h"

//===================  Constructor ================//
Button::Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style)// with offset, no label
	:BaseFrame(priority, anchor_type, width, offset, frame_style),

	_buttonID{ button_id },
	_onLeftClick{nullptr},
	_onRightClick{nullptr},
	_onHovering_Started{nullptr},
	_onHovering_Ended{nullptr},
	_isOverlapping{false},// buttons never overlaps
	_lable{"Button"}
{
	FillAlpha();// so that the button can be detected not only the frame but also the inside
}

Button::Button(int buttonID, int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style)// without offset, no label
	:BaseFrame(priority, anchor_type, width, {0,0}, frame_style),

	_buttonID{ buttonID },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ "Button" }
{
	FillAlpha();
}


Button::Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style)// with offset and lable
	:BaseFrame(priority, anchor_type, width, offset, frame_style),
	_buttonID{ button_id },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ lable }
{
	FillAlpha();
}

Button::Button(int buttonID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style)// without offset, with lable
	:BaseFrame(priority, anchor_type, width, { 0,0 }, frame_style),

	_buttonID{ buttonID },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ lable }
{
	FillAlpha();
}
//-----------------------<<      MOUSE EVENTS       >>-----------------------------//

bool Button::IsDetected(COORD mouse_coord)// return bool by checking if the mouse coord is in range of button(not finding corrd for each)
{
	COORD width = GetWidthXY();
	COORD start = GetPrintStartCoord();

	// const Scene& frame = GetFramePtr();// get for read only

	const Scene* frame = GetTexturePtr();// get for read only //-->_collision_mask will be used for detection

	
	//---> find relative coord of mouse position

	COORD relative_coord = { mouse_coord.X - start.X, mouse_coord.Y - start.Y };

	if (relative_coord.X < 0 || relative_coord.Y < 0 || relative_coord.X >= width.X || relative_coord.Y >= width.Y)
		return false;


	return _collision_mask[relative_coord.Y][relative_coord.X];//return relative coord of mouse cursor and it will be used


}

void Button::SetButtonID(int newId)
{
	_buttonID = newId;
}

int Button::GetButtonID()
{
	return _buttonID;
}


//===== Left Click ======//
void Button::SetOnLeftClick(function<void()> function)
{
	_onLeftClick = function;
}

void Button::OnLeftClick()
{
	if (_onLeftClick != nullptr)_onLeftClick();// if the function is valid call function
	else OnInvalidInput();// if not, do this
}
//===== Left Click ======//
void Button::SetOnRightClick(function<void()> function)
{
}

void Button::OnRightClick()
{
	if (_onRightClick != nullptr)_onRightClick();// if the function is valid call function
	else OnInvalidInput();// if not, do this
}
//===== Left Click ======//
void Button::SetOnHovering_started(function<void()> function)
{
	_onHovering_Started = function;
}

void Button::OnHovering_started()
{
	//if (_onHovering != nullptr)_onHovering();// if the function is valid call function
	////else OnInvalidInput();//maybe not for hovering //-----> edited, this was triggering on each frame. only start once for detection

	if (!_isOverlapping)// if it did not overlapped before
	{
		_isOverlapping = true;
		if (_onHovering_Started != nullptr) _onHovering_Started();
	}
}

void Button::SetOnHovering_ended(function<void()> function)
{
	_onHovering_Ended = function;
}

void Button::OnHovering_ended()
{
	if (_isOverlapping)
	{
		_isOverlapping = false;
		if (_onHovering_Ended != nullptr) _onHovering_Ended();
	}
}

void Button::OnInvalidInput()// event fucntion when click failed (if containing function isnt valid)
{
	// not decided yet
}

void Button::FillAlpha()
{
	short int x = _width_XY.X;
	short int y = _width_XY.Y;

	_collision_mask.assign(y, vector<bool>(x, true));// just assign it all true
}

std::vector<std::vector<bool>> Button::GetCollisionMask()
{
	return _collision_mask;
}

void Button::SetLable(string new_lable)
{
	_lable = new_lable;
}

Button::~Button()
{
}

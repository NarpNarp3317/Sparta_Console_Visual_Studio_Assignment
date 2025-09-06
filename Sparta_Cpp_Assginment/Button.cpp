#include "Button.h"

//===================  Constructor ================//
Button::Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset)// with offset, no label
	:BaseFrame(priority, anchor_type, width, offset),

	_id{ button_id },
	_onLeftClick{nullptr},
	_onRightClick{nullptr},
	_onHovering{nullptr},
	_lable{"Button"}
{
}

Button::Button(int buttonID, int priority, PivotPoiontLocation anchor_type, COORD width)// without offset, no label
	:BaseFrame(priority, anchor_type, width, {0,0}),

	_id{ buttonID },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering{ nullptr },
	_lable{ "Button" }
{
}


Button::Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset)// with offset and lable
	:BaseFrame(priority, anchor_type, width, offset),
	_id{ button_id },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering{ nullptr },
	_lable{ lable }
{
}

Button::Button(int buttonID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width)// without offset, with lable
	:BaseFrame(priority, anchor_type, width, { 0,0 }),

	_id{ buttonID },
	_onLeftClick{ nullptr },
	_onRightClick{ nullptr },
	_onHovering{ nullptr },
	_lable{ lable }
{
}
//-----------------------<<      MOUSE EVENTS       >>-----------------------------//

bool Button::IsDetected(COORD mouse_coord)// return bool by checking if the mouse coord is in range of button(not finding corrd for each)
{
	COORD width = GetWidthXY();
	COORD start = GetPrintStartCoord();
	const Scene& frame = GetFramePtr();// get for read only
	
	//---> find relative coord of mouse position

	COORD relative_coord = { mouse_coord.X - start.X, mouse_coord.Y - start.Y };

	if (relative_coord.X < 0 || relative_coord.Y < 0 || relative_coord.X >= width.X || relative_coord.Y >= width.Y)
		return false;

	return frame._alpha[relative_coord.Y][relative_coord.X];//return relative coord of mouse cursor and it will be used

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
void Button::SetOnHovering(function<void()> function)
{
	_onHovering = function;
}

void Button::OnHovering()
{
	if (_onHovering != nullptr)_onHovering();// if the function is valid call function
	//else OnInvalidInput();//maybe not for hovering
}

void Button::OnInvalidInput()// event fucntion when click failed (if containing function isnt valid)
{
	// not decided yet
}



void Button::SetLable(string new_lable)
{
	_lable = new_lable;
}

COORD Button::GetMouseCoord()
{
	return COORD();
}

Button::~Button()
{
}

#include "Button.h"
#include "SceneMaker.h"
#include "SimpleButton.h"

//===================  Constructor ================//
Button::Button(int buttonID, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color)// with offset, no label
	:BaseFrame(priority, anchor_type, width, offset, frame_style, text_color, bg_color),

	_isClickable{true},
	_buttonID{ buttonID },
	_onLeftPressed{nullptr},
	_onLeftReleased{nullptr},
	_onRightPressed{nullptr},
	_onRightReleased{nullptr},
	_onHovering_Started{nullptr},
	_onHovering_Ended{nullptr},
	_isOverlapping{false},// buttons never overlaps
	_lable{"Button"}
{
	
	FillAlpha();// so that the button can be detected not only the frame but also the inside
	GenerateDefaultButtonSet();
}

Button::Button(int buttonID, int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color)// without offset, no label
	:BaseFrame(priority, anchor_type, width, {0,0}, frame_style, text_color, bg_color),

	_isClickable{ true },
	_buttonID{ buttonID },
	_onLeftPressed{ nullptr },
	_onLeftReleased{ nullptr },
	_onRightPressed{ nullptr },
	_onRightReleased{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ "Button" }
{
	
	FillAlpha();
	GenerateDefaultButtonSet();
}

Button::Button(int buttonID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color)// with offset and lable
	:BaseFrame(priority, anchor_type, width, offset, frame_style, text_color, bg_color),

	_isClickable{ true },
	_buttonID{ buttonID },
	_onLeftPressed{ nullptr },
	_onLeftReleased{ nullptr },
	_onRightPressed{ nullptr },
	_onRightReleased{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ lable }
{
	
	FillAlpha();
	GenerateDefaultButtonSet();
}

Button::Button(int buttonID, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color)// without offset, with lable
	:BaseFrame(priority, anchor_type, width, { 0,0 }, frame_style, text_color, bg_color),

	_isClickable{ true },
	_buttonID{ buttonID },
	_onLeftPressed{ nullptr },
	_onLeftReleased{ nullptr },
	_onRightPressed{ nullptr },
	_onRightReleased{ nullptr },
	_onHovering_Started{ nullptr },
	_onHovering_Ended{ nullptr },
	_isOverlapping{ false },
	_lable{ lable }
{
	
	FillAlpha();
	GenerateDefaultButtonSet();
}
//-----------------------<<      MOUSE EVENTS       >>-----------------------------//

bool Button::IsDetected(COORD mouse_coord)// return bool by checking if the mouse coord is in range of button(not finding corrd for each)
{
	COORD width = GetWidthXY();
	COORD start = GetPrintStartCoord();

	COORD relative_coord = { mouse_coord.X - start.X, mouse_coord.Y - start.Y };

	if (relative_coord.X < 0 || relative_coord.Y < 0 || relative_coord.X >= width.X || relative_coord.Y >= width.Y)
	{
		SwitchTexturePtr(&_idle_texture);
		return false;
	}
		
	SwitchTexturePtr(&_hovering_texture);

	return _collision_mask[relative_coord.Y][relative_coord.X];//return relative coord of mouse cursor and it will be used
}


void Button::GenerateDefaultButtonSet()
{
	//====== un triggered =====//
	SceneMaker::FillColor(&_idle_texture, _width_XY, DarkGray, DarkGray);
	SceneMaker::AddFrame(&_idle_texture, _width_XY, double_line, DarkGray, Black);
	SceneMaker::AddTexts(&_idle_texture, _width_XY, { 0,0 }, { _lable }, center_center, Black, DarkGray);

	SwitchTexturePtr(&_idle_texture);// switch the pointing texture address

	//====== triggered ======//
	SceneMaker::FillColor(&_pressed_texture, _width_XY, DarkGreen, DarkGreen);
	SceneMaker::AddFrame(&_pressed_texture, _width_XY, double_line, DarkGreen, Black);
	SceneMaker::AddTexts(&_pressed_texture, _width_XY, { 0,0 }, { _lable }, center_center, Black, DarkGreen);

	//====== triggered ======//
	SceneMaker::FillColor(&_hovering_texture, _width_XY, Gray, Gray);
	SceneMaker::AddFrame(&_hovering_texture, _width_XY, double_line, Gray, Black);
	SceneMaker::AddTexts(&_hovering_texture, _width_XY, { 0,0 }, { _lable }, center_center, Black, Gray);

	//====== triggered ======//
	SceneMaker::FillColor(&_activate_failed_texture, _width_XY, DarkRed, DarkRed);
	SceneMaker::AddFrame(&_activate_failed_texture, _width_XY, double_line, DarkRed, Black);
	SceneMaker::AddTexts(&_activate_failed_texture, _width_XY, { 0,0 }, { _lable }, center_center, Black, DarkRed);
	
}

void Button::SetButtonID(int newId)
{
	_buttonID = newId;
}

int Button::GetButtonID()
{
	return _buttonID;
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



//============= Mouse Trigger Events ============//

//===== Left Click ======//
void Button::SetOnLeftPressed(function<void()> function)
{
	_onLeftPressed = function;
}
void Button::OnLeftPressed()
{
	if (_onLeftPressed != nullptr)// if the function is valid call function
	{
		SwitchTexturePtr(&_pressed_texture);
		_onLeftPressed();// show indication texture when button event is triggered
	}
	else OnInvalidInput();// if not, do this
}

void Button::SetOnLeftReleased(function<void()> function)
{
	_onLeftReleased = function;
}

void Button::OnLeftReleased()
{
	if (_onLeftReleased != nullptr)
	{
		_onLeftPressed();
	}
}

//===== Right Click ======//
void Button::SetOnRightPressed(function<void()> function)
{
	_onRightPressed = function;// missed here, now recovered!
}
void Button::OnRightPressed()
{
	if (_onRightPressed != nullptr)// if the function is valid call function
	{
		SwitchTexturePtr(&_pressed_texture);
		_onRightPressed();
	}
	else OnInvalidInput();// if not, do this
}

void Button::SetOnRightReleased(function<void()> function)
{
	_onRightReleased = function;
}
void Button::OnRightReleased()
{	
	if (_onRightReleased != nullptr)
	{
		_onRightReleased();
	}
}


//===== Hovering ======//
void Button::SetOnHovering_started(function<void()> function)
{
	_onHovering_Started = function;
}

void Button::OnHovering_started()
{
	if (!_isOverlapping)// if it did not overlapped before
	{
		_isOverlapping = true;
		if (_onHovering_Started != nullptr)
		{
			//change the texture of the button for indication
			_onHovering_Started();
		}
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
		if (_onHovering_Ended != nullptr)
		{
			_onHovering_Ended();
		}
	}
}

//==== Invalid Error ====//
void Button::OnInvalidInput()// event fucntion when click failed (if containing function isnt valid)
{
	SwitchTexturePtr(&_activate_failed_texture);
	_isClickable = false;

	//TriggerState(rejective_state, 16);// disable input for 16 frames// not now
}

/*
void Button::I_Live_Update()
{
	Interactable::I_Live_Update();

	if (_current_State == idle_state && !_isClickable)// if current state is idle and currently unclickable
	{
		_isClickable = true;
	}
}
*/

Button::~Button()
{

}

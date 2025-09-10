#include "Popout.h"
#include "SceneMaker.h"



/*
Popout::Popout(Popout_Type type, PivotPoiontLocation anchor_type, COORD witdh, map<int, vector<string>> texts, Text_Color texts_color, Text_Color text, Text_Color bg)
	:BaseFrame(1,center_center, witdh, text, bg),
	_texts{texts},
	_texts_color{ texts_color }
{
	SceneMaker::PrepareCanvas(_texturePtr, _width_XY);
	SceneMaker::AddFrame(_texturePtr, _width_XY, double_line, text, bg);

	P_SetupButtons();// set up buttons by popout type
	P_Update_Texts();
}

void Popout::P_SetupButtons()
{
	switch (_pop_type)
	{
	case Confirmation:
		P_SetConfirmButtons();
		P_SetSkipButton();
	}
}

void Popout::P_SetConfirmButtons()
{
}

void Popout::P_SetSkipButton()
{
}

void Popout::P_SetValueadjustmenButtons(int* target_value)
{
}

void Popout::P_Update_Texts()
{
}

void Popout::Next_Texts()
{
}
*/

Popout::Popout(Popout_Type type, PivotPoiontLocation anchor_type, COORD offset, Text_Color texts_color, Text_Color text, Text_Color bg)
	:BaseFrame(1,center_center, AdjustPopoutWidth(), offset, double_line, text, bg),
	_pop_type{type},
	_target_value{nullptr},
	_current_PopoutLayer_index{0}// from the start
{
	
}

void Popout::AddPopoutLayer(Popout_Type type, Scene layer_texture)
{

}

void Popout::AddCustomPopoutLayer(Scene layer_texture, vector<Button*> buttons, vector<function<void()>> custom_functions)
{
}

void Popout::NextLayer()
{
}

void Popout::GetCurrentButtons()
{
}

void Popout::UpdateLayer()
{
}

void Popout::LeavePopout()
{
}

void Popout::SetDefaultButtons()
{
	switch (_pop_type)
	{
	case Confirmation:

		Yes_Button = new Button(1, 1, "Yes", bottom_center, { 5,3 }, { -5,0 }, single_line, White, Black, _default_widh_XY);
		No_Button = new Button(1,1,"No", bottom_center, { 5,3 }, { 5,0 }, single_line, White, Black, _default_widh_XY);
		_active_buttons = { Yes_Button, No_Button };
		break;

	case ValueChange:

		Increment_Button = new Button(3, 101, "+", top_center, { 5,3 }, { -5,0 }, single_line, White, Black, _default_widh_XY);
		Decrement_Button = new Button(4, 101, "-", top_center, { 5,3 }, { 5,0 }, single_line, White, Black, _default_widh_XY);
		Confirm_Button = new Button(5, 101, "Confirm", bottom_right, { 10,3 }, { -1,-1 }, single_line, White, Black, _default_widh_XY);
		Leave_Button = new Button(6, 101, "X", top_right, { 3,3 }, { 0,0 }, single_line, White, Black, _default_widh_XY);
		_active_buttons = { Increment_Button, Decrement_Button, Confirm_Button, Leave_Button };
		break;

	case Information:
	case Error:

		Skip_Button = new Button(7, 101, "Skip", bottom_right, { 10,3 }, { -1,-1 }, single_line, White, Black, _default_widh_XY);
		Leave_Button = new Button(8, 101, "X", top_center, { 10,3 }, { 0,0 }, single_line, White, Black, _default_widh_XY);
		_active_buttons = { Skip_Button, Leave_Button };
		break;

	default:
		//error!!!! invalid enum
	}
}

void Popout::AttachDefaultButtons()
{
}

COORD Popout::AdjustPopoutWidth()
{
	return COORD();
}

bool Popout::IncrementValue()
{
	if(_value_storage<0) return false;
	
	++_value_storage;
	return true;
}

bool Popout::DecrementValue()
{
	if (_value_storage < 0) return false;

	--_value_storage;
	return true;
}

void Popout::SetTargetValue(int* value)
{
	_target_value = value;

	if (_target_value != nullptr)
	{
		_value_storage = *_target_value;
	}
}

int Popout::GetTargetValue()
{
	return _value_storage;
}

bool Popout::ConfirmValueChange()
{
	if (_target_value != nullptr) return false;

	//if(_target_value<0)return false; //temp condition. no negative--> this condition will be checked when clicking the increment decrement button

	*_target_value = _value_storage;

	return true;
}

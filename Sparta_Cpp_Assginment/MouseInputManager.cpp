#include "MouseInputManager.h"

MouseInputManager::MouseInputManager(HANDLE input_Handle):
	_isActive{false},
	_isClickable{false},
	_is_Left_Pressed{false},
	_is_Right_Pressed{ false },
	_Interaction_targetPtr{nullptr},
	_cursor_coord_on_event{0,0},// default for now
	_input_type{None},
	_mouse_event_Record{},
	_input_Record{},
	_events{},
	_OnMouseEvent{nullptr}
{
	this->_input_H = input_Handle;
	Start_MouseInputReading();
}

void MouseInputManager::UpdateMouseInput()
{
	//==== no no conditions ====//
	if (!_isActive) return;
	if (_OnMouseEvent == nullptr) return;
	//if (!PeekConsoleInput(_input_H, &_input_Record, 1, &_events)) return;// not so sure
	if (!ReadConsoleInput(_input_H, &_input_Record, 1, &_events)) return;
	if (_input_Record.EventType != MOUSE_EVENT) return;
	//--------------------------//

	_input_type = None;//reset the input type
	_mouse_event_Record = _input_Record.Event.MouseEvent;// record mouse events from Event(which is from input record by dread console input)
	_cursor_coord_on_event = _mouse_event_Record.dwMousePosition;//dworld mouse cursor position

	bool L_pressed_Now = (_mouse_event_Record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
	bool R_pressed_Now = (_mouse_event_Record.dwButtonState & RIGHTMOST_BUTTON_PRESSED);


	//========== Left Trigger ==========//
	if (L_pressed_Now && !R_pressed_Now && _isClickable)// when only left is pressed whil it is clickable
	{
		_is_Left_Pressed = true;
		if (_Interaction_targetPtr != nullptr && CheckTargetValid(_Interaction_targetPtr))// target address is not empty and target is valid
		{
			_Interaction_targetPtr->Trigger_ActiveState();// pressed
			_input_type = Left_click;
		}
	}
	else if (!L_pressed_Now && _is_Left_Pressed)// if was pressed but now, it is released
	{
		_is_Left_Pressed = false;// no longer pressed
		if (_Interaction_targetPtr != nullptr && CheckTargetValid(_Interaction_targetPtr))// if the target and pointer is still valid
		{
			if (_Interaction_targetPtr->GetState() == active_state)// if current state is active
			{
				_Interaction_targetPtr->OnLeftPressed();
			}
		}
	}
	//========== Right Trigger ==========//
	if (R_pressed_Now && !L_pressed_Now && _isClickable)// when only left is pressed whil it is clickable
	{
		_is_Right_Pressed = true;
		if (_Interaction_targetPtr != nullptr && CheckTargetValid(_Interaction_targetPtr))// target address is not empty and target is valid
		{
			_Interaction_targetPtr->Trigger_ActiveState();// pressed
			_input_type = Right_click;
		}
	}
	else if (!R_pressed_Now && _is_Right_Pressed)// if was pressed but now, it is released
	{
		_is_Right_Pressed = false;// no longer pressed
		if (_Interaction_targetPtr != nullptr && CheckTargetValid(_Interaction_targetPtr))// if the target and pointer is still valid
		{
			if (_Interaction_targetPtr->GetState() == active_state)// if current state is active
			{
				_Interaction_targetPtr->OnLeftPressed();
			}
		}
	}


}

void MouseInputManager::Start_MouseInputReading()// version 2, no looping( looping for console)// this checks for each frame of the update
{
	//==== no no conditions ====//
	if (!_isActive) return;
	if (_OnMouseEvent == nullptr) return;
	//if (!PeekConsoleInput(_input_H, &_input_Record, 1, &_events)) return;// not so sure
	if (!ReadConsoleInput(_input_H, &_input_Record, 1, &_events)) return;
	if (_input_Record.EventType != MOUSE_EVENT) return;
	//--------------------------//
	_input_type = None;//reset the input type
	_mouse_event_Record = _input_Record.Event.MouseEvent;// record mouse events from Event(which is from input record by dread console input)
	_cursor_coord_on_event = _mouse_event_Record.dwMousePosition;//dworld mouse cursor position
	//=== mouse input/event checking ===//
	if (_mouse_event_Record.dwEventFlags == 0 && _isClickable)
	{
		if (_mouse_event_Record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) _input_type = Left_click;//DWORD Button state--> tells which button was pressed// using bit operator
		else if (_mouse_event_Record.dwButtonState & RIGHTMOST_BUTTON_PRESSED) _input_type = Right_click;
	}
	else if (_mouse_event_Record.dwEventFlags == MOUSE_MOVED)_input_type = Hovering;
	//== trigger call ==//
	if (_input_type != None) _OnMouseEvent(_cursor_coord_on_event, _input_type);// if mouse input is valid input type
	if (!_isActive) return;// if _isactive turns false, stop the loop
}

//---------------------------------------------------------- Able/Disable
void MouseInputManager::Pause_MouseInputReading()
{
	_input_type = None;//reset the input type

	_mouse_event_Record = _input_Record.Event.MouseEvent;// record mouse events from Event(which is from input record by dread console input)
	_cursor_coord_on_event = _mouse_event_Record.dwMousePosition;//dworld mouse cursor position

	//=== mouse input/event checking ===//
	if (_mouse_event_Record.dwEventFlags == 0 && _isClickable)
	{
		if (_mouse_event_Record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) _input_type = Left_click;//DWORD Button state--> tells which button was pressed// using bit operator

		else if (_mouse_event_Record.dwButtonState & RIGHTMOST_BUTTON_PRESSED) _input_type = Right_click;

	}
	else if (_mouse_event_Record.dwEventFlags == MOUSE_MOVED)_input_type = Hovering;

	//== trigger call ==//
	if (_input_type != None) _OnMouseEvent(_cursor_coord_on_event, _input_type);// if mouse input is valid input type	

	if (!_isActive) return;// if _isactive turns false, stop the loop
}


void MouseInputManager::ActivateMouseInput()
{
	_isActive = true;
}

//---------------------------------------------------------- Able/Disable
void MouseInputManager::DeactivateMouseInput()//every mouse input

{
	this->_isActive = false;
}

void MouseInputManager::ActivateMouseClick()
{
	this->_isClickable = true;
}

void MouseInputManager::DisableMouseClick()
{
	this->_isClickable = false;
}

//----------------------------------------------------- mouse events
void MouseInputManager::OnRightClick()
{
	this->_Interaction_targetPtr->OnRightPressed();
}

void MouseInputManager::OnLeftClick()
{
	this->_Interaction_targetPtr->OnLeftPressed();
}

void MouseInputManager::OnHovering_started()
{
	this->_Interaction_targetPtr->OnHovering_started();
}

void MouseInputManager::OnHovering_ended()
{
	this->_Interaction_targetPtr->OnHovering_ended();
}

//void MouseInputManager::Hovering()
//{
//	// condition for button coord matching with mouse cursor coord--> this triggers button to change color
//	this->_Interaction_targetPtr->OnHovering();
//}

//------------------------------------------------------------------------------------** Interaction
void MouseInputManager::SetInteractionTarget(Interactable* newTarget)
{
	this->_Interaction_targetPtr = newTarget;
}

void MouseInputManager::DetectInteractionTarget()
{
	
}

Interactable* MouseInputManager::GetCurrentInteractionTarget()
{
	return nullptr;
}

bool MouseInputManager::CheckTargetValid(Interactable* newTarget)// check if the interaction target is valid or not
{
	if (newTarget != nullptr) return true;
	else return false;	
}

MouseInputManager::~MouseInputManager()
{
}

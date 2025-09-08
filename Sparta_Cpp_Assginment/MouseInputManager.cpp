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


void MouseInputManager::UpdateMouseInput()// version 2, using Centralized TimeManagement
{
	//======= No No Conditions =====//
	if (!_isActive || _OnMouseEvent == nullptr) return;
	if (!ReadConsoleInput(_input_H, &_input_Record, 1, &_events)) return;
	if (_input_Record.EventType != MOUSE_EVENT) return;
	//-----------------------------//

	_input_type = None;
	_mouse_event_Record = _input_Record.Event.MouseEvent;
	_cursor_coord_on_event = _mouse_event_Record.dwMousePosition;

	bool L_pressed_Now = (_mouse_event_Record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
	bool R_pressed_Now = (_mouse_event_Record.dwButtonState & RIGHTMOST_BUTTON_PRESSED);

	//==== Left Button ====//
	if (L_pressed_Now && !_is_Left_Pressed && _isClickable)
	{
		_is_Left_Pressed = true;
		if (CheckTargetValid(_Interaction_targetPtr))
		{
			_Interaction_targetPtr->TriggerState(active_state,0);// trigger now!
			_Interaction_targetPtr->OnLeftPressed();
			_input_type = Left_click;
		}
	}
	else if (!L_pressed_Now && _is_Left_Pressed)
	{
		_is_Left_Pressed = false;
		if (CheckTargetValid(_Interaction_targetPtr))
		{
			if (_Interaction_targetPtr->GetState() == active_state)
			{
				_Interaction_targetPtr->OnLeftReleased();
				_Interaction_targetPtr->TriggerState(idle_state,5000);
			}
		}
	}

	//==== Right Button ====//
	if (R_pressed_Now && !_is_Right_Pressed && _isClickable)
	{
		_is_Right_Pressed = true;
		if (CheckTargetValid(_Interaction_targetPtr))
		{
			_Interaction_targetPtr->TriggerState(active_state,0);
			_Interaction_targetPtr->OnRightPressed();
			_input_type = Right_click;
		}
	}
	else if (!R_pressed_Now && _is_Right_Pressed)
	{
		_is_Right_Pressed = false;
		if (CheckTargetValid(_Interaction_targetPtr))
		{
			if (_Interaction_targetPtr->GetState() == active_state)
			{
				_Interaction_targetPtr->OnRightReleased();
				_Interaction_targetPtr->TriggerState(idle_state,5000);
			}
		}
	}

	//==== Hovering ====//
	if (_mouse_event_Record.dwEventFlags == MOUSE_MOVED)
	{
		if (CheckTargetValid(_Interaction_targetPtr))
		{
			if (_Interaction_targetPtr->IsDetected(_cursor_coord_on_event))
			{
				if (_Interaction_targetPtr->GetState() != focused_state)
				{
					_Interaction_targetPtr->OnHovering_started();
					_Interaction_targetPtr->TriggerState(focused_state,0);
				}
			}
			else if (_Interaction_targetPtr->GetState() == idle_state)
			{
				_Interaction_targetPtr->OnHovering_ended();
				_Interaction_targetPtr->TriggerState(idle_state,0);
			}
		}
	}

	// Callback hook if needed
	if (_input_type != None)
	{
		_OnMouseEvent(_cursor_coord_on_event, _input_type);
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

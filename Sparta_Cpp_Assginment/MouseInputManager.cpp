#include "MouseInputManager.h"

MouseInputManager::MouseInputManager(HANDLE input_Handle):
	_isActive{false},
	_isClickable{false},
	_Interaction_targetPtr{nullptr},
	_cursor_coord_on_event{0,0}// default for now

{
	this->_input_H = input_Handle;
	Start_MouseInputReading();
}

//--------------------------------------------------------- ** Mouse Event 

void MouseInputManager::Start_MouseInputReading()
{
	this->_isActive = true;
	while (_isActive)// loop reading mouse event while it is active
	{
		if (ReadConsoleInput(_input_H, &_input_Record, 1, &_events))// input handle에서 읽힌 input을 _input_record에 저장함, 
		{
			if (_input_Record.EventType == MOUSE_EVENT && _isClickable)//만약 읽힌 이벤트의 타입이 mouse event이고, 지금 클릭 가능한 상황일시에
			{
				_mouse_event_Record = _input_Record.Event.MouseEvent;// record mouse events from Event(which is from input record by dread console input)
				_cursor_coord_on_event = _mouse_event_Record.dwMousePosition;//dworld mouse cursor position

				//if (_Interaction_targetPtr->)// only works if the mouse cursor's coord overlaps with targrt's //alshjdklajhsfdlkua fuck
				//{
					if (_mouse_event_Record.dwEventFlags == 0)//if no mouse input mode is flagged, 
					{
						if (_mouse_event_Record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)//flag for left click
						{
							OnLeftClick();
						}
						else if (_mouse_event_Record.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
						{
							OnRightClick();
						}
					}
					else if (_mouse_event_Record.dwEventFlags == MOUSE_MOVED)
					{
						Hovering();
					}
				//}


	
			}
		}
	}
}

//---------------------------------------------------------- Able/Disable
void MouseInputManager::Pause_MouseInputReading()
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
	this->_Interaction_targetPtr->OnRightClick();
}

void MouseInputManager::OnLeftClick()
{
	this->_Interaction_targetPtr->OnLeftClick();
}

void MouseInputManager::Hovering()
{
	// condition for button coord matching with mouse cursor coord--> this triggers button to change color
	this->_Interaction_targetPtr->OnHovering();
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

bool MouseInputManager::CheckTargetValid(Interactable* newTarget)
{
	if (newTarget != nullptr) return true;
	else return false;	
}

MouseInputManager::~MouseInputManager()
{
}

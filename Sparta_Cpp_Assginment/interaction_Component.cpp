#include "interaction_Component.h"

void Interactable::Trigger_ActiveState()
{
	_current_State = active_state;
	ResetStateTimer();// back to 0
}

void Interactable::Trigger_FocusedState_Start()
{
	_current_State = focused_state;
}

void Interactable::Trigger_FocusedState_End()
{
	_current_State = idle_state;
}

void Interactable::Trigger_ErrorState()
{
	_current_State = rejective_state;
	ResetStateTimer();
}

void Interactable::I_Live_Update()
{
	if (_current_State == active_state || _current_State == rejective_state)// other states do not need timer(hovering, idle)
	{
		if (_state_timer < _state_duration)// if there's still time left
		{
			_state_timer++;// increment
		}
		else
		{
			// Time is up ¡æ return to idle
			_current_State = idle_state;
			_state_timer = 0;//reset the timer
			//ResetStateTimer() ---> or just =0
		}
	}
}

void Interactable::SetState(Interactable_State newState)
{
	_current_State = newState;
}

Interactable_State Interactable::GetState()
{
	return _current_State;
}

void Interactable::UpdateStateTimer()
{
	if (_state_timer < _state_duration) _state_timer++;
}

void Interactable::ResetStateTimer()
{
	_state_duration = 0;
}

int Interactable::GetStateTimer()
{
	return _state_timer;
}

void Interactable::SetStateDuration(int newDuration)
{
	_state_duration = newDuration;
}

int Interactable::GetStateDuration()
{
	return _state_duration;
}

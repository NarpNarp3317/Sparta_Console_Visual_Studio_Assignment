#include "interaction_Component.h"





void Interactable::I_Live_Update()
{
	if ((_current_State == active_state || _current_State == rejective_state) &&
		ClockTower::Get_Current_Tick() >= _reserved_time)
	{
		_current_State = idle_state;
	}
}


/*nteractable::Interactable(void* owner)
{
	_onwer = owner;
}*/


void Interactable::SetStateDuration(int duration)
{
	_state_duration = duration;
}


//void* Interactable::GetOwner()
//{
//	return _owner;
//}


void Interactable::TriggerState(Interactable_State newState, int duration)
{
	_current_State = newState;

	if (duration > 0)
	{
		_reserved_time = ClockTower::Get_Current_Tick() + duration;// reserve alarm
	}	
	else
	{
		//_reserved_time = 0;// do it now!
	}
}


Interactable_State Interactable::GetState()
{
	return _current_State;
}


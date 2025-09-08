#pragma once
#include "Enum_Live_Interactable_state.h"
/*
this will allow classes with possession of this component(?) to be able to get interaction from mouse or other input events
current interactions are
1. right click
2. left click
3. hovering

with these interactions, classes with this componet will tirger their member fucntions
ex. button
left click--> use
right click ---> info
hoverring--> change color(highlight)

*/

class Interactable
{
//private:--> the owner can get access
protected:
	Interactable_State _current_State = idle_state;
	
	//==== timer ====//
	int _state_timer;
	int _state_duration;


public:

	// interaction events

	virtual void OnLeftPressed(){}
	virtual void OnLeftReleased(){}

	virtual void OnRightPressed(){}
	virtual void OnRightReleased(){}

	virtual void OnHovering_started(){}
	virtual void OnHovering_ended(){}// so that hovering is not keep calling event on every frame

	//===== trigger function =====//

	void Trigger_ActiveState();
	void Trigger_FocusedState_Start();
	void Trigger_FocusedState_End();
	void Trigger_ErrorState();


	virtual void I_Live_Update();// timer for owner

	void SetState(Interactable_State newState);
	Interactable_State GetState();

	void UpdateStateTimer();// this will increment by each update
	void ResetStateTimer();// back to 0
	int GetStateTimer();// get how much time has past

	void SetStateDuration(int duration);
	int GetStateDuration();




};
#pragma once
#include "Enum_Live_Interactable_state.h"
#include "Windows.h"
#include "ClockTower.h"
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
//template<typename Owner>// use template to get unknown class of owner as pointer
//--> still needs to put the data type in <>
class Interactable
{

//public: Interactable(void* owner);// use generic pointer instead----> cannot use it for -> any ways. mission failed


//private:--> the owner can get access
protected:
	//void* _owner;
	Interactable_State _current_State=idle_state;
	
	//==== timer ====//
	int _reserved_time = 0;// the clock time of state update end
	int _state_duration=0;


public:

	//virtual bool IsDetected(COORD mouseCoord) {};--> this one has body. it needs to return a bool value

	virtual bool IsDetected(COORD mouseCoord) =0;// making it into pure virtual// doesnt have to return anything in here.
	// allows classes that have this component to override and use detection// which will be used in Mouse input manager!!!! fuck yeah now i get it fuck



	// interaction events

	virtual void OnLeftPressed(){}
	virtual void OnLeftReleased(){}

	virtual void OnRightPressed(){}
	virtual void OnRightReleased(){}

	virtual void OnHovering_started(){}
	virtual void OnHovering_ended(){}// so that hovering is not keep calling event on every frame

	//===== trigger function =====//

	void SetStateDuration(int duration);
	//void* GetOwner();

	void TriggerState(Interactable_State newState, int duration);
	
	Interactable_State GetState();

	virtual void I_Live_Update();// some will use their own timer.

	/*
	void SetState(Interactable_State newState);
	Interactable_State GetState();

	void UpdateStateTimer();// this will increment by each update
	void ResetStateTimer();// back to 0
	int GetStateTimer();// get how much time has past

	int GetStateDuration();
	*/
	// this method was allowing interactables to get their own timer, but when the number goes up, if burden the computing
	// for effeciency, i chose centralized time manager to siganl and check every interactables.



};
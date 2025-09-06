#pragma once

/*
this will allow classes with possession of this component(?) to be able to get interaction from mouse or other input events
current interactions are
1. right click
2. left click
3. hovering

with these interactions, classes with this componet will tirger their member fucntions
ex. button
left click--> usse
right click ---> info
hoverring--> change color(highlight)

*/

class Interactable
{
public:
	virtual void OnLeftClick(){}
	virtual void OnRightClick(){}
	virtual void OnHovering() {}// while makes more sence, but for unifomity(?) just "On"
	//virtual void InvalidInput(){}// for left, right click. try to interact but cannot for reason?
	//--> make functions for exceptional cases in the class, not in here

	virtual bool isDetected();

	virtual~Interactable(){}
};
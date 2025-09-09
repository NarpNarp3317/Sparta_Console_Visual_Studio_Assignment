#pragma once

enum Interactable_State// to use this for more than button state, this needs to be inclusive
{
	idle_state,// default , no stimulation
	active_state, // event happened, action!
	focused_state,// like hovering, highlighted ?
	rejective_state// event trigger failed
};
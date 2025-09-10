#pragma once

enum PopupType// for making popout layer
{
	Information,// just to show texture
	Error,// same as information but <<ERROR>> on top of the popout
	Confirmation,// yes or no
	ValueChange,// adjust the target value
	Custom
};
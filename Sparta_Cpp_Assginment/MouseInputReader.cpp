#include "MouseInputReader.h"

MouseInputReader::MouseInputReader(HANDLE input_Handle)
{
	this->_input_H = input_Handle;
	this->_isactive = true;
}

void MouseInputReader::ActivateMouseClick()
{
	ReadConsoleInput(_input_H, &input_Record, 1, &events);//
}

void MouseInputReader::DisableMouseClick()
{
}

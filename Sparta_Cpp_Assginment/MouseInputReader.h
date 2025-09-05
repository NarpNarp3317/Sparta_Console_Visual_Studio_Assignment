#pragma once
#include <Windows.h>

class MouseInputReader
{
public:
	MouseInputReader(HANDLE input_Handle);

private:
	HANDLE _input_H;// from console manager
	COORD _cursor_coord_on_event;

	INPUT_RECORD input_Record;//varaible to record the input event
	DWORD events;// this will store the number of events read//
	bool _isactive;//

public:

	void ActivateMouseClick();// 마우스 클릭 가능하게 함
	void DisableMouseClick();// 마우스 클릭 읽기를 중단함

	void OnRightClick();
	void OnLeftClick();
	void Hovering();

};
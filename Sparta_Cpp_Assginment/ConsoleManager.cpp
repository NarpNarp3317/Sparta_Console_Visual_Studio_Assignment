#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
	:_input_H(GetStdHandle(STD_INPUT_HANDLE))
	,_output_H(GetStdHandle(STD_OUTPUT_HANDLE))// input, ouput handle설정
	,_KeyboardConsoleMode(GetConsoleMode(_input_H,&_KeyboardConsoleMode))//생성시, 기본 콘솔보드(키보드)를 모드로 저장함
	,_consoleWindow(GetConsoleWindow())// 현재 콘솔창의 정보를 가져옴
{

	// 시작 세팅
	/*
	1. f11눌러서 화면 확대
	2. console window 최대크기로 수정
	3. console input mode, mouse click mode로 변경
	4. 게임 시작화면 진행
	*/

	StartScene();

	this->_mouse = new MouseInputReader(_input_H);
	this->_printer = new Printer(_output_H);



}

void ConsoleManager::StartScene()
{
	/*
	printf( "Type F11 to continue: \n >> ");//F11같은 F key들은 여기서 영향줄수 없음 그렇기에 누른다는 가정아래에서 게임을 실행하도록 함
	std::cin.get();
	//f11 이후로 진행
	*/

	ConsoleWindowResizing();
	

	SwitchInputmode(MouseClickMode);

	//GetConsoleMode(_input_H, &_MouseControllMode);// and put it on mouse console mode

	std::cin.get();
}

void ConsoleManager::ResizeConsoleWindow()
{

}

void ConsoleManager::SwitchInputmode(Enum_ConsoleMode inputmode)//입력 모드를 주어진 enum으로 변경함
{
	if (inputmode == KeyboardTypeInMode)
	{
		SetConsoleMode(_input_H, _KeyboardConsoleMode);
		this->_consoleMode = KeyboardTypeInMode;
	}
	else if (inputmode == MouseClickMode)
	{
		 SetConsoleMode(_input_H, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
		this->_consoleMode = MouseClickMode;
	}

	else; //Error status updater; --> Enum 추가하지 말것
}

void ConsoleManager::ConsoleWindowResizing()
{
	ShowWindow(_consoleWindow, SW_MAXIMIZE);//showwnindow_maximize
	//
	_windows_Scale = GetLargestConsoleWindowSize(_output_H);// 현 화면의 최대 크기를 저장

	_windows_RECT_Corners = { 0, 0, _windows_Scale.X, _windows_Scale.Y };// 화면 코너들의 좌표들을 저장
	SetConsoleWindowInfo(_output_H, TRUE, &_windows_RECT_Corners);//콘솔창의 info

	SetConsoleScreenBufferSize(_output_H, _windows_Scale);//화면 크기를 정해둔 크기로 바꿈
}

void ConsoleManager::PlaceButtons()
{
}

#pragma once
#include <Windows.h>
#include "Enum_MouseInput.h"
#include "Enum_ConsoleMode.h"
#include "MouseInputReader.h"
#include "Printer.h"

class ConsoleManager
{
public:
	ConsoleManager();

	// 시작 세팅
	/*
	1. f11눌러서 화면 확대
	2. console window 최대크기로 수정
	3. console input mode, mouse click mode로 변경
	4. 게임 시작화면 진행
	*/

private:

	MouseInputReader* _mouse;//마우스 입력
	Printer* _printer;

	Enum_ConsoleMode _consoleMode;//현 콘솔모드

	HANDLE _input_H;// stdinput handle 보관
	HANDLE _output_H;//Output handle보관

	DWORD _KeyboardConsoleMode;//default mode
	//DWORD _MouseControllMode;

	HWND _consoleWindow;//현재 콘솔 창

	COORD _windows_Scale;//콘솔 윈도우 크기 
	SMALL_RECT _windows_RECT_Corners; //{ 0, 0, x길이, y길이-- > 직사각형 윈도우 화면의 코너 좌표 }

	//short int _window_X_length;//화면 x
	//short int _window_Y_Length;//화면 y

	//vector<vector<int>> _button_id_storage --> 클릭 가능한 버튼들의 id들을 저장함

public:

	void StartScene();//화면 설정 시작

	void ResizeConsoleWindow();//화면 최대 크기로 콘솔창 확대

	void SwitchInputmode(Enum_ConsoleMode inputmode);

	void ConsoleWindowResizing();// maximize the console window

	void PlaceButtons();//클릭 가능한 버튼들의 좌표와 anchor pivot point와 맞게 배치함

};
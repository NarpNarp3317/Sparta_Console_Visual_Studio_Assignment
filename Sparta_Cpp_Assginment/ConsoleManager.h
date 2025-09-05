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

	// ���� ����
	/*
	1. f11������ ȭ�� Ȯ��
	2. console window �ִ�ũ��� ����
	3. console input mode, mouse click mode�� ����
	4. ���� ����ȭ�� ����
	*/

private:

	MouseInputReader* _mouse;//���콺 �Է�
	Printer* _printer;

	Enum_ConsoleMode _consoleMode;//�� �ָܼ��

	HANDLE _input_H;// stdinput handle ����
	HANDLE _output_H;//Output handle����

	DWORD _KeyboardConsoleMode;//default mode
	//DWORD _MouseControllMode;

	HWND _consoleWindow;//���� �ܼ� â

	COORD _windows_Scale;//�ܼ� ������ ũ�� 
	SMALL_RECT _windows_RECT_Corners; //{ 0, 0, x����, y����-- > ���簢�� ������ ȭ���� �ڳ� ��ǥ }

	//short int _window_X_length;//ȭ�� x
	//short int _window_Y_Length;//ȭ�� y

	//vector<vector<int>> _button_id_storage --> Ŭ�� ������ ��ư���� id���� ������

public:

	void StartScene();//ȭ�� ���� ����

	void ResizeConsoleWindow();//ȭ�� �ִ� ũ��� �ܼ�â Ȯ��

	void SwitchInputmode(Enum_ConsoleMode inputmode);

	void ConsoleWindowResizing();// maximize the console window

	void PlaceButtons();//Ŭ�� ������ ��ư���� ��ǥ�� anchor pivot point�� �°� ��ġ��

};
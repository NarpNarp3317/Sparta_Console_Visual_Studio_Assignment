#include "ConsoleManager.h"
#include <iostream>

ConsoleManager::ConsoleManager()
	:_input_H(GetStdHandle(STD_INPUT_HANDLE))
	,_output_H(GetStdHandle(STD_OUTPUT_HANDLE))// input, ouput handle����
	,_KeyboardConsoleMode(GetConsoleMode(_input_H,&_KeyboardConsoleMode))//������, �⺻ �ֺܼ���(Ű����)�� ���� ������
	,_consoleWindow(GetConsoleWindow())// ���� �ܼ�â�� ������ ������
{

	// ���� ����
	/*
	1. f11������ ȭ�� Ȯ��
	2. console window �ִ�ũ��� ����
	3. console input mode, mouse click mode�� ����
	4. ���� ����ȭ�� ����
	*/

	StartScene();

	this->_mouse = new MouseInputReader(_input_H);
	this->_printer = new Printer(_output_H);



}

void ConsoleManager::StartScene()
{
	/*
	printf( "Type F11 to continue: \n >> ");//F11���� F key���� ���⼭ �����ټ� ���� �׷��⿡ �����ٴ� �����Ʒ����� ������ �����ϵ��� ��
	std::cin.get();
	//f11 ���ķ� ����
	*/

	ConsoleWindowResizing();
	

	SwitchInputmode(MouseClickMode);

	//GetConsoleMode(_input_H, &_MouseControllMode);// and put it on mouse console mode

	std::cin.get();
}

void ConsoleManager::ResizeConsoleWindow()
{

}

void ConsoleManager::SwitchInputmode(Enum_ConsoleMode inputmode)//�Է� ��带 �־��� enum���� ������
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

	else; //Error status updater; --> Enum �߰����� ����
}

void ConsoleManager::ConsoleWindowResizing()
{
	ShowWindow(_consoleWindow, SW_MAXIMIZE);//showwnindow_maximize
	//
	_windows_Scale = GetLargestConsoleWindowSize(_output_H);// �� ȭ���� �ִ� ũ�⸦ ����

	_windows_RECT_Corners = { 0, 0, _windows_Scale.X, _windows_Scale.Y };// ȭ�� �ڳʵ��� ��ǥ���� ����
	SetConsoleWindowInfo(_output_H, TRUE, &_windows_RECT_Corners);//�ܼ�â�� info

	SetConsoleScreenBufferSize(_output_H, _windows_Scale);//ȭ�� ũ�⸦ ���ص� ũ��� �ٲ�
}

void ConsoleManager::PlaceButtons()
{
}

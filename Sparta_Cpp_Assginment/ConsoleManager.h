#pragma once
#include <Windows.h>
#include "Enum_MouseInput.h"
#include "Enum_ConsoleMode.h"
#include "MouseInputManager.h"// for mouse input/and keyboard input(default)
#include "Display.h"// for a scene on screen
#include "Printer.h"// renerer
#include "Interaction_Component.h"

class ConsoleManager
	/*
	console manager reads the inputs on the console in loop and printout the scene using output handle;
	
	*/
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

	bool _isrunning;//to start and pause the live update

	MouseInputManager* _mouse;//���콺 �Է�
	Printer* _printer;

	Enum_ConsoleMode _consoleMode;//�� �ָܼ��

	HANDLE _input_H;// stdinput handle ����
	HANDLE _output_H;//Output handle����

	DWORD _input_Mode;
	//DWORD _KeyboardConsoleMode;//default mode//---> dont store it but use function set input mode// which is more expandable than making more data members for each mode
	//DWORD _MouseControllMode;

	HWND _consoleWindow;//���� �ܼ� â

	COORD _windows_Scale;//�ܼ� ������ ũ�� 
	SMALL_RECT _windows_RECT_Corners; //{ 0, 0, x����, y����-- > ���簢�� ������ ȭ���� �ڳ� ��ǥ }

	//======= UI Display =======//
	Display* _currentDisplay;
	vector<Display*> _Displays;

	//short int _window_X_length;//ȭ�� x
	//short int _window_Y_Length;//ȭ�� y

	//vector<vector<int>> _button_id_storage --> Ŭ�� ������ ��ư���� id���� ������

	Scene _final_Scene;

public:

	void SetupScene();//ȭ�� ���� ����

	void ResizeConsoleWindow();//load the saved display scene when the console window size get changed

	void SwitchInputmode(Enum_ConsoleMode inputmode);

	void ReadMouseInput();


	void ConsoleWindowResizing();// maximize the console window

	//void PlaceButtons();//Ŭ�� ������ ��ư���� ��ǥ�� anchor pivot point�� �°� ��ġ��// edited--> set placement infos in Display obj(ex. menue, ingame, battle, shop)

	// �Ⱦ�
	//void SetDisplacement();
	//void MouseinputReader(COORD mouse_coord);// read what mouse input manager is getting



	void SetCurrentDisplay(Display* _disp);




	void C_ActivateMouseInput();
	void C_DeactivateMouseInput();
	void C_ActivateMouseClicks();// ActivateMouseClick is already in use of mouse input manager
	void C_DeactivateMouseClicks();

	void SetupMouseInput();

	//====== Actually updating the Console ====//
	void Update();// input and output
	void Run_Update();
	void Pause_Update();

	~ConsoleManager();





};
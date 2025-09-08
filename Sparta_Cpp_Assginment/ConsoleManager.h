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

	// 시작 세팅
	/*
	1. f11눌러서 화면 확대
	2. console window 최대크기로 수정
	3. console input mode, mouse click mode로 변경
	4. 게임 시작화면 진행
	*/

private:

	bool _isrunning;//to start and pause the live update

	MouseInputManager* _mouse;//마우스 입력
	Printer* _printer;

	Enum_ConsoleMode _consoleMode;//현 콘솔모드

	HANDLE _input_H;// stdinput handle 보관
	HANDLE _output_H;//Output handle보관

	DWORD _input_Mode;
	//DWORD _KeyboardConsoleMode;//default mode//---> dont store it but use function set input mode// which is more expandable than making more data members for each mode
	//DWORD _MouseControllMode;

	HWND _consoleWindow;//현재 콘솔 창

	COORD _windows_Scale;//콘솔 윈도우 크기 
	SMALL_RECT _windows_RECT_Corners; //{ 0, 0, x길이, y길이-- > 직사각형 윈도우 화면의 코너 좌표 }

	//======= UI Display =======//
	Display* _currentDisplay;
	vector<Display*> _Displays;

	//short int _window_X_length;//화면 x
	//short int _window_Y_Length;//화면 y

	//vector<vector<int>> _button_id_storage --> 클릭 가능한 버튼들의 id들을 저장함

	Scene _final_Scene;

public:

	void SetupScene();//화면 설정 시작

	void ResizeConsoleWindow();//load the saved display scene when the console window size get changed

	void SwitchInputmode(Enum_ConsoleMode inputmode);

	void ReadMouseInput();


	void ConsoleWindowResizing();// maximize the console window

	//void PlaceButtons();//클릭 가능한 버튼들의 좌표와 anchor pivot point와 맞게 배치함// edited--> set placement infos in Display obj(ex. menue, ingame, battle, shop)

	// 안씀
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
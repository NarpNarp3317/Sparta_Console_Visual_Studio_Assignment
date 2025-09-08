#include "ConsoleManager.h"
#include <string>

ConsoleManager::ConsoleManager()
	:_input_H(GetStdHandle(STD_INPUT_HANDLE))
	,_output_H(GetStdHandle(STD_OUTPUT_HANDLE)),// input, ouput handle설정
	_isrunning{ false }// start as paused
{


	SetConsoleOutputCP(437);// to print extended ascii

	//SetConsoleFonstsize(16, 11);

	// 시작 세팅
	/*
	1. f11눌러서 화면 확대// 아니면 어느정도 여백을 줘서 화면이 겹치지 않게 하기
	2. console window 최대크기로 수정
	3. console input mode, mouse click mode로 변경
	4. 게임 시작화면 진행
	*/

	SetupScene();

	this->_mouse = new MouseInputManager (_input_H);
	this->_printer = new Printer(_output_H);


	SetupScene();// setup scene and print out on console screen



	//==== mouse settings =====//
	C_ActivateMouseClicks();//---> at the beginning, activate mouse event and button click
	C_ActivateMouseInput();
	SetupMouseInput();// setup mouse input function so that mouseinput can be detected

	
}

void ConsoleManager::SetupScene()
{
	/*
	printf( "Type F11 to continue: \n >> ");//F11같은 F key들은 여기서 영향줄수 없음 그렇기에 누른다는 가정아래에서 게임을 실행하도록 함
	std::cin.get();
	//f11 이후로 진행
	*/
	
	
	ConsoleWindowResizing();
	
	FillConsoleWithDot();
	SwitchInputmode(MouseClickMode);

	//GetConsoleMode(_input_H, &_MouseControllMode);// and put it on mouse console mode
	
}

//======== Mouse Input ==========//
void ConsoleManager::C_ActivateMouseInput()
{
	if (_mouse != nullptr)_mouse->ActivateMouseInput();
}

void ConsoleManager::C_DeactivateMouseInput()
{
	if (_mouse != nullptr)_mouse->DeactivateMouseInput();
}

void ConsoleManager::C_ActivateMouseClicks()
{
	if (_mouse != nullptr)_mouse->ActivateMouseClick();
}

void ConsoleManager::C_DeactivateMouseClicks()
{
	if (_mouse != nullptr)_mouse->DisableMouseClick();
}

void ConsoleManager::SetupMouseInput()
{
	_mouse->_OnMouseEvent =// define what MouseEvent is
		[this](COORD mouse_coord, Enum_MouseInput input_type)
		{
			if (_currentDisplay == nullptr) return;// no no situation

			for (Button* button : _currentDisplay->GetInteractables())// check every interactables in current display(for now, its a buttons)
			{
				if (button->IsDetected(mouse_coord))// if button is in range and overlap with alpha
				{
					button->OnHovering_started();

					switch (input_type)
					{
					case Left_click:button->OnLeftClick(); break;

					case Right_click:button->OnRightClick(); break;

						//case Hovering:button->OnHovering(); break; no more

					default:
					{
						//error, invalid enum has been used
						break;
					}
					}
				}
				else
				{
					button->OnHovering_ended();
				}
				//break;// stop loop!, button detected!(only for non overlapping button situation, but...why would there be overlapping situation?)
			}
		};
}


void ConsoleManager::ResizeConsoleWindow()// if the console window size is changed, reposition the scenes

{

}

void ConsoleManager::SetConsoleFonstsize(short int width, short int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo = { 0 };
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// Get current font info
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// Set desired font
	fontInfo.dwFontSize.X = width;   // font width
	fontInfo.dwFontSize.Y = height;  // font height
	wcscpy_s(fontInfo.FaceName, L"Consolas"); // optional: choose a monospaced font

	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void ConsoleManager::SwitchInputmode(Enum_ConsoleMode inputmode)//입력 모드를 주어진 enum으로 변경함
{
	switch (inputmode)
	{
	case KeyboardTypeInMode:
		this->_input_Mode = ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT;// this is default console input mode
		break;
	case MouseClickMode:
		this->_input_Mode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;// and this is for mouse input mode
		break;
	}

	SetConsoleMode(_input_H, _input_Mode);
	_consoleMode = inputmode;//for current enum of input mode
}


void ConsoleManager::ReadMouseInput()// do this after printing is done
{
	if(_mouse!=nullptr)
	_mouse->Start_MouseInputReading();
}

void ConsoleManager::ConsoleWindowResizing()// maximize the scale of console window
{
	_consoleWindow = GetConsoleWindow();
	_windows_Scale = GetLargestConsoleWindowSize(_output_H);// 현 화면의 최대 크기를 저장

	const short paddingX = 10;
	const short paddingY = 10;
	COORD bufferSize = 
	{
	   static_cast<SHORT>(_windows_Scale.X - paddingX),
	   static_cast<SHORT>(_windows_Scale.Y - paddingY)
	};


	SetConsoleScreenBufferSize(_output_H, bufferSize);//화면 크기를 정해둔 크기로 바꿈

	//_windows_RECT_Corners = { 0, 0, _windows_Scale.X, _windows_Scale.Y };// 화면 코너들의 좌표들을 저장
	_windows_RECT_Corners = { 0, 0, static_cast<short>(_windows_Scale.X-1), static_cast<short>(_windows_Scale.Y - 1) };
	SetConsoleWindowInfo(_output_H, TRUE, &_windows_RECT_Corners);//콘솔창의 info

	ShowWindow(_consoleWindow, SW_MAXIMIZE);//showwnindow_maximize
	BaseFrame::SetScreenLimits(_windows_Scale);// informs base frames the max limit of the projectable area (screen limit)	
}

//// 안씀
//void ConsoleManager::SetDisplacement()
//{
//	
//}
//
//// 안씀
//void ConsoleManager::MouseinputReader(COORD mouse_coord)
//{
//	if (_currentDisplay == nullptr) return;
//
//	for (Button* button : _currentDisplay->GetButtons())
//	{
//		if (button->IsDetected(mouse_coord))
//		{
//
//		}
//	}
//}


ConsoleManager::~ConsoleManager()
{
	delete _mouse;
	delete _printer;
	SwitchInputmode(KeyboardTypeInMode);// before dying, set to default console input
}

//void ConsoleManager::FillConsoleWithDot()
//{
//	const COORD screenLimit = BaseFrame::GetScreenLimits();
//	const short paddingX = 10;
//	const short paddingY = 10;
//
//	const short startX = paddingX / 2;
//	const short startY = paddingY / 2;
//	const short endX = screenLimit.X - (paddingX / 2);
//	const short endY = screenLimit.Y - (paddingY / 2);
//
//	DWORD charsWritten;
//
//	std::string line(endX - startX, '.'); // line length = padded width
//
//	for (short y = startY; y < endY; ++y)
//	{
//		COORD pos = { startX, y };
//		WriteConsoleOutputCharacterA(_output_H, line.c_str(), line.size(), pos, &charsWritten);
//	}
//}


void ConsoleManager::Update()
{
	if (!_currentDisplay || !_printer) return;// nothing to print or cannot print

	// update the scene first
	_final_Scene = _printer->MergeDisplay(_currentDisplay);
	_printer->PrintFrame(_final_Scene);// print out the updated scene

	if (_mouse != nullptr)
	{
		_mouse->Start_MouseInputReading();
	}

}

void ConsoleManager::Run_Update()
{
	_isrunning = true;
	while (_isrunning)
	{
		Update();
		Sleep(30);//frame rate of the update
	}
}

void ConsoleManager::Pause_Update()
{
	_isrunning = false;
}

void ConsoleManager::SetCurrentDisplay(Display* _disp)
{
	_currentDisplay = _disp;
}
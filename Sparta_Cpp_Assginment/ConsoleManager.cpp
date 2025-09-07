#include "ConsoleManager.h"
#include <string>

ConsoleManager::ConsoleManager()
	:_input_H(GetStdHandle(STD_INPUT_HANDLE))
	,_output_H(GetStdHandle(STD_OUTPUT_HANDLE))// input, ouput handle설정
{
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

void ConsoleManager::ResizeConsoleWindow()
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

void ConsoleManager::SetDisplacement()
{
	
}

void ConsoleManager::MouseinputReader(COORD mouse_coord)
{
	if (_currentDisplay == nullptr) return;

	for (Button* button : _currentDisplay->GetButtons())
	{
		if (button->IsDetected(mouse_coord))
		{

		}
	}
}


ConsoleManager::~ConsoleManager()
{
	delete _mouse;
	delete _printer;
	SwitchInputmode(KeyboardTypeInMode);// before dying, set to default console input
}

void ConsoleManager::FillConsoleWithDot()
{
	const COORD screenLimit = BaseFrame::GetScreenLimits();
	const short paddingX = 10;
	const short paddingY = 10;

	const short startX = paddingX / 2;
	const short startY = paddingY / 2;
	const short endX = screenLimit.X - (paddingX / 2);
	const short endY = screenLimit.Y - (paddingY / 2);

	DWORD charsWritten;

	std::string line(endX - startX, '.'); // line length = padded width

	for (short y = startY; y < endY; ++y)
	{
		COORD pos = { startX, y };
		WriteConsoleOutputCharacterA(_output_H, line.c_str(), line.size(), pos, &charsWritten);
	}
}
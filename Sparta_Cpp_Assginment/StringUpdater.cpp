#include "StringUpdater.h"

StringUpdater::StringUpdater(COORD start_coord, short int color) :_typed_string{ "" }
{
	this->_cursorPosition = start_coord;
	this->_output_H = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_text_color = color;
	this->_isLineChanged = false;

	//시작지점 설정
	SetConsoleCursorPosition(_output_H, start_coord);
}

StringUpdater::StringUpdater(COORD start_coord)
{
	this->_cursorPosition = start_coord;
	this->_output_H = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_text_color = 7;
	this->_isLineChanged = false;

	//시작지점 설정
	SetConsoleCursorPosition(_output_H, start_coord);
}

void StringUpdater::ResetCoord(COORD newcoord)
{
	this->_cursorPosition = newcoord;
}

COORD StringUpdater::GetCoord()
{
	return _cursorPosition;
}

void StringUpdater::SetTextColor(short int new_color)
{
	this->_text_color= new_color;
}


void StringUpdater::CleanStrings()
{
	for (int length : _str_lengths)//이전 입력된 string의 열만큼 반복
	{
		for (int i = 0; i < length; i++)
		{
			printf(" ");//이전 출력을 " "를 덮어 씌워서 지움
		}
		//해당 줄 지우기 완료
		SetConsoleTextAttribute(_output_H, 7);
		SetConsoleCursorPosition(_output_H,_cursorPosition);//다음 줄 시작 좌표를 (x, y+1)로 두고 다시 출력 시작
	}
}

void StringUpdater::StringUpdate(const string& _typed_string)
{

	if(!_isLineChanged)CleanStrings();// 이전 string지우고 출력

	SetConsoleTextAttribute(_output_H, _text_color);//출력 색상 설정
	//int=line_length;
	for (int i = 0; i < _typed_string.length();i++)//string에서 '\n' 발견 시에 줄 바꾸기// edited--> no string  has endl and continue writing
	{
		/*
		if(_typed_string[i] != '\n')
		{
			printf("%c", _typed_string[i]);
			line_length++;
		}
		else
		{
			_str_lengths.push_back(line_length);// store the length of actual string
			line_length=0;
			_cursorPosition = { _cursorPosition.X, static_cast<short>(_cursorPosition.Y + 1) };// line change
			SetConsoleCursorPosition(_output_H, _cursorPosition);

		}
		*///--> cannot type or put 

		printf("%c", _typed_string[i]);
		_str_lengths.push_back(i);// store the length of actual string	
	}

	SetConsoleTextAttribute(_output_H, 7);//default로 되돌리기
	this->_isLineChanged = false;
}

void StringUpdater::NextLine()
{
	_cursorPosition = { _cursorPosition.X, ++_cursorPosition.Y }; //change Y coord to change the line// coord can be incremented ++
	SetConsoleCursorPosition(_output_H, _cursorPosition);
	this->_isLineChanged = true;// set this to be true
}


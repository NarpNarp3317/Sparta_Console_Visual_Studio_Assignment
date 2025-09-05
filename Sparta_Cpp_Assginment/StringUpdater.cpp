#include "StringUpdater.h"

StringUpdater::StringUpdater(COORD start_coord, short int color) :_typed_string{ "" }
{
	this->_cursorPosition = start_coord;
	this->_output_H = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_text_color = color;
	this->_isLineChanged = false;

	//�������� ����
	SetConsoleCursorPosition(_output_H, start_coord);
}

StringUpdater::StringUpdater(COORD start_coord)
{
	this->_cursorPosition = start_coord;
	this->_output_H = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_text_color = 7;
	this->_isLineChanged = false;

	//�������� ����
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
	for (int length : _str_lengths)//���� �Էµ� string�� ����ŭ �ݺ�
	{
		for (int i = 0; i < length; i++)
		{
			printf(" ");//���� ����� " "�� ���� ������ ����
		}
		//�ش� �� ����� �Ϸ�
		SetConsoleTextAttribute(_output_H, 7);
		SetConsoleCursorPosition(_output_H,_cursorPosition);//���� �� ���� ��ǥ�� (x, y+1)�� �ΰ� �ٽ� ��� ����
	}
}

void StringUpdater::StringUpdate(const string& _typed_string)
{

	if(!_isLineChanged)CleanStrings();// ���� string����� ���

	SetConsoleTextAttribute(_output_H, _text_color);//��� ���� ����
	//int=line_length;
	for (int i = 0; i < _typed_string.length();i++)//string���� '\n' �߰� �ÿ� �� �ٲٱ�// edited--> no string  has endl and continue writing
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

	SetConsoleTextAttribute(_output_H, 7);//default�� �ǵ�����
	this->_isLineChanged = false;
}

void StringUpdater::NextLine()
{
	_cursorPosition = { _cursorPosition.X, ++_cursorPosition.Y }; //change Y coord to change the line// coord can be incremented ++
	SetConsoleCursorPosition(_output_H, _cursorPosition);
	this->_isLineChanged = true;// set this to be true
}


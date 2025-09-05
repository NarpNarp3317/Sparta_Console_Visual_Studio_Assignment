#pragma once
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class StringUpdater
{
public: 
	StringUpdater(COORD start_coord,short int color);// console 출력 시작부분 설정
	StringUpdater(COORD start_coord);// 컬러 설정없는 default white color

private:
	COORD _cursorPosition;//출력 시작부분
	string _typed_string;// 입력된 
	vector<int> _str_lengths;//이전 (string들의 길이 저장 1열, 2열, 3열의 줄 길이)//--> 만약 \n이 실행되었을 시에는 1열만
	HANDLE _output_H;//좌표 설정
	short int _text_color;// 출력하는 텍스트의 컬러 설정
	bool _isLineChanged;//print out next string without cleaning up prior text


public:

	void ResetCoord(COORD newcoord);//시작지점 재설정
	COORD GetCoord();// 시작지점 좌표 찾기
	void SetTextColor(short int new_color);//텍스트 컬러 변경


	void CleanStrings();//이전의 출력들을 지우고 다음 stringupdate를 준비
	void StringUpdate(const string& _typed_string);//입력된 string 설정된 위치에 출력
	void NextLine();

};



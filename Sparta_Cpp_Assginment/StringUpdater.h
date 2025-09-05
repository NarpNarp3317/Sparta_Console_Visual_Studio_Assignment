#pragma once
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class StringUpdater
{
public: 
	StringUpdater(COORD start_coord,short int color);// console ��� ���ۺκ� ����
	StringUpdater(COORD start_coord);// �÷� �������� default white color

private:
	COORD _cursorPosition;//��� ���ۺκ�
	string _typed_string;// �Էµ� 
	vector<int> _str_lengths;//���� (string���� ���� ���� 1��, 2��, 3���� �� ����)//--> ���� \n�� ����Ǿ��� �ÿ��� 1����
	HANDLE _output_H;//��ǥ ����
	short int _text_color;// ����ϴ� �ؽ�Ʈ�� �÷� ����
	bool _isLineChanged;//print out next string without cleaning up prior text


public:

	void ResetCoord(COORD newcoord);//�������� �缳��
	COORD GetCoord();// �������� ��ǥ ã��
	void SetTextColor(short int new_color);//�ؽ�Ʈ �÷� ����


	void CleanStrings();//������ ��µ��� ����� ���� stringupdate�� �غ�
	void StringUpdate(const string& _typed_string);//�Էµ� string ������ ��ġ�� ���
	void NextLine();

};



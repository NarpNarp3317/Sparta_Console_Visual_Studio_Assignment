#pragma once
#include "TextPixel.h"
#include "PivotPoint.h"
#include <vector>
#include <Windows.h>

using namespace std;


class BaseFrame
{
public:
	BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width, COORD offset);//offset�� �ְ� frame�� ����
	BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width);//�־��� Ÿ�Կ� ���� ������ ����

private:
	int _layerPriority;//layer����
	
	COORD _width_XY;
	PivotPoiontLocation _anchor_type;// top left, midle center, middle right....

	vector<vector<TextPixel>> _frame;//
	//vector<vector<bool>> _alpha;// �ȼ��� �����ϴ� ���� right�� ����//Ŭ�� ������ ���� ����//������ �������� �ִ� ������ ���� �Ǵ°ɷ�
	
	COORD _pivotPoint;//pivot point(anchor point)�� �Ǵ� ���� ��ǥ
	COORD _offset;// by adding the offset, reposition the frame

public:
	void GenerateFrame();//����� ������ �������� ������

};
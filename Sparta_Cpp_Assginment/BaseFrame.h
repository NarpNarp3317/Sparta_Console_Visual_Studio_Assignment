#pragma once
#include "TextPixel.h"
#include "PivotPoint.h"
#include <vector>
#include <Windows.h>

using namespace std;


class BaseFrame
{
public:
	BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width, COORD offset);//offset을 주고 frame을 생성
	BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width);//주어진 타입에 맞춰 프레임 생성

private:
	int _layerPriority;//layer순서
	
	COORD _width_XY;
	PivotPoiontLocation _anchor_type;// top left, midle center, middle right....

	vector<vector<TextPixel>> _frame;//
	//vector<vector<bool>> _alpha;// 픽셀이 존재하는 곳을 right로 저장//클릭 가능한 곳을 저장//지금은 프레임이 있는 범위는 전부 되는걸로
	
	COORD _pivotPoint;//pivot point(anchor point)가 되는 곳의 좌표
	COORD _offset;// by adding the offset, reposition the frame

public:
	void GenerateFrame();//변경된 정보로 프레임을 생성함

};
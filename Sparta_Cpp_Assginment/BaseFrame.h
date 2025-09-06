#pragma once
#include "Scene.h"
#include "PivotPoint.h"
#include <vector>
#include <Windows.h>

using namespace std;


class BaseFrame
{
public:
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset);//offset�� �ְ� frame�� ����
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width);//�־��� Ÿ�Կ� ���� ������ ����



//protected: //--> nah, ill use getter function. seems right

private:
//protected://--> just use getter function
	//bool isclampable;// if the frame is out of full size of console screen, it could be not generated or get clamped. this bool decides the obj's condition
	// --> not done yet

	int _layerPriority;//layer����
	short int _frame_color;// frame color
	
	COORD _width_XY;
	PivotPoiontLocation _anchor_type;// top left, midle center, middle right....

	Scene _frame;//
	COORD _print_start;
	//vector<vector<bool>> _alpha;// �ȼ��� �����ϴ� ���� true�� ����//Ŭ�� ������ ���� ����?//������ �������� �ִ� ������ ���� �Ǵ°ɷ�
	//  ---> by only reading the _frame, this wont be necessary for now
	//--------> yes this will be used but not in here, but in scene struct
	
	//COORD _pivotPoint;//pivot point(anchor point)�� �Ǵ� ���� ��ǥ
	//edited ----> coord is already decided by the enum PivotPoiontLocation. additional movement can be adjusted by offset

	COORD _offset;// by adding the offset, reposition the frame

	static COORD _screen_Limit;// all shared by same class
	


public:

	void CalulatePrintStartCoord(PivotPoiontLocation anchor_type);// printring starts from the top left corner, this coord will be calculated based on the anchor type of frame

	COORD GetPrintStartCoord();
	COORD GetWidthXY();
	const Scene& GetFramePtr();


	void GenerateFrame();//����� ������ �������� ������

	static void SetScreenLimits(COORD limit_area);
	static COORD GetScreenLimits();

	

};
#pragma once
#include "Scene.h"
#include "PivotPoint.h"
#include "Enum_FrameType.h"
#include <vector>
#include <Windows.h>


using namespace std;


class BaseFrame
{
public:
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_Style);
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_Style);
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset);//offset�� �ְ� frame�� ����
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width);//�־��� Ÿ�Կ� ���� ������ ����

protected:
//private:

	// bool isclampable;// if the frame is out of full size of console screen, it could be not generated or get clamped. this bool decides the obj's condition
	// --> not done yet
	int _layerPriority;//layer����
	short int _frame_color;// frame color
	
	COORD _width_XY;
	PivotPoiontLocation _anchor_type;// top left, midle center, middle right....

	Scene _frame;//
	COORD _print_start;
	COORD _offset;// by adding the offset, reposition the frame
	COORD print_start_coord;

	static COORD _screen_Limit;// all shared by same class

	Scene _visual;//frame // could this be a texture?
	FrameStyle _frame_style;// look of frame
	Scene _texture;// the texture content of the frame
	
	//vector<vector<bool>> _alpha;// �ȼ��� �����ϴ� ���� true�� ����//Ŭ�� ������ ���� ����?//������ �������� �ִ� ������ ���� �Ǵ°ɷ�
	//  ---> by only reading the _frame, this wont be necessary for now
	//--------> yes this will be used but not in here, but in scene struct
	
	//COORD _pivotPoint;//pivot point(anchor point)�� �Ǵ� ���� ��ǥ
	//edited ----> coord is already decided by the enum PivotPoiontLocation. additional movement can be adjusted by offset	


public:
	void CalculatePrintStartCoord(PivotPoiontLocation anchor_type);// printring starts from the top left corner, this coord will be calculated based on the anchor type of frame

	COORD GetPrintStartCoord();
	COORD GetWidthXY();
	// const Scene& GetFramePtr();
	Scene* GetFramePtr();
	Scene* GetTexturePtr();// get what's inside the frame

	void SetPicture(const Scene& new_picture);// set whats in side the frame
	
	bool IsOuterFrameVisible();// for merging, check if the frame style is no line, so that it can decide the range of the merged scene(if visual frame ---> 1 less, else as its width)


	void GenerateFrame();//����� ������ �������� ������
	//void FillAlpha();// for button, fill all with true so that button can be detected

	static void SetScreenLimits(COORD limit_area);
	static COORD GetScreenLimits();

	

};
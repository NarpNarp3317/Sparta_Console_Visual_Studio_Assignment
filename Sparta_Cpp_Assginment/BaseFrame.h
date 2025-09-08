#pragma once
#include "Scene.h"
#include "PivotPoint.h"
#include "Enum_FrameType.h"
#include "Enum_Text_Color.h"
#include <vector>
#include <Windows.h>


using namespace std;


class BaseFrame
{
public:
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_Style, Text_Color text_color, Text_Color bg_color);
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_Style, Text_Color text_color, Text_Color bg_color);
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, Text_Color text_color, Text_Color bg_color);//offset을 주고 frame을 생성
	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, Text_Color text_color, Text_Color bg_color);//주어진 타입에 맞춰 프레임 생성

protected:
//private:

	// bool isclampable;// if the frame is out of full size of console screen, it could be not generated or get clamped. this bool decides the obj's condition
	// --> not done yet
	int _layerPriority;//layer순서
	short int _text_color;// frame color
	
	COORD _width_XY;
	PivotPoiontLocation _anchor_type;// top left, midle center, middle right....

	COORD _print_start;
	COORD _offset;// by adding the offset, reposition the frame
	COORD print_start_coord;

	static COORD _screen_Limit;// all shared by same class

	FrameStyle _frame_style;// look of frame
	Scene _texture;// the texture content of the frame
	
	//vector<vector<bool>> _alpha;// 픽셀이 존재하는 곳을 true로 저장//클릭 가능한 곳을 저장?//지금은 프레임이 있는 범위는 전부 되는걸로
	//  ---> by only reading the _frame, this wont be necessary for now
	//--------> yes this will be used but not in here, but in scene struct
	
	//COORD _pivotPoint;//pivot point(anchor point)가 되는 곳의 좌표
	//edited ----> coord is already decided by the enum PivotPoiontLocation. additional movement can be adjusted by offset	


public:
	void CalculatePrintStartCoord(PivotPoiontLocation anchor_type);// printring starts from the top left corner, this coord will be calculated based on the anchor type of frame

	COORD GetPrintStartCoord();
	COORD GetWidthXY();
	// const Scene& GetFramePtr();

	Scene* GetTexturePtr();// get what's inside the frame

	void SetPicture(const Scene& new_picture);// set whats in side the frame
	
	bool IsOuterFrameVisible();// for merging, check if the frame style is no line, so that it can decide the range of the merged scene(if visual frame ---> 1 less, else as its width)


	void GenerateEmptyScene();//make a holder for the new texture
	//void FillAlpha();// for button, fill all with true so that button can be detected

	static void SetScreenLimits(COORD limit_area);
	static COORD GetScreenLimits();

	

};
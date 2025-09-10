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
	// default frame, anchor point based on max screen width

	BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_Style, Text_Color text_color, Text_Color bg_color, COORD custom_area);
	// custom area for anchor point
	
	 
	//BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_Style, Text_Color text_color, Text_Color bg_color); 
	// always put offset and frame style --> it seems too much to read
	//BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, Text_Color text_color, Text_Color bg_color);//offset을 주고 frame을 생성
	//BaseFrame(int priority, PivotPoiontLocation anchor_type, COORD width, Text_Color text_color, Text_Color bg_color);//주어진 타입에 맞춰 프레임 생성

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

	//COORD _limit_area;// frame can now use custom area for the limit.

	static COORD _screen_Limit;// all shared by same class

	FrameStyle _frame_style;// look of frame
	Scene _texture;// the texture content of the frame
	Scene* _texturePtr;// this is for later when the scene gets switched, it would be inefficient to put new value to texture everytime when texture is switched
	//----> so make a ptr for a real texture and when the switch happens, change the address in ptr and send it to caller.(like iterator)
	

public:
	void CalculatePrintStartCoord(PivotPoiontLocation anchor_type);// printring starts from the top left corner, this coord will be calculated based on the anchor type of frame
	void CalculatePrintStartCoord_In_Range(PivotPoiontLocation anchor_type, COORD area);// anchor point not based by full screen but custom range
																						//---> so that sub buttons can be anchored in popout frame

	COORD GetPrintStartCoord();
	COORD GetWidthXY();
	// const Scene& GetFramePtr();

	Scene* GetTexturePtr();// get what's inside the frame
	void SwitchTexturePtr(Scene* switched_texturePtr);// switch the address of the texture

	void SetPicture(Scene* new_picture);// set whats in side the frame
	
	bool IsOuterFrameVisible();// for merging, check if the frame style is no line, so that it can decide the range of the merged scene(if visual frame ---> 1 less, else as its width)


	
	//void FillAlpha();// for button, fill all with true so that button can be detected

	static void SetScreenLimits(COORD limit_area);
	static COORD GetScreenLimits();

	

};
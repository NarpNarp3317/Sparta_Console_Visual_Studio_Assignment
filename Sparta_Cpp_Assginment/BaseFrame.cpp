#include "BaseFrame.h"

BaseFrame::BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width, COORD offset)// offset 과 함께 생성
{
}

BaseFrame::BaseFrame(int priority, COORD anchor_location, PivotPoiontLocation anchor_type, COORD width)//offset 없이 생성
{
}





//void BaseFrame::GenerateFrame()
//{
//	short int x = _width_XY.X;
//	short int y = _width_XY.Y;
//	short int off_x=
//
//	if (x >= 2 || y >= 2)// the frame needs to be at least bigger than 2*2 so that corner can be made
//	{
//		//well, unsigend char can be set with number, not only hexcode!!
//		Frame[0][0] = T_Pixel{ frame_color,201 };        // top-left ╔
//		Frame[0][x - 1] = T_Pixel{ frame_color,187 };    // top-right ╗
//		Frame[y - 1][0] = T_Pixel{ frame_color,200 };    // bottom-left ╚
//		Frame[y - 1][x - 1] = T_Pixel{ frame_color,188 };// bottom-right ╝
//
//		// now for ║, ═
//		for (int i = 1; i < x - 1; i++)//first and last on top and bottom is corners
//		{
//			Frame[0][i] = T_Pixel{ frame_color, 205 }; // top ═
//			Frame[y - 1][i] = T_Pixel{ frame_color, 205 }; // bottom ═
//		}
//		for (int j = 1; j < y - 1; j++)//same here
//		{
//			Frame[j][0] = T_Pixel{ frame_color, 186 }; // left ║
//			Frame[j][x - 1] = T_Pixel{ frame_color, 186 }; // right ║
//		}
//	}
//
//}

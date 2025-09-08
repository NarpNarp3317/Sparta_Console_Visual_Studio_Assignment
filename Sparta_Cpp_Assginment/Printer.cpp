#include "Printer.h"
#include <algorithm>// for layer sorting

Printer::Printer(HANDLE output_handle):_output_H{ output_handle }, _previous_Scene{nullptr}
{
}

bool Printer::CompareLayerPriority(Scene* A, Scene* B)
{
	return A->_layer_priority < B->_layer_priority;// lower priority on top
}

Scene Printer::MergeLayers(const vector<Scene*>& scenes)
{
	COORD Max_screensize = BaseFrame::GetScreenLimits();

	Scene merged;//empty
	if(scenes.empty()) return Scene();
	;
	// make empty canvas
	merged._layer_priority = 0;//the final print
	merged._T_Pixel_frame.assign(Max_screensize.Y, vector<T_Pixel>(Max_screensize.X, T_Pixel{ 7,' ' }));//make empty layer with ' ', size of full screen
	merged._alpha.assign(Max_screensize.Y, vector<bool>(Max_screensize.X, false));// make empty "empty" alpha screen
	// merge layers and make it into one layer of frame

	vector<Scene*> sortedS = scenes;// for sorting
	sort(sortedS.begin(), sortedS.end(), CompareLayerPriority);


	for (Scene* current_S : sortedS)// for every layers
	{
		for (int y = 0; y < current_S->_T_Pixel_frame.size(); ++y)
		{
			for (int x = 0; x < current_S->_T_Pixel_frame[y].size(); ++x)
			{
				
				if (current_S->_alpha[y][x])// if there is a char to be sorted
				{
					merged._T_Pixel_frame[y][x] = current_S->_T_Pixel_frame[y][x];
					merged._alpha[y][x] = true;
				}
				//skip the ' '
			}
		}
	}

	return merged;
}
/*
Scene Printer::MergeDisplay(Display* display)
{
	if (!display) return Scene();// return empty scene

	vector<Scene*> display_layers;//empty storage

	display_layers.push_back(display->GetFramePtr());// frame of display

	for (Button* button : display->GetInteractables())// add all buttons
	{
		display_layers.push_back(button->GetFramePtr());
	}

	return MergeLayers(display_layers);// send it to the merge function and return scene
}
*/ //-----> this was only out frames at 00, print start was not considered in this code

Scene Printer::MergeDisplay(Display* display)
{
	Scene merged;

	if (!display) return merged;

	Scene* base = display->GetTexturePtr(); // start with display frame
	if(base==nullptr) return merged;// if display base frame is invalid// the cunstructor generate it at the beginning but just in case

	merged = *base;
	COORD display_range = display->GetWidthXY();
	bool isFrameVisible=display->IsOuterFrameVisible();

	for (Button* button : display->GetInteractables())
	{
		Scene* button_scene = button->GetTexturePtr();
		// Scene* button_scene = button->GetTexturePtr();
		if (button_scene == nullptr) continue;// if button scene is empty, skip

		COORD start = button->GetPrintStartCoord();// this was essentiall!!!
		COORD button_width = button->GetWidthXY();// get range


		for (int y = 0; y < button_width.Y; y++)
		{
			for (int x = 0; x < button_width.X; x++)
			{
				int mergedY = start.Y + y;
				int mergedX = start.X + x;

				if (button_scene->_alpha[y][x] != true) continue;

				if (isFrameVisible)// i know it can be improved but it just works. improve it later// basically, deciding the range 
				{

					if (mergedX <1 || mergedX > display_range.X-2) continue;
					if (mergedY <1 || mergedY > display_range.Y-2) continue;

					merged._T_Pixel_frame[mergedY][mergedX] = button_scene->_T_Pixel_frame[y][x];
					merged._alpha[mergedY][mergedX] = true;
				}
				else
				{
					if (mergedX <0 || mergedX >= display_range.X) continue;
					if (mergedY <0 || mergedY >= display_range.Y) continue;

					merged._T_Pixel_frame[mergedY][mergedX] = button_scene->_T_Pixel_frame[y][x];
					merged._alpha[mergedY][mergedX] = true;
				}	
			}
		}
	}
	return merged;
}

void Printer::PrintFrame(const Scene& scene)
{
	COORD position{0,0};

	for (int y = 0; y < scene._T_Pixel_frame.size(); ++y)
	{
		position.Y = static_cast<short>(y);

		for (int x = 0; x < scene._T_Pixel_frame[y].size(); ++x)
		{
			position.X = static_cast<short>(x);
			const T_Pixel& current_P = scene._T_Pixel_frame[y][x];

			if (current_P.Pixel != ' ')// now thanks to writeconsoleA, does not have to write ' ' before printing char in coord above 0,0
			{
				SetConsoleCursorPosition(_output_H, position);
				SetConsoleTextAttribute(_output_H, current_P.color);
				WriteConsoleA(_output_H, &current_P.Pixel, 1, nullptr, nullptr);//handle, char ptr, number of char to print, recieve number of written char(optional), idk, it's here...?)
				//reference:
				//https://learn.microsoft.com/ko-kr/windows/console/writeconsole
				//**** == writeconsoleA can print multiple chars as string at once, without loop computation!!!!! ---> this could improve the speed of printing!!!!!
				// todo--> get more info
			}
		}
	}
}

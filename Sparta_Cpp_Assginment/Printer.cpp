#include "Printer.h"
#include <algorithm>// for layer sorting

Printer::Printer(HANDLE output_handle):_output_H{ output_handle }, _previous_Scene{}, _hasPrintedOnce{false}// it did not printed in the beginning
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

Scene Printer::MergeLayout(Layout* layout)
{
	Scene merged;

	if (!layout) return merged;

	Scene* base = layout->GetTexturePtr(); // start with display frame
	if(base==nullptr) return merged;// if display base frame is invalid// the cunstructor generate it at the beginning but just in case

	merged = *base;
	COORD display_range = layout->GetWidthXY();
	bool isFrameVisible=layout->IsOuterFrameVisible();

	for (Button* button : layout->GetInteractables())
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
				}
				else
				{
					if (mergedX <0 || mergedX >= display_range.X) continue;
					if (mergedY <0 || mergedY >= display_range.Y) continue;
				}
				merged._T_Pixel_frame[mergedY][mergedX] = button_scene->_T_Pixel_frame[y][x];
				merged._alpha[mergedY][mergedX] = true;
			}
		}
	}
	return merged;
}

void Printer::PrintScene(const Scene& scene)// this one is only printing the texture
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
	_hasPrintedOnce = true;
}

void Printer::PrintLayout(Layout* layout)
{
	if (layout == nullptr) return;

	Scene merged = MergeLayout(layout);
	PrintScene(merged);

	_previous_Scene = merged;
}

void Printer::PrintPartialUpdates(Layout* layout)// compare the difference and print the new one only
{
	if (layout == nullptr) return;

	if (!_hasPrintedOnce)// if printer did not printed
	{
		PrintLayout(layout);// print all
		return;
	}

	Scene merged = MergeLayout(layout);


	//====== Partioal Print ======//
    COORD print_start{0,0};

    for (int y = 0; y < merged._T_Pixel_frame.size(); ++y)
    {
        for (int x = 0; x < merged._T_Pixel_frame[y].size(); ++x)
        {
            const T_Pixel& current_T_Pixel = merged._T_Pixel_frame[y][x];
            const T_Pixel& previous_T_Pixel  = _previous_Scene._T_Pixel_frame[y][x];

            if (current_T_Pixel.Pixel != previous_T_Pixel.Pixel || current_T_Pixel.color != previous_T_Pixel.color)// check if both are different
            {
                print_start.X = static_cast<short>(x);
                print_start.Y = static_cast<short>(y);

                SetConsoleCursorPosition(_output_H, print_start);
                SetConsoleTextAttribute(_output_H, current_T_Pixel.color);
                WriteConsoleA(_output_H, &current_T_Pixel.Pixel, 1, nullptr, nullptr);
            }
        }
    }
	_hasPrintedOnce = true;// check did printed

    // update previous Scene
    _previous_Scene = merged;
}

void Printer::ResetPrintRecord()
{
	_hasPrintedOnce = false;// printed more than once
}

bool Printer::GetPrintRecord()
{
	return _hasPrintedOnce;
}

#pragma once
#include <vector>
#include "BaseFrame.h"
#include "TextPixel.h"
#include "Scene.h"
#include "Button.h"
#include "Layout.h"



class Printer
{
public:
	Printer(HANDLE output_handle);


private:
	HANDLE _output_H;
	
	Scene* _previous_Scene;//store prvious scene and find newly updated area by comapring alphas of new and this(previous) layers
	static bool CompareLayerPriority(Scene* A, Scene* B);

public:

	Scene MergeLayers(const vector<Scene*>& scenes);

	void PrintFrame(const Scene& scene);// read the scene and print out on display
	Scene MergeDisplay(Layout* display);

};
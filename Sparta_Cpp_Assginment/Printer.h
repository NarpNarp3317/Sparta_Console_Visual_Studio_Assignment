#pragma once
#include <vector>
#include <map>
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
	bool _hasPrintedOnce;// checking for do once
	HANDLE _output_H;
	
	Scene _previous_Scene;//store prvious scene and find newly updated area by comapring alphas of new and this(previous) layers

	Scene _background_Scene;// for printing display. elements print over the background
	std::map< int, Scene* > _previous_elements;//key= priority or id, textures of elements(not only buttons but every updatable scenes)

	static bool CompareLayerPriority(Scene* A, Scene* B);

public:

	Scene MergeLayers(const vector<Scene*>& scenes);
	Scene MergeLayout(Layout* display);

	void PrintScene(const Scene& scene);// read the scene and print out on display
	void PrintLayout(Layout* display);
	void PrintPartialUpdates(Layout* display);// only print on updated area

	void ResetPrintRecord();// set did printed to false
	bool GetPrintRecord();
};
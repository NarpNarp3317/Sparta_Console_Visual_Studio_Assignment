#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Scene.h"
#include "Enum_FrameType.h"
#include "PivotPoint.h"
#include "Enum_Text_Color.h"

/*
this is for generating 2d vector of T-Pixels and alpha from empty scene obj.
functions
1. make frame
2. fill color// fill scene with colors
3. change all color// as one color
4. invert color // only for full color
5. export the scene// no need, it will modify the imported scene directly

// the generative functions will overpaint the previous scene

*/
class SceneMaker
{
public:
	SceneMaker();

private:
	Scene* _scene;
	COORD _width_XY;

public:
	void ImportScene(Scene* scene, COORD width_XY, COORD offset);

	void AddTexts(std::vector<std::string> Texts, PivotPoiontLocation anchor_type, COORD offset, Text_Color text_color, Text_Color background_color);

	void AddFrame(FrameStyle style, Text_Color text_color, Text_Color background_color);

	//Scene ExportScene();

	void ChangeWholeColor(Text_Color text_color, Text_Color background_color);

	void Switch_Text_BG_Colors();

	short int FindColorCode(Text_Color text_color, Text_Color background_color);

};
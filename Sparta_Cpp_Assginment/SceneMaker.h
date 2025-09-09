#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Scene.h"
#include "Enum_FrameType.h"
#include "PivotPoint.h"
#include "Enum_Text_Color.h"

using namespace std;

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
class SceneMaker// make it into static function
{
	// all needs to get scene ptr and width for argument
public:
	//static void ImportScene(Scene* scene, COORD width_XY, COORD offset);// no longer needed

	static void PrepareCanvas(Scene* scene, COORD width_XY);// assignt un empty 2d vector, like preparing right size of canvas to paint

	static void AddTexts(Scene* scene, COORD width_XY, COORD offset, vector<string> Texts, PivotPoiontLocation anchor_type, Text_Color text_color, Text_Color background_color);

	static void AddTexts_withChosenColor(Scene* scene, COORD width_XY, COORD offset, vector<string> Texts, PivotPoiontLocation anchor_type, short int color);// when the color is already chosen

	static void AddFrame(Scene* scene, COORD width_XY, FrameStyle style, Text_Color text_color, Text_Color background_color);

	static void AddFrame_withChosenColor(Scene* scene, COORD width_XY,  FrameStyle style, short int color);// same here // when the color is already chosen

	//Scene ExportScene();

	static void FillColor(Scene* scene, COORD width_XY, Text_Color text_color, Text_Color background_color);

	static void FillChars(Scene* scene, COORD width_XY, unsigned char text,Text_Color text_color, Text_Color background_color);

	static void ChangeWholeColor(Scene* scene, COORD width_XY, Text_Color text_color, Text_Color background_color);

	static void Switch_Text_BG_Colors(Scene* scene, COORD width_XY);

	static short int FindColorCode(Text_Color text_color, Text_Color background_color);

};
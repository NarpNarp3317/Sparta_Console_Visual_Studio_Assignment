#pragma once

#include <vector>
#include "TextPixel.h"


struct Scene
{
	int _layer_priority;
	std::vector<std::vector<T_Pixel>> _T_Pixel_frame;
	std::vector<std::vector<bool>> _alpha;
};
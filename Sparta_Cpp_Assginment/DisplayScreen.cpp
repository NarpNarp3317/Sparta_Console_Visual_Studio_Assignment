#include "DisplayScreen.h"
#include "BaseFrame.h"
#include <vector>
/*
DisplayScreen does not merge the elements as one Scene.

layer priority
 0: outer frame
 1: effect
 2:...


 m-1:...
 n: background 



*/

class DisplayScreen :public BaseFrame
{
	DisplayScreen();

	Scene _background;

	vector<S




};
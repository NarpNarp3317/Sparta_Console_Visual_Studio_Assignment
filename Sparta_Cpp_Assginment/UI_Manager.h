#pragma once
#include "Layout.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

// this will store the layout link them
/*

*/

class UI_Manager
{
public:
	UI_Manager();

private:
	map<char, Layout*> _layout_Lists;	
	Layout* _previous_layout;

public:

	void AddLayout(Layout* newlayout);

	Layout* GetLayout(char key);

	bool Migrate_to_newLayout(char destination);


};
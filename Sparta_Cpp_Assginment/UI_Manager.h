#pragma once
#include "Layout.h"
#include "Enum_Layout.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

// this will store the layout and its addresses to migrate to new layout.
/*

*/

class UI_Manager
{

private:
    // Layouts //

    Layout GameMenu;// start
    Layout LoadGame;// loading new games
    Layout Character_Selection;
    Layout Lounge_Stage;
    Layout Store;
    Layout Battle_Stage;

    Layout Intermission;// layout with plain scene, scene change effect

    map< Enum_Layout, Layout*> layout_List;
    Layout* _precious_Layout;
    Layout* _current_Layout;

    //======== Required Scenes =======// original scene here, delt with pointer

    //=== Layout type ===//
    Scene intermission;// during layout change
    Scene loading;
    Scene victory;
    Scene lost;

    map<string, Scene*> Scene_List;// storage for 

    //=== Props ===//
    Scene potion_bottle;
    Scene weapon;// there could be a type but for now, just one

    //=== extra ====//
    Scene x_button;
    Scene skip_button;

	map<string, Layout*> _layout_Lists;	
	Layout* _previous_layout;

public:

	void AddLayout(Layout* newlayout);

	Layout* GetLayout(Enum_Layout key);

	void Migrate_to_newLayout(Enum_Layout destination);


};
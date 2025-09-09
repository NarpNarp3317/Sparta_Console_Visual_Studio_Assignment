#include "UI_Manager.h"

void UI_Manager::Migrate_to_newLayout(Enum_Layout destination)
{
    map< Enum_Layout, Layout*>::const_iterator it = layout_List.find(destination);
        //layout_List.find()
    if (it != layout_List.end())
    {

    }
}

#pragma once
#include "BaseFrame.h"
#include "Button.h"
#include <vector>
//#include <map>

//Display is a class that store UI elements

class Layout :public BaseFrame
{
public:
    Layout();
    ~Layout();

private:
    //vector<Scene*> _Scenes;// container for textures
    int _button_id_counter;
   vector<Button*> _buttons;// containter for buttonPtrs
    //map<int, Button*> _buttons;

public:
    void AddButton(Button* new_button);

    void RemoveButton(Button* new_button);// remove from the display 

    vector<Button*> GetInteractables();

    /*  void AddScene(Scene* scene);

      vector<Scene*>GetScenes();*/
};
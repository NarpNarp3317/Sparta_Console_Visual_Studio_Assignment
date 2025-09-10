#pragma once
#include "BaseFrame.h"
#include "Button.h"
#include <vector>

//Display is a class that store UI elements

class Layout :public BaseFrame
{
public:
    Layout();
    ~Layout();

private:
    //vector<Scene*> _Scenes;// container for textures

    vector<Button*> _buttons;// containter for buttonPtrs

public:
    void AddButton(Button* new_button);

    vector<Button*> GetInteractables();

  /*  void AddScene(Scene* scene);

    vector<Scene*>GetScenes();*/
};
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"

#define SCENE_SAVE_FILENAME "scenesave.save"
#define SCENE_DIVIDER "@@@"
#define VECTOR_DIVIDER "###"

class SceneSaveAndLoader
{

public:
	bool saveScene(Scene* _scene, std::string _fileName = SCENE_SAVE_FILENAME);
	Scene loadScene(std::string _fileName);
};
#include "SceneSaveAndLoader.h"
#include "Logger.h"


bool SceneSaveAndLoader::saveScene(Scene* _scene, std::string _fileName)
{
	/*
	* 저장할 목록
	int _layer_priority;
	std::vector<std::vector<T_Pixel>> _T_Pixel_frame;
	std::vector<std::vector<bool>> _alpha;
	*/

	std::ofstream saveFile(_fileName);
	if (!saveFile.is_open())
	{
		LOG("SCENE SAVE FILE OPEN FAIL");
		return false;
	}
	saveFile << _scene->_layer_priority << std::endl;
	saveFile << SCENE_DIVIDER << std::endl;
	for (int i = 0; i < _scene->_T_Pixel_frame.size(); i++)
	{
		for (int j = 0; j < _scene->_T_Pixel_frame[i].size(); j++)
		{
			saveFile << std::to_string(_scene->_T_Pixel_frame[i][j].color) << std::endl;
			saveFile << std::to_string(_scene->_T_Pixel_frame[i][j].Pixel) << std::endl;
		}
		saveFile << VECTOR_DIVIDER << std::endl;
	}
	saveFile << SCENE_DIVIDER << std::endl;
	for (int i = 0; i < _scene->_alpha.size(); i++)
	{
		for (int j = 0; j < _scene->_alpha[i].size(); j++)
		{
			saveFile << _scene->_alpha[i][j] << std::endl;
		}
			saveFile << SCENE_DIVIDER << std::endl;
	}
	saveFile << VECTOR_DIVIDER << std::endl;
	saveFile.close();

    LOG("SCENE SAVE COMPLETE");

	return true;
}

Scene SceneSaveAndLoader::loadScene(std::string _fileName)
{
    Scene loadedScene;

    std::ifstream loadFile(_fileName);
    if (!loadFile.is_open())
    {
        LOG("SCENE LOAD FILE OPEN FAIL");
        return loadedScene;
    }

    std::string line;
    std::string divider;

    std::getline(loadFile, line);
    loadedScene._layer_priority = std::stoi(line);

    std::getline(loadFile, divider);

    loadedScene._T_Pixel_frame.clear(); // Clear any existing data
    while (std::getline(loadFile, line) && line != SCENE_DIVIDER)
    {
        std::vector<T_Pixel> row;
        while (line != VECTOR_DIVIDER)
        {
            T_Pixel pixel;

            pixel.color = std::stoi(line);
            std::getline(loadFile, line);
            pixel.Pixel = static_cast<unsigned char>(std::stoi(line));

            row.push_back(pixel);
            if (!std::getline(loadFile, line)) break;
        }
        loadedScene._T_Pixel_frame.push_back(row);
    }

    loadedScene._alpha.clear(); 
    while (std::getline(loadFile, line) && line != VECTOR_DIVIDER)
    {
        std::vector<bool> row;
        while (line != SCENE_DIVIDER)
        {
            row.push_back(line == "1");

            if (!std::getline(loadFile, line)) break;
        }
        loadedScene._alpha.push_back(row);
    }

    loadFile.close();

    LOG("SCENE LOAD COMPLETE");
    return loadedScene;
}
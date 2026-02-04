//
// Created by tiernux on 02/02/2026.
//
#include "Scenes/Scene.h"
#include "Constants.h"

#include <fstream>
#include <iostream>

Scene::Scene(const std::string &sceneName)
{
    fileName = sceneName;
}

bool Scene::SaveScene(std::unordered_map<std::string,std::string> &data) const //Data is provided and written raw to the location with some predetermined paths
{
    std::string assetString= SCENE_DIRECTORY + fileName + SCENE_FORMAT;
    std::ofstream file(assetString);


    for (auto const& [key, value] : data) {
        file << key << "=" << value << "\n";
    }

    file.close();


    return true;
}

std::unordered_map<std::string, std::string> Scene::LoadScene() const //Attempt to load directory and file, if file doesn't exist return empty Data
{
    std::unordered_map<std::string, std::string> database;
    std::string assetLocation = SCENE_DIRECTORY + fileName + SCENE_FORMAT;
    std::ifstream file(assetLocation);

    if (!file.is_open()) return database;

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter = line.find('=');
        if (delimiter != std::string::npos) {
            std::string key = line.substr(0, delimiter);
            std::string val = line.substr(delimiter + 1);
            database[key] = val;
        }
    }
    return database;
}

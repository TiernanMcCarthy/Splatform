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

bool Scene::SaveScene(std::string data) const //Data is provided and written raw to the location with some predetermined paths
{
    std::string assetString= SCENE_DIRECTORY + fileName + SCENE_FORMAT;
    std::ofstream file(assetString);

    file << data;

    file.close();


    return true;
}

std::unordered_map<std::string, std::string> Scene::LoadScene() const //Attempt to load directory and file, if file doesn't exist return empty Data
{
    std::unordered_map<std::string, std::string> database = std::unordered_map<std::string, std::string> ();

    std::string assetLocation= SCENE_DIRECTORY + fileName + SCENE_FORMAT;

    std::ifstream file(assetLocation);

    if (!file.is_open())
    {
        std::cout<<fileName << " does not exist as a scene on disc"<< std::endl;
        return database;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t fq = line.find("\""), sq = line.find("\"", fq + 1), tq = line.find("\"", sq + 1), lq = line.find("\"", tq + 1);
        if (fq != std::string::npos && lq != std::string::npos && tq > sq) {
            std::string key = line.substr(fq + 1, sq - fq - 1);
            std::string val = line.substr(tq + 1, lq - tq - 1);
            if (key.find(".") != std::string::npos || key.find("Root") == 0 || key == "Scene_RootCount") {
                database[key] = val;
            }
        }
    }

    return database;
}

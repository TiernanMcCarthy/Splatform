//
// Created by tiernux on 01/02/2026.
//
#pragma once
#ifndef SPLATFORM_SCENE_H
#define SPLATFORM_SCENE_H
#include <string>
#include <unordered_map>

//A scene is a reference to a physical file or a file to be made, when a scene is saved every object is serialised and
//the information is saved to file, which should be loaded later
class Scene
{
public:

    std::string fileName;

    //Load data from file and return the database to convert to serialised data
    std::unordered_map<std::string,std::string> LoadScene() const;

    Scene(const std::string &sceneName ="DefaultScene");

    //Save already serialised data to a file, return false if failed.
    bool SaveScene(std::string data) const;






};



#endif // SPLATFORM_SCENE_H


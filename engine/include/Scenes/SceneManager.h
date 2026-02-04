//
// Created by tiernux on 01/02/2026.
//
#pragma once

#ifndef SPLATFORM_SCENEMANAGER_H
#define SPLATFORM_SCENEMANAGER_H
#include <string>
#include <unordered_map>
#include "Objects/EntityID.h"

#include <vector>
class Scene;
class Object;
class GameObject;



class SceneManagement
{
    public:

    static std::unordered_map<EntityID, Object *> objectRegister;

    //holds all gameobjects in the Scene
    static std::vector<GameObject *> gameObjects;

    static Scene* currentScene;

    void Update(float deltaTime);

    SceneManagement();

    static bool SaveCurrentScene();

    // Load a scene from a string, additive not implemented, just thinking ahead. Return false if scene cannot be found
    static bool LoadScene(std::string sceneName, bool additive=false);

    static void AddNewObject(GameObject* newObject,bool useStart=true);

    static void RemoveObject(GameObject* object);

    static void RemoveObjectFromRegister(EntityID id);

    static void ClearDestructionStack();

    /// <summary>
    /// Destroys a GameObject and removes it from the GameObject List
    /// </summary>
    static void Destroy(Object* target);



private:
    //holds all objects that are being destroyed this frame, we need to clear them from the appropriate areas
    static std::vector<Object*> destructionStack;








    private:



};



#endif // SPLATFORM_SCENEMANAGER_H

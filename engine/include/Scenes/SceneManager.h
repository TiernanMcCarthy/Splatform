//
// Created by tiernux on 01/02/2026.
//
#pragma once

#ifndef SPLATFORM_SCENEMANAGER_H
#define SPLATFORM_SCENEMANAGER_H
#include "Objects/EntityID.h"
#include "Objects/Behaviour.h"
#include <string>
#include <unordered_map>
#include <typeinfo>

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
    static void LoadScene(std::string sceneName, bool additive=false);

    static void AddNewObject(GameObject* newObject,bool useStart=true);

    static void RemoveObject(GameObject* object);

    static void RemoveObjectFromRegister(EntityID id);

    static void ClearDestructionStack();

    static void AddBehaviourForStart(Behaviour* behaviour);

    static void ExecuteStart();

    /// <summary>
    /// Destroys a GameObject and removes it from the GameObject List
    /// </summary>
    static void Destroy(Object* target);




    static void SceneStartup();



    template<typename T>
 static std::vector<T*> GetBehavioursOfType()
    {
        std::vector<T*> behaviours;

        for (auto* go : gameObjects)
        {
            for (auto* b : CheckBehaviours(go))
            {
                if (T* casted = dynamic_cast<T*>(b))
                {
                    behaviours.push_back(casted);
                }
            }
        }

        return behaviours;
    }

    template<typename T>
 static T* GetBehaviourOfType()
    {
        for (auto* go : gameObjects)
        {
            for (auto* b : CheckBehaviours(go))
            {
                if (T* casted = dynamic_cast<T*>(b))
                {
                    return casted;
                }
            }
        }

        return nullptr;
    }

private:
    //holds all objects that are being destroyed this frame, we need to clear them from the appropriate areas
    static std::vector<Object*> destructionStack;

    static std::vector<GameObject*> startBuffer;

    static std::vector<Behaviour*> CheckBehaviours(GameObject* object);

    static std::string pendingSceneName;
    static bool loadScene;

    void DeferredLoadScene();










    private:



};



#endif // SPLATFORM_SCENEMANAGER_H

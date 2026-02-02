//
// Created by tiernux on 02/02/2026.
//
#include <Scenes/SceneManager.h>

#include "Objects/GameObject.h"

#include <Scenes/Scene.h>

std::unordered_map<EntityID, Object *> SceneManagement::objectRegister;

//holds all gameobjects in the Scene
std::vector<GameObject *> SceneManagement::gameObjects;

std::vector<Object *> SceneManagement::destructionStack;

SceneManagement::SceneManagement()
{
    currentScene= new Scene();
}

void SceneManagement::Update(float deltaTime)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        //Update all GameObjects
        gameObjects[i]->Update(deltaTime);
    }
}

void SceneManagement::AddNewObject(GameObject *newObject)
{
    gameObjects.push_back(newObject);
    gameObjects[gameObjects.size() - 1]->Start();

}
void SceneManagement::RemoveObject(GameObject *object)
{
    if (object)
    {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), object), gameObjects.end());
    }

}

void SceneManagement::ClearDestructionStack()
{
    Object* targetPointer;
    for (int i = 0; i < destructionStack.size(); i++)
    {
        targetPointer = destructionStack[i];
        targetPointer->OnDestroy();
        delete targetPointer;
    }
    destructionStack.clear();
}

void SceneManagement::Destroy(Object *target)
{
    //Destroy target if it's not a null pointer
    if (target)
    {
        destructionStack.push_back(target);
    }
}

bool SceneManagement::LoadScene(std::string sceneName, bool additive)
{


    return true;
}
//
// Created by tiernux on 02/02/2026.
//
#include <Scenes/SceneManager.h>

#include "BoxRenderer.h"
#include "Constants.h"
#include "Objects/GameObject.h"

#include <Scenes/Scene.h>
#include <fstream>

std::unordered_map<EntityID, Object *> SceneManagement::objectRegister;

//holds all gameobjects in the Scene
std::vector<GameObject *> SceneManagement::gameObjects;

std::vector<Object *> SceneManagement::destructionStack;

std::vector<GameObject*> SceneManagement::startBuffer;

Scene*SceneManagement::currentScene;

bool SceneManagement::loadScene = false;

SceneManagement::SceneManagement()
{
    currentScene= new Scene();

    loadScene = false;
}

void SceneManagement::RemoveObjectFromRegister(EntityID id)
{
    objectRegister.erase(id);
}

void SceneManagement::Update(float deltaTime)
{


    for (int i = 0; i < gameObjects.size(); i++)
    {
        //Update all GameObjects
        gameObjects[i]->CheckActiveState();
        gameObjects[i]->Update(deltaTime);
    }

    if (loadScene)
    {
        DeferredLoadScene();
    }
}

void SceneManagement::AddNewObject(GameObject *newObject,bool useStart)
{
    //startBuffer.push_back(newObject);
    gameObjects.push_back(newObject);
    if (useStart)
    {
        gameObjects[gameObjects.size() - 1]->Start();
    }

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
void SceneManagement::AddBehaviourForStart(Behaviour *behaviour)
{
    //behaviourStartBuffer.push_back(behaviour);
}

void SceneManagement::ExecuteStart()
{

    for (int i=0; i < startBuffer.size(); i++)
    {
        startBuffer[i]->Start();
    }


    startBuffer.clear();
}

bool SceneManagement::SaveCurrentScene() {
    Serializer saver(Mode::Saving);

    // Use a clear, consistent key name
    int count = (int)gameObjects.size();
    saver.Property("Scene_RootCount", count);

    for (int i = 0; i < count; i++) {
        // ENSURE THIS MATCHES THE LOAD EXACTLY
        saver.Property("Root" + std::to_string(i) + "_ID", gameObjects[i]->ObjectID);
    }

    for (auto go : gameObjects) {
        go->Serialize(saver);
    }

    currentScene->SaveScene(saver.database);
    return true;
}


void SceneManagement::DeferredLoadScene()
{
    // Wipe and clear all objects
    for (auto go : gameObjects) delete go;
    gameObjects.clear();
    objectRegister.clear();
    ClearDestructionStack();
    Engine::GEngine->ClearDrawObjects();
    destructionStack.clear();


    //SceneStartup();

    // 2. LOAD FILE
    std::unordered_map<std::string, std::string> db;

    db=currentScene->LoadScene();

    Serializer loader(Mode::Loading);
    loader.database = db;

    // 3. RECONSTRUCT
    int rootCount = 0;
    loader.Property("Scene_RootCount", rootCount);

    for (int i = 0; i < rootCount; i++) {
        EntityID id;
        loader.Property("Root" + std::to_string(i) + "_ID", id);

        // Constructor adds to gameObjects list automatically
        GameObject* go = new GameObject("SerialObject", false);
        go->ForceID(id);
    }

    // 4. DATA INJECTION
    for (int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Serialize(loader);
    }

    loadScene=false;
}



void SceneManagement::LoadScene(std::string sceneName, bool additive)
{
    //delete currentScene;
    currentScene= new Scene(sceneName);

    loadScene=true;

}



void SceneManagement::SceneStartup()
{

    //Create Background
    BoxRenderer* background = (new GameObject("Background"))->AddBehaviour<BoxRenderer>();

    background->depth=-1;

    //Setup Background
    float pixelCount = (DISPLAYWIDTH * DISPLAYHEIGHT)/1.5f;

    float pixelRatio = (pixelCount / (256 * 224));

    background->gameObject->transform.localScale = sf::Vector2f(256*pixelRatio, 224*pixelRatio);

    background->gameObject->transform.SetPosition(DISPLAYWIDTH / 2, DISPLAYHEIGHT / 2);

    background->ApplyImage("assets/flatImage.png");

}
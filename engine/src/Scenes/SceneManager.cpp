//
// Created by tiernux on 02/02/2026.
//
#include <Scenes/SceneManager.h>

#include "Objects/GameObject.h"

#include <Scenes/Scene.h>
#include <fstream>

std::unordered_map<EntityID, Object *> SceneManagement::objectRegister;

//holds all gameobjects in the Scene
std::vector<GameObject *> SceneManagement::gameObjects;

std::vector<Object *> SceneManagement::destructionStack;

Scene*SceneManagement::currentScene;

SceneManagement::SceneManagement()
{
    currentScene= new Scene();
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
        gameObjects[i]->Update(deltaTime);
    }
}

void SceneManagement::AddNewObject(GameObject *newObject,bool useStart)
{
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

bool SceneManagement::SaveCurrentScene()
{
    // 1. Gather all data into the Serializer's database
    Serializer saver(Mode::Saving);
    int count = (int)gameObjects.size();
    saver.Property("Scene_RootCount", count);

    for (int i = 0; i < count; i++) {
        saver.Property("Root" + std::to_string(i) + "_ObjectID", gameObjects[i]->ObjectID);
    }

    for (auto go : gameObjects) {
        go->Serialize(saver);
    }

    currentScene->SaveScene(saver.database);

    return true;

}


bool SceneManagement::LoadScene(std::string sceneName, bool additive)
{
    // 1. Cleanup current scene
    for (auto go : gameObjects) Destroy(go);
    gameObjects.clear();
    SceneManagement::objectRegister.clear();

    Engine::GEngine->ClearDrawObjects();

    // 2. Read the flat file into a temporary map
    std::unordered_map<std::string, std::string> db;
    std::ifstream file(sceneName);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter = line.find('=');
        if (delimiter != std::string::npos) {
            std::string key = line.substr(0, delimiter);
            std::string val = line.substr(delimiter + 1);
            db[key] = val;
        }
    }

    // 3. Use the Serializer to reconstruct objects
    Serializer loader(Mode::Loading);
    loader.database = db;

    int rootCount = 0;
    loader.Property("Scene_RootCount", rootCount);

    // Instantiate the GameObjects first so IDs exist in the registry for linking
    for (int i = 0; i < rootCount; i++) {
        EntityID id;
        loader.Property("Root" + std::to_string(i) + "_ObjectID", id);
        GameObject* go = new GameObject("SerialObject",false);
        go->ForceID(id);
    }

    // Run the actual serialization (restores names and behaviours)
    for (auto go : gameObjects) {
        go->Serialize(loader);

        std::cout << go->name << std::endl;
    }

    //Call start on all serialised objects
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Start();
    }

    std::cout << "\n--- [REGISTER DEBUG] ---" << std::endl;
    std::cout << "Total Objects in Register: " << objectRegister.size() << std::endl;

    for (auto const& [id, obj] : objectRegister) {
        if (obj) {
            std::cout << " > ID: " << id
                      << " | Type: " << obj->GetTypeName()
                      << " | Memory Address: " << obj << std::endl;
        } else {
            std::cout << " > ID: " << id << " | [NULL POINTER ERROR]" << std::endl;
        }
    }

    std::cout << "--- [GAME OBJECT LIST] ---" << std::endl;
    for (auto go : gameObjects) {
        std::cout << " > GO: " << go->name << " (ID: " << go->ObjectID << ")" << std::endl;
        for (auto b : go->GetBehaviours()) {
            std::cout << "    - Bev: " << b->GetTypeName() << " (ID: " << b->ObjectID << ")" << std::endl;
        }
    }
    std::cout << "------------------------\n" << std::endl;

    return true;
}
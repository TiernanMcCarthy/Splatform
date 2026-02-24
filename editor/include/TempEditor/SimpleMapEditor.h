//
// Created by Tiern on 19/02/2026.
//

#ifndef SPLATFORM_SIMPLEMAPEDITOR_H
#define SPLATFORM_SIMPLEMAPEDITOR_H
#include "Objects/Behaviour.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"
#include "TestPlayer/PlayerSpawn.h"
#include <unordered_map>

class EditorTempCamera;
class SceneCamera;
class TestPlayer;

inline int tileSize=64;

struct Vector2iHash
{
    std::size_t operator()(const sf::Vector2i& v) const noexcept
    {
        return std::hash<int>{}(v.x) ^ (std::hash<int>{}(v.y) << 1);
    }
};
/// Temporary measure to just draw rectangular geometry for making "levels" and saving them to disk
class SimpleMapEditor : public Behaviour {
public:



    void Update(float deltaTime) override;

    void Start() override;



private:

    int posX=0;
    int posY=0;

    float snapSize[4] = {2,1,0.5f,0.25f};

    int currentSnap=1;

    RectangleBlock* lastObject= nullptr;

    RectangleBlock* currentContext= nullptr;

    PlayerSpawn* spawnPoint= nullptr;

    TestPlayer* player = nullptr;

    EditorTempCamera* camera= nullptr;

    sf::Vector2f spawnPos;

    GameObject* selection = nullptr;

    std::unordered_map<sf::Vector2i,GameObject*,Vector2iHash> spawnedObjects;

    bool isCreating=false;

    //std::vector<>

    void LoadTerrainFromFile();

    void ManageInput();

    void ManageSelection();

    void ManageSaving();

    void FinishBlock();

    void BuildBlock();

    void CheckStates();

    void CreateBlock();


};

#endif // SPLATFORM_SIMPLEMAPEDITOR_H

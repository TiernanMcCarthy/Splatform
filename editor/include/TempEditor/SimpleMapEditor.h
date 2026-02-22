//
// Created by Tiern on 19/02/2026.
//

#ifndef SPLATFORM_SIMPLEMAPEDITOR_H
#define SPLATFORM_SIMPLEMAPEDITOR_H
#include "Objects/Behaviour.h"
#include "Terrain/BuildingBlocks/RectangleBlock.h"
#include "TestPlayer/PlayerSpawn.h"

class SceneCamera;
class TestPlayer;
/// Temporary measure to just draw rectangular geometry for making "levels" and saving them to disk
class SimpleMapEditor : public Behaviour
{

public:



    void Update(float deltaTime) override;

    void Start() override;



private:

    RectangleBlock* lastObject= nullptr;

    RectangleBlock* currentContext= nullptr;

    PlayerSpawn* spawnPoint= nullptr;

    TestPlayer* player = nullptr;

    sf::Vector2f spawnPos;

    bool isCreating=false;

    void ManageSaving();

    void FinishBlock();

    void BuildBlock();

    void CheckStates();

    void CreateBlock();


};

#endif // SPLATFORM_SIMPLEMAPEDITOR_H

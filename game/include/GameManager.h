//
// Created by tiernan on 7/18/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Behaviour.h"
#include "SettlerManager.h"

#endif //GAMEMANAGER_H

class WorldMap;

//The Game Manager exists to maintain and manage the tile simulation
// It should contain and Manage the WorldMap and the Settler Managers
class GameManager : public Behaviour
{
public:

    GameManager();

    ~GameManager() = default;

    void Start() override;

    void Update(float deltaTime) override;



private:
    WorldMap* worldMap;

    SettlerManager* settlerManager;
};
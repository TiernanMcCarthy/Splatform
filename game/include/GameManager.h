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

    //Clock for managing processing
    sf::Clock simulationClock;

    //Rate of iterations per second
    int iterationsPerSecond;

    //last time an update was done (put at end of iteration)
    float lastIterationTime;

    //When iterations were started, if we go over budget in this second, skip iterations
    float iterationStart;

    int iterationCount=0;
};
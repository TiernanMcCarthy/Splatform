//
// Created by tiernan on 7/18/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../../engine/include/Objects/Behaviour.h"
#include "SettlerManager.h"
#include "Systems/ThreadPool.h"

#include <atomic>

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

    void IncreaseIterationSpeed();

    void DecreaseIterationSpeed();


    int GetGameSpeed();



private:
    WorldMap* worldMap;

    SettlerManager* settlerManager;

    //Clock for managing processing
    sf::Clock simulationClock;


    //Rate of iterations per second
    std::atomic<int> iterationsPerSecond{0};

    std::atomic<bool> killSimulationThread{false};

    std::atomic<bool> pauseThread;

    void SimulationLoop(const std::atomic<bool> &killThread, const std::atomic<int>& iterationsPerSec, SettlerManager& manager, const std::atomic<bool> &pauseThread);

    ThreadPool* simulationThread;
};
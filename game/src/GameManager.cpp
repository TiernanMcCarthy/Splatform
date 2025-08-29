//
// Created by tiernan on 7/20/25.
//


//Engine Includes
#include "../../engine/include/Objects/GameObject.h"
#include "Engine.h"

// Game Includes
#include "GameManager.h"

#include "Settlement.h"
#include "SettlerManager.h"
#include "TerrainTile.h"
#include "WorldMap.h"

#include <atomic>


GameManager::GameManager()
{

}

void foo()
{

}

void GameManager::Start()
{
    //Create World Map
     GameObject *worldObject = new GameObject("WorldMap");
     worldMap = worldObject->AddBehaviour<WorldMap>();
     worldMap->LoadMap("assets/map.png");

     Team::SetCapitalColour(sf::Color(255,192,0,255));

     //Create Settler Manager
     settlerManager = new SettlerManager(worldMap);

     settlerManager->StartGame(8);

     simulationClock=sf::Clock();

     iterationsPerSecond=60;

     simulationThread=  new ThreadPool(1);

     simulationThread->QueueJob(
         [this] {SimulationLoop(std::ref(killSimulationThread),std::ref(iterationsPerSecond), *settlerManager,std::ref(pauseThread));});


}

void GameManager::SimulationLoop(const std::atomic<bool> &killThread, const std::atomic<int>& iterationsPerSec, SettlerManager& manager,const std::atomic<bool> &pauseWorld)
{

    //last time an update was done (put at end of iteration)
    float lastIterationTime;

    //When iterations were started, if we go over budget in this second, skip iterations
    float iterationStart;

    int iterationCount=0;
    while (!killThread)
    {
        if (simulationClock.getElapsedTime().asSeconds() <  1 && iterationCount<iterationsPerSecond)
        {
            settlerManager->IterateSettlements();
            iterationCount++;
        }
        else if (simulationClock.getElapsedTime().asSeconds() >= 1) //We've iterated too many times or the clock is finished
        {
            if (iterationCount<iterationsPerSecond)
            {
                std::cout<<"Experiencing Slowdown at this speed"<<std::endl;
                int newSpeed=iterationsPerSec-1;
                iterationsPerSecond=newSpeed;
            }
            iterationCount=0;
            simulationClock.restart(); //Reset the clock for next iteration
        }
    }
}

void GameManager::IncreaseIterationSpeed()
{
    int iteration=iterationsPerSecond.load()+1;
    iterationsPerSecond.store(std::clamp(iteration,0,1000));
}

void GameManager::DecreaseIterationSpeed()
{
    int iteration=iterationsPerSecond.load()-1;
    iterationsPerSecond.store(std::clamp(iteration,0,30));
}


void GameManager::Update(float deltaTime)
{
    //Read and look for player interaction?

    //Draw the Map
    worldMap->DrawMap();
}

int GameManager::GetGameSpeed()
{
    return iterationsPerSecond.load();
}


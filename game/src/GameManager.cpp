//
// Created by tiernan on 7/20/25.
//


//Engine Includes
#include "../../engine/include/Objects/GameObject.h"
#include "Engine.h"

// Game Includes
#include "GameManager.h"
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

     //Create Settler Manager
     settlerManager = new SettlerManager(worldMap);

     settlerManager->StartGame(8);

     simulationClock=sf::Clock();

     iterationsPerSecond=4;


     simulationThread=  new ThreadPool(1);

     simulationThread->QueueJob(
         [this] {SimulationLoop(std::ref(killSimulationThread),std::ref(iterationsPerSecond), *settlerManager,std::ref(pauseThread));});

   // threadPool->QueueJob([&tempWorld,start, end, &found, &index, t] {FindHabitableTile(std::ref(tempWorld),start,end,std::ref(found),std::ref(index),t);});
    //SimulationLoop(&killSimulationThread,iterationsPerSecond,*settlerManager));

     /*Tile Testing
     TerrainTile* temp=worldMap->GetRandomTile();

     TerrainTile* newTile;
     temp->DrawTile(sf::Color::Black);

     //Above
     newTile=worldMap->GetTile(temp->GetPosition() + sf::Vector2u(0, -1));
     newTile->DrawTile(sf::Color::Yellow);

     //Left
    newTile=worldMap->GetTile(temp->GetPosition() + sf::Vector2u(-1, 0));
    newTile->DrawTile(sf::Color::Red);
     //Right
    newTile=worldMap->GetTile(temp->GetPosition() + sf::Vector2u(1, 0));
    newTile->DrawTile(sf::Color::Magenta);
     //Down
    newTile=worldMap->GetTile(temp->GetPosition() + sf::Vector2u(0, 1));
    newTile->DrawTile(sf::Color::Blue);*/


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


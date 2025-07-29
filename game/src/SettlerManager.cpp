//
// Created by tiernan on 7/20/25.
//
#include "SettlerManager.h"
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"

#include "GameSettings.h"

#include "Systems/ThreadPool.h"

#include <atomic>
#include <iostream>


void EpicFunction(std::atomic<bool>& testBool)
{
    testBool.exchange(!testBool);
}

SettlerManager::SettlerManager(WorldMap *map)
{
    if (map == nullptr)
    {
        std::cout<<"World map is not initialised, please review"<<std::endl;
        return;
    }
    worldMap = map;

    threadPool = new ThreadPool(4);

    std::atomic<bool> testBool=false;
    std::atomic<bool> testBool2=true;
    std::atomic<bool> testBool3=false;
    std::atomic<bool> testBool4=true;
    threadPool->QueueJob([&testBool] {EpicFunction(std::ref(testBool));});
    threadPool->QueueJob([&testBool2] {EpicFunction(std::ref(testBool2));});
    threadPool->QueueJob([&testBool3] {EpicFunction(std::ref(testBool3));});
    threadPool->QueueJob([&testBool4] {EpicFunction(std::ref(testBool4));});

}


void SettlerManager::StartGame(int teams)
{

    std::cout<<"Starting game with teams: "<<teams<<std::endl;


    for (int i=0; i<teams; i++)
    {
        Team* testTeam = new Team(i,1,1,playerColours[i]);
        TerrainTile* temp=worldMap->GetRandomTileThreaded();

        if (temp == nullptr)
        {
            std::cout<<"No terrain tile found at startup"<<std::endl;
            return;
        }

        Settlement* t = new Settlement(temp,testTeam);

        t->Init();

        PushSettler(t);
    }

}

void SettlerManager::PushSettler(Settlement *settler)
{
    settlements.push_back(settler);
    settler->Init();
}


void SettlerManager::IterateSettlements()
{
    //Run through settler list and complete their actions

    for (int i=0; i<settlements.size(); i++)
    {
        settlements[i]->Simulate(this);
    }
}

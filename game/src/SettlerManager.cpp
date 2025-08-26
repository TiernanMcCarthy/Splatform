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
#include <random>

void EpicFunction(std::atomic<bool>& testBool,std::atomic<bool>& testy)
{
    testBool.exchange(!testBool);
    testy.exchange(!testy);
}

SettlerManager::SettlerManager(WorldMap *map)
{

    if (map == nullptr)
    {
        std::cout<<"World map is not initialised, please review"<<std::endl;
        return;
    }
    worldMap = map;

}


void SettlerManager::StartGame(int teams)
{

    std::cout<<"Starting game with teams: "<<teams<<std::endl;

    Team* deadTeam = new Team(-1,1,1,sf::Color::Black);

    for (int i=0;i<worldMap->GetTileCount(); i++)
    {
        TerrainTile* tempTile=worldMap->GetTile(worldMap->ConvertIndexToCoordinates(i));

        if (tempTile->IsLand())
        {
            Settlement* newSettler = new Settlement(tempTile,deadTeam,this);
            settlements.push_back(newSettler);
            tempTile->DrawTile(tempTile->GetOriginalColour());
            //CreateSettler(tempTile,deadTeam);
        }
    }

    for (int i=0; i<teams; i++)
    {
        Team* testTeam = new Team(i,1,1,playerColours[i]);
        TerrainTile* temp=worldMap->GetRandomTileThreaded();

        if (temp == nullptr)
        {
            std::cout<<"No terrain tile found at startup"<<std::endl;
            return;
        }

        CreateSettler(temp,testTeam);
    }

}

void SettlerManager::PushSettler(Settlement *settler)
{
    settlements.push_back(settler);
    //settler->Init();
}


void SettlerManager::IterateSettlements()
{
    // in IterateSettlements
    static std::random_device rd;
    static std::mt19937 g(rd()); // Mersenne Twister engine

    std::shuffle(Settlement::directions.begin(), Settlement::directions.end(), g);

    //Run through settler list and complete their actions
    for (int i=0; i<settlements.size(); i++)
    {
        currentIteration = settlements[i];
        if (currentIteration->IsAlive())
        {
            currentIteration->Simulate();
        }
    }
}


void SettlerManager::CreateSettler(TerrainTile *target,Team* team)
{
    //Activate associated Settler with Tile
    Settlement* temp =&target->GetOwner();

    temp->MakeActive(team);
}

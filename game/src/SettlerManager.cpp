//
// Created by tiernan on 7/20/25.
//
#include "SettlerManager.h"
#include "Settlement.h"
#include "WorldMap.h"

#include <iostream>

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

    Team* testTeam = new Team(1,1,1,sf::Color::Blue);

    TerrainTile* temp=worldMap->GetRandomTile();

    Settlement* t = new Settlement(temp,testTeam);

    settlements.push_back(t);

    for (int i=0; i<teams; i++)
    {

    }

}

void SettlerManager::IterateSettlements()
{
    //Run through settler list and complete their actions

    for (int i=0; i<settlements.size(); i++)
    {
        settlements[i]->Simulate();
    }
}

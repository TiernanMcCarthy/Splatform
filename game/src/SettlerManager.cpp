//
// Created by tiernan on 7/20/25.
//
#include "SettlerManager.h"
#include "Settlement.h"
#include "TerrainTile.h"
#include "WorldMap.h"

#include "GameSettings.h"

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

    for (int i=0; i<teams; i++)
    {
        Team* testTeam = new Team(i,1,1,playerColours[i]);
        TerrainTile* temp=worldMap->GetRandomTile();

        Settlement* t = new Settlement(temp,testTeam);

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

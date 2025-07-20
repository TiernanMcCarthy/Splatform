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

    std::cout<<"Starting game "<<teams<<std::endl;

}

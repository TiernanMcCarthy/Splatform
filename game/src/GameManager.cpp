//
// Created by tiernan on 7/20/25.
//
#include "GameManager.h"
#include "Engine.h"
#include "GameObject.h"
#include "WorldMap.h"
#include "SettlerManager.h"

 GameManager::GameManager()
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
}

//
// Created by tiernan on 7/20/25.
//
#include "GameManager.h"
#include "Engine.h"
#include "GameObject.h"
#include "SettlerManager.h"
#include "TerrainTile.h"
#include "WorldMap.h"

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

     TerrainTile* temp=worldMap->GetRandomTile();

      std::cout<<temp->IsLand()<<std::endl;
}

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

     settlerManager->StartGame(4);

     simulationClock=sf::Clock();

     iterationsPerSecond=2;

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

void GameManager::Update(float deltaTime)
{
    //Simulate the map
    // Settler Manager Simulate (x number of iterations per Second)(game speed)
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
        }
        iterationCount=0;
        simulationClock.restart(); //Reset the clock for next iteration
    }

    //Read and look for player interaction?

    //Draw the Map
    worldMap->DrawMap();
}

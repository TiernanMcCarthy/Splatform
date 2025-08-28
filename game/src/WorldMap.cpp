//
// Created by tiernan on 7/9/25.
//



//Engine Includes
#include "../../engine/include/Objects/GameObject.h"
#include "Constants.h"
#include <Systems/FastCommonExtensions.h>
//Game Includes
#include "WorldMap.h"




#include "TerrainTile.h"

#include <Systems/ThreadPool.h>
#ifdef WIN32
#include <random>
#endif
#ifndef WIN32
#include <bits/stdc++.h>
#endif

#include <atomic>
#include <iostream>
#include <time.h>
#include <utility>

sf::Color terrainColour=sf::Color(51, 204, 0, 255);

 WorldMap::WorldMap()
{

}


void WorldMap::Start()
{
     worldMapVisual= gameObject->AddBehaviour<BoxRenderer>();
     gameObject->transform.localPosition=sf::Vector2f(DISPLAYWIDTH/2,DISPLAYHEIGHT/2);

     threadPool= new ThreadPool(4);
}

bool WorldMap::LoadMap(const std::string &path)
{
     mapImage= sf::Image();
     //Load image and set cosmetics
     if (!mapImage.loadFromFile(path))
        {
            std::cout<<"Cannot load map "<<path<<std::endl;
            return false;
        }
     worldMapVisual->ApplyImage(mapImage);
     dimensions = worldMapVisual->renderTexture->getSize();

     gameObject->transform.localScale=sf::Vector2f(dimensions.x,dimensions.y);
     worldMapVisual->UpdateVisualComponents();

     //Create Tilemap
     sf::Color pixelColour;
     bool validLand=false;
     int index=0;
     for (int y=0; y<dimensions.y; y++)
     {
        for (int x=0; x<dimensions.x; x++)
        {
            pixelColour=mapImage.getPixel(sf::Vector2u(x,y));
            if (pixelColour==terrainColour)
            {
                validLand=true;
                habitableTileCount++;
            }
            else
            {
                validLand=false;
            }
            world.push_back(new TerrainTile(validLand,pixelColour,this,index));
            index++;
        }

     }
     return true;
}

sf::Vector2u WorldMap::ConvertIndexToCoordinates(int index) const
{
     return sf::Vector2u(index%dimensions.x,index/dimensions.x);
}


void WorldMap::DrawMap()
{


     //Run through Draw Commands

     int elementsToDraw=drawCommands.size();

     for (int i=0; i<elementsToDraw; i++)
     {
         if (drawCommands[0].coords.x>mapImage.getSize().x || drawCommands[0].coords.y>mapImage.getSize().y || drawCommands[0].coords.x<0 || drawCommands[0].coords.y<0)
         {
             std::cout<<"Something went wrong when drawing"<<std::endl;
         }
         mapImage.setPixel(drawCommands[0].coords,drawCommands[0].colour);
         drawCommands.erase(drawCommands.begin());
     }

     if (!worldMapVisual->renderTexture->loadFromImage(mapImage))
     {
         std::cout<<"Invalid Map Image, cannot update texture"<<std::endl;
     }


     //Clear out range but not the entire list as the thread might still be running and popping elements in
     //drawCommands.erase(drawCommands.begin(),drawCommands.begin()+elementsToDraw-1);

}

//Fetches a tile from the worldmap for manipulation or reading
TerrainTile *WorldMap::GetTile(int x, int y)
{
     int size=world.size();
     int location= x+ y*dimensions.x;


     if (x>dimensions.x || x<=0 || location>=size)
     {
         std::cout<<"Invalid Coordinate requested"<<std::endl;
         return nullptr;
     }

     return world[location];
}

//Fetches a tile from the worldmap for manipulation or reading
TerrainTile *WorldMap::GetTile(sf::Vector2u pos)
 {
     int size=world.size();
     int location= pos.x+ pos.y*dimensions.x;


     if (pos.x>dimensions.x || pos.x<0 || location>=size)
     {
         std::cout<<"Invalid Coordinate requested"<<std::endl;
         return nullptr;
     }

     return world[location];
 }

//Returns random habitable Tile
TerrainTile* WorldMap::GetRandomTile()
{
     int remainingTiles=world.size()-populatedTileCount;
     if (remainingTiles<1)
     {
         std::cout<<"No Free Tiles to populate, no tiles can be returned";
         return nullptr;
     }
     //If we have more than 5% active tiles, random sort shouldn't take too long, otherwise, linear search for a tile
     if (remainingTiles>world.size()*0.05f)
     {
         TerrainTile* testTile;
         int x;
         int y;
         while (true)
         {
             srand(time(NULL));
             x = rand()%dimensions.x;
             y = rand()%dimensions.y;

             testTile=GetTile(x,y);
             if (testTile!=nullptr)
             {
                 if (testTile->IsLand() && !testTile->IsSettled())
                 {
                     return testTile;
                 }
             }

         }
     }
     else
     {
         for (int i=0; i<world.size(); i++)
         {
             if (world[i]->IsLand() && !world[i]->IsSettled())
             {
                 return world[i];
             }
         }

     }

     return nullptr;
}

int FindHabitableTile(const std::vector<TerrainTile*>& vec, size_t start, size_t end, std::atomic<bool>& found, std::atomic<int>& index, int thread_id)
 {
     srand(time(NULL));
     //int x = rand()%
     //int y = rand()%dimensions.y
        TerrainTile* tile=vec[start];
         while (true)
         {
             if (found==true)
             {
                 return -1;
             }
             int i = start + rand()%(end-start);
             tile=vec[i];
             if (tile->IsLand() && !tile->IsSettled())
             {
                 found.exchange(true);
                 index.store(i);
                 return i;
             }
         }


     return -1;
 }

TerrainTile *WorldMap::GetRandomTileThreaded()
{
     int remainingTiles=world.size()-populatedTileCount;
     if (remainingTiles<1)
     {
         std::cout<<"No Free Tiles to populate, no tiles can be returned";
         return nullptr;
     }

     size_t threadCount=4;
     size_t chunkSize=world.size()/threadCount;

     std::vector<std::thread> threads;
     std::atomic<bool> found = false;
     std::atomic<int> index =-1;

     std::vector<size_t> chunkOrder(threadCount);
     for (size_t i = 0; i < threadCount; ++i) {
         chunkOrder[i] = i;
     }

     //Ridiculous C++ Randomness for Shuffle...
     std::random_device rd;
     std::mt19937 g(rd());

     std::vector<TerrainTile*> &tempWorld =world;


     std::shuffle(chunkOrder.begin(), chunkOrder.end(),g);
     for (size_t i = 0; i < threadCount; i++) {
         size_t t=chunkOrder[i];

         size_t start = t * chunkSize;

         size_t end = (t == threadCount - 1) ? world.size() : (t + 1) * chunkSize;

         threadPool->QueueJob([&tempWorld,start, end, &found, &index, t] {FindHabitableTile(std::ref(tempWorld),start,end,std::ref(found),std::ref(index),t);});

         //threads.emplace_back(FindHabitableTile, std::ref(world), start, end,std::ref(found),std::ref(index), t);
     }

     while (threadPool->IsBusy())
     {
        std::cout<<"Waiting for threads to finish"<<std::endl;
        //Holds Threads
     }

     if (index!=-1)
     {
         return world[index];
     }

     std::cout<<"No fsaffsafas tiles found";
    return nullptr;
}

/*
TerrainTile *WorldMap::GetRandomTileThreaded()
 {
     int remainingTiles=world.size()-populatedTileCount;
     if (remainingTiles<1)
     {
         std::cout<<"No Free Tiles to populate, no tiles can be returned";
         return nullptr;
     }


     int threadCount=threadPool->GetThreadCount();
     size_t chunkSize=world.size()/threadCount;

     std::atomic<bool> found = false;
     std::atomic<int> index =-1;

     std::vector<size_t> chunkOrder(threadCount);
     for (size_t i = 0; i < threadCount; ++i) {
         chunkOrder[i] = i;
     }

     //Ridiculous C++ Randomness for Shuffle...
     std::random_device rd;
     std::mt19937 g(rd());

     std::shuffle(chunkOrder.begin(), chunkOrder.end(),g);
     for (size_t i = 0; i < threadCount; i++) {
         size_t t=chunkOrder[i];

         size_t start = t * chunkSize;

         size_t end = (t == threadCount - 1) ? world.size() : (t + 1) * chunkSize;
         threadPool->QueueJob([world,&found] {
             FindHabitableTile(std::ref(found));
         });


         //threadPool->QueueJob([world,&found] {FindHabitableTile(std::ref(found));});
         //threads.emplace_back(FindHabitableTile, std::ref(world), start, end,std::ref(found),std::ref(index), t);
     }

     for (auto& th : threads)
         th.join();

     if (index!=-1)
     {
         return world[index];
     }

     return nullptr;
 }*/


void WorldMap::AddDrawCommand(DrawCommand dc)
{
    drawCommands.push_back(dc);
}



void WorldMap::Update(float deltatime)
{

     //Debug Draw to show alive tiles
     if (EngineInputSystem::InputSystem->MouseTwo->wasReleasedThisFrame==true)
     {
         for (int i=0; i<world.size(); i++)
         {
             if (world[i]->IsSettled())
             {
                 world[i]->DrawTile(sf::Color::Black);
             }
         }
     }

}


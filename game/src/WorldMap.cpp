//
// Created by tiernan on 7/9/25.
//

#include "WorldMap.h"

#include "Constants.h"
#include "GameObject.h"
#include "TerrainTile.h"

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
}

bool WorldMap::LoadMap(std::string path)
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

sf::Vector2u WorldMap::ConvertIndexToCoordinates(int index)
{
     return sf::Vector2u(index%dimensions.x,index/dimensions.x);
}


void WorldMap::DrawMap()
{

     //Run through Draw Commands

     for (int i=0; i<drawCommands.size(); i++)
     {
         mapImage.setPixel(drawCommands[i].coords,drawCommands[i].colour);
     }

     if (!worldMapVisual->renderTexture->loadFromImage(mapImage))
     {
         std::cout<<"Invalid Map Image, cannot update texture"<<std::endl;
     }

     drawCommands.clear();
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


     if (pos.x>dimensions.x || pos.x<=0 || location>=size)
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

void WorldMap::AddDrawCommand(DrawCommand dc)
{
    drawCommands.push_back(dc);
}



void WorldMap::Update(float deltatime)
{

}


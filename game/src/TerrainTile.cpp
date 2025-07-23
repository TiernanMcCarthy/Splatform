//
// Created by tiernan on 7/13/25.
//

#include "TerrainTile.h"
#include "WorldMap.h"

 TerrainTile::TerrainTile(bool land, sf::Color colour,WorldMap* worldObject, int ind)
{
     isLand=land;
     originalColour=colour;
     currentColour=colour;
     owner=nullptr;
     world=worldObject;
     index=ind;
     position=worldObject->ConvertIndexToCoordinates(index);
}

bool TerrainTile::IsLand()
{
    return isLand;
}

bool TerrainTile::IsSettled()
{
     if (owner!=nullptr)
     {
         return true;
     }

     return false;
 }


void TerrainTile::ClearSettlement()
{
    owner=nullptr;
}

void TerrainTile::SetOwner(Settlement* newOwner)
{
    if (newOwner!=nullptr)
    {
        owner=newOwner;
    }
}

Settlement& TerrainTile::GetOwner()
{
    return *owner;
}

void TerrainTile::DrawTile(sf::Color colour)
 {
     currentColour=colour;
     world->AddDrawCommand(DrawCommand(position,currentColour));

 }

sf::Vector2u TerrainTile::GetPosition()
 {
     return position;
 }

TerrainTile& TerrainTile::GetLand(sf::Vector2u pos)
 {
     return *world->GetTile(pos);
 }


void TerrainTile::ResetTile()
 {

 }


sf::Color TerrainTile::GetColour()
 {
     return currentColour;
 }

